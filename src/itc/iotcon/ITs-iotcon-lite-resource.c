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



/**
 * @function 		ITs_iotcon_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_iotcon_lite_resource_startup(void)
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
void ITs_iotcon_lite_resource_cleanup(void)
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
//& purpose: scenario to connect and disconnect iotcon.

/**
* @testcase 			ITc_iotcon_lite_resource_create_destroy_p
* @author            	SRID(mohit.kr)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			create and destroy iotcon lite resource.
* @scenario				create iotcon resource\n
* 						destroy iotcon resource\n
* @apicovered			iotcon_lite_resource_create, iotcon_lite_resource_destroy,iotcon_resource_types_create,iotcon_attributes_create,iotcon_attributes_add_int,iotcon_attributes_destroy,iotcon_resource_types_destroy
* @passcase				if iotcon_lite_resource_create and iotcon_lite_resource_destroy passes
* @failcase				if iotcon_lite_resource_create or iotcon_lite_resource_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_lite_resource_create_destroy_p(void)
{
	IotconCreateLiteResource();

	if (g_hLiteLightResource)
	{
		int nRet = iotcon_lite_resource_destroy(g_hLiteLightResource);
		PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_lite_resource_destroy", IotConGetError(nRet));
		g_hLiteLightResource = NULL;
	}

	return 0;
}



//& type: auto
//& purpose: scenario to update lite resource state of iotcon.
/**
* @testcase 			ITc_iotcon_lite_resource_update_attributes_p
* @author            	SRID(mohit.kr)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			update lite resource state of iotcon
* @scenario				create iotcon resource \n
* 						create state iotcon resource \n
* 						add state iotcon resource \n
* 						update state iotcon resource \n
* @apicovered			iotcon_attributes_add_int, iotcon_lite_resource_update_attributes, iotcon_attributes_destroy
* @passcase				if  iotcon_lite_resource_update_attributes passes
* @failcase				if iotcon_lite_resource_update_attributes fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_lite_resource_update_attributes_p(void)
{
	START_TEST;
	int nRet;
	iotcon_attributes_h state = NULL;

	IotconCreateLiteResource();
	nRet = iotcon_attributes_create(&state);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet));
	if(state==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_create fail states is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		IotconDestroyLiteResource();
		return 1;
	}

	nRet = iotcon_attributes_add_int(state, LITE_RESOURCE_BR, ++g_nBrightness);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet));

	nRet = iotcon_lite_resource_update_attributes(g_hLiteLightResource, state);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_lite_resource_update_attributes", IotConGetError(nRet));

	iotcon_attributes_destroy(state);
	IotconDestroyLiteResource();

	return 0;
}


//& type: auto
//& purpose: scenario to update lite resource state of iotcon.
/**
* @testcase 			ITc_iotcon_lite_resource_get_attributes_p
* @author            	SRID(mohit.kr)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @since_tizen 			3.0
* @description			get state of iotcon lite resource.
* @scenario				create iotcon resource \n
* 						create state iotcon resource \n
* 						get state iotcon resource \n
* @apicovered			iotcon_lite_resource_get_attributes
* @passcase				if  iotcon_lite_resource_get_attributes passes
* @failcase				if iotcon_lite_resource_get_attributes fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_iotcon_lite_resource_get_attributes_p(void)
{
	START_TEST;
	int nRet;
	iotcon_attributes_h state = NULL;

	IotconCreateLiteResource();
	nRet = iotcon_lite_resource_get_attributes(g_hLiteLightResource, &state);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_lite_resource_update_attributes", IotConGetError(nRet));
	if(state==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_create fail states is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		IotconDestroyLiteResource();
		return 1;
	}
	IotconDestroyLiteResource();
	return 0;
}

/** @} */
/** @} */
