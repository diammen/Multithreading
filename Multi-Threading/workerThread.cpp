#include "pch.h"
#include "workerThread.h"

void workerThread::findWork(taskQueue * taskQueue)
{
	while (!taskQueue->isEmpty())
	{
		taskQueue->pop()->execute();
	}
}