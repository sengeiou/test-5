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
#include "assert.h"
#include "utc-capi-message-port.h"
#include <message_port.h>
#include <stdlib.h>
#include <app_manager.h>
#include <app.h>
#include <unistd.h>
#include <bundle.h>
#define MAX_COUNTER 30
#include "tct_app_common.h"
#include <glib-object.h>
#include <glib-2.0/glib.h>

static const int __local_port_id = 1;
static const char __local_port[] = "my_test_local_port";
static const char __remote_port[] = "my_test_remote_port";
static const char __remote_app_id[] = "org.tizen.messageportapp";
static const char __invalid_cert_remote_app_id[] = "org.tizen.messageportapp2";
static const char __terminated_remote_app_id[] = "org.tizen.messageportapp3";
static const char __unregistered_remote_app_id[] = "org.tizen.messageportapp4";
static bundle* __bundle = NULL;

static const int __negative_local_port_id = -1;
static const int __invalid_local_port_id = 2147483647;
static const char __invalid_remote_port[] = "invalid_test_remote_port";
static const char __check_user_data[] = "check_user_data";
static app_control_h __g_app_control_handler;

static char *__exceed_data = NULL;
static bundle *__exceed_bundle;
static const int EXCEED_MESSAGE_SIZE = 32 * 1024 + 1;

FILE *g_fp_log;
int __port_id;

#define assert_with_exit(exp) do { \
	if (!(exp)) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
		__result = 1; \
		ui_app_exit(); \
		return 1; \
	} \
} while (0)

#define assert_eq_with_exit(var, ref) do { \
	if (var != ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, (int)var, #ref, (int)ref); \
		__result = 1; \
		ui_app_exit(); \
		return 1; \
	} \
} while (0)

#define assert_neq_with_exit(var, ref) do { \
	if (var == ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		__result = 1; \
		ui_app_exit(); \
		return 1; \
	} \
} while (0)

#define assert_neq_without_exit(var, ref) do { \
	if (var == ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		__result = 1; \
		return 1; \
	} \
} while (0)

#define assert_gt_with_exit(var, ref) do { \
	if(var <= ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		__result = 1; \
		ui_app_exit(); \
		return 1; \
	} \
} while (0)

#define assert_eq_with_exit_no_returnval(var, ref) do { \
        if (var != ref) { \
                fprintf(stderr, \
                                "Assert fail in %s:%d\n", __FILE__, __LINE__); \
                fprintf(stderr, \
                                "Values \"%s\" and \"%s\" are not equal:\n" \
                                "%s == %d, %s == %d\n", \
                                #var, #ref, #var, (int)var, #ref, (int)ref); \
                __result = 1; \
                ui_app_exit(); \
                return; \
        } \
} while (0)

#define normal_exit(result) do { \
	__result = result; \
	ui_app_exit(); \
} while (0)

void __run_invalid_cert_app() {

	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret = app_control_create(&__g_app_control_handler);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(__g_app_control_handler , __invalid_cert_remote_app_id);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	do {

		ret = app_manager_is_running(__invalid_cert_remote_app_id, &is_running);
		if(ret == APP_MANAGER_ERROR_NONE) {
			if (!is_running) {
				ret = app_control_send_launch_request(__g_app_control_handler, NULL, NULL);
				if (ret != APP_CONTROL_ERROR_NONE) {
					sleep(1);
				}
			}
		}

	} while (--counter > 0 && !is_running);
	sleep(1);

}

void __run_unregistered_app() {

	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret = app_control_create(&__g_app_control_handler);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(__g_app_control_handler , __unregistered_remote_app_id);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	do {

		ret = app_manager_is_running(__unregistered_remote_app_id, &is_running);
		if(ret == APP_MANAGER_ERROR_NONE) {
			if (!is_running) {
				ret = app_control_send_launch_request(__g_app_control_handler, NULL, NULL);
				if (ret != APP_CONTROL_ERROR_NONE) {
					sleep(1);
				}
			}
		}

	} while (--counter > 0 && !is_running);
	sleep(1);

}

