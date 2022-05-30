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
#ifndef __TCT_MIME-TYPE-NATIVE_H__
#define __TCT_MIME-TYPE-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void utc_mime_type_get_mime_type_startup(void);
extern void utc_mime_type_get_mime_type_cleanup(void);
extern void utc_mime_type_get_mime_type_for_file_startup(void);
extern void utc_mime_type_get_mime_type_for_file_cleanup(void);
extern void utc_mime_type_get_mime_type_for_data_startup(void);
extern void utc_mime_type_get_mime_type_for_data_cleanup(void);

extern int utc_mime_type_get_mime_type_p1(void);
extern int utc_mime_type_get_mime_type_p2(void);
extern int utc_mime_type_get_mime_type_p3(void);
extern int utc_mime_type_get_mime_type_p4(void);
extern int utc_mime_type_get_mime_type_p5(void);
extern int utc_mime_type_get_mime_type_p6(void);
extern int utc_mime_type_get_mime_type_n1(void);
extern int utc_mime_type_get_mime_type_n2(void);
extern int utc_mime_type_get_mime_type_n3(void);
extern int utc_mime_type_get_file_extension_p1(void);
extern int utc_mime_type_get_file_extension_p2(void);
extern int utc_mime_type_get_file_extension_n1(void);
extern int utc_mime_type_get_file_extension_n2(void);
extern int utc_mime_type_get_file_extension_n3(void);
extern int utc_mime_type_get_file_extension_n4(void);
extern int utc_mime_type_get_mime_type_for_file_p1(void);
extern int utc_mime_type_get_mime_type_for_file_n1(void);
extern int utc_mime_type_get_mime_type_for_file_n2(void);
extern int utc_mime_type_get_mime_type_for_file_n3(void);
extern int utc_mime_type_get_mime_type_for_data_p1(void);
extern int utc_mime_type_get_mime_type_for_data_n1(void);
extern int utc_mime_type_get_mime_type_for_data_n2(void);


testcase tc_array[] = {
	{"utc_mime_type_get_mime_type_p1",utc_mime_type_get_mime_type_p1,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_p2",utc_mime_type_get_mime_type_p2,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_p3",utc_mime_type_get_mime_type_p3,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_p4",utc_mime_type_get_mime_type_p4,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_p5",utc_mime_type_get_mime_type_p5,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_p6",utc_mime_type_get_mime_type_p6,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_n1",utc_mime_type_get_mime_type_n1,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_n2",utc_mime_type_get_mime_type_n2,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_n3",utc_mime_type_get_mime_type_n3,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_p1",utc_mime_type_get_file_extension_p1,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_p2",utc_mime_type_get_file_extension_p2,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_n1",utc_mime_type_get_file_extension_n1,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_n2",utc_mime_type_get_file_extension_n2,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_n3",utc_mime_type_get_file_extension_n3,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_file_extension_n4",utc_mime_type_get_file_extension_n4,utc_mime_type_get_mime_type_startup,utc_mime_type_get_mime_type_cleanup},
	{"utc_mime_type_get_mime_type_for_file_p1",utc_mime_type_get_mime_type_for_file_p1,utc_mime_type_get_mime_type_for_file_startup,utc_mime_type_get_mime_type_for_file_cleanup},
	{"utc_mime_type_get_mime_type_for_file_n1",utc_mime_type_get_mime_type_for_file_n1,utc_mime_type_get_mime_type_for_file_startup,utc_mime_type_get_mime_type_for_file_cleanup},
	{"utc_mime_type_get_mime_type_for_file_n2",utc_mime_type_get_mime_type_for_file_n2,utc_mime_type_get_mime_type_for_file_startup,utc_mime_type_get_mime_type_for_file_cleanup},
	{"utc_mime_type_get_mime_type_for_file_n3",utc_mime_type_get_mime_type_for_file_n3,utc_mime_type_get_mime_type_for_file_startup,utc_mime_type_get_mime_type_for_file_cleanup},
	{"utc_mime_type_get_mime_type_for_data_p1",utc_mime_type_get_mime_type_for_data_p1,utc_mime_type_get_mime_type_for_data_startup,utc_mime_type_get_mime_type_for_data_cleanup},
	{"utc_mime_type_get_mime_type_for_data_n1",utc_mime_type_get_mime_type_for_data_n1,utc_mime_type_get_mime_type_for_data_startup,utc_mime_type_get_mime_type_for_data_cleanup},
	{"utc_mime_type_get_mime_type_for_data_n2",utc_mime_type_get_mime_type_for_data_n2,utc_mime_type_get_mime_type_for_data_startup,utc_mime_type_get_mime_type_for_data_cleanup},
	{NULL, NULL}
};

#endif // __TCT_MIME-TYPE-NATIVE_H__
