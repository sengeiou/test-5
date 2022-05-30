//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_NNSTREAMER-NATIVE_H__
#define __TCT_NNSTREAMER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_nnstreamer_single_startup (void);
extern void utc_nnstreamer_single_cleanup (void);
extern void utc_nnstreamer_pipeline_startup (void);
extern void utc_nnstreamer_pipeline_cleanup (void);
extern void utc_nnstreamer_pipeline_sink_startup (void);
extern void utc_nnstreamer_pipeline_sink_cleanup (void);
extern void utc_nnstreamer_pipeline_src_startup (void);
extern void utc_nnstreamer_pipeline_src_cleanup (void);
extern void utc_nnstreamer_pipeline_switch_startup (void);
extern void utc_nnstreamer_pipeline_switch_cleanup (void);
extern void utc_nnstreamer_pipeline_valve_startup (void);
extern void utc_nnstreamer_pipeline_valve_cleanup (void);
extern void utc_nnstreamer_pipeline_tensor_info_startup (void);
extern void utc_nnstreamer_pipeline_tensor_info_cleanup (void);
extern void utc_nnstreamer_pipeline_tensor_data_startup (void);
extern void utc_nnstreamer_pipeline_tensor_data_cleanup (void);
extern void utc_nnstreamer_scenario_startup (void);
extern void utc_nnstreamer_scenario_cleanup (void);
extern void utc_nnstreamer_capi_startup (void);
extern void utc_nnstreamer_capi_cleanup (void);
extern void utc_machine_learning_service_startup (void);
extern void utc_machine_learning_service_cleanup (void);

extern int utc_ml_pipeline_construct_p (void);
extern int utc_ml_pipeline_construct_n (void);
extern int utc_ml_pipeline_destroy_p (void);
extern int utc_ml_pipeline_destroy_n (void);
extern int utc_ml_pipeline_get_state_p (void);

extern int utc_ml_pipeline_get_state_n (void);
extern int utc_ml_pipeline_start_p (void);
extern int utc_ml_pipeline_start_n (void);
extern int utc_ml_pipeline_stop_p (void);
extern int utc_ml_pipeline_stop_n (void);

extern int utc_ml_check_nnfw_availability_full_p (void);
extern int utc_ml_check_nnfw_availability_full_n (void);
extern int utc_ml_check_nnfw_availability_p (void);
extern int utc_ml_check_nnfw_availability_n (void);
extern int utc_ml_check_element_availability_p (void);
extern int utc_ml_check_element_availability_n1 (void);
extern int utc_ml_check_element_availability_n2 (void);

extern int utc_ml_pipeline_sink_register_p (void);
extern int utc_ml_pipeline_sink_register_n (void);
extern int utc_ml_pipeline_sink_unregister_p (void);

extern int utc_ml_pipeline_sink_unregister_n (void);
extern int utc_ml_pipeline_src_get_handle_p (void);
extern int utc_ml_pipeline_src_get_handle_n (void);
extern int utc_ml_pipeline_src_release_handle_p (void);
extern int utc_ml_pipeline_src_release_handle_n (void);

extern int utc_ml_pipeline_src_input_data_p (void);
extern int utc_ml_pipeline_src_input_data_n (void);
extern int utc_ml_pipeline_src_get_tensors_info_p (void);
extern int utc_ml_pipeline_src_get_tensors_info_n (void);

extern int utc_ml_pipeline_src_set_event_cb_p (void);
extern int utc_ml_pipeline_src_set_event_cb_n1 (void);
extern int utc_ml_pipeline_src_set_event_cb_n2 (void);
extern int utc_ml_pipeline_switch_get_handle_p (void);

extern int utc_ml_pipeline_switch_get_handle_n (void);
extern int utc_ml_pipeline_switch_release_handle_p (void);
extern int utc_ml_pipeline_switch_release_handle_n (void);
extern int utc_ml_pipeline_switch_select_p (void);
extern int utc_ml_pipeline_switch_select_n (void);

extern int utc_ml_pipeline_switch_get_pad_list_p (void);
extern int utc_ml_pipeline_switch_get_pad_list_n (void);
extern int utc_ml_pipeline_valve_get_handle_p (void);
extern int utc_ml_pipeline_valve_get_handle_n (void);
extern int utc_ml_pipeline_valve_release_handle_p (void);

extern int utc_ml_pipeline_valve_release_handle_n (void);
extern int utc_ml_pipeline_valve_set_open_p (void);
extern int utc_ml_pipeline_valve_set_open_n (void);
extern int utc_ml_tensors_info_create_p (void);
extern int utc_ml_tensors_info_create_n (void);

