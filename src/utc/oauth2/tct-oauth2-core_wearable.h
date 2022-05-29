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

extern void utc_oauth2_startup(void);
extern void utc_oauth2_cleanup(void);

extern int utc_oauth2_manager_create_p(void);
extern int utc_oauth2_manager_create_n(void);
extern int utc_oauth2_manager_destroy_p(void);
extern int utc_oauth2_manager_destroy_n(void);
extern int utc_oauth2_manager_request_token_n(void);
extern int utc_oauth2_manager_request_authorization_grant_n(void);
extern int utc_oauth2_manager_request_access_token_n(void);
extern int utc_oauth2_manager_refresh_access_token_n(void);
extern int utc_oauth2_manager_is_request_in_progress_n(void);
extern int utc_oauth2_manager_clear_cookies_n(void);
extern int utc_oauth2_manager_clear_cache_n(void);
extern int utc_oauth2_request_create_p(void);
extern int utc_oauth2_request_create_n(void);
extern int utc_oauth2_request_destroy_p(void);
extern int utc_oauth2_request_destroy_n(void);
extern int utc_oauth2_request_set_auth_end_point_url_p(void);
extern int utc_oauth2_request_set_auth_end_point_url_n(void);
extern int utc_oauth2_request_set_token_end_point_url_p(void);
extern int utc_oauth2_request_set_token_end_point_url_n(void);
extern int utc_oauth2_request_set_redirection_url_p(void);
extern int utc_oauth2_request_set_redirection_url_n(void);
extern int utc_oauth2_request_set_refresh_token_url_p(void);
extern int utc_oauth2_request_set_refresh_token_url_n(void);
extern int utc_oauth2_request_set_refresh_token_p(void);
extern int utc_oauth2_request_set_refresh_token_n(void);
extern int utc_oauth2_request_set_response_type_p(void);
extern int utc_oauth2_request_set_response_type_n(void);
extern int utc_oauth2_request_set_client_id_p(void);
extern int utc_oauth2_request_set_client_id_n(void);
extern int utc_oauth2_request_set_client_authentication_type_p(void);
extern int utc_oauth2_request_set_client_authentication_type_n(void);
extern int utc_oauth2_request_set_scope_p(void);
extern int utc_oauth2_request_set_scope_n(void);
extern int utc_oauth2_request_set_state_p(void);
extern int utc_oauth2_request_set_state_n(void);
extern int utc_oauth2_request_set_grant_type_p(void);
extern int utc_oauth2_request_set_grant_type_n(void);
extern int utc_oauth2_request_set_authorization_code_p(void);
extern int utc_oauth2_request_set_authorization_code_n(void);
extern int utc_oauth2_request_set_user_name_p(void);
extern int utc_oauth2_request_set_user_name_n(void);
extern int utc_oauth2_request_set_password_p(void);
extern int utc_oauth2_request_set_password_n(void);
extern int utc_oauth2_request_add_custom_data_p(void);
extern int utc_oauth2_request_add_custom_data_n(void);
extern int utc_oauth2_request_get_auth_end_point_url_p(void);
extern int utc_oauth2_request_get_auth_end_point_url_n(void);
extern int utc_oauth2_request_get_token_end_point_url_p(void);
extern int utc_oauth2_request_get_token_end_point_url_n(void);
extern int utc_oauth2_request_get_redirection_url_p(void);
extern int utc_oauth2_request_get_redirection_url_n(void);
extern int utc_oauth2_request_get_refresh_token_url_p(void);
extern int utc_oauth2_request_get_refresh_token_url_n(void);
extern int utc_oauth2_request_get_refresh_token_p(void);
extern int utc_oauth2_request_get_refresh_token_n(void);
extern int utc_oauth2_request_get_response_type_p(void);
extern int utc_oauth2_request_get_response_type_n(void);
extern int utc_oauth2_request_get_client_id_p(void);
extern int utc_oauth2_request_get_client_id_n(void);
extern int utc_oauth2_request_get_client_secret_p(void);
extern int utc_oauth2_request_get_client_secret_n(void);
extern int utc_oauth2_request_get_scope_p(void);
extern int utc_oauth2_request_get_scope_n(void);
extern int utc_oauth2_request_get_state_p(void);
extern int utc_oauth2_request_get_state_n(void);
extern int utc_oauth2_request_get_grant_type_p(void);
extern int utc_oauth2_request_get_grant_type_n(void);
extern int utc_oauth2_request_get_authorization_code_p(void);
extern int utc_oauth2_request_get_authorization_code_n(void);
extern int utc_oauth2_request_get_user_name_p(void);
extern int utc_oauth2_request_get_user_name_n(void);
extern int utc_oauth2_request_get_password_p(void);
extern int utc_oauth2_request_get_password_n(void);
extern int utc_oauth2_request_get_custom_data_p(void);
extern int utc_oauth2_request_get_custom_data_n(void);
extern int utc_oauth2_response_destroy_n(void);
extern int utc_oauth2_response_get_authorization_code_n(void);
extern int utc_oauth2_response_get_state_n(void);
extern int utc_oauth2_response_get_access_token_n(void);
extern int utc_oauth2_response_get_token_type_n(void);
extern int utc_oauth2_response_get_expires_in_n(void);
extern int utc_oauth2_response_get_refresh_token_n(void);
extern int utc_oauth2_response_get_scope_n(void);
extern int utc_oauth2_response_get_error_n(void);
extern int utc_oauth2_response_get_custom_data_n(void);
extern int utc_oauth2_error_get_code_n(void);
extern int utc_oauth2_error_get_description_n(void);
extern int utc_oauth2_error_get_uri_n(void);
extern int utc_oauth2_error_get_custom_data_n(void);

