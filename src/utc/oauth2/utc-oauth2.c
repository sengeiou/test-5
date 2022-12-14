#include "assert.h"
#include <oauth2.h>
#include <string.h>

#define OAUTH2_FREE(ptr) \
		if (ptr != NULL) { \
			free(ptr); \
			ptr = NULL; \
		}

static bool manager_created = false;
static bool request_created = false;
static oauth2_manager_h manager = NULL;
static oauth2_request_h request = NULL;
static int _is_fail = true;

/**
 * @function		utc_oauth2_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_oauth2_startup(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_manager_create(&manager);
	if (ret == OAUTH2_ERROR_NONE)
	{
		manager_created = true;
	}

	ret = oauth2_request_create(&request);
	if (ret == OAUTH2_ERROR_NONE)
	{
		request_created = true;
	}
}

/**
 * @function		utc_oauth2_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_oauth2_cleanup(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_manager_destroy(manager);
	if (ret == OAUTH2_ERROR_NONE)
	{
		manager_created = false;
	}
	manager = NULL;

	ret = oauth2_request_destroy(request);
	if (ret == OAUTH2_ERROR_NONE)
	{
		request_created = false;
	}
	request = NULL;
}

/**
 * @testcase		utc_oauth2_manager_create_p
 * @since_tizen		2.4
 * @description		This positive TC tests oauth2 manager creation
 */
