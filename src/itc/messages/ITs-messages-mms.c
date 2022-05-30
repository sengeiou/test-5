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
#include "ITs-messages-common.h"

messages_service_h g_pstHandleMessageServiceMms = NULL;

bool g_bMessageServiceMms = false;
bool g_bFeatureMismatchMms = false;
bool g_bFeatureNotSupportedMms = false;

/**
* @function 		ITs_messages_startup
* @description	 	Opens a handle for a messaging service and Creates a message handle
* @parameter		NA
* @return 			NA
*/
void ITs_messages_mms_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Messages_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bFeatureMismatchMms = false;
	g_bFeatureNotSupportedMms = false;
	g_bIsTelephonyFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	int nRet = messages_open_service(&g_pstHandleMessageServiceMms);
	if ( !g_bIsTelephonyFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_open_service returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, MessagesGetError(nRet));
			g_bFeatureMismatchMms = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_open_service correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, MessagesGetError(nRet));
			g_bFeatureNotSupportedMms = true;
		}
		return;
	}
	if ( nRet == MESSAGES_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] messages_open_service in startup passed\\n", __LINE__, API_NAMESPACE);
		g_bMessageServiceMms = true;
	}
	else
	{
		FPRINTF("[Line : %d][%s]messages_open_service failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		g_bMessageServiceMms = false;
	}
	
	g_bIsTelephonyFeatureMmsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_MMS, API_NAMESPACE);
	return;
}

/**
* @function 		ITs_messages_cleanup
* @description	 	Close a handle for a messaging service and Destroy a message handle
* @parameter		NA
* @return 			NA
*/
void ITs_messages_mms_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Messages_p\\n", __LINE__, API_NAMESPACE);
#endif
	
	if ( g_bIsTelephonyFeatureSupported && g_bMessageServiceMms )
	{
		int nRet = messages_close_service(g_pstHandleMessageServiceMms);
		if ( nRet == MESSAGES_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s]messages_close_service passed cleanUp\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s]messages_close_service failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE, nRet,MessagesGetError(nRet));
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s]messages_open_service failed\\n", __LINE__, API_NAMESPACE);
	}
	g_pstHandleMessageServiceMms = NULL;

	return;
}

