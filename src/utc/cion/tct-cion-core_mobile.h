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

extern void utc_cion_group_startup(void);
extern void utc_cion_group_cleanup(void);
extern int utc_cion_group_create_p(void);
extern int utc_cion_group_create_n(void);
extern int utc_cion_group_destroy_p(void);
extern int utc_cion_group_destroy_n(void);
extern int utc_cion_group_subscribe_p(void);
extern int utc_cion_group_subscribe_n(void);
extern int utc_cion_group_unsubscribe_p(void);
extern int utc_cion_group_unsubscribe_n(void);
extern int utc_cion_group_publish_p(void);
extern int utc_cion_group_publish_n(void);

extern void utc_cion_server_startup(void);
extern void utc_cion_server_cleanup(void);
extern int utc_cion_server_create_p(void);
extern int utc_cion_server_create_n(void);
extern int utc_cion_server_destroy_p(void);
extern int utc_cion_server_destroy_n(void);
extern int utc_cion_server_listen_p(void);
extern int utc_cion_server_listen_n(void);
extern int utc_cion_server_stop_p(void);
extern int utc_cion_server_stop_n(void);
extern int utc_cion_server_disconnect_p(void);
extern int utc_cion_server_disconnect_n(void);
extern int utc_cion_server_send_payload_async_p(void);
extern int utc_cion_server_send_payload_async_n(void);
extern int utc_cion_server_foreach_connected_peer_info_p(void);
extern int utc_cion_server_foreach_connected_peer_info_n(void);
extern int utc_cion_server_add_connection_result_cb_p(void);
extern int utc_cion_server_add_connection_result_cb_n(void);
extern int utc_cion_server_remove_connection_result_cb_p(void);
extern int utc_cion_server_remove_connection_result_cb_n(void);
extern int utc_cion_server_add_payload_received_cb_p(void);
extern int utc_cion_server_add_payload_received_cb_n(void);
extern int utc_cion_server_remove_payload_received_cb_p(void);
extern int utc_cion_server_remove_payload_received_cb_n(void);
extern int utc_cion_server_set_data_received_cb_p(void);
extern int utc_cion_server_set_data_received_cb_n(void);
extern int utc_cion_server_unset_data_received_cb_p(void);
extern int utc_cion_server_unset_data_received_cb_n(void);
extern int utc_cion_server_add_disconnected_cb_p(void);
extern int utc_cion_server_add_disconnected_cb_n(void);
extern int utc_cion_server_remove_disconnected_cb_p(void);
extern int utc_cion_server_remove_disconnected_cb_n(void);
extern int utc_cion_server_accept_p(void);
extern int utc_cion_server_accept_n(void);
extern int utc_cion_server_reject_p(void);
extern int utc_cion_server_reject_n(void);
extern int utc_cion_server_set_display_name_p(void);
extern int utc_cion_server_set_display_name_n(void);
extern int utc_cion_server_set_on_demand_launch_enabled_p(void);
extern int utc_cion_server_set_on_demand_launch_enabled_n(void);

extern void utc_cion_client_startup(void);
extern void utc_cion_client_cleanup(void);
extern int utc_cion_client_create_p(void);
extern int utc_cion_client_create_n(void);
extern int utc_cion_client_destroy_p(void);
extern int utc_cion_client_destroy_n(void);
extern int utc_cion_client_try_discovery_p(void);
extern int utc_cion_client_try_discovery_n(void);
extern int utc_cion_client_stop_discovery_p(void);
extern int utc_cion_client_stop_discovery_n(void);
extern int utc_cion_client_connect_p(void);
extern int utc_cion_client_connect_n(void);
extern int utc_cion_client_disconnect_p(void);
extern int utc_cion_client_disconnect_n(void);
extern int utc_cion_client_send_data_p(void);
extern int utc_cion_client_send_data_n(void);
extern int utc_cion_client_send_payload_async_p(void);
extern int utc_cion_client_send_payload_async_n(void);
extern int utc_cion_client_add_connection_result_cb_p(void);
extern int utc_cion_client_add_connection_result_cb_n(void);
extern int utc_cion_client_remove_connection_result_cb_p(void);
extern int utc_cion_client_remove_connection_result_cb_n(void);
extern int utc_cion_client_add_payload_received_cb_p(void);
extern int utc_cion_client_add_payload_received_cb_n(void);
extern int utc_cion_client_remove_payload_received_cb_p(void);
extern int utc_cion_client_remove_payload_received_cb_n(void);
extern int utc_cion_client_add_disconnected_cb_p(void);
extern int utc_cion_client_add_disconnected_cb_n(void);
extern int utc_cion_client_remove_disconnected_cb_p(void);
extern int utc_cion_client_remove_disconnected_cb_n(void);

