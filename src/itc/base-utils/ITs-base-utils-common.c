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

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

/**
* @function 		BaseUtilsGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* BaseUtilsGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{	
	case I18N_ERROR_NONE: 								szErrorVal = "I18N_ERROR_NONE";								break;
	//case I18N_ERROR_ILLEGAL_ARGUMENT: 				szErrorVal = "I18N_ERROR_ILLEGAL_ARGUMENT";					break;
	case I18N_ERROR_MISSING_RESOURCE: 					szErrorVal = "I18N_ERROR_MISSING_RESOURCE";					break;
	case I18N_ERROR_INVALID_FORMAT: 					szErrorVal = "I18N_ERROR_INVALID_FORMAT";					break;
	case I18N_ERROR_FILE_ACCESS: 						szErrorVal = "I18N_ERROR_FILE_ACCESS";						break;
	case I18N_ERROR_INTERNAL_PROGRAM: 					szErrorVal = "I18N_ERROR_INTERNAL_PROGRAM";					break;
	//case I18N_ERROR_MEMORY_ALLOCATION: 				szErrorVal = "I18N_ERROR_MEMORY_ALLOCATION";				break;
	case I18N_ERROR_INDEX_OUTOFBOUNDS: 					szErrorVal = "I18N_ERROR_INDEX_OUTOFBOUNDS";				break;
	case I18N_ERROR_INVALID_CHAR_FOUND: 				szErrorVal = "I18N_ERROR_INVALID_CHAR_FOUND";				break;
	case I18N_ERROR_BUFFER_OVERFLOW: 					szErrorVal = "I18N_ERROR_BUFFER_OVERFLOW";					break;
	//case I18N_ERROR_UNSUPPORTED: 						szErrorVal = "I18N_ERROR_UNSUPPORTED";						break;
	case I18N_ERROR_COLLATOR_VERSION_MISMATCH: 			szErrorVal = "I18N_ERROR_COLLATOR_VERSION_MISMATCH";		break;
	case I18N_ERROR_USELESS_COLLATOR: 					szErrorVal = "I18N_ERROR_USELESS_COLLATOR";					break;
	case I18N_ERROR_NO_WRITE_PERMISSION: 				szErrorVal = "I18N_ERROR_NO_WRITE_PERMISSION";				break;
	case I18N_ERROR_RESOURCE_TYPE_MISMATCH: 			szErrorVal = "I18N_ERROR_RESOURCE_TYPE_MISMATCH";			break;
	case I18N_ERROR_TOO_MANY_ALIASES: 					szErrorVal = "I18N_ERROR_TOO_MANY_ALIASES";					break;
	case I18N_ERROR_INVALID_PARAMETER: 					szErrorVal = "I18N_ERROR_INVALID_PARAMETER";				break;
	case I18N_ERROR_BAD_VARIABLE_DEFINITION: 			szErrorVal = "I18N_ERROR_BAD_VARIABLE_DEFINITION";			break;
	case I18N_ERROR_MALFORMED_RULE:						szErrorVal = "I18N_ERROR_MALFORMED_RULE";					break;
	case I18N_ERROR_MALFORMED_UNICODE_ESCAPE:			szErrorVal = "I18N_ERROR_MALFORMED_UNICODE_ESCAPE";			break;
	case I18N_ERROR_MALFORMED_VARIABLE_DEFINITION:		szErrorVal = "I18N_ERROR_MALFORMED_VARIABLE_DEFINITION";	break;
	case I18N_ERROR_MALFORMED_VARIABLE_REFERENCE:		szErrorVal = "I18N_ERROR_MALFORMED_VARIABLE_REFERENCE";		break;
	case I18N_ERROR_MISPLACED_ANCHOR_START:				szErrorVal = "I18N_ERROR_MISPLACED_ANCHOR_START";			break;
	case I18N_ERROR_MISPLACED_CURSOR_OFFSET:			szErrorVal = "I18N_ERROR_MISPLACED_CURSOR_OFFSET";			break;
	case I18N_ERROR_MISPLACED_QUANTIFIER:				szErrorVal = "I18N_ERROR_MISPLACED_QUANTIFIER";				break;
	case I18N_ERROR_MISSING_OPERATOR:					szErrorVal = "I18N_ERROR_MISSING_OPERATOR";					break;
	case I18N_ERROR_MULTIPLE_ANTE_CONTEXTS:				szErrorVal = "I18N_ERROR_MULTIPLE_ANTE_CONTEXTS";			break;
	case I18N_ERROR_MULTIPLE_CURSORS:					szErrorVal = "I18N_ERROR_MULTIPLE_CURSORS";					break;
	case I18N_ERROR_MULTIPLE_POST_CONTEXTS:				szErrorVal = "I18N_ERROR_MULTIPLE_POST_CONTEXTS";			break;
	case I18N_ERROR_TRAILING_BACKSLASH:					szErrorVal = "I18N_ERROR_TRAILING_BACKSLASH";				break;
	case I18N_ERROR_UNDEFINED_SEGMENT_REFERENCE:		szErrorVal = "I18N_ERROR_UNDEFINED_SEGMENT_REFERENCE";		break;
	case I18N_ERROR_UNDEFINED_VARIABLE:					szErrorVal = "I18N_ERROR_UNDEFINED_VARIABLE";				break;
	case I18N_ERROR_UNQUOTED_SPECIAL:					szErrorVal = "I18N_ERROR_UNQUOTED_SPECIAL";					break;
	case I18N_ERROR_UNTERMINATED_QUOTE:					szErrorVal = "I18N_ERROR_UNTERMINATED_QUOTE";				break;
	case I18N_ERROR_RULE_MASK:							szErrorVal = "I18N_ERROR_RULE_MASK";						break;
	case I18N_ERROR_MISPLACED_COMPOUND_FILTER:			szErrorVal = "I18N_ERROR_MISPLACED_COMPOUND_FILTER";		break;
	case I18N_ERROR_MULTIPLE_COMPOUND_FILTERS:			szErrorVal = "I18N_ERROR_MULTIPLE_COMPOUND_FILTERS";		break;
	case I18N_ERROR_MALFORMED_PRAGMA:					szErrorVal = "I18N_ERROR_MALFORMED_PRAGMA";					break;
	case I18N_ERROR_UNCLOSED_SEGMENT:					szErrorVal = "I18N_ERROR_UNCLOSED_SEGMENT";					break;
	case I18N_ERROR_VARIABLE_RANGE_EXHAUSTED:			szErrorVal = "I18N_ERROR_VARIABLE_RANGE_EXHAUSTED";			break;
	case I18N_ERROR_VARIABLE_RANGE_OVERLAP:				szErrorVal = "I18N_ERROR_VARIABLE_RANGE_OVERLAP";			break;
	case I18N_ERROR_ILLEGAL_CHARACTER:					szErrorVal = "I18N_ERROR_ILLEGAL_CHARACTER";				break;
	case I18N_ERROR_INTERNAL_TRANSLITERATOR:			szErrorVal = "I18N_ERROR_INTERNAL_TRANSLITERATOR";			break;
	case I18N_ERROR_INVALID_ID:							szErrorVal = "I18N_ERROR_INVALID_ID";						break;
	case I18N_ERROR_INVALID_FUNCTION:					szErrorVal = "I18N_ERROR_INVALID_FUNCTION";					break;
	case I18N_ERROR_UNEXPECTED_TOKEN:					szErrorVal = "I18N_ERROR_UNEXPECTED_TOKEN";					break;
	case I18N_ERROR_MULTIPLE_DECIMAL_SEPARATORS:		szErrorVal = "I18N_ERROR_MULTIPLE_DECIMAL_SEPARATORS";		break;
	case I18N_ERROR_MULTIPLE_EXPONENTIAL_SYMBOLS:		szErrorVal = "I18N_ERROR_MULTIPLE_EXPONENTIAL_SYMBOLS";		break;
	case I18N_ERROR_MALFORMED_EXPONENTIAL_PATTERN:		szErrorVal = "I18N_ERROR_MALFORMED_EXPONENTIAL_PATTERN";	break;
	case I18N_ERROR_MULTIPLE_PERCENT_SYMBOLS:			szErrorVal = "I18N_ERROR_MULTIPLE_PERCENT_SYMBOLS";			break;
	case I18N_ERROR_MULTIPLE_PERMILL_SYMBOLS:			szErrorVal = "I18N_ERROR_MULTIPLE_PERMILL_SYMBOLS";			break;
	case I18N_ERROR_MULTIPLE_PAD_SPECIFIERS:			szErrorVal = "I18N_ERROR_MULTIPLE_PAD_SPECIFIERS";			break;
	case I18N_ERROR_PATTERN_SYNTAX:						szErrorVal = "I18N_ERROR_PATTERN_SYNTAX";					break;
	case I18N_ERROR_ILLEGAL_PAD_POSITION:				szErrorVal = "I18N_ERROR_ILLEGAL_PAD_POSITION";				break;
	case I18N_ERROR_UNMATCHED_BRACES:					szErrorVal = "I18N_ERROR_UNMATCHED_BRACES";					break;
	case I18N_ERROR_ARGUMENT_TYPE_MISMATCH:				szErrorVal = "I18N_ERROR_ARGUMENT_TYPE_MISMATCH";			break;
	case I18N_ERROR_DUPLICATE_KEYWORD:					szErrorVal = "I18N_ERROR_DUPLICATE_KEYWORD";				break;
	case I18N_ERROR_UNDEFINED_KEYWORD:					szErrorVal = "I18N_ERROR_UNDEFINED_KEYWORD";				break;
	case I18N_ERROR_DEFAULT_KEYWORD_MISSING:			szErrorVal = "I18N_ERROR_DEFAULT_KEYWORD_MISSING";			break;
	case I18N_ERROR_DECIMAL_NUMBER_SYNTAX:				szErrorVal = "I18N_ERROR_DECIMAL_NUMBER_SYNTAX";			break;
	case I18N_ERROR_INEXACT_FORMAT:						szErrorVal = "I18N_ERROR_INEXACT_FORMAT";					break;
	case I18N_ERROR_UBRK_INTERNAL:						szErrorVal = "I18N_ERROR_UBRK_INTERNAL";					break;
	case I18N_ERROR_UBRK_HEX_DIGITS_EXPECTED:			szErrorVal = "I18N_ERROR_UBRK_HEX_DIGITS_EXPECTED";			break;
	case I18N_ERROR_UBRK_SEMICOLON_EXPECTED:			szErrorVal = "I18N_ERROR_UBRK_SEMICOLON_EXPECTED";			break;
	case I18N_ERROR_UBRK_RULE_SYNTAX:					szErrorVal = "I18N_ERROR_UBRK_RULE_SYNTAX";					break;
	case I18N_ERROR_UBRK_UNCLOSED_SET:					szErrorVal = "I18N_ERROR_UBRK_UNCLOSED_SET";				break;
	case I18N_ERROR_UBRK_ASSIGN_ERROR:					szErrorVal = "I18N_ERROR_UBRK_ASSIGN_ERROR";				break;
	case I18N_ERROR_UBRK_VARIABLE_REDEFINITION:			szErrorVal = "I18N_ERROR_UBRK_VARIABLE_REDEFINITION";		break;
	case I18N_ERROR_UBRK_MISMATCHED_PAREN:				szErrorVal = "I18N_ERROR_UBRK_MISMATCHED_PAREN";			break;
	case I18N_ERROR_UBRK_NEW_LINE_IN_QUOTED_STRING:		szErrorVal = "I18N_ERROR_UBRK_NEW_LINE_IN_QUOTED_STRING";	break;
	case I18N_ERROR_UBRK_UNDEFINED_VARIABLE:			szErrorVal = "I18N_ERROR_UBRK_UNDEFINED_VARIABLE";			break;
	case I18N_ERROR_UBRK_INIT:							szErrorVal = "I18N_ERROR_UBRK_INIT";						break;
	case I18N_ERROR_UBRK_RULE_EMPTY_SET:				szErrorVal = "I18N_ERROR_UBRK_RULE_EMPTY_SET";				break;
	case I18N_ERROR_UBRK_UNRECOGNIZED_OPTION:			szErrorVal = "I18N_ERROR_UBRK_UNRECOGNIZED_OPTION";			break;
	case I18N_ERROR_UBRK_MALFORMED_RULE_TAG:			szErrorVal = "I18N_ERROR_UBRK_MALFORMED_RULE_TAG";			break;
	case I18N_ERROR_OUT_OF_MEMORY:			szErrorVal = "I18N_ERROR_OUT_OF_MEMORY";			break;
	default: 											szErrorVal = "I18N_ERROR_UNKNOWN";							break;
	}
	return szErrorVal;
}
	

/**
* @function 		baseUtilTimeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/ 
gboolean baseUtilTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}


/**
* @function 		UcalenderGetType
* @description	 	Maps Ucalender Type enum values to string.
* @parameter		nRet: result code returned
* @return 			Ucalender Type represented as string
*/
char* UcalenderGetType(int nRet)
{
	char *szUcalenderType = NULL;

	switch ( nRet )
	{
	case I18N_UCALENDAR_TRADITIONAL: 		szUcalenderType = "I18N_UCALENDAR_TRADITIONAL";		break;
	case I18N_UCALENDAR_GREGORIAN: 			szUcalenderType = "I18N_UCALENDAR_GREGORIAN";		break;
	default: 								szUcalenderType = "Unknown Ucalender Type";			break;
	}
	return szUcalenderType;
}

/**
* @function 		UnormalizationModeValue
* @description	 	Maps Unormalization Mode Values to string.
* @parameter		nRet: result code returned
* @return 			Unormalization Mode Value represented as string
*/
char* UnormalizationModeValue(int nRet)
{
	char *szUnormalizationMode = NULL;

	switch ( nRet )
	{
	case I18N_UNORMALIZATION_COMPOSE: 				szUnormalizationMode = "I18N_UNORMALIZATION_COMPOSE";				break;
	case I18N_UNORMALIZATION_DECOMPOSE: 			szUnormalizationMode = "I18N_UNORMALIZATION_DECOMPOSE";				break;
	case I18N_UNORMALIZATION_FCD: 					szUnormalizationMode = "I18N_UNORMALIZATION_FCD";					break;
	case I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS: 	szUnormalizationMode = "I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS";	break;
	default: 										szUnormalizationMode = "Unknown Unormalization Mode";				break;
	}
	return szUnormalizationMode;
}

