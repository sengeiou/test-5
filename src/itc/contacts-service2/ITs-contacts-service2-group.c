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

/**
* @function 		ITs_contacts_service2_group_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_group_startup(void)
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
		if ( ContactsServiceCreateAndInsertRecord(&g_nFirstRecordId, &g_nFirstContactId, &g_nFirstPersonId, &g_hFirstProfileRecord, &g_hRecordFirst, "099882723", "TESTFIRST_g")
			&& ContactsServiceCreateAndInsertGroupRecord())
		{
			g_bContactsServiceCreation = true;
		}
		else
		{
			g_bContactsServiceCreation = false;
		}
	}
	else
	{
		g_bContactsServiceCreation = false;
	}
	return;
}

/**
* @function 		ITs_contacts_service2_group_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_group_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_record_destroy(g_hRecordFirst, true);
	contacts_record_destroy(g_hFirstProfileRecord, true);
	contacts_record_destroy(g_hGroupRecord, true);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstRecordId);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstContactId);
	contacts_db_delete_record(_contacts_person._uri, g_nFirstPersonId);
	contacts_db_delete_record(_contacts_group._uri, g_nGroupId);
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/********************************************************************************************/

/** @addtogroup itc-contacts_service2-group-testcases
*  @brief 		Integration testcases for module contacts_service2-group
*  @ingroup 	itc-contacts_service2-group
*  @{
*/

//& purpose: Adds/Removes a contact and a group relationship to the contacts database.
//& type: auto

/**
* @testcase 			ITc_contacts_group_add_remove_contact_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds/Removes a contact and a group relationship to the contacts database.
* @scenario				Connect to database\n
*						Add a contact and a group relationship to the contacts database\n
*						Remove a contact and a group relationship from the contacts database\n
* 						Disconnect from database
* @apicovered			contacts_group_add_contact(), contacts_group_remove_contact()
* @passcase				When contacts_group_add_contact() and contacts_group_remove_contact() are successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_group_add_remove_contact_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_group_add_contact(g_nGroupId, g_nFirstContactId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_group_add_contact", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_group_remove_contact(g_nGroupId, g_nFirstContactId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_group_remove_contact", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets a group between the previous group and the next group.
//& type: auto

/**
* @testcase 			ITc_contacts_group_set_group_order_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a group between the previous group and the next group.
* @scenario				Connect to database\n
*						Set a group between the previous group and the next group\n
* 						Disconnect from database
* @apicovered			contacts_group_set_group_order()
* @passcase				When contacts_group_set_group_order is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_group_set_group_order_p(void)
{
	START_TEST;

	int nPrevGroupId = 1;
	int nNextGroupId = 0;

	// Target API
	int nRet = contacts_group_set_group_order(g_nGroupId,nPrevGroupId,nNextGroupId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_group_set_group_order", ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
