package libsvm;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.StandardSocketOptions;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Vector;

import javax.rmi.ssl.SslRMIClientSocketFactory;

public class ST
{
	public static int numOfTrans = 0;

	public static void EdmondsKarp(int start, int end, double[][] cap, Node[] node, int s) throws IOException
	{
		double[][] flow = new double[cap.length][cap[0].length]; // 记录流量
		int[] pre = new int[cap.length]; // 记录前一个节点
		double[] rest = new double[cap.length]; // 记录剩余的流量，残量
		int numOfPath = 0;
		double maxflow = 0;

		for (int i = 0; i < flow.length; i++)
		{
			Arrays.fill(flow[i], 0);
		}

		Arrays.fill(pre, 0);

		LinkedList list = new LinkedList<Integer>();

		while (true)
		{

			for (int j = 0; j < rest.length; j++)
			{// 设置残量都为0
				rest[j] = 0;
			}
			rest[start] = 10000000;
			list.add(start);
			while (!list.isEmpty())
			{
				int u = (int) list.pollFirst();
				for (int v = 0; v <= end; v++)
				{
					if (rest[v] == 0 && cap[u][v] - flow[u][v] > 0 && cap[u][v] != -1)
					{
						pre[v] = u;
						rest[v] = Math.min(rest[u], cap[u][v] - flow[u][v]);// 获取start到v节点的最小残量
						list.add(v);
					}
				}
			}

			maxflow += rest[end];

			if (rest[end] == 0)
			{
				return;
			}
			Vector<Integer> vectorOfOnePath = new Vector<Integer>();
			for (int u = end; u != start; u = pre[u])
			{
				flow[pre[u]][u] += rest[end]; // 更新正向流
				flow[u][pre[u]] -= rest[end]; // 更新反向流
				if (u != end)
				{
					vectorOfOnePath.add(u);
				}
			}
			String str = "";
			int length = 0;
			double cov = 0;
			for (int i = vectorOfOnePath.size() - 1; i >= 0; i--)
			{
				// System.out.print(vectorOfOnePath.get(i)+" ");
				str = str + node[vectorOfOnePath.get(i)].getSequence();
				length = length + node[vectorOfOnePath.get(i)].getLength();
				cov = cov + node[vectorOfOnePath.get(i)].getCov();
			}
			if (str != "")
			{
				FileWriter fw = new FileWriter("f:\\2.fa", true);
				BufferedWriter bw = new BufferedWriter(fw);
				bw.write("trans" + numOfTrans + "_sg" + s + "_" + numOfPath + "   " + "len = " + length + "    "
						+ "cov = " + cov + "  " + "sequence = ");
				bw.newLine();
				bw.flush(); // 将数据更新至文件
				bw.write(str);
				bw.newLine();
				bw.flush();
				bw.close();
				fw.close();
				numOfTrans++;
				numOfPath++;
			}
		}

		// return vectorOfPaths;
	}

	public static void alterAdj(double[][] adj)
	{
		for (int i = 0; i < adj.length; i++)
		{
			if (adj[0][i] == 0)
			{
				adj[0][i] = 10000;
			}
			if (adj[i][adj.length - 1] == 0)
			{
				adj[i][adj.length - 1] = 10000;
			}
		}
		// for(int i=0;i<adj.length;i++){
		// for(int j=0;j<adj[0].length;j++){
		// System.out.print(adj[i][j]+" ");
		// }
		// System.out.println();
		// }

	}

