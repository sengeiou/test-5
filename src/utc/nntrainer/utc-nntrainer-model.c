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
#include <string.h>

static int status;
static ml_train_model_h model;
static ml_train_layer_h layers[2];
static ml_train_optimizer_h adam;
static ml_train_dataset_h dataset;
static ml_tensors_info_h input_info, output_info;

/**
 * @function utc_nntrainer_model_startup
 * @since_tizen 6.0
 * @description Called before each test case
 */
void utc_nntrainer_model_startup(void)
{
  if (init_path() < 0)
    LOG_I("initiating path failed");

  check_feature();

  ml_train_layer_create(&layers[0], ML_TRAIN_LAYER_TYPE_INPUT);
  ml_train_layer_set_property(layers[0], "input_shape=1:1:100",
                              "normalization=true",
                              "name=input_layer", NULL);

  ml_train_layer_create(&layers[1], ML_TRAIN_LAYER_TYPE_FC);
  ml_train_layer_set_property(
      layers[1], "unit=10", "activation=softmax", "bias_initializer=zeros",
      "weight_regularizer=l2norm",
      "weight_regularizer_constant=0.005",
      "weight_initializer=xavier_uniform",
      "name=fc100",
      "input_layers=input_layer", NULL);

  ml_train_optimizer_create(&adam, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
  ml_train_optimizer_set_property(
      adam, "learning_rate=0.0001", "decay_rate=0.96", "decay_steps=1000",
      "beta1=0.002", "beta2=0.001", "epsilon=1e-7", NULL);

  ml_train_dataset_create_with_file(&dataset, train_path, NULL, NULL);
}

/**
 * @function utc_nntrainer_model_cleanup
 * @since_tizen 6.0
 * @description Called after each test case
 */
void utc_nntrainer_model_cleanup(void)
{
  ml_train_layer_destroy(layers[0]);
  ml_train_layer_destroy(layers[1]);

  ml_train_optimizer_destroy(adam);
  ml_train_dataset_destroy(dataset);
  return;
}

/**
 * @function utc_nntrainer_model_construct_p
 * @since_tizen 6.0
 * @description construct model test
 */
int utc_nntrainer_model_construct_p(void)
{
  status = ml_train_model_construct(&model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_construct_n
 * @since_tizen 6.0
 * @description construct model test
 */
int utc_nntrainer_model_construct_n(void)
{
  status = ml_train_model_construct(NULL);
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
 * @function utc_nntrainer_model_construct_with_conf_p
 * @since_tizen 6.0
 * @description construct model test construct with conf
 */
int utc_nntrainer_model_construct_with_conf_p(void)
{
  status = ml_train_model_construct_with_conf(conf_path, &model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_construct_with_conf_n
 * @since_tizen 6.0
 * @description construct model test construct with conf
 */
int utc_nntrainer_model_construct_with_conf_n(void)
{
  status = ml_train_model_construct_with_conf("wrong_path.ini", &model);
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
 * @function utc_nntrainer_model_destroy_p
 * @since_tizen 6.0
 * @description destroy model test
 */
int utc_nntrainer_model_destroy_p(void)
{
  ml_train_model_construct(&model);

  status = ml_train_model_destroy(model);
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
 * @function utc_nntrainer_model_destroy_n
 * @since_tizen 6.0
 * @description destroy model test
 */
int utc_nntrainer_model_destroy_n(void)
{
  status = ml_train_model_destroy(NULL);
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
 * @function utc_nntrainer_model_add_layer_p
 * @since_tizen 6.0
 * @description test for add_layer
 */
int utc_nntrainer_model_add_layer_p(void)
{

  ml_train_model_construct(&model);
  status = ml_train_model_add_layer(model, layers[0]);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_add_layer_n1
 * @since_tizen 6.0
 * @description test for add_layer twice with same name
 */
int utc_nntrainer_model_add_layer_n1(void)
{

  ml_train_model_construct(&model);
  ml_train_model_add_layer(model, layers[1]);

  status = ml_train_model_add_layer(model, layers[1]);
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
 * @function utc_nntrainer_model_add_layer_n2
 * @since_tizen 6.0
 * @description test for add_layer owned by other model
 */
int utc_nntrainer_model_add_layer_n2(void)
{
  ml_train_model_h other_model;
  ml_train_model_construct(&other_model);
  ml_train_model_add_layer(other_model, layers[1]);

  status = ml_train_model_add_layer(model, layers[1]);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_model_destroy(model);
  ml_train_model_destroy(other_model);

  return 0;
}

/**
 * @function utc_nntrainer_model_set_optimizer_p
 * @since_tizen 6.0
 * @description test for set_optimizer
 */
int utc_nntrainer_model_set_optimizer_p(void)
{
  ml_train_model_construct(&model);
  status = ml_train_model_set_optimizer(model, adam);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_set_optimizer_n1
 * @since_tizen 6.0
 * @description test for set_optimizer owned by other model
 */
int utc_nntrainer_model_set_optimizer_n1(void)
{
  ml_train_model_h other_model;
  ml_train_model_construct(&other_model);

  ml_train_model_set_optimizer(other_model, adam);

  ml_train_model_construct(&model);
  status = ml_train_model_set_optimizer(model, adam);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_model_destroy(model);
  ml_train_model_destroy(other_model);

  return 0;
}

/**
 * @function utc_nntrainer_model_set_optimizer_n2
 * @since_tizen 6.0
 * @description test for set_optimizer passing null
 */
int utc_nntrainer_model_set_optimizer_n2(void)
{

  ml_train_model_construct(&model);
  status = ml_train_model_set_optimizer(model, NULL);
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
 * @function utc_nntrainer_model_set_dataset_p
 * @since_tizen 6.0
 * @description test for set_dataset
 */
int utc_nntrainer_model_set_dataset_p(void)
{

  ml_train_model_construct(&model);
  status = ml_train_model_set_dataset(model, dataset);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_set_dataset_n1
 * @since_tizen 6.0
 * @description test for set_dataset owned by other model
 */
int utc_nntrainer_model_set_dataset_n1(void)
{
  ml_train_model_h other_model;
  ml_train_model_construct(&other_model);

  ml_train_model_set_dataset(other_model, dataset);

  ml_train_model_construct(&model);
  status = ml_train_model_set_dataset(model, dataset);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  ml_train_model_destroy(model);
  ml_train_model_destroy(other_model);

  return 0;
}

/**
 * @function utc_nntrainer_model_set_dataset_n2
 * @since_tizen 6.0
 * @description test for set_dataset passing null
 */
int utc_nntrainer_model_set_dataset_n2(void)
{

  ml_train_model_construct(&model);
  status = ml_train_model_set_dataset(model, NULL);
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
 * @function utc_nntrainer_model_get_summary_p
 * @since_tizen 6.0
 * @description test for get summary
 */
int utc_nntrainer_model_get_summary_p(void)
{
  ml_train_model_construct(&model);
  ml_train_model_add_layer(model, layers[0]);
  ml_train_model_compile(model, NULL);

  char *sum = NULL;
  status = ml_train_model_get_summary(model, ML_TRAIN_SUMMARY_TENSOR, &sum);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  if (sum)
    free(sum);

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_get_summary_n
 * @since_tizen 6.0
 * @description test for get summary
 */
int utc_nntrainer_model_get_summary_n(void)
{
  ml_train_model_construct(&model);
  ml_train_model_compile(model, NULL);

  status = ml_train_model_get_summary(model, ML_TRAIN_SUMMARY_TENSOR, NULL);
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
 * @function utc_nntrainer_model_compile_p
 * @since_tizen 6.0
 * @description test for model compile
 */
int utc_nntrainer_model_compile_p(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);

  status = ml_train_model_compile(model, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_compile_n
 * @since_tizen 6.0
 * @description test for model compile with invalid parameter
 */
int utc_nntrainer_model_compile_n(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);

  status = ml_train_model_compile(model, "invalid_parameter=should_fail", NULL);
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
 * @function utc_nntrainer_model_run_p1
 * @since_tizen 6.0
 * @description test for model run with file
 */
int utc_nntrainer_model_run_p1(void)
{
  const char * data_path = app_get_data_path();
  char model_prop_path[PATH_MAX];

  if (snprintf(model_prop_path, PATH_MAX, "save_path=%s%s", data_path, "model.bin") < 0) {
    free((char *)data_path);
    LOG_I("getting save path property failed");
    return 1;
  }
  free((char *)data_path);

  ml_train_model_construct_with_conf(conf_path, &model);

  ml_train_model_compile(model, NULL);

  status = ml_train_model_run(model, model_prop_path, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_run_p2
 * @since_tizen 6.0
 * @description test for model run with generator dataset
 */
int utc_nntrainer_model_run_p2(void)
{
  ml_train_dataset_h dataset;
  ml_train_optimizer_h optimizer;

  ml_train_model_construct(&model);
  ml_train_dataset_create_with_generator(&dataset, constant_generator_cb, NULL, NULL);

  ml_train_dataset_set_property(dataset, "buffer_size=9", NULL);
  ml_train_model_set_dataset(model, dataset);

  ml_train_optimizer_create(&optimizer, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
  ml_train_optimizer_set_property(
      optimizer, "learning_rate=0.0001", "decay_rate=0.96", "decay_steps=1000",
      "beta1=0.9", "beta2=0.9999", "epsilon=1e-7", NULL);

  ml_train_model_set_optimizer(model, optimizer);

  ml_train_model_add_layer(model, layers[0]);
  ml_train_model_add_layer(model, layers[1]);

  ml_train_model_compile(model, "loss=cross", "batch_size=9", NULL);

  status = ml_train_model_run(model, "epochs=1", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_run_n
 * @since_tizen 6.0
 * @description test for model run without compile
 */
int utc_nntrainer_model_run_n(void)
{
  ml_train_model_construct(&model);

  status = ml_train_model_run(model, NULL);
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
 * @function utc_nntrainer_model_get_input_tensors_info_p
 * @since_tizen 6.5
 * @description test for get info of model's input tensors
 */
int utc_nntrainer_model_get_input_tensors_info_p(void)
{
  unsigned int input_count;
  unsigned int input_dim_expected[4] = {2, 1, 1, 1280};
  unsigned int dim[4];

  ml_train_model_construct_with_conf(conf_path, &model);
  ml_train_model_compile(model, NULL);

  status = ml_train_model_get_input_tensors_info(model, &input_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_tensors_info_get_count(input_info, &input_count);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    assert_eq(input_count, 1ul);
  }

  status = ml_tensors_info_get_tensor_dimension(input_info, 0, dim);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    for (unsigned int i = 0; i < 4; ++i) {
      assert_eq(dim[i], input_dim_expected[i]);
    }
  }

  ml_tensors_info_destroy(input_info);
  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_get_input_tensors_info_n1
 * @since_tizen 6.5
 * @description test for get info of model's input tensors without model
 */
int utc_nntrainer_model_get_input_tensors_info_n1(void)
{
  status = ml_train_model_get_input_tensors_info(NULL, &input_info);
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
 * @function utc_nntrainer_model_get_input_tensors_info_n2
 * @since_tizen 6.5
 * @description test for get info of model's input tensors without model compile
 */
int utc_nntrainer_model_get_input_tensors_info_n2(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);

  status = ml_train_model_get_input_tensors_info(model, &input_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_get_input_tensors_info_n3
 * @since_tizen 6.5
 * @description test for get info of model's input tensors with destroyed model
 */
int utc_nntrainer_model_get_input_tensors_info_n3(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);
  ml_train_model_compile(model, NULL);
  ml_train_model_destroy(model);

  status = ml_train_model_get_input_tensors_info(model, &input_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }

  return 0;
}

/**
 * @function utc_nntrainer_model_get_output_tensors_info_p
 * @since_tizen 6.5
 * @description test for get info of model's output tensors
 */
int utc_nntrainer_model_get_output_tensors_info_p(void)
{
  unsigned int output_count;
  unsigned int output_dim_expected[4] = {2, 1, 1, 10};
  unsigned int dim[4];

  ml_train_model_construct_with_conf(conf_path, &model);
  ml_train_model_compile(model, NULL);

  status = ml_train_model_get_output_tensors_info(model, &output_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_tensors_info_get_count(output_info, &output_count);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    assert_eq(output_count, 1ul);
  }

  status = ml_tensors_info_get_tensor_dimension(output_info, 0, dim);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    for (unsigned int i = 0; i < 4; ++i) {
      assert_eq(dim[i], output_dim_expected[i]);
    }
  }

  ml_tensors_info_destroy(output_info);
  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_get_output_tensors_info_n1
 * @since_tizen 6.5
 * @description test for get info of model's output tensors without model
 */
int utc_nntrainer_model_get_output_tensors_info_n1(void)
{
  status = ml_train_model_get_output_tensors_info(NULL, &output_info);
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
 * @function utc_nntrainer_model_get_output_tensors_info_n2
 * @since_tizen 6.5
 * @description test for get info of model's output tensors without model compile
 */
int utc_nntrainer_model_get_output_tensors_info_n2(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);

  status = ml_train_model_get_output_tensors_info(model, &output_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(model);

  return 0;
}

/**
 * @function utc_nntrainer_model_get_output_tensors_info_n3
 * @since_tizen 6.5
 * @description test for get info of model's output tensors with destroyed model
 */
int utc_nntrainer_model_get_output_tensors_info_n3(void)
{
  ml_train_model_construct_with_conf(conf_path, &model);
  ml_train_model_compile(model, NULL);
  ml_train_model_destroy(model);

  status = ml_train_model_get_output_tensors_info(model, &output_info);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }

  return 0;
}

/**
 * @function utc_nntrainer_model_get_layer_p1
 * @since_tizen 7.0
 * @description test for get neural network layer from the model with
 *              ml_train_model_construct()
 */
int utc_nntrainer_model_get_layer_p1(void)
{
  ml_train_layer_h get_layer;

  status = ml_train_model_construct(&model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_add_layer(model, layers[0]);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_get_layer(model, "input_layer", &get_layer);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_destroy(model);
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
 * @function utc_nntrainer_model_get_layer_n1
 * @since_tizen 7.0
 * @description test for get neural network layer from the model with
 *              ml_train_model_construct()
 */
int utc_nntrainer_model_get_layer_n1(void)
{
  ml_train_layer_h get_layer;

  status = ml_train_model_construct(&model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_add_layer(model, layers[0]);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_get_layer(model, "unknown", &get_layer);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }

  status = ml_train_model_destroy(model);
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
 * @function utc_nntrainer_model_get_layer_p2
 * @since_tizen 7.0
 * @description test for get neural network layer from the model with
 *              ml_train_model_construct_with_conf()
 */
int utc_nntrainer_model_get_layer_p2(void)
{
  char *default_summary = NULL;
  char *modified_summary = NULL;
  char *result = NULL;
  ml_train_layer_h get_layer;

  status = ml_train_model_construct_with_conf(conf_path, &model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_get_summary(model, ML_TRAIN_SUMMARY_MODEL, &default_summary);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    result = strstr(default_summary, "inputlayer");
    assert_neq(result, NULL);

    if (default_summary)
      free(default_summary);
  }

  status = ml_train_model_get_layer(model, "inputlayer", &get_layer);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_layer_set_property(get_layer, "name=renamed_inputlayer", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_get_summary(model, ML_TRAIN_SUMMARY_MODEL, &modified_summary);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
    result = strstr(modified_summary, "renamed_inputlayer");
    assert_neq(result, NULL);

    if (modified_summary)
      free(modified_summary);
  }

  status = ml_train_model_destroy(model);
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
 * @function utc_nntrainer_model_get_layer_n2
 * @since_tizen 7.0
 * @description test for get neural network layer from the model with
 *              ml_train_model_construct_with_conf()
 */
int utc_nntrainer_model_get_layer_n2(void)
{
  ml_train_layer_h get_layer;

  status = ml_train_model_construct_with_conf(conf_path, &model);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  /* getting layer is prohibited after model compile */
  status = ml_train_model_compile(model, NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_get_layer(model, "inputlayer", &get_layer);
  assert_eq(status, ML_ERROR_NOT_SUPPORTED);

  status = ml_train_model_destroy(model);
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
 * @function utc_nntrainer_model_save_load_format_bin_p
 * @since_tizen 6.5
 * @description save model to bin format and load model from bin format
 */
int utc_nntrainer_model_save_load_format_bin_p(void)
{
  ml_train_model_h save_model, load_model;
  ml_train_model_construct_with_conf(conf_path, &save_model);
  ml_train_model_construct_with_conf(conf_path, &load_model);
  ml_train_model_compile(save_model, NULL);
  ml_train_model_compile(load_model, NULL);

  status = ml_train_model_save(save_model, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  status = ml_train_model_load(load_model, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  ml_train_model_destroy(save_model);
  ml_train_model_destroy(load_model);

  return 0;
}

/**
 * @function utc_nntrainer_model_save_load_format_bin_n
 * @since_tizen 6.5
 * @description save model to bin format and load model from bin format without compile the model
 */
int utc_nntrainer_model_save_load_format_bin_n(void)
{
  ml_train_model_h save_model, load_model;
  ml_train_model_construct_with_conf(conf_path, &save_model);
  ml_train_model_construct_with_conf(conf_path, &load_model);

  status = ml_train_model_save(save_model, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_UNKNOWN);
  }

  ml_train_model_compile(save_model, NULL);
  ml_train_model_save(save_model, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);

  status = ml_train_model_load(load_model, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_UNKNOWN);
  }

  ml_train_model_destroy(save_model);
  ml_train_model_destroy(load_model);

  return 0;
}
