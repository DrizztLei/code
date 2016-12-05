package nachos.threads;

import java.util.HashSet;
import java.util.Random;

import nachos.machine.*;

public class LotteryScheduler extends Scheduler
{
	public LotteryScheduler()
	{
	}

	public int getPriority(KThread thread)
	{
		Lib.assertTrue(Machine.interrupt().disabled());

		return getLotteryThreadState(thread).getTickets();
	}

	public int getEffectivePriority(KThread thread)
	{
		Lib.assertTrue(Machine.interrupt().disabled());

		return getLotteryThreadState(thread).getEffectiveTickets();
	}

	public void setPriority(KThread thread, int priority)
	{
		Lib.assertTrue(Machine.interrupt().disabled());

		Lib.assertTrue(priority >= priorityMinimum && priority <= priorityMaximum);

		LotteryThreadState lts = getLotteryThreadState(thread);

		if (priority != lts.getTickets())
			lts.setTickets(priority);
	}

	public boolean increasePriority()
	{
		boolean intStatus = Machine.interrupt().disable(), returnBool = true;

		KThread thread = KThread.currentThread();

		int priority = getPriority(thread);
		if (priority == priorityMaximum)
			returnBool = false;
		else
			setPriority(thread, priority + 1);

		Machine.interrupt().restore(intStatus);
		return returnBool;
	}

	public boolean decreasePriority()
	{
		boolean intStatus = Machine.interrupt().disable(), returnBool = true;

		KThread thread = KThread.currentThread();

		int priority = getPriority(thread);
		if (priority == priorityMinimum)
			returnBool = false;
		else
			setPriority(thread, priority - 1);

		Machine.interrupt().restore(intStatus);
		return returnBool;
	}

	static final int priorityDefault = 1;

	static final int priorityMinimum = 1;

	static final int priorityMaximum = Integer.MAX_VALUE;

	protected LotteryThreadState getLotteryThreadState(KThread thread)
	{
		if (thread.schedulingState == null)
			thread.schedulingState = new LotteryThreadState(thread);

		return (LotteryThreadState) thread.schedulingState;
	}

	@Override
	public ThreadQueue newThreadQueue(boolean transferPriority)
	{
		return new LotteryQueue(transferPriority);
	}

	protected class LotteryQueue extends ThreadQueue
	{

		LotteryQueue(boolean transferTickets2)
		{
			transferTickets = transferTickets2;
		}

		@Override
		public void waitForAccess(KThread thread)
		{
			Lib.assertTrue(Machine.interrupt().disabled());
			getLotteryThreadState(thread).waitForAccess(this);
		}

		@Override
		public KThread nextThread()
		{
			Lib.assertTrue(Machine.interrupt().disabled());
			if (waiting.isEmpty())
				return null;
			else
			{
				int ticketIndex = randomGenerator.nextInt(totalEffectiveTickets) + 1;

				KThread returnThread = null;

				for (LotteryThreadState lts : waiting)
				{
					ticketIndex -= lts.getEffectiveTickets();

					if (ticketIndex <= 0)
					{
						returnThread = lts.thread;
						lts.acquire(this);
						break;
					}
				}

				return returnThread;
			}
		}

		public void acquire(KThread thread)
		{
			Lib.assertTrue(Machine.interrupt().disabled());
			getLotteryThreadState(thread).acquire(this);
		}

		public void print()
		{
		}

		private LotteryThreadState lockingThread;

		private HashSet<LotteryThreadState> waiting = new HashSet<LotteryThreadState>();

		private boolean transferTickets;

		private int totalEffectiveTickets;

		Random randomGenerator = new Random();

		void updateEffectiveTickets()
		{
			int temp = 0;
			for (LotteryThreadState lts : waiting)
				temp += lts.getEffectiveTickets();
			totalEffectiveTickets = temp;
		}

		void removeFromWaiting(LotteryThreadState lotteryThreadState)
		{
			if (waiting.remove(lotteryThreadState))
			{
				updateEffectiveTickets();// TODO: probably can do a shorter
											// update in the future

				if (lockingThread != null)
					lockingThread.fullUpdateEffectiveTickets();
			}
		}
	}

	protected static class LotteryThreadState
	{

		LotteryThreadState(KThread thread2)
		{
			thread = thread2;
		}

		void acquire(LotteryQueue lotteryQueue)
		{
			if (lotteryQueue.lockingThread != this)
			{
				if (lotteryQueue.lockingThread != null)
					lotteryQueue.lockingThread.release(lotteryQueue);

				lotteryQueue.removeFromWaiting(this);

				lotteryQueue.lockingThread = this;

				acquired.add(lotteryQueue);
				waiting.remove(lotteryQueue);

				fullUpdateEffectiveTickets();
			}
		}

