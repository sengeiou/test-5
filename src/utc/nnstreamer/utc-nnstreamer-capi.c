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

#include "utc-nnstreamer-common.h"

/**
 * @function		utc_nnstreamer_capi_startup
 * @since_tizen		6.0
 * @description		called before the specific test cases
 */
void utc_nnstreamer_capi_startup(void)
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
 * @function		utc_nnstreamer_capi_cleanup
 * @since_tizen		6.0
 * @description		called after the specific test cases
 */
void utc_nnstreamer_capi_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_handle_p
 * @since_tizen		6.0
 * @description		Positive test case of getting element handle
 */
int utc_nnstreamer_capi_element_get_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h  = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_handle_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting element handle with NULL name
 */
int utc_nnstreamer_capi_element_get_handle_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_handle (handle, NULL, &vsrc_h);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_handle_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting element handle with wrong name
 */
int utc_nnstreamer_capi_element_get_handle_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_handle (handle, "WRONG_PROPERTY_NAME", &vsrc_h);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_release_handle_p
 * @since_tizen		6.0
 * @description		Positive test case of releasing element handle
 */
int utc_nnstreamer_capi_element_release_handle_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  ml_pipeline_element_h selector_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_release_handle_n1
 * @since_tizen		6.0
 * @description		Negative test case of releasing element handle with NULL name
 */
int utc_nnstreamer_capi_element_release_handle_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_handle (handle, NULL, &vsrc_h);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_release_handle_n2
 * @since_tizen		6.0
 * @description		Negative test case of releasing element handle with wrong name
 */
int utc_nnstreamer_capi_element_release_handle_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_handle (handle, "WRONG_PROPERTY_NAME", &vsrc_h);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_bool_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting boolean property
 */
int utc_nnstreamer_capi_element_set_bool_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", TRUE);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_bool_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting boolean property without element handle
 */
int utc_nnstreamer_capi_element_set_bool_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_bool(NULL, "sync-streams", FALSE);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_bool_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting boolean property
 */
int utc_nnstreamer_capi_element_set_bool_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_bool(selector_h, "WRONG_PROPERTY", TRUE);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_bool_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting boolean property
 */
int utc_nnstreamer_capi_element_get_bool_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int ret_sync_streams;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_bool (selector_h, "sync-streams", &ret_sync_streams);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_sync_streams, FALSE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", TRUE);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_bool (selector_h, "sync-streams", &ret_sync_streams);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_sync_streams, TRUE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_bool_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting boolean property without element handle
 */
int utc_nnstreamer_capi_element_get_bool_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int ret_sync_streams;
  int status;

  /* Test Code */
  status = ml_pipeline_element_get_property_bool (NULL, "sync-streams", &ret_sync_streams);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_bool_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting boolean property with invalid property name
 */
int utc_nnstreamer_capi_element_get_bool_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int ret_sync_streams;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_bool (selector_h, "WRONG_NAME", &ret_sync_streams);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_bool_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting boolean property without return value
 */
