#ifndef FUNCTIONS_SEQUENCE_TASK_H
#define FUNCTIONS_SEQUENCE_TASK_H

#include "defines.h"
#include <Task.h>

template<typename T> using Callback = void(*)(T*);
template<typename T> using CallbackReturningInterval = uint32_t(*)(T*);

class SequenceNode {
	friend class FunctionsSequenceTask;
	friend class SequenceTaskBuilder;

	SequenceNode(Callback<void> callback, uint32_t intervalToNextTask,
			void* stateHolder = nullptr) :
			callback(callback), intervalToNextTask(intervalToNextTask), stateHolder(
					stateHolder) {
	}
	SequenceNode(CallbackReturningInterval<void> callbackReturningInterval,
			void* stateHolder = nullptr) :
			callbackReturningInterval(callbackReturningInterval), stateHolder(
					stateHolder) {
	}
	Callback<void> callback = nullptr;
	CallbackReturningInterval<void> callbackReturningInterval = nullptr;
	uint32_t intervalToNextTask = 0;
	void* stateHolder = nullptr;
	SequenceNode* pNext = nullptr;
};

class FunctionsSequenceTask: public Task {
public:
	virtual ~FunctionsSequenceTask() {
		SequenceNode *p, *pToBeDeleted;
		p = pFirstNode;
		while (p != nullptr) {
			pToBeDeleted = p;
			p = p->pNext;
			delete pToBeDeleted;
		}
	}
private:
	FunctionsSequenceTask(Callback<void> callback, uint32_t intervalToNextTask,
			void* stateHolder) :
			Task(0) {
		pFirstNode = pLastNode = new SequenceNode(callback, intervalToNextTask,
				stateHolder);
	}

	FunctionsSequenceTask(
			CallbackReturningInterval<void> functionReturningInterval,
			void* stateHolder) :
			Task(0) {
		pFirstNode = pLastNode = new SequenceNode(functionReturningInterval,
				stateHolder);
	}

	FunctionsSequenceTask(const FunctionsSequenceTask&) = delete;
	FunctionsSequenceTask& operator=(const FunctionsSequenceTask&) = delete;

	friend class SequenceTaskBuilder;

	bool OnStart() override {
		sequenceCompleted = false;
		pNodeToRun = pFirstNode;
		_remainingTime = 0;
		return true;
	}

	void OnUpdate(uint32_t taskDeltaTime) override {
		if (sequenceCompleted && !repeat) {
			_timeInterval = -1;
			return;
		}
		if (pNodeToRun->callbackReturningInterval != nullptr) {
			pNodeToRun->intervalToNextTask =
					pNodeToRun->callbackReturningInterval(
							pNodeToRun->stateHolder);
		} else {
			pNodeToRun->callback(pNodeToRun->stateHolder);
		}
		_timeInterval = pNodeToRun->intervalToNextTask;
		if (pNodeToRun->pNext != nullptr) {
			pNodeToRun = pNodeToRun->pNext;
		} else {

			/*
			 * this is the last node
			 */
			if (repeat) {
				pNodeToRun = pFirstNode;
			} else {
				sequenceCompleted = true;
				_timeInterval = -1;
			}
		}
	}

	SequenceNode* pFirstNode;
	SequenceNode* pLastNode;
	SequenceNode* pNodeToRun = nullptr;
	boolean repeat = false;
	boolean sequenceCompleted = false;
};

class SequenceTaskBuilder {
public:
	template<typename T>
	static SequenceTaskBuilder begin(Callback<T> callback,
			uint32_t intervalToNextTask, T* stateHolder = nullptr) {
		SequenceTaskBuilder builder { new FunctionsSequenceTask(
				(Callback<void> ) callback, intervalToNextTask,
				(void*) stateHolder) };
		return builder;
	}

	template<typename T>
	static SequenceTaskBuilder begin(
			CallbackReturningInterval<T> callbackReturningInterval,
			T* stateHolder = nullptr) {
		SequenceTaskBuilder builder { new FunctionsSequenceTask(
				(CallbackReturningInterval<void> ) callbackReturningInterval,
				(void*) stateHolder) };
		return builder;
	}

	template<typename T>
	SequenceTaskBuilder& then(Callback<T> callback, uint32_t intervalToNextTask,
			T* stateHolder = nullptr) {
		pInstance->pLastNode->pNext = new SequenceNode(callback,
				intervalToNextTask, stateHolder);
		pInstance->pLastNode = pInstance->pLastNode->pNext;
		return *this;
	}

	template<typename T>
	SequenceTaskBuilder& then(
			CallbackReturningInterval<T> callbackReturningIntervalck,
			T* stateHolder = nullptr) {
		pInstance->pLastNode->pNext = new SequenceNode(
				callbackReturningIntervalck, stateHolder, stateHolder);
		pInstance->pLastNode = pInstance->pLastNode->pNext;
		return *this;
	}

	FunctionsSequenceTask& done() {
		pInstance->repeat = false;
		return *pInstance;
	}

	FunctionsSequenceTask& thenRepeat() {
		pInstance->repeat = true;
		return *pInstance;
	}

private:
	SequenceTaskBuilder(FunctionsSequenceTask* pInstance) :
		pInstance(pInstance) {
	}
	FunctionsSequenceTask* pInstance;
};

#endif
