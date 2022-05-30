/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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
 */
#include <glib.h>
#include <system_info.h>
#include <iotcon.h>

#include "utc-iotcon-common.h"

#define REPRESENTATION_LIST_COUNT 10
#define REPRESENTATION_ATTRIBUTES_KEY_INT "int1"
#define REPRESENTATION_ATTRIBUTES_KEY_DOUBLE "double1"
#define REPRESENTATION_ATTRIBUTES_KEY_BOOL "bool1"
#define REPRESENTATION_ATTRIBUTES_KEY_STR "str1"
#define REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR "byte_str1"
#define REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES "attributes1"
#define REPRESENTATION_ATTRIBUTES_KEY_LIST "list1_1"
#define REPRESENTATION_ATTRIBUTES_KEY_NULL "null1"
#define REPRESENTATION_LIGHT_RESOURCE_TYPE "core.light"
#define REPRESENTATION_LIGHT_RESOURCE_URI "/a/light"

static bool g_feature;

static int _representation_create_list_attributes(iotcon_list_h *list_attributes)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	iotcon_attributes_h attributes = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_attributes_create(&attributes);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}

		ret = iotcon_list_add_attributes(list, attributes, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			iotcon_list_destroy(list);
			return 1;
		}

		iotcon_attributes_destroy(attributes);
	}
	*list_attributes = list;

	return 0;
}

static int _representation_create_list_double(iotcon_list_h *list_double)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_DOUBLE, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_add_double(list, (double)i, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_double() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	*list_double = list;
	return 0;
}

static int _representation_create_list_str(iotcon_list_h *list_str)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_STR, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		char temp_str[10];
		snprintf(temp_str, sizeof(temp_str), "val%d", i);

		ret = iotcon_list_add_str(list, temp_str, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_str() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	*list_str = list;
	return 0;
}

static int _representation_create_list_byte_str(iotcon_list_h *list_byte_str)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_BYTE_STR, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		unsigned char temp_byte_str[3] = {70, 71, 72};

		ret = iotcon_list_add_byte_str(list, temp_byte_str, 3, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_byte_str() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	*list_byte_str = list;
	return 0;
}

static int _representation_create_list_int(iotcon_list_h *list_int)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_add_int(list, i, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	*list_int = list;
	return 0;
}

static int _representation_create_list_bool(iotcon_list_h *list_bool)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_BOOL, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		bool value = (i % 2)? true: false;
		ret = iotcon_list_add_bool(list, value, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_bool() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	*list_bool = list;
	return 0;
}

static int _representation_create_list_list(iotcon_list_h *list_list)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	iotcon_list_h list_temp = NULL;

	ret = iotcon_list_create(IOTCON_TYPE_LIST, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_create(IOTCON_TYPE_INT, &list_temp);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}

		ret = iotcon_list_add_list(list, list_temp, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_list() Fail(%d)", ret);
			iotcon_list_destroy(list_temp);
			iotcon_list_destroy(list);
			return 1;
		}

		iotcon_list_destroy(list_temp);
	}
	*list_list = list;
	return 0;
}

