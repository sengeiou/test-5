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
#include "ITs-bundle-common.h"

/** @addtogroup itc-bundle
*  @ingroup itc
*  @{
*/

//& set: Bundle

bundle *g_bundle;
bool g_bBundleCreation = false;
bundle_keyval_t *g_BundlestKeyVal;
static GMainLoop *mainloop;

/**
* @function 		ITs_bundle_startup
* @description	 	Called before each test, created bundle handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_bundle_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Bundle_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bBundleCreation )
	{
		g_bBundleCreation = false;

		int nRet = bundle_free (g_bundle);
		if ( nRet != BUNDLE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] bundle_free failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, BundleGetError(nRet), nRet);
			return;
		}
	}

	g_bundle = bundle_create();
	if ( g_bundle == NULL )
	{
		FPRINTF("[Line : %d][%s] Unable to create bundle\\n", __LINE__, API_NAMESPACE);
		g_bBundleCreation = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Bundle created successfully\\n", __LINE__, API_NAMESPACE);
		g_bBundleCreation = true;
	}

	return;
}

/**
* @function 		ITs_bundle_cleanup
* @description	 	Called after each test, destroys bundle handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_bundle_cleanup(void)
{
	if ( g_bBundleCreation )
	{
		int nRet = bundle_free (g_bundle);
		g_bBundleCreation = false;

		if ( nRet != BUNDLE_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] bundle_free failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, BundleGetError(nRet), nRet);
			return;
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Bundle_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}


/**
* @function 		KeyValuePairInBundleCallback
* @description	 	callback function for each key-value pairs in a given bundle
* @parameter		key: Bundle Key, type: type of value of given key, bundle_keyval_t: The key-value pair handle, user_data: User data sent to callback
* @return 			NA
*/
void KeyValuePairInBundleCallback(const char *key, const int type, const bundle_keyval_t *kv, void *user_data) 
{
	g_BundlestKeyVal = (bundle_keyval_t *)kv;

	FPRINTF("[Line : %d][%s] reached bundle key value pairs callback\\n", __LINE__, API_NAMESPACE);

	if ( mainloop )
	{
		g_main_loop_quit(mainloop);
	}
	return;
}

/** @addtogroup itc-bundle-testcases
*  @brief 		Integration testcases for module bundle
*  @ingroup 	itc-bundle
*  @{
*/