int utc_nnstreamer_capi_element_get_bool_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_bool (selector_h, "sync-streams", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_bool_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting boolean property with wrong type
 */
int utc_nnstreamer_capi_element_get_bool_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h selector_h = NULL;
  gchar *pipeline;
  int ret_wrong_type;
  int status;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "is01", &selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_bool(selector_h, "sync-streams", FALSE);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (selector_h, "sync-streams", &ret_wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (selector_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_string_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting string property
 */
int utc_nnstreamer_capi_element_set_string_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_string (demux_h, "tensorpick", "0");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_string_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting string property without element handle
 */
int utc_nnstreamer_capi_element_set_string_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_string (NULL, "tensorpick", "0");
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_string_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting string property with wrong name
 */
int utc_nnstreamer_capi_element_set_string_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_string (demux_h, "WRONG_NAME", "0");
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_string_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting string property
 */
int utc_nnstreamer_capi_element_get_string_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  gchar *ret_tensorpick;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_string (demux_h, "tensorpick", "0");
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_string (demux_h, "tensorpick", &ret_tensorpick);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (g_str_equal (ret_tensorpick, "0"), TRUE);
  g_free (ret_tensorpick);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_string_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting string property without element handle
 */
int utc_nnstreamer_capi_element_get_string_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  gchar *ret_tensorpick;

  /* Test Code */
  status = ml_pipeline_element_get_property_string (NULL, "tensorpick", &ret_tensorpick);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_string_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting string property with wrong name
 */
int utc_nnstreamer_capi_element_get_string_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  gchar *ret_tensorpick;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_string (demux_h, "tensorpick", "0");
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_string (demux_h, "WRONG_NAME", &ret_tensorpick);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_string_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting string property without return value
 */
int utc_nnstreamer_capi_element_get_string_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_string (demux_h, "tensorpick", "0");
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_string (demux_h, "tensorpick", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_string_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting string property with wrong type
 */
int utc_nnstreamer_capi_element_get_string_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h demux_h = NULL;
  gchar *pipeline;
  int ret_wrong_type;
  int status;

  pipeline = g_strdup("videotestsrc ! video/x-raw,format=RGB,width=640,height=480 ! videorate max-rate=1 ! " \
    "tensor_converter ! tensor_mux ! tensor_demux name=demux ! tensor_sink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "demux", &demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_string (demux_h, "tensorpick", "0");
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (demux_h, "tensorpick", &ret_wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (demux_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int32_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting int32 property
 */
int utc_nnstreamer_capi_element_set_int32_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", 10);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", -1234);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int32_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting int32 property without element handle
 */
int utc_nnstreamer_capi_element_set_int32_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (NULL, "kx", 10);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int32_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting int32 property with wrong name
 */
int utc_nnstreamer_capi_element_set_int32_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (vsrc_h, "WRONG_NAME", 10);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int32_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting int32 property with wrong type
 */
int utc_nnstreamer_capi_element_set_int32_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "kx", 10U);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int32_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting int32 property
 */
int utc_nnstreamer_capi_element_get_int32_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int32_t ret_kx;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", 10);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vsrc_h, "kx", &ret_kx);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_kx, 10);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", -1234);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_int32 (vsrc_h, "kx", &ret_kx);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_kx, -1234);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int32_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting int32 property without element handle
 */
int utc_nnstreamer_capi_element_get_int32_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  int32_t ret_kx;

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (NULL, "kx", &ret_kx);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int32_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting int32 property with wrong name
 */
int utc_nnstreamer_capi_element_get_int32_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int32_t ret_kx;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", 10);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vsrc_h, "WRONG_NAME", &ret_kx);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int32_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting int32 property without return value
 */
int utc_nnstreamer_capi_element_get_int32_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", 10);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vsrc_h, "kx", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int32_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting int32 property with wrong type
 */
int utc_nnstreamer_capi_element_get_int32_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int32_t ret_kx;
  uint32_t ret_wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vsrc_h, "kx", 10);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (vsrc_h, "kx", &ret_wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int64_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting int64 property
 */
int utc_nnstreamer_capi_element_set_int64_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 1234567891234LL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 10LL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int64_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting int64 property without element handle
 */
int utc_nnstreamer_capi_element_set_int64_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_int64 (NULL, "timestamp-offset", 1234567891234LL);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int64_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting int64 property with wrong name
 */
int utc_nnstreamer_capi_element_set_int64_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int64 (vsrc_h, "WRONG_NAME", 1234567891234LL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_int64_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting int64 property with wrong type
 */
int utc_nnstreamer_capi_element_set_int64_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (vsrc_h, "timestamp-offset", 12LL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int64_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting int64 property
 */
int utc_nnstreamer_capi_element_get_int64_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int64_t ret_timestame_offset;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 1234567891234LL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int64 (vsrc_h, "timestamp-offset", &ret_timestame_offset);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_timestame_offset, 1234567891234LL);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 10LL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_int64 (vsrc_h, "timestamp-offset", &ret_timestame_offset);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_timestame_offset, 10LL);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int64_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting int64 property
 */
int utc_nnstreamer_capi_element_get_int64_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  int64_t ret_timestame_offset;

  /* Test Code */
  status = ml_pipeline_element_get_property_int64 (NULL, "timestamp-offset", &ret_timestame_offset);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int64_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting int64 property with wrong name
 */
int utc_nnstreamer_capi_element_get_int64_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int64_t ret_timestame_offset;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 1234567891234LL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int64 (vsrc_h, "WRONG_NAME", &ret_timestame_offset);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int64_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting int64 property without return value
 */
int utc_nnstreamer_capi_element_get_int64_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 1234567891234LL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int64 (vsrc_h, "timestamp-offset", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_int64_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting int64 property with wrong type
 */
int utc_nnstreamer_capi_element_get_int64_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int64 (vsrc_h, "timestamp-offset", 1234567891234LL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vsrc_h, "timestamp-offset", &wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint32_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting uint32 property
 */
int utc_nnstreamer_capi_element_set_uint32_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 123456U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 4294967295U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint32_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting uint32 property without element handle
 */
int utc_nnstreamer_capi_element_set_uint32_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_uint32 (NULL, "foreground-color", 123456U);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint32_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting uint32 property
 */
int utc_nnstreamer_capi_element_set_uint32_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "WRONG_NAME", 123456U);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint32_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting uint32 property
 */
int utc_nnstreamer_capi_element_set_uint32_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (vsrc_h, "foreground-color", 123456);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint32_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting uint32 property
 */
int utc_nnstreamer_capi_element_get_uint32_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  uint32_t ret_foreground_color;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 123456U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (vsrc_h, "foreground-color", &ret_foreground_color);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_foreground_color, 123456U);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 4294967295U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_uint32 (vsrc_h, "foreground-color", &ret_foreground_color);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_foreground_color, 4294967295U);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint32_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting uint32 property without element handle
 */
int utc_nnstreamer_capi_element_get_uint32_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  uint32_t ret_foreground_color;

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (NULL, "foreground-color", &ret_foreground_color);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint32_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting uint32 property with wrong name
 */
int utc_nnstreamer_capi_element_get_uint32_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  uint32_t ret_foreground_color;
  int32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 123456U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (vsrc_h, "WRONG_NAME", &ret_foreground_color);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint32_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting uint32 property without return value
 */
int utc_nnstreamer_capi_element_get_uint32_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 123456U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (vsrc_h, "foreground-color", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint32_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting uint32 property
 */
int utc_nnstreamer_capi_element_get_uint32_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vsrc_h = NULL;
  int status;
  int32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vsrc", &vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vsrc_h, "foreground-color", 123456U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vsrc_h, "foreground-color", &wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint64_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting uint64 property
 */
int utc_nnstreamer_capi_element_set_uint64_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 123456789123456789ULL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 987654321ULL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint64_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting uint64 property without element handle
 */
int utc_nnstreamer_capi_element_set_uint64_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_uint64 (NULL, "timeout", 123456789123456789ULL);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint64_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting uint64 property with wrong name
 */
int utc_nnstreamer_capi_element_set_uint64_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "WRONG_NAME", 123456789123456789ULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_uint64_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting uint64 property with wrong type
 */
int utc_nnstreamer_capi_element_set_uint64_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_uint32 (udpsrc_h, "timeout", 123456789ULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint64_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting uint64 property
 */
int utc_nnstreamer_capi_element_get_uint64_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  uint64_t ret_timeout;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 123456789123456789ULL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint64 (udpsrc_h, "timeout", &ret_timeout);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_timeout, 123456789123456789ULL);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 987654321ULL);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_uint64 (udpsrc_h, "timeout", &ret_timeout);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_timeout, 987654321ULL);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint64_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting uint64 property without element handle
 */
int utc_nnstreamer_capi_element_get_uint64_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  uint64_t ret_timeout;

  /* Test Code */
  status = ml_pipeline_element_get_property_uint64 (NULL, "timeout", &ret_timeout);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint64_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting uint64 property with wrong name
 */
int utc_nnstreamer_capi_element_get_uint64_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  uint64_t ret_timeout;
  uint32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 123456789123456789ULL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint64 (udpsrc_h, "WRONG_NAME", &ret_timeout);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint64_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting uint64 property without return value
 */
int utc_nnstreamer_capi_element_get_uint64_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  uint32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 123456789123456789ULL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint64 (udpsrc_h, "timeout", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_uint64_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting uint64 property with wrong type
 */
int utc_nnstreamer_capi_element_get_uint64_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h udpsrc_h = NULL;
  int status;
  uint32_t wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("udpsrc name=usrc port=5555 caps=application/x-rtp ! queue ! fakesink");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "usrc", &udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint64 (udpsrc_h, "timeout", 123456789123456789ULL);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_uint32 (udpsrc_h, "timeout", &wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (udpsrc_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_double_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting double property
 */
int utc_nnstreamer_capi_element_set_double_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 0.72);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 1.43);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_double_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting double property without element handle
 */
int utc_nnstreamer_capi_element_set_double_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_double (NULL, "sharpness", 0.72);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_double_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting double property with wrong name
 */
int utc_nnstreamer_capi_element_set_double_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_double (vscale_h, "WRONG_NAME", 1.43);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_double_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting double property with wrong type
 */
int utc_nnstreamer_capi_element_set_double_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_int32 (vscale_h, "sharpness", 10);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_double_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting double property
 */
int utc_nnstreamer_capi_element_get_double_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  double ret_sharpness;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 0.72);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_double (vscale_h, "sharpness", &ret_sharpness);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_sharpness, 0.72);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 1.43);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_double (vscale_h, "sharpness", &ret_sharpness);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_sharpness, 1.43);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_double_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting double property without element handle
 */
