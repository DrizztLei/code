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

public class Binner {
    private int maxBins;

    public Binner(int maxBins) {
        this.maxBins = maxBins;
    }

    public final BinnedData binHex(double[] x, double[] y, int nBins) {

        int n = x.length;

        // scaling constants

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

        for (int i = 0; i < n; i++) {
            if (Double.isNaN(x[i])) continue;
            if (Double.isNaN(y[i])) continue;
            double sx = c1 * x[i];
            double sy = c2 * y[i];
            int i1 = (int) (sy + .5);
            int j1 = (int) (sx + .5);
            double dy = sy - (double) i1;
            double dx = sx - (double) j1;
            double dist1 = dx * dx + 3. * dy * dy;
            int m;
            if (dist1 < con1) {
                m = i1 * iinc + j1;
            } else if (dist1 > con2) {
                m = (int) sy * iinc + (int) sx + jinc;
            } else {
                int i2 = (int) sy;
                int j2 = (int) sx;
                dy = sy - (double) i2 - .5;
                dx = sx - (double) j2 - .5;
                double dist2 = dx * dx + 3. * dy * dy;
                if (dist1 <= dist2) {
                    m = i1 * iinc + j1;
                } else {
                    m = i2 * iinc + j2 + jinc;
                }
            }
            count[m]++;
            xbin[m] += (x[i] - xbin[m]) / count[m];
            ybin[m] += (y[i] - ybin[m]) / count[m];
        }

        nBin = deleteEmptyBins(count, xbin, ybin);
        if (nBin > maxBins) {
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

    private int deleteEmptyBins(int[] count, double[] xbin, double[] ybin) {

        int k = 0;
        for (int i = 0; i < count.length; i++) {
            if (count[i] > 0) {
                count[k] = count[i];
                xbin[k] = xbin[i];
                ybin[k] = ybin[i];
                k++;
            }
        }
        return k;
    }
}