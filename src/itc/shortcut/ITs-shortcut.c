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
#include "ITs-shortcut-common.h"

//& set: Shortcut

/** @addtogroup itc-shortcut
*  @ingroup itc
*  @{
*/

const char *g_pszICON_PATH = NULL;
bool g_bShortcutNotSupported = false;

/*********************************************************CallBack Start*********************************************************/
/**
 * @function 		ShortcutAddToHomeWidgetCB
 * @description	 	Callback function
 * @parameter		int ret, void *data
 * @return 			int
 */
static int ShortcutAddToHomeWidgetCB(int ret, void *data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ShortcutAddToHomeWidgetCB callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if((data == NULL) || (strcmp(data, TESTSTRING) != 0))
	{
		g_bCallbackHit = false;
		FPRINTF("[Line : %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		QUIT_GMAIN_LOOP;
		return 0;
	}

	if ( ret < 0 )
	{
		FPRINTF("[Line : %d][%s] Failed to add shortcut : %s\\n", __LINE__, API_NAMESPACE, strerror(errno));
		QUIT_GMAIN_LOOP;
		return 0;
	}
	else
	{
		g_bCallbackHit = true;
	}

	if(g_b2CallbackValueCheck)
	{
		QUIT_GMAIN_LOOP_CONDITIONAL(g_bCallbackHit, g_bRequestCBCallbackHit);
	}
	else
	{
		QUIT_GMAIN_LOOP;
	}


	return 0;
}

/**
 * @function 		ShortcutAddToHomeCB
 * @description	 	Callback function
 * @parameter		int ret, void *data
 * @return 			int
 */
static int ShortcutAddToHomeCB(int ret, void *data)
{
	FPRINTF("[Line : %d][%s] ShortcutAddToHomeCB callback called\\n", __LINE__, API_NAMESPACE);

	if((data == NULL) || (strcmp(data, TESTSTRING) != 0))
	{
		g_bCallbackHit = false;
		FPRINTF("[Line : %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		QUIT_GMAIN_LOOP;
		return 0;
	}

	if ( ret < 0 )
	{
		FPRINTF("[Line : %d][%s] Failed to add shortcut : %s\\n", __LINE__, API_NAMESPACE, strerror(errno));
		QUIT_GMAIN_LOOP;
		return 0;
	}
	else
	{
		g_bCallbackHit = true;
	}

	if(g_b2CallbackValueCheck)
	{
		QUIT_GMAIN_LOOP_CONDITIONAL(g_bCallbackHit, g_bRequestCBCallbackHit);
	}
	else
	{
		QUIT_GMAIN_LOOP;
	}

	return 0;
}

/**
 * @function 		ShortcutRequestCB
 * @description	 	Callback function
 * @parameter		const char *package_name, const char *name, int type, const char *content_info, const char *icon, int pid, double period, int allow_duplicate, void *data
 * @return 			int
 */
static int ShortcutRequestCB(const char *package_name, const char *name, int type, const char *content_info, const char *icon, int pid, double period, int allow_duplicate, void *data)
{
	FPRINTF("[Line : %d][%s] ShortcutRequestCB callback called\\n", __LINE__, API_NAMESPACE);

	if((data == NULL) || (strcmp(data, TESTSTRING) != 0))
	{
		g_bRequestCBCallbackHit = false;
		FPRINTF("[Line : %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		QUIT_GMAIN_LOOP;
		return 0;
	}

	if(package_name == NULL)
	{
		FPRINTF("[Line : %d][%s] package name is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bRequestCBCallbackHit = false;
	}
	else if(name == NULL)
	{
		FPRINTF("[Line : %d][%s] name is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bRequestCBCallbackHit = false;
	}
	else if(type < 0)
	{
		FPRINTF("[Line : %d][%s] type is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bRequestCBCallbackHit = false;
	}
	else if(pid < 0)
	{
		FPRINTF("[Line : %d][%s] pid is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bRequestCBCallbackHit = false;
	}
	else
	{
		g_bRequestCBCallbackHit = true;
	}
	
	if(g_bRequestCBCallbackHit == false)
	{
		QUIT_GMAIN_LOOP;
	}

	else
	{
		if(g_b2CallbackValueCheck)
		{
			QUIT_GMAIN_LOOP_CONDITIONAL(g_bCallbackHit, g_bRequestCBCallbackHit);
		}
		else
		{
			QUIT_GMAIN_LOOP;
		}
	}

	return 0;
}

/**
 * @function 		ShortcutListCallBack
 * @description	 	Callback function
 * @parameter		const char *package_name, const char *icon, const char *name, const char *extra_key, const char *extra_data, void *user_data
 * @return 			int
 */
static int ShortcutListCallBack(const char *package_name, const char *icon, const char *name, const char *extra_key, const char *extra_data, void *user_data)
{
	FPRINTF("[Line : %d][%s] ShortcutListCallBack callback called\\n", __LINE__, API_NAMESPACE);

	if((user_data == NULL) || (strcmp(user_data, TESTSTRING) != 0))
	{
		g_bCallbackHit = false;
		FPRINTF("[Line : %d][%s] Invalid user_data passed to callback\\n", __LINE__, API_NAMESPACE);
		QUIT_GMAIN_LOOP;
		return -1;
	}

	if(package_name == NULL)
	{
		FPRINTF("[Line : %d][%s] package name is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	else if(name == NULL)
	{
		FPRINTF("[Line : %d][%s] name is invalid in callback function\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	else
	{
		g_bCallbackHit = true;
	}

	if(g_bCallbackHit == false)
	{
		QUIT_GMAIN_LOOP;
	}

	else
	{
		if(g_b2CallbackValueCheck)
		{
			QUIT_GMAIN_LOOP_CONDITIONAL(g_bCallbackHit, g_bRequestCBCallbackHit);
		}
		else
		{
			QUIT_GMAIN_LOOP;
		}
	}

	return -1;
}

/**
 * @function 		ShortcutRemoveCb
 * @description	 	Callback function
 * @parameter		const char *package_name, const char *name, int sender_pid, void *user_data
 * @return 			int
 */
static int ShortcutRemoveCb(const char *package_name, const char *name, int sender_pid, void *user_data)
{
	g_bCallbackHitRemoveCb = true;
	FPRINTF("[Line : %d][%s] Inside ShortcutRemoveCb callback function\\n", __LINE__, API_NAMESPACE);
	QUIT_GMAIN_LOOP;
	return 0;
}

/**
 * @function 		ShortcutRemoveFromHomeCB
 * @description	 	Callback function
 * @parameter		int ret, void *data
 * @return 			int
 */
static int ShortcutRemoveFromHomeCB(int ret, void *data)
{
	FPRINTF("[Line : %d][%s] ShortcutRemoveFromHomeCB callback called\\n", __LINE__, API_NAMESPACE);
	if ( ret < 0 )
	{
		FPRINTF("[Line : %d][%s] Failed to remove shortcut : %s\\n", __LINE__, API_NAMESPACE, strerror(errno));
		QUIT_GMAIN_LOOP;
		return 0;
	}
	
	QUIT_GMAIN_LOOP
	return 0;
}
/**********************************************************CallBack End**********************************************************/


/**
 * @function 		ITs_shortcut_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_shortcut_startup(void)
{
	g_b2CallbackValueCheck = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT start-up: ITs_Shortcut_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bShortcutNotSupported = false;

#ifdef MOBILE   //Starts MOBILE
	if ( !TCTCheckSystemInfoFeatureSupported(SHORTCUT_FEATURE, API_NAMESPACE) )
	{
		g_bShortcutNotSupported = true;
	}
#endif   //End mobile
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		int path_size = strlen(pszValue)+strlen("/icon.png")+1;
		g_pszICON_PATH=(char*)calloc(path_size, sizeof(char));
		if( g_pszICON_PATH == NULL)
                {
                        FPRINTF("[Line : %d][%s] Memory Allocation failed for g_pszICON_PATH \\n", __LINE__, API_NAMESPACE);
                        return;
                }
		snprintf(g_pszICON_PATH, path_size, "%s/icon.png", pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	TCT_CheckInstalledApp(1, TEST_SHORTCUT_APPID);
	elm_init(0, NULL);
	return;
}


/**
 * @function 		ITs_shortcut_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_shortcut_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] TEST SUIT clean-up: ITs_Shortcut_p\\n", __LINE__, API_NAMESPACE);
#endif

	elm_shutdown();

	if (g_pszICON_PATH) {
		free(g_pszICON_PATH);
		g_pszICON_PATH = NULL;
	}

	return;
}

/** @addtogroup itc-shortcut-testcases
*  @brief 		Integration testcases for module shortcut
*  @ingroup 	itc-shortcut
*  @{
*/

/**
* @testcase 		ITc_shortcut_add_to_home_p
* @since_tizen 		2.4
* @author			SRID(abhishek1.g)
* @reviewer			SRID(gupta.sanjay)
* @type				auto
* @description		Test shortcut_add_to_home
* @scenario			Call shortcut_add_to_home
* @apicovered		shortcut_add_to_home
* @passcase			If target API returns SHORTCUT_ERROR_NONE
* @failcase			If API fails to complete the scenario cycle
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
//& purpose: Test shortcut_add_to_home
//& type: auto

int ITc_shortcut_add_to_home_p(void)
{
	START_TEST;
	g_b2CallbackValueCheck = true;

	int nRet = -1;
	char *pszName = "Test";

	g_bCallbackHit = false;
	g_bRequestCBCallbackHit = false;

	nRet = shortcut_set_request_cb(ShortcutRequestCB, TESTSTRING);
#ifdef MOBILE //Starts MOBILE
	if (g_bShortcutNotSupported)
		{
		if(nRet != SHORTCUT_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif //End mobile
	PRINT_RESULT(SHORTCUT_ERROR_NONE, nRet, "shortcut_set_request_cb", ShortcutError(nRet));

	nRet = shortcut_add_to_home(pszName, LAUNCH_BY_APP, TEST_SHORTCUT_APPID, g_pszICON_PATH, DUPLICATEALLOWED, ShortcutAddToHomeCB, TESTSTRING);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_add_to_home", ShortcutError(nRet), shortcut_unset_request_cb());
	CHECK_CALLBACK_STATUS("shortcut_add_to_home", g_bCallbackHit, g_bRequestCBCallbackHit);

	shortcut_unset_request_cb();
	return 0;
}

/**
* @testcase 		ITc_shortcut_add_to_home_widget_p
* @since_tizen 		2.4
* @author			SRID(abhishek1.g)
* @reviewer			SRID(gupta.sanjay)
* @type				auto
* @description		Test shortcut_add_to_home_widget
* @scenario			Call shortcut_add_to_home_widget
* @apicovered		shortcut_add_to_home_widget
* @passcase			If target API returns SHORTCUT_ERROR_NONE
* @failcase			If API fails to complete the scenario cycle
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
//& purpose: Test shortcut_add_to_home_widget
//& type: auto

int ITc_shortcut_add_to_home_widget_p(void)
{
	START_TEST;
	g_b2CallbackValueCheck = true;

	int nRet = -1;
	char *pszName = "Test";

	shortcut_widget_size_e eShortcutWidgetSize[] = {WIDGET_SIZE_DEFAULT,
		WIDGET_SIZE_1x1,
		WIDGET_SIZE_2x1,
		WIDGET_SIZE_2x2,
		WIDGET_SIZE_4x1,
		WIDGET_SIZE_4x2,
		WIDGET_SIZE_4x3,
		WIDGET_SIZE_4x4,
		WIDGET_SIZE_4x5,
		WIDGET_SIZE_4x6,
		WIDGET_SIZE_EASY_DEFAULT,
		WIDGET_SIZE_EASY_1x1,
		WIDGET_SIZE_EASY_3x1,
		WIDGET_SIZE_EASY_3x3};


	int enum_size1 = sizeof(eShortcutWidgetSize) / sizeof(shortcut_widget_size_e);
	int enum_counter1 = 0;

	for ( enum_counter1=0; enum_counter1<enum_size1; enum_counter1++)
	{
		g_bCallbackHit = false;
		g_bRequestCBCallbackHit = false;

		nRet = shortcut_set_request_cb(ShortcutRequestCB, TESTSTRING);
#ifdef MOBILE //Starts MOBILE
		if (g_bShortcutNotSupported)
			{
			if(nRet != SHORTCUT_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}
#endif //End mobile
		PRINT_RESULT(SHORTCUT_ERROR_NONE, nRet, "shortcut_set_request_cb", ShortcutError(nRet));

		nRet = shortcut_add_to_home_widget(pszName, eShortcutWidgetSize[enum_counter1], TEST_SHORTCUT_APPID, g_pszICON_PATH, SHORTCUTPERIOD, DUPLICATEALLOWED, ShortcutAddToHomeWidgetCB, TESTSTRING);
		RUN_POLLING_LOOP;
		PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_add_to_home_widget", ShortcutError(nRet), shortcut_unset_request_cb());
		CHECK_CALLBACK_STATUS("shortcut_add_to_home_widget", g_bCallbackHit, g_bRequestCBCallbackHit);
		shortcut_unset_request_cb();
	}

	return 0;
}

/**
* @testcase 		ITc_shortcut_set_request_cb_p
* @since_tizen 		2.4
* @author			SRID(abhishek1.g)
* @reviewer			SRID(gupta.sanjay)
* @type				auto
* @description		Test shortcut_set_request_cb
* @scenario			Call shortcut_set_request_cb
* @apicovered		shortcut_set_request_cb
* @passcase			If target API returns SHORTCUT_ERROR_NONE
* @failcase			If API fails to complete the scenario cycle
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
//& purpose: Test shortcut_set_request_cb
//& type: auto

int ITc_shortcut_set_unset_request_cb_p(void)
{
	START_TEST;
	g_b2CallbackValueCheck = true;

	int nRet = -1;
	char *pszName = "Test";

	g_bCallbackHit = false;
	g_bRequestCBCallbackHit = false;

	nRet = shortcut_set_request_cb(ShortcutRequestCB, TESTSTRING);
#ifdef MOBILE //Starts MOBILE
	if (g_bShortcutNotSupported)
		{
		if(nRet != SHORTCUT_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif //End mobile
	PRINT_RESULT(SHORTCUT_ERROR_NONE, nRet, "shortcut_set_request_cb", ShortcutError(nRet));

	nRet = shortcut_add_to_home(pszName, LAUNCH_BY_APP, TEST_SHORTCUT_APPID, g_pszICON_PATH, DUPLICATEALLOWED, ShortcutAddToHomeCB, TESTSTRING);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_add_to_home", ShortcutError(nRet), shortcut_unset_request_cb());
	CHECK_CALLBACK_STATUS("shortcut_set_request_cb", g_bCallbackHit, g_bRequestCBCallbackHit);

	shortcut_unset_request_cb();
	return 0;
}

/**
* @testcase 		ITc_shortcut_get_list_p
* @since_tizen 		2.4
* @author			SRID(abhishek1.g)
* @reviewer			SRID(gupta.sanjay)
* @type				auto
* @description		Test shortcut_get_list
* @scenario			Call shortcut_get_list
* @apicovered		shortcut_get_list
* @passcase			If target API returns SHORTCUT_ERROR_NONE
* @failcase			If API fails to complete the scenario cycle
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
//& purpose: Test shortcut_get_list
//& type: auto

int ITc_shortcut_get_list_p(void)
{
	START_TEST;
	int nRet = -1;

	g_bCallbackHit = false;
	g_bRequestCBCallbackHit = true;
	nRet = shortcut_get_list(TEST_SHORTCUT_APPID, ShortcutListCallBack, TESTSTRING);
#ifdef MOBILE //Starts MOBILE
	if (g_bShortcutNotSupported)
		{
		if(nRet != SHORTCUT_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif //End mobile
	if(nRet < 0)
	{
		FPRINTF("[Line : %d][%s] shortcut_get_list Failed,return invalid number of items\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_CALLBACK_STATUS("shortcut_get_list", g_bCallbackHit, g_bRequestCBCallbackHit);

	return 0;
}

/**
* @testcase 		ITc_shortcut_set_unset_remove_cb_p
* @since_tizen 		3.0
* @author			SRID(a.pandia1)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description		Registers and unregisters the callback function to listen the remove requests from applications
* @scenario			Call shortcut_set_remove_cb, shortcut_unset_remove_cb
* @apicovered		shortcut_set_remove_cb, shortcut_unset_remove_cb
* @passcase			If target API returns SHORTCUT_ERROR_NONE
* @failcase			If API fails to complete the scenario cycle
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
//& purpose: Registers and unregisters the callback function to listen the remove requests from applications
//& type: auto

int ITc_shortcut_set_unset_remove_cb_p(void)
{
	START_TEST;
	g_b2CallbackValueCheck = true;

	int nRet = -1;
	char *pszName = "Test";

	g_bCallbackHit = false;
	g_bRequestCBCallbackHit = false;

	nRet = shortcut_set_request_cb(ShortcutRequestCB, TESTSTRING);
#ifdef MOBILE //Starts MOBILE
	if (g_bShortcutNotSupported)
		{
		if(nRet != SHORTCUT_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
#endif //End mobile
	PRINT_RESULT(SHORTCUT_ERROR_NONE, nRet, "shortcut_set_request_cb", ShortcutError(nRet));

	nRet = shortcut_add_to_home(pszName, LAUNCH_BY_APP, TEST_SHORTCUT_APPID, g_pszICON_PATH, DUPLICATEALLOWED, ShortcutAddToHomeCB, TESTSTRING);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_add_to_home", ShortcutError(nRet), shortcut_unset_request_cb());
	CHECK_CALLBACK_STATUS("shortcut_set_request_cb", g_bCallbackHit, g_bRequestCBCallbackHit);
	
	g_bCallbackHitRemoveCb = false;
	// Target API
	nRet = shortcut_set_remove_cb(ShortcutRemoveCb, NULL);
	PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_set_remove_cb", ShortcutError(nRet), shortcut_unset_request_cb());
	
	// Callback Triggering API
	nRet = shortcut_remove_from_home(pszName, ShortcutRemoveFromHomeCB, NULL);
	PRINT_RESULT_CLEANUP(SHORTCUT_ERROR_NONE, nRet, "shortcut_remove_from_home", ShortcutError(nRet), shortcut_unset_remove_cb();shortcut_unset_request_cb());
	
	RUN_POLLING_LOOP;
	if(!g_bCallbackHitRemoveCb)
	{
		FPRINTF("[Line : %d][%s] Failed to hit callback ShortcutRemoveCb\\n", __LINE__, API_NAMESPACE);
		shortcut_unset_remove_cb();
		shortcut_unset_request_cb();
		return 1;
	}
	
	// Target API
	shortcut_unset_remove_cb();

	shortcut_unset_request_cb();
	return 0;
}
/** @} */
/** @} */
