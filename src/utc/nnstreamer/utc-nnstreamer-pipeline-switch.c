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
static gchar * pipeline;
static guint * count_sink;
static gchar ** node_list;

static TestPipeState * pipe_state;
static ml_pipeline_h handle;
static ml_pipeline_switch_h switchhandle;
static ml_pipeline_switch_e type;

/**
 * @function		utc_nnstreamer_pipeline_switch_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_switch_startup(void)
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

  node_list = NULL;

  pipeline = g_strdup ("input-selector name=ins ! tensor_converter ! tensor_sink name=sinkx "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_0 "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_1");

  count_sink = (guint *) g_malloc (sizeof (guint));
  *count_sink = 0;

  pipe_state = (TestPipeState *) g_new0 (TestPipeState, 1);
  status = ml_pipeline_construct (pipeline, test_pipe_state_callback, pipe_state, &handle);
}

/**
 * @function		utc_nnstreamer_pipeline_switch_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_switch_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
  status = ml_pipeline_destroy (handle);

  g_free (pipeline);
  g_free (count_sink);
  g_free (pipe_state);
}

/**
 * @testcase		utc_ml_pipeline_switch_get_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get switch handle
 */
int utc_ml_pipeline_switch_get_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_handle (handle, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_INPUT_SELECTOR);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_get_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get switch handle, Failure case
 */
int utc_ml_pipeline_switch_get_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_handle (NULL, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_release_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release switch handle
 */
int utc_ml_pipeline_switch_release_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_handle (handle, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_INPUT_SELECTOR);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_release_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release switch handle, Failure case
 */
int utc_ml_pipeline_switch_release_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_release_handle (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_select_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline select switch
 */
int utc_ml_pipeline_switch_select_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_handle (handle, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_INPUT_SELECTOR);

  status = ml_pipeline_switch_select (switchhandle, "sink_1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_select_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline select switch, Failure case
 */
int utc_ml_pipeline_switch_select_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_select (NULL, "sink_1");
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_get_pad_list_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get pad list
 */
int utc_ml_pipeline_switch_get_pad_list_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_handle (handle, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_INPUT_SELECTOR);

  status = ml_pipeline_switch_get_pad_list (switchhandle, &node_list);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_switch_get_pad_list_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get pad list, Failure case
 */
int utc_ml_pipeline_switch_get_pad_list_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_switch_get_pad_list (NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}
