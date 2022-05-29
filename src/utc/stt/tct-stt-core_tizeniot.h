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

extern void utc_stt_startup(void);
extern void utc_stt_cleanup(void);
extern void utc_stte_startup(void);
extern void utc_stte_cleanup(void);

extern int utc_stt_create_p(void);
extern int utc_stt_create_n(void);
extern int utc_stt_destroy_p(void);
extern int utc_stt_destroy_p1(void);
extern int utc_stt_destroy_p2(void);
extern int utc_stt_destroy_n(void);
extern int utc_stt_destroy_n1(void);
extern int utc_stt_destroy_n2(void);
extern int utc_stt_prepare_p(void);
extern int utc_stt_prepare_n(void);
extern int utc_stt_prepare_n1(void);
extern int utc_stt_unprepare_p(void);
extern int utc_stt_unprepare_n(void);
extern int utc_stt_unprepare_n1(void);
extern int utc_stt_foreach_supported_engines_p(void);
extern int utc_stt_foreach_supported_engines_n(void);
extern int utc_stt_foreach_supported_engines_n1(void);
extern int utc_stt_get_engine_p(void);
extern int utc_stt_get_engine_n(void);
extern int utc_stt_get_engine_n1(void);
extern int utc_stt_set_engine_p(void);
extern int utc_stt_set_engine_n(void);
extern int utc_stt_set_engine_n1(void);
extern int utc_stt_foreach_supported_languages_p(void);
extern int utc_stt_foreach_supported_languages_n(void);
extern int utc_stt_get_default_language_p(void);
extern int utc_stt_get_default_language_n(void);
extern int utc_stt_get_state_p(void);
extern int utc_stt_get_state_n(void);
extern int utc_stt_is_recognition_type_supported_p(void);
extern int utc_stt_is_recognition_type_supported_p1(void);
extern int utc_stt_is_recognition_type_supported_n(void);
extern int utc_stt_is_recognition_type_supported_n1(void);
extern int utc_stt_is_recognition_type_supported_n2(void);
extern int utc_stt_set_silence_detection_p(void);
extern int utc_stt_set_silence_detection_n(void);
extern int utc_stt_set_silence_detection_n1(void);
extern int utc_stt_set_silence_detection_n2(void);
extern int utc_stt_start_p(void);
extern int utc_stt_start_n(void);
extern int utc_stt_start_n1(void);
extern int utc_stt_stop_p(void);
extern int utc_stt_stop_n(void);
extern int utc_stt_cancel_p(void);
extern int utc_stt_cancel_n(void);
extern int utc_stt_cancel_n1(void);
extern int utc_stt_get_recording_volume_p(void);
extern int utc_stt_get_recording_volume_n(void);
extern int utc_stt_get_recording_volume_n1(void);
extern int utc_stt_set_recognition_result_cb_p(void);
extern int utc_stt_set_recognition_result_cb_n(void);
extern int utc_stt_set_recognition_result_cb_n1(void);
extern int utc_stt_unset_recognition_result_cb_p(void);
extern int utc_stt_unset_recognition_result_cb_n(void);
extern int utc_stt_unset_recognition_result_cb_n1(void);
extern int utc_stt_set_state_changed_cb_p(void);
extern int utc_stt_set_state_changed_cb_n(void);
extern int utc_stt_set_state_changed_cb_n1(void);
extern int utc_stt_unset_state_changed_cb_p(void);
extern int utc_stt_unset_state_changed_cb_n(void);
extern int utc_stt_unset_state_changed_cb_n1(void);
extern int utc_stt_set_error_cb_p(void);
extern int utc_stt_set_error_cb_n(void);
extern int utc_stt_set_error_cb_n1(void);
extern int utc_stt_unset_error_cb_p(void);
extern int utc_stt_unset_error_cb_n(void);
extern int utc_stt_unset_error_cb_n1(void);
extern int utc_stt_set_default_language_changed_cb_p(void);
extern int utc_stt_set_default_language_changed_cb_n(void);
extern int utc_stt_set_default_language_changed_cb_n1(void);
extern int utc_stt_unset_default_language_changed_cb_p(void);
extern int utc_stt_unset_default_language_changed_cb_n(void);
extern int utc_stt_unset_default_language_changed_cb_n1(void);
extern int utc_stt_set_start_sound_p(void);
extern int utc_stt_set_start_sound_n(void);
extern int utc_stt_set_start_sound_n1(void);
extern int utc_stt_unset_start_sound_p(void);
extern int utc_stt_unset_start_sound_n(void);
extern int utc_stt_unset_start_sound_n1(void);
extern int utc_stt_set_stop_sound_p(void);
extern int utc_stt_set_stop_sound_n(void);
extern int utc_stt_set_stop_sound_n1(void);
extern int utc_stt_set_stop_sound_n2(void);
extern int utc_stt_unset_stop_sound_p(void);
extern int utc_stt_unset_stop_sound_n(void);
extern int utc_stt_unset_stop_sound_n1(void);
extern int utc_stt_foreach_detailed_result_p(void);
extern int utc_stt_foreach_detailed_result_n(void);
extern int utc_stt_get_error_message_n(void);
extern int utc_stt_get_error_message_n1(void);
extern int utc_stt_get_error_message_n2(void);
extern int utc_stt_set_private_data_p(void);
extern int utc_stt_set_private_data_n(void);
extern int utc_stt_set_private_data_n1(void);
extern int utc_stt_set_private_data_n2(void);
extern int utc_stt_set_private_data_n3(void);
extern int utc_stt_get_private_data_p(void);
extern int utc_stt_get_private_data_n(void);
extern int utc_stt_get_private_data_n1(void);
extern int utc_stt_get_private_data_n2(void);
extern int utc_stt_get_private_data_n3(void);
extern int utc_stt_set_credential_p(void);
extern int utc_stt_set_credential_n(void);
extern int utc_stt_set_credential_n1(void);
extern int utc_stt_set_engine_changed_cb_p(void);
extern int utc_stt_set_engine_changed_cb_n(void);
extern int utc_stt_set_engine_changed_cb_n1(void);
extern int utc_stt_unset_engine_changed_cb_p(void);
extern int utc_stt_unset_engine_changed_cb_n(void);
extern int utc_stt_unset_engine_changed_cb_n1(void);
extern int utc_stt_set_speech_status_cb_p(void);
extern int utc_stt_set_speech_status_cb_n(void);
extern int utc_stt_unset_speech_status_cb_p(void);
extern int utc_stt_unset_speech_status_cb_n(void);
extern int utc_stte_main_p(void);
extern int utc_stte_main_n(void);
extern int utc_stte_send_result_n(void);
extern int utc_stte_send_speech_status_n(void);
extern int utc_stte_send_error_p(void);
extern int utc_stte_set_private_data_set_cb_p(void);
extern int utc_stte_set_private_data_set_cb_n(void);
extern int utc_stte_set_private_data_requested_cb_p(void);
extern int utc_stte_set_private_data_requested_cb_n(void);
extern int utc_stte_set_audio_type_set_cb_p(void);
extern int utc_stte_set_audio_type_set_cb_n(void);
extern int utc_stte_unset_audio_type_set_cb_p(void);

