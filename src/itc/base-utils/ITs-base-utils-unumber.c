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

i18n_unumber_format_h num_format;

/**
* @function 		ITs_base_utils_unumber_startup
* @description	 	Called before each test. Creates an i18n_unumber_format_h handle and get default locale
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_unumber_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bBaseUtilsInitFlag = false;
	g_pDefaultTzid = NULL;	
	int nRetVal = -1;
	i18n_uchar *pRet = NULL;
	int nLength = 8;
	g_pszDefaultLocale = I18N_ULOCALE_US;

	nRetVal = i18n_unumber_create(I18N_UNUMBER_DEFAULT, g_pDefaultTzid, nLength, g_pszDefaultLocale, NULL, &num_format);
	if (nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_unumber_create failed in STARTUP, error returned = %s \n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRetVal));
		return;
	}
	if ( num_format == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_unumber_create failed, num_format = NULL\\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_pDefaultTzid = (i18n_uchar*)calloc(strlen(I18N_DEFAULT_T_ZONE) + 1, sizeof(i18n_uchar));
    if (g_pDefaultTzid == NULL) 
	{
		FPRINTF("\\n[Line : %d][%s] g_pDefaultTzid, memory not allocated properly.\n", __LINE__, API_NAMESPACE);
        return;
    }
    pRet = i18n_ustring_copy_ua(g_pDefaultTzid, (char *)I18N_DEFAULT_T_ZONE);
	if(i18n_ustring_get_length(pRet) == 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in start-up.\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_nLengthDefaultTimeZone = i18n_ustring_get_length(g_pDefaultTzid);
	g_bBaseUtilsInitFlag = true;
}
/**
* @function 		ITs_base_utils_udatepg_cleanup
* @description	 	Called after each test. Destroy the created i18n_unumber_format_h handle
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_unumber_cleanup(void)
{
	i18n_unumber_destroy(num_format);
	if(g_pDefaultTzid != NULL)
	{
		free(g_pDefaultTzid);
		g_pDefaultTzid = NULL;
	}
	g_bBaseUtilsInitFlag = false;
}

bool BaseUtilsCheckSetGetValue(double a, double b){
	double epsilon = 0.000000001;
    return fabs(a - b) < epsilon;
}


//& type: auto
//& purpose: Gets a symbol associated with a i18n_unumber_format.
/**
* @testcase				ITc_i18n_unumber_get_symbol_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates and return a new unumber_format for formatting and parsing numbers.\n
*						Gets a symbol associated with a i18n_unumber_format.\n
* 						Destroys a i18n_unumber_format. 	
* @apitarget			i18n_unumber_get_symbol
* @apicovered			i18n_unumber_get_symbol, i18n_unumber_create, i18n_unumber_destroy
* @passcase				When i18n_unumber_get_symbol is successful
* @failcase				If target i18n_unumber_get_symbol or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_get_symbol_p(void)
{
	START_TEST;

	int nLength = -1;
	i18n_unumber_format_h unumber_format = NULL;
	i18n_uchar Symbolbuffer[I18N_UCHAR_CAPACITY];
	int nSymbolBufSize = 0;

	int nRetVal = i18n_unumber_create(I18N_UNUMBER_DEFAULT, g_pDefaultTzid, nLength, g_pszDefaultLocale, NULL, &unumber_format);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_create", BaseUtilsGetError(nRetVal));

	if ( unumber_format == NULL )
	{
		FPRINTF("[Line : %d][%s] i18n_unumber_create failed, unumber_format = NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	i18n_unumber_format_symbol_e eUnumberFormatSymbol[] = {I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL,
		I18N_UNUMBER_GROUPING_SEPARATOR_SYMBOL,
		I18N_UNUMBER_PATTERN_SEPARATOR_SYMBOL,
		I18N_UNUMBER_ZERO_DIGIT_SYMBOL,
		I18N_UNUMBER_PERCENT_SYMBOL,
		I18N_UNUMBER_DIGIT_SYMBOL,
		I18N_UNUMBER_MINUS_SIGN_SYMBOL,
		I18N_UNUMBER_PLUS_SIGN_SYMBOL,
		I18N_UNUMBER_CURRENCY_SYMBOL,
		I18N_UNUMBER_INTL_CURRENCY_SYMBOL,
		I18N_UNUMBER_MONETARY_SEPARATOR_SYMBOL,
		I18N_UNUMBER_EXPONENTIAL_SYMBOL,
		I18N_UNUMBER_PERMILL_SYMBOL,
		I18N_UNUMBER_PAD_ESCAPE_SYMBOL,
		I18N_UNUMBER_INFINITY_SYMBOL,
		I18N_UNUMBER_NAN_SYMBOL,
		I18N_UNUMBER_SIGNIFICANT_DIGIT_SYMBOL,
		I18N_UNUMBER_MONETARY_GROUPING_SEPARATOR_SYMBOL,
		I18N_UNUMBER_ONE_DIGIT_SYMBOL,
		I18N_UNUMBER_TWO_DIGIT_SYMBOL,
		I18N_UNUMBER_THREE_DIGIT_SYMBOL,
		I18N_UNUMBER_FOUR_DIGIT_SYMBOL,
		I18N_UNUMBER_FIVE_DIGIT_SYMBOL,
		I18N_UNUMBER_SIX_DIGIT_SYMBOL,
		I18N_UNUMBER_SEVEN_DIGIT_SYMBOL,
		I18N_UNUMBER_EIGHT_DIGIT_SYMBOL,
		I18N_UNUMBER_NINE_DIGIT_SYMBOL};

	int nEnumSize = sizeof(eUnumberFormatSymbol) / sizeof(eUnumberFormatSymbol[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_unumber_get_symbol with Format Symbol = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatSymbol(eUnumberFormatSymbol[nEnumCounter]));
		nRetVal = i18n_unumber_get_symbol(unumber_format, eUnumberFormatSymbol[nEnumCounter], Symbolbuffer, I18N_UCHAR_CAPACITY, &nSymbolBufSize);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_unumber_get_symbol", BaseUtilsGetError(nRetVal), i18n_unumber_destroy(unumber_format));
	}
	nRetVal = i18n_unumber_destroy(unumber_format);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRetVal, "i18n_unumber_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}


//& type: auto
//& purpose: Creates and Destroy given unumber_format. unumber_format is used for formatting and parsing numbers. 
/**
* @testcase				ITc_i18n_unumber_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates and return a new unumber_format for formatting and parsing numbers.\n
*                       Destroys a i18n_unumber_format. 
* @apitarget			i18n_unumber_create, i18n_unumber_destroy
* @apicovered			i18n_unumber_create, i18n_unumber_destroy
* @passcase				When i18n_unumber_create, i18n_unumber_destroy is successful
* @failcase				When i18n_unumber_create or i18n_unumber_destroy failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_create_destroy_p(void)
{	
	START_TEST;
	int nRetVal = -1;
	i18n_unumber_format_style_e eUnumberFormatStyle[] = {	I18N_UNUMBER_PATTERN_DECIMAL, 
											I18N_UNUMBER_DECIMAL, 
											I18N_UNUMBER_CURRENCY,
											I18N_UNUMBER_PERCENT,
											I18N_UNUMBER_SCIENTIFIC,
											I18N_UNUMBER_SPELLOUT,
											I18N_UNUMBER_ORDINAL,
											I18N_UNUMBER_DURATION,
											I18N_UNUMBER_NUMBERING_SYSTEM,
											I18N_UNUMBER_PATTERN_RULEBASED,
#if defined(MOBILE) || defined(TIZENIOT)
											I18N_UNUMBER_CURRENCY_ISO,
											I18N_UNUMBER_CURRENCY_PLURAL,
#endif				//End MOBILE						
											/*I18N_UNUMBER_CURRENCY_ISO,
											I18N_UNUMBER_CURRENCY_PLURAL,
											I18N_UNUMBER_FORMAT_STYLE_COUNT,*/
											I18N_UNUMBER_DEFAULT};
	int nEnumSize = sizeof(eUnumberFormatStyle) / sizeof(eUnumberFormatStyle[0]);
	int nEnumCounter = 0;

	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
			i18n_unumber_format_h unumber_format = NULL;
			FPRINTF("\\n[Line : %d][%s] Executing i18n_unumber_create with Format Style = %s and default Locale=%s \n", __LINE__, API_NAMESPACE, UnumberGetFormatStyle(eUnumberFormatStyle[nEnumCounter]), g_pszDefaultLocale);
			nRetVal = i18n_unumber_create(eUnumberFormatStyle[nEnumCounter], g_pDefaultTzid, g_nLengthDefaultTimeZone, g_pszDefaultLocale, NULL, &unumber_format);
			PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_create", BaseUtilsGetError(nRetVal));
			
			nRetVal = i18n_unumber_destroy(unumber_format);
			PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_destroy", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Sets the pattern used by an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_apply_pattern_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets the pattern used by an i18n_unumber_format_h.