/**
* @function 		UcalenderDateFieldValue
* @description	 	Maps Ucalender DateField Type enum values to string.
* @parameter		nRet: result code returned
* @return 			Ucalender DateField Type represented as string
*/
char* UcalenderDateFieldValue(int nRet)
{
	char *szUcalenderDFType = NULL;

	switch ( nRet )
	{
	case I18N_UCALENDAR_ERA: 						szUcalenderDFType = "I18N_UCALENDAR_ERA";						break;
	case I18N_UCALENDAR_YEAR: 						szUcalenderDFType = "I18N_UCALENDAR_YEAR";						break;
	case I18N_UCALENDAR_MONTH: 						szUcalenderDFType = "I18N_UCALENDAR_MONTH";						break;
	case I18N_UCALENDAR_WEEK_OF_YEAR: 				szUcalenderDFType = "I18N_UCALENDAR_WEEK_OF_YEAR";				break;
	case I18N_UCALENDAR_WEEK_OF_MONTH: 				szUcalenderDFType = "I18N_UCALENDAR_WEEK_OF_MONTH";				break;
	case I18N_UCALENDAR_DATE: 						szUcalenderDFType = "I18N_UCALENDAR_DATE";						break;
	case I18N_UCALENDAR_DAY_OF_YEAR: 				szUcalenderDFType = "I18N_UCALENDAR_DAY_OF_YEAR";				break;
	case I18N_UCALENDAR_DAY_OF_WEEK: 				szUcalenderDFType = "I18N_UCALENDAR_DAY_OF_WEEK";				break;
	case I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH: 		szUcalenderDFType = "I18N_UCALENDAR_DAY_OF_WEEK_IN_MONTH";		break;
	case I18N_UCALENDAR_AM_PM: 						szUcalenderDFType = "I18N_UCALENDAR_AM_PM";						break;
	case I18N_UCALENDAR_HOUR: 						szUcalenderDFType = "I18N_UCALENDAR_HOUR";						break;
	case I18N_UCALENDAR_HOUR_OF_DAY: 				szUcalenderDFType = "I18N_UCALENDAR_HOUR_OF_DAY";				break;
	case I18N_UCALENDAR_MINUTE: 					szUcalenderDFType = "I18N_UCALENDAR_MINUTE";					break;
	case I18N_UCALENDAR_SECOND: 					szUcalenderDFType = "I18N_UCALENDAR_SECOND";					break;
	case I18N_UCALENDAR_MILLISECOND: 				szUcalenderDFType = "I18N_UCALENDAR_MILLISECOND";				break;
	case I18N_UCALENDAR_ZONE_OFFSET: 				szUcalenderDFType = "I18N_UCALENDAR_ZONE_OFFSET";				break;
	case I18N_UCALENDAR_DST_OFFSET: 				szUcalenderDFType = "I18N_UCALENDAR_DST_OFFSET";				break;
	default: 										szUcalenderDFType = "Unknown Type";								break;
	}
	return szUcalenderDFType;
}

/**
* @function 		UcalenderGetAttributeType
* @description	 	Maps Ucalender Attributes Type values to string.
* @parameter		nRet: result code returned
* @return 			Ucalender Attributes Type value represented as string
*/
char* UcalenderGetAttributeType(int nRet)
{
	char *szUcalenderType = NULL;

	switch ( nRet )
	{
	case I18N_UCALENDAR_LENIENT: 						szUcalenderType = "I18N_UCALENDAR_LENIENT";						break;
	case I18N_UCALENDAR_FIRST_DAY_OF_WEEK: 				szUcalenderType = "I18N_UCALENDAR_FIRST_DAY_OF_WEEK";			break;
	case I18N_UCALENDAR_MINIMAL_DAYS_IN_FIRST_WEEK: 	szUcalenderType = "I18N_UCALENDAR_MINIMAL_DAYS_IN_FIRST_WEEK";	break;
	default: 											szUcalenderType = "Unknown Type";								break;
	}
	return szUcalenderType;
}

/**
* @function 		UcalenderGetDisplayNameType
* @description	 	Maps Ucalender DisplayName Type enum values to string.
* @parameter		nRet: result code returned
* @return 			Ucalender DisplayName Type represented as string
*/
char* UcalenderGetDisplayNameType(int nRet)
{
	char *szDisplayNameTypeVal = NULL;

	switch ( nRet )
	{
	case I18N_UCALENDAR_STANDARD: 				szDisplayNameTypeVal = "I18N_UCALENDAR_STANDARD";				break;
	case I18N_UCALENDAR_SHORT_STANDARD: 		szDisplayNameTypeVal = "I18N_UCALENDAR_SHORT_STANDARD";			break;
	case I18N_UCALENDAR_DST: 					szDisplayNameTypeVal = "I18N_UCALENDAR_DST";					break;
	case I18N_UCALENDAR_SHORT_DST: 				szDisplayNameTypeVal = "I18N_UCALENDAR_SHORT_DST";				break;
	default: 									szDisplayNameTypeVal = "Unknown Type";							break;
	}
	return szDisplayNameTypeVal;
}

/**
* @function 		UnumberGetFormatStyle
* @description	 	Maps Style of given unumber style format enum values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* UnumberGetFormatStyle(int nRet)
{
	char *szStyleVal = NULL;

	switch ( nRet )
	{
	case I18N_UNUMBER_PATTERN_DECIMAL: 			szStyleVal = "I18N_UNUMBER_PATTERN_DECIMAL";			break;
	case I18N_UNUMBER_CURRENCY: 				szStyleVal = "I18N_UNUMBER_CURRENCY";					break;
	case I18N_UNUMBER_PERCENT: 					szStyleVal = "I18N_UNUMBER_PERCENT";					break;
	case I18N_UNUMBER_SCIENTIFIC: 				szStyleVal = "I18N_UNUMBER_SCIENTIFIC";					break;
	case I18N_UNUMBER_SPELLOUT: 				szStyleVal = "I18N_UNUMBER_SPELLOUT";					break;
	case I18N_UNUMBER_ORDINAL: 					szStyleVal = "I18N_UNUMBER_ORDINAL";					break;
	case I18N_UNUMBER_DURATION: 				szStyleVal = "I18N_UNUMBER_DURATION";					break;
	case I18N_UNUMBER_NUMBERING_SYSTEM: 		szStyleVal = "I18N_UNUMBER_NUMBERING_SYSTEM";			break;
	case I18N_UNUMBER_PATTERN_RULEBASED: 		szStyleVal = "I18N_UNUMBER_PATTERN_RULEBASED";			break;
	case I18N_UNUMBER_CURRENCY_ISO: 			szStyleVal = "I18N_UNUMBER_CURRENCY_ISO";				break;
	case I18N_UNUMBER_CURRENCY_PLURAL: 			szStyleVal = "I18N_UNUMBER_CURRENCY_PLURAL";			break;
	case I18N_UNUMBER_FORMAT_STYLE_COUNT: 		szStyleVal = "I18N_UNUMBER_FORMAT_STYLE_COUNT";			break;
	case I18N_UNUMBER_DECIMAL: 					szStyleVal = "I18N_UNUMBER_DECIMAL";					break;
	default: 									szStyleVal = "Unknown Unumber Format Style";			break;
	}
	return szStyleVal;
}

/**
* @function 		UnumberGetFormatSymbol
* @description	 	Maps symbol of given unumber format enum values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* UnumberGetFormatSymbol(int nRet)
{
	char *szSymbolVal = NULL;

	switch ( nRet )
	{
	case I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL: 					szSymbolVal = "I18N_UNUMBER_DECIMAL_SEPARATOR_SYMBOL";				break;
	case I18N_UNUMBER_GROUPING_SEPARATOR_SYMBOL: 					szSymbolVal = "I18N_UNUMBER_GROUPING_SEPARATOR_SYMBOL";				break;
	case I18N_UNUMBER_PATTERN_SEPARATOR_SYMBOL: 					szSymbolVal = "I18N_UNUMBER_PATTERN_SEPARATOR_SYMBOL";				break;
	case I18N_UNUMBER_ZERO_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_ZERO_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_PERCENT_SYMBOL: 								szSymbolVal = "I18N_UNUMBER_PERCENT_SYMBOL";						break;
	case I18N_UNUMBER_DIGIT_SYMBOL: 								szSymbolVal = "I18N_UNUMBER_DIGIT_SYMBOL";							break;
	case I18N_UNUMBER_MINUS_SIGN_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_MINUS_SIGN_SYMBOL";						break;
	case I18N_UNUMBER_PLUS_SIGN_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_PLUS_SIGN_SYMBOL";						break;
	case I18N_UNUMBER_CURRENCY_SYMBOL: 								szSymbolVal = "I18N_UNUMBER_CURRENCY_SYMBOL";						break;
	case I18N_UNUMBER_INTL_CURRENCY_SYMBOL: 						szSymbolVal = "I18N_UNUMBER_INTL_CURRENCY_SYMBOL";					break;
	case I18N_UNUMBER_MONETARY_SEPARATOR_SYMBOL: 					szSymbolVal = "I18N_UNUMBER_MONETARY_SEPARATOR_SYMBOL";				break;
	case I18N_UNUMBER_EXPONENTIAL_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_EXPONENTIAL_SYMBOL";					break;
	case I18N_UNUMBER_PERMILL_SYMBOL: 								szSymbolVal = "I18N_UNUMBER_PERMILL_SYMBOL";						break;
	case I18N_UNUMBER_PAD_ESCAPE_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_PAD_ESCAPE_SYMBOL";						break;
	case I18N_UNUMBER_INFINITY_SYMBOL: 								szSymbolVal = "I18N_UNUMBER_INFINITY_SYMBOL";						break;
	case I18N_UNUMBER_NAN_SYMBOL: 									szSymbolVal = "I18N_UNUMBER_NAN_SYMBOL";							break;
	case I18N_UNUMBER_SIGNIFICANT_DIGIT_SYMBOL: 					szSymbolVal = "I18N_UNUMBER_SIGNIFICANT_DIGIT_SYMBOL";				break;
	case I18N_UNUMBER_MONETARY_GROUPING_SEPARATOR_SYMBOL:			szSymbolVal = "I18N_UNUMBER_MONETARY_GROUPING_SEPARATOR_SYMBOL";	break;
	case I18N_UNUMBER_ONE_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_ONE_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_TWO_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_TWO_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_THREE_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_THREE_DIGIT_SYMBOL";					break;
	case I18N_UNUMBER_FOUR_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_FOUR_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_FIVE_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_FIVE_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_SIX_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_SIX_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_SEVEN_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_SEVEN_DIGIT_SYMBOL";					break;
	case I18N_UNUMBER_EIGHT_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_EIGHT_DIGIT_SYMBOL";					break;
	case I18N_UNUMBER_NINE_DIGIT_SYMBOL: 							szSymbolVal = "I18N_UNUMBER_NINE_DIGIT_SYMBOL";						break;
	case I18N_UNUMBER_FORMAT_SYMBOL_COUNT: 							szSymbolVal = "I18N_UNUMBER_FORMAT_SYMBOL_COUNT";					break;
	default: 														szSymbolVal = "Unknown Style";										break;
	}
	return szSymbolVal;
}

/**
* @function 		UnumberGetFormatSymbol
* @description	 	Maps symbol of given unumber format enum values to string.
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* UdateGetFormatStyle(int nRet)
{
	char *szFormatStyleVal = NULL;

	switch ( nRet )
	{
	case I18N_UDATE_FULL: 				szFormatStyleVal = "I18N_UDATE_FULL";				break;
	case I18N_UDATE_LONG: 				szFormatStyleVal = "I18N_UDATE_LONG";				break;
	case I18N_UDATE_MEDIUM: 			szFormatStyleVal = "I18N_UDATE_MEDIUM";				break;
	case I18N_UDATE_SHORT: 				szFormatStyleVal = "I18N_UDATE_SHORT";				break;
	//case I18N_UDATE_DEFAULT: 			szFormatStyleVal = "I18N_UDATE_DEFAULT";			break;
	case I18N_UDATE_RELATIVE: 			szFormatStyleVal = "I18N_UDATE_RELATIVE";			break;
	case I18N_UDATE_LONG_RELATIVE: 	szFormatStyleVal = "I18N_UDATE_LONG_RELATIVE";			break;
	case I18N_UDATE_MEDIUM_RELATIVE: 	szFormatStyleVal = "I18N_UDATE_MEDIUM_RELATIVE";	break;
	case I18N_UDATE_SHORT_RELATIVE: 	szFormatStyleVal = "I18N_UDATE_SHORT_RELATIVE";		break;
	case I18N_UDATE_NONE: 				szFormatStyleVal = "I18N_UDATE_NONE";				break;
	default: 							szFormatStyleVal = "Unknown Style";					break;
	}
	return szFormatStyleVal;
}

/**
* @function 		UcollatorResult
* @description	 	Maps UCollator Result Values
* @parameter		nRet: result code returned
* @return 			Type represented as string
*/
char* UcollatorResult(int nRet)
{
	char *szCollatorResultVal = NULL;

	switch ( nRet )
	{
	case I18N_UCOLLATOR_EQUAL: 			szCollatorResultVal = "I18N_UCOLLATOR_EQUAL";		break;
	case I18N_UCOLLATOR_GREATER: 		szCollatorResultVal = "I18N_UCOLLATOR_GREATER";		break;
	case I18N_UCOLLATOR_LESS: 			szCollatorResultVal = "I18N_UCOLLATOR_LESS";		break;
	default: 							szCollatorResultVal = "Unknown Result";				break;
	}
	return szCollatorResultVal;
}

