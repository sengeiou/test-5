//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-nnstreamer-common.h"

/**
 * @function		MlPipelineStateChangeCallback
 * @description Pipeline state changed callback
 */
static void MlPipelineStateChangeCallback(ml_pipeline_state_e state, void *user_data)
{
	TestPipeState *pipe_state;

	pipe_state = (TestPipeState *) user_data;

	switch (state) {
		case ML_PIPELINE_STATE_PAUSED:
			pipe_state->paused = TRUE;
			break;
		case ML_PIPELINE_STATE_PLAYING:
			pipe_state->playing = TRUE;
			break;
		default:
			break;
	}
}


/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

//& set: nnstreamer

/**
* @function 		ITs_nnstreamer_pipeline_switch_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_switch_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_pipeline_switch_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;

	pszNnpipeline = g_strdup ("input-selector name=ins ! tensor_converter ! tensor_sink name=sinkx "
		"videotestsrc is-live=true ! videoconvert ! ins.sink_0 "
		"videotestsrc is-live=true ! videoconvert ! ins.sink_1");

	g_pipePipeLineState = (TestPipeState *) g_new0 (TestPipeState, 1);
	nRet = ml_pipeline_construct (pszNnpipeline, MlPipelineStateChangeCallback, g_pipePipeLineState, &g_hPipelinehandle);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_pipeline_construct failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_pipeline_construct failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_pipeline_construct is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_pipeline_construct is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_pipeline_construct failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_pipeline_construct failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNnstreamerCreation = false;
	}
	else
	{
		g_bNnstreamerCreation = true;
	}
	return;
}

/**
* @function 		ITs_nnstreamer_pipeline_switch_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_switch_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_pipeline_switch_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	if (g_hPipelinehandle) {
		int nRet = ml_pipeline_destroy (g_hPipelinehandle);
		if(nRet !=0)
		{
			FPRINTF("ml_pipeline_destroy failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "ml_pipeline_destroy failed");
		}
		g_hPipelinehandle = NULL;
	}
	g_free (g_pipePipeLineState);
	g_free (pszNnpipeline);
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_switch_get_release_handle_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To get and release switch pipeline handle
* @scenario			To get and release switch pipeline handle
* @apicovered			ml_pipeline_switch_get_handle, ml_pipeline_switch_release_handle
* @passcase			When ml_pipeline_switch_get_handle, ml_pipeline_switch_release_handle is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Get and release switch pipeline handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_switch_get_release_handle_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_switch_h hPipeSwitchHandle =  NULL;
	ml_pipeline_switch_e eSwitchType = -1;

	CHECK_HANDLE(g_hPipelinehandle, "ITc_nnstreamer_pipeline_ml_pipeline_switch_get_release_handle_p");

	nRet = ml_pipeline_switch_get_handle (g_hPipelinehandle, "ins", &eSwitchType, &hPipeSwitchHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_switch_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSwitchHandle, "ml_pipeline_switch_get_handle");

	if(eSwitchType < 0)
	{
		FPRINTF("[Line : %d][%s] eSwitchType value is invalid \\n", __LINE__, API_NAMESPACE);
		ml_pipeline_switch_release_handle (hPipeSwitchHandle);
		return 1;
	}

	nRet = ml_pipeline_switch_release_handle (hPipeSwitchHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_switch_release_handle", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_switch_select_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To select switch pipeline hanlde
* @scenario			To select switch pipeline hanlde
* @apicovered			ml_pipeline_switch_select
* @passcase			When ml_pipeline_switch_select and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To select switch pipeline hanlde
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_switch_select_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_switch_h hPipeSwitchHandle =  NULL;
	ml_pipeline_switch_e eSwitchType;

	nRet = ml_pipeline_switch_get_handle (g_hPipelinehandle, "ins", &eSwitchType, &hPipeSwitchHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_switch_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSwitchHandle, "ml_pipeline_switch_get_handle");

	if(eSwitchType < 0)
	{
		FPRINTF("[Line : %d][%s] eSwitchType value is invalid \\n", __LINE__, API_NAMESPACE);
		ml_pipeline_switch_release_handle (hPipeSwitchHandle);
		return 1;
	}

	nRet = ml_pipeline_switch_select (hPipeSwitchHandle, "sink_1");
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_switch_select", NnStreamerGetError(nRet),ml_pipeline_switch_release_handle (hPipeSwitchHandle));

	nRet = ml_pipeline_switch_release_handle (hPipeSwitchHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_switch_release_handle", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_switch_get_pad_list_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To get Pad list from switch handle
* @scenario			To get Pad list from switch handle
* @apicovered			ml_pipeline_switch_get_pad_list
* @passcase			When ml_pipeline_switch_get_pad_list and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To get Pad list from switch handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_switch_get_pad_list_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_switch_h hPipeSwitchHandle =  NULL;
	ml_pipeline_switch_e eSwitchType = -1;
	gchar ** nodeList = NULL;

	nRet = ml_pipeline_switch_get_handle (g_hPipelinehandle, "ins", &eSwitchType, &hPipeSwitchHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_switch_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSwitchHandle, "ml_pipeline_switch_get_handle");
	if(eSwitchType < 0)
	{
		FPRINTF("[Line : %d][%s] eSwitchType value is invalid \\n", __LINE__, API_NAMESPACE);
		ml_pipeline_switch_release_handle (hPipeSwitchHandle);
		return 1;
	}

	nRet = ml_pipeline_switch_get_pad_list (hPipeSwitchHandle, &nodeList);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_switch_get_pad_list", NnStreamerGetError(nRet), ml_pipeline_switch_release_handle (hPipeSwitchHandle));
	CHECK_HANDLE_CLEANUP(nodeList, "ml_pipeline_switch_get_pad_list", ml_pipeline_switch_release_handle (hPipeSwitchHandle));

	nRet = ml_pipeline_switch_release_handle (hPipeSwitchHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_switch_release_handle", NnStreamerGetError(nRet));

	return 0;
}
