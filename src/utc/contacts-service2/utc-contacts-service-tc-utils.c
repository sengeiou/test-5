//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <string.h>
#include <stdio.h>
#include <glib.h>

#include <contacts.h>
#include <account.h>
#include <storage.h>
#include <system_info.h>
#include "tct_common.h"

#include "utc-contacts-service-tc-utils.h"

#define CTS_TC_PATH_LEN 1024
#define API_NAMESPACE			"[CONTACTS-SERVICE]"

struct cts_storage_s {
	const char *file_name;
	char *file_path;
};

static int accnt_id = 0;

char* ctsvc_tc_util_get_file_path(const char *file)
{
	struct cts_storage_s storage;
	storage.file_name = file;
	storage.file_path = NULL;

	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);

		char file_path[CTS_TC_PATH_LEN] = {0};
		snprintf(file_path, sizeof(file_path), "%s/res/%s", pszValue, storage.file_name);
		storage.file_path = strdup(file_path);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
	}

	return storage.file_path;
}

void ctsvc_tc_util_db_changed_cb(const char *view_uri, void *user_data) { }
void ctsvc_tc_util_setting_name_display_order_chagned_cb(contacts_name_display_order_e name_display_order, void* user_data) {}
void ctsvc_tc_util_setting_name_sorting_order_chagned_cb(contacts_name_sorting_order_e name_display_order, void* user_data) {}

int ctsvc_tc_util_account_insert(int *account_id)
{
	if (NULL == account_id)
		return -1;

	int ret = 0;
	account_h account = NULL;

	if (0 != accnt_id) {
		*account_id = accnt_id;
		return 0;
	}

	do {
		if (0 != (ret = account_create(&account))) break;
		if (0 != (ret = account_set_user_name(account, CTSVC_TC_UTIL_ACCOUNT_USER_NAME))) break;
		if (0 != (ret = account_set_package_name(account, CTSVC_TC_UTIL_ACCOUNT_PACKAGE_NAME))) break;
		if (0 != (ret = account_insert_to_db(account, account_id))) break;
		accnt_id = *account_id;
		if (0 != (ret = account_destroy(account))) break;
		account = NULL;
	} while (0);

	account_destroy(account);
	return ret;
}

int ctsvc_tc_util_account_delete()
{
	if (accnt_id <= 0)
		return -1;

	int ret = 0;
	do {
		if (0 != (ret = account_delete_from_db_by_id(accnt_id))) break;
	} while (0);

	return ret;
}


ctsvc_property_s ctsvc_tc_util_create_bool_property(unsigned int property_id, bool value)
{
	ctsvc_property_s prop;
	prop.property_id = property_id;
	prop.type = PROPERTY_BOOL;
	prop.val.bool_val = value;
	return prop;
}

ctsvc_property_s ctsvc_tc_util_create_int_property(unsigned int property_id, int  value)
{
	ctsvc_property_s prop;
	prop.property_id = property_id;
	prop.type = PROPERTY_INT;
	prop.val.int_val = value;
	return prop;
}

ctsvc_property_s ctsvc_tc_util_create_double_property(unsigned int property_id, double value)
{
	ctsvc_property_s prop;
	prop.property_id = property_id;
	prop.type = PROPERTY_DOUBLE;
	prop.val.double_val = value;
	return prop;
}

ctsvc_property_s ctsvc_tc_util_create_str_property(unsigned int property_id, char *value)
{
	ctsvc_property_s prop;
	prop.property_id = property_id;
	prop.type = PROPERTY_STR;
	prop.val.str_val = value;
	return prop;
}

ctsvc_property_s ctsvc_tc_util_create_lli_property(unsigned int property_id, long long int value)
{
	ctsvc_property_s prop;
	prop.property_id = property_id;
	prop.type = PROPERTY_LLI;
	prop.val.lli_val = value;
	return prop;
}

