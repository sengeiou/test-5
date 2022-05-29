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

// _contacts_contact_updated_info
#define CTSVC_CONTACT_UPDATED_TYPE_C1 CONTACTS_CHANGE_INSERTED
#define CTSVC_CONTACT_UPDATED_IMAGE_CHANGED_C1 true
#define CTSVC_CONTACT_UPDATED_TYPE_C2 CONTACTS_CHANGE_INSERTED
#define CTSVC_CONTACT_UPDATED_IMAGE_CHANGED_C2 true

ctsvc_view_s _view_contact_updated_info;
bool _view_contact_updated_info_load = false;

static void _ctsvc_tc_load_view_contact_updated_info()
{
	_view_contact_updated_info_load = true;
	// _contacts_contact_updated_info
	ctsvc_property_s contact_updated_info_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_contact_updated_info.type , CTSVC_CONTACT_UPDATED_TYPE_C1),
		ctsvc_tc_util_create_bool_property(_contacts_contact_updated_info.image_changed  , CTSVC_CONTACT_UPDATED_IMAGE_CHANGED_C1),
	};
	ctsvc_property_s contact_updated_info_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_contact_updated_info.type , CTSVC_CONTACT_UPDATED_TYPE_C2),
		ctsvc_tc_util_create_bool_property(_contacts_contact_updated_info.image_changed  , CTSVC_CONTACT_UPDATED_IMAGE_CHANGED_C2),
	};


	_view_contact_updated_info.create1_count = sizeof(contact_updated_info_create1)/sizeof(ctsvc_property_s);
	_view_contact_updated_info.create2_count = sizeof(contact_updated_info_create2)/sizeof(ctsvc_property_s);

	_view_contact_updated_info.create1 = calloc(_view_contact_updated_info.create1_count, sizeof(ctsvc_property_s));
	_view_contact_updated_info.create2 = calloc(_view_contact_updated_info.create2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_contact_updated_info.create1_count;i++)
		_view_contact_updated_info.create1[i] = contact_updated_info_create1[i];
	for (i=0;i<_view_contact_updated_info.create2_count;i++)
		_view_contact_updated_info.create2[i] = contact_updated_info_create2[i];
}

static int _ctsvc_tc_record_free_property_contact_updated_info()
{
	if (false == _view_contact_updated_info_load)
		return -1;

	_view_contact_updated_info_load = false;

	free(_view_contact_updated_info.create1);
	free(_view_contact_updated_info.create2);

	return 0;
}

int ctsvc_tc_record_get_property_contact_updated_info(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_contact_updated_info_load)
		_ctsvc_tc_load_view_contact_updated_info();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_contact_updated_info.create1;
		*p_property_count = _view_contact_updated_info.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_contact_updated_info.create2;
		*p_property_count = _view_contact_updated_info.create2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_create_contact_updated_info(ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact_updated_info._uri, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_contact_updated_info(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}



static int _ctsvc_tc_record_clone_contact_updated_info(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_contact_updated_info(PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_contact_updated_info(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_contact_updated_info(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact_updated_info._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_contact_updated_info(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact_updated_info._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_contact_updated_info(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_contact_updated_info._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_contact_updated_info._uri)) {
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

static int _ctsvc_tc_record_compare_type_contact_updated_info(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_contact_updated_info(PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_contact_updated_info(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_contact_updated_info(void)
{
	return _ctsvc_tc_record_compare_type_contact_updated_info(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_int_contact_updated_info(void)
{
	return _ctsvc_tc_record_compare_type_contact_updated_info(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_bool_contact_updated_info(void)
{
	return _ctsvc_tc_record_compare_type_contact_updated_info(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_int_contact_updated_info(void)
{
	return _ctsvc_tc_record_compare_type_contact_updated_info(PROPERTY_INT);
}


ctsvc_tc_record_plugin_s _tc_record_contact_updated_info = {
	.clone = _ctsvc_tc_record_clone_contact_updated_info,
	.create = _ctsvc_tc_record_create_contact_updated_info,
	.destroy = _ctsvc_tc_record_destroy_contact_updated_info,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_contact_updated_info,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_contact_updated_info,
	.get_double = NULL,
	.get_int = _ctsvc_tc_record_get_int_contact_updated_info,
	.get_lli = NULL,
	.get_str = NULL,
	.get_str_p = NULL,
	.set_bool = _ctsvc_tc_record_set_bool_contact_updated_info,
	.set_double = NULL,
	.set_int = _ctsvc_tc_record_set_int_contact_updated_info,
	.set_lli = NULL,
	.set_str = NULL,
	.free_properties = _ctsvc_tc_record_free_property_contact_updated_info,
};
