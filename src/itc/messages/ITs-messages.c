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

/** @addtogroup itc-messages
* @ingroup		itc
* @{
*/

messages_message_h g_pstHandleSMSMessage = NULL;
messages_service_h g_pstHandleMessageService = NULL;

bool g_bMessagesCreation = false;
bool g_bMessageService = false;
bool g_bMessagesCB = false;
bool g_bFeatureMismatch = false;
bool g_bFeatureNotSupported = false;
bool g_bMessagesCBParameter = false;

/**
* @function 		MessagesSearchCB
* @description	 	Called when a message is retrieved from a search request
* @parameter		msg : The message handle, index : The index of a message from the messages\n
*					result_count : The count of the messages that have been retrieved, nTotal_count : The count of the messages\n
*					data : The user data passed from the for each function
* @return 			NA
*/
bool MessagesSearchCB(messages_message_h msg, int index, int result_count, int nTotal_count, void * data)
{
	g_bMessagesCB = true;
	if(msg == NULL)
	{
		FPRINTF("[Line : %d][%s] message handle is NULL\\n", __LINE__, API_NAMESPACE);
		g_bMessagesCBParameter = false;
	}
	else if(index<0)
	{
		FPRINTF("[Line : %d][%s] index is not valid\\n", __LINE__, API_NAMESPACE);
		g_bMessagesCBParameter = false;
	}
	else if(result_count<0)
	{
		FPRINTF("[Line : %d][%s] result_count is not valid\\n", __LINE__, API_NAMESPACE);
		g_bMessagesCBParameter = false;
	}
	else
	{
		g_bMessagesCBParameter = true;
	}
	FPRINTF("[Line : %d][%s] nTotal_count = %d \\n", __LINE__, API_NAMESPACE,nTotal_count);
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
	return true;
}

/**
* @function 		MessagesSetMessageSentCB
* @description	 	Called when the process of sending a message to all recipients is finished
* @parameter		result : The result of message sending, user_data : The user data passed from the callback registration function
* @return 			NA
*/
void MessagesSetMessageSentCB(messages_sending_result_e result, void *user_data)
{
	g_bMessagesCB = true;
	if((result < -1) || (result > 0))
	{
		FPRINTF("[Line : %d][%s] message sending result is not valid\\n", __LINE__, API_NAMESPACE);
		g_bMessagesCBParameter = false;
	}
	else
	{
		g_bMessagesCBParameter = true;
	}
	
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}

/**
* @function 		IncomingCB
* @description		Called when an incoming message is received
* @parameter		incoming_msg : An incoming message, data : The user data passed from the callback registration function
* @return 			NA
*/
void IncomingCB(messages_message_h incoming_msg, void * data)
{
	g_bMessagesCB = true;
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}

/**
* @function 		PushCallback
* @description		Called when an incoming push message is received
* @parameter		header : The header of the push message\n
*					body : The body of the push message (it is not a null-terminated string)\n
*					body length : The length of body\n
*					user : The user data to be passed to the callback function
* @return 			NA
*/
static void PushCallback(const char *header, const char *body, int body_length, void* data)
{
	g_bMessagesCB = true;
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}
/**
* @function 		ITs_messages_startup
* @description	 	Opens a handle for a messaging service and Creates a message handle
* @parameter		NA
* @return 			NA
*/
void ITs_messages_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Messages_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsTelephonyFeatureSupported = true;
	g_bFeatureMismatch = false;
	g_bFeatureNotSupported = false;

	g_bIsTelephonyFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	int nRet = messages_open_service(&g_pstHandleMessageService);
	if ( !g_bIsTelephonyFeatureSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_open_service returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MessagesGetError(nRet));
			g_bFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_open_service correctly returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE,  MessagesGetError(nRet));
			g_bFeatureNotSupported = true;
		}
		return;
	}
	if ( nRet != MESSAGES_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] messages_open_service failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE,  nRet, MessagesGetError(nRet));
		g_bMessageService = false;
		return;
	}
	else if(g_pstHandleMessageService == NULL)
	{
		FPRINTF("[Line : %d][%s] messages_open_service failed, Handle is NULL \\n", __LINE__, API_NAMESPACE);
		g_bMessageService = false;
		return;
	}
	else
	{
		FPRINTF("[Line : %d][%s] messages_open_service in startup passed\\n", __LINE__, API_NAMESPACE);
		g_bMessageService = true;
	}

	nRet = messages_create_message(MESSAGES_TYPE_SMS, &g_pstHandleSMSMessage);
	if ( nRet != MESSAGES_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to create message, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE,  nRet,MessagesGetError(nRet));
		g_bMessagesCreation = false;
	}
	else if(g_pstHandleSMSMessage == NULL)
	{
		FPRINTF("[Line : %d][%s] messages_create_message failed, Handle is NULL \\n", __LINE__, API_NAMESPACE);
		g_bMessagesCreation = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] message created successfully startup\\n", __LINE__, API_NAMESPACE);
		g_bMessagesCreation = true;
	}

	return;
}

