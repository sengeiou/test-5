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
#ifndef _ITS_TBM_COMMON_H_
#define _ITS_TBM_COMMON_H_

#include "tct_common.h"
#include <tbm_surface.h>

/** @addtogroup itc-tbm
*  @ingroup itc
*  @{
*/
tbm_surface_h g_surface;
bool g_bLibtbmInit;

#define API_NAMESPACE			"TBM_ITC"

#define START_TEST {\
	FPRINTF("\\nStarting test : %s\\n",__FUNCTION__);\
	if ( !g_bLibtbmInit )\
{\
	FPRINTF("\\n[Line : %d][tbm_ITC] Precondition of tbm Initialization failed\\n", __LINE__);\
	return 1;\
}\
}

#define SUPPORT_CHECK {\
	if ( g_nTotalFormatCount == 0 )\
{\
	FPRINTF("[Line : %d][%s] No supported tbm format\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
        if ( Handle == NULL )\
{\
        FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
}\
}
char *LibtbmGetError(int nRet);
bool LibtbmCreateSurface(unsigned int nFormat);
void LibtbmDestroySurface();
char *LibtbmGetFormatType(int nRet);
/** @} */
#endif  //_ITS_TBM_COMMON_H_
