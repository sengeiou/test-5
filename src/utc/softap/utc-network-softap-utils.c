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

#include "utc-network-softap-utils.h"

#include <system_info.h>

#define SYSTEM_INFO_FEATURE_PROFILE "http://tizen.org/feature/profile"

int softap_utils_check_profile(const char *profile)
{
	int check = 0;
	char *current_profile = NULL;
	int ret = system_info_get_platform_string(SYSTEM_INFO_FEATURE_PROFILE, &current_profile);
	if (ret == SYSTEM_INFO_ERROR_NONE && profile && current_profile) {
		if (!strncmp(profile, current_profile, strlen(profile)))
			check = 1;
	}

	if (current_profile)
		free(current_profile);

	return check;
}
