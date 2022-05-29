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


static i18n_plural_rules_h g_plural_rules = NULL;
static const char *pszRules = "one: n is 1; few: n in 2..4";

/** @addtogroup itc-base-utils
 *  @ingroup itc
 *  @{
 */



//& set: BaseUtilsPluralRules
void ITs_base_utils_plural_rules_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if(remove(ERR_LOG))
		{
			FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up is failed due to mulfuntion of remove API\\n", __LINE__, API_NAMESPACE);
		}		
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_plural_rules_startup\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet =  i18n_plural_rules_create_rules_from_descr(pszRules, &g_plural_rules);
	if (nRet != I18N_ERROR_NONE) {
		g_bBaseUtilsInitFlag = false;
		FPRINTF("\\n[Line : %d][%s] rules creation failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	else if(g_plural_rules == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_plural_rules is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}

	return;
}

void ITs_base_utils_plural_rules_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_plural_rules_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if (g_plural_rules != NULL)
	{
		i18n_plural_rules_destroy(g_plural_rules);
		g_plural_rules = NULL;
		g_bBaseUtilsInitFlag = false;
	}
}

/** @addtogroup itc-base-utils-testcases
 *  @brief 		Integration testcases for module base-utils plural rules
 *  @ingroup 	itc-base-utils
 *  @{
 */

//& type: auto
//& purpose: Creates and delete a plural rules object
/**
 * @testcase				ITc_i18n_plural_rules_create_destroy_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- Creates and destroy a plural object
 * @apitarget			i18n_plural_rules_create, i18n_plural_rules_destroy
 * @apicovered			i18n_plural_rules_create, i18n_plural_rules_destroy
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_create, i18n_plural_rules_destroy
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_create, i18n_plural_rules_destroy or pre-condition APIs fail
 * @precondition			NA
 * @postcondition				NA
 */
