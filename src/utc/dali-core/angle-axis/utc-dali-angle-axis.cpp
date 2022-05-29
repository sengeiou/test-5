#include "utc-dali-angle-axis-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Angleaxis
/**
 * @function      utc_Dali_AngleAxis_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */

void utc_Dali_AngleAxis_startup(void)
{
  test_return_value = 0;
}


/**
 * @function      utc_Dali_AngleAxis_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */

void utc_Dali_AngleAxis_cleanup(void)
{

}

void AngleAxisConstructorP();
void AngleAxisConsDegreeP();
void AngleAxisConsRadianP();
void AngleAxisEqualP();
void AngleAxisOutputStreamOpeatorP();

namespace
{
  enum TEST_CASES_LIST_ACTOR
  {
    ANGLE_AXIS_CONSTRUCTOR_P,
    ANGLE_AXIS_CONSTRUCTOR_DEGREE_P,
    ANGLE_AXIS_CONSTRUCTOR_RADIAN_P,
    ANGLE_AXIS_EQUAL_P,
    ANGLE_AXIS_OUTPUT_STREAM_OPERATOR_P
  };

  struct AngleAxis_TestApp : public ConnectionTracker
  {
    AngleAxis_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &AngleAxis_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &AngleAxis_TestApp::Tick );
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
        case ANGLE_AXIS_CONSTRUCTOR_P:
          AngleAxisConstructorP();
          break;

        case ANGLE_AXIS_CONSTRUCTOR_DEGREE_P:
          AngleAxisConsDegreeP();
          break;

        case ANGLE_AXIS_CONSTRUCTOR_RADIAN_P:
          AngleAxisConsRadianP();
          break;

        case ANGLE_AXIS_EQUAL_P:
          AngleAxisEqualP();
          break;

        case ANGLE_AXIS_OUTPUT_STREAM_OPERATOR_P:
          AngleAxisOutputStreamOpeatorP();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

void AngleAxisConsRadianP()
{
  Radian radian(Math::PI_2);

  AngleAxis angleaxis(radian, Vector3::ZAXIS);

  DALI_CHECK_FAIL(angleaxis.axis != Vector3::ZAXIS, " Dali::AngleAxis(radian, axis) is Failed: axis position mismatches.");
  DALI_CHECK_FAIL(angleaxis.angle !=  Degree(Radian(Math::PI_2)), " Dali::AngleAxis(radian, axis) is Failed: angle rotation mismatches.");

  DaliLog::PrintPass();
}

void AngleAxisConstructorP()
{
  AngleAxis angleaxis;
  const float WIDTH_DEFAULT = 0.0f, HEIGHT_DEFAULT = 0.0f, DEPTH_DEFAULT = 0.0f;

  Radian angle = angleaxis.angle;
  DALI_CHECK_FAIL(angle.radian != 0.0f, "AngleAxis::angle is Null");
  DALI_CHECK_FAIL(angleaxis.axis != Vector3(WIDTH_DEFAULT, HEIGHT_DEFAULT, DEPTH_DEFAULT), " Dali::AngleAxis is Failed: vector inatances mismatches.");
  DALI_CHECK_FAIL(angleaxis.axis.x != WIDTH_DEFAULT || angleaxis.axis.y != HEIGHT_DEFAULT || angleaxis.axis.z != DEPTH_DEFAULT, " Dali::AngleAxis is Failed: vector (width or height or depth) value(s) mismatches.");

  DaliLog::PrintPass();
}

void AngleAxisConsDegreeP()
{
  const float ANGLE_ROTATION = 75.0f;
  Degree degree(ANGLE_ROTATION);

  AngleAxis angleaxis(degree, Vector3::XAXIS);

  DALI_CHECK_FAIL(angleaxis.angle != degree, " Dali::AngleAxis(degree, axis) is Failed: angle rotation mismatches.");
  DALI_CHECK_FAIL(angleaxis.axis != Vector3::XAXIS, " Dali::AngleAxis(degree, axis) is Failed: axis position mismatches.");

  DaliLog::PrintPass();
}

void AngleAxisEqualP()
{
  Radian r(Math::PI_2);
  AngleAxis a(r, Vector3::ZAXIS);
  AngleAxis b(a);

  DALI_CHECK_FAIL((!(a == b)), " Dali::AngleAxisEqualP(axis, axis) is Failed: axis position mismatches.");
  b.axis = Vector3::YAXIS;
  DALI_CHECK_FAIL((a == b), " Dali::AngleAxisEqualP(axis, axis) is Failed: axis position mismatches.");

  DaliLog::PrintPass();
}

void AngleAxisOutputStreamOpeatorP()
{
  AngleAxis angleaxisx( Dali::ANGLE_120, Vector3::XAXIS );
  std::ostringstream streamx;
  streamx << angleaxisx;
  DALI_CHECK_FAIL( streamx.str().compare("[ Axis: [1, 0, 0], Angle: 120 degrees ]") !=0, "out stream value not match");

  AngleAxis angleaxisy( Dali::ANGLE_120, Vector3::YAXIS );
  std::ostringstream streamy;
  streamy << angleaxisy;
  DALI_CHECK_FAIL( streamy.str().compare("[ Axis: [0, 1, 0], Angle: 120 degrees ]") !=0, "out stream value not match");

  AngleAxis angleaxisz( Dali::ANGLE_120, Vector3::ZAXIS );
  std::ostringstream streamz;
  streamz << angleaxisz;
  DALI_CHECK_FAIL( streamz.str().compare("[ Axis: [0, 0, 1], Angle: 120 degrees ]") !=0, "out stream value not match");
  DaliLog::PrintPass();
}


/**
 * @testcase      UtcDaliAngleAxisConstructorP
 * @since_tizen   2.4
 * @description   check if Constructor api works or not.
 */

int UtcDaliAngleAxisConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AngleAxis_TestApp testApp( application, ANGLE_AXIS_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliAngleAxisConstructorP2
 * @since_tizen   2.4
 * @description   check if Constructor api works or not.
 */

int UtcDaliAngleAxisConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AngleAxis_TestApp testApp( application, ANGLE_AXIS_CONSTRUCTOR_DEGREE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliAngleAxisConstructorP3
 * @since_tizen   2.4
 * @description   check if Constructor3 api works or not.
 */

int UtcDaliAngleAxisConstructorP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AngleAxis_TestApp testApp(application, ANGLE_AXIS_CONSTRUCTOR_RADIAN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliAngleAxisEqualP
 * @since_tizen   2.4
 * @description   Compare two angle axis for equality.
 */

int UtcDaliAngleAxisEqualP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AngleAxis_TestApp testApp(application, ANGLE_AXIS_EQUAL_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliAngleAxisOutputStreamOpeatorP
 * @since_tizen   2.4
 * @description   To Check angleaxis outstream operator is working properly or not.
 */

int UtcDaliAngleAxisOutputStreamOpeatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AngleAxis_TestApp testApp(application, ANGLE_AXIS_OUTPUT_STREAM_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}
