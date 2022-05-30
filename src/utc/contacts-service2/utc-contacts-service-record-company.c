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
#include "utc-contacts-service-record-company.h"

// _contacts_company
#define CTSVC_COMPANY_TYPE_C1 CONTACTS_COMPANY_TYPE_OTHER
#define CTSVC_COMPANY_TYPE_U1 CONTACTS_COMPANY_TYPE_CUSTOM
#define CTSVC_COMPANY_LABEL_U1 "LABEL_U"
#define CTSVC_COMPANY_NAME_C1 "NAME_C"
#define CTSVC_COMPANY_NAME_U1 "NAME_U"
#define CTSVC_COMPANY_DEPARTMENT_C1 "DEPARTMENT_C"
#define CTSVC_COMPANY_DEPARTMENT_U1 "DEPARTMENT_U"
#define CTSVC_COMPANY_JOB_TITLE_C1 "JOB_TITLE_C"
#define CTSVC_COMPANY_JOB_TITLE_U1 "JOB_TITLE_U"
#define CTSVC_COMPANY_ASSISTANT_NAME_C1 "ASSISTANT_NAME_C"
#define CTSVC_COMPANY_ASSISTANT_NAME_U1 "ASSISTANT_NAME_U"
#define CTSVC_COMPANY_ROLE_C1 "ROLE_C"
#define CTSVC_COMPANY_ROLE_U1 "ROLE_U"
#define CTSVC_COMPANY_LOGO_C1 CTSVC_IMAGE_PATH_C1
#define CTSVC_COMPANY_LOGO_U1 CTSVC_IMAGE_PATH_U1
#define CTSVC_COMPANY_LOCATION_C1 "LOCATION_C"
#define CTSVC_COMPANY_LOCATION_U1 "LOCATION_U"
#define CTSVC_COMPANY_DESCRIPTION_C1 "DESCRIPTION_C"
#define CTSVC_COMPANY_DESCRIPTION_U1 "DESCRIPTION_U"
#define CTSVC_COMPANY_PHONETIC_NAME_C1 "PHONETIC_NAME_C"
#define CTSVC_COMPANY_PHONETIC_NAME_U1 "PHONETIC_NAME_U"
#define CTSVC_COMPANY_TYPE_C2 CONTACTS_COMPANY_TYPE_OTHER
#define CTSVC_COMPANY_TYPE_U2 CONTACTS_COMPANY_TYPE_CUSTOM
#define CTSVC_COMPANY_LABEL_U2 "LABEL_U2"
#define CTSVC_COMPANY_NAME_C2 "NAME_C2"
#define CTSVC_COMPANY_NAME_U2 "NAME_U2"
#define CTSVC_COMPANY_DEPARTMENT_C2 "DEPARTMENT_C2"
#define CTSVC_COMPANY_DEPARTMENT_U2 "DEPARTMENT_U2"
#define CTSVC_COMPANY_JOB_TITLE_C2 "JOB_TITLE_C2"
#define CTSVC_COMPANY_JOB_TITLE_U2 "JOB_TITLE_U2"
#define CTSVC_COMPANY_ASSISTANT_NAME_C2 "ASSISTANT_NAME_C2"
#define CTSVC_COMPANY_ASSISTANT_NAME_U2 "ASSISTANT_NAME_U2"
#define CTSVC_COMPANY_ROLE_C2 "ROLE_C2"
#define CTSVC_COMPANY_ROLE_U2 "ROLE_U2"
#define CTSVC_COMPANY_LOGO_C2 CTSVC_IMAGE_PATH_C2
#define CTSVC_COMPANY_LOGO_U2 CTSVC_IMAGE_PATH_U2
#define CTSVC_COMPANY_LOCATION_C2 "LOCATION_C2"
#define CTSVC_COMPANY_LOCATION_U2 "LOCATION_U2"
#define CTSVC_COMPANY_DESCRIPTION_C2 "DESCRIPTION_C2"
#define CTSVC_COMPANY_DESCRIPTION_U2 "DESCRIPTION_U2"
#define CTSVC_COMPANY_PHONETIC_NAME_C2 "PHONETIC_NAME_C2"
#define CTSVC_COMPANY_PHONETIC_NAME_U2 "PHONETIC_NAME_U2"

