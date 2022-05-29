#include "utc-dali-math-utils-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Mathutils

/**
 * @function      utc_Dali_MathUtils_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_MathUtils_startup(void)
{
  test_return_value=TC_PASS;
  gRenderCountMathUtils=TC_PASS;
}

/**
 * @function      utc_Dali_MathUtils_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_MathUtils_cleanup(void)
{
}

namespace
{
  enum TEST_CASES_LIST_ACTOR
  {
    MATH_UTILS_NEXT_POWER_OF_TWO_P,
    MATH_UTILS_IS_POWER_OF_TWO_P,
    MATH_UTILS_EQUALS_ZERO_P,
    MATH_UTILS_SHORTEST_DISTANCE_IN_DOMAIN_P,
    MATH_UTILS_CLAMP_FLOAT_P,
    MATH_UTILS_CLAMP_INT_P,
    MATH_UTILS_CLAMP_IN_PLACE_FLOAT_P,
    MATH_UTILS_CLAMP_IN_PLACE_INT_P,
    MATH_UTILS_ROUND_P,
    MATH_UTILS_LERP_FOR_FLOAT_P,
    MATH_UTILS_LERP_FOR_INT_P,
    MATH_UTILS_EQUALS_WITH_AND_WITH_OUT_EPSILON_P,
    MATH_UTILS_SIGN_P,
    MATH_UTILS_WRAP_IN_DOMAIN_P
  };

  struct Math_Utils_TestApp : public ConnectionTracker
  {
    Math_Utils_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Math_Utils_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Math_Utils_TestApp::Tick );
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
        case MATH_UTILS_NEXT_POWER_OF_TWO_P:
          MathUtilsNextPowerOfTwoP();
          break;

        case MATH_UTILS_IS_POWER_OF_TWO_P:
          MathUtilsIsPowerOfTwoP();
          break;

        case MATH_UTILS_EQUALS_ZERO_P:
          MathUtilsEqualsZeroP();
          break;

        case MATH_UTILS_SHORTEST_DISTANCE_IN_DOMAIN_P:
          MathUtilsShortestDistanceInDomainP();
          break;

        case MATH_UTILS_CLAMP_FLOAT_P:
          MathUtilsClampfloatP();
          break;

        case MATH_UTILS_CLAMP_INT_P:
          MathUtilsClampintP();
          break;

        case MATH_UTILS_CLAMP_IN_PLACE_FLOAT_P:
          MathUtilsClampInPlacefloatP();
          break;

        case MATH_UTILS_CLAMP_IN_PLACE_INT_P:
          MathUtilsClampInPlaceintP();
          break;

        case MATH_UTILS_ROUND_P:
          MathUtilsRoundP();
          break;

        case MATH_UTILS_LERP_FOR_FLOAT_P:
          MathUtilsLerpForFloatP();
          break;

        case MATH_UTILS_LERP_FOR_INT_P:
          MathUtilsLerpForIntP();
          break;

        case MATH_UTILS_EQUALS_WITH_AND_WITH_OUT_EPSILON_P:
          MathUtilsEqualsWithAndWithoutEpsilonP();
          break;

        case MATH_UTILS_SIGN_P:
          MathUtilsSignP();
          break;

        case MATH_UTILS_WRAP_IN_DOMAIN_P:
          MathUtilsWarpInDomainP();
          break;

      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case MATH_UTILS_EQUALS_WITH_AND_WITH_OUT_EPSILON_P:
          switch (gRenderCountMathUtils)
          {
            case 0:
              VTMathUtilsEqualsWithAndWithoutEpsilon001();
              gRenderCountMathUtils++;
              break;

            case 1:
              VTMathUtilsEqualsWithAndWithoutEpsilon002();
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
 * @testcase      UtcDaliMathUtilsNextPowerOfTwoP
 * @since_tizen   2.4
 * @description   check if MathUtilsNextPowerOfTwoP api works or not.
 */
int UtcDaliMathUtilsNextPowerOfTwoP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_NEXT_POWER_OF_TWO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsIsPowerOfTwoP
 * @since_tizen   2.4
 * @description   check if MathUtilsIsPowerOfTwoP api works or not.
 */
int UtcDaliMathUtilsIsPowerOfTwoP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_IS_POWER_OF_TWO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsEqualsZeroP
 * @since_tizen   2.4
 * @description   check if MathUtilsEqualsZeroP api works or not.
 */
int UtcDaliMathUtilsEqualsZeroP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_EQUALS_ZERO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsShortestDistanceInDomainP
 * @since_tizen   2.4
 * @description   check if MathUtilsShortestDistanceInDomainP api works or not.
 */
int UtcDaliMathUtilsShortestDistanceInDomainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_SHORTEST_DISTANCE_IN_DOMAIN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsClampfloatP
 * @since_tizen   2.4
 * @description   check if ClampfloatP api works or not.
 */
int UtcDaliMathUtilsClampfloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_CLAMP_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsClampintP
 * @since_tizen   2.4
 * @description   check if ClampintP api works or not.
 */
int UtcDaliMathUtilsClampintP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_CLAMP_INT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsClampInPlacefloatP
 * @since_tizen   2.4
 * @description   check if ClampInPlacefloatP api works or not.
 */
int UtcDaliMathUtilsClampInPlacefloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_CLAMP_IN_PLACE_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsClampInPlaceintP
 * @since_tizen   2.4
 * @description   check if ClampInPlaceint api works or not.
 */
int UtcDaliMathUtilsClampInPlaceintP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_CLAMP_IN_PLACE_INT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsRoundP
 * @since_tizen   2.4
 * @description   check if Round api works or not.
 */
int UtcDaliMathUtilsRoundP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_ROUND_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsLerpForFloatP
 * @since_tizen   2.4
 * @description   check if LerpForFloat api works or not.
 */
int UtcDaliMathUtilsLerpForFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_LERP_FOR_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsLerpForIntP
 * @since_tizen   2.4
 * @description   check if LerpForInt api works or not.
 */
int UtcDaliMathUtilsLerpForIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_LERP_FOR_INT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsEqualsWithAndWithoutEpsilonP
 * @since_tizen   2.4
 * @description   check if EqualsWithAndWithoutEpsilon api works or not.
 */
int UtcDaliMathUtilsEqualsWithAndWithoutEpsilonP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_EQUALS_WITH_AND_WITH_OUT_EPSILON_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliMathUtilsSignP
 * @since_tizen             2.4
 * @description             Check sign of a value.
 */
int UtcDaliMathUtilsSignP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_SIGN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliMathUtilsWarpInDomainP
 * @since_tizen   2.4
 * @description   return the wrapped value over the domain (start) (end).
 */
int UtcDaliMathUtilsWarpInDomainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Math_Utils_TestApp testApp( application, MATH_UTILS_WRAP_IN_DOMAIN_P);
  application.MainLoop();
  return test_return_value;
}
