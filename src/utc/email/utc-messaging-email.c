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
#include "assert.h"
#include <messaging/email.h>
#include <stdlib.h>
#include <string.h>
#include <storage.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>

#define CONFIG_LINE_LEN_MAX		2048	//maximum key-value line length
#define CONFIG_VALUE_LEN_MAX		1024	//maximum length of value
#define DEFAULT_ADDRESS "test-email-account-test@tizen.org"
#define EAMIL_FEATURE "http://tizen.org/feature/email"

static char* file="testemail.txt";
static char* email_path=NULL;
static char g_pstrRecipient[CONFIG_VALUE_LEN_MAX] = {0,};
static bool is_email_supported = false;

static bool storage_device_cb(int storage_id, storage_type_e type, storage_state_e state, const char* path, void* user_data){
        if(type==STORAGE_TYPE_INTERNAL){
          email_path=(char*)malloc(strlen(path)+strlen(file)+5);
          snprintf(email_path, strlen(path)+strlen(file)+5,"%s/%s",path,file);
        return false;
        }
        return true;
}

bool _get_value_from_config(char* key, char* value)
{
        if ( NULL == key )
        {
            return false;
        }
        FILE* pfilePtr = fopen(CONFIGFILE_PATH, "r");
        if ( NULL == pfilePtr )
        {
            return false;
        }

        char* pszKey = NULL;
        char* pszValue = NULL;
        char* pszDelim = "=\n";
        char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};

        while ( !feof(pfilePtr) )
        {
                if ( fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL )
                {
                        pszKey = strtok(szConfigLine, pszDelim);
                        pszValue = strtok(NULL, pszDelim);

                        if ( 0 == strcmp(pszKey, key) )
                        {
                                break;
                        }

                        pszKey = NULL;
                        pszValue = NULL;
                }
        }

        fclose(pfilePtr);
        if ( NULL == pszValue )
        {
                return false;
        }

        if ( strlen(pszValue) >= CONFIG_VALUE_LEN_MAX )
        {
                return false;
        }

        memset(value, 0, CONFIG_VALUE_LEN_MAX);
        g_strlcpy(value, pszValue, CONFIG_VALUE_LEN_MAX);
        return true;
}

/**
 * @function		utc_messaging_email_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_messaging_email_startup(void)
{
	/* start of TC */
	system_info_get_platform_bool(EAMIL_FEATURE, &is_email_supported);

    storage_foreach_device_supported(storage_device_cb,NULL);
    if ( true != _get_value_from_config("EMAIL_RECIPIENT", g_pstrRecipient) )
    {
        g_strlcpy(g_pstrRecipient, DEFAULT_ADDRESS, CONFIG_VALUE_LEN_MAX);
    }
}

/**
 * @function		utc_messaging_email_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_messaging_email_cleanup(void)
{
}

/**
 * @testcase		utc_messaging_email_create_message_p
 * @since_tizen		2.3
 * @description		Test inserting for creating the message of email
 */
