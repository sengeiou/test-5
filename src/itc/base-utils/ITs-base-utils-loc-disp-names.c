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
#include "ITs-base-utils-loc-disp-names.h"

i18n_loc_disp_names_h g_hLocDisp = NULL;
bool g_hLocDispHandleCreated;
const char *g_pszLanguage = "en";
const char *g_pszScript = "Hant";
const char *g_pszRegion = "US";
const char *g_pszVariant = "PRE_EURO";
const char *g_pszKey = "calendar";
const char *g_pszValue = "gregorian";
char * g_pszName = NULL;

void ITs_base_utils_loc_disp_names_startup(void)
{
	g_hLocDispHandleCreated = false;
	int nRet = i18n_loc_disp_names_create(g_pszLocale, &g_hLocDisp);
	if(nRet != I18N_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] g_hLocDisp handle creation failed. nRet = %d \\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
		return;
	}
	if(g_hLocDisp == NULL)
	{
		FPRINTF("[Line : %d][%s] g_hLocDisp handle creation failed. \\n", __LINE__, API_NAMESPACE);
		return;
	}
	g_hLocDispHandleCreated = true;
	FPRINTF("[Line : %d][%s] g_hLocDisp handle created successfully. \\n", __LINE__, API_NAMESPACE);
	return;
}

void ITs_base_utils_loc_disp_names_cleanup(void)
{
	if(g_hLocDisp != NULL)
	{
		int nRet =i18n_loc_disp_names_destroy(g_hLocDisp);
		FPRINTF("[Line : %d][%s] g_hLocDisp handle destroy failed. \\n", __LINE__, API_NAMESPACE);
		g_hLocDisp = NULL;
	}
	return;
}
// & type: auto
// & purpose: Creates a default locale display names object.
/**
* @testcas			ITs_base_utils_i18n_loc_disp_names_create_p
* @since_tizen 			5.0
* @author            		SRID(awadhesh1.s)
* @reviewer         		SRID(nibha.sharma)
* @type 			auto
* @scenario			Creates a default locale display names object.
* @apitarget			i18n_loc_disp_names_create
* @apicovered			i18n_loc_disp_names_create, i18n_loc_disp_names_destroy
* @passcase			return 0 and locale display object created.
* @failcase			Negative value return
* @precondition			NA
* @postcondition		NA
*/
int ITs_base_utils_i18n_loc_disp_names_create_p(void)
{
	START_LOCALE_DISP_TEST

	i18n_loc_disp_names_h hLocDisp =  NULL;
	const char * pszLocale[] = {"en_US","en_GB","zh_TW","ko_KR", "ja_JP", "it_IT", "de_DE", "fr_FR", "zh_CN", "fr_CA", "en_CA","zh_CN","ko","ja","it","de","fr","en","zh"};
	char * pszDummy = NULL;
	int nLocaleOption = sizeof(pszLocale) / sizeof(pszDummy);
	int nCounter;
	bool bLocaleFail = false;

	for(nCounter = 0; nCounter < nLocaleOption; nCounter++ )
	{
		int nRet = i18n_loc_disp_names_create(pszLocale[nCounter], &hLocDisp);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_create", BaseUtilsGetError(nRet));

		if(hLocDisp == NULL)
		{
			FPRINTF("[Line : %d][%s] hLocDisp handle creation failed. Locale = %s \\n", __LINE__, API_NAMESPACE, pszLocale[nCounter]);
			bLocaleFail = true;
		}
		else
		{
			nRet =i18n_loc_disp_names_destroy(hLocDisp);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_destroy", BaseUtilsGetError(nRet));
			hLocDisp = NULL;
		}
	}
	if(bLocaleFail)
	{
		return 1;
	}
	return 0;
}
// & type: auto
// & purpose: Creates a locale display names object for the given dialect handling.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_create_from_dialect_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Creates a locale display names object for the given dialect handling..
* @apitarget                    i18n_loc_disp_names_create_from_dialect
* @apicovered                   i18n_loc_disp_names_create_from_dialect, i18n_loc_disp_names_destroy
* @passcase                     return 0 and locale display object created.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/

