#include "utc-dali-radian-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Radian_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Radian_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Radian_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Radian_cleanup(void)
{

}

void RadianConstruct();
void RadianOperatorEqual();
void RadianOperatorNotEqual();
void RadianCastOperator1();
void RadianCastOperator2();
void RadianOperatorCompareLess();
void RadianClamp();
void RadianAnglesCheck();
void RadianComparisonOperator();

namespace
{
  enum TEST_CASES_LIST_RADIAN
  {
    RADIAN_CONSTRUCT,
    RADIAN_OPERATOR_EQUAL,
    RADIAN_OPERATOR_NOT_EQUAL,
    RADIAN_CASTOPERATOR1,
    RADIAN_CASTOPERATOR2,
    RADIAN_OPERATOR_COMPARELESS,
    RADIAN_CLAMP,
    RADIAN_ANGLES,
    RADIAN_COMPARISON_OPERATORS,
  };

  struct Radian_TestApp : public ConnectionTracker
  {
    Radian_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Radian_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Radian_TestApp::Tick );
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
        case RADIAN_CONSTRUCT:
          RadianConstruct();
          break;

        case RADIAN_OPERATOR_EQUAL:
          RadianOperatorEqual();
          break;

        case RADIAN_OPERATOR_NOT_EQUAL:
          RadianOperatorNotEqual();
          break;

        case RADIAN_CASTOPERATOR1:
          RadianCastOperator1();
          break;

        case RADIAN_CASTOPERATOR2:
          RadianCastOperator2();
          break;

        case RADIAN_OPERATOR_COMPARELESS:
          RadianOperatorCompareLess();
          break;

        case RADIAN_CLAMP:
          RadianClamp();
          break;

        case RADIAN_ANGLES:
          RadianAnglesCheck();
          break;

        case RADIAN_COMPARISON_OPERATORS:
          RadianComparisonOperator();
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
void RadianConstruct()
{
  const Degree ANGLE_VALUE(180.0f);

  Radian radian1(Math::PI);
  DALI_CHECK_FAIL(radian1 != Math::PI, " Dali::Radian::Radian() is Failed" );

  Radian radian2(ANGLE_VALUE);
  DALI_CHECK_FAIL(radian2 != Math::PI, "Dali::Radian::Radian(degree) is Failed" );

  DaliLog::PrintPass();
}
void RadianOperatorEqual()
{
  Radian radian1(Math::PI_2);
  Radian radian2(Math::PI_2);

  DALI_CHECK_FAIL(radian1 != radian2, "The equality operator is Failed" );
  DaliLog::PrintPass();
}
void RadianOperatorNotEqual()
{
  Radian radian1(Math::PI);
  Radian radian2(Math::PI_2);

  DALI_CHECK_FAIL(radian1 == radian2, "The inequality operator is Failed " );

  DaliLog::PrintPass();
}
void RadianCastOperator1()
{
  Radian radian1(Math::PI);

  const float& val1( radian1 );

  DALI_CHECK_FAIL(val1 != Math::PI, "Dali::Radian cast operator constant float is Failed " );

  DaliLog::PrintPass();
}
void RadianCastOperator2()
{
  Radian radian1(Math::PI);

  Radian& val1( radian1 );

  DALI_CHECK_FAIL(val1 != Math::PI, "Dali::Radian cast operator float is Failed" );

  DaliLog::PrintPass();
}
void RadianOperatorCompareLess()
{
  Radian radian1(Math::PI_2);
  Radian radian2(Math::PI);

  DALI_CHECK_FAIL(radian1 >= radian2, "Dali::Radian comparison operator is Failed" );

  DaliLog::PrintPass();
}
void RadianClamp()
{
  const float fMin = Math::PI - 0.25f, fMax = Math::PI + 0.25f;

  Radian radian1(Math::PI);
  DALI_CHECK_FAIL(radian1.radian != Math::PI, "Dali::Radian::Radian() is Failed. The radian value is not set." );

  Radian clampedRad = Dali::Clamp(radian1, fMin, fMax);
  DALI_CHECK_FAIL(clampedRad != Radian(ClampAngle<float>(radian1.radian, fMin, fMax)), "Dali::Clamp() is Failed: Clamped angle did not match for radian." );

  Radian radianMin(fMin - 0.25f);
  clampedRad = Dali::Clamp(radianMin, fMin, fMax);
  DALI_CHECK_FAIL(clampedRad != Radian(fMin), "Dali::Clamp() is Failed: Clamped angle did not match for radian.");
  Radian radianMax(fMax + 0.25f);
  clampedRad = Dali::Clamp(radianMax, fMin, fMax);
  DALI_CHECK_FAIL(clampedRad != Radian(fMax), "Dali::Clamp() is Failed: Clamped angle did not match for radian.");

  DaliLog::PrintPass();
}

void RadianAnglesCheck()
{
  const Degree ANGLE_VALUE_360(360.0f);
  const Degree ANGLE_VALUE_315(315.0f);
  const Degree ANGLE_VALUE_270(270.0f);
  const Degree ANGLE_VALUE_225(225.0f);
  const Degree ANGLE_VALUE_180(180.0f);
  const Degree ANGLE_VALUE_135(135.0f);
  const Degree ANGLE_VALUE_120(120.0f);
  const Degree ANGLE_VALUE_90(90.0f);
  const Degree ANGLE_VALUE_60(60.0f);
  const Degree ANGLE_VALUE_45(45.0f);
  const Degree ANGLE_VALUE_30(30.0f);
  const Degree ANGLE_VALUE_0(0.0f);

  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_360) != ANGLE_360, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_315) != ANGLE_315, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_270) != ANGLE_270, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_225) != ANGLE_225, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_180) != ANGLE_180, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_135) != ANGLE_135, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_120) != ANGLE_120, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_90) != ANGLE_90, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_60) != ANGLE_60, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_45) != ANGLE_45, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_30) != ANGLE_30, " Failed to retrieve Angle." );
  DALI_CHECK_FAIL(Radian(ANGLE_VALUE_0) != ANGLE_0, " Failed to retrieve Angle." );

  DaliLog::PrintPass();
}

