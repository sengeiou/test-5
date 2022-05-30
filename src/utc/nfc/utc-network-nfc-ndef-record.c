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
static bool nfc_supported;

/**
 * @function		utc_nfc_ndef_record_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_ndef_record_startup(void)
{
	nfc_manager_initialize();
	system_info_get_platform_bool("http://tizen.org/feature/network.nfc",&nfc_supported);
}

/**
 * @function		utc_nfc_ndef_record_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void utc_nfc_ndef_record_cleanup(void)
{
	nfc_manager_deinitialize();
}

/**
 * @testcase		utc_nfc_ndef_record_create_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_p(void)
{
    int ret;
    nfc_ndef_record_h record;
    unsigned char testbuffer[] = "TEST";

    ret = nfc_ndef_record_create(&record, NFC_RECORD_TNF_WELL_KNOWN, testbuffer, 1, testbuffer, 4, testbuffer, 4);
    if(!nfc_supported){
	 assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
    }
    else{

	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_n(void)
{
    int ret;
    unsigned char testbuffer[] = "TEST";

    ret = nfc_ndef_record_create(NULL, NFC_RECORD_TNF_WELL_KNOWN, testbuffer, 1, testbuffer, 4, testbuffer, 4);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_text_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_text_p(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
	ret= nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_text_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_text_n(void)
{
    int ret;

    ret = nfc_ndef_record_create_text(NULL, "test", "en-US", NFC_ENCODE_UTF_8);
	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_uri_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_uri_p(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_uri(&record, "http://test.com");
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

	assert_eq(ret,NFC_ERROR_NONE);
	ret= nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_uri_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_uri_n(void)
{
    int ret;

    ret = nfc_ndef_record_create_uri(NULL, "http://test.com");

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_mime_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_mime_p(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_mime(&record, "text/plain", (unsigned char *)"the text record", sizeof("the text record"));
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret, NFC_ERROR_NONE);
	ret= nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_mime_n_1
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_mime_n_1(void)
{
    int ret = NFC_ERROR_NONE;

    ret = nfc_ndef_record_create_mime(NULL, "text/plain", (unsigned char *)"the text record", sizeof("the text record"));

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_mime_n_2
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_mime_n_2(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_mime(&record, NULL, (unsigned char *)"the text record", sizeof("the text record"));

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_create_mime_n_3
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_create_mime_n_3(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_mime(&record, "text/plain", NULL, sizeof("the text record"));

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_destroy_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_destroy_p(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_destroy_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_destroy_n(void)
{
    int ret;

    ret = nfc_ndef_record_destroy(NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_set_id_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_set_id_p(void)
{
    int ret;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_set_id(record, (unsigned char *)"test", 4);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_set_id_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_set_id_n(void)
{
    int ret;

    ret = nfc_ndef_record_set_id(NULL, (unsigned char *)"test", 4);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_id_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_id_p(void)
{
    int ret;
    int size;
    nfc_ndef_record_h record;
    unsigned char *id;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_set_id(record, (unsigned char *)"test", 4);
        assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_id(record, &id, &size);
        nfc_ndef_record_destroy(record);
	assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_id_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_id_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_id(NULL, NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_payload_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_payload_p(void)
{
    int ret;
    unsigned int size;
    nfc_ndef_record_h record;
    unsigned char *payload;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);

        ret = nfc_ndef_record_get_payload(record, &payload, &size);

        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_payload_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_payload_n(void)
{
    int ret;

    ret = nfc_ndef_record_set_id(NULL, (unsigned char *)"test", 4);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_type_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_type_p(void)
{
    int ret;
    int size;
    nfc_ndef_record_h record;
    unsigned char *data;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_type(record, &data, &size);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_type_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_type(NULL, NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_tnf_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_tnf_p(void)
{
    int ret;
    nfc_ndef_record_h record;
    nfc_record_tnf_e tnf;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_tnf(record, &tnf);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_tnf_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_tnf_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_tnf(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_text_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_text_p(void)
{
    int ret;
    char *text;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_text(record, &text);
	assert_eq(ret,NFC_ERROR_NONE);
        free(text);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_text_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_text_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_text(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_langcode_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_langcode_p(void)
{
    int ret;
    char *text;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_langcode(record, &text);
        assert_eq(ret,NFC_ERROR_NONE);
        free(text);
        nfc_ndef_record_destroy(record);
    	assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;

}
/**
 * @testcase		utc_nfc_ndef_record_get_langcode_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_langcode_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_langcode(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_encode_type_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_encode_type_p(void)
{
    int ret;
    nfc_encode_type_e type;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_text(&record, "test", "en-US", NFC_ENCODE_UTF_8);
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{
	assert_eq(ret,NFC_ERROR_NONE);

        ret = nfc_ndef_record_get_encode_type(record, &type);

        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_encode_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_encode_type_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_encode_type(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_uri_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_uri_p(void)
{
    int ret;
    char *uri;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_uri(&record, "http://test.com");

    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_uri(record, &uri);
       	assert_eq(ret,NFC_ERROR_NONE);
        free(uri);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_uri_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_uri_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_uri(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }

    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_mime_type_p
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_mime_type_p(void)
{
    int ret;
    char *mime_type;
    nfc_ndef_record_h record;

    ret = nfc_ndef_record_create_mime(&record, "text/plain", (unsigned char *)"the text record", sizeof("the text record"));
    if(!nfc_supported){ assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);}
    else{

	assert_eq(ret,NFC_ERROR_NONE);
        ret = nfc_ndef_record_get_mime_type(record, &mime_type);
        assert_eq(ret,NFC_ERROR_NONE);
        free(mime_type);
        nfc_ndef_record_destroy(record);
        assert_eq(ret, NFC_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_nfc_ndef_record_get_mime_type_n
 * @since_tizen		2.3
 * @description		
 */
int utc_nfc_ndef_record_get_mime_type_n(void)
{
    int ret;

    ret = nfc_ndef_record_get_mime_type(NULL, NULL);

	if(!nfc_supported){

            assert_eq(ret,NFC_ERROR_NOT_SUPPORTED);
        }
        else{
            assert_eq(ret, NFC_ERROR_INVALID_PARAMETER);
        }
    return 0;
}