		private void release(LotteryQueue lotteryQueue)
		{
			if (lotteryQueue.lockingThread == this)
			{
				if (!acquired.remove(lotteryQueue))
					System.out.println("Error : Release something not in the acquired set");
				lotteryQueue.lockingThread = null;
				fullUpdateEffectiveTickets();
			}
		}

		void waitForAccess(LotteryQueue lotteryQueue)
		{
			release(lotteryQueue);
			if (!lotteryQueue.waiting.contains(this))
			{
				waiting.add(lotteryQueue);
				lotteryQueue.waiting.add(this);

				if (lotteryQueue.transferTickets && lotteryQueue.lockingThread != null)
					lotteryQueue.lockingThread.fullUpdateEffectiveTickets();
				else
					lotteryQueue.updateEffectiveTickets();
			}
		}

		int getEffectiveTickets()
		{
			return effectiveTickets;
		}

		int getTickets()
		{
			return tickets;
		}

		void setTickets(int tickets2)
		{
			tickets = tickets2;
			fullUpdateEffectiveTickets();
		}

		private void fullUpdateEffectiveTickets()
		{
			int temp = tickets;

			for (LotteryQueue lq : acquired)
				if (lq.transferTickets)
					for (LotteryThreadState lts : lq.waiting)
						temp += lts.effectiveTickets;

			effectiveTickets = temp;

			for (LotteryQueue lq : waiting)
			{
				lq.updateEffectiveTickets();
				if (lq.transferTickets && lq.lockingThread != null)
					lq.lockingThread.fullUpdateEffectiveTickets();
			}
		}

		private HashSet<LotteryQueue> acquired = new HashSet<LotteryQueue>();

		private HashSet<LotteryQueue> waiting = new HashSet<LotteryQueue>();

		private int tickets = priorityDefault;

		private int effectiveTickets = priorityDefault;

		private KThread thread;
	}

	public static void selfTest()
	{
		if (ThreadedKernel.scheduler != null && ThreadedKernel.scheduler instanceof LotteryScheduler)
		{
			boolean oldValue = Machine.interrupt().disable();
			noDonation();
			withDonation();
			Machine.interrupt().restore(oldValue);
		}
	}

	private static void withDonation()
	{
		KThread k1 = new KThread(), k2 = new KThread(), k3 = new KThread(), k4 = new KThread();
		LotteryQueue lq1 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(true),
				lq2 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(true),
				lq3 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(true);

		lq1.acquire(k1);
		lq2.acquire(k2);
		lq3.acquire(k3);

		lq1.waitForAccess(k2);
		lq2.waitForAccess(k3);
		lq3.waitForAccess(k4);

		((LotteryThreadState) k1.schedulingState).setTickets(10);
		((LotteryThreadState) k2.schedulingState).setTickets(10);
		((LotteryThreadState) k3.schedulingState).setTickets(10);
		((LotteryThreadState) k4.schedulingState).setTickets(10);

		Lib.assertTrue(((LotteryThreadState) k1.schedulingState).getEffectiveTickets() == 40
				&& ((LotteryThreadState) k2.schedulingState).getEffectiveTickets() == 30
				&& ((LotteryThreadState) k3.schedulingState).getEffectiveTickets() == 20
				&& ((LotteryThreadState) k4.schedulingState).getEffectiveTickets() == 10);
	}

	private static void noDonation()
	{
		KThread k1 = new KThread(), k2 = new KThread(), k3 = new KThread(), k4 = new KThread();
		LotteryQueue lq1 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(false),
				lq2 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(false),
				lq3 = (LotteryQueue) ThreadedKernel.scheduler.newThreadQueue(false);

		lq1.acquire(k1);
		lq2.acquire(k2);
		lq3.acquire(k3);

		lq1.waitForAccess(k2);
		lq2.waitForAccess(k3);
		lq3.waitForAccess(k4);

		((LotteryThreadState) k1.schedulingState).setTickets(100);
		((LotteryThreadState) k2.schedulingState).setTickets(100);
		((LotteryThreadState) k3.schedulingState).setTickets(100);
		((LotteryThreadState) k4.schedulingState).setTickets(100);

		Lib.assertTrue(((LotteryThreadState) k1.schedulingState).getEffectiveTickets() == 100
				&& ((LotteryThreadState) k2.schedulingState).getEffectiveTickets() == 100
				&& ((LotteryThreadState) k3.schedulingState).getEffectiveTickets() == 100
				&& ((LotteryThreadState) k4.schedulingState).getEffectiveTickets() == 100);
	}
}
