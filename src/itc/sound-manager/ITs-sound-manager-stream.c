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
/** @addtogroup itc-sound-manager
*  @ingroup itc
*  @{
*/
//& set: SoundManager

static bool g_bCallbackResult = false;

static bool g_bSupportedFeatureMicrophone = false;
static sound_behavior_e g_behavior = SOUND_BEHAVIOR_NONE;
static int g_nRet;

/**
* @function 		sound_stream_focus_state_changed_callback
* @description	 	callback function for stream focus state change
* @parameter		stream : stream info, focus_mask, focus_state, reason, sound_behavior, extra info, user data
* @return 			NA
*/
static void sound_stream_focus_state_changed_callback(sound_stream_info_h stream_info,
													sound_stream_focus_mask_e focus_mask,
													sound_stream_focus_state_e focus_state,
													sound_stream_focus_change_reason_e reason,
													int sound_behavior,
													const char *extra_info,
													void *user_data)
{
	g_behavior = sound_behavior;

	FPRINTF("[Line : %d][%s] Inside callback \"sound_stream_focus_state_changed_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;

	FPRINTF("[Line : %d][%s] Outside from callback \"sound_stream_focus_state_changed_callback\"\\n", __LINE__, API_NAMESPACE);

	if( focus_mask < 0 || focus_state < 0)
	{
		FPRINTF("[Line : %d][%s] Invalid output parameters - changed focus: mask(%x), state(%d) (0:released, 1:acquired)\n", __LINE__, API_NAMESPACE, focus_mask, focus_state);
		g_nRet = -1;
	}
}

void sound_stream_ducking_state_changed_callback(sound_stream_ducking_h stream_ducking, bool is_ducked, void *user_data)
{

	FPRINTF("[Line : %d][%s] Inside callback \"sound_stream_ducking_state_changed_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;

}

/**
* @function 		sound_stream_focus_state_watch_callback
* @description	 	callback function for stream focus state watch
* @parameter		stream focus mask: focus mask, focus state: changed focus state, focus change reason: reason for change additional_info, user_data : user data
* @return 			NA
*/
static void sound_stream_focus_state_watch_callback(int id, sound_stream_focus_mask_e changed_focus_mask, sound_stream_focus_state_e changed_focus_state, sound_stream_focus_change_reason_e reason_for_change, const char *additional_info, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside callback \"sound_stream_focus_state_watch_callback\"\\n", __LINE__, API_NAMESPACE);
	g_bCallbackResult = true;

	FPRINTF("[Line : %d][%s] Outside from callback \"sound_stream_focus_state_watch_callback\"\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		ITs_sound_manager_stream_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_stream_startup(void)
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
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_sound_manager_stream_startup\\n", __LINE__, API_NAMESPACE);

	g_bSupportedFeatureMicrophone = TCTCheckSystemInfoFeatureSupported(FEATURE_MICROPHONE, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_sound_manager_stream_startup\\n", __LINE__, API_NAMESPACE);

	return;
}

/**
* @function 		ITs_sound_manager_stream_cleanup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_sound_manager_stream_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sound_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/** @addtogroup itc-sound-manager-testcases
*  @brief 		Integration testcases for module sound-manager
*  @ingroup 	itc-sound-manager
*  @{
*/
//& purpose: To create and destroy a handle for stream information.
//& type : auto
/**
* @testcase 			ITc_sound_manager_create_destroy_stream_information_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to create and destroy handle for stream information
* @scenario				create handle\n
* 						destroy handle
* @apicovered			sound_manager_create_stream_information, sound_manager_destroy_stream_information
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_create_destroy_stream_information_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0;
	sound_stream_info_h stream_info;

	sound_stream_type_e stream_type[] = {
		SOUND_STREAM_TYPE_MEDIA, /**< Sound stream type for media */
		SOUND_STREAM_TYPE_SYSTEM, /**< Sound stream type for system */
		SOUND_STREAM_TYPE_ALARM, /**< Sound stream type for alarm */
		SOUND_STREAM_TYPE_NOTIFICATION, /**< Sound stream type for notification */
		SOUND_STREAM_TYPE_EMERGENCY, /**< Sound stream type for emergency */
		SOUND_STREAM_TYPE_VOICE_INFORMATION, /**< Sound stream type for voice information */
		SOUND_STREAM_TYPE_VOICE_RECOGNITION, /**< Sound stream type for voice recognition */
		SOUND_STREAM_TYPE_RINGTONE_VOIP, /**< Sound stream type for ringtone for VoIP */
		SOUND_STREAM_TYPE_VOIP, /**< Sound stream type for VoIP */
        SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY,/**< Sound stream type for media only for external devices */
	};
	int nSoundDeviceMaskCount = sizeof(stream_type) / sizeof(stream_type[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nSoundDeviceMaskCount; nEnumLoopCount++ )
	{

		nRet = sound_manager_create_stream_information(stream_type[nEnumLoopCount], sound_stream_focus_state_changed_callback, NULL, &stream_info);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

		CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

		nRet = sound_manager_destroy_stream_information(stream_info);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));
	}
	return 0;
}

//& purpose: To add and remove the device to the stream information for the stream routing.
//& type : auto
/**
* @testcase 			ITc_sound_manager_add_remove_device_for_stream_routing_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to add and remove the device to the stream information for the stream routing.
* @scenario				create handle\n
* 						add and remove the device to the stream information for the stream routing.
* @apicovered			sound_manager_create_stream_information, sound_manager_add_device_for_stream_routing, sound_manager_remove_device_for_stream_routing
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_add_remove_device_for_stream_routing_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
	sound_device_h device = NULL;
	sound_device_list_h deviceList = NULL;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

	nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		return 0;		
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	CHECK_HANDLE(deviceList, "sound_manager_get_device_list");

	nRet = sound_manager_get_next_device(deviceList, &device);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		return 0;		
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	CHECK_HANDLE(device, "sound_manager_get_next_device");

	nRet = sound_manager_add_device_for_stream_routing(stream_info, device);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_for_stream_routing", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_remove_device_for_stream_routing(stream_info, device);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_device_for_stream_routing", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To remove all devices from the stream information for the stream routing.
//& type : auto
/**
* @testcase 			ITc_sound_manager_remove_all_devices_for_stream_routing_p
* @since_tizen 			4.0
* @author				SRID(k.tejram)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Remove all the devices from the stream information for the stream routing.
* @scenario				create handle\n
* 						remove all the devices from the stream information for the stream routing.
* @apicovered			sound_manager_create_stream_information, sound_manager_add_device_for_stream_routing, sound_manager_remove_all_devices_for_stream_routing
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_remove_all_devices_for_stream_routing_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
	sound_device_h device = NULL;
	sound_device_list_h deviceList = NULL;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

	nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		return 0;
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	CHECK_HANDLE_CLEANUP(deviceList, "sound_manager_get_device_list", sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_get_next_device(deviceList, &device);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		return 0;
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_free_device_list(deviceList);sound_manager_destroy_stream_information(stream_info));

	CHECK_HANDLE_CLEANUP(device, "sound_manager_get_next_device", sound_manager_free_device_list(deviceList);sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_add_device_for_stream_routing(stream_info, device);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_for_stream_routing", SoundManagerGetError(nRet), sound_manager_free_device_list(deviceList);sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_remove_all_devices_for_stream_routing(stream_info);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_all_devices_for_stream_routing", SoundManagerGetError(nRet), sound_manager_free_device_list(deviceList);sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To apply the stream routing.
//& type : auto
/**
* @testcase 			ITc_sound_manager_apply_stream_routing_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			to apply the stream routing.
* @scenario				create handle\n
* 						apply stream routing.
* @apicovered			sound_manager_create_stream_information, sound_manager_apply_stream_routing
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_apply_stream_routing_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
	sound_device_list_h device_list;
	sound_device_h device;
	sound_device_type_e type;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

	nRet = sound_manager_get_device_list(SOUND_DEVICE_ALL_MASK, &device_list);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	while (sound_manager_get_next_device(device_list, &device) == SOUND_MANAGER_ERROR_NONE) {
		nRet = sound_manager_get_device_type(device, &type);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_type", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

		switch (type) {
			case SOUND_DEVICE_BUILTIN_MIC:
			case SOUND_DEVICE_BUILTIN_SPEAKER:
				nRet = sound_manager_add_device_for_stream_routing(stream_info, device);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_device_for_stream_routing", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));
				break;
			default:
				continue;
		}
	}

	nRet = sound_manager_apply_stream_routing(stream_info);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_apply_stream_routing", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_free_device_list(device_list);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To acquire and release the stream focus
//& type : auto
/**
* @testcase 			ITc_sound_manager_acquire_release_focus_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			acquire and release the stream focus
* @scenario				create handle\n
* 						acquire and release focus
* @apicovered			sound_manager_create_stream_information, sound_manager_acquire_focus, sound_manager_release_focus
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_acquire_release_focus_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0;
	sound_stream_info_h stream_info;
	sound_stream_focus_mask_e focus_mask[] = {
		SOUND_STREAM_FOCUS_FOR_PLAYBACK, /**< Mask for playback focus */
		SOUND_STREAM_FOCUS_FOR_RECORDING, /**< Mask for recording focus */
		SOUND_STREAM_FOCUS_FOR_BOTH, /**< Mask for both playback and recording focus */
 	};

	int nSoundDeviceMaskCount = sizeof(focus_mask) / sizeof(focus_mask[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nSoundDeviceMaskCount; nEnumLoopCount++ )
	{

		nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

		CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

		nRet = sound_manager_acquire_focus(stream_info, focus_mask[nEnumLoopCount], SOUND_BEHAVIOR_NONE, NULL);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

		nRet = sound_manager_release_focus(stream_info, focus_mask[nEnumLoopCount], SOUND_BEHAVIOR_NONE, NULL);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_release_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

		nRet = sound_manager_destroy_stream_information(stream_info);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));
	}

	return 0;
}

