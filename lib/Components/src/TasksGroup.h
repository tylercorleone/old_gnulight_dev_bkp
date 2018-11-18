#include<Task.h>

class TasksGroup: public Task {
public:
	TasksGroup() :
			Task(-1) {
	}
	void addTask(Task* pTask) {
		Task* pIterate = _pFirstTask;
		while (pIterate != nullptr) {
			if (pIterate == pTask) {
				return;
			}
			pIterate = pIterate->_pNext;
		}
		if (_pFirstTask == nullptr) {
			_pFirstTask = pTask;
			_pLastTask = pTask;
		} else {
			_pLastTask->_pNext = pTask;
			_pLastTask = pTask;
		}
	if (isActive() {
				taskManager.StartTask(ptask);
			}
		}
	}
	void removeTask(Task* pTask) {
		Task* pIterate = _pFirstTask;
		Task* pIteratePrev = nullptr;
		while (pIterate != nullptr) {
			Task* pNext = pIterate->_pNext;
			if (pIterate == pTask) {
				// Remove it
				pIterate->_taskState = TaskState_Stopped;
				pIterate->_pNext = nullptr;

				if (pIterate == _pFirstTask) {
					// first one, correct our first pointer
					_pFirstTask = pNext;
					if (pIterate == _pLastTask) {
						// last one, correct our last pointer
						_pLastTask = _pFirstTask;
					}
				} else {
					// all others correct the previous to remove it
					pIteratePrev->_pNext = pNext;
					if (pIterate == _pLastTask) {
						// last one, correct our last pointer
						_pLastTask = pIteratePrev;
					}
				}
			} else {
				// didn't remove, advance the previous pointer
				pIteratePrev = pIterate;

				if (pIterate->_taskState == TaskState_Running) {
					// add the initial time so we don't loose any remainders
					pIterate->_remainingTime += pIterate->_timeInterval;
					// if we are still less than delta time, things are running slow
					// so push to the next update frame
					if (pIterate->_remainingTime <= deltaTime) {
						pIterate->_remainingTime = deltaTime + TaskTimeAccuracy;
					}
				}

				uint32_t newRemainingTime = pIterate->_remainingTime
						- deltaTime;
				pIterate->_remainingTime = newRemainingTime;

				if (newRemainingTime < nextWakeTime) {
					nextWakeTime = newRemainingTime;
				}
			}

			pIterate = pNext; // iterate to the next
		}
	}

private:
	TaskManager _taskManager;
	Task* _pFirstTask;
	Task* _pLastTask;
};
