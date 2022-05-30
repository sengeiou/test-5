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

/**
 * @function		utc_nnstreamer_scenario_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_scenario_startup(void)
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
 * @function		utc_nnstreamer_scenario_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_scenario_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
}

/**
 * @testcase		utc_nnstreamer_scenario_construct_destruct_empty_pipeline_p
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_construct_destruct_empty_pipeline_p (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup ("videotestsrc num_buffers=2 ! fakesink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq(status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq(status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_construct_destruct_pipeline_p1
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_construct_destruct_pipeline_p1 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc num_buffers=2 ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224 ! tensor_converter ! fakesink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_construct_destruct_pipeline_p2
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_construct_destruct_pipeline_p2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc num_buffers=2 ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224 ! tensor_converter ! valve name=valvex ! tensor_sink name=sinkx");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_construct_pipeline_error_case_n1
 * @since_tizen		5.5
 * @description		Negative test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_construct_pipeline_error_case_n1 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("nonexistsrc ! fakesink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_construct_pipeline_error_case_n2
 * @since_tizen		5.5
 * @description		Negative test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_construct_pipeline_error_case_n2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc num_buffers=2 ! audioconvert ! fakesink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_pipeline_state_test_p1
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_pipeline_state_test_p1 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx");
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
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

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_pipeline_state_test_p2
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_pipeline_state_test_p2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! valve name=valvex ! valve name=valvey ! input-selector name=is01 ! tensor_sink name=sinkx");
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
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

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  /* Resume playing */
  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  g_usleep (SLEEP_TIME); /* Enough to empty the queue */
  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_pipeline_state_test_p3
 * @since_tizen		5.5
 * @description		Positive test case of pipeline construct & destruct
 */
int utc_nnstreamer_scenario_pipeline_state_test_p3 (void)
{
  IS_SUPPORT_FEATURE;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *) fullpath);
  gchar *file1 = g_build_path ("/", dir, "valve1", NULL);
  gchar * pipeline =
      g_strdup_printf
      ("videotestsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=16,height=16,framerate=10/1 ! tensor_converter ! queue ! valve name=valve1 ! filesink location=\"%s\"",
      file1);
  GStatBuf buf;

  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  ml_pipeline_valve_h valve1;

  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  assert (dir != NULL);

  status = ml_pipeline_valve_get_handle (handle, "valve1", &valve1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_set_open (valve1, false); /* close */
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Wait for the pipeline stgart. */
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  wait_for_start (handle, state, status);
  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = g_lstat (file1, &buf);
  assert_eq (status, 0);
  assert_eq (buf.st_size, 0);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_set_open (valve1, true); /* open */
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_valve_release_handle (valve1); /* release valve handle */
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. (10Hz x 0.5s --> 5)*/

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = g_lstat (file1, &buf);
  assert_eq (status, 0);
  assert_geq (buf.st_size, 2048); /* At least two frames during SLEEP_TIME */
  assert_eq (buf.st_size % 1024, 0); /* It should be divided by 1024 */

  g_free (fullpath);
  g_free (file1);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_valve_error_cases_n
 * @since_tizen		5.5
 * @description		Failure case to handle valve element with invalid param.
 */
int utc_nnstreamer_scenario_valve_error_cases_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_valve_h valve_h;
  int status;

  gchar * pipeline = g_strdup ("videotestsrc num-buffers=3 ! videoconvert ! valve name=valvex ! tensor_converter ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param : pipe */
  status = ml_pipeline_valve_get_handle (NULL, "valvex", &valve_h);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : name */
  status = ml_pipeline_valve_get_handle (handle, NULL, &valve_h);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : wrong name */
  status = ml_pipeline_valve_get_handle (handle, "wrongname", &valve_h);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : invalid type */
  status = ml_pipeline_valve_get_handle (handle, "sinkx", &valve_h);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : handle */
  status = ml_pipeline_valve_get_handle (handle, "valvex", NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_sink_p1
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline sink
 */
int utc_nnstreamer_scenario_sink_p1 (void)
{
  IS_SUPPORT_FEATURE;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *) fullpath);

  assert_neq (dir, (gchar *) NULL);

  gchar *file1 = g_build_path ("/", dir, "original", NULL);
  gchar *file2 = g_build_path ("/", dir, "sink", NULL);
  gchar * pipeline =
      g_strdup_printf
      ("videotestsrc num-buffers=3 ! videoconvert ! video/x-raw,format=BGRx,width=64,height=48,famerate=60/1 ! tee name=t t. ! queue ! filesink location=\"%s\"  t. ! queue ! tensor_converter ! tensor_sink name=sinkx",
      file1);
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  ml_pipeline_sink_h sinkhandle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_dm01, file2, &sinkhandle);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME * 2); /* Wait a bit. */

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Wait a bit. */

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  /* File Comparison to check the integrity */
  assert_eq (file_cmp (file1, file2), 0);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_sink_p2
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline sink
 */
