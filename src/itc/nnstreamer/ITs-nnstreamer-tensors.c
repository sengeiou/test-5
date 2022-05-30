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


static ml_tensors_info_h g_hTensorsInfoHandle;

ml_tensor_type_e g_eMlNnTensorType[] = {
				ML_TENSOR_TYPE_INT32,
				ML_TENSOR_TYPE_UINT32,
  				ML_TENSOR_TYPE_INT16,
  				ML_TENSOR_TYPE_UINT16,
				ML_TENSOR_TYPE_INT8,
				ML_TENSOR_TYPE_UINT8,
  				ML_TENSOR_TYPE_FLOAT64,
  				ML_TENSOR_TYPE_FLOAT32,
  				ML_TENSOR_TYPE_INT64,
  				ML_TENSOR_TYPE_UINT64,
};

/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

//& set: nnstreamer


/**
* @function 		ITs_nnstreamer_tensors_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_tensors_startup(void)
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
	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;
	nRet = ml_tensors_info_create(&g_hTensorsInfoHandle);
	if(!g_bFeatureIsSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_tensors_info_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_tensors_info_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_tensors_info_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_tensors_info_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_tensors_info_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_tensors_info_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNnstreamerCreation = false;
	}
	else
	{
		g_bNnstreamerCreation = true;
	}
	return;
}


/**
* @function 		ITs_nnstreamer_tensors_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_tensors_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_tensors_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hTensorsInfoHandle)
	{
		ml_tensors_info_destroy (g_hTensorsInfoHandle);
	}

}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_create_destroy_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Create and Destroy ml tensors info handle
* @scenario			Create and Destroy ml tensors info handle
* @apicovered			ml_tensors_info_create, ml_tensors_info_destroy
* @passcase			When mml_tensors_info_create, ml_tensors_info_destroy is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Create and Destroy ml tensors info handle
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensors_info_h hTensorsInfoHandle = NULL;

	nRet = ml_tensors_info_create (&hTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_destroy (hTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_clone_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Clone ml tensors info handle
* @scenario			Clone ml tensors info handle
* @apicovered			ml_tensors_info_clone
* @passcase			When ml_tensors_info_clone and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to clone ml tensors info handle
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_clone_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensors_info_h hTensorsInfoHandle = NULL;
	ml_tensors_info_h hCloneTensorsInfoHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension outputTensorDimension;
	ml_tensor_type_e eGetTensorType = -1;
	unsigned int nSetCount = 1;
	unsigned int nGetCount = 0;

	inputTensorDimension[0] = 10;
	inputTensorDimension[1] = 1;
	inputTensorDimension[2] = 1;
	inputTensorDimension[3] = 1;

	nRet = ml_tensors_info_create (&hTensorsInfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorsInfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_create (&hCloneTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorsInfoHandle));
	CHECK_HANDLE_CLEANUP(hCloneTensorsInfoHandle, "ml_tensors_info_create",ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_set_count (hTensorsInfoHandle, nSetCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
    nRet = ml_tensors_info_set_tensor_type (hTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
    nRet = ml_tensors_info_set_tensor_dimension (hTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_clone (hCloneTensorsInfoHandle, hTensorsInfoHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_clone", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_get_count (hCloneTensorsInfoHandle, &nGetCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(nSetCount, nGetCount, "ml_tensors_info_get_count", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_get_tensor_type (hCloneTensorsInfoHandle, 0, &eGetTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(ML_TENSOR_TYPE_UINT8, eGetTensorType, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_get_tensor_dimension (hCloneTensorsInfoHandle, 0, outputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(inputTensorDimension[0], outputTensorDimension[0], "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(inputTensorDimension[1], outputTensorDimension[1], "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(inputTensorDimension[2], outputTensorDimension[2], "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));
	PRINT_RESULT_CLEANUP(inputTensorDimension[3], outputTensorDimension[3], "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet),ml_tensors_info_destroy (hCloneTensorsInfoHandle);ml_tensors_info_destroy (hTensorsInfoHandle));

	nRet = ml_tensors_info_destroy (hCloneTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hTensorsInfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_validate_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To validate ml tensors info handle
* @scenario			To validate ml tensors info handle
* @apicovered			ml_tensors_info_validate
* @passcase			When ml_tensors_info_validate and Precondition API is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for tensors handle validation
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_validate_p(void)
{
	START_TEST;
	int nRet = -1;
	bool isTensorsInfoValid = true;
	ml_tensors_info_h hTensorinfoHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	inputTensorDimension[0] = 10;
	inputTensorDimension[1] = 1;
	inputTensorDimension[2] = 1;
	inputTensorDimension[3] = 1;

	nRet = ml_tensors_info_create (&hTensorinfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hTensorinfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_set_tensor_type (hTensorinfoHandle, 0, ML_TENSOR_TYPE_INT16);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hTensorinfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));


	nRet = ml_tensors_info_validate (hTensorinfoHandle, &isTensorsInfoValid);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_validate", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_destroy (hTensorinfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_set_get_count_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To set and get tensors info count
* @scenario			To set and get tensors info count
* @apicovered			ml_tensors_info_set_count, ml_tensors_info_get_count
* @passcase			When ml_tensors_info_set_count, ml_tensors_info_get_count is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to set and get tensors info count
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_set_get_count_p(void)
{
	START_TEST;
	int nRet = -1;
	unsigned int nSetCount = 2;
	unsigned int nGetCount = 0;

	nRet = ml_tensors_info_set_count (g_hTensorsInfoHandle, nSetCount);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_get_count (g_hTensorsInfoHandle, &nGetCount);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet));
	PRINT_RESULT(nSetCount, nGetCount, "set and get count not same", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_name_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To set and get tensors info name
* @scenario			To set and get tensors info name
* @apicovered			ml_tensors_info_set_tensor_name, ml_tensors_info_get_tensor_name
* @passcase			When ml_tensors_info_set_tensor_name, ml_tensors_info_get_tensor_name is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to set and get tensors info name
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_name_p(void)
{
	START_TEST;
	int nRet = -1;
	gchar * pszGetTensorName = NULL;
	ml_tensors_info_h hTensorinfoHandle = NULL;

	nRet = ml_tensors_info_create (&hTensorinfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hTensorinfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_set_tensor_name (hTensorinfoHandle, 0, "tensor-name-test");
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_name", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet =  ml_tensors_info_get_tensor_name (hTensorinfoHandle, 0, &pszGetTensorName);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_name", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	if(strcmp(pszGetTensorName, "tensor-name-test") != 0)
	{
		FPRINTF("[%s:%d] Set Value  %s and Get value  %sof tensor name is not same\\n", __FILE__, __LINE__, "tensor-name-test", pszGetTensorName);
		nRet = ml_tensors_info_destroy (hTensorinfoHandle);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));
		g_free (pszGetTensorName);
		return 1;
	}

	nRet = ml_tensors_info_destroy (hTensorinfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	g_free (pszGetTensorName);

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_type_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To set and get tensors info type
* @scenario			To set and get tensors info type
* @apicovered			ml_tensors_info_set_tensor_type, ml_tensors_info_get_tensor_type
* @passcase			When ml_tensors_info_set_tensor_type, ml_tensors_info_get_tensor_type is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to set and get tensors info type
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_type_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensor_type_e eGetTensorType = -1;;
	int nEnumCounter = 0;
	int nEnumSize = sizeof(g_eMlNnTensorType) / sizeof(g_eMlNnTensorType[0]);

	ml_tensors_info_h hTensorinfoHandle = NULL;

	nRet = ml_tensors_info_create (&hTensorinfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hTensorinfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	for (nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_tensors_info_set_tensor_type (hTensorinfoHandle, 0, g_eMlNnTensorType[nEnumCounter]);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorinfoHandle));

		nRet =  ml_tensors_info_get_tensor_type (hTensorinfoHandle, 0, &eGetTensorType);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorinfoHandle));

		PRINT_RESULT_CLEANUP(g_eMlNnTensorType[nEnumCounter], eGetTensorType, "set and get type not same", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorinfoHandle));
	}

	nRet = ml_tensors_info_destroy (hTensorinfoHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_dimension_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To set and get tensors info dimension
* @scenario			To set and get tensors info dimension
* @apicovered			ml_tensors_info_set_tensor_dimension, ml_tensors_info_get_tensor_dimension
* @passcase			When ml_tensors_info_set_tensor_dimension, ml_tensors_info_get_tensor_dimension is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to set and get tensors info dimension
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_set_get_tensor_dimension_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensor_dimension inputTensorDimension;
	ml_tensor_dimension OutTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 300;
	inputTensorDimension[2] = 300;
	inputTensorDimension[3] = 1;

	ml_tensors_info_h hTensorinfoHandle = NULL;

	nRet = ml_tensors_info_create (&hTensorinfoHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
  	CHECK_HANDLE(hTensorinfoHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hTensorinfoHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hTensorinfoHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	nRet = ml_tensors_info_get_tensor_dimension (hTensorinfoHandle, 0, OutTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	PRINT_RESULT_CLEANUP(OutTensorDimension[0], 3U, "Set and Get dimesnion are not same", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));
	PRINT_RESULT_CLEANUP(OutTensorDimension[1], 300U, "Set and Get dimesnion are not same", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));
	PRINT_RESULT_CLEANUP(OutTensorDimension[2], 300U, "Set and Get dimesnion are not same", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));
	PRINT_RESULT_CLEANUP(OutTensorDimension[3], 1U, "Set and Get dimesnion are not same", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoHandle));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_info_get_tensor_size_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To get tensors info size
* @scenario			To get tensors info size
* @apicovered			ml_tensors_info_get_tensor_size
* @passcase			When ml_tensors_info_get_tensor_size is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To get tensors info size
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_info_get_tensor_size_p(void)
{
	START_TEST;
	int nRet = -1;
	size_t nTensorSize;
	ml_tensor_dimension inputTensorDimension;
	inputTensorDimension[0] = 3;
	inputTensorDimension[1] = 300;
	inputTensorDimension[2] = 300;
	inputTensorDimension[3] = 1;

	nRet = ml_tensors_info_set_count (g_hTensorsInfoHandle, 1);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_set_tensor_type (g_hTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_set_tensor_dimension (g_hTensorsInfoHandle, 0, inputTensorDimension);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_get_tensor_size(g_hTensorsInfoHandle, 0, &nTensorSize);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_size", NnStreamerGetError(nRet));

	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_data_create_destroy_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To create and destroy tensor data handle
* @scenario			To create and destroy tensor data handle
* @apicovered			ml_tensors_data_create,ml_tensors_data_destroy
* @passcase			When mml_tensors_data_create,ml_tensors_data_destroy is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To create and destroy tensor data handle
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_data_create_destroy_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensors_data_h hTensorsDataHandle = NULL;
	ml_tensor_dimension inputTensorDimension;
	inputTensorDimension[0] = 2;
	inputTensorDimension[1] = 2;
	inputTensorDimension[2] = 2;
	inputTensorDimension[3] = 2;

	ml_tensors_info_set_count (g_hTensorsInfoHandle, 1);
	ml_tensors_info_set_tensor_type (g_hTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	ml_tensors_info_set_tensor_dimension (g_hTensorsInfoHandle, 0, inputTensorDimension);

	nRet = ml_tensors_data_create (g_hTensorsInfoHandle, &hTensorsDataHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorsDataHandle, "ml_tensors_data_create");

	nRet = ml_tensors_data_destroy (hTensorsDataHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));
	return 0;
}

/*
* @testcase 			ITc_nnstreamer_tensors_ml_tensors_data_set_get_tensor_data_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			To Set and Get tensor data
* @scenario			To Set and Get tensor data
* @apicovered			ml_tensors_data_create,ml_tensors_data_destroy
* @passcase			When mml_tensors_data_create,ml_tensors_data_destroy is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API To create and destroy tensor data handle
//& type: auto
int ITc_nnstreamer_tensors_ml_tensors_data_set_get_tensor_data_p(void)
{
	START_TEST;
	int nRet = -1;
	ml_tensors_data_h hTensorsDataHandle = NULL;
	uint8_t uintarray[4] = {1,1,1,1};
	unsigned int i, nCount = 0;
	void *dataPtr = NULL;
	size_t dataSize = 0;
	ml_tensor_dimension inputTensorDimension;
	inputTensorDimension[0] = 2;
	inputTensorDimension[1] = 2;
	inputTensorDimension[2] = 2;
	inputTensorDimension[3] = 2;

	nRet = ml_tensors_info_set_count (g_hTensorsInfoHandle, 1);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_set_tensor_type (g_hTensorsInfoHandle, 0, ML_TENSOR_TYPE_UINT8);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_set_tensor_dimension (g_hTensorsInfoHandle, 0, inputTensorDimension);
        PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet));

	nRet = ml_tensors_data_create (g_hTensorsInfoHandle, &hTensorsDataHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorsDataHandle, "ml_tensors_data_create");

	nRet = ml_tensors_data_set_tensor_data (hTensorsDataHandle, 0, uintarray, 4);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_set_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy (hTensorsDataHandle));

	nRet = ml_tensors_info_get_count (g_hTensorsInfoHandle, &nCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet), ml_tensors_data_destroy (hTensorsDataHandle));

	for (i = 0; i < nCount; i++)
	{
		nRet = ml_tensors_data_get_tensor_data (hTensorsDataHandle, i, &dataPtr, &dataSize);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_get_tensor_data", NnStreamerGetError(nRet), ml_tensors_data_destroy (hTensorsDataHandle));
	}

	nRet = ml_tensors_data_destroy (hTensorsDataHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));
	return 0;
}
