#include "pch.h"
#include "workerThread.h"

workerThread::workerThread(taskQueue<task> * taskQueue)
{
	thread = std::thread(&workerThread::findWork, this, taskQueue);
}

workerThread::~workerThread()
{
	thread.join();
}

void workerThread::findWork(taskQueue<task> * taskQueue)
{
	while (!taskQueue->isEmpty())
	{
		taskQueue->pop()->execute();
	}
}