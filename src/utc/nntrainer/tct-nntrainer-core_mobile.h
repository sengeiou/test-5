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
#ifndef __TCT_NNTRAINER_MOBILE_H__
#define __TCT_NNTRAINER_MOBILE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_nntrainer_layer_startup(void);
extern void utc_nntrainer_layer_cleanup(void);

extern int utc_nntrainer_layer_create_p(void);
extern int utc_nntrainer_layer_create_n(void);
extern int utc_nntrainer_layer_destroy_p(void);
extern int utc_nntrainer_layer_destroy_n(void);
extern int utc_nntrainer_layer_set_property_p(void);
extern int utc_nntrainer_layer_set_property_n(void);

extern void utc_nntrainer_optimizer_startup(void);
extern void utc_nntrainer_optimizer_cleanup(void);

extern int utc_nntrainer_optimizer_create_p(void);
extern int utc_nntrainer_optimizer_create_n(void);
extern int utc_nntrainer_optimizer_destroy_p(void);
extern int utc_nntrainer_optimizer_destroy_n(void);
extern int utc_nntrainer_optimizer_set_property_p(void);
extern int utc_nntrainer_optimizer_set_property_n(void);

extern void utc_nntrainer_dataset_startup(void);
extern void utc_nntrainer_dataset_cleanup(void);

extern int utc_nntrainer_dataset_create_file_p(void);
extern int utc_nntrainer_dataset_create_file_n(void);
extern int utc_nntrainer_dataset_create_generator_p(void);
extern int utc_nntrainer_dataset_create_generator_n(void);
extern int utc_nntrainer_dataset_destroy_p(void);
extern int utc_nntrainer_dataset_destroy_n(void);
extern int utc_nntrainer_dataset_set_property_p(void);
extern int utc_nntrainer_dataset_set_property_n(void);

extern void utc_nntrainer_model_startup(void);
extern void utc_nntrainer_model_cleanup(void);

