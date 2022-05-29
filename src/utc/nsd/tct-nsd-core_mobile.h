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
#ifndef __TCT_NSD-NATIVE_H__
#define __TCT_NSD-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_nsd_ssdp_browse_startup(void);
extern void utc_nsd_ssdp_browse_cleanup(void);
extern void utc_nsd_ssdp_register_startup(void);
extern void utc_nsd_ssdp_register_cleanup(void);
extern void utc_nsd_dnssd_browse_startup(void);
extern void utc_nsd_dnssd_browse_cleanup(void);
extern void utc_nsd_dnssd_register_startup(void);
extern void utc_nsd_dnssd_register_cleanup(void);

extern int utc_nsd_ssdp_start_browsing_service_p(void);
extern int utc_nsd_ssdp_start_browsing_service_n(void);
extern int utc_nsd_ssdp_stop_browsing_service_p(void);
extern int utc_nsd_ssdp_stop_browsing_service_n1(void);
extern int utc_nsd_ssdp_stop_browsing_service_n2(void);
extern int utc_nsd_ssdp_initialize_p(void);
extern int utc_nsd_ssdp_deinitialize_p(void);
extern int utc_nsd_ssdp_deinitialize_n(void);
extern int utc_nsd_ssdp_create_local_service_p(void);
extern int utc_nsd_ssdp_create_local_service_n(void);
extern int utc_nsd_ssdp_destroy_local_service_p(void);
extern int utc_nsd_ssdp_detroy_local_service_n(void);
extern int utc_nsd_ssdp_set_usn_p(void);
extern int utc_nsd_ssdp_set_usn_n1(void);
extern int utc_nsd_ssdp_set_usn_n2(void);
extern int utc_nsd_ssdp_set_url_p(void);
extern int utc_nsd_ssdp_set_url_n1(void);
extern int utc_nsd_ssdp_set_url_n2(void);
extern int utc_nsd_ssdp_get_target_p(void);
extern int utc_nsd_ssdp_get_target_n1(void);
extern int utc_nsd_ssdp_get_target_n2(void);
extern int utc_nsd_ssdp_get_usn_p(void);
extern int utc_nsd_ssdp_get_usn_n1(void);
extern int utc_nsd_ssdp_get_usn_n2(void);
extern int utc_nsd_ssdp_get_url_p(void);
extern int utc_nsd_ssdp_get_url_n1(void);
extern int utc_nsd_ssdp_get_url_n2(void);
extern int utc_nsd_ssdp_register_local_service_p(void);
extern int utc_nsd_ssdp_register_local_service_n1(void);
extern int utc_nsd_ssdp_register_local_service_n2(void);
extern int utc_nsd_ssdp_deregister_local_service_p(void);
extern int utc_nsd_ssdp_deregister_local_service_n(void);
extern int utc_nsd_dnssd_start_browsing_service_p(void);
extern int utc_nsd_dnssd_start_browsing_service_n(void);
extern int utc_nsd_dnssd_stop_browsing_service_p(void);
extern int utc_nsd_dnssd_stop_browsing_service_n(void);
extern int utc_nsd_dnssd_service_get_ip_n1(void);
extern int utc_nsd_dnssd_service_get_ip_n2(void);
extern int utc_nsd_dnssd_initialize_p(void);
extern int utc_nsd_dnssd_deinitialize_p(void);
extern int utc_nsd_dnssd_deinitialize_n(void);
extern int utc_nsd_dnssd_create_local_service_p(void);
extern int utc_nsd_dnssd_create_local_service_n(void);
extern int utc_nsd_dnssd_destroy_local_service_p(void);
extern int utc_nsd_dnssd_detroy_local_service_n(void);
extern int utc_nsd_dnssd_set_name_p(void);
extern int utc_nsd_dnssd_set_name_n1(void);
extern int utc_nsd_dnssd_set_name_n2(void);
extern int utc_nsd_dnssd_set_port_p(void);
extern int utc_nsd_dnssd_set_port_n1(void);
extern int utc_nsd_dnssd_set_port_n2(void);
extern int utc_nsd_dnssd_set_record_p(void);
extern int utc_nsd_dnssd_set_record_n(void);
extern int utc_nsd_dnssd_unset_record_p(void);
extern int utc_nsd_dnssd_unset_record_n(void);
extern int utc_nsd_dnssd_add_txt_record_p(void);
extern int utc_nsd_dnssd_add_txt_record_n1(void);
extern int utc_nsd_dnssd_add_txt_record_n2(void);
extern int utc_nsd_dnssd_get_all_txt_record_p(void);
extern int utc_nsd_dnssd_get_all_txt_record_n1(void);
extern int utc_nsd_dnssd_get_all_txt_record_n2(void);
extern int utc_nsd_dnssd_remove_txt_record_p(void);
extern int utc_nsd_dnssd_remove_txt_record_n1(void);
extern int utc_nsd_dnssd_remove_txt_record_n2(void);
extern int utc_nsd_dnssd_get_type_p(void);
extern int utc_nsd_dnssd_get_type_n1(void);
extern int utc_nsd_dnssd_get_type_n2(void);
extern int utc_nsd_dnssd_get_name_p(void);
extern int utc_nsd_dnssd_get_name_n1(void);
extern int utc_nsd_dnssd_get_name_n2(void);
extern int utc_nsd_dnssd_get_port_p(void);
extern int utc_nsd_dnssd_get_port_n1(void);
extern int utc_nsd_dnssd_get_port_n2(void);
extern int utc_nsd_dnssd_register_local_service_p(void);
extern int utc_nsd_dnssd_register_local_service_n(void);
extern int utc_nsd_dnssd_deregister_local_service_p(void);
extern int utc_nsd_dnssd_deregister_local_service_n(void);

