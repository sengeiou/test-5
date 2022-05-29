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

extern void utc_sync_manager_startup(void);
extern void utc_sync_manager_cleanup(void);

extern int utc_sync_adapter_set_callbacks_p(void);
extern int utc_sync_adapter_set_callbacks_n(void);
extern int utc_sync_adapter_set_callbacks_n2(void);
extern int utc_sync_manager_on_demand_sync_job_p(void);
extern int utc_sync_manager_on_demand_sync_job_n(void);
extern int utc_sync_manager_on_demand_sync_job_n2(void);
extern int utc_sync_manager_on_demand_sync_job_p2(void);
extern int utc_sync_manager_on_demand_sync_job_n3(void);
extern int utc_sync_manager_on_demand_sync_job_n4(void);
extern int utc_sync_manager_add_periodic_sync_job_p(void);
extern int utc_sync_manager_add_periodic_sync_job_n(void);
extern int utc_sync_manager_add_periodic_sync_job_n2(void);
extern int utc_sync_manager_add_periodic_sync_job_n3(void);
extern int utc_sync_manager_add_periodic_sync_job_p2(void);
extern int utc_sync_manager_add_periodic_sync_job_n4(void);
extern int utc_sync_manager_add_periodic_sync_job_n5(void);
extern int utc_sync_manager_add_data_change_sync_job_p(void);
extern int utc_sync_manager_add_data_change_sync_job_n(void);
extern int utc_sync_manager_add_data_change_sync_job_n2(void);
extern int utc_sync_manager_add_data_change_sync_job_p2(void);
extern int utc_sync_manager_add_data_change_sync_job_n3(void);
extern int utc_sync_manager_add_data_change_sync_job_n4(void);
extern int utc_sync_manager_remove_sync_job_p(void);
extern int utc_sync_manager_remove_sync_job_p2(void);
extern int utc_sync_manager_remove_sync_job_n(void);
extern int utc_sync_manager_foreach_sync_job_p(void);
extern int utc_sync_manager_foreach_sync_job_n(void);

testcase tc_array[] = {
	{"utc_sync_adapter_set_callbacks_p",utc_sync_adapter_set_callbacks_p,NULL,NULL},
	{"utc_sync_adapter_set_callbacks_n",utc_sync_adapter_set_callbacks_n,NULL,NULL},
	{"utc_sync_adapter_set_callbacks_n2",utc_sync_adapter_set_callbacks_n2,NULL,NULL},
	{"utc_sync_manager_on_demand_sync_job_p",utc_sync_manager_on_demand_sync_job_p,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_on_demand_sync_job_n",utc_sync_manager_on_demand_sync_job_n,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_on_demand_sync_job_n2",utc_sync_manager_on_demand_sync_job_n2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_on_demand_sync_job_p2",utc_sync_manager_on_demand_sync_job_p2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_on_demand_sync_job_n3",utc_sync_manager_on_demand_sync_job_n3,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_on_demand_sync_job_n4",utc_sync_manager_on_demand_sync_job_n4,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_p",utc_sync_manager_add_periodic_sync_job_p,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_n",utc_sync_manager_add_periodic_sync_job_n,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_n2",utc_sync_manager_add_periodic_sync_job_n2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_n3",utc_sync_manager_add_periodic_sync_job_n3,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_p2",utc_sync_manager_add_periodic_sync_job_p2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_n4",utc_sync_manager_add_periodic_sync_job_n4,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_periodic_sync_job_n5",utc_sync_manager_add_periodic_sync_job_n5,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_p",utc_sync_manager_add_data_change_sync_job_p,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_n",utc_sync_manager_add_data_change_sync_job_n,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_n2",utc_sync_manager_add_data_change_sync_job_n2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_p2",utc_sync_manager_add_data_change_sync_job_p2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_n3",utc_sync_manager_add_data_change_sync_job_n3,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_add_data_change_sync_job_n4",utc_sync_manager_add_data_change_sync_job_n4,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_remove_sync_job_p",utc_sync_manager_remove_sync_job_p,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_remove_sync_job_p2",utc_sync_manager_remove_sync_job_p2,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_remove_sync_job_n",utc_sync_manager_remove_sync_job_n,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_foreach_sync_job_p",utc_sync_manager_foreach_sync_job_p,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{"utc_sync_manager_foreach_sync_job_n",utc_sync_manager_foreach_sync_job_n,utc_sync_manager_startup,utc_sync_manager_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SYNC-MANAGER-NATIVE_H__