testcase tc_array[] = {
	{"utc_stt_create_p",utc_stt_create_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_create_n",utc_stt_create_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_p",utc_stt_destroy_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_p1",utc_stt_destroy_p1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_p2",utc_stt_destroy_p2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_n",utc_stt_destroy_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_n1",utc_stt_destroy_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_destroy_n2",utc_stt_destroy_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_prepare_p",utc_stt_prepare_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_prepare_n",utc_stt_prepare_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_prepare_n1",utc_stt_prepare_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unprepare_p",utc_stt_unprepare_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unprepare_n",utc_stt_unprepare_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unprepare_n1",utc_stt_unprepare_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_supported_engines_p",utc_stt_foreach_supported_engines_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_supported_engines_n",utc_stt_foreach_supported_engines_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_supported_engines_n1",utc_stt_foreach_supported_engines_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_engine_p",utc_stt_get_engine_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_engine_n",utc_stt_get_engine_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_engine_n1",utc_stt_get_engine_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_p",utc_stt_set_engine_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_n",utc_stt_set_engine_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_n1",utc_stt_set_engine_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_supported_languages_p",utc_stt_foreach_supported_languages_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_supported_languages_n",utc_stt_foreach_supported_languages_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_default_language_p",utc_stt_get_default_language_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_default_language_n",utc_stt_get_default_language_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_state_p",utc_stt_get_state_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_state_n",utc_stt_get_state_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_is_recognition_type_supported_p",utc_stt_is_recognition_type_supported_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_is_recognition_type_supported_p1",utc_stt_is_recognition_type_supported_p1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_is_recognition_type_supported_n",utc_stt_is_recognition_type_supported_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_is_recognition_type_supported_n1",utc_stt_is_recognition_type_supported_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_is_recognition_type_supported_n2",utc_stt_is_recognition_type_supported_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_silence_detection_p",utc_stt_set_silence_detection_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_silence_detection_n",utc_stt_set_silence_detection_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_silence_detection_n1",utc_stt_set_silence_detection_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_silence_detection_n2",utc_stt_set_silence_detection_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_start_p",utc_stt_start_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_start_n",utc_stt_start_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_start_n1",utc_stt_start_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_stop_p",utc_stt_stop_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_stop_n",utc_stt_stop_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_cancel_p",utc_stt_cancel_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_cancel_n",utc_stt_cancel_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_cancel_n1",utc_stt_cancel_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_recording_volume_p",utc_stt_get_recording_volume_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_recording_volume_n",utc_stt_get_recording_volume_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_recording_volume_n1",utc_stt_get_recording_volume_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_recognition_result_cb_p",utc_stt_set_recognition_result_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_recognition_result_cb_n",utc_stt_set_recognition_result_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_recognition_result_cb_n1",utc_stt_set_recognition_result_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_recognition_result_cb_p",utc_stt_unset_recognition_result_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_recognition_result_cb_n",utc_stt_unset_recognition_result_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_recognition_result_cb_n1",utc_stt_unset_recognition_result_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_state_changed_cb_p",utc_stt_set_state_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_state_changed_cb_n",utc_stt_set_state_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_state_changed_cb_n1",utc_stt_set_state_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_state_changed_cb_p",utc_stt_unset_state_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_state_changed_cb_n",utc_stt_unset_state_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_state_changed_cb_n1",utc_stt_unset_state_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_error_cb_p",utc_stt_set_error_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_error_cb_n",utc_stt_set_error_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_error_cb_n1",utc_stt_set_error_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_error_cb_p",utc_stt_unset_error_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_error_cb_n",utc_stt_unset_error_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_error_cb_n1",utc_stt_unset_error_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_default_language_changed_cb_p",utc_stt_set_default_language_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_default_language_changed_cb_n",utc_stt_set_default_language_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_default_language_changed_cb_n1",utc_stt_set_default_language_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_default_language_changed_cb_p",utc_stt_unset_default_language_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_default_language_changed_cb_n",utc_stt_unset_default_language_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_default_language_changed_cb_n1",utc_stt_unset_default_language_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_start_sound_p",utc_stt_set_start_sound_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_start_sound_n",utc_stt_set_start_sound_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_start_sound_n1",utc_stt_set_start_sound_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_start_sound_p",utc_stt_unset_start_sound_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_start_sound_n",utc_stt_unset_start_sound_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_start_sound_n1",utc_stt_unset_start_sound_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_stop_sound_p",utc_stt_set_stop_sound_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_stop_sound_n",utc_stt_set_stop_sound_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_stop_sound_n1",utc_stt_set_stop_sound_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_stop_sound_n2",utc_stt_set_stop_sound_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_stop_sound_p",utc_stt_unset_stop_sound_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_stop_sound_n",utc_stt_unset_stop_sound_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_stop_sound_n1",utc_stt_unset_stop_sound_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_detailed_result_p",utc_stt_foreach_detailed_result_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_foreach_detailed_result_n",utc_stt_foreach_detailed_result_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_error_message_n",utc_stt_get_error_message_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_error_message_n1",utc_stt_get_error_message_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_error_message_n2",utc_stt_get_error_message_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_private_data_p",utc_stt_set_private_data_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_private_data_n",utc_stt_set_private_data_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_private_data_n1",utc_stt_set_private_data_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_private_data_n2",utc_stt_set_private_data_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_private_data_n3",utc_stt_set_private_data_n3,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_private_data_p",utc_stt_get_private_data_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_private_data_n",utc_stt_get_private_data_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_private_data_n1",utc_stt_get_private_data_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_private_data_n2",utc_stt_get_private_data_n2,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_get_private_data_n3",utc_stt_get_private_data_n3,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_credential_p",utc_stt_set_credential_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_credential_n",utc_stt_set_credential_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_credential_n1",utc_stt_set_credential_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_changed_cb_p",utc_stt_set_engine_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_changed_cb_n",utc_stt_set_engine_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_engine_changed_cb_n1",utc_stt_set_engine_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_engine_changed_cb_p",utc_stt_unset_engine_changed_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_engine_changed_cb_n",utc_stt_unset_engine_changed_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_engine_changed_cb_n1",utc_stt_unset_engine_changed_cb_n1,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_speech_status_cb_p",utc_stt_set_speech_status_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_set_speech_status_cb_n",utc_stt_set_speech_status_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_speech_status_cb_p",utc_stt_unset_speech_status_cb_p,utc_stt_startup,utc_stt_cleanup},
	{"utc_stt_unset_speech_status_cb_n",utc_stt_unset_speech_status_cb_n,utc_stt_startup,utc_stt_cleanup},
	{"utc_stte_main_p",utc_stte_main_p,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_main_n",utc_stte_main_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_send_result_n",utc_stte_send_result_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_send_speech_status_n",utc_stte_send_speech_status_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_send_error_p",utc_stte_send_error_p,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_private_data_set_cb_p",utc_stte_set_private_data_set_cb_p,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_private_data_set_cb_n",utc_stte_set_private_data_set_cb_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_private_data_requested_cb_p",utc_stte_set_private_data_requested_cb_p,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_private_data_requested_cb_n",utc_stte_set_private_data_requested_cb_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_audio_type_set_cb_p",utc_stte_set_audio_type_set_cb_p,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_set_audio_type_set_cb_n",utc_stte_set_audio_type_set_cb_n,utc_stte_startup,utc_stte_cleanup},
	{"utc_stte_unset_audio_type_set_cb_p",utc_stte_unset_audio_type_set_cb_p,utc_stte_startup,utc_stte_cleanup},
	{NULL, NULL}
};

#endif // __TCT_STT-NATIVE_H__
