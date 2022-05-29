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
#include "ITs-voice-control-common.h"

/** @addtogroup itc-voice-control
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		IterateEcoreLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateEcoreLoop(void)
{
	while(g_CallBackHit != true)
	{
		ecore_main_loop_iterate();
	}
}

/**
* @function 		VoiceControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* VoiceControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case VC_ERROR_NONE:							szErrorVal = "VC_ERROR_NONE";								break;
		case VC_ERROR_OUT_OF_MEMORY:				szErrorVal = "VC_ERROR_OUT_OF_MEMORY";						break;
		case VC_ERROR_IO_ERROR:						szErrorVal = "VC_ERROR_IO_ERROR";							break;
		case VC_ERROR_INVALID_PARAMETER:			szErrorVal = "VC_ERROR_INVALID_PARAMETER";					break;
		case VC_ERROR_TIMED_OUT:					szErrorVal = "VC_ERROR_TIMED_OUT";							break;
		case VC_ERROR_RECORDER_BUSY:				szErrorVal = "VC_ERROR_RECORDER_BUSY";						break;
		case VC_ERROR_PERMISSION_DENIED:			szErrorVal = "VC_ERROR_PERMISSION_DENIED";					break;
		case VC_ERROR_NOT_SUPPORTED:				szErrorVal = "VC_ERROR_NOT_SUPPORTED";						break;
		case VC_ERROR_INVALID_STATE:				szErrorVal = "VC_ERROR_INVALID_STATE";						break;
		case VC_ERROR_INVALID_LANGUAGE:				szErrorVal = "VC_ERROR_INVALID_LANGUAGE";					break;
		case VC_ERROR_ENGINE_NOT_FOUND:				szErrorVal = "VC_ERROR_ENGINE_NOT_FOUND";					break;
		case VC_ERROR_OPERATION_FAILED:				szErrorVal = "VC_ERROR_OPERATION_FAILED";					break;
		case VC_ERROR_OPERATION_REJECTED:			szErrorVal = "VC_ERROR_OPERATION_REJECTED";					break;
		case VC_ERROR_ITERATION_END:				szErrorVal = "VC_ERROR_ITERATION_END";						break;
		case VC_ERROR_EMPTY:						szErrorVal = "VC_ERROR_EMPTY";								break;
		case VC_ERROR_SERVICE_RESET:				szErrorVal = "VC_ERROR_SERVICE_RESET";						break;
		case VC_ERROR_IN_PROGRESS_TO_READY :		szErrorVal = "VC_ERROR_IN_PROGRESS_TO_READY ";			    break;
		case VC_ERROR_IN_PROGRESS_TO_RECORDING :	szErrorVal = "VC_ERROR_IN_PROGRESS_TO_RECORDING  ";			break;
		case VC_ERROR_IN_PROGRESS_TO_PROCESSING :	szErrorVal = "VC_ERROR_IN_PROGRESS_TO_PROCESSING   ";		break;
		default:									szErrorVal = "VC_ERROR_UNKNOWN";							break;
	}
	return szErrorVal;
}

/**
* @function 		CreateCommands
* @description	 	Create commands for command list
* @parameter		NA
* @return 			NA
*/
bool CreateCommands(void)
{
	int nRet = -1;

	nRet = vc_cmd_create(&g_arrhVcCommand[0]);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet));

	nRet = vc_cmd_set_command(g_arrhVcCommand[0], VOICECOMMAND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_command", VoiceControlGetError(nRet), DestroyCommands());

	nRet = vc_cmd_set_type(g_arrhVcCommand[0], VC_COMMAND_TYPE_BACKGROUND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_type", VoiceControlGetError(nRet), DestroyCommands());

	nRet = vc_cmd_create(&g_arrhVcCommand[1]);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_create", VoiceControlGetError(nRet), DestroyCommands());

	nRet = vc_cmd_set_command(g_arrhVcCommand[1], VOICECOMMANDNEW);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_command", VoiceControlGetError(nRet), DestroyCommands());

	nRet = vc_cmd_set_type(g_arrhVcCommand[1], VC_COMMAND_TYPE_BACKGROUND);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_set_type", VoiceControlGetError(nRet), DestroyCommands());

	return 0;
}

/**
* @function 		DestroyCommands
* @description	 	Destroy commands for command list
* @parameter		NA
* @return 			NA
*/
bool DestroyCommands(void)
{
	int nRet = -1;

	if ( g_arrhVcCommand[0] )
	{
		nRet = vc_cmd_destroy(g_arrhVcCommand[0]);
		PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet), vc_cmd_destroy(g_arrhVcCommand[1]));
	}

	if ( g_arrhVcCommand[1] )
	{
		nRet = vc_cmd_destroy(g_arrhVcCommand[1]);
		PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_cmd_destroy", VoiceControlGetError(nRet));
	}

	return 0;
}

