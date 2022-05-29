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
#include <stdbool.h>

#include "utc-contacts-service-tc-utils.h"

// _contacts_phone_log_stat

ctsvc_view_s _view_phone_log_stat;
bool _view_phone_log_stat_load = false;

static void _ctsvc_tc_load_view_phone_log_stat()
{
	_view_phone_log_stat_load = true;
	// _contacts_phone_log_stat
	ctsvc_property_s contact_phone_log_stat_create1[] = {
	};
	ctsvc_property_s contact_phone_log_stat_create2[] = {
	};


	_view_phone_log_stat.create1_count = sizeof(contact_phone_log_stat_create1)/sizeof(ctsvc_property_s);
	_view_phone_log_stat.create2_count = sizeof(contact_phone_log_stat_create2)/sizeof(ctsvc_property_s);

	_view_phone_log_stat.create1 = calloc(_view_phone_log_stat.create1_count, sizeof(ctsvc_property_s));
	_view_phone_log_stat.create2 = calloc(_view_phone_log_stat.create2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_phone_log_stat.create1_count;i++)
		_view_phone_log_stat.create1[i] = contact_phone_log_stat_create1[i];
	for (i=0;i<_view_phone_log_stat.create2_count;i++)
		_view_phone_log_stat.create2[i] = contact_phone_log_stat_create2[i];
}

static int _ctsvc_tc_record_free_property_phone_log_stat()
{
	if (false == _view_phone_log_stat_load)
		return -1;

	_view_phone_log_stat_load = false;

	free(_view_phone_log_stat.create1);
	free(_view_phone_log_stat.create2);

	return 0;
}

int ctsvc_tc_record_get_property_phone_log_stat(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_phone_log_stat_load)
		_ctsvc_tc_load_view_phone_log_stat();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_phone_log_stat.create1;
		*p_property_count = _view_phone_log_stat.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_phone_log_stat.create2;
		*p_property_count = _view_phone_log_stat.create2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_create_phone_log_stat(ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log_stat._uri, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_phone_log_stat(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}



static int _ctsvc_tc_record_clone_phone_log_stat(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_phone_log_stat(PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_phone_log_stat(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_phone_log_stat(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log_stat._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_phone_log_stat(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log_stat._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_phone_log_stat(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_phone_log_stat._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_phone_log_stat._uri)) {
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

ctsvc_tc_record_plugin_s _tc_record_phone_log_stat = {
	.clone = _ctsvc_tc_record_clone_phone_log_stat,
	.create = _ctsvc_tc_record_create_phone_log_stat,
	.destroy = _ctsvc_tc_record_destroy_phone_log_stat,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_phone_log_stat,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = NULL,
	.get_double = NULL,
	.get_int = NULL,
	.get_lli = NULL,
	.get_str = NULL,
	.get_str_p = NULL,
	.set_bool = NULL,
	.set_double = NULL,
	.set_int = NULL,
	.set_lli = NULL,
	.set_str = NULL,
	.free_properties = _ctsvc_tc_record_free_property_phone_log_stat,
};
