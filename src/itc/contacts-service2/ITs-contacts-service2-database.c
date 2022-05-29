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
* @function 		ContactsDbChangedCB
* @description	 	Called when the designated view changes.
* @parameter		const char* view_uri, void* user_data
* @return 			void
*/
static void ContactsDbChangedCB(const char* view_uri, void* user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] ContactsDbChangedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( view_uri == NULL )
	{
		FPRINTF("[Line : %d][%s] ContactsDbChangedCB callback returned null view uri\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = false;
	}
	else
	{
		g_bCallbackReturnValue = true;
	}
	if ( g_pContactsServiceMainLoop )
	{
		g_main_loop_quit(g_pContactsServiceMainLoop);
	}
	return;
}


/**
* @function 		ContactsDbStatusChangedCB
* @description	 	Called when the designated view changes.
* @parameter		const char* view_uri,char *changes, void* user_data
* @return 			void
*/
static void ContactsDbStatusChangedCB(contacts_db_status_e status, void* user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] ContactsDbStatusChangedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	switch ( status )
	{
	case CONTACTS_DB_STATUS_NORMAL:
		FPRINTF("[Line : %d][%s] Db status: CONTACTS_DB_STATUS_NORMAL\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	case CONTACTS_DB_STATUS_CHANGING_COLLATION:
		FPRINTF("[Line : %d][%s] Db status: CONTACTS_DB_STATUS_CHANGING_COLLATION\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = true;
		break;
	}
	if ( g_pContactsServiceMainLoop )
	{
		g_main_loop_quit(g_pContactsServiceMainLoop);
	}
	return;
}

/*****************************************************************************/
/**
* @function 		ITs_contacts_service2_database_startup
* @description	 	Called before each test, set the service bool true
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_database_startup(void)
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

	if ( ContactsServiceConnect() == true)
	{
		if ( ContactsServiceCreateAndInsertRecord(&g_nFirstRecordId, &g_nFirstContactId, &g_nFirstPersonId, &g_hFirstProfileRecord, &g_hRecordFirst, "099882722", "TESTFIRST_d") == true )
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
* @function 		ITs_contacts_service2_database_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_database_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	if( g_bIsConnected || ContactsServiceConnect() )
	{
		contacts_record_destroy(g_hRecordFirst, true);
		contacts_record_destroy(g_hFirstProfileRecord, true);
		contacts_db_delete_record(_contacts_person._uri, g_nFirstPersonId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFirstRecordId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFirstContactId);
		ContactsServiceDisconnect();
	}
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-database-testcases
*  @brief 		Integration testcases for module contacts_service2-database
*  @ingroup 	itc-contacts_service2-database
*  @{
*/
//& purpose: Connects and disconnects to the contacts service
//& type: auto

/**
* @testcase 			ITc_contacts_connect_disconnect_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects and disconnects to the contacts service.
* @scenario				Connect to contacts service\n
* 						Disconnect the contacts service
* @apicovered			contacts_connect(), contacts_disconnect()
* @passcase				When contacts_connect and contacts_disconnect are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_connect_disconnect_p(void)
{
	START_TEST;

	if ( ContactsServiceDisconnect() == false )
	{
		return 1;
	}

	// Target API
	int nRet = contacts_connect();
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_connect", ContactsServiceGetError(nRet),ContactsServiceConnect());

	// Target API
	nRet = contacts_disconnect();
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_disconnect", ContactsServiceGetError(nRet),ContactsServiceConnect());

	return 0;
}

//& purpose: Connects/Disconnects to the contacts service with a connection on another thread.
//& type: auto

/**
* @testcase 			ITc_contacts_connect_disconnect_on_thread_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects/Disconnects to the contacts service with a connection on another thread.
* @scenario				Connects to the contacts service with a connection on another thread\n
* 						Disconnects to the contacts service
* @apicovered			contacts_connect_on_thread(), contacts_disconnect_on_thread()
* @passcase				When contacts_connect_on_thread and contacts_disconnect_on_thread are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_connect_disconnect_on_thread_p(void)
{
	START_TEST;

	if ( ContactsServiceDisconnect() == false )
	{
		return 1;
	}

	// Target API
	int nRet = contacts_connect_on_thread();
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_connect_on_thread", ContactsServiceGetError(nRet),ContactsServiceConnect());

	// Target API
	nRet = contacts_disconnect_on_thread();
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_disconnect_on_thread", ContactsServiceGetError(nRet),ContactsServiceConnect());

	return 0;
}

//& purpose: Connects to the contacts service.
//& type: auto

/**
* @testcase 			ITc_contacts_connect_with_flags_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects to the contacts service.
* @scenario				Connect to contacts service\n
* 						Disconnect from contacts service 
* @apicovered			contacts_connect_with_flags()
* @passcase				When contacts_connect_with_flags is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_connect_with_flags_p(void)
{
	START_TEST;

	if ( ContactsServiceDisconnect() == false )
	{
		return 1;
	}

	// Target API
	int nRet = contacts_connect_with_flags(CONTACTS_CONNECT_FLAG_RETRY);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_connect_with_flags", ContactsServiceGetError(nRet),ContactsServiceConnect());

	nRet = contacts_disconnect();
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_disconnect", ContactsServiceGetError(nRet),ContactsServiceConnect());
	return 0;
}

//& purpose: Registers/Deregisters a callback function to be invoked when a record changes.
//& type: auto

/**
* @testcase 			ITc_contacts_db_add_remove_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers/Deregisters a callback function to be invoked when a record changes.
* @scenario				Connect to contacts service and add record\n
*						Add changed cb\n
*						Update record\n
*						Check callback called\n
*						Remove changed cb\n
* 						Disconnect the contacts service and destroy record
* @apicovered			contacts_db_add_changed_cb(), contacts_db_remove_changed_cb()
* @passcase				When contacts_db_add_changed_cb and contacts_db_remove_changed_cb are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_db_add_remove_changed_cb_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	contacts_record_h hPersonRecord = NULL;
	g_bCallbackHit = false;

	// Target API
	int nRet = contacts_db_add_changed_cb(_contacts_person._uri, ContactsDbChangedCB, NULL);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_add_changed_cb", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_db_get_record(_contacts_person._uri, g_nFirstPersonId, &hPersonRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_set_bool(hPersonRecord, _contacts_person.is_favorite, false);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_bool", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_db_update_record(hPersonRecord);
	RUN_POLLING_LOOP;
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_update_record", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	if ( g_bCallbackHit == false || g_bCallbackReturnValue == false )
	{
		FPRINTF("[Line : %d][%s] Callback failed\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hPersonRecord, true);
		return 1;
	}

	// Target API
	nRet = contacts_db_remove_changed_cb(_contacts_person._uri, ContactsDbChangedCB, NULL);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_remove_changed_cb", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_destroy(hPersonRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: Registers/Deregisters a callback function.
//& type: auto

/**
* @testcase 			ITc_contacts_db_add_remove_status_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers/Deregisters a callback function.
* @scenario				Connect to contacts service and add record\n
*						Add status changed cb\n
*						Check callback called\n
*						Remove status changed cb\n
* 						Disconnect the contacts service and destroy record
* @apicovered			contacts_db_add_status_changed_cb (), contacts_db_remove_status_changed_cb()
* @passcase				When contacts_db_add_status_changed_cb  and contacts_db_remove_status_changed_cb  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_db_add_remove_status_changed_cb_p(void)
{
	START_TEST;

	g_bCallbackHit = false;

	// Target API
	int nRet = contacts_db_add_status_changed_cb(ContactsDbStatusChangedCB, NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_add_status_changed_cb", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_remove_status_changed_cb(ContactsDbStatusChangedCB, NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_remove_status_changed_cb", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: Inserts and Deletes multiple records in and from the contacts database.
//& type: auto

/**
* @testcase 			ITc_contacts_db_insert_delete_records_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts and Deletes multiple records in and from the contacts database.
* @scenario				Connect to contacts service\n
*						inserts multiple records in the database\n
*						deletes multiple records from the database\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_insert_records(), contacts_db_delete_records()
* @passcase				When contacts_db_insert_records and contacts_db_delete_records are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_insert_delete_records_p(void)
{
	START_TEST;

	contacts_record_h stNumberRecord = NULL;
	contacts_record_h stMainRecord = NULL;
	contacts_list_h stList = NULL;

	int *pnID;
	int unCount = 0;

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_set_str(stNumberRecord, _contacts_number.number, "981236789");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_record_add_child_record(stMainRecord, _contacts_contact.number, stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_list_create(&stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_create", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_list_add(stList, stMainRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	// Target API
	nRet =contacts_db_insert_records(stList, &pnID, &unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_records", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_db_delete_records(_contacts_contact._uri,pnID, unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_delete_records", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_record_destroy(stMainRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet),contacts_record_destroy(stNumberRecord, true));

	return 0;
}

//& purpose: Inserts and Deletes a record in and from the contacts database.
//& type: auto

/**
* @testcase 			ITc_contacts_db_insert_delete_record_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts and Deletes a record in and from the contacts database.
* @scenario				Connect to contacts service\n
*						inserts records in the database\n
*						deletes records from the database\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_insert_record(), contacts_db_delete_record()
* @passcase				When contacts_db_insert_record and contacts_db_delete_record are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_insert_delete_record_p(void)
{
	START_TEST;

	contacts_record_h stNumberRecord = NULL;
	contacts_record_h stMainRecord = NULL;
	int nContactID = 0;

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_set_str(stNumberRecord, _contacts_number.number, "98123");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_record_add_child_record(stMainRecord, _contacts_contact.number, stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	// Target API
	nRet =contacts_db_insert_record(stMainRecord, &nContactID);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));


	nRet = contacts_record_destroy(stMainRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet), contacts_db_delete_record(_contacts_contact._uri, nContactID));

	sleep(2);
	nRet = contacts_db_delete_record(_contacts_contact._uri, nContactID);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_delete_record", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To update a record in the contacts database.
//& type: auto
/**
* @testcase 			ITc_contacts_db_update_record_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To update a record in the contacts database.
* @scenario				Connect to contacts service\n
*						Insert record\n
*						Get record\n
*						Update record in the contact database\n 
*						Delete the record\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_update_record()
* @passcase				When contacts_db_update_record is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_update_record_p(void)
{
	START_TEST;

	contacts_record_h hPersonRecord;

	int nRet = contacts_db_get_record(_contacts_person._uri, g_nFirstPersonId, &hPersonRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_set_bool(hPersonRecord, _contacts_person.is_favorite, false);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_bool", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	// Target API
	nRet =contacts_db_update_record(hPersonRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_update_record", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_destroy(hPersonRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: To get a record from the contacts database
//& type: auto

/**
* @testcase 			ITc_contacts_db_get_record_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get a record from the contacts database
* @scenario				Connect to contacts service\n
*						Insert record\n
*						Get record\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_get_record()
* @passcase				When contacts_db_get_record  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_record_p(void)
{
	START_TEST;
	bool bIsTelephonyFeatureIsSupported = true;
	bIsTelephonyFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	contacts_record_h stMainRecord = NULL;

	// Target API
	int nRet = contacts_db_get_record(_contacts_contact._uri, g_nFirstRecordId, &stMainRecord);

	#ifdef MOBILE	//Starts MOBILE
	if(!bIsTelephonyFeatureIsSupported)
	{
		if (stMainRecord != NULL)
		{
			contacts_record_destroy(stMainRecord, true);
		}

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_record API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_record API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}
	#endif  //End MOBILE

	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));
	CHECK_HANDLE_CLEANUP(stMainRecord, "contacts_db_get_record", contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_destroy(stMainRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	#ifdef WEARABLE	//Starts WEARABLE
	bool bVal = ContactsServiceCreateAndInsertRecordSdn(&g_hFirstProfileRecord);
	if (!bVal)
	{
		FPRINTF("[Line : %d][%s] ContactsServiceCreateAndInsertRecordSdn api returns false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	nRet = contacts_db_get_record(_contacts_sdn._uri, g_nFirstRecordId, &stMainRecord);

	if(!bIsTelephonyFeatureIsSupported)
	{
		if (stMainRecord != NULL)
		{
			contacts_record_destroy(stMainRecord, true);
		}

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_record API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_record API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}

	if ( nRet == CONTACTS_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] No SDN in Database, nRet = %s\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
		return 0;
	}

	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));
	CHECK_HANDLE(stMainRecord, "contacts_db_get_record");

	nRet = contacts_record_destroy(stMainRecord, true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	#endif  //End WEARABLE

	return 0;
}

//& purpose: To update multiple records in the contacts database. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_update_records_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To update multiple records in the contacts database.
* @scenario				Connect to contacts service\n
*						Create record\n
*						Create list\n
*						Insert record\n
*						Update list\n
*						Delete record and destroy list\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_update_records()
* @passcase				When contacts_db_update_records  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_update_records_p(void)
{
	START_TEST;

	contacts_list_h stList;
	contacts_record_h hPersonRecord;

	int nRet = contacts_db_get_record(_contacts_person._uri, g_nFirstPersonId, &hPersonRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_set_bool(hPersonRecord, _contacts_person.is_favorite, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_bool", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_list_create(&stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_create", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_list_add(stList, hPersonRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	// Target API
	nRet = contacts_db_update_records(stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_update_records", ContactsServiceGetError(nRet),contacts_record_destroy(hPersonRecord, true));

	nRet = contacts_record_destroy(hPersonRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To replace an id-identified record with the given record. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_replace_record_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To replace an id-identified record with the given record. 
* @scenario				Connect to contacts service\n
*						replace an identified record with the given one\n
* 						Disconnect the contacts service 
* @apicovered			contacts_db_replace_record()
* @passcase				When contacts_db_replace_record  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_replace_record_p(void)
{
	START_TEST;

	contacts_record_h pstMainRecords = NULL;

	int nRet = contacts_record_create(_contacts_contact._uri, &pstMainRecords);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_replace_record(pstMainRecords, g_nFirstRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_replace_record", ContactsServiceGetError(nRet),contacts_record_destroy(pstMainRecords, true));

	nRet = contacts_record_destroy(pstMainRecords, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: To get the number of records in a specific view
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_count_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get the number of records in a specific view
* @scenario				Connect to contacts service\n
*						Get the number if records count\n
* 						Disconnect the contacts service 
* @apicovered			contacts_db_get_count()
* @passcase				When contacts_db_get_count  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_count_p(void)
{
	START_TEST;

	int nCount;

	// Target API
	int nRet =contacts_db_get_count(_contacts_contact._uri, &nCount);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_count", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To get the number of records matching a query. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_count_with_query_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get the number of records matching a query. 
* @scenario				Connect to contacts service\n
*						Create the query\n
*						Get the number of records matching query\n
*						Disconnect the contacts service
* @apicovered			contacts_db_get_count_with_query()
* @passcase				When contacts_db_get_count_with_query  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_count_with_query_p(void)
{
	START_TEST;

	int nCount;
	contacts_query_h stQuery = NULL;

	int nRet = contacts_query_create(_contacts_person._uri, &stQuery);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_get_count_with_query(stQuery, &nCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_count_with_query", ContactsServiceGetError(nRet),contacts_query_destroy(stQuery));

	nRet = contacts_query_destroy(stQuery);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: To get the current contacts database version. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_current_version_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get the current contacts database version. 
* @scenario				Connect to contacts service\n
*						Get the current contacts database version.\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_get_current_version()
* @passcase				When contacts_db_get_current_version  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_current_version_p(void)
{
	START_TEST;

	int nContactsDbVersion = 0;

	// Target API
	int nRet =contacts_db_get_current_version(&nContactsDbVersion);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_current_version", ContactsServiceGetError(nRet));

	return 0;
}
//& purpose: To get the last changed contacts database version on the current connection.
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_last_change_version_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get the last changed contacts database version on the current connection.
* @scenario				Connect to contacts service\n
get the last change version\n
* 						Disconnect the contacts service 
* @apicovered			contacts_db_get_last_change_version()
* @passcase				When contacts_db_get_last_change_version  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_last_change_version_p(void)
{
	START_TEST;

	int nLastChangeVersion;

	// Target API
	int nRet =contacts_db_get_last_change_version(&nLastChangeVersion);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_last_change_version", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Uses a query to find records.
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_records_with_query_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Uses a query to find records..
* @scenario				Connect to contacts service\n
*						Create the record\n
*						Insert the records\n
*						Create the query\n
*						Use the query to find records\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_get_records_with_query()
* @passcase				When contacts_db_get_records_with_query  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_records_with_query_p(void)
{
	START_TEST;

	bool bIsTelephonyFeatureIsSupported = true;
	bIsTelephonyFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	int nOffset = 0, nLimit = 0;
	contacts_query_h stQuery = NULL;
	contacts_list_h stList = NULL;

	int nRet = contacts_query_create(_contacts_person._uri, &stQuery);
	#ifdef MOBILE	//Starts MOBILE
	if(!bIsTelephonyFeatureIsSupported)
	{
		if(stQuery != NULL)
		{
			contacts_query_destroy(stQuery);
		}

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_query_create API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_query_create API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}
	#endif  //End MOBILE
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));
	CHECK_HANDLE(stQuery, "contacts_query_create");

	// Target API
	nRet = contacts_db_get_records_with_query(stQuery, nOffset, nLimit, &stList);


	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_records_with_query", ContactsServiceGetError(nRet), contacts_query_destroy(stQuery); contacts_list_destroy(stList, true));

	nRet = contacts_query_destroy(stQuery);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));
       #ifdef WEARABLE //Starts WEARABLE
        bool bVal = ContactsServiceCreateAndInsertRecordSdn(&g_hFirstProfileRecord);
        if (!bVal)
        {
                FPRINTF("[Line : %d][%s] ContactsServiceCreateAndInsertRecordSdn api returns false\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

        nRet = contacts_query_create(_contacts_sdn._uri, &stQuery);
        PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));
        CHECK_HANDLE(stQuery, "contacts_query_create");

        // Target API
        nRet = contacts_db_get_records_with_query(stQuery, nOffset, nLimit, &stList);
        if(!bIsTelephonyFeatureIsSupported)
        {
                if(stQuery != NULL)
                {
                        contacts_query_destroy(stQuery);
                }

                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        FPRINTF("[Line : %d][%s] contacts_db_get_records_with_query API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
                        return 1;
                }
                else
                {
                        FPRINTF("[Line : %d][%s] contacts_db_get_records_with_query API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
                        return 0;
                }
        }

        PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_records_with_query", ContactsServiceGetError(nRet), contacts_query_destroy(stQuery); contacts_list_destroy(stList, true));

        nRet = contacts_query_destroy(stQuery);
        PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet));

        nRet = contacts_list_destroy(stList, true);
        PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));
        #endif  //End WEARABLE

        return 0;

}

//& purpose: to get the last changed contacts database version on the current connection
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_changes_by_version_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			to get the last changed contacts database version on the current connection
* @scenario				Connect to contacts service\n
*						Get the last changed database\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_get_changes_by_version()
* @passcase				When contacts_db_get_changes_by_version  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_changes_by_version_p(void)
{
	START_TEST;

	int nContactID = 0;
	int nContactsDbVersion = 0;
	int nCurrentContactsDbVersion;
	contacts_record_h stMainRecord = NULL;
	contacts_record_h stNumberRecord = NULL;
	contacts_list_h stList;

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_set_str(stNumberRecord, _contacts_number.number, "9870");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet), contacts_record_destroy(stNumberRecord, true);contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_add_child_record(stMainRecord, _contacts_contact.number, stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet), contacts_record_destroy(stNumberRecord, true);contacts_record_destroy(stMainRecord, true));

	nRet = contacts_db_get_current_version (&nContactsDbVersion);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_current_version", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));


	nRet = contacts_db_insert_record(stMainRecord, &nContactID);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));

	// Target API
	nRet = contacts_db_get_changes_by_version(_contacts_contact_updated_info._uri, nContactID, nContactsDbVersion, &stList, &nCurrentContactsDbVersion);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_changes_by_version", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_db_delete_record(_contacts_contact._uri, nContactID);
	contacts_list_destroy(stList, true));

	nRet = contacts_record_destroy( stMainRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet), contacts_db_delete_record(_contacts_contact._uri, nContactID);contacts_list_destroy(stList, true));

	nRet = contacts_db_delete_record(_contacts_contact._uri, nContactID);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_delete_record", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To get the status of the database
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_status_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To get the status of the database
* @scenario				Connect to contacts service\n
* 						get the status of database\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_get_status()
* @passcase				When contacts_db_get_status  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_status_p(void)
{
	START_TEST;

	contacts_db_status_e stContactsDbStatus;

	// Target API
	int nRet =contacts_db_get_status(&stContactsDbStatus);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_status", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Replaces database records identified by given ids with a given record list. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_replace_records_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects and disconnects to the contacts service.
* @scenario				Connect to contacts service\n
* 						replaces database bu given id\n
* 						Disconnect the contacts service
* @apicovered			contacts_db_replace_records()
* @passcase				When contacts_db_replace_records  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_replace_records_p(void)
{
	START_TEST;

	contacts_record_h stNumberRecord = NULL;
	contacts_record_h stMainRecord = NULL;
	contacts_list_h stList = NULL;

	int *pnID = NULL;
	int unCount = 0;

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_set_str(stNumberRecord, _contacts_number.number, "981236789");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_record_add_child_record(stMainRecord, _contacts_contact.number, stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_list_create(&stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_create", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_list_add(stList, stMainRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_add", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet =contacts_db_insert_records(stList, &pnID, &unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_records", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	// Target API
	nRet =contacts_db_replace_records(stList, pnID, unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_replace_records", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_list_destroy(stList, true));

	nRet = contacts_db_delete_records(_contacts_contact._uri,pnID, unCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_delete_records", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_destroy(stMainRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet),contacts_record_destroy(stNumberRecord, true));

	return 0;
}

//& purpose: Finds records based on a given keyword.
//& type: auto
/**
* @testcase 			ITc_contacts_db_search_records_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Finds records based on a given keyword.
* @scenario				Connect to contacts service\n
* 						To find record for a given keyword\n
* 						Disconnect to contacts service
* @apicovered			contacts_db_search_records()
* @passcase				When contacts_db_search_records  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_search_records_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList;

	// Target API
	int nRet = contacts_db_search_records( _contacts_person._uri, pszKeyword, nOffset, nLimit, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To find records based on given query and keyword. 
//& type: auto
/**
* @testcase 			ITc_contacts_db_search_records_with_query_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To find records based on given query and keyword. 
* @scenario				connect to contacts service\n
* 						Use query on keyword to find record\n
* 						Disconnect to contacts service
* @apicovered			contacts_db_search_records_with_query()
* @passcase				When contacts_db_search_records_with_query  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_search_records_with_query_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList;
	contacts_query_h query = NULL;

	int nRet = contacts_query_create(_contacts_person._uri, &query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_search_records_with_query(query, pszKeyword, nOffset, nLimit, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records_with_query", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true);contacts_query_destroy(query));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet),contacts_query_destroy(query));

	nRet = contacts_query_destroy(query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet));
	return 0;

}

//& purpose: To find  records based on a keyword and range.
//& type: auto
/**
* @testcase 			ITc_contacts_db_search_records_with_range_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To find  records based on a keyword and range.
* @scenario				connect to contacts service\n
* 						set the range and accordingly find record based on keyword\n
* 						disconnect to contacts service
* @apicovered			contacts_db_search_records_with_range()
* @passcase				When contacts_db_search_records_with_range  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_search_records_with_range_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	int nRange = 1;
	contacts_list_h stList;

	// Target API
	int nRet = contacts_db_search_records_with_range(_contacts_person._uri, pszKeyword, nOffset, nLimit, nRange, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records_with_range", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To retrieve all records and return the results list.
//& type: auto
/**
* @testcase 			ITc_contacts_db_get_all_records_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To retrieve all records and return the results list.
* @scenario				connect to contacts service\n
* 						To retrieve all records\n
* 						return the result list\n
* 						dis-connect to contacts service
* @apicovered			contacts_db_get_all_records()
* @passcase				When contacts_db_get_all_records  are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_db_get_all_records_p(void)
{
	START_TEST;
	bool bIsTelephonyFeatureIsSupported = true;
	bIsTelephonyFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h stList = NULL;

	// Target API
	int nRet = contacts_db_get_all_records(_contacts_person._uri, nOffset, nLimit, &stList);
	#ifdef MOBILE	//Starts MOBILE
	if(!bIsTelephonyFeatureIsSupported)
	{
		if(stList != NULL)
		{
			contacts_list_destroy(stList, true);
		}

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_all_records API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_all_records API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}
	#endif  //End MOBILE

	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_all_records", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	#ifdef WEARABLE	//Starts WEARABLE
	bool bVal = ContactsServiceCreateAndInsertRecordSdn(&g_hFirstProfileRecord);
	if (!bVal)
	{
		FPRINTF("[Line : %d][%s] ContactsServiceCreateAndInsertRecordSdn api returns false\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	nRet = contacts_db_get_all_records(_contacts_sdn._uri, nOffset, nLimit, &stList);
	if(!bIsTelephonyFeatureIsSupported)
	{
		if(stList != NULL)
		{
			contacts_list_destroy(stList, true);
		}

		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_all_records API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_all_records API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}

	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_all_records", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));
	#endif  //End WEARABLE

	return 0;
}

//& purpose: Finds records based on a given keyword for snippet.
//& type: auto
/**
* @testcase 		ITc_contacts_db_search_records_for_snippet_p
* @since_tizen		3.0
* @author           SRID(sameer.g1)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		Finds records based on a given keyword.
* @scenario			Connect to contacts service\n
* 					To find record for a given keyword\n
* 					Disconnect to contacts service
* @apicovered		contacts_db_search_records_for_snippet()
* @passcase			When contacts_db_search_records_for_snippet are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		contacts_connect() should be called to open a connection to the contacts service
* @postcondition	None
*/
int ITc_contacts_db_search_records_for_snippet_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList = NULL;

	// Target API
	int nRet = contacts_db_search_records_for_snippet(_contacts_person._uri, pszKeyword, nOffset, nLimit, NULL, NULL, -1, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records_for_snippet", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));
	CHECK_HANDLE_CLEANUP(stList, "contacts_db_search_records_for_snippet", contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To Finds records based on a keyword and range for snippet.
//& type: auto
/**
* @testcase 		ITc_contacts_db_search_records_with_range_for_snippet_p
* @since_tizen		3.0
* @author           SRID(sameer.g1)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To find  records based on a keyword and range.
* @scenario			connect to contacts service\n
* 					set the range and accordingly find record based on keyword\n
* 					disconnect to contacts service
* @apicovered		contacts_db_search_records_with_range_for_snippet()
* @passcase			When contacts_db_search_records_with_range_for_snippet are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		contacts_connect() should be called to open a connection to the contacts service
* @postcondition	None
*/
int ITc_contacts_db_search_records_with_range_for_snippet_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	int nRange = 1;
	contacts_list_h stList;

	// Target API
	int nRet = contacts_db_search_records_with_range_for_snippet(_contacts_person._uri, pszKeyword, nOffset, nLimit, nRange,NULL, NULL, -1, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records_with_range_for_snippet", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true));
	CHECK_HANDLE_CLEANUP(stList, "contacts_db_search_records_with_range_for_snippet", contacts_list_destroy(stList, true));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: To find records based on given query and keyword. 
//& type: auto
/**
* @testcase 		ITc_contacts_db_search_records_with_query_for_snippet_p
* @since_tizen		3.0
* @author           SRID(sameer.g1)
* @reviewer         SRID(a.pandia1)
* @type 			auto
* @description		To find records based on given query and keyword. 
* @scenario			connect to contacts service\n
* 					Use query on keyword to find record\n
* 					Disconnect to contacts service
* @apicovered		contacts_db_search_records_with_query_for_snippet
* @passcase			When contacts_db_search_records_with_query_for_snippet  are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		contacts_connect() should be called to open a connection to the contacts service
* @postcondition	None
*/
int ITc_contacts_db_search_records_with_query_for_snippet_p(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList;
	contacts_query_h query = NULL;

	int nRet = contacts_query_create(_contacts_person._uri, &query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_search_records_with_query_for_snippet(query, pszKeyword, nOffset, nLimit,NULL, NULL, -1, &stList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_search_records_with_query_for_snippet", ContactsServiceGetError(nRet),contacts_list_destroy(stList, true); contacts_query_destroy(query));

	CHECK_HANDLE_CLEANUP(stList, "contacts_db_search_records_with_query_for_snippet", contacts_list_destroy(stList, true); contacts_query_destroy(query));

	nRet = contacts_list_destroy(stList, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet),contacts_query_destroy(query));

	nRet = contacts_query_destroy(query);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet));
	return 0;

}

//& purpose: Gets the number of found records based on a given keyword.
//& type: auto
/**
* @testcase			ITc_contacts_db_get_count_for_search_records_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @description			Gets the number of found records based on a given keyword.
* @scenario			Connect to contacts service\n
*				inserts multiple records in the database\n
*				deletes multiple records from the database\n
* 				Disconnect the contacts service
* @apicovered			contacts_db_get_count_for_search_records
* @passcase			When contacts_db_get_count_for_search_records and pre-conditions are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition		None
*/
int ITc_contacts_db_get_count_for_search_records_p(void)
{
	START_TEST;

	unsigned int nGetRecordCnt = 0;
	int nRet;

	// Target API
	nRet = contacts_db_get_count_for_search_records(_contacts_person._uri, "010", &nGetRecordCnt);

	if(!g_bIsContactFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records API call returned mismatch %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records API call correctly returned %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}

	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_count_for_search_records", ContactsServiceGetError(nRet));
	FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records, record count is = %d\\n", __LINE__, API_NAMESPACE, nGetRecordCnt);

	return 0;
}

//& purpose: Gets the number of found records based on a given keyword and query.
//& type: auto

/**
* @testcase			ITc_contacts_db_get_count_for_search_records_with_query_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @description			Gets the number of found records based on a given keyword and query.
* @scenario			Connect to contacts service\n
*				inserts multiple records in the database\n
*				deletes multiple records from the database\n
* 				Disconnect the contacts service
* @apicovered			contacts_db_get_count_for_search_records_with_query
* @passcase			When contacts_db_get_count_for_search_records_with_query and pre-conditions are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition		None
*/
int ITc_contacts_db_get_count_for_search_records_with_query_p(void)
{
	START_TEST;

	contacts_query_h hContactQuery = NULL;
	contacts_filter_h hContactFilter = NULL;

	int nRet;
	unsigned int nGetRecordCnt = 0;

	nRet = contacts_query_create(_contacts_person._uri, &hContactQuery);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	if(!g_bIsContactFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_query_create API call returned mismatch %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_query_create API call correctly returned %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}

	nRet = contacts_filter_create(_contacts_person._uri, &hContactFilter);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet), contacts_query_destroy(hContactQuery));

	nRet = contacts_filter_add_int(hContactFilter, _contacts_person.id, CONTACTS_MATCH_LESS_THAN_OR_EQUAL, g_nFirstPersonId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet), contacts_query_destroy(hContactQuery); contacts_filter_destroy(hContactFilter));

	nRet = contacts_query_set_filter(hContactQuery, hContactFilter);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_query_set_filter", ContactsServiceGetError(nRet), contacts_query_destroy(hContactQuery); contacts_filter_destroy(hContactFilter));

	// Target API
	nRet = contacts_db_get_count_for_search_records_with_query(hContactQuery, "010", &nGetRecordCnt);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_count_for_search_records_with_query", ContactsServiceGetError(nRet), contacts_query_destroy(hContactQuery); contacts_filter_destroy(hContactFilter));
	FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records_with_query, record count is = %d\\n", __LINE__, API_NAMESPACE, nGetRecordCnt);

	nRet = contacts_filter_destroy(hContactFilter);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));

	nRet = contacts_query_destroy(hContactQuery);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Gets the number of found records based on a given keyword and range.
