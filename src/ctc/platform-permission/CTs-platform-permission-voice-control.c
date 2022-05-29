#include "CTs-platform-permission-common.h"

#include <voice_control.h>
#include <voice_control_command.h>
#include <voice_control_common.h>
#include <glib.h>
#include <Ecore.h>

#define MICROPHONEFEATURE		"http://tizen.org/feature/microphone"
#define SPEECHCONTROLFEATURE	"http://tizen.org/feature/speech.control"

/**
* @function 		VoiceControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* VoiceControlGetError(int nRet)
{
	char *szErrorVal = "VC_ERROR_UNKNOWN";
	switch ( nRet )
	{
		case VC_ERROR_NONE:						szErrorVal = "VC_ERROR_NONE";					break;
		case VC_ERROR_OUT_OF_MEMORY:			szErrorVal = "VC_ERROR_OUT_OF_MEMORY";			break;
		case VC_ERROR_IO_ERROR:					szErrorVal = "VC_ERROR_IO_ERROR";				break;
		case VC_ERROR_INVALID_PARAMETER:		szErrorVal = "VC_ERROR_INVALID_PARAMETER";		break;
		case VC_ERROR_TIMED_OUT:				szErrorVal = "VC_ERROR_TIMED_OUT";				break;
		case VC_ERROR_RECORDER_BUSY:			szErrorVal = "VC_ERROR_RECORDER_BUSY";			break;
		case VC_ERROR_PERMISSION_DENIED:		szErrorVal = "VC_ERROR_PERMISSION_DENIED";		break;
		case VC_ERROR_NOT_SUPPORTED:			szErrorVal = "VC_ERROR_NOT_SUPPORTED";			break;
		case VC_ERROR_INVALID_STATE:			szErrorVal = "VC_ERROR_INVALID_STATE";			break;
		case VC_ERROR_INVALID_LANGUAGE:			szErrorVal = "VC_ERROR_INVALID_LANGUAGE";		break;
		case VC_ERROR_ENGINE_NOT_FOUND:			szErrorVal = "VC_ERROR_ENGINE_NOT_FOUND";		break;
		case VC_ERROR_OPERATION_FAILED:			szErrorVal = "VC_ERROR_OPERATION_FAILED";		break;
		case VC_ERROR_OPERATION_REJECTED:		szErrorVal = "VC_ERROR_OPERATION_REJECTED";		break;
		case VC_ERROR_ITERATION_END:			szErrorVal = "VC_ERROR_ITERATION_END";			break;
		case VC_ERROR_EMPTY:					szErrorVal = "VC_ERROR_EMPTY";					break;
	}
	return szErrorVal;
}

/**
* @function         CTs_platform_permission_VoiceControl_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_VoiceControl_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_VoiceControl_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_VoiceControl_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_VoiceControl_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_VoiceControl_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:Checking tizen.org/privilege/recorder privilege
//& type: auto
/**
* @testcase			CTc_VoiceControl_PrivilegeRecorder
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To test vc_initialize and vc_deinitialize					
* @apicovered		Call vc_initialize, vc_deinitialize
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_VoiceControl_PrivilegeRecorder(void)
{
	START_TEST;
	int nRet = -1;
	bool bIsVcFeatureSupported = true;
	bIsVcFeatureSupported = TCTCheckSystemInfoFeatureSupported(MICROPHONEFEATURE, API_NAMESPACE) && TCTCheckSystemInfoFeatureSupported(SPEECHCONTROLFEATURE, API_NAMESPACE);
	if ( false == bIsVcFeatureSupported )
    {
        FPRINTF("[Line : %d][%s] [%s] and [%s] is not supported\\n", __LINE__, API_NAMESPACE, MICROPHONEFEATURE, SPEECHCONTROLFEATURE);
        return 0;
    }
	
	nRet = vc_initialize();	
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "vc_initialize", VoiceControlGetError(nRet),vc_deinitialize(),VC_ERROR_NONE);
		
	return 0;
}

