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
#include "utc-contacts-service-record-activity-photo.h"

// _contacts_activity_photo
#define CTSVC_ACTIVITY_PHOTO_PHOTO_URL_C1 CTSVC_IMAGE_PATH_C1
#define CTSVC_ACTIVITY_PHOTO_PHOTO_URL_U1 CTSVC_IMAGE_PATH_U1
#define CTSVC_ACTIVITY_PHOTO_SORT_INDEX_C1 1
#define CTSVC_ACTIVITY_PHOTO_SORT_INDEX_U1 2
#define CTSVC_ACTIVITY_PHOTO_PHOTO_URL_C2 CTSVC_IMAGE_PATH_C2
#define CTSVC_ACTIVITY_PHOTO_PHOTO_URL_U2 CTSVC_IMAGE_PATH_U2
#define CTSVC_ACTIVITY_PHOTO_SORT_INDEX_C2 2
#define CTSVC_ACTIVITY_PHOTO_SORT_INDEX_U2 2

ctsvc_view_s _view_activity_photo;
bool _view_activity_photo_load = false;

static void _ctsvc_tc_load_view_activity_photo()
{
	_view_activity_photo_load = true;
	// ctsvc_tc_util_create_str_property(_contacts_activity_photo
	ctsvc_property_s activity_photo_create1[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity_photo.photo_url, CTSVC_ACTIVITY_PHOTO_PHOTO_URL_C1),
		ctsvc_tc_util_create_int_property(_contacts_activity_photo.sort_index, CTSVC_ACTIVITY_PHOTO_SORT_INDEX_C1),
	};
	ctsvc_property_s activity_photo_update1[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity_photo.photo_url, CTSVC_ACTIVITY_PHOTO_PHOTO_URL_U1),
		ctsvc_tc_util_create_int_property(_contacts_activity_photo.sort_index, CTSVC_ACTIVITY_PHOTO_SORT_INDEX_U1),
	};
	ctsvc_property_s activity_photo_create2[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity_photo.photo_url, CTSVC_ACTIVITY_PHOTO_PHOTO_URL_C2),
		ctsvc_tc_util_create_int_property(_contacts_activity_photo.sort_index, CTSVC_ACTIVITY_PHOTO_SORT_INDEX_C2),
	};
	ctsvc_property_s activity_photo_update2[] = {
		ctsvc_tc_util_create_str_property(_contacts_activity_photo.photo_url, CTSVC_ACTIVITY_PHOTO_PHOTO_URL_U2),
		ctsvc_tc_util_create_int_property(_contacts_activity_photo.sort_index, CTSVC_ACTIVITY_PHOTO_SORT_INDEX_U2),
	};

	_view_activity_photo.create1_count = sizeof(activity_photo_create1)/sizeof(ctsvc_property_s);
	_view_activity_photo.create2_count = sizeof(activity_photo_create2)/sizeof(ctsvc_property_s);
	_view_activity_photo.update1_count = sizeof(activity_photo_update1)/sizeof(ctsvc_property_s);
	_view_activity_photo.update2_count = sizeof(activity_photo_update2)/sizeof(ctsvc_property_s);

	_view_activity_photo.create1 = calloc(_view_activity_photo.create1_count, sizeof(ctsvc_property_s));
	_view_activity_photo.create2 = calloc(_view_activity_photo.create2_count, sizeof(ctsvc_property_s));
	_view_activity_photo.update1 = calloc(_view_activity_photo.update1_count, sizeof(ctsvc_property_s));
	_view_activity_photo.update2 = calloc(_view_activity_photo.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_activity_photo.create1_count;i++)
		_view_activity_photo.create1[i] = activity_photo_create1[i];
	for (i=0;i<_view_activity_photo.create2_count;i++)
		_view_activity_photo.create2[i] = activity_photo_create2[i];
	for (i=0;i<_view_activity_photo.update1_count;i++)
		_view_activity_photo.update1[i] = activity_photo_update1[i];
	for (i=0;i<_view_activity_photo.update2_count;i++)
		_view_activity_photo.update2[i] = activity_photo_update2[i];
}

