#include "pch.h"
#include "logger.h"

void logWrite::execute()
{
	
}

logger::logger()
{

}

logger::logger(std::string _filename, int _maxThreadCount)
{
	filename = _filename;
	maxThreadCount = _maxThreadCount;
	//getInput();
	logThread();
}

void logger::log(std::string message)
{
	static std::mutex mutex;
	mutex.lock();

	std::ofstream file(filename, std::ios::app);

	if (file.is_open())
	{
		file << message << "\n";
		file.flush();
		file.close();
	}
	else
	{
		std::cout << "Failed to open file." << std::endl;
		return;
	}

	mutex.unlock();
}

void logger::logThread()
{
	for (int i = 0; i < 100; ++i)
	{
		std::string msg = "MESSAGE NO. ";
		msg += std::to_string(i);
		tasks.emplace_back(logWrite());
	}
}

void logger::logFlush()
{
	for (auto& t : threads)
	{
		t.join();
	}
}

void logger::getInput()
{
	std::string input;

	std::cout << "Enter a character: " << std::endl;
	std::cin >> input;

	threads.emplace_back(&logger::log, this, input);
}
