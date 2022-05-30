#include "assert.h"
#include <utils_i18n.h>
#include <string.h>

static i18n_measure_unit_h measure_unit = NULL;
static int ret = I18N_ERROR_NONE;
static char *type = NULL;
static char *subtype = NULL;

/**
 * @function        utc_capi_base_utils_measure-unit_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_unit_startup(void)
{
}

/**
 * @function        utc_capi_base_utils_measure-unit_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_capi_base_utils_measure_unit_cleanup(void)
{
    if (measure_unit != NULL) {
        i18n_measure_unit_destroy(measure_unit);
        measure_unit = NULL;
    }

    free(type);
    type = NULL;

    free(subtype);
    subtype = NULL;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_teaspoon_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_teaspoon and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_teaspoon_p(void)
{
    ret = i18n_measure_unit_create_teaspoon(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "teaspoon";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_teaspoon_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_teaspoon passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_teaspoon_n(void)
{
    ret = i18n_measure_unit_create_teaspoon(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}
/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_tablespoon_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_tablespoon and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_tablespoon_p(void)
{
    ret = i18n_measure_unit_create_tablespoon(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "tablespoon";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_tablespoon_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_tablespoon passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_tablespoon_n(void)
{
    ret = i18n_measure_unit_create_tablespoon(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_quart_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_quart and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_quart_p(void)
{
    ret = i18n_measure_unit_create_quart(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "quart";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_quart_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_quart passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_quart_n(void)
{
    ret = i18n_measure_unit_create_quart(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pint_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pint and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pint_p(void)
{
    ret = i18n_measure_unit_create_pint(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "pint";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pint_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pint passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pint_n(void)
{
    ret = i18n_measure_unit_create_pint(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliliter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliliter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliliter_p(void)
{
    ret = i18n_measure_unit_create_milliliter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "milliliter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliliter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliliter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliliter_n(void)
{
    ret = i18n_measure_unit_create_milliliter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megaliter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megaliter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megaliter_p(void)
{
    ret = i18n_measure_unit_create_megaliter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "megaliter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megaliter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megaliter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megaliter_n(void)
{
    ret = i18n_measure_unit_create_megaliter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_liter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_liter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_liter_p(void)
{
    ret = i18n_measure_unit_create_liter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "liter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_liter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_liter passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_liter_n(void)
{
    ret = i18n_measure_unit_create_liter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectoliter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectoliter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectoliter_p(void)
{
    ret = i18n_measure_unit_create_hectoliter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "hectoliter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectoliter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectoliter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectoliter_n(void)
{
    ret = i18n_measure_unit_create_hectoliter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gallon_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gallon and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gallon_p(void)
{
    ret = i18n_measure_unit_create_gallon(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "gallon";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gallon_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gallon passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gallon_n(void)
{
    ret = i18n_measure_unit_create_gallon(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fluid_ounce_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fluid_ounce and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fluid_ounce_p(void)
{
    ret = i18n_measure_unit_create_fluid_ounce(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "fluid-ounce";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fluid_ounce_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fluid_ounce passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fluid_ounce_n(void)
{
    ret = i18n_measure_unit_create_fluid_ounce(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_deciliter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_deciliter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_deciliter_p(void)
{
    ret = i18n_measure_unit_create_deciliter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "deciliter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_deciliter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_deciliter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_deciliter_n(void)
{
    ret = i18n_measure_unit_create_deciliter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cup_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cup and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cup_p(void)
{
    ret = i18n_measure_unit_create_cup(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cup";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));
    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cup_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cup passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cup_n(void)
{
    ret = i18n_measure_unit_create_cup(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_yard_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_yard and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_yard_p(void)
{
    ret = i18n_measure_unit_create_cubic_yard(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-yard";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_yard_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_yard passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_yard_n(void)
{
    ret = i18n_measure_unit_create_cubic_yard(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_mile_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_mile and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_mile_p(void)
{
    ret = i18n_measure_unit_create_cubic_mile(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-mile";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_mile_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_mile passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_mile_n(void)
{
    ret = i18n_measure_unit_create_cubic_mile(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_meter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_meter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_meter_p(void)
{
    ret = i18n_measure_unit_create_cubic_meter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-meter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_meter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_meter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_meter_n(void)
{
    ret = i18n_measure_unit_create_cubic_meter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_kilometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_kilometer and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_kilometer_p(void)
{
    ret = i18n_measure_unit_create_cubic_kilometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-kilometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_kilometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_kilometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_kilometer_n(void)
{
    ret = i18n_measure_unit_create_cubic_kilometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_inch_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_inch and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_inch_p(void)
{
    ret = i18n_measure_unit_create_cubic_inch(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-inch";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_inch_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_inch passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_inch_n(void)
{
    ret = i18n_measure_unit_create_cubic_inch(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_foot_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_foot and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_foot_p(void)
{
    ret = i18n_measure_unit_create_cubic_foot(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-foot";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_foot_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_foot passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_foot_n(void)
{
    ret = i18n_measure_unit_create_cubic_foot(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_centimeter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_centimeter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_centimeter_p(void)
{
    ret = i18n_measure_unit_create_cubic_centimeter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "cubic-centimeter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_cubic_centimeter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_cubic_centimeter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_cubic_centimeter_n(void)
{
    ret = i18n_measure_unit_create_cubic_centimeter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_centiliter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_centiliter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_centiliter_p(void)
{
    ret = i18n_measure_unit_create_centiliter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "centiliter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_centiliter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_centiliter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_centiliter_n(void)
{
    ret = i18n_measure_unit_create_centiliter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_bushel_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_bushel and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_bushel_p(void)
{
    ret = i18n_measure_unit_create_bushel(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "bushel";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_bushel_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_bushel passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_bushel_n(void)
{
    ret = i18n_measure_unit_create_bushel(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_acre_foot_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_acre_foot and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_acre_foot_p(void)
{
    ret = i18n_measure_unit_create_acre_foot(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "volume";
    const char *ref_subtype = "acre-foot";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_acre_foot_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_acre_foot passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_acre_foot_n(void)
{
    ret = i18n_measure_unit_create_acre_foot(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kelvin_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kelvin and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kelvin_p(void)
{
    ret = i18n_measure_unit_create_kelvin(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "temperature";
    const char *ref_subtype = "kelvin";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kelvin_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kelvin passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kelvin_n(void)
{
    ret = i18n_measure_unit_create_kelvin(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fahrenheit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fahrenheit and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fahrenheit_p(void)
{
    ret = i18n_measure_unit_create_fahrenheit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "temperature";
    const char *ref_subtype = "fahrenheit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fahrenheit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fahrenheit passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fahrenheit_n(void)
{
    ret = i18n_measure_unit_create_fahrenheit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_celsius_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_celsius and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_celsius_p(void)
{
    ret = i18n_measure_unit_create_celsius(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "temperature";
    const char *ref_subtype = "celsius";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_celsius_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_celsius passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_celsius_n(void)
{
    ret = i18n_measure_unit_create_celsius(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_per_hour_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile_per_hour and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_per_hour_p(void)
{
    ret = i18n_measure_unit_create_mile_per_hour(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "speed";
    const char *ref_subtype = "mile-per-hour";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_per_hour_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile_per_hour passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_per_hour_n(void)
{
    ret = i18n_measure_unit_create_mile_per_hour(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter_per_second and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_p(void)
{
    ret = i18n_measure_unit_create_meter_per_second(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "speed";
    const char *ref_subtype = "meter-per-second";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter_per_second passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_n(void)
{
    ret = i18n_measure_unit_create_meter_per_second(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilometer_per_hour_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilometer_per_hour and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilometer_per_hour_p(void)
{
    ret = i18n_measure_unit_create_kilometer_per_hour(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "speed";
    const char *ref_subtype = "kilometer-per-hour";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilometer_per_hour_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilometer_per_hour passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilometer_per_hour_n(void)
{
    ret = i18n_measure_unit_create_kilometer_per_hour(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_karat_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_karat and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_karat_p(void)
{
    ret = i18n_measure_unit_create_karat(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "concentr";
    const char *ref_subtype = "karat";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_karat_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_karat passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_karat_n(void)
{
    ret = i18n_measure_unit_create_karat(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pound_per_square_inch_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pound_per_square_inch and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pound_per_square_inch_p(void)
{
    ret = i18n_measure_unit_create_pound_per_square_inch(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "pressure";
    const char *ref_subtype_latest = "pound-force-per-square-inch";
    const char *ref_subtype_old = "pound-per-square-inch";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype_latest) || !strcmp(subtype, ref_subtype_old));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pound_per_square_inch_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pound_per_square_inch passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pound_per_square_inch_n(void)
{
    ret = i18n_measure_unit_create_pound_per_square_inch(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millimeter_of_mercury_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millimeter_of_mercury and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millimeter_of_mercury_p(void)
{
    ret = i18n_measure_unit_create_millimeter_of_mercury(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "pressure";
    const char *ref_subtype_latest = "millimeter-ofhg";
    const char *ref_subtype_old = "millimeter-of-mercury";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype_latest) || !strcmp(subtype, ref_subtype_old));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millimeter_of_mercury_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millimeter_of_mercury passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millimeter_of_mercury_n(void)
{
    ret = i18n_measure_unit_create_millimeter_of_mercury(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millibar_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millibar and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millibar_p(void)
{
    ret = i18n_measure_unit_create_millibar(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "pressure";
    const char *ref_subtype = "millibar";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millibar_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millibar passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millibar_n(void)
{
    ret = i18n_measure_unit_create_millibar(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_inch_hg_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_inch_hg and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_inch_hg_p(void)
{
    ret = i18n_measure_unit_create_inch_hg(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "pressure";
    const char *ref_subtype_latest = "inch-ofhg";
    const char *ref_subtype_old = "inch-hg";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype_latest) || !strcmp(subtype, ref_subtype_old));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_inch_hg_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_inch_hg passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_inch_hg_n(void)
{
    ret = i18n_measure_unit_create_inch_hg(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectopascal_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectopascal and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectopascal_p(void)
{
    ret = i18n_measure_unit_create_hectopascal(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "pressure";
    const char *ref_subtype = "hectopascal";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectopascal_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectopascal passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectopascal_n(void)
{
    ret = i18n_measure_unit_create_hectopascal(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_watt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_watt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_watt_p(void)
{
    ret = i18n_measure_unit_create_watt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "watt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_watt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_watt passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_watt_n(void)
{
    ret = i18n_measure_unit_create_watt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliwatt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliwatt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliwatt_p(void)
{
    ret = i18n_measure_unit_create_milliwatt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "milliwatt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliwatt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliwatt passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliwatt_n(void)
{
    ret = i18n_measure_unit_create_milliwatt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megawatt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megawatt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megawatt_p(void)
{
    ret = i18n_measure_unit_create_megawatt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "megawatt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megawatt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megawatt passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megawatt_n(void)
{
    ret = i18n_measure_unit_create_megawatt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilowatt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilowatt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilowatt_p(void)
{
    ret = i18n_measure_unit_create_kilowatt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "kilowatt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilowatt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilowatt passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilowatt_n(void)
{
    ret = i18n_measure_unit_create_kilowatt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_horsepower_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_horsepower and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_horsepower_p(void)
{
    ret = i18n_measure_unit_create_horsepower(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "horsepower";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_horsepower_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_horsepower passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_horsepower_n(void)
{
    ret = i18n_measure_unit_create_horsepower(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigawatt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigawatt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigawatt_p(void)
{
    ret = i18n_measure_unit_create_gigawatt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "power";
    const char *ref_subtype = "gigawatt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigawatt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigawatt passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigawatt_n(void)
{
    ret = i18n_measure_unit_create_gigawatt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ton_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ton and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ton_p(void)
{
    ret = i18n_measure_unit_create_ton(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "ton";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ton_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ton passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ton_n(void)
{
    ret = i18n_measure_unit_create_ton(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_stone_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_stone and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_stone_p(void)
{
    ret = i18n_measure_unit_create_stone(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "stone";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_stone_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_stone passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_stone_n(void)
{
    ret = i18n_measure_unit_create_stone(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pound_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pound and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pound_p(void)
{
    ret = i18n_measure_unit_create_pound(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "pound";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_pound_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_pound passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_pound_n(void)
{
    ret = i18n_measure_unit_create_pound(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ounce_troy_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ounce_troy and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ounce_troy_p(void)
{
    ret = i18n_measure_unit_create_ounce_troy(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "ounce-troy";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ounce_troy_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ounce_troy passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ounce_troy_n(void)
{
    ret = i18n_measure_unit_create_ounce_troy(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ounce_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ounce and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ounce_p(void)
{
    ret = i18n_measure_unit_create_ounce(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "ounce";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ounce_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ounce passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ounce_n(void)
{
    ret = i18n_measure_unit_create_ounce(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milligram_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milligram and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milligram_p(void)
{
    ret = i18n_measure_unit_create_milligram(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "milligram";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milligram_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milligram passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milligram_n(void)
{
    ret = i18n_measure_unit_create_milligram(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_microgram_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_microgram and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_microgram_p(void)
{
    ret = i18n_measure_unit_create_microgram(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "microgram";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_microgram_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_microgram passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_microgram_n(void)
{
    ret = i18n_measure_unit_create_microgram(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_metric_ton_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_metric_ton and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_metric_ton_p(void)
{
    ret = i18n_measure_unit_create_metric_ton(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "metric-ton";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_metric_ton_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_metric_ton passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_metric_ton_n(void)
{
    ret = i18n_measure_unit_create_metric_ton(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilogram_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilogram and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilogram_p(void)
{
    ret = i18n_measure_unit_create_kilogram(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "kilogram";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilogram_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilogram passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilogram_n(void)
{
    ret = i18n_measure_unit_create_kilogram(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gram_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gram and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gram_p(void)
{
    ret = i18n_measure_unit_create_gram(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "gram";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gram_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gram passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gram_n(void)
{
    ret = i18n_measure_unit_create_gram(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_carat_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_carat and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_carat_p(void)
{
    ret = i18n_measure_unit_create_carat(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "mass";
    const char *ref_subtype = "carat";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_carat_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_carat passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_carat_n(void)
{
    ret = i18n_measure_unit_create_carat(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_lux_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_lux and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_lux_p(void)
{
    ret = i18n_measure_unit_create_lux(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "light";
    const char *ref_subtype = "lux";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_lux_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_lux passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_lux_n(void)
{
    ret = i18n_measure_unit_create_lux(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_yard_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_yard and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_yard_p(void)
{
    ret = i18n_measure_unit_create_yard(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "yard";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_yard_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_yard passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_yard_n(void)
{
    ret = i18n_measure_unit_create_yard(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_picometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_picometer and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_picometer_p(void)
{
    ret = i18n_measure_unit_create_picometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "picometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_picometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_picometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_picometer_n(void)
{
    ret = i18n_measure_unit_create_picometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_parsec_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_parsec and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_parsec_p(void)
{
    ret = i18n_measure_unit_create_parsec(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "parsec";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_parsec_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_parsec passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_parsec_n(void)
{
    ret = i18n_measure_unit_create_parsec(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nautical_mile_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nautical_mile and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nautical_mile_p(void)
{
    ret = i18n_measure_unit_create_nautical_mile(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "nautical-mile";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nautical_mile_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nautical_mile passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nautical_mile_n(void)
{
    ret = i18n_measure_unit_create_nautical_mile(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nanometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nanometer and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nanometer_p(void)
{
    ret = i18n_measure_unit_create_nanometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "nanometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nanometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nanometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nanometer_n(void)
{
    ret = i18n_measure_unit_create_nanometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millimeter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millimeter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millimeter_p(void)
{
    ret = i18n_measure_unit_create_millimeter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "millimeter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millimeter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millimeter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millimeter_n(void)
{
    ret = i18n_measure_unit_create_millimeter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_p(void)
{
    ret = i18n_measure_unit_create_mile(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "mile";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_n(void)
{
    ret = i18n_measure_unit_create_mile(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_micrometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_micrometer and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_micrometer_p(void)
{
    ret = i18n_measure_unit_create_micrometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "micrometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_micrometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_micrometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_micrometer_n(void)
{
    ret = i18n_measure_unit_create_micrometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_meter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_p(void)
{
    ret = i18n_measure_unit_create_meter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "meter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_meter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_n(void)
{
    ret = i18n_measure_unit_create_meter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_light_year_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_light_year and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_light_year_p(void)
{
    ret = i18n_measure_unit_create_light_year(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "light-year";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_light_year_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_light_year passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_light_year_n(void)
{
    ret = i18n_measure_unit_create_light_year(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilometer and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilometer_p(void)
{
    ret = i18n_measure_unit_create_kilometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "kilometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilometer_n(void)
{
    ret = i18n_measure_unit_create_kilometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_inch_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_inch and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_inch_p(void)
{
    ret = i18n_measure_unit_create_inch(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "inch";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_inch_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_inch passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_inch_n(void)
{
    ret = i18n_measure_unit_create_inch(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_furlong_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_furlong and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_furlong_p(void)
{
    ret = i18n_measure_unit_create_furlong(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "furlong";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_furlong_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_furlong passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_furlong_n(void)
{
    ret = i18n_measure_unit_create_furlong(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_foot_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_foot and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_foot_p(void)
{
    ret = i18n_measure_unit_create_foot(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "foot";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_foot_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_foot passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_foot_n(void)
{
    ret = i18n_measure_unit_create_foot(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fathom_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fathom and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fathom_p(void)
{
    ret = i18n_measure_unit_create_fathom(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "fathom";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_fathom_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_fathom passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_fathom_n(void)
{
    ret = i18n_measure_unit_create_fathom(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_decimeter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_decimeter and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_decimeter_p(void)
{
    ret = i18n_measure_unit_create_decimeter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "decimeter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_decimeter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_decimeter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_decimeter_n(void)
{
    ret = i18n_measure_unit_create_decimeter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_centimeter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_centimeter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_centimeter_p(void)
{
    ret = i18n_measure_unit_create_centimeter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "centimeter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_centimeter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_centimeter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_centimeter_n(void)
{
    ret = i18n_measure_unit_create_centimeter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_astronomical_unit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_astronomical_unit and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_astronomical_unit_p(void)
{
    ret = i18n_measure_unit_create_astronomical_unit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "length";
    const char *ref_subtype = "astronomical-unit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_astronomical_unit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_astronomical_unit passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_astronomical_unit_n(void)
{
    ret = i18n_measure_unit_create_astronomical_unit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megahertz_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megahertz and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megahertz_p(void)
{
    ret = i18n_measure_unit_create_megahertz(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "frequency";
    const char *ref_subtype = "megahertz";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megahertz_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megahertz passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megahertz_n(void)
{
    ret = i18n_measure_unit_create_megahertz(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilohertz_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilohertz and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilohertz_p(void)
{
    ret = i18n_measure_unit_create_kilohertz(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "frequency";
    const char *ref_subtype = "kilohertz";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilohertz_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilohertz passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilohertz_n(void)
{
    ret = i18n_measure_unit_create_kilohertz(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hertz_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hertz and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hertz_p(void)
{
    ret = i18n_measure_unit_create_hertz(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "frequency";
    const char *ref_subtype = "hertz";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hertz_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hertz passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hertz_n(void)
{
    ret = i18n_measure_unit_create_hertz(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigahertz_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigahertz and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigahertz_p(void)
{
    ret = i18n_measure_unit_create_gigahertz(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "frequency";
    const char *ref_subtype = "gigahertz";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigahertz_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigahertz passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigahertz_n(void)
{
    ret = i18n_measure_unit_create_gigahertz(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilowatt_hour_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilowatt_hour and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilowatt_hour_p(void)
{
    ret = i18n_measure_unit_create_kilowatt_hour(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "kilowatt-hour";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilowatt_hour_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilowatt_hour passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilowatt_hour_n(void)
{
    ret = i18n_measure_unit_create_kilowatt_hour(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilojoule_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilojoule and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilojoule_p(void)
{
    ret = i18n_measure_unit_create_kilojoule(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "kilojoule";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilojoule_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilojoule passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilojoule_n(void)
{
    ret = i18n_measure_unit_create_kilojoule(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilocalorie_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilocalorie and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilocalorie_p(void)
{
    ret = i18n_measure_unit_create_kilocalorie(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "kilocalorie";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilocalorie_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilocalorie passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilocalorie_n(void)
{
    ret = i18n_measure_unit_create_kilocalorie(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_joule_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_joule and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_joule_p(void)
{
    ret = i18n_measure_unit_create_joule(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "joule";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_joule_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_joule passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_joule_n(void)
{
    ret = i18n_measure_unit_create_joule(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_foodcalorie_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_foodcalorie and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_foodcalorie_p(void)
{
    ret = i18n_measure_unit_create_foodcalorie(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "foodcalorie";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_foodcalorie_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_foodcalorie passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_foodcalorie_n(void)
{
    ret = i18n_measure_unit_create_foodcalorie(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_calorie_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_calorie and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_calorie_p(void)
{
    ret = i18n_measure_unit_create_calorie(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "energy";
    const char *ref_subtype = "calorie";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_calorie_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_calorie passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_calorie_n(void)
{
    ret = i18n_measure_unit_create_calorie(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_volt_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_volt and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_volt_p(void)
{
    ret = i18n_measure_unit_create_volt(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "electric";
    const char *ref_subtype = "volt";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_volt_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_volt passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_volt_n(void)
{
    ret = i18n_measure_unit_create_volt(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ohm_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ohm and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ohm_p(void)
{
    ret = i18n_measure_unit_create_ohm(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "electric";
    const char *ref_subtype = "ohm";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ohm_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ohm passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ohm_n(void)
{
    ret = i18n_measure_unit_create_ohm(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliampere_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliampere and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliampere_p(void)
{
    ret = i18n_measure_unit_create_milliampere(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "electric";
    const char *ref_subtype = "milliampere";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_milliampere_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_milliampere passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_milliampere_n(void)
{
    ret = i18n_measure_unit_create_milliampere(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ampere_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ampere and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ampere_p(void)
{
    ret = i18n_measure_unit_create_ampere(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "electric";
    const char *ref_subtype = "ampere";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_ampere_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_ampere passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_ampere_n(void)
{
    ret = i18n_measure_unit_create_ampere(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_year_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_year and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_year_p(void)
{
    ret = i18n_measure_unit_create_year(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "year";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_year_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_year passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_year_n(void)
{
    ret = i18n_measure_unit_create_year(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_week_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_week and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_week_p(void)
{
    ret = i18n_measure_unit_create_week(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "week";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_week_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_week passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_week_n(void)
{
    ret = i18n_measure_unit_create_week(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_second_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_second and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_second_p(void)
{
    ret = i18n_measure_unit_create_second(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "second";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_second_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_second passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_second_n(void)
{
    ret = i18n_measure_unit_create_second(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nanosecond_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nanosecond and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nanosecond_p(void)
{
    ret = i18n_measure_unit_create_nanosecond(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "nanosecond";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_nanosecond_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_nanosecond passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_nanosecond_n(void)
{
    ret = i18n_measure_unit_create_nanosecond(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_month_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_month and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_month_p(void)
{
    ret = i18n_measure_unit_create_month(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "month";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_month_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_month passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_month_n(void)
{
    ret = i18n_measure_unit_create_month(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_minute_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_minute and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_minute_p(void)
{
    ret = i18n_measure_unit_create_minute(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "minute";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_minute_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_minute passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_minute_n(void)
{
    ret = i18n_measure_unit_create_minute(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millisecond_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millisecond and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millisecond_p(void)
{
    ret = i18n_measure_unit_create_millisecond(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "millisecond";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_millisecond_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_millisecond passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_millisecond_n(void)
{
    ret = i18n_measure_unit_create_millisecond(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_microsecond_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_microsecond and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_microsecond_p(void)
{
    ret = i18n_measure_unit_create_microsecond(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "microsecond";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_microsecond_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_microsecond passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_microsecond_n(void)
{
    ret = i18n_measure_unit_create_microsecond(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hour_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hour and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hour_p(void)
{
    ret = i18n_measure_unit_create_hour(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "hour";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hour_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hour passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hour_n(void)
{
    ret = i18n_measure_unit_create_hour(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_day_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_day and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_day_p(void)
{
    ret = i18n_measure_unit_create_day(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "duration";
    const char *ref_subtype = "day";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_day_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_day passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_day_n(void)
{
    ret = i18n_measure_unit_create_day(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_terabyte_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_terabyte and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_terabyte_p(void)
{
    ret = i18n_measure_unit_create_terabyte(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "terabyte";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_terabyte_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_terabyte passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_terabyte_n(void)
{
    ret = i18n_measure_unit_create_terabyte(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_terabit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_terabit and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_terabit_p(void)
{
    ret = i18n_measure_unit_create_terabit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "terabit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_terabit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_terabit passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_terabit_n(void)
{
    ret = i18n_measure_unit_create_terabit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megabyte_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megabyte and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megabyte_p(void)
{
    ret = i18n_measure_unit_create_megabyte(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "megabyte";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megabyte_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megabyte passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megabyte_n(void)
{
    ret = i18n_measure_unit_create_megabyte(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megabit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megabit and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megabit_p(void)
{
    ret = i18n_measure_unit_create_megabit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "megabit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_megabit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_megabit passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_megabit_n(void)
{
    ret = i18n_measure_unit_create_megabit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilobyte_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilobyte and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilobyte_p(void)
{
    ret = i18n_measure_unit_create_kilobyte(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "kilobyte";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilobyte_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilobyte passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilobyte_n(void)
{
    ret = i18n_measure_unit_create_kilobyte(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilobit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilobit and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilobit_p(void)
{
    ret = i18n_measure_unit_create_kilobit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "kilobit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_kilobit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_kilobit passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_kilobit_n(void)
{
    ret = i18n_measure_unit_create_kilobit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigabyte_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigabyte and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigabyte_p(void)
{
    ret = i18n_measure_unit_create_gigabyte(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "gigabyte";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigabyte_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigabyte passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigabyte_n(void)
{
    ret = i18n_measure_unit_create_gigabyte(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigabit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigabit and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigabit_p(void)
{
    ret = i18n_measure_unit_create_gigabit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "gigabit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_gigabit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_gigabit passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_gigabit_n(void)
{
    ret = i18n_measure_unit_create_gigabit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_byte_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_byte and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_byte_p(void)
{
    ret = i18n_measure_unit_create_byte(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "byte";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_byte_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_byte passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_byte_n(void)
{
    ret = i18n_measure_unit_create_byte(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_bit_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_bit and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_bit_p(void)
{
    ret = i18n_measure_unit_create_bit(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "digital";
    const char *ref_subtype = "bit";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_bit_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_bit passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_bit_n(void)
{
    ret = i18n_measure_unit_create_bit(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_per_gallon_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile_per_gallon and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_per_gallon_p(void)
{
    ret = i18n_measure_unit_create_mile_per_gallon(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "consumption";
    const char *ref_subtype = "mile-per-gallon";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_mile_per_gallon_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_mile_per_gallon passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_mile_per_gallon_n(void)
{
    ret = i18n_measure_unit_create_mile_per_gallon(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_liter_per_kilometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_liter_per_kilometer and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_liter_per_kilometer_p(void)
{
    ret = i18n_measure_unit_create_liter_per_kilometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "consumption";
    const char *ref_subtype = "liter-per-kilometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_liter_per_kilometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_liter_per_kilometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_liter_per_kilometer_n(void)
{
    ret = i18n_measure_unit_create_liter_per_kilometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_yard_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_yard and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_yard_p(void)
{
    ret = i18n_measure_unit_create_square_yard(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-yard";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_yard_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_yard passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_yard_n(void)
{
    ret = i18n_measure_unit_create_square_yard(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_mile_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_mile and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_mile_p(void)
{
    ret = i18n_measure_unit_create_square_mile(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-mile";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_mile_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_mile passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_mile_n(void)
{
    ret = i18n_measure_unit_create_square_mile(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_meter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_meter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_meter_p(void)
{
    ret = i18n_measure_unit_create_square_meter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-meter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_meter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_meter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_meter_n(void)
{
    ret = i18n_measure_unit_create_square_meter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_kilometer_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_kilometer and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_kilometer_p(void)
{
    ret = i18n_measure_unit_create_square_kilometer(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-kilometer";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_kilometer_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_kilometer passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_kilometer_n(void)
{
    ret = i18n_measure_unit_create_square_kilometer(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_inch_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_inch and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_inch_p(void)
{
    ret = i18n_measure_unit_create_square_inch(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-inch";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_inch_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_inch passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_inch_n(void)
{
    ret = i18n_measure_unit_create_square_inch(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_foot_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_foot and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_foot_p(void)
{
    ret = i18n_measure_unit_create_square_foot(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-foot";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_foot_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_foot passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_foot_n(void)
{
    ret = i18n_measure_unit_create_square_foot(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_centimeter_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_centimeter and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_centimeter_p(void)
{
    ret = i18n_measure_unit_create_square_centimeter(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "square-centimeter";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_square_centimeter_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_square_centimeter passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_square_centimeter_n(void)
{
    ret = i18n_measure_unit_create_square_centimeter(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectare_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectare and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectare_p(void)
{
    ret = i18n_measure_unit_create_hectare(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "hectare";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_hectare_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_hectare passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_hectare_n(void)
{
    ret = i18n_measure_unit_create_hectare(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_acre_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_acre and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_acre_p(void)
{
    ret = i18n_measure_unit_create_acre(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "area";
    const char *ref_subtype = "acre";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_acre_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_acre passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_acre_n(void)
{
    ret = i18n_measure_unit_create_acre(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_radian_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_radian and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_radian_p(void)
{
    ret = i18n_measure_unit_create_radian(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "angle";
    const char *ref_subtype = "radian";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_radian_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_radian passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_radian_n(void)
{
    ret = i18n_measure_unit_create_radian(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_degree_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_degree and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_degree_p(void)
{
    ret = i18n_measure_unit_create_degree(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "angle";
    const char *ref_subtype = "degree";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_degree_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_degree passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_degree_n(void)
{
    ret = i18n_measure_unit_create_degree(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_arc_second_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_arc_second and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_arc_second_p(void)
{
    ret = i18n_measure_unit_create_arc_second(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "angle";
    const char *ref_subtype = "arc-second";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_arc_second_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_arc_second passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_arc_second_n(void)
{
    ret = i18n_measure_unit_create_arc_second(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_arc_minute_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_arc_minute and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_arc_minute_p(void)
{
    ret = i18n_measure_unit_create_arc_minute(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "angle";
    const char *ref_subtype = "arc-minute";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_arc_minute_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_arc_minute passing invalid
 *              measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_arc_minute_n(void)
{
    ret = i18n_measure_unit_create_arc_minute(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase
 *           utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_squared_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter_per_second_squared and checks
 *              whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_squared_p(void)
{
    ret = i18n_measure_unit_create_meter_per_second_squared(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "acceleration";
    const char *ref_subtype_latest = "meter-per-square-second";
    const char *ref_subtype_old = "meter-per-second-squared";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype_latest) || !strcmp(subtype, ref_subtype_old));

    return 0;
}

/**
 * @testcase
 *           utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_squared_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_meter_per_second_squared passing
 *              invalid measure_unit and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_meter_per_second_squared_n(void)
{
    ret = i18n_measure_unit_create_meter_per_second_squared(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_g_force_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_g_force and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_g_force_p(void)
{
    ret = i18n_measure_unit_create_g_force(&measure_unit);

    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "acceleration";
    const char *ref_subtype = "g-force";

    assert(!strcmp(type, ref_type));
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_g_force_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create_g_force passing invalid measure_unit
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_g_force_n(void)
{
    ret = i18n_measure_unit_create_g_force(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

static bool measure_unit_available_types_cb(const char *type_id, void *user_data)
{
    fprintf(stderr, "type_id : %s\n", type_id);
    return false;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_foreach_available_type_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_foreach_available_type and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_foreach_available_type_p(void)
{
    ret = i18n_measure_unit_foreach_available_type(measure_unit_available_types_cb, NULL);

    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_foreach_available_type_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_foreach_available_type passing invalid cb and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_foreach_available_type_n(void)
{
    ret = i18n_measure_unit_foreach_available_type(NULL, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_with_type_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available_with_type and checks whether
 *              function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_with_type_p(void)
{
    int32_t available = -1;
    const char *type = "area";
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = 3000;

    ret = i18n_measure_unit_get_available_with_type(dest_capacity, type, &dest_array, &available);

    if (available > dest_capacity) {
        assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    } else {
        assert_eq(ret, I18N_ERROR_NONE);
    }

    assert_neq(available, -1);
    assert_neq(dest_array, NULL);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available_with_type passing invalid
 *              dest_capacity and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n(void)
{
    int32_t available = -1;
    const char *type = "Test string";
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = -1; // Invalid parameter

    ret = i18n_measure_unit_get_available_with_type(dest_capacity, type, &dest_array, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available_with_type passing invalid type
 *              and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n2(void)
{
    int32_t available = -1;
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = 3000;

    ret = i18n_measure_unit_get_available_with_type(dest_capacity, NULL, &dest_array, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n3
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available_with_type passing invalid
 *              dest_array and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n3(void)
{
    int32_t available = -1;
    const char *type = "Test string";
    int32_t dest_capacity = 3000;

    ret = i18n_measure_unit_get_available_with_type(dest_capacity, type, NULL, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n4
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available_with_type passing invalid
 *              available and checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_with_type_n4(void)
{
    const char *type = "Test string";
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = 3000;

    ret = i18n_measure_unit_get_available_with_type(dest_capacity, type, &dest_array, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_p(void)
{
    int32_t available = -1;
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = 3000;

    ret = i18n_measure_unit_get_available(dest_capacity, &dest_array, &available);

    if (available > dest_capacity) {
        assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    } else {
        assert_eq(ret, I18N_ERROR_NONE);
    }

    assert_neq(available, -1);
    assert_neq(dest_array, NULL);


    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available passing invalid dest_capacity and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_n(void)
{
    int32_t available = -1;
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = -1; // Invalid parameter

    ret = i18n_measure_unit_get_available(dest_capacity, &dest_array, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available passing invalid dest_array and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_n2(void)
{
    int32_t available = -1;
    int32_t dest_capacity = 1;

    ret = i18n_measure_unit_get_available(dest_capacity, NULL, &available);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_available_n3
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_available passing invalid available and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_available_n3(void)
{
    i18n_measure_unit_h *dest_array = NULL;
    int32_t dest_capacity = 1;

    ret = i18n_measure_unit_get_available(dest_capacity, &dest_array, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_subtype_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_subtype and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_get_subtype_p(void)
{
    ret = i18n_measure_unit_create_megahertz(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, &subtype);
    assert_neq(subtype, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_subtype = "megahertz";
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_subtype_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_subtype passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_subtype_n(void)
{
    ret = i18n_measure_unit_get_subtype(NULL, &subtype);

    assert_eq(subtype, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_subtype_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_subtype passing invalid subtype and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_subtype_n2(void)
{
    ret = i18n_measure_unit_create_megahertz(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_subtype(measure_unit, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_type_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_type and checks whether function
 *              succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_get_type_p(void)
{
    ret = i18n_measure_unit_create_megahertz(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    ret = i18n_measure_unit_get_type(measure_unit, &type);
    assert_neq(type, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_type = "frequency";
    assert(!strcmp(type, ref_type));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_type_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_type passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_type_n(void)
{
    ret = i18n_measure_unit_get_type(NULL, &type);

    assert_eq(type, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_get_type_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_get_type passing invalid type and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_get_type_n2(void)
{
    ret = i18n_measure_unit_create(&measure_unit);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_unit, NULL);

    ret = i18n_measure_unit_get_type(measure_unit, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_destroy_p(void)
{
    ret = i18n_measure_unit_create(&measure_unit);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_unit, NULL);

    ret = i18n_measure_unit_destroy(measure_unit);
    assert_eq(ret, I18N_ERROR_NONE);

    measure_unit = NULL;

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_destroy passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_destroy_n(void)
{
    ret = i18n_measure_unit_destroy(NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_array_destroy_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_array_destroy and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_array_destroy_p(void)
{
    int32_t available = -1;
    const char *type = "area";
    i18n_measure_unit_h *dest_array = NULL;
    int32_t max_count = 3000;

    ret = i18n_measure_unit_get_available_with_type(max_count, type, &dest_array, &available);

    if (available > max_count) {
        assert_eq(ret, I18N_ERROR_BUFFER_OVERFLOW);
    } else {
        assert_eq(ret, I18N_ERROR_NONE);
    }

    assert_neq(available, -1);
    assert_neq(dest_array, NULL);

    ret = i18n_measure_unit_array_destroy(dest_array, available);
    assert_eq(ret, I18N_ERROR_NONE);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_array_destroy_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_array_destroy passing invalid measure_unit array and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_array_destroy_n(void)
{
    int array_size = 1;
    ret = i18n_measure_unit_array_destroy(NULL, array_size);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_clone_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_clone and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_clone_p(void)
{
    ret = i18n_measure_unit_create_megahertz(&measure_unit);
    assert_neq(measure_unit, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    i18n_measure_unit_h clone = NULL;
    ret = i18n_measure_unit_clone(measure_unit, &clone);
    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(clone, NULL);

    ret = i18n_measure_unit_get_subtype(clone, &subtype);

    i18n_measure_unit_destroy(clone);

    assert_neq(subtype, NULL);
    assert_eq(ret, I18N_ERROR_NONE);

    const char *ref_subtype = "megahertz";
    assert(!strcmp(subtype, ref_subtype));

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_clone_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_clone passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_clone_n(void)
{
    i18n_measure_unit_h clone = NULL;

    ret = i18n_measure_unit_clone(NULL, &clone);

    assert_eq(clone, NULL);
    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_clone_n2
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_clone passing invalid clone and checks for
 *              an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_clone_n2(void)
{
    ret = i18n_measure_unit_create(&measure_unit);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_unit, NULL);

    ret = i18n_measure_unit_clone(measure_unit, NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_p
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create and checks whether function succeeded.
 */
int utc_capi_base_utils_i18n_measure_unit_create_p(void)
{
    i18n_measure_unit_h measure_unit = NULL;

    ret = i18n_measure_unit_create(&measure_unit);

    assert_eq(ret, I18N_ERROR_NONE);
    assert_neq(measure_unit, NULL);

    i18n_measure_unit_destroy(measure_unit);

    return 0;
}

/**
 * @testcase utc_capi_base_utils_i18n_measure_unit_create_n
 * @since_tizen 3.0
 * @description Calls i18n_measure_unit_create passing invalid measure_unit and
 *              checks for an invalid parameter error code.
 */
int utc_capi_base_utils_i18n_measure_unit_create_n(void)
{
    ret = i18n_measure_unit_create(NULL);

    assert_eq(ret, I18N_ERROR_INVALID_PARAMETER);

    return 0;
}

