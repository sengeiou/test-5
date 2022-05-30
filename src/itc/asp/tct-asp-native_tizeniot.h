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
#ifndef __TCT_ASP_NATIVE_H__
#define __TCT_ASP_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_asp_startup(void);
extern void ITs_asp_cleanup(void);
extern void ITs_asp_advert_startup(void);
extern void ITs_asp_advert_cleanup(void);
extern void ITs_asp_seek_startup(void);
extern void ITs_asp_seek_cleanup(void);
extern void ITs_asp_session_startup(void);
extern void ITs_asp_session_cleanup(void);

extern int ITc_asp_initialize_deinitialize_p(void);
extern int ITc_asp_advert_create_destroy_p(void);
extern int ITc_asp_seek_create_destroy_p(void);
extern int ITc_asp_session_create_destroy_p(void);
extern int ITc_asp_advert_set_service_type_p(void);
extern int ITc_asp_advert_set_auto_accept_p(void);
extern int ITc_asp_advert_add_get_remove_info_p(void);
extern int ITc_asp_advert_set_status_p(void);
extern int ITc_asp_advert_set_discovery_tech_p(void);
extern int ITc_asp_advert_set_preferred_connection_p(void);
extern int ITc_asp_advert_set_get_p2p_role_scheme_p(void);
extern int ITc_asp_advert_set_get_p2p_config_method_p(void);
extern int ITc_asp_advert_set_p2p_response_p(void);
extern int ITc_asp_advert_start_stop_advertising_p(void);
extern int ITc_asp_advert_change_service_status_p(void);
extern int ITc_asp_advert_set_unset_status_changed_cb_p(void);
extern int ITc_asp_seek_add_remove_info_p(void);
extern int ITc_asp_seek_set_discovery_tech_p(void);
extern int ITc_asp_seek_set_preferred_connection_p(void);
extern int ITc_asp_seek_start_stop_p(void);
extern int ITc_asp_seek_set_unset_search_result_cb_p(void);
extern int ITc_asp_session_get_mac_p(void);
extern int ITc_asp_session_get_id_p(void);
extern int ITc_asp_session_set_get_info_p(void);
extern int ITc_asp_session_set_get_p2p_role_scheme_p(void);
extern int ITc_asp_session_set_get_p2p_config_method_p(void);
extern int ITc_asp_session_get_close_status_p(void);
extern int ITc_asp_session_connect_p(void);
extern int ITc_asp_session_set_unset_request_cb_p(void);
extern int ITc_asp_session_set_unset_config_request_cb_p(void);
extern int ITc_asp_session_set_unset_connect_status_cb_p(void);
extern int ITc_asp_session_set_unset_status_cb_p(void);
extern int ITc_asp_session_set_unset_port_status_cb_p(void);

testcase tc_array[] = {
    {"ITc_asp_initialize_deinitialize_p", ITc_asp_initialize_deinitialize_p, ITs_asp_startup, ITs_asp_cleanup},
    {"ITc_asp_advert_create_destroy_p", ITc_asp_advert_create_destroy_p, ITs_asp_startup, ITs_asp_cleanup},
    {"ITc_asp_seek_create_destroy_p", ITc_asp_seek_create_destroy_p, ITs_asp_startup, ITs_asp_cleanup},
    {"ITc_asp_session_create_destroy_p", ITc_asp_session_create_destroy_p, ITs_asp_startup, ITs_asp_cleanup},
    {"ITc_asp_advert_set_service_type_p", ITc_asp_advert_set_service_type_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_auto_accept_p", ITc_asp_advert_set_auto_accept_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_add_get_remove_info_p", ITc_asp_advert_add_get_remove_info_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_status_p", ITc_asp_advert_set_status_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_discovery_tech_p", ITc_asp_advert_set_discovery_tech_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_preferred_connection_p", ITc_asp_advert_set_preferred_connection_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_get_p2p_role_scheme_p", ITc_asp_advert_set_get_p2p_role_scheme_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_get_p2p_config_method_p", ITc_asp_advert_set_get_p2p_config_method_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_p2p_response_p", ITc_asp_advert_set_p2p_response_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_start_stop_advertising_p", ITc_asp_advert_start_stop_advertising_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_change_service_status_p", ITc_asp_advert_change_service_status_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_advert_set_unset_status_changed_cb_p", ITc_asp_advert_set_unset_status_changed_cb_p, ITs_asp_advert_startup, ITs_asp_advert_cleanup},
    {"ITc_asp_seek_add_remove_info_p", ITc_asp_seek_add_remove_info_p, ITs_asp_seek_startup, ITs_asp_seek_cleanup},
    {"ITc_asp_seek_set_discovery_tech_p", ITc_asp_seek_set_discovery_tech_p, ITs_asp_seek_startup, ITs_asp_seek_cleanup},
    {"ITc_asp_seek_set_preferred_connection_p", ITc_asp_seek_set_preferred_connection_p, ITs_asp_seek_startup, ITs_asp_seek_cleanup},
    {"ITc_asp_seek_start_stop_p", ITc_asp_seek_start_stop_p, ITs_asp_seek_startup, ITs_asp_seek_cleanup},
    {"ITc_asp_seek_set_unset_search_result_cb_p", ITc_asp_seek_set_unset_search_result_cb_p, ITs_asp_seek_startup, ITs_asp_seek_cleanup},
    {"ITc_asp_session_get_mac_p", ITc_asp_session_get_mac_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_get_id_p", ITc_asp_session_get_id_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_get_info_p", ITc_asp_session_set_get_info_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_get_p2p_role_scheme_p", ITc_asp_session_set_get_p2p_role_scheme_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_get_p2p_config_method_p", ITc_asp_session_set_get_p2p_config_method_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_get_close_status_p", ITc_asp_session_get_close_status_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_connect_p", ITc_asp_session_connect_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_unset_request_cb_p", ITc_asp_session_set_unset_request_cb_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_unset_config_request_cb_p", ITc_asp_session_set_unset_config_request_cb_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_unset_connect_status_cb_p", ITc_asp_session_set_unset_connect_status_cb_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_unset_status_cb_p", ITc_asp_session_set_unset_status_cb_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
    {"ITc_asp_session_set_unset_port_status_cb_p", ITc_asp_session_set_unset_port_status_cb_p, ITs_asp_session_startup, ITs_asp_session_cleanup},
	{NULL, NULL}
};

#endif // __TCT_ASP_NATIVE_H__
