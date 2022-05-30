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

//& set: NFC

static GMainLoop *g_pNFCMainLoop;

/**
* @function            NFCSnepEventCB
* @description         Called when SNEP event is raised.
* @parameter           nfc_p2p_snep_h handle, nfc_snep_event_e event, nfc_error_e result, nfc_ndef_message_h msg, void *user_data
* @return              void
*/
static void NFCSnepEventCB(nfc_p2p_snep_h handle, nfc_snep_event_e event, nfc_error_e result, nfc_ndef_message_h msg, void *user_data)
{
	FPRINTF("[Line : %d][%s] NFC snep event callback invoked\\n", __LINE__, API_NAMESPACE);
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}

/**
* @function 		ITs_nfc_snep_startup
* @description	 	Called before each test, Check whether NFC is supported or not and initialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_snep_startup(void)
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
* @function 		ITs_nfc_snep_cleanup
* @description	 	Called after each test, deinitialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_snep_cleanup(void)
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

/** @addtogroup	itc-nfc-testcases
* @brief 		Integration testcases for module nfc
* @ingroup		itc-nfc
* @{
*/

//& purpose: Register/Unregister peer-to-peer server using SNEP protocol.
//& type : auto
/**
* @testcase				    ITc_nfc_snep_register_unregister_server_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    Register/Unregister peer-to-peer server using SNEP protocol.
* @scenario				    Register the peer-to-peer server using SNEP protocol\n
* 							Unregister the peer-to-peer server using SNEP protocol
* @apicovered				nfc_snep_register_server, nfc_snep_unregister_server
* @passcase					When nfc_snep_register_server and nfc_snep_unregister_server are successful
* @failcase					When nfc_snep_register_server or nfc_snep_unregister_server fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_snep_register_unregister_server_p(void)
{
	START_TEST;
    bool bIsSupportedNFCP2P = false;
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsSupportedNFCP2P, API_NAMESPACE);

	int nRet = nfc_snep_register_server(SERVICE_ACCESS_NAME, SERVICE_ACCESS_POINT, NFCSnepEventCB, NULL); // Target API
	if (!bIsSupportedNFCP2P)
	{
		if (nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_snep_register_server failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__, API_NAMESPACE , NFCGetError(nRet));
			return 1;
		}
		return 0;
	}

	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_snep_register_server", NFCGetError(nRet));

	sleep(SHORT_DELAY);
	nRet = nfc_snep_unregister_server(SERVICE_ACCESS_NAME, SERVICE_ACCESS_POINT); // Target API
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_snep_unregister_server", NFCGetError(nRet));

	return 0;
}

/** @} */ //end of itc-nfc
/** @} */ //end of itc-nfc-testcases