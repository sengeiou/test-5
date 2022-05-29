#include "CTs-platform-permission-common.h"

#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include <app.h>
#include "widget_service.h"
#include "widget_errno.h"
#include <Evas.h>
#include <Ecore_Evas.h>
#include <Edje.h>
#include "widget_viewer_evas.h"

#define WIDGET_VIEWER_EVAS_FEATURE	"http://tizen.org/feature/shell.appwidget"
#define SAMPLE_PKGNAME				"org.tizen.sample"
#define SAMPLE_WIDGET				SAMPLE_PKGNAME

Evas_Object *g_win = NULL;



/**
 * @function 		WidgetServiceGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return 			error string
 */
char* WidgetViewerGetError(int nRet)
{
	char *szErrorVal = "UNKNOWN ERROR";

	switch(nRet)
	{
		case WIDGET_ERROR_NONE:						szErrorVal = "WIDGET_ERROR_NONE";			break;
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
	}
	return szErrorVal;
}

/**
* @function         CTs_platform_permission_WidgetViewer_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_WidgetViewer_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_WidgetViewer_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_WidgetViewer_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_WidgetViewer_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_WidgetViewer_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:Checking tizen.org/privilege/widget.viewer privilege
//& type: auto
/**
* @testcase			CTc_WidgetViewer_PrivilegeWidgetViewer
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			widget viewer evas initialize deinitialize	
* @apicovered		Call widget_viewer_evas_init, widget_viewer_evas_fini
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_WidgetViewer_PrivilegeWidgetViewer(void)
{
	START_TEST;
	int nRet = -1;

	bool bWidgetFeatureSupported = TCTCheckSystemInfoFeatureSupported(WIDGET_VIEWER_EVAS_FEATURE, API_NAMESPACE);
	if ( false == bWidgetFeatureSupported )
    {
        FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, WIDGET_VIEWER_EVAS_FEATURE);
        return 0;
    }
	
	elm_init(0, NULL);
	elm_config_preferred_engine_set("opengl_x11");
	g_win = elm_win_add(NULL, "ITC WIN", ELM_WIN_BASIC);
	
	nRet = widget_viewer_evas_init(g_win);
	if(nRet == WIDGET_ERROR_NONE)
	{
		if ( g_win )
		{
			evas_object_del(g_win);
		}
		widget_viewer_evas_fini();		
		elm_shutdown();
	}	
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "widget_viewer_evas_init", WidgetViewerGetError(nRet),evas_object_del(g_win););
	

	return 0;
}
