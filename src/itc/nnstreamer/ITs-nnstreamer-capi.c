//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
bool g_bCustomCallbackHit;
//& set: nnstreamer

/**
 * @function		MlCustomEasyInvokeCallback
 * @description		Invoke callback for custom-easy filter.
 */
static int MlCustomEasyInvokeCallback (const ml_tensors_data_h in, ml_tensors_data_h out, void *user_data)
{
	if (user_data) {
		void *raw_data = NULL;
		size_t *data_size = (size_t *) user_data;

		ml_tensors_data_get_tensor_data (out, 0, &raw_data, data_size);
	}
	g_bCallbackHit = true;

	return 0;
}

/**
 * @function		MlPipelineSinkCallbackTensor
 * @description A tensor-sink callback for sink handle in a pipeline
 */
static void MlPipelineSinkCallbackTensor(const ml_tensors_data_h data, const ml_tensors_info_h info, void *user_data)
{
	FPRINTF("[%s:%d] MlPipelineSinkCallbackTensor callback hit\\n", __FILE__, __LINE__);
	guint *count = (guint *) user_data;

	*count = *count + 1;
	g_bCallbackHit = true;
}

/**
 * @function		TestIfCustomCallback
 * @description		Invoke callback for tensor_if custom condition.
 */
static int TestIfCustomCallback (const ml_tensors_data_h data, const ml_tensors_info_h info, int *result, void *user_data)
{
	FPRINTF("[%s:%d] TestIfCustomCallback callback hit\\n", __FILE__, __LINE__);
	void *data_ptr;
	guint sum = 0, i;
	size_t data_size;

	int nRet = ml_tensors_data_get_tensor_data (data, 0, &data_ptr, &data_size);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_get_tensor_data", NnStreamerGetError(nRet));

	for (i = 0; i < data_size; i++)
		sum += ((guint8 *) data_ptr)[i];

	/* Sum value 30 means that the sixth buffer has arrived.*/
	if (sum >= 30)
		*result = 0;
	else
		*result = 1;
	g_bCustomCallbackHit = true;
	return 0;
}

/**
* @function 		ITs_nnstreamer_capi_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_capi_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_pipeline_capi_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
	g_bNnstreamerCreation = false;
	g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLInterference = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_INTERFACE, API_NAMESPACE);
	g_bFeatureIsSupported = g_bFeatureML  && g_bFeatureMLInterference;

	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";

	ml_pipeline_h hMlPipeline = NULL;
	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
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

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return;
}

/**
* @function 		ITs_nnstreamer_capi_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_capi_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_pipeline_capi_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
}


/** @addtogroup itc-nnstreamer-testcases
*  @brief 		Integration testcases for module nnstreamer
*  @ingroup 	itc-nnstreamer
*  @{
*/


/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_get_release_handle_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets an element handle in NNStreamer pipelines to control its properties and releases the given element handle.
* @scenario				Gets an element handle in NNStreamer pipelines to control its properties. Releases the given element handle.
* @apicovered			ml_pipeline_element_get_handle, ml_pipeline_element_release_handle
* @passcase				When ml_pipeline_element_get_handle, ml_pipeline_element_release_handle is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Get and Release ml pipeline handle
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_get_release_handle_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVsrc  = NULL;
	const char *pszElementName = "vsrc";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVsrc, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_release_handle (hMlVsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet), ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_bool_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the boolean value of element's property in NNStreamer pipelines.
