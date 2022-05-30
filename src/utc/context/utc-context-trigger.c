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
#include "utc-context-common.h"
#include "utc-context-trigger-custom.h"
#include <context_trigger.h>
#include <string.h>
#include "tct_app_common.h"

//& set: Context
#define TRIGGER_FEATURE		"http://tizen.org/feature/contextual_trigger"
#define INVALID_OPERATOR "invalid_op"
#define EVENT_ARR_SIZE (sizeof(event_arr) / sizeof(event_arr[0]))
#define CONDITION_ARR_SIZE (sizeof(condition_arr) / sizeof(condition_arr[0]))
int event_arr[] = {CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_EVENT_BATTERY,
					CONTEXT_TRIGGER_EVENT_CHARGER, CONTEXT_TRIGGER_EVENT_GPS,
					CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_EVENT_USB,
					CONTEXT_TRIGGER_EVENT_WIFI, CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE,
					CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_EVENT_EMAIL,
					CONTEXT_TRIGGER_EVENT_MESSAGE, CONTEXT_TRIGGER_EVENT_CONTACTS,
					CONTEXT_TRIGGER_EVENT_ACTIVITY_STATIONARY, CONTEXT_TRIGGER_EVENT_ACTIVITY_WALKING,
					CONTEXT_TRIGGER_EVENT_ACTIVITY_RUNNING, CONTEXT_TRIGGER_EVENT_ACTIVITY_IN_VEHICLE,
					CONTEXT_TRIGGER_EVENT_PLACE};
int condition_arr[] = {CONTEXT_TRIGGER_CONDITION_TIME, CONTEXT_TRIGGER_CONDITION_BATTERY,
					CONTEXT_TRIGGER_CONDITION_CHARGER, CONTEXT_TRIGGER_CONDITION_GPS,
					CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_CONDITION_USB,
					CONTEXT_TRIGGER_CONDITION_WIFI, CONTEXT_TRIGGER_CONDITION_POWER_SAVING_MODE,
					CONTEXT_TRIGGER_CONDITION_CALL, CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY,
					CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_CONDITION_MUSIC_PLAYBACK_FREQUENCY,
					CONTEXT_TRIGGER_CONDITION_VIDEO_PLAYBACK_FREQUENCY};

static app_control_h app = NULL;

bool trigger_checked = false;
bool is_trigger_supported = false;

/**
* @function 		initialize_app_handle
* @description	 	Creates and initialize an app handle
* @parameter		NA
* @return 			NA
*/
bool initialize_app_handle(void)
{
	int err;

	TCT_UTCCheckInstalledApp(1, "org.tizen.testapplication");

	err = app_control_create(&app);
	if (err != APP_CONTROL_ERROR_NONE) {
		return false;
	}

	err = app_control_set_operation(app, APP_CONTROL_OPERATION_DEFAULT);
	if (err != APP_CONTROL_ERROR_NONE) {
		app_control_destroy(app);
		return false;
	}

	err = app_control_set_app_id (app, "org.tizen.testapplication");
	if (err != APP_CONTROL_ERROR_NONE) {
		app_control_destroy(app);
		return false;
	}

	return true;
}

/**
* @function 		release_app_handle
* @description	 	Destroy an app handle
* @parameter		NA
* @return 			NA
*/
void release_app_handle(void)
{
	app_control_destroy(app);
}

/**
 * @function		utc_context_trigger_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_context_trigger_startup(void)
{
	if (!trigger_checked) {
		system_info_get_platform_bool(TRIGGER_FEATURE, &is_trigger_supported);
		trigger_checked = true;
	}

	if (!is_trigger_supported)
		PRINT_INFO("Feature(%s) is not supported", TRIGGER_FEATURE);
}

/**
 * @function		utc_context_trigger_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_context_trigger_cleanup(void)
{
	int* enabled_arr = NULL;
	int enabled_count = 0;
	int* disabled_arr = NULL;
	int disabled_count = 0;
	int i = 0;

	if (!is_trigger_supported)
		return;

	context_trigger_get_own_rule_ids(&enabled_arr, &enabled_count, &disabled_arr, &disabled_count);

	for (i = 0; i < enabled_count; i++) {
		context_trigger_disable_rule(enabled_arr[i]);
		context_trigger_remove_rule(enabled_arr[i]);
	}

	for (i = 0; i < disabled_count; i++) {
		context_trigger_remove_rule(disabled_arr[i]);
	}

	if (enabled_arr) {
		free(enabled_arr);
		enabled_arr = NULL;
	}

	if (disabled_arr) {
		free(disabled_arr);
		disabled_arr = NULL;
	}

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
}

/**
 * @testcase		utc_context_trigger_add_rule_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_add_rule()
 */
int utc_context_trigger_add_rule_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_h rule2 = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h event2 = NULL;
	context_trigger_rule_entry_h condition = NULL;
	context_trigger_rule_entry_h condition2 = NULL;
	context_trigger_rule_entry_h condition3 = NULL;
	int rule_id;
	int rule_id2;

	if (!is_trigger_supported) {
		error = context_trigger_add_rule(rule, &rule_id);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition3);
	context_trigger_rule_entry_add_key(condition3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);
	context_trigger_rule_entry_add_comparison_string(condition3, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, "Mon");

	// Add rule
	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition);
	context_trigger_rule_add_entry(rule, condition3);
	context_trigger_rule_set_action_app_control(rule, app);

	error = context_trigger_add_rule(rule, &rule_id);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	assert_gt(rule_id, 0);

	// Add same rule and check rule id is same
	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule2);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &event2);
	context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	context_trigger_rule_entry_add_comparison_int(event2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &condition2);
	context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TYPE);
	context_trigger_rule_entry_add_comparison_string(condition2, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_add_entry(rule2, event2);
	context_trigger_rule_add_entry(rule2, condition3);
	context_trigger_rule_add_entry(rule2, condition2);
	context_trigger_rule_set_action_app_control(rule2, app);

	error = context_trigger_add_rule(rule2, &rule_id2);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	assert_eq(rule_id2, rule_id);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_entry_destroy(event2);
	context_trigger_rule_entry_destroy(condition2);
	context_trigger_rule_entry_destroy(condition3);
	context_trigger_rule_destroy(rule);
	context_trigger_rule_destroy(rule2);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_add_rule_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_add_rule()
 */
int utc_context_trigger_add_rule_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_LEVEL);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_add_entry(rule, condition);

	// Err: No event added
	error = context_trigger_add_rule(rule, &rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: No action added
	context_trigger_rule_add_entry(rule, event);

	error = context_trigger_add_rule(rule, &rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_set_action_app_control(rule, app);

	// Err: Null parameter
	error = context_trigger_add_rule(NULL, &rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Null parameter
	error = context_trigger_add_rule(rule, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_remove_rule_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_remove_rule()
 */
int utc_context_trigger_remove_rule_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);

	error = context_trigger_remove_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_remove_rule_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_remove_rule()
 */
int utc_context_trigger_remove_rule_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);
	context_trigger_enable_rule(rule_id);

	// Err: Invalid parameter
	error = context_trigger_remove_rule(-1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_remove_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_ENABLED);

	// Err: Non-existent rule id
	error = context_trigger_remove_rule(rule_id + 1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST);

	context_trigger_disable_rule(rule_id);
	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_enable_rule_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_enable_rule()
 */
int utc_context_trigger_enable_rule_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TYPE);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_HEADSET);

	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);

	error = context_trigger_enable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_disable_rule(rule_id);
	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_enable_rule_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_enable_rule()
 */
