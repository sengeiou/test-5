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

static int status;

static ml_pipeline_h handle;
static ml_pipeline_src_h srchandle;

static ml_tensors_data_h data;
static ml_tensors_info_h info;

static gchar * pipeline;

/**
 * @function		utc_nnstreamer_pipeline_src_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_src_startup(void)
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

  pipeline = g_strdup ("appsrc name=srcx ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  status = ml_pipeline_start (handle);
}

/**
 * @function		utc_nnstreamer_pipeline_src_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_src_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
  status = ml_pipeline_stop (handle);
  status = ml_pipeline_destroy (handle);

  g_free (pipeline);
}

/**
 * @testcase		utc_ml_pipeline_src_get_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get handle of src
 */
int utc_ml_pipeline_src_get_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_get_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get handle of src, Failure case
 */
int utc_ml_pipeline_src_get_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_handle (NULL, "dummy", &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_release_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release handle of src
 */
int utc_ml_pipeline_src_release_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_release_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release handle of src, Failure case
 */
int utc_ml_pipeline_src_release_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_release_handle (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_input_data_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get input data
 */
int utc_ml_pipeline_src_input_data_p (void)
{
  int i, ret = 0;
  uint8_t *uintarray1[10];
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_create (info, &data);
  assert_eq (status, ML_ERROR_NONE);

  for (i = 0; i < 10; i++) {
    uintarray1[i] = (uint8_t *) g_malloc (4);
    uintarray1[i][0] = i + 4;
    uintarray1[i][1] = i + 1;
    uintarray1[i][2] = i + 3;
    uintarray1[i][3] = i + 2;
  }

  status = ml_tensors_data_set_tensor_data (data, 0, uintarray1[0], 4);
  if (status != ML_ERROR_NONE){
    ret = 1;
    goto error_return;
  }

  status = ml_pipeline_src_input_data (srchandle, data, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
  if (status != ML_ERROR_NONE){
    ret = 1;
    goto error_return;
  }

  status = ml_pipeline_src_release_handle (srchandle);
  if (status != ML_ERROR_NONE){
    ret = 1;
    goto error_return;
  }

error_return:
  for (i = 0; i < 10; i++) {
    g_free (uintarray1[i]);
  }
  status = ml_tensors_data_destroy (data);
  assert_eq (status, ML_ERROR_NONE);

  return ret;
}

/**
 * @testcase		utc_ml_pipeline_src_input_data_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get input data, Failure case
 */
int utc_ml_pipeline_src_input_data_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_input_data (srchandle, NULL, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_get_tensors_info_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get tensor info
 */
int utc_ml_pipeline_src_get_tensors_info_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_get_tensors_info_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get tensor info, Failure case
 */
int utc_ml_pipeline_src_get_tensors_info_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_src_get_tensors_info (NULL, &info);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/* @function		test_src_cb_push_dummy
 * @description Internal function to push dummy into appsrc.
 */

static void
test_src_cb_push_dummy (ml_pipeline_src_h src_handle)
{
  ml_tensors_data_h data;
  ml_tensors_info_h info;

  if (ml_pipeline_src_get_tensors_info (src_handle, &info) == ML_ERROR_NONE) {
    ml_tensors_data_create (info, &data);
    ml_pipeline_src_input_data (src_handle, data, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
    ml_tensors_info_destroy (info);
  }
}


/* @function		test_src_cb_need_data
 * @description A appsrc callback for src handle in a pipeline
 */
static void
test_src_cb_need_data (ml_pipeline_src_h src_handle, unsigned int length,
    void *user_data)
{
  test_src_cb_push_dummy (src_handle);
}

/**
 * @testcase		utc_ml_pipeline_src_set_event_cb_p
 * @since_tizen		6.5
 * @description		Test NNStreamer pipeline set src callback
 */
int utc_ml_pipeline_src_set_event_cb_p (void)
{
  IS_SUPPORT_FEATURE;

  ml_pipeline_sink_h sinkhandle;
  ml_pipeline_src_callbacks_s callback = { 0, };
  guint *count_sink;

  callback.need_data = test_src_cb_need_data;

  count_sink = (guint *) g_malloc0 (sizeof (guint));
  assert_neq (count_sink, NULL);

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_set_event_cb (srchandle, &callback, NULL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (
    handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  test_src_cb_push_dummy (srchandle);
  g_usleep (100000);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert_gt (*count_sink, 1U);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (count_sink);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_set_event_cb_n1
 * @since_tizen		6.5
 * @description		Test NNStreamer pipeline set src callback with invalid param
 */
int utc_ml_pipeline_src_set_event_cb_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_src_callbacks_s callback;

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param */
  status = ml_pipeline_src_set_event_cb (NULL, &callback, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_src_set_event_cb_n2
 * @since_tizen		6.5
 * @description		Test NNStreamer pipeline set src callback with invalid param
 */
int utc_ml_pipeline_src_set_event_cb_n2 (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param */
  status = ml_pipeline_src_set_event_cb (srchandle, NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}
