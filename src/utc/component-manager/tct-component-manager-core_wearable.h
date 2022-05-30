/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TCT_COMPONENT_MANAGER_NATIVE_H__
#define __TCT_COMPONENT_MANAGER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_component_context_clone_p_startup(void);
extern void utc_component_context_clone_p_cleanup(void);
extern int utc_component_context_clone_p(void);
extern int utc_component_context_clone_n(void);

extern void utc_component_context_destroy_p_startup(void);
extern int utc_component_context_destroy_p(void);
extern int utc_component_context_destroy_n(void);

extern void utc_component_context_get_app_id_p_startup(void);
extern void utc_component_context_get_app_id_p_cleanup(void);
extern int utc_component_context_get_app_id_p(void);
extern int utc_component_context_get_app_id_n(void);

extern void utc_component_context_get_component_id_p_startup(void);
extern void utc_component_context_get_component_id_p_cleanup(void);
extern int utc_component_context_get_component_id_p(void);
extern int utc_component_context_get_component_id_n(void);

extern void utc_component_context_get_component_state_p_startup(void);
extern void utc_component_context_get_component_state_p_cleanup(void);
extern int utc_component_context_get_component_state_p(void);
extern int utc_component_context_get_component_state_n(void);

extern void utc_component_context_get_instance_id_p_startup(void);
extern void utc_component_context_get_instance_id_p_cleanup(void);
extern int utc_component_context_get_instance_id_p(void);
extern int utc_component_context_get_instance_id_n(void);

extern void utc_component_context_is_subcomponent_p_startup(void);
extern void utc_component_context_is_subcomponent_p_cleanup(void);
extern int utc_component_context_is_subcomponent_p(void);
extern int utc_component_context_is_subcomponent_n(void);

extern void utc_component_context_is_terminated_p_startup(void);
extern void utc_component_context_is_terminated_p_cleanup(void);
extern int utc_component_context_is_terminated_p(void);
extern int utc_component_context_is_terminated_n(void);

extern void utc_component_info_clone_p_startup(void);
extern void utc_component_info_clone_p_cleanup(void);
extern int utc_component_info_clone_p(void);
extern int utc_component_info_clone_n(void);

extern void utc_component_info_create_p_startup(void);
extern void utc_component_info_create_p_cleanup(void);
extern int utc_component_info_create_p(void);
extern int utc_component_info_create_n(void);

extern void utc_component_info_destroy_p_startup(void);
extern int utc_component_info_destroy_p(void);
extern int utc_component_info_destroy_n(void);

extern void utc_component_info_get_app_id_p_startup(void);
extern void utc_component_info_get_app_id_p_cleanup(void);
extern int utc_component_info_get_app_id_p(void);
extern int utc_component_info_get_app_id_n(void);

extern void utc_component_info_get_component_id_p_startup(void);
extern void utc_component_info_get_component_id_p_cleanup(void);
extern int utc_component_info_get_component_id_p(void);
extern int utc_component_info_get_component_id_n(void);

extern void utc_component_info_get_component_type_p_startup(void);
extern void utc_component_info_get_component_type_p_cleanup(void);
extern int utc_component_info_get_component_type_p(void);
extern int utc_component_info_get_component_type_n(void);

extern void utc_component_info_get_icon_p_startup(void);
extern void utc_component_info_get_icon_p_cleanup(void);
extern int utc_component_info_get_icon_p(void);
extern int utc_component_info_get_icon_n(void);

extern void utc_component_info_get_label_p_startup(void);
extern void utc_component_info_get_label_p_cleanup(void);
extern int utc_component_info_get_label_p(void);
extern int utc_component_info_get_label_n(void);

extern void utc_component_info_get_localized_label_p_startup(void);
extern void utc_component_info_get_localized_label_p_cleanup(void);
extern int utc_component_info_get_localized_label_p(void);
extern int utc_component_info_get_localized_label_n(void);

extern void utc_component_info_is_icon_display_p_startup(void);
extern void utc_component_info_is_icon_display_p_cleanup(void);
extern int utc_component_info_is_icon_display_p(void);
extern int utc_component_info_is_icon_display_n(void);

extern void utc_component_info_is_managed_by_task_manager_p_startup(void);
extern void utc_component_info_is_managed_by_task_manager_p_cleanup(void);
extern int utc_component_info_is_managed_by_task_manager_p(void);
extern int utc_component_info_is_managed_by_task_manager_n(void);

extern void utc_component_manager_is_running_p_startup(void);
extern int utc_component_manager_is_running_p(void);
extern int utc_component_manager_is_running_n(void);