int ITc_i18n_plural_rules_create_destroy_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_rules_h plural_rules = NULL;

	//Target API
	nRet = i18n_plural_rules_create(&plural_rules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(plural_rules, "i18n_plural_rules_create");

	//Target API
	nRet = i18n_plural_rules_destroy(plural_rules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: clone a plural rules object
/**
 * @testcase				ITc_i18n_plural_rules_clone_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- clone a plural object object
 * @apitarget			i18n_plural_rules_clone
 * @apicovered			i18n_plural_rules_clone,i18n_plural_rules_destroy
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_clone
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_clone or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_clone_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_rules_h clone = NULL;

	//Target API
	nRet = i18n_plural_rules_clone(g_plural_rules, &clone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(clone, "i18n_plural_rules_clone");

	nRet = i18n_plural_rules_destroy(clone);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a plural rules object from description
/**
 * @testcase				ITc_i18n_plural_rules_create_rules_from_descr_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- Creates a plural object object from description
 * @apitarget			i18n_plural_rules_create_rules_from_descr
 * @apicovered			i18n_plural_rules_create_rules_from_descr, i18n_plural_rules_destroy
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_create_rules_from_descr, i18n_plural_rules_destroy
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_create_rules_from_descr or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_create_rules_from_descr_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_rules_h plural_rules = NULL;
	const char *szRules = "one: n is 1; few: n in 2..4";

	//Target API
	nRet = i18n_plural_rules_create_rules_from_descr(szRules, &plural_rules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_create_rules_from_descr", BaseUtilsGetError(nRet));
	CHECK_HANDLE(plural_rules, "i18n_plural_rules_create_rules_from_descr");

	nRet = i18n_plural_rules_destroy(plural_rules);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Creates a plural rules locale
/**
 * @testcase			ITc_i18n_plural_rules_for_locale_id_p
 * @since_tizen 		5.0
 * @author            	SRID(shilpa.j)
 * @reviewer         	SRID(a.pandia1)
 * @type 				auto
 * @scenario			- Creates a plural rules locale
 * @apitarget			i18n_plural_rules_for_locale_id
 * @apicovered			i18n_plural_rules_for_locale_id
 * @passcase			I18N_ERROR_NONE returned by i18n_plural_rules_for_locale_id
 * @failcase			I18N_ERROR_NONE not returned by i18n_plural_rules_for_locale_id or pre-condition APIs fail
 * @precondition		NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_for_locale_id_p(void)
{
	START_TEST;

	int nRet = -1;
	const char *pszLocalId = "en_US";

	i18n_plural_rules_h plural_rules = NULL;
	i18n_uplural_type_e ePluralType[] = {I18N_UPLURAL_TYPE_CARDINAL,
		I18N_UPLURAL_TYPE_ORDINAL};
	int enum_size1 = sizeof(ePluralType) / sizeof(i18n_uplural_type_e);
	int enum_counter1 = 0;

	for ( enum_counter1=0; enum_counter1<enum_size1; enum_counter1++)
	{
		//Target API
		nRet = i18n_plural_rules_for_locale_id(pszLocalId, ePluralType[enum_counter1], &plural_rules);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_for_locale_id", BaseUtilsGetError(nRet));
		CHECK_HANDLE(plural_rules, "i18n_plural_rules_for_locale_id");

		nRet = i18n_plural_rules_destroy(plural_rules);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: select int32 plural rules
/**
 * @testcase				ITc_i18n_plural_rules_select_int32_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- select int32 plural rules
 * @apitarget			i18n_plural_rules_select_int32
 * @apicovered			i18n_plural_rules_select_int32
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_select_int32
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_select_int32 or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_select_int32_p(void)
{
	START_TEST;

	int nRet = -1;
	int output_length = -1;
	const char *szOutputValue = "one";
	int32_t number = 1;
	i18n_uchar buffer[BUFFER] = { 0 };
	i18n_uchar output_buffer[BUFFER] = { 0 };

	//Target API
	nRet = i18n_plural_rules_select_int32(g_plural_rules, number, BUFFER, buffer, &output_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_select_int32", BaseUtilsGetError(nRet));

	i18n_ustring_copy_au_n(output_buffer, buffer, BUFFER);

	if (strncmp(output_buffer, szOutputValue, strlen(szOutputValue)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and buffer string %s is not same\\n", __LINE__, API_NAMESPACE, szOutputValue, output_buffer);
		return 1;
	}
	if(output_length != strlen(szOutputValue) )
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, output_length, strlen(szOutputValue));
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: select doubles plural rules
/**
 * @testcase				ITc_i18n_plural_rules_select_double_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- select doubles rules
 * @apitarget			i18n_plural_rules_select_double
 * @apicovered			i18n_plural_rules_select_double,i18n_ustring_copy_au_n
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_select_double
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_select_double or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_select_double_p(void)
{
	START_TEST;

	int nRet = -1;
	const char *szOutputValue = "few";
	double number = 2.0;
	i18n_uchar buffer[BUFFER] = { 0 };
	int output_length = -1;
	char output_buffer[BUFFER] = { 0 };

	//Target API
	nRet = i18n_plural_rules_select_double(g_plural_rules, number, BUFFER, buffer, &output_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_select_double", BaseUtilsGetError(nRet));
	i18n_ustring_copy_au_n(output_buffer, buffer, BUFFER);

	if (strncmp(output_buffer, szOutputValue, strlen(szOutputValue)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and buffer string %s is not same\\n", __LINE__, API_NAMESPACE, szOutputValue, output_buffer);
		return 1;
	}

	if(output_length != strlen(szOutputValue) )
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, output_length, strlen(szOutputValue));
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: get a plural rules keywords
/**
 * @testcase				IITc_i18n_plural_rules_get_keywords_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- get a plural rules keywords
 * @apitarget			i18n_plural_rules_get_keywords
 * @apicovered			i18n_plural_rules_get_keywords
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_get_keywords
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_get_keywords or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_get_keywords_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_uenumeration_h result = NULL;

	//Target API
	nRet = i18n_plural_rules_get_keywords(g_plural_rules, &result);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_get_keywords", BaseUtilsGetError(nRet));
	CHECK_HANDLE(result, "i18n_plural_rules_get_keywords");

	nRet = i18n_uenumeration_destroy(result);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_uenumeration_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: get a plural rules sample
/**
 * @testcase				ITc_i18n_plural_rules_get_samples_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- get a plural rules sample
 * @apitarget			i18n_plural_rules_get_samples
 * @apicovered			i18n_plural_rules_get_samples
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_get_samples
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_get_samples or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_get_samples_p(void)
{
	START_TEST;

	int nRet = -1;
	double array[BUFFER] = { 0 };
	const char *szKeyword = "few";
	int count = -1;

	//Target API
	nRet = i18n_plural_rules_get_samples(g_plural_rules, szKeyword, array, BUFFER, &count);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_get_samples", BaseUtilsGetError(nRet));
	if (count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] count %d is not set\\n", __LINE__, API_NAMESPACE, count);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: check the status of keywords
/**
 * @testcase				ITc_i18n_plural_rules_is_keyword_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- check the status of keywords
 * @apitarget			i18n_plural_rules_is_keyword
 * @apicovered			i18n_plural_rules_is_keyword
 * @passcase				I18N_ERROR_NONE returned by i18n_plural_rules_is_keyword
 * @failcase				I18N_ERROR_NONE not returned by i18n_plural_rules_is_keyword or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_is_keyword_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_ubool bKeyword = false;
	const char *szKeyword = "one";

	//Target API
	nRet = i18n_plural_rules_is_keyword(g_plural_rules, szKeyword, &bKeyword);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_is_keyword", BaseUtilsGetError(nRet));
	if (bKeyword != true)
	{
		FPRINTF("\\n[Line : %d][%s] keyword is false\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: get other keyword
/**
 * @testcase				ITc_i18n_plural_rules_get_keyword_other_p
 * @since_tizen 			4.0
 * @author            	SRID(manoj.g2)
 * @reviewer         	SRID(shobhit.v)
 * @type 				auto
 * @scenario				- get other keyword
 * @apitarget			i18n_plural_rules_get_keyword_other
 * @apicovered			i18n_plural_rules_get_keyword_other
 * @passcase				I18N_ERROR_NONE returned by ii18n_plural_rules_get_keyword_other
 * @failcase				I18N_ERROR_NONE not returned by ii18n_plural_rules_get_keyword_other or pre-condition APIs fail
 * @precondition			NA
 * @postcondition		NA
 */
int ITc_i18n_plural_rules_get_keyword_other_p(void)
{
	START_TEST;

	int nRet = -1;
	const char *szOutputValue = "other";
	i18n_uchar buffer[BUFFER] = { 0 };
	int output_length = -1;
	char output_buffer[BUFFER] = { 0 };

	//Target API
	nRet = i18n_plural_rules_get_keyword_other(g_plural_rules, BUFFER, buffer, &output_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_get_keyword_other", BaseUtilsGetError(nRet));
	i18n_ustring_copy_au_n(output_buffer, buffer, BUFFER);

	if (strncmp(output_buffer, szOutputValue, strlen(szOutputValue)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and buffer string %s is not same\\n", __LINE__, API_NAMESPACE, szOutputValue, output_buffer);
		return 1;
	}

	if(output_length != strlen(szOutputValue) )
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, output_length, strlen(szOutputValue));
		return 1;
	}

	return 0;
}


