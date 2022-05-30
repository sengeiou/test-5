//
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
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
#ifndef _CTS_MEDIACODEC_COMMON_H_
#define _CTS_MEDIACODEC_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include <media_codec.h>

/** @addtogroup ctc-mediacodec
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE		"MEDIA_CODEC_CTC"
#define MEDIACODEC_FEATURE		"http://tizen.org/feature/multimedia.media_codec"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bMediaCodecNotSupported)\
	{\
		FPRINTF("[Line : %d][%s] Required feature of mediacodec is not supported. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( g_bMismatch )\
	{\
		FPRINTF("[Line : %d][%s] MediaCodec_Check_System_Info_Feature_Supported and mediacodec_create returned different value. So leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

//Add helper function declarations here

char *MediaCodecGetCodecName(int nType);
char *MediaCodecGetCodecSupportedTypeName(int nIndex);

/** @} */ //end of ctc-mediacodec

#endif  //_CTS_MEDIACODEC_COMMON_H_