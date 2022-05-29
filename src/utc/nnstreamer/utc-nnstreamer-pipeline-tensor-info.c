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
static ml_tensors_info_h info;

/**
 * @function		utc_nnstreamer_pipeline_tensor_info_startup
 * @since_tizen		5.5
 * @description		called before the specific test cases
 */
void utc_nnstreamer_pipeline_tensor_info_startup(void)
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
 * @function		utc_nnstreamer_pipeline_tensor_info_cleanup
 * @since_tizen		5.5
 * @description		called after the specific test cases
 */
void utc_nnstreamer_pipeline_tensor_info_cleanup(void)
{
  if (!feature_ml || !feature_ml_inf) {
    return;
  }
}

/**
 * @testcase		utc_ml_tensors_info_create_p
 * @since_tizen		5.5
 * @description		Test NNStreamer create tensor info
 */
int utc_ml_tensors_info_create_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_create_n
 * @since_tizen		5.5
 * @description		Test NNStreamer create tensor info, Failure case
 */
int utc_ml_tensors_info_create_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_destroy_p
 * @since_tizen		5.5
 * @description		Test NNStreamer destroy tensor info
 */
int utc_ml_tensors_info_destroy_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_destroy_n
 * @since_tizen		5.5
 * @description		Test NNStreamer destroy tensor info, Failure case
 */
