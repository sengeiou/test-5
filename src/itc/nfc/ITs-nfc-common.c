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
#include "ITs-nfc-common.h"

/** @addtogroup itc-nfc
* @ingroup		itc
* @{
*/

extern app_control_h g_app_control_handler;

/**
* @function			NFCGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* NFCGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case NFC_ERROR_NONE:					szErrorVal = "NFC_ERROR_NONE";						break;
	case NFC_ERROR_OUT_OF_MEMORY:			szErrorVal = "NFC_ERROR_OUT_OF_MEMORY";				break;
	case NFC_ERROR_OPERATION_FAILED:		szErrorVal = "NFC_ERROR_OPERATION_FAILED";			break;
	case NFC_ERROR_INVALID_PARAMETER:		szErrorVal = "NFC_ERROR_INVALID_PARAMETER";			break;
	case NFC_ERROR_INVALID_NDEF_MESSAGE:	szErrorVal = "NFC_ERROR_INVALID_NDEF_MESSAGE";		break;
	case NFC_ERROR_INVALID_RECORD_TYPE:		szErrorVal = "NFC_ERROR_INVALID_RECORD_TYPE";		break;
	case NFC_ERROR_TIMED_OUT:				szErrorVal = "NFC_ERROR_TIMED_OUT";					break;
	case NFC_ERROR_DEVICE_BUSY:				szErrorVal = "NFC_ERROR_DEVICE_BUSY";				break;
	case NFC_ERROR_NO_DEVICE:				szErrorVal = "NFC_ERROR_NO_DEVICE";					break;
	case NFC_ERROR_NOT_ACTIVATED:			szErrorVal = "NFC_ERROR_NOT_ACTIVATED";				break;
	case NFC_ERROR_NOT_SUPPORTED:			szErrorVal = "NFC_ERROR_NOT_SUPPORTED";				break;
	case NFC_ERROR_ALREADY_ACTIVATED:		szErrorVal = "NFC_ERROR_ALREADY_ACTIVATED";			break;
	case NFC_ERROR_ALREADY_DEACTIVATED:		szErrorVal = "NFC_ERROR_ALREADY_DEACTIVATED";		break;
	case NFC_ERROR_READ_ONLY_NDEF:			szErrorVal = "NFC_ERROR_READ_ONLY_NDEF";			break;
	case NFC_ERROR_NO_SPACE_ON_NDEF:		szErrorVal = "NFC_ERROR_NO_SPACE_ON_NDEF";			break;
	case NFC_ERROR_NO_NDEF_MESSAGE:			szErrorVal = "NFC_ERROR_NO_NDEF_MESSAGE";			break;
	case NFC_ERROR_NOT_NDEF_FORMAT:			szErrorVal = "NFC_ERROR_NOT_NDEF_FORMAT";			break;
	case NFC_ERROR_SECURITY_RESTRICTED:		szErrorVal = "NFC_ERROR_SECURITY_RESTRICTED";		break;
	default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function			NFCTagFilterEnumString
* @description	 	Enumerations for NFC Tag filter
* @parameter[IN]	nRet: enum value
* @return			pszEnumString: enum value as a string
*/
char* NFCTagFilterEnumString(int nRet)
{
	char *pszEnumString = NULL;
	switch ( nRet )
	{
	case NFC_TAG_FILTER_ALL_DISABLE:			pszEnumString = "NFC_TAG_FILTER_ALL_DISABLE";			break;
	case NFC_TAG_FILTER_ISO14443A_ENABLE:		pszEnumString = "NFC_TAG_FILTER_ISO14443A_ENABLE";		break;
	case NFC_TAG_FILTER_ISO14443B_ENABLE:		pszEnumString = "NFC_TAG_FILTER_ISO14443B_ENABLE";		break;
	case NFC_TAG_FILTER_ISO15693_ENABLE:		pszEnumString = "NFC_TAG_FILTER_ISO15693_ENABLE";		break;
	case NFC_TAG_FILTER_FELICA_ENABLE:			pszEnumString = "NFC_TAG_FILTER_FELICA_ENABLE";			break;
	case NFC_TAG_FILTER_JEWEL_ENABLE:			pszEnumString = "NFC_TAG_FILTER_JEWEL_ENABLE";			break;
	case NFC_TAG_FILTER_IP_ENABLE:				pszEnumString = "NFC_TAG_FILTER_IP_ENABLE";				break;
	case NFC_TAG_FILTER_ALL_ENABLE:				pszEnumString = "NFC_TAG_FILTER_ALL_ENABLE";			break;
	default:									pszEnumString = "Unknown Filter";						break;
	}
	return pszEnumString;
}

