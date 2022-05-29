#include "utc-dali-style-manager-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_StyleManager_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_StyleManager_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_StyleManager_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_StyleManager_cleanup(void)
{

}

void StyleManagerConstructor();
void StyleManagerCopyConstructor();
void StyleManagerGet();
void StyleManagerApplyTheme();
void StyleManagerApplyDefaultTheme();
void StyleManagerSetStyleConstant();
void StyleManagerGetStyleConstant();
void StyleManagerApplyStyle();

namespace
{
  enum TEST_CASES_LIST_STYLE_MANAGER
  {
    STYLE_MANAGER_CONSTRUCTOR,
    STYLE_MANAGER_COPY_CONSTRUCTOR,
    STYLE_MANAGER_GET,
    STYLE_MANAGER_APPLY_THEME,
    STYLE_MANAGER_APPLY_DEFAULT_THEME,
    STYLE_MANAGER_SET_STYLE_CONSTANT,
    STYLE_MANAGER_GET_STYLE_CONSTANT,
    STYLE_MANAGER_APPLY_STYLE
  };

  struct StyleManager_TestApp : public ConnectionTracker
  {
    StyleManager_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &StyleManager_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &StyleManager_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      mTimer.Stop();
      mApplication.Quit();
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case STYLE_MANAGER_CONSTRUCTOR:
          StyleManagerConstructor();
          break;

        case STYLE_MANAGER_COPY_CONSTRUCTOR:
          StyleManagerCopyConstructor();
          break;

        case STYLE_MANAGER_GET:
          StyleManagerGet();
          break;

        case STYLE_MANAGER_APPLY_THEME:
          StyleManagerApplyTheme();
          break;

        case STYLE_MANAGER_APPLY_DEFAULT_THEME:
          StyleManagerApplyDefaultTheme();
          break;

        case STYLE_MANAGER_SET_STYLE_CONSTANT:
          StyleManagerSetStyleConstant();
          break;

        case STYLE_MANAGER_GET_STYLE_CONSTANT:
          StyleManagerGetStyleConstant();
          break;

        case STYLE_MANAGER_APPLY_STYLE:
          StyleManagerApplyStyle();
          break;
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace

/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void StyleManagerConstructor()
{
  StyleManager styleManager;
  DALI_CHECK_FAIL(styleManager, "StyleManager constructor failed");

  DaliLog::PrintPass();
}

void StyleManagerCopyConstructor()
{
  StyleManager styleManager = StyleManager::Get();
  StyleManager copyOfStyleManager( styleManager );
  DALI_CHECK_FAIL(!copyOfStyleManager, "CopyConstructor of StyleManager failed");

  DaliLog::PrintPass();
}

void StyleManagerGet()
{
  TypeInfo type;
  type = TypeRegistry::Get().GetTypeInfo( "StyleManager" );

  DALI_CHECK_FAIL(!type, "StyleManager constructor failed");

  BaseHandle handle = type.CreateInstance();
  DALI_CHECK_FAIL(!handle, "StyleManager handle failed");

  StyleManager manager;

  manager = StyleManager::Get();
  DALI_CHECK_FAIL(!manager, "StyleManager manager failed");

  StyleManager newManager = StyleManager::Get();
  DALI_CHECK_FAIL(!newManager, "StyleManager new manager failed");

  // Check that focus manager is a singleton
  DALI_CHECK_FAIL(manager != newManager, "StyleManager new manager failed");

  DaliLog::PrintPass();
}

void StyleManagerApplyTheme()
{
  const char* json1 =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,1.0,0.0,1.0],\n"
    "      \"foregroundColor\":[0.0,0.0,1.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  const char* json2 =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,0.0,0.0,1.0],\n"
    "      \"foregroundColor\":[0.0,1.0,1.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  // Add 2 buttons to test how many times the signal is sent
  PushButton testButton = PushButton::New();
  PushButton testButton2 = PushButton::New();
  Stage::GetCurrent().Add( testButton );
  Stage::GetCurrent().Add( testButton2 );
  StyleManager styleManager = StyleManager::Get();


  std::string themeFile("ThemeOne");
  StyleManager::Get().ApplyTheme(themeFile);

