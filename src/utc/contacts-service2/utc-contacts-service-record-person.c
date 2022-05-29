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
#include "utc-contacts-service-record-person.h"

// _contacts_person
#define CTSVC_PERSON_RINGTONE_PATH_U1 CTSVC_RINGTONE_PATH_U1
#define CTSVC_PERSON_VIBRATION_U1 CTSVC_VIBRATION_U1
#define CTSVC_PERSON_IS_FAVORITE_U1 true
#define CTSVC_PERSON_MESSAGE_ALERT_U1 CTSVC_MESSAGE_ALERT_U1
#define CTSVC_PERSON_RINGTONE_PATH_U2 CTSVC_RINGTONE_PATH_U2
#define CTSVC_PERSON_VIBRATION_U2 CTSVC_VIBRATION_U2
#define CTSVC_PERSON_IS_FAVORITE_U2 true
#define CTSVC_PERSON_MESSAGE_ALERT_U2 CTSVC_MESSAGE_ALERT_U2


ctsvc_view_s _view_person;
bool _view_person_load = false;

static void _ctsvc_tc_load_view_person()
{
	_view_person_load = true;
	// _contacts_person
	ctsvc_property_s person_create1[] = {
	};
	ctsvc_property_s person_create2[] = {
	};
	ctsvc_property_s person_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_person.ringtone_path, CTSVC_PERSON_RINGTONE_PATH_U1),
		ctsvc_tc_util_create_str_property(_contacts_person.vibration, CTSVC_PERSON_VIBRATION_U1),
		ctsvc_tc_util_create_bool_property(_contacts_person.is_favorite, CTSVC_PERSON_IS_FAVORITE_U1),
		ctsvc_tc_util_create_str_property(_contacts_person.message_alert, CTSVC_PERSON_MESSAGE_ALERT_U1),
	};
	ctsvc_property_s person_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_person.ringtone_path, CTSVC_PERSON_RINGTONE_PATH_U2),
		ctsvc_tc_util_create_str_property(_contacts_person.vibration, CTSVC_PERSON_VIBRATION_U2),
		ctsvc_tc_util_create_bool_property(_contacts_person.is_favorite, CTSVC_PERSON_IS_FAVORITE_U2),
		ctsvc_tc_util_create_str_property(_contacts_person.message_alert, CTSVC_PERSON_MESSAGE_ALERT_U2),
	};


	_view_person.create1_count = sizeof(person_create1)/sizeof(ctsvc_property_s);
	_view_person.create2_count = sizeof(person_create2)/sizeof(ctsvc_property_s);
	_view_person.update1_count = sizeof(person_update1)/sizeof(ctsvc_property_s);
	_view_person.update2_count = sizeof(person_update2)/sizeof(ctsvc_property_s);

	_view_person.create1 = calloc(_view_person.create1_count, sizeof(ctsvc_property_s));
	_view_person.create2 = calloc(_view_person.create2_count, sizeof(ctsvc_property_s));
	_view_person.update1 = calloc(_view_person.update1_count, sizeof(ctsvc_property_s));
	_view_person.update2 = calloc(_view_person.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_person.create1_count;i++)
		_view_person.create1[i] = person_create1[i];
	for (i=0;i<_view_person.create2_count;i++)
		_view_person.create2[i] = person_create2[i];
	for (i=0;i<_view_person.update1_count;i++)
		_view_person.update1[i] = person_update1[i];
	for (i=0;i<_view_person.update2_count;i++)
		_view_person.update2[i] = person_update2[i];
}

