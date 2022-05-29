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

//& set: Email

char g_pstrRecipient[CONFIG_VALUE_LEN_MAX] = {0,};

/**
* @function 		ITs_email_startup
* @description	 	Called before each test, created email handle
* @parameter		NA
* @return 			NA
*/
void ITs_email_startup(void)
{
	struct stat stBuff;  
        g_eEmailNotSupported=false;
        g_eEmailMismatch    =false; 
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Messaging_Email_p\\n", __LINE__, API_NAMESPACE);
#endif
	//Create Email Message Handle
    
	g_bIsEmailSendFeatureSupported = TCTCheckSystemInfoFeatureSupported(EMAIL_FEATURE, API_NAMESPACE) ;

	int nRet = email_create_message(&g_hEmail);

	if(! g_bIsEmailSendFeatureSupported )
        {
           if(nRet == EMAILS_ERROR_NOT_SUPPORTED)
           {
		FPRINTF("[Line : %d][%s] email_create_message() returned %s error for unsupported feature :success \\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
  		g_eEmailNotSupported=true;
           }
	   else
	   {
                FPRINTF("[Line : %d][%s] email_create_message() returned %s error for unsupported feature,error mismatch :Failure \\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
                g_eEmailMismatch=true;
     	   }
	   return ;
	}

	if ( nRet == EMAILS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Email message handle created successfully in precondition\\n", __LINE__, API_NAMESPACE);
		g_bEmailCreation = true;

		//Initialize recipient email address value from configuration file
		if ( true == GetValueFromConfigFile("EMAIL_RECIPIENT", g_pstrRecipient, API_NAMESPACE) )
		{
#if DEBUG
			FPRINTF("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE, g_pstrRecipient);
#endif
		}
		else
		{
			FPRINTF("[Line : %d][%s] GetValueFromConfigFile returned error in start-up\\n", __LINE__, API_NAMESPACE);

			strncpy(g_pstrRecipient, EMAILADDRESS, CONFIG_VALUE_LEN_MAX-1);
			FPRINTF("[Line : %d][%s] Using recipient address : %s\\n", __LINE__, API_NAMESPACE, EMAILADDRESS);
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to create email message handle, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		g_bEmailCreation = false;
	}

	g_bIsEmailSendFeatureSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE) ||
		TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
}

/**
* @function 		ITs_email_cleanup
* @description	 	Called after each test, destroys email handle
* @parameter		NA
* @return 			NA
*/
void ITs_email_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Messaging_Email_p\\n", __LINE__, API_NAMESPACE);
#endif

	//Destroy Email Message Handle
	if ( g_hEmail != NULL )
	{
		int nRet = email_destroy_message(g_hEmail);
		if ( nRet == 0 )
		{
			FPRINTF("[Line : %d][%s] Email message handle destroyed successfully\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d][%s] Unable to destroy email message handle, error returned = %s\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
		}
	}
}

/**
* @function 		EmailTimeout
* @description	 	Called if some callback is not invoked for a particular EmailTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean EmailTimeout(gpointer data)
{
	GMainLoop *pMainLoop = (GMainLoop *) data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(g_pEmailMainLoop);
		g_main_loop_unref(g_pEmailMainLoop);
		g_pEmailMainLoop = NULL;
	}
	
	FPRINTF("[Line : %d][%s] Callback Time-out\\n", __LINE__, API_NAMESPACE);
	return false;
}

void email_message_sent_callback(email_h email, email_sending_e result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Callback invoked: email_message_sent_callback \\n", __LINE__, API_NAMESPACE);
	g_bCallbackOccurred = true;
	
	if ( email == NULL )
	{
		FPRINTF("[Line : %d][%s] email is NULL in callback email_message_sent_callback\\n", __LINE__, API_NAMESPACE);
		if ( g_pEmailMainLoop )
		{
			g_main_loop_quit(g_pEmailMainLoop);
			g_main_loop_unref(g_pEmailMainLoop);
			g_pEmailMainLoop = NULL;
		}
		return;
	}

	if ( result == EMAIL_SENDING_SUCCEEDED )
	{
		FPRINTF("[Line : %d][%s] email_send_message succeeded\\n", __LINE__, API_NAMESPACE);
		g_bEmailSentSuccess = true;
	}
	else if ( result == EMAIL_SENDING_FAILED )
	{
		FPRINTF("[Line : %d][%s] email_send_message failed\\n", __LINE__, API_NAMESPACE);
		g_bEmailSentSuccess = false;
	}

	if ( g_pEmailMainLoop )
	{
		g_main_loop_quit(g_pEmailMainLoop);
		g_main_loop_unref(g_pEmailMainLoop);
		g_pEmailMainLoop = NULL;
	}
}


/** @addtogroup itc-email-testcases
*  @brief 		Integration testcases for module email
*  @ingroup 	itc-email
*  @{
*/

//& purpose Adds and removes attachment to an email message
//& type: auto
/**
* @testcase   			ITc_email_add_remove_attach_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Adds and removes attachment to an email message
* @scenario				Creates an email message\n
*						Adds a file as an attachment\n
*						Removes the attachment\n
*						Destroys the email message
* @apicovered			email_add_attach, email_remove_all_attachments
* @passcase				If adds and removes the attachment to the email message successfully
* @failcase				If fails to add and remove attachment to the email message
* @precondition			NA
* @postcondition		NA 
*/
int ITc_email_add_remove_attach_p(void)
{
	START_TEST;

	//Target API
	/**** Add Attachment to the Email Message ****/
	char *pszImagePath = EmailGetDataPath(IMAGE_NAME);
	if(pszImagePath == NULL)
	{
		FPRINTF("[Line : %d][%s] EmailGetDataPath failed,\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = email_add_attach(g_hEmail, pszImagePath);
	PRINT_RESULT_CLEANUP(EMAILS_ERROR_NONE, nRet, "email_add_attach", EmailGetError(nRet),FREE_MEMORY(pszImagePath));

	//Target API
	/**** Clears All Attachments of the Email Message ****/
	nRet = email_remove_all_attachments(g_hEmail);
	PRINT_RESULT_CLEANUP(EMAILS_ERROR_NONE, nRet, "email_remove_all_attachments", EmailGetError(nRet),FREE_MEMORY(pszImagePath));
	
	FREE_MEMORY(pszImagePath);

	return 0;
}

//& purpose Adds and removes recipient to an email message
//& type: auto
/**
* @testcase   			ITc_email_add_remove_recipient_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Adds and removes recipient to an email message
* @scenario				Creates an email message\n
*						Adds a recipient\n
*						Removes the recipient\n
*						Destroys the email message
* @apicovered			email_add_recipient, email_remove_all_recipients
* @passcase				If adds and removes the recipient to the email message successfully
* @failcase				If fails to add and remove recipient to the email message
* @precondition			NA
* @postcondition		NA 
*/
int ITc_email_add_remove_recipient_p(void)
{
	START_TEST;

	email_recipient_type_e recipient_type[] = { EMAIL_RECIPIENT_TYPE_TO, EMAIL_RECIPIENT_TYPE_CC, EMAIL_RECIPIENT_TYPE_BCC };
	int enum_size = sizeof(recipient_type) / sizeof(recipient_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		//Target API
		/**** Add Recipient to the Email Message ****/
		int nRet = email_add_recipient(g_hEmail, recipient_type[enum_counter], g_pstrRecipient);
		if ( nRet != EMAILS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] email_add_recipient failed for recipient type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE,
				EmailGetRecipientType(recipient_type[enum_counter]), EmailGetError(nRet));
			return 1;
		}

		//Target API
		/**** Remove All Recipients of the Email Message ****/
		nRet = email_remove_all_recipients(g_hEmail);
		if ( nRet != EMAILS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] email_remove_all_recipients failed for recipient type = %s, error returned = %s\\n", __LINE__, API_NAMESPACE,
				EmailGetRecipientType(recipient_type[enum_counter]), EmailGetError(nRet));
			return 1;
		}
	}

	return 0;
}

//& purpose Create and destroy an email message handle
//& type: auto
/**
* @testcase   			ITc_email_create_destroy_message_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Destroys an email message handle
* @scenario				Creates an Email service\n
*						Destroys an Email service
* @apicovered			email_create_message, email_destroy_message
* @passcase				If creates and destroys the email message handle
* @failcase				If fails to create and destroy the email message handle
* @precondition			NA
* @postcondition		NA 
*/
int ITc_email_create_destroy_message_p(void)
{
	START_TEST;

	email_h email = NULL;

	//Target API
	/**** Create Email Message Handle ****/
	int nRet = email_create_message(&email);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_create_message", EmailGetError(nRet));
	CHECK_HANDLE(email, "email_create_message");

	//Target API
	/**** Destroy Email Message Handle ****/
	nRet = email_destroy_message(email);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_destroy_message", EmailGetError(nRet));

	return 0;
}

//& purpose Saves an email message in outbox
//& type: auto
/**
* @testcase   			ITc_email_save_message_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Creates an email message handle for sending an email message
* @scenario				Creates an email message\n
*						Saves the email message in outbox\n
*						Destroys the email message
* @apicovered			email_save_message 
* @passcase				If saves the email message successfully
* @failcase				If fails to save the email message
* @precondition			NA
* @postcondition		NA 
*/
int ITc_email_save_message_p(void)
{
	START_TEST;

	//Create an email message with attachment
	bool bRet = CreateEmailMessageWithAttachment(g_hEmail);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] Failed to create email message\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target API
	/**** Save Email Message ****/
	int nRet = email_save_message(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_save_message", EmailGetError(nRet));

	return 0;
}

//& purpose Sends an email message with attachment
//& type: auto
/**
* @testcase   			ITc_email_send_message_with_attachment_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Creates an email message handle for sending an email message
* @scenario				Creates an email message\n
*						Sends the email message\n
*						Destroys the email message
* @apicovered			email_save_message, email_send_message, email_set_message_sent_cb, email_unset_message_sent_cb 
* @passcase				If sends an email message successfully
* @failcase				If fails to send the email message
* @precondition			An email account should be manually added to the device before executing this test
* @postcondition		NA
*/
int ITc_email_send_message_with_attachment_p(void)
{
	START_TEST;

	g_bCallbackOccurred = false;
	g_bEmailSentSuccess = false;

	//Create an email message with attachment
	bool bRet = CreateEmailMessageWithAttachment(g_hEmail);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] failed to create email message\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Save Email Message
	int nRet = email_save_message(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_save_message", EmailGetError(nRet));

	/* Set Email Message Sent Callback Function */
	nRet = email_set_message_sent_cb(g_hEmail, email_message_sent_callback, NULL);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_set_message_sent_cb", EmailGetError(nRet));

	//Target API
	/**** Send Email Message ****/
	nRet = email_send_message(g_hEmail, true);
	if ( !g_bIsEmailSendFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] email_send_message() returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
			email_unset_message_sent_cb(g_hEmail);
			return 0;
		}

		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	PRINT_RESULT_CLEANUP(EMAILS_ERROR_NONE, nRet, "email_set_message_sent_cb", EmailGetError(nRet), email_unset_message_sent_cb(g_hEmail));

	int nEmailTimeoutId = 0;
	RUN_POLLING_LOOP;

	if ( !g_bCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}
	if ( !g_bEmailSentSuccess )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb invoked callback with email_sending_e = false\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	/* Unset Email Message Sent Callback Function */
	nRet = email_unset_message_sent_cb(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_unset_message_sent_cb", EmailGetError(nRet));

	return 0;
}

//& purpose Sends an email message without attachment
//& type: auto
/**
* @testcase   			ITc_email_send_message_without_attachment_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Creates an email message handle for sending an email message
* @scenario				Creates an email message\n
*						Sends the email message\n
*						Destroys the email message
* @apicovered			email_send_message, email_save_message, email_set_message_sent_cb, email_unset_message_sent_cb
* @passcase				If sends an email message successfully
* @failcase				If fails to send the email message
* @precondition			An email account should be manually added to the device before executing this test
* @postcondition		NA 
*/
int ITc_email_send_message_without_attachment_p(void)
{
	START_TEST;

	g_bCallbackOccurred = false;
	g_bEmailSentSuccess = false;

	//Create an email message with attachment
	bool bRet = CreateEmailMessageWithoutAttachment(g_hEmail);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] failed to create email message\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Save Email Message
	int nRet = email_save_message(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_save_message", EmailGetError(nRet));

	/* Set Email Message Sent Callback Function */
	nRet = email_set_message_sent_cb(g_hEmail, email_message_sent_callback, NULL);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_set_message_sent_cb", EmailGetError(nRet));

	//Target API
	/**** Send Email Message ****/
	nRet = email_send_message(g_hEmail, true);
	if ( !g_bIsEmailSendFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] email_send_message() returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
			email_unset_message_sent_cb(g_hEmail);
			return 0;
		}

		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	PRINT_RESULT_CLEANUP(EMAILS_ERROR_NONE, nRet, "email_send_message", EmailGetError(nRet), email_unset_message_sent_cb(g_hEmail));

	int nEmailTimeoutId = 0;	
	RUN_POLLING_LOOP;

	if ( !g_bCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}
	if ( !g_bEmailSentSuccess )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb invoked callback with email_sending_e = false\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	/* Unset Email Message Sent Callback Function */
	nRet = email_unset_message_sent_cb(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_unset_message_sent_cb", EmailGetError(nRet));

	return 0;
}

//& purpose Populates the body of an email message
//& type: auto
/**
* @testcase   			ITc_email_set_body_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Sets the subject of an email message
* @scenario				Creates an Email service\n
*						Populates the body of an email message\n
*						Destroys an Email service
* @apicovered			email_set_body
* @passcase				If populates the body of email message successfully
* @failcase				If fails to populate the body of email message
* @precondition			NA
* @postcondition		NA
*/
int ITc_email_set_body_p(void)
{
	START_TEST;

	//Target API
	/**** Populate the body of Email Message ****/
	int nRet = email_set_body(g_hEmail, EMAILBODY);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_set_body", EmailGetError(nRet));

	return 0;
}

//& purpose Register and unregister email message sent callback function
//& type: auto
/**
* @testcase   			ITc_email_set_unset_message_sent_cb_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Creates an email message handle for sending an email message
* @scenario				Creates an email message\n
*						Registers email message sent callback function\n
*						Sends the email message\n
*						Unregisters email message sent callback function\n
*						Destroys the email message
* @apicovered			email_set_message_sent_cb, email_send_message, email_unset_message_sent_cb
* @passcase				If registers & unregisters the email message sent callback function successfully
* @failcase				If fails to register & unregister the email message sent callback function
* @precondition			An email account should be manually added to the device before executing this test
* @postcondition		NA
*/
int ITc_email_set_unset_message_sent_cb_p(void)
{
	START_TEST;

	bool bRet = CreateEmailMessageWithoutAttachment(g_hEmail);
	if ( bRet == false )
	{
		FPRINTF("[Line : %d][%s] failed to create email message without attachment\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = email_save_message(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_save_message", EmailGetError(nRet));

	g_bCallbackOccurred = false;
	g_bEmailSentSuccess = false;

	//Target API
	/**** Set Email Message Sent Callback Function ****/
	nRet = email_set_message_sent_cb(g_hEmail, email_message_sent_callback, NULL);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_set_message_sent_cb", EmailGetError(nRet));

	//Send an email message
	nRet = email_send_message(g_hEmail, true);
	PRINT_RESULT_CLEANUP(EMAILS_ERROR_NONE, nRet, "email_send_message", EmailGetError(nRet), email_unset_message_sent_cb(g_hEmail));

	if ( !g_bIsEmailSendFeatureSupported )
	{
		if ( nRet == TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] email_send_message() returned %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, EmailGetError(nRet));
			email_unset_message_sent_cb(g_hEmail);
			return 0;
		}

		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	int nEmailTimeoutId = 0;
	RUN_POLLING_LOOP;

	if ( !g_bCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb failed to invoke callback\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}
	if ( !g_bEmailSentSuccess )
	{
		FPRINTF("[Line : %d][%s] email_set_message_sent_cb invoked callback with email_sending_e = false\\n", __LINE__, API_NAMESPACE);
		email_unset_message_sent_cb(g_hEmail);
		return 1;
	}

	//Target API
	/**** Unset Email Message Sent Callback Function ****/
	nRet = email_unset_message_sent_cb(g_hEmail);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_unset_message_sent_cb", EmailGetError(nRet));

	g_bCallbackOccurred = false;
	
	//Send an email message
	nRet = email_send_message(g_hEmail, true);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_send_message", EmailGetError(nRet));
	RUN_POLLING_LOOP;
	if ( g_bCallbackOccurred )
	{
		FPRINTF("[Line : %d][%s] email_unset_message_sent_cb failed to stop callback\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose Sets the subject of an email message
//& type: auto
/**
* @testcase   			ITc_email_set_subject_p
* @since_tizen			2.3
* @author             	SRID(gupta.sanjay)
* @reviewer         	SRID(ravi.kumar2)
* @type 				auto
* @description			Sets the subject of an email message
* @scenario				Creates an Email service\n
*						Sets the subject of an email message\n
*						Destroys an Email service
* @apicovered			email_set_subject
* @passcase				If sets the subject of email message successfully
* @failcase				If fails to set the subject of email message
* @precondition			NA
* @postcondition		NA 
*/
int ITc_email_set_subject_p(void)
{
	START_TEST;

	//Target API
	/**** Set the subject of Email Message ****/
	int nRet = email_set_subject(g_hEmail, EMAILSUBJECT);
	PRINT_RESULT(EMAILS_ERROR_NONE, nRet, "email_set_subject", EmailGetError(nRet));

	return 0;
}
/** @} */
/** @} */
