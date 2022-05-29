//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-application-common.h"

/** @addtogroup itc-application
*  @ingroup itc
*  @{
*/
//& set: Application

bool g_bCallBackHit_resourceManager = false;
bool g_bUserDataMismatch_resourceManager = false;


/**
* @function 		ITs_application_resourceManager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_resourceManager_startup(void)
{
	g_bCallBackHit_resourceManager = false;
	g_bUserDataMismatch_resourceManager = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_application_resourceManager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_resourceManager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: Initialize and release the resource manager
/**
* @testcase 			ITc_application_app_resource_manager_init_release_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates resource manager and get from db
* @scenario				Initialize the resource manager
*						Release the resource manager
* @apicovered			app_resource_manager_init, app_resource_manager_release
* @passcase				When app_resource_manager_init and app_resource_manager_release are successful and set value should match the get value
* @failcase				If any of target API fails
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_resource_manager_init_release_p(void)
{
	START_TEST;

	//Target API
	int nRet = app_resource_manager_init();
	PRINT_RESULT(APP_RESOURCE_ERROR_NONE, nRet, "app_resource_manager_init", AppResourceGetError(nRet));

	nRet = app_resource_manager_release();
	PRINT_RESULT(APP_RESOURCE_ERROR_NONE, nRet, "app_resource_manager_release", AppResourceGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Convert resource ID to path name
/**
* @testcase 			ITc_application_app_resource_manager_get_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Convert resource ID to path name
* @scenario				create a key
*						set the resource id
* @apicovered			app_resource_manager_get
* @passcase				When app_resource_manager_get are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_resource_manager_get_p(void)
{
	START_TEST;

	app_resource_e eResourceType[] = {
		APP_RESOURCE_TYPE_IMAGE, /**<Image*/
		APP_RESOURCE_TYPE_LAYOUT, /**<Edje*/
		APP_RESOURCE_TYPE_SOUND, /**<Sound*/
		APP_RESOURCE_TYPE_BIN /**<Bin*/
	};

	int nEnumSize = sizeof(eResourceType) / sizeof(eResourceType[0]);
	int nEnumCounter;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		char *id = NULL;
		char* szType = NULL;
		switch ( eResourceType[nEnumCounter] )
		{
		case APP_RESOURCE_TYPE_IMAGE:
			id = IMAGE_ID;
			szType = "APP_RESOURCE_TYPE_IMAGE";
			break;
		case APP_RESOURCE_TYPE_LAYOUT:
			id = EDJ_ID;
			szType = "APP_RESOURCE_TYPE_LAYOUT";
			break;
		case APP_RESOURCE_TYPE_SOUND:
			id = SOUND_ID;
			szType = "APP_RESOURCE_TYPE_SOUND";
			break;
		case APP_RESOURCE_TYPE_BIN:
			continue;
		}

		//Target API
		char *pPath = NULL;
		int nRet = app_resource_manager_get(eResourceType[nEnumCounter], id, &pPath);
		if ( nRet != APP_RESOURCE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_resource_manager_get failed for eResourceType = %s, error returned = %s\\n", __LINE__, API_NAMESPACE, szType, AppResourceGetError(nRet));
			return 1;
		}

		FPRINTF("[Line : %d][%s] app_resource_manager_get returned value = %s for eResourceType = %s\\n", __LINE__, API_NAMESPACE, pPath, szType);
		CHECK_VALUE_STRING(pPath, "app_resource_manager_get");
	}

	return 0;
}

/** @} */
/** @} */
