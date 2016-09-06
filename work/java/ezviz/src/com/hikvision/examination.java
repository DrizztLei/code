package com.hikvision;

import java.util.HashMap;
import java.util.Map;

public class examination extends PublicControllerTest{
	
	public static void main(String[] args)
	{
			examination emit = new examination();
			Map<String, Object> parameter = new HashMap<>();
			
			parameter.put("accessToken", "at.26jzrnh46galxx9i4sxb0r616llk2zeo-3r7y5jmlnk-0htw8kf-dphpcxywt");
			//parameter.put("deviceSerial", "624233133");			
			//parameter.put("channelNo", 1);
			for(int i = 1 ; i < args.length ; i+=2)
			{
				parameter.put(args[i], args[i+1]);
			}
			
			//Map<String, Object> map = emit.paramsInit("camera/getCameraInfo" , parameter);
			Map<String, Object> map = emit.paramsInit(args[0],parameter);
			emit.doPost(map);
	}
}
