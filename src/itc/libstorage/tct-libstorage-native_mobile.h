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
#ifndef __TCT_LIBSTORAGE-NATIVE_H__
#define __TCT_LIBSTORAGE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_storage_startup(void);
extern void ITs_storage_cleanup(void);

extern int ITc_libstorage_get_internal_memory_size_p(void);
extern int ITc_libstorage_get_external_memory_size_p(void);
extern int ITc_libstorage_foreach_device_supported_p(void);
extern int ITc_libstorage_get_directory_p(void);
extern int ITc_libstorage_get_root_directory_p(void);
extern int ITc_libstorage_get_type_p(void);
extern int ITc_libstorage_get_state_p(void);
extern int ITc_libstorage_get_total_space_p(void);
extern int ITc_libstorage_get_available_space_p(void);
extern int ITc_libstorage_set_unset_state_changed_cb_p(void);
extern int ITc_libstorage_storage_set_unset_changed_cb_p(void);
extern int ITc_libstorage_storage_get_type_dev_p(void);

testcase tc_array[] = {
	{"ITc_libstorage_get_internal_memory_size_p",ITc_libstorage_get_internal_memory_size_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_external_memory_size_p",ITc_libstorage_get_external_memory_size_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_foreach_device_supported_p",ITc_libstorage_foreach_device_supported_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_directory_p",ITc_libstorage_get_directory_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_root_directory_p",ITc_libstorage_get_root_directory_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_type_p",ITc_libstorage_get_type_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_state_p",ITc_libstorage_get_state_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_total_space_p",ITc_libstorage_get_total_space_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_get_available_space_p",ITc_libstorage_get_available_space_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_set_unset_state_changed_cb_p",ITc_libstorage_set_unset_state_changed_cb_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_storage_set_unset_changed_cb_p",ITc_libstorage_storage_set_unset_changed_cb_p,ITs_storage_startup,ITs_storage_cleanup},
	{"ITc_libstorage_storage_get_type_dev_p",ITc_libstorage_storage_get_type_dev_p,ITs_storage_startup,ITs_storage_cleanup},
	{NULL, NULL}
};

#endif // __TCT_LIBSTORAGE-NATIVE_H__
