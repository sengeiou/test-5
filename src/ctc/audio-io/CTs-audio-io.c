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
#include "CTs-audio-io-common.h"

/** @addtogroup ctc-audio-io
* @ingroup		ctc
* @{
*/
 
//& set: AudioIo

/**
* @function 		CTs_audio_io_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_audio_io_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		CTs_audio_io_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_audio_io_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Audio_IO_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-audio-io-testcases
* @brief 		Integration testcases for module audio-io
* @ingroup		ctc-audio-io
*  @{
*/

//& purpose: It checks whether Mobile device implementations accurately report the presence or absence of a microphone. 
//& eType: auto
/**
* @testcase	 		CTc_audio_input_check_microphone_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer         SRID(gupta.sanjay)
* @type				auto
* @scenario			Check the microphone feature in device
* @apicovered		system_info_get_platform_bool
* @passcase			If presence or absence of microphone is accurately reported
* @failcase			If presence or absence of microphone is not accurately reported
* @precondition		NA
* @postcondition	NA
*/
int CTc_audio_input_check_microphone_p(void)
{
	START_TEST;

	bool bFeatureSupported = false;

	int nRet = system_info_get_platform_bool(MICROPHONE_FEATURE, &bFeatureSupported);
	if ( nRet != SYSTEM_INFO_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Presence or Absence of microphone is not accurately reported, error returned = %s\\n", __LINE__, API_NAMESPACE, TCTSystemInfoGetError(nRet));
		return 1;
	}

	FPRINTF("[Line : %d][%s] Presence or Absence of microphone is accurately reported\\n", __LINE__, API_NAMESPACE);
	if ( bFeatureSupported )
	{
		FPRINTF("[Line : %d][%s] Microphone feature is present\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Microphone feature is absent\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}

/** @} */ //end of ctc-audio-io-testcases
/** @} */ //end of ctc-audio-io