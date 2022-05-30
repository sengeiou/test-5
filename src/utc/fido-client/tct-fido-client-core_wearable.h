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

extern void utc_fido_client_startup(void);
extern void utc_fido_client_cleanup(void);

extern int utc_fido_client_get_client_vendor_p(void);
extern int utc_fido_client_get_client_vendor_n(void);
extern int utc_fido_client_get_client_version_p(void);
extern int utc_fido_client_get_client_version_n(void);
extern int utc_fido_client_uaf_is_supported_p(void);
extern int utc_fido_client_uaf_is_supported_n(void);
extern int utc_fido_client_uaf_get_response_message_n1(void);
extern int utc_fido_client_uaf_get_response_message_n2(void);
extern int utc_fido_client_uaf_set_server_result_n(void);
extern int utc_fido_client_foreach_authenticator_n(void);
extern int utc_fido_client_authenticator_get_title_n(void);
extern int utc_fido_client_authenticator_get_aaid_n(void);
extern int utc_fido_client_authenticator_get_description_n(void);
extern int utc_fido_client_authenticator_get_assertion_scheme_n(void);
extern int utc_fido_client_authenticator_get_algorithm_n(void);
extern int utc_fido_client_authenticator_foreach_attestation_type_n(void);
extern int utc_fido_client_authenticator_get_verification_method_n(void);
extern int utc_fido_client_authenticator_get_key_protection_method_n(void);
extern int utc_fido_client_authenticator_get_matcher_protection_method_n(void);
extern int utc_fido_client_authenticator_get_attachment_hint_n(void);
extern int utc_fido_client_authenticator_get_is_second_factor_only_p(void);
extern int utc_fido_client_authenticator_get_tc_discplay_n(void);
extern int utc_fido_client_authenticator_get_tc_display_type_n(void);
extern int utc_fido_client_authenticator_get_icon_n(void);
extern int utc_fido_client_foreach_authenticator_p(void);

testcase tc_array[] = {
	{"utc_fido_client_get_client_vendor_p",utc_fido_client_get_client_vendor_p,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_get_client_vendor_n",utc_fido_client_get_client_vendor_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_get_client_version_p",utc_fido_client_get_client_version_p,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_get_client_version_n",utc_fido_client_get_client_version_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_uaf_is_supported_p",utc_fido_client_uaf_is_supported_p,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_uaf_is_supported_n",utc_fido_client_uaf_is_supported_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_uaf_get_response_message_n1",utc_fido_client_uaf_get_response_message_n1,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_uaf_get_response_message_n2",utc_fido_client_uaf_get_response_message_n2,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_uaf_set_server_result_n",utc_fido_client_uaf_set_server_result_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_foreach_authenticator_n",utc_fido_client_foreach_authenticator_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_title_n",utc_fido_client_authenticator_get_title_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_aaid_n",utc_fido_client_authenticator_get_aaid_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_description_n",utc_fido_client_authenticator_get_description_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_assertion_scheme_n",utc_fido_client_authenticator_get_assertion_scheme_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_algorithm_n",utc_fido_client_authenticator_get_algorithm_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_foreach_attestation_type_n",utc_fido_client_authenticator_foreach_attestation_type_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_verification_method_n",utc_fido_client_authenticator_get_verification_method_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_key_protection_method_n",utc_fido_client_authenticator_get_key_protection_method_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_matcher_protection_method_n",utc_fido_client_authenticator_get_matcher_protection_method_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_attachment_hint_n",utc_fido_client_authenticator_get_attachment_hint_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_is_second_factor_only_p",utc_fido_client_authenticator_get_is_second_factor_only_p,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_tc_discplay_n",utc_fido_client_authenticator_get_tc_discplay_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_tc_display_type_n",utc_fido_client_authenticator_get_tc_display_type_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_authenticator_get_icon_n",utc_fido_client_authenticator_get_icon_n,utc_fido_client_startup,utc_fido_client_cleanup},
	{"utc_fido_client_foreach_authenticator_p",utc_fido_client_foreach_authenticator_p,utc_fido_client_startup,utc_fido_client_cleanup},
	{NULL, NULL}
};

#endif // __TCT_FIDO-CLIENT-NATIVE_H__
