import java.util.ArrayList;
public class kID 
{

	private static ArrayList<subkID> id = new ArrayList<subkID>();

	//private final static String prefix = "http://kk.bigk2.com:8080/KOAuthDemeter/";

	public static ArrayList<subkID> getKID() 
	{
		return id;
	}

	public String getID(int index) 
	{
		return getKID().get(index).getIDName();
	}

	public static void append(String name) 
	{
		getKID().add(new subkID(name));
	}

	static 
	{
		/*
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
		getMethod().add(new subMethod(getPrefix() + "KInfo/getEnvironmentInfo"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKHumanInfo"));
		getMethod().add(new subMethod(getPrefix() + "KInfo/getKLatestHumanInfo"));
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
		*/
		getKID().add(new subkID("d9b6073f-e334-49a6-af5c-e1b6e8516ae9"));
		getKID().add(new subkID("2ac73cd5-0abe-422c-88c3-22f5116d695f"));
	}
}
