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
#include "ITs-tts-common.h"

/** @addtogroup itc-tts
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
* @function 		TtsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
**/


char* TtsGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case TTS_ERROR_NONE : szErrorVal = "TTS_ERROR_NONE" ; break;
	case TTS_ERROR_INVALID_PARAMETER : szErrorVal = "TTS_ERROR_INVALID_PARAMETER" ; break;
	case TTS_ERROR_OUT_OF_MEMORY  : szErrorVal = "TTS_ERROR_OUT_OF_MEMORY" ; break;
	case TTS_ERROR_INVALID_STATE : szErrorVal = "TTS_ERROR_INVALID_STATE" ; break;
	case TTS_ERROR_IO_ERROR  : szErrorVal = "TTS_ERROR_IO_ERROR" ; break;
	case TTS_ERROR_OUT_OF_NETWORK  : szErrorVal = "TTS_ERROR_OUT_OF_NETWORK" ; break;
	case TTS_ERROR_INVALID_VOICE  : szErrorVal = "TTS_ERROR_INVALID_VOICE" ; break;
	case TTS_ERROR_ENGINE_NOT_FOUND  : szErrorVal = "TTS_ERROR_ENGINE_NOT_FOUND" ; break;
	case TTS_ERROR_TIMED_OUT   : szErrorVal = "TTS_ERROR_TIMED_OUT" ; break;
	case TTS_ERROR_OPERATION_FAILED   : szErrorVal = "TTS_ERROR_OPERATION_FAILED" ; break;
	case TTS_ERROR_AUDIO_POLICY_BLOCKED   : szErrorVal = "TTS_ERROR_AUDIO_POLICY_BLOCKED" ; break;
	case TTS_ERROR_PERMISSION_DENIED   : szErrorVal = "TTS_ERROR_PERMISSION_DENIED" ; break;
	case TTS_ERROR_NOT_SUPPORTED   : szErrorVal = "TTS_ERROR_NOT_SUPPORTED" ; break;
	case TTS_ERROR_NOT_SUPPORTED_FEATURE   : szErrorVal = "TTS_ERROR_NOT_SUPPORTED_FEATURE" ; break;
	default : szErrorVal = "TTS_ERROR_UNKNOWN" ; break;
	}

	return szErrorVal;
}
/**
* @function 		TtseGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* TtseGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case TTSE_ERROR_NONE:						szErrorVal = "TTSE_ERROR_NONE";						break;
	case TTSE_ERROR_OUT_OF_MEMORY:				szErrorVal = "TTSE_ERROR_OUT_OF_MEMORY";			break;
	case TTSE_ERROR_IO_ERROR:					szErrorVal = "TTSE_ERROR_IO_ERROR";					break;
	case TTSE_ERROR_INVALID_PARAMETER:			szErrorVal = "TTSE_ERROR_INVALID_PARAMETER";		break;
	case TTSE_ERROR_NETWORK_DOWN:				szErrorVal = "TTSE_ERROR_NETWORK_DOWN";				break;
	case TTSE_ERROR_PERMISSION_DENIED:			szErrorVal = "TTSE_ERROR_PERMISSION_DENIED";		break;
	case TTSE_ERROR_INVALID_STATE:				szErrorVal = "TTSE_ERROR_INVALID_STATE";			break;
	case TTSE_ERROR_INVALID_VOICE:				szErrorVal = "TTSE_ERROR_INVALID_VOICE";			break;
	case TTSE_ERROR_OPERATION_FAILED:			szErrorVal = "TTSE_ERROR_OPERATION_FAILED";			break;
	case TTSE_ERROR_NOT_SUPPORTED_FEATURE:		szErrorVal = "TTSE_ERROR_NOT_SUPPORTED_FEATURE";	break;
	case TTSE_ERROR_NOT_SUPPORTED:				szErrorVal = "TTSE_ERROR_NOT_SUPPORTED";			break;
	default:									szErrorVal = "TTS_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}
/**
* @function 			UixTtsPrintAPIErrorMSG
* @description	 		Prints Error API Error message
* @parameter[IN]   	pszAPI[API name]
* 			 [IN]		nRet[API return value]
* @return 				NA
*/
void UixTtsPrintAPIErrorMSG(char *pszAPI, int nRet)
{
	FPRINTF("[Line : %d][%s][%s API Call Failed With Return Value: %d][error is: %s]\\n", __LINE__, API_NAMESPACE, pszAPI, nRet, TtsGetError(nRet));
}

