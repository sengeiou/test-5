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
#ifndef __TCT_LIBSTORAGE64-NATIVE_H__
#define __TCT_LIBSTORAGE64-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_storage_startup(void);

extern int utc_system_storage_get_internal_memory_size_p(void);
extern int utc_system_storage_get_internal_memory_size_n(void);
extern int utc_system_storage_get_external_memory_size_p(void);
extern int utc_system_storage_get_external_memory_size_n(void);
extern int utc_storage_foreach_device_supported_p(void);
extern int utc_storage_foreach_device_supported_n(void);
extern int utc_storage_get_root_directory_p(void);
extern int utc_storage_get_root_directory_n_1(void);
extern int utc_storage_get_root_directory_n_2(void);
extern int utc_storage_get_directory_p(void);
extern int utc_storage_get_directory_n_1(void);
extern int utc_storage_get_directory_n_2(void);
extern int utc_storage_get_directory_n_3(void);
extern int utc_storage_get_type_p(void);
extern int utc_storage_get_type_n_1(void);
extern int utc_storage_get_type_n_2(void);
extern int utc_storage_get_state_p(void);
extern int utc_storage_get_state_n_1(void);
extern int utc_storage_get_state_n_2(void);
extern int utc_storage_get_total_space_p(void);
extern int utc_storage_get_total_space_n_1(void);
extern int utc_storage_get_total_space_n_2(void);
extern int utc_storage_get_available_space_p(void);
extern int utc_storage_get_available_space_n_1(void);
extern int utc_storage_get_available_space_n_2(void);
extern int utc_storage_set_state_changed_cb_p(void);
extern int utc_storage_set_state_changed_cb_n_1(void);
extern int utc_storage_set_state_changed_cb_n_2(void);
extern int utc_storage_unset_state_changed_cb_p(void);
extern int utc_storage_unset_state_changed_cb_n_1(void);
extern int utc_storage_unset_state_changed_cb_n_2(void);

testcase tc_array[] = {
	{"utc_system_storage_get_internal_memory_size_p",utc_system_storage_get_internal_memory_size_p,NULL,NULL},
	{"utc_system_storage_get_internal_memory_size_n",utc_system_storage_get_internal_memory_size_n,NULL,NULL},
	{"utc_system_storage_get_external_memory_size_p",utc_system_storage_get_external_memory_size_p,NULL,NULL},
	{"utc_system_storage_get_external_memory_size_n",utc_system_storage_get_external_memory_size_n,NULL,NULL},
	{"utc_storage_foreach_device_supported_p",utc_storage_foreach_device_supported_p,utc_storage_startup,NULL},
	{"utc_storage_foreach_device_supported_n",utc_storage_foreach_device_supported_n,utc_storage_startup,NULL},
	{"utc_storage_get_root_directory_p",utc_storage_get_root_directory_p,utc_storage_startup,NULL},
	{"utc_storage_get_root_directory_n_1",utc_storage_get_root_directory_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_root_directory_n_2",utc_storage_get_root_directory_n_2,utc_storage_startup,NULL},
	{"utc_storage_get_directory_p",utc_storage_get_directory_p,utc_storage_startup,NULL},
	{"utc_storage_get_directory_n_1",utc_storage_get_directory_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_directory_n_2",utc_storage_get_directory_n_2,utc_storage_startup,NULL},
	{"utc_storage_get_directory_n_3",utc_storage_get_directory_n_3,utc_storage_startup,NULL},
	{"utc_storage_get_type_p",utc_storage_get_type_p,utc_storage_startup,NULL},
	{"utc_storage_get_type_n_1",utc_storage_get_type_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_type_n_2",utc_storage_get_type_n_2,utc_storage_startup,NULL},
	{"utc_storage_get_state_p",utc_storage_get_state_p,utc_storage_startup,NULL},
	{"utc_storage_get_state_n_1",utc_storage_get_state_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_state_n_2",utc_storage_get_state_n_2,utc_storage_startup,NULL},
	{"utc_storage_get_total_space_p",utc_storage_get_total_space_p,utc_storage_startup,NULL},
	{"utc_storage_get_total_space_n_1",utc_storage_get_total_space_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_total_space_n_2",utc_storage_get_total_space_n_2,utc_storage_startup,NULL},
	{"utc_storage_get_available_space_p",utc_storage_get_available_space_p,utc_storage_startup,NULL},
	{"utc_storage_get_available_space_n_1",utc_storage_get_available_space_n_1,utc_storage_startup,NULL},
	{"utc_storage_get_available_space_n_2",utc_storage_get_available_space_n_2,utc_storage_startup,NULL},
	{"utc_storage_set_state_changed_cb_p",utc_storage_set_state_changed_cb_p,utc_storage_startup,NULL},
	{"utc_storage_set_state_changed_cb_n_1",utc_storage_set_state_changed_cb_n_1,utc_storage_startup,NULL},
	{"utc_storage_set_state_changed_cb_n_2",utc_storage_set_state_changed_cb_n_2,utc_storage_startup,NULL},
	{"utc_storage_unset_state_changed_cb_p",utc_storage_unset_state_changed_cb_p,utc_storage_startup,NULL},
	{"utc_storage_unset_state_changed_cb_n_1",utc_storage_unset_state_changed_cb_n_1,utc_storage_startup,NULL},
	{"utc_storage_unset_state_changed_cb_n_2",utc_storage_unset_state_changed_cb_n_2,utc_storage_startup,NULL},
	{NULL, NULL}
};

#endif // __TCT_LIBSTORAGE64-NATIVE_H__
