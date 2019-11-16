#pragma once
#include <thread>
#include <atomic>
#include "taskQueue.h"

class workerThread
{
	std::thread thread;
public:
	workerThread(taskQueue<task> * taskQueue);
	~workerThread();
	void findWork(taskQueue<task> * taskQueue);
};