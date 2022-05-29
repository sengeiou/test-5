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
#include "utc-contacts-service-record-name.h"

// _contacts_name
#define CTSVC_NAME_FIRST_C1 "FIRST_C"
#define CTSVC_NAME_FIRST_U1 "FIRST_U"
#define CTSVC_NAME_LAST_C1 "LAST_C"
#define CTSVC_NAME_LAST_U1 "LAST_U"
#define CTSVC_NAME_ADDITION_C1 "ADDITION_C"
#define CTSVC_NAME_ADDITION_U1 "ADDITION_U"
#define CTSVC_NAME_SUFFIX_C1 "SUFFIX_C"
#define CTSVC_NAME_SUFFIX_U1 "SUFFIX_U"
#define CTSVC_NAME_PREFIX_C1 "PREFIX_C"
#define CTSVC_NAME_PREFIX_U1 "PREFIX_U"
#define CTSVC_NAME_PHONETIC_FIRST_C1 "PHONETIC_FIRST_C"
#define CTSVC_NAME_PHONETIC_FIRST_U1 "PHONETIC_FIRST_U"
#define CTSVC_NAME_PHONETIC_MIDDLE_C1 "PHONETIC_MIDDLE_C"
#define CTSVC_NAME_PHONETIC_MIDDLE_U1 "PHONETIC_MIDDLE_U"
#define CTSVC_NAME_PHONETIC_LAST_C1 "PHONETIC_LAST_C"
#define CTSVC_NAME_PHONETIC_LAST_U1 "PHONETIC_LAST_U"
#define CTSVC_NAME_FIRST_C2 "FIRST_C2"
#define CTSVC_NAME_FIRST_U2 "FIRST_U2"
#define CTSVC_NAME_LAST_C2 "LAST_C2"
#define CTSVC_NAME_LAST_U2 "LAST_U2"
#define CTSVC_NAME_ADDITION_C2 "ADDITION_C2"
#define CTSVC_NAME_ADDITION_U2 "ADDITION_U2"
#define CTSVC_NAME_SUFFIX_C2 "SUFFIX_C2"
#define CTSVC_NAME_SUFFIX_U2 "SUFFIX_U2"
#define CTSVC_NAME_PREFIX_C2 "PREFIX_C2"
#define CTSVC_NAME_PREFIX_U2 "PREFIX_U2"
#define CTSVC_NAME_PHONETIC_FIRST_C2 "PHONETIC_FIRST_C2"
#define CTSVC_NAME_PHONETIC_FIRST_U2 "PHONETIC_FIRST_U2"
#define CTSVC_NAME_PHONETIC_MIDDLE_C2 "PHONETIC_MIDDLE_C2"
#define CTSVC_NAME_PHONETIC_MIDDLE_U2 "PHONETIC_MIDDLE_U2"
#define CTSVC_NAME_PHONETIC_LAST_C2 "PHONETIC_LAST_C2"
#define CTSVC_NAME_PHONETIC_LAST_U2 "PHONETIC_LAST_U2"
#define CTSVC_NAME_FIRST_C3 "FIRST_C3"
#define CTSVC_NAME_LAST_C3 "LAST_C"
#define CTSVC_NAME_ADDITION_C3 "ADDITION_C3"
#define CTSVC_NAME_SUFFIX_C3 "SUFFIX_C3"
#define CTSVC_NAME_PREFIX_C3 "PREFIX_C3"
#define CTSVC_NAME_PHONETIC_FIRST_C3 "PHONETIC_FIRST_C3"
#define CTSVC_NAME_PHONETIC_MIDDLE_C3 "PHONETIC_MIDDLE_C3"
#define CTSVC_NAME_PHONETIC_LAST_C3 "PHONETIC_LAST_C3"
#define CTSVC_NAME_FIRST_C4 "FIRST_C4"
#define CTSVC_NAME_LAST_C4 "LAST_C"
#define CTSVC_NAME_ADDITION_C4 "ADDITION_C4"
#define CTSVC_NAME_SUFFIX_C4 "SUFFIX_C4"
#define CTSVC_NAME_PREFIX_C4 "PREFIX_C4"
#define CTSVC_NAME_PHONETIC_FIRST_C4 "PHONETIC_FIRST_C4"
#define CTSVC_NAME_PHONETIC_MIDDLE_C4 "PHONETIC_MIDDLE_C4"
#define CTSVC_NAME_PHONETIC_LAST_C4 "PHONETIC_LAST_C4"
#define CTSVC_NAME_FIRST_C5 "FIRST_C5"
#define CTSVC_NAME_LAST_C5 "LAST_C"
#define CTSVC_NAME_ADDITION_C5 "ADDITION_C5"
#define CTSVC_NAME_SUFFIX_C5 "SUFFIX_C5"
#define CTSVC_NAME_PREFIX_C5 "PREFIX_C5"
#define CTSVC_NAME_PHONETIC_FIRST_C5 "PHONETIC_FIRST_C5"
#define CTSVC_NAME_PHONETIC_MIDDLE_C5 "PHONETIC_MIDDLE_C5"
#define CTSVC_NAME_PHONETIC_LAST_C5 "PHONETIC_LAST_C5"

