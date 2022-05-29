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
static ml_pipeline_valve_h valve1;

/**
 * @function		utc_nnstreamer_pipeline_valve_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_valve_startup(void)
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

  pipeline = g_strdup ("videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=16,height=16,framerate=10/1 ! tensor_converter ! queue ! valve name=valve1");
  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
}

/**
 * @function		utc_nnstreamer_pipeline_valve_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_valve_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
  status = ml_pipeline_destroy (handle);
  g_free (pipeline);
}

/**
 * @testcase		utc_ml_pipeline_valve_get_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get valve handle
 */
int utc_ml_pipeline_valve_get_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_get_handle (handle, "valve1", &valve1);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_valve_get_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline get valve handle, Failure case
 */
int utc_ml_pipeline_valve_get_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_get_handle (NULL, "valve1", &valve1);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_valve_release_handle_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release valve handle
 */
int utc_ml_pipeline_valve_release_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_get_handle (handle, "valve1", &valve1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_set_open (valve1, true); /* close */
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_release_handle (valve1); /* release valve handle */
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_valve_release_handle_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline release valve handle, Failure case
 */
int utc_ml_pipeline_valve_release_handle_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_release_handle (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_pipeline_valve_set_open_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline set valve open
 */
int utc_ml_pipeline_valve_set_open_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_get_handle (handle, "valve1", &valve1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_set_open (valve1, false); /* close */
  assert_eq (status, ML_ERROR_NONE);
  return 0;
}

/**
 * @testcase		utc_ml_pipeline_valve_set_open_n
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline set valve open, Failure case
 */
int utc_ml_pipeline_valve_set_open_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_pipeline_valve_set_open (NULL, true);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}
