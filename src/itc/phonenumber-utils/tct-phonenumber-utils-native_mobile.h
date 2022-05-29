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
#ifndef __TCT_PHONENUMBER-UTILS-NATIVE_H__
#define __TCT_PHONENUMBER-UTILS-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_phonenumber_utils_startup(void);
extern void ITs_phonenumber_utils_cleanup(void);
extern void ITs_phonenumber_utils_blocking_rule_startup(void);
extern void ITs_phonenumber_utils_blocking_rule_cleanup(void);

extern int ITc_phone_number_get_formatted_number_p(void);
extern int ITc_phone_number_get_location_from_number_p(void);
extern int ITc_phone_number_get_normalized_number_p(void);
extern int ITc_phone_number_connect_disconnect_p(void);
extern int ITc_phone_number_utils_blocking_rule_create_destroy_p(void);
extern int ITc_phone_number_utils_blocking_rule_set_get_number_p(void);
extern int ITc_phone_number_utils_blocking_rule_set_get_match_type_p(void);


testcase tc_array[] = {
	{"ITc_phone_number_get_formatted_number_p",ITc_phone_number_get_formatted_number_p,ITs_phonenumber_utils_startup,ITs_phonenumber_utils_cleanup},
	{"ITc_phone_number_get_location_from_number_p",ITc_phone_number_get_location_from_number_p,ITs_phonenumber_utils_startup,ITs_phonenumber_utils_cleanup},
	{"ITc_phone_number_get_normalized_number_p",ITc_phone_number_get_normalized_number_p,ITs_phonenumber_utils_startup,ITs_phonenumber_utils_cleanup},
	{"ITc_phone_number_connect_disconnect_p",ITc_phone_number_connect_disconnect_p,ITs_phonenumber_utils_startup,ITs_phonenumber_utils_cleanup},
	{"ITc_phone_number_utils_blocking_rule_create_destroy_p",ITc_phone_number_utils_blocking_rule_create_destroy_p,ITs_phonenumber_utils_blocking_rule_startup,ITs_phonenumber_utils_blocking_rule_cleanup},
	{"ITc_phone_number_utils_blocking_rule_set_get_number_p",ITc_phone_number_utils_blocking_rule_set_get_number_p,ITs_phonenumber_utils_blocking_rule_startup,ITs_phonenumber_utils_blocking_rule_cleanup},
	{"ITc_phone_number_utils_blocking_rule_set_get_match_type_p",ITc_phone_number_utils_blocking_rule_set_get_match_type_p,ITs_phonenumber_utils_blocking_rule_startup,ITs_phonenumber_utils_blocking_rule_cleanup},
	{NULL, NULL}
};

#endif // __TCT_PHONENUMBER-UTILS-NATIVE_H__
