#include "utc-dali-vector2-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Vector2
/**
 * @function            utc_Dali_Vector2_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Vector2_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Vector2_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Vector2_cleanup(void)
{

}

void Vector2ConstructorP();
void Vector2ConstrucAndGetAsFloatP();
void Vector2ConstructArrayAndGetAsConstFloatP();
void Vector2Vec3ConstructAndAssignP();
void Vector2Vec4ConstructAndAssignP();
void Vector2ClampP();
void Vector2OperatorInequalityP();
void Vector2OperatorMultiplicationAndAssignmentP();
void Vector2OperatorAdditionAndAssignmentP();
void Vector2OperatorSubtractionAndAssignmentP();
void Vector2OperatorUnaryNegationP();
void Vector2OperatorDivisionAndAssignmentP();
void Vector2OperatorFloatAssignmentP();
void Vector2OperatorEqualityP();
void Vector2OperatorSubscriptP();
void Vector2NormalizeWithLengthAndLengthSquaredP();
void Vector2MinP();
void Vector2MaxP();

namespace
{
  enum TEST_CASES_LIST_VECTOR2
  {
    VECTOR2_CONSTRUCTOR_P,
    VECTOR2_CONSTRUCT_GET_AS_FLOAT_P,
    VECTOR2_CONSTRUCT_GET_AS_CONST_FLOAT_P,
    VECTOR2_VEC3_CONSTRUCT_AND_ASSIGN_P,
    VECTOR2_VEC4_CONSTRUCT_AND_ASSIGN_P,
    VECTOR2_CLAMP_P,
    VECTOR2_OPERATOR_INEQUALITY_P,
    VECTOR2_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P,
    VECTOR2_OPERATOR_ADDITION_AND_ASSIGNMENT_P,
    VECTOR2_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P,
    VECTOR2_OPERATOR_UNARY_NEGATION_P,
    VECTOR2_OPERATOR_DIVISION_AND_ASSIGNMENT_P,
    VECTOR2_OPERATOR_FLOAT_ASSIGNMENT_P,
    VECTOR2_OPERATOR_EQUALITY_P,
    VECTOR2_OPERATOR_SUBSCRIPT_P,
    VECTOR2_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P,
    VECTOR2_MIN_P,
    VECTOR2_MAX_P
  };

  struct Vector2_TestApp : public ConnectionTracker
  {
    Vector2_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Vector2_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Vector2_TestApp::Tick );
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
        case VECTOR2_CONSTRUCTOR_P:
          Vector2ConstructorP();
          break;
        case VECTOR2_CONSTRUCT_GET_AS_FLOAT_P:
          Vector2ConstrucAndGetAsFloatP();
          break;
        case VECTOR2_CONSTRUCT_GET_AS_CONST_FLOAT_P:
          Vector2ConstructArrayAndGetAsConstFloatP();
          break;
        case VECTOR2_VEC3_CONSTRUCT_AND_ASSIGN_P:
          Vector2Vec3ConstructAndAssignP();
          break;
        case VECTOR2_VEC4_CONSTRUCT_AND_ASSIGN_P:
          Vector2Vec4ConstructAndAssignP();
          break;
        case VECTOR2_CLAMP_P:
          Vector2ClampP();
          break;
        case VECTOR2_OPERATOR_INEQUALITY_P:
          Vector2OperatorInequalityP();
          break;
        case VECTOR2_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P:
          Vector2OperatorMultiplicationAndAssignmentP();
          break;
        case VECTOR2_OPERATOR_ADDITION_AND_ASSIGNMENT_P:
          Vector2OperatorAdditionAndAssignmentP();
          break;
        case VECTOR2_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P:
          Vector2OperatorSubtractionAndAssignmentP();
          break;
        case VECTOR2_OPERATOR_UNARY_NEGATION_P:
          Vector2OperatorUnaryNegationP();
          break;
        case VECTOR2_OPERATOR_DIVISION_AND_ASSIGNMENT_P:
          Vector2OperatorDivisionAndAssignmentP();
          break;
        case VECTOR2_OPERATOR_FLOAT_ASSIGNMENT_P:
          Vector2OperatorFloatAssignmentP();
          break;
        case VECTOR2_OPERATOR_EQUALITY_P:
          Vector2OperatorEqualityP();
          break;
        case VECTOR2_OPERATOR_SUBSCRIPT_P:
          Vector2OperatorSubscriptP();
          break;
        case VECTOR2_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P:
          Vector2NormalizeWithLengthAndLengthSquaredP();
          break;
        case VECTOR2_MIN_P:
          Vector2MinP();
          break;
        case VECTOR2_MAX_P:
          Vector2MaxP();
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

void Vector2ConstructorP()
{
  float fVecX = 0.0f, fVecY = 0.0f;

  Vector2 vec2;
  DALI_CHECK_FAIL( ( vec2.x != fVecX ) || ( vec2.y != fVecY ) , "Vector2 api is failed to create constructor with given float value.");

  DaliLog::PrintPass();
}

void Vector2ConstrucAndGetAsFloatP()
{
  float fVecX = 0.0f, fVecY = 2.0f;
  float *rgfpValue = NULL;

  Vector2 vec2( fVecX, fVecY );

  DALI_CHECK_FAIL( ( vec2.x != fVecX ) || ( vec2.y != fVecY ) , "Vector2 api is failed to create constructor with given float value.");

  rgfpValue = vec2.AsFloat();

  DALI_CHECK_FAIL((vec2.x != rgfpValue[0]) || (vec2.y != rgfpValue[1]) , "AsFloat is failed to retrieve value of Vector2 as an array.");

  DaliLog::PrintPass();
}

void Vector2ConstructArrayAndGetAsConstFloatP()
{
  float rgfValues[] = {0.0f, 1.0f};

  const Vector2 vec2( rgfValues );

  DALI_CHECK_FAIL( ( vec2.x != rgfValues[0] ) || ( vec2.y != rgfValues[1] ) , "Vector2 api is failed create constructor with given value.");

  const float *rgfpValue = vec2.AsFloat();

  DALI_CHECK_FAIL( ( vec2.x != rgfpValue[0] ) || ( vec2.y != rgfpValue[1] ) , "AsFloat()const api is failed to retrieve values of Vector2 as an array of 2 float values.");

  DaliLog::PrintPass();
}

void Vector2Vec3ConstructAndAssignP()
{
  float fValX = 1.0f, fValY  = 2.0f, fValZ  = 3.0f;

  Vector3 vec3( fValX, fValY, fValZ );
  Vector2 vec2Construct( vec3 );

  DALI_CHECK_FAIL( ( vec2Construct.width != vec3.x ) || ( vec2Construct.height != vec3.y ) , "Vector2 api is failed to create constructor with given value.");

  Vector2 vec2Assign;
  vec2Assign = vec3;

  DALI_CHECK_FAIL( ( vec2Assign.width != vec3.x ) || ( vec2Assign.height != vec3.y ) , "Assignment operator failed to assign Vector3 values to Vector2.");
  DALI_CHECK_FAIL( vec2Assign != vec2Construct, "Constructed and assigned Vector2 with same Vector3 must be same.");

  DaliLog::PrintPass();
}

void Vector2Vec4ConstructAndAssignP()
{
  float fValX = 1.0f, fValY  = 2.0f, fValZ  = 3.0f, fValW = 4.0f;

  Vector4 vec4( fValX, fValY, fValZ, fValW );

  Vector2 vec2Construct( vec4 );

  DALI_CHECK_FAIL( ( vec2Construct.width != vec4.x ) || ( vec2Construct.height != vec4.y ) , "Vector2 api is failed to create constructor with given value.");

  Vector2 vec2Assign( 0.0f, 0.0f );
  vec2Assign = vec4;

  DALI_CHECK_FAIL( ( vec2Assign.width != vec4.x ) || ( vec2Assign.height != vec4.y ) , "Assignment operator failed to assign Vector4 values to Vector2");
  DALI_CHECK_FAIL( vec2Assign != vec2Construct, "Constructed and assigned Vector2 with same Vector4 values must be same.");

  DaliLog::PrintPass();
}

void Vector2ClampP()
{
  Vector2 vec2Values( 11.0f, 2.0f );
  Vector2 vec2Min( 1.0f, 3.0f );
  Vector2 vec2Max( 10.0f, 13.0f );
  Vector2 vec2ClamResult( 10.0f, 3.0f );

  vec2Values.Clamp( vec2Min, vec2Max );

  DALI_CHECK_FAIL( vec2ClamResult != vec2Values , "Clamp is failed to Clamp the vector between minimum and maximum vectors.");

  DaliLog::PrintPass();
}

void Vector2OperatorInequalityP()
{
  Vector2 vec2Values1( 11.0f, 2.0f );
  Vector2 vec2Values2( 11.0f, 1.0f );
  bool bInequal = false;

  bInequal = ( vec2Values1 != vec2Values2 );

  DALI_CHECK_FAIL( !bInequal , "operator!= Api failed to check inequality of to Vector2.");

  DaliLog::PrintPass();
}

void Vector2OperatorMultiplicationAndAssignmentP()
{
  Vector2 vec2Values1( 2.0f, 2.0f );
  Vector2 vec2Values2( 3.0f, 1.0f );
  Vector2 vec2Result( 6.0f, 2.0f );
  Vector2 vec2GetResult;
  vec2GetResult = vec2Values1 * vec2Values2;
  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator* Api failed multiply two vector.");

  float fScaleVal = 3.0f;
  vec2Result = Vector2( 6.0f, 6.0f );
  vec2GetResult = vec2Values1 * fScaleVal;
  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator* Api failed to multiply a vector with a float value.");

  vec2Result = Vector2( 6.0f, 2.0f );
  vec2Values1 *= vec2Values2;
  DALI_CHECK_FAIL( vec2Values1 != vec2Result , "Api failed to multiply two vector and failed to assign the product to left hand side.");

  vec2Values1 = Vector2( 2.0f, 2.0f );
  vec2Result = Vector2( 6.0f, 6.0f );
  vec2Values1 *= fScaleVal;
  DALI_CHECK_FAIL( vec2Values1 != vec2Result , "operator*= Api failed to multiply a vector with a float value and assign the product to left hand side.");

  DaliLog::PrintPass();
}

void Vector2OperatorAdditionAndAssignmentP()
{
  Vector2 vec2Values1( 2.0f, 2.0f );
  Vector2 vec2Values2( 4.0f, 3.0f );
  Vector2 vec2Result( 6.0f, 5.0f );
  Vector2 vec2GetResult;

  vec2GetResult = vec2Values1 + vec2Values2;

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator+ Api failed to add two vector.");

  vec2Values1 += vec2Values2;

  DALI_CHECK_FAIL( vec2Values1 != vec2Result , "operator+= Api failed to add two vector and assign the value to left hand side");

  DaliLog::PrintPass();
}

void Vector2OperatorSubtractionAndAssignmentP()
{
  Vector2 vec2Values1( 6.0f, 6.0f );
  Vector2 vec2Values2( 4.0f, 3.0f );
  Vector2 vec2Result( 2.0f, 3.0f );
  Vector2 vec2GetResult;

  vec2GetResult = vec2Values1 - vec2Values2;

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator- Api failed to Subtract two vector.");

  vec2Values1 -= vec2Values2;

  DALI_CHECK_FAIL( vec2Values1 != vec2Result , "operator-= Api failed to Subtract two vector and assign the value to left hand side.");

  DaliLog::PrintPass();
}

void Vector2OperatorUnaryNegationP()
{
  Vector2 vec2Values( 3.0f, 2.0f );
  Vector2 vec2Result( -3.0f, -2.0f );
  Vector2 vec2GetResult;

  vec2GetResult = ( -vec2Values );

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator-() Api failed to negate vector values.");

  DaliLog::PrintPass();
}

void Vector2OperatorDivisionAndAssignmentP()
{
  Vector2 vec2Values1( 6.0f, 6.0f );
  Vector2 vec2Values2( 3.0f, 2.0f );
  Vector2 vec2Result( 2.0f, 3.0f );
  Vector2 vec2GetResult;
  vec2GetResult = vec2Values1 / vec2Values2;
  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator/ Api failed to Divide two vector.");


  float fScaleVal = 3.0f;
  vec2Result = Vector2( 2.0f, 2.0f );
  vec2GetResult = vec2Values1 / fScaleVal;
  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "operator/ Api failed to divide a vector with a float value.");


  vec2Result = Vector2( 2.0f, 3.0f );
  vec2Values1 /= vec2Values2;
  DALI_CHECK_FAIL( vec2Values1 != vec2Result , "operator/= Api failed Divide two vector and assign the value to left hand side.");


  Vector2 vec2Values( 6.0f, 6.0f );
  vec2Result = Vector2( 2.0f, 2.0f );
  vec2Values /= fScaleVal;
  DALI_CHECK_FAIL( vec2Values != vec2Result , "operator/= Api failed to divide a vector with a float value.");

  DaliLog::PrintPass();
}

void Vector2OperatorFloatAssignmentP()
{
  float rgfpValues[2] = { 2.0f, 2.0f };
  Vector2 vec2Values( 0.0f, 0.0f );
  Vector2 vec2Result( 2.0f, 2.0f );

  vec2Values = rgfpValues;

  DALI_CHECK_FAIL( vec2Values != vec2Result , "operator= api is failed to assign array of floats to a vector2.");

  DaliLog::PrintPass();
}

void Vector2OperatorEqualityP()
{
  Vector2 vec2Values1( 11.0f, 2.0f );
  Vector2 vec2Values2;
  bool bEqual = false;

  vec2Values2=vec2Values1;
  bEqual = ( vec2Values1 == vec2Values2 );

  DALI_CHECK_FAIL( !bEqual , "operator== Api failed to return correct result.");

  DaliLog::PrintPass();
}

void Vector2OperatorSubscriptP()
{
  int nIndex = 0;
  Vector2 vec2Values( 2.0f, 3.0f );
  float fValueGvnIndx = 2.0f, fRetValue = 0.0f;

  fRetValue = vec2Values[nIndex];

  DALI_CHECK_FAIL( fRetValue != fValueGvnIndx , "Failed to return correct value for given index.");

  DaliLog::PrintPass();
}

void Vector2NormalizeWithLengthAndLengthSquaredP()
{
  float fValue1X = 2.0f, fValue1Y = 2.0f;
  float fUnitLength = 1.0f, fRetVal = 0.0f, fLengthVal = -1.0f, fVecLength = -1.0f, fVecLengthSquared = -1.0f;
  Vector2 vec2NormalizedVal( -1.0f, -1.0f );

  Vector2 vec2Values( fValue1X, fValue1Y );

  //  Calculation for length according to definition
  fVecLength = sqrtf( vec2Values.x*vec2Values.x + vec2Values.y*vec2Values.y );

  //  Find length of the vector
  fLengthVal = vec2Values.Length();

  DALI_CHECK_FAIL( !Equals(fLengthVal, fVecLength, VECTOR2_MATH_EPSILON ) , "Length Api failed to return the length of the vector.");

  //  Calculated Normalized Value.
  vec2NormalizedVal.x  =  vec2Values.x/fLengthVal;
  vec2NormalizedVal.y  =  vec2Values.y/fLengthVal;

  vec2Values.Normalize();

  //  Calculation for length according to definition
  fVecLengthSquared = vec2Values.x*vec2Values.x + vec2Values.y*vec2Values.y;

  fRetVal = vec2Values.LengthSquared();

  DALI_CHECK_FAIL( fVecLengthSquared != fRetVal , "LengthSquared Api failed to return expected result.");
  DALI_CHECK_FAIL( vec2Values  !=  vec2NormalizedVal , "Failed to normalize vector2.");
  DALI_CHECK_FAIL( !Equals( fRetVal, fUnitLength, VECTOR2_MATH_EPSILON ) , "Failed to meet unit length criteria for normalized vector.");

  DaliLog::PrintPass();
}

void Vector2MinP()
{
  Vector2 vec2Values1( 11.0f, 2.0f );
  Vector2 vec2Values2( 10.0f, 1.0f );

  Vector2 vec2CalResult( min( vec2Values1.x, vec2Values2.x ), min( vec2Values1.y, vec2Values2.y ) );

  Vector2 vec2GetResult = Min( vec2Values1, vec2Values2 );

  DALI_CHECK_FAIL( vec2GetResult != vec2CalResult , "Min Api failed to return correct value");
  DALI_CHECK_FAIL( vec2GetResult.x > vec2Values1.x || vec2GetResult.x > vec2Values2.x || vec2GetResult.y > vec2Values1.y || vec2GetResult.y > vec2Values2.y  , "Returning Vector2 is not minimum for all components.");

  DaliLog::PrintPass();
}

void Vector2MaxP()
{
  Vector2 vec2Values1( 11.0f, 2.0f );
  Vector2 vec2Values2( 10.0f, 1.0f );

  Vector2 vec2CalResult( max( vec2Values1.x, vec2Values2.x ), max( vec2Values1.y, vec2Values2.y ) );

  Vector2 vec2GetResult = Max( vec2Values1, vec2Values2 );

  DALI_CHECK_FAIL( vec2GetResult != vec2CalResult , "Max Api failed to return correct value.");
  DALI_CHECK_FAIL( vec2GetResult.x < vec2Values1.x || vec2GetResult.x < vec2Values2.x || vec2GetResult.y < vec2Values1.y || vec2GetResult.y < vec2Values2.y  , "Returning Vector2 is not maximum for all components.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase        UtcDaliVector2ConstructorP
 * @since_tizen     2.4
 * @description     Construct a vector using default constructor.
 */
