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
static ml_train_layer_h layer;

/**
 * @function utc_nntrainer_layer_startup
 * @since_tizen 6.0
 * @description Called before each test case
 */
void utc_nntrainer_layer_startup(void)
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
 * @function utc_nntrainer_layer_cleanup
 * @since_tizen 6.0
 * @description Called after each test case
 */
void utc_nntrainer_layer_cleanup(void)
{
  return;
}

/**
 * @function utc_nntrainer_layer_create_p
 * @since_tizen 6.0
 * @description create layer test
 */
int utc_nntrainer_layer_create_p(void)
{
  status = ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_INPUT);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }

  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_create_p2
 * @since_tizen 6.5
 * @description create layer with 6.5 supported layer
 */
int utc_nntrainer_layer_create_p2(void)
{
  ml_train_layer_type_e layer_types[] = {
      ML_TRAIN_LAYER_TYPE_BN,
      ML_TRAIN_LAYER_TYPE_CONV2D,
      ML_TRAIN_LAYER_TYPE_POOLING2D,
      ML_TRAIN_LAYER_TYPE_FLATTEN,
      ML_TRAIN_LAYER_TYPE_ACTIVATION,
      ML_TRAIN_LAYER_TYPE_ADDITION,
      ML_TRAIN_LAYER_TYPE_CONCAT,
      ML_TRAIN_LAYER_TYPE_MULTIOUT,
      ML_TRAIN_LAYER_TYPE_EMBEDDING,
      ML_TRAIN_LAYER_TYPE_RNN,
      ML_TRAIN_LAYER_TYPE_LSTM,
      ML_TRAIN_LAYER_TYPE_SPLIT,
      ML_TRAIN_LAYER_TYPE_GRU,
      ML_TRAIN_LAYER_TYPE_PERMUTE,
      ML_TRAIN_LAYER_TYPE_DROPOUT,
      ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER,
      ML_TRAIN_LAYER_TYPE_CENTROID_KNN,
      ML_TRAIN_LAYER_TYPE_CONV1D,
      ML_TRAIN_LAYER_TYPE_LSTMCELL,
      ML_TRAIN_LAYER_TYPE_GRUCELL,
      ML_TRAIN_LAYER_TYPE_RNNCELL,
      ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL,
      ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP,
      ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE,
      ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM,
      ML_TRAIN_LAYER_TYPE_LOSS_MSE,
      ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID,
      ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX,
  };
  const unsigned int layer_types_size = 23;
  unsigned int i = 0;

  for (i = 0; i < layer_types_size; ++i)
  {
    status = ml_train_layer_create(&layer, layer_types[i]);

    if (train_supported == false)
    {
      assert_eq(status, ML_ERROR_NOT_SUPPORTED);
    }
    else
    {
      assert_eq(status, ML_ERROR_NONE);
    }

    if (layer != NULL && status == ML_ERROR_NONE)
    {
      if (layer != NULL)
      {
        ml_train_layer_destroy(layer);
        layer = NULL;
      }
      layer = NULL;
    }
  }

  return 0;
}

/**
 * @function utc_nntrainer_layer_create_n
 * @since_tizen 6.0
 * @description Test for creating unknown layer
 */
int utc_nntrainer_layer_create_n(void)
{
  status = ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_UNKNOWN);
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
 * @function utc_nntrainer_layer_destory_p
 * @since_tizen 6.0
 * @description Test for destroying layer
 */
int utc_nntrainer_layer_destroy_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_FC);
  status = ml_train_layer_destroy(layer);
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
 * @function utc_nntrainer_layer_destroy_n
 * @since_tizen 6.0
 * @description Test for destroying layer that is passed to model
 */
int utc_nntrainer_layer_destroy_n(void)
{
  ml_train_model_h model;
  ml_train_model_construct(&model);
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_INPUT);

  ml_train_model_add_layer(model, layer);

  status = ml_train_layer_destroy(layer);
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
 * @function utc_nntrainer_layer_set_property_p
 * @since_tizen 6.0
 * @description Test for setting property
 */