int utc_context_trigger_enable_rule_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);

	// Err: Invalid parameter
	error = context_trigger_enable_rule(-1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Non-existent rule id
	error = context_trigger_enable_rule(rule_id+1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST);

	// Err: Already enabled
	context_trigger_enable_rule(rule_id);

	error = context_trigger_enable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_ENABLED);

	context_trigger_disable_rule(rule_id);
	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_disable_rule_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_disable_rule()
 */
int utc_context_trigger_disable_rule_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);
	context_trigger_enable_rule(rule_id);

	error = context_trigger_disable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_disable_rule_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_disable_rule()
 */
int utc_context_trigger_disable_rule_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);
	context_trigger_enable_rule(rule_id);

	// Err: Invalid parameter
	error = context_trigger_disable_rule(-1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Non-existent rule id
	error = context_trigger_disable_rule(rule_id + 1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST);

	// Err: Already disabled rule
	context_trigger_disable_rule(rule_id);

	error = context_trigger_disable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_NOT_ENABLED);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_get_own_rule_ids_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_get_own_rule_ids_p
 */
int utc_context_trigger_get_own_rule_ids_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule1 = NULL;
	context_trigger_rule_h rule2 = NULL;
	context_trigger_rule_entry_h event1 = NULL;
	context_trigger_rule_entry_h event2 = NULL;
	int rule_id1;
	int rule_id2;
	int* enabled_arr = NULL;
	int enabled_count;
	int* disabled_arr = NULL;
	int disabled_count;

	if (!is_trigger_supported) {
		error = context_trigger_get_own_rule_ids(&enabled_arr, &enabled_count, &disabled_arr, &disabled_count);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	error = context_trigger_get_own_rule_ids(&enabled_arr, &enabled_count, &disabled_arr, &disabled_count);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	assert_eq(enabled_count, 0);
	assert_eq(disabled_count, 0);

	if (enabled_arr) {
		free(enabled_arr);
		enabled_arr = NULL;
	}

	if (disabled_arr) {
		free(disabled_arr);
		disabled_arr = NULL;
	}

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule1);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
	context_trigger_rule_entry_add_key(event1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule1, event1);
	context_trigger_rule_set_action_app_control(rule1, app);
	context_trigger_add_rule(rule1, &rule_id1);
	context_trigger_enable_rule(rule_id1);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule2);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
	context_trigger_rule_add_entry(rule2, event2);
	context_trigger_rule_set_action_app_control(rule2, app);
	context_trigger_add_rule(rule2, &rule_id2);

	error = context_trigger_get_own_rule_ids(&enabled_arr, &enabled_count, &disabled_arr, &disabled_count);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	assert_eq(enabled_count, 1);
	assert_eq(disabled_count, 1);

	context_trigger_disable_rule(rule_id1);
	context_trigger_remove_rule(rule_id1);
	context_trigger_remove_rule(rule_id2);
	context_trigger_rule_entry_destroy(event1);
	context_trigger_rule_entry_destroy(event2);
	context_trigger_rule_destroy(rule1);
	context_trigger_rule_destroy(rule2);
	release_app_handle();

	assert(enabled_arr);
	assert(disabled_arr);

	assert_eq(enabled_arr[0], rule_id1);
	assert_eq(disabled_arr[0], rule_id2);

	free(enabled_arr);
	enabled_arr = NULL;

	free(disabled_arr);
	disabled_arr = NULL;

	return 0;
}

/**
 * @testcase		utc_context_trigger_get_own_rule_ids_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_get_own_rule_ids()
 */
