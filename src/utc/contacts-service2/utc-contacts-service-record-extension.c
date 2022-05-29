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
#include "utc-contacts-service-record-extension.h"

// _contacts_extension
#define CTSVC_EXTENSION_DATA1_C1 1
#define CTSVC_EXTENSION_DATA1_U1 2
#define CTSVC_EXTENSION_DATA2_C1 "DATA2_C"
#define CTSVC_EXTENSION_DATA2_U1 "DATA2_U"
#define CTSVC_EXTENSION_DATA3_C1 "DATA3_C"
#define CTSVC_EXTENSION_DATA3_U1 "DATA3_U"
#define CTSVC_EXTENSION_DATA4_C1 "DATA4_C"
#define CTSVC_EXTENSION_DATA4_U1 "DATA4_U"
#define CTSVC_EXTENSION_DATA5_C1 "DATA5_C"
#define CTSVC_EXTENSION_DATA5_U1 "DATA5_U"
#define CTSVC_EXTENSION_DATA6_C1 "DATA6_C"
#define CTSVC_EXTENSION_DATA6_U1 "DATA6_U"
#define CTSVC_EXTENSION_DATA7_C1 "DATA7_C"
#define CTSVC_EXTENSION_DATA7_U1 "DATA7_U"
#define CTSVC_EXTENSION_DATA8_C1 "DATA8_C"
#define CTSVC_EXTENSION_DATA8_U1 "DATA8_U"
#define CTSVC_EXTENSION_DATA9_C1 "DATA9_C"
#define CTSVC_EXTENSION_DATA9_U1 "DATA9_U"
#define CTSVC_EXTENSION_DATA10_C1 "DATA10_C"
#define CTSVC_EXTENSION_DATA10_U1 "DATA10_U"
#define CTSVC_EXTENSION_DATA11_C1 "DATA11_C"
#define CTSVC_EXTENSION_DATA11_U1 "DATA11_U"
#define CTSVC_EXTENSION_DATA12_C1 "DATA12_C"
#define CTSVC_EXTENSION_DATA12_U1 "DATA12_U"
#define CTSVC_EXTENSION_DATA1_C2 2
#define CTSVC_EXTENSION_DATA1_U2 2
#define CTSVC_EXTENSION_DATA2_C2 "DATA2_C2"
#define CTSVC_EXTENSION_DATA2_U2 "DATA2_U2"
#define CTSVC_EXTENSION_DATA3_C2 "DATA3_C2"
#define CTSVC_EXTENSION_DATA3_U2 "DATA3_U2"
#define CTSVC_EXTENSION_DATA4_C2 "DATA4_C2"
#define CTSVC_EXTENSION_DATA4_U2 "DATA4_U2"
#define CTSVC_EXTENSION_DATA5_C2 "DATA5_C2"
#define CTSVC_EXTENSION_DATA5_U2 "DATA5_U2"
#define CTSVC_EXTENSION_DATA6_C2 "DATA6_C2"
#define CTSVC_EXTENSION_DATA6_U2 "DATA6_U2"
#define CTSVC_EXTENSION_DATA7_C2 "DATA7_C2"
#define CTSVC_EXTENSION_DATA7_U2 "DATA7_U2"
#define CTSVC_EXTENSION_DATA8_C2 "DATA8_C2"
#define CTSVC_EXTENSION_DATA8_U2 "DATA8_U2"
#define CTSVC_EXTENSION_DATA9_C2 "DATA9_C2"
#define CTSVC_EXTENSION_DATA9_U2 "DATA9_U2"
#define CTSVC_EXTENSION_DATA10_C2 "DATA10_C2"
#define CTSVC_EXTENSION_DATA10_U2 "DATA10_U2"
#define CTSVC_EXTENSION_DATA11_C2 "DATA11_C2"
#define CTSVC_EXTENSION_DATA11_U2 "DATA11_U2"
#define CTSVC_EXTENSION_DATA12_C2 "DATA12_C2"
#define CTSVC_EXTENSION_DATA12_U2 "DATA12_U2"

ctsvc_view_s _view_extension;
bool _view_extension_load = false;