int utc_nnstreamer_capi_element_get_double_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  double ret_sharpness;

  /* Test Code */
  status = ml_pipeline_element_get_property_double (NULL, "sharpness", &ret_sharpness);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_double_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting double property with wrong name
 */
int utc_nnstreamer_capi_element_get_double_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  double ret_sharpness;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 0.72);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_double (vscale_h, "WRONG_NAME", &ret_sharpness);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_double_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting double property without return value
 */
int utc_nnstreamer_capi_element_get_double_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 0.72);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_double (vscale_h, "sharpness", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_double_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting double property with wrong type
 */
int utc_nnstreamer_capi_element_get_double_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  int wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_double (vscale_h, "sharpness", 0.72);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_int32 (vscale_h, "sharpness", &wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_enum_property_p
 * @since_tizen		6.0
 * @description		Positive test case of setting enum property
 */
int utc_nnstreamer_capi_element_set_enum_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 3U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 5U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_int32 (vscale_h, "method", 4);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_uint32 (vscale_h, "method", 2U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_enum_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of setting enum property without element handle
 */
int utc_nnstreamer_capi_element_set_enum_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* Test Code */
  status = ml_pipeline_element_set_property_enum (NULL, "method", 3U);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_enum_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of setting enum property
 */
int utc_nnstreamer_capi_element_set_enum_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_enum (vscale_h, "WRONG_NAME", 3U);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_set_enum_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of setting enum property
 */
int utc_nnstreamer_capi_element_set_enum_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_set_property_double (vscale_h, "method", 3.0);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_enum_property_p
 * @since_tizen		6.0
 * @description		Positive test case of getting enum property
 */
int utc_nnstreamer_capi_element_get_enum_property_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  uint32_t ret_method;
  int32_t ret_signed_method;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 3U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_enum (vscale_h, "method", &ret_method);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_method, 3U);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 5U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_enum (vscale_h, "method", &ret_method);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_method, 5U);

  status = ml_pipeline_element_set_property_uint32 (vscale_h, "method", 2U);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_uint32 (vscale_h, "method", &ret_method);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_method, 2U);

  status = ml_pipeline_element_set_property_int32 (vscale_h, "method", 4);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_property_int32 (vscale_h, "method", &ret_signed_method);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (ret_signed_method, 4);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_enum_property_n1
 * @since_tizen		6.0
 * @description		Negative test case of getting enum property without element handle
 */