int utc_context_trigger_get_own_rule_ids_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	int* arr1;
	int count1;
	int* arr2;
	int count2;

	// Err: NULL paremeter
	error = context_trigger_get_own_rule_ids(&arr1, NULL, NULL, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(NULL, &count1, NULL, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(NULL, NULL, &arr2, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(NULL, NULL, NULL, &count2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(&arr1, &count1, &arr2, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(&arr1, &count1, NULL, &count2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(NULL, &count1, &arr2, &count2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_get_own_rule_ids(&arr1, NULL, &arr2, &count2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_get_rule_by_id_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_get_rule_by_id()
 */
int utc_context_trigger_get_rule_by_id_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;
	context_trigger_rule_h rule_result = NULL;
	const char* description = "At 15:00";
	char* des_result = NULL;

	if (!is_trigger_supported) {
		error = context_trigger_get_rule_by_id(rule_id, &rule_result);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_set_description(rule, description);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	error = context_trigger_add_rule(rule, &rule_id);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_get_rule_by_id(rule_id, &rule_result);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_get_description(rule_result, &des_result);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	context_trigger_rule_destroy(rule_result);
	release_app_handle();

	assert(des_result);
	assert(!strcmp(des_result, description));

	free(des_result);
	des_result = NULL;

	return 0;
}

/**
 * @testcase		utc_context_trigger_get_rule_by_id_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_get_rule_by_id()
 */
int utc_context_trigger_get_rule_by_id_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;
	context_trigger_rule_h rule_result = NULL;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	// Err: Invalid parameter
	error = context_trigger_get_rule_by_id(0, &rule_result);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);

	// Err: Invalid parameter
	error = context_trigger_get_rule_by_id(rule_id, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Non-existent rule id
	error = context_trigger_get_rule_by_id(rule_id + 1, &rule_result);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_create_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_create()
 */
int utc_context_trigger_rule_create_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule1 = NULL;
	context_trigger_rule_h rule2 = NULL;

	error = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_destroy(rule1);
	context_trigger_rule_destroy(rule2);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_create_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_create()
 */
int utc_context_trigger_rule_create_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;

	// Err: Invalid parameter
	error = context_trigger_rule_create(-1, &rule);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_destroy()
 */
int utc_context_trigger_rule_destroy_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule1 = NULL;
	context_trigger_rule_h rule2 = NULL;

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule1);
	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule2);

	error = context_trigger_rule_destroy(rule1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_destroy(rule2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case or context_trigger_rule_destroy()
 */
int utc_context_trigger_rule_destroy_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Invalid parameter
	context_trigger_rule_h rule = NULL;
	error = context_trigger_rule_destroy(rule);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_add_entry_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_add_entry
 */
int utc_context_trigger_rule_add_entry_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h e_call = NULL;
	context_trigger_rule_entry_h c_wifi = NULL;
	context_trigger_rule_entry_h c_comm = NULL;

	bool call_supported = false;
	bool wifi_supported = false;
	bool comm_supported = false;

	if (!is_trigger_supported) {
		error = context_trigger_rule_add_entry(rule, c_wifi);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

		error = context_trigger_rule_add_entry(rule, e_call);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

		error = context_trigger_rule_add_entry(rule, c_comm);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

		return 0;
	}

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CALL, &call_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_WIFI, &wifi_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);
	if (!(call_supported && wifi_supported && comm_supported)) {
		PRINT_INFO("Not supported item used. Skip test. (Call %d, Wifi %d, CommunicationFreq %d)", call_supported, wifi_supported, comm_supported);
		return 0;
	}

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_call);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_WIFI, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_wifi);
	context_trigger_rule_entry_add_key(c_wifi, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_STATE);
	context_trigger_rule_entry_add_comparison(c_wifi, CONTEXT_TRIGGER_STATE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_STATE);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_comm);
	context_trigger_rule_entry_add_option(c_comm, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_ADDRESS);
	context_trigger_rule_entry_add_key(c_comm, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
	context_trigger_rule_entry_add_comparison_int(c_comm, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_LESS_THAN, 6);

	// C -> E -> C
	error = context_trigger_rule_add_entry(rule, c_wifi);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_add_entry(rule, e_call);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_add_entry(rule, c_comm);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(e_call);
	context_trigger_rule_entry_destroy(c_wifi);
	context_trigger_rule_entry_destroy(c_comm);
	context_trigger_rule_destroy(rule);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_add_entry_n1
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_add_entry()
 */
int utc_context_trigger_rule_add_entry_n1(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h e_headphone = NULL;
	context_trigger_rule_entry_h e_battery = NULL;
	context_trigger_rule_entry_h e_place = NULL;
	context_trigger_rule_entry_h c_comm = NULL;
	context_trigger_rule_entry_h c_comm2 = NULL;

	bool hdp_supported = false;
	bool batt_supported = false;
	bool place_supported = false;
	bool comm_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, &hdp_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_BATTERY, &batt_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_PLACE, &place_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_headphone);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_battery);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_place);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_comm);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_comm2);

	// Err: Invalid parameter
	error = context_trigger_rule_add_entry(NULL, e_headphone);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);
	error = context_trigger_rule_add_entry(rule, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Event already added
	if (!is_trigger_supported || (hdp_supported && batt_supported)) {
		error = context_trigger_rule_add_entry(rule, e_headphone);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		error = context_trigger_rule_add_entry(rule, e_battery);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	// Err: Mandatory option not added (Event)
	if (!is_trigger_supported || place_supported) {
		error = context_trigger_rule_add_entry(rule, e_place);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	if (!is_trigger_supported || comm_supported) {
		// Err: Mandatory option not added (Condition)
		context_trigger_rule_entry_add_option_string(c_comm, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_WEEKDAY);
		context_trigger_rule_entry_add_key(c_comm, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		context_trigger_rule_entry_add_comparison_int(c_comm, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_LESS_THAN, 6);
		error = context_trigger_rule_add_entry(rule, c_comm);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Condition without comparison data (key & value not added)
		context_trigger_rule_entry_add_option_string(c_comm2, CONTEXT_TRIGGER_ADDRESS, "010-1111-2222");
		context_trigger_rule_entry_add_option_string(c_comm2, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_WEEKDAY);
		error = context_trigger_rule_add_entry(rule, c_comm2);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Condition without comparison data (only key added)
		context_trigger_rule_entry_add_key(c_comm2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		error = context_trigger_rule_add_entry(rule, c_comm2);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	context_trigger_rule_entry_destroy(e_headphone);
	context_trigger_rule_entry_destroy(e_battery);
	context_trigger_rule_entry_destroy(e_place);
	context_trigger_rule_entry_destroy(c_comm);
	context_trigger_rule_entry_destroy(c_comm2);
	context_trigger_rule_destroy(rule);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_add_entry_n2
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_add_entry()
 */
int utc_context_trigger_rule_add_entry_n2(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	bool call_supported = false;
	bool wifi_supported = false;
	bool hdp_supported = false;
	bool comm_supported = false;
	bool chgr_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CALL, &call_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_WIFI, &wifi_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_HEADPHONE, &hdp_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CHARGER, &chgr_supported);

	// Referntial condition test (1)
	if (!is_trigger_supported || (call_supported && wifi_supported)) {
		context_trigger_rule_h rule2 = NULL;
		context_trigger_rule_entry_h e_call = NULL;
		context_trigger_rule_entry_h c_wifi = NULL;

		context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule2);
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_call);
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_WIFI, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_wifi);
		context_trigger_rule_add_entry(rule2, e_call);

		// Err: Invalid referential comparison key (attribute data not provided)
		context_trigger_rule_entry_add_key(c_wifi, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_BSSID);
		context_trigger_rule_entry_add_comparison(c_wifi, CONTEXT_TRIGGER_BSSID, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_EVENT);
		error = context_trigger_rule_add_entry(rule2, c_wifi);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(e_call);
		context_trigger_rule_entry_destroy(c_wifi);
		context_trigger_rule_destroy(rule2);
	} else {
		PRINT_INFO("Not supported item included. Skip test (1/4)");
	}

	// Referntial condition test (2)
	if (!is_trigger_supported || (call_supported && hdp_supported)) {
		context_trigger_rule_h rule3 = NULL;
		context_trigger_rule_entry_h e_call2 = NULL;
		context_trigger_rule_entry_h c_headphone = NULL;

		context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule3);
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_call2);
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_headphone);
		context_trigger_rule_add_entry(rule3, e_call2);

		// Err: Referential comparison data type not matched
		context_trigger_rule_entry_add_key(c_headphone, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
		context_trigger_rule_entry_add_comparison(c_headphone, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MEDIUM);
		error = context_trigger_rule_add_entry(rule3, c_headphone);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(e_call2);
		context_trigger_rule_entry_destroy(c_headphone);
		context_trigger_rule_destroy(rule3);
	} else {
		PRINT_INFO("Not supported item included. Skip test (2/4)");
	}

	// Referntial condition test (3)
	if (!is_trigger_supported || (call_supported && comm_supported)) {
		context_trigger_rule_h rule4 = NULL;
		context_trigger_rule_entry_h e_call3 = NULL;
		context_trigger_rule_entry_h c_comm3 = NULL;

		context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule4);
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_call3);
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_comm3);
		context_trigger_rule_add_entry(rule4, e_call3);

		// Err: Invalid referential option key (attribute data not provided)
		context_trigger_rule_entry_add_option(c_comm3, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_APP_ID);
		context_trigger_rule_entry_add_key(c_comm3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		context_trigger_rule_entry_add_comparison_int(c_comm3, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_LESS_THAN, 6);
		error = context_trigger_rule_add_entry(rule4, c_comm3);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(e_call3);
		context_trigger_rule_entry_destroy(c_comm3);
		context_trigger_rule_destroy(rule4);
	} else {
		PRINT_INFO("Not supported item included. Skip test (3/4)");
	}

	// Referntial condition test (4)
	if (!is_trigger_supported || (chgr_supported && comm_supported)) {
		context_trigger_rule_h rule5 = NULL;
		context_trigger_rule_entry_h e_charger = NULL;
		context_trigger_rule_entry_h c_comm4 = NULL;

		context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &rule5);
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CHARGER, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &e_charger);
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &c_comm4);
		context_trigger_rule_add_entry(rule5, e_charger);

		// Err: Referential option data type not matched
		context_trigger_rule_entry_add_option(c_comm4, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_IS_CONNECTED);
		context_trigger_rule_entry_add_key(c_comm4, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		context_trigger_rule_entry_add_comparison_int(c_comm4, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_LESS_THAN, 6);
		error = context_trigger_rule_add_entry(rule5, c_comm4);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(e_charger);
		context_trigger_rule_entry_destroy(c_comm4);
		context_trigger_rule_destroy(rule5);
	} else {
		PRINT_INFO("Not supported item included. Skip test (4/4)");
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_action_app_control_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_set_action_app_control()
 */
int utc_context_trigger_rule_set_action_app_control_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TYPE);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_HEADSET);

	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition);

	error = context_trigger_rule_set_action_app_control(rule, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_add_rule(rule, &rule_id);

	error = context_trigger_enable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_disable_rule(rule_id);
	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_action_app_control_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_set_action_app_control()
 */
int utc_context_trigger_rule_set_action_app_control_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	// Err: Invalid parameter
	error = context_trigger_rule_set_action_app_control(NULL, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	context_trigger_rule_h rule = NULL;
	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);

	app_control_h invalid_app = NULL;
	error = context_trigger_rule_set_action_app_control(rule, invalid_app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
	// Err: Invalid app id
	app_control_create(&invalid_app);
	app_control_set_operation(invalid_app, APP_CONTROL_OPERATION_DEFAULT);
	app_control_set_app_id (invalid_app, "invalid_app_id");

	error = context_trigger_rule_set_action_app_control(rule, invalid_app);
	app_control_destroy(invalid_app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: Service application
	app_control_h service_app;
	app_control_create(&service_app);
	app_control_set_operation(service_app, APP_CONTROL_OPERATION_DEFAULT);
	app_control_set_app_id (service_app, "org.tizen.testservice");

	error = context_trigger_rule_set_action_app_control(rule, service_app);
	app_control_destroy(service_app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
#endif	//MOBILE

	// Err: Action already added
	error = context_trigger_rule_set_action_app_control(rule, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_set_action_app_control(rule, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_action_notification_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_set_action_notification()
 */
int utc_context_trigger_rule_set_action_notification_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	int rule_id;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TYPE);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
	context_trigger_rule_entry_add_comparison_string(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_HEADSET);

	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition);

	error = context_trigger_rule_set_action_notification(rule, "Notification title", "Notification content", NULL, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_add_rule(rule, &rule_id);

	error = context_trigger_enable_rule(rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_disable_rule(rule_id);
	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_action_notification_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_set_action_notification()
 */
int utc_context_trigger_rule_set_action_notification_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	// Err: Invalid parameter
	error = context_trigger_rule_set_action_notification(NULL, "Notification title", "Notification content", NULL, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	context_trigger_rule_h rule = NULL;
	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);

	error = context_trigger_rule_set_action_notification(rule, NULL, "Notification content", NULL, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_set_action_notification(rule, "Notification title", NULL, NULL, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

#if defined(MOBILE) || defined(TIZENIOT)
	// Err: Invalid app id
	app_control_h invalid_app = NULL;
	app_control_create(&invalid_app);
	app_control_set_operation(invalid_app, APP_CONTROL_OPERATION_DEFAULT);
	app_control_set_app_id (invalid_app, "invalid_app_id");

	error = context_trigger_rule_set_action_app_control(rule, invalid_app);
	app_control_destroy(invalid_app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
#endif	//MOBILE

	// Err: Action already added
	error = context_trigger_rule_set_action_notification(rule, "Notification title", "Notification content", NULL, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_set_action_notification(rule, "Notification title", "Notification content", NULL, app);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_description_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_set_description()
 */
int utc_context_trigger_rule_set_description_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);

	error = context_trigger_rule_set_description(rule, "Rule description test");
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_destroy(rule);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_set_description_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_set_description()
 */
int utc_context_trigger_rule_set_description_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Invalid parameter
	error = context_trigger_rule_set_description(NULL, "Rule description test");
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_get_description_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_get_description()
 */
int utc_context_trigger_rule_get_description_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;
	context_trigger_rule_h rule_result = NULL;
	const char* description = "At 15:00";
	char* des_result = NULL;

	if (!is_trigger_supported) {
		error = context_trigger_rule_get_description(rule_result, &des_result);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_set_description(rule, description);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);
	context_trigger_get_rule_by_id(rule_id, &rule_result);

	error = context_trigger_rule_get_description(rule_result, &des_result);
	assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	context_trigger_rule_destroy(rule_result);
	release_app_handle();

	assert(des_result);
	assert(!strcmp(des_result, description));

	free(des_result);
	des_result = NULL;

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_get_description_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_get_description()
 */
int utc_context_trigger_rule_get_description_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	int rule_id;
	context_trigger_rule_h rule_result = NULL;
	const char* description = "At 15:00";
	char* des_result = NULL;

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_set_description(rule, description);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 15 * 60);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_set_action_app_control(rule, app);
	context_trigger_add_rule(rule, &rule_id);
	context_trigger_get_rule_by_id(rule_id, &rule_result);

	// Err: Invalid parameter
	error = context_trigger_rule_get_description(NULL, &des_result);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_get_description(rule_result, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_destroy(rule);
	context_trigger_rule_destroy(rule_result);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_event_create_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_event_create()
 */
int utc_context_trigger_rule_event_create_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	int i = 0;

	for (i = 0; i < EVENT_ARR_SIZE; i++) {
		context_trigger_rule_entry_h event1 = NULL;
		context_trigger_rule_entry_h event2 = NULL;

		if (!is_trigger_supported) {
			error = context_trigger_rule_event_create(event_arr[i], CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

			error = context_trigger_rule_event_create(event_arr[i], CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &event2);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

			continue;
		}

		bool supported = true;
		error = context_trigger_rule_event_is_supported(event_arr[i], &supported);
		if (error == CONTEXT_TRIGGER_ERROR_NONE && supported == false) {
			PRINT_INFO("Event(%x) is not supported", event_arr[i]);
			continue;
		}

		error = context_trigger_rule_event_create(event_arr[i], CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

		error = context_trigger_rule_event_create(event_arr[i], CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &event2);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(event1);
		context_trigger_rule_entry_destroy(event2);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_event_create_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_event_create()
 */
int utc_context_trigger_rule_event_create_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;

	// Err: Invalid parameter
	error = context_trigger_rule_event_create(-1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, -1, &event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_event_is_supported_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_event_is_supported()
 */
int utc_context_trigger_rule_event_is_supported_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	bool supported;
	int i = 0;

	for (i = 0; i < EVENT_ARR_SIZE; i++) {
		if (!is_trigger_supported) {
			error = context_trigger_rule_event_is_supported(event_arr[i], &supported);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
			continue;
		}

		error = context_trigger_rule_event_is_supported(event_arr[i], &supported);
		if (!supported)
			PRINT_INFO("Event(%x) is not supported", event_arr[i]);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_event_is_supported_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_event_is_supported()
 */
int utc_context_trigger_rule_event_is_supported_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	bool supported;

	// Err: Invalid parameter
	error = context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_event_is_supported(-1, &supported);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_condition_create_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_condition_create()
 */
int utc_context_trigger_rule_condition_create_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	int i = 0;

	for (i = 0; i < CONDITION_ARR_SIZE; i++) {
		context_trigger_rule_entry_h condition1 = NULL;
		context_trigger_rule_entry_h condition2 = NULL;

		if (!is_trigger_supported) {
			error = context_trigger_rule_condition_create(condition_arr[i], CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

			error = context_trigger_rule_condition_create(condition_arr[i], CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &condition2);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

			continue;
		}

		bool supported = true;
		error = context_trigger_rule_condition_is_supported(condition_arr[i], &supported);
		if (error == CONTEXT_TRIGGER_ERROR_NONE && supported == false) {
			PRINT_INFO("Condition(%x) is not supported", condition_arr[i]);
			continue;
		}

		error = context_trigger_rule_condition_create(condition_arr[i], CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

		error = context_trigger_rule_condition_create(condition_arr[i], CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &condition2);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(condition1);
		context_trigger_rule_entry_destroy(condition2);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_condition_create_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_condition_create()
 */
int utc_context_trigger_rule_condition_create_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h condition = NULL;

	// Err: Invalid parameter
	error = context_trigger_rule_condition_create(-1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, -1, &condition);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_condition_is_supported_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_condition_is_supported()
 */
int utc_context_trigger_rule_condition_is_supported_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	bool supported;
	int i = 0;

	for (i = 0; i < CONDITION_ARR_SIZE; i++) {
		if (!is_trigger_supported) {
			error = context_trigger_rule_condition_is_supported(condition_arr[i], &supported);
			assert_eq(error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);
			continue;
		}

		error = context_trigger_rule_condition_is_supported(condition_arr[i], &supported);
		if (!supported)
			PRINT_INFO("Condition(%x) is not supported", condition_arr[i]);
		assert_eq(error, CONTEXT_TRIGGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_condition_is_supported_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_condition_is_supported()
 */
int utc_context_trigger_rule_condition_is_supported_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	bool supported;

	// Err: Invalid parameter
	error = context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_HEADPHONE, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_condition_is_supported(-1, &supported);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_destroy_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_destroy()
 */
int utc_context_trigger_rule_entry_destroy_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;

	bool hdp_supported;
	bool btr_supported;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, &hdp_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_BATTERY, &btr_supported);

	if (hdp_supported) {
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

		error = context_trigger_rule_entry_destroy(event);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	}

	if (btr_supported) {
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);

		error = context_trigger_rule_entry_destroy(condition);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_destroy_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_destroy()
 */
int utc_context_trigger_rule_entry_destroy_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Invalid parameter
	context_trigger_rule_entry_h event = NULL;
	error = context_trigger_rule_entry_destroy(event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_key_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_key()
 */
int utc_context_trigger_rule_entry_add_key_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;

	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

	error = context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(event);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_key_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_key()
 */
int utc_context_trigger_rule_entry_add_key_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;

	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

	// Err: Invalid parameter
	error = context_trigger_rule_entry_add_key(NULL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_key(event, -1, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Invalid comparison key
	error = context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_ENABLED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: Key already added
	error = context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	error = context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_entry_destroy(event);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_int_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_comparison()
 */
int utc_context_trigger_rule_entry_add_comparison_int_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	bool etime_supported = false;
	bool ctime_supported = false;
	bool chgr_supported = false;
	bool btr_supported = false;
	bool psm_supported = false;
	bool app_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_TIME, &etime_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_TIME, &ctime_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CHARGER, &chgr_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_BATTERY, &btr_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE, &psm_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, &app_supported);

	if (!is_trigger_supported || etime_supported) {
		context_trigger_rule_entry_h event1 = NULL;
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
		context_trigger_rule_entry_add_key(event1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);

		error = context_trigger_rule_entry_add_comparison_int(event1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 16 * 60);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(event1);
	} else {
		PRINT_INFO("Not supported. Skip Test(1/6)");
	}

	if (!is_trigger_supported || ctime_supported) {
		context_trigger_rule_entry_h condition1 = NULL;
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
		context_trigger_rule_entry_add_key(condition1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
		context_trigger_rule_entry_add_key(condition1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_DAY_OF_MONTH);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 1000);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_DAY_OF_MONTH, CONTEXT_TRIGGER_EQUAL_TO, 20);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(condition1);
	} else {
		PRINT_INFO("Not supported. Skip Test(2/6)");
	}

	if (!is_trigger_supported || chgr_supported) {
		context_trigger_rule_entry_h event2 = NULL;
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CHARGER, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
		context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);

		error = context_trigger_rule_entry_add_comparison_int(event2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(event2);
	} else {
		PRINT_INFO("Not supported. Skip Test(3/6)");
	}

	if (!is_trigger_supported || btr_supported) {
		context_trigger_rule_entry_h event3 = NULL;
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event3);
		context_trigger_rule_entry_add_key(event3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CHARGING);

		error = context_trigger_rule_entry_add_comparison_int(event3, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(event3);
	} else {
		PRINT_INFO("Not supported. Skip Test(4/6)");
	}

	if (!is_trigger_supported || psm_supported) {
		context_trigger_rule_entry_h event4 = NULL;
		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event4);
		context_trigger_rule_entry_add_key(event4, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_ENABLED);

		error = context_trigger_rule_entry_add_comparison_int(event4, CONTEXT_TRIGGER_IS_ENABLED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TRUE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(event4);
	} else {

		PRINT_INFO("Not supported. Skip Test(5/6)");
	}

	if (!is_trigger_supported || app_supported) {
		context_trigger_rule_entry_h condition2 = NULL;
		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
		context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TOTAL_COUNT);

		error = context_trigger_rule_entry_add_comparison_int(condition2, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_EQUAL_TO, 1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		error = context_trigger_rule_entry_add_comparison_int(condition2, CONTEXT_TRIGGER_TOTAL_COUNT, CONTEXT_TRIGGER_EQUAL_TO, 10);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

		context_trigger_rule_entry_destroy(condition2);
	} else {
		PRINT_INFO("Not supported. Skip Test(6/6)");
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_int_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_comparison()
 */
int utc_context_trigger_rule_entry_add_comparison_int_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	bool etime_supported = false;
	bool ctime_supported = false;
	bool chgr_supported = false;
	bool btr_supported= false;
	bool psm_supported = false;
	bool app_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_TIME, &etime_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_TIME, &ctime_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CHARGER, &chgr_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_BATTERY, &btr_supported);
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE, &psm_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, &app_supported);

	if (!is_trigger_supported || etime_supported) {
		context_trigger_rule_entry_h event = NULL;

		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

		// Err: Key not added
		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 16 * 60);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NO_DATA);

		context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);

		// Err: Invalid parameter
		error = context_trigger_rule_entry_add_comparison_int(NULL, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_comparison_int(event, NULL, CONTEXT_TRIGGER_EQUAL_TO, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, NULL, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		// Err: Invalid operator
		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, INVALID_OPERATOR, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Duplicated operator & value
		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Invalid comparison value type
		context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);
		error = context_trigger_rule_entry_add_comparison_int(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, 16);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event);
	} else {
		PRINT_INFO("Not supported item. Skip test(1/7)");
	}

	// Err: Invalid comparison value
	if (!is_trigger_supported || etime_supported) {
		context_trigger_rule_entry_h event1 = NULL;

		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
		context_trigger_rule_entry_add_key(event1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);

		error = context_trigger_rule_entry_add_comparison_int(event1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(event1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 1440);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event1);
	} else {
		PRINT_INFO("Not supported item. Skip test(2/7)");
	}

	if (!is_trigger_supported || ctime_supported) {
		context_trigger_rule_entry_h condition1 = NULL;

		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
		context_trigger_rule_entry_add_key(condition1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 1440);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_DAY_OF_MONTH, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(condition1, CONTEXT_TRIGGER_DAY_OF_MONTH, CONTEXT_TRIGGER_EQUAL_TO, 32);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(condition1);
	} else {
		PRINT_INFO("Not supported item. Skip test(3/7)");
	}

	if (!is_trigger_supported || chgr_supported) {
		context_trigger_rule_entry_h event2 = NULL;

		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CHARGER, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
		context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);

		error = context_trigger_rule_entry_add_comparison_int(event2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(event2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, 2);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event2);
	} else {
		PRINT_INFO("Not supported item. Skip test(4/7)");
	}

	if (!is_trigger_supported || btr_supported) {
		context_trigger_rule_entry_h event3 = NULL;

		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event3);
		context_trigger_rule_entry_add_key(event3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CHARGING);

		error = context_trigger_rule_entry_add_comparison_int(event3, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(event3, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, 2);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event3);
	} else {
		PRINT_INFO("Not supported item. Skip test(5/7)");
	}

	if (!is_trigger_supported || psm_supported) {
		context_trigger_rule_entry_h event4 = NULL;

		context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event4);
		context_trigger_rule_entry_add_key(event4, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_ENABLED);

		error = context_trigger_rule_entry_add_comparison_int(event4, CONTEXT_TRIGGER_IS_ENABLED, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(event4, CONTEXT_TRIGGER_IS_ENABLED, CONTEXT_TRIGGER_EQUAL_TO, 2);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event4);
	} else {
		PRINT_INFO("Not supported item. Skip test(6/7)");
	}

	if (!is_trigger_supported || app_supported) {
		context_trigger_rule_entry_h condition2 = NULL;

		context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
		context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
		context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TOTAL_COUNT);

		error = context_trigger_rule_entry_add_comparison_int(condition2, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_comparison_int(condition2, CONTEXT_TRIGGER_TOTAL_COUNT, CONTEXT_TRIGGER_EQUAL_TO, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(condition2);
	} else {
		PRINT_INFO("Not supported item. Skip test(7/7)");
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_string_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_comparison_string()
 */
int utc_context_trigger_rule_entry_add_comparison_string_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	int error2 = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event1 = NULL;
	context_trigger_rule_entry_h event2 = NULL;
	context_trigger_rule_entry_h event3 = NULL;
	context_trigger_rule_entry_h event4 = NULL;
	context_trigger_rule_entry_h event5 = NULL;
	context_trigger_rule_entry_h event6 = NULL;
	context_trigger_rule_entry_h event7 = NULL;
	context_trigger_rule_entry_h event8 = NULL;

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);

		error = context_trigger_rule_entry_add_comparison_string(event1, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MON);
		context_trigger_rule_entry_destroy(event1);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_TIME);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_LEVEL);

		error = context_trigger_rule_entry_add_comparison_string(event2, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_LOW);
		context_trigger_rule_entry_destroy(event2);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_BATTERY);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_GPS, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event3);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_STATE);

		error = context_trigger_rule_entry_add_comparison_string(event3, CONTEXT_TRIGGER_STATE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_CONNECTED);
		context_trigger_rule_entry_destroy(event3);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_GPS);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event4);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event4, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);

		error = context_trigger_rule_entry_add_comparison_string(event4, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_HEADSET);
		context_trigger_rule_entry_destroy(event4);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_HEADPHONE);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_WIFI, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event5);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event5, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_BSSID);

		error = context_trigger_rule_entry_add_comparison_string(event5, CONTEXT_TRIGGER_BSSID, CONTEXT_TRIGGER_EQUAL_TO, "office");
		context_trigger_rule_entry_destroy(event5);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_WIFI);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event6);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event6, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_MEDIUM);
		context_trigger_rule_entry_add_key(event6, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_ADDRESS);

		error = context_trigger_rule_entry_add_comparison_string(event6, CONTEXT_TRIGGER_MEDIUM, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_VOICE);
		error2 = context_trigger_rule_entry_add_comparison_string(event6, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_EQUAL_TO, "10-1111-2222");
		context_trigger_rule_entry_destroy(event6);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error2, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_CALL);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CONTACTS, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event7);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event7, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_EVENT);
		context_trigger_rule_entry_add_key(event7, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);

		error = context_trigger_rule_entry_add_comparison_string(event7, CONTEXT_TRIGGER_EVENT, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_CHANGED);
		error2 = context_trigger_rule_entry_add_comparison_string(event7, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MY_PROFILE);

		context_trigger_rule_entry_destroy(event7);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error2, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_CONTACTS);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_ACTIVITY_RUNNING, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event8);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event8, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_EVENT);
		context_trigger_rule_entry_add_key(event8, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_ACCURACY);

		error = context_trigger_rule_entry_add_comparison_string(event8, CONTEXT_TRIGGER_EVENT, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_DETECTED);
		error2 = context_trigger_rule_entry_add_comparison_string(event8, CONTEXT_TRIGGER_ACCURACY, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);

		context_trigger_rule_entry_destroy(event8);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error2, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_ACTIVITY_RUNNING);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_string_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_comparison_string()
 */
