/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <calendar.h>

#include "utc-calendar-util.h"
#include "utc-calendar-debug.h"

void _clean_db_book(void)
{

	calendar_list_h list = NULL;
	calendar_db_get_all_records(_calendar_book._uri, 0, 0, &list);

	int count = 0;
	calendar_list_get_count(list, &count);

	if (0 == count)
		return;

	int i;
	int ret;
	ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret){
		calendar_list_destroy(list, true);
		return;
	}
	for(i = 0; i < count; i++){
		int id = 0;
		calendar_record_h book = NULL;
		calendar_list_get_current_record_p(list, &book);
		ret = calendar_record_get_int(book, _calendar_book.id, &id);
		if (CALENDAR_ERROR_NONE != ret){
			fprintf(stderr, "Current record error at %s:%d\n", __FILE__, __LINE__);
			calendar_list_destroy(list, true);
			calendar_list_destroy(book, true);
			return;
		}
		if (id <= DEFAULT_BIRTHDAY_CALENDAR_BOOK_ID) {
			calendar_list_next(list);
			continue;
		}
		calendar_db_delete_record(_calendar_book._uri, id);
		calendar_list_next(list);
	}
	calendar_list_destroy(list, true);
}

void _clean_db_timezone(void)
{
	calendar_list_h list = NULL;
	calendar_db_get_all_records(_calendar_timezone._uri, 0, 0, &list);

	int count = 0;
	calendar_list_get_count(list, &count);

	if (0 == count)
		return;

	int *ids = NULL;
	ids = (int*) calloc(count, sizeof(int));

	int i;
	int ret;
	ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret){
		fprintf(stderr, "Calendar list error at %s:%d\n", __FILE__, __LINE__);
		calendar_list_destroy(list, true);
		free(ids);
		return;
	}
	for(i = 0; i < count; i++){
		calendar_record_h timezone = NULL;
		calendar_list_get_current_record_p(list, &timezone);
		ret = calendar_record_get_int(timezone, _calendar_timezone.id, &(ids[i]));
		if (CALENDAR_ERROR_NONE != ret){
			fprintf(stderr, "Current record error at %s:%d\n", __FILE__, __LINE__);
			calendar_list_destroy(list, true);
			calendar_list_destroy(timezone, true);
			free(ids);
			return;
		}
		calendar_list_next(list);
	}
	calendar_list_destroy(list, true);

	calendar_db_delete_records(_calendar_timezone._uri, ids, count);
	if(ids){
		free(ids);
	}
}

void _clean_db_event(void)
{
	calendar_list_h list = NULL;
	calendar_db_get_all_records(_calendar_event._uri, 0, 0, &list);

	int count = 0;
	calendar_list_get_count(list, &count);

	if (0 == count)
		return;

	int *ids = NULL;
	ids = (int*) calloc(count, sizeof(int));

	int i;
	int ret;
	ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret){
		fprintf(stderr, "Calendar list error at %s:%d\n", __FILE__, __LINE__);
		calendar_list_destroy(list, true);
		free(ids);
		return;
	}
	for(i = 0; i < count; i++){
		calendar_record_h event = NULL;
		calendar_list_get_current_record_p(list, &event);
		ret = calendar_record_get_int(event, _calendar_event.id, &(ids[i]));
		if (CALENDAR_ERROR_NONE != ret){
			fprintf(stderr, "Calendar record get error at %s:%d\n", __FILE__, __LINE__);
			calendar_list_destroy(list, true);
			calendar_list_destroy(event, true);
			return;
		}
		calendar_list_next(list);
	}
	calendar_list_destroy(list, true);

	calendar_db_delete_records(_calendar_event._uri, ids, count);
	if(ids){
		free(ids);
	}
}

