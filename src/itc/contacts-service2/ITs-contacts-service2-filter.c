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
* @function 		ITs_contacts_service2_filter_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_filter_startup(void)
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
* @function 		ITs_contacts_service2_filter_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_filter_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/********************************************************************************************/

/** @addtogroup itc-contacts_service2-filter-testcases
*  @brief 		Integration testcases for module contacts_service2-filter
*  @ingroup 	itc-contacts_service2-filter
*  @{
*/

//& purpose: Creates/Destroys a filter.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates/Destroys a filter.
* @scenario				Connect to database\n
*						Create filter\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_create() , contacts_filter_destroy()
* @passcase				When contacts_filter_create() and contacts_filter_destroy() are successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_contacts_filter_create_destroy_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;

	// Target API
	int nRet = contacts_filter_create(_contacts_number._uri, &filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

	nRet = contacts_filter_destroy(filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Adds a condition for a boolean type property.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_bool_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a condition for a boolean type property.
* @scenario				Connect to database\n
*						Create filter\n
*						Add a condition for a boolean type property\n
*						Destroy filter\n
* 						Disconnect from database 
* @apicovered			contacts_filter_add_bool()
* @passcase				When contacts_filter_add_bool() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_bool_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;

	int nRet = contacts_filter_create(_contacts_number._uri, &filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_filter_add_bool(filter,_contacts_number.is_default, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_bool", ContactsServiceGetError(nRet) , contacts_filter_destroy(filter));

	nRet = contacts_filter_destroy(filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
	return 0;

}

//& purpose: Adds a condition for an integer type property.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_int_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a condition for an integer type property.
* @scenario				Connect to database\n
*						Create filter\n
*						Add a condition for a integer type property\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_add_int()
* @passcase				When contacts_filter_add_int() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_int_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;
	contacts_match_int_flag_e int_flag[] = {
		CONTACTS_MATCH_EQUAL,
		CONTACTS_MATCH_GREATER_THAN,
		CONTACTS_MATCH_GREATER_THAN_OR_EQUAL,
		CONTACTS_MATCH_LESS_THAN,
		CONTACTS_MATCH_LESS_THAN_OR_EQUAL,
		CONTACTS_MATCH_NOT_EQUAL,
		CONTACTS_MATCH_NONE };

		int nEnumSize = sizeof(int_flag) / sizeof(int_flag[0]);
		int nEnumCounter = 0;

		for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
		{
			int nRet = contacts_filter_create(_contacts_number._uri, &filter);
			PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

			// Target API
			nRet = contacts_filter_add_int(filter,_contacts_number.id, int_flag[nEnumCounter], 0);
			PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet) , contacts_filter_destroy(filter));

			nRet = contacts_filter_destroy(filter);
			PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
		}

		return 0;
}

//& purpose: Adds a condition for a string type property.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_str_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a condition for a string type property.
* @scenario				Connect to database\n
*						Create filter\n
*						Add a condition for a string type property\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_add_str()
* @passcase				When contacts_filter_add_str() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_str_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;
	contacts_match_str_flag_e str_flag[] = { CONTACTS_MATCH_EXACTLY,
		CONTACTS_MATCH_FULLSTRING, CONTACTS_MATCH_CONTAINS,
		CONTACTS_MATCH_STARTSWITH, CONTACTS_MATCH_ENDSWITH,
		CONTACTS_MATCH_EXISTS};

	int nEnumSize = sizeof(str_flag) / sizeof(str_flag[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		int nRet = contacts_filter_create(_contacts_number._uri, &filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

		// Target API
		nRet = contacts_filter_add_str(filter,_contacts_number.number, str_flag[nEnumCounter], "987");
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_str", ContactsServiceGetError(nRet) , contacts_filter_destroy(filter));

		nRet = contacts_filter_destroy(filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
	}

	return 0;
}

//& purpose: Adds a condition for a double type property.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_double_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a condition for a double type property.
* @scenario				Connect to database\n
*						Create filter\n
*						Add a condition for a double type property\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_add_double()
* @passcase				When contacts_filter_add_double() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_double_p(void)
{
	START_TEST;

	double nMatch = 1.0;
	contacts_filter_h filter = NULL;
	contacts_match_int_flag_e int_flag[] = { CONTACTS_MATCH_EQUAL,
		CONTACTS_MATCH_GREATER_THAN, CONTACTS_MATCH_GREATER_THAN_OR_EQUAL,
		CONTACTS_MATCH_LESS_THAN, CONTACTS_MATCH_LESS_THAN_OR_EQUAL,
		CONTACTS_MATCH_NOT_EQUAL, CONTACTS_MATCH_NONE };

	int nEnumSize = sizeof(int_flag) / sizeof(int_flag[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		int nRet = contacts_filter_create(_contacts_person._uri, &filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

		// Target API
		nRet = contacts_filter_add_double(filter,_contacts_person.favorite_priority, int_flag[nEnumCounter], nMatch);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_double", ContactsServiceGetError(nRet), contacts_filter_destroy(filter));

		nRet = contacts_filter_destroy(filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
	}

	return 0;
}

//& purpose: Adds an operator between conditions.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_operator_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds an operator between conditions.
* @scenario				Connect to database\n
*						Create filter\n
*						Add an operator between conditions\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_add_operator()
* @passcase				When contacts_filter_add_operator() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_operator_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;
	contacts_filter_operator_e operator[] = { CONTACTS_FILTER_OPERATOR_AND, CONTACTS_FILTER_OPERATOR_OR};

	int nEnumSize = sizeof(operator) / sizeof(operator[0]);
	int nEnumCounter = 0;

	for ( nEnumCounter=0; nEnumCounter<nEnumSize; nEnumCounter++ )
	{
		int nRet = contacts_filter_create(_contacts_number._uri, &filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

		nRet = contacts_filter_add_int(filter,_contacts_number.id, CONTACTS_MATCH_EQUAL, 0);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet),contacts_filter_destroy(filter));

		// Target API
		nRet = contacts_filter_add_operator(filter,operator[nEnumCounter]);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_operator", ContactsServiceGetError(nRet),contacts_filter_destroy(filter));

		nRet = contacts_filter_add_int(filter,_contacts_number.id, CONTACTS_MATCH_EQUAL, 0);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet),contacts_filter_destroy(filter));

		nRet = contacts_filter_destroy(filter);
		PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
	}

	return 0;
}

//& purpose: Adds a filter to a given filter.
//& type: auto

/**
* @testcase 			ITc_contacts_filter_add_filter_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a filter to a given filter.
* @scenario				Connect to database\n
*						Create filter\n
*						Adds a filter to a given filter\n
*						Destroy filter\n
* 						Disconnect from database
* @apicovered			contacts_filter_add_filter()
* @passcase				When contacts_filter_add_filter() is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_filter_add_filter_p(void)
{
	START_TEST;

	contacts_filter_h filter1 = NULL;
	contacts_filter_h filter2 = NULL;

	int nRet = contacts_filter_create(_contacts_number._uri, &filter1);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

	nRet = contacts_filter_create(_contacts_number._uri, &filter2);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet), contacts_filter_destroy(filter1));

	nRet = contacts_filter_add_int(filter1,_contacts_number.id, CONTACTS_MATCH_EQUAL, 0);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet), contacts_filter_destroy(filter1);contacts_filter_destroy(filter2));

	nRet = contacts_filter_add_int(filter2,_contacts_number.id, CONTACTS_MATCH_EQUAL, 1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_int", ContactsServiceGetError(nRet), contacts_filter_destroy(filter1);contacts_filter_destroy(filter2));

	nRet = contacts_filter_add_operator(filter1,CONTACTS_FILTER_OPERATOR_AND);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_operator", ContactsServiceGetError(nRet), contacts_filter_destroy(filter1);contacts_filter_destroy(filter2));


	// Target API
	nRet = contacts_filter_add_filter(filter1,filter2);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_add_filter", ContactsServiceGetError(nRet), contacts_filter_destroy(filter1);contacts_filter_destroy(filter2));

	nRet = contacts_filter_destroy(filter1);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet), contacts_filter_destroy(filter2));

	nRet = contacts_filter_destroy(filter2);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));
	return 0;
}
/** @} */ 
/** @} */
