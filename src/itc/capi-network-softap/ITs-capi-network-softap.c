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

#include<ITs-capi-network-softap-common.h>
static softap_h g_hSoftapHandle =  NULL;


/**
 * @brief 		Called when the connection state is changed.
 * @since_tizen 5.0
 * @remarks 		The @a client should not be released by the application and it is valid only in this function.\n
 *          		In order to use it outside this function, a user must copy the client with softap_client_clone().
 * @param[in]  		client  The client of which connection state is changed
 * @param[in]  		opened  @c true when connection is opened, otherwise false
 * @param[in]  		user_data  The user data passed from softap_set_client_connection_state_changed_cb()
 * @pre  		If you register callback function using softap_set_client_connection_state_changed_cb(), this will be invoked when the connection state is   				changed.
**/

static void softapClientConnectionStateChangedCb(softap_client_h client, bool opened, void *user_data)
{
	return;
}

/**
 * @brief 		Called when you get the connected client repeatedly.
 * @since_tizen 5.0
 * @remarks 		The @a client should not be released by the application and it is valid only in this function.\n
 *          		In order to use the client outside this function, a user must copy the client with softap_client_clone().
 * @param[in]  		client  The connected client
 * @param[in]  		user_data  The user data passed from the request function
 * @return  		@c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @pre  		softap_foreach_connected_clients() will invoke this callback.
 * @see  		softap_foreach_connected_clients()
*/
static bool softapConnectedClientCb(softap_client_h client, void *user_data)
{
	return true;
}

/**
 * @brief Called when the SoftAP is enabled.
 * @since_tizen 5.0
 * @param[in]  result  The result of enabling the SoftAP
 * @param[in]  is_requested  Indicates whether this change is requested
 * @param[in]  user_data  The user data passed from softap_set_enabled_cb()
 * @pre  If you register callback function using softap_set_enabled_cb(), this will be invoked when the SoftAP is enabled.
 */

static void softapSetEnabledCb(softap_error_e error, softap_disabled_cause_e code, void *data)
{
	return;
}

/**
 * @brief Called when the SoftAP is disabled.
 * @since_tizen 5.0
 * @param[in]  result  The result of disabling the SoftAP
 * @param[in]  cause  The cause of disabling
 * @param[in]  user_data  The user data passed from softap_set_disabled_cb()
 * @pre  If you register callback function using softap_set_disabled_cb(), this will be invoked when the SoftAP is disabled.
 */
static void softapSetDisabledCb(softap_error_e error, softap_disabled_cause_e code, void *data)
{
	return;
}
/**
 * @brief Called when the security type of SoftAP is changed.
 * @since_tizen 5.0
 * @param[in]  changed_type  The changed security type
 * @param[in]  user_data  The user data passed from the register function
*/
static void softapSecurityTypeChangedCb(softap_security_type_e changed_type, void *user_data)
{
	return;
}

/**
 * @brief Called when the visibility of SSID is changed.
 * @since_tizen 5.0
 * @param[in]  changed_visible  The changed visibility of SSID
 * @param[in]  user_data  The user data passed from the register function
 */
static void softapSsidVisibilityChangedCb(bool changed_visible, void *user_data)
{
	return;
}
/**
 * @brief Called when the passphrase Changed for softap.
 * @since_tizen 5.0
 * @param[in]  user_data  The user data passed from the register function
 */
static void softapPassphraseChangedCb(void *user_data)
{
	return;
}

/**
* @function             ITs_softap_startup
* @description          Called before each test
* @parameter            NA
* @return               NA
*/

