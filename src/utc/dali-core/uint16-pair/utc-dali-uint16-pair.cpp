#include "utc-dali-uint16-pair-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Uint16Pair

/**
 * @function      utc_Dali_Uint16Pair_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Uint16Pair_startup(void)
{
  test_return_value = 0;
}

/**
 * @function      utc_Dali_Uint16Pair_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_Uint16Pair_cleanup(void)
{

}

void Uint16PairFromFloatVec2P();
void Uint16PairFromFloatArrayP();
void Uint16PairGetHeightP();
void Uint16PairGetWidthP();
void Uint16PairOperatorGreaterThanP();
void Uint16PairOperatorLessThanP();
void Uint16PairOperatorEqualsP();
void Uint16PairOperatorNotEqualsP();
void Uint16PairOperatorAssignmentP();
void Uint16PairConstructorP();
void Uint16PairConstructorP2();
void Uint16PairCopyConstructorP();
void Uint16PairGetXP();
void Uint16PairGetYP();
void Uint16PairSetXP();
void Uint16PairSetYP();
void Uint16PairSetHeightP();
void Uint16PairSetWidthP();

namespace
{
  enum TEST_CASES_LIST_UINT16_PAIR
  {
    UINT16_PAIR_FROM_FLOAT_VEC2_P,
    UINT16_PAIR_FROM_FLOAT_ARRAY_P,
    UINT16_PAIR_FROM_GET_HEIGHT_P,
    UINT16_PAIR_FROM_GET_WIDTH_P,
    UINT16_PAIR_FROM_OPERATION_GREATER_THAN_P,
    UINT16_PAIR_FROM_OPERATION_LESS_THAN_P,
    UINT16_PAIR_FROM_OPERATOR_EQUALS_P,
    UINT16_PAIR_FROM_OPERATOR_NOT_EQUALS_P,
    UINT16_PAIR_FROM_OPERATOR_ASSIGNMENT_P,
    UINT16_PAIR_FROM_CONSTRUCTOR_P,
    UINT16_PAIR_FROM_CONSTRUCTOR_P2,
    UINT16_PAIR_FROM_COPY_CONSTRUCTOR_P,
    UINT16_PAIR_FROM_GET_X_P,
    UINT16_PAIR_FROM_GET_Y_P,
    UINT16_PAIR_FROM_SET_X_P,
    UINT16_PAIR_FROM_SET_Y_P,
    UINT16_PAIR_FROM_SET_HEIGHT_P,
    UINT16_PAIR_FROM_SET_WIDTH_P
  };

  struct Unit16Pair_TestApp : public ConnectionTracker
  {
    Unit16Pair_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Unit16Pair_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Unit16Pair_TestApp::Tick );
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
        case UINT16_PAIR_FROM_FLOAT_VEC2_P:
          Uint16PairFromFloatVec2P();
          break;

        case UINT16_PAIR_FROM_FLOAT_ARRAY_P:
          Uint16PairFromFloatArrayP();
          break;

        case UINT16_PAIR_FROM_GET_HEIGHT_P:
          Uint16PairGetHeightP();
          break;

        case UINT16_PAIR_FROM_GET_WIDTH_P:
          Uint16PairGetWidthP();
          break;

        case UINT16_PAIR_FROM_OPERATION_GREATER_THAN_P:
          Uint16PairOperatorGreaterThanP();
          break;

        case UINT16_PAIR_FROM_OPERATION_LESS_THAN_P:
          Uint16PairOperatorLessThanP();
          break;

        case UINT16_PAIR_FROM_OPERATOR_EQUALS_P:
          Uint16PairOperatorEqualsP();
          break;

        case UINT16_PAIR_FROM_OPERATOR_NOT_EQUALS_P:
          Uint16PairOperatorNotEqualsP();

        case UINT16_PAIR_FROM_CONSTRUCTOR_P:
          Uint16PairConstructorP();
          break;

        case UINT16_PAIR_FROM_CONSTRUCTOR_P2:
          Uint16PairConstructorP2();
          break;

        case UINT16_PAIR_FROM_COPY_CONSTRUCTOR_P:
          Uint16PairCopyConstructorP();
          break;

        case UINT16_PAIR_FROM_GET_X_P:
          Uint16PairGetXP();
          break;

        case UINT16_PAIR_FROM_GET_Y_P:
          Uint16PairGetYP();
          break;

        case UINT16_PAIR_FROM_SET_X_P:
          Uint16PairSetXP();
          break;

        case UINT16_PAIR_FROM_SET_Y_P:
          Uint16PairSetYP();

        case UINT16_PAIR_FROM_SET_HEIGHT_P:
          Uint16PairSetHeightP();
          break;

        case UINT16_PAIR_FROM_SET_WIDTH_P:
          Uint16PairSetWidthP();
          break;

        case UINT16_PAIR_FROM_OPERATOR_ASSIGNMENT_P:
          Uint16PairOperatorAssignmentP();
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

void Uint16PairOperatorAssignmentP()
{
  Uint16Pair unitPair1;
  Uint16Pair unitPair2;

  unitPair1 = Uint16Pair(5,5);
  unitPair2 = unitPair1;

  DALI_CHECK_FAIL( unitPair1 != unitPair2 ,"Assignment operator is failed.");

  DaliLog::PrintPass();
}

void Uint16PairFromFloatVec2P()
{
  Vector2 vec2Input(5.f, 5.f);
  Uint16Pair unitPair = Uint16Pair::FromFloatVec2(vec2Input);

  DALI_CHECK_FAIL( unitPair.GetX() != 5u , "FromFloatVec2 is failed for X dimension.");
  DALI_CHECK_FAIL( unitPair.GetY() != 5u , "FromFloatVec2 is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairFromFloatArrayP()
{
  float array[] = {5.f, 5.f};
  Uint16Pair unitPair = Uint16Pair::FromFloatArray(array);

  DALI_CHECK_FAIL( unitPair.GetX() != 5u , "FromFloatArray is failed for X dimension.");
  DALI_CHECK_FAIL( unitPair.GetY() != 5u , "FromFloatArray is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairGetWidthP()
{
  Uint16Pair unitPair = Uint16Pair(5,5);

  DALI_CHECK_FAIL( unitPair.GetWidth() != 5u , "GetWidth is failed.");
  DALI_CHECK_FAIL( unitPair.GetHeight() != 5u , "GetHeight is failed.");

  DaliLog::PrintPass();
}

void Uint16PairGetHeightP()
{
  Uint16Pair unitPair = Uint16Pair(5,5);

  DALI_CHECK_FAIL( unitPair.GetWidth() != 5u , "GetWidth is failed.");
  DALI_CHECK_FAIL( unitPair.GetHeight() != 5u , "GetHeight is failed.");

  DaliLog::PrintPass();
}

void Uint16PairSetWidthP()
{
  Uint16Pair unitPair = Uint16Pair();

  unitPair.SetWidth(5);
  DALI_CHECK_FAIL( unitPair.GetWidth() != 5u , "SetWidth and GetWidth mismatch.");

  DaliLog::PrintPass();
}

void Uint16PairSetHeightP()
{
  Uint16Pair unitPair = Uint16Pair();

  unitPair.SetHeight(5);
  DALI_CHECK_FAIL( unitPair.GetHeight() != 5u , "SetHeight and GetHeight mismatch.");

  DaliLog::PrintPass();
}

void Uint16PairOperatorGreaterThanP()
{
  Uint16Pair unitPair1;
  Uint16Pair unitPair2;

  unitPair1 = Uint16Pair(5,5);
  unitPair2 = Uint16Pair(6,6);
  DALI_CHECK_FAIL( unitPair1 > unitPair2 ,"Greater than comparison operator is failed.");

  unitPair1 = Uint16Pair(6,6);
  unitPair2 = Uint16Pair(5,5);
  DALI_CHECK_FAIL( unitPair2 > unitPair1 ,"Greater than comparison operator is failed.");

  DaliLog::PrintPass();
}

void Uint16PairOperatorLessThanP()
{
  Uint16Pair unitPair1;
  Uint16Pair unitPair2;

  unitPair1 = Uint16Pair(5,5);
  unitPair2 = Uint16Pair(6,6);
  DALI_CHECK_FAIL( unitPair2 < unitPair1 ,"Less than comparison operator is failed.");

  unitPair1 = Uint16Pair(6,6);
  unitPair2 = Uint16Pair(5,5);
  DALI_CHECK_FAIL( unitPair1 < unitPair2 ,"Less than comparison operator is failed.");

  DaliLog::PrintPass();
}

void Uint16PairOperatorEqualsP()
{
  Uint16Pair unitPair1;
  Uint16Pair unitPair2;

  unitPair1 = Uint16Pair(5,5);
  unitPair2 = Uint16Pair(5,5);

  DALI_CHECK_FAIL( unitPair1 != unitPair2 ,"Equals comparison operator is failed.");

  DaliLog::PrintPass();
}

void Uint16PairOperatorNotEqualsP()
{
  Uint16Pair unitPair1;
  Uint16Pair unitPair2;

  unitPair1 = Uint16Pair(5,4);
  unitPair2 = Uint16Pair(5,5);

  DALI_CHECK_FAIL( unitPair1 == unitPair2 ,"NotEquals comparison operator is failed.");

  DaliLog::PrintPass();
}

void Uint16PairConstructorP()
{
  Uint16Pair v;

  DALI_CHECK_FAIL(v.GetWidth() != 0u, "Constructor is failed for X dimension.");
  DALI_CHECK_FAIL(v.GetHeight() != 0u, "Constructor is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairConstructorP2()
{
  Uint16Pair v(10,10);

  DALI_CHECK_FAIL(v.GetX() != 10u, "Constructor is failed for X dimension.");
  DALI_CHECK_FAIL(v.GetY() != 10u, "Constructor is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairCopyConstructorP()
{
  Uint16Pair unitPair = Uint16Pair(5,5);
  Uint16Pair v = unitPair;

  DALI_CHECK_FAIL(v.GetWidth() != 5u, "Copy Constructor is failed for X dimension.");
  DALI_CHECK_FAIL(v.GetHeight() != 5u, "Copy Constructor is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairGetXP()
{
  Vector2 vec2Input(5.f, 5.f);
  Uint16Pair unitPair = Uint16Pair::FromFloatVec2(vec2Input);

  DALI_CHECK_FAIL(unitPair.GetX() != 5u, "FromFloatVec2 is failed for X dimension.");

  DaliLog::PrintPass();
}

void Uint16PairGetYP()
{
  float array[] = {5.f, 5.f};
  Uint16Pair unitPair = Uint16Pair::FromFloatArray(array);

  DALI_CHECK_FAIL(unitPair.GetY() != 5u, "FromFloatArray is failed for Y dimension.");

  DaliLog::PrintPass();
}

void Uint16PairSetXP()
{
  Uint16Pair unitPair = Uint16Pair();

  unitPair.SetX(5);
  DALI_CHECK_FAIL(unitPair.GetX() != 5u, "SetX and GetX mismatch.");

  DaliLog::PrintPass();
}

void Uint16PairSetYP()
{
  Uint16Pair unitPair = Uint16Pair();

  unitPair.SetY(5);
  DALI_CHECK_FAIL(unitPair.GetY() != 5u, "SetX and GetX mismatch.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase      UtcDaliUint16PairFromFloatVec2P
 * @since_tizen   2.4
 * @description   check if FromFloatVec2 api works or not.
 */