extern void utc_component_manager_foreach_component_info_p_startup(void);
extern int utc_component_manager_foreach_component_info_p(void);
extern int utc_component_manager_foreach_component_info_n(void);

extern void utc_component_manager_get_component_context_p_startup(void);
extern int utc_component_manager_get_component_context_p(void);
extern int utc_component_manager_get_component_context_n(void);

extern void utc_component_manager_get_component_info_p_startup(void);
extern int utc_component_manager_get_component_info_p(void);
extern int utc_component_manager_get_component_info_n(void);

extern void utc_component_manager_foreach_component_context_p_startup(void);
extern int utc_component_manager_foreach_component_context_p(void);
extern int utc_component_manager_foreach_component_context_n(void);

extern void utc_component_manager_resume_component_p_startup(void);
extern void utc_component_manager_resume_component_p_cleanup(void);
extern int utc_component_manager_resume_component_p(void);
extern int utc_component_manager_resume_component_n(void);

extern void utc_component_manager_terminate_bg_component_p_startup(void);
extern void utc_component_manager_terminate_bg_component_p_cleanup(void);
extern int utc_component_manager_terminate_bg_component_p(void);
extern int utc_component_manager_terminate_bg_component_n(void);

testcase tc_array[] = {
    {"utc_component_context_clone_p", utc_component_context_clone_p, utc_component_context_clone_p_startup, utc_component_context_clone_p_cleanup},
    {"utc_component_context_clone_n", utc_component_context_clone_n, NULL, NULL},
    {"utc_component_context_destroy_p", utc_component_context_destroy_p, utc_component_context_destroy_p_startup, NULL},
    {"utc_component_context_destroy_n", utc_component_context_destroy_n, NULL, NULL},
    {"utc_component_context_get_app_id_p", utc_component_context_get_app_id_p, utc_component_context_get_app_id_p_startup, utc_component_context_get_app_id_p_cleanup},
    {"utc_component_context_get_app_id_n", utc_component_context_get_app_id_n, NULL, NULL},
    {"utc_component_context_get_component_id_p", utc_component_context_get_component_id_p, utc_component_context_get_component_id_p_startup, utc_component_context_get_component_id_p_cleanup},
    {"utc_component_context_get_component_id_n", utc_component_context_get_component_id_n, NULL, NULL},
    {"utc_component_context_get_component_state_p", utc_component_context_get_component_state_p, utc_component_context_get_component_state_p_startup, utc_component_context_get_component_state_p_cleanup},
    {"utc_component_context_get_component_state_n", utc_component_context_get_component_state_n, NULL, NULL},
    {"utc_component_context_get_instance_id_p", utc_component_context_get_instance_id_p, utc_component_context_get_instance_id_p_startup, utc_component_context_get_instance_id_p_cleanup},
    {"utc_component_context_get_instance_id_n", utc_component_context_get_instance_id_n, NULL, NULL},
    {"utc_component_context_is_subcomponent_p", utc_component_context_is_subcomponent_p, utc_component_context_is_subcomponent_p_startup, utc_component_context_is_subcomponent_p_cleanup},
    {"utc_component_context_is_subcomponent_n", utc_component_context_is_subcomponent_n, NULL, NULL},
    {"utc_component_context_is_terminated_p", utc_component_context_is_terminated_p, utc_component_context_is_terminated_p_startup, utc_component_context_is_terminated_p_cleanup},
    {"utc_component_context_is_terminated_n", utc_component_context_is_terminated_n, NULL, NULL},
    {"utc_component_info_clone_p", utc_component_info_clone_p, utc_component_info_clone_p_startup, utc_component_info_clone_p_cleanup},
    {"utc_component_info_clone_n", utc_component_info_clone_n, NULL, NULL},
    {"utc_component_info_create_p", utc_component_info_create_p, utc_component_info_create_p_startup, utc_component_info_create_p_cleanup},
    {"utc_component_info_create_n", utc_component_info_create_n, NULL, NULL},
    {"utc_component_info_destroy_p", utc_component_info_destroy_p, utc_component_info_destroy_p_startup, NULL},
    {"utc_component_info_destroy_n", utc_component_info_destroy_n, NULL, NULL},
    {"utc_component_info_get_app_id_p", utc_component_info_get_app_id_p, utc_component_info_get_app_id_p_startup, utc_component_info_get_app_id_p_cleanup},
    {"utc_component_info_get_app_id_n", utc_component_info_get_app_id_n, NULL, NULL},
    {"utc_component_info_get_component_id_p", utc_component_info_get_component_id_p, utc_component_info_get_component_id_p_startup, utc_component_info_get_component_id_p_cleanup},
    {"utc_component_info_get_component_id_n", utc_component_info_get_component_id_n, NULL, NULL},
    {"utc_component_info_get_component_type_p", utc_component_info_get_component_type_p, utc_component_info_get_component_type_p_startup, utc_component_info_get_component_type_p_cleanup},
    {"utc_component_info_get_component_type_n", utc_component_info_get_component_type_n, NULL, NULL},
    {"utc_component_info_get_icon_p", utc_component_info_get_icon_p, utc_component_info_get_icon_p_startup, utc_component_info_get_icon_p_cleanup},
    {"utc_component_info_get_icon_n", utc_component_info_get_icon_n, NULL, NULL},
    {"utc_component_info_get_label_p", utc_component_info_get_label_p, utc_component_info_get_label_p_startup, utc_component_info_get_label_p_cleanup},
    {"utc_component_info_get_label_n", utc_component_info_get_label_n, NULL, NULL},
    {"utc_component_info_get_localized_label_p", utc_component_info_get_localized_label_p, utc_component_info_get_localized_label_p_startup, utc_component_info_get_localized_label_p_cleanup},
    {"utc_component_info_get_localized_label_n", utc_component_info_get_localized_label_n, NULL, NULL},
    {"utc_component_info_is_icon_display_p", utc_component_info_is_icon_display_p, utc_component_info_is_icon_display_p_startup, utc_component_info_is_icon_display_p_cleanup},
    {"utc_component_info_is_icon_display_n", utc_component_info_is_icon_display_n, NULL, NULL},
    {"utc_component_info_clone_p", utc_component_info_clone_p, utc_component_info_clone_p_startup, utc_component_info_clone_p_cleanup},
    {"utc_component_info_clone_n", utc_component_info_clone_n, NULL, NULL},
    {"utc_component_info_create_p", utc_component_info_create_p, utc_component_info_create_p_startup, utc_component_info_create_p_cleanup},
    {"utc_component_info_create_n", utc_component_info_create_n, NULL, NULL},
    {"utc_component_info_destroy_p", utc_component_info_destroy_p, utc_component_info_destroy_p_startup, NULL},
    {"utc_component_info_destroy_n", utc_component_info_destroy_n, NULL, NULL},
    {"utc_component_info_get_app_id_p", utc_component_info_get_app_id_p, utc_component_info_get_app_id_p_startup, utc_component_info_get_app_id_p_cleanup},
    {"utc_component_info_get_app_id_n", utc_component_info_get_app_id_n, NULL, NULL},
    {"utc_component_info_get_component_id_p", utc_component_info_get_component_id_p, utc_component_info_get_component_id_p_startup, utc_component_info_get_component_id_p_cleanup},
    {"utc_component_info_get_component_id_n", utc_component_info_get_component_id_n, NULL, NULL},
    {"utc_component_info_get_component_type_p", utc_component_info_get_component_type_p, utc_component_info_get_component_type_p_startup, utc_component_info_get_component_type_p_cleanup},
    {"utc_component_info_get_component_type_n", utc_component_info_get_component_type_n, NULL, NULL},
    {"utc_component_info_get_icon_p", utc_component_info_get_icon_p, utc_component_info_get_icon_p_startup, utc_component_info_get_icon_p_cleanup},
    {"utc_component_info_get_icon_n", utc_component_info_get_icon_n, NULL, NULL},
    {"utc_component_info_get_label_p", utc_component_info_get_label_p, utc_component_info_get_label_p_startup, utc_component_info_get_label_p_cleanup},
    {"utc_component_info_get_label_n", utc_component_info_get_label_n, NULL, NULL},
    {"utc_component_info_get_localized_label_p", utc_component_info_get_localized_label_p, utc_component_info_get_localized_label_p_startup, utc_component_info_get_localized_label_p_cleanup},
    {"utc_component_info_get_localized_label_n", utc_component_info_get_localized_label_n, NULL, NULL},
    {"utc_component_info_is_icon_display_p", utc_component_info_is_icon_display_p, utc_component_info_is_icon_display_p_startup, utc_component_info_is_icon_display_p_cleanup},
    {"utc_component_info_is_icon_display_n", utc_component_info_is_icon_display_n, NULL, NULL},
    {"utc_component_info_clone_p", utc_component_info_clone_p, utc_component_info_clone_p_startup, utc_component_info_clone_p_cleanup},
    {"utc_component_info_clone_n", utc_component_info_clone_n, NULL, NULL},
    {"utc_component_info_create_p", utc_component_info_create_p, utc_component_info_create_p_startup, utc_component_info_create_p_cleanup},
    {"utc_component_info_create_n", utc_component_info_create_n, NULL, NULL},
    {"utc_component_info_destroy_p", utc_component_info_destroy_p, utc_component_info_destroy_p_startup, NULL},
    {"utc_component_info_destroy_n", utc_component_info_destroy_n, NULL, NULL},
    {"utc_component_info_get_app_id_p", utc_component_info_get_app_id_p, utc_component_info_get_app_id_p_startup, utc_component_info_get_app_id_p_cleanup},
    {"utc_component_info_get_app_id_n", utc_component_info_get_app_id_n, NULL, NULL},
    {"utc_component_info_get_component_id_p", utc_component_info_get_component_id_p, utc_component_info_get_component_id_p_startup, utc_component_info_get_component_id_p_cleanup},
    {"utc_component_info_get_component_id_n", utc_component_info_get_component_id_n, NULL, NULL},
    {"utc_component_info_get_component_type_p", utc_component_info_get_component_type_p, utc_component_info_get_component_type_p_startup, utc_component_info_get_component_type_p_cleanup},
    {"utc_component_info_get_component_type_n", utc_component_info_get_component_type_n, NULL, NULL},
    {"utc_component_info_get_icon_p", utc_component_info_get_icon_p, utc_component_info_get_icon_p_startup, utc_component_info_get_icon_p_cleanup},
    {"utc_component_info_get_icon_n", utc_component_info_get_icon_n, NULL, NULL},
    {"utc_component_info_get_label_p", utc_component_info_get_label_p, utc_component_info_get_label_p_startup, utc_component_info_get_label_p_cleanup},
    {"utc_component_info_get_label_n", utc_component_info_get_label_n, NULL, NULL},
    {"utc_component_info_get_localized_label_p", utc_component_info_get_localized_label_p, utc_component_info_get_localized_label_p_startup, utc_component_info_get_localized_label_p_cleanup},
    {"utc_component_info_get_localized_label_n", utc_component_info_get_localized_label_n, NULL, NULL},
    {"utc_component_info_is_icon_display_p", utc_component_info_is_icon_display_p, utc_component_info_is_icon_display_p_startup, utc_component_info_is_icon_display_p_cleanup},
    {"utc_component_info_is_icon_display_n", utc_component_info_is_icon_display_n, NULL, NULL},
    {"utc_component_info_is_managed_by_task_manager_p", utc_component_info_is_managed_by_task_manager_p, utc_component_info_is_managed_by_task_manager_p_startup, utc_component_info_is_managed_by_task_manager_p_cleanup},
    {"utc_component_info_is_managed_by_task_manager_n", utc_component_info_is_managed_by_task_manager_n, NULL, NULL},
    {"utc_component_manager_is_running_p", utc_component_manager_is_running_p, utc_component_manager_is_running_p_startup, NULL},
    {"utc_component_manager_is_running_n", utc_component_manager_is_running_n, NULL, NULL},
    {"utc_component_manager_foreach_component_info_p", utc_component_manager_foreach_component_info_p, utc_component_manager_foreach_component_info_p_startup, NULL},
    {"utc_component_manager_foreach_component_info_n", utc_component_manager_foreach_component_info_n, NULL, NULL},
    {"utc_component_manager_get_component_context_p", utc_component_manager_get_component_context_p, utc_component_manager_get_component_context_p_startup, NULL},
    {"utc_component_manager_get_component_context_n", utc_component_manager_get_component_context_n, NULL, NULL},
    {"utc_component_manager_get_component_info_p", utc_component_manager_get_component_info_p, utc_component_manager_get_component_info_p_startup, NULL},
    {"utc_component_manager_get_component_info_n", utc_component_manager_get_component_info_n, NULL, NULL},
    {"utc_component_manager_foreach_component_context_p", utc_component_manager_foreach_component_context_p, utc_component_manager_foreach_component_context_p_startup, NULL},
    {"utc_component_manager_foreach_component_context_n", utc_component_manager_foreach_component_context_n, NULL, NULL},
    {"utc_component_manager_resume_component_p", utc_component_manager_resume_component_p, utc_component_manager_resume_component_p_startup, utc_component_manager_resume_component_p_cleanup},
    {"utc_component_manager_resume_component_n", utc_component_manager_resume_component_n, NULL, NULL},
    {"utc_component_manager_terminate_bg_component_p", utc_component_manager_terminate_bg_component_p, utc_component_manager_terminate_bg_component_p_startup, utc_component_manager_terminate_bg_component_p_cleanup},
    {"utc_component_manager_terminate_bg_component_n", utc_component_manager_terminate_bg_component_n, NULL, NULL},
    {NULL, NULL}
};

#endif // __TCT_COMPONENT_MANAGER_NATIVE_H__
