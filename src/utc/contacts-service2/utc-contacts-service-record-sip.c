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
#include "utc-contacts-service-record-sip.h"

// _contacts_sip
#define CTSVC_SIP_TYPE_C1 CONTACTS_SIP_TYPE_HOME
#define CTSVC_SIP_TYPE_U1 CONTACTS_SIP_TYPE_CUSTOM
#define CTSVC_SIP_ADDRESS_C1 "ADDRESS_C1"
#define CTSVC_SIP_ADDRESS_U1 "ADDRESS_U1"
#define CTSVC_SIP_LABEL_U1 "LABEL_U"
#define CTSVC_SIP_TYPE_C2 CONTACTS_SIP_TYPE_HOME
#define CTSVC_SIP_TYPE_U2 CONTACTS_SIP_TYPE_CUSTOM
#define CTSVC_SIP_ADDRESS_C2 "ADDRESS_C2"
#define CTSVC_SIP_ADDRESS_U2 "ADDRESS_U2"
#define CTSVC_SIP_LABEL_U2 "LABEL_U2"

ctsvc_view_s _view_sip;
bool _view_sip_load = false;

static void _ctsvc_tc_load_view_sip()
{
	_view_sip_load = true;
	// _contacts_sip
	ctsvc_property_s sip_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_sip.address, CTSVC_SIP_ADDRESS_C1),
		ctsvc_tc_util_create_int_property(_contacts_sip.type, CTSVC_SIP_TYPE_C1),
	};
	ctsvc_property_s sip_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_sip.address, CTSVC_SIP_ADDRESS_U1),
		ctsvc_tc_util_create_int_property(_contacts_sip.type, CTSVC_SIP_TYPE_U1),
		ctsvc_tc_util_create_str_property(_contacts_sip.label, CTSVC_SIP_LABEL_U1),
	};
	ctsvc_property_s sip_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_sip.address, CTSVC_SIP_ADDRESS_C2),
		ctsvc_tc_util_create_int_property(_contacts_sip.type, CTSVC_SIP_TYPE_C2),
	};
	ctsvc_property_s sip_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_sip.address, CTSVC_SIP_ADDRESS_U2),
		ctsvc_tc_util_create_int_property(_contacts_sip.type, CTSVC_SIP_TYPE_U2),
		ctsvc_tc_util_create_str_property(_contacts_sip.label, CTSVC_SIP_LABEL_U2),
	};

	_view_sip.create1_count = sizeof(sip_create1)/sizeof(ctsvc_property_s);
	_view_sip.create2_count = sizeof(sip_create2)/sizeof(ctsvc_property_s);
	_view_sip.update1_count = sizeof(sip_update1)/sizeof(ctsvc_property_s);
	_view_sip.update2_count = sizeof(sip_update2)/sizeof(ctsvc_property_s);

	_view_sip.create1 = calloc(_view_sip.create1_count, sizeof(ctsvc_property_s));
	_view_sip.create2 = calloc(_view_sip.create2_count, sizeof(ctsvc_property_s));
	_view_sip.update1 = calloc(_view_sip.update1_count, sizeof(ctsvc_property_s));
	_view_sip.update2 = calloc(_view_sip.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_sip.create1_count;i++)
		_view_sip.create1[i] = sip_create1[i];
	for (i=0;i<_view_sip.create2_count;i++)
		_view_sip.create2[i] = sip_create2[i];
	for (i=0;i<_view_sip.update1_count;i++)
		_view_sip.update1[i] = sip_update1[i];
	for (i=0;i<_view_sip.update2_count;i++)
		_view_sip.update2[i] = sip_update2[i];
}

static int _ctsvc_tc_record_free_property_sip()
{
	if (false == _view_sip_load)
		return -1;

	_view_sip_load = false;

	free(_view_sip.create1);
	free(_view_sip.create2);
	free(_view_sip.update1);
	free(_view_sip.update2);

	return 0;
}

int ctsvc_tc_record_get_property_sip(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_sip_load)
		_ctsvc_tc_load_view_sip();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_sip.create1;
		*p_property_count = _view_sip.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_sip.create2;
		*p_property_count = _view_sip.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_sip.update1;
		*p_property_count = _view_sip.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_sip.update2;
		*p_property_count = _view_sip.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_sip(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_sip(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_sip(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_sip(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_sip(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_sip(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_sip(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sip._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_sip.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_sip(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_sip(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_sip(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_sip(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_sip(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sip._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_sip(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sip._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_sip(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sip._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_sip._uri)) {
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

static int _ctsvc_tc_record_compare_type_sip(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_sip(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_sip(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_sip(void)
{
	return _ctsvc_tc_record_compare_type_sip(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_sip = {
	.clone = _ctsvc_tc_record_clone_sip,
	.create = _ctsvc_tc_record_create_sip,
	.destroy = _ctsvc_tc_record_destroy_sip,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_sip,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_sip,
	.get_double = _ctsvc_tc_record_get_double_sip,
	.get_int = _ctsvc_tc_record_get_int_sip,
	.get_lli = _ctsvc_tc_record_get_lli_sip,
	.get_str = _ctsvc_tc_record_get_str_sip,
	.get_str_p = _ctsvc_tc_record_get_str_p_sip,
	.set_bool = _ctsvc_tc_record_set_bool_sip,
	.set_double = _ctsvc_tc_record_set_double_sip,
	.set_int = _ctsvc_tc_record_set_int_sip,
	.set_lli = _ctsvc_tc_record_set_lli_sip,
	.set_str = _ctsvc_tc_record_set_str_sip,
	.free_properties = _ctsvc_tc_record_free_property_sip,
};

static int _ctsvc_tc_filter_add_type_sip(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_sip._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_sip(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_sip(void)
{
	return _ctsvc_tc_filter_add_type_sip(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_sip(void)
{
	return _ctsvc_tc_filter_add_type_sip(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_sip(void)
{
	return _ctsvc_tc_filter_add_type_sip(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_sip(void)
{
	return _ctsvc_tc_filter_add_type_sip(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_sip(void)
{
	return _ctsvc_tc_filter_add_type_sip(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_sip = {
	.add_bool = _ctsvc_tc_filter_add_bool_sip,
	.add_double = _ctsvc_tc_filter_add_double_sip,
	.add_int = _ctsvc_tc_filter_add_int_sip,
	.add_lli = _ctsvc_tc_filter_add_lli_sip,
	.add_str = _ctsvc_tc_filter_add_str_sip,
};
