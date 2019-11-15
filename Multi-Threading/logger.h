#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include "task.h"
#include "workerThread.h"

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
	int maxThreadCount = 0;

public:
	std::vector<task> tasks;
	std::vector<std::thread> threads;

	logger();
	logger(std::string _filename, int _maxThreadCount);

	void log(std::string message);
	void logThread();
	void logFlush();
	void queueTasks();
	void getInput();
};