extern int utc_nntrainer_model_construct_p(void);
extern int utc_nntrainer_model_construct_n(void);
extern int utc_nntrainer_model_construct_with_conf_p(void);
extern int utc_nntrainer_model_construct_with_conf_n(void);
extern int utc_nntrainer_model_destroy_p(void);
extern int utc_nntrainer_model_destroy_n(void);
extern int utc_nntrainer_model_add_layer_p(void);
extern int utc_nntrainer_model_add_layer_n1(void);
extern int utc_nntrainer_model_add_layer_n2(void);
extern int utc_nntrainer_model_set_optimizer_p(void);
extern int utc_nntrainer_model_set_optimizer_n1(void);
extern int utc_nntrainer_model_set_optimizer_n2(void);
extern int utc_nntrainer_model_set_dataset_p(void);
extern int utc_nntrainer_model_set_dataset_n1(void);
extern int utc_nntrainer_model_set_dataset_n2(void);
extern int utc_nntrainer_model_get_summary_p(void);
extern int utc_nntrainer_model_get_summary_n(void);
extern int utc_nntrainer_model_compile_p(void);
extern int utc_nntrainer_model_compile_n(void);
extern int utc_nntrainer_model_run_p1(void);
extern int utc_nntrainer_model_run_p2(void);
extern int utc_nntrainer_model_run_n(void);
/// since tizen 6.5
extern int utc_nntrainer_layer_create_p2(void);
extern int utc_nntrainer_layer_set_property_bn_p(void);
extern int utc_nntrainer_layer_set_property_bn_n(void);
extern int utc_nntrainer_layer_set_property_conv_p(void);
extern int utc_nntrainer_layer_set_property_conv_n(void);
extern int utc_nntrainer_layer_set_property_pooling_p(void);
extern int utc_nntrainer_layer_set_property_pooling_n(void);
extern int utc_nntrainer_layer_set_property_activation_p(void);
extern int utc_nntrainer_layer_set_property_activation_n(void);
extern int utc_nntrainer_layer_set_property_addition_p(void);
extern int utc_nntrainer_layer_set_property_addition_n(void);
extern int utc_nntrainer_layer_set_property_concat_p(void);
extern int utc_nntrainer_layer_set_property_concat_n(void);
extern int utc_nntrainer_layer_set_property_multiout_p(void);
extern int utc_nntrainer_layer_set_property_multiout_n(void);
extern int utc_nntrainer_layer_set_property_embedding_p(void);
extern int utc_nntrainer_layer_set_property_embedding_n(void);
extern int utc_nntrainer_layer_set_property_rnn_p(void);
extern int utc_nntrainer_layer_set_property_rnn_n(void);
extern int utc_nntrainer_layer_set_property_lstm_p(void);
extern int utc_nntrainer_layer_set_property_lstm_n(void);
extern int utc_nntrainer_layer_set_property_split_p(void);
extern int utc_nntrainer_layer_set_property_split_n(void);
extern int utc_nntrainer_layer_set_property_gru_p(void);
extern int utc_nntrainer_layer_set_property_gru_n(void);
extern int utc_nntrainer_layer_set_property_permute_p(void);
extern int utc_nntrainer_layer_set_property_permute_n(void);
extern int utc_nntrainer_layer_set_property_dropout_p(void);
extern int utc_nntrainer_layer_set_property_dropout_n(void);
extern int utc_nntrainer_layer_set_property_backbone_nnstreamer_p(void);
extern int utc_nntrainer_layer_set_property_backbone_nnstreamer_n(void);
extern int utc_nntrainer_layer_set_property_centroid_knn_p(void);
extern int utc_nntrainer_layer_set_property_centroid_knn_n(void);
extern int utc_nntrainer_layer_set_property_conv1d_p(void);
extern int utc_nntrainer_layer_set_property_conv1d_n(void);
extern int utc_nntrainer_layer_set_property_lstmcell_p(void);
extern int utc_nntrainer_layer_set_property_lstmcell_n(void);
extern int utc_nntrainer_layer_set_property_grucell_p(void);
extern int utc_nntrainer_layer_set_property_grucell_n(void);
extern int utc_nntrainer_layer_set_property_rnncell_p(void);
extern int utc_nntrainer_layer_set_property_rnncell_n(void);
extern int utc_nntrainer_layer_set_property_zoneoutlstmcell_p(void);
extern int utc_nntrainer_layer_set_property_zoneoutlstmcell_n(void);
extern int utc_nntrainer_layer_set_property_preprocess_flip_p(void);
extern int utc_nntrainer_layer_set_property_preprocess_flip_n(void);
extern int utc_nntrainer_layer_set_property_preprocess_translate_p(void);
extern int utc_nntrainer_layer_set_property_preprocess_translate_n(void);
extern int utc_nntrainer_layer_set_property_preprocess_l2norm_p(void);
extern int utc_nntrainer_layer_set_property_preprocess_l2norm_n(void);
extern int utc_nntrainer_layer_set_property_loss_mse_p(void);
extern int utc_nntrainer_layer_set_property_loss_mse_n(void);
extern int utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_p(void);
extern int utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_n(void);
extern int utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_p(void);
extern int utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_n(void);
extern int utc_nntrainer_model_get_input_tensors_info_p(void);
extern int utc_nntrainer_model_get_input_tensors_info_n1(void);
extern int utc_nntrainer_model_get_input_tensors_info_n2(void);
extern int utc_nntrainer_model_get_input_tensors_info_n3(void);
extern int utc_nntrainer_model_get_output_tensors_info_p(void);
extern int utc_nntrainer_model_get_output_tensors_info_n1(void);
extern int utc_nntrainer_model_get_output_tensors_info_n2(void);
extern int utc_nntrainer_model_get_output_tensors_info_n3(void);
extern int utc_nntrainer_model_get_layer_p1(void);
extern int utc_nntrainer_model_get_layer_n1(void);
extern int utc_nntrainer_model_get_layer_p2(void);
extern int utc_nntrainer_model_get_layer_n2(void);
extern int utc_nntrainer_model_save_load_format_bin_p(void);
extern int utc_nntrainer_model_save_load_format_bin_n(void);
extern int utc_nntrainer_dataset_create_p(void);
extern int utc_nntrainer_dataset_create_n(void);
extern int utc_nntrainer_dataset_add_generator_p(void);
extern int utc_nntrainer_dataset_add_generator_train_dataset_n1(void);
extern int utc_nntrainer_dataset_add_generator_train_dataset_n2(void);
extern int utc_nntrainer_dataset_add_generator_valid_dataset_n1(void);
extern int utc_nntrainer_dataset_add_generator_valid_dataset_n2(void);
extern int utc_nntrainer_dataset_add_generator_test_dataset_n1(void);
extern int utc_nntrainer_dataset_add_generator_test_dataset_n2(void);
extern int utc_nntrainer_dataset_add_file_p(void);
extern int utc_nntrainer_dataset_add_file_train_dataset_n1(void);
extern int utc_nntrainer_dataset_add_file_train_dataset_n2(void);
extern int utc_nntrainer_dataset_add_file_valid_dataset_n1(void);
extern int utc_nntrainer_dataset_add_file_valid_dataset_n2(void);
extern int utc_nntrainer_dataset_add_file_test_dataset_n1(void);
extern int utc_nntrainer_dataset_add_file_test_dataset_n2(void);
extern int utc_nntrainer_dataset_set_property_for_mode_p(void);
extern int utc_nntrainer_dataset_set_property_for_mode_n(void);

