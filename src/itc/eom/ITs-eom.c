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

int g_bEomattributeChangecb = false;
int g_bEomModeChangecb = false;
int g_bEomOutputAdded = false;
int g_bEomOutputRemoved = false;
gboolean Timeout_Function(gpointer data);

/**
 * @function 		Timeout_Function
 * @description	 	Function for Timeout
 * @parameter		gpointer
 * @return 			true or false
 */
gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
 * @function 		eom_mode_changed_callback
 * @description	 	callback function for eom mode change
 * @parameter		External output manager id, user_data
 * @return 			NA
 */
static void eom_mode_changed_callback(eom_output_id output_id, void *user_data)
{
	g_bEomModeChangecb = true;
	FPRINTF("[Line : %d][%s] eom_mode_changed_callback invoked\\n", __LINE__, API_NAMESPACE);
	return;
}

/**
 * @function 		eom_attribute_changed_callback
 * @description	 	callback function for eom attribute change
 * @parameter		External output manager id, user_data
 * @return 			NA
 */
static void eom_attribute_changed_callback(eom_output_id output_id, void *user_data)
{
	g_bEomattributeChangecb = true;
	FPRINTF("[Line : %d][%s] eom_attribute_changed_callback invoked\\n", __LINE__, API_NAMESPACE);
	return;
}

/**
 * @function 		eom_set_output_added_callback
 * @description	 	callback function for eom output added
 * @parameter		External output manager id, user_data
 * @return 			NA
 */
static void eom_set_output_added_callback(eom_output_id output_id, void *user_data)
{
	g_bEomOutputAdded = true;
	FPRINTF("[Line : %d][%s] eom_set_output_added_callback invoked\\n", __LINE__, API_NAMESPACE);
	return;
}

/**
 * @function 		eom_set_output_removed_callback
 * @description	 	callback function for eom output removed
 * @parameter		External output manager id, user_data
 * @return 			NA
 */
static void eom_set_output_removed_callback(eom_output_id output_id, void *user_data)
{

	g_bEomOutputRemoved = true;
	FPRINTF("[Line : %d][%s] eom_set_output_removed_callback invoked\\n", __LINE__, API_NAMESPACE);
	return;
}

/**
 * @function 		ITs_eom_startup
 * @description		Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_eom_startup(void)
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
	int nRet = eom_init();
	if ( nRet != EOM_ERROR_NONE )
	{
		g_bEomInitialized = false;
		FPRINTF("[Line : %d][%s] eom_init failed in startup\\n", __LINE__, API_NAMESPACE);
	}
	return;
}

/**
 * @function 		ITs_eom_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_eom_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Eom_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bEomInitialized )
	{
		eom_deinit();
	}
	return;
}

/** @addtogroup itc-eom-testcases
 *  @brief 		Integration testcases for module eom
 *  @ingroup 	itc-eom
 *  @{
 */

