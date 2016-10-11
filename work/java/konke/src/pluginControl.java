import java.io.IOException;
import java.util.List;

import org.json.JSONObject;
import org.jsoup.Connection;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.FormElement;
import org.jsoup.select.Elements;

public class pluginControl {
	private static final String token = "155bbd381a287e9b505e987379fa685e";
	public static String getID() throws IOException
	{
		Connection conn = null;
		String url = "http://kk.bigk2.com:8080/KOAuthDemeter/User/queryUserId";
		
		conn = Jsoup.connect(url);
		
		conn.header("Authorization", "Bearer " + token);
		
		conn.data("username" , "elvis.linuxer@gmail.com");
				
		Document doc = conn.post();
		
		String text= doc.body().text();
		
		System.out.println(doc.body());
		
		System.out.println(text);
		
		JSONObject jo=new JSONObject(text);
		
		String reqId = jo.getString("reqId");
		String result = jo.getString("result");
		String username = jo.getString("username");
		String des = jo.getString("des");
		String userid = jo.getString("userid");
		
		if(result.hashCode() == "-1".hashCode() )
		{
			return null;
		}
		else
		{
			return userid;
		}
	}
	
	public static void main(String [] args)
	{
		try {
			String id = getID();
			System.out.println(id);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
