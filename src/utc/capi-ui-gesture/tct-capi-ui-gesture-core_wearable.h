//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_CAPI-UI-GESTURE-NATIVE_H__
#define __TCT_CAPI-UI-GESTURE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_capi_ui_gesture_startup(void);
extern void utc_capi_ui_gesture_cleanup(void);

extern int utc_hand_gesture_is_supported_type_p(void);
extern int utc_hand_gesture_is_supported_type_n(void);
extern int utc_hand_gesture_create_p(void);
extern int utc_hand_gesture_create_n(void);
extern int utc_hand_gesture_destroy_p(void);
extern int utc_hand_gesture_destroy_n(void);
extern int utc_hand_gesture_set_option_p(void);
extern int utc_hand_gesture_set_option_n(void);
extern int utc_hand_gesture_start_recognition_p(void);
extern int utc_hand_gesture_start_recognition_n(void);
extern int utc_hand_gesture_stop_recognition_p(void);
extern int utc_hand_gesture_stop_recognition_n(void);
extern int utc_hand_gesture_get_engine_info_p(void);
extern int utc_hand_gesture_get_engine_info_n(void);
extern int utc_hand_gesture_set_error_cb_p(void);
extern int utc_hand_gesture_set_error_cb_n(void);
extern int utc_hand_gesture_unset_error_cb_p(void);
extern int utc_hand_gesture_unset_error_cb_n(void);

testcase tc_array[] = {
	{"utc_hand_gesture_is_supported_type_p",utc_hand_gesture_is_supported_type_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_is_supported_type_n",utc_hand_gesture_is_supported_type_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_create_p",utc_hand_gesture_create_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_create_n",utc_hand_gesture_create_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_destroy_p",utc_hand_gesture_destroy_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_destroy_n",utc_hand_gesture_destroy_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_set_option_p",utc_hand_gesture_set_option_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_set_option_n",utc_hand_gesture_set_option_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_start_recognition_p",utc_hand_gesture_start_recognition_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_start_recognition_n",utc_hand_gesture_start_recognition_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_stop_recognition_p",utc_hand_gesture_stop_recognition_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_stop_recognition_n",utc_hand_gesture_stop_recognition_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_get_engine_info_p",utc_hand_gesture_get_engine_info_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_get_engine_info_n",utc_hand_gesture_get_engine_info_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_set_error_cb_p",utc_hand_gesture_set_error_cb_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_set_error_cb_n",utc_hand_gesture_set_error_cb_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_unset_error_cb_p",utc_hand_gesture_unset_error_cb_p,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{"utc_hand_gesture_unset_error_cb_n",utc_hand_gesture_unset_error_cb_n,utc_capi_ui_gesture_startup,utc_capi_ui_gesture_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI-UI-GESTURE-NATIVE_H__
