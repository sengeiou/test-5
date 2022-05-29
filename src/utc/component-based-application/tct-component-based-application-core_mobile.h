//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_COMPONENT_BASED_APPLICATION_NATIVE_H__
#define __TCT_COMPONENT_BASED_APPLICATION_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_component_based_application_startup(void);
extern void utc_component_based_application_cleanup(void);

extern int utc_component_based_app_main_p(void);
extern int utc_component_based_app_main_n(void);
extern int utc_component_based_app_add_frame_component_p(void);
extern int utc_component_based_app_add_frame_component_n(void);
extern int utc_component_based_app_add_service_component_p(void);
extern int utc_component_based_app_add_service_component_n(void);
extern int utc_frame_component_get_display_status_p(void);
extern int utc_frame_component_get_display_status_n(void);
extern int utc_frame_component_get_window_p(void);
extern int utc_frame_component_get_window_n(void);
extern int utc_component_register_action_p(void);
extern int utc_component_register_action_n(void);
extern int utc_component_deregister_action_p(void);
extern int utc_component_deregister_action_n(void);
extern int utc_component_send_launch_request_sync_p(void);
extern int utc_component_send_launch_request_sync_n(void);
extern int utc_component_send_launch_request_async_p(void);
extern int utc_component_send_launch_request_async_n(void);
extern int utc_component_based_app_exit_p(void);
extern int utc_component_finish_p(void);
extern int utc_component_finish_n(void);

testcase tc_array[] = {
    {"utc_component_based_app_main_p", utc_component_based_app_main_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_main_n", utc_component_based_app_main_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_add_frame_component_p", utc_component_based_app_add_frame_component_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_add_frame_component_n", utc_component_based_app_add_frame_component_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_add_service_component_p", utc_component_based_app_add_service_component_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_add_service_component_n", utc_component_based_app_add_service_component_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_frame_component_get_display_status_p", utc_frame_component_get_display_status_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_frame_component_get_display_status_n", utc_frame_component_get_display_status_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_frame_component_get_window_p", utc_frame_component_get_window_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_frame_component_get_window_n", utc_frame_component_get_window_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_register_action_p", utc_component_register_action_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_register_action_n", utc_component_register_action_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_deregister_action_p", utc_component_deregister_action_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_deregister_action_n", utc_component_deregister_action_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_send_launch_request_sync_p", utc_component_send_launch_request_sync_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
	{"utc_component_send_launch_request_sync_n", utc_component_send_launch_request_sync_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
	{"utc_component_send_launch_request_async_p", utc_component_send_launch_request_async_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
	{"utc_component_send_launch_request_async_n", utc_component_send_launch_request_async_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_based_app_exit_p", utc_component_based_app_exit_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_finish_p", utc_component_finish_p, utc_component_based_application_startup, utc_component_based_application_cleanup},
    {"utc_component_finish_n", utc_component_finish_n, utc_component_based_application_startup, utc_component_based_application_cleanup},
	{NULL, NULL}
};

#endif // __TCT_COMPONENT_BASED_APPLICATION_NATIVE_H__
