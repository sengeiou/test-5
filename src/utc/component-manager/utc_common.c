/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <app_control.h>

#include "log_private.h"
#include "utc_common.h"

static void __app_control_result_cb(app_control_h request,
		app_control_error_e result, void *data)
{
	_I("Result: %d", result);
}

int common_send_launch_request(const char *app_id, const char *component_id,
		const char *extra)
{
	app_control_h app_control;
	int ret;

	ret = app_control_create(&app_control);
	if (ret != APP_CONTROL_ERROR_NONE) {
		_E("Failed to create app_control handle. error(%d)", ret);
		return ret;
	}

	ret = app_control_set_app_id(app_control, app_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		_E("Failed to set application ID. error(%d)", ret);
		app_control_destroy(app_control);
		return ret;
	}

	ret = app_control_set_component_id(app_control, component_id);
	if (ret != APP_CONTROL_ERROR_NONE) {
		_E("Failed to set component ID. error(%d)", ret);
		app_control_destroy(app_control);
		return ret;
	}

	if (extra) {
		ret = app_control_add_extra_data(app_control, "extra", extra);
		if (ret != APP_CONTROL_ERROR_NONE) {
			_E("Failed to add extra data. error(%d)", ret);
			app_control_destroy(app_control);
			return ret;
		}
	}

	ret = app_control_send_launch_request_async(app_control,
			__app_control_result_cb, NULL, NULL);
	app_control_destroy(app_control);
	if (ret != APP_CONTROL_ERROR_NONE) {
		_E("Failed to send launch request. error(%d)", ret);
		return ret;
	}

	return 0;
}

bool common_wait_until_done(common_do_cb callback, void *user_data)
{
	int retry_count = 0;

	do {
		if (callback(user_data))
			return true;

		usleep(500000);
		retry_count++;
	} while (retry_count <= 10);

	return false;
}
