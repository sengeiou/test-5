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

static i18n_uset_h uset = NULL;
static i18n_uchar32 start = 0x41;
static i18n_uchar32 end = 0x50;

//& set: BaseUtils
void ITs_base_utils_uset_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}	
	
	int nRetVal = i18n_uset_create(start, end, &uset);
	if( nRetVal == I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = true;
	}
	return;
}

void ITs_base_utils_uset_cleanup(void)
{
	int nRetVal = i18n_uset_destroy(uset);
	if( nRetVal == I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
	}
	return;
}

//& purpose: Creates an empty #i18n_uset_h object.
/**
 * @testcase 				ITc_i18n_uset_create_empty_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates an empty #i18n_uset_h object.
 * @scenario				Creates an empty #i18n_uset_h object.\n
 *                          Disposes an empty #i18n_uset_h object.
 * @api-covered				ITc_i18n_uset_create_empty_p, i18n_uset_destroy
 * @pass-case				When ITc_i18n_uset_create_empty_p is successful.
 * @fail-case				If target ITc_i18n_uset_create_empty_p fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_create_empty_p(void)
{	
	START_TEST;
	i18n_uset_h uset = NULL;
	
	//Target Api
	int nRetVal = i18n_uset_create_empty(&uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create_empty", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_uset_destroy(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: Creates and destroys an #i18n_uset_h object that contains the range of characters
/**
 * @testcase 				ITc_i18n_uset_create_destroy_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates and destroys an #i18n_uset_h object that contains the range of characters
 * @scenario				Creates an #i18n_uset_h object that contains the range of characters\n
 *							Disposes an #i18n_uset_h object that contains the range of characters						
 * @api-covered				i18n_uset_create, i18n_uset_destroy
 * @pass-case				When i18n_uset_create & i18n_uset_destroy is successful.
 * @fail-case				If target i18n_uset_create & i18n_uset_destroy fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_create_destroy_p(void)
{	
	START_TEST;
	i18n_uset_h uset = NULL;
	
	//Target Api
	int nRetVal = i18n_uset_create(start, end, &uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_uset_destroy(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: Creates a set based on a given pattern.
/**
 * @testcase 				ITc_i18n_uset_create_pattern_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates a set based on a given pattern.
 * @scenario				Creates a set based on a given pattern.\n
 *							Disposes a set based on a given pattern. 
 * @api-covered				i18n_uset_create_pattern
 * @pass-case				When i18n_uset_create_pattern is successful.
 * @fail-case				If target i18n_uset_create_pattern fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_create_pattern_p(void)
{	
	START_TEST;
	i18n_uset_h uset = NULL;
	char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
	
    _pattern = (i18n_uchar*) calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_uchar *pRet = i18n_ustring_copy_ua(_pattern, pattern);
	int32_t nSourceLength = i18n_ustring_get_length(_pattern);
	if(pRet == NULL || nSourceLength <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY1(_pattern);
		return 1;
	}
	
	//Target Api	
	int nRetVal = i18n_uset_create_pattern(_pattern, nSourceLength, &uset);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_uset_create_pattern", BaseUtilsGetError(nRetVal),FREE_MEMORY1(_pattern));
	
	nRetVal = i18n_uset_destroy(uset);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_destroy", BaseUtilsGetError(nRetVal), FREE_MEMORY1(_pattern));
	
	FREE_MEMORY1(_pattern);

	return 0;
}
	
//& purpose: Creates a set based on a given pattern.
/**
 * @testcase 				ITc_i18n_uset_create_pattern_options_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Creates a set based on a given pattern.
 * @scenario				Creates a set based on a given pattern.\n
 *							Disposes a set based on a given pattern.
 * @api-covered				i18n_uset_create_pattern_options
 * @pass-case				When i18n_uset_create_pattern_options is successful.
 * @fail-case				If target i18n_uset_create_pattern_options fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_create_pattern_options_p(void)
{	
	START_TEST;
	i18n_uset_h uset = NULL;
	char *pattern = "[:Hyphen:]";
    i18n_uchar *_pattern = NULL;
	int nRetVal = -1;
	
    _pattern = (i18n_uchar*) calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_uchar *pRet = i18n_ustring_copy_ua(_pattern, pattern);
	int32_t nSourceLength = i18n_ustring_get_length(_pattern);
	if(pRet == NULL || nSourceLength <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY1(_pattern);
		return 1;
	}
	
	uint32_t BitmaskType[] = { I18N_USET_IGNORE_SPACE, I18N_USET_CASE_INSENSITIVE};
	int nEnumSize = sizeof(BitmaskType) / sizeof(BitmaskType[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		//Target Api
		nRetVal = i18n_uset_create_pattern_options(_pattern, nSourceLength, BitmaskType[nEnumCounter], &uset);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_create_pattern_options", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset);FREE_MEMORY1(_pattern));
		nRetVal = i18n_uset_destroy(uset);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_destroy", BaseUtilsGetError(nRetVal), FREE_MEMORY1(_pattern));
	}
	FREE_MEMORY1(_pattern);
	return 0;
}

//& purpose: Returns a copy of this object.
/**
 * @testcase 				ITc_i18n_uset_clone_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns a copy of this object.
 * @scenario				Returns a copy of this object.\n
 *							Disposes the copied object. 
 * @api-covered				i18n_uset_clone, i18n_uset_destroy
 * @pass-case				When i18n_uset_clone is successful.
 * @fail-case				If target i18n_uset_clone fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_clone_p(void)
{		
	START_TEST;
    i18n_uset_h uset_c = NULL;

	//Target Api
	int nRetVal = i18n_uset_clone (uset, &uset_c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_clone", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_uset_destroy(uset_c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose: Freezes the set (make it immutable).
/**
 * @testcase 				ITc_i18n_uset_freeze_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Freezes the set (make it immutable).
 * @scenario				Freezes the set.					
 * @api-covered				i18n_uset_freeze
 * @pass-case				When i18n_uset_freeze is successful.
 * @fail-case				If target i18n_uset_freeze fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_freeze_p(void)
{		
	START_TEST;
	
	//Target Api
	int nRetVal = i18n_uset_freeze(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_freeze", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose:Determines whether the set has been frozen (made immutable) or not.
/**
 * @testcase 				ITc_i18n_uset_is_frozen_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Determines whether the set has been frozen (made immutable) or not.
 * @scenario				Freezes the set.\n
 *							Determines whether the set has been frozen or not. 
 * @api-covered				i18n_uset_is_frozen, i18n_uset_freeze
 * @pass-case				When i18n_uset_is_frozen is successful.
 * @fail-case				If target i18n_uset_is_frozen fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_is_frozen_p(void)
{		
	START_TEST;

	int nRetVal = i18n_uset_freeze(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_freeze", BaseUtilsGetError(nRetVal));
	
	//Target Api
	i18n_ubool ubool = i18n_uset_is_frozen (uset);
	CHECK_VALUE_INT(ubool, "i18n_uset_is_frozen");
	
	nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_is_frozen", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose: Clones the set and make the clone mutable.
/**
 * @testcase 				ITc_i18n_uset_clone_as_thawed_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Clones the set and make the clone mutable.
 * @scenario				Freezes the set.\n
 *							Clones the set and make the clone mutable.\n
 *							Disposes the cloned set. 
 * @api-covered				i18n_ustring_to_title, i18n_uset_freeze, i18n_uset_destroy
 * @pass-case				When i18n_uset_clone_as_thawed is successful.
 * @fail-case				If target i18n_uset_clone_as_thawed fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_clone_as_thawed_p(void)
{		
	START_TEST;
	i18n_uset_h uset_c = NULL;

	int nRetVal = i18n_uset_freeze(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_freeze", BaseUtilsGetError(nRetVal));
	
	//Target Api
	nRetVal = i18n_uset_clone_as_thawed(uset, &uset_c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_clone_as_thawed", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_uset_destroy(uset_c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Causes the #i18n_uset_h object to represent the range <code>start - end</code>.
/**
 * @testcase 				ITc_i18n_uset_set_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Causes the #i18n_uset_h object to represent the range <code>start - end</code>.
 * @scenario				Creates the empty set.\n
 *							Set the empty set to represent the range <code>start - end</code>.\n
 *							Disposes the set.						
 * @api-covered				i18n_uset_set, i18n_uset_create_empty, i18n_uset_destroy
 * @pass-case				When i18n_uset_set is successful.
 * @fail-case				If target i18n_uset_set fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_set_p(void)
{		
	START_TEST;
	i18n_uset_h uset1 = NULL;
	
	int nRetVal = i18n_uset_create_empty(&uset1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create_empty", BaseUtilsGetError(nRetVal));

	//Target Api
	nRetVal = i18n_uset_set(uset1, start, end);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_set", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset));
	
	nRetVal = i18n_uset_destroy(uset1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& type: auto
//& purpose: Modifies the set to represent the set specified by the given
/**
 * @testcase 				ITc_i18n_uset_apply_pattern_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Modifies the set to represent the set specified by the given.
 * @scenario				Modifies the set to represent the set specified by the given						
 * @api-covered				i18n_uset_set, i18n_uset_create_empty, i18n_uset_destroy
 * @pass-case				When i18n_uset_set is successful.
 * @fail-case				If target i18n_uset_set fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_apply_pattern_p(void)
{		
	START_TEST;
	const char *pattern = "[:Hyphen:]";
    i18n_uchar *upattern = NULL;

    upattern = (i18n_uchar*) calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_uchar *pRet = i18n_ustring_copy_ua(upattern, pattern);
	int32_t upattern_length = i18n_ustring_get_length(upattern);
	if(pRet == NULL || upattern_length <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY1(upattern);
		return 1;
	}
	
	uint32_t BitmaskType[] = { I18N_USET_IGNORE_SPACE, I18N_USET_CASE_INSENSITIVE};
	int nEnumSize = sizeof(BitmaskType) / sizeof(BitmaskType[0]);
	int nEnumCounter = 0;
	int32_t nIndex = -1;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		nIndex = i18n_uset_apply_pattern(uset, upattern, upattern_length, BitmaskType[nEnumCounter]);
		CHECK_RETURN_VAL_CLEANUP(nIndex, "i18n_uset_is_frozen",FREE_MEMORY1(upattern));
		
		int nRetVal = get_last_result();
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_apply_pattern", BaseUtilsGetError(nRetVal), FREE_MEMORY1(upattern));
	}
	
   FREE_MEMORY1(upattern);
   
   return 0;
}

	
//& purpose: Modifies the set to contain those code points which have the given value
/**
 * @testcase 				ITc_i18n_uset_apply_int_property_value_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Modifies the set to contain those code points which have the given value.
 * @scenario				Modifies the set to contain those code points which have the given value.						
 * @api-covered				i18n_uset_apply_int_property_value
 * @pass-case				When i18n_uset_apply_int_property_value is successful.
 * @fail-case				If target i18n_uset_apply_int_property_value fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_apply_int_property_value_p(void)
{		
	START_TEST;
	int32_t value = 10;
	/* [AS PER THE HEADER INFORMATION, THIS API TAKES THE PROPERTY VALUE AS PER BELOW]
	 * property in the range #I18N_UCHAR_INT_START..#I18N_UCHAR_INT_LIMIT-1
 	 * or #I18N_UCHAR_MASK_START..#I18N_UCHAR_MASK_LIMIT-1.
	*/
	i18n_uchar_uproperty_e eUCharProperty[] =
	{
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
		I18N_UCHAR_GENERAL_CATEGORY_MASK
	};

	int nEnumSize = sizeof(eUCharProperty) / sizeof(eUCharProperty[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		FPRINTF("[Line : %d][%s] Executing i18n_uset_apply_int_property_value with eUCharProperty = %s\\n", __LINE__, API_NAMESPACE, uCharPropertyName(eUCharProperty[nEnumCounter]));

		//Target Api
		int nRetVal = i18n_uset_apply_int_property_value(uset, eUCharProperty[nEnumCounter], value);
		switch(eUCharProperty[nEnumCounter])
		{
			case I18N_UCHAR_BIDI_PAIRED_BRACKET_TYPE: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_BPT_NONE, I18N_UCHAR_U_BPT_CLOSE, "i18n_uset_apply_int_property_value");
				break;

			case I18N_UCHAR_JOINING_GROUP:
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_JG_NO_JOINING_GROUP, I18N_UCHAR_U_JG_AFRICAN_QAF, "i18n_uset_apply_int_property_value");
				break;
			
			case I18N_UCHAR_WORD_BREAK: 
				CHECK_RETURN_ENUM_VAL(I18N_UCHAR_U_WB_OTHER, I18N_UCHAR_U_WB_ZWJ, "i18n_uset_apply_int_property_value");
				break;
			
			default	: 
				PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_apply_int_property_value", BaseUtilsGetError(nRetVal));
				break;
		}
	}
	return 0;
}

