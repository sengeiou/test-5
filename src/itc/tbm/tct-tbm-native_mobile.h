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
#ifndef __TCT_TBM-NATIVE_H__
#define __TCT_TBM-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_tbm_startup(void);
extern void ITs_tbm_cleanup(void);

extern int ITc_tbm_surface_create_destroy_p(void);
extern int ITc_tbm_surface_map_unmap_p(void);
extern int ITc_tbm_surface_get_width_p(void);
extern int ITc_tbm_surface_get_height_p(void);
extern int ITc_tbm_surface_query_formats_p(void);
extern int ITc_tbm_surface_get_info_p(void);
extern int ITc_tbm_surface_get_format_p(void);

testcase tc_array[] = {
	{"ITc_tbm_surface_create_destroy_p",ITc_tbm_surface_create_destroy_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_map_unmap_p",ITc_tbm_surface_map_unmap_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_get_width_p",ITc_tbm_surface_get_width_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_get_height_p",ITc_tbm_surface_get_height_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_query_formats_p",ITc_tbm_surface_query_formats_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_get_info_p",ITc_tbm_surface_get_info_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{"ITc_tbm_surface_get_format_p",ITc_tbm_surface_get_format_p,ITs_tbm_startup,ITs_tbm_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TBM-NATIVE_H__
