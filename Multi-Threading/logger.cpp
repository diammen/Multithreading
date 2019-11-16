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

logger::~logger()
{
	for (auto& t : threads)
	{
		delete t;
	}
}

logger::logger(std::string _filename, int _maxThreadCount)
{
	filename = _filename;
	maxThreadCount = _maxThreadCount;
	tasks = new taskQueue<task>(1000);
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
	for (size_t i = 0; i < maxThreadCount; ++i)
	{
		threads.emplace_back(new workerThread(tasks));
	}
}

void logger::logTest()
{
	threads.clear();
	queueTasks();
	logThread();
}

void logger::queueTasks()
{
	for (int i = 1; i <= tasks->maxCapacity(); ++i)
	{
		std::string msg = "MESSAGE NO. ";
		msg += std::to_string(i);
		tasks->push(new logWrite(i + (cycles * tasks->maxCapacity())));
	}
	cycles++;
}

void logger::getInput()
{
	getchar();
	logTest();
}