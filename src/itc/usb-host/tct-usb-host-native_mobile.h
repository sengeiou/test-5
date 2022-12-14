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

extern void ITs_usbhost_startup(void);
extern void ITs_usbhost_cleanup(void);

extern int ITc_usb_host_set_unset_hotplug_cb_p(void);
extern int ITc_usb_host_create_destroy_p(void);
extern int ITc_usb_host_create_destroy_transfer_p(void);
extern int ITc_usb_host_create_control_transfer_p(void);
extern int ITc_usb_host_transfer_submit_cancel_p(void);
extern int ITc_usb_host_transfer_set_ep_p(void);
extern int ITc_usb_host_transfer_set_get_data_p(void);
extern int ITc_usb_host_transfer_get_length_p(void);
extern int ITc_host_control_transfer_set_value_p(void);
extern int ITc_usb_host_control_transfer_set_request_p(void);
extern int ITc_usb_host_control_transfer_set_request_type_p(void);
extern int ITc_usb_host_control_transfer_set_index_p(void);
extern int ITc_usb_host_transfer_set_timeout_p(void);
extern int ITc_usb_host_transfer_get_status_p(void);
extern int ITc_usb_host_transfer_get_type_p(void);
extern int ITc_usb_host_transfer_set_callback_p(void);
extern int ITc_usb_host_transfer_set_get_num_iso_packets_p(void);
extern int ITc_usb_host_control_transfer_get_data_p(void);

extern int ITc_usb_host_get_device_list_p(void);
extern int ITc_usb_host_device_open_close_p(void);
extern int ITc_usb_host_device_open_with_vid_pid_p(void);
extern int ITc_usb_host_ref_unref_device_p(void);
extern int ITc_usb_host_device_get_bus_number_p(void);
extern int ITc_usb_host_device_get_address_p(void);
extern int ITc_usb_host_device_get_config_p(void);
extern int ITc_usb_host_get_active_config_p(void);
extern int ITc_usb_host_device_get_bcd_usb_p(void);
extern int ITc_usb_host_device_get_class_p(void);
extern int ITc_usb_host_device_get_sub_class_p(void);
extern int ITc_usb_host_device_get_protocol_p(void);
extern int ITc_usb_host_device_get_max_packet_size_0_p(void);
extern int ITc_usb_host_device_get_id_vendor_p(void);
extern int ITc_usb_host_device_get_id_product_p(void);
extern int ITc_usb_host_device_get_bcd_device_p(void);
extern int ITc_usb_host_device_get_num_configurations_p(void);
extern int ITc_usb_host_device_usb_host_is_device_opened_p(void);
extern int ITc_usb_host_device_get_manufacturer_str_p(void);
extern int ITc_usb_host_device_get_product_str_p(void);
extern int ITc_usb_host_device_get_serial_number_str_p(void);
extern int ITc_usb_host_device_get_config_p(void);
extern int ITc_usb_host_device_set_config_p(void);
extern int ITc_usb_host_device_get_config_str_p(void);
extern int ITc_usb_host_device_config_get_num_interfaces_p(void);
extern int ITc_usb_host_device_config_is_self_powered_p(void);
extern int ITc_usb_host_device_config_support_remote_wakeup_p(void);
extern int ITc_usb_host_device_config_get_config_max_power_p(void);
extern int ITc_usb_host_device_config_get_interface_p(void);
extern int ITc_usb_host_claim_release_interface_p(void);
extern int ITc_usb_host_interface_get_number_p(void);
extern int ITc_usb_host_interface_get_endpoint_p(void);
extern int ITc_usb_host_interface_get_str_p(void);
extern int ITc_usb_host_interface_get_num_endpoints_p(void);
extern int ITc_usb_host_interface_set_altsetting_p(void);
extern int ITc_usb_host_endpoint_get_number_p(void);
extern int ITc_usb_host_endpoint_get_direction_p(void);
extern int ITc_usb_host_endpoint_get_transfer_type_p(void);
extern int ITc_usb_host_endpoint_get_usage_type_p(void);
extern int ITc_usb_host_endpoint_get_synch_type_p(void);
extern int ITc_usb_host_endpoint_get_max_packet_size_p(void);
extern int ITc_usb_host_endpoint_get_interval_p(void);

testcase tc_array[] = {
{"ITc_usb_host_set_unset_hotplug_cb_p",ITc_usb_host_set_unset_hotplug_cb_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_create_destroy_p",ITc_usb_host_create_destroy_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_get_device_list_p",ITc_usb_host_get_device_list_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_open_close_p",ITc_usb_host_device_open_close_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_open_with_vid_pid_p",ITc_usb_host_device_open_with_vid_pid_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_ref_unref_device_p",ITc_usb_host_ref_unref_device_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_bus_number_p",ITc_usb_host_device_get_bus_number_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_address_p",ITc_usb_host_device_get_address_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_config_p",ITc_usb_host_device_get_config_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_get_active_config_p",ITc_usb_host_get_active_config_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_bcd_usb_p",ITc_usb_host_device_get_bcd_usb_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_class_p",ITc_usb_host_device_get_class_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_sub_class_p",ITc_usb_host_device_get_sub_class_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_protocol_p",ITc_usb_host_device_get_protocol_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_max_packet_size_0_p",ITc_usb_host_device_get_max_packet_size_0_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_id_vendor_p",ITc_usb_host_device_get_id_vendor_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_id_product_p",ITc_usb_host_device_get_id_product_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_bcd_device_p",ITc_usb_host_device_get_bcd_device_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_num_configurations_p",ITc_usb_host_device_get_num_configurations_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_usb_host_is_device_opened_p",ITc_usb_host_device_usb_host_is_device_opened_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_manufacturer_str_p",ITc_usb_host_device_get_manufacturer_str_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_product_str_p",ITc_usb_host_device_get_product_str_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_serial_number_str_p",ITc_usb_host_device_get_serial_number_str_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_config_p",ITc_usb_host_device_get_config_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_set_config_p",ITc_usb_host_device_set_config_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_get_config_str_p",ITc_usb_host_device_get_config_str_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_config_get_num_interfaces_p",ITc_usb_host_set_unset_hotplug_cb_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_config_is_self_powered_p",ITc_usb_host_device_config_is_self_powered_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_config_support_remote_wakeup_p",ITc_usb_host_device_config_support_remote_wakeup_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_config_get_config_max_power_p",ITc_usb_host_device_config_get_config_max_power_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_device_config_get_interface_p",ITc_usb_host_device_config_get_interface_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_claim_release_interface_p",ITc_usb_host_claim_release_interface_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_interface_get_number_p",ITc_usb_host_interface_get_number_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_interface_get_endpoint_p",ITc_usb_host_interface_get_endpoint_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_interface_get_str_p",ITc_usb_host_interface_get_str_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_interface_get_num_endpoints_p",ITc_usb_host_interface_get_num_endpoints_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_interface_set_altsetting_p",ITc_usb_host_interface_set_altsetting_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_number_p",ITc_usb_host_endpoint_get_number_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_direction_p",ITc_usb_host_endpoint_get_direction_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_transfer_type_p",ITc_usb_host_endpoint_get_transfer_type_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_usage_type_p",ITc_usb_host_endpoint_get_usage_type_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_synch_type_p",ITc_usb_host_set_unset_hotplug_cb_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_max_packet_size_p",ITc_usb_host_endpoint_get_max_packet_size_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_endpoint_get_interval_p",ITc_usb_host_endpoint_get_interval_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_create_destroy_transfer_p",ITc_usb_host_create_destroy_transfer_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_create_control_transfer_p",ITc_usb_host_create_control_transfer_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_submit_cancel_p",ITc_usb_host_transfer_submit_cancel_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_set_ep_p",ITc_usb_host_transfer_set_ep_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_set_get_data_p",ITc_usb_host_transfer_set_get_data_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_get_length_p",ITc_usb_host_transfer_get_length_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_host_control_transfer_set_value_p",ITc_host_control_transfer_set_value_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_control_transfer_set_request_p",ITc_usb_host_control_transfer_set_request_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_control_transfer_set_request_type_p",ITc_usb_host_control_transfer_set_request_type_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_control_transfer_set_index_p",ITc_usb_host_control_transfer_set_index_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_set_timeout_p",ITc_usb_host_transfer_set_timeout_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_get_status_p",ITc_usb_host_transfer_get_status_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_get_type_p",ITc_usb_host_transfer_get_type_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_set_callback_p",ITc_usb_host_transfer_set_callback_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_transfer_set_get_num_iso_packets_p",ITc_usb_host_transfer_set_get_num_iso_packets_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{"ITc_usb_host_control_transfer_get_data_p",ITc_usb_host_control_transfer_get_data_p,ITs_usbhost_startup,ITs_usbhost_cleanup},
{NULL, NULL}
};


#endif // __TCT_USB-HOST-NATIVE_H__
