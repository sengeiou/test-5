#include "CTs-platform-permission-common.h"
#include <media/audio_io.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>
#include <sound_manager.h>

#define SAMPLE_RATE 44100

/**
* @function 		AudioInputGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AudioInputGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case AUDIO_IO_ERROR_INVALID_PARAMETER:		 szErrorVal = "AUDIO_IO_ERROR_INVALID_PARAMETER";		break;
	case AUDIO_IO_ERROR_OUT_OF_MEMORY: 			 szErrorVal = "AUDIO_IO_ERROR_OUT_OF_MEMORY";			break;
	case AUDIO_IO_ERROR_DEVICE_NOT_OPENED: 		 szErrorVal = "AUDIO_IO_ERROR_DEVICE_NOT_OPENED";		break;
	case AUDIO_IO_ERROR_INVALID_OPERATION: 		 szErrorVal = "AUDIO_IO_ERROR_INVALID_OPERATION";		break;
	case AUDIO_IO_ERROR_DEVICE_NOT_CLOSED:		 szErrorVal = "AUDIO_IO_ERROR_DEVICE_NOT_CLOSED";		break;
	case AUDIO_IO_ERROR_INVALID_BUFFER: 		 szErrorVal = "AUDIO_IO_ERROR_INVALID_BUFFER";			break;
	case AUDIO_IO_ERROR_SOUND_POLICY: 			 szErrorVal = "AUDIO_IO_ERROR_SOUND_POLICY";			break;
	case AUDIO_IO_ERROR_NONE: 					 szErrorVal = "AUDIO_IO_ERROR_NONE";					break;
	default: 									 szErrorVal = "Unknown Error";							break;
	}
	return szErrorVal;
}

/**
* @function 		AudioChannel
* @description	 	Maps error enums 
* @parameter		nRet: error code returned
* @return 			error string
*/

char* AudioChannel(audio_channel_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case AUDIO_CHANNEL_STEREO:		szErrorVal = "AUDIO_CHANNEL_STEREO";	break;
	case AUDIO_CHANNEL_MONO:		szErrorVal = "AUDIO_CHANNEL_MONO";		break;
	}
	return szErrorVal;
}
/**
* @function 		AudioSampleRate
* @description	 	Maps error enums 
* @parameter		nRet: error code returned
* @return 			error string
*/
char* AudioSampleRate(audio_sample_type_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case AUDIO_SAMPLE_TYPE_U8:			szErrorVal = "AUDIO_SAMPLE_TYPE_U8";		break;
	case AUDIO_SAMPLE_TYPE_S16_LE:		szErrorVal = "AUDIO_SAMPLE_TYPE_S16_LE";	break;
	}
	return szErrorVal;
}

/**
* @function         CTs_platform_permission_audioio_startup
* @description         Called before each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_audioio_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_audioio_cleanup
* @description         Called after each test
* @parameter        NA
* @return             NA
*/
void CTs_platform_permission_audioio_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:To create an audio device instance and to return an input handle to record PCM and to release it
//& type: auto
/**
* @testcase			CTc_AudioIO_PrivilegeRecorder_Create
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		To create an audio device instance and to return an input handle to record PCM and to release it
* @scenario			Create an audio device\n
*					Create a local audio handle\n
* @apicovered		audio_in_create
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/ 
int CTc_AudioIO_PrivilegeRecorder_Create(void)
{
	START_TEST;
    IS_FEATURE_SUPPORTED(FEATURE_AUDIO_MICROPHONE, g_bIsSupported, API_NAMESPACE);
	if ( false == g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_AUDIO_MICROPHONE);
		return 0;
	}
	audio_in_h pstAudioInputHandle = NULL;
	audio_channel_e eAudioChannel = AUDIO_CHANNEL_STEREO;
	audio_sample_type_e eAudioSampleRate = AUDIO_SAMPLE_TYPE_U8;
	
	int nRet = audio_in_create(SAMPLE_RATE, eAudioChannel, eAudioSampleRate, &pstAudioInputHandle);	
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "audio_in_create", AudioInputGetError(nRet),audio_in_destroy(pstAudioInputHandle),AUDIO_IO_ERROR_NONE);			

	return 0;
}
