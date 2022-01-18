/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include "tizen.h"
#include "private/tizen_error_private.h"

/* END of Tizen Platoform Error */
#define TIZEN_ERROR_MIN_PLATFORM_MODULE -0x0FFFFFFF

// Added by the request of AppFW part (Details: https://reviews.llvm.org/D26028)
__attribute__((tls_model("initial-exec")))
static __thread int tizen_last_error = TIZEN_ERROR_NONE;

int get_last_result(void)
{
	return tizen_last_error;
}

void set_last_result(int err)
{
	tizen_last_error = err;
}

char *_get_error_message(int err_code)
{
	char *msg = NULL;
	int i, arry_cnt;
	arry_cnt = sizeof(err_list) / sizeof(err_info);
	for (i = 0; i < arry_cnt; i++) {
		if (err_code == err_list[i].value) {
			msg = err_list[i].msg;
			break;
		}
	}
	return msg;
}

char *get_error_message(int err_code)
{
	static __thread char msg[512];
	char *tmp = NULL;
	memset(msg, 0x00, sizeof(msg));


	if (err_code == 0) {
		strncpy(msg, "Successful", sizeof(msg));
	} else if (err_code >= TIZEN_ERROR_OWNER_DEAD && err_code < 0) {
		if ((~err_code + 1) == -ENOSYS)
			strncpy(msg, "Invalid operation", sizeof(msg));
		else
			strerror_r(~err_code + 1, msg, sizeof(msg));
	} else if (err_code >= TIZEN_ERROR_MIN_PLATFORM_ERROR && err_code < TIZEN_ERROR_END_OF_COLLECTION) {
		tmp = _get_error_message(err_code);
		if (tmp != NULL)
			strncpy(msg, tmp, sizeof(msg) - 1);
	} else if (err_code >= TIZEN_ERROR_MIN_PLATFORM_MODULE && err_code < -0x009F0000) {
		tmp = _get_error_message(err_code);
		if (tmp != NULL)
			strncpy(msg, tmp, sizeof(msg) - 1);
	} else {;
	}
	return msg;
}
