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

#include "utc-mtp.h"

static int _init_state = MTP_ERROR_NONE;

void _mtp_event_cb(mtp_event_e event, int arg, void *user_data)
{

}

void utc_mtp_manager_startup(void)
{
	_init_state = mtp_initialize();
}

void utc_mtp_manager_cleanup(void)
{
	mtp_deinitialize();
}

int utc_mtp_mtp_initialize_p(void)
{
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	return 0;
}

int utc_mtp_mtp_get_devices_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_get_devices(NULL, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_get_storages_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_get_storages(0, NULL, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_get_object_handles_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_get_object_handles(0, 0, MTP_FILETYPE_ALL, 0, NULL, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_get_object_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_get_object(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_get_thumbnail_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_get_thumbnail(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_add_mtp_event_cb_p(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_add_mtp_event_cb(_mtp_event_cb, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_NONE);
	return 0;
}

int utc_mtp_mtp_add_mtp_event_cb_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_add_mtp_event_cb(NULL, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_remove_mtp_event_cb_p(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_remove_mtp_event_cb(_mtp_event_cb);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_NONE);
	return 0;
}

int utc_mtp_mtp_remove_mtp_event_cb_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_remove_mtp_event_cb(NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_deinitialize_p(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_deinitialize();
	// process end

	MTP_ASSERT(ret, MTP_ERROR_NONE);
	return 0;
}
