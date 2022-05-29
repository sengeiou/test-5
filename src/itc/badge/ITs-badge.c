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
#include "ITs-badge-common.h"

/** @addtogroup itc-badge
*  @ingroup itc
*  @{
*/

//& set: Badge

/****************************************************Callback Start****************************************************/

/**
 * @function 		BadgeForeachCallBack
 * @description	 	Callback Function
 * @parameter		const char *app_id, unsigned int count, void *user_data
 * @return 			NA
 */
static bool BadgeForeachCallBack(const char *app_id, unsigned int count, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "BadgeForeachCallBack");
#endif

	g_bCallBackHit = true;
	return false;
}

/**
 * @function 		BadgeChangedCallBack
 * @description	 	Callback Function
 * @parameter		unsigned int action, const char *app_id, unsigned int count, void *user_data
 * @return 			NA
 */
static void BadgeChangedCallBack(unsigned int action, const char *app_id, unsigned int count, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] %s Callback Invoked\\n", __LINE__, API_NAMESPACE, "BadgeChangedCallBack");
#endif

	g_bCallBackHit = true;
	QuitGmainLoop();
	return;
}

/*****************************************************Callback End*****************************************************/

bool g_bBadgeInit = false;

/**
* @function 		ITs_badge_startup
* @description	 	Called before each test, creates a badge for the application itself.
* @parameter		NA
* @return 			NA
*/
void ITs_badge_startup(void)
{
	g_bBadgeInit = false;
	g_bBadgeNotSupported = false;
	g_bBadgeMismatch = false;
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Badge_p\\n", __LINE__, API_NAMESPACE);
#endif

	//badge_app_id, the id of the application for which the badge to be created, can be null when creating a badge for itself
	badge_error_e eRetValue = badge_add(/*BADGE_PACKAGE*/NULL);
	bool bFeatureBadge  = TCTCheckSystemInfoFeatureSupported(BADGE_FEATURE, API_NAMESPACE);

	if(!bFeatureBadge)
	{
		if(eRetValue == BADGE_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] badge_add() returned %s error for unsupported feature :success \\n", __LINE__,
				API_NAMESPACE, BadgeGetError(eRetValue));
			g_bBadgeNotSupported = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] badge_add() returned %s error for unsupported feature, error mismatch :Failure \\n",
			 __LINE__, API_NAMESPACE, BadgeGetError(eRetValue));
			g_bBadgeMismatch = true;
		}

		return;
	}

	if ( eRetValue == BADGE_ERROR_NONE || eRetValue == BADGE_ERROR_ALREADY_EXIST )
	{
		FPRINTF("[Line : %d] [%s] badge_add succeeded in startup\\n", __LINE__, API_NAMESPACE);
		g_bBadgeInit = true;
	}
	else
	{
		FPRINTF("[Line : %d] [%s] badge_add failed in startup, error = %s\\n", __LINE__, API_NAMESPACE, BadgeGetError(eRetValue));
		g_bBadgeInit = false;
	}
}

