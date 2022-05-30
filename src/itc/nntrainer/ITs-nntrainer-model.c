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

static ml_train_model_h g_hMlTrainModel;

static int setBinDataPath(const char *pszFile, char *pPath)
{
	char *pszRootPath;
	pszRootPath = app_get_data_path();

	memset(pPath, 0, PATH_MAX);

	if (pszRootPath == NULL)
	{
		FPRINTF("[Line : %d][%s] failed to get data path\\n", __LINE__, API_NAMESPACE);
		return -1;
	}

	if (pPath == NULL)
	{
		FPRINTF("[Line : %d][%s] pPath is null\\n", __LINE__, API_NAMESPACE);
		free(pszRootPath);
		return -1;
	}

	snprintf(pPath, PATH_MAX, "%s%s", pszRootPath, pszFile);
	FPRINTF("[Line : %d][%s] data path: %s\\n", __LINE__, API_NAMESPACE,pPath);
	free(pszRootPath);

	return 0;
}
//& set: Nntrainer

/** @addtogroup itc-nntrainer
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_nntrainer_model_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_model_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nntrainer_model_startup\\n", __LINE__, API_NAMESPACE);
#endif

	char *pszResPath = app_get_resource_path();
	if (chdir(pszResPath) < 0)
	{
		FPRINTF("[Line : %d][%s] initiating path failed\\n", __LINE__, API_NAMESPACE);
	}
	FREE_MEMORY(pszResPath);

	g_bIsFeatureMismatched = false;
	g_bNntrainerCreation = false;
	g_bIsMLTrainFeatureSupported = TCTCheckSystemInfoFeatureSupported(ML_TRAIN_FEATURE, API_NAMESPACE);

	int nRet = ml_train_model_construct(&g_hMlTrainModel);
	if(!g_bIsMLTrainFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_train_model_construct failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_model_construct failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_train_model_construct is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_model_construct is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_train_model_construct failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_model_construct failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNntrainerCreation = false;
	}
	else
	{
		g_bNntrainerCreation = true;
	}

	return;
}


/**
 * @function 		ITs_nntrainer_model_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_model_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nntrainer_model_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hMlTrainModel)
	{

		int nRet = ml_train_model_destroy(g_hMlTrainModel);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));
	}

	return;
}

/** @addtogroup itc-nntrainer-testcases
*  @brief 		Integration testcases for module nntrainer
*  @ingroup 	itc-nntrainer
*  @{
*/

