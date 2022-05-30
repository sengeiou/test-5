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

#include <string.h>

#include "utc-nnstreamer-common.h"
#include <ml-api-service.h>

#define IS_SUPPORT_ML_SERVICE_FEATURE \
do { \
  if (!feature_ml || !feature_ml_service) { \
    FPRINTF("[%s][%d][%s] Machine Learning feature is not supported!\\n", __FILE__, __LINE__, __FUNCTION__); \
    return 0; \
  } \
} while (0)

static int status;
static gchar *test_model;
static gchar *pipeline;

/**
 * @function		utc_machine_learning_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_machine_learning_service_startup (void)
{
  const gchar *model_file = "mobilenet_v1_1.0_224_quant.tflite";

	int ret = system_info_get_platform_bool(FEATURE_ML, &feature_ml);
  if (ret != SYSTEM_INFO_ERROR_NONE || !feature_ml) {
    FPRINTF("[%s][%d][%s] feature machine_learning is not supported!\\n", __FILE__, __LINE__, __FUNCTION__);
    return;
  }
	ret = system_info_get_platform_bool(FEATURE_ML_SERVICE, &feature_ml_service);
  if (ret != SYSTEM_INFO_ERROR_NONE || !feature_ml_service) {
    FPRINTF("[%s][%d][%s] feature machine_learning.service is not supported!\\n", __FILE__, __LINE__, __FUNCTION__);
    return;
  }

  FPRINTF("[%s][%d][%s] [STARTUP]\\n", __FILE__, __LINE__, __FUNCTION__);
  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    test_model = (gchar*)malloc(model_path_len);
    snprintf(test_model, model_path_len, "%s/res/res/%s", pszValue, model_file);
    FPRINTF("[%s][%d][%s] %s\\n", __FILE__, __LINE__, __FUNCTION__, test_model);
  }
  else
  {
    FPRINTF("[%s][%d][%s] ERROR TO GET MODEL PATH\\n", __FILE__, __LINE__, __FUNCTION__);
  }

  pipeline = g_strdup_printf ("appsrc name=appsrc ! "
      "other/tensors,num-tensors=1,dimensions=(string)1:1:1:1,types=(string)float32,framerate=(fraction)0/1,format=static ! "
      "tensor_filter name=filter_h framework=tensorflow-lite model=%s ! tensor_sink name=tensor_sink",
      test_model);
}

/**
 * @function		utc_machine_learning_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_machine_learning_service_cleanup (void)
{
  if (!feature_ml || !feature_ml_service) {
    return;
  }
  g_free (pipeline);
  g_free (test_model);
}

/**
 * @testcase		utc_ml_service_set_pipeline_p1
 * @since_tizen		7.0
 * @description		Positive test case to set pipeline description.
 */
int utc_ml_service_set_pipeline_p1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";

  /* Test */
  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_set_pipeline_p2
 * @since_tizen		7.0
 * @description		Positive test case to update pipeline description.
 */
int utc_ml_service_set_pipeline_p2 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  gchar *pipeline2, *ret_pipeline;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, &ret_pipeline);
  assert_eq (ML_ERROR_NONE, status);
  assert (0 == strcmp (pipeline, ret_pipeline));
  g_free (ret_pipeline);

  pipeline2 =
      g_strdup_printf
      ("v4l2src ! videoconvert ! videoscale ! video/x-raw,format=RGB,width=640,height=480,framerate=5/1 ! "
      "mqttsink pub-topic=example/objectDetection");
  status = ml_service_set_pipeline (key, pipeline2);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, &ret_pipeline);
  assert_eq (ML_ERROR_NONE, status);
  assert (0 == strcmp (pipeline2, ret_pipeline));

  g_free (pipeline2);
  g_free (ret_pipeline);

  return 0;
}

/**
 * @testcase		utc_ml_service_set_pipeline_n1
 * @since_tizen		7.0
 * @description		Negative test case to set pipeline description with invalid param.
 */
int utc_ml_service_set_pipeline_n1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, NULL);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_set_pipeline_n2
 * @since_tizen		7.0
 * @description		Negative test case to set pipeline description with invalid param.
 */
int utc_ml_service_set_pipeline_n2 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;

  status = ml_service_set_pipeline (NULL, pipeline);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_set_pipeline_p1
 * @since_tizen		7.0
 * @description		Positive test case to get pipeline description.
 */
int utc_ml_service_get_pipeline_p1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  gchar *ret_pipeline;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, &ret_pipeline);
  assert_eq (ML_ERROR_NONE, status);
  assert (0 == strcmp (pipeline, ret_pipeline));

  g_free (ret_pipeline);

  return 0;
}

/**
 * @testcase		utc_ml_service_get_pipeline_n1
 * @since_tizen		7.0
 * @description		Negative test case to get pipeline description with invalid param.
 */
int utc_ml_service_get_pipeline_n1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  gchar *ret_pipeline;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (NULL, &ret_pipeline);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_get_pipeline_n2
 * @since_tizen		7.0
 * @description		Negative test case to get pipeline description with invalid param.
 */
int utc_ml_service_get_pipeline_n2 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, NULL);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_delete_pipeline_p1
 * @since_tizen		7.0
 * @description		Positive test case to delete pipeline description.
 */
int utc_ml_service_delete_pipeline_p1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  gchar *ret_pipeline;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, &ret_pipeline);
  assert_eq (ML_ERROR_NONE, status);
  assert (0 == strcmp (pipeline, ret_pipeline));

  status = ml_service_delete_pipeline (key);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_get_pipeline (key, &ret_pipeline);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  g_free (ret_pipeline);

  return 0;
}

/**
 * @testcase		utc_ml_service_delete_pipeline_n1
 * @since_tizen		7.0
 * @description		Negative test case to delete pipeline description.
 */
int utc_ml_service_delete_pipeline_n1 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_delete_pipeline (NULL);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_delete_pipeline_n2
 * @since_tizen		7.0
 * @description		Negative test case to delete pipeline description.
 */
int utc_ml_service_delete_pipeline_n2 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";
  const gchar *invalid_key = "InvalidServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_delete_pipeline (invalid_key);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}

/**
 * @testcase		utc_ml_service_delete_pipeline_n3
 * @since_tizen		7.0
 * @description		Negative test case to delete pipeline description.
 */
int utc_ml_service_delete_pipeline_n3 (void)
{
  IS_SUPPORT_ML_SERVICE_FEATURE;
  const gchar *key = "ServiceName";

  status = ml_service_set_pipeline (key, pipeline);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_delete_pipeline (key);
  assert_eq (ML_ERROR_NONE, status);

  status = ml_service_delete_pipeline (key);
  assert_eq (ML_ERROR_INVALID_PARAMETER, status);

  return 0;
}
