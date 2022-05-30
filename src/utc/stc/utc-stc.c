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
#include "assert.h"
#include "utc-stc-common.h"

//& set: Stc

void utc_stc_startup(void)
{
	int ret = STC_ERROR_NONE;

	g_bFeatureSTC = stc_check_feature_supported(STC_FEATURE);

	ret = stc_initialize(&g_hSTC);
	PRINT_RETURN("stc_initialize", ret);

	ret = stc_stats_rule_create(g_hSTC, &g_hRule);
	PRINT_RETURN("stc_stats_rule_create", ret);
}

void utc_stc_cleanup(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_destroy(g_hRule);
	PRINT_RETURN("stc_stats_rule_destroy", ret);

	ret = stc_deinitialize(g_hSTC);
	PRINT_RETURN("stc_deinitialize", ret);
}


int utc_stc_initialize_p(void)
{
	int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_initialize(&g_hSTC);
		CHECK_RETURN("stc_initialize", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_deinitialize(g_hSTC);
	CHECK_RETURN("stc_deinitialize", ret, STC_ERROR_NONE);

	ret = stc_initialize(&g_hSTC);
	CHECK_RETURN("stc_initialize", ret, STC_ERROR_NONE);

    return 0;
}

int utc_stc_initialize_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_initialize(NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_initialize", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_initialize", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_deinitialize_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_deinitialize(&g_hSTC);
		CHECK_RETURN("stc_deinitialize", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_deinitialize(g_hSTC);
	CHECK_RETURN("stc_deinitialize", ret, STC_ERROR_NONE);

	ret = stc_initialize(&g_hSTC);
	CHECK_RETURN("stc_initialize", ret, STC_ERROR_NONE);

    return 0;
}

int utc_stc_deinitialize_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_deinitialize(NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_deinitialize", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_deinitialize", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_create_p(void)
{
	stc_stats_rule_h hRule;
	int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_create(g_hSTC, &hRule);
		CHECK_RETURN("stc_stats_rule_create", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_create(g_hSTC, &hRule);
	CHECK_RETURN("stc_stats_rule_create", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_destroy(hRule);
	CHECK_RETURN("stc_stats_rule_destroy", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_create_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_create(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_create", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_create", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_destroy_p(void)
{
    stc_stats_rule_h hRule = NULL;
	int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_destroy(hRule);
		CHECK_RETURN("stc_stats_rule_destroy", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_create(g_hSTC, &hRule);
	CHECK_RETURN("stc_stats_rule_create", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_destroy(hRule);
	CHECK_RETURN("stc_stats_rule_destroy", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_destroy_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_destroy(NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_destroy", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_destroy", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_set_app_id_p(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NONE);
	}

	return 0;
}

int utc_stc_stats_rule_set_app_id_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_app_id(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_set_time_interval_p(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_time_interval(g_hRule, 0, 0);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NONE);
	}

	return 0;
}

int utc_stc_stats_rule_set_time_interval_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_time_interval(NULL, 0, 0);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_set_iface_type_p(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_iface_type(g_hRule, STC_IFACE_DATACALL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_iface_type", ret, STC_ERROR_NONE);
	}

	return 0;
}

int utc_stc_stats_rule_set_iface_type_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_iface_type(NULL, STC_IFACE_UNKNOWN);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_iface_type", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_set_time_period_p(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_time_period(g_hRule, STC_TIME_PERIOD_MONTH);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_time_period", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_time_period", ret, STC_ERROR_NONE);
	}

	return 0;
}

int utc_stc_stats_rule_set_time_period_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_set_time_period(NULL, STC_TIME_PERIOD_UNKNOWN);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_set_time_period", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_set_time_period", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_get_app_id_p(void)
{
    int ret = STC_ERROR_NONE;
	char *app_id = NULL;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_get_app_id(g_hRule, &app_id);
		CHECK_RETURN("stc_stats_rule_get_app_id", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	CHECK_RETURN("stc_stats_rule_set_app_id", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_get_app_id(g_hRule, &app_id);
	FREE_MEMORY(app_id);
	CHECK_RETURN("stc_stats_rule_get_app_id", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_get_app_id_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_get_app_id(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_get_app_id", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_get_app_id", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_get_time_interval_p(void)
{
    int ret = STC_ERROR_NONE;
	time_t from, to;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_get_time_interval(g_hRule, &from, &to);
		CHECK_RETURN("stc_stats_rule_get_app_id", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_set_time_interval(g_hRule, 0, 0);
	CHECK_RETURN("stc_stats_rule_get_time_interval", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_get_time_interval(g_hRule, &from, &to);
	CHECK_RETURN("stc_stats_rule_get_time_interval", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_get_time_interval_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_get_time_interval(NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_get_time_interval", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_get_time_interval", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_get_iface_type_p(void)
{
    int ret = STC_ERROR_NONE;
	stc_iface_type_e iface_type;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_get_iface_type(g_hRule, &iface_type);
		CHECK_RETURN("stc_stats_rule_get_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_set_iface_type(g_hRule, STC_IFACE_DATACALL);
	CHECK_RETURN("stc_stats_rule_set_iface_type", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_get_iface_type(g_hRule, &iface_type);
	CHECK_RETURN("stc_stats_rule_get_iface_type", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_get_iface_type_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_get_iface_type(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_get_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_get_iface_type", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_rule_get_time_period_p(void)
{
    int ret = STC_ERROR_NONE;
	stc_time_period_e time_period;

	if (!g_bFeatureSTC) {
		ret = stc_stats_rule_get_time_period(g_hRule, &time_period);
		CHECK_RETURN("stc_stats_rule_get_time_period", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_stats_rule_set_time_period(g_hRule, STC_TIME_PERIOD_MONTH);
	CHECK_RETURN("stc_stats_rule_set_time_period", ret, STC_ERROR_NONE);

	ret = stc_stats_rule_get_time_period(g_hRule, &time_period);
	CHECK_RETURN("stc_stats_rule_get_time_period", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_rule_get_time_period_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_rule_get_time_period(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_rule_get_time_period", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_rule_get_time_period", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_get_stats_p(void)
{
	int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_get_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
		CHECK_RETURN("stc_get_stats", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_UNKNOWN);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_get_stats_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_get_stats(NULL, NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_get_stats", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_get_stats", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_get_all_stats_p(void)
{
	int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_get_all_stats(g_hSTC, g_hRule, stc_get_stats_finished_cb, NULL);
		CHECK_RETURN("stc_get_all_stats", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_all_stats_info(STATS_INFO_GET_ALL);
	CHECK_RETURN("stc_get_all_stats_info", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_get_all_stats_n(void)
{
	int ret = STC_ERROR_NONE;

	ret = stc_get_all_stats(NULL, NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_get_all_stats", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_get_all_stats", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_foreach_stats_p(void)
{
    int ret = STC_ERROR_NONE;
	time_t from, to;

	if (!g_bFeatureSTC) {
		ret = stc_get_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
		CHECK_RETURN("stc_get_stats", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	from = stc_make_time(2000, 1, 1, 1, 1);
	time(&to);
	ret = stc_stats_rule_set_time_interval(g_hRule, from, to);
	CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NONE);

	g_nCallbackRet = STC_ERROR_NONE;
	ret = stc_foreach_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
	CHECK_RETURN("stc_foreach_stats", ret, STC_ERROR_NONE);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, STC_ERROR_NONE);

	return 0;
}

int utc_stc_foreach_stats_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_foreach_stats(NULL, NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_foreach_stats", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_foreach_stats", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_foreach_all_stats_p(void)
{
   int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_foreach_all_stats(NULL, NULL, NULL);
		CHECK_RETURN("stc_foreach_all_stats", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_all_stats_info(STATS_INFO_FOREACH_ALL);
	CHECK_RETURN("stc_get_all_stats_info", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_foreach_all_stats_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_foreach_all_stats(NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_foreach_all_stats", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_foreach_all_stats", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_get_total_stats_p(void)
{
    int ret = STC_ERROR_NONE;
	time_t from, to;

	if (!g_bFeatureSTC) {
		ret = stc_get_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
		CHECK_RETURN("stc_get_stats", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	from = stc_make_time(2000, 1, 1, 1, 1);
	time(&to);
	ret = stc_stats_rule_set_time_interval(g_hRule, from, to);
	CHECK_RETURN("stc_stats_rule_set_time_interval", ret, STC_ERROR_NONE);

	g_nCallbackRet = STC_ERROR_NONE;
	ret = stc_get_total_stats(g_hSTC, g_hRule, stc_stats_info_callback, NULL);
	CHECK_RETURN("stc_get_total_stats", ret, STC_ERROR_NONE);
	RUN_GMAIN_LOOP;
	CHECK_RETURN(CALLBACK_RETURN, g_nCallbackRet, STC_ERROR_NONE);

	return 0;
}

int utc_stc_get_total_stats_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_get_total_stats(NULL, NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_get_total_stats", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_get_total_stats", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_clone_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_clone(NULL, NULL);
		CHECK_RETURN("stc_stats_info_clone", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_CLONE);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_clone_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_clone(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_clone", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_clone", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_destroy_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_destroy(NULL);
		CHECK_RETURN("stc_stats_info_destroy", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_DESTROY);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_destroy_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_destroy(NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_destroy", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_destroy", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_app_id_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_app_id(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_app_id", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_APPID);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_app_id_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_app_id(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_app_id", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_app_id", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_iface_name_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_iface_name(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_iface_name", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_IFACE_NAME);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_iface_name_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_iface_name(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_iface_name", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_iface_name", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_time_interval_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_time_interval(g_hRule, 0, 0);
		CHECK_RETURN("stc_stats_info_get_time_interval", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_TIME_INTERVAL);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_time_interval_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_time_interval(NULL, 0, 0);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_time_interval", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_time_interval", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_iface_type_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_iface_type(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_IFACE_TYPE);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_iface_type_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_iface_type(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_iface_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_iface_type", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_counter_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_counter(g_hRule, NULL, NULL);
		CHECK_RETURN("stc_stats_info_get_counter", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_COUNTER);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_counter_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_counter(NULL, NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_counter", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_counter", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_roaming_type_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_roaming_type(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_roaming_type", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_ROAMING_TYPE);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_roaming_type_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_roaming_type(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_roaming_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_roaming_type", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_protocol_type_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_protocol_type(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_protocol_type", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_PROTOCOL_TYPE);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_protocol_type_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_protocol_type(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_protocol_type", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_protocol_type", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

int utc_stc_stats_info_get_process_state_p(void)
{
    int ret = STC_ERROR_NONE;

	if (!g_bFeatureSTC) {
		ret = stc_stats_info_get_process_state(g_hRule, NULL);
		CHECK_RETURN("stc_stats_info_get_process_state", ret, STC_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = stc_get_statistics_information(STATS_INFO_PROTOCOL_TYPE);
	CHECK_RETURN("stc_get_statistics_information", ret, STC_ERROR_NONE);

	return 0;
}

int utc_stc_stats_info_get_process_state_n(void)
{
    int ret = STC_ERROR_NONE;

	ret = stc_stats_info_get_process_state(NULL, NULL);
	if (!g_bFeatureSTC) {
		CHECK_RETURN("stc_stats_info_get_process_state", ret, STC_ERROR_NOT_SUPPORTED);
	} else {
		CHECK_RETURN("stc_stats_info_get_process_state", ret, STC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
