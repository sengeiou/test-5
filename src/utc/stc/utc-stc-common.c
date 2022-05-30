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

#include <time.h>
#include "utc-stc-common.h"

gboolean stc_callback_timeut(gpointer data)
{
	g_nCallbackRet = STC_ERROR_INVALID_OPERATION;
	PRINT_RETURN("stc_callback_timeut", g_nCallbackRet);
	QUIT_GMAIN_LOOP;
	return false;
}

const char *stc_get_error(int err)
{
	switch (err) {
	case STC_ERROR_NONE:
		return "None";
	case STC_ERROR_NOT_PERMITTED:
		return "Operation not permitted";
	case STC_ERROR_OUT_OF_MEMORY:
		return "Out of memory";
	case STC_ERROR_PERMISSION_DENIED:
		return "Permission denied";
	case STC_ERROR_RESOURCE_BUSY:
		return "Device or resource busy";
	case STC_ERROR_INVALID_OPERATION:
		return "Invalid operation";
	case STC_ERROR_INVALID_PARAMETER:
		return "Invalid parameter";
	case STC_ERROR_NOT_SUPPORTED:
		return "Not supported";
	case STC_ERROR_OPERATION_FAILED:
		return "Operation failed";
	case STC_ERROR_NOT_INITIALIZED:
		return "Cgroup doen't mounted or daemon not started";
	case STC_ERROR_ALREADY_INITIALIZED:
		return "Already initialized";
	case STC_ERROR_IN_PROGRESS:
		return "In progress";
	default:
		return "Unknown";
	}
}

bool stc_check_feature_supported(char *key)
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

time_t stc_make_time(int year, int mon, int day, int hour, int min)
{
	struct tm curr = { 0, };
	curr.tm_year = year - 1900;
	curr.tm_mon = mon - 1;
	curr.tm_mday = day;
	curr.tm_hour = hour;
	curr.tm_min = min;
	return mktime(&curr);
}

stc_error_e stc_get_all_stats_info(stc_stats_info_e e)
{
	int ret = STC_ERROR_NONE;
	time_t from, to;

	ret = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NONE);

	from = stc_make_time(2000, 1, 1, 1, 1);
	time(&to);
	ret = stc_stats_rule_set_time_interval(g_hRule, from, to);
	CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NONE);

	g_nCallbackRet = STC_ERROR_OPERATION_FAILED;
	g_eStatsInfo = e;
	ret = stc_get_all_stats(g_hSTC, g_hRule, stc_get_stats_finished_cb, NULL);
	CHECK_RETURN("stc_get_all_stats", ret, STC_ERROR_NONE);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, STC_ERROR_NONE);

	return STC_ERROR_NONE;
}

void stc_get_stats_finished_cb(stc_error_e result,
		stc_all_stats_info_h info, void *user_data)
{
	g_nCallbackRet = STC_ERROR_NONE;

	int ret = STC_ERROR_NONE;

	switch (g_eStatsInfo) {
	case STATS_INFO_GET_ALL:
		{
			PRINT_RETURN("stc_get_all_stats", result);
		}
		break;
	case STATS_INFO_FOREACH_ALL:
		{
			ret = stc_foreach_all_stats(info, stc_stats_info_callback, user_data);
			PRINT_RETURN("stc_foreach_all_stats", ret);
		}
		break;
	default:
		PRINT_RETURN("stc_get_stats_finished_cb", ret);
		break;
	}

	QUIT_GMAIN_LOOP;
}

stc_error_e stc_get_statistics_information(stc_stats_info_e e)
{
	int ret = STC_ERROR_NONE;
	time_t from, to;

	ret = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NONE);

	from = stc_make_time(2000, 1, 1, 1, 1);
	time(&to);
	ret = stc_stats_rule_set_time_interval(g_hRule, from, to);
	CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NONE);

	g_nCallbackRet = STC_ERROR_NONE;
	g_eStatsInfo = e;
	ret = stc_foreach_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
	CHECK_RETURN("stc_get_stats", ret, STC_ERROR_NONE);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, STC_ERROR_NONE);

	return STC_ERROR_NONE;
}

stc_callback_ret_e stc_stats_info_callback(stc_error_e result,
		stc_stats_info_h info, void *user_data)
{
	g_nCallbackRet = STC_ERROR_NONE;

	int ret = STC_ERROR_NONE;

	switch(g_eStatsInfo) {
	case STATS_INFO_APPID:
		{
			char *app_id;
			ret = stc_stats_info_get_app_id(info, &app_id);
			PRINT_RETURN("stc_stats_info_get_app_id", ret);
		}
		break;
	case STATS_INFO_IFACE_NAME:
		{
			char *iface_name;
			ret = stc_stats_info_get_iface_name(info, &iface_name);
			PRINT_RETURN("stc_stats_info_get_iface_name", ret);
		}
		break;
	case STATS_INFO_TIME_INTERVAL:
		{
			time_t from;
			time_t to;
			ret = stc_stats_info_get_time_interval(info, &from, &to);
			PRINT_RETURN("stc_stats_info_get_time_interval", ret);
		}
		break;
	case STATS_INFO_IFACE_TYPE:
		{
			stc_iface_type_e iface_type;
			ret = stc_stats_info_get_iface_type(info, &iface_type);
			PRINT_RETURN("stc_stats_info_get_iface_type", ret);
		}
		break;
	case STATS_INFO_COUNTER:
		{
			int64_t incoming;
			int64_t outgoing;
			ret = stc_stats_info_get_counter(info, &incoming, &outgoing);
			PRINT_RETURN("stc_stats_info_get_counter", ret);
		}
		break;
	case STATS_INFO_ROAMING_TYPE:
		{
			stc_roaming_type_e roaming;
			ret = stc_stats_info_get_roaming_type(info, &roaming);
			PRINT_RETURN("stc_stats_info_get_roaming_type", ret);
		}
		break;
	case STATS_INFO_PROTOCOL_TYPE:
		{
			stc_protocol_type_e prototype;
			ret = stc_stats_info_get_protocol_type(info, &prototype);
			PRINT_RETURN("stc_stats_info_get_protocol_type", ret);
		}
		break;
	case STATS_INFO_PROCESS_STATE:
		{
			stc_process_state_e procstate;
			ret = stc_stats_info_get_process_state(info, &procstate);
			PRINT_RETURN("stc_stats_info_get_process_state", ret);
		}
		break;
	case STATS_INFO_CLONE:
	case STATS_INFO_DESTROY:
		{
			stc_stats_info_h cloned = NULL;
			ret = stc_stats_info_clone(info, &cloned);
			PRINT_RETURN("stc_stats_info_clone", ret);
			if (ret == STC_ERROR_NONE) {
				ret = stc_stats_info_destroy(cloned);
				PRINT_RETURN("stc_stats_info_destroy", ret);
			}
		}
		break;
	case STATS_INFO_FOREACH_ALL:
		{
			PRINT_RETURN("stc_foreach_all_stats", ret);
		}
		break;
	default:
		PRINT_RETURN("stc_stats_info_callback", ret);
		break;
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

