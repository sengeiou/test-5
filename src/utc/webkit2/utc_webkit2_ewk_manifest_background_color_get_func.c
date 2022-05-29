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

/**
 * @function       utc_webkit2_ewk_manifest_background_color_get_func_startup
 * @description    Called before each test
 * @parameter      NA
 * @return         NA
 */
void utc_webkit2_ewk_manifest_background_color_get_func_startup(void)
{
  utc_webkit2_ewk_test_init();
  evas_object_smart_callback_add(test_view.webview, "load,finished", loadFinished, NULL);
  evas_object_smart_callback_add(test_view.webview, "load,error", loadError, NULL);
}

/**
 * @function       utc_webkit2_ewk_manifest_background_color_get_func_cleanup
 * @description    Called after each test
 * @parameter      NA
 * @return         NA
 */
void utc_webkit2_ewk_manifest_background_color_get_func_cleanup(void)
{
  evas_object_smart_callback_del(test_view.webview, "load,finished", loadFinished);
  evas_object_smart_callback_del(test_view.webview, "load,error", loadError);
  utc_webkit2_ewk_test_end();
}

/**
 * @description Callback function for receiving the manifest.
 */
static void DidReceiveRequestManifest(Evas_Object* view, Ewk_View_Request_Manifest* manifest, void* user_data) {
  if (manifest != NULL) {
    uint8_t r, g, b, a;
    ewk_manifest_background_color_get(manifest, &r, &g, &b, &a);
    if(r == 158 && g == 158 && b == 158 && a == 255)
      isSucceed = EINA_TRUE;
    else
      isSucceed = EINA_FALSE;
  } else
    isSucceed = EINA_FALSE;
  utc_webkit2_main_loop_quit();
}

/**
 * @testcase       utc_webkit2_ewk_manifest_background_color_get_p
 * @since_tizen    3.0
 * @description    To request manifest information to current's page.
 * @scenario       Load test html page(ewk_view_url_set).
 *                 Execute ewk_view_request_manifest.
 *                 Register callback function and wait until you receive manifest data.
 */
int utc_webkit2_ewk_manifest_background_color_get_p(void)
{
  // 1. Open page
  assert_eq(EINA_TRUE, loadURL("https://googlechrome.github.io/samples/web-application-manifest"));
  utc_webkit2_main_loop_begin();
  assert_eq(EINA_TRUE, isLoadSucceed);

  // 2. ewk_view_request_manifest call
  ewk_view_request_manifest(test_view.webview, DidReceiveRequestManifest, NULL);
  utc_webkit2_main_loop_begin();

  // If the color of background is received some value from the manifest, it is normal operation.
  assert_eq(EINA_TRUE, isSucceed);
  return 0;
}

/**
 * @testcase       utc_webkit2_ewk_manifest_background_color_get_n
 * @since_tizen    3.0
 * @description    To get background color from NULL object.
 * @scenario       Load test html page(ewk_view_url_set).
 *                 Execute ewk_view_request_manifest.
 *                 Register callback function and wait until you receive manifest data.
 *                 Get background color from NULL object
 */
int utc_webkit2_ewk_manifest_background_color_get_n(void)
{
  // 1. Open page.
  assert_eq(EINA_TRUE, loadURL("https://www.tizen.org"));
  utc_webkit2_main_loop_begin();
  assert_eq(EINA_TRUE, isLoadSucceed);

  // 2. Call ewk_view_request_manifest and register callback function.
  ewk_view_request_manifest(test_view.webview, DidReceiveRequestManifest, NULL);
  utc_webkit2_main_loop_begin();

  // If callback function received NULL, it is normal operation.
  assert_eq(EINA_FALSE, isSucceed);

  // 3. Get background color from NULL object, and if it returns EINA_FALSE it is normal operation.
  uint8_t r, g, b, a;
  if (!ewk_manifest_background_color_get(NULL, &r, &g, &b, &a))
    assert(EINA_TRUE);
  else
    assert(EINA_FALSE);

  return 0;
}
