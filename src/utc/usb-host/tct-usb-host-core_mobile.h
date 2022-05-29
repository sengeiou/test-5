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
#ifndef __TCT_USB-HOST-NATIVE_H__
#define __TCT_USB-HOST-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_usb_host_context_startup(void);
extern void utc_usb_host_context_cleanup(void);
extern void utc_usb_host_device_startup(void);
extern void utc_usb_host_device_cleanup(void);
extern void utc_usb_host_config_startup(void);
extern void utc_usb_host_config_cleanup(void);
extern void utc_usb_host_async_transfer_startup(void);
extern void utc_usb_host_control_transfer_startup(void);
extern void utc_usb_host_async_transfer_cleanup(void);
extern void utc_usb_host_control_transfer_cleanup(void);

extern int utc_usb_host_create_p(void);
extern int utc_usb_host_create_n(void);
extern int utc_usb_host_get_device_list_n(void);
extern int utc_usb_host_get_device_list_p(void);
extern int utc_usb_host_free_device_list_n(void);
extern int utc_usb_host_device_open_p(void);
extern int utc_usb_host_device_open_n(void);
extern int utc_usb_host_device_close_p(void);
extern int utc_usb_host_device_close_n(void);
extern int utc_usb_host_device_open_with_vid_pid_p(void);
extern int utc_usb_host_device_open_with_vid_pid_n(void);
extern int utc_usb_host_ref_device_p(void);
extern int utc_usb_host_ref_device_n(void);
extern int utc_usb_host_unref_device_p(void);
extern int utc_usb_host_unref_device_n(void);
extern int utc_usb_host_device_get_bus_number_p(void);
extern int utc_usb_host_device_get_bus_number_n(void);
extern int utc_usb_host_device_get_address_p(void);
extern int utc_usb_host_device_get_address_n(void);
extern int utc_usb_host_device_get_config_p(void);
extern int utc_usb_host_device_get_config_invalid_n(void);
extern int utc_usb_host_device_get_config_not_found_n(void);
extern int utc_usb_host_get_active_config_p(void);
extern int utc_usb_host_get_active_config_n(void);
extern int utc_usb_host_set_config_n(void);
extern int utc_usb_host_set_config_p(void);
extern int utc_usb_host_device_get_bcd_usb_p(void);
extern int utc_usb_host_device_get_bcd_usb_n(void);
extern int utc_usb_host_device_get_class_p(void);
extern int utc_usb_host_device_get_class_n(void);
extern int utc_usb_host_device_get_sub_class_p(void);
extern int utc_usb_host_device_get_sub_class_n(void);
extern int utc_usb_host_device_get_protocol_p(void);
extern int utc_usb_host_device_get_protocol_n(void);
extern int utc_usb_host_device_get_max_packet_size_0_p(void);
extern int utc_usb_host_device_get_max_packet_size_0_n(void);
extern int utc_usb_host_device_get_id_vendor_p(void);
extern int utc_usb_host_device_get_id_vendor_n(void);
extern int utc_usb_host_device_get_id_product_p(void);
extern int utc_usb_host_device_get_id_product_n(void);
extern int utc_usb_host_device_get_bcd_device_p(void);
extern int utc_usb_host_device_get_bcd_device_n(void);
extern int utc_usb_host_device_get_num_configurations_p(void);
extern int utc_usb_host_device_get_num_configurations_n(void);
extern int utc_usb_host_is_device_opened_p(void);
extern int utc_usb_host_is_device_opened_n(void);
extern int utc_usb_host_device_get_manufacturer_str_p(void);
extern int utc_usb_host_device_get_manufacturer_str_n(void);
extern int utc_usb_host_device_get_product_str_p(void);
extern int utc_usb_host_device_get_product_str_n(void);
extern int utc_usb_host_device_get_serial_number_str_p(void);
extern int utc_usb_host_device_get_serial_number_str_n(void);
extern int utc_usb_host_config_destroy_p(void);
extern int utc_usb_host_config_destroy_n(void);
extern int utc_usb_host_config_get_num_interfaces_p(void);
extern int utc_usb_host_config_get_num_interfaces_n(void);
extern int utc_usb_host_config_is_self_powered_p(void);
extern int utc_usb_host_config_is_self_powered_n(void);
extern int utc_usb_host_config_support_remote_wakeup_p(void);
extern int utc_usb_host_config_support_remote_wakeup_n(void);
extern int utc_usb_host_config_get_max_power_p(void);
extern int utc_usb_host_config_get_max_power_n(void);
extern int utc_usb_host_config_get_str_p(void);
extern int utc_usb_host_config_get_str_n(void);
extern int utc_usb_host_interface_get_altsetting_n(void);
extern int utc_usb_host_device_get_port_numbers_n(void);
extern int utc_usb_host_config_get_interface_p(void);
extern int utc_usb_host_config_get_interface_n(void);
extern int utc_usb_host_claim_interface_p(void);
extern int utc_usb_host_claim_interface_n(void);
extern int utc_usb_host_release_interface_p(void);
extern int utc_usb_host_release_interface_n(void);
extern int utc_usb_host_interface_get_number_p(void);
extern int utc_usb_host_interface_get_number_n(void);
extern int utc_usb_host_interface_get_num_endpoints_p(void);
extern int utc_usb_host_interface_get_num_endpoints_n(void);
extern int utc_usb_host_interface_get_endpoint_p(void);
extern int utc_usb_host_interface_get_endpoint_n(void);
extern int utc_usb_host_interface_get_str_p(void);
extern int utc_usb_host_interface_get_str_n(void);
extern int utc_usb_host_endpoint_get_number_p(void);
extern int utc_usb_host_endpoint_get_number_n(void);
extern int utc_usb_host_endpoint_get_direction_p(void);
extern int utc_usb_host_endpoint_get_direction_n(void);
extern int utc_usb_host_endpoint_get_transfer_type_p(void);
extern int utc_usb_host_endpoint_get_transfer_type_n(void);
extern int utc_usb_host_endpoint_get_synch_type_p(void);
extern int utc_usb_host_endpoint_get_synch_type_n(void);
extern int utc_usb_host_endpoint_get_usage_type_p(void);
extern int utc_usb_host_endpoint_get_usage_type_n(void);
extern int utc_usb_host_endpoint_get_max_packet_size_p(void);
extern int utc_usb_host_endpoint_get_max_packet_size_n(void);
extern int utc_usb_host_endpoint_get_interval_p(void);
extern int utc_usb_host_endpoint_get_interval_n(void);
extern int utc_usb_host_transfer_p(void);
extern int utc_usb_host_interrupt_transfer_p(void);
extern int utc_usb_host_transfer_n(void);
extern int utc_usb_host_control_transfer_p(void);
extern int utc_usb_host_control_transfer_n(void);
extern int utc_usb_host_set_altsetting_p(void);
extern int utc_usb_host_set_altsetting_n(void);
extern int utc_usb_host_device_unconfigure_n(void);
extern int utc_usb_host_create_transfer_n(void);
extern int utc_usb_host_create_transfer_p(void);
extern int utc_usb_host_create_isochronous_transfer_n(void);
extern int utc_usb_host_create_control_transfer_n(void);
extern int utc_usb_host_create_control_transfer_p(void);
extern int utc_usb_host_transfer_set_ep_n(void);
extern int utc_usb_host_transfer_set_ep_p(void);
extern int utc_usb_host_transfer_set_callback_n(void);
extern int utc_usb_host_transfer_set_callback_p(void);
extern int utc_usb_host_transfer_set_data_n(void);
extern int utc_usb_host_transfer_set_data_p(void);
extern int utc_usb_host_transfer_set_timeout_n(void);
extern int utc_usb_host_transfer_set_timeout_p(void);
extern int utc_usb_host_transfer_set_num_iso_packets_n(void);
extern int utc_usb_host_transfer_set_num_iso_packets_p(void);
extern int utc_usb_host_control_transfer_set_request_type_n(void);
extern int utc_usb_host_control_transfer_set_request_type_p(void);
extern int utc_usb_host_control_transfer_set_request_n(void);
extern int utc_usb_host_control_transfer_set_request_p(void);
extern int utc_usb_host_control_transfer_set_value_n(void);
extern int utc_usb_host_control_transfer_set_value_p(void);
extern int utc_usb_host_control_transfer_set_index_n(void);
extern int utc_usb_host_control_transfer_set_index_p(void);
extern int utc_usb_host_transfer_get_status_n(void);
extern int utc_usb_host_transfer_get_status_p(void);
extern int utc_usb_host_transfer_get_data_n(void);
extern int utc_usb_host_transfer_get_data_p(void);
extern int utc_usb_host_control_transfer_get_data_n(void);
extern int utc_usb_host_control_transfer_get_data_p(void);
extern int utc_usb_host_transfer_get_length_n(void);
extern int utc_usb_host_transfer_get_length_p(void);
extern int utc_usb_host_transfer_get_num_iso_packets_n(void);
extern int utc_usb_host_transfer_get_num_iso_packets_p(void);
extern int utc_usb_host_transfer_set_iso_packet_length_n(void);
extern int utc_usb_host_transfer_get_iso_packet_status_n(void);
extern int utc_usb_host_transfer_get_iso_packet_data_n(void);
extern int utc_usb_host_transfer_get_iso_packet_length_n(void);
extern int utc_usb_host_transfer_get_type_n(void);
extern int utc_usb_host_transfer_get_type_p(void);
extern int utc_usb_host_transfer_destroy_n(void);
extern int utc_usb_host_transfer_destroy_p(void);
extern int utc_usb_host_transfer_submit_n(void);
extern int utc_usb_host_transfer_submit_p(void);
extern int utc_usb_host_transfer_cancel_n(void);
extern int utc_usb_host_transfer_cancel_p(void);