int ctsvc_tc_util_print_property(ctsvc_property_s *property_list, int property_count)
{
	int ret = 0;

	int i;
	for (i=0;i<property_count;i++) {
		ctsvc_property_s prop = property_list[i];
		switch (prop.type) {
		case PROPERTY_BOOL:
 			break;
 		case PROPERTY_INT:
 			break;
 		case PROPERTY_DOUBLE:
 			break;
 		case PROPERTY_STR:
 			break;
 		case PROPERTY_LLI:
			break;
		default: // invlid type
			return -1;
		}
	}
	return ret;

}


int ctsvc_tc_util_record_set_property(contacts_record_h record, ctsvc_property_s *property_list, int property_count)
{
	int ret = 0;
	if (NULL == record)
		return -1;

	int i;
	for (i=0;i<property_count;i++) {
		ctsvc_property_s prop = property_list[i];
		switch (prop.type) {
		case PROPERTY_BOOL:
 			ret += contacts_record_set_bool(record, prop.property_id, prop.val.bool_val);
 			break;
 		case PROPERTY_INT:
 			ret += contacts_record_set_int(record, prop.property_id, prop.val.int_val);
 			break;
 		case PROPERTY_DOUBLE:
 			ret += contacts_record_set_double(record, prop.property_id, prop.val.double_val);
 			break;
 		case PROPERTY_STR:
 			ret += contacts_record_set_str(record, prop.property_id, prop.val.str_val);
 			break;
 		case PROPERTY_LLI:
 			ret += contacts_record_set_lli(record, prop.property_id, prop.val.lli_val);
			break;
		default: // invlid type
			return -1;
		}
	}
	return ret;

}

int ctsvc_tc_util_filter_set(contacts_filter_h filter, ctsvc_property_s *property_list, int property_count)
{
	int ret = 0;
	if (property_count <= 0)
		return -1;

	ctsvc_property_s prop = property_list[0];
	switch (prop.type) {
	case PROPERTY_BOOL:
		ret = contacts_filter_add_bool(filter, prop.property_id, prop.val.bool_val);
		break;
	case PROPERTY_INT:
		ret = contacts_filter_add_int(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.int_val);
		break;
	case PROPERTY_DOUBLE:
		ret = contacts_filter_add_double(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.double_val);
		break;
	case PROPERTY_STR:
		ret = contacts_filter_add_str(filter, prop.property_id, CONTACTS_MATCH_FULLSTRING, prop.val.str_val);
		break;
	case PROPERTY_LLI:
		ret = contacts_filter_add_lli(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.lli_val);
		break;
	default: // invlid type
		return -1;
	}
	return ret;
}

static int _ctsvc_tc_util_record_compare_bool(contacts_record_h record, unsigned int property_id, bool val_comp)
{
	bool val;
	contacts_record_get_bool(record, property_id, &val);
	if (val != val_comp) {
		return -1;
	}
	return 0;
}

static int _ctsvc_tc_util_record_compare_int(contacts_record_h record, unsigned int property_id, int val_comp)
{
	int val;
	contacts_record_get_int(record, property_id, &val);
	if (val != val_comp) {
		return -1;
	}
	return 0;
}

static int _ctsvc_tc_util_record_compare_double(contacts_record_h record, unsigned int property_id, double val_comp)
{
	double val;
	contacts_record_get_double(record, property_id, &val);
	if (val != val_comp) {
		return -1;
	}
	return 0;
}

static int _ctsvc_tc_util_record_compare_lli(contacts_record_h record, unsigned int property_id, long long int val_comp)
{
	long long int val;
	contacts_record_get_lli(record, property_id, &val);
	if (val != val_comp) {
		return -1;
	}
	return 0;
}

static int _ctsvc_tc_util_record_compare_str(contacts_record_h record, unsigned int property_id, char *val_comp)
{
	int ret = 0;
	char *val = NULL;
	ret = contacts_record_get_str_p(record, property_id, &val);
	if (CONTACTS_ERROR_NONE != ret)
		return ret;

	if (STRING_EQUAL != g_strcmp0(val_comp, val)) {
		return -1;
	}
	val = NULL;

	ret = contacts_record_get_str(record, property_id, &val);
	if (CONTACTS_ERROR_NONE != ret)
		return ret;

	if (STRING_EQUAL != g_strcmp0(val_comp, val)) {
		free(val);
		return -1;
	}
	free(val);
	val = NULL;

	return 0;
}