/**
* @function 		TtsTimeoutFunction
* @description	 	Called if some callback is not invoked for a particular Tts Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean TtsTimeoutFunction(gpointer data)
{
	FPRINTF( "\\n [Line : %d][%s] [player_ITC] Callback Tts wait complete for 20 seconds. Timeout\\n",__LINE__, API_NAMESPACE);
	ecore_main_loop_quit();
	return FALSE;
}

/**
* @function 		TtsWaitForAsync
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void TtsWaitForAsync()
{
	g_timeout_add(TIMEOUT, TtsTimeoutFunction, NULL);
	ecore_main_loop_begin();
}

/******************************************************Helpers***********************************************/

/**
* @function 		TtsSetStateChangedCallBacks
* @description	 	Called to set state changed callback
* @parameter		StateChange
* @return 			int
*/

int TtsSetStateChangedCallBacks(tts_state_changed_cb StateChange)
{
	int nRet = tts_set_state_changed_cb(g_pstTts, StateChange, NULL);
	if ( nRet != TTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] tts_set_state_changed_cb failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
		return 1;
	}
	return 0;
}

/**
* @function 		TtsUnSetStateChangedCallBacks
* @description	 	Called to unset state changed callback
* @parameter		NA
* @return 			NA
*/

void TtsUnSetStateChangedCallBacks(void)
{
	FPRINTF("[Line : %d][%s] tts_unset_state_changed_cb is called\\n", __LINE__, API_NAMESPACE);
	tts_unset_state_changed_cb(g_pstTts);
}

/**
* @function 		TtsSetUtteranceCallBacks
* @description	 	Called to set utterance callbacks
* @parameter		StartCallBack, CompleteCallBack
* @return 			int
*/

int TtsSetUtteranceCallBacks(tts_utterance_started_cb StartCallBack, tts_utterance_completed_cb CompleteCallBack)
{
	int nRet =  tts_set_utterance_started_cb(g_pstTts, StartCallBack, NULL);
	if ( nRet < 0 )
	{
		UixTtsPrintAPIErrorMSG("tts_set_utterance_started_cb",nRet);
		return 1;
	}

	nRet =  tts_set_utterance_completed_cb(g_pstTts, CompleteCallBack, NULL);
	if ( nRet < 0 )
	{
		UixTtsPrintAPIErrorMSG("tts_set_utterance_completed_cb",nRet);
		return 1;
	}
	return 0;
}

/**
* @function 		TtsUnSetUtteranceCallBacks
* @description	 	Called to unset utterance callbacks
* @parameter		NA
* @return 			NA
*/

void TtsUnSetUtteranceCallBacks(void)
{
	tts_unset_utterance_started_cb(g_pstTts);
	tts_unset_utterance_completed_cb(g_pstTts);
}

/**
* @function 		TtsPrepare
* @description	 	Called to prepare tts
* @parameter		StateChange
* @return 			bool
*/

bool TtsPrepare(tts_state_changed_cb StateChange)
{
	if ( 1 == TtsSetStateChangedCallBacks(StateChange) )
	{
		return false;
	}

	int nRet = tts_set_mode(g_pstTts, TTS_MODE_DEFAULT);
	if ( nRet < 0 )
	{
		UixTtsPrintAPIErrorMSG("tts_set_mode", nRet);
		return false;
	}

	nRet=tts_prepare(g_pstTts);
	if ( nRet != TTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] tts_prepare failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TtsGetError(nRet));
		return false;
	}
	TtsWaitForAsync();

	return true;
}

/**
* @function 		TtsUnPrepare
* @description	 	Called to unprepare tts
* @parameter		NA
* @return 			NA
*/

void TtsUnPrepare(void)
{
	tts_stop(g_pstTts);
	tts_unprepare(g_pstTts);
	TtsUnSetStateChangedCallBacks();
}
/** @} */

/******************************************************Helpers End*******************************************/