testcase tc_array[] = {
    {"utc_usb_host_create_p", utc_usb_host_create_p, NULL, NULL},
    {"utc_usb_host_create_n", utc_usb_host_create_n, NULL, NULL},
    {"utc_usb_host_get_device_list_p", utc_usb_host_get_device_list_p, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_get_device_list_n",utc_usb_host_get_device_list_n, NULL, NULL},
    {"utc_usb_host_free_device_list_n", utc_usb_host_free_device_list_n, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_open_p", utc_usb_host_device_open_p, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_open_n", utc_usb_host_device_open_n, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_close_n", utc_usb_host_device_close_n, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_close_p", utc_usb_host_device_close_p, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_open_with_vid_pid_p", utc_usb_host_device_open_with_vid_pid_p, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_open_with_vid_pid_n", utc_usb_host_device_open_with_vid_pid_n, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_ref_device_p", utc_usb_host_ref_device_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_ref_device_n", utc_usb_host_ref_device_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_unref_device_p", utc_usb_host_unref_device_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_unref_device_n", utc_usb_host_unref_device_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_bus_number_p", utc_usb_host_device_get_bus_number_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_bus_number_n", utc_usb_host_device_get_bus_number_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_address_p", utc_usb_host_device_get_address_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_address_n", utc_usb_host_device_get_address_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_config_p", utc_usb_host_device_get_config_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_config_invalid_n", utc_usb_host_device_get_config_invalid_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_config_not_found_n", utc_usb_host_device_get_config_not_found_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_get_active_config_p", utc_usb_host_get_active_config_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_get_active_config_n", utc_usb_host_get_active_config_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_set_config_n",utc_usb_host_set_config_n,NULL,NULL},
    {"utc_usb_host_set_config_p",utc_usb_host_set_config_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_device_get_bcd_usb_p", utc_usb_host_device_get_bcd_usb_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_bcd_usb_n", utc_usb_host_device_get_bcd_usb_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_class_p", utc_usb_host_device_get_class_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_class_n", utc_usb_host_device_get_class_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_sub_class_p", utc_usb_host_device_get_sub_class_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_sub_class_n", utc_usb_host_device_get_sub_class_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_protocol_p", utc_usb_host_device_get_protocol_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_protocol_n", utc_usb_host_device_get_protocol_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_max_packet_size_0_p", utc_usb_host_device_get_max_packet_size_0_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_max_packet_size_0_n", utc_usb_host_device_get_max_packet_size_0_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_id_vendor_p", utc_usb_host_device_get_id_vendor_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_id_vendor_n", utc_usb_host_device_get_id_vendor_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_id_product_p", utc_usb_host_device_get_id_product_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_id_product_n", utc_usb_host_device_get_id_product_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_bcd_device_p", utc_usb_host_device_get_bcd_device_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_bcd_device_n", utc_usb_host_device_get_bcd_device_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_num_configurations_p", utc_usb_host_device_get_num_configurations_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_num_configurations_n", utc_usb_host_device_get_num_configurations_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_is_device_opened_p", utc_usb_host_is_device_opened_p, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_is_device_opened_n", utc_usb_host_is_device_opened_n, utc_usb_host_context_startup, utc_usb_host_context_cleanup},
    {"utc_usb_host_device_get_manufacturer_str_p", utc_usb_host_device_get_manufacturer_str_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_manufacturer_str_n", utc_usb_host_device_get_manufacturer_str_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_product_str_p", utc_usb_host_device_get_product_str_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_product_str_n", utc_usb_host_device_get_product_str_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_serial_number_str_p", utc_usb_host_device_get_serial_number_str_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_device_get_serial_number_str_n", utc_usb_host_device_get_serial_number_str_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_config_destroy_p", utc_usb_host_config_destroy_p, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_config_destroy_n", utc_usb_host_config_destroy_n, utc_usb_host_device_startup, utc_usb_host_device_cleanup},
    {"utc_usb_host_config_get_num_interfaces_p", utc_usb_host_config_get_num_interfaces_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_num_interfaces_n", utc_usb_host_config_get_num_interfaces_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_is_self_powered_p", utc_usb_host_config_is_self_powered_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_is_self_powered_n", utc_usb_host_config_is_self_powered_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_support_remote_wakeup_p", utc_usb_host_config_support_remote_wakeup_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_support_remote_wakeup_n", utc_usb_host_config_support_remote_wakeup_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_max_power_p", utc_usb_host_config_get_max_power_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_max_power_n", utc_usb_host_config_get_max_power_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_str_p", utc_usb_host_config_get_str_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_str_n", utc_usb_host_config_get_str_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_altsetting_n",utc_usb_host_interface_get_altsetting_n,NULL,NULL},
    {"utc_usb_host_device_get_port_numbers_n", utc_usb_host_device_get_port_numbers_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_interface_p", utc_usb_host_config_get_interface_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_config_get_interface_n", utc_usb_host_config_get_interface_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_claim_interface_p", utc_usb_host_claim_interface_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_claim_interface_n", utc_usb_host_claim_interface_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_release_interface_p", utc_usb_host_release_interface_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_release_interface_n", utc_usb_host_release_interface_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_number_p", utc_usb_host_interface_get_number_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_number_n", utc_usb_host_interface_get_number_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_num_endpoints_p", utc_usb_host_interface_get_num_endpoints_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_num_endpoints_n", utc_usb_host_interface_get_num_endpoints_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_endpoint_p", utc_usb_host_interface_get_endpoint_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_endpoint_n", utc_usb_host_interface_get_endpoint_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_str_p", utc_usb_host_interface_get_str_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interface_get_str_n", utc_usb_host_interface_get_str_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_number_p", utc_usb_host_endpoint_get_number_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_number_n", utc_usb_host_endpoint_get_number_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_direction_p", utc_usb_host_endpoint_get_direction_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_direction_n", utc_usb_host_endpoint_get_direction_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_transfer_type_p", utc_usb_host_endpoint_get_transfer_type_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_transfer_type_n", utc_usb_host_endpoint_get_transfer_type_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_synch_type_p", utc_usb_host_endpoint_get_synch_type_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_synch_type_n", utc_usb_host_endpoint_get_synch_type_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_usage_type_p", utc_usb_host_endpoint_get_usage_type_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_usage_type_n", utc_usb_host_endpoint_get_usage_type_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_max_packet_size_p", utc_usb_host_endpoint_get_max_packet_size_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_max_packet_size_n", utc_usb_host_endpoint_get_max_packet_size_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_interval_p", utc_usb_host_endpoint_get_interval_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_endpoint_get_interval_n", utc_usb_host_endpoint_get_interval_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_transfer_p", utc_usb_host_transfer_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_interrupt_transfer_p", utc_usb_host_interrupt_transfer_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_transfer_n", utc_usb_host_transfer_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_control_transfer_p", utc_usb_host_control_transfer_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_control_transfer_n", utc_usb_host_control_transfer_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_set_altsetting_p", utc_usb_host_set_altsetting_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_set_altsetting_n", utc_usb_host_set_altsetting_n, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_device_unconfigure_n",utc_usb_host_device_unconfigure_n,NULL,NULL},
    {"utc_usb_host_create_transfer_n", utc_usb_host_create_transfer_n, NULL, NULL},
    {"utc_usb_host_create_transfer_p", utc_usb_host_create_transfer_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_create_isochronous_transfer_n", utc_usb_host_create_isochronous_transfer_n, NULL, NULL},
    {"utc_usb_host_create_control_transfer_n", utc_usb_host_create_control_transfer_n, NULL, NULL},
    {"utc_usb_host_create_control_transfer_p", utc_usb_host_create_control_transfer_p, utc_usb_host_config_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_transfer_set_ep_n", utc_usb_host_transfer_set_ep_n, NULL, NULL},
    {"utc_usb_host_transfer_set_ep_p", utc_usb_host_transfer_set_ep_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_set_callback_n", utc_usb_host_transfer_set_callback_n, NULL, NULL},
    {"utc_usb_host_transfer_set_callback_p", utc_usb_host_transfer_set_callback_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_set_data_n", utc_usb_host_transfer_set_data_n, NULL, NULL},
    {"utc_usb_host_transfer_set_data_p", utc_usb_host_transfer_set_data_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_set_timeout_n", utc_usb_host_transfer_set_timeout_n, NULL, NULL},
    {"utc_usb_host_transfer_set_timeout_p", utc_usb_host_transfer_set_timeout_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_set_num_iso_packets_n", utc_usb_host_transfer_set_num_iso_packets_n, NULL, NULL},
    {"utc_usb_host_transfer_set_num_iso_packets_p", utc_usb_host_transfer_set_num_iso_packets_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_control_transfer_set_request_type_n", utc_usb_host_control_transfer_set_request_type_n, NULL, NULL},
    {"utc_usb_host_control_transfer_set_request_type_p", utc_usb_host_control_transfer_set_request_type_p, utc_usb_host_control_transfer_startup, utc_usb_host_control_transfer_cleanup},
    {"utc_usb_host_control_transfer_set_request_n", utc_usb_host_control_transfer_set_request_n, NULL, NULL},
    {"utc_usb_host_control_transfer_set_request_p", utc_usb_host_control_transfer_set_request_p, utc_usb_host_control_transfer_startup, utc_usb_host_control_transfer_cleanup},
    {"utc_usb_host_control_transfer_set_value_n", utc_usb_host_control_transfer_set_value_n, NULL, NULL},
    {"utc_usb_host_control_transfer_set_value_p", utc_usb_host_control_transfer_set_value_p, utc_usb_host_control_transfer_startup, utc_usb_host_control_transfer_cleanup},
    {"utc_usb_host_control_transfer_set_index_n", utc_usb_host_control_transfer_set_index_n, NULL, NULL},
    {"utc_usb_host_control_transfer_set_index_p", utc_usb_host_control_transfer_set_index_p, utc_usb_host_control_transfer_startup, utc_usb_host_control_transfer_cleanup},
    {"utc_usb_host_transfer_get_status_n", utc_usb_host_transfer_get_status_n, NULL, NULL},
    {"utc_usb_host_transfer_get_status_p", utc_usb_host_transfer_get_status_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_get_data_n", utc_usb_host_transfer_get_data_n, NULL, NULL},
    {"utc_usb_host_transfer_get_data_p", utc_usb_host_transfer_get_data_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_control_transfer_get_data_n", utc_usb_host_control_transfer_get_data_n, NULL, NULL},
    {"utc_usb_host_control_transfer_get_data_p", utc_usb_host_control_transfer_get_data_p, utc_usb_host_control_transfer_startup, utc_usb_host_control_transfer_cleanup},
    {"utc_usb_host_transfer_get_length_n", utc_usb_host_transfer_get_length_n, NULL, NULL},
    {"utc_usb_host_transfer_get_length_p", utc_usb_host_transfer_get_length_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_get_num_iso_packets_n", utc_usb_host_transfer_get_num_iso_packets_n, NULL, NULL},
    {"utc_usb_host_transfer_get_num_iso_packets_p", utc_usb_host_transfer_get_num_iso_packets_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_set_iso_packet_length_n", utc_usb_host_transfer_set_iso_packet_length_n, NULL, NULL},
    {"utc_usb_host_transfer_get_iso_packet_status_n", utc_usb_host_transfer_get_iso_packet_status_n, NULL, NULL},
    {"utc_usb_host_transfer_get_iso_packet_data_n", utc_usb_host_transfer_get_iso_packet_data_n, NULL, NULL},
    {"utc_usb_host_transfer_get_iso_packet_length_n", utc_usb_host_transfer_get_iso_packet_length_n, NULL, NULL},
    {"utc_usb_host_transfer_get_type_n", utc_usb_host_transfer_get_type_n, NULL, NULL},
    {"utc_usb_host_transfer_get_type_p", utc_usb_host_transfer_get_type_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_destroy_n", utc_usb_host_transfer_destroy_n, NULL, NULL},
    {"utc_usb_host_transfer_destroy_p", utc_usb_host_transfer_destroy_p, utc_usb_host_async_transfer_startup, utc_usb_host_config_cleanup},
    {"utc_usb_host_transfer_submit_n", utc_usb_host_transfer_submit_n, NULL, NULL},
    {"utc_usb_host_transfer_submit_p", utc_usb_host_transfer_submit_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {"utc_usb_host_transfer_cancel_n", utc_usb_host_transfer_cancel_n, NULL, NULL},
    {"utc_usb_host_transfer_cancel_p", utc_usb_host_transfer_cancel_p, utc_usb_host_async_transfer_startup, utc_usb_host_async_transfer_cleanup},
    {NULL, NULL}
};

#endif // __TCT_USB-HOST-NATIVE_H__
