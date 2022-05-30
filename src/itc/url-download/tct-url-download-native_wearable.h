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
#ifndef __TCT_URL-DOWNLOAD-NATIVE_H__
#define __TCT_URL-DOWNLOAD-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_url_download_startup(void);
extern void ITs_url_download_cleanup(void);
extern void ITs_url_download_set_get_startup(void);
extern void ITs_url_download_set_get_cleanup(void);
extern void ITs_url_download_get_startup(void);
extern void ITs_url_download_get_cleanup(void);

extern int ITc_download_create_destroy_p(void);
extern int ITc_download_add_remove_http_header_field_p(void);
extern int ITc_download_set_unset_progress_cb_p(void);
extern int ITc_download_start_cancel_p(void);
extern int ITc_download_pause_p(void);
extern int ITc_download_set_temp_file_path_p(void);
extern int ITc_download_set_get_notification_app_control_p(void);
extern int ITc_download_set_get_auto_download_p(void);
extern int ITc_download_set_get_destination_p(void);
extern int ITc_download_set_get_file_name_p(void);
extern int ITc_download_set_get_network_type_p(void);
extern int ITc_download_set_get_notification_description_p(void);
extern int ITc_download_set_get_notification_title_p(void);
extern int ITc_download_set_get_notification_type_p(void);
extern int ITc_download_set_get_url_p(void);
extern int ITc_download_set_get_state_changed_cb_p(void);
extern int ITc_download_get_http_header_field_p(void);
extern int ITc_download_get_http_header_field_list_p(void);
extern int ITc_download_get_temp_path_p(void);
extern int ITc_download_get_content_name_p(void);
extern int ITc_download_get_content_size_p(void);
extern int ITc_download_get_downloaded_file_path_p(void);
extern int ITc_download_get_etag_p(void);
extern int ITc_download_get_http_status_p(void);
extern int ITc_download_get_mime_type_p(void);
extern int ITc_download_get_state_p(void);
extern int ITc_download_get_error_p(void);

testcase tc_array[] = {
	{"ITc_download_create_destroy_p",ITc_download_create_destroy_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_add_remove_http_header_field_p",ITc_download_add_remove_http_header_field_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_set_unset_progress_cb_p",ITc_download_set_unset_progress_cb_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_start_cancel_p",ITc_download_start_cancel_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_pause_p",ITc_download_pause_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_set_temp_file_path_p",ITc_download_set_temp_file_path_p,ITs_url_download_startup,ITs_url_download_cleanup},
	{"ITc_download_set_get_notification_app_control_p",ITc_download_set_get_notification_app_control_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_auto_download_p",ITc_download_set_get_auto_download_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_destination_p",ITc_download_set_get_destination_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_file_name_p",ITc_download_set_get_file_name_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_network_type_p",ITc_download_set_get_network_type_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_notification_description_p",ITc_download_set_get_notification_description_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_notification_title_p",ITc_download_set_get_notification_title_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_notification_type_p",ITc_download_set_get_notification_type_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_url_p",ITc_download_set_get_url_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_set_get_state_changed_cb_p",ITc_download_set_get_state_changed_cb_p,ITs_url_download_set_get_startup,ITs_url_download_set_get_cleanup},
	{"ITc_download_get_http_header_field_p",ITc_download_get_http_header_field_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_http_header_field_list_p",ITc_download_get_http_header_field_list_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_temp_path_p",ITc_download_get_temp_path_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_content_name_p",ITc_download_get_content_name_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_content_size_p",ITc_download_get_content_size_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_downloaded_file_path_p",ITc_download_get_downloaded_file_path_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_etag_p",ITc_download_get_etag_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_http_status_p",ITc_download_get_http_status_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_mime_type_p",ITc_download_get_mime_type_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_state_p",ITc_download_get_state_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{"ITc_download_get_error_p",ITc_download_get_error_p,ITs_url_download_get_startup,ITs_url_download_get_cleanup},
	{NULL, NULL}
};

#endif // __TCT_URL-DOWNLOAD-NATIVE_H__
