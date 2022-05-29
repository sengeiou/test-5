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

static ml_train_optimizer_h g_hMlTrainOptimizer;

//& set: Nntrainer

/** @addtogroup itc-nntrainer
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_nntrainer_optimizer_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_optimizer_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nntrainer_optimizer_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureMismatched = false;
	g_bNntrainerCreation = false;
	g_bIsMLTrainFeatureSupported = TCTCheckSystemInfoFeatureSupported(ML_TRAIN_FEATURE, API_NAMESPACE);

	int nRet = ml_train_optimizer_create(&g_hMlTrainOptimizer, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
	if(!g_bIsMLTrainFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_train_optimizer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_optimizer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_train_optimizer_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_optimizer_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_train_optimizer_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_optimizer_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNntrainerCreation = false;
	}
	else
	{
		g_bNntrainerCreation = true;
	}

	return;
}


/**
 * @function 		ITs_nntrainer_optimizer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_optimizer_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nntrainer_optimizer_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hMlTrainOptimizer)
	{
		int nRet = ml_train_optimizer_destroy(g_hMlTrainOptimizer);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_optimizer_destroy", NnTrainerGetError(nRet));
	}

	return;
}

/** @addtogroup itc-nntrainer-testcases
*  @brief 		Integration testcases for module nntrainer
*  @ingroup 	itc-nntrainer
*  @{
*/

//& purpose: To create and free a neural network optimizer.
//& type: auto
/**
* @testcase 			ITc_nntrainer_optimizer_create_destroy_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and frees a neural network optimizer.
*						Destroys neural network optimizer.
* @scenario				Create neural network optimizer.
* @apicovered			ml_train_optimizer_create, ml_train_optimizer_destroy
* @passcase				If ml_train_optimizer_create and ml_train_optimizer_destroy are successfull
* @failcase 			If ml_train_optimizer_create or ml_train_optimizer_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_optimizer_create_destroy_p(void)
{
	START_TEST;

	ml_train_optimizer_type_e eMlTrainOptimizerType[] = {
		ML_TRAIN_OPTIMIZER_TYPE_ADAM,
		ML_TRAIN_OPTIMIZER_TYPE_SGD
	};

	int nEnumSize = sizeof(eMlTrainOptimizerType) / sizeof(eMlTrainOptimizerType[0]);
	ml_train_optimizer_h hMlTrainOptimizer = NULL;
	int nRet = -1;

	for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_train_optimizer_create(&hMlTrainOptimizer, eMlTrainOptimizerType[nEnumCounter]);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_optimizer_create", NnTrainerGetError(nRet));
		CHECK_HANDLE(hMlTrainOptimizer, "ml_train_optimizer_create");

		nRet = ml_train_optimizer_destroy(hMlTrainOptimizer);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_optimizer_destroy", NnTrainerGetError(nRet));
	}

	return 0;
}

//& purpose: To set the neural network optimizer property.
//& type: auto
/**
* @testcase 			ITc_nntrainer_optimizer_set_property_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the neural network optimizer property.
* @scenario				Set neural network optimizer property.
* @apicovered			ml_train_optimizer_set_property
* @passcase				If ml_train_optimizer_set_property is successfull
* @failcase 			If ml_train_optimizer_set_property fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_optimizer_set_property_p(void)
{
	START_TEST;

	int nRet = ml_train_optimizer_set_property(g_hMlTrainOptimizer, "beta1=0.002", "beta2=0.001", NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_optimizer_set_property", NnTrainerGetError(nRet));

	return 0;
}

/** @} */
/** @} */
