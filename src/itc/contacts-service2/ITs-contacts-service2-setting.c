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
#include "ITs-contacts-service2-common.h"

/** @addtogroup itc-contacts-service2
*  @ingroup itc
*  @{
*/


//& set: ContactsService
//Callbacks

/**
* @function 		ContactsServiceContactsSettingNameDisplayOrderChangedCB
* @description	 	Called when a designated view changes.
* @parameter		contacts_name_display_order_e name_display_order, void* user_data
* @return 			NA
*/
static void  ContactsServiceContactsSettingNameDisplayOrderChangedCB(contacts_name_display_order_e name_display_order, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ContactsServiceContactsSettingNameDisplayOrderChangedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pContactsServiceMainLoop )
	{
		g_main_loop_quit(g_pContactsServiceMainLoop);
	}
	return;
}

/**
* @function 		ContactsServiceContactsSettingNameSortingOrderChangedCB
* @description	 	Called when a designated view changes.
* @parameter		contacts_name_sorting_order_e name_sorting_order, void* user_data
* @return 			NA
*/
static void  ContactsServiceContactsSettingNameSortingOrderChangedCB(contacts_name_sorting_order_e name_sorting_order, void* user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ContactsServiceContactsSettingNameSortingOrderChangedCB callback called\\n", __LINE__ , API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pContactsServiceMainLoop )
	{
		g_main_loop_quit(g_pContactsServiceMainLoop);
	}
	return;
}

/************************************************************************************/

/**
* @function 		ITs_contacts_service2_setting_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_setting_startup(void)
{
	struct stat stBuff;
	g_bIsContactFeatureSupported = false;
	g_bContactFeatureMismatch = false;
	g_bIsConnected = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsContactFeatureSupported = TCTCheckSystemInfoFeatureSupported(CONTACT_FEATURE, API_NAMESPACE);

	if ( ContactsServiceConnect() == true )
	{
		g_bContactsServiceCreation = true;
	}
	else
	{
		g_bContactsServiceCreation = false;
	}
	return;
}

/**
* @function 		ITs_contacts_service2_setting_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_setting_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-setting-testcases
*  @brief 		Integration testcases for module contacts_service2-setting
*  @ingroup 	itc-contacts_service2-setting
*  @{
*/
//& purpose: Sets/Gets the contacts name display order.
//& type: auto

