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
#ifndef __TCT_OAUTH2-NATIVE_H__
#define __TCT_OAUTH2-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_oauth2_startup(void);
extern void ITs_oauth2_cleanup(void);
extern void ITs_oauth2_request_startup(void);
extern void ITs_oauth2_request_cleanup(void);

extern int ITc_oauth2_manager_create_destroy_p(void);
extern int ITc_oauth2_request_create_destroy_p(void);
extern int ITc_oauth2_request_set_get_auth_end_point_url_p(void);
extern int ITc_oauth2_request_set_get_token_end_point_url_p(void);
extern int ITc_oauth2_request_set_get_redirection_url_p(void);
extern int ITc_oauth2_request_set_get_refresh_token_url_p(void);
extern int ITc_oauth2_request_set_get_refresh_token_p(void);
extern int ITc_oauth2_request_set_get_response_type_p(void);
extern int ITc_oauth2_request_set_get_client_id_p(void);
extern int ITc_oauth2_request_set_get_client_secret_p(void);
extern int ITc_oauth2_request_set_client_authentication_type_p(void);
extern int ITc_oauth2_request_set_get_scope_p(void);
extern int ITc_oauth2_request_set_get_state_p(void);
extern int ITc_oauth2_request_set_get_grant_type_p(void);
extern int ITc_oauth2_request_set_get_authorization_code_p(void);
extern int ITc_oauth2_request_set_get_user_name_p(void);
extern int ITc_oauth2_request_set_get_password_p(void);
extern int ITc_oauth2_request_add_get_custom_data_p(void);

testcase tc_array[] = {
	{"ITc_oauth2_manager_create_destroy_p",ITc_oauth2_manager_create_destroy_p,ITs_oauth2_startup,ITs_oauth2_cleanup},
	{"ITc_oauth2_request_create_destroy_p",ITc_oauth2_request_create_destroy_p,ITs_oauth2_startup,ITs_oauth2_cleanup},
	{"ITc_oauth2_request_set_get_auth_end_point_url_p",ITc_oauth2_request_set_get_auth_end_point_url_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_token_end_point_url_p",ITc_oauth2_request_set_get_token_end_point_url_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_redirection_url_p",ITc_oauth2_request_set_get_redirection_url_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_refresh_token_url_p",ITc_oauth2_request_set_get_refresh_token_url_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_refresh_token_p",ITc_oauth2_request_set_get_refresh_token_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_response_type_p",ITc_oauth2_request_set_get_response_type_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_client_id_p",ITc_oauth2_request_set_get_client_id_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_client_secret_p",ITc_oauth2_request_set_get_client_secret_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_client_authentication_type_p",ITc_oauth2_request_set_client_authentication_type_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_scope_p",ITc_oauth2_request_set_get_scope_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_state_p",ITc_oauth2_request_set_get_state_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_grant_type_p",ITc_oauth2_request_set_get_grant_type_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_authorization_code_p",ITc_oauth2_request_set_get_authorization_code_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_user_name_p",ITc_oauth2_request_set_get_user_name_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_set_get_password_p",ITc_oauth2_request_set_get_password_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{"ITc_oauth2_request_add_get_custom_data_p",ITc_oauth2_request_add_get_custom_data_p,ITs_oauth2_request_startup,ITs_oauth2_request_cleanup},
	{NULL, NULL}
};

#endif // __TCT_OAUTH2-NATIVE_H__
