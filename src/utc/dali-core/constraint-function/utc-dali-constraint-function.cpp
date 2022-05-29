#include "utc-dali-constraint-function-impl.h"

//& set: Constraint

/**
 * @function            utc_Dali_ConstraintFunction_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConstraintFunction_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Constraint_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_ConstraintFunction_cleanup(void)
{

}

namespace
{
  enum TEST_CASES_LIST_CONSTRAINT_FUNCTION
  {
    CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTION_P,
    CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTOR_P,
    CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_METHOD_FUNCTOR_P,
    CONSTRAINT_FUNCTION_FUNCTION_CLONE_P,
    CONSTRAINT_FUNCTION_FUNCTOR_CLONE_P,
    CONSTRAINT_FUNCTION_METHOD_FUNCTOR_CLONE_P
  };

  struct ConstraintFunction_TestApp : public ConnectionTracker
  {
    ConstraintFunction_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ConstraintFunction_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ConstraintFunction_TestApp::Tick );
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
        case CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTION_P:
          ConstraintFunctionConstructorWithFunctionP();
          break;
        case CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTOR_P:
          ConstraintFunctionConstructorWithFunctorP();
          break;
        case CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_METHOD_FUNCTOR_P:
          ConstraintFunctionConstructorWithMethodFunctorP();
          break;
        case CONSTRAINT_FUNCTION_FUNCTION_CLONE_P:
          ConstraintFunctionFunctionCloneP();
          break;
        case CONSTRAINT_FUNCTION_FUNCTOR_CLONE_P:
          ConstraintFunctionFunctorCloneP();
          break;
        case CONSTRAINT_FUNCTION_METHOD_FUNCTOR_CLONE_P:
          ConstraintFunctionMethodFunctorCloneP();
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
 * @testcase        UtcDaliConstraintFunctionWithFunctionP
 * @since_tizen     2.4
 * @description     To check if the constructor which connects to the provided C function (or a static member function) works fine or not
 */
int UtcDaliConstraintFunctionWithFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintFunctionWithFunctorP
 * @since_tizen     2.4
 * @description     To check if the constructor which copies a function object and connects to the functor of that object works fine or not
 */
int UtcDaliConstraintFunctionWithFunctorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_FUNCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintFunctionWithFunctorP
 * @since_tizen     2.4
 * @description     To check if the constructor which copies a function object and allows a connection to a member method works fine or not
 */
int UtcDaliConstraintFunctionWithMethodFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_CONSTRUCTOR_WITH_METHOD_FUNCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintFunctionCloneP
 * @since_tizen     2.4
 * @description     To check if the clone to the Function object works fine or not
 */
int UtcDaliConstraintFunctionCloneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_FUNCTION_CLONE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintFunctorCloneP
 * @since_tizen     2.4
 * @description     To check if the clone to the Functor object works fine or not
 */
int UtcDaliConstraintFunctorCloneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_FUNCTOR_CLONE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintMethodFunctionCloneP
 * @since_tizen     2.4
 * @description     To check if the clone a function object and allows a connection to a member method works fine or not
 */
int UtcDaliConstraintMethodFunctionCloneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ConstraintFunction_TestApp testapp( application, CONSTRAINT_FUNCTION_METHOD_FUNCTOR_CLONE_P);
  application.MainLoop();
  return test_return_value;
}