void ITs_softap_startup(void)
{
	g_bIsFeatureSupported = true;
	g_bSoftapFetaureSupported = false;
	g_hSoftapHandle = NULL;
	g_bIsFeatureMismatched = false;
	g_bIsSoftapHandleCreated = false;

	g_bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(SOFTAP_FEATURE,API_NAMESPACE);

	int nRet = softap_create(&g_hSoftapHandle);

	if (!g_bIsFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[%s:%d] softap_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__,SoftApGetError(nRet), nRet);
                        dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] softap_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)", __FILE__, __LINE__, SoftApGetError(nRet), nRet);
                        g_bIsFeatureMismatched = true;
                        return;
                }

                FPRINTF("[%s:%d] softap_create is unsupported\\n", __FILE__, __LINE__);
                dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] softap_create feature is unsupported", __FILE__, __LINE__);
                g_bSoftapFetaureSupported = false;
		return;
	}
	if(nRet != SOFTAP_ERROR_NONE || g_hSoftapHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] softap handle creation failed. \\n", __LINE__, API_NAMESPACE);
		g_bIsSoftapHandleCreated = false;
                return;
	}
	else
	{
		FPRINTF("[Line : %d][%s] softap handle created successfully \\n", __LINE__, API_NAMESPACE);
		g_bIsSoftapHandleCreated = true;
	}
	return;
}
/**
* @function             ITs_softap_cleanup
* @description          Called after each test
* @parameter            NA
* @return               NA
*/
void ITs_softap_cleanup(void)
{
	if(g_hSoftapHandle)
	{
	  int nRet = softap_destroy(g_hSoftapHandle);
	  PRINT_RESULT_NORETURN(SOFTAP_ERROR_NONE, nRet, "softap_destroy", SoftApGetError(nRet));
	  g_hSoftapHandle = NULL;
	}
	return;
}

//& type: auto
//& purpose:  scenario to create and destroy softap handle.
/**
* @testcase                     ITs_softap_create_destroy_p
* @author               	SRID(awadhesh1.s)
* @reviewer             	SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  create and destroy handle.
* @apicovered                   softap_create , softap_destroy.
* @passcase                     if softap handle create and destroy properly.
* @failcase                     if softap handle create or destroy fails.
* @precondition                 softap handle must be NULL before create.
* @postcondition                softap handle must be NULL after destroy.
*/