* @scenario				Sets the boolean value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_bool, ml_pipeline_element_get_property_bool
* @passcase				When ml_pipeline_element_set_property_bool, ml_pipeline_element_get_property_bool is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get boolean value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_bool_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlSelector  = NULL;
	int nSetProperty = FALSE;
	int nGetProperty;
	const char *pszElementName = "is01";
	const char *pszPropertyName = "sync-streams";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlSelector);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlSelector, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_bool(hMlSelector, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));

	nRet = ml_pipeline_element_get_property_bool (hMlSelector, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));

	nSetProperty = TRUE;
	nRet = ml_pipeline_element_set_property_bool(hMlSelector, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));

	nRet = ml_pipeline_element_get_property_bool (hMlSelector, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_bool", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlSelector));

	nRet = ml_pipeline_element_release_handle (hMlSelector);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_string_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the string value of element's property in NNStreamer pipelines.
* @scenario				Sets the string value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_string, ml_pipeline_element_get_property_string
* @passcase				When ml_pipeline_element_set_property_string, ml_pipeline_element_get_property_string is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get string value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_string_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc is-live=true ! videoconvert ! videoscale ! " \
	"video/x-raw,width=640,height=480,framerate=30/1 ! tensor_converter ! " \
	"tensor_rate name=trate framerate=45/1 throttle=false ! tensor_sink";


	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlRate  = NULL;
	const char *pszElementName = "trate";
	const char *pszPropertyName = "framerate";
	const char *pszSetProperty = "60/1";
	char *pszGetProperty = NULL;

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlRate);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlRate, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_string (hMlRate, pszPropertyName, pszSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_string", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlRate));

	nRet = ml_pipeline_element_get_property_string (hMlRate, pszPropertyName, &pszGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_string", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlRate));
	if ( 0 != strncmp(pszSetProperty, pszGetProperty, strlen(pszSetProperty)) )
	{
		FPRINTF("[%s:%d] TC Failed Reason; Set Value %s and Get value %s of property name is not same\\n", __FILE__, __LINE__, pszSetProperty, pszGetProperty);
		nRet = ml_pipeline_element_release_handle (hMlRate);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

		nRet = ml_pipeline_destroy (hMlPipeline);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

		return 1;
	}

	nRet = ml_pipeline_element_release_handle (hMlRate);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_int32_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the integer value of element's property in NNStreamer pipelines.
* @scenario				Sets the integer value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_int32, ml_pipeline_element_get_property_int32
* @passcase				When ml_pipeline_element_set_property_int32, ml_pipeline_element_get_property_int32 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get integer value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_int32_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVsrc  = NULL;
	int32_t nSetProperty = 10;
	int32_t nGetProperty;
	const char *pszElementName = "vsrc";
	const char *pszPropertyName = "kx";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVsrc, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_int32(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_int32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_int32 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_int32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_int32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nSetProperty = -1234;
	nRet = ml_pipeline_element_set_property_int32(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_int32", NnStreamerGetError(nRet), ml_pipeline_destroy(hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_int32 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_int32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_int32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_release_handle (hMlVsrc);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_int64_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the integer 64bit value of element's property in NNStreamer pipelines.
* @scenario				Sets the integer 64bit value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_int64, ml_pipeline_element_get_property_int64
* @passcase				When ml_pipeline_element_set_property_int64, ml_pipeline_element_get_property_int64 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get integer 64bit value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_int64_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVsrc  = NULL;
	int64_t nSetProperty = 1234567891234LL;
	int64_t nGetProperty;
	const char *pszElementName = "vsrc";
	const char *pszPropertyName = "timestamp-offset";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVsrc, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_int64(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_int64 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nSetProperty = 10LL;
	nRet = ml_pipeline_element_set_property_int64(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_int64 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_int64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_release_handle (hMlVsrc);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_uint32_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the unsigned integer value of element's property in NNStreamer pipelines.
* @scenario				Sets the unsigned integer value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_uint32, ml_pipeline_element_get_property_uint32
* @passcase				When ml_pipeline_element_set_property_uint32, ml_pipeline_element_get_property_uint32 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get unsigned integer value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_uint32_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVsrc  = NULL;
	uint32_t nSetProperty = 123456U;
	uint32_t nGetProperty;
	const char *pszElementName = "vsrc";
	const char *pszPropertyName = "foreground-color";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVsrc, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_uint32(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_uint32 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nSetProperty = 4294967295U;
	nRet = ml_pipeline_element_set_property_uint32(hMlVsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_get_property_uint32 (hMlVsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_uint32", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVsrc));

	nRet = ml_pipeline_element_release_handle (hMlVsrc);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_uint64_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and  Gets the unsigned integer 64bit value of element's property in NNStreamer pipelines.
* @scenario				Sets the unsigned integer 64bit value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_uint64, ml_pipeline_element_get_property_uint64
* @passcase				When ml_pipeline_element_set_property_uint64, ml_pipeline_element_get_property_uint64 is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get unsigned integer 64bit value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_uint64_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlUsrc  = NULL;
	uint64_t nSetProperty = 123456789123456789ULL;
	uint64_t nGetProperty;
	const char *pszElementName = "usrc";
	const char *pszPropertyName = "timeout";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlUsrc);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlUsrc, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_uint64(hMlUsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));

	nRet = ml_pipeline_element_get_property_uint64 (hMlUsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));

	nSetProperty = 987654321ULL;
	nRet = ml_pipeline_element_set_property_uint64(hMlUsrc, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));

	nRet = ml_pipeline_element_get_property_uint64 (hMlUsrc, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_uint64", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlUsrc));

	nRet = ml_pipeline_element_release_handle (hMlUsrc);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_double_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the floating point value of element's property in NNStreamer pipelines.
* @scenario				Sets the floating point value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_double, ml_pipeline_element_get_property_double
* @passcase				When ml_pipeline_element_set_property_double, ml_pipeline_element_get_property_double is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get floating point value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_double_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVscale  = NULL;
	double nSetProperty = 0.72;
	double nGetProperty;
	const char *pszElementName = "vscale";
	const char *pszPropertyName = "sharpness";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVscale);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVscale, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_double(hMlVscale, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_double", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_get_property_double (hMlVscale, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_double", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_double", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nSetProperty = 1.43;
	nRet = ml_pipeline_element_set_property_double(hMlVscale, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_double", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_get_property_double (hMlVscale, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_double", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_double", NnStreamerGetError(nRet), ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_release_handle (hMlVscale);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_element_set_get_property_enum_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and Gets the enumeration value of element's property in NNStreamer pipelines.
* @scenario				Sets the enumeration value of element's property in NNStreamer pipelines, get it and compare the values.
* @apicovered			ml_pipeline_element_set_property_enum, ml_pipeline_element_get_property_enum
* @passcase				When ml_pipeline_element_set_property_enum, ml_pipeline_element_get_property_enum is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for Set and Get enumeration value of element's property in NNStreamer pipelines.
//& type: auto
int ITc_nnstreamer_ml_pipeline_element_set_get_property_enum_p(void)
{
	START_TEST;
	int nRet = -1;
	char *pszPipeLine = "videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
	"video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
	"valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx";
	ml_pipeline_h hMlPipeline = NULL;
	ml_pipeline_element_h hMlVscale  = NULL;
	uint32_t nSetProperty = 3U;
	uint32_t nGetProperty;
	const char *pszElementName = "vscale";
	const char *pszPropertyName = "method";

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet));
	CHECK_HANDLE(hMlPipeline, "ml_pipeline_construct");

	nRet = ml_pipeline_element_get_handle (hMlPipeline, pszElementName, &hMlVscale);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_handle", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hMlVscale, "ml_pipeline_element_get_handle", ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_element_set_property_enum(hMlVscale, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_get_property_enum (hMlVscale, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nSetProperty = 5U;
	nRet = ml_pipeline_element_set_property_enum(hMlVscale, pszPropertyName, nSetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_set_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_get_property_enum (hMlVscale, pszPropertyName, &nGetProperty);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_element_get_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));
	PRINT_RESULT_CLEANUP(nSetProperty, nGetProperty, "ml_pipeline_element_get_property_enum", NnStreamerGetError(nRet),ml_pipeline_destroy (hMlPipeline); ml_pipeline_element_release_handle (hMlVscale));

	nRet = ml_pipeline_element_release_handle (hMlVscale);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_element_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_custom_easy_filter_register_unregister_p
* @since_tizen			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Registers a custom filter and unregisters it.
* @scenario				Registers and unregisters a custom filter.
* @apicovered			ml_pipeline_custom_easy_filter_register, ml_pipeline_custom_easy_filter_unregister
* @passcase				When ml_pipeline_custom_easy_filter_register, ml_pipeline_custom_easy_filter_unregister is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to register and unregister a custom filter
//& type: auto
int ITc_nnstreamer_ml_pipeline_custom_easy_filter_register_unregister_p(void)
{
	START_TEST;
	int nRet = -1;
	int nTimeoutId = 0;
	const char pszTestCustomFilter[] = "test-custom-filter";
	char *pszPipeLine = g_strdup_printf
	("appsrc name=srcx ! other/tensor,dimension=(string)2:1:1:1,type=(string)int8,framerate=(fraction)0/1 ! " \
	"tensor_filter framework=custom-easy model=%s ! tensor_sink name=sinkx",
	pszTestCustomFilter);

	ml_pipeline_h hMlPipeline = NULL;
	ml_custom_easy_filter_h hCustom;
	ml_pipeline_src_h hPipeSrcHandle;
	ml_tensors_data_h hTensorsDataHandle;
	ml_tensor_dimension inputTensorDimension = { 2, 1, 1, 1 };
	size_t *filter_data_size = (size_t *) g_malloc0 (sizeof (size_t));

	guint nSt = 0, nEnd = 5;
	gulong nTime = 50000;

	ml_tensors_info_h hTensorinfoInHandle = NULL;
	nRet = ml_tensors_info_create (&hTensorinfoInHandle);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet));
	CHECK_HANDLE(hTensorinfoInHandle, "ml_tensors_info_create");

	nRet = ml_tensors_info_set_count (hTensorinfoInHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle));

	nRet = ml_tensors_info_set_tensor_type (hTensorinfoInHandle, 0, ML_TENSOR_TYPE_INT8);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hTensorinfoInHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle));

	ml_tensors_info_h hTensorinfoOutHandle = NULL;
	nRet = ml_tensors_info_create (&hTensorinfoOutHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_create", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle));
	CHECK_HANDLE_CLEANUP(hTensorinfoOutHandle, "ml_tensors_info_create", ml_tensors_info_destroy (hTensorinfoInHandle));

	nRet = ml_tensors_info_set_count (hTensorinfoOutHandle, 1);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_count", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));

	nRet = ml_tensors_info_set_tensor_type (hTensorinfoOutHandle, 0, ML_TENSOR_TYPE_FLOAT32);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_type", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));

	nRet = ml_tensors_info_set_tensor_dimension (hTensorinfoOutHandle, 0, inputTensorDimension);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_set_tensor_dimension", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));

	g_bCallbackHit = false;
	nRet = ml_pipeline_custom_easy_filter_register (pszTestCustomFilter, hTensorinfoInHandle, hTensorinfoOutHandle, MlCustomEasyInvokeCallback, filter_data_size, &hCustom);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_custom_easy_filter_register", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));

	nRet = ml_pipeline_construct (pszPipeLine, NULL, NULL, &hMlPipeline);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));
	CHECK_HANDLE_CLEANUP(hMlPipeline, "ml_pipeline_construct", ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle));

	nRet = ml_pipeline_src_get_handle (hMlPipeline, "srcx", &hPipeSrcHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline));
	CHECK_HANDLE_CLEANUP(hPipeSrcHandle, "ml_pipeline_src_get_handle", ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline));

	nRet = ml_pipeline_start (hMlPipeline);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle));

	for (nSt = 0; nSt < nEnd; nSt++) {
		nRet = ml_tensors_data_create (hTensorinfoInHandle, &hTensorsDataHandle);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet));
		CHECK_HANDLE_CLEANUP(hTensorsDataHandle, "ML_ERROR_NONE", ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle));

		nRet = ml_pipeline_src_input_data (hPipeSrcHandle, hTensorsDataHandle, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_input_data", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle); ml_tensors_data_destroy(hTensorsDataHandle) );

		g_usleep (nTime);
	}
	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "ml_pipeline_custom_easy_filter_register", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle); ml_tensors_data_destroy(hTensorsDataHandle));

	nRet = ml_pipeline_stop (hMlPipeline);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle); ml_tensors_data_destroy(hTensorsDataHandle));

	nRet = ml_pipeline_src_release_handle (hPipeSrcHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_src_release_handle", NnStreamerGetError(nRet));

	nRet = ml_pipeline_destroy (hMlPipeline);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet));

	nRet = ml_pipeline_custom_easy_filter_unregister (hCustom);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_custom_easy_filter_unregister", NnStreamerGetError(nRet), ml_tensors_info_destroy (hTensorinfoInHandle); ml_tensors_info_destroy (hTensorinfoOutHandle); ml_pipeline_destroy (hMlPipeline); ml_pipeline_src_release_handle (hPipeSrcHandle); ml_tensors_data_destroy(hTensorsDataHandle));

	nRet = ml_tensors_info_destroy (hTensorinfoInHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	nRet = ml_tensors_info_destroy (hTensorinfoOutHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));

	g_free (filter_data_size);

	return 0;
}

