/*
 * Scagnostics
 *
 * Leland Wilkinson and Anushka Anand (University of Illinois at Chicago)
 * This program accompanies the following paper:
 
 * Wilkinson L., Anand, A., and Grossman, R. (2006). High-Dimensional visual analytics: 
 *   Interactive exploration guided by pairwise views of point distributions. 
 *   IEEE Transactions on Visualization and Computer Graphics, November/December 2006 (Vol. 12, No. 6) pp. 1363-1372.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software.
 * Supporting documentation must also include a citation of
 * the abovementioned article.
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, THE AUTHORS MAKE NO
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
 * OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.
 */
package scagnostics;

public class Cluster
{

	private int[] members;
	private int numClusters;
	private int numIterations;
	private int nVar;
	private int nRow;

	public Cluster(int numClusters, int numIterations)
	{
		this.numIterations = 3;
		this.numClusters = 0;
		if (numIterations != 0)
			this.numIterations = numIterations;
		if (numClusters != 0)
			this.numClusters = numClusters;
	}

	public int[] compute(double[][] data)
	{
		nRow = data.length;
		nVar = data[0].length;
		boolean useStoppingRule = false;
		double[][] ssr = null;
		if (numClusters == 0)
		{
			useStoppingRule = true;
			numClusters = 25;
			ssr = new double[numClusters][nVar];
		}

		double[][] center = new double[numClusters][nVar];
		double[][] count = new double[numClusters][nVar];
		double[][] mean = new double[numClusters][nVar];
		double[][] min = new double[numClusters][nVar];
		double[][] max = new double[numClusters][nVar];
		double[][] ssq = new double[numClusters][nVar];
		int[] closestPoints = new int[numClusters];
		double[] closestDistances = new double[numClusters];

		members = new int[nRow];
		int[] mem = new int[nRow];

		for (int k = 0; k < numClusters; k++)
		{

			/* find best assignments for current number of clusters */
			for (int iter = 0; iter < numIterations; iter++)
			{
				boolean reassigned = false;
				for (int l = 0; l <= k; l++)
				{
					for (int j = 0; j < nVar; j++)
					{
						if (iter == 0 || center[l][j] != mean[l][j])
						{
							reassign(k, data, center, count, mean, min, max, ssq, closestPoints, closestDistances);
							reassigned = true;
							break;
						}
					}
					if (reassigned)
						break;
				}
				if (!reassigned || k == 0)
					break;
			}

			/* check whether we should stop */

			if (useStoppingRule)
			{
				double ssq1 = 0;
				double ssq2 = 0;
				for (int j = 0; j < nVar; j++)
				{
					for (int l = 0; l <= k; l++)
					{
						ssq1 += ssr[l][j];
						ssq2 += ssq[l][j];
						ssr[l][j] = ssq[l][j];
					}
				}
				double pre = (ssq1 - ssq2) / ssq1; // proportional reduction of
													// error
				if (pre > 0 && pre < .1)
				{
					numClusters = k;
					reassign(k, data, center, count, mean, min, max, ssq, closestPoints, closestDistances);
					System.arraycopy(mem, 0, members, 0, nRow);
					break;
				} else
				{
					System.arraycopy(members, 0, mem, 0, nRow);
				}
			}

			/* now split a cluster to increment number of clusters */

			if (k < numClusters - 1)
			{
				int kn = k + 1;
				double dmax = 0;
				int jm = 0;
				int km = 0;
				double cutpoint = 0;
				for (int l = 0; l <= k; l++)
				{
					for (int j = 0; j < nVar; j++)
					{
						double dm = max[l][j] - min[l][j];
						if (dm > dmax)
						{
							cutpoint = mean[l][j];
							dmax = dm;
							jm = j;
							km = l;
						}
					}
				}
				for (int i = 0; i < nRow; i++)
				{
					if (members[i] == km && data[i][jm] > cutpoint)
					{
						for (int j = 0; j < nVar; j++)
						{
							count[km][j]--;
							count[kn][j]++;
							mean[km][j] -= (data[i][j] - mean[km][j]) / count[km][j];
							mean[kn][j] += (data[i][j] - mean[kn][j]) / count[kn][j];
						}
					}
				}
			}
		}

		int nc = 0;
		double cutoff = .1;
		for (int k = 0; k < numClusters; k++)
		{
			if (count[k][0] / (double) nRow > cutoff)
				nc++;
		}

		int[] exemplars = new int[nc];
		nc = 0;
		for (int k = 0; k < numClusters; k++)
		{
			if (count[k][0] / (double) nRow > cutoff)
			{
				exemplars[nc] = closestPoints[k];
				nc++;
			}
		}
		return exemplars;
	}

	private void reassign(int nCluster, double[][] data, double[][] center, double[][] count, double[][] mean,
			double[][] min, double[][] max, double[][] ssq, int[] closestPoints, double[] closestDistances)
	{

		/* initialize cluster statistics */

		for (int k = 0; k <= nCluster; k++)
		{
			closestPoints[k] = -1;
			closestDistances[k] = Double.POSITIVE_INFINITY;
			for (int j = 0; j < nVar; j++)
			{
				center[k][j] = mean[k][j];
				mean[k][j] = 0;
				count[k][j] = 0;
				ssq[k][j] = 0;
				min[k][j] = Double.POSITIVE_INFINITY;
				max[k][j] = Double.NEGATIVE_INFINITY;
			}
		}

		/* assign each point to closest cluster and update statistics */

		for (int i = 0; i < nRow; i++)
		{

			/* find closest cluster */
			double dmin = Double.POSITIVE_INFINITY;
			int kmin = -1;
			for (int k = 0; k <= nCluster; k++)
			{
				double dd = distance(data[i], center[k]);
				if (dd < dmin)
				{
					dmin = dd;
					kmin = k;
					if (dmin < closestDistances[k])
					{
						closestDistances[k] = dmin;
						closestPoints[k] = i;
					}
				}
			}
			if (kmin < 0)
			{
				members[i] = -1;
			} else
			{
				members[i] = kmin;
			}

			/* update cluster statistics */

			for (int j = 0; j < nVar; j++)
			{
				if (!Double.isNaN(data[i][j]))
				{
					count[kmin][j]++;
					double xn = count[kmin][j];
					double xa = data[i][j];
					mean[kmin][j] += (xa - mean[kmin][j]) / xn;
					if (xn > 1.)
						ssq[kmin][j] += xn * (xa - mean[kmin][j]) * (xa - mean[kmin][j]) / (xn - 1.);
					if (min[kmin][j] > xa)
						min[kmin][j] = xa;
					if (max[kmin][j] < xa)
						max[kmin][j] = xa;
				}
			}
		}
	}

	private double distance(double[] a, double[] b)
	{
		double dist = 0;
		for (int i = 0; i < a.length; i++)
		{
			dist += (a[i] - b[i]) * (a[i] - b[i]);
		}
		return dist;
	}
}