#include "CTs-platform-permission-common.h"
#include <stt.h>

#define MICROPHONE_FEATURE			"http://tizen.org/feature/microphone"
#define SPEECH_RECOGNITION_FEATURE	"http://tizen.org/feature/speech.recognition"
/**
* @function 		SttGetError
* @description	 	Maps stt_error_e enums to string values
* @parameter		nError : error code returned
* @return 			error string
*/
char* SttGetError(stt_error_e nError)
{
	char *szErrorVal = "Undefined Error";
	switch ( nError )
	{
	case STT_ERROR_NONE:					szErrorVal = "STT_ERROR_NONE";					break;
	case STT_ERROR_OUT_OF_MEMORY:			szErrorVal = "STT_ERROR_OUT_OF_MEMORY";			break;
	case STT_ERROR_INVALID_PARAMETER:		szErrorVal = "STT_ERROR_INVALID_PARAMETER";		break;
	case STT_ERROR_IO_ERROR:				szErrorVal = "STT_ERROR_IO_ERROR";				break;
	case STT_ERROR_TIMED_OUT:				szErrorVal = "STT_ERROR_TIMED_OUT";				break;
	case STT_ERROR_OPERATION_FAILED:		szErrorVal = "STT_ERROR_OPERATION_FAILED";		break;
	case STT_ERROR_RECORDER_BUSY:			szErrorVal = "STT_ERROR_RECORDER_BUSY";			break;
	case STT_ERROR_OUT_OF_NETWORK:			szErrorVal = "STT_ERROR_OUT_OF_NETWORK";		break;
	case STT_ERROR_INVALID_STATE:			szErrorVal = "STT_ERROR_INVALID_STATE";			break;
	case STT_ERROR_INVALID_LANGUAGE:		szErrorVal = "STT_ERROR_INVALID_LANGUAGE";		break;
	case STT_ERROR_ENGINE_NOT_FOUND:		szErrorVal = "STT_ERROR_ENGINE_NOT_FOUND";		break;
	case STT_ERROR_NOT_SUPPORTED:			szErrorVal = "STT_ERROR_NOT_SUPPORTED";			break;
	case STT_ERROR_NOT_SUPPORTED_FEATURE:	szErrorVal = "STT_ERROR_NOT_SUPPORTED_FEATURE";	break;
	}

	return szErrorVal;
}
/**
* @function 		CTs_platform_permission_stt_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_stt_startup(void)
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
* @function 		CTs_platform_permission_stt_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_stt_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


//& purpose Create and destroy an STT handle
//& type: auto
/**
* @testcase				ITc_stt_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(manoj.g2)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @description			Create and destroy an STT handle
* @scenario				Creates an STT handle\n
* 						Destroys an STT handle
* @apicovered			stt_create, stt_destroy, stt_get_state
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			NA
* @postcondition		NA 
*/
int CTc_Stt_PrivilegeRecorder_create_destroy(void)
{
	START_TEST;
	
	stt_h hStt = NULL;
	bool g_bIsMICROSupported =false;
	bool g_bIsSPEECHSupported =false;
	bool g_bIsSttSupported =false;
	
	IS_FEATURE_SUPPORTED(MICROPHONE_FEATURE, g_bIsMICROSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(SPEECH_RECOGNITION_FEATURE, g_bIsSPEECHSupported, API_NAMESPACE);
	g_bIsSttSupported = g_bIsMICROSupported && g_bIsSPEECHSupported;
	if ( false == g_bIsSttSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] and [%s] is not supported\\n", __LINE__, API_NAMESPACE, MICROPHONE_FEATURE,SPEECH_RECOGNITION_FEATURE);
		return 0;
	}
	//Target API
	/**** Create STT Handle ****/
	int nRet = stt_create(&hStt);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "stt_create", SttGetError(nRet),stt_destroy(hStt),STT_ERROR_NONE);

	return 0;
}