int ITs_softap_create_destroy_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	nRet = softap_destroy(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_destroy", SoftApGetError(nRet));
	g_hSoftapHandle = NULL;

	nRet = softap_create(&g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_create", SoftApGetError(nRet));

	CHECK_HANDLE(g_hSoftapHandle, "softap_create");
	return 0;
}
//& type: auto
//& purpose:  scenario to check softap is enabled.
/**
* @testcase                     ITs_softap_is_enabled_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  get softap status (enable or diable).
* @apicovered                   softap_is_enabled.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_is_enabled_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	bool bEnable = false;

	nRet = softap_is_enabled(g_hSoftapHandle, &bEnable);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_is_enabled", SoftApGetError(nRet));

	return 0;
}
//& purpose:  scenario to set unset softap enable callback.
/**
* @testcase                     ITs_softap_set_unset_enabled_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  get softap status (enable or diable).
* @apicovered                   softap_is_enabled.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_unset_enabled_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	nRet = softap_set_enabled_cb(g_hSoftapHandle, softapSetEnabledCb, NULL);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_enabled_cb", SoftApGetError(nRet));

	nRet = softap_unset_enabled_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_enabled_cb", SoftApGetError(nRet));

        return 0;
}

//& purpose:  set callback for connected client.
/**
* @testcase                     ITs_softap_foreach_connected_clients_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set cllback for connected client.
* @apicovered                   softap_foreach_connected_clients.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_foreach_connected_clients_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;

	nRet = softap_foreach_connected_clients(g_hSoftapHandle, softapConnectedClientCb, NULL);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_foreach_connected_clients", SoftApGetError(nRet));

	return 0;
}
//& purpose:  set and unset callback for softap disable.
/**
* @testcase                     ITs_softap_set_unset_disabled_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set and unset callback for softap disable.
* @apicovered                   softap_set_disabled_cb , softap_unset_disabled_cb.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_unset_disabled_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;

	nRet = softap_set_disabled_cb(g_hSoftapHandle, softapSetDisabledCb, NULL);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_disabled_cb", SoftApGetError(nRet));

	nRet = softap_unset_disabled_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_disabled_cb", SoftApGetError(nRet));

	return 0;
}
//& purpose:  set and unset callback for client connection change.
/**
* @testcase                     ITs_softap_set_unset_client_connection_state_changed_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set and unset callback for softap disable.
* @apicovered                   softap_set_client_connection_state_changed_cb,
*				softap_unset_client_connection_state_changed_cb.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_unset_client_connection_state_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	nRet = softap_set_client_connection_state_changed_cb(g_hSoftapHandle, softapClientConnectionStateChangedCb, NULL);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_client_connection_state_changed_cb", SoftApGetError(nRet));

	nRet = softap_unset_client_connection_state_changed_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_client_connection_state_changed_cb", SoftApGetError(nRet));

	return 0;
}
//& purpose:  set and unset callback for softap security type changed.
/**
* @testcase                     ITs_softap_set_unset_security_type_changed_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set and unset callback for security type changed.
* @apicovered                   softap_set_security_type_changed_cb , softap_unset_security_type_changed_cb.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_unset_security_type_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE

	int nRet = 0;
	nRet = softap_set_security_type_changed_cb(g_hSoftapHandle, softapSecurityTypeChangedCb, NULL);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_security_type_changed_cb", SoftApGetError(nRet));

	nRet = softap_unset_security_type_changed_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_security_type_changed_cb", SoftApGetError(nRet));

	return 0;
}
//& purpose:  set and unset callback for softap ssid visibility changed.
/**
* @testcase                     ITs_softap_set_unset_ssid_visibility_changed_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set and unset callback for ssid visibility changed.
* @apicovered                   softap_set_ssid_visibility_changed_cb ,softap_unset_ssid_visibility_changed_cb.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_unset_ssid_visibility_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	nRet = softap_set_ssid_visibility_changed_cb(g_hSoftapHandle, softapSsidVisibilityChangedCb, NULL);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_ssid_visibility_changed_cb", SoftApGetError(nRet));

	nRet = softap_unset_ssid_visibility_changed_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_ssid_visibility_changed_cb", SoftApGetError(nRet));
	return 0;
}
//& purpose:  set and unset callback for softap passphrase changed.
/**
* @testcase                     ITs_softap_set_unset_passphrase_changed_cb_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  set and unset callback for passphrase changed.
* @apicovered                   softap_set_passphrase_changed_cb ,softap_unset_passphrase_changed_cb.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/
int ITs_softap_set_unset_passphrase_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	nRet = softap_set_passphrase_changed_cb(g_hSoftapHandle, softapPassphraseChangedCb,NULL);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_passphrase_changed_cb", SoftApGetError(nRet));

	nRet = softap_unset_passphrase_changed_cb(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_unset_passphrase_changed_cb", SoftApGetError(nRet));
	return 0;
}
//& purpose:  Set and get security type.
/**
* @testcase                     ITs_softap_set_get_security_type_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and unset security type.
* @apicovered                   softap_set_security_type ,softap_get_security_type.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/
int ITs_softap_set_get_security_type_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	softap_security_type_e eSecurityTypeSet[] = {SOFTAP_SECURITY_TYPE_NONE, SOFTAP_SECURITY_TYPE_WPA2_PSK, SOFTAP_SECURITY_TYPE_WPS};
	int nEnumSize = sizeof(eSecurityTypeSet) / sizeof(eSecurityTypeSet[0]);
	int enum_counter = 0;
	softap_security_type_e eSecurityTypeGet;

	for(enum_counter = 0; enum_counter < nEnumSize ; enum_counter++)
	{
		nRet = softap_set_security_type(g_hSoftapHandle, eSecurityTypeSet[enum_counter]);
		PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_security_type", SoftApGetError(nRet));


		nRet = softap_get_security_type(g_hSoftapHandle, &eSecurityTypeGet);
		PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_security_type", SoftApGetError(nRet));

		if(eSecurityTypeSet[enum_counter] != eSecurityTypeGet)
		{
			FPRINTF("\\n[Line : %d][%s] softap_get_security_type returned wrong value = %d , error returned = %s", __LINE__, API_NAMESPACE, eSecurityTypeGet, SoftApGetError(nRet));
			return 1;
		}
	}
	return 0;
}

//& purpose:  Set and get ssid type.
/**
* @testcase                     ITs_softap_set_get_ssid_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and unset security type.
* @apicovered                   softap_set_ssid ,softap_get_ssid.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_get_ssid_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
        const char sSid[] = "ABCDEFGH";
	nRet = softap_set_ssid(g_hSoftapHandle, sSid);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_ssid", SoftApGetError(nRet));

	char *sRetSid = NULL;
	nRet = softap_get_ssid(g_hSoftapHandle, &sRetSid);
	PRINT_RESULT_CLEANUP(SOFTAP_ERROR_NONE, nRet, "softap_get_ssid", SoftApGetError(nRet),FREE_MEMORY(sRetSid));

	if(strncmp(sSid, sRetSid, sizeof(sSid)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] softap_get_ssid Failed returned wrong value = %s, error returned = %s", __LINE__, API_NAMESPACE, sRetSid, SoftApGetError(nRet));
		FREE_MEMORY(sRetSid);
		return 1;
	}
	FREE_MEMORY(sRetSid);
	return 0;
}
//& purpose:  Set and get ssid visibility.
/**
* @testcase                     ITs_softap_set_get_ssid_visibility_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and get ssid visibility.
* @apicovered                   softap_set_ssid_visibility ,softap_get_ssid_visibility.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_get_ssid_visibility_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	bool bGetVisible = false;
        bool bSetVisible = true;
	nRet = softap_set_ssid_visibility(g_hSoftapHandle, bSetVisible);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_ssid_visibility", SoftApGetError(nRet));

	nRet = softap_get_ssid_visibility(g_hSoftapHandle, &bGetVisible);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_get_ssid_visibility", SoftApGetError(nRet));

        if(bSetVisible != bGetVisible)
	{
		FPRINTF("\\n[Line : %d][%s] softap_get_ssid_visibility Failed returned wrong value = %d, error returned = %s", __LINE__, API_NAMESPACE, bGetVisible, SoftApGetError(nRet));
                return 1;
	}
	return 0;
}
//& purpose: Set Get the passphrase for SoftAP.
/**
* @testcase                     ITs_softap_set_get_passphrase_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set Get the passphrase for SoftAP.
* @apicovered                   softap_set_passphrase ,softap_get_passphrase.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_get_passphrase_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	int nIndex = 0;
	char sPassphrase[PASSPHRASE_MAX + 1] = {0, };

	srand(time(NULL));
	for (nIndex = 0; nIndex < PASSPHRASE_MAX ; nIndex++)
	{
		sPassphrase[nIndex] = (char) (rand()%26) + 97;
	}
	nRet = softap_set_passphrase(g_hSoftapHandle, sPassphrase);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_passphrase", SoftApGetError(nRet));

	char *sRetPass = NULL;

	nRet = softap_get_passphrase(g_hSoftapHandle, &sRetPass);
	PRINT_RESULT_CLEANUP(SOFTAP_ERROR_NONE, nRet, "softap_get_passphrase", SoftApGetError(nRet),FREE_MEMORY(sRetPass));

	if(sRetPass)
	  FREE_MEMORY(sRetPass);
	return 0;
}
//& purpose:  Set and get vendor element.
/**
* @testcase                     ITs_softap_set_get_vendor_element_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and get ssid visibility.
* @apicovered                   softap_set_vendor_element, softap_get_vendor_element.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_get_vendor_element_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	const char* sVendor = "DD050016328000";

	nRet = softap_set_vendor_element(g_hSoftapHandle, sVendor);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_vendor_element", SoftApGetError(nRet));

	char * sRetVendor = NULL;
	nRet = softap_get_vendor_element(g_hSoftapHandle, &sRetVendor);
        PRINT_RESULT_CLEANUP(SOFTAP_ERROR_NONE, nRet, "softap_get_vendor_element", SoftApGetError(nRet),FREE_MEMORY(sRetVendor));

        if(sRetVendor)
	 FREE_MEMORY(sRetVendor);
	return 0;
}

//& purpose:  Set and get channel.
/**
* @testcase                     ITs_softap_set_get_channel_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and get channel.
* @apicovered                   softap_set_channel, softap_get_channel.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 softap_enable_dhcp must be enable.
* @postcondition                NA.
*/

int ITs_softap_set_get_channel_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	int nChannel = 10;

	nRet = softap_enable_dhcp(g_hSoftapHandle);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_enable_dhcp", SoftApGetError(nRet));

	nRet = softap_set_channel(g_hSoftapHandle, nChannel);
        PRINT_RESULT_CLEANUP(SOFTAP_ERROR_NONE, nRet, "softap_set_channel", SoftApGetError(nRet), softap_disable_dhcp(g_hSoftapHandle));

	int nRetChannel = 0;
	nRet = softap_get_channel(g_hSoftapHandle, &nRetChannel);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_get_channel", SoftApGetError(nRet));

	nRet = softap_disable_dhcp(g_hSoftapHandle);
        PRINT_RESULT_NORETURN(SOFTAP_ERROR_NONE, nRet, "softap_disable_dhcp", SoftApGetError(nRet));
	return 0;
}