/**
* @function			NFCSeTypeEnumString
* @description	 	Enumerations for NFC Secure Element type
* @parameter[IN]	nRet: enum value
* @return			pszEnumString: enum value as a string
*/
char* NFCSeTypeEnumString(int nRet)
{
	char *pszEnumString = NULL;
	switch ( nRet )
	{
	case NFC_SE_TYPE_DISABLE:		pszEnumString = "NFC_SE_TYPE_DISABLE";		break;
	case NFC_SE_TYPE_ESE:			pszEnumString = "NFC_SE_TYPE_ESE";			break;
	case NFC_SE_TYPE_UICC:			pszEnumString = "NFC_SE_TYPE_UICC";			break;
	default: 						pszEnumString = "UNKNOWN";					break;
	}
	return pszEnumString;
}

/**
* @function			NFCGetTnfEnumString
* @description	 	Maps type enums to string values
* @parameter[IN]	nRet: enum value
* @return			pszEnumString: enum value as a string
*/
char* NFCGetTnfEnumString(int nRet)
{
	char *pszEnumString = NULL;
	switch ( nRet )
	{
	case NFC_RECORD_TNF_EMPTY:			pszEnumString = "NFC_RECORD_TNF_EMPTY";				break;
	case NFC_RECORD_TNF_WELL_KNOWN:		pszEnumString = "NFC_RECORD_TNF_WELL_KNOWN";		break;
	case NFC_RECORD_TNF_MIME_MEDIA:		pszEnumString = "NFC_RECORD_TNF_MIME_MEDIA";		break;
	case NFC_RECORD_TNF_URI:			pszEnumString = "NFC_RECORD_TNF_URI";				break;
	case NFC_RECORD_TNF_EXTERNAL_RTD:	pszEnumString = "NFC_RECORD_TNF_EXTERNAL_RTD";		break;
	case NFC_RECORD_TNF_UNKNOWN:		pszEnumString = "NFC_RECORD_TNF_UNKNOWN";			break;
	case NFC_RECORD_TNF_UNCHANGED:		pszEnumString = "NFC_RECORD_TNF_UNCHANGED";			break;
	default:					 		pszEnumString = "Unknown Record";					break;
	}
	return pszEnumString;
}

/**
* @function			NFCGetEncodeEnumString
* @description	 	Maps type enums to string values
* @parameter[IN]	nRet: enum value
* @return			pszEnumString: enum value as a string
*/
char * NFCGetEncodeEnumString(int nRet)
{
	char *pszEnumString = NULL;
	switch ( nRet )
	{
	case NFC_ENCODE_UTF_8:		pszEnumString = "NFC_ENCODE_UTF_8";		break;
	case NFC_ENCODE_UTF_16:		pszEnumString = "NFC_ENCODE_UTF_16";	break;
	default:			 		pszEnumString = "Unknown Encoding";		break;
	}
	return pszEnumString;
}

/**
* @function			NFCCreateMessageRecordHandle
* @description	 	Create ndef message handle and ndef record handle
* @parameter		NA
* @return			true or false
*/
bool NFCCreateMessageRecordHandle(void)
{
	int nRet = nfc_ndef_message_create(&g_hMessage);
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_create failed, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
		return false;
	}
	else if (g_hMessage == NULL )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_message_create' message handle is null\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_create passed\\n", __LINE__, API_NAMESPACE);
	}
	sleep(LONG_DELAY);

	nRet = nfc_ndef_record_create_uri(&g_hRecord, URI);
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_uri failed, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
		return false;
	}
	else if ( g_hRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create_uri', record handle is null.\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_uri passed\\n", __LINE__, API_NAMESPACE);
	}
	sleep(LONG_DELAY);
	return true;
}

