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

extern void ITs_componenet_based_app_startup(void);
extern void ITs_componenet_based_app_cleanup(void);

extern int ITc_component_based_app_main_p(void);
extern int ITc_component_based_app_exit_p(void);
extern int ITc_component_based_app_add_frame_component_p(void);
extern int ITc_component_based_app_add_service_component_p(void);
extern int ITc_component_get_id_p(void);
extern int ITc_component_get_instance_id_p(void);
extern int ITc_component_register_action_p(void);
extern int ITc_component_deregister_action_p(void);
extern int ITc_component_send_launch_request_sync_p(void);
extern int ITc_component_send_launch_request_async_p(void);
extern int ITc_frame_component_get_display_status_p(void);
extern int ITc_frame_component_get_window_p(void);
extern int ITc_component_finish_p(void);

testcase tc_array[] = {
	{"ITc_component_based_app_main_p", ITc_component_based_app_main_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_based_app_exit_p", ITc_component_based_app_exit_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_based_app_add_frame_component_p", ITc_component_based_app_add_frame_component_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_based_app_add_service_component_p", ITc_component_based_app_add_service_component_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_get_id_p", ITc_component_get_id_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_get_instance_id_p", ITc_component_get_instance_id_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_register_action_p", ITc_component_register_action_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_deregister_action_p", ITc_component_deregister_action_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_send_launch_request_sync_p", ITc_component_send_launch_request_sync_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_send_launch_request_async_p", ITc_component_send_launch_request_async_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_frame_component_get_display_status_p", ITc_frame_component_get_display_status_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_frame_component_get_window_p", ITc_frame_component_get_window_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{"ITc_component_finish_p", ITc_component_finish_p, ITs_componenet_based_app_startup, ITs_componenet_based_app_cleanup},
	{NULL, NULL}
};

#endif // __TCT_COMPONENT_BASED_APPLICATION_NATIVE_H__
