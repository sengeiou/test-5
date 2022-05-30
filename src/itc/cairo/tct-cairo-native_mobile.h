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
#ifndef __TCT_CAIRO-NATIVE_H__
#define __TCT_CAIRO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_cairo_startup(void);
extern void ITs_cairo_cleanup(void);

extern int ITc_cairo_evas_gl_device_create_p(void);
extern int ITc_cairo_gl_surface_create_for_evas_gl_p(void);
extern int ITc_cairo_evas_gl_device_get_gl_p(void);
extern int ITc_cairo_evas_gl_device_get_context_p(void);
extern int ITc_cairo_gl_surface_create_p(void);
extern int ITc_cairo_gl_surface_create_for_texture_p(void);
extern int ITc_cairo_gl_surface_get_width_p(void);
extern int ITc_cairo_gl_surface_get_height_p(void);
extern int ITc_cairo_gl_device_set_thread_aware_p(void);

testcase tc_array[] = {
	{"ITc_cairo_evas_gl_device_create_p",ITc_cairo_evas_gl_device_create_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_surface_create_for_evas_gl_p",ITc_cairo_gl_surface_create_for_evas_gl_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_evas_gl_device_get_gl_p",ITc_cairo_evas_gl_device_get_gl_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_evas_gl_device_get_context_p",ITc_cairo_evas_gl_device_get_context_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_surface_create_p",ITc_cairo_gl_surface_create_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_surface_create_for_texture_p",ITc_cairo_gl_surface_create_for_texture_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_surface_get_width_p",ITc_cairo_gl_surface_get_width_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_surface_get_height_p",ITc_cairo_gl_surface_get_height_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{"ITc_cairo_gl_device_set_thread_aware_p",ITc_cairo_gl_device_set_thread_aware_p,ITs_cairo_startup,ITs_cairo_cleanup},
	{NULL, NULL}
};

#endif // __TCT_CAIRO-NATIVE_H__