/**
* @function 		CreateCommandList
* @description	 	Create command list
* @parameter		NA
* @return 			NA
*/
bool CreateCommandList(void)
{
	int nRet = -1;

	nRet = CreateCommands();
	PRINT_RESULT(0, nRet, "CreateCommands", "Returned Value Not Correct");

	nRet = vc_cmd_list_create(&g_hVcCommandList);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_create", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_add(g_hVcCommandList, g_arrhVcCommand[0]);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_add", VoiceControlGetError(nRet), DestroyCommandList());

	nRet = vc_cmd_list_add(g_hVcCommandList, g_arrhVcCommand[1]);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_add", VoiceControlGetError(nRet), DestroyCommandList());

	return 0;
}

/**
* @function 		DestroyCommandList
* @description	 	Destroy command list
* @parameter		NA
* @return 			NA
*/
bool DestroyCommandList(void)
{
	int nRet = -1;

	if ( g_hVcCommandList )
	{
		nRet = vc_cmd_list_destroy(g_hVcCommandList, false);
		PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_cmd_list_destroy", VoiceControlGetError(nRet), DestroyCommands());
	}

	nRet = DestroyCommands();
	PRINT_RESULT(0, nRet, "DestroyCommands", "Returned Value Not Correct");

	return 0;
}

/**
* @function 		PrepareVoiceControl
* @description	 	Prepare Voice Control
* @parameter		NA
* @return 			NA
*/
bool PrepareVoiceControl(void)
{
	int nRet = -1;

	nRet = vc_set_state_changed_cb(StateChangedCallBack, NULL);
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_set_state_changed_cb", VoiceControlGetError(nRet));

	g_CallBackHit = false;
	nRet = vc_prepare();
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_prepare", VoiceControlGetError(nRet), UnPrepareVoiceControl());
	IterateEcoreLoop();
	PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_prepare", "CallBack Not Invoked", UnPrepareVoiceControl());

	return 0;
}

/**
* @function 		UnPrepareVoiceControl
* @description	 	Prepare Voice Control
* @parameter		NA
* @return 			NA
*/
bool UnPrepareVoiceControl(void)
{
	int nRet = -1;
	vc_state_e eVcState = VC_STATE_INITIALIZED;

	nRet = vc_get_state(&eVcState);
	PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_get_state", VoiceControlGetError(nRet), vc_unprepare(); vc_unset_state_changed_cb());
	if ( eVcState == VC_STATE_READY )
	{
		g_CallBackHit = false;
		nRet = vc_unprepare();
		PRINT_RESULT_CLEANUP(VC_ERROR_NONE, nRet, "vc_unprepare", VoiceControlGetError(nRet), vc_unset_state_changed_cb());
		IterateEcoreLoop();
		PRINT_RESULT_CLEANUP(true, g_CallBackHit, "vc_unprepare", "CallBack Not Invoked", vc_unset_state_changed_cb());
	}

	nRet = vc_unset_state_changed_cb();
	PRINT_RESULT(VC_ERROR_NONE, nRet, "vc_unset_state_changed_cb", VoiceControlGetError(nRet));

	return 0;
}

/** @} */