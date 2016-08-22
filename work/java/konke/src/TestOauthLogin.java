import java.util.List;

import org.json.JSONObject;
import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.FormElement;
import org.jsoup.select.Elements;

public class TestOauthLogin {

	private static final String client_id = "4yCOi48I687EN2Ix";
	private static final String client_secret = "1K742MBPCd5LAL24";

	public static String getAccessToken(String username, String password) {

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

			System.out.println("access_token : " + access_token);
			System.out.println("refresh_token : " + refresh_token);

		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("catch the error");
		}
		return access_token;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
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
