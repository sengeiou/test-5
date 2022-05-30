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
#ifndef __TCT_WIDGET_SERVICE-NATIVE_H__
#define __TCT_WIDGET_SERVICE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_widget_service_startup(void);
extern void ITs_widget_service_cleanup(void);

extern int ITc_widget_service_get_size_type_p(void);
extern int ITc_widget_service_get_size_p(void);
extern int ITc_widget_service_get_widget_list_p(void);
extern int ITc_widget_service_get_main_app_id_p(void);
extern int ITc_widget_service_get_name_p(void);
extern int ITc_widget_service_get_package_id_p(void);
extern int ITc_widget_service_get_widget_id_p(void);
extern int ITc_widget_service_get_widget_list_by_pkgid_p(void);
extern int ITc_widget_service_get_supported_sizes_p(void);
extern int ITc_widget_service_get_supported_size_types_p(void);
extern int ITc_widget_service_get_app_id_of_setup_app_p(void);
extern int ITc_widget_service_get_icon_p(void);
extern int ITc_widget_service_get_preview_image_path_p(void);
extern int ITc_widget_service_get_nodisplay_p(void);
extern int ITc_widget_service_get_need_of_mouse_event_p(void);
extern int ITc_widget_service_get_need_of_frame_p(void);
extern int ITc_widget_service_get_need_of_touch_effect_p(void);
extern int ITc_widget_service_set_unset_lifecycle_event_cb_p(void);
extern int ITc_widget_service_set_unset_disable_event_cb_p(void);
extern int ITc_widget_service_get_widget_disabled_p(void);

testcase tc_array[] = {
	{"ITc_widget_service_get_size_type_p",ITc_widget_service_get_size_type_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_size_p",ITc_widget_service_get_size_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_widget_list_p",ITc_widget_service_get_widget_list_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_main_app_id_p",ITc_widget_service_get_main_app_id_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_name_p",ITc_widget_service_get_name_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_package_id_p",ITc_widget_service_get_package_id_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_widget_id_p",ITc_widget_service_get_widget_id_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_widget_list_by_pkgid_p",ITc_widget_service_get_widget_list_by_pkgid_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_supported_sizes_p",ITc_widget_service_get_supported_sizes_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_supported_size_types_p",ITc_widget_service_get_supported_size_types_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_app_id_of_setup_app_p",ITc_widget_service_get_app_id_of_setup_app_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_icon_p",ITc_widget_service_get_icon_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_preview_image_path_p",ITc_widget_service_get_preview_image_path_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_nodisplay_p",ITc_widget_service_get_nodisplay_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_need_of_mouse_event_p",ITc_widget_service_get_need_of_mouse_event_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_need_of_frame_p",ITc_widget_service_get_need_of_frame_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_get_need_of_touch_effect_p",ITc_widget_service_get_need_of_touch_effect_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_set_unset_lifecycle_event_cb_p",ITc_widget_service_set_unset_lifecycle_event_cb_p,ITs_widget_service_startup,ITs_widget_service_cleanup},
	{"ITc_widget_service_set_unset_disable_event_cb_p", ITc_widget_service_set_unset_disable_event_cb_p,ITs_widget_service_startup, ITs_widget_service_cleanup},
	{"ITc_widget_service_get_widget_disabled_p", ITc_widget_service_get_widget_disabled_p,ITs_widget_service_startup, ITs_widget_service_cleanup},
	{NULL, NULL}
};

#endif // __TCT_WIDGET_SERVICE-NATIVE_H__
