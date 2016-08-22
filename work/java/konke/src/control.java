import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

import com.google.gson.Gson;

public class control {

	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/User/verificateAccessToken";
	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/User/getKList";
	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/User/getKLightInfo";
	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/KControl/doSwitchK";
	private static final String ADD_URL = "http://kk.bigk2.com:8080/KOAuthDemeter/User/switchKLight";
	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/User/getKLightInfo";
	// private static final String ADD_URL =
	// "http://kk.bigk2.com:8080/KOAuthDemeter/User/getAvatar";
	private static final String token = "155bbd381a287e9b505e987379fa685e";
	private static final String kid = "d9b6073f-e334-49a6-af5c-e1b6e8516ae9";
	private static final String userid = "elvis.linuxer@gmail.com";

	public static void appadd() throws IOException {

		/*
		 * // 创建连接 URL url = new URL(ADD_URL); HttpURLConnection connection =
		 * (HttpURLConnection) url.openConnection();
		 * connection.setDoOutput(true); connection.setDoInput(true);
		 * connection.setRequestMethod("POST"); connection.setUseCaches(false);
		 * connection.setInstanceFollowRedirects(true);
		 * //connection.setRequestProperty("Content-Type",
		 * "application/x-www-form-urlencoded"); //conn.header("Authorization",
		 * "Bearer " + token); connection.setRequestProperty("Authorization",
		 * "Bearer 155bbd381a287e9b505e987379fa685e");
		 * 
		 * connection.connect();
		 * 
		 * // POST请求 DataOutputStream out = new
		 * DataOutputStream(connection.getOutputStream()); JSONObject obj = new
		 * JSONObject();
		 * 
		 * //obj.element("app_name", "asdf"); //obj.append("app_name", "asdf");
		 * //obj.element("app_ip", "10.21.243.234"); //obj.append("app_ip",
		 * "10.21.243.234"); //obj.element("app_port", 8080);
		 * //obj.append("app_port", 8080); //obj.element("app_type", "001");
		 * //obj.append("app_type", "001"); //obj.element("app_area", "asd");
		 * //obj.append("app_area", "asd");
		 * 
		 * obj.append("username", "elvis.linuxer@gmail.com");
		 * out.writeBytes(obj.toString()); out.flush(); out.close();
		 * 
		 * // 读取响应 /* BufferedReader reader = new BufferedReader(new
		 * InputStreamReader(connection.getInputStream())); String lines;
		 * StringBuffer sb = new StringBuffer(""); while ((lines =
		 * reader.readLine()) != null) { lines = new String(lines.getBytes(),
		 * "utf-8"); sb.append(lines); } System.out.println(sb); reader.close();
		 */
		// 断开连接
		/*
		 * connection.disconnect();
		 */

		URL url = new URL(ADD_URL); // 创建连接
		HttpURLConnection connection = (HttpURLConnection) url.openConnection();
		connection.setDoOutput(true);
		connection.setDoInput(true);
		connection.setUseCaches(false);
		connection.setInstanceFollowRedirects(true);
		connection.setRequestMethod("POST"); // 设置请求方式
		connection.setRequestProperty("Accept", "application/json"); // 设置接收数据的格式
		connection.setRequestProperty("Content-Type", "application/json"); // 设置发送数据的格式
		connection.setRequestProperty("Accept-Encoding", "identity");
		connection.setRequestProperty("Authorization", "Bearer " + token);

		connection.connect();

		RequestParamsBean params = new RequestParamsBean();

		params.setUserid(userid);
		params.setKid(kid);
		params.setKey("open");

		String msg = new Gson().toJson(params);

		// 向服务器POST信息
		if (null != msg && msg.length() > 0) {
			OutputStreamWriter out = new OutputStreamWriter(connection.getOutputStream(), "UTF-8"); // 服务器采用UTF-8编码
			out.append(msg);
			out.flush();
			out.close();
		}

		// 读取服务器响应(最大长度10K)
		int length = 10 * 1024;
		// int length =connection.getContentLength();// 获取长度,这里一直返回0,不知道什么原因
		InputStream is = connection.getInputStream();
		if (length != -1) {
			byte[] data = new byte[length];
			byte[] temp = new byte[512];// 每次读取512字节
			int readLen = 0;// 单次读取的长度
			int destPos = 0;// 总字节数
			while ((readLen = is.read(temp)) > 0) {
				System.arraycopy(temp, 0, data, destPos, readLen);
				destPos += readLen;
			}
			String result = new String(data, "UTF-8"); // 响应也是UTF-8编码
			System.out.println("服务器返回结果：" + result);
		}
	}

	public static void main(String[] args) {
		try {
			appadd();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