//& purpose: Encodes and Decodes Bundle
//& type: auto
/**
* @testcase 			ITc_bundle_encode_decode_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Encode and Decode Bundle
* @scenario				Adds a string type key-value pair into Bundle\\n
* 						Encode the Bundle\n
* 						Decode the Bundle\n
*						Check whether the decoded bundle is the same before encoding, by checking string value with given key
* @apicovered			bundle_encode, bundle_decode
* @passcase				When bundle_encode, bundle_decode are successful.
* @failcase				If target API bundle_encode or bundle_decode fails or any precondition and postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_encode_decode_p(void)
{
	START_TEST;

	bundle_raw *pstBundleRaw;
	int nLength = 0;

	//Precondition

	int nRetVal = bundle_add_str(g_bundle, (char*)KEY1, (char*)KEY1_VALUE);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal));

	nRetVal = bundle_encode(g_bundle,&pstBundleRaw,&nLength);;
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_encode", BundleGetError(nRetVal));
	CHECK_HANDLE(pstBundleRaw,"bundle_encode");
	CHECK_VALUE_INT(nLength,"bundle_encode");

	bundle *tempBundle = bundle_decode(pstBundleRaw,nLength);

        CHECK_HANDLE_CLEANUP(tempBundle, "bundle_decode", FREE_MEMORY(pstBundleRaw));

	char* pTempBundleStr = NULL;
	nRetVal = bundle_get_str(tempBundle, (char *)KEY1, &pTempBundleStr);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_get_str", BundleGetError(nRetVal), FREE_MEMORY(pstBundleRaw);bundle_free(tempBundle));
	CHECK_HANDLE_CLEANUP(pTempBundleStr,"bundle_get_str",FREE_MEMORY(pstBundleRaw);bundle_free(tempBundle));
	if ( strcmp((char *)KEY1_VALUE, pTempBundleStr) != 0 )//not equal
	{
		FPRINTF("[Line : %d][%s] bundle_get_str failed, error returned = %s\\n", __LINE__, API_NAMESPACE,  BundleGetError(nRetVal));
		FREE_MEMORY(pstBundleRaw);
		bundle_free(tempBundle);
		return 1;
	}

	FREE_MEMORY(pstBundleRaw);
	bundle_free(tempBundle);

	return 0;
}

//& purpose: Add StringArray and Get String Array
//& type: auto
/**
* @testcase 			ITc_bundle_add_get_str_array_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Add String Array, Set its element and Get String Array
* @scenario				Add Empty StringArray with defined length\n
* 						Set StringArray Elements\n
* 						Get StringArray
* @apicovered			bundle_add_str_array and bundle_get_str_array
* @passcase				When bundle_add_str_array and bundle_get_str_array are successful.
* @failcase				If target API's bundle_add_str_array or bundle_get_str_array fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_add_get_str_array_p(void)
{
	START_TEST;

	const char **pszStringArray = (const char *[]){"aaa", "bbb", "ccc"};
	int nStringArrayLength =  3;

	int nRetVal = bundle_add_str_array(g_bundle, (char *)KEY1, pszStringArray, nStringArrayLength); // add a String-array with length 3
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str_array", BundleGetError(nRetVal));

	const char **pStringArrayOutput = NULL;
	int nLengthOutput = 0;

	pStringArrayOutput = bundle_get_str_array(g_bundle, (const char *)KEY1, &nLengthOutput);
	if ( pStringArrayOutput == NULL || (nLengthOutput != nStringArrayLength) )
	{
		FPRINTF("[Line : %d][%s] bundle_get_str_array failed, pStringArrayOutput returned = %s\\n", __LINE__, API_NAMESPACE, (char *)pStringArrayOutput);
		nRetVal = bundle_del(g_bundle, (char *)KEY1);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}
	else 
	{
		int nCount = 0;
		for ( nCount =0; nCount < nStringArrayLength; nCount++ )
		{
			if ( strcmp(pszStringArray[nCount], pStringArrayOutput[nCount]) != 0 )//not equal 
			{
				FPRINTF("[Line : %d][%s]bundle_get_str_array failed, as returned values of getByte Array %d element not matched with original Value %s\\n", __LINE__, API_NAMESPACE, nCount, pStringArrayOutput[nCount]);
				nRetVal = bundle_del(g_bundle, (char *)KEY1);
				PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
				return 1;		
			}
		}
	}

	nRetVal = bundle_del(g_bundle, (char *)KEY1);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
	return 0;
}

//& purpose: Create Bundle Add key value Pair to Bundle And Frees given bundle object with key-value pairs in it.
//& type: auto
/**
* @testcase 			ITc_bundle_create_add_str_free_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a Bundle, Add key value-pair's, and Frees given bundle object with key-value pairs in it
* @scenario				Create a Bundle\n
*						Adds a key-value pair into bundle\n
*						Frees given bundle object with key-value pairs in it
* @apicovered			bundle_create, bundle_add_str, bundle_free						
* @passcase				When bundle_create, or bundle_free are successful.
* @failcase				If target API's bundle_create or bundle_free fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_create_add_str_free_p(void)
{
	START_TEST;

	char szKey[20] = {0};
	char szValue[20] = {0};
	bundle *pBundle = NULL;

	pBundle = bundle_create();

        CHECK_HANDLE(pBundle, "bundle_create");

	snprintf(szKey, sizeof(szKey)-1, "KEY%d", 1);
	snprintf(szValue, sizeof(szValue)-1, "VALUE%d", 1);

	int nRetVal = bundle_add_str(pBundle, szKey, szValue);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal), bundle_free(pBundle));

	nRetVal = bundle_free(pBundle);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_free", BundleGetError(nRetVal));

	return 0;
}

//& purpose:  Adds a Byte Key Value pair into a given bundle And Gets Value of given key(byte) from the bundle
//& type: auto
/**
* @testcase 			ITc_bundle_add_get_byte_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a byte type key-value pair into a given bundle And Gets a value from a given byte key
* @scenario				Adds a byte type key-value pair into a given bundle And Gets a value from a given byte key
* @apicovered			bundle_add_byte, bundle_get_byte					
* @passcase				When bundle_add_byte, bundle_get_byteare successful.
* @failcase				If target API's bundle_add_byte or bundle_get_byte fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_add_get_byte_p(void)
{
	START_TEST;

	char szKeyByte[20] = {0};
	char szValueByte[20] = {0};
	snprintf(szKeyByte, sizeof(szKeyByte)-1, "KEY%dB", 1);
	snprintf(szValueByte, sizeof(szValueByte)-1, "VALUE%dB", 1);

	int nRetVal = bundle_add_byte(g_bundle, szKeyByte, szValueByte, 20);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_byte", BundleGetError(nRetVal));

	unsigned char *pTempByteValue = NULL;
	size_t  nByteSize = 0;

	nRetVal = bundle_get_byte(g_bundle, (const char *)szKeyByte, (void **)&pTempByteValue, &nByteSize);
	if ( nRetVal != BUNDLE_ERROR_NONE || pTempByteValue == NULL || (strcmp((char *)szValueByte, (char *)pTempByteValue) != 0) || (nByteSize!= 20) )
	{
		FPRINTF("[Line : %d][%s] bundle_get_byte failed, error returned = %s for key = %s\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal), (char *)szKeyByte);
		nRetVal = bundle_del(g_bundle, (char *)szKeyByte);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	nRetVal =  bundle_del(g_bundle, (char *)szKeyByte);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));		

	return 0;
}

//& purpose:  Adds a String Key Value pair into a given bundle And Gets Value of given key(String) from the bundle
//& type: auto
/**
* @testcase 			ITc_bundle_add_get_str_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a String type key-value pair into a given bundle And Gets a value from a given String key
* @scenario				Adds a String type key-value pair into a given bundle And Gets a value from a given String key
* @apicovered			bundle_add_str, bundle_get_str					
* @passcase				When bundle_add_str, bundle_get_str are successful.
* @failcase				If target API's bundle_add_str or bundle_get_str fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_add_get_str_p(void)
{
	START_TEST;

	int nRetVal = bundle_add_str(g_bundle, (char *)KEY1, (char *)KEY1_VALUE);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal));		

	char *tempStrValue = NULL;
	nRetVal = bundle_get_str(g_bundle, (char *)KEY1, &tempStrValue);
	if(tempStrValue == NULL)
	{
		FPRINTF("[Line : %d][%s] bundle_get_str value of tempStrValue is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( nRetVal != BUNDLE_ERROR_NONE  || (strcmp((char *)KEY1_VALUE, tempStrValue) != 0))
	{
		FPRINTF("[Line : %d][%s] bundle_get_str failed, error returned = %s for key = %s\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal), (char *)KEY1);

		nRetVal = bundle_del(g_bundle, (char *)KEY1);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));		
		return 1;
	}

	nRetVal = bundle_del(g_bundle, (char *)KEY1);	
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));		

	return 0;
}

//& purpose: Get the Type of Key Values added in the Bundle and Deletes added key-value pair from the given bundle
//& type: auto
/**
* @testcase 			ITc_bundle_get_type_del_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get the Type of Key Values added in the Bundle and Deletes added key-value pair from the given bundle 
* @scenario				Adds byte and string type key-value pair into a given bundle\n
*						Gets the type of added key-values pairs of the given bundle\n
*						Delete the added key values pair from the given bundle
* @apicovered			bundle_get_type, bundle_del					
* @passcase				Whenbundle_get_type, bundle_del are successful.
* @failcase				If target API's bundle_get_type or bundle_del fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_get_type_del_p(void)
{
	START_TEST;

	char szKey[20] = {0};
	char szValue[20] = {0};

	snprintf(szKey, sizeof(szKey)-1, "KEY%d", 1);
	snprintf(szValue, sizeof(szValue)-1, "VALUE%d", 1);

	int nRetVal = bundle_add_str(g_bundle, szKey, szValue);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal));		

	char szKeyByte[20] = {0};
	char szValueByte[20] = {0};
	snprintf(szKeyByte, sizeof(szKeyByte)-1, "KEY%dB", 1);
	snprintf(szValueByte, sizeof(szValueByte)-1, "VALUE%dB", 1);

	nRetVal = bundle_add_byte(g_bundle, szKeyByte, szValueByte, 20);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_byte", BundleGetError(nRetVal));		

	nRetVal =  bundle_get_type(g_bundle, (char *)szKey);
	PRINT_RESULT_CLEANUP(BUNDLE_TYPE_STR, nRetVal, "bundle_get_type", BundleGetError(nRetVal),
		bundle_del(g_bundle, (char *)szKey);nRetVal = bundle_del(g_bundle, (char *)szKeyByte));		

	nRetVal =  bundle_get_type(g_bundle, (char *)szKeyByte);
	PRINT_RESULT_CLEANUP(BUNDLE_TYPE_BYTE, nRetVal, "bundle_get_type", BundleGetError(nRetVal),
		bundle_del(g_bundle, (char *)szKey);nRetVal = bundle_del(g_bundle, (char *)szKeyByte));		

	nRetVal =  bundle_del(g_bundle, (char *)szKey);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_get_type", BundleGetError(nRetVal),
		bundle_del(g_bundle, (char *)szKey);nRetVal = bundle_del(g_bundle, (char *)szKeyByte));		

	nRetVal = bundle_del(g_bundle, (char *)szKeyByte);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));

	return 0;
}

//& purpose: Iterates a callback function for each key-value pairs in a given bundle And fetch information inside key-value pair handle.
//& type: auto
/**
* @testcase 			ITc_bundle_key_val_target_apis_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a Bundle, Add String type key-pair's, Iterates a callback function for key-value pairs added in a given bundle and Destroy the Bundle.
* @scenario				Create a Bundle\\n
*						Adds a string type key-value pair into bundle\n
*						Adds a strings array type key-value pair into a given bundle\n
* 						Iterates a callback function for each key-value pairs in a given bundle\n
*						Fetch information inside key-value pair handle provided by callback\n
*						Frees given bundle object with key-value pairs in it
* @apicovered			bundle_foreach, bundle_keyval_get_type, bundle_keyval_type_is_array, bundle_keyval_get_basic_val, bundle_keyval_get_array_val 
* @passcase				When bundle_create, bundle_add_str, bundle_keyval_get_type, bundle_keyval_type_is_array, bundle_keyval_get_basic_val, bundle_keyval_get_array_val, bundle_free are successful.
* @failcase				If target API's bundle_keyval_get_type or bundle_keyval_type_is_array or bundle_keyval_get_basic_val or bundle_keyval_get_array_val fails or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_key_val_target_apis_p(void)
{
	START_TEST;

	char szKey[20] = {0};
	char szValue[20] = {0};
	g_BundlestKeyVal = NULL;
	snprintf(szKey, sizeof(szKey)-1, "KEY%d", 1);
	snprintf(szValue, sizeof(szValue)-1, "VALUE%d", 1);

	int nRetVal = bundle_add_str(g_bundle, szKey, szValue);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal));

	bundle_foreach(g_bundle, KeyValuePairInBundleCallback, NULL);

	if ( g_BundlestKeyVal == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_foreach failed, with key %s\\n", __LINE__, API_NAMESPACE, szKey);
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	nRetVal = bundle_keyval_get_type(g_BundlestKeyVal);
	if (nRetVal < 0) 
	{
		g_BundlestKeyVal = NULL;
		FPRINTF("[Line : %d][%s] bundle_foreach failed, with key %s\\n", __LINE__, API_NAMESPACE, szKey);
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	FPRINTF("[Line : %d][%s] Type of a key-value pair = %s for key = %s\\n", __LINE__, API_NAMESPACE, BundleGetTypePropertyValue(nRetVal), szKey);

	nRetVal = bundle_keyval_type_is_array(g_BundlestKeyVal);
	if ( nRetVal != BUNDLE_ERROR_NONE )
	{
		g_BundlestKeyVal = NULL;			
		FPRINTF("[Line : %d][%s] bundle_foreach failed, with key %s\\n", __LINE__, API_NAMESPACE, szKey);
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	void *pBasicVal = NULL;
	size_t nBasicSize = 0;

	nRetVal = bundle_keyval_get_basic_val(g_BundlestKeyVal, &pBasicVal, &nBasicSize);
	if (nRetVal != BUNDLE_ERROR_NONE || pBasicVal == NULL || (strcmp(szValue, (char *)pBasicVal) != 0) || (nBasicSize == 0)) 
	{
		FPRINTF("[Line : %d][%s] bundle_keyval_get_basic_val failed, with key = %s as returned basic value = %s and expected returned value = %s\\n", __LINE__, API_NAMESPACE, szKey, (char *)pBasicVal, szValue);
		g_BundlestKeyVal = NULL;
		pBasicVal = NULL;
		nBasicSize = 0;
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	pBasicVal = NULL;
	g_BundlestKeyVal = NULL;
	nBasicSize = 0;
	nRetVal = bundle_del(g_bundle, szKey);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));

	const char *pszStringArray[] = {"abc", "bcd", "cde"};
	const int nStringArrayLength = 3;
	nRetVal = bundle_add_str_array(g_bundle, (const char *)szKey, pszStringArray, nStringArrayLength); // add a String array
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str_array", BundleGetError(nRetVal));
	bundle_foreach(g_bundle, KeyValuePairInBundleCallback, NULL); 

	if ( g_BundlestKeyVal == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_foreach failed, with key %s\\n", __LINE__, API_NAMESPACE, szKey);
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));
		return 1;
	}

	nRetVal = bundle_keyval_type_is_array(g_BundlestKeyVal);
	if (nRetVal != 1) 
	{
		FPRINTF("[Line : %d][%s] The ErrorCode = %s\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal));
		FPRINTF("[Line : %d][%s] bundle_keyval_type_is_array failed, with key = %s\\n", __LINE__, API_NAMESPACE, szKey);
		g_BundlestKeyVal = NULL;
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));			
		return 1;	
	}

	void **pKeyValueArray = NULL;
	unsigned int nKeyValueLength  = 0;
	size_t *pKeyValueArrayElemSize = NULL;

	nRetVal = bundle_keyval_get_array_val(g_BundlestKeyVal, &pKeyValueArray, &nKeyValueLength, &pKeyValueArrayElemSize);
	if ( nRetVal != BUNDLE_ERROR_NONE || pKeyValueArray == NULL || nKeyValueLength != nStringArrayLength || pKeyValueArrayElemSize == NULL ) 
	{
		FPRINTF("[Line : %d][%s] bundle_keyval_get_array_val Failed with ErrorCode = %s\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal));
		FPRINTF("[Line : %d][%s] The Returned Array Length = %d, And Expected Length = %d\\n", __LINE__, API_NAMESPACE, nKeyValueLength, nStringArrayLength);
		g_BundlestKeyVal = NULL;
		pKeyValueArray = NULL;
		pKeyValueArrayElemSize = NULL;
		nRetVal = bundle_del(g_bundle, szKey);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));	
		return 1;
	}

	pKeyValueArray = NULL;
	pKeyValueArrayElemSize = NULL;
	g_BundlestKeyVal = NULL;
	nRetVal = bundle_del(g_bundle, szKey);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));	
	return 0;
}


//& purpose: Get the Total Count of Key Value pairs inside given bundle
//& type: auto
/**
* @testcase 			ITc_bundle_get_count_p
* @since_tizen			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get the Total Count of Key Value pairs inside given bundle
* @scenario				Create a Bundle\n
*						Adds 3 Times a string type key-value pair into bundle\n
*						Use bundle_get_count to verify the count\n
*						Frees given bundle object with key-value pairs in it
* @apicovered			bundle_add_str, bundle_get_count
* @passcase				When bundle_get_count or any precondition or postcondition API successful.
* @failcase				If target API's bundle_get_count or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_get_count_p(void)
{
	START_TEST;
	int nRetVal = -1;
	char szKey[20] = {0};
	char szValue[20] = {0};
	int nCounter = 0;

	nRetVal = bundle_add_str(g_bundle,(char *)KEY1, (char *)KEY1_VALUE); 
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal));		
	nCounter++;

	nRetVal = bundle_add_str(g_bundle,(char *)KEY2, (char *)KEY2_VALUE); 
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal),
		bundle_del(g_bundle,(char *)KEY1));			
	nCounter++;

	snprintf(szKey, sizeof(szKey)-1, "KEY%d", 1);
	snprintf(szValue, sizeof(szValue)-1, "VALUE%d", 1);

	nRetVal = bundle_add_str(g_bundle,szKey, szValue); 
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal) , 
		bundle_del(g_bundle,(char *)KEY1);bundle_del(g_bundle,(char *)KEY2));
	nCounter++;

	nRetVal =  bundle_get_count(g_bundle);
	if (nRetVal != nCounter) 
	{
		FPRINTF("[Line : %d][%s] bundle_get_count failed, as Actual Count = %d not equal to expected count = %d\\n", __LINE__, API_NAMESPACE, nRetVal, nCounter);
		bundle_del(g_bundle,(char *)KEY1);
		bundle_del(g_bundle,(char *)KEY2);
		bundle_del(g_bundle, szKey);
		return 1;
	}

	nRetVal = bundle_del(g_bundle,(char *)KEY1);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal) ,
		bundle_del(g_bundle,(char *)KEY2);bundle_del(g_bundle, szKey));	

	nRetVal = bundle_del(g_bundle,(char *)KEY2);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal),
		bundle_del(g_bundle, szKey));	

	nRetVal = bundle_del(g_bundle, szKey);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_del", BundleGetError(nRetVal));	

	return 0;
}

//& Duplicates a given bundle object
//& type: auto
/**
* @testcase 			ITc_bundle_dup_p
* @since_tizen			2.4
* @author            	SRID(ajay.kr1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Duplicates a given bundle object
* @scenario				Duplicates a given bundle object
* @apicovered			bundle_dup
* @passcase				When bundle_dup is successful.
* @failcase				If target API's bundle_dup or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_dup_p(void)
{
	START_TEST;

	int nRetVal = -1;
	bundle *pBundle = NULL;
	bundle *pDupBundle = NULL;
	char *tempStrValue = NULL;

	pBundle = bundle_create();
	if ( pBundle == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = bundle_add_str(pBundle, (char *)KEY1, (char *)KEY1_VALUE);
	PRINT_RESULT_CLEANUP(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_str", BundleGetError(nRetVal),bundle_free(pBundle));

	pDupBundle = bundle_dup(pBundle);
	if ( pDupBundle == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = bundle_get_str(pDupBundle, (char *)KEY1, &tempStrValue);
	if ( nRetVal != BUNDLE_ERROR_NONE || tempStrValue == NULL || (strcmp((char *)KEY1_VALUE, tempStrValue) != 0))
	{
		FPRINTF("[Line : %d][%s] bundle_get_str failed, error returned = %s for key = %s\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal), (char *)KEY1);

		nRetVal = bundle_free(pDupBundle);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_free", BundleGetError(nRetVal));

		nRetVal = bundle_free(pBundle);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_free", BundleGetError(nRetVal));

		return 1;
	}

	nRetVal = bundle_free(pDupBundle);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_free", BundleGetError(nRetVal));

	nRetVal = bundle_free(pBundle);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_free", BundleGetError(nRetVal));

	return 0;
}

//& purpose:  Adds a byte array into a given bundle
//& type: auto
/**
* @testcase 			ITc_bundle_add_byte_array_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Adds a byte array into a given bundle
* @scenario			Adds a byte array type key-value pair into a given bundle
* @apicovered			bundle_add_byte_array
* @passcase			When bundle_add_byte_array successful.
* @failcase			If target API's bundle_add_byte_array or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_add_byte_array_p(void)
{
	START_TEST;

	int nRetVal = bundle_add_byte_array(g_bundle, (char *)KEY1, 4);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_byte_array", BundleGetError(nRetVal));

	nRetVal = bundle_get_type(g_bundle, (char *)KEY1);
	PRINT_RESULT(BUNDLE_TYPE_BYTE_ARRAY, nRetVal, "bundle_get_type", BundleGetError(nRetVal));

	return 0;
}

//& purpose:  Set and Get byte array into a given bundle
//& type: auto
/**
* @testcase 			ITc_bundle_set_get_byte_array_p
* @since_tizen			5.5
* @author            		SRID(manoj.g2)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @description			Set and Get byte array into a given bundle
* @scenario			Set and Get byte array into a given bundle
* @apicovered			bundle_set_byte_array_element and bundle_get_byte_array
* @passcase			When bundle_set_byte_array_element and bundle_get_byte_array successful.
* @failcase			If target API's bundle_set_byte_array_element and bundle_get_byte_array	or any precondition or postcondition API fails
* @precondition			Bundle must be created
* @postcondition		Bundle must be released
*/
int ITc_bundle_set_get_byte_array_p(void)
{
	START_TEST;

	void **byte_array = NULL;
	unsigned int len = 0;
	unsigned int *arrELementSize = NULL;
	const char **pszStringArray = (const char *[]){"aaa", "bbb", "ccc"};
	int byteArrSize = 3;

	int nRetVal = bundle_add_byte_array(g_bundle, (char *)KEY1, byteArrSize);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_add_byte_array", BundleGetError(nRetVal));

	for(int index =0;index<byteArrSize;index++)
	{
		nRetVal = bundle_set_byte_array_element(g_bundle, (char *)KEY1, index, pszStringArray[index], 4);
		PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_set_byte_array_element", BundleGetError(nRetVal));
	}

	nRetVal = bundle_get_byte_array(g_bundle, (char *)KEY1, &byte_array, &len, &arrELementSize);
	PRINT_RESULT(BUNDLE_ERROR_NONE, nRetVal, "bundle_get_byte_array", BundleGetError(nRetVal));

	CHECK_HANDLE(byte_array, "bundle_get_byte_array");
	if(len <= 0 || arrELementSize == NULL || arrELementSize[0] != 4 || arrELementSize[1] != 4 || arrELementSize[2] != 4)
	{
		FPRINTF("[Line : %d][%s] bundle_get_byte_array failed, element size is wrong\\n", __LINE__, API_NAMESPACE, BundleGetError(nRetVal));
		return 1;
	}

	return 0;
}


/** @} */
/** @} */
