#include "utc-dali-alpha-function-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_AlphaFunction_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AlphaFunction_startup(void)
{
  test_return_value =0;
  gRenderCountAlphaFunction=TC_PASS;
}


/**
 * @function            utc_Dali_AlphaFunction_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AlphaFunction_cleanup(void)
{

}


/**
 * @function         customAlphaFunction
 * @description        Function for testing creation of AlphaFunction with function Pointer
 * @param    [in]    float progress
 * @return      NA
 */

namespace
{
  enum TEST_CASES_LIST_ACTOR
  {
    ALPHAFUNCTION_DEFAULT,
    ALPHAFUNCTION_BUILTINFUNCTION,
    ALPHAFUNCTION_BYFUNCTION_PROTOTYPE_GET_CUSTOMFUNCTION,
    ALPHAFUNCTION_BY_CONTROLPOINTS_GETBEZIER_CONTROLPOINTS,
    ALPHAFUNCTION_GETMODE,
    ALPHAFUNCTION_CONSTRUCTOR_FROM_FUNCTION_POINTER
  };

  struct Actor_TestApp : public ConnectionTracker
  {
    Actor_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Actor_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL + 200 ); //Add render delay time
      mTimer.TickSignal().Connect( this, &Actor_TestApp::Tick );
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
        case ALPHAFUNCTION_DEFAULT:
          AlphaFunctionDefault();
          break;

        case ALPHAFUNCTION_BUILTINFUNCTION:
          AlphaFunctionBuiltinFunction();
          break;

        case ALPHAFUNCTION_BYFUNCTION_PROTOTYPE_GET_CUSTOMFUNCTION:
          AlphaFunctionByFunctionPrototypeGetCustomFunction();
          break;

        case ALPHAFUNCTION_BY_CONTROLPOINTS_GETBEZIER_CONTROLPOINTS:
          AlphaFunctionByControlPointsGetBezierControlPoints();
          break;

        case ALPHAFUNCTION_GETMODE:
          AlphaFunctionGetMode();
          break;

        case ALPHAFUNCTION_CONSTRUCTOR_FROM_FUNCTION_POINTER:
          AlphaFunctionConstructorFromFunctionPointer();
          break;

      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case ALPHAFUNCTION_DEFAULT:
          switch (gRenderCountAlphaFunction)
          {
            case 0:
              VTAlphaFunctionDefault001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ALPHAFUNCTION_BUILTINFUNCTION:
          switch (gRenderCountAlphaFunction)
          {
            case 0:
              VTAlphaFunctionBuiltinFunction001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ALPHAFUNCTION_BYFUNCTION_PROTOTYPE_GET_CUSTOMFUNCTION:
          switch (gRenderCountAlphaFunction)
          {
            case 0:
              VTAlphaFunctionByFunctionPrototypeGetCustomFunction001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case ALPHAFUNCTION_BY_CONTROLPOINTS_GETBEZIER_CONTROLPOINTS:
          switch (gRenderCountAlphaFunction)
          {
            case 0:
              VTAlphaFunctionByControlPointsGetBezierControlPoints001();
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


    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


/**
 * @testcase            UtcDaliAlphaFunctionDefaultP
 * @since_tizen         2.4
 * @description         check if the default constructor works or not.
 */

int UtcDaliAlphaFunctionDefaultP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_DEFAULT);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAlphaFunctionBuiltinFunctionP
 * @since_tizen         2.4
 * @description         check if the BuiltinFunction api works or not.
 */

int UtcDaliAlphaFunctionBuiltinFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_BUILTINFUNCTION);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAlphaFunctionGetCustomFunctionP
 * @since_tizen         2.4
 * @description         check if the GetCustomFunction api works or not.
 */

int UtcDaliAlphaFunctionGetCustomFunctionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_BYFUNCTION_PROTOTYPE_GET_CUSTOMFUNCTION);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAlphaFunctionGetBezierControlPointsP
 * @since_tizen         2.4
 * @description         check if the GetBezierControlPoints api works or not.
 */

int UtcDaliAlphaFunctionGetBezierControlPointsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_BY_CONTROLPOINTS_GETBEZIER_CONTROLPOINTS);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAlphaFunctionGetModeP
 * @since_tizen         2.4
 * @description         check if the GetMode api works or not.
 */

int UtcDaliAlphaFunctionGetModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_GETMODE);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAlphaFunctionConstructorFromFunctionPointerP
 * @since_tizen         2.4
 * @description         check if the constructor works or not.
 */

int UtcDaliAlphaFunctionConstructorFromFunctionPointerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Actor_TestApp testApp( application, ALPHAFUNCTION_CONSTRUCTOR_FROM_FUNCTION_POINTER);
  application.MainLoop();
  return test_return_value;
}
