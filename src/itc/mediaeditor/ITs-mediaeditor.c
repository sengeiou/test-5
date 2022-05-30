//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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
#include "ITs-mediaeditor-common.h"
#include <Elementary.h>

static Evas_Object *g_win = NULL;
static Evas_Object *g_eo = NULL;
static mediaeditor_state_e g_TargetState = MEDIAEDITOR_STATE_IDLE;
static char* g_ProjectNewFilename = "project_new.xges";
static char* g_ProjectNewPath = NULL;
static char* g_ProjectLoadFilename = "project_load.xges";
static char* g_ProjectLoadPath = NULL;
char* g_pszVideoClipPath = NULL;
char* g_RenderFilename = "output.mp4";
char* g_pszRenderPath = NULL;

static void winDeleteCB(void *data, Evas_Object *obj, void *event)
{
	elm_exit();
}

static void createWindow()
{
	int nWidth = 0;
	int nHeight = 0;

	g_win = elm_win_util_standard_add("mediaeditor_itc", "mediaeditor_itc");
	if (g_win)
	{
		elm_win_borderless_set(g_win, EINA_TRUE);
		evas_object_smart_callback_add(g_win, "delete,request", winDeleteCB, NULL);
		elm_win_screen_size_get(g_win, NULL, NULL, &nWidth, &nHeight);
		evas_object_resize(g_win, nWidth, nHeight);
		elm_win_autodel_set(g_win, EINA_TRUE);
	}
	g_eo = evas_object_image_add(evas_object_evas_get(g_win));
}

static void destroyWindow()
{

	if (g_win)
	{
		evas_object_del(g_win);
		g_win = NULL;
	}

	if (g_eo)
	{
		evas_object_del(g_eo);
		g_eo = NULL;
	}
}

//& set: Mediaeditor

//Callbacks


/**
* @function			MediaeditorStateChangedCB
* @parameter			mediaeditor_state_e previous, mediaeditor_state_e current, void *user_data
* @return				NA
*/
static void MediaeditorStateChangedCB(mediaeditor_state_e previous, mediaeditor_state_e current, void *user_data)
{
    FPRINTF("[Line : %d][%s] MediaeditorStateChangedCB callback invoked. previous state[%d], current state[%d]\\n", __LINE__, API_NAMESPACE,previous,current);
    g_bMediaEditorCallback = true;
    if (g_TargetState == current)
	{
		if (g_pMainLoop)
		{
			g_main_loop_quit(g_pMainLoop);
			g_pMainLoop = NULL;
		}
    }
}

