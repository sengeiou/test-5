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
* @function 		ContactsVcardParseCB
* @description	 	Called to get a record handle of _contacts_contact view.
* @parameter		contacts_record_h record, void *user_data
* @return 			bool
*/
static bool ContactsVcardParseCB(contacts_record_h record, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] ContactsVcardParseCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pContactsServiceMainLoop )
	{
		g_main_loop_quit(g_pContactsServiceMainLoop);
	}
	return false;
}

/****************************************************************************/

/**
* @function 		ITs_contacts_service2_vcard_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_vcard_startup(void)
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
		if ( ContactsServiceCreateAndInsertRecord(&g_nFirstRecordId, &g_nFirstContactId, &g_nFirstPersonId, &g_hFirstProfileRecord, &g_hRecordFirst, "099882724", "TESTFIRST_v") == true )
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
* @function 		ITs_contacts_service2_vcard_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_vcard_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_record_destroy(g_hRecordFirst, true);
	contacts_record_destroy(g_hFirstProfileRecord, true);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstRecordId);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstContactId);
	contacts_db_delete_record(_contacts_person._uri, g_nFirstPersonId);
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-vcard-testcases
*  @brief 		Integration testcases for module contacts_service2-vcard
*  @ingroup 	itc-contacts_service2-vcard
*  @{
*/

