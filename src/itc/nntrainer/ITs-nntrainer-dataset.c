//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-nntrainer-common.h"

static ml_train_dataset_h g_hDataset;

//& set: Nntrainer

/** @addtogroup itc-nntrainer
*  @ingroup itc
*  @{
*/

/**
* @function			ConstantGeneratorCB
* @description		Callback function
* @parameter[IN]	float **outVec, float **outLabel, bool *last, void *user_data
* @return			NA
*/
static int ConstantGeneratorCB(float **outVec, float **outLabel, bool *last, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ConstantGeneratorCB is called\\n", __LINE__, API_NAMESPACE);
#endif

	static int count = 0;
	unsigned int i;
	unsigned int data_size = FEATURE_SIZE;

	for (i = 0; i < data_size; ++i) {
		outVec[0][i] = 1;
	}

	outLabel[0][0] = 1;

	if (count == 5) {
		*last = true;
		count = 0;
	} else {
		*last = false;
		count++;
	}

	g_CallBackHit = true;

	return ML_ERROR_NONE;
}

/**
 * @function 		ITs_nntrainer_dataset_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_dataset_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nntrainer_dataset_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureMismatched = false;
	g_bNntrainerCreation = false;
	g_bIsMLTrainFeatureSupported = TCTCheckSystemInfoFeatureSupported(ML_TRAIN_FEATURE, API_NAMESPACE);

	char pszValSetPath[PATH_LEN];
	char pszTrainingSetPath[PATH_LEN];
	char pszTestSetPath[PATH_LEN];

	if ( false == GetResourceDataPath(TRAININGSET_PATH, pszTrainingSetPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the training set path\\n", __LINE__, API_NAMESPACE);
	}

	if ( false == GetResourceDataPath(VALSET_PATH, pszValSetPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the val set path\\n", __LINE__, API_NAMESPACE);
	}

	if ( false == GetResourceDataPath(TESTSET_PATH, pszTestSetPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the test set path\\n", __LINE__, API_NAMESPACE);
	}

	int nRet = ml_train_dataset_create(&g_hDataset);
	if(!g_bIsMLTrainFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_train_dataset_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_dataset_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_train_dataset_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_dataset_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_train_dataset_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_dataset_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNntrainerCreation = false;
	}
	if(g_hDataset == NULL)
	{
		FPRINTF("[%s:%d] ml_train_dataset_create failed, handle is null\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_dataset_create failed, handle is null", __FILE__, __LINE__);
		g_bNntrainerCreation = false;
	}
	else
	{
		g_bNntrainerCreation = true;
	}

	return;
}


/**
 * @function 		ITs_nntrainer_dataset_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_dataset_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nntrainer_dataset_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hDataset)
	{
		int nRet = ml_train_dataset_destroy(g_hDataset);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_dataset_destroy", NnTrainerGetError(nRet));
	}

	return;
}

/** @addtogroup itc-nntrainer-testcases
*  @brief 		Integration testcases for module nntrainer
*  @ingroup 	itc-nntrainer
*  @{
*/

//& purpose: Constructs and destroy the dataset.
//& type: auto
/**
* @testcase 			ITc_nntrainer_dataset_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Constructs and destroy the dataset.
* @scenario				Constructs and destroy the dataset.
* @apicovered			ml_train_dataset_create,ml_train_dataset_destroy
* @passcase				If ml_train_dataset_create and ml_train_dataset_destroy are successfull
* @failcase 			If ml_train_dataset_create or ml_train_dataset_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_dataset_create_destroy_p(void)
{
	START_TEST;

	int nRet = ml_train_dataset_destroy(g_hDataset);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_destroy", NnTrainerGetError(nRet));

	nRet = ml_train_dataset_create(&g_hDataset);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_create", NnTrainerGetError(nRet));
	CHECK_HANDLE(g_hDataset, "ml_train_dataset_create");

	return 0;
}

//& purpose:  Adds data generator callback to dataset.
//& type: auto
/**
* @testcase 			ITc_nntrainer_dataset_add_generator_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds data generator callback to dataset.
* @scenario				Adds data generator callback to dataset.
* @apicovered			ml_train_dataset_add_generator
* @passcase				If ml_train_dataset_add_generator is successfull
* @failcase 			If ml_train_dataset_add_generator fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_dataset_add_generator_p(void)
{
	START_TEST;

	int nRet = -1;
	ml_train_dataset_mode_e eDatasetMode[3] = {ML_TRAIN_DATASET_MODE_TRAIN, ML_TRAIN_DATASET_MODE_VALID, ML_TRAIN_DATASET_MODE_TEST};
	int nEnumSize = sizeof(eDatasetMode) / sizeof(eDatasetMode[0]);
 
	for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_train_dataset_add_generator(g_hDataset, eDatasetMode[nEnumCounter], ConstantGeneratorCB, NULL);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_add_generator", NnTrainerGetError(nRet));
	}

	return 0;
}

//& purpose:  Adds data file to dataset.
//& type: auto
/**
* @testcase 			ITc_nntrainer_dataset_add_file_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds data file to dataset.
* @scenario				Adds data file to dataset.
* @apicovered			ml_train_dataset_add_file
* @passcase				If ml_train_dataset_add_file is successfull
* @failcase 			If ml_train_dataset_add_file fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_dataset_add_file_p(void)
{
	START_TEST;

	int nRet = -1;
	ml_train_dataset_h hDataset;
	char pszTrainingSetPath[PATH_LEN];

	if ( false == GetResourceDataPath(TRAININGSET_PATH, pszTrainingSetPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the training set path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ml_train_dataset_mode_e eDatasetMode[3] = {ML_TRAIN_DATASET_MODE_TRAIN, ML_TRAIN_DATASET_MODE_VALID, ML_TRAIN_DATASET_MODE_TEST};
	int nEnumSize = sizeof(eDatasetMode) / sizeof(eDatasetMode[0]);

	for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_train_dataset_add_file(g_hDataset, eDatasetMode[nEnumCounter], pszTrainingSetPath);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_add_file", NnTrainerGetError(nRet));
	}

	return 0;
}

//& purpose: Sets the neural network dataset property.
//& type: auto
/**
* @testcase 			ITc_nntrainer_dataset_set_property_for_mode_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the neural network dataset property.
* @scenario				Sets the neural network dataset property.
* @apicovered			ml_train_dataset_set_property_for_mode
* @passcase				If ml_train_dataset_set_property_for_mode is successfull
* @failcase 			If ml_train_dataset_set_property_for_mode fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_dataset_set_property_for_mode_p(void)
{
	START_TEST;

	int nRet = ml_train_dataset_add_generator(g_hDataset, ML_TRAIN_DATASET_MODE_TRAIN, ConstantGeneratorCB, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_add_generator", NnTrainerGetError(nRet));

	nRet = ml_train_dataset_set_property_for_mode(g_hDataset, ML_TRAIN_DATASET_MODE_TRAIN, "buffer_size=1", NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_set_property_for_mode", NnTrainerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