//& purpose: Add/Get attachment
//& type: auto
/**
* @testcase 			ITc_messages_mms_add_get_attachement_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds/Get the attachment MMS message.
* @scenario				Create MMS message\n
* 						Add attachment\n
* 						Get attachment
* @apicovered			messages_mms_add_attachment, messages_mms_get_attachment
* @passcase				When messages_mms_add_attachment and  messages_mms_get_attachment are successful.
* @failcase				If target API messages_mms_add_attachment or messages_mms_get_attachment fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_mms_add_get_attachement_p(void)
{
	START_TEST_MMS;

	messages_message_h stHandleMMSMessage = NULL;
	char *pszPath = NULL;
	char pPath[PATH_LEN] = {0,};
	if ( false == MessagesAppendToAppDataPath(MESSAGES_IMAGE_FILE, pPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	messages_media_type_e eMessageMediaType;
	messages_media_type_e eMessagesMediaType[] = {
		MESSAGES_MEDIA_UNKNOWN,
		MESSAGES_MEDIA_IMAGE,
		MESSAGES_MEDIA_AUDIO,
		MESSAGES_MEDIA_VIDEO
	};

	int nEnumSize = sizeof(eMessagesMediaType) / sizeof(eMessagesMediaType[0]);
	int nEnumCounter = 0;

	g_bIsTelephonyFeatureMmsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_MMS, API_NAMESPACE);

	int nRet = messages_create_message(MESSAGES_TYPE_MMS, &stHandleMMSMessage);

	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_create_message() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_create_message failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_create_message", MessagesGetError(nRet));

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		nRet = messages_mms_add_attachment(stHandleMMSMessage, eMessagesMediaType[nEnumCounter], MESSAGES_IMAGE_FILE);
		usleep(2000000);
		if ( !g_bIsTelephonyFeatureMmsSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] messages_mms_add_attachment() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
			}
			else
			{
				FPRINTF("[Line : %d][%s] messages_mms_add_attachment failed for unsuported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			}
			return 1;
		}
		PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_add_attachment", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));

		nRet = messages_mms_get_attachment(stHandleMMSMessage, 0, &eMessageMediaType, &pszPath);
		if ( !g_bIsTelephonyFeatureMmsSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] messages_mms_get_attachment() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
			}
			else
			{
				FPRINTF("[Line : %d][%s] messages_mms_get_attachment failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			}
			return 1;
		}
		FREE_MEMORY(pszPath);
		PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_get_attachment", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));
	}

	nRet = messages_destroy_message (stHandleMMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_destroy_message", MessagesGetError(nRet));

	return 0;
}

//& purpose: Gets the attachment with the specified index
//& type: auto
/**
* @testcase 			ITc_messages_mms_get_attachement_count_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the attachment with the specified index
* @scenario				Create MMS message\n
* 						Gets the attachment with the specified index
* @apicovered			messages_mms_get_attachment_count
* @passcase				When messages_mms_get_attachment_count is successful.
* @failcase				If target API messages_mms_get_attachment_count fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_mms_get_attachement_count_p(void)
{
	START_TEST_MMS;

	messages_message_h stHandleMMSMessage = NULL;
	int nCount = 0;

	g_bIsTelephonyFeatureMmsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_MMS, API_NAMESPACE);

	int nRet = messages_create_message(MESSAGES_TYPE_MMS, &stHandleMMSMessage);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_create_message() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_create_message failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_create_message", MessagesGetError(nRet));


	nRet = messages_mms_get_attachment_count(stHandleMMSMessage, &nCount);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_mms_get_attachment_count() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_mms_get_attachment_count failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_get_attachment_count", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));

	nRet = messages_destroy_message (stHandleMMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_destroy_message", MessagesGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets the subject of a message
//& type: auto
/**
* @testcase 			ITc_messages_mms_set_get_subject_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets/Gets the subject of a message
* @scenario				Create MMS message\n
*						Sets the subject of a message\n
* 						Gets the subject of a message
* @apicovered			messages_mms_set_subject, messages_mms_get_subject,
* @passcase				When messages_mms_set_subject and messages_mms_get_subject are successful.
* @failcase				If target API messages_mms_set_subject and messages_mms_get_subject are fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_mms_set_get_subject_p(void)
{
	START_TEST_MMS;

	messages_message_h stHandleMMSMessage = NULL;
	const char *pInputSubject = "mms message subject";
	char *pSubject = NULL;
	
	g_bIsTelephonyFeatureMmsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_MMS, API_NAMESPACE);

	int nRet = messages_create_message(MESSAGES_TYPE_MMS, &stHandleMMSMessage);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_create_message() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_create_message failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_create_message", MessagesGetError(nRet));

	nRet = messages_mms_set_subject(stHandleMMSMessage,pInputSubject);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_mms_set_subject() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_mms_set_subject failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_set_subject", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));

	nRet = messages_mms_get_subject(stHandleMMSMessage, &pSubject);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_mms_get_subject() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_mms_get_subject failed for unsuported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_get_subject", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));
	if ( strcmp( pSubject, pInputSubject ) != 0 )
	{
		FPRINTF("[Line : %d][%s] messages_mms_get_subject failed since pSubject in messages_mms_get_subject is not same, as set\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pSubject);
		messages_destroy_message (stHandleMMSMessage);
		return 1;
	}

	FREE_MEMORY(pSubject);

	nRet = messages_destroy_message (stHandleMMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_destroy_message", MessagesGetError(nRet));

	return 0;
}

//& purpose: Removes all attachments from a MMS message
//& type: auto
/**
* @testcase 			ITc_messages_mms_remove_all_attachments_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Removes all attachments from a MMS message
* @scenario				Create MMS message\n
*						Removes all attachments from a MMS message
* @apicovered			messages_mms_remove_all_attachments
* @passcase				When messages_mms_remove_all_attachments is successful.
* @failcase				If target API messages_mms_remove_all_attachments is fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_mms_remove_all_attachments_p(void)
{
	START_TEST_MMS;
	
	messages_message_h stHandleMMSMessage = NULL;
	
	g_bIsTelephonyFeatureMmsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_MMS, API_NAMESPACE);

	int nRet = messages_create_message(MESSAGES_TYPE_MMS, &stHandleMMSMessage);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_create_message() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_create_message failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_create_message", MessagesGetError(nRet));

	nRet = messages_mms_remove_all_attachments(stHandleMMSMessage);
	if ( !g_bIsTelephonyFeatureMmsSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_mms_remove_all_attachments() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_mms_remove_all_attachments failed for unsuported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_mms_remove_all_attachments", MessagesGetError(nRet), messages_destroy_message (stHandleMMSMessage));

	nRet = messages_destroy_message (stHandleMMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_destroy_message", MessagesGetError(nRet));

	return 0;
}
