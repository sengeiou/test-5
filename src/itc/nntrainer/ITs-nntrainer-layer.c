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

static ml_train_layer_h g_hMlTrainLayer;

//& set: Nntrainer

/** @addtogroup itc-nntrainer
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_nntrainer_layer_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_layer_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_nntrainer_layer_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsFeatureMismatched = false;
	g_bNntrainerCreation = false;
	g_bIsMLTrainFeatureSupported = TCTCheckSystemInfoFeatureSupported(ML_TRAIN_FEATURE, API_NAMESPACE);

	int nRet = ml_train_layer_create(&g_hMlTrainLayer, ML_TRAIN_LAYER_TYPE_INPUT);
	if(!g_bIsMLTrainFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ml_train_layer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_layer_create failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)", __FILE__, __LINE__, nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] ml_train_layer_create is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_layer_create is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != ML_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ml_train_layer_create failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] ml_train_layer_create failed, error returned = (%d)", __FILE__, __LINE__,  nRet);
		g_bNntrainerCreation = false;
	}
	else
	{
		g_bNntrainerCreation = true;
	}

	return;
}


/**
 * @function 		ITs_nntrainer_layer_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_nntrainer_layer_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_nntrainer_layer_cleanup\\n", __LINE__, API_NAMESPACE);
#endif

	if(g_hMlTrainLayer)
	{
		int nRet = ml_train_layer_destroy(g_hMlTrainLayer);
		PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_train_layer_destroy", NnTrainerGetError(nRet));
	}

	return;
}

/** @addtogroup itc-nntrainer-testcases
*  @brief 		Integration testcases for module nntrainer
*  @ingroup 	itc-nntrainer
*  @{
*/

