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
#ifndef __UTC_CONTEXT_COMMON_H__
#define __UTC_CONTEXT_COMMON_H__

#include "assert.h"
#include "tct_common.h"
#include <dlog.h>

#define PRINT_INFO(fmt, args...) {\
	fprintf(stderr, "[Info][Line: %d] "fmt"\\n", __LINE__, ##args); \
	PRINT_UTC_LOG("[Info][Line: %d] "fmt"\\n", __LINE__, ##args); \
	dlog_print (DLOG_INFO, "core-context-tests", "[%s:%d] "fmt"\n", __func__, __LINE__, ##args); \
}

#define HISTORY_ASSERT_EQ_WITH_CHECK_SUPPORTED(CONDITION, VALUE1, VALUE2) \
		do { \
			if (CONDITION) { \
				assert_eq(VALUE1, VALUE2); \
			} else { \
				assert_eq(VALUE1, CONTEXT_HISTORY_ERROR_NOT_SUPPORTED); \
			} \
		} while (0)

#define HISTORY_ASSERT_GEQ_IF_SUPPORTED(CONDITION, VALUE1, VALUE2) \
		do { \
			if (CONDITION) { \
				assert_geq(VALUE1, VALUE2); \
			} \
		} while (0)

#define HISTORY_ASSERT_IF_SUPPORTED(CONDITION, VALUE1) \
		do { \
			if (CONDITION) { \
				assert(VALUE1); \
			} \
		} while (0)

#define TRIGGER_ASSERT_EQ_WITH_CHECK_SUPPORTED(CONDITION, VALUE1, VALUE2) \
		do { \
			if (CONDITION) { \
				assert_eq(VALUE1, VALUE2); \
			} else { \
				assert_eq(VALUE1, CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED); \
			} \
		} while (0)

#endif // __UTC_CONTEXT_COMMON_H__
