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

void utc_mtp_storageinfo_startup(void)
{
	_init_state = mtp_initialize();
}

void utc_mtp_storageinfo_cleanup(void)
{
	mtp_deinitialize();
}

int utc_mtp_mtp_storageinfo_get_description_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_storageinfo_get_description(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_storageinfo_get_free_space_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_storageinfo_get_free_space(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_storageinfo_get_max_capacity_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_storageinfo_get_max_capacity(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_storageinfo_get_storage_type_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_storageinfo_get_storage_type(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_storageinfo_get_volume_identifier_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_storageinfo_get_volume_identifier(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}
