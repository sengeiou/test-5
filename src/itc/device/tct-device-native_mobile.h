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
#ifndef __TCT_DEVICE_NATIVE_H__
#define __TCT_DEVICE_NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void ITs_device_startup(void);
extern void ITs_device_cleanup(void);
extern void ITs_device_haptic_startup(void);
extern void ITs_device_haptic_cleanup(void);
extern void ITs_device_battery_startup(void);
extern void ITs_device_battery_cleanup(void);
extern void ITs_device_display_startup(void);
extern void ITs_device_display_cleanup(void);
extern void ITs_device_led_startup(void);
extern void ITs_device_led_cleanup(void);
extern void ITs_device_power_startup(void);
extern void ITs_device_power_cleanup(void);
extern void ITs_device_ir_startup(void);
extern void ITs_device_ir_cleanup(void);
extern void ITs_device_thermal_startup(void);
extern void ITs_device_thermal_cleanup(void);

extern int ITc_device_add_remove_callback_p(void);
extern int ITc_device_haptic_vibrate_stop_p(void);
extern int ITc_device_haptic_get_count_p(void);
extern int ITc_device_haptic_open_close_p(void);
extern int ITc_device_battery_get_percent_p(void);
extern int ITc_device_battery_is_charging_p(void);
extern int ITc_device_battery_get_level_status_p(void);
extern int ITc_device_battery_get_health_p(void);
extern int ITc_device_battery_get_power_source_p(void);
extern int ITc_device_battery_get_property_p(void);
extern int ITc_device_battery_get_status_p(void);
extern int ITc_device_display_get_numbers_p(void);
extern int ITc_device_display_get_max_brightness_p(void);
extern int ITc_device_display_set_get_brightness_p(void);
extern int ITc_device_display_change_get_state_p(void);
extern int ITc_device_flash_get_max_brightness_p(void);
extern int ITc_device_flash_set_get_brightness_p(void);
extern int ITc_device_led_play_stop_custom_p(void);
extern int ITc_device_power_request_release_lock_p(void);
extern int ITc_power_wakeup_p(void);
extern int ITc_device_ir_is_available_p(void);
extern int ITc_device_ir_transmit_p(void);
extern int ITc_device_thermal_get_temperature_p(void);

testcase tc_array[] = {
	{"ITc_device_add_remove_callback_p",ITc_device_add_remove_callback_p,ITs_device_startup,ITs_device_cleanup},
	{"ITc_device_haptic_vibrate_stop_p",ITc_device_haptic_vibrate_stop_p,ITs_device_haptic_startup,ITs_device_haptic_cleanup},
	{"ITc_device_haptic_get_count_p",ITc_device_haptic_get_count_p,ITs_device_haptic_startup,ITs_device_haptic_cleanup},
	{"ITc_device_haptic_open_close_p",ITc_device_haptic_open_close_p,ITs_device_haptic_startup,ITs_device_haptic_cleanup},
	{"ITc_device_battery_get_percent_p",ITc_device_battery_get_percent_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_is_charging_p",ITc_device_battery_is_charging_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_get_level_status_p",ITc_device_battery_get_level_status_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_get_health_p",ITc_device_battery_get_health_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_get_power_source_p",ITc_device_battery_get_power_source_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_get_property_p",ITc_device_battery_get_property_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_battery_get_status_p",ITc_device_battery_get_status_p,ITs_device_battery_startup,ITs_device_battery_cleanup},
	{"ITc_device_display_get_numbers_p",ITc_device_display_get_numbers_p,ITs_device_display_startup,ITs_device_display_cleanup},
	{"ITc_device_display_get_max_brightness_p",ITc_device_display_get_max_brightness_p,ITs_device_display_startup,ITs_device_display_cleanup},
	{"ITc_device_display_set_get_brightness_p",ITc_device_display_set_get_brightness_p,ITs_device_display_startup,ITs_device_display_cleanup},
	{"ITc_device_display_change_get_state_p",ITc_device_display_change_get_state_p,ITs_device_display_startup,ITs_device_display_cleanup},
	{"ITc_device_flash_get_max_brightness_p",ITc_device_flash_get_max_brightness_p,ITs_device_led_startup,ITs_device_led_cleanup},
	{"ITc_device_flash_set_get_brightness_p",ITc_device_flash_set_get_brightness_p,ITs_device_led_startup,ITs_device_led_cleanup},
	{"ITc_device_led_play_stop_custom_p",ITc_device_led_play_stop_custom_p,ITs_device_led_startup,ITs_device_led_cleanup},
	{"ITc_device_power_request_release_lock_p",ITc_device_power_request_release_lock_p,ITs_device_power_startup,ITs_device_power_cleanup},
	{"ITc_power_wakeup_p",ITc_power_wakeup_p,ITs_device_power_startup,ITs_device_power_cleanup},
	{"ITc_device_ir_is_available_p",ITc_device_ir_is_available_p,ITs_device_ir_startup,ITs_device_ir_cleanup},
	{"ITc_device_ir_transmit_p",ITc_device_ir_transmit_p,ITs_device_ir_startup,ITs_device_ir_cleanup},
	{"ITc_device_thermal_get_temperature_p",ITc_device_thermal_get_temperature_p,ITs_device_thermal_startup,ITs_device_thermal_cleanup},
	{NULL, NULL}
};

#endif // __TCT_DEVICE_NATIVE_H__
