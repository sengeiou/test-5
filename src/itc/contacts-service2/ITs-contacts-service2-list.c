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

contacts_list_h g_list;

/**
* @function 		ITs_contacts_service2_list_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_list_startup(void)
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
		int nRet = contacts_list_create(&g_list);
		if ( nRet == CONTACTS_ERROR_NONE )
		{
			g_bContactsServiceCreation = true;
			contacts_record_h record1 = NULL;
			contacts_record_h record2 = NULL;
			nRet = contacts_record_create(_contacts_number._uri, &record1);
			if ( nRet != CONTACTS_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
				return;
			}
			nRet = contacts_record_create(_contacts_number._uri, &record2);
			if ( nRet != CONTACTS_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
				return;
			}
			nRet = contacts_list_add(g_list, record1);
			if ( nRet != CONTACTS_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_list_add", ContactsServiceGetError(nRet));
				return;
			}
			nRet = contacts_list_add(g_list, record2);
			if ( nRet != CONTACTS_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_list_add", ContactsServiceGetError(nRet));
				return;
			}
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
* @function 		ITs_contacts_service2_list_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_list_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_list_destroy(g_list, true);
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}


/** @addtogroup itc-contacts_service2-list-testcases
*  @brief 		Integration testcases for module contacts_service2-list
*  @ingroup 	itc-contacts_service2-list
*  @{
*/

//& purpose: Creates/Destroys a list.
//& type: auto

/**
* @testcase 			ITc_contacts_list_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates/Destroys a list.
* @scenario				Connect to database\n
*						Create a list\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_create(), contacts_list_destroy()
* @passcase				When contacts_list_create() and contacts_list_destroy() are successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_create_destroy_p(void)
{
	START_TEST;

	contacts_list_h list = NULL;

	// Target API
	int nRet = contacts_list_create(&list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_list_destroy(list,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Adds/removes a record to a contacts list.
//& type: auto

/**
* @testcase 			ITc_contacts_list_add_remove_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds/removes a record to a contacts list.
* @scenario				Connect to database\n
*						Create a list\n
*						Create record\n
*						Add record to contact list\n
*						Remove record from contact list\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_add(), contacts_list_remove()
* @passcase				When contacts_list_add() and contacts_list_remove() are successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_add_remove_p(void)
{
	START_TEST;

	contacts_record_h record = NULL;
	int nRet = contacts_record_create(_contacts_number._uri, &record);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
    nRet = contacts_list_add(g_list, record);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet), contacts_record_destroy(record, true));

	// Target API
	nRet = contacts_list_remove(g_list, record);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_remove", ContactsServiceGetError(nRet), contacts_record_destroy(record, true));

	nRet = contacts_record_destroy(record, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Moves a contacts list to the first position.
//& type: auto

/**
* @testcase 			ITc_contacts_list_first_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a contacts list to the first position.
* @scenario				Connect to database\n
*						Create a list\n
*						Move a contacts list to the first position\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_first()
* @passcase				When contacts_list_first() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_first_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_list_first(g_list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_first", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Moves a contacts list to the last position. 
//& type: auto

/**
* @testcase 			ITc_contacts_list_last_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a contacts list to the last position. 
* @scenario				Connect to database\n
*						Create a list\n
*						Move a contacts list to the last position\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_last()
* @passcase				When contacts_list_last() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_last_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_list_last(g_list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_last", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Moves a contacts list to the next/previous position. 
//& type: auto

/**
* @testcase 			ITc_contacts_list_next_prev_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a contacts list to the next/previous position. 
* @scenario				Connect to database\n
*						Create a list\n
*						Move a contacts list to the next position\n
*						Move a contacts list to the previous position\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_next()
* @passcase				When contacts_list_next() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_next_prev_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_list_next(g_list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_next", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_list_prev(g_list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_prev", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Retrieves the number of contact entities from a contacts list.
//& type: auto

/**
* @testcase 			ITc_contacts_list_get_count_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the number of contact entities from a contacts list.
* @scenario				Connect to database\n
*						Create a list\n
*						Add record to contact list\n
*						Retrieves the number of contact entities\n
*						Destroy record\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_get_count()
* @passcase				When contacts_list_get_count() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_get_count_p(void)
{
	START_TEST;

	int unCount = 0;
	contacts_record_h record1 = NULL;

	int nRet = contacts_record_create(_contacts_number._uri, &record1);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_list_add(g_list, record1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet),contacts_record_destroy(record1, true));

	// Target API
	nRet = contacts_list_get_count(g_list ,&unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_get_count", ContactsServiceGetError(nRet),contacts_list_remove(g_list, record1);contacts_record_destroy(record1, true));

	if ( unCount == 0 )
	{
		FPRINTF("[Line : %d][%s] contacts_list_get_count returned Count = %d\\n", __LINE__, API_NAMESPACE, unCount);
		contacts_list_remove(g_list, record1);
		contacts_record_destroy(record1, true);
		return 1;
	}

	nRet = contacts_list_remove(g_list, record1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_remove", ContactsServiceGetError(nRet),contacts_record_destroy(record1, true));

	nRet = contacts_record_destroy(record1, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Retrieves a record from the contacts list. 
//& type: auto

/**
* @testcase 			ITc_contacts_list_get_current_record_p_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves a record from the contacts list. 
* @scenario				Connect to database\n
*						Create a list\n
*						Add record to contact list\n
*						Retrieve a record from the contacts list\n
*						Destroy record\n
*						Destroy the list\n
* 						Disconnect from database
* @apicovered			contacts_list_get_current_record_p()
* @passcase				When contacts_list_get_current_record_p() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_list_get_current_record_p_p(void)
{
	START_TEST;

	contacts_record_h record1 = NULL;
	contacts_record_h record2 = NULL;
	contacts_record_h getRecord = NULL;

	int nRet = contacts_record_create(_contacts_number._uri, &record1);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_number._uri, &record2);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(record1, true));

	nRet = contacts_list_add(g_list, record1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet), contacts_record_destroy(record1, true);contacts_record_destroy(record2, true));

	nRet = contacts_list_add(g_list, record2);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet), contacts_list_remove(g_list, record1);
	contacts_record_destroy(record1, true);
	contacts_record_destroy(record2, true));

	// Target API
	nRet = contacts_list_get_current_record_p(g_list ,&getRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_get_current_record_p", ContactsServiceGetError(nRet),contacts_list_remove(g_list, record1);

	contacts_list_remove(g_list, record2);
	contacts_record_destroy(record1, true);
	contacts_record_destroy(record2, true));

	if ( getRecord == NULL )
	{
		FPRINTF("[Line : %d][%s] contacts_list_get_current_record_p returned Null record\\n", __LINE__ , API_NAMESPACE);
		contacts_list_remove(g_list, record1);
		contacts_list_remove(g_list, record2);
		contacts_record_destroy(record1, true);
		contacts_record_destroy(record2, true);
		return 1;
	}

	nRet = contacts_list_remove(g_list, record1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_remove",ContactsServiceGetError(nRet), contacts_record_destroy(record1, true);contacts_list_remove(g_list, record2);contacts_record_destroy(record2, true));

	nRet = contacts_list_remove(g_list, record2);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_remove",ContactsServiceGetError(nRet), contacts_record_destroy(record1, true);contacts_record_destroy(record2, true));

	nRet = contacts_record_destroy(record1, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy",ContactsServiceGetError(nRet), contacts_record_destroy(record2, true));

	nRet = contacts_record_destroy(record2, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy",ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
