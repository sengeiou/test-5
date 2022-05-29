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
#ifndef __TCT_PRIVACY_PRIVILEGE_MANAGER_NATIVE_H__
#define __TCT_PRIVACY_PRIVILEGE_MANAGER_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern int utc_ppm_check_permission_n1(void);
extern int utc_ppm_check_permission_n2(void);
extern int utc_ppm_check_permission_n3(void);
extern int utc_ppm_check_permissions_n1(void);
extern int utc_ppm_check_permissions_n2(void);
extern int utc_ppm_check_permissions_n3(void);
extern int utc_ppm_request_permission_n1(void);
extern int utc_ppm_request_permission_n2(void);
extern int utc_ppm_request_permission_n3(void);
extern int utc_ppm_request_permissions_n1(void);
extern int utc_ppm_request_permissions_n2(void);
extern int utc_ppm_request_permissions_n3(void);

testcase tc_array[] = {
    {"utc_ppm_check_permission_n1", utc_ppm_check_permission_n1, NULL, NULL},
    {"utc_ppm_check_permission_n2", utc_ppm_check_permission_n2, NULL, NULL},
    {"utc_ppm_check_permission_n3", utc_ppm_check_permission_n3, NULL, NULL},
    {"utc_ppm_check_permissions_n1", utc_ppm_check_permissions_n1, NULL, NULL},
    {"utc_ppm_check_permissions_n2", utc_ppm_check_permissions_n2, NULL, NULL},
    {"utc_ppm_check_permissions_n3", utc_ppm_check_permissions_n3, NULL, NULL},
    {"utc_ppm_request_permission_n1", utc_ppm_request_permission_n1, NULL, NULL},
    {"utc_ppm_request_permission_n2", utc_ppm_request_permission_n2, NULL, NULL},
    {"utc_ppm_request_permission_n3", utc_ppm_request_permission_n3, NULL, NULL},
    {"utc_ppm_request_permissions_n1", utc_ppm_request_permissions_n1, NULL, NULL},
    {"utc_ppm_request_permissions_n2", utc_ppm_request_permissions_n2, NULL, NULL},
    {"utc_ppm_request_permissions_n3", utc_ppm_request_permissions_n3, NULL, NULL},
    {NULL, NULL}
};

#endif // __TCT_PRIVACY_PRIVILEGE_MANAGER_NATIVE_H__
