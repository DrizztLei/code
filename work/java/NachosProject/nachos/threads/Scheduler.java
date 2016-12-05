package nachos.threads;

import nachos.machine.*;

/**
 * Coordinates a group of thread queues of the same kind.
 * 
 * @see nachos.threads.ThreadQueue
 */
public abstract class Scheduler
{
	/**
	 * Allocate a new scheduler.
	 */
	public Scheduler()
	{
	}


	public abstract ThreadQueue newThreadQueue(boolean transferPriority);

	public int getPriority(KThread thread)
	{
		Lib.assertTrue(Machine.interrupt().disabled());
		return 0;
	}


	public int getPriority()
	{
		return getPriority(KThread.currentThread());
	}

	
	public int getEffectivePriority(KThread thread)
	{
		Lib.assertTrue(Machine.interrupt().disabled());
		return 0;
	}

	public int getEffectivePriority()
	{
		return getEffectivePriority(KThread.currentThread());
	}


	public void setPriority(KThread thread, int priority)
	{
		Lib.assertTrue(Machine.interrupt().disabled());
	}

	public void setPriority(int priority)
	{
		setPriority(KThread.currentThread(), priority);
	}

	public boolean increasePriority()
	{
		return false;
	}

	public boolean decreasePriority()
	{
		return false;
	}
}