//& purpose: To create and free a neural network layer.
//& type: auto
/**
* @testcase 			ITc_nntrainer_layer_create_destroy_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and frees a neural network layer.
*						Destroys neural network layer.
* @scenario				Create neural network layer.
* @apicovered			ml_train_layer_create, ml_train_layer_destroy
* @passcase				If ml_train_layer_create and ml_train_layer_destroy are successfull
* @failcase 			If ml_train_layer_create or ml_train_layer_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_layer_create_destroy_p(void)
{
	START_TEST;
	ml_train_layer_type_e eMlTrainLayerType[] = {
		ML_TRAIN_LAYER_TYPE_BN,
		ML_TRAIN_LAYER_TYPE_CONV2D,
		ML_TRAIN_LAYER_TYPE_POOLING2D,
		ML_TRAIN_LAYER_TYPE_FLATTEN,
		ML_TRAIN_LAYER_TYPE_ACTIVATION,
		ML_TRAIN_LAYER_TYPE_ADDITION,
		ML_TRAIN_LAYER_TYPE_CONCAT,
		ML_TRAIN_LAYER_TYPE_MULTIOUT,
		ML_TRAIN_LAYER_TYPE_INPUT,
		ML_TRAIN_LAYER_TYPE_FC,
		ML_TRAIN_LAYER_TYPE_EMBEDDING,
		ML_TRAIN_LAYER_TYPE_RNN,
		ML_TRAIN_LAYER_TYPE_LSTM,
		ML_TRAIN_LAYER_TYPE_SPLIT,
		ML_TRAIN_LAYER_TYPE_GRU,
		ML_TRAIN_LAYER_TYPE_PERMUTE,
		ML_TRAIN_LAYER_TYPE_DROPOUT,
		ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER,
		ML_TRAIN_LAYER_TYPE_CENTROID_KNN,
		ML_TRAIN_LAYER_TYPE_CONV1D,
		ML_TRAIN_LAYER_TYPE_LSTMCELL,
		ML_TRAIN_LAYER_TYPE_GRUCELL,
		ML_TRAIN_LAYER_TYPE_RNNCELL,
		ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL,
		ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP,
		ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE,
		ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM,
		ML_TRAIN_LAYER_TYPE_LOSS_MSE,
		ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID,
		ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX
	};

	int nEnumSize = sizeof(eMlTrainLayerType) / sizeof(eMlTrainLayerType[0]);
	ml_train_layer_h hMlTrainLayer = NULL;
	int nRet = -1;

	for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		nRet = ml_train_layer_create(&hMlTrainLayer, eMlTrainLayerType[nEnumCounter]);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_create", NnTrainerGetError(nRet));
		CHECK_HANDLE(hMlTrainLayer, "ml_train_layer_create");

		nRet = ml_train_layer_destroy(hMlTrainLayer);
		PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_destroy", NnTrainerGetError(nRet));
	}

	return 0;
}

//& purpose: To set the neural network layer Property.
//& type: auto
/**
* @testcase 			ITc_nntrainer_layer_set_property_p
* @since_tizen 			6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets the neural network layer Property.
* @scenario				Set neural network layer Property.
* @apicovered			ml_train_layer_set_property
* @passcase				If ml_train_layer_set_property is successfull
* @failcase 			If ml_train_layer_set_property fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_nntrainer_layer_set_property_p(void)
{
	START_TEST;

	 ml_train_layer_type_e eMlTrainLayerType[] = {
                 ML_TRAIN_LAYER_TYPE_BN,
                 ML_TRAIN_LAYER_TYPE_CONV2D,
                 ML_TRAIN_LAYER_TYPE_POOLING2D,
                 ML_TRAIN_LAYER_TYPE_ACTIVATION,
                 ML_TRAIN_LAYER_TYPE_ADDITION,
                 ML_TRAIN_LAYER_TYPE_CONCAT,
                 ML_TRAIN_LAYER_TYPE_MULTIOUT,
                 ML_TRAIN_LAYER_TYPE_INPUT,
                 ML_TRAIN_LAYER_TYPE_EMBEDDING,
                 ML_TRAIN_LAYER_TYPE_RNN,
                 ML_TRAIN_LAYER_TYPE_LSTM,
                 ML_TRAIN_LAYER_TYPE_SPLIT,
                 ML_TRAIN_LAYER_TYPE_GRU,
                 ML_TRAIN_LAYER_TYPE_PERMUTE,
                 ML_TRAIN_LAYER_TYPE_DROPOUT,
                 ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER,
                 ML_TRAIN_LAYER_TYPE_CENTROID_KNN,
                 ML_TRAIN_LAYER_TYPE_CONV1D,
                 ML_TRAIN_LAYER_TYPE_LSTMCELL,
                 ML_TRAIN_LAYER_TYPE_GRUCELL,
                 ML_TRAIN_LAYER_TYPE_RNNCELL,
                 ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL,
                 ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP,
                 ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE,
                 ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM,
                 ML_TRAIN_LAYER_TYPE_LOSS_MSE,
                 ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID,
                 ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX
         };

         int nEnumSize = sizeof(eMlTrainLayerType) / sizeof(eMlTrainLayerType[0]);
         ml_train_layer_h hMlTrainLayer = NULL;
         int nRet = -1;

         for (int nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
         {
                 nRet = ml_train_layer_create(&hMlTrainLayer, eMlTrainLayerType[nEnumCounter]);
                 PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_create", NnTrainerGetError(nRet));
                 CHECK_HANDLE(hMlTrainLayer, "ml_train_layer_create");

                 nRet = Set_Layer_Property(hMlTrainLayer,eMlTrainLayerType[nEnumCounter]);
                 PRINT_RESULT_CLEANUP(ML_ERROR_NONE, nRet, "ml_train_layer_set_property", NnTrainerGetError(nRet), ml_train_layer_destroy(hMlTrainLayer));

                 nRet = ml_train_layer_destroy(hMlTrainLayer);
                 PRINT_RESULT(ML_ERROR_NONE, nRet, "ml_train_layer_destroy", NnTrainerGetError(nRet));
                 hMlTrainLayer = NULL;
         }

	return 0;
}

/** @} */
/** @} */
