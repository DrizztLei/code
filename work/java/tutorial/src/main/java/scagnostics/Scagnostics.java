package scagnostics;

import com.vividsolutions.jts.geom.Coordinate;
import org.geotools.graph.structure.Edge;
import org.geotools.graph.structure.Graph;
import org.geotools.graph.structure.basic.BasicGraph;
import org.geotools.graph.util.delaunay.DelaunayEdge;
import org.geotools.graph.util.delaunay.DelaunayNode;
import org.geotools.graph.util.delaunay.DelaunayTriangulator;
import org.geotools.graph.util.delaunay.GraphViewer;

import javax.swing.*;
import java.io.*;
import java.util.*;

public class Scagnostics
{
	public static final String outAlphaHullFileName = "./alphaHull.csv";
	public static final String outConvexHullFileName = "./convexHull.csv";
	public static final String outClumpyFileName = "./clumpy.csv";
	public static final String outOutlyingFileName = "./outlying.csv";
	public static final String outSkewed = "./skewed.csv";
	public static final String outMST = "./MST.csv";
	public static final String outDT = "./DT.csv";
	public static final String outDiameter = "./diameter.csv";
	public static final String outStriated = "./striated.csv";
	public static FileOutputStream out;
	StringBuffer sb;

	public static EdgeSc maxEdge = new EdgeSc();
	public static EdgeSc maxRunt = new EdgeSc();

	// public static final String

	public static File convexHullFile, alphaHullFile, clumpyFile, outlyingFile, skewedFile, MSTFile, DTFile,
			diameterFile, striatedFile;

	static
	{
		alphaHullFile = new File(outAlphaHullFileName);
		convexHullFile = new File(outConvexHullFileName);
		clumpyFile = new File(outClumpyFileName);
		outlyingFile = new File(outOutlyingFileName);
		skewedFile = new File(outSkewed);
		MSTFile = new File(outMST);
		DTFile = new File(outDT);
		diameterFile = new File(outDiameter);
		striatedFile = new File(outStriated);
	}

	private BinnedData bdata;

	private List<Node> nodes; // nodes set
	private List<EdgeSc> edges; // edges set
	private List<Triangle> triangles; // triangles set
	private List<EdgeSc> mstEdges; // minimum spanning tree set

	private EdgeSc hullStart; // entering edge of convex hull
	private EdgeSc actE;
	private int totalPeeledCount;
	private int totalCount;

	private double alphaArea = 1, alphaPerimeter = 1, hullArea = 1, hullPerimeter = 1;
	private double totalOriginalMSTLengths;
	private double totalMSTOutlierLengths;
	private double[] sortedOriginalMSTLengths;
	private static int numScagnostics = 9;
	public final static int OUTLYING = 0, SKEWED = 1, CLUMPY = 2, SPARSE = 3, STRIATED = 4, CONVEX = 5, SKINNY = 6,
			STRINGY = 7, MONOTONIC = 8;
	public final static String[] scagnosticsLabels =
	{ "Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic" };
	private int[] px, py, counts;
	private boolean[] isOutlier;
	private double FUZZ = .999;

	public Scagnostics(double[] x, double[] y, int numBins, int maxBins)
	{
		nodes = new ArrayList<Node>();
		nodes_dt = new ArrayList<Node>();
		edges = new ArrayList<EdgeSc>();
		triangles = new ArrayList<Triangle>();
		mstEdges = new ArrayList<EdgeSc>();
		Binner b = new Binner(maxBins);
		bdata = b.binHex(x, y, numBins);
		// System.out.println(Main.asp);
		// System.out.println("LENGTH : " + bdata.y.length);
		for (int i = 0; i < bdata.getYData().length; i++)
		{
			bdata.y[i] = (int) (bdata.y[i] * Main.asp);
			// System.out.println(bdata.x[i] + "\t" + bdata.y[i]);
			// System.out.println(bdata.y[i]);
		}

	}

	protected List<Node> nodes_dt;

	protected void add_DT_Node(int x, int y, int count, int pointID)
	{
		Node add_on = new Node(x, y, count, pointID);
		nodes_dt.add(add_on);
	}

	protected Node search_DT_Node(int x, int y)
	{
		Iterator<Node> it = nodes_dt.iterator();
		while (it.hasNext())
		{
			Node n = (Node) it.next();
			if (n.x == x && n.y == y)
			{
				return n;
			}
		}
		System.err.println("Cannot Find Point at " + x + " " + y);
		return null;
	}