//& type: auto
//& purpose: get eom output ids array.
/**
* @testcase				ITc_eom_get_output_id_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output ids array
* @scenario				Initialize eom\n
*						Get eom output ids
* @apicovered			eom_get_eom_output_ids
* @passcase				When eom_get_eom_output_ids is successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_id_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);

	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s] id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Get eom output type
/**
* @testcase				ITc_eom_get_output_type_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output type
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output type
* @apicovered			eom_get_eom_output_ids, eom_get_output_type
* @passcase				When eom_get_eom_output_ids and eom_get_output_type are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_type_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_type_e eType;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_type(output_ids[nEnumCounter], &eType);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_output_type", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Get eom output mode
/**
* @testcase				ITc_eom_get_output_mode_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output mode
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output mode
* @apicovered			eom_get_eom_output_ids, eom_get_output_mode
* @passcase				When eom_get_eom_output_ids and eom_get_output_mode are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_mode_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_mode_e mode;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_mode(output_ids[nEnumCounter], &mode);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_output_mode", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Set and get eom output attribute
/**
* @testcase				ITc_eom_get_set_output_attribute_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set and get eom output attribute
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Set output attribute\n
*						Get output attribute
* @apicovered			eom_get_eom_output_ids, eom_get_output_attribute, eom_set_output_attribute
* @passcase				When eom_get_eom_output_ids and eom_get_output_attribute, eom_set_output_attribute are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_set_output_attribute_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_attribute_e attribute[] = {
		EOM_OUTPUT_ATTRIBUTE_NORMAL,			/**< Normal presentation mode window showing on external output */
		EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE_SHARE,	/**< Exclusive share presentation mode window showing on external output */
		EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE,			/**< Exclusive presentation mode window showing on external output */
		EOM_OUTPUT_ATTRIBUTE_MAX
	};
	eom_output_attribute_e attribute1;
	eom_output_attribute_e attribute2;
	int nEnumCounter = 1;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(nIdCount ==0)
	{	
		FPRINTF("[Line : %d][%s] no external device avaialble \\n", __LINE__, API_NAMESPACE);
		return 0;
	}	

	for ( nEnumCounter=0;nEnumCounter<nIdCount;nEnumCounter++)
	{
		attribute1 = attribute[nEnumCounter];
		nRet = eom_set_output_attribute(output_ids[nEnumCounter], attribute1);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet,"eom_set_output_attribute", EomGetError(nRet), FREE_MEMORY(output_ids));
		sleep(2);

		nRet = eom_get_output_attribute(output_ids[nEnumCounter], &attribute2);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, " eom_get_output_attribute", EomGetError(nRet), FREE_MEMORY(output_ids));
		if ( attribute2 != attribute1 )
		{
			FPRINTF("[Line : %d][%s] eom_get_output_attribute return value %s mismatch with attribute %s set using eom_set_output_attribute\\n",
				__LINE__, API_NAMESPACE, EomGetAttribute(attribute2), EomGetAttribute(attribute1));
			FREE_MEMORY(output_ids);
			return 1;
		}
	}

	FREE_MEMORY(output_ids);
	return 0;
}