testcase tc_array[] = {
	{"utc_nsd_ssdp_start_browsing_service_p",utc_nsd_ssdp_start_browsing_service_p,utc_nsd_ssdp_browse_startup,utc_nsd_ssdp_browse_cleanup},
	{"utc_nsd_ssdp_start_browsing_service_n",utc_nsd_ssdp_start_browsing_service_n,utc_nsd_ssdp_browse_startup,utc_nsd_ssdp_browse_cleanup},
	{"utc_nsd_ssdp_stop_browsing_service_p",utc_nsd_ssdp_stop_browsing_service_p,utc_nsd_ssdp_browse_startup,utc_nsd_ssdp_browse_cleanup},
	{"utc_nsd_ssdp_stop_browsing_service_n1",utc_nsd_ssdp_stop_browsing_service_n1,utc_nsd_ssdp_browse_startup,utc_nsd_ssdp_browse_cleanup},
	{"utc_nsd_ssdp_stop_browsing_service_n2",utc_nsd_ssdp_stop_browsing_service_n2,utc_nsd_ssdp_browse_startup,utc_nsd_ssdp_browse_cleanup},
	{"utc_nsd_ssdp_initialize_p",utc_nsd_ssdp_initialize_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_deinitialize_p",utc_nsd_ssdp_deinitialize_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_deinitialize_n",utc_nsd_ssdp_deinitialize_n,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_create_local_service_p",utc_nsd_ssdp_create_local_service_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_create_local_service_n",utc_nsd_ssdp_create_local_service_n,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_destroy_local_service_p",utc_nsd_ssdp_destroy_local_service_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_detroy_local_service_n",utc_nsd_ssdp_detroy_local_service_n,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_usn_p",utc_nsd_ssdp_set_usn_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_usn_n1",utc_nsd_ssdp_set_usn_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_usn_n2",utc_nsd_ssdp_set_usn_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_url_p",utc_nsd_ssdp_set_url_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_url_n1",utc_nsd_ssdp_set_url_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_set_url_n2",utc_nsd_ssdp_set_url_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_target_p",utc_nsd_ssdp_get_target_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_target_n1",utc_nsd_ssdp_get_target_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_target_n2",utc_nsd_ssdp_get_target_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_usn_p",utc_nsd_ssdp_get_usn_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_usn_n1",utc_nsd_ssdp_get_usn_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_usn_n2",utc_nsd_ssdp_get_usn_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_url_p",utc_nsd_ssdp_get_url_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_url_n1",utc_nsd_ssdp_get_url_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_get_url_n2",utc_nsd_ssdp_get_url_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_register_local_service_p",utc_nsd_ssdp_register_local_service_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_register_local_service_n1",utc_nsd_ssdp_register_local_service_n1,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_register_local_service_n2",utc_nsd_ssdp_register_local_service_n2,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_deregister_local_service_p",utc_nsd_ssdp_deregister_local_service_p,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_ssdp_deregister_local_service_n",utc_nsd_ssdp_deregister_local_service_n,utc_nsd_ssdp_register_startup,utc_nsd_ssdp_register_cleanup},
	{"utc_nsd_dnssd_start_browsing_service_p",utc_nsd_dnssd_start_browsing_service_p,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_start_browsing_service_n",utc_nsd_dnssd_start_browsing_service_n,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_stop_browsing_service_p",utc_nsd_dnssd_stop_browsing_service_p,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_stop_browsing_service_n",utc_nsd_dnssd_stop_browsing_service_n,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_service_get_ip_n1",utc_nsd_dnssd_service_get_ip_n1,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_service_get_ip_n2",utc_nsd_dnssd_service_get_ip_n2,utc_nsd_dnssd_browse_startup,utc_nsd_dnssd_browse_cleanup},
	{"utc_nsd_dnssd_initialize_p",utc_nsd_dnssd_initialize_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_deinitialize_p",utc_nsd_dnssd_deinitialize_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_deinitialize_n",utc_nsd_dnssd_deinitialize_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_create_local_service_p",utc_nsd_dnssd_create_local_service_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_create_local_service_n",utc_nsd_dnssd_create_local_service_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_destroy_local_service_p",utc_nsd_dnssd_destroy_local_service_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_detroy_local_service_n",utc_nsd_dnssd_detroy_local_service_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_name_p",utc_nsd_dnssd_set_name_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_name_n1",utc_nsd_dnssd_set_name_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_name_n2",utc_nsd_dnssd_set_name_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_port_p",utc_nsd_dnssd_set_port_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_port_n1",utc_nsd_dnssd_set_port_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_port_n2",utc_nsd_dnssd_set_port_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_record_p",utc_nsd_dnssd_set_record_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_set_record_n",utc_nsd_dnssd_set_record_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_unset_record_p",utc_nsd_dnssd_unset_record_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_unset_record_n",utc_nsd_dnssd_unset_record_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_add_txt_record_p",utc_nsd_dnssd_add_txt_record_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_add_txt_record_n1",utc_nsd_dnssd_add_txt_record_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_add_txt_record_n2",utc_nsd_dnssd_add_txt_record_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_all_txt_record_p",utc_nsd_dnssd_get_all_txt_record_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_all_txt_record_n1",utc_nsd_dnssd_get_all_txt_record_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_all_txt_record_n2",utc_nsd_dnssd_get_all_txt_record_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_remove_txt_record_p",utc_nsd_dnssd_remove_txt_record_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_remove_txt_record_n1",utc_nsd_dnssd_remove_txt_record_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_remove_txt_record_n2",utc_nsd_dnssd_remove_txt_record_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_type_p",utc_nsd_dnssd_get_type_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_type_n1",utc_nsd_dnssd_get_type_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_type_n2",utc_nsd_dnssd_get_type_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_name_p",utc_nsd_dnssd_get_name_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_name_n1",utc_nsd_dnssd_get_name_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_name_n2",utc_nsd_dnssd_get_name_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_port_p",utc_nsd_dnssd_get_port_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_port_n1",utc_nsd_dnssd_get_port_n1,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_get_port_n2",utc_nsd_dnssd_get_port_n2,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_register_local_service_p",utc_nsd_dnssd_register_local_service_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_register_local_service_n",utc_nsd_dnssd_register_local_service_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_deregister_local_service_p",utc_nsd_dnssd_deregister_local_service_p,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{"utc_nsd_dnssd_deregister_local_service_n",utc_nsd_dnssd_deregister_local_service_n,utc_nsd_dnssd_register_startup,utc_nsd_dnssd_register_cleanup},
	{NULL, NULL}
};

#endif // __TCT_NSD-NATIVE_H__
