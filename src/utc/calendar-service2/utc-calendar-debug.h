/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __UTC_CALENDAR_DEBUG_H__
#define __UTC_CALENDAR_DEBUG_H__

#include "tct_common.h"

#define LOG_TAG "NativeTCT_CALENDAR_SERVICE"

#define DBG(fmt, arg...) dlog_print(DLOG_INFO, LOG_TAG, fmt, ##arg)

#define ASSERT_IF(expr, fmt, arg...) do { \
	if (expr) { \
		char buf_assert[1024] = {0}; \
		snprintf(buf_assert, sizeof(buf_assert), fmt, ##arg); \
		return -1; \
	} \
} while (0)

#define CAL_ASSERT_EQ(var, ref, fmt, arg...) do { \
	if (var != ref) \
		dlog_print(DLOG_INFO, LOG_TAG, fmt, ##arg); \
	assert_eq(var, ref); \
} while (0)


#endif /* __UTC_CALENDAR_DEBUG_H__ */

