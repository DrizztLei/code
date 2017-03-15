package web;
import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.Scanner;

public class ChangedPng
{

	static double[][] ratio_dat;
	static Scanner scanner = new Scanner(System.in);
	public static String[] filename;
	public static int size;
	public static int feature_number = 9;

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
	}

	public static void main(String[] args) throws FileNotFoundException
	{
		String[] fdistx_Name =
		{ "Binormal", "Clustered", "Doughnut", "Exponential", "Funnel", "Quadratic", "Spherical", "Stripe",
				"Stripe_Rays", "Uniform" };

		for (int i = 0; i < feature_number; i++)
		{
			String root = "C:\\Users\\Elvis Lei\\Documents\\scagnostics_data\\issue\\out\\"; // change
																								// root
																								// here

			String[] feature_name =
			{ "Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic" };

			PrintStream printStream = new PrintStream(
					new FileOutputStream(root + "\\html\\" + feature_name[i] + ".html"));

			ratio_dat = new double[size][9];

			StringBuilder sb = new StringBuilder();

			sb.append("<html lang=\"en\">");
			sb.append("<head>");
			sb.append("<meta charset=\"utf-8\" />");
			sb.append("<title>Results comparsion in" + feature_name[i] + "</title>");
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
			for (int ixx = 0; ixx < fdistx_Name.length; ++ixx)
			{
				File file = new File(root + "/result/");

				File[] tempList = file.listFiles();

				size = tempList.length;

				System.out.println(size);

				boolean flag = true;

				if (flag)
				{
					filename = new String[size];
					for (int j = 0; j < filename.length; j++)
					{
						filename[j] = tempList[j].toString();
					}

					for (int j = 0; j < size; j++)
					{
						String read_ratio = filename[j];
						readTxtFile(read_ratio, j);
					}
				} else
				{
					flag = false;
				}

				for (int i1 = 0; i1 < size; i1++)
				{
					double min = ratio_dat[i1][i];
					int flag1 = i1;
					for (int j = i1; j < size; j++)
					{
						if (min > ratio_dat[j][i])
						{
							min = ratio_dat[j][i];
							flag1 = j;
						}
					}

					double temp = ratio_dat[i1][i];
					ratio_dat[i1][i] = ratio_dat[flag1][i];
					ratio_dat[flag1][i] = temp;

					String exchange = filename[i1];
					filename[i1] = filename[flag1];
					filename[flag1] = exchange;
				}

				int count = 0;

				for (int i1 = 0; i1 < size; i1++)
				{

					String name = filename[i1].replaceAll(".csv", "");

					String png = tempList[i1].toString();

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

						BigDecimal bd = new BigDecimal(ratio_dat[i1][i]);
						bd = bd.setScale(8, RoundingMode.HALF_UP);
						String value = "" + bd.toString();
						String data = "" + value;
						System.out.println(name);
						sb.append(
								"<td class=\"text-center\" style=\"padding:0 20px;\"><a target=\"_blank\"  href=\"../png/"
										+ name + ".png\"><img src=\"../png/" + name
										+ ".png\" /></a><p style=\"text-align:center;\">" + data + "</td>");
						count++;

					}

					if (count % 9 == 0)
					{
						sb.append("</tr>");
					}

				}
			}
			sb.append("</tbody></table></body></html>");
			printStream.println(sb.toString());
			printStream.close();
		}

	}
}