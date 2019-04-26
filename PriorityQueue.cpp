#include<cstring>
#include<iostream>
#include<cmath>
#include "PriorityQueue.hpp"
using namespace std;

typedef PriorityQueue::DataType DataType;

PriorityQueue::PriorityQueue(unsigned int capacity)
{
	capacity_ = capacity + 1;
	size_ = 0;
	heap_ = new DataType[capacity_];
	heap_[0] = 0;
}

PriorityQueue::~PriorityQueue()
{
	delete [] heap_;
	heap_ = NULL;
	size_ = 0;
}

bool PriorityQueue::enqueue(DataType val)
{
	if(full())
		return false;
	else if(empty())
	{
		size_++;
		heap_[1] = val;
		return true;
	}
	else
	{
		size_++;
		heap_[size_] = val;
		unsigned int i = size_;
		while(i > 1 && heap_[i] > heap_[i / 2])
		{
			DataType temp = heap_[i / 2];
			heap_[i / 2] = heap_[i];
			heap_[i] = temp;
			i /= 2;
		}
		return true;
	}
}

bool PriorityQueue::dequeue()
{
	if(empty())
		return false;
	else
	{
		heap_[1] = heap_[size_];
		unsigned int i = 1;
		while(i < size_ && i*2+1 <= size_ && (heap_[i] < heap_[2*i] || heap_[i] < heap_[2*i + 1]))
		{

			if(heap_[2 * i + 1] < heap_[2*i])
			{
				DataType temp = heap_[2*i];
				heap_[2*i] = heap_[i];
				heap_[i] = temp;
				i *= 2;
			}
			else if(heap_[2 * i] < heap_[2*i + 1])
			{
				DataType temp = heap_[2*i + 1];
				heap_[2*i + 1] = heap_[i];
				heap_[i] = temp;
				i = 2*i + 1;
			}
		}
		size_--;
		return true;
	}
}

DataType PriorityQueue::max() const
{
	return heap_[1];
}

bool PriorityQueue::empty() const
{
	return size_ == 0;
}

bool PriorityQueue::full() const
{
	return size_ == capacity_ - 1;
}

unsigned int PriorityQueue::size() const
{
	return size_;
}

void PriorityQueue::print() const
{
	if(empty())
		cout << "The queue is empty." << endl;
	else
		for(unsigned int i = 1; i <= size_; i++)
			cout << "Item No. " << i << " = " << heap_[i] << endl;
}




