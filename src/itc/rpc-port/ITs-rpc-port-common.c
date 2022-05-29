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
#include "ITs-rpc-port-common.h"

/** @addtogroup itc-rpc-port
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		RpcPortGetError
* @description	 	Maps dlog_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* RpcPortGetError(int nErrorType)
{
	char *szErrorVal = "Unknown Error";
	switch ( nErrorType )
	{
		case RPC_PORT_ERROR_NONE:				szErrorVal = "RPC_PORT_ERROR_NONE";					break;
		case RPC_PORT_ERROR_INVALID_PARAMETER:	szErrorVal = "RPC_PORT_ERROR_INVALID_PARAMETER";	break;
		case RPC_PORT_ERROR_OUT_OF_MEMORY:		szErrorVal = "RPC_PORT_ERROR_OUT_OF_MEMORY";		break;
		case RPC_PORT_ERROR_PERMISSION_DENIED:	szErrorVal = "RPC_PORT_ERROR_PERMISSION_DENIED";	break;
		case RPC_PORT_ERROR_IO_ERROR:			szErrorVal = "RPC_PORT_ERROR_IO_ERROR";				break;
	}

	return szErrorVal;
}

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
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
 * @function 		GetFilePath
 * @description	 	Gets the file path
 * @parameter		const char *pszFileName, char *pszBuf, unsigned int nSize
 * @return 			void
 */
void GetFilePath(const char *pszFileName, char *pszBuf, unsigned int nSize)
{
	char *pszDataPath;
	pszDataPath = app_get_data_path();

	snprintf(pszBuf, nSize, "%s%s", pszDataPath, pszFileName);
}

/**
 * @function 		CreateFile
 * @description	 	Creates the file
 * @parameter		const char *pszFilePath, const char *pszMessage
 * @return 			void
 */
void CreateFile(const char *pszFilePath, const char *pszMessage)
{
	FILE * fp = fopen (pszFilePath, "w+");

	if (fp)
	{
		fprintf(fp, pszMessage);
		fclose(fp);
	}
}

/** @} */
