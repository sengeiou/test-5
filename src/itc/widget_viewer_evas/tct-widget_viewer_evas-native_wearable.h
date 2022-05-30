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
#ifndef __TCT_WIDGET_VIEWER_EVAS-NATIVE_H__
#define __TCT_WIDGET_VIEWER_EVAS-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_widget_viewer_evas_startup(void);
extern void ITs_widget_viewer_evas_cleanup(void);

extern int ITc_widget_viewer_evas_get_widget_id_p(void);
extern int ITc_widget_viewer_evas_get_period_p(void);
extern int ITc_widget_viewer_evas_is_visibility_frozen_p(void);
extern int ITc_widget_viewer_evas_is_widget_p(void);
extern int ITc_widget_viewer_evas_is_faulted_p(void);
extern int ITc_widget_viewer_evas_notify_resumed_status_of_viewer_p(void);
extern int ITc_widget_viewer_evas_notify_paused_status_of_viewer_p(void);
extern int ITc_widget_viewer_evas_pause_widget_p(void);
extern int ITc_widget_viewer_evas_resume_widget_p(void);
extern int ITc_widget_viewer_evas_feed_mouse_up_event_p(void);
extern int ITc_widget_viewer_evas_thaw_visibility_p(void);
extern int ITc_widget_viewer_evas_get_title_string_p(void);
extern int ITc_widget_viewer_evas_freeze_visibility_p(void);
extern int ITc_widget_viewer_evas_set_option_p(void);
extern int ITc_widget_viewer_evas_notify_orientation_of_viewer_p(void);
extern int ITc_widget_viewer_evas_cancel_click_event_p(void);
extern int ITc_widget_viewer_evas_set_permanent_delete_p(void);
extern int ITc_widget_viewer_evas_disable_preview_p(void);
extern int ITc_widget_viewer_evas_disable_overlay_text_p(void);
extern int ITc_widget_viewer_evas_disable_loading_p(void);
extern int ITc_widget_viewer_evas_add_widget_p(void);
extern int ITc_widget_viewer_evas_activate_faulted_widget_p(void);
extern int ITc_widget_viewer_evas_get_content_info_p(void);
extern int ITc_widget_viewer_evas_get_widget_instance_id_p(void);

testcase tc_array[] = {
	{"ITc_widget_viewer_evas_get_widget_id_p",ITc_widget_viewer_evas_get_widget_id_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_get_period_p",ITc_widget_viewer_evas_get_period_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_is_visibility_frozen_p",ITc_widget_viewer_evas_is_visibility_frozen_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_is_widget_p",ITc_widget_viewer_evas_is_widget_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_is_faulted_p",ITc_widget_viewer_evas_is_faulted_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_notify_resumed_status_of_viewer_p",ITc_widget_viewer_evas_notify_resumed_status_of_viewer_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_notify_paused_status_of_viewer_p",ITc_widget_viewer_evas_notify_paused_status_of_viewer_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_pause_widget_p",ITc_widget_viewer_evas_pause_widget_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_resume_widget_p",ITc_widget_viewer_evas_resume_widget_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_feed_mouse_up_event_p",ITc_widget_viewer_evas_feed_mouse_up_event_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_thaw_visibility_p",ITc_widget_viewer_evas_thaw_visibility_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_get_title_string_p",ITc_widget_viewer_evas_get_title_string_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_freeze_visibility_p",ITc_widget_viewer_evas_freeze_visibility_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_set_option_p",ITc_widget_viewer_evas_set_option_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_notify_orientation_of_viewer_p",ITc_widget_viewer_evas_notify_orientation_of_viewer_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_cancel_click_event_p",ITc_widget_viewer_evas_cancel_click_event_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_set_permanent_delete_p",ITc_widget_viewer_evas_set_permanent_delete_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_disable_preview_p",ITc_widget_viewer_evas_disable_preview_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_disable_overlay_text_p",ITc_widget_viewer_evas_disable_overlay_text_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_disable_loading_p",ITc_widget_viewer_evas_disable_loading_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_add_widget_p",ITc_widget_viewer_evas_add_widget_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_activate_faulted_widget_p",ITc_widget_viewer_evas_activate_faulted_widget_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_get_content_info_p",ITc_widget_viewer_evas_get_content_info_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{"ITc_widget_viewer_evas_get_widget_instance_id_p",ITc_widget_viewer_evas_get_widget_instance_id_p,ITs_widget_viewer_evas_startup,ITs_widget_viewer_evas_cleanup},
	{NULL, NULL}
};

#endif // __TCT_WIDGET_VIEWER_EVAS-NATIVE_H__
