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
#ifndef __TCT_HTTP-NATIVE_H__
#define __TCT_HTTP-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_http_startup(void);
extern void ITs_http_cleanup(void);
extern void ITs_http_transaction_startup(void);
extern void ITs_http_transaction_cleanup(void);

extern int ITc_http_init_deinit_p(void);
extern int ITc_http_session_create_destroy_p(void);
extern int ITc_http_session_set_get_auto_redirection_p(void);
extern int ITc_http_session_get_active_transaction_count_p(void);
extern int ITc_http_session_get_max_transaction_count_p(void);
extern int ITc_http_session_open_destroy_transaction_p(void);
extern int ITc_http_session_destroy_all_transactions_p(void);
extern int ITc_http_transaction_register_callbacks_p(void);
extern int ITc_http_transaction_set_uploaded_cb_p(void);
extern int ITc_http_transaction_set_progress_cb_p(void);
extern int ITc_http_transaction_set_get_timeout_p(void);
extern int ITc_http_transaction_set_ready_to_write_p(void);
extern int ITc_http_transaction_set_get_interface_name_p(void);
extern int ITc_http_transaction_set_get_server_certificate_verification_p(void);
extern int ITc_http_transaction_pause_resume_p(void);
extern int ITc_http_transaction_header_add_remove_field_p(void);
extern int ITc_http_transaction_request_set_get_method_p(void);
extern int ITc_http_transaction_request_set_get_version_p(void);
extern int ITc_http_transaction_request_set_get_uri_p(void);
extern int ITc_http_transaction_request_set_get_accept_encoding_p(void);
extern int ITc_http_transaction_request_set_get_cookie_p(void);
extern int ITc_http_transaction_request_write_body_p(void);
extern int ITc_http_trasaction_open_authentication_p(void);
extern int ITc_http_transaction_set_get_credentials_p(void);
extern int ITc_http_transaction_set_get_http_auth_scheme_p(void);
extern int ITc_http_transaction_get_status_code_text_version_realm_p(void);
extern int ITc_http_transaction_request_set_upload_file_cancel_p(void);
extern int ITc_http_transaction_set_get_tcp_fastopen_p(void);

testcase tc_array[] = {
	{"ITc_http_init_deinit_p",ITc_http_init_deinit_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_create_destroy_p",ITc_http_session_create_destroy_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_set_get_auto_redirection_p",ITc_http_session_set_get_auto_redirection_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_get_active_transaction_count_p",ITc_http_session_get_active_transaction_count_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_get_max_transaction_count_p",ITc_http_session_get_max_transaction_count_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_open_destroy_transaction_p",ITc_http_session_open_destroy_transaction_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_session_destroy_all_transactions_p",ITc_http_session_destroy_all_transactions_p,ITs_http_startup,ITs_http_cleanup},
	{"ITc_http_transaction_register_callbacks_p",ITc_http_transaction_register_callbacks_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_uploaded_cb_p",ITc_http_transaction_set_uploaded_cb_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_progress_cb_p",ITc_http_transaction_set_progress_cb_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_timeout_p",ITc_http_transaction_set_get_timeout_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_ready_to_write_p",ITc_http_transaction_set_ready_to_write_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_interface_name_p",ITc_http_transaction_set_get_interface_name_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_server_certificate_verification_p",ITc_http_transaction_set_get_server_certificate_verification_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_pause_resume_p",ITc_http_transaction_pause_resume_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_header_add_remove_field_p",ITc_http_transaction_header_add_remove_field_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_get_method_p",ITc_http_transaction_request_set_get_method_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_get_version_p",ITc_http_transaction_request_set_get_version_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_get_uri_p",ITc_http_transaction_request_set_get_uri_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_get_accept_encoding_p",ITc_http_transaction_request_set_get_accept_encoding_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_get_cookie_p",ITc_http_transaction_request_set_get_cookie_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_write_body_p",ITc_http_transaction_request_write_body_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_trasaction_open_authentication_p",ITc_http_trasaction_open_authentication_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_credentials_p",ITc_http_transaction_set_get_credentials_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_http_auth_scheme_p",ITc_http_transaction_set_get_http_auth_scheme_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_get_status_code_text_version_realm_p",ITc_http_transaction_get_status_code_text_version_realm_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_request_set_upload_file_cancel_p",ITc_http_transaction_request_set_upload_file_cancel_p,ITs_http_transaction_startup,ITs_http_transaction_cleanup},
	{"ITc_http_transaction_set_get_tcp_fastopen_p", ITc_http_transaction_set_get_tcp_fastopen_p, ITs_http_transaction_startup, ITs_http_transaction_cleanup},
	{NULL, NULL}
};

#endif // __TCT_HTTP-NATIVE_H__
