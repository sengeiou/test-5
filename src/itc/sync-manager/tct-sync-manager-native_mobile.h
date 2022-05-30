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
#ifndef __TCT_SYNC-MANAGER-NATIVE_H__
#define __TCT_SYNC-MANAGER-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_sync_manager_startup(void);
extern void ITs_sync_manager_cleanup(void);

extern int ITc_sync_manager_sync_adapter_set_unset_callbacks_p(void);
extern int ITc_sync_manager_on_demand_sync_job_p(void);
extern int ITc_sync_manager_add_remove_periodic_sync_job_p(void);
extern int ITc_sync_manager_add_remove_data_change_sync_job_p(void);
extern int ITc_sync_manager_foreach_sync_job_p(void);

testcase tc_array[] = {
	{"ITc_sync_manager_sync_adapter_set_unset_callbacks_p",ITc_sync_manager_sync_adapter_set_unset_callbacks_p,ITs_sync_manager_startup,ITs_sync_manager_cleanup},
	{"ITc_sync_manager_on_demand_sync_job_p",ITc_sync_manager_on_demand_sync_job_p,ITs_sync_manager_startup,ITs_sync_manager_cleanup},
	{"ITc_sync_manager_add_remove_periodic_sync_job_p",ITc_sync_manager_add_remove_periodic_sync_job_p,ITs_sync_manager_startup,ITs_sync_manager_cleanup},
	{"ITc_sync_manager_add_remove_data_change_sync_job_p",ITc_sync_manager_add_remove_data_change_sync_job_p,ITs_sync_manager_startup,ITs_sync_manager_cleanup},
	{"ITc_sync_manager_foreach_sync_job_p",ITc_sync_manager_foreach_sync_job_p,ITs_sync_manager_startup,ITs_sync_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SYNC-MANAGER-NATIVE_H__
