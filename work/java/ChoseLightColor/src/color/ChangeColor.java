package color;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.print.attribute.standard.Sides;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.json.JSONException;
import org.json.JSONObject;

import com.philips.lighting.hue.sdk.PHAccessPoint;
import com.philips.lighting.hue.sdk.PHBridgeSearchManager;
import com.philips.lighting.hue.sdk.PHHueSDK;
import com.philips.lighting.hue.sdk.PHMessageType;
import com.philips.lighting.hue.sdk.PHSDKListener;
import com.philips.lighting.hue.sdk.utilities.PHUtilities;
import com.philips.lighting.model.PHBridge;
import com.philips.lighting.model.PHHueParsingError;
import com.philips.lighting.model.PHLight;
import com.philips.lighting.model.PHLightState;

@WebServlet(name = "ChangeColor", value = "/change_color")
public class ChangeColor extends HttpServlet
{

	private static final long serialVersionUID = 1L;
	public static int R, G, B;
	public static PHHueSDK philips;
	public static List<PHLight> lights;
	public static PHBridge bridge;
	public static PHLightState lightState = new PHLightState();

	private static boolean flag = false;

	public static PHSDKListener listener = new PHSDKListener()
	{

		@Override
		public void onParsingErrors(List<PHHueParsingError> arg0)
		{
			// TODO Auto-generated method stub

		}

		@Override
		public void onError(int arg0, String arg1)
		{
			// TODO Auto-generated method stub

		}

		@Override
		public void onConnectionResumed(PHBridge arg0)
		{
			// TODO Auto-generated method stub

		}

		@Override
		public void onConnectionLost(PHAccessPoint arg0)
		{
			// TODO Auto-generated method stub

		}

		@Override
		public void onCacheUpdated(List<Integer> arg0, PHBridge arg1)
		{
			// TODO Auto-generated method stub
			if (arg0.contains(PHMessageType.LIGHTS_CACHE_UPDATED))
			{
				System.out.println("LIGHTS CACHE UPDATED.");
			}
		}

		@Override
		public void onBridgeConnected(PHBridge arg0, String arg1)
		{
			// TODO Auto-generated method stub
			// TODO Auto-generated method stub
			// getPrintWriteOut().print("ON BRIDGE CONNECTED .");

			/*
			 * 
			 * philips.setSelectedBridge(arg0); philips.enableHeartbeat(arg0,
			 * PHHueSDK.HB_INTERVAL);
			 * 
			 * lights =
			 * philips.getSelectedBridge().getResourceCache().getAllLights();
			 * 
			 * System.out.println(lights.size());
			 * 
			 * // System.out.println(lights.size()); PHLightState lightState =
			 * new PHLightState();
			 * 
			 * float xy[] = PHUtilities.calculateXYFromRGB(ChangeColor.R,
			 * ChangeColor.G, ChangeColor.B, lights.get(0).getModelNumber());
			 * lightState.setOn(true); lightState.setX(xy[0]);
			 * lightState.setY(xy[1]);
			 * 
			 * arg0.updateLightState(lights.get(0).getIdentifier(), lightState,
			 * null);
			 * 
			 */

			ChangeColor.bridge = arg0;
			ChangeColor.lights = philips.getSelectedBridge().getResourceCache().getAllLights();

			System.out.println("init size : " + ChangeColor.lights.size());
		}

		@Override
		public void onAuthenticationRequired(PHAccessPoint arg0)
		{
			// TODO Auto-generated method stub

		}

		@Override
		public void onAccessPointsFound(List<PHAccessPoint> arg0)
		{
			// TODO Auto-generated method stub

		}
	};

	static
	{

		philips = PHHueSDK.getInstance();
		philips.getNotificationManager().registerSDKListener(listener);

		PHBridgeSearchManager sm = (PHBridgeSearchManager) philips.getSDKService(PHHueSDK.SEARCH_BRIDGE);
		sm.search(true, true);

		PHAccessPoint accessPoint = new PHAccessPoint();
		accessPoint.setIpAddress(Main.id);
		accessPoint.setUsername(Main.userName);

		philips.connect(accessPoint);

	}

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
	{
		doPost(req, resp);
	}

	@Override
	protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException
	{
		try
		{
			if (this.flag == false)
			{
				flag = true;
				return;
			}

			System.out.println("process post ");
			JSONObject object = CommonHelper.getJsonObject(req);

			ChangeColor.R = object.getInt("R"); // Integer.parseInt(object.getString("R"));
			ChangeColor.G = object.getInt("G");
			ChangeColor.B = object.getInt("B");

			/*
			 * 
			 * PHHueSDK philips = PHHueSDK.getInstance();
			 * philips.getNotificationManager().registerSDKListener(listener);
			 * PHBridgeSearchManager sm = (PHBridgeSearchManager)
			 * philips.getSDKService(PHHueSDK.SEARCH_BRIDGE); sm.search(true,
			 * true); PHAccessPoint accessPoint = new PHAccessPoint();
			 * accessPoint.setIpAddress(Main.id);
			 * accessPoint.setUsername(Main.userName);
			 * 
			 * philips.connect(accessPoint);
			 * 
			 */


				philips.setSelectedBridge(ChangeColor.bridge);
				philips.enableHeartbeat(ChangeColor.bridge, PHHueSDK.HB_INTERVAL);

				System.out.println("GET INT");
				System.out.println(lights.size());

				/*
				 * 
				 * bridge = philips.getSelectedBridge();
				 * 
				 * philips.setSelectedBridge(bridge);
				 * philips.enableHeartbeat(bridge, PHHueSDK.HB_INTERVAL);
				 * 
				 */

				// System.out.println(lights.size());
				
				lightState = new PHLightState(); 
				
				float xy[] = PHUtilities.calculateXYFromRGB(ChangeColor.R, ChangeColor.G, ChangeColor.B,
						lights.get(1).getModelNumber());
				lightState.setOn(true);
				lightState.setX(xy[0]);
				lightState.setY(xy[1]);

				bridge.updateLightState(lights.get(1).getIdentifier(), lightState, null);

		}
		catch (JSONException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