static int _ctsvc_tc_record_free_property_activity_photo()
{
	int i;

	if (false == _view_activity_photo_load)
		return -1;

	_view_activity_photo_load = false;

	for (i=0;i<_view_activity_photo.create1_count;i++) {
		if (_contacts_activity_photo.photo_url == _view_activity_photo.create1[i].property_id)
			free(_view_activity_photo.create1[i].val.str_val);
	}
	for (i=0;i<_view_activity_photo.create2_count;i++) {
		if (_contacts_activity_photo.photo_url == _view_activity_photo.create2[i].property_id)
			free(_view_activity_photo.create2[i].val.str_val);
	}
	for (i=0;i<_view_activity_photo.update1_count;i++) {
		if (_contacts_activity_photo.photo_url == _view_activity_photo.update1[i].property_id)
			free(_view_activity_photo.update1[i].val.str_val);
	}
	for (i=0;i<_view_activity_photo.update2_count;i++) {
		if (_contacts_activity_photo.photo_url == _view_activity_photo.update2[i].property_id)
			free(_view_activity_photo.update2[i].val.str_val);
	}

	free(_view_activity_photo.create1);
	free(_view_activity_photo.create2);
	free(_view_activity_photo.update1);
	free(_view_activity_photo.update2);

	return 0;
}

int ctsvc_tc_record_get_property_activity_photo(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_activity_photo_load)
		_ctsvc_tc_load_view_activity_photo();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_activity_photo.create1;
		*p_property_count = _view_activity_photo.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_activity_photo.create2;
		*p_property_count = _view_activity_photo.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_activity_photo.update1;
		*p_property_count = _view_activity_photo.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_activity_photo.update2;
		*p_property_count = _view_activity_photo.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_activity_photo(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_activity_photo(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_activity_photo(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_activity_photo(int activity_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity_photo._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_activity_photo.activity_id, activity_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_activity_photo(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_activity_photo(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_activity_photo(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_activity_photo(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity_photo._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_activity_photo(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity_photo._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_activity_photo(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_activity_photo._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_activity_photo._uri)) {
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

static int _ctsvc_tc_record_compare_type_activity_photo(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_activity_photo(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_activity_photo(void)
{
	return _ctsvc_tc_record_compare_type_activity_photo(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_activity_photo = {
	.clone = _ctsvc_tc_record_clone_activity_photo,
	.create = _ctsvc_tc_record_create_activity_photo,
	.destroy = _ctsvc_tc_record_destroy_activity_photo,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_activity_photo,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_activity_photo,
	.get_double = _ctsvc_tc_record_get_double_activity_photo,
	.get_int = _ctsvc_tc_record_get_int_activity_photo,
	.get_lli = _ctsvc_tc_record_get_lli_activity_photo,
	.get_str = _ctsvc_tc_record_get_str_activity_photo,
	.get_str_p = _ctsvc_tc_record_get_str_p_activity_photo,
	.set_bool = _ctsvc_tc_record_set_bool_activity_photo,
	.set_double = _ctsvc_tc_record_set_double_activity_photo,
	.set_int = _ctsvc_tc_record_set_int_activity_photo,
	.set_lli = _ctsvc_tc_record_set_lli_activity_photo,
	.set_str = _ctsvc_tc_record_set_str_activity_photo,
	.free_properties = _ctsvc_tc_record_free_property_activity_photo,
};

static int _ctsvc_tc_filter_add_type_activity_photo(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_activity_photo._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_activity_photo(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_activity_photo(void)
{
	return _ctsvc_tc_filter_add_type_activity_photo(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_activity_photo(void)
{
	return _ctsvc_tc_filter_add_type_activity_photo(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_activity_photo(void)
{
	return _ctsvc_tc_filter_add_type_activity_photo(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_activity_photo(void)
{
	return _ctsvc_tc_filter_add_type_activity_photo(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_activity_photo(void)
{
	return _ctsvc_tc_filter_add_type_activity_photo(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_activity_photo = {
	.add_bool = _ctsvc_tc_filter_add_bool_activity_photo,
	.add_double = _ctsvc_tc_filter_add_double_activity_photo,
	.add_int = _ctsvc_tc_filter_add_int_activity_photo,
	.add_lli = _ctsvc_tc_filter_add_lli_activity_photo,
	.add_str = _ctsvc_tc_filter_add_str_activity_photo,
};
