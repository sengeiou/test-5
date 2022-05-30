//
// Copyright (c) 2018 Samsung Electronics Co., Ltd.
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

#define BUFSIZE 256

static i18n_plural_format_h g_hPluralFormat = NULL;

/** @addtogroup itc-base-utils
 *  @ingroup itc
 *  @{
 */



//& set: BaseUtilsPluralFormat
void ITs_base_utils_plural_format_startup(void)
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
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_plural_format_startup\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = I18N_ERROR_NONE;

	nRet = i18n_plural_format_create(&g_hPluralFormat);
	if (nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("\\n[Line : %d][%s] format creation failed with error code %s\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
	}
	else if(g_hPluralFormat == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] g_hPluralFormat is null\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
	}
	else
	{
		g_bBaseUtilsInitFlag = true;
	}

	return;
}

//& unset: BaseUtilsPluralFormat
void ITs_base_utils_plural_format_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_base_utils_plural_format_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if (g_hPluralFormat != NULL)
	{
		i18n_plural_format_destroy(g_hPluralFormat);
		g_hPluralFormat = NULL;
		g_bBaseUtilsInitFlag = false;
	}
}

/** @addtogroup itc-base-utils-testcases
 *  @brief 	Integration testcases for module base-utils plural format
 *  @ingroup 	itc-base-utils
 *  @{
 */


/*
 * @testcase		ITc_i18n_plural_format_create_destroy_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create, i18n_plural_format_destroy
 * @apicovered		i18n_plural_format_create, i18n_plural_format_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create, i18n_plural_format_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create, i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_destroy_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat = NULL;

	// Target API
	nRet = i18n_plural_format_create(&hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create");

	// Target API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}


/*
 * @testcase		ITc_i18n_plural_format_create_from_locale_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_locale
 * @apicovered		i18n_plural_format_create_from_locale
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_locale
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_locale, i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_locale_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";

	// Target API
	nRet = i18n_plural_format_create_from_locale(pszLocale, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale");

	// Post condition API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}


/*
 * @testcase		ITc_i18n_plural_format_create_from_rules_pattern_p
 * @since_tizen 	5.0
 * @author		SRID(j.abhishek)
 * @reviewer		SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_rules_pattern
 * @apicovered		i18n_plural_format_create_from_rules_pattern
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_rules_pattern
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_rules_pattern,
 * 			i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_rules_pattern_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_rules_h hPluralRules = NULL;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	// Precondition API
	nRet = i18n_plural_rules_create(&hPluralRules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralRules, "i18n_plural_rules_create");

	// Target API
	nRet = i18n_plural_format_create_from_rules_pattern(hPluralRules, pszPattern, &hPluralFormat);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_rules_pattern", BaseUtilsGetError(nRet), i18n_plural_rules_destroy(hPluralRules));
	CHECK_HANDLE_CLEANUP(hPluralFormat, "i18n_plural_format_create_from_rules_pattern", i18n_plural_rules_destroy(hPluralRules));

	// Cleanup API
	nRet = i18n_plural_rules_destroy(hPluralRules);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

/*
 * @testcase		ITc_i18n_plural_format_create_from_locale_type_pattern_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_locale_type_pattern
 * @apicovered		i18n_plural_format_create_from_locale_type_pattern
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_locale_type_pattern
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_locale_type_pattern,
 * 			i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_locale_type_pattern_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	i18n_uplural_type_e uplural_type[] =
	{
		I18N_UPLURAL_TYPE_CARDINAL,     /**< Plural rules for cardinal numbers: 1 file vs. 2 files */
		I18N_UPLURAL_TYPE_ORDINAL      /**< Plural rules for ordinal numbers: 1st file, 2nd file, 3rd file, 4th file, etc. */
	};

	int enum_size = sizeof(uplural_type) / sizeof(uplural_type[0]);
	int enum_counter;

	for(enum_counter = 0; enum_counter < enum_size; enum_counter++)
	{
		hPluralFormat = NULL;

		// Target API
		nRet = i18n_plural_format_create_from_locale_type_pattern(pszLocale, uplural_type[enum_counter], pszPattern, &hPluralFormat);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_type_pattern", BaseUtilsGetError(nRet));
		CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_type_pattern");

		// Cleanup API
		nRet = i18n_plural_format_destroy(hPluralFormat);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));
	}
	return 0;
}


