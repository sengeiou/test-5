#include "utc-dali-extents-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Extents
/**
 * @function      utc_Dali_Extents_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Extents_startup(void)
{
  test_return_value=0;
}

/**
 * @function      utc_Dali_Extents_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Extents_cleanup(void)
{
}

void ExtentsConstructorP();
void ExtentsConstructorP2();
void ExtentsCopyConstructorP();
void ExtentsCopyOperatorAssignmentP();
void ExtentsOperatorAssignmentP();
void ExtentsOperatorEqualityP();
void ExtentsOperatorInequalityP();
void ExtentsOperatorEqualsOStreamP();

namespace
{
  enum TEST_CASES_LIST_EXTENTS
  {
    EXTENTS_CONSTRUCTOR_P,
    EXTENTS_CONSTRUCTOR_P2,
    EXTENTS_COPY_CONSTRUCTOR_P,
    EXTENTS_COPY_OPERATOR_ASSIGNMENT_P,
    EXTENTS_OPERATOR_ASSIGNMENT_P,
    EXTENTS_OPERATOR_EQUALITY_P,
    EXTENTS_OPERATOR_INEQUALITY_P,
    EXTENTS_OPERATOR_EQUALS_OSTREAM_P
  };

  struct Extents_TestApp : public ConnectionTracker
  {
    Extents_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Extents_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Extents_TestApp::Tick );
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
        case EXTENTS_CONSTRUCTOR_P:
          ExtentsConstructorP();
          break;

        case EXTENTS_CONSTRUCTOR_P2:
          ExtentsConstructorP2();
          break;

        case EXTENTS_COPY_CONSTRUCTOR_P:
          ExtentsCopyConstructorP();
          break;

        case EXTENTS_COPY_OPERATOR_ASSIGNMENT_P:
          ExtentsCopyOperatorAssignmentP();
          break;

        case EXTENTS_OPERATOR_ASSIGNMENT_P:
          ExtentsOperatorAssignmentP();
          break;

        case EXTENTS_OPERATOR_EQUALITY_P:
          ExtentsOperatorEqualityP();
          break;

        case EXTENTS_OPERATOR_INEQUALITY_P:
          ExtentsOperatorInequalityP();
          break;

        case EXTENTS_OPERATOR_EQUALS_OSTREAM_P:
          ExtentsOperatorEqualsOStreamP();
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
void ExtentsConstructorP()
{
  Extents extent;
  DALI_CHECK_FAIL( extent.start != 0u, "Dali::Extents Constructor is Failed." );
  DALI_CHECK_FAIL( extent.end != 0u, "Dali::Extents Constructor is Failed." );
  DALI_CHECK_FAIL( extent.top != 0u, "Dali::Extents Constructor is Failed." );
  DALI_CHECK_FAIL( extent.bottom != 0u, "Dali::Extents Constructor is Failed." );

  DaliLog::PrintPass();
}

void ExtentsConstructorP2()
{
  Extents extent( 10u, 20u, 400u, 200u );
  DALI_CHECK_FAIL( extent.start != 10u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent.end != 20u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent.top != 400u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent.bottom != 200u, "Dali::Extents Copy Constructor is Failed." );

  DaliLog::PrintPass();
}

void ExtentsCopyConstructorP()
{
  Extents extent( 10u, 20u, 400u, 200u );
  Extents extent2( extent );

  DALI_CHECK_FAIL( extent2.start != 10u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent2.end != 20u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent2.top != 400u, "Dali::Extents Copy Constructor is Failed." );
  DALI_CHECK_FAIL( extent2.bottom != 200u, "Dali::Extents Copy Constructor is Failed." );

  DaliLog::PrintPass();
}

void ExtentsCopyOperatorAssignmentP()
{
  Extents extent;

  Extents extent2( 1u, 2u, 3u, 4u );
  extent = extent2;

  DALI_CHECK_FAIL( extent.start != 1u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.end != 2u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.top != 3u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.bottom != 4u, "Dali::Extents Assignment Operator is Failed." );

  DaliLog::PrintPass();
}

void ExtentsOperatorAssignmentP()
{
  Extents extent;
  const uint16_t array[] = { 1u, 2u, 3u, 4u };
  extent = (const uint16_t*)array;

  DALI_CHECK_FAIL( extent.start != 1u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.end != 2u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.top != 3u, "Dali::Extents Assignment Operator is Failed." );
  DALI_CHECK_FAIL( extent.bottom != 4u, "Dali::Extents Assignment Operator is Failed." );

  DaliLog::PrintPass();
}

void ExtentsOperatorEqualityP()
{
  Extents extent1( 10u, 20u, 200u, 200u );
  Extents extent1p( 10u, 20u, 200u, 200u );

  Extents extent2( 10u, 120u, 200u, 200u );
  Extents extent3( 10u, 80u, 200u, 200u );

  DALI_CHECK_FAIL( !( extent1 == extent1p ), "Dali::Extents Equality Operator is Failed." );
  DALI_CHECK_FAIL( !( extent1 == extent1 ), "Dali::Extents Equality Operator is Failed." );
  DALI_CHECK_FAIL( extent1 == extent2, "Dali::Extents Equality Operator is Failed." );
  DALI_CHECK_FAIL( extent1 == extent3, "Dali::Extents Equality Operator is Failed." );

  DaliLog::PrintPass();
}

void ExtentsOperatorInequalityP()
{
  Extents extent1( 10u, 20u, 200u, 200u );
  Extents extent2( 10u, 120u, 200u, 200u );
  Extents extent3( 10u, 80u, 200u, 200u );

  DALI_CHECK_FAIL( extent1 == extent2, "Dali::Extents Inequality Operator is Failed." );
  DALI_CHECK_FAIL( extent1 == extent3, "Dali::Extents Inequality Operator is Failed." );

  DaliLog::PrintPass();
}

void ExtentsOperatorEqualsOStreamP()
{
  std::ostringstream oss;

  Extents extent( 1u, 2u, 10u, 10u );

  oss << extent;

  std::string expectedOutput = "[1, 2, 10, 10]";

  DALI_CHECK_FAIL( oss.str() != expectedOutput, "Dali::Extents Equals Ostream Operator is Failed." );

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase      UtcDaliExtentsConstructorP
 * @since_tizen   4.0
 * @description   check if Extents constructor works properly or not.
 */
int UtcDaliExtentsConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_CONSTRUCTOR_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsConstructorP2
 * @since_tizen   4.0
 * @description   check if Extents copy constructor works properly or not.
 */
int UtcDaliExtentsConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_CONSTRUCTOR_P2 );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsCopyConstructorP
 * @since_tizen   4.0
 * @description   check if Extents copy constructor works properly or not.
 */
int UtcDaliExtentsCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_COPY_CONSTRUCTOR_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsCopyOperatorAssignmentP
 * @since_tizen   4.0
 * @description   check if Extents copy assignment operator works properly or not.
 */
int UtcDaliExtentsCopyOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_COPY_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsOperatorAssignmentP
 * @since_tizen   4.0
 * @description   check if Extents assignment operator works properly or not.
 */
int UtcDaliExtentsOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsOperatorEqualityP
 * @since_tizen   4.0
 * @description   check if Extents equality operator works properly or not.
 */
int UtcDaliExtentsOperatorEqualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_OPERATOR_EQUALITY_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsOperatorInequalityP
 * @since_tizen   4.0
 * @description   check if Extents inequality operator works properly or not.
 */
int UtcDaliExtentsOperatorInequalityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_OPERATOR_INEQUALITY_P );
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase      UtcDaliExtentsOperatorEqualsOStreamP
 * @since_tizen   4.0
 * @description   check if Extents ostream operator works properly or not.
 */
int UtcDaliExtentsOperatorEqualsOStreamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Extents_TestApp testApp( application, EXTENTS_OPERATOR_EQUALS_OSTREAM_P );
  application.MainLoop();
  return test_return_value;
}