int utc_nnstreamer_capi_element_get_enum_property_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  uint32_t ret_method;

  /* Test Code */
  status = ml_pipeline_element_get_property_enum (NULL, "method", &ret_method);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_enum_property_n2
 * @since_tizen		6.0
 * @description		Negative test case of getting enum property with wrong name
 */
int utc_nnstreamer_capi_element_get_enum_property_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  uint32_t ret_method;
  double wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 3U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_enum (vscale_h, "WRONG_NAME", &ret_method);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_enum_property_n3
 * @since_tizen		6.0
 * @description		Negative test case of getting enum property without return value
 */
int utc_nnstreamer_capi_element_get_enum_property_n3 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  double wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 3U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_enum (vscale_h, "method", NULL);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_element_get_enum_property_n4
 * @since_tizen		6.0
 * @description		Negative test case of getting enum property with wrong type
 */
int utc_nnstreamer_capi_element_get_enum_property_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_h handle = NULL;
  ml_pipeline_element_h vscale_h = NULL;
  int status;
  double wrong_type;
  gchar *pipeline;

  pipeline = g_strdup("videotestsrc name=vsrc is-live=true ! videoconvert ! videoscale name=vscale ! " \
    "video/x-raw,format=RGBx,width=224,height=224,framerate=60/1 ! tensor_converter ! " \
    "valve name=valvex ! input-selector name=is01 ! tensor_sink name=sinkx");

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_get_handle (handle, "vscale", &vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_set_property_enum (vscale_h, "method", 3U);
  assert_eq (status, ML_ERROR_NONE);

  /* Test Code */
  status = ml_pipeline_element_get_property_double (vscale_h, "method", &wrong_type);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_element_release_handle (vscale_h);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (handle);
  assert_eq (status, ML_ERROR_NONE);

  g_free(pipeline);

  return 0;
}

