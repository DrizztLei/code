import java.util.ArrayList;
public class method 
{

	private static ArrayList<subMethod> method = new ArrayList<subMethod>();

	private final static String client_name = "elvis.linuxer@gmail.com";
	private final static String userid = "elvis.linuxer@gmail.com";
	private final static String client_id = "4yCOi48I687EN2Ix";
	private final static String client_secret = "1K742MBPCd5LAL24";
	private final static String access_token = "155bbd381a287e9b505e987379fa685e";
	private final static String kid = "d9b6073f-e334-49a6-af5c-e1b6e8516ae9";
	private final static String mac = "28-d9-8a-06-d2-41";
	private final static String prefix = "http://kk.bigk2.com:8080/KOAuthDemeter/";

	public static ArrayList<subMethod> getMethod() 
	{
		return method;
	}

	public String getURL(int index) 
	{
		return getMethod().get(index).getMethodName();
	}

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

	/*
	 * private static String getMAC() { return mac; }
	 */
	private static String getPrefix() 
	{
		return prefix;
	}

	public static String setParameter(String[] info) 
	{

		// RequestParamsBean params = new RequestParamsBean();
		// params.setUserid(getUserID());

		int start = 1, step = 2;

		String msg = "{";
		msg += "\"userid\":\"" + getUserID() + "\"," + "\"kid\":\"" + getKID() + "\"";
		if (info.length != 1) 
		{
			msg += ",";
		}
		for (int i = start; i < info.length; i += step) 
		{
			msg += "\"" + info[i] + "\":\"" + info[i + 1] + "\"";
			if (i + step != info.length) 
			{
				msg += ",";
			}
		}

		msg += "}";
		return msg;
	}

	public static void append(String name) 
	{
		getMethod().add(new subMethod(name));
	}

	static 
	{
		getMethod().add(new subMethod(getPrefix()));
		getMethod().add(new subMethod(getPrefix() + "User/getAvater"));
		getMethod().add(new subMethod(getPrefix() + "User/getKList"));
		getMethod().add(new subMethod(getPrefix() + "KControl/doSwitchK"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKTimerList"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKElectricity"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKDelayOpenInfo"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKState"));
		getMethod().add(new subMethod(getPrefix() + "User/getKInfo"));
		getMethod().add(new subMethod(getPrefix() + "User/switchKLight"));
		getMethod().add(new subMethod(getPrefix() + "User/getKLightInfo"));
		getMethod().add(new subMethod(getPrefix() + "User/getKSceneList"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKDelayCloseInfo"));
		getMethod().add(new subMethod(getPrefix() + "User/getGeneralRemoteList"));
		getMethod().add(new subMethod(getPrefix() + "KControl/sendGeneralRemoteOrder"));
		getMethod().add(new subMethod(getPrefix() + "User/getAirConditionerRemoteList"));
		getMethod().add(new subMethod(getPrefix() + "KControl/sendAirConditionerOrder"));
		getMethod().add(new subMethod(getPrefix() + "User/setTimerTask"));
		getMethod().add(new subMethod(getPrefix() + "User/removeTimeTask"));
		getMethod().add(new subMethod(getPrefix() + "User/setDelayTask"));
		getMethod().add(new subMethod(getPrefix() + "User/removeDelayTask"));
		getMethod().add(new subMethod(getPrefix() + "User/openChargingProtection"));
		getMethod().add(new subMethod(getPrefix() + "User/closeChargingProtection"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getSingleKStatus"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getEnviromentInfo"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKHumanInfo"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKLatesHumanInfo"));
		getMethod().add(new subMethod(getPrefix() + "User/uploadKSceneList"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKOnlineStatus"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKElectricityByMonth"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKElectricityByDay"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKElectricityByHour"));
		getMethod().add(new subMethod(getPrefix() + "User/uploadSceneByIndex"));
		getMethod().add(new subMethod(getPrefix() + "User/downloadSceneByIndex"));
		getMethod().add(new subMethod(getPrefix() + "User/deleteSceneByIndex"));
		getMethod().add(new subMethod(getPrefix() + "CheckAccessToken"));
		getMethod().add(new subMethod(getPrefix() + "User/putLinkage"));
		getMethod().add(new subMethod(getPrefix() + "User/getMultipleKOnlineStatus"));
		getMethod().add(new subMethod(getPrefix() + "User/queryUserId"));
		getMethod().add(new subMethod(getPrefix() + "User/verificateAccessToken"));
		getMethod().add(new subMethod(getPrefix() + "KControl/enableWiFiBridge"));
		getMethod().add(new subMethod(getPrefix() + "disableWiFiBridge"));
	}
}