/**
* @function 		UcollatorStrengthValues
* @description	 	Maps Strength Ucollator format enum values to string.
* @parameter		nRet: result Ucollator Strength Value String returned
* @return 			Type represented as string
*/
char* UcollatorStrengthValues(int nRet)
{
	char *szStrengthVal = NULL;

	switch ( nRet )
	{
	case I18N_UCOLLATOR_DEFAULT: 					szStrengthVal = "I18N_UCOLLATOR_DEFAULT";			break;
	case I18N_UCOLLATOR_PRIMARY: 					szStrengthVal = "I18N_UCOLLATOR_PRIMARY";			break;
	case I18N_UCOLLATOR_SECONDARY: 					szStrengthVal = "I18N_UCOLLATOR_SECONDARY";			break;
	case I18N_UCOLLATOR_TERTIARY: 					szStrengthVal = "I18N_UCOLLATOR_TERTIARY";			break;
	//case I18N_UCOLLATOR_DEFAULT_STRENGTH: 		szStrengthVal = "I18N_UCOLLATOR_DEFAULT_STRENGTH";	break;
	case I18N_UCOLLATOR_QUATERNARY: 				szStrengthVal = "I18N_UCOLLATOR_QUATERNARY";		break;
	case I18N_UCOLLATOR_IDENTICAL: 					szStrengthVal = "I18N_UCOLLATOR_IDENTICAL";			break;
	}
	return szStrengthVal;
}

/**
* @function 		UcollatorAttributes
* @description	 	Maps Strength Ucollator format enum values to string.
* @parameter		nRet: Ucollator Attributes String returned
* @return 			Type represented as string
*/
char* UcollatorAttributes(int nRet)
{
	char *szAttributeVal = NULL;
	switch ( nRet )
	{
	case I18N_UCOLLATOR_FRENCH_COLLATION: 				szAttributeVal = "I18N_UCOLLATOR_FRENCH_COLLATION";			break;
	case I18N_UCOLLATOR_ALTERNATE_HANDLING: 			szAttributeVal = "I18N_UCOLLATOR_ALTERNATE_HANDLING";		break;
	case I18N_UCOLLATOR_CASE_FIRST: 					szAttributeVal = "I18N_UCOLLATOR_CASE_FIRST";				break;
	case I18N_UCOLLATOR_CASE_LEVEL: 					szAttributeVal = "I18N_UCOLLATOR_CASE_LEVEL";				break;
	case I18N_UCOLLATOR_NORMALIZATION_MODE: 			szAttributeVal = "I18N_UCOLLATOR_NORMALIZATION_MODE";		break;
	//case I18N_UCOLLATOR_DECOMPOSITION_MODE: 			szAttributeVal = "I18N_UCOLLATOR_DECOMPOSITION_MODE";		break;
	case I18N_UCOLLATOR_STRENGTH: 						szAttributeVal = "I18N_UCOLLATOR_STRENGTH";					break;
	case I18N_UCOLLATOR_NUMERIC_COLLATION: 				szAttributeVal = "I18N_UCOLLATOR_NUMERIC_COLLATION";		break;
	case I18N_UCOLLATOR_ATTRIBUTE_COUNT: 				szAttributeVal = "I18N_UCOLLATOR_ATTRIBUTE_COUNT";			break;
	}
	return szAttributeVal;
}

