#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include "task.h"
#include "workerThread.h"
#include "taskQueue.h"

class logWrite : public task
{
public:
	std::string message;
	int index;

	logWrite(int _index);
	void execute();
};

class logger
{
	std::string filename;
	std::string fileBuffer;
	std::fstream file;
	int maxThreadCount = 0;
	int cycles = 0;

public:
	taskQueue<task> * tasks;
	std::vector<workerThread*> threads;

	logger();
	~logger();
	logger(std::string _filename, int _maxThreadCount);

	void log(std::string message);
	void logThread();
	void logTest();
	void queueTasks();
	void getInput();
};