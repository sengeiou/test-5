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

#include "utc-nnstreamer-common.h"

static ml_single_h single;
static gchar *test_model;
static int status;

const gchar *model_file = "mobilenet_v1_1.0_224_quant.tflite";

/**
 * @function		utc_nnstreamer_single_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nnstreamer_single_startup(void)
{
	int ret = system_info_get_platform_bool(FEATURE_ML, &feature_ml);
  if (ret != SYSTEM_INFO_ERROR_NONE || !feature_ml) {
    FPRINTF("[%s][%d][%s] feature machine_learning is not supported!\\n", __FILE__, __LINE__, __FUNCTION__);
    return;
  }
	ret = system_info_get_platform_bool(FEATURE_ML_INFERENCE, &feature_ml_inf);
  if (ret != SYSTEM_INFO_ERROR_NONE || !feature_ml_inf) {
    FPRINTF("[%s][%d][%s] feature machine_learning.inference is not supported!\\n", __FILE__, __LINE__, __FUNCTION__);
    return;
  }

  test_model = NULL;

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
}

/**
 * @function		utc_nnstreamer_single_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nnstreamer_single_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }

  g_free (test_model);
}

/**
 * @testcase		utc_ml_single_open_p
 * @since_tizen		5.5
 * @description		Test NNStreamer single open
 */
