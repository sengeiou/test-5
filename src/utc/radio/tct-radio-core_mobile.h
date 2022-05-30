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

extern void utc_media_radio_startup(void);
extern void utc_media_radio_cleanup(void);

extern int utc_media_radio_get_state_p(void);
extern int utc_media_radio_get_state_n(void);
extern int utc_media_radio_start_p(void);
extern int utc_media_radio_start_n(void);
extern int utc_media_radio_set_frequency_p(void);
extern int utc_media_radio_set_frequency_n(void);
extern int utc_media_radio_get_frequency_p(void);
extern int utc_media_radio_get_frequency_n(void);
extern int utc_media_radio_seek_up_p(void);
extern int utc_media_radio_seek_up_n(void);
extern int utc_media_radio_seek_down_p(void);
extern int utc_media_radio_seek_down_n(void);
extern int utc_media_radio_scan_start_p(void);
extern int utc_media_radio_scan_start_n(void);
extern int utc_media_radio_scan_stop_p(void);
extern int utc_media_radio_scan_stop_n(void);
extern int utc_media_radio_set_mute_p(void);
extern int utc_media_radio_set_mute_n(void);
extern int utc_media_radio_is_muted_p(void);
extern int utc_media_radio_is_muted_n(void);
extern int utc_media_radio_set_scan_completed_cb_p(void);
extern int utc_media_radio_set_scan_completed_cb_n(void);
extern int utc_media_radio_unset_scan_completed_cb_p(void);
extern int utc_media_radio_unset_scan_completed_cb_n(void);
extern int utc_media_radio_set_interrupted_cb_p(void);
extern int utc_media_radio_set_interrupted_cb_n(void);
extern int utc_media_radio_unset_interrupted_cb_p(void);
extern int utc_media_radio_unset_interrupted_cb_n(void);
extern int utc_media_radio_get_signal_strength_p(void);
extern int utc_media_radio_get_signal_strength_n(void);
extern int utc_media_radio_stop_p(void);
extern int utc_media_radio_stop_n(void);
extern int utc_media_radio_destroy_p(void);
extern int utc_media_radio_destroy_n(void);
extern int utc_media_radio_create_p(void);
extern int utc_media_radio_create_n(void);
extern int utc_media_radio_get_frequency_range_p(void);
extern int utc_media_radio_get_frequency_range_n(void);
extern int utc_media_radio_get_channel_spacing_p(void);
extern int utc_media_radio_get_channel_spacing_n(void);
extern int utc_media_radio_set_volume_p(void);
extern int utc_media_radio_set_volume_n(void);
extern int utc_media_radio_get_volume_p(void);
extern int utc_media_radio_get_volume_n(void);

testcase tc_array[] = {
	{"utc_media_radio_get_state_p",utc_media_radio_get_state_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_state_n",utc_media_radio_get_state_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_start_p",utc_media_radio_start_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_start_n",utc_media_radio_start_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_frequency_p",utc_media_radio_set_frequency_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_frequency_n",utc_media_radio_set_frequency_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_frequency_p",utc_media_radio_get_frequency_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_frequency_n",utc_media_radio_get_frequency_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_seek_up_p",utc_media_radio_seek_up_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_seek_up_n",utc_media_radio_seek_up_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_seek_down_p",utc_media_radio_seek_down_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_seek_down_n",utc_media_radio_seek_down_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_scan_start_p",utc_media_radio_scan_start_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_scan_start_n",utc_media_radio_scan_start_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_scan_stop_p",utc_media_radio_scan_stop_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_scan_stop_n",utc_media_radio_scan_stop_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_mute_p",utc_media_radio_set_mute_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_mute_n",utc_media_radio_set_mute_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_is_muted_p",utc_media_radio_is_muted_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_is_muted_n",utc_media_radio_is_muted_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_scan_completed_cb_p",utc_media_radio_set_scan_completed_cb_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_scan_completed_cb_n",utc_media_radio_set_scan_completed_cb_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_unset_scan_completed_cb_p",utc_media_radio_unset_scan_completed_cb_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_unset_scan_completed_cb_n",utc_media_radio_unset_scan_completed_cb_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_interrupted_cb_p",utc_media_radio_set_interrupted_cb_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_interrupted_cb_n",utc_media_radio_set_interrupted_cb_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_unset_interrupted_cb_p",utc_media_radio_unset_interrupted_cb_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_unset_interrupted_cb_n",utc_media_radio_unset_interrupted_cb_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_signal_strength_p",utc_media_radio_get_signal_strength_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_signal_strength_n",utc_media_radio_get_signal_strength_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_stop_p",utc_media_radio_stop_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_stop_n",utc_media_radio_stop_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_destroy_p",utc_media_radio_destroy_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_destroy_n",utc_media_radio_destroy_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_create_p",utc_media_radio_create_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_create_n",utc_media_radio_create_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_frequency_range_p",utc_media_radio_get_frequency_range_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_frequency_range_n",utc_media_radio_get_frequency_range_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_channel_spacing_p",utc_media_radio_get_channel_spacing_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_channel_spacing_n",utc_media_radio_get_channel_spacing_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_volume_p",utc_media_radio_set_volume_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_set_volume_n",utc_media_radio_set_volume_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_volume_p",utc_media_radio_get_volume_p,utc_media_radio_startup,utc_media_radio_cleanup},
	{"utc_media_radio_get_volume_n",utc_media_radio_get_volume_n,utc_media_radio_startup,utc_media_radio_cleanup},
	{NULL, NULL}
};

#endif // __TCT_RADIO-NATIVE_H__
