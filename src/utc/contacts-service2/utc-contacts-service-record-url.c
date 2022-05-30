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
#include "utc-contacts-service-record-url.h"

// _contacts_url
#define CTSVC_URL_TYPE_C1 CONTACTS_URL_TYPE_HOME
#define CTSVC_URL_TYPE_U1 CONTACTS_URL_TYPE_CUSTOM
#define CTSVC_URL_LABEL_U1 "LABEL_U"
#define CTSVC_URL_URL_C1 "http://URL_C"
#define CTSVC_URL_URL_U1 "http://URL_U"
#define CTSVC_URL_TYPE_C2 CONTACTS_URL_TYPE_HOME
#define CTSVC_URL_TYPE_U2 CONTACTS_URL_TYPE_CUSTOM
#define CTSVC_URL_LABEL_U2 "LABEL_U2"
#define CTSVC_URL_URL_C2 "http://URL_C2"
#define CTSVC_URL_URL_U2 "http://URL_U2"

ctsvc_view_s _view_url;
bool _view_url_load = false;

static void _ctsvc_tc_load_view_url()
{
	_view_url_load = true;
	// _contacts_url
	ctsvc_property_s url_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_url.type,	CTSVC_URL_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_url.url, CTSVC_URL_URL_C1),
	};
	ctsvc_property_s url_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_url.type,	CTSVC_URL_TYPE_U1),
		ctsvc_tc_util_create_str_property(_contacts_url.label, CTSVC_URL_LABEL_U1),
		ctsvc_tc_util_create_str_property(_contacts_url.url, CTSVC_URL_URL_U1),
	};

	ctsvc_property_s url_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_url.type,	CTSVC_URL_TYPE_C2),
		ctsvc_tc_util_create_str_property(_contacts_url.url, CTSVC_URL_URL_C2),
	};
	ctsvc_property_s url_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_url.type,	CTSVC_URL_TYPE_U2),
		ctsvc_tc_util_create_str_property(_contacts_url.label, CTSVC_URL_LABEL_U2),
		ctsvc_tc_util_create_str_property(_contacts_url.url, CTSVC_URL_URL_U2),
	};


	_view_url.create1_count = sizeof(url_create1)/sizeof(ctsvc_property_s);
	_view_url.create2_count = sizeof(url_create2)/sizeof(ctsvc_property_s);
	_view_url.update1_count = sizeof(url_update1)/sizeof(ctsvc_property_s);
	_view_url.update2_count = sizeof(url_update2)/sizeof(ctsvc_property_s);

	_view_url.create1 = calloc(_view_url.create1_count, sizeof(ctsvc_property_s));
	_view_url.create2 = calloc(_view_url.create2_count, sizeof(ctsvc_property_s));
	_view_url.update1 = calloc(_view_url.update1_count, sizeof(ctsvc_property_s));
	_view_url.update2 = calloc(_view_url.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_url.create1_count;i++)
		_view_url.create1[i] = url_create1[i];
	for (i=0;i<_view_url.create2_count;i++)
		_view_url.create2[i] = url_create2[i];
	for (i=0;i<_view_url.update1_count;i++)
		_view_url.update1[i] = url_update1[i];
	for (i=0;i<_view_url.update2_count;i++)
		_view_url.update2[i] = url_update2[i];
}

static int  _ctsvc_tc_record_free_property_url()
{
	if (false == _view_url_load)
		return -1;

	_view_url_load = false;

	free(_view_url.create1);
	free(_view_url.create2);
	free(_view_url.update1);
	free(_view_url.update2);

	return 0;
}

int ctsvc_tc_record_get_property_url(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_url_load)
		_ctsvc_tc_load_view_url();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_url.create1;
		*p_property_count = _view_url.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_url.create2;
		*p_property_count = _view_url.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_url.update1;
		*p_property_count = _view_url.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_url.update2;
		*p_property_count = _view_url.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_url(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_url(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_url(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_url(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_url(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_url(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_url(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_url._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_url.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_url(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}


static int _ctsvc_tc_record_clone_url(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_url(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_url(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_url(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_url._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_url(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_url._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_url(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_url._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_url._uri)) {
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

static int _ctsvc_tc_record_compare_type_url(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_url(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_url(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_url(void)
{
	return _ctsvc_tc_record_compare_type_url(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_url = {
	.clone = _ctsvc_tc_record_clone_url,
	.create = _ctsvc_tc_record_create_url,
	.destroy = _ctsvc_tc_record_destroy_url,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_url,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_url,
	.get_double = _ctsvc_tc_record_get_double_url,
	.get_int = _ctsvc_tc_record_get_int_url,
	.get_lli = _ctsvc_tc_record_get_lli_url,
	.get_str = _ctsvc_tc_record_get_str_url,
	.get_str_p = _ctsvc_tc_record_get_str_p_url,
	.set_bool = _ctsvc_tc_record_set_bool_url,
	.set_double = _ctsvc_tc_record_set_double_url,
	.set_int = _ctsvc_tc_record_set_int_url,
	.set_lli = _ctsvc_tc_record_set_lli_url,
	.set_str = _ctsvc_tc_record_set_str_url,
	.free_properties = _ctsvc_tc_record_free_property_url,
};


static int _ctsvc_tc_filter_add_type_url(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_url._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_url(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_url(void)
{
	return _ctsvc_tc_filter_add_type_url(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_url(void)
{
	return _ctsvc_tc_filter_add_type_url(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_url(void)
{
	return _ctsvc_tc_filter_add_type_url(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_url(void)
{
	return _ctsvc_tc_filter_add_type_url(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_url(void)
{
	return _ctsvc_tc_filter_add_type_url(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_url = {
	.add_bool = _ctsvc_tc_filter_add_bool_url,
	.add_double = _ctsvc_tc_filter_add_double_url,
	.add_int = _ctsvc_tc_filter_add_int_url,
	.add_lli = _ctsvc_tc_filter_add_lli_url,
	.add_str = _ctsvc_tc_filter_add_str_url,
};
