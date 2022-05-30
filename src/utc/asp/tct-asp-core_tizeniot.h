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
#ifndef __TCT_ASP-NATIVE_H__
#define __TCT_ASP-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_asp_startup(void);
extern void utc_asp_cleanup(void);
extern void utc_asp_advert_startup(void);
extern void utc_asp_advert_cleanup(void);
extern void utc_asp_seek_startup(void);
extern void utc_asp_seek_cleanup(void);
extern void utc_asp_session_startup(void);
extern void utc_asp_session_cleanup(void);

extern int utc_asp_initialize_p(void);
extern int utc_asp_initialize_n(void);
extern int utc_asp_deinitialize_p(void);
extern int utc_asp_deinitialize_n(void);
extern int utc_asp_seek_set_search_result_cb_p(void);
extern int utc_asp_seek_set_search_result_cb_n1(void);
extern int utc_asp_seek_set_search_result_cb_n2(void);
extern int utc_asp_seek_unset_search_result_cb_p(void);
extern int utc_asp_seek_unset_search_result_cb_n(void);
extern int utc_asp_advert_set_status_changed_cb_p(void);
extern int utc_asp_advert_set_status_changed_cb_n1(void);
extern int utc_asp_advert_set_status_changed_cb_n2(void);
extern int utc_asp_advert_unset_status_changed_cb_p(void);
extern int utc_asp_advert_unset_status_changed_cb_n(void);
extern int utc_asp_session_set_request_cb_p(void);
extern int utc_asp_session_set_request_cb_n1(void);
extern int utc_asp_session_set_request_cb_n2(void);
extern int utc_asp_session_unset_request_cb_p(void);
extern int utc_asp_session_unset_request_cb_n(void);
extern int utc_asp_session_set_config_request_cb_p(void);
extern int utc_asp_session_set_config_request_cb_n1(void);
extern int utc_asp_session_set_config_request_cb_n2(void);
extern int utc_asp_session_unset_config_request_cb_p(void);
extern int utc_asp_session_unset_config_request_cb_n(void);
extern int utc_asp_session_set_connect_status_cb_p(void);
extern int utc_asp_session_set_connect_status_cb_n1(void);
extern int utc_asp_session_set_connect_status_cb_n2(void);
extern int utc_asp_session_unset_connect_status_cb_p(void);
extern int utc_asp_session_unset_connect_status_cb_n(void);
extern int utc_asp_session_set_status_cb_p(void);
extern int utc_asp_session_set_status_cb_n1(void);
extern int utc_asp_session_set_status_cb_n2(void);
extern int utc_asp_session_unset_status_cb_p(void);
extern int utc_asp_session_unset_status_cb_n(void);
extern int utc_asp_session_set_port_status_cb_p(void);
extern int utc_asp_session_set_port_status_cb_n1(void);
extern int utc_asp_session_set_port_status_cb_n2(void);
extern int utc_asp_session_unset_port_status_cb_p(void);
extern int utc_asp_session_unset_port_status_cb_n(void);
extern int utc_asp_advert_create_p(void);
extern int utc_asp_advert_create_n1(void);
extern int utc_asp_advert_create_n2(void);
extern int utc_asp_advert_destroy_p(void);
extern int utc_asp_advert_destroy_n1(void);
extern int utc_asp_advert_destroy_n2(void);
extern int utc_asp_advert_destroy_n3(void);
extern int utc_asp_seek_create_p(void);
extern int utc_asp_seek_create_n1(void);
extern int utc_asp_seek_create_n2(void);
extern int utc_asp_seek_create_n3(void);
extern int utc_asp_seek_destroy_p(void);
extern int utc_asp_seek_destroy_n1(void);
extern int utc_asp_seek_destroy_n2(void);
extern int utc_asp_seek_destroy_n3(void);
extern int utc_asp_session_create_p(void);
extern int utc_asp_session_create_n1(void);
extern int utc_asp_session_create_n2(void);
extern int utc_asp_session_create_n3(void);
extern int utc_asp_session_create_n4(void);
extern int utc_asp_session_destroy_p(void);
extern int utc_asp_session_destroy_n1(void);
extern int utc_asp_session_destroy_n2(void);
extern int utc_asp_session_destroy_n3(void);
extern int utc_asp_advert_set_service_type_n(void);
extern int utc_asp_advert_set_auto_accept_n(void);
extern int utc_asp_advert_add_info_n(void);
extern int utc_asp_advert_get_info_n(void);
extern int utc_asp_advert_remove_info_n(void);
extern int utc_asp_advert_set_status_n(void);
extern int utc_asp_advert_set_discovery_tech_n(void);
extern int utc_asp_advert_set_preferred_connection_n(void);
extern int utc_asp_advert_set_p2p_role_scheme_n(void);
extern int utc_asp_advert_get_p2p_role_scheme_n(void);
extern int utc_asp_advert_set_p2p_config_method_n(void);
extern int utc_asp_advert_get_p2p_config_method_n(void);
extern int utc_asp_advert_set_p2p_response_n(void);
extern int utc_asp_advert_start_advertising_n(void);
extern int utc_asp_advert_stop_advertising_n(void);
extern int utc_asp_advert_change_service_status_n(void);
extern int utc_asp_seek_add_info_n(void);
extern int utc_asp_seek_remove_info_n(void);
extern int utc_asp_seek_set_discovery_tech_n(void);
extern int utc_asp_seek_set_preferred_connection_n(void);
extern int utc_asp_seek_start_n(void);
extern int utc_asp_seek_stop_n(void);
extern int utc_asp_session_get_mac_n(void);
extern int utc_asp_session_get_id_n(void);
extern int utc_asp_session_set_info_n(void);
extern int utc_asp_session_get_info_n(void);
extern int utc_asp_session_set_p2p_role_scheme_n(void);
extern int utc_asp_session_get_p2p_role_scheme_n(void);
extern int utc_asp_session_set_p2p_config_method_n(void);
extern int utc_asp_session_get_p2p_config_method_n(void);
extern int utc_asp_session_get_close_status_n(void);
extern int utc_asp_session_connect_n(void);
extern int utc_asp_session_confirm_n(void);
extern int utc_asp_session_get_handle_n(void);
extern int utc_asp_session_set_state_ready_n(void);
extern int utc_asp_session_close_n(void);
extern int utc_asp_session_bind_port_n(void);
extern int utc_asp_session_release_port_n(void);
extern int utc_asp_advert_set_service_type_p(void);
extern int utc_asp_advert_set_service_type_n1(void);
extern int utc_asp_advert_set_service_type_n2(void);
extern int utc_asp_advert_set_service_type_n3(void);
extern int utc_asp_advert_set_auto_accept_p(void);
extern int utc_asp_advert_set_auto_accept_n1(void);
extern int utc_asp_advert_set_auto_accept_n2(void);
extern int utc_asp_advert_add_info_p(void);
extern int utc_asp_advert_add_info_n1(void);
extern int utc_asp_advert_add_info_n2(void);
extern int utc_asp_advert_get_info_p(void);
extern int utc_asp_advert_get_info_n1(void);
extern int utc_asp_advert_get_info_n2(void);
extern int utc_asp_advert_remove_info_p(void);
extern int utc_asp_advert_remove_info_n1(void);
extern int utc_asp_advert_remove_info_n2(void);
extern int utc_asp_advert_set_status_p(void);
extern int utc_asp_advert_set_status_n1(void);
extern int utc_asp_advert_set_status_n2(void);
extern int utc_asp_advert_set_discovery_tech_p1(void);
extern int utc_asp_advert_set_discovery_tech_p2(void);
extern int utc_asp_advert_set_discovery_tech_p3(void);
extern int utc_asp_advert_set_discovery_tech_p4(void);
extern int utc_asp_advert_set_discovery_tech_p5(void);
extern int utc_asp_advert_set_discovery_tech_n1(void);
extern int utc_asp_advert_set_discovery_tech_n2(void);
extern int utc_asp_advert_set_discovery_tech_n3(void);
extern int utc_asp_advert_set_preferred_connection_p(void);
extern int utc_asp_advert_set_preferred_connection_n1(void);
extern int utc_asp_advert_set_preferred_connection_n2(void);
extern int utc_asp_advert_set_p2p_role_scheme_p(void);
extern int utc_asp_advert_set_p2p_role_scheme_n1(void);
extern int utc_asp_advert_set_p2p_role_scheme_n2(void);
extern int utc_asp_advert_get_p2p_role_scheme_p(void);
extern int utc_asp_advert_get_p2p_role_scheme_n1(void);
extern int utc_asp_advert_get_p2p_role_scheme_n2(void);
extern int utc_asp_advert_set_p2p_config_method_p1(void);
extern int utc_asp_advert_set_p2p_config_method_p2(void);
extern int utc_asp_advert_set_p2p_config_method_p3(void);
extern int utc_asp_advert_set_p2p_config_method_p4(void);
extern int utc_asp_advert_set_p2p_config_method_p5(void);
extern int utc_asp_advert_set_p2p_config_method_n1(void);
extern int utc_asp_advert_set_p2p_config_method_n2(void);
extern int utc_asp_advert_set_p2p_config_method_n3(void);
extern int utc_asp_advert_get_p2p_config_method_p(void);
extern int utc_asp_advert_get_p2p_config_method_n1(void);
extern int utc_asp_advert_get_p2p_config_method_n2(void);
extern int utc_asp_advert_get_p2p_config_method_n3(void);
extern int utc_asp_advert_set_p2p_response_p(void);
extern int utc_asp_advert_set_p2p_response_n1(void);
extern int utc_asp_advert_set_p2p_response_n2(void);
extern int utc_asp_advert_set_p2p_response_n3(void);
extern int utc_asp_advert_set_p2p_response_n4(void);
extern int utc_asp_advert_start_advertising_n1(void);
extern int utc_asp_advert_start_advertising_n2(void);
extern int utc_asp_advert_stop_advertising_n1(void);
extern int utc_asp_advert_stop_advertising_n2(void);
extern int utc_asp_advert_change_service_status_n1(void);
extern int utc_asp_advert_change_service_status_n2(void);
extern int utc_asp_seek_add_info_p(void);
extern int utc_asp_seek_add_info_n1(void);
extern int utc_asp_seek_add_info_n2(void);
extern int utc_asp_seek_remove_info_p(void);
extern int utc_asp_seek_remove_info_n1(void);
extern int utc_asp_seek_remove_info_n2(void);
extern int utc_asp_seek_set_discovery_tech_p1(void);
extern int utc_asp_seek_set_discovery_tech_p2(void);
extern int utc_asp_seek_set_discovery_tech_p3(void);
extern int utc_asp_seek_set_discovery_tech_p4(void);
extern int utc_asp_seek_set_discovery_tech_p5(void);
extern int utc_asp_seek_set_discovery_tech_n1(void);
extern int utc_asp_seek_set_discovery_tech_n2(void);
extern int utc_asp_seek_set_discovery_tech_n3(void);
extern int utc_asp_seek_set_preferred_connection_p(void);
extern int utc_asp_seek_set_preferred_connection_n1(void);
extern int utc_asp_seek_set_preferred_connection_n2(void);
extern int utc_asp_seek_start_n1(void);
extern int utc_asp_seek_start_n2(void);
extern int utc_asp_seek_stop_n1(void);
extern int utc_asp_seek_stop_n2(void);
extern int utc_asp_session_get_mac_p(void);
extern int utc_asp_session_get_mac_n1(void);
extern int utc_asp_session_get_mac_n2(void);
extern int utc_asp_session_get_mac_n3(void);
extern int utc_asp_session_get_id_p(void);
extern int utc_asp_session_get_id_n1(void);
extern int utc_asp_session_get_id_n2(void);
extern int utc_asp_session_get_id_n3(void);
extern int utc_asp_session_set_info_p(void);
extern int utc_asp_session_set_info_n1(void);
extern int utc_asp_session_set_info_n2(void);
extern int utc_asp_session_set_info_n3(void);
extern int utc_asp_session_get_info_p(void);
extern int utc_asp_session_get_info_n1(void);
extern int utc_asp_session_get_info_n2(void);
extern int utc_asp_session_get_info_n3(void);
extern int utc_asp_session_set_p2p_role_scheme_p(void);
extern int utc_asp_session_set_p2p_role_scheme_n1(void);
extern int utc_asp_session_set_p2p_role_scheme_n2(void);
extern int utc_asp_session_set_p2p_role_scheme_n3(void);
extern int utc_asp_session_get_p2p_role_scheme_p(void);
extern int utc_asp_session_get_p2p_role_scheme_n1(void);
extern int utc_asp_session_get_p2p_role_scheme_n2(void);
extern int utc_asp_session_get_p2p_role_scheme_n3(void);
extern int utc_asp_session_set_p2p_config_method_p1(void);
extern int utc_asp_session_set_p2p_config_method_p2(void);
extern int utc_asp_session_set_p2p_config_method_p3(void);
extern int utc_asp_session_set_p2p_config_method_p4(void);
extern int utc_asp_session_set_p2p_config_method_n1(void);
extern int utc_asp_session_set_p2p_config_method_n2(void);
extern int utc_asp_session_set_p2p_config_method_n3(void);
extern int utc_asp_session_get_p2p_config_method_p(void);
extern int utc_asp_session_get_p2p_config_method_n1(void);
extern int utc_asp_session_get_p2p_config_method_n2(void);
extern int utc_asp_session_get_p2p_config_method_n3(void);
extern int utc_asp_session_get_close_status_p(void);
extern int utc_asp_session_get_close_status_n1(void);
extern int utc_asp_session_get_close_status_n2(void);
extern int utc_asp_session_get_close_status_n3(void);
extern int utc_asp_session_connect_n1(void);
extern int utc_asp_session_connect_n2(void);
extern int utc_asp_session_confirm_n1(void);
extern int utc_asp_session_confirm_n2(void);
extern int utc_asp_session_get_handle_n1(void);
extern int utc_asp_session_get_handle_n2(void);
extern int utc_asp_session_set_state_ready_n1(void);
extern int utc_asp_session_set_state_ready_n2(void);
extern int utc_asp_session_close_n1(void);
extern int utc_asp_session_close_n2(void);
extern int utc_asp_session_bind_port_n1(void);
extern int utc_asp_session_bind_port_n2(void);
extern int utc_asp_session_bind_port_n3(void);
extern int utc_asp_session_release_port_n1(void);
extern int utc_asp_session_release_port_n2(void);
extern int utc_asp_session_release_port_n3(void);

