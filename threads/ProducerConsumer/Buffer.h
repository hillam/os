#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <iostream>
#include <stdio.h>
#include <mutex>

using namespace std;

class Buffer
{
public:
	Buffer() : m_buffer(), MAX_SIZE(4), m_mut()
	{ }

	bool isEmpty() const
	{ return m_buffer.size() == 0; }

	bool isFull() const
	{ return m_buffer.size() == MAX_SIZE; }

	int consume();
	int produce(int i);

private:
	const int MAX_SIZE;
	vector<int> m_buffer;
	mutex m_mut;
};

#endif