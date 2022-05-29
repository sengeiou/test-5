//
// Copyright (c) 2018 - 2021 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_RPC_PORT_NATIVE_H__
#define __TCT_RPC_PORT_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_rpc_port_proxy_startup(void);
extern void utc_rpc_port_proxy_cleanup(void);
extern int utc_rpc_port_proxy_create_p(void);
extern int utc_rpc_port_proxy_create_n(void);
extern int utc_rpc_port_proxy_destroy_p(void);
extern int utc_rpc_port_proxy_destroy_n(void);
extern int utc_rpc_port_proxy_connect_p(void);
extern int utc_rpc_port_proxy_connect_n(void);
extern int utc_rpc_port_proxy_add_connected_event_cb_p(void);
extern int utc_rpc_port_proxy_add_connected_event_cb_n1(void);
extern int utc_rpc_port_proxy_add_connected_event_cb_n2(void);
extern int utc_rpc_port_proxy_add_received_event_cb_p(void);
extern int utc_rpc_port_proxy_add_received_event_cb_n1(void);
extern int utc_rpc_port_proxy_add_received_event_cb_n2(void);
extern int utc_rpc_port_proxy_add_disconnected_event_cb_p(void);
extern int utc_rpc_port_proxy_add_disconnected_event_cb_n1(void);
extern int utc_rpc_port_proxy_add_disconnected_event_cb_n2(void);
extern int utc_rpc_port_proxy_add_rejected_event_cb_p1(void);
extern int utc_rpc_port_proxy_add_rejected_event_cb_p2(void);
extern int utc_rpc_port_proxy_add_rejected_event_cb_n1(void);
extern int utc_rpc_port_proxy_add_rejected_event_cb_n2(void);
extern int utc_rpc_port_proxy_get_port_p(void);
extern int utc_rpc_port_proxy_get_port_n1(void);
extern int utc_rpc_port_proxy_get_port_n2(void);

extern void utc_rpc_port_stub_startup(void);
extern void utc_rpc_port_stub_cleanup(void);
extern int utc_rpc_port_stub_create_p(void);
extern int utc_rpc_port_stub_create_n(void);
extern int utc_rpc_port_stub_destroy_p(void);
extern int utc_rpc_port_stub_destroy_n(void);
extern int utc_rpc_port_stub_listen_p(void);
extern int utc_rpc_port_stub_listen_n(void);
extern int utc_rpc_port_stub_add_privilege_p(void);
extern int utc_rpc_port_stub_add_privilege_n(void);
extern int utc_rpc_port_stub_set_trusted_p(void);
extern int utc_rpc_port_stub_set_trusted_n(void);
extern int utc_rpc_port_stub_add_connected_event_cb_p(void);
extern int utc_rpc_port_stub_add_connected_event_cb_n1(void);
extern int utc_rpc_port_stub_add_connected_event_cb_n2(void);
extern int utc_rpc_port_stub_add_received_event_cb_p(void);
extern int utc_rpc_port_stub_add_received_event_cb_n1(void);
extern int utc_rpc_port_stub_add_received_event_cb_n2(void);
extern int utc_rpc_port_stub_add_disconnected_event_cb_p(void);
extern int utc_rpc_port_stub_add_disconnected_event_cb_n1(void);
extern int utc_rpc_port_stub_add_disconnected_event_cb_n2(void);
extern int utc_rpc_port_stub_get_port_p(void);
extern int utc_rpc_port_stub_get_port_n1(void);
extern int utc_rpc_port_stub_get_port_n2(void);
extern int utc_rpc_port_stub_get_port_n3(void);

extern int utc_rpc_port_read_p(void);
extern int utc_rpc_port_read_n(void);
extern int utc_rpc_port_write_p(void);
extern int utc_rpc_port_write_n(void);

