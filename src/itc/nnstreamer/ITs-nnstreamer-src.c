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



/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/


/* @function		PushDummySrcApp
 * @description Internal function to push dummy into appsrc.
 */
static void PushDummySrcApp(ml_pipeline_src_h src_handle)
{
	FPRINTF("[Line : %d][%s] PushDummySrcApp function called\\n", __LINE__, API_NAMESPACE);
	ml_tensors_data_h data;
	ml_tensors_info_h info;
	if (ml_pipeline_src_get_tensors_info (src_handle, &info) == ML_ERROR_NONE)
	{
		ml_tensors_data_create (info, &data);
		ml_pipeline_src_input_data (src_handle, data, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
		ml_tensors_info_destroy (info);
	}
	return;
}
/* @function		PipeLineSrcDataCB
 * @description		The app-src callbacks for event handling
 */
static void PipeLineSrcDataCB(ml_pipeline_src_h src_handle, unsigned int length,void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s] PipeLineSrcDataCB callback hit\\n", __LINE__, API_NAMESPACE);
	ml_tensors_data_h data;
	ml_tensors_info_h info;
	if (ml_pipeline_src_get_tensors_info (src_handle, &info) == ML_ERROR_NONE)
	{
		ml_tensors_data_create (info, &data);
		ml_pipeline_src_input_data (src_handle, data, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
		ml_tensors_info_destroy (info);
	}
	return;
}
/**
 * @function		MlPipelineSinkCallback
 * @description A tensor-sink callback for sink handle in a pipeline
 */
static void MlPipelineSinkCallback(const ml_tensors_data_h data, const ml_tensors_info_h info, void *user_data)
{
	guint *count = (guint *) user_data;

	*count = *count + 1;
	g_bCallbackHit = true;
}
//& set: nnstreamer

/**
* @function 		ITs_nnstreamer_pipeline_src_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_src_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_pipeline_src_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;

	pszNnpipeline = g_strdup ("appsrc name=srcx ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! tensor_sink name=sinkx");

	nRet = ml_pipeline_construct (pszNnpipeline, NULL, NULL, &g_hPipelinehandle);
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
* @function 		ITs_nnstreamer_pipeline_src_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_src_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_pipeline_src_cleanup\\n", __LINE__, API_NAMESPACE);
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
	g_free (pszNnpipeline);
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_src_get_release_handle_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To create and release src pipeline handle
* @scenario			To create and release src pipeline handle
* @apicovered			ml_pipeline_src_get_handle, ml_pipeline_src_release_handle
* @passcase			When ml_pipeline_src_get_handle, ml_pipeline_src_release_handle is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To create and release src pipeline handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_src_get_release_handle_p(void)
{
	START_TEST;
	int nRet = -1;
	static ml_pipeline_src_h hPipeSrcHandle =  NULL;

	nRet = ml_pipeline_src_get_handle (g_hPipelinehandle, "srcx", &hPipeSrcHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSrcHandle, "ml_pipeline_src_get_handle");

	nRet = ml_pipeline_src_release_handle (hPipeSrcHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_release_handle", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_src_get_tensors_info_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To get tensors info from pipeline src handle
* @scenario			To get tensors info from pipeline src handle
* @apicovered			ml_pipeline_src_get_tensors_info
* @passcase			When ml_pipeline_src_get_tensors_info and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To get tensors info from pipeline src handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_src_get_tensors_info_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_src_h hPipeSrcHandle =  NULL;
	ml_tensors_info_h hTensorinfo = NULL;

	nRet = ml_pipeline_src_get_handle (g_hPipelinehandle, "srcx", &hPipeSrcHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSrcHandle, "ml_pipeline_src_get_handle");

	nRet = ml_pipeline_src_get_tensors_info (hPipeSrcHandle, &hTensorinfo);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_tensors_info", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfo, "ml_pipeline_src_get_tensors_info");

	nRet = ml_tensors_info_destroy (hTensorinfo);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_src_get_input_data_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To get input data from src pipeline
* @scenario			To get input data from src pipeline
* @apicovered			ml_pipeline_src_get_input_data
* @passcase			When ml_pipeline_src_get_input_data and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To get input data from src pipeline
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_src_input_data_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_src_h hPipeSrcHandle =  NULL;
	ml_tensors_info_h hTensorinfo = NULL;
	ml_tensors_data_h hTensorData = NULL;
	uint8_t uintarray[4] = {1,1,1,1};

	nRet = ml_pipeline_src_get_handle (g_hPipelinehandle, "srcx", &hPipeSrcHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSrcHandle, "ml_pipeline_src_get_handle");

	nRet = ml_pipeline_src_get_tensors_info (hPipeSrcHandle, &hTensorinfo);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_tensors_info", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfo, "ml_pipeline_src_get_tensors_info");

	nRet = ml_tensors_data_create (hTensorinfo, &hTensorData);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfo));
	CHECK_HANDLE_CLEANUP(hTensorData, "ml_tensors_data_create", ml_tensors_info_destroy (hTensorinfo));

	nRet = ml_tensors_data_set_tensor_data (hTensorData, 0, uintarray, 4);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_set_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy (hTensorData); ml_tensors_info_destroy (hTensorinfo));

	nRet = ml_pipeline_src_input_data (hPipeSrcHandle, hTensorData, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_input_data", NnStreamerGetError(nRet), ml_tensors_data_destroy (hTensorData); ml_tensors_info_destroy (hTensorinfo));

	nRet = ml_tensors_data_destroy (hTensorData);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hTensorinfo);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_src_set_event_cb_p
* @since_tizen			6.5
* @author            		SRID(nibha.sharma)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Sets the callbacks which will be invoked when a new input frame may be accepted.
* @scenario			Sets the callbacks which will be invoked when a new input frame may be accepted.
* @apicovered			ml_pipeline_src_set_event_cb
* @passcase			When ml_pipeline_src_set_event_cb and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Sets the callbacks which will be invoked when a new input frame may be accepted.
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_src_set_event_cb_p (void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_src_h hPipeSrcHandle =  NULL;
	ml_pipeline_sink_h  hPipeSinkHandle = NULL;
	guint *pszCountSink;

	ml_pipeline_src_callbacks_s callback = { 0, };
	callback.need_data = PipeLineSrcDataCB;

	pszCountSink = (guint *) g_malloc0 (sizeof (guint));
	CHECK_HANDLE(pszCountSink, "pszCountSink");
	*pszCountSink = 0;

	g_bCallbackHit = false;

	nRet =  ml_pipeline_construct (pszNnpipeline, NULL, NULL, &g_hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet),FREE_MEMORY(pszCountSink));

	nRet = ml_pipeline_sink_register (g_hPipelinehandle, "sinkx", MlPipelineSinkCallback, pszCountSink, &hPipeSinkHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_sink_register", NnStreamerGetError(nRet),FREE_MEMORY(pszCountSink));
	CHECK_HANDLE_CLEANUP(hPipeSinkHandle, "ml_pipeline_sink_register",FREE_MEMORY(pszCountSink));

	nRet = ml_pipeline_src_get_handle(g_hPipelinehandle, "srcx", &hPipeSrcHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet), FREE_MEMORY(pszCountSink));
	CHECK_HANDLE_CLEANUP(hPipeSrcHandle, "ml_pipeline_src_get_handle", FREE_MEMORY(pszCountSink));

	nRet = ml_pipeline_src_set_event_cb (hPipeSrcHandle, &callback, NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_set_event_cb", NnStreamerGetError(nRet), FREE_MEMORY(pszCountSink));

	nRet = ml_pipeline_start (g_hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet), FREE_MEMORY(pszCountSink));

	PushDummySrcApp(hPipeSrcHandle);
	g_usleep(50000);

	PRINT_RESULT(true, g_bCallbackHit, "ml_pipeline_src_set_event_cb", NnStreamerGetError(nRet));
	nRet = ml_pipeline_stop (g_hPipelinehandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet));

	/** Wait while the pipeline processes the buffers and flush the data */
	g_usleep (200000);
	ml_pipeline_flush (g_hPipelinehandle, false);
	g_usleep (200000);

	FREE_MEMORY(pszCountSink);

	return 0;
}