* @apitarget			i18n_unumber_apply_pattern
* @apicovered			i18n_unumber_apply_pattern
* @passcase				When i18n_unumber_apply_pattern is successful
* @failcase				When i18n_unumber_apply_pattern failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_apply_pattern_p(void)
{
	START_TEST;

    i18n_uchar szPattern[8] = {'#', ',', '#', '#', ',', '#', '#', '#'};
    int nLength = 8;
	int nRetVal = I18N_ERROR_NONE;
	
	nRetVal = i18n_unumber_apply_pattern(num_format, true, szPattern, nLength, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_apply_pattern", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Creates a copy of an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_clone_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Creates a copy of an i18n_unumber_format_h.
* @apitarget			i18n_unumber_clone
* @apicovered			i18n_unumber_clone
* @passcase				When i18n_unumber_clone is successful
* @failcase				When i18n_unumber_clone failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_clone_p(void)
{
	START_TEST;

	i18n_unumber_format_h num_format_clone = NULL;
	int nRetVal = I18N_ERROR_NONE;
	
	nRetVal = i18n_unumber_clone(num_format, &num_format_clone);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_clone", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(num_format_clone, "i18n_unumber_clone");
	
	i18n_unumber_destroy(num_format_clone);
	return 0;
}

//& type: auto
//& purpose: Determines how many locales have decimal formatting patterns available.
/**
* @testcase				ITc_i18n_unumber_count_available_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Determines how many locales have decimal formatting patterns available.
* @apitarget			i18n_unumber_count_available
* @apicovered			i18n_unumber_count_available
* @passcase				When i18n_unumber_count_available is successful
* @failcase				When i18n_unumber_count_available failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_count_available_p(void)
{
	START_TEST;
	
	int nRetVal = -1;
	
	nRetVal = i18n_unumber_count_available();
	if(nRetVal == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_count_available failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Formats a decimal number using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_format_decimal_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Formats a decimal number using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_format_decimal
* @apicovered			i18n_unumber_format_decimal
* @passcase				When i18n_unumber_format_decimal is successful
* @failcase				When i18n_unumber_format_decimal failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_format_decimal_p(void)
{
	START_TEST;

	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	int nBufSize = -1;
	
	nBufSize = i18n_unumber_format_decimal(num_format, "2014.0", 5,  szResult, nResultCapacity, NULL);
	if(nBufSize == -1 || i18n_ustring_get_length(szResult) <= 0)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_format_decimal failed.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Formats a double using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_format_double_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Formats a double using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_format_double
* @apicovered			i18n_unumber_format_double
* @passcase				When i18n_unumber_format_double is successful
* @failcase				When i18n_unumber_format_double failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_format_double_p(void)
{
	START_TEST;
	
	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	int nBufSize = -1;
	
	nBufSize = i18n_unumber_format_double(num_format, 2014.0, szResult, nResultCapacity, NULL);
	if(nBufSize == -1 || i18n_ustring_get_length(szResult) <= 0)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_format_double failed.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Formats a double currency amount using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_format_double_currency_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Formats a double currency amount using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_format_double_currency
* @apicovered			i18n_unumber_format_double_currency
* @passcase				When i18n_unumber_format_double_currency is successful
* @failcase				When i18n_unumber_format_double_currency failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_format_double_currency_p(void)
{
	START_TEST;
	
	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
    char *pCurrency = "KRW";
    i18n_uchar *pCurrencyTemp = NULL;
    pCurrencyTemp = (i18n_uchar*)calloc(strlen(pCurrency) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(pCurrencyTemp, pCurrency);
	int nBufSize = -1;
	
	nBufSize = i18n_unumber_format_double_currency(num_format, 2014.0, pCurrencyTemp, szResult, nResultCapacity, NULL);
	if(nBufSize == -1 || i18n_ustring_get_length(szResult) <= 0)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_format_double_currency failed.\\n", __LINE__, API_NAMESPACE);
		free(pCurrencyTemp);
		return 1;
	}
	free(pCurrencyTemp);
	return 0;
}

//& type: auto
//& purpose: Formats an int64 using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_format_int64_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Formats an int64 using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_format_int64
* @apicovered			i18n_unumber_format_int64
* @passcase				When i18n_unumber_format_int64 is successful
* @failcase				When i18n_unumber_format_int64 failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_format_int64_p(void)
{
	START_TEST;

	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	int nBufSize = -1;
		
	nBufSize = i18n_unumber_format_int64(num_format, 1994, szResult, nResultCapacity, NULL);
	if(nBufSize == -1 || i18n_ustring_get_length(szResult) <= 0)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_format_int64 failed.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Set/Gets a numeric attribute associated with an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_set_get_attribute_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set a numeric attribute associated with an i18n_unumber_format_h.\n
*						Gets a numeric attribute associated with an i18n_unumber_format_h.
* @apitarget			i18n_unumber_set_attribute, i18n_unumber_get_attribute
* @apicovered			i18n_unumber_set_attribute, i18n_unumber_get_attribute
* @passcase				When i18n_unumber_set_attribute and i18n_unumber_get_attribute are successful
* @failcase				When i18n_unumber_set_attribute or i18n_unumber_get_attribute failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_set_get_attribute_p(void)
{
	START_TEST;

	int nRetVal = -1;
	int nGetAttr = -1;
	int nPadEnumVal = 1;
	i18n_unumber_format_attribute_e eUnumberFormatAttr[] = {I18N_UNUMBER_PARSE_INT_ONLY,                   
															I18N_UNUMBER_GROUPING_USED,                   
															I18N_UNUMBER_MAX_INTEGER_DIGITS,             
															I18N_UNUMBER_MIN_INTEGER_DIGITS,               
															I18N_UNUMBER_INTEGER_DIGITS,                   
															I18N_UNUMBER_MAX_FRACTION_DIGITS,              
															I18N_UNUMBER_MIN_FRACTION_DIGITS,              
															I18N_UNUMBER_FRACTION_DIGITS,                  
															I18N_UNUMBER_MULTIPLIER,                       
															I18N_UNUMBER_GROUPING_SIZE,                    
															I18N_UNUMBER_ROUNDING_MODE,                                   
															I18N_UNUMBER_FORMAT_WIDTH,                     
															I18N_UNUMBER_PADDING_POSITION,                 
															I18N_UNUMBER_SECONDARY_GROUPING_SIZE,          
															I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN,
															I18N_UNUM_SCALE
															};
	
	int nUnumberFormatAttrSize = sizeof(eUnumberFormatAttr)/sizeof(eUnumberFormatAttr[0]);
	int nIndex ;
	for(nIndex = 0; nIndex < nUnumberFormatAttrSize; nIndex++)
	{
		if(eUnumberFormatAttr[nIndex] == I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN){
			nRetVal = i18n_unumber_set_attribute(num_format, eUnumberFormatAttr[nIndex], false); // As per developer request need to pass parameter as bool(true/false) instead of nIndex 
		}
		else if(eUnumberFormatAttr[nIndex] == I18N_UNUMBER_PADDING_POSITION){
			nRetVal = i18n_unumber_set_attribute(num_format, eUnumberFormatAttr[nIndex], nPadEnumVal);
		}
		else{
			nRetVal = i18n_unumber_set_attribute(num_format, eUnumberFormatAttr[nIndex], nIndex);
		}
		
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_set_attribute failed for %s. Returned value = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		
		nGetAttr = i18n_unumber_get_attribute(num_format, eUnumberFormatAttr[nIndex]);
		
		nRetVal = get_last_result();
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_attribute failed for %s. Returned value = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}

		if(eUnumberFormatAttr[nIndex] == I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN ){
			if(nGetAttr != false ){
				FPRINTF("[Line : %d][%s]i18n_unumber_get_attribute failed for %s. Returned value not equal for I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN \\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
				return 1;
			}	
			
		}
		else if(eUnumberFormatAttr[nIndex] == I18N_UNUMBER_PADDING_POSITION ){
			if(nGetAttr != nPadEnumVal ){
				FPRINTF("[Line : %d][%s]i18n_unumber_get_attribute failed for %s. Returned value not equal for I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN \\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
				return 1;
			}	
			
		}
		else {
			if(nGetAttr != nIndex ){
				FPRINTF("[Line : %d][%s]i18n_unumber_get_attribute failed for %s. Returned value not equal to set attribute\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
				return 1;
			}
			
		}
		
		
		FPRINTF("[Line : %d][%s]i18n_unumber_set_attribute and i18n_unumber_get_attribute passed for %s.\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
	}
	return 0;
}

//& type: auto
//& purpose: Gets a locale for which decimal formatting patterns are available.
/**
* @testcase				ITc_i18n_unumber_get_available_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets a locale for which decimal formatting patterns are available.
* @apitarget			i18n_unumber_get_available
* @apicovered			i18n_unumber_get_available
* @passcase				When i18n_unumber_get_available is successful
* @failcase				When i18n_unumber_get_available failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_get_available_p(void)
{
	START_TEST;
	
	const char *pRetVal = NULL;
	
	pRetVal = i18n_unumber_get_available(0);
	if(pRetVal == NULL)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_get_available failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Set/Gets a numeric attribute associated with an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_set_get_double_attribute_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set a numeric attribute associated with an i18n_unumber_format_h.\n
*						Gets a numeric attribute associated with an i18n_unumber_format_h.
* @apitarget			i18n_unumber_set_double_attribute, i18n_unumber_get_double_attribute
* @apicovered			i18n_unumber_set_double_attribute, i18n_unumber_get_double_attribute
* @passcase				When i18n_unumber_set_double_attribute and i18n_unumber_get_double_attribute are successful
* @failcase				When i18n_unumber_set_double_attribute or i18n_unumber_get_double_attribute failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_set_get_double_attribute_p(void)
{
	START_TEST;
	
	int nRetVal = -1;
	double dGetAttr = -1;
	i18n_unumber_format_attribute_e eUnumberFormatAttr[] = {I18N_UNUMBER_ROUNDING_INCREMENT /*,
															I18N_UNUMBER_PARSE_INT_ONLY,                   
															I18N_UNUMBER_GROUPING_USED,                    
															I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN,             
															I18N_UNUMBER_MAX_INTEGER_DIGITS,               
															I18N_UNUMBER_MIN_INTEGER_DIGITS,               
															I18N_UNUMBER_INTEGER_DIGITS,                   
															I18N_UNUMBER_MAX_FRACTION_DIGITS,              
															I18N_UNUMBER_MIN_FRACTION_DIGITS,              
															I18N_UNUMBER_FRACTION_DIGITS,                  
															I18N_UNUMBER_MULTIPLIER,                       
															I18N_UNUMBER_GROUPING_SIZE,                    
															I18N_UNUMBER_ROUNDING_MODE,               
															I18N_UNUMBER_FORMAT_WIDTH,                     
															I18N_UNUMBER_PADDING_POSITION,                 
															I18N_UNUMBER_SECONDARY_GROUPING_SIZE,          
															I18N_UNUMBER_SIGNIFICANT_DIGITS_USED,          
															I18N_UNUMBER_MIN_SIGNIFICANT_DIGITS,           
															I18N_UNUMBER_MAX_SIGNIFICANT_DIGITS,           
															I18N_UNUMBER_LENIENT_PARSE,                    
															I18N_UNUM_SCALE,                               
															I18N_UNUM_FORMAT_FAIL_IF_MORE_THAN_MAX_DIGITS,
															I18N_UNUM_PARSE_NO_EXPONENT */}; // As suggested by developers
	
	int nUnumberFormatAttrSize = sizeof(eUnumberFormatAttr)/sizeof(eUnumberFormatAttr[0]);
	int nIndex ;
	double dVar;
	for(nIndex = 0; nIndex < nUnumberFormatAttrSize; nIndex++)
	{
		dVar = (double)nIndex+1.1;
		nRetVal = i18n_unumber_set_double_attribute(num_format, eUnumberFormatAttr[nIndex], dVar);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_set_double_attribute failed for %s. Returned value = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		
		dGetAttr = i18n_unumber_get_double_attribute(num_format, eUnumberFormatAttr[nIndex]);
		
		nRetVal = get_last_result();
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_double_attribute failed for %s. Returned value = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		
		if(!BaseUtilsCheckSetGetValue(dGetAttr, dVar))
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_double_attribute failed for %s. Returned value not matched with set value\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
			return 1;
		}
		FPRINTF("[Line : %d][%s]i18n_unumber_set_double_attribute and i18n_unumber_get_double_attribute passed for %s.\\n", __LINE__, API_NAMESPACE, UnumberGetFormatAttr(eUnumberFormatAttr[nIndex]));
	}
	return 0;
}

