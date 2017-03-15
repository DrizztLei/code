package scagnostics;

import java.util.List;

public class Triangle
{
	protected EdgeSc anEdge; // an edge of this triangle
	protected double c_cx; // center of circle: X
	protected double c_cy; // center of circle: Y
	protected double c_r; // radius of circle
	protected boolean onComplex = true;

	protected Triangle(EdgeSc e1, EdgeSc e2, EdgeSc e3)
	{
		update(e1, e2, e3);
	}

	protected Triangle(List<EdgeSc> edges, EdgeSc e1, EdgeSc e2, EdgeSc e3)
	{
		update(e1, e2, e3);
		edges_add(edges, e1);
		edges_add(edges, e2);
		edges_add(edges, e3);
	}

	protected boolean isEqual(Triangle t)
	{
		return (anEdge.isEqual(t.anEdge)) && (anEdge.nextE.isEqual(t.anEdge.nextE))
				&& (anEdge.nextE.nextE.isEqual(t.anEdge.nextE.nextE));
		// (anEdge.isEqual(t.anEdge)||anEdge.isEqual(t.anEdge.nextE)||anEdge.isEqual(t.anEdge.nextE))
		// &&
		// (anEdge.nextE.isEqual(t.anEdge.nextE)||anEdge.nextE.isEqual(t.anEdge)||anEdge.nextE.isEqual(t.anEdge.nextE.nextE))
		// &&
		// (anEdge.nextE.nextE.isEqual(t.anEdge.nextE.nextE)||anEdge.nextE.nextE.isEqual(t.anEdge)||anEdge.nextE.nextE.isEqual(t.anEdge.nextE));
	}

	protected void edges_add(List<EdgeSc> edges, EdgeSc e1)
	{
		if (edges.isEmpty())
		{
			edges.add(e1);
			return;
		}
		for (int i = 0; i < edges.size(); ++i)
		{
			if (edges.get(i).isEqual(e1))
				return;
		}
		edges.add(e1);
	}

	protected void update(EdgeSc e1, EdgeSc e2, EdgeSc e3)
	{
		onComplex = true;
		anEdge = e1;
		e1.nextE = e2;
		e2.nextE = e3;
		e3.nextE = e1;
		e1.inT = this;
		e2.inT = this;
		e3.inT = this;
		findCircle();
	}

	protected boolean inCircle(Node nd)
	{
		return nd.distToNode(c_cx, c_cy) < c_r;
	}

	protected void removeEdges(List<EdgeSc> edges)
	{
		edges.remove(anEdge);
		edges.remove(anEdge.nextE);
		edges.remove(anEdge.nextE.nextE);
	}

	protected void findCircle()
	{
		double x1 = (double) anEdge.p1.x;
		double y1 = (double) anEdge.p1.y;
		double x2 = (double) anEdge.p2.x;
		double y2 = (double) anEdge.p2.y;
		double x3 = (double) anEdge.nextE.p2.x;
		double y3 = (double) anEdge.nextE.p2.y;
		double a = (y2 - y3) * (x2 - x1) - (y2 - y1) * (x2 - x3);
		double a1 = (x1 + x2) * (x2 - x1) + (y2 - y1) * (y1 + y2);
		double a2 = (x2 + x3) * (x2 - x3) + (y2 - y3) * (y2 + y3);
		c_cx = (a1 * (y2 - y3) - a2 * (y2 - y1)) / a / 2;
		c_cy = (a2 * (x2 - x1) - a1 * (x2 - x3)) / a / 2;
		c_r = anEdge.p1.distToNode(c_cx, c_cy);
	}
}