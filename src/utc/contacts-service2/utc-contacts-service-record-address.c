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
#include "utc-contacts-service-record-address.h"

// _contacts_address
#define CTSVC_ADDRESS_TYPE_C1 CONTACTS_ADDRESS_TYPE_HOME
#define CTSVC_ADDRESS_TYPE_U1 CONTACTS_ADDRESS_TYPE_CUSTOM
#define CTSVC_ADDRESS_LABEL_U1 "LABEL_U"
#define CTSVC_ADDRESS_POSTBOX_C1 "POSTBOX_C"
#define CTSVC_ADDRESS_POSTBOX_U1 "POSTBOX_U"
#define CTSVC_ADDRESS_EXTENDED_C1 "EXTENDED_C"
#define CTSVC_ADDRESS_EXTENDED_U1 "EXTENDED_U"
#define CTSVC_ADDRESS_STREET_C1 "STREET_C"
#define CTSVC_ADDRESS_STREET_U1 "STREET_U"
#define CTSVC_ADDRESS_LOCALITY_C1 "LOCALITY_C"
#define CTSVC_ADDRESS_LOCALITY_U1 "LOCALITY_U"
#define CTSVC_ADDRESS_REGION_C1 "REGION_C"
#define CTSVC_ADDRESS_REGION_U1 "REGION_U"
#define CTSVC_ADDRESS_POSTAL_CODE_C1 "POSTAL_CODE_C"
#define CTSVC_ADDRESS_POSTAL_CODE_U1 "POSTAL_CODE_U"
#define CTSVC_ADDRESS_COUNTRY_C1 "COUNTRY_C"
#define CTSVC_ADDRESS_COUNTRY_U1 "COUNTRY_U"
#define CTSVC_ADDRESS_TYPE_C2 CONTACTS_ADDRESS_TYPE_HOME
#define CTSVC_ADDRESS_TYPE_U2 CONTACTS_ADDRESS_TYPE_CUSTOM
#define CTSVC_ADDRESS_LABEL_U2 "LABEL_U2"
#define CTSVC_ADDRESS_POSTBOX_C2 "POSTBOX_C2"
#define CTSVC_ADDRESS_POSTBOX_U2 "POSTBOX_U2"
#define CTSVC_ADDRESS_EXTENDED_C2 "EXTENDED_C2"
#define CTSVC_ADDRESS_EXTENDED_U2 "EXTENDED_U2"
#define CTSVC_ADDRESS_STREET_C2 "STREET_C2"
#define CTSVC_ADDRESS_STREET_U2 "STREET_U2"
#define CTSVC_ADDRESS_LOCALITY_C2 "LOCALITY_C2"
#define CTSVC_ADDRESS_LOCALITY_U2 "LOCALITY_U2"
#define CTSVC_ADDRESS_REGION_C2 "REGION_C2"
#define CTSVC_ADDRESS_REGION_U2 "REGION_U2"
#define CTSVC_ADDRESS_POSTAL_CODE_C2 "POSTAL_CODE_C2"
#define CTSVC_ADDRESS_POSTAL_CODE_U2 "POSTAL_CODE_U2"
#define CTSVC_ADDRESS_COUNTRY_C2 "COUNTRY_C2"
#define CTSVC_ADDRESS_COUNTRY_U2 "COUNTRY_U2"

ctsvc_view_s _view_address;
bool _view_address_load = false;

