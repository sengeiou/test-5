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
#include "ITs-player-display-common.h"

/** @addtogroup itc-player-display
*  @ingroup itc
*  @{
*/
//& set: Player
bool g_bPlayerCreation;

/**
* @function			ITs_player_360_startup
* @description		Called before each test, created player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_360_startup(void)
{
	g_bIsSupported = false;
	ecore_main_loop_glib_integrate();
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_player_360_startup\\n", __LINE__, API_NAMESPACE);
#endif

	CreateEvasWindow();
	if ( g_pEvasObject == NULL )
	{
		FPRINTF("[Line : %d][%s] Evas window object is not created, failed in Precondition\\n", __LINE__, API_NAMESPACE);
		g_bPlayerCreation = false;
		return;
	}

	int nRet = player_create(&g_player);
	if ( nRet != PLAYER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create player, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		g_bPlayerCreation = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Player created successfully\\n",__LINE__, API_NAMESPACE);
		g_bPlayerCreation = true;
	}

	if(TCTCheckSystemInfoFeatureSupported(OPENGL_FEATURE, API_NAMESPACE) && TCTCheckSystemInfoFeatureSupported(SPHERICAL_VIDEO_FEATURE, API_NAMESPACE))
	{
		g_bIsSupported = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s] SPHERICAL and OPENGL feature not supported \\n", __LINE__, API_NAMESPACE);
		g_bIsSupported = false;
	}
	return;
}

/**
* @function			ITs_player_360_cleanup
* @description		Called after each test, destroys player handle
* @parameter		NA
* @return			NA
*/
void ITs_player_360_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_player_360_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bPlayerCreation && g_player )
	{
		int nRet = player_destroy (g_player);
		if ( nRet != PLAYER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] player_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, PlayerGetError(nRet));
		}
		g_player = NULL;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Player was not created\\n",__LINE__, API_NAMESPACE);
	}
	if ( g_pEvasObject )
	{
		evas_object_del(g_pEvasObject);
		g_pEvasObject = NULL;
	}
	if ( g_pEvasWindow )
	{
		evas_object_del(g_pEvasWindow);
		g_pEvasWindow = NULL;
	}
	g_bIsSupported = false;
	return;
}
//& purpose: Gets information whether the current content of the player is spherical.
//& type: auto
/**
* @testcase			ITc_media_player_360_is_content_spherical_p
* @author			SRID(ankit.j)
* @reviewer			SRID(nibha.sharma)
* @type				auto
* @since_tizen			5.0
* @description			Gets information whether the current content of the player is spherical.
* @scenario			Gets information whether the current content of the player is spherical.
* @apicovered			player_360_is_content_spherical
* @passcase			The value indicating whether the content is spherical returns success
* @failcase			The value indicating whether the content is spherical returns negative value
* @precondition			The player state must be one of:#PLAYER_STATE_READY, #PLAYER_STATE_PLAYING, or #PLAYER_STATE_PAUSED
* @postcondition		N/A
*/

