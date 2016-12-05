package color;

import java.io.BufferedReader;
import java.io.IOException;

import javax.servlet.http.HttpServletRequest;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class CommonHelper
{

	public static String getJson(HttpServletRequest req)
	{
		BufferedReader reader;
		try
		{
			reader = new BufferedReader(req.getReader());
			String json = "";
			String temp;
			while ((temp = reader.readLine()) != null)
				json += temp;
			return json;
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return null;
	}

	public static JSONObject getJsonObject(HttpServletRequest req) throws JSONException
	{
		BufferedReader reader;
		try
		{
			reader = new BufferedReader(req.getReader());
			String json = "";
			String temp;
			while ((temp = reader.readLine()) != null)
				json += temp;
			System.out.println(json);
			return new JSONObject(json);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return null;
	}

	public static JSONArray getJSONArray(HttpServletRequest req) throws JSONException
	{
		BufferedReader reader;
		try
		{
			reader = new BufferedReader(req.getReader());
			String json = "";
			String temp;
			while ((temp = reader.readLine()) != null)
				json += temp;
			return new JSONArray(json);
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		return null;
	}
}
