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
#ifndef __TCT_MEDIAMUXER-NATIVE_H__
#define __TCT_MEDIAMUXER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_mediamuxer_startup(void);
extern void utc_mediamuxer_cleanup(void);

extern int utc_mediamuxer_create_p(void);
extern int utc_mediamuxer_create_n(void);
extern int utc_mediamuxer_set_data_sink_p(void);
extern int utc_mediamuxer_set_data_sink_n(void);
extern int utc_mediamuxer_add_track_p(void);
extern int utc_mediamuxer_add_track_n(void);
extern int utc_mediamuxer_prepare_p(void);
extern int utc_mediamuxer_prepare_n(void);
extern int utc_mediamuxer_start_p(void);
extern int utc_mediamuxer_start_n(void);
extern int utc_mediamuxer_write_sample_p(void);
extern int utc_mediamuxer_write_sample_n(void);
extern int utc_mediamuxer_close_track_p(void);
extern int utc_mediamuxer_close_track_n(void);
extern int utc_mediamuxer_pause_p(void);
extern int utc_mediamuxer_pause_n(void);
extern int utc_mediamuxer_resume_p(void);
extern int utc_mediamuxer_resume_n(void);
extern int utc_mediamuxer_stop_p(void);
extern int utc_mediamuxer_stop_n(void);
extern int utc_mediamuxer_unprepare_p(void);
extern int utc_mediamuxer_unprepare_n(void);
extern int utc_mediamuxer_destroy_p(void);
extern int utc_mediamuxer_destroy_n(void);
extern int utc_mediamuxer_get_state_p(void);
extern int utc_mediamuxer_get_state_n(void);
extern int utc_mediamuxer_set_error_cb_p(void);
extern int utc_mediamuxer_set_error_cb_n(void);
extern int utc_mediamuxer_unset_error_cb_p(void);
extern int utc_mediamuxer_unset_error_cb_n(void);
extern int utc_mediamuxer_set_eos_cb_p(void);
extern int utc_mediamuxer_set_eos_cb_n(void);
extern int utc_mediamuxer_unset_eos_cb_p(void);
extern int utc_mediamuxer_unset_eos_cb_n(void);

testcase tc_array[] = {
	{"utc_mediamuxer_create_p",utc_mediamuxer_create_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_create_n",utc_mediamuxer_create_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_data_sink_p",utc_mediamuxer_set_data_sink_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_data_sink_n",utc_mediamuxer_set_data_sink_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_add_track_p",utc_mediamuxer_add_track_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_add_track_n",utc_mediamuxer_add_track_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_prepare_p",utc_mediamuxer_prepare_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_prepare_n",utc_mediamuxer_prepare_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_start_p",utc_mediamuxer_start_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_start_n",utc_mediamuxer_start_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_write_sample_p",utc_mediamuxer_write_sample_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_write_sample_n",utc_mediamuxer_write_sample_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_close_track_p",utc_mediamuxer_close_track_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_close_track_n",utc_mediamuxer_close_track_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_pause_p",utc_mediamuxer_pause_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_pause_n",utc_mediamuxer_pause_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_resume_p",utc_mediamuxer_resume_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_resume_n",utc_mediamuxer_resume_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_stop_p",utc_mediamuxer_stop_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_stop_n",utc_mediamuxer_stop_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unprepare_p",utc_mediamuxer_unprepare_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unprepare_n",utc_mediamuxer_unprepare_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_destroy_p",utc_mediamuxer_destroy_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_destroy_n",utc_mediamuxer_destroy_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_get_state_p",utc_mediamuxer_get_state_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_get_state_n",utc_mediamuxer_get_state_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_error_cb_p",utc_mediamuxer_set_error_cb_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_error_cb_n",utc_mediamuxer_set_error_cb_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unset_error_cb_p",utc_mediamuxer_unset_error_cb_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unset_error_cb_n",utc_mediamuxer_unset_error_cb_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_eos_cb_p",utc_mediamuxer_set_eos_cb_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_set_eos_cb_n",utc_mediamuxer_set_eos_cb_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unset_eos_cb_p",utc_mediamuxer_unset_eos_cb_p,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{"utc_mediamuxer_unset_eos_cb_n",utc_mediamuxer_unset_eos_cb_n,utc_mediamuxer_startup,utc_mediamuxer_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MEDIAMUXER-NATIVE_H__
