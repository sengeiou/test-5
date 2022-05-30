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

#define L I18N_UCHAR_U_LEFT_TO_RIGHT
#define R I18N_UCHAR_U_RIGHT_TO_LEFT

static i18n_ubidi_h g_hUbidi = NULL;
static i18n_uchar *g_pszUcharSrc = NULL;
static i18n_uchar *g_pszUcharDest = NULL;
static int32_t g_nSrcLength = -1;
static int32_t g_nDestLength = -1;

/*********************************Callback Started*****************************/
static i18n_uchar_direction_e NewClassCB(const void* context, i18n_uchar32 c)
{
	i18n_uchar_direction_e custom_classes[] = {
			R, R, R, R, R, R, R, R,
			L, L, L, L, L, L, L, L
			};

	return c >= 16 ? I18N_UBIDI_CLASS_DEFAULT : custom_classes[c];
}

static i18n_uchar_direction_e OldClassCB(const void* context, i18n_uchar32 c)
{
	i18n_uchar_direction_e custom_classes[] = {
		R, L
		};

	return c >= 2 ? I18N_UBIDI_CLASS_DEFAULT : custom_classes[c];
}
/*********************************Callback End*****************************/

static int check_current_locale()
{
	const char *pszLoc = NULL;
	const char *pszValue = "en_US_POSIX";
	i18n_ulocale_get_default(&pszLoc);

	if (strncmp(pszLoc, pszValue,strlen(pszValue)) == 0)
	{
		return 1;
	}
	return 0;
} 


static int32_t get_uchar_length(const char *arr)
{
	int32_t ulen = strlen(arr);
	i18n_uchar text[ulen + 1];
	i18n_ustring_copy_ua(text, arr);
	return i18n_ustring_get_length(text);
}

//& set: BaseUtilsUbidi
void ITs_base_utils_ubidi_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRetVal = i18n_ubidi_create(&g_hUbidi);
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_create failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}

	char pszTestStr[] = "<Paragraph1> <اختبار> paragraph1\n"
                         "<Paragraph2> <اختبار> paragraph2";

	g_nSrcLength = get_uchar_length(pszTestStr);

	g_pszUcharSrc = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (g_nSrcLength + 1));
	i18n_ustring_copy_ua(g_pszUcharSrc, pszTestStr);

	g_nDestLength = g_nSrcLength + 1;
	g_pszUcharDest = (i18n_uchar *) malloc(sizeof(i18n_uchar) * (g_nDestLength));

	nRetVal = i18n_ubidi_set_para(g_hUbidi, g_pszUcharSrc, g_nSrcLength, I18N_UBIDI_DEFAULT_LTR, NULL);
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_set_para failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	nRetVal = i18n_ubidi_set_reordering_options(g_hUbidi, I18N_UBIDI_OPTION_DEFAULT);
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_set_reordering_options failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	nRetVal = i18n_ubidi_set_reordering_mode(g_hUbidi, I18N_UBIDI_REORDER_DEFAULT);
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_set_reordering_mode failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	nRetVal = i18n_ubidi_set_class_cb(g_hUbidi, OldClassCB, NULL, NULL, NULL);
	if(nRetVal != I18N_ERROR_NONE)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_set_class_cb failed in startup\\n", __LINE__, API_NAMESPACE);
		g_bBaseUtilsInitFlag = false;
		return;
	}
	g_bBaseUtilsInitFlag = true;
	return;
}

void ITs_base_utils_ubidi_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	if( g_hUbidi )
	{
		int nRetVal = i18n_ubidi_destroy(g_hUbidi);
		if(nRetVal != I18N_ERROR_NONE)
		{
			FPRINTF("\\n[Line : %d][%s] i18n_ubidi_destroy failed in startup\\n", __LINE__, API_NAMESPACE);
			FREE_MEMORY(g_pszUcharSrc);
			FREE_MEMORY(g_pszUcharDest);
			return;
		}
		g_hUbidi = NULL;
	}
	FREE_MEMORY(g_pszUcharSrc);
	FREE_MEMORY(g_pszUcharDest);
	g_bBaseUtilsInitFlag = false;
	return;
}

/** @addtogroup itc-base-utils-testcases
*  @brief 		Integration testcases for module base-utils ubrk
*  @ingroup 	itc-base-utils
*  @{
*/

