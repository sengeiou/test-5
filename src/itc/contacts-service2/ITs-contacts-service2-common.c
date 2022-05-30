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

//Add helper function definitions here

/**
* @function 		ContactsServiceGetDataPath
* @description	 	Returnes the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool ContactsServiceGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path;app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		ContactsServiceAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path;pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool ContactsServiceAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF("[Line : %d][%s] Null Path provided;Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == ContactsServiceGetDataPath(pAppDataPath))
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line : %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);

	return true;
}

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
	case CONTACTS_ERROR_NOT_SUPPORTED:			szErrorVal = "CONTACTS_ERROR_NOT_SUPPORTED";				break;
	default:							szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForInt
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForInt(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CONTACTS_MATCH_EQUAL:						szErrorVal = "CONTACTS_MATCH_EQUAL";					break;
	case CONTACTS_MATCH_GREATER_THAN:				szErrorVal = "CONTACTS_MATCH_GREATER_THAN";				break;
	case CONTACTS_MATCH_GREATER_THAN_OR_EQUAL:		szErrorVal = "CONTACTS_MATCH_GREATER_THAN_OR_EQUAL";	break;
	case CONTACTS_MATCH_LESS_THAN:					szErrorVal = "CONTACTS_MATCH_LESS_THAN";				break;
	case CONTACTS_MATCH_LESS_THAN_OR_EQUAL:			szErrorVal = "CONTACTS_MATCH_LESS_THAN_OR_EQUAL";		break;
	case CONTACTS_MATCH_NOT_EQUAL:					szErrorVal = "CONTACTS_MATCH_NOT_EQUAL";				break;
	case CONTACTS_MATCH_NONE:						szErrorVal = "CONTACTS_MATCH_NONE";						break;
	default:										szErrorVal = "Unknown Match";							break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForStr
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForStr(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_MATCH_EXACTLY:			szErrorVal = "CONTACTS_MATCH_EXACTLY";			break;
	case CONTACTS_MATCH_FULLSTRING:			szErrorVal = "CONTACTS_MATCH_FULLSTRING";		break;
	case CONTACTS_MATCH_CONTAINS:			szErrorVal = "CONTACTS_MATCH_CONTAINS";			break;
	case CONTACTS_MATCH_STARTSWITH:			szErrorVal = "CONTACTS_MATCH_STARTSWITH";		break;
	case CONTACTS_MATCH_ENDSWITH:			szErrorVal = "CONTACTS_MATCH_ENDSWITH";			break;
	case CONTACTS_MATCH_EXISTS:				szErrorVal = "CONTACTS_MATCH_EXISTS";			break;
	default:								szErrorVal = "Unknown Match";					break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForOperator
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForOperator(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_FILTER_OPERATOR_AND:			szErrorVal = "CONTACTS_FILTER_OPERATOR_AND";		break;
	case CONTACTS_FILTER_OPERATOR_OR:			szErrorVal = "CONTACTS_FILTER_OPERATOR_OR";			break;
	default:									szErrorVal = "Unknown Filter";						break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForDisplayOrder
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForDisplayOrder(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST:		szErrorVal = "CONTACTS_NAME_DISPLAY_ORDER_FIRSTLAST";		break;
	case CONTACTS_NAME_DISPLAY_ORDER_LASTFIRST:		szErrorVal = "CONTACTS_NAME_DISPLAY_ORDER_LASTFIRST";		break;
	default:										szErrorVal = "Unknown Order";								break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForSortingOrder
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForSortingOrder(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_NAME_SORTING_ORDER_FIRSTLAST:		szErrorVal = "CONTACTS_NAME_SORTING_ORDER_FIRSTLAST";		break;
	case CONTACTS_NAME_SORTING_ORDER_LASTFIRST:		szErrorVal = "CONTACTS_NAME_SORTING_ORDER_LASTFIRST";		break;
	default:										szErrorVal = "Unknown Order";								break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForPersonProperty
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForPersonProperty(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_PERSON_PROPERTY_NAME_CONTACT:		szErrorVal = "CONTACTS_PERSON_PROPERTY_NAME_CONTACT";		break;
	case CONTACTS_PERSON_PROPERTY_NUMBER:			szErrorVal = "CONTACTS_PERSON_PROPERTY_NUMBER";				break;
	case CONTACTS_PERSON_PROPERTY_EMAIL:			szErrorVal = "CONTACTS_PERSON_PROPERTY_EMAIL";				break;
	case CONTACTS_PERSON_PROPERTY_IMAGE:			szErrorVal = "CONTACTS_PERSON_PROPERTY_IMAGE";				break;
	default:										szErrorVal = "Unknown Property";							break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceGetEnumForUsageType
* @description	 	Maps enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* ContactsServiceGetEnumForUsageType(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CONTACTS_PERSON_PROPERTY_NAME_CONTACT:		szErrorVal = "CONTACTS_PERSON_PROPERTY_NAME_CONTACT";		break;
	case CONTACTS_PERSON_PROPERTY_NUMBER:			szErrorVal = "CONTACTS_PERSON_PROPERTY_NUMBER";				break;
	case CONTACTS_PERSON_PROPERTY_EMAIL:			szErrorVal = "CONTACTS_PERSON_PROPERTY_EMAIL";				break;
	case CONTACTS_PERSON_PROPERTY_IMAGE:			szErrorVal = "CONTACTS_PERSON_PROPERTY_IMAGE";				break;
	default:										szErrorVal = "Unknown Property";							break;
	}

	return szErrorVal;
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
	if(!g_bIsContactFeatureSupported)
	{
		if(nRet != TIZEN_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] contacts_connect API call did not return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			g_bContactFeatureMismatch = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_connect API call correctly return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			g_bContactFeatureMismatch = false;
		}
		return false;
	}

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
* @function 		ContactsServiceCreateAndInsertGroupRecord
* @description	 	Create a group record and insert in DB
* @parameter		NA
* @return 			true if group successfully added, else false
*/
bool ContactsServiceCreateAndInsertGroupRecord()
{
	int nRet = contacts_record_create(_contacts_group._uri, &g_hGroupRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_set_str(g_hGroupRecord, _contacts_group.name, "Group1");
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_set_str", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_db_insert_record(g_hGroupRecord, &g_nGroupId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record", ContactsServiceGetError(nRet));
		return false;
	}

	return true;
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
	contacts_record_h hTempRecord = NULL;
	contacts_record_h hPersonRecord = NULL;

	/*------------------------------ _contacts_number ------------------------------*/
	nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord_number);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE,"contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_create(_contacts_number._uri, &hNumberRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_set_str(hNumberRecord, _contacts_number.number, pszNumber);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_set_str", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_add_child_record(hMainRecord_number, _contacts_contact.number, hNumberRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_add_child_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet =contacts_db_insert_record(hMainRecord_number, nContactId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 1\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_destroy(hMainRecord_number, true);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return false;
	}
	hMainRecord_number = NULL;
	hNumberRecord = NULL;

	/*------------------------------ _contacts_name ------------------------------*/
	nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord_name);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_set_str(hNameRecord, _contacts_name.first, pszName);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_set_str", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_add_child_record(hMainRecord_name, _contacts_contact.name, hNameRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_add_child_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_db_insert_record(hMainRecord_name, nRecordId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 2\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_insert_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_destroy(hMainRecord_name, false);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return false;
	}
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
	nRet = contacts_db_get_record(_contacts_contact._uri, *nRecordId, &hTempRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 1\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_get_int(hTempRecord, _contacts_contact.person_id, nPersonId);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_get_int", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_destroy(hTempRecord, false);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return false;
	}
	hMainRecord_name = NULL;

	nRet = contacts_db_get_record(_contacts_person._uri, *nPersonId, &hPersonRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 2\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_set_bool(hPersonRecord, _contacts_person.is_favorite, true);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_set_bool", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_db_update_record(hPersonRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_update_record", ContactsServiceGetError(nRet));
		return false;
	}
	nRet = contacts_record_destroy(hPersonRecord, false);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_destroy", ContactsServiceGetError(nRet));
		return false;
	}
	hPersonRecord = NULL;

	nRet = contacts_db_get_record(_contacts_contact._uri, *nRecordId, hRecord);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, inside 3\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record");
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_db_get_record", ContactsServiceGetError(nRet));
		return false;
	}
	return true;
}

