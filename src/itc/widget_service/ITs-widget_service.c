//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-widget_service-common.h"

//& set: Widget_service

/** @addtogroup itc-widget_service
*  @ingroup itc
*  @{
*/
bool g_bSkipExecutionWithPass = false;
bool g_bSkipExecutionWithFail = false;
bool g_bWidgetServiceReadFeatureStatusDone = false;
bool g_bWidgetFeatureSupported = false;

/*******************************************************************CallBack Start*******************************************************************/

/**
* @function 		WidgetListCB
* @description	 	Widget List Callback
* @parameter		pkgid: package id , widgetid: widget id, data:The user data passed from the for each function
* @return 			int value
*/
static int WidgetListCB(const char *pkgid, const char *widgetid, int is_prime, void *data)
{
	FPRINTF("[Line: %d][%s] In WidgetListCB\\n", __LINE__, API_NAMESPACE);
	if ( (data == NULL) || (strcmp(data, TESTSTRING) != 0) )
	{
		g_bWidgetServiceCBFlag = false;
		FPRINTF("[Line: %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		if ( g_loop != NULL )
		{
			g_main_loop_quit(g_loop);
			g_loop = NULL;
		}
		return -1;
	}

	if ( strcmp(pkgid, TEST_TESTWIDGET_APPID) == 0 )
	{
		g_bWidgetServiceCBFlag = true;
		FPRINTF("[Line: %d][%s] In WidgetListCB\\n", __LINE__, API_NAMESPACE);

		strncpy(g_szPkgid, pkgid, strlen(pkgid)+1);
		strncpy(g_szWidgetid, widgetid, strlen(widgetid)+1);
		FPRINTF("[Line: %d][%s] PkgId is %s and WidgetId is %s\\n", __LINE__, API_NAMESPACE, g_szPkgid, g_szWidgetid);

		if ( g_loop != NULL )
		{
			g_main_loop_quit(g_loop);
			g_loop = NULL;
		}

		return -1;//-1 to break out of loop else continue
	}
	else
	{
		return WIDGET_ERROR_NONE;
	}
}

/**
* @function 		WidgetListByPkgIdCB
* @description	 	Widget List Callback
* @parameter		widget_id: widget id , is_prime: sent as 1 if the widget is a default widget, data: user data
* @return 			int value
*/
static int WidgetListByPkgIdCB(const char *widget_id, int is_prime, void *data)
{
	g_bWidgetServiceCBFlag = true;
	FPRINTF("[Line: %d][%s] In WidgetListByPkgIdCB\\n", __LINE__, API_NAMESPACE);

	if ( (data == NULL) || (strcmp(data, TESTSTRING) != 0) )
	{
		g_bWidgetServiceCBFlag = false;
		FPRINTF("[Line: %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		if ( g_loop != NULL )
		{
			g_main_loop_quit(g_loop);
			g_loop = NULL;
		}
		return -1;
	}

	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}

	return -1;//-1 to break out of loop else continue
}

/**
* @function 		WidgetLifecycleEventCB
* @description	 	Widget instance list Callback
* @parameter		widget_id: widget id , widget_lifecycle_event_e: lifecycle event, widget_instance_id: widget instance id, user_data:The user data passed from the for each function
* @return 			int value
*/
static int WidgetLifecycleEventCB(const char *widget_id, widget_lifecycle_event_e lifecycle_event, const char *widget_instance_id, void *data)
{
	g_bWidgetServiceCBFlag = true;
	FPRINTF("[Line: %d][%s] In WidgetLifecycleEventCB\\n", __LINE__, API_NAMESPACE);

	if ( (data == NULL) || (strcmp(data, TESTSTRING) != 0) )
	{
		g_bWidgetServiceCBFlag = false;
		FPRINTF("[Line: %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		if ( g_loop != NULL )
		{
			g_main_loop_quit(g_loop);
			g_loop = NULL;
		}
		return 0;
	}

	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}

	return 0;//false to break out of loop else continue
}

/**
* @function 		WidgetInstanceListCB
* @description	 	Widget instance list Callback
* @parameter		const char *widget_id, const char *instance_id, void *data
* @return 			int value
*/
static int WidgetInstanceListCB(const char *widget_id, const char *instance_id, void *data)
{
	g_bWidgetServiceCBFlag = true;
	FPRINTF("[Line: %d][%s] In WidgetInstanceListCB\\n", __LINE__, API_NAMESPACE);

	if((data == NULL) || (strcmp(data, TESTSTRING) != 0))
	{
		g_bWidgetServiceCBFlag = false;
		FPRINTF("[Line: %d][%s] Invalid data passed to callback\\n", __LINE__, API_NAMESPACE);
		if ( g_loop != NULL )
		{
			g_main_loop_quit(g_loop);
			g_loop = NULL;
		}
		return -1;
	}

	strncpy(g_szInstanceId, instance_id, strlen(instance_id)+1);
	FPRINTF("[Line: %d][%s] InstanceId is %s\\n", __LINE__, API_NAMESPACE, g_szInstanceId);

	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}

	return -1;//-1 to break out of loop else continue
}