//& purpose: To get state of focus
//& type : auto
/**
* @testcase 			ITc_sound_manager_get_focus_state_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			get state of focus
* @scenario				create handle\n
* 						get state of focus
* @apicovered			sound_manager_create_stream_information, sound_manager_get_focus_state
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_focus_state_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
	sound_stream_focus_state_e state_for_playback;
	sound_stream_focus_state_e state_for_recording;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

	nRet = sound_manager_get_focus_state(stream_info, &state_for_playback, &state_for_recording);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_focus_state", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To add and remove the watch callback function to be invoked when the focus state for each sound stream type is changed regardless of the process.
//& type : auto
/**
* @testcase 			ITc_sound_manager_add_remove_focus_state_watch_cb_p
* @since_tizen 			3.0
* @author				SRID(shekhar1.s)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			add and remove the watch callback
* @scenario				create handle\n
* 						acquire and release focus
* @apicovered			sound_manager_add_focus_state_watch_cb, sound_manager_remove_focus_state_watch_cb
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_add_remove_focus_state_watch_cb_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0, id = 0;

	sound_stream_focus_mask_e focus_mask[] = {
		SOUND_STREAM_FOCUS_FOR_PLAYBACK, /**< Mask for playback focus */
		SOUND_STREAM_FOCUS_FOR_RECORDING, /**< Mask for recording focus */
		SOUND_STREAM_FOCUS_FOR_BOTH, 	  /**< Mask for both playback and recording focus */
 	};

	int nSoundDeviceMaskCount = sizeof(focus_mask) / sizeof(focus_mask[0]);
	for ( nEnumLoopCount = 0; nEnumLoopCount < nSoundDeviceMaskCount; nEnumLoopCount++ )
	{
		nRet = sound_manager_add_focus_state_watch_cb(focus_mask[nEnumLoopCount], sound_stream_focus_state_watch_callback, NULL, &id);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_add_focus_state_watch_cb", SoundManagerGetError(nRet));

		nRet = sound_manager_remove_focus_state_watch_cb(id);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_remove_focus_state_watch_cb", SoundManagerGetError(nRet));
	}

	return 0;

}