/**
* @testcase 			ITc_nnstreamer_ml_pipeline_tensor_if_custom_register_unregister_p
* @since_tizen			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(j.abhishek)
* @type 				auto
* @description			Registers a tensor custom condition and unregisters it.
* @scenario				Registers a tensor custom condition and unregisters it.
* @apicovered			ml_pipeline_tensor_if_custom_register, ml_pipeline_tensor_if_custom_unregister
* @passcase				When ml_pipeline_tensor_if_custom_register, ml_pipeline_tensor_if_custom_unregister is successful.
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Registers a tensor custom condition and unregisters it.
//& type: auto
int ITc_nnstreamer_ml_pipeline_tensor_if_custom_register_unregister_p(void)
{
	START_TEST;
	int nRet = -1,nTimeoutId = 0;
	const gchar *psz_tmpdir = g_get_tmp_dir ();
	const gchar *psz_dirname = "nns-tizen-XXXXXX";
	gchar *psz_fullpath = g_build_path ("/", psz_tmpdir, psz_dirname, NULL);
	gchar *pszdir = g_mkdtemp ((gchar *)psz_fullpath);
	gchar *psz_file = g_build_path ("/", pszdir, "output", NULL);
	ml_pipeline_h hPipelinehandle;
	ml_pipeline_src_h hPipeSrcHandle;
	ml_pipeline_sink_h hPipeSinkHandle;
	ml_pipeline_if_h hCustom;
	ml_tensors_info_h hTensorinfo;
	ml_tensors_data_h hTensorData;
	unsigned int nGetCount = 0;
	ml_tensor_type_e eTensorType = ML_TENSOR_TYPE_UNKNOWN;
	uint8_t *nUIntArray[LIMIT];
	uint8_t *nContent = NULL;
	guint i;
	gsize nLength;

	gchar *pszNnpipeline = g_strdup_printf (PIPELINE_STREAM, psz_file);
	guint *unsinkCount = (guint *)g_malloc0 (sizeof (guint));
	CHECK_HANDLE(unsinkCount, "unsinkCount");
	*unsinkCount = 0;

	g_bCustomCallbackHit = false;
	nRet = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", TestIfCustomCallback, NULL, &hCustom);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_tensor_if_custom_register", NnStreamerGetError(nRet), FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	CHECK_HANDLE_CLEANUP(hPipeSinkHandle, "ml_pipeline_tensor_if_custom_register",  FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_construct (pszNnpipeline, NULL, NULL, &hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_construct", NnStreamerGetError(nRet), FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	CHECK_HANDLE_CLEANUP(hPipeSinkHandle, "ml_pipeline_construct",  FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	g_bCallbackHit = false;
	nRet = ml_pipeline_sink_register (hPipelinehandle, "sink_false", MlPipelineSinkCallbackTensor, unsinkCount, &hPipeSinkHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_sink_register", NnStreamerGetError(nRet), ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	CHECK_HANDLE_CLEANUP(hPipeSinkHandle, "ml_pipeline_sink_register",  ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_src_get_handle (hPipelinehandle, "appsrc", &hPipeSrcHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_handle", NnStreamerGetError(nRet),ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	CHECK_HANDLE_CLEANUP(hPipeSrcHandle, "ml_pipeline_src_get_handle",  ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_start (hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_start", NnStreamerGetError(nRet),ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	RUN_POLLING_LOOP;
	for (i = 0; i < LIMIT; i++) {
		nUIntArray[i] = (uint8_t *)g_malloc (4);
		CHECK_HANDLE(nUIntArray[i], "nUIntArray[i]");
		nUIntArray[i][0] = i + 4;
		nUIntArray[i][1] = i + 1;
		nUIntArray[i][2] = i + 3;
		nUIntArray[i][3] = i + 2;
	  }

	nRet = ml_pipeline_src_get_tensors_info (hPipeSrcHandle, &hTensorinfo);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_get_tensors_info", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	CHECK_HANDLE_CLEANUP(hTensorinfo, "ml_pipeline_src_get_tensors_info",ml_pipeline_stop (hPipelinehandle); ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_tensors_info_get_count (hTensorinfo, &nGetCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	if (nGetCount != 1U)
	{
		FPRINTF("[%s:%d] ml_tensors_info_get_count value mismatch for nGetCount,nGetCount returned = (%d)\\n", __FILE__, __LINE__,nGetCount);
		TensorInfoPipelineStop(hPipelinehandle,hPipeSrcHandle,hPipeSinkHandle,hTensorinfo);
		FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
		return 1;
	}

	nRet = ml_tensors_info_get_tensor_type (hTensorinfo, 0, &eTensorType);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_tensor_type", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	if (eTensorType != ML_TENSOR_TYPE_UINT8)
	{
		FPRINTF("[%s:%d] ml_tensors_info_get_count value mismatch for nGetCount,nGetCount returned = (%d)\\n", __FILE__, __LINE__,nGetCount);
		TensorInfoPipelineStop(hPipelinehandle,hPipeSrcHandle,hPipeSinkHandle,hTensorinfo);
		FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
		return 1;
	}

	nRet = ml_tensors_data_create (hTensorinfo, &hTensorData);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_create", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	/* Set tensor data and push buffers to source pad */
	for (i = 0; i < LIMIT; i++) {
		nRet = ml_tensors_data_set_tensor_data (hTensorData, 0, nUIntArray[i], 4);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_data_set_tensor_data", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

		nRet = ml_pipeline_src_input_data (hPipeSrcHandle, hTensorData, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_input_data", NnStreamerGetError(nRet),ml_pipeline_stop (hPipelinehandle);ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

		g_usleep (50000); /* 50ms. Wait a bit. */
	}
	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "ml_pipeline_custom_easy_filter_register", NnStreamerGetError(nRet), ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	PRINT_RESULT_CLEANUP(true, g_bCustomCallbackHit, "ml_pipeline_tensor_if_custom_register", NnStreamerGetError(nRet), ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_stop (hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet),ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));
	PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "ml_pipeline_stop", NnStreamerGetError(nRet), ml_pipeline_src_release_handle (hPipeSrcHandle);ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_src_release_handle (hPipeSrcHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_src_release_handle", NnStreamerGetError(nRet),ml_pipeline_sink_unregister (hPipeSinkHandle); ml_pipeline_destroy (hPipelinehandle); ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_sink_unregister (hPipeSinkHandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_sink_unregister", NnStreamerGetError(nRet), ml_pipeline_destroy (hPipelinehandle);ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_destroy (hPipelinehandle);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_destroy", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	nRet = ml_pipeline_tensor_if_custom_unregister (hCustom);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_pipeline_tensor_if_custom_unregister", NnStreamerGetError(nRet),ml_tensors_info_destroy (hTensorinfo);ml_tensors_data_destroy (hTensorData);FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file));

	if( (g_file_get_contents (psz_file, (gchar **)&nContent, &nLength, NULL) != TRUE))
	{
		FPRINTF("[%s:%d] g_file_get_contents returned false\\n", __FILE__, __LINE__);
		TensorInfoDataDestroy(hTensorinfo,hTensorData);
		FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
		return 1;
	}
	if( nLength != (4U * 5))
	{
		FPRINTF("[%s:%d] g_file_get_contents value mismatch for nLength,nLength returned = (%d)\\n", __FILE__, __LINE__,nLength);
		TensorInfoDataDestroy(hTensorinfo,hTensorData);
		FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
		return 1;
	}
	CHECK_HANDLE(nContent, "nContent");

	/* Check if the TRUE path data is received correctly.  */
	if (nContent && nLength == 20) {
		for (i = 0; i < 5; i++) {
			if( nContent[i * 4 + 0] !=  i + 4)
			{
				FPRINTF("[%s:%d] nContent[i * 4 + 0] value mismatch\\n", __FILE__, __LINE__);
				g_free (nContent);
				TensorInfoDataDestroy(hTensorinfo,hTensorData);
				FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
				return 1;
			}
			if( nContent[i * 4 + 1] != i + 1)
			{
				FPRINTF("[%s:%d] nContent[i * 4 + 1] value mismatch\\n", __FILE__, __LINE__);
				g_free (nContent);
				TensorInfoDataDestroy(hTensorinfo,hTensorData);
				FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
				return 1;
			}
			if( nContent[i * 4 + 2] != i + 3)
			{
				FPRINTF("[%s:%d] nContent[i * 4 + 2] value mismatch\\n", __FILE__, __LINE__);
				g_free (nContent);
				TensorInfoDataDestroy(hTensorinfo,hTensorData);
				FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
				return 1;
			}
			if( nContent[i * 4 + 3] != i + 2)
			{
				FPRINTF("[%s:%d] nContent[i * 4 + 3] value mismatch\\n", __FILE__, __LINE__);
				g_free (nContent);
				TensorInfoDataDestroy(hTensorinfo,hTensorData);
				FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
				return 1;
			}
		}
	  }
	g_free (nContent);

	  /* The FALSE path receives 5 buffers. */
	if( *unsinkCount != 5U)
	{
		FPRINTF("[%s:%d] value mismatch for unsinkCount,unsinkCount returned = (%d)\\n", __FILE__, __LINE__,unsinkCount);
		TensorInfoDataDestroy(hTensorinfo,hTensorData);
		FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);
		return 1;
	}

	for (i = 0; i < LIMIT; i++) {
		g_free (nUIntArray[i]);
	}
	TensorInfoDataDestroy(hTensorinfo,hTensorData);
	FreeCustomTensorMemory(&pszNnpipeline,&unsinkCount,&psz_fullpath,&psz_file);

	  return 0;
}

/** @} */
/** @} */
