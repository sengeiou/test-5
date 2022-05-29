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
#include "ITs-base-utils-common.h"

struct timeval g_stBaseUtilsStartTime;
struct mallinfo g_stBaseUtilsMemInfo;


/**
* @function 		ITs_base_utils_ulocale_startup
* @description	 	Called before each test. Get the default locale to be used
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_ulocale_startup(void)
{
	g_bBaseUtilsInitFlag = false;		
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_pszDefaultLocale = I18N_ULOCALE_US;
	g_bBaseUtilsInitFlag = true;
	return;
}
/**
* @function 		ITs_base_utils_ulocale_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_ulocale_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;
	return;
}

//& type: auto
//& purpose: Gets the language code for the specified locale.
/**
 * @testcase				ITc_i18n_ulocale_get_language_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Gets the language code for the specified locale.
 * @apitarget				i18n_ulocale_get_language
 * @apicovered				i18n_ulocale_get_language
 * @passcase				When i18n_ulocale_get_language is successful.
 * @failcase				If target i18n_ulocale_get_language api fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_get_language_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	char pstLanguage[I18N_LANG_CAPACITY] = {0,};
	int nLanguageBufSize;

	nRetVal = i18n_ulocale_get_language(g_pszDefaultLocale, pstLanguage, I18N_LANG_CAPACITY, &nLanguageBufSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_language", BaseUtilsGetError(nRetVal));
	if(nLanguageBufSize > I18N_LANG_CAPACITY)
	{
		FPRINTF("\\n[Line : %d][%s] As Returned Language Buffer Size(%d) is greater than language capacity(%d), the returned language code=%s is truncated.", __LINE__, API_NAMESPACE, nLanguageBufSize, I18N_LANG_CAPACITY, pstLanguage);
	}
	return 0;
}

//& type: auto
//& purpose: Gets the language code for the specified locale.
/**
 * @testcase				ITc_i18n_ulocale_get_display_name_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Gets the language code for the specified locale.
 * @apitarget				i18n_ulocale_get_display_name
 * @apicovered				i18n_ulocale_get_display_name
 * @passcase				When i18n_ulocale_get_display_name is successful.
 * @failcase				If target i18n_ulocale_get_display_name api fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_get_display_name_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	
	int nDisplayNameBufSize = -1;
	i18n_uchar localeDisplayName[I18N_RESULT_LEN] = { 0, };
	
	nRetVal = i18n_ulocale_get_display_name(g_pszDefaultLocale, g_pszDefaultLocale, localeDisplayName, I18N_RESULT_LEN, &nDisplayNameBufSize);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_display_name", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(localeDisplayName, "i18n_ulocale_get_display_name");
	CHECK_RETURN_VAL(nDisplayNameBufSize, "i18n_ulocale_get_display_name");
	
	return 0;
}

//& type: auto
//& purpose: Set and Gets default locale.
/**
 * @testcase				ITc_i18n_ulocale_set_get_default_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Set default locale and Get default locale. 	
 * @apitarget				i18n_ulocale_set_default, i18n_ulocale_get_default						
 * @apicovered				i18n_ulocale_set_default, i18n_ulocale_get_default
 * @passcase				When i18n_ulocale_set_default, i18n_ulocale_get_default are successful.
 * @failcase				If target i18n_ulocale_set_default or i18n_ulocale_get_default fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_set_get_default_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_set_default(LOCALE);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_set_default", BaseUtilsGetError(nRetVal));

	const char *pszGetDefaultLocale = NULL;
	nRetVal = i18n_ulocale_get_default(&pszGetDefaultLocale);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_default", BaseUtilsGetError(nRetVal));
	if(strcmp(LOCALE, pszGetDefaultLocale) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ulocale_get_default failed, as Actual Default Locale=%s not matched with the expected Locale=%s \n", __LINE__, API_NAMESPACE, pszGetDefaultLocale, LOCALE );
		return 1;
	}
	const char *pszSetDefaultLocale = NULL;
	nRetVal = i18n_ulocale_set_default(pszSetDefaultLocale);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_set_default", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Gets the specified locale from a list of all available locale.
/**
 * @testcase				ITc_i18n_ulocale_get_available_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Gets the specified locale from a list of all available locale.
 * @apitarget				i18n_ulocale_get_available
 * @apicovered				i18n_ulocale_get_available
 * @passcase				When i18n_ulocale_get_available is successful.
 * @failcase				If target i18n_ulocale_get_available api fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_get_available_p(void)
{	
	START_TEST;
	const char *pRet = NULL;
	
	int32_t nCount = i18n_ulocale_count_available();
	CHECK_RETURN_VAL(nCount, "i18n_ulocale_count_available");
	
	int32_t nIndex = nCount;
	if(nCount > 0)
	{
		nIndex = nCount -1;
	}
	
	pRet = i18n_ulocale_get_available(nIndex);
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][base-util_ITC] i18n_ulocale_get_available failed\\n", __LINE__);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Gets the country code for the specified locale.
/**
 * @testcase				ITc_i18n_ulocale_get_country_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Gets the country code for the specified locale.
 * @apitarget				i18n_ulocale_get_country
 * @apicovered				i18n_ulocale_get_country
 * @passcase				When i18n_ulocale_get_country is successful.
 * @failcase				If target i18n_ulocale_get_country api fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_get_country_p(void)
{	
	START_TEST;
	const char *pLocaleId = I18N_ULOCALE_US;
	char szCountry[I18N_LANG_CAPACITY] = {0,};
	int nCountryCapacity = I18N_LANG_CAPACITY;
	int nError = I18N_ERROR_NONE;
	int32_t nBufSize = -1;
	
	nBufSize = i18n_ulocale_get_country(pLocaleId, szCountry, nCountryCapacity, &nError);
	PRINT_RESULT(I18N_ERROR_NONE, nError, "i18n_ulocale_get_country", BaseUtilsGetError(nError));
	CHECK_RETURN_VAL(nBufSize, "i18n_ulocale_get_country");
	
	return 0;
}


//& type: auto
//& purpose: Gets the size of all available locale list
/**
 * @testcase				ITc_i18n_ulocale_count_available_p
 * @since_tizen 			2.3
 * @author            		SRID(m.khalid)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @scenario				Gets the size of all available locale list.
 * @apitarget				i18n_ulocale_count_available
 * @apicovered				i18n_ulocale_count_available,
 * @passcase				When i18n_ulocale_count_available is successful.
 * @failcase				If target i18n_ulocale_count_available api fails or any precondition and postcondition api fails.
 * @precondition			NA
 * @postcondition			NA 
 */