extern int utc_ml_tensors_info_destroy_p (void);
extern int utc_ml_tensors_info_destroy_n (void);
extern int utc_ml_tensors_info_validate_p (void);
extern int utc_ml_tensors_info_validate_n (void);
extern int utc_ml_tensors_info_clone_p (void);

extern int utc_ml_tensors_info_clone_n (void);
extern int utc_ml_tensors_info_set_count_p (void);
extern int utc_ml_tensors_info_set_count_n (void);
extern int utc_ml_tensors_info_get_count_p (void);
extern int utc_ml_tensors_info_get_count_n (void);

extern int utc_ml_tensors_info_set_tensor_name_p (void);
extern int utc_ml_tensors_info_set_tensor_name_n (void);
extern int utc_ml_tensors_info_get_tensor_name_p (void);
extern int utc_ml_tensors_info_get_tensor_name_n (void);
extern int utc_ml_tensors_info_set_tensor_type_p (void);

extern int utc_ml_tensors_info_set_tensor_type_n (void);
extern int utc_ml_tensors_info_get_tensor_type_p (void);
extern int utc_ml_tensors_info_get_tensor_type_n (void);
extern int utc_ml_tensors_info_set_tensor_dimension_p (void);
extern int utc_ml_tensors_info_set_tensor_dimension_n (void);

extern int utc_ml_tensors_info_get_tensor_dimension_p (void);
extern int utc_ml_tensors_info_get_tensor_dimension_n (void);
extern int utc_ml_tensors_info_get_tensor_size_p (void);
extern int utc_ml_tensors_info_get_tensor_size_n (void);
extern int utc_ml_tensors_data_create_p (void);

extern int utc_ml_tensors_data_create_n (void);
extern int utc_ml_tensors_data_destroy_p (void);
extern int utc_ml_tensors_data_destroy_n (void);
extern int utc_ml_tensors_data_get_tensor_data_p (void);
extern int utc_ml_tensors_data_get_tensor_data_n (void);

extern int utc_ml_tensors_data_set_tensor_data_p (void);
extern int utc_ml_tensors_data_set_tensor_data_n (void);
extern int utc_ml_single_open_p (void);
extern int utc_ml_single_open_n (void);
extern int utc_ml_single_close_p (void);

extern int utc_ml_single_close_n (void);
extern int utc_ml_single_invoke_p (void);
extern int utc_ml_single_invoke_n (void);
extern int utc_ml_single_get_input_info_p (void);
extern int utc_ml_single_get_input_info_n (void);

extern int utc_ml_single_get_output_info_p (void);
extern int utc_ml_single_get_output_info_n (void);
extern int utc_ml_single_set_timeout_p (void);
extern int utc_ml_single_set_timeout_n (void);
extern int utc_ml_single_set_input_info_p (void);

extern int utc_ml_single_set_input_info_n (void);
extern int utc_ml_single_set_property_p (void);
extern int utc_ml_single_set_property_n (void);
extern int utc_ml_single_get_property_p (void);
extern int utc_ml_single_get_property_n (void);

extern int utc_ml_single_invoke_dynamic_p (void);
extern int utc_ml_single_invoke_dynamic_n (void);

extern int utc_ml_single_open_full_p (void);
extern int utc_ml_single_open_full_n (void);
extern int utc_ml_single_invoke_fast_p (void);
extern int utc_ml_single_invoke_fast_n (void);

extern int utc_nnstreamer_scenario_construct_destruct_empty_pipeline_p (void);
extern int utc_nnstreamer_scenario_construct_destruct_pipeline_p1 (void);
extern int utc_nnstreamer_scenario_construct_destruct_pipeline_p2 (void);
extern int utc_nnstreamer_scenario_construct_pipeline_error_case_n1 (void);
extern int utc_nnstreamer_scenario_construct_pipeline_error_case_n2 (void);

extern int utc_nnstreamer_scenario_pipeline_state_test_p1 (void);
extern int utc_nnstreamer_scenario_pipeline_state_test_p2 (void);
extern int utc_nnstreamer_scenario_pipeline_state_test_p3 (void);
extern int utc_nnstreamer_scenario_valve_error_cases_n (void);
extern int utc_nnstreamer_scenario_sink_p1 (void);

extern int utc_nnstreamer_scenario_sink_p2 (void);
extern int utc_nnstreamer_scenario_sink_error_cases_n (void);
extern int utc_nnstreamer_scenario_src_p (void);
extern int utc_nnstreamer_scenario_src_error_case_n1 (void);
extern int utc_nnstreamer_scenario_src_error_case_n2 (void);