//& purpose: To set and get auto focus reacquisition.
//& type : auto
/**
* @testcase 			ITc_sound_manager_set_get_focus_reacquisition_p
* @since_tizen 			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(parashant.v)
* @type 				auto
* @description			To set and get auto focus reacquisition.
* @scenario				sound_manager_set_focus_reacquisition\n
* 						sound_manager_get_focus_reacquisition
* @apicovered			sound_manager_set_focus_reacquisition, sound_manager_get_focus_reacquisition
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_set_get_focus_reacquisition_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1, nEnumLoopCount = 0,nMisMatchCount = 0;
	sound_stream_info_h stream_info;
	bool setEnable = false;
	bool getEnable;

	sound_stream_type_e stream_type[] = {
		SOUND_STREAM_TYPE_MEDIA, /**< Sound stream type for media */
		SOUND_STREAM_TYPE_SYSTEM, /**< Sound stream type for system */
		SOUND_STREAM_TYPE_ALARM, /**< Sound stream type for alarm */
		SOUND_STREAM_TYPE_NOTIFICATION, /**< Sound stream type for notification */
		SOUND_STREAM_TYPE_EMERGENCY, /**< Sound stream type for emergency */
		SOUND_STREAM_TYPE_VOICE_INFORMATION, /**< Sound stream type for voice information */
		SOUND_STREAM_TYPE_VOICE_RECOGNITION, /**< Sound stream type for voice recognition */
		SOUND_STREAM_TYPE_RINGTONE_VOIP, /**< Sound stream type for ringtone for VoIP */
		SOUND_STREAM_TYPE_VOIP, /**< Sound stream type for VoIP */
		SOUND_STREAM_TYPE_MEDIA_EXTERNAL_ONLY, /**< Sound stream type for media only for external dev */
	};
	int nSoundDeviceMaskCount = sizeof(stream_type) / sizeof(stream_type[0]);

	for ( nEnumLoopCount = 0; nEnumLoopCount < nSoundDeviceMaskCount; nEnumLoopCount++ )
	{

		nRet = sound_manager_create_stream_information(stream_type[nEnumLoopCount], sound_stream_focus_state_changed_callback, NULL, &stream_info);
		if (nRet == SOUND_MANAGER_ERROR_NOT_SUPPORTED)
			continue;
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

		CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

		nRet = sound_manager_set_focus_reacquisition(stream_info,setEnable);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_focus_reacquisition", SoundManagerGetError(nRet));

		nRet = sound_manager_get_focus_reacquisition(stream_info,&getEnable);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_focus_reacquisition", SoundManagerGetError(nRet));

		if(setEnable != getEnable)
		{
			FPRINTF("[Line : %d][%s] auto focus reacquisition value mismatched\\n", __LINE__, API_NAMESPACE);
			nMisMatchCount ++;
		}

		nRet = sound_manager_destroy_stream_information(stream_info);
		PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));
	}

	if(nMisMatchCount > 0)
	{
		return 1;
	}
	return 0;
}


