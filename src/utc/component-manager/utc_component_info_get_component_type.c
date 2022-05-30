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

void utc_component_info_get_component_type_p_startup(void)
{
	int ret;

	TCT_UTCCheckInstalledApp(1, "org.example.componentbased");

	ret = component_info_create("org.example.frame-component",
			&__component_info);
	if (ret != COMPONENT_MANAGER_ERROR_NONE)
		_E("Failed to create component info. error(%d)", ret);
}

void utc_component_info_get_component_type_p_cleanup(void)
{
	component_info_destroy(__component_info);
}

/**
 * @testcase            utc_component_info_get_component_type_p
 * @since_tizen         5.5
 * @description         Gets the type of the component.
 * @scenario            Calls the component_info_get_component_type() and checks the return value.
 *                      The type must not be "COMPONENT_INFO_COMPONENT_TYPE_FRAME".
 */
int utc_component_info_get_component_type_p(void)
{
	component_info_component_type_e type;
	int ret;

	ret = component_info_get_component_type(__component_info, &type);
	if (ret != COMPONENT_MANAGER_ERROR_NONE) {
		_E("Failed to get component type. error(%d)", ret);
		return ret;
	}

	if (type != COMPONENT_INFO_COMPONENT_TYPE_FRAME) {
		_E("type(%d) is not `COMPONENT_INFO_COMPONENT_TYPE_FRAME`",
				type);
		return -1;
	}

	return 0;
}

/**
 * @testcase            utc_component_info_get_component_type_n
 * @since_tizen         5.5
 * @description         Gets the type of the component.
 * @scenario            Calls the component_info_get_component_type() with nullptrs.
 *                      The return value must be COMPONENT_MANAGER_ERROR_INVALID_PARAMETER.
 */
int utc_component_info_get_component_type_n(void)
{
	int ret;

	ret = component_info_get_component_type(NULL, NULL);
	if (ret != COMPONENT_MANAGER_ERROR_INVALID_PARAMETER) {
		_E("The return value(%d) is not invalid parameter", ret);
		return ret;
	}

	return 0;
}
