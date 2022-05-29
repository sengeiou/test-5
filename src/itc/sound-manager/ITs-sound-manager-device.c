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
#include "ITs-sound-manager-common.h"
#define TESTFILE					"WavPlayerTest.wav"
/** @addtogroup itc-sound-manager
*  @ingroup itc
*  @{
*/
//& set: SoundManager
bool g_bWavPlayerPlaybackCompletedCallback;
static GMainLoop *g_pMainLoop;
static bool g_bCallbackResult ;
static bool g_bSupportedFeatureMicrophone ;

/**
* @function 		test_sound_manager_device_connected_cb
* @description	 	callback function for volume change
* @parameter		device : sound device, is_connected: connection state, user_data : user data
* @return 			NA
*/
static void test_sound_manager_device_connected_cb(sound_device_h device, bool is_connected, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_manager_device_connected_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Outside from callback \"test_sound_manager_device_connected_cb\"\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		test_sound_device_state_changed_cb
* @description	 	callback function for volume change
* @parameter		sound_device_h device, sound_device_state_e state, void *user_data
* @return 			NA
*/
static void test_sound_device_state_changed_cb(sound_device_h device, sound_device_state_e state, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_device_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Outside from callback \"test_sound_device_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}
/**
* @function             sound_device_running_changed_cb
* @description          called when state of a sound device was changed
* @parameter            sound_device_h device, bool is_running, void *user_data
* @return                       NA
*/
static void test_sound_device_running_changed_cb(sound_device_h device, bool is_running, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_device_running_changed_cb\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;
	if(is_running == true)
	{
		FPRINTF("[Line : %d][%s] Device is running\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] Device is not running\n", __LINE__, API_NAMESPACE);
	}
	QUIT_GMAIN_LOOP;
}
/**
* @function				WavPlayerPlaybackCompletedCallback
* @description			To Call when transcoding is finished just before storing in the file
* @parameter	[IN]	Wav Player ID
* @parameter	[IN]	The user data passed from the callback registration function
* @return				NA
*/
void WavPlayerPlaybackCompletedCallback(int nId, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] WavPlayerPlaybackCompletedCallback is called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bWavPlayerPlaybackCompletedCallback = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}
/**
* @function 		test_sound_manager_stream_focus_state_changed_cb
* @description	 	callback function
* @parameter		sound_stream_info_h stream_info, sound_stream_focus_mask_e focus_mask, sound_stream_focus_state_e focus_state, sound_stream_focus_change_reason_e reason, int sound_behavior, const char *extra_info, void *user_data
* @return 			NA
*/
static void test_sound_manager_stream_focus_state_changed_cb(sound_stream_info_h stream_info,
															sound_stream_focus_mask_e focus_mask,
															sound_stream_focus_state_e focus_state,
															sound_stream_focus_change_reason_e reason,
															int sound_behavior,
															const char *extra_info,
															void *user_data)
{
	g_bCallbackResult = true;
	FPRINTF("[Line : %d][%s] Inside callback \"test_sound_manager_stream_focus_state_changed_cb\"\\n", __LINE__, API_NAMESPACE);
}
/**
* @function 		ITs_sound_manager_device_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_device_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bCallbackResult = false;
	g_bSupportedFeatureMicrophone = TCTCheckSystemInfoFeatureSupported(FEATURE_MICROPHONE, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_sound_manager_device_cleanup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_device_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& purpose: To get the next item of the device list and free it
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_next_device_free_device_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			To get the next item of the device list and free it
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list and free it
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device,sound_manager_free_device_list
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_next_device_free_device_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_mask_e e_device_mask = SOUND_DEVICE_ALL_MASK;
	sound_device_h hDevice = NULL;

	int nRet = sound_manager_get_device_list(e_device_mask, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));


	return 0;
}
#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
//& purpose: To get the previous item of the device list
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_prev_device_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the next item of the device list
* @scenario				Get the list of devices connected\n
*						Get the previous item of the device list
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_prev_device
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_prev_device_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_mask_e e_device_mask = SOUND_DEVICE_ALL_MASK;
	sound_device_h hDevice = NULL;

	int nRet = sound_manager_get_device_list(e_device_mask, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	//to come on root node a call is required
	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		nRet = sound_manager_free_device_list(deviceList);
		PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	hDevice = NULL;
	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		nRet = sound_manager_get_prev_device(deviceList, &hDevice);
		PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NO_DATA, nRet, "sound_manager_get_prev_device\\n", SoundManagerGetError(nRet));
		nRet = sound_manager_free_device_list(deviceList);
		PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	hDevice = NULL;
	nRet = sound_manager_get_prev_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_prev_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_prev_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_prev_device");

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}
#endif //End MOBILE or Wearable
#ifdef TV	//Starts TV
//& purpose: To get the previous item of the device list
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_prev_device_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the next item of the device list
* @scenario				Get the list of devices connected\n
*						Get the previous item of the device list
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_prev_device
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_prev_device_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_mask_e e_device_mask = SOUND_DEVICE_ALL_MASK;
	sound_device_h hDevice = NULL;

	int nRet = sound_manager_get_device_list(e_device_mask, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	//to come on root node a call is required
	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	hDevice = NULL;
	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	hDevice = NULL;
	nRet = sound_manager_get_prev_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_prev_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		deviceList = NULL;
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_prev_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_prev_device");

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}
#endif  //TV	//End TV
//& purpose: To get the type of the device
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_type_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the type of the device
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list\n
*						Get the type of the device
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_device_type
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_type_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_type_e eType = -1;
	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &deviceList);
	#endif  //TV	//End TV

	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_get_device_type (hDevice, &eType);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet));

	if (  eType < SOUND_DEVICE_BUILTIN_SPEAKER || eType > SOUND_DEVICE_USB_AUDIO )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_device_type failed, device type is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To get the io direction of the device
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_io_direction_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the type of the device
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list\n
*						Get the io direction of the device
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_device_io_direction
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_io_direction_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_io_direction_e eIoDirection = -1;

	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &deviceList);
	#endif  //TV	//End TV

	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet));

	if ( eIoDirection < SOUND_DEVICE_IO_DIRECTION_IN || eIoDirection > SOUND_DEVICE_IO_DIRECTION_BOTH )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_device_io_direction failed, sound device direction is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To get the id of the device
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_id_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the type of the device
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list\n
*						Get the id of the device
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_device_id
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_id_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_h hDevice = NULL;
	int nId = -1;
	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &deviceList);
	#endif  //TV	//End TV

	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_get_device_id(hDevice, &nId);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_id", SoundManagerGetError(nRet));
	if ( nId == -1 )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_device_id failed, sound device id is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To get the name of the device
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_name_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the type of the device
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list\n
*						Get the name of the device
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_device_name
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_name_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_h hDevice = NULL;
	char *pszName = NULL;
	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &deviceList);
	#endif  //TV	//End TV

	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_get_device_name(hDevice, &pszName);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_name", SoundManagerGetError(nRet));
	CHECK_HANDLE(pszName, "sound_manager_get_device_name");
	return 0;
}

//& purpose: To get the state of the device
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_state_p
* @since_tizen 			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To get the type of the device
* @scenario				Get the list of devices connected\n
*						Get the next item of the device list\n
*						Get the state of the device
* @apicovered			sound_manager_get_device_list, sound_manager_get_next_device, sound_manager_get_device_state
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_state_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h deviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_state_e eState = -1;

	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	int nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &deviceList);
	#endif  //TV	//End TV

	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &hDevice);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDevice, "sound_manager_get_next_device");

	nRet = sound_manager_get_device_state(hDevice, &eState);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_state", SoundManagerGetError(nRet));

	if ( eState != SOUND_DEVICE_STATE_DEACTIVATED && eState != SOUND_DEVICE_STATE_ACTIVATED )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_device_state failed, sound device state is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}

#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
//& purpose: To get the list of devices connected
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_list_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To get the list of devices connected
* @scenario				Get the list of devices connected
* @apicovered			sound_manager_get_device_list
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_list_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumCount = 0;
	sound_device_list_h deviceList = NULL;

	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_IN_MASK;
	int arrSoundDeviceMask[] = {
		SOUND_DEVICE_IO_DIRECTION_IN_MASK,		/**< Mask for input devices */
		SOUND_DEVICE_IO_DIRECTION_OUT_MASK,		/**< Mask for output devices */
		SOUND_DEVICE_IO_DIRECTION_BOTH_MASK,	/**< Mask for input/output devices (both directions are available) */
		SOUND_DEVICE_TYPE_INTERNAL_MASK,		/**< Mask for built-in devices */
		SOUND_DEVICE_TYPE_EXTERNAL_MASK,		/**< Mask for external devices */
		SOUND_DEVICE_ALL_MASK					/**< Mask for all devices */
	};
	int nSoundDeviceMaskCount = sizeof(arrSoundDeviceMask) / sizeof(arrSoundDeviceMask[0]);

	for ( nEnumCount = 0;nEnumCount < nSoundDeviceMaskCount;nEnumCount++ )
	{
		e_device_mask = arrSoundDeviceMask[nEnumCount];
		nRet = sound_manager_get_device_list(e_device_mask, &deviceList);
		if(nRet != SOUND_MANAGER_ERROR_NO_DATA)
		{
			PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
			CHECK_HANDLE(deviceList, "sound_manager_get_device_list");
		}
	}

	return 0;
}
#endif//MOBILE or TIZENIOT or WEARABLE
#ifdef TV	//Starts TV
//& purpose: To get the list of devices connected
//& type: auto
/**
* @testcase 			ITc_sound_manager_get_device_list_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To get the list of devices connected
* @scenario				Get the list of devices connected
* @apicovered			sound_manager_get_device_list
* @apicovered			sound_manager_get_device_list
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_device_list_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_device_list_h deviceList = NULL;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &deviceList);
	if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		return 0;
	}
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	return 0;
}
#endif//End TV


//& purpose: Gets current media playback device type
//& type : auto
/**
* @testcase 			ITc_sound_manager_get_current_media_playback_device_type_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Gets current media playback device type
* @scenario
* 						Create stream info handle\n
*						Acquire recording focus\n
*						Get the current recording focus
* @apicovered			sound_manager_get_current_media_playback_device_type, sound_manager_get_device_list
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/

int ITc_sound_manager_get_current_media_playback_device_type_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_device_type_e edevice_type;
	sound_device_list_h  hlist = NULL;
	//Target API
	nRet = sound_manager_get_current_media_playback_device_type(&edevice_type);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		/* check whether playback device exists, NO_DATA should be returned also */
		nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_OUT_MASK, &hlist);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NO_DATA, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	}
	else
	{
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_current_media_playback_device_type", SoundManagerGetError(nRet));
		if(edevice_type < SOUND_DEVICE_BUILTIN_SPEAKER || edevice_type > SOUND_DEVICE_BLUETOOTH_VOICE)
		{
			FPRINTF("\\n[Line : %d][%s]sound_manager_get_current_media_playback_device_type wrong value returned ",__LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}
//& purpose: To check register/unregister a callback function to be invoked when the connection state of a sound device was changed.
//& type : auto
/**
* @testcase 			ITc_sound_manager_add_remove_device_connection_changed_cb_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To check register/unregister a callback function to be invoked when the connection state of a sound device was changed.
* @scenario				register a callback function on changing the connection state of sound device\n
* 						unregister a callback function on changing the connection state of sound device
* @apicovered			sound_manager_add_device_connection_changed_cb, sound_manager_remove_device_connection_changed_cb
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_add_remove_device_connection_changed_cb_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0;

	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_IN_MASK;
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_OUT_MASK;
	#endif  //TV	//End TV

	int arrSoundDeviceMask[] = {
		SOUND_DEVICE_IO_DIRECTION_IN_MASK,		/**< Mask for input devices */
		SOUND_DEVICE_IO_DIRECTION_OUT_MASK,		/**< Mask for output devices */
		SOUND_DEVICE_IO_DIRECTION_BOTH_MASK,	/**< Mask for input/output devices (both directions are available) */
		SOUND_DEVICE_TYPE_INTERNAL_MASK,		/**< Mask for built-in devices */
		SOUND_DEVICE_TYPE_EXTERNAL_MASK,		/**< Mask for external devices */
		SOUND_DEVICE_ALL_MASK					/**< Mask for all devices */
	};
	int nSoundDeviceMaskCount = sizeof(arrSoundDeviceMask) / sizeof(arrSoundDeviceMask[0]);

	for ( nEnumLoopCount = 0;nEnumLoopCount < nSoundDeviceMaskCount;nEnumLoopCount++ )
	{
		int nGetID;
		e_device_mask = arrSoundDeviceMask[nEnumLoopCount];

		nRet = sound_manager_add_device_connection_changed_cb(SOUND_DEVICE_ALL_MASK, test_sound_manager_device_connected_cb, NULL, &nGetID);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_connection_changed_cb", SoundManagerGetError(nRet));

		nRet = sound_manager_remove_device_connection_changed_cb(nGetID);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_device_connection_changed_cb", SoundManagerGetError(nRet));

	}
	return 0;
}

