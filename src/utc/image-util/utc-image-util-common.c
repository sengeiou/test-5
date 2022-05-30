//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include <image_util.h>

#include "tct_common.h"
#include "utc-image-util-common.h"

/** @addtogroup utc-image-util
* @ingroup		utc
* @{
*/

//Add helper function definitions here

/**
* @function 	__utc_get_test_path
* @description	Get the test file path
* @parameter	[IN] base_dir, 		base directory
* 				[IN] filename, 		filename
* @return		NA
*/

char *_utc_get_test_path(const char *base_dir, const char *filename)
{
	if (!base_dir || !strlen(base_dir) ||
		!filename || !strlen(filename))
		return NULL;

	return g_strdup_printf("%s/res/%s", base_dir, filename);
}

int _utc_decode_from_file(const char *path, image_util_image_h *decoded_image)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_decode_h decoder = NULL;

	ret = image_util_decode_create(&decoder);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%d:%s] image_util_decode_create failed! %d \\n", __LINE__, __FUNCTION__, ret);
		return ret;
	}

	ret = image_util_decode_set_input_path(decoder, path);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%d:%s] image_util_decode_set_input_path failed! %d \\n", __LINE__, __FUNCTION__, ret);
		image_util_decode_destroy(decoder);
		return ret;
	}

	ret = image_util_decode_run2(decoder, decoded_image);
	if (ret != IMAGE_UTIL_ERROR_NONE)
		FPRINTF("[%d:%s] image_util_decode_run2 failed! %d \\n", __LINE__, __FUNCTION__, ret);

	image_util_decode_destroy(decoder);

	return ret;
}

int _utc_encode_to_buffer(image_util_type_e type, image_util_image_h decoded_image, unsigned char **buffer, size_t *buffer_size)
{
	int ret = IMAGE_UTIL_ERROR_NONE;
	image_util_encode_h encoder = NULL;

	ret = image_util_encode_create(type, &encoder);
	if (ret != IMAGE_UTIL_ERROR_NONE) {
		FPRINTF("[%d:%s] image_util_encode_create failed! %d \\n", __LINE__, __FUNCTION__, ret);
		return ret;
	}

	ret = image_util_encode_run_to_buffer(encoder, decoded_image, buffer, buffer_size);
	if (ret != IMAGE_UTIL_ERROR_NONE)
		FPRINTF("[%d:%s] image_util_encode_run_to_buffer failed! %d \\n", __LINE__, __FUNCTION__, ret);

	image_util_encode_destroy(encoder);

	return ret;
}

/**
* @}
*/