/**
 * @function		test_custom_easy_cb
 * @description		Invoke callback for custom-easy filter.
 */
static int
test_custom_easy_cb (const ml_tensors_data_h in, ml_tensors_data_h out,
    void *user_data)
{
  /* test code, set data size. */
  if (user_data) {
    void *raw_data = NULL;
    size_t *data_size = (size_t *) user_data;

    ml_tensors_data_get_tensor_data (out, 0, &raw_data, data_size);
  }

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_p
 * @since_tizen		6.0
 * @description		Positive test case of registering the custom filter
 */
int utc_nnstreamer_capi_custom_filter_registration_p (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_pipeline_h pipe;
  ml_pipeline_src_h src;
  ml_pipeline_sink_h sink;
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info, out_info;
  ml_tensors_data_h in_data;
  ml_tensor_dimension dim = { 2, 1, 1, 1 };
  int status;
  gchar *pipeline =
      g_strdup_printf
      ("appsrc name=srcx ! other/tensor,dimension=(string)2:1:1:1,type=(string)int8,framerate=(fraction)0/1 ! " \
       "tensor_filter framework=custom-easy model=%s ! tensor_sink name=sinkx",
      test_custom_filter);
  guint *count_sink = (guint *) g_malloc0 (sizeof (guint));
  size_t *filter_data_size = (size_t *) g_malloc0 (sizeof (size_t));
  size_t data_size;
  guint i;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_INT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, dim);

  ml_tensors_info_create (&out_info);
  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_FLOAT32);
  ml_tensors_info_set_tensor_dimension (out_info, 0, dim);
  ml_tensors_info_get_tensor_size(out_info, 0, &data_size);

  /* test code for custom filter */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, filter_data_size, &custom);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_construct (pipeline, NULL, NULL, &pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (pipe, "sinkx", test_sink_callback_count,
      count_sink, &sink);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_handle (pipe, "srcx", &src);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (pipe);
  assert_eq (status, ML_ERROR_NONE);

  for (i = 0; i < 5; i++) {
    status = ml_tensors_data_create (in_info, &in_data);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_pipeline_src_input_data (src, in_data, ML_PIPELINE_BUF_POLICY_AUTO_FREE);
    assert_eq (status, ML_ERROR_NONE);

    g_usleep (50000); /* 50ms. Wait a bit. */
  }

  status = ml_pipeline_stop (pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (src);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sink);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_custom_easy_filter_unregister (custom);
  assert_eq (status, ML_ERROR_NONE);

  /* check received data in sink node */
  assert_gt (*count_sink, 0U);
  assert (*filter_data_size > 0U && *filter_data_size == data_size);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);
  g_free (pipeline);
  g_free (count_sink);
  g_free (filter_data_size);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n1
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter without filter name
 */