testcase tc_array[] = {
	{"utc_oauth2_manager_create_p",utc_oauth2_manager_create_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_create_n",utc_oauth2_manager_create_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_destroy_p",utc_oauth2_manager_destroy_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_destroy_n",utc_oauth2_manager_destroy_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_request_token_n",utc_oauth2_manager_request_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_request_authorization_grant_n",utc_oauth2_manager_request_authorization_grant_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_request_access_token_n",utc_oauth2_manager_request_access_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_refresh_access_token_n",utc_oauth2_manager_refresh_access_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_is_request_in_progress_n",utc_oauth2_manager_is_request_in_progress_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_clear_cookies_n",utc_oauth2_manager_clear_cookies_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_manager_clear_cache_n",utc_oauth2_manager_clear_cache_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_create_p",utc_oauth2_request_create_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_create_n",utc_oauth2_request_create_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_destroy_p",utc_oauth2_request_destroy_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_destroy_n",utc_oauth2_request_destroy_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_auth_end_point_url_p",utc_oauth2_request_set_auth_end_point_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_auth_end_point_url_n",utc_oauth2_request_set_auth_end_point_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_token_end_point_url_p",utc_oauth2_request_set_token_end_point_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_token_end_point_url_n",utc_oauth2_request_set_token_end_point_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_redirection_url_p",utc_oauth2_request_set_redirection_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_redirection_url_n",utc_oauth2_request_set_redirection_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_refresh_token_url_p",utc_oauth2_request_set_refresh_token_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_refresh_token_url_n",utc_oauth2_request_set_refresh_token_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_refresh_token_p",utc_oauth2_request_set_refresh_token_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_refresh_token_n",utc_oauth2_request_set_refresh_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_response_type_p",utc_oauth2_request_set_response_type_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_response_type_n",utc_oauth2_request_set_response_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_client_id_p",utc_oauth2_request_set_client_id_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_client_id_n",utc_oauth2_request_set_client_id_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_client_authentication_type_p",utc_oauth2_request_set_client_authentication_type_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_client_authentication_type_n",utc_oauth2_request_set_client_authentication_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_scope_p",utc_oauth2_request_set_scope_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_scope_n",utc_oauth2_request_set_scope_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_state_p",utc_oauth2_request_set_state_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_state_n",utc_oauth2_request_set_state_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_grant_type_p",utc_oauth2_request_set_grant_type_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_grant_type_n",utc_oauth2_request_set_grant_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_authorization_code_p",utc_oauth2_request_set_authorization_code_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_authorization_code_n",utc_oauth2_request_set_authorization_code_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_user_name_p",utc_oauth2_request_set_user_name_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_user_name_n",utc_oauth2_request_set_user_name_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_password_p",utc_oauth2_request_set_password_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_set_password_n",utc_oauth2_request_set_password_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_add_custom_data_p",utc_oauth2_request_add_custom_data_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_add_custom_data_n",utc_oauth2_request_add_custom_data_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_auth_end_point_url_p",utc_oauth2_request_get_auth_end_point_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_auth_end_point_url_n",utc_oauth2_request_get_auth_end_point_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_token_end_point_url_p",utc_oauth2_request_get_token_end_point_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_token_end_point_url_n",utc_oauth2_request_get_token_end_point_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_redirection_url_p",utc_oauth2_request_get_redirection_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_redirection_url_n",utc_oauth2_request_get_redirection_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_refresh_token_url_p",utc_oauth2_request_get_refresh_token_url_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_refresh_token_url_n",utc_oauth2_request_get_refresh_token_url_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_refresh_token_p",utc_oauth2_request_get_refresh_token_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_refresh_token_n",utc_oauth2_request_get_refresh_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_response_type_p",utc_oauth2_request_get_response_type_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_response_type_n",utc_oauth2_request_get_response_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_client_id_p",utc_oauth2_request_get_client_id_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_client_id_n",utc_oauth2_request_get_client_id_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_client_secret_p",utc_oauth2_request_get_client_secret_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_client_secret_n",utc_oauth2_request_get_client_secret_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_scope_p",utc_oauth2_request_get_scope_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_scope_n",utc_oauth2_request_get_scope_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_state_p",utc_oauth2_request_get_state_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_state_n",utc_oauth2_request_get_state_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_grant_type_p",utc_oauth2_request_get_grant_type_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_grant_type_n",utc_oauth2_request_get_grant_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_authorization_code_p",utc_oauth2_request_get_authorization_code_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_authorization_code_n",utc_oauth2_request_get_authorization_code_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_user_name_p",utc_oauth2_request_get_user_name_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_user_name_n",utc_oauth2_request_get_user_name_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_password_p",utc_oauth2_request_get_password_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_password_n",utc_oauth2_request_get_password_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_custom_data_p",utc_oauth2_request_get_custom_data_p,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_request_get_custom_data_n",utc_oauth2_request_get_custom_data_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_destroy_n",utc_oauth2_response_destroy_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_authorization_code_n",utc_oauth2_response_get_authorization_code_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_state_n",utc_oauth2_response_get_state_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_access_token_n",utc_oauth2_response_get_access_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_token_type_n",utc_oauth2_response_get_token_type_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_expires_in_n",utc_oauth2_response_get_expires_in_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_refresh_token_n",utc_oauth2_response_get_refresh_token_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_scope_n",utc_oauth2_response_get_scope_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_error_n",utc_oauth2_response_get_error_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_response_get_custom_data_n",utc_oauth2_response_get_custom_data_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_error_get_code_n",utc_oauth2_error_get_code_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_error_get_description_n",utc_oauth2_error_get_description_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_error_get_uri_n",utc_oauth2_error_get_uri_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{"utc_oauth2_error_get_custom_data_n",utc_oauth2_error_get_custom_data_n,utc_oauth2_startup,utc_oauth2_cleanup},
	{NULL, NULL}
};

#endif // __TCT_OAUTH2-NATIVE_H__
