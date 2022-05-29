#include "CTs-platform-permission-common.h"
#include <app.h>

#define NFC_HCE_FEATURE  			"http://tizen.org/feature/network.nfc.card_emulation.hce"
#define NFC_CARD_EMULATION_FEATURE  "http://tizen.org/feature/network.nfc.card_emulation"
#define NFC_P2P_FEATURE             "http://tizen.org/feature/network.nfc.p2p"
#define NFC_TAG_FEATURE             "http://tizen.org/feature/network.nfc.tag"
#define NFC_CARD_EMULATION_UICC_FEATURE             "http://tizen.org/feature/network.secure_element.uicc"
#define NFC_CARD_EMULATION_ESE_FEATURE              "http://tizen.org/feature/network.secure_element.ese"
#define SHORT_DELAY					 1
#define SERVICE_ACCESS_NAME			"urn:nfc:sn:snep"
#define SERVICE_ACCESS_POINT		4
#define SEAPPIDNAME					"org.tizen.testnfclient"
#define SEAPPIDHEXVALUE				"6f72672e74697a656e2e746573746e66636c69656e74" // Hex value of org.tizen.testnfclient
#define MICROSECONDS_PER_SECOND		1000000
#define COUNTER 					30

nfc_se_h g_pstNfcSEHandle = NULL;
unsigned char *g_pszHCEData = NULL;
unsigned int g_nHCEDataLen = 0;

GMainLoop *g_pNFCMainLoop;
app_control_h g_app_control_handler = NULL;
nfc_ndef_message_h g_pstNfcNdepMessageHandle = NULL;
nfc_p2p_snep_h g_pstNfp2pHandle = NULL;

