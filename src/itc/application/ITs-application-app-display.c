//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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

bool g_bFeatureApp = false;
bool g_bAppInfoCreation = false;

typedef struct app_context_s {
	char *id;
	app_info_app_component_type_e comp_type;
} app_context;

static app_context g_hContext;
app_info_h g_hApp_info = NULL;
/**
* @function 		ITs_application_app_get_display_state_startup
* @description	 	Called before each test
* @parameter		NA
* @return 		NA
*/
void ITs_application_app_get_display_state_startup(void)
{
	int nRet = -1;
	g_bAppInfoCreation = false;

	nRet = app_get_id(&g_hContext.id);
	if (nRet != APP_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to get id, nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return;
	}

	nRet = app_info_create(g_hContext.id, &g_hApp_info);

	if(g_hApp_info == NULL){
		FPRINTF("[Line : %d][%s] Failed to create app info, nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return;
	}

	if (nRet != APP_MANAGER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to create app info, nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return;
	}

	nRet = app_info_get_app_component_type(g_hApp_info, &g_hContext.comp_type);
	if (nRet != APP_MANAGER_ERROR_NONE) {
		FPRINTF("[Line : %d][%s] Failed to get app component type, nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return;
	}
	g_bAppInfoCreation = true;
	g_bFeatureApp = TCTCheckSystemInfoFeatureSupported(FEATURE_APP, API_NAMESPACE);
	if(!g_bFeatureApp)
	{
		FPRINTF("[Line : %d][%s] System Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return;
	}
}

/**
* @function 		ITs_application_app_get_display_state_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 		NA
*/
void ITs_application_app_get_display_state_cleanup(void)
{
	if (g_hContext.id) {
		free(g_hContext.id);
		g_hContext.id = NULL;
	}
	if(g_hApp_info != NULL){
		app_info_destroy(g_hApp_info);
		g_hApp_info = NULL;
	}
}


//& type: auto
//& purpose: Test app_get_display_state
/**
* @testcase 			ITc_application_app_get_display_state_p
* @since_tizen			5.5
* @author			SRID(p.chauhan)
* @reviewer			SRID(priya.kohli)
* @type 			auto
* @description			Test app_get_display_state
* @scenario			Call Test app_get_display_state
* @apicovered			app_get_display_state
* @passcase			When app_get_display_state is successful and return correct value.
* @failcase			If target API fails or value mis-match happens.
* @precondition			None
* @postcondition		None
*/
int ITc_application_app_get_display_state_p(void)
{
	START_TEST_DISPLAY;
	app_display_state_e eState;
	int nRet = -1;

	nRet = app_get_display_state(&eState);

	if (nRet != APP_ERROR_NONE) {
		if (nRet == APP_ERROR_NOT_SUPPORTED && !g_bFeatureApp) {
			FPRINTF("[Line : %d][%s] display state is not supported,  nRet = %d \\n", __LINE__, API_NAMESPACE, nRet);
			return 0;
		}

		if (nRet == APP_ERROR_INVALID_CONTEXT) {
			FPRINTF("[Line : %d][%s] This is service-application, nRet = %d \\n", __LINE__, API_NAMESPACE, nRet);
			return 0;
		}

		FPRINTF("[Line : %d][%s] Failed to get display state, nRet = %d\\n", __LINE__, API_NAMESPACE, nRet);
		return 1;
	}
	if (eState == APP_DISPLAY_STATE_OFF) {
		FPRINTF("[Line : %d][%s] State is OFF not the expected State, eState = %d \\n", __LINE__, API_NAMESPACE, (int)eState);
		return 1;
	}
	return 0;
}
