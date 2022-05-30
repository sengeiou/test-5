//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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
#include <ml-api-service.h>

static gchar *g_TestModel;
static gchar *g_Pipeline;

/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

//& set: nnstreamer


/**
* @function 		ITs_nnstreamer_ml_service_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_ml_service_startup(void)
{
	int nRet =-1;
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0)
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nnstreamer_ml_service_startup\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsFeatureMismatched = false;
        g_bFeatureMLService = false;
        g_bFeatureML = TCTCheckSystemInfoFeatureSupported(FEATURE_ML, API_NAMESPACE);
	g_bFeatureMLService = TCTCheckSystemInfoFeatureSupported(FEATURE_ML_SERVICE, API_NAMESPACE);

        if (g_bFeatureML && g_bFeatureMLService)
	{
                char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
                const gchar *model_file = "mobilenet_v1_1.0_224_quant.tflite";
                if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
		{
			int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
			g_TestModel = (gchar*)malloc(model_path_len);
			snprintf(g_TestModel, model_path_len, "%s/res/res/%s", pszValue, model_file);
			FPRINTF("[%s][%d][%s] %s\\n", __FILE__, __LINE__, __FUNCTION__, g_TestModel);
		}
		else
		{
			FPRINTF("[%s][%d][%s] ERROR TO GET MODEL PATH\\n", __FILE__, __LINE__, __FUNCTION__);
		}

		g_Pipeline = g_strdup_printf ("appsrc name=appsrc ! "
		  "other/tensors,num-tensors=1,dimensions=(string)1:1:1:1,types=(string)float32,framerate=(fraction)0/1,format=static ! "
		  "tensor_filter name=filter_h framework=tensorflow-lite model=%s ! tensor_sink name=tensor_sink",
		g_TestModel);
	}
	return;
}


/**
* @function 		ITs_nnstreamer_ml_service_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_nnstreamer_ml_service_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nnstreamer_ml_service_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

    if (g_bFeatureML && g_bFeatureMLService)
    {
	g_free (g_Pipeline);
	g_free (g_TestModel);
    }
}

/*
* @testcase 			ITc_nnstreamer_ml_service_set_get_pipeline_p
* @since_tizen			7.0
* @author            		SRID(shobhit.v)
* @reviewer         		SRID(ankit.sr1)
* @type 			auto
* @description			Set pipeline and get pipeline
* @scenario			Set pipeline and get pipeline
* @apicovered			ml_service_set_pipeline and ml_service_get_pipeline
* @passcase			When ml_service_set_pipeline and ml_service_get_pipeline is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for set and get ml service pipeline
//& type: auto
int ITc_nnstreamer_ml_service_set_get_pipeline_p(void)
{
    START_TEST_ML_SERVICE;

    gchar *pipeline2, *get_pipeline;
    const gchar *key = "ServiceName";
    int nRetVal = -1;

    nRetVal = ml_service_set_pipeline (key, g_Pipeline);
    ML_SERVICE_FEATURE_CHECK;
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_set_pipeline", NnStreamerGetError(nRetVal));

    nRetVal = ml_service_get_pipeline (key, &get_pipeline);
    ML_SERVICE_FEATURE_CHECK;
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_get_pipeline", NnStreamerGetError(nRetVal));
    if (0 != strcmp (g_Pipeline, get_pipeline))
    {
	 FPRINTF("[Line : %d][%s] Set and Get pipeline value mismatch \\n", __LINE__, API_NAMESPACE);
         g_free (get_pipeline);
	 return 1;
    }

    g_free (get_pipeline);

    pipeline2 =
    g_strdup_printf
      ("v4l2src ! videoconvert ! videoscale ! video/x-raw,format=RGB,width=640,height=480,framerate=5/1 ! "
      "mqttsink pub-topic=example/objectDetection");
    nRetVal = ml_service_set_pipeline (key, pipeline2);
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_set_pipeline", NnStreamerGetError(nRetVal));

    nRetVal = ml_service_get_pipeline (key, &get_pipeline);
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_get_pipeline", NnStreamerGetError(nRetVal));
    if (0 != strcmp (pipeline2, get_pipeline))
    {
	 FPRINTF("[Line : %d][%s] Set and Get pipeline value mismatch for second key\\n", __LINE__, API_NAMESPACE);
	 g_free (pipeline2);
         g_free (get_pipeline);
	 return 1;
    }
    g_free (pipeline2);
    g_free (get_pipeline);

    return 0;
}

/*
* @testcase 			ITc_nnstreamer_ml_service_delete_pipeline_p
* @since_tizen			7.0
* @author            		SRID(shobhit.v)
* @reviewer         		SRID(ankit.sr1)
* @type 			auto
* @description			Set pipeline and get pipeline
* @scenario			Set pipeline and get pipeline
* @apicovered			ml_service_set_pipeline, ml_service_get_pipeline and ml_service_delete_pipeline
* @passcase			When ml_service_delete_pipeline is successful.
* @failcase			If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to Check for delete pipeline ml service
//& type: auto
int ITc_nnstreamer_ml_service_delete_pipeline_p(void)
{
    START_TEST_ML_SERVICE;

    gchar *get_pipeline;
    const gchar *key = "ServiceName";
    int nRetVal = -1;

    nRetVal = ml_service_set_pipeline (key, g_Pipeline);
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_set_pipeline", NnStreamerGetError(nRetVal));

    nRetVal = ml_service_get_pipeline (key, &get_pipeline);
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_get_pipeline", NnStreamerGetError(nRetVal));
    if (0 != strcmp (g_Pipeline, get_pipeline))
    {
	 FPRINTF("[Line : %d][%s] Set and Get pipeline value mismatch for second key\\n", __LINE__, API_NAMESPACE);
         g_free (get_pipeline);
	 return 1;
    }

    nRetVal = ml_service_delete_pipeline (key);
    ML_SERVICE_FEATURE_CHECK;
    PRINT_RESULT(ML_ERROR_NONE, nRetVal, "ml_service_delete_pipeline", NnStreamerGetError(nRetVal));

    nRetVal = ml_service_get_pipeline (key, &get_pipeline);
    PRINT_RESULT(ML_ERROR_INVALID_PARAMETER, nRetVal, "ml_service_get_pipeline", NnStreamerGetError(nRetVal));

    g_free (get_pipeline);

    return 0;
}
