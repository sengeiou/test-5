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
#ifndef __TCT_RPC-PORT-NATIVE_H__
#define __TCT_RPC-PORT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_rpc_port_proxy_startup(void);
extern void ITs_rpc_port_proxy_cleanup(void);
extern void ITs_rpc_port_stub_startup(void);
extern void ITs_rpc_port_stub_cleanup(void);
extern void ITs_rpc_port_parcel_startup(void);
extern void ITs_rpc_port_parcel_cleanup(void);

extern int ITc_rpc_port_proxy_create_destroy_p(void);
extern int ITc_rpc_port_proxy_connect_p(void);
extern int ITc_rpc_port_proxy_add_connected_disconnected_event_cb_p(void);
extern int ITc_rpc_port_proxy_add_rejected_event_cb_p(void);
extern int ITc_rpc_port_proxy_add_received_event_cb_p(void);
extern int ITc_rpc_port_stub_create_destroy_p(void);
extern int ITc_rpc_port_stub_listen_p(void);
extern int ITc_rpc_port_stub_add_privilege_p(void);
extern int ITc_rpc_port_stub_set_trusted_p(void);
extern int ITc_rpc_port_stub_add_connected_received_event_cb_p(void);
extern int ITc_rpc_port_proxy_get_port_p(void);
extern int ITc_rpc_port_parcel_create_destroy_p(void);
extern int ITc_rpc_port_parcel_create_from_port_p(void);
extern int ITc_rpc_port_parcel_send_p(void);
extern int ITc_rpc_port_parcel_write_read_byte_p(void);
extern int ITc_rpc_port_parcel_write_read_int16_p(void);
extern int ITc_rpc_port_parcel_write_read_int32_p(void);
extern int ITc_rpc_port_parcel_write_read_int64_p(void);
extern int ITc_rpc_port_parcel_write_read_float_p(void);
extern int ITc_rpc_port_parcel_write_read_double_p(void);
extern int ITc_rpc_port_parcel_write_read_string_p(void);
extern int ITc_rpc_port_parcel_write_read_bool_p(void);
extern int ITc_rpc_port_parcel_write_read_bundle_p(void);
extern int ITc_rpc_port_parcel_write_read_array_count_p(void);
extern int ITc_rpc_port_parcel_write_read_p(void);
extern int ITc_rpc_port_parcel_burst_write_read_p(void);
extern int ITc_rpc_port_stub_get_port_p(void);
extern int ITc_rpc_port_stub_add_disconnected_event_cb_p(void);
extern int ITc_rpc_port_write_p(void);
extern int ITc_rpc_port_read_p(void);
extern int ITc_rpc_port_proxy_connect_sync_p(void);
extern int ITc_rpc_port_set_private_sharing_array_p(void);
extern int ITc_rpc_port_set_private_sharing_p(void);
extern int ITc_rpc_port_unset_private_sharing_p(void);
extern int ITc_rpc_port_parcel_get_header_p(void);
extern int ITc_rpc_port_parcel_header_set_get_seq_num_p(void);
extern int ITc_rpc_port_parcel_header_set_get_tag_p(void);
extern int ITc_rpc_port_parcel_header_get_timestamp_p(void);
extern int ITc_rpc_port_disconnect_p(void);
extern int ITc_rpc_port_parcel_get_raw_p(void);
extern int ITc_rpc_port_parcel_create_from_raw_p(void);

testcase tc_array[] = {
	{"ITc_rpc_port_proxy_get_port_p",ITc_rpc_port_proxy_get_port_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_proxy_create_destroy_p",ITc_rpc_port_proxy_create_destroy_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_proxy_connect_p",ITc_rpc_port_proxy_connect_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_proxy_add_connected_disconnected_event_cb_p",ITc_rpc_port_proxy_add_connected_disconnected_event_cb_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_proxy_add_rejected_event_cb_p",ITc_rpc_port_proxy_add_rejected_event_cb_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_proxy_add_received_event_cb_p",ITc_rpc_port_proxy_add_received_event_cb_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_stub_create_destroy_p",ITc_rpc_port_stub_create_destroy_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_stub_listen_p",ITc_rpc_port_stub_listen_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_stub_add_privilege_p",ITc_rpc_port_stub_add_privilege_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_stub_set_trusted_p",ITc_rpc_port_stub_set_trusted_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_stub_add_connected_received_event_cb_p",ITc_rpc_port_stub_add_connected_received_event_cb_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_parcel_create_destroy_p",ITc_rpc_port_parcel_create_destroy_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_create_from_port_p",ITc_rpc_port_parcel_create_from_port_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_send_p",ITc_rpc_port_parcel_send_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_byte_p",ITc_rpc_port_parcel_write_read_byte_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_int16_p",ITc_rpc_port_parcel_write_read_int16_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_int32_p",ITc_rpc_port_parcel_write_read_int32_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_int64_p",ITc_rpc_port_parcel_write_read_int64_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_float_p",ITc_rpc_port_parcel_write_read_float_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_double_p",ITc_rpc_port_parcel_write_read_double_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_string_p",ITc_rpc_port_parcel_write_read_string_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_bool_p",ITc_rpc_port_parcel_write_read_bool_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_bundle_p",ITc_rpc_port_parcel_write_read_bundle_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_array_count_p",ITc_rpc_port_parcel_write_read_array_count_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_write_read_p",ITc_rpc_port_parcel_write_read_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_burst_write_read_p",ITc_rpc_port_parcel_burst_write_read_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_stub_get_port_p",ITc_rpc_port_stub_get_port_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_write_p",ITc_rpc_port_write_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_read_p",ITc_rpc_port_read_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_stub_add_disconnected_event_cb_p",ITc_rpc_port_stub_add_disconnected_event_cb_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_proxy_connect_sync_p",ITc_rpc_port_proxy_connect_sync_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_set_private_sharing_array_p",ITc_rpc_port_set_private_sharing_array_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_set_private_sharing_p",ITc_rpc_port_set_private_sharing_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_unset_private_sharing_p",ITc_rpc_port_unset_private_sharing_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_parcel_get_header_p",ITc_rpc_port_parcel_get_header_p,ITs_rpc_port_proxy_startup,ITs_rpc_port_proxy_cleanup},
	{"ITc_rpc_port_parcel_header_set_get_seq_num_p",ITc_rpc_port_parcel_header_set_get_seq_num_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_header_set_get_tag_p",ITc_rpc_port_parcel_header_set_get_tag_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_header_get_timestamp_p",ITc_rpc_port_parcel_header_get_timestamp_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_disconnect_p",ITc_rpc_port_disconnect_p,ITs_rpc_port_stub_startup,ITs_rpc_port_stub_cleanup},
	{"ITc_rpc_port_parcel_get_raw_p",ITc_rpc_port_parcel_get_raw_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{"ITc_rpc_port_parcel_create_from_raw_p",ITc_rpc_port_parcel_create_from_raw_p,ITs_rpc_port_parcel_startup,ITs_rpc_port_parcel_cleanup},
	{NULL, NULL}
};

#endif //TCT_RPC-PORT-NATIVE_H__
