#pragma once
#include <atomic>
#include "logger.h"

class taskQueue
{
private:
	size_t capacity;
	std::mutex access;
	size_t head;
	task ** tasks;

public:

	taskQueue(size_t taskCapacity)
	{
		tasks = new task*[taskCapacity];
		capacity = taskCapacity;
		head = 0;
	}
	~taskQueue()
	{
		delete[] tasks;
	}

	task * pop()
	{
		task * t = tasks[--head];
		return t;
	}

	void push(task * t)
	{
		tasks[head++] = t;
	}

	bool isEmpty()
	{
		return head == 0;
	}

	size_t capacity()
	{
		return capacity;
	}
};