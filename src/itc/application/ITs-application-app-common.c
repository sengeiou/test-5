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

bool g_bCallBackHit_appCommon = false;
bool g_bUserDataMismatch_appCommon = false;

/**
* @function 		ITs_application_app_common_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_app_common_startup(void)
{
	g_bCallBackHit_appCommon = false;
	g_bUserDataMismatch_appCommon = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_app_common_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_application_app_common_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_app_common_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_app_common_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type: auto
//& purpose: gets absolute path to application cache directory
/**
* @testcase 			ITc_application_app_get_cache_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_cache_path
* @passcase				When app_get_cache_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_cache_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_cache_path();
	CHECK_VALUE_STRING(pPath, "app_get_cache_path");
	FPRINTF("[Line : %d][%s] app_get_cache_path returned value = %s\\n", __LINE__, API_NAMESPACE, pPath);
	return 0;

}
//& type: auto
//& purpose: gets absolute path to application data
/**
* @testcase 			ITc_application_app_get_data_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_data_path
* @passcase				When app_get_data_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_data_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_data_path();
	CHECK_VALUE_STRING(pPath, "app_get_data_path");
	FPRINTF("[Line : %d][%s] app_get_data_path returned value = %s\\n", __LINE__, API_NAMESPACE, pPath);
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application external data directory
/**
* @testcase 			ITc_application_app_get_external_data_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_external_data_path
* @passcase				When app_get_external_data_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_external_data_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_external_data_path();
	CHECK_VALUE_STRING(pPath, "app_get_external_data_path");
	FPRINTF("[Line : %d][%s] app_get_external_data_path returned value = %s\\n", __LINE__, API_NAMESPACE, pPath );
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application external cache directory
/**
* @testcase 			ITc_application_app_get_external_cache_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_external_cache_path
* @passcase				When app_get_external_cache_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_external_cache_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_external_cache_path();
	CHECK_VALUE_STRING(pPath, "app_get_external_cache_path");
	FPRINTF("[Line : %d][%s] app_get_external_cache_path returned value = %s\\n", __LINE__, API_NAMESPACE, pPath );
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application external shared data directory
/**
* @testcase 			ITc_application_app_get_external_shared_data_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_external_shared_data_path
* @passcase				When app_get_external_shared_data_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_external_shared_data_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_external_shared_data_path();
	CHECK_VALUE_STRING(pPath, "app_get_external_shared_data_path");
	FPRINTF("[Line : %d][%s] app_get_external_shared_data_path returned value = %s d", __LINE__, API_NAMESPACE, pPath);
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application resource directory
/**
* @testcase 			ITc_application_app_get_resource_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_resource_path
* @passcase				When app_get_resource_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_resource_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_resource_path();
	CHECK_VALUE_STRING(pPath, "app_get_resource_path");
	FPRINTF("[Line : %d][%s] app_get_resource_path returned value = %s d", __LINE__, API_NAMESPACE, pPath);
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application shared data directory
/**
* @testcase 			ITc_application_app_get_shared_data_path_p
* @deprecated			Deprecated API since 3.0
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_shared_data_path
* @passcase				When app_get_shared_data_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_shared_data_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = NULL;
	pPath = app_get_shared_data_path();
	int nRet = get_last_result();

	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_get_shared_data_path", AppGetError(nRet));		
	if(pPath==NULL){
		FPRINTF("[Line : %d][%s] app_get_shared_data_path returned value = %s d", __LINE__, API_NAMESPACE, pPath);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: gets absolute path to application shared resource directory
/**
* @testcase 			ITc_application_app_get_shared_resource_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_shared_resource_path
* @passcase				When app_get_shared_resource_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_shared_resource_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_shared_resource_path();
	CHECK_VALUE_STRING(pPath, "app_get_shared_resource_path");
	FPRINTF("[Line : %d][%s] app_get_shared_resource_path returned value = %s d", __LINE__, API_NAMESPACE, pPath);
	return 0;
}

//& type: auto
//& purpose: gets absolute path to application shared trusted directory, used to share data with group of trusted applications
/**
* @testcase 			ITc_application_app_get_shared_trusted_path_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_shared_trusted_path
* @passcase				When app_get_shared_trusted_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_shared_trusted_path_p(void)
{
	START_TEST;

	//Target API
	char* pPath = app_get_shared_trusted_path();
	CHECK_VALUE_STRING(pPath, "app_get_shared_trusted_path");
	FPRINTF("[Line : %d][%s] app_get_shared_trusted_path returned value = %s d", __LINE__, API_NAMESPACE, pPath);
	return 0;
}

//& type: auto
//& purpose: gets application id
/**
* @testcase 			ITc_application_app_get_id_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_id
* @passcase				When app_get_id is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_id_p(void)
{
	START_TEST;

	char* pValue = NULL;

	//Target API
	int nRet = app_get_id(&pValue);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_get_id", AppGetError(nRet));
	CHECK_VALUE_STRING(pValue, "app_get_id");

	FPRINTF("[Line : %d][%s] app_get_id returned value = %s\\n", __LINE__, API_NAMESPACE, pValue);
	FREE_MEMORY(pValue);

	return 0;
}

//& type: auto
//& purpose: gets application version
/**
* @testcase 			ITc_application_app_get_version_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_version
* @passcase				When app_get_version is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_version_p(void)
{
	START_TEST;

	char* pValue = NULL;

	//Target API
	int nRetue = app_get_version(&pValue);
	PRINT_RESULT(APP_ERROR_NONE, nRetue, "app_get_version", AppGetError(nRetue));
	CHECK_VALUE_STRING(pValue, "app_get_version");

	FPRINTF("[Line : %d][%s] app_get_version returned value = %s\\n", __LINE__, API_NAMESPACE, pValue);
	FREE_MEMORY(pValue);

	return 0;
}

//& type: auto
//& purpose: gets application localized name
/**
* @testcase 			ITc_application_app_get_name_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_name
* @passcase				When app_get_name is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_name_p(void)
{
	START_TEST;

	char* pValue = NULL;

	//Target API
	int nRetue = app_get_name(&pValue);
	PRINT_RESULT(APP_ERROR_NONE, nRetue, "app_get_name", AppGetError(nRetue));
	CHECK_VALUE_STRING(pValue, "app_get_name");

	FPRINTF("[Line : %d][%s] app_get_name returned value = %s\\n", __LINE__, API_NAMESPACE, pValue);
	FREE_MEMORY(pValue);

	return 0;
}

//& type: auto
//& purpose: activates, resets and disables watchdog timer
/**
* @testcase 			ITc_application_app_watchdog_timer_enable_kick_disable_p
* @since_tizen			5.5
* @author			SRID(s.rathi)
* @reviewer			SRID(priya.kohli)
* @type 			auto
* @description			Activates, resets, and disables watchdog timer
* @scenario				Call Enable API\n
*					Call Kick API\n
*					Call Disable API\n
* @apicovered			app_watchdog_timer_enable, app_watchdog_timer_kick, app_watchdog_timer_disable
* @passcase				When all three target APIs are successful and returns APP_ERROR_NONE.
* @failcase				If any of three target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_watchdog_timer_enable_kick_disable_p(void)
{
	START_TEST;

	int nRet = APP_ERROR_NONE;
	nRet = app_watchdog_timer_enable();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_watchdog_timer_enable", AppGetError(nRet));

	nRet = app_watchdog_timer_kick();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_watchdog_timer_kick", AppGetError(nRet));

	nRet = app_watchdog_timer_disable();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_watchdog_timer_disable", AppGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: activates and disables watchdog timer
/**
* @testcase 			ITc_application_app_watchdog_timer_enable_disable_p
* @since_tizen			5.5
* @author			SRID(s.rathi)
* @reviewer			SRID(priya.kohli)
* @type 			auto
* @description			Activates and disables watchdog timer
* @scenario				Call Enable API\n
*					Call Disable API\n
* @apicovered			app_watchdog_timer_enable, app_watchdog_timer_disable
* @passcase				When both target APIs are successful and returns APP_ERROR_NONE.
* @failcase				If any of two target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_watchdog_timer_enable_disable_p(void)
{
	START_TEST;

	int nRet = APP_ERROR_NONE;
	nRet = app_watchdog_timer_enable();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_watchdog_timer_enable", AppGetError(nRet));

	nRet = app_watchdog_timer_disable();
	PRINT_RESULT(APP_ERROR_NONE, nRet, "app_watchdog_timer_disable", AppGetError(nRet));

	return 0;
}

#ifdef TV	//Starts TV
//& type: auto
//& purpose: gets absolute path to application tep resource directory
/**
* @testcase 			ITc_application_app_get_tep_resource_path_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call target API and validate the values.
* @scenario				Call target API\n
*						Validate the value
* @apicovered			app_get_tep_resource_path
* @passcase				When app_get_tep_resource_path is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
/*int ITc_application_app_get_tep_resource_path_p(void)			// undefined reference to API app_get_tep_resource_path in 3.0 tv repo
{
	START_TEST;

	//Target API
	char* pPath = app_get_tep_resource_path();
	CHECK_VALUE_STRING(pPath, "app_get_tep_resource_path");
	
	return 0;
}*/
#endif  //TV	//End TV

/** @} */
/** @} */
