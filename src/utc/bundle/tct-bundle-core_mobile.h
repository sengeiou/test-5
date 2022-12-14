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

extern void utc_ApplicationFW_bundle_del_startup(void);
extern void utc_ApplicationFW_bundle_del_cleanup(void);
extern void utc_ApplicationFW_bundle_add_str_startup(void);
extern void utc_ApplicationFW_bundle_add_str_cleanup(void);
extern void utc_ApplicationFW_bundle_add_byte_startup(void);
extern void utc_ApplicationFW_bundle_add_byte_cleanup(void);
extern void utc_ApplicationFW_bundle_add_str_array_startup(void);
extern void utc_ApplicationFW_bundle_add_str_array_cleanup(void);
extern void utc_ApplicationFW_bundle_get_str_array_startup(void);
extern void utc_ApplicationFW_bundle_get_str_array_cleanup(void);
extern void utc_ApplicationFW_bundle_add_byte_array_startup(void);
extern void utc_ApplicationFW_bundle_add_byte_array_cleanup(void);
extern void utc_ApplicationFW_bundle_set_byte_array_element_startup(void);
extern void utc_ApplicationFW_bundle_set_byte_array_element_cleanup(void);
extern void utc_ApplicationFW_bundle_get_byte_array_startup(void);
extern void utc_ApplicationFW_bundle_get_byte_array_cleanup(void);

extern int utc_ApplicationFW_bundle_create_p(void);
extern int utc_ApplicationFW_bundle_decode_p1(void);
extern int utc_ApplicationFW_bundle_decode_p2(void);
extern int utc_ApplicationFW_bundle_decode_n(void);
extern int utc_ApplicationFW_bundle_del_p(void);
extern int utc_ApplicationFW_bundle_del_n(void);
extern int utc_ApplicationFW_bundle_del_n2(void);
extern int utc_ApplicationFW_bundle_del_n3(void);
extern int utc_ApplicationFW_bundle_dup_p(void);
extern int utc_ApplicationFW_bundle_dup_n(void);
extern int utc_ApplicationFW_bundle_encode_p(void);
extern int utc_ApplicationFW_bundle_encode_n(void);
extern int utc_ApplicationFW_bundle_encode_n2(void);
extern int utc_ApplicationFW_bundle_encode_n3(void);
extern int utc_ApplicationFW_bundle_free_p(void);
extern int utc_ApplicationFW_bundle_free_n(void);
extern int utc_ApplicationFW_bundle_get_count_p(void);
extern int utc_ApplicationFW_bundle_get_count_n(void);
extern int utc_ApplicationFW_bundle_foreach_p(void);
extern int utc_ApplicationFW_bundle_foreach_n(void);
extern int utc_ApplicationFW_bundle_get_type_p(void);
extern int utc_ApplicationFW_bundle_get_type_n(void);
extern int utc_ApplicationFW_bundle_add_str_p(void);
extern int utc_ApplicationFW_bundle_add_str_n(void);
extern int utc_ApplicationFW_bundle_add_str_n2(void);
extern int utc_ApplicationFW_bundle_add_str_n3(void);
extern int utc_ApplicationFW_bundle_get_str_p(void);
extern int utc_ApplicationFW_bundle_get_str_n(void);
extern int utc_ApplicationFW_bundle_get_str_n2(void);
extern int utc_ApplicationFW_bundle_get_str_n3(void);
extern int utc_ApplicationFW_bundle_add_byte_p(void);
extern int utc_ApplicationFW_bundle_add_byte_n(void);
extern int utc_ApplicationFW_bundle_add_byte_n2(void);
extern int utc_ApplicationFW_bundle_get_byte_p(void);
extern int utc_ApplicationFW_bundle_get_byte_n(void);
extern int utc_ApplicationFW_bundle_get_byte_n2(void);
extern int utc_ApplicationFW_bundle_get_byte_n3(void);
extern int utc_ApplicationFW_bundle_add_str_array_p(void);
extern int utc_ApplicationFW_bundle_add_str_array_n(void);
extern int utc_ApplicationFW_bundle_add_str_array_n2(void);
extern int utc_ApplicationFW_bundle_add_str_array_n3(void);
extern int utc_ApplicationFW_bundle_get_str_array_p(void);
extern int utc_ApplicationFW_bundle_get_str_array_n(void);
extern int utc_ApplicationFW_bundle_get_str_array_n2(void);
extern int utc_ApplicationFW_bundle_get_str_array_n3(void);
extern int utc_ApplicationFW_bundle_keyval_get_type_p(void);
extern int utc_ApplicationFW_bundle_keyval_get_type_n(void);
extern int utc_ApplicationFW_bundle_keyval_type_is_array_p(void);
extern int utc_ApplicationFW_bundle_keyval_type_is_array_n(void);
extern int utc_bundle_keyval_get_basic_val_p(void);
extern int utc_bundle_keyval_get_basic_val_n(void);
extern int utc_bundle_keyval_get_array_val_p(void);
extern int utc_bundle_keyval_get_array_val_n(void);
extern int utc_ApplicationFW_bundle_add_byte_array_p(void);
extern int utc_ApplicationFW_bundle_add_byte_array_n1(void);
extern int utc_ApplicationFW_bundle_add_byte_array_n2(void);
extern int utc_ApplicationFW_bundle_set_byte_array_element_p(void);
extern int utc_ApplicationFW_bundle_set_byte_array_element_n(void);
extern int utc_ApplicationFW_bundle_get_byte_array_p(void);
extern int utc_ApplicationFW_bundle_get_byte_array_n(void);

