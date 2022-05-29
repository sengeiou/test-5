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
#ifndef __TCT_FIDO-CLIENT-NATIVE_H__
#define __TCT_FIDO-CLIENT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_fido_client_startup(void);
extern void ITs_fido_client_cleanup(void);

extern int ITc_fido_foreach_authenticator_p(void);
extern int ITc_fidoclient_fido_authenticator_getTitle_p(void);
extern int ITc_fido_authenticator_get_aaid_p(void);
extern int ITc_fidoclient_fido_authenticator_getdescription_p(void);
extern int ITc_fidoclient_fido_authenticator_getscheme_p(void);
extern int ITc_fidoclient_fido_authenticator_getalgorithm_p(void);
extern int ITc_fido_authenticator_foreach_attestation_type_p(void);
extern int ITc_fido_authenticator_get_verification_method_p(void);
extern int ITc_fido_authenticator_get_key_protection_method_p(void);
extern int ITc_fido_authenticator_get_attachment_hint_p(void);
extern int ITc_fido_authenticator_get_is_second_factor_only_p(void);
extern int ITc_fido_authenticator_get_tc_display_type_p(void);
extern int ITc_fido_authenticator_get_tc_discplay_p(void);
extern int ITc_fido_authenticator_get_icon_p(void);
extern int ITc_fido_get_client_vendor_p(void);
extern int ITc_fido_get_client_version_p(void);
extern int ITc_fido_uaf_is_supported_p(void);
extern int ITc_fido_uaf_get_response_message_p(void);
extern int ITc_fido_uaf_set_server_result_p(void);
extern int ITc_fido_authenticator_get_matcher_protection_method_p(void);

testcase tc_array[] = {
	{"ITc_fido_foreach_authenticator_p",ITc_fido_foreach_authenticator_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fidoclient_fido_authenticator_getTitle_p",ITc_fidoclient_fido_authenticator_getTitle_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_aaid_p",ITc_fido_authenticator_get_aaid_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fidoclient_fido_authenticator_getdescription_p",ITc_fidoclient_fido_authenticator_getdescription_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fidoclient_fido_authenticator_getscheme_p",ITc_fidoclient_fido_authenticator_getscheme_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fidoclient_fido_authenticator_getalgorithm_p",ITc_fidoclient_fido_authenticator_getalgorithm_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_foreach_attestation_type_p",ITc_fido_authenticator_foreach_attestation_type_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_verification_method_p",ITc_fido_authenticator_get_verification_method_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_key_protection_method_p",ITc_fido_authenticator_get_key_protection_method_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_attachment_hint_p",ITc_fido_authenticator_get_attachment_hint_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_is_second_factor_only_p",ITc_fido_authenticator_get_is_second_factor_only_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_tc_display_type_p",ITc_fido_authenticator_get_tc_display_type_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_tc_discplay_p",ITc_fido_authenticator_get_tc_discplay_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_icon_p",ITc_fido_authenticator_get_icon_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_get_client_vendor_p",ITc_fido_get_client_vendor_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_get_client_version_p",ITc_fido_get_client_version_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_uaf_is_supported_p",ITc_fido_uaf_is_supported_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_uaf_get_response_message_p",ITc_fido_uaf_get_response_message_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_uaf_set_server_result_p",ITc_fido_uaf_set_server_result_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{"ITc_fido_authenticator_get_matcher_protection_method_p",ITc_fido_authenticator_get_matcher_protection_method_p,ITs_fido_client_startup,ITs_fido_client_cleanup},
	{NULL, NULL}
};

#endif // __TCT_FIDO-CLIENT-NATIVE_H__
