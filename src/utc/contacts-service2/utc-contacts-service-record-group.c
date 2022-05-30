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
#include "utc-contacts-service-record-group.h"

// _contacts_group
#define CTSVC_GROUP_NAME_C1 "NAME_C"
#define CTSVC_GROUP_NAME_U1 "NAME_U"
#define CTSVC_GROUP_RINGTONE_PATH_C1 CTSVC_RINGTONE_PATH_C1
#define CTSVC_GROUP_RINGTONE_PATH_U1 CTSVC_RINGTONE_PATH_U1
#define CTSVC_GROUP_IMAGE_PATH_C1 CTSVC_IMAGE_PATH_C1
#define CTSVC_GROUP_IMAGE_PATH_U1 CTSVC_IMAGE_PATH_U1
#define CTSVC_GROUP_VIBRATION_C1 CTSVC_VIBRATION_C1
#define CTSVC_GROUP_VIBRATION_U1 CTSVC_VIBRATION_U1
#define CTSVC_GROUP_EXTRA_DATA_C1 "EXTRA_DATA_C"
#define CTSVC_GROUP_EXTRA_DATA_U1 "EXTRA_DATA_U"
#define CTSVC_GROUP_IS_READONLY_C1 true
#define CTSVC_GROUP_MESSAGE_ALERT_C1 CTSVC_MESSAGE_ALERT_C1
#define CTSVC_GROUP_MESSAGE_ALERT_U1 CTSVC_MESSAGE_ALERT_U1
#define CTSVC_GROUP_NAME_C2 "NAME_C2"
#define CTSVC_GROUP_NAME_U2 "NAME_U2"
#define CTSVC_GROUP_RINGTONE_PATH_C2 CTSVC_RINGTONE_PATH_C2
#define CTSVC_GROUP_RINGTONE_PATH_U2 CTSVC_RINGTONE_PATH_U2
#define CTSVC_GROUP_IMAGE_PATH_C2 CTSVC_IMAGE_PATH_C2
#define CTSVC_GROUP_IMAGE_PATH_U2 CTSVC_IMAGE_PATH_U2
#define CTSVC_GROUP_VIBRATION_C2 CTSVC_VIBRATION_C2
#define CTSVC_GROUP_VIBRATION_U2 CTSVC_VIBRATION_U2
#define CTSVC_GROUP_EXTRA_DATA_C2 "EXTRA_DATA_C2"
#define CTSVC_GROUP_EXTRA_DATA_U2 "EXTRA_DATA_U2"
#define CTSVC_GROUP_IS_READONLY_C2 true
#define CTSVC_GROUP_MESSAGE_ALERT_C2 CTSVC_MESSAGE_ALERT_C2
#define CTSVC_GROUP_MESSAGE_ALERT_U2 CTSVC_MESSAGE_ALERT_U2


ctsvc_view_s _view_group;
bool _view_group_load = false;

static void _ctsvc_tc_load_view_group()
{
	_view_group_load = true;
	// _contacts_group
	ctsvc_property_s group_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_group.name, CTSVC_GROUP_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_group.ringtone_path, CTSVC_GROUP_RINGTONE_PATH_C1),
		ctsvc_tc_util_create_str_property(_contacts_group.image_path, CTSVC_GROUP_IMAGE_PATH_C1),
		ctsvc_tc_util_create_str_property(_contacts_group.vibration, CTSVC_GROUP_VIBRATION_C1),
		ctsvc_tc_util_create_str_property(_contacts_group.extra_data, CTSVC_GROUP_EXTRA_DATA_C1),
		ctsvc_tc_util_create_str_property(_contacts_group.message_alert, CTSVC_GROUP_MESSAGE_ALERT_C1),
	};
	ctsvc_property_s group_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_group.name, CTSVC_GROUP_NAME_U1),
		ctsvc_tc_util_create_str_property(_contacts_group.ringtone_path, CTSVC_GROUP_RINGTONE_PATH_U1),
		ctsvc_tc_util_create_str_property(_contacts_group.image_path, CTSVC_GROUP_IMAGE_PATH_U1),
		ctsvc_tc_util_create_str_property(_contacts_group.vibration, CTSVC_GROUP_VIBRATION_U1),
		ctsvc_tc_util_create_str_property(_contacts_group.extra_data, CTSVC_GROUP_EXTRA_DATA_U1),
		ctsvc_tc_util_create_str_property(_contacts_group.message_alert, CTSVC_GROUP_MESSAGE_ALERT_U1),
	};

	ctsvc_property_s group_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_group.name, CTSVC_GROUP_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_group.ringtone_path, CTSVC_GROUP_RINGTONE_PATH_C2),
		ctsvc_tc_util_create_str_property(_contacts_group.image_path, CTSVC_GROUP_IMAGE_PATH_C2),
		ctsvc_tc_util_create_str_property(_contacts_group.vibration, CTSVC_GROUP_VIBRATION_C2),
		ctsvc_tc_util_create_str_property(_contacts_group.extra_data, CTSVC_GROUP_EXTRA_DATA_C2),
		ctsvc_tc_util_create_str_property(_contacts_group.message_alert, CTSVC_GROUP_MESSAGE_ALERT_C2),
	};
	ctsvc_property_s group_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_group.name, CTSVC_GROUP_NAME_U2),
		ctsvc_tc_util_create_str_property(_contacts_group.ringtone_path, CTSVC_GROUP_RINGTONE_PATH_U2),
		ctsvc_tc_util_create_str_property(_contacts_group.image_path, CTSVC_GROUP_IMAGE_PATH_U2),
		ctsvc_tc_util_create_str_property(_contacts_group.vibration, CTSVC_GROUP_VIBRATION_U2),
		ctsvc_tc_util_create_str_property(_contacts_group.extra_data, CTSVC_GROUP_EXTRA_DATA_U2),
		ctsvc_tc_util_create_str_property(_contacts_group.message_alert, CTSVC_GROUP_MESSAGE_ALERT_U2),
	};

	_view_group.create1_count = sizeof(group_create1)/sizeof(ctsvc_property_s);
	_view_group.create2_count = sizeof(group_create2)/sizeof(ctsvc_property_s);
	_view_group.update1_count = sizeof(group_update1)/sizeof(ctsvc_property_s);
	_view_group.update2_count = sizeof(group_update2)/sizeof(ctsvc_property_s);

	_view_group.create1 = calloc(_view_group.create1_count, sizeof(ctsvc_property_s));
	_view_group.create2 = calloc(_view_group.create2_count, sizeof(ctsvc_property_s));
	_view_group.update1 = calloc(_view_group.update1_count, sizeof(ctsvc_property_s));
	_view_group.update2 = calloc(_view_group.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_group.create1_count;i++)
		_view_group.create1[i] = group_create1[i];
	for (i=0;i<_view_group.create2_count;i++)
		_view_group.create2[i] = group_create2[i];
	for (i=0;i<_view_group.update1_count;i++)
		_view_group.update1[i] = group_update1[i];
	for (i=0;i<_view_group.update2_count;i++)
		_view_group.update2[i] = group_update2[i];
}

