#include "utc-dali-property-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Property_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Property_startup(void)
{
  test_return_value=0;
  gRenderCountProperty=TC_PASS;
}

/**
 * @function            utc_Dali_Property_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Property_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_PROPERTY
  {
    PROPERTY_WITH_PROPERTY_NAME,
    PROPERTY_WITH_PROPERTY_INDEX,
    PROPERTY_WITH_NAME_COMPONENT_INDEX,
    PROPERTY_WITH_PROPERTY_AND_COMPONENT_INDEX
  };

  struct Property_TestApp : public ConnectionTracker
  {
    Property_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
      }
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case PROPERTY_WITH_PROPERTY_NAME:
          PropertyWithPropertyName();
          break;

        case PROPERTY_WITH_PROPERTY_INDEX:
          PropertyWithPropertyIndex();
          break;

        case PROPERTY_WITH_NAME_COMPONENT_INDEX:
          PropertyWithNameComponentIndex();
          break;
        case PROPERTY_WITH_PROPERTY_AND_COMPONENT_INDEX:
          PropertyWithPropertyIndexComponentIndex();
          break;

      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case PROPERTY_WITH_PROPERTY_NAME:
          switch (gRenderCountProperty)
          {
            case 0:
              VTPropertyWithPropertyName001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_WITH_PROPERTY_INDEX:
          switch (gRenderCountProperty)
          {
            case 0:
              VTPropertyWithComponentIndex001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case PROPERTY_WITH_NAME_COMPONENT_INDEX:
          switch (gRenderCountProperty)
          {
            case 0:
              VTPropertyWithNameComponentIndex001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;
        default:
          mTimer.Stop();
          mApplication.Quit();
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace



/**
 * @testcase                 UtcDaliPropertyWithPropertyIndexP
 * @since_tizen              2.4
 * @description              Create Property instance using property index, and check whether a property is animated with it
 */
int UtcDaliPropertyWithPropertyIndexP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_TestApp testApp( application, PROPERTY_WITH_PROPERTY_INDEX);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                 UtcDaliPropertyWithNameComponentIndexP
 * @since_tizen              2.4
 * @description              Create Property instance using property and component index and check whether a property is animated with it
 */
int UtcDaliPropertyWithPropertyAndComponentIndexP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_TestApp testApp( application, PROPERTY_WITH_PROPERTY_AND_COMPONENT_INDEX);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliPropertyWithPropertyNameP
 * @since_tizen              2.4
 * @description              Create Property instance using property name and check whether a property is animated with it
 */
int UtcDaliPropertyWithPropertyNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_TestApp testApp( application, PROPERTY_WITH_PROPERTY_NAME);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                 UtcDaliPropertyWithNameAndComponentIndexP
 * @since_tizen              2.4
 * @description              Create Property instance using property name and component and check whether a property is animated with it
 */
int UtcDaliPropertyWithNameAndComponentIndexP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_TestApp testApp( application, PROPERTY_WITH_NAME_COMPONENT_INDEX);
  application.MainLoop();
  return test_return_value;
}