int utc_nnstreamer_scenario_sink_p2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  ml_pipeline_sink_h sinkhandle;
  int status;
  guint *count_sink;
  TestPipeState *pipe_state;

  /* pipeline with appsink */
  gchar * pipeline = g_strdup ("videotestsrc num-buffers=3 ! videoconvert ! tensor_converter ! appsink name=sinkx");

  count_sink = (guint *) g_malloc (sizeof (guint));
  *count_sink = 0;

  pipe_state = (TestPipeState *) g_new0 (TestPipeState, 1);

  status = ml_pipeline_construct (pipeline, test_pipe_state_callback, pipe_state, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME * 2); /* Let a few frames flow. */

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Wait a bit. */

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert (*count_sink > 0U);
  assert (pipe_state->paused);
  assert (pipe_state->playing);

  g_free (pipeline);
  g_free (count_sink);
  g_free (pipe_state);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_sink_error_cases_n
 * @since_tizen		5.5
 * @description		Failure case to register callback with invalid param.
 */
int utc_nnstreamer_scenario_sink_error_cases_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_sink_h sinkhandle;
  int status;
  guint *count_sink;

  gchar * pipeline = g_strdup ("videotestsrc is-live=true ! videoconvert ! valve name=valvex ! tensor_converter ! tensor_sink name=sinkx");

  count_sink = (guint *) g_malloc (sizeof (guint));
  *count_sink = 0;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param : pipe */
  status = ml_pipeline_sink_register (NULL, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : name */
  status = ml_pipeline_sink_register (handle, NULL, test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : wrong name */
  status = ml_pipeline_sink_register (handle, "wrongname", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : invalid type */
  status = ml_pipeline_sink_register (handle, "valvex", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : callback */
  status = ml_pipeline_sink_register (handle, "sinkx", NULL, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : handle */
  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert (*count_sink > 0U);

  g_free (pipeline);
  g_free (count_sink);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_src_p
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline src
 */
int utc_nnstreamer_scenario_src_p (void)
{
  IS_SUPPORT_FEATURE;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *) fullpath);
  gchar *file1 = g_build_path ("/", dir, "output", NULL);
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  ml_pipeline_src_h srchandle;
  int status;
  ml_tensors_info_h info;
  ml_tensors_data_h data1, data2;
  unsigned int count = 0;
  uint8_t uintarray1[10][4];
  uint8_t uintarray2[10][4];
  uint8_t * content;
  ml_tensor_type_e type = ML_TENSOR_TYPE_UNKNOWN;
  ml_tensor_dimension dim = { 0, };

  int i;
  gsize len;

  gchar * pipeline =
      g_strdup_printf ("appsrc name=srcx ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! filesink location=\"%s\" buffer-mode=unbuffered",
      file1);

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);
  assert (dir != NULL);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Wait a bit. */
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_get_count (info, &count);
  assert_eq (count, 1U);

  ml_tensors_info_get_tensor_type (info, 0, &type);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  ml_tensors_info_get_tensor_dimension (info, 0, dim);
  assert_eq (dim[0], 4U);
  assert_eq (dim[1], 1U);
  assert_eq (dim[2], 1U);
  assert_eq (dim[3], 1U);

  status = ml_tensors_data_create (info, &data1);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (info);

  for (i = 0; i < 10; i++) {
    uintarray1[i][0] = i + 4;
    uintarray1[i][1] = i + 1;
    uintarray1[i][2] = i + 3;
    uintarray1[i][3] = i + 2;

    uintarray2[i][0] = i + 3;
    uintarray2[i][1] = i + 2;
    uintarray2[i][2] = i + 1;
    uintarray2[i][3] = i + 4;
    /* These will be free'ed by gstreamer (ML_PIPELINE_BUF_POLICY_AUTO_FREE) */
    /** @todo Check whether gstreamer really deallocates this */
  }
  status = ml_tensors_data_set_tensor_data (data1, 0, uintarray1[0], 4);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_input_data (srchandle, data1, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Wait a bit. */

  status = ml_pipeline_src_input_data (srchandle, data1, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Wait a bit. */

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_get_count (info, &count);
  assert_eq (count, 1U);

  ml_tensors_info_get_tensor_type (info, 0, &type);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  ml_tensors_info_get_tensor_dimension (info, 0, dim);
  assert_eq (dim[0], 4U);
  assert_eq (dim[1], 1U);
  assert_eq (dim[2], 1U);
  assert_eq (dim[3], 1U);

  for (i = 0; i < 10; i++) {
    status = ml_tensors_data_set_tensor_data (data1, 0, uintarray1[i], 4);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_pipeline_src_input_data (srchandle, data1, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_tensors_data_create (info, &data2);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_tensors_data_set_tensor_data (data2, 0, uintarray2[i], 4);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_pipeline_src_input_data (srchandle, data2, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
    assert_eq (status, ML_ERROR_NONE);

    g_usleep (SLEEP_TIME); /* Wait a bit. */
  }

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Wait for the pipeline to flush all */

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert (g_file_get_contents (file1, (gchar **) &content, &len, NULL));
  assert_eq (len, 8U * 11);

  for (i = 0; i < 10; i++) {
    assert_eq (content[i * 8 + 0 + 8], i + 4);
    assert_eq (content[i * 8 + 1 + 8], i + 1);
    assert_eq (content[i * 8 + 2 + 8], i + 3);
    assert_eq (content[i * 8 + 3 + 8], i + 2);
    assert_eq (content[i * 8 + 4 + 8], i + 3);
    assert_eq (content[i * 8 + 5 + 8], i + 2);
    assert_eq (content[i * 8 + 6 + 8], i + 1);
    assert_eq (content[i * 8 + 7 + 8], i + 4);
  }

  status = ml_tensors_info_destroy (info);
  status = ml_tensors_data_destroy (data1);
  g_free (pipeline);
  g_free (content);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_src_error_case_n1
 * @since_tizen		5.5
 * @description		Failure case when pipeline is NULL.
 */
int utc_nnstreamer_scenario_src_error_case_n1 (void)
{
  int status;
  IS_SUPPORT_FEATURE;
  ml_pipeline_src_h srchandle;

  status = ml_pipeline_src_get_handle (NULL, "dummy", &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_src_error_case_n2
 * @since_tizen		5.5
 * @description		Failure case when the name of source node is wrong.
 */
int utc_nnstreamer_scenario_src_error_case_n2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("appsrc name=mysource ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! valve name=valvex ! tensor_sink");
  ml_pipeline_h handle;
  ml_pipeline_src_h srchandle;

  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param : pipe */
  status = ml_pipeline_src_get_handle (NULL, "mysource", &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : name */
  status = ml_pipeline_src_get_handle (handle, NULL, &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : wrong name */
  status = ml_pipeline_src_get_handle (handle, "wrongname", &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : invalid type */
  status = ml_pipeline_src_get_handle (handle, "valvex", &srchandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : handle */
  status = ml_pipeline_src_get_handle (handle, "mysource", NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_src_error_case_n3
 * @since_tizen		5.5
 * @description		Failure case when the number of tensors is 0 or bigger than ML_TENSOR_SIZE_LIMIT;
 */
int utc_nnstreamer_scenario_src_error_case_n3 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("appsrc name=srcx ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! tensor_sink");
  ml_pipeline_h handle;
  ml_pipeline_src_h srchandle;
  ml_tensors_data_h data;
  ml_tensors_info_h info;

  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_create (info, &data);
  assert_eq (status, ML_ERROR_NONE);

  /* null data */
  status = ml_pipeline_src_input_data (srchandle, NULL, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_data_destroy (data);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_switch_pipeline_p1
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline switch
 */
int utc_nnstreamer_scenario_switch_pipeline_p1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_switch_h switchhandle;
  ml_pipeline_sink_h sinkhandle;
  ml_pipeline_switch_e type;
  ml_pipeline_state_e state;
  int status;
  guint *count_sink;
  TestPipeState *pipe_state;
  gchar **node_list = NULL;

  gchar * pipeline = g_strdup ("input-selector name=ins ! tensor_converter ! tensor_sink name=sinkx "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_0 "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_1");

  count_sink = (guint *) g_malloc (sizeof (guint));
  *count_sink = 0;

  pipe_state = (TestPipeState *) g_new0 (TestPipeState, 1);

  status = ml_pipeline_construct (pipeline, test_pipe_state_callback, pipe_state, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_get_handle (handle, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_INPUT_SELECTOR);

  status = ml_pipeline_switch_get_pad_list (switchhandle, &node_list);
  assert_eq (status, ML_ERROR_NONE);

  if (node_list) {
    gchar *name = NULL;
    guint idx = 0;

    while ((name = node_list[idx]) != NULL) {
      assert (g_str_equal (name, "sink_0") || g_str_equal (name, "sink_1"));
      idx++;
      g_free (name);
    }

    assert_eq (idx, 2U);
    g_free (node_list);
  }

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_select (switchhandle, "sink_1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME);
  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  wait_for_start (handle, state, status);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert (*count_sink > 0U);

  assert (pipe_state->paused);
  assert (pipe_state->playing);

  g_free (count_sink);
  g_free (pipe_state);
  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_switch_pipeline_p2
 * @since_tizen		5.5
 * @description		Test NNStreamer pipeline switch
 */
int utc_nnstreamer_scenario_switch_pipeline_p2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_switch_h switchhandle;
  ml_pipeline_sink_h sinkhandle0, sinkhandle1;
  ml_pipeline_switch_e type;
  int status;
  guint *count_sink0, *count_sink1;
  gchar **node_list = NULL;

  /**
   * Prerolling problem
   * For running the test, set async=false in the sink element when using an output selector.
   * The pipeline state can be changed to paused after all sink element receive buffer.
   */
  gchar * pipeline = g_strdup ("videotestsrc is-live=true ! videoconvert ! tensor_converter ! output-selector name=outs "
      "outs.src_0 ! tensor_sink name=sink0 async=false "
      "outs.src_1 ! tensor_sink name=sink1 async=false");

  count_sink0 = (guint *) g_malloc (sizeof (guint));
  *count_sink0 = 0;

  count_sink1 = (guint *) g_malloc (sizeof (guint));
  *count_sink1 = 0;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_get_handle (handle, "outs", &type, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_PIPELINE_SWITCH_OUTPUT_SELECTOR);

  status = ml_pipeline_switch_get_pad_list (switchhandle, &node_list);
  assert_eq (status, ML_ERROR_NONE);

  if (node_list) {
    gchar *name = NULL;
    guint idx = 0;

    while ((name = node_list[idx]) != NULL) {
      assert (g_str_equal (name, "src_0") || g_str_equal (name, "src_1"));
      idx++;
      g_free (name);
    }

    assert_eq (idx, 2U);
    g_free (node_list);
  }

  status = ml_pipeline_sink_register (handle, "sink0", test_sink_callback_count, count_sink0, &sinkhandle0);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (handle, "sink1", test_sink_callback_count, count_sink1, &sinkhandle1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_select (switchhandle, "src_1");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_sink_unregister (sinkhandle0);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sinkhandle1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  assert_eq (*count_sink0, 0U);
  assert (*count_sink1 > 0U);

  g_free (count_sink0);
  g_free (count_sink1);
  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_switch_pipeline_error_cases_n
 * @since_tizen		5.5
 * @description		Failure case to handle input-selector element with invalid param.
 */
int utc_nnstreamer_scenario_switch_pipeline_error_cases_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_switch_h switchhandle;
  ml_pipeline_switch_e type;
  int status;

  gchar * pipeline = g_strdup ("input-selector name=ins ! tensor_converter ! tensor_sink name=sinkx "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_0 "
      "videotestsrc is-live=true ! videoconvert ! ins.sink_1");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param : pipe */
  status = ml_pipeline_switch_get_handle (NULL, "ins", &type, &switchhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : name */
  status = ml_pipeline_switch_get_handle (handle, NULL, &type, &switchhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : wrong name */
  status = ml_pipeline_switch_get_handle (handle, "wrongname", &type, &switchhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : invalid type */
  status = ml_pipeline_switch_get_handle (handle, "sinkx", &type, &switchhandle);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : handle */
  status = ml_pipeline_switch_get_handle (handle, "ins", &type, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* successfully get switch handle if the param type is null */
  status = ml_pipeline_switch_get_handle (handle, "ins", NULL, &switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  /* invalid param : handle */
  status = ml_pipeline_switch_select (NULL, "invalidpadname");
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : pad name */
  status = ml_pipeline_switch_select (switchhandle, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid param : wrong pad name */
  status = ml_pipeline_switch_select (switchhandle, "wrongpadname");
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_pipeline_switch_release_handle (switchhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_check_tensor_info_utilities_p
 * @since_tizen		5.5
 * @description		Test NNStreamer Utility for checking tensors info handle
 */
int utc_nnstreamer_scenario_check_tensor_info_utilities_p (void)
{
  gchar *out_name;
  size_t data_size;
  int status;
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h info;
  ml_tensor_dimension in_dim, out_dim;
  ml_tensor_type_e out_type;

  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  in_dim[0] = 3;
  in_dim[1] = 300;
  in_dim[2] = 300;
  in_dim[3] = 1;

  /* add tensor info */
  status = ml_tensors_info_set_count (info, 2);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_set_tensor_dimension (info, 0, in_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 1, ML_TENSOR_TYPE_FLOAT64);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_set_tensor_dimension (info, 1, in_dim);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_set_tensor_name (info, 1, "tensor-name-test");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 2, ML_TENSOR_TYPE_UINT64);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);
  status = ml_tensors_info_set_tensor_dimension (info, 2, in_dim);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* get tensor info */
  status = ml_tensors_info_get_tensor_type (info, 0, &out_type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_type, ML_TENSOR_TYPE_UINT8);

  status = ml_tensors_info_get_tensor_dimension (info, 0, out_dim);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_dim[0], 3U);
  assert_eq (out_dim[1], 300U);
  assert_eq (out_dim[2], 300U);
  assert_eq (out_dim[3], 1U);

  status = ml_tensors_info_get_tensor_name (info, 0, &out_name);
  assert_eq (status, ML_ERROR_NONE);
  assert (out_name == NULL);

  status = ml_tensors_info_get_tensor_type (info, 1, &out_type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_type, ML_TENSOR_TYPE_FLOAT64);

  status = ml_tensors_info_get_tensor_dimension (info, 1, out_dim);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_dim[0], 3U);
  assert_eq (out_dim[1], 300U);
  assert_eq (out_dim[2], 300U);
  assert_eq (out_dim[3], 1U);

  status = ml_tensors_info_get_tensor_name (info, 1, &out_name);
  assert_eq (status, ML_ERROR_NONE);
  assert (out_name && g_str_equal (out_name, "tensor-name-test"));
  g_free (out_name);

  status = ml_tensors_info_get_tensor_type (info, 2, &out_type);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_get_tensor_dimension (info, 2, out_dim);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_get_tensor_name (info, 2, &out_name);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* get tensor size */
  status = ml_tensors_info_get_tensor_size (info, 0, &data_size);
  assert_eq (status, ML_ERROR_NONE);
  assert (data_size == (3 * 300 * 300));

  status = ml_tensors_info_get_tensor_size (info, 1, &data_size);
  assert_eq (status, ML_ERROR_NONE);
  assert (data_size == (3 * 300 * 300 * 8));

  status = ml_tensors_info_get_tensor_size (info, -1, &data_size);
  assert_eq (status, ML_ERROR_NONE);
  assert (data_size == ((3 * 300 * 300) + (3 * 300 * 300 * 8)));

  status = ml_tensors_info_get_tensor_size (info, 2, &data_size);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_filter_tensorflow_lite_p1
 * @since_tizen		5.5
 * @description		Test NNStreamer single shot (tensorflow-lite)
 */
int utc_nnstreamer_scenario_filter_tensorflow_lite_p1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_info_h in_res, out_res;
  ml_tensors_data_h input, output;
  ml_tensor_dimension in_dim, out_dim, res_dim;
  ml_tensor_type_e type = ML_TENSOR_TYPE_UNKNOWN;
  unsigned int count = 0;
  char *name = NULL;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "mobilenet_v1_1.0_224_quant.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_nnstreamer_scenario_filter_tensorflow_lite_p1");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
  assert (g_file_test (test_model, G_FILE_TEST_EXISTS));

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);
  ml_tensors_info_create (&in_res);
  ml_tensors_info_create (&out_res);

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

  /* input tensor in filter */
  status = ml_single_get_input_info (single, &in_res);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (in_res, &count);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (count, 1U);

  status = ml_tensors_info_get_tensor_name (in_res, 0, &name);
  assert_eq (status, ML_ERROR_NONE);
  g_free (name);

  status = ml_tensors_info_get_tensor_type (in_res, 0, &type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  ml_tensors_info_get_tensor_dimension (in_res, 0, res_dim);
  assert (in_dim[0] == res_dim[0]);
  assert (in_dim[1] == res_dim[1]);
  assert (in_dim[2] == res_dim[2]);
  assert (in_dim[3] == res_dim[3]);

  /* output tensor in filter */
  status = ml_single_get_output_info (single, &out_res);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (out_res, &count);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (count, 1U);

  status = ml_tensors_info_get_tensor_name (out_res, 0, &name);
  assert_eq (status, ML_ERROR_NONE);
  g_free (name);

  status = ml_tensors_info_get_tensor_type (out_res, 0, &type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  ml_tensors_info_get_tensor_dimension (out_res, 0, res_dim);
  assert (out_dim[0] == res_dim[0]);
  assert (out_dim[1] == res_dim[1]);
  assert (out_dim[2] == res_dim[2]);
  assert (out_dim[3] == res_dim[3]);

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

  g_free (test_model);
  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);
  ml_tensors_info_destroy (in_res);
  ml_tensors_info_destroy (out_res);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_filter_tensorflow_lite_p2
 * @since_tizen		5.5
 * @description		Test NNStreamer single shot (tensorflow-lite), Start pipeline without tensor info
 */
int utc_nnstreamer_scenario_filter_tensorflow_lite_p2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h input, output;
  ml_tensor_dimension in_dim, out_dim;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "mobilenet_v1_1.0_224_quant.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_nnstreamer_scenario_filter_tensorflow_lite_p2");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;
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

  status = ml_single_open (&single, test_model, NULL, NULL,
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

  g_free (test_model);
  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_filter_tensorflow_lite_n
 * @since_tizen		5.5
 * @description		Test NNStreamer single shot (tensorflow-lite), Failure case with invalid param.
 */
int utc_nnstreamer_scenario_filter_tensorflow_lite_n (void)
{
  IS_SUPPORT_FEATURE;
  ml_single_h single;
  ml_tensors_info_h in_info, out_info;
  ml_tensor_dimension in_dim, out_dim;
  int status;

  gchar *test_model;

  char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

  char *model_file = "mobilenet_v1_1.0_224_quant.tflite";
  char *model_file_path = NULL;

  if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
  {
    int model_path_len = strlen(pszValue) + strlen(model_file) + 10;
    model_file_path = (char*)malloc(model_path_len);
    CHECK_HANDLE(model_file_path,"malloc:failure:utc_nnstreamer_scenario_filter_tensorflow_lite_n");
    snprintf(model_file_path, model_path_len, "%s/res/res/%s", pszValue, model_file);
  }

  test_model = model_file_path;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  /* invalid file path */
  status = ml_single_open (&single, "wrong_file_name", in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* null file path */
  status = ml_single_open (&single, NULL, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid handle */
  status = ml_single_open (NULL, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid input tensor info */
  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  in_dim[0] = 3;
  in_dim[1] = 224;
  in_dim[2] = 224;
  in_dim[3] = 1;
  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, in_dim);

  /* invalid output tensor info */
  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW_LITE, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  out_dim[0] = 1001;
  out_dim[1] = 1;
  out_dim[2] = 1;
  out_dim[3] = 1;
  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_UINT8);
  ml_tensors_info_set_tensor_dimension (out_info, 0, out_dim);

  /* invalid file extension */
  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_TENSORFLOW, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* invalid handle */
  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  /* Successfully opened unknown fw type (tf-lite) */
  status = ml_single_open (&single, test_model, in_info, out_info,
      ML_NNFW_TYPE_ANY, ML_NNFW_HW_ANY);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_single_close (single);
  assert_eq (status, ML_ERROR_NONE);

  g_free (test_model);
  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_p
 * @since_tizen		6.0
 * @description		Test the conversion and decoding of the nnstreamer flatbuf.
 */
int utc_nnstreamer_scenario_flatbuf_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  int status;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *) fullpath);
  gchar *file1 = g_build_path ("/", dir, "video_raw.log", NULL);
  gchar *file2 = g_build_path ("/", dir, "flatbuf.log", NULL);

  gchar * pipeline = g_strdup_printf ("videotestsrc num-buffers=1 pattern=13 ! "
    "video/x-raw,format=RGB,width=320,height=240,framerate=5/1 ! tensor_converter ! "
    "tee name=t ! queue ! filesink location=\"%s\" buffer-mode=unbuffered "
    "t. ! queue ! tensor_decoder mode=flatbuf ! other/flatbuf-tensor ! tensor_converter ! "
    "filesink location=\"%s\" buffer-mode=unbuffered", file1, file2);

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

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  /* File Comparison to check conversion and decoding of the nnstreamer flatbuf. */
  assert_eq (file_cmp (file1, file2), 0);

  g_free (file1);
  g_free (file2);
  g_free (fullpath);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_n1
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with missing caps
 */
int utc_nnstreamer_scenario_flatbuf_n1 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=flatbuf ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_n2
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid caps
 */
int utc_nnstreamer_scenario_flatbuf_n2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=flatbuf ! other/flatbuf ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_n3
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid caps
 */
int utc_nnstreamer_scenario_flatbuf_n3 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=flatbuf ! other/protobuf-tensor ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_n4
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with missing property of the tensor converter
 */
int utc_nnstreamer_scenario_flatbuf_n4 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder ! other/flatbuf-tensor ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_flatbuf_n5
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid framerate of flatbuf caps
 */
int utc_nnstreamer_scenario_flatbuf_n5 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 !  videoconvert ! videoscale ! video/x-raw, width=320, height=240, framerate=30/1, format=RGB ! "
    "tensor_converter ! tensor_decoder mode=flatbuf ! other/flatbuf-tensor,framerate=10/1 ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}


/**
 * @testcase		utc_nnstreamer_scenario_protobuf_p
 * @since_tizen		6.0
 * @description		Test the conversion and decoding of the nnstreamer protobuf.
 */
int utc_nnstreamer_scenario_protobuf_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  int status;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *) fullpath);
  gchar *file1 = g_build_path ("/", dir, "video_raw.log", NULL);
  gchar *file2 = g_build_path ("/", dir, "protobuf.log", NULL);

  gchar * pipeline = g_strdup_printf ("videotestsrc num-buffers=1 pattern=13 ! "
    "video/x-raw,format=RGB,width=320,height=240,framerate=5/1 ! tensor_converter ! "
    "tee name=t ! queue ! filesink location=\"%s\" buffer-mode=unbuffered "
    "t. ! queue ! tensor_decoder mode=protobuf ! other/protobuf-tensor ! tensor_converter ! "
    "filesink location=\"%s\" buffer-mode=unbuffered", file1, file2);

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

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  /* File Comparison to check conversion and decoding of the nnstreamer protobuf. */
  assert_eq (file_cmp (file1, file2), 0);

  g_free (file1);
  g_free (file2);
  g_free (fullpath);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_protobuf_n1
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with missing caps
 */
int utc_nnstreamer_scenario_protobuf_n1 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=protobuf ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_protobuf_n2
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid caps
 */
int utc_nnstreamer_scenario_protobuf_n2 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=protobuf ! other/protobuf ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_protobuf_n3
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid caps
 */
int utc_nnstreamer_scenario_protobuf_n3 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder mode=protobuf ! other/flatbuf-tensor ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_protobuf_n4
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with missing property of the tensor converter
 */
int utc_nnstreamer_scenario_protobuf_n4 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 ! "
    "tensor_converter ! tensor_decoder ! other/protobuf-tensor ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_protobuf_n5
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid framerate of protobuf caps
 */
int utc_nnstreamer_scenario_protobuf_n5 (void)
{
  IS_SUPPORT_FEATURE;
  gchar * pipeline = g_strdup("videotestsrc numbuffers=1 pattern=13 !  videoconvert ! videoscale ! video/x-raw, width=320, height=240, framerate=30/1, format=RGB ! "
    "tensor_converter ! tensor_decoder mode=protobuf ! other/protobuf-tensor,framerate=10/1 ! tensor_converter ! tensor_sink");
  ml_pipeline_h handle;
  int status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_tizensensor_p
 * @since_tizen		6.0
 * @description		Test the tensor_src_tizensensor (accelerometer sensor) to work
 */
int utc_nnstreamer_scenario_tizensensor_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  int status;
  bool tizensensor_is_supported = false;
  bool accelerometer_is_supported = false;
  gchar * pipeline;

  status = system_info_get_platform_bool (
      "http://tizen.org/feature/sensor.accelerometer",
      &accelerometer_is_supported);
  if (status != SYSTEM_INFO_ERROR_NONE || !accelerometer_is_supported) {
    FPRINTF("[%s][%d][%s] feature sensor.accelerometer is not supported!\\n", __FILE__, __LINE__, __FUNCTION__);
    return 0;
  }

  status = ml_check_element_availability ("tensor_src_tizensensor", &tizensensor_is_supported);
  if (status !=ML_ERROR_NONE || !tizensensor_is_supported) {
    FPRINTF("[%s][%d][%s] tizensensorsrc is not available on the device!\\n", __FILE__, __LINE__, __FUNCTION__);
    return 0;
  }

  pipeline = g_strdup_printf ("tensor_src_tizensensor type=accelerometer ! tensor_sink sync=true");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE); /* At this moment, it can be READY, PAUSED, or PLAYING */
  assert_neq (state, ML_PIPELINE_STATE_UNKNOWN);
  assert_neq (state, ML_PIPELINE_STATE_NULL);

  g_usleep (SLEEP_TIME); /* SLEEP_TIME is good for general systems, but not enough for emulators to start gst pipeline. Let a few frames flow. */

  wait_for_start (handle, state, status);

  assert_eq (state, ML_PIPELINE_STATE_PLAYING);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (SLEEP_TIME); /* Let a few frames flow. */

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (state, ML_PIPELINE_STATE_PAUSED);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_tizensensor_n1
 * @since_tizen		6.0
 * @description		Negative test case to construct pipeline with invalid sensor type
 */
int utc_nnstreamer_scenario_tizensensor_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle;
  ml_pipeline_state_e state;
  bool tizensensor_is_supported = false;
  int status;
  gchar * pipeline;

  status = ml_check_element_availability ("tensor_src_tizensensor", &tizensensor_is_supported);
  if (status !=ML_ERROR_NONE || !tizensensor_is_supported) {
    FPRINTF("[%s][%d][%s] tizensensorsrc is not available on the device!\\n", __FILE__, __LINE__, __FUNCTION__);
    return 0;
  }

  /* there is no sensor type named "invalid_sensor" */
  pipeline = g_strdup_printf (
      "tensor_src_tizensensor type=invalid_sensor ! tensor_sink sync=true");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_STREAMS_PIPE);

  g_free (pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_capi_element_p1
 * @since_tizen		6.0
 * @description		Construct the pipeline and run it during updating element's property.
 */
int utc_nnstreamer_scenario_capi_element_p1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  ml_pipeline_state_e state;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale ! video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! " \
    "tensor_converter ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test code: Set the videotestsrc pattern */
  status = ml_pipeline_element_set_property_enum (vsrc_h, "pattern", 4);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (50000);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  wait_for_start (handle, state, status);
  assert_eq (state, ML_PIPELINE_STATE_PLAYING);

  /* Stop playing */
  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (50000);

  /* Test code: Set the new videotestsrc pattern */
  status = ml_pipeline_element_set_property_enum (vsrc_h, "pattern", 12);
  assert_eq (status, ML_ERROR_NONE);

  /* Resume playing */
  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (50000);

  status = ml_pipeline_get_state (handle, &state);
  assert_eq (status, ML_ERROR_NONE);
  wait_for_start (handle, state, status);
  assert_eq (state, ML_PIPELINE_STATE_PLAYING);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  g_usleep (50000);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_scenario_capi_element_p2
 * @since_tizen		6.0
 * @description		Construct the pipeline and run it during updating element's property.
 */
int utc_nnstreamer_scenario_capi_element_p2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_sink_h sinkhandle = NULL;
  ml_pipeline_element_h asink_h = NULL;
  gchar *pipeline;
  guint *count_sink;
  int status;

  pipeline = g_strdup ("videotestsrc is-live=true ! videoconvert ! tensor_converter ! appsink name=sinkx sync=false");

  count_sink = (guint *) g_malloc (sizeof (guint));
  assert_neq (count_sink, NULL);
  *count_sink = 0;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "sinkx", &asink_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (handle, "sinkx", test_sink_callback_count, count_sink, &sinkhandle);
  assert_eq (status, ML_ERROR_NONE);
  assert_neq (sinkhandle, NULL);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (100000);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);
  assert_gt (*count_sink, 0U);

  /* Test Code */
  *count_sink = 0;

  status = ml_pipeline_element_set_property_bool (asink_h, "emit-signals", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_usleep (100000);

  /* Since `emit-signals` property of appsink is set as FALSE, *count_sink should be 0 */
  assert_eq (*count_sink, 0U);

  status = ml_pipeline_stop (handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sinkhandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (asink_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free (pipeline);
  g_free (count_sink);

  return 0;
}