int utc_nntrainer_layer_set_property_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_INPUT);
  status = ml_train_layer_set_property(layer, "input_shape=1:1:6270", "normalization=true", "standardization=true", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @function utc_nntrainer_layer_set_property_n
 * @since_tizen 6.0
 * @description Test for setting invalid property
 */
int utc_nntrainer_layer_set_property_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_INPUT);
  status = ml_train_layer_set_property(layer, "invalid_property_key=invalid_property_value", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_INVALID_PARAMETER);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_bn_p
 * @since_tizen 6.5
 * @description set property with 6.5 bn layer
 */
int utc_nntrainer_layer_set_property_bn_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_BN);
  status = ml_train_layer_set_property(layer, "name=bn", "epsilon=0.001", "moving_mean_initializer=zeros",
                                       "moving_variance_initializer=ones", "gamma_initializer=zeros",
                                       "beta_initializer=ones", "momentum=0.9", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_bn_n
 * @since_tizen 6.5
 * @description set property with 6.5 bn layer
 */
int utc_nntrainer_layer_set_property_bn_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_BN);
  status = ml_train_layer_set_property(layer, "name=bn", "epsilon=string_value", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_conv_p
 * @since_tizen 6.5
 * @description set property with 6.5 conv layer
 */
int utc_nntrainer_layer_set_property_conv_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONV2D);
  status = ml_train_layer_set_property(layer, "filters=3", "kernel_size=2, 2", "stride=1,1", "padding=0, 0", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_conv_n
 * @since_tizen 6.5
 * @description set property with 6.5 conv layer
 */
int utc_nntrainer_layer_set_property_conv_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONV2D);
  status = ml_train_layer_set_property(layer, "kernel_size=string", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_pooling_p
 * @since_tizen 6.5
 * @description set property with 6.5 pooling layer
 */
int utc_nntrainer_layer_set_property_pooling_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_POOLING2D);
  status = ml_train_layer_set_property(layer, "pooling=max", "pool_size=1, 1", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_pooling_n
 * @since_tizen 6.5
 * @description set property with 6.5 pooling layer
 */
int utc_nntrainer_layer_set_property_pooling_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_POOLING2D);
  status = ml_train_layer_set_property(layer, "pooling=undef", "pool_size=1, 1", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_activation_p
 * @since_tizen 6.5
 * @description set property with 6.5 activation layer
 */
int utc_nntrainer_layer_set_property_activation_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ACTIVATION);
  status = ml_train_layer_set_property(layer, "activation=relu", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_activation_n
 * @since_tizen 6.5
 * @description set property with 6.5 activation layer
 */
int utc_nntrainer_layer_set_property_activation_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ACTIVATION);
  status = ml_train_layer_set_property(layer, "activation=undef", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_addition_p
 * @since_tizen 6.5
 * @description set property with 6.5 addition layer
 */
int utc_nntrainer_layer_set_property_addition_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ADDITION);
  status = ml_train_layer_set_property(layer, "name=addition", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_addition_n
 * @since_tizen 6.5
 * @description set property with 6.5 addition layer
 */
int utc_nntrainer_layer_set_property_addition_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ADDITION);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_concat_p
 * @since_tizen 6.5
 * @description set property with 6.5 concat layer
 */
int utc_nntrainer_layer_set_property_concat_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONCAT);
  status = ml_train_layer_set_property(layer, "name=concat", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_concat_n
 * @since_tizen 6.5
 * @description set property with 6.5 concat layer
 */
int utc_nntrainer_layer_set_property_concat_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONCAT);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_multiout_p
 * @since_tizen 6.5
 * @description set property with 6.5 multiout layer
 */
int utc_nntrainer_layer_set_property_multiout_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_MULTIOUT);
  status = ml_train_layer_set_property(layer, "name=multiout", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_multiout_n
 * @since_tizen 6.5
 * @description set property with 6.5 multiout layer
 */
int utc_nntrainer_layer_set_property_multiout_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_MULTIOUT);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_embedding_p
 * @since_tizen 6.5
 * @description set property with 6.5 embedding layer
 */
int utc_nntrainer_layer_set_property_embedding_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_EMBEDDING);
  status = ml_train_layer_set_property(layer, "name=embedding", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_embedding_n
 * @since_tizen 6.5
 * @description set property with 6.5 embedding layer
 */
int utc_nntrainer_layer_set_property_embedding_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_EMBEDDING);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_rnn_p
 * @since_tizen 6.5
 * @description set property with 6.5 rnn layer
 */
