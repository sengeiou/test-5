//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
 * @function             ITs_base_utils_ures_startup
 * @description          Called before each test
 * @parameter            NA
 * @return               NA
 */
void ITs_base_utils_ures_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
 * @function             ITs_base_utils_ures_cleanup
 * @description          Called after each test
 * @parameter            NA
 * @return               NA
 */
void ITs_base_utils_ures_cleanup(void)
{
#if DEBUG
	FPRINTF("\\n[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif

	return;
}

static void itc_base_utils_get_resource_path(char *path, int size)
{
	char *apps_root;
	if (NULL == path)
		return;

	apps_root = app_get_resource_path();
	assert_neq(apps_root, NULL);

	snprintf(path, size, "%s", apps_root);
	FPRINTF("resource path]: %s", path);
	free(apps_root);
}

/*
 * @testcase		ITc_i18n_ures_create_destroy_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_create, i18n_ures_destroy
 * @apicovered          i18n_ures_create, i18n_ures_destroy
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_destroy
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_destroy
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_create_destroy_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "en";
	const char *pszPackageName = NULL;
	i18n_ures_h hUres = NULL;

	//Target API
	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));
	hUres = NULL;

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_create_direct_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_create_direct
 * @apicovered          i18n_ures_create_direct
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create_direct
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create_direct
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_create_direct_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "en";
	const char *pszPackageName = NULL;
	i18n_ures_h hUres = NULL;

	//Target API
	nRet = i18n_ures_create_direct(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create_direct", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create_direct");

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_create_unicode_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_create_unicode
 * @apicovered          i18n_ures_create_unicode
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create_unicode
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create_unicode
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_create_unicode_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "en";
	const char *pszPackageName = NULL;
	i18n_ures_h hUres = NULL;

	//Target API
	nRet = i18n_ures_create_unicode(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create_unicode", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create_unicode");

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_version_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_version
 * @apicovered          i18n_ures_create, i18n_ures_get_version
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_version
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_version
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_version_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "en";
	const char *pszPackageName = NULL;
	i18n_ures_h hUres = NULL;
	i18n_uversion_info version_array;

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_version(hUres, version_array);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_version", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_locale_by_type_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_locale_by_type
 * @apicovered          i18n_ures_create, i18n_ures_get_locale_by_type
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_locale_by_type
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_locale_by_type
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_locale_by_type_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "en";
	const char *pszPackageName = NULL;
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_locale_by_type(hUres, I18N_ULOCALE_DATA_LOCALE_TYPE_ACTUAL_LOCALE, &pszLocaleType);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_locale_by_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(pszLocaleType, "i18n_ures_get_locale_by_type", i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_string
 * @apicovered          i18n_ures_create, i18n_ures_get_string
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_string_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int32_t len = -1;
	int count = -1;
	const i18n_uchar *pszStrResult = NULL;
	i18n_ures_type_e type_result;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < count; ++i)
	{
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));

		nRet = i18n_ures_get_type(hItem, &type_result);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));

		switch(type_result)
		{
		case I18N_URES_STRING:
			{
				//Target API
				nRet = i18n_ures_get_string(hItem, &len, &pszStrResult);
				PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_string", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));
				if(len < 0)
				{
					FPRINTF("\\n[Line : %d][%s] i18n_ures_get_string failed ,len is not correct \n", __LINE__, API_NAMESPACE);
					i18n_ures_destroy(hItem);
					i18n_ures_destroy(hUres);
					return 1;
				}
				break;
			}

		}
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_UTF8_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_UTF8_string
 * @apicovered          i18n_ures_create, i18n_ures_get_UTF8_string
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_UTF8_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_UTF8_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_UTF8_string_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int32_t len = -1;
	int count = -1;
	i18n_ures_type_e type_result;
	int i = 0;
	const char *pszResult = NULL;
	char *pszBuff = NULL;
	char szBuffer[16];
	pszBuff = szBuffer;
	int32_t result_len = (int32_t)sizeof(szBuffer);
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	if(count > 10)
	{
		count = 10;
	}
	for(i = 0; i < count; ++i)
	{
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));

		nRet = i18n_ures_get_type(hItem, &type_result);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));

		switch(type_result)
		{
		case I18N_URES_STRING:
			{
				//Target API
				nRet = i18n_ures_get_UTF8_string(hItem, pszBuff, &result_len, true, &pszResult);
				PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_string", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));
				break;
			}
		}
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_binary_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_binary
 * @apicovered          i18n_ures_create, i18n_ures_get_binary
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_binary
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_binary
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_binary_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresKey = NULL;
	int32_t len;
	const uint8_t *binary_result;
	int i = 0;
	int nCount = 15;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_by_key(hUres, "binarytest", hUresKey, &hUresKey);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresKey, "i18n_ures_get_by_key", i18n_ures_destroy(hUres));

	//Target API
	nRet = i18n_ures_get_binary(hUresKey, &len, &binary_result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_binary", BaseUtilsGetError(nRet), i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));

	if(len < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_binary failed ,len is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUresKey);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < nCount; ++i)
	{
		PRINT_RESULT_CLEANUP(binary_result[i], i, "i18n_ures_get_binary", "obtained and expected result are not same", i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));
	}

	nRet = i18n_ures_destroy(hUresKey);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_int_vector_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_int_vector
 * @apicovered          i18n_ures_create, i18n_ures_get_int_vector
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_int_vector
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_int_vector
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_int_vector_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresKey = NULL;
	int32_t len = -1;
	const int32_t *int_vector_result;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_by_key(hUres, "emptyintv", hUresKey, &hUresKey);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresKey, "i18n_ures_get_by_key", i18n_ures_destroy(hUres));

	//Target API
	nRet = i18n_ures_get_int_vector(hUresKey, &len, &int_vector_result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_int_vector", BaseUtilsGetError(nRet), i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));
	PRINT_RESULT_CLEANUP(len, 0, "i18n_ures_get_int_vector", "obtained and expected length are not same", i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUresKey);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_uint_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_uint
 * @apicovered          i18n_ures_create, i18n_ures_get_uint
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_uint
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_uint
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_uint_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresKey = NULL;
	int32_t len = -1;
	const int32_t *int_vector_result;
	uint32_t uint_result;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_by_key(hUres, "one", hUresKey, &hUresKey);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresKey, "i18n_ures_get_by_key", i18n_ures_destroy(hUres));

	//Target API
	nRet = i18n_ures_get_uint(hUresKey, &uint_result);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_uint", BaseUtilsGetError(nRet), i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));
	PRINT_RESULT_CLEANUP(uint_result, 1, "i18n_ures_get_uint", "obtained and expected length are not same", i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUresKey);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_int_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_int
 * @apicovered          i18n_ures_create, i18n_ures_get_int
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_int
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_int
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_int_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int32_t int_result;
	int count;
	i18n_ures_type_e type_result;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < count; ++i)
	{
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));

		nRet = i18n_ures_get_type(hItem, &type_result);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));

		switch(type_result)
		{
		case I18N_URES_INT:
			{
				//Target API
				nRet = i18n_ures_get_int(hItem, &int_result);
				PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_int", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));
				break;
			}

		}
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_size_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_size
 * @apicovered          i18n_ures_create, i18n_ures_get_size
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_size
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_size
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_size_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	i18n_ures_h hUres = NULL;
	int count = -1;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_type_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_type
 * @apicovered          i18n_ures_create, i18n_ures_get_type
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_type
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_type
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_type_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int count;
	i18n_ures_type_e type_result;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < count; ++i)
	{
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));

		//Target API
		nRet = i18n_ures_get_type(hItem, &type_result);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_key_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_key
 * @apicovered          i18n_ures_create, i18n_ures_get_key
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_key
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_key
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_key_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int count;
	i18n_ures_type_e type_result;
	const char *pszKey = NULL;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < count; ++i)
	{
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));

		//Target API
		nRet = i18n_ures_get_key(hItem, &pszKey);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_type", BaseUtilsGetError(nRet), i18n_ures_destroy(hItem); i18n_ures_destroy(hUres));
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_reset_iterator_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_reset_iterator
 * @apicovered          i18n_ures_create, i18n_ures_reset_iterator
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_reset_iterator
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_reset_iterator
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_reset_iterator_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_reset_iterator(hUres);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_reset_iterator", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;

}
/*
 * @testcase		ITc_i18n_ures_has_next_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_has_next
 * @apicovered          i18n_ures_create, i18n_ures_has_next
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_has_next
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_has_next
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_has_next_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	bool bHasNext = false;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_has_next(hUres, &bHasNext);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_has_next", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	PRINT_RESULT_CLEANUP(true, bHasNext, "i18n_ures_has_next", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_next_resource_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_next_resource
 * @apicovered          i18n_ures_create, i18n_ures_get_next_resource
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_next_resource
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_next_resource
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_next_resource_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresNextResource = NULL;
	bool bHasNext = false;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_next_resource(hUres, hUresNextResource, &hUresNextResource);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_next_resource", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresNextResource, "i18n_ures_get_next_resource", i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUresNextResource);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_next_string_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_next_string
 * @apicovered          i18n_ures_create, i18n_ures_get_next_string
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_next_string
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_next_string
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_next_string_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	i18n_ures_h hUres = NULL;
	const i18n_uchar *pszResult = NULL;
	int32_t result_len = 0;
	const char *pszKey = NULL;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_next_string(hUres, &result_len, &pszKey, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_next_string", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	if(result_len < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_next_string failed ,result_len is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_by_index_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_by_index
 * @apicovered          i18n_ures_create, i18n_ures_get_by_index
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_by_index
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_by_index
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_by_index_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "testtypes";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hItem = NULL;
	int count = -1;
	int i = 0;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_size(hUres, &count);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_size", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(count < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_size failed ,count is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	for(i = 0; i < count; ++i)
	{
		//Target API
		nRet = i18n_ures_get_by_index(hUres, i, hItem, &hItem);
		PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
		CHECK_HANDLE_CLEANUP(hItem, "i18n_ures_get_by_index", i18n_ures_destroy(hUres));
	}
	nRet = i18n_ures_destroy(hItem);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_string_by_index_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_string_by_index
 * @apicovered          i18n_ures_create, i18n_ures_get_string_by_index
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_string_by_index
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_string_by_index
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_string_by_index_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "te";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresKey = NULL;
	int32_t len = -1;
	const i18n_uchar *pszStrResult = NULL;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	nRet = i18n_ures_get_by_key(hUres, "array_only_in_te", hUresKey, &hUresKey);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresKey, "i18n_ures_get_by_key", i18n_ures_destroy(hUres));

	//Target API
	nRet = i18n_ures_get_string_by_index(hUresKey, 0, &len, &pszStrResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_string_by_index", BaseUtilsGetError(nRet),i18n_ures_destroy(hUresKey); i18n_ures_destroy(hUres));
	if(len < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_string_by_index failed ,len is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUresKey);
		i18n_ures_destroy(hUres);
		return 1;
	}

	nRet = i18n_ures_destroy(hUresKey);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_UTF8_string_by_index_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_UTF8_string_by_index
 * @apicovered          i18n_ures_create, i18n_ures_get_UTF8_string_by_index
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_UTF8_string_by_index
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_UTF8_string_by_index
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_UTF8_string_by_index_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "te";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	const char *pszStrResult = NULL;
	char *pszBuff = NULL;
	char szBuffer[16];
	pszBuff = szBuffer;
	int32_t len = (int32_t)sizeof(szBuffer);
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_UTF8_string_by_index(hUres, 1, pszBuff, &len, false, &pszStrResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_UTF8_string_by_index", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_by_key_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_by_key
 * @apicovered          i18n_ures_create, i18n_ures_get_by_key
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_by_key
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_by_key
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_by_key_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "te";
	const char *pszLocaleType = NULL;
	i18n_ures_h hUres = NULL;
	i18n_ures_h hUresKey = NULL;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_by_key(hUres, "array_only_in_te", hUresKey, &hUresKey);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	CHECK_HANDLE_CLEANUP(hUresKey, "i18n_ures_get_by_key", i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUresKey);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_string_by_key_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_string_by_key
 * @apicovered          i18n_ures_create, i18n_ures_get_string_by_key
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_string_by_key
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_string_by_key
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_string_by_key_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "te";
	i18n_ures_h hUres = NULL;
	const i18n_uchar *pszResult = NULL;
	int32_t result_len = -1;
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_string_by_key(hUres, "string_only_in_te", &result_len, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_string_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(result_len < 0)
	{
		FPRINTF("\\n[Line : %d][%s] i18n_ures_get_string_by_key failed ,result_len is not correct \n", __LINE__, API_NAMESPACE);
		i18n_ures_destroy(hUres);
		return 1;
	}

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
/*
 * @testcase		ITc_i18n_ures_get_UTF8_string_by_key_p
 * @since_tizen 	6.0
 * @author            	SRID(mohit.m)
 * @reviewer         	SRID(shobhit.v)
 * @type 		auto
 * @scenario		calls the api based on code
 * @apitarget		i18n_ures_get_UTF8_string_by_key
 * @apicovered          i18n_ures_create, i18n_ures_get_UTF8_string_by_key
 * @passcase		I18N_ERROR_NONE returned by i18n_ures_create, i18n_ures_get_UTF8_string_by_key
 * @failcase		I18N_ERROR_NONE not returned by i18n_ures_create, i18n_ures_get_UTF8_string_by_key
 * @precondition	NA
 * @postcondition	NA
 */
int ITc_i18n_ures_get_UTF8_string_by_key_p(void)
{
	START_TEST_PRINT;

	int nRet = -1;
	const char *pszLocale = "te";
	i18n_ures_h hUres = NULL;
	const i18n_uchar *pszExpectedResult = "TE";
	const char *pszResult = NULL;
	char *pszBuff = NULL;
	char szBuffer[16];
	pszBuff = szBuffer;
	int32_t result_len = (int32_t)sizeof(szBuffer);
	char pszPackageName[CONFIG_VALUE_LEN_MAX] = {0,};
	itc_base_utils_get_resource_path(pszPackageName, CONFIG_VALUE_LEN_MAX - 1);

	nRet = i18n_ures_create(pszPackageName, pszLocale, &hUres);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_ures_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(hUres, "i18n_ures_create");

	//Target API
	nRet = i18n_ures_get_UTF8_string_by_key(hUres, "string_only_in_te", pszBuff, &result_len, false, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_UTF8_string_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));
	if(strncmp(pszResult, pszExpectedResult, strlen(pszExpectedResult)) != 0)
	{
		FPRINTF("[Line : %d][%s] i18n_ures_get_UTF8_string_by_key mismatch pszResult = %s. \\n", __LINE__, API_NAMESPACE, pszResult);
		i18n_ures_destroy(hUres);
		return 1;
	}

	pszResult = NULL;

	nRet = i18n_ures_get_UTF8_string_by_key(hUres, "string_only_in_te", pszBuff, &result_len, true, &pszResult);
	PRINT_RESULT_CLEANUP(I18N_ERROR_NONE, nRet, "i18n_ures_get_UTF8_string_by_key", BaseUtilsGetError(nRet), i18n_ures_destroy(hUres));

	nRet = i18n_ures_destroy(hUres);
	PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_ures_destroy", BaseUtilsGetError(nRet));

	return 0;
}