/**
* @function 		ITs_badge_cleanup
* @description	 	Called after each test, removes the created badge for the application
* @parameter		NA
* @return 			NA
*/
void ITs_badge_cleanup(void)
{
	if ( g_bBadgeInit )
	{
		badge_error_e eRetValue = badge_remove(BADGE_PACKAGE);
		if ( eRetValue == BADGE_ERROR_NONE )
		{
			FPRINTF("[Line : %d] [%s] badge_remove succeeded in cleanup\\n", __LINE__, API_NAMESPACE);
		}
		else
		{
			FPRINTF("[Line : %d] [%s] badge_remove failed in cleanup, error = %s\\n", __LINE__, API_NAMESPACE, BadgeGetError(eRetValue));
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Badge_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/** @addtogroup itc-badge-testcases
*  @brief 		Integration testcases for module badge
*  @ingroup 	itc-badge
*  @{
*/
//& type: auto
//& purpose: to create and remove a badge
/**
* @testcase 			ITc_badge_new_remove_p
* @since_tizen			2.3
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To create and remove a badge
* @scenario				Remove the badge created in startup\n
* 						Create a badge\n
* 						Remove badge\n
* 						Create a badge
* @apicovered			badge_new, badge_remove
* @passcase				If badge_new, badge_remove returns success
* @failcase				If badge_new, badge_remove returns false
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_new_remove_p(void)
{
	START_TEST;
	badge_error_e eRetValue = BADGE_ERROR_NONE;

	//Remove already created badge in startup
	eRetValue = badge_remove(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_remove", BadgeGetError(eRetValue));

	// Target API
	eRetValue = badge_new(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_new", BadgeGetError(eRetValue));

	// Target API
	eRetValue = badge_remove(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_remove", BadgeGetError(eRetValue));

	//Create badge again to be removed in cleanup
	eRetValue = badge_new(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_new", BadgeGetError(eRetValue));
	return 0;
}

//& type: auto
//& purpose: to create and remove a badge
/**
* @testcase 			ITc_badge_add_remove_p
* @since_tizen			2.4
* @author				SRID(saurabh.s9)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To create and remove a badge
* @scenario				Remove the badge created in startup\n
* 						Create a badge\n
* 						Remove badge\n
* 						Create a badge
* @apicovered			badge_add, badge_remove
* @passcase				If badge_add, badge_remove returns success
* @failcase				If badge_add, badge_remove returns false
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_add_remove_p(void)
{
	START_TEST;
	badge_error_e eRetValue = BADGE_ERROR_NONE;

	//Remove already created badge in startup
	eRetValue = badge_remove(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_remove", BadgeGetError(eRetValue));

	// Target API
	//badge_app_id, the id of the application for which the badge to be created, can be null when creating a badge for itself
	eRetValue = badge_add(/*BADGE_PACKAGE*/NULL);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_add", BadgeGetError(eRetValue));

	// Target API
	eRetValue = badge_remove(BADGE_PACKAGE);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_remove", BadgeGetError(eRetValue));

	//Create badge again to be removed in cleanup
	//badge_app_id, the id of the application for which the badge to be created, can be null when creating a badge for itself
	eRetValue = badge_add(/*BADGE_PACKAGE*/NULL);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_add", BadgeGetError(eRetValue));
	return 0;
}

//& type: auto
//& purpose: to set and get badge count for the designated package
/**
* @testcase 			ITc_badge_set_get_count_p
* @since_tizen			2.3
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To set and get badge count for the designated package
* @scenario				Set badge count for the designated package\n
* 						Get badge count for the designated package\n
* 						Compare set and get values
* @apicovered			badge_set_count, badge_get_count
* @passcase				If badge_set_count, badge_get_count returns success and set get values are same
* @failcase				If either badge_set_count or badge_get_count returns false or set get values are not same
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_set_get_count_p(void)
{
	START_TEST;

	unsigned int unSetCount = 2, unGetCount = 0;
	badge_error_e eRetValue = BADGE_ERROR_NONE;

	// Target API
	eRetValue = badge_set_count(BADGE_PACKAGE, unSetCount);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_set_count", BadgeGetError(eRetValue));

	// Target API
	eRetValue = badge_get_count(BADGE_PACKAGE, &unGetCount);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_get_count", BadgeGetError(eRetValue));

	if ( unGetCount != unSetCount )
	{
		FPRINTF("[Line : %d] [%s] badge_get_count failed , error returned = get and set values are not same\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: to set and get the display option for the designated package.
/**
* @testcase 			ITc_badge_set_get_display_p
* @since_tizen			2.3
* @author            	SRID(saurabh.s9)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To set and get the display option for the designated package.
* @scenario				Set the display option for the designated package\n
* 						Get the display option for the designated package\n
* 						Compare set and get values
* @apicovered			badge_set_display, badge_get_display
* @passcase				If badge_set_display, badge_get_display returns success and set get values are same
* @failcase				If either badge_set_display or badge_get_display returns false or set get values are not same
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_set_get_display_p(void)
{
	START_TEST;
	badge_error_e eRetValue = BADGE_ERROR_NONE;
	unsigned int unSetDisplay = 1, unGetDisplay = 0;

	// Target API
	eRetValue =  badge_set_display(BADGE_PACKAGE, unSetDisplay);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_set_display", BadgeGetError(eRetValue));

	// Target API
	eRetValue = badge_get_display(BADGE_PACKAGE, &unGetDisplay);
	PRINT_RESULT(BADGE_ERROR_NONE, eRetValue, "badge_get_display", BadgeGetError(eRetValue));
	if ( unGetDisplay != unSetDisplay )
	{
		FPRINTF("[Line : %d] [%s] badge_get_display failed , error returned = get and set values are not same\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& type: auto
//& purpose: To Test badge_foreach
/**
* @testcase 			ITc_badge_foreach_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To Test badge_foreach
* @scenario				Call badge_foreach
* @apicovered			badge_foreach
* @passcase				If badge_foreach returns success and set get values are same
* @failcase				If target api or precondition api fails
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_foreach_p(void)
{
	START_TEST;
	int nRet = -1;

	g_bCallBackHit = false;
	nRet = badge_foreach(BadgeForeachCallBack, NULL);
	PRINT_RESULT(BADGE_ERROR_NONE, nRet, "badge_foreach", BadgeGetError(nRet));
	PRINT_RESULT(true, g_bCallBackHit, "badge_foreach", "CallBack Not Invoked");

	return 0;
}

//& type: auto
//& purpose: To Test badge_register_changed_cb and badge_unregister_changed_cb
/**
* @testcase 			ITc_badge_register_unregister_changed_cb_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			To Test badge_register_changed_cb and badge_unregister_changed_cb
* @scenario				Call badge_register_changed_cb, badge_unregister_changed_cb
* @apicovered			badge_register_changed_cb, badge_unregister_changed_cb
* @passcase				If badge_register_changed_cb and badge_unregister_changed_cb returns success and set get values are same
* @failcase				If target api or precondition api fails
* @precondition			badge should be created
* @postcondition		badge should be removed
*/
int ITc_badge_register_unregister_changed_cb_p(void)
{
	START_TEST;
	int nRet = -1;

	g_bCallBackHit = false;
	nRet = badge_register_changed_cb(BadgeChangedCallBack, NULL);
	PRINT_RESULT(BADGE_ERROR_NONE, nRet, "badge_register_changed_cb", BadgeGetError(nRet));

	nRet = badge_set_count(BADGE_PACKAGE, 2);
	PRINT_RESULT(BADGE_ERROR_NONE, nRet, "badge_set_count", BadgeGetError(nRet));
	IterateGmainLoop();
	PRINT_RESULT(true, g_bCallBackHit, "badge_register_changed_cb", "CallBack Not Invoked");
	nRet = badge_unregister_changed_cb(BadgeChangedCallBack);
	PRINT_RESULT(BADGE_ERROR_NONE, nRet, "badge_unregister_changed_cb", BadgeGetError(nRet));

	return 0;
}

/** @} */
/** @} */
