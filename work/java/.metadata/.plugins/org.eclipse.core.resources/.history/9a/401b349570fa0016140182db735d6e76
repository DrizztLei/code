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

import java.util.*;


public class Edge {
    protected Node p1, p2;           // start and end point of the edge
    protected Edge invE = null;     // inverse edge (p2->p1)
    protected Edge nextE = null;    // next edge in the triangle in counterclockwise
    protected Edge nextH = null;    // convex hull link
    protected Triangle inT = null;   // triangle containing this edge
    protected double a, b, c;          // line equation parameters. aX+bY+c=0
    protected double weight;

    protected boolean onHull = false;
    protected boolean onMST = false;
    protected boolean onShape = false;
    protected boolean onOutlier = false;

    protected Edge(Node p1, Node p2) {
        update(p1, p2);
    }

    protected void update(Node p1, Node p2) {
        this.p1 = p1;
        this.p2 = p2;
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
        weight = Math.sqrt(a * a + b * b);
        asIndex();
    }

    protected Edge makeSymm() {
        Edge e = new Edge(p2, p1);
        linkSymm(e);
        return e;
    }

    protected void linkSymm(Edge e) {
        this.invE = e;
        if (e != null) e.invE = this;
    }

    protected int onSide(Node nd) {
        double s = a * nd.x + b * nd.y + c;
        if (s > 0.0) return 1;
        if (s < 0.0) return -1;
        return 0;
    }

    protected void asIndex() {
        p1.anEdge = this;
    }

    protected Edge mostLeft() {
        Edge ee, e = this;
        while ((ee = e.nextE.nextE.invE) != null && ee != this) e = ee;
        return e.nextE.nextE;
    }

    protected Edge mostRight() {
        Edge ee, e = this;
        while (e.invE != null && (ee = e.invE.nextE) != this) e = ee;
        return e;
    }

    protected void deleteSimplex() {
        onShape = false;
        inT.onComplex = false;
        if (invE != null) {
            invE.onShape = false;
            invE.inT.onComplex = false;
        }
    }

    protected boolean isEqual(Edge e) {
        return (e.p1.x == this.p1.x) && (e.p2.x == this.p2.x) && (e.p1.y == this.p1.y) && (e.p2.y == this.p2.y);
    }

    protected boolean isEquivalent(Edge e) {
        return ((e.p1.x == this.p1.x) && (e.p2.x == this.p2.x) && (e.p1.y == this.p1.y) && (e.p2.y == this.p2.y)) ||
                ((e.p1.x == this.p2.x) && (e.p1.y == this.p2.y) && (e.p2.x == this.p1.x) && (e.p2.y == this.p1.y));
    }

    protected Node otherNode(Node n) {
        if (n.equals(p1))
            return p2;
        else
            return p1;
    }

    protected boolean isNewEdge(Node n) {
        Iterator it = n.getNeighborIterator();
        while (it.hasNext()) {
            Edge e2 = (Edge) it.next();
            if (e2.isEquivalent(this))
                return false;
        }
        return true;
    }

    protected int getRunts(double[] maxLength) {
        double cutoff = weight;
        double[] maxLength1 = new double[1];
        double[] maxLength2 = new double[1];
        int count1 = p1.getMSTChildren(cutoff, maxLength1);
        int count2 = p2.getMSTChildren(cutoff, maxLength2);
        if (count1 < count2) {
            maxLength[0] = maxLength1[0];
            return count1;
        } else if (count1 == count2) {        // take more tightly clustered child
            if (maxLength1[0] < maxLength2[0])
                maxLength[0] = maxLength1[0];
            else
                maxLength[0] = maxLength2[0];
            return count1;
        } else {
            maxLength[0] = maxLength2[0];
            return count2;
        }
    }
}
