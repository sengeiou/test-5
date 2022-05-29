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
// See the License for the specific language governing permissions 
// limitations under the License.
//
#include "ITs-contacts-service2-common.h"

/** @addtogroup itc-contacts-service2
*  @ingroup itc
*  @{
*/

//& set: ContactsService

/**
* @function 		ITs_contacts_service2_record_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_record_startup(void)
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
* @function 		ITs_contacts_service2_record_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_record_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-record-testcases
*  @brief 		Integration testcases for module contacts_service2-record
*  @ingroup 	itc-contacts_service2-record
*  @{
*/
//& purpose: Creates/Destroys a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_create_destroy_p
* @since_tizen		2.3
* @author            SRID(sk.roy)
* @reviewer         SRID(gupta.sanjay)
* @type 			auto
* @description		Creates/Destroys a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Destroy Record\n
* 					Disconnect from database 
* @apicovered		contacts_record_create(), contacts_record_destroy()
* @passcase			When contacts_record_create() contacts_record_destroy() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition	record must be released with contacts_record_destroy()
*/
int ITc_contacts_record_create_destroy_p(void)
{
	START_TEST;

	contacts_record_h hNameRecord = NULL;

	// Target API
	int nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Adds/Removes a child record to the parent record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_add_remove_child_record_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Adds/Removes a child record to the parent record.
* @scenario			Connect to database\n
*					Create Record\n
*					Add child record\n
*					Remove child record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_add_child_record(), contacts_record_remove_child_record()
* @passcase			When contacts_record_add_child_record() contacts_record_remove_child_record() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_contacts_record_add_remove_child_record_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	contacts_record_h hNameRecord = NULL;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet), contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_remove_child_record", ContactsServiceGetError(nRet), contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Makes a clone of a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_clone_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Makes a clone of a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Clone record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_clone()
* @passcase			When contacts_record_clone() is successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	cloned_record must be released with contacts_record_destroy().
*/
int ITc_contacts_record_clone_p(void)
{
	START_TEST;

	contacts_record_h hNameRecord = NULL;
	contacts_record_h hClonedRecord = NULL;

	int nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_clone(hNameRecord,&hClonedRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_clone", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true));

	nRet = contacts_record_destroy(hClonedRecord,true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true));

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Gets the number of child records of a parent record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_get_child_record_count_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Gets the number of child records of a parent record.
* @scenario			Connect to database\n
*					    Create Record\n
*					Add child record\n
*					Get the number of child records\n
*					Remove child record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_get_child_record_count()
* @passcase			When contacts_record_get_child_record_count() is successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_contacts_record_get_child_record_count_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	contacts_record_h hNameRecord = NULL;
	int nCount = 0;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_get_child_record_count(hMainRecord, _contacts_contact.name, &nCount);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_child_record_count", ContactsServiceGetError(nRet) , contacts_record_remove_child_record(hMainRecord,_contacts_contact.name, hNameRecord);
	contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	if ( nCount == 0 )
	{
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_child_record_count", ContactsServiceGetError(nRet) , contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
		contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));
	}

	nRet = contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_remove_child_record", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet) , contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Gets a child record handle pointer from the parent record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_get_child_record_at_p_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Gets a child record handle pointer from the parent record.
* @scenario			Connect to database\n
*					Create Record\n
*					Add child record\n
*					Get the child record handle pointer from the parent record\n
*					Remove child record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_get_child_record_at_p()
* @passcase			When contacts_record_get_child_record_at_p() is successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/

int ITc_contacts_record_get_child_record_at_p_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	contacts_record_h hNameRecord = NULL;
	contacts_record_h hChildRecord = NULL;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_get_child_record_at_p(hMainRecord, _contacts_contact.name, 0, &hChildRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_child_record_count", 
		ContactsServiceGetError(nRet) ,contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: Clones a child record list of the given parent record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_clone_child_record_list_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Clones a child record list of the given parent record.
* @scenario			Connect to database\n
*					Create Record\n
*					Add child record\n
*					Clones the child record list\n
*					Destroy list\n
*					Remove child record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_clone_child_record_list()
* @passcase			When contacts_record_clone_child_record_list() is successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/

int ITc_contacts_record_clone_child_record_list_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	contacts_record_h hNameRecord = NULL;
	contacts_list_h	hCloneList;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_clone_child_record_list(hMainRecord, _contacts_contact.name,&hCloneList);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_clone_child_record_list", ContactsServiceGetError(nRet) , contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	if ( hCloneList == NULL )
	{
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_clone_child_record_list", ContactsServiceGetError(nRet), contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));
	}

	nRet = contacts_list_destroy(hCloneList,true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_list_destroy", ContactsServiceGetError(nRet) , contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_remove_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_remove_child_record", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true);contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet) , contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets a string to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_set_get_str_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets/Gets a string to a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Set a string to a record\n