ctsvc_view_s _view_name;
bool _view_name_load = false;

static void _ctsvc_tc_load_view_name()
{
	_view_name_load = true;
	// _contacts_name
	ctsvc_property_s name_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle, CTSVC_NAME_PHONETIC_MIDDLE_C1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_C1),
	};
	ctsvc_property_s name_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle,	CTSVC_NAME_PHONETIC_MIDDLE_U1),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_U1),
	};
	ctsvc_property_s name_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle, CTSVC_NAME_PHONETIC_MIDDLE_C2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_C2),
	};
	ctsvc_property_s name_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle,	CTSVC_NAME_PHONETIC_MIDDLE_U2),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_U2),
	};
	ctsvc_property_s name_create3[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle, CTSVC_NAME_PHONETIC_MIDDLE_C3),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_C3),
	};
	ctsvc_property_s name_create4[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle, CTSVC_NAME_PHONETIC_MIDDLE_C4),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_C4),
	};
	ctsvc_property_s name_create5[] = {
		ctsvc_tc_util_create_str_property(_contacts_name.first, CTSVC_NAME_FIRST_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.last, CTSVC_NAME_LAST_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.addition, CTSVC_NAME_ADDITION_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.suffix, CTSVC_NAME_SUFFIX_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.prefix, CTSVC_NAME_PREFIX_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_first, CTSVC_NAME_PHONETIC_FIRST_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_middle, CTSVC_NAME_PHONETIC_MIDDLE_C5),
		ctsvc_tc_util_create_str_property(_contacts_name.phonetic_last, CTSVC_NAME_PHONETIC_LAST_C5),
	};

	_view_name.create1_count = sizeof(name_create1)/sizeof(ctsvc_property_s);
	_view_name.create2_count = sizeof(name_create2)/sizeof(ctsvc_property_s);
	_view_name.create3_count = sizeof(name_create3)/sizeof(ctsvc_property_s);
	_view_name.create4_count = sizeof(name_create4)/sizeof(ctsvc_property_s);
	_view_name.create5_count = sizeof(name_create5)/sizeof(ctsvc_property_s);
	_view_name.update1_count = sizeof(name_update1)/sizeof(ctsvc_property_s);
	_view_name.update2_count = sizeof(name_update2)/sizeof(ctsvc_property_s);

	_view_name.create1 = calloc(_view_name.create1_count, sizeof(ctsvc_property_s));
	_view_name.create2 = calloc(_view_name.create2_count, sizeof(ctsvc_property_s));
	_view_name.create3 = calloc(_view_name.create3_count, sizeof(ctsvc_property_s));
	_view_name.create4 = calloc(_view_name.create4_count, sizeof(ctsvc_property_s));
	_view_name.create5 = calloc(_view_name.create5_count, sizeof(ctsvc_property_s));
	_view_name.update1 = calloc(_view_name.update1_count, sizeof(ctsvc_property_s));
	_view_name.update2 = calloc(_view_name.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_name.create1_count;i++)
		_view_name.create1[i] = name_create1[i];
	for (i=0;i<_view_name.create2_count;i++)
		_view_name.create2[i] = name_create2[i];
	for (i=0;i<_view_name.create3_count;i++)
		_view_name.create3[i] = name_create3[i];
	for (i=0;i<_view_name.create4_count;i++)
		_view_name.create4[i] = name_create4[i];
	for (i=0;i<_view_name.create5_count;i++)
		_view_name.create5[i] = name_create5[i];
	for (i=0;i<_view_name.update1_count;i++)
		_view_name.update1[i] = name_update1[i];
	for (i=0;i<_view_name.update2_count;i++)
		_view_name.update2[i] = name_update2[i];
}

