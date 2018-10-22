#include "FunctionsSequenceTask.h"

FunctionsSequenceTask::FunctionsSequenceTask(Callback callback, uint32_t intervalToNextTask) :
		Task(0) {
	pFirstNode = pLastNode = new SequenceNode(callback, intervalToNextTask);
}

FunctionsSequenceTask::FunctionsSequenceTask(
		pNodeFunctionReturningInterval functionReturningInterval,
		void* pStateHolder) :
		Task(0) {
	pFirstNode = pLastNode = new SequenceNode(functionReturningInterval,
			pStateHolder);
}

FunctionsSequenceTask& FunctionsSequenceTask::then(pNodeFunction function,
		uint32_t intervalToNextTask, void* pStateHolder) {
	pLastNode->pNext = new SequenceNode(function, intervalToNextTask);
	pLastNode = pLastNode->pNext;
	return *this;
}

FunctionsSequenceTask& FunctionsSequenceTask::then(
		pNodeFunctionReturningInterval functionReturningInterval, void* pStateHolder) {
	pLastNode->pNext = new SequenceNode(functionReturningInterval, pStateHolder);
	pLastNode = pLastNode->pNext;
	return *this;
}

void FunctionsSequenceTask::done() {
	repeat = false;
}

void FunctionsSequenceTask::thenRepeat() {
	repeat = true;
}

FunctionsSequenceTask::~FunctionsSequenceTask() {
	SequenceNode *p, *pToBeDeleted;
	p = pFirstNode;
	while (p != nullptr) {
		pToBeDeleted = p;
		p = p->pNext;
		delete pToBeDeleted;
	}
}

bool FunctionsSequenceTask::OnStart() {
	sequenceCompleted = false;
	pNodeToRun = pFirstNode;
	_remainingTime = 0;
	return true;
}

void FunctionsSequenceTask::OnUpdate(uint32_t taskDeltaTime) {
	if (sequenceCompleted && !repeat) {
		_timeInterval = -1;
		return;
	}
	if (pNodeToRun->pFunctionReturningInterval != nullptr) {
		pNodeToRun->intervalToNextTask = pNodeToRun->pFunctionReturningInterval(
				pNodeToRun->pStateHolder);
	} else {
		pNodeToRun->pFunction(pNodeToRun->pStateHolder);
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