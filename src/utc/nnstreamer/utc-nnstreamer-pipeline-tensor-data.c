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
static ml_pipeline_src_h srchandle;
static ml_tensors_data_h data;
static ml_tensors_info_h info;

/**
 * @function		utc_nnstreamer_pipeline_tensor_data_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_tensor_data_startup(void)
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

  pipeline = g_strdup ("appsrc name=srcx ! other/tensor,dimension=(string)4:1:1:1,type=(string)uint8,framerate=(fraction)0/1 ! tensor_sink");
}

/**
 * @function		utc_nnstreamer_pipeline_tensor_data_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_tensor_data_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
  g_free (pipeline);
}

/**
 * @testcase		utc_ml_tensors_data_create_p
 * @since_tizen		5.5
 * @description		Test NNStreamer create tensor data
 */
int utc_ml_tensors_data_create_p (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  status = ml_pipeline_start (handle);
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  status = ml_pipeline_src_get_tensors_info (srchandle, &info);

  status = ml_tensors_data_create (info, &data);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  status = ml_pipeline_stop (handle);
  status = ml_pipeline_destroy (handle);
  status = ml_tensors_data_destroy (data);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_create_n
 * @since_tizen		5.5
 * @description		Test NNStreamer create tensor data, Failure case
 */
int utc_ml_tensors_data_create_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_data_create (NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_destroy_p
 * @since_tizen		5.5
 * @description		Test NNStreamer destroy tensor data
 */
int utc_ml_tensors_data_destroy_p (void)
{
  IS_SUPPORT_FEATURE;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  status = ml_pipeline_start (handle);
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  status = ml_tensors_data_create (info, &data);
  status = ml_pipeline_src_release_handle (srchandle);
  status = ml_pipeline_stop (handle);
  status = ml_pipeline_destroy (handle);

  status = ml_tensors_data_destroy (data);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_destroy_n
 * @since_tizen		5.5
 * @description		Test NNStreamer destroy tensor data, Failure case
 */
int utc_ml_tensors_data_destroy_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_data_destroy (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_set_tensor_data_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor data
 */
int utc_ml_tensors_data_set_tensor_data_p (void)
{
  IS_SUPPORT_FEATURE;
  uint8_t uintarray1[4] = {1, 1, 1, 1};

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  status = ml_pipeline_start (handle);
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  status = ml_tensors_data_create (info, &data);

  status = ml_tensors_data_set_tensor_data (data, 0, uintarray1, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  status = ml_pipeline_stop (handle);
  status = ml_pipeline_destroy (handle);
  status = ml_tensors_data_destroy (data);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_set_tensor_data_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor data, Failure case
 */
int utc_ml_tensors_data_set_tensor_data_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_data_set_tensor_data (NULL, 0, NULL, 0);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_get_tensor_data_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor data
 */
int utc_ml_tensors_data_get_tensor_data_p (void)
{
  IS_SUPPORT_FEATURE;
  void *data_ptr;
  size_t data_size;

  status = ml_pipeline_construct (pipeline, NULL, NULL, &handle);
  status = ml_pipeline_start (handle);
  status = ml_pipeline_src_get_handle (handle, "srcx", &srchandle);
  status = ml_pipeline_src_get_tensors_info (srchandle, &info);
  status = ml_tensors_data_create (info, &data);

  status = ml_tensors_data_get_tensor_data (data, 0, &data_ptr, &data_size);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_pipeline_src_release_handle (srchandle);
  status = ml_pipeline_stop (handle);
  status = ml_pipeline_destroy (handle);
  status = ml_tensors_data_destroy (data);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_data_get_tensor_data_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor data, Failure case
 */
int utc_ml_tensors_data_get_tensor_data_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_data_get_tensor_data (NULL, 0, NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}
