package Experiment;

import java.io.PrintWriter;
import java.util.List;
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

public class Main
{
	private static final String userName = "pehNjKT6cdWEaSk-uC9T6c4mpw6ecI8kz2zyjRuY";
	private static final String id = "192.168.1.8";
	public static final PHHueSDK philips = PHHueSDK.getInstance();
	public static List<PHLight> lights;
	public static int red = -1, green = -1, blue = -1;
	public static int brightness = -1;
	public static Boolean philipsSwitch = null;
	public static int order;

	private static final PrintWriter pwout = new PrintWriter(System.out, true);
	private static final PrintWriter pwerr = new PrintWriter(System.err, true);

	public static PrintWriter getPrintWriteOut()
	{
		return pwout;
	}

	public static PrintWriter getPrintWriteErr()
	{
		return pwerr;
	}

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
				// getPrintWriteOut().print("LIGHTS CACHE UPDATED.");
				// getPrintWriteOut().flush();
				System.exit(0);
			}
		}

		@Override
		public void onBridgeConnected(PHBridge arg0, String arg1)
		{
			// TODO Auto-generated method stub
			// getPrintWriteOut().print("ON BRIDGE CONNECTED .");
			philips.setSelectedBridge(arg0);
			philips.enableHeartbeat(arg0, PHHueSDK.HB_INTERVAL);
			Main.lights = philips.getSelectedBridge().getResourceCache().getAllLights();

			// System.out.println(lights.size());
			PHLightState lightState = new PHLightState();

			if (brightness != -1)
			{
				lightState.setBrightness(brightness);
				// arg0.updateLightState(lights.get(Main.order).getIdentifier(),
				// lightState, null);
				// System.exit(0);
			}
			else if (red + green + blue != -3)
			{
				float xy[] = PHUtilities.calculateXYFromRGB(red, green, blue, lights.get(0).getModelNumber());
				lightState.setOn(true);
				lightState.setX(xy[0]);
				lightState.setY(xy[1]);
			}
			else if (philipsSwitch != null)
			{
				lightState.setOn(philipsSwitch);
			}

			// lightState.setHue(color);
			// lightState.setOn(false);
			{
				/*
				 * System.out.println("light support brightness : " +
				 * lights.get(0).supportsBrightness());
				 * System.out.println("light support CT : " +
				 * lights.get(0).supportsCT());
				 * System.out.println("light support color : " +
				 * lights.get(0).supportsColor()); System.out.
				 * println("light support last known light statate : " +
				 * lights.get(0).getLastKnownLightState());
				 */
			}
			if (Main.order >= lights.size())
			{
				// getPrintWriteErr().print("ERROR FOR OUT OF BOUNDARY.");
				// getPrintWriteErr().flush();
				System.exit(-1);
			}
			arg0.updateLightState(lights.get(Main.order).getIdentifier(), lightState, null);
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

	public static void main(String[] args)
	{
		int length = args.length;
		if (length != 2 && length != 4)
		{
			System.exit(1);
		}
		if (args.length == 2)
		{
			try
			{
				order = new Integer(args[0]);
				brightness = new Integer(args[1]);
				if (brightness < 0 || brightness > 254)
				{
					System.out.println("ERROR FOR PARAMETER");
					System.exit(-1);
				}
			}
			catch (NumberFormatException exception)
			{
				order = new Integer(args[0]);
				philipsSwitch = new Boolean(args[1]);
			}
			catch (Exception e)
			{
				System.exit(-1);
			}
		}
		else
		{
			order = new Integer(args[0]);
			red = new Integer(args[1]);
			green = new Integer(args[2]);
			blue = new Integer(args[3]);
			// getPrintWriteOut().print("MODE FOR COLOR.");
		}
		// System.out.println(color);
		PHHueSDK philips = PHHueSDK.getInstance();
		philips.getNotificationManager().registerSDKListener(listener);
		PHBridgeSearchManager sm = (PHBridgeSearchManager) philips.getSDKService(PHHueSDK.SEARCH_BRIDGE);
		sm.search(true, true);
		PHAccessPoint accessPoint = new PHAccessPoint();
		accessPoint.setIpAddress(Main.id);
		accessPoint.setUsername(Main.userName);
		philips.connect(accessPoint);

		/*
		 * PHBridge bridge = philips.getSelectedBridge();
		 * 
		 * List<PHLight> lights = bridge.getResourceCache().getAllLights();
		 * 
		 * System.out.println(lights.size());
		 * 
		 * philips.disableAllHeartbeat(); philips.destroySDK();
		 */
		/*
		 * PHHeartbeatManager beatManager = PHHeartbeatManager.getInstance();
		 * PHBridgeResourcesCache cache =
		 * philips.getSelectedBridge().getResourceCache(); List <PHLight> lights
		 * = cache.getAllLights(); PHBridge bridge =
		 * PHHueSDK.getInstance().getSelectedBridge(); PHLightState status = new
		 * PHLightState(); status.setHue(12345);
		 */
	}
}
