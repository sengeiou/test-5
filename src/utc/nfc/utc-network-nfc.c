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

//& set: Nfc
static int _startup_ret = NFC_ERROR_NONE;
static int _activation_ret = NFC_ERROR_NONE;
static bool nfc_supported=false;
static bool nfc_tag_supported=false;
static bool nfc_p2p_supported=false;
static bool nfc_ce_supported=false;
static bool nfc_ce_hce_supported=false;

/**
 * @function		utc_nfc_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_startup(void)
{
    _startup_ret = nfc_manager_initialize();

    system_info_get_platform_bool("http://tizen.org/feature/network.nfc",&nfc_supported);
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.tag",&nfc_tag_supported);
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.p2p",&nfc_p2p_supported);
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&nfc_ce_supported);
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation.hce",&nfc_ce_hce_supported);
}

/**
 * @function		utc_nfc_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_cleanup(void)
{
    nfc_manager_deinitialize();
}

static void _activation_changed_cb(bool activated, void *user_data)
{
}

static void _activation_completed_cb(int error, void *user_data)
{
	_activation_ret = error;
	g_main_loop_quit((GMainLoop *)user_data);
}

static void _utc_tag_discovered_cb(nfc_discovered_type_e type,
        nfc_tag_h tag, void *user_data)
{
}

static void _utc_ndef_discovered_cb(nfc_ndef_message_h message, void *user_data)
{
}

static void _utc_p2p_discovered_cb(nfc_discovered_type_e type,
        nfc_p2p_target_h target, void *user_data)
{
}

static void _utc_se_event_cb(nfc_se_event_e event , void *user_data)
{
}

static void _utc_se_transaction_event_cb(nfc_se_type_e se_type,
        unsigned char* aid, int aid_size , unsigned char* param,
        int param_size,  void *user_data)
{
}

/**
 * @testcase		utc_nfc_manager_is_supported_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_is_supported_p(void)
{

    int result;

    nfc_manager_is_supported();
    result = get_last_result();
    if(!nfc_supported){

        assert_eq(result,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
        assert_eq(result, NFC_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_initialize_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_initialize_p(void)
{
    int ret = NFC_ERROR_NONE;
    nfc_manager_deinitialize();
    ret = nfc_manager_initialize();
    if(!nfc_supported){

        assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_manager_deinitialize_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_deinitialize_p(void)
{
    int ret;

    ret = nfc_manager_deinitialize();
    if(!nfc_supported){

	assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
	assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_activation_changed_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_activation_changed_cb_p(void)
{
    int ret;

    ret = nfc_manager_set_activation_changed_cb(_activation_changed_cb, NULL);
    if(!nfc_supported){

	assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
	assert_eq(ret, NFC_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_activation_changed_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_activation_changed_cb_n(void)
{

    int ret;

    ret = nfc_manager_set_activation_changed_cb(NULL, NULL);
    if(!nfc_supported){

        assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
        assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_activation_changed_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_activation_changed_cb_p(void)
{
	int ret;

	nfc_manager_unset_activation_changed_cb();

	ret = get_last_result();
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_activation_changed_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_activation_changed_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();

	nfc_manager_unset_activation_changed_cb();

	ret = get_last_result();
	if(!nfc_supported){

     	   assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
	}
	else{
	    assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_tag_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_tag_discovered_cb_p(void)
{
	int ret;

	nfc_manager_unset_tag_discovered_cb();

	ret = get_last_result();

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_tag_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_tag_discovered_cb_n(void)
{
	int ret;
	nfc_manager_deinitialize();

	nfc_manager_unset_tag_discovered_cb();

	ret = get_last_result();

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_ndef_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_ndef_discovered_cb_p(void)
{
	int ret;

	nfc_manager_unset_ndef_discovered_cb();

	ret = get_last_result();
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_ndef_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_ndef_discovered_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();

	nfc_manager_unset_ndef_discovered_cb();

	ret = get_last_result();
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
        }

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_p2p_target_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_p2p_target_discovered_cb_p(void)
{
	int ret;
	nfc_manager_unset_p2p_target_discovered_cb();

	ret = get_last_result();
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_p2p_target_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_p2p_target_discovered_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();

	nfc_manager_unset_p2p_target_discovered_cb();

	ret = get_last_result();
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_is_activated_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_is_activated_p(void)
{
	int result;
	int ret;
        nfc_manager_is_activated();

	result = get_last_result();
	if(!nfc_supported){

            assert_eq(result,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(result, NFC_ERROR_NONE);
        }

        return 0;
}



/**
 * @testcase		utc_nfc_manager_set_tag_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_tag_discovered_cb_p(void)
{
	int ret;

	ret = nfc_manager_set_tag_discovered_cb(_utc_tag_discovered_cb, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_tag_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_tag_discovered_cb_n(void)
{
	int ret;
	ret = nfc_manager_set_tag_discovered_cb(NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_ndef_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_ndef_discovered_cb_p(void)
{
        int ret;

        ret = nfc_manager_set_ndef_discovered_cb(_utc_ndef_discovered_cb, NULL);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

        return 0;
}

/**
 * @testcase		utc_nfc_manager_set_ndef_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_ndef_discovered_cb_n(void)
{
        int ret;

        ret = nfc_manager_set_ndef_discovered_cb(NULL, NULL);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

        return 0;
}

/**
 * @testcase		utc_nfc_manager_set_p2p_target_discovered_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_p2p_target_discovered_cb_p(void)
{
	int ret;

	ret = nfc_manager_set_p2p_target_discovered_cb(_utc_p2p_discovered_cb, NULL);
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_p2p_target_discovered_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_p2p_target_discovered_cb_n(void)
{
	int ret;

	ret = nfc_manager_set_p2p_target_discovered_cb(NULL, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_system_handler_enable_p1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_system_handler_enable_p1(void)
{
    int ret;

    ret = nfc_manager_set_system_handler_enable(true);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_system_handler_enable_p2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_system_handler_enable_p2(void)
{
    int ret;

    ret = nfc_manager_set_system_handler_enable(false);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_system_handler_enable_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_system_handler_enable_n(void)
{
    int ret;

    nfc_manager_deinitialize();

    ret = nfc_manager_set_system_handler_enable(false);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_get_se_type_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_se_type_p(void)
{
    int ret;
    nfc_se_type_e tp;
    bool ce_supported=false;

    system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&ce_supported);
    ret = nfc_manager_get_se_type(&tp);

    if(ce_supported){

	 assert_eq(ret, NFC_ERROR_NONE);
    }
    else{

	 assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_get_se_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_se_type_n(void)
{
    int ret;
    bool ce_supported=false;

    system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&ce_supported);

    ret = nfc_manager_get_se_type(NULL);
    if(ce_supported){

	assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
    }
    else{

	 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_type_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_type_p(void)
{
    int ret;
    nfc_se_type_e tp;
    bool ce_supported=false;

    system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&ce_supported);

    if(ce_supported){
        ret = nfc_manager_get_se_type(&tp);
        if(tp == NFC_SE_TYPE_DISABLE) nfc_manager_set_se_type(NFC_SE_TYPE_ESE);
    }
    else{
	ret=nfc_manager_set_se_type(NFC_SE_TYPE_ESE);
	assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_type_n(void)
{
    int ret;
    bool ce_supported=false;

    system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&ce_supported);

    ret = nfc_manager_set_se_type(-3);
    if(ce_supported){

	 assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
    }
    else{

	 assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_get_cached_message_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_cached_message_n(void)
{
    int ret;

    ret = nfc_manager_get_cached_message(NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_get_connected_tag_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_connected_tag_n(void)
{
	int ret;

	ret = nfc_manager_get_connected_tag(NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_get_connected_target_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_connected_target_n(void)
{
	int ret;

	ret = nfc_manager_get_connected_target(NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_tag_filter_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_tag_filter_p(void)
{
	int filter;
	int ret;

	nfc_manager_set_tag_filter(NFC_TAG_FILTER_ALL_ENABLE);
	filter = nfc_manager_get_tag_filter();
	ret = get_last_result();

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(filter, NFC_TAG_FILTER_ALL_ENABLE);
	}

	nfc_manager_set_tag_filter(NFC_TAG_FILTER_ALL_DISABLE);
	filter = nfc_manager_get_tag_filter();
	ret = get_last_result();

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(filter,NFC_TAG_FILTER_ALL_DISABLE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_tag_filter_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_tag_filter_n(void)
{
	int ret;

	nfc_manager_set_tag_filter(-999);

	ret = get_last_result();
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_get_tag_filter_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_tag_filter_p(void)
{
	int filter;
	int ret;

	nfc_manager_set_tag_filter(NFC_TAG_FILTER_ISO14443A_ENABLE);
	filter = nfc_manager_get_tag_filter();
	ret = get_last_result();

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(filter, NFC_TAG_FILTER_ISO14443A_ENABLE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_get_tag_filter_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_get_tag_filter_n(void)
{
	int ret;
	int filter;

	nfc_manager_deinitialize();

	filter = nfc_manager_get_tag_filter();

	ret = get_last_result();
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_is_system_handler_enabled_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_is_system_handler_enabled_p(void)
{
    int ret;
    bool enabled;

    enabled = nfc_manager_is_system_handler_enabled();
    ret = get_last_result();

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_manager_is_system_handler_enabled_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_is_system_handler_enabled_n(void)
{
    int ret;
    bool enabled;

    nfc_manager_deinitialize();

    enabled = nfc_manager_is_system_handler_enabled();
    ret = get_last_result();

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
        }

    return 0;
}

static nfc_se_h se_handle;

//& Set: Tag

/**
 * @testcase		utc_nfc_tag_get_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_get_type_n(void)
{
	int ret;

	ret = nfc_tag_get_type(NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_is_support_ndef_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_is_support_ndef_n(void)
{
	int ret;

	ret = nfc_tag_is_support_ndef(NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_get_maximum_ndef_size_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_get_maximum_ndef_size_n(void)
{
	int ret;

	ret = nfc_tag_get_maximum_ndef_size(NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_get_ndef_size_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_get_ndef_size_n(void)
{
	int ret;

	ret = nfc_tag_get_ndef_size(NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_foreach_information_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_foreach_information_n(void)
{
	int ret;

	ret = nfc_tag_foreach_information(NULL, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_transceive_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_transceive_n(void)
{
	int ret;

	ret = nfc_tag_transceive(NULL, NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_read_ndef_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_read_ndef_n(void)
{
	int ret;

	ret = nfc_tag_read_ndef(NULL, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_write_ndef_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_write_ndef_n(void)
{
	int ret;

	ret = nfc_tag_write_ndef(NULL, NULL, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_tag_format_ndef_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_tag_format_ndef_n(void)
{
	int ret;

	ret = nfc_tag_format_ndef(NULL, NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_authenticate_with_keyA_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_authenticate_with_keyA_n(void)
{
	int ret;

	ret = nfc_mifare_authenticate_with_keyA(NULL, 0, NULL, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_authenticate_with_keyB_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_authenticate_with_keyB_n(void)
{
	int ret;

	ret = nfc_mifare_authenticate_with_keyB(NULL, 0, NULL, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_read_block_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_read_block_n(void)
{
	int ret;

	ret = nfc_mifare_read_block(NULL, 0, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_read_page_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_read_page_n(void)
{
	int ret;

	ret = nfc_mifare_read_page(NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_write_block_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_write_block_n(void)
{
	int ret;

	ret = nfc_mifare_write_block(NULL, 0, NULL, 0, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_write_page_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_write_page_n(void)
{
	int ret;

	ret = nfc_mifare_write_page(NULL, 0, NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_increment_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_increment_n(void)
{
	int ret;

	ret = nfc_mifare_increment(NULL, 0, 0, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_decrement_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_decrement_n(void)
{
	int ret;

	ret = nfc_mifare_decrement(NULL, 0, 0, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_transfer_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_transfer_n(void)
{
	int ret;

	ret = nfc_mifare_transfer(NULL, 0, NULL, NULL);

	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_mifare_restore_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_mifare_restore_n(void)
{
	int ret;

	ret = nfc_mifare_restore(NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_tag_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_p2p_set_data_received_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_p2p_set_data_received_cb_n(void)
{
	int ret;

	ret = nfc_p2p_set_data_received_cb(NULL, NULL, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_p2p_unset_data_received_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_p2p_unset_data_received_cb_n(void)
{
	int ret;

	ret = nfc_p2p_unset_data_received_cb(NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_p2p_send_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_p2p_send_n(void)
{
	int ret;

	ret = nfc_p2p_send(NULL, NULL, NULL, NULL);
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

//& set: SNEP

static void _snep_activation_completed_cb(nfc_error_e error, void *user_data)
{
	_activation_ret = error;
    g_main_loop_quit((GMainLoop *)user_data);
}

/**
 * @function		utc_nfc_snep_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_snep_startup(void)
{
    _startup_ret = nfc_manager_initialize();
    system_info_get_platform_bool("http://tizen.org/feature/network.nfc",&nfc_supported);
}

/**
 * @function		utc_nfc_snep_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_snep_cleanup(void)
{
    nfc_manager_deinitialize();
}

static const char *san = "abcd:efgh";
static int sap = 0x22;

static void _snep_event_cb(nfc_p2p_snep_h handle,
    nfc_snep_event_e event, nfc_error_e result,
    nfc_ndef_message_h msg, void *user_data)
{

}

/**
 * @testcase		utc_nfc_snep_register_server_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_register_server_p(void)
{
	int ret;

	ret = nfc_snep_register_server(san, sap, _snep_event_cb, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
		nfc_snep_unregister_server(san,sap);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_register_server_n1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_register_server_n1(void)
{
	int ret;

	ret = nfc_snep_register_server(san, 0, NULL, NULL);
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_register_server_n2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_register_server_n2(void)
{
	int ret;

	ret = nfc_snep_register_server(NULL, sap, NULL, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_unregister_server_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_unregister_server_p(void)
{
	int ret;

	ret = nfc_snep_register_server(san, sap, _snep_event_cb, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	ret = nfc_snep_unregister_server(san, sap);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_unregister_server_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_unregister_server_n(void)
{
	int ret;

	ret = nfc_snep_unregister_server(san, sap);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_OPERATION_FAILED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_send_client_request_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_send_client_request_n(void)
{
	int ret;

	ret = nfc_snep_send_client_request(NULL, 0, NULL, NULL, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_start_client_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_start_client_n(void)
{
	int ret;

	ret = nfc_snep_start_client(NULL, NULL, 0, NULL, NULL);

	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_snep_start_server_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_start_server_n(void)
{
	int ret;
	ret = nfc_snep_start_server(NULL, NULL, 0, NULL, NULL);
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}


/**
 * @testcase		utc_nfc_snep_stop_service_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_snep_stop_service_n(void)
{
	int ret;

	ret = nfc_snep_stop_service(NULL, NULL);
	if (!nfc_supported || !nfc_p2p_supported) {
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	} else {
		assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @function		utc_ce_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_ce_startup(void)
{
	_startup_ret = nfc_manager_initialize();
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc.card_emulation",&nfc_supported);
}

/**
 * @function		utc_ce_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_ce_cleanup(void)
{
    nfc_manager_deinitialize();
}

/**
 * @testcase		utc_nfc_se_enable_card_emulation_p
 * @since_tizen		2.3
 * @remarks             This API can return a security error depending on the security level of the manufacturer.
 *                      If you want to know about security level in detail, See the GSMA specification.\n
 *                      (http://www.gsma.com/digitalcommerce/wp-content/uploads/2013/12/GSMA-NFC05-NFC-Handset-APIs-Requirement-Specification-version-4-1.pdf)
 * @description		
 */
