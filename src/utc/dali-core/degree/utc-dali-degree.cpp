#include "utc-dali-degree-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Degree

/**
 * @function      utc_Dali_Degree_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Degree_startup(void)
{
  test_return_value = 0;
}

/**
 * @function      utc_Dali_Degree_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Degree_cleanup(void)
{

}

void DegreeConsFloatP();
void DegreeConsRadianP();
void DegreeOperatorEqualP();
void DegreeOperatorNotEqualP();
void DegreeCastOperatorP();
void DegreeCastOperatorP2();
void DegreeOperatorCompareP();
void DegreeClampP();

namespace
{
  enum TEST_CASES_LIST_DEGREE
  {
    DEGREE_CONSTRUCTOR_FLOAT_P,
    DEGREE_CONSTRUCTOR_RADIAN_P,
    DEGREE_OPERATOR_EQUAL_P,
    DEGREE_OPERATOR_NOTEQUAL_P,
    DEGREE_CAST_OPERATOR_P,
    DEGREE_CAST_OPERATOR_P2,
    DEGREE_OPERATOR_COMPARE_P,
    DEGREE_CLAMP_P
  };

  struct Degree_TestApp : public ConnectionTracker
  {
    Degree_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Degree_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Degree_TestApp::Tick );
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
        case DEGREE_CONSTRUCTOR_FLOAT_P:
          DegreeConsFloatP();
          break;

        case DEGREE_CONSTRUCTOR_RADIAN_P:
          DegreeConsRadianP();
          break;

        case DEGREE_OPERATOR_EQUAL_P:
          DegreeOperatorEqualP();
          break;

        case DEGREE_OPERATOR_NOTEQUAL_P:
          DegreeOperatorNotEqualP();
          break;

        case DEGREE_CAST_OPERATOR_P:
          DegreeCastOperatorP();
          break;

        case DEGREE_CAST_OPERATOR_P2:
          DegreeCastOperatorP2();
          break;

        case DEGREE_OPERATOR_COMPARE_P:
          DegreeOperatorCompareP();
          break;

        case DEGREE_CLAMP_P:
          DegreeClampP();
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

void DegreeConsFloatP()
{
  Degree degree(ANGLE_ONE80);
  DALI_CHECK_FAIL(degree.degree !=  ANGLE_ONE80, "Dali::Degree is Failed: angle value mismatches.");
  DALI_CHECK_FAIL(degree.degree != (Radian(degree) * ONE80_OVER_PI), "Dali::Degree is Failed: radian angle value from degree value compared mismatches.");

  DaliLog::PrintPass();
}

void DegreeConsRadianP()
{
  Degree degree( Radian( (float)Math::PI ) );
  DALI_CHECK_FAIL(degree.degree !=  ANGLE_ONE80, "Dali::Degree(radian) is Failed: angle value mismatches.");
  DALI_CHECK_FAIL(degree.degree != (Radian(degree) * ONE80_OVER_PI), "Dali::Degree(radian) is Failed: radian angle value from degree value compared mismatches.");

  DaliLog::PrintPass();
}

void DegreeOperatorEqualP()
{
  Degree degree1(ANGLE_RHS);

  Degree degree2(ANGLE_LHS);
  DALI_CHECK_FAIL(degree1.degree != degree2.degree, "Equality operator [ operator==(degree) ] is Failed: angle value mismatches.");

  DaliLog::PrintPass();
}

void DegreeOperatorNotEqualP()
{
  const float ANGLE180_RHS = 180.0f, ANGLE90_LHS = 90.0f;

  Degree degree1(ANGLE90_LHS);

  Degree degree2(ANGLE180_RHS);
  DALI_CHECK_FAIL(degree1.degree == degree2.degree, "Inequality operator [ operator!=(degree) ] is Failed: angle value matches.");

  DaliLog::PrintPass();
}

void DegreeCastOperatorP()
{
  Degree degree1(ANGLE_LHS);

  const float& val1( degree1.degree );
  DALI_CHECK_FAIL(val1 != ANGLE_RHS, "Cast operator [ operator const float&() ] is Failed: angle value mismatches.");

  DaliLog::PrintPass();
}

void DegreeCastOperatorP2()
{
  Degree degree1(ANGLE_LHS);

  float& val1( degree1.degree );
  DALI_CHECK_FAIL(val1 != ANGLE_RHS, "Cast operator [ operator float&() ] is Failed: angle value mismatches.");

  DaliLog::PrintPass();
}

void DegreeOperatorCompareP()
{
  const float ANGLE180_RHS = 180.0f, ANGLE90_LHS = 90.0f;

  Degree degree1(ANGLE90_LHS);

  Degree degree2(ANGLE180_RHS);
  DALI_CHECK_FAIL(!(Radian(degree1) < degree2), "Comparison operator [ operator<( degree ) ] is Failed: angle value comparison fails.");

  DaliLog::PrintPass();
}

void DegreeClampP()
{
  const float fMin = ANGLE_ONE80 - 30.0f, fMax = ANGLE_ONE80 + 20.0f;

  Degree degree(ANGLE_ONE80);
  DALI_CHECK_FAIL(degree.degree !=  ANGLE_ONE80, "Dali::Degree is Failed: angle value mismatches.");
  DALI_CHECK_FAIL(degree.degree != (Radian(degree) * ONE80_OVER_PI), "Dali::Degree is Failed: radian angle value from degree value compared mismatches.");

  Degree clampedDeg = Clamp( degree, fMin, fMax);
  DALI_CHECK_FAIL(clampedDeg != Degree(ClampAngle<float>(degree.degree, fMin, fMax)), "Dali::Clamp() is Failed: Clamped angle did not match for degree.");

  Degree degreeMin(fMin - 5.0f);

  clampedDeg = Clamp( degreeMin, fMin, fMax);
  DALI_CHECK_FAIL(clampedDeg != Degree(fMin), "Dali::Clamp() is Failed: Clamped angle did not match for degree.");

  Degree degreeMax(fMax + 5.0f);

  clampedDeg = Clamp( degreeMax, fMin, fMax);
  DALI_CHECK_FAIL(clampedDeg != Degree(fMax), "Dali::Clamp() is Failed: Clamped angle did not match for degree.");

  DaliLog::PrintPass();
}



/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase      UtcDaliDegreeConstructorFloatP
 * @since_tizen   2.4
 * @description   check if DegreeConstructorFloat api works or not.
 */
int UtcDaliDegreeConstructorFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_CONSTRUCTOR_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeConstructorRadianP
 * @since_tizen   2.4
 * @description   check if DegreeConstructorRadianP api works or not.
 */
int UtcDaliDegreeConstructorRadianP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_CONSTRUCTOR_RADIAN_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeOperatorEqualP
 * @since_tizen   2.4
 * @description   check if DegreeOperatorEqualP api works or not.
 */
int UtcDaliDegreeOperatorEqualP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_OPERATOR_EQUAL_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeOperatorNotEqualP
 * @since_tizen   2.4
 * @description   check if DegreeOperatorNotEqualP api works or not.
 */
int UtcDaliDegreeOperatorNotEqualP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_OPERATOR_NOTEQUAL_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeCastOperatorP
 * @since_tizen   2.4
 * @description   check if DegreeCastOperatorP api works or not.
 */
int UtcDaliDegreeCastOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_CAST_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeCastOperatorP2
 * @since_tizen   2.4
 * @description   check if DegreeCastOperatorP2 api works or not.
 */
int UtcDaliDegreeCastOperatorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_CAST_OPERATOR_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeOperatorCompareP
 * @since_tizen   2.4
 * @description   check if DegreeOperatorCompareP api works or not.
 */
int UtcDaliDegreeOperatorCompareP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_OPERATOR_COMPARE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliDegreeClampP
 * @since_tizen   2.4
 * @description   check if DegreeClampP api works or not.
 */
int UtcDaliDegreeClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Degree_TestApp testApp( application, DEGREE_CLAMP_P);
  application.MainLoop();
  return test_return_value;
}
