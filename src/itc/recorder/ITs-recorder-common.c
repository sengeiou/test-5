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
#include "ITs-recorder-common.h"

/** @addtogroup itc-recorder
*  @ingroup itc
*  @{
*/

/**
* @function			GetInternalMemoryIdCallBack
* @description		callback function to retrieves all storage in device
* @parameter[IN]	int storage_id - storage device id
* @parameter[IN]	storage_type_e type - storage type
* @parameter[IN]	storage_state_e - storage device state
* @parameter[IN]	void *user_data - user data
* @return			NA
*/
static bool GetInternalMemoryIdCallBack(int storage_id, storage_type_e type, storage_state_e state, const char *path, void *user_data)
{
#if DEBUG
	FPRINTF("[Line: %d][%s] GetInternalMemoryIdCallBack callback hit\\n", __LINE__, API_NAMESPACE);
#endif

	if ( type == STORAGE_TYPE_INTERNAL)
	{
		FPRINTF("[Line: %d][%s] Internal Storage ID Found\\n", __LINE__, API_NAMESPACE);
		g_bStorageFound = true;
		g_nStorageId = storage_id;
		return false;
	}
	return true;
}

/**
* @function 		RecorderGetState
* @description	 	Maps error enums to string values and print Recorder State Code
* @parameter		Recorder state
* @return 			N/A
*/
char* RecorderGetState(recorder_state_e RecordState)
{
	char* pszState = "Unknown State";
	switch ( RecordState )
	{
	case RECORDER_STATE_NONE:		pszState = "RECORDER_STATE_NONE";			break;
	case RECORDER_STATE_CREATED:		pszState = "RECORDER_STATE_CREATED";			break;
	case RECORDER_STATE_READY:		pszState = "RECORDER_STATE_READY";			break;
	case RECORDER_STATE_RECORDING:		pszState = "RECORDER_STATE_RECORDING";			break;
	case RECORDER_STATE_PAUSED:		pszState = "RECORDER_STATE_PAUSED";			break;
	}
	return pszState;
}

/**
* @function 		RecorderGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* RecorderGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case RECORDER_ERROR_NONE:				szErrorVal = "RECORDER_ERROR_NONE";				break;
	case RECORDER_ERROR_INVALID_PARAMETER:			szErrorVal = "RECORDER_ERROR_INVALID_PARAMETER";		break;
	case RECORDER_ERROR_INVALID_STATE:			szErrorVal = "RECORDER_ERROR_INVALID_STATE";			break;
	case RECORDER_ERROR_OUT_OF_MEMORY:			szErrorVal = "RECORDER_ERROR_OUT_OF_MEMORY";			break;
	case RECORDER_ERROR_DEVICE:				szErrorVal = "RECORDER_ERROR_DEVICE";				break;
	case RECORDER_ERROR_INVALID_OPERATION:			szErrorVal = "RECORDER_ERROR_INVALID_OPERATION";		break;
	case RECORDER_ERROR_SECURITY_RESTRICTED: 		szErrorVal = "RECORDER_ERROR_SECURITY_RESTRICTED";		break;
	case RECORDER_ERROR_ESD: 				szErrorVal = "RECORDER_ERROR_ESD";				break;
	case RECORDER_ERROR_OUT_OF_STORAGE: 			szErrorVal = "RECORDER_ERROR_OUT_OF_STORAGE";			break;
	case RECORDER_ERROR_PERMISSION_DENIED:		 	szErrorVal = "RECORDER_ERROR_PERMISSION_DENIED";		break;
	case RECORDER_ERROR_NOT_SUPPORTED:			szErrorVal = "RECORDER_ERROR_NOT_SUPPORTED";			break;
	case RECORDER_ERROR_RESOURCE_CONFLICT:			szErrorVal = "RECORDER_ERROR_RESOURCE_CONFLICT";		break;
	case RECORDER_ERROR_SERVICE_DISCONNECTED:		szErrorVal = "RECORDER_ERROR_SERVICE_DISCONNECTED";		break;
	default: 						szErrorVal = "Unknown Error";					break;
	}
	return szErrorVal;
}

/**
* @function 		SoundManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SoundManagerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_MANAGER_ERROR_NONE:					szErrorVal = "SOUND_MANAGER_ERROR_NONE";					break;
	case SOUND_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "SOUND_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case SOUND_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case SOUND_MANAGER_ERROR_INVALID_OPERATION:		szErrorVal = "SOUND_MANAGER_ERROR_INVALID_OPERATION";		break;
	case SOUND_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "SOUND_MANAGER_ERROR_PERMISSION_DENIED";		break;
	case SOUND_MANAGER_ERROR_NOT_SUPPORTED:			szErrorVal = "SOUND_MANAGER_ERROR_NOT_SUPPORTED";			break;
	case SOUND_MANAGER_ERROR_NO_DATA:				szErrorVal = "SOUND_MANAGER_ERROR_NO_DATA";					break;
	case SOUND_MANAGER_ERROR_NO_PLAYING_SOUND:		szErrorVal = "SOUND_MANAGER_ERROR_NO_PLAYING_SOUND";		break;
	case SOUND_MANAGER_ERROR_INTERNAL:				szErrorVal = "SOUND_MANAGER_ERROR_INTERNAL";				break;
	case SOUND_MANAGER_ERROR_POLICY:				szErrorVal = "SOUND_MANAGER_ERROR_POLICY";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}


/**
* @function 		CreateAudioRecorder
* @description 		Creates a audio recorder
* @parameter		NA
* @return 			true if successful, otherwise false.
*/
bool CreateAudioRecorder()
{
	g_bMismatch = false;
	
	int nRet = recorder_create_audiorecorder(&g_pstRecorder);
	if ( g_bAudioRecFeatureNotSupported == true )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
			return true;
		}
		return true;
	}

	if ( nRet != RECORDER_ERROR_NONE )
	{
#if DEBUG
		FPRINTF("[Line: %d][%s] cannot create audio recorder\\n", __LINE__, API_NAMESPACE);
#endif
		return false;
	}
	return true;
}