int utc_ml_tensors_info_destroy_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_destroy (NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_validate_p
 * @since_tizen		5.5
 * @description		Test NNStreamer validate tensor info
 */
int utc_ml_tensors_info_validate_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h t_info;
  ml_tensor_dimension t_dim;
  bool valid = false;

  status = ml_tensors_info_create (&t_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (t_info, 1);
  assert_eq (status, ML_ERROR_NONE);

  t_dim[0] = 10;
  t_dim[1] = 1;
  t_dim[2] = 1;
  t_dim[3] = 1;

  status = ml_tensors_info_set_tensor_type (t_info, 0, ML_TENSOR_TYPE_INT16);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_dimension (t_info, 0, t_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_validate (t_info, &valid);
  assert_eq (status, ML_ERROR_NONE);
  assert (valid);

  status = ml_tensors_info_destroy (t_info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_validate_n
 * @since_tizen		5.5
 * @description		Test NNStreamer validate tensor info, Failure case
 */
int utc_ml_tensors_info_validate_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_validate (NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_clone_p
 * @since_tizen		5.5
 * @description		Test NNStreamer clone tensor info
 */
int utc_ml_tensors_info_clone_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensors_info_h in_info, out_info;
  guint count = 0;
  ml_tensor_dimension in_dim, out_dim;
  ml_tensor_type_e type = ML_TENSOR_TYPE_UNKNOWN;

  status = ml_tensors_info_create (&in_info);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_create (&out_info);
  assert_eq (status, ML_ERROR_NONE);

  in_dim[0] = 5;
  in_dim[1] = 1;
  in_dim[2] = 1;
  in_dim[3] = 1;

  status = ml_tensors_info_set_count (in_info, 1);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_set_tensor_type (in_info, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_set_tensor_dimension (in_info, 0, in_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_clone (out_info, in_info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (out_info, &count);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (count, 1U);

  status = ml_tensors_info_get_tensor_type (out_info, 0, &type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (type, ML_TENSOR_TYPE_UINT8);

  status = ml_tensors_info_get_tensor_dimension (out_info, 0, out_dim);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (in_dim[0], out_dim[0]);
  assert_eq (in_dim[1], out_dim[1]);
  assert_eq (in_dim[2], out_dim[2]);
  assert_eq (in_dim[3], out_dim[3]);

  status = ml_tensors_info_destroy (in_info);
  assert_eq (status, ML_ERROR_NONE);
  status = ml_tensors_info_destroy (out_info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_clone_n
 * @since_tizen		5.5
 * @description		Test NNStreamer clone tensor info, Failure case
 */
int utc_ml_tensors_info_clone_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_clone (NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_count_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor info count
 */
int utc_ml_tensors_info_set_count_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 2);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_count_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor info count, Failure case
 */
int utc_ml_tensors_info_set_count_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (NULL, 2);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_count_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor info count
 */
int utc_ml_tensors_info_get_count_p (void)
{
  unsigned int num = 0;

  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 2);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (info, &num);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (num, 2);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_count_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor info count, Failure case
 */
int utc_ml_tensors_info_get_count_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_count (NULL, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_name_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor name
 */
int utc_ml_tensors_info_set_tensor_name_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_name (info, 0, "tensor-name-test");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_name_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor name, Failure case
 */
int utc_ml_tensors_info_set_tensor_name_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_name (NULL, 1, "tensor-name-test");
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_name_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor name
 */
int utc_ml_tensors_info_get_tensor_name_p (void)
{
  gchar * out_name = NULL;

  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_name (info, 0, "tensor-name-test");
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_name (info, 0, &out_name);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  g_free (out_name);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_name_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor name, Failure case
 */
int utc_ml_tensors_info_get_tensor_name_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_name (NULL, 0, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_type_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor type
 */
int utc_ml_tensors_info_set_tensor_type_p (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_type_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor type, Failure case
 */
int utc_ml_tensors_info_set_tensor_type_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (NULL, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_type_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor type
 */
int utc_ml_tensors_info_get_tensor_type_p (void)
{
  ml_tensor_type_e out_type;

  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_type (info, 0, &out_type);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_type, ML_TENSOR_TYPE_UINT8);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_type_n
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor type, Failure case
 */
int utc_ml_tensors_info_get_tensor_type_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_type (NULL, 0, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_dimension_p
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor dimension
 */
int utc_ml_tensors_info_set_tensor_dimension_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensor_dimension in_dim;

  in_dim[0] = 3;
  in_dim[1] = 300;
  in_dim[2] = 300;
  in_dim[3] = 1;

  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_dimension (info, 0, in_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_set_tensor_dimension_n
 * @since_tizen		5.5
 * @description		Test NNStreamer set tensor dimension, Failure case
 */
int utc_ml_tensors_info_set_tensor_dimension_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_dimension (NULL, 1, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_dimension_p
 * @since_tizen		5.5
 * @description		Test NNStreamer get tensor dimension, Failure case
 */
int utc_ml_tensors_info_get_tensor_dimension_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensor_dimension in_dim, out_dim;

  in_dim[0] = 3;
  in_dim[1] = 300;
  in_dim[2] = 300;
  in_dim[3] = 1;

  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_dimension (info, 0, in_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_dimension (info, 0, out_dim);
  assert_eq (status, ML_ERROR_NONE);
  assert_eq (out_dim[0], 3U);
  assert_eq (out_dim[1], 300U);
  assert_eq (out_dim[2], 300U);
  assert_eq (out_dim[3], 1U);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_dimension_n
 * @since_tizen		5.5
  * @description		Test NNStreamer get tensor dimension, Failure case
 */
int utc_ml_tensors_info_get_tensor_dimension_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_dimension (NULL, 1, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_size_p
 * @since_tizen		5.5
  * @description		Test NNStreamer getting the byte size of the given handle of tensors information.
 */
int utc_ml_tensors_info_get_tensor_size_p (void)
{
  IS_SUPPORT_FEATURE;
  ml_tensor_dimension in_dim;
  size_t data_size;

  in_dim[0] = 3;
  in_dim[1] = 300;
  in_dim[2] = 300;
  in_dim[3] = 1;

  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_count (info, 1);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_type (info, 0, ML_TENSOR_TYPE_UINT8);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_set_tensor_dimension (info, 0, in_dim);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_size (info, 0, &data_size);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}

/**
 * @testcase		utc_ml_tensors_info_get_tensor_size_n
 * @since_tizen		5.5
  * @description		Test NNStreamer getting the byte size of the given handle of tensors information, Failure case
 */
int utc_ml_tensors_info_get_tensor_size_n (void)
{
  IS_SUPPORT_FEATURE;
  status = ml_tensors_info_create (&info);
  assert_eq (status, ML_ERROR_NONE);

  status = ml_tensors_info_get_tensor_size (NULL, 0, NULL);
  assert_eq (status, ML_ERROR_INVALID_PARAMETER);

  status = ml_tensors_info_destroy (info);
  assert_eq (status, ML_ERROR_NONE);

  return 0;
}
