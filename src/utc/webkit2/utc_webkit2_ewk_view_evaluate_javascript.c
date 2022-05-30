#include "utc_webkit2_ewk.h"
#include "assert.h"

const char* TEST_STRING = "test evaluate javascript";
static Eina_Bool isLoadSucceed = EINA_TRUE;

static Eina_Bool loadURL(const char* url)
{
    return ewk_view_url_set(test_view.webview, url);
}

static void loadFinished(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
}

static void loadError(void* data, Evas_Object* webview, void* event_info)
{
    utc_webkit2_main_loop_quit();
    isLoadSucceed = EINA_FALSE;
}

/**
 * @function        utc_webkit2_ewk_autofill_profile_data_get_func_startup
 * @description     Called before each test
 * @parameter       NA
 * @return          NA
 */
void utc_webkit2_ewk_view_evaluate_javascript_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function        utc_webkit2_ewk_autofill_profile_data_get_func_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_webkit2_ewk_view_evaluate_javascript_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @testcase        utc_webkit2_ewk_view_add_script_message_handler_p
 * @since_tizen    3.0
 * @description    To execute javascript with function name & parameters.
 * @scenario       Load test html page(ewk_view_url_set).
 *                 Execute ewk_view_evaluate_javascript with javascipt function name & value.
 */

int utc_webkit2_ewk_view_evaluate_javascript_p(void)
{
    // 1. open test url.
    assert_eq(EINA_TRUE, loadURL(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert_eq(EINA_TRUE, isLoadSucceed);

    // Execute some JavaScript using the result
    Eina_Bool result = ewk_view_evaluate_javascript(test_view.webview, "sendResult", TEST_STRING);
    assert_eq(EINA_TRUE, result);
    return 0;
}

/**
 * @testcase        utc_webkit2_ewk_view_add_script_message_handler_p
 * @since_tizen    3.0
 * @description    To Send NULL function or value.
 * @scenario       Load test html page(ewk_view_url_set).
 *                 Execute ewk_view_evaluate_javascript with NULL function name & value.
 */
int utc_webkit2_ewk_view_evaluate_javascript_n(void)
{
    assert_eq(EINA_TRUE, loadURL(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert_eq(EINA_TRUE, isLoadSucceed);

    Eina_Bool result = ewk_view_evaluate_javascript(test_view.webview, NULL, TEST_STRING);
    assert_eq(EINA_FALSE, result);

    result = ewk_view_evaluate_javascript(test_view.webview, "sendResult", NULL);
    assert_eq(EINA_FALSE, result);
    return 0;
}