//& type: auto
//& purpose: Creates and Destroy i18n_ubidi_h handle.
/**
* @testcase				ITc_i18n_ubidi_create_destroy_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				- Creates and Destroy i18n_ubidi_h handle.
* @apitarget			i18n_ubidi_create, i18n_ubidi_destroy
* @apicovered			i18n_ubidi_create, i18n_ubidi_destroy
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_create and i18n_ubidi_destroy
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_create or i18n_ubidi_destroy or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_create_destroy_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_h hUbidi = NULL;

	int nRetVal = i18n_ubidi_create(&hUbidi);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_create", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hUbidi, "i18n_ubidi_create");
	
	nRetVal = i18n_ubidi_destroy(hUbidi);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}
// & type: auto
// & purpose: Gets the number of paragraphs.
/**
* @testcase				ITc_i18n_ubidi_count_paragraphs_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the number of paragraphs.
* @apitarget			i18n_ubidi_count_paragraphs
* @apicovered			i18n_ubidi_count_paragraphs
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_count_paragraphs
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_count_paragraphs or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_count_paragraphs_p(void)
{
	START_TEST_PRINT

	int32_t nCount = -1;
	int nParCount = 2;

	int nRetVal = i18n_ubidi_count_paragraphs(g_hUbidi, &nCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_count_paragraphs", BaseUtilsGetError(nRetVal));
	if(nCount != nParCount)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_count_paragraphs Fails nCount is:%d\\n", __LINE__, API_NAMESPACE, nCount);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets the number of runs.
/**
* @testcase				ITc_i18n_ubidi_count_runs_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the number of runs.
* @apitarget			i18n_ubidi_count_runs
* @apicovered			i18n_ubidi_count_runs
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_count_runs
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_count_runs or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_count_runs_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t nCount = -1;

	int nRetVal = i18n_ubidi_count_runs(g_hUbidi, &nCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_count_runs", BaseUtilsGetError(nRetVal));
	if(nCount < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_count_runs Fails nCount is:%d\\n", __LINE__, API_NAMESPACE, nCount);
		return 1;
	}

	return 0;
}


// & type: auto
// & purpose: Gets the base direction of the text provided according to the Unicode Bidirectional Algorithm.
/**
* @testcase				ITc_i18n_ubidi_get_base_direction_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the base direction of the text provided according to the Unicode Bidirectional Algorithm.
* @apitarget			i18n_ubidi_get_base_direction
* @apicovered			i18n_ubidi_get_base_direction
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_base_direction
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_base_direction or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_base_direction_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_direction_e direction = I18N_UBIDI_LTR;

	int nRetVal = i18n_ubidi_get_base_direction(g_pszUcharSrc, g_nSrcLength, &direction);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_base_direction", BaseUtilsGetError(nRetVal));
	if(direction != I18N_UBIDI_LTR)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ubidi_get_base_direction Fails\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Sets and Gets the current callback function used for ubidi class determination.
/**
* @testcase				ITc_i18n_ubidi_set_get_class_cb_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the current callback function used for ubidi class determination.
* @apitarget			i18n_ubidi_set_class_cb, i18n_ubidi_get_class_cb
* @apicovered			i18n_ubidi_set_class_cb, i18n_ubidi_get_class_cb
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_class_cb & i18n_ubidi_get_class_cb
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_class_cb or i18n_ubidi_get_class_cb or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_get_class_cb_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_class_cb newcb = NewClassCB;
	i18n_ubidi_class_cb oldcb = NULL;
	i18n_ubidi_class_cb getcb = NULL;
	const void *pszContext = NULL;

	int nRetVal = i18n_ubidi_set_class_cb(g_hUbidi, newcb, NULL, &oldcb, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_class_cb", BaseUtilsGetError(nRetVal));
	if (oldcb == NULL)
	{
		return 1;
	}
	if (oldcb != OldClassCB)
	{
		return 1;
	}
	nRetVal = i18n_ubidi_get_class_cb(g_hUbidi, &getcb, &pszContext);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_class_cb", BaseUtilsGetError(nRetVal));
	if (getcb == NULL)
	{
		return 1;
	}
	if (getcb != newcb)
	{
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Sets the context
/**
* @testcase				ITc_i18n_ubidi_set_context_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets the context
* @apitarget			i18n_ubidi_set_context
* @apicovered			i18n_ubidi_set_context
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_context
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_context or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_context_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int nRetVal = i18n_ubidi_set_context(g_hUbidi, g_pszUcharSrc, g_nSrcLength, NULL, 0);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_context", BaseUtilsGetError(nRetVal));

	return 0;
}

// & type: auto
// & purpose:  Modifies the operation of the ubidi algorithm such that it approximates an "inverse ubidi" algorithm.
/**
* @testcase				ITc_i18n_ubidi_set_inverse_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Modifies the operation of the ubidi algorithm such that it approximates an "inverse ubidi" algorithm.
* @apitarget			i18n_ubidi_set_inverse
* @apicovered			i18n_ubidi_set_inverse
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_inverse
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_inverse or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_inverse_p(void)
{
	START_TEST_PRINT

	i18n_ubool bisInverse = true;
	int nRetVal = i18n_ubidi_set_inverse(g_hUbidi, bisInverse);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_inverse", BaseUtilsGetError(nRetVal));

	return 0;
}

// & type: auto
// & purpose: Sets an #i18n_ubidi_h object to contain the reordering information, especially the resolved levels,for all the characters in a line of text.
/**
* @testcase				ITc_i18n_ubidi_set_line_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets an #i18n_ubidi_h object to contain the reordering information, especially the resolved levels,for all the characters in a line of text.
* @apitarget			i18n_ubidi_set_line
* @apicovered			i18n_ubidi_set_line
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_line
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_line or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_line_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int nRetVal = i18n_ubidi_set_line(g_hUbidi, 10, 16, g_hUbidi);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_line", BaseUtilsGetError(nRetVal));
	
	return 0;
}

// & type: auto
// & purpose: Performs the Unicode bidi algorithm.
/**
* @testcase				ITc_i18n_ubidi_set_para_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Performs the Unicode bidi algorithm.
* @apitarget			i18n_ubidi_set_para
* @apicovered			i18n_ubidi_set_para
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_para
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_para or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_para_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int nRetVal = i18n_ubidi_set_para(g_hUbidi, g_pszUcharSrc, g_nSrcLength, I18N_UBIDI_DEFAULT_LTR, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_para", BaseUtilsGetError(nRetVal));

	return 0;
}

// & type: auto
// & purpose: Sets and Gets the requested reordering mode
/**
* @testcase				ITc_i18n_ubidi_set_get_reordering_mode_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the requested reordering mode
* @apitarget			i18n_ubidi_set_reordering_mode, i18n_ubidi_get_reordering_mode
* @apicovered			i18n_ubidi_set_reordering_mode, i18n_ubidi_get_reordering_mode
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_reordering_mode & i18n_ubidi_get_reordering_mode
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_reordering_mode or i18n_ubidi_get_reordering_mode or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_get_reordering_mode_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_reordering_mode_e setMode = I18N_UBIDI_REORDER_NUMBERS_SPECIAL;
	i18n_ubidi_reordering_mode_e getMode = I18N_UBIDI_REORDER_DEFAULT;

	int nRetVal = i18n_ubidi_set_reordering_mode(g_hUbidi, setMode);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_reordering_mode", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ubidi_get_reordering_mode(g_hUbidi, &getMode);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_reordering_mode", BaseUtilsGetError(nRetVal));
	if(setMode != getMode)
	{
		FPRINTF("\\n[Line : %d][%s] Value Mismatch Fails\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose: Sets and Gets the reordering options
/**
* @testcase				ITc_i18n_ubidi_set_get_reordering_options_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets and Gets the reordering options
* @apitarget			i18n_ubidi_set_reordering_options, i18n_ubidi_get_reordering_options
* @apicovered			i18n_ubidi_set_reordering_options, i18n_ubidi_get_reordering_options
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_set_reordering_options & i18n_ubidi_get_reordering_options
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_set_reordering_options or i18n_ubidi_get_reordering_options or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_set_get_reordering_options_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_reordering_option_e setOptions = I18N_UBIDI_OPTION_INSERT_MARKS;
	i18n_ubidi_reordering_option_e getOptions = I18N_UBIDI_OPTION_DEFAULT;

	int nRetVal = i18n_ubidi_set_reordering_options(g_hUbidi, setOptions);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_reordering_options", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ubidi_get_reordering_options(g_hUbidi, &getOptions);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_reordering_options", BaseUtilsGetError(nRetVal));
	if(setOptions != getOptions)
	{
		FPRINTF("\\n[Line : %d][%s] Value Mismatch Fails\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose: Retrieves the ubidi class for a given code point
/**
* @testcase				ITc_i18n_ubidi_get_customized_class_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Retrieves the ubidi class for a given code point
* @apitarget			i18n_ubidi_get_customized_class
* @apicovered			i18n_ubidi_get_customized_class
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_customized_class
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_customized_class or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_customized_class_p(void)
{
	START_TEST_PRINT

	i18n_uchar32 nVal = 0;
	i18n_uchar_direction_e getDirection = L;

	int nRetVal = i18n_ubidi_get_customized_class(g_hUbidi, nVal, &getDirection);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_customized_class", BaseUtilsGetError(nRetVal));
	if(getDirection != R) 
	{
		FPRINTF("\\n[Line : %d][%s] Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose: Gets the directionality of the text.
/**
* @testcase				ITc_i18n_ubidi_get_direction_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the directionality of the text.
* @apitarget			i18n_ubidi_get_direction
* @apicovered			i18n_ubidi_get_direction
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_direction
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_direction or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_direction_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	i18n_ubidi_direction_e getDirection = -1;
	int nRetVal = i18n_ubidi_get_direction(g_hUbidi, &getDirection);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_direction", BaseUtilsGetError(nRetVal));
	if(getDirection  < I18N_UBIDI_LTR || getDirection  >I18N_UBIDI_NEUTRAL)
	{
		FPRINTF("\\n[Line : %d][%s] Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets the length of the text.
/**
* @testcase				ITc_i18n_ubidi_get_length_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the length of the text.
* @apitarget			i18n_ubidi_get_length
* @apicovered			i18n_ubidi_get_length
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_length
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_length or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_length_p(void)
{
	START_TEST_PRINT

	int32_t nLength = -1;
	int nRetVal = i18n_ubidi_get_length(g_hUbidi, &nLength);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_length", BaseUtilsGetError(nRetVal));
	if(nLength != g_nSrcLength)
	{
		FPRINTF("\\n[Line : %d][%s] Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets the level for one character.
/**
* @testcase				ITc_i18n_ubidi_get_level_at_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the level for one character.
* @apitarget			i18n_ubidi_get_level_at
* @apicovered			i18n_ubidi_get_level_at
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_level_at
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_level_at or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_level_at_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         1, 1, 1, 1, 1, 1,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int32_t processed_length = -1;
	int nRetVal = i18n_ubidi_get_processed_length(g_hUbidi, &processed_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_processed_length", BaseUtilsGetError(nRetVal));

	int32_t char_index;
	i18n_ubidi_level_t levels[processed_length];
	for(char_index = 0; char_index < processed_length; ++char_index)
	{
		nRetVal = i18n_ubidi_get_level_at(g_hUbidi, char_index, &levels[char_index]);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_level_at", BaseUtilsGetError(nRetVal));
	}

	int i;
	for(i = 0; i < processed_length; ++i)
	{
		if(levels[i] != valid_levels[i])
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets the logical text position from a visual position.
/**
* @testcase				ITc_i18n_ubidi_get_logical_index_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the logical text position from a visual position.
* @apitarget			i18n_ubidi_get_logical_index
* @apicovered			i18n_ubidi_get_logical_index
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_logical_index
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_logical_index or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_logical_index_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

	int32_t length = -1;
	int i;

	int nRetVal = i18n_ubidi_get_result_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_result_length", BaseUtilsGetError(nRetVal));

	for(i = 0; i < length; ++i)
	{
		int32_t logical_index = -1;
		nRetVal = i18n_ubidi_get_logical_index(g_hUbidi, i, &logical_index);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_logical_index", BaseUtilsGetError(nRetVal));
		if(logical_index != valid_map[i])
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets a logical-to-visual index map (array) for the character
/**
* @testcase				ITc_i18n_ubidi_get_logical_map_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets a logical-to-visual index map (array) for the character
* @apitarget			i18n_ubidi_get_logical_map
* @apicovered			i18n_ubidi_get_logical_map
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_logical_map
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_logical_map or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_logical_map_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};
	int32_t length = -1;
	int i;
	int nRetVal = i18n_ubidi_get_result_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_result_length", BaseUtilsGetError(nRetVal));

	int32_t index_map[length];

	nRetVal = i18n_ubidi_get_logical_map(g_hUbidi, index_map);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_logical_map", BaseUtilsGetError(nRetVal));
	for(i = 0; i < length; ++i)
	{
		if(index_map[i] != valid_map[i])
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose:  Gets a logical run.
/**
* @testcase				ITc_i18n_ubidi_get_logical_run_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				 Gets a logical run.
* @apitarget			i18n_ubidi_get_logical_run
* @apicovered			i18n_ubidi_get_logical_run
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_logical_run
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_logical_run or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_logical_run_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int valid_p_logical_position[] = {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
										20, 20, 20, 20, 20, 20,
										47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
										47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47,
										53, 53, 53, 53, 53, 53,
										65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65};
    i18n_ubidi_level_t valid_levels[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										1, 1, 1, 1, 1, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										1, 1, 1, 1, 1, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	int32_t processed_length = -1;
	int32_t logical_position;

	int nRetVal = i18n_ubidi_get_processed_length(g_hUbidi, &processed_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_processed_length", BaseUtilsGetError(nRetVal));

	for(logical_position = 0; logical_position < processed_length; ++logical_position)
	{
		int32_t p_logical_position = -2;
		i18n_ubidi_level_t level = 2;

		nRetVal = i18n_ubidi_get_logical_run(g_hUbidi, logical_position, &p_logical_position, &level);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_logical_run", BaseUtilsGetError(nRetVal));
		if((p_logical_position != valid_p_logical_position[logical_position]) || (level != valid_levels[logical_position]))
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets a paragraph, given a position within the text.
/**
* @testcase				ITc_i18n_ubidi_get_paragraph_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets a paragraph, given a position within the text.
* @apitarget			i18n_ubidi_get_paragraph
* @apicovered			i18n_ubidi_get_paragraph
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_paragraph
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_paragraph or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_paragraph_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t valid_para_start[] = {0, 33};
	int32_t valid_para_limit[] = {33, 65};
	i18n_ubidi_level_t valid_para_level[] = {0, 0};
	int32_t length = -1;
	int32_t char_index;

	int nRetVal = i18n_ubidi_get_processed_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_processed_length", BaseUtilsGetError(nRetVal));

	for(char_index = 0; char_index < length; ++char_index)
	{
		int32_t paragraph_index = -1;
		int32_t p_para_start = -1;
		int32_t p_para_limit = -1;
		i18n_ubidi_level_t p_para_level = 1;
		nRetVal = i18n_ubidi_get_paragraph(g_hUbidi, char_index, &p_para_start, &p_para_limit, &p_para_level, &paragraph_index);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_paragraph", BaseUtilsGetError(nRetVal));
		if((p_para_start != valid_para_start[paragraph_index]) || (p_para_limit != valid_para_limit[paragraph_index]) ||(p_para_level != valid_para_level[paragraph_index]))
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}
	return 0;
}

// & type: auto
// & purpose: Gets a paragraph, given the index of this paragraph.
/**
* @testcase				ITc_i18n_ubidi_get_paragraph_by_index_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets a paragraph, given the index of this paragraph.
* @apitarget			i18n_ubidi_get_paragraph_by_index
* @apicovered			i18n_ubidi_get_paragraph_by_index
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_paragraph_by_index
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_paragraph_by_index or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_paragraph_by_index_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t valid_para_start[] = {0, 33};
	int32_t valid_para_limit[] = {33, 65};
	i18n_ubidi_level_t valid_para_level[] = {0, 0};
	int32_t count = -1;
	int32_t para_index;

	int nRetVal = i18n_ubidi_count_paragraphs(g_hUbidi, &count);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_count_paragraphs", BaseUtilsGetError(nRetVal));

	for(para_index = 0; para_index < count; ++para_index)
	{
		int32_t p_para_start = -1;
		int32_t p_para_limit = -1;
		i18n_ubidi_level_t p_para_level = 1;
		nRetVal = i18n_ubidi_get_paragraph_by_index(g_hUbidi, para_index, &p_para_start, &p_para_limit, &p_para_level);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_paragraph_by_index", BaseUtilsGetError(nRetVal));
		if((p_para_start != valid_para_start[para_index]) || (p_para_limit != valid_para_limit[para_index]) ||(p_para_level != valid_para_level[para_index]))
		{
			FPRINTF("\\n[Line : %d][%s] Value mismatch Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets the paragraph level of the text.
/**
* @testcase				ITc_i18n_ubidi_get_para_level_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the paragraph level of the text.
* @apitarget			i18n_ubidi_get_para_level
* @apicovered			i18n_ubidi_get_para_level
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_para_level
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_para_level or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_para_level_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	i18n_ubidi_level_t level = 1;

	int nRetVal = i18n_ubidi_get_para_level(g_hUbidi, &level);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_para_level", BaseUtilsGetError(nRetVal));
	if(level != 0)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose: Gets the length of the source text processed
/**
* @testcase				ITc_i18n_ubidi_get_processed_length_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the length of the source text processed
* @apitarget			i18n_ubidi_get_processed_length
* @apicovered			i18n_ubidi_get_processed_length
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_processed_length
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_processed_length or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_processed_length_p(void)
{
	START_TEST_PRINT

	int32_t length = -1;
	char *pszText = "Tizen Native Testing";

	int nRetVal = i18n_ubidi_get_processed_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_processed_length", BaseUtilsGetError(nRetVal));
	if(length != g_nSrcLength)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets the length of the reordered text resulting
/**
* @testcase				ITc_i18n_ubidi_get_result_length_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the length of the reordered text resulting
* @apitarget			i18n_ubidi_get_result_length
* @apicovered			i18n_ubidi_get_result_length
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_result_length
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_result_length or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_result_length_p(void)
{
	START_TEST_PRINT

	int32_t length = -1;
	char *pszText = "Tizen Native Testing";

	int nRetVal = i18n_ubidi_get_result_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_result_length", BaseUtilsGetError(nRetVal));
	if(length != g_nSrcLength)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

// & type: auto
// & purpose: Gets the pointer to the given #i18n_ubidi_h object's text.
/**
* @testcase				ITc_i18n_ubidi_get_text_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the pointer to the given #i18n_ubidi_h object's text.
* @apitarget			i18n_ubidi_get_text
* @apicovered			i18n_ubidi_get_text
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_text
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_text or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_text_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	char *text = NULL;
	int nRetVal = i18n_ubidi_get_text(g_hUbidi, &text);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_text", BaseUtilsGetError(nRetVal));

	int nCmpare = strcmp(text, "<Paragraph1> <اختبار> paragraph1\n"
                           "<Paragraph2> <اختبار> paragraph2");
	if(nCmpare != 0)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets the visual position from a logical text position.
/**
* @testcase				ITc_i18n_ubidi_get_visual_index_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the visual position from a logical text position.
* @apitarget			i18n_ubidi_get_visual_index
* @apicovered			i18n_ubidi_get_visual_index
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_visual_index
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_visual_index or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_visual_index_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t length = -1;
	int i;
	int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};
	int nRetVal = i18n_ubidi_get_result_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_result_length", BaseUtilsGetError(nRetVal));

	for(i = 0; i < length; ++i)
	{
		int32_t visual_index = -1;
		nRetVal = i18n_ubidi_get_visual_index(g_hUbidi, i, &visual_index);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_visual_index", BaseUtilsGetError(nRetVal));
		if(visual_index != valid_map[i])
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets a visual-to-logical index map
/**
* @testcase				ITc_i18n_ubidi_get_visual_map_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets a visual-to-logical index map
* @apitarget			i18n_ubidi_get_visual_map
* @apicovered			i18n_ubidi_get_visual_map
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_visual_map
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_visual_map or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_visual_map_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int32_t valid_map[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                           19, 18, 17, 16, 15, 14,
                           20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
                           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
                           44, 45, 46,
                           52, 51, 50, 49, 48, 47,
                           53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64};

	int32_t length = -1;
	int i;

	int nRetVal = i18n_ubidi_get_result_length(g_hUbidi, &length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_result_length", BaseUtilsGetError(nRetVal));

	int32_t index_map[length];

	nRetVal = i18n_ubidi_get_visual_map(g_hUbidi, index_map);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_visual_map", BaseUtilsGetError(nRetVal));

	for(i = 0; i < length; ++i)
	{
		if(index_map[i] != valid_map[i])
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets one run's logical start, length, and directionality
/**
* @testcase				ITc_i18n_ubidi_get_visual_run_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets one run's logical start, length, and directionality
* @apitarget			i18n_ubidi_get_visual_run
* @apicovered			i18n_ubidi_get_visual_run
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_get_visual_run
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_get_visual_run or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_get_visual_run_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	int logical_ind[] = {0, 14, 20, 47, 53};
	int length[] = {14, 6, 27, 6, 12};
	int32_t run_index;
	int nCounter = -1;
	i18n_ubidi_direction_e dir[] = {I18N_UBIDI_LTR, I18N_UBIDI_RTL,
            I18N_UBIDI_LTR, I18N_UBIDI_RTL, I18N_UBIDI_LTR};

	int nRetVal = i18n_ubidi_count_runs(g_hUbidi, &nCounter);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_count_runs", BaseUtilsGetError(nRetVal));

	for(run_index = 0; run_index < nCounter; ++run_index)
	{
		int32_t p_logical_index = -1;
		int32_t p_length = -1;
		i18n_ubidi_direction_e direction = I18N_UBIDI_MIXED;
		nRetVal = i18n_ubidi_get_visual_run(g_hUbidi, run_index, &p_logical_index, &p_length, &direction);
		PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_get_visual_run", BaseUtilsGetError(nRetVal));
		if((p_logical_index != logical_ind[run_index]) || (p_length != length[run_index]) || (direction != dir[run_index]))
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Inverts an index map.
/**
* @testcase				ITc_i18n_ubidi_invert_map_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Inverts an index map.
* @apitarget			i18n_ubidi_invert_map
* @apicovered			i18n_ubidi_invert_map
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_invert_map
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_invert_map or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_invert_map_p(void)
{
	START_TEST_PRINT

	int32_t length = 10;
	int32_t src_map[] = {0, 1, 11, 12, 6, 5, 4, 13, 9, -1};
	int32_t valid_dst_map[] = {0, 1, -1, -1, 6, 5, 4, -1, -1, 8, -1, 2, 3, 7};
	int32_t dst_length = 14;
	int32_t dst_map[dst_length+1];
	int i;

	int nRetVal = i18n_ubidi_invert_map(src_map, length, dst_map);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_invert_map", BaseUtilsGetError(nRetVal));

	for(i = 0; i < dst_length; ++i)
	{
		if(dst_map[i] != valid_dst_map[i])
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

// & type: auto
// & purpose: Gets whether the given #i18n_ubidi_h object is set to perform the inverse ubidi algorithm.
/**
* @testcase				ITc_i18n_ubidi_is_inverse_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets whether the given #i18n_ubidi_h object is set to perform the inverse ubidi algorithm.
* @apitarget			i18n_ubidi_is_inverse
* @apicovered			i18n_ubidi_is_inverse
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_is_inverse
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_is_inverse or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_is_inverse_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_reordering_mode_e mode = I18N_UBIDI_REORDER_DEFAULT;
	i18n_ubool is_inverse = true;

	int nRetVal = i18n_ubidi_set_reordering_mode(g_hUbidi, mode);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_reordering_mode", BaseUtilsGetError(nRetVal));

	nRetVal = i18n_ubidi_is_inverse(g_hUbidi, &is_inverse);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_is_inverse", BaseUtilsGetError(nRetVal));
	if(is_inverse != false)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Gets whether the given #i18n_ubidi_h object is set to allocate level 0 to block separators.
/**
* @testcase				ITc_i18n_ubidi_is_order_paragraphs_ltr_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets whether the given #i18n_ubidi_h object is set to allocate level 0 to block separators.
* @apitarget			i18n_ubidi_is_order_paragraphs_ltr
* @apicovered			i18n_ubidi_is_order_paragraphs_ltr
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_is_order_paragraphs_ltr
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_is_order_paragraphs_ltr or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_is_order_paragraphs_ltr_p(void)
{
	START_TEST_PRINT

	i18n_ubool bOrderParaLtr = true;
	i18n_ubool bRetOrderParaLtr = false;

	int nRetVal = i18n_ubidi_order_paragraphs_ltr(g_hUbidi, bOrderParaLtr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_order_paragraphs_ltr", BaseUtilsGetError(nRetVal));

	int nSrcLen = i18n_ustring_get_length(g_pszUcharSrc);
	nRetVal = i18n_ubidi_set_para(g_hUbidi, g_pszUcharSrc, nSrcLen, I18N_UBIDI_DEFAULT_LTR, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_set_para", BaseUtilsGetError(nRetVal));


	nRetVal = i18n_ubidi_is_order_paragraphs_ltr(g_hUbidi, &bRetOrderParaLtr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_is_order_paragraphs_ltr", BaseUtilsGetError(nRetVal));
	if(bRetOrderParaLtr != true)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Creates an ubidi structure with preallocated memory for internal structures.
/**
* @testcase				ITc_i18n_ubidi_create_sized_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates an ubidi structure with preallocated memory for internal structures.
* @apitarget			i18n_ubidi_create_sized
* @apicovered			i18n_ubidi_create_sized
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_create_sized
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_create_sized or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_create_sized_p(void)
{
	START_TEST_PRINT

	int32_t max_length = 10;
	int32_t max_run_count = 3;
	i18n_ubidi_h hUbidi = NULL;

	int nRetVal = i18n_ubidi_create_sized(max_length, max_run_count, &hUbidi);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_create_sized", BaseUtilsGetError(nRetVal));
	CHECK_HANDLE(hUbidi,"i18n_ubidi_create_sized");

	nRetVal = i18n_ubidi_destroy(hUbidi);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_destroy", BaseUtilsGetError(nRetVal));

	return 0;
}

// & type: auto
// & purpose: Sets whether block separators must be allocated level zero
/**
* @testcase				ITc_i18n_ubidi_order_paragraphs_ltr_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets whether block separators must be allocated level zero
* @apitarget			i18n_ubidi_order_paragraphs_ltr
* @apicovered			i18n_ubidi_order_paragraphs_ltr
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_order_paragraphs_ltr
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_order_paragraphs_ltr or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_order_paragraphs_ltr_p(void)
{
	START_TEST_PRINT

	i18n_ubool ret_order_paragraph_ltr = true;
	i18n_ubool order_paragraph_ltr = true;
	int nRetVal = i18n_ubidi_is_order_paragraphs_ltr(g_hUbidi, &ret_order_paragraph_ltr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_is_order_paragraphs_ltr", BaseUtilsGetError(nRetVal));
	if(ret_order_paragraph_ltr != false)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRetVal = i18n_ubidi_order_paragraphs_ltr(g_hUbidi, order_paragraph_ltr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_order_paragraphs_ltr", BaseUtilsGetError(nRetVal));

	int nSrcLen = i18n_ustring_get_length(g_pszUcharSrc);
	nRetVal = i18n_ubidi_set_para(g_hUbidi, g_pszUcharSrc, nSrcLen, I18N_UBIDI_DEFAULT_RTL, NULL);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ustring_get_length", BaseUtilsGetError(nRetVal));

	ret_order_paragraph_ltr = false;
	nRetVal = i18n_ubidi_is_order_paragraphs_ltr(g_hUbidi, &ret_order_paragraph_ltr);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_is_order_paragraphs_ltr", BaseUtilsGetError(nRetVal));
	if(ret_order_paragraph_ltr != true)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

// & type: auto
// & purpose: Performs logical reordering.
/**
* @testcase				ITc_i18n_ubidi_reorder_logical_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Performs logical reordering.
* @apitarget			i18n_ubidi_reorder_logical
* @apicovered			i18n_ubidi_reorder_logical
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_reorder_logical
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_reorder_logical or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_reorder_logical_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
	int32_t length = 10;
	int32_t valid_index_map[] = {3, 2, 1, 0, 4, 5, 6, 9, 8, 7};
	int32_t index_map[length + 1];

	int nRetVal = i18n_ubidi_reorder_logical(levels, length, index_map);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_reorder_logical", BaseUtilsGetError(nRetVal));

	int i;
	for(i = 0; i < length; ++i)
	{
		if(index_map[i] != valid_index_map[i])
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}
// & type: auto
// & purpose: Performs visual reordering.
/**
* @testcase				ITc_i18n_ubidi_reorder_visual_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Performs visual reordering.
* @apitarget			i18n_ubidi_reorder_visual
* @apicovered			i18n_ubidi_reorder_visual
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_reorder_visual
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_reorder_visual or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_reorder_visual_p(void)
{
	START_TEST_PRINT

	i18n_ubidi_level_t levels[] = {1, 1, 1, 1, 0, 0, 0, 1, 1, 1};
	int32_t length = 10;
	int32_t valid_index_map[] = {3, 2, 1, 0, 4, 5, 6, 9, 8, 7};
	int32_t index_map[length + 1];

	int nRetVal = i18n_ubidi_reorder_visual(levels, length, index_map);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_reorder_visual", BaseUtilsGetError(nRetVal));

	int i;
	for(i = 0; i < length; ++i)
	{
		if(index_map[i] != valid_index_map[i])
		{
			FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}
// & type: auto
// & purpose: write a reordered string to the destination buffer.
/**
* @testcase				ITc_i18n_ubidi_write_reordered_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				write a reordered string to the destination buffer.
* @apitarget			i18n_ubidi_write_reordered
* @apicovered			i18n_ubidi_write_reordered
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_write_reordered
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_write_reordered or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_write_reordered_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	uint16_t options = I18N_UBIDI_KEEP_BASE_COMBINING;
	int32_t output_length = -1;
	int nRetVal = i18n_ubidi_write_reordered(g_hUbidi, options, g_nDestLength, g_pszUcharDest, &output_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_write_reordered", BaseUtilsGetError(nRetVal));
	if(output_length != g_nSrcLength)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char tmp[BUFFER];
	i18n_ustring_copy_au(tmp, g_pszUcharDest);
	int cmp = strcmp(tmp, "<Paragraph1> <رابتخا> paragraph1\n"
                          "<Paragraph2> <رابتخا> paragraph2");
	if(cmp !=0)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
// & type: auto
// & purpose: Reverses a Right-To-Left run of Unicode text.
/**
* @testcase				ITc_i18n_ubidi_write_reverse_p
* @since_tizen 			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Reverses a Right-To-Left run of Unicode text.
* @apitarget			i18n_ubidi_write_reverse
* @apicovered			i18n_ubidi_write_reverse
* @passcase				I18N_ERROR_NONE returned by i18n_ubidi_write_reverse
* @failcase				I18N_ERROR_NONE not returned by i18n_ubidi_write_reverse or pre-condition APIs fail
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_ubidi_write_reverse_p(void)
{
	START_TEST_PRINT
	if (check_current_locale())
		return 0;

	uint16_t options = I18N_UBIDI_DO_MIRRORING;
	int32_t output_length = -1;
	int nRetVal = i18n_ubidi_write_reverse(g_pszUcharSrc, g_nSrcLength, options, g_nDestLength, g_pszUcharDest, &output_length);
	PRINT_RESULT(I18N_ERROR_NONE, nRetVal,"i18n_ubidi_write_reverse", BaseUtilsGetError(nRetVal));
	if(output_length == -1)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	char tmp[BUFFER];
	i18n_ustring_copy_au(tmp, g_pszUcharDest);
	int cmp = strcmp(tmp,"2hpargarap <رابتخا> <2hpargaraP>\n"
                          "1hpargarap <رابتخا> <1hpargaraP>");

	if(cmp !=0)
	{
		FPRINTF("\\n[Line : %d][%s]Fail\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
/** @} */
/** @} */
