#include "CTs-platform-permission-common.h"
#include "recorder.h" 
#define FEATURE_AUDIO_MICROPHONE		"http://tizen.org/feature/microphone"
#define CAMERA_FEATURE				"http://tizen.org/feature/camera"
#define FILENAME					"/Recorder.file"
#define CTC_AUDIO_CODEC_NUM 5
#define CTC_FILE_FORMAT_NUM 7

recorder_h g_pstRecorder;
char *g_RecorderFile;
int g_nStorageId;
bool g_bStorageFound;

enum {
	USER_DATA_AUDIO_CODEC,
	USER_DATA_FILE_FORMAT,
	USER_DATA_MAX
};

static bool	audiocodec_fileformat_compatibility_table[CTC_AUDIO_CODEC_NUM][CTC_FILE_FORMAT_NUM] =
{        /* 3GP MP4 AMR ADTS WAV OGG M2TS */
/*AMR*/     {1,  0,  1,  0,   0,  0,  0},
/*AAC*/     {1,  1,  0,  0,   0,  0,  1},
/*VORBIS*/  {0,  0,  0,  0,   0,  1,  0},
/*PCM*/     {0,  0,  0,  0,   1,  0,  0},
/*MP3*/     {0,  1,  0,  0,   0,  0,  1}
};

/**
* @function 		CTs_platform_permission_recorder_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_recorder_startup(void)
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
* @function 		CTs_platform_permission_recorder_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_recorder_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
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
	case RECORDER_ERROR_NONE:               		szErrorVal = "case RECORDER_ERROR_NONE";			break;
	case RECORDER_ERROR_INVALID_PARAMETER:  		szErrorVal = "case RECORDER_ERROR_INVALID_PARAMETER";		break;
	case RECORDER_ERROR_INVALID_STATE:   			szErrorVal = "case RECORDER_ERROR_INVALID_STATE";		break;
	case RECORDER_ERROR_OUT_OF_MEMORY: 	    		szErrorVal = "case RECORDER_ERROR_OUT_OF_MEMORY";		break;
	case RECORDER_ERROR_DEVICE:        			szErrorVal = "case RECORDER_ERROR_DEVICE";			break;
	case RECORDER_ERROR_INVALID_OPERATION:			szErrorVal = "case RECORDER_ERROR_INVALID_OPERATION";		break;
	case RECORDER_ERROR_SECURITY_RESTRICTED: 		szErrorVal = "case RECORDER_ERROR_SECURITY_RESTRICTED";		break;
	case RECORDER_ERROR_ESD: 				szErrorVal = "case RECORDER_ERROR_ESD";				break;
	case RECORDER_ERROR_OUT_OF_STORAGE: 			szErrorVal = "case RECORDER_ERROR_OUT_OF_STORAGE";		break;
	case RECORDER_ERROR_PERMISSION_DENIED:		 	szErrorVal = "case RECORDER_ERROR_PERMISSION_DENIED";		break;
	case RECORDER_ERROR_NOT_SUPPORTED:			szErrorVal = "case RECORDER_ERROR_NOT_SUPPORTED";		break;
	default: 						szErrorVal = "case RECORDER_ERROR_NONE";			break;
	}
	return szErrorVal;
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
	int Ret = storage_get_directory(g_nStorageId, STORAGE_DIRECTORY_VIDEOS, &pszPath);
	if(Ret != STORAGE_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] storage_get_directory  returned ERROR =%s\\n", __LINE__,API_NAMESPACE,RecorderGetError(Ret));
		return;
	}

	g_RecorderFile = (char *)malloc(strlen(pszPath) + strlen(FILENAME) + 1);
	memset(g_RecorderFile, 0x00, (strlen(pszPath) + strlen(FILENAME) + 1));
	strncpy(g_RecorderFile, pszPath,strlen(g_RecorderFile)+1);
	strncat(g_RecorderFile, FILENAME,strlen(FILENAME)+1);
	FPRINTF("[Line: %d][%s] Output File Path is %s\\n", __LINE__,API_NAMESPACE, g_RecorderFile);
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
	if ((int)codec >= 0 && (int)codec < CTC_AUDIO_CODEC_NUM) 
	{
		user_data[USER_DATA_AUDIO_CODEC] = (int)codec;
		int nRet = recorder_foreach_supported_file_format(g_pstRecorder, RecorderSupportedFileFormatCallback, user_data);
		if ( nRet != RECORDER_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] recorder_foreach_supported_file_format failed, error returned = %s\\n", __LINE__,API_NAMESPACE, RecorderGetError(nRet));
			return false;
		}	
		eSetFileFormat = (recorder_file_format_e)user_data[USER_DATA_FILE_FORMAT];		
	}
	else
	{
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


//& purpose:Checking tizen.org/privilege/recorder privilege
//& type: auto
/**
* @testcase			CTc_Recorder_PrivilegeAudioRecorder_create
* @since_tizen		2.3
* @author			SRID(shobhit.v)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @scenario			Creates a recorder handle to record an audio\n
* 					Destroys the recorder handle
* @apicovered		recorder_create_audiorecorder and recorder_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Recorder_PrivilegeAudioRecorder_create(void)
{
	START_TEST;

	g_pstRecorder = NULL;
	int nRet = 0;
	bool bIsMicroSupported =false;
	bool bIsCameraSupported =false;
	bool bIsSupported =false;
	IS_FEATURE_SUPPORTED(FEATURE_AUDIO_MICROPHONE, bIsMicroSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(CAMERA_FEATURE, bIsCameraSupported, API_NAMESPACE);
	bIsSupported = bIsMicroSupported && bIsCameraSupported;
	if ( false == bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature is not supported [%s] \\n", __LINE__, API_NAMESPACE, FEATURE_AUDIO_MICROPHONE);
		return 0;
	}
	nRet = recorder_create_audiorecorder(&g_pstRecorder);
	PRINT_RESULT(RECORDER_ERROR_NONE, nRet, "recorder_create_audiorecorder", RecorderPrintErrorMsg(nRet));
	
	if ( ReadyRecorderHandler() != true )
	{
		FPRINTF( "[Line : %d][%s] Recorder Ready Initialize condition failed\\n", __LINE__, API_NAMESPACE);
		recorder_destroy(g_pstRecorder);
		return 1;
	}
	
	// Target API
	nRet = recorder_start(g_pstRecorder);
	if ( nRet != TIZEN_ERROR_PERMISSION_DENIED)
	{
		FPRINTF("[Line : %d][%s] recorder_start failed. Error returned = %s: \\n", __LINE__, API_NAMESPACE, RecorderPrintErrorMsg(nRet));
		recorder_cancel(g_pstRecorder);
		recorder_unprepare(g_pstRecorder);
		recorder_destroy(g_pstRecorder);
		return 1;
	}
	recorder_cancel(g_pstRecorder);
	recorder_unprepare(g_pstRecorder);
	recorder_destroy(g_pstRecorder);
	return 0;
}


