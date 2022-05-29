#include "CTs-platform-permission-common.h"
#include <glib.h>
#include <widget_service.h>
#include <widget_errno.h>

#define TESTSTRING					"Test"
#define WIDGET_SERVICE_FEATURE		"http://tizen.org/feature/shell.appwidget"
#define PATH_LEN					1024
#define LANGUAGE					"en-us"
//#define TESTPACKAGE					"org.tizen.testwidget"
#define TIMEOUT_CB 					30000
#define RUN_POLLING_LOOP {\
	if ( g_bWidgetServiceCBFlag == false )\
	{\
		g_loop = g_main_loop_new(NULL, false);\
		nTimeoutId = g_timeout_add(TIMEOUT_CB, WidgetServiceTimeout, g_loop);\
		g_main_loop_run(g_loop);\
		g_source_remove(nTimeoutId);\
		g_loop = NULL;\
	}\
}
/**
 * @function 		WidgetServiceTimeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean WidgetServiceTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line: %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}
int g_nRet;
GMainLoop *g_loop;
bool g_bWidgetServiceCBFlag;
bool g_bWidgetCreation;
char g_szPkgid[PATH_LEN];
char g_szWidgetid[PATH_LEN];

/**
 * @function 		WidgetServiceGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
/*char* WidgetServiceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
		case WIDGET_ERROR_NONE:						szErrorVal = "WIDGET_ERROR_NONE";						break;
		case WIDGET_ERROR_INVALID_PARAMETER:		szErrorVal = "WIDGET_ERROR_INVALID_PARAMETER";			break;
		case WIDGET_ERROR_OUT_OF_MEMORY:			szErrorVal = "WIDGET_ERROR_OUT_OF_MEMORY";				break;
		case WIDGET_ERROR_RESOURCE_BUSY:			szErrorVal = "WIDGET_ERROR_RESOURCE_BUSY";				break;
		case WIDGET_ERROR_PERMISSION_DENIED:		szErrorVal = "WIDGET_ERROR_PERMISSION_DENIED";			break;
		case WIDGET_ERROR_CANCELED:					szErrorVal = "WIDGET_ERROR_CANCELED";					break;
		case WIDGET_ERROR_IO_ERROR:					szErrorVal = "WIDGET_ERROR_IO_ERROR";					break;
		case WIDGET_ERROR_TIMED_OUT:				szErrorVal = "WIDGET_ERROR_TIMED_OUT";					break;
		case WIDGET_ERROR_NOT_SUPPORTED:			szErrorVal = "WIDGET_ERROR_NOT_SUPPORTED";				break;
		case WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "WIDGET_ERROR_FILE_NO_SPACE_ON_DEVICE";	break;
		case WIDGET_ERROR_FAULT:					szErrorVal = "WIDGET_ERROR_FAULT";						break;
		case WIDGET_ERROR_ALREADY_EXIST:			szErrorVal = "WIDGET_ERROR_ALREADY_EXIST";				break;
		case WIDGET_ERROR_ALREADY_STARTED:			szErrorVal = "WIDGET_ERROR_ALREADY_STARTED";			break;
		case WIDGET_ERROR_NOT_EXIST:				szErrorVal = "WIDGET_ERROR_NOT_EXIST";					break;
		case WIDGET_ERROR_DISABLED:					szErrorVal = "WIDGET_ERROR_DISABLED";					break;
		default:									szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}*/

