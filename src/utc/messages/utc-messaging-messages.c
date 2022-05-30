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
#include <glib.h>
#include <messages.h>
#include <stdlib.h>
#include <string.h>
#include <storage.h>
#include <system_info.h>
#include "tct_common.h"

//& set: Messages
//#define CONFIG_LINE_LEN_MAX		2048	//maximum key-value line length
//#define CONFIG_VALUE_LEN_MAX		1024	//maximum length of value

#define TEST_ADDRESS_COUNT 3
#define TEST_ADDRESS "+8230014180"

#define API_NAMESPACE	"MESSAGES"

static char g_pstrRecipient[CONFIG_VALUE_LEN_MAX] = {0,};

static char *test_addresses[TEST_ADDRESS_COUNT] = {
    "+471234567128",
    "+472222222332",
    TEST_ADDRESS,
};

#define TEST_SIM_ID 1
#define TEST_TEXT "This is test message body. Hello TIZEN Native API!!"
#define TEST_SUBJECT "Test MMS Message!"

#define TEST_ATTACH_COUNT 3

static char* image_path=NULL;
static char* audio_path=NULL;
static char* video_path=NULL;

static char* image="Default.jpg";
static char* audio="audio.amr";
static char* video="V091120_104905.3gp";

static messages_service_h _svc = NULL;
static messages_message_h _msg_sms = NULL;
static messages_message_h _msg_mms = NULL;

static messages_message_h* searched_message_array = NULL;
static int searched_message_length;

static bool is_sms_supported;
static bool is_mms_supported;

typedef struct
{
	bool add_address;
	bool add_text;
	bool add_subject;     //Should be false for SMS
	bool add_attachment;  //Should be false for SMS
	bool search;
} message_prepare;

typedef struct
{
	bool channel;
	bool channel_set_activated;
	bool channel_set_id;
	bool channel_set_name;

	bool settings;
	bool settings_set_enabled;


} cb_prepare;


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
	char *temp = NULL;
	char szConfigLine[CONFIG_LINE_LEN_MAX] = {0,};

	while ( !feof(pfilePtr) )
	{
		if ( fgets(szConfigLine, CONFIG_LINE_LEN_MAX, pfilePtr) != NULL )
		{
			pszKey = strtok_r(szConfigLine, pszDelim, &temp);
			pszValue = strtok_r(NULL, pszDelim, &temp);

			if ( 0 == g_strcmp0(pszKey, key) )
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
	strncpy(value, pszValue, CONFIG_VALUE_LEN_MAX);

	return true;
}
/**
 * @function		utc_messaging_messages_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_messaging_messages_startup(void)
{
	/* start of TC */
	system_info_get_platform_bool("http://tizen.org/feature/network.telephony.sms",&is_sms_supported);
	system_info_get_platform_bool("http://tizen.org/feature/network.telephony.mms",&is_mms_supported);
	//storage_foreach_device_supported(storage_device_cb,NULL);
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
		PRINT_UTC_LOG("[Line : %d][%s] Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
		int image_path_size = strlen(pszValue)+strlen(image)+sizeof(char)*6;
		image_path=(char*)calloc(image_path_size, sizeof(char));
		snprintf(image_path, image_path_size, "%s/res/%s", pszValue, image);

		int audio_path_size = strlen(pszValue)+strlen(audio)+sizeof(char)*6;
		audio_path=(char*)calloc(audio_path_size, sizeof(char));
		snprintf(audio_path, audio_path_size, "%s/res/%s", pszValue, audio);

		int video_path_size = strlen(pszValue)+strlen(video)+sizeof(char)*6;
		video_path=(char*)calloc(video_path_size, sizeof(char));
		snprintf(video_path, video_path_size, "%s/res/%s", pszValue, video);
	}
	else
	{
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error\\n", __LINE__, API_NAMESPACE);
	}
	
	messages_open_service(&_svc);

	if ( true != _get_value_from_config("MESSAGES_MOBILE_NUMBER", g_pstrRecipient) )
	{
		strncpy(g_pstrRecipient, TEST_ADDRESS, CONFIG_VALUE_LEN_MAX);
	}

	searched_message_length = 0;
}


/**
 * @function		utc_messaging_messages_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_messaging_messages_cleanup(void)
{
	/* end of TC */
	if (_msg_mms) {
		messages_destroy_message(_msg_mms);
		_msg_mms = NULL;
	}

	if (_msg_sms) {
		messages_destroy_message(_msg_sms);
		_msg_sms = NULL;
	}

	if (searched_message_length > 0) {
		messages_free_message_array(searched_message_array);
		searched_message_length = 0;
	}

	if (_svc) {
		messages_close_service(_svc);
		_svc = NULL;
	}

	if (audio_path) {
		free(audio_path);
		audio_path = NULL;
	}

	if (video_path) {
		free(video_path);
		video_path = NULL;
	}

	if (image_path) {
		free(image_path);
		image_path = NULL;
	}
}