/**
* @function 		uCharBlockCode
* @description	 	Maps uChar block Code enum values to string.
* @parameter		nRet: uChar block Code String returned
* @return 			uChar block Code represented as string
*/
char* uCharBlockCode(int nRet)
{
	char *szAttributeVal = NULL;
	switch ( nRet )
	{
	case I18N_UCHAR_UBLOCK_NO_BLOCK:								szAttributeVal = "I18N_UCHAR_UBLOCK_NO_BLOCK";										break;
	case I18N_UCHAR_UBLOCK_BASIC_LATIN: 							szAttributeVal = "I18N_UCHAR_UBLOCK_BASIC_LATIN";									break;
	case I18N_UCHAR_UBLOCK_LATIN_1_SUPPLEMENT:						szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_1_SUPPLEMENT";							break;
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_A:						szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_A";								break;
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_B:						szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_B";								break;
	case I18N_UCHAR_UBLOCK_IPA_EXTENSIONS:							szAttributeVal = "I18N_UCHAR_UBLOCK_IPA_EXTENSIONS";								break;
	case I18N_UCHAR_UBLOCK_SPACING_MODIFIER_LETTERS:				szAttributeVal = "I18N_UCHAR_UBLOCK_SPACING_MODIFIER_LETTERS";						break;
	case I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS:				szAttributeVal = "I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS";					break;
	case I18N_UCHAR_UBLOCK_GREEK:									szAttributeVal = "I18N_UCHAR_UBLOCK_GREEK";											break;
	case I18N_UCHAR_UBLOCK_CYRILLIC:								szAttributeVal = "I18N_UCHAR_UBLOCK_CYRILLIC";										break;
	case I18N_UCHAR_UBLOCK_ARMENIAN:								szAttributeVal = "I18N_UCHAR_UBLOCK_ARMENIAN";										break;
	case I18N_UCHAR_UBLOCK_HEBREW:									szAttributeVal = "I18N_UCHAR_UBLOCK_HEBREW";										break;
	case I18N_UCHAR_UBLOCK_ARABIC: 									szAttributeVal = "I18N_UCHAR_UBLOCK_ARABIC";										break;
	case I18N_UCHAR_UBLOCK_SYRIAC:									szAttributeVal = "I18N_UCHAR_UBLOCK_SYRIAC";										break;
	case I18N_UCHAR_UBLOCK_THAANA: 									szAttributeVal = "I18N_UCHAR_UBLOCK_THAANA";										break;
	case I18N_UCHAR_UBLOCK_DEVANAGARI:								szAttributeVal = "I18N_UCHAR_UBLOCK_DEVANAGARI";									break;
	case I18N_UCHAR_UBLOCK_BENGALI:									szAttributeVal = "I18N_UCHAR_UBLOCK_BENGALI";										break;
	case I18N_UCHAR_UBLOCK_GURMUKHI:								szAttributeVal = "I18N_UCHAR_UBLOCK_GURMUKHI";										break;
	case I18N_UCHAR_UBLOCK_GUJARATI:								szAttributeVal = "I18N_UCHAR_UBLOCK_GUJARATI";										break;
	case I18N_UCHAR_UBLOCK_ORIYA:									szAttributeVal = "I18N_UCHAR_UBLOCK_ORIYA";											break;
	case I18N_UCHAR_UBLOCK_TAMIL:									szAttributeVal = "I18N_UCHAR_UBLOCK_TAMIL";											break;
	case I18N_UCHAR_UBLOCK_TELUGU:									szAttributeVal = "I18N_UCHAR_UBLOCK_TELUGU";										break;
	case I18N_UCHAR_UBLOCK_KANNADA:									szAttributeVal = "I18N_UCHAR_UBLOCK_KANNADA";										break;
	case I18N_UCHAR_UBLOCK_MALAYALAM:								szAttributeVal = "I18N_UCHAR_UBLOCK_MALAYALAM";										break;
	case I18N_UCHAR_UBLOCK_SINHALA:									szAttributeVal = "I18N_UCHAR_UBLOCK_SINHALA";										break;
	case I18N_UCHAR_UBLOCK_THAI:									szAttributeVal = "I18N_UCHAR_UBLOCK_THAI";											break;
	case I18N_UCHAR_UBLOCK_LAO:										szAttributeVal = "I18N_UCHAR_UBLOCK_LAO";											break;
	case I18N_UCHAR_UBLOCK_TIBETAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_TIBETAN";										break;
	case I18N_UCHAR_UBLOCK_MYANMAR:									szAttributeVal = "I18N_UCHAR_UBLOCK_MYANMAR";										break;
	case I18N_UCHAR_UBLOCK_GEORGIAN:								szAttributeVal = "I18N_UCHAR_UBLOCK_GEORGIAN";										break;
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO:								szAttributeVal = "I18N_UCHAR_UBLOCK_HANGUL_JAMO";									break;
	case I18N_UCHAR_UBLOCK_ETHIOPIC:								szAttributeVal = "I18N_UCHAR_UBLOCK_ETHIOPIC";										break;
	case I18N_UCHAR_UBLOCK_CHEROKEE:								szAttributeVal = "I18N_UCHAR_UBLOCK_CHEROKEE";										break;
	case I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS:	szAttributeVal = "I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS";			break;
	case I18N_UCHAR_UBLOCK_OGHAM:									szAttributeVal = "I18N_UCHAR_UBLOCK_OGHAM";											break;
	case I18N_UCHAR_UBLOCK_RUNIC:									szAttributeVal = "I18N_UCHAR_UBLOCK_RUNIC";											break;
	case I18N_UCHAR_UBLOCK_KHMER:									szAttributeVal = "I18N_UCHAR_UBLOCK_KHMER";											break;
	case I18N_UCHAR_UBLOCK_MONGOLIAN: 								szAttributeVal = "I18N_UCHAR_UBLOCK_MONGOLIAN";										break;
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_ADDITIONAL: 				szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_ADDITIONAL";						break;
	case I18N_UCHAR_UBLOCK_GREEK_EXTENDED: 							szAttributeVal = "I18N_UCHAR_UBLOCK_GREEK_EXTENDED";								break;
	case I18N_UCHAR_UBLOCK_GENERAL_PUNCTUATION: 					szAttributeVal = "I18N_UCHAR_UBLOCK_GENERAL_PUNCTUATION";							break;
	case I18N_UCHAR_UBLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS";					break;
	case I18N_UCHAR_UBLOCK_CURRENCY_SYMBOLS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_CURRENCY_SYMBOLS";								break;
	case I18N_UCHAR_UBLOCK_COMBINING_MARKS_FOR_SYMBOLS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_COMBINING_MARKS_FOR_SYMBOLS";					break;
	case I18N_UCHAR_UBLOCK_LETTERLIKE_SYMBOLS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_LETTERLIKE_SYMBOLS";							break;
	case I18N_UCHAR_UBLOCK_NUMBER_FORMS:							szAttributeVal = "I18N_UCHAR_UBLOCK_NUMBER_FORMS";									break;
	case I18N_UCHAR_UBLOCK_ARROWS:									szAttributeVal = "I18N_UCHAR_UBLOCK_ARROWS";										break;
	case I18N_UCHAR_UBLOCK_MATHEMATICAL_OPERATORS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_MATHEMATICAL_OPERATORS";						break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_TECHNICAL:					szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_TECHNICAL";						break;
	case I18N_UCHAR_UBLOCK_CONTROL_PICTURES: 						szAttributeVal = "I18N_UCHAR_UBLOCK_CONTROL_PICTURES";								break;
	case I18N_UCHAR_UBLOCK_OPTICAL_CHARACTER_RECOGNITION:			szAttributeVal = "I18N_UCHAR_UBLOCK_OPTICAL_CHARACTER_RECOGNITION";					break;
	case I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERICS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERICS";						break;
	case I18N_UCHAR_UBLOCK_BOX_DRAWING: 							szAttributeVal = "I18N_UCHAR_UBLOCK_BOX_DRAWING";									break;
	case I18N_UCHAR_UBLOCK_BLOCK_ELEMENTS: 							szAttributeVal = "I18N_UCHAR_UBLOCK_BLOCK_ELEMENTS";								break;
	case I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES: 						szAttributeVal = "I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES";								break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS";							break;
	case I18N_UCHAR_UBLOCK_DINGBATS:								szAttributeVal = "I18N_UCHAR_UBLOCK_DINGBATS";										break;
	case I18N_UCHAR_UBLOCK_BRAILLE_PATTERNS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_BRAILLE_PATTERNS";								break;
	case I18N_UCHAR_UBLOCK_CJK_RADICALS_SUPPLEMENT: 				szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_RADICALS_SUPPLEMENT";						break;
	case I18N_UCHAR_UBLOCK_KANGXI_RADICALS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_KANGXI_RADICALS";								break;
	case I18N_UCHAR_UBLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS: 		szAttributeVal = "I18N_UCHAR_UBLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS";			break;
	case I18N_UCHAR_UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION: 			szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION";					break;
	case I18N_UCHAR_UBLOCK_HIRAGANA:								szAttributeVal = "I18N_UCHAR_UBLOCK_HIRAGANA";										break;
	case I18N_UCHAR_UBLOCK_KATAKANA:								szAttributeVal = "I18N_UCHAR_UBLOCK_KATAKANA";										break;
	case I18N_UCHAR_UBLOCK_BOPOMOFO:								szAttributeVal = "I18N_UCHAR_UBLOCK_BOPOMOFO";										break;
	case I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO: 				szAttributeVal = "I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO";						break;
	case I18N_UCHAR_UBLOCK_KANBUN:									szAttributeVal = "I18N_UCHAR_UBLOCK_KANBUN";										break;
	case I18N_UCHAR_UBLOCK_BOPOMOFO_EXTENDED: 						szAttributeVal = "I18N_UCHAR_UBLOCK_BOPOMOFO_EXTENDED";								break;
	case I18N_UCHAR_UBLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS: 		szAttributeVal = "I18N_UCHAR_UBLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS";				break;
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY: 						szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY";								break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A: 		szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A";			break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS";						break;
	case I18N_UCHAR_UBLOCK_YI_SYLLABLES: 							szAttributeVal = "I18N_UCHAR_UBLOCK_YI_SYLLABLES";									break;
	case I18N_UCHAR_UBLOCK_YI_RADICALS: 							szAttributeVal = "I18N_UCHAR_UBLOCK_YI_RADICALS";									break;
	case I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES: 						szAttributeVal = "I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES";								break;
	case I18N_UCHAR_UBLOCK_HIGH_SURROGATES: 						szAttributeVal = "I18N_UCHAR_UBLOCK_HIGH_SURROGATES";								break;
	case I18N_UCHAR_UBLOCK_HIGH_PRIVATE_USE_SURROGATES: 			szAttributeVal = "I18N_UCHAR_UBLOCK_HIGH_PRIVATE_USE_SURROGATES";					break;
	case I18N_UCHAR_UBLOCK_LOW_SURROGATES: 							szAttributeVal = "I18N_UCHAR_UBLOCK_LOW_SURROGATES";								break;
	case I18N_UCHAR_UBLOCK_PRIVATE_USE_AREA: 						szAttributeVal = "I18N_UCHAR_UBLOCK_PRIVATE_USE_AREA";								break;
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS";					break;
	case I18N_UCHAR_UBLOCK_ALPHABETIC_PRESENTATION_FORMS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_ALPHABETIC_PRESENTATION_FORMS";					break;
	case I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_A: 			szAttributeVal = "I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_A";					break;
	case I18N_UCHAR_UBLOCK_COMBINING_HALF_MARKS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_COMBINING_HALF_MARKS";							break;
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_FORMS: 				szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_FORMS";						break;
	case I18N_UCHAR_UBLOCK_SMALL_FORM_VARIANTS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_SMALL_FORM_VARIANTS";							break;
	case I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_B: 			szAttributeVal = "I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_B";					break;
	case I18N_UCHAR_UBLOCK_SPECIALS:								szAttributeVal = "I18N_UCHAR_UBLOCK_SPECIALS";										break;
	case I18N_UCHAR_UBLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS";					break;
	case I18N_UCHAR_UBLOCK_OLD_ITALIC: 								szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_ITALIC";									break;
	case I18N_UCHAR_UBLOCK_GOTHIC:									szAttributeVal = "I18N_UCHAR_UBLOCK_GOTHIC";										break;
	case I18N_UCHAR_UBLOCK_DESERET:									szAttributeVal = "I18N_UCHAR_UBLOCK_DESERET";										break;
	case I18N_UCHAR_UBLOCK_BYZANTINE_MUSICAL_SYMBOLS: 				szAttributeVal = "I18N_UCHAR_UBLOCK_BYZANTINE_MUSICAL_SYMBOLS";						break;
	case I18N_UCHAR_UBLOCK_MUSICAL_SYMBOLS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_MUSICAL_SYMBOLS";								break;
	case I18N_UCHAR_UBLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS: 		szAttributeVal = "I18N_UCHAR_UBLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS";				break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B: 		szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B";			break;
	case I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT:	szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT";		break;
	case I18N_UCHAR_UBLOCK_TAGS: 									szAttributeVal = "I18N_UCHAR_UBLOCK_TAGS";											break;
	case I18N_UCHAR_UBLOCK_CYRILLIC_SUPPLEMENT:			szAttributeVal = "I18N_UCHAR_UBLOCK_CYRILLIC_SUPPLEMENT";							break;
	case I18N_UCHAR_UBLOCK_TAGALOG:									szAttributeVal = "I18N_UCHAR_UBLOCK_TAGALOG";										break;
	case I18N_UCHAR_UBLOCK_HANUNOO:									szAttributeVal = "I18N_UCHAR_UBLOCK_HANUNOO";										break;
	case I18N_UCHAR_UBLOCK_BUHID:									szAttributeVal = "I18N_UCHAR_UBLOCK_BUHID";											break;
	case I18N_UCHAR_UBLOCK_TAGBANWA:								szAttributeVal = "I18N_UCHAR_UBLOCK_TAGBANWA";										break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A:	szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A";			break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_A: 					szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_A";							break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_B: 					szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_B";							break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B: 	szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B";			break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS: 	szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS";			break;
	case I18N_UCHAR_UBLOCK_KATAKANA_PHONETIC_EXTENSIONS: 			szAttributeVal = "I18N_UCHAR_UBLOCK_KATAKANA_PHONETIC_EXTENSIONS";					break;
	case I18N_UCHAR_UBLOCK_VARIATION_SELECTORS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_VARIATION_SELECTORS";							break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A: 		szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A";				break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B: 		szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B";				break;
	case I18N_UCHAR_UBLOCK_LIMBU:									szAttributeVal = "I18N_UCHAR_UBLOCK_LIMBU";											break;
	case I18N_UCHAR_UBLOCK_TAI_LE:									szAttributeVal = "I18N_UCHAR_UBLOCK_TAI_LE";										break;
	case I18N_UCHAR_UBLOCK_KHMER_SYMBOLS: 							szAttributeVal = "I18N_UCHAR_UBLOCK_KHMER_SYMBOLS";									break;
	case I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS";							break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS: 		szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS";				break;
	case I18N_UCHAR_UBLOCK_YIJING_HEXAGRAM_SYMBOLS: 				szAttributeVal = "I18N_UCHAR_UBLOCK_YIJING_HEXAGRAM_SYMBOLS";						break;
	case I18N_UCHAR_UBLOCK_LINEAR_B_SYLLABARY: 						szAttributeVal = "I18N_UCHAR_UBLOCK_LINEAR_B_SYLLABARY";							break;
	case I18N_UCHAR_UBLOCK_LINEAR_B_IDEOGRAMS: 						szAttributeVal = "I18N_UCHAR_UBLOCK_LINEAR_B_IDEOGRAMS";							break;
	case I18N_UCHAR_UBLOCK_AEGEAN_NUMBERS: 							szAttributeVal = "I18N_UCHAR_UBLOCK_AEGEAN_NUMBERS";								break;
	case I18N_UCHAR_UBLOCK_UGARITIC:								szAttributeVal = "I18N_UCHAR_UBLOCK_UGARITIC";										break;
	case I18N_UCHAR_UBLOCK_SHAVIAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_SHAVIAN";										break;
	case I18N_UCHAR_UBLOCK_OSMANYA:									szAttributeVal = "I18N_UCHAR_UBLOCK_OSMANYA";										break;
	case I18N_UCHAR_UBLOCK_CYPRIOT_SYLLABARY: 						szAttributeVal = "I18N_UCHAR_UBLOCK_CYPRIOT_SYLLABARY";								break;
	case I18N_UCHAR_UBLOCK_TAI_XUAN_JING_SYMBOLS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_TAI_XUAN_JING_SYMBOLS";							break;
	case I18N_UCHAR_UBLOCK_VARIATION_SELECTORS_SUPPLEMENT: 			szAttributeVal = "I18N_UCHAR_UBLOCK_VARIATION_SELECTORS_SUPPLEMENT";				break;
	case I18N_UCHAR_UBLOCK_ANCIENT_GREEK_MUSICAL_NOTATION: 			szAttributeVal = "I18N_UCHAR_UBLOCK_ANCIENT_GREEK_MUSICAL_NOTATION";				break;
	case I18N_UCHAR_UBLOCK_ANCIENT_GREEK_NUMBERS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_ANCIENT_GREEK_NUMBERS";							break;
	case I18N_UCHAR_UBLOCK_ARABIC_SUPPLEMENT: 						szAttributeVal = "I18N_UCHAR_UBLOCK_ARABIC_SUPPLEMENT";								break;
	case I18N_UCHAR_UBLOCK_BUGINESE:								szAttributeVal = "I18N_UCHAR_UBLOCK_BUGINESE";										break;
	case I18N_UCHAR_UBLOCK_CJK_STROKES: 							szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_STROKES";									break;
	case I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT: 	szAttributeVal = "I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT";		break;
	case I18N_UCHAR_UBLOCK_COPTIC:									szAttributeVal = "I18N_UCHAR_UBLOCK_COPTIC";										break;
	case I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED: 						szAttributeVal = "I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED";								break;
	case I18N_UCHAR_UBLOCK_ETHIOPIC_SUPPLEMENT: 					szAttributeVal = "I18N_UCHAR_UBLOCK_ETHIOPIC_SUPPLEMENT";							break;
	case I18N_UCHAR_UBLOCK_GEORGIAN_SUPPLEMENT: 					szAttributeVal = "I18N_UCHAR_UBLOCK_GEORGIAN_SUPPLEMENT";							break;
	case I18N_UCHAR_UBLOCK_GLAGOLITIC: 								szAttributeVal = "I18N_UCHAR_UBLOCK_GLAGOLITIC";									break;
	case I18N_UCHAR_UBLOCK_KHAROSHTHI: 								szAttributeVal = "I18N_UCHAR_UBLOCK_KHAROSHTHI";									break;
	case I18N_UCHAR_UBLOCK_MODIFIER_TONE_LETTERS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_MODIFIER_TONE_LETTERS";							break;
	case I18N_UCHAR_UBLOCK_NEW_TAI_LUE: 							szAttributeVal = "I18N_UCHAR_UBLOCK_NEW_TAI_LUE";									break;
	case I18N_UCHAR_UBLOCK_OLD_PERSIAN: 							szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_PERSIAN";									break;
	case I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT: 			szAttributeVal = "I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT";				break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_PUNCTUATION: 				szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_PUNCTUATION";						break;
	case I18N_UCHAR_UBLOCK_SYLOTI_NAGRI: 							szAttributeVal = "I18N_UCHAR_UBLOCK_SYLOTI_NAGRI";									break;
	case I18N_UCHAR_UBLOCK_TIFINAGH:								szAttributeVal = "I18N_UCHAR_UBLOCK_TIFINAGH";										break;
	case I18N_UCHAR_UBLOCK_VERTICAL_FORMS: 							szAttributeVal = "I18N_UCHAR_UBLOCK_VERTICAL_FORMS";								break;
	case I18N_UCHAR_UBLOCK_NKO: 									szAttributeVal = "I18N_UCHAR_UBLOCK_NKO";											break;
	case I18N_UCHAR_UBLOCK_BALINESE:								szAttributeVal = "I18N_UCHAR_UBLOCK_BALINESE";										break;
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_C: 						szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_C";								break;
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_D: 						szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_D";								break;
	case I18N_UCHAR_UBLOCK_PHAGS_PA:								szAttributeVal = "I18N_UCHAR_UBLOCK_PHAGS_PA";										break;
	case I18N_UCHAR_UBLOCK_PHOENICIAN: 								szAttributeVal = "I18N_UCHAR_UBLOCK_PHOENICIAN";									break;
	case I18N_UCHAR_UBLOCK_CUNEIFORM: 								szAttributeVal = "I18N_UCHAR_UBLOCK_CUNEIFORM";										break;
	case I18N_UCHAR_UBLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION: 		szAttributeVal = "I18N_UCHAR_UBLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION";				break;
	case I18N_UCHAR_UBLOCK_COUNTING_ROD_NUMERALS: 					szAttributeVal = "I18N_UCHAR_UBLOCK_COUNTING_ROD_NUMERALS";							break;
	case I18N_UCHAR_UBLOCK_SUNDANESE: 								szAttributeVal = "I18N_UCHAR_UBLOCK_SUNDANESE";										break;
	case I18N_UCHAR_UBLOCK_LEPCHA:									szAttributeVal = "I18N_UCHAR_UBLOCK_LEPCHA";										break;
	case I18N_UCHAR_UBLOCK_OL_CHIKI:								szAttributeVal = "I18N_UCHAR_UBLOCK_OL_CHIKI";										break;
	case I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_A: 					szAttributeVal = "I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_A";							break;
	case I18N_UCHAR_UBLOCK_VAI: 									szAttributeVal = "I18N_UCHAR_UBLOCK_VAI";											break;
	case I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_B: 					szAttributeVal = "I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_B";							break;
	case I18N_UCHAR_UBLOCK_SAURASHTRA:								szAttributeVal = "I18N_UCHAR_UBLOCK_SAURASHTRA";									break;
	case I18N_UCHAR_UBLOCK_KAYAH_LI:								szAttributeVal = "I18N_UCHAR_UBLOCK_KAYAH_LI";										break;
	case I18N_UCHAR_UBLOCK_REJANG:									szAttributeVal = "I18N_UCHAR_UBLOCK_REJANG";										break;
	case I18N_UCHAR_UBLOCK_CHAM:									szAttributeVal = "I18N_UCHAR_UBLOCK_CHAM";											break;
	case I18N_UCHAR_UBLOCK_ANCIENT_SYMBOLS:							szAttributeVal = "I18N_UCHAR_UBLOCK_ANCIENT_SYMBOLS";								break;
	case I18N_UCHAR_UBLOCK_PHAISTOS_DISC:							szAttributeVal = "I18N_UCHAR_UBLOCK_PHAISTOS_DISC";									break;
	case I18N_UCHAR_UBLOCK_LYCIAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_LYCIAN";										break;
	case I18N_UCHAR_UBLOCK_CARIAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_CARIAN";										break;
	case I18N_UCHAR_UBLOCK_LYDIAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_LYDIAN";										break;
	case I18N_UCHAR_UBLOCK_MAHJONG_TILES:							szAttributeVal = "I18N_UCHAR_UBLOCK_MAHJONG_TILES";									break;
	case I18N_UCHAR_UBLOCK_DOMINO_TILES:							szAttributeVal = "I18N_UCHAR_UBLOCK_DOMINO_TILES";									break;
	case I18N_UCHAR_UBLOCK_SAMARITAN:								szAttributeVal = "I18N_UCHAR_UBLOCK_SAMARITAN";										break;
	case I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED:	szAttributeVal = "I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED";	break;
	case I18N_UCHAR_UBLOCK_TAI_THAM:								szAttributeVal = "I18N_UCHAR_UBLOCK_TAI_THAM";										break;
	case I18N_UCHAR_UBLOCK_VEDIC_EXTENSIONS:						szAttributeVal = "I18N_UCHAR_UBLOCK_VEDIC_EXTENSIONS";								break;
	case I18N_UCHAR_UBLOCK_LISU:									szAttributeVal = "I18N_UCHAR_UBLOCK_LISU";											break;
	case I18N_UCHAR_UBLOCK_BAMUM:									szAttributeVal = "I18N_UCHAR_UBLOCK_BAMUM";											break;
	case I18N_UCHAR_UBLOCK_COMMON_INDIC_NUMBER_FORMS:				szAttributeVal = "I18N_UCHAR_UBLOCK_COMMON_INDIC_NUMBER_FORMS";						break;
	case I18N_UCHAR_UBLOCK_DEVANAGARI_EXTENDED:						szAttributeVal = "I18N_UCHAR_UBLOCK_DEVANAGARI_EXTENDED";							break;
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A:					szAttributeVal = "I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A";						break;
	case I18N_UCHAR_UBLOCK_JAVANESE:								szAttributeVal = "I18N_UCHAR_UBLOCK_JAVANESE";										break;
	case I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_A:						szAttributeVal = "I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_A";							break;
	case I18N_UCHAR_UBLOCK_TAI_VIET:								szAttributeVal = "I18N_UCHAR_UBLOCK_TAI_VIET";										break;
	case I18N_UCHAR_UBLOCK_MEETEI_MAYEK:							szAttributeVal = "I18N_UCHAR_UBLOCK_MEETEI_MAYEK";									break;
	case I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B:					szAttributeVal = "I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B";						break;
	case I18N_UCHAR_UBLOCK_IMPERIAL_ARAMAIC:						szAttributeVal = "I18N_UCHAR_UBLOCK_IMPERIAL_ARAMAIC";								break;
	case I18N_UCHAR_UBLOCK_OLD_SOUTH_ARABIAN:						szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_SOUTH_ARABIAN";								break;
	case I18N_UCHAR_UBLOCK_AVESTAN:									szAttributeVal = "I18N_UCHAR_UBLOCK_AVESTAN";										break;
	case I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PARTHIAN:					szAttributeVal = "I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PARTHIAN";						break;
	case I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PAHLAVI:					szAttributeVal = "I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PAHLAVI";							break;
	case I18N_UCHAR_UBLOCK_OLD_TURKIC:								szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_TURKIC";									break;
	case I18N_UCHAR_UBLOCK_RUMI_NUMERAL_SYMBOLS:					szAttributeVal = "I18N_UCHAR_UBLOCK_RUMI_NUMERAL_SYMBOLS";							break;
	case I18N_UCHAR_UBLOCK_KAITHI:									szAttributeVal = "I18N_UCHAR_UBLOCK_KAITHI";										break;
	case I18N_UCHAR_UBLOCK_EGYPTIAN_HIEROGLYPHS:					szAttributeVal = "I18N_UCHAR_UBLOCK_EGYPTIAN_HIEROGLYPHS";							break;
	case I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT:		szAttributeVal = "I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT";				break;
	case I18N_UCHAR_UBLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT:			szAttributeVal = "I18N_UCHAR_UBLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT";				break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C:		szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C";			break;
	case I18N_UCHAR_UBLOCK_MANDAIC:									szAttributeVal = "I18N_UCHAR_UBLOCK_MANDAIC";										break;
	case I18N_UCHAR_UBLOCK_BATAK:									szAttributeVal = "I18N_UCHAR_UBLOCK_BATAK";											break;
	case I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED_A:						szAttributeVal = "I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED_A";							break;
	case I18N_UCHAR_UBLOCK_BRAHMI:									szAttributeVal = "I18N_UCHAR_UBLOCK_BRAHMI";										break;
	case I18N_UCHAR_UBLOCK_BAMUM_SUPPLEMENT:						szAttributeVal = "I18N_UCHAR_UBLOCK_BAMUM_SUPPLEMENT";								break;
	case I18N_UCHAR_UBLOCK_KANA_SUPPLEMENT:							szAttributeVal = "I18N_UCHAR_UBLOCK_KANA_SUPPLEMENT";								break;
	case I18N_UCHAR_UBLOCK_PLAYING_CARDS:							szAttributeVal = "I18N_UCHAR_UBLOCK_PLAYING_CARDS";									break;
	case I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS:	szAttributeVal = "I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS";			break;
	case I18N_UCHAR_UBLOCK_EMOTICONS:								szAttributeVal = "I18N_UCHAR_UBLOCK_EMOTICONS";										break;
	case I18N_UCHAR_UBLOCK_TRANSPORT_AND_MAP_SYMBOLS:				szAttributeVal = "I18N_UCHAR_UBLOCK_TRANSPORT_AND_MAP_SYMBOLS";						break;
	case I18N_UCHAR_UBLOCK_ALCHEMICAL_SYMBOLS:						szAttributeVal = "I18N_UCHAR_UBLOCK_ALCHEMICAL_SYMBOLS";							break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D:		szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D";			break;
	case I18N_UCHAR_UBLOCK_ARABIC_EXTENDED_A:		szAttributeVal ="I18N_UCHAR_UBLOCK_ARABIC_EXTENDED_A";		break;
	case I18N_UCHAR_UBLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS:		szAttributeVal ="I18N_UCHAR_UBLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS";		break;
	case I18N_UCHAR_UBLOCK_CHAKMA:		szAttributeVal ="I18N_UCHAR_UBLOCK_CHAKMA";		break;
	case I18N_UCHAR_UBLOCK_MEETEI_MAYEK_EXTENSIONS:		szAttributeVal ="I18N_UCHAR_UBLOCK_MEETEI_MAYEK_EXTENSIONS";		break;
	case I18N_UCHAR_UBLOCK_MEROITIC_CURSIVE:		szAttributeVal ="I18N_UCHAR_UBLOCK_MEROITIC_CURSIVE";		break;
	case I18N_UCHAR_UBLOCK_MEROITIC_HIEROGLYPHS:		szAttributeVal ="I18N_UCHAR_UBLOCK_MEROITIC_HIEROGLYPHS";		break;
	case I18N_UCHAR_UBLOCK_MIAO:		szAttributeVal ="I18N_UCHAR_UBLOCK_MIAO";		break;
	case I18N_UCHAR_UBLOCK_SHARADA:		szAttributeVal ="I18N_UCHAR_UBLOCK_SHARADA";		break;
	case I18N_UCHAR_UBLOCK_SORA_SOMPENG:		szAttributeVal ="I18N_UCHAR_UBLOCK_SORA_SOMPENG";		break;
	case I18N_UCHAR_UBLOCK_SUNDANESE_SUPPLEMENT:		szAttributeVal ="I18N_UCHAR_UBLOCK_SUNDANESE_SUPPLEMENT";		break;
	case I18N_UCHAR_UBLOCK_TAKRI:		szAttributeVal ="I18N_UCHAR_UBLOCK_TAKRI";		break;

#if defined(MOBILE) || defined(TIZENIOT)
    case I18N_UCHAR_UBLOCK_BASSA_VAH:								szAttributeVal = "I18N_UCHAR_UBLOCK_BASSA_VAH";                                     break;	
	case I18N_UCHAR_UBLOCK_CAUCASIAN_ALBANIAN:                      szAttributeVal = "I18N_UCHAR_UBLOCK_CAUCASIAN_ALBANIAN";                            break;            	
	case I18N_UCHAR_UBLOCK_COPTIC_EPACT_NUMBERS:                    szAttributeVal = "I18N_UCHAR_UBLOCK_COPTIC_EPACT_NUMBERS";                          break;            	
	case I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_EXTENDED:    szAttributeVal = "I18N_	UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_EXTENDED";         break;            	
	case I18N_UCHAR_UBLOCK_DUPLOYAN:                                szAttributeVal = "I18N_UCHAR_UBLOCK_DUPLOYAN";                                      break;            	
	case I18N_UCHAR_UBLOCK_ELBASAN:                                 szAttributeVal = "I18N_UCHAR_UBLOCK_ELBASAN";                                       break;            	
	case I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES_EXTENDED:               szAttributeVal = "I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES_EXTENDED";                     break;            	
	case I18N_UCHAR_UBLOCK_GRANTHA:                                 szAttributeVal = "I18N_UCHAR_UBLOCK_GRANTHA";                                       break;            	
	case I18N_UCHAR_UBLOCK_KHOJKI:                                  szAttributeVal = "I18N_UCHAR_UBLOCK_KHOJKI";                                        break;            	
	case I18N_UCHAR_UBLOCK_KHUDAWADI:                               szAttributeVal = "I18N_UCHAR_UBLOCK_KHUDAWADI";                                     break;            	
	case I18N_UCHAR_UBLOCK_LATIN_EXTENDED_E:                        szAttributeVal = "I18N_UCHAR_UBLOCK_LATIN_EXTENDED_E";                              break;            	
	case I18N_UCHAR_UBLOCK_LINEAR_A:                                szAttributeVal = "I18N_UCHAR_UBLOCK_LINEAR_A";                                      break;                    	
	case I18N_UCHAR_UBLOCK_MAHAJANI:                                szAttributeVal = "I18N_UCHAR_UBLOCK_MAHAJANI";                                      break;                   
	case I18N_UCHAR_UBLOCK_MANICHAEAN:                              szAttributeVal = "I18N_UCHAR_UBLOCK_MANICHAEAN";                                    break;                   
	case I18N_UCHAR_UBLOCK_MENDE_KIKAKUI:                           szAttributeVal = "I18N_UCHAR_UBLOCK_MENDE_KIKAKUI";                                 break;                   
	case I18N_UCHAR_UBLOCK_MODI:                                    szAttributeVal = "I18N_UCHAR_UBLOCK_MODI";                                          break;                	
	case I18N_UCHAR_UBLOCK_MRO:                                     szAttributeVal = "I18N_UCHAR_UBLOCK_MRO";                                           break;               	
	case I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_B:                      szAttributeVal = "I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_B";                            break;                   
	case I18N_UCHAR_UBLOCK_NABATAEAN:                               szAttributeVal = "I18N_UCHAR_UBLOCK_NABATAEAN";                                     break;                     	
	case I18N_UCHAR_UBLOCK_OLD_NORTH_ARABIAN:                       szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_NORTH_ARABIAN";                             break;                   
	case I18N_UCHAR_UBLOCK_OLD_PERMIC:                              szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_PERMIC";                                    break;                    
	case I18N_UCHAR_UBLOCK_ORNAMENTAL_DINGBATS:                     szAttributeVal = "I18N_UCHAR_UBLOCK_ORNAMENTAL_DINGBATS";                           break;                   
	case I18N_UCHAR_UBLOCK_PAHAWH_HMONG:                            szAttributeVal = "I18N_UCHAR_UBLOCK_PAHAWH_HMONG";                                  break;                    
	case I18N_UCHAR_UBLOCK_PALMYRENE:                               szAttributeVal = "I18N_UCHAR_UBLOCK_PALMYRENE";                                     break;                   
	case I18N_UCHAR_UBLOCK_PAU_CIN_HAU:                             szAttributeVal = "I18N_UCHAR_UBLOCK_PAU_CIN_HAU";                                   break;                   
	case I18N_UCHAR_UBLOCK_PSALTER_PAHLAVI:                         szAttributeVal = "I18N_UCHAR_UBLOCK_PSALTER_PAHLAVI";                               break;                   
	case I18N_UCHAR_UBLOCK_SHORTHAND_FORMAT_CONTROLS:               szAttributeVal = "I18N_UCHAR_UBLOCK_SHORTHAND_FORMAT_CONTROLS";                     break;                   
	case I18N_UCHAR_UBLOCK_SIDDHAM:                                 szAttributeVal = "I18N_UCHAR_UBLOCK_SIDDHAM";                                       break;                   	
	case I18N_UCHAR_UBLOCK_SINHALA_ARCHAIC_NUMBERS:                 szAttributeVal = "I18N_UCHAR_UBLOCK_SINHALA_ARCHAIC_NUMBERS";                       break;                   
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_C:                   szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_C";                         break;                   
	case I18N_UCHAR_UBLOCK_TIRHUTA:                                 szAttributeVal = "I18N_UCHAR_UBLOCK_TIRHUTA";                                       break;                   	
	case I18N_UCHAR_UBLOCK_WARANG_CITI:                             szAttributeVal = "I18N_UCHAR_UBLOCK_WARANG_CITI";                                   break;                       	
	case I18N_UCHAR_UBLOCK_AHOM:                             szAttributeVal = "I18N_UCHAR_UBLOCK_AHOM";	break;
	case I18N_UCHAR_ANATOLIAN_HIEROGLYPHS:                             szAttributeVal = "I18N_UCHAR_ANATOLIAN_HIEROGLYPHS";	break;
	case I18N_UCHAR_UBLOCK_CHEROKEE_SUPPLEMENT:                             szAttributeVal = "I18N_UCHAR_UBLOCK_CHEROKEE_SUPPLEMENT";	break;
	case I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E:                             szAttributeVal = "I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E";	break;
	case I18N_UCHAR_UBLOCK_EARLY_DYNASTIC_CUNEIFORM:                             szAttributeVal = "I18N_UCHAR_UBLOCK_EARLY_DYNASTIC_CUNEIFORM";	break;
	case I18N_UCHAR_UBLOCK_HATRAN:                             szAttributeVal = "I18N_UCHAR_UBLOCK_HATRAN";	break;
	case I18N_UCHAR_UBLOCK_MULTANI:                             szAttributeVal = "I18N_UCHAR_UBLOCK_MULTANI";	break;
	case I18N_UCHAR_UBLOCK_OLD_HUNGARIAN:                             szAttributeVal = "I18N_UCHAR_UBLOCK_OLD_HUNGARIAN";	break;
	case I18N_UCHAR_UBLOCK_SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS:                             szAttributeVal = "I18N_UCHAR_UBLOCK_SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS";	break;
	case I18N_UCHAR_UBLOCK_SUTTON_SIGNWRITING:                             szAttributeVal = "I18N_UCHAR_UBLOCK_SUTTON_SIGNWRITING";	break;
	case I18N_UCHAR_UBLOCK_ADLAM:                             szAttributeVal = "I18N_UCHAR_UBLOCK_ADLAM";	break;
	case I18N_UCHAR_UBLOCK_BHAIKSUKI:                             szAttributeVal = "I18N_UCHAR_UBLOCK_BHAIKSUKI";	break;
	case I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_C:                             szAttributeVal = "I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_C";	break;
	case I18N_UCHAR_UBLOCK_GLAGOLITIC_SUPPLEMENT:                             szAttributeVal = "I18N_UCHAR_UBLOCK_GLAGOLITIC_SUPPLEMENT";	break;
	case I18N_UCHAR_UBLOCK_IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION:                             szAttributeVal = "I18N_UCHAR_UBLOCK_IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION";	break;
	case I18N_UCHAR_UBLOCK_MARCHEN:                             szAttributeVal = "I18N_UCHAR_UBLOCK_MARCHEN";	break;
	case I18N_UCHAR_UBLOCK_MONGOLIAN_SUPPLEMENT:                             szAttributeVal = "I18N_UCHAR_UBLOCK_MONGOLIAN_SUPPLEMENT";	break;
	case I18N_UCHAR_UBLOCK_NEWA:                             szAttributeVal = "I18N_UCHAR_UBLOCK_NEWA";	break;
	case I18N_UCHAR_UBLOCK_OSAGE:                             szAttributeVal = "I18N_UCHAR_UBLOCK_OSAGE";	break;
	case I18N_UCHAR_UBLOCK_TANGUT:                             szAttributeVal = "I18N_UCHAR_UBLOCK_TANGUT";	break;
	case I18N_UCHAR_UBLOCK_TANGUT_COMPONENTS:                             szAttributeVal = "I18N_UCHAR_UBLOCK_TANGUT_COMPONENTS";	break;

#endif  //MOBILE    //End MOBILE

	case I18N_UCHAR_UBLOCK_COUNT:									szAttributeVal = "I18N_UCHAR_UBLOCK_COUNT";											break;
	case I18N_UCHAR_UBLOCK_INVALID_CODE:							szAttributeVal = "I18N_UCHAR_UBLOCK_INVALID_CODE";									break;
	default:                                                  		szAttributeVal = "Unknown Error";	break;
	}
	return szAttributeVal;
}