	public double[] compute()
	{
		px = bdata.getXData();
		py = bdata.getYData();
		if (px.length < 3)
		{
			return null;
		}

		int xx = px[0];
		int yy = py[0];
		boolean isXConstant = true;
		boolean isYConstant = true;
		for (int i = 1; i < px.length; i++)
		{
			if (px[i] != xx)
			{
				isXConstant = false;
			}
			if (py[i] != yy)
			{
				isYConstant = false;
			}
		}
		if (isXConstant || isYConstant)
		{
			return null;
		}

		try
		{
			initFindOutlying();
		} catch (FileNotFoundException e1)
		{
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		findOutliers(bdata);

		computeAlphaGraph();

		computeTotalCount();
		computeAlphaArea();
		// computeAlphaPerimeter();
		computeHullArea();
		// computeHullPerimeter();

		double[] result = computeMeasures();

		try
		{
			computeAlphaHullPointOutput(outAlphaHullFileName);
			computeConvexHullPointOutput(outConvexHullFileName);
			computeOutlyingPointOutput(outOutlyingFileName);
			computeMSTOutput(outMST);

			computeDT(outDT);
			computeDiameter(outDiameter);
			computeStriated(outStriated);
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		return result;
	}

	private void initFindOutlying() throws FileNotFoundException
	{
		out = new FileOutputStream(outOutlyingFileName, false);
		sb = new StringBuffer();
	}

	private void computeStriated(String outstriated) throws UnsupportedEncodingException, IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(outstriated, false);
		StringBuffer sb = new StringBuffer();

		Iterator<EdgeSc> it = mstEdges.iterator();
		while (it.hasNext())
		{
			EdgeSc e = (EdgeSc) it.next();
			Node n1 = e.p1;
			Node n2 = e.p2;
			if (n1.mstDegree == 2 && n2.mstDegree == 2)
			{
				EdgeSc e1 = getAdjacentMSTEdge(n1, e);
				EdgeSc e2 = getAdjacentMSTEdge(n2, e);
				if (cosineOfAdjacentEdges(e, e1, n1) < -.7 && cosineOfAdjacentEdges(e, e2, n2) < -.7)
				{
					double valueOne = cosineOfAdjacentEdges(e, e1, n1);
					int x1, x2, x3, y1, y2, y3;
					if (e1.p1.x == n1.x && e1.p1.y == n1.y)
					{
						x1 = e1.p2.x;
						y1 = e1.p2.y;

						x2 = n1.x;
						y2 = n1.y;

						x3 = n2.x;
						y3 = n2.y;
					} else
					{
						x1 = e1.p1.x;
						y1 = e1.p1.y;

						x2 = n1.x;
						y2 = n1.y;

						x3 = n2.x;
						y3 = n2.y;
					}
					sb.append(x1 + "," + y1 + "," + x2 + "," + y2 + "," + x3 + "," + y3 + "," + valueOne + "\n");

					double valueTwo = cosineOfAdjacentEdges(e, e2, n2);
					if (e2.p1.x == n2.x && e2.p1.y == n2.y)
					{
						x1 = e2.p2.x;
						y1 = e2.p2.y;

						x2 = n2.x;
						y2 = n2.y;

						x3 = n1.x;
						y3 = n1.y;
					} else
					{
						x1 = e2.p1.x;
						y1 = e2.p1.y;

						x2 = n2.x;
						y2 = n2.y;

						x3 = n1.x;
						y3 = n1.y;
					}
					sb.append(x1 + "," + y1 + "," + x2 + "," + y2 + "," + x3 + "," + y3 + "," + valueTwo + "\n");
				}

			}
		}

		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeDT(String outdt) throws UnsupportedEncodingException, IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(outdt, false);
		StringBuffer sb = new StringBuffer();

		Iterator<Triangle> iterator = triangles.iterator();

		while (iterator.hasNext())
		{

			Triangle triangle = iterator.next();
			EdgeSc e1 = triangle.anEdge;
			EdgeSc e2 = e1.nextE;
			EdgeSc e3 = e2.nextE;

			EdgeSc[] edgeSet = new EdgeSc[]
			{ e1, e2, e3 };

			for (int i = 0; i < edgeSet.length; i++)
			{
				EdgeSc edge = edgeSet[i];
				Node from = edge.p1;
				Node to = edge.p2;

				int start_x = from.x;
				int start_y = from.y;
				int end_x = to.x;
				int end_y = to.y;

				sb.append(start_x + ",");
				sb.append(start_y + "\n");
				sb.append(end_x + ",");
				sb.append(end_y + "\n");
			}
		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeSkewedOutput(String outskewed) throws UnsupportedEncodingException, IOException
	{

		if (sortedOriginalMSTLengths.length == 0)
		{
			return;
		}
		int n = sortedOriginalMSTLengths.length;

		int n50 = n / 2;
		int n10 = n / 10;
		int n90 = (9 * n) / 10;

		double n10Value = sortedOriginalMSTLengths[n10];
		double n50Value = sortedOriginalMSTLengths[n50];
		double n90Value = sortedOriginalMSTLengths[n90];

		double[] compareArray =
		{ n10Value, n50Value, n90Value };
		int pointToArray = 0;

		FileOutputStream out;
		out = new FileOutputStream(outskewed, false);
		StringBuffer sb = new StringBuffer();

		Iterator<EdgeSc> iterator = mstEdges.iterator();

		while (iterator.hasNext())
		{

			EdgeSc edge = iterator.next();

			double weight = edge.weight;

			if (Double.compare(weight, compareArray[pointToArray]) == 0)
			{
				// System.out.println("get in");
				// System.out.println("compare value : " +
				// compareArray[pointToArray]);

				Node from = edge.p1;
				Node to = edge.p2;

				int start_x = from.x;
				int start_y = from.y;
				int end_x = to.x;
				int end_y = to.y;

				sb.append(start_x + ",");
				sb.append(start_y + "\n");
				sb.append(end_x + ",");
				sb.append(end_y + "\n");
				++pointToArray;

				if (!(pointToArray < compareArray.length))
				{
					break;
				}

				iterator = mstEdges.iterator();

				// System.out.println(compareArray[pointToArray]);
			}
		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeMSTOutput(String outmst) throws UnsupportedEncodingException, IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(outmst, false);
		StringBuffer sb = new StringBuffer();

		Iterator<EdgeSc> iterator = edges.iterator();

		while (iterator.hasNext())
		{

			EdgeSc edge = iterator.next();
			if (edge.onMST)
			{
				Node from = edge.p1;
				Node to = edge.p2;

				int start_x = from.x;
				int start_y = from.y;
				int end_x = to.x;
				int end_y = to.y;

				sb.append(start_x + ",");
				sb.append(start_y + "\n");
				sb.append(end_x + ",");
				sb.append(end_y + "\n");
			}
		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeOutlyingPointOutput(String outoutlyingfilename) throws UnsupportedEncodingException, IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(outoutlyingfilename, false);

		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeConvexHullPointOutput(String convexhullfilename) throws IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(convexhullfilename, false);
		StringBuffer sb = new StringBuffer();

		Iterator<EdgeSc> iterator = edges.iterator();

		while (iterator.hasNext())
		{

			EdgeSc edge = iterator.next();
			if (edge.onHull)
			{
				Node from = edge.p1;
				Node to = edge.p2;

				int start_x = from.x;
				int start_y = from.y;
				int end_x = to.x;
				int end_y = to.y;

				sb.append(start_x + ",");
				sb.append(start_y + "\n");
				sb.append(end_x + ",");
				sb.append(end_y + "\n");
			}
		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeAlphaHullPointOutput(String alphaHullFile) throws IOException
	{

		FileOutputStream out;
		out = new FileOutputStream(alphaHullFile, false);
		StringBuffer sb = new StringBuffer();

		Iterator<EdgeSc> iterator = edges.iterator();

		while (iterator.hasNext())
		{

			EdgeSc edge = iterator.next();
			if (edge.onShape)
			{
				Node from = edge.p1;
				Node to = edge.p2;

				int start_x = from.x;
				int start_y = from.y;
				int end_x = to.x;
				int end_y = to.y;

				sb.append(start_x + ",");
				sb.append(start_y + "\n");
				sb.append(end_x + ",");
				sb.append(end_y + "\n");
			}
		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	public static int getNumScagnostics()
	{
		return scagnosticsLabels.length;
	}

	public static String[] getScagnosticsLabels()
	{
		return scagnosticsLabels;
	}

	public static boolean[] computeScagnosticsExemplars(double[][] pts)
	{
		int nPts = pts.length;
		if (nPts < 2)
			return null;
		Cluster c = new Cluster(0, 0);
		int[] exemp = c.compute(pts);
		boolean[] exemplars = new boolean[nPts];
		for (int i = 0; i < exemp.length; i++)
			exemplars[exemp[i]] = true;
		return exemplars;
	}

	public static boolean[] computeScagnosticsOutliers(double[][] pts)
	{

		// Prim's algorithm

		int nPts = pts.length; // p*(p-1)/2 points representing pairwise
		// scatterplots
		int nVar = pts[0].length; // number of scagnostics (9)
		if (nPts < 2)
			return null;
		int[][] edges = new int[nPts - 1][2];
		int[] list = new int[nPts];
		int[] degrees = new int[nPts];
		double[] cost = new double[nPts];
		double[] lengths = new double[nPts - 1];

		list[0] = 0;
		cost[0] = Double.POSITIVE_INFINITY;
		int cheapest = 0;

		for (int i = 1; i < nPts; i++)
		{
			for (int j = 0; j < nVar; j++)
			{
				double d = pts[i][j] - pts[0][j];
				cost[i] += d * d;
			}
			if (cost[i] < cost[cheapest])
				cheapest = i;
		}
		for (int j = 1; j < nPts; j++)
		{
			int end = list[cheapest];
			int jp = j - 1;
			edges[jp][0] = cheapest;
			edges[jp][1] = end;
			lengths[jp] = cost[cheapest];
			degrees[cheapest]++;
			degrees[end]++;
			cost[cheapest] = Double.POSITIVE_INFINITY;
			end = cheapest;

			for (int i = 1; i < nPts; i++)
			{
				if (cost[i] != Double.POSITIVE_INFINITY)
				{
					double dist = 0.;
					for (int k = 0; k < nVar; k++)
					{
						double d = pts[i][k] - pts[end][k];
						dist += d * d;
					}
					if (dist < cost[i])
					{
						list[i] = end;
						cost[i] = dist;
					}
					if (cost[i] < cost[cheapest])
						cheapest = i;
				}
			}
		}
		double cutoff = findCutoff(lengths);
		boolean[] outliers = new boolean[nPts];
		for (int i = 0; i < nPts; i++)
			outliers[i] = true;
		for (int i = 0; i < nPts - 1; i++)
		{
			if (lengths[i] < cutoff)
			{
				for (int k = 0; k < 2; k++)
				{
					int node = edges[i][k];
					outliers[node] = false;
				}
			}
		}
		return outliers;
	}

	private void clear()
	{
		// System.out.println("before clear : " + nodes.size());
		nodes.clear();
		edges.clear();
		triangles.clear();
		mstEdges.clear();
	}

	private void findOutliers(BinnedData bdata)
	{
		this.counts = bdata.getCounts();
		isOutlier = new boolean[px.length];
		// delaunay_tri(px, py);
		// System.out.println("PxPy Size: " + px.length + " " + py.length);
		computeDT(px, py);
		computeMST();
		// System.out.println("Mst size: " + mstEdges.size());
		sortedOriginalMSTLengths = getSortedMSTEdgeLengths();
		// for (int i = 0; i < sortedOriginalMSTLengths.length; ++i) {
		// System.out.println("Mst edge at " + i + " " +
		// sortedOriginalMSTLengths[i]);
		// }
		double cutoff = computeCutoff(sortedOriginalMSTLengths);
		computeTotalOriginalMSTLengths();
		try
		{
			// System.out.println("Call the out skewed.");
			computeSkewedOutput(outSkewed);
		} catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// System.out.println("Cutoff: " + cutoff);
		boolean foundNewOutliers = computeMSTOutliers(cutoff);
		double[] sortedPeeledMSTLengths;
		while (foundNewOutliers)
		{
			clear();
			// System.out.println("PxPy Size: " + px.length + " " + py.length);
			computeDT(px, py);
			computeMST();
			// System.out.println("Mst size: " + mstEdges.size());
			sortedPeeledMSTLengths = getSortedMSTEdgeLengths();
			cutoff = computeCutoff(sortedPeeledMSTLengths);
			// System.out.println("Cutoff: " + cutoff);
			foundNewOutliers = computeMSTOutliers(cutoff);
		}
	}

	private void computeTotalCount()
	{
		for (int i = 0; i < counts.length; i++)
		{
			totalCount += counts[i];
		}
	}

	private double[] computeMeasures()
	{
		double[] results = new double[numScagnostics];
		// Do not change order of these calls!

		results[OUTLYING] = computeOutlierMeasure();
		try
		{
			results[CLUMPY] = computeClusterMeasure();
		} catch (UnsupportedEncodingException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		results[SKEWED] = computeMSTEdgeLengthSkewnessMeasure();
		results[CONVEX] = computeConvexityMeasure();
		results[SKINNY] = computeSkinnyMeasure();
		results[STRINGY] = computeStringyMeasure();
		results[STRIATED] = computeStriationMeasure();
		results[SPARSE] = computeSparsenessMeasure();
		results[MONOTONIC] = computeMonotonicityMeasure();
		return results;
	}

	private void computeDiameter(String outDiameter) throws UnsupportedEncodingException, IOException
	{
		FileOutputStream out;
		out = new FileOutputStream(outDiameter, false);
		StringBuffer sb = new StringBuffer();

		/*
		 * Iterator<Edge> it = mstEdges.iterator(); while (it.hasNext()) { Edge
		 * edge = it.next();
		 * 
		 * Node from = edge.p1; Node to = edge.p2;
		 * 
		 * int p1MSTDegree = from.mstDegree; int p2MSTDegree = to.mstDegree;
		 * 
		 * if(p1MSTDegree == 2 && p2MSTDegree == 2) { Edge fromAdj =
		 * getAdjacentMSTEdge(from, edge); Edge toAdj = getAdjacentMSTEdge(to,
		 * edge);
		 * 
		 * Edge[] edgeSet = new Edge[]{fromAdj, toAdj, edge}; for(int i = 0; i <
		 * edgeSet.length; i++) { from = edgeSet[i].p1; to = edgeSet[i].p2;
		 * 
		 * int start_x = from.x; int start_y = from.y; int end_x = to.x; int
		 * end_y = to.y;
		 * 
		 * sb.append(start_x + ","); sb.append(start_y + "\n"); sb.append(end_x
		 * + ","); sb.append(end_y + "\n"); } } }
		 */
		Iterator<Node> it = nodes.iterator();
		// System.out.println(nodes.size());
		while (it.hasNext())
		{
			Node node = it.next();
			// if (node.onMST)
			{
				if (node.mstDegree == 1)
				{
					int x = node.x;
					int y = node.y;
					int label = 1;
					sb.append(x + "," + y + "," + label + "\n");
				} else if (node.mstDegree == 2)
				{
					int x = node.x;
					int y = node.y;
					int label = 2;
					sb.append(x + "," + y + "," + label + "\n");
				} else
				{
					int x = node.x;
					int y = node.y;
					int label = 0;
					sb.append(x + "," + y + "," + label + "\n");
				}
			}

		}
		out.write(sb.toString().getBytes("utf-8"));
		out.close();
	}

	private void computeDT(int[] px, int[] py)
	{
		totalPeeledCount = 0;
		Random r = new Random(13579);
		for (int i = 0; i < px.length; i++)
		{
			int x = px[i] + (int) (8 * (r.nextDouble() - .5)); // perturb to
			// prevent
			// singularities
			int y = py[i] + (int) (8 * (r.nextDouble() - .5));
			int count = counts[i];
			if (!isOutlier[i])
			{
				// add_DT_Node(x,y,count,i);
				Node nd_dt = new Node(x, y, count, i);
				nodes_dt.add(nd_dt);
				// System.out.println("Nodes here: " + x + " " + y);
				// insert(x, y, count, i);
				totalPeeledCount += count;
			}
		}
		delaunay_tri(nodes_dt);
		nodes_dt.clear();
		setNeighbors();
		markHull();
	}

	public Node nodes_add(Node nd, boolean flag)
	{
		if (nodes.isEmpty())
		{
			nodes.add(nd);
			// System.out.println("Add Node: " + nd.x + " " + nd.y);
			flag = true;
			return nd;
		}
		for (int i = 0; i < nodes.size(); ++i)
		{
			if (nd.x == nodes.get(i).x && nd.y == nodes.get(i).y)
			{
				flag = false;
				return nodes.get(i);
			}
		}
		nodes.add(nd);
		// System.out.println("Add Node: " + nd.x + " " + nd.y);
		flag = true;
		return nd;
	}

	public void delaunay_tri(List<Node> node_vec)
	{
		List<DelaunayNode> nodes_List_DT = new ArrayList<DelaunayNode>();
		double dtx = 0.1;
		// System.out.println("Node_vec Size: " + node_vec.size());
		double max = 0;
		for (int i = 0; i < node_vec.size(); i++)
		{
			// Coordinate coord = new Coordinate(x_data[i], y_data[i]);
			double tmp_x = node_vec.get(i).x, tmp_y = node_vec.get(i).y;
			Coordinate coord = new Coordinate(tmp_x, tmp_y);
			// System.out.print("x " + tmp_x);
			// System.out.println(" y " + tmp_y);
			max = Math.max(max, Math.abs(tmp_x));
			max = Math.max(max, Math.abs(tmp_y));
			// System.out.print("x " + x_data[i]);
			// System.out.println(" y " + y_data[i]);
			DelaunayNode xyNode = new DelaunayNode();
			xyNode.setCoordinate(coord);
			nodes_List_DT.add(xyNode);
		}
		// System.out.println("max 1 " + max);
		List<Edge> edges_dt = new ArrayList<Edge>();
		// System.out.println("Nodes_List_DT Size: " + nodes_List_DT.size());
		DelaunayEdge edge = new DelaunayEdge(nodes_List_DT.get(0), nodes_List_DT.get(1));
		// System.out.print(nodes.get(0).getCoordinate().x + "," +
		// nodes.get(0).getCoordinate().y + " - " +
		// nodes.get(1).getCoordinate().x + "," +
		// nodes.get(1).getCoordinate().y);
		edges_dt.add(edge);
		BasicGraph basicGraph = new BasicGraph();
		basicGraph.setNodes(nodes_List_DT);
		basicGraph.setEdges(edges_dt);

		DelaunayTriangulator delaunayTriangulator = new DelaunayTriangulator();
		DelaunayNode[] delaunayNodes = new DelaunayNode[nodes_List_DT.size()];
		// System.out.println(nodes.toArray(delaunayNodes));
		delaunayTriangulator.setNodeArray(nodes_List_DT.toArray(delaunayNodes));
		// 构建三角网
		// delaunayTriangulator.getTriangulation();
		Graph graph_dt = delaunayTriangulator.getTriangulation();

		Vector triangle_dt = delaunayTriangulator.getTriangles();
		// System.out.println("Triangles size: " + triangle_dt.size());
		int ixp = 0;
		max *= 2;
		for (int i = 0; i < triangle_dt.size(); i++)
		{
			String x_name = triangle_dt.get(i).toString();
			// System.out.println("triangle_dt pos: " + x_name);
			x_name = x_name.replaceAll("\\(", "");
			x_name = x_name.replaceAll("\\)", "");
			x_name = x_name.replaceAll("\\{", "");
			x_name = x_name.replaceAll("\\}", "");
			String[] source_x_name = x_name.split(",");
			float[] x_p =
			{ Float.valueOf(source_x_name[0]), Float.valueOf(source_x_name[2]), Float.valueOf(source_x_name[4]) };
			float[] y_p =
			{ Float.valueOf(source_x_name[1]), Float.valueOf(source_x_name[3]), Float.valueOf(source_x_name[5]) };

			// System.out.println("x pos: " + x_p[0] + " " + x_p[1] + " " +
			// x_p[2] + " ");
			// System.out.println("y pos: " + y_p[0] + " " + y_p[1] + " " +
			// y_p[2] + " ");

			// if (x_p[0] < 1500 && x_p[0] > -500 && x_p[1] < 1500 && x_p[1] >
			// -500 && x_p[2] < 1500 && x_p[2] > -500
			// && y_p[0] < 3000 && y_p[0] > -40 && y_p[1] < 3000 && y_p[1] > -40
			// && y_p[2] < 3000 && y_p[2] > -40) {
			if (x_p[0] < max && x_p[1] < max && x_p[2] < max && y_p[0] < max && y_p[1] < max && y_p[2] < max
					&& x_p[0] > -max && x_p[1] > -max && x_p[2] > -max && y_p[0] > -max && y_p[1] > -max
					&& y_p[2] > -max)
			{
				boolean flag1 = true, flag2 = true, flag3 = true;
				Node n_cur1 = search_DT_Node((int) x_p[0], (int) y_p[0]);
				Node nd1 = new Node(n_cur1.x, n_cur1.y, n_cur1.count, n_cur1.pointID);
				// nd1 = nodes_add(nd1, flag1);
				if (nodes.isEmpty())
				{
					nodes.add(nd1);
					// System.out.println("Add Node: " + nd.x + " " + nd.y);
				}
				for (int ixx = 0; ixx < nodes.size(); ++ixx)
				{
					if (nd1.x == nodes.get(ixx).x && nd1.y == nodes.get(ixx).y)
					{
						flag1 = false;
						nd1 = nodes.get(ixx);
					}
				}
				if (flag1)
					nodes.add(nd1);

				// System.out.println("Add Node: " + nd.x + " " + nd.y);
				Node n_cur2 = search_DT_Node((int) x_p[1], (int) y_p[1]);
				Node nd2 = new Node(n_cur2.x, n_cur2.y, n_cur2.count, n_cur2.pointID);
				// nd2 = nodes_add(nd2, flag2);
				for (int ixx = 0; ixx < nodes.size(); ++ixx)
				{
					if (nd2.x == nodes.get(ixx).x && nd2.y == nodes.get(ixx).y)
					{
						flag2 = false;
						nd2 = nodes.get(ixx);
					}
				}
				if (flag2)
					nodes.add(nd2);

				Node n_cur3 = search_DT_Node((int) x_p[2], (int) y_p[2]);
				Node nd3 = new Node(n_cur3.x, n_cur3.y, n_cur3.count, n_cur3.pointID);
				// nd3 = nodes_add(nd3, flag3);
				for (int ixx = 0; ixx < nodes.size(); ++ixx)
				{
					if (nd3.x == nodes.get(ixx).x && nd3.y == nodes.get(ixx).y)
					{
						flag3 = false;
						nd3 = nodes.get(ixx);
					}
				}
				if (flag3)
					nodes.add(nd3);

				EdgeSc e1 = new EdgeSc(nd1, nd2);
				EdgeSc e2 = new EdgeSc(nd2, nd3);
				EdgeSc e3 = new EdgeSc(nd3, nd1);
				e1.nextH = e2;
				e2.nextH = e3;
				e3.nextH = e1;

				if (ixp == 0)
				{
					hullStart = e1;
					// e1.invE = e1;
					ixp = 1;
				} else
				{
					// if (flag1) {
					// System.out.println("Expand 1");
					// expandHull(nd1);
					// }
					// if (flag2) {
					// System.out.println("Expand 2");
					// expandHull(nd2);
					// }
					// if (flag3) {
					// System.out.println("Expand 3");
					// expandHull(nd3);
					// }
					// System.out.println("Expand Done");
				}

				// e1.invE = new EdgeSc(nd2, nd1);
				// e2.invE = new EdgeSc(nd3, nd2);
				// e3.invE = new EdgeSc(nd3, nd1);

				// e1.invE = e1;
				// e2.invE = e2;
				// e3.invE = e3;

				// swapTest(e1);
				// swapTest(e2);
				// swapTest(e3);
				triangles.add(new Triangle(edges, e1, e2, e3));

				e1.makeSymm();
				e2.makeSymm();
				e3.makeSymm();
				if (e1.invE.inT == null)
					e1.invE.inT = e1.inT;
				if (e2.invE.inT == null)
					e2.invE.inT = e2.inT;
				if (e3.invE.inT == null)
					e3.invE.inT = e3.inT;
			}

		}
		// System.out.println("Nodes size: " + nodes.size());
	}

	static public void delaunay_tri(int[] x_data, int[] y_data)
	{
		List<DelaunayNode> nodes = new ArrayList<DelaunayNode>();
		double dtx = 0.1;
		for (int i = 0; i < x_data.length; i++)
		{
			// Coordinate coord = new Coordinate(x_data[i], y_data[i]);
			Coordinate coord = new Coordinate(x_data[i] * dtx, y_data[i] * dtx);
			// System.out.print("x " + x_data[i]);
			// System.out.println(" y " + y_data[i]);
			DelaunayNode xyNode = new DelaunayNode();
			xyNode.setCoordinate(coord);
			nodes.add(xyNode);
		}
		List<Edge> edges = new ArrayList<Edge>();
		DelaunayEdge edge = new DelaunayEdge(nodes.get(0), nodes.get(1));
		System.out.print(nodes.get(0).getCoordinate().x + "," + nodes.get(0).getCoordinate().y + " - "
				+ nodes.get(1).getCoordinate().x + "," + nodes.get(1).getCoordinate().y);
		edges.add(edge);
		BasicGraph basicGraph = new BasicGraph();
		basicGraph.setNodes(nodes);
		basicGraph.setEdges(edges);

		DelaunayTriangulator delaunayTriangulator = new DelaunayTriangulator();
		DelaunayNode[] delaunayNodes = new DelaunayNode[nodes.size()];
		System.out.println(nodes.toArray(delaunayNodes));
		delaunayTriangulator.setNodeArray(nodes.toArray(delaunayNodes));
		// 构建三角网
		// delaunayTriangulator.getTriangulation();
		GraphViewer gpViewer = new GraphViewer();
		Graph graph_dt = delaunayTriangulator.getTriangulation();
		Collection coll_dt = graph_dt.getNodes();
		System.out.println("Collection nodes: " + coll_dt.size());
		for (Iterator itLst = coll_dt.iterator(); itLst.hasNext();)
		{
			System.out.println(itLst.next());
		}

		gpViewer.setGraph(graph_dt);

		Vector triangle_dt = delaunayTriangulator.getTriangles();
		System.out.println("Triangles: " + triangle_dt.size());
		for (int i = 0; i < triangle_dt.size(); i++)
		{
			System.out.println(triangle_dt.get(i));
		}
		// DelaunayNode[] node_dt = delaunayTriangulator.getNodeArray();
		// System.out.println("Nodes : " + node_dt.length);
		// for (int i = 0; i < node_dt.length; i++) {
		// System.out.println(node_dt[i]);
		// }

		gpViewer.setSize(1000, 1000);
		gpViewer.setVisible(true);
		JFrame jFrame = new JFrame();
		jFrame.add(gpViewer);
		// jFrame.add(new JButton("dd"));
		jFrame.setSize(1000, 1000);
		jFrame.setVisible(true);
	}

	private double computeStringyMeasure()
	{
		int count1 = 0;
		int count2 = 0;
		Iterator<Node> it = nodes.iterator();
		// System.out.println("compute nodes size : " + nodes.size());
		while (it.hasNext())
		{
			Node n = (Node) it.next();
			if (n.mstDegree == 1)
			{
				count1++;
			}

			if (n.mstDegree == 2)
			{
				count2++;
			}

		}
		// System.out.println("COUNT");
		// System.out.println(count1);
		// System.out.println(count2);
		double result = (double) count2 / (double) (nodes.size() - count1);
		return result * result * result;
	}

	private void computeMST()
	{
		if (nodes.size() > 1)
		{
			List<Node> mstNodes = new ArrayList<Node>();
			Node mstNode = (Node) nodes.get(0);
			updateMSTNodes(mstNode, mstNodes);
			int count = 1;
			while (count < nodes.size())
			{
				EdgeSc addEdge = null;
				double wmin = Double.MAX_VALUE;
				Node nmin = null;
				Iterator<Node> mstIterator = mstNodes.iterator();
				// System.out.println("MstNodes Size: " + mstNodes.size());
				while (mstIterator.hasNext())
				{
					mstNode = (Node) mstIterator.next();
					// System.out.println("MstNodes Here: " + mstNode.x + " " +
					// mstNode.y);
					EdgeSc candidateEdge = mstNode.shortestEdge(false);
					if (candidateEdge != null)
					{
						double wt = candidateEdge.weight;
						// System.out.println("CandidateEdge Weight: " + wt + "
						// ");
						if (wt < wmin)
						{
							wmin = wt;
							nmin = mstNode;
							addEdge = candidateEdge;
						}
					}
				}
				if (addEdge != null)
				{
					Node addNode = addEdge.otherNode(nmin);
					updateMSTNodes(addNode, mstNodes);
					updateMSTEdges(addEdge, mstEdges);
					// System.out.println("Add mstNodes: " + addNode.x + " " +
					// addNode.y);
				}
				count++;
			}
		}
	}

	private static double findCutoff(double[] distances)
	{
		int[] index = Sorts.indexedDoubleArraySort(distances, 0, 0);
		int n50 = distances.length / 2;
		int n25 = n50 / 2;
		int n75 = n50 + n50 / 2;
		return distances[index[n75]] + 1.5 * (distances[index[n75]] - distances[index[n25]]);
	}

	private boolean computeMSTOutliers(double omega)
	{
		boolean found = false;
		Iterator<Node> it = nodes.iterator();

		while (it.hasNext())
		{
			Node n = (Node) it.next();
			Iterator<EdgeSc> ie = n.neighbors.iterator();
			boolean delete = true;
			while (ie.hasNext())
			{
				EdgeSc e = (EdgeSc) ie.next();
				if (e.onMST && e.weight < omega)
					delete = false;
				// else
				// System.out.print("DELETE! & Weight: " + e.weight);
			}
			if (delete)
			{
				ie = n.neighbors.iterator();
				double sumlength = 0;
				while (ie.hasNext())
				{
					EdgeSc e = (EdgeSc) ie.next();
					if (e.onMST && !e.onOutlier)
					{
						sumlength += e.weight;
						e.onOutlier = true;
						Node from = e.p1;
						Node to = e.p2;
						int x1 = from.x;
						int y1 = from.y;

						int x2 = to.x;
						int y2 = to.y;

						// System.out.print("Outlier: " + e.p1.x + " " + e.p1.y
						// + " to " + e.p2.x + " " + e.p2.y);
						// System.out.print(" Length: " + Math.sqrt(Math.pow((x2
						// - x1), 2) + Math.pow((y2 - y1), 2)));
						// System.out.println(" Length: " + e.weight);

						sb.append(x1 + "," + y1 + "\n");
						sb.append(x2 + "," + y2 + "\n");
					}
				}
				totalMSTOutlierLengths += sumlength;
				isOutlier[n.pointID] = true;
				// System.out.println("Is Outlier: " + n.x + " " + n.y);
				found = true;
			}
		}
		return found;
	}

	private double computeCutoff(double[] lengths)
	{
		if (lengths.length == 0)
			return 0;
		int n50 = lengths.length / 2;
		int n25 = n50 / 2;
		int n75 = n50 + n25;
		return lengths[n75] + 1.5 * (lengths[n75] - lengths[n25]);
	}

	private double computeAlphaValue()
	{
		int length = sortedOriginalMSTLengths.length;
		if (length == 0)
			return 100.;
		int n90 = (9 * length) / 10;
		double alpha = sortedOriginalMSTLengths[n90];
		return Math.min(alpha, 100.);
	}

	private double computeMSTEdgeLengthSkewnessMeasure()
	{
		if (sortedOriginalMSTLengths.length == 0)
			return 0;
		int n = sortedOriginalMSTLengths.length;
		int n50 = n / 2;
		int n10 = n / 10;
		int n90 = (9 * n) / 10;
		// System.out.println("Skew Num Pos: " + n10 + " " + n50 + " " + n90);
		// System.out.println("Skew Edge Num Here: " + mstEdges.size());
		double skewness = (sortedOriginalMSTLengths[n90] - sortedOriginalMSTLengths[n50])
				/ (sortedOriginalMSTLengths[n90] - sortedOriginalMSTLengths[n10]);
		double t = (double) totalCount / 500;
		double correction = .7 + .3 / (1 + t * t);
		return 1 - correction * (1 - skewness);
	}

	private void updateMSTEdges(EdgeSc addEdge, List<EdgeSc> mstEdges)
	{
		mstEdges.add(addEdge);
		addEdge.onMST = true;
		addEdge.p1.mstDegree++;
		addEdge.p2.mstDegree++;
	}

	private void updateMSTNodes(Node addNode, List<Node> mstNodes)
	{
		mstNodes.add(addNode);
		addNode.onMST = true;
	}

	private double[] getSortedMSTEdgeLengths()
	{
		double[] lengths = computeEdgeLengths(mstEdges.iterator(), mstEdges.size());

		Sorts.doubleArraySort(lengths, 0, 0);

		return lengths;
	}

	private void computeTotalOriginalMSTLengths()
	{
		for (int i = 0; i < sortedOriginalMSTLengths.length; i++)
		{
			totalOriginalMSTLengths += sortedOriginalMSTLengths[i];
		}
	}

	private double computeOutlierMeasure()
	{
		return totalMSTOutlierLengths / totalOriginalMSTLengths;
	}

	private double[] computeEdgeLengths(Iterator<EdgeSc> graph, int n)
	{
		double[] lengths = new double[n];
		int i = 0;
		while (graph.hasNext())
		{
			EdgeSc e = (EdgeSc) graph.next();
			lengths[i] = e.weight;
			// System.out.println("Weight at " + i + " " + e.weight);
			i++;
		}
		return lengths;
	}

	private boolean pointsInCircle(Node n, double xc, double yc, double radius)
	{
		double r = FUZZ * radius;
		Iterator<?> i = n.neighbors.iterator();
		while (i.hasNext())
		{
			EdgeSc e = (EdgeSc) i.next();
			Node no = e.otherNode(n);
			double dist = no.distToNode(xc, yc);
			if (dist < r)
				return true;
		}
		return false;
	}

	private void computeAlphaGraph()
	{
		// requires initializing SEdge.onShape = false

		boolean deleted;
		double alpha = computeAlphaValue();
		do
		{
			Iterator<EdgeSc> i = edges.iterator();
			deleted = false;
			while (i.hasNext())
			{
				EdgeSc e = (EdgeSc) i.next();
				if (e.inT.onComplex)
				{
					if (alpha < e.weight / 2)
					{
						e.inT.onComplex = false;
						deleted = true;
					} else
					{
						// if (e.invE.inT == null)
						// e.invE = null;
						if (e.invE != null)
						{
							if (e.invE.inT.onComplex)
								continue;
						}
						if (!edgeIsExposed(alpha, e))
						{
							e.inT.onComplex = false;
							deleted = true;
						}
					}
				}
			}
		} while (deleted);
		// markShape(); //modified by zeyu @ 05/03
	}

	private void markShape()
	{
		Iterator<EdgeSc> i = edges.iterator();

		while (i.hasNext())
		{
			EdgeSc e = (EdgeSc) i.next();
			e.onShape = false;
			// System.out.print("E (" + e.p1.x + "," + e.p1.y + ")->(" + e.p2.x
			// + "," + e.p2.y + ") ; ");
			if (e.inT.onComplex)
			{
				// System.out.println("Set");
				if (e.invE == null)
				{
					e.onShape = true;
					// System.out.println("Set TRUE");
					// System.out.println("invE NULL");

				} else if (!e.invE.inT.onComplex)
				{
					e.onShape = true;
					// System.out.println("Set TRUE");
					// System.out.println("Set True invE (" + e.invE.p1.x + ","
					// + e.invE.p1.y + ")->(" + e.invE.p2.x + "," + e.invE.p2.y
					// + ")");

				} /*
					 * else { System.out.println("Set False invE (" +
					 * e.invE.p1.x + "," + e.invE.p1.y + ")->(" + e.invE.p2.x +
					 * "," + e.invE.p2.y + ")"); } } else { if (e.invE == null)
					 * { System.out.println("invE NULL !On Complex "); } else {
					 * System.out.println("!On Complex invE (" + e.invE.p1.x +
					 * "," + e.invE.p1.y + ")->(" + e.invE.p2.x + "," +
					 * e.invE.p2.y + ")"); }
					 */
			}
		}
	}

	private boolean edgeIsExposed(double alpha, EdgeSc e)
	{
		double x1 = e.p1.x;
		double x2 = e.p2.x;
		double y1 = e.p1.y;
		double y2 = e.p2.y;
		double xe = (x1 + x2) / 2;
		double ye = (y1 + y2) / 2;
		double d = Math.sqrt(alpha * alpha - e.weight * e.weight / 4);
		double xt = d * (y2 - y1) / e.weight;
		double yt = d * (x2 - x1) / e.weight;
		double xc1 = xe + xt;
		double yc1 = ye - yt;
		double xc2 = xe - xt;
		double yc2 = ye + yt;
		boolean pointsInCircle1 = pointsInCircle(e.p1, xc1, yc1, alpha) || pointsInCircle(e.p2, xc1, yc1, alpha);
		boolean pointsInCircle2 = pointsInCircle(e.p1, xc2, yc2, alpha) || pointsInCircle(e.p2, xc2, yc2, alpha);
		return !(pointsInCircle1 && pointsInCircle2);
	}

	private double computeClusterMeasure() throws UnsupportedEncodingException, IOException
	{

		Iterator<EdgeSc> it = mstEdges.iterator();
		double[] maxLength = new double[1];
		double maxValue = 0;

		Scagnostics.maxRunt.p1 = new Node();
		Scagnostics.maxRunt.p2 = new Node();

		while (it.hasNext())
		{
			EdgeSc e = (EdgeSc) it.next();
			clearVisits();
			e.onMST = false; // break MST at this edge
			int runts = e.getRunts(maxLength);
			e.onMST = true; // restore this edge to MST
			if (maxLength[0] > 0)
			{
				double value = runts * (1 - maxLength[0] / e.weight);

				if (value > maxValue)
				{
					int leftDeltaX = EdgeSc.localLeftStartX - EdgeSc.localLeftEndX;
					int leftDeltaY = EdgeSc.localLeftStartY - EdgeSc.localLeftEndY;

					int rightDeltaX = EdgeSc.localRightStartX - EdgeSc.localRightEndX;
					int rightDeltaY = EdgeSc.localRightStartY - EdgeSc.localRightEndY;

					double length_1 = Math.sqrt(Math.pow(leftDeltaX, 2) + Math.pow(leftDeltaY, 2));
					double length_2 = Math.sqrt(Math.pow(rightDeltaX, 2) + Math.pow(rightDeltaY, 2));

					// System.out.println("LENGTH 1 " + length_1);
					// System.out.println("LENGTH 2 " + length_2);
					// System.out.println("max length: " + maxLength[0]);
					// System.out.println("e weight :" + e.weight);
					// System.out.println("value :" + value);
					// System.out.println("Res :" + 2 * value /
					// totalPeeledCount);
					if (Double.compare(length_1, maxLength[0]) == 0)
					{
						EdgeSc.leftStartX = EdgeSc.localLeftStartX;
						EdgeSc.leftStartY = EdgeSc.localLeftStartY;

						EdgeSc.leftEndX = EdgeSc.localLeftEndX;
						EdgeSc.leftEndY = EdgeSc.localLeftEndY;

						Scagnostics.maxRunt.p1.x = EdgeSc.leftStartX;
						Scagnostics.maxRunt.p1.y = EdgeSc.leftStartY;
						Scagnostics.maxRunt.p2.x = EdgeSc.leftEndX;
						Scagnostics.maxRunt.p2.y = EdgeSc.leftEndY;

						// System.out.println("LEFT Start "+Edge.leftStartX+"
						// "+Edge.leftStartY+" END "+Edge.leftEndX+"
						// "+Edge.leftEndY+" w1 "+Edge.w1);
						// System.out.println("RUNT:LEFT Start
						// "+Scagnostics.maxRunt.p1.x+"
						// "+Scagnostics.maxRunt.p1.y+" END "+maxRunt.p2.x+"
						// "+maxRunt.p2.y);
					} else if (Double.compare(length_2, maxLength[0]) == 0)
					{
						EdgeSc.rightStartX = EdgeSc.localRightStartX;
						EdgeSc.rightStartY = EdgeSc.localRightStartY;

						EdgeSc.rightEndX = EdgeSc.localRightEndX;
						EdgeSc.rightEndY = EdgeSc.localRightEndY;

						Scagnostics.maxRunt.p1.x = EdgeSc.rightStartX;
						Scagnostics.maxRunt.p1.y = EdgeSc.rightStartY;
						Scagnostics.maxRunt.p2.x = EdgeSc.rightEndX;
						Scagnostics.maxRunt.p2.y = EdgeSc.rightEndY;

						// System.out.println("RIGHT Start "+Edge.rightStartX+"
						// "+Edge.rightStartY+" END "+Edge.rightEndX+"
						// "+Edge.rightEndY+" w2 "+Edge.w2);
						// System.out.println("RUNT:RIGHT Start
						// "+Scagnostics.maxRunt.p1.x+"
						// "+Scagnostics.maxRunt.p1.y+" END "+maxRunt.p2.x+"
						// "+maxRunt.p2.y);
					}
					maxValue = value;
					Scagnostics.maxEdge = e;
				}
			}
		}

		FileOutputStream out;
		out = new FileOutputStream(outClumpyFileName, false);
		StringBuffer sb = new StringBuffer();

		if (Scagnostics.maxEdge.p1 == null)// maxEdge == Runt edge, Green;
											// maxRunt == Max edge, Purp
		{
			Scagnostics.maxEdge = new EdgeSc();
			Scagnostics.maxEdge.p1 = new Node();
			Scagnostics.maxEdge.p2 = new Node();

			Scagnostics.maxEdge.p1.x = 0;
			Scagnostics.maxEdge.p1.y = 0;

			Scagnostics.maxEdge.p2.x = 0;
			Scagnostics.maxEdge.p2.y = 0;
			// System.out.println("found the null");
		}
		// System.out.println("RUNT: Start "+Scagnostics.maxRunt.p1.x+"
		// "+Scagnostics.maxRunt.p1.y+" END "+maxRunt.p2.x+" "+maxRunt.p2.y);
		sb.append(Scagnostics.maxEdge.p1.x + ",");
		sb.append(Scagnostics.maxEdge.p1.y + ",");
		sb.append(Scagnostics.maxRunt.p1.x + ",");
		sb.append(Scagnostics.maxRunt.p1.y + "\n");

		sb.append(Scagnostics.maxEdge.p2.x + ",");
		sb.append(Scagnostics.maxEdge.p2.y + ",");
		sb.append(Scagnostics.maxRunt.p2.x + ",");
		sb.append(Scagnostics.maxRunt.p2.y + "\n");

		out.write(sb.toString().getBytes("utf-8"));
		out.close();
		// System.out.println(2 * maxValue / totalPeeledCount);
		// System.out.println(maxValue);
		return 2 * maxValue / totalPeeledCount;
	}

	private void clearVisits()
	{
		Iterator<Node> it = nodes.iterator();
		// System.out.println("SIZE : " + nodes.size());
		while (it.hasNext())
		{
			Node n = (Node) it.next();
			n.isVisited = false;
		}
	}

	private double computeMonotonicityMeasure()
	{
		int n = counts.length;
		double[] ax = new double[n];
		double[] ay = new double[n];
		double[] weights = new double[n];
		for (int i = 0; i < n; i++)
		{
			ax[i] = px[i];
			ay[i] = py[i];
			weights[i] = counts[i];
		}
		double[] rx = Sorts.rank(ax);
		double[] ry = Sorts.rank(ay);
		double s = computePearson(rx, ry, weights);
		return s * s;
	}

	private double computePearson(double[] x, double[] y, double[] weights)
	{
		int n = x.length;
		double xmean = 0;
		double ymean = 0;
		double xx = 0;
		double yy = 0;
		double xy = 0;
		double sumwt = 0;
		for (int i = 0; i < n; i++)
		{
			double wt = weights[i];
			if (wt > 0 && !isOutlier[i])
			{
				sumwt += wt;
				xx += (x[i] - xmean) * wt * (x[i] - xmean);
				yy += (y[i] - ymean) * wt * (y[i] - ymean);
				xy += (x[i] - xmean) * wt * (y[i] - ymean);
				xmean += (x[i] - xmean) * wt / sumwt;
				ymean += (y[i] - ymean) * wt / sumwt;
			}
		}
		xy = xy / Math.sqrt(xx * yy);
		return xy;
	}

	private double computeSparsenessMeasure()
	{
		int n = sortedOriginalMSTLengths.length;
		int n90 = (9 * n) / 10;
		double sparse = Math.min(sortedOriginalMSTLengths[n90] / 1000, 1);
		double t = (double) totalCount / 500;
		double correction = .7 + .3 / (1 + t * t);
		return correction * sparse;
	}

	private double computeStriationMeasure()
	{
		double numEdges = 0;
		Iterator<EdgeSc> it = mstEdges.iterator();
		while (it.hasNext())
		{
			EdgeSc e = (EdgeSc) it.next();
			Node n1 = e.p1;
			Node n2 = e.p2;
			if (n1.mstDegree == 2 && n2.mstDegree == 2)
			{
				EdgeSc e1 = getAdjacentMSTEdge(n1, e);
				EdgeSc e2 = getAdjacentMSTEdge(n2, e);
				if (cosineOfAdjacentEdges(e, e1, n1) < -.7 && cosineOfAdjacentEdges(e, e2, n2) < -.7)
				{
					numEdges++;
				}
			}
		}
		return numEdges / (double) mstEdges.size();
	}

	private EdgeSc getAdjacentMSTEdge(Node n, EdgeSc e)
	{
		Iterator<EdgeSc> nt = n.neighbors.iterator();
		while (nt.hasNext())
		{
			EdgeSc et = (EdgeSc) nt.next();
			if (et.onMST && !e.equals(et))
			{
				return et;
			}
		}
		return null;
	}

	private double cosineOfAdjacentEdges(EdgeSc e1, EdgeSc e2, Node n)
	{
		double v1x = e1.otherNode(n).x - n.x;
		double v1y = e1.otherNode(n).y - n.y;
		double v2x = e2.otherNode(n).x - n.x;
		double v2y = e2.otherNode(n).y - n.y;
		double v1 = Math.sqrt(v1x * v1x + v1y * v1y);
		double v2 = Math.sqrt(v2x * v2x + v2y * v2y);
		v1x = v1x / v1;
		v1y = v1y / v1;
		v2x = v2x / v2;
		v2y = v2y / v2;
		return v1x * v2x + v1y * v2y;
	}

	private double computeConvexityMeasure()
	{
		if (hullArea == 0) // points in general position
			return 1;
		else
		{
			double t = (double) totalCount / 500;
			double correction = .7 + .3 / (1 + t * t);
			double convexity = alphaArea / hullArea;
			return correction * convexity;
		}
	}

	private double computeSkinnyMeasure()
	{
		if (alphaPerimeter > 0)
			return 1 - Math.sqrt(4 * Math.PI * alphaArea) / alphaPerimeter;
		else
			return 1;
	}

	private boolean checkSideEdgComp(EdgeSc e)
	{
		Node p1 = e.p1;
		Node p2 = e.p2;
		int count = 0;
		if (p1.neighbors != null)
		{
			Iterator it_p1 = p1.neighbors.iterator();
			while (it_p1.hasNext())
			{
				EdgeSc e_p1 = (EdgeSc) it_p1.next();
				if (e_p1.inT.onComplex && !e_p1.isEqual(e))
				{
					if (p2.neighbors != null)
					{
						Iterator it_p2 = p2.neighbors.iterator();

						while (it_p2.hasNext())
						{
							EdgeSc e_p2 = (EdgeSc) it_p2.next();
							if (e_p2.inT.onComplex && !e_p2.isEqual(e))
							{
								if (e_p1.inT.isEqual(e_p2.inT))
								{
									++count;
								}
							}
						}

					}
				}
			}
		}
		if (count == 1)
		{
			// System.out.println("Got Shape");
			return true;
		}
		return true;
	}

	private void checkSideTriComp(Triangle t)
	{
		// double sum = 0;
		EdgeSc e1 = t.anEdge;
		EdgeSc e2 = t.anEdge.nextE;
		EdgeSc e3 = t.anEdge.nextE.nextE;
		e1.onShape = true;
		e2.onShape = true;
		e3.onShape = true;
		// if (checkSideEdgComp(e1)) {
		// sum += e1.weight;
		// e1.onShape = true;
		// }
		// if (checkSideEdgComp(e2)) {
		// sum += e2.weight;
		// e2.onShape = true;
		// }
		// if (checkSideEdgComp(e3)) {
		// sum += e3.weight;
		// e3.onShape = true;
		// }
		// return sum;
	}

	private void computeAlphaArea()
	{
		double area = 0.0;
		double sum_alpha_perimeter = 0;
		Iterator<Triangle> tri = triangles.iterator();
		while (tri.hasNext())
		{
			Triangle t = (Triangle) tri.next();
			if (t.onComplex)
			{
				Node p1 = t.anEdge.p1;
				Node p2 = t.anEdge.p2;
				Node p3 = t.anEdge.nextE.p2;
				area += Math.abs(p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p1.y * p2.x);

				// System.out.println("Triangle onC: (" + t.anEdge.p1.x + "," +
				// t.anEdge.p1.y + ")->(" + t.anEdge.p2.x + "," + t.anEdge.p2.y
				// + ") ; " +
				// "(" + t.anEdge.nextE.p1.x + "," + t.anEdge.nextE.p1.y +
				// ")->(" + t.anEdge.nextE.p2.x + "," + t.anEdge.nextE.p2.y + ")
				// ; " +
				// "(" + t.anEdge.nextE.nextE.p1.x + "," +
				// t.anEdge.nextE.nextE.p1.y + ")->(" +
				// t.anEdge.nextE.nextE.p2.x + "," + t.anEdge.nextE.nextE.p2.y +
				// ") ; ");

				// sum_alpha_perimeter += checkSideTriComp(t);
				checkSideTriComp(t);

			}
		}
		alphaArea = area / 2;
		// alphaPerimeter = sum_alpha_perimeter;
		// System.out.println("alphaArea " + alphaArea);
		// System.out.println("alphaPerimeter " + alphaPerimeter);
	}

	private boolean checkSideEdg(EdgeSc e)
	{
		Node p1 = e.p1;
		Node p2 = e.p2;
		int count = 0;
		if (p1.neighbors != null)
		{
			Iterator it_p1 = p1.neighbors.iterator();
			while (it_p1.hasNext())
			{
				EdgeSc e_p1 = (EdgeSc) it_p1.next();
				if (!e_p1.isEqual(e))
				{
					if (p2.neighbors != null)
					{
						Iterator it_p2 = p2.neighbors.iterator();

						while (it_p2.hasNext())
						{
							EdgeSc e_p2 = (EdgeSc) it_p2.next();
							if (!e_p2.isEqual(e))
							{
								if (e_p1.inT.isEqual(e_p2.inT))
								{
									++count;
								}
							}
						}

					}
				}
			}
		}
		System.out.println("Adj Edge Count: " + count);
		if (count == 2)
		{
			// System.out.println("Got Shape");
			return true;
		}
		return false;
	}

	private void checkSideTri(Triangle t)
	{
		// double sum = 0;
		EdgeSc e1 = t.anEdge;
		EdgeSc e2 = t.anEdge.nextE;
		EdgeSc e3 = t.anEdge.nextE.nextE;
		e1.onHull = true;
		e2.onHull = true;
		e3.onHull = true;
		// if (checkSideEdg(e1)) {
		// //sum += e1.weight;
		// e1.onHull = true;
		// }
		// if (checkSideEdg(e2)) {
		// //sum += e2.weight;
		// e2.onHull = true;
		// }
		// if (checkSideEdg(e3)) {
		// //sum += e3.weight;
		// e3.onHull = true;
		// }
		// return sum;
	}

	private void computeHullArea()
	{
		double area = 0.0;
		Iterator<Triangle> tri = triangles.iterator();
		while (tri.hasNext())
		{
			Triangle t = (Triangle) tri.next();
			Node p1 = t.anEdge.p1;
			Node p2 = t.anEdge.p2;
			Node p3 = t.anEdge.nextE.p2;
			area += Math.abs(p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p3.y * p1.x - p1.y * p2.x);
			checkSideTri(t);
		}
		hullArea = area / 2.;
		// System.out.println("hullArea " + hullArea);
	}

	private void computeAlphaPerimeter()
	{
		double sum = 0;
		Iterator<EdgeSc> it = edges.iterator();
		while (it.hasNext())
		{
			EdgeSc e = (EdgeSc) it.next();
			if (e.onShape)
			{
				sum += e.weight;
			}
		}
		alphaPerimeter = sum;
		System.out.println("alphaPerimeter " + alphaPerimeter);
	}

	private void computeHullPerimeter()
	{
		double sum = 0;
		EdgeSc e = hullStart;
		do
		{
			sum += e.p1.distToNode(e.p2.x, e.p2.y);
			e = e.nextH;
		} while (!e.isEqual(hullStart));
		hullPerimeter = sum;
		// System.out.println("hullPerimeter " + hullPerimeter);
	}

	private void setNeighbors()
	{
		Iterator<EdgeSc> it = edges.iterator();
		while (it.hasNext())
		{
			EdgeSc e = (EdgeSc) it.next();
			if (e.isNewEdge(e.p1))
			{
				e.p1.setNeighbor(e);
				// System.out.println("Node " + e.p1.x + " " + e.p1.y + " Get
				// Neighbor Weight: " + e.weight + " With Size: " +
				// e.p1.neighbors.size());
			}
			if (e.isNewEdge(e.p2))
			{
				e.p2.setNeighbor(e);
				// System.out.println("Node " + e.p2.x + " " + e.p2.y + " Get
				// Neighbor Weight: " + e.weight + " With Size: " +
				// e.p2.neighbors.size());
			}
		}
	}

	private void insert(int px, int py, int count, int id)
	{
		int eid;
		Node nd = new Node(px, py, count, id);
		nodes.add(nd);
		if (nodes.size() < 3)
			return;
		if (nodes.size() == 3) // create the first triangle
		{
			Node p1 = (Node) nodes.get(0);
			Node p2 = (Node) nodes.get(1);
			Node p3 = (Node) nodes.get(2);
			EdgeSc e1 = new EdgeSc(p1, p2);
			if (e1.onSide(p3) == 0)
			{
				nodes.remove(nd);
				return;
			}
			if (e1.onSide(p3) == -1) // right side
			{
				p1 = (Node) nodes.get(1);
				p2 = (Node) nodes.get(0);
				e1.update(p1, p2);
			}
			EdgeSc e2 = new EdgeSc(p2, p3);
			EdgeSc e3 = new EdgeSc(p3, p1);
			e1.nextH = e2;
			e2.nextH = e3;
			e3.nextH = e1;
			hullStart = e1;
			triangles.add(new Triangle(edges, e1, e2, e3));
			return;
		}
		actE = (EdgeSc) edges.get(0);
		if (actE.onSide(nd) == -1)
		{
			if (actE.invE == null)
			{
				eid = -1;
			} else
			{
				eid = searchEdge(actE.invE, nd);
			}
		} else
		{
			eid = searchEdge(actE, nd);
		}

		if (eid == 0)
		{
			nodes.remove(nd);
			return;
		}
		if (eid > 0)
		{
			expandTri(actE, nd, eid); // nd is inside or on a triangle
		} else
		{
			expandHull(nd); // nd is outside convex hull
		}

	}

	private void expandTri(EdgeSc e, Node nd, int type)
	{
		EdgeSc e1 = e;
		EdgeSc e2 = e1.nextE;
		EdgeSc e3 = e2.nextE;
		Node p1 = e1.p1;
		Node p2 = e2.p1;
		Node p3 = e3.p1;
		if (type == 2)
		{ // nd is inside of the triangle
			EdgeSc e10 = new EdgeSc(p1, nd);
			EdgeSc e20 = new EdgeSc(p2, nd);
			EdgeSc e30 = new EdgeSc(p3, nd);
			e.inT.removeEdges(edges);
			triangles.remove(e.inT); // remove old triangle
			EdgeSc e100 = e10.makeSymm();
			EdgeSc e200 = e20.makeSymm();
			EdgeSc e300 = e30.makeSymm();
			triangles.add(new Triangle(edges, e1, e20, e100));
			triangles.add(new Triangle(edges, e2, e30, e200));
			triangles.add(new Triangle(edges, e3, e10, e300));
			swapTest(e1); // swap test for the three new triangles
			swapTest(e2);
			swapTest(e3);
		} else
		{ // nd is on the edge e
			EdgeSc e4 = e1.invE;
			if (e4 == null || e4.inT == null)
			{ // one triangle involved
				EdgeSc e30 = new EdgeSc(p3, nd);
				EdgeSc e02 = new EdgeSc(nd, p2);
				EdgeSc e10 = new EdgeSc(p1, nd);
				EdgeSc e03 = e30.makeSymm();
				// shareEdges(e03,e30);
				e10.asIndex();
				e1.mostLeft().nextH = e10;
				e10.nextH = e02;
				e02.nextH = e1.nextH;
				hullStart = e02;
				triangles.remove(e1.inT); // remove oldtriangle and add two new
				// triangles
				edges.remove(e1);
				edges.add(e10);
				edges.add(e02);
				edges.add(e30);
				edges.add(e03);
				triangles.add(new Triangle(e2, e30, e02));
				triangles.add(new Triangle(e3, e10, e03));
				swapTest(e2); // swap test for the two new triangles
				swapTest(e3);
				swapTest(e30);
			} else
			{ // two triangle involved
				EdgeSc e5 = e4.nextE;
				EdgeSc e6 = e5.nextE;
				Node p4 = e6.p1;
				EdgeSc e10 = new EdgeSc(p1, nd);
				EdgeSc e20 = new EdgeSc(p2, nd);
				EdgeSc e30 = new EdgeSc(p3, nd);
				EdgeSc e40 = new EdgeSc(p4, nd);
				triangles.remove(e.inT); // remove oldtriangle
				e.inT.removeEdges(edges);
				triangles.remove(e4.inT); // remove old triangle
				e4.inT.removeEdges(edges);
				e5.asIndex(); // because e, e4 removed, reset edge sortOrder of
				// node p1 and p2
				e2.asIndex();
				triangles.add(new Triangle(edges, e2, e30, e20.makeSymm()));
				triangles.add(new Triangle(edges, e3, e10, e30.makeSymm()));
				triangles.add(new Triangle(edges, e5, e40, e10.makeSymm()));
				triangles.add(new Triangle(edges, e6, e20, e40.makeSymm()));
				swapTest(e2); // swap test for the three new triangles
				swapTest(e3);
				swapTest(e5);
				swapTest(e6);
				swapTest(e10);
				swapTest(e20);
				swapTest(e30);
				swapTest(e40);
			}
		}
	}

	private void expandHull(Node nd)
	{
		EdgeSc e1, e2, e3 = null, enext;
		EdgeSc e = hullStart;
		EdgeSc comedge = null, lastbe = null;
		while (true)
		{
			enext = e.nextH;
			if (e.onSide(nd) == -1)
			{ // right side
				if (lastbe != null)
				{
					e1 = e.makeSymm();
					e2 = new EdgeSc(e.p1, nd);
					e3 = new EdgeSc(nd, e.p2);
					if (comedge == null)
					{
						hullStart = lastbe;
						lastbe.nextH = e2;
						lastbe = e2;
					} else
					{
						comedge.linkSymm(e2);
					}

					comedge = e3;
					triangles.add(new Triangle(edges, e1, e2, e3));
					swapTest(e);
				}
			} else
			{
				if (comedge != null)
					break;
				lastbe = e;
			}
			e = enext;
		}

		lastbe.nextH = e3;
		e3.nextH = e;
	}

	private int searchEdge(EdgeSc e, Node nd)
	{
		int f2, f3;
		EdgeSc e0 = null;
		if ((f2 = e.nextE.onSide(nd)) == -1)
		{
			if (e.nextE.invE != null)
				return searchEdge(e.nextE.invE, nd);
			else
			{
				actE = e;
				return -1;
			}
		}
		if (f2 == 0)
			e0 = e.nextE;
		EdgeSc ee = e.nextE;
		if ((f3 = ee.nextE.onSide(nd)) == -1)
		{
			if (ee.nextE.invE != null)
				return searchEdge(ee.nextE.invE, nd);
			else
			{
				actE = ee.nextE;
				return -1;
			}
		}
		if (f3 == 0)
			e0 = ee.nextE;
		if (e.onSide(nd) == 0)
			e0 = e;
		if (e0 != null)
		{
			actE = e0;
			if (e0.nextE.onSide(nd) == 0)
			{
				actE = e0.nextE;
				return 0;
			}
			if (e0.nextE.nextE.onSide(nd) == 0)
				return 0;
			return 1;
		}
		actE = ee;
		return 2;
	}

	private void swapTest(EdgeSc e11)
	{
		EdgeSc e21 = e11.invE;
		if (e21 == null || e21.inT == null)
			return;
		EdgeSc e12 = e11.nextE;
		EdgeSc e13 = e12.nextE;
		EdgeSc e22 = e21.nextE;
		EdgeSc e23 = e22.nextE;
		if (e11.inT.inCircle(e22.p2) || e21.inT.inCircle(e12.p2))
		{
			e11.update(e22.p2, e12.p2);
			e21.update(e12.p2, e22.p2);
			e11.linkSymm(e21);
			e13.inT.update(e13, e22, e11);
			e23.inT.update(e23, e12, e21);
			e12.asIndex();
			e22.asIndex();
			swapTest(e12);
			swapTest(e22);
			swapTest(e13);
			swapTest(e23);
		}
	}

	private void markHull()
	{
		EdgeSc e = hullStart;
		if (e != null)
			do
			{
				e.onHull = true;
				e.p1.onHull = true;
				e.p2.onHull = true;
				e = e.nextH;
			} while (!e.isEqual(hullStart));
	}
}