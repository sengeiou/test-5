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
#include "ITs-%{MODULE_NAME}-common.h"

//& set: %{MODULE_NAME_C}

/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_%{MODULE_NAME_U}_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_%{MODULE_NAME_U}_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	return;
}


/**
 * @function 		ITs_%{MODULE_NAME_U}_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_%{MODULE_NAME_U}_cleanup(void)
{
	return;
}

/** @addtogroup itc-%{MODULE_NAME}-testcases
*  @brief 		Integration testcases for module %{MODULE_NAME}
*  @ingroup 	itc-%{MODULE_NAME}
*  @{
*/

//& purpose: A purpose of a first positive TC.
int ITc_First_p(void)
{
    return 0;
}

//& purpose: A purpose of a first negative TC.
int ITc_First_n(void)
{
    return 0;
}

/** @} */
/** @} */
