/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __TCT_CAPI_MAPS_SERVICE_UTILS_H__
#define __TCT_CAPI_MAPS_SERVICE_UTILS_H__

#include "tct_common.h"
#include "assert.h"
#include <dlog.h>
#include <maps_service.h>

#define _LOG(fmt, args...) { \
	dlog_print (DLOG_INFO, "CAPI_MAPS_SERVICE_UTC", "[%s:%d] "fmt"\n", __func__, __LINE__, ##args); \
}

#define API_NAMESPACE				"CAPI_MAPS_SERVICE_UTC"
#define INTERNET_FEATURE			"http://tizen.org/feature/network.internet"

#define ASSERT_IF_VAL_REF2(var, cond, ref1, ref2) \
	if (cond) { \
		if (var != ref1) { \
			fprintf(stderr, \
	            "\\n[TCT][%s][Line : %d] Assert fail; Values (0x%X) and (%s) are not equal\\n", __FILE__, __LINE__, var, #ref1); \
			return 1; \
		} \
	} else { \
		if (var != ref2) { \
			fprintf(stderr, \
	            "\\n[TCT][%s][Line : %d] Assert fail; Values (0x%X) and (%s) are not equal\\n", __FILE__, __LINE__, var, #ref2); \
			return 1; \
		} \
	} \

/* Returns the name of current provider */
char *__utc_get_maps_provider_name_here();

bool _is_internet_feature_supported(void);
bool _is_maps_feature_supported(void);

#endif /*__TCT_CAPI_MAPS_SERVICE_UTILS_H__*/