static void _ctsvc_tc_load_view_extension()
{
	_view_extension_load = true;
	// _contacts_extension
	ctsvc_property_s extension_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_extension.data1, CTSVC_EXTENSION_DATA1_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data2, CTSVC_EXTENSION_DATA2_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data3, CTSVC_EXTENSION_DATA3_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data4, CTSVC_EXTENSION_DATA4_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data5, CTSVC_EXTENSION_DATA5_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data6, CTSVC_EXTENSION_DATA6_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data7, CTSVC_EXTENSION_DATA7_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data8, CTSVC_EXTENSION_DATA8_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data9, CTSVC_EXTENSION_DATA9_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data10, CTSVC_EXTENSION_DATA10_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data11, CTSVC_EXTENSION_DATA11_C1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data12, CTSVC_EXTENSION_DATA12_C1),
	};
	ctsvc_property_s extension_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_extension.data1, CTSVC_EXTENSION_DATA1_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data2, CTSVC_EXTENSION_DATA2_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data3, CTSVC_EXTENSION_DATA3_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data4, CTSVC_EXTENSION_DATA4_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data5, CTSVC_EXTENSION_DATA5_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data6, CTSVC_EXTENSION_DATA6_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data7, CTSVC_EXTENSION_DATA7_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data8, CTSVC_EXTENSION_DATA8_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data9, CTSVC_EXTENSION_DATA9_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data10, CTSVC_EXTENSION_DATA10_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data11, CTSVC_EXTENSION_DATA11_U1),
		ctsvc_tc_util_create_str_property(_contacts_extension.data12, CTSVC_EXTENSION_DATA12_U1),
	};
	ctsvc_property_s extension_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_extension.data1, CTSVC_EXTENSION_DATA1_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data2, CTSVC_EXTENSION_DATA2_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data3, CTSVC_EXTENSION_DATA3_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data4, CTSVC_EXTENSION_DATA4_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data5, CTSVC_EXTENSION_DATA5_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data6, CTSVC_EXTENSION_DATA6_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data7, CTSVC_EXTENSION_DATA7_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data8, CTSVC_EXTENSION_DATA8_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data9, CTSVC_EXTENSION_DATA9_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data10, CTSVC_EXTENSION_DATA10_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data11, CTSVC_EXTENSION_DATA11_C2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data12, CTSVC_EXTENSION_DATA12_C2),
	};
	ctsvc_property_s extension_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_extension.data1, CTSVC_EXTENSION_DATA1_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data2, CTSVC_EXTENSION_DATA2_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data3, CTSVC_EXTENSION_DATA3_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data4, CTSVC_EXTENSION_DATA4_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data5, CTSVC_EXTENSION_DATA5_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data6, CTSVC_EXTENSION_DATA6_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data7, CTSVC_EXTENSION_DATA7_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data8, CTSVC_EXTENSION_DATA8_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data9, CTSVC_EXTENSION_DATA9_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data10, CTSVC_EXTENSION_DATA10_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data11, CTSVC_EXTENSION_DATA11_U2),
		ctsvc_tc_util_create_str_property(_contacts_extension.data12, CTSVC_EXTENSION_DATA12_U2),
	};

	_view_extension.create1_count = sizeof(extension_create1)/sizeof(ctsvc_property_s);
	_view_extension.create2_count = sizeof(extension_create2)/sizeof(ctsvc_property_s);
	_view_extension.update1_count = sizeof(extension_update1)/sizeof(ctsvc_property_s);
	_view_extension.update2_count = sizeof(extension_update2)/sizeof(ctsvc_property_s);

	_view_extension.create1 = calloc(_view_extension.create1_count, sizeof(ctsvc_property_s));
	_view_extension.create2 = calloc(_view_extension.create2_count, sizeof(ctsvc_property_s));
	_view_extension.update1 = calloc(_view_extension.update1_count, sizeof(ctsvc_property_s));
	_view_extension.update2 = calloc(_view_extension.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_extension.create1_count;i++)
		_view_extension.create1[i] = extension_create1[i];
	for (i=0;i<_view_extension.create2_count;i++)
		_view_extension.create2[i] = extension_create2[i];
	for (i=0;i<_view_extension.update1_count;i++)
		_view_extension.update1[i] = extension_update1[i];
	for (i=0;i<_view_extension.update2_count;i++)
		_view_extension.update2[i] = extension_update2[i];
}

static int _ctsvc_tc_record_free_property_extension()
{
	if (false == _view_extension_load)
		return -1;

	_view_extension_load = false;

	free(_view_extension.create1);
	free(_view_extension.create2);
	free(_view_extension.update1);
	free(_view_extension.update2);

	return 0;
}

int ctsvc_tc_record_get_property_extension(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_extension_load)
		_ctsvc_tc_load_view_extension();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_extension.create1;
		*p_property_count = _view_extension.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_extension.create2;
		*p_property_count = _view_extension.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_extension.update1;
		*p_property_count = _view_extension.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_extension.update2;
		*p_property_count = _view_extension.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_extension(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_extension(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_extension(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_extension(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_extension(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_extension(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_extension(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_extension._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_extension.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_extension(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_extension(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_extension(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_extension(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_extension(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_extension._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_extension(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_extension._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_extension(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_extension._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_extension._uri)) {
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

static int _ctsvc_tc_record_compare_type_extension(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_extension(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_extension(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_extension(void)
{
	return _ctsvc_tc_record_compare_type_extension(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_extension = {
	.clone = _ctsvc_tc_record_clone_extension,
	.create = _ctsvc_tc_record_create_extension,
	.destroy = _ctsvc_tc_record_destroy_extension,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_extension,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_extension,
	.get_double = _ctsvc_tc_record_get_double_extension,
	.get_int = _ctsvc_tc_record_get_int_extension,
	.get_lli = _ctsvc_tc_record_get_lli_extension,
	.get_str = _ctsvc_tc_record_get_str_extension,
	.get_str_p = _ctsvc_tc_record_get_str_p_extension,
	.set_bool = _ctsvc_tc_record_set_bool_extension,
	.set_double = _ctsvc_tc_record_set_double_extension,
	.set_int = _ctsvc_tc_record_set_int_extension,
	.set_lli = _ctsvc_tc_record_set_lli_extension,
	.set_str = _ctsvc_tc_record_set_str_extension,
	.free_properties = _ctsvc_tc_record_free_property_extension,
};

static int _ctsvc_tc_filter_add_type_extension(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_extension._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_extension(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_extension(void)
{
	return _ctsvc_tc_filter_add_type_extension(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_extension(void)
{
	return _ctsvc_tc_filter_add_type_extension(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_extension(void)
{
	return _ctsvc_tc_filter_add_type_extension(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_extension(void)
{
	return _ctsvc_tc_filter_add_type_extension(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_extension(void)
{
	return _ctsvc_tc_filter_add_type_extension(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_extension = {
	.add_bool = _ctsvc_tc_filter_add_bool_extension,
	.add_double = _ctsvc_tc_filter_add_double_extension,
	.add_int = _ctsvc_tc_filter_add_int_extension,
	.add_lli = _ctsvc_tc_filter_add_lli_extension,
	.add_str = _ctsvc_tc_filter_add_str_extension,
};