/**
* @function			MediaeditorLayerPriorityChangedCB
* @parameter			mediaeditor_layer_info_s *layer_infos, unsigned int size, void *user_data
* @return				NA
*/
static void MediaeditorLayerPriorityChangedCB(mediaeditor_layer_info_s *layer_infos, unsigned int size, void *user_data)
{
	FPRINTF("[Line : %d][%s] MediaeditorLayerPriorityChangedCB callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bMediaEditorCallback = true;
	if (layer_infos == NULL)
	{
		FPRINTF("[Line : %d][%s] layer_infos is null\\n", __LINE__, API_NAMESPACE);
        return;
	}

	for (unsigned int i = 0 ; i < size ; i++)
	{
		FPRINTF("[Line : %d][%s] layer id[%d], layer priority[%d]\\n", __LINE__, API_NAMESPACE,layer_infos[i].id, layer_infos[i].priority);
	}
	if (g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function			MediaeditorProjectLoadedCB
* @parameter			void *user_data
* @return				NA
*/
static void MediaeditorProjectLoadedCB(void *user_data)
{
	FPRINTF("[Line : %d][%s] MediaeditorProjectLoadedCB callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bMediaEditorCallback = true;

	if (g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}


/**
* @function			MediaeditorErrorCB
* @parameter			mediaeditor_error_e error, mediaeditor_state_e state, void *user_data
* @return				NA
*/
static void MediaeditorErrorCB(mediaeditor_error_e error, mediaeditor_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] MediaeditorErrorCB callback invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function			MediaeditorRenderCompletedCB
* @parameter			void *user_data
* @return				NA
*/
static void MediaeditorRenderCompletedCB(void *user_data)
{
    FPRINTF("[Line : %d][%s] MediaeditorRenderCompletedCB callback invoked\\n", __LINE__, API_NAMESPACE);
    g_bMediaEditorCallback = true;
	if (g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
		g_pMainLoop = NULL;
	}
	 return;
}

/** @addtogroup itc-mediaeditor
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_mediaeditor_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediaeditor_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_mediaeditor_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bMediaEditorHandleCreated = false;

	char pszValue[CONFIG_VALUE_LEN_MAX] = { 0, };
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE, pszValue);
		unsigned int path_size = strlen(pszValue) + strlen("/res/video.mp4") + 1;

		g_pszVideoClipPath = (char*)calloc(path_size, sizeof(char));
		if (g_pszVideoClipPath == NULL)
		{
			FPRINTF("[Line : %d][%s] Memory Allocation Failed for g_pszVideoClipPath \\n", __LINE__, API_NAMESPACE);
			return;
		}
		snprintf(g_pszVideoClipPath, path_size, "%s/res/video.mp4", pszValue);

		path_size = strlen(pszValue) + strlen(g_RenderFilename) + 1;
		g_pszRenderPath = (char*)calloc(path_size, sizeof(char));
        snprintf(g_pszRenderPath, path_size, "%s/res/%s", pszValue, g_RenderFilename);

        path_size = strlen(pszValue) + strlen(g_ProjectNewFilename) + 1;
        g_ProjectNewPath = (char*)malloc(path_size);
        snprintf(g_ProjectNewPath, path_size, "%s/res/%s", pszValue, g_ProjectNewFilename);

        path_size = strlen(pszValue) + strlen(g_ProjectLoadFilename) + 11;
        g_ProjectLoadPath = (char*)malloc(path_size);
        snprintf(g_ProjectLoadPath, path_size, "%s/res/%s", pszValue, g_ProjectLoadFilename);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	int nRet = mediaeditor_create(&g_hMediaEditorHandle);
	if (nRet != MEDIAEDITOR_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] mediaeditor_create failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, MediaEditorGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] mediaeditor_create failed, error returned = (%d)", API_NAMESPACE, __LINE__, nRet);
		g_bMediaEditorHandleCreated = false;
		return;
	}
	if (g_hMediaEditorHandle == NULL)
	{
		g_bMediaEditorHandleCreated = false;
		return;
	}
	g_bMediaEditorHandleCreated = true;
}


/**
 * @function 		ITs_mediaeditor_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_mediaeditor_cleanup(void)
{
	if (g_pszVideoClipPath)
	{
		free(g_pszVideoClipPath);
		g_pszVideoClipPath = NULL;
	}
	if (g_pszRenderPath)
	{
		free(g_pszRenderPath);
		g_pszRenderPath = NULL;
	}
	if (g_ProjectNewPath)
	{
		free(g_ProjectNewPath);
		g_ProjectNewPath = NULL;
	}
	if (g_ProjectLoadPath)
	{
		free(g_ProjectLoadPath);
		g_ProjectLoadPath = NULL;
	}
	if (g_hMediaEditorHandle)
	{
		int nRet = mediaeditor_destroy(g_hMediaEditorHandle);
		if (nRet != MEDIAEDITOR_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] mediaediotor_destroy api failed.\\n", __LINE__, API_NAMESPACE);
		}
	}

	return;
}


//& purpose: Creates and Destroy an instance of MediaEditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_create_destroy_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy an instance of MediaEditor
* @scenario				Creates and Destroy an instance of MediaEditor
* @apicovered			mediaeditor_create, mediaeditor_create
* @passcase				If mediaeditor_create, mediaeditor_create is successful
* @failcase 			If mediaeditor_create Or mediaeditor_create fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_create_destroy_p(void)
{
	START_TEST;

	int nRet = mediaeditor_destroy(g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_destroy", MediaEditorGetError(nRet));

	nRet = mediaeditor_create(&g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_create", MediaEditorGetError(nRet));
	CHECK_HANDLE(g_hMediaEditorHandle, "mediaeditor_create");

	nRet = mediaeditor_destroy(g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_destroy", MediaEditorGetError(nRet));

	nRet = mediaeditor_create(&g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_create", MediaEditorGetError(nRet));
	CHECK_HANDLE(g_hMediaEditorHandle, "mediaeditor_create");

	return 0;
}

//& purpose: Set display of an instance of Mediaeditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_display_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set display for media
* @scenario				Set display for media
* @apicovered			mediaeditor_set_display
* @passcase				If mediaeditor_set_display is successful
* @failcase 			If mediaeditor_set_display fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_display_p(void)
{
	START_TEST;

	createWindow();

	mediaeditor_display_type_e eDisplayType[] =
	{
		//MEDIAEDITOR_DISPLAY_TYPE_OVERLAY, /**< Overlay surface display */
		MEDIAEDITOR_DISPLAY_TYPE_EVAS,    /**< Evas object surface display */
		//MEDIAEDITOR_DISPLAY_TYPE_ECORE,   /**< Ecore object surface display */
		//MEDIAEDITOR_DISPLAY_TYPE_NONE     /**< This disposes off buffers */
	};

	int nEnumSize = sizeof(eDisplayType) / sizeof(eDisplayType[0]);
	int nEnumCounter = 0;

	//feature check
	bool bIsDisplayFeatureSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_NAME_DISPLAY, API_NAMESPACE);

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Target API
		FPRINTF("[Line : %d][%s] For display type = [%d] \\n", __LINE__, API_NAMESPACE, eDisplayType[nEnumCounter]);
		int nRet = mediaeditor_set_display(g_hMediaEditorHandle, eDisplayType[nEnumCounter], GET_DISPLAY(g_eo));

		if (!bIsDisplayFeatureSupported)
		{
			PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NOT_SUPPORTED, nRet, "mediaeditor_set_display", MediaEditorGetError(nRet), destroyWindow());
		}
		else
		{
			PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_display", MediaEditorGetError(nRet), destroyWindow());
		}
	}
	destroyWindow();
	return 0;
}


