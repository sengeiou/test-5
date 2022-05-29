#include "utc-dali-quaternion-impl.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Quaternion_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Quaternion_startup(void)
{
  test_return_value=0;
  gRenderCountQuaternion=0;
}

/**
 * @function            utc_Dali_Quaternion_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Quaternion_cleanup(void)
{

}


namespace
{
  enum TEST_CASES_LIST_QUATERNION
  {
    QUATERNION_BY_FLOAT,
    QUATERNION_BY_VECTOR,
    QUATERNION_BY_ANGLE_VECTOR4_AXIS,
    QUATERNION_BY_EULER_ANGLES,
    QUATERNION_AS_VECTOR,
    QUATERNION_CONSTRUCTOR_BY_MATRIX,
    QUATERNION_CONSTRUCTOR_BY_ORTHONORMAL_AXES,
    QUATERNION_CONJUGATE,
    QUATERNION_EULER_ANGLES,
    QUATERNION_EXP,
    QUATERNION_LOG,
    QUATERNION_INVERT,
    QUATERNION_IS_IDENTITY,
    QUATERNION_LENGTH,
    QUATERNION_NORMALIZE_NORMALIZED,
    QUATERNION_LENGTH_SQUARED,
    QUATERNION_OPERATOR_INEQUALITY,
    QUATERNION_OPERATOR_EQUALITY,
    QUATERNION_OPERATOR_MULTIPLICATION_DIVISION,
    QUATERNION_OPERATOR_ADDITION,
    QUATERNION_OPERATOR_MULTIPLICATION_SCALE,
    QUATERNION_OPERATOR_MULTIPLICATION_WITH_ASSIGNMENT,
    QUATERNION_OPERATOR_DIVISION_SCALE,
    QUATERNION_OPERATOR_SCALE_DIV_ASSIGNEMENT,
    QUATERNION_OPERATOR_SET_EULER,
    QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC4,
    QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC3,
    QUATERNION_SUBTRACTION_ADDITION_WITH_ASSIGNMENT_OPERATOR,
    QUATERNION_UNARY_MINUS_OPERATOR,
    QUATERNION_ROTATE_VEC4,
    QUATERNION_ROTATE_VEC3,
    QUATERNION_ANGLE_BETWEEN,
    QUATERNION_DOT,
    QUATERNION_FROM_AXIS_ANGLE,
    QUATERNION_LERP,
    QUATERNION_SLERP,
    QUATERNION_SLERP_NO_INVERT,
    QUATERNION_SQUAD,
    QUATERNION_OPERATOR_MULTIPLICATION_WITH_VECTOR3,
    QUATERNION_BY_ANGLE_VECTOR3_AXIS,
    QUATERNION_BY_TWO_VECTOR3,
    QUATERNION_SUBSTRACT_ASSIGN_OSTREAM_OPERATOR
  };

  struct Quaternion_TestApp : public ConnectionTracker
  {
    Quaternion_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Quaternion_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Quaternion_TestApp::Tick );
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
        case QUATERNION_BY_FLOAT:
          QuaternionByFloat();
          break;

        case QUATERNION_BY_VECTOR:
          QuaternionByVector();
          break;

        case QUATERNION_BY_ANGLE_VECTOR4_AXIS:
          QuaternionByAngleVector4Axis();
          break;

        case QUATERNION_BY_EULER_ANGLES:
          QuaternionByEulerAngles();
          break;

        case QUATERNION_AS_VECTOR:
          QuaternionAsVector();
          break;

        case QUATERNION_CONSTRUCTOR_BY_MATRIX:
          QuaternionConstructorByMatrix();
          break;

        case QUATERNION_CONSTRUCTOR_BY_ORTHONORMAL_AXES:
          QuaternionConstructorByOrthonormalAxes();
          break;

        case QUATERNION_CONJUGATE:
          QuaternionConjugate();
          break;

        case QUATERNION_EULER_ANGLES:
          QuaternionEulerAngles();
          break;

        case QUATERNION_EXP:
          QuaternionExp();
          break;

        case QUATERNION_LOG:
          QuaternionLog();
          break;

        case QUATERNION_INVERT:
          QuaternionInvert();
          break;

        case QUATERNION_IS_IDENTITY:
          QuaternionIsIdentity();
          break;

        case QUATERNION_LENGTH:
          QuaternionLength();
          break;

        case QUATERNION_NORMALIZE_NORMALIZED:
          QuaternionNormalizeNormalized();
          break;

        case QUATERNION_LENGTH_SQUARED:
          QuaternionLengthSquared();
          break;

        case QUATERNION_OPERATOR_INEQUALITY:
          QuaternionOperatorInequality();
          break;

        case QUATERNION_OPERATOR_EQUALITY:
          QuaternionOperatorEquality();
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_DIVISION:
          QuaternionOperatorMultiplicationDivision();
          break;

        case QUATERNION_OPERATOR_ADDITION:
          QuaternionOperatorAddition();
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_SCALE:
          QuaternionOperatorMultiplicationScale();
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_WITH_ASSIGNMENT:
          QuaternionOperatorMultiplicationWithAssignment();
          break;

        case QUATERNION_OPERATOR_DIVISION_SCALE:
          QuaternionOperatorDivisionScale();
          break;

        case QUATERNION_OPERATOR_SCALE_DIV_ASSIGNEMENT:
          QuaternionOperatorScaleDivAssignement();
          break;

        case QUATERNION_OPERATOR_SET_EULER:
          QuaternionOperatorSetEuler();
          break;

        case QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC4:
          QuaternionOperatorToAxisAngleVec4();
          break;

        case QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC3:
          QuaternionOperatorToAxisAngleVec3();
          break;

        case QUATERNION_SUBTRACTION_ADDITION_WITH_ASSIGNMENT_OPERATOR:
          QuaternionSubtractionAdditionWithAssignmentOperator();
          break;

        case QUATERNION_UNARY_MINUS_OPERATOR:
          QuaternionUnaryMinusOperator();
          break;

        case QUATERNION_ROTATE_VEC4:
          QuaternionRotateVec4();
          break;

        case QUATERNION_ROTATE_VEC3:
          QuaternionRotateVec3();
          break;

        case QUATERNION_ANGLE_BETWEEN:
          QuaternionAngleBetween();
          break;

        case QUATERNION_DOT:
          QuaternionDot();
          break;

        case QUATERNION_FROM_AXIS_ANGLE:
          QuaternionFromAxisAngle();
          break;

        case QUATERNION_LERP:
          QuaternionLerp();
          break;

        case QUATERNION_SLERP:
          QuaternionSlerp();
          break;

        case QUATERNION_SLERP_NO_INVERT:
          QuaternionSlerpNoInvert();
          break;

        case QUATERNION_SQUAD:
          QuaternionSquad();
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_WITH_VECTOR3:
          QuaternionOperatorMultiplicationWithVector3();
          break;

        case QUATERNION_BY_ANGLE_VECTOR3_AXIS:
          QuaternionByAngleVector3Axis();
          break;

        case QUATERNION_BY_TWO_VECTOR3:
          QuaternionByTwoVector3();
          break;

        case QUATERNION_SUBSTRACT_ASSIGN_OSTREAM_OPERATOR:
          QuaternionSubstractAssignOStreamOperator();
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case QUATERNION_BY_FLOAT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByFloat001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_BY_VECTOR:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByVector001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_BY_ANGLE_VECTOR4_AXIS:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByAngleVector4Axis001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_BY_EULER_ANGLES:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByEulerAngles001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_AS_VECTOR:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionAsVector001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_CONJUGATE:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionConjugate001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_EULER_ANGLES:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionEulerAngles001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_EXP:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionExp001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_LOG:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionLog001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_INVERT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionInvert001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_LENGTH:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionLength001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_NORMALIZE_NORMALIZED:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionNormalizeNormalized001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_LENGTH_SQUARED:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionLengthSquared001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_INEQUALITY:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorInequality001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_DIVISION:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorMultiplicationDivision001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_ADDITION:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorAddition001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_SCALE:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorMultiplicationScale001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_WITH_ASSIGNMENT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorMultiplicationWithAssignment001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_DIVISION_SCALE:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorDivisionScale001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_SCALE_DIV_ASSIGNEMENT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorScaleDivAssignement001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_SET_EULER:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorSetEuler001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC4:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorToAxisAngleVec4001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC3:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorToAxisAngleVec3001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_SUBTRACTION_ADDITION_WITH_ASSIGNMENT_OPERATOR:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionSubtractionAdditionWithAssignmentOperator001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_UNARY_MINUS_OPERATOR:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionUnaryMinusOperator001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_ROTATE_VEC4:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionRotateVec4001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_ROTATE_VEC3:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionRotateVec3001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_ANGLE_BETWEEN:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionAngleBetween001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_DOT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionDot001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_FROM_AXIS_ANGLE:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionFromAxisAngle001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_LERP:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionLerp001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_SLERP:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionSlerp001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_SLERP_NO_INVERT:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionSlerpNoInvert001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_SQUAD:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionSquad001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_OPERATOR_MULTIPLICATION_WITH_VECTOR3:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionOperatorMultiplicationWithVector3001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case QUATERNION_BY_ANGLE_VECTOR3_AXIS:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByAngleVector3Axis001();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }

          break;

        case QUATERNION_BY_TWO_VECTOR3:
          switch (gRenderCountQuaternion)
          {
            case 0:
              VTQuaternionByTwoVector3001();
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
 * @testcase         UtcDaliQuaternionByFloatP
 * @since_tizen      2.4
 * @description      Construct a quaternion instance represented by floats
 */
int UtcDaliQuaternionByFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_FLOAT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionByVectorP
 * @since_tizen      2.4
 * @description      Construct from a quaternion represented by a vector
 */
int UtcDaliQuaternionByVectorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_VECTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionByAngleVector4AxisP
 * @since_tizen      2.4
 * @description      Retrieve the Quaternion instance initialized by Angle and Vector4 Axis type parameters
 */
int UtcDaliQuaternionByAngleVector4AxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_ANGLE_VECTOR4_AXIS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionByEulerAnglesP
 * @since_tizen      2.4
 * @description      Constructor from three Eular Angles
 */
int UtcDaliQuaternionByEulerAnglesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_EULER_ANGLES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionAsVectorP
 * @since_tizen      2.4
 * @description      Return the quaternion as a vector
 */
int UtcDaliQuaternionAsVectorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_AS_VECTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionConstructorByMatrixP
 * @since_tizen      2.4
 * @description      Constructor from matrix object
 */
int UtcDaliQuaternionConstructorByMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_CONSTRUCTOR_BY_MATRIX);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionConstructorByOrthonormalAxesP
 * @since_tizen      2.4
 * @description      Retrieve the Quaternion instance using three Orthonormal axes
 */
int UtcDaliQuaternionConstructorByOrthonormalAxesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_CONSTRUCTOR_BY_ORTHONORMAL_AXES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionConjugateP
 * @since_tizen      2.4
 * @description      Conjugate the instance of quaternion
 */
int UtcDaliQuaternionConjugateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_CONJUGATE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionEulerAnglesP
 * @since_tizen      2.4
 * @description      Get the three Euler Angles from the quaternion instance
 */
int UtcDaliQuaternionEulerAnglesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_EULER_ANGLES);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionExpP
 * @since_tizen      2.4
 * @description      Performs an exponent e^Quaternion
 */
int UtcDaliQuaternionExpP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_EXP);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionLogP
 * @since_tizen      2.4
 * @description      Performs an logarithm Log(Quaternion)
 */
int UtcDaliQuaternionLogP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_LOG);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionInvertP
 * @since_tizen      2.4
 * @description      Perform an Invert() operation on the Quaternion instance
 */
int UtcDaliQuaternionInvertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_INVERT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionIsIdentityP
 * @since_tizen      2.4
 * @description      Check if this is an identity quaternion
 */
int UtcDaliQuaternionIsIdentityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_IS_IDENTITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionLengthP
 * @since_tizen      2.4
 * @description      Calculate the length of a quaternion instance
 */
int UtcDaliQuaternionLengthP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_LENGTH);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionNormalizeNormalizedP
 * @since_tizen      2.4
 * @description      Normalize quaternion instance to unit length and get the return quaternion
 */
int UtcDaliQuaternionNormalizeNormalizedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_NORMALIZE_NORMALIZED);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionLengthSquaredP
 * @since_tizen      2.4
 * @description      Return the squared length of the quaternion
 */
int UtcDaliQuaternionLengthSquaredP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_LENGTH_SQUARED);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorInequalityP
 * @since_tizen      2.4
 * @description      Check the inequality of two Quaternion instance
 */
int UtcDaliQuaternionOperatorInequalityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_INEQUALITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorEqualityP
 * @since_tizen      2.4
 * @description      Check the equality of two Quaternion instance
 */
int UtcDaliQuaternionOperatorEqualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_EQUALITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorMultiplicationDivisionP
 * @since_tizen      2.4
 * @description      Multiplication and Division operator
 */
int UtcDaliQuaternionOperatorMultiplicationDivisionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_MULTIPLICATION_DIVISION);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorAdditionP
 * @since_tizen      2.4
 * @description      Addition operator operation
 */
int UtcDaliQuaternionOperatorAdditionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_ADDITION);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorMultiplicationScaleP
 * @since_tizen      2.4
 * @description      Scaling a quaternion instance by a float value
 */
int UtcDaliQuaternionOperatorMultiplicationScaleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_MULTIPLICATION_SCALE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorMultiplicationWithAssignmentP
 * @since_tizen      2.4
 * @description      Multiplication with assignment operator
 */