//& purpose: To check register/unregister a callback function to be invoked when the state of a sound device was changed.
//& type : auto
/**
* @testcase 			ITc_sound_manager_add_remove_device_state_changed_cb_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			To check register/unregister a callback function to be invoked when the state of a sound device was changed.
* @scenario				register a callback function on changing the information of sound device\n
* 						unregister a callback function on changing the information of sound device
* @apicovered			sound_manager_add_device_state_changed_cb, sound_manager_remove_device_state_changed_cb
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_add_remove_device_state_changed_cb_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0;

	#if defined(MOBILE) ||  defined(TIZENIOT) || defined(WEARABLE) //Starts MOBILE or  TIZENIOT and WEARABLE
	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_IN_MASK;
	#endif//MOBILE or TIZENIOT or WEARABLE
	#ifdef TV	//Starts TV
	sound_device_mask_e e_device_mask = SOUND_DEVICE_IO_DIRECTION_OUT_MASK;
	#endif  //TV	//End TV
	int arrSoundDeviceMask[] = {
		SOUND_DEVICE_IO_DIRECTION_IN_MASK,		/**< Mask for input devices */
		SOUND_DEVICE_IO_DIRECTION_OUT_MASK,		/**< Mask for output devices */
		SOUND_DEVICE_IO_DIRECTION_BOTH_MASK,	/**< Mask for input/output devices (both directions are available) */
		SOUND_DEVICE_TYPE_INTERNAL_MASK,		/**< Mask for built-in devices */
		SOUND_DEVICE_TYPE_EXTERNAL_MASK,		/**< Mask for external devices */
		SOUND_DEVICE_ALL_MASK					/**< Mask for all devices */
	};
	int nSoundDeviceMaskCount = sizeof(arrSoundDeviceMask) / sizeof(arrSoundDeviceMask[0]);

	for ( nEnumLoopCount = 0;nEnumLoopCount < nSoundDeviceMaskCount;nEnumLoopCount++ )
	{
		int nGetID;
		e_device_mask = arrSoundDeviceMask[nEnumLoopCount];
		nRet = sound_manager_add_device_state_changed_cb(SOUND_DEVICE_ALL_MASK, test_sound_device_state_changed_cb, NULL, &nGetID);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_state_changed_cb", SoundManagerGetError(nRet));

		nRet = sound_manager_remove_device_state_changed_cb(nGetID);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_device_state_changed_cb", SoundManagerGetError(nRet));
	}
	return 0;
}
//& purpose: To check if the device is running.
//& type : auto
/**
* @testcase                     ITc_sound_manager_is_device_running_p
* @since_tizen                  5.0
* @author                       SRID(manu.tiwari)
* @reviewer                     SRID(j.abhishek)
* @type                         auto
* @description                  To check if the device is running
* @scenario                     To check is_running status of sound_manager_is_device_running
* @apicovered                   sound_manager_is_device_running
* @passcase                     When API return SOUND_MANAGER_ERROR_NONE
* @failcase                     When API not return SOUND_MANAGER_ERROR_NONE
* @precondition                 None
* @postcondition                None
*/
int ITc_sound_manager_is_device_running_p(void)
{
        START_TEST;
        // Initializing testing variable
        sound_device_list_h hdeviceList = NULL;
        sound_device_mask_e device_mask = SOUND_DEVICE_ALL_MASK;
        sound_device_h hDevice = NULL;
        bool is_running = false;

        int nRet = sound_manager_get_device_list(device_mask, &hdeviceList);
        PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
        CHECK_HANDLE(hdeviceList, "sound_manager_get_device_list");

        nRet = sound_manager_get_next_device(hdeviceList, &hDevice);
        PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet),sound_manager_free_device_list(hdeviceList));
        CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device",sound_manager_free_device_list(hdeviceList));

        nRet = sound_manager_is_device_running(hDevice,&is_running);
        PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_is_device_running\\n", SoundManagerGetError(nRet),sound_manager_free_device_list(hdeviceList));
        if(is_running == false)
	{
		FPRINTF("[%s:%d] Device is not running\\n", __FILE__, __LINE__);
	}
        else
	{
		FPRINTF("[%s:%d] Device is running\\n", __FILE__, __LINE__);
	}
	nRet = sound_manager_free_device_list(hdeviceList);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));
	return 0;
}
//& purpose: Adds a callback function to be invoked when the state of a sound device was changed
//& type : auto
/**
* @testcase                     ITc_sound_manager_add_remove_device_running_changed_cb_p
* @since_tizen                  5.0
* @author                       SRID(manu.tiwari)
* @reviewer                     SRID(j.abhishek)
* @type                         auto
* @description                  Adds and removes a callback function to be invoked when the state of a sound device was changed
* @scenario
* @apicovered                   sound_manager_add_device_running_changed_cb,sound_manager_remove_device_running_changed_cb
* @passcase                     When API return SOUND_MANAGER_ERROR_NONE
* @failcase                     When API not return SOUND_MANAGER_ERROR_NONE
* @precondition                 None
* @postcondition                sound_device_running_changed_cb() will be invoked
*/