//& purpose: Get State of an instance of Mediaeditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_get_state_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get instance
* @scenario				Get instance
* @apicovered			mediaeditor_get_state
* @passcase				If mediaeditor_get_state is successful
* @failcase 			If mediaeditor_get_state fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_get_state_p(void)
{
	START_TEST;
	mediaeditor_state_e eGetState = MEDIAEDITOR_STATE_IDLE;

	int nRet = mediaeditor_get_state(g_hMediaEditorHandle, &eGetState);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_state", MediaEditorGetError(nRet));
	if (eGetState != MEDIAEDITOR_STATE_IDLE)
	{
		FPRINTF("[Line : %d][%s] eGetState is not idle\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& purpose: Add and remove a layer of instance of Mediaeditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_add_remove_layer_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Add and remove a layer
* @scenario				Add and remove a layer
* @apicovered			mediaeditor_add_layer and mediaeditor_remove_layer
* @passcase				If mediaeditor_add_layer, mediaeditor_add_layer is successful
* @failcase 			If mediaeditor_add_layer Or mediaeditor_add_layer fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_add_remove_layer_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_remove_layer(g_hMediaEditorHandle, nLayerId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_remove_layer", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Move a layer of instance of Mediaeditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_move_layer_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Move a layer's priority
* @scenario				Move a layer's priority
* @apicovered			mediaeditor_add_layer and mediaeditor_move_layer
* @passcase				If mediaeditor_add_layer and mediaeditor_move_layer is successful
* @failcase 			If mediaeditor_add_layer Or mediaeditor_move_layer fails
* @precondition			NA
* @postcondition		NA
*/
int  ITc_mediaeditor_move_layer_p(void)
{
	START_TEST;
	unsigned int nLayerId1 = 0;
	unsigned int nLayerId2 = 0;
	unsigned int nLayerPriority1 = 0;
	unsigned int nLayerPriority2 = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId1, &nLayerPriority1);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId2, &nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_move_layer(g_hMediaEditorHandle, nLayerId1, nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_move_layer", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Activate and Deactivate an instance of mediaeditor
//& type: auto
/**
* @testcase 			ITc_mediaeditor_activate_deactivate_layer_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Activate and Deactivate layer
* @scenario				Activate and Deactivate layer
* @apicovered			mediaeditor_add_layer, mediaeditor_activate_layer and mediaeditor_deactivate_layer
* @passcase				If all pre condition APIs and mediaeditor_deactivate_layer is successful
* @failcase 			If all pre condition APIs Or mediaeditor_deactivate_layer is successful
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_activate_deactivate_layer_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_activate_layer(g_hMediaEditorHandle, nLayerId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_activate_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_deactivate_layer(g_hMediaEditorHandle, nLayerId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_deactivate_layer", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Get Layer Priority
//& type: auto
/**
* @testcase 			ITc_mediaeditor_get_layer_priority_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Get Layer Priority
* @scenario				Add layer and Get Layer Priority
* @apicovered			mediaeditor_add_layer and mediaeditor_get_layer_priority
* @passcase				If mediaeditor_add_layer and mediaeditor_get_layer_priority is successful
* @failcase 			If mediaeditor_add_layer Or mediaeditor_get_layer_priority fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_get_layer_priority_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_layer_priority(g_hMediaEditorHandle, nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_layer_priority", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Gets the lowest priority of all layers
//& type: auto
/**
* @testcase 			ITc_mediaeditor_get_layer_lowest_priority_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the lowest priority of all layers
* @scenario				Add layers and Gets the lowest priority of all layers
* @apicovered			mediaeditor_add_layer, mediaeditor_get_layer_lowest_priority
* @passcase				If mediaeditor_add_layer, mediaeditor_get_layer_lowest_priority is successful
* @failcase 			If mediaeditor_add_layer Or mediaeditor_get_layer_lowest_priority fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_get_layer_lowest_priority_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nLayerLowestPriority = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_layer_lowest_priority(g_hMediaEditorHandle, &nLayerLowestPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_layer_lowest_priority", MediaEditorGetError(nRet));

	if (nLayerLowestPriority != 0)
	{
		FPRINTF("[Line : %d][%s] lowest priority value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_layer_lowest_priority(g_hMediaEditorHandle, &nLayerLowestPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_layer_lowest_priority", MediaEditorGetError(nRet));

	if (nLayerLowestPriority != 1)
	{
		FPRINTF("[Line : %d][%s] lowest priority value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Gets the layer ID of layer
//& type: auto
/**
* @testcase 			ITc_mediaeditor_get_layer_id_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the layer ID of layer
* @scenario				Add layer and Gets the layer ID of layer
* @apicovered			mediaeditor_add_layer and mediaeditor_get_layer_id
* @passcase				If mediaeditor_add_layer and mediaeditor_get_layer_id is successful
* @failcase 			If mediaeditor_add_layer Or mediaeditor_get_layer_id fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_get_layer_id_p(void)
{
	START_TEST;
	unsigned int nLayerId1 = 0;
	unsigned int nLayerId2 = 0;
	unsigned int nGetLayerId = 0;
	unsigned int nLayerPriority1 = 0;
	unsigned int nLayerPriority2 = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId1, &nLayerPriority1);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId2, &nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_layer_id(g_hMediaEditorHandle, nLayerPriority2, &nGetLayerId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_layer_id", MediaEditorGetError(nRet));

	if (nGetLayerId != nLayerId2)
	{
		FPRINTF("[Line : %d][%s] layer Id value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = mediaeditor_get_layer_id(g_hMediaEditorHandle, nLayerPriority1, &nGetLayerId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_layer_id", MediaEditorGetError(nRet));

	if (nGetLayerId != nLayerId1)
	{
		FPRINTF("[Line : %d][%s] layer Id value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Add and remove a clip on timeline
//& type: auto
/**
* @testcase 			ITc_mediaeditor_add_remove_clip_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Add layer and Add and remove a clip on timeline
* @scenario				Add layer and Add and remove a clip on timeline
* @apicovered			mediaeditor_add_layer, mediaeditor_add_clip and mediaeditor_remove_clip
* @passcase				If mediaeditor_add_layer, mediaeditor_add_clip and mediaeditor_remove_clip is successful
* @failcase 			If mediaeditor_add_layer, mediaeditor_add_clip Or mediaeditor_remove_clip fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_add_remove_clip_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_remove_clip(g_hMediaEditorHandle, nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_remove_clip", MediaEditorGetError(nRet));
	return 0;
}

//& purpose: Split the clip
//& type: auto
/**
* @testcase 			ITc_mediaeditor_split_clip_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Split the clip
* @scenario				add layer and clip, then Split the clip
* @apicovered			mediaeditor_add_layer, mediaeditor_add_clip and mediaeditor_split_clip
* @passcase				If mediaeditor_add_layer, mediaeditor_add_clip and mediaeditor_split_clip is successful
* @failcase 			If mediaeditor_add_layer, mediaeditor_add_clip Or mediaeditor_split_clip fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_split_clip_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nSplitClipId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_split_clip(g_hMediaEditorHandle, nClipId, nDuration / 2, &nSplitClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_split_clip", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Group and ungroup a clip
//& type: auto
/**
* @testcase 			ITc_mediaeditor_group_ungroup_clip_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Group and ungroup a clip
* @scenario				Group and ungroup a clip
* @apicovered			mediaeditor_group_clip and mediaeditor_ungroup_clip
* @passcase				If mediaeditor_group_clip and mediaeditor_ungroup_clip is successful
* @failcase 			If mediaeditor_group_clip Or mediaeditor_ungroup_clip fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_group_ungroup_clip_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipIds[2] = { 0 };
	unsigned int *nUngroupedClipIds;
	unsigned int nUngroupedClipSize = 0;
	unsigned int nGroupId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipIds[0]);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart+nDuration, nDuration, nInPoint, &nClipIds[1]);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_group_clip(g_hMediaEditorHandle, nClipIds, 2, &nGroupId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_group_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_ungroup_clip(g_hMediaEditorHandle, nGroupId, &nUngroupedClipIds, &nUngroupedClipSize);
 	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_ungroup_clip", MediaEditorGetError(nRet));

	if (nUngroupedClipSize != 2)
	{
		FPRINTF("[Line : %d][%s] Clip Size value mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
//& purpose: Move Clip Layer
//& type: auto
/**
* @testcase 			ITc_mediaeditor_move_clip_layer_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Move Clip Layer
* @scenario				Move Clip Layer
* @apicovered		   mediaeditor_move_clip_layer
* @passcase				If pre condition and mediaeditor_move_clip_layer is successful
* @failcase 			If pre condition Or mediaeditor_move_clip_layer fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_move_clip_layer_p(void)
{
	START_TEST;
	unsigned int nLayerId1 = 0;
	unsigned int nLayerId2 = 0;
	unsigned int nLayerPriority1 = 0;
	unsigned int nLayerPriority2 = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId1, &nLayerPriority1);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId2, &nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId1, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_move_clip_layer(g_hMediaEditorHandle, nClipId, nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_move_clip", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Set and Get Clip from start
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_get_clip_start_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and Get Clip from start
* @scenario				Set and Get Clip from start
* @apicovered			mediaeditor_set_clip_start, mediaeditor_get_clip_start
* @passcase				If mediaeditor_set_clip_start and mediaeditor_get_clip_start is successful
* @failcase 			If mediaeditor_set_clip_start Or mediaeditor_get_clip_start is successful fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_get_clip_start_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 10;
	unsigned int nSetStart = 0;
	unsigned int nGetStart = 0;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_clip_start(g_hMediaEditorHandle, nClipId, nSetStart);
	if (nRet == MEDIAEDITOR_ERROR_NOT_SUPPORTED)
	{
		dlog_print(DLOG_DEBUG, "NativeTCT", "[%s(%d)] setting clip start feature is not supported, skip it", __FUNCTION__, __LINE__);
		return 0;
	}
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_clip_start", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_clip_start(g_hMediaEditorHandle, nClipId, &nGetStart);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_clip_start", MediaEditorGetError(nRet));
	if (nSetStart != nGetStart)
	{
		FPRINTF("[Line : %d][%s] start value of clip mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set and get clip duration
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_get_clip_duration_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and get clip duration
* @scenario				Set and get clip duration
* @apicovered			mediaeditor_set_clip_duration and mediaeditor_get_clip_duration
* @passcase				If mediaeditor_set_clip_duration and mediaeditor_get_clip_duration is pass
* @failcase 			If mediaeditor_set_clip_duration Or mediaeditor_get_clip_duration fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_get_clip_duration_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 10;
	unsigned int nDuration = 100;
	unsigned int nSetDuration = 200;
	unsigned int nGetDuration = 0;
	unsigned int nInPoint = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_clip_duration(g_hMediaEditorHandle, nClipId, nSetDuration);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_clip_duration", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_clip_duration(g_hMediaEditorHandle, nClipId, &nGetDuration);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_clip_duration", MediaEditorGetError(nRet));
	if (nSetDuration != nGetDuration)
	{
		FPRINTF("[Line : %d][%s] duration value of clip mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set and get clip in point
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_get_clip_in_point_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and get clip in point
* @scenario				Set and get clip in point
* @apicovered			mediaeditor_set_clip_in_point and mediaeditor_get_clip_in_point
* @passcase				If mediaeditor_set_clip_in_point and mediaeditor_get_clip_in_point is successful
* @failcase 			If mediaeditor_set_clip_in_point Or mediaeditor_get_clip_in_point fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_get_clip_in_point_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 10;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 100;
	unsigned int nGetInPoint = 10;
	unsigned int nSetInPoint = 200;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_clip_in_point(g_hMediaEditorHandle, nClipId, nSetInPoint);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_clip_in_point", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_clip_in_point(g_hMediaEditorHandle, nClipId, &nGetInPoint);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_clip_in_point", MediaEditorGetError(nRet));
	if (nSetInPoint != nGetInPoint)
	{
		FPRINTF("[Line : %d][%s] in point value of clip mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set and get clip resolution
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_get_clip_resolution_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and get clip resolution
* @scenario				Set and get clip resolution
* @apicovered			mediaeditor_set_clip_resolution and mediaeditor_set_clip_resolution
* @passcase				If mediaeditor_set_clip_resolution and mediaeditor_set_clip_resolution is successful
* @failcase 			If mediaeditor_set_clip_resolution Or mediaeditor_set_clip_resolution fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_get_clip_resolution_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 10;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 100;
	unsigned int nSetWidth = 320;
	unsigned int nSetHeight = 160;
	unsigned int nGetWidth = 0;
	unsigned int nGetHeight = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_clip_resolution(g_hMediaEditorHandle, nClipId, nSetWidth, nSetHeight);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_clip_resolution", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_clip_resolution(g_hMediaEditorHandle, nClipId, &nGetWidth, &nGetHeight);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_clip_resolution", MediaEditorGetError(nRet));
	if ((nSetWidth != nGetWidth) || (nSetHeight != nGetHeight))
	{
		FPRINTF("[Line : %d][%s] resolution value of clip mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Set and Get clip volume
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_get_clip_volume_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and Get clip volume
* @scenario				Set and Get clip volume
* @apicovered			mediaeditor_set_clip_volume and mediaeditor_get_clip_volume
* @passcase				If mediaeditor_set_clip_volume and mediaeditor_get_clip_volume is successful
* @failcase 			If mediaeditor_set_clip_volume Or mediaeditor_get_clip_volume fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_get_clip_volume_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 10;
	unsigned int nDuration = 100;
	unsigned int nInPoint = 100;
	double nSetVolume = 0.5;
	double nGetVolume = 0.0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_clip_volume(g_hMediaEditorHandle, nClipId, nSetVolume);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_clip_volume", MediaEditorGetError(nRet));

	nRet = mediaeditor_get_clip_volume(g_hMediaEditorHandle, nClipId, &nGetVolume);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_get_clip_volume", MediaEditorGetError(nRet));
	if (nSetVolume != nGetVolume)
	{
		FPRINTF("[Line : %d][%s] resolution value of clip mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: Add transition
//& type: auto
/**
* @testcase 			ITc_mediaeditor_add_transition_p
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Add transition
* @scenario				Add transition
* @apicovered			mediaeditor_add_transition
* @passcase				If mediaeditor_add_transition is successful
* @failcase 			If mediaeditor_add_transition fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_add_transition_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 200;
	unsigned int nInPoint = 0;
	unsigned int nTransitionStart = 0;
	unsigned int nTransitionDuration = 0;

	mediaeditor_transition_type_e eTransitionType[] =
	{
		MEDIAEDITOR_TRANSITION_TYPE_NONE,               /**< Transition none */
		MEDIAEDITOR_TRANSITION_TYPE_BAR_WIPE_LR,        /**< A bar moves from left to right */
		MEDIAEDITOR_TRANSITION_TYPE_BAR_WIPE_TB,        /**< A bar moves from top to bottom */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_TL,        /**< A box expands from the upper-left corner to the lower-right corner */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_TR,        /**< A box expands from the upper-right corner to the lower-left corner */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_BR,        /**< A box expands from the lower-right corner to the upper-left corner */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_BL,        /**< A box expands from the lower-left corner to the upper-right corner */
		MEDIAEDITOR_TRANSITION_TYPE_FOUR_BOX_WIPE_CI,   /**< A box shape expands from each of the four corners toward the center */
		MEDIAEDITOR_TRANSITION_TYPE_FOUR_BOX_WIPE_CO,   /**< A box shape expands from the center of each quadrant toward the corners of each quadrant */
		MEDIAEDITOR_TRANSITION_TYPE_BARNDOOR_V,        /**< A central, vertical line splits and expands toward the left and right edges */
		MEDIAEDITOR_TRANSITION_TYPE_BARNDOOR_H,        /**< A central, horizontal line splits and expands toward the top and bottom edges */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_TC,       /**< A box expands from the top edge's midpoint to the bottom corners */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_RC,       /**< A box expands from the right edge's midpoint to the left corners */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_BC,       /**< A box expands from the bottom edge's midpoint to the top corners */
		MEDIAEDITOR_TRANSITION_TYPE_BOX_WIPE_LC,       /**< A box expands from the left edge's midpoint to the right corners */
		MEDIAEDITOR_TRANSITION_TYPE_DIAGONAL_TL,       /**< A diagonal line moves from the upper-left corner to the lower-right corner */
		MEDIAEDITOR_TRANSITION_TYPE_DIAGONAL_TR,       /**< A diagonal line moves from the upper right corner to the lower-left corner */
		MEDIAEDITOR_TRANSITION_TYPE_BOWTIE_V,          /**< Two wedge shapes slide in from the top and bottom edges toward the center */
		MEDIAEDITOR_TRANSITION_TYPE_BOWTIE_H,          /**< Two wedge shapes slide in from the left and right edges toward the center */
		MEDIAEDITOR_TRANSITION_TYPE_BARNDOOR_DBL,      /**< A diagonal line from the lower-left to upper-right corners splits and expands toward the opposite corners */
		MEDIAEDITOR_TRANSITION_TYPE_BARNDOOR_DTL,      /**< A diagonal line from upper-left to lower-right corners splits and expands toward the opposite corners */
		MEDIAEDITOR_TRANSITION_TYPE_MISC_DIAGONAL_DBD, /**< Four wedge shapes split from the center and retract toward the four edges */
		MEDIAEDITOR_TRANSITION_TYPE_MISC_DIAGONAL_DD,  /**< A diamond connecting the four edge midpoints simultaneously contracts toward the center and expands toward the edges */
		MEDIAEDITOR_TRANSITION_TYPE_VEE_D,             /**< A wedge shape moves from top to bottom */
		MEDIAEDITOR_TRANSITION_TYPE_VEE_L,             /**< A wedge shape moves from right to left */
		MEDIAEDITOR_TRANSITION_TYPE_VEE_U,             /**< A wedge shape moves from bottom to top */
		MEDIAEDITOR_TRANSITION_TYPE_VEE_R,             /**< A wedge shape moves from left to right */
		MEDIAEDITOR_TRANSITION_TYPE_BARNVEE_D,         /**< A 'V' shape extending from the bottom edge's midpoint to the opposite corners contracts toward the center and expands toward the edges */
		MEDIAEDITOR_TRANSITION_TYPE_BARNVEE_L,         /**< A 'V' shape extending from the left edge's midpoint to the opposite corners contracts toward the center and expands toward the edges */
		MEDIAEDITOR_TRANSITION_TYPE_BARNVEE_U,         /**< A 'V' shape extending from the top edge's midpoint to the opposite corners contracts toward the center and expands toward the edges */
		MEDIAEDITOR_TRANSITION_TYPE_BARNVEE_R,         /**< A 'V' shape extending from the right edge's midpoint to the opposite corners contracts toward the center and expands toward the edges */
		MEDIAEDITOR_TRANSITION_TYPE_IRIS_RECT,        /**< A rectangle expands from the center. */
		MEDIAEDITOR_TRANSITION_TYPE_CLOCK_CW12,       /**< A radial hand sweeps clockwise from the twelve o'clock position */
		MEDIAEDITOR_TRANSITION_TYPE_CLOCK_CW3,        /**< A radial hand sweeps clockwise from the three o'clock position */
		MEDIAEDITOR_TRANSITION_TYPE_CLOCK_CW6,        /**< A radial hand sweeps clockwise from the six o'clock position */
		MEDIAEDITOR_TRANSITION_TYPE_CLOCK_CW9,        /**< A radial hand sweeps clockwise from the nine o'clock position */
		MEDIAEDITOR_TRANSITION_TYPE_PINWHEEL_TBV,     /**< Two radial hands sweep clockwise from the twelve and six o'clock positions */
		MEDIAEDITOR_TRANSITION_TYPE_PINWHEEL_TBH,     /**< Two radial hands sweep clockwise from the nine and three o'clock positions */
		MEDIAEDITOR_TRANSITION_TYPE_PINWHEEL_FB,      /**< Four radial hands sweep clockwise */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_CT,           /**< A fan unfolds from the top edge, the fan axis at the center */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_CR,           /**< A fan unfolds from the right edge, the fan axis at the center */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLEFAN_FOV,    /**< Two fans, their axes at the center, unfold from the top and bottom */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLEFAN_FOH,    /**< Two fans, their axes at the center, unfold from the left and right */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWT,  /**< A radial hand sweeps clockwise from the top edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWR,  /**< A radial hand sweeps clockwise from the right edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWB,  /**< A radial hand sweeps clockwise from the bottom edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWL,  /**< A radial hand sweeps clockwise from the left edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_PV,   /**< Two radial hands sweep clockwise and counter-clockwise from the top and bottom edges' midpoints */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_PD,   /**< Two radial hands sweep clockwise and counter-clockwise from the left and right edges' midpoints */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_OV,   /**< Two radial hands attached at the top and bottom edges' midpoints sweep from right to left */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_OH,   /**< Two radial hands attached at the left and right edges' midpoints sweep from top to bottom */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_T,            /**< A fan unfolds from the bottom, the fan axis at the top edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_R,            /**< A fan unfolds from the left, the fan axis at the right edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_B,            /**< A fan unfolds from the top, the fan axis at the bottom edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_FAN_L,            /**< A fan unfolds from the right, the fan axis at the left edge's midpoint */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLEFAN_FIV,    /**< Two fans, their axes at the top and bottom, unfold from the center */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLEFAN_FIH,    /**< Two fans, their axes at the left and right, unfold from the center */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWTL, /**< A radial hand sweeps clockwise from the upper-left corner */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CCWBL, /**< A radial hand sweeps counter-clockwise from the lower-left corner */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CWBR, /**< A radial hand sweeps clockwise from the lower-right corner */
		MEDIAEDITOR_TRANSITION_TYPE_SINGLESWEEP_CCWTR, /**< A radial hand sweeps counter-clockwise from the upper-right corner */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_PDTL, /**< Two radial hands attached at the upper-left and lower-right corners sweep down and up */
		MEDIAEDITOR_TRANSITION_TYPE_DOUBLESWEEP_PDBL, /**< Two radial hands attached at the lower-left and upper-right corners sweep down and up */
		MEDIAEDITOR_TRANSITION_TYPE_SALOONDOOR_T,     /**< Two radial hands attached at the upper-left and upper-right corners sweep down */
		MEDIAEDITOR_TRANSITION_TYPE_SALOONDOOR_L,     /**< Two radial hands attached at the upper-left and lower-left corners sweep to the right */
		MEDIAEDITOR_TRANSITION_TYPE_SALOONDOOR_B,     /**< Two radial hands attached at the lower-left and lower-right corners sweep up */
		MEDIAEDITOR_TRANSITION_TYPE_SALOONDOOR_R,     /**< Two radial hands attached at the upper-right and lower-right corners sweep to the left */
		MEDIAEDITOR_TRANSITION_TYPE_WINDSHIELD_R,     /**< Two radial hands attached at the midpoints of the top and bottom halves sweep from right to left */
		MEDIAEDITOR_TRANSITION_TYPE_WINDSHIELD_U,     /**< Two radial hands attached at the midpoints of the left and right halves sweep from top to bottom */
		MEDIAEDITOR_TRANSITION_TYPE_WINDSHIELD_V,     /**< Two sets of radial hands attached at the midpoints of the top and bottom halves sweep from top to bottom and bottom to top */
		MEDIAEDITOR_TRANSITION_TYPE_WINDSHIELD_H,     /**< Two sets of radial hands attached at the midpoints of the left and right halves sweep from left to right and right to left */
		MEDIAEDITOR_TRANSITION_TYPE_CROSSFADE         /**< Crossfade */
	};

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart + (nDuration/2), nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	nTransitionStart = nStart + (nDuration / 2);
	nTransitionDuration = nDuration / 2;

	/*enum*/
	int nEnumSize = sizeof(eTransitionType) / sizeof(eTransitionType[0]);
	int nEnumCounter;

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Target API
		FPRINTF("[Line : %d][%s] For transition type = [%d] \\n", __LINE__, API_NAMESPACE, eTransitionType[nEnumCounter]);
		nRet = mediaeditor_add_transition(g_hMediaEditorHandle, eTransitionType[nEnumCounter], nLayerId, nTransitionStart, nTransitionDuration);
		PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_transition", MediaEditorGetError(nRet));
	}
	return 0;
}

//& purpose: Add and Remove effect on different enums
//& type: auto
/**
* @testcase 			ITc_add_remove_effect_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and Destroy an instance of MediaEditor
* @scenario				Creates and Destroy an instance of MediaEditor
* @apicovered			mediaeditor_create,webrtc_destroy
* @passcase				If webrtc_create,webrtc_destroy is successful
* @failcase 			If webrtc_create,webrtc_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_add_remove_effect_p(void)
{
	START_TEST;
	unsigned int nLayerId = 0;
	unsigned int nLayerPriority = 0;
	unsigned int nClipId = 0;
	unsigned int nEffectId = 0;
	unsigned int nStart = 0;
	unsigned int nDuration = 200;
	unsigned int nInPoint = 0;

	mediaeditor_effect_type_e eEffectType[] =
	{
		//MEDIAEDITOR_EFFECT_TYPE_NONE,               /**< None */		-- returning error
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_EDGETV,       /**< Applies edge detect on video */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_AGINGTV,      /**< Adds age to video input using scratches and dust */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_DICETV,       /**< Dices the screen up into many small squares */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_WARPTV,       /**< Realtime goo'ing of the video input */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_SHAGADELICTV, /**< Makes images shagadelic */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_VERTIGOTV,    /**< A loopback alpha blending effector with rotating and scaling */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_REVTV,        /**< A video waveform monitor for each line of video processed */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_QUARKTV,      /**< Motion dissolver */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_OPTV,         /**< Optical art meets real-time video effect */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_RADIOACTV,    /**< Motion-enlightment effect */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_STREAKTV,     /**< Makes after images of moving objects */
		MEDIAEDITOR_EFFECT_VIDEO_TYPE_RIPPLETV,     /**< Makes ripple mark effect on the video input */
		MEDIAEDITOR_EFFECT_AUDIO_TYPE_FADE_IN,      /**< Audio fade in */
		MEDIAEDITOR_EFFECT_AUDIO_TYPE_FADE_OUT,     /**< Audio fade out */
		MEDIAEDITOR_EFFECT_AUDIO_TYPE_ECHO         /**< Adds an echo or reverb effect to an audio stream */
	};

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId, &nLayerPriority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, nLayerId, nStart, nDuration, nInPoint, &nClipId);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	int nEnumSize = sizeof(eEffectType) / sizeof(eEffectType[0]);
	int nEnumCounter;
	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Target API
		FPRINTF("[Line : %d][%s] For effect type = [%d] \\n", __LINE__, API_NAMESPACE, eEffectType[nEnumCounter]);

		nRet = mediaeditor_add_effect(g_hMediaEditorHandle, eEffectType[nEnumCounter], nLayerId, nStart, nDuration, &nEffectId);
		PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_effect", MediaEditorGetError(nRet));

		nRet = mediaeditor_remove_effect(g_hMediaEditorHandle, nEffectId);
		PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_remove_effect", MediaEditorGetError(nRet));
	}
	return 0;
}

