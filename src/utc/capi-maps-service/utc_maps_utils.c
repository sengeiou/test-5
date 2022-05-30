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

#include "utc_maps_utils.h"

static bool _is_removed_checked_providers = false;
static bool _is_removed_HERE = false;

static char *MAPS_PROVIDER_NAME_HERE = "HERE";

static bool __check_removed_provider_cb(char *maps_provider, void *user_data)
{
	free(maps_provider);
	return true;
}

char *__utc_get_maps_provider_name_here()
{
	return MAPS_PROVIDER_NAME_HERE;
}

bool _is_internet_feature_supported(void)
{
	bool __is_supported = true;
	char *profile = NULL;
	int ret = system_info_get_platform_string("http://tizen.org/feature/profile", &profile);
	if (ret == SYSTEM_INFO_ERROR_NONE && profile && *profile) {
		if (!strcmp("wearable", profile))
			system_info_get_platform_bool("http://tizen.org/feature/network.internet", &__is_supported);
	}
	if (profile)
		free(profile);
	return __is_supported;
}

bool _is_maps_feature_supported(void)
{
	bool __is_supported = true;
	system_info_get_platform_bool("http://tizen.org/feature/maps", &__is_supported);
	return __is_supported;
}

