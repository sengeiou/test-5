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

contacts_query_h g_hQuery;

/**
* @function 		ITs_contacts_service2_query_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_query_startup(void)
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
		int nRet = contacts_query_create(_contacts_person._uri, &g_hQuery);
		if ( nRet == CONTACTS_ERROR_NONE )
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
* @function 		ITs_contacts_service2_query_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_query_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_query_destroy(g_hQuery);
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-query-testcases
*  @brief 		Integration testcases for module contacts_service2-query
*  @ingroup 	itc-contacts_service2-query
*  @{
*/

//& purpose: Creates/Destroys a query.
//& type: auto

/**
* @testcase 			ITc_contacts_query_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates/Destroys a query.
* @scenario				Connect to database\n
*						Create a query\n
*						Destroy the query\n
* 						Disconnect from database
* @apicovered			contacts_query_create(), contacts_query_destroy()
* @passcase				When contacts_query_create and contacts_query_destroy are successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_query_create_destroy_p(void)
{
	START_TEST;

	contacts_query_h query = NULL;

	// Target API
	int nRet = contacts_query_create(_contacts_person._uri, &query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_query_destroy(query);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets a filter for query.
//& type: auto

/**
* @testcase 			ITc_contacts_query_set_filter_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a filter for query.
* @scenario				Connect to database\n
*						Create a query\n
*						Create filter\n
*						Set the filter for query\n
*						Destroy filter\n
*						Destroy the query\n
* 						Disconnect from database
* @apicovered			contacts_query_set_filter()
* @passcase				When contacts_query_set_filter is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_query_set_filter_p(void)
{
	START_TEST;

	contacts_filter_h filter = NULL;

	int nRet = contacts_filter_create(_contacts_person._uri, &filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_create", ContactsServiceGetError(nRet));

	// Target API
	nRet = contacts_query_set_filter(g_hQuery,filter);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_query_set_filter", ContactsServiceGetError(nRet),contacts_filter_destroy(filter));

	nRet = contacts_filter_destroy(filter);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_filter_destroy", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Adds property IDs for projection.
//& type: auto

/**
* @testcase 			ITc_contacts_query_set_projection_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds property IDs for projection.
* @scenario				Connect to database\n
*						Create a query\n
*						Add property IDs for projection\n
*						Destroy the query\n
* 						Disconnect from database 
* @apicovered			contacts_query_set_projection()
* @passcase				When contacts_query_set_projection is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_query_set_projection_p(void)
{
	START_TEST;

	unsigned int person_projection[] = {_contacts_person.id,_contacts_person.display_name,};

	// Target API
	int nRet = contacts_query_set_projection(g_hQuery, person_projection,sizeof(person_projection)/sizeof(int));
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_set_projection", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets a sort mode for query.
//& type: auto

/**
* @testcase 			ITc_contacts_query_set_sort_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a sort mode for query.
* @scenario				Connect to database\n
*						Create a query\n
*						Set a sort mode for query\n
*						Destroy the query\n
* 						Disconnect from database
* @apicovered			contacts_query_set_sort()
* @passcase				When contacts_query_set_sort is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_query_set_sort_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_query_set_sort(g_hQuery,_contacts_person.display_name, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_set_sort", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Sets the distinct option
//& type: auto
/**
* @testcase 			ITc_contacts_query_set_distinct_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set the distinct option for projection
* @scenario				Connect to database\n
*						Create a query\n
*						Set the distinct option for projection\n
*						Destroy the query\n
* 						Disconnect from database
* @apicovered			contacts_query_set_distinct()
* @passcase				When contacts_query_set_distinct is successful
* @failcase				If target API fails or any precondition API fails.
* @precondition			None
* @postcondition		None
*/
int ITc_contacts_query_set_distinct_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_query_set_distinct(g_hQuery,true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_query_set_distinct", ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
