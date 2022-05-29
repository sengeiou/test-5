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
#ifndef _ITS_MEDIADEMUXER_COMMON_H_
#define _ITS_MEDIADEMUXER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <fcntl.h>
#include <mediademuxer.h>
#include <storage.h>
#include <glib-2.0/glib.h>

/** @addtogroup itc-mediademuxer
*  @ingroup itc
*  @{
*/

bool g_bMediademuxerCreation;

#define API_NAMESPACE			"MEDIADEMUXER_ITC"
#define MAXENUMSIZE				50
#define SETENUM					1
#define GETENUM					0
#define TRACK_INDEX 			1
#define POSITION 				2000

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bMediademuxerCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of mediademuxer failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

char* MediademuxerGetState(mediademuxer_state state);
char* MediademuxerGetError(mediademuxer_error_e error);
/** @} */
#endif  //_ITS_MEDIADEMUXER_COMMON_H_
