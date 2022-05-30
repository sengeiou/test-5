//
// Copyright (c) 2015 Samsung Electronics Co., Ltd.
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
#include "assert_common.h"
#include <stdio.h>
#include <app_event.h>
#include <bundle.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <app_manager.h>
#include <app.h>
#include <glib.h>
#include "tct_app_common.h"
#define MAX_COUNTER 30

static const char __sender_app_id[] = "org.tizen.eventsender";

static const char __trusted_receiver[] = "org.tizen.event_receiver";
static const char __non_trusted_receiver[] = "org.tizen.event_receiver2";

static const int __negative_local_port_id = -1;
static const int __invalid_local_port_id = 2147483647;
static const char __invalid_remote_port[] = "invalid_test_remote_port";
static app_control_h __g_app_control_handler;

static const int EXCEED_MESSAGE_SIZE = 32 * 1024 + 1;




static event_handler_h event_handler;

static char *user_data_key = "user_data_key";
static char *user_data = "user_data";

static void __run_receiver_app(const char *appid) {
	bool is_running = false;
	int counter = MAX_COUNTER;
	int ret = app_control_create(&__g_app_control_handler);

	if (ret != APP_CONTROL_ERROR_NONE) {
		normal_exit(1);
		return;
	}

	ret = app_control_set_app_id(__g_app_control_handler , appid);
	if (ret != APP_CONTROL_ERROR_NONE) {
		normal_exit(1);
		return;
	}

	do {
		ret = app_manager_is_running(appid, &is_running);
		if (ret == APP_MANAGER_ERROR_NONE) {
			if (!is_running) {
				ret = app_control_send_launch_request(__g_app_control_handler,
						NULL, NULL);
				if (ret != APP_CONTROL_ERROR_NONE) {
					sleep(1);
				}
			}
		}
	} while (--counter > 0 && !is_running);

	sleep(5);
}

static void __get_event_name(char *local_event_name)
{
	char *appid;
	app_get_id(&appid);
	snprintf(local_event_name, PATH_MAX, "event.%s.user_event", appid);
	free(appid);
}

void timer_handler(int signum) {

	__timer_cnt ++;
	if (__timer_cnt > MAX_TIMER_CNT) {
		event_remove_event_handler(event_handler);
		__timer_cnt = 0;
		normal_exit(0);
	}
}

static void utc_event_cb(const char *event_name, bundle *event_data, void *user_data)
{
	fprintf(stderr, "utc_event_cb : %s \n", event_name);
	return;
}

static void utc_event_cb_with_valid_check(const char *event_name, bundle *event_data, void *user_data)
{
	fprintf(stderr, "utc_event_cb_with_valid_check : %s \n", event_name);

	char *received_data = NULL;
	bundle_get_str(event_data, user_data_key, &received_data);

	if (strcmp(received_data, __correct_value) == 0) {
		event_remove_event_handler(event_handler);
		normal_exit(0);
	} else {
		normal_exit(1);
	}

	return;
}

/**
 * @function            utc_application_app_event_startup
 * @description         Called before some test
 * @parameter           NA
 * @return              NA
 */
void utc_application_app_event_startup(void)
{
        TCT_UTCCheckInstalledApp(1, "org.tizen.eventsender");
}