extern void utc_cion_peer_info_startup(void);
extern void utc_cion_peer_info_cleanup(void);
extern int utc_cion_peer_info_clone_p(void);
extern int utc_cion_peer_info_clone_n(void);

extern int utc_cion_peer_info_get_device_id_p(void);
extern int utc_cion_peer_info_get_device_id_n(void);
extern int utc_cion_peer_info_get_device_name_p(void);
extern int utc_cion_peer_info_get_device_name_n(void);
extern int utc_cion_peer_info_get_device_platform_p(void);
extern int utc_cion_peer_info_get_device_platform_n(void);
extern int utc_cion_peer_info_get_device_platform_version_p(void);
extern int utc_cion_peer_info_get_device_platform_version_n(void);
extern int utc_cion_peer_info_get_device_type_p(void);
extern int utc_cion_peer_info_get_device_type_n(void);
extern int utc_cion_peer_info_get_app_id_p(void);
extern int utc_cion_peer_info_get_app_id_n(void);
extern int utc_cion_peer_info_get_app_version_p(void);
extern int utc_cion_peer_info_get_app_version_n(void);
extern int utc_cion_peer_info_get_uuid_p(void);
extern int utc_cion_peer_info_get_uuid_n(void);
extern int utc_cion_peer_info_get_display_name_p(void);
extern int utc_cion_peer_info_get_display_name_n(void);

extern int utc_cion_peer_info_destroy_p(void);
extern int utc_cion_peer_info_destroy_n(void);

extern void utc_cion_payload_startup(void);
extern void utc_cion_payload_cleanup(void);
extern int utc_cion_payload_create_p(void);
extern int utc_cion_payload_create_n(void);
extern int utc_cion_payload_destroy_p(void);
extern int utc_cion_payload_destroy_n(void);
extern int utc_cion_payload_get_type_p(void);
extern int utc_cion_payload_get_type_n(void);
extern int utc_cion_payload_get_data_p(void);
extern int utc_cion_payload_get_data_n(void);
extern int utc_cion_payload_set_data_p(void);
extern int utc_cion_payload_set_data_n(void);
extern int utc_cion_payload_save_as_file_p(void);
extern int utc_cion_payload_save_as_file_n(void);
extern int utc_cion_payload_get_received_file_name_p(void);
extern int utc_cion_payload_get_received_file_name_n(void);
extern int utc_cion_payload_get_received_bytes_p(void);
extern int utc_cion_payload_get_received_bytes_n(void);
extern int utc_cion_payload_get_total_bytes_p(void);
extern int utc_cion_payload_get_total_bytes_n(void);
extern int utc_cion_payload_set_file_path_p(void);
extern int utc_cion_payload_set_file_path_n(void);
extern int utc_cion_payload_get_payload_id_p(void);
extern int utc_cion_payload_get_payload_id_n(void);

extern void utc_cion_payload_async_result_startup(void);
extern void utc_cion_payload_async_result_cleanup(void);
extern int utc_cion_payload_async_result_clone_p(void);
extern int utc_cion_payload_async_result_clone_n(void);
extern int utc_cion_payload_async_result_destroy_p(void);
extern int utc_cion_payload_async_result_destroy_n(void);
extern int utc_cion_payload_async_result_get_peer_info_p(void);
extern int utc_cion_payload_async_result_get_peer_info_n(void);
extern int utc_cion_payload_async_result_get_payload_id_p(void);
extern int utc_cion_payload_async_result_get_payload_id_n(void);

