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

extern void ITs_nsd_ssdp_startup(void);
extern void ITs_nsd_ssdp_cleanup(void);
extern void ITs_nsd_dnssd_startup(void);
extern void ITs_nsd_dnssd_cleanup(void);

extern int ITc_ssdp_initialize_deinitialize_p(void);
extern int ITc_ssdp_create_destroy_local_service_p(void);
extern int ITc_ssdp_service_set_get_usn_p(void);
extern int ITc_ssdp_service_set_get_url_p(void);
extern int ITc_ssdp_service_get_target_p(void);
extern int ITc_ssdp_register_deregister_local_service_p(void);
extern int ITc_ssdp_start_stop_browsing_service_p(void);
extern int ITc_dnssd_initialize_deinitialize_p(void);
extern int ITc_dnssd_create_destroy_local_service_p(void);
extern int ITc_dnssd_service_set_get_name_p(void);
extern int ITc_dnssd_service_set_get_port_p(void);
extern int ITc_dnssd_service_get_type_p(void);
extern int ITc_dnssd_register_deregister_local_service_p(void);
extern int ITc_dnssd_service_add_remove_txt_record_p(void);
extern int ITc_dnssd_service_set_unset_record_p(void);
extern int ITc_dnssd_service_get_all_txt_record_p(void);

testcase tc_array[] = {
	{"ITc_ssdp_initialize_deinitialize_p",ITc_ssdp_initialize_deinitialize_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_create_destroy_local_service_p",ITc_ssdp_create_destroy_local_service_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_service_set_get_usn_p",ITc_ssdp_service_set_get_usn_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_service_set_get_url_p",ITc_ssdp_service_set_get_url_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_service_get_target_p",ITc_ssdp_service_get_target_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_register_deregister_local_service_p",ITc_ssdp_register_deregister_local_service_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_ssdp_start_stop_browsing_service_p",ITc_ssdp_start_stop_browsing_service_p,ITs_nsd_ssdp_startup,ITs_nsd_ssdp_cleanup},
	{"ITc_dnssd_initialize_deinitialize_p",ITc_dnssd_initialize_deinitialize_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_create_destroy_local_service_p",ITc_dnssd_create_destroy_local_service_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_set_get_name_p",ITc_dnssd_service_set_get_name_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_set_get_port_p",ITc_dnssd_service_set_get_port_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_get_type_p",ITc_dnssd_service_get_type_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_register_deregister_local_service_p",ITc_dnssd_register_deregister_local_service_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_add_remove_txt_record_p",ITc_dnssd_service_add_remove_txt_record_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_set_unset_record_p",ITc_dnssd_service_set_unset_record_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{"ITc_dnssd_service_get_all_txt_record_p",ITc_dnssd_service_get_all_txt_record_p,ITs_nsd_dnssd_startup,ITs_nsd_dnssd_cleanup},
	{NULL, NULL}
};

#endif // __TCT_NSD-NATIVE_H__
