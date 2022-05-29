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

#ifndef _UTC_MEDIA_CONTROLLER_COMMON_H_
#define _UTC_MEDIA_CONTROLLER_COMMON_H_

#include "assert.h"
#include <glib.h>


//& set: ImageUtilCommon

#define IMAGEUTIL_SAFE_FREE(src) {\
		if ( src != NULL ) {\
				free(src); \
				src = NULL; \
		}\
	}

#define IMAGEUTIL_SAFE_G_FREE(src) {\
		if ( src != NULL ) {\
				g_free(src); \
				src = NULL; \
		}\
	}

#define retval_if_neq(var, ref) \
    do { \
        if (var != ref) { \
            fprintf(stderr, \
                "\\n[TCT][%s][Line : %d] Assert fail; Values (%s == 0x%x) and (%s == 0x%x) are not equal\\n", \
                __FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
            return var; \
        } \
    } while (0)

char *_utc_get_test_path(const char *base_dir, const char *filename);
int _utc_decode_from_file(const char *path, image_util_image_h *decoded_image);
int _utc_encode_to_buffer(image_util_type_e type, image_util_image_h decoded_image, unsigned char **buffer, size_t *buffer_size);

#endif /* _UTC_MEDIA_CONTROLLER_COMMON_H_ */
