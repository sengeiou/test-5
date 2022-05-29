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

int g_bAppControlSendLaunchRequest = false;
int g_bAppControlAppMatched = false;
int g_bAppControlExtraData = false;

bool g_bCallBackHit_appControl = false;
bool g_bUserDataMismatch_appControl = false;

void *g_pUserData_appControl = "user_data_1";


/**
* @function 		ITs_application_app_control_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_app_control_startup(void)
{
	g_bCallBackHit_appControl = false;
	g_bUserDataMismatch_appControl = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_application_app_control_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_application_app_control_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		application_app_control_action_cb
* @description	 	callback function for app control action
* @parameter		action: The name of the app_control action, app_control: The handle of the app_control, user_data: The user data passed from the callback registration function 
* @return 			false
*/
void application_app_control_action_cb(const char *action, app_control_h hControl,void *user_data)
{
	return;
}
/**
* @function 		application_app_control_reply_cb
* @description	 	callback function for app control reply
* @parameter		hRequest : handle for app control request, hReply : app control handle, eResult : result, user_data : user data sent to callback
* @return 			false
*/
void application_app_control_reply_cb(app_control_h hRequest, app_control_h hReply, app_control_result_e eResult, void *user_data)
{
	g_bCallBackHit_appControl = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_appControl) != 0)
	{
		g_bUserDataMismatch_appControl = true;
	}

	g_bAppControlSendLaunchRequest = true;
	FPRINTF("[Line : %d][%s] app_control_reply_callback invoked, error returned = %d\\n", __LINE__, API_NAMESPACE, (int)eResult);
	
	if (g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}
}

/**
* @function 		application_app_control_result_cb
* @description	 	callback function for app control result
* @parameter		hRequest : handle for app control request, eResult : result, user_data : user data sent to callback
* @return 			false
*/
void application_app_control_result_cb(app_control_h hRequest, app_control_error_e eResult, void *user_data)
{
	if(strncmp((char *)user_data,(char *)g_pUserData_appControl,strlen(g_pUserData_appControl)) != 0)
	{
		g_bUserDataMismatch_appControl = true;
	}

	g_bAppControlSendLaunchRequest = true;
	FPRINTF("[Line : %d][%s] app_control_result_callback invoked, error returned = %d\\n", __LINE__, API_NAMESPACE, (int)eResult);

	if (g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}
}

/**
* @function 		application_app_control_app_matched_cb
* @description	 	callback function for app control application match
* @parameter		app_control : app control handle, package : package name, user_data : user data sent to callback
* @return 			false
*/
bool application_app_control_app_matched_cb(app_control_h app_control, const char *package, void *user_data)
{
	g_bCallBackHit_appControl = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_appControl) != 0)
	{
		g_bUserDataMismatch_appControl = true;
	}

	
	g_bAppControlAppMatched = true;
	FPRINTF("[Line : %d][%s] app_matched_callback invoked, package = %s\\n", __LINE__, API_NAMESPACE, package);
	return false;
}

/**
* @function 		application_app_control_extra_data_cb
* @description	 	callback function for app control extra data
* @parameter		app_control : app control handle, key : key name, user_data : user data sent to callback
* @return 			false
*/
bool application_app_control_extra_data_cb(app_control_h app_control, const char *key, void *user_data)
{
	g_bCallBackHit_appControl = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_appControl) != 0)
	{
		g_bUserDataMismatch_appControl = true;
	}


	g_bAppControlExtraData = true;
	FPRINTF("[Line : %d][%s] extra_data_callback invoked\\n", __LINE__, API_NAMESPACE);

	return false;
}