/**
* @function 		ITs_messages_cleanup
* @description	 	Close a handle for a messaging service and Destroy a message handle
* @parameter		NA
* @return 			NA
*/
void ITs_messages_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Messages_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = 0;
	if ( g_bIsTelephonyFeatureSupported && g_bMessagesCreation )
	{
		nRet = messages_destroy_message(g_pstHandleSMSMessage);
		if ( nRet == MESSAGES_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] messages_destroy_message passed cleanUp\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_destroy_message failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE,  nRet,MessagesGetError(nRet));
		}
	}

	if ( g_bMessageService )
	{
		nRet = messages_close_service(g_pstHandleMessageService);
		if ( nRet == MESSAGES_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] messages_close_service passed cleanUp\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_close_service failed, error returned = %d(%s)\\n", __LINE__, API_NAMESPACE, nRet, MessagesGetError(nRet));
		}
	}
	g_pstHandleMessageService = NULL;

	return;
}

/** @addtogroup	itc-messages-testcases
* @brief 		Integration testcases for module messages
* @ingroup		itc-messages
* @{
*/

//& purpose: Adds/Get a recipient's address to the message
//& type: auto
/**
* @testcase 			ITc_messages_add_get_address_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a recipient's address (phone number) to the message
* @scenario				Create SMS message\n
*						Add recipient's address\n
*						Get recipient's address
* @apicovered			messages_add_address, messages_get_address, messages_get_address_count, messages_remove_all_addresses
* @passcase				When messages_add_address, messages_get_address, messages_get_address_count and messages_remove_all_addresses are successful.
* @failcase				If target API messages_add_address, messages_get_address, messages_get_address_count and messages_remove_all_addresses are fails or any precondition API fails.
* @precondition			Message handle must be created, Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle must be released
*/
int ITc_messages_add_get_address_p(void)
{
	START_TEST;
	
	messages_recipient_type_e recipient_type;
	int nRet = 0, nIndex=0, nNoOfRecipents = 0;
	char *pAaddress=NULL;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE ))
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	messages_recipient_type_e eMessagesRecipientType[] = {
		MESSAGES_RECIPIENT_UNKNOWN,
		MESSAGES_RECIPIENT_TO,
		MESSAGES_RECIPIENT_CC,
		MESSAGES_RECIPIENT_BCC
	};

	int nEnumSize = sizeof(eMessagesRecipientType) / sizeof(eMessagesRecipientType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0;nEnumCounter<nEnumSize;nEnumCounter++)
	{
		nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, eMessagesRecipientType[nEnumCounter] );
		PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet));

		nRet = messages_get_address(g_pstHandleSMSMessage, nIndex, &pAaddress, &recipient_type);
		PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_get_address", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));
		CHECK_VALUE_STRING(pAaddress, "messages_get_address");
		
		if(recipient_type != MESSAGES_RECIPIENT_TO)
		{
			FPRINTF("[Line : %d][%s] messages_get_address failed, recipient type is mismatched\\n", __LINE__, API_NAMESPACE);
			messages_remove_all_addresses(g_pstHandleSMSMessage);
			FREE_MEMORY(pAaddress);
			return 1;
		}

		nRet = messages_get_address_count(g_pstHandleSMSMessage, &nNoOfRecipents);
		PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_get_address_count", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage);FREE_MEMORY(pAaddress));
		//CHECK_VALUE_INT(nNoOfRecipents, "messages_get_address_count");
		if(nNoOfRecipents == 0)
		{
			FPRINTF("[Line : %d][%s] messages_get_address_count failed, Number of recipents is zero\\n", __LINE__, API_NAMESPACE);
			messages_remove_all_addresses(g_pstHandleSMSMessage);
			FREE_MEMORY(pAaddress);
			return 1;
		}

		nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
		PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet),FREE_MEMORY(pAaddress));
		
		FREE_MEMORY(pAaddress);
	}

	return 0;
}

