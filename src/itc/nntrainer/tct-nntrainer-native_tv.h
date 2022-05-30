//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_NNTRAINER_NATIVE_H__
#define __TCT_NNTRAINER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_nntrainer_layer_startup(void);
extern void ITs_nntrainer_layer_cleanup(void);
extern void ITs_nntrainer_optimizer_startup(void);
extern void ITs_nntrainer_optimizer_cleanup(void);
extern void ITs_nntrainer_dataset_startup(void);
extern void ITs_nntrainer_dataset_cleanup(void);
extern void ITs_nntrainer_model_startup(void);
extern void ITs_nntrainer_model_cleanup(void);

extern int ITc_nntrainer_layer_create_destroy_p(void);
extern int ITc_nntrainer_layer_set_property_p(void);
extern int ITc_nntrainer_optimizer_create_destroy_p(void);
extern int ITc_nntrainer_optimizer_set_property_p(void);
extern int ITc_nntrainer_model_construct_destroy_p(void);
extern int ITc_nntrainer_model_construct_with_conf_destroy_p(void);
extern int ITc_nntrainer_model_add_layer_p(void);
extern int ITc_nntrainer_model_set_optimizer_p(void);
extern int ITc_nntrainer_model_set_dataset_p(void);
extern int ITc_nntrainer_model_get_summary_p(void);
extern int ITc_nntrainer_model_compile_p(void);
extern int ITc_nntrainer_model_run_p(void);
extern int ITc_nntrainer_model_get_input_tensors_info_p(void);
extern int ITc_nntrainer_model_get_output_tensors_info_p(void);
extern int ITc_nntrainer_model_save_load_format_bin_p(void);
extern int ITc_nntrainer_dataset_create_destroy_p(void);
extern int ITc_nntrainer_dataset_add_generator_p(void);
extern int ITc_nntrainer_dataset_add_file_p(void);
extern int ITc_nntrainer_dataset_set_property_for_mode_p(void);

testcase tc_array[] = {
	{"ITc_nntrainer_layer_create_destroy_p", ITc_nntrainer_layer_create_destroy_p, ITs_nntrainer_layer_startup, ITs_nntrainer_layer_cleanup},
	{"ITc_nntrainer_layer_set_property_p", ITc_nntrainer_layer_set_property_p, ITs_nntrainer_layer_startup, ITs_nntrainer_layer_cleanup},
	{"ITc_nntrainer_optimizer_create_destroy_p", ITc_nntrainer_optimizer_create_destroy_p, ITs_nntrainer_optimizer_startup, ITs_nntrainer_optimizer_cleanup},
	{"ITc_nntrainer_optimizer_set_property_p", ITc_nntrainer_optimizer_set_property_p, ITs_nntrainer_optimizer_startup, ITs_nntrainer_optimizer_cleanup},
	{"ITc_nntrainer_model_construct_destroy_p", ITc_nntrainer_model_construct_destroy_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_construct_with_conf_destroy_p", ITc_nntrainer_model_construct_with_conf_destroy_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_add_layer_p", ITc_nntrainer_model_add_layer_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_set_optimizer_p", ITc_nntrainer_model_set_optimizer_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_set_dataset_p", ITc_nntrainer_model_set_dataset_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_get_summary_p", ITc_nntrainer_model_get_summary_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_compile_p", ITc_nntrainer_model_compile_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_run_p", ITc_nntrainer_model_run_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_get_input_tensors_info_p", ITc_nntrainer_model_get_input_tensors_info_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_get_output_tensors_info_p", ITc_nntrainer_model_get_output_tensors_info_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_model_save_load_format_bin_p", ITc_nntrainer_model_save_load_format_bin_p, ITs_nntrainer_model_startup, ITs_nntrainer_model_cleanup},
	{"ITc_nntrainer_dataset_create_destroy_p", ITc_nntrainer_dataset_create_destroy_p, ITs_nntrainer_dataset_startup, ITs_nntrainer_dataset_cleanup},
	{"ITc_nntrainer_dataset_add_generator_p", ITc_nntrainer_dataset_add_generator_p, ITs_nntrainer_dataset_startup, ITs_nntrainer_dataset_cleanup},
	{"ITc_nntrainer_dataset_add_file_p", ITc_nntrainer_dataset_add_file_p, ITs_nntrainer_dataset_startup, ITs_nntrainer_dataset_cleanup},
	{"ITc_nntrainer_dataset_set_property_for_mode_p", ITc_nntrainer_dataset_set_property_for_mode_p, ITs_nntrainer_dataset_startup, ITs_nntrainer_dataset_cleanup},
	{NULL, NULL}
};

#endif // __TCT_NNTRAINER_NATIVE_H__