int UtcDaliUint16PairFromFloatVec2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_FLOAT_VEC2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairOperatorAssignmentP
 * @since_tizen   2.4
 * @description   check if Assignment Operator api works or not.
 */
int UtcDaliUint16PairOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairFromFloatArrayP
 * @since_tizen   2.4
 * @description   check if FromFloatArray api works or not.
 */
int UtcDaliUint16PairFromFloatArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_FLOAT_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairGetHeightP
 * @since_tizen   2.4
 * @description   check if GetHeight api works or not.
 */
int UtcDaliUint16PairGetHeightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_GET_HEIGHT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairGetWidthP
 * @since_tizen   2.4
 * @description   check if GetWidth api works or not.
 */
int UtcDaliUint16PairGetWidthP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_GET_WIDTH_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairiSetHeightP
 * @since_tizen   2.4
 * @description   check if SetHeight api works or not.
 */
int UtcDaliUint16PairSetHeightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_SET_HEIGHT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairSetWidthP
 * @since_tizen   2.4
 * @description   check if SetWidth api works or not.
 */
int UtcDaliUint16PairSetWidthP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_SET_WIDTH_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairiSetYP
 * @since_tizen   2.4
 * @description   check if SetY api works or not.
 */
int UtcDaliUint16PairSetYP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_SET_Y_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairSetXP
 * @since_tizen   2.4
 * @description   check if SetX api works or not.
 */