/**
* @function 		WidgetDisableEventCB
* @description	 	Widget disable event Callback
* @parameter		const char *pszWidgetID, bool bIsdisabled, void *pszData
* @return		void
*/
static void WidgetDisableEventCB(const char *pszWidgetID, bool bIsdisabled, void *pszData)
{
	FPRINTF("[Line: %d][%s] In WidgetDisableEventCB\\n", __LINE__, API_NAMESPACE);
	return;
}
/********************************************************************CallBack End********************************************************************/

/**
 * @function 		ITs_widget_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_widget_service_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	TCT_CheckInstalledApp(1, TEST_TESTWIDGET_APPID);

	if ( false == g_bWidgetServiceReadFeatureStatusDone )
	{
		g_bWidgetFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIDGET_SERVICE_FEATURE, API_NAMESPACE);
		g_bWidgetServiceReadFeatureStatusDone = true;
	}

	int nTimeoutId = 0;
	g_bWidgetCreation = false;
	g_bWidgetServiceCBFlag = false;

	int nRet = widget_service_get_widget_list(WidgetListCB, TESTSTRING);
	if ( !g_bWidgetFeatureSupported )
	{
		if ( nRet == WIDGET_ERROR_NOT_SUPPORTED )
		{
			g_bSkipExecutionWithPass = true;
			return;
		}

		g_bSkipExecutionWithFail = true;
		return;
	}
	if ( nRet < 0 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_widget_list fails, error returned = %s[%d]\\n", __LINE__, API_NAMESPACE, WidgetServiceGetError(nRet), nRet);
		return;
	}

	RUN_POLLING_LOOP;
	if ( !g_bWidgetServiceCBFlag )
	{
		FPRINTF("[Line: %d][%s] WidgetListCB callback failed\\n", __LINE__, API_NAMESPACE);
		return;
	}

	g_bWidgetCreation = true;
	return;
}

/**
 * @function 		ITs_widget_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_widget_service_cleanup(void)
{
	return;
}

/** @addtogroup itc-widget_service-testcases
*  @brief 		Integration testcases for module widget_service
*  @ingroup 	itc-widget_service
*  @{
*/