/**
* @function 		uCharPropertyName
* @description	 	Maps uChar Property Name enum values to string.
* @parameter		nRet: uChar Property Name String returned
* @return 			Type represented as string
*/
char* uCharPropertyName(int nRet)
{
	char *szAttributeVal = NULL;
	switch ( nRet )
	{
	case I18N_UCHAR_ALPHABETIC:							szAttributeVal = "I18N_UCHAR_ALPHABETIC";								break;
	case I18N_UCHAR_ASCII_HEX_DIGIT:					szAttributeVal = "I18N_UCHAR_ASCII_HEX_DIGIT";							break;
	case I18N_UCHAR_BIDI_CONTROL:						szAttributeVal = "I18N_UCHAR_BIDI_CONTROL";								break;
	case I18N_UCHAR_BIDI_MIRRORED:						szAttributeVal = "I18N_UCHAR_BIDI_MIRRORED";							break;
	case I18N_UCHAR_DASH:								szAttributeVal = "I18N_UCHAR_DASH";										break;
	case I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT:		szAttributeVal = "I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT";				break;
	case I18N_UCHAR_DEPRECATED:							szAttributeVal = "I18N_UCHAR_DEPRECATED";								break;
	case I18N_UCHAR_DIACRITIC:							szAttributeVal = "I18N_UCHAR_DIACRITIC";								break;
	case I18N_UCHAR_EXTENDER:							szAttributeVal = "I18N_UCHAR_EXTENDER";									break;
	case I18N_UCHAR_FULL_COMPOSITION_EXCLUSION:			szAttributeVal = "I18N_UCHAR_FULL_COMPOSITION_EXCLUSION";				break;
	case I18N_UCHAR_GRAPHEME_BASE:						szAttributeVal = "I18N_UCHAR_GRAPHEME_BASE";							break;
	case I18N_UCHAR_GRAPHEME_EXTEND:					szAttributeVal = "I18N_UCHAR_GRAPHEME_EXTEND";							break;
	case I18N_UCHAR_GRAPHEME_LINK:						szAttributeVal = "I18N_UCHAR_GRAPHEME_LINK";							break;
	case I18N_UCHAR_HEX_DIGIT:							szAttributeVal = "I18N_UCHAR_HEX_DIGIT";								break;
	case I18N_UCHAR_HYPHEN:								szAttributeVal = "I18N_UCHAR_HYPHEN";									break;
	case I18N_UCHAR_ID_CONTINUE:						szAttributeVal = "I18N_UCHAR_ID_CONTINUE";								break;
	case I18N_UCHAR_ID_START:							szAttributeVal = "I18N_UCHAR_ID_START";									break;
	case I18N_UCHAR_IDEOGRAPHIC:						szAttributeVal = "I18N_UCHAR_IDEOGRAPHIC";								break;
	case I18N_UCHAR_IDS_BINARY_OPERATOR:				szAttributeVal = "I18N_UCHAR_IDS_BINARY_OPERATOR";						break;
	case I18N_UCHAR_IDS_TRINARY_OPERATOR:				szAttributeVal = "I18N_UCHAR_IDS_TRINARY_OPERATOR";						break;
	case I18N_UCHAR_JOIN_CONTROL:						szAttributeVal = "I18N_UCHAR_JOIN_CONTROL";								break;
	case I18N_UCHAR_LOGICAL_ORDER_EXCEPTION:			szAttributeVal = "I18N_UCHAR_LOGICAL_ORDER_EXCEPTION";					break;
	case I18N_UCHAR_LOWERCASE:							szAttributeVal = "I18N_UCHAR_LOWERCASE";								break;
	case I18N_UCHAR_MATH:								szAttributeVal = "I18N_UCHAR_MATH";										break;
	case I18N_UCHAR_NONCHARACTER_CODE_POINT:			szAttributeVal = "I18N_UCHAR_NONCHARACTER_CODE_POINT";					break;
	case I18N_UCHAR_QUOTATION_MARK:						szAttributeVal = "I18N_UCHAR_QUOTATION_MARK";							break;
	case I18N_UCHAR_RADICAL:							szAttributeVal = "I18N_UCHAR_RADICAL";									break;
	case I18N_UCHAR_SOFT_DOTTED:						szAttributeVal = "I18N_UCHAR_SOFT_DOTTED";								break;
	case I18N_UCHAR_TERMINAL_PUNCTUATION:				szAttributeVal = "I18N_UCHAR_TERMINAL_PUNCTUATION";						break;
	case I18N_UCHAR_UNIFIED_IDEOGRAPH:					szAttributeVal = "I18N_UCHAR_UNIFIED_IDEOGRAPH";						break;
	case I18N_UCHAR_UPPERCASE:							szAttributeVal = "I18N_UCHAR_UPPERCASE";								break;
	case I18N_UCHAR_WHITE_SPACE:						szAttributeVal = "I18N_UCHAR_WHITE_SPACE";								break;
	case I18N_UCHAR_XID_CONTINUE:						szAttributeVal = "I18N_UCHAR_XID_CONTINUE";								break;
	case I18N_UCHAR_XID_START:							szAttributeVal = "I18N_UCHAR_XID_START";								break;
	case I18N_UCHAR_CASE_SENSITIVE:						szAttributeVal = "I18N_UCHAR_CASE_SENSITIVE";							break;
	case I18N_UCHAR_S_TERM:								szAttributeVal = "I18N_UCHAR_S_TERM";									break;
	case I18N_UCHAR_VARIATION_SELECTOR:					szAttributeVal = "I18N_UCHAR_VARIATION_SELECTOR";						break;
	case I18N_UCHAR_NFD_INERT:							szAttributeVal = "I18N_UCHAR_NFD_INERT";								break;
	case I18N_UCHAR_NFKD_INERT:							szAttributeVal = "I18N_UCHAR_NFKD_INERT";								break;
	case I18N_UCHAR_NFC_INERT:							szAttributeVal = "I18N_UCHAR_NFC_INERT";								break;
	case I18N_UCHAR_NFKC_INERT:							szAttributeVal = "I18N_UCHAR_NFKC_INERT";								break;
	case I18N_UCHAR_SEGMENT_STARTER:					szAttributeVal = "I18N_UCHAR_SEGMENT_STARTER";							break;
	case I18N_UCHAR_PATTERN_SYNTAX:						szAttributeVal = "I18N_UCHAR_PATTERN_SYNTAX";							break;
	case I18N_UCHAR_PATTERN_WHITE_SPACE:				szAttributeVal = "I18N_UCHAR_PATTERN_WHITE_SPACE";						break;
	case I18N_UCHAR_POSIX_ALNUM:						szAttributeVal = "I18N_UCHAR_POSIX_ALNUM";								break;
	case I18N_UCHAR_POSIX_BLANK:						szAttributeVal = "I18N_UCHAR_POSIX_BLANK";								break;
	case I18N_UCHAR_POSIX_GRAPH:						szAttributeVal = "I18N_UCHAR_POSIX_GRAPH";								break;
	case I18N_UCHAR_POSIX_PRINT:						szAttributeVal = "I18N_UCHAR_POSIX_PRINT";								break;
	case I18N_UCHAR_POSIX_XDIGIT:						szAttributeVal = "I18N_UCHAR_POSIX_XDIGIT";								break;
	case I18N_UCHAR_CASED:								szAttributeVal = "I18N_UCHAR_CASED";									break;
	case I18N_UCHAR_CASE_IGNORABLE:						szAttributeVal = "I18N_UCHAR_CASE_IGNORABLE";							break;
	case I18N_UCHAR_CHANGES_WHEN_LOWERCASED:			szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_LOWERCASED";					break;
	case I18N_UCHAR_CHANGES_WHEN_UPPERCASED:			szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_UPPERCASED";					break;
	case I18N_UCHAR_CHANGES_WHEN_TITLECASED:			szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_TITLECASED";					break;
	case I18N_UCHAR_CHANGES_WHEN_CASEFOLDED:			szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_CASEFOLDED";					break;
	case I18N_UCHAR_CHANGES_WHEN_CASEMAPPED:			szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_CASEMAPPED";					break;
	case I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED:		szAttributeVal = "I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED";				break;
	case I18N_UCHAR_EMOJI:				szAttributeVal = "I18N_UCHAR_EMOJI";				break;
	case I18N_UCHAR_EMOJI_PRESENTATION:		szAttributeVal = "I18N_UCHAR_EMOJI_PRESENTATION";				break;
	case I18N_UCHAR_EMOJI_MODIFIER:			szAttributeVal = "I18N_UCHAR_EMOJI_MODIFIER";				break;
	case I18N_UCHAR_EMOJI_MODIFIER_BASE:		szAttributeVal = "I18N_UCHAR_EMOJI_MODIFIER_BASE";				break;
	case I18N_UCHAR_BINARY_LIMIT:						szAttributeVal = "I18N_UCHAR_BINARY_LIMIT";								break;
	case I18N_UCHAR_BIDI_CLASS:						szAttributeVal = "I18N_UCHAR_BIDI_CLASS";								break;
	case I18N_UCHAR_BLOCK:								szAttributeVal = "I18N_UCHAR_BLOCK";									break;
	case I18N_UCHAR_CANONICAL_COMBINING_CLASS:			szAttributeVal = "I18N_UCHAR_CANONICAL_COMBINING_CLASS";				break;
	case I18N_UCHAR_DECOMPOSITION_TYPE:					szAttributeVal = "I18N_UCHAR_DECOMPOSITION_TYPE";						break;
	case I18N_UCHAR_EAST_ASIAN_WIDTH:					szAttributeVal = "I18N_UCHAR_EAST_ASIAN_WIDTH";							break;
	case I18N_UCHAR_GENERAL_CATEGORY:					szAttributeVal = "I18N_UCHAR_GENERAL_CATEGORY";							break;
	case I18N_UCHAR_JOINING_GROUP:						szAttributeVal = "I18N_UCHAR_JOINING_GROUP";							break;
	case I18N_UCHAR_JOINING_TYPE:						szAttributeVal = "I18N_UCHAR_JOINING_TYPE";								break;
	case I18N_UCHAR_LINE_BREAK:							szAttributeVal = "I18N_UCHAR_LINE_BREAK";								break;
	case I18N_UCHAR_NUMERIC_TYPE:						szAttributeVal = "I18N_UCHAR_NUMERIC_TYPE";								break;
	case I18N_UCHAR_SCRIPT:								szAttributeVal = "I18N_UCHAR_SCRIPT";									break;
	case I18N_UCHAR_HANGUL_SYLLABLE_TYPE:				szAttributeVal = "I18N_UCHAR_HANGUL_SYLLABLE_TYPE";						break;
	case I18N_UCHAR_NFD_QUICK_CHECK:					szAttributeVal = "I18N_UCHAR_NFD_QUICK_CHECK";							break;
	case I18N_UCHAR_NFKD_QUICK_CHECK:					szAttributeVal = "I18N_UCHAR_NFKD_QUICK_CHECK";							break;
	case I18N_UCHAR_NFC_QUICK_CHECK:					szAttributeVal = "I18N_UCHAR_NFC_QUICK_CHECK";							break;
	case I18N_UCHAR_NFKC_QUICK_CHECK:					szAttributeVal = "I18N_UCHAR_NFKC_QUICK_CHECK";							break;
	case I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS:		szAttributeVal = "I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS";			break;
	case I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS:	szAttributeVal = "I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS";			break;
	case I18N_UCHAR_GRAPHEME_CLUSTER_BREAK:				szAttributeVal = "I18N_UCHAR_GRAPHEME_CLUSTER_BREAK";					break;
	case I18N_UCHAR_SENTENCE_BREAK:						szAttributeVal = "I18N_UCHAR_SENTENCE_BREAK";							break;
	case I18N_UCHAR_WORD_BREAK:							szAttributeVal = "I18N_UCHAR_WORD_BREAK";								break;
	case I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE:			szAttributeVal = "I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE";					break;
	case I18N_UCHAR_INT_LIMIT:							szAttributeVal = "I18N_UCHAR_INT_LIMIT";								break;
	case I18N_UCHAR_GENERAL_CATEGORY_MASK:			szAttributeVal = "I18N_UCHAR_GENERAL_CATEGORY_MASK";					break;
	case I18N_UCHAR_MASK_LIMIT:							szAttributeVal = "I18N_UCHAR_MASK_LIMIT";								break;
	case I18N_UCHAR_NUMERIC_VALUE:						szAttributeVal = "I18N_UCHAR_NUMERIC_VALUE";							break;
	case I18N_UCHAR_DOUBLE_LIMIT:						szAttributeVal = "I18N_UCHAR_DOUBLE_LIMIT";								break;
	case I18N_UCHAR_AGE:								szAttributeVal = "I18N_UCHAR_AGE";										break;
	case I18N_UCHAR_BIDI_MIRRORING_GLYPH:				szAttributeVal = "I18N_UCHAR_BIDI_MIRRORING_GLYPH";						break;
	case I18N_UCHAR_CASE_FOLDING:						szAttributeVal = "I18N_UCHAR_CASE_FOLDING";								break;
	case I18N_UCHAR_LOWERCASE_MAPPING:					szAttributeVal = "I18N_UCHAR_LOWERCASE_MAPPING";						break;
	case I18N_UCHAR_NAME:								szAttributeVal = "I18N_UCHAR_NAME";										break;
	case I18N_UCHAR_SIMPLE_CASE_FOLDING:				szAttributeVal = "I18N_UCHAR_SIMPLE_CASE_FOLDING";						break;
	case I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING:			szAttributeVal = "I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING";					break;
	case I18N_UCHAR_SIMPLE_TITLECASE_MAPPING:			szAttributeVal = "I18N_UCHAR_SIMPLE_TITLECASE_MAPPING";					break;
	case I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING:			szAttributeVal = "I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING";					break;
	case I18N_UCHAR_TITLECASE_MAPPING:					szAttributeVal = "I18N_UCHAR_TITLECASE_MAPPING";						break;
	case I18N_UCHAR_UPPERCASE_MAPPING:					szAttributeVal = "I18N_UCHAR_UPPERCASE_MAPPING";						break;
	case I18N_UCHAR_BIDI_PAIRED_BRACKET:				szAttributeVal = "I18N_UCHAR_BIDI_PAIRED_BRACKET";						break;
	case I18N_UCHAR_STRING_LIMIT:						szAttributeVal = "I18N_UCHAR_STRING_LIMIT";								break;
	case I18N_UCHAR_SCRIPT_EXTENSIONS:					szAttributeVal = "I18N_UCHAR_SCRIPT_EXTENSIONS";						break;
	case I18N_UCHAR_OTHER_PROPERTY_LIMIT:				szAttributeVal = "I18N_UCHAR_OTHER_PROPERTY_LIMIT";						break;
	case I18N_UCHAR_INVALID_CODE:						szAttributeVal = "I18N_UCHAR_INVALID_CODE";								break;
	default:											szAttributeVal = "Unknown Error";										break;
	}
	return szAttributeVal;
}