//& purpose: Gets the message box type of a message
//& type: auto
/**
* @testcase 			ITc_messages_get_mboxType_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the message box type of a message
* @scenario				Create SMS message\n
*						Gets the message box type of a message
* @apicovered			messages_get_mbox_type
* @passcase				When  messages_get_mbox_type is successful.
* @failcase				If target API messages_get_mbox_type fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_get_mboxType_p(void)
{
	START_TEST;
	
	messages_message_box_e eBoxType = -1;
	int nRet = messages_get_mbox_type(g_pstHandleSMSMessage, &eBoxType);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_mbox_type", MessagesGetError(nRet));
	if((eBoxType < MESSAGES_MBOX_ALL) || (eBoxType > MESSAGES_MBOX_DRAFT))
	{
		FPRINTF("[Line : %d][%s] messages_get_mbox_type failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the message count in the specific message box
//& type: auto
/**
* @testcase 			ITc_messages_get_message_count_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the message count in the specific message box
* @scenario				Create SMS message\n
*						Gets the message count in the specific message box
* @apicovered			messages_get_message_count
* @passcase				When  messages_get_message_cout is successful.
* @failcase				If target API messages_get_message_count fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_get_message_count_p(void)
{
	START_TEST;
	
	const char* pData = "CALL BACK FOR INCOMING MMS";
	const char *pMsgText = "Test Message Text";
	int nTimeoutId = 0;
	int nCount = 0;
	
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE) )
	{
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_message_incoming_cb(g_pstHandleMessageService, IncomingCB, (void*)pData);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_sim_id(g_pstHandleSMSMessage, 1);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_sim_id", MessagesGetError(nRet), 	messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	g_bMessagesCB = false;
	g_bMessagesCBParameter = false;
	nRet = messages_send_message(g_pstHandleMessageService, g_pstHandleSMSMessage, true, MessagesSetMessageSentCB, NULL);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_send_message", MessagesGetError(nRet), 	messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	if ( g_bMessagesCB == false )
	{
		FPRINTF("[Line : %d][%s] MessagesSetMessageSentCB failed\\n", __LINE__, API_NAMESPACE);
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}
	else if ( g_bMessagesCBParameter == false )
	{
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}
		
	nRet = messages_get_message_count(g_pstHandleMessageService, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN, &nCount);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_message_count", MessagesGetError(nRet));
	CHECK_VALUE_INT(nCount, "messages_get_message_count");

	nRet = messages_unset_message_incoming_cb(g_pstHandleMessageService);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_unset_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT_NORETURN(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

//& purpose: Adds an additional listening port for the incoming SMS messages
//& type: auto
/**
* @testcase 			ITc_messages_add_get_sms_listening_port_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the message count in the specific message box
* @scenario				Create SMS message\n
*						Add listening port for the incoming SMS messages
* @apicovered			messages_add_sms_listening_port
* @passcase				When  messages_add_sms_listening_port is successful.
* @failcase				If target API messages_add_sms_listening_port fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_add_get_sms_listening_port_p(void)
{
	START_TEST;
	
	messages_service_h pstHandleMessageService = NULL;
	int nAddPort = ADD_PORT;
	int nGetPort = -1;
	
	int nRet = messages_open_service(&pstHandleMessageService);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_open_service", MessagesGetError(nRet));
	CHECK_HANDLE(pstHandleMessageService, "messages_open_service");

	nRet = messages_add_sms_listening_port(pstHandleMessageService, nAddPort);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_add_sms_listening_port", MessagesGetError(nRet), messages_close_service(pstHandleMessageService));

	nRet =  messages_get_message_port(g_pstHandleSMSMessage, &nGetPort);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_get_message_port", MessagesGetError(nRet), messages_close_service(pstHandleMessageService));
	if(nGetPort == -1)
	{
		FPRINTF("[Line : %d][%s] messages_get_message_port failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = messages_close_service(pstHandleMessageService);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_close_service", MessagesGetError(nRet));

	return 0;
}

//& purpose: Glets the type of a message
//& type: auto
/**
* @testcase 			ITc_messages_get_message_type_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the type of a message
* @scenario				Create SMS message\n
*						Gets the message type
* @apicovered			messages_get_message_type
* @passcase				When  messages_get_message_type is successful.
* @failcase				If target API messages_get_message_type fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_get_message_type_p(void)
{
	START_TEST;
	
	messages_message_type_e eMsgType = -1;
	int nRet = messages_get_message_type(g_pstHandleSMSMessage, &eMsgType);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_message_type", MessagesGetError(nRet));
	if((eMsgType<MESSAGES_TYPE_UNKNOWN)||(eMsgType>MESSAGES_TYPE_SMS_ETWS_SECONDARY))
	{
		FPRINTF("[Line : %d][%s] messages_get_message_type failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets/Gets the text of a message.
//& type: auto
/**
* @testcase 			ITc_messages_set_get_text_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get the text of a message.
* @scenario				Create SMS message\n
*						Sets message text\n
*						Gets message text
* @apicovered			messages_set_text, messages_get_text
* @passcase				When  messages_set_text and messages_get_text are successful.
* @failcase				If target API messages_set_text and messages_get_text are fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_set_get_text_p(void)
{
	START_TEST;
	
	const char *pText = "this is the text";
	char* pTextget = NULL;
	
	int nRet = messages_set_text(g_pstHandleSMSMessage, pText);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet));

	nRet = messages_get_text(g_pstHandleSMSMessage, &pTextget);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_text", MessagesGetError(nRet));

	if ( strcmp( pTextget, pText ) != 0 )
	{
		FPRINTF("[Line : %d][%s] pTextget in messages_get_text is not same, as set\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pTextget);
		return 1;
	}
	FREE_MEMORY(pTextget);

	return 0;
}

//& purpose: Gets the time of a message
//& type: auto
/**
* @testcase 			ITc_messages_get_time_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the time of a message
* @scenario				Create SMS message\n
*						Gets message time
* @apicovered			messages_get_time
* @passcase				When messages_get_time is successful.
* @failcase				If target API messages_get_time fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_get_time_p(void)
{
	START_TEST;
	
	time_t stGetTime = -1;
	int nRet = messages_get_time(g_pstHandleSMSMessage, &stGetTime);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_time", MessagesGetError(nRet));
	if(stGetTime == -1)
	{
		FPRINTF("[Line : %d][%s] messages_get_time failed, output is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Set/Get the sim id of the sending message
//& type: auto
/**
* @testcase 			ITc_messages_set_get_sim_id_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get the sim id of the sending message
* @scenario				Create SMS message
*						Set the sim id of the sending message
*						Get the sim id of the sending message
* @apicovered			messages_set_sim_id, messages_get_sim_id
* @passcase				When  messages_set_sim_id, messages_get_sim_id is successful.
* @failcase				If target API messages_set_sim_id, messages_get_sim_id fails or any precondition API fails.
* @precondition			Message handle must be created
* @postcondition		Message handle must be released
*/
int ITc_messages_set_get_sim_id_p(void)
{
	START_TEST;
	
	int nSetSimId = 1, nGetSimId = -1;
	int nRet = messages_set_sim_id(g_pstHandleSMSMessage, nSetSimId);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_set_sim_id", MessagesGetError(nRet));

	nRet = messages_get_sim_id(g_pstHandleSMSMessage, &nGetSimId);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_get_sim_id", MessagesGetError(nRet));
	FPRINTF("[Line : %d][%s] sim id = [%d]\\n", __LINE__, API_NAMESPACE,  nGetSimId);
	if ( nSetSimId != nGetSimId )
	{
		FPRINTF("[Line : %d][%s] messages_get_sim_id is failed since Set Sim id: %d and Get Sim id: %d in ITc_messages_get_sim_id_p is not same\\n", __LINE__, API_NAMESPACE, nSetSimId, nGetSimId);
		return 1;
	}

	return 0;
}