extern void utc_cion_connection_result_startup(void);
extern void utc_cion_connection_result_cleanup(void);
extern int utc_cion_connection_result_get_status_p(void);
extern int utc_cion_connection_result_get_status_n(void);
extern int utc_cion_connection_result_get_reason_p(void);
extern int utc_cion_connection_result_get_reason_n(void);

extern void utc_cion_security_startup(void);
extern void utc_cion_security_cleanup(void);
extern int utc_cion_security_create_p(void);
extern int utc_cion_security_create_n(void);
extern int utc_cion_security_destory_p(void);
extern int utc_cion_security_destory_n(void);
extern int utc_cion_security_set_ca_path_p(void);
extern int utc_cion_security_set_ca_path_n(void);
extern int utc_cion_security_set_cert_path_p(void);
extern int utc_cion_security_set_cert_path_n(void);
extern int utc_cion_security_set_private_key_path_p(void);
extern int utc_cion_security_set_private_key_path_n(void);
extern int utc_cion_security_get_ca_path_p(void);
extern int utc_cion_security_get_ca_path_n(void);
extern int utc_cion_security_get_cert_path_p(void);
extern int utc_cion_security_get_cert_path_n(void);
extern int utc_cion_security_get_private_key_path_p(void);
extern int utc_cion_security_get_private_key_path_n(void);

