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
#include "utc-contacts-service-record-profile.h"

// _contacts_profile
#define CTSVC_PROFILE_UID_C1 "UID_C"
#define CTSVC_PROFILE_UID_U1 "UID_U"
#define CTSVC_PROFILE_TEXT_C1 "TEXT_C"
#define CTSVC_PROFILE_TEXT_U1 "TEXT_U"
#define CTSVC_PROFILE_ORDER_C1 1
#define CTSVC_PROFILE_ORDER_U1 2
#define CTSVC_PROFILE_SERVICE_OPERATION_C1 "SERVICE_OPERATION_C"
#define CTSVC_PROFILE_SERVICE_OPERATION_U1 "SERVICE_OPERATION_U"
#define CTSVC_PROFILE_MIME_C1 "MIME_C"
#define CTSVC_PROFILE_MIME_U1 "MIME_U"
#define CTSVC_PROFILE_APP_ID_C1 "APP_ID_C"
#define CTSVC_PROFILE_APP_ID_U1 "APP_ID_U"
#define CTSVC_PROFILE_URI_C1 "URI_C"
#define CTSVC_PROFILE_URI_U1 "URI_U"
#define CTSVC_PROFILE_CATEGORY_C1 "CATEGORY_C"
#define CTSVC_PROFILE_CATEGORY_U1 "CATEGORY_U"
#define CTSVC_PROFILE_EXTRA_DATA_C1 "EXTRA_DATA_C"
#define CTSVC_PROFILE_EXTRA_DATA_U1 "EXTRA_DATA_U"
#define CTSVC_PROFILE_UID_C2 "UID_C2"
#define CTSVC_PROFILE_UID_U2 "UID_U2"
#define CTSVC_PROFILE_TEXT_C2 "TEXT_C2"
#define CTSVC_PROFILE_TEXT_U2 "TEXT_U2"
#define CTSVC_PROFILE_ORDER_C2 2
#define CTSVC_PROFILE_ORDER_U2 2
#define CTSVC_PROFILE_SERVICE_OPERATION_C2 "SERVICE_OPERATION_C2"
#define CTSVC_PROFILE_SERVICE_OPERATION_U2 "SERVICE_OPERATION_U2"
#define CTSVC_PROFILE_MIME_C2 "MIME_C2"
#define CTSVC_PROFILE_MIME_U2 "MIME_U2"
#define CTSVC_PROFILE_APP_ID_C2 "APP_ID_C2"
#define CTSVC_PROFILE_APP_ID_U2 "APP_ID_U2"
#define CTSVC_PROFILE_URI_C2 "URI_C2"
#define CTSVC_PROFILE_URI_U2 "URI_U2"
#define CTSVC_PROFILE_CATEGORY_C2 "CATEGORY_C2"
#define CTSVC_PROFILE_CATEGORY_U2 "CATEGORY_U2"
#define CTSVC_PROFILE_EXTRA_DATA_C2 "EXTRA_DATA_C2"
#define CTSVC_PROFILE_EXTRA_DATA_U2 "EXTRA_DATA_U2"

ctsvc_view_s _view_profile;
bool _view_profile_load = false;

