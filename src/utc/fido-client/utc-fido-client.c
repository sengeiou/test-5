//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "assert.h"
#include <fido.h>
#include <dlog.h>
#include <glib.h>
#include <system_info.h>

#define STRING_SIZE_1024 1024
#define STRING_SIZE_5000 5000

#define FIDO_CLIENT_UTC_LOG_TAG "NativeTCT"

#define FIDO_CLIENT_UTC_LOG_RED "\033[0;31m"
#define FIDO_CLIENT_UTC_LOG_GREEN "\033[0;32m"
#define FIDO_CLIENT_UTC_LOG_END "\033[0;m"

#define FIDO_CLIENT_UTC_INFO(fmt, arg...) \
	do { \
		dlog_print(DLOG_INFO, FIDO_CLIENT_UTC_LOG_TAG, FIDO_CLIENT_UTC_LOG_GREEN "[%s][Line : %d] " fmt FIDO_CLIENT_UTC_LOG_END, __FILE__, __LINE__, ##arg); \
	} while (0)

#define FN_CALL \
	do { \
		dlog_print(DLOG_INFO, FIDO_CLIENT_UTC_LOG_TAG, FIDO_CLIENT_UTC_LOG_GREEN "[%s][Line : %d] %s >>>>>>> called " FIDO_CLIENT_UTC_LOG_END, __FILE__, __LINE__, __FUNCTION__); \
	} while (0)

#define FIDO_CLIENT_UTC_ERR(fmt, arg...) \
	do { \
		dlog_print(DLOG_ERROR, FIDO_CLIENT_UTC_LOG_TAG, FIDO_CLIENT_UTC_LOG_RED "[%s][Line : %d] " fmt FIDO_CLIENT_UTC_LOG_END, __FILE__, __LINE__, ##arg); \
	} while (0)

#define FIDO_CLIENT_UTC_ERR_CMP(var, ref) \
	if (var != ref) { \
		fprintf(stderr, \
				"\\n[%s][Line : %d] Fail: Values (%s == 0x%x) and (%s == 0x%x)\\n", \
				__FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
		dlog_print(DLOG_ERROR, FIDO_CLIENT_UTC_LOG_TAG, \
				FIDO_CLIENT_UTC_LOG_RED "\\n[%s:%d] Fail: Values (%s == 0x%x) and (%s == 0x%x)\\n" FIDO_CLIENT_UTC_LOG_END, \
				__FILE__, __LINE__, #var, (int)var, #ref, (int)ref); \
	} while (0)

#define FIDO_CLIENT_UTC_ASSERT_EQ(var, ref) \
	if (var != ref) { \
		dlog_print(DLOG_ERROR, FIDO_CLIENT_UTC_LOG_TAG, \
				FIDO_CLIENT_UTC_LOG_RED "(%s == 0x%x) and (%s == 0x%x) are not equal" FIDO_CLIENT_UTC_LOG_END, \
				#var, (int)var, #ref, (int)ref); \
		assert_eq(var, ref); \
	} while (0)


#define FIDO_CLIENT_UTC_ASSERT_NEQ(var, ref) \
	if (var == ref) { \
		dlog_print(DLOG_ERROR, FIDO_CLIENT_UTC_LOG_TAG, \
				FIDO_CLIENT_UTC_LOG_RED "(%s == 0x%x) and (%s == 0x%x) are equal" FIDO_CLIENT_UTC_LOG_END, \
				#var, (int)var, #ref, (int)ref); \
		assert_neq(var, ref); \
	} while (0)

#define FIDO_CLIENT_UTC_ASSERT_NULL(var) \
	if (NULL == var) { \
		dlog_print(DLOG_ERROR, FIDO_CLIENT_UTC_LOG_TAG, \
				FIDO_CLIENT_UTC_LOG_RED "%s is NULL" FIDO_CLIENT_UTC_LOG_END, #var); \
		assert(var); \
	} while (0)

//& set: Fido
#define FIDO_FREE(ptr) \
		if (ptr != NULL) { \
			free(ptr); \
			ptr = NULL; \
		}

static GMainLoop *g_pMainLoop;
static guint g_nTimeoutId;
static int g_CallbackRet = FIDO_ERROR_NONE;
static bool g_feature = true;
bool g_bProcessCallback;

#define JSON_INVALID_STRING "\{\"improperjson\": []}"
#define CLIENT_VENDOR "samsung"
#define GMAINTIMEOUT 			1000
#define MAJOR_VERSION 1
#define MINOR_VERSION 0

#define RUN_GMAIN_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	g_nTimeoutId = g_timeout_add(GMAINTIMEOUT, _fido_callback_timeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(g_nTimeoutId);\
	g_pMainLoop = NULL;\
}

#define QUIT_GMAIN_LOOP {\
	if (g_pMainLoop) {\
		g_main_loop_quit(g_pMainLoop);\
		g_main_loop_unref(g_pMainLoop);\
		g_pMainLoop = NULL;\
	}\
}

static char *
__get_error_code(fido_error_e error_code)
{

	char *error_str = calloc(1, 128);

	if(error_code == FIDO_ERROR_NONE)
		strcpy(error_str, "SUCCESS");
	else if (error_code == FIDO_ERROR_OUT_OF_MEMORY)
		strcpy(error_str, "FIDO_ERROR_OUT_OF_MEMORY");
	else if (error_code == FIDO_ERROR_INVALID_PARAMETER)
		strcpy(error_str, "FIDO_ERROR_INVALID_PARAMETER");
	else if (error_code == FIDO_ERROR_NO_DATA)
		strcpy(error_str, "FIDO_ERROR_NO_DATA");
	else if (error_code == FIDO_ERROR_PERMISSION_DENIED)
		strcpy(error_str, "FIDO_ERROR_PERMISSION_DENIED");
	else if (error_code == FIDO_ERROR_NOT_SUPPORTED)
		strcpy(error_str, "FIDO_ERROR_NOT_SUPPORTED");
	else if (error_code == FIDO_ERROR_USER_ACTION_IN_PROGRESS)
		strcpy(error_str, "FIDO_ERROR_USER_ACTION_IN_PROGRESS");
	else if (error_code == FIDO_ERROR_USER_CANCELLED)
		strcpy(error_str, "FIDO_ERROR_USER_CANCELLED");
	else if (error_code == FIDO_ERROR_UNSUPPORTED_VERSION)
		strcpy(error_str, "FIDO_ERROR_UNSUPPORTED_VERSION");
	else if (error_code == FIDO_ERROR_NO_SUITABLE_AUTHENTICATOR)
		strcpy(error_str, "FIDO_ERROR_NO_SUITABLE_AUTHENTICATOR");
	else if (error_code == FIDO_ERROR_PROTOCOL_ERROR)
		strcpy(error_str, "FIDO_ERROR_PROTOCOL_ERROR");
	else if (error_code == FIDO_ERROR_UNTRUSTED_FACET_ID)
		strcpy(error_str, "FIDO_ERROR_UNTRUSTED_FACET_ID");
	else
		strcpy(error_str, "FIDO_ERROR_UNKNOWN");
	return error_str;
}

static void fido_uaf_get_response_message_callback(fido_error_e tizen_error_code, const char *uaf_response, void *user_data)
{
	g_CallbackRet = tizen_error_code;
	QUIT_GMAIN_LOOP;
}

gboolean _fido_callback_timeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	g_CallbackRet = FIDO_ERROR_UNKNOWN;
	if( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/**
 * @function		utc_fido_client_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_fido_client_startup(void)
{
	int ret = system_info_get_platform_bool("http://tizen.org/feature/fido.uaf", &g_feature);
	if (SYSTEM_INFO_ERROR_NONE != ret) {
		FIDO_CLIENT_UTC_ERR("system_info_get_platform_bool() Fail(%d)", ret);
		return;
	}

	// Launch fido-asm service daemon in advance
	ret = FIDO_ERROR_NONE;
	bool is_supported = true;

	ret = fido_uaf_is_supported(JSON_INVALID_STRING, &is_supported);
	if(!g_feature) {
		assert_eq_no_return(ret, FIDO_ERROR_NOT_SUPPORTED);
		return ;
	}

	assert_eq_no_return(ret, FIDO_ERROR_NONE);
	assert_eq_no_return(is_supported, false);

    return ;
}

/**
 * @function		utc_fido_client_cleanup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void utc_fido_client_cleanup(void)
{
}

/**
 * @testcase		utc_fido_client_get_client_vendor_p
 * @since_tizen		3.0
 * @description		Test gettting fido client vendor.
 */
int utc_fido_client_get_client_vendor_p(void)
{
	int ret = FIDO_ERROR_NONE;
	char *vendor = NULL;

	ret = fido_get_client_vendor(&vendor);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_NONE);
	assert_eq(strcmp(CLIENT_VENDOR, vendor), 0);

	return 0;
}

/**
 * @testcase		utc_fido_client_get_client_vendor_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client vendor with invalid parameter.
 */
int utc_fido_client_get_client_vendor_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_get_client_vendor(NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_get_client_version_p
 * @since_tizen		3.0
 * @description		Test gettting fido client version.
 */
int utc_fido_client_get_client_version_p(void)
{
	int ret = FIDO_ERROR_NONE;
	int major_version = -1;
	int minor_version = -1;

	ret = fido_get_client_version(&major_version, &minor_version);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_NONE);
	assert_eq(major_version, MAJOR_VERSION);
	assert_eq(minor_version, MINOR_VERSION);

	return 0;
}

/**
 * @testcase		utc_fido_client_get_client_version_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client version with invalid parameter.
 */
int utc_fido_client_get_client_version_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_get_client_version(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_uaf_is_supported_p
 * @since_tizen		3.0
 * @description		Test if uaf is supported.
 */
int utc_fido_client_uaf_is_supported_p(void)
{
	int ret = FIDO_ERROR_NONE;
	bool is_supported = true;

	ret = fido_uaf_is_supported(JSON_INVALID_STRING, &is_supported);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_NONE);
	assert_eq(is_supported, false);

	return 0;
}

/**
 * @testcase		utc_fido_client_uaf_is_supported_n
 * @since_tizen		3.0
 * @description		Test fail if uaf is supported with invalid parameter.
 */
int utc_fido_client_uaf_is_supported_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_uaf_is_supported(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_uaf_get_response_message_n1
 * @since_tizen		3.0
 * @description		Test fail getting fido client uaf response message with invalid parameter.
 */
int utc_fido_client_uaf_get_response_message_n1(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_uaf_get_response_message(NULL, NULL, NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_uaf_get_response_message_n2
 * @since_tizen		3.0
 * @description		Test fail getting fido client uaf response message with invalid JSON string.
 */
int utc_fido_client_uaf_get_response_message_n2(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_uaf_get_response_message(JSON_INVALID_STRING, NULL, fido_uaf_get_response_message_callback, NULL);
		if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_NONE);
	RUN_GMAIN_LOOP
	assert_eq(g_CallbackRet, FIDO_ERROR_PROTOCOL_ERROR);

	g_CallbackRet = FIDO_ERROR_NONE;

	return 0;
}

/**
 * @testcase		utc_fido_client_uaf_set_server_result_n
 * @since_tizen		3.0
 * @description		Test fail setting fido client uaf server result with invalid parameter.
 */
int utc_fido_client_uaf_set_server_result_n(void)
{
	int ret = FIDO_ERROR_NONE;
	int set_val = 0;

	ret = fido_uaf_set_server_result(set_val, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_foreach_authenticator_n
 * @since_tizen		3.0
 * @description		Test fail fido client foreach authenticator with invalid parameter.
 */
int utc_fido_client_foreach_authenticator_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_foreach_authenticator(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_title_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator title with invalid parameter.
 */
int utc_fido_client_authenticator_get_title_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_title(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_aaid_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator aaid with invalid parameter.
 */
int utc_fido_client_authenticator_get_aaid_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_aaid(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_description_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator description with invalid parameter.
 */
int utc_fido_client_authenticator_get_description_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_description(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_assertion_scheme_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator assertion scheme with invalid parameter.
 */
int utc_fido_client_authenticator_get_assertion_scheme_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_assertion_scheme(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_algorithm_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator algorithm with invalid parameter.
 */
int utc_fido_client_authenticator_get_algorithm_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_algorithm(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_foreach_attestation_type_n
 * @since_tizen		3.0
 * @description		Test fail authenticator foreach attestation with invalid parameter.
 */
int utc_fido_client_authenticator_foreach_attestation_type_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_foreach_attestation_type(NULL, NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_verification_method_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator verification method with invalid parameter.
 */
int utc_fido_client_authenticator_get_verification_method_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_verification_method(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_key_protection_method_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator key protection method with invalid parameter.
 */
int utc_fido_client_authenticator_get_key_protection_method_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_key_protection_method(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_matcher_protection_method_n
 * @since_tizen		3.0
 * @description		Test fail getting authenticator matcher protection method with invalid parameter.
 */
int utc_fido_client_authenticator_get_matcher_protection_method_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_matcher_protection_method(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_attachment_hint_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client authenticator attachment hint with invalid parameter.
 */
int utc_fido_client_authenticator_get_attachment_hint_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_attachment_hint(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_is_second_factor_only_p
 * @since_tizen		3.0
 * @description		Test getting fido client authenticator is second factor only.
 */
int utc_fido_client_authenticator_get_is_second_factor_only_p(void)
{

	bool ret = fido_authenticator_get_is_second_factor_only(NULL);
	assert_eq(ret, false);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_tc_discplay_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client authenticator tc display with invalid parameter.
 */
int utc_fido_client_authenticator_get_tc_discplay_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_tc_discplay(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_tc_display_type_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client authenticator tc display type with invalid parameter.
 */
int utc_fido_client_authenticator_get_tc_display_type_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_tc_display_type(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_client_authenticator_get_icon_n
 * @since_tizen		3.0
 * @description		Test fail getting fido client authenticator icon with invalid parameter.
 */
int utc_fido_client_authenticator_get_icon_n(void)
{
	int ret = FIDO_ERROR_NONE;

	ret = fido_authenticator_get_icon(NULL, NULL);
	if(!g_feature) {
		assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
		return 0;
	}

	assert_eq(ret, FIDO_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_fido_foreach_authenticator_p
 * @since_tizen		3.0
 * @description		Test success fido client find authenticators
 */
void fido_attestation_type_cb_list(fido_auth_attestation_type_e att_type, void *user_data)
{
	int *res = (int*)user_data;
	*res = 0;

	if (att_type == -1) {
		*res = 1;
	}
	return;
}

static int
__get_authinfo_string(const fido_authenticator_h auth)
{
	char *title =  NULL;
	fido_authenticator_get_title(auth, &title);
	if (!title) {
		return false;
	}
	free(title);

	char *aaid = NULL;
	fido_authenticator_get_aaid(auth, &aaid);
	if (!aaid) {
		return false;
	}
	free(aaid);

	char *description = NULL;
	fido_authenticator_get_description(auth, &description);
	if (!description) {
		return false;
	}
	free(description);

	char *scheme = NULL;
	fido_authenticator_get_assertion_scheme(auth, &scheme);
	if (!scheme) {
		return false;
	}
	free(scheme);

	int *res = (int*)calloc(1, 4);
	*res = 0;

	fido_authenticator_foreach_attestation_type(auth, fido_attestation_type_cb_list, res);
	if(*res == 1) {
		goto error;
    }

	fido_auth_algo_e get_algo = -1;
	fido_authenticator_get_algorithm(auth, &get_algo);
	if (get_algo == -1) {
		goto error ;
	}

	fido_auth_user_verify_type_e user_ver = -1;
	fido_authenticator_get_verification_method(auth, &user_ver);
	if (user_ver == -1) {
		goto error;
	}

	fido_auth_key_protection_type_e key_protection = -1;
	fido_authenticator_get_key_protection_method(auth, &key_protection);
	if (key_protection == -1) {
		goto error ;
	}

	fido_auth_matcher_protection_type_e matcher_protection = -1;
	fido_authenticator_get_matcher_protection_method(auth, &matcher_protection);
	if (matcher_protection == -1) {
		goto error ;
	}

	fido_auth_attachment_hint_e attachment_hint = -1;
	fido_authenticator_get_attachment_hint(auth, &attachment_hint);
	if (attachment_hint == -1) {
		goto error ;
	}

	fido_auth_tc_display_type_e tc_discplay = -1;
	fido_authenticator_get_tc_discplay(auth, &tc_discplay);
	if (tc_discplay == -1) {
		goto error ;
	}

	char *tc_display_type = NULL;
	fido_authenticator_get_tc_display_type(auth, &tc_display_type);
	if (!tc_display_type) {
		goto error ;
	}
	free(tc_display_type);

	char *icon = NULL;
	fido_authenticator_get_icon(auth, &icon);
	if (!icon) {
		goto error ;
	}
	free(icon);
    	free(res);
	return true;

error:
    free(res);
    return false;
}

static void
auth_list_cb(const fido_authenticator_h auth, void *user_data)
{
	int *res = (int*)user_data;
	*res = 0;

	int ret = __get_authinfo_string(auth);

	if(ret == false)
		*res = 1;
	return;
}

int utc_fido_client_foreach_authenticator_p(void)
{

	int *res = (int*)calloc(1, 4);
	*res = 0;

	int ret = fido_foreach_authenticator(auth_list_cb, res);
	if(!g_feature) {
	free(res);
	assert_eq(ret, FIDO_ERROR_NOT_SUPPORTED);
	return 0;
	}

	assert_eq(ret, 0);
	assert_eq(*res, 0);
	free(res);
	return 0;
}
