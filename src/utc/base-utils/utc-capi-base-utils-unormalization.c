#include "assert.h"
#include <string.h>
#include <utils_i18n.h>

#define STR_LEN 64
#define LENGTHOF(array) (int32_t)(sizeof(array)/sizeof((array)[0]))

static int ret = I18N_ERROR_NONE;

static const i18n_uchar g_const_ustr[STR_LEN] = { 0, };
static int g_str_len = -1;

//& set: capi-base-utils-unormalization

/**
 * @function        utc_capi_base_utils_unormalization_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_unormalization_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_unormalization_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_unormalization_cleanup(void)
{
}

/**
 * @testcase        utc_capi_base_utils_i18n_unormalization_normalize_p
 * @since_tizen     2.3
 * @description     Writes the normalized form of the string,
 *                  checks result and error code.
 */
int utc_capi_base_utils_i18n_unormalization_normalize_p(void)
{
    int ret = I18N_ERROR_NONE;
    char *package_name = NULL;
    char *name = "nfkc";
    i18n_unormalization_mode_e mode = I18N_UNORMALIZATION_DECOMPOSE;
    i18n_unormalizer_h normalizer2 = NULL;
    i18n_uchar dest[STR_LEN] = {0, };
    int capacity = STR_LEN;
    int len_deststr = 0;

    ret = i18n_unormalization_get_instance( package_name, name, mode, &normalizer2 );
    assert_eq( ret, I18N_ERROR_NONE );
    assert_neq( normalizer2, NULL );

    ret = i18n_unormalization_normalize( normalizer2, g_const_ustr, g_str_len, dest, capacity, &len_deststr );
    assert_eq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unormalization_normalize_n
 * @since_tizen     2.3
 * @description     Writes the normalized form of the string,
 *                  passing invalid noramlizer handle, so error is expected.
 */
int utc_capi_base_utils_i18n_unormalization_normalize_n(void)
{
    int ret = I18N_ERROR_NONE;
    i18n_uchar dest[4] = {0, };
    int capacity = 0;
    int len_deststr = 0;

    ret = i18n_unormalization_normalize( NULL, NULL, -1, dest, capacity, &len_deststr );
    assert_neq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unormalization_get_instance_p
 * @since_tizen     2.3
 * @description     Gets a normalizer handle, checks result and error code.
 */
int utc_capi_base_utils_i18n_unormalization_get_instance_p(void)
{
    int ret = I18N_ERROR_NONE;
    char *package_name = NULL;
    char *name = "nfkc";
    i18n_unormalization_mode_e mode = I18N_UNORMALIZATION_DECOMPOSE;
    i18n_unormalizer_h normalizer2 = NULL;

    ret = i18n_unormalization_get_instance( package_name, name, mode, &normalizer2 );
    assert_eq( ret, I18N_ERROR_NONE );
    assert_neq( normalizer2, NULL );
    return 0;
}

/**
 * @testcase        utc_capi_base_utils_i18n_unormalization_get_instance_n
 * @since_tizen     2.3
 * @description     Gets a normalizer handle, passing invalid name of data file,
 *                  so error is expected.
 */
int utc_capi_base_utils_i18n_unormalization_get_instance_n(void)
{
    int ret = I18N_ERROR_NONE;
    char *package_name = NULL;
    char *name = 0;
    i18n_unormalization_mode_e mode = I18N_UNORMALIZATION_DECOMPOSE;
    i18n_unormalizer_h normalizer2 = NULL;

    ret = i18n_unormalization_get_instance( package_name, name, mode, &normalizer2 );
    assert_neq( ret, I18N_ERROR_NONE );
    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfc_instance_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfc_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfc_instance_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfc_instance_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfc_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfc_instance_n(void)
{
	ret = i18n_unormalization_get_nfc_instance(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfd_instance_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfd_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfd_instance_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfd_instance_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfd_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfd_instance_n(void)
{
	ret = i18n_unormalization_get_nfd_instance(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkc_instance_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkc_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkc_instance_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkc_instance_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkc_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkc_instance_n(void)
{
	ret = i18n_unormalization_get_nfkc_instance(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkc_casefold_instance_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkc_casefold_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkc_casefold_instance_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_casefold_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkc_casefold_instance_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkc_casefold_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkc_casefold_instance_n(void)
{
	ret = i18n_unormalization_get_nfkc_casefold_instance(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkd_instance_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkd_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkd_instance_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_nfkd_instance_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_nfkd_instance and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_nfkd_instance_n(void)
{
	ret = i18n_unormalization_get_nfkd_instance(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_create_filtered_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_create_filtered and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_create_filtered_p(void)
{
	i18n_unormalizer_h nfc, normalizer2;
	ret = i18n_unormalization_get_nfc_instance(&nfc);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uset_h filter_set;
	ret = i18n_unormalization_create_filtered(nfc, &filter_set, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_create_filtered_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_create_filtered and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_create_filtered_n(void)
{
	i18n_unormalizer_h nfc, normalizer2;
	ret = i18n_unormalization_get_nfc_instance(&nfc);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uset_h filter_set;
	ret = i18n_unormalization_create_filtered(NULL, &filter_set, &normalizer2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_unormalization_create_filtered(nfc, NULL, &normalizer2);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	ret = i18n_unormalization_create_filtered(nfc, &filter_set, NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	return 0;
}
/**
 * @testcase utc_capi_base_utils_i18n_unormalization_destroy_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_destroy_p(void)
{
	i18n_unormalizer_h nfc, normalizer2;
	ret = i18n_unormalization_get_nfc_instance(&nfc);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uset_h filter_set;
	ret = i18n_unormalization_create_filtered(nfc, &filter_set, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	ret = i18n_unormalization_destroy(normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_destroy_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_destroy_n(void)
{
	ret = i18n_unormalization_destroy(NULL);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_normalize_second_and_append_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_normalize_second_and_append and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_normalize_second_and_append_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };  /* last chars are 'A' and 'cedilla' nfc */
	static const i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };	/* first char is 'ring above' nfc */
	/* nfc: C5 is 'A with ring above' */
	static const i18n_uchar expected[]={ 0x61, 0x62, 0x63, 0xC5, 0x327, 0x64, 0x65, 0x66 };
	int32_t length;

	ret = i18n_unormalization_normalize_second_and_append(normalizer2, a, -1, LENGTHOF(a), b, -1, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, LENGTHOF(expected));
	assert_eq(a[0], 0x61);
	assert_eq(a[1], 0x62);
	assert_eq(a[2], 0x63);
	assert_eq(a[3], 0xC5);
	assert_eq(a[4], 0x327);
	assert_eq(a[5], 0x64);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_normalize_second_and_append_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_normalize_second_and_append and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_normalize_second_and_append_n(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };  /* last chars are 'A' and 'cedilla' nfc */
	static const i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };	/* first char is 'ring above' nfc */
	/* nfc: C5 is 'A with ring above' */
	int32_t length;

	ret = i18n_unormalization_normalize_second_and_append(normalizer2, a, -1, 0, b, -1, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_append_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_append and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_append_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };  /* last chars are 'A' and 'cedilla' nfc */
	static const i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };	/* first char is 'ring above' nfc */
	/* nfc: C5 is 'A with ring above' */
	static const i18n_uchar expected[]={ 0x61, 0x62, 0x63, 0xC5, 0x327, 0x64, 0x65, 0x66 };
	int32_t length;

	ret = i18n_unormalization_append(normalizer2, a, -1, LENGTHOF(a), b, -1, &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, LENGTHOF(expected));
	assert_eq(a[0], 0x61);
	assert_eq(a[1], 0x62);
	assert_eq(a[2], 0x63);
	assert_eq(a[3], 0xC5);
	assert_eq(a[4], 0x327);
	assert_eq(a[5], 0x64);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_append_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_append and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_append_n(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a[20] = { 0x61, 0x62, 0x63, 0x41, 0x327, 0 };  /* last chars are 'A' and 'cedilla' nfc */
	static const i18n_uchar b[]={ 0x30A, 0x64, 0x65, 0x66, 0 };	/* first char is 'ring above' nfc */
	/* nfc: C5 is 'A with ring above' */
	static const i18n_uchar expected[]={ 0x61, 0x62, 0x63, 0xC5, 0x327, 0x64, 0x65, 0x66 };
	int32_t length;

	ret = i18n_unormalization_append(normalizer2, a, -1, 6, b, -1, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
	assert_eq(length, LENGTHOF(expected));

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_p1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_p1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0x20, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_p2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_p2(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0xe4, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 2);
	assert_eq(decomp[0], 0x61);
	assert_eq(decomp[1], 0x308);
	assert_eq(decomp[2], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_p3
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_p3(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0xac01, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 3);
	assert_eq(decomp[0], 0x1100);
	assert_eq(decomp[1], 0x1161);
	assert_eq(decomp[2], 0x11a8);
	assert_eq(decomp[3], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_n1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_n1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0xac01, NULL, 0, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_n2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_n2(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0xac01, decomp, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_decomposition_n3
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_decomposition_n3(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_instance(NULL, "nfc", I18N_UNORMALIZATION_COMPOSE_CONTIGUOUS, &normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_decomposition(normalizer2, 0xac01, NULL, 4, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0x20, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p2(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xe4, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 2);
	assert_eq(decomp[0], 0x61);
	assert_eq(decomp[1], 0x308);
	assert_eq(decomp[2], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p3
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p3(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0x1e08, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 2);
	assert_eq(decomp[0], 0xc7);
	assert_eq(decomp[1], 0x301);
	assert_eq(decomp[2], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p4
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p4(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0x212b, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 1);
	assert_eq(decomp[0], 0xc5);
	assert_eq(decomp[1], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p5
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p5(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xac00, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 2);
	assert_eq(decomp[0], 0x1100);
	assert_eq(decomp[1], 0x1161);
	assert_eq(decomp[2], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p6
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_p6(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xac01, decomp, LENGTHOF(decomp), &length);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(length, 2);
	assert_eq(decomp[0], 0xac00);
	assert_eq(decomp[1], 0x11a8);
	assert_eq(decomp[2], 0);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xac01, NULL, 0, &length);
	assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
	assert_eq(length, 2);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n2(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar decomp[32];
	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xac01, decomp, -1, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n3
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_get_raw_decomposition and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_get_raw_decomposition_n3(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfkc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t length;
	ret = i18n_unormalization_get_raw_decomposition(normalizer2, 0xac01, NULL, 4, &length);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_compose_pair_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_compose_pair and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_compose_pair_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a = 0x1100;
	i18n_uchar b = 0x1161;
	i18n_uchar composite = 0xac00;

	i18n_uchar32 result;
	ret = i18n_unormalization_compose_pair(normalizer2, a, b, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, composite);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_compose_pair_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_compose_pair and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_compose_pair_n(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_uchar a = 0x1100;
	i18n_uchar b = 0x1161;
	i18n_uchar composite = 0xac00;

	i18n_uchar32 result;
	ret = i18n_unormalization_compose_pair(NULL, a, b, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_is_normalized_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_is_normalized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_is_normalized_p(void)
{
	static const i18n_uchar src[3] = {0xAC00, 0xAC01, 0};

	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalization_is_normalized(normalizer2, src, 1, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_is_normalized_n1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_is_normalized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_is_normalized_n1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalization_is_normalized(normalizer2, NULL, 1, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_is_normalized_n2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_is_normalized and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_is_normalized_n2(void)
{
	static const i18n_uchar src[3] = {0xAC00, 0xAC01, 0};

	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfc_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalization_is_normalized(normalizer2, src, -2, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_quick_check_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_quick_check and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_quick_check_p(void)
{
	const i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A,
								0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_unormalization_check_result_e result;
	for(int count = 0; count <10; ++count) {
		ret = i18n_unormalization_quick_check(normalizer2, &(CPnfd[count]), 1, &result);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(result, I18N_UNORMALIZATION_YES);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_quick_check_n1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_quick_check and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_quick_check_n1(void)
{
	const i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A,
								0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_unormalization_check_result_e result;
	for(int count = 0; count < 10; count++) {
		ret = i18n_unormalization_quick_check(normalizer2, &(CPnfd[count]), -3, &result);
		assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_quick_check_n2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_quick_check and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_quick_check_n2(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_unormalization_check_result_e result;
	ret = i18n_unormalization_quick_check(normalizer2, NULL, 1, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_span_quick_check_yes and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_p(void)
{
	const i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A,
								0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result;
	for(int count = 0; count <10; ++count) {
		ret = i18n_unormalization_span_quick_check_yes(normalizer2, &(CPnfd[count]), 1, &result);
		assert_eq(ret, I18N_ERROR_NONE);
		assert_eq(result, 1);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_n1
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_span_quick_check_yes and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_n1(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result;
	ret = i18n_unormalization_span_quick_check_yes(normalizer2, NULL, 1, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_n2
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_span_quick_check_yes and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_span_quick_check_yes_n2(void)
{
	const i18n_uchar CPnfd[] = {0x00C6, 0x017F, 0x0F74, 0x1000, 0x1E9A,
								0x2261, 0x3075, 0x4000, 0x5000, 0xF000};
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	int32_t result;
	for(int asdf = 0; asdf <10; ++asdf) {
		ret = i18n_unormalization_span_quick_check_yes(normalizer2, &(CPnfd[asdf]), -3, &result);
		assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);
	}

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalizer_has_boundary_before_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalizer_has_boundary_before and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalizer_has_boundary_before_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalizer_has_boundary_before(normalizer2, 0xad, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalizer_has_boundary_before_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalizer_has_boundary_before and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalizer_has_boundary_before_n(void)
{
	i18n_ubool result;
	ret = i18n_unormalizer_has_boundary_before(NULL, 0xad, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalizer_has_boundary_after_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalizer_has_boundary_after and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalizer_has_boundary_after_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalizer_has_boundary_after(normalizer2, 0xad, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalizer_has_boundary_after_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalizer_has_boundary_after and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalizer_has_boundary_after_n(void)
{
	i18n_ubool result;
	ret = i18n_unormalizer_has_boundary_after(NULL, 0xad, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_is_inert_p
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_is_inert and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_is_inert_p(void)
{
	i18n_unormalizer_h normalizer2 = NULL;
	ret = i18n_unormalization_get_nfd_instance(&normalizer2);
	assert_eq(ret, I18N_ERROR_NONE);

	i18n_ubool result;
	ret = i18n_unormalization_is_inert(normalizer2, 0xad, &result);
	assert_eq(ret, I18N_ERROR_NONE);
	assert_eq(result, true);

	return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_unormalization_is_inert_n
 * @since_tizen 6.0
 * @description Calls i18n_unormalization_is_inert and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_unormalization_is_inert_n(void)
{
	i18n_ubool result;
	ret = i18n_unormalization_is_inert(NULL, 0xad, &result);
	assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

	return 0;
}
