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
#ifndef __UCT_IOTCON_COMMON_H__
#define __UCT_IOTCON_COMMON_H__

#include "assert.h"

#define ICUTC_LOG_TAG "NativeTCT"
#include <dlog.h>
#include <net_connection.h>

#define ICUTC_LOG_RED "\033[0;31m"
#define ICUTC_LOG_GREEN "\033[0;32m"
#define ICUTC_LOG_END "\033[0;m"

#define ICUTC_INFO(fmt, arg...) \
	do { \
		dlog_print(DLOG_INFO, ICUTC_LOG_TAG, ICUTC_LOG_GREEN "[%s][Line : %d] " fmt ICUTC_LOG_END, __FILE__, __LINE__, ##arg); \
	} while (0)

#define FN_CALL \
	do { \
		dlog_print(DLOG_INFO, ICUTC_LOG_TAG, ICUTC_LOG_GREEN "[%s][Line : %d] %s >>>>>>> called " ICUTC_LOG_END, __FILE__, __LINE__, __FUNCTION__); \
	} while (0)

#define ICUTC_ERR(fmt, arg...) \
	do { \
		dlog_print(DLOG_ERROR, ICUTC_LOG_TAG, ICUTC_LOG_RED "[%s][Line : %d] " fmt ICUTC_LOG_END, __FILE__, __LINE__, ##arg); \
	} while (0)

#define ICUTC_ERR_CMP(var, ref) \
	if (var != ref) { \
		fprintf(stderr, \
				"\\n[%s][Line : %d] Fail: Values (%s == 0x%x) and (%s == 0x%x)\\n", \
				__FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
		dlog_print(DLOG_ERROR, ICUTC_LOG_TAG, \
				ICUTC_LOG_RED "\\n[%s:%d] Fail: Values (%s == 0x%x) and (%s == 0x%x)\\n" ICUTC_LOG_END, \
				__FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
	} while (0)

#define ICUTC_ASSERT_EQ(var, ref) \
	if (var != ref) { \
		dlog_print(DLOG_ERROR, ICUTC_LOG_TAG, \
				ICUTC_LOG_RED "(%s == 0x%x) and (%s == 0x%x) are not equal" ICUTC_LOG_END, \
				#var, (int)var, #ref, (int)ref); \
		assert_eq(var, ref); \
	} while (0)


#define ICUTC_ASSERT_NEQ(var, ref) \
	if (var == ref) { \
		dlog_print(DLOG_ERROR, ICUTC_LOG_TAG, \
				ICUTC_LOG_RED "(%s == 0x%x) and (%s == 0x%x) are equal" ICUTC_LOG_END, \
				#var, (int)var, #ref, (int)ref); \
		assert_neq(var, ref); \
	} while (0)

#define ICUTC_ASSERT_NULL(var) \
	if (NULL == var) { \
		dlog_print(DLOG_ERROR, ICUTC_LOG_TAG, \
				ICUTC_LOG_RED "%s is NULL" ICUTC_LOG_END, #var); \
		assert(var); \
	} while (0)


#define TIMEOUT_COUNT_MAX 3
#define LOCAL_HOST_ADDRESS "127.0.0.1"
#define LIGHT_RESOURCE_TYPE "core.light"
#define LIGHT_RESOURCE_TYPE2 "core.light2"
#define LIGHT_RESOURCE_TYPE3 "core.light3"
#define LIGHT_RESOURCE_URI "/a/light"
#define LED_RESOURCE_TYPE "core.led"
#define LED_RESOURCE_URI "/a/led"
#define ICUTC_REMOTE_RESOURCE_TIME_INTERVAL 10
#define ICUTC_REMOTE_RESOURCE_TIME_INTERVAL_MAX 3600
#define ICUTC_PRESENCE_INTERVAL 10
#define ICUTC_PRESENCE_INTERVAL_MAX 60*60*24
#define WIFI_FEATURE		    	"http://tizen.org/feature/network.wifi"
#define ETHERNET_FEATURE	    	"http://tizen.org/feature/network.ethernet"

char *g_ipv4_address;
bool g_bFeatureWifi;
bool g_bFeatureEthernet;
connection_h g_conn_h;

void icutc_check_wifi_state();
int icutc_send_ok_response(iotcon_request_h request);
int icutc_create_resource_types(const char *type, iotcon_resource_types_h *types_h);
int icutc_create_resource_interfaces(iotcon_resource_interfaces_h *ifaces_h);
int icutc_create_resource(const char *resource_type, const char *resource_uri,
		iotcon_resource_h *resource_handle);
int icutc_create_attributes(iotcon_attributes_h *attributes);
int icutc_create_representation(iotcon_representation_h *representation);
int icutc_get_svr_db_path(char **path);
void icutc_get_client_ipv4_address(void);
void icutc_free_client_ipv4_address(void);

#endif /* __UCT_IOTCON_COMMON_H__ */