//& purpose: To construct and destruct the neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_construct_destroy_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Constructs and destructs the neural network model.
* @scenario				Constructs the neural network model.
*						Destructs the neural network model.
* @apicovered			ml_train_model_construct, ml_train_model_destroy
* @passcase				If ml_train_model_construct and ml_train_model_destroy are successfull
* @failcase 			If ml_train_model_construct or ml_train_model_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_construct_destroy_p(void)
{
	START_TEST;

	ml_train_model_h hMlTrainModel;
	int nRet = ml_train_model_construct(&hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct");

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To construct and destruct the neural network model with the given configuration file.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_construct_with_conf_destroy_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Constructs and destructs the neural network model with the given configuration file.
* @scenario				Constructs the neural network model with the given configuration file.
*						Destructs the neural network model.
* @apicovered			ml_train_model_construct_with_conf, ml_train_model_destroy
* @passcase				If ml_train_model_construct_with_conf and ml_train_model_destroy are successfull
* @failcase 			If ml_train_model_construct_with_conf or ml_train_model_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_construct_with_conf_destroy_p(void)
{
	START_TEST;

	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ml_train_model_h hMlTrainModel;
	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To add layer in neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_add_layer_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds layer in neural network model.
* @scenario				Add a layer to the model.
* @apicovered			ml_train_model_add_layer
* @passcase				If ml_train_model_add_layer is successfull
* @failcase 			If ml_train_model_add_layer fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_add_layer_p(void)
{
	START_TEST;

	ml_train_layer_h hMlTrainLayer;
	int nRet = ml_train_layer_create(&hMlTrainLayer, ML_TRAIN_LAYER_TYPE_INPUT);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_create", NnTrainerGetError(nRet));

	nRet = ml_train_layer_set_property(hMlTrainLayer, "input_shape=1:1:62720", "normalization=true", "standardization=true", NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_layer_set_property", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

	nRet = ml_train_model_add_layer(g_hMlTrainModel, hMlTrainLayer);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_add_layer", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

	nRet = ml_train_layer_destroy(hMlTrainLayer);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_layer_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To set the optimizer for the neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_set_optimizer_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the optimizer for the neural network model.
* @scenario				Set neural network optimizer.
* @apicovered			ml_train_model_set_optimizer
* @passcase				If ml_train_model_set_optimizer is successfull
* @failcase 			If ml_train_model_set_optimizer fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_set_optimizer_p(void)
{
	START_TEST;

	ml_train_optimizer_h hMlTrainOptimizer;
	int nRet = ml_train_optimizer_create(&hMlTrainOptimizer, ML_TRAIN_OPTIMIZER_TYPE_ADAM);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_optimizer_create", NnTrainerGetError(nRet));

	nRet = ml_train_optimizer_set_property(hMlTrainOptimizer, "learning_rate=0.0001", "decay_rate=0.96", "decay_steps=1000", "beta1=0.002", "beta2=0.001", "epsilon=1e-7", NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_optimizer_set_property", NnTrainerGetError(nRet), ml_train_optimizer_destroy(hMlTrainOptimizer));

	nRet = ml_train_model_set_optimizer(g_hMlTrainModel, hMlTrainOptimizer);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_set_optimizer", NnTrainerGetError(nRet), ml_train_optimizer_destroy(hMlTrainOptimizer));

	nRet = ml_train_optimizer_destroy(hMlTrainOptimizer);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_optimizer_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To set the dataset for the neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_set_dataset_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the dataset (data provider) for the neural network model.
* @scenario				Set dataset for running the model.
* @apicovered			ml_train_model_set_dataset
* @passcase				If ml_train_model_set_dataset is successfull
* @failcase 			If ml_train_model_set_dataset fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_set_dataset_p(void)
{
	START_TEST;

	char pszTrainingSetPath[PATH_LEN];
	if ( false == GetResourceDataPath(TRAININGSET_PATH, pszTrainingSetPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the training set path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ml_train_dataset_h hMlTrainDataset;
	int nRet = ml_train_dataset_create_with_file(&hMlTrainDataset, pszTrainingSetPath, NULL, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_dataset_create_with_file", NnTrainerGetError(nRet));

	nRet = ml_train_model_set_dataset(g_hMlTrainModel, hMlTrainDataset);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_set_optimizer", NnTrainerGetError(nRet), ml_train_dataset_destroy(hMlTrainDataset));

	nRet = ml_train_dataset_destroy(hMlTrainDataset);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_dataset_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To get the summary of the neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_get_summary_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the summary of the neural network model.
* @scenario				Get summary of the neural network model.
* @apicovered			ml_train_model_get_summary
* @passcase				If ml_train_model_get_summary is successfull
* @failcase 			If ml_train_model_get_summary fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_get_summary_p(void)
{
	START_TEST;

	ml_train_summary_type_e eMlTrainSummaryType[] = {
		ML_TRAIN_SUMMARY_MODEL,
		ML_TRAIN_SUMMARY_LAYER,
		ML_TRAIN_SUMMARY_TENSOR
	} ;

	int nEnumSize = sizeof(eMlTrainSummaryType) / sizeof(eMlTrainSummaryType[0]);

	ml_train_layer_h hMlTrainLayer;
	int nRet = ml_train_layer_create(&hMlTrainLayer, ML_TRAIN_LAYER_TYPE_INPUT);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_create", NnTrainerGetError(nRet));

	nRet = ml_train_layer_set_property(hMlTrainLayer, "input_shape=1:1:62720", "normalization=true", "standardization=true", NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_layer_set_property", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

	nRet = ml_train_model_add_layer(g_hMlTrainModel, hMlTrainLayer);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_add_layer", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

	nRet = ml_train_model_compile(g_hMlTrainModel, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet));

	char *pszSum = NULL;

	for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_train_model_get_summary(g_hMlTrainModel, eMlTrainSummaryType[nEnumCounter], &pszSum);
		PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_get_summary", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

		FREE_MEMORY(pszSum);
	}

	nRet = ml_train_layer_destroy(hMlTrainLayer);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_layer_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To compile and finalize the neural network model with the given loss.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_compile_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Compiles and finalizes the neural network model with the given loss.
* @scenario				Train the compiled neural network model with the passed training hyperparameters.
* @apicovered			ml_train_model_compile
* @passcase				If ml_train_model_compile is successfull
* @failcase 			If ml_train_model_compile fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_compile_p(void)
{
	START_TEST;

	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	ml_train_model_h hMlTrainModel;
	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_compile(hMlTrainModel, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: To train the neural network model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_run_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Trains the neural network model.
* @scenario				Trains the neural network model.
* @apicovered			ml_train_model_run
* @passcase				If ml_train_model_run is successfull
* @failcase 			If ml_train_model_run fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_run_p(void)
{
	START_TEST;

	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	char pszSaveProp[PATH_LEN];
	const char * pszDataPath = app_get_data_path();
	if ( snprintf(pszSaveProp, PATH_LEN, "save_path=%s%s", pszDataPath, "model.bin") < 0 ) {
		FPRINTF("[Line : %d][%s] unable to get the data path\\n", __LINE__, API_NAMESPACE);
		free((char *)pszDataPath);
		return 1;
	}
	free((char *)pszDataPath);

	ml_train_model_h hMlTrainModel;
	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_compile(hMlTrainModel, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet));

	nRet = ml_train_model_run(hMlTrainModel, pszSaveProp, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_run", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose:  Gets input tensors information of the model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_get_input_tensors_info_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets input tensors information of the model.
* @scenario				Gets input tensors information of the model.
* @apicovered			ml_train_model_get_input_tensors_info
* @passcase				If ml_train_model_get_input_tensors_info is successfull
* @failcase 			If ml_train_model_get_input_tensors_info fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_get_input_tensors_info_p(void)
{
	START_TEST;
	ml_tensors_info_h hInputInfo;
	ml_train_model_h hMlTrainModel;
	int nInputCount;

	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_compile(hMlTrainModel, NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet),ml_train_model_destroy(hMlTrainModel));

	nRet = ml_train_model_get_input_tensors_info(hMlTrainModel, &hInputInfo);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_get_input_tensors_info", NnTrainerGetError(nRet),ml_train_model_destroy(hMlTrainModel));
	CHECK_HANDLE_CLEANUP(hInputInfo, "ml_train_model_get_input_tensors_info",ml_train_model_destroy(hMlTrainModel));

	nRet = ml_tensors_info_get_count(hInputInfo, &nInputCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnTrainerGetError(nRet),ml_tensors_info_destroy(hInputInfo);	ml_train_model_destroy(hMlTrainModel));

	if(nInputCount < 0)
	{
		FPRINTF("[Line : %d][%s] nInputCount value is not correct\\n", __LINE__, API_NAMESPACE);
		ml_tensors_info_destroy(hInputInfo);
		ml_train_model_destroy(hMlTrainModel);
		return 1;
	}

	nRet = ml_tensors_info_destroy(hInputInfo);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: Gets output tensors information of the model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_get_output_tensors_info_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets output tensors information of the model.
* @scenario				Gets output tensors information of the model.
* @apicovered			ml_train_model_get_output_tensors_info
* @passcase				If ml_train_model_get_output_tensors_info is successfull
* @failcase 			If ml_train_model_get_output_tensors_info fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_get_output_tensors_info_p(void)
{
	START_TEST;
	static ml_tensors_info_h output_info;
	ml_train_model_h hMlTrainModel;
	unsigned int nOutputCount;

	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hMlTrainModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hMlTrainModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_compile(hMlTrainModel, NULL);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet),ml_train_model_destroy(hMlTrainModel));

	nRet = ml_train_model_get_output_tensors_info(hMlTrainModel, &output_info);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_model_get_output_tensors_info", NnTrainerGetError(nRet),ml_train_model_destroy(hMlTrainModel));

	nRet = ml_tensors_info_get_count(output_info, &nOutputCount);
	PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_tensors_info_get_count", NnTrainerGetError(nRet),ml_tensors_info_destroy(output_info);ml_train_model_destroy(hMlTrainModel));

	if(nOutputCount < 0)
	{
		FPRINTF("[Line : %d][%s] nOutputCount value is not correct\\n", __LINE__, API_NAMESPACE);
		ml_tensors_info_destroy(output_info);
		ml_train_model_destroy(hMlTrainModel);
		return 1;
	}

	nRet = ml_tensors_info_destroy(output_info);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hMlTrainModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}

//& purpose: Saves and  Loads the model.
//& type: auto
/**
* @testcase 			ITc_nntrainer_model_save_load_format_bin_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Saves and  Loads the model.
* @scenario				Saves and  Loads the model.
* @apicovered			ml_train_model_save,ml_train_model_load
* @passcase				If ml_train_model_save and ml_train_model_load are successfull
* @failcase 			If ml_train_model_save or ml_train_model_load fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_model_save_load_format_bin_p(void)
{
	START_TEST;
	ml_train_model_h hSaveModel, hLoadModel;
	char pszConfPath[PATH_LEN];
	if ( false == GetResourceDataPath(CONF_PATH, pszConfPath) )
	{
		FPRINTF("[Line : %d][%s] unable to get the conf path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	int nRet = ml_train_model_construct_with_conf(pszConfPath, &hSaveModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hSaveModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_construct_with_conf(pszConfPath, &hLoadModel);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_construct_with_conf", NnTrainerGetError(nRet));
	CHECK_HANDLE(hLoadModel, "ml_train_model_construct_with_conf");

	nRet = ml_train_model_compile(hSaveModel, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet));

	nRet = ml_train_model_compile(hLoadModel, NULL);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_compile", NnTrainerGetError(nRet));

	if (setBinDataPath(BIN_PATH, bin_path) < 0)
	{
		FPRINTF("[Line : %d][%s] Pat not set\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = ml_train_model_save(hSaveModel, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_save", NnTrainerGetError(nRet));

	nRet = ml_train_model_load(hLoadModel, bin_path, ML_TRAIN_MODEL_FORMAT_BIN);
	PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_model_load", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hSaveModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	nRet = ml_train_model_destroy(hLoadModel);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_model_destroy", NnTrainerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