void __run_normal_app() {

	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret = app_control_create(&__g_app_control_handler);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	ret = app_control_set_app_id(__g_app_control_handler , __remote_app_id);
	assert_eq_with_exit_no_returnval(ret, APP_CONTROL_ERROR_NONE);

	do {
		ret = app_control_send_launch_request(__g_app_control_handler, NULL, NULL);
		if (ret != APP_CONTROL_ERROR_NONE)
			sleep(1);
		app_manager_is_running(__remote_app_id, &is_running);
	} while (--counter > 0 && !is_running);
	sleep(1);
}

/**
 * @function		utc_capi_message_port_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_message_port_startup(void)
{
	__bundle = bundle_create();
	__exceed_bundle = bundle_create();

	TCT_UTCCheckInstalledApp(4, "org.tizen.messageportapp", "org.tizen.messageportapp2",
				"org.tizen.messageportapp3", "org.tizen.messageportapp4");
}

/**
 * @function		utc_capi_message_port_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_capi_message_port_cleanup(void)
{
	bundle_free(__bundle);
	bundle_free(__exceed_bundle);
}

void __message_port_cb(int local_port_id, const char *remote_app_id,
		const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data)
{
}

void __message_port_cb_check_value(int local_port_id, const char *remote_app_id,
		const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data)
{

	bool is_valid_return = false;
	printf("[messageport] __message_port_cb_check_value called \n");

	char *data = NULL;
	char *user_data_char = (char *)user_data;
	bundle_get_str(message, "data", &data);
	printf("[messageport] received data, correct_value : %s, %s \n", data, __correct_value);
	if (data != NULL) {
		if (strcmp(data, __correct_value) == 0) {
			is_valid_return = true;
		}
	}

	printf("[messageport] send, recive done!! \n");
	if (!is_valid_return ||
			user_data_char != __check_user_data) {
		normal_exit(1);
		return;
	}

	printf("[messageport] success send, receive validation ! \n");
	normal_exit(0);

}

void __message_port_cb_check_value_with_multi_call(int local_port_id, const char *remote_app_id,
		const char *remote_port, bool trusted_remote_port, bundle *message, void *user_data)
{

	bool is_valid_return = false;
	printf("[messageport] __message_port_cb_check_value_with_multi_call called \n");

	char *data = NULL;
	bundle_get_str(message, "data", &data);
	printf("[messageport] received data, correct_value : %s, %s \n", data, __correct_value);
	if (data != NULL) {
		if (strcmp(data, __correct_value) == 0) {
			is_valid_return = true;
		}
	}

	__send_cnt--;
	printf("[messageport] data : send, recive done!! %d \n", __send_cnt);
	if (!is_valid_return) {
		normal_exit(1);
		return;
	}

	if (__send_cnt == 0) {
		printf("[messageport] data success send, receive validation ! \n");
		int ret = message_port_unregister_local_port(__port_id);
		if (ret != MESSAGE_PORT_ERROR_NONE) {
			printf("[messageport] data message_port_unregister_local_port error : %d", ret);
		}
		normal_exit(0);
	}

}

void __registered_remote_port_cb(const char *remote_app_id, const char *remote_port, bool
		trusted_remote_port, void *user_data)
{
	printf("[messageport] remote port is registered! \n");

	char *user_data_char = (char *)user_data;
	if (user_data_char != __check_user_data) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

void __unregistered_remote_port_cb(const char *remote_app_id, const char *remote_port, bool
		trusted_remote_port, void *user_data)
{
	printf("[messageport] remote port is unregistered! \n");

	char *user_data_char = (char *)user_data;
	if (user_data_char != __check_user_data) {
		normal_exit(1);
		return;
	}

	normal_exit(0);
}

/**
 * @testcase		utc_capi_message_port_register_local_port_n01
 * @since_tizen		2.3
 * @description		Register local port with invalid parameter.
 * @scenario 		Try to register local port with invalid parameter and check return value.
 */