static int _ctsvc_tc_record_free_property_name()
{
	if (false == _view_name_load)
		return -1;

	_view_name_load = false;

	free(_view_name.create1);
	free(_view_name.create2);
	free(_view_name.create3);
	free(_view_name.create4);
	free(_view_name.create5);
	free(_view_name.update1);
	free(_view_name.update2);

	return 0;
}

int ctsvc_tc_record_get_property_name(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_name_load)
		_ctsvc_tc_load_view_name();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_name.create1;
		*p_property_count = _view_name.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_name.create2;
		*p_property_count = _view_name.create2_count;
		break;
	case PROPERTY_TYPE_CREATE3:
		*p_properties = _view_name.create3;
		*p_property_count = _view_name.create3_count;
		break;
	case PROPERTY_TYPE_CREATE4:
		*p_properties = _view_name.create4;
		*p_property_count = _view_name.create4_count;
		break;
	case PROPERTY_TYPE_CREATE5:
		*p_properties = _view_name.create5;
		*p_property_count = _view_name.create5_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_name.update1;
		*p_property_count = _view_name.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_name.update2;
		*p_property_count = _view_name.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_name(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_name(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_name(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_name(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_name(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_name(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_name(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_name._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_name.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_name(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_name(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_name(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_name(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_name(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_name._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_name(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_name._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_name(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_name._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_name._uri)) {
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

static int _ctsvc_tc_record_compare_type_name(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_name(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_name(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_name(void)
{
	return _ctsvc_tc_record_compare_type_name(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_name = {
	.clone = _ctsvc_tc_record_clone_name,
	.create = _ctsvc_tc_record_create_name,
	.destroy = _ctsvc_tc_record_destroy_name,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_name,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_name,
	.get_double = _ctsvc_tc_record_get_double_name,
	.get_int = _ctsvc_tc_record_get_int_name,
	.get_lli = _ctsvc_tc_record_get_lli_name,
	.get_str = _ctsvc_tc_record_get_str_name,
	.get_str_p = _ctsvc_tc_record_get_str_p_name,
	.set_bool = _ctsvc_tc_record_set_bool_name,
	.set_double = _ctsvc_tc_record_set_double_name,
	.set_int = _ctsvc_tc_record_set_int_name,
	.set_lli = _ctsvc_tc_record_set_lli_name,
	.set_str = _ctsvc_tc_record_set_str_name,
	.free_properties = _ctsvc_tc_record_free_property_name,
};

static int _ctsvc_tc_filter_add_type_name(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_name._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_name(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_name(void)
{
	return _ctsvc_tc_filter_add_type_name(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_name(void)
{
	return _ctsvc_tc_filter_add_type_name(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_name(void)
{
	return _ctsvc_tc_filter_add_type_name(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_name(void)
{
	return _ctsvc_tc_filter_add_type_name(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_name(void)
{
	return _ctsvc_tc_filter_add_type_name(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_name = {
	.add_bool = _ctsvc_tc_filter_add_bool_name,
	.add_double = _ctsvc_tc_filter_add_double_name,
	.add_int = _ctsvc_tc_filter_add_int_name,
	.add_lli = _ctsvc_tc_filter_add_lli_name,
	.add_str = _ctsvc_tc_filter_add_str_name,
};
