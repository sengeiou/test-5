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
#include "assert.h"
#include <nfc.h>
#include <glib.h>
#include <system_info.h>

//& set: HCE
static bool hce_supported=false;

/**
 * @function		utc_nfc_se_hce_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_se_hce_startup(void)
{
	nfc_manager_initialize();
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation.hce",&hce_supported);
}

/**
 * @function		utc_nfc_se_hce_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_se_hce_cleanup(void)
{
    nfc_manager_deinitialize();
}

void _nfc_hce_event_cb(nfc_se_h handle, nfc_hce_event_type_e event,
	unsigned char *apdu, unsigned int apdu_len, void *user_data)
{

}

void _nfc_se_registered_aid_cb(nfc_se_type_e se_type,	const char *aid, bool read_only, void *user_data)
{

}

/**
 * @testcase		utc_nfc_manager_set_hce_event_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_hce_event_cb_p(void)
{
	int ret;

	ret = nfc_manager_set_hce_event_cb(_nfc_hce_event_cb, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
   }
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_hce_event_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_hce_event_cb_n(void)
{
	int ret;

	ret = nfc_manager_set_hce_event_cb(NULL, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
   }
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_hce_event_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_hce_event_cb_p(void)
{
	int ret;

	nfc_manager_unset_hce_event_cb();

	ret = get_last_result();

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
   }
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_hce_event_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_hce_event_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	nfc_manager_unset_hce_event_cb();

	ret = get_last_result();

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
   }
	else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}
/**
 * @testcase		utc_nfc_se_set_default_route_p
 * @since_tizen		2.3
 * @remarks		This API can return a security error depending on the security level of the manufacturer.
 * 			If you want to know about security level in detail, See the GSMA specification.\n
 * 			(http://www.gsma.com/digitalcommerce/wp-content/uploads/2013/12/GSMA-NFC05-NFC-Handset-APIs-Requirement-Specification-version-4-1.pdf)
 * @description		
 */
int utc_nfc_se_set_default_route_p(void)
{
	int ret;
	ret = nfc_se_set_default_route(NFC_SE_TYPE_HCE, NFC_SE_TYPE_DISABLE, NFC_SE_TYPE_DISABLE);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert(ret == NFC_ERROR_NONE
			|| ret == NFC_ERROR_SECURITY_RESTRICTED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_set_default_route_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_set_default_route_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	ret = nfc_se_set_default_route(NFC_SE_TYPE_HCE, NFC_SE_TYPE_DISABLE, NFC_SE_TYPE_DISABLE);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_is_activated_handler_for_aid_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_is_activated_handler_for_aid_p(void)
{
	int ret;
	const char aid[] = "11121314";
	bool activated_handler;

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);

	ret = nfc_se_is_activated_handler_for_aid(NFC_SE_TYPE_HCE, aid, &activated_handler);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_is_activated_handler_for_aid_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_is_activated_handler_for_aid_n(void)
{
	int ret;

	ret = nfc_se_is_activated_handler_for_aid(NFC_SE_TYPE_HCE, NULL, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_is_activated_handler_for_category_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_is_activated_handler_for_category_p(void)
{
	int ret;
	const char aid[] = "11121314";
	bool activated_handler;

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);

	ret = nfc_se_is_activated_handler_for_category(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, &activated_handler);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_is_activated_handler_for_category_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_is_activated_handler_for_category_n(void)
{
	int ret;

	ret = nfc_se_is_activated_handler_for_category(NFC_SE_TYPE_HCE, 0, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_register_aid_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_register_aid_p(void)
{
	int ret;
	const char aid[] = "11121314";

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_register_aid_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_register_aid_n(void)
{
	int ret;

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_unregister_aid_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_unregister_aid_p(void)
{
	int ret;
	const char aid[] = "11121314";

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);
	ret = nfc_se_unregister_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_unregister_aid_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_unregister_aid_n(void)
{
	int ret;

	ret = nfc_se_unregister_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_foreach_registered_aids_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_foreach_registered_aids_p(void)
{
	int ret;
	const char aid[] = "11121314";

	ret = nfc_se_register_aid(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, aid);

	ret = nfc_se_foreach_registered_aids(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, _nfc_se_registered_aid_cb, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_foreach_registered_aids_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_foreach_registered_aids_n(void)
{
	int ret;

	ret = nfc_se_foreach_registered_aids(NFC_SE_TYPE_HCE, NFC_CARD_EMULATION_CATEGORY_PAYMENT, NULL, NULL);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_hce_send_apdu_response_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_hce_send_apdu_response_n(void)
{
	int ret;

	ret = nfc_hce_send_apdu_response(NULL, NULL, 0);

	if(!hce_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}
	else{
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}
