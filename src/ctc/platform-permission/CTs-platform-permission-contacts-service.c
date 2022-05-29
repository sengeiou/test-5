#include "CTs-platform-permission-common.h"

//Add test package related includes here
#include <contacts.h>
#include <glib.h>
#include <app.h>

//Add helper function declarations here

bool g_bContactsServiceCreation;
bool g_bCallbackHit;
bool g_bCallbackReturnValue;
bool g_bIsConnected;

int g_nFirstRecordId;
int g_nFirstPersonId;
int g_nFirstContactId;
int g_nSecondRecordId;
int g_nSecondPersonId;
int g_nSecondContactId;
int g_nFrontRecordId;
int g_nFrontPersonId;
int g_nFrontContactId;
int g_nBackRecordId;
int g_nBackPersonId;
int g_nBackContactId;
int g_nPersonId;
int g_nGroupId;

contacts_record_h g_hFirstProfileRecord;
contacts_record_h g_hSecondProfileRecord;
contacts_record_h g_hFrontProfileRecord;
contacts_record_h g_hBackProfileRecord;
contacts_record_h g_hRecordFirst;
contacts_record_h g_hRecordSecond;
contacts_record_h g_hRecordFront;
contacts_record_h g_hRecordBack;
contacts_record_h g_hGroupRecord;

GMainLoop *g_pContactsServiceMainLoop;

#define TELEPHONY_FEATURE		"http://tizen.org/feature/network.telephony"

/**
* @function 		ContactsServiceGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ContactsServiceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CONTACTS_ERROR_NONE:					szErrorVal = "CONTACTS_ERROR_NONE";			break;
	case CONTACTS_ERROR_OUT_OF_MEMORY:			szErrorVal = "CONTACTS_ERROR_OUT_OF_MEMORY";			break;
	case CONTACTS_ERROR_INVALID_PARAMETER:		szErrorVal = "CONTACTS_ERROR_INVALID_PARAMETER";		break;
	case CONTACTS_ERROR_FILE_NO_SPACE:			szErrorVal = "CONTACTS_ERROR_FILE_NO_SPACE";			break;
	case CONTACTS_ERROR_NO_DATA:				szErrorVal = "CONTACTS_ERROR_NO_DATA";					break;
	case CONTACTS_ERROR_PERMISSION_DENIED:		szErrorVal = "CONTACTS_ERROR_PERMISSION_DENIED";		break;
	case CONTACTS_ERROR_DB:						szErrorVal = "CONTACTS_ERROR_DB";						break;
	case CONTACTS_ERROR_DB_LOCKED:				szErrorVal = "CONTACTS_ERROR_DB_LOCKED";				break;
	case CONTACTS_ERROR_IPC_NOT_AVALIABLE:		szErrorVal = "CONTACTS_ERROR_IPC_NOT_AVALIABLE";		break;
	case CONTACTS_ERROR_IPC:					szErrorVal = "CONTACTS_ERROR_IPC";						break;
	case CONTACTS_ERROR_SYSTEM:					szErrorVal = "CONTACTS_ERROR_SYSTEM";					break;
	case CONTACTS_ERROR_INTERNAL:				szErrorVal = "CONTACTS_ERROR_INTERNAL";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}



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
/**
* @function 		ContactsServiceConnect
* @description	 	Connect Contacts DB
* @parameter		NA
* @return 			true if service initialized successfully, else false
*/
bool ContactsServiceConnect(void)
{
	int nRet = contacts_connect();
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] contacts_connect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
		return false;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] contacts_connect passed\\n", __LINE__, API_NAMESPACE);
#endif
		g_bIsConnected = true;
		return true;
	}
}

