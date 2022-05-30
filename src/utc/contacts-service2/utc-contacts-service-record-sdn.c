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
#include "utc-contacts-service-record-sdn.h"

static int _ctsvc_tc_record_clone_sdn(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	contacts_record_h record_clone = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sdn._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_clone(record, &record_clone))) break;
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

static int _ctsvc_tc_record_create_sdn(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sdn._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_destroy_sdn(void)
{
	int ret = 0;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sdn._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		return 0;
	} while(0);
	contacts_record_destroy(record, true);
	return ret;
}

static int _ctsvc_tc_record_get_uri_p_sdn(void)
{
	int ret = 0;
	const char *uri = NULL;
	contacts_record_h record = NULL;
	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_create(_contacts_sdn._uri, &record))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_uri_p(record, &uri))) break;
		if (NULL == uri || STRING_EQUAL != strcmp(uri, _contacts_sdn._uri)) {
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

static int _ctsvc_tc_record_get_str_sdn(void)
{
	int ret = 0;
	char *str = NULL;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_all_records(_contacts_sdn._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		ret = contacts_list_get_current_record_p(list, &record);
		if (CONTACTS_ERROR_NO_DATA == ret) {
			ret = CONTACTS_ERROR_NONE;
			break;
		}
		if (CONTACTS_ERROR_NONE != ret) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_str(record, _contacts_sdn.number, &str))) break;
		free(str);
		str = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		return 0;
	} while(0);

	free(str);
	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);

	if (!ctsvc_tc_util_is_sim_support() && CONTACTS_ERROR_NOT_SUPPORTED == ret)
		return 0;

	return ret;
}

static int _ctsvc_tc_record_get_str_p_sdn(void)
{
	int ret = 0;
	char *str = NULL;
	contacts_list_h list = NULL;
	contacts_record_h record = NULL;

	do {
		if (CONTACTS_ERROR_NONE != (ret = contacts_db_get_all_records(_contacts_sdn._uri, OFFSET_DEFAULT, LIMIT_DEFAULT, &list))) break;
		ret = contacts_list_get_current_record_p(list, &record);
		if (CONTACTS_ERROR_NO_DATA == ret) {
			ret = CONTACTS_ERROR_NONE;
			break;
		}
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_get_str_p(record, _contacts_sdn.number, &str))) break;
		if (CONTACTS_ERROR_NONE != (ret = contacts_record_destroy(record, true))) break;
		record = NULL;
		if (CONTACTS_ERROR_NONE != (ret = contacts_list_destroy(list, true))) break;
		list = NULL;
		return 0;
	} while(0);

	contacts_record_destroy(record, true);
	contacts_list_destroy(list, true);

	if (!ctsvc_tc_util_is_sim_support() && CONTACTS_ERROR_NOT_SUPPORTED == ret)
		return 0;

	return ret;
}

ctsvc_tc_record_plugin_s _tc_record_sdn = {
	.clone = _ctsvc_tc_record_clone_sdn,
	.create = _ctsvc_tc_record_create_sdn,
	.destroy = _ctsvc_tc_record_destroy_sdn,
	.get_uri_p = _ctsvc_tc_record_get_uri_p_sdn,
	.add_child_record = NULL,
	.clone_child_record_list = NULL,
	.remove_child_record = NULL,
	.get_child_record_at_p = NULL,
	.get_child_record_count = NULL,
	.get_bool = NULL,
	.get_double = NULL,
	.get_int = NULL,
	.get_lli = NULL,
	.get_str = _ctsvc_tc_record_get_str_sdn,
	.get_str_p = _ctsvc_tc_record_get_str_p_sdn,
	.set_bool = NULL,
	.set_double = NULL,
	.set_int = NULL,
	.set_lli = NULL,
	.set_str = NULL,
	.free_properties = NULL,
};
