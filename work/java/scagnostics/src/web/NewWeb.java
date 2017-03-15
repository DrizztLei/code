package web;

import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Scanner;

public class NewWeb
{

	static double[][] ratio_dat = new double[828][1];
	static Scanner scanner = new Scanner(System.in);

	public static void readTxtFile(String filePath, int cur_num)
	{
		int count = 1;
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
					switch (count)
					{
					case 3:
						ratio_dat[cur_num][0] = Double.valueOf(sourceStrArray[1].toString());
						break;
					default:
						break;
					}
					count++;
				}
				read.close();
			} else
			{

			}
		} catch (Exception e)
		{

			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws FileNotFoundException
	{

		String path = "C:/Users/Elvis Lei/Documents/thousand_csv/";

		File file = new File(path + "/result/");

		File[] tempList = file.listFiles();

		int size = 828;

		StringBuilder sb = new StringBuilder();
		@SuppressWarnings("resource")
		PrintStream printStream = new PrintStream(
				new FileOutputStream("C:\\Users\\Elvis Lei\\Documents\\thousand_csv\\html\\out.html"));

		sb.append("<html lang=\"en\">");
		sb.append("<head>");
		sb.append("<meta charset=\"utf-8\" />");
		sb.append("<title>Results comparsion</title>");
		sb.append("<meta name=\"viewport\" content=\"initial-scale=1.0; maximum-scale=1.0; width=device-width;\">");
		sb.append("<link rel=\"stylesheet\" type=\"text/css\" href=\"css/index.css\">");
		sb.append("</head>");
		sb.append("<body>");
		sb.append("<div class=\"table-title\">");
		sb.append("<h3>IMAGE WITH CLUMPY</h3>");
		sb.append("<h4 style=\"color:red; font-weight:bold;\">All images are clickable</h4>");
		sb.append("</div>");
		sb.append("<table class=\"table-fill\">");

		sb.append("<tbody class=\"table-hover\">");

		int count = 0;

		String[] filename = new String[828];
		for (int i = 0; i < filename.length; i++)
		{
			filename[i] = tempList[i].toString();
		}

		for (int i = 0; i < size; i++)
		{
			String read_ratio = filename[i];
			readTxtFile(read_ratio, i);
		}

		for (int i = 0; i < 828; i++)
		{
			double min = ratio_dat[i][0];
			int flag = i;
			for (int j = i; j < 828; j++)
			{
				if (min > ratio_dat[j][0])
				{
					min = ratio_dat[j][0];
					flag = j;
				}
			}

			double temp = ratio_dat[i][0];
			ratio_dat[i][0] = ratio_dat[flag][0];
			ratio_dat[flag][0] = temp;

			String exchange = filename[i];
			filename[i] = filename[flag];
			filename[flag] = exchange;
		}

		for (int i = 0; i < size; i++)
		{

			String name = filename[i].replaceAll(".csv", "");

			String png = tempList[i].toString();

			png = png.replaceAll("\\.csv", ".png");
			png = png.replaceAll("result", "png");

			int position = name.lastIndexOf('\\');

			name = name.substring(position + 1);

			File png_file = new File(png);

			if (!png_file.exists())
			{
				System.out.println("PNG : " + png + " NOT FOUND . ");
				continue;
			}

			for (int j = 0; j < 1; j++)
			{
				if (i == 0 || ratio_dat[i][0] != ratio_dat[i - 1][0])
				{
					BigDecimal bd = new BigDecimal(ratio_dat[i][0]);
					bd = bd.setScale(8, RoundingMode.HALF_UP);
					String value = "" + bd.toString();
					String clumpy_dat = "" + value;
					System.out.println(name);
					sb.append("<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../png/"
							+ name + ".png\"><img src=\"../png/" + name
							+ ".png\" /></a><p style=\"text-align:center;\">" + clumpy_dat + "</td>");
					count++;
				}

			}

			if (count % 9 == 0)
			{
				sb.append("</tr>");
			}

		}

		sb.append("</tbody></table></body></html>");
		printStream.println(sb.toString());
	}
}