/**
* @function 		ContactsServiceCreateAndInsertRecordSdn
* @description	 	Create a record and insert in DB
* @parameter		NA
* @return 			true if contact successfully added, else false
*/
bool ContactsServiceCreateAndInsertRecordSdn(contacts_record_h *hProfileRecord)
{
	int nRet = 0;

	/*------------------------------ _contacts_sdn ------------------------------*/
	nRet = contacts_record_create(_contacts_sdn._uri, hProfileRecord);

	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = %s\\n", __LINE__, API_NAMESPACE, "contacts_record_create", ContactsServiceGetError(nRet));
		return false;
	}

	if ( !hProfileRecord )
	{
		FPRINTF("[Line : %d][%s] %s failed, hProfileRecord is NULL.\\n", __LINE__, API_NAMESPACE, "contacts_record_create");
		return false;
	}

	return true;
}

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/**
* @function 		CreateVcard
* @description	 	Creates vcard
* @parameter		NA
* @return 			bool
*/
bool CreateVcard(void)
{
	//create vcard from contacts
	char *pszVcardStream = NULL;
	int nRet = contacts_vcard_make_from_contact(g_hRecordFirst,&pszVcardStream);
	if ( nRet != CONTACTS_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] contacts_vcard_make_from_contact failed , error returned = %s\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
		return false;
	}
	size_t nBytes = strlen(pszVcardStream);

	// write stream buffer to file
	FILE* pFptr = fopen(VCFPATH,"w+");
	if ( !pFptr )
	{
		FPRINTF("[Line : %d][%s] CreateVcard failed , Unable to open Vcard stream file",__LINE__, API_NAMESPACE);
		return false;
	}

	fwrite(pszVcardStream, SIZE, nBytes, pFptr);
	fclose(pFptr);
	return true;
}
/** @} */