//& type: auto
//& purpose: Get eom output attribute state
/**
* @testcase				ITc_eom_get_output_attribute_state_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output attribute state
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output attribute state
* @apicovered			eom_get_eom_output_ids, eom_get_output_attribute_state
* @passcase				When eom_get_eom_output_ids and eom_get_output_attribute_state are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_attribute_state_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_attribute_state_e eState;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_attribute_state(output_ids[nEnumCounter], &eState);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_output_attribute_state", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Get eom output resolution
/**
* @testcase				ITc_eom_get_output_resolution_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output resolution
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output resolution
* @apicovered			eom_get_eom_output_ids, eom_get_output_resolution
* @passcase				When eom_get_eom_output_ids and eom_get_output_resolution are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_resolution_p(void)
{
	START_TEST;

	int nIdCount = -1;
	int nWidth = 0;
	int nHeight = 0;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_resolution(output_ids[nEnumCounter], &nWidth, &nHeight);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_output_resolution", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Get eom output physical size
/**
* @testcase				ITc_eom_get_output_physical_size_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Get eom output physical size
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output physical size
* @passcase				When eom_get_eom_output_ids and eom_get_output_physical_size are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_get_output_physical_size_p(void)
{
	START_TEST;

	int nIdCount = -1;
	int nPhyWidth = 0;
	int nPhyHeight = 0;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_physical_size(output_ids[nEnumCounter], &nPhyWidth,&nPhyHeight);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "om_get_output_physical_size", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Set eom output window
/**
* @testcase				ITc_eom_set_output_window_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set eom output window
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Set output attribute\n
*						Set output window
* @apicovered			eom_get_eom_output_ids, eom_set_output_window, eom_set_output_attribute
* @passcase				When eom_get_eom_output_ids and eom_set_output_window are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_set_output_window_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_attribute_e attribute = EOM_OUTPUT_ATTRIBUTE_NORMAL;
	int nEnumCounter = 0;

	Evas_Object *win = elm_win_add(NULL, "output_window", ELM_WIN_BASIC);
	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_set_output_attribute(output_ids[nEnumCounter], attribute);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_set_output_attribute", EomGetError(nRet), FREE_MEMORY(output_ids));
		
		nRet = eom_set_output_window(output_ids[nEnumCounter], win);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_set_output_window", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Set and unset the attribute changed callback
/**
* @testcase				ITc_eom_set_unset_attribute_changed_cb_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set and unset the attribute changed callback
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Set attribute changed callback\n
*						Unset attribute changed callback
* @apicovered			eom_unset_attribute_changed_cb, eom_set_attribute_changed_cb
* @passcase				When   eom_set_attribute_changed_cb and eom_unset_attribute_changed_cb are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_set_unset_attribute_changed_cb_p(void)
{
	START_TEST;

	int nRet = eom_set_attribute_changed_cb(eom_attribute_changed_callback,NULL);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, "eom_set_attribute_changed_cb", EomGetError(nRet));

	nRet = eom_unset_attribute_changed_cb(eom_attribute_changed_callback);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, "eom_unset_attribute_changed_cb", EomGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and unset the output mode changed callback
/**
* @testcase				ITc_eom_set_unset_mode_changed_cb_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set and unset the output mode changed callback
* @scenario				Initialize eom\n
*						Get eom output ids\n
*						Get output mode\n
*						Set mode changed callback\n
*						Unset mode changed callback
* @apicovered			eom_set_mode_changed_cb, eom_unset_mode_changed_cb
* @passcase				When eom_set_mode_changed_cb , eom_unset_mode_changed_cb are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_set_unset_mode_changed_cb_p(void)
{
	START_TEST;

	int nIdCount = -1;
	eom_output_mode_e eMode;
	int nEnumCounter = 0;

	eom_output_id* output_ids = eom_get_eom_output_ids(&nIdCount);
	int nRet = get_last_result();
	PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_eom_output_ids", EomGetError(nRet), FREE_MEMORY(output_ids));
	if ( nIdCount == -1 )
	{
		FPRINTF("[Line : %d][%s]  id count is not updated\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	for ( nEnumCounter=0; nEnumCounter<nIdCount; nEnumCounter++ )
	{
		nRet = eom_get_output_mode(output_ids[nEnumCounter], &eMode);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_get_output_mode", EomGetError(nRet), FREE_MEMORY(output_ids));

		nRet = eom_set_mode_changed_cb(eom_mode_changed_callback,NULL);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_set_mode_changed_cb", EomGetError(nRet), FREE_MEMORY(output_ids));

		g_bEomModeChangecb = false;
		nRet = eom_unset_mode_changed_cb(eom_mode_changed_callback);
		PRINT_RESULT_CLEANUP(EOM_ERROR_NONE, nRet, "eom_unset_mode_changed_cb", EomGetError(nRet), FREE_MEMORY(output_ids));
	}
	FREE_MEMORY(output_ids);

	return 0;
}

//& type: auto
//& purpose: Set and unset the output added callback
/**
* @testcase				ITc_eom_set_unset_output_added_cb_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set and unset the output added callback
* @scenario				Initialize eom\n
*						Set output added callback\n
*						Unset output added callback
* @apicovered			 eom_set_output_added_cb, eom_unset_output_added_cb
* @passcase				When eom_unset_output_added_cb and eom_set_output_added_cb are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_set_unset_output_added_cb_p(void)
{
	START_TEST;

	int nRet = eom_set_output_added_cb(eom_set_output_added_callback, NULL);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, " eom_set_output_added_cb", EomGetError(nRet));

	nRet = eom_unset_output_added_cb(eom_set_output_added_callback);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, "eom_unset_output_added_cb", EomGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set and unset the output removed callback
/**
* @testcase				ITc_eom_set_unset_output_removed_cb_p
* @since_tizen			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Set and unset the output removed callback
* @scenario				Initialize eom\n
*						Set output removed changed callback\n
*						Unset output removed changed callback
* @apicovered			eom_set_output_removed_cb,eom_unset_output_removed_cb
* @passcase				When eom_unset_output_removed_cb and eom_set_output_removed_cb are successful
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_eom_set_unset_output_removed_cb_p(void)
{
	START_TEST;

	int nRet = eom_set_output_removed_cb(eom_set_output_removed_callback, NULL);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, " eom_set_output_removed_cb", EomGetError(nRet));

	nRet = eom_unset_output_removed_cb(eom_set_output_removed_callback);
	PRINT_RESULT(EOM_ERROR_NONE, nRet, "eom_unset_output_removed_cb", EomGetError(nRet));

	return 0;
}

/** @} */
/** @} */
