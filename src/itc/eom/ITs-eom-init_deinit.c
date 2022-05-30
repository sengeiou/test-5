//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
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
#include "ITs-eom-common.h"

//& set: Eom

/** @addtogroup itc-eom
 *  @ingroup itc
 *  @{
 */

/**
 * @function 		ITs_eom_init_deinit_startup
 * @description		Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_eom_init_deinit_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Eom_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bEomInitialized = true;
	return;
}

/**
 * @function 		ITs_eom_init_deinit_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_eom_init_deinit_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Eom_p\\n", __LINE__, API_NAMESPACE);
#endif
	if(g_bEomInitialized == true )
	{
		g_bEomInitialized = false;
	}
	return;
}

/** @addtogroup itc-eom-testcases
 *  @brief 		Integration testcases for module eom
 *  @ingroup 	itc-eom
 *  @{
 */

//& type: auto
//& purpose:initialize and deinitialize eom.
/**
* @testcase				ITc_eom_output_init_deinit_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Initialize and deinitialize eom
* @scenario				Initialize eom\n
*						Deinitialize eom
* @apicovered			eom_init, eom_deinit
* @passcase				When eom_init and eom_deinit are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_output_init_deinit_p(void)
{
	START_TEST;
	g_bEomInitialized = true;
	int nRet = EOM_ERROR_NONE;
	nRet = eom_init();
	PRINT_RESULT(EOM_ERROR_NONE, nRet, "eom_init failed", EomGetError(nRet));

	eom_deinit();
	return 0;
}


