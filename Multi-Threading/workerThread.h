#pragma once
#include <thread>
#include <atomic>
#include "logger.h"
#include "taskQueue.h"

class workerThread
{
private:
	std::atomic<bool> threadExit;
public:
	std::thread thread;
	logWrite task;

	void findWork(taskQueue * taskQueue);
};