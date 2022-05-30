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
* @function 		ITs_contacts_service2_person_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_person_startup(void)
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
	g_nFirstPersonId = 0;
	g_nSecondPersonId = 0;
	g_nFrontPersonId = 0;
	g_nBackPersonId = 0;

	g_bIsContactFeatureSupported = TCTCheckSystemInfoFeatureSupported(CONTACT_FEATURE, API_NAMESPACE);

	if ( ContactsServiceConnect() == true )
	{
		if ( ContactsServiceCreateAndInsertRecord(&g_nFirstRecordId, &g_nFirstContactId, &g_nFirstPersonId, &g_hFirstProfileRecord, &g_hRecordFirst, "9876543210", "TESTFIRST_p") == true )
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
* @function 		ITs_contacts_service2_person_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_person_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_db_delete_record(_contacts_person._uri, g_nPersonId);
	if ( g_nFirstPersonId > 0 )
	{
		contacts_record_destroy(g_hRecordFirst, true);
		contacts_record_destroy(g_hFirstProfileRecord, true);
		contacts_db_delete_record(_contacts_person._uri, g_nFirstPersonId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFirstRecordId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFirstContactId);
	}
	if ( g_nSecondPersonId > 0 )
	{
		contacts_record_destroy(g_hRecordSecond, true);
		contacts_record_destroy(g_hSecondProfileRecord, true);
		contacts_db_delete_record(_contacts_person._uri, g_nSecondPersonId);
		contacts_db_delete_record(_contacts_contact._uri, g_nSecondRecordId);
		contacts_db_delete_record(_contacts_contact._uri, g_nSecondContactId);
	}
	if ( g_nFrontPersonId > 0 )
	{
		contacts_record_destroy(g_hRecordFront, true);
		contacts_record_destroy(g_hFrontProfileRecord, true);
		contacts_db_delete_record(_contacts_person._uri, g_nFrontPersonId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFrontRecordId);
		contacts_db_delete_record(_contacts_contact._uri, g_nFrontContactId);
	}
	if ( g_nBackPersonId > 0 )
	{
		contacts_record_destroy(g_hRecordBack, true);
		contacts_record_destroy(g_hBackProfileRecord, true);
		contacts_db_delete_record(_contacts_person._uri, g_nBackPersonId);
		contacts_db_delete_record(_contacts_contact._uri, g_nBackRecordId);
		contacts_db_delete_record(_contacts_contact._uri, g_nBackContactId);
	}
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-person-testcases
*  @brief 		Integration testcases for module contacts_service2-person
*  @ingroup 	itc-contacts_service2-person
*  @{
*/
//& purpose: Set/Get a default property for a record.
//& type: auto

/**
* @testcase 			ITc_contacts_person_set_get_default_property_p01
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get a default property for a record.
* @scenario				Connect to database\n
*						Add records to database\n
*						Set record's default property\n
*						Get a default property for a record\n
*						Delete records\n
* 						Disconnect from database
* @apicovered			contacts_person_set_default_property() ,contacts_person_get_default_property()
* @passcase				When contacts_person_set_default_property() and contacts_person_get_default_property() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_person_set_get_default_property_p01(void)
{
	START_TEST;

	contacts_person_property_e person_property[] = { CONTACTS_PERSON_PROPERTY_NAME_CONTACT };

	int nEnumSize = sizeof(person_property) / sizeof(person_property[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		int nRet = contacts_person_set_default_property(person_property[nEnumCounter],g_nFirstPersonId,g_nFirstRecordId);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_set_default_property", ContactsServiceGetError(nRet));

		// Target API
		nRet = contacts_person_get_default_property(person_property[nEnumCounter],g_nFirstPersonId,&g_nFirstRecordId);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_get_default_property", ContactsServiceGetError(nRet));
	}

	return 0;
}

//& purpose: Set/Get a default property for a record.
//& type: auto

/**
* @testcase 			ITc_contacts_person_set_get_default_property_p02
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get a default property for a record.
* @scenario				Connect to database\n
*						Add records to database\n
*						Set record's default property\n
*						Get a default property for a record\n
*						Delete records\n
* 						Disconnect from database
* @apicovered			contacts_person_set_default_property() ,contacts_person_get_default_property()
* @passcase				When contacts_person_set_default_property() and contacts_person_get_default_property() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_person_set_get_default_property_p02(void)
{
	START_TEST;

	contacts_record_h hEmailRecord = NULL;
	int nEmailRecordId = -1;
	contacts_person_property_e person_property[] = {CONTACTS_PERSON_PROPERTY_EMAIL};

	int nRet = contacts_record_create(_contacts_email._uri, &hEmailRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_set_int(hEmailRecord, _contacts_email.contact_id, g_nFirstRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hEmailRecord, true));

	nRet = contacts_record_set_str(hEmailRecord, _contacts_email.email, "testcontacts@gmail.com");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hEmailRecord, true));

	nRet = contacts_db_insert_record(hEmailRecord, &nEmailRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet),contacts_record_destroy(hEmailRecord, true));

	int nEnumSize = sizeof(person_property) / sizeof(person_property[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		nRet = contacts_person_set_default_property(person_property[nEnumCounter],g_nFirstPersonId,nEmailRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_set_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hEmailRecord, true));

		// Target API
		nRet = contacts_person_get_default_property(person_property[nEnumCounter],g_nFirstPersonId,&nEmailRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_get_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hEmailRecord, true));
	}

	nRet = contacts_record_destroy(hEmailRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Set/Get a default property for a record.
//& type: auto

/**
* @testcase 			ITc_contacts_person_set_get_default_property_p03
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get a default property for a record.
* @scenario				Connect to database\n
*						Add records to database\n
*						Set record's default property\n
*						Get a default property for a record\n
*						Delete records\n
* 						Disconnect from database
* @apicovered			contacts_person_set_default_property() ,contacts_person_get_default_property()
* @passcase				When contacts_person_set_default_property() and contacts_person_get_default_property() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_person_set_get_default_property_p03(void)
{
	START_TEST;

	contacts_record_h hImageRecord = NULL;
	int nImageRecordId = -1;
	char pPath[PATH_LEN] = {0,};
	if ( false == ContactsServiceAppendToAppDataPath(IMAGEPATH, pPath) )
	{
		FPRINTF("[Line : %d][%s] Unable to get the app data path\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	contacts_person_property_e person_property[] = {CONTACTS_PERSON_PROPERTY_IMAGE};
	int nRet = contacts_record_create(_contacts_image._uri, &hImageRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_set_int(hImageRecord, _contacts_image.contact_id, g_nFirstRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hImageRecord, true));

	nRet = contacts_record_set_str(hImageRecord, _contacts_image.path , pPath);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hImageRecord, true));

	nRet = contacts_db_insert_record(hImageRecord, &nImageRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet),contacts_record_destroy(hImageRecord, true));

	int nEnumSize = sizeof(person_property) / sizeof(person_property[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		nRet = contacts_person_set_default_property(person_property[nEnumCounter],g_nFirstPersonId,nImageRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_set_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hImageRecord, true));

		// Target API
		nRet = contacts_person_get_default_property(person_property[nEnumCounter],g_nFirstPersonId,&nImageRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_get_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hImageRecord, true));
	}

	nRet = contacts_record_destroy(hImageRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Set/Get a default property for a record.
//& type: auto

/**
* @testcase 			ITc_contacts_person_set_get_default_property_p04
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set/Get a default property for a record.
* @scenario				Connect to database\n
*						Add records to database\n
*						Set record's default property\n
*						Get a default property for a record\n
*						Delete records\n
* 						Disconnect from database
* @apicovered			contacts_person_set_default_property() ,contacts_person_get_default_property()
* @passcase				When contacts_person_set_default_property() and contacts_person_get_default_property() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_person_set_get_default_property_p04(void)
{
	START_TEST;

	contacts_record_h hNumberRecord = NULL;
	int nNumberRecordId = -1;
	contacts_person_property_e person_property[] = { CONTACTS_PERSON_PROPERTY_NUMBER};

	int nRet = contacts_record_create( _contacts_number._uri, &hNumberRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_set_int(hNumberRecord, _contacts_number.contact_id, g_nFirstRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true));

	nRet = contacts_record_set_str(hNumberRecord, _contacts_number.number , "9812345670");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true));

	nRet = contacts_db_insert_record(hNumberRecord, &nNumberRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true));

	int nEnumSize = sizeof(person_property) / sizeof(person_property[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		// Target API
		nRet = contacts_person_set_default_property(person_property[nEnumCounter],g_nFirstPersonId,nNumberRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_set_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true));

		// Target API
		nRet = contacts_person_get_default_property(person_property[nEnumCounter],g_nFirstPersonId,&nNumberRecordId);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_person_get_default_property", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true));
	}

	nRet = contacts_record_destroy(hNumberRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets the order of a (favorite) contact.
//& type: auto

/**
* @testcase 			ITc_contacts_person_set_favorite_order_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets the order of a (favorite) contact.
* @scenario				Connect to database\n
*						Set the order of a (favorite) contact\n
* 						Disconnect from database
* @apicovered			contacts_person_set_favorite_order()
* @passcase				When contacts_person_set_favorite_order() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_person_set_favorite_order_p(void)
{
	START_TEST;

	if ( ContactsServiceCreateAndInsertRecord(&g_nFrontRecordId, &g_nFrontContactId, &g_nFrontPersonId, &g_hFrontProfileRecord, &g_hRecordFront, "9877543211", "TESTFRONT") == false )
	{
		FPRINTF("[Line : %d][%s] failed to insert front record\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if ( ContactsServiceCreateAndInsertRecord(&g_nBackRecordId, &g_nBackContactId , &g_nBackPersonId, &g_hBackProfileRecord, &g_hRecordBack, "9876643212", "TESTBACK") == false )
	{
		FPRINTF("[Line : %d][%s] failed to insert back record\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	int nRet =  contacts_person_set_favorite_order(g_nFirstPersonId,g_nBackPersonId,g_nFrontPersonId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_set_favorite_order", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Links a person to another person.
//& type: auto

/**
* @testcase 			ITc_contacts_person_link_unlink_person_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Links a person to another person.
* @scenario				Connect to database\n
*						Links a person to another person\n
*						Unlink contact\n
* 						Disconnect from database
* @apicovered			contacts_person_link_person() , contacts_person_unlink_contact()
* @passcase				When contacts_person_link_person() and contacts_person_unlink_contact() are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_person_link_unlink_person_p(void)
{
	START_TEST;

	g_nPersonId = -1;
	if ( ContactsServiceCreateAndInsertRecord(&g_nSecondRecordId,&g_nSecondContactId, &g_nSecondPersonId, &g_hSecondProfileRecord, &g_hRecordSecond, "9886543210", "TESTSECOND") == false )
	{
		FPRINTF("[Line : %d][%s] failed to insert second record\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	int nRet =  contacts_person_link_person(g_nFirstPersonId, g_nSecondPersonId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_link_person", ContactsServiceGetError(nRet));

	// Target API
	nRet =  contacts_person_unlink_contact(g_nFirstPersonId, g_nSecondRecordId ,&g_nPersonId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_unlink_contact", ContactsServiceGetError(nRet));
	if ( g_nPersonId < 0 )
	{
		FPRINTF("[Line : %d][%s] Person id is negative\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Resets a person's usage count.
//& type: auto

/**
* @testcase 			ITc_contacts_person_reset_usage_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Resets a person's usage count
* @scenario				Connect to database\n
*						Reset a person's usage count\n
* 						Disconnect from database
* @apicovered			contacts_person_reset_usage()
* @passcase				When contacts_person_reset_usage() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_person_reset_usage_p(void)
{
	START_TEST;

	contacts_usage_type_e usage_type[] = {
		CONTACTS_USAGE_STAT_TYPE_NONE,
		CONTACTS_USAGE_STAT_TYPE_OUTGOING_CALL,
		CONTACTS_USAGE_STAT_TYPE_OUTGOING_MSG,
		CONTACTS_USAGE_STAT_TYPE_OUTGOING_EMAIL, 
		CONTACTS_USAGE_STAT_TYPE_INCOMING_CALL, 
		CONTACTS_USAGE_STAT_TYPE_INCOMING_MSG,  
		CONTACTS_USAGE_STAT_TYPE_INCOMING_EMAIL,
		CONTACTS_USAGE_STAT_TYPE_MISSED_CALL,    
		CONTACTS_USAGE_STAT_TYPE_REJECTED_CALL, 
		CONTACTS_USAGE_STAT_TYPE_BLOCKED_CALL,
		CONTACTS_USAGE_STAT_TYPE_BLOCKED_MSG};

		int nEnumSize = sizeof(usage_type) / sizeof(usage_type[0]);
		int nEnumCounter = 0;

		for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
		{
			// Target API
			int nRet =  contacts_person_reset_usage(g_nFirstPersonId,usage_type[nEnumCounter]);
			PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_reset_usage", ContactsServiceGetError(nRet));
		}
		return 0;
}


//& purpose: Gets aggregation suggestions.
//& type: auto

/**
* @testcase 			ITc_contacts_person_get_aggregation_suggestions_p
* @since_tizen			3.0
* @author            	SRID(nibha.sharma)
* @reviewer         	SRID(parshant.v)
* @type 				auto
* @description			get aggregation suggestions
* @scenario				get aggregation suggestions
* @apicovered			contacts_person_get_aggregation_suggestions()
* @passcase				When contacts_person_get_aggregation_suggestions() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect() should be called to open a connection to the contacts service.
* @postcondition		None
*/
int ITc_contacts_person_get_aggregation_suggestions_p(void)
{
	START_TEST;
	
	contacts_list_h hList = NULL;
		
	// Target API
	int nRet =  contacts_person_get_aggregation_suggestions(g_nFirstPersonId,0,&hList);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_person_get_aggregation_suggestions", ContactsServiceGetError(nRet));
	if(hList == NULL)
	{
		FPRINTF("[Line : %d][%s] hList is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	nRet = contacts_list_destroy(hList,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet));
	
	return 0;
}

/** @} */ 
/** @} */
