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
#include "ITs-nfc-common.h"

/** @addtogroup itc-nfc
* @ingroup		itc
* @{
*/

/** @addtogroup	itc-nfc-testcases
* @brief 		Integration testcases for module nfc
* @ingroup		itc-nfc
* @{
*/


/** @} */ //end of itc-nfc
/** @} */ //end of itc-nfc-testcases

//& set: NFC

static GMainLoop *g_pNFCMainLoop;
bool g_bNFCManagerCallback;
nfc_se_h g_pstNfcSEHandle = NULL;
unsigned char *g_pszHCEData = NULL;
unsigned int g_nHCEDataLen = 0;
//Callbacks

/**
* @function            NFCNdefDiscoveredCB
* @description         Callback function which is invoked when an NDEF Message is discovered
* @parameter           nfc_ndef_message_h message, void *user_data
* @return              void
*/
static void NFCNdefDiscoveredCB(nfc_ndef_message_h message, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bNFCManagerCallback = true;
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}

/**
* @function            NFCSeEventCB
* @description         Callback function which is invoked for receiving Secure Element event
* @parameter           nfc_se_event_e event, void *user_data
* @return              void
*/
static void NFCSeEventCB(nfc_se_event_e event, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function            NFCActivationChangedCB
* @description         Callback function which is invoked when NFC activation state has changed
* @parameter           bool activated, void *user_data
* @return              void
*/
static void NFCActivationChangedCB(bool activated, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function            NFCSeTransactionEventCB
* @description         Callback function which is invoked when receiving Secure Element transaction event data
* @parameter           nfc_se_type_e se_type, unsigned char *aid, int aid_size, unsigned char *param, int param_size, void *user_data
* @return              void
*/
static void NFCSeTransactionEventCB(nfc_se_type_e se_type, unsigned char *aid, int aid_size, unsigned char *param, int param_size, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bNFCManagerCallback = true;
	switch ( se_type )
	{
	case NFC_SE_TYPE_DISABLE:
		FPRINTF("[Line : %d][%s] se_type:  NFC_SE_TYPE_DISABLE\\n", __LINE__, API_NAMESPACE);
		break;

	case NFC_SE_TYPE_ESE:
		FPRINTF("[Line : %d][%s] se_type:  NFC_SE_TYPE_ESE\\n", __LINE__, API_NAMESPACE);
		break;

	case NFC_SE_TYPE_UICC:
		FPRINTF("[Line : %d][%s] se_type:  NFC_SE_TYPE_UICC\\n", __LINE__, API_NAMESPACE);
		break;

	default:
		FPRINTF("[Line : %d][%s] No Valid type.\\n", __LINE__, API_NAMESPACE);
		break;
	}
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}

/**
* @function            NFCTagDiscoveredCB
* @description         Callback function which is invoked when NFC tag appears or disappears
* @parameter           nfc_discovered_type_e type, nfc_tag_h tag, void *user_data
* @return              void
*/
static void NFCTagDiscoveredCB(nfc_discovered_type_e type, nfc_tag_h tag, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bNFCManagerCallback = true;
	switch ( type )
	{
	case NFC_DISCOVERED_TYPE_ATTACHED:
		FPRINTF("[Line : %d][%s] type:  NFC_DISCOVERED_TYPE_ATTACHED\\n", __LINE__, API_NAMESPACE);
		break;

	case NFC_DISCOVERED_TYPE_DETACHED:
		FPRINTF("[Line : %d][%s] type:  NFC_DISCOVERED_TYPE_DETACHED\\n", __LINE__, API_NAMESPACE);
		break;
	}
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}

/**
* @function            NFCP2PTargetDiscoveredCB
* @description         Callback function which is invoked when NFC peer-to-peer target appeared or disappeared
* @parameter           nfc_discovered_type_e type, nfc_p2p_target_h target, void *user_data
* @return              void
*/
static void NFCP2PTargetDiscoveredCB(nfc_discovered_type_e type, nfc_p2p_target_h target, void *user_data)
{
	FPRINTF("[Line : %d][%s] callback invoked\\n", __LINE__, API_NAMESPACE);
	g_bNFCManagerCallback = true;
	switch ( type )
	{
	case NFC_DISCOVERED_TYPE_ATTACHED:
		FPRINTF("[Line : %d][%s] type:  NFC_DISCOVERED_TYPE_ATTACHED\\n", __LINE__, API_NAMESPACE);
		break;

	case NFC_DISCOVERED_TYPE_DETACHED:
		FPRINTF("[Line : %d][%s] type:  NFC_DISCOVERED_TYPE_DETACHED\\n", __LINE__, API_NAMESPACE);
		break;
	}
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}


/**
* @function            NfcHCEEventCallback
* @description         Callback function which is invoked for receiving Secure Element event
* @parameter           handle : nfc handle, event : HCE event, apdu : bytes array of apdu command data, apdu_len : size of apdu command, user_data : user data
* @return              void
*/
static void NfcHCEEventCallback (nfc_se_h handle, nfc_hce_event_type_e event, unsigned char *apdu, unsigned int apdu_len, void *user_data)
{
	FPRINTF( "\\n [Line : %d] [%s] NfcHCEEventCallback callback invoked \\n", __LINE__,API_NAMESPACE);
	g_pstNfcSEHandle = handle;
	g_nHCEDataLen = apdu_len;
	g_pszHCEData = apdu;
}


/**
* @function 		ITs_nfc_manager_startup
* @description	 	Called before each test, Check whether NFC is supported or not and initialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_manager_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_NFC_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_TESTNFCLIENT_APPID);
	g_bNFCNotSupported = false;
	g_bMismatch = false;
	IS_FEATURE_SUPPORTED(NFC_FEATURE, g_bIsSupportedNFC, API_NAMESPACE);
	if ( !g_bIsSupportedNFC )
	{
		if ( !nfc_manager_is_supported() )
		{
			g_bNFCNotSupported = true;
			return;
		}
		g_bMismatch = true;
		return;
	}

	int nRet = nfc_manager_initialize();
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_manager_initialize failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
		g_bNFCTestPrecondition = false;
		return;
	}
	FPRINTF("[Line : %d][%s] nfc_manager_initialize successfully\\n", __LINE__, API_NAMESPACE);
	g_bNFCTestPrecondition = true;

	return;
}

/**
* @function 		ITs_nfc_manager_cleanup
* @description	 	Called after each test, deinitialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_NFC_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bNFCTestPrecondition )
	{
		int nRet = nfc_manager_deinitialize();
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_manager_deinitialize failed in cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
		}
	}
	return;
}

//& purpose: Check if NFC is supported.
//& type: auto
/**
* @testcase 				ITc_nfc_is_supported_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Check if NFC is supported
* @scenario					Check if NFC is supported
* @apicovered				nfc_manager_is_supported
* @passcase					Always pass if API does not crash, just prints if NFC is supported or not.
* @failcase					If nfc_manager_is_supported crashes or throws exception.
* @precondition				N/A
* @postcondition			N/A
*/
int ITc_nfc_is_supported_p(void)
{
	START_TEST;

	bool bRetVal = nfc_manager_is_supported(); // Target API
	if ( bRetVal )
	{
		FPRINTF("[Line : %d][%s] NFC is supported on the device\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] NFC is not supported on the device\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}

//& purpose: To initialize and deinitialize the NFC Manager
//& type : auto
/**
* @testcase				    ITc_nfc_manager_initialize_deinitialize_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To initialize and deinitialize the NFC Manager
* @scenario				    Initialize the NFC Manager\n
* 							Deinitialize the NFC Manager
* @apicovered				nfc_manager_initialize, nfc_manager_deinitialize
* @passcase					When nfc_manager_initialize and nfc_manager_deinitialize are successful
* @failcase					When nfc_manager_initialize or nfc_manager_deinitialize fails
* @precondition				N/A
* @postcondition			N/A
*/
int ITc_nfc_manager_initialize_deinitialize_p(void)
{
	START_TEST;

	int nRet = nfc_manager_deinitialize();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_deinitialize", NFCGetError(nRet));
	sleep(SHORT_DELAY);

	nRet = nfc_manager_initialize(); // Target API
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_initialize", NFCGetError(nRet));
	sleep(SHORT_DELAY);

	nRet = nfc_manager_deinitialize(); // Target API
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_deinitialize", NFCGetError(nRet));
	sleep(SHORT_DELAY);

	nRet = nfc_manager_initialize();
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_manager_initialize", NFCGetError(nRet));

	return 0;
}

//& purpose: Check if NFC is activated.
//& type: auto
/**
* @testcase 				ITc_nfc_is_activated_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Check if NFC is activated
* @scenario					Check if NFC is activated
* @apicovered				nfc_manager_is_activated
* @passcase					Always pass if API does not crash, just prints if NFC is activated or not.
* @failcase					If nfc_manager_is_supported crashes or throws exception.
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_is_activated_p(void)
{
	START_TEST;

	bool bRetVal = nfc_manager_is_activated(); // Target API
	if ( bRetVal )
	{
		FPRINTF("[Line : %d][%s] NFC is activated\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] NFC is not activated\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}

//& purpose: To set and get the state of the system handler.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_system_handler_enable_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To set and get the state of the system handler
* @scenario				    Set the state of the system handler\n
*                           Get the state of the system handler
* @apicovered				nfc_manager_set_system_handler_enable, nfc_manager_is_system_handler_enabled
* @passcase					When nfc_manager_set_system_handler_enable is successful and get state matches the state which was set
* @failcase					When nfc_manager_set_system_handler_enable fails or get state mismatches the state which was set
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_system_handler_enable_p(void)
{
	START_TEST;

	bool bEnable = true;
	int nRet = nfc_manager_set_system_handler_enable(bEnable); // Target API 
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_system_handler_enable", NFCGetError(nRet));

	bool bRetVal = nfc_manager_is_system_handler_enabled(); // Target API
	if ( bRetVal )
	{
		FPRINTF("[Line : %d][%s] state of system handler is enable\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] state of system handler is not enable\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose: To register and unregister the NDEF discovery callback function.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_ndef_discovered_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregisters the NDEF discovery callback function
* @scenario				    Register the NDEF discovery callback function\n
* 							Unregister the NDEF discovery callback function
* @apicovered				nfc_manager_set_ndef_discovered_cb, nfc_manager_unset_ndef_discovered_cb
* @passcase					When nfc_manager_set_ndef_discovered_cb is successful
* @failcase					When nfc_manager_set_ndef_discovered_cb fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_ndef_discovered_p(void)
{
	START_TEST;

	int nRet = nfc_manager_set_ndef_discovered_cb(NFCNdefDiscoveredCB, NULL); // Target API
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_ndef_discovered_cb", NFCGetError(nRet));

	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	sleep(SHORT_DELAY);

	nfc_manager_unset_ndef_discovered_cb(); // Target API
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_ndef_discovered_cb", NFCGetError(nRet));

	return 0;
}

//& purpose: To set and get filter of target types.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_get_tag_filter_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To set and get filter of target types
* @scenario				    Set filter of target types\n
*                           Get the current filter status
* @apicovered				nfc_manager_set_tag_filter, nfc_manager_get_tag_filter
* @passcase					When current filter status is matched with set filter of target type
* @failcase					When current filter status is mismatched with set filter of target type
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_get_tag_filter_p(void)
{
	START_TEST;

    bool bIsSupportedNFCTAG = false;
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsSupportedNFCTAG, API_NAMESPACE);

	nfc_tag_filter_e nRet = 0;
	nfc_tag_filter_e eConfig[] = {
		NFC_TAG_FILTER_ALL_DISABLE,
		NFC_TAG_FILTER_ISO14443A_ENABLE,
		NFC_TAG_FILTER_ISO14443B_ENABLE,
		NFC_TAG_FILTER_ISO15693_ENABLE,
		NFC_TAG_FILTER_FELICA_ENABLE,
		NFC_TAG_FILTER_JEWEL_ENABLE,
		NFC_TAG_FILTER_IP_ENABLE,
		NFC_TAG_FILTER_ALL_ENABLE
	};
	int nEnumSize = sizeof(eConfig) / sizeof(eConfig[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		nfc_manager_set_tag_filter(eConfig[nEnumCounter]);
		int ret = get_last_result();
		if (!bIsSupportedNFCTAG)
		{
			if (ret != NFC_ERROR_NOT_SUPPORTED)
			{
				FPRINTF( "\\n [Line : %d] [%s] nfc_manager_set_tag_filter failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , NFCGetError(nRet));
				return 1;
			}
			FPRINTF( "\\n [Line : %d] [%s] nfc_manager_set_tag_filter failed, NFC_TAG_FEATURE feature is not supported,\\n ", __LINE__, API_NAMESPACE);
			return 0;
		}

		PRINT_RESULT(NFC_ERROR_NONE, ret, "nfc_manager_set_tag_filter", NFCGetError(ret));

		sleep(SHORT_DELAY);
		nRet = nfc_manager_get_tag_filter();
		if ( eConfig[nEnumCounter] != NFC_TAG_FILTER_ALL_ENABLE )
		{
			if ( nRet != eConfig[nEnumCounter] )
			{
				FPRINTF("[Line : %d][%s] nfc_manager_get_tag_filter is mismatched for enum: %s,\\n", __LINE__, API_NAMESPACE, NFCTagFilterEnumString(eConfig[nEnumCounter]));
				return 1;
			}
		}
		else
		{
			if ( nRet == 0 )
			{
				FPRINTF("[Line : %d][%s] nfc_manager_get_tag_filter is mismatched for enum: %s,\\n", __LINE__, API_NAMESPACE, NFCTagFilterEnumString(eConfig[nEnumCounter]));
				return 1;
			}
		}
	}

	return 0;
}

//& purpose: To register and unregister the Secure Element event callback function.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_se_event_cb_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregister the Secure Element event callback function
* @scenario				    Register Secure Element event callback function\n
* 							Unregister Secure Element event callback function
* @apicovered				nfc_manager_set_se_event_cb, nfc_manager_unset_se_event_cb
* @passcase					When nfc_manager_set_se_event_cb is successful
* @failcase					When nfc_manager_set_se_event_cb is not successful
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_se_event_cb_p(void)
{
	START_TEST_CARD_EMUL_CHECK;
	

	bool bIsSupportedNFCEmulation = false;
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsSupportedNFCEmulation, API_NAMESPACE);
	
	int nRet = nfc_manager_set_se_event_cb(NFCSeEventCB, NULL);
	if ( !bIsSupportedNFCEmulation )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] nfc_manager_set_se_event_cb API call returned mismatch for unsupported NFC card emulation feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_manager_set_se_event_cb API call correctly returned for unsupported NFC feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 0;
		}
	}
	else
	{
		PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_se_event_cb", NFCGetError(nRet));
	}
	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	sleep(SHORT_DELAY);

	nfc_manager_unset_se_event_cb();
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_se_event_cb", NFCGetError(nRet));

	return 0;
}

//& purpose: To set and unset the NFC Activation state changed callback.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_activation_changed_cb_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To set and unset the NFC Activation state changed callback
* @scenario				    Set and unset the NFC Activation state changed callback\n
* 							Unset the NFC Activation state changed callback
* @apicovered				nfc_manager_set_activation_changed_cb, nfc_manager_unset_activation_changed_cb
* @passcase					When nfc_manager_set_activation_changed_cb is successful
* @failcase					When nfc_manager_set_activation_changed_cb is not successful
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_activation_changed_cb_p(void)
{
	START_TEST;

	int nRet = nfc_manager_set_activation_changed_cb(NFCActivationChangedCB, NULL);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_activation_changed_cb", NFCGetError(nRet));

	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	sleep(SHORT_DELAY);

	nfc_manager_unset_activation_changed_cb();
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_activation_changed_cb", NFCGetError(nRet));

	return 0;
}

//& purpose: To register and unregister callback function for receiving Secure Element transaction event(NFC_SE_EVENT_TRANSACTION) data.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_se_transaction_event_cb_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregister callback function for receiving Secure Element transaction event(NFC_SE_EVENT_TRANSACTION) data
* @scenario				    Register callback function for receiving Secure Element transaction event(NFC_SE_EVENT_TRANSACTION) data\n
* 							Unregister callback function for receiving Secure Element transaction event(NFC_SE_EVENT_TRANSACTION) data
* @apicovered				nfc_manager_set_se_transaction_event_cb, nfc_manager_unset_se_transaction_event_cb
* @passcase					When nfc_manager_set_se_transaction_event_cb is successful
* @failcase					When nfc_manager_set_se_transaction_event_cb fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_se_transaction_event_cb_p(void)
{
	START_TEST_CARD_EMUL_CHECK;

	bool bIsSupportedNFCEmulation = false;
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsSupportedNFCEmulation, API_NAMESPACE);
	
	nfc_se_type_e eSeType[] = {NFC_SE_TYPE_ESE, NFC_SE_TYPE_UICC};
	int nEnumSize = sizeof( eSeType ) / sizeof(eSeType[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		int nRet = nfc_manager_set_se_transaction_event_cb(eSeType[nEnumCounter], NFCSeTransactionEventCB, NULL);
		if ( !bIsSupportedNFCEmulation )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] nfc_manager_set_se_transaction_event_cb API call returned mismatch for unsupported NFC card emulation feature, error returned = %s\\n",
					__LINE__, API_NAMESPACE, NFCGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] nfc_manager_set_se_transaction_event_cb API call correctly returned for unsupported NFC feature, error returned = %s\\n",
					__LINE__, API_NAMESPACE, NFCGetError(nRet));
				return 0;
			}
		}
		else if( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_manager_set_se_transaction_event_cb failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCSeTypeEnumString(eSeType[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}


		/** There is manual operation required for callback invocation. Callback cannot be tested **/
		sleep(SHORT_DELAY);

		nfc_manager_unset_se_transaction_event_cb(eSeType[nEnumCounter]);
		nRet = get_last_result();
		PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_se_transaction_event_cb", NFCGetError(nRet));
	}

	return 0;
}

//& purpose: To register and unregister callback function for receiving notification about tag discovery.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_tag_discovered_cb_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregister callback function for receiving notification about tag discovery
* @scenario				    Register callback function for receiving notification about tag discovery\n
*                           Set filter of target types\n
* 							Unregister callback function for receiving notification about tag discovery
* @apicovered				nfc_manager_set_tag_discovered_cb, nfc_manager_unset_tag_discovered_cb
* @passcase					When nfc_manager_set_tag_discovered_cb is successful
* @failcase					When nfc_manager_set_tag_discovered_cb fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_tag_discovered_cb_p(void)
{
	START_TEST;
	bool bIsSupportedNFCTAG = false;
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsSupportedNFCTAG, API_NAMESPACE);

	int nRet = nfc_manager_set_tag_discovered_cb(NFCTagDiscoveredCB, NULL);
	if (!bIsSupportedNFCTAG)
	{
		if (nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_manager_set_tag_discovered_cb failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , NFCGetError(nRet));
			return 1;
		}
		return 0;
	}
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_tag_discovered_cb", NFCGetError(nRet));

	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	sleep(SHORT_DELAY);

	nfc_manager_unset_tag_discovered_cb();
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_tag_discovered_cb", NFCGetError(nRet));

	return 0;
}

//& purpose: To register and unregister callback function for receiving NFC peer-to-peer target discovered notification.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_p2p_target_discovered_cb
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregister callback function for receiving NFC peer-to-peer target discovered notification
* @scenario				    Register callback function for receiving NFC peer-to-peer target discovered notification\n
*                           Set filter of target types\n
* 							Unregister callback function for receiving NFC peer-to-peer target discovered notification
* @apicovered				nfc_manager_set_p2p_target_discovered_cb, nfc_manager_unset_p2p_target_discovered_cb
* @passcase				    When nfc_manager_set_p2p_target_discovered_cb is successful
* @failcase					When nfc_manager_set_p2p_target_discovered_cb fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_p2p_target_discovered_cb(void)
{
	START_TEST;
	bool bIsSupportedNFCP2P = false;
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsSupportedNFCP2P, API_NAMESPACE);

	int nRet = nfc_manager_set_p2p_target_discovered_cb(NFCP2PTargetDiscoveredCB, NULL);
	if (!bIsSupportedNFCP2P)
	{
		 if (nRet != NFC_ERROR_NOT_SUPPORTED)
		 {
			 FPRINTF( "\\n [Line : %d] [%s] nfc_manager_set_p2p_target_discovered_cb failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , NFCGetError(nRet));
			 return 1;
		 }
		 return 0;
	}
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_p2p_target_discovered_cb", NFCGetError(nRet));

	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	sleep(SHORT_DELAY);

	nfc_manager_unset_p2p_target_discovered_cb();
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_p2p_target_discovered_cb", NFCGetError(nRet));

	return 0;
}

//& purpose: To register and unregister callback function for receiving HCE(Host Card Emulation) event
//& type : auto
/**
* @testcase				    ITc_nfc_manager_set_unset_hce_event_cb_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To register and unregister callback function for receiving HCE(Host Card Emulation) event
* @scenario				    register callback function for receiving HCE(Host Card Emulation) event\n
* 							Unregister callback function for receiving HCE(Host Card Emulation) event
* @apicovered				nfc_manager_set_hce_event_cb, nfc_manager_unset_hce_event_cb
* @passcase				    When nfc_manager_set_hce_event_cb is successful
* @failcase					When nfc_manager_set_hce_event_cb fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_set_unset_hce_event_cb_p(void)
{
    START_TEST;
	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	int nRet = nfc_manager_set_hce_event_cb(NfcHCEEventCallback, NULL);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_manager_set_hce_event_cb failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , NFCGetError(nRet));
			return 1;
		}

		return 0;
	}

	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_set_hce_event_cb", NFCGetError(nRet));

	/** There is manual operation required for callback invocation. Callback cannot be tested **/
	usleep(MICROSECONDS_PER_SECOND);

	nfc_manager_unset_hce_event_cb();
	nRet = get_last_result();
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_unset_hce_event_cb", NFCGetError(nRet));

	return 0;
}