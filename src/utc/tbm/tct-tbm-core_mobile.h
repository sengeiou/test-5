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

extern void utc_tbm_surface_create_startup(void);
extern void utc_tbm_surface_create_cleanup(void);
extern void utc_tbm_surface_info_startup(void);
extern void utc_tbm_surface_info_cleanup(void);
extern void utc_tbm_surface_map_startup(void);
extern void utc_tbm_surface_map_cleanup(void);

extern int utc_tbm_surface_create_p(void);
extern int utc_tbm_surface_create_n(void);
extern int utc_tbm_surface_destroy_p(void);
extern int utc_tbm_surface_destroy_n(void);
extern int utc_tbm_surface_get_info_p(void);
extern int utc_tbm_surface_get_info_n(void);
extern int utc_tbm_surface_get_width_p(void);
extern int utc_tbm_surface_get_width_n(void);
extern int utc_tbm_surface_get_height_p(void);
extern int utc_tbm_surface_get_height_n(void);
extern int utc_tbm_surface_get_format_p(void);
extern int utc_tbm_surface_get_format_n(void);
extern int utc_tbm_surface_query_formats_p(void);
extern int utc_tbm_surface_map_p(void);
extern int utc_tbm_surface_map_n(void);
extern int utc_tbm_surface_unmap_p(void);
extern int utc_tbm_surface_unmap_n(void);

testcase tc_array[] = {
	{"utc_tbm_surface_create_p",utc_tbm_surface_create_p,utc_tbm_surface_create_startup,utc_tbm_surface_create_cleanup},
	{"utc_tbm_surface_create_n",utc_tbm_surface_create_n,utc_tbm_surface_create_startup,utc_tbm_surface_create_cleanup},
	{"utc_tbm_surface_destroy_p",utc_tbm_surface_destroy_p,utc_tbm_surface_create_startup,utc_tbm_surface_create_cleanup},
	{"utc_tbm_surface_destroy_n",utc_tbm_surface_destroy_n,utc_tbm_surface_create_startup,utc_tbm_surface_create_cleanup},
	{"utc_tbm_surface_get_info_p",utc_tbm_surface_get_info_p,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_info_n",utc_tbm_surface_get_info_n,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_width_p",utc_tbm_surface_get_width_p,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_width_n",utc_tbm_surface_get_width_n,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_height_p",utc_tbm_surface_get_height_p,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_height_n",utc_tbm_surface_get_height_n,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_format_p",utc_tbm_surface_get_format_p,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_get_format_n",utc_tbm_surface_get_format_n,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_query_formats_p",utc_tbm_surface_query_formats_p,utc_tbm_surface_info_startup,utc_tbm_surface_info_cleanup},
	{"utc_tbm_surface_map_p",utc_tbm_surface_map_p,utc_tbm_surface_map_startup,utc_tbm_surface_map_cleanup},
	{"utc_tbm_surface_map_n",utc_tbm_surface_map_n,utc_tbm_surface_map_startup,utc_tbm_surface_map_cleanup},
	{"utc_tbm_surface_unmap_p",utc_tbm_surface_unmap_p,utc_tbm_surface_map_startup,utc_tbm_surface_map_cleanup},
	{"utc_tbm_surface_unmap_n",utc_tbm_surface_unmap_n,utc_tbm_surface_map_startup,utc_tbm_surface_map_cleanup},
	{NULL, NULL}
};

#endif // __TCT_TBM-NATIVE_H__