testcase tc_array[] = {
	{"utc_ApplicationFW_bundle_create_p",utc_ApplicationFW_bundle_create_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_decode_p1",utc_ApplicationFW_bundle_decode_p1,NULL,NULL},
	{"utc_ApplicationFW_bundle_decode_p2",utc_ApplicationFW_bundle_decode_p2,NULL,NULL},
	{"utc_ApplicationFW_bundle_decode_n",utc_ApplicationFW_bundle_decode_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_del_p",utc_ApplicationFW_bundle_del_p,utc_ApplicationFW_bundle_del_startup,utc_ApplicationFW_bundle_del_cleanup},
	{"utc_ApplicationFW_bundle_del_n",utc_ApplicationFW_bundle_del_n,utc_ApplicationFW_bundle_del_startup,utc_ApplicationFW_bundle_del_cleanup},
	{"utc_ApplicationFW_bundle_del_n2",utc_ApplicationFW_bundle_del_n2,utc_ApplicationFW_bundle_del_startup,utc_ApplicationFW_bundle_del_cleanup},
	{"utc_ApplicationFW_bundle_del_n3",utc_ApplicationFW_bundle_del_n3,utc_ApplicationFW_bundle_del_startup,utc_ApplicationFW_bundle_del_cleanup},
	{"utc_ApplicationFW_bundle_dup_p",utc_ApplicationFW_bundle_dup_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_dup_n",utc_ApplicationFW_bundle_dup_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_encode_p",utc_ApplicationFW_bundle_encode_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_encode_n",utc_ApplicationFW_bundle_encode_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_encode_n2",utc_ApplicationFW_bundle_encode_n2,NULL,NULL},
	{"utc_ApplicationFW_bundle_encode_n3",utc_ApplicationFW_bundle_encode_n3,NULL,NULL},
	{"utc_ApplicationFW_bundle_free_p",utc_ApplicationFW_bundle_free_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_free_n",utc_ApplicationFW_bundle_free_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_count_p",utc_ApplicationFW_bundle_get_count_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_count_n",utc_ApplicationFW_bundle_get_count_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_foreach_p",utc_ApplicationFW_bundle_foreach_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_foreach_n",utc_ApplicationFW_bundle_foreach_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_type_p",utc_ApplicationFW_bundle_get_type_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_type_n",utc_ApplicationFW_bundle_get_type_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_add_str_p",utc_ApplicationFW_bundle_add_str_p,utc_ApplicationFW_bundle_add_str_startup,utc_ApplicationFW_bundle_add_str_cleanup},
	{"utc_ApplicationFW_bundle_add_str_n",utc_ApplicationFW_bundle_add_str_n,utc_ApplicationFW_bundle_add_str_startup,utc_ApplicationFW_bundle_add_str_cleanup},
	{"utc_ApplicationFW_bundle_add_str_n2",utc_ApplicationFW_bundle_add_str_n2,utc_ApplicationFW_bundle_add_str_startup,utc_ApplicationFW_bundle_add_str_cleanup},
	{"utc_ApplicationFW_bundle_add_str_n3",utc_ApplicationFW_bundle_add_str_n3,utc_ApplicationFW_bundle_add_str_startup,utc_ApplicationFW_bundle_add_str_cleanup},
	{"utc_ApplicationFW_bundle_get_str_p",utc_ApplicationFW_bundle_get_str_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_str_n",utc_ApplicationFW_bundle_get_str_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_str_n2",utc_ApplicationFW_bundle_get_str_n2,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_str_n3",utc_ApplicationFW_bundle_get_str_n3,NULL,NULL},
	{"utc_ApplicationFW_bundle_add_byte_p",utc_ApplicationFW_bundle_add_byte_p,utc_ApplicationFW_bundle_add_byte_startup,utc_ApplicationFW_bundle_add_byte_cleanup},
	{"utc_ApplicationFW_bundle_add_byte_n",utc_ApplicationFW_bundle_add_byte_n,utc_ApplicationFW_bundle_add_byte_startup,utc_ApplicationFW_bundle_add_byte_cleanup},
	{"utc_ApplicationFW_bundle_add_byte_n2",utc_ApplicationFW_bundle_add_byte_n2,utc_ApplicationFW_bundle_add_byte_startup,utc_ApplicationFW_bundle_add_byte_cleanup},
	{"utc_ApplicationFW_bundle_get_byte_p",utc_ApplicationFW_bundle_get_byte_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_byte_n",utc_ApplicationFW_bundle_get_byte_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_byte_n2",utc_ApplicationFW_bundle_get_byte_n2,NULL,NULL},
	{"utc_ApplicationFW_bundle_get_byte_n3",utc_ApplicationFW_bundle_get_byte_n3,NULL,NULL},
	{"utc_ApplicationFW_bundle_add_str_array_p",utc_ApplicationFW_bundle_add_str_array_p,utc_ApplicationFW_bundle_add_str_array_startup,utc_ApplicationFW_bundle_add_str_array_cleanup},
	{"utc_ApplicationFW_bundle_add_str_array_n",utc_ApplicationFW_bundle_add_str_array_n,utc_ApplicationFW_bundle_add_str_array_startup,utc_ApplicationFW_bundle_add_str_array_cleanup},
	{"utc_ApplicationFW_bundle_add_str_array_n2",utc_ApplicationFW_bundle_add_str_array_n2,utc_ApplicationFW_bundle_add_str_array_startup,utc_ApplicationFW_bundle_add_str_array_cleanup},
	{"utc_ApplicationFW_bundle_add_str_array_n3",utc_ApplicationFW_bundle_add_str_array_n3,utc_ApplicationFW_bundle_add_str_array_startup,utc_ApplicationFW_bundle_add_str_array_cleanup},
	{"utc_ApplicationFW_bundle_get_str_array_p",utc_ApplicationFW_bundle_get_str_array_p,utc_ApplicationFW_bundle_get_str_array_startup,utc_ApplicationFW_bundle_get_str_array_cleanup},
	{"utc_ApplicationFW_bundle_get_str_array_n",utc_ApplicationFW_bundle_get_str_array_n,utc_ApplicationFW_bundle_get_str_array_startup,utc_ApplicationFW_bundle_get_str_array_cleanup},
	{"utc_ApplicationFW_bundle_get_str_array_n2",utc_ApplicationFW_bundle_get_str_array_n2,utc_ApplicationFW_bundle_get_str_array_startup,utc_ApplicationFW_bundle_get_str_array_cleanup},
	{"utc_ApplicationFW_bundle_get_str_array_n3",utc_ApplicationFW_bundle_get_str_array_n3,utc_ApplicationFW_bundle_get_str_array_startup,utc_ApplicationFW_bundle_get_str_array_cleanup},
	{"utc_ApplicationFW_bundle_keyval_get_type_p",utc_ApplicationFW_bundle_keyval_get_type_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_keyval_get_type_n",utc_ApplicationFW_bundle_keyval_get_type_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_keyval_type_is_array_p",utc_ApplicationFW_bundle_keyval_type_is_array_p,NULL,NULL},
	{"utc_ApplicationFW_bundle_keyval_type_is_array_n",utc_ApplicationFW_bundle_keyval_type_is_array_n,NULL,NULL},
	{"utc_bundle_keyval_get_basic_val_p",utc_bundle_keyval_get_basic_val_p,NULL,NULL},
	{"utc_bundle_keyval_get_basic_val_n",utc_bundle_keyval_get_basic_val_n,NULL,NULL},
	{"utc_bundle_keyval_get_array_val_p",utc_bundle_keyval_get_array_val_p,NULL,NULL},
	{"utc_bundle_keyval_get_array_val_n",utc_bundle_keyval_get_array_val_n,NULL,NULL},
	{"utc_ApplicationFW_bundle_add_byte_array_p",utc_ApplicationFW_bundle_add_byte_array_p,utc_ApplicationFW_bundle_add_byte_array_startup,utc_ApplicationFW_bundle_add_byte_array_cleanup},
	{"utc_ApplicationFW_bundle_add_byte_array_n1",utc_ApplicationFW_bundle_add_byte_array_n1,utc_ApplicationFW_bundle_add_byte_array_startup,utc_ApplicationFW_bundle_add_byte_array_cleanup},
	{"utc_ApplicationFW_bundle_add_byte_array_n2",utc_ApplicationFW_bundle_add_byte_array_n2,utc_ApplicationFW_bundle_add_byte_array_startup,utc_ApplicationFW_bundle_add_byte_array_cleanup},
	{"utc_ApplicationFW_bundle_set_byte_array_element_p",utc_ApplicationFW_bundle_set_byte_array_element_p,utc_ApplicationFW_bundle_set_byte_array_element_startup,utc_ApplicationFW_bundle_set_byte_array_element_cleanup},
	{"utc_ApplicationFW_bundle_set_byte_array_element_n",utc_ApplicationFW_bundle_set_byte_array_element_n,utc_ApplicationFW_bundle_set_byte_array_element_startup,utc_ApplicationFW_bundle_set_byte_array_element_cleanup},
	{"utc_ApplicationFW_bundle_get_byte_array_p",utc_ApplicationFW_bundle_get_byte_array_p,utc_ApplicationFW_bundle_get_byte_array_startup,utc_ApplicationFW_bundle_get_byte_array_cleanup},
	{"utc_ApplicationFW_bundle_get_byte_array_n",utc_ApplicationFW_bundle_get_byte_array_n,utc_ApplicationFW_bundle_get_byte_array_startup,utc_ApplicationFW_bundle_get_byte_array_cleanup},
	{NULL, NULL}
};

#endif // __TCT_BUNDLE-NATIVE_H__