testcase tc_array[] = {
    {"utc_cion_group_create_p", utc_cion_group_create_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_create_n", utc_cion_group_create_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_destroy_p", utc_cion_group_destroy_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_destroy_n", utc_cion_group_destroy_n, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_subscribe_p", utc_cion_group_subscribe_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_subscribe_n", utc_cion_group_subscribe_n, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_unsubscribe_p", utc_cion_group_unsubscribe_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_unsubscribe_n", utc_cion_group_unsubscribe_n, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_publish_p", utc_cion_group_publish_p, utc_cion_group_startup, utc_cion_group_cleanup},
    {"utc_cion_group_publish_n", utc_cion_group_publish_n, utc_cion_group_startup, utc_cion_group_cleanup},

    {"utc_cion_server_create_p", utc_cion_server_create_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_create_n", utc_cion_server_create_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_destroy_p", utc_cion_server_destroy_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_destroy_n", utc_cion_server_destroy_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_listen_p", utc_cion_server_listen_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_listen_n", utc_cion_server_listen_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_stop_p", utc_cion_server_stop_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_stop_n", utc_cion_server_stop_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_disconnect_p", utc_cion_server_disconnect_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_disconnect_n", utc_cion_server_disconnect_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_send_payload_async_p", utc_cion_server_send_payload_async_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_send_payload_async_n", utc_cion_server_send_payload_async_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_foreach_connected_peer_info_p", utc_cion_server_foreach_connected_peer_info_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_foreach_connected_peer_info_n", utc_cion_server_foreach_connected_peer_info_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_connection_result_cb_p", utc_cion_server_add_connection_result_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_connection_result_cb_n", utc_cion_server_add_connection_result_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_connection_result_cb_p", utc_cion_server_remove_connection_result_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_connection_result_cb_n", utc_cion_server_remove_connection_result_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_payload_received_cb_p", utc_cion_server_add_payload_received_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_payload_received_cb_n", utc_cion_server_add_payload_received_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_payload_received_cb_p", utc_cion_server_remove_payload_received_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_payload_received_cb_n", utc_cion_server_remove_payload_received_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_data_received_cb_p", utc_cion_server_set_data_received_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_data_received_cb_n", utc_cion_server_set_data_received_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_unset_data_received_cb_p", utc_cion_server_unset_data_received_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_unset_data_received_cb_n", utc_cion_server_unset_data_received_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_disconnected_cb_p", utc_cion_server_add_disconnected_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_add_disconnected_cb_n", utc_cion_server_add_disconnected_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_disconnected_cb_p", utc_cion_server_remove_disconnected_cb_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_remove_disconnected_cb_n", utc_cion_server_remove_disconnected_cb_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_accept_p", utc_cion_server_accept_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_accept_n", utc_cion_server_accept_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_reject_p", utc_cion_server_reject_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_reject_n", utc_cion_server_reject_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_display_name_p", utc_cion_server_set_display_name_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_display_name_n", utc_cion_server_set_display_name_n, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_on_demand_launch_enabled_p", utc_cion_server_set_on_demand_launch_enabled_p, utc_cion_server_startup, utc_cion_server_cleanup},
    {"utc_cion_server_set_on_demand_launch_enabled_n", utc_cion_server_set_on_demand_launch_enabled_n, utc_cion_server_startup, utc_cion_server_cleanup},

    {"utc_cion_client_create_p", utc_cion_client_create_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_create_n", utc_cion_client_create_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_destroy_p", utc_cion_client_destroy_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_destroy_n", utc_cion_client_destroy_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_try_discovery_p", utc_cion_client_try_discovery_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_try_discovery_n", utc_cion_client_try_discovery_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_stop_discovery_p", utc_cion_client_stop_discovery_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_stop_discovery_n", utc_cion_client_stop_discovery_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_connect_p", utc_cion_client_connect_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_connect_n", utc_cion_client_connect_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_disconnect_p", utc_cion_client_disconnect_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_disconnect_n", utc_cion_client_disconnect_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_send_data_p", utc_cion_client_send_data_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_send_data_n", utc_cion_client_send_data_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_send_payload_async_p", utc_cion_client_send_payload_async_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_send_payload_async_n", utc_cion_client_send_payload_async_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_connection_result_cb_p", utc_cion_client_add_connection_result_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_connection_result_cb_n", utc_cion_client_add_connection_result_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_connection_result_cb_p", utc_cion_client_remove_connection_result_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_connection_result_cb_n", utc_cion_client_remove_connection_result_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_payload_received_cb_p", utc_cion_client_add_payload_received_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_payload_received_cb_n", utc_cion_client_add_payload_received_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_payload_received_cb_p", utc_cion_client_remove_payload_received_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_payload_received_cb_n", utc_cion_client_remove_payload_received_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_disconnected_cb_p", utc_cion_client_add_disconnected_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_add_disconnected_cb_n", utc_cion_client_add_disconnected_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_disconnected_cb_p", utc_cion_client_remove_disconnected_cb_p, utc_cion_client_startup, utc_cion_client_cleanup},
    {"utc_cion_client_remove_disconnected_cb_n", utc_cion_client_remove_disconnected_cb_n, utc_cion_client_startup, utc_cion_client_cleanup},

    {"utc_cion_peer_info_clone_p", utc_cion_peer_info_clone_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_clone_n", utc_cion_peer_info_clone_n, utc_cion_peer_info_startup, NULL},

    {"utc_cion_peer_info_get_device_id_p", utc_cion_peer_info_get_device_id_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_id_n", utc_cion_peer_info_get_device_id_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_name_p", utc_cion_peer_info_get_device_name_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_name_n", utc_cion_peer_info_get_device_name_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_platform_p", utc_cion_peer_info_get_device_platform_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_platform_n", utc_cion_peer_info_get_device_platform_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_platform_version_p", utc_cion_peer_info_get_device_platform_version_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_platform_version_n", utc_cion_peer_info_get_device_platform_version_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_type_p", utc_cion_peer_info_get_device_type_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_device_type_n", utc_cion_peer_info_get_device_type_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_app_id_p", utc_cion_peer_info_get_app_id_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_app_id_n", utc_cion_peer_info_get_app_id_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_app_version_p", utc_cion_peer_info_get_app_version_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_app_version_n", utc_cion_peer_info_get_app_version_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_uuid_p", utc_cion_peer_info_get_uuid_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_uuid_n", utc_cion_peer_info_get_uuid_n, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_display_name_p", utc_cion_peer_info_get_display_name_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_get_display_name_n", utc_cion_peer_info_get_display_name_n, utc_cion_peer_info_startup, NULL},

    {"utc_cion_peer_info_destroy_p", utc_cion_peer_info_destroy_p, utc_cion_peer_info_startup, NULL},
    {"utc_cion_peer_info_destroy_n", utc_cion_peer_info_destroy_n, utc_cion_peer_info_startup, utc_cion_peer_info_cleanup},

    {"utc_cion_payload_create_p", utc_cion_payload_create_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_create_n", utc_cion_payload_create_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_destroy_p", utc_cion_payload_destroy_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_destroy_n", utc_cion_payload_destroy_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_type_p", utc_cion_payload_get_type_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_type_n", utc_cion_payload_get_type_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_data_p", utc_cion_payload_get_data_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_data_n", utc_cion_payload_get_data_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_set_data_p", utc_cion_payload_set_data_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_set_data_n", utc_cion_payload_set_data_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_save_as_file_p", utc_cion_payload_save_as_file_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_save_as_file_n", utc_cion_payload_save_as_file_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_received_file_name_p", utc_cion_payload_get_received_file_name_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_received_file_name_n", utc_cion_payload_get_received_file_name_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_received_bytes_p", utc_cion_payload_get_received_bytes_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_received_bytes_n", utc_cion_payload_get_received_bytes_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_total_bytes_p", utc_cion_payload_get_total_bytes_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_total_bytes_n", utc_cion_payload_get_total_bytes_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_set_file_path_p", utc_cion_payload_set_file_path_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_set_file_path_n", utc_cion_payload_set_file_path_n, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_payload_id_p", utc_cion_payload_get_payload_id_p, utc_cion_payload_startup, utc_cion_payload_cleanup},
    {"utc_cion_payload_get_payload_id_n", utc_cion_payload_get_payload_id_n, utc_cion_payload_startup, utc_cion_payload_cleanup},

    {"utc_cion_payload_async_result_clone_p", utc_cion_payload_async_result_clone_p, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_clone_n", utc_cion_payload_async_result_clone_n, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_destroy_p", utc_cion_payload_async_result_destroy_p, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_destroy_n", utc_cion_payload_async_result_destroy_n, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_get_peer_info_p", utc_cion_payload_async_result_get_peer_info_p, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_get_peer_info_n", utc_cion_payload_async_result_get_peer_info_n, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_get_payload_id_p", utc_cion_payload_async_result_get_payload_id_p, utc_cion_payload_async_result_startup, NULL},
    {"utc_cion_payload_async_result_get_payload_id_n", utc_cion_payload_async_result_get_payload_id_n, utc_cion_payload_async_result_startup, utc_cion_payload_async_result_cleanup},

    {"utc_cion_connection_result_get_status_p", utc_cion_connection_result_get_status_p, utc_cion_connection_result_startup, NULL},
    {"utc_cion_connection_result_get_status_n", utc_cion_connection_result_get_status_n, utc_cion_connection_result_startup, NULL},
    {"utc_cion_connection_result_get_reason_p", utc_cion_connection_result_get_reason_p, utc_cion_connection_result_startup, NULL},
    {"utc_cion_connection_result_get_reason_n", utc_cion_connection_result_get_reason_n, utc_cion_connection_result_startup, utc_cion_connection_result_cleanup},

    {"utc_cion_security_create_p", utc_cion_security_create_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_create_n", utc_cion_security_create_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_destory_p", utc_cion_security_destory_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_destory_n", utc_cion_security_destory_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_ca_path_p", utc_cion_security_set_ca_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_ca_path_n", utc_cion_security_set_ca_path_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_cert_path_p", utc_cion_security_set_cert_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_cert_path_n", utc_cion_security_set_cert_path_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_private_key_path_p", utc_cion_security_set_private_key_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_set_private_key_path_n", utc_cion_security_set_private_key_path_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_ca_path_p", utc_cion_security_get_ca_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_ca_path_n", utc_cion_security_get_ca_path_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_cert_path_p", utc_cion_security_get_cert_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_cert_path_n", utc_cion_security_get_cert_path_n, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_private_key_path_p", utc_cion_security_get_private_key_path_p, utc_cion_security_startup, utc_cion_security_cleanup},
    {"utc_cion_security_get_private_key_path_n", utc_cion_security_get_private_key_path_n, utc_cion_security_startup, utc_cion_security_cleanup},

    {NULL, NULL}
};

#endif // __TCT_CION_NATIVE_H__
