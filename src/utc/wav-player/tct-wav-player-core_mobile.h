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
#ifndef __TCT_WAV-PLAYER-NATIVE_H__
#define __TCT_WAV-PLAYER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_wav_player_startup(void);
extern void utc_wav_player_cleanup(void);

extern int utc_wav_player_start_new_p(void);
extern int utc_wav_player_start_new_n1(void);
extern int utc_wav_player_start_new_n2(void);
extern int utc_wav_player_start_new_n3(void);
extern int utc_wav_player_start_loop_p(void);
extern int utc_wav_player_start_loop_n1(void);
extern int utc_wav_player_start_loop_n2(void);
extern int utc_wav_player_start_loop_n3(void);
extern int utc_wav_player_stop_p(void);
extern int utc_wav_player_stop_n(void);
extern int utc_wav_player_callback_p(void);

testcase tc_array[] = {
	{"utc_wav_player_start_new_p",utc_wav_player_start_new_p,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_new_n1",utc_wav_player_start_new_n1,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_new_n2",utc_wav_player_start_new_n2,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_new_n3",utc_wav_player_start_new_n3,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_loop_p",utc_wav_player_start_loop_p,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_loop_n1",utc_wav_player_start_loop_n1,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_loop_n2",utc_wav_player_start_loop_n2,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_start_loop_n3",utc_wav_player_start_loop_n3,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_stop_p",utc_wav_player_stop_p,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_stop_n",utc_wav_player_stop_n,utc_wav_player_startup,utc_wav_player_cleanup},
	{"utc_wav_player_callback_p",utc_wav_player_callback_p,utc_wav_player_startup,utc_wav_player_cleanup},
	{NULL, NULL}
};

#endif // __TCT_WAV-PLAYER-NATIVE_H__