int UtcDaliUint16PairSetXP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_SET_X_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairOperatorGreaterThanP
 * @since_tizen   2.4
 * @description   check if OperatorGreaterThan api works or not.
 */
int UtcDaliUint16PairOperatorGreaterThanP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_OPERATION_GREATER_THAN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairOperatorLessThanP
 * @since_tizen   2.4
 * @description   check if OperatorLessThan api works or not.
 */
int UtcDaliUint16PairOperatorLessThanP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_OPERATION_LESS_THAN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairOperatorEqualsP
 * @since_tizen   2.4
 * @description   check if OperatorEquals api works or not.
 */
int UtcDaliUint16PairOperatorEqualsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_OPERATOR_EQUALS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairOperatorNotEqualsP
 * @since_tizen   2.4
 * @description   check if OperatorNotEquals api works or not.
 */
int UtcDaliUint16PairOperatorNotEqualsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_OPERATOR_NOT_EQUALS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairConstructorP
 * @since_tizen   2.4
 * @description   check if Constructor api works or not.
 */
int UtcDaliUint16PairConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairConstructorP2
 * @since_tizen   2.4
 * @description   check if Constructor api works or not.
 */
int UtcDaliUint16PairConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairCopyConstructorP
 * @since_tizen   2.4
 * @description   check if CopyConstructor api works or not.
 */
int UtcDaliUint16PairCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairGetXP
 * @since_tizen   2.4
 * @description   check if GetX api works or not.
 */
int UtcDaliUint16PairGetXP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_GET_X_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliUint16PairGetYP
 * @since_tizen   2.4
 * @description   check if GetY api works or not.
 */
int UtcDaliUint16PairGetYP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Unit16Pair_TestApp testApp( application, UINT16_PAIR_FROM_GET_Y_P);
  application.MainLoop();
  return test_return_value;
}
