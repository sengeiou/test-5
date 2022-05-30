//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-cion-common.h"

//& set: Cion

/** @addtogroup itc-cion
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_cion_group_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_group_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	return;
}


/**
 * @function 		ITs_cion_group_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_cion_group_cleanup(void)
{
	return;
}

/** @addtogroup itc-cion-testcases
*  @brief 		Integration testcases for module cion
*  @ingroup 	itc-cion
*  @{
*/

//& purpose: Creates and destroy a Cion group handle
//& type: auto
/**
* @testcase 			ITc_cion_group_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroy a Cion group handle
* @scenario				Creates and destroy a Cion group handle
* @apicovered			cion_group_create,cion_group_destroy
* @passcase				If cion_group_create,cion_group_destroy is successfull
* @failcase 			If cion_group_create,cion_group_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_group_create_destroy_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_group_h hGroup = NULL;

	nRetVal = cion_group_create(&hGroup, "ITc_cion_group_create_destroy_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_group_create", CionGetError(nRetVal));
	CHECK_HANDLE(hGroup,"cion_group_create");

	nRetVal = cion_group_destroy(hGroup);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_group_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Subscribes and Unsubscribes to a topic that the group handle has.
//& type: auto
/**
* @testcase 			ITc_cion_group_subscribe_unsubscribe_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Subscribes and Unsubscribes to a topic that the group handle has.
* @scenario				Subscribes and Unsubscribes to a topic that the group handle has.
* @apicovered			cion_group_subscribe,cion_group_unsubscribe
* @passcase				If cion_group_subscribe,cion_group_unsubscribe is successfull
* @failcase 			If cion_group_subscribe,cion_group_unsubscribe fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_group_subscribe_unsubscribe_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_group_h hGroup = NULL;

	nRetVal = cion_group_create(&hGroup, "ITc_cion_group_subscribe_unsubscribe_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_group_create", CionGetError(nRetVal));
	CHECK_HANDLE(hGroup,"cion_group_create");

	nRetVal = cion_group_subscribe(hGroup);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_group_subscribe", CionGetError(nRetVal),cion_group_destroy(hGroup));

	nRetVal = cion_group_unsubscribe(hGroup);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_group_unsubscribe", CionGetError(nRetVal),cion_group_destroy(hGroup));

	nRetVal = cion_group_destroy(hGroup);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_group_destroy", CionGetError(nRetVal));

	return 0;
}

//& purpose: Publishes data to the group.
//& type: auto
/**
* @testcase 			ITc_cion_group_publish_p
* @since_tizen 			6.5
* @author				SRID(nibha.sharma)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Publishes data to the group.
* @scenario				Publishes data to the group.
* @apicovered			cion_group_publish
* @passcase				If cion_group_publish is successfull
* @failcase 			If cion_group_publish fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_cion_group_publish_p(void)
{
	START_TEST;
	int nRetVal = -1;
	cion_group_h hGroup = NULL;
	cion_payload_h hPayload;
	unsigned char data[] = "test data";

	nRetVal = cion_group_create(&hGroup, "ITc_cion_group_publish_p", NULL);
	PRINT_RESULT(CION_ERROR_NONE, nRetVal, "cion_group_create", CionGetError(nRetVal));
	CHECK_HANDLE(hGroup,"cion_group_create");

	nRetVal = cion_group_subscribe(hGroup);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_group_subscribe", CionGetError(nRetVal),cion_group_destroy(hGroup));

	nRetVal = cion_payload_create(&hPayload, CION_PAYLOAD_TYPE_DATA);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_create", CionGetError(nRetVal),cion_group_unsubscribe(hGroup);cion_group_destroy(hGroup));
	CHECK_HANDLE(hPayload,"cion_payload_create");

	nRetVal = cion_payload_set_data(hPayload, data, sizeof(data));
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_payload_set_data", CionGetError(nRetVal),cion_group_unsubscribe(hGroup);cion_group_destroy(hGroup));

	nRetVal = cion_group_publish(hGroup, hPayload);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_group_publish", CionGetError(nRetVal),cion_group_unsubscribe(hGroup);cion_group_destroy(hGroup));

	nRetVal = cion_group_unsubscribe(hGroup);
	PRINT_RESULT_CLEANUP(CION_ERROR_NONE, nRetVal, "cion_group_unsubscribe", CionGetError(nRetVal),cion_group_destroy(hGroup));

	nRetVal = cion_group_destroy(hGroup);
	PRINT_RESULT_NORETURN(CION_ERROR_NONE, nRetVal, "cion_group_destroy", CionGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */