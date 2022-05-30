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
#ifndef __TCT_CION_NATIVE_H__
#define __TCT_CION_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_cion_client_startup(void);
extern void ITs_cion_client_cleanup(void);
extern void ITs_cion_group_startup(void);
extern void ITs_cion_group_cleanup(void);
extern void ITs_cion_security_startup(void);
extern void ITs_cion_security_cleanup(void);
extern void ITs_cion_payload_startup(void);
extern void ITs_cion_payload_cleanup(void);
extern void ITs_cion_payload_async_startup(void);
extern void ITs_cion_payload_async_cleanup(void);
extern void ITs_cion_peer_info_startup(void);
extern void ITs_cion_peer_info_cleanup(void);
extern void ITs_cion_server_startup(void);
extern void ITs_cion_server_cleanup(void);

extern int ITc_cion_payload_async_result_clone_destroy_p(void);
extern int ITc_cion_payload_async_result_get_peer_info_p(void);
extern int ITc_cion_payload_async_result_get_payload_id_p(void);
extern int ITc_cion_peer_info_clone_destroy_p(void);
extern int ITc_cion_peer_info_get_device_id_p(void);
extern int ITc_cion_peer_info_get_device_name_p(void);
extern int ITc_cion_peer_info_get_device_platform_p(void);
extern int ITc_cion_peer_info_get_device_platform_version_p(void);
extern int ITc_cion_peer_info_get_device_type_p(void);
extern int ITc_cion_peer_info_get_app_id_p(void);
extern int ITc_cion_peer_info_get_app_version_p(void);
extern int ITc_cion_peer_info_get_uuid_p(void);
extern int ITc_cion_peer_info_get_display_name_p(void);
extern int ITc_cion_client_create_destroy_p(void);
extern int ITc_cion_client_send_data_p(void);
extern int ITc_cion_client_try_stop_discovery_p(void);
extern int ITc_cion_client_connect_disconnect_p(void);
extern int ITc_cion_client_send_payload_async_p(void);
extern int ITc_cion_client_add_remove_connection_result_cb_p(void);
extern int ITc_cion_client_add_remove_payload_received_cb_p(void);
extern int ITc_cion_client_add_remove_disconnected_cb_p(void);
extern int ITc_cion_group_create_destroy_p(void);
extern int ITc_cion_group_subscribe_unsubscribe_p(void);
extern int ITc_cion_group_publish_p(void);
extern int ITc_cion_security_create_destory_p(void);
extern int ITc_cion_security_set_get_ca_path_p(void);
extern int ITc_cion_security_set_get_cert_path_p(void);
extern int ITc_cion_security_set_get_private_key_path_p(void);
extern int ITc_cion_payload_create_destroy_p(void);
extern int ITc_cion_payload_get_type_p(void);
extern int ITc_cion_payload_set_get_data_p(void);
extern int ITc_cion_payload_set_file_path_p(void);
extern int ITc_cion_payload_get_payload_id_p(void);
extern int ITc_cion_payload_save_as_file_p(void);
extern int ITc_cion_payload_get_received_file_name_p(void);
extern int ITc_cion_payload_get_received_bytes_p(void);
extern int ITc_cion_payload_get_total_bytes_p(void);
extern int ITc_cion_server_create_destroy_p(void);
extern int ITc_cion_server_listen_stop_p(void);
extern int ITc_cion_server_add_remove_connection_result_cb_p(void);
extern int ITc_cion_server_add_remove_payload_received_cb_p(void);
extern int ITc_cion_server_set_unset_data_received_cb_p(void);
extern int ITc_cion_server_add_remove_disconnected_cb_p(void);
extern int ITc_cion_server_accept_p(void);
extern int ITc_cion_server_set_display_name_p(void);
extern int ITc_cion_server_foreach_connected_peer_info_p(void);
extern int ITc_cion_server_set_on_demand_launch_enabled_p(void);
extern int ITc_cion_server_reject_p(void);
extern int ITc_cion_server_disconnect_p(void);
extern int ITc_cion_server_send_payload_async_p(void);

testcase tc_array[] = {
	{"ITc_cion_payload_async_result_clone_destroy_p", ITc_cion_payload_async_result_clone_destroy_p, ITs_cion_payload_async_startup, ITs_cion_payload_async_cleanup},
	{"ITc_cion_payload_async_result_get_peer_info_p", ITc_cion_payload_async_result_get_peer_info_p, ITs_cion_payload_async_startup, ITs_cion_payload_async_cleanup},
	{"ITc_cion_payload_async_result_get_payload_id_p", ITc_cion_payload_async_result_get_payload_id_p, ITs_cion_payload_async_startup, ITs_cion_payload_async_cleanup},
	{"ITc_cion_peer_info_clone_destroy_p",ITc_cion_peer_info_clone_destroy_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_device_id_p", ITc_cion_peer_info_get_device_id_p,ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_device_name_p",ITc_cion_peer_info_get_device_name_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_device_platform_p",ITc_cion_peer_info_get_device_platform_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_device_platform_version_p",ITc_cion_peer_info_get_device_platform_version_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_device_type_p",ITc_cion_peer_info_get_device_type_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_app_id_p",ITc_cion_peer_info_get_app_id_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_app_version_p",ITc_cion_peer_info_get_app_version_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_uuid_p",ITc_cion_peer_info_get_uuid_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_peer_info_get_display_name_p",ITc_cion_peer_info_get_display_name_p, ITs_cion_peer_info_startup, ITs_cion_peer_info_cleanup},
	{"ITc_cion_client_create_destroy_p", ITc_cion_client_create_destroy_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_send_data_p", ITc_cion_client_send_data_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_try_stop_discovery_p", ITc_cion_client_try_stop_discovery_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_connect_disconnect_p", ITc_cion_client_connect_disconnect_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_send_payload_async_p", ITc_cion_client_send_payload_async_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_add_remove_connection_result_cb_p", ITc_cion_client_add_remove_connection_result_cb_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_add_remove_payload_received_cb_p", ITc_cion_client_add_remove_payload_received_cb_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_client_add_remove_disconnected_cb_p", ITc_cion_client_add_remove_disconnected_cb_p, ITs_cion_client_startup, ITs_cion_client_cleanup},
	{"ITc_cion_group_create_destroy_p", ITc_cion_group_create_destroy_p, ITs_cion_group_startup, ITs_cion_group_cleanup},
	{"ITc_cion_group_subscribe_unsubscribe_p", ITc_cion_group_subscribe_unsubscribe_p, ITs_cion_group_startup, ITs_cion_group_cleanup},
	{"ITc_cion_group_publish_p", ITc_cion_group_publish_p, ITs_cion_group_startup, ITs_cion_group_cleanup},
	{"ITc_cion_security_create_destory_p", ITc_cion_security_create_destory_p, ITs_cion_security_startup, ITs_cion_security_cleanup},
	{"ITc_cion_security_set_get_ca_path_p", ITc_cion_security_set_get_ca_path_p, ITs_cion_security_startup, ITs_cion_security_cleanup},
	{"ITc_cion_security_set_get_cert_path_p", ITc_cion_security_set_get_cert_path_p, ITs_cion_security_startup, ITs_cion_security_cleanup},
	{"ITc_cion_security_set_get_private_key_path_p", ITc_cion_security_set_get_private_key_path_p, ITs_cion_security_startup, ITs_cion_security_cleanup},
	{"ITc_cion_payload_create_destroy_p", ITc_cion_payload_create_destroy_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_get_type_p", ITc_cion_payload_get_type_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_set_file_path_p", ITc_cion_payload_set_file_path_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_set_file_path_p", ITc_cion_payload_set_file_path_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_set_get_data_p",ITc_cion_payload_set_get_data_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_get_payload_id_p", ITc_cion_payload_get_payload_id_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_save_as_file_p", ITc_cion_payload_save_as_file_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_get_received_file_name_p", ITc_cion_payload_get_received_file_name_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_get_received_bytes_p", ITc_cion_payload_get_received_bytes_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_payload_get_total_bytes_p", ITc_cion_payload_get_total_bytes_p, ITs_cion_payload_startup, ITs_cion_payload_cleanup},
	{"ITc_cion_server_create_destroy_p",ITc_cion_server_create_destroy_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_listen_stop_p",ITc_cion_server_listen_stop_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_add_remove_connection_result_cb_p",ITc_cion_server_add_remove_connection_result_cb_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_add_remove_payload_received_cb_p",ITc_cion_server_add_remove_payload_received_cb_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_set_unset_data_received_cb_p",ITc_cion_server_set_unset_data_received_cb_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_add_remove_disconnected_cb_p",ITc_cion_server_add_remove_disconnected_cb_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_accept_p",ITc_cion_server_accept_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_set_display_name_p",ITc_cion_server_set_display_name_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_foreach_connected_peer_info_p",ITc_cion_server_foreach_connected_peer_info_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_set_on_demand_launch_enabled_p",ITc_cion_server_set_on_demand_launch_enabled_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_reject_p",ITc_cion_server_reject_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_disconnect_p",ITc_cion_server_disconnect_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
	{"ITc_cion_server_send_payload_async_p",ITc_cion_server_send_payload_async_p, ITs_cion_server_startup, ITs_cion_server_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CION_NATIVE_H__
