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
#include "utc-contacts-service-record-number.h"

// _contacts_number
#define CTSVC_NUMBER_TYPE_C1 CONTACTS_NUMBER_TYPE_HOME
#define CTSVC_NUMBER_TYPE_U1 CONTACTS_NUMBER_TYPE_CUSTOM
#define CTSVC_NUMBER_LABEL_U1 "LABEL_U"
#define CTSVC_NUMBER_NUMBER_C1 "010-1111-1111"
#define CTSVC_NUMBER_NUMBER_U1 "010-2222-2222"
#define CTSVC_NUMBER_TYPE_C2 CONTACTS_NUMBER_TYPE_HOME
#define CTSVC_NUMBER_TYPE_U2 CONTACTS_NUMBER_TYPE_CUSTOM
#define CTSVC_NUMBER_LABEL_U2 "LABEL_U2"
#define CTSVC_NUMBER_NUMBER_C2 "010-3333-3333"
#define CTSVC_NUMBER_NUMBER_U2 "010-4444-4444"
#define CTSVC_NUMBER_NUMBER_C3 CTSVC_NUMBER_NUMBER_C1
#define CTSVC_NUMBER_NUMBER_C4 "010-5555-5555"
#define CTSVC_NUMBER_NUMBER_C5 "010-6666-6666"

ctsvc_view_s _view_number;
bool _view_number_load = false;

static void _ctsvc_tc_load_view_number()
{
	_view_number_load = true;
	// _contacts_number
	ctsvc_property_s number_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_C1),
	};
	ctsvc_property_s number_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_U1),
		ctsvc_tc_util_create_str_property(_contacts_number.label, CTSVC_NUMBER_LABEL_U1),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_U1),
	};
	ctsvc_property_s number_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_C2),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_C2),
	};
	ctsvc_property_s number_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_U2),
		ctsvc_tc_util_create_str_property(_contacts_number.label, CTSVC_NUMBER_LABEL_U2),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_U2),
	};
	ctsvc_property_s number_create3[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_C3),
	};
	ctsvc_property_s number_create4[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_C4),
	};
	ctsvc_property_s number_create5[] = {
		ctsvc_tc_util_create_int_property(_contacts_number.type, CTSVC_NUMBER_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_number.number, CTSVC_NUMBER_NUMBER_C5),
	};


	_view_number.create1_count = sizeof(number_create1)/sizeof(ctsvc_property_s);
	_view_number.create2_count = sizeof(number_create2)/sizeof(ctsvc_property_s);
	_view_number.create3_count = sizeof(number_create3)/sizeof(ctsvc_property_s);
	_view_number.create4_count = sizeof(number_create4)/sizeof(ctsvc_property_s);
	_view_number.create5_count = sizeof(number_create5)/sizeof(ctsvc_property_s);
	_view_number.update1_count = sizeof(number_update1)/sizeof(ctsvc_property_s);
	_view_number.update2_count = sizeof(number_update2)/sizeof(ctsvc_property_s);

	_view_number.create1 = calloc(_view_number.create1_count, sizeof(ctsvc_property_s));
	_view_number.create2 = calloc(_view_number.create2_count, sizeof(ctsvc_property_s));
	_view_number.create3 = calloc(_view_number.create3_count, sizeof(ctsvc_property_s));
	_view_number.create4 = calloc(_view_number.create4_count, sizeof(ctsvc_property_s));
	_view_number.create5 = calloc(_view_number.create5_count, sizeof(ctsvc_property_s));
	_view_number.update1 = calloc(_view_number.update1_count, sizeof(ctsvc_property_s));
	_view_number.update2 = calloc(_view_number.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_number.create1_count;i++)
		_view_number.create1[i] = number_create1[i];
	for (i=0;i<_view_number.create2_count;i++)
		_view_number.create2[i] = number_create2[i];
	for (i=0;i<_view_number.create3_count;i++)
		_view_number.create3[i] = number_create3[i];
	for (i=0;i<_view_number.create4_count;i++)
		_view_number.create4[i] = number_create4[i];
	for (i=0;i<_view_number.create5_count;i++)
		_view_number.create5[i] = number_create5[i];
	for (i=0;i<_view_number.update1_count;i++)
		_view_number.update1[i] = number_update1[i];
	for (i=0;i<_view_number.update2_count;i++)
		_view_number.update2[i] = number_update2[i];
}

static int _ctsvc_tc_record_free_property_number()
{
	if (false == _view_number_load)
		return -1;

	_view_number_load = false;

	free(_view_number.create1);
	free(_view_number.create2);
	free(_view_number.create3);
	free(_view_number.create4);
	free(_view_number.create5);
	free(_view_number.update1);
	free(_view_number.update2);

	return 0;
}

int ctsvc_tc_record_get_property_number(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_number_load)
		_ctsvc_tc_load_view_number();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_number.create1;
		*p_property_count = _view_number.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_number.create2;
		*p_property_count = _view_number.create2_count;
		break;
	case PROPERTY_TYPE_CREATE3:
		*p_properties = _view_number.create3;
		*p_property_count = _view_number.create3_count;
		break;
	case PROPERTY_TYPE_CREATE4:
		*p_properties = _view_number.create4;
		*p_property_count = _view_number.create4_count;
		break;
	case PROPERTY_TYPE_CREATE5:
		*p_properties = _view_number.create5;
		*p_property_count = _view_number.create5_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_number.update1;
		*p_property_count = _view_number.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_number.update2;
		*p_property_count = _view_number.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_number(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_number(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_number(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_number(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_number(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_number(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_number(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_number._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_number.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_number(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_number(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_number(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_number(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_number(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_number._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_number(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_number._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_number(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_number._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_number._uri)) {
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

static int _ctsvc_tc_record_compare_type_number(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_number(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_number(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_number(void)
{
	return _ctsvc_tc_record_compare_type_number(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_number = {
	.clone = _ctsvc_tc_record_clone_number,
	.create = _ctsvc_tc_record_create_number,
	.destroy = _ctsvc_tc_record_destroy_number,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_number,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_number,
	.get_double = _ctsvc_tc_record_get_double_number,
	.get_int = _ctsvc_tc_record_get_int_number,
	.get_lli = _ctsvc_tc_record_get_lli_number,
	.get_str = _ctsvc_tc_record_get_str_number,
	.get_str_p = _ctsvc_tc_record_get_str_p_number,
	.set_bool = _ctsvc_tc_record_set_bool_number,
	.set_double = _ctsvc_tc_record_set_double_number,
	.set_int = _ctsvc_tc_record_set_int_number,
	.set_lli = _ctsvc_tc_record_set_lli_number,
	.set_str = _ctsvc_tc_record_set_str_number,
	.free_properties = _ctsvc_tc_record_free_property_number,
};



static int _ctsvc_tc_filter_add_type_number(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_number._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_number(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_number(void)
{
	return _ctsvc_tc_filter_add_type_number(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_number(void)
{
	return _ctsvc_tc_filter_add_type_number(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_number(void)
{
	return _ctsvc_tc_filter_add_type_number(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_number(void)
{
	return _ctsvc_tc_filter_add_type_number(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_number(void)
{
	return _ctsvc_tc_filter_add_type_number(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_number = {
	.add_bool = _ctsvc_tc_filter_add_bool_number,
	.add_double = _ctsvc_tc_filter_add_double_number,
	.add_int = _ctsvc_tc_filter_add_int_number,
	.add_lli = _ctsvc_tc_filter_add_lli_number,
	.add_str = _ctsvc_tc_filter_add_str_number,
};