void utc_application_app_event_cleanup(void)
{
	app_control_send_terminate_request(__g_app_control_handler);
	app_control_destroy(__g_app_control_handler);
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_BATTERY_CHARGER_STATUS,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p1(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_CHARGER_STATUS, utc_event_cb,
			"SYSTEM_EVENT_BATTERY_CHARGER_STATUS", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p2
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_BATTERY_LEVEL_STATUS,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p2(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_LEVEL_STATUS, utc_event_cb,
			"SYSTEM_EVENT_BATTERY_LEVEL_STATUS", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase            utc_application_app_event_add_event_handler_p3
 * @since_tizen         2.4
 * @type                Positive
 * @description         Adds the event handler for receiving event-data of interested events.
 * @scenario            Adds the event handler for the SYSTEM_EVENT_USB_STATUS,
 *                      and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p3(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_USB_STATUS, utc_event_cb,
			"SYSTEM_EVENT_USB_STATUS", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p4
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_EARJACK_STATUS,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p4(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_EARJACK_STATUS, utc_event_cb,
			"SYSTEM_EVENT_EARJACK_STATUS", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p5
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_DISPLAY_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p5(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_DISPLAY_STATE, utc_event_cb,
			"SYSTEM_EVENT_DISPLAY_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p6
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_BOOT_COMPLETED,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p6(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BOOT_COMPLETED, utc_event_cb,
			"SYSTEM_EVENT_BOOT_COMPLETED", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p7
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_SYSTEM_SHUTDOWN,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p7(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_SYSTEM_SHUTDOWN, utc_event_cb,
			"SYSTEM_EVENT_SYSTEM_SHUTDOWN", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p8
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_LOW_MEMORY,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p8(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_LOW_MEMORY, utc_event_cb,
			"SYSTEM_EVENT_LOW_MEMORY", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p9
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adss the event handler for the SYSTEM_EVENT_WIFI_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p9(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_WIFI_STATE, utc_event_cb,
			"SYSTEM_EVENT_WIFI_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p10
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_BT_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p10(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BT_STATE, utc_event_cb,
			"SYSTEM_EVENT_BT_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p11
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_BT_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p11(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_LOCATION_ENABLE_STATE, utc_event_cb,
			"SYSTEM_EVENT_LOCATION_ENABLE_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p12
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_GPS_ENABLE_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p12(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_GPS_ENABLE_STATE, utc_event_cb,
			"SYSTEM_EVENT_GPS_ENABLE_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p13
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_NPS_ENABLE_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p13(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_NPS_ENABLE_STATE, utc_event_cb,
			"SYSTEM_EVENT_NPS_ENABLE_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p14
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_TIME_ZONE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p14(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_TIME_ZONE, utc_event_cb,
			"SYSTEM_EVENT_TIME_ZONE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p15
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_HOUR_FORMAT,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p15(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_HOUR_FORMAT, utc_event_cb,
			"SYSTEM_EVENT_HOUR_FORMAT", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p16
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_LANGUAGE_SET,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p16(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_LANGUAGE_SET, utc_event_cb,
			"SYSTEM_EVENT_LANGUAGE_SET", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p17
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adss the event handler for the SYSTEM_EVENT_REGION_FORAMT,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p17(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_REGION_FORMAT, utc_event_cb,
			"SYSTEM_EVENT_REGION_FORMAT", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p18
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adss the event handler for the SYSTEM_EVENT_VIBRATION_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p18(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_VIBRATION_STATE, utc_event_cb,
			"SYSTEM_EVENT_VIBRATION_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p19
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adss the event handler for the SYSTEM_EVENT_SCREEN_AUTOROTATE_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p19(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_SCREEN_AUTOROTATE_STATE, utc_event_cb,
			"SYSTEM_EVENT_SCREEN_AUTOROTATE_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p20
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_MOBILE_DATA_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p20(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_MOBILE_DATA_STATE, utc_event_cb,
			"SYSTEM_EVENT_MOBILE_DATA_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p21
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_DATA_ROAMING_STATE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p21(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_DATA_ROAMING_STATE, utc_event_cb,
			"SYSTEM_EVENT_DATA_ROAMING_STATE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p22
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_FONT_SET,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p22(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_FONT_SET, utc_event_cb,
			"SYSTEM_EVENT_FONT_SET", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p23
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_INCOMING_MSG,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p23(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_INCOMING_MSG, utc_event_cb,
			"SYSTEM_EVENT_INCOMING_MSG", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p24
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adss the event handler for the SYSTEM_EVENT_TIME_CHANGED,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p24(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_TIME_CHANGED, utc_event_cb,
			"SYSTEM_EVENT_TIME_CHANGED", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p25
 * @since_tizen		2.4
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_SLIENT_MODE,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p25(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_SILENT_MODE, utc_event_cb,
			"SYSTEM_EVENT_SILENT_MODE", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p26
 * @since_tizen		3.0
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_NETWORK_STATUS,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p26(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_NETWORK_STATUS, utc_event_cb,
			"SYSTEM_EVENT_NETWORK_STATUS", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_p27
 * @since_tizen		3.0
 * @type		Positive
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler for the SYSTEM_EVENT_OUTGOING_MSG,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_p27(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_OUTGOING_MSG, utc_event_cb,
			"SYSTEM_EVENT_OUTGOING_MSG", &event_handler);

	event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler with the invalid parameter
 *			that the event_name is NULL, and then checks the return value.
 */
int utc_application_app_event_add_event_handler_n1(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(NULL, utc_event_cb,
			NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_n2
 * @since_tizen		2.4
 * @type		Negative
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler with the invalid parameter
 *			that the callback is NULL, and then checks the return value.
 */
int utc_application_app_event_add_event_handler_n2(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_CHARGER_STATUS, NULL,
			NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_n3
 * @since_tizen		2.4
 * @type		Negative
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler with the invalid parameter
 *			that the event_handler is NULL, and then checks the return value.
 */
int utc_application_app_event_add_event_handler_n3(void)
{
	int ret = EVENT_ERROR_NONE;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_CHARGER_STATUS, utc_event_cb,
			NULL, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_add_event_handler_n4
 * @since_tizen		2.4
 * @type		Negative
 * @description		Adds the event handler for receiving event-data of interested events.
 * @scenario		Adds the event handler with the NULL parameters,
 *			and then checks the return value.
 */
int utc_application_app_event_add_event_handler_n4(void)
{
	int ret = EVENT_ERROR_NONE;

	ret = event_add_event_handler(NULL, NULL, NULL, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_remove_event_handler_p
 * @since_tizen		2.4
 * @type		Positive
 * @description		Removes the registered event handler.
 * @scenario		Adds the event handler and removes the registered event handler.
 */
int utc_application_app_event_remove_event_handler_p(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_CHARGER_STATUS, utc_event_cb,
			"SYSTEM_EVENT_BATTERY_CHARGER_STATUS", &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = event_remove_event_handler(event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_remove_event_handler_n
 * @since_tizen		2.4
 * @type		Negative
 * @description		Removes the registered event handler.
 * @scenario		Adds the event handler and removes the registered event handler
 *			with the invalid parameter, that the event_handler is NULL.
 *			And then, checks the return value.
 */
int utc_application_app_event_remove_event_handler_n(void)
{
	int ret = EVENT_ERROR_NONE;
	event_handler_h event_handler;

	ret = event_add_event_handler(SYSTEM_EVENT_BATTERY_CHARGER_STATUS, utc_event_cb,
			"SYSTEM_EVENT_BATTERY_CHARGER_STATUS", &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = event_remove_event_handler(NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_app_event_p1
 * @since_tizen		2.4
 * @type		Positive
 * @description		Sends the User-Event to trusted receiver applications.
 * @scenario		Adds the event handler and sends the user event,
 *			and then checks the return value.
 */
int utc_application_app_event_publish_app_event_p1(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;
	char local_event_name[PATH_MAX];

	__run_receiver_app(__trusted_receiver);

	ret = event_add_event_handler("event.org.tizen.event_receiver.user_event",
			utc_event_cb_with_valid_check, NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, user_data_key, user_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	__correct_value = user_data;

	__get_event_name(local_event_name);
	ret = event_publish_app_event(local_event_name, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_app_event_p2
 * @since_tizen		2.4
 * @type		Positive
 * @description		Sends the User-Event to non-trusted receiver applications.
 * @scenario		Adds the event handler and sends the user event,
 *			and then checks the return value.
 */
int utc_application_app_event_publish_app_event_p2(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;
	char local_event_name[PATH_MAX];

	__run_receiver_app(__non_trusted_receiver);

	ret = event_add_event_handler("event.org.tizen.event_receiver2.user_event",
			utc_event_cb_with_valid_check, NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, user_data_key, user_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	__correct_value = user_data;

	__get_event_name(local_event_name);
	ret = event_publish_app_event(local_event_name, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_app_event_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to receiver applications.
 * @scenario		Sends the event with the invalid parameter,
 *			that the event_name is NULL, and then checks the retrun value.
 */
int utc_application_app_event_publish_app_event_n1(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, "user_data_key", "user_data");
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	ret = event_publish_app_event(NULL, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_app_event_n2
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to receiver applications.
 * @scenario		Sends the user event with the invalid parameter,
 *			that the event_data is NULL, and then checks the return value.
 */
int utc_application_app_event_publish_app_event_n2(void)
{
	int ret = EVENT_ERROR_NONE;
	char local_event_name[PATH_MAX];

	__get_event_name(local_event_name);
	ret = event_publish_app_event(local_event_name, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_app_event_n3
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to receiver applications.
 * @scenario		Sends the event with the NULL parameters,
 *			and then checks the return value.
 */
int utc_application_app_event_publish_app_event_n3(void)
{
	int ret = EVENT_ERROR_NONE;

	ret = event_publish_app_event(NULL, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_p
 * @since_tizen		2.4
 * @type		Positive
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario	Launchs the trusted receiver-application and adds event handler.
 *			Sends trusted events to receiver application and wait for reply event from receiver application
 *			and then checks the return value.
 */
int utc_application_app_event_publish_trusted_app_event_p(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;
	char local_event_name[PATH_MAX];

	__run_receiver_app(__trusted_receiver);

	ret = event_add_event_handler("event.org.tizen.event_receiver.user_event",
			utc_event_cb_with_valid_check, NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, user_data_key, user_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	__correct_value = user_data;

	__get_event_name(local_event_name);
	ret = event_publish_trusted_app_event(local_event_name, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_n1
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario		Send the event with the invalid parameter
 *			that the event_name is NULL, and then checks the return value.
 */
int utc_application_app_event_publish_trusted_app_event_n1(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, "user_data_key", "user_data");
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	ret = event_publish_trusted_app_event(NULL, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_n2
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario		Sends the user event with the invalid parameter
 *			that the event_data is NULL, and then checks the return value.
 */
int utc_application_app_event_publish_trusted_app_event_n2(void)
{
	int ret = EVENT_ERROR_NONE;
	char local_event_name[PATH_MAX];

	__get_event_name(local_event_name);
	ret = event_publish_trusted_app_event(local_event_name, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_n3
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario		Send the event with the NULL parameters,
 *			and then checks the return value.
 */
int utc_application_app_event_publish_trusted_app_event_n3(void)
{
	int ret = EVENT_ERROR_NONE;

	ret = event_publish_trusted_app_event(NULL, NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_n4
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario		Adds the event handler and launchs the event-sender application.
 *			And then, the event-sender application will send the user-event that
 *			the event_name is "event.org.tizen.eventsender.user_event". While calling
 *			the callback function, the __correct_value compares with the user_data.
 *			If two values are same, this test-case exits normally.
 */
int utc_application_app_event_publish_trusted_app_event_n4(void)
{
	int ret = EVENT_ERROR_NONE;
	struct sigaction sa;
	struct itimerval timer;

#if !(GLIB_CHECK_VERSION(2, 36, 0))
	g_type_init();
#endif

	bool is_running = false;
	int counter = MAX_COUNTER;
	ret = app_control_create(&__g_app_control_handler);

	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	ret = event_add_event_handler("event.org.tizen.eventsender.user_event", utc_event_cb_with_valid_check,
			"SYSTEM_EVENT_BATTERY_CHARGER_STATUS", &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	__correct_value = "wrong value";

	ret = app_control_set_app_id(__g_app_control_handler , __sender_app_id);
	assert_eq_with_exit(ret, APP_CONTROL_ERROR_NONE);

	do {

		ret = app_manager_is_running(__sender_app_id, &is_running);
		if(ret == APP_MANAGER_ERROR_NONE)
		{
			if (!is_running) {
				ret = app_control_send_launch_request(__g_app_control_handler , NULL , NULL);
				if ( ret != APP_CONTROL_ERROR_NONE )
				{
					sleep(1);
				}
			}
		}

	} while (--counter > 0 && !is_running);

	if (!is_running) {
		normal_exit(1);
	} else {

		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = timer_handler;
		sigaction(SIGALRM, &sa, NULL);

		timer.it_value.tv_sec = 1;
		timer.it_value.tv_usec = 0;

		timer.it_interval.tv_sec = 1;
		timer.it_interval.tv_usec = 0;

		setitimer(ITIMER_REAL, &timer, NULL);
	}

	return 0;
}

/**
 * @testcase		utc_application_app_event_publish_trusted_app_event_n5
 * @since_tizen		2.4
 * @type		Negative
 * @description		Sends the User-Event to trusted receiver-applications.
 * @scenario	Launchs the non trusted receiver-application and adds event handler.
 *			Sends trusted events to receiver application and wait for reply event from receiver application.
 *			Event handler will not be invoked.
 */
int utc_application_app_event_publish_trusted_app_event_n5(void)
{
	int ret = EVENT_ERROR_NONE;
	struct sigaction sa;
	struct itimerval timer;
	bundle *event_data = NULL;
	char local_event_name[PATH_MAX];

	__run_receiver_app(__non_trusted_receiver);

	ret = event_add_event_handler("event.org.tizen.event_receiver2.user_event",
			utc_event_cb_with_valid_check, NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, user_data_key, user_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	__correct_value = "wrong value";

	__get_event_name(local_event_name);
	ret = event_publish_trusted_app_event(local_event_name, event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = bundle_free(event_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = timer_handler;
	sigaction(SIGALRM, &sa, NULL);

	timer.it_value.tv_sec = 1;
	timer.it_value.tv_usec = 0;

	timer.it_interval.tv_sec = 1;
	timer.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &timer, NULL);

	return 0;
}

/**
 * @testcase		utc_application_app_event_keep_last_event_data_p
 * @since_tizen	3.0
 * @type			Positive
 * @description	Request to keep last event data for user-event
 * @scenario		Request to keep last event data for "event.core.application-tests.user_event".
 *				Sends the event with user_data and add the event handler for the event,
 *				and checks the return value
 */
int utc_application_app_event_keep_last_event_data_p(void)
{
	int ret = EVENT_ERROR_NONE;
	bundle *event_data = NULL;

	ret = event_keep_last_event_data("event.core.application-tests.user_event");
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	event_data = bundle_create();
	assert_neq_with_exit(event_data, NULL);

	ret = bundle_add_str(event_data, user_data_key, user_data);
	assert_eq_with_exit(ret, BUNDLE_ERROR_NONE);

	__correct_value = user_data;
	ret = event_publish_app_event("event.core.application-tests.user_event", event_data);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	ret = event_add_event_handler("event.core.application-tests.user_event",
			utc_event_cb_with_valid_check, NULL, &event_handler);
	assert_eq_with_exit(ret, EVENT_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_application_app_event_keep_last_event_data_n
 * @since_tizen	3.0
 * @type			Negative
 * @description	Request to keep last event data for user-event
 * @scenario		Call event_keep_last_event_data() with the invalid parameter
 *				that event_name is NULL, and then checks the return value.
 */
int utc_application_app_event_keep_last_event_data_n(void)
{
	int ret = EVENT_ERROR_NONE;

	ret = event_keep_last_event_data(NULL);
	assert_eq_with_exit(ret, EVENT_ERROR_INVALID_PARAMETER);
	normal_exit(0);

	return 0;
}