/**
 * @function 		UcalendarGetTimezoneType
 * @description	 	Maps symbol of given timezone type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Type represented as string
 */
char* UcalendarGetTimezoneType(int nRet)
{
	char *pszReturnString = NULL;

	switch(nRet)
	{
		case I18N_UCALENDAR_ZONE_TYPE_ANY : pszReturnString = "I18N_UCALENDAR_ZONE_TYPE_ANY" ; break; 
		case I18N_UCALENDAR_ZONE_TYPE_CANONICAL : pszReturnString = "I18N_UCALENDAR_ZONE_TYPE_CANONICAL" ; break; 
		case I18N_UCALENDAR_ZONE_TYPE_CANONICAL_LOCATION : pszReturnString = "I18N_UCALENDAR_ZONE_TYPE_CANONICAL_LOCATION" ; break; 
		default : pszReturnString = "Unknown Timezone type" ; break;
	}
	return pszReturnString;
}

/**
 * @function 		UcalendarGetLimitType
 * @description	 	Maps symbol of given limit type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Type represented as string
 */
char* UcalendarGetLimitType(int nRet)
{
	char *pszReturnString = NULL;

	switch(nRet)
	{
		case I18N_UCALENDAR_MINIMUM : pszReturnString = "I18N_UCALENDAR_MINIMUM" ; break; 
		case I18N_UCALENDAR_MAXIMUM : pszReturnString = "I18N_UCALENDAR_MAXIMUM" ; break; 
		case I18N_UCALENDAR_GREATEST_MINIMUM : pszReturnString = "I18N_UCALENDAR_GREATEST_MINIMUM" ; break; 
		case I18N_UCALENDAR_LEAST_MAXIMUM : pszReturnString = "I18N_UCALENDAR_LEAST_MAXIMUM" ; break; 
		case I18N_UCALENDAR_ACTUAL_MINIMUM : pszReturnString = "I18N_UCALENDAR_ACTUAL_MINIMUM" ; break; 
		case I18N_UCALENDAR_ACTUAL_MAXIMUM : pszReturnString = "I18N_UCALENDAR_ACTUAL_MAXIMUM" ; break; 
		default : pszReturnString = "Unknown Limit type" ; break;
	}
	return pszReturnString;
}