int utc_oauth2_manager_create_p(void)
{
	assert(manager_created);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_create_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager creation
 */
int utc_oauth2_manager_create_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_manager_create(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_destroy_p
 * @since_tizen		2.4
 * @description		This positive TC tests destroying oauth2 manager handle with valid inputs
 */
int utc_oauth2_manager_destroy_p(void)
{
	oauth2_manager_h manager_local = NULL;

	int ret = oauth2_manager_create(&manager_local);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	ret = oauth2_manager_destroy(manager_local);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_destroy_n
 * @since_tizen		2.4
 * @description		This negative TC tests destroying oauth2 manager handle with invalid input
 */
int utc_oauth2_manager_destroy_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_manager_destroy(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_request_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager request token with invalid inputs
 */
int utc_oauth2_manager_request_token_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_request_token(NULL, NULL, NULL, NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_request_authorization_grant_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager request authorization grant with invalid inputs
 */
int utc_oauth2_manager_request_authorization_grant_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_request_authorization_grant(NULL, NULL, NULL, NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_request_access_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager request access token with invalid inputs
 */
int utc_oauth2_manager_request_access_token_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_request_access_token(NULL, NULL, NULL, NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_refresh_access_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager refresh access token with invalid inputs
 */
int utc_oauth2_manager_refresh_access_token_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_refresh_access_token(NULL, NULL, NULL, NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_is_request_in_progress_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 manager request progress state with invalid inputs
 */
int utc_oauth2_manager_is_request_in_progress_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_is_request_in_progress(NULL);
	assert_eq(ret, false);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_clear_cookies_n
 * @since_tizen		2.4
 * @description		This negative TC tests clearing oauth2 manager cookies with invalid inputs
 */
int utc_oauth2_manager_clear_cookies_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_clear_cookies(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_manager_clear_cache_n
 * @since_tizen		2.4
 * @description		This negative TC tests clearing oauth2 manager cache with invalid inputs
 */
int utc_oauth2_manager_clear_cache_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_manager_clear_cache(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}


/*
 * request
 */

/**
 * @testcase		utc_oauth2_request_create_p
 * @since_tizen		2.4
 * @description		This positive TC tests oauth2 request creation
 */
int utc_oauth2_request_create_p(void)
{
	assert(request_created);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_create_n
 * @since_tizen		2.4
 * @description		This negative TC tests oauth2 request creation
 */
int utc_oauth2_request_create_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_request_create(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_destroy_p
 * @since_tizen		2.4
 * @description		This positive TC tests destroying oauth2 request with valid input
 */
int utc_oauth2_request_destroy_p(void)
{
	assert(request_created);
	utc_oauth2_cleanup();

	assert(!request_created);

	utc_oauth2_startup();

	return 0;
}

/**
 * @testcase		utc_oauth2_request_destroy_n
 * @since_tizen		2.4
 * @description		This negative TC tests destroying oauth2 request with invalid input
 */
int utc_oauth2_request_destroy_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	ret = oauth2_request_destroy(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_auth_end_point_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid url
 */
int utc_oauth2_request_set_auth_end_point_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_auth_end_point_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_auth_end_point_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle end point url with invalid inputs
 */
int utc_oauth2_request_set_auth_end_point_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_auth_end_point_url(NULL, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_token_end_point_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle token with valid end point url
 */
int utc_oauth2_request_set_token_end_point_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_token_end_point_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_token_end_point_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle end point url token with invalid inputs
 */
int utc_oauth2_request_set_token_end_point_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_token_end_point_url(NULL, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_redirection_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid redirection url
 */
int utc_oauth2_request_set_redirection_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_redirection_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_redirection_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests seting oauth2 request handle redirection url with invalid inputs
 */
int utc_oauth2_request_set_redirection_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_redirection_url(NULL, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_refresh_token_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid refresh token url
 */
int utc_oauth2_request_set_refresh_token_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_refresh_token_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle refresh token url with invalid inputs
 */
int utc_oauth2_request_set_refresh_token_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token_url(NULL, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_refresh_token_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid refresh token
 */
int utc_oauth2_request_set_refresh_token_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token(request, "refresh_token");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_refresh_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle refresh token with invalid inputs
 */
int utc_oauth2_request_set_refresh_token_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token(NULL, "refresh_token");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_response_type_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid response type
 */
int utc_oauth2_request_set_response_type_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	oauth2_response_type_e type = OAUTH2_RESPONSE_TYPE_CODE;

	ret = oauth2_request_set_response_type(request, type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_response_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle with invalid inputs
 */
int utc_oauth2_request_set_response_type_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_response_type(NULL, OAUTH2_RESPONSE_TYPE_CODE);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_client_id_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid client id
 */
int utc_oauth2_request_set_client_id_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_id(request, "client_id");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_client_id_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle client id with invalid inputs
 */
int utc_oauth2_request_set_client_id_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_id(NULL, "client_id");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_client_authentication_type_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid client authentication type
 */
int utc_oauth2_request_set_client_authentication_type_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_authentication_type(request, OAUTH2_CLIENT_AUTHENTICATION_TYPE_REQUEST_BODY);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_client_authentication_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle client authentication type with invalid inputs
 */
int utc_oauth2_request_set_client_authentication_type_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_authentication_type(NULL, OAUTH2_CLIENT_AUTHENTICATION_TYPE_REQUEST_BODY);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_scope_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid set scope
 */
int utc_oauth2_request_set_scope_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_scope(request, "email");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_scope_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle scope with invalid inputs
 */
int utc_oauth2_request_set_scope_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_scope(NULL, "email");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_state_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid state
 */
int utc_oauth2_request_set_state_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_state(request, "sample_state");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_state_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle state with invalid inputs
 */
int utc_oauth2_request_set_state_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_state(NULL, "sample_state");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_grant_type_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid grant type
 */
int utc_oauth2_request_set_grant_type_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	int type = OAUTH2_GRANT_TYPE_AUTH_CODE;

	ret = oauth2_request_set_grant_type(request, type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_grant_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle grant type with invalid inputs
 */
int utc_oauth2_request_set_grant_type_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	int type = OAUTH2_GRANT_TYPE_AUTH_CODE;

	ret = oauth2_request_set_grant_type(NULL, type);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_authorization_code_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid authorization code
 */
int utc_oauth2_request_set_authorization_code_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_authorization_code(request, "authorization_code");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_authorization_code_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle authorization with invalid inputs
 */
int utc_oauth2_request_set_authorization_code_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_authorization_code(NULL, "authorization_code");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_user_name_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid user name
 */
int utc_oauth2_request_set_user_name_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_user_name(request, "user_name");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_user_name_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle user name with invalid inputs
 */
int utc_oauth2_request_set_user_name_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_user_name(NULL, "user_name");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_password_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid password
 */
int utc_oauth2_request_set_password_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_password(request, "password");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_set_password_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle password with invalid inputs
 */
int utc_oauth2_request_set_password_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_password(NULL, "password");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_add_custom_data_p
 * @since_tizen		2.4
 * @description		This positive TC tests setting oauth2 request handle with valid custom data
 */
int utc_oauth2_request_add_custom_data_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_add_custom_data(request, "custom_key", "custom_value");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_add_custom_data_n
 * @since_tizen		2.4
 * @description		This negative TC tests setting oauth2 request handle with invalid custom data inputs
 */
int utc_oauth2_request_add_custom_data_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_add_custom_data(NULL, "custom_key", "custom_value");
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_auth_end_point_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request handle with valid end point url
 */
int utc_oauth2_request_get_auth_end_point_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_auth_end_point_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *url = NULL;
	ret = oauth2_request_get_auth_end_point_url(request, &url);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("www.example.com", url), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_auth_end_point_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request handle end point url with invalid inputs
 */
int utc_oauth2_request_get_auth_end_point_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *url = NULL;

	ret = oauth2_request_get_auth_end_point_url(NULL, &url);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_token_end_point_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request token end point url with valid inputs
 */
int utc_oauth2_request_get_token_end_point_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_token_end_point_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *url = NULL;
	ret = oauth2_request_get_token_end_point_url(request, &url);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("www.example.com", url), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_token_end_point_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request token end point url with invalid inputs
 */
int utc_oauth2_request_get_token_end_point_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *url = NULL;

	ret = oauth2_request_get_token_end_point_url(NULL, &url);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_redirection_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request redirection url with valid inputs
 */
int utc_oauth2_request_get_redirection_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_redirection_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *url = NULL;
	ret = oauth2_request_get_redirection_url(request, &url);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("www.example.com", url), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_redirection_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request redirection url with invalid inputs
 */
int utc_oauth2_request_get_redirection_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *url = NULL;

	ret = oauth2_request_get_redirection_url(NULL, &url);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_refresh_token_url_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request refresh token url with valid input
 */
int utc_oauth2_request_get_refresh_token_url_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token_url(request, "www.example.com");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *url = NULL;
	ret = oauth2_request_get_refresh_token_url(request, &url);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("www.example.com", url), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_refresh_token_url_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request refresh token url with invalid inputs
 */
int utc_oauth2_request_get_refresh_token_url_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *url = NULL;

	ret = oauth2_request_get_refresh_token_url(NULL, &url);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_refresh_token_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request refresh token with valid inputs
 */
int utc_oauth2_request_get_refresh_token_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_refresh_token(request, "refresh_token");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *token = NULL;
	ret = oauth2_request_get_refresh_token(request, &token);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("refresh_token", token), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_refresh_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request refresh token with invalid inputs
 */
int utc_oauth2_request_get_refresh_token_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *token = NULL;

	ret = oauth2_request_get_refresh_token_url(NULL, &token);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_response_type_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request response type with valid inputs
 */
int utc_oauth2_request_get_response_type_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	oauth2_response_type_e set_type = OAUTH2_RESPONSE_TYPE_CODE;

	ret = oauth2_request_set_response_type(request, set_type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	oauth2_response_type_e type;
	ret = oauth2_request_get_response_type(request, &type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(type, OAUTH2_RESPONSE_TYPE_CODE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_response_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request response type with invalid inputs
 */
int utc_oauth2_request_get_response_type_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	oauth2_response_type_e type;

	ret = oauth2_request_get_response_type(NULL, &type);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_client_id_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request client id with valid inputs
 */
int utc_oauth2_request_get_client_id_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_id(request, "client_id");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *id = NULL;
	ret = oauth2_request_get_client_id(request, &id);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("client_id", id), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_client_id_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request client id with invalid inputs
 */
int utc_oauth2_request_get_client_id_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *id = NULL;

	ret = oauth2_request_get_client_id(NULL, &id);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_client_secret_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request client secret with valid inputs
 */
int utc_oauth2_request_get_client_secret_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_client_secret(request, "client_secret");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *secret = NULL;
	ret = oauth2_request_get_client_secret(request, &secret);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("client_secret", secret), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_client_secret_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request client secret with invalid inputs
 */
int utc_oauth2_request_get_client_secret_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *secret = NULL;

	ret = oauth2_request_get_client_secret(NULL, &secret);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_scope_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request scope with valid inputs
 */
int utc_oauth2_request_get_scope_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_scope(request, "email");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *scope = NULL;
	ret = oauth2_request_get_scope(request, &scope);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("email", scope), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_scope_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request scope with invalid inputs
 */
int utc_oauth2_request_get_scope_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *scope = NULL;

	ret = oauth2_request_get_scope(NULL, &scope);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_state_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request state with valid inputs
 */
int utc_oauth2_request_get_state_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_state(request, "sample_state");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *state = NULL;
	ret = oauth2_request_get_state(request, &state);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("sample_state", state), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_state_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request state with invalid inputs
 */
int utc_oauth2_request_get_state_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *state = NULL;

	ret = oauth2_request_get_state(NULL, &state);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_grant_type_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request grant type with valid inputs
 */
int utc_oauth2_request_get_grant_type_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	int set_type = OAUTH2_GRANT_TYPE_AUTH_CODE;

	ret = oauth2_request_set_grant_type(request, set_type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	oauth2_grant_type_e type;
	ret = oauth2_request_get_grant_type(request, &type);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(type, OAUTH2_GRANT_TYPE_AUTH_CODE);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_grant_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request grant type with invalid inputs
 */
int utc_oauth2_request_get_grant_type_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	oauth2_grant_type_e type;

	ret = oauth2_request_get_grant_type(NULL, &type);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_authorization_code_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request authorization code with valid inputs
 */
int utc_oauth2_request_get_authorization_code_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_authorization_code(request, "auth_code");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *code = NULL;
	ret = oauth2_request_get_authorization_code(request, &code);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("auth_code", code), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_authorization_code_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request authorization code with invalid inputs
 */
int utc_oauth2_request_get_authorization_code_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *code = NULL;

	ret = oauth2_request_get_authorization_code(NULL, &code);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_user_name_p
 * @since_tizen		2.4
 * @description		This psoitive TC tests getting oauth2 request user name with invalid inputs
 */
int utc_oauth2_request_get_user_name_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_user_name(request, "user_name");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *user_name = NULL;
	ret = oauth2_request_get_user_name(request, &user_name);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("user_name", user_name), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_user_name_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request user name with invalid inputs
 */
int utc_oauth2_request_get_user_name_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *user_name = NULL;

	ret = oauth2_request_get_user_name(NULL, &user_name);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_password_p
 * @since_tizen		2.4
 * @description		This psoitive TC tests getting oauth2 request password with valid inputs
 */
int utc_oauth2_request_get_password_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_set_password(request, "password");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *password = NULL;
	ret = oauth2_request_get_password(request, &password);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("password", password), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_password_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request password with invalid inputs
 */
int utc_oauth2_request_get_password_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;
	char *password = NULL;

	ret = oauth2_request_get_password(NULL, &password);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_custom_data_p
 * @since_tizen		2.4
 * @description		This positive TC tests getting oauth2 request custom data with invalid inputs
 */
int utc_oauth2_request_get_custom_data_p(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_request_add_custom_data(request, "c_key", "c_val");
	assert_eq(ret, OAUTH2_ERROR_NONE);

	char *val = NULL;
	ret = oauth2_request_get_custom_data(request, "c_key", &val);
	assert_eq(ret, OAUTH2_ERROR_NONE);

	assert_eq(strcmp("c_val", val), 0);

	return 0;
}

/**
 * @testcase		utc_oauth2_request_get_custom_data_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 request custtom data with invalid inputs
 */
int utc_oauth2_request_get_custom_data_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	char *val = NULL;
	ret = oauth2_request_get_custom_data(request, "key", &val);
	assert_eq(ret, OAUTH2_ERROR_VALUE_NOT_FOUND);

	return 0;
}


/*
 * response
 */

/**
 * @testcase		utc_oauth2_response_destroy_n
 * @since_tizen		2.4
 * @description		This negative TC tests destryoing oauth2 response with invalid inputs
 */
int utc_oauth2_response_destroy_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	ret = oauth2_response_destroy(NULL);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_authorization_code_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 respose authorization code with invalid inputs
 */
int utc_oauth2_response_get_authorization_code_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *code = NULL;

	ret = oauth2_response_get_authorization_code(NULL, &code);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_state_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response state with invalid inputs
 */
int utc_oauth2_response_get_state_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *state = NULL;

	ret = oauth2_response_get_state(NULL, &state);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_access_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response access token with invalid inputs
 */
int utc_oauth2_response_get_access_token_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *token = NULL;

	ret = oauth2_response_get_access_token(NULL, &token);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_token_type_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response token type with invalid inputs
 */
int utc_oauth2_response_get_token_type_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *type = NULL;

	ret = oauth2_response_get_token_type(NULL, &type);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_expires_in_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response expires time with invalid inputs
 */
int utc_oauth2_response_get_expires_in_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	long long expires_in = 0;

	ret = oauth2_response_get_expires_in(NULL, &expires_in);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_refresh_token_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response refresh token with invalid inputs
 */
int utc_oauth2_response_get_refresh_token_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *token = NULL;

	ret = oauth2_response_get_refresh_token(NULL, &token);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_scope_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response scope with invalid inputs
 */
int utc_oauth2_response_get_scope_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *scope = NULL;

	ret = oauth2_response_get_scope(NULL, &scope);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_error_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response error with invalid inputs
 */
int utc_oauth2_response_get_error_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	oauth2_error_h err = NULL;

	ret = oauth2_response_get_error(NULL, &err);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_response_get_custom_data_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 response custom data with invalid inputs
 */
int utc_oauth2_response_get_custom_data_n(void)
{
	assert(request);

	int ret = OAUTH2_ERROR_NONE;

	char *val = NULL;
	ret = oauth2_response_get_custom_data(NULL, "key", &val);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}


/*
 * error
 */

/**
 * @testcase		utc_oauth2_error_get_code_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 error code with invalid inputs
 */
int utc_oauth2_error_get_code_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	int val1 = 0;
	int val2 = 0;

	ret = oauth2_error_get_code(NULL, &val1, &val2);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_error_get_description_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 error description with invalid inputs
 */
int utc_oauth2_error_get_description_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *description = NULL;

	ret = oauth2_error_get_description(NULL, &description);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_error_get_uri_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 error uri with invalid inputs
 */
int utc_oauth2_error_get_uri_n(void)
{
	int ret = OAUTH2_ERROR_NONE;
	char *uri = NULL;

	ret = oauth2_error_get_uri(NULL, &uri);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase		utc_oauth2_error_get_custom_data_n
 * @since_tizen		2.4
 * @description		This negative TC tests getting oauth2 error custom data with invalid inputs
 */
int utc_oauth2_error_get_custom_data_n(void)
{
	int ret = OAUTH2_ERROR_NONE;

	char *val = NULL;
	ret = oauth2_error_get_custom_data(NULL, "key", &val);
	assert_eq(ret, OAUTH2_ERROR_INVALID_PARAMETER);

	return 0;
}