ctsvc_view_s _view_company;
bool _view_company_load = false;

static void _ctsvc_tc_load_view_company()
{
	_view_company_load = true;
	// _contacts_company
	ctsvc_property_s company_create1[] = {
		ctsvc_tc_util_create_int_property(_contacts_company.type, CTSVC_COMPANY_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.name, CTSVC_COMPANY_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.department, CTSVC_COMPANY_DEPARTMENT_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.job_title, CTSVC_COMPANY_JOB_TITLE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.assistant_name, CTSVC_COMPANY_ASSISTANT_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.role, CTSVC_COMPANY_ROLE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.logo, CTSVC_COMPANY_LOGO_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.location, CTSVC_COMPANY_LOCATION_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.description, CTSVC_COMPANY_DESCRIPTION_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.phonetic_name, CTSVC_COMPANY_PHONETIC_NAME_C1),
	};
	ctsvc_property_s company_update1[] = {
		ctsvc_tc_util_create_int_property(_contacts_company.type, CTSVC_COMPANY_TYPE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.label, CTSVC_COMPANY_LABEL_U1),
		ctsvc_tc_util_create_str_property(_contacts_company.name, CTSVC_COMPANY_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.department, CTSVC_COMPANY_DEPARTMENT_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.job_title, CTSVC_COMPANY_JOB_TITLE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.assistant_name, CTSVC_COMPANY_ASSISTANT_NAME_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.role, CTSVC_COMPANY_ROLE_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.logo, CTSVC_COMPANY_LOGO_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.location, CTSVC_COMPANY_LOCATION_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.description, CTSVC_COMPANY_DESCRIPTION_C1),
		ctsvc_tc_util_create_str_property(_contacts_company.phonetic_name, CTSVC_COMPANY_PHONETIC_NAME_C1),
	};
	ctsvc_property_s company_create2[] = {
		ctsvc_tc_util_create_int_property(_contacts_company.type, CTSVC_COMPANY_TYPE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.name, CTSVC_COMPANY_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.department, CTSVC_COMPANY_DEPARTMENT_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.job_title, CTSVC_COMPANY_JOB_TITLE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.assistant_name, CTSVC_COMPANY_ASSISTANT_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.role, CTSVC_COMPANY_ROLE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.logo, CTSVC_COMPANY_LOGO_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.location, CTSVC_COMPANY_LOCATION_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.description, CTSVC_COMPANY_DESCRIPTION_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.phonetic_name, CTSVC_COMPANY_PHONETIC_NAME_C2),
	};
	ctsvc_property_s company_update2[] = {
		ctsvc_tc_util_create_int_property(_contacts_company.type, CTSVC_COMPANY_TYPE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.label, CTSVC_COMPANY_LABEL_U2),
		ctsvc_tc_util_create_str_property(_contacts_company.name, CTSVC_COMPANY_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.department, CTSVC_COMPANY_DEPARTMENT_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.job_title, CTSVC_COMPANY_JOB_TITLE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.assistant_name, CTSVC_COMPANY_ASSISTANT_NAME_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.role, CTSVC_COMPANY_ROLE_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.logo, CTSVC_COMPANY_LOGO_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.location, CTSVC_COMPANY_LOCATION_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.description, CTSVC_COMPANY_DESCRIPTION_C2),
		ctsvc_tc_util_create_str_property(_contacts_company.phonetic_name, CTSVC_COMPANY_PHONETIC_NAME_C2),
	};

	_view_company.create1_count = sizeof(company_create1)/sizeof(ctsvc_property_s);
	_view_company.create2_count = sizeof(company_create2)/sizeof(ctsvc_property_s);
	_view_company.update1_count = sizeof(company_update1)/sizeof(ctsvc_property_s);
	_view_company.update2_count = sizeof(company_update2)/sizeof(ctsvc_property_s);

	_view_company.create1 = calloc(_view_company.create1_count, sizeof(ctsvc_property_s));
	_view_company.create2 = calloc(_view_company.create2_count, sizeof(ctsvc_property_s));
	_view_company.update1 = calloc(_view_company.update1_count, sizeof(ctsvc_property_s));
	_view_company.update2 = calloc(_view_company.update2_count, sizeof(ctsvc_property_s));

	int i;
	for (i=0;i<_view_company.create1_count;i++)
		_view_company.create1[i] = company_create1[i];
	for (i=0;i<_view_company.create2_count;i++)
		_view_company.create2[i] = company_create2[i];
	for (i=0;i<_view_company.update1_count;i++)
		_view_company.update1[i] = company_update1[i];
	for (i=0;i<_view_company.update2_count;i++)
		_view_company.update2[i] = company_update2[i];
}

