package nachos.threads;

import nachos.machine.*;

import java.util.TreeMap;

public class Alarm
{

	private TreeMap<Long, KThread> waitingThreads;

	public Alarm()
	{
		waitingThreads = new TreeMap<Long, KThread>();
		Machine.timer().setInterruptHandler(new Runnable()
		{
			public void run()
			{
				timerInterrupt();
			}
		});
	}

	public void timerInterrupt()
	{
		boolean intStatus = Machine.interrupt().disable();

		long curTime = Machine.timer().getTime();
		while (!waitingThreads.isEmpty() && waitingThreads.firstKey() <= curTime)
			waitingThreads.pollFirstEntry().getValue().ready();

		Machine.interrupt().restore(intStatus);

		KThread.yield();
	}
	public void waitUntil(long x)
	{
		// Sleeping thread is an atomic operation
		boolean intStatus = Machine.interrupt().disable();

		// Place current thread on a wait queue and put it to sleep
		waitingThreads.put(Machine.timer().getTime() + x, KThread.currentThread());
		KThread.sleep();

		Machine.interrupt().restore(intStatus);
	}

	private static final char dbgAlarm = 'a'; // Flag to enable Alarm debug

	public static void selfTest()
	{
		Lib.debug(dbgAlarm, "Alarm Self Test");

		// Test that alarm wakes up thread after proper amount of time
		KThread thread = new KThread(new Runnable()
		{
			public void run()
			{
				final long ticks = 1000;
				long sleepTime = Machine.timer().getTime();
				ThreadedKernel.alarm.waitUntil(ticks);
				long wakeTime = Machine.timer().getTime();

				Lib.debug(dbgAlarm, (((wakeTime - sleepTime >= ticks) ? "[PASS]" : "[FAIL]")
						+ ": Thread slept at least " + ticks + " ticks " + sleepTime + "->" + wakeTime));
			}
		});
		thread.fork();
		thread.join();

		KThread threadA = new KThread(new TestSeqThread('A', 100));
		KThread threadB = new KThread(new TestSeqThread('B', 700));
		KThread threadC = new KThread(new TestSeqThread('C', 1400));

		threadA.fork();
		threadB.fork();
		threadC.fork();
		threadA.join();
		threadB.join();
		threadC.join();

		Lib.debug(dbgAlarm, (TestSeqThread.wakeSequence.equals("ABC") ? "[PASS]" : "[FAIL")
				+ ": Threads woke up in order (" + TestSeqThread.wakeSequence + ")");
	}

	private static class TestSeqThread implements Runnable
	{
		char myName;
		long mySleepTicks;

		static String wakeSequence = "";
		static Lock lock = new Lock();

		public TestSeqThread(char name, long sleepTicks)
		{
			myName = name;
			mySleepTicks = sleepTicks;
		}

		public void run()
		{
			ThreadedKernel.alarm.waitUntil(mySleepTicks);
			lock.acquire();
			wakeSequence = wakeSequence + myName;
			lock.release();
		}
	}
}