void _clean_db_todo(void)
{
	calendar_list_h list = NULL;
	calendar_db_get_all_records(_calendar_todo._uri, 0, 0, &list);

	int count = 0;
	calendar_list_get_count(list, &count);

	if (0 == count)
		return;

	int *ids = NULL;
	ids = (int*) calloc(count, sizeof(int));

	int i;
	int ret;
	ret = calendar_list_first(list);
	if (CALENDAR_ERROR_NONE != ret){
		fprintf(stderr, "Calendar list error at %s:%d\n", __FILE__, __LINE__);
		calendar_list_destroy(list, true);
		free(ids);
		return;
	}
	for(i = 0; i < count; i++){
		calendar_record_h todo = NULL;
		calendar_list_get_current_record_p(list, &todo);
		ret = calendar_record_get_int(todo, _calendar_todo.id, &(ids[i]));
		if (CALENDAR_ERROR_NONE != ret){
			fprintf(stderr, "Calendar record get error at %s:%d\n", __FILE__, __LINE__);
			calendar_list_destroy(list, true);
			calendar_list_destroy(todo, true);
			free(ids);
			return;
		}
		calendar_list_next(list);
	}
	calendar_list_destroy(list, true);

	calendar_db_delete_records(_calendar_todo._uri, ids, count);
	if(ids){
		free(ids);
	}
}

void _clean_db(void)
{
	_clean_db_book();
	_clean_db_event();
	_clean_db_todo();
	_clean_db_timezone();

}
int _check_str(char *str, const char *value)
{
	int ret = 0;
	if (NULL == str) {
		fprintf(stderr, "str is NULL");
		return -1;
	}
	if (NULL == value) {
		fprintf(stderr, "value is NULL");
		return -1;
	}

	if (!strncmp(str, value, strlen(value))) {
		ret = 0;
	} else {
		ret = -1;
		fprintf(stderr, "get[%s] expected[%s]", str, value);
	}
	return ret;
}
int _check_str_with_len(char *str, const char *value, int len)
{
	int ret = 0;
	if (NULL == str) {
		fprintf(stderr, "str is NULL");
		return -1;
	}
	if (NULL == value) {
		fprintf(stderr, "value is NULL");
		return -1;
	}

	if (!strncmp(str, value, len)) {
		ret = 0;
	} else {
		ret = -1;
		fprintf(stderr, "get[%s] expected[%s]", str, value);
	}
	return ret;
}
int _check_int(int *i, const int value)
{
	int ret = 0;
	if (value == *i) {
		ret = 0;
	} else {
		ret = -1;
		fprintf(stderr, "get(%d) expected(%d)", *i, value);
	}
	*i = 0;
	return ret;
}
int _check_double(double *d, const double value)
{
	int ret = 0;
	if (value == *d) {
		ret = 0;
	} else {
		ret = -1;
	}
	*d = 0;
	return ret;
}
int _check_lli(long long int *l, const long long int value)
{
	int ret = 0;
	if (value == *l) {
		ret = 0;
	} else {
		ret = -1;
	}
	*l = 0;
	return ret;
}
int _check_caltime(calendar_time_s *ct, calendar_time_s value)
{
	int ret = 0;
	switch (ct->type)
	{
	case CALENDAR_TIME_UTIME:
		if (value.time.utime == ct->time.utime) {
			ret = 0;
		} else {
			ret = -1;
		}
		break;
	case CALENDAR_TIME_LOCALTIME:
		if (value.time.date.year == ct->time.date.year &&
				value.time.date.month  == ct->time.date.month &&
				value.time.date.mday   == ct->time.date.mday  &&
				value.time.date.hour   == ct->time.date.hour  &&
				value.time.date.minute == ct->time.date.minute &&
				value.time.date.second == ct->time.date.second) {
			ret = 0;
		} else {
			ret = -1;
		}
		break;
	}
	memset(ct, 0x0, sizeof(calendar_time_s));
	return ret;
}

bool _is_feature_supported(void)
{
	int ret = 0;
	static bool has_feature = false;

	ret = system_info_get_platform_bool(UTC_CALENDAR_FEATURE, &has_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret)
		return false;
	if (false == has_feature) {
		DBG("feature is not supported");
	}

	return has_feature;
}
