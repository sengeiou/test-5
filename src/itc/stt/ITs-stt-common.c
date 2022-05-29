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
#include "ITs-stt-common.h"
/** @addtogroup itc-stt
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		TimeoutFunction
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
* @function 		SttGetError
* @description	 	Maps stt_error_e enums to string values
* @parameter		nError : error code returned
* @return 			error string
*/
char* SttGetError(stt_error_e nError)
{
	char *szErrorVal = NULL;
	switch ( nError )
	{
	case STT_ERROR_NONE:						szErrorVal = "STT_ERROR_NONE";						break;
	case STT_ERROR_OUT_OF_MEMORY:				szErrorVal = "STT_ERROR_OUT_OF_MEMORY";				break;
	case STT_ERROR_INVALID_PARAMETER:			szErrorVal = "STT_ERROR_INVALID_PARAMETER";			break;
	case STT_ERROR_IO_ERROR:					szErrorVal = "STT_ERROR_IO_ERROR";					break;
	case STT_ERROR_TIMED_OUT:					szErrorVal = "STT_ERROR_TIMED_OUT";					break;
	case STT_ERROR_OPERATION_FAILED:			szErrorVal = "STT_ERROR_OPERATION_FAILED";			break;
	case STT_ERROR_RECORDER_BUSY:				szErrorVal = "STT_ERROR_RECORDER_BUSY";				break;
	case STT_ERROR_OUT_OF_NETWORK:				szErrorVal = "STT_ERROR_OUT_OF_NETWORK";			break;
	case STT_ERROR_INVALID_STATE:				szErrorVal = "STT_ERROR_INVALID_STATE";				break;
	case STT_ERROR_INVALID_LANGUAGE:			szErrorVal = "STT_ERROR_INVALID_LANGUAGE";			break;
	case STT_ERROR_ENGINE_NOT_FOUND:			szErrorVal = "STT_ERROR_ENGINE_NOT_FOUND";			break;
	case STT_ERROR_NOT_SUPPORTED:				szErrorVal = "STT_ERROR_NOT_SUPPORTED";				break;
	case STT_ERROR_NOT_SUPPORTED_FEATURE:		szErrorVal = "STT_ERROR_NOT_SUPPORTED_FEATURE";		break;
	case STT_ERROR_PERMISSION_DENIED:			szErrorVal = "STT_ERROR_PERMISSION_DENIED";			break;
	case STT_ERROR_RECORDING_TIMED_OUT:			szErrorVal = "STT_ERROR_RECORDING_TIMED_OUT";		break;
	case STT_ERROR_NO_SPEECH:					szErrorVal = "STT_ERROR_NO_SPEECH";					break;
	case STT_ERROR_IN_PROGRESS_TO_READY:		szErrorVal = "STT_ERROR_IN_PROGRESS_TO_READY";		break;
	case STT_ERROR_IN_PROGRESS_TO_RECORDING:	szErrorVal = "STT_ERROR_IN_PROGRESS_TO_RECORDING";	break;
	case STT_ERROR_IN_PROGRESS_TO_PROCESSING:	szErrorVal = "STT_ERROR_IN_PROGRESS_TO_PROCESSING";	break;
	case STT_ERROR_SERVICE_RESET:				szErrorVal = "STT_ERROR_SERVICE_RESET";				break;
	default:									szErrorVal = "Undefined Error";						break;
	}
	return szErrorVal;
}
/**
* @function 		StteGetError
* @description	 	Maps stte_error_e enums to string values
* @parameter		nError : error code returned
* @return 			error string
*/
char* StteGetError(stte_error_e nError)
{
	char *szErrorVal = NULL;
	switch ( nError )
	{
	case STTE_ERROR_NONE:						szErrorVal = "STTE_ERROR_NONE";						break;
	case STTE_ERROR_OUT_OF_MEMORY:				szErrorVal = "STTE_ERROR_OUT_OF_MEMORY";			break;
	case STTE_ERROR_IO_ERROR:					szErrorVal = "STTE_ERROR_IO_ERROR";					break;
	case STTE_ERROR_INVALID_PARAMETER:			szErrorVal = "STTE_ERROR_INVALID_PARAMETER";		break;
	case STTE_ERROR_NETWORK_DOWN:				szErrorVal = "STTE_ERROR_NETWORK_DOWN";				break;
	case STTE_ERROR_INVALID_STATE:				szErrorVal = "STTE_ERROR_INVALID_STATE";			break;
	case STTE_ERROR_INVALID_LANGUAGE:			szErrorVal = "STTE_ERROR_INVALID_LANGUAGE";			break;
	case STTE_ERROR_OPERATION_FAILED:			szErrorVal = "STTE_ERROR_OPERATION_FAILED";			break;
	case STTE_ERROR_NOT_SUPPORTED_FEATURE:		szErrorVal = "STTE_ERROR_NOT_SUPPORTED_FEATURE";	break;
	case STTE_ERROR_PERMISSION_DENIED:			szErrorVal = "STTE_ERROR_PERMISSION_DENIED";		break;
	case STTE_ERROR_RECORDING_TIMED_OUT:		szErrorVal = "STTE_ERROR_RECORDING_TIMED_OUT";		break;
	default:									szErrorVal = "Undefined Error";						break;
	}
	return szErrorVal;
}