int UtcDaliVector2ConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector2ConstrucAndGetAsFloatP
 * @since_tizen     2.4
 * @description     Construct a vector with two float value and retrieve the values of Vector2 as an array of two float value.
 */
int UtcDaliVector2ConstrucAndGetAsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_CONSTRUCT_GET_AS_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2ConstructArrayAndGetAsConstFloatP
 * @since_tizen     2.4
 * @description     Construct a vector with an array values and retrieve the values as an array of 2 float values.
 */
int UtcDaliVector2ConstructArrayAndGetAsConstFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_CONSTRUCT_GET_AS_CONST_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2Vec3ConstructAndAssignP
 * @since_tizen     2.4
 * @description     Construct a vector with Vector3 and assigned a Vector2 with Vector3 values.
 */
int UtcDaliVector2Vec3ConstructAndAssignP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_VEC3_CONSTRUCT_AND_ASSIGN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2Vec4ConstructAndAssignP
 * @since_tizen     2.4
 * @description     Construct a vector with Vector4 and assigned a Vector2 with Vector4 values.
 */
int UtcDaliVector2Vec4ConstructAndAssignP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_VEC4_CONSTRUCT_AND_ASSIGN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2ClampP
 * @since_tizen     2.4
 * @description     Clamps the vector between minimum and maximum vectors.
 */
