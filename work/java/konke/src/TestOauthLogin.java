import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.util.List;

import javax.naming.spi.DirStateFactory.Result;

import org.json.JSONObject;
import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.FormElement;
import org.jsoup.select.Elements;


public class TestOauthLogin {

	private static final String client_id = "4yCOi48I687EN2Ix";
	private static final String client_secret = "1K742MBPCd5LAL24";

	public static String getAccessToken(String username, String password) throws IOException {
		/*
		String access_token = null;

		try {

			Connection conn = null;

			String url = "http://kk.bigk2.com:8080/KOAuthDemeter/authorize?response_type=code&client_id=" + client_id
					+ "&redirect_uri=http://www.baidu.com";
			conn = Jsoup.connect(url);
			Document doc = conn.get();

			// System.out.println(doc.toString());

			List<FormElement> formList = doc.getAllElements().forms();
			if (formList.size() > 0) {
				FormElement form = formList.get(0);
				Elements usernameInput = form.select("input[name=username]");
				Elements passwordInput = form.select("input[name=password]");
				usernameInput.attr("value", username);
				passwordInput.attr("value", password);

				conn = form.submit();
				doc = conn.post();
			}

			String code = doc.baseUri().split("=")[1];

			System.out.println("code : " + code);

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
			System.err.println("Error in access the token .");
			System.exit(-1);
		}
		return access_token;
		*/
		URL url = new URL("https://open.ys7.com:443/api/lapp/token/get");

		HttpURLConnection connection = (HttpURLConnection) url.openConnection();

		connection.setDoOutput(true);
		connection.setDoInput(true);
		connection.setUseCaches(false);
		connection.setInstanceFollowRedirects(true);
		connection.setRequestMethod("POST"); // 设置请求方式
		connection.setRequestProperty("Accept", "application/json"); // 设置接收数据的格式
		connection.setRequestProperty("Content-Type", "application/json"); // 设置发送数据的格式
		//connection.setRequestProperty("Accept-Encoding", "identity");
		//connection.setRequestProperty("Authorization", "Bearer " + getAccessToken());

		connection.connect();

		//getMethod();
		String msg = "appKey=c295e6dc623e4f03a0d915e43bdb0ae3&appSecret=ccb7eaa12d2b3f6108c3bb4657bc92b1";
		
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
			System.out.print(result);
		}
		return null;
	}

	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		getAccessToken("elvis.linuxer@gmail.com", "Idon'tknow");
		/*
		 * result for 
		 * code : 
		 * 5cd51124f86c27f7f069a4bff2dfa969 
		 * access_token :
		 * 155bbd381a287e9b505e987379fa685e 
		 * refresh_token :
		 * 39eb5e709bd37b4214c13e9f97f750f2
		 */
	}

}