/**
* @function 		ContactsServiceDisconnect
* @description	 	Disconnect Contacts DB
* @parameter		NA
* @return 			true if service de initialized successfully, else false
*/
bool ContactsServiceDisconnect(void)
{
	int nRet = contacts_disconnect();
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] contacts_disconnect failed, error returned = %s\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
		return false;
	}
	else
	{
#if DEBUG
		FPRINTF("[Line : %d][%s] contacts_disconnect passed\\n", __LINE__, API_NAMESPACE);
#endif
		g_bIsConnected = false;
		return true;
	}
}
/**
* @function 		ContactsServiceCreateAndInsertRecord
* @description	 	Create a record and insert in DB
* @parameter		NA
* @return 			true if contact successfully added, else false
*/
bool ContactsServiceCreateAndInsertRecord(int *nRecordId, int *nContactId, int *nPersonId, contacts_record_h *hProfileRecord, contacts_record_h *hRecord, const char *pszNumber, const char *pszName)
{
	int nRet = 0;
	contacts_record_h hMainRecord_number = NULL;
	contacts_record_h hMainRecord_name = NULL;
	contacts_record_h hNameRecord = NULL;
	contacts_record_h hNumberRecord = NULL;
	//contacts_record_h hTempRecord = NULL;
	//contacts_record_h hPersonRecord = NULL;

	/*------------------------------ _contacts_number ------------------------------*/
	contacts_record_create(_contacts_contact._uri, &hMainRecord_number);
	contacts_record_create(_contacts_number._uri, &hNumberRecord);
	contacts_record_set_str(hNumberRecord, _contacts_number.number, pszNumber);
	nRet = contacts_record_add_child_record(hMainRecord_number, _contacts_contact.number, hNumberRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_add_child_record", ContactsServiceGetError(nRet));
		return false;
	}

	/*
	nRet =contacts_db_insert_record(hMainRecord_number, nContactId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 1\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record", ContactsServiceGetError(nRet));
		return false;
	}
	*/
	contacts_record_destroy(hMainRecord_number, true);
	hMainRecord_number = NULL;
	hNumberRecord = NULL;

	/*------------------------------ _contacts_name ------------------------------*/
	contacts_record_create(_contacts_contact._uri, &hMainRecord_name);
	contacts_record_create(_contacts_name._uri, &hNameRecord);
	contacts_record_set_str(hNameRecord, _contacts_name.first, pszName);
	nRet = contacts_record_add_child_record(hMainRecord_name, _contacts_contact.name, hNameRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_add_child_record", ContactsServiceGetError(nRet));
		return false;
	}
	/*
	nRet = contacts_db_insert_record(hMainRecord_name, nRecordId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 2\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record", ContactsServiceGetError(nRet));
		return false;
	}
	*/
	contacts_record_destroy(hMainRecord_name, false);
	hMainRecord_name = NULL;

	/*------------------------------ _contacts_my_profile ------------------------------*/
	nRet = contacts_record_create(_contacts_my_profile._uri, hProfileRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
	}
	nRet = contacts_record_set_str(*hProfileRecord, _contacts_my_profile.uid, "my_uid");
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_set_str", ContactsServiceGetError(nRet));
	}
	nRet = contacts_record_add_child_record(*hProfileRecord, _contacts_my_profile.name, hNameRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_add_child_record", ContactsServiceGetError(nRet));
		return false;
	}

	/*------------------------------ _contacts_person.is_favorite ------------------------------*/
	/*
	nRet = contacts_db_get_record(_contacts_contact._uri, *nRecordId, &hTempRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 1\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	contacts_record_get_int(hTempRecord, _contacts_contact.person_id, nPersonId);
	contacts_record_destroy(hTempRecord, false);
	hMainRecord_name = NULL;

	nRet = contacts_db_get_record(_contacts_person._uri, *nPersonId, &hPersonRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 2\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	contacts_record_set_bool(hPersonRecord, _contacts_person.is_favorite, true);
	nRet = contacts_db_update_record(hPersonRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_update_record", ContactsServiceGetError(nRet));
		return false;
	}
	contacts_record_destroy(hPersonRecord, false);
	hPersonRecord = NULL;

	nRet = contacts_db_get_record(_contacts_contact._uri, *nRecordId, hRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 3\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	*/
	return true;
}

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
* @function         CTs_platform_permission_ContactsService_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_ContactsService_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_ContactsService_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	g_bIsConnected = false;
	if ( ContactsServiceConnect() == true )
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
}

