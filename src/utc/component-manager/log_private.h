/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
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

#pragma once

#include <stdio.h>
#include <libgen.h>
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "NativeTCT"

#define _E(fmt, ...) do {                                                      \
	dlog_print(DLOG_ERROR, LOG_TAG, "%s: %s(%d) > "fmt,                    \
			basename(__FILE__), __FUNCTION__,                      \
			__LINE__, ##__VA_ARGS__);                              \
	fprintf(stderr, "%s: %s(%d) > "fmt,                                    \
			basename(__FILE__), __FUNCTION__,                      \
			__LINE__, ##__VA_ARGS__);                              \
} while (0)

#define _W(fmt, ...) dlog_print(DLOG_WARN, LOG_TAG, "%s: %s(%d) > "fmt,        \
		basename(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define _I(fmt, ...) dlog_print(DLOG_INFO, LOG_TAG, "%s: %s(%d) > "fmt,        \
		basename(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define _D(fmt, ...) dlog_print(DLOG_DEBUG, LOG_TAG, "%s: %s(%d) > "fmt,       \
		basename(__FILE__), __FUNCTION__, __LINE__, ##__VA_ARGS__)