int utc_context_trigger_rule_entry_add_comparison_string_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	int error2 = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h event1 = NULL;
	context_trigger_rule_entry_h event2 = NULL;
	context_trigger_rule_entry_h event3 = NULL;
	context_trigger_rule_entry_h event4 = NULL;
	context_trigger_rule_entry_h event5 = NULL;
	context_trigger_rule_entry_h event6 = NULL;
	context_trigger_rule_entry_h event7 = NULL;

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		// Err: Key not added
		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NO_DATA);

		context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);

		// Err: Invalid parameter
		error = context_trigger_rule_entry_add_comparison_string(NULL, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_comparison_string(event, NULL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, NULL, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, NULL);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		// Err: Invalid operator
		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_LESS_THAN, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Duplicated operator & value
		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WEEKEND);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Invalid comparison vale type
		context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
		error = context_trigger_rule_entry_add_comparison_string(event, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, "16");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_TIME);
	}

	// Err: Invalid comparison value
	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);

		error = context_trigger_rule_entry_add_comparison_string(event1, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_LOW);
		context_trigger_rule_entry_destroy(event1);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_TIME);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_LEVEL);

		error = context_trigger_rule_entry_add_comparison_string(event2, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MON);
		context_trigger_rule_entry_destroy(event2);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_BATTERY);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_GPS, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event3);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event3, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_STATE);

		error = context_trigger_rule_entry_add_comparison_string(event3, CONTEXT_TRIGGER_STATE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_HEADSET);
		context_trigger_rule_entry_destroy(event3);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_GPS);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event4);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event4, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);

		error = context_trigger_rule_entry_add_comparison_string(event4, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_CONNECTED);
		context_trigger_rule_entry_destroy(event4);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_HEADPHONE);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event5);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event5, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_MEDIUM);

		error = context_trigger_rule_entry_add_comparison_string(event5, CONTEXT_TRIGGER_MEDIUM, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_DETECTED);
		context_trigger_rule_entry_destroy(event5);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_CALL);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CONTACTS, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event6);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event6, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_EVENT);
		context_trigger_rule_entry_add_key(event6, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);

		error = context_trigger_rule_entry_add_comparison_string(event6, CONTEXT_TRIGGER_EVENT, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_CHANGED);
		error2 = context_trigger_rule_entry_add_comparison_string(event6, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MY_PROFILE);

		context_trigger_rule_entry_destroy(event6);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error2, CONTEXT_TRIGGER_ERROR_NONE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_CONTACTS);
	}

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_ACTIVITY_RUNNING, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event7);
	if (!is_trigger_supported || error != CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		context_trigger_rule_entry_add_key(event7, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_EVENT);
		context_trigger_rule_entry_add_key(event7, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_ACCURACY);

		error = context_trigger_rule_entry_add_comparison_string(event7, CONTEXT_TRIGGER_EVENT, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_NORMAL);
		error2 = context_trigger_rule_entry_add_comparison_string(event7, CONTEXT_TRIGGER_ACCURACY, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_CRITICAL);

		context_trigger_rule_entry_destroy(event7);

		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error2, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Event(%x) is not supported", CONTEXT_TRIGGER_EVENT_ACTIVITY_RUNNING);
	}


	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_p1
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_comparison()
 */