int utc_messaging_email_create_message_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_create_message(&msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_destroy_message(msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_create_message_n
 * @since_tizen		2.3
 * @description		Test fail inserting for creating the message of email
 */
int utc_messaging_email_create_message_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_create_message(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_destroy_message_p
 * @since_tizen		2.3
 * @description		Test inserting for free the created message
 */
int utc_messaging_email_destroy_message_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_destroy_message(msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_destroy_message(msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_destroy_message_n
 * @since_tizen		2.3
 * @description		Test fail inserting for free the created message
 */
int utc_messaging_email_destroy_message_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_destroy_message(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_set_subject_p
 * @since_tizen		2.3
 * @description		Test inserting for setting the subject in a message
 */
int utc_messaging_email_set_subject_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_set_subject(msg, "title: First email!!!");
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_set_subject(msg, "title: First email!!!");
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_set_subject_n
 * @since_tizen		2.3
 * @description		Test fail inserting for setting the subject in a message
 */
int utc_messaging_email_set_subject_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_set_subject(NULL, "title: First email!!!");
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_set_body_p
 * @since_tizen		2.3
 * @description		Test inserting for setting the body in a message
 */
int utc_messaging_email_set_body_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_set_body(msg, "First SMS message!!!");
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_set_body(msg, "First SMS message!!!");
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_set_body_n
 * @since_tizen		2.3
 * @description		Test fail inserting for setting the body in a message
 */
int utc_messaging_email_set_body_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_set_body(NULL, "First SMS message!!!");
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}


/**
 * @testcase		utc_messaging_email_add_recipient_p
 * @since_tizen		2.3
 * @description		Test inserting for adding the recipients in a message
 */
int utc_messaging_email_add_recipient_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO,g_pstrRecipient);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO,g_pstrRecipient);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_add_recipient_n
 * @since_tizen		2.3
 * @description		Test fail inserting for adding the recipients in a message
 */
int utc_messaging_email_add_recipient_n(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_add_recipient(msg, 100, g_pstrRecipient);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO, g_pstrRecipient);
    assert_eq (ret, EMAILS_ERROR_INVALID_PARAMETER);

    ret = email_create_message(&msg);

    ret = email_add_recipient(msg, 100, g_pstrRecipient);
    assert_eq (ret, EMAILS_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_messaging_email_remove_all_recipients_p
 * @since_tizen		2.3
 * @description		Test inserting for removing the recipients in a message
 */
int utc_messaging_email_remove_all_recipients_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_remove_all_recipients(msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO, g_pstrRecipient);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_remove_all_recipients(msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_remove_all_recipients_n
 * @since_tizen		2.3
 * @description		Test fail inserting for removing the recipients in a message
 */
int utc_messaging_email_remove_all_recipients_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_remove_all_recipients(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_save_message_p
 * @since_tizen		2.3
 * @description		Test inserting for adding the message in a DB
 */
int utc_messaging_email_save_message_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_save_message(msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_save_message(msg);
    assert_eq(ret, EMAILS_ERROR_NONE);

    ret = email_destroy_message(msg);
    assert_eq(ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_save_message_n
 * @since_tizen		2.3
 * @description		Test fail inserting for adding the message in a DB
 */
int utc_messaging_email_save_message_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_save_message(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_add_attach_p
 * @since_tizen		2.3
 * @description		Test inserting for adding the attachment in a message
 */
int utc_messaging_email_add_attach_p(void)
{

    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;
    FILE* file = NULL;

    if (false == is_email_supported)
    {
        ret = email_add_attach(msg, email_path);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    file = fopen(email_path, "w");
    assert_neq (file, NULL);
    fclose(file);

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_add_attach(msg, email_path);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_add_attach_n
 * @since_tizen		2.3
 * @description		Test fail inserting for adding the attachment in a message
 */
int utc_messaging_email_add_attach_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_add_attach(NULL, NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_remove_all_attachments_p
 * @since_tizen		2.3
 * @description		Test inserting for removing all attachments in a message
 */
int utc_messaging_email_remove_all_attachments_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;
    FILE* file = NULL;

    if (false == is_email_supported)
    {
        ret = email_remove_all_attachments(msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    file = fopen(email_path, "w");
    assert_neq(file, NULL);
    fclose(file);

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_add_attach(msg, email_path);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_remove_all_attachments(msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_remove_all_attachments_n
 * @since_tizen		2.3
 * @description		Test fail inserting for removing all attachments in a message
 */
int utc_messaging_email_remove_all_attachments_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_remove_all_attachments(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_send_message_p
 * @since_tizen		2.3
 * @description		Test inserting for sending the message
 */
int utc_messaging_email_send_message_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_send_message(msg, false);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_add_recipient(msg, EMAIL_RECIPIENT_TYPE_TO, g_pstrRecipient);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_set_body(msg, "First email message!!!");
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_save_message(msg);
    assert_eq(ret, EMAILS_ERROR_NONE);

    ret = email_send_message(msg, false);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_send_message_n
 * @since_tizen		2.3
 * @description		Test fail inserting for sending the message
 */
int utc_messaging_email_send_message_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_send_message(NULL, false);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

static void email_cb(email_h handle, email_sending_e result, void *user_data)
{
    printf("CALLBACK EXECUTED\n");
    printf("transport status  = %d\n", result);
}

/**
 * @testcase		utc_messaging_email_set_message_sent_cb_p
 * @since_tizen		2.3
 * @description		Test inserting for setting callback function of sending status
 */
int utc_messaging_email_set_message_sent_cb_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_set_message_sent_cb(msg, email_cb, NULL);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_set_message_sent_cb(msg, email_cb, NULL);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_set_message_sent_cb_n
 * @since_tizen		2.3
 * @description		Test fail inserting for setting callback function of sending status
 */
int utc_messaging_email_set_message_sent_cb_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_set_message_sent_cb(NULL, NULL, NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

/**
 * @testcase		utc_messaging_email_unset_message_sent_cb_p
 * @since_tizen		2.3
 * @description		Test inserting for removing the callback function
 */
int utc_messaging_email_unset_message_sent_cb_p(void)
{
    int ret = EMAILS_ERROR_NONE;
    email_h msg = NULL;

    if (false == is_email_supported)
    {
        ret = email_unset_message_sent_cb(msg);
        assert_eq(ret, EMAILS_ERROR_NOT_SUPPORTED);
        return 0;
    }

    ret = email_create_message(&msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_set_message_sent_cb(msg, email_cb, NULL);
    assert_eq (ret, EMAILS_ERROR_NONE);

    ret = email_unset_message_sent_cb(msg);
    assert_eq (ret, EMAILS_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_messaging_email_unset_message_sent_cb_n
 * @since_tizen		2.3
 * @description		Test fail inserting for removing the callback function
 */
int utc_messaging_email_unset_message_sent_cb_n(void)
{
    int ret = EMAILS_ERROR_NONE;

    ret = email_unset_message_sent_cb(NULL);
    assert_eq (ret, (false == is_email_supported ? EMAILS_ERROR_NOT_SUPPORTED : EMAILS_ERROR_INVALID_PARAMETER));

    return 0;
}

