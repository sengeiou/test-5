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
#include "ITs-sound-pool-common.h"

/** @addtogroup itc-sound-pool
*  @ingroup itc
*  @{
*/

//Add helper function definitions here
char* SoundPoolGetError(int nRet)
{
	char *szErrorVal = "Undefined Error";

	switch ( nRet )
	{
		case SOUND_POOL_ERROR_NONE:					szErrorVal = "SOUND_POOL_ERROR_NONE";				break;
		case SOUND_POOL_ERROR_KEY_NOT_AVAILABLE:	szErrorVal = "SOUND_POOL_ERROR_KEY_NOT_AVAILABLE";	break;
		case SOUND_POOL_ERROR_OUT_OF_MEMORY:		szErrorVal = "SOUND_POOL_ERROR_OUT_OF_MEMORY";		break;
		case SOUND_POOL_ERROR_INVALID_PARAMETER:	szErrorVal = "SOUND_POOL_ERROR_INVALID_PARAMETER";	break;
		case SOUND_POOL_ERROR_INVALID_OPERATION:	szErrorVal = "SOUND_POOL_ERROR_INVALID_OPERATION";	break;
		case SOUND_POOL_ERROR_NOT_PERMITTED:		szErrorVal = "SOUND_POOL_ERROR_NOT_PERMITTED";		break;
		case SOUND_POOL_ERROR_NO_SUCH_FILE:			szErrorVal = "SOUND_POOL_ERROR_NO_SUCH_FILE";		break;
	}

	return szErrorVal;
}


/** @} */
