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

/**
* @function 		ITs_nfc_ndef_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_nfc_ndef_startup(void)
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
	g_hMessage = NULL;
	g_hRecord = NULL;
	return;
}

/**
* @function 		ITs_nfc_ndef_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_nfc_ndef_cleanup(void)
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

//& purpose: Creates a record with given parameter value and destroy the record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_create_destroy_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Creates a record with given parameter value and destroy the record
* @scenario					Create record\n
*							Destroy record
* @apicovered				nfc_ndef_record_create and nfc_ndef_record_destroy
* @passcase					When nfc_ndef_record_create and nfc_ndef_record_destroy is successfull
* @failcase					If target APIs nfc_ndef_record_create or nfc_ndef_record_destroy fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_create_destroy_p(void)
{
	START_TEST;

	int nRet = 0;
	unsigned char szType[] = "TEST";
	unsigned char szID[] = "TEST";
	unsigned char szPayLoad[] = "TEST";
	int nTypeSize = 1;
	int nIdSize = 4;
	int nPayloadSize = 4;
	nfc_record_tnf_e tnf_type[] = {NFC_RECORD_TNF_EMPTY, NFC_RECORD_TNF_WELL_KNOWN, NFC_RECORD_TNF_MIME_MEDIA, NFC_RECORD_TNF_URI, NFC_RECORD_TNF_EXTERNAL_RTD, NFC_RECORD_TNF_UNKNOWN, NFC_RECORD_TNF_UNCHANGED};
	int nEnumSize = sizeof(tnf_type) / sizeof(tnf_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( tnf_type[nEnumCounter] == NFC_RECORD_TNF_EMPTY )
		{
			nRet = nfc_ndef_record_create(&g_hRecord, tnf_type[nEnumCounter], NULL, 0, NULL, 0, NULL, 0);
		}
		else
		{
			nRet = nfc_ndef_record_create(&g_hRecord, tnf_type[nEnumCounter], szType, nTypeSize, szID, nIdSize, szPayLoad, nPayloadSize);
		}
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_create failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}
		else if ( g_hRecord == NULL )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create' record handle is null for enum %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_create passed for enum %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]));
		}

		sleep(LONG_DELAY);

		nRet = nfc_ndef_record_destroy(g_hRecord);
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy passed for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]));
		}
	}

	return 0;
}


//& purpose: Creates a record with text type payload
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_create_text_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Creates a record with text type payload
* @scenario					Create record with text\n
*							Destroy record
* @apicovered				nfc_ndef_record_create_text and nfc_ndef_record_destroy
* @passcase					When nfc_ndef_record_create_text is successfull
* @failcase					If target APIs nfc_ndef_record_create_text fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_create_text_p(void)
{
	START_TEST;

	int nRet = 0;
	nfc_encode_type_e encode_type[] = {NFC_ENCODE_UTF_8, NFC_ENCODE_UTF_16};
	int nEnumSize = sizeof(encode_type) / sizeof(encode_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if (encode_type[nEnumCounter] == NFC_ENCODE_UTF_8)
		{
			nRet = nfc_ndef_record_create_text(&g_hRecord, ENCODE_TEXT, ENCODE_TYPE_UTF8, encode_type[nEnumCounter]);
		}
		else
		{
			nRet = nfc_ndef_record_create_text(&g_hRecord, ENCODE_TEXT, ENCODE_TYPE_UTF16, encode_type[nEnumCounter]);
		}

		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_create_text failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}
		else if ( g_hRecord == NULL )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create_text' record handle is null for enum %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_create_text passed for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
		}

		sleep(LONG_DELAY);

		nRet = nfc_ndef_record_destroy(g_hRecord);
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy failed for %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy passed for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
		}
	}

	return 0;
}

//& purpose: Creates a record with URI type payload
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_create_uri_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Creates a record with URI type payload
* @scenario					Create record with uri\n
*							Destroy record
* @apicovered				nfc_ndef_record_create_uri and nfc_ndef_record_destroy
* @passcase					When nfc_ndef_record_create_uri is successfull
* @failcase					If target APIs nfc_ndef_record_create_uri fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_create_uri_p(void)
{
	START_TEST;

	int nRet = nfc_ndef_record_create_uri(&g_hRecord, URI);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_record_create_uri", NFCGetError(nRet));	
	CHECK_HANDLE(g_hRecord, "nfc_ndef_record_create_uri");

	sleep(LONG_DELAY);

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Creates a record with MIME type payload
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_create_mime_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Creates a record with MIME type payload
* @scenario					Create record with MIME\n
*							Destroy record
* @apicovered				nfc_ndef_record_create_mime and nfc_ndef_record_destroy
* @passcase					When nfc_ndef_record_create_mime is successfull
* @failcase					If target APIs nfc_ndef_record_create_mime fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_create_mime_p(void)
{
	START_TEST;

	const char *pszMimeType = "text/plain";
	const unsigned char pszData[] = "TempData";
	int nDataSize = sizeof(pszData);

	int nRet = nfc_ndef_record_create_mime(&g_hRecord, pszMimeType, pszData, nDataSize);		
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_record_create_mime", NFCGetError(nRet));	
	CHECK_HANDLE(g_hRecord, "nfc_ndef_record_create_mime");

	sleep(LONG_DELAY);

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Creates NDEF message handle
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_create_destroy_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Creates NDEF message handle
* @scenario					Create message handle\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_create and nfc_ndef_message_destroy
* @passcase					When nfc_ndef_message_create and nfc_ndef_message_destroy is successfull
* @failcase					If target APIs nfc_ndef_message_create or nfc_ndef_message_destroy fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_create_destroy_p(void)
{
	START_TEST;

	int nRet = nfc_ndef_message_create(&g_hMessage);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_message_create", NFCGetError(nRet));	
	CHECK_HANDLE(g_hMessage, "nfc_ndef_message_create");

	sleep(LONG_DELAY);

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets the number of record in NDEF message
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_get_record_count_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets the number of record in NDEF message
* @scenario					Create message handle\n
*							Create record handle\n
*							Append record in message\n
*							Get record count\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_append_record, nfc_ndef_message_destroy and nfc_ndef_message_get_record_count
* @passcase					When nfc_ndef_message_get_record_count is successfull and count is 1
* @failcase					If target APIs nfc_ndef_message_get_record_count fails or count is less than 1
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_get_record_count_p(void)
{
	START_TEST;

	if ( NFCCreateMessageRecordHandle() == false )
	{
		return 1;
	}

	int nCount = 0;
	int nRet = nfc_ndef_message_append_record(g_hMessage, g_hRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_append_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage));

	sleep(LONG_DELAY);

	nRet = nfc_ndef_message_get_record_count(g_hMessage, &nCount);		
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_get_record_count", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage));	
	if ( nCount == 0 )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_message_get_record_count', count is 0\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}
	FPRINTF("[Line : %d][%s] Count value: %d\\n", __LINE__, API_NAMESPACE, nCount);

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));

	return 0;
}

//& purpose: Appends a record into NDEF message
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_append_record_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Appends a record into NDEF message
* @scenario					Create message handle\n
*							Create record handle\n
*							Append record in message\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_create, nfc_ndef_message_append_record and nfc_ndef_message_destroy
* @passcase					When nfc_ndef_message_append_record is successfull
* @failcase					If target API nfc_ndef_message_append_record fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_append_record_p(void)
{
	START_TEST;

	int nRet = nfc_ndef_message_create(&g_hMessage);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_message_create", NFCGetError(nRet));	
	CHECK_HANDLE(g_hMessage, "nfc_ndef_message_create");
	sleep(LONG_DELAY);

	nRet = nfc_ndef_record_create_uri(&g_hRecord, URI);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_create_uri", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););	
	if ( g_hRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_create_uri return NULL handle\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}
	sleep(LONG_DELAY);

	nRet = nfc_ndef_message_append_record(g_hMessage, g_hRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_append_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););	
	sleep(LONG_DELAY);

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));

	return 0;
}

//& purpose: Inserts a record at index into NDEF message and remove record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_insert_remove_record_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Inserts a record at index into NDEF message and remove record
* @scenario					Create message handle\n
*							Create record handle\n
*							Insert record in message\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_insert_record and nfc_ndef_message_destroy
* @passcase					When nfc_ndef_message_insert_record and nfc_ndef_message_remove_record is successfull
* @failcase					If target APIs nfc_ndef_message_insert_record or nfc_ndef_message_remove_record fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_insert_remove_record_p(void)
{
	START_TEST;

	if ( NFCCreateMessageRecordHandle() == false )
	{
		return 1;
	}

	int nIndex = 0;
	int nRet = nfc_ndef_message_insert_record(g_hMessage, nIndex, g_hRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_insert_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););	

	sleep(LONG_DELAY);

	nRet = nfc_ndef_message_remove_record(g_hMessage, nIndex);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_remove_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););	

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets record by index
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_get_record_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets record by index
* @scenario					Create message handle\n
*							Create record handle\n
*							Append record in message\n
*							Get record\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_destroy and nfc_ndef_message_get_record
* @passcase					When nfc_ndef_message_get_record is successfull
* @failcase					If target API nfc_ndef_message_get_record fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_get_record_p(void)
{
	START_TEST;

	if ( NFCCreateMessageRecordHandle() == false )
	{
		return 1;
	}

	int nIndex = 0;
	nfc_ndef_record_h hGetRecord = NULL;

	int nRet = nfc_ndef_message_insert_record(g_hMessage, nIndex, g_hRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_insert_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););

	nRet = nfc_ndef_message_get_record(g_hMessage, nIndex, &hGetRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_get_record", NFCGetError(nRet), nfc_ndef_message_remove_record(g_hMessage, nIndex); nfc_ndef_message_destroy(g_hMessage););	

	if ( hGetRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_get_record return NULL handle\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_message_remove_record(g_hMessage, nIndex);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}

	nRet = nfc_ndef_message_remove_record(g_hMessage, nIndex);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_remove_record", NFCGetError(nRet));	

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets serial bytes array of NDEF message and Creates NDEF message handle from raw serial bytes
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_message_get_rawdata_create_from_rawdata_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets serial bytes array of NDEF message and Creates NDEF message handle from raw serial bytes
* @scenario					Create message handle\n
*							Create record handle\n
*							Append record in message\n
*							Get raw data\n
*							Create message from raw data\n
*							Destroy message handle
* @apicovered				nfc_ndef_message_append_record, nfc_ndef_message_destroy, nfc_ndef_message_get_rawdata and nfc_ndef_message_create_from_rawdata
* @passcase					When nfc_ndef_message_get_rawdata and nfc_ndef_message_create_from_rawdata is successful
* @failcase					If target APIs nfc_ndef_message_get_rawdata or nfc_ndef_message_create_from_rawdata fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_message_get_rawdata_create_from_rawdata_p(void)
{
	START_TEST;

	nfc_ndef_message_h hGetMessage = NULL;
	unsigned char *pszBuffer = NULL;
	unsigned int nBufferSize = 0;

	if ( NFCCreateMessageRecordHandle() == false )
	{
		return 1;
	}

	int nRet = nfc_ndef_message_append_record(g_hMessage, g_hRecord);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_append_record", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););

	//Target api: nfc_ndef_message_get_rawdata
	nRet = nfc_ndef_message_get_rawdata(g_hMessage, &pszBuffer, &nBufferSize);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_get_rawdata", NFCGetError(nRet), nfc_ndef_message_destroy(g_hMessage););	
	if ( pszBuffer == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_get_rawdata return NULL buffer\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}

	if ( nBufferSize <= 0 )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_get_rawdata returns buffer size is: %u.\\n", __LINE__, API_NAMESPACE, nBufferSize);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}

	//Target api: nfc_ndef_message_create_from_rawdata
	nRet = nfc_ndef_message_create_from_rawdata(&hGetMessage, pszBuffer, nBufferSize);		
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_create_from_rawdata", NFCGetError(nRet), FREE_MEMORY(pszBuffer); nfc_ndef_message_destroy(g_hMessage););
	if ( hGetMessage == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_message_create_from_rawdata returns NULL buffer\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszBuffer);
		nfc_ndef_message_destroy(g_hMessage);
		return 1;
	}

	FREE_MEMORY(pszBuffer);

	nRet = nfc_ndef_message_destroy(hGetMessage);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet),nfc_ndef_message_destroy(g_hMessage));	

	nRet = nfc_ndef_message_destroy(g_hMessage);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_message_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets record payload
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_payload_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets record payload
* @scenario					Create record handle\n
*							Get record payload\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy and nfc_ndef_record_get_payload
* @passcase					When nfc_ndef_record_get_payload is successfull
* @failcase					If target API nfc_ndef_record_get_payload fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_payload_p(void)
{
	START_TEST;

	unsigned char *pszPayload = NULL;
	unsigned int nSize = 0;

	if ( NFCCreateUri() == false )
	{
		return 1;
	}

	int nRet = nfc_ndef_record_get_payload(g_hRecord, &pszPayload, &nSize);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_get_payload", NFCGetError(nRet), nfc_ndef_record_destroy(g_hRecord););	
	if ( pszPayload == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_payload returns NULL record payload\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}

	if ( nSize <= 0 )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_payload returns invalid size\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Set record ID and get record id
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_set_get_id_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Set record ID and get record id
* @scenario					Create record handle\n
*							Set record id\n
*							Get record id\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy, nfc_ndef_record_set_id and nfc_ndef_record_get_id
* @passcase					When nfc_ndef_record_set_id and nfc_ndef_record_get_id is successfull
* @failcase					If target APIs nfc_ndef_record_set_id or nfc_ndef_record_get_id fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_set_get_id_p(void)
{
	START_TEST;

	unsigned char szSetId[10] = {0,};
	unsigned char *pszGetId = NULL;
	int nGetSize = 0;
	int nLength = 0;

	if ( NFCCreateUri() == false )
	{
		return 1;
	}

	snprintf((char *)szSetId, sizeof(szSetId)-1, "ID_%d", 1);
	nLength = strlen((char *)szSetId);

	int nRet = nfc_ndef_record_set_id(g_hRecord, szSetId, nLength);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_set_id", NFCGetError(nRet), nfc_ndef_record_destroy(g_hRecord););	
	sleep(LONG_DELAY);

	nRet = nfc_ndef_record_get_id(g_hRecord, &pszGetId, &nGetSize);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_get_id", NFCGetError(nRet), nfc_ndef_record_destroy(g_hRecord););	
	if ( pszGetId == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_id returns NULL Id\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	if ( nGetSize != nLength )
	{
		FPRINTF("[Line : %d][%s] After nfc_ndef_record_get_id, ID mismatch\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets record type
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_type_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets record type
* @scenario					Create record handle\n
*							Get record type\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy and nfc_ndef_record_get_type
* @passcase					When nfc_ndef_record_get_type is successfull
* @failcase					If target API nfc_ndef_record_get_type fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_type_p(void)
{
	START_TEST;

	unsigned char *pszType = NULL;
	int nSize = 0;

	if ( NFCCreateUri() == false )
	{
		return 1;
	}

	int nRet = nfc_ndef_record_get_type(g_hRecord, &pszType, &nSize);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_get_type", NFCGetError(nRet), nfc_ndef_record_destroy(g_hRecord););	
	if ( pszType == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_type returns NULL record type\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	if ( nSize <= 0 )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_type', Size value is incorrect\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets record TNF(Type Name Format) value
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_tnf_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets record TNF(Type Name Format) value
* @scenario					Create record handle\n
*							Get tnf type\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy and nfc_ndef_record_get_tnf
* @passcase					When nfc_ndef_record_get_tnf is successfull
* @failcase					If target API nfc_ndef_record_get_tnf fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_tnf_p(void)
{
	START_TEST;

	int nRet = 0;
	nfc_record_tnf_e tnf = NFC_RECORD_TNF_EMPTY;
	nfc_record_tnf_e tnf_type[] = {NFC_RECORD_TNF_EMPTY, NFC_RECORD_TNF_WELL_KNOWN, NFC_RECORD_TNF_MIME_MEDIA, NFC_RECORD_TNF_URI, NFC_RECORD_TNF_EXTERNAL_RTD, NFC_RECORD_TNF_UNKNOWN, NFC_RECORD_TNF_UNCHANGED};
	int nEnumSize = sizeof(tnf_type) / sizeof(tnf_type[0]);
	int nEnumCounter = 0;
	unsigned char szType[] = "TEST";
	unsigned char szID[] = "TEST";
	unsigned char szPayLoad[] = "TEST";
	int nTypeSize = 1;
	int nIdSize = 4;
	int nPayloadSize = 4;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( tnf_type[nEnumCounter] == NFC_RECORD_TNF_EMPTY )
		{
			nRet = nfc_ndef_record_create(&g_hRecord, tnf_type[nEnumCounter], NULL, 0, NULL, 0, NULL, 0);
		}
		else
		{
			nRet = nfc_ndef_record_create(&g_hRecord, tnf_type[nEnumCounter], szType, nTypeSize, szID, nIdSize, szPayLoad, nPayloadSize);
		}
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_create failed in for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]), NFCGetError(nRet));
			return 1;
		}
		else if ( g_hRecord == NULL )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_create' record handle is null for enum: %s.\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]));
			return 1;
		}

		nRet = nfc_ndef_record_get_tnf(g_hRecord, &tnf);			
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_get_tnf failed for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]), NFCGetError(nRet));
			nfc_ndef_record_destroy(g_hRecord);
			return 1;
		}
		else if (tnf != tnf_type[nEnumCounter])
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_tnf', tnf value is incorrect for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]));
			nfc_ndef_record_destroy(g_hRecord);
			return 1;
		}

		nRet = nfc_ndef_record_destroy(g_hRecord);
		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_destroy failed for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetTnfEnumString(tnf_type[nEnumCounter]), NFCGetError(nRet));
		}
	}

	return 0;
}

//& purpose: Gets text from text record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_text_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets text from text record
* @scenario					Create record handle\n
*							Get text\n
*							Destroy record
* @apicovered				nfc_ndef_record_get_text
* @passcase					When nfc_ndef_record_get_text is successfull
* @failcase					If target API nfc_ndef_record_get_text fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_text_p(void)
{
	START_TEST;

	int nRet = 0;
	char *pszText = NULL;
	nfc_encode_type_e encode_type[] = {NFC_ENCODE_UTF_8, NFC_ENCODE_UTF_16};
	int nEnumSize = sizeof(encode_type) / sizeof(encode_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( NFCCreateRecordText(encode_type[nEnumCounter], nEnumCounter) == false )
		{
			return 1;
		}

		nRet = nfc_ndef_record_get_text(g_hRecord, &pszText);

		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_get_text failed for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]), NFCGetError(nRet));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else if ( pszText == NULL )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_text', text value is null for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else if ( strcmp(pszText, ENCODE_TEXT) != 0 )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_text', text value mismatch for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
			FREE_MEMORY(pszText);
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		FREE_MEMORY(pszText);
		NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
	}

	return 0;
}

//& purpose: Gets language code from text record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_langcode_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets language code from text record
* @scenario					Create record handle\n
*							Get language code\n
*							Destroy record
* @apicovered				nfc_ndef_record_get_langcode
* @passcase					When nfc_ndef_record_get_langcode is successfull
* @failcase					If target API nfc_ndef_record_get_langcode fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_langcode_p(void)
{
	START_TEST;

	int nRet = 0;
	char *pszLanguage = NULL;
	nfc_encode_type_e encode_type[] = {NFC_ENCODE_UTF_8, NFC_ENCODE_UTF_16};
	int nEnumSize = sizeof(encode_type) / sizeof(encode_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( NFCCreateRecordText(encode_type[nEnumCounter], nEnumCounter) == false )
		{
			return 1;
		}

		nRet = nfc_ndef_record_get_langcode(g_hRecord, &pszLanguage);

		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_get_langcode failed for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]), NFCGetError(nRet));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else if ( pszLanguage == NULL )
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_langcode', language value is null for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else
		{
			if (encode_type[nEnumCounter] == NFC_ENCODE_UTF_8)	
			{
				if ( strcmp(pszLanguage, ENCODE_TYPE_UTF8) != 0 )
				{
					FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_langcode', language value mismatch for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
					NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
					return 1;
				}
				else
				{
					FPRINTF("[Line : %d][%s] nfc_ndef_record_get_langcode passed\\n", __LINE__, API_NAMESPACE);
				}
			}
			else
			{
				if ( strcmp(pszLanguage, ENCODE_TYPE_UTF16) != 0 )
				{
					FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_langcode', language value mismatch for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
					NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
					return 1;
				}
				else
				{
					FPRINTF("[Line : %d][%s] nfc_ndef_record_get_langcode passed\\n", __LINE__, API_NAMESPACE);
				}
			}
		}
		FREE_MEMORY(pszLanguage);
		NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
	}

	return 0;
}

//& purpose: Gets encoding type from text record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_encode_type_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets encoding type from text record
* @scenario					Create record handle\n
*							Get encoding type\n
*							Destroy record
* @apicovered				nfc_ndef_record_get_encode_type
* @passcase					When nfc_ndef_record_get_encode_type is successfull
* @failcase					If target API nfc_ndef_record_get_encode_type fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_encode_type_p(void)
{
	START_TEST;

	int nRet = 0;
	nfc_encode_type_e encode;
	nfc_encode_type_e encode_type[] = {NFC_ENCODE_UTF_8, NFC_ENCODE_UTF_16};
	int nEnumSize = sizeof(encode_type) / sizeof(encode_type[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( NFCCreateRecordText(encode_type[nEnumCounter], nEnumCounter) == false )
		{
			return 1;
		}
		nRet = nfc_ndef_record_get_encode_type(g_hRecord, &encode);

		if ( nRet != NFC_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_get_encode_type failed for enum: %s, error returned = %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]), NFCGetError(nRet));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else if (encode != encode_type[nEnumCounter])
		{
			FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_encode_type', encode value is incorrect for enum: %s\\n", __LINE__, API_NAMESPACE, NFCGetEncodeEnumString(encode_type[nEnumCounter]));
			NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] nfc_ndef_record_get_encode_type passed\\n", __LINE__, API_NAMESPACE);
		}
		NFCDestroyText(encode_type[nEnumCounter], nEnumCounter);
	}

	return 0;
}

//& purpose: Gets URI from uri record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_uri_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets URI from uri record
* @scenario					Create record handle\n
*							Get uri\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy and nfc_ndef_record_get_uri
* @passcase					When nfc_ndef_record_get_uri is successfull
* @failcase					If target API nfc_ndef_record_get_uri fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_uri_p(void)
{
	START_TEST;

	char *pszGetUri = NULL;

	if ( NFCCreateUri() == false )
	{
		return 1;
	}

	int nRet = nfc_ndef_record_get_uri(g_hRecord, &pszGetUri);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_get_uri", NFCGetError(nRet), FREE_MEMORY(pszGetUri); nfc_ndef_record_destroy(g_hRecord););

	if ( pszGetUri == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_uri returns NULL URI\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	if ( strcmp(pszGetUri, URI) != 0 )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_uri' uri value mismatch (set value is: %s and get value is: %s)\\n", __LINE__, API_NAMESPACE, URI, pszGetUri);
		FREE_MEMORY(pszGetUri);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	FREE_MEMORY(pszGetUri);

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

//& purpose: Gets mime type from mime type record
//& type: auto
/**
* @testcase 				ITc_nfc_ndef_record_get_mime_type_p
* @since_tizen 				2.3
* @author            		SRID(avinash.a)
* @reviewer         		SRID(gupta.sanjay)
* @type 					auto
* @description				Gets mime type from mime type record
* @scenario					Create record handle\n
*							Get mime type\n
*							Destroy record
* @apicovered				nfc_ndef_record_destroy and nfc_ndef_record_get_mime_type
* @passcase					When nfc_ndef_record_get_mime_type is successfull
* @failcase					If target API nfc_ndef_record_get_mime_type fails
* @precondition				NFC Manager must be initialized
* @postcondition			NFC Manager must be deinitialized
*/
int ITc_nfc_ndef_record_get_mime_type_p(void)
{
	START_TEST;

	const char *pszMimeType = "text/plain";
	const unsigned char pszData[] = "TempData";
	int nDataSize = sizeof(pszData);
	char *pszGetMimeType = NULL;

	int nRet = nfc_ndef_record_create_mime(&g_hRecord, pszMimeType, pszData, nDataSize);
	PRINT_RESULT(NFC_ERROR_NONE, nRet, "nfc_ndef_record_create_mime", NFCGetError(nRet));	
	CHECK_HANDLE(g_hRecord, "nfc_ndef_record_create_mime");

	nRet = nfc_ndef_record_get_mime_type(g_hRecord, &pszGetMimeType);
	PRINT_RESULT_CLEANUP(NFC_ERROR_NONE, nRet, "nfc_ndef_record_get_mime_type", NFCGetError(nRet), FREE_MEMORY(pszGetMimeType); nfc_ndef_record_destroy(g_hRecord););

	if ( pszGetMimeType == NULL )
	{
		FPRINTF("[Line : %d][%s] nfc_ndef_record_get_mime_type returns NULL mime type\\n", __LINE__, API_NAMESPACE);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	if ( strcmp(pszGetMimeType, pszMimeType) != 0 )
	{
		FPRINTF("[Line : %d][%s] After 'nfc_ndef_record_get_mime_type' Mime type value mismatch (set value is: %s and get value is: %s)\\n", __LINE__, API_NAMESPACE, pszMimeType, pszGetMimeType);
		FREE_MEMORY(pszGetMimeType);
		nfc_ndef_record_destroy(g_hRecord);
		return 1;
	}
	FREE_MEMORY(pszGetMimeType);

	nRet = nfc_ndef_record_destroy(g_hRecord);
	PRINT_RESULT_NORETURN(NFC_ERROR_NONE, nRet, "nfc_ndef_record_destroy", NFCGetError(nRet));	

	return 0;
}

/** @} */ //end of itc-nfc
/** @} */ //end of itc-nfc-testcases