int ITs_base_utils_i18n_loc_disp_names_create_from_dialect_p(void)
{
	START_LOCALE_DISP_TEST

	i18n_loc_disp_names_h hLocDisp =  NULL;
	i18n_udialect_handling_e eDialect[] = {I18N_ULDN_STANDARD_NAMES, I18N_ULDN_DIALECT_NAMES};
	int nEnumSize = sizeof(eDialect) / sizeof(eDialect[0]);
	int nCounter = 0;
	bool bLocaleFail = false;

	for(nCounter = 0; nCounter < nEnumSize ; nCounter++ )
	{
		int nRet = i18n_loc_disp_names_create_from_dialect(g_pszLocale, eDialect[nCounter], &hLocDisp);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_create_from_dialect", BaseUtilsGetError(nRet));
		if(hLocDisp == NULL)
		{
			FPRINTF("[Line : %d][%s] hLocDisp handle creation failed. dialect = %d. \\n", __LINE__, API_NAMESPACE,eDialect[nCounter]);
			bLocaleFail = true;
		}
		else
		{
			nRet =i18n_loc_disp_names_destroy(hLocDisp);
			PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_destroy", BaseUtilsGetError(nRet));
			hLocDisp = NULL;
		}
	}
	if(bLocaleFail)
	{
		return 1;
	}
	return 0;
}
// & type: auto
// & purpose: Creates a locale display names object for given display contexts.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_create_from_context_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Creates a default locale display names object.
* @apitarget                    i18n_loc_disp_names_create_from_context
* @apicovered                   i18n_loc_disp_names_create_from_context, i18n_loc_disp_names_destroy
* @passcase                     return 0 and locale display object created.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_create_from_context_p(void)
{
	START_LOCALE_DISP_TEST

	i18n_loc_disp_names_h hLocDisp =  NULL;
	i18n_udisplay_context_e eContexts[] = {I18N_UDISPLAY_CONTEXT_STANDARD_NAMES, I18N_UDISPLAY_CONTEXT_CAPITALIZATION_FOR_UI_LIST_OR_MENU };
	int nEnumSize = sizeof(eContexts) / sizeof(eContexts[0]);
	int nCounter = 0;

	int nRet = i18n_loc_disp_names_create_from_context(g_pszLocale, eContexts, nEnumSize, &hLocDisp);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_create_from_context", BaseUtilsGetError(nRet));
	if(hLocDisp == NULL)
	{
		FPRINTF("[Line : %d][%s] hLocDisp handle creation failed. \\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRet =i18n_loc_disp_names_destroy(hLocDisp);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_destroy", BaseUtilsGetError(nRet));
	hLocDisp = NULL;

	return 0;
}
// & type: auto
// & purpose: Gets the locale used by the given locale display names object to determinate the display names.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_locale_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the locale used by the given locale display.
				names object to determinate the display names.
* @apitarget                    i18n_loc_disp_names_get_locale
* @apicovered                   i18n_loc_disp_names_get_locale
* @passcase                     return 0 and locale display.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_locale_p(void)
{
	START_LOCALE_DISP_TEST

	char * pszOutput =  NULL;
	const char * pszExpected = "en_US";
	int nRet = i18n_loc_disp_names_get_locale(g_hLocDisp, &pszOutput);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_locale", BaseUtilsGetError(nRet));

	if(strncmp(pszOutput, pszExpected, strlen(pszExpected)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_locale mismatch pszOutput = %s. \\n", __LINE__, API_NAMESPACE,pszOutput);
		FREE_MEMORY(pszOutput);
		return 1;
	}
	FREE_MEMORY(pszOutput);
	return 0;
}
// & type: auto
// & purpose: Gets the dialect handling used by the given locale display names object.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_dialect_handling_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the dialect handling used by the given locale display names object.
* @apitarget                    i18n_loc_disp_names_get_dialect_handling
* @apicovered                   i18n_loc_disp_names_get_dialect_handling
* @passcase                     return 0 and dialect handle.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_dialect_handling_p(void)
{
	START_LOCALE_DISP_TEST

	i18n_udialect_handling_e eDialect;

	int nRet = i18n_loc_disp_names_get_dialect_handling(g_hLocDisp, &eDialect);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_locale", BaseUtilsGetError(nRet));

	if(eDialect != I18N_ULDN_STANDARD_NAMES && eDialect != I18N_ULDN_DIALECT_NAMES)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_dialect_handling mismatch eDialect = %d. \\n", __LINE__, API_NAMESPACE, eDialect);
                return 1;
	}
	return 0;
}

// & type: auto
// & purpose:Gets the context from the given locale display names object.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_context_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the context from the given locale display names object.
* @apitarget                    i18n_loc_disp_names_get_context
* @apicovered                   i18n_loc_disp_names_get_context
* @passcase                     return 0 and context.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_context_p(void)
{
	START_LOCALE_DISP_TEST
	i18n_udisplay_context_type_e eType[] = { I18N_UDISPCTX_TYPE_DIALECT_HANDLING, I18N_UDISPCTX_TYPE_CAPITALIZATION,
	#ifndef U_HIDE_DRAFT_API
	I18N_UDISPCTX_TYPE_DISPLAY_LENGTH
	#endif
	};
	int nEnumSize = sizeof(eType) / sizeof(eType[0]);
	int nCounter = 0;
	bool bContext =  false;

	for(nCounter = 0 ; nCounter < nEnumSize ; nCounter++ )
	{
		i18n_udisplay_context_e eContext = 0;

		int nRet = i18n_loc_disp_names_get_context(g_hLocDisp, eType[nCounter], &eContext);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_context", BaseUtilsGetError(nRet));

		if( !(eContext == (eType[nCounter] << 8 + 0) || eContext == (eType[nCounter] << 8 + 1) || eContext == (eType[nCounter]<< 8 + 2) || eContext == (eType[nCounter] << 8 + 3) || eContext == (eType[nCounter]<< 8 + 4) ))
		{
			FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_context mismatch. eContext = %d. \\n", __LINE__, API_NAMESPACE, eContext);
			bContext = true;
		}
	}
	if(bContext)
	{
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose:Gets the display name of the provided locale.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_loc_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided locale.
* @apitarget                    i18n_loc_disp_names_get_loc_disp_name
* @apicovered                   i18n_loc_disp_names_get_loc_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_loc_disp_name_p(void)
{
	START_LOCALE_DISP_TEST

	const char *pszExpected = "English (United States)";

	int nRet = i18n_loc_disp_names_get_loc_disp_name(g_hLocDisp, g_pszLocale, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_loc_disp_name", BaseUtilsGetError(nRet));

	if( strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0 )
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_loc_disp_name mismatch. pszExpected = %s , g_pszName =. \\n", __LINE__, API_NAMESPACE, pszExpected, g_pszName);
		FREE_MEMORY(g_pszName);
		return 1;
	}
	FREE_MEMORY(g_pszName);
	return 0;
}

// & type: auto
// & purpose: Gets the display name of the provided language code.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_language_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided language code.
* @apitarget                    i18n_loc_disp_names_get_language_disp_name
* @apicovered                   i18n_loc_disp_names_get_language_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/

int ITs_base_utils_i18n_loc_disp_names_get_language_disp_name_p(void)
{
	START_LOCALE_DISP_TEST
	const char *pszExpected = "English";

	int nRet = i18n_loc_disp_names_get_language_disp_name(g_hLocDisp, g_pszLanguage, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_language_disp_name", BaseUtilsGetError(nRet));

	if(strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_language_disp_name mismatchi. pszExpected = %s, _pszName = %s. \\n", __LINE__, API_NAMESPACE, pszExpected, g_pszName);
		FREE_MEMORY(g_pszName);
		return 1;
	}
	FREE_MEMORY(g_pszName);
	return 0;
}

// & type: auto
// & purpose: Gets the display name of the script code provided as string.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the script code provided as string.
* @apitarget                    i18n_loc_disp_names_get_script_disp_name
* @apicovered                   i18n_loc_disp_names_get_script_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_p(void)
{
	START_LOCALE_DISP_TEST
	const char *pszExpected = "Traditional";

	int nRet = i18n_loc_disp_names_get_script_disp_name(g_hLocDisp, g_pszScript, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_language_disp_name", BaseUtilsGetError(nRet));

	if(strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_script_disp_name mismatch. pszExpected = %s, g_pszName = %s \\n", __LINE__, API_NAMESPACE, pszExpected, g_pszName);
		FREE_MEMORY(g_pszName);
		return 1;
	}
	FREE_MEMORY(g_pszName);
	return 0;
}

// & type: auto
// & purpose: Gets the display name of the script code provided as enumeration.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the script code provided as string.
* @apitarget                    i18n_loc_disp_names_get_script_disp_name_with_script_code
* @apicovered                   i18n_loc_disp_names_get_script_disp_name_with_script_code
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_script_disp_name_with_script_code_p(void)
{
	START_LOCALE_DISP_TEST
	int nScriptCodeUpLimit = sizeof(g_eScriptCode)/ sizeof(g_eScriptCode[0]);
	int nCounter;
	bool bMisMatch = false;
	for(nCounter = 0 ; nCounter < nScriptCodeUpLimit ; nCounter++)
	{
		int nRet = i18n_loc_disp_names_get_script_disp_name_with_script_code(g_hLocDisp, g_eScriptCode[nCounter], &g_pszName);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_language_disp_name", BaseUtilsGetError(nRet));

		if(g_pszName == NULL)
		{
			FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_script_disp_name_with_script_code mismatch. nScriptCode = %d , g_pszName = %s \\n", __LINE__, API_NAMESPACE, g_eScriptCode[nCounter], &g_pszName);
			bMisMatch = true;
		}
		else
		{
			FREE_MEMORY(g_pszName);
		}
	}
	if(bMisMatch)
	{
		return 1;
	}
	return 0;

}
// & type: auto
// & purpose: Gets the display name of the provided region code.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_region_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided region code.
* @apitarget                    i18n_loc_disp_names_get_region_disp_name
* @apicovered                   i18n_loc_disp_names_get_region_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_region_disp_name_p(void)
{
	START_LOCALE_DISP_TEST

	const char *pszExpected[] = {"United States", "United Kingdom", "Taiwan", "South Korea", "Japan", "Italy", "Germany", "France","China", "Canada"};
	const char *pszRegion[] = {"US","GB","TW","KR", "JP", "IT", "DE", "FR", "CN", "CA"};
	char * pszDummy = NULL;
	int nEnumSize = sizeof(pszRegion) / sizeof(pszDummy) ;
	int nCounter;
	int nRet;
	bool bMisMatch = false;
	for(nCounter = 0; nCounter < nEnumSize ; nCounter++)
	{
		nRet = i18n_loc_disp_names_get_region_disp_name(g_hLocDisp, pszRegion[nCounter], &g_pszName);
		PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_region_disp_name", BaseUtilsGetError(nRet));

		if(strncmp(pszExpected[nCounter], g_pszName, strlen(pszExpected[nCounter])) != 0)
		{
			FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_region_disp_name mismatch. pszExpected = %s , pszName = %s \\n", __LINE__, API_NAMESPACE, pszExpected[nCounter], g_pszName);
			FREE_MEMORY(g_pszName);
			bMisMatch = true;
		}
	}
	if(bMisMatch)
	{
		return 1;
	}
	FREE_MEMORY(g_pszName);
	return 0;
}

// & type: auto
// & purpose:Gets the display name of the provided variant.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_variant_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided variant.
* @apitarget                    i18n_loc_disp_names_get_variant_disp_name
* @apicovered                   i18n_loc_disp_names_get_variant_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_variant_disp_name_p(void)
{
	START_LOCALE_DISP_TEST
	const char *pszExpected = "PRE_EURO";

	int nRet = i18n_loc_disp_names_get_variant_disp_name(g_hLocDisp, g_pszVariant, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_variant_disp_name", BaseUtilsGetError(nRet));

	if(strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_variant_disp_name mismatch. pszExpected = %s, g_pszName = %s\\n", __LINE__, API_NAMESPACE, pszExpected, g_pszName);
		FREE_MEMORY(g_pszName);
		return 1;
	}

	FREE_MEMORY(g_pszName);
	return 0;
}

// & type: auto
// & purpose:Gets the display name of the provided locale key.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_key_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided locale key.
* @apitarget                    i18n_loc_disp_names_get_key_disp_name
* @apicovered                   i18n_loc_disp_names_get_key_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_key_disp_name_p(void)
{
	START_LOCALE_DISP_TEST
	const char *pszExpected = "Calendar";

	int nRet = i18n_loc_disp_names_get_key_disp_name(g_hLocDisp, g_pszKey, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_key_disp_name", BaseUtilsGetError(nRet));

	if(strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_key_disp_name mismatch. pszExpected = %s \\n", __LINE__, API_NAMESPACE, pszExpected);
		FREE_MEMORY(g_pszName);
		return 1;
	}

	FREE_MEMORY(g_pszName);
	return 0;
}
// & type: auto
// & purpose:Gets the display name of the provided locale key-value.
/**
* @testcas                      ITs_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p
* @since_tizen                  5.0
* @author                       SRID(awadhesh1.s)
* @reviewer                     SRID(nibha.sharma)
* @type                         auto
* @scenario                     Gets the display name of the provided locale keyvalue.
* @apitarget                    i18n_loc_disp_names_get_key_value_disp_name
* @apicovered                   i18n_loc_disp_names_get_key_value_disp_name
* @passcase                     return 0 and display name.
* @failcase                     Negative value return
* @precondition                 NA
* @postcondition                NA
*/
int ITs_base_utils_i18n_loc_disp_names_get_key_value_disp_name_p(void)
{

	START_LOCALE_DISP_TEST

	const char *pszExpected = "Gregorian Calendar";
	int nRet = i18n_loc_disp_names_get_key_value_disp_name(g_hLocDisp, g_pszKey, g_pszValue, &g_pszName);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_loc_disp_names_get_key_value_disp_name", BaseUtilsGetError(nRet));

	if(strncmp(pszExpected, g_pszName, strlen(pszExpected)) != 0)
	{
	FPRINTF("[Line : %d][%s] i18n_loc_disp_names_get_key_value_disp_name mismatch.  pszExpected =  %s , g_pszName = %s \\n", __LINE__, API_NAMESPACE, pszExpected ,g_pszName);
		FREE_MEMORY(g_pszName);
		return 1;
	}

	FREE_MEMORY(g_pszName);
	return 0;
}