void RadianComparisonOperator()
{
  Radian a(Math::PI_4);
  Radian b(Math::PI_2);
  Radian c(Math::PI);
  Radian d(2.0f*Math::PI);
  Radian e(-Math::PI);

  DALI_CHECK_FAIL( Radian(Math::PI_2) > Degree(180.0f), "Dali::Radian comparison operator is Failed");
  DALI_CHECK_FAIL( Radian(Math::PI_2) > Degree(90.0f),  "Dali::Radian comparison operator is Failed");
  DALI_CHECK_FAIL( Radian(Math::PI_2) < Degree(45.0f),  "Dali::Radian comparison operator is Failed");

  DALI_CHECK_FAIL( Degree(180.0f) < Radian(Math::PI_2), "Dali::Radian comparison operator is Failed");
  DALI_CHECK_FAIL( Degree(90.0f) < Radian(Math::PI_2), "Dali::Radian comparison operator is Failed");
  DALI_CHECK_FAIL( Degree(45.0f) > Radian(Math::PI_2), "Dali::Radian comparison operator is Failed");

  DALI_CHECK_FAIL( Degree(b) == c, "Dali::Radian comparison operator is Failed" );
  DALI_CHECK_FAIL( Degree(c) != c, "Dali::Radian comparison operator is Failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase         UtcDaliRadianConsFloatP
 * @since_tizen      2.4
 * @description      Create an angle in radians.
 */
int UtcDaliRadianConstructP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_CONSTRUCT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianOperatorEqualP
 * @since_tizen      2.4
 * @description      Compare equality between two radians.
 */
int UtcDaliRadianOperatorEqualP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_OPERATOR_EQUAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianOperatorNotEqualP
 * @since_tizen      2.4
 * @description      Compare inequality between two radians.
 */
int UtcDaliRadianOperatorNotEqualP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_OPERATOR_NOT_EQUAL);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianCastOperator1P
 * @since_tizen      2.4
 * @description      Cast operator to const float reference.
 */
int UtcDaliRadianCastOperator1P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_CASTOPERATOR1);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianCastOperator2P
 * @since_tizen      2.4
 * @description      Cast operator to const float reference.
 */
int UtcDaliRadianCastOperator2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_CASTOPERATOR2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianOperatorCompareLessP
 * @since_tizen      2.4
 * @description      It compare two radians.
 */
int UtcDaliRadianOperatorCompareLessP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_OPERATOR_COMPARELESS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianClampP
 * @since_tizen      2.4
 * @description      If it clamps angle to between or to the minimum and maximum values.
 */
int UtcDaliRadianClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_CLAMP);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianAnglesCheckP
 * @since_tizen      2.4
 * @description      Check for Radian constant angle values.
 */
int UtcDaliRadianAnglesCheckP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_ANGLES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliRadianComparisonOperator
 * @since_tizen      2.4
 * @description      checks for Radian comparison operators.
 */
int UtcDaliRadianComparisonOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Radian_TestApp testApp( application, RADIAN_COMPARISON_OPERATORS);
  application.MainLoop();
  return test_return_value;
}

