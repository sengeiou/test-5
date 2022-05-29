/*
 * Copyright (c) 2014 - 2015 Samsung Electronics Co., Ltd. All rights reserved.
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

#include <contacts.h>
#include <stdlib.h>

#include "utc-contacts-service-tc-utils.h"
#include "utc-contacts-service-record-activity.h"

// _contacts_activity
#define CTSVC_ACTIVITY_SOURCE_NAME_C1 "SOURCE_NAME_C"
#define CTSVC_ACTIVITY_SOURCE_NAME_U1 "SOURCE_NAME_U"
#define CTSVC_ACTIVITY_STATUS_C1 "STATUS_C"
#define CTSVC_ACTIVITY_STATUS_U1 "STATUS_U"
#define CTSVC_ACTIVITY_TIMESTAMP_C1 1
#define CTSVC_ACTIVITY_TIMESTAMP_U1 2
#define CTSVC_ACTIVITY_SERVICE_OPERATION_C1 "SERVICE_OPERATION_C"
#define CTSVC_ACTIVITY_SERVICE_OPERATION_U1 "SERVICE_OPERATION_U"
#define CTSVC_ACTIVITY_URI_C1 "URI_C"
#define CTSVC_ACTIVITY_URI_U1 "URI_U"
#define CTSVC_ACTIVITY_SOURCE_NAME_C2 "SOURCE_NAME_C2"
#define CTSVC_ACTIVITY_SOURCE_NAME_U2 "SOURCE_NAME_U2"
#define CTSVC_ACTIVITY_STATUS_C2 "STATUS_C2"
#define CTSVC_ACTIVITY_STATUS_U2 "STATUS_U2"
#define CTSVC_ACTIVITY_TIMESTAMP_C2 3
#define CTSVC_ACTIVITY_TIMESTAMP_U2 4
#define CTSVC_ACTIVITY_SERVICE_OPERATION_C2 "SERVICE_OPERATION_C2"
#define CTSVC_ACTIVITY_SERVICE_OPERATION_U2 "SERVICE_OPERATION_U2"
#define CTSVC_ACTIVITY_URI_C2 "URI_C2"
#define CTSVC_ACTIVITY_URI_U2 "URI_U2"

ctsvc_view_s _view_activity;
bool _view_activity_load = false;

static void _ctsvc_tc_load_view_activity()
{
	_view_activity_load = true;
	ctsvc_property_s activity_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity.source_name, CTSVC_ACTIVITY_SOURCE_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_activity.status, CTSVC_ACTIVITY_STATUS_C1),
		ctsvc_tc_util_create_int_property(_contacts_activity.timestamp, CTSVC_ACTIVITY_TIMESTAMP_C1),
		ctsvc_tc_util_create_str_property(_contacts_activity.service_operation, CTSVC_ACTIVITY_SERVICE_OPERATION_C1),
		ctsvc_tc_util_create_str_property(_contacts_activity.uri, CTSVC_ACTIVITY_URI_C1),
	};
	ctsvc_property_s activity_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity.source_name, CTSVC_ACTIVITY_SOURCE_NAME_U1),
		ctsvc_tc_util_create_str_property(_contacts_activity.status, CTSVC_ACTIVITY_STATUS_U1),
		ctsvc_tc_util_create_int_property(_contacts_activity.timestamp, CTSVC_ACTIVITY_TIMESTAMP_U1),
		ctsvc_tc_util_create_str_property(_contacts_activity.service_operation, CTSVC_ACTIVITY_SERVICE_OPERATION_U1),
		ctsvc_tc_util_create_str_property(_contacts_activity.uri, CTSVC_ACTIVITY_URI_U1),
	};
	ctsvc_property_s activity_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity.source_name, CTSVC_ACTIVITY_SOURCE_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_activity.status, CTSVC_ACTIVITY_STATUS_C2),
		ctsvc_tc_util_create_int_property(_contacts_activity.timestamp, CTSVC_ACTIVITY_TIMESTAMP_C2),
		ctsvc_tc_util_create_str_property(_contacts_activity.service_operation, CTSVC_ACTIVITY_SERVICE_OPERATION_C2),
		ctsvc_tc_util_create_str_property(_contacts_activity.uri, CTSVC_ACTIVITY_URI_C2),
	};
	ctsvc_property_s activity_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity.source_name, CTSVC_ACTIVITY_SOURCE_NAME_U2),
		ctsvc_tc_util_create_str_property(_contacts_activity.status, CTSVC_ACTIVITY_STATUS_U2),
		ctsvc_tc_util_create_int_property(_contacts_activity.timestamp, CTSVC_ACTIVITY_TIMESTAMP_U2),
		ctsvc_tc_util_create_str_property(_contacts_activity.service_operation, CTSVC_ACTIVITY_SERVICE_OPERATION_U2),
		ctsvc_tc_util_create_str_property(_contacts_activity.uri, CTSVC_ACTIVITY_URI_U2),
	};

	_view_activity.create1_count = sizeof(activity_create1)/sizeof(ctsvc_property_s);
	_view_activity.create2_count = sizeof(activity_create2)/sizeof(ctsvc_property_s);
	_view_activity.update1_count = sizeof(activity_update1)/sizeof(ctsvc_property_s);
	_view_activity.update2_count = sizeof(activity_update2)/sizeof(ctsvc_property_s);

	_view_activity.create1 = calloc(_view_activity.create1_count, sizeof(ctsvc_property_s));
	_view_activity.create2 = calloc(_view_activity.create2_count, sizeof(ctsvc_property_s));
	_view_activity.update1 = calloc(_view_activity.update1_count, sizeof(ctsvc_property_s));
	_view_activity.update2 = calloc(_view_activity.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_activity.create1_count;i++)
		_view_activity.create1[i] = activity_create1[i];
	for (i=0;i<_view_activity.create2_count;i++)
		_view_activity.create2[i] = activity_create2[i];
	for (i=0;i<_view_activity.update1_count;i++)
		_view_activity.update1[i] = activity_update1[i];
	for (i=0;i<_view_activity.update2_count;i++)
		_view_activity.update2[i] = activity_update2[i];
}

static int _ctsvc_tc_record_free_property_activity()
{
	if (false == _view_activity_load)
		return -1;

	_view_activity_load = false;

	free(_view_activity.create1);
	free(_view_activity.create2);
	free(_view_activity.update1);
	free(_view_activity.update2);

	return 0;
}

int ctsvc_tc_record_get_property_activity(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_activity_load)
		_ctsvc_tc_load_view_activity();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_activity.create1;
		*p_property_count = _view_activity.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_activity.create2;
		*p_property_count = _view_activity.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_activity.update1;
		*p_property_count = _view_activity.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_activity.update2;
		*p_property_count = _view_activity.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_activity(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_activity(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_activity(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_activity(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_activity.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_activity(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_activity(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_activity(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_util_record_compare(record_clone, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record_clone, true))) break;
		record_clone = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	contacts_record_destroy(record_clone, true);
	return ret;
}

static int _ctsvc_tc_record_create_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_activity(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_activity._uri)) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_add_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	contacts_record_h child = NULL;

	ret = contacts_record_create(view_uri, &child);
	if (CONTACTS_ERROR_NONE != ret)
		return ret;

	ret = contacts_record_add_child_record(record, property_id, child);
	if (CONTACTS_ERROR_NONE != ret)
		contacts_record_destroy(child, true);

	return ret;
}

static int _ctsvc_tc_record_add_child_record_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_add_child_record(record, _contacts_activity.photo, _contacts_activity_photo._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	contacts_record_h child = NULL;
	contacts_list_h list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone_child_record_list(record, property_id, &list))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_get_count(list, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	contacts_list_destroy(list, true);
	return ret;
}


static int _ctsvc_tc_record_clone_child_record_list_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_clone_child_record(record, _contacts_activity.photo, _contacts_activity_photo._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_remove_child_record(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	int count2 = 0;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_at_p(record, property_id, 0, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_remove_child_record(record, property_id, child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(child, true))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count2))) break;
		if (count == count2) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}

static int _ctsvc_tc_record_remove_child_record_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_remove_child_record(record, _contacts_activity.photo, _contacts_activity_photo._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_at_p(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_at_p(record, property_id, 0, &child))) break;
		if (NULL == child) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_at_p_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_at_p(record, _contacts_activity.photo, _contacts_activity_photo._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_child_record_count(contacts_record_h record, unsigned int property_id, const char *view_uri)
{
	int ret;
	int count = 0;
	contacts_record_h child = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(view_uri, &child))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_add_child_record(record, property_id, child))) break;
		child = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_child_record_count(record, property_id, &count))) break;
		if (count < 1) {
			ret = -1;
			break;
		}
		return 0;
	} while (0);
	contacts_record_destroy(child, true);
	return ret;
}


static int _ctsvc_tc_record_get_child_record_count_activity(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity._uri, &record))) break;
		if (0 != (ret = _ctsvc_tc_record_get_child_record_count(record, _contacts_activity.photo, _contacts_activity_photo._uri))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;

}

static int _ctsvc_tc_record_compare_type_activity(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_activity(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_activity(void)
{
	return _ctsvc_tc_record_compare_type_activity(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_activity = {
	.clone = _ctsvc_tc_record_clone_activity,
	.create = _ctsvc_tc_record_create_activity,
	.destroy = _ctsvc_tc_record_destroy_activity,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_activity,
	.add_child_record = _ctsvc_tc_record_add_child_record_activity,
	.clone_child_record_list = _ctsvc_tc_record_clone_child_record_list_activity,
	.remove_child_record = _ctsvc_tc_record_remove_child_record_activity,
	.get_child_record_at_p = _ctsvc_tc_record_get_child_record_at_p_activity,
	.get_child_record_count = _ctsvc_tc_record_get_child_record_count_activity,
	.get_bool = _ctsvc_tc_record_get_bool_activity,
	.get_double = _ctsvc_tc_record_get_double_activity,
	.get_int = _ctsvc_tc_record_get_int_activity,
	.get_lli = _ctsvc_tc_record_get_lli_activity,
	.get_str = _ctsvc_tc_record_get_str_activity,
	.get_str_p = _ctsvc_tc_record_get_str_p_activity,
	.set_bool = _ctsvc_tc_record_set_bool_activity,
	.set_double = _ctsvc_tc_record_set_double_activity,
	.set_int = _ctsvc_tc_record_set_int_activity,
	.set_lli = _ctsvc_tc_record_set_lli_activity,
	.set_str = _ctsvc_tc_record_set_str_activity,
	.free_properties = _ctsvc_tc_record_free_property_activity,
};

static int _ctsvc_tc_filter_add_type_activity(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_activity._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_activity(void)
{
	return _ctsvc_tc_filter_add_type_activity(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_activity(void)
{
	return _ctsvc_tc_filter_add_type_activity(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_activity(void)
{
	return _ctsvc_tc_filter_add_type_activity(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_activity(void)
{
	return _ctsvc_tc_filter_add_type_activity(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_activity(void)
{
	return _ctsvc_tc_filter_add_type_activity(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_activity = {
	.add_bool = _ctsvc_tc_filter_add_bool_activity,
	.add_double = _ctsvc_tc_filter_add_double_activity,
	.add_int = _ctsvc_tc_filter_add_int_activity,
	.add_lli = _ctsvc_tc_filter_add_lli_activity,
	.add_str = _ctsvc_tc_filter_add_str_activity,
};
