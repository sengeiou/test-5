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
#ifndef __TCT_SOUND_POOL_NATIVE_H__
#define __TCT_SOUND_POOL_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_sound_pool_startup(void);
extern void utc_sound_pool_cleanup(void);

extern int utc_sound_pool_create_p(void);
extern int utc_sound_pool_create_n(void);
extern int utc_sound_pool_create_n2(void);
extern int utc_sound_pool_destroy_p(void);
extern int utc_sound_pool_destroy_n(void);
extern int utc_sound_pool_load_source_from_file_p(void);
extern int utc_sound_pool_load_source_from_file_p2(void);
extern int utc_sound_pool_load_source_from_file_n(void);
extern int utc_sound_pool_unload_source_p(void);
extern int utc_sound_pool_unload_source_n(void);
extern int utc_sound_pool_get_state_p(void);
extern int utc_sound_pool_get_state_n(void);
extern int utc_sound_pool_activate_p(void);
extern int utc_sound_pool_activate_n(void);
extern int utc_sound_pool_deactivate_p(void);
extern int utc_sound_pool_deactivate_n(void);
extern int utc_sound_pool_set_volume_p(void);
extern int utc_sound_pool_set_volume_n(void);
extern int utc_sound_pool_get_volume_p(void);
extern int utc_sound_pool_get_volume_n(void);
extern int utc_sound_pool_set_state_changed_cb_p(void);
extern int utc_sound_pool_set_state_changed_cb_n(void);
extern int utc_sound_pool_unset_state_changed_cb_p(void);
extern int utc_sound_pool_unset_state_changed_cb_n(void);
extern int utc_sound_pool_stream_play_p(void);
extern int utc_sound_pool_stream_play_p2(void);
extern int utc_sound_pool_stream_play_p3(void);
extern int utc_sound_pool_stream_play_n(void);
extern int utc_sound_pool_stream_pause_p(void);
extern int utc_sound_pool_stream_pause_p2(void);
extern int utc_sound_pool_stream_pause_n(void);
extern int utc_sound_pool_stream_resume_p(void);
extern int utc_sound_pool_stream_resume_p2(void);
extern int utc_sound_pool_stream_resume_n(void);
extern int utc_sound_pool_stream_stop_p(void);
extern int utc_sound_pool_stream_stop_n(void);
extern int utc_sound_pool_stream_stop_n2(void);
extern int utc_sound_pool_stream_set_volume_p(void);
extern int utc_sound_pool_stream_set_volume_n(void);
extern int utc_sound_pool_stream_get_volume_p(void);
extern int utc_sound_pool_stream_get_volume_n(void);
extern int utc_sound_pool_stream_set_priority_p(void);
extern int utc_sound_pool_stream_set_priority_n(void);
extern int utc_sound_pool_stream_get_priority_p(void);
extern int utc_sound_pool_stream_get_priority_n(void);
extern int utc_sound_pool_stream_get_state_p(void);
extern int utc_sound_pool_stream_get_state_n(void);

testcase tc_array[] = {
    {"utc_sound_pool_create_p", utc_sound_pool_create_p, NULL, NULL},
    {"utc_sound_pool_create_n", utc_sound_pool_create_n, NULL, NULL},
    {"utc_sound_pool_create_n2", utc_sound_pool_create_n2, NULL, utc_sound_pool_cleanup},
    {"utc_sound_pool_destroy_p", utc_sound_pool_destroy_p, NULL, NULL},
    {"utc_sound_pool_destroy_n", utc_sound_pool_destroy_n, NULL, utc_sound_pool_cleanup},
    {"utc_sound_pool_load_source_from_file_p", utc_sound_pool_load_source_from_file_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_load_source_from_file_p2", utc_sound_pool_load_source_from_file_p2, NULL, utc_sound_pool_cleanup},
    {"utc_sound_pool_load_source_from_file_n", utc_sound_pool_load_source_from_file_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_unload_source_p", utc_sound_pool_unload_source_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_unload_source_n", utc_sound_pool_unload_source_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_get_state_p", utc_sound_pool_get_state_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_get_state_n", utc_sound_pool_get_state_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_activate_p", utc_sound_pool_activate_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_activate_n", utc_sound_pool_activate_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_deactivate_p", utc_sound_pool_deactivate_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_deactivate_n", utc_sound_pool_deactivate_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_set_volume_p", utc_sound_pool_set_volume_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_set_volume_n", utc_sound_pool_set_volume_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_get_volume_p", utc_sound_pool_get_volume_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_get_volume_n", utc_sound_pool_get_volume_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_set_state_changed_cb_p", utc_sound_pool_set_state_changed_cb_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_set_state_changed_cb_n", utc_sound_pool_set_state_changed_cb_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_unset_state_changed_cb_p", utc_sound_pool_unset_state_changed_cb_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_unset_state_changed_cb_n", utc_sound_pool_unset_state_changed_cb_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_play_p", utc_sound_pool_stream_play_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_play_p2", utc_sound_pool_stream_play_p2, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_play_p3", utc_sound_pool_stream_play_p3, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_play_n", utc_sound_pool_stream_play_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_pause_p", utc_sound_pool_stream_pause_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_pause_p2", utc_sound_pool_stream_pause_p2, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_pause_n", utc_sound_pool_stream_pause_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_resume_p", utc_sound_pool_stream_resume_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_resume_p2", utc_sound_pool_stream_resume_p2, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_resume_n", utc_sound_pool_stream_resume_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_stop_p", utc_sound_pool_stream_stop_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_stop_n", utc_sound_pool_stream_stop_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_stop_n2", utc_sound_pool_stream_stop_n2, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_set_volume_p", utc_sound_pool_stream_set_volume_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_set_volume_n", utc_sound_pool_stream_set_volume_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_volume_p", utc_sound_pool_stream_get_volume_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_volume_n", utc_sound_pool_stream_get_volume_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_set_priority_p", utc_sound_pool_stream_set_priority_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_set_priority_n", utc_sound_pool_stream_set_priority_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_priority_p", utc_sound_pool_stream_get_priority_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_priority_n", utc_sound_pool_stream_get_priority_n, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_state_p", utc_sound_pool_stream_get_state_p, utc_sound_pool_startup, utc_sound_pool_cleanup},
    {"utc_sound_pool_stream_get_state_n", utc_sound_pool_stream_get_state_n, utc_sound_pool_startup, utc_sound_pool_cleanup},

    {NULL, NULL}
};
#endif // __TCT_SOUND_POOL_NATIVE_H__