int utc_ml_single_open_p (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_open_n
 * @since_tizen		5.5
 * @description		Test NNStreamer single open, failure case
 */
int utc_ml_single_open_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_single_open (&single, "wrong_file_name", NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_TYPE_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_single_close_p
 * @since_tizen		5.5
 * @description		Test NNStreamer single close
 */
int utc_ml_single_close_p (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_close_n
 * @since_tizen		5.5
 * @description		Test NNStreamer single close, failure case
 */
int utc_ml_single_close_n (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_single_open_p
 * @since_tizen		5.5
 * @description		Test NNStreamer invoke model
 */
int utc_ml_single_invoke_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h input, output;
  ml_tensor_dimension in_dim, out_dim;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  in_dim[0] = 3;
  in_dim[1] = 224;
  in_dim[2] = 224;
  in_dim[3] = 1;
  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, in_dim);

  out_dim[0] = 1001;
  out_dim[1] = 1;
  out_dim[2] = 1;
  out_dim[3] = 1;
  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (out_info, 0, out_dim);

  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  input = output = NULL;

  /* generate dummy data */
  status = ml_tensors_data_create (in_info, &input);
  assert_eq (status, ML_ERROR_NONE);
  assert (input != NULL);

  status = ml_single_invoke (single, input, &output);
  assert_eq (status, ML_ERROR_NONE);
  assert (output != NULL);

  ml_tensors_data_destroy (output);
  ml_tensors_data_destroy (input);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_ml_single_invoke_n
 * @since_tizen		5.5
 * @description		Test NNStreamer invoke model, failure case
 */
int utc_ml_single_invoke_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_data_h input, output;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  input = output = NULL;
  status = ml_single_invoke (single, input, &output);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_input_info_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get input tensor's info
 */
int utc_ml_single_get_input_info_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h ts_info;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  ml_tensors_info_create (&ts_info);

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  /* input tensor in filter */
  status = ml_single_get_input_info (single, &ts_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_input_info_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get input tensor's info, failure case
 */
int utc_ml_single_get_input_info_n (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  /* input tensor in filter */
  status = ml_single_get_input_info (single, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_output_info_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get output tensor's info
 */
int utc_ml_single_get_output_info_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h ts_info;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  ml_tensors_info_create (&ts_info);

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  /* input tensor in filter */
  status = ml_single_get_output_info (single, &ts_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (ts_info);
  status = ml_single_close (single);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_output_info_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get output tensor's info, failure case
 */
int utc_ml_single_get_output_info_n (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  /* input tensor in filter */
  status = ml_single_get_output_info (single, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_timeout_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set timeout test
 */
int utc_ml_single_set_timeout_p (void)
{
  IS_SUPPORT_FEATURE;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_set_timeout (single, 5);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_timeout_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set timeout test, Failure case
 */
int utc_ml_single_set_timeout_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_single_set_timeout (NULL, 5);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_input_info_p
 * @since_tizen		6.0
 * @description		Test setting input info after model loaded
 */
int utc_ml_single_set_input_info_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  ml_tensors_info_h in_info;
  ml_tensor_dimension res_dim;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_set_input_info_p");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_input_info (single, &in_info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_get_tensor_dimension (in_info, 0, res_dim);
  /* dim change */
  res_dim[3] += 1;
  status = ml_tensors_info_set_tensor_dimension (in_info, 0, res_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_set_input_info (single, in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);
  ml_tensors_info_destroy (in_info);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_input_info_n
 * @since_tizen		6.0
 * @description		Test setting input info after model loaded. Failure Case.
 */
int utc_ml_single_set_input_info_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  ml_tensors_info_h in_info;
  ml_tensor_type_e type = ML_TENSOR_TYPE_UNKNOWN;
  unsigned int count = 0;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_set_input_info_n");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_input_info (single, &in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (in_info, &count);
  assert_eq (status, ML_ERROR_NONE);

  /** changing the count of number of tensors is not allowed */
  ml_tensors_info_set_count (in_info, count + 1);
  status = ml_single_set_input_info (single, in_info);
  assert_neq (status, ML_ERROR_NONE);
  ml_tensors_info_set_count (in_info, count);

  status = ml_tensors_info_get_tensor_type (in_info, 0, &type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_TENSOR_TYPE_FLOAT32);

  /** changing the type of input tensors is not allowed */
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_INT32);
  status = ml_single_set_input_info (single, in_info);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);
  ml_tensors_info_destroy (in_info);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_property_p
 * @since_tizen		6.0
 * @description		Test setting property after model loaded
 */
int utc_ml_single_set_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_set_property_p");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_set_property (single, "input", "5:1:1:1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_set_property_n
 * @since_tizen		6.0
 * @description		Test setting property after model loaded. Failure case.
 */
int utc_ml_single_set_property_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_set_property_n");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_set_property (single, "input", NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_property_p
 * @since_tizen		6.0
 * @description		Test getting property after model loaded
 */
int utc_ml_single_get_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  char *prop_value;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_get_property_p");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_set_property (single, "input", "5:1:1:1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_property (single, "input", &prop_value);
  assert_eq (status, ML_ERROR_NONE);

  assert_eq (g_strcmp0 (prop_value, "5:1:1:1"), 0);
  g_free (prop_value);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_get_property_n
 * @since_tizen		6.0
 * @description		Test getting property after model loaded. Failure case.
 */
int utc_ml_single_get_property_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  char *prop_value;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_get_property_p");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_property (single, "unknown_prop", &prop_value);
  assert_eq (status, ML_ERROR_NOT_SUPPORTED);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_invoke_dynamic_p
 * @since_tizen		6.0
 * @description		Test Run model with dynamic property/setting info.
 */
int utc_ml_single_invoke_dynamic_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  int status;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h input, output;


  int tmp_count;
  ml_tensor_type_e tmp_type = ML_TENSOR_TYPE_UNKNOWN;
  ml_tensor_dimension tmp_dim;


  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_invoke_dynamic_p");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_input_info (single, &in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_create (in_info, &input);
  assert_eq (status, ML_ERROR_NONE);

  float tmp_input[] = {1.0};
  float * output_buf;
  size_t data_size;
  status = ml_tensors_data_set_tensor_data(input, 0, tmp_input,
      1 * sizeof(float));

  ml_tensors_info_get_count(in_info, &tmp_count);
  ml_tensors_info_get_tensor_type(in_info, 0, &tmp_type);
  ml_tensors_info_get_tensor_dimension(in_info, 0, tmp_dim);

  status = ml_single_invoke_dynamic (single, input, in_info, &output, &out_info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_data_get_tensor_data(output, 0, (void **) &output_buf,
      &data_size);

  ml_tensors_info_get_count(out_info, &tmp_count);
  ml_tensors_info_get_tensor_type(out_info, 0, &tmp_type);
  ml_tensors_info_get_tensor_dimension(out_info, 0, tmp_dim);

  ml_tensors_data_destroy (output);
  ml_tensors_data_destroy (input);
  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  status = ml_single_set_property (single, "input", "5:1:1:1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_input_info (single, &in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_create (in_info, &input);
  assert_eq (status, ML_ERROR_NONE);

  float tmp_input2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
  float * output_buf2;
  status = ml_tensors_data_set_tensor_data(input, 0, tmp_input2,
      5 * sizeof(float));

  ml_tensors_info_get_count(in_info, &tmp_count);
  ml_tensors_info_get_tensor_type(in_info, 0, &tmp_type);
  ml_tensors_info_get_tensor_dimension(in_info, 0, tmp_dim);

  status = ml_single_invoke_dynamic (single, input, in_info, &output, &out_info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_data_get_tensor_data(output, 0, (void **) &output_buf2,
      &data_size);

  ml_tensors_info_get_count(out_info, &tmp_count);
  ml_tensors_info_get_tensor_type(out_info, 0, &tmp_type);
  ml_tensors_info_get_tensor_dimension(out_info, 0, tmp_dim);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_data_destroy (output);
  ml_tensors_data_destroy (input);
  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_invoke_dynamic_n
 * @since_tizen		6.0
 * @description		Test Run model with dynamic property/setting info. Failure Case
 */
int utc_ml_single_invoke_dynamic_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  int status;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h input, output;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "add.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_ml_single_invoke_dynamic_n");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_get_input_info (single, &in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_create (in_info, &input);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_invoke_dynamic (single, NULL, in_info, &output, &out_info);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_invoke_dynamic (single, input, NULL, &output, &out_info);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_invoke_dynamic (single, input, in_info, NULL, &out_info);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_invoke_dynamic (single, input, in_info, &output, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_data_destroy (input);
  ml_tensors_info_destroy (in_info);

  g_free (test_model);

  return 0;
}

/**
 * @testcase		utc_ml_single_open_full_p
 * @since_tizen		6.5
 * @description		Test NNStreamer single open with cusotom options
 */
int utc_ml_single_open_full_p (void)
{
  IS_SUPPORT_FEATURE;
  const char * custom_option = "NumThreads:2";
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open_full (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY, custom_option);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_single_open_full_n
 * @since_tizen		6.5
 * @description		Test NNStreamer single open with cusotom options, failure case
 */
int utc_ml_single_open_full_n (void)
{
  IS_SUPPORT_FEATURE;
  const char * custom_option = "NumThreads:2";
  status = ml_single_open_full (&single, "wrong_file_name", NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_TYPE_ANY, custom_option);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_single_invoke_fast_p
 * @since_tizen		6.5
 * @description		Test NNStreamer invoke model with preallocated output
 */
int utc_ml_single_invoke_fast_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h input, output;
  ml_tensor_dimension in_dim, out_dim;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  in_dim[0] = 3;
  in_dim[1] = 224;
  in_dim[2] = 224;
  in_dim[3] = 1;
  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, in_dim);

  out_dim[0] = 1001;
  out_dim[1] = 1;
  out_dim[2] = 1;
  out_dim[3] = 1;
  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (out_info, 0, out_dim);

  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  input = output = NULL;

  /* generate dummy data */
  status = ml_tensors_data_create (in_info, &input);
  assert_eq (status, ML_ERROR_NONE);
  assert (input != NULL);

  status = ml_tensors_data_create (out_info, &output);
  assert_eq (status, ML_ERROR_NONE);
  assert (output != NULL);

  status = ml_single_invoke_fast (single, input, output);
  assert_eq (status, ML_ERROR_NONE);
  assert (output != NULL);

  ml_tensors_data_destroy (output);
  ml_tensors_data_destroy (input);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_ml_single_invoke_fast_n
 * @since_tizen		6.5
 * @description		Test NNStreamer invoke model with preallocated output, failure case
 */
int utc_ml_single_invoke_fast_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_data_h input, output;

  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  status = ml_single_open (&single, test_model, NULL, NULL,
     ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  input = output = NULL;
  status = ml_single_invoke_fast (single, input, &output);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}