int ITc_media_player_360_is_content_spherical_p(void)
{
	START_TEST;
	bool isContentSpherical=false;
	int nRet = -1;
	player_state_e state;
	char pPath[PATH_LEN] = {0};

	if ( false == PlayerAppendToAppDataPath(MEDIA_360_PATH, pPath))
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_get_state(g_player,&state);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_get_state", PlayerGetError(nRet));

	PlayerGetState(state);
	if ( state != PLAYER_STATE_IDLE )
	{
		FPRINTF("[Line : %d][%s] Player state does not change after player_create() call",__LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = player_set_uri(g_player, pPath);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_uri", PlayerGetError(nRet));

	nRet = player_set_display(g_player, PLAYER_DISPLAY_TYPE_OVERLAY, GET_DISPLAY(g_pEvasWindow));
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_set_display", PlayerGetError(nRet));

	nRet = player_prepare(g_player);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_prepare", PlayerGetError(nRet));

	nRet = player_360_is_content_spherical(g_player, &isContentSpherical);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_is_content_spherical", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_is_content_spherical", PlayerGetError(nRet));

	if(isContentSpherical != true)
	{
		FPRINTF("[Line : %d][%s] ITc_media_player_360_is_content_spherical_p, failed. It has returned false for spherical 360 media content \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;

}
/** @addtogroup itc-player-testcases
*  @brief		Integration testcases for module player
*  @ingroup		itc-player
*  @{
*/

//& purpose: Gets and Sets the 360 video display mode
//& type : auto
/**
* @testcase				ITc_player_360_is_set_enabled_p
* @author				SRID(manu.tiwari)
* @reviewer				SRID(abhishek.j)
* @type					auto
* @since_tizen			5.0
* @description			Gets and Sets the 360 video display mode
* @scenario				Gets and Sets the 360 video display mode
* @apicovered			player_360_set_enabled, player_360_is_enabled
* @passcase				When API returns PLAYER_ERROR_NONE
* @failcase				When API not returns PLAYER_ERROR_NONE
* @precondition			player must be created
* @postcondition		player must be destroyed
*/
int ITc_player_360_is_set_enabled_p(void)
{
	START_TEST;
	//isEnabled = false = display with full panorama mode
	//isEnabled = true = display with 360 video mode
	bool nSetEnabled = false;
	bool nIsEnabled = true;    //default value
	//Target API
	int nRet = player_360_set_enabled(g_player, nSetEnabled);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_set_enabled", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_set_enabled", PlayerGetError(nRet));
	// Target API
	nRet = player_360_is_enabled(g_player, &nIsEnabled);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_is_enabled", PlayerGetError(nRet));
	if(nIsEnabled != false)
	{
		FPRINTF("[Line : %d][%s] video display mode mismatch\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}
//& purpose: Sets and Gets the 360 video direction of view
//& type : auto
/**
* @testcase				ITc_player_360_set_get_direction_of_view_p
* @author				SRID(manu.tiwari)
* @reviewer				SRID(abhishek.j)
* @type					auto
* @since_tizen			5.0
* @description			Sets and Gets the 360 video direction of view
* @scenario				Sets and Gets the 360 video direction of view
* @apicovered			player_360_set_direction_of_view, player_360_get_direction_of_view
* @passcase				When API returns PLAYER_ERROR_NONE
* @failcase				When API not returns PLAYER_ERROR_NONE
* @precondition			player must be created
* @postcondition		player must be destroyed
*/
int ITc_player_360_set_get_direction_of_view_p(void)
{
	START_TEST;
	float nGetYaw = -1.0;
	float nSetYaw = 3.14;
	float nSetPitch = 1.57;
	float nGetPitch = -1.0;
	int nRet = player_360_set_direction_of_view(g_player, nSetYaw, nSetPitch);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_set_direction_of_view", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_set_direction_of_view", PlayerGetError(nRet));
	nRet = player_360_get_direction_of_view(g_player, &nGetYaw, &nGetPitch);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_get_direction_of_view", PlayerGetError(nRet));
	if (( nSetPitch != nGetPitch ) || ( nSetYaw != nGetYaw ))
	{
		FPRINTF("[Line : %d][%s] error returned = set get pitch values mismatched, set pitch value = %f, get pitch value = %f, set yaw value = %f, get yaw value = %f\\n", __LINE__, API_NAMESPACE, nSetPitch, nGetPitch, nSetYaw, nGetYaw);
		return 1;
	}
	return 0;
}
//& purpose: Sets and Gets the zoom level of 360 video
//& type : auto
/**
* @testcase				ITc_player_360_set_get_zoom_p
* @author				SRID(manu.tiwari)
* @reviewer				SRID(abhishek.j)
* @type					auto
* @since_tizen			5.0
* @description			Sets and Gets the zoom level of 360 video
* @scenario				Sets and Gets the zoom level of 360 video
* @apicovered			player_360_set_zoom, player_360_get_zoom
* @passcase				When API returns PLAYER_ERROR_NONE
* @failcase				When API not returns PLAYER_ERROR_NONE
* @precondition			player must be created
* @postcondition		player must be destroyed
*/
int ITc_player_360_set_get_zoom_p(void)
{
	START_TEST;

	float nSetZoom = 5.0;
	float nGetZoom = 0.0;
	int nRet = player_360_set_zoom(g_player, nSetZoom);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_set_zoom", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_set_zoom", PlayerGetError(nRet));
	nRet = player_360_get_zoom(g_player, &nGetZoom);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_get_zoom", PlayerGetError(nRet));
	if(nGetZoom != nSetZoom)
	{
		FPRINTF("[Line : %d][%s] error returned = set get zoom values mismatched, set value = %f, get value = %f\\n", __LINE__, API_NAMESPACE, nSetZoom, nGetZoom);
		return 1;
	}
	return 0;
}
//& purpose: Sets and Gets the field of view information of 360 video
//& type : auto
/**
* @testcase				ITc_player_360_set_get_field_of_view
* @author				SRID(manu.tiwari)
* @reviewer				SRID(abhishek.j)
* @type					auto
* @since_tizen			5.0
* @description			Sets and Gets the field of view information of 360 video
* @scenario				Sets and Gets the field of view information of 360 video
* @apicovered			player_360_set_field_of_view, player_360_get_field_of_view
* @passcase				When API returns PLAYER_ERROR_NONE
* @failcase				When API not returns PLAYER_ERROR_NONE
* @precondition			player must be created
* @postcondition		player must be destroyed
*/
int ITc_player_360_set_get_field_of_view(void)
{
	START_TEST;
	int nSethorizontaldegrees = 120;
	int nSetverticaldegrees = 67;
	int nGethorizontaldegrees = 0;
	int nGetverticaldegrees = 0;
	int nRet = player_360_set_field_of_view(g_player, nSethorizontaldegrees, nSetverticaldegrees);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_set_field_of_view", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_set_field_of_view", PlayerGetError(nRet));
	nRet = player_360_get_field_of_view(g_player, &nGethorizontaldegrees, &nGetverticaldegrees);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_get_field_of_view", PlayerGetError(nRet));
	if (( nSethorizontaldegrees != nGethorizontaldegrees ) || ( nSetverticaldegrees != nGetverticaldegrees ))
	{
		FPRINTF("[Line : %d][%s] error returned = set get field of view values mismatched, set horizontal degree = %d, get horizontal degree = %d, set vertical degree = %d, get vertical degree = %d\\n", __LINE__, API_NAMESPACE, nSethorizontaldegrees, nGethorizontaldegrees, nSetverticaldegrees, nGetverticaldegrees);
		return 1;
	}
	return 0;
}

//& purpose: Sets zoom with field of view information of 360 video
//& type : auto
/**
* @testcase				ITc_player_360_set_zoom_with_field_of_view_p
* @author				SRID(manoj.g2)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @since_tizen			5.0
* @description			Sets zoom with field of view information of 360 video
* @scenario				Sets zoom with field of view information of 360 video
* @apicovered			player_360_set_zoom_with_field_of_view, player_360_get_field_of_view
* @passcase				When API returns PLAYER_ERROR_NONE
* @failcase				When API not returns PLAYER_ERROR_NONE
* @precondition			player must be created
* @postcondition		player must be destroyed
*/
int ITc_player_360_set_zoom_with_field_of_view_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSethorizontaldegrees = 120;
	int nSetverticaldegrees = 90;
	int nGetHorizontalDegree = 0;
	int nGetVerticalDegree = 0;
	float nSetlevel = 3.0;
	float nGetlevel = 0.0;

	//Target API
	nRet = player_360_set_zoom_with_field_of_view(g_player, nSetlevel, nSethorizontaldegrees, nSetverticaldegrees);
	if ( false == g_bIsSupported )
	{
		PRINT_RESULT(PLAYER_ERROR_FEATURE_NOT_SUPPORTED_ON_DEVICE, nRet, "player_360_set_zoom_with_field_of_view", PlayerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_set_zoom_with_field_of_view", PlayerGetError(nRet));

	nRet = player_360_get_zoom(g_player, &nGetlevel);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_get_zoom", PlayerGetError(nRet));
	if(nGetlevel != nSetlevel)
	{
		FPRINTF("[Line : %d][%s] player_360_get_zoom after call is %f ",__LINE__, API_NAMESPACE, nGetlevel);
		return 1;
	}

	nRet = player_360_get_field_of_view(g_player, &nGetHorizontalDegree, &nGetVerticalDegree);
	PRINT_RESULT(PLAYER_ERROR_NONE, nRet, "player_360_get_field_of_view", PlayerGetError(nRet));
	if (( nSethorizontaldegrees != nGetHorizontalDegree ) || ( nSetverticaldegrees != nGetVerticalDegree ))
	{
		FPRINTF("[Line : %d][%s] error returned = set get field of view values mismatched, set horizontal degree = %d, get horizontal degree = %d, set vertical degree = %d, get vertical degree = %d\\n", __LINE__, API_NAMESPACE, nSethorizontaldegrees, nGetHorizontalDegree, nSetverticaldegrees, nGetVerticalDegree);
		return 1;
	}
	return 0;
}
/** @} */
/** @} */
