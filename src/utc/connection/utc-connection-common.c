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

#include "utc-connection-common.h"

gboolean test_connection_timeout_callback(gpointer data)
{
	g_CallbackRet = CONNECTION_ERROR_OPERATION_FAILED;
	PRINT_RETURN("test_connection_timeout_callback", g_CallbackRet);
	QUIT_GMAIN_LOOP;

	return false;
}

const char *connection_get_error(connection_error_e error)
{
	switch (error) {
	case CONNECTION_ERROR_NONE:
		return "CONNECTION_ERROR_NONE";
	case CONNECTION_ERROR_INVALID_PARAMETER:
		return "CONNECTION_ERROR_INVALID_PARAMETER";
	case CONNECTION_ERROR_OUT_OF_MEMORY:
		return "CONNECTION_ERROR_OUT_OF_MEMORY";
	case CONNECTION_ERROR_INVALID_OPERATION:
		return "CONNECTION_ERROR_INVALID_OPERATION";
	case CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:
		return "CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED";
	case CONNECTION_ERROR_OPERATION_FAILED:
		return "CONNECTION_ERROR_OPERATION_FAILED";
	case CONNECTION_ERROR_ITERATOR_END:
		return "CONNECTION_ERROR_ITERATOR_END";
	case CONNECTION_ERROR_NO_CONNECTION:
		return "CONNECTION_ERROR_NO_CONNECTION";
	case CONNECTION_ERROR_NOW_IN_PROGRESS:
		return "CONNECTION_ERROR_NOW_IN_PROGRESS";
	case CONNECTION_ERROR_ALREADY_EXISTS:
		return "CONNECTION_ERROR_ALREADY_EXISTS";
	case CONNECTION_ERROR_OPERATION_ABORTED:
		return "CONNECTION_ERROR_OPERATION_ABORTED";
	case CONNECTION_ERROR_DHCP_FAILED:
		return "CONNECTION_ERROR_DHCP_FAILED";
	case CONNECTION_ERROR_INVALID_KEY:
		return "CONNECTION_ERROR_INVALID_KEY";
	case CONNECTION_ERROR_NO_REPLY:
		return "CONNECTION_ERROR_NO_REPLY";
	case CONNECTION_ERROR_PERMISSION_DENIED:
		return "CONNECTION_ERROR_PERMISSION_DENIED";
	case CONNECTION_ERROR_NOT_SUPPORTED:
		return "CONNECTION_ERROR_NOT_SUPPORTED";
	case CONNECTION_ERROR_ALREADY_INITIALIZED:
		return "CONNECTION_ERROR_ALREADY_INITIALIZED";
	case CONNECTION_ERROR_NOT_INITIALIZED:
		return "CONNECTION_ERROR_NOT_INITIALIZED";
	default:
		return "CONNECTION_ERROR_UNKNOWN";
	}
}

bool connection_check_feature_supported(char *key)
{
	bool value = false;
	int ret = system_info_get_platform_bool(key, &value);

	if (ret != SYSTEM_INFO_ERROR_NONE) {
		FPRINTF("[%s:%d] system_info_get_platform_bool failed, error returned = %d\\n", __FILE__, __LINE__, ret);
		return false;
	}

	if (value) {
		FPRINTF("[%s:%d] %s feature is supported\\n", __FILE__, __LINE__, key);
	} else {
		FPRINTF("[%s:%d] %s feature is not supported\\n", __FILE__, __LINE__, key);
	}

	return value;
}

int test_get_any_profile(connection_profile_h *profile)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;

	int  rv = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	PRINT_RETURN("connection_get_profile_iterator", rv);
	if(CONNECTION_ERROR_NONE != rv)
		return -1;

	rv = connection_profile_iterator_next(profile_iter, &profile_h);
	PRINT_RETURN("connection_profile_iterator_next", rv);
	if(CONNECTION_ERROR_NONE != rv)
		return -1;

	rv = connection_profile_clone(profile, profile_h);
	PRINT_RETURN("connection_profile_clone", rv);
	if(CONNECTION_ERROR_NONE != rv)
		return -1;

	return 1;
}
