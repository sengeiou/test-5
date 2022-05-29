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

/**
* @function 		ITs_smartcard_session_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_smartcard_session_startup(void)
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
* @function 		ITs_smartcard_session_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_smartcard_session_cleanup(void)
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

//& purpose Checks if the given session is closed
//& type: auto
/**
* @testcase 		ITc_smartcard_session_is_closed_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Checks if the given session is closed
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Open session to the Secure Element in a given reader\n
*					Check if the given session is closed\n
*					Close the session to the given reader\n
*					Check if the given session is closed\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_open_session, smartcard_reader_close_sessions, smartcard_session_is_closed
* @passcase			If smartcard_session_is_closed and all supporting APIs are successful
* @failcase			If smartcard_session_is_closed or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_session_is_closed_p(void)
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

		bool bIsClosed;

		// Target API
		nRet = smartcard_session_is_closed(nSession, &bIsClosed);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_is_closed failed for session %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, nSession, SmartcardGetError(nRet), nRet);
			return 1;
		}
		if ( bIsClosed )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_is_closed incorrectly returned True for session %d\\n", __LINE__, API_NAMESPACE, nSession);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_session_is_closed correctly returned False for session %d\\n", __LINE__, API_NAMESPACE, nSession);

		nRet = smartcard_reader_close_sessions(g_pnReaders[nCounter]);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_close_sessions failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_close_sessions passed for reader %d\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter]);

		// Target API
		nRet = smartcard_session_is_closed(nSession, &bIsClosed);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_is_closed failed for session %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, nSession, SmartcardGetError(nRet), nRet);
			return 1;
		}
		if ( !bIsClosed )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_is_closed incorrectly returned False for session %d\\n", __LINE__, API_NAMESPACE, nSession);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_session_is_closed correctly returned True for session %d\\n", __LINE__, API_NAMESPACE, nSession);
	}

	return 0;
}

//& purpose Gets the reader that provides the given session
//& type: auto
/**
* @testcase 		ITc_smartcard_session_get_reader_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Gets the reader that provides the given session
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Open session to the Secure Element in a given reader\n
*					Get the reader that provides the given session\n
*					Close the session to the given reader\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_open_session, smartcard_session_get_reader, smartcard_reader_close_sessions
* @passcase			If smartcard_session_get_reader and all supporting APIs are successful
* @failcase			If smartcard_session_get_reader or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_session_get_reader_p(void)
{
	START_TEST_CHECK_READERS;

	int nCounter;
	for ( nCounter=0; nCounter<g_nLength; nCounter++ )
	{
		int nSession = false;
		int nRet = smartcard_reader_open_session(g_pnReaders[nCounter], &nSession);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_open_session failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_open_session returned %d for reader %d\\n", __LINE__, API_NAMESPACE, nSession, g_pnReaders[nCounter]);

		int nReader;

		// Target API
		nRet = smartcard_session_get_reader(nSession, &nReader);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_get_reader failed for session %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, nSession, SmartcardGetError(nRet), nRet);
			smartcard_reader_close_sessions(g_pnReaders[nCounter]);
			return 1;
		}
		if ( nReader != g_pnReaders[nCounter] )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_get_reader returned value %d mismatch with expected value %d for session %d\\n", __LINE__, API_NAMESPACE, nReader, g_pnReaders[nCounter], nSession);
			smartcard_reader_close_sessions(g_pnReaders[nCounter]);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_session_get_reader returned %d for session %d\\n", __LINE__, API_NAMESPACE, nReader, nSession);

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

//& purpose Gets the Answer to Reset(ATR) of a given Secure Element
//& type: auto
/**
* @testcase 		ITc_smartcard_session_get_atr_p
* @since_tizen		2.3.1
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		Gets the Answer to Reset(ATR) of a given Secure Element
* @scenario			Initialize smartcard service\n
*					Get the list of available Secure Element readers\n
*					Open session to the Secure Element in a given reader\n
*					Get the Answer to Reset(ATR) of this Secure Element\n
*					Close the session to the given reader\n
*					De-initialize smartcard service
* @apicovered		smartcard_reader_open_session, smartcard_session_get_atr, smartcard_reader_close_sessions
* @passcase			If smartcard_session_get_atr and all supporting APIs are successful
* @failcase			If smartcard_session_get_atr or any supporting API is failed
* @precondition		NA
* @postcondition	NA
*/
int ITc_smartcard_session_get_atr_p(void)
{
	START_TEST_CHECK_READERS;

	int nCounter;
	for ( nCounter=0; nCounter<g_nLength; nCounter++ )
	{
		int nSession = false;
		int nRet = smartcard_reader_open_session(g_pnReaders[nCounter], &nSession);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_reader_open_session failed for reader %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, g_pnReaders[nCounter], SmartcardGetError(nRet), nRet);
			return 1;
		}
		FPRINTF("[Line : %d][%s] smartcard_reader_open_session returned %d for reader %d\\n", __LINE__, API_NAMESPACE, nSession, g_pnReaders[nCounter]);

		unsigned char* pszAtr = NULL;
		int nLength;

		// Target API
		nRet = smartcard_session_get_atr(nSession, &pszAtr, &nLength);
		if ( nRet != SMARTCARD_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] smartcard_session_get_atr failed for session %d, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, nSession, SmartcardGetError(nRet), nRet);
			smartcard_reader_close_sessions(g_pnReaders[nCounter]);
			return 1;
		}

		FPRINTF("[Line : %d][%s] smartcard_session_get_atr returned %s for session %d\\n", __LINE__, API_NAMESPACE, pszAtr, nSession);

		FREE_MEMORY(pszAtr);

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