//& purpose:  Set softap dhcp enable and diable.
/**
* @testcase                     ITs_softap_enable_disable_dhcp_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set dhcp enable and disable.
* @apicovered                   softap_enable_dhcp, softap_disable_dhcp,.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 softap_enable_dhcp must be enable.
* @postcondition                NA.
*/


int ITs_softap_enable_disable_dhcp_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet =0 ;

	nRet = softap_enable_dhcp(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_enable_dhcp", SoftApGetError(nRet));

	bool bIsEnable = false;
	nRet = softap_is_dhcp_enabled(g_hSoftapHandle, &bIsEnable);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_is_dhcp_enabled", SoftApGetError(nRet));

	if(!bIsEnable)
	{
		FPRINTF("\\n[Line : %d][%s] softap_enable_dhcp Failed ,dhcp status is = %d error returned = %s", __LINE__, API_NAMESPACE, bIsEnable, SoftApGetError(nRet));
                return 1;
	}

	nRet = softap_disable_dhcp(g_hSoftapHandle);

	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_disable_dhcp", SoftApGetError(nRet));

	nRet = softap_is_dhcp_enabled(g_hSoftapHandle, &bIsEnable);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_is_dhcp_enabled", SoftApGetError(nRet));

        if(bIsEnable)
        {
                FPRINTF("\\n[Line : %d][%s] softap_disable_dhcp Failed ,dhcp status is = %d error returned = %s", __LINE__, API_NAMESPACE, bIsEnable, SoftApGetError(nRet));
                return 1;
        }
	return 0;
}