/**
* @function 		CreateVideoRecorder
* @description 		Creates a video recorder
* @parameter		NA
* @return 			true if successful, otherwise false.
*/
bool CreateVideoRecorder()
{
	g_bMismatch = false;

	int nRet = camera_create(CAMERA_DEVICE_CAMERA0, &g_pstCamera);

	if ( g_bCamFeatureNotSupported == true )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		return true;
	}
	if ( nRet != 0 )
	{
		FPRINTF("[Line: %d][%s] cannot create camera\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	
	nRet = recorder_create_videorecorder(g_pstCamera, &g_pstRecorder);
	if ( g_bVideoRecFeatureNotSupported  == true )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bMismatch = true;
		}
		return true;
	}
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] cannot create video recorder\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return true;
}

/**
* @function 		DestroyRecorderHandler
* @description 		Destroys the recorder handler
* @parameter		N/A
* @return 			true if successful, otherwise false
*/
bool DestroyRecorderHandler(void)
{
	int nRet = recorder_destroy(g_pstRecorder);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_destroy failed, error returned = %s\\n", __LINE__, API_NAMESPACE, RecorderGetError(nRet));
		return false;
	}
	return true;
}
/**
* @function 		RecorderSupportedAudioEncoderCallback
* @description	 	callback function for retrieving all supported audio encoders
* @parameter		recorder_audio_codec_e codec, void *user_data
* @return 			NA
*/
bool RecorderSupportedAudioEncoderCallback(recorder_audio_codec_e codec, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] RecorderSupportedAudioEncoderCallback callback is called\\n", __LINE__, API_NAMESPACE);
#endif	
	bool ret = true;
	if ( user_data != NULL )
	{
		*( (recorder_audio_codec_e *)user_data) = codec;
		return false;
	}
	
	if ( g_mainloop )
	{
		g_main_loop_quit(g_mainloop);
		g_main_loop_unref(g_mainloop);
		g_mainloop = NULL;
	}
	
	return ret;
}

