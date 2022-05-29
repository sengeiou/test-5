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
#ifndef __TCT_SDL2-NATIVE_H__
#define __TCT_SDL2-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void setArgument(int argc, char* argv[]);
extern void initSDLApp();

extern int utc_SDL_tizen_app_init_p(void);
extern int utc_SDL_tizen_app_init_n(void);
extern int utc_SDL_tizen_app_init_n2(void);
extern int utc_SDL_tizen_app_init_n3(void);

extern void utc_sdl_startup(void);
extern void utc_sdl_cleanup(void);

extern int utc_SDL_Vulkan_GetInstanceExtensions_p(void);
extern int utc_SDL_Vulkan_GetInstanceExtensions_p2(void);
extern int utc_SDL_Vulkan_GetInstanceExtensions_n(void);
extern int utc_SDL_Vulkan_GetInstanceExtensions_n2(void);
extern int utc_SDL_Vulkan_GetInstanceExtensions_n3(void);
extern int utc_SDL_Vulkan_CreateSurface_p(void);
extern int utc_SDL_Vulkan_CreateSurface_n(void);
extern int utc_SDL_Vulkan_CreateSurface_n2(void);
extern int utc_SDL_Vulkan_CreateSurface_n3(void);
extern int utc_SDL_Vulkan_CreateSurface_n4(void);

testcase tc_array[] = {
	{"utc_SDL_tizen_app_init_p", utc_SDL_tizen_app_init_p, NULL, NULL},
	{"utc_SDL_tizen_app_init_n", utc_SDL_tizen_app_init_n, NULL, NULL},
	{"utc_SDL_tizen_app_init_n2", utc_SDL_tizen_app_init_n2, NULL, NULL},
	{"utc_SDL_tizen_app_init_n3", utc_SDL_tizen_app_init_n3, NULL, NULL},
	{"utc_SDL_Vulkan_GetInstanceExtensions_p",utc_SDL_Vulkan_GetInstanceExtensions_p,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_GetInstanceExtensions_p2",utc_SDL_Vulkan_GetInstanceExtensions_p2,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_GetInstanceExtensions_n",utc_SDL_Vulkan_GetInstanceExtensions_n,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_GetInstanceExtensions_n2",utc_SDL_Vulkan_GetInstanceExtensions_n2,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_GetInstanceExtensions_n3",utc_SDL_Vulkan_GetInstanceExtensions_n3,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_CreateSurface_p",utc_SDL_Vulkan_CreateSurface_p,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_CreateSurface_n",utc_SDL_Vulkan_CreateSurface_n,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_CreateSurface_n2",utc_SDL_Vulkan_CreateSurface_n2,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_CreateSurface_n3",utc_SDL_Vulkan_CreateSurface_n3,utc_sdl_startup,utc_sdl_cleanup},
	{"utc_SDL_Vulkan_CreateSurface_n4",utc_SDL_Vulkan_CreateSurface_n4,utc_sdl_startup,utc_sdl_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SDL2-NATIVE_H__