extern void utc_rpc_port_parcel_startup(void);
extern void utc_rpc_port_parcel_cleanup(void);
extern int utc_rpc_port_parcel_create_p(void);
extern int utc_rpc_port_parcel_create_from_port_p(void);
extern int utc_rpc_port_parcel_create_from_port_n1(void);
extern int utc_rpc_port_parcel_create_from_port_n2(void);
extern int utc_rpc_port_parcel_send_p(void);
extern int utc_rpc_port_parcel_send_n1(void);
extern int utc_rpc_port_parcel_send_n2(void);
extern int utc_rpc_port_parcel_create_from_port_n2(void);
extern int utc_rpc_port_parcel_destroy_p(void);
extern int utc_rpc_port_parcel_destroy_n(void);
extern int utc_rpc_port_parcel_write_byte_p(void);
extern int utc_rpc_port_parcel_write_byte_n(void);
extern int utc_rpc_port_parcel_write_int16_p(void);
extern int utc_rpc_port_parcel_write_int16_n(void);
extern int utc_rpc_port_parcel_write_int32_p(void);
extern int utc_rpc_port_parcel_write_int32_n(void);
extern int utc_rpc_port_parcel_write_int64_p(void);
extern int utc_rpc_port_parcel_write_int64_n(void);
extern int utc_rpc_port_parcel_write_float_p(void);
extern int utc_rpc_port_parcel_write_float_n(void);
extern int utc_rpc_port_parcel_write_double_p(void);
extern int utc_rpc_port_parcel_write_double_n(void);
extern int utc_rpc_port_parcel_write_string_p(void);
extern int utc_rpc_port_parcel_write_string_n(void);
extern int utc_rpc_port_parcel_write_bool_p(void);
extern int utc_rpc_port_parcel_write_bool_n(void);
extern int utc_rpc_port_parcel_write_bundle_p(void);
extern int utc_rpc_port_parcel_write_bundle_n(void);
extern int utc_rpc_port_parcel_write_array_count_p(void);
extern int utc_rpc_port_parcel_write_array_count_n(void);
extern int utc_rpc_port_parcel_write_p(void);
extern int utc_rpc_port_parcel_write_n1(void);
extern int utc_rpc_port_parcel_write_n2(void);
extern int utc_rpc_port_parcel_read_byte_p(void);
extern int utc_rpc_port_parcel_read_byte_n(void);
extern int utc_rpc_port_parcel_read_int16_p(void);
extern int utc_rpc_port_parcel_read_int16_n(void);
extern int utc_rpc_port_parcel_read_int32_p(void);
extern int utc_rpc_port_parcel_read_int32_n(void);
extern int utc_rpc_port_parcel_read_int64_p(void);
extern int utc_rpc_port_parcel_read_int64_n(void);
extern int utc_rpc_port_parcel_read_float_p(void);
extern int utc_rpc_port_parcel_read_float_n(void);
extern int utc_rpc_port_parcel_read_double_p(void);
extern int utc_rpc_port_parcel_read_double_n(void);
extern int utc_rpc_port_parcel_read_string_p(void);
extern int utc_rpc_port_parcel_read_string_n(void);
extern int utc_rpc_port_parcel_read_bool_p(void);
extern int utc_rpc_port_parcel_read_bool_n(void);
extern int utc_rpc_port_parcel_read_bundle_p(void);
extern int utc_rpc_port_parcel_read_bundle_n(void);
extern int utc_rpc_port_parcel_read_array_count_p(void);
extern int utc_rpc_port_parcel_read_array_count_n(void);
extern int utc_rpc_port_parcel_read_p(void);
extern int utc_rpc_port_parcel_read_n1(void);
extern int utc_rpc_port_parcel_read_n2(void);
extern int utc_rpc_port_parcel_get_header_p(void);
extern int utc_rpc_port_parcel_get_header_n(void);
extern int utc_rpc_port_parcel_header_set_get_tag_p(void);
extern int utc_rpc_port_parcel_header_set_get_tag_n(void);
extern int utc_rpc_port_parcel_header_set_get_seq_num_p(void);
extern int utc_rpc_port_parcel_header_set_get_seq_num_n(void);
extern int utc_rpc_port_parcel_header_get_timestamp_p(void);
extern int utc_rpc_port_parcel_header_get_timestamp_n(void);
extern int utc_rpc_port_parcel_burst_read_p(void);
extern int utc_rpc_port_parcel_burst_read_n(void);
extern int utc_rpc_port_parcel_burst_write_p(void);
extern int utc_rpc_port_parcel_burst_write_n(void);
extern int utc_rpc_port_parcel_get_raw_p(void);
extern int utc_rpc_port_parcel_get_raw_n(void);
extern int utc_rpc_port_parcel_create_from_raw_p(void);
extern int utc_rpc_port_parcel_create_from_raw_n(void);