int ctsvc_tc_util_record_compare_type(contacts_record_h record, ctsvc_data_type_e type, ctsvc_property_s *properties, int property_count)
{
	int i;
	int ret = 0;

	for (i=0;i<property_count;i++) {
		ctsvc_property_s prop = properties[i];
		if (prop.type == type) {
			switch (prop.type) {
			case PROPERTY_BOOL:
				ret = _ctsvc_tc_util_record_compare_bool(record, prop.property_id, prop.val.bool_val);
				break;
			case PROPERTY_INT:
				ret = _ctsvc_tc_util_record_compare_int(record, prop.property_id, prop.val.int_val);
				break;
			case PROPERTY_DOUBLE:
				ret = _ctsvc_tc_util_record_compare_double(record, prop.property_id, prop.val.double_val);
				break;
			case PROPERTY_STR:
				if (_contacts_image.path == prop.property_id
						|| _contacts_company.logo == prop.property_id
						|| _contacts_group.image_path == prop.property_id
						|| _contacts_contact.image_thumbnail_path == prop.property_id) {
					if (prop.val.str_val)
						return 0;
					else
						return -1;
				}
				else {
					ret = _ctsvc_tc_util_record_compare_str(record, prop.property_id, prop.val.str_val);
				}
				break;
			case PROPERTY_LLI:
				ret = _ctsvc_tc_util_record_compare_lli(record, prop.property_id, prop.val.lli_val);
				break;
			default: // invlid type
				return -1;
			}
		}
		if (0 != ret)
			break;
	}
	return ret;
}

int ctsvc_tc_util_filter_add_type(contacts_filter_h filter, ctsvc_data_type_e type, ctsvc_property_s *properties, int property_count)
{
	int i;
	int ret = 0;

	for (i=0;i<property_count;i++) {
		ctsvc_property_s prop = properties[i];
		if (prop.type == type) {
			switch (prop.type) {
			case PROPERTY_BOOL:
				ret = contacts_filter_add_bool(filter, prop.property_id, prop.val.bool_val);
				return ret;
			case PROPERTY_INT:
				ret = contacts_filter_add_int(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.int_val);
				return ret;
			case PROPERTY_DOUBLE:
				ret = contacts_filter_add_double(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.double_val);
				return ret;
			case PROPERTY_STR:
				ret = contacts_filter_add_str(filter, prop.property_id, CONTACTS_MATCH_FULLSTRING, prop.val.str_val);
				return ret;
			case PROPERTY_LLI:
				ret = contacts_filter_add_lli(filter, prop.property_id, CONTACTS_MATCH_EQUAL, prop.val.lli_val);
				return ret;
			default: // invlid type
				return -1;
			}
		}
		if (0 != ret)
			break;
	}
	return ret;
}


int ctsvc_tc_util_record_compare(contacts_record_h record, ctsvc_property_s *properties, int property_count)
{
	int i;
	int ret = 0;

	for (i=0;i<property_count;i++) {
		ctsvc_property_s prop = properties[i];
		switch (prop.type) {
		case PROPERTY_BOOL:
			ret = _ctsvc_tc_util_record_compare_bool(record, prop.property_id, prop.val.bool_val);
			break;
		case PROPERTY_INT:
			ret = _ctsvc_tc_util_record_compare_int(record, prop.property_id, prop.val.int_val);
			break;
		case PROPERTY_DOUBLE:
			ret = _ctsvc_tc_util_record_compare_double(record, prop.property_id, prop.val.double_val);
			break;
		case PROPERTY_STR:
			if (_contacts_image.path == prop.property_id
					|| _contacts_company.logo == prop.property_id
					|| _contacts_group.image_path == prop.property_id
					|| _contacts_contact.image_thumbnail_path == prop.property_id) {
				if (prop.val.str_val)
					return 0;
				else
					return -1;
			}
			else {
				ret = _ctsvc_tc_util_record_compare_str(record, prop.property_id, prop.val.str_val);
			}
			break;
		case PROPERTY_LLI:
			ret = _ctsvc_tc_util_record_compare_lli(record, prop.property_id, prop.val.lli_val);
			break;
		default: // invlid type
			return -1;
		}
		if (0 != ret)
			break;
	}
	return ret;
}

