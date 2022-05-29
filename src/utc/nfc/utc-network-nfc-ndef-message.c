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

//& set: Nfc-ndef
static bool nfc_supported=false;

/**
 * @function		utc_nfc_ndef_message_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_ndef_message_startup(void)
{
	nfc_manager_initialize();
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc",&nfc_supported);
}

/**
 * @function		utc_nfc_ndef_message_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_ndef_message_cleanup(void)
{
    nfc_manager_deinitialize();
}

/**
 * @testcase		utc_nfc_ndef_message_create_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_create_p(void)
{
    int ret;
    nfc_ndef_message_h message;

    ret = nfc_ndef_message_create(&message);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_NONE);
 	    nfc_ndef_message_destroy(message);
       }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_create_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_create_n(void)
{
    int ret;

    ret = nfc_ndef_message_create(NULL);


	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_create_from_rawdata_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_create_from_rawdata_p(void)
{
    int ret;
    unsigned char *buffer;
    unsigned int size;
    nfc_ndef_message_h message;
    nfc_ndef_message_h message2;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

        assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        nfc_ndef_message_append_record(message, record1);
        nfc_ndef_message_get_rawdata(message, &buffer, &size);
        ret = nfc_ndef_message_create_from_rawdata(&message2, buffer, size);

        nfc_ndef_message_destroy(message2);
        nfc_ndef_message_destroy(message);
        free(buffer);
        assert_eq(ret, NFC_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_create_from_rawdata_n1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_create_from_rawdata_n1(void)
{
    int ret;

    ret = nfc_ndef_message_create_from_rawdata(NULL, NULL, 0);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_create_from_rawdata_n2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_create_from_rawdata_n2(void)
{
    int ret;
    nfc_ndef_message_h message2;

    ret = nfc_ndef_message_create_from_rawdata(&message2, NULL, 0);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_destroy_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_destroy_p(void)
{
    int ret;
    nfc_ndef_message_h message;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

        assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_message_destroy(message);

        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_destroy_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_destroy_n(void)
{
    int ret;

    ret = nfc_ndef_message_destroy(NULL);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_record_count_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_record_count_p(void)
{
    int ret;
    int count;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
        assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        nfc_ndef_message_append_record(message, record1);
        ret = nfc_ndef_message_get_record_count(message, &count);
        nfc_ndef_message_destroy(message);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_record_count_n1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_record_count_n1(void)
{
    int ret;
    nfc_ndef_message_h message;

    ret = nfc_ndef_message_create(&message);
    if(nfc_supported){

        assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_message_get_record_count(message, NULL);
        assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
    }
    else{
        ret = nfc_ndef_message_get_record_count(message, NULL);
        assert_eq(ret, NFC_ERROR_NOT_SUPPORTED);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_record_count_n2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_record_count_n2(void)
{
    int ret;
    int count;

    ret = nfc_ndef_message_get_record_count(NULL, &count);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_rawdata_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_rawdata_p(void)
{
    int ret;
    unsigned char *buffer;
    unsigned int size;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        nfc_ndef_message_append_record(message, record1);
        ret = nfc_ndef_message_get_rawdata(message, &buffer, &size);
        nfc_ndef_message_destroy(message);
        free(buffer);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_rawdata_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_rawdata_n(void)
{
    int ret;

    ret = nfc_ndef_message_get_rawdata(NULL, NULL, NULL);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_append_record_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_append_record_p(void)
{
    int ret;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
        assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        ret = nfc_ndef_message_append_record(message, record1);
        nfc_ndef_message_destroy(message);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_append_record_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_append_record_n(void)
{
    int ret;

    ret = nfc_ndef_message_append_record(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_insert_record_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_insert_record_p(void)
{
    int ret;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
        assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        ret = nfc_ndef_message_insert_record(message, 0, record1);
        nfc_ndef_message_destroy(message);
        assert_eq(ret, NFC_ERROR_NONE);
    }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_insert_record_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_insert_record_n(void)
{
    int ret;

    ret = nfc_ndef_message_insert_record(NULL, 0, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_remove_record_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_remove_record_p(void)
{
    int ret;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        ret = nfc_ndef_message_insert_record(message, 0, record1);
	assert_eq(ret,NFC_ERROR_NONE);
	ret = nfc_ndef_message_remove_record(message, 0);
        nfc_ndef_message_destroy(message);
	assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_remove_record_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_remove_record_n(void)
{
    int ret;

    ret = nfc_ndef_message_remove_record(NULL, 0);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_record_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_record_p(void)
{
    int ret;
    nfc_ndef_message_h message;
    nfc_ndef_record_h record1, record2;

    ret = nfc_ndef_message_create(&message);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        nfc_ndef_record_create_text(&record1, "test", "en-US", NFC_ENCODE_UTF_8);
        ret = nfc_ndef_message_insert_record(message, 0, record1);
	assert_eq(ret,NFC_ERROR_NONE);
	ret = nfc_ndef_message_get_record(message, 0, &record2);
        nfc_ndef_message_destroy(message);
	assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_message_get_record_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_message_get_record_n(void)
{
    int ret;

    ret = nfc_ndef_message_get_record(NULL, 0, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}
