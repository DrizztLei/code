package nachos.threads;

import java.util.LinkedList;

import nachos.machine.*;

/**
 * An implementation of condition variables that disables interrupt()s for
 * synchronization.
 * 
 * <p>
 * You must implement this.
 * 
 * @see nachos.threads.Condition
 */
public class Condition2
{
	/**
	 * Allocate a new condition variable.
	 * 
	 * @param conditionLock
	 *            the lock associated with this condition variable. The current
	 *            thread must hold this lock whenever it uses <tt>sleep()</tt>,
	 *            <tt>wake()</tt>, or <tt>wakeAll()</tt>.
	 */
	public Condition2(Lock conditionLock)
	{
		this.conditionLock = conditionLock;
	}

	public void sleep()
	{
		Lib.assertTrue(conditionLock.isHeldByCurrentThread());

		boolean status = Machine.interrupt().disable();

		conditionLock.release();

		waitQueue.add(KThread.currentThread());

		KThread.sleep();

		conditionLock.acquire();

		Machine.interrupt().restore(status);
	}

	/**
	 * Wake up at most one thread sleeping on this condition variable. The
	 * current thread must hold the associated lock.
	 */
	public void wake()
	{
		Lib.assertTrue(conditionLock.isHeldByCurrentThread());

		boolean intStatus = Machine.interrupt().disable();

		if (!waitQueue.isEmpty())
			waitQueue.pop().ready();

		Machine.interrupt().restore(intStatus);
	}

	/**
	 * Wake up all threads sleeping on this condition variable. The current
	 * thread must hold the associated lock.
	 */
	public void wakeAll()
	{
		Lib.assertTrue(conditionLock.isHeldByCurrentThread());

		boolean intStatus = Machine.interrupt().disable();

		for (KThread waitingThead : waitQueue)
		{
			waitingThead.ready();
		}

		waitQueue.clear();

		Machine.interrupt().restore(intStatus);
	}

	/**
	 * Tests whether this module is working.
	 */
	public static void selfTest()
	{

		System.out.println("Condition2 Self Test");
		KThread thread;

		thread = new KThread(new Runnable()
		{
			Condition2 cond = new Condition2(new Lock());

			public void run()
			{
				try
				{
					cond.sleep();
					System.out.println("ERROR : : Successfully called Condition2.sleep() without holding condition lock");
				}
				catch (Error e)
				{
					System.out.println(
							"INFO : : Condition2.sleep() threw assertion when called without holding condition lock");
				}
				try
				{
					cond.wake();
					System.out.println("ERROR : : Successfully called Condition2.wake() without holding condition lock");
				}
				catch (Error e)
				{
					System.out.println(
							"INFO : : Condition2.wake() threw assertion when called without holding condition lock");
				}
				try
				{
					cond.wakeAll();
					System.out
							.println("ERROR : : Successfully called Condition2.wakeAll() without holding condition lock");
				}
				catch (Error e)
				{
					System.out.println(
							"INFO : : Condition2.wakeAll() threw assertion when called without holding condition lock");
				}
			}
		});
		thread.fork();
		thread.join();

		final Lock lock = new Lock();
		final Condition2 cond = new Condition2(lock);

		KThread thread1 = new KThread(new Runnable()
		{
			public void run()
			{
				lock.acquire();
				cond.sleep();

				System.out.println(
						(lock.isHeldByCurrentThread() ? "INFO : " : "ERROR : ") + ": Thread reacquires lock when woken.");
				lock.release();
			}
		});

		KThread thread2 = new KThread(new Runnable()
		{
			public void run()
			{
				lock.acquire();
				cond.w();
				lock.release();
			}
		});

		thread1.fork();
		thread2.fork();
		thread1.join();

		WakeCounter.wakeups = 0;
		WakeCounter.lock = lock;
		WakeCounter.cond = cond;

		new KThread(new WakeCounter()).fork();
		new KThread(new WakeCounter()).fork();
		thread = new KThread(new Runnable()
		{
			public void run()
			{
				lock.acquire();
				cond.wake();
				lock.release();
			}
		});
		thread.fork();
		thread.join();

		WakeCounter.wakeups = 0;

		new KThread(new WakeCounter()).fork();
		new KThread(new WakeCounter()).fork();
		thread = new KThread(new Runnable()
		{
			public void run()
			{
				lock.acquire();
				cond.wakeAll();
				lock.release();
			}
		});
		thread.fork();
		thread.join();

	}

	protected void w()
	{
		// TODO Auto-generated method stub
		
	}

	/**
	 * Test class which increments a static counter when woken
	 */
	static class WakeCounter implements Runnable
	{
		public static int wakeups = 0;
		public static Lock lock = null;
		public static Condition2 cond = null;

		public void run()
		{
			lock.acquire();
			cond.sleep();
			wakeups++;
			lock.release();
		}
	}

	private Lock conditionLock;

	private LinkedList<KThread> waitQueue = new LinkedList<KThread>();
}
