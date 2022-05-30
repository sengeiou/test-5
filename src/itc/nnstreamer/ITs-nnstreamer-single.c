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


static ml_single_h g_SingleHandle;
static gchar *MlTestModel;

const gchar *tensorFlowModelFileName = "mobilenet_v1_1.0_224_quant.tflite";

/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

//& set: nnstreamer


/**
* @function 		ITs_nnstreamer_tensors_single_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_tensors_single_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_tensors_startup\\n", __LINE__, API_NAMESPACE);
#endif

	MlTestModel = NULL;
  	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;

	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		int model_path_len = strlen(pszValue) + strlen(tensorFlowModelFileName) + 10;
		MlTestModel = (gchar*)malloc(model_path_len);
		snprintf(MlTestModel, model_path_len, "%s/res/res/%s", pszValue, tensorFlowModelFileName);
		FPRINTF("[%s][%d][%s] %s\\n", __FILE__, __LINE__, __FUNCTION__, MlTestModel);
	}
	else
	{
		FPRINTF("[%s][%d][%s] ERROR TO GET MODEL PATH\\n", __FILE__, __LINE__, __FUNCTION__);
	}
	nRet = ml_single_open (&g_SingleHandle, MlTestModel, NULL, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_single_open failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_single_open failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_single_open is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_single_open is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_single_openfailed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] mml_single_open failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNnstreamerCreation = false;
	}
	else
	{
		g_bNnstreamerCreation = true;
	}

}


/**
* @function 		ITs_nnstreamer_single_tensors_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_tensors_single_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_single_tensors_cleanup\\n", __LINE__, API_NAMESPACE);
#endif


	if(g_SingleHandle)
	{
		ml_single_close (g_SingleHandle);
		g_SingleHandle = NULL;
	}
	 g_free (MlTestModel);

}

/*
* @testcase 			ITc_nnstreamer_single_ml_single_open_close_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Open and Close ML single
* @scenario			Open and Close ML single
* @apicovered		ml_single_open, ml_single_close
* @passcase			When ml_single_open, ml_single_close is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Open and Close ML single
//& type: auto
int ITc_nnstreamer_single_ml_single_open_close_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_single_h hSingleHandle = NULL;

	nRet = ml_single_open (&hSingleHandle, MlTestModel, NULL, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet));
	CHECK_HANDLE(hSingleHandle, "ml_single_open");

	nRet = ml_single_close (hSingleHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_set_timeout_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To Set ML single timeout value
* @scenario			To Set ML single timeout value
* @apicovered			ml_single_set_timeout
* @passcase			When ml_single_set_timeout and precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Set ML single timeout value
//& type: auto
int ITc_nnstreamer_single_ml_set_timeout_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_single_h hSingleHandle = NULL;

	nRet = ml_single_open (&hSingleHandle, MlTestModel, NULL, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet));
	CHECK_HANDLE(hSingleHandle, "ml_single_open");

	nRet = ml_single_set_timeout(hSingleHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_set_timeout", NnStreamerGetError(nRet),ml_single_close (hSingleHandle));

	nRet = ml_single_close (hSingleHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_single_invoke_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Invoke ML single
* @scenario			Invoke ML single
* @apicovered			ml_single_invoke
* @passcase			When ml_single_invoke and precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Invoke ML single
//& type: auto
int ITc_nnstreamer_single_ml_single_invoke_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	ml_tensors_info_h hInputTensorsInfoHandle = NULL;
	ml_tensors_info_h hOutputTensorsInfoHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension outputTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 224;
	inputTensorDimension[2] = 224;
	inputTensorDimension[3] = 1;
	outputTensorDimension[0] = 1001;
	outputTensorDimension[1] = 1;
	outputTensorDimension[2] = 1;
	outputTensorDimension[3] = 1;

	ml_tensors_data_h hInputDataHandle = NULL;
	ml_tensors_data_h hOutputDataHandle = NULL;

	nRet = ml_tensors_info_create (&hInputTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hInputTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hInputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hInputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hInputTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_create (&hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_tensors_info_create", ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_count (hOutputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hOutputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hOutputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_open (&hSingleHandle, MlTestModel, hInputTensorsInfoHandle, hOutputTensorsInfoHandle, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hInputTensorsInfoHandle, "ml_single_open",ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_data_create (hInputTensorsInfoHandle, &hInputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hInputDataHandle, "ml_tensors_data_create",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	/* to prevent timeout with low performance */
	ml_single_set_timeout (hSingleHandle, 20000);

	nRet = ml_single_invoke (hSingleHandle, hInputDataHandle, &hOutputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_invoke", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle);ml_tensors_data_destroy (hInputDataHandle));
	CHECK_HANDLE_CLEANUP(hOutputDataHandle, "ml_single_invoke",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle);ml_tensors_data_destroy (hInputDataHandle));

	nRet = ml_single_close (hSingleHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle);ml_tensors_data_destroy (hInputDataHandle);ml_tensors_data_destroy (hOutputDataHandle));

	nRet = ml_tensors_data_destroy (hInputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_destroy (hOutputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_get_set_input_info_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Get and Set tensor input info from ml single
* @scenario			Get and Set tensor input info from ml single and set it back
* @apicovered			ml_single_set_input_info, ml_single_get_input_info
* @passcase			When ml_single_set_input_info, ml_single_get_input_info and precondition APIs are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Get and Set tensor input info from ml single
//& type: auto
int ITc_nnstreamer_single_ml_get_set_input_info_p(void)
{
	START_TEST;

	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	ml_tensors_info_h hInputTensorsInfoHandle = NULL;
	ml_tensors_info_h hOutputTensorsInfoHandle = NULL;
	ml_tensors_info_h hGetInputTensorsInfoHandle = NULL;

	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension outputTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 224;
	inputTensorDimension[2] = 224;
	inputTensorDimension[3] = 1;
	outputTensorDimension[0] = 1001;
	outputTensorDimension[1] = 1;
	outputTensorDimension[2] = 1;
	outputTensorDimension[3] = 1;

	nRet = ml_tensors_info_create (&hInputTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hInputTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hInputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hInputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hInputTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_create (&hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_tensors_info_create", ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_count (hOutputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hOutputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hOutputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_open (&hSingleHandle, MlTestModel, hInputTensorsInfoHandle, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hSingleHandle, "ml_single_open",ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	//Target API
	nRet = ml_single_get_input_info (hSingleHandle, &hGetInputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_get_input_info", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hGetInputTensorsInfoHandle, "ml_single_get_input_info",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_get_tensor_dimension (hGetInputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimensions", NnStreamerGetError(nRet), ml_single_close(hSingleHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_info_destroy(hGetInputTensorsInfoHandle));

	/* Dimension change */
	outputTensorDimension[3] += 1;
	nRet = ml_tensors_info_set_tensor_dimension(hGetInputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_single_close(hSingleHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_info_destroy(hGetInputTensorsInfoHandle));

	//Target API
	nRet = ml_single_set_input_info(hSingleHandle, hGetInputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_set_input_info", NnStreamerGetError(nRet), ml_single_close(hSingleHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_info_destroy(hGetInputTensorsInfoHandle));

	nRet = ml_single_close(hSingleHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_destroy (hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hGetInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_get_output_info_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Get tensor output info from ml single
* @scenario			Get tensor output info from ml single
* @apicovered			ml_single_get_output_info
* @passcase			When ml_single_get_output_info and precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Get tensor output info from ml single
//& type: auto
int ITc_nnstreamer_single_ml_get_output_info_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	ml_tensors_info_h hInputTensorsInfoHandle = NULL;
	ml_tensors_info_h hOutputTensorsInfoHandle = NULL;
	ml_tensors_info_h hGetOutputTensorsInfoHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension outputTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 224;
	inputTensorDimension[2] = 224;
	inputTensorDimension[3] = 1;
	outputTensorDimension[0] = 1001;
	outputTensorDimension[1] = 1;
	outputTensorDimension[2] = 1;
	outputTensorDimension[3] = 1;

	nRet = ml_tensors_info_create (&hInputTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hInputTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hInputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hInputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hInputTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_create (&hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_tensors_info_create", ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_count (hOutputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hOutputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hOutputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_open (&hSingleHandle, MlTestModel, hInputTensorsInfoHandle, hOutputTensorsInfoHandle, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hSingleHandle, "ml_single_open",ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_get_output_info (hSingleHandle, &hGetOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_get_output_info", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hGetOutputTensorsInfoHandle, "ml_single_get_output_info",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_close (hSingleHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_destroy (hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_set_get_property_p
* @since_tizen			6.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To Set and Get ML single property value
* @scenario			To Set and Get ML single property value
* @apicovered			ml_single_set_property, ml_single_get_property
* @passcase			When ml_single_set_property, ml_single_get_property and precondition APIs are successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To Set and Get ML single property value
//& type: auto
int ITc_nnstreamer_single_ml_set_get_property_p(void)
{
	START_TEST;

	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	const char *pszPropertyName = "input";
	const char *pszSetProperty = "3:224:224:1";
	char *pszGetProperty = NULL;

	nRet = ml_single_open(&hSingleHandle, MlTestModel, NULL, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet));
	CHECK_HANDLE(hSingleHandle, "ml_single_open");

	//Target API
	nRet = ml_single_set_property(hSingleHandle, pszPropertyName, pszSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_set_property", NnStreamerGetError(nRet), ml_single_close(hSingleHandle));

	//Target API
	nRet = ml_single_get_property(hSingleHandle, pszPropertyName, &pszGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_get_property", NnStreamerGetError(nRet), ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(pszGetProperty, "ml_single_get_property", ml_single_close(hSingleHandle));

	if ( 0 != strncmp(pszSetProperty, pszGetProperty, strlen(pszSetProperty)) )
	{
		FPRINTF("[%s:%d] TC Failed Reason; Set Value %s and Get value %s of tensor property name is not same\\n", __FILE__, __LINE__, pszSetProperty, pszGetProperty);
		nRet = ml_single_close(hSingleHandle);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));
		return 1;
	}

	nRet = ml_single_close(hSingleHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_invoke_dynamic_p
* @since_tizen			6.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To Invokes the model with the given input data with the given tensors information.
* @scenario			To Invokes the model with the given input data with the given tensors information.
* @apicovered			ml_single_invoke_dynamic
* @passcase			When ml_single_invoke_dynamic and precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Invokes the model with the given input data with the given tensors information.
//& type: auto
int ITc_nnstreamer_single_ml_invoke_dynamic_p(void)
{
	START_TEST;

	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	ml_tensors_info_h hInputTensorsInfoHandle = NULL;
	ml_tensors_info_h hOutputTensorsInfoHandle = NULL;
	ml_tensors_data_h hInputDataHandle = NULL;
	ml_tensors_data_h hOutputDataHandle = NULL;

	ml_tensor_type_e eTensorType = ML_TENSOR_TYPE_UNKNOWN;
	ml_tensor_dimension nTmpTensorDimension;

	const char *pszPropertyName = "input";
	const char *pszSetProperty = "3:224:224:1";
	float fTmpInputArr[] = {1.0};
	unsigned int nTmpCnt = 0;
	float *fOutBuf;
	size_t nDataSize;

	nRet = ml_single_open(&hSingleHandle, MlTestModel, NULL, NULL, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet));
	CHECK_HANDLE(hSingleHandle, "ml_single_open");

	nRet = ml_single_get_input_info(hSingleHandle, &hInputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_get_input_info", NnStreamerGetError(nRet), ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hInputTensorsInfoHandle, "ml_single_get_input_info", ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_create(hInputTensorsInfoHandle, &hInputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet), ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hInputDataHandle, "ml_tensors_data_create", ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_set_tensor_data(hInputDataHandle, 0, fTmpInputArr, 1 * sizeof(float));
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_set_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_count(hInputTensorsInfoHandle, &nTmpCnt);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_type(hInputTensorsInfoHandle, 0, &eTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_dimension(hInputTensorsInfoHandle, 0, nTmpTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	//Target API
	nRet = ml_single_invoke_dynamic(hSingleHandle, hInputDataHandle, hInputTensorsInfoHandle, &hOutputDataHandle, &hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_invoke_dynamic", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hOutputDataHandle, "ml_single_invoke_dynamic", ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_single_invoke_dynamic", ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_get_tensor_data(hOutputDataHandle, 0, (void **)&fOutBuf, &nDataSize);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_get_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_count(hOutputTensorsInfoHandle, &nTmpCnt);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_type(hOutputTensorsInfoHandle, 0, &eTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_dimension(hOutputTensorsInfoHandle, 0, nTmpTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_destroy(hInputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_destroy(hOutputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy(hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy(hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_single_set_property(hSingleHandle, pszPropertyName, pszSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_set_property", NnStreamerGetError(nRet), ml_single_close(hSingleHandle));

	nRet = ml_single_get_input_info(hSingleHandle, &hInputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_get_input_info", NnStreamerGetError(nRet), ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hInputTensorsInfoHandle, "ml_single_get_input_info", ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_create(hInputTensorsInfoHandle, &hInputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet), ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hInputDataHandle, "ml_tensors_data_create", ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	float fTmpInput2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float *fOutBuf2;

	nRet = ml_tensors_data_set_tensor_data(hInputDataHandle, 0, fTmpInput2, 5 * sizeof(float));
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_set_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_count(hInputTensorsInfoHandle, &nTmpCnt);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_type(hInputTensorsInfoHandle, 0, &eTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_dimension(hInputTensorsInfoHandle, 0, nTmpTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	//Target API
	nRet = ml_single_invoke_dynamic(hSingleHandle, hInputDataHandle, hInputTensorsInfoHandle, &hOutputDataHandle, &hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_invoke_dynamic", NnStreamerGetError(nRet), ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hOutputDataHandle, "ml_single_invoke_dynamic", ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_single_invoke_dynamic", ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_data_get_tensor_data(hOutputDataHandle, 0, (void **) &fOutBuf2, &nDataSize);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_get_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_count(hOutputTensorsInfoHandle, &nTmpCnt);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_type(hOutputTensorsInfoHandle, 0, &eTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_tensors_info_get_tensor_dimension(hOutputTensorsInfoHandle, 0, nTmpTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_data_destroy(hOutputDataHandle); ml_tensors_info_destroy(hOutputTensorsInfoHandle); ml_tensors_data_destroy(hInputDataHandle); ml_tensors_info_destroy(hInputTensorsInfoHandle); ml_single_close(hSingleHandle));

	nRet = ml_single_close(hSingleHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_destroy(hInputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_destroy(hOutputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy(hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroyv", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy(hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

  return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_single_open_full_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(j.abhishek)
* @type 				auto
* @description			To check NNStreamer single open with cusotom options
* @scenario				To check NNStreamer single open with cusotom options
* @apicovered			ml_single_open_full
* @passcase				When ml_single_open_full and precondition API is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: To check NNStreamer single open with cusotom options
//& type: auto
int ITc_nnstreamer_single_ml_single_open_full_p(void)
{
	START_TEST;
	const char * pszCutomOpt = "NumThreads:2";
	int nRet = -1;
	ml_single_h hSingleHandle = NULL;

	nRet = ml_single_open_full(&hSingleHandle, MlTestModel, NULL, NULL,ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY, pszCutomOpt);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_single_open_full", NnStreamerGetError(nRet));
	CHECK_HANDLE(hSingleHandle, "ml_single_open_full");

	nRet = ml_single_close(hSingleHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_single_ml_single_invoke_fast_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(j.abhishek)
* @type 				auto
* @description			To check NNStreamer invoke model with preallocated output
* @scenario				To check NNStreamer invoke model with preallocated output
* @apicovered			ml_single_invoke_fast
* @passcase				When ml_single_invoke_fast and precondition API is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: To check NNStreamer invoke model with preallocated output
//& type: auto
int ITc_nnstreamer_single_ml_single_invoke_fast_p (void)
{
	START_TEST;

	int nRet = -1;
	ml_single_h hSingleHandle = NULL;
	ml_tensors_info_h hInputTensorsInfoHandle = NULL;
	ml_tensors_info_h hOutputTensorsInfoHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension outputTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 224;
	inputTensorDimension[2] = 224;
	inputTensorDimension[3] = 1;
	outputTensorDimension[0] = 1001;
	outputTensorDimension[1] = 1;
	outputTensorDimension[2] = 1;
	outputTensorDimension[3] = 1;

	ml_tensors_data_h hInputDataHandle = NULL;
	ml_tensors_data_h hOutputDataHandle = NULL;

	nRet = ml_tensors_info_create (&hInputTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hInputTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hInputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hInputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hInputTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_create (&hOutputTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputTensorsInfoHandle, "ml_tensors_info_create", ml_tensors_info_destroy (hInputTensorsInfoHandle));

	nRet = ml_tensors_info_set_count (hOutputTensorsInfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hOutputTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hOutputTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_open (&hSingleHandle, MlTestModel, hInputTensorsInfoHandle, hOutputTensorsInfoHandle, ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_open", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hInputTensorsInfoHandle, "ml_single_open",ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	/* generate dummy data */
	nRet = ml_tensors_data_create (hInputTensorsInfoHandle, &hInputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hInputDataHandle, "ml_tensors_data_create",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_data_create (hOutputTensorsInfoHandle, &hOutputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputDataHandle, "ml_tensors_data_create",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_single_invoke_fast (hSingleHandle, hInputDataHandle, hOutputDataHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_invoke_fast", NnStreamerGetError(nRet),ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hOutputDataHandle, "ml_single_invoke_fast",ml_single_close (hSingleHandle);ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle));

	nRet = ml_tensors_data_destroy (hInputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_destroy (hOutputDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));

	nRet = ml_single_close (hSingleHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_single_close", NnStreamerGetError(nRet),ml_tensors_info_destroy (hInputTensorsInfoHandle);ml_tensors_info_destroy (hOutputTensorsInfoHandle);ml_tensors_data_destroy (hInputDataHandle);ml_tensors_data_destroy (hOutputDataHandle));


	nRet = ml_tensors_info_destroy (hInputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hOutputTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}
