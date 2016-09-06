package Experiment;

import java.awt.image.AreaAveragingScaleFilter;
import java.io.PrintWriter;
import java.lang.reflect.Parameter;
import java.util.List;
import com.philips.lighting.hue.sdk.PHAccessPoint;
import com.philips.lighting.hue.sdk.PHBridgeSearchManager;
import com.philips.lighting.hue.sdk.PHHueSDK;
import com.philips.lighting.hue.sdk.PHMessageType;
import com.philips.lighting.hue.sdk.PHSDKListener;
import com.philips.lighting.model.PHBridge;
import com.philips.lighting.model.PHHueParsingError;
import com.philips.lighting.model.PHLight;


public class Read {
	public static final PHHueSDK philips = PHHueSDK.getInstance();
	public static List<PHLight> lights;
	public static int red = 255, green = 255 , blue = 255;
	public static int brightness = -1;
	public static boolean philipsSwitch = true;
	
	private static final PrintWriter pwout = new PrintWriter(System.out , true);
	private static final PrintWriter pwerr = new PrintWriter(System.err , true);
	private static String paramter = "";
	
	public static String getParamter()
	{
		return paramter;
	}
	
	public static void setParameter(String para)
	{
		paramter = para;
	}
	
	public static PrintWriter getPrintWriteOut()
	{
		return pwout;
	}
	
	public static PrintWriter getPrintWriteErr()
	{
		return pwerr;
	}

	public static PHSDKListener listener = new PHSDKListener() {

		@Override
		public void onParsingErrors(List<PHHueParsingError> arg0) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onError(int arg0, String arg1) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onConnectionResumed(PHBridge arg0) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onConnectionLost(PHAccessPoint arg0) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onCacheUpdated(List<Integer> arg0, PHBridge arg1) {
			// TODO Auto-generated method stub
			if (arg0.contains(PHMessageType.LIGHTS_CACHE_UPDATED)) {
				System.exit(0);
			}
		}

		@Override
		public void onBridgeConnected(PHBridge arg0, String arg1) {
			// TODO Auto-generated method stub

			//System.out.println(lights.size());
			//System.out.println(lights.get(0).getName());
			//getPrintWriteOut().println(lights.get(0).getModelNumber());
			philips.setSelectedBridge(arg0);
			philips.enableHeartbeat(arg0, PHHueSDK.HB_INTERVAL);
			Read.lights = philips.getSelectedBridge().getResourceCache().getAllLights();
			if(getParamter().hashCode() == "brightness".hashCode())
			{
				getPrintWriteOut().print(lights.get(0).getLastKnownLightState().getBrightness().toString());
				getPrintWriteOut().flush();
				System.exit(0);
			}
			else
			{
				getPrintWriteErr().print("ERROR FOR INPUT");
				getPrintWriteErr().flush();
				System.exit(-1);
			}
			/*
			Main.
			
			{
				System.out.println("light support brightness : " + lights.get(0).supportsBrightness());
				System.out.println("light support CT : " + lights.get(0).supportsCT());
				System.out.println("light support color : " + lights.get(0).supportsColor());
				System.out.println("light support last known light statate : " + lights.get(0).getLastKnownLightState());
				getPrintWriteOut().println(lights.get(0).getModelNumber());
			}
			arg0.updateLightState(lights.get(0).getIdentifier(), null , null);
			*/
			
			// System.out.println(lights.size());
			//PHLightState lightState = new PHLightState();
			//float xy[] = PHUtilities.calculateXYFromRGB(red, green, blue, lights.get(0).getModelNumber());
			/*
			if(brightness != -1)
			{
				lightState.setBrightness(brightness);	
			}
			
			lightState.setOn(philipsSwitch);
			lightState.setX(xy[0]);
			lightState.setY(xy[1]);
			*/
			//lightState.setHue(color);
			// lightState.setOn(false);
			//arg0.updateLightState(lights.get(0).getIdentifier(), lightState, null);
		}

		@Override
		public void onAuthenticationRequired(PHAccessPoint arg0) {
			// TODO Auto-generated method stub

		}

		@Override
		public void onAccessPointsFound(List<PHAccessPoint> arg0) {
			// TODO Auto-generated method stub
		}
	};

	public static void main(String[] args) {
		
		if (args.length != 1 )
		{
			getPrintWriteErr().println("ERROR FOR PARAMETER" );
			System.exit(1);
		}
		setParameter(args[0]);
		// System.out.println(color);
		PHHueSDK philips = PHHueSDK.getInstance();
		philips.getNotificationManager().registerSDKListener(listener);
		PHBridgeSearchManager sm = (PHBridgeSearchManager) philips.getSDKService(PHHueSDK.SEARCH_BRIDGE);
		sm.search(true, true);
		PHAccessPoint accessPoint = new PHAccessPoint();
		accessPoint.setIpAddress("192.168.1.8");
		accessPoint.setUsername("pehNjKT6cdWEaSk-uC9T6c4mpw6ecI8kz2zyjRuY");
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
