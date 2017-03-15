package scagnostics;

public class BinnedData
{
	public int[] x = null;
	public int[] y = null;
	private int[] counts = null;

	private static final double RESOLUTION = 1000;

	public BinnedData(double[] x, double[] y, int[] counts)
	{
		this.x = integerizeData(x);
		this.y = integerizeData(y);
		this.counts = counts;
	}

	private int[] integerizeData(double[] x)
	{
		int n = x.length;
		int[] xd = new int[n];
		for (int i = 0; i < n; i++)
		{
			xd[i] = (int)(RESOLUTION * x[i]);
			// xd[i] = (int)(x[i]);
			// System.out.println(xd[i]);
		}
		return xd;
	}

	protected int[] getXData()
	{
		return x;
	}

	protected int[] getYData()
	{
		return y;
	}

	protected int[] getCounts()
	{
		return counts;
	}
}