static void _ctsvc_tc_load_view_address()
{
	_view_address_load = true;
	ctsvc_property_s address_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_address.type, CTSVC_ADDRESS_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.postbox, CTSVC_ADDRESS_POSTBOX_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.extended, CTSVC_ADDRESS_EXTENDED_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.street, CTSVC_ADDRESS_STREET_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.locality, CTSVC_ADDRESS_LOCALITY_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.region, CTSVC_ADDRESS_REGION_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.postal_code, CTSVC_ADDRESS_POSTAL_CODE_C1),
		ctsvc_tc_util_create_str_property(_contacts_address.country, CTSVC_ADDRESS_COUNTRY_C1),
	};
	ctsvc_property_s address_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_address.type, CTSVC_ADDRESS_TYPE_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.label, CTSVC_ADDRESS_LABEL_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.postbox, CTSVC_ADDRESS_POSTBOX_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.extended, CTSVC_ADDRESS_EXTENDED_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.street, CTSVC_ADDRESS_STREET_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.locality, CTSVC_ADDRESS_LOCALITY_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.region, CTSVC_ADDRESS_REGION_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.postal_code, CTSVC_ADDRESS_POSTAL_CODE_U1),
		ctsvc_tc_util_create_str_property(_contacts_address.country, CTSVC_ADDRESS_COUNTRY_U1),
	};
	ctsvc_property_s address_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_address.type, CTSVC_ADDRESS_TYPE_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.postbox, CTSVC_ADDRESS_POSTBOX_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.extended, CTSVC_ADDRESS_EXTENDED_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.street, CTSVC_ADDRESS_STREET_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.locality, CTSVC_ADDRESS_LOCALITY_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.region, CTSVC_ADDRESS_REGION_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.postal_code, CTSVC_ADDRESS_POSTAL_CODE_C2),
		ctsvc_tc_util_create_str_property(_contacts_address.country, CTSVC_ADDRESS_COUNTRY_C2),
	};
	ctsvc_property_s address_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_address.type, CTSVC_ADDRESS_TYPE_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.label, CTSVC_ADDRESS_LABEL_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.postbox, CTSVC_ADDRESS_POSTBOX_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.extended, CTSVC_ADDRESS_EXTENDED_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.street, CTSVC_ADDRESS_STREET_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.locality, CTSVC_ADDRESS_LOCALITY_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.region, CTSVC_ADDRESS_REGION_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.postal_code, CTSVC_ADDRESS_POSTAL_CODE_U2),
		ctsvc_tc_util_create_str_property(_contacts_address.country, CTSVC_ADDRESS_COUNTRY_U2),
	};

	_view_address.create1_count = sizeof(address_create1)/sizeof(ctsvc_property_s);
	_view_address.create2_count = sizeof(address_create2)/sizeof(ctsvc_property_s);
	_view_address.update1_count = sizeof(address_update1)/sizeof(ctsvc_property_s);
	_view_address.update2_count = sizeof(address_update2)/sizeof(ctsvc_property_s);

	_view_address.create1 = calloc(_view_address.create1_count, sizeof(ctsvc_property_s));
	_view_address.create2 = calloc(_view_address.create2_count, sizeof(ctsvc_property_s));
	_view_address.update1 = calloc(_view_address.update1_count, sizeof(ctsvc_property_s));
	_view_address.update2 = calloc(_view_address.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_address.create1_count;i++)
		_view_address.create1[i] = address_create1[i];
	for (i=0;i<_view_address.create2_count;i++)
		_view_address.create2[i] = address_create2[i];
	for (i=0;i<_view_address.update1_count;i++)
		_view_address.update1[i] = address_update1[i];
	for (i=0;i<_view_address.update2_count;i++)
		_view_address.update2[i] = address_update2[i];
}

static int _ctsvc_tc_record_free_property_address()
{
	if (false == _view_address_load)
		return -1;

	_view_address_load = false;

	free(_view_address.create1);
	free(_view_address.create2);
	free(_view_address.update1);
	free(_view_address.update2);

	return 0;
}

int ctsvc_tc_record_get_property_address(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_address_load)
		_ctsvc_tc_load_view_address();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_address.create1;
		*p_property_count = _view_address.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_address.create2;
		*p_property_count = _view_address.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_address.update1;
		*p_property_count = _view_address.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_address.update2;
		*p_property_count = _view_address.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_address(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_address(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_address(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_address(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_address(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_address(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_address(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_address._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_address.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_address(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_address(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_address(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_address(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_address(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_address._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_address(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_address._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_address(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_address._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_address._uri)) {
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

static int _ctsvc_tc_record_compare_type_address(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_address(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_address(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_address(void)
{
	return _ctsvc_tc_record_compare_type_address(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_address = {
	.clone = _ctsvc_tc_record_clone_address,
	.create = _ctsvc_tc_record_create_address,
	.destroy = _ctsvc_tc_record_destroy_address,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_address,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_address,
	.get_double = _ctsvc_tc_record_get_double_address,
	.get_int = _ctsvc_tc_record_get_int_address,
	.get_lli = _ctsvc_tc_record_get_lli_address,
	.get_str = _ctsvc_tc_record_get_str_address,
	.get_str_p = _ctsvc_tc_record_get_str_p_address,
	.set_bool = _ctsvc_tc_record_set_bool_address,
	.set_double = _ctsvc_tc_record_set_double_address,
	.set_int = _ctsvc_tc_record_set_int_address,
	.set_lli = _ctsvc_tc_record_set_lli_address,
	.set_str = _ctsvc_tc_record_set_str_address,
	.free_properties = _ctsvc_tc_record_free_property_address,
};

static int _ctsvc_tc_filter_add_type_address(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_address._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_address(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_address(void)
{
	return _ctsvc_tc_filter_add_type_address(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_address(void)
{
	return _ctsvc_tc_filter_add_type_address(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_address(void)
{
	return _ctsvc_tc_filter_add_type_address(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_address(void)
{
	return _ctsvc_tc_filter_add_type_address(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_address(void)
{
	return _ctsvc_tc_filter_add_type_address(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_address = {
	.add_bool = _ctsvc_tc_filter_add_bool_address,
	.add_double = _ctsvc_tc_filter_add_double_address,
	.add_int = _ctsvc_tc_filter_add_int_address,
	.add_lli = _ctsvc_tc_filter_add_lli_address,
	.add_str = _ctsvc_tc_filter_add_str_address,
};