/**
* @function         CTs_platform_permission_ContactsService_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_ContactsService_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_ContactsService_p\\n", __LINE__, API_NAMESPACE);
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
	//sleep(SLEEP_TIME);

    return;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_db_insert_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Inserts and Deletes multiple records in and from the contacts database.
* @apicovered		contacts_db_insert_records(), contacts_db_delete_records()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_db_insert_records(void)
{
	START_TEST;

	contacts_record_h stNumberRecord = NULL;
	contacts_record_h stMainRecord = NULL;
	contacts_list_h stList = NULL;

	int *pnID;
	int unCount = 0;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	CHECK_HANDLE(stMainRecord, "contacts_record_create");

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true));

	CHECK_HANDLE_CLEANUP(stNumberRecord, "contacts_record_create",contacts_record_destroy(stMainRecord, true));

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
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_insert_records", ContactsServiceGetError(nRet),contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true);contacts_db_delete_records(_contacts_contact._uri,pnID, unCount),CONTACTS_ERROR_NONE);
	contacts_record_destroy(stMainRecord, true);

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_db_insert_record
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			InsertsInserts and Deletes a record in and from the contacts database.
* @apicovered		contacts_db_insert_record(), contacts_db_delete_record()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_db_insert_record(void)
{
	START_TEST;

	contacts_record_h stNumberRecord = NULL;
	contacts_record_h stMainRecord = NULL;
	int nContactID = 0;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_record_create(_contacts_contact._uri, &stMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	CHECK_HANDLE(stMainRecord, "contacts_record_create");

	nRet = contacts_record_create(_contacts_number._uri, &stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true));

	CHECK_HANDLE_CLEANUP(stNumberRecord, "contacts_record_create",contacts_record_destroy(stMainRecord, true));

	nRet = contacts_record_set_str(stNumberRecord, _contacts_number.number, "98123");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	nRet = contacts_record_add_child_record(stMainRecord, _contacts_contact.number, stNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true));

	// Target API
	nRet =contacts_db_insert_record(stMainRecord, &nContactID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet), contacts_record_destroy(stMainRecord, true);contacts_record_destroy(stNumberRecord, true),CONTACTS_ERROR_NONE);
	contacts_record_destroy(stNumberRecord, true);
	contacts_record_destroy(stMainRecord, true);

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Finds records based on a given keyword.
* @apicovered		contacts_db_search_records()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records(void)
{
	START_TEST;

	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}


	// Target API
	int nRet = contacts_db_search_records( _contacts_person._uri, pszKeyword, nOffset, nLimit, &stList);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_search_records", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true),CONTACTS_ERROR_NONE);

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records_with_query
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To find records based on given query and keyword. 
* @apicovered		contacts_db_search_records_with_query()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records_with_query(void)
{
	START_TEST;
	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h  stList;
	contacts_query_h query = NULL;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}
	int nRet = contacts_query_create(_contacts_person._uri, &query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_search_records_with_query(query, pszKeyword, nOffset, nLimit, &stList);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_search_records_with_query", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true);contacts_query_destroy(query),CONTACTS_ERROR_NONE);
	contacts_query_destroy(query);

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records_with_range
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To find  records based on a keyword and range.
* @apicovered		contacts_db_search_records_with_range()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_search_records_with_range(void)
{
	START_TEST;
	const char* pszKeyword = "test";
	int nOffset = 0;
	int nLimit = 0;
	int nRange = 1;
	contacts_list_h stList;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

		// Target API
	int nRet = contacts_db_search_records_with_range(_contacts_person._uri, pszKeyword, nOffset, nLimit, nRange, &stList);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_search_records_with_range", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true),CONTACTS_ERROR_NONE);

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_get_all_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To retrieve all records and return the results list.
* @apicovered		contacts_db_get_all_records()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_get_all_records(void)
{
	START_TEST;

	int nOffset = 0;
	int nLimit = 0;
	contacts_list_h stList;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

    if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_db_get_all_records(_contacts_person._uri, nOffset, nLimit, &stList);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_get_all_records", ContactsServiceGetError(nRet), contacts_list_destroy(stList, true),CONTACTS_ERROR_NONE);

	return 0;
}


//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_get_current_version
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To get the last changed contacts database version on the current connection.
* @apicovered		contacts_db_get_last_change_version()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_get_current_version(void)
{
	START_TEST;

	int nLastChangeVersion;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_db_get_last_change_version(&nLastChangeVersion);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_get_last_change_version", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_get_count
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To get the number of records in a specific view
* @apicovered		contacts_db_get_count()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_get_count(void)
{
	START_TEST;
	int nCount;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_db_get_count(_contacts_contact._uri, &nCount);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_get_count", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_get_count_with_query
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			To get the number of records in a specific view
* @apicovered		contacts_db_get_count_with_query()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_get_count_with_query(void)
{
	START_TEST;
	int nCount;
	contacts_query_h stQuery = NULL;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_query_create(_contacts_person._uri, &stQuery);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_get_count_with_query(stQuery, &nCount);
	contacts_query_destroy(stQuery);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_get_count_with_query", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_get_records_with_query
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Uses a query to find records.
* @apicovered		contacts_db_get_records_with_query()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_get_records_with_query(void)
{
	START_TEST;
	int nOffset = 0, nLimit = 0;
	contacts_query_h stQuery = NULL;
	contacts_list_h stList = NULL;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_query_create(_contacts_person._uri, &stQuery);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_db_get_records_with_query(stQuery, nOffset, nLimit, &stList);
	contacts_query_destroy(stQuery);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_get_records_with_query", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read callhistory.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_db_add_changed_cb
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Registers/Deregisters a callback function to be invoked when a record changes.
* @apicovered		contacts_db_add_changed_cb()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_db_add_changed_cb(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_db_add_changed_cb(_contacts_person._uri, ContactsDbChangedCB, NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_db_add_changed_cb", ContactsServiceGetError(nRet));

	return 0;
}

/***************************** contact service group ****************/

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_group_set_group_order
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Sets a group between the previous group and the next group.
* @apicovered		contacts_group_set_group_order()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_group_set_group_order(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_group_set_group_order(1,2,3);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_group_set_group_order", ContactsServiceGetError(nRet));

	return 0;
}