static int _ctsvc_tc_record_free_property_group()
{
	int i;

	if (false == _view_group_load)
		return -1;

	_view_group_load = false;

	for (i=0;i<_view_group.create1_count;i++) {
		if (_contacts_group.ringtone_path == _view_group.create1[i].property_id
			|| _contacts_group.image_path == _view_group.create1[i].property_id
			|| _contacts_group.vibration == _view_group.create1[i].property_id
			|| _contacts_group.message_alert == _view_group.create1[i].property_id)
			free(_view_group.create1[i].val.str_val);
	}
	for (i=0;i<_view_group.create2_count;i++) {
		if (_contacts_group.ringtone_path == _view_group.create2[i].property_id
			|| _contacts_group.image_path == _view_group.create2[i].property_id
			|| _contacts_group.vibration == _view_group.create2[i].property_id
			|| _contacts_group.message_alert == _view_group.create2[i].property_id)
			free(_view_group.create2[i].val.str_val);
	}
	for (i=0;i<_view_group.update1_count;i++) {
		if (_contacts_group.ringtone_path == _view_group.update1[i].property_id
			|| _contacts_group.image_path == _view_group.update1[i].property_id
			|| _contacts_group.vibration == _view_group.update1[i].property_id
			|| _contacts_group.message_alert == _view_group.update1[i].property_id)
			free(_view_group.update1[i].val.str_val);
	}
	for (i=0;i<_view_group.update2_count;i++) {
		if (_contacts_group.ringtone_path == _view_group.update2[i].property_id
			|| _contacts_group.image_path == _view_group.update2[i].property_id
			|| _contacts_group.vibration == _view_group.update2[i].property_id
			|| _contacts_group.message_alert == _view_group.update2[i].property_id)
			free(_view_group.update2[i].val.str_val);
	}

	free(_view_group.create1);
	free(_view_group.create2);
	free(_view_group.update1);
	free(_view_group.update2);

	return 0;
}

int ctsvc_tc_record_get_property_group(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_group_load)
		_ctsvc_tc_load_view_group();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_group.create1;
		*p_property_count = _view_group.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_group.create2;
		*p_property_count = _view_group.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_group.update1;
		*p_property_count = _view_group.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_group.update2;
		*p_property_count = _view_group.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_group(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_group(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_group(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_group(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_group(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_group(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_group(int address_book_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_group._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_group.address_book_id, address_book_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_group(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_group(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_group(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_group(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_group(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_group._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_group(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_group._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_group(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_group._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_group._uri)) {
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

static int _ctsvc_tc_record_compare_type_group(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_group(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_group(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_group(void)
{
	return _ctsvc_tc_record_compare_type_group(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_group = {
	.clone = _ctsvc_tc_record_clone_group,
	.create = _ctsvc_tc_record_create_group,
	.destroy = _ctsvc_tc_record_destroy_group,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_group,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_group,
	.get_double = _ctsvc_tc_record_get_double_group,
	.get_int = _ctsvc_tc_record_get_int_group,
	.get_lli = _ctsvc_tc_record_get_lli_group,
	.get_str = _ctsvc_tc_record_get_str_group,
	.get_str_p = _ctsvc_tc_record_get_str_p_group,
	.set_bool = _ctsvc_tc_record_set_bool_group,
	.set_double = _ctsvc_tc_record_set_double_group,
	.set_int = _ctsvc_tc_record_set_int_group,
	.set_lli = _ctsvc_tc_record_set_lli_group,
	.set_str = _ctsvc_tc_record_set_str_group,
	.free_properties = _ctsvc_tc_record_free_property_group,
};


static int _ctsvc_tc_filter_add_type_group(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_group._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_group(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_group(void)
{
	return _ctsvc_tc_filter_add_type_group(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_group(void)
{
	return _ctsvc_tc_filter_add_type_group(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_group(void)
{
	return _ctsvc_tc_filter_add_type_group(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_group(void)
{
	return _ctsvc_tc_filter_add_type_group(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_group(void)
{
	return _ctsvc_tc_filter_add_type_group(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_group = {
	.add_bool = _ctsvc_tc_filter_add_bool_group,
	.add_double = _ctsvc_tc_filter_add_double_group,
	.add_int = _ctsvc_tc_filter_add_int_group,
	.add_lli = _ctsvc_tc_filter_add_lli_group,
	.add_str = _ctsvc_tc_filter_add_str_group,
};