/**
 * @function 		UcalendarGetLocaleType
 * @description	 	Maps symbol of given locale type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Type represented as string
 */
char* UcalendarGetLocaleType(int nRet)
{
	char *pszReturnString = NULL;

	switch(nRet)
	{
		case I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE : pszReturnString = "I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE" ; break; 
		case I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE : pszReturnString = "I18N_ULOCALE_DATA_LOCALE_TYPE_VALID_LOCALE" ; break; 
		default : pszReturnString = "Unknown Locale type" ; break;
	}
	return pszReturnString;
}

/**
 * @function 		UcalendarGetDaysOfWeek
 * @description	 	Maps symbol of given day of week enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Type represented as string
 */
char* UcalendarGetDaysOfWeek(int nRet)
{
	char *pszReturnString = NULL;

	switch(nRet)
	{
		case I18N_UCALENDAR_SUNDAY : pszReturnString = "I18N_UCALENDAR_SUNDAY" ; break; 
		case I18N_UCALENDAR_MONDAY : pszReturnString = "I18N_UCALENDAR_MONDAY" ; break; 
		case I18N_UCALENDAR_TUESDAY : pszReturnString = "I18N_UCALENDAR_TUESDAY" ; break; 
		case I18N_UCALENDAR_WEDNESDAY : pszReturnString = "I18N_UCALENDAR_WEDNESDAY" ; break; 
		case I18N_UCALENDAR_THURSDAY : pszReturnString = "I18N_UCALENDAR_THURSDAY" ; break; 
		case I18N_UCALENDAR_FRIDAY : pszReturnString = "I18N_UCALENDAR_FRIDAY" ; break; 
		case I18N_UCALENDAR_SATURDAY : pszReturnString = "I18N_UCALENDAR_SATURDAY" ; break; 
		default : pszReturnString = "Unknown day of the week" ; break;
	}
	return pszReturnString;
}

/**
 * @function 		UcalendarGetTimezoneTransitionType
 * @description	 	Maps symbol of given day of week enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Type represented as string
 */
char* UcalendarGetTimezoneTransitionType(int nRet)
{
	char *pszReturnString = NULL;

	switch(nRet)
	{
		case I18N_UCALENDAR_TZ_TRANSITION_NEXT : pszReturnString = "I18N_UCALENDAR_TZ_TRANSITION_NEXT" ; break; 
		case I18N_UCALENDAR_TZ_TRANSITION_NEXT_INCLUSIVE : pszReturnString = "I18N_UCALENDAR_TZ_TRANSITION_NEXT_INCLUSIVE" ; break; 
		case I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS : pszReturnString = "I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS" ; break; 
		case I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS_INCLUSIVE : pszReturnString = "I18N_UCALENDAR_TZ_TRANSITION_PREVIOUS_INCLUSIVE" ; break; 
		default : pszReturnString = "Unknown Timezone transition type" ; break;
	}
	return pszReturnString;
}

/**
 * @function 		UdateGetDateFormatFieldValue
 * @description	 	Maps Udate Date Format Field enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Udate Date Format Field represented as string
 */
char* UdateGetDateFormatFieldValue(int nRet)
{
	char *szUcalenderDFType = NULL;

	switch(nRet)
	{
		case I18N_UDATE_FORMAT_ERA_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_ERA_FIELD" ; break; 
		case I18N_UDATE_FORMAT_YEAR_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_YEAR_FIELD" ; break; 
		case I18N_UDATE_FORMAT_MONTH_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_MONTH_FIELD" ; break; 
		case I18N_UDATE_FORMAT_DATE_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_DATE_FIELD" ; break; 
		case I18N_UDATE_FORMAT_HOUR_OF_DAY1_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_HOUR_OF_DAY1_FIELD" ; break; 
		case I18N_UDATE_FORMAT_HOUR_OF_DAY0_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_HOUR_OF_DAY0_FIELD" ; break; 
		case I18N_UDATE_FORMAT_MINUTE_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_MINUTE_FIELD" ; break; 
		case I18N_UDATE_FORMAT_SECOND_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_SECOND_FIELD" ; break; 
		case I18N_UDATE_FORMAT_FRACTIONAL_SECOND_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_FRACTIONAL_SECOND_FIELD" ; break; 
		case I18N_UDATE_FORMAT_DAY_OF_WEEK_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_DAY_OF_WEEK_FIELD" ; break; 
		case I18N_UDATE_FORMAT_DAY_OF_YEAR_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_DAY_OF_YEAR_FIELD" ; break; 
		case I18N_UDATE_FORMAT_DAY_OF_WEEK_IN_MONTH_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_DAY_OF_WEEK_IN_MONTH_FIELD" ; break; 
		case I18N_UDATE_FORMAT_WEEK_OF_YEAR_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_WEEK_OF_YEAR_FIELD" ; break; 
		case I18N_UDATE_FORMAT_WEEK_OF_MONTH_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_WEEK_OF_MONTH_FIELD" ; break; 
		case I18N_UDATE_FORMAT_AM_PM_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_AM_PM_FIELD" ; break; 
		case I18N_UDATE_FORMAT_HOUR1_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_HOUR1_FIELD" ; break; 
		case I18N_UDATE_FORMAT_HOUR0_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_HOUR0_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_FIELD" ; break; 
		case I18N_UDATE_FORMAT_YEAR_WOY_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_YEAR_WOY_FIELD" ; break; 
		case I18N_UDATE_FORMAT_DOW_LOCAL_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_DOW_LOCAL_FIELD" ; break; 
		case I18N_UDATE_FORMAT_EXTENDED_YEAR_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_EXTENDED_YEAR_FIELD" ; break; 
		case I18N_UDATE_FORMAT_JULIAN_DAY_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_JULIAN_DAY_FIELD" ; break; 
		case I18N_UDATE_FORMAT_MILLISECONDS_IN_DAY_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_MILLISECONDS_IN_DAY_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_RFC_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_RFC_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_GENERIC_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_GENERIC_FIELD" ; break; 
		case I18N_UDATE_FORMAT_STANDALONE_DAY_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_STANDALONE_DAY_FIELD" ; break; 
		case I18N_UDATE_FORMAT_STANDALONE_MONTH_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_STANDALONE_MONTH_FIELD" ; break; 
		case I18N_UDATE_FORMAT_QUARTER_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_QUARTER_FIELD" ; break; 
		case I18N_UDATE_FORMAT_STANDALONE_QUARTER_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_STANDALONE_QUARTER_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_SPECIAL_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_SPECIAL_FIELD" ; break; 
		case I18N_UDATE_FORMAT_YEAR_NAME_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_YEAR_NAME_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_LOCALIZED_GMT_OFFSET_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_LOCALIZED_GMT_OFFSET_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_ISO_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_ISO_FIELD" ; break; 
		case I18N_UDATE_FORMAT_TIMEZONE_ISO_LOCAL_FIELD : szUcalenderDFType = "I18N_UDATE_FORMAT_TIMEZONE_ISO_LOCAL_FIELD" ; break; 
		case I18N_UDATE_FORMAT_FIELD_COUNT : szUcalenderDFType = "I18N_UDATE_FORMAT_FIELD_COUNT" ; break; 
		default : szUcalenderDFType = "Unknown Udate Date Format Field value" ; break;
	}
	return szUcalenderDFType;
}

/**
 * @function 		UdateGetFormatSymbolType
 * @description	 	Maps Udate Format Symbol type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Udate Format Symbol type represented as string
 */
char* UdateGetFormatSymbolType(int nRet)
{
	char *szUcalenderDFType = NULL;

	switch(nRet)
	{
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_ERAS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_AM_PMS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_AM_PMS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_LOCALIZED_CHARS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_LOCALIZED_CHARS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_ERA_NAMES : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_ERA_NAMES" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_NARROW_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_MONTHS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_MONTHS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_NARROW_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_QUARTERS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_QUARTERS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_QUARTERS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORT_QUARTERS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_QUARTERS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_QUARTERS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_QUARTERS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORT_QUARTERS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORTER_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_SHORTER_WEEKDAYS" ; break; 
		case I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS : szUcalenderDFType = "I18N_UDATE_FORMAT_SYMBOL_TYPE_STANDALONE_SHORTER_WEEKDAYS" ; break; 
		default : szUcalenderDFType = "Unknown Udate Format Symbol type" ; break;
	}
	return szUcalenderDFType;
}

/**
 * @function 		UdateGetDisplayContext
 * @description	 	Maps Udate Display context type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Udate Display context type represented as string
 */
