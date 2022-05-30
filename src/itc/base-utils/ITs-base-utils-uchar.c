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

int gBufSize = 50;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUchar

/**
* @function 		ITs_base_utils_uchar_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_uchar_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bBaseUtilsInitFlag = true;
	return;
}

/**
* @function 		ITs_base_utils_uchar_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_uchar_cleanup(void)
{
	g_bBaseUtilsInitFlag = false;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/*********************************Callback Started*****************************/

/**
* @function 		CountTitlecaseLettersCB
* @description	 	Callback function which is invoked when i18n_uchar_enum_char_types is called
* @parameter		void *context, i18n_uchar32 start, i18n_uchar32 limit, i18n_uchar_category_e type to be passed
* @return 		i18n_ubool
*/
static i18n_ubool CountTitlecaseLettersCB(void *context, i18n_uchar32 start, i18n_uchar32 limit, i18n_uchar_category_e type)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] CountTitlecaseLettersCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	return true;
}

/**
* @function 		DoSampleCB
* @description	 	Callback function which is invoked when i18n_uchar_enum_char_names is called
* @parameter		void *context, i18n_uchar32 code, i18n_uchar_u_char_name_choice_e name_choice, const char *name, int32_t length
* @return 		i18n_ubool
*/
static i18n_ubool DoSampleCB(void *context, i18n_uchar32 code, i18n_uchar_u_char_name_choice_e name_choice, const char *name, int32_t length)
{
	FPRINTF("[Line : %d][%s] DoSampleCB callback called\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	return true;
}
/*********************************Callback End*********************************/


//& type: auto
//& purpose: Gets the property value for an enumerated property for a code point.
/**
* @testcase				ITc_i18n_uchar_get_int_property_value_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Gets the property value for an enumerated property for a code point.
* @apitarget			i18n_uchar_get_int_property_value
* @apicovered			i18n_uchar_get_int_property_value
* @passcase				When i18n_uchar_get_int_property_value is successful
* @failcase				If target i18n_uchar_get_int_property_value fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uchar_get_int_property_value_p(void)
{	
	START_TEST;

	i18n_uchar_uproperty_e eUCharProperty[] = 
	{
		I18N_UCHAR_ALPHABETIC,
		I18N_UCHAR_ASCII_HEX_DIGIT,
		I18N_UCHAR_BIDI_CONTROL,
		I18N_UCHAR_BIDI_MIRRORED,
		I18N_UCHAR_DASH,
		I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT,
		I18N_UCHAR_DEPRECATED,
		I18N_UCHAR_DIACRITIC,
		I18N_UCHAR_EXTENDER,
		I18N_UCHAR_FULL_COMPOSITION_EXCLUSION,
		I18N_UCHAR_GRAPHEME_BASE,
		I18N_UCHAR_GRAPHEME_EXTEND,
		I18N_UCHAR_GRAPHEME_LINK,
		I18N_UCHAR_HEX_DIGIT,
		I18N_UCHAR_HYPHEN,
		I18N_UCHAR_ID_CONTINUE,
		I18N_UCHAR_ID_START,
		I18N_UCHAR_IDEOGRAPHIC,
		I18N_UCHAR_IDS_BINARY_OPERATOR,
		I18N_UCHAR_IDS_TRINARY_OPERATOR,
		I18N_UCHAR_JOIN_CONTROL,
		I18N_UCHAR_LOGICAL_ORDER_EXCEPTION,
		I18N_UCHAR_LOWERCASE,
		I18N_UCHAR_MATH,
		I18N_UCHAR_NONCHARACTER_CODE_POINT,
		I18N_UCHAR_QUOTATION_MARK,
		I18N_UCHAR_RADICAL,
		I18N_UCHAR_SOFT_DOTTED,
		I18N_UCHAR_TERMINAL_PUNCTUATION,
		I18N_UCHAR_UNIFIED_IDEOGRAPH,
		I18N_UCHAR_UPPERCASE,
		I18N_UCHAR_WHITE_SPACE,
		I18N_UCHAR_XID_CONTINUE,
		I18N_UCHAR_XID_START,
		I18N_UCHAR_CASE_SENSITIVE,
		I18N_UCHAR_S_TERM,
		I18N_UCHAR_VARIATION_SELECTOR,
		I18N_UCHAR_NFD_INERT,
		I18N_UCHAR_NFKD_INERT,
		I18N_UCHAR_NFC_INERT,
		I18N_UCHAR_NFKC_INERT,
		I18N_UCHAR_SEGMENT_STARTER,
		I18N_UCHAR_PATTERN_SYNTAX,
		I18N_UCHAR_PATTERN_WHITE_SPACE,
		I18N_UCHAR_POSIX_ALNUM,
		I18N_UCHAR_POSIX_BLANK,
		I18N_UCHAR_POSIX_GRAPH,
		I18N_UCHAR_POSIX_PRINT,
		I18N_UCHAR_POSIX_XDIGIT,
		I18N_UCHAR_CASED,
		I18N_UCHAR_CASE_IGNORABLE,
		I18N_UCHAR_CHANGES_WHEN_LOWERCASED,
		I18N_UCHAR_CHANGES_WHEN_UPPERCASED,
		I18N_UCHAR_CHANGES_WHEN_TITLECASED,
		I18N_UCHAR_CHANGES_WHEN_CASEFOLDED,
		I18N_UCHAR_CHANGES_WHEN_CASEMAPPED,
		I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED,
		I18N_UCHAR_EMOJI,
		I18N_UCHAR_EMOJI_PRESENTATION,
		I18N_UCHAR_EMOJI_MODIFIER,
		I18N_UCHAR_EMOJI_MODIFIER_BASE,
		I18N_UCHAR_BINARY_LIMIT,
		I18N_UCHAR_BIDI_CLASS,
		I18N_UCHAR_BLOCK,
		I18N_UCHAR_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_DECOMPOSITION_TYPE,
		I18N_UCHAR_EAST_ASIAN_WIDTH,
		I18N_UCHAR_GENERAL_CATEGORY,
		I18N_UCHAR_JOINING_GROUP,
		I18N_UCHAR_JOINING_TYPE,
		I18N_UCHAR_LINE_BREAK,
		I18N_UCHAR_NUMERIC_TYPE,
		I18N_UCHAR_SCRIPT,
		I18N_UCHAR_HANGUL_SYLLABLE_TYPE,
		I18N_UCHAR_NFD_QUICK_CHECK,
		I18N_UCHAR_NFKD_QUICK_CHECK,
		I18N_UCHAR_NFC_QUICK_CHECK,
		I18N_UCHAR_NFKC_QUICK_CHECK,
		I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_GRAPHEME_CLUSTER_BREAK,
		I18N_UCHAR_SENTENCE_BREAK,
		I18N_UCHAR_WORD_BREAK,
		I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE,
		I18N_UCHAR_INT_LIMIT,
		I18N_UCHAR_GENERAL_CATEGORY_MASK,
		I18N_UCHAR_MASK_LIMIT,
		I18N_UCHAR_NUMERIC_VALUE,
		I18N_UCHAR_DOUBLE_LIMIT,
		I18N_UCHAR_AGE,
		I18N_UCHAR_BIDI_MIRRORING_GLYPH,
		I18N_UCHAR_CASE_FOLDING,
		I18N_UCHAR_LOWERCASE_MAPPING,
		I18N_UCHAR_NAME,
		I18N_UCHAR_SIMPLE_CASE_FOLDING,
		I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING,
		I18N_UCHAR_SIMPLE_TITLECASE_MAPPING,
		I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING,
		I18N_UCHAR_TITLECASE_MAPPING,
		I18N_UCHAR_UPPERCASE_MAPPING,
		I18N_UCHAR_BIDI_PAIRED_BRACKET,
		I18N_UCHAR_STRING_LIMIT,
		I18N_UCHAR_SCRIPT_EXTENSIONS,
		I18N_UCHAR_OTHER_PROPERTY_LIMIT,
		I18N_UCHAR_INVALID_CODE
	};

	int nEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		i18n_uchar32 uChar32TextCode = 0xA;
		int nPropertyValue = 0;
		FPRINTF("[Line : %d][%s] Executing i18n_uchar_get_int_property_value with eUCharProperty = %s\\n", __LINE__, API_NAMESPACE, uCharPropertyName(eUCharProperty[nEnumCounter]));

		int nRetVal = i18n_uchar_get_int_property_value(uChar32TextCode, eUCharProperty[nEnumCounter], &nPropertyValue);
		switch(eUCharProperty[nEnumCounter])
		{
			case I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_BPT_NONE, I18N_UCHAR_U_BPT_CLOSE, "i18n_uchar_get_int_property_value");
				break;

			case I18N_UCHAR_BIDI_CLASS: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_LEFT_TO_RIGHT, I18N_UCHAR_U_POP_DIRECTIONAL_ISOLATE, "i18n_uchar_get_int_property_value");
				break;
				
			case I18N_UCHAR_JOINING_GROUP: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_JG_NO_JOINING_GROUP, I18N_UCHAR_U_JG_AFRICAN_QAF, "i18n_uchar_get_int_property_value");
				break;
			
			case I18N_UCHAR_WORD_BREAK: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_WB_OTHER, I18N_UCHAR_U_WB_ZWJ, "i18n_uchar_get_int_property_value");
				break;
			
			default	: 
				PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_int_property_value", BaseUtilsGetError(nRetVal));
				break;
		}
	}
	return 0;
}



//& type: auto
//& purpose: Returns the Unicode allocation block that contains the character.
/**
* @testcase				ITc_i18n_uchar_get_ublock_code_p
* @since_tizen 			2.3
* @author            	SRID(m.khalid)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @scenario				Returns the Unicode allocation block that contains the character.
* @apitarget			i18n_uchar_get_ublock_code
* @apicovered			i18n_uchar_get_ublock_code
* @passcase				When i18n_uchar_get_ublock_code is successful
* @failcase				If target i18n_uchar_get_ublock_code fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_uchar_get_ublock_code_p(void)
{	
	START_TEST;

	i18n_uchar_ublock_code_e eUCharBlockCode[] = {	I18N_UCHAR_UBLOCK_NO_BLOCK, 
		I18N_UCHAR_UBLOCK_BASIC_LATIN, 
		I18N_UCHAR_UBLOCK_LATIN_1_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_A, 
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_B, 
		I18N_UCHAR_UBLOCK_IPA_EXTENSIONS, 
		I18N_UCHAR_UBLOCK_SPACING_MODIFIER_LETTERS, 
		I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS, 
		I18N_UCHAR_UBLOCK_GREEK, 
		I18N_UCHAR_UBLOCK_CYRILLIC, 
		I18N_UCHAR_UBLOCK_ARMENIAN, 
		I18N_UCHAR_UBLOCK_HEBREW, 
		I18N_UCHAR_UBLOCK_ARABIC, 
		I18N_UCHAR_UBLOCK_SYRIAC, 
		I18N_UCHAR_UBLOCK_THAANA, 
		I18N_UCHAR_UBLOCK_DEVANAGARI, 
		I18N_UCHAR_UBLOCK_BENGALI, 
		I18N_UCHAR_UBLOCK_GURMUKHI, 
		I18N_UCHAR_UBLOCK_GUJARATI, 
		I18N_UCHAR_UBLOCK_ORIYA, 
		I18N_UCHAR_UBLOCK_TAMIL, 
		I18N_UCHAR_UBLOCK_TELUGU, 
		I18N_UCHAR_UBLOCK_KANNADA, 
		I18N_UCHAR_UBLOCK_MALAYALAM, 
		I18N_UCHAR_UBLOCK_SINHALA, 
		I18N_UCHAR_UBLOCK_THAI, 
		I18N_UCHAR_UBLOCK_LAO, 
		I18N_UCHAR_UBLOCK_TIBETAN, 
		I18N_UCHAR_UBLOCK_MYANMAR, 
		I18N_UCHAR_UBLOCK_GEORGIAN, 
		I18N_UCHAR_UBLOCK_HANGUL_JAMO, 
		I18N_UCHAR_UBLOCK_ETHIOPIC, 
		I18N_UCHAR_UBLOCK_CHEROKEE, 
		I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS, 
		I18N_UCHAR_UBLOCK_OGHAM, 
		I18N_UCHAR_UBLOCK_RUNIC, 
		I18N_UCHAR_UBLOCK_KHMER, 
		I18N_UCHAR_UBLOCK_MONGOLIAN, 
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_ADDITIONAL,
		I18N_UCHAR_UBLOCK_GREEK_EXTENDED, 
		I18N_UCHAR_UBLOCK_GENERAL_PUNCTUATION, 
		I18N_UCHAR_UBLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS, 
		I18N_UCHAR_UBLOCK_CURRENCY_SYMBOLS, 
		I18N_UCHAR_UBLOCK_COMBINING_MARKS_FOR_SYMBOLS, 
		I18N_UCHAR_UBLOCK_LETTERLIKE_SYMBOLS, 
		I18N_UCHAR_UBLOCK_NUMBER_FORMS, 
		I18N_UCHAR_UBLOCK_ARROWS, 
		I18N_UCHAR_UBLOCK_MATHEMATICAL_OPERATORS, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_TECHNICAL, 
		I18N_UCHAR_UBLOCK_CONTROL_PICTURES, 
		I18N_UCHAR_UBLOCK_OPTICAL_CHARACTER_RECOGNITION, 
		I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERICS, 
		I18N_UCHAR_UBLOCK_BOX_DRAWING, 
		I18N_UCHAR_UBLOCK_BLOCK_ELEMENTS, 
		I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS, 
		I18N_UCHAR_UBLOCK_DINGBATS, 
		I18N_UCHAR_UBLOCK_BRAILLE_PATTERNS, 
		I18N_UCHAR_UBLOCK_CJK_RADICALS_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_KANGXI_RADICALS, 
		I18N_UCHAR_UBLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS, 
		I18N_UCHAR_UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION, 
		I18N_UCHAR_UBLOCK_HIRAGANA, 
		I18N_UCHAR_UBLOCK_KATAKANA, 
		I18N_UCHAR_UBLOCK_BOPOMOFO, 
		I18N_UCHAR_UBLOCK_HANGUL_COMPATIBILITY_JAMO, 
		I18N_UCHAR_UBLOCK_KANBUN, 
		I18N_UCHAR_UBLOCK_BOPOMOFO_EXTENDED, 
		I18N_UCHAR_UBLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS, 
		I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY, 
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A, 
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS, 
		I18N_UCHAR_UBLOCK_YI_SYLLABLES, 
		I18N_UCHAR_UBLOCK_YI_RADICALS, 
		I18N_UCHAR_UBLOCK_HANGUL_SYLLABLES, 
		I18N_UCHAR_UBLOCK_HIGH_SURROGATES, 
		I18N_UCHAR_UBLOCK_HIGH_PRIVATE_USE_SURROGATES, 
		I18N_UCHAR_UBLOCK_LOW_SURROGATES, 
		I18N_UCHAR_UBLOCK_PRIVATE_USE_AREA,
		I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS, 
		I18N_UCHAR_UBLOCK_ALPHABETIC_PRESENTATION_FORMS, 
		I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_A, 
		I18N_UCHAR_UBLOCK_COMBINING_HALF_MARKS, 
		I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_FORMS, 
		I18N_UCHAR_UBLOCK_SMALL_FORM_VARIANTS, 
		I18N_UCHAR_UBLOCK_ARABIC_PRESENTATION_FORMS_B, 
		I18N_UCHAR_UBLOCK_SPECIALS, 
		I18N_UCHAR_UBLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS, 
		I18N_UCHAR_UBLOCK_OLD_ITALIC, 
		I18N_UCHAR_UBLOCK_GOTHIC, 
		I18N_UCHAR_UBLOCK_DESERET, 
		I18N_UCHAR_UBLOCK_BYZANTINE_MUSICAL_SYMBOLS, 
		I18N_UCHAR_UBLOCK_MUSICAL_SYMBOLS, 
		I18N_UCHAR_UBLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS, 
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B, 
		I18N_UCHAR_UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_TAGS, 
		I18N_UCHAR_UBLOCK_CYRILLIC_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_TAGALOG, 
		I18N_UCHAR_UBLOCK_HANUNOO, 
		I18N_UCHAR_UBLOCK_BUHID, 
		I18N_UCHAR_UBLOCK_TAGBANWA, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_A, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_B, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS, 
		I18N_UCHAR_UBLOCK_KATAKANA_PHONETIC_EXTENSIONS, 
		I18N_UCHAR_UBLOCK_VARIATION_SELECTORS, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B, 
		I18N_UCHAR_UBLOCK_LIMBU, 
		I18N_UCHAR_UBLOCK_TAI_LE, 
		I18N_UCHAR_UBLOCK_KHMER_SYMBOLS, 
		I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS, 
		I18N_UCHAR_UBLOCK_YIJING_HEXAGRAM_SYMBOLS, 
		I18N_UCHAR_UBLOCK_LINEAR_B_SYLLABARY, 
		I18N_UCHAR_UBLOCK_LINEAR_B_IDEOGRAMS, 
		I18N_UCHAR_UBLOCK_AEGEAN_NUMBERS, 
		I18N_UCHAR_UBLOCK_UGARITIC, 
		I18N_UCHAR_UBLOCK_SHAVIAN, 
		I18N_UCHAR_UBLOCK_OSMANYA, 
		I18N_UCHAR_UBLOCK_CYPRIOT_SYLLABARY, 
		I18N_UCHAR_UBLOCK_TAI_XUAN_JING_SYMBOLS, 
		I18N_UCHAR_UBLOCK_VARIATION_SELECTORS_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_ANCIENT_GREEK_MUSICAL_NOTATION, 
		I18N_UCHAR_UBLOCK_ANCIENT_GREEK_NUMBERS, 
		I18N_UCHAR_UBLOCK_ARABIC_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_BUGINESE, 
		I18N_UCHAR_UBLOCK_CJK_STROKES, 
		I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_COPTIC, 
		I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED, 
		I18N_UCHAR_UBLOCK_ETHIOPIC_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_GEORGIAN_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_GLAGOLITIC, 
		I18N_UCHAR_UBLOCK_KHAROSHTHI, 
		I18N_UCHAR_UBLOCK_MODIFIER_TONE_LETTERS, 
		I18N_UCHAR_UBLOCK_NEW_TAI_LUE, 
		I18N_UCHAR_UBLOCK_OLD_PERSIAN, 
		I18N_UCHAR_UBLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_PUNCTUATION, 
		I18N_UCHAR_UBLOCK_SYLOTI_NAGRI, 
		I18N_UCHAR_UBLOCK_TIFINAGH, 
		I18N_UCHAR_UBLOCK_VERTICAL_FORMS, 
		I18N_UCHAR_UBLOCK_NKO, 
		I18N_UCHAR_UBLOCK_BALINESE, 
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_C, 
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_D, 
		I18N_UCHAR_UBLOCK_PHAGS_PA, 
		I18N_UCHAR_UBLOCK_PHOENICIAN, 
		I18N_UCHAR_UBLOCK_CUNEIFORM, 
		I18N_UCHAR_UBLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION, 
		I18N_UCHAR_UBLOCK_COUNTING_ROD_NUMERALS, 
		I18N_UCHAR_UBLOCK_SUNDANESE, 
		I18N_UCHAR_UBLOCK_LEPCHA, 
		I18N_UCHAR_UBLOCK_OL_CHIKI, 
		I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_A, 
		I18N_UCHAR_UBLOCK_VAI, 
		I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_B, 
		I18N_UCHAR_UBLOCK_SAURASHTRA, 
		I18N_UCHAR_UBLOCK_KAYAH_LI, 
		I18N_UCHAR_UBLOCK_REJANG, 
		I18N_UCHAR_UBLOCK_CHAM, 
		I18N_UCHAR_UBLOCK_ANCIENT_SYMBOLS, 
		I18N_UCHAR_UBLOCK_PHAISTOS_DISC, 
		I18N_UCHAR_UBLOCK_LYCIAN, 
		I18N_UCHAR_UBLOCK_CARIAN, 
		I18N_UCHAR_UBLOCK_LYDIAN, 
		I18N_UCHAR_UBLOCK_MAHJONG_TILES, 
		I18N_UCHAR_UBLOCK_DOMINO_TILES, 
		I18N_UCHAR_UBLOCK_SAMARITAN, 
		I18N_UCHAR_UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED, 
		I18N_UCHAR_UBLOCK_TAI_THAM, 
		I18N_UCHAR_UBLOCK_VEDIC_EXTENSIONS, 
		I18N_UCHAR_UBLOCK_LISU, 
		I18N_UCHAR_UBLOCK_BAMUM, 
		I18N_UCHAR_UBLOCK_COMMON_INDIC_NUMBER_FORMS, 
		I18N_UCHAR_UBLOCK_DEVANAGARI_EXTENDED, 
		I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_A, 
		I18N_UCHAR_UBLOCK_JAVANESE, 
		I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_A, 
		I18N_UCHAR_UBLOCK_TAI_VIET, 
		I18N_UCHAR_UBLOCK_MEETEI_MAYEK, 
		I18N_UCHAR_UBLOCK_HANGUL_JAMO_EXTENDED_B, 
		I18N_UCHAR_UBLOCK_IMPERIAL_ARAMAIC, 
		I18N_UCHAR_UBLOCK_OLD_SOUTH_ARABIAN, 
		I18N_UCHAR_UBLOCK_AVESTAN, 
		I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PARTHIAN, 
		I18N_UCHAR_UBLOCK_INSCRIPTIONAL_PAHLAVI, 
		I18N_UCHAR_UBLOCK_OLD_TURKIC, 
		I18N_UCHAR_UBLOCK_RUMI_NUMERAL_SYMBOLS, 
		I18N_UCHAR_UBLOCK_KAITHI, 
		I18N_UCHAR_UBLOCK_EGYPTIAN_HIEROGLYPHS, 
		I18N_UCHAR_UBLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C, 
		I18N_UCHAR_UBLOCK_MANDAIC, 
		I18N_UCHAR_UBLOCK_BATAK, 
		I18N_UCHAR_UBLOCK_ETHIOPIC_EXTENDED_A, 
		I18N_UCHAR_UBLOCK_BRAHMI, 
		I18N_UCHAR_UBLOCK_BAMUM_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_KANA_SUPPLEMENT, 
		I18N_UCHAR_UBLOCK_PLAYING_CARDS, 
		I18N_UCHAR_UBLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS, 
		I18N_UCHAR_UBLOCK_EMOTICONS, 
		I18N_UCHAR_UBLOCK_TRANSPORT_AND_MAP_SYMBOLS, 
		I18N_UCHAR_UBLOCK_ALCHEMICAL_SYMBOLS, 
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D, 
		I18N_UCHAR_UBLOCK_ARABIC_EXTENDED_A,
		I18N_UCHAR_UBLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS,
		I18N_UCHAR_UBLOCK_CHAKMA,
		I18N_UCHAR_UBLOCK_MEETEI_MAYEK_EXTENSIONS,
		I18N_UCHAR_UBLOCK_MEROITIC_CURSIVE,
		I18N_UCHAR_UBLOCK_MEROITIC_HIEROGLYPHS,
		I18N_UCHAR_UBLOCK_MIAO,
		I18N_UCHAR_UBLOCK_SHARADA,
		I18N_UCHAR_UBLOCK_SORA_SOMPENG,
		I18N_UCHAR_UBLOCK_SUNDANESE_SUPPLEMENT,
		I18N_UCHAR_UBLOCK_TAKRI,

#if defined(MOBILE) || defined(TIZENIOT) 
		I18N_UCHAR_UBLOCK_BASSA_VAH,                                                   
		/**< Bassa Vah (Since 3.0) */	
		I18N_UCHAR_UBLOCK_CAUCASIAN_ALBANIAN,                                          
		/**< Caucasian Albanian (Since 3.0) */	
		I18N_UCHAR_UBLOCK_COPTIC_EPACT_NUMBERS,                                        
		/**< Coptic Epact Numbers (Since 3.0) */	
		I18N_UCHAR_UBLOCK_COMBINING_DIACRITICAL_MARKS_EXTENDED,                         
		/**< Combining Diacritical Marks Extended (Since 3.0) */	
		I18N_UCHAR_UBLOCK_DUPLOYAN,                                                    
		/**< Duployan (Since 3.0) */	
		I18N_UCHAR_UBLOCK_ELBASAN,                                                     
		/**< Elbasan (Since 3.0) */	
		I18N_UCHAR_UBLOCK_GEOMETRIC_SHAPES_EXTENDED,                                   
		/**< Geometric Shapes Extended (Since 3.0) */	
		I18N_UCHAR_UBLOCK_GRANTHA,                                                     
		/**< Grantha (Since 3.0) */	
		I18N_UCHAR_UBLOCK_KHOJKI,                                                      
		/**< Khojki (Since 3.0) */	
		I18N_UCHAR_UBLOCK_KHUDAWADI,                                                   
		/**< Khudawadi (Since 3.0) */	
		I18N_UCHAR_UBLOCK_LATIN_EXTENDED_E,                                            
		/**< Latin Extended E (Since 3.0) */	
		I18N_UCHAR_UBLOCK_LINEAR_A,                                                    
		/**< Linear A (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MAHAJANI,                                                    
		/**< Mahajani (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MANICHAEAN,                                                  
		/**< Manichaean (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MENDE_KIKAKUI,                                               
		/**< Mende Kikakui (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MODI,                                                        
		/**< Modi (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MRO,                                                         
		/**< Mro (Since 3.0) */	
		I18N_UCHAR_UBLOCK_MYANMAR_EXTENDED_B,                                          
		/**< Myanmar Extended B (Since 3.0) */	
		I18N_UCHAR_UBLOCK_NABATAEAN,                                                   
		/**< Nabataean (Since 3.0) */	
		I18N_UCHAR_UBLOCK_OLD_NORTH_ARABIAN,                                           
		/**< Old North Arabian (Since 3.0) */	
		I18N_UCHAR_UBLOCK_OLD_PERMIC,                                                  
		/**< Old Permic (Since 3.0) */	
		I18N_UCHAR_UBLOCK_ORNAMENTAL_DINGBATS,                                         
		/**< Ornamental Dingbats (Since 3.0) */	
		I18N_UCHAR_UBLOCK_PAHAWH_HMONG,                                                
		/**< Pahawh Hmong (Since 3.0) */	
		I18N_UCHAR_UBLOCK_PALMYRENE,                                                   
		/**< Palmyrene (Since 3.0) */	
		I18N_UCHAR_UBLOCK_PAU_CIN_HAU,                                                 
		/**< Pau Cin Hau (Since 3.0) */	
		I18N_UCHAR_UBLOCK_PSALTER_PAHLAVI,                                             
		/**< Psalter Pahlavi (Since 3.0) */	
		I18N_UCHAR_UBLOCK_SHORTHAND_FORMAT_CONTROLS,                                   
		/**< Shorthand Format Controls (Since 3.0) */	
		I18N_UCHAR_UBLOCK_SIDDHAM,                                                     
		/**< Siddham (Since 3.0) */	
		I18N_UCHAR_UBLOCK_SINHALA_ARCHAIC_NUMBERS ,                                    
		/**< Sinhala Archaic Numbers (Since 3.0) */	
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_ARROWS_C ,                                      
		/**< Supplemental Arrows C (Since 3.0) */	
		I18N_UCHAR_UBLOCK_TIRHUTA ,                                                    
		/**< Tirhuta (Since 3.0) */	
		I18N_UCHAR_UBLOCK_WARANG_CITI ,                                                
		/**< Warang Citi (Since 3.0) */
		I18N_UCHAR_UBLOCK_AHOM,
		/**< Ahom (Since 4.0) */
		I18N_UCHAR_ANATOLIAN_HIEROGLYPHS,
		/**< Hieroglyphs (Since 4.0) */
		I18N_UCHAR_UBLOCK_CHEROKEE_SUPPLEMENT,
		/**< Cherokee Supplement (Since 4.0) */
		I18N_UCHAR_UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_E,
		/**< CJK Unified Ideographs Extension E (Since 4.0) */
		I18N_UCHAR_UBLOCK_EARLY_DYNASTIC_CUNEIFORM,
		/**< Early Dynastic Cuneiform (Since 4.0) */
		I18N_UCHAR_UBLOCK_HATRAN,
		/**< Hatran (Since 4.0) */
		I18N_UCHAR_UBLOCK_MULTANI,
		/**< Multani (Since 4.0) */
		I18N_UCHAR_UBLOCK_OLD_HUNGARIAN,
		/**< Old Hungarian (Since 4.0) */
		I18N_UCHAR_UBLOCK_SUPPLEMENTAL_SYMBOLS_AND_PICTOGRAPHS,
		/**< Supplemental Symbols And Pictographs (Since 4.0) */
		I18N_UCHAR_UBLOCK_SUTTON_SIGNWRITING,
		/**< Sutton Signwritting (Since 4.0) */
		I18N_UCHAR_UBLOCK_ADLAM,
		/**< Adlam (Since 4.0) */
		I18N_UCHAR_UBLOCK_BHAIKSUKI,
		/**< Bhaiksuki (Since 4.0) */
		I18N_UCHAR_UBLOCK_CYRILLIC_EXTENDED_C,
		/**< Cyrillic Extended C (Since 4.0) */
		I18N_UCHAR_UBLOCK_GLAGOLITIC_SUPPLEMENT,
		/**< Glagolitic Supplement (Since 4.0) */
		I18N_UCHAR_UBLOCK_IDEOGRAPHIC_SYMBOLS_AND_PUNCTUATION,
		/**< Ideographic Symbols And Punctation (Since 4.0) */
		I18N_UCHAR_UBLOCK_MARCHEN,
		/**< Marchen (Since 4.0) */
		I18N_UCHAR_UBLOCK_MONGOLIAN_SUPPLEMENT,
		/**< Mongolian Supplement (Since 4.0) */
		I18N_UCHAR_UBLOCK_NEWA,
		/**< Newa (Since 4.0) */
		I18N_UCHAR_UBLOCK_OSAGE,
		/**< Osage (Since 4.0) */
		I18N_UCHAR_UBLOCK_TANGUT,
		/**< Tangut (Since 4.0) */
		I18N_UCHAR_UBLOCK_TANGUT_COMPONENTS,
		/**< Tangut Components (Since 4.0) */

#endif  //MOBILE    //End MOBILE

		I18N_UCHAR_UBLOCK_COUNT, 
		I18N_UCHAR_UBLOCK_INVALID_CODE};
	int nEnumSize = sizeof(eUCharBlockCode) / sizeof(eUCharBlockCode[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_uchar_get_ublock_code with eUCharBlockCode = %s\\n", __LINE__, API_NAMESPACE, uCharBlockCode(eUCharBlockCode[nEnumCounter]));
		i18n_uchar32 uChar32TextCode = 0xA;

		int nRetVal = i18n_uchar_get_ublock_code(uChar32TextCode, &eUCharBlockCode[nEnumCounter]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_ublock_code", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

//& type: auto
//& purpose: Checks a binary unicode property for a code point.
/**
* @testcase			ITc_i18n_uchar_has_binary_property_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Checks a binary unicode property for a code point.
* @apitarget			i18n_uchar_has_binary_property
* @apicovered			i18n_uchar_has_binary_property
* @passcase			When i18n_uchar_has_binary_property is successful
* @failcase			If target i18n_uchar_has_binary_property api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_has_binary_property_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_uproperty_e eUCharProperty[] = {
		I18N_UCHAR_GRAPHEME_BASE,
		I18N_UCHAR_ID_CONTINUE,
		I18N_UCHAR_ID_START,
		I18N_UCHAR_LOWERCASE,
		I18N_UCHAR_XID_CONTINUE,
		I18N_UCHAR_XID_START,
		I18N_UCHAR_CASE_SENSITIVE,
		I18N_UCHAR_NFD_INERT,
		I18N_UCHAR_NFKD_INERT,
		I18N_UCHAR_SEGMENT_STARTER,
		I18N_UCHAR_POSIX_ALNUM,
		I18N_UCHAR_POSIX_GRAPH,
		I18N_UCHAR_POSIX_PRINT,
		I18N_UCHAR_CASED,
		I18N_UCHAR_CHANGES_WHEN_UPPERCASED,
		I18N_UCHAR_CHANGES_WHEN_TITLECASED,
		I18N_UCHAR_CHANGES_WHEN_CASEMAPPED
	};

	int nEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nEnumCounter;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bHasProperty = false;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		bHasProperty = false;
		nRetVal = i18n_uchar_has_binary_property(uChar32TextCode, eUCharProperty[nEnumCounter], &bHasProperty);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_has_binary_property", BaseUtilsGetError(nRetVal));

		if(!bHasProperty)
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_has_binary_property [%s] property has returned bHasProperty FALSE\\n", __LINE__, API_NAMESPACE, uCharPropertyName(eUCharProperty[nEnumCounter]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Checks if a code point has the Alphabetic Unicode unicode property.
/**
* @testcase			ITc_i18n_uchar_is_alphabetic_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Checks if a code point has the Alphabetic Unicode unicode property.
* @apitarget			i18n_uchar_is_alphabetic
* @apicovered			i18n_uchar_is_alphabetic
* @passcase			When i18n_uchar_is_alphabetic is successful
* @failcase			If target i18n_uchar_is_alphabetic api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_alphabetic_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsAlphabetic = false;

	nRetVal = i18n_uchar_is_alphabetic(uChar32TextCode, &bIsAlphabetic);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_alphabetic", BaseUtilsGetError(nRetVal));

	if(!bIsAlphabetic)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_alphabetic returned a false bIsAlphabetic\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Checks if a code point has the Lowercase Unicode property.
/**
* @testcase			ITc_i18n_uchar_is_lowercase_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Checks if a code point has the Lowercase Unicode property.
* @apitarget			i18n_uchar_is_lowercase
* @apicovered			i18n_uchar_is_lowercase
* @passcase			When i18n_uchar_is_lowercase is successful
* @failcase			If target i18n_uchar_is_lowercase api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_lowercase_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsLowerCase = false;

	nRetVal = i18n_uchar_is_lowercase(uChar32TextCode, &bIsLowerCase);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_lowercase", BaseUtilsGetError(nRetVal));

	if(!bIsLowerCase)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_lowercase returned a false bIsLowerCase\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Checks if a code point has the Uppercase Unicode property.
/**
* @testcase			ITc_i18n_uchar_is_uppercase_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Checks if a code point has the Uppercase Unicode property.
* @apitarget			i18n_uchar_is_uppercase
* @apicovered			i18n_uchar_is_uppercase
* @passcase			When i18n_uchar_is_uppercase is successful
* @failcase			If target i18n_uchar_is_uppercase api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_uppercase_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x41;
	i18n_ubool bIsUpperCase = false;

	nRetVal = i18n_uchar_is_uppercase(uChar32TextCode, &bIsUpperCase);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_uppercase", BaseUtilsGetError(nRetVal));

	if(!bIsUpperCase)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_uppercase returned a false bIsUpperCase\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Checks if a code point has the White_Space Unicode property.
/**
* @testcase			ITc_i18n_uchar_is_white_space_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Checks if a code point has the White_Space Unicode property.
* @apitarget			i18n_uchar_is_white_space
* @apicovered			i18n_uchar_is_white_space
* @passcase			When i18n_uchar_is_white_space is successful
* @failcase			If target i18n_uchar_is_white_space api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_white_space_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x20;
	i18n_ubool bIsWhiteSpace = false;

	nRetVal = i18n_uchar_is_white_space(uChar32TextCode, &bIsWhiteSpace);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_white_space", BaseUtilsGetError(nRetVal));

	if(!bIsWhiteSpace)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_white_space returned a false bIsWhiteSpace\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Gets the minimum value for an enumerated/integer/binary Unicode property.
/**
* @testcase			ITc_i18n_uchar_get_int_property_min_value_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the minimum value for an enumerated/integer/binary Unicode property.
* @apitarget			i18n_uchar_get_int_property_min_value
* @apicovered			i18n_uchar_get_int_property_min_value
* @passcase			When i18n_uchar_get_int_property_min_value is successful
* @failcase			If target i18n_uchar_get_int_property_min_value api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_int_property_min_value_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_uproperty_e eUCharProperty[] = {
		I18N_UCHAR_ALPHABETIC,
		I18N_UCHAR_ASCII_HEX_DIGIT,
		I18N_UCHAR_BIDI_CONTROL,
		I18N_UCHAR_BIDI_MIRRORED,
		I18N_UCHAR_DASH,
		I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT,
		I18N_UCHAR_DEPRECATED,
		I18N_UCHAR_DIACRITIC,
		I18N_UCHAR_EXTENDER,
		I18N_UCHAR_FULL_COMPOSITION_EXCLUSION,
		I18N_UCHAR_GRAPHEME_BASE,
		I18N_UCHAR_GRAPHEME_EXTEND,
		I18N_UCHAR_GRAPHEME_LINK,
		I18N_UCHAR_HEX_DIGIT,
		I18N_UCHAR_HYPHEN,
		I18N_UCHAR_ID_CONTINUE,
		I18N_UCHAR_ID_START,
		I18N_UCHAR_IDEOGRAPHIC,
		I18N_UCHAR_IDS_BINARY_OPERATOR,
		I18N_UCHAR_IDS_TRINARY_OPERATOR,
		I18N_UCHAR_JOIN_CONTROL,
		I18N_UCHAR_LOGICAL_ORDER_EXCEPTION,
		I18N_UCHAR_LOWERCASE,
		I18N_UCHAR_MATH,
		I18N_UCHAR_NONCHARACTER_CODE_POINT,
		I18N_UCHAR_QUOTATION_MARK,
		I18N_UCHAR_RADICAL,
		I18N_UCHAR_SOFT_DOTTED,
		I18N_UCHAR_TERMINAL_PUNCTUATION,
		I18N_UCHAR_UNIFIED_IDEOGRAPH,
		I18N_UCHAR_UPPERCASE,
		I18N_UCHAR_WHITE_SPACE,
		I18N_UCHAR_XID_CONTINUE,
		I18N_UCHAR_XID_START,
		I18N_UCHAR_CASE_SENSITIVE,
		I18N_UCHAR_S_TERM,
		I18N_UCHAR_VARIATION_SELECTOR,
		I18N_UCHAR_NFD_INERT,
		I18N_UCHAR_NFKD_INERT,
		I18N_UCHAR_NFC_INERT,
		I18N_UCHAR_NFKC_INERT,
		I18N_UCHAR_SEGMENT_STARTER,
		I18N_UCHAR_PATTERN_SYNTAX,
		I18N_UCHAR_PATTERN_WHITE_SPACE,
		I18N_UCHAR_POSIX_ALNUM,
		I18N_UCHAR_POSIX_BLANK,
		I18N_UCHAR_POSIX_GRAPH,
		I18N_UCHAR_POSIX_PRINT,
		I18N_UCHAR_POSIX_XDIGIT,
		I18N_UCHAR_CASED,
		I18N_UCHAR_CASE_IGNORABLE,
		I18N_UCHAR_CHANGES_WHEN_LOWERCASED,
		I18N_UCHAR_CHANGES_WHEN_UPPERCASED,
		I18N_UCHAR_CHANGES_WHEN_TITLECASED,
		I18N_UCHAR_CHANGES_WHEN_CASEFOLDED,
		I18N_UCHAR_CHANGES_WHEN_CASEMAPPED,
		I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED,
		I18N_UCHAR_BINARY_LIMIT,
		I18N_UCHAR_BIDI_CLASS,
		I18N_UCHAR_INT_START,
		I18N_UCHAR_BLOCK,
		I18N_UCHAR_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_DECOMPOSITION_TYPE,
		I18N_UCHAR_EAST_ASIAN_WIDTH,
		I18N_UCHAR_GENERAL_CATEGORY,
		I18N_UCHAR_JOINING_GROUP,
		I18N_UCHAR_JOINING_TYPE,
		I18N_UCHAR_LINE_BREAK,
		I18N_UCHAR_NUMERIC_TYPE,
		I18N_UCHAR_SCRIPT,
		I18N_UCHAR_HANGUL_SYLLABLE_TYPE,
		I18N_UCHAR_NFD_QUICK_CHECK,
		I18N_UCHAR_NFKD_QUICK_CHECK,
		I18N_UCHAR_NFC_QUICK_CHECK,
		I18N_UCHAR_NFKC_QUICK_CHECK,
		I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_GRAPHEME_CLUSTER_BREAK,
		I18N_UCHAR_SENTENCE_BREAK,
		I18N_UCHAR_WORD_BREAK,
		I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE,
		I18N_UCHAR_INT_LIMIT,
		I18N_UCHAR_GENERAL_CATEGORY_MASK,
		I18N_UCHAR_MASK_START,
		I18N_UCHAR_MASK_LIMIT,
		I18N_UCHAR_NUMERIC_VALUE,
		I18N_UCHAR_DOUBLE_START,
		I18N_UCHAR_DOUBLE_LIMIT,
		I18N_UCHAR_AGE,
		I18N_UCHAR_STRING_START,
		I18N_UCHAR_BIDI_MIRRORING_GLYPH,
		I18N_UCHAR_CASE_FOLDING,
		I18N_UCHAR_LOWERCASE_MAPPING,
		I18N_UCHAR_NAME,
		I18N_UCHAR_SIMPLE_CASE_FOLDING,
		I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING,
		I18N_UCHAR_SIMPLE_TITLECASE_MAPPING,
		I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING,
		I18N_UCHAR_TITLECASE_MAPPING,
		I18N_UCHAR_UPPERCASE_MAPPING,
		I18N_UCHAR_BIDI_PAIRED_BRACKET,
		I18N_UCHAR_STRING_LIMIT,
		I18N_UCHAR_SCRIPT_EXTENSIONS,
		I18N_UCHAR_OTHER_PROPERTY_START,
		I18N_UCHAR_OTHER_PROPERTY_LIMIT
	};

	int nEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nEnumCounter = 0;
	int32_t nIntPropertyMinValue = 0x02;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		nIntPropertyMinValue = 0x02;

		nRetVal = i18n_uchar_get_int_property_min_value(eUCharProperty[nEnumCounter], &nIntPropertyMinValue);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_int_property_min_value", BaseUtilsGetError(nRetVal));

		if(nIntPropertyMinValue)
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_int_property_min_value returned a wrong value nIntPropertyMinValue\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Gets the maximum value for an enumerated/integer/binary Unicode property.
/**
* @testcase			ITc_i18n_uchar_get_int_property_max_value_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the maximum value for an enumerated/integer/binary Unicode property.
* @apitarget			i18n_uchar_get_int_property_max_value
* @apicovered			i18n_uchar_get_int_property_max_value
* @passcase			When i18n_uchar_get_int_property_max_value is successful
* @failcase			If target i18n_uchar_get_int_property_max_value api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_int_property_max_value_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;
	i18n_uchar_uproperty_e eUCharPropertyWithMaxValue = I18N_UCHAR_SCRIPT;
	int nPropertyValue = 0x00;
	int32_t nIntPropertyMaxValue = 0x00;

	nRetVal = i18n_uchar_get_int_property_max_value(eUCharPropertyWithMaxValue, &nIntPropertyMaxValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_int_property_max_value", BaseUtilsGetError(nRetVal));

	if(nIntPropertyMaxValue < nPropertyValue)
	{
		FPRINTF("[Line : %d][%s] Error: i18n_uchar_get_int_property_max_value() returned a wrong value: %d for enum I18N_UCHAR_SCRIPT\\n", __LINE__, API_NAMESPACE, nIntPropertyMaxValue);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Gets the numeric value for a Unicode code point as defined in the Unicode Character Database.
/**
* @testcase			ITc_i18n_uchar_get_numeric_value_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the numeric value for a Unicode code point as defined in the Unicode Character Database.
* @apitarget			i18n_uchar_get_numeric_value
* @apicovered			i18n_uchar_get_numeric_value
* @passcase			When i18n_uchar_get_numeric_value is successful
* @failcase			If target i18n_uchar_get_numeric_value api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_numeric_value_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x09E7;
	double nNumericValue = 0;

	nRetVal = i18n_uchar_get_numeric_value(uChar32TextCode, &nNumericValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_numeric_value", BaseUtilsGetError(nRetVal));

	if(nNumericValue == I18N_U_NO_NUMERIC_VALUE)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_numeric_value returned I18N_U_NO_NUMERIC_VALUE value of nNumericValue\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}


//& type: auto
//& purpose: Determines whether the specified code point has the general category "Ll" (lowercase letter).
/**
* @testcase			ITc_i18n_uchar_is_lowercase_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point has the general category "Ll" (lowercase letter).
* @apitarget			i18n_uchar_is_lowercase
* @apicovered			i18n_uchar_is_lowercase
* @passcase			When i18n_uchar_is_lowercase is successful
* @failcase			If target i18n_uchar_is_lowercase api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_lower_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsLower = false;

	nRetVal = i18n_uchar_is_lower(uChar32TextCode, &bIsLower);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_lower", BaseUtilsGetError(nRetVal));

	if(!bIsLower)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_lower returned a false bIsLower\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point has the general category "Lu" (uppercase letter).
/**
* @testcase			ITc_i18n_uchar_is_upper_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point has the general category "Lu" (uppercase letter).
* @apitarget			i18n_uchar_is_upper
* @apicovered			i18n_uchar_is_upper
* @passcase			When i18n_uchar_is_upper is successful
* @failcase			If target i18n_uchar_is_upper api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_upper_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x42;
	i18n_ubool bIsUpper = false;

	nRetVal = i18n_uchar_is_upper(uChar32TextCode, &bIsUpper);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_upper", BaseUtilsGetError(nRetVal));

	if(!bIsUpper)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_upper returned a false bIsUpper\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a titlecase letter.
/**
* @testcase			ITc_i18n_uchar_is_title_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a titlecase letter.
* @apitarget			i18n_uchar_is_title
* @apicovered			i18n_uchar_is_title
* @passcase			When i18n_uchar_is_title is successful
* @failcase			If target i18n_uchar_is_title api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_title_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x01C8;
	i18n_ubool bIsTitle = false;

	nRetVal = i18n_uchar_is_title(uChar32TextCode, &bIsTitle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_title", BaseUtilsGetError(nRetVal));

	if(!bIsTitle)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_title returned a false bIsTitle\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a digit character according to Java.
/**
* @testcase			ITc_i18n_uchar_is_digit_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a digit character according to Java.
* @apitarget			i18n_uchar_is_digit
* @apicovered			i18n_uchar_is_digit
* @passcase			When i18n_uchar_is_digit is successful
* @failcase			If target i18n_uchar_is_digit api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_digit_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x37;
	i18n_ubool bIsDigit = false;

	nRetVal = i18n_uchar_is_digit(uChar32TextCode, &bIsDigit);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_digit", BaseUtilsGetError(nRetVal));

	if(!bIsDigit)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_digit returned a false bIsDigit\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a letter character.
/**
* @testcase			ITc_i18n_uchar_is_alpha_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a letter character.
* @apitarget			i18n_uchar_is_alpha
* @apicovered			i18n_uchar_is_alpha
* @passcase			When i18n_uchar_is_alpha is successful
* @failcase			If target i18n_uchar_is_alpha api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_alpha_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsAlpha = false;

	nRetVal = i18n_uchar_is_alpha(uChar32TextCode, &bIsAlpha);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_alpha", BaseUtilsGetError(nRetVal));

	if(!bIsAlpha)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_alpha returned a false bIsAlpha\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is an alphanumeric character (letter or digit)
/**
* @testcase			ITc_i18n_uchar_is_alnum_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is an alphanumeric character (letter or digit)
* @apitarget			i18n_uchar_is_alnum
* @apicovered			i18n_uchar_is_alnum
* @passcase			When i18n_uchar_is_alnum is successful
* @failcase			If target i18n_uchar_is_alnum api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_alnum_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsAlnum = false;

	nRetVal = i18n_uchar_is_alnum(uChar32TextCode, &bIsAlnum);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_alnum", BaseUtilsGetError(nRetVal));

	if(!bIsAlnum)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_alnum returned a false bIsAlnum\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a hexadecimal digit.
/**
* @testcase			ITc_i18n_uchar_is_xdigit_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a hexadecimal digit.
* @apitarget			i18n_uchar_is_xdigit
* @apicovered			i18n_uchar_is_xdigit
* @passcase			When i18n_uchar_is_xdigit is successful
* @failcase			If target i18n_uchar_is_xdigit api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_xdigit_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x37;
	i18n_ubool bIsXDigit = false;

	nRetVal = i18n_uchar_is_xdigit(uChar32TextCode, &bIsXDigit);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_xdigit", BaseUtilsGetError(nRetVal));

	if(!bIsXDigit)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_xdigit returned a false bIsXDigit\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a punctuation character.
/**
* @testcase			ITc_i18n_uchar_is_punct_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a punctuation character.
* @apitarget			i18n_uchar_is_punct
* @apicovered			i18n_uchar_is_punct
* @passcase			When i18n_uchar_is_punct is successful
* @failcase			If target i18n_uchar_is_punct api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_punct_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x2018;
	i18n_ubool bIsPunct = false;

	nRetVal = i18n_uchar_is_punct(uChar32TextCode, &bIsPunct);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_punct", BaseUtilsGetError(nRetVal));

	if(!bIsPunct)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_punct returned a false bIsPunct\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a "graphic" character (printable, excluding, spaces).
/**
* @testcase			ITc_i18n_uchar_is_graph_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a "graphic" character (printable, excluding, spaces).
* @apitarget			i18n_uchar_is_graph
* @apicovered			i18n_uchar_is_graph
* @passcase			When i18n_uchar_is_graph is successful
* @failcase			If target i18n_uchar_is_graph api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_graph_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsGraph = false;

	nRetVal = i18n_uchar_is_graph(uChar32TextCode, &bIsGraph);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_graph", BaseUtilsGetError(nRetVal));

	if(!bIsGraph)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_graph returned a false bIsGraph\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a "blank" or "horizontal space", a character that visibly separates words on a line.
/**
* @testcase			ITc_i18n_uchar_is_blank_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a "blank" or "horizontal space", a character that visibly separates words on a line.
* @apitarget			i18n_uchar_is_blank
* @apicovered			i18n_uchar_is_blank
* @passcase			When i18n_uchar_is_blank is successful
* @failcase			If target i18n_uchar_is_blank api fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_blank_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x09;
	i18n_ubool bIsBlank = false;

	nRetVal = i18n_uchar_is_blank(uChar32TextCode, &bIsBlank);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_blank", BaseUtilsGetError(nRetVal));

	if(!bIsBlank)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_blank returned a false bIsBlank\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is "defined", which usually means that it is assigned a character.
/**
* @testcase			ITc_i18n_uchar_is_defined_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is "defined", which usually means that it is assigned a character.
* @apitarget			i18n_uchar_is_defined
* @apicovered			i18n_uchar_is_defined
* @passcase			When i18n_uchar_is_defined is successful
* @failcase			If target api i18n_uchar_is_defined fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_defined_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsDefined = false;

	nRetVal = i18n_uchar_is_defined(uChar32TextCode, &bIsDefined);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_defined", BaseUtilsGetError(nRetVal));

	if(!bIsDefined)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_defined returned a false bIsDefined\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines if the specified character is a space character or not.
/**
* @testcase			ITc_i18n_uchar_is_space_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character is a space character or not.
* @apitarget			i18n_uchar_is_space
* @apicovered			i18n_uchar_is_space
* @passcase			When i18n_uchar_is_space is successful
* @failcase			If target api i18n_uchar_is_space fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_space_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x20;
	i18n_ubool bIsSpace = false;

	nRetVal = i18n_uchar_is_space(uChar32TextCode, &bIsSpace);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_space", BaseUtilsGetError(nRetVal));

	if(!bIsSpace)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_space returned a false bIsSpace\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines if the specified code point is a space character according to Java.
/**
* @testcase			ITc_i18n_uchar_is_java_space_char_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified code point is a space character according to Java.
* @apitarget			i18n_uchar_is_java_space_char
* @apicovered			i18n_uchar_is_java_space_char
* @passcase			When i18n_uchar_is_java_space_char is successful
* @failcase			If target api i18n_uchar_is_java_space_char fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_java_space_char_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x2028;
	i18n_ubool bIsJavaSpaceChar = false;

	nRetVal = i18n_uchar_is_java_space_char(uChar32TextCode, &bIsJavaSpaceChar);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_java_space_char", BaseUtilsGetError(nRetVal));

	if(!bIsJavaSpaceChar)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_java_space_char returned a false bIsJavaSpaceChar\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines if the specified code point is a whitespace character according to Java/ICU.
/**
* @testcase			ITc_i18n_uchar_is_whitespace_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified code point is a whitespace character according to Java/ICU.
* @apitarget			i18n_uchar_is_whitespace
* @apicovered			i18n_uchar_is_whitespace
* @passcase			When i18n_uchar_is_whitespace is successful
* @failcase			If target api i18n_uchar_is_whitespace fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_whitespace_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x20;
	i18n_ubool bIsWhiteSpace = false;

	nRetVal = i18n_uchar_is_whitespace(uChar32TextCode, &bIsWhiteSpace);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_whitespace", BaseUtilsGetError(nRetVal));

	if(!bIsWhiteSpace)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_whitespace returned a false bIsWhiteSpace\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a control character (as defined by this function).
/**
* @testcase			ITc_i18n_uchar_is_control_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a control character (as defined by this function).
* @apitarget			i18n_uchar_is_control
* @apicovered			i18n_uchar_is_control
* @passcase			When i18n_uchar_is_control is successful
* @failcase			If target api i18n_uchar_is_control fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_control_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x7F;
	i18n_ubool bIsControl = false;

	nRetVal = i18n_uchar_is_control(uChar32TextCode, &bIsControl);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_control", BaseUtilsGetError(nRetVal));

	if(!bIsControl)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_control returned a false bIsControl\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is an ISO control code.
/**
* @testcase			ITc_i18n_uchar_is_iso_control_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is an ISO control code.
* @apitarget			i18n_uchar_is_iso_control
* @apicovered			i18n_uchar_is_iso_control
* @passcase			When i18n_uchar_is_iso_control is successful
* @failcase			If target api i18n_uchar_is_iso_control fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_iso_control_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x1F;
	i18n_ubool bIsISOControl = false;

	nRetVal = i18n_uchar_is_iso_control(uChar32TextCode, &bIsISOControl);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_iso_control", BaseUtilsGetError(nRetVal));

	if(!bIsISOControl)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_iso_control returned a false bIsISOControl\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a printable character.
/**
* @testcase			ITc_i18n_uchar_is_printable_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a printable character.
* @apitarget			i18n_uchar_is_printable
* @apicovered			i18n_uchar_is_printable
* @passcase			When i18n_uchar_is_printable is successful
* @failcase			If target api i18n_uchar_is_printable fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_printable_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsPrintable = false;

	nRetVal = i18n_uchar_is_printable(uChar32TextCode, &bIsPrintable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_printable", BaseUtilsGetError(nRetVal));

	if(!bIsPrintable)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_printable returned a false bIsPrintable\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines whether the specified code point is a base character.
/**
* @testcase			ITc_i18n_uchar_is_base_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the specified code point is a base character.
* @apitarget			i18n_uchar_is_base
* @apicovered			i18n_uchar_is_base
* @passcase			When i18n_uchar_is_base is successful
* @failcase			If target api i18n_uchar_is_base fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_base_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsBase = false;

	nRetVal = i18n_uchar_is_base(uChar32TextCode, &bIsBase);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_base", BaseUtilsGetError(nRetVal));

	if(!bIsBase)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_base returned a false bIsBase\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the bidirectional category value for the code point.
/**
* @testcase			ITc_i18n_uchar_char_direction_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the bidirectional category value for the code point.
* @apitarget			i18n_uchar_char_direction
* @apicovered			i18n_uchar_char_direction
* @passcase			When i18n_uchar_char_direction is successful
* @failcase			If target api i18n_uchar_char_direction fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_direction_p(void)
{
	START_TEST;

	i18n_uchar_direction_e nUCharDirection = I18N_UCHAR_U_RIGHT_TO_LEFT;
	i18n_uchar32 uChar32TextCode = 0x6D;
	int nRetVal = I18N_ERROR_NONE;

	nRetVal = i18n_uchar_char_direction(uChar32TextCode, &nUCharDirection);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_direction", BaseUtilsGetError(nRetVal));

	if(nUCharDirection != I18N_UCHAR_U_LEFT_TO_RIGHT)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_char_direction returned a false bIsBase\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Determines whether the code point has the Bidi_Mirrored property.
/**
* @testcase			ITc_i18n_uchar_is_mirrored_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines whether the code point has the Bidi_Mirrored property.
* @apitarget			i18n_uchar_is_mirrored
* @apicovered			i18n_uchar_is_mirrored
* @passcase			When i18n_uchar_is_mirrored is successful
* @failcase			If target api i18n_uchar_is_mirrored fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_mirrored_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x7D;
	i18n_ubool bIsMirrored = false;

	nRetVal = i18n_uchar_is_mirrored(uChar32TextCode, &bIsMirrored);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_mirrored", BaseUtilsGetError(nRetVal));

	if(!bIsMirrored)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_mirrored returned a false bIsMirrored\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the specified character to a "mirror-image" character.
/**
* @testcase			ITc_i18n_uchar_char_mirror_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the specified character to a "mirror-image" character.
* @apitarget			i18n_uchar_char_mirror
* @apicovered			i18n_uchar_char_mirror
* @passcase			When i18n_uchar_char_mirror is successful
* @failcase			If target api i18n_uchar_char_mirror fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_mirror_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x7D;
	i18n_uchar32 uChar32MirrorChar = 0x019C;
	i18n_uchar32 uChar32Result = 0x7B;

	nRetVal = i18n_uchar_char_mirror(uChar32TextCode, &uChar32MirrorChar);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_mirror", BaseUtilsGetError(nRetVal));

	if(uChar32MirrorChar != uChar32Result)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_char_mirror returned different uChar32MirrorChar than result\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the specified character to its paired bracket character.
/**
* @testcase			ITc_i18n_uchar_get_bidi_paired_bracket_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the specified character to its paired bracket character.
* @apitarget			i18n_uchar_get_bidi_paired_bracket
* @apicovered			i18n_uchar_get_bidi_paired_bracket
* @passcase			When i18n_uchar_get_bidi_paired_bracket is successful
* @failcase			If target api i18n_uchar_get_bidi_paired_bracket fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_bidi_paired_bracket_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_uchar32 uChar32BidiPairedBracket = 0x6D;

	nRetVal = i18n_uchar_get_bidi_paired_bracket(uChar32TextCode, &uChar32BidiPairedBracket);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_bidi_paired_bracket", BaseUtilsGetError(nRetVal));

	if(uChar32BidiPairedBracket != 0X6D)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_bidi_paired_bracket returned different value \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the general category value for the code point.
/**
* @testcase			ITc_i18n_uchar_char_type_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the general category value for the code point.
* @apitarget			i18n_uchar_char_type
* @apicovered			i18n_uchar_char_type
* @passcase			When i18n_uchar_char_type is successful
* @failcase			If target api i18n_uchar_char_type fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_type_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	int8_t nCharType = 0;

	nRetVal = i18n_uchar_char_type(uChar32TextCode, &nCharType);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_type", BaseUtilsGetError(nRetVal));

	if(nCharType != 0X2)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_char_type returned different value of nCharType \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Enumerates efficiently all code points with their unicode general categories.
/**
* @testcase			ITc_i18n_uchar_enum_char_types_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Enumerates efficiently all code points with their unicode general categories.
* @apitarget			i18n_uchar_enum_char_types
* @apicovered			i18n_uchar_enum_char_types
* @passcase			When i18n_uchar_enum_char_types is successful
* @failcase			If target api i18n_uchar_enum_char_types fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_enum_char_types_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;
	int nTimeoutId = 0;
	int nSampleCounter = 0;

	g_bCallbackHit = false;

	nRetVal = i18n_uchar_enum_char_types(CountTitlecaseLettersCB, (void *)&nSampleCounter);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_enum_char_types", BaseUtilsGetError(nRetVal));

	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] i18n_uchar_enum_char_types failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the combining class of the code point.
/**
* @testcase			ITc_i18n_uchar_get_combining_class_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the combining class of the code point.
* @apitarget			i18n_uchar_get_combining_class
* @apicovered			i18n_uchar_get_combining_class
* @passcase			When i18n_uchar_get_combining_class is successful
* @failcase			If target api i18n_uchar_get_combining_class fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_combining_class_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	uint8_t nCombiningClass = 1;

	nRetVal = i18n_uchar_get_combining_class(uChar32TextCode, &nCombiningClass);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_combining_class", BaseUtilsGetError(nRetVal));

	if(nCombiningClass != 0X0)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_combining_class returned different value of nCombiningClass \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the decimal digit value of a decimal digit character.
/**
* @testcase			ITc_i18n_uchar_char_digit_value_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the decimal digit value of a decimal digit character.
* @apitarget			i18n_uchar_char_digit_value
* @apicovered			i18n_uchar_char_digit_value
* @passcase			When i18n_uchar_char_digit_value is successful
* @failcase			If target api i18n_uchar_char_digit_value fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_digit_value_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x0663;
	uint32_t nCharDigitalValue = 0;

	nRetVal = i18n_uchar_char_digit_value(uChar32TextCode, &nCharDigitalValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_digit_value", BaseUtilsGetError(nRetVal));

	if(nCharDigitalValue != 3)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_char_digit_value returned different value of nCharDigitalValue \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Retrieves the name of a unicode character.
/**
* @testcase			ITc_i18n_uchar_char_name_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieves the name of a unicode character.
* @apitarget			i18n_uchar_char_name
* @apicovered			i18n_uchar_char_name
* @passcase			When i18n_uchar_char_name is successful
* @failcase			If target api i18n_uchar_char_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_name_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode[3] =
	{
		0x03B1,
		0x03B2,
		0x0E9D
	};

	const char sCharName[3][100] = {
		"GREEK SMALL LETTER ALPHA",
		"GREEK SMALL LETTER BETA",
		"LAO LETTER FO TAM"
	};

	i18n_uchar_u_char_name_choice_e eUCharNameChoice = I18N_UCHAR_U_UNICODE_CHAR_NAME;
	char sBuffer[gBufSize];
	int32_t *nNameLength;

	int nEnumSize = sizeof(uChar32TextCode) / sizeof(uChar32TextCode[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		nRetVal = i18n_uchar_char_name(uChar32TextCode[nEnumCounter], eUCharNameChoice, sBuffer, gBufSize, &nNameLength);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_name", BaseUtilsGetError(nRetVal));

		if(!strlen(sBuffer))
		{
			FPRINTF("[Line : %d][%s] Error there is no name, then the buffer will be set to the empty string \\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		if(!nNameLength)
		{
			FPRINTF("[Line : %d][%s] Error there is no name for this character \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		if(strcmp(sBuffer, sCharName[nEnumCounter]))
		{
			FPRINTF("[Line : %d][%s] Character name returned is [%s] \\n", __LINE__, API_NAMESPACE, sBuffer);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Finds a unicode character by its name and return its code point value.
/**
* @testcase			ITc_i18n_uchar_char_from_name_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Finds a unicode character by its name and return its code point value.
* @apitarget			i18n_uchar_char_from_name
* @apicovered			i18n_uchar_char_from_name
* @passcase			When i18n_uchar_char_from_name is successful
* @failcase			If target api i18n_uchar_char_from_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_from_name_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_u_char_name_choice_e eUCharNameChoice = I18N_UCHAR_U_UNICODE_CHAR_NAME;

	const char sCharName[3][100] = {
		"GREEK SMALL LETTER ALPHA",
		"GREEK SMALL LETTER BETA",
		"LAO LETTER FO TAM"
	};

	i18n_uchar32 nCharFromName[3] = {
		0x03B1,
		0x03B2,
		0x0E9D
	};

	i18n_uchar32 cCharFromName;
	int32_t *nNameLength;

	int nEnumSize = sizeof(sCharName) / sizeof(sCharName[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		nRetVal = i18n_uchar_char_from_name(eUCharNameChoice, sCharName[nEnumCounter], &cCharFromName);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_from_name", BaseUtilsGetError(nRetVal));

		if(cCharFromName != nCharFromName[nEnumCounter])
		{
			FPRINTF("[Line : %d][%s] Error Character name returned is [%x] \\n", __LINE__, API_NAMESPACE, cCharFromName );
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Enumerates all assigned unicode characters between the @a start and @a limit code points (@a start inclusive, @a limit exclusive) and call a function for each, passing the codepoint value and the character name.
/**
* @testcase			ITc_i18n_uchar_enum_char_names_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Enumerates all assigned unicode characters between the @a start and @a limit code points (@a start inclusive, @a limit exclusive) and
*				call a function for each, passing the codepoint value and the character name.
* @apitarget			i18n_uchar_enum_char_names
* @apicovered			i18n_uchar_enum_char_names
* @passcase			When i18n_uchar_enum_char_names is successful
* @failcase			If target api i18n_uchar_enum_char_names fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_enum_char_names_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_u_char_name_choice_e eUCharNameChoice = I18N_UCHAR_U_EXTENDED_CHAR_NAME;

	i18n_uchar32 cStart = 0x6A;
	i18n_uchar32 cLimit = 0x6F;
	int nSampleCounter = 2;

	g_bCallbackHit = false;

	nRetVal = i18n_uchar_enum_char_names(cStart, cLimit, DoSampleCB, (void *)&nSampleCounter, eUCharNameChoice);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_enum_char_names", BaseUtilsGetError(nRetVal));

	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] i18n_uchar_enum_char_names failed, error = callback not invoked\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the unicode name for a given property, as given in the unicode database file.
/**
* @testcase			ITc_i18n_uchar_get_property_name_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the unicode name for a given property, as given in the unicode database file.
* @apitarget			i18n_uchar_get_property_name
* @apicovered			i18n_uchar_get_property_name
* @passcase			When i18n_uchar_get_property_name is successful
* @failcase			If target api i18n_uchar_get_property_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_property_name_p(void)
{
	START_TEST;

	i18n_uchar_uproperty_e eUCharProperty[] = {
		I18N_UCHAR_ALPHABETIC,
		I18N_UCHAR_ASCII_HEX_DIGIT,
		I18N_UCHAR_BIDI_CONTROL,
		I18N_UCHAR_BIDI_MIRRORED,
		I18N_UCHAR_DASH,
		I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT,
		I18N_UCHAR_DEPRECATED,
		I18N_UCHAR_DIACRITIC,
		I18N_UCHAR_EXTENDER,
		I18N_UCHAR_FULL_COMPOSITION_EXCLUSION,
		I18N_UCHAR_GRAPHEME_BASE,
		I18N_UCHAR_GRAPHEME_EXTEND,
		I18N_UCHAR_GRAPHEME_LINK,
		I18N_UCHAR_HEX_DIGIT,
		I18N_UCHAR_HYPHEN,
		I18N_UCHAR_ID_CONTINUE,
		I18N_UCHAR_ID_START,
		I18N_UCHAR_IDEOGRAPHIC,
		I18N_UCHAR_IDS_BINARY_OPERATOR,
		I18N_UCHAR_IDS_TRINARY_OPERATOR,
		I18N_UCHAR_JOIN_CONTROL,
		I18N_UCHAR_LOGICAL_ORDER_EXCEPTION,
		I18N_UCHAR_LOWERCASE,
		I18N_UCHAR_MATH,
		I18N_UCHAR_NONCHARACTER_CODE_POINT,
		I18N_UCHAR_QUOTATION_MARK,
		I18N_UCHAR_RADICAL,
		I18N_UCHAR_SOFT_DOTTED,
		I18N_UCHAR_TERMINAL_PUNCTUATION,
		I18N_UCHAR_UNIFIED_IDEOGRAPH,
		I18N_UCHAR_UPPERCASE,
		I18N_UCHAR_WHITE_SPACE,
		I18N_UCHAR_XID_CONTINUE,
		I18N_UCHAR_XID_START,
		I18N_UCHAR_CASE_SENSITIVE,
		I18N_UCHAR_VARIATION_SELECTOR,
		I18N_UCHAR_NFD_INERT,
		I18N_UCHAR_NFKD_INERT,
		I18N_UCHAR_NFC_INERT,
		I18N_UCHAR_NFKC_INERT,
		I18N_UCHAR_SEGMENT_STARTER,
		I18N_UCHAR_PATTERN_SYNTAX,
		I18N_UCHAR_PATTERN_WHITE_SPACE,
		I18N_UCHAR_POSIX_ALNUM,
		I18N_UCHAR_POSIX_BLANK,
		I18N_UCHAR_POSIX_GRAPH,
		I18N_UCHAR_POSIX_PRINT,
		I18N_UCHAR_POSIX_XDIGIT,
		I18N_UCHAR_CASED,
		I18N_UCHAR_CASE_IGNORABLE,
		I18N_UCHAR_CHANGES_WHEN_LOWERCASED,
		I18N_UCHAR_CHANGES_WHEN_UPPERCASED,
		I18N_UCHAR_CHANGES_WHEN_TITLECASED,
		I18N_UCHAR_CHANGES_WHEN_CASEFOLDED,
		I18N_UCHAR_CHANGES_WHEN_CASEMAPPED,
		I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED,
		I18N_UCHAR_EMOJI,
		I18N_UCHAR_EMOJI_PRESENTATION,
		I18N_UCHAR_EMOJI_MODIFIER,
		I18N_UCHAR_EMOJI_MODIFIER_BASE,
		I18N_UCHAR_BIDI_CLASS,
		I18N_UCHAR_BLOCK,
		I18N_UCHAR_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_DECOMPOSITION_TYPE,
		I18N_UCHAR_EAST_ASIAN_WIDTH,
		I18N_UCHAR_GENERAL_CATEGORY,
		I18N_UCHAR_JOINING_GROUP,
		I18N_UCHAR_JOINING_TYPE,
		I18N_UCHAR_LINE_BREAK,
		I18N_UCHAR_NUMERIC_TYPE,
		I18N_UCHAR_SCRIPT,
		I18N_UCHAR_HANGUL_SYLLABLE_TYPE,
		I18N_UCHAR_NFD_QUICK_CHECK,
		I18N_UCHAR_NFKD_QUICK_CHECK,
		I18N_UCHAR_NFC_QUICK_CHECK,
		I18N_UCHAR_NFKC_QUICK_CHECK,
		I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_GRAPHEME_CLUSTER_BREAK,
		I18N_UCHAR_SENTENCE_BREAK,
		I18N_UCHAR_WORD_BREAK,
		I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE,
		I18N_UCHAR_GENERAL_CATEGORY_MASK,
		I18N_UCHAR_NUMERIC_VALUE,
		I18N_UCHAR_AGE,
		I18N_UCHAR_BIDI_MIRRORING_GLYPH,
		I18N_UCHAR_CASE_FOLDING,
		I18N_UCHAR_LOWERCASE_MAPPING,
		I18N_UCHAR_NAME,
		I18N_UCHAR_SIMPLE_CASE_FOLDING,
		I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING,
		I18N_UCHAR_SIMPLE_TITLECASE_MAPPING,
		I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING,
		I18N_UCHAR_TITLECASE_MAPPING,
		I18N_UCHAR_UPPERCASE_MAPPING,
		I18N_UCHAR_BIDI_PAIRED_BRACKET,
		I18N_UCHAR_SCRIPT_EXTENSIONS
	};

	const char sPropertyNameString[100][50] =
	{
		"Alphabetic",
		"ASCII_Hex_Digit",
		"Bidi_Control",
		"Bidi_Mirrored",
		"Dash",
		"Default_Ignorable_Code_Point",
		"Deprecated",
		"Diacritic",
		"Extender",
		"Full_Composition_Exclusion",
		"Grapheme_Base",
		"Grapheme_Extend",
		"Grapheme_Link",
		"Hex_Digit",
		"Hyphen",
		"ID_Continue",
		"ID_Start",
		"Ideographic",
		"IDS_Binary_Operator",
		"IDS_Trinary_Operator",
		"Join_Control",
		"Logical_Order_Exception",
		"Lowercase",
		"Math",
		"Noncharacter_Code_Point",
		"Quotation_Mark",
		"Radical",
		"Soft_Dotted",
		"Terminal_Punctuation",
		"Unified_Ideograph",
		"Uppercase",
		"White_Space",
		"XID_Continue",
		"XID_Start",
		"Case_Sensitive",
		"Variation_Selector",
		"NFD_Inert",
		"NFKD_Inert",
		"NFC_Inert",
		"NFKC_Inert",
		"Segment_Starter",
		"Pattern_Syntax",
		"Pattern_White_Space",
		"alnum",
		"blank",
		"graph",
		"print",
		"xdigit",
		"Cased",
		"Case_Ignorable",
		"Changes_When_Lowercased",
		"Changes_When_Uppercased",
		"Changes_When_Titlecased",
		"Changes_When_Casefolded",
		"Changes_When_Casemapped",
		"Changes_When_NFKC_Casefolded",
		"Emoji",
		"Emoji_Presentation",
		"Emoji_Modifier",
		"Emoji_Modifier_Base",
		"Bidi_Class",
		"Block",
		"Canonical_Combining_Class",
		"Decomposition_Type",
		"East_Asian_Width",
		"General_Category",
		"Joining_Group",
		"Joining_Type",
		"Line_Break",
		"Numeric_Type",
		"Script",
		"Hangul_Syllable_Type",
		"NFD_Quick_Check",
		"NFKD_Quick_Check",
		"NFC_Quick_Check",
		"NFKC_Quick_Check",
		"Lead_Canonical_Combining_Class",
		"Trail_Canonical_Combining_Class",
		"Grapheme_Cluster_Break",
		"Sentence_Break",
		"Word_Break",
		"Bidi_Paired_Bracket_Type",
		"General_Category_Mask",
		"Numeric_Value",
		"Age",
		"Bidi_Mirroring_Glyph",
		"Case_Folding",
		"Lowercase_Mapping",
		"Name",
		"Simple_Case_Folding",
		"Simple_Lowercase_Mapping",
		"Simple_Titlecase_Mapping",
		"Simple_Uppercase_Mapping",
		"Titlecase_Mapping",
		"Uppercase_Mapping",
		"Bidi_Paired_Bracket",
		"Script_Extensions"
	};

	i18n_uchar_u_property_name_choice_e eUcharPropertyNameChoice = I18N_UCHAR_U_LONG_PROPERTY_NAME;

	int nPropertyEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nPropertyEnumCounter = 0;

	char *sPropertyName;
	int nRetVal = I18N_ERROR_NONE;

	for ( nPropertyEnumCounter = 0; nPropertyEnumCounter < nPropertyEnumSize; nPropertyEnumCounter++ )
	{
		nRetVal = i18n_uchar_get_property_name(eUCharProperty[nPropertyEnumCounter], eUcharPropertyNameChoice, &sPropertyName);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_property_name", BaseUtilsGetError(nRetVal));

		if(!sPropertyName)
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_property_name returned NULL for the property name for enum counter[%d]\\n", __LINE__, API_NAMESPACE, nPropertyEnumCounter);
			return 1;
		}
		if(strcmp(sPropertyName, sPropertyNameString[nPropertyEnumCounter]))
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_property_name returned incorrect property name [%s] for enum counter[%d] and its property[%s]\\n", __LINE__, API_NAMESPACE, sPropertyName, nPropertyEnumCounter, sPropertyNameString[nPropertyEnumCounter]);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Returns the #i18n_uchar_uproperty_e enum for a given property name, as specified in the unicode database.
/**
* @testcase			ITc_i18n_uchar_get_property_enum
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the #i18n_uchar_uproperty_e enum for a given property name, as specified in the unicode database.
* @apitarget			i18n_uchar_get_property_enum
* @apicovered			i18n_uchar_get_property_enum
* @passcase			When i18n_uchar_get_property_enum is successful
* @failcase			If target api i18n_uchar_get_property_enum fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_property_enum_p(void)
{
	START_TEST;

	i18n_uchar_uproperty_e eUCharProperty[] = {
		I18N_UCHAR_ALPHABETIC,
		I18N_UCHAR_ASCII_HEX_DIGIT,
		I18N_UCHAR_BIDI_CONTROL,
		I18N_UCHAR_BIDI_MIRRORED,
		I18N_UCHAR_DASH,
		I18N_UCHAR_DEFAULT_IGNORABLE_CODE_POINT,
		I18N_UCHAR_DEPRECATED,
		I18N_UCHAR_DIACRITIC,
		I18N_UCHAR_EXTENDER,
		I18N_UCHAR_FULL_COMPOSITION_EXCLUSION,
		I18N_UCHAR_GRAPHEME_BASE,
		I18N_UCHAR_GRAPHEME_EXTEND,
		I18N_UCHAR_GRAPHEME_LINK,
		I18N_UCHAR_HEX_DIGIT,
		I18N_UCHAR_HYPHEN,
		I18N_UCHAR_ID_CONTINUE,
		I18N_UCHAR_ID_START,
		I18N_UCHAR_IDEOGRAPHIC,
		I18N_UCHAR_IDS_BINARY_OPERATOR,
		I18N_UCHAR_IDS_TRINARY_OPERATOR,
		I18N_UCHAR_JOIN_CONTROL,
		I18N_UCHAR_LOGICAL_ORDER_EXCEPTION,
		I18N_UCHAR_LOWERCASE,
		I18N_UCHAR_MATH,
		I18N_UCHAR_NONCHARACTER_CODE_POINT,
		I18N_UCHAR_QUOTATION_MARK,
		I18N_UCHAR_RADICAL,
		I18N_UCHAR_SOFT_DOTTED,
		I18N_UCHAR_TERMINAL_PUNCTUATION,
		I18N_UCHAR_UNIFIED_IDEOGRAPH,
		I18N_UCHAR_UPPERCASE,
		I18N_UCHAR_WHITE_SPACE,
		I18N_UCHAR_XID_CONTINUE,
		I18N_UCHAR_XID_START,
		I18N_UCHAR_CASE_SENSITIVE,
		I18N_UCHAR_S_TERM,
		I18N_UCHAR_VARIATION_SELECTOR,
		I18N_UCHAR_NFD_INERT,
		I18N_UCHAR_NFKD_INERT,
		I18N_UCHAR_NFC_INERT,
		I18N_UCHAR_NFKC_INERT,
		I18N_UCHAR_SEGMENT_STARTER,
		I18N_UCHAR_PATTERN_SYNTAX,
		I18N_UCHAR_PATTERN_WHITE_SPACE,
		I18N_UCHAR_POSIX_ALNUM,
		I18N_UCHAR_POSIX_BLANK,
		I18N_UCHAR_POSIX_GRAPH,
		I18N_UCHAR_POSIX_PRINT,
		I18N_UCHAR_POSIX_XDIGIT,
		I18N_UCHAR_CASED,
		I18N_UCHAR_CASE_IGNORABLE,
		I18N_UCHAR_CHANGES_WHEN_LOWERCASED,
		I18N_UCHAR_CHANGES_WHEN_UPPERCASED,
		I18N_UCHAR_CHANGES_WHEN_TITLECASED,
		I18N_UCHAR_CHANGES_WHEN_CASEFOLDED,
		I18N_UCHAR_CHANGES_WHEN_CASEMAPPED,
		I18N_UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED,
		I18N_UCHAR_EMOJI,
		I18N_UCHAR_EMOJI_PRESENTATION,
		I18N_UCHAR_EMOJI_MODIFIER,
		I18N_UCHAR_EMOJI_MODIFIER_BASE,
		I18N_UCHAR_BIDI_CLASS,
		I18N_UCHAR_BLOCK,
		I18N_UCHAR_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_DECOMPOSITION_TYPE,
		I18N_UCHAR_EAST_ASIAN_WIDTH,
		I18N_UCHAR_GENERAL_CATEGORY,
		I18N_UCHAR_JOINING_GROUP,
		I18N_UCHAR_JOINING_TYPE,
		I18N_UCHAR_LINE_BREAK,
		I18N_UCHAR_NUMERIC_TYPE,
		I18N_UCHAR_SCRIPT,
		I18N_UCHAR_HANGUL_SYLLABLE_TYPE,
		I18N_UCHAR_NFD_QUICK_CHECK,
		I18N_UCHAR_NFKD_QUICK_CHECK,
		I18N_UCHAR_NFC_QUICK_CHECK,
		I18N_UCHAR_NFKC_QUICK_CHECK,
		I18N_UCHAR_LEAD_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_TRAIL_CANONICAL_COMBINING_CLASS,
		I18N_UCHAR_GRAPHEME_CLUSTER_BREAK,
		I18N_UCHAR_SENTENCE_BREAK,
		I18N_UCHAR_WORD_BREAK,
		I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE,
		I18N_UCHAR_GENERAL_CATEGORY_MASK,
		I18N_UCHAR_NUMERIC_VALUE,
		I18N_UCHAR_AGE,
		I18N_UCHAR_BIDI_MIRRORING_GLYPH,
		I18N_UCHAR_CASE_FOLDING,
		I18N_UCHAR_LOWERCASE_MAPPING,
		I18N_UCHAR_NAME,
		I18N_UCHAR_SIMPLE_CASE_FOLDING,
		I18N_UCHAR_SIMPLE_LOWERCASE_MAPPING,
		I18N_UCHAR_SIMPLE_TITLECASE_MAPPING,
		I18N_UCHAR_SIMPLE_UPPERCASE_MAPPING,
		I18N_UCHAR_TITLECASE_MAPPING,
		I18N_UCHAR_UPPERCASE_MAPPING,
		I18N_UCHAR_BIDI_PAIRED_BRACKET,
		I18N_UCHAR_SCRIPT_EXTENSIONS
	};

	const char sPropertyNameString[100][50] =
	{
		"Alphabetic",
		"ASCII_Hex_Digit",
		"Bidi_Control",
		"Bidi_Mirrored",
		"Dash",
		"Default_Ignorable_Code_Point",
		"Deprecated",
		"Diacritic",
		"Extender",
		"Full_Composition_Exclusion",
		"Grapheme_Base",
		"Grapheme_Extend",
		"Grapheme_Link",
		"Hex_Digit",
		"Hyphen",
		"ID_Continue",
		"ID_Start",
		"Ideographic",
		"IDS_Binary_Operator",
		"IDS_Trinary_Operator",
		"Join_Control",
		"Logical_Order_Exception",
		"Lowercase",
		"Math",
		"Noncharacter_Code_Point",
		"Quotation_Mark",
		"Radical",
		"Soft_Dotted",
		"Terminal_Punctuation",
		"Unified_Ideograph",
		"Uppercase",
		"White_Space",
		"XID_Continue",
		"XID_Start",
		"Case_Sensitive",
		"STerm",
		"Variation_Selector",
		"NFD_Inert",
		"NFKD_Inert",
		"NFC_Inert",
		"NFKC_Inert",
		"Segment_Starter",
		"Pattern_Syntax",
		"Pattern_White_Space",
		"alnum",
		"blank",
		"graph",
		"print",
		"xdigit",
		"Cased",
		"Case_Ignorable",
		"Changes_When_Lowercased",
		"Changes_When_Uppercased",
		"Changes_When_Titlecased",
		"Changes_When_Casefolded",
		"Changes_When_Casemapped",
		"Changes_When_NFKC_Casefolded",
		"Emoji",
		"Emoji_Presentation",
		"Emoji_Modifier",
		"Emoji_Modifier_Base",
		"Bidi_Class",
		"Block",
		"Canonical_Combining_Class",
		"Decomposition_Type",
		"East_Asian_Width",
		"General_Category",
		"Joining_Group",
		"Joining_Type",
		"Line_Break",
		"Numeric_Type",
		"Script",
		"Hangul_Syllable_Type",
		"NFD_Quick_Check",
		"NFKD_Quick_Check",
		"NFC_Quick_Check",
		"NFKC_Quick_Check",
		"Lead_Canonical_Combining_Class",
		"Trail_Canonical_Combining_Class",
		"Grapheme_Cluster_Break",
		"Sentence_Break",
		"Word_Break",
		"Bidi_Paired_Bracket_Type",
		"General_Category_Mask",
		"Numeric_Value",
		"Age",
		"Bidi_Mirroring_Glyph",
		"Case_Folding",
		"Lowercase_Mapping",
		"Name",
		"Simple_Case_Folding",
		"Simple_Lowercase_Mapping",
		"Simple_Titlecase_Mapping",
		"Simple_Uppercase_Mapping",
		"Titlecase_Mapping",
		"Uppercase_Mapping",
		"Bidi_Paired_Bracket",
		"Script_Extensions"
	};

	int nPropertyEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nPropertyEnumCounter = 0;

	i18n_uchar_uproperty_e ePropertyEnum = I18N_UCHAR_ALPHABETIC;
	int nRetVal = I18N_ERROR_NONE;

	for ( nPropertyEnumCounter = 0; nPropertyEnumCounter < nPropertyEnumSize; nPropertyEnumCounter++ )
	{
		nRetVal = i18n_uchar_get_property_enum(sPropertyNameString[nPropertyEnumCounter], &ePropertyEnum);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_property_enum", BaseUtilsGetError(nRetVal));

		if(ePropertyEnum != eUCharProperty[nPropertyEnumCounter])
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_property_enum returned NULL for the property [%s]\\n", __LINE__, API_NAMESPACE, uCharPropertyName(eUCharProperty[nPropertyEnumCounter]));
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Returns the unicode name for a given property value.
/**
* @testcase			ITc_i18n_uchar_get_property_value_name_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the unicode name for a given property value.
* @apitarget			i18n_uchar_get_property_value_name
* @apicovered			i18n_uchar_get_property_value_name
* @passcase			When i18n_uchar_get_property_value_name is successful
* @failcase			If target api i18n_uchar_get_property_value_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_property_value_name_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_u_word_break_values_e eUCharUWordBreakValue[] =
	{
		I18N_UCHAR_U_WB_OTHER,
		I18N_UCHAR_U_WB_ALETTER,
		I18N_UCHAR_U_WB_FORMAT,
		I18N_UCHAR_U_WB_KATAKANA,
		I18N_UCHAR_U_WB_MIDLETTER,
		I18N_UCHAR_U_WB_MIDNUM,
		I18N_UCHAR_U_WB_NUMERIC,
		I18N_UCHAR_U_WB_EXTENDNUMLET,
		I18N_UCHAR_U_WB_CR,
		I18N_UCHAR_U_WB_EXTEND,
		I18N_UCHAR_U_WB_LF,
		I18N_UCHAR_U_WB_MIDNUMLET,
		I18N_UCHAR_U_WB_NEWLINE,
		I18N_UCHAR_U_WB_REGIONAL_INDICATOR,
		I18N_UCHAR_U_WB_HEBREW_LETTER,
		I18N_UCHAR_U_WB_SINGLE_QUOTE,
		I18N_UCHAR_U_WB_DOUBLE_QUOTE
	};

	const char* sUCharUWordBreakValueName[17] =
	{
		"Other",
		"ALetter",
		"Format",
		"Katakana",
		"MidLetter",
		"MidNum",
		"Numeric",
		"ExtendNumLet",
		"CR",
		"Extend",
		"LF",
		"MidNumLet",
		"Newline",
		"Regional_Indicator",
		"Hebrew_Letter",
		"Single_Quote",
		"Double_Quote"
	};

	int nSizeStringWordBreakValueName = sizeof(sUCharUWordBreakValueName) / sizeof(sUCharUWordBreakValueName[0]);
	int nLoopCount;

	char* sPropertyValueName;
	i18n_uchar_u_property_name_choice_e eUcharPropertyNameChoice = I18N_UCHAR_U_LONG_PROPERTY_NAME;
	i18n_uchar_uproperty_e eUCharPropertyWithValueName = I18N_UCHAR_WORD_BREAK;

	for ( nLoopCount = 0; nLoopCount < nSizeStringWordBreakValueName; nLoopCount++ )
	{
		nRetVal = i18n_uchar_get_property_value_name(eUCharPropertyWithValueName, eUCharUWordBreakValue[nLoopCount], eUcharPropertyNameChoice, &sPropertyValueName);

		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_property_value_name", BaseUtilsGetError(nRetVal));

		if(sPropertyValueName == NULL)
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_property_value_name returned NULL \\n", __LINE__, API_NAMESPACE);
			return 1;
		}

		if(strcmp(sPropertyValueName, sUCharUWordBreakValueName[nLoopCount]))
		{
			FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_property_value_name returned [%s] incorrect property value name for proprty name [%s]\\n", __LINE__, API_NAMESPACE, sPropertyValueName, sUCharUWordBreakValueName[nLoopCount]);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Returns the property value integer for a given value name, as specified in the unicode database.
/**
* @testcase			ITc_i18n_uchar_get_property_value_enum_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the property value integer for a given value name, as specified in the unicode database.
* @apitarget			i18n_uchar_get_property_value_enum
* @apicovered			i18n_uchar_get_property_value_enum
* @passcase			When i18n_uchar_get_property_value_enum is successful
* @failcase			If target api i18n_uchar_get_property_value_enum fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_property_value_enum_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar_category_e eUCharCatagoryValue[] = {
		I18N_UCHAR_U_GENERAL_OTHER_TYPES,
		I18N_UCHAR_U_UPPERCASE_LETTER,
		I18N_UCHAR_U_LOWERCASE_LETTER,
		I18N_UCHAR_U_TITLECASE_LETTER,
		I18N_UCHAR_U_MODIFIER_LETTER,
		I18N_UCHAR_U_OTHER_LETTER,
		I18N_UCHAR_U_NON_SPACING_MARK,
		I18N_UCHAR_U_ENCLOSING_MARK,
		I18N_UCHAR_U_COMBINING_SPACING_MARK,
		I18N_UCHAR_U_DECIMAL_DIGIT_NUMBER,
		I18N_UCHAR_U_LETTER_NUMBER,
		I18N_UCHAR_U_OTHER_NUMBER,
		I18N_UCHAR_U_SPACE_SEPARATOR,
		I18N_UCHAR_U_LINE_SEPARATOR,
		I18N_UCHAR_U_PARAGRAPH_SEPARATOR,
		I18N_UCHAR_U_CONTROL_CHAR,
		I18N_UCHAR_U_FORMAT_CHAR,
		I18N_UCHAR_U_PRIVATE_USE_CHAR,
		I18N_UCHAR_U_SURROGATE,
		I18N_UCHAR_U_DASH_PUNCTUATION,
		I18N_UCHAR_U_START_PUNCTUATION,
		I18N_UCHAR_U_END_PUNCTUATION,
		I18N_UCHAR_U_CONNECTOR_PUNCTUATION,
		I18N_UCHAR_U_OTHER_PUNCTUATION,
		I18N_UCHAR_U_MATH_SYMBOL,
		I18N_UCHAR_U_CURRENCY_SYMBOL,
		I18N_UCHAR_U_MODIFIER_SYMBOL,
		I18N_UCHAR_U_OTHER_SYMBOL,
		I18N_UCHAR_U_INITIAL_PUNCTUATION,
		I18N_UCHAR_U_FINAL_PUNCTUATION
	};

	const char* sUCharUPropertyAlias[30] = {
		"Cn",
		"Lu",
		"Ll",
		"Lt",
		"Lm",
		"Lo",
		"Mn",
		"Me",
		"Mc",
		"Nd",
		"Nl",
		"No",
		"Zs",
		"Zl",
		"Zp",
		"Cc",
		"Cf",
		"Co",
		"Cs",
		"Pd",
		"Ps",
		"Pe",
		"Pc",
		"Po",
		"Sm",
		"Sc",
		"Sk",
		"So",
		"Pi",
		"Pf"
	};

	int neUCharCatagoryValueEnumSize = sizeof(eUCharCatagoryValue) / sizeof(eUCharCatagoryValue[0]);
	int nLoopCount = 0;

	i18n_uchar_uproperty_e eUCharProperty = I18N_UCHAR_GENERAL_CATEGORY;
	int32_t nValueEnum = 0;

	for(nLoopCount = 0; nLoopCount < neUCharCatagoryValueEnumSize; nLoopCount++)
	{
		nRetVal = i18n_uchar_get_property_value_enum(eUCharProperty, sUCharUPropertyAlias[nLoopCount], &nValueEnum);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_property_value_enum", BaseUtilsGetError(nRetVal));

		if(nValueEnum == I18N_UCHAR_INVALID_CODE)
		{
			FPRINTF("[Line : %d][%s] Error - i18n_uchar_get_property_value_enum: The property and Alias [%s] is invalid \\n", __LINE__, API_NAMESPACE, sUCharUPropertyAlias[nLoopCount]);
			return 1;
		}

		if(nValueEnum != eUCharCatagoryValue[nLoopCount])
		{
			FPRINTF("[Line : %d][%s] Error - i18n_uchar_get_property_value_enum: the given Alias name [%s] does not match with corresponding Enum value [%d] of the given property \\n", __LINE__, API_NAMESPACE, sUCharUPropertyAlias[nLoopCount], eUCharCatagoryValue[nLoopCount]);
			return 1;
		}
	}
	return 0;
}

//& type: auto
//& purpose: Determines if the specified character is permissible as the first character in an identifier according to unicode (the unicode standard, version 3.0, chapter 5.16 identifiers).
/**
* @testcase			ITc_i18n_uchar_is_id_start_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character is permissible as the first character in an identifier according to unicode (the unicode standard, * 				version 3.0, chapter 5.16 identifiers).
* @apitarget			i18n_uchar_is_id_start
* @apicovered			i18n_uchar_is_id_start
* @passcase			When i18n_uchar_is_id_start is successful
* @failcase			If target api i18n_uchar_is_id_start fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_id_start_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsIdStart = false;

	nRetVal = i18n_uchar_is_id_start(uChar32TextCode, &bIsIdStart);

	if(!bIsIdStart)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_id_start returned FALSE for bIsIdStart \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_id_start", BaseUtilsGetError(nRetVal));
	return 0;
}

//& type: auto
//& purpose: Determines if the specified character is permissible in an identifier according to Java.
/**
* @testcase			ITc_i18n_uchar_is_id_part_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character is permissible in an identifier according to Java.
* @apitarget			i18n_uchar_is_id_part
* @apicovered			i18n_uchar_is_id_part
* @passcase			When i18n_uchar_is_id_part is successful
* @failcase			If target api i18n_uchar_is_id_part fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_id_part_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsIdPart = false;

	nRetVal = i18n_uchar_is_id_part(uChar32TextCode, &bIsIdPart);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_id_part", BaseUtilsGetError(nRetVal));

	if(!bIsIdPart)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_id_part returned FALSE for bIsIdStart \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines if the specified character should be regarded as an ignorable character in an identifier, according to java.
/**
* @testcase			ITc_i18n_uchar_is_id_ignorable_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character should be regarded as an ignorable character in an identifier, according to java.
* @apitarget			i18n_uchar_is_id_ignorable
* @apicovered			i18n_uchar_is_id_ignorable
* @passcase			When i18n_uchar_is_id_ignorable is successful
* @failcase			If target api i18n_uchar_is_id_ignorable fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_id_ignorable_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x07;
	i18n_ubool bIsIdIgnorable = false;

	nRetVal = i18n_uchar_is_id_ignorable(uChar32TextCode, &bIsIdIgnorable);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_id_ignorable", BaseUtilsGetError(nRetVal));

	if(!bIsIdIgnorable)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_id_ignorable returned FALSE for bIsIdIgnorable \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines if the specified character is permissible as the first character in a java identifier.
/**
* @testcase			ITc_i18n_uchar_is_java_id_start_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character is permissible as the first character in a java identifier.
* @apitarget			i18n_uchar_is_java_id_start
* @apicovered			i18n_uchar_is_java_id_start
* @passcase			When i18n_uchar_is_java_id_start is successful
* @failcase			If target api i18n_uchar_is_java_id_start fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_java_id_start_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsJavaIdStart = false;

	nRetVal = i18n_uchar_is_java_id_start(uChar32TextCode, &bIsJavaIdStart);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_java_id_start", BaseUtilsGetError(nRetVal));

	if(!bIsJavaIdStart)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_java_id_start returned FALSE for bIsJavaIdStart \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines if the specified character is permissible in a java identifier.
/**
* @testcase			ITc_i18n_uchar_is_java_id_part_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines if the specified character is permissible in a java identifier.
* @apitarget			i18n_uchar_is_java_id_part
* @apicovered			i18n_uchar_is_java_id_part
* @passcase			When i18n_uchar_is_java_id_part is successful
* @failcase			If target api i18n_uchar_is_java_id_part fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_is_java_id_part_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_ubool bIsJavaIdPart = false;

	nRetVal = i18n_uchar_is_java_id_part(uChar32TextCode, &bIsJavaIdPart);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_is_java_id_part", BaseUtilsGetError(nRetVal));

	if(!bIsJavaIdPart)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_is_java_id_part returned FALSE for bIsJavaIdPart \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the given character to its lowercase equivalent.
/**
* @testcase			ITc_i18n_uchar_to_lower_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the given character to its lowercase equivalent.
* @apitarget			i18n_uchar_to_lower
* @apicovered			i18n_uchar_to_lower
* @passcase			When i18n_uchar_to_lower is successful
* @failcase			If target api i18n_uchar_to_lower fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_to_lower_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	i18n_uchar32 cToLower;

	nRetVal = i18n_uchar_to_lower(uChar32TextCode, &cToLower);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_to_lower", BaseUtilsGetError(nRetVal));

	if(cToLower != uChar32TextCode)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_to_lower returned wrong value of cToLower \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the given character to its uppercase equivalent.
/**
* @testcase			ITc_i18n_uchar_to_upper_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the given character to its uppercase equivalent.
* @apitarget			i18n_uchar_to_upper
* @apicovered			i18n_uchar_to_upper
* @passcase			When i18n_uchar_to_upper is successful
* @failcase			If target api i18n_uchar_to_upper fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_to_upper_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x4D;
	i18n_uchar32 cToUpper;

	nRetVal = i18n_uchar_to_upper(uChar32TextCode, &cToUpper);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_to_upper", BaseUtilsGetError(nRetVal));

	if(cToUpper != uChar32TextCode)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_to_upper returned wrong value of cToUpper \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the given character to its titlecase equivalent.
/**
* @testcase			ITc_i18n_uchar_to_title_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the given character to its titlecase equivalent.
* @apitarget			i18n_uchar_to_title
* @apicovered			i18n_uchar_to_title
* @passcase			When i18n_uchar_to_title is successful
* @failcase			If target api i18n_uchar_to_title fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_to_title_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x2B;
	i18n_uchar32 cToTitle;

	nRetVal = i18n_uchar_to_title(uChar32TextCode, &cToTitle);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_to_title", BaseUtilsGetError(nRetVal));

	if(cToTitle != uChar32TextCode)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_to_title returned wrong value of cToTitle \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Maps the given character to its case folding equivalent.
/**
* @testcase			ITc_i18n_uchar_fold_case_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Maps the given character to its case folding equivalent.
* @apitarget			i18n_uchar_fold_case
* @apicovered			i18n_uchar_fold_case
* @passcase			When i18n_uchar_fold_case is successful
* @failcase			If target api i18n_uchar_fold_case fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_fold_case_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x6D;
	uint32_t nFoldCaseOptions = I18N_U_FOLD_CASE_DEFAULT;
	i18n_uchar32 nCodePoint = 0;

	nRetVal = i18n_uchar_fold_case(uChar32TextCode, nFoldCaseOptions, &nCodePoint);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_fold_case", BaseUtilsGetError(nRetVal));

	if(nCodePoint != uChar32TextCode)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_fold_case returned wrong value of cToTitle \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: Returns the decimal digit value of the code point in the specified radix.
/**
* @testcase			ITc_i18n_uchar_digit_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Returns the decimal digit value of the code point in the specified radix.
* @apitarget			i18n_uchar_digit
* @apicovered			i18n_uchar_digit
* @passcase			When i18n_uchar_digit is successful
* @failcase			If target api i18n_uchar_digit fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_digit_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x36;
	int8_t nRadix = 10;
	int32_t nNumericalValue = 0;

	nRetVal = i18n_uchar_digit(uChar32TextCode, nRadix, &nNumericalValue);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_digit", BaseUtilsGetError(nRetVal));

	if(0x6 != nNumericalValue)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_digit returned wrong value of nNumericalValue \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Determines the character representation for a specific digit in the specified radix.
/**
* @testcase			ITc_i18n_uchar_for_digit_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Determines the character representation for a specific digit in the specified radix.
* @apitarget			i18n_uchar_for_digit
* @apicovered			i18n_uchar_for_digit
* @passcase			When i18n_uchar_for_digit is successful
* @failcase			If target api i18n_uchar_for_digit fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_for_digit_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	int32_t nDigit = 7;
	int8_t nRadix = 10;
	i18n_uchar32 uChar32Representation = 0;

	nRetVal = i18n_uchar_for_digit(nDigit, nRadix, &uChar32Representation);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_for_digit", BaseUtilsGetError(nRetVal));

	if(0x37 != uChar32Representation)
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_for_digit returned wrong value of uChar32Representation \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Gets the "age" of the code point.
/**
* @testcase			ITc_i18n_uchar_char_age_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the "age" of the code point.
* @apitarget			i18n_uchar_char_age
* @apicovered			i18n_uchar_char_age
* @passcase			When i18n_uchar_char_age is successful
* @failcase			If target api i18n_uchar_char_age fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_char_age_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32UVersionInfo = 0x1207;
	i18n_uversion_info uVesrionInfoCharAge;
	i18n_uversion_info pszUVersionInfo = {4, 1, 0};

	nRetVal = i18n_uchar_char_age(uChar32UVersionInfo, &uVesrionInfoCharAge);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_char_age", BaseUtilsGetError(nRetVal));

	if(memcmp(uVesrionInfoCharAge, pszUVersionInfo, 3))
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_char_age returned wrong value of pszUVersionInfo \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Gets the unicode version information.
/**
* @testcase			ITc_i18n_uchar_get_unicode_version_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the unicode version information.
* @apitarget			i18n_uchar_get_unicode_version
* @apicovered			i18n_uchar_get_unicode_version
* @passcase			When i18n_uchar_get_unicode_version is successful
* @failcase			If target api i18n_uchar_get_unicode_version fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_unicode_version_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uversion_info pszUVersionInfoArray;

	nRetVal = i18n_uchar_get_unicode_version(pszUVersionInfoArray);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_unicode_version", BaseUtilsGetError(nRetVal));

	return 0;
}

//& type: auto
//& purpose: Gets the FC_NFKC_Closure property string for a character.
/**
* @testcase			ITc_i18n_uchar_get_fc_nfkc_closure_p
* @since_tizen 			4.0
* @author            		SRID(j.abhishek)
* @reviewer         		SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the FC_NFKC_Closure property string for a character.
* @apitarget			i18n_uchar_get_fc_nfkc_closure
* @apicovered			i18n_uchar_get_fc_nfkc_closure
* @passcase			When i18n_uchar_get_fc_nfkc_closure is successful
* @failcase			If target api i18n_uchar_get_fc_nfkc_closure fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_uchar_get_fc_nfkc_closure_p(void)
{
	START_TEST;
	int nRetVal = I18N_ERROR_NONE;

	i18n_uchar32 uChar32TextCode = 0x2121;
	i18n_uchar pszDestinationBuf[gBufSize];

	i18n_uchar pszResultBuf[gBufSize];
	int32_t nLength;

	i18n_ustring_copy_ua(pszResultBuf, "tel");

	nRetVal = i18n_uchar_get_fc_nfkc_closure(uChar32TextCode, pszDestinationBuf, gBufSize, &nLength);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uchar_get_fc_nfkc_closure", BaseUtilsGetError(nRetVal));

	if(memcmp(pszDestinationBuf, pszResultBuf, 4))
	{
		FPRINTF("[Line : %d][%s] Error in i18n_uchar_get_fc_nfkc_closure returned pszDestinationBuf and pszResultBuf values does not match \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