/**
* @function            NFCSnepEventCB
* @description         Called when SNEP event is raised.
* @parameter           nfc_p2p_snep_h handle, nfc_snep_event_e event, nfc_error_e result, nfc_ndef_message_h msg, void *user_data
* @return              void
*/
void NFCSnepEventCB(nfc_p2p_snep_h handle, nfc_snep_event_e event, nfc_error_e result, nfc_ndef_message_h msg, void *user_data)
{
	FPRINTF("[Line : %d][%s] NFC snep event callback invoked\\n", __LINE__, API_NAMESPACE);
	
	g_pstNfcNdepMessageHandle = msg;
	g_pstNfp2pHandle = handle;
	
	if ( g_pNFCMainLoop )
	{
		g_main_loop_quit(g_pNFCMainLoop);
	}
}
/**
* @function 		NfcSERegisteredAidCallback
* @description	 	callback function Secure Element
* @parameter		se_type : type of Secure Element , aid : Application Id, read_only : Secure Element read mode, user_data = user data
* @return 			NA
*/
void NfcSERegisteredAidCallback (nfc_se_type_e se_type,	const char *aid, bool read_only, void *user_data)
{
	FPRINTF("[Line : %d][%s] Reached NfcSERegisteredAidCallback \\n", __LINE__, API_NAMESPACE);
	return;
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
* @function 		NfcTagReadCompletedCallback
* @description	 	callback function 
* @parameter		nfc_error_e , nfc_ndef_message_h , user_data = user data
* @return 			NA
*/
void NfcTagReadCompletedCallback(nfc_error_e result, nfc_ndef_message_h message, void *user_data)
{
	FPRINTF("[Line : %d][%s] Reached NfcTagReadCompletedCallback \\n", __LINE__, API_NAMESPACE);
	return;
}
/**
* @function 		NfcCompletedCallback
* @description	 	callback function 
* @parameter		nfc_error_e , user_data = user data
*/
void NfcCompletedCallback(nfc_error_e result, void *user_data)
{
	FPRINTF("[Line : %d][%s] Reached NfcCompletedCallback \\n", __LINE__, API_NAMESPACE);
	return;
}
/**
* @function 		NfcTagCompletedCallback
* @description	 	callback function 
* @parameter		nfc_error_e , user_data = user data
*/
void NfcTagCompletedCallback(nfc_error_e result, unsigned char *buffer, int buffer_size, void *user_data)
{
	FPRINTF("[Line : %d][%s] Reached NfcTagCompletedCallback \\n", __LINE__, API_NAMESPACE);
	return;
}
/**
* @function 		TerminateApp
* @description	 	terminates application launched for sending message
* @parameter		NA
* @return 			NA
*/
void TerminateApp()
{
	app_control_send_terminate_request(g_app_control_handler);
	app_control_destroy(g_app_control_handler);
}

/**
* @function         CTs_platform_permission_nfc_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_nfc_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	int nRet = nfc_manager_initialize();
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_manager_initialize failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, NfcPrintErrorInfo(nRet));
		return;
	}
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_nfc_startup\\n", __LINE__, API_NAMESPACE);
#endif
   return;
}

/**
* @function         CTs_platform_permission_nfc_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_nfc_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_nfc_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
    int nRet = nfc_manager_deinitialize();
	if ( nRet != NFC_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] nfc_manager_initialize failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, NfcPrintErrorInfo(nRet));
		return;
	}
    return;
}
//& purpose: Checking tizen.org/privilege/nfc privilege
//& type: auto
/**
* @testcase			CTc_nfc_Privilege_Nfc_HandlerEnable
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario
* 					Set the state of the system handler\n
* @apicovered		nfc_manager_set_system_handler_enable
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NFC Manager must be initialize
* @postcondition	Releases all resources of the NFC Manager
*/
int CTc_nfc_Privilege_Nfc_HandlerEnable(void)
{
	START_TEST;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;

	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature s not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_set_system_handler_enable(true);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_set_system_handler_enable", NfcPrintErrorInfo(nRet));

	return 0;
}
//& purpose: Checking tizen.org/privilege/nfc privilege
//& type: auto
/**
* @testcase			CTc_nfc_Privilege_Nfc_IsHandlerEnabled
* @since_tizen		2.3
* @author			SRID(manu.tiwari)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @scenario
* 					check the state of the system handler\n
* @apicovered		nfc_manager_is_system_handler_enabled
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NFC Manager must be initialize
* @postcondition	Releases all resources of the NFC Manager
*/
int CTc_nfc_Privilege_Nfc_IsHandlerEnabled(void)
{
	START_TEST;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;

	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature s not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_is_system_handler_enabled();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_is_system_handler_enabled", NfcPrintErrorInfo(nRet));

	return 0;
}
//& purpose: checking http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_SetHceEvent
* @since_tizen 				2.3.1
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    To register and unregister callback function for receiving HCE(Host Card Emulation) event
* @scenario				    register callback function for receiving HCE(Host Card Emulation) event\n
* 							Unregister callback function for receiving HCE(Host Card Emulation) event
* @apicovered				nfc_manager_set_hce_event_cb, nfc_manager_unset_hce_event_cb
* @passcase				    If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_SetHceEvent(void)
{
    START_TEST;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;

	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature s not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_set_hce_event_cb(NfcHCEEventCallback, NULL);
	if(nRet == NFC_ERROR_NONE)
	{
		nfc_manager_unset_hce_event_cb();
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_set_hce_event_cb", NfcPrintErrorInfo(nRet));
	return 0;
}
//& purpose:checking http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_GetSeType
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    To get the card emulation Secure Element type
* @scenario				    Get the card emulation Secure Element type\n
*                           Check whether output value is valid or not
* @apicovered			    nfc_manager_get_se_type
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/

int CTc_Nfc_Privilege_NfcCardEmulation_GetSeType(void)
{
	START_TEST;

	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;

	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature s not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	nfc_se_type_e eGeType = -1;
	int nRet = nfc_manager_get_se_type(&eGeType);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_get_se_type", NfcPrintErrorInfo(nRet));

	return 0;
}
//& purpose:checking http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_SetSeType
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    To Set the card emulation Secure Element type
* @scenario				    Set the card emulation Secure Element type\n
*                           Check whether output value is valid or not
* @apicovered				nfc_manager_set_se_type
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/

int CTc_Nfc_Privilege_NfcCardEmulation_SetSeType(void)
{
	START_TEST;

	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;

	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Feature s not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_set_se_type(NFC_SE_TYPE_ESE);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_set_se_type", NfcPrintErrorInfo(nRet));

	return 0;
}
//& purpose: http://tizen.org/privilege/nfc
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_Nfc_RegisterUnregisterServer
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    To Set the card emulation Secure Element type
* @scenario				    Register the peer-to-peer server using SNEP protocol\n
* 							Unregister the peer-to-peer server using SNEP protocol
* @apicovered				nfc_snep_register_server, nfc_snep_unregister_server
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_Nfc_RegisterUnregisterServer(void)
{
	START_TEST;
	
    bool bIsSupportedNFCP2P = false;
	bool bIsNfcSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsSupportedNFCP2P, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	bIsSupported = bIsSupportedNFCP2P && bIsNfcSupported;
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_snep_register_server(SERVICE_ACCESS_NAME, SERVICE_ACCESS_POINT, NFCSnepEventCB, NULL); // Target API
	sleep(SHORT_DELAY);
	if(nRet == NFC_ERROR_NONE)
	{
		nfc_snep_unregister_server(SERVICE_ACCESS_NAME, SERVICE_ACCESS_POINT);
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_snep_register_server", NfcPrintErrorInfo(nRet));
	
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_CardEmulationMode
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Get the current card emulation mode.
* @scenario				    Get the current card emulation mode.
* @apicovered				nfc_se_get_card_emulation_mode
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_CardEmulationMode(void)
{
	START_TEST;
	
	nfc_se_card_emulation_mode_type_e type = NFC_SE_CARD_EMULATION_MODE_ON;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_se_get_card_emulation_mode(&type);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_get_card_emulation_mode", NfcPrintErrorInfo(nRet));
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_RegisterAid
* @since_tizen 				2.3.1
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for specific AID
* @scenario				    Check whether an application to call this api is currently the activated handler for specific AID
* @apicovered				nfc_se_register_aid,nfc_se_unregister_aid
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_RegisterAid(void)
{
	START_TEST;
	
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;

	int nRet = nfc_se_register_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	if(nRet == NFC_ERROR_NONE)
	{
		nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
		TerminateApp();
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_register_aid", NfcPrintErrorInfo(nRet), TerminateApp());
	
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_ActivatedHandleForAid
* @since_tizen 				2.3.1
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for specific AID
* @scenario				    Check whether an application to call this api is currently the activated handler for specific AID
* @apicovered				nfc_se_is_activated_handler_for_aid
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_ActivatedHandleForAid(void)
{
	START_TEST;
	
	//bool bIsSupportedNFCHCE = false;
	bool bIsActivatedHandler = false;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = nfc_se_is_activated_handler_for_aid(NFC_SE_TYPE_HCE , SEAPPIDHEXVALUE, &bIsActivatedHandler);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_is_activated_handler_for_aid", NfcPrintErrorInfo(nRet),TerminateApp());

	return 0;
}
//& purpose: http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_ActivatedHandleForCategory
* @since_tizen 				2.3.1
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for category.
* @scenario				    Check whether an application to call this api is currently the activated handler for category.
* @apicovered				nfc_se_is_activated_handler_for_category
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_ActivatedHandleForCategory(void)
{
	START_TEST;
	
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	bool bIsActivatedHandler = false;
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;

	int nRet = nfc_se_is_activated_handler_for_category(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, &bIsActivatedHandler);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_is_activated_handler_for_category", NfcPrintErrorInfo(nRet), TerminateApp());
	
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc.cardemulation
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulation_TransectionFgDispatch
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Enable and Disable the transaction foreground dispatch state
* @scenario				    Enable and Disable the transaction foreground dispatch state
* @apicovered				nfc_manager_enable_transaction_fg_dispatch,nfc_manager_disable_transaction_fg_dispatch
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulation_TransectionFgDispatch(void)
{
	START_TEST;
	
	//bool bIsSupportedNFC = false;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet =  nfc_manager_enable_transaction_fg_dispatch();
	if(nRet == NFC_ERROR_NONE)
	{
		nfc_manager_disable_transaction_fg_dispatch();
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_enable_transaction_fg_dispatch", NfcPrintErrorInfo(nRet));

	return 0;
}
//& purpose: http://tizen.org/privilege/nfc
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_Nfc_GetConnectedTag
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Gets current connected tag
* @scenario				    Gets current connected tag
* @apicovered				nfc_manager_get_connected_tag
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_Nfc_GetConnectedTag(void)
{
	START_TEST;
	
	nfc_tag_h tag;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_get_connected_tag(&tag);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_get_connected_tag", NfcPrintErrorInfo(nRet),NULL, NFC_ERROR_NONE);
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_Nfc_GetConnectedTarget
* @since_tizen 				2.3
* @author            		SRID(manu.tiwari)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Gets current connected p2p target.
* @scenario				    Gets current connected p2p target.
* @apicovered				nfc_manager_get_connected_target
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_Nfc_GetConnectedTarget(void)
{
	START_TEST;
	
	nfc_p2p_target_h target = NULL;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsP2pSupported =false;
	bool bIsTagSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_P2P_FEATURE, bIsP2pSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_TAG_FEATURE, bIsTagSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsP2pSupported &&  bIsTagSupported &&  bIsUiccSupported && bIsEseSupported;
	
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = nfc_manager_get_connected_target(&target);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_manager_get_connected_target", NfcPrintErrorInfo(nRet),NULL, NFC_ERROR_NONE);
	return 0;
}
//& purpose: http://tizen.org/privilege/nfc
//& type : auto
/**
* @testcase				    CTc_Nfc_Privilege_NfcCardEmulationEnableCardEmulation
* @since_tizen 				2.3
* @author            		SRID(gaurav.m2)
* @reviewer         		SRID(parshant.v)
* @type 					auto
* @description			    Enable card emulation mode. 
* @scenario				    Enable card emulation mode. 
* @apicovered				nfc_se_enable_card_emulation
* @passcase			        If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			        If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int CTc_Nfc_Privilege_NfcCardEmulationEnableCardEmulation(void)
{
	START_TEST;
	
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}		
	int nRet = nfc_se_enable_card_emulation();	
	if(nRet == NFC_ERROR_NONE)
	{
		nfc_se_disable_card_emulation ();
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_enable_card_emulation", NfcPrintErrorInfo(nRet));
	
	return 0;
}
//& purpose: checkinghttp://tizen.org/privilege/nfc.cardemulation privilege
//& type: auto
/**
* @testcase			CTc_Nfc_PrivilegeNfc_se_set_preferred_handler
* @since_tizen 		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		sets the application as a preferred handler.
* @scenario			sets the application as a preferred handler.
* @apicovered		nfc_se_set_preferred_handler
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NFC Manager must be initialize
* @postcondition	Releases all resources of the NFC Manager
*/
int CTc_Nfc_PrivilegeNfc_se_set_preferred_handler(void)
{
	START_TEST;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = -1;
	
	nRet = nfc_se_set_preferred_handler();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_set_preferred_handler", NfcPrintErrorInfo(nRet),TerminateApp());
	
	TerminateApp();
	return 0;
}

//& purpose: checkinghttp://tizen.org/privilege/nfc.cardemulation privilege
//& type: auto
/**
* @testcase			CTc_Nfc_PrivilegeNfc_se_unset_preferred_handler
* @since_tizen 		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		unsets the application as a preferred handler.
* @scenario			unsets the application as a preferred handler.
* @apicovered		nfc_se_set_preferred_handler
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NFC Manager must be initialize
* @postcondition	Releases all resources of the NFC Manager
*/
int CTc_Nfc_PrivilegeNfc_se_unset_preferred_handler(void)
{
	START_TEST;
	bool bIsNfcSupported =false;
	bool bIsCardemulSupported =false;
	bool bIsHseSupported =false;
	bool bIsUiccSupported =false;
	bool bIsEseSupported =false;
	bool bIsSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_NFC, bIsNfcSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsCardemulSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsHseSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_UICC_FEATURE, bIsUiccSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_ESE_FEATURE, bIsEseSupported, API_NAMESPACE);
	bIsSupported =bIsNfcSupported && bIsCardemulSupported && bIsHseSupported  &&  bIsUiccSupported && bIsEseSupported;
	
	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	int nRet = -1;

	nRet = nfc_se_unset_preferred_handler();
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "nfc_se_unset_preferred_handler", NfcPrintErrorInfo(nRet),TerminateApp());
	
	TerminateApp();
	return 0;
}