int utc_nntrainer_layer_set_property_rnn_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_RNN);
  status = ml_train_layer_set_property(layer, "name=rnn", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_rnn_n
 * @since_tizen 6.5
 * @description set property with 6.5 rnn layer
 */
int utc_nntrainer_layer_set_property_rnn_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_RNN);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_lstm_p
 * @since_tizen 6.5
 * @description set property with 6.5 lstm layer
 */
int utc_nntrainer_layer_set_property_lstm_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LSTM);
  status = ml_train_layer_set_property(layer, "name=lstm", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_lstm_n
 * @since_tizen 6.5
 * @description set property with 6.5 lstm layer
 */
int utc_nntrainer_layer_set_property_lstm_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LSTM);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_split_p
 * @since_tizen 6.5
 * @description set property with 6.5 split layer
 */
int utc_nntrainer_layer_set_property_split_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_SPLIT);
  status = ml_train_layer_set_property(layer, "name=split", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_split_n
 * @since_tizen 6.5
 * @description set property with 6.5 split layer
 */
int utc_nntrainer_layer_set_property_split_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_SPLIT);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_gru_p
 * @since_tizen 6.5
 * @description set property with 6.5 gru layer
 */
int utc_nntrainer_layer_set_property_gru_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_GRU);
  status = ml_train_layer_set_property(layer, "name=gru", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_gru_n
 * @since_tizen 6.5
 * @description set property with 6.5 gru layer
 */
int utc_nntrainer_layer_set_property_gru_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_GRU);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_permute_p
 * @since_tizen 6.5
 * @description set property with 6.5 permute layer
 */
int utc_nntrainer_layer_set_property_permute_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PERMUTE);
  status = ml_train_layer_set_property(layer, "name=permute", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_permute_n
 * @since_tizen 6.5
 * @description set property with 6.5 permute layer
 */
int utc_nntrainer_layer_set_property_permute_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PERMUTE);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_dropout_p
 * @since_tizen 6.5
 * @description set property with 6.5 dropout layer
 */
int utc_nntrainer_layer_set_property_dropout_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_DROPOUT);
  status = ml_train_layer_set_property(layer, "name=dropout", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_dropout_n
 * @since_tizen 6.5
 * @description set property with 6.5 dropout layer
 */
int utc_nntrainer_layer_set_property_dropout_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_DROPOUT);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_backbone_nnstreamer_p
 * @since_tizen 6.5
 * @description set property with 6.5 backbone_nnstreamer layer
 */
int utc_nntrainer_layer_set_property_backbone_nnstreamer_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER);
  status = ml_train_layer_set_property(layer, "name=backbone_nnstreamer", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_backbone_nnstreamer_n
 * @since_tizen 6.5
 * @description set property with 6.5 backbone_nnstreamer layer
 */
int utc_nntrainer_layer_set_property_backbone_nnstreamer_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_centroid_knn_p
 * @since_tizen 6.5
 * @description set property with 6.5 centroid_knn layer
 */
int utc_nntrainer_layer_set_property_centroid_knn_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CENTROID_KNN);
  status = ml_train_layer_set_property(layer, "name=centroid_knn", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_centroid_knn_n
 * @since_tizen 6.5
 * @description set property with 6.5 centroid_knn layer
 */
int utc_nntrainer_layer_set_property_centroid_knn_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CENTROID_KNN);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_conv1d_p
 * @since_tizen 7.0
 * @description set property with 7.0 conv1d layer
 */
int utc_nntrainer_layer_set_property_conv1d_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONV1D);
  status = ml_train_layer_set_property(layer, "name=conv1d", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_conv1d_n
 * @since_tizen 7.0
 * @description set property with 7.0 conv1d layer
 */
int utc_nntrainer_layer_set_property_conv1d_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_CONV1D);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_lstmcell_p
 * @since_tizen 7.0
 * @description set property with 7.0 lstmcell layer
 */