//& purpose: To get sound type
//& type : auto
/**
* @testcase 			ITc_sound_manager_get_sound_type_p
* @since_tizen 			3.0
* @author				SRID(manu.tiwari)
* @reviewer				SRID(parshant.v)
* @type 				auto
* @description			get sound type via stream info
* @scenario				create handle\n
* 						get sound type
* @apicovered			sound_manager_create_stream_information, sound_manager_get_sound_type
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_sound_type_p(void)
{
       START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
    sound_type_e e_sound_type = -1;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

    nRet = sound_manager_get_sound_type(stream_info, &e_sound_type);
    PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_sound_type", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));
    FPRINTF("[Line : %d][%s] sound_manager_get_sound_type, sound type = %s\\n", __LINE__, API_NAMESPACE, SoundManagerGetSoundType(e_sound_type));
	if (e_sound_type != SOUND_TYPE_VOIP)
		return 1;
	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	//error case check SOUND_MANAGER_ERROR_NO_DATA for SOUND_STREAM_TYPE_EMERGENCY
	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_EMERGENCY, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

    nRet = sound_manager_get_sound_type(stream_info, &e_sound_type);
    PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NO_DATA, nRet, "sound_manager_get_sound_type", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));
    FPRINTF("[Line : %d][%s] sound_manager_get_sound_type, sound type = %s\\n", __LINE__, API_NAMESPACE, SoundManagerGetSoundType(e_sound_type));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To get current acquired focus
//& type : auto
/**
* @testcase 			ITc_sound_manager_get_current_playback_recording_focus_p
* @since_tizen 			3.0
* @author				HQ(sc11.lee)
* @type 				auto
* @description			get current acquired focus in this system
* @scenario				create two stream_info handles with different stream type\n
* 						acquire each focus (playback, recording)\n
* 						get current playback/recording focus
* @apicovered			sound_manager_create_stream_information, sound_manager_acquire_focus,\n
* 						sound_manager_get_current_playback_focus, sound_manager_get_current_recording_focus
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_get_current_playback_recording_focus_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info_alarm;
	sound_stream_info_h stream_info_media;
	sound_stream_focus_change_reason_e playback_acquired_by;
	sound_stream_focus_change_reason_e recording_acquired_by;
	sound_behavior_e behavior;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_ALARM, sound_stream_focus_state_changed_callback, NULL, &stream_info_alarm);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info_alarm, "sound_manager_create_stream_information");

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, sound_stream_focus_state_changed_callback, NULL, &stream_info_media);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_alarm));

	CHECK_HANDLE(stream_info_media, "sound_manager_create_stream_information");

	nRet = sound_manager_acquire_focus(stream_info_alarm, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_alarm));

	nRet = sound_manager_acquire_focus(stream_info_media, SOUND_STREAM_FOCUS_FOR_RECORDING, SOUND_BEHAVIOR_NONE, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_media));

	nRet = sound_manager_get_current_playback_focus(&playback_acquired_by, &behavior, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_current_playback_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_alarm));

	if (playback_acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_ALARM)
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_current_playback_focus is not equal to: %s\\n", __LINE__, API_NAMESPACE, "SOUND_STREAM_FOCUS_CHANGED_BY_ALARM");
		return 1;
	}

	nRet = sound_manager_destroy_stream_information(stream_info_alarm);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	nRet = sound_manager_get_current_recording_focus(&recording_acquired_by, &behavior, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_current_recording_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_media));

	if (recording_acquired_by != SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA)
	{
		FPRINTF("[Line : %d][%s] sound_manager_get_current_recording_focus is not equal to: %s\\n", __LINE__, API_NAMESPACE, "SOUND_STREAM_FOCUS_CHANGED_BY_MEDIA");
		return 1;
	}

	nRet = sound_manager_destroy_stream_information(stream_info_media);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To check if the sound behavior is set normally and passed to another handle successfully
//& type : auto
/**
* @testcase 			ITc_sound_manager_focus_get_requesting_requested_behavior_get_changed_focus_state_p
* @since_tizen 			3.0
* @author				HQ(sc11.lee)
* @type 				auto
* @description			To check if the sound behavior is set normally and passed to another handle successfully
* @scenario				create two stream_info handles\n
* 						acquire playback focus for the first handle\n
* 						set requesting sound behavior and acquire the focus using the second handle\n
* 						get requested sound behavior within the focus state changed callback of the first handle
* @apicovered			sound_manager_create_stream_information, sound_manager_acquire_focus
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_focus_get_requesting_requested_behavior_get_changed_focus_state_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info_media1;
	sound_stream_info_h stream_info_media2;
	sound_behavior_e behavior = SOUND_BEHAVIOR_FADING;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, sound_stream_focus_state_changed_callback, NULL, &stream_info_media1);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info_media1, "sound_manager_create_stream_information");

	nRet = sound_manager_acquire_focus(stream_info_media1, SOUND_STREAM_FOCUS_FOR_PLAYBACK, SOUND_BEHAVIOR_NONE, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_media1));

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, sound_stream_focus_state_changed_callback, NULL, &stream_info_media2);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_media1));

	CHECK_HANDLE(stream_info_media2, "sound_manager_create_stream_information");

	nRet = sound_manager_acquire_focus(stream_info_media2, SOUND_STREAM_FOCUS_FOR_PLAYBACK, behavior, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info_media2));

	if (g_behavior != SOUND_BEHAVIOR_FADING)
		return 1;

	if (g_nRet != SOUND_MANAGER_ERROR_NONE)
		return 1;

	nRet = sound_manager_destroy_stream_information(stream_info_media1);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	nRet = sound_manager_destroy_stream_information(stream_info_media2);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}
//& purpose: Check whether stream is connected to given device or not
//& type : auto
/**
* @testcase 			ITc_sound_manager_is_stream_on_device_p
* @since_tizen 			3.0
* @author				SRID(shilpa.j)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Check whether stream is connected to given device or not
* @scenario				create handle\n
* 						get sound type
* @apicovered			sound_manager_create_stream_information, sound_manager_is_stream_on_device
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/

int ITc_sound_manager_is_stream_on_device_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = -1;
	sound_stream_info_h stream_info;
	sound_device_h device = NULL;
	sound_device_list_h deviceList = NULL;
	bool bis_on = false;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &stream_info);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(stream_info, "sound_manager_create_stream_information");

	nRet = sound_manager_get_device_list(SOUND_DEVICE_IO_DIRECTION_IN_MASK, &deviceList);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_device_list error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		return 0;		
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info));

	nRet = sound_manager_get_next_device(deviceList, &device);
	if (nRet == SOUND_MANAGER_ERROR_NO_DATA)
	{
		FPRINTF("\\n[Line : %d][%s]sound_manager_get_next_device error returned = %s . So leaving test",__LINE__, API_NAMESPACE, SoundManagerGetError(nRet));
		sound_manager_destroy_stream_information(stream_info);
		sound_manager_free_device_list(deviceList);
		return 0;		
	}
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_next_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info);sound_manager_free_device_list(deviceList));

	CHECK_HANDLE_CLEANUP(device, "sound_manager_get_next_device", sound_manager_destroy_stream_information(stream_info);sound_manager_free_device_list(deviceList));
	
	//Target API
	nRet = sound_manager_is_stream_on_device(stream_info, device, &bis_on);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_is_stream_on_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(stream_info);sound_manager_free_device_list(deviceList));

	nRet = sound_manager_free_device_list(deviceList);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	nRet = sound_manager_destroy_stream_information(stream_info);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To acquire and release the stream focus for all Streams
//& type : auto
/**
* @testcase 			ITc_sound_manager_acquire_release_focus_all_p
* @since_tizen 			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description			acquire and release the stream focus for all Streams
* @scenario			create handle\n
* 				acquire focus for specific stream, acquired focus for all streams
*				and release focus for all streams
* @apicovered			sound_manager_acquire_focus_all, sound_manager_release_focus_all
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_acquire_release_focus_all_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = SOUND_MANAGER_ERROR_NONE;
	sound_stream_info_h hStreamInfo = NULL;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &hStreamInfo);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));

	CHECK_HANDLE(hStreamInfo, "sound_manager_create_stream_information");

	nRet = sound_manager_acquire_focus_all(hStreamInfo, SOUND_BEHAVIOR_NONE, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus_all", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfo));

	nRet = sound_manager_release_focus_all(hStreamInfo, SOUND_BEHAVIOR_NONE, NULL);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_release_focus_all", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfo));

	nRet = sound_manager_destroy_stream_information(hStreamInfo);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: Delivers focuses to another stream information.
//& type : auto
/**
* @testcase 			ITc_sound_manager_deliver_focus_p
* @since_tizen 			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Delivers focuses to another stream information.
* @scenario				Delivers focuses to another stream information.
* @apicovered			sound_manager_deliver_focus
* @passcase				When API return SOUND_MANAGER_ERROR_NONE
* @failcase				When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_deliver_focus_p(void)
{
	START_TEST;

	sound_stream_info_h hStreamInfoSource = NULL;
	sound_stream_info_h hStreamInfoDest = NULL;
	sound_stream_focus_state_e eFocusState;
	sound_stream_focus_mask_e eFocusMask[] ={
		SOUND_STREAM_FOCUS_FOR_PLAYBACK,
		SOUND_STREAM_FOCUS_FOR_RECORDING,
		SOUND_STREAM_FOCUS_FOR_BOTH
	};
	int nEnumSize = sizeof(eFocusMask)/sizeof(eFocusMask[0]);

	int nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_VOIP, sound_stream_focus_state_changed_callback, NULL, &hStreamInfoSource);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
	CHECK_HANDLE(hStreamInfoSource, "sound_manager_create_stream_information");

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, sound_stream_focus_state_changed_callback, NULL, &hStreamInfoDest);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfoSource));
	CHECK_HANDLE_CLEANUP(hStreamInfoDest, "sound_manager_create_stream_information",sound_manager_destroy_stream_information(hStreamInfoSource));

	for(int nLoopCounter = 0; nLoopCounter < nEnumSize;nLoopCounter++)
	{
		nRet = sound_manager_acquire_focus(hStreamInfoSource, eFocusMask[nLoopCounter], SOUND_BEHAVIOR_NONE, NULL);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_acquire_focus", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfoSource);sound_manager_destroy_stream_information(hStreamInfoDest));

		nRet = sound_manager_deliver_focus(hStreamInfoSource, hStreamInfoDest, eFocusMask[nLoopCounter]);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_deliver_focus", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfoSource);sound_manager_destroy_stream_information(hStreamInfoDest));

		nRet = sound_manager_get_focus_state(hStreamInfoSource, &eFocusState, NULL);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_focus_state", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfoSource);sound_manager_destroy_stream_information(hStreamInfoDest));
		if(eFocusState != SOUND_STREAM_FOCUS_STATE_RELEASED )
		{
			FPRINTF("\\n[Line : %d][%s]sound_manager_get_focus_state return wrong value",__LINE__, API_NAMESPACE);
			sound_manager_destroy_stream_information(hStreamInfoSource);
			sound_manager_destroy_stream_information(hStreamInfoDest);
			return 1;
		}

		nRet = sound_manager_get_focus_state(hStreamInfoDest, &eFocusState, NULL);
		PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_focus_state", SoundManagerGetError(nRet),sound_manager_destroy_stream_information(hStreamInfoSource);sound_manager_destroy_stream_information(hStreamInfoDest));
		if(eFocusState != SOUND_STREAM_FOCUS_STATE_ACQUIRED )
		{
			FPRINTF("\\n[Line : %d][%s]sound_manager_get_focus_state return wrong value",__LINE__, API_NAMESPACE);
			sound_manager_destroy_stream_information(hStreamInfoSource);
			sound_manager_destroy_stream_information(hStreamInfoDest);
			return 1;
		}
	}

	nRet = sound_manager_destroy_stream_information(hStreamInfoSource);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));
	
	nRet = sound_manager_destroy_stream_information(hStreamInfoDest);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To create and destroy stream ducking
//& type : auto
/**
* @testcase 			ITc_sound_manager_create_destroy_stream_ducking_p
* @since_tizen 			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			create and destroy ducking for all Streams
* @scenario			create stream ducking handle\n
* 				destroy stream ducking handle for all streams
* @apicovered			sound_manager_create_stream_ducking, sound_manager_destroy_stream_ducking
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_create_destroy_stream_ducking_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = SOUND_MANAGER_ERROR_NONE;
	sound_stream_ducking_h hStreamDucking = NULL;

	nRet = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamDucking);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_ducking", SoundManagerGetError(nRet));

	CHECK_HANDLE(&hStreamDucking, "sound_manager_create_stream_ducking");

        nRet = sound_manager_destroy_stream_ducking(hStreamDucking);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_ducking", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To check if stream is ducked.
//& type : auto
/**
* @testcase 			ITc_sound_manager_is_ducked_p
* @since_tizen 			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			checking if stream is ducked or not
* @scenario			create stream ducking handle\n
* 				check weather stream is ducked and destroy stream ducking handle for streams
* @apicovered			sound_manager_create_stream_ducking, sound_manager_is_ducked, sound_manager_destroy_stream_ducking
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_is_ducked_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = SOUND_MANAGER_ERROR_NONE;
	sound_stream_ducking_h hStreamDucking = NULL;
	bool bIsDucked;

	nRet = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamDucking);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_ducking", SoundManagerGetError(nRet));

	CHECK_HANDLE(&hStreamDucking, "sound_manager_create_stream_ducking");

	nRet = sound_manager_is_ducked(hStreamDucking, &bIsDucked);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_is_ducked", SoundManagerGetError(nRet), sound_manager_destroy_stream_ducking(hStreamDucking));

	nRet = sound_manager_destroy_stream_ducking(hStreamDucking);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_ducking", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To activate and deactivate stream ducking.
//& type : auto
/**
* @testcase 			ITc_sound_manager_activate_deactivate_ducking_p
* @since_tizen 			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			To activate and deactivate stream ducking
* @scenario			create stream ducking handle\n
* 				activate and deactivate ducking and destroy stream ducking handle for streams
* @apicovered			sound_manager_create_stream_ducking, sound_manager_activate_ducking, sound_manager_deactivate_ducking,sound_manager_destroy_stream_ducking
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_activate_deactivate_ducking_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = SOUND_MANAGER_ERROR_NONE;
	sound_stream_ducking_h hStreamDucking = NULL;
        unsigned int tDuration = 500;
        double dRatio = 0.5;

	nRet = sound_manager_create_stream_ducking(SOUND_STREAM_TYPE_MEDIA, sound_stream_ducking_state_changed_callback, NULL, &hStreamDucking);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_ducking", SoundManagerGetError(nRet));

	CHECK_HANDLE(&hStreamDucking, "sound_manager_create_stream_ducking");

	nRet = sound_manager_activate_ducking(hStreamDucking, tDuration, dRatio);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_activate_ducking", SoundManagerGetError(nRet), sound_manager_destroy_stream_ducking(hStreamDucking));

	nRet = sound_manager_deactivate_ducking(hStreamDucking);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_deactivate_ducking", SoundManagerGetError(nRet), sound_manager_destroy_stream_ducking(hStreamDucking));

	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(g_bCallbackResult, true, "sound_manager_activate_ducking", SoundManagerGetError(nRet), sound_manager_destroy_stream_ducking(hStreamDucking));

	nRet = sound_manager_destroy_stream_ducking(hStreamDucking);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_ducking", SoundManagerGetError(nRet));

	return 0;
}

//& purpose: To get and set stream prefered device.
//& type : auto
/**
* @testcase 			ITc_sound_manager_set_get_stream_prefered_device_p
* @since_tizen 			5.5
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @description			To get and set stream prefered device
* @scenario			Create stream info handle\n
*				Get current device list\n				Get device handle from the device list\n
*				Find buit-in speaker or built-in mic device handle\n
*				Set the device handle as preferred device\n
*				Get the device handle as preferred device\n
* @apicovered			sound_manager_set_stream_preferred_device, sound_manager_get_stream_preferred_device
* @passcase			When API return SOUND_MANAGER_ERROR_NONE
* @failcase			When API not return SOUND_MANAGER_ERROR_NONE
* @precondition			None
* @postcondition		None
*/
int ITc_sound_manager_set_get_stream_prefered_device_p(void)
{
	START_TEST;
	// Initializing testing variable
	int nRet = SOUND_MANAGER_ERROR_NONE;
	sound_stream_info_h hStreamInfoHandle = NULL;
	sound_device_list_h hlist = NULL;
	sound_device_h hdevice = NULL;
	int setInDeviceID = 0;
	int setOutDeviceID = 0;
	int getInDeviceID = 0;
	int getOutDeviceID = 0;
	sound_device_type_e etype;

	nRet = sound_manager_create_stream_information(SOUND_STREAM_TYPE_MEDIA, NULL, NULL, &hStreamInfoHandle);
	PRINT_RESULT(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_create_stream_information", SoundManagerGetError(nRet));
	CHECK_HANDLE(hStreamInfoHandle, "sound_manager_create_stream_information");

	nRet = sound_manager_get_device_list(SOUND_DEVICE_TYPE_INTERNAL_MASK, &hlist);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_list", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle));
	CHECK_HANDLE_CLEANUP(hlist, "sound_manager_get_device_list", sound_manager_destroy_stream_information(hStreamInfoHandle));
	while (!(nRet = sound_manager_get_next_device(hlist, &hdevice))) {
		CHECK_HANDLE_CLEANUP(hdevice, "sound_manager_get_next_device", sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));
		if (!(nRet = sound_manager_get_device_type(hdevice, &etype))) {
			 if (etype == SOUND_DEVICE_BUILTIN_SPEAKER) {
				nRet = sound_manager_set_stream_preferred_device(hStreamInfoHandle, SOUND_DEVICE_IO_DIRECTION_OUT, hdevice);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_stream_preferred_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));

				nRet = sound_manager_get_device_id(hdevice, &setOutDeviceID);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_id", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));
			 } else if (etype == SOUND_DEVICE_BUILTIN_MIC) {
				nRet = sound_manager_set_stream_preferred_device(hStreamInfoHandle, SOUND_DEVICE_IO_DIRECTION_IN, hdevice);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_set_stream_preferred_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));

				nRet = sound_manager_get_device_id(hdevice, &setInDeviceID);
				PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_device_id", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));
			 }
		}
	}

	nRet = sound_manager_get_stream_preferred_device(hStreamInfoHandle, &getInDeviceID, &getOutDeviceID);
	PRINT_RESULT_CLEANUP(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_get_stream_preferred_device", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));

	if (getInDeviceID != SOUND_MANAGER_STREAM_NO_PREFERRED_DEVICE)
		PRINT_RESULT_CLEANUP(getInDeviceID, setInDeviceID, "Input Device ID is different in Set and Get Value", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));

	if (getOutDeviceID != SOUND_MANAGER_STREAM_NO_PREFERRED_DEVICE)
		PRINT_RESULT_CLEANUP(getOutDeviceID, setOutDeviceID, "Output Device ID is different in Set and Get Value", SoundManagerGetError(nRet), sound_manager_destroy_stream_information(hStreamInfoHandle);sound_manager_free_device_list(hlist));

	nRet = sound_manager_destroy_stream_information(hStreamInfoHandle);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_destroy_stream_information", SoundManagerGetError(nRet));

	nRet = sound_manager_free_device_list(hlist);
	PRINT_RESULT_NORETURN(SOUND_MANAGER_ERROR_NONE, nRet, "sound_manager_free_device_list", SoundManagerGetError(nRet));

	return 0;
}
