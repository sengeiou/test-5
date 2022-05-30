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

ml_nnfw_hw_e g_eMlNnHardwareType[] = {
	ML_NNFW_HW_ANY,
	ML_NNFW_HW_AUTO,
	ML_NNFW_HW_CPU,
	ML_NNFW_HW_CPU_SIMD,
	ML_NNFW_HW_GPU,
	ML_NNFW_HW_NPU,
	ML_NNFW_HW_CPU_NEON,
	ML_NNFW_HW_NPU_MOVIDIUS,
	ML_NNFW_HW_NPU_EDGE_TPU,
	ML_NNFW_HW_NPU_VIVANTE,
	ML_NNFW_HW_NPU_SR
};


/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/


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
//& set: nnstreamer

/**
* @function 		ITs_nnstreamer_pipeline_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_pipeline_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;

	pszNnpipeline = g_strdup ("videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=30/1 ! tensor_converter ! valve name=valve1 ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx");

	g_unsinkCount = (guint *) g_malloc (sizeof (guint));
	*g_unsinkCount = 0;

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
* @function 		ITs_nnstreamer_pipeline_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_pipeline_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_pipeline_cleanup\\n", __LINE__, API_NAMESPACE);
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
	g_free (g_unsinkCount);
	g_free (g_pipePipeLineState);
	g_free (pszNnpipeline);
}


/** @addtogroup itc-nnstreamer-testcases
*  @brief 		Integration testcases for module nnstreamer
*  @ingroup 	itc-nnstreamer
*  @{
*/


