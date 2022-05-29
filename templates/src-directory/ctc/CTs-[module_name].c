//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "CTs-%{MODULE_NAME}-common.h"

/** @addtogroup ctc-%{MODULE_NAME}
* @ingroup		ctc
* @{
*/

//& set: %{MODULE_NAME_C}


/**
 * @function 		CTs_%{MODULE_NAME_U}_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_%{MODULE_NAME_U}_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	return;
}


/**
 * @function 		CTs_%{MODULE_NAME_U}_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void CTs_%{MODULE_NAME_U}_cleanup(void)
{
	return;
}


/** @addtogroup	ctc-%{MODULE_NAME}-testcases
* @brief 		Integration testcases for module %{MODULE_NAME}
* @ingroup		ctc-%{MODULE_NAME}
* @{
*/

//& purpose:
//& eType: auto
/**
 * @TCName	 				CTc_First_p
 * @TCType					Positive
 * @scenario
 * @api-covered
 * @pre-condition
 * @post-condition
 * @pass-case
 * @fail-case
 * @remarks
 */
int CTc_First_p(void)
{
    return 0;
}

/** @} */
/** @} */
