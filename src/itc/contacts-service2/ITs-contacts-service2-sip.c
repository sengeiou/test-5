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
* @function 		ITs_contacts_service2_sip_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_sip_startup(void)
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
* @function 		ITs_contacts_service2_sip_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_sip_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-sip-testcases
*  @brief 		Integration testcases for module contacts_service2-sip
*  @ingroup 	itc-contacts_service2-sip
*  @{
*/
//& purpose: Creates/Destroys a record for sip URI.
//& type: auto

/**
* @testcase 		ITc_contacts_record_create_destroy_sip_p
* @since_tizen		3.0
* @author           SRID(nibha.sharma)
* @reviewer         SRID(parshant.v)
* @type 			auto
* @description		Creates/Destroys a record for sip URI.
* @scenario			Connect to database\n
*					Create Record for sip URI\n
*					Destroy Record for sip URI\n
* 					Disconnect from database 
* @apicovered		contacts_record_create(), contacts_record_destroy()
* @passcase			When contacts_record_create() contacts_record_destroy() are successful for sip URI.
* @failcase			If target API fails or any precondition API fails.
* @precondition		contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition	record must be released with contacts_record_destroy()
*/
int ITc_contacts_record_create_destroy_sip_p(void)
{
	START_TEST;

	contacts_record_h hNameRecord = NULL;

	// Target sip URI
	int nRet = contacts_record_create(_contacts_sip._uri, &hNameRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));
	CHECK_HANDLE(hNameRecord, "contacts_record_create");

	nRet = contacts_record_destroy(hNameRecord,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets a string(for sip view) to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_set_get_str_sip_p
* @since_tizen		3.0
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		Sets/Gets a string(for sip view) to a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Set a string(for sip view) to a record\n
*					Get string(for sip view)\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_set_str(),  contacts_record_get_str()
* @passcase			When  contacts_record_set_str()  contacts_record_get_str() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	value must be released with free()
*/
int ITc_contacts_record_set_get_str_sip_p(void)
{
	START_TEST;

	contacts_record_h hAddRecord = NULL;
	char* pszSetAdd = "Samsung Delhi";
	char* pszGetAdd = NULL;

	int nRet = contacts_record_create(_contacts_sip._uri, &hAddRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));
	CHECK_HANDLE(hAddRecord, "contacts_record_create");

	// Target address variable(for sip view)
	nRet = contacts_record_set_str(hAddRecord, _contacts_sip.address, pszSetAdd);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet) , contacts_record_destroy(hAddRecord,true));

	nRet = contacts_record_get_str(hAddRecord, _contacts_sip.address, &pszGetAdd);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] contacts_record_get_str failed , error returned = %s\\n", __LINE__ , API_NAMESPACE, ContactsServiceGetError(nRet));
		FREE_MEMORY(pszGetAdd);

		nRet = contacts_record_destroy(hAddRecord,true);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return 1;
	}

	if ( strcmp(pszSetAdd,pszGetAdd) != 0 )
	{
		FPRINTF("[Line : %d][%s] set get values are not same\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetAdd);

		nRet = contacts_record_destroy(hAddRecord,true);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return 1;
	}
	
	FREE_MEMORY(pszGetAdd);
	
	nRet = contacts_record_destroy(hAddRecord,true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets/Gets an integer value(for sip view) to a record.
//& type: auto

/**
* @testcase 		ITc_contacts_record_set_get_int_sip_p
* @since_tizen		3.0
* @author			SRID(nibha.sharma)
* @reviewer			SRID(parshant.v)
* @type 			auto
* @description		Sets/Gets an integer value(for sip view) to a record.
* @scenario			Connect to database\n
*					Create Record\n
*					Set an integer value(for sip view) to a record\n
*					Get integer value(for sip view)\n
*					Check set get values\n
*					Destroy Record\n
* 					Disconnect from database
* @apicovered		contacts_record_set_int(),  contacts_record_get_int()
* @passcase			When  contacts_record_set_int()  contacts_record_get_int() are successful.
* @failcase			If target API fails or any precondition API fails.
* @precondition		NA
* @postcondition	NA
*/

int ITc_contacts_record_set_get_int_sip_p(void)
{
	START_TEST;

	contacts_record_h hMainRecord = NULL;
	int nSet = 1;
	int nGet = 0;

	int nRet = contacts_record_create(_contacts_sip._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));
	CHECK_HANDLE(hMainRecord, "contacts_record_create");

	// Target contact_id variable(for sip view)
	nRet = contacts_record_set_int(hMainRecord, _contacts_sip.contact_id, nSet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord,true));

	nRet = contacts_record_get_int(hMainRecord,_contacts_sip.contact_id, &nGet);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord,true));

	if ( nSet != nGet )
	{
		FPRINTF("[Line : %d][%s] get values are not same\\n", __LINE__, API_NAMESPACE);
		contacts_record_destroy(hMainRecord,true);
		return 1;
	}

	nRet = contacts_record_destroy(hMainRecord,true);
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