int ITc_i18n_ulocale_count_available_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_count_available();
	if(nRetVal < 0)
	{
		FPRINTF("[Line : %d][base-util_ITC] i18n_ulocale_count_available failed \\n", __LINE__);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Adds the likely subtags for a provided locale ID, per the algorithm described.
/**
* @testcase				ITc_i18n_ulocale_add_likely_subtags_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Adds the likely subtags for a provided locale ID, per the algorithm described
* @apitarget			i18n_ulocale_add_likely_subtags
* @apicovered			i18n_ulocale_add_likely_subtags
* @passcase				When i18n_ulocale_add_likely_subtags is successful
* @failcase				When i18n_ulocale_add_likely_subtags failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_add_likely_subtags_p(void)
{
	START_TEST;

	const char *pLocaleId = "My_Id";
    char szMaximizedLocaleId[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nMaximizedLocaleIdCapacity = I18N_ULOCALE_CAPACITY;
	
	int nRetVal = i18n_ulocale_add_likely_subtags(pLocaleId, szMaximizedLocaleId, nMaximizedLocaleIdCapacity);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_add_likely_subtags failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the full name for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_canonicalize_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the full name for the specified locale.
* @apitarget			i18n_ulocale_canonicalize
* @apicovered			i18n_ulocale_canonicalize
* @passcase				When i18n_ulocale_canonicalize is successful
* @failcase				When i18n_ulocale_canonicalize failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_canonicalize_p(void)
{
	START_TEST;

	const char *pLocaleId = "My_Id";
    char szName[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nNameCapacity = I18N_ULOCALE_CAPACITY;
	int nBufSize = -1;
	
	nBufSize = i18n_ulocale_canonicalize(pLocaleId, szName, nNameCapacity);
	if( nBufSize == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_canonicalize failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns a locale ID for the specified BCP47 language tag string.
/**
* @testcase				ITc_i18n_ulocale_for_language_tag_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns a locale ID for the specified BCP47 language tag string.
* @apitarget			i18n_ulocale_for_language_tag
* @apicovered			i18n_ulocale_for_language_tag
* @passcase				When i18n_ulocale_for_language_tag is successful
* @failcase				When i18n_ulocale_for_language_tag failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_for_language_tag_p(void)
{
	START_TEST;

	const char *pLangTag = "en";
    char szLocaleId[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nLocaleIdCapacity = I18N_ULOCALE_CAPACITY;
    int32_t nParsedLength;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_for_language_tag(pLangTag, szLocaleId, nLocaleIdCapacity, &nParsedLength);
	if( nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_for_language_tag failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	CHECK_HANDLE(szLocaleId, "i18n_ulocale_for_language_tag");
	
	return 0;
}

//& type: auto
//& purpose: Gets the full name for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_base_name_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the full name for the specified locale.
* @apitarget			i18n_ulocale_get_base_name
* @apicovered			i18n_ulocale_get_base_name
* @passcase				When i18n_ulocale_get_base_name is successful
* @failcase				When i18n_ulocale_get_base_name failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_base_name_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD@currency=USD;president=WHO";
    char szName[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nNameCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_base_name(pLocaleId, szName, nNameCapacity);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_base_name failed. Returned value is -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the layout character orientation for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_character_orientation_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the layout character orientation for the specified locale.
* @apitarget			i18n_ulocale_get_character_orientation
* @apicovered			i18n_ulocale_get_character_orientation
* @passcase				When i18n_ulocale_get_character_orientation is successful
* @failcase				When i18n_ulocale_get_character_orientation failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_character_orientation_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD@currency=USD";
    i18n_ulocale_layout_type_e layout_type;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_character_orientation(pLocaleId, &layout_type);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_character_orientation", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the country name suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_country_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the country name suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_country
* @apicovered			i18n_ulocale_get_display_country
* @passcase				When i18n_ulocale_get_display_country is successful
* @failcase				When i18n_ulocale_get_display_country failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_country_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szCountry[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nCountryCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_country(pLocaleId, pDisplayLocale, szCountry, nCountryCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_country failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Gets the keyword name suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_keyword_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the keyword name suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_keyword
* @apicovered			i18n_ulocale_get_display_keyword
* @passcase				When i18n_ulocale_get_display_keyword is successful
* @failcase				When i18n_ulocale_get_display_keyword failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_keyword_p(void)
{
	START_TEST;

	const char *pKeyword = "currency";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szDest[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nDestCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_keyword(pKeyword, pDisplayLocale, szDest, nDestCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_keyword failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the value of the keyword suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_keyword_value_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the value of the keyword suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_keyword_value
* @apicovered			i18n_ulocale_get_display_keyword_value
* @passcase				When i18n_ulocale_get_display_keyword_value is successful
* @failcase				When i18n_ulocale_get_display_keyword_value failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_keyword_value_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD@currency=USD";
    const char *pKeyword = "currency";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szDest[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nDestCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_keyword_value(pLocaleId, pKeyword, pDisplayLocale, szDest, nDestCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_keyword_value failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Gets the language name suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_language_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the language name suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_language
* @apicovered			i18n_ulocale_get_display_language
* @passcase				When i18n_ulocale_get_display_language is successful
* @failcase				When i18n_ulocale_get_display_language failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_language_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szLanguage[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nLanguageCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_language(pLocaleId, pDisplayLocale, szLanguage, nLanguageCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_language failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the script name suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_script_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the script name suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_script
* @apicovered			i18n_ulocale_get_display_script
* @passcase				When i18n_ulocale_get_display_script is successful
* @failcase				When i18n_ulocale_get_display_script failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_script_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szScript[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nScriptCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_script(pLocaleId, pDisplayLocale, szScript, nScriptCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_script failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the variant name suitable for display for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_display_variant_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the variant name suitable for display for the specified locale.
* @apitarget			i18n_ulocale_get_display_variant
* @apicovered			i18n_ulocale_get_display_variant
* @passcase				When i18n_ulocale_get_display_variant is successful
* @failcase				When i18n_ulocale_get_display_variant failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_display_variant_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
    const char *pDisplayLocale = "en_US";
    i18n_uchar szVariant[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nVariantCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_display_variant(pLocaleId, pDisplayLocale, szVariant, nVariantCapacity);
	if(nRetVal == 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_display_variant failed. Returned value is 0\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the ISO country code for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_iso3_country_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the ISO country code for the specified locale.
* @apitarget			i18n_ulocale_get_iso3_country
* @apicovered			i18n_ulocale_get_iso3_country
* @passcase				When i18n_ulocale_get_iso3_country is successful
* @failcase				When i18n_ulocale_get_iso3_country failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_iso3_country_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
	const char *pRet = NULL;
	
	pRet = i18n_ulocale_get_iso3_country(pLocaleId);
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_iso3_country failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the ISO language code for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_iso3_language_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the ISO language code for the specified locale.
* @apitarget			i18n_ulocale_get_iso3_language
* @apicovered			i18n_ulocale_get_iso3_language
* @passcase				When i18n_ulocale_get_iso3_language is successful
* @failcase				When i18n_ulocale_get_iso3_language failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_iso3_language_p(void)
{
	START_TEST;

	const char *pLocaleId = "zh_Hans_HK_USD";
	const char *pRet = NULL;
	
	pRet = i18n_ulocale_get_iso3_language(pLocaleId);
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_iso3_language failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets a list of all available 2-letter country codes defined in ISO 639.
/**
* @testcase				ITc_i18n_ulocale_get_iso_countries_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a list of all available 2-letter country codes defined in ISO 639.
* @apitarget			i18n_ulocale_get_iso_countries
* @apicovered			i18n_ulocale_get_iso_countries
* @passcase				When i18n_ulocale_get_iso_countries is successful
* @failcase				When i18n_ulocale_get_iso_countries failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_iso_countries_p(void)
{
	START_TEST;

	const char *const *pRet = NULL;
	
	pRet = i18n_ulocale_get_iso_countries();
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_iso_countries failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets a list of all available 2-letter language codes plus additional 3-letter codes.
/**
* @testcase				ITc_i18n_ulocale_get_iso_languages_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a list of all available 2-letter language codes plus additional 3-letter codes.
* @apitarget			i18n_ulocale_get_iso_languages
* @apicovered			i18n_ulocale_get_iso_languages
* @passcase				When i18n_ulocale_get_iso_languages is successful
* @failcase				When i18n_ulocale_get_iso_languages failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_iso_languages_p(void)
{
	START_TEST;
	
	const char *const *pRet = NULL;
	
	pRet = i18n_ulocale_get_iso_languages();
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_iso_languages failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Set/Get the value for a keyword.
/**
* @testcase				ITc_i18n_ulocale_set_get_keyword_value_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets or removes the value of the specified keyword.\n
*						Gets the value for a keyword.\n
*						Match set and get value.
* @apitarget			i18n_ulocale_set_keyword_value, i18n_ulocale_get_keyword_value
* @apicovered			i18n_ulocale_set_keyword_value, i18n_ulocale_get_keyword_value
* @passcase				When i18n_ulocale_set_keyword_value, i18n_ulocale_get_keyword_value are successful
* @failcase				When i18n_ulocale_set_keyword_value or i18n_ulocale_get_keyword_value failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_set_get_keyword_value_p(void)
{
	START_TEST;

	const char *pKeywordName = "currency";
    const char *pKeywordValue = "USD";
    char szBuffer[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nBufferCapacity = I18N_ULOCALE_CAPACITY;
	const char *pLocaleId = "zh_Hans_HK_USD@currency=USD";
	int nRetVal = -1;
	
	i18n_ulocale_set_keyword_value(pKeywordName, pKeywordValue, szBuffer, nBufferCapacity);
	if(strlen(szBuffer) <= 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_set_keyword_value failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRetVal = i18n_ulocale_get_keyword_value(pLocaleId, pKeywordName, szBuffer, nBufferCapacity);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_keyword_value failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(strcmp(pKeywordValue, szBuffer) != 0)
	{
		FPRINTF("[Line : %d][%s] Set and get value not matched\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the Win32 LCID value for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_lcid_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the Win32 LCID value for the specified locale.
* @apitarget			i18n_ulocale_get_lcid
* @apicovered			i18n_ulocale_get_lcid
* @passcase				When i18n_ulocale_get_lcid is successful
* @failcase				When i18n_ulocale_get_lcid failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_lcid_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
	int nRetVal = -1;
	
	i18n_ulocale_get_lcid(pLocaleId);
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_lcid", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the layout line orientation for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_line_orientation_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the layout line orientation for the specified locale.
* @apitarget			i18n_ulocale_get_line_orientation
* @apicovered			i18n_ulocale_get_line_orientation
* @passcase				When i18n_ulocale_get_line_orientation is successful
* @failcase				When i18n_ulocale_get_line_orientation failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_line_orientation_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD@currency=USD";
    i18n_ulocale_layout_type_e layout_type;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_line_orientation(pLocaleId, &layout_type);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_line_orientation", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Gets the I18N locale ID for the specified Win32 LCID value.
/**
* @testcase				ITc_i18n_ulocale_get_locale_for_lcid_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the I18N locale ID for the specified Win32 LCID value.
* @apitarget			i18n_ulocale_get_locale_for_lcid
* @apicovered			i18n_ulocale_get_lcid, i18n_ulocale_get_locale_for_lcid
* @passcase				When i18n_ulocale_get_lcid and i18n_ulocale_get_locale_for_lcid are successful
* @failcase				When i18n_ulocale_get_lcid or i18n_ulocale_get_locale_for_lcid failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_locale_for_lcid_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
    char szLocale[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nLocaleCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	uint32_t nLcid;
	
	nLcid = i18n_ulocale_get_lcid(pLocaleId);
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_get_lcid", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_ulocale_get_locale_for_lcid(nLcid, szLocale, nLocaleCapacity);
	if( nRetVal < 0  )
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_locale_for_lcid failed. Returned value is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the full name for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_name_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the full name for the specified locale.
* @apitarget			i18n_ulocale_get_name
* @apicovered			i18n_ulocale_get_name
* @passcase				When i18n_ulocale_get_name is successful
* @failcase				When i18n_ulocale_get_name failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_name_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
    char szName[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nNameCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_name(pLocaleId, szName, nNameCapacity);
	if( nRetVal <= 0  && strlen(szName) <= 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_name failed.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Truncates the locale ID string to get the parent locale ID.
/**
* @testcase				ITc_i18n_ulocale_get_parent_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Truncates the locale ID string to get the parent locale ID.
* @apitarget			i18n_ulocale_get_parent
* @apicovered			i18n_ulocale_get_parent
* @passcase				When i18n_ulocale_get_parent is successful
* @failcase				When i18n_ulocale_get_parent failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_parent_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
	char szParent[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nParentCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_parent(pLocaleId, szParent, nParentCapacity);
	if( nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_parent failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Gets the script code for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_script_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the script code for the specified locale.
* @apitarget			i18n_ulocale_get_script
* @apicovered			i18n_ulocale_get_script
* @passcase				When i18n_ulocale_get_script is successful
* @failcase				When i18n_ulocale_get_script failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_script_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK";
    char szScript[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nScriptCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_script(pLocaleId, szScript, nScriptCapacity);
	if( nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_script failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the variant code for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_get_variant_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the variant code for the specified locale.
* @apitarget			i18n_ulocale_get_variant
* @apicovered			i18n_ulocale_get_variant
* @passcase				When i18n_ulocale_get_variant is successful
* @failcase				When i18n_ulocale_get_variant failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_get_variant_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
    char szVariant[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nVariantCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_get_variant(pLocaleId, szVariant, nVariantCapacity);
	if( nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s] i18n_ulocale_get_variant failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets an enumeration of keywords for the specified locale.
/**
* @testcase				ITc_i18n_ulocale_keywords_create_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets an enumeration of keywords for the specified locale.
* @apitarget			i18n_ulocale_keywords_create
* @apicovered			i18n_ulocale_keywords_create
* @passcase				When i18n_ulocale_keywords_create is successful
* @failcase				When i18n_ulocale_keywords_create failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_keywords_create_p(void)
{
	START_TEST;
	
	i18n_uenumeration_h keywords = NULL;
	int nRetVal = -1;
	
	nRetVal =i18n_ulocale_keywords_create(I18N_LOCALE_ID, &keywords);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_keywords_create", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Minimizes the subtags for a provided locale ID
/**
* @testcase				ITc_i18n_ulocale_minimize_subtags_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Minimizes the subtags for a provided locale ID.
* @apitarget			i18n_ulocale_minimize_subtags
* @apicovered			i18n_ulocale_minimize_subtags
* @passcase				When i18n_ulocale_minimize_subtags is successful
* @failcase				When i18n_ulocale_minimize_subtags failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_minimize_subtags_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_Hans_HK_USD";
    char szMinimizedLocaleId[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nMinimizedLocaleIdCapacity = I18N_ULOCALE_CAPACITY;
	int nRetVal = -1;
	
	nRetVal =i18n_ulocale_minimize_subtags(pLocaleId, szMinimizedLocaleId, nMinimizedLocaleIdCapacity);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_ulocale_minimize_subtags failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns a well-formed language tag for this locale ID.
/**
* @testcase				ITc_i18n_ulocale_to_language_tag_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns a well-formed language tag for this locale ID.
* @apitarget			i18n_ulocale_to_language_tag
* @apicovered			i18n_ulocale_to_language_tag
* @passcase				When i18n_ulocale_to_language_tag is successful
* @failcase				When i18n_ulocale_to_language_tag failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_to_language_tag_p(void)
{
	START_TEST;
	
	const char *pLocaleId = "zh_HK";
    char szLangTag[I18N_ULOCALE_CAPACITY] = {0,};
    int32_t nLangtagCapacity = I18N_ULOCALE_CAPACITY;
    i18n_ubool bStrict = true;
	int nRetVal = -1;
	
	nRetVal = i18n_ulocale_to_language_tag(pLocaleId, szLangTag, nLangtagCapacity, bStrict);
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_ulocale_to_language_tag failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Checks if the local name is bogus for perticular locale name.
/**
* @testcase				ITc_i18n_ulocale_is_bogus_p
* @since_tizen 			4.0
* @author            	SRID(j.abhishek)
* @reviewer         	SRID(shobhit.v)
* @type 				auto
* @scenario			Checks if the local name is bogus for perticular locale name.
* @apitarget			i18n_ulocale_is_bogus
* @apicovered			i18n_ulocale_is_bogus
* @passcase			When i18n_ulocale_is_bogus is successful
* @failcase			When i18n_ulocale_is_bogus failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ulocale_is_bogus_p(void)
{
	START_TEST;
	int nRetVal = -1;

	i18n_ubool bIsBogusReturn = false;

	/* Added Local's defined in the rootstrap file "base/utils_i18n_types.h" */
	const char *pDisplayLocale[21] = {"zh", "en", "fr", "de", "it", "ja", "ko", "zh_CN", "zh_TW", "en_CA", "fr_CA", "fr_FR", "de_DE", "it_IT", "ja_JP", "ko_KR", "en_GB", "en_US"};

	int nStringSize = sizeof(pDisplayLocale) / sizeof(pDisplayLocale[0]);
	int nStringCounter;

	for ( nStringCounter = 0; nStringCounter < nStringSize; nStringCounter++ )
	{
		nRetVal = i18n_ulocale_is_bogus(pDisplayLocale[nStringCounter], &bIsBogusReturn);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_ulocale_is_bogus", BaseUtilsGetError(nRetVal));

		if(bIsBogusReturn)
		{
			FPRINTF("[Line : %d][%s]i18n_ulocale_is_bogus failed. Given LOCAL VALUE is bogus\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}
