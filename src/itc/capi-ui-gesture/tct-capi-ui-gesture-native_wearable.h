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
#ifndef __TCT_CAPI_UI_GESTURE_NATIVE_H__
#define __TCT_CAPI_UI_GESTURE_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_capi_ui_gesture_startup(void);
extern void ITs_capi_ui_gesture_cleanup(void);

extern int ITc_hand_gesture_create_destroy_p(void);
extern int ITc_hand_gesture_is_supported_type_p(void);
extern int ITc_hand_gesture_set_option_p(void);
extern int ITc_hand_gesture_start_stop_recognition_p(void);
extern int ITc_hand_gesture_get_engine_info_p(void);
extern int ITc_hand_gesture_set_unset_error_cb_p(void);

testcase tc_array[] = {
    {"ITc_hand_gesture_create_destroy_p", ITc_hand_gesture_create_destroy_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {"ITc_hand_gesture_is_supported_type_p", ITc_hand_gesture_is_supported_type_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {"ITc_hand_gesture_set_option_p", ITc_hand_gesture_set_option_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {"ITc_hand_gesture_start_stop_recognition_p", ITc_hand_gesture_start_stop_recognition_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {"ITc_hand_gesture_get_engine_info_p", ITc_hand_gesture_get_engine_info_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {"ITc_hand_gesture_set_unset_error_cb_p", ITc_hand_gesture_set_unset_error_cb_p, ITs_capi_ui_gesture_startup, ITs_capi_ui_gesture_cleanup},
    {NULL, NULL}
};

#endif // __TCT_CAPI_UI_GESTURE_NATIVE_H__
