import java.util.*;

public class Main
{
	public static void main(String args[]) throws Exception
	{
		Buffer b = new Buffer();
		(new Thread(new Producer(b))).start();
		(new Thread(new Producer(b))).start();
		(new Thread(new Consumer(b))).start();
		(new Thread(new Consumer(b))).start();
	}
}

class Buffer
{
	private static final int MAX_SIZE = 4;
	private List<Integer> m_buffer;

	public Buffer()
	{
		m_buffer = new ArrayList<Integer>();
	}

	synchronized public int consume() throws Exception
	{
		while (isEmpty())
		{
			System.out.println("Waiting for production...");
			wait();
		}
		if (m_buffer.size() < 1)
			throw new Exception("Size too small!");
		int i = m_buffer.remove(0);

		System.out.println("Items after consumption " + m_buffer.size());
		notifyAll();
		return i;
	}

	synchronized public void produce(int i) throws Exception
	{
		while (isFull())
		{
			System.out.println("Waiting for consumption...");
			wait();
		}
		if (m_buffer.size() > MAX_SIZE)
			throw new Exception("Size too large!");

		m_buffer.add(i);

		System.out.println("Items after production " + m_buffer.size());
		notifyAll();
	}

	private boolean isEmpty()
	{
		return m_buffer.size() == 0;
	}

	private boolean isFull()
	{
		return m_buffer.size() == MAX_SIZE;
	}

}


class Producer implements Runnable
{
	private static final int PROD_VAR = 1000;
	private static Random m_rand = new Random();
	private Buffer m_buffer;

	public Producer(Buffer b)
	{
		m_buffer = b;
	}

	public void run()
	{
		try
		{
			int i = 0;
			while (true)
			{
				Thread.sleep(m_rand.nextInt(PROD_VAR)+1000);
				m_buffer.produce(i);
				System.out.println("Produced " + i);
				i++;
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}

class Consumer implements Runnable
{
	private static final int CONS_VAR = 100;
	private static Random m_rand = new Random();
	private Buffer m_buffer;

	public Consumer(Buffer b)
	{
		m_buffer = b;
	}

	public void run()
	{
		try
		{
			while (true)
			{
				Thread.sleep(m_rand.nextInt(CONS_VAR)+1000);
				System.out.println("Consumed " + m_buffer.consume());
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}