int ITc_sound_manager_add_remove_device_running_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1, nTimeoutId = 0, nGetID = -1, nId = -1;
	sound_stream_info_h hStreamInfo = NULL;
	char pPath[PATH_LEN] = {0,};
	sound_device_list_h hdeviceList = NULL;
	sound_device_type_e eDeviceType = -1;
	sound_device_type_e eType = -1;
        sound_device_mask_e eDeviceMask = SOUND_DEVICE_ALL_MASK;
        sound_device_h hDevice = NULL;
        bool bIsRunning = false;

	if ( false == WavPlayerAppendToAppDataPath(TESTFILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__,API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_get_current_media_playback_device_type(&eDeviceType);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_current_media_playback_device_type\\n", SoundManagerGetError(nRet));
	if (  eDeviceType < SOUND_DEVICE_BUILTIN_SPEAKER || eDeviceType > SOUND_DEVICE_BLUETOOTH_VOICE )
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_current_media_playback_device_type failed, device type is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = sound_manager_get_device_list(eDeviceMask, &hdeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hdeviceList, "sound_manager_get_device_list");

	while(eType != eDeviceType)
	{
		nRet = sound_manager_get_next_device(hdeviceList, &hDevice);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device\\n", SoundManagerGetError(nRet),sound_manager_free_device_list(hdeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device",sound_manager_free_device_list(hdeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		if (  eType < SOUND_DEVICE_BUILTIN_SPEAKER || eType > SOUND_DEVICE_BLUETOOTH_VOICE )
		{
			FPRINTF("[Line : %d][%s] sound_manager_get_device_type failed, device type is invalid\\n", __LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hdeviceList);
			return 1;
		}
	}

        nRet = sound_manager_is_device_running(hDevice,&bIsRunning);
        PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_is_device_running\\n", SoundManagerGetError(nRet),sound_manager_free_device_list(hdeviceList));

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamInfo);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
	CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");
	g_bCallbackResult  = false;
	//target API
	nRet = sound_manager_add_device_running_changed_cb(SOUND_DEVICE_ALL_MASK, test_sound_device_running_changed_cb, NULL, &nGetID);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_running_changed_cb", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfo);sound_manager_free_device_list(hdeviceList));
	if ( nGetID < 0 )
	{
		FPRINTF("[Line : %d][%s] sound_manager_add_device_running_changed_cb failed, output parameter is having invalid value\\n", __LINE__, API_NAMESPACE);
		sound_manager_remove_device_running_changed_cb(nGetID);
		sound_manager_destroy_stream_information(hStreamInfo);
		sound_manager_free_device_list(hdeviceList);
		return 1;
	}

	g_bWavPlayerPlaybackCompletedCallback = false;
	nRet = wav_player_start_new(pPath, hStreamInfo, WavPlayerPlaybackCompletedCallback, NULL, &nId);
	PRINT_RESULT_CLEANUP(WAV_PLAYER_ERROR_NONE, nRet, "wav_player_start_new", WavPlayerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfo);sound_manager_remove_device_running_changed_cb(nGetID);sound_manager_free_device_list(hdeviceList));
	if ( nId < 0 )
	{
		FPRINTF("[Line : %d][%s] wav_player_start_new failed, output parameter is having invalid value\\n", __LINE__, API_NAMESPACE);
		sound_manager_remove_device_running_changed_cb(nGetID);
		sound_manager_destroy_stream_information(hStreamInfo);
		sound_manager_free_device_list(hdeviceList);
		return 1;
	}
	nRet = wav_player_stop(nId);
	PRINT_RESULT_CLEANUP(WAV_PLAYER_ERROR_NONE, nRet, "wav_player_stop", WavPlayerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfo);sound_manager_remove_device_running_changed_cb(nGetID));

	if(bIsRunning == false)
	{
		FPRINTF("[%s:%d] Device is not running\\n", __FILE__, __LINE__);
		RUN_POLLING_LOOP;
		if(!g_bCallbackResult)
		{
			FPRINTF("[%s:%d] test_sound_device_running_changed_cb not invoked!!\\n", __FILE__, __LINE__);
			sound_manager_remove_device_running_changed_cb(nGetID);
			sound_manager_destroy_stream_information(hStreamInfo);
			sound_manager_free_device_list(hdeviceList);
			return 1;
		}
	}

	nRet = sound_manager_free_device_list(hdeviceList);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	//Target API
	nRet = sound_manager_remove_device_running_changed_cb(nGetID);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_device_running_changed_cb", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfo));
	nRet = sound_manager_destroy_stream_information(hStreamInfo);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information\\n", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the device's supported sample formats.
