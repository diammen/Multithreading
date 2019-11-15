#include "pch.h"
#include "logger.h"

logWrite::logWrite(int _index)
{
	index = _index;
}

void logWrite::execute()
{
	static std::mutex mutex;
	mutex.lock();

	message = "Message NO. ";
	message += std::to_string(index);

	std::cout << message << std::endl;

	mutex.unlock();
}

logger::logger()
{

}

logger::logger(std::string _filename, int _maxThreadCount)
{
	filename = _filename;
	maxThreadCount = _maxThreadCount;
	queueTasks();
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
		mutex.unlock();
		return;
	}

	mutex.unlock();
}

void logger::logThread()
{
	while (tasks.size() > 0)
	{
		if (threads.size() < maxThreadCount)
		{
			threads.emplace_back(std::thread(&logWrite::execute, tasks[0]));
			tasks.erase(tasks.begin());
		}
		else
		{
			return;
		}
		threads.emplace_back(std::thread(&logWrite::execute, tasks[0]));
		tasks.erase(tasks.begin());
	}
}

void logger::logFlush()
{
	for (auto& t : threads)
	{
		t.join();
	}
}

void logger::queueTasks()
{
	for (int i = 1; i <= 100; ++i)
	{
		std::string msg = "MESSAGE NO. ";
		msg += std::to_string(i);
		tasks.emplace_back(logWrite(i));
	}
}

void logger::getInput()
{
	std::string input;

	std::cout << "Enter a character: " << std::endl;
	std::cin >> input;

	threads.emplace_back(&logger::log, this, input);
}