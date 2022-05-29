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
static ml_pipeline_h handle;
static ml_pipeline_sink_h sinkhandle;
static TestPipeState * pipe_state;

/**
 * @function		utc_nnstreamer_pipeline_sink_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_sink_startup(void)
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

  /* pipeline with appsink */
  pipeline = g_strdup ("videotestsrc num-buffers=3 ! videoconvert ! tensor_converter ! appsink name=sinkx");

  count_sink = (guint *) g_malloc (sizeof (guint));
  *count_sink = 0;

  pipe_state = (TestPipeState *) g_new0 (TestPipeState, 1);
  status = ml_pipeline_construct (pipeline, test_pipe_state_callback, pipe_state, &handle);
}

/**
 * @function		utc_nnstreamer_pipeline_sink_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_sink_cleanup(void)
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
 * @testcase		utc_ml_pipeline_sink_register_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline register sink
 */
int utc_ml_pipeline_sink_register_p (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_sink_register_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline register sink, Failure case
 */
int utc_ml_pipeline_sink_register_n (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_sink_register (NULL, "sinkx", test_sink_callback_count, NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_sink_unregister_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline unregister sink
 */
int utc_ml_pipeline_sink_unregister_p (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_sink_unregister_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline register sink, Failure case
 */
int utc_ml_pipeline_sink_unregister_n (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_sink_unregister (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}
