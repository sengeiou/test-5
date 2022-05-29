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
#include "ITs-media-key-common.h"

/** @addtogroup itc-media-key
* @ingroup		itc
* @{
*/

//& set: MediaKey

/**
* @function 		ITs_media_key_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_media_key_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Media_Key_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_media_key_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_media_key_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Media_Key_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 			media_key_event_callback
* @description 			Callback function for any media-key event
* @parameter	[IN]	media_key_e
* @parameter	[IN]	media_key_event_e
*           	[IN]	void *user_data
* @return				NA
*/ 
void media_key_event_callback(media_key_e key, media_key_event_e status, void *user_data)
{
	FPRINTF("[Line : %d][%s] media_key_event_callback invoked, media-key = %d, status = %d\\n", __LINE__, API_NAMESPACE, key, status);
}

/** @addtogroup	itc-media-key-testcases
* @brief 		Integration testcases for module media-key
* @ingroup		itc-media-key
* @{
*/

//& type: auto
//& purpose: Registers and then unregisters a change event callback for all media keys
/**
* @testcase 			ITc_media_key_reserve_release_p
* @since_tizen			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers and then unregisters a change event callback for all media keys
* @scenario				Registers change event callback\n
* 						Unregisters change event callback
* @apicovered			media_key_release, media_key_reserve						
* @passcase				When media_key_release and  media_key_reserve are successful.
* @failcase				If target api fails.
* @precondition			None
* @postcondition		None
*/
int ITc_media_key_reserve_release_p(void)
{
	START_TEST;

	int nRetVal = media_key_reserve(media_key_event_callback, NULL);
	PRINT_RESULT(MEDIA_KEY_ERROR_NONE, nRetVal, "media_key_reserve", Media_KeyGetError(nRetVal));

	// Give some sleep between register and release
	usleep(2000);

	nRetVal = media_key_release();
	PRINT_RESULT(MEDIA_KEY_ERROR_NONE, nRetVal, "media_key_release", Media_KeyGetError(nRetVal));	

	return 0;
}

/** @} */ //end of itc-media-key
/** @} */ //end of itc-media-key-testcases