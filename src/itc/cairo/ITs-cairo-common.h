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
#ifndef _ITS_CAIRO_COMMON_H_
#define _ITS_CAIRO_COMMON_H_
#include "tct_common.h"
#include <cairo.h>
#include <cairo-evas-gl.h>
#include <Evas_GL.h>
#include <Elementary.h>
#include <stdbool.h>
#include <system_info.h>
#include <tizen.h>

//Add test package related includes here
#define API_NAMESPACE		"ITC_Cairo"
#define WIDTH				300
#define HEIGHT				300
#define CAIRO_FEATURE		"http://tizen.org/feature/opengles.version.2_0"

#define START_TEST {\
	FPRINTF("[Line No : %d][%s]Starting test : %s\\n", __LINE__,API_NAMESPACE, __FUNCTION__);\
	if (!g_nEvas_state) {\
		FPRINTF("[Line No : %d][%s] Precondition failed in startup \\n", __LINE__,API_NAMESPACE);\
		return 1;\
	}\
	CHECK_FEATURE;\
}

#define PRINT_RESULT_CAIRO(nRetVal, API, bIsSupported) {\
	if(!bIsSupported) {\
		if (nRetVal == TIZEN_ERROR_NOT_SUPPORTED)\
		{\
			FPRINTF( "[Line : %d] [%s]  %s passed \\n",__LINE__, API_NAMESPACE, API);\
			return 0;\
		}\
		else {\
			FPRINTF( " [Line : %d] [%s] %s failed. Mismatch in value. Expected = TIZEN_ERROR_NOT_SUPPORTED, returned = %s \\n",__LINE__, API_NAMESPACE, API, CairoGetError(nRetVal));\
			return 1;\
		}\
	}\
	if (nRetVal == CAIRO_STATUS_SUCCESS)\
	{\
		FPRINTF( " [Line : %d] [%s]  %s passed\\n",__LINE__, API_NAMESPACE, API);\
	}\
	else \
	{\
		FPRINTF( " [Line : %d] [%s] %s failed, error returned = %s \\n",__LINE__, API_NAMESPACE, API, CairoGetError(nRetVal));\
		return 1;\
	}\
}

#define CHECK_FEATURE {\
	bIsSupported = TCTCheckSystemInfoFeatureSupported(CAIRO_FEATURE, API_NAMESPACE);\
	if (!bIsSupported) {\
		FPRINTF(" [Line No : %d][%s] Feature  : %s is not supported \\n", __LINE__,API_NAMESPACE, CAIRO_FEATURE);\
	}\
}

//Add helper function declarations here
char* CairoGetError(int nRet);
#endif  //_ITS_CAIRO_COMMON_H_
