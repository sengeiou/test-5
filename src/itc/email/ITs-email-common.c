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
#include "ITs-email-common.h"

/** @addtogroup itc-email
*  @ingroup itc
*  @{
*/

extern char g_pstrRecipient[CONFIG_VALUE_LEN_MAX];

//Add helper function definitions here

/**
* @function 		EmailGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EmailGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case EMAILS_ERROR_NONE:									szErrorVal = "EMAILS_ERROR_NONE";								break;
	case EMAILS_ERROR_OUT_OF_MEMORY:						szErrorVal = "EMAILS_ERROR_OUT_OF_MEMORY";						break;
	case EMAILS_ERROR_INVALID_PARAMETER:					szErrorVal = "EMAILS_ERROR_INVALID_PARAMETER";					break;
	case EMAILS_ERROR_SERVER_NOT_READY:						szErrorVal = "EMAILS_ERROR_SERVER_NOT_READY";					break;
	case EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED:		szErrorVal = "EMAILS_ERROR_COMMUNICATION_WITH_SERVER_FAILED";	break;
	case EMAILS_ERROR_OPERATION_FAILED:						szErrorVal = "EMAILS_ERROR_OPERATION_FAILED";					break;
	case EMAILS_ERROR_ACCOUNT_NOT_FOUND:					szErrorVal = "EMAILS_ERROR_ACCOUNT_NOT_FOUND";					break;
	case EMAILS_ERROR_DB_FAILED:							szErrorVal = "EMAILS_ERROR_DB_FAILED";							break;
	case EMAILS_ERROR_PERMISSION_DENIED:					szErrorVal = "EMAILS_ERROR_PERMISSION_DENIED";					break; 
	case EMAILS_ERROR_NOT_SUPPORTED:						szErrorVal = "EMAILS_ERROR_NOT_SUPPORTED";						break;//ACR 992

	
	default:												szErrorVal = "Undefined Error";									break;
	}

	return szErrorVal;
}

/**
* @function 		EmailGetRecipientType
* @description	 	Maps recipient type enums to string values
* @parameter		nRecipient : Recipient type
* @return 			Recipient type string
*/
char* EmailGetRecipientType(int nRecipient)
{
	char* szRecipientType = NULL;

	switch ( nRecipient )
	{
	case EMAIL_RECIPIENT_TYPE_TO:		szRecipientType = "EMAIL_RECIPIENT_TYPE_TO";		break;
	case EMAIL_RECIPIENT_TYPE_CC:		szRecipientType = "EMAIL_RECIPIENT_TYPE_CC";		break;
	case EMAIL_RECIPIENT_TYPE_BCC:		szRecipientType = "EMAIL_RECIPIENT_TYPE_BCC";		break;
	default:							szRecipientType = "Unknown Recipient Type";			break;
	}

	return szRecipientType;
}

bool CreateEmailMessageWithoutAttachment(email_h email)
{
	/* Set Email Message Subject */
	int nRet = email_set_subject(email, EMAILSUBJECT);
	if ( nRet != EMAILS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] email_set_subject failed, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		return false;
	}

	/* Set Email Message Body */
	nRet = email_set_body(email, EMAILBODY);
	if ( nRet != EMAILS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] email_set_body failed, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		return false;
	}

	/* Add Email Message Recipient */
	nRet = email_add_recipient(email, EMAIL_RECIPIENT_TYPE_TO, g_pstrRecipient);
	if ( nRet != EMAILS_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] email_add_recipient failed, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		return false;
	}

	return true;
}

bool CreateEmailMessageWithAttachment(email_h email) {
	bool bRet = CreateEmailMessageWithoutAttachment(email);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] failed to create email message without attachment\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	/* Add Attachment to the Email Message */
	char *pszImagePath = EmailGetDataPath(IMAGE_NAME);
	if(pszImagePath == NULL)
	{
		FPRINTF("[Line : %d][%s] EmailGetDataPath failed,\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	int nRet = email_add_attach(email, pszImagePath);
	if ( nRet != EMAILS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] email_add_attach failed, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		FREE_MEMORY(pszImagePath);
		return false;
	}
	FREE_MEMORY(pszImagePath);
	return true;
}

bool SendEmailMessageWithoutAttachment(email_h email)
{
	bool bRet = CreateEmailMessageWithoutAttachment(email);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] failed to create email message without attachment\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	/* Send Email Message */
	int nRet = email_send_message(email, true);
	if ( nRet != EMAILS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] email_send_message failed, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		return false;
	}

	return true;
}

/**
* @function 			EmailGetDataPath
* @description 			Get the path to application data directory
* @parameter	[IN]	char* pszFileName [file name]
* @return 				NA
*/
char* EmailGetDataPath(char *pszFileName)
{
	char *pszAppData =  app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_data_path() returned invalid path\\n", __LINE__, API_NAMESPACE);
		return pszImgPath;
	}
	
	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName) + 1);
	if(pszImgPath == NULL)
		return pszImgPath;
	snprintf(pszImgPath, strlen(pszAppData) + strlen(pszFileName) + 1, "%s%s",pszAppData, pszFileName );
	FPRINTF("[Line : %d][%s] app_get_data_path() is %s\\n", __LINE__, API_NAMESPACE, pszImgPath);
	return pszImgPath;
}

/** @} */
