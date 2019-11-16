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
	logger myLog("log.txt", 4);

	myLog.getInput();
    return 0;
}