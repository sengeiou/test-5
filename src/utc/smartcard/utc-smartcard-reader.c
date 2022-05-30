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

static int reader;
static int _init_state = SMARTCARD_ERROR_NONE;

/**
 * @function		utc_smartcard_reader_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_reader_startup(void)
{
	int length;
	int* readers;

	_init_state = smartcard_initialize();
	if(SMARTCARD_ERROR_NONE == _init_state)
	{
		_init_state = smartcard_get_readers(&readers, &length);
		if(SMARTCARD_ERROR_NONE == _init_state && length > 0)
			reader = readers[0];
		else
			_init_state = SMARTCARD_ERROR_GENERAL;
	}
}

/**
 * @function		utc_smartcard_reader_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_reader_cleanup(void)
{
	smartcard_deinitialize();
}

/**
 * @testcase		utc_smartcard_smartcard_reader_get_name_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_get_name_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	char *reader_name;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_get_name(reader, &reader_name);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_reader_get_name_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_get_name_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_get_name(reader, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_reader_is_secure_element_present_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_is_secure_element_present_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	bool is_present = false;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_is_secure_element_present(reader, &is_present);
	// process end

	//if ispresent is true
	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_reader_is_secure_element_present_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_is_secure_element_present_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_is_secure_element_present(reader, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_reader_open_session_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_open_session_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	int session;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_open_session(reader, &session);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_reader_open_session_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_open_session_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_open_session(reader, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_reader_close_sessions_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_close_sessions_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_close_sessions(reader);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_reader_close_sessions_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_reader_close_sessions_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_close_sessions(0);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

static void __reader_event_cb(int reader_id, smartcard_reader_event_type_e event_type, void *user_data)
{
	return;
}

/**
 * @testcase		utc_smartcard_smartcard_reader_close_sessions_p
 * @since_tizen		3.0
 * @description
 */
int utc_smartcard_smartcard_reader_set_event_cb_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_set_event_cb(__reader_event_cb, NULL);
	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);

	ret = smartcard_reader_unset_event_cb();
	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	// process end

	return 0;

}

/**
 * @testcase		utc_smartcard_smartcard_reader_close_sessions_n
 * @since_tizen		3.0
 * @description
 */
int utc_smartcard_smartcard_reader_set_event_cb_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_reader_set_event_cb(NULL, NULL);

	if (ret == SMARTCARD_ERROR_INVALID_PARAMETER) {
		smartcard_deinitialize();
		ret = smartcard_reader_unset_event_cb();

		SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NOT_INITIALIZED);
	} else {
		SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	}
	// process end

	return 0;
}
