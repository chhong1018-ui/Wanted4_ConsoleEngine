#pragma once

#include <iostream>

template<typename T, size_t Size>
class Queue
{
public:
	Queue()
		: front(0), rear(0), size(Size + 1)
	{
	}

	bool IsEmpty() const
	{
		return front == rear;
	}

	bool IsFull() const
	{
		return ((rear + 1) % size) == front;
	}

	void Enqueue(const T& value)
	{
		if (IsFull() == true)
		{
			std::cout << "Error: 큐가 가득 찼습니다.\n";
			return;
		}

		rear = (rear + 1) % size;
		data[rear] = value;
	}

	T Dequeue()
	{
		if (IsEmpty() == true)
		{
			std::cout << "Error: 큐가 비었습니다.\n";
		}

		front = (front + 1) % size;
		return data[front];
	}

	T Peek() const
	{
		if (IsEmpty() == true)
		{
			std::cout << "Error: 큐가 비었습니다.\n";
		}

		return data[(front + 1) % size];
	}

private:
	size_t front;
	size_t rear;
	size_t size;
	T data[Size + 1];
};