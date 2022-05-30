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

#include "utc-smartcard.h"

static int channel;
static int _init_state = SMARTCARD_ERROR_NONE;

/**
 * @function		utc_smartcard_channel_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_channel_startup(void)
{
	_init_state = smartcard_initialize();
}

/**
 * @function		utc_smartcard_channel_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_channel_cleanup(void)
{
	smartcard_deinitialize();
}

/**
 * @testcase		utc_smartcard_smartcard_channel_close_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_close_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_close(0);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_channel_is_basic_channel_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_is_basic_channel_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_is_basic_channel(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_is_closed_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_is_closed_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_is_closed(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_get_select_response_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_get_select_response_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_get_select_response(0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_get_session_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_get_session_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_get_session(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_transmit_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_transmit_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_transmit(0, NULL, 0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_transmit_retrieve_response_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_transmit_retrieve_response_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_transmit_retrieve_response(0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_channel_select_next_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_channel_select_next_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_channel_select_next(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}