*					Get string\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_set_str(),  contacts_record_get_str()
* @passcase			When  contacts_record_set_str()  contacts_record_get_str() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	value must be released with free()
*/
int ITc_contacts_record_set_get_str_p(void)
{
	START_TEST;

	contacts_record_h hNameRecord = NULL;
	char* pszSetName = "SetName";
	char* pszGetName = NULL;

	int nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_set_str(hNameRecord, _contacts_name.first, pszSetName);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet) , contacts_record_destroy(hNameRecord,true));

	// Target API
	nRet = contacts_record_get_str(hNameRecord, _contacts_name.first, &pszGetName);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] contacts_record_get_str failed , error returned = %s\\n", __LINE__ , API_NAMESPACE, ContactsServiceGetError(nRet));
		FREE_MEMORY(pszGetName);

		nRet = contacts_record_destroy(hNameRecord,true);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return 1;
	}

	if ( strcmp(pszSetName,pszGetName) != 0 )
	{
		FPRINTF("[Line : %d][%s] set get values are not same\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetName);

		nRet = contacts_record_destroy(hNameRecord,true);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return 1;
	}

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets an integer value to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_set_get_int_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets/Gets an integer value to a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Set an integer value to a record\n
*					Get integer value\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_set_int(),  contacts_record_get_int()
* @passcase			When  contacts_record_set_int()  contacts_record_get_int() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/

int ITc_contacts_record_set_get_int_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	int nSet = 1;
	int nGet;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_set_int(hMainRecord, _contacts_contact.link_mode, nSet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_get_int(hMainRecord,_contacts_contact.link_mode, &nGet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord,true));

	if ( nSet != nGet )
	{
		FPRINTF("[Line : %d][%s] get values are not same\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hMainRecord,true);
		return 1;
	}

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets a boolean value to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_set_get_bool_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets/Gets a boolean value to a record
* @scenario			Connect to database\n
*					Create Record\n
*					Set an boolean value to a record\n
*					Get boolean value\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_set_bool(),  contacts_record_get_bool()
* @passcase			When  contacts_record_set_bool() contacts_record_get_bool() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/

int ITc_contacts_record_set_get_bool_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	bool bSet = true;
	bool bGet = false;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_set_bool(hMainRecord, _contacts_contact.is_favorite, bSet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_bool", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	// Target API
	nRet = contacts_record_get_bool(hMainRecord,_contacts_contact.is_favorite, &bGet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_bool", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	if ( bSet != bGet )
	{
		FPRINTF("[Line : %d][%s] set get values are not same\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hMainRecord,true);
		return 1;
	}

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Gets URI string from a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_get_uri_p_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Gets URI string from a record
* @scenario			Connect to database\n
*					Create Record\n
*					Get URI string from a record\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_get_uri_p()
* @passcase			When contacts_record_get_uri_p() is successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_contacts_record_get_uri_p_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	const char *pszViewUri = NULL;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_get_uri_p(hMainRecord, &pszViewUri);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_uri_p", ContactsServiceGetError(nRet), contacts_record_destroy(hMainRecord,true));

	if ( pszViewUri == NULL )
	{
		FPRINTF("[Line : %d][%s] contacts_record_get_uri_p returned null view uri\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hMainRecord,true);
		return 1;
	}

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}

//& purpose: Gets a string to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_get_str_p_p
* @since_tizen		2.3
* @author			SRID(sk.roy)
* @reviewer			SRID(gupta.sanjay)
* @type 			auto
* @description		Sets/Gets a string to a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Set a string to a record\n
*					Get string\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_create, contacts_record_set_str(),  contacts_record_get_str_p()
* @passcase			When  contacts_record_set_str() contacts_record_get_str_p() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	value must not be released with free()
*/
int ITc_contacts_record_get_str_p_p(void)
{
	START_TEST;

	contacts_record_h hNameRecord = NULL;
	char* pszSetName = "SetName";
	char* pszGetName = NULL;

	int nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_record_set_str(hNameRecord, _contacts_name.first, pszSetName);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet), contacts_record_destroy(hNameRecord,true));

	// Target API
	nRet = contacts_record_get_str_p(hNameRecord, _contacts_name.first, &pszGetName);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_str_p", ContactsServiceGetError(nRet), contacts_record_destroy(hNameRecord,true));

	if ( strcmp(pszSetName,pszGetName) != 0 )
	{
		FPRINTF("[Line : %d][%s] set get values are not same\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hNameRecord,true);
		return 1;
	}

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
	return 0;
}
/** @} */ 
/** @} */
