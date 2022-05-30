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
bool g_bCallbackHit = false;


/**
 * @function 		ITs_iotcon_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */

void ITs_iotcon_startup(void)
{
	struct stat stBuff;
	char *svr_db_path;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIotconConnect = true;
	g_bFeatureUnsupported = false;

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
 * @function 		ITs_iotcon_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_cleanup(void)
{
	if( g_bIotconConnect )
	{
		iotcon_deinitialize();

	}
	return;
}

/** @addtogroup itc-iotcon-testcases
*  @brief 		Integration testcases for module iotcon
*  @ingroup 	itc-iotcon
*  @{
*/

//& type: auto
//& purpose:  scenario to create and destroy iotcon list
/**
* @testcase 			ITc_iotcon_set_get_timeout_p
* @author            	SRID(sk.roy)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			sets and gets timeout value in seconds
* @scenario				sets timeout value \n
* 						gets timeout value\n
* @apicovered			iotcon_set_timeout, iotcon_get_timeout
* @passcase				if iotcon_set_timeout and iotcon_get_timeout passes
* @failcase				if iotcon_set_timeout or iotcon_get_timeout fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_set_get_timeout_p(void)
{
	START_TEST;

	int nTimeoutSec = 0;

	int nRet = iotcon_set_timeout(IOTCON_TIMEOUT);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_set_timeout", IotConGetError(nRet));

	nRet = iotcon_get_timeout(&nTimeoutSec);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_get_timeout", IotConGetError(nRet));

	if(nTimeoutSec != IOTCON_TIMEOUT)
	{
		FPRINTF("[Line : %d][%s] Failed testcase, as value set by API iotcon_set_timeout is not same as provided by API iotcon_get_timeout : \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
//& type: auto
//& purpose:  set the device name
/**
* @testcase 			ITc_iotcon_set_get_polling_interval_p
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @since_tizen 			3.0
* @description			sets the device name
* @scenario				sets the device name *
* @apicovered			iotcon_set_device_name
* @passcase				if iotcon_set_device_name passes
* @failcase				if iotcon_set_device_name fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_set_device_name_p(void)
{
	START_TEST;
	 char*pszDeviceName = "device_name";
	int nRet = iotcon_set_device_name(pszDeviceName);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_set_device_name", IotConGetError(nRet));

    return 0;
}


#if 0
//& type: auto
//& purpose:  scenario to create and destroy iotcon list
/**
* @testcase 			ITc_iotcon_set_get_polling_interval_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			sets and gets polling value
* @scenario				sets polling value \n
* 						gets polling value\n
* @apicovered			iotcon_polling_set_interval, iotcon_polling_get_interval
* @passcase				if iotcon_polling_set_interval and iotcon_polling_get_interval passes
* @failcase				if iotcon_polling_set_interval or iotcon_polling_get_interval fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_set_get_polling_interval_p(void)
{
	START_TEST;
	int nRet;
	int getInterval;
	int setInterval = 100;

	nRet = iotcon_polling_set_interval(setInterval);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_polling_set_interval", IotConGetError(nRet));

	nRet = iotcon_polling_get_interval(&getInterval);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_polling_get_interval", IotConGetError(nRet));

	if(setInterval != getInterval)
	{
		FPRINTF("[Line : %d][%s] Failed testcase, as value set by API is not same as provided by get API: \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose:  scenario to create and destroy iotcon list
/**
* @testcase 			ITc_iotcon_polling_invoke_p
* @author            	SRID(asit.s)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			iotcon polling invoke
* @scenario				polling invoke \n
* @apicovered			iotcon_polling_invoke
* @passcase				if iotcon_polling_invoke passes
* @failcase				if iotcon_polling_invoke fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_polling_invoke_p(void)
{
	START_TEST;

	int nRet = iotcon_polling_invoke();
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_polling_invoke", IotConGetError(nRet));

	return 0;
}
#endif

/** @} */
/** @} */
