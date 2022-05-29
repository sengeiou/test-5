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
app_control_h g_app_control_handler;

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
* @function 		ITs_nfc_se_startup
* @description	 	Called before each test, Check whether NFC is supported or not and initialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_se_startup(void)
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
* @function 		ITs_nfc_se_cleanup
* @description	 	Called after each test, deinitialize the NFC manager.
* @parameter		NA
* @return 			NA
*/
void ITs_nfc_se_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_NFC_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bNFCTestPrecondition )
	{
		int nRet = nfc_manager_deinitialize();
		if ( nRet != 0 )
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

//& purpose: Get the current card emulation mode
//& type: auto
/**
* @testcase 				ITc_nfc_se_get_card_emulation_mode_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Get the current card emulation mode.
* @scenario					Get the current card emulation mode.
* @apicovered				nfc_se_get_card_emulation_mode
* @passcase					When nfc_se_get_card_emulation_mode is successfull
* @failcase					If target API nfc_se_get_card_emulation_mode fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_se_get_card_emulation_mode_p(void)
{
	START_TEST;

	nfc_se_card_emulation_mode_type_e type = NFC_SE_CARD_EMULATION_MODE_ON;
	bool bIsSupportedNFCEmulation = false;
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsSupportedNFCEmulation, API_NAMESPACE);

	int nRet = nfc_se_get_card_emulation_mode(&type);
	if ( !bIsSupportedNFCEmulation )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] nfc_se_get_card_emulation_mode API call returned mismatch for unsupported NFC card emulation feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}

		else
		{
			FPRINTF("[Line : %d][%s] nfc_se_get_card_emulation_mode API call correctly returned for unsupported NFC feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_se_get_card_emulation_mode", NFCGetError(nRet));
	if ( type == NFC_SE_CARD_EMULATION_MODE_ON )
	{
		FPRINTF("[Line : %d][%s] emulation mode is: %s\\n", __LINE__, API_NAMESPACE, "NFC_SE_CARD_EMULATION_MODE_ON");
	}
	else
	{
		FPRINTF("[Line : %d][%s] emulation mode is: %s\\n", __LINE__, API_NAMESPACE, "NFC_SE_CARD_EMULATION_MODE_ON");
	}

	return 0;
}

//& purpose: To get the card emulation Secure Element type.
//& type : auto
/**
* @testcase				    ITc_nfc_manager_get_se_type_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    To get the card emulation Secure Element type
* @scenario				    Get the card emulation Secure Element type\n
*                           Check whether output value is valid or not
* @apicovered				nfc_manager_get_se_type
* @passcase					When nfc_manager_get_se_type are successful and output value is valid
* @failcase					When nfc_manager_get_se_type fails or output value is invalid
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_manager_get_se_type_p(void)
{
	START_TEST;

	bool bIsSupportedNFCEmulation = false;
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsSupportedNFCEmulation, API_NAMESPACE);

	nfc_se_type_e eGeType = -1;
	int nRet = nfc_manager_get_se_type(&eGeType);
	if ( !bIsSupportedNFCEmulation )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API call returned mismatch for unsupported NFC card emulation feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API call correctly returned for unsupported NFC feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 0;
		}
	}
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_get_se_type", NFCGetError(nRet));
	if ( eGeType < 0 )
	{
		FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API call returned invalid value\\n",
			__LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}


//& purpose: Set the default route
//& type: auto
/**
* @testcase				    ITc_nfc_se_set_default_route_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    Set the default route
* @scenario				    Set the default route
* @apicovered				nfc_se_set_default_route,nfc_manager_get_se_type
* @passcase					When nfc_se_set_default_route are successful and output value is valid
* @failcase					When nfc_se_set_default_route fails or output value is invalid
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_se_set_default_route_p(void)
{
	START_TEST;

	bool bIsSupportedNFCEmulation = false;
	IS_FEATURE_SUPPORTED(NFC_CARD_EMULATION_FEATURE, bIsSupportedNFCEmulation, API_NAMESPACE);

	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	nfc_se_type_e ePowerOnStatus = -1;
	int nRet = nfc_manager_get_se_type(&ePowerOnStatus);
	if ( !bIsSupportedNFCEmulation )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API call returned mismatch for unsupported NFC card emulation feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API call correctly returned for unsupported NFC feature, error returned = %s\\n",
				__LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 0;
		}
	}
	else
	{
		PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_manager_get_se_type", NFCGetError(nRet));
	}
	if((ePowerOnStatus<NFC_SE_TYPE_DISABLE)||(ePowerOnStatus>NFC_SE_TYPE_HCE))
	{
		FPRINTF("[Line : %d][%s] nfc_manager_get_se_type API gives invalid output value\\n",
				__LINE__, API_NAMESPACE);
			return 1;
	}

	nRet = nfc_se_set_default_route(ePowerOnStatus, ePowerOnStatus, ePowerOnStatus);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_set_default_route failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_se_set_default_route API call correctly returned for unsupported NFC feature, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetError(nRet));
			return 0;
		}
	}
	else
	{
		if(nRet == NFC_ERROR_NONE || nRet == NFC_ERROR_SECURITY_RESTRICTED)
		{
			FPRINTF("[Line : %d][%s] nfc_se_set_default_route API passed \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
		else
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_set_default_route failed, expected return = NFC_ERROR_NONE or NFC_ERROR_SECURITY_RESTRICTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			return 1;
		}
	}

	return 0;
}

//& purpose: To register and unregister a AID for a specific category
//& type : auto
/**
* @testcase				    ITc_nfc_se_register_unregister_aid_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    register and unregister a AID for a specific category
* @scenario				    register AID for a specific category
* 						    unregister AID for a specific category
* @apicovered				nfc_se_register_aid, nfc_se_unregister_aid
* @passcase					When nfc_se_register_aid is successful
* @failcase					When nfc_se_register_aid fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_se_register_unregister_aid_p(void)
{
    START_TEST;

	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	int nRet = -1;
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;
	if (!LaunchApp(TEST_TESTNFCLIENT_APPID))
	{
		return 1;
	}

	nRet = nfc_se_register_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_register_aid failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			TerminateApp();
			return 1;
		}

		TerminateApp();
		return 0;
	}

	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_register_aid", NFCGetError(nRet), TerminateApp());

	usleep(MICROSECONDS_PER_SECOND);
	nRet = nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_unregister_aid", NFCGetError(nRet), TerminateApp());
	TerminateApp();
	return 0;
}

//& purpose: Check whether an application to call this api is currently the activated handler for specific AID
//& type: auto
/**
* @testcase				    ITc_nfc_se_is_activated_handler_for_aid_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for specific AID
* @scenario				    Check whether an application to call this api is currently the activated handler for specific AID
* @apicovered				nfc_se_register_aid, nfc_se_is_activated_handler_for_aid, nfc_se_unregister_aid
* @passcase					When nfc_se_is_activated_handler_for_aid is successful
* @failcase					When nfc_se_is_activated_handler_for_aid fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_se_is_activated_handler_for_aid_p(void)
{
	START_TEST;

	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	int nRet = -1;
	bool bIsActivatedHandler = false;
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;
	if (!LaunchApp(TEST_TESTNFCLIENT_APPID))
	{
		return 1;
	}

	nRet = nfc_se_register_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_register_aid failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			TerminateApp();
			return 1;
		}

		TerminateApp();
		return 0;
	}

	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_register_aid", NFCGetError(nRet), TerminateApp());

	nRet = nfc_se_is_activated_handler_for_aid(NFC_SE_TYPE_HCE , SEAPPIDHEXVALUE, &bIsActivatedHandler);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_is_activated_handler_for_aid", NFCGetError(nRet), nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);TerminateApp());

	nRet = nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_unregister_aid", NFCGetError(nRet), TerminateApp());
	TerminateApp();
	return 0;
}

//& purpose: Check whether an application to call this api is currently the activated handler for category.
//& type: auto
/**
* @testcase				    ITc_nfc_se_is_activated_handler_for_category_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for category.
* @scenario				    Check whether an application to call this api is currently the activated handler for category.
* @apicovered				nfc_se_register_aid, nfc_se_is_activated_handler_for_category, nfc_se_unregister_aid
* @passcase					When nfc_se_is_activated_handler_for_category is successful
* @failcase					When nfc_se_is_activated_handler_for_category fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_se_is_activated_handler_for_category_p(void)
{
	START_TEST;
	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	int nRet = -1;
	bool bIsActivatedHandler = false;
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;
	if (!LaunchApp(TEST_TESTNFCLIENT_APPID))
	{
		return 1;
	}

	nRet = nfc_se_register_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_register_aid failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			TerminateApp();
			return 1;
		}

		TerminateApp();
		return 0;
	}

	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_register_aid", NFCGetError(nRet), TerminateApp());

	nRet = nfc_se_is_activated_handler_for_category(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, &bIsActivatedHandler);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_is_activated_handler_for_category", NFCGetError(nRet), nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);TerminateApp());

	nRet = nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_unregister_aid", NFCGetError(nRet), TerminateApp());
	TerminateApp();
	return 0;
}

//& purpose: Check whether an application to call this api is currently the activated handler for specific AID
//& type: auto
/**
* @testcase				    ITc_nfc_se_foreach_registered_aids_p
* @since_tizen 				2.3.1
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description			    Check whether an application to call this api is currently the activated handler for category.
* @scenario				    Check whether an application to call this api is currently the activated handler for category.
* @apicovered				nfc_se_register_aid, nfc_se_foreach_registered_aids, nfc_se_unregister_aid
* @passcase					When nfc_se_foreach_registered_aids is successful
* @failcase					When nfc_se_foreach_registered_aids fails
* @precondition				NFC Manager must be initialize
* @postcondition			Releases all resources of the NFC Manager
*/
int ITc_nfc_se_foreach_registered_aids_p(void)
{
	START_TEST;
	bool bIsSupportedNFCHCE = false;
	IS_FEATURE_SUPPORTED(NFC_HCE_FEATURE, bIsSupportedNFCHCE, API_NAMESPACE);

	int nRet = -1;
	nfc_card_emulation_category_type_e eNfcCardEmuCategory = NFC_CARD_EMULATION_CATEGORY_PAYMENT;
	if (!LaunchApp(TEST_TESTNFCLIENT_APPID))
	{
		return 1;
	}

	nRet = nfc_se_register_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	if(!bIsSupportedNFCHCE)
	{
		if(nRet != NFC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF( "\\n [Line : %d] [%s] nfc_se_register_aid failed, expected return = NFC_ERROR_NOT_SUPPORTED, value returned = %s ", __LINE__,API_NAMESPACE, NFCGetError(nRet));
			TerminateApp();
			return 1;
		}

		TerminateApp();
		return 0;
	}

	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_register_aid", NFCGetError(nRet), TerminateApp());

	nRet = nfc_se_foreach_registered_aids(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, NfcSERegisteredAidCallback, NULL);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_foreach_registered_aids", NFCGetError(nRet), nfc_se_unregister_aid(NFC_SE_TYPE_HCE ,eNfcCardEmuCategory, SEAPPIDHEXVALUE);TerminateApp());

	nRet = nfc_se_unregister_aid(NFC_SE_TYPE_HCE , eNfcCardEmuCategory, SEAPPIDHEXVALUE);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_se_unregister_aid", NFCGetError(nRet), TerminateApp());
	TerminateApp();
	return 0;
}
/** @} */ //end of itc-nfc
/** @} */ //end of itc-nfc-testcases