//& purpose: Creates a project to given path and Save current information
//& type: auto
/**
* @testcase 			ITc_mediaeditor_create_save_project_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates a project to given path and save current editing information
* @scenario				Creates a project to given path and save current editing information
* @apicovered			mediaeditor_create_project and mediaeditor_save_project
* @passcase				If mediaeditor_create_project and mediaeditor_save_project pass
* @failcase 			If mediaeditor_create_project Or mediaeditor_save_project fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_create_save_project_p(void)
{
	START_TEST;
	int nRet = mediaeditor_create_project(g_hMediaEditorHandle, g_ProjectNewPath);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_create_project", MediaEditorGetError(nRet));

	nRet = mediaeditor_save_project(g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_save_project", MediaEditorGetError(nRet));

	return 0;
}


//& purpose: Loads a project from a path
//& type: auto
/**
* @testcase 			ITc_mediaeditor_load_project_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Loads a project from a path
* @scenario				Loads a project from a path
* @apicovered			mediaeditor_load_project
* @passcase				If mediaeditor_load_project pass
* @failcase 			If mediaeditor_load_project fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_load_project_p(void)
{
	START_TEST;
	int nTimeoutId = 0;

	g_bMediaEditorCallback = false;
	int nRet = mediaeditor_load_project(g_hMediaEditorHandle, g_ProjectLoadPath, MediaeditorProjectLoadedCB, NULL);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_save_project", MediaEditorGetError(nRet));

	RUN_POLLING_LOOP;

	if ( g_bMediaEditorCallback == false )
	{
		FPRINTF("[Line : %d][%s] mediaeditor_load_project failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& purpose: Start and Stop preview
//& type: auto
/**
* @testcase 			ITc_mediaeditor_start_stop_preview_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Start and Stop preview
* @scenario				Start and Stop preview, Check callback hit for start preview
* @apicovered			mediaeditor_set_state_changed_cb, mediaeditor_add_layer, mediaeditor_add_clip mediaeditor_start_preview and mediaeditor_stop_preview
* @passcase				If all precondition APIs, mediaeditor_start_preview and mediaeditor_stop_preview pass.
* @failcase 			If mediaeditor_start_preview, mediaeditor_stop_preview Or any pre condition API fails
* @precondition			mediaeditor_add_layer and mediaeditor_add_clip
* @postcondition		NA
*/
int ITc_mediaeditor_start_stop_preview_p(void)
{
    START_TEST;
    unsigned int layer_id = 0;
    unsigned int layer_priority = 0;
    unsigned int clip_id = 0;
    unsigned int start = 0;
    unsigned int duration = 5000;
    unsigned int in_point = 0;
    int nTimeoutId = 0;

    int nRet = mediaeditor_set_state_changed_cb(g_hMediaEditorHandle, MediaeditorStateChangedCB, NULL);
    PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_state_changed_cb", MediaEditorGetError(nRet));

    createWindow();
    nRet = mediaeditor_set_display(g_hMediaEditorHandle, MEDIAEDITOR_DISPLAY_TYPE_EVAS, GET_DISPLAY(g_eo));
    PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_display", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));

    nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &layer_id, &layer_priority);
    PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));

    nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, layer_id, start, duration, in_point, &clip_id);
    PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));

    g_TargetState = MEDIAEDITOR_STATE_PREVIEW;
    g_bMediaEditorCallback = false;

	//feature check
	bool bIsDisplayFeatureSupported = TCTCheckSystemInfoFeatureSupported(FEATURE_NAME_DISPLAY, API_NAMESPACE);
	nRet = mediaeditor_start_preview(g_hMediaEditorHandle);
	if (!bIsDisplayFeatureSupported)
	{
		PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NOT_SUPPORTED, nRet, "mediaeditor_start_preview", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));
	}
	else
	{
		PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_start_preview", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));
	}

    /* Wait state transition : IDLE -> PREVIEW */
	RUN_POLLING_LOOP;

	if ( g_bMediaEditorCallback == false )
	{
		FPRINTF("[Line : %d][%s] mediaeditor_start_preview failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle);
		destroyWindow();
		return 1;
	}

	nRet = mediaeditor_stop_preview(g_hMediaEditorHandle);
	if (!bIsDisplayFeatureSupported)
	{
		PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NOT_SUPPORTED, nRet, "mediaeditor_stop_preview", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));
	}
	else
	{
		PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_stop_preview", MediaEditorGetError(nRet), destroyWindow();mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle));
	}

	mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle);
	destroyWindow();

	return 0;
}

