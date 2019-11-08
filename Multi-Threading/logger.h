#pragma once
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include "task.h"

class logWrite : task
{
public:
	std::string message;

	void execute();
};

class logger
{
	std::string filename;
	int maxThreadCount;

public:
	std::vector<task> tasks;
	std::vector<std::thread> threads;

	logger();
	logger(std::string _filename, int _maxThreadCount);

	void log(std::string message);
	void logThread();
	void logFlush();
	void getInput();
};