const char *ctsvc_tc_util_get_view_uri(ctsvc_view_e view)
{
	switch (view) {
	case VIEW_ADDRESSBOOK:
		return _contacts_address_book._uri;
	case VIEW_GROUP:
		return _contacts_group._uri;
	case VIEW_PERSON:
		return _contacts_person._uri;
	case VIEW_SIMPLE_CONTACT:
		return _contacts_simple_contact._uri;
	case VIEW_CONTACT:
		return _contacts_contact._uri;
	case VIEW_MY_PROFILE:
		return _contacts_my_profile._uri;
	case VIEW_NAME:
		return _contacts_name._uri;
	case VIEW_NUMBER:
		return _contacts_number._uri;
	case VIEW_EMAIL:
		return _contacts_email._uri;
	case VIEW_ADDRESS:
		return _contacts_address._uri;
	case VIEW_NOTE:
		return _contacts_note._uri;
	case VIEW_URL:
		return _contacts_url._uri;
	case VIEW_EVENT:
		return _contacts_event._uri;
	case VIEW_GROUP_RELATION:
		return _contacts_group_relation._uri;
	case VIEW_RELATIONSHIP:
		return _contacts_relationship._uri;
	case VIEW_IMAGE:
		return _contacts_image._uri;
	case VIEW_COMPANY:
		return _contacts_company._uri;
	case VIEW_NICKNAME:
		return _contacts_nickname._uri;
	case VIEW_MESSENGER:
		return _contacts_messenger._uri;
	case VIEW_EXTENSION:
		return _contacts_extension._uri;
	case VIEW_SDN:
		return _contacts_sdn._uri;
	case VIEW_PROFILE:
		return _contacts_profile._uri;
	case VIEW_ACTIVITY_PHOTO:
		return _contacts_activity_photo._uri;
	case VIEW_ACTIVITY:
		return _contacts_activity._uri;
	case VIEW_SPEEDDIAL:
		return _contacts_speeddial._uri;
	case VIEW_PHONE_LOG:
		return _contacts_phone_log._uri;
	case VIEW_CONTACT_UPDATED_INFO:
		return _contacts_contact_updated_info._uri;
	case VIEW_MY_PROFILE_UPDATED_INFO:
		return _contacts_my_profile_updated_info._uri;
	case VIEW_GROUP_UPDATED_INFO:
		return _contacts_group_updated_info._uri;
	case VIEW_GROUP_MEMBER_UPDATED_INFO:
		return _contacts_group_member_updated_info._uri;
	case VIEW_GROUPREL_UPDATED_INFO:
		return _contacts_grouprel_updated_info._uri;
	case VIEW_PHONE_LOG_STAT:
		return _contacts_phone_log_stat._uri;
	case VIEW_SIP:
		return _contacts_sip._uri;
	default:
		return NULL;
	}
}

bool ctsvc_tc_util_is_sim_support()
{
	bool is_supported = false;
	system_info_get_platform_bool("http://tizen.org/feature/network.telephony", &is_supported);
	return is_supported;
}

bool ctsvc_tc_util_is_contact_support()
{
	int ret;
	static bool feature_checked = false;
	static bool contact_feature = false;

	if (feature_checked)
		return contact_feature;

	ret = system_info_get_platform_bool("http://tizen.org/feature/contact", &contact_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		return contact_feature;
	}

	feature_checked = true;
	return contact_feature;
}

