//
// Copyright (c) 2014-2020 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_PRIVILEGE-INFO-NATIVE_H__
#define __TCT_PRIVILEGE-INFO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_privilege_info_startup(void);
extern int utc_privilege_info_get_display_name_p1(void);
extern int utc_privilege_info_get_display_name_p2(void);
extern int utc_privilege_info_get_display_name_n1(void);
extern int utc_privilege_info_get_display_name_n2(void);
extern int utc_privilege_info_get_description_p1(void);
extern int utc_privilege_info_get_description_p2(void);
extern int utc_privilege_info_get_description_n1(void);
extern int utc_privilege_info_get_description_n2(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_p1(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_p2(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_n1(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_n2(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_n3(void);
extern int utc_privilege_info_get_display_name_by_pkgtype_n4(void);
extern int utc_privilege_info_get_description_by_pkgtype_p1(void);
extern int utc_privilege_info_get_description_by_pkgtype_p2(void);
extern int utc_privilege_info_get_description_by_pkgtype_n1(void);
extern int utc_privilege_info_get_description_by_pkgtype_n2(void);
extern int utc_privilege_info_get_description_by_pkgtype_n3(void);
extern int utc_privilege_info_get_description_by_pkgtype_n4(void);
extern int utc_privilege_info_get_privacy_display_name_p(void);
extern int utc_privilege_info_get_privacy_display_name_n1(void);
extern int utc_privilege_info_get_privacy_display_name_n2(void);
extern int utc_privilege_info_get_privilege_info_list_p1(void);
extern int utc_privilege_info_get_privilege_info_list_p2(void);
extern int utc_privilege_info_get_privilege_info_list_p3(void);
extern int utc_privilege_info_get_privilege_info_list_p4(void);
extern int utc_privilege_info_get_privilege_info_list_p5(void);
extern int utc_privilege_info_get_privilege_info_list_n1(void);
extern int utc_privilege_info_free_privilege_info_list_p1(void);
extern int utc_privilege_info_free_privilege_info_list_n1(void);

testcase tc_array[] = {
	{"utc_privilege_info_get_display_name_p1",utc_privilege_info_get_display_name_p1,NULL,NULL},
	{"utc_privilege_info_get_display_name_p2",utc_privilege_info_get_display_name_p2,NULL,NULL},
	{"utc_privilege_info_get_display_name_n1",utc_privilege_info_get_display_name_n1,NULL,NULL},
	{"utc_privilege_info_get_display_name_n2",utc_privilege_info_get_display_name_n2,NULL,NULL},
	{"utc_privilege_info_get_description_p1",utc_privilege_info_get_description_p1,NULL,NULL},
	{"utc_privilege_info_get_description_p2",utc_privilege_info_get_description_p2,NULL,NULL},
	{"utc_privilege_info_get_description_n1",utc_privilege_info_get_description_n1,NULL,NULL},
	{"utc_privilege_info_get_description_n2",utc_privilege_info_get_description_n2,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_p1",utc_privilege_info_get_display_name_by_pkgtype_p1,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_p2",utc_privilege_info_get_display_name_by_pkgtype_p2,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_n1",utc_privilege_info_get_display_name_by_pkgtype_n1,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_n2",utc_privilege_info_get_display_name_by_pkgtype_n2,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_n3",utc_privilege_info_get_display_name_by_pkgtype_n3,NULL,NULL},
	{"utc_privilege_info_get_display_name_by_pkgtype_n4",utc_privilege_info_get_display_name_by_pkgtype_n4,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_p1",utc_privilege_info_get_description_by_pkgtype_p1,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_p2",utc_privilege_info_get_description_by_pkgtype_p2,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_n1",utc_privilege_info_get_description_by_pkgtype_n1,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_n2",utc_privilege_info_get_description_by_pkgtype_n2,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_n3",utc_privilege_info_get_description_by_pkgtype_n3,NULL,NULL},
	{"utc_privilege_info_get_description_by_pkgtype_n4",utc_privilege_info_get_description_by_pkgtype_n4,NULL,NULL},
	{"utc_privilege_info_get_privacy_display_name_p",utc_privilege_info_get_privacy_display_name_p,utc_privilege_info_startup,NULL},
	{"utc_privilege_info_get_privacy_display_name_n1",utc_privilege_info_get_privacy_display_name_n1,utc_privilege_info_startup,NULL},
	{"utc_privilege_info_get_privacy_display_name_n2",utc_privilege_info_get_privacy_display_name_n2,utc_privilege_info_startup,NULL},
	{"utc_privilege_info_get_privilege_info_list_p1", utc_privilege_info_get_privilege_info_list_p1,NULL,NULL},
	{"utc_privilege_info_get_privilege_info_list_p2", utc_privilege_info_get_privilege_info_list_p2,NULL,NULL},
	{"utc_privilege_info_get_privilege_info_list_p3", utc_privilege_info_get_privilege_info_list_p3,NULL,NULL},
	{"utc_privilege_info_get_privilege_info_list_p4", utc_privilege_info_get_privilege_info_list_p4,NULL,NULL},
	{"utc_privilege_info_get_privilege_info_list_p5", utc_privilege_info_get_privilege_info_list_p5,NULL,NULL},
	{"utc_privilege_info_get_privilege_info_list_n1", utc_privilege_info_get_privilege_info_list_n1,NULL,NULL},
	{"utc_privilege_info_free_privilege_info_list_p1", utc_privilege_info_free_privilege_info_list_p1,NULL,NULL},
	{"utc_privilege_info_free_privilege_info_list_n1", utc_privilege_info_free_privilege_info_list_n1,NULL,NULL},
	{NULL, NULL}
};

#endif // __TCT_PRIVILEGE-INFO-NATIVE_H__
