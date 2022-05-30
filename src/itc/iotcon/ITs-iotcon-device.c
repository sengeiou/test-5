//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "ITs-iotcon-common.h"

bool g_Error;
//& set: Iotcon

/**
* @function 		IotconGetDeviceInfoCB
* @description	 	Callback Function
* @parameter		iotcon_device_info_h info, iotcon_error_e result,void *user_data
* @return 			bool
*/
static bool IotconGetDeviceInfoCB(iotcon_device_info_h info, iotcon_error_e result,void *user_data)
{
	if ( info == NULL )
	{
		FPRINTF("[Line : %d][%s] Callback invoked ,info is NULL \\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);
	}

	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	
	return true;
}

/**
* @function 		IotconGetPlatformInfoCB
* @description	 	Callback Function
* @parameter		iotcon_platform_info_h info, iotcon_error_e result,void *user_data
* @return 			bool
*/
static bool IotconGetPlatformInfoCB(iotcon_platform_info_h info,iotcon_error_e result, void *user_data)
{
	if ( info == NULL )
	{
		FPRINTF("[Line : %d][%s] Callback invoked for get platform info. info is NULL \\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Callback invoked for get platform info\\n", __LINE__, API_NAMESPACE);
	}

	g_bCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	return true;
}

/**
* @function 		IotconDeviceInfoGetPropertyCB
* @description	 	Callback Function
* @parameter		iotcon_device_info_h info, iotcon_error_e result,void *user_data
* @return 			NA
*/

static bool IotconDeviceInfoGetPropertyCB(iotcon_device_info_h info, iotcon_error_e result,void *user_data)
{
	if ( info == NULL )
	{
		FPRINTF("[Line : %d][%s] Callback invoked for device_info_get_property. info is NULL \\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Callback invoked. \\n", __LINE__, API_NAMESPACE);
	}
	
	g_bCheckCb = true;

	char *pszValue = NULL;

	int nGetPropertyOption[] = {
			IOTCON_DEVICE_INFO_NAME ,
			IOTCON_DEVICE_INFO_SPEC_VER,
			IOTCON_DEVICE_INFO_ID,
			IOTCON_DEVICE_INFO_DATA_MODEL_VER,

		};
	int nRet = -1;
	int nEnumStartCount = 0 ;

	int nGetPropertyOptionCount = sizeof(nGetPropertyOption) / sizeof(nGetPropertyOption[0]);

	for(nEnumStartCount = 0 ; nEnumStartCount < nGetPropertyOptionCount ; nEnumStartCount++ )
	{
		nRet = iotcon_device_info_get_property(info, nGetPropertyOption[nEnumStartCount],&pszValue);
		if (IOTCON_ERROR_NONE != nRet)
		{
			g_Error = true;
			FPRINTF("[Line : %d][%s] iotcon_device_info_get_property failed for enum: %d Error: %s\\n", __LINE__, API_NAMESPACE, nEnumStartCount, IotConGetError(nRet));
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
				g_pMainLoop = NULL;
			}
			return false;
		}
		FPRINTF(" property  =  [EnumVal : %d][ Value  : %s]  \\n", nEnumStartCount, pszValue);
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	return true;
}

/**
* @function 		IotconPlatformInfoGetPropertyCB
* @description	 	Callback Function
* @parameter		iotcon_platform_info_h info, iotcon_error_e result,void *user_data
* @return 			NA
*/

static bool IotconPlatformInfoGetPropertyCB(iotcon_platform_info_h info, iotcon_error_e result, void *user_data)
{
	if ( info == NULL )
	{
		FPRINTF("[Line : %d][%s] Callback invoked for device_info_get_property. Info is NULL \\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Callback invoked. \\n", __LINE__, API_NAMESPACE);
	}
	g_bCheckCb = true;

	char *pszValue = NULL;

	int nGetPropertyOption[] = {
			IOTCON_PLATFORM_INFO_ID ,
			IOTCON_PLATFORM_INFO_MANUF_NAME,
			IOTCON_PLATFORM_INFO_MANUF_URL,
			IOTCON_PLATFORM_INFO_MODEL_NUMBER,
			IOTCON_PLATFORM_INFO_DATE_OF_MANUF ,
			IOTCON_PLATFORM_INFO_PLATFORM_VER,
			IOTCON_PLATFORM_INFO_OS_VER,
			IOTCON_PLATFORM_INFO_HARDWARE_VER,
			IOTCON_PLATFORM_INFO_FIRMWARE_VER,
			IOTCON_PLATFORM_INFO_SUPPORT_URL,
			IOTCON_PLATFORM_INFO_SYSTEM_TIME,

	};
	int nRet = -1;
	int nEnumStartCount = 0 ;

	int nGetPropertyOptionCount = sizeof(nGetPropertyOption) / sizeof(nGetPropertyOption[0]);

	for(nEnumStartCount = 0 ; nEnumStartCount < nGetPropertyOptionCount ; nEnumStartCount++ )
	{
		nRet = iotcon_platform_info_get_property(info, nGetPropertyOption[nEnumStartCount],&pszValue);
		if (IOTCON_ERROR_NONE != nRet)
		{
			g_Error = true;
			FPRINTF("[Line : %d][%s] iotcon_platform_info_get_property failed for enum: %d Error: %s\\n", __LINE__, API_NAMESPACE, nEnumStartCount, IotConGetError(nRet));
			if ( g_pMainLoop )
			{
				g_main_loop_quit(g_pMainLoop);
				g_pMainLoop = NULL;
			}
			return false;
		}
		FPRINTF(" property  =  [EnumVal : %d][ Value  : %s]  \\n",nEnumStartCount, pszValue);
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	return true;
}

/**
 * @function 		ITs_iotcon_device_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */

void ITs_iotcon_device_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;
	g_Error = false;
	
	ic_get_svr_db_path(&svr_db_path);
   int nRet = iotcon_initialize(svr_db_path);
   free(svr_db_path);
	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bIotconConnect = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			g_bFeatureUnsupported = true;
		}
		return;
	}

	if ( nRet != IOTCON_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] iotcon_initialize failed API return %s error \\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
		g_bIotconConnect = false;
		return;
	}

	return;
}