int UtcDaliVector2ClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_CLAMP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2OperatorInequalityP
 * @since_tizen     2.4
 * @description     Check inequality between two operator.
 */
int UtcDaliVector2OperatorInequalityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_INEQUALITY_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector2OperatorMultiplicationAndAssignmentP
 * @since_tizen     2.4
 * @description     Multiply two vector, multiply vector with float value and assignment.
 */
int UtcDaliVector2OperatorMultiplicationAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2OperatorAdditionAndAssignmentP
 * @since_tizen     2.4
 * @description     Add two vectors and assign the result to left hand side.
 */
int UtcDaliVector2OperatorAdditionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_ADDITION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector2OperatorSubtractionAndAssignmentP
 * @since_tizen     2.4
 * @description     Subtract two vectors and assign the result to left hand side.
 */
int UtcDaliVector2OperatorSubtractionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector2OperatorUnaryNegationP
 * @since_tizen     2.4
 * @description     Provide negation of a vector.
 */
int UtcDaliVector2OperatorUnaryNegationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_UNARY_NEGATION_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector2OperatorDivisionAndAssignmentP
 * @since_tizen     2.4
 * @description     Divide two vector and related operation.
 */
int UtcDaliVector2OperatorDivisionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_DIVISION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2OperatorFloatAssignmentP
 * @since_tizen     2.4
 * @description     Assign array of floats to a vector2.
 */
int UtcDaliVector2OperatorFloatAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_FLOAT_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2OperatorEqualityP
 * @since_tizen     2.4
 * @description     Check equality between two operator.
 */
int UtcDaliVector2OperatorEqualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_EQUALITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2OperatorSubscriptP
 * @since_tizen     2.4
 * @description     Return the float at the given index.
 */
int UtcDaliVector2OperatorSubscriptP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_OPERATOR_SUBSCRIPT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2NormalizeWithLengthAndLengthSquaredP
 * @since_tizen     2.4
 * @description     Sets the vector to be unit length, whilst maintaining its direction.
 */
int UtcDaliVector2NormalizeWithLengthAndLengthSquaredP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2MinP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the minimum of the corresponding component in a and b.
 */
int UtcDaliVector2MinP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_MIN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector2MaxP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the maximum of the corresponding component in a and b.
 */
int UtcDaliVector2MaxP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector2_TestApp testApp( application, VECTOR2_MAX_P);
  application.MainLoop();
  return test_return_value;
}
