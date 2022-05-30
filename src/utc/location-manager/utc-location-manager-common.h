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
#ifndef __UTC_LOCATION_MANAGER_COMMON_H__
#define __UTC_LOCATION_MANAGER_COMMON_H__

#include "tct_common.h"
#include <locations.h>
#include <dlog.h>

#define LOCATION_FEATURE		"http://tizen.org/feature/location"
#define GPS_FEATURE				"http://tizen.org/feature/location.gps"
#define GPS_SATELLITE_FEATURE	"http://tizen.org/feature/location.gps.satellite"
#define WPS_FEATURE				"http://tizen.org/feature/location.wps"
#define BATCH_FEATURE			"http://tizen.org/feature/location.batch"
#define FUSED_FEATURE			"http://tizen.org/feature/location.fused"

int ret;
bool service_enabled;
bool is_gps_supported;
bool is_gps_satellite_supported;
bool is_wps_supported;
bool is_batch_supported;
bool is_fused_supported;
bool is_location_supported;


#define CHECK_INVALID_PARAMETER(condition, ret)	\
		do { \
			if (condition) { \
				assert_eq(ret, LOCATIONS_ERROR_INVALID_PARAMETER); \
			} else { \
				assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED); \
			} \
		} while (0)

#define CHECK_INCORRECT_METHOD(condition, ret)	\
		do { \
			if (condition) { \
				assert_eq(ret, LOCATIONS_ERROR_INCORRECT_METHOD); \
			} else { \
				assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED); \
			} \
		} while (0)

#define CHECK_ERROR_NONE(condition, ret)	\
		do { \
			if (condition) { \
				assert_eq(ret, LOCATIONS_ERROR_NONE); \
			} else { \
				assert_eq(ret, LOCATIONS_ERROR_NOT_SUPPORTED); \
			} \
		} while (0)

#define CHECK(condition, ret)	\
		do { \
			if (condition) { \
				assert_eq(ret, LOCATIONS_ERROR_NONE); \
			} \
		} while (0)

#define _LOG(fmt, args...) { \
	dlog_print (DLOG_INFO, "LOCATION_MANAGER_UTC", "[%s:%d] "fmt"\n", __func__, __LINE__, ##args); \
}

#endif // __UTC_LOCATION_MANAGER_COMMON_H__