  DaliLog::PrintPass();
}

void StyleManagerApplyDefaultTheme()
{
  const char* defaultTheme =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,1.0,0.0,1.0],\n"
    "      \"foregroundColor\":[0.0,0.0,1.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  const char* appTheme =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,0.0,1.0,1.0],\n"
    "      \"foregroundColor\":[0.0,1.0,0.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  PushButton testButton = PushButton::New();
  Stage::GetCurrent().Add( testButton );
  StyleManager styleManager = StyleManager::Get();

  std::string themeFile("ThemeOne");
  StyleManager::Get().ApplyTheme(themeFile);

  StyleManager::Get().ApplyDefaultTheme();

  DaliLog::PrintPass();
}

void StyleManagerSetStyleConstant()
{
  StyleManager manager = StyleManager::Get();

  std::string key( "key" );
  Property::Value value( 100 );

  manager.SetStyleConstant( key, value );

  Property::Value returnedValue;
  manager.GetStyleConstant( key, returnedValue );

  DALI_CHECK_FAIL( value.Get<int>() != returnedValue.Get<int>(), "StyleManager setStyleConstant failed" );

  DaliLog::PrintPass();
}

void StyleManagerGetStyleConstant()
{
  StyleManager manager = StyleManager::Get();

  std::string key( "key" );
  Property::Value value( 100 );

  manager.SetStyleConstant( key, value );

  Property::Value returnedValue;
  manager.GetStyleConstant( key, returnedValue );

  DALI_CHECK_FAIL( value.Get<int>() != returnedValue.Get<int>(), "StyleManager getStyleConstant failed" );

  DaliLog::PrintPass();
}

void StyleManagerApplyStyle()
{
  const char* json1 =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,1.0,0.0,1.0],\n"
    "      \"foregroundColor\":[0.0,0.0,1.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  const char* json2 =
    "{\n"
    "  \"styles\":\n"
    "  {\n"
    "    \"testbutton\":\n"
    "    {\n"
    "      \"backgroundColor\":[1.0,0.0,0.0,1.0],\n"
    "      \"foregroundColor\":[0.0,1.0,1.0,1.0]\n"
    "    }\n"
    "  }\n"
    "}\n";

  Stage stage = Stage::GetCurrent();
  PushButton testButton =  PushButton::New();
  PushButton testButton2 = PushButton::New();
  stage.Add( testButton );
  stage.Add( testButton2 );

  StyleManager styleManager = StyleManager::Get();


  std::string themeFile("ThemeOne");
  styleManager.ApplyTheme(themeFile);
  styleManager.ApplyStyle( testButton, themeFile, "testbutton" );

  // Apply the style to the test button:
  std::string themeFile2("ThemeTwo");
  styleManager.ApplyStyle( testButton2, themeFile2, "testbutton" );

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliStyleManagerConstructor
 * @since_tizen         2.4
 * @description         Constructor to StyleManager
 */
int UtcDaliStyleManagerConstructor(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_CONSTRUCTOR);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliStyleManagerCopyConstructor
 * @since_tizen         2.4
 * @description         Copy constructor to StyleManager
 */

int UtcDaliStyleManagerCopyConstructor(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_COPY_CONSTRUCTOR);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliStyleManagerGet
 * @since_tizen         2.4
 * @description         Tests Get API
 */
int UtcDaliStyleManagerGet(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_GET);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase               UtcDaliStyleManagerApplyTheme
 * @since_tizen            2.4
 * @description            Test apply theme works properly.
 */
int UtcDaliStyleManagerApplyTheme(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_APPLY_THEME);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase               UtcDaliStyleManagerApplyDefaultTheme
 * @since_tizen            2.4
 * @description            Test Apply DefaultTheme
 */
int UtcDaliStyleManagerApplyDefaultTheme(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_APPLY_DEFAULT_THEME);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase               UtcDaliStyleManagerSetStyleConstant
 * @since_tizen            2.4
 * @description            Test Set Style Constant.
 */
int UtcDaliStyleManagerSetStyleConstant(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_SET_STYLE_CONSTANT);
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase               UtcDaliStyleManagerGetStyleConstant
 * @since_tizen            2.4
 * @description            Test Get Style Constant.
 */
int UtcDaliStyleManagerGetStyleConstant(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_GET_STYLE_CONSTANT);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase               UtcDaliStyleManagerApplyStyle
 * @since_tizen            2.4
 * @description            Test ApplyStyle.
 */
int UtcDaliStyleManagerApplyStyle(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  StyleManager_TestApp testApp( application, STYLE_MANAGER_APPLY_STYLE);
  application.MainLoop();

  return test_return_value;
}
