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
#ifndef _CTS_AUDIO_IO_COMMON_H_
#define _CTS_AUDIO_IO_COMMON_H_

#include "tct_common.h"

#include <media/audio_io.h>

/** @addtogroup ctc-audio-io
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE		    	"AUDIO_IO_CTC"
#define MEMLOG						20
#define MAX_BLOCK_SIZE          	100
#define MICROPHONE_FEATURE			"http://tizen.org/feature/microphone"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

/** @} */ //end of ctc-audio-io

#endif  //_CTS_AUDIO_IO_COMMON_H_