static int _ctsvc_tc_record_free_property_company()
{
	int i;

	if (false == _view_company_load)
		return -1;

	_view_company_load = false;

	for (i=0;i<_view_company.create1_count;i++) {
		if(_contacts_company.logo == _view_company.create1[i].property_id)
			free(_view_company.create1[i].val.str_val);
	}
	for (i=0;i<_view_company.create2_count;i++) {
		if(_contacts_company.logo == _view_company.create2[i].property_id)
			free(_view_company.create2[i].val.str_val);
	}
	for (i=0;i<_view_company.update1_count;i++) {
		if(_contacts_company.logo == _view_company.update1[i].property_id)
			free(_view_company.update1[i].val.str_val);
	}
	for (i=0;i<_view_company.update2_count;i++) {
		if(_contacts_company.logo == _view_company.update2[i].property_id)
			free(_view_company.update2[i].val.str_val);
	}

	free(_view_company.create1);
	free(_view_company.create2);
	free(_view_company.update1);
	free(_view_company.update2);

	return 0;
}

int ctsvc_tc_record_get_property_company(ctsvc_property_type_e type, ctsvc_property_s **p_properties, int *p_property_count)
{
	if (false == _view_company_load)
		_ctsvc_tc_load_view_company();

	switch (type) {
	case PROPERTY_TYPE_CREATE1:
		*p_properties = _view_company.create1;
		*p_property_count = _view_company.create1_count;
		break;
	case PROPERTY_TYPE_CREATE2:
		*p_properties = _view_company.create2;
		*p_property_count = _view_company.create2_count;
		break;
	case PROPERTY_TYPE_UPDATE1:
		*p_properties = _view_company.update1;
		*p_property_count = _view_company.update1_count;
		break;
	case PROPERTY_TYPE_UPDATE2:
		*p_properties = _view_company.update2;
		*p_property_count = _view_company.update2_count;
		break;
	default :
		break;
	}
	return 0;
}

