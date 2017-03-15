package scagnostics;

public class Binner
{
	private int maxBins;

	public Binner(int maxBins)
	{
		this.maxBins = maxBins;
	}

	public final BinnedData binHex(double[] x, double[] y, int nBins)
	{

		int n = x.length;

		// scaling constants
		
		// System.out.println(nBins);

		double con1 = .25;
		double con2 = 1. / 3.;
		double c1 = (double) (nBins - 1);
		double c2 = c1 / Math.sqrt(3.);
		int jinc = nBins;
		int iinc = 2 * nBins;
		int nBin = (nBins + 20) * (nBins + 20);

		int[] count = new int[nBin];
		double[] xbin = new double[nBin];
		double[] ybin = new double[nBin];

		// fill bins

		for (int i = 0; i < n; i++)
		{
			if (Double.isNaN(x[i]))
				continue;
			if (Double.isNaN(y[i]))
				continue;
			double sx = c1 * x[i];
			double sy = c2 * y[i];
			int i1 = (int) (sy + .5);
			int j1 = (int) (sx + .5);
			double dy = sy - (double) i1;
			double dx = sx - (double) j1;
			double dist1 = dx * dx + 3. * dy * dy;
			int m;
			if (dist1 < con1)
			{
				m = i1 * iinc + j1;
				// System.out.println("1 : " + m);
			} else if (dist1 > con2)
			{
				// System.out.println(sy);
				// System.out.println(iinc);
				// System.out.println(sx);
				// System.out.println(jinc);
				
				m = (int) sy * iinc + (int) sx + jinc;
				// System.out.println("2 : " + m);
			} else
			{
				int i2 = (int) sy;
				int j2 = (int) sx;
				dy = sy - (double) i2 - .5;
				dx = sx - (double) j2 - .5;
				double dist2 = dx * dx + 3. * dy * dy;
				if (dist1 <= dist2)
				{
					m = i1 * iinc + j1;
					// System.out.println("3 : " + m);
				} else
				{
					m = i2 * iinc + j2 + jinc;
					// System.out.println("4 : " + m);
				}
			}
			// System.out.println(m);
			count[m]++;
			xbin[m] += (x[i] - xbin[m]) / count[m];
			ybin[m] += (y[i] - ybin[m]) / count[m];
		}

		nBin = deleteEmptyBins(count, xbin, ybin);
		if (nBin > maxBins)
		{
			nBins = 2 * nBins / 3;
			return binHex(x, y, nBins);
		}

		int[] tcount = new int[nBin];
		double[] xtbin = new double[nBin];
		double[] ytbin = new double[nBin];

		System.arraycopy(count, 0, tcount, 0, nBin);
		System.arraycopy(xbin, 0, xtbin, 0, nBin);
		System.arraycopy(ybin, 0, ytbin, 0, nBin);

		return new BinnedData(xtbin, ytbin, tcount);
	}

	private int deleteEmptyBins(int[] count, double[] xbin, double[] ybin)
	{

		int k = 0;
		for (int i = 0; i < count.length; i++)
		{
			if (count[i] > 0)
			{
				count[k] = count[i];
				xbin[k] = xbin[i];
				ybin[k] = ybin[i];
				k++;
			}
		}
		return k;
	}
}