extern int utc_nnstreamer_scenario_src_error_case_n3 (void);
extern int utc_nnstreamer_scenario_switch_pipeline_p1 (void);
extern int utc_nnstreamer_scenario_switch_pipeline_p2 (void);
extern int utc_nnstreamer_scenario_switch_pipeline_error_cases_n (void);
extern int utc_nnstreamer_scenario_check_tensor_info_utilities_p (void);

extern int utc_nnstreamer_scenario_filter_tensorflow_lite_p1 (void);
extern int utc_nnstreamer_scenario_filter_tensorflow_lite_p2 (void);
extern int utc_nnstreamer_scenario_filter_tensorflow_lite_n (void);
extern int utc_nnstreamer_scenario_flatbuf_p (void);
extern int utc_nnstreamer_scenario_flatbuf_n1 (void);

extern int utc_nnstreamer_scenario_flatbuf_n2 (void);
extern int utc_nnstreamer_scenario_flatbuf_n3 (void);
extern int utc_nnstreamer_scenario_flatbuf_n4 (void);
extern int utc_nnstreamer_scenario_flatbuf_n5 (void);
extern int utc_nnstreamer_scenario_capi_element_p1 (void);

extern int utc_nnstreamer_scenario_capi_element_p2 (void);
extern int utc_nnstreamer_capi_element_get_handle_p (void);
extern int utc_nnstreamer_capi_element_get_handle_n1 (void);
extern int utc_nnstreamer_capi_element_get_handle_n2 (void);
extern int utc_nnstreamer_capi_element_release_handle_p (void);

extern int utc_nnstreamer_capi_element_release_handle_n1 (void);
extern int utc_nnstreamer_capi_element_release_handle_n2 (void);
extern int utc_nnstreamer_capi_element_set_bool_property_p (void);
extern int utc_nnstreamer_capi_element_set_bool_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_bool_property_n2 (void);

extern int utc_nnstreamer_capi_element_get_bool_property_p (void);
extern int utc_nnstreamer_capi_element_get_bool_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_bool_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_bool_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_bool_property_n4 (void);

extern int utc_nnstreamer_capi_element_set_string_property_p (void);
extern int utc_nnstreamer_capi_element_set_string_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_string_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_string_property_p (void);
extern int utc_nnstreamer_capi_element_get_string_property_n1 (void);

extern int utc_nnstreamer_capi_element_get_string_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_string_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_string_property_n4 (void);
extern int utc_nnstreamer_capi_element_set_int32_property_p (void);
extern int utc_nnstreamer_capi_element_set_int32_property_n1 (void);

extern int utc_nnstreamer_capi_element_set_int32_property_n2 (void);
extern int utc_nnstreamer_capi_element_set_int32_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_int32_property_p (void);
extern int utc_nnstreamer_capi_element_get_int32_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_int32_property_n2 (void);

extern int utc_nnstreamer_capi_element_get_int32_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_int32_property_n4 (void);
extern int utc_nnstreamer_capi_element_set_int64_property_p (void);
extern int utc_nnstreamer_capi_element_set_int64_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_int64_property_n2 (void);

extern int utc_nnstreamer_capi_element_set_int64_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_int64_property_p (void);
extern int utc_nnstreamer_capi_element_get_int64_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_int64_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_int64_property_n3 (void);

extern int utc_nnstreamer_capi_element_get_int64_property_n4 (void);
extern int utc_nnstreamer_capi_element_set_uint32_property_p (void);
extern int utc_nnstreamer_capi_element_set_uint32_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_uint32_property_n2 (void);
extern int utc_nnstreamer_capi_element_set_uint32_property_n3 (void);

extern int utc_nnstreamer_capi_element_get_uint32_property_p (void);
extern int utc_nnstreamer_capi_element_get_uint32_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_uint32_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_uint32_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_uint32_property_n4 (void);

extern int utc_nnstreamer_capi_element_set_uint64_property_p (void);
extern int utc_nnstreamer_capi_element_set_uint64_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_uint64_property_n2 (void);
extern int utc_nnstreamer_capi_element_set_uint64_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_uint64_property_p (void);

extern int utc_nnstreamer_capi_element_get_uint64_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_uint64_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_uint64_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_uint64_property_n4 (void);
extern int utc_nnstreamer_capi_element_set_double_property_p (void);

extern int utc_nnstreamer_capi_element_set_double_property_n1 (void);
extern int utc_nnstreamer_capi_element_set_double_property_n2 (void);
extern int utc_nnstreamer_capi_element_set_double_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_double_property_p (void);
extern int utc_nnstreamer_capi_element_get_double_property_n1 (void);

extern int utc_nnstreamer_capi_element_get_double_property_n2 (void);
extern int utc_nnstreamer_capi_element_get_double_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_double_property_n4 (void);
extern int utc_nnstreamer_capi_element_set_enum_property_p (void);
extern int utc_nnstreamer_capi_element_set_enum_property_n1 (void);