extern int utc_rpc_port_proxy_connect_sync_p(void);
extern int utc_rpc_port_proxy_connect_sync_n(void);
extern int utc_rpc_port_set_private_sharing_array_p(void);
extern int utc_rpc_port_set_private_sharing_array_n(void);
extern int utc_rpc_port_set_private_sharing_p(void);
extern int utc_rpc_port_set_private_sharing_n(void);
extern int utc_rpc_port_unset_private_sharing_p(void);
extern int utc_rpc_port_unset_private_sharing_n(void);
extern int utc_rpc_port_disconnect_p(void);
extern int utc_rpc_port_disconnect_n(void);

testcase tc_array[] = {
	{"utc_rpc_port_proxy_create_p", utc_rpc_port_proxy_create_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_create_n", utc_rpc_port_proxy_create_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_destroy_p", utc_rpc_port_proxy_destroy_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_destroy_n", utc_rpc_port_proxy_destroy_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_connect_p", utc_rpc_port_proxy_connect_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_connect_n", utc_rpc_port_proxy_connect_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_connected_event_cb_p", utc_rpc_port_proxy_add_connected_event_cb_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_connected_event_cb_n1", utc_rpc_port_proxy_add_connected_event_cb_n1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_connected_event_cb_n2", utc_rpc_port_proxy_add_connected_event_cb_n2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_received_event_cb_p", utc_rpc_port_proxy_add_received_event_cb_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_received_event_cb_n1", utc_rpc_port_proxy_add_received_event_cb_n1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_received_event_cb_n2", utc_rpc_port_proxy_add_received_event_cb_n2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_disconnected_event_cb_p", utc_rpc_port_proxy_add_disconnected_event_cb_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_disconnected_event_cb_n1", utc_rpc_port_proxy_add_disconnected_event_cb_n1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_disconnected_event_cb_n2", utc_rpc_port_proxy_add_disconnected_event_cb_n2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_rejected_event_cb_p1", utc_rpc_port_proxy_add_rejected_event_cb_p1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_rejected_event_cb_p2", utc_rpc_port_proxy_add_rejected_event_cb_p2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_rejected_event_cb_n1", utc_rpc_port_proxy_add_rejected_event_cb_n1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_add_rejected_event_cb_n2", utc_rpc_port_proxy_add_rejected_event_cb_n2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_get_port_p", utc_rpc_port_proxy_get_port_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_get_port_n1", utc_rpc_port_proxy_get_port_n1, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_proxy_get_port_n2", utc_rpc_port_proxy_get_port_n2, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_stub_create_p", utc_rpc_port_stub_create_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_create_n", utc_rpc_port_stub_create_n, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_destroy_p", utc_rpc_port_stub_destroy_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_destroy_n", utc_rpc_port_stub_destroy_n, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_listen_p", utc_rpc_port_stub_listen_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_listen_n", utc_rpc_port_stub_listen_n, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_privilege_p", utc_rpc_port_stub_add_privilege_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_privilege_n", utc_rpc_port_stub_add_privilege_n, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_set_trusted_p", utc_rpc_port_stub_set_trusted_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_set_trusted_n", utc_rpc_port_stub_set_trusted_n, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_connected_event_cb_p", utc_rpc_port_stub_add_connected_event_cb_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_connected_event_cb_n1", utc_rpc_port_stub_add_connected_event_cb_n1, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_connected_event_cb_n2", utc_rpc_port_stub_add_connected_event_cb_n2, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_received_event_cb_p", utc_rpc_port_stub_add_received_event_cb_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_received_event_cb_n1", utc_rpc_port_stub_add_received_event_cb_n1, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_received_event_cb_n2", utc_rpc_port_stub_add_received_event_cb_n2, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_disconnected_event_cb_p", utc_rpc_port_stub_add_disconnected_event_cb_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_disconnected_event_cb_n1", utc_rpc_port_stub_add_disconnected_event_cb_n1, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_add_disconnected_event_cb_n2", utc_rpc_port_stub_add_disconnected_event_cb_n2, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_get_port_p", utc_rpc_port_stub_get_port_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_get_port_n1", utc_rpc_port_stub_get_port_n1, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_get_port_n2", utc_rpc_port_stub_get_port_n2, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_stub_get_port_n3", utc_rpc_port_stub_get_port_n3, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_read_p", utc_rpc_port_read_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_read_n", utc_rpc_port_read_n, NULL, NULL},
	{"utc_rpc_port_write_p", utc_rpc_port_write_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_write_n", utc_rpc_port_write_n, NULL, NULL},
	{"utc_rpc_port_parcel_create_p", utc_rpc_port_parcel_create_p , NULL, NULL},
	{"utc_rpc_port_parcel_create_from_port_p", utc_rpc_port_parcel_create_from_port_p, utc_rpc_port_parcel_startup, utc_rpc_port_parcel_cleanup},
	{"utc_rpc_port_parcel_create_from_port_n1", utc_rpc_port_parcel_create_from_port_n1, NULL, NULL},
	{"utc_rpc_port_parcel_create_from_port_n2", utc_rpc_port_parcel_create_from_port_n2, NULL, NULL},
	{"utc_rpc_port_parcel_send_p", utc_rpc_port_parcel_send_p, utc_rpc_port_parcel_startup, utc_rpc_port_parcel_cleanup},
	{"utc_rpc_port_parcel_send_n1", utc_rpc_port_parcel_send_n1, NULL, NULL},
	{"utc_rpc_port_parcel_send_n2", utc_rpc_port_parcel_send_n2, NULL, NULL},
	{"utc_rpc_port_parcel_destroy_p", utc_rpc_port_parcel_destroy_p, NULL, NULL},
	{"utc_rpc_port_parcel_destroy_n", utc_rpc_port_parcel_destroy_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_byte_p", utc_rpc_port_parcel_write_byte_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_byte_n", utc_rpc_port_parcel_write_byte_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_int16_p", utc_rpc_port_parcel_write_int16_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_int16_n", utc_rpc_port_parcel_write_int16_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_int32_p", utc_rpc_port_parcel_write_int32_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_int32_n", utc_rpc_port_parcel_write_int32_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_int64_p", utc_rpc_port_parcel_write_int64_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_int64_n", utc_rpc_port_parcel_write_int64_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_float_p", utc_rpc_port_parcel_write_float_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_float_n", utc_rpc_port_parcel_write_float_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_double_p", utc_rpc_port_parcel_write_double_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_double_n", utc_rpc_port_parcel_write_double_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_string_p", utc_rpc_port_parcel_write_string_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_string_n", utc_rpc_port_parcel_write_string_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_bool_p", utc_rpc_port_parcel_write_bool_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_bool_n", utc_rpc_port_parcel_write_bool_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_bundle_p", utc_rpc_port_parcel_write_bundle_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_bundle_n", utc_rpc_port_parcel_write_bundle_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_array_count_p", utc_rpc_port_parcel_write_array_count_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_array_count_n", utc_rpc_port_parcel_write_array_count_n, NULL, NULL},
	{"utc_rpc_port_parcel_write_p", utc_rpc_port_parcel_write_p, NULL, NULL},
	{"utc_rpc_port_parcel_write_n1", utc_rpc_port_parcel_write_n1, NULL, NULL},
	{"utc_rpc_port_parcel_write_n2", utc_rpc_port_parcel_write_n2, NULL, NULL},
	{"utc_rpc_port_parcel_read_byte_p", utc_rpc_port_parcel_read_byte_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_byte_n", utc_rpc_port_parcel_read_byte_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_int16_p", utc_rpc_port_parcel_read_int16_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_int16_n", utc_rpc_port_parcel_read_int16_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_int32_p", utc_rpc_port_parcel_read_int32_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_int32_n", utc_rpc_port_parcel_read_int32_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_int64_p", utc_rpc_port_parcel_read_int64_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_int64_n", utc_rpc_port_parcel_read_int64_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_float_p", utc_rpc_port_parcel_read_float_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_float_n", utc_rpc_port_parcel_read_float_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_double_p", utc_rpc_port_parcel_read_double_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_double_n", utc_rpc_port_parcel_read_double_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_string_p", utc_rpc_port_parcel_read_string_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_string_n", utc_rpc_port_parcel_read_string_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_bool_p", utc_rpc_port_parcel_read_bool_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_bool_n", utc_rpc_port_parcel_read_bool_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_bundle_p", utc_rpc_port_parcel_read_bundle_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_bundle_n", utc_rpc_port_parcel_read_bundle_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_array_count_p", utc_rpc_port_parcel_read_array_count_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_array_count_n", utc_rpc_port_parcel_read_array_count_n, NULL, NULL},
	{"utc_rpc_port_parcel_read_p", utc_rpc_port_parcel_read_p, NULL, NULL},
	{"utc_rpc_port_parcel_read_n1", utc_rpc_port_parcel_read_n1, NULL, NULL},
	{"utc_rpc_port_parcel_read_n2", utc_rpc_port_parcel_read_n2, NULL, NULL},
	{"utc_rpc_port_parcel_burst_read_p", utc_rpc_port_parcel_burst_read_p, NULL, NULL},
	{"utc_rpc_port_parcel_burst_read_n", utc_rpc_port_parcel_burst_read_n, NULL, NULL},
	{"utc_rpc_port_parcel_burst_write_p", utc_rpc_port_parcel_burst_write_p, NULL, NULL},
	{"utc_rpc_port_parcel_burst_write_n", utc_rpc_port_parcel_burst_write_n, NULL, NULL},
	{"utc_rpc_port_proxy_connect_sync_p", utc_rpc_port_proxy_connect_sync_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_parcel_get_header_p", utc_rpc_port_parcel_get_header_p, NULL, NULL},
	{"utc_rpc_port_parcel_get_header_n", utc_rpc_port_parcel_get_header_n, NULL, NULL},
	{"utc_rpc_port_parcel_header_set_get_tag_p", utc_rpc_port_parcel_header_set_get_tag_p, utc_rpc_port_parcel_startup, utc_rpc_port_parcel_cleanup},
	{"utc_rpc_port_parcel_header_set_get_tag_n", utc_rpc_port_parcel_header_set_get_tag_n, NULL, NULL},
	{"utc_rpc_port_parcel_header_set_get_seq_num_p", utc_rpc_port_parcel_header_set_get_seq_num_p, utc_rpc_port_parcel_startup, utc_rpc_port_parcel_cleanup},
	{"utc_rpc_port_parcel_header_set_get_seq_num_n", utc_rpc_port_parcel_header_set_get_seq_num_n, NULL, NULL},
	{"utc_rpc_port_parcel_header_get_timestamp_p", utc_rpc_port_parcel_header_get_timestamp_p, NULL, NULL},
	{"utc_rpc_port_parcel_header_get_timestamp_n", utc_rpc_port_parcel_header_get_timestamp_n, NULL, NULL},
	{"utc_rpc_port_parcel_get_raw_p", utc_rpc_port_parcel_get_raw_p, NULL, NULL},
	{"utc_rpc_port_parcel_get_raw_n", utc_rpc_port_parcel_get_raw_n, NULL, NULL},
	{"utc_rpc_port_parcel_create_from_raw_p", utc_rpc_port_parcel_create_from_raw_p, NULL, NULL},
	{"utc_rpc_port_parcel_create_from_raw_n", utc_rpc_port_parcel_create_from_raw_n, NULL, NULL},
	{"utc_rpc_port_proxy_connect_sync_n", utc_rpc_port_proxy_connect_sync_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_set_private_sharing_array_p", utc_rpc_port_set_private_sharing_array_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_set_private_sharing_array_n", utc_rpc_port_set_private_sharing_array_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_set_private_sharing_p", utc_rpc_port_set_private_sharing_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_set_private_sharing_n", utc_rpc_port_set_private_sharing_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_unset_private_sharing_p", utc_rpc_port_unset_private_sharing_p, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_unset_private_sharing_n", utc_rpc_port_unset_private_sharing_n, utc_rpc_port_proxy_startup, utc_rpc_port_proxy_cleanup},
	{"utc_rpc_port_disconnect_p", utc_rpc_port_disconnect_p, utc_rpc_port_stub_startup, utc_rpc_port_stub_cleanup},
	{"utc_rpc_port_disconnect_n", utc_rpc_port_disconnect_n, NULL, NULL},
	{NULL, NULL}
};

#endif // __TCT_RPC_PORT_NATIVE_H__
