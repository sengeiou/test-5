#include "CTs-platform-permission-common.h"
#include <shortcut_manager.h>
#define ICON_PATH					"/opt/usr/media/icon.png"
#define	DUPLICATEALLOWED			1
#define PKGID						"native.shortcut-itc"
#define TESTSTRING					"Test"
#define SHORTCUTPERIOD				-1.0f
#define TIMEOUT_CB					15000

#define QUIT_GMAIN_LOOP {\
		if ( g_pShortcutMainLoop )\
		{\
			g_main_loop_quit(g_pShortcutMainLoop);\
			g_pShortcutMainLoop = NULL;\
		}\
}\


#define QUIT_GMAIN_LOOP_CONDITIONAL(CallbackHit1, CallbackHit2) {\
		if(CallbackHit1 && CallbackHit2)\
		{\
			if ( g_pShortcutMainLoop )\
			{\
				g_main_loop_quit(g_pShortcutMainLoop);\
				g_pShortcutMainLoop = NULL;\
			}\
		}\
}\
gboolean ShortcutTimeoutFunction(gpointer data);
#define RUN_POLLING_LOOP {\
	g_pShortcutMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(TIMEOUT_CB, ShortcutTimeoutFunction, g_pShortcutMainLoop);\
	g_main_loop_run(g_pShortcutMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pShortcutMainLoop = NULL;\
	g_nTimeoutId = 0;\
}

int g_nTimeoutId;
GMainLoop *g_pShortcutMainLoop;
bool g_bCallbackHit;
bool g_bRequestCBCallbackHit;
bool g_b2CallbackValueCheck;

/**
 * @function 		ShortcutTimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
gboolean ShortcutTimeoutFunction(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}
/**
* @function 		CTs_platform_permission_shortcut_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_shortcut_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_shortcut_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_shortcut_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
 * @function 		ShortcutError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* ShortcutError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case SHORTCUT_ERROR_NONE:				szErrorVal = "SHORTCUT_ERROR_NONE";					break;
		case SHORTCUT_ERROR_NO_SPACE:			szErrorVal = "SHORTCUT_ERROR_NO_SPACE";				break;
		case SHORTCUT_ERROR_EXIST:				szErrorVal = "SHORTCUT_ERROR_EXIST";				break;
		case SHORTCUT_ERROR_FAULT:				szErrorVal = "SHORTCUT_ERROR_FAULT";				break;
		case SHORTCUT_ERROR_NOT_SUPPORTED:		szErrorVal = "SHORTCUT_ERROR_NOT_SUPPORTED";		break;
		case SHORTCUT_ERROR_RESOURCE_BUSY:		szErrorVal = "SHORTCUT_ERROR_RESOURCE_BUSY";		break;
		case SHORTCUT_ERROR_INVALID_PARAMETER:	szErrorVal = "SHORTCUT_ERROR_INVALID_PARAMETER";	break;
		case SHORTCUT_ERROR_COMM:				szErrorVal = "SHORTCUT_ERROR_COMM";					break;
		case SHORTCUT_ERROR_OUT_OF_MEMORY:		szErrorVal = "SHORTCUT_ERROR_OUT_OF_MEMORY";		break;
		case SHORTCUT_ERROR_IO_ERROR:			szErrorVal = "SHORTCUT_ERROR_IO_ERROR";				break;
		case SHORTCUT_ERROR_PERMISSION_DENIED:	szErrorVal = "SHORTCUT_ERROR_PERMISSION_DENIED";	break;
		default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}
/**
* @function 			Shortcut_response_cb
* @description 			Called to receive the result of shortcut_add_to_home().
* @parameter	[IN]	nRet	Result value, it could be 0 if succeed to add a shortcut, or errno
*				[IN]	pUserData	Callback data
* @precondition			NA
* @return 				Result value
*/
static int Shortcut_response_cb(int nRet, void *pUserData)
{
	return nRet;
}
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
	return SHORTCUT_ERROR_NONE;
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

	return SHORTCUT_ERROR_NONE;
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
	return SHORTCUT_ERROR_NONE;
}

