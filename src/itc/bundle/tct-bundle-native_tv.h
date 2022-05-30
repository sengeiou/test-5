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
#ifndef __TCT_BUNDLE-NATIVE_H__
#define __TCT_BUNDLE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_bundle_startup(void);
extern void ITs_bundle_cleanup(void);

extern int ITc_bundle_encode_decode_p(void);
extern int ITc_bundle_add_get_str_array_p(void);
extern int ITc_bundle_create_add_str_free_p(void);
extern int ITc_bundle_add_get_byte_p(void);
extern int ITc_bundle_add_get_str_p(void);
extern int ITc_bundle_get_type_del_p(void);
extern int ITc_bundle_key_val_target_apis_p(void);
extern int ITc_bundle_get_count_p(void);
extern int ITc_bundle_dup_p(void);
extern int ITc_bundle_add_byte_array_p(void);
extern int ITc_bundle_set_get_byte_array_p(void);

testcase tc_array[] = {
	{"ITc_bundle_encode_decode_p",ITc_bundle_encode_decode_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_add_get_str_array_p",ITc_bundle_add_get_str_array_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_create_add_str_free_p",ITc_bundle_create_add_str_free_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_add_get_byte_p",ITc_bundle_add_get_byte_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_add_get_str_p",ITc_bundle_add_get_str_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_get_type_del_p",ITc_bundle_get_type_del_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_key_val_target_apis_p",ITc_bundle_key_val_target_apis_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_get_count_p",ITc_bundle_get_count_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_dup_p",ITc_bundle_dup_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_add_byte_array_p",ITc_bundle_add_byte_array_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{"ITc_bundle_set_get_byte_array_p",ITc_bundle_set_get_byte_array_p,ITs_bundle_startup,ITs_bundle_cleanup},
	{NULL, NULL}
};

#endif // __TCT_BUNDLE-NATIVE_H__
