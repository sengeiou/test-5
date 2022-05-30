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

int utc_ua_monitor_set_location_period_p(void)
{
	int ret = UA_ERROR_NONE;
	ua_monitor_h ua_mon_h = NULL;

	if (!ua_is_feature_location_supported()) {
		ret = ua_monitor_set_location_period(NULL, NULL);
		CHECK_RETURN("ua_monitor_set_location_period", ret, UA_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = ua_monitor_create(&ua_mon_h);
	CHECK_RETURN("ua_monitor_create", ret, UA_ERROR_NONE);

	ret = ua_monitor_set_location_period(ua_mon_h, 500);
	CHECK_RETURN("ua_monitor_set_location_period", ret, UA_ERROR_NONE);

	ret = ua_monitor_destroy(ua_mon_h);
	CHECK_RETURN("ua_monitor_destroy", ret, UA_ERROR_NONE);

	return 0;
}

int utc_ua_monitor_set_location_period_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_set_location_period(NULL, NULL);
	if (!ua_is_feature_location_supported()) {
		CHECK_RETURN("ua_monitor_set_location_period", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_set_location_period", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_location_get_distance_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_location_get_distance(NULL, NULL);
	if (!ua_is_feature_location_supported()) {
		CHECK_RETURN("ua_location_get_distance", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_location_get_distance", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_location_get_position_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_location_get_position(NULL, NULL, NULL, NULL);
	if (!ua_is_feature_location_supported()) {
		CHECK_RETURN("ua_location_get_position", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_location_get_position", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_start_location_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_start_location_detection(NULL, NULL, NULL, NULL);
	if (!ua_is_feature_location_supported()) {
		CHECK_RETURN("ua_monitor_start_location_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_start_location_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_ua_monitor_stop_location_detection_n(void)
{
	int ret = UA_ERROR_NONE;

	ret = ua_monitor_stop_location_detection(NULL);
	if (!ua_is_feature_location_supported()) {
		CHECK_RETURN("ua_monitor_stop_location_detection", ret, UA_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("ua_monitor_stop_location_detection", ret, UA_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