/**
 * @function 		ITs_iotcon_device_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_device_cleanup(void)
{
	if( g_bIotconConnect )
	{
		iotcon_deinitialize();

	}
	return;
}

//& type: auto
//& purpose:  scenario to find device value in iotcon device
/**
* @testcase   			ITc_iotcon_find_device_info_p
* @author             	SRID(arvind.ky)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get device info in iotcon device.
* @scenario				connect device \n
*						iotcon_find_device_info \n
* @apicovered			iotcon_initialize, iotcon_find_device_info
* @passcase				If iotcon_find_device_info passes.
* @failcase				If iotcon_find_device_info fails.
* @precondition			create device
* @postcondition		NA
*/

int ITc_iotcon_find_device_info_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
    g_bCheckCb = false;
	
	int nRet = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP, NULL, IotconGetDeviceInfoCB, NULL);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_find_device_info", IotConGetError(nRet));

	RUN_POLLING_LOOP;

	if(g_bCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to get property info in iotcon device
/**
* @testcase   			ITc_iotcon_device_info_get_property_p
* @author             	SRID(arvind.ky)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			scenario to get device info in iotcon device..
* @scenario				connect device \n
*						iotcon_find_device_info \n
* @apicovered			iotcon_initialize, iotcon_device_info_get_property
* @passcase				If iotcon_device_info_get_property passes.
* @failcase				If iotcon_device_info_get_property fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_device_info_get_property_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
    g_bCheckCb = false;
	g_Error = false;
	
	int nRet = iotcon_find_device_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP, NULL, IotconDeviceInfoGetPropertyCB, NULL);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_find_device_info", IotConGetError(nRet));

	RUN_POLLING_LOOP;

	if(g_bCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	if(g_Error == true)
	{
		FPRINTF("[Line : %d][%s] iotcon_device_info_get_property failed : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	
    return 0;
}

//& type: auto
//& purpose:  scenario to get platform info in iotcon device
/**
* @testcase   			ITc_iotcon_find_platform_info_p
* @author             	SRID(arvind.ky)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To extract representative colour from an image buffer.
* @scenario				connect device \n
*						iotcon_find_platform_info \n
* @apicovered			iotcon_initialize, iotcon_find_platform_info
* @passcase				If iotcon_find_platform_info passes.
* @failcase				If iotcon_find_platform_info fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_find_platform_info_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
	g_bCheckCb = false;
	
	int nRet = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP, NULL, IotconGetPlatformInfoCB, NULL);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_find_platform_info", IotConGetError(nRet));

	RUN_POLLING_LOOP;

	if(g_bCheckCb != true)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:  scenario to get platform info in iotcon device
/**
* @testcase   			ITc_iotcon_platform_info_get_property_p
* @author             	SRID(arvind.ky)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			To extract representative colour from an image buffer.
* @scenario				connect device \n
*						iotcon_find_device_info \n
* @apicovered			iotcon_initialize, iotcon_platform_info_get_property
* @passcase				If iotcon_platform_info_get_property passess.
* @failcase				If iotcon_platform_info_get_property fails.
* @precondition			create device
* @postcondition		NA
*/
int ITc_iotcon_platform_info_get_property_p(void)
{
	START_TEST;
	int nIotconTimeoutId = 0;
	g_bCheckCb = false;
	g_Error = false;
	
	int nRet = iotcon_find_platform_info(IOTCON_MULTICAST_ADDRESS, IOTCON_CONNECTIVITY_IP, NULL, IotconPlatformInfoGetPropertyCB, NULL);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_find_platform_info", IotConGetError(nRet));

	RUN_POLLING_LOOP;

	if(g_bCheckCb == false)
	{
		FPRINTF("[Line : %d][%s] callback not invoked : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}
	if(g_Error == true)
	{
		FPRINTF("[Line : %d][%s] iotcon_platform_info_get_property failed : \\n", __LINE__, API_NAMESPACE );
		return 1;
	}

	return 0;
}

/** @} */
/** @} */