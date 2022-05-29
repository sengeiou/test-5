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
#ifndef __TCT_RADIO-NATIVE_H__
#define __TCT_RADIO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_radio_startup(void);
extern void ITs_radio_cleanup(void);

extern int ITc_radio_create_destroy_p(void);
extern int ITc_radio_start_stop_p(void);
extern int ITc_radio_set_get_frequency_p(void);
extern int ITc_radio_set_mute_muted_p(void);
extern int ITc_radio_get_state_p(void);
extern int ITc_radio_get_signal_strength_p(void);
extern int ITc_radio_seek_up_down_p(void);
extern int ITc_radio_scan_start_stop_p(void);
extern int ITc_radio_set_unset_scan_completed_cb_p(void);
extern int ITc_radio_set_unset_interrupted_cb_p(void);
extern int ITc_radio_get_frequency_range_p(void);
extern int ITc_radio_get_channel_spacing_p(void);
extern int ITc_radio_set_get_volume_p(void);

testcase tc_array[] = {
	{"ITc_radio_create_destroy_p",ITc_radio_create_destroy_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_start_stop_p",ITc_radio_start_stop_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_set_get_frequency_p",ITc_radio_set_get_frequency_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_set_mute_muted_p",ITc_radio_set_mute_muted_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_get_state_p",ITc_radio_get_state_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_get_signal_strength_p",ITc_radio_get_signal_strength_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_seek_up_down_p",ITc_radio_seek_up_down_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_scan_start_stop_p",ITc_radio_scan_start_stop_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_set_unset_scan_completed_cb_p",ITc_radio_set_unset_scan_completed_cb_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_set_unset_interrupted_cb_p",ITc_radio_set_unset_interrupted_cb_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_get_frequency_range_p",ITc_radio_get_frequency_range_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_get_channel_spacing_p",ITc_radio_get_channel_spacing_p,ITs_radio_startup,ITs_radio_cleanup},
	{"ITc_radio_set_get_volume_p",ITc_radio_set_get_volume_p,ITs_radio_startup,ITs_radio_cleanup},
	{NULL, NULL}
};

#endif // __TCT_RADIO-NATIVE_H__