//& purpose: Get widget size
//& type: auto
/**
* @testcase 			ITc_widget_service_get_size_type_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget size
* @scenario				Get widget size
* @apicovered			widget_service_get_size, widget_service_get_size_type
* @passcase				When widget_service_get_size_type is successful
* @failcase				If target API widget_service_get_size_type fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_size_type_p(void)
{
	START_TEST;
	widget_size_type_e eWidgetSizeType;
	int nWidth = 0, nHeight = 0;

	int nRet = widget_service_get_size(WIDGET_SIZE_TYPE_1x1, &nWidth, &nHeight);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_size", WidgetServiceGetError(nRet));

	nRet = widget_service_get_size_type(nWidth, nHeight, &eWidgetSizeType);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_size_type", WidgetServiceGetError(nRet));

	if ( eWidgetSizeType != WIDGET_SIZE_TYPE_1x1 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size_type failed, returned eWidgetSizeType = %d\\n", __LINE__, API_NAMESPACE, eWidgetSizeType);
		return 1;
	}

	return 0;
}

//& purpose: Get widget size
//& type: auto
/**
* @testcase 			ITc_widget_service_get_size_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget size
* @scenario				Get widget size
* @apicovered			widget_service_get_size
* @passcase				When widget_service_get_size is successful
* @failcase				If target API widget_service_get_size fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_size_p(void)
{
	START_TEST;
	int nWidth = 0, nHeight = 0;

	int nRet = widget_service_get_size(WIDGET_SIZE_TYPE_1x1, &nWidth, &nHeight);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_size", WidgetServiceGetError(nRet));

	if ( ( nWidth < 0 ) || ( nHeight < 0 ) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_size failed, returned nWidth = %d, nHeight = %d\\n", __LINE__, API_NAMESPACE, nWidth, nHeight);
		return 1;
	}

	return 0;
}

//& purpose: Get widget list
//& type: auto
/**
* @testcase 			ITc_widget_service_get_widget_list_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget list
* @scenario				Get widget list
* @apicovered			widget_service_get_widget_list
* @passcase				When widget_service_get_widget_list is successful
* @failcase				If target API widget_service_get_widget_list fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_widget_list_p(void)
{
	START_TEST;
	int nTimeoutId = 0;
	g_bWidgetServiceCBFlag = false;

	int nRet = widget_service_get_widget_list(WidgetListCB, TESTSTRING);
	if ( nRet < 0 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_widget_list fails, error returned = %s[%d]\\n", __LINE__, API_NAMESPACE, WidgetServiceGetError(nRet), nRet);
		return 1;
	}

	RUN_POLLING_LOOP;
	if ( !g_bWidgetServiceCBFlag )
	{
		FPRINTF("[Line: %d][%s] WidgetListCB callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Get widget app id
//& type: auto
/**
* @testcase 			ITc_widget_service_get_main_app_id_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget app id
* @scenario				Get widget app id
* @apicovered			widget_service_get_main_app_id
* @passcase				When widget_service_get_main_app_id is successful
* @failcase				If target API widget_service_get_main_app_id fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_main_app_id_p(void)
{
	START_TEST;
	char *pszAppId = NULL;

	pszAppId = widget_service_get_main_app_id(g_szWidgetid);
	if ( pszAppId == NULL )
	{
		VERDICTLASTRESULT("widget_service_get_main_app_id");
	}

	FREE_MEMORY(pszAppId);
	return 0;
}

//& purpose: widget service get widget name
//& type: auto
/**
* @testcase 			ITc_widget_service_get_name_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget name
* @scenario				get widget name
* @apicovered			widget_service_get_name
* @passcase				When widget_service_get_name is successful
* @failcase				If target API widget_service_get_name fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_name_p(void)
{
	START_TEST;
	char *pWidgetName = NULL;

	pWidgetName = widget_service_get_name(g_szWidgetid, LANGUAGE);
	if ( pWidgetName == NULL )
	{
		VERDICTLASTRESULT("widget_service_get_name");
	}

	FREE_MEMORY(pWidgetName);
	return 0;
}

//& purpose: widget service get widget pkgid
//& type: auto
/**
* @testcase 			ITc_widget_service_get_package_id_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget pkgid
* @scenario				get widget pkgid
* @apicovered			widget_service_get_package_id
* @passcase				When widget_service_get_package_id is successful
* @failcase				If target API widget_service_get_package_id fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_package_id_p(void)
{
	START_TEST;
	char *pPackageId = NULL;

	pPackageId = widget_service_get_package_id(g_szWidgetid);
	if ( (pPackageId == NULL) || (strcmp(g_szPkgid, pPackageId) != 0) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_package_id failed, pPackageId is not correct\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pPackageId);
		return 1;
	}

	FREE_MEMORY(pPackageId);
	return 0;
}

//& purpose: Get widget widget id
//& type: auto
/**
* @testcase 			ITc_widget_service_get_widget_id_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget id
* @scenario				Get widget id
* @apicovered			widget_service_get_widget_id
* @passcase				When widget_service_get_widget_id is successful
* @failcase				If target API widget_service_get_widget_id fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_widget_id_p(void)
{
	START_TEST;
	char *pWidgetId = NULL;

	pWidgetId = widget_service_get_widget_id(g_szPkgid);
	if ( (pWidgetId == NULL) || (strcmp(g_szWidgetid, pWidgetId) != 0) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_widget_id failed, pWidgetId is not correct\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pWidgetId);
		return 1;
	}

	FREE_MEMORY(pWidgetId);
	return 0;
}

//& purpose: widget service get widget list by pkgid
//& type: auto
/**
* @testcase 			ITc_widget_service_get_widget_list_by_pkgid_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget list by pkgid
* @scenario				get widget list by pkgid
* @apicovered			widget_service_get_widget_list_by_pkgid
* @passcase				When widget_service_get_widget_list_by_pkgid is successful
* @failcase				If target API widget_service_get_widget_list_by_pkgid fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_widget_list_by_pkgid_p(void)
{
	START_TEST;
	int nTimeoutId = 0;

	g_bWidgetServiceCBFlag = false;
	int nRet = widget_service_get_widget_list_by_pkgid(g_szPkgid, WidgetListByPkgIdCB, TESTSTRING);
	if ( nRet < 0 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_widget_list_by_pkgid failed, error returned = %s[%d]\\n", __LINE__, API_NAMESPACE, WidgetServiceGetError(nRet), nRet);
		return 1;
	}

	RUN_POLLING_LOOP;

	if ( !g_bWidgetServiceCBFlag )
	{
		FPRINTF("[Line: %d][%s] WidgetListByPkgIdCB callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: widget service get supported sizes
//& type: auto
/**
* @testcase 			ITc_widget_service_get_supported_sizes_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget supported sizes
* @scenario				get widget supported sizes
* @apicovered			widget_service_get_supported_sizes
* @passcase				When widget_service_get_supported_sizes is successful
* @failcase				If target API widget_service_get_supported_sizes fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_supported_sizes_p(void)
{
	START_TEST;
	int nCnt = INT_MAX;
	int *pWidth = NULL, *pHeight = NULL;

	int nRet = widget_service_get_supported_sizes(g_szWidgetid, &nCnt, &pWidth, &pHeight);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_sizes", WidgetServiceGetError(nRet));
	if ( (pWidth == NULL) || (pHeight == NULL) || (nCnt < 0) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_sizes failed, no of supported sizes returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pWidth);
		FREE_MEMORY(pHeight);
		return 1;
	}

	FREE_MEMORY(pWidth);
	FREE_MEMORY(pHeight);
	return 0;
}

//& purpose: widget service get supported types
//& type: auto
/**
* @testcase 			ITc_widget_service_get_supported_size_types_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget supported types
* @scenario				get widget supported types
* @apicovered			widget_service_get_supported_size_types
* @passcase				When widget_service_get_supported_size_types is successful
* @failcase				If target API widget_service_get_supported_size_types fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_supported_size_types_p(void)
{
	START_TEST;
	int nCnt = INT_MAX;
	int *pTypes = NULL;

	int nRet = widget_service_get_supported_size_types(g_szWidgetid, &nCnt, &pTypes);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));

	if ( nCnt < 0 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_size_types failed, no of supported sizes types returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pTypes);
		return 1;
	}

	FREE_MEMORY(pTypes);
	return 0;
}

//& purpose: widget service get app id of setup app
//& type: auto
/**
* @testcase 			ITc_widget_service_get_app_id_of_setup_app_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get app id of setup app
* @scenario				get app id of setup app
* @apicovered			widget_service_get_app_id_of_setup_app
* @passcase				When widget_service_get_app_id_of_setup_app is successful
* @failcase				If target API widget_service_get_app_id_of_setup_app fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_app_id_of_setup_app_p(void)
{
	START_TEST;
	char *pAppIdOfSetup = NULL;

	pAppIdOfSetup = widget_service_get_app_id_of_setup_app(g_szWidgetid);
	if ( pAppIdOfSetup == NULL )
	{
		VERDICTLASTRESULT("widget_service_get_app_id_of_setup_app");
	}

	FREE_MEMORY(pAppIdOfSetup);
	return 0;
}

//& purpose: Get widget icon
//& type: auto
/**
* @testcase 			ITc_widget_service_get_icon_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function requests get widget icon
* @scenario				Get widget icon
* @apicovered			widget_service_get_icon
* @passcase				When widget_service_get_icon is successful
* @failcase				If target API widget_service_get_icon fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_icon_p(void)
{
	START_TEST;
	char *pIcon = NULL;

	pIcon = widget_service_get_icon(g_szPkgid, LANGUAGE);
	if ( pIcon == NULL )
	{
		VERDICTLASTRESULT("widget_service_get_icon");
	}

	FREE_MEMORY(pIcon);
	return 0;
}

//& purpose: widget service get preview image path
//& type: auto
/**
* @testcase 			ITc_widget_service_get_preview_image_path_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function get widget preview image path
* @scenario				get widget preview image path
* @apicovered			widget_service_get_preview_image_path
* @passcase				When widget_service_get_preview_image_path is successful
* @failcase				If target API widget_service_get_preview_image_path fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_preview_image_path_p(void)
{
	START_TEST;
	char *pImagePath = NULL;
	int *pTypes = NULL;
	int nCnt = INT_MAX;

	int nRet = widget_service_get_supported_size_types(g_szWidgetid, &nCnt, &pTypes);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));
	if ( (nCnt < 0) || (pTypes == NULL) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_size_types failed, no of supported sizes types returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pTypes);
		return 1;
	}

	pImagePath = widget_service_get_preview_image_path(g_szWidgetid, *pTypes);
	if ( pImagePath == NULL )
	{
		FREE_MEMORY(pTypes);
		VERDICTLASTRESULT("widget_service_get_preview_image_path");
	}

	FREE_MEMORY(pTypes);
	FREE_MEMORY(pImagePath);
	return 0;
}

//& purpose: Test widget_service_get_nodisplay
//& type: auto
/**
* @testcase 			ITc_widget_service_get_nodisplay_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Test widget_service_get_nodisplay
* @scenario				Call widget_service_get_nodisplay
* @apicovered			widget_service_get_nodisplay
* @passcase				When widget_service_get_nodisplay is successful
* @failcase				If target API widget_service_get_nodisplay fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_nodisplay_p(void)
{
	START_TEST;
	int nDisplay = -1;

	nDisplay = widget_service_get_nodisplay(g_szWidgetid);
	if ( nDisplay < 0 )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_nodisplay failed, nDisplay is less then 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: check if widget need mouse event
//& type: auto
/**
* @testcase 			ITc_widget_service_get_need_of_mouse_event_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function check if widget need mouse event
* @scenario				check if widget need mouse event
* @apicovered			widget_service_get_need_of_mouse_event
* @passcase				When widget_service_get_need_of_mouse_event is successful
* @failcase				If target API widget_service_get_need_of_mouse_event fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_need_of_mouse_event_p(void)
{
	START_TEST;
	bool bNeedMouseMvent = false;
	int *pTypes = NULL;
	int nCnt = INT_MAX;

	int nRet = widget_service_get_supported_size_types(g_szWidgetid, &nCnt, &pTypes);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));
	if ( (nCnt < 0) || (pTypes == NULL) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_size_types failed, no of supported sizes types returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pTypes);
		return 1;
	}

	nRet = widget_service_get_need_of_mouse_event(g_szPkgid, *pTypes, &bNeedMouseMvent);
	PRINT_RESULT_CLEANUP(WIDGET_ERROR_NONE, nRet, "widget_service_get_need_of_mouse_event", WidgetServiceGetError(nRet), FREE_MEMORY(pTypes));

	FREE_MEMORY(pTypes);
	return 0;
}

//& purpose: check if widget need frame
//& type: auto
/**
* @testcase 			ITc_widget_service_get_need_of_frame_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function check if widget need frame
* @scenario				check if widget need frame
* @apicovered			widget_service_get_need_of_frame
* @passcase				When widget_service_get_need_of_frame is successful
* @failcase				If target API widget_service_get_need_of_frame fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_need_of_frame_p(void)
{
	START_TEST;
	bool bNeedOfFrame = false;
	int *pTypes = NULL;
	int nCnt = INT_MAX;

	int nRet = widget_service_get_supported_size_types(g_szWidgetid, &nCnt, &pTypes);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));
	if ( (nCnt < 0) || (pTypes == NULL) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_size_types failed, no of supported sizes types returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pTypes);
		return 1;
	}

	nRet = widget_service_get_need_of_frame(g_szPkgid, *pTypes, &bNeedOfFrame);
	PRINT_RESULT_CLEANUP(WIDGET_ERROR_NONE, nRet, "widget_service_get_need_of_frame", WidgetServiceGetError(nRet), FREE_MEMORY(pTypes));

	FREE_MEMORY(pTypes);
	return 0;
}

//& purpose: check if widget need of touch effect
//& type: auto
/**
* @testcase 			ITc_widget_service_get_need_of_touch_effect_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function check if widget need of touch effect
* @scenario				check if widget need of touch effect
* @apicovered			widget_service_get_need_of_touch_effect
* @passcase				When widget_service_get_need_of_touch_effect is successful
* @failcase				If target API widget_service_get_need_of_touch_effect fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_get_need_of_touch_effect_p(void)
{
	START_TEST;
	bool bNeedOfTouchEvent = false;
	int *pTypes = NULL;
	int nCnt = INT_MAX;

	int nRet = widget_service_get_supported_size_types(g_szWidgetid, &nCnt, &pTypes);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));
	if ( (nCnt < 0) || (pTypes == NULL) )
	{
		FPRINTF("[Line: %d][%s] widget_service_get_supported_size_types failed, no of supported sizes types returned = %d\\n", __LINE__, API_NAMESPACE, nCnt);
		FREE_MEMORY(pTypes);
		return 1;
	}

	nRet = widget_service_get_need_of_touch_effect(g_szPkgid, *pTypes, &bNeedOfTouchEvent);
	PRINT_RESULT_CLEANUP(WIDGET_ERROR_NONE, nRet, "widget_service_get_need_of_touch_effect", WidgetServiceGetError(nRet), FREE_MEMORY(pTypes));

	FREE_MEMORY(pTypes);
	return 0;
}

//& purpose: widget service set/unset lifecycle event cb
//& type: auto
/**
* @testcase 			ITc_widget_service_set_unset_lifecycle_event_cb_p
* @since_tizen			2.3.1
* @author            	SRID(abhishek1.g)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			This function set/unset lifecycle event cb
* @scenario				set/unset lifecycle event cb
* @apicovered			widget_service_set_lifecycle_event_cb, widget_service_unset_lifecycle_event_cb
* @passcase				When widget_service_set_lifecycle_event_cb ,widget_service_unset_lifecycle_event_cb is successful
* @failcase				If target API widget_service_set_lifecycle_event_cb, widget_service_unset_lifecycle_event_cb fails or any precondition API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_widget_service_set_unset_lifecycle_event_cb_p(void)
{
	START_TEST;

	int nRet = widget_service_set_lifecycle_event_cb(g_szWidgetid, WidgetLifecycleEventCB, TESTSTRING);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_set_lifecycle_event_cb", WidgetServiceGetError(nRet));

	nRet = widget_service_unset_lifecycle_event_cb(g_szWidgetid, NULL);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_unset_lifecycle_event_cb", WidgetServiceGetError(nRet));

	return 0;
}

//& purpose: widget service set/unset lifecycle event cb
//& type: auto
/**
* @testcase 		ITc_widget_service_set_unset_disable_event_cb_p
* @since_tizen		5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Sets and Unset the callback function for widget disable event.
* @scenario		set/unset disable event cb
* @apicovered		widget_service_set_disable_event_cb, widget_service_unset_disable_event_cb
* @passcase		When widget_service_set_disable_event_cb, widget_service_unset_disable_event_cb is successful
* @failcase		If target API widget_service_set_disable_event_cb, widget_service_unset_disable_event_cb fails or any precondition API fails
* @precondition	NA
* @postcondition	NA
*/
int ITc_widget_service_set_unset_disable_event_cb_p(void)
{
	START_TEST;
	int nRet = WIDGET_ERROR_NONE;

	//Target API
	nRet = widget_service_set_disable_event_cb(WidgetDisableEventCB, TESTSTRING);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_set_disable_event_cb", WidgetServiceGetError(nRet));

	//Target api
	nRet = widget_service_unset_disable_event_cb();
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_unset_disable_event_cb", WidgetServiceGetError(nRet));

	return 0;
}

//& purpose: Gets the 'disabled' state of a widget
//& type: auto
/**
* @testcase		ITc_widget_service_get_widget_disabled_p
* @since_tizen		5.5
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 		auto
* @description		Gets the 'disabled' state of a widget.
* @scenario		Gets the 'disabled' state of a widget.
* @apicovered		widget_service_get_widget_disabled
* @passcase		When widget_service_get_widget_disabled is successful
* @failcase		If target API widget_service_get_widget_disabled fails or any precondition API fails
* @precondition	NA
* @postcondition	NA
*/
int ITc_widget_service_get_widget_disabled_p(void)
{
	START_TEST;

	int nRet = WIDGET_ERROR_NONE;
	bool bIsDisabled = true;

	//Target API
	nRet = widget_service_get_widget_disabled(TEST_TESTWIDGET_APPID, &bIsDisabled);
	PRINT_RESULT(WIDGET_ERROR_NONE, nRet, "widget_service_get_widget_disabled", WidgetServiceGetError(nRet));
	PRINT_RESULT(false, bIsDisabled, "widget_service_get_widget_disabled", WidgetServiceGetError(nRet));

	return 0;
}

/** @} */
/** @} */