//& type : auto
/**
* @testcase 			ITs_sound_manager_get_supported_sample_formats_p
* @since_tizen 			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Gets the device's supported sample formats.
* @apicovered                   sound_manager_get_supported_sample_formats
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_get_supported_sample_formats_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	sound_device_h hDevice = NULL;
	sound_sample_format_e *eSampleFormat = NULL;
	unsigned int nNumOfElems = 0;

	int nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_get_supported_sample_formats(hDevice, &eSampleFormat, &nNumOfElems);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_supported_sample_formats", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
			CHECK_HANDLE_CLEANUP(eSampleFormat, "sound_manager_get_supported_sample_formats", sound_manager_free_device_list(hDeviceList));
			if(nNumOfElems == 0 || nNumOfElems > SAMPLE_FORMAT_COUNT)
			{
				FPRINTF("\\n[Line : %d][%s]sound_manager_get_supported_sample_formats failed, no supported formats",__LINE__, API_NAMESPACE);
				sound_manager_free_device_list(hDeviceList);
				FREE_MEMORY(eSampleFormat);
				return 1;
			}
			sound_manager_free_device_list(hDeviceList);
			FREE_MEMORY(eSampleFormat);
			return 0;
		}
	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
//& purpose: Sets/Gets the device's sample format.
//& type : auto
/**
* @testcase			ITs_sound_manager_set_get_sample_format_p
* @since_tizen			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Sets/Gets the device's sample format.
* @apicovered			sound_manager_get_supported_sample_formats,sound_manager_set_sample_format,sound_manager_get_sample_format
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_set_get_sample_format_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	sound_device_h hDevice = NULL;
	sound_sample_format_e *eSampleFormat = NULL;
	sound_sample_format_e eFindSampleFormat;
	unsigned int nNumOfElems = 0;
	int nRet = -1, nEnumLoopCount = 0;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_get_supported_sample_formats(hDevice, &eSampleFormat, &nNumOfElems);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_supported_sample_formats", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
			CHECK_HANDLE_CLEANUP(eSampleFormat, "sound_manager_get_supported_sample_formats", sound_manager_free_device_list(hDeviceList));
			if(nNumOfElems == 0 || nNumOfElems > SAMPLE_FORMAT_COUNT)
			{
				FPRINTF("\\n[Line : %d][%s]sound_manager_get_supported_sample_formats failed, no supported formats",__LINE__, API_NAMESPACE);
				sound_manager_free_device_list(hDeviceList);
				FREE_MEMORY(eSampleFormat);
				return 1;
			}
			for ( nEnumLoopCount = 0; nEnumLoopCount < nNumOfElems ; nEnumLoopCount++ )
			{
				nRet = sound_manager_set_sample_format(hDevice, eSampleFormat[nEnumLoopCount]);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_sample_format", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eSampleFormat));
				nRet = sound_manager_get_sample_format(hDevice, &eFindSampleFormat);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_sample_format", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eSampleFormat));
				PRINT_RESULT_CLEANUP(eFindSampleFormat, eSampleFormat[nEnumLoopCount], "sound_manager_get_sample_format", "Output parameter doesn't match the set value", sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eSampleFormat));
			}
			sound_manager_free_device_list(hDeviceList);
			FREE_MEMORY(eSampleFormat);
			return 0;
		}
	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
//& purpose: Gets the device's supported sample rates.
//& type : auto
/**
* @testcase 			ITs_sound_manager_get_supported_sample_rates_p
* @since_tizen 			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Gets the device's supported sample rates.
* @apicovered			sound_manager_get_supported_sample_rates
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_get_supported_sample_rates_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	sound_sample_rate_e *eSampleRates = NULL;
	unsigned int nNumOfElems = 0;
	int nRet = -1;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			nRet = sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_get_supported_sample_rates(hDevice, &eSampleRates, &nNumOfElems);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_supported_sample_rates", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
			CHECK_HANDLE_CLEANUP(eSampleRates, "sound_manager_get_supported_sample_rates", sound_manager_free_device_list(hDeviceList));
			if(nNumOfElems == 0 || nNumOfElems > SAMPLE_RATE_COUNT)
			{
				FPRINTF("\\n[Line : %d][%s]sound_manager_get_supported_sample_rates failed, no supported rates",__LINE__, API_NAMESPACE);
				sound_manager_free_device_list(hDeviceList);
				FREE_MEMORY(eSampleRates);
				return 1;
			}
			sound_manager_free_device_list(hDeviceList);
			FREE_MEMORY(eSampleRates);
			return 0;
		}
	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
//& purpose: Sets/Gets the device's sample rates.
//& type : auto
/**
* @testcase 			ITs_sound_manager_set_get_sample_rates_p
* @since_tizen 			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Sets/Gets the device's sample rates.
* @apicovered			sound_manager_get_supported_sample_rates,sound_manager_set_sample_rate,sound_manager_get_sample_rate.
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_set_get_sample_rate_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	sound_sample_rate_e *eOutSampleRates = NULL;
	sound_sample_rate_e eFindSampleRate;
	unsigned int nNumOfElems = 0;
	int nRet=-1, nEnumLoopCount = 0;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_get_supported_sample_rates(hDevice, &eOutSampleRates, &nNumOfElems);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_supported_sample_rates", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
			CHECK_HANDLE_CLEANUP(eOutSampleRates, "sound_manager_get_supported_sample_rates", sound_manager_free_device_list(hDeviceList));
			if(nNumOfElems == 0 || nNumOfElems > SAMPLE_RATE_COUNT)
			{
				FPRINTF("\\n[Line : %d][%s]sound_manager_get_supported_sample_rates failed, no supported rates",__LINE__, API_NAMESPACE);
				sound_manager_free_device_list(hDeviceList);
				FREE_MEMORY(eOutSampleRates);
				return 1;
			}
			for ( nEnumLoopCount = 0; nEnumLoopCount < nNumOfElems ; nEnumLoopCount++ )
			{
				nRet = sound_manager_set_sample_rate(hDevice, eOutSampleRates[nEnumLoopCount]);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_sample_rate", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eOutSampleRates));

				nRet = sound_manager_get_sample_rate(hDevice, &eFindSampleRate);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_sample_rate", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eOutSampleRates));

				PRINT_RESULT_CLEANUP(eFindSampleRate, eOutSampleRates[nEnumLoopCount], "sound_manager_get_sample_rate", "Output parameter doesn't match the set value", sound_manager_free_device_list(hDeviceList);FREE_MEMORY(eOutSampleRates));
			}
			sound_manager_free_device_list(hDeviceList);
			FREE_MEMORY(eOutSampleRates);
			return 0;
		}
	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
//& purpose: Sets/Gets the device's 'avoid resampling' property.
//& type : auto
/**
* @testcase 			ITs_sound_manager_set_get_avoid_resampling_p
* @since_tizen 			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Sets/Gets the device's 'avoid resampling' property.
* @apicovered			sound_manager_set_avoid_resampling,sound_manager_get_avoid_resampling
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_set_get_avoid_resampling_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	bool bSetEnable = true;
	bool bFindEnable = false;
	int nRet = -1;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_set_avoid_resampling(hDevice, bSetEnable);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_avoid_resampling", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

			nRet = sound_manager_get_avoid_resampling(hDevice, &bFindEnable);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_avoid_resampling", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

			PRINT_RESULT_CLEANUP(bFindEnable, bSetEnable, "sound_manager_get_avoid_resampling", "Output parameter doesn't match the set value", sound_manager_free_device_list(hDeviceList));
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
//& purpose: Sets/Gets the restriction of stream type only for media.
//& type : auto
/**
* @testcase 			ITs_sound_manager_set_get_media_stream_only
* @since_tizen 			5.0
* @author			SRID(karanam.s)
* @reviewer			SRID(j.abhishek)
* @type 			auto
* @description			Sets/Gets the restriction of stream type only for media.
* @apicovered			sound_manager_set_media_stream_only,sound_manager_get_media_stream_only
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			device should be #SOUND_DEVICE_USB_AUDIO type and an output device
* @postcondition		N/A
*/
int ITs_sound_manager_set_get_media_stream_only_p(void)
{
	START_TEST;
	// Initializing testing variable
	sound_device_list_h hDeviceList = NULL;
	sound_device_h hDevice = NULL;
	sound_device_type_e eType;
	sound_device_io_direction_e eIoDirection;
	bool bSetEnable = true;
	bool bFindEnable = false;
	int nRet = -1;

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &hDeviceList);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet));
	CHECK_HANDLE(hDeviceList, "sound_manager_get_device_list");

	while(hDeviceList != NULL)
	{
		nRet = sound_manager_get_next_device(hDeviceList, &hDevice);
		if(nRet == SOUND_MANAGER_ERROR_NO_DATA)
		{
			FPRINTF("\\n[Line : %d][%s] Unsupported device , device must be usb audio type and output device",__LINE__, API_NAMESPACE);
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));
		CHECK_HANDLE_CLEANUP(hDevice, "sound_manager_get_next_device", sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_type(hDevice, &eType);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		nRet = sound_manager_get_device_io_direction(hDevice, &eIoDirection);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_io_direction", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

		if(eType == SOUND_DEVICE_USB_AUDIO && eIoDirection == SOUND_DEVICE_IO_DIRECTION_OUT)
		{
			nRet = sound_manager_set_media_stream_only(hDevice, bSetEnable);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_media_stream_only", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

			nRet = sound_manager_get_media_stream_only(hDevice, &bFindEnable);
			PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_media_stream_only", SoundManagerGetError(nRet), sound_manager_free_device_list(hDeviceList));

			PRINT_RESULT_CLEANUP(bFindEnable, bSetEnable, "sound_manager_get_media_stream_only", "Output parameter doesn't match the set value", sound_manager_free_device_list(hDeviceList));
			sound_manager_free_device_list(hDeviceList);
			return 0;
		}

	}
	FPRINTF("\\n[Line : %d][%s] No device attached, usb audio type and output device must be attached",__LINE__, API_NAMESPACE);
	return 0;
}
