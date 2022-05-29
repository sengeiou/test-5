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

static int _init_state = SMARTCARD_ERROR_NONE;

/**
 * @function		utc_smartcard_service_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_service_startup(void)
{
	_init_state = smartcard_initialize();
}

/**
 * @function		utc_smartcard_service_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_smartcard_service_cleanup(void)
{
	smartcard_deinitialize();
}

/**
 * @testcase		utc_smartcard_smartcard_initialize_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_initialize_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_initialize();
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_deinitialize_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_deinitialize_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_deinitialize();
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_deinitialize_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_deinitialize_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	smartcard_deinitialize();
	ret = smartcard_deinitialize();
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NOT_INITIALIZED);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_get_version_p
 * @since_tizen		3.0
 * @description
 */
int utc_smartcard_smartcard_get_version_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	char *version = NULL;

	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_get_version(&version);

	if (version != NULL)
		free(version);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_get_version_n
 * @since_tizen		3.0
 * @description
 */
int utc_smartcard_smartcard_get_version_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_get_version(NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_get_readers_p
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_get_readers_p(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	int length;
	int* readers;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_get_readers(&readers, &length);
	// process end

	// if length is 0, assert
	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_NONE);
	return 0;
}

/**
 * @testcase		utc_smartcard_smartcard_get_readers_n
 * @since_tizen		2.3
 * @description		
 */
int utc_smartcard_smartcard_get_readers_n(void)
{
	int ret = SMARTCARD_ERROR_NONE;
	SMARTCARD_ASSERT(_init_state, SMARTCARD_ERROR_NONE);

	// process start
	ret = smartcard_get_readers(NULL, NULL);
	// process end

	SMARTCARD_ASSERT(ret, SMARTCARD_ERROR_INVALID_PARAMETER);
	return 0;
}