/**
* @function 		WidgetListByPkgIdCB
* @description	 	Widget List Callback
* @parameter		widget_id: widget id , is_prime: sent as 1 if the widget is a default widget, data: user data
* @return 			int value
*/
static int WidgetListByPkgIdCB(const char *widget_id, int is_prime, void *data)
{/*
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
	*/
	return 0;
}
/**
* @function 		CTs_platform_permission_widgetservice_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_widgetservice_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_widgetservice_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_widgetservice_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_widgetservice_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_widgetservice_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

static int widget_list_cb_p(const char *pkgid, const char *widget_id, int is_prime, void *data)
{
	return WIDGET_ERROR_NONE;
}
//& purpose: Get widget list
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_widget_list
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests get widget list
* @scenario				Get widget list
* @apicovered			widget_service_get_widget_list
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_widget_list(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	int nTimeoutId =-1;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	int nRet = widget_service_get_widget_list(widget_list_cb_p, "org.tizen.testwidget");
	RUN_POLLING_LOOP;
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_widget_list", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: Get widget icon
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_icon
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests get widget icon
* @scenario				Get widget Icon
* @apicovered			widget_service_get_icon
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_icon(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	//char *pIcon = NULL;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	
	//pIcon = widget_service_get_icon("org.tizen.sample", NULL);
	widget_service_get_icon("org.tizen.testwidget", NULL);
	int nRet =get_last_result();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_icon", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: Get widget id
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_widget_id
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests get widget id
* @scenario				Get widget widget id
* @apicovered			widget_service_get_widget_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_widget_id(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	//char *pWidgetId = NULL;
	
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	
	//pWidgetId = widget_service_get_widget_id("org.tizen.testwidget");
	widget_service_get_widget_id("org.tizen.testwidget");
	int nRet =get_last_result();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_widget_id", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: Get widget  Main id
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_widget_main_id
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests get widget Main id
* @scenario				Get widget Main id
* @apicovered			widget_service_get_main_app_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_widget_main_id(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	//char *pWidgetId = NULL;
	
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	
	//pWidgetId = widget_service_get_main_app_id("org.tizen.sample");
	widget_service_get_main_app_id("org.tizen.testwidget");
	int nRet =get_last_result();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_main_app_id", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: Get widget  Mouse Support
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_widget_mouse_support
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests get widget id
* @scenario				Get widget Mouse Support
* @apicovered			widget_service_get_need_of_mouse_event
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_widget_mouse_support(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	bool bNeedMouseMvent = false;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}

	int nRet = widget_service_get_need_of_mouse_event("org.tizen.testwidget", WIDGET_SIZE_TYPE_1x1 , &bNeedMouseMvent);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_need_of_mouse_event", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: widget service get app id of setup app
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_app_id_of_setup_app
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function get app id of setup app
* @scenario				get app id of setup app
* @apicovered			widget_service_get_app_id_of_setup_app
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_app_id_of_setup_app(void)
{
	START_TEST;
	char *pAppIdOfSetup = NULL;
	int nRet =0;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	pAppIdOfSetup = widget_service_get_app_id_of_setup_app("org.tizen.testwidget");
	nRet = get_last_result();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_app_id_of_setup_app", WidgetServiceGetError(nRet),FREE_MEMORY(pAppIdOfSetup));
	

	FREE_MEMORY(pAppIdOfSetup);
	return 0;
}
//& purpose: check if widget need of touch effect
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_need_of_touch_effect
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function check if widget need of touch effect
* @scenario				check if widget need of touch effect
* @apicovered			widget_service_get_need_of_touch_effect
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_need_of_touch_effect(void)
{
	START_TEST;
	bool bNeedOfTouchEvent = false;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	

	int nRet = widget_service_get_need_of_touch_effect("org.tizen.testwidget", WIDGET_SIZE_TYPE_1x1, &bNeedOfTouchEvent);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_need_of_touch_effect", WidgetServiceGetError(nRet));

	return 0;
}
//& purpose: widget service get widget list by pkgid
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_widget_list_by_pkgid
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function get widget list by pkgid
* @scenario				get widget list by pkgid
* @apicovered			widget_service_get_widget_list_by_pkgid
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_widget_list_by_pkgid(void)
{
	START_TEST;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}
	g_bWidgetServiceCBFlag = false;
	int nRet = widget_service_get_widget_list_by_pkgid("org.tizen.testwidget", WidgetListByPkgIdCB, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_widget_list_by_pkgid", WidgetServiceGetError(nRet));
	

	

	return 0;
}
//& purpose: widget service get package id
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_package_id
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function get widget   package id
* @scenario				 get package id
* @apicovered			widget_service_get_package_id
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_package_id(void)
{
	START_TEST;
	char *pPackageId = NULL;
	
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}

	pPackageId = widget_service_get_package_id("org.tizen.testwidget");
	int nRet = get_last_result();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_package_id", WidgetServiceGetError(nRet));
	

	FREE_MEMORY(pPackageId);
	return 0;
}
//& purpose: widget service get widget name
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_name
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function get widget name
* @scenario				get widget name
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_name(void)
{
	START_TEST;
	char *pWidgetName = NULL;
	
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}

	pWidgetName = widget_service_get_name("org.tizen.testwidget", LANGUAGE);
	int nRet = get_last_result();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_name", WidgetServiceGetError(nRet));
	

	FREE_MEMORY(pWidgetName);
	return 0;
}
//& purpose: widget service get supported sizes
//& type: auto
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_supported_sizes
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function get widget supported sizes
* @scenario				get widget supported sizes
* @apicovered			widget_service_get_supported_sizes
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/
int CTc_WidgetService_PrivilegeWidgetViewer_get_supported_sizes(void)
{
	START_TEST;
	int nCnt = INT_MAX;
	int *pWidth = NULL, *pHeight = NULL;
	
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}

	int nRet = widget_service_get_supported_sizes("org.tizen.testwidget", &nCnt, &pWidth, &pHeight);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_supported_sizes", WidgetServiceGetError(nRet));

	FREE_MEMORY(pWidth);
	FREE_MEMORY(pHeight);
	return 0;
}
//& purpose: Get widget  supported size types
/**
* @testcase 			CTc_WidgetService_PrivilegeWidgetViewer_get_supported_size_types
* @since_tizen			2.3.1
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			This function requests Get widget  supported size types
* @scenario				Get widget  supported size types
* @apicovered			widget_service_get_supported_size_types
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition			NA
* @postcondition		NA
*/

int CTc_WidgetService_PrivilegeWidgetViewer_get_supported_size_types(void)
{
	START_TEST;
	bool g_bIsSupported = false;
	int *pTypes = NULL;
	int nCnt = INT_MAX;
	IS_FEATURE_SUPPORTED(WIDGET_SERVICE_FEATURE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_SERVICE_FEATURE);
		return 0;
	}

	int nRet = widget_service_get_supported_size_types("Test", &nCnt, &pTypes);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_service_get_supported_size_types", WidgetServiceGetError(nRet));
	
	FREE_MEMORY(pTypes);
	return 0;
}