/**
* @function 		RecorderSupportedFileFormatCallback
* @description	 	callback function for retrieving all supported file formats
* @parameter		recorder_file_format_e format, void *user_data
* @return 			NA
*/
bool RecorderSupportedFileFormatCallback(recorder_file_format_e format, void *user_data)
{	
	int *pUserData = NULL;	
	bool ret = true;
	if ( user_data != NULL )
	{
		pUserData = (int *)user_data;
		if (audiocodec_fileformat_compatibility_table[pUserData[USER_DATA_AUDIO_CODEC]][(int)format]) {
			pUserData[USER_DATA_FILE_FORMAT] = (int)format;
			return false;
		}
	}
	
	return ret;
}
/**
* @function 		ReadyRecorderHandler
* @description 		Gets the recorder prepared.
* @parameter		N/A
* @return 			true if successful, otherwise false.
*/
bool ReadyRecorderHandler(void)
{
	int user_data[USER_DATA_MAX];
	recorder_audio_codec_e codec;
	memset(user_data, 0, sizeof(int) * USER_DATA_MAX);	
	recorder_file_format_e eSetFileFormat = -1;

	
	int nRet = recorder_foreach_supported_audio_encoder(g_pstRecorder, RecorderSupportedAudioEncoderCallback, &codec);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_foreach_supported_audio_encoder failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
		return false;
	}	
	if ((int)codec >= 0 && (int)codec < ITC_AUDIO_CODEC_NUM) {
	
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		int nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		if ( nRet != RECORDER_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] recorder_foreach_supported_file_format failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
			return false;
		}	
		eSetFileFormat = (recorder_file_format_e)user_data[USER_DATA_FILE_FORMAT];		
	}else{
		FPRINTF("[Line : %d][%s] failed, error = RECORDER_ERROR_NOT_SUPPORTED", __LINE__, API_NAMESPACE);
		return false;
	}	
	

	nRet = recorder_set_audio_encoder(g_pstRecorder, codec);	
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_set_audio_encoder failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
		return false;
	}

	GetFileName();
	char* pchSetFilename = strdup(g_RecorderFile);
	FREE_MEMORY(g_RecorderFile);

	nRet = recorder_set_filename(g_pstRecorder, pchSetFilename);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_set_filename failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
		FREE_MEMORY(pchSetFilename);
		return false;
	}

	nRet = recorder_set_file_format(g_pstRecorder,eSetFileFormat);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_set_file_format failed, error returned = %s\\n", __LINE__, API_NAMESPACE,RecorderGetError(nRet));
		FREE_MEMORY(pchSetFilename);
		return false;
	}

	nRet = recorder_prepare(g_pstRecorder);
	if ( nRet != RECORDER_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] recorder_prepare failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
		FREE_MEMORY(pchSetFilename);
		return false;
	}

	FREE_MEMORY(pchSetFilename);

	return true;
}

/**
* @function 		GetFileName
* @description	 	Function to get recorder file
* @parameter		NA
* @return 			NA
*/
void GetFileName(void)
{
	g_bStorageFound = false;
	storage_foreach_device_supported(GetInternalMemoryIdCallBack, NULL);

	if ( g_bStorageFound == false )
	{
		FPRINTF("[Line: %d][%s] Internal Storage ID not found using storage id number 1\\n", __LINE__, API_NAMESPACE);
		g_nStorageId = 1;
	}

	char *pszPath = NULL;
	storage_get_directory(g_nStorageId, STORAGE_DIRECTORY_VIDEOS, &pszPath);

	g_RecorderFile = (char *)malloc(strlen(pszPath) + strlen(FILENAME) + 1);
	memset(g_RecorderFile, 0x00, (strlen(pszPath) + strlen(FILENAME) + 1));
	strncpy(g_RecorderFile, pszPath, strlen(pszPath)+1);
	strncat(g_RecorderFile, FILENAME, strlen(FILENAME)+1);
	FPRINTF("[Line: %d][%s] Output File Path is %s\\n", __LINE__,API_NAMESPACE, g_RecorderFile);
}

/**
* @function 		RecorderTimeoutFunction
* @description	 	Called if some callback is not invoked for a particular Recorder Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean RecorderTimeoutFunction(gpointer data)
{
	FPRINTF( "[Line: %d][%s] Callback Recorder wait complete for 20 seconds. Timeout\\n",__LINE__, API_NAMESPACE);
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/**
* @function 		RecorderWaitForAsync
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void RecorderWaitForAsync()
{
	int timeout_id = 0;
	g_mainloop = g_main_loop_new(NULL, FALSE);

	timeout_id = g_timeout_add(TIMEOUT, RecorderTimeoutFunction, g_mainloop);
	g_main_loop_run(g_mainloop);
	g_source_remove(timeout_id);
}
/** @} */
