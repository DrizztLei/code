package web;

import java.io.*;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class ClusterWeb
{

	static double[][] ratio_dat;
	static Scanner scanner = new Scanner(System.in);
	public static String[] filename;
	public static int size;
	public static int feature_number = 9;
	public static int threshold = 8;
	public static DecimalFormat df = new DecimalFormat("0.0000000");

	public static final int number = 6;
	public static final int NewLine = 9;
	
	public static final String root = "C:/Users/Elvis Lei/Documents/scagnostics_data/issue/";	// change root here
	public static final String path = root + "/rotate/"; // change father
																// directory
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

	public static void main(String[] args) throws FileNotFoundException
	{

		ArrayList<String> fileList = getFileName(path);
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

			PrintStream printStream = new PrintStream(
					new FileOutputStream(path + "\\html\\" + feature_name[i] + ".html"));

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

			for (int j = 0; j < size / number; j++)
			{
				int start = j * number + 1;
				int end = j * number + number;

				for (int k = start; k < end; k++)
				{
					double minValue = ratio_dat[k][i];
					int minSeq = k;

					for (int l = k; l < end; l++)
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

			double[] varSet = new double[size / number];
			double[] meanSet = new double[size / number];

			for (int j = 0; j < size / number; j++)
			{
				int start = j * number;
				int end = j * number + number;
				double mean = 0;

				for (int k = start; k < end; k++)
				{
					mean += ratio_dat[k][i];
				}
				mean /= (end - start);
				
				double var = 0;
				for (int k = start; k < end; k++)
				{
					var += Math.pow(ratio_dat[k][i] - mean, 2);
				}

				meanSet[j] = mean; 
				varSet[j] = Math.sqrt(var / number);
			}
			
			for (int j = 0; j < varSet.length; j++)
			{
				double min = varSet[j];
				int seq = j;
				for (int k = j; k < varSet.length; k++)
				{
					if (min < varSet[k])
					{
						min = varSet[k];
						seq = k;
					}
				}

				double temp = varSet[seq];
				varSet[seq] = varSet[j];
				varSet[j] = temp;
				
				temp = meanSet[seq];
				meanSet[seq] = meanSet[j];
				meanSet[j] = temp;

				for (int k = 0; k < number; k++)
				{
					int ori = k + j * number;
					int aim = k + seq * number;

					double tempValue = ratio_dat[ori][i];
					ratio_dat[ori][i] = ratio_dat[aim][i];
					ratio_dat[aim][i] = tempValue;

					String exchange = filename[ori];
					filename[ori] = filename[aim];
					filename[aim] = exchange;
				}
			}
			/*
			for(int l = 0; l < size/number; l++)
			{
				for(int m = 0; m < number; m++)
				{
					System.out.print(ratio_dat[l * number + m][i] + ", ");
				}
				System.out.println();
				System.out.println(meanSet[l]);
				System.out.println(varSet[l]);
				scanner.nextLine();
			}
			*/
			for (int j = 0; j < size; j++)
			{
				String[] fileInfo = filename[j].split("\\\\");
				String originName = fileInfo[fileInfo.length - 1];
				String directory = fileInfo[fileInfo.length - 3];
				String fatherDirectory = fileInfo[fileInfo.length - 4];

				String name = originName.replaceAll(".csv", "");
				String png = fileList.get(j).toString();

				png = png.replaceAll("\\.csv", ".png");
				png = png.replaceAll("\\\\result\\\\", "\\\\png\\\\");

				int position = name.lastIndexOf('\\');

				name = name.substring(position + 1);

				File png_file = new File(png);

				if (!png_file.exists())
				{
					System.out.println("PNG : " + png + " NOT FOUND . ");
					continue;
				}

				String value = df.format(ratio_dat[j][i]);
				String data = value;
				if (data.length() > threshold)
				{
					data = data.substring(0, threshold - 1);
				}

				String varData = df.format(varSet[j / number]);

				sb.append("<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../" + "/"
						+ fatherDirectory + "/" + directory + "/png/" + name + ".png\"><img src=\"../" + "/"
						+ fatherDirectory + "/" + directory + "/png/" + name
						+ ".png\" /></a><p style=\"text-align:center;\">" + data
						+ (j % number == 0 ? ("</a><p style=\"text-align:center;\">" + varData) : "") + "</td>");

				count++;
				countNewLine++;

				if (count % number == 0)
				{
					sb.append("<tr>");
					countNewLine = 0;
				}
				else if (countNewLine % NewLine == 0)
				{
					sb.append("</tr>");
				}
			}
			sb.append("</tbody></table></body></html>");
			printStream.println(sb.toString());
			printStream.close();
		}
	}
}
