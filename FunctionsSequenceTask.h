#ifndef FUNCTIONS_SEQUENCE_TASK_H
#define FUNCTIONS_SEQUENCE_TASK_H

#include "defines.h"
#include <Task.h>

typedef void (*pNodeFunction)(void* pStateHolder);
typedef uint32_t (*pNodeFunctionReturningInterval)(void* pStateHolder);
typedef void* pStateHolder;

class SequenceNode {
	friend class FunctionsSequenceTask;
public:
	SequenceNode(pNodeFunction function, uint32_t intervalToNextTask, pStateHolder pStateHolder = nullptr) :
			pFunction(function), intervalToNextTask(intervalToNextTask), pStateHolder(pStateHolder) {
	}
	SequenceNode(pNodeFunctionReturningInterval functionReturningInterval, pStateHolder pStateHolder = nullptr) :
			pFunctionReturningInterval(functionReturningInterval), pStateHolder(pStateHolder) {
	}
private:
	pNodeFunction pFunction = nullptr;
	pNodeFunctionReturningInterval pFunctionReturningInterval = nullptr;
	void* pStateHolder = nullptr;
	uint32_t intervalToNextTask = 0;
	SequenceNode* pNext = nullptr;
};

class FunctionsSequenceTask: public Task {
public:
	FunctionsSequenceTask(pNodeFunction function, uint32_t intervalToNextTask, pStateHolder pStateHolder = nullptr);
	FunctionsSequenceTask(pNodeFunctionReturningInterval functionReturningInterval, pStateHolder pStateHolder = nullptr);
	virtual ~FunctionsSequenceTask();
	FunctionsSequenceTask& then(pNodeFunction function,
			uint32_t intervalToNextTask, pStateHolder pStateHolder = nullptr);
	FunctionsSequenceTask& then(pNodeFunctionReturningInterval functionReturningInterval, pStateHolder pStateHolder = nullptr);
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