/**
* @function 		SttGetOptionForSilenceDetection
* @description	 	Maps stt_option_silence_detection_e enums to string values
* @parameter		nOption : silent detection option
* @return 			silent detection option string
*/
char* SttGetOptionForSilenceDetection(stt_option_silence_detection_e nOption)
{
	char *szOption = "Undefined Option";
	switch ( nOption )
	{
	case STT_OPTION_SILENCE_DETECTION_FALSE:	szOption = "STT_OPTION_SILENCE_DETECTION_FALSE";	break;
	case STT_OPTION_SILENCE_DETECTION_TRUE:		szOption = "STT_OPTION_SILENCE_DETECTION_TRUE";		break;
	case STT_OPTION_SILENCE_DETECTION_AUTO:		szOption = "STT_OPTION_SILENCE_DETECTION_AUTO";		break;
	}

	return szOption;
}

/**
* @function 		SttGetResultEvent
* @description	 	Maps stt_result_event_e enums to string values
* @parameter		nEvent : result event
* @return 			result event string
*/
char* SttGetResultEvent(stt_result_event_e nEvent)
{
	char *szEvent = "Undefined Option";
	switch ( nEvent )
	{
	case STT_RESULT_EVENT_FINAL_RESULT:		szEvent = "STT_RESULT_EVENT_FINAL_RESULT";		break;
	case STT_RESULT_EVENT_PARTIAL_RESULT:	szEvent = "STT_RESULT_EVENT_PARTIAL_RESULT";	break;
	case STT_RESULT_EVENT_ERROR:			szEvent = "STT_RESULT_EVENT_ERROR";				break;
	}

	return szEvent;
}

/**
* @function 		SttGetResultTimeEvent
* @description	 	Maps stt_result_time_event_e enums to string values
* @parameter		nRet : result time event
* @return 			result time event string
*/
char* SttGetResultTimeEvent(stt_result_time_event_e nEvent)
{
	char *szEvent = "Undefined Result Time Event";
	switch ( nEvent )
	{
	case STT_RESULT_TIME_EVENT_BEGINNING:	szEvent = "STT_RESULT_TIME_EVENT_BEGINNING";	break;	//Event when the token is beginning type
	case STT_RESULT_TIME_EVENT_MIDDLE:		szEvent = "STT_RESULT_TIME_EVENT_MIDDLE";		break;	//Event when the token is middle type
	case STT_RESULT_TIME_EVENT_END:			szEvent = "STT_RESULT_TIME_EVENT_END";			break;	//Event when the token is end type
	}

	return szEvent;
}

/**
* @function 		SttGetState
* @description	 	Maps stt_state_e enums to string values
* @parameter		nState : state
* @return 			state string
*/
char* SttGetState(stt_state_e nState)
{
	char *szState = "Undefined State";
	switch ( nState )
	{
	case STT_STATE_CREATED:		szState = "STT_STATE_CREATED";		break;
	case STT_STATE_READY:		szState = "STT_STATE_READY";		break;
	case STT_STATE_RECORDING:	szState = "STT_STATE_RECORDING";	break;
	case STT_STATE_PROCESSING:	szState = "STT_STATE_PROCESSING";	break;
	}

	return szState;
}

/**
* @function 		SttGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool SttGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		SttAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool SttAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == SttGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}
/** @} */