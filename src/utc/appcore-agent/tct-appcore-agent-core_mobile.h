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
#ifndef __TCT_APPCORE-AGENT-NATIVE_H__
#define __TCT_APPCORE-AGENT-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"


extern int utc_appcore_agent_service_app_main_p1(void);
extern int utc_appcore_agent_service_app_main_p2(void);
extern int utc_appcore_agent_service_app_main_n1(void);
extern int utc_appcore_agent_service_app_main_n2(void);
extern int utc_appcore_agent_service_app_main_n3(void);
extern int utc_appcore_agent_service_app_exit_p(void);
extern int utc_appcore_agent_service_app_add_event_handler_p1(void);
extern int utc_appcore_agent_service_app_add_event_handler_p2(void);
extern int utc_appcore_agent_service_app_add_event_handler_n(void);
extern int utc_appcore_agent_service_app_remove_event_handler_p(void);
extern int utc_appcore_agent_service_app_remove_event_handler_n(void);

testcase tc_array[] = {
	{"utc_appcore_agent_service_app_main_p1",utc_appcore_agent_service_app_main_p1,NULL,NULL},
	{"utc_appcore_agent_service_app_main_p2",utc_appcore_agent_service_app_main_p2,NULL,NULL},
	{"utc_appcore_agent_service_app_main_n1",utc_appcore_agent_service_app_main_n1,NULL,NULL},
	{"utc_appcore_agent_service_app_main_n2",utc_appcore_agent_service_app_main_n2,NULL,NULL},
	{"utc_appcore_agent_service_app_main_n3",utc_appcore_agent_service_app_main_n3,NULL,NULL},
	{"utc_appcore_agent_service_app_exit_p",utc_appcore_agent_service_app_exit_p,NULL,NULL},
	{"utc_appcore_agent_service_app_add_event_handler_p1",utc_appcore_agent_service_app_add_event_handler_p1,NULL,NULL},
	{"utc_appcore_agent_service_app_add_event_handler_p2",utc_appcore_agent_service_app_add_event_handler_p2,NULL,NULL},
	{"utc_appcore_agent_service_app_add_event_handler_n",utc_appcore_agent_service_app_add_event_handler_n,NULL,NULL},
	{"utc_appcore_agent_service_app_remove_event_handler_p",utc_appcore_agent_service_app_remove_event_handler_p,NULL,NULL},
	{"utc_appcore_agent_service_app_remove_event_handler_n",utc_appcore_agent_service_app_remove_event_handler_n,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_APPCORE-AGENT-NATIVE_H__
