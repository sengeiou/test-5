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
#ifndef __TCT_MOTION-NATIVE_H__
#define __TCT_MOTION-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_motion_activity_startup(void);
extern void utc_motion_activity_cleanup(void);
extern void utc_motion_gesture_startup(void);
extern void utc_motion_gesture_cleanup(void);

extern int utc_motion_activity_is_supported_p(void);
extern int utc_motion_activity_is_supported_n(void);
extern int utc_motion_activity_create_p(void);
extern int utc_motion_activity_create_n(void);
extern int utc_motion_activity_release_p(void);
extern int utc_motion_activity_release_n(void);
extern int utc_motion_activity_start_recognition_p(void);
extern int utc_motion_activity_start_recognition_n(void);
extern int utc_motion_activity_stop_recognition_p(void);
extern int utc_motion_activity_stop_recognition_n(void);
extern int utc_motion_activity_get_accuracy_n(void);
extern int utc_motion_gesture_is_supported_p(void);
extern int utc_motion_gesture_is_supported_n(void);
extern int utc_motion_gesture_create_p(void);
extern int utc_motion_gesture_create_n(void);
extern int utc_motion_gesture_release_p(void);
extern int utc_motion_gesture_release_n(void);
extern int utc_motion_gesture_start_recognition_p(void);
extern int utc_motion_gesture_start_recognition_n(void);
extern int utc_motion_gesture_stop_recognition_p(void);
extern int utc_motion_gesture_stop_recognition_n(void);
extern int utc_motion_gesture_get_event_n(void);
extern int utc_motion_gesture_get_tilt_n(void);

testcase tc_array[] = {
	{"utc_motion_activity_is_supported_p",utc_motion_activity_is_supported_p,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_is_supported_n",utc_motion_activity_is_supported_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_create_p",utc_motion_activity_create_p,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_create_n",utc_motion_activity_create_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_release_p",utc_motion_activity_release_p,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_release_n",utc_motion_activity_release_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_start_recognition_p",utc_motion_activity_start_recognition_p,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_start_recognition_n",utc_motion_activity_start_recognition_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_stop_recognition_p",utc_motion_activity_stop_recognition_p,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_stop_recognition_n",utc_motion_activity_stop_recognition_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_activity_get_accuracy_n",utc_motion_activity_get_accuracy_n,utc_motion_activity_startup,utc_motion_activity_cleanup},
	{"utc_motion_gesture_is_supported_p",utc_motion_gesture_is_supported_p,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_is_supported_n",utc_motion_gesture_is_supported_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_create_p",utc_motion_gesture_create_p,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_create_n",utc_motion_gesture_create_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_release_p",utc_motion_gesture_release_p,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_release_n",utc_motion_gesture_release_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_start_recognition_p",utc_motion_gesture_start_recognition_p,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_start_recognition_n",utc_motion_gesture_start_recognition_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_stop_recognition_p",utc_motion_gesture_stop_recognition_p,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_stop_recognition_n",utc_motion_gesture_stop_recognition_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_get_event_n",utc_motion_gesture_get_event_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{"utc_motion_gesture_get_tilt_n",utc_motion_gesture_get_tilt_n,utc_motion_gesture_startup,utc_motion_gesture_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MOTION-NATIVE_H__
