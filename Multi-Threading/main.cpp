#include "pch.h"
#include "logger.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

int main()
{
	logger myLog = logger("log.txt", 5);
	std::vector<std::thread> threads;

	myLog.logFlush();
    return 0;
}