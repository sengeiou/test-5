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
#include "CTs-sound-manager-common.h"

/** @addtogroup ctc-sound-manager
* @ingroup		ctc
* @{
*/

//& set: SoundManager

/**
* @function 		CTs_sound_manager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_sound_manager_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		CTs_sound_manager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_sound_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	ctc-sound-manager-testcases
* @brief 		Integration testcases for module sound-manager
* @ingroup		ctc-sound-manager
* @{
*/

//& purpose: To get the list of audio output devices connected
//& type: auto
/**
* @testcase 		CTc_sound_manager_get_audio_output_device_list_p
* @since_tizen		2.3
* @author			SRID(a.pandia1)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Gets the list of audio output devices connected
* @apicovered		sound_manager_get_device_list
* @passcase			When API return SOUND_MANAGER_ERROR_NONE and the list of audio output devices is not NULL
* @failcase			When API doesn't return SOUND_MANAGER_ERROR_NONE or the list of audio output devices is NULL
* @precondition		None
* @postcondition	None
*/
int CTc_sound_manager_get_audio_output_device_list_p(void)
{
	START_TEST;

	sound_device_list_h audioOutDeviceList = NULL;
	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_OUT_MASK ;		/*< Mask for output devices */

	int nRetVal = sound_manager_get_device_list(e_device_mask, &audioOutDeviceList);

	if( nRetVal == SOUND_MANAGER_ERROR_NO_DATA )
	{
		return 0;
	}

	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRetVal, "sound_manager_get_device_list", SoundManagerGetError(nRetVal))

	if ( audioOutDeviceList == NULL )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_device_list failed, device list returned is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FPRINTF("[Line : %d][%s] Target supports at least one audio output device\\n", __LINE__, API_NAMESPACE);
	return 0;
}

/** @} */ //end of ctc-sound-manager
/** @} */ //end of ctc-sound-manager-testcases