//& purpose: Retrieves the count of contact entities from a vCard file.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_get_entity_count_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the count of contact entities from a vCard file.
* @scenario				Connect to database\n
*						Retrieves the count of contact entities from a vCard file\n
* 						Disconnect from database
* @apicovered			contacts_vcard_get_entity_count()
* @passcase				When contacts_vcard_get_entity_count() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_get_entity_count_p(void)
{
	START_TEST;

	int nCount = 0;
	bool isVcardCreated = false;
	isVcardCreated = CreateVcard();
	if ( isVcardCreated != true )
	{
		FPRINTF("[Line : %d][%s] %s failed, returned = %d\\n", __LINE__, API_NAMESPACE, "CreateVcard", isVcardCreated);
		return 1;
	}

	// Target API
	int nRet = contacts_vcard_get_entity_count(VCFPATH,&nCount);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_get_entity_count", ContactsServiceGetError(nRet));
	if ( nCount == 0 )
	{
		FPRINTF("[Line : %d][%s] Count is 0\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Retrieves the vCard stream from a contact.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_make_from_contact_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the vCard stream from a contact.
* @scenario				Connect to database\n
*						Add contact\n
*						Retrieves the vCard stream from a contact\n
*						Delete contact\n
* 						Disconnect from database
* @apicovered			contacts_vcard_make_from_contact()
* @passcase				When contacts_vcard_make_from_contact() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_make_from_contact_p(void)
{
	START_TEST;

	char *vcard = NULL;

	// Target API
	int nRet = contacts_vcard_make_from_contact(g_hRecordFirst,&vcard);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_make_from_contact", ContactsServiceGetError(nRet));
	if ( vcard == NULL )
	{
		FPRINTF("[Line : %d][%s] vcard is NULL\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Retrieves the vCard stream from a contact.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_make_from_my_profile_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the vCard stream from a contact.
* @scenario				Connect to database\n
*						Add contact\n
*						Retrieves the vCard stream from a contact\n
*						Delete contact\n
* 						Disconnect from database
* @apicovered			contacts_vcard_make_from_my_profile()
* @passcase				When contacts_vcard_make_from_my_profile() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_make_from_my_profile_p(void)
{
	START_TEST;

	char *vcard = NULL;

	// Target API
	int nRet = contacts_vcard_make_from_my_profile(g_hFirstProfileRecord,&vcard);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_make_from_my_profile", ContactsServiceGetError(nRet));
	if ( vcard == NULL )
	{
		FPRINTF("[Line : %d][%s] vcard is NULL\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Retrieves the vCard stream from a person.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_make_from_person_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the vCard stream from a person.
* @scenario				Connect to database\n
*						Add contact\n
*						Retrieves the  vCard stream from a person\n
*						Delete contact\n
* 						Disconnect from database
* @apicovered			contacts_vcard_make_from_person()
* @passcase				When contacts_vcard_make_from_person() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_make_from_person_p(void)
{
	START_TEST;

	char *vcard = NULL;
	contacts_record_h hPersonRecord = NULL;

	int nRet = contacts_db_get_record(_contacts_person._uri, g_nFirstPersonId, &hPersonRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_vcard_make_from_person(hPersonRecord,&vcard);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_make_from_person", ContactsServiceGetError(nRet), contacts_record_destroy(hPersonRecord, true));
	if ( vcard == NULL )
	{
		FPRINTF("[Line : %d][%s] vcard is NULL\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	nRet = contacts_record_destroy(hPersonRecord, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Retrieves all contacts with a record handle (_contacts_contact) from a vCard file.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_parse_to_contact_foreach_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all contacts with a record handle (_contacts_contact) from a vCard file.
* @scenario				Connect to database\n
*						Retrieves all contacts with a record handle from a vCard file\n
*						Check callback is invoked or not\n
* 						Disconnect from database
* @apicovered			contacts_vcard_parse_to_contact_foreach()
* @passcase				When contacts_vcard_parse_to_contact_foreach() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		ContactsVcardParseCB must be invoked
*/
int ITc_contacts_vcard_parse_to_contact_foreach_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	bool isVcardCreated = false;
	isVcardCreated = CreateVcard();
	if ( isVcardCreated != true )
	{
		FPRINTF("[Line : %d][%s] %s failed, returned = %d\\n", __LINE__, API_NAMESPACE , "CreateVcard", isVcardCreated);
		return 1;
	}

	g_bCallbackHit = false;

	// Target API
	int nRet = contacts_vcard_parse_to_contact_foreach(VCFPATH,ContactsVcardParseCB,NULL);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_parse_to_contact_foreach", ContactsServiceGetError(nRet));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] Failed to call callback\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Retrieves all contacts with a contacts list from a vCard stream.
//& type: auto

/**
* @testcase 			ITc_contacts_vcard_parse_to_contacts_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all contacts with a contacts list from a vCard stream.
* @scenario				Connect to database\n
*						Create contact\n
*						Make vcard stream\n
*						Retrieves all contacts with a contacts list from a vCard stream\n
*						Delete contact\n
* 						Disconnect from database
* @apicovered			contacts_vcard_parse_to_contacts()
* @passcase				When contacts_vcard_parse_to_contacts() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_parse_to_contacts_p(void)
{
	START_TEST;

	contacts_list_h list = NULL;
	char *vcard = NULL;

	int nRet = contacts_vcard_make_from_contact(g_hRecordFirst,&vcard);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_make_from_contact", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_vcard_parse_to_contacts(vcard,&list);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_parse_to_contacts", ContactsServiceGetError(nRet));

	if ( list == NULL )
	{
		FPRINTF("[Line : %d][%s] Contact List is Null\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Sets and Gets the limit size of photos to append in vCard streams
//& type: auto

/**
* @testcase 				ITc_contacts_vcard_set_get_limit_size_of_photo_p
* @since_tizen			3.0
* @author            		SRID(nibha.sharma)
* @reviewer         		SRID(a.pandia1)
* @type 						auto
* @description			Sets and Gets the limit size of photos to append in vCard streams
* @scenario				contacts_vcard_set_limit_size_of_photo,contacts_vcard_get_limit_size_of_photo		
* @apicovered			contacts_vcard_set_limit_size_of_photo,contacts_vcard_get_limit_size_of_photo
* @passcase				When contacts_vcard_set_limit_size_of_photo and contacts_vcard_get_limit_size_of_photo are successful.
* @failcase					If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_vcard_set_get_limit_size_of_photo_p(void)
{
	START_TEST;
	
	unsigned int nSetSize = 800;
	unsigned int nGetSize = 0;

	//Target API
	int nRet = contacts_vcard_set_limit_size_of_photo(nSetSize);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_set_limit_size_of_photo", ContactsServiceGetError(nRet));
	
	//Target API
	nRet = contacts_vcard_get_limit_size_of_photo(&nGetSize);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_vcard_get_limit_size_of_photo", ContactsServiceGetError(nRet));
	
	if(nSetSize != nGetSize)
	{
		FPRINTF("[Line : %d][%s] size values are different\\n", __LINE__ , API_NAMESPACE);
		return 1;
	}

	return 0;
}
/** @} */ 
/** @} */