int utc_context_trigger_rule_entry_add_comparison_p1(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition1 = NULL;
	context_trigger_rule_entry_h condition2 = NULL;
	int rule_id;

	bool hdp_supported = false;
	bool chgr_supported = false;
	bool usb_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, &hdp_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_CHARGER, &chgr_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_USB, &usb_supported);
	if (is_trigger_supported && !(hdp_supported && chgr_supported && usb_supported)) {
		PRINT_INFO("Not supported item used. Skip test. (Headphone %d, Charger %d, USB %d)", hdp_supported, chgr_supported, usb_supported);
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_CHARGER, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
	context_trigger_rule_entry_add_key(condition1, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	error = context_trigger_rule_entry_add_comparison(condition1, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_USB, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
	context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	error = context_trigger_rule_entry_add_comparison(condition2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition1);
	context_trigger_rule_add_entry(rule, condition2);
	context_trigger_rule_set_action_app_control(rule, app);

	error = context_trigger_add_rule(rule, &rule_id);
	if (error == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		PRINT_INFO("Not supported");
	} else {
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	}

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition1);
	context_trigger_rule_entry_destroy(condition2);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_p2
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_comparison() - For each referential key
 */
int utc_context_trigger_rule_entry_add_comparison_p2(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h condition = NULL;

	bool btr_supported = false;
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_BATTERY, &btr_supported);
	if (is_trigger_supported && !btr_supported) {
		PRINT_INFO("Not supported item used. Skip test.");
		return 0;
	}

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CHARGING);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_LEVEL);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TIME_OF_DAY);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_DAY_OF_MONTH);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CHARGING);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CHARGING, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_ENABLED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_DAY_OF_WEEK);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_LEVEL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_STATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_TYPE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_BSSID);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MEDIUM);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_ADDRESS);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_EVENT);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_LEVEL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_ACCURACY);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(condition);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_comparison_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_comparison()
 */
