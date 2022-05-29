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
#include "ITs-smartcard-common.h"

//& set: Smartcard

int* g_pnReaders;
int g_nLength;


static void ReaderEventCb(int reader_id, smartcard_reader_event_type_e event_type, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside ReaderEventCb callback function\\n", __LINE__, API_NAMESPACE);
	return;
}

/**
 * @function 		ITs_smartcard_reader_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_reader_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Smartcard_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsUICCSupported = TCTCheckSystemInfoFeatureSupported(SE_UICC_FEATURE, API_NAMESPACE);
	g_bIsESESupported = TCTCheckSystemInfoFeatureSupported(SE_ESE_FEATURE, API_NAMESPACE);
	g_bIsSmartcardSupported = g_bIsUICCSupported || g_bIsESESupported;

	g_bIsFeatureMismatched = false;
	g_bIsServiceInitialized = false;
	g_bIsReadersAvailable = false;
	
	int nRet = smartcard_initialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_initialize is unsupported\\n", __LINE__, API_NAMESPACE);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != SMARTCARD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] smartcard_initialize failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
		g_bIsServiceInitialized = false;
	}
	else
	{
		g_bIsServiceInitialized = true;
		
		nRet = smartcard_get_readers(&g_pnReaders, &g_nLength);
		if ( !g_bIsSmartcardSupported )
		{
			if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] smartcard_get_readers failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
				g_bIsFeatureMismatched = true;
				return;
			}
			
			FPRINTF("[Line : %d][%s] smartcard_get_readers is unsupported\\n", __LINE__, API_NAMESPACE);
			g_bIsFeatureMismatched = false;
		}
		else if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_get_readers failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			g_bIsReadersAvailable = false;
		}
		else
		{
			FPRINTF("[Line : %d][%s] smartcard_get_readers returned %d readers\\n", __LINE__, API_NAMESPACE, g_nLength);
			g_bIsReadersAvailable = true;
		}
	}
	
	return;
}

/**
 * @function 		ITs_smartcard_reader_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_smartcard_reader_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Smartcard_p\\n", __LINE__, API_NAMESPACE);
#endif

	FREE_MEMORY(g_pnReaders);
	
	int nRet = smartcard_deinitialize();
	if ( !g_bIsSmartcardSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] smartcard_deinitialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
			return;
		}
		
		FPRINTF("[Line : %d][%s] smartcard_deinitialize is unsupported\\n", __LINE__, API_NAMESPACE);
	}
	else if ( nRet != SMARTCARD_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] smartcard_deinitialize failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, SmartcardGetError(nRet), nRet);
	}
	
	return;
}

//& purpose Gets the name of the given reader
//& type: auto
/**
* @testcase 		ITc_smartcard_reader_get_name_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Gets the name of the given reader
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Get the name of the given reader\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_get_name
* @passcase			If smartcard_reader_get_name and all supporting APIs are successful
* @failcase			If smartcard_reader_get_name or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_reader_get_name_p(void)
{
	START_TEST_CHECK_READERS;

	int nCounter;
	for ( nCounter=0; nCounter<g_nLength; nCounter++ )
	{
		char* pszReaderName;
		
		// Target API
		int nRet = smartcard_reader_get_name(g_pnReaders[nCounter], &pszReaderName);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_get_name failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		if ( NULL == pszReaderName )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_get_name returned NULL for reader %d\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter]);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_get_name returned %s for reader %d\\n", __LINE__, API_NAMESPACE, pszReaderName, g_pnReaders[nCounter]);
		
		FREE_MEMORY(pszReaderName);
	}
	
	return 0;
}

//& purpose Checks if a Secure Element is present in the given reader
//& type: auto
/**
* @testcase 		ITc_smartcard_reader_is_secure_element_present_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Checks if a Secure Element is present in the given reader
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Check if a Secure Element is present in the given reader\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_is_secure_element_present
* @passcase			If smartcard_reader_is_secure_element_present and all supporting APIs are successful
* @failcase			If smartcard_reader_is_secure_element_present or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_reader_is_secure_element_present_p(void)
{
	START_TEST_CHECK_READERS;

	int nCounter;
	for ( nCounter=0; nCounter<g_nLength; nCounter++ )
	{
		bool bIsPresent = false;
		
		// Target API
		int nRet = smartcard_reader_is_secure_element_present(g_pnReaders[nCounter], &bIsPresent);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_is_secure_element_present failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_is_secure_element_present returned %s for reader %d\\n", __LINE__, API_NAMESPACE, (bIsPresent ? "True" : "False"), g_pnReaders[nCounter]);
	}
	
	return 0;
}

//& purpose Open and close session to a Secure Element in the given reader
//& type: auto
/**
* @testcase 		ITc_smartcard_reader_open_close_session_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Open and close session to a Secure Element in the given reader
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Open session to the Secure Element in a given reader\n
*					Close the session to the given reader\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_open_session, smartcard_reader_close_sessions
* @passcase			If smartcard_reader_open_session, smartcard_reader_close_sessions and all supporting APIs are successful
* @failcase			If smartcard_reader_open_session, smartcard_reader_close_sessions or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_reader_open_close_session_p(void)
{
	START_TEST_CHECK_READERS;

	int nCounter;
	for ( nCounter=0; nCounter<g_nLength; nCounter++ )
	{
		int nSession = false;
		
		// Target API
		int nRet = smartcard_reader_open_session(g_pnReaders[nCounter], &nSession);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_open_session failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_open_session returned %d for reader %d\\n", __LINE__, API_NAMESPACE, nSession, g_pnReaders[nCounter]);
		
		// Target API
		nRet = smartcard_reader_close_sessions(g_pnReaders[nCounter]);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_close_sessions failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_close_sessions passed for reader %d\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter]);
	}
	
	return 0;
}

//& purpose Gets the version of SIMAlliance OpenMobileAPI specification
//& type: auto
/**
* @testcase 		ITc_smartcard_get_version_p
* @since_tizen		3.0
* @author           SRID(a.pandia1)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		Gets the version name
* @scenario			Gets the version name
* @apicovered		smartcard_get_version
* @passcase			If smartcard_get_version API called successful
* @failcase			If smartcard_get_version API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_get_version_p(void)
{
	START_TEST_CHECK_READERS;

	char *pszVersion = NULL;
		
	// Target API
	int nRet = smartcard_get_version(&pszVersion);
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet,"smartcard_get_version",SmartcardGetError(nRet));
	if ( NULL == pszVersion )
	{
		FPRINTF("[Line : %d][%s] smartcard_get_version returned NULL for reader \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	FREE_MEMORY(pszVersion);
		
	return 0;
}

//& purpose Sets and unsets a callback function for receiving reader event
//& type: auto
/**
* @testcase 		ITc_smartcard_reader_set_unset_event_cb_p
* @since_tizen		3.0
* @author           SRID(a.pandia1)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		Sets and unsets a callback function for receiving reader event
* @scenario			Sets a callback function for receiving reader event\n
					Unsets a callback function for receiving reader event
* @apicovered		smartcard_reader_set_event_cb, smartcard_reader_unset_event_cb 
* @passcase			If smartcard_reader_set_event_cb and smartcard_reader_unset_event_cb APIs called successful
* @failcase			If smartcard_reader_set_event_cb and smartcard_reader_unset_event_cb APIs get failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_reader_set_unset_event_cb_p(void)
{
	START_TEST_CHECK_READERS;

	// Target API
	int nRet = smartcard_reader_set_event_cb(ReaderEventCb, NULL);
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet,"smartcard_reader_set_event_cb",SmartcardGetError(nRet));
	
	nRet = smartcard_reader_unset_event_cb();
	PRINT_RESULT(SMARTCARD_ERROR_NONE, nRet,"smartcard_reader_unset_event_cb",SmartcardGetError(nRet));
	
	return 0;
}