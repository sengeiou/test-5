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

#ifndef __UTC_NNTRAINER_COMMON__
#define __UTC_NNTRAINER_COMMON__

#define FEATURE_ML_TRAIN "http://tizen.org/feature/machine_learning.training"

#include "tct_common.h"

#include <system_info.h>
#include <nntrainer.h>
#include <dlog.h>
#include <limits.h>

#include <app.h>

#define LABEL_PATH "label.dat"
#define CONF_PATH "model.ini"
#define TESTSET_PATH "trainingSet.dat"
#define TRAININGSET_PATH "trainingSet.dat"
#define VALSET_PATH "trainingSet.dat"
#define BIN_PATH "bin.bin"

#define FEATURE_SIZE 100
#define NUM_CLASS 10

static bool train_supported;
static char label_path[PATH_MAX];
static char train_path[PATH_MAX];
static char test_path[PATH_MAX];
static char val_path[PATH_MAX];
static char bin_path[PATH_MAX];
static char conf_path[PATH_MAX];

#define LOG_I(fmt, args...)                                                              \
  {                                                                                      \
    dlog_print(DLOG_INFO, "NNTRAINER", "[%s:%d] " fmt "\n", __func__, __LINE__, ##args); \
  }

/**
 * @function check_feature
 * @since_tizen 6.0
 * @description check and set *_supported on success
 */
static int check_feature()
{
  int status = SYSTEM_INFO_ERROR_NONE;

  status = system_info_get_platform_bool(FEATURE_ML_TRAIN, &train_supported);
  if (status != SYSTEM_INFO_ERROR_NONE)
  {
    train_supported = false;
    LOG_I("checking feature failed!");
    return status;
  }

  return status;
}

/**
 * @function get_full_path of resource
 * @since_tizen 6.0
 * @description get
 *
 * @param[in] file
 * @param[out] full_path
 * @return status
 */
static int res_path_(const char *file, char *full_path)
{
  char *root_path;
  root_path = app_get_resource_path();

  memset(full_path, 0, PATH_MAX);

  if (root_path == NULL)
  {
    LOG_I("failed to get resource path");
    return -1;
  }

  if (full_path == NULL)
  {
    LOG_I("full_path is null");
    free(root_path);
    return -1;
  }

  snprintf(full_path, PATH_MAX, "%s%s", root_path, file);
  LOG_I("resource path: %s", full_path);
  free(root_path);

  return 0;
}

/**
 * @function get_full_path of data path
 * @since_tizen 6.5
 * @description get
 *
 * @param[in] file
 * @param[out] full_path
 * @return status
 */
static int data_path_(const char *file, char *full_path)
{
  char *root_path;
  root_path = app_get_data_path();

  memset(full_path, 0, PATH_MAX);

  if (root_path == NULL)
  {
    LOG_I("failed to get data path");
    return -1;
  }

  if (full_path == NULL)
  {
    LOG_I("full_path is null");
    free(root_path);
    return -1;
  }

  snprintf(full_path, PATH_MAX, "%s%s", root_path, file);
  LOG_I("data path: %s", full_path);
  free(root_path);

  return 0;
}

/**
 * @function init_path
 * @since_tizen 6.0
 * @description init resource paths;
 */
static int init_path()
{
  if (res_path_(LABEL_PATH, label_path) < 0)
    return -1;

  if (res_path_(CONF_PATH, conf_path) < 0)
    return -1;

  if (res_path_(TRAININGSET_PATH, train_path) < 0)
    return -1;

  if (res_path_(TESTSET_PATH, test_path) < 0)
    return -1;

  if (res_path_(VALSET_PATH, val_path) < 0)
    return -1;

  if (data_path_(BIN_PATH, bin_path) < 0)
    return -1;

  char *res_path = app_get_resource_path();

  if (chdir(res_path) < 0)
  {
    free(res_path);
    return -1;
  };
  free(res_path);
  return 0;
}

/**
 * @function Constant generator cb
 * @since_tizen 6.0
 *
 * @param outVec dataset information
 * @param outLabel label information
 * @param last whether it is last
 * @param user_data user data
 * @return int error code
 */
static int constant_generator_cb(float **outVec, float **outLabel, bool *last,
                                 void *user_data)
{
  static int count = 0;
  unsigned int i, j;
  unsigned int data_size = FEATURE_SIZE;

  for (i = 0; i < data_size; ++i)
  {
    outVec[0][i] = 0.0f;
  }


  outLabel[0][0] = 1.0f;
  for (j = 1; j < NUM_CLASS; ++j)
  {
    outLabel[0][j] = 0.0f;
  }

  if (count == 10)
  {
    *last = true;
    count = 0;
  }
  else
  {
    *last = false;
    count++;
  }

  LOG_I("generator called");

  return ML_ERROR_NONE;
}

#define FEATURE_CHECK_AND_ASSERT(status, errno)    \
  do                                               \
  {                                                \
    {                                              \
      if (train_supported == false)                \
      {                                            \
        assert_eq(status, ML_ERROR_NOT_SUPPORTED); \
      }                                            \
      else                                         \
      {                                            \
        assert_eq(status, errno);                  \
      }                                            \
    }                                              \
  } while (0);

#define ASSERT_STATUS(errno) FEATURE_CHECK_AND_ASSERT(status, errno)

#endif // UTC_NNTRAINER_COMMON
