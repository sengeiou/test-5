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

#include <component_manager.h>

#include "assert.h"
#include "tct_app_common.h"
#include "log_private.h"

static component_info_h __component_info;

void utc_component_info_is_icon_display_p_startup(void)
{
	int ret;

	TCT_UTCCheckInstalledApp(1, "org.example.componentbased");

	ret = component_info_create("org.example.frame-component",
			&__component_info);
	if (ret != COMPONENT_MANAGER_ERROR_NONE)
		_E("Failed to create component info. error(%d)", ret);
}

void utc_component_info_is_icon_display_p_cleanup(void)
{
	component_info_destroy(__component_info);
}

/**
 * @testcase            utc_component_info_is_icon_display_p
 * @since_tizen         5.5
 * @description         Checks whether the icon of the component should be displayed or not.
 * @scenario            Calls the component_info_is_icon_display() and checks the return value.
 *                      The icon_display must be "true".
 */
int utc_component_info_is_icon_display_p(void)
{
	bool icon_display;
	int ret;

	ret = component_info_is_icon_display(__component_info, &icon_display);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to check icon display. error(%d)", ret);
		return ret;
	}

	if (!icon_display) {
		_E("icon_display(%d) is not `true`", icon_display);
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_info_is_icon_display_n
 * @since_tizen         5.5
 * @description         Checks whether the icon of the component should be displayed or not.
 * @scenario            Calls the component_info_is_icon_display() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_info_is_icon_display_n(void)
{
	int ret;

	ret = component_info_is_icon_display(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