//& purpose: Set and Unset state changed callback
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_unset_state_changed_cb_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and Unset state changed callback
* @scenario				Set and Unset state changed callback
* @apicovered			mediaeditor_set_state_changed_cb and mediaeditor_unset_state_changed_cb
* @passcase				If mediaeditor_set_state_changed_cb and mediaeditor_unset_state_changed_cb API pass
* @failcase 			If mediaeditor_set_state_changed_cb or mediaeditor_unset_state_changed_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_unset_state_changed_cb_p(void)
{
    START_TEST;

    int nRet = mediaeditor_set_state_changed_cb(g_hMediaEditorHandle, MediaeditorStateChangedCB, NULL);
    PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_state_changed_cb", MediaEditorGetError(nRet));

    nRet = mediaeditor_unset_state_changed_cb(g_hMediaEditorHandle);
    PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_unset_state_changed_cb", MediaEditorGetError(nRet));

    return 0;
}

//& purpose: Set and Unset error callback
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_unset_error_cb_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Set and Unset error callback
* @scenario				Set and Unset error callback
* @apicovered			mediaeditor_set_error_cb and mediaeditor_unset_error_cb
* @passcase				If mediaeditor_set_error_cb and mediaeditor_unset_error_cb API pass
* @failcase 			If mediaeditor_set_error_cb or mediaeditor_unset_error_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mediaeditor_set_unset_error_cb_p(void)
{
    START_TEST;

    int nRet = mediaeditor_set_error_cb(g_hMediaEditorHandle, MediaeditorErrorCB, NULL);
    PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_error_cb", MediaEditorGetError(nRet));

    nRet = mediaeditor_unset_error_cb(g_hMediaEditorHandle);
    PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_unset_error_cb", MediaEditorGetError(nRet));

    return 0;
}

 //& purpose: Set and Unset layer priority