//& type: auto
/**
* @testcase			ITc_contacts_db_get_count_for_search_records_with_range_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @description			Gets the number of found records based on a given keyword and range.
* @scenario			Connect to contacts service\n
*				inserts multiple records in the database\n
*				deletes multiple records from the database\n
* 				Disconnect the contacts service
* @apicovered			contacts_db_get_count_for_search_records_with_range
* @passcase			When contacts_db_get_count_for_search_records_with_range and pre-conditions are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition		None
*/
int ITc_contacts_db_get_count_for_search_records_with_range_p(void)
{
	START_TEST;

	int nRet;
	unsigned int nGetRecordCnt = 0;

	// Target API
	nRet = contacts_db_get_count_for_search_records_with_range(_contacts_person._uri, "010", CONTACTS_SEARCH_RANGE_NAME | CONTACTS_SEARCH_RANGE_NUMBER, &nGetRecordCnt);

	if(!g_bIsContactFeatureSupported)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records_with_range API call returned mismatch %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records_with_range API call correctly returned %s error for unsupported contact feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
	}

	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_count_for_search_records_with_range", ContactsServiceGetError(nRet));
	FPRINTF("[Line : %d][%s] contacts_db_get_count_for_search_records_with_range, record count is = %d\\n", __LINE__, API_NAMESPACE, nGetRecordCnt);

	return 0;
}

/** @} */ 
/** @} */