/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_construct_destroy_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Create and Destroy ml pipeline handle
* @scenario				Create and Destroy ml pipeline handle
* @apicovered			ml_pipeline_construct, ml_pipeline_destroy
* @passcase				When ml_pipeline_construct, ml_pipeline_destroy is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Create and Destroy ml pipeline handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_construct_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc num_buffers=2 ! fakesink";
	ml_pipeline_h hMlPipeline = NULL;

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase			ITc_nnstreamer_pipeline_ml_pipeline_get_state_p
* @since_tizen			5.5
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			get machine learning pipeline state
* @scenario				get machine learning pipeline state
* @apicovered			ml_pipeline_get_state
* @passcase				When ml_pipeline_get_state is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Get machine learning pipeline state
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_get_state_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_state_e eMlState = -1;
	nRet = ml_pipeline_start (g_hPipelinehandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet));

	nRet = ml_pipeline_get_state (g_hPipelinehandle, &eMlState);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_get_state ", NnStreamerGetError(nRet), ml_pipeline_stop(g_hPipelinehandle));

	if(eMlState < 0 || eMlState ==  ML_PIPELINE_STATE_UNKNOWN || eMlState ==  ML_PIPELINE_STATE_NULL )
	{
		FPRINTF("eMlState value is not valid and is %d \\n", eMlState);
		ml_pipeline_stop(g_hPipelinehandle);
		return 1;
	}

	nRet = ml_pipeline_stop(g_hPipelinehandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_start_stop_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 				auto
* @description			start and stop the ml pipeline
* @scenario				start and stop the ml pipeline
* @apicovered			ml_pipeline_start, ml_pipeline_stop
* @passcase				When l_pipeline_start, ml_pipeline_stop is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API start and stop the ml pipeline
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_start_stop_p(void)
{
	START_TEST;
	int nRet = -1;
 	nRet = ml_pipeline_start (g_hPipelinehandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet));

	nRet = ml_pipeline_stop(g_hPipelinehandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_check_nnfw_availability_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Test NNStreamer check nnfw availabiliry
* @scenario			Test NNStreamer check nnfw availabiliry
* @apicovered			ml_check_nnfw_availability
* @passcase			When ml_check_nnfw_availability  is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Test NNStreamer check nnfw availabiliry
//& type: auto
int ITc_nnstreamer_pipeline_ml_check_nnfw_availability_p(void)
{
	START_TEST;
	int nRet = -1;
	bool isNnAvailable = false;
	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMlNnHardwareType) / sizeof(g_eMlNnHardwareType[0]);

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, g_eMlNnHardwareType[nEnumCounter], &isNnAvailable);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_check_nnfw_availability", NnStreamerGetError(nRet));
	}

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_sink_register_unregister_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To register and unregister sink pipeline
* @scenario			To register and unregister sink pipeline
* @apicovered			ml_pipeline_sink_register, ml_pipeline_sink_unregister
* @passcase			When ml_pipeline_sink_register, ml_pipeline_sink_unregister is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To To register and unregister sink pipeline
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_sink_register_unregister_p(void)
{
	START_TEST;
	int nRet = -1 ,nTimeoutId = 0;
	static ml_pipeline_sink_h hPipeSinkHandle =  NULL;

	g_bCallbackHit = false;

	nRet = ml_pipeline_sink_register (g_hPipelinehandle, "sinkx", MlPipelineSinkCallback, g_unsinkCount, &hPipeSinkHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_sink_register", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeSinkHandle, "ml_pipeline_sink_register");


	nRet = ml_pipeline_start (g_hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet) ,ml_pipeline_sink_unregister (hPipeSinkHandle));

	RUN_POLLING_LOOP;

	nRet = ml_pipeline_stop (g_hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet), ml_pipeline_sink_unregister (hPipeSinkHandle));

	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "ml_pipeline_stop", NnStreamerGetError(nRet), ml_pipeline_sink_unregister (hPipeSinkHandle));

	nRet = ml_pipeline_sink_unregister (hPipeSinkHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_sink_unregister", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_valve_get_release_handle_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To create and release valve pipeline handle
* @scenario			To create and release valve pipeline handle
* @apicovered			ml_pipeline_valve_get_handle, ml_pipeline_valve_release_handle
* @passcase			When ml_pipeline_valve_get_handle, ml_pipeline_valve_release_handle is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To create and release valve pipeline handle
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_valve_get_release_handle_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_valve_h hPipeValveHandle =  NULL;

	nRet = ml_pipeline_valve_get_handle (g_hPipelinehandle, "valve1", &hPipeValveHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_valve_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeValveHandle, "ml_pipeline_valve_get_handle");

	nRet = ml_pipeline_valve_release_handle (hPipeValveHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_valve_release_handle", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_pipeline_valve_set_open_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To Set pipeline valve handle open
* @scenario			To Set pipeline valve handle open
* @apicovered			ml_pipeline_valve_get_handle, ml_pipeline_valve_release_handle
* @passcase			When ml_pipeline_valve_set_open and precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Set pipeline valve handle open
//& type: auto
int ITc_nnstreamer_pipeline_ml_pipeline_valve_set_open_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_valve_h hPipeValveHandle =  NULL;

	nRet = ml_pipeline_valve_get_handle (g_hPipelinehandle, "valve1", &hPipeValveHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_valve_get_handle", NnStreamerGetError(nRet));
	CHECK_HANDLE(hPipeValveHandle, "ml_pipeline_valve_get_handle");

	nRet = ml_pipeline_valve_set_open (hPipeValveHandle, false);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_valve_set_open", NnStreamerGetError(nRet), ml_pipeline_valve_release_handle (hPipeValveHandle));

	nRet = ml_pipeline_valve_release_handle (hPipeValveHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_valve_release_handle", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_tizensensor_p
* @since_tizen			6.0
* @author				SR(yongjoo1.ahn)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test the tensor_src_tizensensor element which integrates Tizen sensor framework to NNStreamer tensor-source filter
* @scenario				Test pipeline with tensor_src_tizensensor element
* @apicovered			ml_pipline_construct, ml_pipeline_start, ml_pipeline_stop, ml_pipeline_destroy
* @passcase				When the pipeline is successfully launched or the accelerometer sensor is not supported.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test tensor_src_tizensensor element
//& type: auto
int ITc_nnstreamer_pipeline_tizensensor_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_pipeline_h hMlPipeline = NULL;
	bool isAccelerometerAvailable = false;
	bool isTizenSensorSrcAvailable = false;
	char *pszPipeLine = "tensor_src_tizensensor type=accelerometer framerate=100/1 ! tensor_sink sync=true";

	isAccelerometerAvailable = TCTCheckSystemInfoFeatureSupported("http://tizen.org/feature/sensor.accelerometer", API_NAMESPACE);

	if (!isAccelerometerAvailable) {
		/* Do not run this test if the accelerometer sensor is not supported  */
		FPRINTF("[Line : %d][%s] sensor.accelerometer is NOT supported\\n", __LINE__, API_NAMESPACE);
		dlog_print(DLOG_INFO, "NativeTCT", "[Line:%d][%s] sensor.accelerometer is NOT supported", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = ml_check_element_availability ("tensor_src_tizensensor", &isTizenSensorSrcAvailable);
	if (nRet !=ML_ERROR_NONE || !isTizenSensorSrcAvailable) {
		FPRINTF("[%d][%s] tizensensorsrc is not available on the device!\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_start (hMlPipeline);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError (nRet), ml_pipeline_destroy (hMlPipeline));

	sleep (1);

	nRet = ml_pipeline_stop (hMlPipeline);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError (nRet), ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_check_element_availability_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(j.abhishek)
* @type 				auto
* @description			To check NNStreamer Utility for checking an element availability.
* @scenario				To check NNStreamer Utility for checking an element availability.
* @apicovered			ml_check_element_availability
* @passcase				When ml_check_element_availability and Precondition API is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: To check NNStreamer Utility for checking an element availability.
//& type: auto
int ITc_nnstreamer_pipeline_ml_check_element_availability_p(void)
{
	START_TEST;
	int nRet = -1, nArrSize = 3, nIndex;
	bool b_isAvailable = false;
	char *psz_testString[3] = {"tensor_converter","tensor_filter","appsrc"};

	for (nIndex=0;nIndex<nArrSize;nIndex++)
	{
		b_isAvailable = false;
		nRet = ml_check_element_availability (psz_testString[nIndex], &b_isAvailable);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_check_element_availability", NnStreamerGetError(nRet));
		if (b_isAvailable == false)
		{
			FPRINTF("[%s:%d] ml_check_element_availability api is failed, bool value b_isAvailable is false\\n", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_pipeline_ml_check_nnfw_availability_full_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Checks the availability of the given execution environments with custom option.
* @scenario				Checks the availability of the given execution environments with custom option.
* @apicovered			ml_check_nnfw_availability_full
* @passcase				When ml_check_nnfw_availability_full and Precondition API is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Checks the availability of the given execution environments with custom option.
//& type: auto
int ITc_nnstreamer_pipeline_ml_check_nnfw_availability_full_p (void)
{
	START_TEST;
	bool bIsAvail;
	ml_nnfw_type_e eNnfwType = ML_NNFW_TYPE_NNFW;
	ml_nnfw_hw_e eNnfwHW = ML_NNFW_HW_ANY;

	int nRet = ml_check_nnfw_availability_full(eNnfwType, eNnfwHW, NULL, &bIsAvail);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_check_nnfw_availability_full", NnStreamerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
