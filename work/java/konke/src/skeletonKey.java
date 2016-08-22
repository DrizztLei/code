import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;

public class skeletonKey 
{
	private final static PrintWriter pw = new PrintWriter(System.out, true);
	private final static PrintWriter pe = new PrintWriter(System.err , true);
	private final static String client_name = "elvis.linuxer@gmail.com";
	private final static String userid = "elvis.linuxer@gmail.com";
	private final static String client_id = "4yCOi48I687EN2Ix";
	private final static String client_secret = "1K742MBPCd5LAL24";
	private final static String access_token = "155bbd381a287e9b505e987379fa685e";
	private final static String kid = "d9b6073f-e334-49a6-af5c-e1b6e8516ae9";
	private final static String mac = "28-d9-8a-06-d2-41";
	private final static String prefix = "http://kk.bigk2.com:8080/KOAuthDemeter/";
	private static method set = new method();

	private static String getClientName() 
	{
		return client_name;
	}

	private static String getUserID() 
	{
		return userid;
	}

	private static String getClientID() 
	{
		return client_id;
	}

	private static String getClientSecret() 
	{
		return client_secret;
	}

	private static String getAccessToken() 
	{
		return access_token;
	}

	private static String getKID() 
	{
		return kid;
	}

	private static String getMAC() 
	{
		return mac;
	}

	private static String getPrefix() 
	{
		return prefix;
	}

	private static PrintWriter getPrintWriter() 
	{
		return pw;
	}

	private static method getMethod() 
	{
		return set;
	}
	
	private static PrintWriter getPrintErr()
	{
		return pe;
	}

	private static int post(int index, String[] info) throws IOException 
	{
		URL url = new URL(getMethod().getURL(index)); // 创建连接

		HttpURLConnection connection = (HttpURLConnection) url.openConnection();

		connection.setDoOutput(true);
		connection.setDoInput(true);
		connection.setUseCaches(false);
		connection.setInstanceFollowRedirects(true);
		connection.setRequestMethod("POST"); // 设置请求方式
		connection.setRequestProperty("Accept", "application/json"); // 设置接收数据的格式
		connection.setRequestProperty("Content-Type", "application/json"); // 设置发送数据的格式
		connection.setRequestProperty("Accept-Encoding", "identity");
		connection.setRequestProperty("Authorization", "Bearer " + getAccessToken());

		connection.connect();

		getMethod();
		String msg = method.setParameter(info);
		
		//System.out.println(msg);

		// 向服务器POST信息
		if (null != msg && msg.length() > 0) 
		{
			OutputStreamWriter out = new OutputStreamWriter(connection.getOutputStream(), "UTF-8"); // 服务器采用UTF-8编码
			out.append(msg);
			out.flush();
			out.close();
		}

		// 读取服务器响应(最大长度10K)
		int length = 10 * 1024;
		// int length =connection.getContentLength();// 获取长度,这里一直返回0,不知道什么原因
		InputStream is = connection.getInputStream();
		if (length != -1) 
		{
			byte[] data = new byte[length];
			byte[] temp = new byte[512];// 每次读取512字节
			int readLen = 0;// 单次读取的长度
			int destPos = 0;// 总字节数
			while ((readLen = is.read(temp)) > 0) 
			{
				System.arraycopy(temp, 0, data, destPos, readLen);
				destPos += readLen;
			}
			String result = new String(data, "UTF-8"); // 响应也是UTF-8编码
			String backtrack = "result";
			int position = result.indexOf(backtrack);
			int step = 2;
			char flag = result.charAt(position+backtrack.length() + step);
			if(flag != '0')
			{
				int failed = result.charAt(position+backtrack.length() + step + 1) - '0';
				//getPrintWriter().println(failed);
				getPrintErr().println(result);
				return -failed;
			}
			else
			{
				getPrintWriter().println(result);
				return 0;
			}
			//getPrintWriter().println(result);
		}
		return -1;
	}

	public static void main(String[] args) 
	{

		if (args.length == 0) 
		{
			getPrintErr().println("error for parameter .");
			System.exit(-1);
		}
		try 
		{
			int index = new Integer(args[0]);
			int value = post(index, args);
			if(value != 0)
			{
				System.exit(value);
			}
		}
		catch (Exception e) 
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(-1);
		}
		/*
		 * for (int i = 0; i < getMethod().getMethod().size(); i++) {
		 * getPrintWriter().println(getMethod().getMethod().get(i).getMethodName
		 * ()); }
		 */
	}
}
