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

void utc_mtp_objectinfo_startup(void)
{
	_init_state = mtp_initialize();
}

void utc_mtp_objectinfo_cleanup(void)
{
	mtp_deinitialize();
}

int utc_mtp_mtp_objectinfo_get_file_name_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_file_name(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_keywords_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_keywords(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_association_desc_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_association_desc(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_association_type_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_association_type(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_size_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_size(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_parent_object_handle_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_parent_object_handle(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_storage_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_storage(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_date_created_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_date_created(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_date_modified_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_date_modified(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_file_type_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_file_type(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_image_bit_depth_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_image_bit_depth(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_image_pix_width_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_image_pix_width(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_image_pix_height_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_image_pix_height(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_thumbnail_size_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_thumbnail_size(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_thumbnail_file_type_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_thumbnail_file_type(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_thumbnail_pix_height_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_thumbnail_pix_height(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

int utc_mtp_mtp_objectinfo_get_thumbnail_pix_width_n(void)
{
	int ret = MTP_ERROR_NONE;
	MTP_ASSERT(_init_state, MTP_ERROR_NONE);

	// process start
	ret = mtp_objectinfo_get_thumbnail_pix_width(0, 0, NULL);
	// process end

	MTP_ASSERT(ret, MTP_ERROR_INVALID_PARAMETER);
	return 0;
}