char* UdateGetDisplayContext(int nRet)
{
	char *szUcalenderDFType = NULL;

	switch(nRet)
	{
		case I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_STANDALONE" ; break; 
		case I18N_UDISPLAY_CONTEXT_STANDARD_NAMES : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_STANDARD_NAMES" ; break; 
		case I18N_UDISPLAY_CONTEXT_DIALECT_NAMES : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_DIALECT_NAMES" ; break; 
		case I18N_UDISPLAY_CONTEXT_CAPITALIZATION_NONE : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_CAPITALIZATION_NONE" ; break; 
		case I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE" ; break; 
		case I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_BEGINNING_OF_SENTENCE : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_BEGINNING_OF_SENTENCE" ; break; 
		case I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_UI_LIST_OR_MENU : szUcalenderDFType = "I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_UI_LIST_OR_MENU" ; break; 
		default : szUcalenderDFType = "Unknown Udate Display context type" ; break;
	}
	return szUcalenderDFType;
}

/**
 * @function 		UbrkGetIteratorType
 * @description	 	Maps Ubrk Iterator type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			Ubrk Iterator type represented as string
 */
char* UbrkGetIteratorType(int nRet)
{
	char *szUcalenderDFType = NULL;

	switch(nRet)
	{
		case I18N_UBRK_CHARACTER : szUcalenderDFType = "I18N_UBRK_CHARACTER" ; break; 
		case I18N_UBRK_WORD : szUcalenderDFType = "I18N_UBRK_WORD" ; break; 
		case I18N_UBRK_LINE : szUcalenderDFType = "I18N_UBRK_LINE" ; break; 
		case I18N_UBRK_SENTENCE : szUcalenderDFType = "I18N_UBRK_SENTENCE" ; break; 
		default : szUcalenderDFType = "Unknown Ubrk Iterator type" ; break;
	}
	return szUcalenderDFType;
}

/**
 * @function 		UdatepgGetDateTimePatternField
 * @description	 	Maps udatepg date time pattern filed type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			udatepg date time pattern filed as string
 */
char* UdatepgGetDateTimePatternField(int nRet)
{
	char *szVal = NULL;

	switch(nRet)
	{
		case I18N_UDATEPG_ERA_FIELD : 					szVal = "I18N_UDATEPG_ERA_FIELD" ; 					break; 
		case I18N_UDATEPG_YEAR_FIELD : 					szVal = "I18N_UDATEPG_YEAR_FIELD" ; 				break; 
		case I18N_UDATEPG_QUARTER_FIELD : 				szVal = "I18N_UDATEPG_QUARTER_FIELD" ; 				break; 
		case I18N_UDATEPG_MONTH_FIELD : 				szVal = "I18N_UDATEPG_MONTH_FIELD" ; 				break;
		case I18N_UDATEPG_WEEK_OF_YEAR_FIELD : 			szVal = "I18N_UDATEPG_WEEK_OF_YEAR_FIELD" ; 		break; 
		case I18N_UDATEPG_WEEK_OF_MONTH_FIELD : 		szVal = "I18N_UDATEPG_WEEK_OF_MONTH_FIELD" ; 		break;
		case I18N_UDATEPG_WEEKDAY_FIELD : 				szVal = "I18N_UDATEPG_WEEKDAY_FIELD" ; 				break; 
		case I18N_UDATEPG_DAY_OF_YEAR_FIELD :			szVal = "I18N_UDATEPG_DAY_OF_YEAR_FIELD" ; 			break;
		case I18N_UDATEPG_DAY_OF_WEEK_IN_MONTH_FIELD : 	szVal = "I18N_UDATEPG_DAY_OF_WEEK_IN_MONTH_FIELD" ; break;
		case I18N_UDATEPG_DAY_FIELD : 					szVal = "I18N_UDATEPG_DAY_FIELD" ; 					break;
		case I18N_UDATEPG_DAYPERIOD_FIELD : 			szVal = "I18N_UDATEPG_DAYPERIOD_FIELD" ; 			break; 
		case I18N_UDATEPG_HOUR_FIELD : 					szVal = "I18N_UDATEPG_HOUR_FIELD" ; 				break; 
		case I18N_UDATEPG_MINUTE_FIELD : 				szVal = "I18N_UDATEPG_MINUTE_FIELD" ; 				break;
		case I18N_UDATEPG_SECOND_FIELD : 				szVal = "I18N_UDATEPG_SECOND_FIELD" ; 				break; 
		case I18N_UDATEPG_FRACTIONAL_SECOND_FIELD : 	szVal = "I18N_UDATEPG_FRACTIONAL_SECOND_FIELD" ; 	break; 
		case I18N_UDATEPG_ZONE_FIELD : 					szVal = "I18N_UDATEPG_ZONE_FIELD" ; 				break; 
		case I18N_UDATEPG_FIELD_COUNT : 				szVal = "I18N_UDATEPG_FIELD_COUNT" ; 				break;
		default : 										szVal = "Unknown Udatepg date time pattern field" ; break;
	}
	return szVal;
}

/**
 * @function 		UdatepgGetDateTimePatternMatchField
 * @description	 	Maps udatepg date time pattern match filed type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			udatepg date time pattern match filed as string
 */
char* UdatepgGetDateTimePatternMatchField(int nRet)
{
	char *szVal = NULL;

	switch(nRet)
	{
		case I18N_UDATEPG_MATCH_NO_OPTIONS : 				szVal = "I18N_UDATEPG_MATCH_NO_OPTIONS" ; 						break; 
		case I18N_UDATEPG_MATCH_HOUR_FIELD_LENGTH : 		szVal = "I18N_UDATEPG_MATCH_HOUR_FIELD_LENGTH" ; 				break; 
		case I18N_UDATEPG_MATCH_ALL_FIELDS_LENGTH : 		szVal = "I18N_UDATEPG_MATCH_ALL_FIELDS_LENGTH" ; 				break; 
		default : 										    szVal = "Unknown Udatepg date time pattern match field" ; 		break;
	}
	return szVal;
}

/**
 * @function 		UnumberGetFormatAttr
 * @description	 	Maps unumber format attribute filed type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			unumber format attribute filed as string
 */
char* UnumberGetFormatAttr(int nRet)
{
	char *szVal = NULL;

	switch(nRet)
	{
		case I18N_UNUMBER_PARSE_INT_ONLY :      				szVal = "I18N_UNUMBER_PARSE_INT_ONLY" ; 					break;              
		case I18N_UNUMBER_GROUPING_USED :         			 	szVal = "I18N_UNUMBER_GROUPING_USED" ; 						break;          
		case I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN: 				szVal = "I18N_UNUMBER_DECIMAL_ALWAYS_SHOWN" ; 				break;              
		case I18N_UNUMBER_MAX_INTEGER_DIGITS: 					szVal = "I18N_UNUMBER_MAX_INTEGER_DIGITS" ; 				break;                
		case I18N_UNUMBER_MIN_INTEGER_DIGITS: 					szVal = "I18N_UNUMBER_MIN_INTEGER_DIGITS" ; 				break;                
		case I18N_UNUMBER_INTEGER_DIGITS: 						szVal = "I18N_UNUMBER_INTEGER_DIGITS" ; 					break;                    
		case I18N_UNUMBER_MAX_FRACTION_DIGITS: 					szVal = "I18N_UNUMBER_MAX_FRACTION_DIGITS" ; 				break;               
		case I18N_UNUMBER_MIN_FRACTION_DIGITS: 					szVal = "I18N_UNUMBER_MIN_FRACTION_DIGITS" ; 				break;               
		case I18N_UNUMBER_FRACTION_DIGITS: 						szVal = "I18N_UNUMBER_FRACTION_DIGITS" ; 					break;                   
		case I18N_UNUMBER_MULTIPLIER: 							szVal = "I18N_UNUMBER_MULTIPLIER" ; 						break;                        
		case I18N_UNUMBER_GROUPING_SIZE: 						szVal = "I18N_UNUMBER_GROUPING_SIZE" ; 						break;                     
		case I18N_UNUMBER_ROUNDING_MODE: 						szVal = "I18N_UNUMBER_ROUNDING_MODE" ; 						break;                     
		case I18N_UNUMBER_ROUNDING_INCREMENT: 					szVal = "I18N_UNUMBER_ROUNDING_INCREMENT" ; 				break;                
		case I18N_UNUMBER_FORMAT_WIDTH: 						szVal = "I18N_UNUMBER_FORMAT_WIDTH" ; 						break;                      
		case I18N_UNUMBER_PADDING_POSITION: 					szVal = "I18N_UNUMBER_PADDING_POSITION" ; 					break;                  
		case I18N_UNUMBER_SECONDARY_GROUPING_SIZE: 				szVal = "I18N_UNUMBER_SECONDARY_GROUPING_SIZE" ; 			break;           
		case I18N_UNUMBER_SIGNIFICANT_DIGITS_USED: 				szVal = "I18N_UNUMBER_SIGNIFICANT_DIGITS_USED" ; 			break;           
		case I18N_UNUMBER_MIN_SIGNIFICANT_DIGITS: 				szVal = "I18N_UNUMBER_MIN_SIGNIFICANT_DIGITS" ; 			break;            
		case I18N_UNUMBER_MAX_SIGNIFICANT_DIGITS: 				szVal = "I18N_UNUMBER_MAX_SIGNIFICANT_DIGITS" ; 			break;            
		case I18N_UNUMBER_LENIENT_PARSE: 						szVal = "I18N_UNUMBER_LENIENT_PARSE" ; 						break;                     
		case I18N_UNUM_SCALE: 									szVal = "I18N_UNUM_SCALE" ; 								break;                                
		case I18N_UNUM_FORMAT_FAIL_IF_MORE_THAN_MAX_DIGITS: 	szVal = "I18N_UNUM_FORMAT_FAIL_IF_MORE_THAN_MAX_DIGITS" ; 	break; 
		case I18N_UNUM_PARSE_NO_EXPONENT: 						szVal = "I18N_UNUM_PARSE_NO_EXPONENT" ; 					break; 
		default: 												szVal = "Unknown unumber format attribute" ; 				break; 
	}
	return szVal;
}




/**
 * @function 		UnumberGetFormatTextAttr
 * @description	 	Maps unumber format attribute filed type enum values to string.
 * @parameter		nRet : result code returned
 * @return 			unumber format attribute field as string
 */
char* UnumberGetFormatTextAttr(int nRet)
{
	char *szVal = NULL;

	switch(nRet)
	{
		case I18N_UNUMBER_POSITIVE_PREFIX : 		szVal = "I18N_UNUMBER_POSITIVE_PREFIX" ; 					break; 
		case I18N_UNUMBER_POSITIVE_SUFFIX : 		szVal = "I18N_UNUMBER_POSITIVE_SUFFIX" ; 					break; 
		case I18N_UNUMBER_NEGATIVE_PREFIX : 		szVal = "I18N_UNUMBER_NEGATIVE_PREFIX" ; 					break; 
		case I18N_UNUMBER_NEGATIVE_SUFFIX : 		szVal = "I18N_UNUMBER_NEGATIVE_SUFFIX" ; 					break; 
		case I18N_UNUMBER_PADDING_CHARACTER : 		szVal = "I18N_UNUMBER_PADDING_CHARACTER" ; 					break; 
		case I18N_UNUMBER_CURRENCY_CODE : 			szVal = "I18N_UNUMBER_CURRENCY_CODE" ; 						break;
		case I18N_UNUMBER_DEFAULT_RULESET : 		szVal = "I18N_UNUMBER_DEFAULT_RULESET" ; 					break;
		case I18N_UNUMBER_PUBLIC_RULESETS : 		szVal = "I18N_UNUMBER_PUBLIC_RULESETS" ; 					break;
		default : 									szVal = "Unknown Udatepg date time pattern match field" ; 	break;
	}
	return szVal;
}
/**
 * @function            UcsdetGetPreFlight
 * @description          Converts an array of unicode characters to an array of codepage characters.
 * @parameter            i18n_uchar *src,  int32_t length, i18n_ucnv_h h_cnv
 * @return                      size of codepage characters
 */

int32_t UcsdetGetPreFlight(const i18n_uchar *src, int32_t length, i18n_ucnv_h h_cnv)
{
	int status;
	char buffer[1024];
	char *pszDest, *pszDestLimit = buffer + sizeof(buffer);
	const i18n_uchar *pszSrcLimit = src + length;
	int32_t result = 0;

	do {
		pszDest = buffer;
		status = I18N_ERROR_NONE;
		status = i18n_ucnv_from_unicode(h_cnv, &pszDest, pszDestLimit, &src, pszSrcLimit, 0, true);
		result += (int32_t) (pszDest - buffer);
	} while (status == I18N_ERROR_BUFFER_OVERFLOW);

	return result;
}
/**
 * @function            UcsdetGetBytes
 * @description         extracts and returns the string of bytes in src
 * @parameter           i18n_uchar *src,  int32_t length, char *codepage,  int32_t *byte_length
 * @return              string of bytes
 */

char *UcsdetGetBytes(const i18n_uchar *src, int32_t length, const char *codepage, int32_t *byte_length)
{
	i18n_ucnv_h h_cnv = NULL;
        int nRet = -1;
	nRet = i18n_ucnv_create(codepage, &h_cnv);
        if(nRet != I18N_ERROR_NONE || h_cnv == NULL)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_create failed with error code %s\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
                return NULL;
        }
	int32_t byte_count = UcsdetGetPreFlight(src, length, h_cnv);
	const i18n_uchar *pszSrcLimit = src + length;
	char *pszBytes = (char *) malloc((byte_count+1) * sizeof(char));
	char *pszDest = pszBytes, *pszDestLimit = pszBytes + byte_count + 1;

	nRet = i18n_ucnv_from_unicode(h_cnv, &pszDest, pszDestLimit, &src, pszSrcLimit, 0, true);
        if(nRet != I18N_ERROR_NONE)
        {
                FPRINTF("\\n[Line : %d][%s] i18n_ucnv_from_unicode failed with error code %s\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
                return NULL;
        }

	nRet = i18n_ucnv_destroy(h_cnv);
        PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ucnv_destroy", BaseUtilsGetError(nRet));

	*byte_length = byte_count;
	return pszBytes;
}
/** @} */