	public static void main(String[] args)
	{

		for (int s = 0; s < 135; s++)
		{

			FileInputStream fis = null;
			InputStreamReader isr = null;
			BufferedReader br = null; // 用于包装InputStreamReader,提高处理性能。因为BufferedReader有缓冲的，而InputStreamReader没有。
			try
			{
				String str = "";
				String str1 = "";
				fis = new FileInputStream("./splicing_graph" + s + ".rg");// FileInputStream
				// 从文件系统中的某个文件中获取字节
				isr = new InputStreamReader(fis);// InputStreamReader
													// 是字节流通向字符流的桥梁,
				br = new BufferedReader(isr);// 从字符输入流中读取文件中的内容,封装了一个new
												// InputStreamReader的对象
				int flagTopo = 0;
				Node node[] = null;
				double[][] adj = null;
				while ((str = br.readLine()) != null)
				{
					str = str.replace(" ", "");
					if (str.equals("**Topological**"))
					{
						str = br.readLine();
						// System.out.println(str);
						String ss[] = str.split(",");

						node = new Node[ss.length];
						adj = new double[ss.length][ss.length];
						for (int i = 0; i < ss.length; i++)
						{
							for (int j = 0; j < ss.length; j++)
							{
								adj[i][j] = -1;
							}
						}
					}
					if (str.equals("**Nodes**"))
					{
						int nodescount = 0;
						while (true)
						{
							str = br.readLine();
							if (str == null)
							{
								break;
							}
							str = str.replace(" ", "");
							if (str.equals("0**Edges**"))
							{
								break;
							}
							if ((str.charAt(0) == 'n' && str.charAt(1) == 'o')
									|| (str.charAt(0) == '0' && str.charAt(1) == 'n'))
							{
								int i = 0;
								int attributeCount = 0;
								Node no = new Node();
								while (i < str.length())
								{
									if (str.charAt(i) == '=')
									{
										int j = i + 1;
										while ((str.charAt(j) >= '0' && str.charAt(j) <= '9') || str.charAt(j) == '.')
										{
											j++;
										}
										switch (attributeCount)
										{
										case 0:
											no.setId(Integer.parseInt(str.substring(i + 1, j)));
											i = j - 1;
											attributeCount++;
											break;
										case 1:
											no.setLength(Integer.parseInt(str.substring(i + 1, j)));
											;
											i = j - 1;
											attributeCount++;
											break;
										case 2:
											no.setCov(Double.parseDouble(str.substring(i + 1, j)));
											i = j - 1;
											attributeCount++;
											no.setSequence(br.readLine());
											node[nodescount] = no;
											nodescount++;
											break;

										}

										i = j - 1;
									} else
										i++;
								}

							}

						}
					}
					if (str.equals("0**Edges**"))
					{
						while (true)
						{
							str = br.readLine();
							if (str == null)
							{
								break;
							}
							str = str.replace(" ", "");
							if (str.equals("**Inhibit_edges**"))
							{
								break;
							}
							if (str != null)
							{
								str = str.replace("->", ",");
								str = str.replace(":", ",");
								str = str.replace(";", ",");
								// System.out.println(str);
								String[] num = str.split(",");
								// System.out.println(num.length);
								int begin = 0, end = 0;// 构建邻接矩阵 矩阵的行列数字
								for (int i = 0; i < num.length; i++)
								{
									if (i % 3 == 2)
									{
										for (int j = 0; j < node.length; j++)
										{
											if (node[j].getId() == Integer.parseInt(num[i - 2]))
											{
												begin = j;
											}
										}
										for (int j = 0; j < node.length; j++)
										{
											if (node[j].getId() == Integer.parseInt(num[i - 1]))
											{
												end = j;
											}
										}
										adj[begin][end] = Double.parseDouble(num[i]);
									}
								}
							}

						}
					}

				}
				// System.out.println("第"+s+"个图的邻接矩阵：");
				// for(int i=0;i<adj.length;i++){
				// for(int j=0;j<adj[0].length;j++){
				// System.out.print(adj[i][j]+" ");
				// }
				// System.out.println();
				// }
				alterAdj(adj);
				EdmondsKarp(0, node.length - 1, adj, node, s);
			} catch (FileNotFoundException e)
			{
				System.out.println("找不到指定文件");
			} catch (IOException e)
			{
				System.out.println("读取文件失败");
			} finally
			{
				try
				{
					br.close();
					isr.close();
					fis.close();
					// 关闭的时候最好按照先后顺序关闭最后开的先关闭所以先关s,再关n,最后关m
				} catch (IOException e)
				{
					e.printStackTrace();
				}
			}

		}
	}

}
