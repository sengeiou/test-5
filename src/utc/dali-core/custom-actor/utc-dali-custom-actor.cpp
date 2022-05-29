#include "utc-dali-custom-actor-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Customactor
/**
 * @function            utc_Dali_CustomActor_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_CustomActor_startup(void)
{
  test_return_value=TC_PASS;
  masterCallStack.clear();
  gRenderCountCustomActor=TC_PASS;
}

/**
 * @function            utc_Dali_CustomActor_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_CustomActor_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_CUSTOM_ACTOR
  {
    CUSTOM_ACTOR_DOWNCAST_P,
    CUSTOM_ACTOR_DOWNCAST_N,
    CUSTOM_ACTOR_GET_IMPLEMENTATION_P,
    CUSTOM_ACTOR_CONSTRUCTOR_P,
    CUSTOM_ACTOR_CONSTRUCTOR_P2,
    CUSTOM_ACTOR_COPY_CONSTRUCTOR_P,
    CUSTOM_ACTOR_OPERATOR_ASSIGNMENT_P
  };

  struct Custom_Actor_TestApp : public ConnectionTracker
  {
    Custom_Actor_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Custom_Actor_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Custom_Actor_TestApp::Tick );
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
        case CUSTOM_ACTOR_DOWNCAST_P:
          CustomActorDownCastP();
          break;

        case CUSTOM_ACTOR_DOWNCAST_N:
          CustomActorDownCastN();
          break;

        case CUSTOM_ACTOR_GET_IMPLEMENTATION_P:
          CustomActorGetImplementationP();
          break;

        case CUSTOM_ACTOR_CONSTRUCTOR_P:
          CustomActorConstructorP();
          break;

        case CUSTOM_ACTOR_CONSTRUCTOR_P2:
          CustomActorConstructorP2();
          break;

        case CUSTOM_ACTOR_COPY_CONSTRUCTOR_P:
          CustomActorCopyConstructorP();
          break;

        case CUSTOM_ACTOR_OPERATOR_ASSIGNMENT_P:
          CustomActorOperatorAssignmentP();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case CUSTOM_ACTOR_DOWNCAST_P:
          switch (gRenderCountCustomActor)
          {
            case 0:
              VTCustomActorDownCast001();
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
 * @testcase           UtcDaliCustomActorDownCastP
 * @since_tizen        2.4
 * @description        check if Downcast api works or not.
 */

int UtcDaliCustomActorDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorDownCastN
 * @since_tizen        2.4
 * @description        check if Downcast api works or not.
 */

int UtcDaliCustomActorDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorGetImplementationP
 * @since_tizen        2.4
 * @description        check if getImplementation api works or not.
 */

int UtcDaliCustomActorGetImplementationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_GET_IMPLEMENTATION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorConstructorP2
 * @since_tizen        2.4
 * @description        check if constructor works or not.
 */

int UtcDaliCustomActorConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorConstructorP
 * @since_tizen        2.4
 * @description        check if constructor works or not.
 */

int UtcDaliCustomActorConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorCopyConstructorP
 * @since_tizen        2.4
 * @description        check if copy constructor works or not.
 */

int UtcDaliCustomActorCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase           UtcDaliCustomActorOperatorAssignmentP
 * @since_tizen        2.4
 * @description        check if operator=() works or not.
 */

int UtcDaliCustomActorOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Custom_Actor_TestApp testApp( application, CUSTOM_ACTOR_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}
