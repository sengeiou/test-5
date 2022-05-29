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
#ifndef _CTS_IMAGE_UTIL_COMMON_H_
#define _CTS_IMAGE_UTIL_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <image_util.h>
#include <app.h>

/** @addtogroup ctc-image-util
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE				"IMAGE_UTIL_CTC"
#define SAMPLE_FILE 				"ImageUtil_sample.jpg"
#define OUTPUT_FILE_PATH 			(ImageUtilGetDataPath("output.jpg"))
#define MEMLOG 						20
#define MAX_BLOCK_SIZE          	25
#define QUALITY          			100

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

unsigned char * g_upszImgDestBuffer;

//Add helper function declarations here

/**Get Image Util API Error Message*/
char* ImageUtilGetError(int nResult);

/**Decode Image*/
bool ImageUtilDecode(const char *pszImgPath, image_util_colorspace_e eColorSpace, unsigned long *nWidth, unsigned long *nHeight, unsigned char **upszDecodeBuffer, unsigned long long *unDecodeSize);

/**Calculate Buffer Size and Encode Image*/
bool ImageUtilEncode(unsigned long nWidth, unsigned long nHeight, image_util_colorspace_e eColorSpace);

/**Check Function*/
bool ImageUtilCheckFunction(unsigned char *upszImageBuffer, unsigned long nWidth, unsigned long nHeight, unsigned long long unDecodeSize);
char* ImageUtilGetDataPath(char *pszFileName);

/** @} */ //end of ctc-image-util

#endif  //_CTS_IMAGE_UTIL_COMMON_H_