static int msg_mms_prepare(message_prepare msg_p)
{
	int ret = MESSAGES_ERROR_NONE;
	ret = messages_create_message(MESSAGES_TYPE_MMS, &_msg_mms);
	if (ret != MESSAGES_ERROR_NONE) return ret;

	if(msg_p.add_address) {
		ret = messages_add_address(_msg_mms, test_addresses[0], MESSAGES_RECIPIENT_CC);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_add_address(_msg_mms, test_addresses[1], MESSAGES_RECIPIENT_BCC);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_add_address(_msg_mms, test_addresses[2], MESSAGES_RECIPIENT_TO);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	if(msg_p.add_text) {
		ret = messages_set_text(_msg_mms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	if(msg_p.add_subject) {
		ret = messages_mms_set_subject(_msg_mms, TEST_SUBJECT);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	if(msg_p.add_attachment) {
		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_IMAGE, image_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_AUDIO, audio_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_VIDEO, video_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	return 0;
}

static int msg_sms_prepare(message_prepare msg_p)
{
	int ret = MESSAGES_ERROR_NONE;
	ret = messages_create_message(MESSAGES_TYPE_SMS, &_msg_sms);
	if (ret != MESSAGES_ERROR_NONE) return ret;

	if(msg_p.add_address){
		int i;
		for (i = 0; i < TEST_ADDRESS_COUNT; i++)
		{
			ret = messages_add_address(_msg_sms, test_addresses[i], MESSAGES_RECIPIENT_TO);
			assert_eq(ret, MESSAGES_ERROR_NONE);
		}
	}

	if(msg_p.add_text){
		ret = messages_set_text(_msg_sms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	if(msg_p.search){
		ret = messages_search_message(
		_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
		NULL, NULL, 0, 0,
		&searched_message_array, &searched_message_length, NULL);

		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_neq(searched_message_length, 0);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_open_service_p
 * @since_tizen		2.3
 * @description		Opens a messages service handle
 * @scenario		Open a messages service handle
 */
int utc_messaging_messages_open_service_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	if(is_sms_supported)
	{
		// startup function is opening service for all tests but this
		// one needs service to be closed
		if(_svc){
			messages_close_service(_svc);
			_svc = NULL;
		}

		ret = messages_open_service(&_svc);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_neq(_svc, NULL);
	}
	else
	{
		ret = messages_open_service(&_svc);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_messaging_messages_open_service_n
 * @since_tizen		2.3
 * @description		Opens a messages service handle
 * @scenario		Try to open service handle for NULL pointer
 */
int utc_messaging_messages_open_service_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_open_service(NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_create_message_p01
 * @since_tizen		2.3
 * @description		Creates a message
 * @scenario		Create a SMS
 */
int utc_messaging_messages_create_message_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_create_message(MESSAGES_TYPE_SMS, &_msg_sms);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_create_message_p02
 * @since_tizen		2.3
 * @description		Creates a message
 * @scenario		Create a MMS
 */
int utc_messaging_messages_create_message_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_create_message(MESSAGES_TYPE_MMS, &_msg_mms);

	if(is_sms_supported)
	{
		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);
		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_create_message_n
 * @since_tizen		2.3
 * @description		Creates a message
 * @scenario		Try to create a SMS for NULL pointer to get negative result
 */
int utc_messaging_messages_create_message_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_create_message(MESSAGES_TYPE_SMS, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_add_address_p
 * @since_tizen		2.3
 * @description		Adds address to a message
 * @scenario		Add a PLMN address to a SMS
 * 					Add PLMN addresses to a MMS for to, cc, bcc and an e-mail address
 */
int utc_messaging_messages_add_address_p(void)
{
	int i;
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,0,0,0,0};
	if (is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		for (i=0; i < TEST_ADDRESS_COUNT; i++)
		{
			ret = messages_add_address(_msg_sms, test_addresses[i], MESSAGES_RECIPIENT_TO);
			assert_eq(ret, MESSAGES_ERROR_NONE);
		}

		if (is_mms_supported) {
			memset(&msg, 0x00, sizeof(message_prepare));
			ret = msg_mms_prepare(msg);
			assert(!ret);

			for (i=0; i < TEST_ADDRESS_COUNT; i++)
			{
				ret = messages_add_address(_msg_mms, test_addresses[i], MESSAGES_RECIPIENT_TO);
				assert_eq(ret, MESSAGES_ERROR_NONE);

				ret = messages_add_address(_msg_mms, test_addresses[i], MESSAGES_RECIPIENT_CC);
				assert_eq(ret, MESSAGES_ERROR_NONE);

				ret = messages_add_address(_msg_mms, test_addresses[i], MESSAGES_RECIPIENT_BCC);
				assert_eq(ret, MESSAGES_ERROR_NONE);

			}

			ret = messages_add_address(_msg_mms, "test@samsung.net", MESSAGES_RECIPIENT_TO);
			assert_eq(ret, MESSAGES_ERROR_NONE);
		}
	}
	else
	{
		for (i=0; i < TEST_ADDRESS_COUNT; i++)
		{
			ret = messages_add_address(_msg_sms, test_addresses[i], MESSAGES_RECIPIENT_TO);
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_add_address_n
 * @since_tizen		2.3
 * @description		Adds address to a message
 * @scenario		Add NULL pointer as a address to a SMS to get negative result
 */
int utc_messaging_messages_add_address_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		ret = messages_add_address(_msg_sms, NULL, MESSAGES_RECIPIENT_TO);

		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_add_address(_msg_sms, NULL, MESSAGES_RECIPIENT_TO);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_address_count_p
 * @since_tizen		2.3
 * @description		Gets a number of address in a message
 * @scenario		Prepare a SMS
 * 					Get count of address in prepared message
 */
int utc_messaging_messages_get_address_count_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int count = 0;
	message_prepare msg = {1,0,0,0,0};

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		ret = messages_get_address_count(_msg_sms, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(count, TEST_ADDRESS_COUNT);
	}
	else
	{
		ret = messages_get_address_count(_msg_sms, &count);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_address_count_n
 * @since_tizen		2.3
 * @description		Gets a number of address in a message
 * @scenario		Prepare a SMS
 * 					Get count of address in prepared message - pass NULL pointer for count to get negative result
 */
int utc_messaging_messages_get_address_count_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {1,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);
		ret = messages_get_address_count(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_get_address_count(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_address_p
 * @since_tizen		2.3
 * @description		Gets address from a message
 * @scenario		Prepare a SMS
 * 					Get address from prepared message
 */
int utc_messaging_messages_get_address_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int i;

	char *address = NULL;
	message_prepare msg = {1,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		for (i=0; i < TEST_ADDRESS_COUNT; i++)
		{
			messages_recipient_type_e type = {0};
			ret = messages_get_address(_msg_sms, i, &address, &type);
			assert_eq(ret, MESSAGES_ERROR_NONE);
			assert_neq(address, NULL);
			ret = strcmp(address, test_addresses[i]);

			free(address);
			address = NULL;

			assert_eq(ret, 0);
			assert_geq(type, MESSAGES_RECIPIENT_TO);
			assert_leq(type, MESSAGES_RECIPIENT_BCC);
		}
	}
	else
	{
		for (i=0; i < TEST_ADDRESS_COUNT; i++)
		{
			ret = messages_get_address(_msg_sms, i, &address, NULL);
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_address_n
 * @since_tizen		2.3
 * @scenario		Prepares a SMS
 * 					Get address from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_get_address_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {1,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		ret = messages_get_address(_msg_sms, 0, NULL, NULL);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_get_address(_msg_sms, 0, NULL, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_remove_all_addresses_p
 * @since_tizen		2.3
 * @description		Removes all addresses from a message
 * @scenario		Prepare a SMS
 * 					Remove all addresses from prepared message
 */
int utc_messaging_messages_remove_all_addresses_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int count = -1;
	message_prepare msg = {1,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		ret = messages_remove_all_addresses(_msg_sms);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_get_address_count(_msg_sms, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(count, 0);
	}
	else
	{
		ret = messages_remove_all_addresses(_msg_sms);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_remove_all_addresses_n
 * @since_tizen		2.3
 * @description		Removes all addresses from a message
 * @scenario		Prepare a SMS
 * 					Remove all addresses from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_remove_all_addresses_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_remove_all_addresses(NULL);

	if(is_sms_supported) {
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	} else {
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_set_text_p01
 * @since_tizen		2.3
 * @description		Sets message text to a message
 * @scenario		Prepare a SMS
 * 					Set message text to prepared message
 */
int utc_messaging_messages_set_text_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_text(_msg_sms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_set_text(_msg_sms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_set_text_p02
 * @since_tizen		2.3
 * @description		Sets message text to a message
 * @scenario		Prepare a MMS
 * 					Set message text to prepared message
 */
int utc_messaging_messages_set_text_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_mms_prepare(msg);

		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_set_text(_msg_mms, TEST_TEXT);
			assert_eq(ret, MESSAGES_ERROR_NONE);

		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		ret = messages_set_text(_msg_mms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_messaging_messages_set_text_n
 * @since_tizen		2.3
 * @description		Sets message text to a message
 * @scenario		Prepare a SMS
 * 					Set message text to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_set_text_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_text(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_set_text(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_text_p01
 * @since_tizen		2.3
 * @description		Gets message text from a message
 * @scenario		Prepare a SMS
 * 					Get message text to prepared message
 */
int utc_messaging_messages_get_text_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	char *text = NULL;
	message_prepare msg_p = {0,1,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_text(_msg_sms, &text);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_neq(text, NULL);

		ret = strcmp(text, TEST_TEXT);
		free(text);
		text = NULL;
		assert_eq(ret, 0);
	}
	else
	{
		ret = messages_get_text(_msg_sms, &text);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_text_p02
 * @since_tizen		2.3
 * @description		Gets message text from a message
 * @scenario		Prepare a MMS
 * 					Get message text to prepared message
 */
int utc_messaging_messages_get_text_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	char *text = NULL;
	message_prepare msg = {0,1,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_mms_prepare(msg);
		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_get_text(_msg_mms, &text);
			assert_eq(ret, MESSAGES_ERROR_NONE);
			assert_neq(text, NULL);

			ret = strcmp(text, TEST_TEXT);
			free(text);
			text = NULL;
			assert_eq(ret, 0);

		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		ret = messages_get_text(_msg_mms, &text);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_text_n
 * @since_tizen		2.3
 * @description		Gets message text from a message
 * @scenario		Prepare a SMS
 * 					Get message text to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_get_text_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_get_text(_msg_sms, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_messaging_messages_set_time_p
 * @since_tizen         3.0
 * @description         Sets display time from a message
 * @scenario            Prepare a SMS
 *                                      Set display time to prepared message
 */
int utc_messaging_messages_set_time_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	time_t t = time(NULL);
	message_prepare msg_p = {0,0,0,0,0};

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_time(_msg_sms, t);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_set_time(_msg_sms, t);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_messaging_messages_set_time_n
 * @since_tizen         3.0
 * @description         Sets display time from a message
 * @scenario            Prepare a SMS
 *                                      Set display time to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_set_time_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_set_time(NULL, 0);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_messaging_messages_get_time_p
 * @since_tizen		2.3
 * @description		Gets display time from a message
 * @scenario		Prepare a SMS
 * 					Get display time to prepared message
 */
int utc_messaging_messages_get_time_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	time_t t;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);
		ret = messages_get_time(_msg_sms, &t);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_get_time(_msg_sms, &t);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_time_n
 * @since_tizen		2.3
 * @description		Gets display time from a message
 * @scenario		Prepare a SMS
 * 					Get display time to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_get_time_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_get_time(NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_type_p01
 * @since_tizen		2.3
 * @description		Gets message type from a message
 * @scenario		Prepare a SMS
 * 					Get message type to prepared message
 * 					Check whether returned type is SMS or not
 */
int utc_messaging_messages_get_message_type_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	messages_message_type_e type;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_message_type(_msg_sms, &type);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(type, MESSAGES_TYPE_SMS);
	}
	else
	{
		ret = messages_get_message_type(_msg_sms, &type);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_type_p02
 * @since_tizen		2.3
 * @description		Gets message type from a message
 * @scenario		Prepare a MMS
 * 					Get message type to prepared message
 * 					Check whether returned type is MMS or not
 */
int utc_messaging_messages_get_message_type_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	messages_message_type_e type;
	message_prepare msg = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_mms_prepare(msg);
		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_get_message_type(_msg_mms, &type);
			assert_eq(ret, MESSAGES_ERROR_NONE);
			assert_eq(type, MESSAGES_TYPE_MMS);
		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		ret = messages_get_message_type(_msg_mms, &type);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_type_n
 * @since_tizen		2.3
 * @description		Gets message type from a message
 * @scenario		Prepare a SMS
 * 					Get message type to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_get_message_type_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_message_type(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_get_message_type(_msg_sms, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_messaging_messages_add_message_p
 * @since_tizen         3.0
 * @description         Adds message to message database
 * @scenario            Create a SMS
 *                                      Adds message to message database
 *                                      Check returned message id is available
 */
int utc_messaging_messages_add_message_p(void)
{
	int ret;
	message_prepare msg = {0,0,0,0,0};
	int msg_id;

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg);
		assert(!ret);

		ret = messages_add_address(_msg_sms, g_pstrRecipient, MESSAGES_RECIPIENT_TO);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_set_text(_msg_sms, TEST_TEXT);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		/* return value is message id! */
		ret = messages_add_message(_svc, _msg_sms, &msg_id);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert(msg_id > 0);
	}
	else
	{
		ret = messages_add_message(_svc, _msg_sms, &msg_id);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_messaging_messages_add_message_n
 * @since_tizen         3.0
 * @description         Adds message to message database
 * @scenario            Adds message to message database - pass NULL pointer to get negative result
 *
 */
int utc_messaging_messages_add_message_n(void)
{
	int ret;
	int msg_id;

	if(is_sms_supported)
	{
		ret = messages_add_message(_svc, NULL, &msg_id);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_add_message(_svc, NULL, &msg_id);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_set_subject_p
 * @since_tizen		2.3
 * @description		Sets subject to a MMS
 * @scenario		Prepare a MMS
 * 					Set subject to prepared message
 */
int utc_messaging_messages_mms_set_subject_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,0,0,0,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_set_subject(_msg_mms, TEST_SUBJECT);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_mms_set_subject(_msg_mms, TEST_SUBJECT);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_set_subject_n01
 * @since_tizen		2.3
 * @description		Sets subject to a MMS
 * @scenario		Prepare a MMS
 * 					Set subject to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_set_subject_n01(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_mms_set_subject(_msg_mms, NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_set_subject_n02
 * @since_tizen		2.3
 * @description		Sets subject to a MMS
 * @scenario		Prepare a SMS
 * 					Set subject to prepared message, but it return negative result. Because prepared message is SMS
 */
int utc_messaging_messages_mms_set_subject_n02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_mms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_mms_set_subject(_msg_sms, TEST_SUBJECT);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_mms_set_subject(_msg_sms, TEST_SUBJECT);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_subject_p
 * @since_tizen		2.3
 * @description		Gets subject from a MMS
 * @scenario		Prepare a MMS
 * 					Get subject from prepared message
 */
int utc_messaging_messages_mms_get_subject_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	char *subject = NULL;
	message_prepare msg = {0,0,1,0,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_get_subject(_msg_mms, &subject);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_neq(subject, NULL);

		ret = strcmp(TEST_SUBJECT, subject);
		free(subject);
		subject = NULL;
		assert_eq(ret, 0);
	}
	else
	{
		ret = messages_mms_get_subject(_msg_mms, &subject);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_subject_n01
 * @since_tizen		2.3
 * @description		Gets subject from a MMS
 * @scenario		Prepare a MMS
 * 					Get subject from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_get_subject_n01(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_mms_get_subject(_msg_mms, NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_subject_n02
 * @since_tizen		2.3
 * @description		Gets subject from a MMS
 * @scenario		Prepare a SMS
 * 					Get subject from prepared message, but it return negative result. Because prepared message is SMS
 */
int utc_messaging_messages_mms_get_subject_n02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	char *subject = NULL;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_mms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_mms_get_subject(_msg_sms, &subject);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_mms_get_subject(_msg_sms, &subject);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_add_attachment_p
 * @since_tizen		2.3
 * @description		Adds attachment files to a MMS
 * @scenario		Prepare a MMS
 * 					Add attachment files to prepared message
 */
int utc_messaging_messages_mms_add_attachment_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,0,0,0,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_IMAGE, image_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_AUDIO, audio_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_VIDEO, video_path);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_IMAGE, image_path);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_add_attachment_n01
 * @since_tizen		2.3
 * @description		Adds attachment files to a MMS
 * @scenario		Prepare a MMS
 * 					Add attachment files to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_add_attachment_n01(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_IMAGE, NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_add_attachment_n02
 * @since_tizen		2.3
 * @description		Adds attachment files to a MMS
 * @scenario		Prepare a SMS
 * 					Add attachment files to prepared message, but it return negative result. Because prepared message is SMS
 */
int utc_messaging_messages_mms_add_attachment_n02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};

	if(is_mms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_add_attachment(_msg_sms, MESSAGES_MEDIA_IMAGE, image_path);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_mms_add_attachment(_msg_sms, MESSAGES_MEDIA_IMAGE, image_path);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_count_p
 * @since_tizen		2.3
 * @description		Gets a number of attachment files from a MMS
 * @scenario		Prepare a MMS
 * 					Get a number of attachment files from prepared message
 */
int utc_messaging_messages_mms_get_attachment_count_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int count = 0;
	message_prepare msg = {0,0,0,1,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_get_attachment_count(_msg_mms, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(count, TEST_ATTACH_COUNT);
	}
	else
	{
		ret = messages_mms_get_attachment_count(_msg_mms, &count);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_count_n01
 * @since_tizen		2.3
 * @description		Gets a number of attachment files from a MMS
 * @scenario		Prepare a MMS
 * 					Get a number of attachment files from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_get_attachment_count_n01(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_mms_get_attachment_count(_msg_mms, NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_count_n02
 * @since_tizen		2.3
 * @description		Gets a number of attachment files from a MMS
 * @scenario		Prepare a SMS
 * 					Get a number of attachment files from prepared message, but it return negative result. Because prepared message is SMS
 */
int utc_messaging_messages_mms_get_attachment_count_n02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int count = 0;
	message_prepare msg_p = {0,0,0,0,0};

	if(is_mms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_get_attachment_count(_msg_sms, &count);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);

	}
	else
	{
		ret = messages_mms_get_attachment_count(_msg_sms, &count);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_p
 * @since_tizen		2.3
 * @description		Gets attachment files from a MMS
 * @scenario		Prepare a MMS
 * 					Get attachment files from prepared message
 * 					Check the returned files are correct
 */
int utc_messaging_messages_mms_get_attachment_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int i;
	messages_media_type_e type;
	char *path = NULL;

	message_prepare msg = {0,0,0,1,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		for (i=0; i < TEST_ATTACH_COUNT; i++)
		{
		ret = messages_mms_get_attachment(_msg_mms, i, &type, &path);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_neq(path, NULL);

		switch(type)
		{
			case MESSAGES_MEDIA_IMAGE:
				ret = strcmp(image_path, path);
				free(path);
				path = NULL;
				assert_eq(ret, 0);
				break;
			case MESSAGES_MEDIA_AUDIO:
				ret = strcmp(audio_path, path);
				free(path);
				path = NULL;
				assert_eq(ret, 0);
				break;
			case MESSAGES_MEDIA_VIDEO:
				ret = strcmp(video_path, path);
				free(path);
				path = NULL;
				assert_eq(ret, 0);
				break;
			default:
				free(path);
				path = NULL;
				return 1;
				break;
			}
		}

	}
	else
	{
		for (i=0; i < TEST_ATTACH_COUNT; i++)
		{
			ret = messages_mms_get_attachment(_msg_mms, i, &type, &path);
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_n01
 * @since_tizen		2.3
 * @description		Gets attachment files from a MMS
 * @scenario		Prepare a MMS
 * 					Get attachment files from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_get_attachment_n01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	messages_media_type_e type;

	ret = messages_mms_get_attachment(_msg_mms, 0, &type, NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_get_attachment_n02
 * @since_tizen		2.3
 * @description		Gets attachment files from a MMS
 * @scenario		Prepare a SMS
 * 					Get attachment files from prepared message, but it return negative result. Because prepared message is SMS
 */
int utc_messaging_messages_mms_get_attachment_n02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	messages_media_type_e type;
	char *path = NULL;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_mms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_mms_get_attachment(_msg_sms, 0, &type, &path);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
		assert_eq(path, NULL);
	}
	else
	{
		ret = messages_mms_get_attachment(_msg_sms, 0, &type, &path);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

void _sent_cb(messages_sending_result_e result, void *user_data)
{
}

/**
 * @testcase		utc_messaging_messages_send_message_p01
 * @since_tizen		2.3
 * @description		Sends a message
 * @scenario		Prepare a SMS
 * 					Add address to prepared message
 * 					Send the message
 */
int utc_messaging_messages_send_message_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,1,0,0,0};

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_add_address(_msg_sms, g_pstrRecipient, MESSAGES_RECIPIENT_TO);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_send_message(_svc, _msg_sms, false, _sent_cb, NULL);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_send_message(_svc, _msg_sms, false, _sent_cb, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/* Sending MMS is not supported in SDK */
/**
 * @testcase		utc_messaging_messages_send_message_p02
 * @since_tizen		2.3
 * @description		Sends a message
 * @scenario		Prepare a MMS
 * 					Add address and attachment files to prepared message
 * 					Send the message
 */
int utc_messaging_messages_send_message_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {0,1,1,0,0};
	if(is_sms_supported)
	{
		ret = msg_mms_prepare(msg);

		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_add_address(_msg_mms, g_pstrRecipient, MESSAGES_RECIPIENT_TO);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_IMAGE, image_path);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_send_message(_svc, _msg_mms, true, _sent_cb, NULL);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_AUDIO, audio_path);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_send_message(_svc, _msg_mms, true, _sent_cb, NULL);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_mms_add_attachment(_msg_mms, MESSAGES_MEDIA_VIDEO, video_path);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_send_message(_svc, _msg_mms, true, _sent_cb, NULL);
			assert_eq(ret, MESSAGES_ERROR_NONE);
		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		ret = messages_send_message(_svc, _msg_mms, false, _sent_cb, NULL);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_send_message_n
 * @since_tizen		2.3
 * @description		Sends a message
 * @scenario		Send the message as NULL pointer to get negative result
 */
int utc_messaging_messages_send_message_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_send_message(_svc, NULL, false, _sent_cb, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static void _incoming_cb(messages_message_h incoming_msg, void *user_data)
{
}

/**
 * @testcase		utc_messaging_messages_set_message_incoming_cb_p
 * @since_tizen		2.3
 * @description		Sets a message incoming callback function
 * @scenario		Set a message incoming callback function
 */
int utc_messaging_messages_set_message_incoming_cb_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_set_message_incoming_cb(_svc, _incoming_cb, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_set_message_incoming_cb_n
 * @since_tizen		2.3
 * @description		Sets a message incoming callback function
 * @scenario		Set a message incoming callback function as NULL pointer to get negative result
 */
int utc_messaging_messages_set_message_incoming_cb_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_set_message_incoming_cb(_svc, NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_unset_message_incoming_cb_p
 * @since_tizen		2.3
 * @description		Unsets a message incoming callback function
 * @scenario		Unset a message incoming callback function
 */
int utc_messaging_messages_unset_message_incoming_cb_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_unset_message_incoming_cb(_svc);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_unset_message_incoming_cb_n
 * @since_tizen		2.3
 * @description		Unsets a message incoming callback function
 * @scenario		Unset a message incoming callback function - pass NULL pointer to get negative result
 */
int utc_messaging_messages_unset_message_incoming_cb_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_unset_message_incoming_cb(NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_remove_all_attachments_p
 * @since_tizen		2.3
 * @description		Removes all attachment files from a MMS
 * @scenario		Prepare a MMS
 * 					Remove all attachment files from prepared message
 * 					Get count of attachment files from the message and check the value is 0
 */
int utc_messaging_messages_mms_remove_all_attachments_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int count = -1;
	message_prepare msg = {0,0,0,1,0};
	if(is_mms_supported)
	{
		ret = msg_mms_prepare(msg);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_remove_all_attachments(_msg_mms);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_mms_get_attachment_count(_msg_mms, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(count, 0);
	}
	else
	{
		ret = messages_mms_remove_all_attachments(_msg_mms);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_mms_remove_all_attachments_n
 * @since_tizen		2.3
 * @description		Removes all attachment files from a MMS
 * @scenario		Remove all attachment files from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_mms_remove_all_attachments_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_mms_remove_all_attachments(NULL);

	if(is_mms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_destroy_message_p01
 * @since_tizen		2.3
 * @description		Destroys a message
 * @scenario		Prepare a SMS
 * 					Destroy prepared message
 */
int utc_messaging_messages_destroy_message_p01(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_destroy_message(_msg_sms);
		_msg_sms = NULL;
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_destroy_message(_msg_sms);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_destroy_message_p02
 * @since_tizen		2.3
 * @description		Destroys a message
 * @scenario		Prepare a MMS
 * 					Destroy prepared message
 */
int utc_messaging_messages_destroy_message_p02(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg = {1,1,1,1,0};
	if(is_sms_supported)
	{
		ret = msg_mms_prepare(msg);

		if (is_mms_supported) {
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_destroy_message(_msg_mms);
			_msg_mms = NULL;
			assert_eq(ret, MESSAGES_ERROR_NONE);
		} else {
			assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
		}
	}
	else
	{
		ret = messages_destroy_message(_msg_mms);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_destroy_message_n
 * @since_tizen		2.3
 * @description		Destroys a message
 * @scenario		Try to destroy a message as NULL pointer to get negative result
 */
int utc_messaging_messages_destroy_message_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_destroy_message(NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

static bool _search_cb(messages_message_h msg, int index, int result_count, int total_count, void *user_data)
{
	return true;
}

/**
 * @testcase		utc_messaging_messages_foreach_message_p
 * @since_tizen		2.3
 * @description		Searches messages by given conditions and invoke callback function with each searched message
 * @scenario		Call messages API with some conditions and callback function
 */
int utc_messaging_messages_foreach_message_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_foreach_message(
				_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_MMS,
				"test", NULL, 0, 0, _search_cb, NULL);


	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_foreach_message_n
 * @since_tizen		2.3
 * @description		Searches messages by given conditions and invoke callback function with each searched message
 * @scenario		Call messages API with NULL pointer as message service handle to get negative result
 */
int utc_messaging_messages_foreach_message_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_foreach_message(
				NULL, MESSAGES_MBOX_ALL, MESSAGES_TYPE_MMS,
				NULL, NULL, 0, 0, _search_cb, NULL);


	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_search_message_p
 * @since_tizen		2.3
 * @description		Searches messages by given conditions
 * @scenario		Call messages API with conditions
 */
int utc_messaging_messages_search_message_p(void)
{
	int ret;

	ret = messages_search_message(
				_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
				NULL, NULL, 0, 0,
				&searched_message_array, &searched_message_length, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_search_message_n
 * @since_tizen		2.3
 * @description		Searches messages by given conditions
 * @scenario		Call messages API with NULL pointer as message service handle to get negative result
 */
int utc_messaging_messages_search_message_n(void)
{
	int ret;

	ret = messages_search_message(
				NULL, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
				NULL, NULL, 0, 0,
				NULL, NULL, NULL);


	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_messaging_messages_get_message_id_p
 * @since_tizen		2.3
 * @description		Gets message id from a message
 * @scenario		Search messages by some conditions
 * 					Get message id from the first message of searched ones
 */
int utc_messaging_messages_get_message_id_p(void)
{
	int ret;
	int msgid;
	messages_message_h p_msg = NULL;

	/* Assumption: you should have at least one message */
	ret = messages_search_message(
				_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
				NULL, NULL, 0, 0,
				&searched_message_array, &searched_message_length, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
		if( searched_message_length > 0 )
		{
			p_msg = searched_message_array[0];
			ret = messages_get_message_id(p_msg, &msgid);
			assert_eq(ret, MESSAGES_ERROR_NONE);
		}
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_id_n
 * @since_tizen		2.3
 * @description		Gets message id from a message
 * @scenario		Get message id from NULL pointer to get negative result
 */
int utc_messaging_messages_get_message_id_n(void)
{
	int ret;

	ret = messages_get_message_id(NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_set_sim_id_p
 * @since_tizen		2.3
 * @description		Sets SIM id to a message
 * @scenario		Prepare a SMS
 * 					Set SIM id to prepared message
 * 					Get SIM id from above message and check the value
 */
int utc_messaging_messages_set_sim_id_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	int simid;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_sim_id(_msg_sms, TEST_SIM_ID);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_get_sim_id(_msg_sms, &simid);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert_eq(simid, TEST_SIM_ID);
	}
	else
	{
		ret = messages_set_sim_id(_msg_sms, TEST_SIM_ID);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase		utc_messaging_messages_set_sim_id_n
 * @since_tizen		2.3
 * @description		Sets SIM id to a message
 * @scenario		Prepare a SMS
 * 					Set SIM id to prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_set_sim_id_n(void)
{
	int ret = MESSAGES_ERROR_NONE;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_sim_id(NULL, TEST_SIM_ID);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);

	}
	else
	{
		ret = messages_set_sim_id(NULL, TEST_SIM_ID);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_sim_id_p
 * @since_tizen		2.3
 * @description		Gets SIM id from a message
 * @scenario		Create a dummy SMS
 * 					Get SIM id from created message
 */
int utc_messaging_messages_get_sim_id_p(void)
{
	int ret;
	int simid;
	message_prepare msg_p = {0,0,0,0,0};
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_sim_id(_msg_sms, &simid);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_get_sim_id(_msg_sms, &simid);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_sim_id_n
 * @since_tizen		2.3
 * @description		Gets SIM id from a message
 * @scenario		Get SIM id from prepared message - pass NULL pointer to get negative result
 */
int utc_messaging_messages_get_sim_id_n(void)
{
	int ret;

	ret = messages_get_sim_id(NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_messaging_messages_set_mbox_type_p
 * @since_tizen         3.0
 * @description         Sets message box type of a message
 * @scenario            Create a SMS
 *                                      Set message box type to created message
 */
int utc_messaging_messages_set_mbox_type_p(void)
{
	int ret;
	message_prepare msg_p = {0,0,0,0,0};
	messages_message_box_e mbox = MESSAGES_MBOX_INBOX;

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_mbox_type(_msg_sms, mbox);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_set_mbox_type(_msg_sms, mbox);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase            utc_messaging_messages_set_mbox_type_n01
 * @since_tizen         3.0
 * @description         Sets message box type of a message
 * @scenario            Sets message box type to NULL pointer to get negative result
 */
int utc_messaging_messages_set_mbox_type_n01(void)
{
	int ret;

	ret = messages_set_mbox_type(NULL, 0);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_messaging_messages_set_mbox_type_n02
 * @since_tizen         3.0
 * @description         Sets message box type of a message
 * @scenario            Sets message box type with invalid mbox to get negative result
 */
int utc_messaging_messages_set_mbox_type_n02(void)
{
	int ret;

	message_prepare msg_p = {0,0,0,0,0};
	messages_message_box_e mbox = MESSAGES_MBOX_ALL;

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_set_mbox_type(_msg_sms, mbox);
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		ret = messages_set_mbox_type(_msg_sms, mbox);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


/**
 * @testcase            utc_messaging_messages_get_mbox_type_p
 * @since_tizen         2.3
 * @description         Gets message box type from a message
 * @scenario            Create a SMS
 *                                      Get message box type from created message
 *                                      Check returned box type is available
 */
int utc_messaging_messages_get_mbox_type_p(void)
{
	int ret;
	message_prepare msg_p = {0,0,0,0,0};
	messages_message_box_e mbox;

	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_mbox_type(_msg_sms, &mbox);
		assert_eq(ret, MESSAGES_ERROR_NONE);
		assert(!(MESSAGES_MBOX_ALL > mbox || MESSAGES_MBOX_DRAFT < mbox));
	}
	else
	{
		ret = messages_get_mbox_type(_msg_sms, &mbox);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
/**
 * @testcase		utc_messaging_messages_get_mbox_type_n
 * @since_tizen		2.3
 * @description		Gets message box type from a message
 * @scenario		Gets message box type from NULL pointer to get negative result
 */
int utc_messaging_messages_get_mbox_type_n(void)
{
	int ret;

	ret = messages_get_mbox_type(NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_add_sms_listening_port_p
 * @since_tizen	2.3
 * @description	Adds an additional listening port for the incoming SMS messages.
 * @scenario		Prepare message service handle.
 * 					Set listening port for the SMS messages.
 * 					It return negative result.
 */
int utc_messaging_messages_add_sms_listening_port_p(void)
{
	int ret;

	ret = messages_add_sms_listening_port(_svc, 1000);
	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_add_sms_listening_port_n
 * @since_tizen	2.3
 * @description	Adds an additional listening port for the incoming SMS messages.
 * @scenario		Prepare message service handle.
 * 					Set listening port for the SMS messages.
 * 					but it return negative result. Because message service handle is NULL.
 */
int utc_messaging_messages_add_sms_listening_port_n(void)
{
	int ret;

	ret = messages_add_sms_listening_port(NULL, 1000);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_port_p
 * @since_tizen	2.3
 * @description	Gets the destination port of the message.
 * @scenario		Prepare message handle
 * 					It return positive result.
 */
int utc_messaging_messages_get_message_port_p(void)
{
	int ret;
	message_prepare msg_p = {0,0,0,0,0};
	int port;
	if(is_sms_supported)
	{
		ret = msg_sms_prepare(msg_p);
		assert(!ret);

		ret = messages_get_message_port(_msg_sms, &port);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_get_message_port(_msg_sms, &port);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_port_n
 * @since_tizen	2.3
 * @description	Gets the destination port of the message.
 * @scenario		Prepare message handle
 * 					but it return negative result. Because message handle is NULL.
 */
int utc_messaging_messages_get_message_port_n(void)
{
	int ret;

	ret = messages_get_message_port(NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_search_message_by_id_p
 * @since_tizen	2.3
 * @description	Searches a message with the given message ID.
 * @scenario		Prepare message service handle.
 * 					Set The message ID.
 * 					It return positive result.
 */
int utc_messaging_messages_search_message_by_id_p(void)
{
	int ret;
	messages_message_h searched_msg = NULL;
	int msgid;
	int searched_msgid;

	ret = messages_search_message(
	_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
	NULL, NULL, 0, 0,
	&searched_message_array, &searched_message_length, NULL);
	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);

		if (searched_message_length > 0) {
			ret = messages_get_message_id(searched_message_array[0], &msgid);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_search_message_by_id(_svc, msgid, &searched_msg);
			assert_eq(ret, MESSAGES_ERROR_NONE);

			ret = messages_get_message_id(searched_msg, &searched_msgid);
			messages_destroy_message(searched_msg);
			assert_eq(ret, MESSAGES_ERROR_NONE);
			assert_eq(msgid, searched_msgid);
		}
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_search_message_by_id_n
 * @since_tizen	2.3
 * @description	Searches a message with the given message ID.
 * @scenario		Prepare message service handle.
 * 					Set The message ID.
 * 					but it return negative result. Because service handle is NULL and out parameter is NULL.
 */
int utc_messaging_messages_search_message_by_id_n(void)
{
	int ret;

	ret = messages_search_message_by_id(NULL, 0, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_count_p
 * @since_tizen	2.3
 * @description	Gets the message count in the specific message box.
 * @scenario		Prepare message service handle.
 * 					Set The message box type and message type.
 * 					It return positive result.
 */
int utc_messaging_messages_get_message_count_p(void)
{
	int ret;
	int count;

	if(is_sms_supported)
	{
		ret = messages_get_message_count(_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_get_message_count(_svc, MESSAGES_MBOX_INBOX, MESSAGES_TYPE_SMS, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_get_message_count(_svc, MESSAGES_MBOX_INBOX, MESSAGES_TYPE_MMS, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_get_message_count(_svc, MESSAGES_MBOX_INBOX, MESSAGES_TYPE_UNKNOWN, &count);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_get_message_count(_svc, MESSAGES_MBOX_INBOX, MESSAGES_TYPE_UNKNOWN, &count);
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_get_message_count_n
 * @since_tizen	2.3
 * @description	Gets the message count in the specific message box.
 * @scenario		Prepare message service handle.
 * 					Set The message box type and message type.
 * 					but it return negative result. Because message type is invalid type and out parameter is NULL.
 */
int utc_messaging_messages_get_message_count_n(void)
{
	int ret;

	ret = messages_get_message_count(_svc, MESSAGES_MBOX_INBOX, MESSAGES_TYPE_UNKNOWN, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_free_message_array_p
 * @since_tizen	2.3
 * @description	Frees the message array.
 * @scenario		Prepare the array of the message handle
 * 					Set The message array
 * 					It return positive result.
 */
int utc_messaging_messages_free_message_array_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	/* Assumption: you should have at least one message in MSG_BOX */
	ret = messages_search_message(
					_svc, MESSAGES_MBOX_ALL, MESSAGES_TYPE_UNKNOWN,
					NULL, NULL, 0, 0,
					&searched_message_array, &searched_message_length, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
		if (searched_message_length > 0)
		{
			ret = messages_free_message_array(searched_message_array);
			searched_message_length = 0;
			assert_eq(ret, MESSAGES_ERROR_NONE);
		}
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_free_message_array_n
 * @since_tizen	2.3
 * @description	Frees the message array.
 * @scenario		Prepare the array of the message handle
 * 					Set The message array
 * 					but it return negative result. Because smessage array is NULL.
 */
int utc_messaging_messages_free_message_array_n(void)
{
	int ret;

	ret = messages_free_message_array(NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_close_service_p
 * @since_tizen	2.3
 * @description	Closes a handle for the messaging service.
 * @scenario		Prepare message service handle.
 * 					Set The message service handle.
 * 					It return positive result.
 */
int utc_messaging_messages_close_service_p(void)
{
	int ret = MESSAGES_ERROR_NONE;
	if(is_sms_supported)
	{
		ret = messages_close_service(_svc);
		_svc = NULL;
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		ret = messages_close_service(_svc);
		_svc = NULL;
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_close_service_n
 * @since_tizen	2.3
 * @description	Closes a handle for the messaging service.
 * @scenario		Prepare message service handle.
 * 					Set The message service handle.
 * 					but it return negative result. Because service handle is NULL.
 */
int utc_messaging_messages_close_service_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_close_service(NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}


//& set: MessagesWapPush

static void _push_callback(const char *header, const char *body, int body_length, void *user_data)
{
    // do nothing
}

/**
 * @testcase		utc_messaging_messages_push_add_incoming_cb_p
 * @since_tizen	2.3
 * @description	Registers a callback to be invoked when an WAP Push message is received.
 * @scenario		Prepare message service handle.
 * 					Set The app_id, callback, user_data.
 * 					It return positive result.
 */
int utc_messaging_messages_push_add_incoming_cb_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_add_incoming_cb(_svc, "TEST_APP_ID", _push_callback, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_add_incoming_cb_n
 * @since_tizen	2.3
 * @description	Registers a callback to be invoked when an WAP Push message is received.
 * @scenario		Prepare message service handle.
 * 					Set The app_id, callback, user_data.
 * 					but it return negative result. Because service handle, callback is NULL.
 */
int utc_messaging_messages_push_add_incoming_cb_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_add_incoming_cb(NULL, "TEST_APP_ID", NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_remove_incoming_cb_p
 * @since_tizen	2.3
 * @description	Unregisters the WAP push incoming callback function.
 * @scenario		Prepare message service handle.
 * 					Set The app_id to indicate a destination WAP Push application ID.
 * 					It return negative result.
 */
int utc_messaging_messages_push_remove_incoming_cb_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_remove_incoming_cb(_svc, "TEST_APP_ID");

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_register_n
 * @since_tizen	2.3
 * @description	Unregisters the WAP push incoming callback function.
 * @scenario		Prepare message service handle.
 * 					Set The app_id to indicate a destination WAP Push application ID.
 * 					but it return negative result. Because service handle is NULL.
 */
int utc_messaging_messages_push_remove_incoming_cb_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_remove_incoming_cb(NULL, "TEST_APP_ID");

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

#define PUSH_TEST_APP_ID "TEST_APP_ID"
#define PUSH_TEST_CONTENT_TYPE "text/vnd.wap.connectivity-xml"

/**
 * @testcase		utc_messaging_messages_push_register_p
 * @since_tizen	2.3
 * @description	Registers an application to the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The content_type, app_id.
 * 					It return negative result.
 */
int utc_messaging_messages_push_register_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_register(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_push_deregister(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_register_n
 * @since_tizen	2.3
 * @description	Registers an application to the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The content_type, app_id.
 * 					but it return negative result. Because content_type, app_id is NULL.
 */
int utc_messaging_messages_push_register_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_register(_svc, NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_reregister_p
 * @since_tizen	2.3
 * @description	Re-registers an application to the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The content_type, app_id, dst_content_type, dst_app_id.
 * 					It return positive result.
 */
int utc_messaging_messages_push_reregister_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	if(is_sms_supported)
	{
		ret = messages_push_register(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	ret = messages_push_reregister(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);

		ret = messages_push_deregister(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_reregister_n
 * @since_tizen	2.3
 * @description	Re-registers an application to the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The content_type, app_id, dst_content_type, dst_app_id.
 * 					but it return negative result. Because content_type, app_id, dst_content_type, dst_app_id is NULL.
 */
int utc_messaging_messages_push_reregister_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_reregister(_svc, NULL, NULL, NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_deregister_p
 * @since_tizen	2.3
 * @description	De-registers an application from the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The MIME content type of the content, WAP Push application ID
 * 					It return positive result.
 */
int utc_messaging_messages_push_deregister_p(void)
{
	int ret = MESSAGES_ERROR_NONE;

	if(is_sms_supported)
	{
		ret = messages_push_register(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}

	ret = messages_push_deregister(_svc, PUSH_TEST_CONTENT_TYPE, PUSH_TEST_APP_ID);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_NONE);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}

/**
 * @testcase		utc_messaging_messages_push_deregister_n
 * @since_tizen	2.3
 * @description	De-registers an application from the mapping table of the WAP Push service.
 * @scenario		Prepare message service handle.
 * 					Set The MIME content type of the content, WAP Push application ID
 * 					but it return negative result. Because application ID, MIME content type is NULL.
 */
int utc_messaging_messages_push_deregister_n(void)
{
	int ret = MESSAGES_ERROR_NONE;

	ret = messages_push_deregister(_svc, NULL, NULL);

	if(is_sms_supported)
	{
		assert_eq(ret, MESSAGES_ERROR_INVALID_PARAMETER);
	}
	else
	{
		assert_eq(ret, MESSAGES_ERROR_NOT_SUPPORTED);
	}

	return 0;
}