static void _ctsvc_tc_load_view_profile()
{
	_view_profile_load = true;
	// _contacts_profile
	ctsvc_property_s profile_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_profile.uid, CTSVC_PROFILE_UID_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.text, CTSVC_PROFILE_TEXT_C1),
		ctsvc_tc_util_create_int_property(_contacts_profile.order, CTSVC_PROFILE_ORDER_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.service_operation, CTSVC_PROFILE_SERVICE_OPERATION_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.mime, CTSVC_PROFILE_MIME_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.app_id, CTSVC_PROFILE_APP_ID_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.uri, CTSVC_PROFILE_URI_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.category, CTSVC_PROFILE_CATEGORY_C1),
		ctsvc_tc_util_create_str_property(_contacts_profile.extra_data, CTSVC_PROFILE_EXTRA_DATA_C1),
	};
	ctsvc_property_s profile_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_profile.uid, CTSVC_PROFILE_UID_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.text, CTSVC_PROFILE_TEXT_U1),
		ctsvc_tc_util_create_int_property(_contacts_profile.order, CTSVC_PROFILE_ORDER_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.service_operation, CTSVC_PROFILE_SERVICE_OPERATION_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.mime, CTSVC_PROFILE_MIME_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.app_id, CTSVC_PROFILE_APP_ID_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.uri, CTSVC_PROFILE_URI_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.category, CTSVC_PROFILE_CATEGORY_U1),
		ctsvc_tc_util_create_str_property(_contacts_profile.extra_data, CTSVC_PROFILE_EXTRA_DATA_U1),
	};
	ctsvc_property_s profile_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_profile.uid, CTSVC_PROFILE_UID_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.text, CTSVC_PROFILE_TEXT_C2),
		ctsvc_tc_util_create_int_property(_contacts_profile.order, CTSVC_PROFILE_ORDER_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.service_operation, CTSVC_PROFILE_SERVICE_OPERATION_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.mime, CTSVC_PROFILE_MIME_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.app_id, CTSVC_PROFILE_APP_ID_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.uri, CTSVC_PROFILE_URI_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.category, CTSVC_PROFILE_CATEGORY_C2),
		ctsvc_tc_util_create_str_property(_contacts_profile.extra_data, CTSVC_PROFILE_EXTRA_DATA_C2),
	};
	ctsvc_property_s profile_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_profile.uid, CTSVC_PROFILE_UID_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.text, CTSVC_PROFILE_TEXT_U2),
		ctsvc_tc_util_create_int_property(_contacts_profile.order, CTSVC_PROFILE_ORDER_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.service_operation, CTSVC_PROFILE_SERVICE_OPERATION_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.mime, CTSVC_PROFILE_MIME_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.app_id, CTSVC_PROFILE_APP_ID_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.uri, CTSVC_PROFILE_URI_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.category, CTSVC_PROFILE_CATEGORY_U2),
		ctsvc_tc_util_create_str_property(_contacts_profile.extra_data, CTSVC_PROFILE_EXTRA_DATA_U2),
	};


	_view_profile.create1_count = sizeof(profile_create1)/sizeof(ctsvc_property_s);
	_view_profile.create2_count = sizeof(profile_create2)/sizeof(ctsvc_property_s);
	_view_profile.update1_count = sizeof(profile_update1)/sizeof(ctsvc_property_s);
	_view_profile.update2_count = sizeof(profile_update2)/sizeof(ctsvc_property_s);

	_view_profile.create1 = calloc(_view_profile.create1_count, sizeof(ctsvc_property_s));
	_view_profile.create2 = calloc(_view_profile.create2_count, sizeof(ctsvc_property_s));
	_view_profile.update1 = calloc(_view_profile.update1_count, sizeof(ctsvc_property_s));
	_view_profile.update2 = calloc(_view_profile.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_profile.create1_count;i++)
		_view_profile.create1[i] = profile_create1[i];
	for (i=0;i<_view_profile.create2_count;i++)
		_view_profile.create2[i] = profile_create2[i];
	for (i=0;i<_view_profile.update1_count;i++)
		_view_profile.update1[i] = profile_update1[i];
	for (i=0;i<_view_profile.update2_count;i++)
		_view_profile.update2[i] = profile_update2[i];
}

static int _ctsvc_tc_record_free_property_profile()
{
	if (false == _view_profile_load)
		return -1;

	_view_profile_load = false;

	free(_view_profile.create1);
	free(_view_profile.create2);
	free(_view_profile.update1);
	free(_view_profile.update2);

	return 0;
}

int ctsvc_tc_record_get_property_profile(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_profile_load)
		_ctsvc_tc_load_view_profile();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_profile.create1;
		*p_property_count = _view_profile.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_profile.create2;
		*p_property_count = _view_profile.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_profile.update1;
		*p_property_count = _view_profile.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_profile.update2;
		*p_property_count = _view_profile.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_profile(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_profile(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_profile(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_profile(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_profile(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_profile(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_profile(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_profile.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_profile(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_profile(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_profile(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_profile(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_profile(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_profile._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_profile._uri)) {
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

static int _ctsvc_tc_record_compare_type_profile(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_profile(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_profile(void)
{
	return _ctsvc_tc_record_compare_type_profile(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_profile = {
	.clone = _ctsvc_tc_record_clone_profile,
	.create = _ctsvc_tc_record_create_profile,
	.destroy = _ctsvc_tc_record_destroy_profile,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_profile,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_profile,
	.get_double = _ctsvc_tc_record_get_double_profile,
	.get_int = _ctsvc_tc_record_get_int_profile,
	.get_lli = _ctsvc_tc_record_get_lli_profile,
	.get_str = _ctsvc_tc_record_get_str_profile,
	.get_str_p = _ctsvc_tc_record_get_str_p_profile,
	.set_bool = _ctsvc_tc_record_set_bool_profile,
	.set_double = _ctsvc_tc_record_set_double_profile,
	.set_int = _ctsvc_tc_record_set_int_profile,
	.set_lli = _ctsvc_tc_record_set_lli_profile,
	.set_str = _ctsvc_tc_record_set_str_profile,
	.free_properties = _ctsvc_tc_record_free_property_profile,
};


static int _ctsvc_tc_filter_add_type_profile(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_profile._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_profile(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_profile(void)
{
	return _ctsvc_tc_filter_add_type_profile(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_profile(void)
{
	return _ctsvc_tc_filter_add_type_profile(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_profile(void)
{
	return _ctsvc_tc_filter_add_type_profile(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_profile(void)
{
	return _ctsvc_tc_filter_add_type_profile(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_profile(void)
{
	return _ctsvc_tc_filter_add_type_profile(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_profile = {
	.add_bool = _ctsvc_tc_filter_add_bool_profile,
	.add_double = _ctsvc_tc_filter_add_double_profile,
	.add_int = _ctsvc_tc_filter_add_int_profile,
	.add_lli = _ctsvc_tc_filter_add_lli_profile,
	.add_str = _ctsvc_tc_filter_add_str_profile,
};
