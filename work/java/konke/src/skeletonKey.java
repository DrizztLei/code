import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.List;

import org.json.JSONObject;
import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.FormElement;
import org.jsoup.select.Elements;

public class skeletonKey 
{
	private final static PrintWriter pw = new PrintWriter(System.out, true);
	private final static PrintWriter pe = new PrintWriter(System.err , true);
	/**
	 * Replace your information here fully.
	 */
	 
	private final static String userid = "elvis.linuxer@gmail.com";//Must unless you wanna get it through the interface of 38 
	private final static String client_id = "4yCOi48I687EN2Ix";//Must
	private final static String client_secret = "1K742MBPCd5LAL24";//Must
	private static String access_token = "155bbd381a287e9b505e987379fa685e"; //Must unless your wanna get it when your first run it.
	private final static String mac = "28-d9-8a-06-d2-41";//Optional
	private final static String client_name = "elvis.linuxer@gmail.com";//Must . The 
	private final static String passwd = "Idon'tknow";//This password is the password of your client_name
	
	private final static String prefix = "http://kk.bigk2.com:8080/KOAuthDemeter/";
	
	private static method set = new method();
	private static kID id = new kID();
	
	public static kID getKID()
	{
		return id;
	}
	
	private static String getPassWD()
	{
		return passwd;
	}
	
	private static void  setAccessToken(String token) 
	{
		access_token = token;
	}

	private static String getClientName() 
	{
		return client_name;
	}

	public static String getUserID() 
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

	private static String getMAC() 
	{
		return mac;
	}

	public static String getPrefix() 
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

	private static int post(int idFlag , int index, String[] info) throws IOException 
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

		//getMethod();
		String msg = method.setParameter(info);
		
		System.out.println(msg);

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
				if(result.indexOf("invalid_token") != -1)
				{
					try
					{
						setAccessToken(refreshAccessToken(getClientName(), getPassWD()));
						return post(idFlag , index, info);
					}
					catch (StackOverflowError e) 
					{
						// TODO: handle exception
						getPrintErr().print("ERROR FOR ACCESS TOKEN INVALID , PLEASE CHECK YOU ID AND SECRET .");
						getPrintErr().flush();
						System.exit(-1);
					}
					catch (Exception e) {
						// TODO: handle exception
						getPrintErr().print("UNKNOW ERROR .");
						getPrintErr().flush();
						System.exit(-1);
					}
				}
				else
				{
					int failed = result.charAt(position+backtrack.length() + step + 1) - '0';
					//getPrintWriter().println(failed);
					getPrintErr().print(result);
					getPrintErr().flush();
					return -failed;					
				}

			}
			else
			{
				getPrintWriter().print(result);
				getPrintWriter().flush();
				return 0;
			}
		}
		return -1;
	}
	
	private static String refreshAccessToken(String username, String password) {
		String access_token = null;
		try {
			Connection conn = null;
			String url = "http://kk.bigk2.com:8080/KOAuthDemeter/authorize?response_type=code&client_id=" + client_id
					+ "&redirect_uri=http://www.baidu.com";
			conn = Jsoup.connect(url);
			Document doc = conn.get();

			// System.out.println(doc.toString());

			List<FormElement> formList = doc.getAllElements().forms();
			if (formList.size() > 0) 
			{
				
				FormElement form = formList.get(0);
				Elements usernameInput = form.select("input[name=username]");
				Elements passwordInput = form.select("input[name=password]");
				usernameInput.attr("value", username);
				passwordInput.attr("value", password);

				conn = form.submit();
				doc = conn.post();
			}

			String code = doc.baseUri().split("=")[1];

			//System.out.print("code : " + code);
			// ------------------------------------------------------------------------

			String tokenUrl = "http://kk.bigk2.com:8080/KOAuthDemeter/accessToken";
			
			conn = Jsoup.connect(tokenUrl);

			conn.data("grant_type", "authorization_code");
			conn.data("client_id", client_id);
			conn.data("client_secret", client_secret);
			conn.data("redirect_uri", "http://www.baidu.com");
			conn.data("code", code);

			doc = conn.post();

			String tokenResp = doc.body().text();

			JSONObject jo = new JSONObject(tokenResp);

			access_token = jo.getString("access_token");
			String refresh_token = jo.getString("refresh_token");

			// ------------------------------------------------------------------------
			//System.out.println("access_token : " + access_token);
			//System.out.println("refresh_token : " + refresh_token);
			
		} catch (Exception e) {
			//e.printStackTrace();
			getPrintErr().print("ERROR IN ACCESS THE TOKEN.");
			getPrintErr().flush();
			System.exit(-1);
		}
		return access_token;
	}

	public static void main(String[] args) 
	{
		args = new String[8];
		args[0] = "0";
		args[1] = "16";
		args[2] = "remoteType";
		args[3] = "1";
		args[4] = "baseOrder";
		args[5] = "Haier&YR-W08";
		args[6] = "extraOrder";
		args[7] = "1.0.0.24";
		if (args == null || args.length == 0) 
		{
			getPrintErr().print("ERROR FOR PARAMETER.");
			getPrintErr().flush();
			System.exit(-1);
		}
		try 
		{
			int idFlag = new Integer(args[0]);
			int index = new Integer(args[1]);
			int value = post(idFlag , index, args);
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
