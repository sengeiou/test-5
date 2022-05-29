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

extern void ITs_sound_pool_startup(void);
extern void ITs_sound_pool_cleanup(void);

extern int ITs_sound_pool_create_destroy_p(void);
extern int ITs_sound_pool_load_unload_source_from_file_p(void);
extern int ITs_sound_pool_stream_play_stop_p(void);
extern int ITs_sound_pool_stream_pause_resume_p(void);
extern int ITs_sound_pool_get_state_p(void);
extern int ITs_sound_pool_activate_deactivate_p(void);
extern int ITs_sound_pool_set_get_volume_p(void);
extern int ITs_sound_pool_stream_set_get_volume_p(void);
extern int ITs_sound_pool_stream_set_get_priority_p(void);
extern int ITs_sound_pool_stream_get_state_p(void);
extern int ITs_sound_pool_set_unset_state_changed_cb_p(void);

testcase tc_array[] = {
    {"ITs_sound_pool_create_destroy_p", ITs_sound_pool_create_destroy_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_load_unload_source_from_file_p", ITs_sound_pool_load_unload_source_from_file_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_stream_play_stop_p", ITs_sound_pool_stream_play_stop_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_stream_pause_resume_p", ITs_sound_pool_stream_pause_resume_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_get_state_p", ITs_sound_pool_get_state_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_activate_deactivate_p", ITs_sound_pool_activate_deactivate_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_set_get_volume_p", ITs_sound_pool_set_get_volume_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_stream_set_get_volume_p", ITs_sound_pool_stream_set_get_volume_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_stream_set_get_priority_p", ITs_sound_pool_stream_set_get_priority_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_stream_get_state_p", ITs_sound_pool_stream_get_state_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {"ITs_sound_pool_set_unset_state_changed_cb_p", ITs_sound_pool_set_unset_state_changed_cb_p, ITs_sound_pool_startup, ITs_sound_pool_cleanup},
    {NULL, NULL}
};
#endif // __TCT_SOUND_POOL_NATIVE_H__
