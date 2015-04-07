#include "Buffer.h"

int Buffer::consume()
{
	m_mut.lock();
	int i = -1;
	if (isEmpty())
	{
		printf("Failed attempt to consume, need more production...\n");
	}
	else
	{
		i =  m_buffer[0];
		m_buffer.erase(m_buffer.begin());
		printf("Items after consumption %d\n", (int)m_buffer.size());
	}
	m_mut.unlock();
	return i;
}

int Buffer::produce(int i)
{
	m_mut.lock();
	if (isFull())
	{
		printf("Failed attempt to produce, need more consumption...\n");
		i = -1;
	}
	else
	{
		m_buffer.push_back(i);
		printf("Items after production %d\n", (int)m_buffer.size());
	}
	m_mut.unlock();
	return i;
}