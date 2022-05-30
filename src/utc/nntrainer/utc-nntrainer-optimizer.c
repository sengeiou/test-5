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

#include "utc-nntrainer-common.h"

static int status;
static ml_train_optimizer_h opt;

/**
 * @function utc_nntrainer_optimizer_startup
 * @since_tizen 6.0
 * @description Called before each test case
 */
void utc_nntrainer_optimizer_startup(void)
{
  int ret = SYSTEM_INFO_ERROR_NONE;

  ret = check_feature();
  if (ret != SYSTEM_INFO_ERROR_NONE)
  {
    LOG_I("startup failed because checking feature failed."
          "Please note that tct can be run unexpectedly");
    return;
  }
}

/**
 * @function utc_nntrainer_optimizer_cleanup
 * @since_tizen 6.0
 * @description Called after each test case
 */
void utc_nntrainer_optimizer_cleanup(void)
{
  return;
}

/**
 * @function utc_nntrainer_optimizer_create_p
 * @since_tizen 6.0
 * @description create optimizer test
 */
int utc_nntrainer_optimizer_create_p(void)
{
  status = ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_SGD);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_optimizer_destroy(opt);

  return 0;
}

/**
 * @function utc_nntrainer_optimizer_create_n
 * @since_tizen 6.0
 * @description Test for creating unknown optimizer
 */
int utc_nntrainer_optimizer_create_n(void)
{
  status = ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_UNKNOWN);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  return 0;
}

/**
 * @function utc_nntrainer_optimizer_destory_p
 * @since_tizen 6.0
 * @description Test for destroying optimizer
 */
int utc_nntrainer_optimizer_destroy_p(void)
{
  ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_SGD);
  status = ml_train_optimizer_destroy(opt);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  return 0;
}

/**
 * @function utc_nntrainer_optimizer_destroy_n
 * @since_tizen 6.0
 * @description Test for destroying optimizer that is passed to model
 */
int utc_nntrainer_optimizer_destroy_n(void)
{
  ml_train_model_h model;
  ml_train_model_construct(&model);
  ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_ADAM);

  ml_train_model_set_optimizer(model, opt);

  status = ml_train_optimizer_destroy(opt);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_optimizer_set_property_p
 * @since_tizen 6.0
 * @description Test for setting property
 */
int utc_nntrainer_optimizer_set_property_p(void)
{
  ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
  status = ml_train_optimizer_set_property(opt, "beta1=0.002", "beta2=0.001", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_optimizer_destroy(opt);
  return 0;
}

/**
 * @function utc_nntrainer_optimizer_set_property_n
 * @since_tizen 6.0
 * @description Test for setting invalid property
 */
int utc_nntrainer_optimizer_set_property_n(void)
{
  ml_train_optimizer_create(&opt, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
  status = ml_train_optimizer_set_property(opt, "invalid_property_key=invalid_property_value", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }
  ml_train_optimizer_destroy(opt);

  return 0;
}
