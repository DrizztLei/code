package web;

import java.io.*;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class MutilColorLinuxWithoutDirectory
{

	static double[][] ratio_dat;
	static Scanner scanner = new Scanner(System.in);
	public static String[] filename;
	public static int size;
	public static int feature_number = 9;
	public static int threshold = 8;
	public static DecimalFormat df = new DecimalFormat("0.0000000");

	public static final int NUMBER = 151;
	public static final int NEWLINE = 9;
	public static final int TYPENUMBER = 3;

	// public static final String root = "/home/elvis/DATASET/ADD/OUTPUT/"; //
	// change
	// here

	public static final String root = "/mnt/gentoo/Users/Elvis Lei/Desktop/ADD&DEL/DELETE_OUTPUT/";

	public static String path = root + "/Clumpy/";
	// father
	// directory

	public static String TxTInfo = path + "/info";
	public static final String[] feature_name =
	{ "Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic" };

	public static ArrayList<String> getFileName(String path)
	{

		File file = new File(path);
		ArrayList<String> returnFileList = new ArrayList<String>();
		if (!file.exists())
		{
			System.out.println("ERROR FOR PATH NOT EXISTS.");
			System.exit(-1);
		} else
		{
			File fileList[] = file.listFiles();
			for (int i = 0; i < fileList.length; i++)
			{
				File subFile = fileList[i];
				if (subFile.isDirectory())
				{
					ArrayList<String> temp = getFileName(subFile.getAbsolutePath());
					if (temp.size() != 0)
					{
						returnFileList.addAll(getFileName(subFile.getAbsolutePath()));
					}
				} else
				{
					String name = subFile.getAbsolutePath();
					if (name.indexOf("result") != -1 && name.endsWith(".csv"))
					{
						returnFileList.add(name);
					}
				}
			}
		}
		return returnFileList;
	}

	public static void readTxtFile(String filePath, int cur_num)
	{
		int count = 0;
		try
		{
			String encoding = "UTF-8";
			File file = new File(filePath);
			if (file.isFile() && file.exists())
			{
				InputStreamReader read = new InputStreamReader(new FileInputStream(file), encoding);
				BufferedReader bufferedReader = new BufferedReader(read);
				String lineTxt = null;
				while ((lineTxt = bufferedReader.readLine()) != null)
				{
					String[] sourceStrArray = lineTxt.split(",");
					ratio_dat[cur_num][count] = Double.valueOf(sourceStrArray[1].toString());
					count++;
				}
				read.close();
			} else
			{
				System.out.println(filePath);
				System.out.println("FILE NOT FOUND > ");
			}
		} catch (Exception e)
		{

			e.printStackTrace();
		}
		if (count != feature_number)
		{
			System.out.println("ERROR");
			System.exit(-1);
		}
	}

	@SuppressWarnings("resource")
	public static ArrayList<String> readFileFromTxt(String TxTName)
	{
		File file = new File(TxTName);
		Scanner scanner;
		try
		{
			scanner = new Scanner(file);
			ArrayList<String> fileList = new ArrayList<String>();
			while (scanner.hasNext())
			{
				fileList.add(scanner.nextLine());
			}
			return fileList;
		} catch (FileNotFoundException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return null;
	}

	public static void main(String[] args) throws FileNotFoundException
	{

		ArrayList<String> fileList = readFileFromTxt(TxTInfo);

		size = fileList.size();

		filename = new String[size];
		ratio_dat = new double[size][feature_number];

		for (int i = 0; i < feature_number; i++)
		{
			for (int j = 0; j < filename.length; j++)
			{
				filename[j] = fileList.get(j);
			}

			for (int j = 0; j < size; j++)
			{
				String read_ratio = filename[j];
				readTxtFile(read_ratio, j);
			}
			System.out.println("Build the feature : " + feature_name[i]);
			PrintStream printStream = new PrintStream(
					new FileOutputStream(path + "/html/" + feature_name[i] + ".html"));

			StringBuilder sb = new StringBuilder();

			sb.append("<html lang=\"en\">");
			sb.append("<head>");
			sb.append("<meta charset=\"utf-8\" />");
			sb.append("<title>Results comparsion</title>");
			sb.append("<meta name=\"viewport\" content=\"initial-scale=1.0; maximum-scale=1.0; width=device-width;\">");
			sb.append("<link rel=\"stylesheet\" type=\"text/css\" href=\"css/index.css\">");
			sb.append("</head>");
			sb.append("<body>");
			sb.append("<div class=\"table-title\">");
			sb.append("<h3>IMAGE WITH " + feature_name[i].toUpperCase() + "</h3>");
			sb.append("<h4 style=\"color:red; font-weight:bold;\">All images are clickable</h4>");
			sb.append("</div>");
			sb.append("<table class=\"table-fill\">");
			sb.append("<tbody class=\"table-hover\">");

			int count = 0;
			int countNewLine = 0;

			// sort for inner
			for (int control = 0; control < TYPENUMBER; control++)
			{
				for (int j = 0; j < size / NUMBER; j++)
				{
					int start = j * NUMBER + 1 + control;
					int end = j * NUMBER + NUMBER;

					for (int k = start; k < end; k += TYPENUMBER)
					{
						double minValue = ratio_dat[k][i];
						int minSeq = k;

						for (int l = k; l < end; l += TYPENUMBER)
						{
							if (minValue > ratio_dat[l][i])
							{
								minValue = ratio_dat[l][i];
								minSeq = l;
							}
						}

						double tempValue = ratio_dat[minSeq][i];
						ratio_dat[minSeq][i] = ratio_dat[k][i];
						ratio_dat[k][i] = tempValue;

						String tempName = filename[minSeq];
						filename[minSeq] = filename[k];
						filename[k] = tempName;
					}
				}
			}

			double[] varSet = new double[(size / NUMBER) * TYPENUMBER];
			double[] meanSet = new double[(size / NUMBER) * TYPENUMBER];

			for (int control = 0; control < TYPENUMBER; control++)
			{
				for (int j = 0; j < size / NUMBER; j++)
				{
					int start = j * NUMBER + 1 + control;
					int end = j * NUMBER + NUMBER;
					double mean = 0;

					for (int k = start; k < end; k += TYPENUMBER)
					{
						mean += ratio_dat[k][i];
					}

					mean /= ((NUMBER - 1) / TYPENUMBER);
					double var = 0;
					for (int k = start; k < end; k += TYPENUMBER)
					{
						var += Math.pow(ratio_dat[k][i] - mean, 2);
					}
					meanSet[j * TYPENUMBER + control] = mean;
					varSet[j * TYPENUMBER + control] = Math.sqrt(var / ((NUMBER - 1) / TYPENUMBER));
				}
			}
			for (int j = 0; j < varSet.length; j += TYPENUMBER)
			{
				double min = varSet[j] + varSet[j + 1];
				int seq = j;
				for (int k = j; k < varSet.length; k += TYPENUMBER)
				{
					if (min < varSet[k] + varSet[k + 1])
					{
						min = varSet[k] + varSet[k + 1];
						seq = k;
					}
				}

				// System.out.println(meanSet[j]);
				// System.out.println(meanSet[seq]);

				for (int n = 0; n < TYPENUMBER; n++)
				{
					double temp = varSet[seq + n];
					varSet[seq + n] = varSet[j + n];
					varSet[j + n] = temp;

					temp = meanSet[seq + n];
					meanSet[seq + n] = meanSet[j + n];
					meanSet[j + n] = temp;
				}

				int start = (j / TYPENUMBER) * NUMBER;
				int end = (seq / TYPENUMBER) * NUMBER;

				for (int k = 0; k < NUMBER; ++k)
				{
					int ori = k + start;
					int aim = k + end;

					double tempValue = ratio_dat[ori][i];
					// System.out.print(tempValue + ",");
					ratio_dat[ori][i] = ratio_dat[aim][i];
					ratio_dat[aim][i] = tempValue;

					String tempExchange = filename[ori];
					filename[ori] = filename[aim];
					filename[aim] = tempExchange;
				}
			}
			
			for (int j = 0; j < size / NUMBER; j++)
			{
				int chooseStart = j * NUMBER;

				{
					String[] fileInfo = filename[chooseStart].split("/");
					String originName = fileInfo[fileInfo.length - 1];
					String directory = fileInfo[fileInfo.length - 3];
					String fatherDirectory = fileInfo[fileInfo.length - 4];

					String name = originName.replaceAll(".csv", "");
					String png = fileList.get(chooseStart).toString();

					png = png.replaceAll("\\.csv", ".png");
					png = png.replaceAll("/result/", "/png/");

					int position = name.lastIndexOf('/');

					name = name.substring(position + 1);

					File png_file = new File(png);

					if (!png_file.exists())
					{
						System.out.println("PNG : " + png + " NOT FOUND . ");
						continue;
					}

					String value = df.format(ratio_dat[chooseStart][i]);
					String data = value;
					if (data.length() > threshold)
					{
						data = data.substring(0, threshold - 1);
					}

					sb.append("<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../"
							+ "/" + fatherDirectory + "/" + directory + "/png/" + name + ".png\"><img src=\"../" + "/"
							+ fatherDirectory + "/" + directory + "/png/" + name
							+ ".png\" /></a><p style=\"text-align:center;\">" + data + "</td>");

					sb.append("</tr>");
				}

				for (int l = 0; l < TYPENUMBER; l++)
				{
					int iteratorTimes = (NUMBER - 1) / TYPENUMBER;
					for (int k = 0; k < iteratorTimes; k++)
					{
						int choose;
						choose = j * NUMBER + 1 + k * TYPENUMBER + l; // big
																		// block
																		// +
																		// small
																		// block
																		// +
																		// bias

						String[] fileInfo = filename[choose].split("/");

						String originName = fileInfo[fileInfo.length - 1];
						String directory = fileInfo[fileInfo.length - 3];
						String fatherDirectory = fileInfo[fileInfo.length - 4];

						String name = originName.replaceAll(".csv", "");
						String png = fileList.get(choose).toString();

						png = png.replaceAll("\\.csv", ".png");
						png = png.replaceAll("/result", "/png/");

						int position = name.lastIndexOf('/');

						name = name.substring(position + 1);

						File png_file = new File(png);

						if (!png_file.exists())
						{
							System.out.println("PNG : " + png + " NOT FOUND . ");
							continue;
						}

						String value = df.format(ratio_dat[choose][i]);
						String data = value;
						if (data.length() > threshold)
						{
							data = data.substring(0, threshold - 1);
						}

						String varData = df.format(varSet[j * TYPENUMBER + l]);

						sb.append("<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../"
								+ "/" + fatherDirectory + "/" + directory + "/png/" + name + ".png\"><img src=\"../"
								+ "/" + fatherDirectory + "/" + directory + "/png/" + name
								+ ".png\" /></a><p style=\"text-align:center;\">" + data
								+ (k == 0 ? ("</a><p style=\"text-align:center;\">" + varData) : "") + "</td>");

						count++;
						countNewLine++;

						if (count % NUMBER == 0)
						{
							sb.append("<tr>");
							countNewLine = 0;
						} else if (countNewLine % NEWLINE == 0)
						{
							sb.append("</tr>");
						}
					}
					sb.append("</tr>");
					countNewLine = 0;
					count = 0;
				}
			}
			sb.append("</tbody></table></body></html>");
			printStream.println(sb.toString());
			printStream.close();
		}

	}
}