/***************************** contact person ****************/

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_person_set_default_property
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Sets the order of a (favorite) contact.
* @apicovered		contacts_person_set_default_property()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_person_set_default_property(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_person_set_default_property(CONTACTS_PERSON_PROPERTY_NUMBER,1,2);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_person_set_default_property", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_person_link_person
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Links a person to another person.
* @apicovered		contacts_person_link_person()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_person_link_person(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_person_link_person(1, 2);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_person_link_person", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_person_reset_usage
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Resets a person's usage count
* @apicovered		contacts_person_reset_usage()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_person_reset_usage(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet =  contacts_person_reset_usage(1, CONTACTS_USAGE_STAT_TYPE_NONE);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_person_reset_usage", ContactsServiceGetError(nRet));

	return 0;
}


//& purpose:Checking tizen.org/privilege/callhistory.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeCallhistoryWrite_contacts_phone_log_reset_statistics
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Resets the phone log's count.
* @apicovered		contacts_phone_log_reset_statistics()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeCallhistoryWrite_contacts_phone_log_reset_statistics(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_phone_log_reset_statistics();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_phone_log_reset_statistics", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_setting_set_name_sorting_order
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the contacts name sorting order.
* @apicovered		contacts_setting_set_name_sorting_order(), contacts_setting_get_name_sorting_order()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_setting_set_name_sorting_order(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}
	// Target API
	int nRet = contacts_setting_set_name_sorting_order(CONTACTS_NAME_SORTING_ORDER_FIRSTLAST);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_set_name_sorting_order", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_setting_get_name_sorting_order
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the contacts name sorting order.
* @apicovered		contacts_setting_set_name_sorting_order(), contacts_setting_get_name_sorting_order()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_setting_get_name_sorting_order(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	contacts_name_sorting_order_e getSortingOrder;

	// Target API
	int nRet = contacts_setting_get_name_sorting_order(&getSortingOrder);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_set_name_sorting_order", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_setting_add_name_display_order_changed_cb
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Registers/Deregisters a callback function.
* @apicovered		contacts_setting_add_name_display_order_changed_cb()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_setting_add_name_display_order_changed_cb(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_setting_add_name_display_order_changed_cb(ContactsServiceContactsSettingNameDisplayOrderChangedCB,NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_add_name_display_order_changed_cb", ContactsServiceGetError(nRet));

	return 0;
}


//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_setting_set_name_display_order
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Sets the contacts name display order.
* @apicovered		contacts_setting_set_name_display_order()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_setting_set_name_display_order(void)
{
	START_TEST;

	contacts_name_display_order_e setDisplayOrder = CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_setting_set_name_display_order(setDisplayOrder);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_set_name_display_order", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_setting_get_name_display_order
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the contacts name display order.
* @apicovered		contacts_setting_get_name_display_order()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_setting_get_name_display_order(void)
{
	START_TEST;

	contacts_name_display_order_e getDisplayOrder;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_setting_get_name_display_order(&getDisplayOrder);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_get_name_display_order", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_contacts_setting_add_name_sorting_order_changed_cb
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Registers/Deregisters a callback function.
* @apicovered		contacts_setting_add_name_sorting_order_changed_cb()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_contacts_setting_add_name_sorting_order_changed_cb(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_setting_add_name_sorting_order_changed_cb(ContactsServiceContactsSettingNameSortingOrderChangedCB,NULL);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_setting_add_name_sorting_order_changed_cb", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_sim_import_all_contacts
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Imports all contacts from SIM to Contacts Database.
* @apicovered		contacts_sim_import_all_contacts()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_sim_import_all_contacts(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_sim_import_all_contacts();
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_sim_import_all_contacts", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.read privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactRead_contacts_sim_get_initialization_status
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Checks whether SIM initialization is completed or not.
* @apicovered		contacts_sim_import_all_contacts()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactRead_contacts_sim_get_initialization_status(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;
	bool bIsCompleted = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet = contacts_sim_get_initialization_status(&bIsCompleted);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_sim_get_initialization_status", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_activity_delete_by_contact_id
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Deletes an activity record from the contacts database by contact id
* @apicovered		contacts_activity_delete_by_contact_id()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_activity_delete_by_contact_id(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_activity_delete_by_contact_id(1);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_activity_delete_by_contact_id", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose:Checking tizen.org/privilege/contact.write privilege
//& type: auto
/**
* @testcase			CTc_ContactsService_PrivilegeContactWrite_contacts_activity_delete_by_account_id
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Deletes an activity record from the contacts database by account id.
* @apicovered		contacts_activity_delete_by_account_id()
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_ContactsService_PrivilegeContactWrite_contacts_activity_delete_by_account_id(void)
{
	START_TEST;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	int nRet = contacts_activity_delete_by_account_id(1);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_activity_delete_by_account_id", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Gets aggregation suggestions.
//& type: auto

/**
* @testcase 		CTc_ContactsService_PrivilegeContacts_person_get_aggregation_suggestions
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description		get aggregation suggestions
* @scenario			get aggregation suggestions
* @apicovered		contacts_person_get_aggregation_suggestions
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @precondition		contacts_connect() should be called to open a connection to the contacts service.
* @postcondition	None
*/
int CTc_ContactsService_PrivilegeContacts_person_get_aggregation_suggestions(void)
{
	START_TEST;

	contacts_list_h hList = NULL;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}

	// Target API
	int nRet =  contacts_person_get_aggregation_suggestions(1,0,&hList);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_person_get_aggregation_suggestions", ContactsServiceGetError(nRet));
	contacts_list_destroy(hList,true);

	return 0;
}

//& purpose: Resets the phone log's count by sim slot no.
//& type: auto
/**
* @testcase 		CTc_ContactsService_PrivilegeContacts_phone_log_reset_statistics_by_sim
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description     	Resets the phone log's count by sim slot no.
* @scenario        	Connect to database\n
*              	   	Reset the phone log's count by sim slot no.\n
*                  	Disconnect from database
* @apicovered      	contacts_phone_log_reset_statistics_by_sim
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition    	contacts_connect2() should be called to open a connection to the contacts service.e	
* @postcondition   	None
*/
int CTc_ContactsService_PrivilegeContacts_phone_log_reset_statistics_by_sim(void)
{
	START_TEST;

	//nSimSlotNo 0 means first SIM, nSimSlotNo 1 means second SIM
	int nSimSlotNo = 0;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}
	   // Target API
	   int nRet = contacts_phone_log_reset_statistics_by_sim(nSimSlotNo);
	   PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_phone_log_reset_statistics_by_sim", ContactsServiceGetError(nRet));

	   return 0;
}

//& purpose: Gets the limit size of width and hight of photos to append in vCard files.
//& type: auto
/**
* @testcase 		CTc_ContactsService_PrivilegeContacts_vcard_get_limit_size_of_photo
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description     	Gets the limit size of width and hight of photos to append in vCard files.
* @scenario        	Gets the limit size of width and hight of photos to append in vCard files.
* @apicovered      	contacts_vcard_get_limit_size_of_photo
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition    	None
* @postcondition   	None
*/
int CTc_ContactsService_PrivilegeContacts_vcard_get_limit_size_of_photo(void)
{
	START_TEST;

	int nRet = 0;
	unsigned int limit_size;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}
	nRet = contacts_vcard_get_limit_size_of_photo(&limit_size);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_vcard_get_limit_size_of_photo", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets the limit size of width and hight of photos to append in vCard files.
//& type: auto
/**
* @testcase 		CTc_ContactsService_PrivilegeContacts_vcard_set_limit_size_of_photo
* @since_tizen		3.0
* @author           SRID(arvin.mittal)
* @reviewer         SRID(shobhit.v)
* @type 			auto
* @description     	Sets the limit size of width and hight of photos to append in vCard files.
* @scenario        	Sets the limit size of width and hight of photos to append in vCard files.
* @apicovered      	contacts_vcard_set_limit_size_of_photo
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition    	None
* @postcondition   	None
*/
int CTc_ContactsService_PrivilegeContacts_vcard_set_limit_size_of_photo(void)
{
	START_TEST;

	int nRet = 0;
	unsigned int setting_size = 96;
	bool bTelephonyIsSupported = false;
	bool bContactIsSupported = false;
	bool bIsSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_TELEPHONY, bTelephonyIsSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_CONTACT, bContactIsSupported, API_NAMESPACE);
	bIsSupported = bTelephonyIsSupported && bContactIsSupported;

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s]  and %s is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_TELEPHONY, FEATURE_CONTACT);
		return 0;
	}
	nRet = contacts_vcard_set_limit_size_of_photo(setting_size);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "contacts_vcard_set_limit_size_of_photo", ContactsServiceGetError(nRet));

	return 0;
}