int utc_context_trigger_rule_entry_add_comparison_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;

	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_entry_add_key(event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_IS_CONNECTED);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_TYPE);

	// Err: Invalid parameter
	error = context_trigger_rule_entry_add_comparison(NULL, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_comparison(condition, NULL, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CONNECTED, NULL, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Event cannot add an referential comparison data
	error = context_trigger_rule_entry_add_comparison(event, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: Invalid operator
	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_TYPE, CONTEXT_TRIGGER_LESS_THAN, CONTEXT_TRIGGER_HEADSET);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: Duplicated operator & value
	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	error = context_trigger_rule_entry_add_comparison(condition, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_IS_CONNECTED);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_int_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_option_int()
 */
int utc_context_trigger_rule_entry_add_option_int_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;

	bool place_supported = false;
	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_PLACE, &place_supported);
	if (!place_supported) {
		PRINT_INFO("Not supported item. Skip test.");
		return 0;
	}

	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	error = context_trigger_rule_entry_add_option_int(event, CONTEXT_TRIGGER_PLACE_ID, 1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(event);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_int_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_option_int()
 */
int utc_context_trigger_rule_entry_add_option_int_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	context_trigger_rule_entry_h condition2 = NULL;

	bool place_supported = false;
	bool app_supported = false;
	bool batt_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_PLACE, &place_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, &app_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_BATTERY, &batt_supported);

	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);

	// Err: Invalid parameter
	error = context_trigger_rule_entry_add_option_int(NULL, CONTEXT_TRIGGER_PLACE_ID, 1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	if (!is_trigger_supported || place_supported) {
		// Err: Invalid parameter
		error = context_trigger_rule_entry_add_option_int(event, NULL, 1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		// Err: Invalid option key
		error = context_trigger_rule_entry_add_option_int(event, CONTEXT_TRIGGER_RANK, 1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Invalid option value
		error = context_trigger_rule_entry_add_option_int(event, CONTEXT_TRIGGER_PLACE_ID, -1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	// Err: Invalid option value type
	if (!is_trigger_supported || app_supported) {
		error = context_trigger_rule_entry_add_option_int(condition, CONTEXT_TRIGGER_ADDRESS, 1);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	// Err: Item with no option
	if (!is_trigger_supported || batt_supported) {
		error = context_trigger_rule_entry_add_option_int(condition2, CONTEXT_TRIGGER_IS_CONNECTED, CONTEXT_TRIGGER_TRUE);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);
	} else {
		PRINT_INFO("Not supported item included. Skip test.");
	}

	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_entry_destroy(condition2);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_string_p
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_option_string()
 */
int utc_context_trigger_rule_entry_add_option_string_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h condition = NULL;
	context_trigger_rule_entry_h condition2 = NULL;

	bool app_supported = false;
	bool comm_supported = false;

	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, &app_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);

	if (is_trigger_supported && (!app_supported || !comm_supported)) {
		PRINT_INFO("Not supported item included. Skip test.");
		return 0;
	}

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_APP_ID, "org.tizen.setting");
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_TIME_OF_DAY, "13-15");
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_WEEKDAY);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
	error = context_trigger_rule_entry_add_option_string(condition2, CONTEXT_TRIGGER_ADDRESS, "010-1111-2222");
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_entry_destroy(condition2);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_string_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_option_string()
 */
int utc_context_trigger_rule_entry_add_option_string_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	context_trigger_rule_entry_h condition2 = NULL;

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	if (is_trigger_supported && error == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		PRINT_INFO("Place event is not supported. Skip test(1/3)");
	} else {
		// Err: Invalid option value type
		error = context_trigger_rule_entry_add_option_string(event, CONTEXT_TRIGGER_PLACE_ID, "1");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(event);
	}

	error = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_MUSIC_PLAYBACK_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	if (is_trigger_supported && error == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		PRINT_INFO("Music playback frequency condition is not supported. Skip test(2/3)");
	} else {
		// Err: Invalid parameter
		error = context_trigger_rule_entry_add_option_string(NULL, CONTEXT_TRIGGER_TIME_OF_DAY, "13-15");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_option_string(condition, NULL, "13-15");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_TIME_OF_DAY, NULL);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

		// Err: Invalid option key
		error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_APP_ID, "13-15");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		// Err: Invalid option value
		error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_TIME_OF_DAY, "19");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_TIME_OF_DAY, "0-26");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		error = context_trigger_rule_entry_add_option_string(condition, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_CONNECTED);
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(condition);
	}

	error = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_WIFI, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
	if (is_trigger_supported && error == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		PRINT_INFO("Wifi condition is not supported. Skip test(3/3)");
	} else {
		// Err: Item with no option
		error = context_trigger_rule_entry_add_option_string(condition2, CONTEXT_TRIGGER_BSSID, "Context");
		TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

		context_trigger_rule_entry_destroy(condition2);
	}

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_p1
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_option()
 */