/**
* @function			NFCCreateRecordText
* @description	 	Create ndef record text
* @parameter[IN]	encode_type: NFC_ENCODE_UTF_8 or NFC_ENCODE_UTF_16
* @parameter[IN]	nEnumCounter: Counter, to display the iteration no in message
* @return			true or false
*/
bool NFCCreateRecordText(nfc_encode_type_e encode_type, int nEnumCounter)
{
	int nRet = -1;
	if ( encode_type == NFC_ENCODE_UTF_8 )
	{
		nRet = nfc_ndef_record_create_text(&g_hRecord, ENCODE_TEXT, ENCODE_TYPE_UTF8, encode_type);
	}
	else
	{
		nRet = nfc_ndef_record_create_text(&g_hRecord, ENCODE_TEXT, ENCODE_TYPE_UTF16, encode_type);
	}
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_text failed in iteration %d for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, nEnumCounter, NFCGetEncodeEnumString(encode_type), NFCGetError(nRet));
		return false;
	}
	else if ( g_hRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create_text' message handle is null in iteration %d for enum: %s\\n", __LINE__, API_NAMESPACE, nEnumCounter, NFCGetEncodeEnumString(encode_type));
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_text passed for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type));
	}
	return true;
}

/**
* @function			NFCDestroyText
* @description	 	Create ndef record text
* @parameter[IN]	encode_type: NFC_ENCODE_UTF_8 or NFC_ENCODE_UTF_16
* @parameter[IN]	nEnumCounter: Counter, to display the iteration no in message
* @return			NA
*/
void NFCDestroyText(nfc_encode_type_e encode_type, int nEnumCounter)
{
	int nRet = nfc_ndef_record_destroy(g_hRecord);
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy failed in iteration %d for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, nEnumCounter, NFCGetEncodeEnumString(encode_type), NFCGetError(nRet));
	}
	else
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy passed for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type));
	}
}

/**
* @function			NFCCreateUri
* @description	 	Create ndef record for uri
* @parameter]		NA
* @return			true or false
*/
bool NFCCreateUri(void)
{
	int nRet = nfc_ndef_record_create_uri(&g_hRecord, URI);
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_uri failed, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
		return false;
	}
	else if ( g_hRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create_uri', record handle is null.\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_uri passed\\n", __LINE__, API_NAMESPACE);
	}
	return true;
}

/**
* @function 		AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE:					szErrorVal = "APP_CONTROL_ERROR_NONE";						break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";			break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";				break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";				break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";				break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";			break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";			break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";			break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";				break;
	case APP_CONTROL_ERROR_TIMED_OUT:				szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/**
* @function 		LaunchAppToSendMsg
* @description	 	launches application needed for send message
* @parameter		NA
* @return 			true : if app is launched successfully, false : if app is not launched
*/
bool LaunchApp (char *pszRemoteAppId)
{
	bool bIsRunning = false;
	int nCounter = COUNTER;

	int nRet = app_control_create(&g_app_control_handler);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail error returned : %s \\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		return false;
	}

	if ( g_app_control_handler == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create fail created handle value null \\n", __LINE__, API_NAMESPACE);
		app_control_destroy(g_app_control_handler);
		return false;
	}

	nRet = app_control_set_app_id(g_app_control_handler , pszRemoteAppId);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id fail error returned : %s \\n", __LINE__, API_NAMESPACE , AppControlGetError(nRet));
		app_control_destroy(g_app_control_handler);
		return false;
	}

	do {

		nRet = app_manager_is_running(pszRemoteAppId, &bIsRunning);
		if(nRet == APP_MANAGER_ERROR_NONE)
		{
			if (!bIsRunning) {
				nRet = app_control_send_launch_request(g_app_control_handler , NULL , NULL);
				if ( nRet != APP_CONTROL_ERROR_NONE )
				{
					sleep(1);
				}
			}
		}

	} while (--nCounter > 0 && !bIsRunning);

	if ( !bIsRunning )
	{
		FPRINTF("[Line : %d][%s] app_control_send_launch_request failed \\n", __LINE__, API_NAMESPACE);
		app_control_destroy(g_app_control_handler);
		return false;
	}
	return true;
}

/**
* @function 		TerminateApp
* @description	 	terminates application launched for sending message
* @parameter		NA
* @return 			NA
*/
void TerminateApp()
{
	app_control_send_terminate_request(g_app_control_handler);
	app_control_destroy(g_app_control_handler);
}

/** @} */ //end of itc-nfc
