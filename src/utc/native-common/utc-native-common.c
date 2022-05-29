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
#include <tizen_error.h>
#include <pthread.h>
#include <string.h>

/**
 * @testcase		utc_get_last_result_p
 * @since_tizen		2.3
 * @description 	To check if get_last_result with valid parameters works fine.
 * @scenario		Set the last error and check the last result through get_last_result()
 */
int utc_get_last_result_p(void)
{
	int i = -1;
	int ret = 0;

	for(; i > TIZEN_ERROR_KEY_REJECTED; i--)
	{
		set_last_result(i);
		ret = get_last_result();
		assert_eq(i,ret);
	}
  return 0;
}

void set_error_num_cb(void *ptr)
{
	set_last_result(5);
	pthread_exit(0);
}

/**
 * @testcase		utc_get_last_result_p2
 * @since_tizen		2.3
 * @description		To check if get_last_result works in a thread-safe manner.
 * @scenario    	Get the last result
 * 			Set the error in the other thread
 *                      Get the last result again and comare two return value.
 */
int utc_get_last_result_p2(void)
{
	int ret1,ret2;
	ret1 = get_last_result();
	pthread_t thread1;
	pthread_create (&thread1, NULL, (void *) &set_error_num_cb, NULL);
	pthread_join(thread1, NULL);
	ret2 = get_last_result();
	assert_eq(ret1,ret2);
  return 0;
}

/**
 * @testcase		utc_set_last_result_p
 * @since_tizen		2.3
 * @description		To check if set_last_result with valid parameters works fine.
 * @scenario    	Set an error for invalid parameter and check the last error.
 */
int utc_set_last_result_p(void)
{
	int ret1, ret2;
	ret1 = get_last_result();
	set_last_result(TIZEN_ERROR_INVALID_PARAMETER);
	ret2 = get_last_result();
	assert_neq(ret1,ret2);
  return 0;
}

/**
 * @testcase		utc_get_error_message_p
 * @since_tizen		2.3
 * @description		To check if get_error_message with valid parameters works fine.
 * @scenario   		Check if get_error_message with valid parameters works fine.
 */
int utc_get_error_message_p(void)
{
	int i,ret;
	char *msg = NULL;
	msg = get_error_message(TIZEN_ERROR_NOT_PERMITTED);
	ret = strncmp(msg,"",strlen(msg));
        assert_neq(ret, 0);
        msg = get_error_message(TIZEN_ERROR_ACCOUNT | 0x01);
		ret = strncmp(msg,"",strlen(msg));
		assert_neq(ret, 0);
  return 0;
}

/**
 * @testcase		utc_get_error_message_n
 * @since_tizen		2.3
 * @description		To check if get_error_message with invalid error value returns NULL.
 * @scenario		check if get_error_message with invalid error value returns NULL.
 */
int utc_get_error_message_n(void)
{
	char* msg;
	int ret;
	msg = get_error_message(0x00011111);
	ret = strncmp(msg,"",strlen(msg));
	assert_eq(ret, 0);
	msg = get_error_message(-0x04FFFFFF);
	ret = strncmp(msg,"",strlen(msg));
	assert_eq(ret, 0);
	msg = get_error_message(TIZEN_ERROR_END_OF_COLLECTION + 1);
	ret = strncmp(msg,"",strlen(msg));
	assert_eq(ret, 0);
	return 0;
}
