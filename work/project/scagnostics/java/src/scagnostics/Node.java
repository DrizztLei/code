package scagnostics;

import java.util.*;

class Node
{
	protected int x, y; // coordinate X,Y
	protected int count; // number of points aggregated at this node
	protected Edge anEdge; // an edge which starts from this node
	protected List<Edge> neighbors = new ArrayList<Edge>(); // nearest Delaunay neighbors list
	protected boolean onMST;
	protected boolean onHull = false;
	protected boolean isVisited = false;
	protected int mstDegree;
	protected int pointID;
	protected int nodeID;

	protected Node(int x, int y, int count, int pointID)
	{
		this.x = x;
		this.y = y;
		this.count = count;
		anEdge = null;
		// neighbors = new ArrayList();
		this.pointID = pointID;
	}
	
	public Node()
	{
		
	}

	protected double distToNode(double px, double py)
	{
		double dx = px - x;
		double dy = py - y;
		return Math.sqrt(dx * dx + dy * dy);
	}

	protected void setNeighbor(Edge neighbor)
	{
		neighbors.add(neighbor);
	}

	protected Iterator getNeighborIterator()
	{
		return neighbors.iterator();
	}

	protected Edge shortestEdge(boolean mst)
	{
		Edge emin = null;
		if (neighbors != null)
		{
			Iterator it = neighbors.iterator();
			double wmin = Double.MAX_VALUE;
			while (it.hasNext())
			{
				Edge e = (Edge) it.next();
				if (mst || !e.otherNode(this).onMST)
				{
					double wt = e.weight;
					if (wt < wmin)
					{
						wmin = wt;
						emin = e;
					}
				}
			}
		}
		return emin;
	}

	protected int getMSTChildren(double cutoff, double[] maxLength, boolean flag)
	{
		// System.out.println("call the mst");
		int count = 0;
		if (isVisited)
		{
			return count;			
		}
		
		isVisited = true;
		Iterator it = neighbors.iterator();
		while (it.hasNext())
		{
			Edge e = (Edge) it.next();
			if (e.onMST)
			{
				if (e.weight < cutoff)
				{
					if (!e.otherNode(this).isVisited)
					{
						count += e.otherNode(this).getMSTChildren(cutoff, maxLength, flag);
						double el = e.weight;
						if (el > maxLength[0])
						{
							maxLength[0] = el;
							if(flag)
							{
								Edge.localLeftStartX = e.p1.x;
								Edge.localLeftStartY = e.p1.y;
								
								// Edge.leftStartX = e.p1.x;
								// Edge.leftStartY = e.p1.y;
								
								// Edge.leftEndX = e.p2.x;
								// Edge.leftEndY = e.p2.y;
								
								Edge.localLeftEndX = e.p2.x;
								Edge.localLeftEndY = e.p2.y;
								
								Edge.w1 = e.weight;
							}
							else
							{
								// Edge.rightStartX = e.p1.x;
								// Edge.rightStartY = e.p1.y;
								
								// Edge.rightEndX = e.p2.x;
								// Edge.rightEndY = e.p2.y;
								
								Edge.localRightStartX = e.p1.x;
								Edge.localRightStartY = e.p1.y;
								
								Edge.localRightEndX = e.p2.x;
								Edge.localRightEndY = e.p2.y;
								
								Edge.w2 = e.weight;
							}
							/*
							edge.weight = e.weight;
							
							edge.p1  = new Node();
							edge.p1.x = e.p1.x;
							edge.p1.y = e.p1.y;
							
							edge.p2 = new Node();
							edge.p2.x = e.p2.x;
							edge.p2.y = e.p2.y;
							*/
							// edge.p2 = e.p2;
							
							// System.out.println(edge.weight);
							// System.out.println("update done");
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