//& type: auto
//& purpose: Creates and Destroys AppControl.
/**
* @testcase 			ITc_application_app_control_create_destroy_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and Destroys AppControl
* @scenario				Create AppControl\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy
* @passcase				When app_control_create, app_control_destroy are successful.
* @failcase				If target API or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_create_destroy_p(void)
{
	START_TEST;

	app_control_h hAppControl;

	//Target API
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	// Give some sleep between create and destroy
	usleep(2000);

	//Target API
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates AppControl with parameters.
/**
* @testcase 			ITc_application_app_control_create_with_parameters_p
* @since_tizen			5.5
* @author			SRID(p.chauhan)
* @reviewer			SRID(manoj.g2)
* @type 			auto
* @description			Creates AppControl with parameters
* @scenario			Create AppControl with Parameters
* @apicovered			app_control_create_with_parameters, app_control_destroy
* @passcase			When app_control_create_with_parameters, app_control_add_extra_data, app_control_destroy are successful.
* @failcase			If target API or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_with_parameters_create_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	app_control_launch_mode_e eAppControlLaunch[] = {	APP_CONTROL_LAUNCH_MODE_SINGLE,
		APP_CONTROL_LAUNCH_MODE_GROUP
	};
	int enum_size = sizeof(eAppControlLaunch) / sizeof(eAppControlLaunch[0]);
	int enum_counter = 0;
	int nRet = -1;
	char *pszKey = "Key1";
	char *pszValue = "Value1";
	const char *pszOperation = "http://tizen.org/appcontrol/operation/dial";
	const char *pszUri = "file:///tmp/1_photo.jpg";
	const char *pszMime = "image/jpg";
	const char *pszCategory = "image/jpg";
	int nExtraDataCount = 1;
	char* pszGetVal;

	for ( enum_counter=0;enum_counter<enum_size;enum_counter++)
	{
		nRet = app_control_create_with_parameters(&hAppControl, pszOperation, pszUri, pszMime, pszCategory, TEST_TESTAPPLICATION_APPID , eAppControlLaunch[enum_counter], nExtraDataCount, pszKey, pszValue);
		PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create_with_parameters", AppControlGetError(nRet));

		CHECK_HANDLE(hAppControl,"app_control_create_with_parameters");

		nRet = app_control_add_extra_data(hAppControl, pszKey, pszValue);
		PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

		nRet = app_control_get_extra_data(hAppControl, pszKey, &pszGetVal);
		PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

		if(0 != strcmp(pszValue, pszGetVal))
		{
			FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszValue, pszGetVal);
			FREE_MEMORY(pszGetVal);
			app_control_destroy(hAppControl);
			return 1;
		}

		FREE_MEMORY(pszGetVal);
		nRet = app_control_destroy(hAppControl);
		PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl Operation.
/**
* @testcase 			ITc_application_app_control_set_get_operation_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl operation, Get AppControl operation and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Operation\n
*						Get AppControl Operation\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_get_operation, app_control_set_operation
* @passcase				When app_control_set_operation, app_control_get_operation are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_operation_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszOperation = "http://tizen.org/appcontrol/operation/dial";//sample operation string
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_set_operation(hAppControl, pszOperation);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_operation(hAppControl, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszOperation, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszOperation, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl App ID.
/**
* @testcase 			ITc_application_app_control_set_get_app_id_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl AppID, Get AppControl AppID and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl AppID\n
*						Get AppControl AppID\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_app_id, app_control_get_app_id
* @passcase				When app_control_set_app_id, app_control_get_app_id are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_app_id_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszAppID = TEST_TESTAPPLICATION_APPID;//sample app string
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_set_app_id(hAppControl, pszAppID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_app_id(hAppControl, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszAppID, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszAppID, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl URI.
/**
* @testcase 			ITc_application_app_control_set_get_uri_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Uri, Get AppControl Uri and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Uri\n
*						Get AppControl Uri\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_uri, app_control_get_uri
* @passcase				When app_control_set_uri, app_control_get_uri are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_uri_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszUri = "file:///tmp/1_photo.jpg";//sample URI string, the file need not present in this location
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_set_uri(hAppControl, pszUri);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_uri", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_uri(hAppControl, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_uri", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszUri, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszUri, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl Mime.
/**
* @testcase 			ITc_application_app_control_set_get_mime_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Mime, Get AppControl Mime and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Mime\n
*						Get AppControl Mime\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_mime, app_control_get_mime
* @passcase				When app_control_set_mime, app_control_get_mime are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_mime_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszMime = "image/jpg";//sample mime string
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_set_mime(hAppControl, pszMime);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_mime(hAppControl, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszMime, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszMime, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: Set and Get AppControl Category.
/**
* @testcase 			ITc_application_app_control_set_get_category_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Category, Get AppControl Category and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Category\n
*						Get AppControl Category\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_category, app_control_get_category
* @passcase				When app_control_set_category, app_control_get_category are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_category_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszCategory = "image/jpg";//sample category string
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_set_category(hAppControl, pszCategory);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_category", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_category(hAppControl, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_category", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszCategory, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszCategory, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Add extra data to AppControl and Get extra data.
/**
* @testcase 			ITc_application_app_control_add_get_extra_data_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Add AppControl Extra Data, Get AppControl Extra Data and then checks the added value should match the get value
* @scenario				Create AppControl\n
*						Add Extra Data\n
*						Get Extra Data\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_add_extra_data, app_control_get_extra_data
* @passcase				When app_control_add_extra_data, app_control_get_extra_data are successful and get value should match the added value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_add_get_extra_data_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	char *pszKey = "Sample_Key";//sample key-value string
	char *pszValue = "Sample_Value";
	char* pszGetVal = NULL;

	//Target API
	nRet = app_control_add_extra_data(hAppControl, pszKey, pszValue);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_extra_data(hAppControl, pszKey, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszValue, pszGetVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszValue, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Add extra data array to AppControl and Get extra data array.
/**
* @testcase 			ITc_application_app_control_add_get_extra_data_array_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Add AppControl Extra Data array, Get AppControl Extra Data Array and then checks the added value should match the get value
* @scenario				Create AppControl\n
*						Add Extra Data Array\n
*						Get Extra Data Array\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_add_extra_data_array, app_control_get_extra_data_array
* @passcase				When app_control_add_extra_data_array, app_control_get_extra_data_array are successful and get value should match the added value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_add_get_extra_data_array_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	char *pszKey = "Sample_Key";//sample key string
	int nArrayLen = 5;
	const char* psz_array_value[] = {"value1", "value2", "value3", "value4","value5"};
	char** ppsz_array_value_out;
	int nArrayLenOut = 0;

	//Target API
	nRet = app_control_add_extra_data_array(hAppControl, pszKey, psz_array_value, nArrayLen);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data_array", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_extra_data_array(hAppControl, pszKey, &ppsz_array_value_out, &nArrayLenOut);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_extra_data_array", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int i = 0;
	for (;i < nArrayLen;++i )
	{
		if ( 0 != strcmp(psz_array_value[i], ppsz_array_value_out[i]) )
		{
			FPRINTF("[Line : %d][%s]add and get extra data array Value mis-match occurs on index %d, added extra data array value = %s, get extra data array value = %s\\n", __LINE__, API_NAMESPACE, i, psz_array_value[i], ppsz_array_value_out[i]);
			FREE_MEMORY(ppsz_array_value_out);
			app_control_destroy(hAppControl);
			return 1;
		}
	}
	FREE_MEMORY(ppsz_array_value_out);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Add extra data array for a given key to AppControl and check if it is extra data array for that key.
/**
* @testcase 			ITc_application_app_control_is_extra_data_array_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Add AppControl Extra Data array for a given key and checks if it is Extra Data Array
* @scenario				Create AppControl\n
*						Add Extra Data Array for a specified key\n
*						Checks for if it is data array for the specified key\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_add_extra_data_array, app_control_is_extra_data_array
* @passcase				When app_control_is_extra_data_arrayis successful and return correct value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_is_extra_data_array_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	char *pszKey = "Sample_Key";//sample key string
	int nArrayLen = 5;
	const char* psz_array_value[] = {"value1", "value2", "value3", "value4","value5"};
	nRet = app_control_add_extra_data_array(hAppControl, pszKey, psz_array_value, nArrayLen);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data_array", AppControlGetError(nRet), app_control_destroy(hAppControl));

	bool bIsArray = false;

	//Target API
	nRet = app_control_is_extra_data_array(hAppControl, pszKey, &bIsArray);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_is_extra_data_array", AppControlGetError(nRet), app_control_destroy(hAppControl));

	//check for length mis-match
	if ( true != bIsArray )
	{
		FPRINTF("[Line : %d][%s] app_control_is_extra_data_array returns false Isarray boolean correct value = true, return value = false\\n", __LINE__, API_NAMESPACE);
	}
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call app_control_clone and check if it copied app_control values properly.
/**
* @testcase 			ITc_application_app_control_clone_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Create AppControl handle and clone it to get duplicate app_control handle.
* @scenario				Create AppControl\n
*						Set AppControl parameters\n
*						Clone app_control handle\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_mime, app_control_clone, app_control_get_mime
* @passcase				When app_control_is_extra_data_arrayis successful and return correct value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_clone_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszMime = "image/jpg";
	nRet = app_control_set_mime(hAppControl, pszMime);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));

	app_control_h hAppControlClone;
	char* pszGetMimeVal = NULL;

	nRet = app_control_clone(&hAppControlClone, hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_clone", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_mime(hAppControlClone, &pszGetMimeVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	if(0 != strcmp(pszMime, pszGetMimeVal))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, pszMime, pszGetMimeVal);
		FREE_MEMORY(pszGetMimeVal);
		app_control_destroy(hAppControl);
		app_control_destroy(hAppControlClone);
		return 1;
	}
	
	FREE_MEMORY(pszGetMimeVal);
	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	nRet = app_control_destroy(hAppControlClone);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Add extra data to AppControl and then remove it.
/**
* @testcase 			ITc_application_app_control_remove_extra_data_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Add AppControl Extra Data, Remove AppControl Extra Data and then checks the added value has been removed
* @scenario				Create AppControl\n
*						Add Extra Data\n
*						Remove Extra Data\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_add_extra_data, app_control_remove_extra_data, app_control_get_extra_data
* @passcase				When app_control_remove_extra_data is successful and added value got removed too.
* @failcase				If target API fails or added value not removed.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_remove_extra_data_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	char *pszKey = "Sample_Key";//sample key-value string
	char *pszValue = "Sample_Value";
	char* pszGetVal = NULL;

	nRet = app_control_add_extra_data(hAppControl, pszKey, pszValue);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

	//Target API
	nRet = app_control_remove_extra_data(hAppControl, pszKey);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_remove_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_extra_data(hAppControl, pszKey, &pszGetVal);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_KEY_NOT_FOUND, nRet, "app_control_get_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));
	if ( pszGetVal != NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_get_extra_data return extra data value after app_control_remove_extra_data call, value returned = %s\\n", __LINE__, API_NAMESPACE, pszGetVal);
		FREE_MEMORY(pszGetVal);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: send application launch request.
/**
* @testcase 			ITc_application_app_control_send_launch_terminate_request_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Create app_control, set app_control launch parameter, send the launch request and terminate it.
* @scenario				Create AppControl\n
*						Set app_control launch parameter\n
*						Send the launch request\n
*						Terminate the launch request\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_set_app_id, app_control_destroy, app_control_send_launch_request, app_control_set_operation, app_control_send_terminate_request
* @passcase				When app_control_send_launch_request, app_control_send_terminate_request are successful and callback function invokes properly.
* @failcase				If target API fails or callback not invoked.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_send_launch_terminate_request_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nTimeoutId = 0;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, TEST_TESTAPPLICATION_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_enable_app_started_result_event(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_enable_app_started_result_event", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	g_bAppControlSendLaunchRequest = false;
	nRet = app_control_send_launch_request(hAppControl, application_app_control_reply_cb, g_pUserData_appControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request", AppControlGetError(nRet), app_control_destroy(hAppControl));
	RUN_POLLING_LOOP;
	
	if(false == g_bAppControlSendLaunchRequest)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	if(g_bUserDataMismatch_appControl)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_send_terminate_request(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_terminate_request", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: set app_control launch parameter set the app matched callback to check the possible matching apps in callback.
/**
* @testcase 			ITc_application_app_control_for_each_app_matched_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Create app_control, set app_control launch parameter set the app matched callback to check the possible matching apps in callback.
* @scenario				Create AppControl\n
*						Set app_control launch parameter\n
*						Set the App Matched Callback\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_operation, app_control_set_mime, app_control_foreach_app_matched
* @passcase				When app_control_foreach_app_matched is successful and callback function invokes properly.
* @failcase				If target API fails or callback not invoked.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_for_each_app_matched_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_VIEW);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_mime(hAppControl, "application/xhtml+xml");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));

	g_bAppControlAppMatched = false;
	//Target API
	nRet = app_control_foreach_app_matched(hAppControl, application_app_control_app_matched_cb, g_pUserData_appControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_foreach_app_matched", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nTimer = 0;
	for ( ;nTimer<WAIT_CALLBACK;++nTimer )
	{
		if ( true == g_bAppControlAppMatched )
		{
			break;
		}
		usleep(2000);
	}
	if ( nTimer >= WAIT_CALLBACK )
	{
		FPRINTF("[Line : %d][%s] app_control_foreach_app_matched callback\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	if(false == g_bCallBackHit_appControl)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	if(g_bUserDataMismatch_appControl)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}


	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: set app_control extra data, set the extra data callback to check the extra data in callback.
/**
* @testcase 			ITc_application_app_control_for_each_extra_data_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Create app_control, set app_control extra data, set the extra data callback to check the extra data in callback.
* @scenario				Create AppControl\n
*						Set app_control extra data\n
*						Set the extra data Callback\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_add_extra_data, app_control_foreach_extra_data
* @passcase				When app_control_foreach_extra_data is successful and callback function invokes properly.
* @failcase				If target API fails or callback not invoked.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_for_each_extra_data_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	char *pszKey = "Sample_Key";//sample key-value pair
	char *pszValue = "Sample_Value";
	nRet = app_control_add_extra_data(hAppControl, pszKey, pszValue);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

	g_bAppControlExtraData = false;
	//Target API
	nRet = app_control_foreach_extra_data(hAppControl, application_app_control_extra_data_cb, g_pUserData_appControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_foreach_extra_data", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nTimer = 0;
	for (;nTimer<WAIT_CALLBACK;++nTimer )
	{
		if ( true == g_bAppControlExtraData )
		{
			break;
		}
		usleep(2000);
	}

	if ( nTimer >= WAIT_CALLBACK )
	{
		FPRINTF("[Line : %d][%s] app_control_foreach_app_matched callback\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	if(false == g_bCallBackHit_appControl)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	if(g_bUserDataMismatch_appControl)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and get the launch mode of the application.
/**
* @testcase 			ITc_application_app_control_set_get_launch_mode_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get the launch mode of the application
* @scenario				Create AppControl\n
*						set the launch mode\n
*						get the launch mode\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_launch_mode, app_control_get_launch_mode
* @passcase				When app_control_set_launch_mode, app_control_get_launch_mode are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_launch_mode_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	app_control_launch_mode_e eAppControlLaunch[] = {	APP_CONTROL_LAUNCH_MODE_SINGLE,
		APP_CONTROL_LAUNCH_MODE_GROUP
	};
	int enum_size = sizeof(eAppControlLaunch) / sizeof(eAppControlLaunch[0]);
	int enum_counter = 0;
	app_control_launch_mode_e eGetMode;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	for ( enum_counter=0;enum_counter<enum_size;enum_counter++)
	{
		//Target API
		nRet = app_control_set_launch_mode(hAppControl, eAppControlLaunch[enum_counter]);
		if ( nRet != APP_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_control_set_launch_mode failed, error returned = %s for launch mode %s\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet), AppControlGetLaunchMode(eAppControlLaunch[enum_counter]));
			app_control_destroy(hAppControl);
			return 1;
		}
		nRet = app_control_get_launch_mode(hAppControl, &eGetMode);
		if ( nRet != APP_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] app_control_get_launch_mode failed, error returned = %s for launch mode %s\\n", __LINE__, API_NAMESPACE, AppControlGetError(nRet), AppControlGetLaunchMode(eGetMode));
			app_control_destroy(hAppControl);
			return 1;
		}
		
		if ( eAppControlLaunch[enum_counter] != eGetMode )
		{
			FPRINTF("[Line : %d][%s] Value Mismatches, (expected = %s, received = %s)\\n", __LINE__, API_NAMESPACE, AppControlGetLaunchMode(eAppControlLaunch[enum_counter]), AppControlGetLaunchMode(eGetMode));
			app_control_destroy(hAppControl);
			return 1;
		}
	}

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Launches an application asynchronously
/**
* @testcase                     ITc_application_app_control_send_launch_request_async_p
* @since_tizen                  5.0
* @author                       SRID(s.rathi)
* @reviewer                     SRID(priya.kohli)
* @type                         auto
* @description                  Sends a launch request to an application asynchronously
* @scenario                     Create AppControl\n
*                               Set default operation\n
*                               Set application ID\n
*                               Launch application asynchronously\n
*                               Destroy AppControl
* @apicovered                   app_control_create, app_control_set_operation, app_control_set_app_id, app_control_send_launch_request_async, app_control_destroy
* @passcase                     When app_control_create, app_control_set_operation, app_control_set_app_id, app_control_send_launch_request_async, app_control_destroy are successful and callback function invoked.
* @failcase                     When target API fails or callback function not invoked
* @precondition                 None
* @postcondition                None
*/
int ITc_application_app_control_send_launch_request_async_p(void)
{
	START_TEST;
	int nRet = APP_CONTROL_ERROR_NONE;
	int nTimeoutId = 0;
	app_control_h hAppControl;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(&hAppControl,"app_control_create");

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, TEST_TESTAPPLICATION_APPID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	g_bAppControlSendLaunchRequest = false;

	nRet = app_control_send_launch_request_async(hAppControl, application_app_control_result_cb, application_app_control_reply_cb, g_pUserData_appControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request_async", AppControlGetError(nRet), app_control_destroy(hAppControl));

	RUN_POLLING_LOOP;

	if(false == g_bAppControlSendLaunchRequest)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	if(g_bUserDataMismatch_appControl)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Launches an application synchronously
/**
* @testcase                     ITc_application_app_control_send_launch_request_sync_p
* @since_tizen                  5.0
* @author                       SRID(p.chauhan)
* @reviewer                     SRID(priya.kohli)
* @type                         auto
* @description                  Sends a launch request to an application synchronously
* @scenario                     Create AppControl\n
*                               Set default operation\n
*                               Set application ID\n
*                               Launch application synchronously\n
*                               Destroy AppControl
* @apicovered                   app_control_create_with_parameters, app_control_send_launch_request_sync, app_control_destroy
* @passcase                     When app_control_send_launch_request_sync, app_control_destroy are successful.
* @failcase                     When target API fails.
* @precondition                 None
* @postcondition                None
*/
int ITc_application_app_control_send_launch_request_sync_p(void)
{
        START_TEST;

        app_control_h hReply = NULL;
        app_control_result_e eResult;
	app_control_h hAppControl;

	app_control_launch_mode_e eAppControlLaunch[] = {	APP_CONTROL_LAUNCH_MODE_SINGLE,
		APP_CONTROL_LAUNCH_MODE_GROUP
	};

	int enum_size = sizeof(eAppControlLaunch) / sizeof(eAppControlLaunch[0]);
	int enum_counter = 0;
	int nRet = -1;
	char *pszKey = "Key1";
	char *pszValue = "Value1";
	const char *pszOperation = APP_CONTROL_OPERATION_DEFAULT;
	const char *pszUri = "file:///tmp/1_photo.jpg";
	const char *pszMime = "image/jpg";
	const char *pszCategory = "image/jpg";
	int nExtraDataCount = 1;

	for ( enum_counter = 0; enum_counter < enum_size; enum_counter++)
	{
		nRet = app_control_create_with_parameters(&hAppControl, pszOperation, pszUri, pszMime, pszCategory, "org.example.reply" , eAppControlLaunch[enum_counter], nExtraDataCount, pszKey, pszValue);
		PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create_with_parameters", AppControlGetError(nRet));

		CHECK_HANDLE(hAppControl,"app_control_create_with_parameters");

		nRet = app_control_send_launch_request_sync(hAppControl, &hReply, &eResult);
		PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_launch_request_sync", AppControlGetError(nRet), app_control_destroy(hAppControl));
		CHECK_HANDLE_CLEANUP(hReply, "app_control_send_launch_request_sync", app_control_destroy(hAppControl); app_control_destroy(hReply));

		if (eResult != APP_CONTROL_RESULT_SUCCEEDED)
		{
		        FPRINTF("[Line : %d][%s] Failed to send launch request sync\\n", __LINE__, API_NAMESPACE);
		        app_control_destroy(hAppControl);
			app_control_destroy(hReply);
		        return 1;
		}
	        app_control_destroy(hAppControl);
        	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	        app_control_destroy(hReply);
	        PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	}
        return 0;
}
//& type: auto
//& purpose: Adds and removes the registered app_control action handle
/**
* @testcase                     ITc_application_app_control_add_remove_action_handler_p
* @since_tizen                  5.5
* @author                       SRID(manu.tiwari)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @description                  Adds and removes the registered app_control action handle.
* @scenario                     Calls app_control_add_action_handler() and app_control_remove_action_handler().
*                               And then, checks the return value.
*                               The action name must be defined in the tizen-manifest.xml
* @apicovered                   app_control_add_action_handler, app_control_remove_action_handler
* @passcase                     When app_control_add_action_handler, app_control_remove_action_handler are successful.
* @failcase                     When target API fails.
* @precondition                 None
* @postcondition                None
*/
int ITc_application_app_control_add_remove_action_handler_p(void)
{
	START_TEST;

	app_control_action_h hHandle = NULL;
	char *pszAction = "action";
	int nRet;

	nRet = app_control_add_action_handler(pszAction, application_app_control_action_cb, NULL, &hHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_add_action_handler", AppControlGetError(nRet));
	CHECK_HANDLE(hHandle,"app_control_add_action_handler");

	nRet = app_control_remove_action_handler(hHandle);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_remove_action_handler", AppControlGetError(nRet));
	return 0;
}

#ifdef TV	//Starts TV
//& type: auto
//& purpose: Test app_control_enable_app_started_result_event
/**
* @testcase 			ITc_app_control_enable_app_started_result_event_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Test app_control_enable_app_started_result_event
* @scenario				Call Test app_control_enable_app_started_result_event
* @apicovered			app_control_create, app_control_destroy, app_control_set_mime, app_control_enable_app_started_result_event
* @passcase				When app_control_enable_app_started_result_event is successful and return correct value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
/*int ITc_app_control_enable_app_started_result_event_p(void)		//undefined reference to API app_control_enable_app_started_result_event in 3.0 tv repo
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *pszMime = "image/jpg";
	nRet = app_control_set_mime(hAppControl, pszMime);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_mime", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_enable_app_started_result_event(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_enable_app_started_result_event", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}*/
#endif  //TV	//End TV

#if 0
//& type: auto
//& purpose: Set and Get AppControl Category.
/**
* @testcase 			ITc_application_app_control_get_event_data_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Category, Get AppControl Category and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Category\n
*						Get AppControl Category\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_get_event_data
* @passcase				When app_control_get_event_data are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
//int ITc_application_app_control_get_event_data_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));
	
	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData,"bundle_create");
	//Target API
	nRet = app_control_get_event_data(hAppControl, &pEventData);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_event_data", AppControlGetError(nRet), app_control_destroy(hAppControl));
	bundle_free(pEventData);

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl Category.
/**
* @testcase 			ITc_application_app_control_send_user_event_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Category, Get AppControl Category and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Category\n
*						Get AppControl Category\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_send_user_event
* @passcase				When app_control_send_user_event are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
//int ITc_application_app_control_send_user_event_p(void)
{
	START_TEST;

	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	int nRet = bundle_add_str(pEventData, "user_data_key1", "user_data_1");
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	app_control_h hAppControl;
	nRet = app_control_create(&hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet), bundle_free(pEventData));

	const char *szEventName = "eventsystem.tizen.system.event.usb.connected";

	//Target API
	nRet = app_control_send_user_event((const char *)szEventName, pEventData);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_user_event", AppControlGetError(nRet), app_control_destroy(hAppControl);bundle_free(pEventData));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet), bundle_free(pEventData));

	nRet = bundle_free(pEventData);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl Category.
/**
* @testcase 			ITc_application_app_control_send_user_event_trusted_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set AppControl Category, Get AppControl Category and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Category\n
*						Get AppControl Category\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_send_user_event_trusted
* @passcase				When app_control_send_user_event_trusted are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
//int ITc_application_app_control_send_user_event_trusted_p(void)
{
	START_TEST;

	bundle* pEventData = bundle_create();
	CHECK_HANDLE(pEventData, "bundle_create");

	int nRet = bundle_add_str(pEventData, "user_data_key1", "user_data_1");
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRet, "bundle_add_str", BundleGetError(nRet), bundle_free(pEventData));

	app_control_h hAppControl;
	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	const char *szEventName = "eventsystem.tizen.system.event.usb.connected";

	//Target API
	nRet = app_control_send_user_event_trusted((const char *)szEventName, pEventData);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_send_user_event_trusted", AppControlGetError(nRet), app_control_destroy(hAppControl);bundle_free(pEventData));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet), bundle_free(pEventData));

	nRet = bundle_free(pEventData);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRet, "bundle_free", BundleGetError(nRet));

	return 0;
}
#endif


//& type: auto
//& purpose: app control create uri from handle
/**
* @testcase 			ITc_application_app_control_create_from_uri_handle_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Creates the app-control handle from URI handle
* @scenario				Creates app_control_uri_handle.\n
*						And then, Calls app_control_create_from_uri_handle(),with the URI handle.\n
* @apicovered			app_control_uri_builder_create,app_control_uri_builder_set_scheme, app_control_uri_builder_set_authority,app_control_uri_builder_set_path,app_control_uri_builder_set_fragment,
*								app_control_destroy, app_control_uri_builder_add_query,app_control_uri_builder_build,app_control_uri_builder_destroy,app_control_uri_destroy,app_control_destroy
* @passcase				when all the precondition APIs and target api is successful
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_create_from_uri_handle_p(void)
{
	START_TEST;
	int nRet = 0;

	app_control_h hAppControl = NULL;
	app_control_uri_h hUri = NULL;
	app_control_uri_builder_h hBuilder = NULL;

	nRet = app_control_uri_builder_create(&hBuilder);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_create", AppControlGetError(nRet));
	CHECK_HANDLE(hBuilder,"app_control_uri_builder_create");

	nRet = app_control_uri_builder_set_scheme(hBuilder, "https");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_authority(hBuilder,
			"//john.doe@www.example.com:123");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_path(hBuilder, "/forum/questions/");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_fragment(hBuilder, "top");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_add_query(hBuilder, "tag", "networking");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_add_query(hBuilder, "order", "newest");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_build(hBuilder, &hUri);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););
	CHECK_HANDLE_CLEANUP(hUri,"app_control_uri_builder_build",app_control_uri_builder_destroy(hBuilder));

	nRet = app_control_create_from_uri_handle(&hAppControl, hUri);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_create_from_uri_handle", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder);app_control_uri_destroy(hUri););
	CHECK_HANDLE_CLEANUP(hAppControl,"app_control_create_from_uri_handle",app_control_uri_builder_destroy(hBuilder);app_control_uri_destroy(hUri));

	app_control_uri_builder_destroy(hBuilder);
	app_control_uri_destroy(hUri);
	app_control_destroy(hAppControl);

	return 0;
}

//& type: auto
//& purpose: app control Set uri by handle
/**
* @testcase 			ITc_application_app_control_set_uri_by_handle_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets uri to app-control by URI handle
* @scenario				Creates app_control_uri_handle\n
*						And then, Calls app_control_set_uri_by_handle(),with the URI handle.\n
* @apicovered			app_control_uri_builder_create,app_control_uri_builder_set_scheme, app_control_uri_builder_set_authority,app_control_uri_builder_set_path,app_control_uri_builder_set_fragment,
*								app_control_destroy, app_control_uri_builder_add_query,app_control_uri_builder_build,app_control_uri_builder_destroy,app_control_uri_destroy,app_control_destroy
* @passcase				when all the precondition APIs and target api is successful.
* @failcase				If any of the target api fails.
* @precondition			None
* @postcondition		None
*/

int ITc_application_app_control_set_uri_by_handle_p(void)
{
	START_TEST;
	int nRet = 0;

	app_control_h hAppControl = NULL;
	app_control_uri_h hUri = NULL;
	app_control_uri_builder_h hBuilder = NULL;

	nRet = app_control_uri_builder_create(&hBuilder);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_create", AppControlGetError(nRet));
	CHECK_HANDLE(hBuilder,"app_control_uri_builder_create");

	nRet = app_control_uri_builder_set_scheme(hBuilder, "https");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_scheme", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_authority(hBuilder,
			"//john.doe@www.example.com:123");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_authority", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_path(hBuilder, "/forum/questions/");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_path", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_set_fragment(hBuilder, "top");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_set_fragment", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_add_query(hBuilder, "tag", "networking");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_add_query(hBuilder, "order", "newest");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_add_query", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););

	nRet = app_control_uri_builder_build(hBuilder, &hUri);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_uri_builder_build", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder););
	CHECK_HANDLE_CLEANUP(hUri,"app_control_uri_builder_build",app_control_uri_builder_destroy(hBuilder));

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder);app_control_uri_destroy(hUri););
	CHECK_HANDLE_CLEANUP(hAppControl,"app_control_create",app_control_uri_builder_destroy(hBuilder);app_control_uri_destroy(hUri));

	nRet = app_control_set_uri_by_handle(hAppControl, hUri);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_uri_by_handle", AppControlGetError(nRet), app_control_uri_builder_destroy(hBuilder);app_control_uri_destroy(hUri);app_control_destroy(hAppControl));

	app_control_uri_builder_destroy(hBuilder);
	app_control_uri_destroy(hUri);
	app_control_destroy(hAppControl);

	return 0;
}

//& type: auto
//& purpose: Set and Get AppControl Component id.
/**
* @testcase 			ITc_application_app_control_set_get_component_id_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Set AppControl Component id, Get AppControl Component id and then checks the set value should match the get value
* @scenario				Create AppControl\n
*						Set AppControl Component id\n
*						Get AppControl Component id\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, app_control_set_component_id and app_control_get_component_id
* @passcase				When app_control_set_component_id and app_control_get_component_id are successful and set value should match the get value.
* @failcase				If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_control_set_get_component_id_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char *gCompID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl,"app_control_create");


	//Target API
	nRet = app_control_set_component_id(hAppControl, "compId");
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_component_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_get_component_id(hAppControl, &gCompID);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_get_component_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	if(0 != strcmp("compId", gCompID))
	{
		FPRINTF("[Line : %d][%s] Value Mismatches, (expected=%s, returned=%s)\\n", __LINE__, API_NAMESPACE, "compId", gCompID);
		FREE_MEMORY(gCompID);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(gCompID);

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

/** @} */
/** @} */