//& type: auto
/**
* @testcase 			ITc_mediaeditor_set_unset_layer_priority_changed_cb_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			set and unset layer priority
* @scenario				set layer priority and check callback hit, uset layer priority
* @apicovered			mediaeditor_add_layer, mediaeditor_set_layer_priority_changed_cb, mediaeditor_move_layer and mediaeditor_unset_layer_priority_changed_cb
* @passcase				If all precondition APIs, mediaeditor_set_layer_priority_changed_cb and mediaeditor_unset_layer_priority_changed_cb pass and callback is hit
* @failcase 			If mediaeditor_set_layer_priority_changed_cb, mediaeditor_unset_layer_priority_changed_cb Or any pre condition API fails
* @precondition			mediaeditor_add_layer and mediaeditor_move_layer
* @postcondition		NA
*/
int ITc_mediaeditor_set_unset_layer_priority_changed_cb_p(void)
{
    START_TEST;
	unsigned int nLayerId1 = 0;
	unsigned int nLayerId2 = 0;
	unsigned int nLayerPriority1 = 0;
	unsigned int nLayerPriority2 = 0;
	int nTimeoutId = 0;

	int nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId1, &nLayerPriority1);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &nLayerId2, &nLayerPriority2);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_set_layer_priority_changed_cb(g_hMediaEditorHandle, MediaeditorLayerPriorityChangedCB, NULL);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_layer_priority_changed_cb", MediaEditorGetError(nRet));

	g_bMediaEditorCallback = false;
	nRet = mediaeditor_move_layer(g_hMediaEditorHandle, nLayerId1, nLayerPriority2);
	PRINT_RESULT_CLEANUP(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_move_layer", MediaEditorGetError(nRet), mediaeditor_unset_layer_priority_changed_cb(g_hMediaEditorHandle));

	RUN_POLLING_LOOP;

	if ( g_bMediaEditorCallback == false )
	{
		FPRINTF("[Line : %d][%s] mediaeditor_set_layer_priority_changed_cb failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		mediaeditor_unset_layer_priority_changed_cb(g_hMediaEditorHandle);
		return 1;
	}

	nRet = mediaeditor_unset_layer_priority_changed_cb(g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_unset_layer_priority_changed_cb", MediaEditorGetError(nRet));

	return 0;
}

//& purpose: Start and Cancel rendering
//& type: auto
/**
* @testcase 			ITc_mediaeditor_start_cancel_render_p(void)
* @since_tizen 			7.0
* @author				SRID(ankit.sri1)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Start and Cancel rendering
* @scenario				Start and check render callback, Cancel rendering
* @apicovered			mediaeditor_add_layer, mediaeditor_add_clip, mediaeditor_start_render and mediaeditor_cancel_render
* @passcase				If all precondition APIs, mediaeditor_start_render and mediaeditor_cancel_render pass.
* @failcase 			If mediaeditor_start_render, mediaeditor_cancel_render Or any pre condition API fails
* @precondition			mediaeditor_add_layer and mediaeditor_add_clip
* @postcondition		NA
*/
int ITc_mediaeditor_start_cancel_render_p(void)
{
	START_TEST;
	unsigned int layer_id = 0;
	unsigned int layer_priority = 0;
	unsigned int clip_id = 0;
	unsigned int start = 0;
	unsigned int duration = 10;
	unsigned int in_point = 0;
	int nTimeoutId = 0;

	int nRet = mediaeditor_set_state_changed_cb(g_hMediaEditorHandle, MediaeditorStateChangedCB, NULL);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_set_state_changed_cb", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_layer(g_hMediaEditorHandle, &layer_id, &layer_priority);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_layer", MediaEditorGetError(nRet));

	nRet = mediaeditor_add_clip(g_hMediaEditorHandle, g_pszVideoClipPath, layer_id, start, duration, in_point, &clip_id);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_add_clip", MediaEditorGetError(nRet));

	g_bMediaEditorCallback = false;
	g_TargetState = MEDIAEDITOR_STATE_RENDERING;

	nRet = mediaeditor_start_render(g_hMediaEditorHandle, g_pszRenderPath, MediaeditorRenderCompletedCB, NULL);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_start_render", MediaEditorGetError(nRet));

	/* Wait to receive render completed callback */
	RUN_POLLING_LOOP;

	if ( g_bMediaEditorCallback == false )
	{
		FPRINTF("[Line : %d][%s] mediaeditor_start_render failed, error returned = Callback Not Invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = mediaeditor_cancel_render(g_hMediaEditorHandle);
	PRINT_RESULT(MEDIAEDITOR_ERROR_NONE, nRet, "mediaeditor_cancel_render", MediaEditorGetError(nRet));

	return 0;
}
/** @} */
/** @} */