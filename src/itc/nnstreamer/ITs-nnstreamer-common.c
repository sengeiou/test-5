//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-nnstreamer-common.h"

/** @addtogroup itc-nnstreamer
*  @ingroup itc
*  @{
*/

//Add Common enum


//Add helper function definitions here

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}

	return false;
}

/**
* @function 		NnStreamerGetError
* @description	 	Maps ml_error_e enums
* @parameter		error : error level
* @return 			error string
*/

char* NnStreamerGetError(int nRet)
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

void FreeCustomTensorMemory(gchar **t_pszNnpipeline,guint **t_unsinkCount,gchar ***t_psz_fullpath,gchar **t_psz_file)
{
	g_free (*t_pszNnpipeline);
	g_free (*t_unsinkCount);
	g_free (*t_psz_fullpath);
	g_free (*t_psz_file);
}

void TensorInfoDataDestroy(ml_tensors_info_h hTensorinfo,ml_tensors_data_h hTensorData)
{
	int nRet = -1;
	nRet = ml_tensors_info_destroy (hTensorinfo);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));
	nRet = ml_tensors_data_destroy (hTensorData);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_data_destroy", NnStreamerGetError(nRet));
}

void TensorInfoPipelineStop(ml_pipeline_h hPipelinehandle,ml_pipeline_src_h hPipeSrcHandle, ml_pipeline_sink_h hPipeSinkHandle,ml_tensors_info_h hTensorinfo)
{
	int nRet = -1;
	nRet = ml_pipeline_stop (hPipelinehandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_stop", NnStreamerGetError(nRet));
	nRet = ml_pipeline_src_release_handle (hPipeSrcHandle);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_src_release_handle", NnStreamerGetError(nRet));
	nRet = ml_pipeline_sink_unregister (hPipeSinkHandle); 
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_pipeline_sink_unregister", NnStreamerGetError(nRet));
	nRet = ml_tensors_info_destroy (hTensorinfo);
	PRINT_RESULT_NORETURN(ML_ERROR_NONE, nRet, "ml_tensors_info_destroy", NnStreamerGetError(nRet));
}
/** @} */