int utc_capi_message_port_register_local_port_n01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_local_port(__local_port, NULL, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_register_local_port_n02
 * @since_tizen		2.3
 * @description		Register local port with invalid parameter.
 * @scenario 		Try to register local port with invalid parameter and check return value.
 */
int utc_capi_message_port_register_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_local_port(NULL, __message_port_cb, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_register_local_port_p01
 * @since_tizen		2.3
 * @description		Register local port with valid parameter.
 * @scenario 		Try to register local port with valid parameter and check return value.
 */
int utc_capi_message_port_register_local_port_p01(void)
{
	int port_id = 0;

	port_id = message_port_register_local_port(__local_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	message_port_unregister_local_port(port_id);

	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_capi_message_port_register_trusted_local_port_n01
 * @since_tizen		2.3
 * @description		Register trusted local port with invalid parameter.
 * @scenario 		Try to register trusted local port with invalid parameter and check return value.
 */
int utc_capi_message_port_register_trusted_local_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_trusted_local_port(__local_port, NULL, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_register_trusted_local_port_n02
 * @since_tizen		2.3
 * @description		Register trusted local port with invalid parameter.
 * @scenario 		Try to register trusted local port with invalid parameter and check return value.
 */
int utc_capi_message_port_register_trusted_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_register_trusted_local_port(NULL, __message_port_cb, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_register_trusted_local_port_p01
 * @since_tizen		2.3
 * @description		Register trusted local port with valid parameter.
 * @scenario 		Try to register trusted local port with valid parameter and check return value.
 */
int utc_capi_message_port_register_trusted_local_port_p01(void)
{
	int port_id = 0;

	port_id = message_port_register_trusted_local_port(__local_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	message_port_unregister_trusted_local_port(port_id);

	normal_exit(0);
	return 0;

}

/**
 * @testcase		utc_capi_message_port_unregister_local_port_n01
 * @since_tizen		2.3
 * @description		Unregister local port with invalid parameter.
 * @scenario 		Try to unregister local port with invalid parameter and check return value.
 */
int utc_capi_message_port_unregister_local_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_local_port(__negative_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_unregister_local_port_n02
 * @since_tizen		2.3
 * @description		Unregister local port with invalid parameter.
 * @scenario 		Try to unregister not exist local port and check return value.
 */
int utc_capi_message_port_unregister_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_local_port(__invalid_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_unregister_local_port_p01
 * @since_tizen		2.3
 * @description		Unregister local port with valid parameter.
 * @scenario 		Try to unregister local port with valid parameter and check return value.
 */
int utc_capi_message_port_unregister_local_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	port_id = message_port_register_local_port(__local_port,
			__message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_unregister_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_unregister_trusted_local_port_n01
 * @since_tizen		2.3
 * @description		Unregister trusted local port with invalid parameter.
 * @scenario 		Try to unregister trusted local port with invalid parameter and check return value.
 */
int utc_capi_message_port_unregister_trusted_local_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_trusted_local_port(__negative_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_unregister_trusted_local_port_n02
 * @since_tizen		2.3
 * @description		Unregister trusted local port with invalid parameter.
 * @scenario 		Try to unregister trusted local port with valid parameter and check return value.
 */
int utc_capi_message_port_unregister_trusted_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_unregister_trusted_local_port(__invalid_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_unregister_trusted_local_port_p01
 * @since_tizen		2.3
 * @description		Unregister trusted local port with valid parameter.
 * @scenario 		Try to unregister trusted local port with valid parameter and check return value.
 */
int utc_capi_message_port_unregister_trusted_local_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	port_id = message_port_register_trusted_local_port(__local_port,
			__message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_unregister_trusted_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_p01
 * @since_tizen		2.3
 * @description		Check remote port with valid parameter.
 * @scenario 		Try to check remote port with valid parameter and check return value.
 */
int utc_capi_message_port_check_remote_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	__run_normal_app();

	res = message_port_check_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_p02
 * @since_tizen		2.3
 * @description		Check remote port with valid parameter.
 * @scenario 		Try to check remote port with valid parameter after register local port and check return value.
 */
int utc_capi_message_port_check_remote_port_p02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_check_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);
	assert_eq_with_exit(exist, true);

	message_port_unregister_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_p03
 * @since_tizen		2.3
 * @description		Check remote port with valid parameter.
 * @scenario 		Try to check unregistered remote port and check exist value.
 */
int utc_capi_message_port_check_remote_port_p03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = true;

	__run_unregistered_app();

	res = message_port_check_remote_port(__unregistered_remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);
	assert_eq_with_exit(exist, false);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_n01
 * @since_tizen		2.3
 * @description		Check remote port with invalid parameter.
 * @scenario 		Try to check remote port with invalid parameter and check return value.
 */
int utc_capi_message_port_check_remote_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_remote_port(__remote_app_id, NULL, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_n02
 * @since_tizen		2.3
 * @description		Check remote port with invalid parameter.
 * @scenario 		Try to check remote port with invalid parameter and check return value.
 */
int utc_capi_message_port_check_remote_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_remote_port(NULL, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_remote_port_n03
 * @since_tizen		2.3
 * @description		Check terminated app's remote port.
 * @scenario 		Try to check terminated app's remote port and check exist value.
 */
int utc_capi_message_port_check_remote_port_n03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = true;

	res = message_port_check_remote_port(__terminated_remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);
	assert_eq_with_exit(exist, false);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_trusted_remote_port_p01
 * @since_tizen		2.3
 * @description		Check trusted remote port.
 * @scenario 		Try to check trusted remote port with valid parameter and check return value.
 */
int utc_capi_message_port_check_trusted_remote_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	__run_normal_app();

	res = message_port_check_trusted_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_trusted_remote_port_p02
 * @since_tizen		2.3
 * @description		Check trusted remote port.
 * @scenario 		Try to check trusted remote port with valid parameter and check exist value.
 */
int utc_capi_message_port_check_trusted_remote_port_p02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_trusted_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_check_trusted_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);
	assert_eq_with_exit(exist, true);

	message_port_unregister_trusted_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_trusted_remote_port_n01
 * @since_tizen		2.3
 * @description		Check trusted remote port.
 * @scenario 		Try to check trusted remote port with invalid parameter and check return value.
 */
int utc_capi_message_port_check_trusted_remote_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_trusted_remote_port(__remote_app_id, NULL, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_check_trusted_remote_port_n02
 * @since_tizen		2.3
 * @description		Check trusted remote port.
 * @scenario 		Try to check trusted remote port with invalid parameter and check return value.
 */
int utc_capi_message_port_check_trusted_remote_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	res = message_port_check_trusted_remote_port(NULL, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_p01
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send message to remote port with invalid parameter and check return value.
 */
int utc_capi_message_port_send_message_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_check_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	res = message_port_send_message(__remote_app_id, __remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	message_port_unregister_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_n01
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_message_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message(__remote_app_id, __remote_port, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_n02
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_message_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message(__remote_app_id, NULL, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_n03
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_message_n03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message(NULL, __remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_n04
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send message to not exist remote port, and check return value.
 */
int utc_capi_message_port_send_message_n04(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_invalid_cert_app();

	res = message_port_send_message(__remote_app_id, __invalid_remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_capi_message_port_send_message_n05
 * @since_tizen		2.3
 * @description		Send message.
 * @scenario 		Try to send larger than max message size, and check return value.
 */
int utc_capi_message_port_send_message_n05(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_normal_app();

	__exceed_data = (char *)calloc(EXCEED_MESSAGE_SIZE, sizeof(char));
	memset(__exceed_data, '-', EXCEED_MESSAGE_SIZE);
	__exceed_data[EXCEED_MESSAGE_SIZE - 1] = '\0';
	bundle_add_str(__exceed_bundle, "data", __exceed_data);

	res = message_port_send_message(__remote_app_id, __remote_port, __exceed_bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_MAX_EXCEEDED);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_p01
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_trusted_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_check_trusted_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	res = message_port_send_trusted_message(__remote_app_id, __remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	message_port_unregister_trusted_local_port(port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_n01
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_trusted_message_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message(__remote_app_id, __remote_port, NULL);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_n02
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_trusted_message_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message(__remote_app_id, NULL, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_n03
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message with invalid parameter and check return value.
 */
int utc_capi_message_port_send_trusted_message_n03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message(NULL, __remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_n04
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message to not exist remote port and check return value.
 */
int utc_capi_message_port_send_trusted_message_n04(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_invalid_cert_app();

	res = message_port_send_trusted_message(__remote_app_id, __invalid_remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_capi_message_port_send_trusted_message_n05
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send larger than max size trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_n05(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_normal_app();

	__exceed_data = (char *)calloc(EXCEED_MESSAGE_SIZE, sizeof(char));
	memset(__exceed_data, '-', EXCEED_MESSAGE_SIZE);
	__exceed_data[EXCEED_MESSAGE_SIZE - 1] = '\0';
	bundle_add_str(__exceed_bundle, "data", __exceed_data);

	res = message_port_send_trusted_message(__remote_app_id, __remote_port, __exceed_bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_MAX_EXCEEDED);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_capi_message_port_send_trusted_message_n06
 * @since_tizen		2.3
 * @description		Send trusted message.
 * @scenario 		Try to send trusted message to different certificate remote port and check return value.
 */
int utc_capi_message_port_send_trusted_message_n06(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_invalid_cert_app();

	res = message_port_send_trusted_message(__invalid_cert_remote_app_id, __remote_port, __bundle);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_CERTIFICATE_NOT_MATCH);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_p01
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and receive value from remote port.
 */
int utc_capi_message_port_send_message_with_local_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	__run_normal_app();

	__port_id = message_port_register_local_port(__remote_port, __message_port_cb_check_value, (void *)__check_user_data);
	assert_gt_with_exit(__port_id, 0);

	res = message_port_check_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	char send_data[10] = "test";
	bundle_add_str(__bundle, "data", send_data);

	__correct_value = strdup(send_data);

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, __bundle, __port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);


	return 1;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_p02
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send multiple message with local port info and receive value from remote port.
 */
int utc_capi_message_port_send_message_with_local_port_p02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	__run_normal_app();

	__port_id = message_port_register_local_port(__local_port,
			__message_port_cb_check_value_with_multi_call, NULL);
	assert_gt_with_exit(__port_id, 0);

	res = message_port_check_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	char send_data[10] = "test";
	bundle_add_str(__bundle, "data", send_data);

	__correct_value = strdup(send_data);
	__send_cnt = 2;

	res = message_port_send_message_with_local_port(__remote_app_id,
			__remote_port, __bundle, __port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	res = message_port_send_message_with_local_port(__remote_app_id,
			__remote_port, __bundle, __port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	return 1;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n01
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, NULL, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n02
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message_with_local_port(__remote_app_id, NULL, __bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n03
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message_with_local_port(NULL, __remote_port, __bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n04
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n04(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, __bundle, __negative_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n05
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message with local port info and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n05(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_normal_app();

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port, __bundle, __invalid_local_port_id);
	assert_neq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n06
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send message to not exist remote port and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n06(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_send_message_with_local_port(__remote_app_id, __invalid_remote_port,
			__bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	message_port_unregister_local_port(port_id);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_message_with_local_port_n07
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send larger than max size message and check return value.
 */
int utc_capi_message_port_send_message_with_local_port_n07(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	__exceed_data = (char *)calloc(EXCEED_MESSAGE_SIZE, sizeof(char));
	memset(__exceed_data, '-', EXCEED_MESSAGE_SIZE);
	__exceed_data[EXCEED_MESSAGE_SIZE - 1] = '\0';
	bundle_add_str(__exceed_bundle, "data", __exceed_data);

	res = message_port_send_message_with_local_port(__remote_app_id, __remote_port,
			__exceed_bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_MAX_EXCEEDED);

	message_port_unregister_local_port(port_id);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_p01
 * @since_tizen		2.3
 * @description		Send message with local port.
 * @scenario 		Try to send trusted message with local port info and receive value from remote port.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_p01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	bool exist = false;

	__run_normal_app();

	__port_id = message_port_register_trusted_local_port(__remote_port, __message_port_cb_check_value, (void *)__check_user_data);
	assert_gt_with_exit(__port_id, 0);

	res = message_port_check_trusted_remote_port(__remote_app_id, __remote_port, &exist);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	char send_data[10] = "test";
	bundle_add_str(__bundle, "data", send_data);

	__correct_value = strdup(send_data);

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, __bundle, __port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	return 1;

}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n01
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n01(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, NULL, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n02
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n02(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, NULL, __bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n03
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n03(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message_with_local_port(NULL, __remote_port, __bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n04
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n04(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, __bundle, __negative_local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n05
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n05(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;

	__run_normal_app();

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port, __bundle, __invalid_local_port_id);
	assert_neq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}


/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n06
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message to not exist remote port and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n06(void)
{
	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __invalid_remote_port,
			__bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_PORT_NOT_FOUND);

	message_port_unregister_local_port(port_id);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n07
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send larger than max size trusted message and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n07(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	__run_normal_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	__exceed_data = (char *)calloc(EXCEED_MESSAGE_SIZE, sizeof(char));
	memset(__exceed_data, '-', EXCEED_MESSAGE_SIZE);
	__exceed_data[EXCEED_MESSAGE_SIZE - 1] = '\0';
	bundle_add_str(__exceed_bundle, "data", __exceed_data);

	res = message_port_send_trusted_message_with_local_port(__remote_app_id, __remote_port,
			__exceed_bundle, __local_port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_MAX_EXCEEDED);

	message_port_unregister_local_port(port_id);

	normal_exit(0);
	return 0;
}
/**
 * @testcase		utc_capi_message_port_send_trusted_message_with_local_port_n08
 * @since_tizen		2.3
 * @description		Send trusted message with local port.
 * @scenario 		Try to send trusted message to different certificate remote port and check return value.
 */
int utc_capi_message_port_send_trusted_message_with_local_port_n08(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;
	int port_id = 0;

	__run_invalid_cert_app();

	port_id = message_port_register_local_port(__remote_port, __message_port_cb, NULL);
	assert_gt_with_exit(port_id, 0);

	res = message_port_send_trusted_message_with_local_port(__invalid_cert_remote_app_id, __remote_port,
			__bundle, port_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_CERTIFICATE_NOT_MATCH);

	message_port_unregister_local_port(port_id);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_add_watching_remote_port_cb_p01
 * @since_tizen		4.0
 * @description		Add a callback to watch that remote port is registered.
 * @scenario 		Add a callback and check callback is called.
 */
int utc_capi_message_port_add_registered_cb_p01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id;
	res = message_port_add_registered_cb(__remote_app_id, __remote_port, 1, __registered_remote_port_cb, (void *)__check_user_data, &watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	__run_normal_app();

	return 1;
}

/**
 * @testcase		utc_capi_message_port_add_registered_cb_n01
 * @since_tizen		4.0
 * @description		Add a callback to watch that remote port is registered.
 * @scenario 		Add a callback and check callback is called.
 */
int utc_capi_message_port_add_registered_cb_n01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id;
	res = message_port_add_registered_cb(NULL, __remote_port, 1, __registered_remote_port_cb, NULL, &watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_add_unregistered_cb_p01
 * @since_tizen		4.0
 * @description		Add a callback to watch that remote port is unregistered.
 * @scenario 		Add a callback and check callback is called.
 */
int utc_capi_message_port_add_unregistered_cb_p01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id;
	res = message_port_add_unregistered_cb( __terminated_remote_app_id, __remote_port, 1, __unregistered_remote_port_cb, (void *)__check_user_data, &watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	__run_normal_app();

	return 1;
}

/**
 * @testcase		utc_capi_message_port_add_unregistered_cb_n01
 * @since_tizen		4.0
 * @description		Add a callback to watch that remote port is registered.
 * @scenario 		Add a callback and check callback is called.
 */
int utc_capi_message_port_add_unregistered_cb_n01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id;
	res = message_port_add_unregistered_cb( __remote_app_id, NULL, 1, __unregistered_remote_port_cb, NULL, &watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_remove_watching_remote_port_cb_p01
 * @since_tizen		4.0
 * @description		Remove a callback to watch that remote port is registered.
 * @scenario 		Remove a callback and check callback is called.
 */
int utc_capi_message_port_remove_registration_event_cb_p01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id;
	res = message_port_add_registered_cb(__remote_app_id, __remote_port, 1, __registered_remote_port_cb, NULL, &watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	__run_normal_app();

	res = message_port_remove_registration_event_cb(watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_NONE);

	normal_exit(0);
	return 0;
}

/**
 * @testcase		utc_capi_message_port_remove_watching_remote_port_cb_n01
 * @since_tizen		4.0
 * @description		Remove a callback to watch that remote port is registered.
 * @scenario 		Remove a callback and check callback is called.
 */
int utc_capi_message_port_remove_registration_event_cb_n01(void)
{

	int res = MESSAGE_PORT_ERROR_NONE;

	int watcher_id = -1;
	res = message_port_remove_registration_event_cb(watcher_id);
	assert_eq_with_exit(res, MESSAGE_PORT_ERROR_INVALID_PARAMETER);

	normal_exit(0);
	return 0;
}
