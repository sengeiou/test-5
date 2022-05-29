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
#include "CTs-sound-manager-common.h"

/** @addtogroup ctc-sound-manager
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 		SoundManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SoundManagerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SOUND_MANAGER_ERROR_NONE :					szErrorVal = "SOUND_MANAGER_ERROR_NONE" ;			 	break; 
	case SOUND_MANAGER_ERROR_OUT_OF_MEMORY :		szErrorVal = "SOUND_MANAGER_ERROR_OUT_OF_MEMORY" ;		break; 
	case SOUND_MANAGER_ERROR_INVALID_PARAMETER :	szErrorVal = "SOUND_MANAGER_ERROR_INVALID_PARAMETER" ;	break; 
	case SOUND_MANAGER_ERROR_INVALID_OPERATION :	szErrorVal = "SOUND_MANAGER_ERROR_INVALID_OPERATION" ;	break;
	case SOUND_MANAGER_ERROR_PERMISSION_DENIED :	szErrorVal = "SOUND_MANAGER_ERROR_PERMISSION_DENIED" ;	break;
	case SOUND_MANAGER_ERROR_NOT_SUPPORTED :		szErrorVal = "SOUND_MANAGER_ERROR_NOT_SUPPORTED" ;		break;
	case SOUND_MANAGER_ERROR_NO_DATA :				szErrorVal = "SOUND_MANAGER_ERROR_NO_DATA" ;			break;
	case SOUND_MANAGER_ERROR_NO_PLAYING_SOUND :		szErrorVal = "SOUND_MANAGER_ERROR_NO_PLAYING_SOUND" ;	break;
	case SOUND_MANAGER_ERROR_INTERNAL :				szErrorVal = "SOUND_MANAGER_ERROR_INTERNAL" ;			break;
	case SOUND_MANAGER_ERROR_POLICY :				szErrorVal = "SOUND_MANAGER_ERROR_POLICY" ;				break;
	default :										szErrorVal = "UNKNOWN" ;								break;
	}
	return szErrorVal;
}

/** @} */ //end of ctc-sound-manager