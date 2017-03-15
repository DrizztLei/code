package web;

import java.io.*;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Union
{

	static double[][] ratio_dat;
	static Scanner scanner = new Scanner(System.in);
	public static String[] filename;
	public static int size;
	public static int feature_number;
	public static int threshold = 8;
	public static DecimalFormat df = new DecimalFormat("0.0000000");

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

		String root = "C:/Users/Elvis Lei/Documents/"; // change root here
		String path = root + "/scagnostics_data/"; // change father directory

		String[] feature_name =
		{ "Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic" };

		feature_number = 9;

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

			for (int count = 0; count < size; count++)
			{
				double min = ratio_dat[count][i];
				int exchangedPosition = count;
				for (int j = count; j < size; j++)
				{
					if (min > ratio_dat[j][i])
					{
						min = ratio_dat[j][i];
						exchangedPosition = j;
					}
				}

				double temp = ratio_dat[count][i];
				ratio_dat[count][i] = ratio_dat[exchangedPosition][i];
				ratio_dat[exchangedPosition][i] = temp;

				String exchange = filename[count];
				filename[count] = filename[exchangedPosition];
				filename[exchangedPosition] = exchange;

				if (filename[exchangedPosition].hashCode() == filename[count].hashCode() && count != exchangedPosition)
				{
					System.out.println(filename[exchangedPosition]);
					System.out.println(filename[count]);
					System.out.println("ERROR FOR HASH CODE SUM");
					System.exit(-1);
				}
			}

			int count = 0;

			for (int j = 0; j < size; j++)
			{
				String[] fileInfo = filename[j].split("\\\\");
				String originName = fileInfo[fileInfo.length - 1];
				String directory = fileInfo[fileInfo.length - 3];

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

				/*
				 * BigDecimal bd = new BigDecimal(ratio_dat[j][i]); bd =
				 * bd.setScale(16, RoundingMode.HALF_UP);
				 */

				String value = df.format(ratio_dat[j][i]);
				String data = value;
				if (data.length() > threshold)
				{
					data = data.substring(0, threshold - 1);
				}

				sb.append("<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../"
						+ directory + "/png/" + name + ".png\"><img src=\"../" + directory + "/png/" + name
						+ ".png\" /></a><p style=\"text-align:center;\">" + data + "</td>");
				count++;

				if (count % 9 == 0)
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