int utc_context_trigger_rule_entry_add_option_p1(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_h rule = NULL;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;
	int rule_id;

	bool call_supported = false;
	bool comm_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CALL, &call_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);

	if (is_trigger_supported && (!call_supported || !comm_supported)) {
		PRINT_INFO("Not supported item included. Skip test.");
		return 0;
	}

	bool ret = initialize_app_handle();

	error = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	context_trigger_rule_entry_add_key(condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, CONTEXT_TRIGGER_RANK);
	context_trigger_rule_entry_add_comparison_int(condition, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_EQUAL_TO, 1);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_ADDRESS);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule);
	context_trigger_rule_add_entry(rule, event);
	context_trigger_rule_add_entry(rule, condition);
	context_trigger_rule_set_action_app_control(rule, app);

	error = context_trigger_add_rule(rule, &rule_id);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_remove_rule(rule_id);
	context_trigger_rule_entry_destroy(event);
	context_trigger_rule_entry_destroy(condition);
	context_trigger_rule_destroy(rule);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_p2
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_option()
 */
int utc_context_trigger_rule_entry_add_option_p2(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	bool time_supported = false;
	bool comm_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_TIME, &time_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);

	if (is_trigger_supported && (!time_supported || !comm_supported)) {
		PRINT_INFO("Not supported item included. Skip test.");
		return 0;
	}

	bool ret = initialize_app_handle();
	assert_eq(ret, true);

	context_trigger_rule_h rule2 = NULL;
	context_trigger_rule_entry_h event2 = NULL;
	context_trigger_rule_entry_h condition2 = NULL;
	int rule_id2;

	context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &rule2);
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event2);
	context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_DAY_OF_WEEK);
	context_trigger_rule_entry_add_comparison_string(event2, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_MON);
	context_trigger_rule_entry_add_comparison_string(event2, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_WED);
	context_trigger_rule_entry_add_comparison_string(event2, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_EQUAL_TO, CONTEXT_TRIGGER_FRI);
	context_trigger_rule_entry_add_key(event2, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_TIME_OF_DAY);
	context_trigger_rule_entry_add_comparison_int(event2, CONTEXT_TRIGGER_TIME_OF_DAY, CONTEXT_TRIGGER_EQUAL_TO, 0);
	context_trigger_rule_add_entry(rule2, event2);

	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition2);
	context_trigger_rule_entry_add_option_string(condition2, CONTEXT_TRIGGER_ADDRESS, "010-1111-2222");
	context_trigger_rule_entry_add_key(condition2, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, CONTEXT_TRIGGER_RANK);
	context_trigger_rule_entry_add_comparison_int(condition2, CONTEXT_TRIGGER_RANK, CONTEXT_TRIGGER_LESS_THAN, 5);

	error = context_trigger_rule_entry_add_option(condition2, CONTEXT_TRIGGER_DAY_OF_WEEK, CONTEXT_TRIGGER_DAY_OF_WEEK);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_add_entry(rule2, condition2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);
	context_trigger_rule_set_action_app_control(rule2, app);

	context_trigger_add_rule(rule2, &rule_id2);

	context_trigger_remove_rule(rule_id2);
	context_trigger_rule_entry_destroy(event2);
	context_trigger_rule_entry_destroy(condition2);
	context_trigger_rule_destroy(rule2);
	release_app_handle();

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_p3
 * @since_tizen		2.4
 * @description		Positive test case of context_trigger_rule_entry_add_option() - For each referential key
 */
