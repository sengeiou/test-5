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

static int session;
static int _init_state = SMARTCARD_ERROR_NONE;

/**
 * @function		utc_smartcard_session_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_session_startup(void)
{
	int length;
	int* readers;

	_init_state = smartcard_initialize();
	if(SMARTCARD_ERROR_NONE == _init_state)
	{
		_init_state = smartcard_get_readers(&readers, &length);
		if(SMARTCARD_ERROR_NONE == _init_state && length > 0)
		{
			_init_state = smartcard_reader_open_session(readers[0], &session);
			if(_init_state != SMARTCARD_ERROR_NONE || session == 0)
				_init_state = SMARTCARD_ERROR_GENERAL;
		}
		else
		{
			_init_state = SMARTCARD_ERROR_GENERAL;
		}
	}
}

/**
 * @function		utc_smartcard_session_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_session_cleanup(void)
{
	smartcard_deinitialize();
}

/**
 * @testcase		utc_smartcard_smartcard_session_get_reader_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_get_reader_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	int reader;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_get_reader(session, &reader);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_get_reader_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_get_reader_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_get_reader(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_get_atr_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_get_atr_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	int length;
	unsigned char* atr = NULL;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_get_atr(session, &atr, &length);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_get_atr_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_get_atr_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_get_atr(0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_close_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_close_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	bool is_closed;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_close(session);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_close_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_close_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_close(0);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_is_closed_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_is_closed_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	bool is_closed;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_is_closed(session, &is_closed);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_is_closed_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_is_closed_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_is_closed(0, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_close_channels_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_close_channels_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_close_channels(session);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_close_channels_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_close_channels_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_close_channels(0);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_open_basic_channel_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_open_basic_channel_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_open_basic_channel(0, NULL, 0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_session_open_logical_channel_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_session_open_logical_channel_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_session_open_logical_channel(0, NULL, 0, NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}