//& purpose: Registers a callback to be invoked when a WAP Push message is received
//& type: auto
/**
* @testcase 			ITc_messages_push_add_remove_incoming_cb_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback to be invoked when a WAP Push message is received
* @scenario				handle for a messaging service\n
*						Registers a callback to be invoked when a WAP Push message is received
* @apicovered			messages_push_add_incoming_cb
* @passcase				When messages_push_add_incoming_cb
* @failcase				If target API messages_push_add_incoming_cb fails or any precondition API fails.
* @precondition			Message service handle must be created,
* @postcondition		Message service handle must be released
*/
int ITc_messages_push_add_remove_incoming_cb_p(void)
{
	START_TEST;
	
	int nRet = messages_push_add_incoming_cb(g_pstHandleMessageService, PUSH_TEST_APP_ID, PushCallback, NULL);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_push_add_incoming_cb", MessagesGetError(nRet));

	nRet = messages_push_remove_incoming_cb(g_pstHandleMessageService, PUSH_TEST_APP_ID);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_push_remove_incoming_cb", MessagesGetError(nRet));

	return 0;
}

//& purpose: Registers/Deregister an application to the mapping table of the WAP Push service
//& type: auto
/**
* @testcase 			ITc_messages_push_register_deregister_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers/Deregister an application to the mapping table of the WAP Push service
* @scenario				handle for a messaging service\n
*						Registers an application to the mapping table of the WAP Push service\n
*						Deregister an application to the mapping table of the WAP Push service
* @apicovered			messages_push_register
* @passcase				When messages_push_register 
* @failcase				If target API messages_push_register fails or any precondition API fails.
* @precondition			Message service handle must be created,
* @postcondition		Message service handle must be released
*/
int ITc_messages_push_register_deregister_p(void)
{
	START_TEST;
	
	int nRet = messages_push_register(g_pstHandleMessageService, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_push_register", MessagesGetError(nRet));

	nRet = messages_push_deregister(g_pstHandleMessageService, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_push_deregister", MessagesGetError(nRet));

	return 0;
}

//& purpose: Re-registers an application to the mapping table of the WAP Push service
//& type: auto
/**
* @testcase 			ITc_messages_push_reregister_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Re-registers an application to the mapping table of the WAP Push service
* @scenario				handle for a messaging service\n
*						Re-registers an application to the mapping table of the WAP Push service
* @apicovered			messages_push_reregister
* @passcase				When messages_push_reregister 
* @failcase				If target API messages_push_reregister fails or any precondition API fails.
* @precondition			Message service handle must be created,
* @postcondition		Message service handle must be released
*/
int ITc_messages_push_reregister_p(void)
{
	START_TEST;
	
	int nRet = messages_push_reregister(g_pstHandleMessageService, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_push_reregister", MessagesGetError(nRet));

	return 0;
}

//& purpose: Send message.
//& type: Manual
/**
* @testcase 			ITc_messages_send_message_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Send message
* @scenario				Add recipient address\n
* 						Set message text\n
* 						Send message\n
*						Set message incoming callback\n
* 						Check callback\n
* 						Unset message incoming callback
* @apicovered			messages_add_address, messages_set_text, messages_send_message, messages_set_message_incoming_cb, messages_unset_message_incoming_cb
* @passcase				When messages_send_message, messages_set_message_incoming_cb and  messages_unset_message_incoming_cb are successful.
* @failcase				If target API messages_add_address,  messages_set_message_incoming_cb or messages_unset_message_incoming_cb fails or any precondition API fails.
* @precondition			Message handle must be created, message recipient and text must be set
*						Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle must be released
*/

int ITc_messages_send_message_p(void)
{
	START_TEST;
	
	const char* pData = "CALL BACK FOR INCOMING MMS";
	const char *pMsgText = "Test Message Text";
	int nTimeoutId = 0;
	
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE) )
	{
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_message_incoming_cb(g_pstHandleMessageService, IncomingCB, (void*)pData);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_sim_id(g_pstHandleSMSMessage, 1);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_sim_id", MessagesGetError(nRet), 	messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	g_bMessagesCB = false;
	g_bMessagesCBParameter = false;
	nRet = messages_send_message(g_pstHandleMessageService, g_pstHandleSMSMessage, true, MessagesSetMessageSentCB, NULL);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_send_message", MessagesGetError(nRet), 	messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	if ( g_bMessagesCB == false )
	{
		FPRINTF("[Line : %d][%s] MessagesSetMessageSentCB failed\\n", __LINE__, API_NAMESPACE);
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}
	else if ( g_bMessagesCBParameter == false )
	{
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}

	nRet = messages_unset_message_incoming_cb(g_pstHandleMessageService);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_unset_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

//& purpose: Search message/by ID and free message array
//& type: auto
/**
* @testcase 			ITc_messages_search_getid_searchbyid_freemessage_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Search message, search message by id and free message array
* @scenario				Add recipient address\n
*						Search message\n
* 						Get message ID\n
* 						Search message by id\n
*						Destroy used message handle in search message\n
*						Free message by ID
* @apicovered			messages_search_message, messages_get_message_id, messages_search_message_by_id, messages_free_message_array
* @passcase				When messages_search_message, messages_get_message_id, messages_search_message_by_id,\n
*						messages_destroy_message and messages_free_message_array are successful.
* @failcase				If target API or any supporting API fails.
* @precondition			Message handle and message service handle must be created\n
*						Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle and message service handle must be released
*/
int ITc_messages_search_getid_searchbyid_freemessage_p(void)
{
	START_TEST;
	
	messages_message_h stHandleSMSMessage = NULL;
	const char *pKeyword = "Test";
	const char *pMsgText = "Test Message Text 1";
	
	messages_message_h *pSearched_message_array = NULL;
	int nSearched_message_length = 0, nTotalMsg = 0, nId=0;
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};

	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE))
	{
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_message_incoming_cb(g_pstHandleMessageService, IncomingCB, NULL);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "g_pstHandleMessageService", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_sim_id(g_pstHandleSMSMessage, 1);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_sim_id", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_send_message(g_pstHandleMessageService, g_pstHandleSMSMessage, true, MessagesSetMessageSentCB, NULL);
	usleep(3000000);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_send_message", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	char *pszSearchValue = strdup(pszValue + 4);
	FPRINTF("[Line : %d][%s] Search message recipient = %s\\n", __LINE__, API_NAMESPACE,  pszSearchValue);

	nRet = messages_search_message(g_pstHandleMessageService, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN, pKeyword, pszSearchValue, 0, 0,	&pSearched_message_array, &nSearched_message_length, &nTotalMsg);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_search_message", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage);FREE_MEMORY(pszSearchValue));

	if ( nSearched_message_length <= 0 )
	{
		FPRINTF("[Line : %d][%s] There is no message in message Array[]\\n", __LINE__, API_NAMESPACE);
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		FREE_MEMORY(pszSearchValue);
		return 1;
	}
	FREE_MEMORY(pszSearchValue);

	nRet = messages_get_message_id(pSearched_message_array[0], &nId);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_get_message_id", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));
	CHECK_VALUE_INT(nId, "messages_get_message_id");

	nRet = messages_search_message_by_id(g_pstHandleMessageService, nId, &stHandleSMSMessage);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_search_message_by_id", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));
	CHECK_HANDLE(stHandleSMSMessage, "messages_search_message_by_id");

	nRet = messages_free_message_array(pSearched_message_array);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_free_message_array", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_unset_message_incoming_cb(g_pstHandleMessageService);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_unset_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

//& purpose: Retrieves the found messages
//& type: auto
/**
* @testcase 			ITc_messages_foreach_message_p
* @since_tizen			2.3
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Send message
* @scenario				Create message handle\n
* 						Retrieves the found messages by invoking the given callback function iteratively
* @apicovered			messages_foreach_message
* @passcase				When messages_send_message is successful.
* @failcase				If target API messages_add_address fails or any precondition API fails.
* @precondition			Message handle must be created, message recipient and text must be successful,\n
*						Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle must be released
*/
int ITc_messages_foreach_message_p(void)
{
	START_TEST;
	
	int nTimeoutId = 0;
	const char *pKeyWord = "test";
	const char *pMsgText = "Test Message Text 1";
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	
	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE) )
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_message_incoming_cb(g_pstHandleMessageService, IncomingCB, NULL);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_sim_id(g_pstHandleSMSMessage, 1);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_sim_id", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_send_message(g_pstHandleMessageService, g_pstHandleSMSMessage, true, MessagesSetMessageSentCB, NULL);
	usleep(3000000);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_send_message", MessagesGetError(nRet), messages_unset_message_incoming_cb(g_pstHandleMessageService);messages_remove_all_addresses(g_pstHandleSMSMessage));

	g_bMessagesCB = false;
	g_bMessagesCBParameter = false;
	nRet = messages_foreach_message(g_pstHandleMessageService, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN, pKeyWord, pszValue, 0, 1, MessagesSearchCB, NULL);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_foreach_message", MessagesGetError(nRet));
	
	RUN_POLLING_LOOP;
	if ( !g_bMessagesCB )
	{
		FPRINTF("[Line : %d][%s] Callback [MessagesSearchCB] failed\\n", __LINE__, API_NAMESPACE);
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}
	else if(!g_bMessagesCBParameter)
	{
		messages_unset_message_incoming_cb(g_pstHandleMessageService);
		messages_remove_all_addresses(g_pstHandleSMSMessage);
		return 1;
	}

	nRet = messages_unset_message_incoming_cb(g_pstHandleMessageService);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_unset_message_incoming_cb", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

//& purpose:  Adds the message to message database
//& type: auto
/**
* @testcase 			ITc_messages_add_message_p
* @since_tizen			2.3
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			 Adds the message to message database
* @scenario				Create message handle\n
* 						Adds the message to message database
* @apicovered			messages_add_message
* @passcase				When messages_add_message is successful.
* @failcase				If target API messages_add_address fails or any precondition API fails.
* @precondition			Message handle must be created, message recipient and text must be successful,\n
*						Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle must be released
*/
int ITc_messages_add_message_p(void)
{
	START_TEST;
	
	int nTimeoutId = 0;
	int nMsgId = -1;
	const char *pMsgText = "Test Message Text 1";
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	
	g_bIsTelephonyFeatureTelephonySupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_TELEPHONY, API_NAMESPACE);
	
	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE) )
	{
	#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
	#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	if ( !g_bIsTelephonyFeatureTelephonySupported )
	{
		
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_add_address() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_add_address failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
					
	}
		
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet =  messages_add_message(g_pstHandleMessageService, g_pstHandleSMSMessage, &nMsgId);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, " messages_add_message", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));
	CHECK_VALUE_INT(nMsgId, "messages_add_message");
	
	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT_NORETURN(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

//& purpose: Sets message box type of a message
//& type: auto
/**
* @testcase 			ITc_messages_set_mbox_type_p
* @since_tizen			2.3
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			Sets message box type of a message
* @scenario				Create message handle\n
* 						Sets message box type of a message
* @apicovered			messages_set_mbox_type
* @passcase				When messages_set_mbox_type is successful.
* @failcase				If target API messages_set_mbox_type fails or any precondition API fails.
* @precondition			Message handle must be created
*						
* @postcondition		Message handle must be released
*/
int ITc_messages_set_mbox_type_p(void)
{
	START_TEST;
		
	messages_message_box_e mbox = MESSAGES_MBOX_INBOX;

	
	g_bIsTelephonyFeatureTelephonySupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_TELEPHONY, API_NAMESPACE);
	//target API
	int nRet =  messages_set_mbox_type(g_pstHandleSMSMessage,mbox);

	if ( !g_bIsTelephonyFeatureTelephonySupported )
	{
		
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_set_mbox_type() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_set_mbox_type failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
					
	}
	
	PRINT_RESULT(MESSAGES_ERROR_NONE, nRet, " messages_set_mbox_type", MessagesGetError(nRet));
		

	return 0;
}