testcase tc_array[] = {
    // layer tcs
    {"utc_nntrainer_layer_create_p", utc_nntrainer_layer_create_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_create_n", utc_nntrainer_layer_create_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_destroy_p", utc_nntrainer_layer_destroy_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_destroy_n", utc_nntrainer_layer_destroy_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_p", utc_nntrainer_layer_set_property_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_n", utc_nntrainer_layer_set_property_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    // optimizer tcs
    {"utc_nntrainer_optimizer_create_p", utc_nntrainer_optimizer_create_p, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    {"utc_nntrainer_optimizer_create_n", utc_nntrainer_optimizer_create_n, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    {"utc_nntrainer_optimizer_destroy_p", utc_nntrainer_optimizer_destroy_p, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    {"utc_nntrainer_optimizer_destroy_n", utc_nntrainer_optimizer_destroy_n, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    {"utc_nntrainer_optimizer_set_property_p", utc_nntrainer_optimizer_set_property_p, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    {"utc_nntrainer_optimizer_set_property_n", utc_nntrainer_optimizer_set_property_n, utc_nntrainer_optimizer_startup, utc_nntrainer_optimizer_cleanup},
    // dataset tcs
    {"utc_nntrainer_dataset_create_file_p", utc_nntrainer_dataset_create_file_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_create_file_n", utc_nntrainer_dataset_create_file_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_create_generator_p", utc_nntrainer_dataset_create_generator_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_create_generator_n", utc_nntrainer_dataset_create_generator_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_destroy_p", utc_nntrainer_dataset_destroy_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_destroy_n", utc_nntrainer_dataset_destroy_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_set_property_p", utc_nntrainer_dataset_set_property_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_set_property_n", utc_nntrainer_dataset_set_property_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    // model tcs
    {"utc_nntrainer_model_construct_p", utc_nntrainer_model_construct_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_construct_n", utc_nntrainer_model_construct_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_construct_with_conf_p", utc_nntrainer_model_construct_with_conf_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_construct_with_conf_n", utc_nntrainer_model_construct_with_conf_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_destroy_p", utc_nntrainer_model_destroy_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_destroy_n", utc_nntrainer_model_destroy_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_add_layer_p", utc_nntrainer_model_add_layer_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_add_layer_n1", utc_nntrainer_model_add_layer_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_add_layer_n2", utc_nntrainer_model_add_layer_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_optimizer_p", utc_nntrainer_model_set_optimizer_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_optimizer_n1", utc_nntrainer_model_set_optimizer_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_optimizer_n2", utc_nntrainer_model_set_optimizer_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_dataset_p", utc_nntrainer_model_set_dataset_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_dataset_n1", utc_nntrainer_model_set_dataset_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_set_dataset_n2", utc_nntrainer_model_set_dataset_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_summary_p", utc_nntrainer_model_get_summary_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_summary_n", utc_nntrainer_model_get_summary_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_compile_p", utc_nntrainer_model_compile_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_compile_n", utc_nntrainer_model_compile_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_run_p1", utc_nntrainer_model_run_p1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_run_p2", utc_nntrainer_model_run_p2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_run_n", utc_nntrainer_model_run_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},

    /// since tizen 6.5
    {"utc_nntrainer_layer_create_p2", utc_nntrainer_layer_create_p2, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_bn_p", utc_nntrainer_layer_set_property_bn_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_bn_n", utc_nntrainer_layer_set_property_bn_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_conv_p", utc_nntrainer_layer_set_property_conv_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_conv_n", utc_nntrainer_layer_set_property_conv_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_pooling_p", utc_nntrainer_layer_set_property_pooling_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_pooling_n", utc_nntrainer_layer_set_property_pooling_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_activation_p", utc_nntrainer_layer_set_property_activation_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_activation_n", utc_nntrainer_layer_set_property_activation_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_addition_p", utc_nntrainer_layer_set_property_addition_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_addition_n", utc_nntrainer_layer_set_property_addition_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_concat_p", utc_nntrainer_layer_set_property_concat_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_concat_n", utc_nntrainer_layer_set_property_concat_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_multiout_p", utc_nntrainer_layer_set_property_multiout_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_multiout_n", utc_nntrainer_layer_set_property_multiout_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_embedding_p", utc_nntrainer_layer_set_property_embedding_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_embedding_n", utc_nntrainer_layer_set_property_embedding_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_rnn_p", utc_nntrainer_layer_set_property_rnn_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_rnn_n", utc_nntrainer_layer_set_property_rnn_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_lstm_p", utc_nntrainer_layer_set_property_lstm_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_lstm_n", utc_nntrainer_layer_set_property_lstm_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_split_p", utc_nntrainer_layer_set_property_split_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_split_n", utc_nntrainer_layer_set_property_split_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_gru_p", utc_nntrainer_layer_set_property_gru_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_gru_n", utc_nntrainer_layer_set_property_gru_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_permute_p", utc_nntrainer_layer_set_property_permute_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_permute_n", utc_nntrainer_layer_set_property_permute_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_dropout_p", utc_nntrainer_layer_set_property_dropout_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_dropout_n", utc_nntrainer_layer_set_property_dropout_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_backbone_nnstreamer_p", utc_nntrainer_layer_set_property_backbone_nnstreamer_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_backbone_nnstreamer_n", utc_nntrainer_layer_set_property_backbone_nnstreamer_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_centroid_knn_p", utc_nntrainer_layer_set_property_centroid_knn_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_centroid_knn_n", utc_nntrainer_layer_set_property_centroid_knn_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_conv1d_p", utc_nntrainer_layer_set_property_conv1d_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_conv1d_n", utc_nntrainer_layer_set_property_conv1d_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_lstmcell_p", utc_nntrainer_layer_set_property_lstmcell_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_lstmcell_n", utc_nntrainer_layer_set_property_lstmcell_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_grucell_p", utc_nntrainer_layer_set_property_grucell_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_grucell_n", utc_nntrainer_layer_set_property_grucell_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_rnncell_p", utc_nntrainer_layer_set_property_rnncell_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_rnncell_n", utc_nntrainer_layer_set_property_rnncell_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_zoneoutlstmcell_p", utc_nntrainer_layer_set_property_zoneoutlstmcell_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_zoneoutlstmcell_n", utc_nntrainer_layer_set_property_zoneoutlstmcell_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_flip_p", utc_nntrainer_layer_set_property_preprocess_flip_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_flip_n", utc_nntrainer_layer_set_property_preprocess_flip_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_translate_p", utc_nntrainer_layer_set_property_preprocess_translate_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_translate_n", utc_nntrainer_layer_set_property_preprocess_translate_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_l2norm_p", utc_nntrainer_layer_set_property_preprocess_l2norm_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_preprocess_l2norm_n", utc_nntrainer_layer_set_property_preprocess_l2norm_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_mse_p", utc_nntrainer_layer_set_property_loss_mse_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_mse_n", utc_nntrainer_layer_set_property_loss_mse_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_p", utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_n", utc_nntrainer_layer_set_property_loss_cross_entropy_sigmoid_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_p", utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_p, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_n", utc_nntrainer_layer_set_property_loss_cross_entropy_softmax_n, utc_nntrainer_layer_startup, utc_nntrainer_layer_cleanup},
    {"utc_nntrainer_model_get_input_tensors_info_p", utc_nntrainer_model_get_input_tensors_info_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_input_tensors_info_n1", utc_nntrainer_model_get_input_tensors_info_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_input_tensors_info_n2", utc_nntrainer_model_get_input_tensors_info_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_input_tensors_info_n3", utc_nntrainer_model_get_input_tensors_info_n3, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_output_tensors_info_p", utc_nntrainer_model_get_output_tensors_info_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_output_tensors_info_n1", utc_nntrainer_model_get_output_tensors_info_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_output_tensors_info_n2", utc_nntrainer_model_get_output_tensors_info_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_output_tensors_info_n3", utc_nntrainer_model_get_output_tensors_info_n3, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_layer_p1", utc_nntrainer_model_get_layer_p1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_layer_n1", utc_nntrainer_model_get_layer_n1, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_layer_p2", utc_nntrainer_model_get_layer_p2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_get_layer_n2", utc_nntrainer_model_get_layer_n2, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_save_load_format_bin_p", utc_nntrainer_model_save_load_format_bin_p, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_model_save_load_format_bin_n", utc_nntrainer_model_save_load_format_bin_n, utc_nntrainer_model_startup, utc_nntrainer_model_cleanup},
    {"utc_nntrainer_dataset_create_p", utc_nntrainer_dataset_create_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_create_n", utc_nntrainer_dataset_create_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_p", utc_nntrainer_dataset_add_generator_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_train_dataset_n1", utc_nntrainer_dataset_add_generator_train_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_train_dataset_n2", utc_nntrainer_dataset_add_generator_train_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_valid_dataset_n1", utc_nntrainer_dataset_add_generator_valid_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_valid_dataset_n2", utc_nntrainer_dataset_add_generator_valid_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_test_dataset_n1", utc_nntrainer_dataset_add_generator_test_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_generator_test_dataset_n2", utc_nntrainer_dataset_add_generator_test_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_p", utc_nntrainer_dataset_add_file_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_train_dataset_n1", utc_nntrainer_dataset_add_file_train_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_train_dataset_n2", utc_nntrainer_dataset_add_file_train_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_valid_dataset_n1", utc_nntrainer_dataset_add_file_valid_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_valid_dataset_n2", utc_nntrainer_dataset_add_file_valid_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_test_dataset_n1", utc_nntrainer_dataset_add_file_test_dataset_n1, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_add_file_test_dataset_n2", utc_nntrainer_dataset_add_file_test_dataset_n2, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_set_property_for_mode_p", utc_nntrainer_dataset_set_property_for_mode_p, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},
    {"utc_nntrainer_dataset_set_property_for_mode_n", utc_nntrainer_dataset_set_property_for_mode_n, utc_nntrainer_dataset_startup, utc_nntrainer_dataset_cleanup},

    {NULL, NULL},
};
#endif // __TCT_NNTRAINER_MOBILE_H__