int utc_nfc_se_enable_card_emulation_p(void)
{
	int ret;

	ret = nfc_se_enable_card_emulation();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert(ret == NFC_ERROR_NONE
			|| ret == NFC_ERROR_ILLEGAL_STATE
			|| ret == NFC_ERROR_SECURITY_RESTRICTED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_enable_card_emulation_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_enable_card_emulation_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	ret = nfc_se_enable_card_emulation();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

    return 0;
}

/**
 * @testcase		utc_nfc_se_disable_card_emulation_p
 * @since_tizen		2.3
 * @remarks             This API can return a security error depending on the security level of the manufacturer.
 *                      If you want to know about security level in detail, See the GSMA specification.\n
 *                      (http://www.gsma.com/digitalcommerce/wp-content/uploads/2013/12/GSMA-NFC05-NFC-Handset-APIs-Requirement-Specification-version-4-1.pdf)
 * @description		
 */
int utc_nfc_se_disable_card_emulation_p(void)
{
	int ret;

	ret = nfc_se_disable_card_emulation();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert(ret == NFC_ERROR_NONE
			|| ret == NFC_ERROR_SECURITY_RESTRICTED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_disable_card_emulation_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_disable_card_emulation_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	ret = nfc_se_disable_card_emulation();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_get_card_emulation_mode_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_get_card_emulation_mode_p(void)
{
	int ret;
	nfc_se_card_emulation_mode_type_e emode;

	ret = nfc_se_get_card_emulation_mode(&emode);

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_se_get_card_emulation_mode_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_se_get_card_emulation_mode_n(void)
{
    int ret;

    ret = nfc_se_get_card_emulation_mode(NULL);

	 if(!nfc_supported){
		 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	 }else{
		 assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	 }

    return 0;
}

/**
 * @testcase            utc_nfc_se_set_preferred_handler_n
 * @since_tizen         3.0
 * @description
 */
int utc_nfc_se_set_preferred_handler_n(void)
{
    int ret;

    nfc_manager_deinitialize();
    ret = nfc_se_set_preferred_handler();

         if(!nfc_supported){
                 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
         }else{
                 assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
         }

    return 0;
}

/**
 * @testcase            utc_nfc_se_unset_preferred_handler_p
 * @since_tizen         3.0
 * @description
 */
int utc_nfc_se_unset_preferred_handler_p(void)
{
    int ret;

    ret = nfc_se_unset_preferred_handler();

         if(!nfc_supported){
                 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
         }else{
                 assert_eq(ret, NFC_ERROR_NONE);
         }

    return 0;
}

/**
 * @testcase            utc_nfc_se_unset_preferred_handler_n
 * @since_tizen         3.0
 * @description
 */
int utc_nfc_se_unset_preferred_handler_n(void)
{
    int ret;

    nfc_manager_deinitialize();
    ret = nfc_se_unset_preferred_handler();

         if(!nfc_supported){
                 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
         }else{
                 assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
         }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_event_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_event_cb_p(void)
{
    int ret;

    ret = nfc_manager_set_se_event_cb(_utc_se_event_cb, NULL);
	 if(!nfc_supported){
		 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	 }else{
		 assert_eq(ret, NFC_ERROR_NONE);
	 }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_event_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_event_cb_n(void)
{
    int ret;

    ret = nfc_manager_set_se_event_cb(NULL, NULL);

	 if(!nfc_supported){
		 assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	 } else{
		 assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
	 }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_se_event_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_se_event_cb_p(void)
{
	int ret;

	nfc_manager_unset_se_event_cb();
	ret = get_last_result();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NONE);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_se_event_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_se_event_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	nfc_manager_unset_se_event_cb();
	ret = get_last_result();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_transaction_event_cb_p1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_transaction_event_cb_p1(void)
{
    int ret;

    ret = nfc_manager_set_se_transaction_event_cb(NFC_SE_TYPE_ESE, _utc_se_transaction_event_cb, NULL);

    if(!nfc_supported){

        assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{
        assert_eq(ret, NFC_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_transaction_event_cb_p2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_transaction_event_cb_p2(void)
{
    int ret;

    ret = nfc_manager_set_se_transaction_event_cb(NFC_SE_TYPE_UICC, _utc_se_transaction_event_cb, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_transaction_event_cb_n1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_transaction_event_cb_n1(void)
{
    int ret;

    ret = nfc_manager_set_se_transaction_event_cb(NFC_SE_TYPE_UICC, NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }


    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_transaction_event_cb_n2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_transaction_event_cb_n2(void)
{
    int ret;

    ret = nfc_manager_set_se_transaction_event_cb(NFC_SE_TYPE_DISABLE, _utc_se_transaction_event_cb, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_set_se_transaction_event_cb_n3
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_set_se_transaction_event_cb_n3(void)
{
    int ret;

    ret = nfc_manager_set_se_transaction_event_cb(-1, _utc_se_transaction_event_cb, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_se_transaction_event_cb_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_se_transaction_event_cb_p(void)
{
	int ret;

	nfc_manager_unset_se_transaction_event_cb(NFC_SE_TYPE_ESE);

	ret = get_last_result();
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
        }

	return 0;
}

/**
 * @testcase		utc_nfc_manager_unset_se_transaction_event_cb_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_unset_se_transaction_event_cb_n(void)
{
	int ret;

	nfc_manager_deinitialize();

	nfc_manager_unset_se_transaction_event_cb(NFC_SE_TYPE_ESE);

	ret = get_last_result();
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
        }

	return 0;
}

/**
 * @testcase		utc_nfc_manager_enable_transaction_fg_dispatch_p
 * @since_tizen		2.3
 * @remarks             This API can return a security error depending on the security level of the manufacturer.
 *                      If you want to know about security level in detail, See the GSMA specification.\n
 *                      (http://www.gsma.com/digitalcommerce/wp-content/uploads/2013/12/GSMA-NFC05-NFC-Handset-APIs-Requirement-Specification-version-4-1.pdf)
 * @description		
 */
int utc_nfc_manager_enable_transaction_fg_dispatch_p(void)
{
	int ret;

	ret = nfc_manager_enable_transaction_fg_dispatch();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert(ret == NFC_ERROR_NONE
			|| ret == NFC_ERROR_ILLEGAL_STATE
			|| ret == NFC_ERROR_SECURITY_RESTRICTED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_enable_transaction_fg_dispatch_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_enable_transaction_fg_dispatch_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	ret = nfc_manager_enable_transaction_fg_dispatch();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_disable_transaction_fg_dispatch_p
 * @since_tizen		2.3
 * @remarks             This API can return a security error depending on the security level of the manufacturer.
 *                      If you want to know about security level in detail, See the GSMA specification.\n
 *                      (http://www.gsma.com/digitalcommerce/wp-content/uploads/2013/12/GSMA-NFC05-NFC-Handset-APIs-Requirement-Specification-version-4-1.pdf)
 * @description		
 */
int utc_nfc_manager_disable_transaction_fg_dispatch_p(void)
{
	int ret;

	ret = nfc_manager_disable_transaction_fg_dispatch();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
		assert(ret == NFC_ERROR_NONE
			|| ret == NFC_ERROR_SECURITY_RESTRICTED);
	}

	return 0;
}

/**
 * @testcase		utc_nfc_manager_disable_transaction_fg_dispatch_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_manager_disable_transaction_fg_dispatch_n(void)
{
	int ret;

	nfc_manager_deinitialize();
	ret = nfc_manager_disable_transaction_fg_dispatch();

	if(!nfc_supported){
		assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
	}else{
	   assert_eq(ret, NFC_ERROR_NOT_INITIALIZED);
	}

	return 0;
}
