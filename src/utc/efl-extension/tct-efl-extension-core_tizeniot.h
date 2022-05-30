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
#ifndef __TCT_EFL-EXT-NATIVE_H__
#define __TCT_EFL-EXT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_efl_ext_startup(void);
extern void utc_efl_ext_cleanup(void);

extern int utc_efl_ext_popup_back_p(void);
extern int utc_efl_ext_ctxpopup_back_p(void);
extern int utc_efl_ext_naviframe_more_cb_p(void);
extern int utc_efl_ext_naviframe_back_cb_p(void);
extern int utc_efl_ext_object_event_callback_add_p1(void);
extern int utc_efl_ext_object_event_callback_add_p2(void);
extern int utc_efl_ext_object_event_callback_del_p(void);
extern int utc_efl_ext_entry_back_cb_p(void);
extern int utc_efl_ext_entry_selection_start_cb_p(void);
extern int utc_efl_ext_entry_selection_cleared_cb_p(void);
extern int utc_efl_ext_entry_selection_back_event_allow_set_p1(void);
extern int utc_efl_ext_entry_selection_back_event_allow_set_p2(void);
extern int utc_efl_ext_win_keygrab_set_p(void);
extern int utc_efl_ext_win_keygrab_unset_p(void);

testcase tc_array[] = {
	{"utc_efl_ext_popup_back_p",utc_efl_ext_popup_back_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_ctxpopup_back_p",utc_efl_ext_ctxpopup_back_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_naviframe_more_cb_p",utc_efl_ext_naviframe_more_cb_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_naviframe_back_cb_p",utc_efl_ext_naviframe_back_cb_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_object_event_callback_add_p1",utc_efl_ext_object_event_callback_add_p1,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_object_event_callback_add_p2",utc_efl_ext_object_event_callback_add_p2,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_object_event_callback_del_p",utc_efl_ext_object_event_callback_del_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_entry_back_cb_p",utc_efl_ext_entry_back_cb_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_entry_selection_start_cb_p",utc_efl_ext_entry_selection_start_cb_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_entry_selection_cleared_cb_p",utc_efl_ext_entry_selection_cleared_cb_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_entry_selection_back_event_allow_set_p1",utc_efl_ext_entry_selection_back_event_allow_set_p1,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_entry_selection_back_event_allow_set_p2",utc_efl_ext_entry_selection_back_event_allow_set_p2,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_win_keygrab_set_p",utc_efl_ext_win_keygrab_set_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{"utc_efl_ext_win_keygrab_unset_p",utc_efl_ext_win_keygrab_unset_p,utc_efl_ext_startup,utc_efl_ext_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EFL-EXT-NATIVE_H__
