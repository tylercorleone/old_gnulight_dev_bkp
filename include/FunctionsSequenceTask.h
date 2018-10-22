#ifndef FUNCTIONS_SEQUENCE_TASK_H
#define FUNCTIONS_SEQUENCE_TASK_H

#include "defines.h"
#include <Task.h>

using pNodeFunction = void (*)(void*);
using pNodeFunctionReturningInterval = uint32_t (*)(void*);
using Callback = void (*)(void*);

class SequenceNode {
	friend class FunctionsSequenceTask;
public:
	// SequenceNode(pNodeFunction function, uint32_t intervalToNextTask, void* pStateHolder = nullptr) :
	// 		pFunction(function), intervalToNextTask(intervalToNextTask), pStateHolder(pStateHolder) {
	// }
	SequenceNode(Callback callback, uint32_t intervalToNextTask) :
			callback(callback), intervalToNextTask(intervalToNextTask) {
	}
	SequenceNode(pNodeFunctionReturningInterval functionReturningInterval, void* pStateHolder = nullptr) :
			pFunctionReturningInterval(functionReturningInterval), pStateHolder(pStateHolder) {
	}
private:
	pNodeFunction pFunction = nullptr;
	Callback callback = nullptr;
	pNodeFunctionReturningInterval pFunctionReturningInterval = nullptr;
	void* pStateHolder = nullptr;
	uint32_t intervalToNextTask = 0;
	SequenceNode* pNext = nullptr;
};

class FunctionsSequenceTask: public Task {
public:
	// FunctionsSequenceTask(pNodeFunction function, uint32_t intervalToNextTask, void* pStateHolder = nullptr);
	FunctionsSequenceTask(Callback callback, uint32_t intervalToNextTask);
	FunctionsSequenceTask(pNodeFunctionReturningInterval functionReturningInterval, void* pStateHolder = nullptr);
	virtual ~FunctionsSequenceTask();
	FunctionsSequenceTask& then(pNodeFunction function,
			uint32_t intervalToNextTask, void* pStateHolder = nullptr);
	FunctionsSequenceTask& then(pNodeFunctionReturningInterval functionReturningInterval, void* pStateHolder = nullptr);
	void done();
	void thenRepeat();
protected:
	bool OnStart() override;
	void OnUpdate(uint32_t deltaTime) override;
	SequenceNode* pFirstNode;
	SequenceNode* pLastNode;
	SequenceNode* pNodeToRun = nullptr;
	bool repeat = false;
	bool sequenceCompleted = false;
};

#endif
