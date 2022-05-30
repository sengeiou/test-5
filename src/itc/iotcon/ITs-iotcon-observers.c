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
iotcon_observers_h g_hIotconObservers = NULL;


/**
 * @function 		ITs_iotcon_observers_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_observers_startup(void)
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

	nRet = iotcon_observers_create(&g_hIotconObservers);
	if (IOTCON_ERROR_NONE != nRet)
	{
		FPRINTF("[Line : %d][%s] iotcon_observers_create fail in startup error returned : \\n", __LINE__, API_NAMESPACE);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}

	if( g_hIotconObservers == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_observers_create failed ,as g_hIotconObservers is NULL : \\n", __LINE__, API_NAMESPACE);
		iotcon_deinitialize();
		g_bIotconConnect = false;
		return;
	}

	return;
}


/**
 * @function 		ITs_iotcon_observers_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_observers_cleanup(void)
{
	if(g_hIotconObservers)
	{
		iotcon_observers_destroy(g_hIotconObservers);
	}

	if( g_bIotconConnect )
	{
		iotcon_deinitialize();
	}
	return;
}

//& type: auto
//& purpose: Creates and destroy a new observers handle.
/**
* @testcase 			ITc_iotcon_observers_create_destroy_p
* @author            	SRID(sk.roy)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Creates and destroy a new observers handle.
* @scenario				Creates new observers handle \n
* 						destroy a new observers handle \n
* @apicovered			iotcon_observers_destroy, iotcon_observers_create
* @passcase				if iotcon_observers_destroy and iotcon_observers_create passes
* @failcase				if iotcon_observers_destroy or iotcon_observers_create fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_observers_create_destroy_p(void)
{
	START_TEST;

	iotcon_observers_h hIotconObservers = NULL;

	int nRet = iotcon_observers_create(&hIotconObservers);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_observers_create", IotConGetError(nRet));

	if( hIotconObservers == NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_observers_create failed ,as hIotconObservers is NULL : \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = iotcon_observers_destroy(hIotconObservers);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_observers_destroy", IotConGetError(nRet));
	
	return 0;
}
//& type: auto
//& purpose: Adds and remove a observer id into the observers handle.
/**
* @testcase 			ITc_iotcon_observers_add_remove_p
* @author            	SRID(sk.roy)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			Adds and remove a observer id into the observers handle
* @scenario				Adds observer id into the observers handle \n
* 						Remove a observer id into the observers handle \n
* @apicovered			iotcon_observers_add, iotcon_observers_remove
* @passcase				if iotcon_observers_add and iotcon_observers_remove passes
* @failcase				if iotcon_observers_add or iotcon_observers_remove fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_observers_add_remove_p(void)
{
	START_TEST;
	int nRet = iotcon_observers_add(g_hIotconObservers, 1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_observers_add", IotConGetError(nRet));


	nRet = iotcon_observers_remove(g_hIotconObservers, 1);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_observers_remove", IotConGetError(nRet));

	return 0;
}
/** @} */
/** @} */