//& type: auto
//& purpose: Gets the locale for this number format object.
/**
* @testcase				ITc_i18n_unumber_get_locale_by_type_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the locale for this number format object.
* @apitarget			i18n_unumber_get_locale_by_type
* @apicovered			i18n_unumber_get_locale_by_type
* @passcase				When i18n_unumber_get_locale_by_type is successful
* @failcase				When i18n_unumber_get_locale_by_type failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_get_locale_by_type_p(void)
{
	START_TEST;

	const char *pRet = NULL;
	
	pRet = i18n_unumber_get_locale_by_type(num_format, I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE);
	if(pRet == NULL)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_get_locale_by_type failed. Returned value is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Set/Gets a text attribute associated with an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_set_get_text_attribute_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Set a text attribute associated with an i18n_unumber_format_h.\n
*						Gets a text attribute associated with an i18n_unumber_format_h.
* @apitarget			i18n_unumber_set_text_attribute, i18n_unumber_get_text_attribute
* @apicovered			i18n_unumber_set_text_attribute, i18n_unumber_get_text_attribute
* @passcase				When i18n_unumber_set_text_attribute and i18n_unumber_get_text_attribute are successful
* @failcase				When i18n_unumber_set_text_attribute or i18n_unumber_get_text_attribute failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_set_get_text_attribute_p(void)
{
	START_TEST;

	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	int nRetVal = -1;
	i18n_uchar szNewValue[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
	i18n_unumber_format_text_attribute_e eFormatTextAttr[] = {I18N_UNUMBER_POSITIVE_PREFIX, 
															   I18N_UNUMBER_POSITIVE_SUFFIX,              
															   I18N_UNUMBER_NEGATIVE_PREFIX,              
															   I18N_UNUMBER_NEGATIVE_SUFFIX,              
															   I18N_UNUMBER_PADDING_CHARACTER,            
															   I18N_UNUMBER_CURRENCY_CODE                
															   /*I18N_UNUMBER_DEFAULT_RULESET,				
															   I18N_UNUMBER_PUBLIC_RULESETS*/};

	int nFormatTextSize = sizeof(eFormatTextAttr)/sizeof(eFormatTextAttr[0]);
	int nIndex;
	int nBufSize =-1;
	for(nIndex = 0; nIndex < nFormatTextSize; nIndex++)
	{
		nRetVal = i18n_unumber_set_text_attribute(num_format, eFormatTextAttr[nIndex], szNewValue, 8);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_set_text_attribute failed for %s. Error Returned = %s.\\n", __LINE__, API_NAMESPACE, UnumberGetFormatTextAttr(eFormatTextAttr[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		
		nBufSize = i18n_unumber_get_text_attribute(num_format, eFormatTextAttr[nIndex], szResult, nResultCapacity);
		if(nBufSize == -1 || i18n_ustring_get_length(szResult) < 0)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_text_attribute failed for %s.\\n", __LINE__, API_NAMESPACE, UnumberGetFormatTextAttr(eFormatTextAttr[nIndex]));
			return 1;
		}
		nRetVal = get_last_result();
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_text_attribute failed for %s.\\n", __LINE__, API_NAMESPACE, UnumberGetFormatTextAttr(eFormatTextAttr[nIndex]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Parses a string into an integer using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_parse_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Parses a string into an integer using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_parse
* @apicovered			i18n_unumber_parse
* @passcase				When i18n_unumber_parse is successful
* @failcase				When i18n_unumber_parse failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_parse_p(void)
{
	START_TEST;
	
	i18n_uchar *pText = NULL;
    char *pTextSample = "232310";
    pText = (i18n_uchar*)calloc(strlen(pTextSample) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(pText, pTextSample);
	int nValue = -1;

	int32_t len = i18n_ustring_get_length(pText);
	nValue = i18n_unumber_parse(num_format, pText, len, NULL);
	int nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_unumber_parse", BaseUtilsGetError(nRetVal),free(pText););
	
	if(nValue == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_parse failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		free(pText);
		return 1;
	}
	
	free(pText);
	return 0;
}


//& type: auto
//& purpose: Parses a number from a string into an unformatted numeric string using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_parse_decimal_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Parses a number from a string into an unformatted numeric string using an #i18n_unumber_format_h.
* @apitarget			i18n_unumber_parse_decimal
* @apicovered			i18n_unumber_parse_decimal
* @passcase				When i18n_unumber_parse_decimal is successful
* @failcase				When i18n_unumber_parse_decimal failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_parse_decimal_p(void)
{
	START_TEST;
	
	char szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int32_t nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	i18n_uchar *pText = NULL;
    char *pTextSample = "12345678.1234";
    pText = (i18n_uchar*)calloc(strlen(pTextSample) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(pText, pTextSample);
	int nLength = -1;

	int32_t len = i18n_ustring_get_length(pText);
	nLength = i18n_unumber_parse_decimal(num_format, pText, len, NULL, szResult, nResultCapacity);
	int nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_unumber_parse_decimal", BaseUtilsGetError(nRetVal),free(pText));
	CHECK_HANDLE_CLEANUP(szResult, "i18n_unumber_parse_decimal",free(pText));
	CHECK_RETURN_VAL_CLEANUP(nResultCapacity, "i18n_unumber_parse_decimal",free(pText););
	
	if(nLength == -1 )
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_parse_decimal failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		free(pText);
		return 1;
	}
	
	free(pText);
	return 0;
}

//& type: auto
//& purpose: Parses a string into a double using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_parse_double_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Parses a string into a double using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_parse_double
* @apicovered			i18n_unumber_parse_double
* @passcase				When i18n_unumber_parse_double is successful
* @failcase				When i18n_unumber_parse_double failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_parse_double_p(void)
{
	START_TEST;
	
	i18n_uchar parse_double[]= { 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33,
								0x32, 0x31, 0x30, 0x2E, 0x31, 0x32, 0x33, 0 };
	int nValue = -1;
	
	int32_t len = i18n_ustring_get_length(parse_double);
	nValue = i18n_unumber_parse_double(num_format, parse_double, len, NULL);
	int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_parse_decimal", BaseUtilsGetError(nRetVal));
	
	if(nValue == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_parse_double failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	return 0;
}

//& type: auto
//& purpose: Parses a string into a double and a currency using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_parse_double_currency_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Parses a string into a double and a currency using an i18n_unumber_format_h.
* @apitarget			i18n_unumber_parse_double_currency
* @apicovered			i18n_unumber_parse_double_currency
* @passcase				When i18n_unumber_parse_double_currency is successful
* @failcase				When i18n_unumber_parse_double_currency failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_parse_double_currency_p(void)
{
	START_TEST;

    i18n_uchar szCurrency[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
	i18n_uchar szText[] = {0x0024,0x0031,0x0032,0x002E,0x0030,0x0030,0};
	double dRet = -1;
	g_pDefaultTzid = NULL;
	int nLength = 8;
	g_pszDefaultLocale = I18N_ULOCALE_US;
	i18n_unumber_format_h hNumFormat;
	
	int nRetVal = i18n_unumber_create(I18N_UNUMBER_CURRENCY, g_pDefaultTzid, nLength, g_pszDefaultLocale, NULL, &hNumFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_create", BaseUtilsGetError(nRetVal));
	
	int32_t len = i18n_ustring_get_length(szText);
	dRet = i18n_unumber_parse_double_currency(hNumFormat,  szText, len, NULL,  szCurrency);
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_unumber_parse_double_currency", BaseUtilsGetError(nRetVal));
	
	FPRINTF("[Line : %d][%s]i18n_unumber_parse_double_currency returned value = %lf\\n", __LINE__, API_NAMESPACE, dRet);
	if(BaseUtilsCheckSetGetValue(dRet, (double)-1))
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_parse_double_currency failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}	
	
	return 0;
}


//& type: auto
//& purpose: Parses a string into an int64 using an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_parse_int64_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Parses a string into an int64 using an i18n_unumber_format_h.\n
* @apitarget			i18n_unumber_parse_int64
* @apicovered			i18n_unumber_parse_int64
* @passcase				When i18n_unumber_parse_int64 is successful
* @failcase				When i18n_unumber_parse_int64 failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_parse_int64_p(void)
{
	START_TEST;
	
	i18n_uchar *pText = NULL;
    char *pTextSample = "0982523554243";
    pText = (i18n_uchar*)calloc(strlen(pTextSample) + 1, sizeof(i18n_uchar));
    i18n_ustring_copy_ua(pText, pTextSample);
	int nValue = -1;

	int32_t len = i18n_ustring_get_length(pText);
	nValue = i18n_unumber_parse_int64(num_format, pText, len, NULL);
	int nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_unumber_parse_int64", BaseUtilsGetError(nRetVal),free(pText););
	
	if(nValue == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_parse_int64 failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		free(pText);
		return 1;
	}
	
	free(pText);
	return 0;
}



//& type: auto
//& purpose: Extracts the pattern from an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_to_pattern_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Extracts the pattern from an i18n_unumber_format_h.
* @apitarget			i18n_unumber_to_pattern
* @apicovered			i18n_unumber_to_pattern
* @passcase				When i18n_unumber_to_pattern is successful
* @failcase				When i18n_unumber_to_pattern failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_to_pattern_p(void)
{
	START_TEST;
	
	i18n_uchar szResult[I18N_UNUMBER_SYMBOL_CAPACITY] = {0,};
    int nResultCapacity = I18N_UNUMBER_SYMBOL_CAPACITY;
	int nBufSize = -1;
	
	nBufSize = i18n_unumber_to_pattern(num_format, 0, szResult, nResultCapacity);
	if(nBufSize == -1)
	{
		FPRINTF("[Line : %d][%s]i18n_unumber_to_pattern failed. Returned value is = -1\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Sets/Gets a symbol associated with an i18n_unumber_format_h.
/**
* @testcase				ITc_i18n_unumber_set_get_symbol_p
* @since_tizen 			2.3.1
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Sets/Gets symbol associated with an i18n_unumber_format_h.
* @apitarget			i18n_unumber_set_symbol, i18n_unumber_get_symbol
* @apicovered			i18n_unumber_set_symbol, i18n_unumber_get_symbol
* @passcase				When i18n_unumber_set_symbol and i18n_unumber_get_symbol are successful
* @failcase				When i18n_unumber_set_symbol or i18n_unumber_get_symbol failed
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_unumber_set_get_symbol_p(void)
{
	START_TEST;

	i18n_uchar szResult[I18N_UCHAR_CAPACITY] = {0,};
	i18n_ustring_copy_ua_n(szResult, "XYZ", strlen("XYZ"));
	
	i18n_uchar szResultTemp[I18N_UCHAR_CAPACITY] = {0,};
	int nLength = i18n_ustring_get_length(szResult);
	int nRetVal = -1;
	i18n_unumber_format_symbol_e eUnumberFormatSymbol[] = {	I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL,
															I18N_UNUMBER_GROUPING_SEPARATOR_SYMBOL,
															I18N_UNUMBER_PATTERN_SEPARATOR_SYMBOL,
															I18N_UNUMBER_ZERO_DIGIT_SYMBOL,
															I18N_UNUMBER_PERCENT_SYMBOL,
															I18N_UNUMBER_DIGIT_SYMBOL,
															I18N_UNUMBER_MINUS_SIGN_SYMBOL,
															I18N_UNUMBER_PLUS_SIGN_SYMBOL,
															I18N_UNUMBER_CURRENCY_SYMBOL,
															I18N_UNUMBER_INTL_CURRENCY_SYMBOL,
															I18N_UNUMBER_MONETARY_SEPARATOR_SYMBOL,
															I18N_UNUMBER_EXPONENTIAL_SYMBOL,
															I18N_UNUMBER_PERMILL_SYMBOL,
															I18N_UNUMBER_PAD_ESCAPE_SYMBOL,
															I18N_UNUMBER_INFINITY_SYMBOL,
															I18N_UNUMBER_NAN_SYMBOL,
															I18N_UNUMBER_SIGNIFICANT_DIGIT_SYMBOL,
															I18N_UNUMBER_MONETARY_GROUPING_SEPARATOR_SYMBOL,
															I18N_UNUMBER_ONE_DIGIT_SYMBOL,
															I18N_UNUMBER_TWO_DIGIT_SYMBOL,
															I18N_UNUMBER_THREE_DIGIT_SYMBOL,
															I18N_UNUMBER_FOUR_DIGIT_SYMBOL,
															I18N_UNUMBER_FIVE_DIGIT_SYMBOL,
															I18N_UNUMBER_SIX_DIGIT_SYMBOL,
															I18N_UNUMBER_SEVEN_DIGIT_SYMBOL,
															I18N_UNUMBER_EIGHT_DIGIT_SYMBOL,
															I18N_UNUMBER_NINE_DIGIT_SYMBOL,
															/*I18N_UNUMBER_FORMAT_SYMBOL_COUNT*/ // As requested by developer 22-05-2015
															};
	
	int nUnumberFormatSymbolSize = sizeof(eUnumberFormatSymbol)/sizeof(eUnumberFormatSymbol[0]);
	int nIndex = 0;
	int nBufLen;
	for(nIndex = 0; nIndex < nUnumberFormatSymbolSize; nIndex++)
	{
		nRetVal = i18n_unumber_set_symbol(num_format, eUnumberFormatSymbol[nIndex], szResult, -1);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_set_symbol failed for %s. Returned value is = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatSymbol(eUnumberFormatSymbol[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		
		nRetVal = i18n_unumber_get_symbol(num_format, eUnumberFormatSymbol[nIndex], szResultTemp, I18N_UCHAR_CAPACITY, &nBufLen);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s]i18n_unumber_get_symbol failed for %s. Returned value is = %s\\n", __LINE__, API_NAMESPACE, UnumberGetFormatSymbol(eUnumberFormatSymbol[nIndex]), BaseUtilsGetError(nRetVal));
			return 1;
		}
		if(i18n_ustring_compare_n(szResult, szResultTemp, nLength) != 0)
		{
			FPRINTF("[Line : %d][%s]Set and Get value mismatched.\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}
