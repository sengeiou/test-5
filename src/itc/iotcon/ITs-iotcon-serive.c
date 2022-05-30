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

//& set: Iotcon

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

static void IotconPinGenCb(const char *pin, void *user_data)
{
}

/**
 * @function 		ITs_iotcon_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */

void ITs_iotcon_service_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bFeatureUnsupported = false;
	if ( !TCTCheckSystemInfoFeatureSupported(IOTCON_FEATURE, API_NAMESPACE) )
	{
		g_bFeatureUnsupported = true;
	}
	return;
}


/**
 * @function 		ITs_iotcon_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_service_cleanup(void)
{
	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose: scenario to connect and disconnect iotcon.
/**
* @testcase 			ITc_iotcon_initialize_deinitialize_p
* @author            	SRID(sk.roy)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			connect and disconnect iotcon.
* @scenario				connect iotcon \n
* 						disconnect iotcon\n
* @apicovered			iotcon_initialize, iotcon_deinitialize
* @passcase				if iotcon_initialize and iotcon_deinitialize passes
* @failcase				if iotcon_initialize or iotcon_deinitialize fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_initialize_deinitialize_p(void)
{
	START_TEST_SERVICE;
	char *svr_db_path;

	ic_get_svr_db_path(&svr_db_path);
   	int nRet = iotcon_initialize(svr_db_path);
	free(svr_db_path);
	if(g_bFeatureUnsupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			return 1;

		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_initialize API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			return 0;
		}
	}
	else
	{
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_initialize", IotConGetError(nRet));
	}

	nRet = iotcon_deinitialize();
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_deinitialize", IotConGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Adds and removes callback to show pin number which is generated automatically.
/**
* @testcase 			ITc_iotcon_add_remove_generated_pin_cb_p
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Adds and removes callback to show pin number which is generated automatically.
* @scenario				Adds callback to show pin number which is generated automatically \n
* 						Removes callback to show pin number which is generated automatically\n
* @apicovered			iotcon_add_generated_pin_cb, iotcon_remove_generated_pin_cb
* @passcase				if iotcon_add_generated_pin_cb and iotcon_remove_generated_pin_cb passes
* @failcase				if iotcon_add_generated_pin_cb or iotcon_remove_generated_pin_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_add_remove_generated_pin_cb_p(void)
{
	START_TEST_SERVICE;
	
   	int nRet = iotcon_add_generated_pin_cb(IotconPinGenCb, NULL);
	if(g_bFeatureUnsupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] iotcon_add_generated_pin_cb API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			return 1;

		}
		else
		{
			FPRINTF("[Line : %d][%s] iotcon_add_generated_pin_cb API call correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, IotConGetError(nRet));
			return 0;
		}
	}
	else
	{
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_add_generated_pin_cb", IotConGetError(nRet));
	}

	nRet = iotcon_remove_generated_pin_cb(IotconPinGenCb);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_remove_generated_pin_cb", IotConGetError(nRet));

	return 0;
}
/** @} */
/** @} */
