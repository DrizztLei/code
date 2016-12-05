package nachos.userprog;

import java.util.LinkedList;

import nachos.machine.*;
import nachos.threads.*;

public class UserKernel extends ThreadedKernel
{

	public UserKernel()
	{
		super();
	}

	public void initialize(String[] args)
	{
		super.initialize(args);

		console = new SynchConsole(Machine.console());

		Machine.processor().setExceptionHandler(new Runnable()
		{
			public void run()
			{
				exceptionHandler();
			}
		});

		for (int currentPageIndex = 0; currentPageIndex < Machine.processor().getNumPhysPages(); currentPageIndex++)
			freePages.add(new TranslationEntry(0, currentPageIndex, false, false, false, false));

		freePagesLock = new Lock();
	}

	public static UserProcess currentProcess()
	{
		if (!(KThread.currentThread() instanceof UThread))
			return null;

		return ((UThread) KThread.currentThread()).process;
	}

	public void exceptionHandler()
	{
		Lib.assertTrue(KThread.currentThread() instanceof UThread);

		UserProcess process = ((UThread) KThread.currentThread()).process;
		int cause = Machine.processor().readRegister(Processor.regCause);
		process.handleException(cause);
	}

	public void run()
	{
		super.run();

		UserProcess process = UserProcess.newUserProcess();

		String shellProgram = Machine.getShellProgramName();
		Lib.assertTrue(process.execute(shellProgram, new String[]
		{}));

		KThread.currentThread().finish();
	}

	TranslationEntry[] acquirePages(int numPages) throws InadequatePagesException
	{
		TranslationEntry[] returnPages = null;

		freePagesLock.acquire();

		if (!freePages.isEmpty() && freePages.size() >= numPages)
		{
			returnPages = new TranslationEntry[numPages];

			for (int i = 0; i < numPages; ++i)
			{
				returnPages[i] = freePages.remove();
				returnPages[i].valid = true;
			}
		}

		freePagesLock.release();

		if (returnPages == null)
			throw new InadequatePagesException();
		else
			return returnPages;
	}

	void releasePages(TranslationEntry[] pageTable)
	{
		freePagesLock.acquire();

		for (TranslationEntry te : pageTable)
		{
			freePages.add(te);
			te.valid = false;
		}

		freePagesLock.release();
	}

	public void terminate()
	{
		super.terminate();
	}

	public static SynchConsole console;

	private LinkedList<TranslationEntry> freePages = new LinkedList<TranslationEntry>();

	private Lock freePagesLock;

	static class InadequatePagesException extends Exception
	{
		private static final long serialVersionUID = 6256028192007727092L;
	}
	
	public void setlfTest()
	{
			UserProcess up = UserProcess.newUserProcess();
			up.execute("cp.coff", new String[] { "2", "a.txt", "self_b.txt" });
	}
}
