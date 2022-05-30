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
#ifndef __TCT_CAPI-MEDIAMUXER-NATIVE_H__
#define __TCT_CAPI-MEDIAMUXER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_mediamuxer_startup(void);
extern void ITs_mediamuxer_cleanup(void);

extern int ITc_mediamuxer_create_destroy_p(void);
extern int ITc_mediamuxer_set_data_sink_p(void);
extern int ITc_mediamuxer_prepare_unprepare_p(void);
extern int ITc_mediamuxer_add_close_track_p(void);
extern int ITc_mediamuxer_start_stop_p(void);
extern int ITc_mediamuxer_write_sample_p(void);
extern int ITc_mediamuxer_get_state_p(void);
extern int ITc_mediamuxer_set_unset_error_cb_p(void);
extern int ITc_mediamuxer_pause_resume_p(void);
extern int ITc_mediamuxer_set_unset_eos_cb_p(void);

testcase tc_array[] = {
	{"ITc_mediamuxer_create_destroy_p",ITc_mediamuxer_create_destroy_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_set_data_sink_p",ITc_mediamuxer_set_data_sink_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_prepare_unprepare_p",ITc_mediamuxer_prepare_unprepare_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_add_close_track_p",ITc_mediamuxer_add_close_track_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_start_stop_p",ITc_mediamuxer_start_stop_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_write_sample_p",ITc_mediamuxer_write_sample_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_get_state_p",ITc_mediamuxer_get_state_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_set_unset_error_cb_p",ITc_mediamuxer_set_unset_error_cb_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_pause_resume_p",ITc_mediamuxer_pause_resume_p,ITs_mediamuxer_startup,ITs_mediamuxer_cleanup},
	{"ITc_mediamuxer_set_unset_eos_cb_p",ITc_mediamuxer_set_unset_eos_cb_p, ITs_mediamuxer_startup, ITs_mediamuxer_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-MEDIAMUXER-NATIVE_H__
