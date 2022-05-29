/*
 * Copyright (c) 2021 Samsung Electronics Co., Ltd. All rights reserved.
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
 *
 */

#include <system_info.h>
#include <glib.h>
#include <dlog.h>
#include <user-awareness.h>

#include "utc-ua-common.h"

int utc_ua_sensor_get_status_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_sensor_get_status(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_sensor_get_status", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_sensor_get_status", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_sensor_get_timestamp_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_sensor_get_timestamp(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_sensor_get_timestamp", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_sensor_get_timestamp", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_sensor_get_type_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_sensor_get_type(NULL, NULL);
	if (!ua_is_feature_supported()) {
		CHECK_RETURN("ua_sensor_get_type", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_sensor_get_type", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