//& purpose: Modifies the set to contain those code points which have the given value for the given property.
/**
 * @testcase 				ITc_i18n_uset_apply_property_alias_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Modifies the set to contain those code points which have the given value for the given property.
 * @scenario				Modifies the set to contain those code points which have the given value for the given property.				
 * @api-covered				i18n_uset_apply_property_alias
 * @pass-case				When i18n_uset_apply_property_alias is successful.
 * @fail-case				If target i18n_uset_apply_property_alias fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_apply_property_alias_p(void)
{		
	START_TEST;
	const i18n_uchar prop[] = {0x6C, 0x62, 0x0}; /* "lb" */
    int32_t prop_length = 3;
    const i18n_uchar value[] = {0x53, 0x50, 0x0}; /* "SP" */
    int32_t value_length = 3;
	
	//Target Api
	int nRetVal = i18n_uset_apply_property_alias(uset, prop, prop_length, value, value_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_apply_property_alias", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose: Resembles the pattern.
/**
 * @testcase 				ITc_i18n_uset_resembles_pattern_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Return true if the given position, in the given pattern, appears to be the start of a UnicodeSet pattern.
 * @scenario				Resembles the pattern for the given positionand pattern.			
 * @api-covered				i18n_uset_resembles_pattern
 * @pass-case				When i18n_uset_resembles_pattern is successful.
 * @fail-case				If target i18n_uset_resembles_pattern fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_resembles_pattern_p(void)
{		
	START_TEST;
    char *pattern = "[:NewPattern:]";
    i18n_uchar *upattern = NULL;
    int32_t pos = 0;
	
    upattern = (i18n_uchar*) calloc(strlen(pattern) + 1, sizeof(i18n_uchar));
    i18n_uchar *pRet = i18n_ustring_copy_ua(upattern, pattern);
	int32_t upattern_length = i18n_ustring_get_length(upattern);
	if(pRet == NULL || upattern_length <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY1(upattern);
		return 1;
	}

	//Target Api
    i18n_ubool ubool = i18n_uset_resembles_pattern(upattern, upattern_length, pos);
	if(ubool == 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_uset_resembles_pattern return zero  \n", __LINE__, API_NAMESPACE);
		FREE_MEMORY1(upattern);
		return 1;
	}
	
    int nRetVal = get_last_result();
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_uset_resembles_pattern", BaseUtilsGetError(nRetVal),FREE_MEMORY1(upattern));
	
	FREE_MEMORY1(upattern);
	
	return 0;
}

//& purpose:  Modifies the set to represent the set specified by the given pattern.
/**
 * @testcase 				ITc_i18n_uset_to_pattern_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Modifies the set to represent the set specified by the given pattern.
 * @scenario				Modifies the set to represent the set specified by the given pattern.					
 * @api-covered				i18n_uset_to_pattern
 * @pass-case				When i18n_uset_to_pattern is successful.
 * @fail-case				If target i18n_uset_to_pattern fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_to_pattern_p(void)
{		
	START_TEST;
	i18n_uchar res[12] = {0,};
    int32_t res_capacity = sizeof(res)/sizeof(res[0]);
    i18n_ubool escape_unprintable = true;

	//Target api
    int32_t nLength = i18n_uset_to_pattern(uset, res, res_capacity, escape_unprintable);
	CHECK_RETURN_VAL(nLength, "i18n_uset_to_pattern");
	
    int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_to_pattern", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose: Adds and Removes the given character to the given #i18n_uset_h.
/**
 * @testcase 				ITc_i18n_uset_add_remove_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Adds and Removes the given character to the given #i18n_uset_h.
 * @scenario				Adds the given character to the given #i18n_uset_h.
 *							Removes the given character to the given #i18n_uset_h.
 * @api-covered				i18n_uset_add, i18n_uset_remove
 * @pass-case				When i18n_uset_add & i18n_uset_remove is successful.
 * @fail-case				If target i18n_uset_add & i18n_uset_remove fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_add_remove_p(void)
{		 
	START_TEST;
	i18n_uchar32 c = 0x61;
	
	//Target Api
	int nRetVal = i18n_uset_add(uset, c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add", BaseUtilsGetError(nRetVal));
	
	//Target Api
	nRetVal = i18n_uset_remove(uset, c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_remove", BaseUtilsGetError(nRetVal));
	
	return 0;
}

//& purpose: Adds and Removes all of the elements in the specified set to this set if they are not already present.
/**
 * @testcase 				ITc_i18n_uset_add_remove_all_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Adds and Removes all of the elements in the specified set to this set if they are not already present.
 * @scenario				Adds all of the elements in the specified set
 *							Removes all of the elements in the specified set						
 * @api-covered				i18n_uset_create, i18n_uset_add_all, i18n_uset_remove_all, i18n_uset_destroy
 * @pass-case				When i18n_uset_add_all & i18n_uset_remove_all is successful.
 * @fail-case				If target i18n_uset_add_all & i18n_uset_remove_all fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_add_remove_all_p(void)
{		
	START_TEST;
	i18n_uset_h uset_new = NULL;
    i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;
	
    int nRetVal = i18n_uset_create(start1, end1, &uset_new);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));

	//Target Api
    nRetVal = i18n_uset_add_all(uset, uset_new);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_all", BaseUtilsGetError(nRetVal));
	
	//Target Api
	nRetVal = i18n_uset_remove_all(uset, uset_new);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_remove_all", BaseUtilsGetError(nRetVal));
	
	nRetVal = i18n_uset_destroy(uset_new);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

   
 //& purpose:Adds and Removes the given range of characters to the given #i18n_uset_h.
/**
 * @testcase 				ITc_i18n_uset_add_remove_range_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Adds and removes the given range of characters to the given #i18n_uset_h.
 * @scenario				Adds the given range of characters to the given #i18n_uset_h.\n
 *							Removes the given range of characters to the given #i18n_uset_h.						
 * @api-covered				i18n_uset_add_range, i18n_uset_remove_range
 * @pass-case				When i18n_uset_add_range, i18n_uset_remove_range is successful.
 * @fail-case				If target i18n_uset_add_range, i18n_uset_remove_range fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_add_remove_range_p(void)
{		
	START_TEST;
	i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;

	//Target Api
    int nRetVal = i18n_uset_add_range(uset, start1, end1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_range", BaseUtilsGetError(nRetVal));
	
	//Target Api
    nRetVal = i18n_uset_remove_range(uset, start1, end1);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_remove_range", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Adds and Removes the given string to the given #i18n_uset_h.
/**
 * @testcase 				ITc_i18n_uset_add_remove_string_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Adds and Removes the given string to the given #i18n_uset_h.
 * @scenario				Adds the given string to the given #i18n_uset_h.\n		
 *							Removes the given string to the given #i18n_uset_h. 
 * @api-covered				i18n_uset_add_string, i18n_uset_remove_string
 * @pass-case				When i18n_uset_add_string & i18n_uset_remove_string is successful.
 * @fail-case				If target i18n_uset_add_string & i18n_uset_remove_string fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_add_remove_string_p(void)
{		
	START_TEST;
	const i18n_uchar str[] = {'m', 'a', 'r', 'k', '\0'};
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target Api
    int nRetVal = i18n_uset_add_string(uset, str, str_len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_string", BaseUtilsGetError(nRetVal));
	
	//Target Api
    nRetVal = i18n_uset_remove_string(uset, str, str_len);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_remove_string", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Adds each of the characters in this string to the set.
/**
 * @testcase 				ITc_i18n_uset_add_all_code_points_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Adds each of the characters in this string to the set.
 * @scenario				Adds each of the characters in this string to the set.					
 * @api-covered				i18n_uset_add_all_code_points
 * @pass-case				When i18n_uset_add_all_code_points is successful.
 * @fail-case				If target i18n_uset_add_all_code_points fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_add_all_code_points_p(void)
{		
	START_TEST;
	const i18n_uchar str[] = {'m', 'a', 'r', 'k', '\0'};
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}

	//Target Api
    int nRetVal = i18n_uset_add_all_code_points(uset, str, str_len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_all_code_points", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Retains only the elements in this set that are contained in the specified range.
/**
 * @testcase 				ITc_i18n_uset_retain_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Retains only the elements in this set that are contained in the specified range.
 * @scenario				Retains only the elements in this set that are contained in the given range.						
 * @api-covered				i18n_uset_retain
 * @pass-case				When i18n_uset_retain is successful.
 * @fail-case				If target i18n_uset_retain fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_retain_p(void)
{		
	START_TEST;
	i18n_uchar32 start1 = 0x41;
   	i18n_uchar32 end1 = 0x42;

	//Target Api
    int nRetVal = i18n_uset_retain(uset, start1, end1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_retain", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Retains only the elements in this set that are contained in the specified set.
/**
 * @testcase 				ITc_i18n_uset_retain_all_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Retains only the elements in this set that are contained in the specified set.
 * @scenario				Retains only the elements in this set that are contained in the given set.						
 * @api-covered				i18n_uset_create, i18n_uset_retain_all, i18n_uset_destroy
 * @pass-case				When i18n_uset_retain_all is successful.
 * @fail-case				If target i18n_uset_retain_all fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_retain_all_p(void)
{		
	START_TEST;
	i18n_uset_h uset_ret = NULL;
	i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;

	int nRetVal = i18n_uset_create(start1, end1, &uset_ret);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
	nRetVal = i18n_uset_retain_all(uset, uset_ret);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal, "i18n_uset_retain_all", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset_ret));
	
	nRetVal = i18n_uset_destroy(uset_ret);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Compacts the given set.
/**
 * @testcase 				ITc_i18n_uset_compact_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Reallocates this objects internal structures to take up the least possible space, without changing this object's value.
 * @scenario				Compacts the given set.					
 * @api-covered				i18n_uset_compact
 * @pass-case				When i18n_uset_compact is successful.
 * @fail-case				If target i18n_uset_compact fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_compact_p(void)
{		
	START_TEST;
	
	//Target Api
    int nRetVal = i18n_uset_compact(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_compact", BaseUtilsGetError(nRetVal));

	return 0;
}
     
 //& purpose: Inverts the given set.
/**
 * @testcase 				ITc_i18n_uset_complement_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Inverts this set.  This operation modifies this set so that its value is its complement.
 * @scenario				Complement the given set.						
 * @api-covered				i18n_uset_complement
 * @pass-case				When i18n_uset_complement is successful.
 * @fail-case				If target i18n_uset_complement fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_complement_p(void)
{		
	START_TEST;
	
	//Target Api
    int nRetVal = i18n_uset_complement(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_complement", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Complements in this set all elements contained in the specified set.
/**
 * @testcase 				ITc_i18n_uset_complement_all_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Complements in this set all elements contained in the specified set.
 * @scenario				Complements the specified set.				
 * @api-covered				i18n_uset_create, i18n_uset_complement_all, i18n_uset_destroy
 * @pass-case				When i18n_uset_complement_all is successful.
 * @fail-case				If target i18n_uset_complement_all fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_complement_all_p(void)
{		
	START_TEST;
	i18n_uset_h uset_com = NULL;
    i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;
	
	int nRetVal = i18n_uset_create(start1, end1, &uset_com);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
    nRetVal = i18n_uset_complement_all(uset, uset_com);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_complement_all", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset_com));

	nRetVal = i18n_uset_destroy(uset_com);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose:Removes all of the elements from this set.
/**
 * @testcase 				ITc_i18n_uset_clear_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Removes all of the elements from this set.
 * @scenario				Clears the set.				
 * @api-covered				i18n_uset_clear
 * @pass-case				When i18n_uset_clear is successful.
 * @fail-case				If target i18n_uset_clear fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_clear_p(void)
{		
	START_TEST;
	
	//Target Api
    int nRetVal = i18n_uset_clear(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_clear", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Closes this set over the given attribute.
/**
 * @testcase 				ITc_i18n_uset_destroy_over_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Closes this set over the given attribute.
 * @scenario				Disposes the set over the given attribute.						
 * @api-covered				i18n_uset_destroy_over
 * @pass-case				When i18n_uset_destroy_over is successful.
 * @fail-case				If target i18n_uset_destroy_over fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_destroy_over_p(void)
{		
	START_TEST;
	int32_t attributes[] = { I18N_USET_IGNORE_SPACE, I18N_USET_CASE_INSENSITIVE, I18N_USET_ADD_CASE_MAPPINGS};
	int nEnumSize = sizeof(attributes) / sizeof(attributes[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		//Target Api
		int nRetVal = i18n_uset_destroy_over(uset, attributes[nEnumCounter]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy_over", BaseUtilsGetError(nRetVal));
	}
	return 0;
}

 //& purpose: Removes all strings from this set.
/**
 * @testcase 				ITc_i18n_uset_remove_all_strings_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Removes all strings from this set.
 * @scenario				Removes all strings from this set.					
 * @api-covered				i18n_uset_remove_all_strings
 * @pass-case				When i18n_uset_remove_all_strings is successful.
 * @fail-case				If target i18n_uset_remove_all_strings fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_remove_all_strings_p(void)
{		
	START_TEST;
	
	//Target Api
    int nRetVal = i18n_uset_remove_all_strings(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy_over", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: checks whether set contains no characters and no strings.
/**
 * @testcase 				ITc_i18n_uset_destroy_over_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if the given #i18n_uset_h contains no characters and no strings.
 * @scenario				Clears the set.\n			
 * 							Check whether set is empty or not.	 
 * @api-covered				i18n_uset_clear, i18n_uset_is_empty
 * @pass-case				When i18n_uset_is_empty is successful.
 * @fail-case				If target i18n_uset_is_empty fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_is_empty_p(void)
{		
	START_TEST;
	
	int nRetVal = i18n_uset_clear(uset);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_clear", BaseUtilsGetError(nRetVal));
	
	//Target Api
	i18n_ubool ubool = i18n_uset_is_empty(uset);
	CHECK_VALUE_INT(ubool, "i18n_uset_is_empty");
	
    nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_is_empty", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: Checks if the given set contains the specified character.
/**
 * @testcase 				ITc_i18n_uset_contains_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns @c true if the given #i18n_uset_h contains the given @a character.
 * @scenario				Add the specified character.\n	
 *							Determines whether set contains the specified character. 
 * @api-covered				i18n_uset_add, i18n_uset_contains
 * @pass-case				When i18n_uset_contains is successful.
 * @fail-case				If target i18n_uset_contains fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_p(void)
{		
	START_TEST;
	i18n_uchar32 c = 0x61;
	
	int nRetVal = i18n_uset_add(uset, c);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add", BaseUtilsGetError(nRetVal));
	
	//Target Api
	i18n_ubool ubool = i18n_uset_contains(uset, c);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains");
	
    nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_contains", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: Determines whether set contains the specified range of characters.	
/**
 * @testcase 				ITc_i18n_uset_contains_range_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if the given #i18n_uset_h contains all characters c where start <= c && c <= end.
 * @scenario				Add the specified range of characters.\n	
 *							Determines whether set contains the specified range of characters.						
 * @api-covered				i18n_uset_add_range, i18n_uset_contains_range 
 * @pass-case				When i18n_uset_contains_range is successful.
 * @fail-case				If target i18n_uset_contains_range fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_range_p(void)
{		
	START_TEST;
	i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;

    int nRetVal = i18n_uset_add_range(uset, start1, end1);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_range", BaseUtilsGetError(nRetVal));
	
	//Target Api
	i18n_ubool ubool = i18n_uset_contains_range(uset, start1, end1);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_range");
	
    nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_contains_range", BaseUtilsGetError(nRetVal));

	return 0;
}

//& purpose: Determines whether set contains the specified string.	
/**
 * @testcase 				ITc_i18n_uset_contains_string_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if the given #i18n_uset_h contains the given string.
 * @scenario				Add the specified string.\n	
 *							Determines whether set contains the specified string.					
 * @api-covered				i18n_uset_add_string, i18n_uset_contains_string
 * @pass-case				When i18n_uset_contains_string is successful.
 * @fail-case				If target i18n_uset_contains_string fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_string_p(void)
{		
	START_TEST;
	 const i18n_uchar str[] = {'m', 'a', 'r', 'k', '\0'};
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}

    int nRetVal = i18n_uset_add_string(uset, str, str_len);
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_string", BaseUtilsGetError(nRetVal));
	
	//Target Api
    i18n_ubool ubool = i18n_uset_contains_string(uset, str, str_len);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_string");
	
    nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_contains_string", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Returns the index of the given character within the given set.
/**
 * @testcase 				ITc_i18n_uset_index_of_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the index of the given @a character within this @a set, where the @a set is ordered by ascending code point.
 * @scenario				Returns the index of the given character within this set.						
 * @api-covered				i18n_uset_index_of
 * @pass-case				When i18n_uset_index_of is successful.
 * @fail-case				If target i18n_uset_index_of fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_index_of_p(void)
{		
	START_TEST;
	i18n_uchar32 c = 0x41;
	int32_t nIndex = -1;
	
	//Target Api
    nIndex = i18n_uset_index_of(uset, c);
	CHECK_RETURN_VAL(nIndex , "i18n_uset_index_of");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_index_of", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Returns character at the given index within the given set.
/**
 * @testcase 				ITc_i18n_uset_char_at_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the character at the given index within this set, where the set is ordered by ascending code point.
 * @scenario				Returns character at the given index within the given set.				
 * @api-covered				i18n_uset_char_at
 * @pass-case				When i18n_uset_char_at is successful.
 * @fail-case				If target i18n_uset_char_at fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_char_at_p(void)
{		
	START_TEST;
	int32_t char_index = 0;
	i18n_uchar32 uchar = NULL;

	//Target Api
    uchar = i18n_uset_char_at(uset, char_index);
	if(uchar == (i18n_uchar32)0)
	{	
		return 1;		
	}
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_char_at", BaseUtilsGetError(nRetVal));

	return 0;
}
	
 //& purpose: Returns the size of the set.
/**
 * @testcase 				ITc_i18n_uset_size_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the number of characters and strings contained in the given #i18n_uset_h.
 * @scenario				Returns the size of the set.						
 * @api-covered				i18n_uset_size
 * @pass-case				When i18n_uset_size is successful.
 * @fail-case				If target i18n_uset_size fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_size_p(void)
{		
	START_TEST;
	int32_t nIndex = -1;

	//Target Api
    nIndex = i18n_uset_size(uset);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_size");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_size", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose:Returns the number of items in this set.
/**
 * @testcase 				ITc_i18n_uset_get_item_count_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the number of items (either a range of characters or a single multicharacter string)in this set.
 * @scenario				Returns the number of items in this set.				
 * @api-covered				i18n_uset_get_item_count
 * @pass-case				When i18n_uset_get_item_count is successful.
 * @fail-case				If target i18n_uset_get_item_count fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_get_item_count_p(void)
{		
	START_TEST;
	int32_t nIndex = -1;

	//Target Api
    nIndex = i18n_uset_get_item_count(uset);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_get_item_count");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_item_count", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Returns an item of this set.
/**
 * @testcase 				ITc_i18n_uset_get_item_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns an item (either a range of characters or a single multicharacter string)in this set.
 * @scenario				Returns an item of this set.						
 * @api-covered				i18n_uset_get_item
 * @pass-case				When i18n_uset_get_item is successful.
 * @fail-case				If target i18n_uset_get_item fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_get_item_p(void)
{		
	START_TEST;
	i18n_uchar32 start1 = 0;
    i18n_uchar32 end1 = 0;
    i18n_uchar str[12] = {0,};
    int32_t str_capacity = sizeof(str)/sizeof(str[0]);
	
	//Target Api
    int32_t nLength = i18n_uset_get_item (uset, 0, &start1, &end1, str, str_capacity);
	CHECK_RETURN_VAL(nLength, "i18n_uset_get_item");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_item", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Determines that set1 a superset of set2.
/**
 * @testcase 				ITc_i18n_uset_contains_all_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if set1 contains all the characters and strings of set2. It answers the question, 'Is set1 a superset of set2?'
 * @scenario				Determines that set1 a superset of set2.						
 * @api-covered				i18n_uset_create,i18n_uset_contains_all, i18n_uset_destroy
 * @pass-case				When i18n_uset_contains_all is successful.
 * @fail-case				If target i18n_uset_contains_all fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_all_p(void)
{		
	START_TEST;
	i18n_uset_h uset2 = NULL;
    i18n_uchar32 start1 = 0x41;
    i18n_uchar32 end1 = 0x48;
	
	int nRetVal = i18n_uset_create(start1, end1, &uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
    i18n_ubool ubool = i18n_uset_contains_all(uset, uset2);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_all");
	
	nRetVal = get_last_result(); 
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_contains_all", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset2));
	
	nRetVal = i18n_uset_destroy(uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Returns true if this set contains all the characters of the given string.
/**
 * @testcase 				ITc_i18n_uset_contains_all_code_points_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if this set contains all the characters of the given string.
 * @scenario				Add all code points.\n
 *							checks whether uset contains all added code points.
 * @api-covered				i18n_uset_add_all_code_points, i18n_uset_contains_all_code_points
 * @pass-case				When i18n_uset_contains_all_code_points is successful.
 * @fail-case				If target i18n_uset_contains_all_code_points fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_all_code_points_p(void)
{		
	START_TEST;
	const i18n_uchar str[] = {'m', 'a', 'r', 'k', '\0'};
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}

    int nRetVal = i18n_uset_add_all_code_points(uset, str, str_len);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_add_all_code_points", BaseUtilsGetError(nRetVal));
	
	//Target Api
	i18n_ubool ubool = i18n_uset_contains_all_code_points(uset, str, str_len);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_all_code_points");
	
    nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_contains_all_code_points", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Determines whether set1 a disjoint set of set2.
/**
 * @testcase 				ITc_i18n_uset_contains_none_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if set1 contains none of the characters and strings of set2.
 * @scenario				Determines whether set1 a disjoint set of set2.						
 * @api-covered				i18n_uset_create, i18n_uset_contains_none, i18n_uset_destroy
 * @pass-case				When i18n_uset_contains_none is successful.
 * @fail-case				If target i18n_uset_contains_none fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_none_p(void)
{		
	START_TEST;
	i18n_uset_h uset2 = NULL;
    i18n_uchar32 start1 = 0x51;
    i18n_uchar32 end1 = 0x60;
	
	int nRetVal = i18n_uset_create(start1, end1, &uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
    i18n_ubool ubool = i18n_uset_contains_none(uset, uset2);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_all_code_points");
	
	nRetVal = get_last_result(); 
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_contains_none", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset2));
	
	nRetVal = i18n_uset_destroy(uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Determines whether set1 and set2 have an intersection.
/**
 * @testcase 				ITc_i18n_uset_contains_some_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if set1 contains some of the characters and strings of set2.
 * @scenario				Determines whether set1 and set2 have an intersection.						
 * @api-covered				i18n_uset_create, i18n_uset_contains_some, i18n_uset_destroy
 * @pass-case				When i18n_uset_contains_some is successful.
 * @fail-case				If target i18n_uset_contains_some fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_contains_some_p(void)
{		
	START_TEST;
	i18n_uset_h uset2 = NULL;
    i18n_uchar32 start1 = 0x45;
    i18n_uchar32 end1 = 0x55;
	
	int nRetVal = i18n_uset_create(start1, end1, &uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
    i18n_ubool ubool = i18n_uset_contains_some(uset, uset2);
	CHECK_VALUE_INT(ubool, "i18n_uset_contains_all_code_points");
	
	nRetVal = get_last_result(); 
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_contains_some", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset2));
	
	nRetVal = i18n_uset_destroy(uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Returns the length of the initial substring of the input string for the give condition
/**
 * @testcase 				ITc_i18n_uset_span_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the length of the initial substring of the input string which consists only of characters\n 
 *							and strings that are contained/not contained in this set
 * @scenario				Returns the length of the initial substring of the input string for the give condition					
 * @api-covered				i18n_uset_span
 * @pass-case				When i18n_uset_span is successful.
 * @fail-case				If target i18n_uset_span fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_span_p(void)
{		
	START_TEST;
	const i18n_uchar str[] = {'q', 'w', 'e', 'r', '\0'};
	int32_t nIndex = -1;
	
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	i18n_uset_span_condition_e span_condition[] = { I18N_USET_SPAN_NOT_CONTAINED, I18N_USET_SPAN_CONTAINED, I18N_USET_SPAN_SIMPLE,
		I18N_USET_SPAN_CONDITION_COUNT };
	int nEnumSize = sizeof(span_condition) / sizeof(span_condition[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{	
		nIndex = i18n_uset_span(uset, str, str_len, span_condition[nEnumCounter]);
		CHECK_RETURN_VAL(nIndex, "i18n_uset_span");
		
		int nRetVal = get_last_result(); 
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_span", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}

 //& purpose: Returns the start of the trailing substring of the input string for the give condition
/**
 * @testcase 				ITc_i18n_uset_span_back_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the start of the trailing substring of the input string which
 * 					        consists only of characters and strings that are contained/not contained in this set
 * @scenario				Returns the length of the triling substring of the input string for the give condition						
 * @api-covered				i18n_uset_span_back
 * @pass-case				When i18n_uset_span_back is successful.
 * @fail-case				If target i18n_uset_span_back fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_span_back_p(void)
{		
	START_TEST;
	const i18n_uchar str[] = {'q', 'w', 'e', 'r', '\0'};
	int32_t nIndex = -1;
	
    int32_t str_len = i18n_ustring_get_length(str);
	if(str_len <= 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ustring_copy_ua failed in precondition \n", __LINE__, API_NAMESPACE);
		return 1;
	}
    i18n_uset_span_condition_e span_condition[] = { I18N_USET_SPAN_NOT_CONTAINED, I18N_USET_SPAN_CONTAINED, I18N_USET_SPAN_SIMPLE,
		I18N_USET_SPAN_CONDITION_COUNT };
	int nEnumSize = sizeof(span_condition) / sizeof(span_condition[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		nIndex = i18n_uset_span_back(uset, str, str_len, span_condition[nEnumCounter]);
		CHECK_RETURN_VAL(nIndex, "i18n_uset_span_back");
		
		int nRetVal = get_last_result(); 
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_span_back", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}

 //& purpose: Returns the length of the initial substring of the input string for the give condition
/**
 * @testcase 				ITc_i18n_uset_span_utf8_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the length of the initial substring of the input string which
 *        					consists only of characters and strings that are contained/not contained in this set
 * @scenario				Returns the length of the initial substring of the input string for the give condition				
 * @api-covered				i18n_uset_span_utf8
 * @pass-case				When i18n_uset_span_utf8 is successful.
 * @fail-case				If target i18n_uset_span_utf8 fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_span_utf8_p(void)
{		
	START_TEST;
	const char *s = "qwer";
    int32_t length = strlen(s);
	int32_t nIndex = -1;
	
	i18n_uset_span_condition_e span_condition[] = { I18N_USET_SPAN_NOT_CONTAINED, I18N_USET_SPAN_CONTAINED, I18N_USET_SPAN_SIMPLE,
		I18N_USET_SPAN_CONDITION_COUNT };
	int nEnumSize = sizeof(span_condition) / sizeof(span_condition[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		nIndex = i18n_uset_span_utf8 (uset, s, length, span_condition[nEnumCounter]);
		CHECK_RETURN_VAL(nIndex, "i18n_uset_span_utf8");
		
		int nRetVal = get_last_result(); 
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_span_utf8", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}

 //& purpose: Returns the start of the trailing substring of the input string for the give condition
/**
 * @testcase 				ITc_i18n_uset_span_back_utf8_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the start of the trailing substring of the input string which
 *       					consists only of characters and strings that are contained/not contained in this set
 * @scenario				Returns the start of the trailing substring of the input string for the give condition				
 * @api-covered				i18n_uset_span_back_utf8
 * @pass-case				When i18n_uset_span_back_utf8 is successful.
 * @fail-case				If target i18n_uset_span_back_utf8 fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_span_back_utf8_p(void)
{		
	START_TEST;
	const char *s = "qwer";
    int32_t length = strlen(s);
	int32_t nIndex = -1;
	
    i18n_uset_span_condition_e span_condition[] = { I18N_USET_SPAN_NOT_CONTAINED, I18N_USET_SPAN_CONTAINED, I18N_USET_SPAN_SIMPLE,
		I18N_USET_SPAN_CONDITION_COUNT };
	int nEnumSize = sizeof(span_condition) / sizeof(span_condition[0]);
	int nEnumCounter = 0;
	
	for (nEnumCounter = 0; nEnumCounter < nEnumSize;  nEnumCounter++)
	{
		nIndex = i18n_uset_span_back_utf8 (uset, s, length, span_condition[nEnumCounter]);
		CHECK_RETURN_VAL(nIndex, "i18n_uset_span_back_utf8");
		
		int nRetVal = get_last_result(); 
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_span_back_utf8", BaseUtilsGetError(nRetVal));
	}
	
	return 0;
}

 //& purpose: Checks that set1 is equal to set2 or not.
/**
 * @testcase 				ITc_i18n_uset_equals_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns true if set1 contains all of the characters and strings of set2, and vice versa.
 * @scenario				Checks that set1 is equal to set2 or not.						
 * @api-covered				i18n_uset_create, i18n_uset_equals, i18n_uset_destroy
 * @pass-case				When i18n_uset_equals is successful.
 * @fail-case				If target i18n_uset_equals fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_equals_p(void)
{		
	START_TEST;
	i18n_uset_h uset2 = NULL;
    i18n_uchar32 start1 = 0x41;
    i18n_uchar32 end1 = 0x50;
	
	int nRetVal = i18n_uset_create(start1, end1, &uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_create", BaseUtilsGetError(nRetVal));
	
	//Target Api
    i18n_ubool ubool = i18n_uset_equals(uset, uset2);
	CHECK_VALUE_INT(ubool, "i18n_uset_equals");
	
	nRetVal = get_last_result(); 
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRetVal,"i18n_uset_equals", BaseUtilsGetError(nRetVal), i18n_uset_destroy(uset2));
	
	nRetVal = i18n_uset_destroy(uset2);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

 //& purpose: Sets the serialized set.
/**
 * @testcase 				ITc_i18n_uset_serialize_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Serializes this @a set into an array of 16-bit integers.
 * @scenario				Serializes the set.					
 * @api-covered				i18n_uset_serialize
 * @pass-case				When i18n_uset_serialize is successful.
 * @fail-case				If target i18n_uset_serialize fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_serialize_p(void)
{		
	START_TEST;
	uint16_t dest[48] = {0, 1, 2, 0};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);
	int32_t nIndex = -1;
	
	//Target Api
    nIndex = i18n_uset_serialize(uset, dest, dest_capacity);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_serialize");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialize", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Gets the serialized set.
/**
 * @testcase 				ITc_i18n_uset_get_serialized_set_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Given a serialized array, fill in the given serialized set object.
 * @scenario				Sets the serialized set.
 *							Gets the serialized set.
 * @api-covered				i18n_uset_serialize, i18n_uset_get_serialized_set
 * @pass-case				When i18n_uset_get_serialized_set is successful.
 * @fail-case				If target i18n_uset_get_serialized_set fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_get_serialized_set_p(void)
{
	START_TEST;
	uint16_t dest[48] = {0, 1, 2, 0};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);
	int32_t nIndex = -1;
	
    nIndex = i18n_uset_serialize(uset, dest, dest_capacity);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_serialize");
	
	int nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialize", BaseUtilsGetError(nRetVal));

    i18n_userialized_set_s fill_set;
	//Target Api
    i18n_ubool ubool = i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
	CHECK_VALUE_INT(ubool, "i18n_uset_get_serialized_set");
	
    nRetVal = get_last_result(); 
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_set", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Sets the serialized set with given character.		
/**
 * @testcase 				ITc_i18n_uset_set_serialized_to_one_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Sets the #i18n_userialized_set_s to contain the given @a character (and nothing else).
 * @scenario				Sets the serialized set with given character.					
 * @api-covered				i18n_uset_set_serialized_to_one
 * @pass-case				When i18n_uset_set_serialized_to_one is successful.
 * @fail-case				If target i18n_uset_set_serialized_to_one fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_set_serialized_to_one_p(void)
{
	START_TEST;
	i18n_uchar32 c = 0x41;
    i18n_userialized_set_s fill_set;
	int32_t nLength = -1;
	
	//Target Api
    int nRetVal = i18n_uset_set_serialized_to_one(c, &fill_set);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_set_serialized_to_one", BaseUtilsGetError(nRetVal));
	
	nLength = fill_set.length;
	CHECK_RETURN_VAL(nLength, "i18n_uset_set_serialized_to_one");
	
	return 0;
}

 //& purpose: checks whether the serialized set contains the given character.
/**
 * @testcase 				ITc_i18n_uset_serialized_contains_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns @c true if the given #i18n_userialized_set_s contains the given @a character.
 * @scenario				Sets the serialize set.\n
 *							Gets the serialized set.\n
 *							checks whether the serialized set contains the given character.						
 * @api-covered				i18n_uset_serialize, i18n_uset_get_serialized_set, i18n_uset_serialized_contains
 * @pass-case				When i18n_uset_serialized_contains is successful.
 * @fail-case				If target i18n_uset_serialized_contains fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_serialized_contains_p(void)
{
	START_TEST;
	uint16_t dest[48] = {0, 1, 2, 0};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);
	int32_t nIndex = -1;
	
    nIndex = i18n_uset_serialize(uset, dest, dest_capacity);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_serialize");

    int nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialize", BaseUtilsGetError(nRetVal));
	
	i18n_userialized_set_s fill_set;
    i18n_ubool ubool = i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
	CHECK_VALUE_INT(ubool, "i18n_uset_get_serialized_set");
	
    nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_set", BaseUtilsGetError(nRetVal));
	
	i18n_uchar32 c = 0x41;
	//Target Api
    ubool = i18n_uset_serialized_contains(&fill_set, c);
	CHECK_VALUE_INT(ubool, "i18n_uset_serialized_contains");
	
    nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialized_contains", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Returns the number of disjoint ranges of characters contained in the given serialized set.
/**
 * @testcase 				ITc_i18n_uset_get_serialized_range_count_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Returns the number of disjoint ranges of characters contained in the given serialized set.
 * @scenario				Sets the serialize set.\n
 *							Gets the serialized set.\n
 *							Gets the range count for the serialized set.						
 * @api-covered				i18n_uset_get_serialized_range_count, i18n_uset_get_serialized_set, i18n_uset_get_serialized_range_count
 * @pass-case				When i18n_uset_get_serialized_range_count is successful.
 * @fail-case				If target i18n_uset_get_serialized_range_count fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_get_serialized_range_count_p(void)
{
	START_TEST;
    uint16_t dest[48] = {0, 1, 2, 0};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);
	int32_t nIndex = -1;
	
    nIndex = i18n_uset_serialize(uset, dest, dest_capacity);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_serialize");

    int nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialize", BaseUtilsGetError(nRetVal));

    i18n_userialized_set_s fill_set;
    i18n_ubool ubool = i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
	CHECK_VALUE_INT(ubool, "i18n_uset_get_serialized_set");
	
    nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_set", BaseUtilsGetError(nRetVal));
	
	//Target Api
    nIndex = i18n_uset_get_serialized_range_count (&fill_set);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_get_serialized_range_count");
	
    nRetVal = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_range_count", BaseUtilsGetError(nRetVal));
	
	return 0;
}

 //& purpose: Gets the current date and time.
/**
 * @testcase 				ITc_i18n_uset_get_serialized_range_p
 * @since_tizen 			2.3.1
 * @author            		SRID(pushpa.singh)
 * @reviewer         		SRID(gupta.sanjay)
 * @type 					auto
 * @description				Play and stop various type of reactions e.g media or vibration patterns
 * @scenario				Gets the current date and time.						
 * @api-covered				i18n_ustring_to_title
 * @pass-case				When i18n_ustring_to_title is successful.
 * @fail-case				If target i18n_ustring_to_title fails or any precondition and postcondition api fails.
 * @pre-condition			NA
 * @post-condition			NA 
 */
int ITc_i18n_uset_get_serialized_range_p(void)
{
	START_TEST;	
    uint16_t dest[48] = {0, 1, 2, 0};
    int32_t dest_capacity = sizeof(dest)/sizeof(dest[0]);
	int32_t nIndex = -1;
	
    nIndex = i18n_uset_serialize(uset, dest, dest_capacity);
	CHECK_RETURN_VAL(nIndex, "i18n_uset_serialize");

    int nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_serialize", BaseUtilsGetError(nRetVal));

    i18n_userialized_set_s fill_set;
    i18n_ubool ubool = i18n_uset_get_serialized_set(dest, dest_capacity, &fill_set);
	CHECK_VALUE_INT(ubool, "i18n_uset_get_serialized_set");
	
    nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_set", BaseUtilsGetError(nRetVal));

    int32_t range_index = 0;
    i18n_uchar32 p_start = 0;
    i18n_uchar32 p_end = 0;
	//Target Api
    ubool = i18n_uset_get_serialized_range(&fill_set, range_index, &p_start, &p_end);
	CHECK_VALUE_INT(ubool, "i18n_uset_get_serialized_range");
	
    nRetVal = get_last_result();
    PRINT_RESULT(I18N_ERROR_NONE, nRetVal, "i18n_uset_get_serialized_range", BaseUtilsGetError(nRetVal));

    return 0;
}