int UtcDaliQuaternionOperatorMultiplicationWithAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_MULTIPLICATION_WITH_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorDivisionScaleP
 * @since_tizen      2.4
 * @description      Scaling a quaternion instance by a float value
 */
int UtcDaliQuaternionOperatorDivisionScaleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_DIVISION_SCALE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorScaleDivAssignementP
 * @since_tizen      2.4
 * @description      Scale division with assignment operator
 */
int UtcDaliQuaternionOperatorScaleDivAssignementP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_SCALE_DIV_ASSIGNEMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorScaleDivAssignementP
 * @since_tizen      2.4
 * @description      Set the Eular angles of the quaternion
 */
int UtcDaliQuaternionOperatorSetEulerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_SET_EULER);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorToAxisAngleVec4P
 * @since_tizen      2.4
 * @description      Convert the quaternion to an axis angle pair
 */
int UtcDaliQuaternionOperatorToAxisAngleVec4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorScaleDivAssignementP
 * @since_tizen      2.4
 * @description      Convert the quaternion to an axis angle pair
 */
int UtcDaliQuaternionOperatorToAxisAngleVec3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_TO_AXIS_ANGLE_VEC3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionSubtractionAdditionWithAssignmentOperatorP
 * @since_tizen      2.4
 * @description      Subtraction and Addition with assignment operator
 */
int UtcDaliQuaternionSubtractionAdditionWithAssignmentOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_SUBTRACTION_ADDITION_WITH_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionUnaryMinusOperatorP
 * @since_tizen      2.4
 * @description      To use of Unary minus operator
 */
int UtcDaliQuaternionUnaryMinusOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_UNARY_MINUS_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionRotateVec4P
 * @since_tizen      2.4
 * @description      To Rotate the Vector4  with respect to quaternion
 */
int UtcDaliQuaternionRotateVec4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_ROTATE_VEC4);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionRotateVec3P
 * @since_tizen      2.4
 * @description      To Rotate the Vector3  with respect to quaternion
 */
int UtcDaliQuaternionRotateVec3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_ROTATE_VEC3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionAngleBetweenP
 * @since_tizen      2.4
 * @description      To get the minimum angle between two quaternion
 */
int UtcDaliQuaternionAngleBetweenP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_ANGLE_BETWEEN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionDotP
 * @since_tizen      2.4
 * @description      Get the Dot production between two quaternions
 */
int UtcDaliQuaternionDotP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_DOT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionFromAxisAngleP
 * @since_tizen      2.4
 * @description      Create quaternion instance using vector4 type axis and float angle
 */
int UtcDaliQuaternionFromAxisAngleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_FROM_AXIS_ANGLE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionLerp
 * @since_tizen      2.4
 * @description      Get the linear interpolation of two quaternion and a static distance
 */
int UtcDaliQuaternionLerpP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_LERP);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionSlerpP
 * @since_tizen      2.4
 * @description      Get the linear interpolation of two quaternion and a static distance
 */
int UtcDaliQuaternionSlerpP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_SLERP);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionSlerpNoInvertP
 * @since_tizen      2.4
 * @description      This version of Slerp used by Squad, does not check for theta is greater than 90
 */
int UtcDaliQuaternionSlerpNoInvertP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_SLERP_NO_INVERT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionSquadP
 * @since_tizen      2.4
 * @description      Get the spherical cubic interpolations
 */
int UtcDaliQuaternionSquadP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_SQUAD);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionOperatorMultiplicationWithVector3P
 * @since_tizen      2.4
 * @description      Multiplication  with Vector3 object
 */
int UtcDaliQuaternionOperatorMultiplicationWithVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_OPERATOR_MULTIPLICATION_WITH_VECTOR3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionByAngleVector3AxisP
 * @since_tizen      2.4
 * @description      Constructor from an Vector3 axis and angle
 */
int UtcDaliQuaternionByAngleVector3AxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_ANGLE_VECTOR3_AXIS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionByTwoVector3P
 * @since_tizen      2.4
 * @description      Construct a Quaternion instance using two Vector3 instances
 */
int UtcDaliQuaternionByTwoVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_BY_TWO_VECTOR3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliQuaternionSubstractAssignOStreamOperatorP
 * @since_tizen      2.4
 * @description      Substract and Assign a Quaternion and print properly
 */
int UtcDaliQuaternionSubstractAssignOStreamOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Quaternion_TestApp testApp( application, QUATERNION_SUBSTRACT_ASSIGN_OSTREAM_OPERATOR);
  application.MainLoop();
  return test_return_value;
}