//& purpose:   Sets display time from a message
//& type: auto
/**
* @testcase 			ITc_messages_set_time_p
* @since_tizen			2.3
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @description			  Sets display time from a message
* @scenario				Create message handle\n
* 						Sets display time from a message
* @apicovered			messages_add_message
* @passcase				When messages_add_message is successful.
* @failcase				If target API messages_add_address fails or any precondition API fails.
* @precondition			Message handle must be created, message recipient and text must be successful,\n
*						Change the [MOBILE_NUMBER] parameter in ITs-messages-common.h accordingly for [messages_add_address]
* @postcondition		Message handle must be released
*/
int ITc_messages_set_time_p(void)
{
	START_TEST;
		
	 time_t stSetTime = {0};
	 const char *pMsgText = "Test Message Text 1";
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	
	
	g_bIsTelephonyFeatureTelephonySupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE_TELEPHONY, API_NAMESPACE);

	if ( true == GetValueFromConfigFile("MESSAGES_MOBILE_NUMBER", pszValue, API_NAMESPACE) )
	{
	#if DEBUG
		FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
	#endif
	}
	else
	{
		FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	int nRet = messages_add_address(g_pstHandleSMSMessage, pszValue, MESSAGES_RECIPIENT_TO);
	if ( !g_bIsTelephonyFeatureTelephonySupported )
	{
		
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] messages_add_address() returned %d(%s) error for unsupported MMS feature\\n", __LINE__, API_NAMESPACE, nRet, 				MessagesGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] messages_add_address failed for unsupported (http://tizen.org/feature/network.telephony.mms ) MMS telephony feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
					
	}
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_add_address", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet = messages_set_text(g_pstHandleSMSMessage, pMsgText);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, "messages_set_text", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));

	nRet =  messages_set_time(g_pstHandleSMSMessage,stSetTime);
	PRINT_RESULT_CLEANUP(MESSAGES_ERROR_NONE, nRet, " messages_add_message", MessagesGetError(nRet), messages_remove_all_addresses(g_pstHandleSMSMessage));
		
	nRet = messages_remove_all_addresses(g_pstHandleSMSMessage);
	PRINT_RESULT_NORETURN(MESSAGES_ERROR_NONE, nRet, "messages_remove_all_addresses", MessagesGetError(nRet));

	return 0;
}

/** @} */ //end of itc-messages
/** @} */ //end of itc-messages-testcases