static int _representation_create_attributes(iotcon_attributes_h *attributes_handle)
{
	int i;
	int ret;
	iotcon_attributes_h attributes = NULL;
	char key[20];
	unsigned char byte_str[3] = {70, 71, 72};
	bool val_bool;
	iotcon_attributes_h val_attributes = NULL;
	iotcon_list_h val_list1, val_list2, val_list3;

	ret = iotcon_attributes_create(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		snprintf(key, sizeof(key), "int%d", i);
		ret = iotcon_attributes_add_int(attributes, key, i);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "bool%d", i);
		val_bool = (i % 2)? true: false;
		ret = iotcon_attributes_add_bool(attributes, key, val_bool);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_bool() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "double%d", i);
		ret = iotcon_attributes_add_double(attributes, key, (double)i);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_double() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "str%d", i);
		ret = iotcon_attributes_add_str(attributes, key, key);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_str() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "byte_str%d", i);
		ret = iotcon_attributes_add_byte_str(attributes, key, byte_str, 3);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_byte_str() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "attributes%d", i);
		ret = iotcon_attributes_create(&val_attributes);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_attributes_add_int(val_attributes, "val_attributes", 10);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_attributes_add_attributes(attributes, key, val_attributes);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_attributes() Fail(%d)", ret);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "list1_%d", i);
		ret = iotcon_list_create(IOTCON_TYPE_INT, &val_list1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_list_add_int(val_list1, 1, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_list_add_int(val_list1, 2, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_list_add_int(val_list1, 3, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_attributes_add_list(attributes, key, val_list1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		snprintf(key, sizeof(key), "list2_%d", i);
		ret = iotcon_list_create(IOTCON_TYPE_LIST, &val_list2);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_list_add_list(val_list2, val_list1, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_list() Fail(%d)", ret);
			iotcon_list_destroy(val_list2);
			iotcon_list_destroy(val_list1);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		iotcon_list_destroy(val_list1);

		ret = iotcon_attributes_add_list(attributes, key, val_list2);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
			iotcon_list_destroy(val_list2);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		iotcon_list_destroy(val_list2);

		snprintf(key, sizeof(key), "list3_%d", i);
		ret = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES, &val_list3);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		ret = iotcon_list_add_attributes(val_list3, val_attributes, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_attributes() Fail(%d)", ret);
			iotcon_list_destroy(val_list3);
			iotcon_attributes_destroy(val_attributes);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		iotcon_attributes_destroy(val_attributes);

		ret = iotcon_attributes_add_list(attributes, key, val_list3);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
			iotcon_list_destroy(val_list3);
			iotcon_attributes_destroy(attributes);
			return 1;
		}

		iotcon_list_destroy(val_list3);

		snprintf(key, sizeof(key), "null%d", i);
		ret = iotcon_attributes_add_null(attributes, key);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_add_null() Fail(%d)", ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}
	}

	*attributes_handle = attributes;
	return 0;
}

static int _representation_create_representation(iotcon_representation_h *repr_handle)
{
	int ret;
	iotcon_attributes_h attributes = NULL;
	iotcon_representation_h repr;
	iotcon_resource_types_h types = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	ret = _representation_create_attributes(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("_representation_create_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_attributes(repr, attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_representation_destroy(repr);
		return 1;
	}
	iotcon_attributes_destroy(attributes);

	ret = iotcon_resource_interfaces_create(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_resource_interfaces(repr, ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_resource_interfaces() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_uri_path(repr, REPRESENTATION_LIGHT_RESOURCE_URI);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_set_uri_path() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_resource_types_create(&types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_create() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}
	ret = iotcon_resource_types_add(types, REPRESENTATION_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return 1;
	}
	ret = iotcon_representation_set_resource_types(repr, types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("_representation_create_attributes() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return 1;
	}
	iotcon_resource_interfaces_destroy(ifaces);
	iotcon_resource_types_destroy(types);

	*repr_handle = repr;
	return 0;
}


/* ##################################################### */

/**
 * @function      utc_iotcon_representation_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_representation_startup(void)
{
	int ret;
	char *path;

	g_feature = false;

	icutc_check_wifi_state();

	ret = system_info_get_platform_bool("http://tizen.org/feature/iot.ocf", &g_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		ICUTC_ERR("system_info_get_platform_bool() Fail(%d)", ret);
		return;
	}

	ret = icutc_get_svr_db_path(&path);
	if (0 != ret) {
		ICUTC_ERR("icutc_get_svr_db_path() Fail(%d)", ret);
		return;
	}

	ICUTC_INFO("path : %s", path);
	ret = iotcon_initialize(path);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_initialize() Fail(%d)", ret);
		free(path);
		return;
	}
	free(path);
}

/**
 * @function      utc_iotcon_represenctation_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_iotcon_representation_cleanup(void)
{
	if (true == g_feature)
		iotcon_deinitialize();
}

/**
 * @testcase      utc_iotcon_representation_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a representation with invalid parameter.
 */
int utc_iotcon_representation_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_representation_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_create_p
 * @since_tizen   3.0
 * @description   Test creating a representation.
 */
int utc_iotcon_representation_create_p(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_representation_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a representation with invalid parameter.
 */
int utc_iotcon_representation_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_representation_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a representation.
 */
int utc_iotcon_representation_destroy_p(void)
{
	int ret;
	iotcon_representation_h repr = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_destroy(repr);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_destroy(repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_clone_n
 * @since_tizen   3.0
 * @description   Test fail cloning a representation with invalid parameter.
 */
int utc_iotcon_representation_clone_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_clone = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_clone(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_clone(NULL, &repr_clone);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_clone() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_clone(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_clone() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_clone_p
 * @since_tizen   3.0
 * @description   Test cloning a representation.
 */
int utc_iotcon_representation_clone_p(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_clone = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_clone(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = _representation_create_representation(&repr_child);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_clone() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_add_child(repr, repr_child);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr_child);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr_child);

	ret = iotcon_representation_clone(repr, &repr_clone);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_clone() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr_clone);
	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_uri_path_n
 * @since_tizen   3.0
 * @description   Test fail setting uri path to presentation with invalid parameter.
 */
int utc_iotcon_representation_set_uri_path_n(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_representation_set_uri_path(NULL, REPRESENTATION_LIGHT_RESOURCE_URI);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_representation_set_uri_path(NULL, REPRESENTATION_LIGHT_RESOURCE_URI);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_set_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_uri_path(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_set_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_uri_path_p
 * @since_tizen   3.0
 * @description   Test setting uri path to presentation.
 */
int utc_iotcon_representation_set_uri_path_p(void)
{
	int ret;
	iotcon_representation_h repr;

	if (false == g_feature) {
		ret = iotcon_representation_set_uri_path(NULL, REPRESENTATION_LIGHT_RESOURCE_URI);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_representation_destroy(repr);
	return 0;

}

/**
 * @testcase      utc_iotcon_representation_get_uri_path_n
 * @since_tizen   3.0
 * @description   Test fail getting uri path from presentation with invalid parameter.
 */
int utc_iotcon_representation_get_uri_path_n(void)
{
	int ret;
	iotcon_representation_h repr;
	char *value;

	if (false == g_feature) {
		ret = iotcon_representation_get_uri_path(NULL, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_uri_path(NULL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_uri_path(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_uri_path_p
 * @since_tizen   3.0
 * @description   Test getting uri path from presentation.
 */
int utc_iotcon_representation_get_uri_path_p(void)
{
	int ret;
	iotcon_representation_h repr;
	char *value;

	if (false == g_feature) {
		ret = iotcon_representation_get_uri_path(NULL, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_uri_path(repr, &value);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_get_uri_path() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}


	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_resource_types_n
 * @since_tizen   3.0
 * @description   Test fail setting resource types to presentation with invalid parameter.
 */
int utc_iotcon_representation_set_resource_types_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_resource_types(NULL, types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_resource_types_create(&types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_create() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_resource_types_add(types, REPRESENTATION_LIGHT_RESOURCE_TYPE);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_types_add() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_resource_types(NULL, types);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_set_resource_types() Fail(%d)", ret);
		iotcon_resource_types_destroy(types);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_resource_types_destroy(types);
	iotcon_representation_destroy(repr);
	return 0;

}

/**
 * @testcase      utc_iotcon_representation_set_resource_types_p
 * @since_tizen   3.0
 * @description   Test setting resource types to presentation.
 */
int utc_iotcon_representation_set_resource_types_p(void)
{
	int ret;
	iotcon_representation_h repr;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_resource_types(NULL, types);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_representation_destroy(repr);
	return 0;

}


/**
 * @testcase      utc_iotcon_representation_get_resource_types_n
 * @since_tizen   3.0
 * @description   Test fail getting resource types from presentation with invalid parameter.
 */
int utc_iotcon_representation_get_resource_types_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_get_resource_types(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_resource_types(NULL, &types);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_types() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_resource_types(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_types() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;

}

/**
 * @testcase      utc_iotcon_representation_get_resource_types_p
 * @since_tizen   3.0
 * @description   Test getting resource types from presentation.
 */
int utc_iotcon_representation_get_resource_types_p(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_types_h types = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_get_resource_types(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_resource_types(repr, &types);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_types() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;

}


/**
 * @testcase      utc_iotcon_representation_set_resource_interfaces_n
 * @since_tizen   3.0
 * @description   Test fail setting interfaces to presentation with invalid parameter.
 */
int utc_iotcon_representation_set_resource_interfaces_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_resource_interfaces(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_resource_interfaces_create(&ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_create() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_DEFAULT);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_resource_interfaces_add() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_resource_interfaces(NULL, ifaces);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_set_resource_interfaces() Fail(%d)", ret);
		iotcon_resource_interfaces_destroy(ifaces);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_resource_interfaces_destroy(ifaces);
	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_resource_interfaces_p
 * @since_tizen   3.0
 * @description   Test setting interfaces to presentation.
 */
int utc_iotcon_representation_set_resource_interfaces_p(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_resource_interfaces(repr, ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_representation_destroy(repr);
	return 0;

}


/**
 * @testcase      utc_iotcon_representation_set_resource_interfaces_n
 * @since_tizen   3.0
 * @description   Test fail getting resource interfaces from presentation with invalid parameter.
 */
int utc_iotcon_representation_get_resource_interfaces_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_resource_interfaces_h ifaces = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_get_resource_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_resource_interfaces(NULL, &ifaces);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_interfaces() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_resource_interfaces(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_interfaces() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;

}

/**
 * @testcase      utc_iotcon_representation_get_resource_interfaces_p
 * @since_tizen   3.0
 * @description   Test getting resource interfaces from presentation.
 */
int utc_iotcon_representation_get_resource_interfaces_p(void)
{
	int ret;
	iotcon_representation_h repr;
	iotcon_resource_interfaces_h ifaces;

	if (false == g_feature) {
		ret = iotcon_representation_get_resource_interfaces(NULL, &ifaces);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_resource_interfaces(repr, &ifaces);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_get_resource_interfaces() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_attributes_n
 * @since_tizen   3.0
 * @description   Test fail setting attributes to presentation with invalid parameter.
 */
int utc_iotcon_representation_set_attributes_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_attributes(NULL, attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = _representation_create_attributes(&attributes);
	if (0 != ret) {
		ICUTC_ERR("_representation_create_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_set_attributes(NULL, attributes);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_set_attributes_p
 * @since_tizen   3.0
 * @description   Test setting attributes to presentation.
 */
int utc_iotcon_representation_set_attributes_p(void)
{
	int ret;
	iotcon_representation_h repr;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_set_attributes(NULL, attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_attributes_n
 * @since_tizen   3.0
 * @description   Test fail getting attributes from presentation with invalid parameter.
 */
int utc_iotcon_representation_get_attributes_n(void)
{
	int ret;
	iotcon_representation_h repr;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_representation_get_attributes(NULL, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_attributes(NULL, &attributes);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_attributes(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;

}

/**
 * @testcase      utc_iotcon_representation_get_attributes_p
 * @since_tizen   3.0
 * @description   Test getting attributes from presentation.
 */
int utc_iotcon_representation_get_attributes_p(void)
{
	int ret;
	iotcon_representation_h repr;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_representation_get_attributes(NULL, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_representation(&repr);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_representation_get_attributes(repr, &attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_get_attributes() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a attributes with invalid parameter.
 */
int utc_iotcon_attributes_create_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_attributes_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_attributes_create(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_create_p
 * @since_tizen   3.0
 * @description   Test creating a attributes.
 */
int utc_iotcon_attributes_create_p(void)
{
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a attributes with invalid parameter.
 */
int utc_iotcon_attributes_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_attributes_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_attributes_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a attributes.
 */
int utc_iotcon_attributes_destroy_p(void)
{
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_create(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_destroy(attributes);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_clone_n
 * @since_tizen   3.0
 * @description   Test fail cloning a attributes with invalid parameter.
 */
int utc_iotcon_attributes_clone_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_attributes_h attributes_clone;

	if (false == g_feature) {
		ret = iotcon_attributes_clone(NULL, &attributes_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_clone(NULL, &attributes_clone);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_clone() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_clone(attributes, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_clone() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_clone_p
 * @since_tizen   3.0
 * @description   Test cloning a attributes.
 */
int utc_iotcon_attributes_clone_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_attributes_h attributes_clone;

	if (false == g_feature) {
		ret = iotcon_attributes_clone(NULL, &attributes_clone);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_clone(attributes, &attributes_clone);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_clone() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes_clone);
	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_int_n
 * @since_tizen   3.0
 * @description   Test fail adding integer value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_int_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	int value = 1;

	if (false == g_feature) {
		ret = iotcon_attributes_add_int(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_int(NULL, "key", value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_int(attributes, NULL, value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_int_p
 * @since_tizen   3.0
 * @description   Test adding integer value to attributes.
 */
int utc_iotcon_attributes_add_int_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	int value = 1;

	if (false == g_feature) {
		ret = iotcon_attributes_add_int(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_bool_n
 * @since_tizen   3.0
 * @description   Test fail adding boolean value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_bool_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	bool value = false;

	if (false == g_feature) {
		ret = iotcon_attributes_add_bool(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_bool(NULL, "key", value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_bool(attributes, NULL, value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_bool_p
 * @since_tizen   3.0
 * @description   Test adding boolean value to attributes.
 */
int utc_iotcon_attributes_add_bool_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	bool value = false;

	if (false == g_feature) {
		ret = iotcon_attributes_add_bool(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_double_n
 * @since_tizen   3.0
 * @description   Test fail adding double value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_double_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	double value = 1.0;

	if (false == g_feature) {
		ret = iotcon_attributes_add_double(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_double(NULL, "key", value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_double(attributes, NULL, value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_add_double_p
 * @since_tizen   3.0
 * @description   Test adding double value to attributes.
 */
int utc_iotcon_attributes_add_double_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	double value = 1.0;

	if (false == g_feature) {
		ret = iotcon_attributes_add_double(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}


/**
 * @testcase      utc_iotcon_attributes_add_str_n
 * @since_tizen   3.0
 * @description   Test fail adding string value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_str_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	char *value = "value";

	if (false == g_feature) {
		ret = iotcon_attributes_add_str(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_str(NULL, "key", value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_str(attributes, NULL, value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_str(attributes, "key", NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_str_p
 * @since_tizen   3.0
 * @description   Test adding string value to attributes.
 */
int utc_iotcon_attributes_add_str_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	char *value = "value";

	if (false == g_feature) {
		ret = iotcon_attributes_add_str(NULL, "key", value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_byte_str_n
 * @since_tizen   3.0
 * @description   Test fail adding byte string value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_byte_str_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	unsigned char value[3] = {70, 71, 72};

	if (false == g_feature) {
		ret = iotcon_attributes_add_byte_str(NULL, "key", value, 3);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_byte_str(NULL, "key", value, 3);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_byte_str(attributes, NULL, value, 3);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_byte_str(attributes, "key", NULL, 3);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_byte_str_p
 * @since_tizen   3.0
 * @description   Test adding byte string value to attributes.
 */
int utc_iotcon_attributes_add_byte_str_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	unsigned char value[3] = {70, 71, 72};

	if (false == g_feature) {
		ret = iotcon_attributes_add_byte_str(NULL, "key", value, 3);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_list_n
 * @since_tizen   3.0
 * @description   Test fail adding list value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_list_n(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;
	iotcon_list_h list_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_attributes_add_list(NULL, "key", list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = _representation_create_list_int(&list_temp);
	if (0 != ret) {
		ICUTC_ERR("_representation_create_list_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_list(NULL, "key", list_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_list(attributes, NULL, list_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_list(attributes, "key", NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_list_destroy(list_temp);
	iotcon_attributes_destroy(attributes);
	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_add_list_p
 * @since_tizen   3.0
 * @description   Test adding list value to attributes.
 */
int utc_iotcon_attributes_add_list_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_list_h list_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_attributes_add_list(NULL, "key", list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_attributes_n
 * @since_tizen   3.0
 * @description   Test fail adding attributes value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_attributes_n(void)
{
	int ret;
	iotcon_attributes_h attributes = NULL;
	iotcon_attributes_h attributes_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_attributes_add_attributes(NULL, "key", attributes_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = _representation_create_attributes(&attributes_temp);
	if (0 != ret) {
		ICUTC_ERR("_representation_create_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_attributes(NULL, "key", attributes_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_attributes(attributes, NULL, attributes_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_attributes(attributes, "key", NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes_temp);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes_temp);
	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_attributes_p
 * @since_tizen   3.0
 * @description   Test adding attributes value to attributes.
 */
int utc_iotcon_attributes_add_attributes_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_attributes_h attributes_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_attributes_add_attributes(NULL, "key", attributes_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_null_n
 * @since_tizen   3.0
 * @description   Test fail adding null value to attributes with invalid parameter.
 */
int utc_iotcon_attributes_add_null_n(void)
{
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_add_null(NULL, "key");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_add_null(NULL, "key");
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_add_null(attributes, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_add_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_add_null_p
 * @since_tizen   3.0
 * @description   Test adding null value to attributes.
 */
int utc_iotcon_attributes_add_null_p(void)
{
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_add_null(NULL, "key");
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_int_n
 * @since_tizen   3.0
 * @description   Test fail getting integer value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_int_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	int value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_int(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_int(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_int(attributes, NULL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_int(attributes, REPRESENTATION_ATTRIBUTES_KEY_INT, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_int_p
 * @since_tizen   3.0
 * @description   Test getting integer value from attributes.
 */
int utc_iotcon_attributes_get_int_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	int value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_int(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_int(attributes, REPRESENTATION_ATTRIBUTES_KEY_INT, &value);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_int() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_bool_n
 * @since_tizen   3.0
 * @description   Test fail getting boolean value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_bool_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	bool value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_bool(NULL, REPRESENTATION_ATTRIBUTES_KEY_BOOL, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_bool(NULL, REPRESENTATION_ATTRIBUTES_KEY_BOOL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_bool(attributes, NULL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_bool(attributes, REPRESENTATION_ATTRIBUTES_KEY_BOOL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_bool_p
 * @since_tizen   3.0
 * @description   Test getting boolean value from attributes
 */
int utc_iotcon_attributes_get_bool_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	bool value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_bool(NULL, REPRESENTATION_ATTRIBUTES_KEY_BOOL, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_bool(attributes, REPRESENTATION_ATTRIBUTES_KEY_BOOL, &value);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_bool() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_double_n
 * @since_tizen   3.0
 * @description   Test fail getting double value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_double_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	double value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_double(NULL, REPRESENTATION_ATTRIBUTES_KEY_DOUBLE, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_double(NULL, REPRESENTATION_ATTRIBUTES_KEY_DOUBLE, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_double(attributes, NULL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_double(attributes, REPRESENTATION_ATTRIBUTES_KEY_DOUBLE, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}


/**
 * @testcase      utc_iotcon_attributes_get_double_p
 * @since_tizen   3.0
 * @description   Test getting double value from attributes.
 */
int utc_iotcon_attributes_get_double_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	double value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_double(NULL, REPRESENTATION_ATTRIBUTES_KEY_DOUBLE, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_double(attributes, REPRESENTATION_ATTRIBUTES_KEY_DOUBLE, &value);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_double() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_str_n
 * @since_tizen   3.0
 * @description   Test fail getting string value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_str_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	char *value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_STR, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_STR, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_str(attributes, NULL, &value);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_str(attributes, REPRESENTATION_ATTRIBUTES_KEY_STR, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_str_p
 * @since_tizen   3.0
 * @description   Test getting string value from attributes.
 */
int utc_iotcon_attributes_get_str_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	char *value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_STR, &value);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_str(attributes, REPRESENTATION_ATTRIBUTES_KEY_STR, &value);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_byte_str_n
 * @since_tizen   3.0
 * @description   Test fail getting byte string value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_byte_str_n(void)
{
	int ret;
	int len;
	iotcon_attributes_h attributes;
	unsigned char *value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_byte_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, &value, &len);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_byte_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, &value, &len);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_byte_str(attributes, NULL, &value, &len);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_byte_str(attributes, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, NULL, &len);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_byte_str(attributes, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, &value, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_byte_str_p
 * @since_tizen   3.0
 * @description   Test getting byte string value from attributes.
 */
int utc_iotcon_attributes_get_byte_str_p(void)
{
	int ret;
	int len;
	iotcon_attributes_h attributes;
	unsigned char *value;

	if (false == g_feature) {
		ret = iotcon_attributes_get_byte_str(NULL, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, &value, &len);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_byte_str(attributes, REPRESENTATION_ATTRIBUTES_KEY_BYTE_STR, &value, &len);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_byte_str() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}


/**
 * @testcase      utc_iotcon_attributes_get_list_n
 * @since_tizen   3.0
 * @description   Test fail getting list value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_list_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_list_h list_temp;

	if (false == g_feature) {
		ret = iotcon_attributes_get_list(NULL, REPRESENTATION_ATTRIBUTES_KEY_LIST, &list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_list(NULL, REPRESENTATION_ATTRIBUTES_KEY_LIST, &list_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_list() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_list(attributes, NULL, &list_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_list() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_list(attributes, REPRESENTATION_ATTRIBUTES_KEY_LIST, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_list() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_list_p
 * @since_tizen   3.0
 * @description   Test getting list value from attributes.
 */
int utc_iotcon_attributes_get_list_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_list_h list_temp;

	if (false == g_feature) {
		ret = iotcon_attributes_get_list(NULL, REPRESENTATION_ATTRIBUTES_KEY_LIST, &list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_list(attributes, REPRESENTATION_ATTRIBUTES_KEY_LIST, &list_temp);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_list() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_attributes_n
 * @since_tizen   3.0
 * @description   Test fail getting attributes value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_attributes_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_attributes_h attributes_temp;

	if (false == g_feature) {
		ret = iotcon_attributes_get_attributes(NULL, REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES, &attributes_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_attributes(NULL, REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES, &attributes_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_attributes(attributes, NULL, &attributes_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_attributes(attributes, REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}
	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_attributes_p
 * @since_tizen   3.0
 * @description   Test getting attributes value from attributes.
 */
int utc_iotcon_attributes_get_attributes_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_attributes_h attributes_temp;

	if (false == g_feature) {
		ret = iotcon_attributes_get_attributes(NULL, REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES, &attributes_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_attributes(attributes, REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES, &attributes_temp);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_is_null_n
 * @since_tizen   3.0
 * @description   Test fail getting value is null from attributes with invalid parameter.
 */
int utc_iotcon_attributes_is_null_n(void)
{
	bool is_null;
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_is_null(NULL, REPRESENTATION_ATTRIBUTES_KEY_NULL, &is_null);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_is_null(NULL, REPRESENTATION_ATTRIBUTES_KEY_NULL, &is_null);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_is_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_is_null(attributes, NULL, &is_null);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_is_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_is_null(attributes, REPRESENTATION_ATTRIBUTES_KEY_NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_is_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_is_null_p
 * @since_tizen   3.0
 * @description   Test getting value is null from attributes.
 */
int utc_iotcon_attributes_is_null_p(void)
{
	bool is_null;
	int ret;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_is_null(NULL, REPRESENTATION_ATTRIBUTES_KEY_NULL, &is_null);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_is_null(attributes, REPRESENTATION_ATTRIBUTES_KEY_NULL, &is_null);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_is_null() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	ICUTC_ASSERT_EQ(is_null, true);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_remove_n
 * @since_tizen   3.0
 * @description   Test fail removing a value from attributes with invalid parameter.
 */
int utc_iotcon_attributes_remove_n(void)
{
	int i;
	int ret;
	iotcon_attributes_h attributes = NULL;
	const char *keys[] = {
		REPRESENTATION_ATTRIBUTES_KEY_BOOL,
		REPRESENTATION_ATTRIBUTES_KEY_INT,
		REPRESENTATION_ATTRIBUTES_KEY_DOUBLE,
		REPRESENTATION_ATTRIBUTES_KEY_STR,
		REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES,
		REPRESENTATION_ATTRIBUTES_KEY_LIST,
	};

	if (false == g_feature) {
		ret = iotcon_attributes_remove(attributes, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_remove(attributes, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_remove() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	for (i = 0; i < sizeof(keys)/sizeof(char *); i++) {
		ret = iotcon_attributes_remove(NULL, keys[i]);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_attributes_remove(%s) Fail(%d)", keys[i], ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_remove_p
 * @since_tizen   3.0
 * @description   Test removing a value from attributes.
 */
int utc_iotcon_attributes_remove_p(void)
{
	int i;
	int ret;
	iotcon_attributes_h attributes = NULL;
	const char *keys[] = {
		REPRESENTATION_ATTRIBUTES_KEY_BOOL,
		REPRESENTATION_ATTRIBUTES_KEY_INT,
		REPRESENTATION_ATTRIBUTES_KEY_DOUBLE,
		REPRESENTATION_ATTRIBUTES_KEY_STR,
		REPRESENTATION_ATTRIBUTES_KEY_ATTRIBUTES,
		REPRESENTATION_ATTRIBUTES_KEY_LIST,
	};

	if (false == g_feature) {
		ret = iotcon_attributes_remove(attributes, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < sizeof(keys)/sizeof(char *); i++) {
		ret = iotcon_attributes_remove(attributes, keys[i]);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_attributes_remove(%s) Fail(%d)", keys[i], ret);
			iotcon_attributes_destroy(attributes);
			return 1;
		}
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_type_n
 * @since_tizen   3.0
 * @description   Test fail getting value type from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_type_n(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_type_e type;

	if (false == g_feature) {
		ret = iotcon_attributes_get_type(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_type(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &type);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_type() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_type(attributes, NULL, &type);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_type() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_type(attributes, REPRESENTATION_ATTRIBUTES_KEY_INT, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_type() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;

}

/**
 * @testcase      utc_iotcon_attributes_get_type_p
 * @since_tizen   3.0
 * @description   Test getting value type from attributes.
 */
int utc_iotcon_attributes_get_type_p(void)
{
	int ret;
	iotcon_attributes_h attributes;
	iotcon_type_e type;

	if (false == g_feature) {
		ret = iotcon_attributes_get_type(NULL, REPRESENTATION_ATTRIBUTES_KEY_INT, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_type(attributes, REPRESENTATION_ATTRIBUTES_KEY_INT, &type);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_type() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	ICUTC_ASSERT_EQ(type, IOTCON_TYPE_INT);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_add_child_n
 * @since_tizen   3.0
 * @description   Test fail adding a child to representation with invalid parameter.
 */
int utc_iotcon_representation_add_child_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_add_child(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_representation_create(&repr_child);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_add_child(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_remove_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr_child);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_add_child(NULL, repr_child);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_remove_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr_child);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr_child);
	iotcon_representation_destroy(repr);

	return 0;

}

/**
 * @testcase      utc_iotcon_representation_add_child_p
 * @since_tizen   3.0
 * @description   Test adding a child to representation.
 */
int utc_iotcon_representation_add_child_p(void)
{
	int i;
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_add_child(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_remove_child_n
 * @since_tizen   3.0
 * @description   Test fail removing a child to representation with invalid parameter.
 */
int utc_iotcon_representation_remove_child_n(void)
{
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_remove_child(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_representation_create(&repr_child);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_remove_child(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_remove_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr_child);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_remove_child(NULL, repr_child);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_remove_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr_child);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr_child);
	iotcon_representation_destroy(repr);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_remove_child_p
 * @since_tizen   3.0
 * @description   Test removing a child to representation.
 */
int utc_iotcon_representation_remove_child_p(void)
{
	int i;
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_remove_child(repr, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_remove_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_remove_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	iotcon_representation_destroy(repr);

	return 0;

}

static bool _representation_children_cb(iotcon_representation_h child, void *user_data)
{
	++(*((int *)user_data));
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_representation_foreach_children_n
 * @since_tizen   3.0
 * @description   Test fail iterating children from representation with invalid parameter.
 */
int utc_iotcon_representation_foreach_children_n(void)
{
	int i;
	int ret;
	int count = 0;
	iotcon_representation_h repr;
	iotcon_representation_h repr_child;

	if (false == g_feature) {
		ret = iotcon_representation_foreach_children(NULL, _representation_children_cb, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	ret = iotcon_representation_foreach_children(NULL, _representation_children_cb, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_foreach_children() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_foreach_children(repr, NULL, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_foreach_children() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_foreach_children_p
 * @since_tizen   3.0
 * @description   Test iterating children from representation.
 */
int utc_iotcon_representation_foreach_children_p(void)
{
	int i;
	int ret;
	int count = 0;
	iotcon_representation_h repr;
	iotcon_representation_h repr_child;

	if (false == g_feature) {
		ret = iotcon_representation_foreach_children(NULL, _representation_children_cb, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	ret = iotcon_representation_foreach_children(repr, _representation_children_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_foreach_children() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_child_count_n
 * @since_tizen   3.0
 * @description   Test fail getting children count from representation with invalid parameter.
 */
int utc_iotcon_representation_get_child_count_n(void)
{
	int i;
	int ret;
	unsigned int count = 0;
	iotcon_representation_h repr;
	iotcon_representation_h repr_child;

	if (false == g_feature) {
		ret = iotcon_representation_get_child_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	ret = iotcon_representation_get_child_count(NULL, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_child_count(repr, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	iotcon_representation_destroy(repr);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_child_count_p
 * @since_tizen   3.0
 * @description   Test getting children count from representation.
 */
int utc_iotcon_representation_get_child_count_p(void)
{
	int i;
	int ret;
	unsigned int count = 0;
	iotcon_representation_h repr;
	iotcon_representation_h repr_child;

	if (false == g_feature) {
		ret = iotcon_representation_get_child_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	ret = iotcon_representation_get_child_count(repr, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}
	iotcon_representation_destroy(repr);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_nth_child_n
 * @since_tizen   3.0
 * @description   Test fail getting nth child from representation with invalid parameter.
 */
int utc_iotcon_representation_get_nth_child_n(void)
{
	int i;
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_get_nth_child(repr, -1, &repr_child);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		iotcon_representation_h repr_child;
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	ret = iotcon_representation_get_nth_child(repr, -1, &repr_child);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_representation_get_nth_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	ret = iotcon_representation_get_nth_child(repr, REPRESENTATION_LIST_COUNT, &repr_child);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_representation_get_nth_child() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_get_nth_child(NULL, i, &repr_child);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_representation_get_nth_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}
	}
	iotcon_representation_destroy(repr);
	return 0;
}

/**
 * @testcase      utc_iotcon_representation_get_nth_child_p
 * @since_tizen   3.0
 * @description   Test getting nth child from representation.
 */
int utc_iotcon_representation_get_nth_child_p(void)
{
	int i;
	int ret;
	iotcon_representation_h repr = NULL;
	iotcon_representation_h repr_child = NULL;

	if (false == g_feature) {
		ret = iotcon_representation_get_nth_child(repr, -1, &repr_child);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_representation_create(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
		return 1;
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_create(&repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_create() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}

		ret = iotcon_representation_add_child(repr, repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr_child);
			iotcon_representation_destroy(repr);
			return 1;
		}
		iotcon_representation_destroy(repr_child);
	}

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_representation_get_nth_child(repr, i, &repr_child);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_representation_add_child() Fail(%d)", ret);
			iotcon_representation_destroy(repr);
			return 1;
		}
	}
	iotcon_representation_destroy(repr);
	return 0;
}

bool _representation_attributes_cb(iotcon_attributes_h attributes, const char *key, void *user_data)
{
	++(*((int *)user_data));
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_attributes_foreach_n
 * @since_tizen   3.0
 * @description   Test fail iterating keys from attributes with invalid parameter.
 */
int utc_iotcon_attributes_foreach_n(void)
{
	int ret;
	int count = 0;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_foreach(NULL, _representation_attributes_cb, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_foreach(NULL, _representation_attributes_cb, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_foreach() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_foreach(attributes, NULL, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_foreach() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_foreach_p
 * @since_tizen   3.0
 * @description   Test iterating keys from attributes.
 */
int utc_iotcon_attributes_foreach_p(void)
{
	int ret;
	int count = 0;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_foreach(NULL, _representation_attributes_cb, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_foreach(attributes, _representation_attributes_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_foreach() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	ICUTC_ASSERT_NEQ(count, 0);

	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_keys_count_n
 * @since_tizen   3.0
 * @description   Test fail getting keys count from attributes with invalid parameter.
 */
int utc_iotcon_attributes_get_keys_count_n(void)
{
	int ret;
	unsigned int count = 0;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_get_keys_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_keys_count(NULL, &count);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_keys_count() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	ret = iotcon_attributes_get_keys_count(attributes, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_attributes_get_keys_count() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}

/**
 * @testcase      utc_iotcon_attributes_get_keys_count_p
 * @since_tizen   3.0
 * @description   Test getting keys count from attributes.
 */
int utc_iotcon_attributes_get_keys_count_p(void)
{
	int ret;
	unsigned int count = 0;
	iotcon_attributes_h attributes;

	if (false == g_feature) {
		ret = iotcon_attributes_get_keys_count(NULL, &count);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_attributes(&attributes);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_get_keys_count(attributes, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_get_keys_count() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	return 0;
}


/**
 * @testcase      utc_iotcon_list_create_n
 * @since_tizen   3.0
 * @description   Test fail creating a list with invalid parameter.
 */
int utc_iotcon_list_create_n(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_create(IOTCON_TYPE_NONE, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_create(IOTCON_TYPE_NONE, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_TYPE);

	ret = iotcon_list_create(IOTCON_TYPE_ATTRIBUTES+1, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_TYPE);

	for (i = IOTCON_TYPE_INT; i <= IOTCON_TYPE_ATTRIBUTES; i++) {
		ret = iotcon_list_create(i, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	}
	return 0;
}

/**
 * @testcase      utc_iotcon_list_create_p
 * @since_tizen   3.0
 * @description   Test creating a list.
 */
int utc_iotcon_list_create_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_create(IOTCON_TYPE_NONE, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i = IOTCON_TYPE_INT; i <= IOTCON_TYPE_ATTRIBUTES; i++) {
		ret = iotcon_list_create(i, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
		iotcon_list_destroy(list);
	}
	return 0;
}

/**
 * @testcase      utc_iotcon_list_destroy_n
 * @since_tizen   3.0
 * @description   Test fail destroying a list with invalid parameter.
 */
int utc_iotcon_list_destroy_n(void)
{
	int ret;

	if (false == g_feature) {
		ret = iotcon_list_destroy(NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_destroy(NULL);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_destroy_p
 * @since_tizen   3.0
 * @description   Test destroying a list.
 */
int utc_iotcon_list_destroy_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_destroy(list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i = IOTCON_TYPE_INT; i <= IOTCON_TYPE_ATTRIBUTES; i++) {
		ret = iotcon_list_create(i, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

		ret = iotcon_list_destroy(list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);
	}
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_int_n
 * @since_tizen   3.0
 * @description   Test fail adding integer value to list with invalid parameter.
 */
int utc_iotcon_list_add_int_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_int(NULL, 0, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_add_int(NULL, 0, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_add_int_p
 * @since_tizen   3.0
 * @description   Test adding integer value to list.
 */
int utc_iotcon_list_add_int_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_int(NULL, 0, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_bool_n
 * @since_tizen   3.0
 * @description   Test fail adding boolean value to list with invalid parameter.
 */
int utc_iotcon_list_add_bool_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_bool(NULL, false, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_add_bool(NULL, false, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_add_bool_p
 * @since_tizen   3.0
 * @description   Test adding boolean value to list.
 */
int utc_iotcon_list_add_bool_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_bool(NULL, false, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_double_n
 * @since_tizen   3.0
 * @description   Test fail adding double value to list with invalid parameter.
 */
int utc_iotcon_list_add_double_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_double(NULL, 0.0, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_add_double(NULL, 0.0, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_double_p
 * @since_tizen   3.0
 * @description   Test adding double value to list.
 */
int utc_iotcon_list_add_double_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_double(NULL, 0.0, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_add_str_n
 * @since_tizen   3.0
 * @description   Test fail adding string value to list with invalid parameter.
 */
int utc_iotcon_list_add_str_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_str(NULL, "test", -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_add_str(NULL, "test", -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_str(list, NULL, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_str_p
 * @since_tizen   3.0
 * @description   Test adding string value to list.
 */
int utc_iotcon_list_add_str_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_str(NULL, "test", -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_byte_str_n
 * @since_tizen   3.0
 * @description   Test fail adding byte string value to list with invalid parameter.
 */
int utc_iotcon_list_add_byte_str_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	unsigned char byte_str[3] = {70, 71, 72};

	if (false == g_feature) {
		ret = iotcon_list_add_byte_str(NULL, byte_str, 3, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_add_byte_str(NULL, byte_str, 3, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_byte_str(list, NULL, 3, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_byte_str_p
 * @since_tizen   3.0
 * @description   Test adding byte string value to list.
 */
int utc_iotcon_list_add_byte_str_p(void)
{
	int ret;
	iotcon_list_h list = NULL;
	unsigned char byte_str[3] = {70, 71, 72};

	if (false == g_feature) {
		ret = iotcon_list_add_byte_str(NULL, byte_str, 3, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_byte_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;
}


/**
 * @testcase      utc_iotcon_list_add_list_n
 * @since_tizen   3.0
 * @description   Test fail adding list value to list with invalid parameter.
 */
int utc_iotcon_list_add_list_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	iotcon_list_h list_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_list(list, NULL, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list_temp);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_create() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_list(list, NULL, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list_temp);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_list(NULL, list, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_list() Fail(%d)", ret);
		iotcon_list_destroy(list_temp);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list_temp);
	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_add_list_p
 * @since_tizen   3.0
 * @description   Test adding list value to list.
 */
int utc_iotcon_list_add_list_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_list(list, NULL, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_add_attributes_n
 * @since_tizen   3.0
 * @description   Test fail adding attributes value to list with invalid parameter.
 */
int utc_iotcon_list_add_attributes_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_attributes(list, NULL, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_attributes_create(&attributes);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_attributes_create() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_attributes(list, NULL, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_add_attributes(NULL, attributes, -1);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_add_attributes() Fail(%d)", ret);
		iotcon_attributes_destroy(attributes);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_attributes_destroy(attributes);
	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_add_attributes_p
 * @since_tizen   3.0
 * @description   Test adding attributes value to list.
 */
int utc_iotcon_list_add_attributes_p(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_add_attributes(list, NULL, -1);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	iotcon_list_destroy(list);
	return 0;
}


/**
 * @testcase      utc_iotcon_list_get_nth_int_n
 * @since_tizen   3.0
 * @description   Test fail getting nth integer value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_int_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	int val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_int(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_int(list, -1, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_int(list, REPRESENTATION_LIST_COUNT, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_int(NULL, 0, &val);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_int(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_int_p
 * @since_tizen   3.0
 * @description   Test getting nth integer value from list.
 */
int utc_iotcon_list_get_nth_int_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	int val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_int(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_int(list, i, &val);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_int() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_bool_n
 * @since_tizen   3.0
 * @description   Test fail getting nth boolean value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_bool_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	bool val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_bool(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_bool(list, -1, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_bool(list, REPRESENTATION_LIST_COUNT, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_bool(NULL, 0, &val);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_bool(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_get_nth_bool_p
 * @since_tizen   3.0
 * @description   Test getting nth boolean value from list.
 */
int utc_iotcon_list_get_nth_bool_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	bool val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_bool(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_bool(list, i, &val);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_bool() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_double_n
 * @since_tizen   3.0
 * @description   Test fail getting nth double value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_double_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	double val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_double(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_double(list, -1, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_double(list, REPRESENTATION_LIST_COUNT, &val);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_double(NULL, 0, &val);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_double(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_get_nth_double_p
 * @since_tizen   3.0
 * @description   Test getting nth double value from list.
 */
int utc_iotcon_list_get_nth_double_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	double val;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_double(list, -1, &val);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_double(list, i, &val);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_double() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;

}

/**
 * @testcase      utc_iotcon_list_get_nth_str_n
 * @since_tizen   3.0
 * @description   Test fail getting nth string value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_str_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	char *str = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_str(list, -1, &str);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_str(list, -1, &str);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_str(list, REPRESENTATION_LIST_COUNT, &str);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_str(NULL, 0, &str);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_str(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_str_p
 * @since_tizen   3.0
 * @description   Test getting nth string value from list.
 */
int utc_iotcon_list_get_nth_str_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	char *str = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_str(list, -1, &str);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_str(list, i, &str);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_str() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_byte_str_n
 * @since_tizen   3.0
 * @description   Test fail getting nth byte string value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_byte_str_n(void)
{
	int ret;
	int len;
	iotcon_list_h list = NULL;
	unsigned char *byte_str = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_byte_str(list, -1, &byte_str, &len);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_byte_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_byte_str(list, -1, &byte_str, &len);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_byte_str(list, REPRESENTATION_LIST_COUNT, &byte_str, &len);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_byte_str(NULL, 0, &byte_str, &len);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_byte_str(list, 0, NULL, &len);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_byte_str(list, 0, &byte_str, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_byte_str_p
 * @since_tizen   3.0
 * @description   Test getting nth byte string value from list.
 */
int utc_iotcon_list_get_nth_byte_str_p(void)
{
	int i;
	int ret;
	int len;
	iotcon_list_h list = NULL;
	unsigned char *byte_str = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_byte_str(list, -1, &byte_str, &len);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_byte_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_byte_str(list, i, &byte_str, &len);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_byte_str() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}
/**
 * @testcase      utc_iotcon_list_get_nth_list_n
 * @since_tizen   3.0
 * @description   Test fail getting nth list value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_list_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	iotcon_list_h list_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_list(list, -1, &list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_list(list, -1, &list_temp);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_list(list, REPRESENTATION_LIST_COUNT, &list_temp);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_list(NULL, 0, &list_temp);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_list(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_list_p
 * @since_tizen   3.0
 * @description   Test getting nth list value from list.
 */
int utc_iotcon_list_get_nth_list_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	iotcon_list_h list_temp = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_list(list, -1, &list_temp);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_list(list, i, &list_temp);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_list() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_nth_attributes_n
 * @since_tizen   3.0
 * @description   Test fail getting nth attributes value from list with invalid parameter.
 */
int utc_iotcon_list_get_nth_attributes_n(void)
{
	int ret;
	iotcon_list_h list = NULL;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_attributes(list, -1, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_get_nth_attributes(list, -1, &attributes);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_attributes(list, REPRESENTATION_LIST_COUNT, &attributes);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_get_nth_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_attributes(NULL, 0, &attributes);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_nth_attributes(list, 0, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_nth_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}


/**
 * @testcase      utc_iotcon_list_get_nth_attributes_p
 * @since_tizen   3.0
 * @description   Test getting nth attributes value from list.
 */
int utc_iotcon_list_get_nth_attributes_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;
	iotcon_attributes_h attributes = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_nth_attributes(list, -1, &attributes);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_get_nth_attributes(list, i, &attributes);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_nth_attributes() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	iotcon_list_destroy(list);
	return 0;
}


/**
 * @testcase      utc_iotcon_list_remove_nth_n
 * @since_tizen   3.0
 * @description   Test fail removing nth value from list with invalid parameter.
 */
int utc_iotcon_list_remove_nth_n(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_remove_nth(list, REPRESENTATION_LIST_COUNT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_add_int(list, i, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	ret = iotcon_list_remove_nth(list, REPRESENTATION_LIST_COUNT);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_remove_nth() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_remove_nth(list, -1);
	if (IOTCON_ERROR_NO_DATA != ret) {
		ICUTC_ERR("iotcon_list_remove_nth() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_remove_nth(NULL, 0);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_remove_nth() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	return 0;
}

/**
 * @testcase      utc_iotcon_list_remove_nth_p
 * @since_tizen   3.0
 * @description   Test removing nth value from list.
 */
int utc_iotcon_list_remove_nth_p(void)
{
	int i;
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_remove_nth(list, REPRESENTATION_LIST_COUNT);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_add_int(list, i, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	for (i = REPRESENTATION_LIST_COUNT-1; 0 <= i; i--) {
		ret = iotcon_list_remove_nth(list, i);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_remove_nth() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}
	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_type_n
 * @since_tizen   3.0
 * @description   Test fail getting value type from list with invalid parameter.
 */
int utc_iotcon_list_get_type_n(void)
{
	int i;
	int ret;
	iotcon_type_e type;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_type(NULL, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_get_type(NULL, &type);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_type() Fail(%d)", ret);
		return 1;
	}

	for (i = IOTCON_TYPE_INT; i <= IOTCON_TYPE_ATTRIBUTES; i++) {
		ret = iotcon_list_create(i, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

		ret = iotcon_list_get_type(list, NULL);
		if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
			ICUTC_ERR("iotcon_list_get_type() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
		iotcon_list_destroy(list);
	}

	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_type_p
 * @since_tizen   3.0
 * @description   Test getting value type from list.
 */
int utc_iotcon_list_get_type_p(void)
{
	int i;
	int ret;
	iotcon_type_e type;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_type(NULL, &type);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	for (i = IOTCON_TYPE_INT; i <= IOTCON_TYPE_ATTRIBUTES; i++) {
		ret = iotcon_list_create(i, &list);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

		ret = iotcon_list_get_type(list, &type);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_get_type() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
		iotcon_list_destroy(list);
		ICUTC_ASSERT_EQ(type, i);
	}

	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_length_n
 * @since_tizen   3.0
 * @description   Test fail getting length from list with invalid parameter.
 */
int utc_iotcon_list_get_length_n(void)
{
	int ret;
	unsigned int length;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_length(NULL, &length);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	ret = iotcon_list_get_length(NULL, &length);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_length() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_get_length(list, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_get_length() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_get_length_p
 * @since_tizen   3.0
 * @description   Test getting length from list.
 */
int utc_iotcon_list_get_length_p(void)
{
	int i;
	int ret;
	unsigned int length;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_get_length(NULL, &length);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	for (i = 0; i < REPRESENTATION_LIST_COUNT; i++) {
		ret = iotcon_list_add_int(list, i, -1);
		if (IOTCON_ERROR_NONE != ret) {
			ICUTC_ERR("iotcon_list_add_int() Fail(%d)", ret);
			iotcon_list_destroy(list);
			return 1;
		}
	}

	ret = iotcon_list_get_length(list, &length);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_get_length() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(length, REPRESENTATION_LIST_COUNT);

	return 0;

}

static bool _representation_list_int_cb(int pos, int value, void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_int_n
 * @since_tizen   3.0
 * @description   Test fail iterating integer value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_int_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_int(NULL, _representation_list_int_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_int(NULL, _representation_list_int_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_int(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_DOUBLE, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_int(list, _representation_list_int_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;

}

/**
 * @testcase      utc_iotcon_list_foreach_int_p
 * @since_tizen   3.0
 * @description   Test iterating integer value from list.
 */
int utc_iotcon_list_foreach_int_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_int(NULL, _representation_list_int_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_int(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_int(list, _representation_list_int_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_int() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

static bool _representation_list_bool_cb(int pos, bool value, void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_bool_n
 * @since_tizen   3.0
 * @description   Test fail iterating boolean value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_bool_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_bool(NULL, _representation_list_bool_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_bool(NULL, _representation_list_bool_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_bool(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_bool(list, _representation_list_bool_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;

}

/**
 * @testcase      utc_iotcon_list_foreach_bool_p
 * @since_tizen   3.0
 * @description   Test iterating boolean value from list.
 */
int utc_iotcon_list_foreach_bool_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_bool(NULL, _representation_list_bool_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_bool(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_bool(list, _representation_list_bool_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_bool() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;

}

static bool _representation_list_double_cb(int pos, const double value, void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_double_n
 * @since_tizen   3.0
 * @description   Test fail iterating double value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_double_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_double(NULL, _representation_list_double_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_double(NULL, _representation_list_double_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_double(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_double(list, _representation_list_double_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;

}

/**
 * @testcase      utc_iotcon_list_foreach_double_p
 * @since_tizen   3.0
 * @description   Test iterating double value from list.
 */
int utc_iotcon_list_foreach_double_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_double(NULL, _representation_list_double_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_double(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_double(list, _representation_list_double_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_double() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;

}

static bool _representation_list_str_cb(int pos, const char *value, void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_str_n
 * @since_tizen   3.0
 * @description   Test fail iterating string value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_str_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_str(NULL, _representation_list_str_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_str(NULL, _representation_list_str_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_str(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_str(list, _representation_list_str_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_foreach_str_p
 * @since_tizen   3.0
 * @description   Test iterating string value from list.
 */
int utc_iotcon_list_foreach_str_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_str(NULL, _representation_list_str_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_str(list, _representation_list_str_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

static bool _representation_list_byte_str_cb(int pos, const unsigned char *value, int len,
		void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_byte_str_n
 * @since_tizen   3.0
 * @description   Test fail iterating byte string value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_byte_str_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_byte_str(NULL, _representation_list_byte_str_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_byte_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_byte_str(NULL, _representation_list_byte_str_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_byte_str(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_byte_str(list, _representation_list_byte_str_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_foreach_byte_str_p
 * @since_tizen   3.0
 * @description   Test iterating byte string value from list.
 */
int utc_iotcon_list_foreach_byte_str_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_byte_str(NULL, _representation_list_byte_str_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_byte_str(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_byte_str(list, _representation_list_byte_str_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_byte_str() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

static bool _representation_list_list_cb(int pos, iotcon_list_h value, void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_list_n
 * @since_tizen   3.0
 * @description   Test fail iterating list value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_list_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_list(NULL, _representation_list_list_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_list(NULL, _representation_list_list_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_list(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_list(list, _representation_list_list_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_foreach_list_p
 * @since_tizen   3.0
 * @description   Test iterating list value from list.
 */
int utc_iotcon_list_foreach_list_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_list(NULL, _representation_list_list_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_list(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_list(list, _representation_list_list_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_list() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);
	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;

}

static bool _representation_list_attributes_cb(int pos, iotcon_attributes_h value,
		void *user_data)
{
	(*((int *)user_data))++;
	return IOTCON_FUNC_CONTINUE;
}

/**
 * @testcase      utc_iotcon_list_foreach_attributes_n
 * @since_tizen   3.0
 * @description   Test fail iterating attributes value from list with invalid parameter.
 */
int utc_iotcon_list_foreach_attributes_n(void)
{
	int ret;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_attributes(NULL, _representation_list_attributes_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_attributes(NULL, _representation_list_attributes_cb, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	ret = iotcon_list_foreach_attributes(list, NULL, NULL);
	if (IOTCON_ERROR_INVALID_PARAMETER != ret) {
		ICUTC_ERR("iotcon_list_foreach_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}

	iotcon_list_destroy(list);
	ret = iotcon_list_create(IOTCON_TYPE_INT, &list);
	ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NONE);

	/* list is NULL */
	ret = iotcon_list_foreach_attributes(list, _representation_list_attributes_cb, NULL);
	if (IOTCON_ERROR_INVALID_TYPE != ret) {
		ICUTC_ERR("iotcon_list_foreach_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	return 0;
}

/**
 * @testcase      utc_iotcon_list_foreach_attributes_p
 * @since_tizen   3.0
 * @description   Test iterating attributes value from list.
 */
int utc_iotcon_list_foreach_attributes_p(void)
{
	int ret;
	int count = 0;
	iotcon_list_h list = NULL;

	if (false == g_feature) {
		ret = iotcon_list_foreach_attributes(NULL, _representation_list_attributes_cb, NULL);
		ICUTC_ASSERT_EQ(ret, IOTCON_ERROR_NOT_SUPPORTED);
		return 0;
	}

	ret = _representation_create_list_attributes(&list);
	ICUTC_ASSERT_EQ(ret, 0);

	ret = iotcon_list_foreach_attributes(list, _representation_list_attributes_cb, &count);
	if (IOTCON_ERROR_NONE != ret) {
		ICUTC_ERR("iotcon_list_foreach_attributes() Fail(%d)", ret);
		iotcon_list_destroy(list);
		return 1;
	}
	iotcon_list_destroy(list);

	ICUTC_ASSERT_EQ(count, REPRESENTATION_LIST_COUNT);

	return 0;
}