//& purpose:  Get softap dhcp status.
/**
* @testcase                     ITs_softap_is_dhcp_enabled_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Get dhcp status.
* @apicovered                   softap_is_dhcp_enabled.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_is_dhcp_enabled_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	bool bIsEnable = false;

	nRet = softap_enable_dhcp(g_hSoftapHandle);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_enable_dhcp", SoftApGetError(nRet));

	nRet = softap_is_dhcp_enabled(g_hSoftapHandle, &bIsEnable);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_is_dhcp_enabled", SoftApGetError(nRet));
	if(!bIsEnable)
	{
		FPRINTF("\\n[Line : %d][%s] softap_is_dhcp_enabled returned wrong status ,dhcp status is = %d error returned = %s", __LINE__, API_NAMESPACE, bIsEnable, SoftApGetError(nRet));
                return 1;
	}
	nRet = softap_disable_dhcp(g_hSoftapHandle);
        PRINT_RESULT_NORETURN(SOFTAP_ERROR_NONE, nRet, "softap_disable_dhcp", SoftApGetError(nRet));
	return 0;
}
//& purpose:  Set dhcp enable in range.
/**
* @testcase                     ITs_softap_is_dhcp_enabled_p
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set dhcp enable in range.
* @apicovered                   softap_enable_dhcp_with_range.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_enable_dhcp_with_range_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	const char *pszStartRange = "192.168.1.3";
	const char *pszEndRange = "192.168.1.200";

	nRet = softap_enable_dhcp_with_range(g_hSoftapHandle, pszStartRange, pszEndRange);
        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_is_dhcp_enabled", SoftApGetError(nRet));

	nRet = softap_disable_dhcp(g_hSoftapHandle);
	PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_disable_dhcp", SoftApGetError(nRet));

	return 0;
}
//& purpose:  Set and get softap mode.
/**
* @testcase                     ITs_softap_set_get_mode_p.
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(a.pandia1)
* @type                         auto
* @since_tizen                  Tizen 5.0
* @description                  Set and get softap mode.
* @apicovered                   softap_set_mode, softap_get_mode.
* @passcase                     if api call made successful.
* @failcase                     if api call fails.
* @precondition                 NA.
* @postcondition                NA.
*/

int ITs_softap_set_get_mode_p(void)
{
	START_TEST_CHECK_INITIALIZE
	int nRet = 0;
	softap_wireless_mode_e eSetMode[] =  {SOFTAP_WIRELESS_MODE_B, SOFTAP_WIRELESS_MODE_G, SOFTAP_WIRELESS_MODE_A, SOFTAP_WIRELESS_MODE_AD};
	int nEnumSize = sizeof(eSetMode) / sizeof(eSetMode[0]);
	int enum_counter = 0;
	softap_wireless_mode_e eGetMode;
	for(int enum_counter = 0; enum_counter < nEnumSize; enum_counter++)
	{
		nRet = softap_set_mode(g_hSoftapHandle, eSetMode[enum_counter]);
	        PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_set_mode", SoftApGetError(nRet));

		nRet = softap_get_mode(g_hSoftapHandle, &eGetMode);
		PRINT_RESULT(SOFTAP_ERROR_NONE, nRet, "softap_get_mode", SoftApGetError(nRet));
	}
	return 0;
}
