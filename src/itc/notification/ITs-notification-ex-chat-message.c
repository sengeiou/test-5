//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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

#include "ITs-notification-common.h"
/**
* @function		ITs_notification_ex_chat_message_startup
* @description		Called before each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_chat_message_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_notification_ex_chat_message_startup \\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

/**
* @function		ITs_notification_ex_chat_message_cleanup
* @description		Called after each test
* @parameter		NA
* @return		NA
*/
void ITs_notification_ex_chat_message_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_notification_ex_chat_message_cleanup \\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
//& type : auto
//& purpose: Creates the notification_ex item handle for the chat message.
/**
* @testcase			ITc_noti_ex_item_chat_message_create_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates the notification_ex item handle for the chat message.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Check for handle and check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_create
* @passcase			noti_ex_item_chat_message_create is successful and return correct value
* @failcase			noti_ex_item_chat_message_create failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Free Title pointer memory and destroy handle.
*/
int ITc_noti_ex_item_chat_message_create_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemChatMsg = NULL;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	noti_ex_item_chat_message_type_e eChatMsgType[] = {
		NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_USER,
		NOTI_EX_ITEM_CHAT_MESSAGE_TYPE_SENDER
	};

	int nEnumSize = sizeof(eChatMsgType) / sizeof(eChatMsgType[0]);
	int nEnumCounter;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++)
	{
		//Taregt API
		nRet = noti_ex_item_chat_message_create(&hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, eChatMsgType[nEnumCounter]);
		PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
		CHECK_HANDLE_CLEANUP(hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

		nRet = noti_ex_item_destroy(hItemChatMsg);
		PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));
	}


	nRet = noti_ex_item_destroy(g_hItemName);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemText);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemImage);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	nRet = noti_ex_item_destroy(g_hItemTime);
	PRINT_RESULT_NORETURN(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_destroy", NotificationExGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the notification_ex item handle for the chat message name.
/**
* @testcase			ITc_noti_ex_item_chat_message_get_name_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the notification_ex item handle for the chat message name.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Get Chat message name and compare with set message name \n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_get_name
* @passcase			noti_ex_item_chat_message_get_name is successful and return correct value
* @failcase			noti_ex_item_chat_message_get_name failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Free Chat Msg pointer memory and destroy handle.
*/
int ITc_noti_ex_item_chat_message_get_name_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGetName = NULL;
	char *pszGetChatName = NULL;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_chat_message_create(&g_hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, g_eChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
	CHECK_HANDLE_CLEANUP(g_hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

	//Taregt API
	nRet = noti_ex_item_chat_message_get_name(g_hItemChatMsg, &hItemGetName);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_get_name", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(hItemGetName, "noti_ex_item_chat_message_get_name", DestroyChatMsgAttributes());

	nRet = noti_ex_item_text_get_contents(hItemGetName, &pszGetChatName);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_get_contents", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(pszGetChatName, "noti_ex_item_text_get_contents", DestroyChatMsgAttributes());

	if( strncmp(g_pszNameText, pszGetChatName, strlen(pszGetChatName) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_chat_message_get_name: return name is different from set name [%s]\\n", __LINE__, API_NAMESPACE, pszGetChatName);
		FREE_MEMORY(pszGetChatName);
		DestroyChatMsgAttributes();

		return 1;
	}
	FREE_MEMORY(pszGetChatName);
	DestroyChatMsgAttributes();

	return 0;
}

//& type : auto
//& purpose: Gets the notification_ex item handle for the chat message text.
/**
* @testcase			ITc_noti_ex_item_chat_message_get_text_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the notification_ex item handle for the chat message name.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Get Chat message name and compare with set message text \n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_get_text
* @passcase			noti_ex_item_chat_message_get_text is successful and return correct value
* @failcase			noti_ex_item_chat_message_get_text failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Free Title pointer memory and destroy handles.
*/
int ITc_noti_ex_item_chat_message_get_text_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGetText = NULL;
	char *pszGetChatText = NULL;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_chat_message_create(&g_hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, g_eChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
	CHECK_HANDLE_CLEANUP(g_hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

	//Taregt API
	nRet = noti_ex_item_chat_message_get_text(g_hItemChatMsg, &hItemGetText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_get_text", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(hItemGetText, "noti_ex_item_chat_message_get_text", DestroyChatMsgAttributes());

	nRet = noti_ex_item_text_get_contents(hItemGetText, &pszGetChatText);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_text_get_contents", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(pszGetChatText, "noti_ex_item_text_get_contents", DestroyChatMsgAttributes());

	if( strncmp(g_pszTextText, pszGetChatText, strlen(pszGetChatText) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_chat_message_get_text: return chat message text is different from set chat message text [%s]\\n", __LINE__, API_NAMESPACE, pszGetChatText);
		FREE_MEMORY(pszGetChatText);
		DestroyChatMsgAttributes();

		return 1;
	}

	FREE_MEMORY(pszGetChatText);
	DestroyChatMsgAttributes();

	return 0;
}

//& type : auto
//& purpose: Gets the notification_ex item handle for the chat message image.
/**
* @testcase			ITc_noti_ex_item_chat_message_get_image_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the notification_ex item handle for the chat message image.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Get Chat message image path and compare with set message image path \n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_get_image
* @passcase			noti_ex_item_chat_message_get_image is successful and return correct value
* @failcase			noti_ex_item_chat_message_get_image failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Free Image Path pointer memory and destroy handles.
*/
int ITc_noti_ex_item_chat_message_get_image_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_h hItemGetImage = NULL;
	char *pszGetImagePath = NULL;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_chat_message_create(&g_hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, g_eChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
	CHECK_HANDLE_CLEANUP(g_hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

	//Taregt API
	nRet = noti_ex_item_chat_message_get_image(g_hItemChatMsg, &hItemGetImage);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_get_image", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(hItemGetImage, "noti_ex_item_chat_message_get_image", DestroyChatMsgAttributes());

	nRet = noti_ex_item_image_get_image_path(hItemGetImage, &pszGetImagePath);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_image_get_image_path", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(pszGetImagePath, "noti_ex_item_image_get_image_path", DestroyChatMsgAttributes());

	if( strncmp(g_pszImagePath, pszGetImagePath, strlen(pszGetImagePath) + 1) )
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_chat_message_get_image: return image path is different from set image path [%s]\\n", __LINE__, API_NAMESPACE, pszGetImagePath);
		FREE_MEMORY(pszGetImagePath);
		DestroyChatMsgAttributes();

		return 1;
	}

	FREE_MEMORY(pszGetImagePath);
	DestroyChatMsgAttributes();

	return 0;
}

//& type : auto
//& purpose: Gets the notification_ex item handle for the chat message time.
/**
* @testcase			ITc_noti_ex_item_chat_message_get_time_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the notification_ex item handle for the chat message time.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Get Chat message time and compare with set message time \n
*				Check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_get_time
* @passcase			noti_ex_item_chat_message_get_time is successful and return correct value
* @failcase			noti_ex_item_chat_message_get_time failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Free Title pointer memory and destroy handle.
*/
int ITc_noti_ex_item_chat_message_get_time_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	int nDiffTime = -1;
	noti_ex_item_h hItemGetTime = NULL;
	time_t tGetCurrTime;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_chat_message_create(&g_hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, g_eChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
	CHECK_HANDLE_CLEANUP(g_hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

	//Taregt API
	nRet = noti_ex_item_chat_message_get_time(g_hItemChatMsg, &hItemGetTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_get_time", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	CHECK_HANDLE_CLEANUP(hItemGetTime, "noti_ex_item_chat_message_get_time", DestroyChatMsgAttributes());

	nRet = noti_ex_item_time_get_time(hItemGetTime, &tGetCurrTime);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_time_get_time", NotificationExGetError(nRet), DestroyChatMsgAttributes());

	nDiffTime = difftime(tGetCurrTime, g_tCurrTime);

	if(nDiffTime)
	{
		FPRINTF("[Line : %d][%s] noti_ex_item_time_get_time: Get Time and Set Time is different and time difference is [%d]\\n", __LINE__, API_NAMESPACE, nDiffTime);
		DestroyChatMsgAttributes();
		return 1;
	}
	DestroyChatMsgAttributes();

	return 0;
}

//& type : auto
//& purpose: Gets the type of chat message.
/**
* @testcase			ITc_noti_ex_item_chat_message_get_message_type_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the type of chat message.
* @scenario			Creates the notification_ex item handle for the chat message \n
*				Gets the type of chat message and check for Pass/Fail.
* @apicovered			noti_ex_item_chat_message_get_message_type
* @passcase			noti_ex_item_chat_message_get_message_type is successful and return correct value
* @failcase			noti_ex_item_chat_message_get_message_type failed or return null value
* @precondition			Name, Text and Image must be created before creating chat message.
* @postcondition		Destroy handle.
*/
int ITc_noti_ex_item_chat_message_get_message_type_p(void)
{
	START_TEST;

	int nRet = NOTI_EX_ERROR_NONE;
	noti_ex_item_chat_message_type_e eGetChatMsgType;

	nRet = CreateChatMsgAttributes();
	if(nRet)
	{
		FPRINTF("[Line : %d][%s] One of the API inside CreateChatMsgAttributes() is failed \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = noti_ex_item_chat_message_create(&g_hItemChatMsg, g_pszChatID, g_hItemName, g_hItemText, g_hItemImage, g_hItemTime, g_eChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_create", NotificationExGetError(nRet), noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));
	CHECK_HANDLE_CLEANUP(g_hItemChatMsg, "noti_ex_item_chat_message_create", noti_ex_item_destroy(g_hItemName); noti_ex_item_destroy(g_hItemText); noti_ex_item_destroy(g_hItemImage); noti_ex_item_destroy(g_hItemTime));

	//Taregt API
	nRet = noti_ex_item_chat_message_get_message_type(g_hItemChatMsg, &eGetChatMsgType);
	PRINT_RESULT_CLEANUP(NOTI_EX_ERROR_NONE, nRet, "noti_ex_item_chat_message_get_message_type", NotificationExGetError(nRet), DestroyChatMsgAttributes());
	PRINT_RESULT_CLEANUP(g_eChatMsgType, eGetChatMsgType, "noti_ex_item_chat_message_get_message_type", "Retrieved chat message type is not same", DestroyChatMsgAttributes());

	DestroyChatMsgAttributes();

	return 0;
}