int utc_nntrainer_layer_set_property_lstmcell_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LSTMCELL);
  status = ml_train_layer_set_property(layer, "name=lstmcell", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_lstmcell_n
 * @since_tizen 7.0
 * @description set property with 7.0 lstmcell layer
 */
int utc_nntrainer_layer_set_property_lstmcell_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LSTMCELL);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_grucell_p
 * @since_tizen 7.0
 * @description set property with 7.0 grucell layer
 */
int utc_nntrainer_layer_set_property_grucell_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_GRUCELL);
  status = ml_train_layer_set_property(layer, "name=grucell", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_grucell_n
 * @since_tizen 7.0
 * @description set property with 7.0 grucell layer
 */
int utc_nntrainer_layer_set_property_grucell_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_GRUCELL);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_rnncell_p
 * @since_tizen 7.0
 * @description set property with 7.0 rnncell layer
 */
int utc_nntrainer_layer_set_property_rnncell_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_RNNCELL);
  status = ml_train_layer_set_property(layer, "name=rnncell", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_rnncell_n
 * @since_tizen 7.0
 * @description set property with 7.0 rnncell layer
 */
int utc_nntrainer_layer_set_property_rnncell_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_RNNCELL);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_zoneoutlstmcell_p
 * @since_tizen 7.0
 * @description set property with 7.0 zoneoutlstmcell layer
 */
int utc_nntrainer_layer_set_property_zoneoutlstmcell_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL);
  status = ml_train_layer_set_property(layer, "name=zoneoutlstmcell", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_zoneoutlstmcell_n
 * @since_tizen 7.0
 * @description set property with 7.0 zoneoutlstmcell layer
 */
int utc_nntrainer_layer_set_property_zoneoutlstmcell_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_flip_p
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_flip layer
 */
int utc_nntrainer_layer_set_property_preprocess_flip_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP);
  status = ml_train_layer_set_property(layer, "name=preprocess_flip", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_flip_n
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_flip layer
 */
int utc_nntrainer_layer_set_property_preprocess_flip_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_translate_p
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_translate layer
 */
int utc_nntrainer_layer_set_property_preprocess_translate_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE);
  status = ml_train_layer_set_property(layer, "name=preprocess_translate", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_translate_n
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_translate layer
 */
int utc_nntrainer_layer_set_property_preprocess_translate_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_l2norm_p
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_l2norm layer
 */
int utc_nntrainer_layer_set_property_preprocess_l2norm_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM);
  status = ml_train_layer_set_property(layer, "name=preprocess_l2norm", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_preprocess_l2norm_n
 * @since_tizen 6.5
 * @description set property with 6.5 preprocess_l2norm layer
 */
int utc_nntrainer_layer_set_property_preprocess_l2norm_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_mse_p
 * @since_tizen 6.5
 * @description set property with 6.5 loss_mse layer
 */
int utc_nntrainer_layer_set_property_loss_mse_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_MSE);
  status = ml_train_layer_set_property(layer, "name=loss_mse", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_mse_n
 * @since_tizen 6.5
 * @description set property with 6.5 loss_mse layer
 */
int utc_nntrainer_layer_set_property_loss_mse_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_MSE);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_p
 * @since_tizen 6.5
 * @description set property with 6.5 loss_cross_entropy_sigmoid layer
 */
int utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID);
  status = ml_train_layer_set_property(layer, "name=loss_cross_entropy_sigmoid", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_n
 * @since_tizen 6.5
 * @description set property with 6.5 loss_cross_entropy_sigmoid layer
 */
int utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_p
 * @since_tizen 6.5
 * @description set property with 6.5 loss_cross_entropy_softmax layer
 */
int utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_p(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX);
  status = ml_train_layer_set_property(layer, "name=loss_cross_entropy_softmax", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_eq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}

/**
 * @brief function utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_n
 * @since_tizen 6.5
 * @description set property with 6.5 loss_cross_entropy_softmax layer
 */
int utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_n(void)
{
  ml_train_layer_create(&layer, ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX);
  status = ml_train_layer_set_property(layer, "unknown_property=unknown_property", NULL);
  if (train_supported == false)
  {
    assert_eq(status, ML_ERROR_NOT_SUPPORTED);
  }
  else
  {
    assert_neq(status, ML_ERROR_NONE);
  }
  if (layer != NULL)
  {
    ml_train_layer_destroy(layer);
    layer = NULL;
  }

  return 0;
}
