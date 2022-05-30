#include "utc_webkit2_ewk.h"
#include "assert.h"

static Eina_Bool isLoadSucceed = EINA_TRUE;
static Eina_Bool isSucceed = EINA_FALSE;

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

static void mainloopQuit(void* data)
{
    utc_webkit2_main_loop_quit();
}

/**
 * @function       utc_webkit2_ewk_autofill_profile_data_get_func_startup
 * @description    Called before each test
 * @parameter      NA
 * @return         NA
 */
void utc_webkit2_ewk_view_javascript_message_handler_add_startup(void)
{
    utc_webkit2_ewk_test_init();
    evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
    evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function       utc_webkit2_ewk_autofill_profile_data_get_func_cleanup
 * @description    Called after each test
 * @parameter      NA
 * @return         NA
 */
void utc_webkit2_ewk_view_javascript_message_handler_add_cleanup(void)
{
    evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
    evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
    utc_webkit2_ewk_test_end();
}

/**
 * @description Callback function for received message from JavaScript.
 */
static void DidReceiveScriptMessage(Evas_Object* view,
                                    Ewk_Script_Message message) {
    const char* name = message.name;

    if (!strcmp(name,"MyJavaScriptInterface")) {
        // Do something.
        isSucceed = EINA_TRUE;
    } else
        isSucceed = EINA_FALSE;

    // Since EFL 1.20 ecore_main_loop_quit does not work on child thread.
    // So call ecore_main_loop_quit on main thread via ecore_main_loop_thread_safe_call_async.
    ecore_main_loop_thread_safe_call_async(mainloopQuit, NULL);
}

/**
 * @testcase       utc_webkit2_ewk_view_javascript_message_handler_add_p
 * @since_tizen    3.0
 * @description    To Send native information to javascript.
 * @scenario       Load test html page(ewk_view_url_set).
 *                 Execute ewk_view_add_script_message_handler.
 *                 ReLoad test html page(ewk_view_url_set - It is for transfer to V8).
 *                 Execute click event(It is for send message from javascript to native).
 */
int utc_webkit2_ewk_view_javascript_message_handler_add_p(void)
{
    // 1. Execute script that sending message from javascript to native.
    Eina_Bool result = ewk_view_javascript_message_handler_add(
        test_view.webview, DidReceiveScriptMessage, "MyJavaScriptInterface");
    assert_eq(EINA_TRUE, result);

    // 2. Open test url.
    assert_eq(EINA_TRUE, loadURL(EWK_VIEW_ADD_JS_INTERFACE_SAMPLE_HTML_FILE));
    utc_webkit2_main_loop_begin();
    assert_eq(EINA_TRUE, isLoadSucceed);

    // 3. Execute script that sending message from javascript to native.
    result = ewk_view_script_execute(test_view.webview,
        "document.getElementById('btn1').onclick();", NULL, NULL);
    assert_eq(EINA_TRUE, result);

    utc_webkit2_main_loop_begin();

    // If native function received message from javascript, it is normal operation.
    assert_eq(EINA_TRUE, isSucceed);

    return 0;
}

/**
 * @testcase       utc_webkit2_ewk_view_javascript_message_handler_add_n
 * @since_tizen    3.0
 * @description    To Send duplicated native information to javascript.
 * @scenario       Excute ewk_view_add_script_message_handler first.
 *                 Excute ewk_view_add_script_message_handler
 *                        same native information |MyJavaScriptinterface|.
 */
int utc_webkit2_ewk_view_javascript_message_handler_add_n(void)
{
  // 1. Send to wrong native information name.
  ewk_view_javascript_message_handler_add(
      test_view.webview, DidReceiveScriptMessage, "MyJavaScriptinterface");

  // 2. Send to duplicated native information too.
  // Duplicated native information occurs
  Eina_Bool result = ewk_view_javascript_message_handler_add(
      test_view.webview, DidReceiveScriptMessage, "MyJavaScriptinterface");

  assert_eq(EINA_FALSE,result);

  return 0;
}
