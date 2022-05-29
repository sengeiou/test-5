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
#include "utc-contacts-service-record-phone-log.h"

// _contacts_phone_log
#define CTSVC_PHONE_LOG_LOG_TYPE_C1 CONTACTS_PLOG_TYPE_VOICE_INCOMING_UNSEEN
#define CTSVC_PHONE_LOG_LOG_TYPE_U1 CONTACTS_PLOG_TYPE_VOICE_INCOMING_SEEN
#define CTSVC_PHONE_LOG_LOG_TYPE_C2 CONTACTS_PLOG_TYPE_VOICE_INCOMING_UNSEEN
#define CTSVC_PHONE_LOG_LOG_TYPE_U2 CONTACTS_PLOG_TYPE_VOICE_INCOMING_SEEN

ctsvc_view_s _view_phone_log;
bool _view_phone_log_load = false;

static void _ctsvc_tc_load_view_phone_log()
{
	_view_phone_log_load = true;
	// _contacts_phone_log
	ctsvc_property_s phone_log_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_phone_log.log_type, CTSVC_PHONE_LOG_LOG_TYPE_C1),
	};
	ctsvc_property_s phone_log_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_phone_log.log_type, CTSVC_PHONE_LOG_LOG_TYPE_U1),
	};
	ctsvc_property_s phone_log_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_phone_log.log_type, CTSVC_PHONE_LOG_LOG_TYPE_C2),
	};
	ctsvc_property_s phone_log_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_phone_log.log_type, CTSVC_PHONE_LOG_LOG_TYPE_U2),
	};



	_view_phone_log.create1_count = sizeof(phone_log_create1)/sizeof(ctsvc_property_s);
	_view_phone_log.create2_count = sizeof(phone_log_create2)/sizeof(ctsvc_property_s);
	_view_phone_log.update1_count = sizeof(phone_log_update1)/sizeof(ctsvc_property_s);
	_view_phone_log.update2_count = sizeof(phone_log_update2)/sizeof(ctsvc_property_s);

	_view_phone_log.create1 = calloc(_view_phone_log.create1_count, sizeof(ctsvc_property_s));
	_view_phone_log.create2 = calloc(_view_phone_log.create2_count, sizeof(ctsvc_property_s));
	_view_phone_log.update1 = calloc(_view_phone_log.update1_count, sizeof(ctsvc_property_s));
	_view_phone_log.update2 = calloc(_view_phone_log.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_phone_log.create1_count;i++)
		_view_phone_log.create1[i] = phone_log_create1[i];
	for (i=0;i<_view_phone_log.create2_count;i++)
		_view_phone_log.create2[i] = phone_log_create2[i];
	for (i=0;i<_view_phone_log.update1_count;i++)
		_view_phone_log.update1[i] = phone_log_update1[i];
	for (i=0;i<_view_phone_log.update2_count;i++)
		_view_phone_log.update2[i] = phone_log_update2[i];
}

static int _ctsvc_tc_record_free_property_phone_log()
{
	if (false == _view_phone_log_load)
		return -1;

	_view_phone_log_load = false;

	free(_view_phone_log.create1);
	free(_view_phone_log.create2);
	free(_view_phone_log.update1);
	free(_view_phone_log.update2);

	return 0;
}


int ctsvc_tc_record_get_property_phone_log(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_phone_log_load)
		_ctsvc_tc_load_view_phone_log();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_phone_log.create1;
		*p_property_count = _view_phone_log.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_phone_log.create2;
		*p_property_count = _view_phone_log.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_phone_log.update1;
		*p_property_count = _view_phone_log.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_phone_log.update2;
		*p_property_count = _view_phone_log.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_phone_log(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_phone_log(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_phone_log(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_phone_log(ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log._uri, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}



static int _ctsvc_tc_record_clone_phone_log(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_phone_log(PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_phone_log(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_phone_log(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_phone_log(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_phone_log(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_phone_log._uri)) {
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

static int _ctsvc_tc_record_compare_type_phone_log(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_phone_log(PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_phone_log(void)
{
	return _ctsvc_tc_record_compare_type_phone_log(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_phone_log = {
	.clone = _ctsvc_tc_record_clone_phone_log,
	.create = _ctsvc_tc_record_create_phone_log,
	.destroy = _ctsvc_tc_record_destroy_phone_log,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_phone_log,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_phone_log,
	.get_double = _ctsvc_tc_record_get_double_phone_log,
	.get_int = _ctsvc_tc_record_get_int_phone_log,
	.get_lli = _ctsvc_tc_record_get_lli_phone_log,
	.get_str = _ctsvc_tc_record_get_str_phone_log,
	.get_str_p = _ctsvc_tc_record_get_str_p_phone_log,
	.set_bool = _ctsvc_tc_record_set_bool_phone_log,
	.set_double = _ctsvc_tc_record_set_double_phone_log,
	.set_int = _ctsvc_tc_record_set_int_phone_log,
	.set_lli = _ctsvc_tc_record_set_lli_phone_log,
	.set_str = _ctsvc_tc_record_set_str_phone_log,
	.free_properties = _ctsvc_tc_record_free_property_phone_log,
};

static int _ctsvc_tc_filter_add_type_phone_log(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_phone_log._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_phone_log(void)
{
	return _ctsvc_tc_filter_add_type_phone_log(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_phone_log(void)
{
	return _ctsvc_tc_filter_add_type_phone_log(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_phone_log(void)
{
	return _ctsvc_tc_filter_add_type_phone_log(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_phone_log(void)
{
	return _ctsvc_tc_filter_add_type_phone_log(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_phone_log(void)
{
	return _ctsvc_tc_filter_add_type_phone_log(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_phone_log = {
	.add_bool = _ctsvc_tc_filter_add_bool_phone_log,
	.add_double = _ctsvc_tc_filter_add_double_phone_log,
	.add_int = _ctsvc_tc_filter_add_int_phone_log,
	.add_lli = _ctsvc_tc_filter_add_lli_phone_log,
	.add_str = _ctsvc_tc_filter_add_str_phone_log,
};
