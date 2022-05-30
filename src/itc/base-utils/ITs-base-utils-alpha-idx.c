#include "ITs-base-utils-common.h"

i18n_alpha_idx_h g_index = NULL;

/** @addtogroup itc-base-utils
*  @ingroup itc
*  @{
*/

//& set: BaseUtilsUstring

/**
* @function 		ITs_base_utils_ustring_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_base_utils_alpha_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	const char *pszLocalId = "en_US";
	bool available;
	g_bBaseUtilsInitFlag = true;
	int record_data = 7;
	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	int nRet = i18n_alpha_idx_create_from_locale_id(pszLocalId, &g_index);
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_create_from_locale_id: failed\\n", __LINE__, API_NAMESPACE);
	}

	nRet = i18n_alpha_idx_add_labels_with_locale_id(g_index, pszLocalId);
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_add_labels_with_locale_id: failed\\n", __LINE__, API_NAMESPACE);
	}

    nRet = i18n_alpha_idx_add_record(g_index, "AAA", &record_data);
    if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_add_record: failed\\n", __LINE__, API_NAMESPACE);
	}

    nRet = i18n_alpha_idx_get_next_bucket(g_index, &available);
    if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_get_next_bucket: failed\\n", __LINE__, API_NAMESPACE);
	}
    
	nRet = i18n_alpha_idx_get_next_bucket(g_index, &available);
    if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_get_next_bucket: failed\\n", __LINE__, API_NAMESPACE);
	}
	
    nRet = i18n_alpha_idx_get_next_record(g_index, &available);
	if(nRet != I18N_ERROR_NONE)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_get_next_record: failed\\n", __LINE__, API_NAMESPACE);
	}
	
	else if(g_index == NULL)
	{
		g_bBaseUtilsInitFlag = false;
		FPRINTF("[Line : %d][%s] g_index is null\\n", __LINE__, API_NAMESPACE);
	}
	
	return;
}

/**
* @function 		ITs_base_utils_ustring_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_base_utils_alpha_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Base_Utils_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bBaseUtilsInitFlag = false;
	int nRet = i18n_alpha_idx_destroy(g_index); 
	if(nRet != I18N_ERROR_NONE)
	{	
		FPRINTF("[Line : %d][%s] TEST SUIT i18n_alpha_idx_destroy: failed\\n", __LINE__, API_NAMESPACE);
	}

	return;
}



//& type: auto
//& purpose: Creates an alphabetic index object for the specified locale.
/**
* @testcase				ITc_i18n_alpha_idx_create_destroy_from_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Creates an alphabetic index object for the specified locale.
* @apitarget			i18n_alpha_idx_create_from_locale_id, i18n_alpha_idx_destroy
* @apicovered			i18n_alpha_idx_create_from_locale_id, i18n_alpha_idx_destroy
* @passcase				When i18n_alpha_idx_create_from_locale_id, i18n_alpha_idx_destroy successful
* @failcase				If target i18n_alpha_idx_create_from_locale_id, i18n_alpha_idx_destroy fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_create_destroy_from_locale_id_p(void)
{	
	START_TEST;
	
	const char *pszLocalId = "en_US";
	i18n_alpha_idx_h index = NULL;
	
	int nRet = i18n_alpha_idx_create_from_locale_id(pszLocalId, &index);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_create_from_locale_id", BaseUtilsGetError(nRet));
	
	nRet = i18n_alpha_idx_destroy(index); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_destroy", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Adds the index characters from a specified locale to the index
/**
* @testcase				ITc_i18n_alpha_idx_add_labels_with_locale_id_p
* @since_tizen 			5.0
* @author            	SRID(shilpa.j)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Adds the index characters from a specified locale to the index
* @apitarget			i18n_alpha_idx_add_labels_with_locale_id
* @apicovered			i18n_alpha_idx_add_labels_with_locale_id
* @passcase				When i18n_alpha_idx_add_labels_with_locale_id successful
* @failcase				If target i18n_alpha_idx_add_labels_with_locale_id fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_add_labels_with_locale_id_p(void)
{	
	START_TEST;
	
	const char *pszLocalId = "en_US";

	int nRet = i18n_alpha_idx_add_labels_with_locale_id(g_index, pszLocalId);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_add_labels_with_locale_id", BaseUtilsGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Adds the record to the alphabetic index and Gets the name of the current record.
/**
* @testcase				ITc_i18n_alpha_idx_add_record_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Adds the record to the alphabetic index and Gets the name of the current record.
* @apitarget			i18n_alpha_idx_add_record 
* @apicovered			i18n_alpha_idx_add_record
* @passcase				When i18n_alpha_idx_add_record  successful
* @failcase				If target i18n_alpha_idx_add_record fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_add_record_p(void)
{	
	START_TEST;
	const char *pRecordName = "RecordName";
	char *pData =  (void *)"Data";
	
	int nRet = i18n_alpha_idx_add_record(g_index, pRecordName, pData);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_add_record", BaseUtilsGetError(nRet));
		
	return 0;
}

//& type: auto
//& purpose: Gets the name of the current record.
/**
* @testcase				ITc_i18n_alpha_idx_get_record_name_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the name of the current record.
* @apitarget			i18n_alpha_idx_get_record_name
* @apicovered			i18n_alpha_idx_get_record_name
* @passcase				When  i18n_alpha_idx_get_record_name successful
* @failcase				If target i18n_alpha_idx_get_record_name fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_record_name_p(void)
{	
	START_TEST;
	char *pGetRecordName =  NULL;
	
	int nRet = i18n_alpha_idx_get_record_name(g_index, &pGetRecordName); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_record_name", BaseUtilsGetError(nRet));
	
	if ( pGetRecordName == NULL )
	{
		FPRINTF("[Line : %d][%s] no record found\\n", __LINE__, API_NAMESPACE);	
		return 1;		
	}
	else
	{
		FREE_MEMORY(pGetRecordName);			
	}
	
	return 0;
}

//& type: auto
//& purpose: Sets the next bucket as current bucket in the index
/**
* @testcase				ITc_i18n_alpha_idx_get_next_bucket_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets the next bucket as current bucket in the index
* @apitarget			i18n_alpha_idx_get_next_bucket
* @apicovered			i18n_alpha_idx_get_next_bucket
* @passcase				When i18n_alpha_idx_get_next_bucket successful
* @failcase				If target i18n_alpha_idx_get_next_bucket fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_next_bucket_p(void)
{	
	START_TEST;
	bool available;
	
	int nRet = i18n_alpha_idx_get_next_bucket(g_index, &available); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_next_bucket", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Gets the next record as current record in current bucket of the index
/**
* @testcase				ITc_i18n_alpha_idx_get_next_record_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				ets the next record as current record in current bucket of the index
* @apitarget			i18n_alpha_idx_get_next_record, i18n_alpha_idx_reset_record_iter
* @apicovered			i18n_alpha_idx_get_next_record, i18n_alpha_idx_reset_record_iter
* @passcase				When i18n_alpha_idx_get_next_record, i18n_alpha_idx_reset_record_iter successful
* @failcase				If target i18n_alpha_idx_get_next_record, i18n_alpha_idx_reset_record_iter fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_next_record_p(void)
{	
	START_TEST;
	bool available;
	
	int nRet = i18n_alpha_idx_reset_record_iter(g_index);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_reset_record_iter", BaseUtilsGetError(nRet));
	
	nRet = i18n_alpha_idx_get_next_record(g_index, &available); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_next_record", BaseUtilsGetError(nRet));
	
	if(available)
	{
		FPRINTF("[Line : %d][%s] next record was available\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		FPRINTF("[Line : %d][%s] there were no more records.\\n", __LINE__, API_NAMESPACE);
	}
	return 0;
}

//& type: auto
//& purpose: Gets the number of <name, data> records in the current bucket.
/**
* @testcase				ITc_i18n_alpha_idx_get_bucket_record_count_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the number of <name, data> records in the current bucket.
* @apitarget			i18n_alpha_idx_get_bucket_record_count
* @apicovered			i18n_alpha_idx_get_bucket_record_count
* @passcase				When i18n_alpha_idx_get_bucket_record_count successful
* @failcase				If target i18n_alpha_idx_get_bucket_record_count fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_bucket_record_count_p(void)
{	
	START_TEST;
	int32_t nRecordsCount = -1;
	
	int nRet = i18n_alpha_idx_get_bucket_record_count(g_index, &nRecordsCount); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_bucket_record_count", BaseUtilsGetError(nRet));
	
	if(nRecordsCount == -1)
	{
		FPRINTF("[Line : %d][%s] nRecordsCount value returned is not correct\\n", __LINE__, API_NAMESPACE);	
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nRecordsCount = [%d]\\n", __LINE__, API_NAMESPACE, nRecordsCount);	
	}
	return 0;
}

//& type: auto
//& purpose: Gets the name of the label of the current bucket in alphabetic index.
/**
* @testcase				ITc_i18n_alpha_idx_get_bucket_label_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the name of the label of the current bucket in alphabetic index.
* @apitarget			i18n_alpha_idx_get_bucket_label
* @apicovered			i18n_alpha_idx_get_bucket_label
* @passcase				When i18n_alpha_idx_get_bucket_label successful
* @failcase				If target i18n_alpha_idx_get_bucket_label fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_bucket_label_p(void)
{	
	START_TEST;
	char *pLabel = NULL;
	
	int nRet = i18n_alpha_idx_get_bucket_label(g_index, &pLabel); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_bucket_label", BaseUtilsGetError(nRet));
	
	if(pLabel == NULL)
	{
		FPRINTF("[Line : %d][%s] pLabel value is not correct\\n", __LINE__, API_NAMESPACE);
		return 1;		
	}
	else
	{
		FPRINTF("[Line : %d][%s] pLabel = [%s]\\n", __LINE__, API_NAMESPACE, pLabel);	
		FREE_MEMORY(pLabel);	
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the data of the current record in a current bucket in alphabetic index.
/**
* @testcase				ITc_i18n_alpha_idx_get_record_data_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the data of the current record in a current bucket in alphabetic index.
* @apitarget			i18n_alpha_idx_get_record_data
* @apicovered			i18n_alpha_idx_get_record_data
* @passcase				When i18n_alpha_idx_get_record_data successful
* @failcase				If target i18n_alpha_idx_get_record_data fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_record_data_p(void)
{	
	START_TEST;
	void *pData = NULL;
	
	pData = i18n_alpha_idx_get_record_data(g_index); 
	int nRet = get_last_result();
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_record_data", BaseUtilsGetError(nRet));
		
	return 0;
}

//& type: auto
//& purpose: Set/Gets the default label used for abbreviated buckets between other index characters
/**
* @testcase				ITc_i18n_alpha_idx_set_get_inflow_label_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Set/Gets the default label used for abbreviated buckets between other index characters
* @apitarget			i18n_alpha_idx_get_inflow_label, i18n_alpha_idx_get_inflow_label
* @apicovered			i18n_alpha_idx_get_inflow_label, i18n_alpha_idx_get_inflow_label
* @passcase				When i18n_alpha_idx_get_inflow_label, i18n_alpha_idx_get_inflow_label successful
* @failcase				If target i18n_alpha_idx_get_inflow_label, i18n_alpha_idx_get_inflow_label fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_set_get_inflow_label_p(void)
{	
	START_TEST;
	char *pGetLabel = NULL;
	const char *pLabel = "Test string";
	 
	int nRet = i18n_alpha_idx_set_inflow_label(g_index, pLabel);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_set_inflow_label", BaseUtilsGetError(nRet));
		
	nRet = i18n_alpha_idx_get_inflow_label(g_index, &pGetLabel); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_inflow_label", BaseUtilsGetError(nRet));
	
	if( strcmp(pGetLabel , pLabel) != 0)
	{
		FPRINTF("[Line : %d][%s] pGetLabel value is not correct\\n", __LINE__, API_NAMESPACE);
		return 1;		
	}
	else
	{
		FPRINTF("[Line : %d][%s] pGetLabel = [%s]\\n", __LINE__, API_NAMESPACE, pGetLabel);
		FREE_MEMORY(pGetLabel);	
	}
	
	return 0;
}

//& type: auto
//& purpose: Set/Gets the special label used for items that sort after the last normal label
/**
* @testcase				ITc_i18n_alpha_idx_set_get_overflow_label_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Set/Gets the special label used for items that sort after the last normal label
* @apitarget			i18n_alpha_idx_get_overflow_label,i18n_alpha_idx_set_overflow_label
* @apicovered			i18n_alpha_idx_get_overflow_label,i18n_alpha_idx_set_overflow_label
* @passcase				When i18n_alpha_idx_get_overflow_label, i18n_alpha_idx_set_overflow_label successful
* @failcase				If target i18n_alpha_idx_get_overflow_label,i18n_alpha_idx_set_overflow_label fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_set_get_overflow_label_p(void)
{	
	START_TEST;
	char *pGetLabel = NULL;
	const char *pLabel = "Test string";
	
	int nRet = i18n_alpha_idx_set_overflow_label(g_index, pLabel);
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_set_overflow_label", BaseUtilsGetError(nRet));
	
	
	nRet = i18n_alpha_idx_get_overflow_label(g_index, &pGetLabel); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_overflow_label", BaseUtilsGetError(nRet));
	
	if( strcmp(pGetLabel , pLabel) != 0)
	{
		FPRINTF("[Line : %d][%s] pGetLabel value is not correct\\n", __LINE__, API_NAMESPACE);
		return 1;		
	}
	else
	{
		FPRINTF("[Line : %d][%s] pGetLabel = [%s]\\n", __LINE__, API_NAMESPACE, pGetLabel);	
		FREE_MEMORY(pGetLabel);	
	}
	
	return 0;
}

//& type: auto
//& purpose: Set/Gets the special label used for items that sort before the first normal label,
/**
* @testcase				ITc_i18n_alpha_idx_set_get_underflow_label_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Set/Gets the special label used for items that sort before the first normal label,
* @apitarget			i18n_alpha_idx_get_underflow_label,i18n_alpha_idx_set_underflow_label
* @apicovered			i18n_alpha_idx_get_underflow_label, i18n_alpha_idx_set_underflow_label
* @passcase				When i18n_alpha_idx_get_underflow_label, i18n_alpha_idx_set_underflow_label successful
* @failcase				If target i18n_alpha_idx_get_underflow_label, i18n_alpha_idx_set_underflow_label fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_set_get_underflow_label_p(void)
{	
	START_TEST;
	char *pGetLabel = NULL;
	const char *pLabel = "test";
	
	int nRet = i18n_alpha_idx_set_underflow_label(g_index, pLabel); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_set_underflow_label", BaseUtilsGetError(nRet));
	
	nRet = i18n_alpha_idx_get_underflow_label(g_index, &pGetLabel); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_underflow_label", BaseUtilsGetError(nRet));
	
	if( strcmp(pGetLabel , pLabel) != 0)
	{
		FPRINTF("[Line : %d][%s] pGetLabel value is not correct\\n", __LINE__, API_NAMESPACE);FREE_MEMORY(pGetLabel);
		FREE_MEMORY(pGetLabel);	
		return 1;		
	}
	else
	{
		FPRINTF("[Line : %d][%s] pGetLabel = [%s]\\n", __LINE__, API_NAMESPACE, pGetLabel);
		FREE_MEMORY(pGetLabel);	
	}
	
	return 0;
}

//& type: auto
//& purpose: Sets/Gets a limit on the number of labels permitted in the index
/**
* @testcase				ITc_i18n_alpha_idx_set_get_max_label_count_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Sets/Gets a limit on the number of labels permitted in the index
* @apitarget			i18n_alpha_idx_get_max_label_count,i18n_alpha_idx_set_max_label_count
* @apicovered			i18n_alpha_idx_get_max_label_count, i18n_alpha_idx_set_max_label_count
* @passcase				When i18n_alpha_idx_get_max_label_count, i18n_alpha_idx_set_max_label_count successful
* @failcase				If target i18n_alpha_idx_get_max_label_count, i18n_alpha_idx_set_max_label_count fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_set_get_max_label_count_p(void)
{	
	START_TEST;
	
	int32_t nMaxLabelCount = 10;
	int32_t nGetMaxLabelCount = -1;
	 
	int nRet = i18n_alpha_idx_set_max_label_count(g_index, nMaxLabelCount); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_set_max_label_count", BaseUtilsGetError(nRet));
	
	nRet = i18n_alpha_idx_get_max_label_count(g_index, &nGetMaxLabelCount); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_max_label_count", BaseUtilsGetError(nRet));
	
	if( nMaxLabelCount != nGetMaxLabelCount)
	{
		FPRINTF("[Line : %d][%s] nGetMaxLabelCount value is not correct\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else
	{
		FPRINTF("[Line : %d][%s] nGetMaxLabelCount = [%d]\\n", __LINE__, API_NAMESPACE, nGetMaxLabelCount);
	}
	
	return 0;
}

//& type: auto
//& purpose: Gets the number of labels in this index
/**
* @testcase				ITc_i18n_alpha_idx_get_bucket_count_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the number of labels in this index
* @apitarget			i18n_alpha_idx_get_bucket_count
* @apicovered			i18n_alpha_idx_get_bucket_count
* @passcase				When i18n_alpha_idx_get_bucket_count successful
* @failcase				If target i18n_alpha_idx_get_bucket_count fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_bucket_count_p(void)
{	
	START_TEST;
	
	int32_t nBucketCount;
	 
	int nRet = i18n_alpha_idx_get_bucket_count(g_index, &nBucketCount); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_bucket_count", BaseUtilsGetError(nRet));
	
	FPRINTF("[Line : %d][%s] nBucketCount = [%d]\\n", __LINE__, API_NAMESPACE, nBucketCount);	
	
	return 0;
}

//& type: auto
//& purpose:  Gets the total number of records in this index, that is, the number of <name, data> pairs added.
/**
* @testcase				ITc_i18n_alpha_idx_get_record_count_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the total number of records in this index, that is, the number of <name, data> pairs added.
* @apitarget			i18n_alpha_idx_get_record_count
* @apicovered			i18n_alpha_idx_get_record_count
* @passcase				When i18n_alpha_idx_get_record_count successful
* @failcase				If target i18n_alpha_idx_get_record_count fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_record_count_p(void)
{	
	START_TEST;
	
	int32_t nRecordCount;
	 
	int nRet = i18n_alpha_idx_get_record_count(g_index, &nRecordCount); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_record_count", BaseUtilsGetError(nRet));
	
	FPRINTF("[Line : %d][%s] nRecordCount = [%d]\\n", __LINE__, API_NAMESPACE, nRecordCount);	
	
	return 0;
}

//& type: auto
//& purpose: Given the name of a record, returns the zero-based index of the bucket in which the item should appear.
/**
* @testcase				ITc_i18n_alpha_idx_get_bucket_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Given the name of a record, returns the zero-based index of the bucket in which the item should appear.
* @apitarget			i18n_alpha_idx_get_bucket_index
* @apicovered			i18n_alpha_idx_get_bucket_index
* @passcase				When i18n_alpha_idx_get_bucket_index successful
* @failcase				If target i18n_alpha_idx_get_bucket_index fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_bucket_index_p(void)
{	
	START_TEST;
	
	const char *pItemName = "Test string";
    int32_t nBucketIndex;
	 
	int nRet = i18n_alpha_idx_get_bucket_index(g_index, pItemName, &nBucketIndex); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_bucket_index", BaseUtilsGetError(nRet));
	
	FPRINTF("[Line : %d][%s] nBucketIndex = [%d]\\n", __LINE__, API_NAMESPACE, nBucketIndex);	
	
	return 0;
}

//& type: auto
//& purpose: Gets the zero based index of the current bucket of this index.
/**
* @testcase				ITc_i18n_alpha_idx_get_current_bucket_index_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the zero based index of the current bucket of this index.
* @apitarget			i18n_alpha_idx_get_current_bucket_index
* @apicovered			i18n_alpha_idx_get_current_bucket_index
* @passcase				When i18n_alpha_idx_get_current_bucket_index successful
* @failcase				If target i18n_alpha_idx_get_current_bucket_index fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_current_bucket_index_p(void)
{	
	START_TEST;
	
	int32_t nBucketIndex;
	 
	int nRet = i18n_alpha_idx_get_current_bucket_index(g_index, &nBucketIndex); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_current_bucket_index", BaseUtilsGetError(nRet));
	
	FPRINTF("[Line : %d][%s] nBucketIndex = [%d]\\n", __LINE__, API_NAMESPACE, nBucketIndex);	
	
	return 0;
}

//& type: auto
//& purpose: Gets the type of the label for the current Bucket
/**
* @testcase				ITc_i18n_alpha_idx_get_bucket_label_type_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Gets the type of the label for the current Bucket
* @apitarget			i18n_alpha_idx_get_bucket_label_type
* @apicovered			i18n_alpha_idx_get_bucket_label_type
* @passcase				When i18n_alpha_idx_get_bucket_label_type successful
* @failcase				If target i18n_alpha_idx_get_bucket_label_type fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_get_bucket_label_type_p(void)
{	
	START_TEST;
	
	i18n_alpha_idx_label_type_e eType;
	 
	int nRet = i18n_alpha_idx_get_bucket_label_type(g_index, &eType); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_get_bucket_label_type", BaseUtilsGetError(nRet));
	
	FPRINTF("[Line : %d][%s] eType = [%d]\\n", __LINE__, API_NAMESPACE, eType);	
	
	return 0;
}

//& type: auto
//& purpose: Resets the bucket iteration for this index.
/**
* @testcase				ITc_i18n_alpha_idx_reset_bucket_iter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Resets the bucket iteration for this index.
* @apitarget			i18n_alpha_idx_reset_bucket_iter
* @apicovered			i18n_alpha_idx_reset_bucket_iter
* @passcase				When i18n_alpha_idx_reset_bucket_iter successful
* @failcase				If target i18n_alpha_idx_reset_bucket_iter fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_reset_bucket_iter_p(void)
{	
	START_TEST;
	
	int nRet = i18n_alpha_idx_reset_bucket_iter(g_index); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_reset_bucket_iter", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Resets the record iteration for this index to before the first Record in the current Bucket.
/**
* @testcase				ITc_i18n_alpha_idx_reset_record_iter_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Resets the record iteration for this index to before the first Record in the current Bucket.
* @apitarget			i18n_alpha_idx_reset_record_iter
* @apicovered			i18n_alpha_idx_reset_record_iter
* @passcase				When i18n_alpha_idx_reset_record_iter successful
* @failcase				If target i18n_alpha_idx_reset_record_iter fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_reset_record_iter_p(void)
{	
	START_TEST;
	
	int nRet = i18n_alpha_idx_reset_record_iter(g_index); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_reset_record_iter", BaseUtilsGetError(nRet));
	
	return 0;
}

//& type: auto
//& purpose: Remove all records from the index
/**
* @testcase				ITc_i18n_alpha_idx_clear_records_p
* @since_tizen 			3.0
* @author            	SRID(gaurav.m2)
* @reviewer         	SRID(a.pandia1)
* @type 				auto
* @scenario				Remove all records from the index
* @apitarget			i18n_alpha_idx_clear_records
* @apicovered			i18n_alpha_idx_clear_records
* @passcase				When i18n_alpha_idx_clear_records successful
* @failcase				If target i18n_alpha_idx_clear_records fails or any precondition and postcondition API fails.
* @precondition			NA
* @postcondition		NA 
*/
int ITc_i18n_alpha_idx_clear_records_p(void)
{	
	START_TEST;
	
	int nRet = i18n_alpha_idx_clear_records(g_index); 
	PRINT_RESULT(I18N_ERROR_NONE, nRet, "i18n_alpha_idx_clear_records", BaseUtilsGetError(nRet));
		
	return 0;
}

/** @} */
/** @} */