int utc_nnstreamer_capi_custom_filter_registration_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info, out_info;
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_register (NULL,
      in_info, out_info, test_custom_easy_cb, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n2
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter without input tensor info
 */
int utc_nnstreamer_capi_custom_filter_registration_n2 (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h out_info;
  int status;

  ml_tensors_info_create (&out_info);

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      NULL, out_info, test_custom_easy_cb, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n3
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter without output tensor info
 */
int utc_nnstreamer_capi_custom_filter_registration_n3 (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info;
  int status;

  ml_tensors_info_create (&in_info);

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, NULL, test_custom_easy_cb, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n4
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter without call back function
 */
int utc_nnstreamer_capi_custom_filter_registration_n4 (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info, out_info;
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, NULL, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n5
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter without filter handle
 */
int utc_nnstreamer_capi_custom_filter_registration_n5 (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_tensors_info_h in_info, out_info;
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, NULL, NULL);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n6
 * @since_tizen		6.0
 * @description		Negative test case of unregistering the custom filter
 */
int utc_nnstreamer_capi_custom_filter_registration_n6 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* test code with null param */
  status = ml_pipeline_custom_easy_filter_unregister (NULL);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n7
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter with invalid input info
 */
int utc_nnstreamer_capi_custom_filter_registration_n7 (void)
{
  IS_SUPPORT_FEATURE;
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info, out_info;
  ml_tensor_dimension dim = { 2, 1, 1, 1 };
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_FLOAT32);
  ml_tensors_info_set_tensor_dimension (out_info, 0, dim);

  /* test code with invalid input info */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n8
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter with invalid output info
 */
int utc_nnstreamer_capi_custom_filter_registration_n8 (void)
{
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom;
  ml_tensors_info_h in_info, out_info;
  ml_tensor_dimension dim = { 2, 1, 1, 1 };
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_INT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, dim);

  /* test code with invalid output info */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, NULL, &custom);
  assert_neq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_custom_filter_registration_n9
 * @since_tizen		6.0
 * @description		Negative test case of registering the custom filter with duplicated filter name
 */
int utc_nnstreamer_capi_custom_filter_registration_n9 (void)
{
  const char test_custom_filter[] = "test-custom-filter";
  ml_custom_easy_filter_h custom, custom2;
  ml_tensors_info_h in_info, out_info;
  ml_tensor_dimension dim = { 2, 1, 1, 1 };
  int status;

  ml_tensors_info_create (&in_info);
  ml_tensors_info_create (&out_info);

  ml_tensors_info_set_count (in_info, 1);
  ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_INT8);
  ml_tensors_info_set_tensor_dimension (in_info, 0, dim);

  ml_tensors_info_set_count (out_info, 1);
  ml_tensors_info_set_tensor_type (out_info, 0, ML_TENSOR_TYPE_FLOAT32);
  ml_tensors_info_set_tensor_dimension (out_info, 0, dim);

  /* test code for duplicated name */
  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, NULL, &custom);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_custom_easy_filter_register (test_custom_filter,
      in_info, out_info, test_custom_easy_cb, NULL, &custom2);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_custom_easy_filter_unregister (custom);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_destroy (in_info);
  ml_tensors_info_destroy (out_info);

  return 0;
}


/**
 * @function		test_if_custom_cb
 * @description		Invoke callback for tensor_if custom condition.
 */
static int
test_if_custom_cb (const ml_tensors_data_h data, const ml_tensors_info_h info, int *result, void *user_data)
{
  void *data_ptr;
  guint sum = 0, i;
  size_t data_size;

  ml_tensors_data_get_tensor_data (data, 0, &data_ptr, &data_size);

  for (i = 0; i < data_size; i++)
    sum += ((guint8 *) data_ptr)[i];

  /* Sum value 30 means that the sixth buffer has arrived.*/
  if (sum >= 30)
    *result = 0;
  else
    *result = 1;

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_registration_p
 * @since_tizen		6.5
 * @description		Positive test case of registering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_registration_p (void)
{
  IS_SUPPORT_FEATURE;
  const gchar *_tmpdir = g_get_tmp_dir ();
  const gchar *_dirname = "nns-tizen-XXXXXX";
  gchar *fullpath = g_build_path ("/", _tmpdir, _dirname, NULL);
  gchar *dir = g_mkdtemp ((gchar *)fullpath);
  gchar *file = g_build_path ("/", dir, "output", NULL);
  ml_pipeline_h pipe;
  ml_pipeline_src_h srchandle;
  ml_pipeline_sink_h sink_false;
  ml_pipeline_if_h custom;
  ml_tensors_info_h info;
  ml_tensors_data_h data;
  unsigned int count = 0;
  ml_tensor_type_e type = ML_TENSOR_TYPE_UNKNOWN;
  int status;
  uint8_t *uintarray[10];
  uint8_t *content = NULL;
  guint i;
  gsize len;
  gchar *pipeline = g_strdup_printf (
      "appsrc name=appsrc ! other/tensor,dimension=(string)4:1:1:1, type=(string)uint8,framerate=(fraction)0/1 ! "
      "tensor_if name=tif compared-value=CUSTOM compared-value-option=tif_custom_cb_name then=PASSTHROUGH else=PASSTHROUGH "
      "tif.src_0 ! queue ! filesink location=\"%s\" buffer-mode=unbuffered "
      "tif.src_1 ! queue ! tensor_sink name=sink_false sync=false async=false", file);

  guint *count_sink = (guint *)g_malloc0 (sizeof (guint));
  assert (count_sink);
  *count_sink = 0;

  /* test code for tensor_if custom */
  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, &custom);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_construct (pipeline, NULL, NULL, &pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_register (
      pipe, "sink_false", test_sink_callback_count, count_sink, &sink_false);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_get_handle (pipe, "appsrc", &srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_start (pipe);
  assert_eq (status, ML_ERROR_NONE);

  for (i = 0; i < 10; i++) {
    uintarray[i] = (uint8_t *)g_malloc (4);
    assert (uintarray[i]);
    uintarray[i][0] = i + 4;
    uintarray[i][1] = i + 1;
    uintarray[i][2] = i + 3;
    uintarray[i][3] = i + 2;
  }

  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  assert_eq (status, ML_ERROR_NONE);

  ml_tensors_info_get_count (info, &count);
  assert_eq (count, 1U);

  ml_tensors_info_get_tensor_type (info, 0, &type);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  status = ml_tensors_data_create (info, &data);
  assert_eq (status, ML_ERROR_NONE);

  /* Set tensor data and push buffers to source pad */
  for (i = 0; i < 10; i++) {
    status = ml_tensors_data_set_tensor_data (data, 0, uintarray[i], 4);
    assert_eq (status, ML_ERROR_NONE);

    status = ml_pipeline_src_input_data (srchandle, data, ML_PIPELINE_BUF_POLICY_DO_NOT_FREE);
    assert_eq (status, ML_ERROR_NONE);

    g_usleep (50000); /* 50ms. Wait a bit. */
  }

  status = ml_pipeline_stop (pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_sink_unregister (sink_false);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_destroy (pipe);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_tensor_if_custom_unregister (custom);
  assert_eq (status, ML_ERROR_NONE);

  assert_eq (g_file_get_contents (file, (gchar **)&content, &len, NULL), TRUE);
  assert_eq (len, 4U * 5);
  assert (content);

  /* Check if the TRUE path data is received correctly.  */
  if (content && len == 20) {
    for (i = 0; i < 5; i++) {
      assert_eq (content[i * 4 + 0], i + 4);
      assert_eq (content[i * 4 + 1], i + 1);
      assert_eq (content[i * 4 + 2], i + 3);
      assert_eq (content[i * 4 + 3], i + 2);
    }
  }
  g_free (content);

  /* The FALSE path receives 5 buffers. */
  assert_eq (*count_sink, 5U);

  for (i = 0; i < 10; i++) {
    g_free (uintarray[i]);
  }
  ml_tensors_info_destroy (info);
  ml_tensors_data_destroy (data);
  g_free (pipeline);
  g_free (count_sink);
  g_free (fullpath);
  g_free (file);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_registration_n1
 * @since_tizen		6.5
 * @description		Negative test case of registering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_registration_n1 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_if_h custom;
  int status;

  /* test code with null param */
  status = ml_pipeline_tensor_if_custom_register (NULL, test_if_custom_cb, NULL, &custom);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_registration_n2
 * @since_tizen		6.5
 * @description		Negative test case of registering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_registration_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_if_h custom;
  int status;

  /* test code with null param */
  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", NULL, NULL, &custom);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_registration_n3
 * @since_tizen		6.5
 * @description		Negative test case of registering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_registration_n3 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* test code with null param */
  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_registration_n4
 * @since_tizen		6.5
 * @description		Negative test case of registering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_registration_n4 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_if_h custom1, custom2;
  int status;

  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, &custom1);
  assert_eq (status, ML_ERROR_NONE);

  /* test to register tensor_if custom twice with same name */
  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, &custom2);
  assert_neq (status, ML_ERROR_NONE);

  status = ml_pipeline_tensor_if_custom_unregister (custom1);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}


/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_unregistration_p
 * @since_tizen		6.5
 * @description		Positive test case of unregistering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_unregistration_p (void)
{
  IS_SUPPORT_FEATURE;
  int status;
  ml_pipeline_if_h custom;

  /* register tensor if custom */
  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, &custom);
  assert_eq (status, ML_ERROR_NONE);

  /* unregister tensor if custom */
  status = ml_pipeline_tensor_if_custom_unregister (custom);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_unregistration_n1
 * @since_tizen		6.5
 * @description		Negative test case of unregistering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_unregistration_n1 (void)
{
  IS_SUPPORT_FEATURE;
  int status;

  /* test code with null param */
  status = ml_pipeline_tensor_if_custom_unregister (NULL);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_nnstreamer_capi_tensor_if_custom_unregistration_n2
 * @since_tizen		6.5
 * @description		Negative test case of unregistering the tensor_if custom condition
 */
int utc_nnstreamer_capi_tensor_if_custom_unregistration_n2 (void)
{
  IS_SUPPORT_FEATURE;
  ml_pipeline_if_h custom;
  int status;

  status = ml_pipeline_tensor_if_custom_register ("tif_custom_cb_name", test_if_custom_cb, NULL, &custom);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_tensor_if_custom_unregister (custom);
  assert_eq (status, ML_ERROR_NONE);

  /* test to unregister tensor_if custom twice */
  status = ml_pipeline_tensor_if_custom_unregister (custom);
  assert_neq (status, ML_ERROR_NONE);

  return 0;
}
