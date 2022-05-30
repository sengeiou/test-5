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
#include "ITs-nntrainer-common.h"

/** @addtogroup itc-nntrainer
*  @ingroup itc
*  @{
*/

/**
* @function 		NnTrainerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* NnTrainerGetError(int nRet)
{
	char *szErrorVal = "Unknown error code";
	switch ( nRet )
	{
		case ML_ERROR_NONE:				szErrorVal = "ML_ERROR_NONE";					break;
		case ML_ERROR_INVALID_PARAMETER:	szErrorVal = "ML_ERROR_INVALID_PARAMETER";	break;
		case ML_ERROR_STREAMS_PIPE:	szErrorVal = "ML_ERROR_STREAMS_PIPE";	break;
		case ML_ERROR_TRY_AGAIN:	szErrorVal = "ML_ERROR_TRY_AGAIN";	break;
		case ML_ERROR_UNKNOWN:	szErrorVal = "ML_ERROR_UNKNOWN";	break;
		case ML_ERROR_TIMED_OUT:	szErrorVal = "ML_ERROR_TIMED_OUT";	break;
		case ML_ERROR_NOT_SUPPORTED:		szErrorVal = "ML_ERROR_NOT_SUPPORTED";		break;
		case ML_ERROR_PERMISSION_DENIED:	szErrorVal = "ML_ERROR_PERMISSION_DENIED";	break;
		case ML_ERROR_OUT_OF_MEMORY:	szErrorVal = "ML_ERROR_OUT_OF_MEMORY";	break;
	}

	return szErrorVal;
}

/**
* @function 		GetResourceDataPath
* @description	 	Gets the resource data path
* @parameter		const char *pFilePath, const char *pFinalPath
* @return 			bool
*/
bool GetResourceDataPath(const char *pFilePath, const char *pFinalPath)
{
	if ( NULL == pFilePath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_resource_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get resource data path; app_get_resource_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	snprintf(pFinalPath, PATH_LEN, "%s%s", pPath, pFilePath);

	FPRINTF("[Line : %d][%s] resource data path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

/**
* @function 		Set_Layer_Property
* @description	 	sets the layer property
* @parameter		ml_train_layer_h hTrainLayer, int nLayerEnum
* @return 			int
*/
int Set_Layer_Property(ml_train_layer_h hTrainLayer, int nLayerEnum)
{
	int nRet = -1;
	switch ( nLayerEnum )
	{
		case ML_TRAIN_LAYER_TYPE_INPUT:
										nRet = ml_train_layer_set_property(hTrainLayer , "input_shape=1:1:6270", "normalization=true", "standardization=true", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_BN:
										nRet = ml_train_layer_set_property(hTrainLayer , "name=bn", "epsilon=0.001", "moving_mean_initializer=zeros",
                                       "moving_variance_initializer=ones", "gamma_initializer=zeros",
                                       "beta_initializer=ones", "momentum=0.9", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_CONV2D:
										nRet = ml_train_layer_set_property(hTrainLayer , "filters=3", "kernel_size=2, 2", "stride=1,1", "padding=0, 0", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_POOLING2D:
										nRet = ml_train_layer_set_property(hTrainLayer , "pooling=max", "pool_size=1, 1", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_ACTIVATION:
										nRet = ml_train_layer_set_property(hTrainLayer , "activation=relu", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_ADDITION:
										nRet = ml_train_layer_set_property(hTrainLayer , "name=addition", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_CONCAT:
										nRet = ml_train_layer_set_property(hTrainLayer , "name=concat", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_MULTIOUT:
										nRet = ml_train_layer_set_property(hTrainLayer , "name=multiout", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_EMBEDDING:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=embedding", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_RNN:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=rnn", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_LSTM:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=lstm", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_SPLIT:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=split", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_GRU:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=gru", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_PERMUTE:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=permute", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_DROPOUT:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=dropout", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_BACKBONE_NNSTREAMER:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=backbone_nnstreamer", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_CENTROID_KNN:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=centroid_knn", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_CONV1D:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=conv1d", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_LSTMCELL:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=lstmcell", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_GRUCELL:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=grucell", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_RNNCELL:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=rnncell", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_ZONEOUTLSTMCELL:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=zoneoutlstmcell", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_PREPROCESS_FLIP:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=preprocess_flip", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_PREPROCESS_TRANSLATE:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=preprocess_translate", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_PREPROCESS_L2NORM:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=preprocess_l2norm", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_LOSS_MSE:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=loss_mse", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SIGMOID:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=loss_cross_entropy_sigmoid", NULL);
										break;
		case ML_TRAIN_LAYER_TYPE_LOSS_CROSS_ENTROPY_SOFTMAX:
										nRet = ml_train_layer_set_property(hTrainLayer, "name=loss_cross_entropy_softmax", NULL);
										break;
	}

	return nRet;

}

/** @} */