int ctsvc_tc_record_compare_company(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_company(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare(record, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_filter_set_company(contacts_filter_h filter, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *properties = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_company(type, &properties, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_set(filter, properties, property_count))) break;
		return 0;
	} while (0);
	return ret;
}


int ctsvc_tc_record_update_company(contacts_record_h record, ctsvc_property_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	do {
		if (0 != (ret = ctsvc_tc_record_get_property_company(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		return 0;
	} while (0);
	return ret;
}

int ctsvc_tc_record_create_company(int contact_id, ctsvc_property_type_e type, contacts_record_h *p_record)
{
	int ret = 0;
	int property_count = 0;
	contacts_record_h record = NULL;
	ctsvc_property_s *property_list = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_company._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_set_int(record, _contacts_company.contact_id, contact_id))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_company(type, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_set_property(record, property_list, property_count))) break;
		*p_record = record;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_clone_company(void)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_create_company(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
		if (CONTACTS_ERROR_NONE != (ret = ctsvc_tc_record_get_property_company(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
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

static int _ctsvc_tc_record_create_company(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_company._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_company(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_company._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_company(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_company._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_company._uri)) {
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

static int _ctsvc_tc_record_compare_type_company(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_record_h record = NULL;

	do {
		if (0 != (ret = ctsvc_tc_record_create_company(0, PROPERTY_TYPE_CREATE1, &record))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_company(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_record_compare_type(record, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while (0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_bool_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_get_double_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_get_int_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_INT);
}

static int _ctsvc_tc_record_get_lli_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_LLI);
}

static int _ctsvc_tc_record_get_str_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_STR);
}

static int _ctsvc_tc_record_get_str_p_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_STR);
}

static int _ctsvc_tc_record_set_bool_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_BOOL);
}

static int _ctsvc_tc_record_set_double_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_record_set_int_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_INT);
}

static int _ctsvc_tc_record_set_lli_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_LLI);
}

static int _ctsvc_tc_record_set_str_company(void)
{
	return _ctsvc_tc_record_compare_type_company(PROPERTY_STR);
}


ctsvc_tc_record_plugin_s _tc_record_company = {
	.clone = _ctsvc_tc_record_clone_company,
	.create = _ctsvc_tc_record_create_company,
	.destroy = _ctsvc_tc_record_destroy_company,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_company,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = _ctsvc_tc_record_get_bool_company,
	.get_double = _ctsvc_tc_record_get_double_company,
	.get_int = _ctsvc_tc_record_get_int_company,
	.get_lli = _ctsvc_tc_record_get_lli_company,
	.get_str = _ctsvc_tc_record_get_str_company,
	.get_str_p = _ctsvc_tc_record_get_str_p_company,
	.set_bool = _ctsvc_tc_record_set_bool_company,
	.set_double = _ctsvc_tc_record_set_double_company,
	.set_int = _ctsvc_tc_record_set_int_company,
	.set_lli = _ctsvc_tc_record_set_lli_company,
	.set_str = _ctsvc_tc_record_set_str_company,
	.free_properties = _ctsvc_tc_record_free_property_company,
};

static int _ctsvc_tc_filter_add_type_company(ctsvc_data_type_e type)
{
	int ret = 0;
	int property_count = 0;
	ctsvc_property_s *property_list = NULL;
	contacts_filter_h filter = NULL;

	do {
		if (0 != (ret = contacts_filter_create(_contacts_company._uri, &filter))) break;
		if (0 != (ret = ctsvc_tc_record_get_property_company(PROPERTY_TYPE_CREATE1, &property_list, &property_count))) break;
		if (0 != (ret = ctsvc_tc_util_filter_add_type(filter, type, property_list, property_count))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_filter_destroy(filter))) break;
		filter = NULL;
		return 0;
	} while (0);
	contacts_filter_destroy(filter);
	return ret;
}

static int _ctsvc_tc_filter_add_bool_company(void)
{
	return _ctsvc_tc_filter_add_type_company(PROPERTY_BOOL);
}

static int _ctsvc_tc_filter_add_int_company(void)
{
	return _ctsvc_tc_filter_add_type_company(PROPERTY_INT);
}

static int _ctsvc_tc_filter_add_double_company(void)
{
	return _ctsvc_tc_filter_add_type_company(PROPERTY_DOUBLE);
}

static int _ctsvc_tc_filter_add_lli_company(void)
{
	return _ctsvc_tc_filter_add_type_company(PROPERTY_LLI);
}

static int _ctsvc_tc_filter_add_str_company(void)
{
	return _ctsvc_tc_filter_add_type_company(PROPERTY_STR);
}

ctsvc_tc_filter_plugin_s _tc_filter_company = {
	.add_bool = _ctsvc_tc_filter_add_bool_company,
	.add_double = _ctsvc_tc_filter_add_double_company,
	.add_int = _ctsvc_tc_filter_add_int_company,
	.add_lli = _ctsvc_tc_filter_add_lli_company,
	.add_str = _ctsvc_tc_filter_add_str_company,
};