//& purpose: checking http://tizen.org/privilege/shortcut privilege
//& type: auto
/**
* @testcase			CTc_Shortcut_PrivilegeShortcut
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Add a shortcut to home
* @apicovered		shortcut_add_to_home
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Shortcut_PrivilegeShortcut_add_to_home(void)
{
	START_TEST;

#ifdef MOBILE //Starts MOBILE
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_SHORTCUT, bIsSupported, API_NAMESPACE);
        if ( false == bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_SHORTCUT);
                return 0;
        }
#endif //End mobile

	int nRet = shortcut_add_to_home("success", LAUNCH_BY_APP, NULL, NULL, 1, Shortcut_response_cb, (void *)2);
	RUN_POLLING_LOOP;
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "shortcut_add_to_home", ShortcutError(nRet));
	return 0;
}

//& purpose: Test shortcut_add_to_home_widget
//& type: auto
/**
* @testcase 		CTc_Shortcut_PrivilegeShortcut_set_request_cb
* @since_tizen 		2.4
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description		Test shortcut_set_request_cb
* @scenario			Call shortcut_set_request_cb
* @apicovered		shortcut_set_request_cb
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
int CTc_Shortcut_PrivilegeShortcut_set_request_cb(void)
{
	START_TEST;

	int nRet = -1;

#ifdef MOBILE //Starts MOBILE
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_SHORTCUT, bIsSupported, API_NAMESPACE);
        if ( false == bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_SHORTCUT);
                return 0;
        }
#endif //End mobile
	
	nRet = shortcut_set_request_cb(ShortcutRequestCB, TESTSTRING);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "shortcut_set_request_cb", ShortcutError(nRet));
		
	return 0;
}
//& purpose: Test shortcut_add_to_home_widget
//& type: auto
/**
* @testcase 		ITc_shortcut_add_to_home_widget_p
* @since_tizen 		2.4
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description		Test shortcut_add_to_home_widget
* @scenario			Call shortcut_add_to_home_widget
* @apicovered		shortcut_add_to_home_widget
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		Prepare the callback function
* @postcondition	You have to check the return status from the callback function which is passed by the argument.
*/
int CTc_Shortcut_PrivilegeShortcut_add_to_home_widget(void)
{
	START_TEST;
	
	int nRet = -1;
	char *pszName = "Test";

#ifdef MOBILE //Starts MOBILE
	bool bIsSupported = false;

        IS_FEATURE_SUPPORTED(FEATURE_SHORTCUT, bIsSupported, API_NAMESPACE);
        if ( false == bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_SHORTCUT);
                return 0;
        }
#endif //End mobile

	nRet = shortcut_add_to_home_widget(pszName, WIDGET_SIZE_1x1, APPID, ICON_PATH, SHORTCUTPERIOD, DUPLICATEALLOWED, ShortcutAddToHomeWidgetCB, TESTSTRING);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "shortcut_add_to_home_widget", ShortcutError(nRet));
/*
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
		nRet = shortcut_add_to_home_widget(pszName, eShortcutWidgetSize[enum_counter1], APPID, ICON_PATH, SHORTCUTPERIOD, DUPLICATEALLOWED, ShortcutAddToHomeWidgetCB, TESTSTRING);
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "shortcut_add_to_home_widget", ShortcutError(nRet));
	}
	*/

	return 0;
}
//& purpose: Test shortcut_get_list
//& type: auto
/**
* @testcase 		CTc_Shortcut_PrivilegeShortcut_get_list
* @since_tizen 		2.4
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description		Test shortcut_get_list
* @scenario			Call shortcut_get_list
* @apicovered		shortcut_get_list
* @passcase			If all privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If all privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		Prepare the callback function
* @postcondition	NA
*/

int CTc_Shortcut_PrivilegeShortcut_get_list(void)
{
	START_TEST;
	int nRet = -1;

#ifdef MOBILE //Starts MOBILE
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_SHORTCUT, bIsSupported, API_NAMESPACE);
        if ( false == bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_SHORTCUT);
                return 0;
        }
#endif //End mobile

	nRet = shortcut_get_list("org.tizen.sample", ShortcutListCallBack, NULL);
	RUN_POLLING_LOOP;
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "shortcut_get_list", ShortcutError(nRet));
		
	return 0;
}