extern int utc_nnstreamer_capi_element_set_enum_property_n2 (void);
extern int utc_nnstreamer_capi_element_set_enum_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_enum_property_p (void);
extern int utc_nnstreamer_capi_element_get_enum_property_n1 (void);
extern int utc_nnstreamer_capi_element_get_enum_property_n2 (void);

extern int utc_nnstreamer_capi_element_get_enum_property_n3 (void);
extern int utc_nnstreamer_capi_element_get_enum_property_n4 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_p (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n1 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n2 (void);

extern int utc_nnstreamer_capi_custom_filter_registration_n3 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n4 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n5 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n6 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n7 (void);

extern int utc_nnstreamer_capi_custom_filter_registration_n8 (void);
extern int utc_nnstreamer_capi_custom_filter_registration_n9 (void);
extern int utc_nnstreamer_capi_tensor_if_custom_registration_p (void);
extern int utc_nnstreamer_capi_tensor_if_custom_registration_n1 (void);
extern int utc_nnstreamer_capi_tensor_if_custom_registration_n2 (void);

extern int utc_nnstreamer_capi_tensor_if_custom_registration_n3 (void);
extern int utc_nnstreamer_capi_tensor_if_custom_registration_n4 (void);
extern int utc_nnstreamer_capi_tensor_if_custom_unregistration_p (void);
extern int utc_nnstreamer_capi_tensor_if_custom_unregistration_n1 (void);
extern int utc_nnstreamer_capi_tensor_if_custom_unregistration_n2 (void);

extern int utc_ml_service_set_pipeline_p1 (void);
extern int utc_ml_service_set_pipeline_p2 (void);
extern int utc_ml_service_set_pipeline_n1 (void);
extern int utc_ml_service_set_pipeline_n2 (void);
extern int utc_ml_service_get_pipeline_p1 (void);
extern int utc_ml_service_get_pipeline_n1 (void);
extern int utc_ml_service_get_pipeline_n2 (void);
extern int utc_ml_service_delete_pipeline_p1 (void);
extern int utc_ml_service_delete_pipeline_n1 (void);
extern int utc_ml_service_delete_pipeline_n2 (void);
extern int utc_ml_service_delete_pipeline_n3 (void);

testcase tc_array[] = {
  {"utc_ml_pipeline_construct_p", utc_ml_pipeline_construct_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_construct_n", utc_ml_pipeline_construct_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_destroy_p", utc_ml_pipeline_destroy_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_destroy_n", utc_ml_pipeline_destroy_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_get_state_p", utc_ml_pipeline_get_state_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},

  {"utc_ml_pipeline_get_state_n", utc_ml_pipeline_get_state_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_start_p", utc_ml_pipeline_start_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_start_n", utc_ml_pipeline_start_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_stop_p", utc_ml_pipeline_stop_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_pipeline_stop_n", utc_ml_pipeline_stop_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},

  {"utc_ml_check_nnfw_availability_full_p", utc_ml_check_nnfw_availability_full_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_nnfw_availability_full_n", utc_ml_check_nnfw_availability_full_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_nnfw_availability_p", utc_ml_check_nnfw_availability_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_nnfw_availability_n", utc_ml_check_nnfw_availability_n, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_element_availability_p", utc_ml_check_element_availability_p, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_element_availability_n1", utc_ml_check_element_availability_n1, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},
  {"utc_ml_check_element_availability_n2", utc_ml_check_element_availability_n2, utc_nnstreamer_pipeline_startup, utc_nnstreamer_pipeline_cleanup},


  {"utc_ml_pipeline_sink_register_p", utc_ml_pipeline_sink_register_p, utc_nnstreamer_pipeline_sink_startup, utc_nnstreamer_pipeline_sink_cleanup},
  {"utc_ml_pipeline_sink_register_n", utc_ml_pipeline_sink_register_n, utc_nnstreamer_pipeline_sink_startup, utc_nnstreamer_pipeline_sink_cleanup},
  {"utc_ml_pipeline_sink_unregister_p", utc_ml_pipeline_sink_unregister_p, utc_nnstreamer_pipeline_sink_startup, utc_nnstreamer_pipeline_sink_cleanup},
  {"utc_ml_pipeline_sink_unregister_n", utc_ml_pipeline_sink_unregister_n, utc_nnstreamer_pipeline_sink_startup, utc_nnstreamer_pipeline_sink_cleanup},
  {"utc_ml_pipeline_src_get_handle_p", utc_ml_pipeline_src_get_handle_p, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},

  {"utc_ml_pipeline_src_get_handle_n", utc_ml_pipeline_src_get_handle_n, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_release_handle_p", utc_ml_pipeline_src_release_handle_p, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_release_handle_n", utc_ml_pipeline_src_release_handle_n, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_input_data_p", utc_ml_pipeline_src_input_data_p, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_input_data_n", utc_ml_pipeline_src_input_data_n, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},

  {"utc_ml_pipeline_src_get_tensors_info_p", utc_ml_pipeline_src_get_tensors_info_p, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_get_tensors_info_n", utc_ml_pipeline_src_get_tensors_info_n, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_set_event_cb_p", utc_ml_pipeline_src_set_event_cb_p, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_set_event_cb_n1", utc_ml_pipeline_src_set_event_cb_n1, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},
  {"utc_ml_pipeline_src_set_event_cb_n2", utc_ml_pipeline_src_set_event_cb_n2, utc_nnstreamer_pipeline_src_startup, utc_nnstreamer_pipeline_src_cleanup},

  {"utc_ml_pipeline_switch_get_handle_p", utc_ml_pipeline_switch_get_handle_p, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_get_handle_n", utc_ml_pipeline_switch_get_handle_n, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_release_handle_p", utc_ml_pipeline_switch_release_handle_p, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},

  {"utc_ml_pipeline_switch_release_handle_n", utc_ml_pipeline_switch_release_handle_n, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_select_p", utc_ml_pipeline_switch_select_p, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_select_n", utc_ml_pipeline_switch_select_n, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_get_pad_list_p", utc_ml_pipeline_switch_get_pad_list_p, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},
  {"utc_ml_pipeline_switch_get_pad_list_n", utc_ml_pipeline_switch_get_pad_list_n, utc_nnstreamer_pipeline_switch_startup, utc_nnstreamer_pipeline_switch_cleanup},

  {"utc_ml_pipeline_valve_get_handle_p", utc_ml_pipeline_valve_get_handle_p, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},
  {"utc_ml_pipeline_valve_get_handle_n", utc_ml_pipeline_valve_get_handle_n, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},
  {"utc_ml_pipeline_valve_release_handle_p", utc_ml_pipeline_valve_release_handle_p, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},
  {"utc_ml_pipeline_valve_release_handle_n", utc_ml_pipeline_valve_release_handle_n, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},
  {"utc_ml_pipeline_valve_set_open_p", utc_ml_pipeline_valve_set_open_p, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},

  {"utc_ml_pipeline_valve_set_open_n", utc_ml_pipeline_valve_set_open_n, utc_nnstreamer_pipeline_valve_startup, utc_nnstreamer_pipeline_valve_cleanup},
  {"utc_ml_tensors_info_create_p", utc_ml_tensors_info_create_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_create_n", utc_ml_tensors_info_create_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_destroy_p", utc_ml_tensors_info_destroy_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_destroy_n", utc_ml_tensors_info_destroy_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},

  {"utc_ml_tensors_info_validate_p", utc_ml_tensors_info_validate_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_validate_n", utc_ml_tensors_info_validate_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_clone_p", utc_ml_tensors_info_clone_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_clone_n", utc_ml_tensors_info_clone_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_count_p", utc_ml_tensors_info_set_count_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},

  {"utc_ml_tensors_info_set_count_n", utc_ml_tensors_info_set_count_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_count_p", utc_ml_tensors_info_get_count_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_count_n", utc_ml_tensors_info_get_count_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_name_p", utc_ml_tensors_info_set_tensor_name_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_name_n", utc_ml_tensors_info_set_tensor_name_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},

  {"utc_ml_tensors_info_get_tensor_name_p", utc_ml_tensors_info_get_tensor_name_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_tensor_name_n", utc_ml_tensors_info_get_tensor_name_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_type_p", utc_ml_tensors_info_set_tensor_type_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_type_n", utc_ml_tensors_info_set_tensor_type_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_tensor_type_p", utc_ml_tensors_info_get_tensor_type_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},

  {"utc_ml_tensors_info_get_tensor_type_n", utc_ml_tensors_info_get_tensor_type_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_dimension_p", utc_ml_tensors_info_set_tensor_dimension_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_set_tensor_dimension_n", utc_ml_tensors_info_set_tensor_dimension_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_tensor_dimension_p", utc_ml_tensors_info_get_tensor_dimension_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_tensor_dimension_n", utc_ml_tensors_info_get_tensor_dimension_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},

  {"utc_ml_tensors_info_get_tensor_size_p", utc_ml_tensors_info_get_tensor_size_p, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_info_get_tensor_size_n", utc_ml_tensors_info_get_tensor_size_n, utc_nnstreamer_pipeline_tensor_info_startup, utc_nnstreamer_pipeline_tensor_info_cleanup},
  {"utc_ml_tensors_data_create_p", utc_ml_tensors_data_create_p, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_create_n", utc_ml_tensors_data_create_n, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_destroy_p", utc_ml_tensors_data_destroy_p, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},

  {"utc_ml_tensors_data_destroy_n", utc_ml_tensors_data_destroy_n, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_get_tensor_data_p", utc_ml_tensors_data_get_tensor_data_p, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_get_tensor_data_n", utc_ml_tensors_data_get_tensor_data_n, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_set_tensor_data_p", utc_ml_tensors_data_set_tensor_data_p, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},
  {"utc_ml_tensors_data_set_tensor_data_n", utc_ml_tensors_data_set_tensor_data_n, utc_nnstreamer_pipeline_tensor_data_startup, utc_nnstreamer_pipeline_tensor_data_cleanup},

  {"utc_ml_single_open_p", utc_ml_single_open_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_open_n", utc_ml_single_open_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_close_p", utc_ml_single_close_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_close_n", utc_ml_single_close_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_invoke_p", utc_ml_single_invoke_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},

  {"utc_ml_single_invoke_n", utc_ml_single_invoke_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_input_info_p", utc_ml_single_get_input_info_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_input_info_n", utc_ml_single_get_input_info_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_output_info_p", utc_ml_single_get_output_info_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_output_info_n", utc_ml_single_get_output_info_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},

  {"utc_ml_single_set_timeout_p", utc_ml_single_set_timeout_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_set_timeout_n", utc_ml_single_set_timeout_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_set_input_info_p", utc_ml_single_set_input_info_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_set_input_info_n", utc_ml_single_set_input_info_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_set_property_p", utc_ml_single_set_property_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},

  {"utc_ml_single_set_property_n", utc_ml_single_set_property_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_property_p", utc_ml_single_get_property_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_get_property_n", utc_ml_single_get_property_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_invoke_dynamic_p", utc_ml_single_invoke_dynamic_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_invoke_dynamic_n", utc_ml_single_invoke_dynamic_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},

  {"utc_ml_single_open_full_p", utc_ml_single_open_full_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_open_full_n", utc_ml_single_open_full_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_invoke_fast_p", utc_ml_single_invoke_fast_p, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_ml_single_invoke_fast_n", utc_ml_single_invoke_fast_n, utc_nnstreamer_single_startup, utc_nnstreamer_single_cleanup},
  {"utc_nnstreamer_scenario_construct_destruct_empty_pipeline_p", utc_nnstreamer_scenario_construct_destruct_empty_pipeline_p, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_construct_destruct_pipeline_p1", utc_nnstreamer_scenario_construct_destruct_pipeline_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_construct_destruct_pipeline_p2", utc_nnstreamer_scenario_construct_destruct_pipeline_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_construct_pipeline_error_case_n1", utc_nnstreamer_scenario_construct_pipeline_error_case_n1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_construct_pipeline_error_case_n2", utc_nnstreamer_scenario_construct_pipeline_error_case_n2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_pipeline_state_test_p1", utc_nnstreamer_scenario_pipeline_state_test_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_pipeline_state_test_p2", utc_nnstreamer_scenario_pipeline_state_test_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_pipeline_state_test_p3", utc_nnstreamer_scenario_pipeline_state_test_p3, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_valve_error_cases_n", utc_nnstreamer_scenario_valve_error_cases_n, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_sink_p1", utc_nnstreamer_scenario_sink_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_sink_p2", utc_nnstreamer_scenario_sink_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_sink_error_cases_n", utc_nnstreamer_scenario_sink_error_cases_n, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_src_p", utc_nnstreamer_scenario_src_p, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_src_error_case_n1", utc_nnstreamer_scenario_src_error_case_n1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_src_error_case_n2", utc_nnstreamer_scenario_src_error_case_n2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_src_error_case_n3", utc_nnstreamer_scenario_src_error_case_n3, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_switch_pipeline_p1", utc_nnstreamer_scenario_switch_pipeline_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_switch_pipeline_p2", utc_nnstreamer_scenario_switch_pipeline_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_switch_pipeline_error_cases_n", utc_nnstreamer_scenario_switch_pipeline_error_cases_n, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_check_tensor_info_utilities_p", utc_nnstreamer_scenario_check_tensor_info_utilities_p, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_filter_tensorflow_lite_p1", utc_nnstreamer_scenario_filter_tensorflow_lite_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_filter_tensorflow_lite_p2", utc_nnstreamer_scenario_filter_tensorflow_lite_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_filter_tensorflow_lite_n", utc_nnstreamer_scenario_filter_tensorflow_lite_n, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_flatbuf_p", utc_nnstreamer_scenario_flatbuf_p, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_flatbuf_n1", utc_nnstreamer_scenario_flatbuf_n1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_flatbuf_n2", utc_nnstreamer_scenario_flatbuf_n2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_scenario_flatbuf_n3", utc_nnstreamer_scenario_flatbuf_n3, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_flatbuf_n4", utc_nnstreamer_scenario_flatbuf_n4, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_flatbuf_n5", utc_nnstreamer_scenario_flatbuf_n5, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_capi_element_p1", utc_nnstreamer_scenario_capi_element_p1, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},
  {"utc_nnstreamer_scenario_capi_element_p2", utc_nnstreamer_scenario_capi_element_p2, utc_nnstreamer_scenario_startup, utc_nnstreamer_scenario_cleanup},

  {"utc_nnstreamer_capi_element_get_handle_p", utc_nnstreamer_capi_element_get_handle_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_handle_n1", utc_nnstreamer_capi_element_get_handle_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_handle_n2", utc_nnstreamer_capi_element_get_handle_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_release_handle_p", utc_nnstreamer_capi_element_release_handle_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_release_handle_n1", utc_nnstreamer_capi_element_release_handle_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_release_handle_n2", utc_nnstreamer_capi_element_release_handle_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_bool_property_p", utc_nnstreamer_capi_element_set_bool_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_bool_property_n1", utc_nnstreamer_capi_element_set_bool_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_bool_property_n2", utc_nnstreamer_capi_element_set_bool_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_bool_property_p", utc_nnstreamer_capi_element_get_bool_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_bool_property_n1", utc_nnstreamer_capi_element_get_bool_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_bool_property_n2", utc_nnstreamer_capi_element_get_bool_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_bool_property_n3", utc_nnstreamer_capi_element_get_bool_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_bool_property_n4", utc_nnstreamer_capi_element_get_bool_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_string_property_p", utc_nnstreamer_capi_element_set_string_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_string_property_n1", utc_nnstreamer_capi_element_set_string_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_string_property_n2", utc_nnstreamer_capi_element_set_string_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_string_property_p", utc_nnstreamer_capi_element_get_string_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_string_property_n1", utc_nnstreamer_capi_element_get_string_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_string_property_n2", utc_nnstreamer_capi_element_get_string_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_string_property_n3", utc_nnstreamer_capi_element_get_string_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_string_property_n4", utc_nnstreamer_capi_element_get_string_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int32_property_p", utc_nnstreamer_capi_element_set_int32_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int32_property_n1", utc_nnstreamer_capi_element_set_int32_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int32_property_n2", utc_nnstreamer_capi_element_set_int32_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_int32_property_n3", utc_nnstreamer_capi_element_set_int32_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int32_property_p", utc_nnstreamer_capi_element_get_int32_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int32_property_n1", utc_nnstreamer_capi_element_get_int32_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int32_property_n2", utc_nnstreamer_capi_element_get_int32_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int32_property_n3", utc_nnstreamer_capi_element_get_int32_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_int32_property_n4", utc_nnstreamer_capi_element_get_int32_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int64_property_p", utc_nnstreamer_capi_element_set_int64_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int64_property_n1", utc_nnstreamer_capi_element_set_int64_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int64_property_n2", utc_nnstreamer_capi_element_set_int64_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_int64_property_n3", utc_nnstreamer_capi_element_set_int64_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_int64_property_p", utc_nnstreamer_capi_element_get_int64_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int64_property_n1", utc_nnstreamer_capi_element_get_int64_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int64_property_n2", utc_nnstreamer_capi_element_get_int64_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int64_property_n3", utc_nnstreamer_capi_element_get_int64_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_int64_property_n4", utc_nnstreamer_capi_element_get_int64_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_uint32_property_p", utc_nnstreamer_capi_element_set_uint32_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint32_property_n1", utc_nnstreamer_capi_element_set_uint32_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint32_property_n2", utc_nnstreamer_capi_element_set_uint32_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint32_property_n3", utc_nnstreamer_capi_element_set_uint32_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint32_property_p", utc_nnstreamer_capi_element_get_uint32_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_uint32_property_n1", utc_nnstreamer_capi_element_get_uint32_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint32_property_n2", utc_nnstreamer_capi_element_get_uint32_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint32_property_n3", utc_nnstreamer_capi_element_get_uint32_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint32_property_n4", utc_nnstreamer_capi_element_get_uint32_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint64_property_p", utc_nnstreamer_capi_element_set_uint64_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_uint64_property_n1", utc_nnstreamer_capi_element_set_uint64_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint64_property_n2", utc_nnstreamer_capi_element_set_uint64_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_uint64_property_n3", utc_nnstreamer_capi_element_set_uint64_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint64_property_p", utc_nnstreamer_capi_element_get_uint64_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint64_property_n1", utc_nnstreamer_capi_element_get_uint64_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_uint64_property_n2", utc_nnstreamer_capi_element_get_uint64_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint64_property_n3", utc_nnstreamer_capi_element_get_uint64_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_uint64_property_n4", utc_nnstreamer_capi_element_get_uint64_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_double_property_p", utc_nnstreamer_capi_element_set_double_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_double_property_n1", utc_nnstreamer_capi_element_set_double_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_double_property_n2", utc_nnstreamer_capi_element_set_double_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_double_property_n3", utc_nnstreamer_capi_element_set_double_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_double_property_p", utc_nnstreamer_capi_element_get_double_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_double_property_n1", utc_nnstreamer_capi_element_get_double_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_double_property_n2", utc_nnstreamer_capi_element_get_double_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_double_property_n3", utc_nnstreamer_capi_element_get_double_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_double_property_n4", utc_nnstreamer_capi_element_get_double_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_enum_property_p", utc_nnstreamer_capi_element_set_enum_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_enum_property_n1", utc_nnstreamer_capi_element_set_enum_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_set_enum_property_n2", utc_nnstreamer_capi_element_set_enum_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_set_enum_property_n3", utc_nnstreamer_capi_element_set_enum_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_enum_property_p", utc_nnstreamer_capi_element_get_enum_property_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_enum_property_n1", utc_nnstreamer_capi_element_get_enum_property_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_enum_property_n2", utc_nnstreamer_capi_element_get_enum_property_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_element_get_enum_property_n3", utc_nnstreamer_capi_element_get_enum_property_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_element_get_enum_property_n4", utc_nnstreamer_capi_element_get_enum_property_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_p", utc_nnstreamer_capi_custom_filter_registration_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n1", utc_nnstreamer_capi_custom_filter_registration_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n2", utc_nnstreamer_capi_custom_filter_registration_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n3", utc_nnstreamer_capi_custom_filter_registration_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_custom_filter_registration_n4", utc_nnstreamer_capi_custom_filter_registration_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n5", utc_nnstreamer_capi_custom_filter_registration_n5, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n6", utc_nnstreamer_capi_custom_filter_registration_n6, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n7", utc_nnstreamer_capi_custom_filter_registration_n7, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_custom_filter_registration_n8", utc_nnstreamer_capi_custom_filter_registration_n8, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_custom_filter_registration_n9", utc_nnstreamer_capi_custom_filter_registration_n9, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_registration_p", utc_nnstreamer_capi_tensor_if_custom_registration_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_registration_n1", utc_nnstreamer_capi_tensor_if_custom_registration_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_registration_n2", utc_nnstreamer_capi_tensor_if_custom_registration_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_registration_n3", utc_nnstreamer_capi_tensor_if_custom_registration_n3, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_nnstreamer_capi_tensor_if_custom_registration_n4", utc_nnstreamer_capi_tensor_if_custom_registration_n4, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_unregistration_p", utc_nnstreamer_capi_tensor_if_custom_unregistration_p, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_unregistration_n1", utc_nnstreamer_capi_tensor_if_custom_unregistration_n1, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},
  {"utc_nnstreamer_capi_tensor_if_custom_unregistration_n2", utc_nnstreamer_capi_tensor_if_custom_unregistration_n2, utc_nnstreamer_capi_startup, utc_nnstreamer_capi_cleanup},

  {"utc_ml_service_set_pipeline_p1", utc_ml_service_set_pipeline_p1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_set_pipeline_p2", utc_ml_service_set_pipeline_p2, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_set_pipeline_n1", utc_ml_service_set_pipeline_n1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_set_pipeline_n2", utc_ml_service_set_pipeline_n2, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_get_pipeline_p1", utc_ml_service_get_pipeline_p1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_get_pipeline_n1", utc_ml_service_get_pipeline_n1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_get_pipeline_n2", utc_ml_service_get_pipeline_n2, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_delete_pipeline_p1", utc_ml_service_delete_pipeline_p1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_delete_pipeline_n1", utc_ml_service_delete_pipeline_n1, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_delete_pipeline_n2", utc_ml_service_delete_pipeline_n2, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {"utc_ml_service_delete_pipeline_n3", utc_ml_service_delete_pipeline_n3, utc_machine_learning_service_startup, utc_machine_learning_service_cleanup},
  {NULL, NULL}
};

#endif // __TCT_NNSTREAMER-NATIVE_H__
