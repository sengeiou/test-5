#include "ITs-base-utils-common.h"

i18n_alpha_idx_h g_alphaIndex = NULL;
i18n_immutable_idx_h g_immutableIndex = NULL;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUstring

/**
* @function 		ITs_base_utils_immutable_idx_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_immutable_idx_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int ret = remove(ERR_LOG);
		if(ret == -1)
		{
			FPRINTF("[Line: %d][%s] unlinking file name error =%s \\n", __LINE__, API_NAMESPACE,ERR_LOG);
			return;
		}
	}
	const char *pszLocalId = "en_US";
	g_bBaseUtilsInitFlag = true;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_base_utils_immutable_idx_startup\\n", __LINE__, API_NAMESPACE);
#endif
	int nRet = i18n_alpha_idx_create_from_locale_id(pszLocalId, &g_alphaIndex);
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_create_from_locale_id: failed in startup. Error Code = %d\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
		return;
	}

	if(g_alphaIndex == NULL)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] Failed in startup. g_alphaIndex is null\\n", __LINE__, API_NAMESPACE);
		return;
	}

	nRet = i18n_alpha_idx_add_labels_with_locale_id(g_alphaIndex, pszLocalId);
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_add_labels_with_locale_id: failed in startup. Error Code = %d\\n", __LINE__, API_NAMESPACE, BaseUtilsGetError(nRet));
		return;
	}

	nRet = i18n_immutable_idx_create(g_alphaIndex, &g_immutableIndex);
	if (nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_immutable_idx_create: failed in startup\\n", __LINE__, API_NAMESPACE);
		return;
	}

	if(g_immutableIndex == NULL)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] Failed in startup. g_immutableIndex is null\\n", __LINE__, API_NAMESPACE);
		return;
	}

	return;
}

/**
* @function 		ITs_base_utils_immutable_idx_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_immutable_idx_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bBaseUtilsInitFlag = false;
	int nRet;

	if(g_alphaIndex)
	{
		nRet = i18n_alpha_idx_destroy(g_alphaIndex);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_destroy", BaseUtilsGetError(nRet));
	}

	if(g_immutableIndex)
	{
		nRet = i18n_immutable_idx_destroy(g_immutableIndex);
		PRINT_RESULT_NORETURN(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_destroy", BaseUtilsGetError(nRet));
	}

	return;
}

//& type: auto
//& purpose: Creates/destroys an immutable index object.
/**
* @testcase				ITc_i18n_immutable_idx_create_destroy
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates/destroys an immutable index object.
* @apitarget			i18n_immutable_idx_create, i18n_immutable_idx_destroy
* @apicovered			i18n_immutable_idx_create, i18n_immutable_idx_destroy
* @passcase				When i18n_immutable_idx_create, i18n_immutable_idx_destroy successful
* @failcase				If target i18n_immutable_idx_create, i18n_immutable_idx_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_immutable_idx_create_destroy(void)
{
	START_TEST;

	const char *pszLanguage = "en";
    const char *pszCountry = "US";
	i18n_immutable_idx_h immutableIndex = NULL;

	int nRet = i18n_immutable_idx_create(g_alphaIndex, &immutableIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_create", BaseUtilsGetError(nRet));
	CHECK_HANDLE(immutableIndex, "i18n_immutable_idx_create");

	nRet = i18n_immutable_idx_destroy(immutableIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_destroy", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Gets the number of index buckets and labels, including underflow/inflow/overflow.
/**
* @testcase				ITc_i18n_immutable_idx_get_bucket_count
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the number of buckets/labels in the current bucket.
* @apitarget			i18n_immutable_idx_get_bucket_count
* @apicovered			i18n_immutable_idx_get_bucket_count
* @passcase				When i18n_immutable_idx_get_bucket_count successful
* @failcase				If target i18n_immutable_idx_get_bucket_count fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_immutable_idx_get_bucket_count(void)
{
	START_TEST;

	int32_t nBucketCount = -1;

	int nRet = i18n_immutable_idx_get_bucket_count(g_immutableIndex, &nBucketCount);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_get_bucket_count", BaseUtilsGetError(nRet));

	if(nBucketCount != 28)
	{
		FPRINTF("[Line : %d][%s] nBucketCount value not correct. nBucketCount = [%d]\\n", __LINE__, API_NAMESPACE, nBucketCount);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Finds the index bucket for the given name and returns the number of that bucket.
/**
* @testcase				ITc_i18n_immutable_idx_get_bucket_index
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Given the name of a record, returns the index of the bucket in which the item should appear.
* @apitarget			i18n_immutable_idx_get_bucket_index
* @apicovered			i18n_immutable_idx_get_bucket_index
* @passcase				When i18n_immutable_idx_get_bucket_index successful
* @failcase				If target i18n_immutable_idx_get_bucket_index fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_immutable_idx_get_bucket_index(void)
{
	START_TEST;

	const char *pszItemName = "C";
    int32_t nBucketIndex = -1;

	int nRet = i18n_immutable_idx_get_bucket_index(g_immutableIndex, pszItemName, &nBucketIndex);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_get_bucket_index", BaseUtilsGetError(nRet));

	if(nBucketIndex != 3)
	{
		FPRINTF("[Line : %d][%s] nBucketIndex value not correct. nBucketIndex = [%d]\\n", __LINE__, API_NAMESPACE, nBucketIndex);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: Returns the label string of the index-th bucket.
/**
* @testcase				ITc_i18n_immutable_idx_get_bucket_label
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the name of the label of the bucket at given index.
* @apitarget			i18n_immutable_idx_get_bucket_label
* @apicovered			i18n_immutable_idx_get_bucket_label
* @passcase				When i18n_immutable_idx_get_bucket_label successful
* @failcase				If target i18n_immutable_idx_get_bucket_label fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_immutable_idx_get_bucket_label(void)
{
	START_TEST;
	int32_t nPosition = 3;
	char *pszLabel = NULL;

	int nRet = i18n_immutable_idx_get_bucket_label(g_immutableIndex, nPosition, &pszLabel);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_get_bucket_label", BaseUtilsGetError(nRet));
	CHECK_HANDLE(pszLabel, "i18n_immutable_idx_get_bucket_label");

	FREE_MEMORY(pszLabel);
	return 0;
}

//& type: auto
//& purpose: Returns the label type of the index-th bucket.
/**
* @testcase				ITc_i18n_immutable_idx_get_bucket_label_type
* @since_tizen 			5.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the type of the label for the index-th bucket.
* @apitarget			i18n_immutable_idx_get_bucket_label_type
* @apicovered			i18n_immutable_idx_get_bucket_label_type
* @passcase				When i18n_immutable_idx_get_bucket_label_type successful
* @failcase				If target i18n_immutable_idx_get_bucket_label_type fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_i18n_immutable_idx_get_bucket_label_type(void)
{
	START_TEST;

	i18n_alpha_idx_label_type_e eType = -1;
	int32_t nPosition = 0;

	int nRet =  i18n_immutable_idx_get_bucket_label_type(g_immutableIndex, nPosition, &eType);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_immutable_idx_get_bucket_label_type", BaseUtilsGetError(nRet));
	PRINT_RESULT(I18N_ALPHA_IDX_UNDERFLOW, eType, "i18n_immutable_idx_get_bucket_label_type", BaseUtilsGetError(nRet));

	return 0;
}

/** @} */
/** @} */
