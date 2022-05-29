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
#ifndef __TCT_APPCORE-WIDGET-NATIVE_H__
#define __TCT_APPCORE-WIDGET-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_appcore_widget_startup(void);
extern void ITs_appcore_widget_cleanup(void);

extern int ITc_appcore_widget_widget_app_main_exit_p(void);
extern int ITc_appcore_widget_widget_app_add_remove_event_handler_p(void);
extern int ITc_appcore_widget_widget_app_class_create_p(void);
extern int ITc_appcore_widget_widget_app_foreach_context_p(void);
extern int ITc_appcore_widget_widget_app_class_add_p(void);

testcase tc_array[] = {
	{"ITc_appcore_widget_widget_app_main_exit_p",ITc_appcore_widget_widget_app_main_exit_p,ITs_appcore_widget_startup,ITs_appcore_widget_cleanup},
	{"ITc_appcore_widget_widget_app_add_remove_event_handler_p",ITc_appcore_widget_widget_app_add_remove_event_handler_p,ITs_appcore_widget_startup,ITs_appcore_widget_cleanup},
	{"ITc_appcore_widget_widget_app_class_create_p",ITc_appcore_widget_widget_app_class_create_p,ITs_appcore_widget_startup,ITs_appcore_widget_cleanup},
	{"ITc_appcore_widget_widget_app_foreach_context_p",ITc_appcore_widget_widget_app_foreach_context_p,ITs_appcore_widget_startup,ITs_appcore_widget_cleanup},
	{"ITc_appcore_widget_widget_app_class_add_p",ITc_appcore_widget_widget_app_class_add_p,ITs_appcore_widget_startup,ITs_appcore_widget_cleanup},
	{NULL, NULL}
};

#endif // __TCT_APPCORE-WIDGET-NATIVE_H__
