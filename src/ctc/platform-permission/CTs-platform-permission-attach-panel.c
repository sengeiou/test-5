#include "CTs-platform-permission-common.h"

#include "assert.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <glib.h>
#include <app.h>
#include <Evas.h>
#include <Ecore_Evas.h>
#include <Edje.h>

#include <attach-panel/attach_panel.h>


#define ATTACH_PANEL_FEATURE1	"%http://tizen.org/feature/camera"
#define ATTACH_PANEL_FEATURE2	"%http://tizen.org/feature/microphone"

bool g_bAttachPanelFeatureSupported = false;

static struct info {
	Evas_Object *win;
	Evas_Object *conformant;
	GMainLoop *mainloop;
    int is_asserted;
} s_info = {
        .is_asserted = 0,
        .win = NULL,
        .conformant = NULL,
     .mainloop = NULL,
};


/**
 * @function		AttachPanelInfoGetError
 * @description		Maps error enums to string values
 * @parameter		nRet: error code returned
 * @return			error string
 */
char* AttachPanelInfoGetError(int nRet)
{
    char *szErrorVal = NULL;

    switch ( nRet )
    {
    case ATTACH_PANEL_ERROR_NONE:							szErrorVal = "ATTACH_PANEL_ERROR_NONE";							break;
    case ATTACH_PANEL_ERROR_INVALID_PARAMETER:				szErrorVal = "ATTACH_PANEL_ERROR_INVALID_PARAMETER";			break;
    case ATTACH_PANEL_ERROR_OUT_OF_MEMORY:					szErrorVal = "ATTACH_PANEL_ERROR_OUT_OF_MEMORY";				break;
    case ATTACH_PANEL_ERROR_PERMISSION_DENIED:				szErrorVal = "ATTACH_PANEL_ERROR_PERMISSION_DENIED";			break;
    case ATTACH_PANEL_ERROR_ALREADY_EXISTS:					szErrorVal = "ATTACH_PANEL_ERROR_ALREADY_EXISTS";				break;
    case ATTACH_PANEL_ERROR_NOT_INITIALIZED:				szErrorVal = "ATTACH_PANEL_ERROR_NOT_INITIALIZED";				break;
    case ATTACH_PANEL_ERROR_UNSUPPORTED_CONTENT_CATEGORY:	szErrorVal = "ATTACH_PANEL_ERROR_UNSUPPORTED_CONTENT_CATEGORY";	break;
    case ATTACH_PANEL_ERROR_ALREADY_DESTROYED:				szErrorVal = "ATTACH_PANEL_ERROR_ALREADY_DESTROYED";			break;
    default:												szErrorVal = "Unknown Error";									break;
    }

    return szErrorVal;
}


/**
 * @function         CTs_platform_permission_Attach_Panel_startup
 * @description      Called before each test
 * @parameter        NA
 * @return           NA
 */
void CTs_platform_permission_Attach_Panel_startup(void)
{
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}
	s_info.win = elm_win_add(NULL, "Attach Panel Sample", ELM_WIN_BASIC);
	if (!s_info.win) {
		printf("[attach panel] fail to create window");
	}
	evas_object_show(s_info.win);

	s_info.conformant = elm_conformant_add(s_info.win);
	if (!s_info.conformant) {
		printf("[attach panel] fail to create window");
	}

	evas_object_size_hint_weight_set(s_info.conformant,  EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(s_info.win, s_info.conformant);
	evas_object_show(s_info.conformant);
	s_info.is_asserted = 0;


#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_Attach_Panel_startup\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
 * @function         CTs_platform_permission_Attach_Panel_cleanup
 * @description      Called after each test
 * @parameter        NA
 * @return           NA
 */
void CTs_platform_permission_Attach_Panel_cleanup(void)
{
	evas_object_del(s_info.conformant);
	s_info.conformant = NULL;
	evas_object_del(s_info.win);
	s_info.win = NULL;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_Attach_Panel_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose:Checking "%http://tizen.org/privilege/camera", "%http://tizen.org/privilege/recorder", "%http://tizen.org/privilege/appmanger.launch"
//& type: auto
/**
 * @testcase			CTc_Attach_Panel_Privileges_Add_Content_Category
 * @since_tizen			2.4
 * @author				SRID(shekhar1.s)
 * @reviewer			SRID(shobhit.v)
 * @type 				auto
 * @scenario			Adds a content category in the attach panel.
 * @apicovered			attach_panel_add_content_category
 * @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
 * @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
 * @precondition		NA
 * @postcondition		NA
 */
int CTc_Attach_Panel_Privileges_Add_Content_Category(void)
{
	START_TEST;
	int nRet = -1;
	attach_panel_h attach_panel;

	g_bAttachPanelFeatureSupported = TCTCheckSystemInfoFeatureSupported(ATTACH_PANEL_FEATURE1, API_NAMESPACE);
	if ( false == g_bAttachPanelFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, ATTACH_PANEL_FEATURE1);
		return 0;
	}
	g_bAttachPanelFeatureSupported = TCTCheckSystemInfoFeatureSupported(ATTACH_PANEL_FEATURE2, API_NAMESPACE);
	if ( false == g_bAttachPanelFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, ATTACH_PANEL_FEATURE2);
		return 0;
	}
	
	nRet = attach_panel_create(s_info.conformant, &attach_panel);
	PRINT_RESULT(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_create", AttachPanelInfoGetError(nRet));

	nRet = attach_panel_add_content_category(attach_panel, ATTACH_PANEL_CONTENT_CATEGORY_IMAGE, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "attach_panel_add_content_category", AttachPanelInfoGetError(nRet));

	nRet = attach_panel_destroy(attach_panel);
	PRINT_RESULT(ATTACH_PANEL_ERROR_NONE, nRet, "attach_panel_add_content_category", AttachPanelInfoGetError(nRet));

	return 0;
	}
