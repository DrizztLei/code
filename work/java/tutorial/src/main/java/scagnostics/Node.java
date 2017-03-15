package scagnostics;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

class Node {
    protected int x, y; // coordinate X,Y
    protected int count; // number of points aggregated at this node
    protected EdgeSc anEdge; // an edge which starts from this node
    protected List<EdgeSc> neighbors = new ArrayList<EdgeSc>(); // nearest Delaunay neighbors list
    protected boolean onMST;
    protected boolean onHull = false;
    protected boolean isVisited = false;
    protected int mstDegree;
    protected int pointID;
    protected int nodeID;

    protected Node(int x, int y, int count, int pointID) {
        this.x = x;
        this.y = y;
        this.count = count;
        anEdge = null;
        // neighbors = new ArrayList();
        this.pointID = pointID;
    }

    public Node() {

    }

    protected double distToNode(double px, double py) {
        double dx = px - x;
        double dy = py - y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    protected void setNeighbor(EdgeSc neighbor) {
        neighbors.add(neighbor);
    }

    protected Iterator getNeighborIterator() {
        return neighbors.iterator();
    }

    protected EdgeSc shortestEdge(boolean mst) {
        EdgeSc emin = null;
        if (neighbors != null) {
            Iterator it = neighbors.iterator();
            //System.out.println("neighbors Size: " + neighbors.size() + " at Node " + this.x + " " + this.y);
            double wmin = Double.MAX_VALUE;
            while (it.hasNext()) {
                EdgeSc e = (EdgeSc) it.next();
                if (mst || !e.otherNode(this).onMST) {
                    double wt = e.weight;
                    //System.out.println("e Weight: " + e.weight);
                    if (wt < wmin) {
                        wmin = wt;
                        emin = e;
                    }
                }
            }
            //System.out.println("Neighbors Not NULL at " + wmin);
        }
        return emin;
    }

    protected int getMSTChildren(double cutoff, double[] maxLength, boolean flag) {
        // System.out.println("call the mst");
        int count = 0;
        if (isVisited) {
            return count;
        }

        isVisited = true;
        Iterator it = neighbors.iterator();
        while (it.hasNext()) {
            EdgeSc e = (EdgeSc) it.next();
            if (e.onMST) {
                if (e.weight < cutoff) {
                    if (!e.otherNode(this).isVisited) {
                        count += e.otherNode(this).getMSTChildren(cutoff, maxLength, flag);
                        double el = e.weight;
                        if (el > maxLength[0]) {
                            maxLength[0] = el;
                            if (flag) {
                                EdgeSc.localLeftStartX = e.p1.x;
                                EdgeSc.localLeftStartY = e.p1.y;

                                EdgeSc.localLeftEndX = e.p2.x;
                                EdgeSc.localLeftEndY = e.p2.y;

                                EdgeSc.w1 = e.weight;
                            } else {
                                EdgeSc.localRightStartX = e.p1.x;
                                EdgeSc.localRightStartY = e.p1.y;

                                EdgeSc.localRightEndX = e.p2.x;
                                EdgeSc.localRightEndY = e.p2.y;

                                EdgeSc.w2 = e.weight;
                            }
                        }
                    }
                }
            }
        }
        count += this.count; // add count for this node
        // System.out.println("RETURNING " );
        return count;
    }
}