testcase tc_array[] = {
	{"utc_asp_initialize_p",utc_asp_initialize_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_initialize_n",utc_asp_initialize_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_deinitialize_p",utc_asp_deinitialize_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_deinitialize_n",utc_asp_deinitialize_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_set_search_result_cb_p",utc_asp_seek_set_search_result_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_set_search_result_cb_n1",utc_asp_seek_set_search_result_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_set_search_result_cb_n2",utc_asp_seek_set_search_result_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_unset_search_result_cb_p",utc_asp_seek_unset_search_result_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_unset_search_result_cb_n",utc_asp_seek_unset_search_result_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_status_changed_cb_p",utc_asp_advert_set_status_changed_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_status_changed_cb_n1",utc_asp_advert_set_status_changed_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_status_changed_cb_n2",utc_asp_advert_set_status_changed_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_unset_status_changed_cb_p",utc_asp_advert_unset_status_changed_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_unset_status_changed_cb_n",utc_asp_advert_unset_status_changed_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_request_cb_p",utc_asp_session_set_request_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_request_cb_n1",utc_asp_session_set_request_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_request_cb_n2",utc_asp_session_set_request_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_request_cb_p",utc_asp_session_unset_request_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_request_cb_n",utc_asp_session_unset_request_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_config_request_cb_p",utc_asp_session_set_config_request_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_config_request_cb_n1",utc_asp_session_set_config_request_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_config_request_cb_n2",utc_asp_session_set_config_request_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_config_request_cb_p",utc_asp_session_unset_config_request_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_config_request_cb_n",utc_asp_session_unset_config_request_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_connect_status_cb_p",utc_asp_session_set_connect_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_connect_status_cb_n1",utc_asp_session_set_connect_status_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_connect_status_cb_n2",utc_asp_session_set_connect_status_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_connect_status_cb_p",utc_asp_session_unset_connect_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_connect_status_cb_n",utc_asp_session_unset_connect_status_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_status_cb_p",utc_asp_session_set_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_status_cb_n1",utc_asp_session_set_status_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_status_cb_n2",utc_asp_session_set_status_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_status_cb_p",utc_asp_session_unset_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_status_cb_n",utc_asp_session_unset_status_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_port_status_cb_p",utc_asp_session_set_port_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_port_status_cb_n1",utc_asp_session_set_port_status_cb_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_port_status_cb_n2",utc_asp_session_set_port_status_cb_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_port_status_cb_p",utc_asp_session_unset_port_status_cb_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_unset_port_status_cb_n",utc_asp_session_unset_port_status_cb_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_create_p",utc_asp_advert_create_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_create_n1",utc_asp_advert_create_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_create_n2",utc_asp_advert_create_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_destroy_p",utc_asp_advert_destroy_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_destroy_n1",utc_asp_advert_destroy_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_destroy_n2",utc_asp_advert_destroy_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_destroy_n3",utc_asp_advert_destroy_n3,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_create_p",utc_asp_seek_create_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_create_n1",utc_asp_seek_create_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_create_n2",utc_asp_seek_create_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_create_n3",utc_asp_seek_create_n3,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_destroy_p",utc_asp_seek_destroy_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_destroy_n1",utc_asp_seek_destroy_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_destroy_n2",utc_asp_seek_destroy_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_destroy_n3",utc_asp_seek_destroy_n3,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_create_p",utc_asp_session_create_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_create_n1",utc_asp_session_create_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_create_n2",utc_asp_session_create_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_create_n3",utc_asp_session_create_n3,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_create_n4",utc_asp_session_create_n4,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_destroy_p",utc_asp_session_destroy_p,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_destroy_n1",utc_asp_session_destroy_n1,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_destroy_n2",utc_asp_session_destroy_n2,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_destroy_n3",utc_asp_session_destroy_n3,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_service_type_n",utc_asp_advert_set_service_type_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_auto_accept_n",utc_asp_advert_set_auto_accept_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_add_info_n",utc_asp_advert_add_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_get_info_n",utc_asp_advert_get_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_remove_info_n",utc_asp_advert_remove_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_status_n",utc_asp_advert_set_status_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_discovery_tech_n",utc_asp_advert_set_discovery_tech_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_preferred_connection_n",utc_asp_advert_set_preferred_connection_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_p2p_role_scheme_n",utc_asp_advert_set_p2p_role_scheme_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_get_p2p_role_scheme_n",utc_asp_advert_get_p2p_role_scheme_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_p2p_config_method_n",utc_asp_advert_set_p2p_config_method_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_get_p2p_config_method_n",utc_asp_advert_get_p2p_config_method_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_p2p_response_n",utc_asp_advert_set_p2p_response_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_start_advertising_n",utc_asp_advert_start_advertising_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_stop_advertising_n",utc_asp_advert_stop_advertising_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_change_service_status_n",utc_asp_advert_change_service_status_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_add_info_n",utc_asp_seek_add_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_remove_info_n",utc_asp_seek_remove_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_set_discovery_tech_n",utc_asp_seek_set_discovery_tech_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_set_preferred_connection_n",utc_asp_seek_set_preferred_connection_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_start_n",utc_asp_seek_start_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_seek_stop_n",utc_asp_seek_stop_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_mac_n",utc_asp_session_get_mac_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_id_n",utc_asp_session_get_id_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_info_n",utc_asp_session_set_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_info_n",utc_asp_session_get_info_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_p2p_role_scheme_n",utc_asp_session_set_p2p_role_scheme_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_p2p_role_scheme_n",utc_asp_session_get_p2p_role_scheme_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_p2p_config_method_n",utc_asp_session_set_p2p_config_method_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_p2p_config_method_n",utc_asp_session_get_p2p_config_method_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_close_status_n",utc_asp_session_get_close_status_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_connect_n",utc_asp_session_connect_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_confirm_n",utc_asp_session_confirm_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_get_handle_n",utc_asp_session_get_handle_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_set_state_ready_n",utc_asp_session_set_state_ready_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_close_n",utc_asp_session_close_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_bind_port_n",utc_asp_session_bind_port_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_session_release_port_n",utc_asp_session_release_port_n,utc_asp_startup,utc_asp_cleanup},
	{"utc_asp_advert_set_service_type_p",utc_asp_advert_set_service_type_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_service_type_n1",utc_asp_advert_set_service_type_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_service_type_n2",utc_asp_advert_set_service_type_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_service_type_n3",utc_asp_advert_set_service_type_n3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_auto_accept_p",utc_asp_advert_set_auto_accept_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_auto_accept_n1",utc_asp_advert_set_auto_accept_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_auto_accept_n2",utc_asp_advert_set_auto_accept_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_add_info_p",utc_asp_advert_add_info_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_add_info_n1",utc_asp_advert_add_info_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_add_info_n2",utc_asp_advert_add_info_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_info_p",utc_asp_advert_get_info_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_info_n1",utc_asp_advert_get_info_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_info_n2",utc_asp_advert_get_info_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_remove_info_p",utc_asp_advert_remove_info_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_remove_info_n1",utc_asp_advert_remove_info_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_remove_info_n2",utc_asp_advert_remove_info_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_status_p",utc_asp_advert_set_status_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_status_n1",utc_asp_advert_set_status_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_status_n2",utc_asp_advert_set_status_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_p1",utc_asp_advert_set_discovery_tech_p1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_p2",utc_asp_advert_set_discovery_tech_p2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_p3",utc_asp_advert_set_discovery_tech_p3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_p4",utc_asp_advert_set_discovery_tech_p4,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_p5",utc_asp_advert_set_discovery_tech_p5,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_n1",utc_asp_advert_set_discovery_tech_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_n2",utc_asp_advert_set_discovery_tech_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_discovery_tech_n3",utc_asp_advert_set_discovery_tech_n3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_preferred_connection_p",utc_asp_advert_set_preferred_connection_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_preferred_connection_n1",utc_asp_advert_set_preferred_connection_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_preferred_connection_n2",utc_asp_advert_set_preferred_connection_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_role_scheme_p",utc_asp_advert_set_p2p_role_scheme_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_role_scheme_n1",utc_asp_advert_set_p2p_role_scheme_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_role_scheme_n2",utc_asp_advert_set_p2p_role_scheme_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_role_scheme_p",utc_asp_advert_get_p2p_role_scheme_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_role_scheme_n1",utc_asp_advert_get_p2p_role_scheme_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_role_scheme_n2",utc_asp_advert_get_p2p_role_scheme_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_p1",utc_asp_advert_set_p2p_config_method_p1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_p2",utc_asp_advert_set_p2p_config_method_p2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_p3",utc_asp_advert_set_p2p_config_method_p3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_p4",utc_asp_advert_set_p2p_config_method_p4,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_p5",utc_asp_advert_set_p2p_config_method_p5,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_n1",utc_asp_advert_set_p2p_config_method_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_n2",utc_asp_advert_set_p2p_config_method_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_config_method_n3",utc_asp_advert_set_p2p_config_method_n3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_config_method_p",utc_asp_advert_get_p2p_config_method_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_config_method_n1",utc_asp_advert_get_p2p_config_method_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_config_method_n2",utc_asp_advert_get_p2p_config_method_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_get_p2p_config_method_n3",utc_asp_advert_get_p2p_config_method_n3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_response_p",utc_asp_advert_set_p2p_response_p,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_response_n1",utc_asp_advert_set_p2p_response_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_response_n2",utc_asp_advert_set_p2p_response_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_response_n3",utc_asp_advert_set_p2p_response_n3,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_set_p2p_response_n4",utc_asp_advert_set_p2p_response_n4,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_start_advertising_n1",utc_asp_advert_start_advertising_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_start_advertising_n2",utc_asp_advert_start_advertising_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_stop_advertising_n1",utc_asp_advert_stop_advertising_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_stop_advertising_n2",utc_asp_advert_stop_advertising_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_change_service_status_n1",utc_asp_advert_change_service_status_n1,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_advert_change_service_status_n2",utc_asp_advert_change_service_status_n2,utc_asp_advert_startup,utc_asp_advert_cleanup},
	{"utc_asp_seek_add_info_p",utc_asp_seek_add_info_p,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_add_info_n1",utc_asp_seek_add_info_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_add_info_n2",utc_asp_seek_add_info_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_remove_info_p",utc_asp_seek_remove_info_p,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_remove_info_n1",utc_asp_seek_remove_info_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_remove_info_n2",utc_asp_seek_remove_info_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_p1",utc_asp_seek_set_discovery_tech_p1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_p2",utc_asp_seek_set_discovery_tech_p2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_p3",utc_asp_seek_set_discovery_tech_p3,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_p4",utc_asp_seek_set_discovery_tech_p4,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_p5",utc_asp_seek_set_discovery_tech_p5,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_n1",utc_asp_seek_set_discovery_tech_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_n2",utc_asp_seek_set_discovery_tech_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_discovery_tech_n3",utc_asp_seek_set_discovery_tech_n3,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_preferred_connection_p",utc_asp_seek_set_preferred_connection_p,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_preferred_connection_n1",utc_asp_seek_set_preferred_connection_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_set_preferred_connection_n2",utc_asp_seek_set_preferred_connection_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_start_n1",utc_asp_seek_start_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_start_n2",utc_asp_seek_start_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_stop_n1",utc_asp_seek_stop_n1,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_seek_stop_n2",utc_asp_seek_stop_n2,utc_asp_seek_startup,utc_asp_seek_cleanup},
	{"utc_asp_session_get_mac_p",utc_asp_session_get_mac_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_mac_n1",utc_asp_session_get_mac_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_mac_n2",utc_asp_session_get_mac_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_mac_n3",utc_asp_session_get_mac_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_id_p",utc_asp_session_get_id_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_id_n1",utc_asp_session_get_id_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_id_n2",utc_asp_session_get_id_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_id_n3",utc_asp_session_get_id_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_info_p",utc_asp_session_set_info_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_info_n1",utc_asp_session_set_info_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_info_n2",utc_asp_session_set_info_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_info_n3",utc_asp_session_set_info_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_info_p",utc_asp_session_get_info_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_info_n1",utc_asp_session_get_info_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_info_n2",utc_asp_session_get_info_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_info_n3",utc_asp_session_get_info_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_role_scheme_p",utc_asp_session_set_p2p_role_scheme_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_role_scheme_n1",utc_asp_session_set_p2p_role_scheme_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_role_scheme_n2",utc_asp_session_set_p2p_role_scheme_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_role_scheme_n3",utc_asp_session_set_p2p_role_scheme_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_role_scheme_p",utc_asp_session_get_p2p_role_scheme_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_role_scheme_n1",utc_asp_session_get_p2p_role_scheme_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_role_scheme_n2",utc_asp_session_get_p2p_role_scheme_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_role_scheme_n3",utc_asp_session_get_p2p_role_scheme_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_p1",utc_asp_session_set_p2p_config_method_p1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_p2",utc_asp_session_set_p2p_config_method_p2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_p3",utc_asp_session_set_p2p_config_method_p3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_p4",utc_asp_session_set_p2p_config_method_p4,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_n1",utc_asp_session_set_p2p_config_method_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_n2",utc_asp_session_set_p2p_config_method_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_p2p_config_method_n3",utc_asp_session_set_p2p_config_method_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_config_method_p",utc_asp_session_get_p2p_config_method_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_config_method_n1",utc_asp_session_get_p2p_config_method_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_config_method_n2",utc_asp_session_get_p2p_config_method_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_p2p_config_method_n3",utc_asp_session_get_p2p_config_method_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_close_status_p",utc_asp_session_get_close_status_p,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_close_status_n1",utc_asp_session_get_close_status_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_close_status_n2",utc_asp_session_get_close_status_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_close_status_n3",utc_asp_session_get_close_status_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_connect_n1",utc_asp_session_connect_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_connect_n2",utc_asp_session_connect_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_confirm_n1",utc_asp_session_confirm_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_confirm_n2",utc_asp_session_confirm_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_handle_n1",utc_asp_session_get_handle_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_get_handle_n2",utc_asp_session_get_handle_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_state_ready_n1",utc_asp_session_set_state_ready_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_set_state_ready_n2",utc_asp_session_set_state_ready_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_close_n1",utc_asp_session_close_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_close_n2",utc_asp_session_close_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_bind_port_n1",utc_asp_session_bind_port_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_bind_port_n2",utc_asp_session_bind_port_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_bind_port_n3",utc_asp_session_bind_port_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_release_port_n1",utc_asp_session_release_port_n1,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_release_port_n2",utc_asp_session_release_port_n2,utc_asp_session_startup,utc_asp_session_cleanup},
	{"utc_asp_session_release_port_n3",utc_asp_session_release_port_n3,utc_asp_session_startup,utc_asp_session_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ASP-NATIVE_H__
