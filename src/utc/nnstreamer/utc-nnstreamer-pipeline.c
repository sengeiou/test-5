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
static ml_pipeline_h handle;
static ml_pipeline_state_e state;

/**
 * @function		utc_nnstreamer_pipeline_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_startup(void)
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
}

/**
 * @function		utc_nnstreamer_pipeline_cleanup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
}

/**
 * @testcase		utc_ml_pipeline_construct_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline construct
 */
int utc_ml_pipeline_construct_p (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc num_buffers=2 ! fakesink";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_construct_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline construct, failure case
 */
int utc_ml_pipeline_construct_n (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "nonexistsrc ! fakesink";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_destroy_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline destroy
 */
int utc_ml_pipeline_destroy_p (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc num_buffers=2 ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224 ! tensor_converter ! fakesink";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_destroy_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline destroy, failure case
 */
int utc_ml_pipeline_destroy_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_destroy (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_get_state_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get pipeline state
 */
int utc_ml_pipeline_get_state_p (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_get_state_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get pipeline state, failure case
 */
int utc_ml_pipeline_get_state_n (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_get_state (handle, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_start_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline construct
 */
int utc_ml_pipeline_start_p (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_start_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline construct, failure case
 */
int utc_ml_pipeline_start_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_start (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_stop_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline stop
 */
int utc_ml_pipeline_stop_p (void)
{
  IS_SUPPORT_FEATURE;
  pipeline = "videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx";
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  g_usleep (SLEEP_TIME); /* SLEEP_TIME is good for general systems, but not enough for emulators to start gst pipeline. Let a few frames flow. */
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  wait_for_start (handle, state, status);
  assert_eq (state, ML_PIPELINE_STATE_PLAYING);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */
  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_stop_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline construct, Failure case
 */
int utc_ml_pipeline_stop_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_stop (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_check_nnfw_availability_full_p
 * @since_tizen		6.5
 * @description		Test NNStreamer check nnfw availability with custom option
 */
int utc_ml_check_nnfw_availability_full_p (void)
{
  bool result;
  IS_SUPPORT_FEATURE;

  int status = ml_check_nnfw_availability_full (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_ANY, NULL, &result);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_check_nnfw_availability_full_n
 * @since_tizen		6.5
 * @description		Test NNStreamer check nnfw availability with custom option, Failure case.
 */
int utc_ml_check_nnfw_availability_full_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_check_nnfw_availability_full (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU, NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_check_nnfw_availability_p
 * @since_tizen		5.5
 * @description		Test NNStreamer check nnfw availabiliry
 */
int utc_ml_check_nnfw_availability_p (void)
{
  bool result;
  IS_SUPPORT_FEATURE;

  int status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_ANY, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_AUTO, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_CPU, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_CPU_NEON, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_GPU, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU_MOVIDIUS, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU_EDGE_TPU, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU_VIVANTE, &result);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU_SR, &result);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_check_nnfw_availability_n
 * @since_tizen		5.5
 * @description		Test NNStreamer check nnfw availabiliry, Failure case.
 */
int utc_ml_check_nnfw_availability_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_check_nnfw_availability (ML_NNFW_TYPE_NNFW, ML_NNFW_HW_NPU, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_check_element_availability_p
 * @since_tizen		6.5
 * @description		 Test NNStreamer Utility for checking an element availability.
 */
int utc_ml_check_element_availability_p (void)
{
  IS_SUPPORT_FEATURE;
  bool available;
  int status;

  status = ml_check_element_availability ("tensor_converter", &available);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (available, true);

  status = ml_check_element_availability ("tensor_filter", &available);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (available, true);

  status = ml_check_element_availability ("appsrc", &available);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (available, true);

  return 0;
}

/**
 * @testcase		utc_ml_check_element_availability_n1
 * @since_tizen		6.5
 * @description		 Test NNStreamer Utility for checking an element availability, Failure case.
 */
int utc_ml_check_element_availability_n1 (void)
{
  IS_SUPPORT_FEATURE;
  bool available;
  int status;

  status = ml_check_element_availability (NULL, &available);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_check_element_availability ("tensor_filter", NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_check_element_availability_n2
 * @since_tizen		6.5
 * @description		 Test NNStreamer Utility for checking an element availability, Failure case.
 */
int utc_ml_check_element_availability_n2 (void)
{
  IS_SUPPORT_FEATURE;
  bool available;
  int status;

  status = ml_check_element_availability ("invalid-elem", &available);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (available, false);

  return 0;
}