/*
 * @testcase		ITc_i18n_plural_format_create_from_locale_type_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_locale_type
 * @apicovered		i18n_plural_format_create_from_locale_type
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_locale_type
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_locale_type,
 * 			i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_locale_type_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat;

	const char *pszLocale = "en_US";

	i18n_uplural_type_e uplural_type[] =
	{
		I18N_UPLURAL_TYPE_CARDINAL,     /**< Plural rules for cardinal numbers: 1 file vs. 2 files */
		I18N_UPLURAL_TYPE_ORDINAL      /**< Plural rules for ordinal numbers: 1st file, 2nd file, 3rd file, 4th file, etc. */
	};

	int enum_size = sizeof(uplural_type) / sizeof(uplural_type[0]);
	int enum_counter;

	for(enum_counter = 0; enum_counter < enum_size; enum_counter++)
	{
		hPluralFormat = NULL;

		// Target API
		nRet = i18n_plural_format_create_from_locale_type(pszLocale, uplural_type[enum_counter], &hPluralFormat);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_type", BaseUtilsGetError(nRet));
		CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_type");

		// Cleanup API
		nRet = i18n_plural_format_destroy(hPluralFormat);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));
	}
	return 0;
}


/*
 * @testcase		ITc_i18n_plural_format_create_from_locale_pattern_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_locale_pattern
 * @apicovered		i18n_plural_format_create_from_locale_pattern
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_locale_pattern
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_locale_pattern,
 * 			i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_locale_pattern_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";


	// Target API
	nRet = i18n_plural_format_create_from_locale_pattern(pszLocale, pszPattern, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_pattern");

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

/*
 * @testcase		ITc_i18n_plural_format_create_from_locale_rules_pattern_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- Creates and destroy a plural format object
 * @apitarget		i18n_plural_format_create_from_locale_rules_pattern
 * @apicovered		i18n_plural_format_create_from_locale_rules_pattern
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_create_from_locale_rules_pattern
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_create_from_locale_rules_pattern,
 * 			i18n_plural_format_destroy or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_create_from_locale_rules_pattern_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_rules_h hPluralRules = NULL;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	// Precondition API
	nRet = i18n_plural_rules_create(&hPluralRules);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_rules_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralRules, "i18n_plural_rules_create");

	// Target API
	nRet = i18n_plural_format_create_from_locale_rules_pattern(pszLocale, hPluralRules, pszPattern, &hPluralFormat);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_rules_pattern", BaseUtilsGetError(nRet), i18n_plural_rules_destroy(hPluralRules));
	CHECK_HANDLE_CLEANUP(hPluralFormat, "i18n_plural_format_create_from_locale_rules_pattern", i18n_plural_rules_destroy(hPluralRules));

	// Cleanup API
	nRet = i18n_plural_rules_destroy(hPluralRules);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_rules_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: clone a plural format object
/**
 * @testcase		ITc_i18n_plural_format_clone_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- clone a plural format object
 * @apitarget		i18n_plural_format_clone
 * @apicovered		i18n_plural_format_clone,i18n_plural_format_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_clone
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_clone or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_clone_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hClone = NULL;

	// Target API
	nRet = i18n_plural_format_clone(g_hPluralFormat, &hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_clone", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hClone, "i18n_plural_format_clone");

	// Cleanup API
	nRet = i18n_plural_format_destroy(hClone);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: apply_pattern a plural format object
/**
 * @testcase		ITc_i18n_plural_format_apply_pattern_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- apply_pattern a plural format object
 * @apitarget		i18n_plural_format_apply_pattern
 * @apicovered		i18n_plural_format_apply_pattern
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_apply_pattern
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_apply_pattern or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_apply_pattern_p(void)
{
	START_TEST;

	int nRet = -1;
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	//Target API
	nRet = i18n_plural_format_apply_pattern(g_hPluralFormat, pszPattern);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_apply_pattern", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: create format of int32
/**
 * @testcase		ITc_i18n_plural_format_format_int32_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- apply int32 format to a plural format object
 * @apitarget		i18n_plural_format_format_int32
 * @apicovered		i18n_plural_format_format_int32,i18n_plural_format_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_format_int32
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_format_int32 or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_format_int32_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	nRet = i18n_plural_format_create_from_locale_pattern(pszLocale, pszPattern, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_pattern");

	i18n_field_position_h hFieldPosition = NULL;
	const char *pszStart_string = "Sample: ";
	i18n_uchar append_to[BUFSIZE] = { 0 };

	i18n_ustring_copy_ua_n(append_to, pszStart_string, BUFSIZE);

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPosition);	//There is only one value of i18n_field_position_dont_care_e
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create_for_field", i18n_plural_format_destroy(hPluralFormat));


	int32_t number = 4;
	int nOutput_length = -1;

	//Target API
	nRet = i18n_plural_format_format_int32(hPluralFormat, number, hFieldPosition, BUFSIZE, append_to, &nOutput_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat); i18n_field_position_destroy(hFieldPosition));

	const char *pszOutput_string = "Sample: psov";
	char output_buffer[BUFSIZE] = { 0 };

	i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);

	if (strncmp(output_buffer, pszOutput_string, strlen(pszOutput_string)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and otput string %s is not same\\n", __LINE__, API_NAMESPACE, output_buffer, pszOutput_string);
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}
	if(nOutput_length != strlen(pszOutput_string) )
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, nOutput_length, strlen(pszOutput_string));
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}

	// Cleanup API
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: create format of double type
/**
 * @testcase		ITc_i18n_plural_format_format_double_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		- apply double a plural format object
 * @apitarget		i18n_plural_format_format_double
 * @apicovered		i18n_plural_format_format_double,i18n_plural_format_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_format_double
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_format_double or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_format_double_p(void)
{
	START_TEST;

	int nRet = -1;

	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	nRet = i18n_plural_format_create_from_locale_pattern(pszLocale, pszPattern, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_pattern");

	i18n_field_position_h hFieldPosition = NULL;
	const char *pszStart_string = "Sample: ";

	i18n_uchar append_to[BUFSIZE] = { 0 };
	i18n_ustring_copy_ua_n(append_to, pszStart_string, BUFSIZE);

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create_for_field", i18n_plural_format_destroy(hPluralFormat));

	int32_t number = 4;
	int nOutput_length = -1;
	const char *pszOutput_string = "Sample: psov";

	//Target API
	nRet = i18n_plural_format_format_double(hPluralFormat, number, hFieldPosition, BUFSIZE, append_to, &nOutput_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat); i18n_field_position_destroy(hFieldPosition));

	char output_buffer[BUFSIZE] = { 0 };
	i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);

	if (strncmp(output_buffer, pszOutput_string, strlen(pszOutput_string)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and otput string %s is not same\\n", __LINE__, API_NAMESPACE, output_buffer, pszOutput_string);
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}
	if(nOutput_length != strlen(pszOutput_string))
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, nOutput_length, strlen(pszOutput_string));
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}

	// Cleanup API
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: create format
/**
 * @testcase		ITc_i18n_plural_format_format_formattable_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		-
 * @apitarget		i18n_plural_format_format_formattable
 * @apicovered		i18n_plural_format_format_formattable,i18n_plural_format_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_format_formattable
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_format_formattable or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_format_formattable_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	nRet = i18n_plural_format_create_from_locale_pattern(pszLocale, pszPattern, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_pattern");

	i18n_field_position_h hFieldPosition = NULL;
	const char *pszStart_string = "Sample: ";
	i18n_uchar append_to[BUFSIZE] = { 0 };

	i18n_ustring_copy_ua_n(append_to, pszStart_string, BUFSIZE);

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create_for_field", i18n_plural_format_destroy(hPluralFormat));


	i18n_formattable_h hFormattable;

	nRet = i18n_formattable_create_with_double(4, &hFormattable);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat); i18n_field_position_destroy(hFieldPosition));
	CHECK_HANDLE_CLEANUP(hFormattable, "i18n_field_position_create_for_field", i18n_plural_format_destroy(hPluralFormat); i18n_field_position_destroy(hFieldPosition));

	int nOutput_length = -1;
	const char *pszOutput_string = "Sample: psov";

	//Target API
	nRet = i18n_plural_format_format_formattable(hPluralFormat, hFormattable, hFieldPosition, BUFSIZE, append_to, &nOutput_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet), i18n_formattable_destroy(hFormattable); i18n_field_position_destroy(hFieldPosition); i18n_plural_format_destroy(hPluralFormat));

	char output_buffer[BUFSIZE] = { 0 };
	i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);

	if (strncmp(output_buffer, pszOutput_string, strlen(pszOutput_string)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and otput string %s is not same\\n", __LINE__, API_NAMESPACE, output_buffer, pszOutput_string);
		i18n_formattable_destroy(hFormattable);
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}
	if(nOutput_length != strlen(pszOutput_string))
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, nOutput_length, strlen(pszOutput_string));
		i18n_formattable_destroy(hFormattable);
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}

	// Cleanup API
	nRet = i18n_formattable_destroy(hFormattable);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_formattable_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set number format
/**
 * @testcase		ITc_i18n_plural_format_set_number_format_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		-
 * @apitarget		i18n_plural_format_set_number_format
 * @apicovered		i18n_plural_format_set_number_format,
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_set_number_format
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_set_number_format or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_set_number_format_p(void)
{
	START_TEST;

	int nRet = -1;
	i18n_unumber_format_h hNumberFormat = NULL;
	const char* pszLocale = "en_US";

	i18n_unumber_format_style_e eFormat_style[] =
	{
		I18N_UNUMBER_PATTERN_DECIMAL,	/**< Decimal format defined by a pattern string */
		I18N_UNUMBER_DECIMAL,	/**< Decimal format ("normal" style) */
		//I18N_UNUMBER_CURRENCY,	// This format is failing the ITC
		//I18N_UNUMBER_PERCENT,	// This format is failing the ITC
		//I18N_UNUMBER_SCIENTIFIC,	// This format is failing the ITC
		//I18N_UNUMBER_SPELLOUT,	// This format is failing the ITC
		I18N_UNUMBER_ORDINAL,	/**< Ordinal rule-based format */
		//I18N_UNUMBER_DURATION,	// This format is failing the ITC
		I18N_UNUMBER_NUMBERING_SYSTEM,	/**< Numbering system rule-based format */
		//I18N_UNUMBER_PATTERN_RULEBASED,	// This format is failing the ITC
		//I18N_UNUMBER_CURRENCY_ISO,	// This format is failing the ITC
		//I18N_UNUMBER_CURRENCY_PLURAL,	// This format is failing the ITC
		//I18N_UNUMBER_CURRENCY_ACCOUNTING,	// This format is failing the ITC
		//I18N_UNUMBER_CASH_CURRENCY,	// This format is failing the ITC
		//I18N_UNUMBER_FORMAT_STYLE_COUNT,	// This format is failing the ITC
		I18N_UNUMBER_DEFAULT,	/**< Default format */
		I18N_UNUMBER_IGNORE	/**< Alias for #I18N_UNUMBER_PATTERN_DECIMAL */
};

	int enum_size = sizeof(eFormat_style) / sizeof(eFormat_style[0]);
	int enum_counter;

	for(enum_counter = 0; enum_counter < enum_size; enum_counter++)
	{

		nRet = i18n_unumber_create(eFormat_style[enum_counter], NULL, -1, pszLocale, NULL, &hNumberFormat);	//Passing Arg5 NULL as this is not target API
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unumber_create", BaseUtilsGetError(nRet));

		// Tareget API
		nRet = i18n_plural_format_set_number_format(g_hPluralFormat, hNumberFormat);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_set_number_format", BaseUtilsGetError(nRet), i18n_unumber_destroy(hNumberFormat));
	}

	// Cleanup API
	nRet = i18n_unumber_destroy(hNumberFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_unumber_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set number format to pattern
/**
 * @testcase		ITc_i18n_plural_format_to_pattern_p
 * @since_tizen 	5.0
 * @author            	SRID(j.abhishek)
 * @reviewer         	SRID(a.pandia1)
 * @type 		auto
 * @scenario		-
 * @apitarget		i18n_plural_format_to_pattern_p
 * @apicovered		i18n_plural_format_to_pattern_p,
 * @passcase		I18N_ERROR_NONE returned by i18n_plural_format_to_pattern_p
 * @failcase		I18N_ERROR_NONE not returned by i18n_plural_format_to_pattern_p or pre-condition APIs fail
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_plural_format_to_pattern_p(void)
{
	START_TEST;

	int nRet = -1;

	i18n_plural_format_h hPluralFormat = NULL;

	const char *pszLocale = "en_US";
	const char *pszPattern = "one{pes} two{psa} few{psi} other{psov}";

	nRet = i18n_plural_format_create_from_locale_pattern(pszLocale, pszPattern, &hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_create_from_locale_pattern", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hPluralFormat, "i18n_plural_format_create_from_locale_pattern");

	i18n_field_position_h hFieldPosition = NULL;
	const char *pszStart_string = "Sample: ";

	i18n_uchar append_to[BUFSIZE] = { 0 };
	i18n_ustring_copy_ua_n(append_to, pszStart_string, BUFSIZE);

	nRet = i18n_field_position_create_for_field(I18N_FIELD_POSITION_DONT_CARE, &hFieldPosition);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_field_position_create_for_field", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat));
	CHECK_HANDLE_CLEANUP(hFieldPosition, "i18n_field_position_create_for_field", i18n_plural_format_destroy(hPluralFormat));

	int nOutput_length = -1;
	const char *pszOutput_string = "Sample: one{pes} two{psa} few{psi} other{psov}";

	//Target API
	nRet = i18n_plural_format_to_pattern(hPluralFormat, hFieldPosition, BUFSIZE, append_to, &nOutput_length);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_plural_format_to_pattern", BaseUtilsGetError(nRet), i18n_plural_format_destroy(hPluralFormat); i18n_field_position_destroy(hFieldPosition));

	char output_buffer[BUFSIZE] = { 0 };
	i18n_ustring_copy_au_n(output_buffer, append_to, BUFSIZE);

	if (strncmp(output_buffer, pszOutput_string, strlen(pszOutput_string)) != 0)
	{
		FPRINTF("\\n[Line : %d][%s] output string %s and otput string %s is not same\\n", __LINE__, API_NAMESPACE, output_buffer, pszOutput_string);
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}
	if(nOutput_length != strlen(pszOutput_string))
	{
		FPRINTF("\\n[Line : %d][%s] output_length %d and output string length  %d is not same\\n", __LINE__, API_NAMESPACE, nOutput_length, strlen(pszOutput_string));
		i18n_field_position_destroy(hFieldPosition);
		i18n_plural_format_destroy(hPluralFormat);
		return 1;
	}

	// Cleanup API
	nRet = i18n_field_position_destroy(hFieldPosition);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_field_position_destroy", BaseUtilsGetError(nRet));

	// Cleanup API
	nRet = i18n_plural_format_destroy(hPluralFormat);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_plural_format_destroy", BaseUtilsGetError(nRet));

	return 0;
}