int utc_context_trigger_rule_entry_add_option_p3(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h condition = NULL;

	error = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	if (is_trigger_supported && error == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
		PRINT_INFO("Not supported. Skip test.");
		return 0;
	}

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_DAY_OF_WEEK);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_LEVEL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_STATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_TYPE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_BSSID);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_MEDIUM);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_ADDRESS);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_EVENT);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_ACCURACY);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(condition);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_entry_add_option_n
 * @since_tizen		2.4
 * @description		Negative test case of context_trigger_rule_entry_add_option()
 */
int utc_context_trigger_rule_entry_add_option_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;
	context_trigger_rule_entry_h condition = NULL;

	bool place_supported = false;
	bool comm_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_PLACE, &place_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);
	if (is_trigger_supported && !(place_supported && comm_supported)) {
		PRINT_INFO("Not supported item included. Skip test.");
		return 0;
	}

	// Err: Invalid parmater
	context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);

	error = context_trigger_rule_entry_add_option(NULL, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_ADDRESS);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_option(condition, NULL, CONTEXT_TRIGGER_ADDRESS);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_ADDRESS, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Event cannot add an referential option data
	error = context_trigger_rule_entry_add_option(event, CONTEXT_TRIGGER_PLACE_ID, CONTEXT_TRIGGER_PLACE_ID);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	// Err: Invalid option key
	error = context_trigger_rule_entry_add_option(condition, CONTEXT_TRIGGER_APP_ID, CONTEXT_TRIGGER_APP_ID);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_RULE);

	context_trigger_rule_entry_destroy(condition);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_register_p
 * @since_tizen		3.0
 * @description		Positive test case of context_trigger_custom_register()
 */
int utc_context_trigger_custom_register_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	// Register same name & template again
	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_register_n
 * @since_tizen		3.0
 * @description		Negative test case of context_trigger_custom_register()
 */
int utc_context_trigger_custom_register_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Null parameter
	error = context_trigger_custom_register(NULL, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE_INVALID_JSON);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Invalid template (invalid, string->int, int->string)
	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE_INVALID1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE_INVALID2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE_INVALID3);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE_INVALID4);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	// Err: Register same item name but different template
	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_DATA_EXIST);

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_unregister_p
 * @since_tizen		3.0
 * @description		Positive test case of context_trigger_custom_unregister()
 */
int utc_context_trigger_custom_unregister_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_unregister_n
 * @since_tizen		3.0
 * @description		Negative test case of context_trigger_custom_unregister()
 */
int utc_context_trigger_custom_unregister_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Null parameter
	error = context_trigger_custom_unregister(NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Not supported
	error = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_publish_p
 * @since_tizen		3.0
 * @description		Positive test case of context_trigger_custom_publish()
 */
int utc_context_trigger_custom_publish_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	error = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_custom_publish_n
 * @since_tizen		3.0
 * @description		NegativePositive test case of context_trigger_custom_publish()
 */
int utc_context_trigger_custom_publish_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	// Err: Not supported
	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

	context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);

	// Err: Invalid parameter
	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_custom_publish(NULL, CUSTOM_WEATHER_DATA1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA_INVALID_JSON);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Invalid data
	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA_INVALID_KEY);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA_INVALID_VAL_INT);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA_INVALID_VAL_STR);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);

	error = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA_INVALID_TYPE);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_DATA);


	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_custom_event_create_p
 * @since_tizen		3.0
 * @description		Positive test case of context_trigger_rule_custom_event_create()
 */
int utc_context_trigger_rule_custom_event_create_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	context_trigger_rule_entry_h event1 = NULL;
	context_trigger_rule_entry_h event2 = NULL;

	context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);

	error = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &event2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(event1);
	context_trigger_rule_entry_destroy(event2);

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_custom_event_create_n
 * @since_tizen		3.0
 * @description		Negative test case of context_trigger_rule_custom_event_create()
 */
int utc_context_trigger_rule_custom_event_create_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h event = NULL;

	// Err: Invalid parameter
	error = context_trigger_rule_custom_event_create(NULL, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, NULL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Not supported
	error = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

	context_trigger_rule_entry_destroy(event);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_custom_condition_create_p
 * @since_tizen		3.0
 * @description		Positive test case of context_trigger_rule_custom_condition_create()
 */
int utc_context_trigger_rule_custom_condition_create_p(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;

	context_trigger_rule_entry_h condition1 = NULL;
	context_trigger_rule_entry_h condition2 = NULL;

	context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);

	error = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	error = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &condition2);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NONE);

	context_trigger_rule_entry_destroy(condition1);
	context_trigger_rule_entry_destroy(condition2);

	context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);

	return 0;
}

/**
 * @testcase		utc_context_trigger_rule_custom_condition_create_n
 * @since_tizen		3.0
 * @description		Negative test case of context_trigger_rule_custom_condition_create()
 */
int utc_context_trigger_rule_custom_condition_create_n(void)
{
	int error = CONTEXT_TRIGGER_ERROR_NONE;
	context_trigger_rule_entry_h condition = NULL;

	// Err: Invalid parameter
	error = context_trigger_rule_custom_condition_create(NULL, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, NULL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	error = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, NULL);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER);

	// Err: Not supported
	error = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition);
	TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(is_trigger_supported, error, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED);

	context_trigger_rule_entry_destroy(condition);

	return 0;
}
