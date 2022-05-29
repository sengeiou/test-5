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
static ml_train_dataset_h dataset;

/**
 * @function utc_nntrainer_dataset_startup
 * @since_tizen 6.0
 * @description Called before each test case
 */
void utc_nntrainer_dataset_startup(void)
{
  int ret = SYSTEM_INFO_ERROR_NONE;
  if (init_path() < 0)
  {
    LOG_I("initiating path failed");
    return;
  }

  ret = check_feature();
  if (ret != SYSTEM_INFO_ERROR_NONE)
  {
    LOG_I("startup failed because checking feature failed."
          "Please note that tct can be run unexpectedly");
    return;
  }
}

/**
 * @function utc_nntrainer_dataset_cleanup
 * @since_tizen 6.0
 * @description Called after each test case
 */
void utc_nntrainer_dataset_cleanup(void)
{
  return;
}

/**
 * @function utc_nntrainer_dataset_create_file_p
 * @since_tizen 6.0
 * @description Test for successfully creating dataset from file
 */
int utc_nntrainer_dataset_create_file_p(void)
{
  status = ml_train_dataset_create_with_file(&dataset, train_path, val_path, test_path);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_create_file_n
 * @since_tizen 6.0
 * @description Test for fail to create dataset
 */
int utc_nntrainer_dataset_create_file_n(void)
{
  status = ml_train_dataset_create_with_file(&dataset, NULL, val_path, test_path);
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
 * @function utc_nntrainer_dataset_create_generator_p
 * @since_tizen 6.0
 * @description Test for create dataset with generator
 */
int utc_nntrainer_dataset_create_generator_p(void)
{
  status = ml_train_dataset_create_with_generator(&dataset, constant_generator_cb, constant_generator_cb, constant_generator_cb);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_create_generator_n
 * @since_tizen 6.0
 * @description Test for fail to create dataset with generator
 */
int utc_nntrainer_dataset_create_generator_n(void)
{
  status = ml_train_dataset_create_with_generator(&dataset, NULL, NULL, NULL);
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
 * @function utc_nntrainer_dataset_destroy_p
 * @since_tizen 6.0
 * @description Test for destroy dataset
 */
int utc_nntrainer_dataset_destroy_p(void)
{
  ml_train_dataset_create_with_generator(&dataset, constant_generator_cb, constant_generator_cb, constant_generator_cb);

  status = ml_train_dataset_destroy(dataset);
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
 * @function utc_nntrainer_dataset_destroy_n
 * @since_tizen 6.0
 * @description Test for destroying dataset that is passed to model
 */
int utc_nntrainer_dataset_destroy_n(void)
{
  ml_train_model_h model;
  ml_train_model_construct(&model);
  ml_train_dataset_create_with_generator(&dataset, constant_generator_cb, NULL, NULL);

  ml_train_model_set_dataset(model, dataset);

  status = ml_train_dataset_destroy(dataset);
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
 * @function utc_nntrainer_dataset_set_property_p
 * @since_tizen 6.0
 * @description Test for dataset set property
 */
int utc_nntrainer_dataset_set_property_p(void)
{
  ml_train_dataset_create_with_file(&dataset, train_path, val_path, test_path);

  status = ml_train_dataset_set_property(dataset, "buffer_size=100", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_set_property_n
 * @since_tizen 6.0
 * @description Test for dataset set property negative
 */
int utc_nntrainer_dataset_set_property_n(void)
{
  ml_train_dataset_create_with_file(&dataset, train_path, val_path, test_path);

  status = ml_train_dataset_set_property(dataset, "invalid_key=invalid_value", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);
  return 0;
}

/**
 * @function utc_nntrainer_dataset_create_p
 * @since_tizen 6.5
 * @description Test for successfully create dataset
 */
int utc_nntrainer_dataset_create_p(void)
{
  status = ml_train_dataset_create(&dataset);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_create_n
 * @since_tizen 6.5
 * @description Test for fail to create dataset
 */
int utc_nntrainer_dataset_create_n(void)
{
  status = ml_train_dataset_create(NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_p
 * @since_tizen 6.5
 * @description Test for adding generator to dataset
 */
int utc_nntrainer_dataset_add_generator_p(void)
{
  ml_train_dataset_create(&dataset);

  ml_train_dataset_mode_e mode[3] = {
    ML_TRAIN_DATASET_MODE_TRAIN, ML_TRAIN_DATASET_MODE_VALID, ML_TRAIN_DATASET_MODE_TEST};

  for (unsigned int i = 0; i < 3; ++i) {
    status = ml_train_dataset_add_generator(dataset, mode[i], constant_generator_cb, NULL);
    if (train_supported == false)
    {
      assert_eq(status, ML_ERROR_NOT_SUPPORTED);
    }
    else
    {
      assert_eq(status, ML_ERROR_NONE);
    }
  }
  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_train_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding train dataset generator to NULL dataset
 */
int utc_nntrainer_dataset_add_generator_train_dataset_n1(void)
{
  status = ml_train_dataset_add_generator(NULL, ML_TRAIN_DATASET_MODE_TRAIN,
                                          constant_generator_cb, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_train_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding NULL train dataset generator
 */
int utc_nntrainer_dataset_add_generator_train_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_generator(dataset, ML_TRAIN_DATASET_MODE_TRAIN,
                                          NULL, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_valid_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding validation dataset generator to NULL dataset
 */
int utc_nntrainer_dataset_add_generator_valid_dataset_n1(void)
{
  status = ml_train_dataset_add_generator(NULL, ML_TRAIN_DATASET_MODE_VALID,
                                          constant_generator_cb, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_valid_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding NULL validation dataset generator
 */
int utc_nntrainer_dataset_add_generator_valid_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_generator(dataset, ML_TRAIN_DATASET_MODE_VALID,
                                          NULL, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_test_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding test dataset generator to NULL dataset
 */
int utc_nntrainer_dataset_add_generator_test_dataset_n1(void)
{
  status = ml_train_dataset_add_generator(NULL, ML_TRAIN_DATASET_MODE_TEST,
                                          constant_generator_cb, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_generator_test_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding NULL test dataset generator
 */
int utc_nntrainer_dataset_add_generator_test_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_generator(dataset, ML_TRAIN_DATASET_MODE_TEST,
                                          NULL, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_p
 * @since_tizen 6.5
 * @description Test for adding data file to dataset
 */
int utc_nntrainer_dataset_add_file_p(void)
{
  ml_train_dataset_create(&dataset);

  ml_train_dataset_mode_e mode[3] = {
    ML_TRAIN_DATASET_MODE_TRAIN, ML_TRAIN_DATASET_MODE_VALID, ML_TRAIN_DATASET_MODE_TEST};

  for (unsigned int i = 0; i < 3; ++i) {
    status = ml_train_dataset_add_file(dataset, mode[i], train_path);
    if (train_supported == false)
    {
      assert_eq(status, ML_ERROR_NOT_SUPPORTED);
    }
    else
    {
      assert_eq(status, ML_ERROR_NONE);
    }
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_train_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding train dataset data file to NULL dataset
 */
int utc_nntrainer_dataset_add_file_train_dataset_n1(void)
{
  status = ml_train_dataset_add_file(NULL, ML_TRAIN_DATASET_MODE_TRAIN, train_path);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_train_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding train dataset data file with NULL file path
 */
int utc_nntrainer_dataset_add_file_train_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_file(dataset, ML_TRAIN_DATASET_MODE_TRAIN, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_valid_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding validation dataset data file to NULL dataset
 */
int utc_nntrainer_dataset_add_file_valid_dataset_n1(void)
{
  status = ml_train_dataset_add_file(NULL, ML_TRAIN_DATASET_MODE_VALID, train_path);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_valid_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding validation dataset data file with NULL file path
 */
int utc_nntrainer_dataset_add_file_valid_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_file(dataset, ML_TRAIN_DATASET_MODE_VALID, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_test_dataset_n1
 * @since_tizen 6.5
 * @description Test for adding test dataset data file to NULL dataset
 */
int utc_nntrainer_dataset_add_file_test_dataset_n1(void)
{
  status = ml_train_dataset_add_file(NULL, ML_TRAIN_DATASET_MODE_TEST, train_path);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_add_file_test_dataset_n2
 * @since_tizen 6.5
 * @description Test for adding test dataset data file with NULL file path
 */
int utc_nntrainer_dataset_add_file_test_dataset_n2(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_add_file(dataset, ML_TRAIN_DATASET_MODE_TEST, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_set_property_for_mode_p
 * @since_tizen 6.5
 * @description Test for dataset set property for mode
 */
int utc_nntrainer_dataset_set_property_for_mode_p(void)
{
  ml_train_dataset_create(&dataset);

  ml_train_dataset_add_generator(dataset, ML_TRAIN_DATASET_MODE_TRAIN, constant_generator_cb, NULL);

  status = ml_train_dataset_set_property_for_mode(
    dataset, ML_TRAIN_DATASET_MODE_TRAIN, "buffer_size=1", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}

/**
 * @function utc_nntrainer_dataset_set_property_for_mode_n
 * @since_tizen 6.5
 * @description Test for dataset set property for mode with empty mode
 */
int utc_nntrainer_dataset_set_property_for_mode_n(void)
{
  ml_train_dataset_create(&dataset);

  status = ml_train_dataset_set_property_for_mode(
    dataset, ML_TRAIN_DATASET_MODE_TRAIN, "buffer_size=1", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_dataset_destroy(dataset);

  return 0;
}
