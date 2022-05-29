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

extern void utc_appcore_widget_startup(void);
extern void utc_appcore_widget_cleanup(void);

extern int utc_appcore_widget_widget_app_main_p(void);
extern int utc_appcore_widget_widget_app_main_n1(void);
extern int utc_appcore_widget_widget_app_main_n2(void);
extern int utc_appcore_widget_widget_app_main_n3(void);
extern int utc_appcore_widget_widget_app_add_event_handler_p(void);
extern int utc_appcore_widget_widget_app_add_event_handler_n(void);
extern int utc_appcore_widget_widget_app_remove_event_handler_p(void);
extern int utc_appcore_widget_widget_app_remove_event_handler_n(void);
extern int utc_appcore_widget_widget_app_class_create_p(void);
extern int utc_appcore_widget_widget_app_class_add_p(void);
extern int utc_appcore_widget_widget_app_class_add_n(void);
extern int utc_appcore_widget_widget_app_exit_p(void);
extern int utc_appcore_widget_widget_app_terminate_context_n(void);
extern int utc_appcore_widget_widget_app_foreach_context_p(void);
extern int utc_appcore_widget_widget_app_foreach_context_n(void);
extern int utc_appcore_widget_widget_app_get_id_n(void);
extern int utc_appcore_widget_widget_app_context_set_tag_n(void);
extern int utc_appcore_widget_widget_app_context_get_tag_n1(void);
extern int utc_appcore_widget_widget_app_context_get_tag_n2(void);
extern int utc_appcore_widget_widget_app_context_set_content_info_n(void);
extern int utc_appcore_widget_widget_app_context_set_title_n(void);
extern int utc_appcore_widget_widget_app_get_elm_win_n(void);

testcase tc_array[] = {
	{"utc_appcore_widget_widget_app_main_p",utc_appcore_widget_widget_app_main_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_main_n1",utc_appcore_widget_widget_app_main_n1,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_main_n2",utc_appcore_widget_widget_app_main_n2,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_main_n3",utc_appcore_widget_widget_app_main_n3,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_add_event_handler_p",utc_appcore_widget_widget_app_add_event_handler_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_add_event_handler_n",utc_appcore_widget_widget_app_add_event_handler_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_remove_event_handler_p",utc_appcore_widget_widget_app_remove_event_handler_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_remove_event_handler_n",utc_appcore_widget_widget_app_remove_event_handler_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_class_create_p",utc_appcore_widget_widget_app_class_create_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_class_add_p",utc_appcore_widget_widget_app_class_add_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_class_add_n",utc_appcore_widget_widget_app_class_add_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_exit_p",utc_appcore_widget_widget_app_exit_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_terminate_context_n",utc_appcore_widget_widget_app_terminate_context_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_foreach_context_p",utc_appcore_widget_widget_app_foreach_context_p,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_foreach_context_n",utc_appcore_widget_widget_app_foreach_context_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_get_id_n",utc_appcore_widget_widget_app_get_id_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_context_set_tag_n",utc_appcore_widget_widget_app_context_set_tag_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_context_get_tag_n1",utc_appcore_widget_widget_app_context_get_tag_n1,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_context_get_tag_n2",utc_appcore_widget_widget_app_context_get_tag_n2,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_context_set_content_info_n",utc_appcore_widget_widget_app_context_set_content_info_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_context_set_title_n",utc_appcore_widget_widget_app_context_set_title_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{"utc_appcore_widget_widget_app_get_elm_win_n",utc_appcore_widget_widget_app_get_elm_win_n,utc_appcore_widget_startup,utc_appcore_widget_cleanup},
	{NULL, NULL}
};

#endif // __TCT_APPCORE-WIDGET-NATIVE_H__
