//
// Copyright (c) 2017 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at 
// http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "ITs-calendar-service2-common.h"

/** @addtogroup itc-calendar-service2
*  @ingroup itc
*  @{
*/

//& set: CalendarService2

/**
* @function			ITs_calendar_service2_contacts_startup
* @description		Called before each test, connects to the calendar service
* @parameter		NA
* @return			NA
*/
void ITs_calendar_service2_contacts_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		int nRet = remove(ERR_LOG);
		PRINT_RESULT_NORETURN(0, nRet, "ITs_calendar_service2_contacts_startup -remove", "Remove failed for ERR_LOG");
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_calendar_service2_contacts_startup\\n", __LINE__, API_NAMESPACE);
#endif

	g_bCalendarIssupportedFeature = TCTCheckSystemInfoFeatureSupported(CALENDAR_FEATURE, API_NAMESPACE);
	g_bCalendarConnect = false;
        int nRet = calendar_connect();
        if ( false == g_bCalendarIssupportedFeature)
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        g_bCalendarMismatch = true;
                }
                else
                {
                        g_bCalendarNotSupported = true;
                }
                return;
        }
	if ( nRet != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to connect to the calendar service, error returned = %s\\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRet));
		g_bCalendarConnect = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Connected to the calendar service successfully\\n", __LINE__, API_NAMESPACE);
		g_bCalendarConnect = true;
	}
	return;
}


/**
* @function			ITs_calendar_service2_contacts_cleanup
* @description		Called after each test, disconnects to the calendar service
* @parameter		NA
* @return			NA
*/
void ITs_calendar_service2_contacts_cleanup(void)
{
	#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_calendar_service2_contacts_cleanup\\n", __LINE__, API_NAMESPACE);
	#endif
	int nRet = calendar_disconnect();
	if ( nRet != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to disconnect to the calendar service, error returned = %s\\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRet));
	}
	return;
}

//& purpose				To test add and delete contacts birthday in calendar
//& type				Auto
/**
* @testcase				ITc_calendar_add_delete_contacts_p
* @since_tizen			4.0
* @author				SRID(sp.pradha)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			test add and delete contacts birthday in calendar
* @scenario				test add and delete contacts birthday in calendar
* @apicovered			contacts_connect(), contacts_disconnect()
* @passcase				CALENDAR_ERROR_NONE returned by ITc_calendar_add_delete_contacts_p
* @failcase				If target API fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_add_delete_contacts_p(void)
{
	START_TEST;

	int nIDAniversary = NULL;
	int nIDCustom = NULL;
	int nIDBirth = NULL;
	int nDateTime1 = 19811205, nDateTime2 = 19811104, nDateTime3 = 19811003;
	int nMonth1 = 12,  nMonth2 = 11, nMonth3 = 11;
	int nDay1 = 5, nDay2 = 4, nDay3 = 4;

	int nRet = contacts_connect();
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_connect", ContactsServiceGetError(nRet));

	nRet = ContactsServiceCreateAndInsertRecord(&nIDAniversary,nDateTime1, CONTACTS_EVENT_TYPE_ANNIVERSARY, NULL);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "ContactsServiceCreateAndInsertRecord", ContactsServiceGetError(nRet),contacts_disconnect());
	FPRINTF("[Line : %d][%s] contact_id_aniversary(%d)\\n", __LINE__, API_NAMESPACE, nIDAniversary);

	nRet = CalendarCheckContact(nIDAniversary, nMonth1, nDay1);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "CalendarCheckContact", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);contacts_disconnect());

	nRet = ContactsServiceCreateAndInsertRecord(&nIDCustom,nDateTime2, CONTACTS_EVENT_TYPE_CUSTOM, "custom");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "ContactsServiceCreateAndInsertRecord", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);contacts_disconnect());
	FPRINTF("[Line : %d][%s] nIDCustom(%d)\\n", __LINE__, API_NAMESPACE, nIDCustom);

	nRet = CalendarCheckContact(nIDCustom, nMonth2, nDay2);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "CalendarCheckContact", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);contacts_db_delete_record(_contacts_contact._uri, nIDCustom);contacts_disconnect());

	nRet = ContactsServiceCreateAndInsertRecord(&nIDBirth,nDateTime3, CONTACTS_EVENT_TYPE_BIRTH, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "ContactsServiceCreateAndInsertRecord", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);contacts_db_delete_record(_contacts_contact._uri, nIDCustom);contacts_disconnect());
	FPRINTF("[Line : %d][%s] nIDBirth(%d)\\n", __LINE__, API_NAMESPACE, nIDBirth);

	nRet = CalendarCheckContact(nIDBirth, nMonth3, nDay3);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "CalendarCheckContact", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);contacts_db_delete_record(_contacts_contact._uri, nIDCustom);contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());

	nRet = contacts_db_delete_record(_contacts_contact._uri, nIDAniversary);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "contacts_db_delete_record", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDCustom);contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());

	nRet = contacts_db_delete_record(_contacts_contact._uri, nIDCustom);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "contacts_db_delete_record", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());

	nRet = contacts_db_delete_record(_contacts_contact._uri, nIDBirth);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "contacts_db_delete_record", CalendarServiceGetError(nRet),contacts_disconnect());

	nRet = contacts_disconnect();
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_disconnect", ContactsServiceGetError(nRet));
	return 0;
} 

//& purpose				To test modified contacts birthday in calendar
//& type				Auto
/**
* @testcase				ITc_calendar_modify_contacts_p
* @since_tizen			4.0
* @author				SRID(niha.sharma)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Test modified contacts birthday in calendar
* @scenario				Test modified contacts birthday in calendar
* @apicovered			contacts_connect(), contacts_disconnect()
* @passcase				CALENDAR_ERROR_NONE returned by ITc_calendar_modify_contacts_p
* @failcase				If target API fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_modify_contacts_p(void)
{
	START_TEST;

	int nIDBirth = NULL;
	int nDateTime = 19811003, nModDateTime = 19450815;
	int nMonth = 10,  nModMonth = 8;
	int nDay = 3, nModDay = 15;

	int nRet = contacts_connect();
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_connect", ContactsServiceGetError(nRet));

	nRet = ContactsServiceCreateAndInsertRecord(&nIDBirth,nDateTime, CONTACTS_EVENT_TYPE_BIRTH, NULL);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "ContactsServiceCreateAndInsertRecord", ContactsServiceGetError(nRet),contacts_disconnect());
	FPRINTF("[Line : %d][%s] nIDBirth(%d)\\n", __LINE__, API_NAMESPACE, nIDBirth);

	nRet = CalendarCheckContact(nIDBirth, nMonth, nDay);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "CalendarCheckContact", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());

	nRet = ModifyContact(nIDBirth, nModDateTime);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "ModContact", ContactsServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());
	FPRINTF("[Line : %d][%s] nIDBirth(%d)\\n", __LINE__, API_NAMESPACE, nIDBirth);

	nRet = CalendarCheckContact(nIDBirth, nModMonth, nModDay);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "CalendarCheckContact", CalendarServiceGetError(nRet),contacts_db_delete_record(_contacts_contact._uri, nIDBirth);contacts_disconnect());

	nRet = contacts_db_delete_record(_contacts_contact._uri, nIDBirth);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_delete_record", ContactsServiceGetError(nRet),contacts_disconnect());

	nRet = contacts_disconnect();
	PRINT_RESULT_NORETURN(CONTACTS_ERROR_NONE, nRet, "contacts_disconnect", ContactsServiceGetError(nRet));

	return 0;
} 