static int _ctsvc_tc_record_free_property_person()
{
	int i;

	if (false == _view_person_load)
		return -1;

	_view_person_load = false;

	for (i=0;i<_view_person.create1_count;i++) {
		if (_contacts_person.ringtone_path == _view_person.create1[i].property_id
			|| _contacts_person.vibration == _view_person.create1[i].property_id
			|| _contacts_person.message_alert == _view_person.create1[i].property_id)
			free(_view_person.create1[i].val.str_val);
	}
	for (i=0;i<_view_person.create2_count;i++) {
		if (_contacts_person.ringtone_path == _view_person.create2[i].property_id
			|| _contacts_person.vibration == _view_person.create2[i].property_id
			|| _contacts_person.message_alert == _view_person.create2[i].property_id)
			free(_view_person.create2[i].val.str_val);
	}
	for (i=0;i<_view_person.update1_count;i++) {
		if (_contacts_person.ringtone_path == _view_person.update1[i].property_id
			|| _contacts_person.vibration == _view_person.update1[i].property_id
			|| _contacts_person.message_alert == _view_person.update1[i].property_id)
			free(_view_person.update1[i].val.str_val);
	}
	for (i=0;i<_view_person.update2_count;i++) {
		if (_contacts_person.ringtone_path == _view_person.update2[i].property_id
			|| _contacts_person.vibration == _view_person.update2[i].property_id
			|| _contacts_person.message_alert == _view_person.update2[i].property_id)
			free(_view_person.update2[i].val.str_val);
	}

	free(_view_person.create1);
	free(_view_person.create2);
	free(_view_person.update1);
	free(_view_person.update2);

	return 0;
}

int ctsvc_tc_record_get_property_person(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_person_load)
		_ctsvc_tc_load_view_person();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_person.create1;
		*p_property_count = _view_person.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_person.create2;
		*p_property_count = _view_person.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_person.update1;
		*p_property_count = _view_person.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_person.update2;
		*p_property_count = _view_person.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_person(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_person(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_person(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_person(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_person(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_person(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}



static int _ctsvc_tc_record_clone_person(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_person._uri, &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_person(PROPERTY_TYPE_UPDATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_person(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_person._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_person(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_person._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_person(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_person._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_person._uri)) {
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

static int _ctsvc_tc_record_compare_type_person(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_person._uri, &record))) break;
		if (0 != (ret = ctsvc_tc_record_update_person(record, PROPERTY_TYPE_UPDATE1))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_person(PROPERTY_TYPE_UPDATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_person(void)
{
	return _ctsvc_tc_record_compare_type_person(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_person = {
	.clone = _ctsvc_tc_record_clone_person,
	.create = _ctsvc_tc_record_create_person,
	.destroy = _ctsvc_tc_record_destroy_person,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_person,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_person,
	.get_double = _ctsvc_tc_record_get_double_person,
	.get_int = _ctsvc_tc_record_get_int_person,
	.get_lli = _ctsvc_tc_record_get_lli_person,
	.get_str = _ctsvc_tc_record_get_str_person,
	.get_str_p = _ctsvc_tc_record_get_str_p_person,
	.set_bool = _ctsvc_tc_record_set_bool_person,
	.set_double = _ctsvc_tc_record_set_double_person,
	.set_int = _ctsvc_tc_record_set_int_person,
	.set_lli = _ctsvc_tc_record_set_lli_person,
	.set_str = _ctsvc_tc_record_set_str_person,
	.free_properties = _ctsvc_tc_record_free_property_person,
};


static int _ctsvc_tc_filter_add_type_person(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_person._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_person(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_person(void)
{
	return _ctsvc_tc_filter_add_type_person(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_person(void)
{
	return _ctsvc_tc_filter_add_type_person(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_person(void)
{
	return _ctsvc_tc_filter_add_type_person(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_person(void)
{
	return _ctsvc_tc_filter_add_type_person(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_person(void)
{
	return _ctsvc_tc_filter_add_type_person(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_person = {
	.add_bool = _ctsvc_tc_filter_add_bool_person,
	.add_double = _ctsvc_tc_filter_add_double_person,
	.add_int = _ctsvc_tc_filter_add_int_person,
	.add_lli = _ctsvc_tc_filter_add_lli_person,
	.add_str = _ctsvc_tc_filter_add_str_person,
};
