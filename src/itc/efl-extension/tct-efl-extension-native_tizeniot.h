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

extern void ITs_efl_ext_startup(void);
extern void ITs_efl_ext_cleanup(void);

extern int ITc_eext_floatingbutton_movement_block_set_get_p(void);
extern int ITc_eext_floatingbutton_mode_set_get_p(void);
extern int ITc_eext_floatingbutton_pos_bring_in_p(void);

testcase tc_array[] = {
	{"ITc_eext_floatingbutton_movement_block_set_get_p",ITc_eext_floatingbutton_movement_block_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_floatingbutton_mode_set_get_p",ITc_eext_floatingbutton_mode_set_get_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{"ITc_eext_floatingbutton_pos_bring_in_p",ITc_eext_floatingbutton_pos_bring_in_p,ITs_efl_ext_startup,ITs_efl_ext_cleanup},
	{NULL, NULL}
};

#endif // __TCT_EFL-EXT-NATIVE_H__
