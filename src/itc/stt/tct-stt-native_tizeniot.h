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
#ifndef __TCT_STT-NATIVE_H__
#define __TCT_STT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_stt_startup(void);
extern void ITs_stt_cleanup(void);
extern void ITs_stte_startup(void);
extern void ITs_stte_cleanup(void);

extern int ITc_stt_create_destroy_p(void);
extern int ITc_stt_prepare_unprepare_p(void);
extern int ITc_stt_start_stop_p(void);
extern int ITc_stt_start_cancel_p(void);
extern int ITc_stt_start_stop_cancel_p(void);
extern int ITc_stt_get_state_p(void);
extern int ITc_stt_get_default_language_p(void);
extern int ITc_stt_set_get_engine_p(void);
extern int ITc_stt_is_recognition_type_supported_p(void);
extern int ITc_stt_get_recording_volume_p(void);
extern int ITc_stt_set_silence_detection_p(void);
extern int ITc_stt_set_unset_start_sound_p(void);
extern int ITc_stt_set_unset_stop_sound_p(void);
extern int ITc_stt_set_unset_state_changed_cb_p(void);
extern int ITc_stt_set_unset_recognition_result_cb_p(void);
extern int ITc_stt_set_unset_default_language_changed_cb_p(void);
extern int ITc_stt_set_unset_error_cb_p(void);
extern int ITc_stt_foreach_detailed_result_p(void);
extern int ITc_stt_foreach_supported_engines_p(void);
extern int ITc_stt_foreach_supported_languages_p(void);
extern int ITc_stt_set_credential_p(void);
extern int ITc_stt_set_get_private_data_p(void);
extern int ITc_stt_set_unset_engine_changed_cb_p(void);
extern int ITc_stt_set_unset_speech_status_cb_p(void);
extern int ITc_stte_main_p(void);
extern int ITc_stte_set_private_data_set_cb_p(void);
extern int ITc_stte_set_private_data_requested_cb_p(void);
extern int ITc_stte_set_unset_audio_type_set_cb_p(void);

testcase tc_array[] = {
	{"ITc_stt_create_destroy_p",ITc_stt_create_destroy_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_prepare_unprepare_p",ITc_stt_prepare_unprepare_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_start_stop_p",ITc_stt_start_stop_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_start_cancel_p",ITc_stt_start_cancel_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_start_stop_cancel_p",ITc_stt_start_stop_cancel_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_get_state_p",ITc_stt_get_state_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_get_default_language_p",ITc_stt_get_default_language_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_get_engine_p",ITc_stt_set_get_engine_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_is_recognition_type_supported_p",ITc_stt_is_recognition_type_supported_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_get_recording_volume_p",ITc_stt_get_recording_volume_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_silence_detection_p",ITc_stt_set_silence_detection_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_start_sound_p",ITc_stt_set_unset_start_sound_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_stop_sound_p",ITc_stt_set_unset_stop_sound_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_state_changed_cb_p",ITc_stt_set_unset_state_changed_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_recognition_result_cb_p",ITc_stt_set_unset_recognition_result_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_default_language_changed_cb_p",ITc_stt_set_unset_default_language_changed_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_error_cb_p",ITc_stt_set_unset_error_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_foreach_detailed_result_p",ITc_stt_foreach_detailed_result_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_foreach_supported_engines_p",ITc_stt_foreach_supported_engines_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_foreach_supported_languages_p",ITc_stt_foreach_supported_languages_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_credential_p",ITc_stt_set_credential_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_get_private_data_p",ITc_stt_set_get_private_data_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_engine_changed_cb_p",ITc_stt_set_unset_engine_changed_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stt_set_unset_speech_status_cb_p",ITc_stt_set_unset_speech_status_cb_p,ITs_stt_startup,ITs_stt_cleanup},
	{"ITc_stte_main_p",ITc_stte_main_p,ITs_stte_startup,ITs_stte_cleanup},
	{"ITc_stte_set_private_data_set_cb_p",ITc_stte_set_private_data_set_cb_p,ITs_stte_startup,ITs_stte_cleanup},
	{"ITc_stte_set_private_data_requested_cb_p",ITc_stte_set_private_data_requested_cb_p,ITs_stte_startup,ITs_stte_cleanup},
	{"ITc_stte_set_unset_audio_type_set_cb_p",ITc_stte_set_unset_audio_type_set_cb_p,ITs_stte_startup,ITs_stte_cleanup},
	{NULL, NULL}
};

#endif // __TCT_STT-NATIVE_H__
