#include "utc-dali-linear-constrainer-impl.h"

//& set: LinearConstrainer

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
unsigned int gInterval = 250u;

/**
 * @function            utc_Dali_LinearConstrainer_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_LinearConstrainer_startup(void)
{
  test_return_value=TC_PASS;
  gRenderCountLinearConstrainer=TC_PASS;
}

/**
 * @function            utc_Dali_LinearConstrainer_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_LinearConstrainer_cleanup(void)
{
}


namespace
{
  enum TEST_CASES_LIST_LINEAR_CONSTRAINER
  {
    LINEAR_CONSTRAINER_NEW_P,
    LINEAR_CONSTRAINER_DOWNCAST_P,
    LINEAR_CONSTRAINER_DOWNCAST_N,
    LINEAR_CONSTRAINER_CONSTRUCTOR_P,
    LINEAR_CONSTRAINER_COPY_CONSTRUCTOR_P,
    LINEAR_CONSTRAINER_OPERTORASSIGNMENT_P,
    LINEAR_CONSTRAINER_APPLY_REMOVE_P
  };

  struct LinearConstrainer_TestApp : public ConnectionTracker
  {
    LinearConstrainer_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &LinearConstrainer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( gInterval );
      mTimer.TickSignal().Connect( this, &LinearConstrainer_TestApp::Tick );
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
        case LINEAR_CONSTRAINER_NEW_P:
          LinearConstrainerNewP();
          break;

        case LINEAR_CONSTRAINER_COPY_CONSTRUCTOR_P:
          LinearConstrainerCopyConstructorP();
          break;

        case LINEAR_CONSTRAINER_CONSTRUCTOR_P:
          LinearConstrainerConstructorP();
          break;

        case LINEAR_CONSTRAINER_DOWNCAST_P:
          LinearConstrainerDowncastP();
          break;

        case LINEAR_CONSTRAINER_DOWNCAST_N:
          LinearConstrainerDowncastN();
          break;

        case LINEAR_CONSTRAINER_OPERTORASSIGNMENT_P:
          LinearConstrainerOperatorAssignmentP();
          break;

        case LINEAR_CONSTRAINER_APPLY_REMOVE_P:
          LinearConstrainerApplyRemoveP();
          break;

      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case LINEAR_CONSTRAINER_APPLY_REMOVE_P:
          switch (gRenderCountLinearConstrainer)
          {
            case 0:
              VTLinearConstrainerApplyRemove001();
              gRenderCountLinearConstrainer++;
              break;
            case 1:
              VTLinearConstrainerApplyRemove002();
              gRenderCountLinearConstrainer++;
              break;
            case 2:
              VTLinearConstrainerApplyRemove003();
              gRenderCountLinearConstrainer++;
              break;
            case 3:
              VTLinearConstrainerApplyRemove004();
              gRenderCountLinearConstrainer++;
              break;
            case 4:
              VTLinearConstrainerApplyRemove005();
              gRenderCountLinearConstrainer++;
              break;
            case 5:
              VTLinearConstrainerApplyRemove006();
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
 * @testcase                 UtcDaliLinearConstrainerNewP
 * @since_tizen              2.4
 * @description              Create a LinearConstrainer handle using New static method.
 */
int UtcDaliLinearConstrainerNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliLinearConstrainerDownCastP
 * @since_tizen              2.4
 * @description              Downcast an Object handle to LinearConstrainer handle..
 */
int UtcDaliLinearConstrainerDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase                 UtcDaliLinearConstrainerDownCastN
 * @since_tizen              2.4
 * @description              Downcast an Object handle to LinearConstrainer handle..
 */
int UtcDaliLinearConstrainerDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliLinearConstrainerConstructorP
 * @since_tizen              2.4
 * @description              Create an initialized LinearConstrainer handle using default constructor.
 */
int UtcDaliLinearConstrainerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliLinearConstrainerCopyConstructorP
 * @since_tizen              2.4
 * @description              Create an initialized LinearConstrainer handle using copy constructor.
 */
int UtcDaliLinearConstrainerCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliLinearConstrainerOperatorAssignmentP
 * @since_tizen              2.4
 * @description              Create an initialized LinearConstrainer handle using copy constructor.
 */
int UtcDaliLinearConstrainerOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_OPERTORASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase                 UtcDaliLinearConstrainerApplyRemoveP
 * @since_tizen              2.4
 * @description              Applies and Remove the linear constraint to the target property
 */
int UtcDaliLinearConstrainerApplyRemoveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  LinearConstrainer_TestApp testApp( application, LINEAR_CONSTRAINER_APPLY_REMOVE_P );
  application.MainLoop();

  return test_return_value;
}

