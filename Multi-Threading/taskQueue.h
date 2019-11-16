#pragma once
#include <atomic>
#include <mutex>
#include "task.h"

template <typename T>
class taskQueue
{
private:
	size_t capacity;
	size_t writeHead;
	size_t readHead;
	T ** tasks;

public:

	taskQueue(size_t taskCapacity)
	{
		tasks = new T*[taskCapacity];
		capacity = taskCapacity;
		writeHead = 0;
		readHead = 0;
	}
	~taskQueue()
	{
		delete[] tasks;
	}

	T * pop()
	{
		task * t = tasks[readHead % maxCapacity()];
		++readHead;
		return t;
	}

	void push(T * t)
	{
		tasks[writeHead % maxCapacity()] = t;
		++writeHead;
	}

	bool isEmpty()
	{
		return writeHead == readHead;
	}

	size_t size()
	{
		return (writeHead >= readHead) ? (writeHead - readHead) + 1 : maxCapacity() - (readHead - writeHead) + 1;
	}

	size_t maxCapacity()
	{
		return capacity;
	}
};