/**
* @testcase 			ITc_contacts_setting_set_get_name_display_order_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets/Gets the contacts name display order.
* @scenario				Connect to database\n
*						Set the contacts name display order\n
*						Get the contacts name display order\n
*						Check if values are same\n
* 						Disconnect from database
* @apicovered			contacts_setting_set_name_display_order(), contacts_setting_get_name_display_order()
* @passcase				When set and get values are same
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_setting_set_get_name_display_order_p(void)
{
	START_TEST;

	contacts_name_display_order_e setDisplayOrder[] = { CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST, CONTACTS_NAME_DISPLAY_ORDER_LASTFIRST};
	contacts_name_display_order_e getDisplayOrder;
	int nEnumSize = sizeof(setDisplayOrder) / sizeof(setDisplayOrder[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		int nRet = contacts_setting_set_name_display_order(setDisplayOrder[nEnumCounter]);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_set_name_display_order", ContactsServiceGetError(nRet));

		// Target API
		nRet = contacts_setting_get_name_display_order(&getDisplayOrder);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_get_name_display_order", ContactsServiceGetError(nRet));
		if ( setDisplayOrder[nEnumCounter] != getDisplayOrder )
		{
			FPRINTF("[Line : %d][%s] Get and Set values are not same\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

//& purpose: Sets/Gets the contacts name sorting order.
//& type: auto

/**
* @testcase 			ITc_contacts_setting_set_get_name_sorting_order_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets/Gets the contacts name sorting order.
* @scenario				Connect to database
*						Set the contacts name sorting order
*						Get the contacts name sorting order
*						Check if values are same
* 						Disconnect from database
* @apicovered			contacts_setting_set_name_sorting_order(), contacts_setting_get_name_sorting_order()
* @passcase				When set and get values are same
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_setting_set_get_name_sorting_order_p(void)
{
	START_TEST;

	contacts_name_sorting_order_e setSortingOrder[] = { CONTACTS_NAME_SORTING_ORDER_FIRSTLAST, CONTACTS_NAME_SORTING_ORDER_LASTFIRST};
	contacts_name_sorting_order_e getSortingOrder;
	int nEnumSize = sizeof(setSortingOrder) / sizeof(setSortingOrder[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		int nRet = contacts_setting_set_name_sorting_order(setSortingOrder[nEnumCounter]);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_set_name_sorting_order", ContactsServiceGetError(nRet));

		// Target API
		nRet = contacts_setting_get_name_sorting_order(&getSortingOrder);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_get_name_sorting_order", ContactsServiceGetError(nRet));
		if ( setSortingOrder[nEnumCounter] != getSortingOrder )
		{
			FPRINTF("[Line : %d][%s] Get and Set values are not same\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
	}

	return 0;
}

//& purpose: Registers/Deregisters a callback function.
//& type: auto

/**
* @testcase 			ITc_contacts_setting_add_remove_name_display_order_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers/Deregisters a callback function.
* @scenario				Connect to database\n
*						Register callback\n
*						Check callback is invoked\n
*						Deregister callback\n
* 						Disconnect from database 
* @apicovered			contacts_setting_add_name_display_order_changed_cb(), contacts_setting_remove_name_display_order_changed_cb()
* @passcase				When callback is invoked
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_setting_add_remove_name_display_order_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	contacts_name_display_order_e setDisplayOrder = CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST;

	// Target API
	int nRet = contacts_setting_add_name_display_order_changed_cb(ContactsServiceContactsSettingNameDisplayOrderChangedCB,NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_add_name_display_order_changed_cb", ContactsServiceGetError(nRet));

	// set name display order and check callback
	g_bCallbackHit = false;
	nRet = contacts_setting_set_name_display_order(setDisplayOrder);

	RUN_POLLING_LOOP;
	if ( nRet != CONTACTS_ERROR_NONE || g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] Failed to call callback , error returned = %s\\n", __LINE__ , API_NAMESPACE, ContactsServiceGetError(nRet));
		return 1;
	}

	// Target API
	nRet = contacts_setting_remove_name_display_order_changed_cb(ContactsServiceContactsSettingNameDisplayOrderChangedCB,NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_remove_name_display_order_changed_cb", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Registers/Deregisters a callback function.
//& type: auto

/**
* @testcase 			ITc_contacts_setting_add_remove_name_sorting_order_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers/Deregisters a callback function.
* @scenario				Connect to database
*						Register callback
*						Check callback is invoked
*						Deregister callback
* 						Disconnect from database
* @apicovered			contacts_setting_add_name_sorting_order_changed_cb(), contacts_setting_remove_name_sorting_order_changed_cb()
* @passcase				When callback is invoked
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_setting_add_remove_name_sorting_order_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	contacts_name_sorting_order_e setSortingOrder = CONTACTS_NAME_SORTING_ORDER_FIRSTLAST;

	// Target API
	int nRet = contacts_setting_add_name_sorting_order_changed_cb(ContactsServiceContactsSettingNameSortingOrderChangedCB,NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_add_name_sorting_order_changed_cb", ContactsServiceGetError(nRet));

	// set name sorting order and check callback
	g_bCallbackHit = false;
	nRet = contacts_setting_set_name_sorting_order(setSortingOrder);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_setting_set_name_sorting_order", ContactsServiceGetError(nRet) , contacts_setting_remove_name_sorting_order_changed_cb(ContactsServiceContactsSettingNameSortingOrderChangedCB,NULL));

	RUN_POLLING_LOOP;
	if ( nRet != CONTACTS_ERROR_NONE || g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] Failed to call callback , error returned = %s\\n", __LINE__ , API_NAMESPACE, ContactsServiceGetError(nRet));
		nRet = contacts_setting_remove_name_sorting_order_changed_cb(ContactsServiceContactsSettingNameSortingOrderChangedCB,NULL);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_remove_name_sorting_order_changed_cb", ContactsServiceGetError(nRet));
		return 1;
	}

	// Target API
	nRet = contacts_setting_remove_name_sorting_order_changed_cb(ContactsServiceContactsSettingNameSortingOrderChangedCB,NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_setting_remove_name_sorting_order_changed_cb", ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
