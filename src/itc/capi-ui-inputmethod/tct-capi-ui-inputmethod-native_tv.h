//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef __TCT_CAPI_UI_INPUTMETHOD_NATIVE_H__
#define __TCT_CAPI_UI_INPUTMETHOD_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_capi_ui_inputmethod_startup(void);
extern void ITs_capi_ui_inputmethod_cleanup(void);

extern int ITc_ime_set_floating_mode_p(void);
extern int ITc_ime_set_floating_drag_start_p(void);
extern int ITc_ime_set_floating_drag_end_p(void);
extern int ITc_ime_get_selected_text_p(void);
extern int ITc_ime_request_hide_p(void);
extern int ITc_ime_update_input_panel_event_p(void);
extern int ITc_ime_set_candidate_visibility_state_p(void);
extern int ITc_ime_event_set_process_key_event_with_keycode_cb_p(void);
extern int ITc_ime_event_set_prediction_hint_data_set_cb_p(void);

testcase tc_array[] = {
	{"ITc_ime_set_floating_mode_p", ITc_ime_set_floating_mode_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_set_floating_drag_start_p", ITc_ime_set_floating_drag_start_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_set_floating_drag_end_p", ITc_ime_set_floating_drag_end_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_get_selected_text_p", ITc_ime_get_selected_text_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_request_hide_p", ITc_ime_request_hide_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_update_input_panel_event_p", ITc_ime_update_input_panel_event_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_set_candidate_visibility_state_p", ITc_ime_set_candidate_visibility_state_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_event_set_process_key_event_with_keycode_cb_p", ITc_ime_event_set_process_key_event_with_keycode_cb_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{"ITc_ime_event_set_prediction_hint_data_set_cb_p", ITc_ime_event_set_prediction_hint_data_set_cb_p, ITs_capi_ui_inputmethod_startup, ITs_capi_ui_inputmethod_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAPI_UI_INPUTMETHOD_NATIVE_H__
