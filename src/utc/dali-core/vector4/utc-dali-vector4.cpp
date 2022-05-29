#include "utc-dali-vector4-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Vector4
/**
 * @function           utc_Dali_Vector4_startup
 * @description        Called before each test
 * @parameter          NA
 * @return             NA
 */
void utc_Dali_Vector4_startup(void)
{
  test_return_value = 0;
}

/**
 * @function           utc_Dali_Vector4_cleanup
 * @description        Called after each test
 * @parameter          NA
 * @return             NA
 */
void utc_Dali_Vector4_cleanup(void)
{

}

void Vector4ConstructorP();
void Vector4ConstructAndGetAsFloatP();
void Vector4ArrayAndGetAsConstFloatP();
void Vector4WithVec2P();
void Vector4WithVec3P();
void Vector4CrossP();
void Vector4DotP();
void Vector4DotVec3P();
void Vector4Dot4P();
void Vector4ClampP();
void Vector4NormalizeWithLengthAndLengthSquaredP();
void Vector4OperatorInequalityP();
void Vector4OperatorMultiplicationAndAssignmentP();
void Vector4OperatorMultiplicationAssignmentFloatP();
void Vector4OperatorAdditionAndAssignmentP();
void Vector4OperatorSubtractionAssignmentP();
void Vector4OperatorUnaryNegationP();
void Vector4OperatorDivisionAndAssignmentP();
void Vector4OperatorDivisionAssignmentFloatP();
void Vector4OperatorFloatAssignmentP();
void Vector4OperatorVector2AssignmentP();
void Vector4OperatorVector3AssignmentP();
void Vector4OperatorEqualityP();
void Vector4OperatorSubscriptP();
void Vector4ClampWithMinMaxP();
void Vector4MinP();
void Vector4MaxP();

namespace
{
  enum TEST_CASES_LIST_VECTOR4
  {
    VECTOR4_CONSTRUCTOR_P,
    VECTOR4_CONSTRUCT_GET_AS_FLOAT_P,
    VECTOR4_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P,
    VECTOR4_WITH_VEC2_P,
    VECTOR4_WITH_VEC3_P,
    VECTOR4_CROSS_P,
    VECTOR4_DOT_P,
    VECTOR4_DOT_VEC3_P,
    VECTOR4_DOT_VEC4_P,
    VECTOR4_CLAMP_P,
    VECTOR4_NORMALIZE_WITH_LENGTH_AND_LENGTH_SQUARED_P,
    VECTOR4_OPERATOR_INEQUALITY_P,
    VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P,
    VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P,
    VECTOR4_OPERATOR_ADDITION_AND_ASSIGNMENT_P,
    VECTOR4_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P,
    VECTOR4_OPERATOR_UNARY_NEGATION_P,
    VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_P,
    VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P,
    VECTOR4_OPERATOR_FLOAT_ASSIGNMENT_P,
    VECTOR4_OPERATOR_VECTOR2_ASSIGNMENT_P,
    VECTOR4_OPERATOR_VECTOR3_ASSIGNMENT_P,
    VECTOR4_OPERATOR_EQUALITY_P,
    VECTOR4_OPERATOR_SUBSCRIPT_P,
    VECTOR4_CLAM_WITH_MIN_MAX_P,
    VECTOR4_MIN_P,
    VECTOR4_MAX_P
  };

  struct Vector4_TestApp : public ConnectionTracker
  {
    Vector4_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Vector4_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Vector4_TestApp::Tick );
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
        case VECTOR4_CONSTRUCTOR_P:
          Vector4ConstructorP();
          break;
        case VECTOR4_CONSTRUCT_GET_AS_FLOAT_P:
          Vector4ConstructAndGetAsFloatP();
          break;
        case VECTOR4_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P:
          Vector4ArrayAndGetAsConstFloatP();
          break;
        case VECTOR4_WITH_VEC2_P:
          Vector4WithVec2P();
          break;
        case VECTOR4_WITH_VEC3_P:
          Vector4WithVec3P();
          break;
        case VECTOR4_CROSS_P:
          Vector4CrossP();
          break;
        case VECTOR4_DOT_P:
          Vector4DotP();
          break;
        case VECTOR4_DOT_VEC3_P:
          Vector4DotVec3P();
          break;
        case VECTOR4_DOT_VEC4_P:
          Vector4Dot4P();
          break;
        case VECTOR4_CLAMP_P:
          Vector4ClampP();
          break;
        case VECTOR4_NORMALIZE_WITH_LENGTH_AND_LENGTH_SQUARED_P:
          Vector4NormalizeWithLengthAndLengthSquaredP();
          break;
        case VECTOR4_OPERATOR_INEQUALITY_P:
          Vector4OperatorInequalityP();
          break;
        case VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P:
          Vector4OperatorMultiplicationAndAssignmentP();
          break;
        case VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P:
          Vector4OperatorMultiplicationAssignmentFloatP();
          break;
        case VECTOR4_OPERATOR_ADDITION_AND_ASSIGNMENT_P:
          Vector4OperatorAdditionAndAssignmentP();
          break;
        case VECTOR4_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P:
          Vector4OperatorSubtractionAssignmentP();
          break;
        case VECTOR4_OPERATOR_UNARY_NEGATION_P:
          Vector4OperatorUnaryNegationP();
          break;
        case VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_P:
          Vector4OperatorDivisionAndAssignmentP();
          break;
        case VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P:
          Vector4OperatorDivisionAssignmentFloatP();
          break;
        case VECTOR4_OPERATOR_FLOAT_ASSIGNMENT_P:
          Vector4OperatorFloatAssignmentP();
          break;
        case VECTOR4_OPERATOR_VECTOR2_ASSIGNMENT_P:
          Vector4OperatorVector2AssignmentP();
          break;
        case VECTOR4_OPERATOR_VECTOR3_ASSIGNMENT_P:
          Vector4OperatorVector3AssignmentP();
          break;
        case VECTOR4_OPERATOR_EQUALITY_P:
          Vector4OperatorEqualityP();
          break;
        case VECTOR4_OPERATOR_SUBSCRIPT_P:
          Vector4OperatorSubscriptP();
          break;
        case VECTOR4_CLAM_WITH_MIN_MAX_P:
          Vector4ClampWithMinMaxP();
          break;
        case VECTOR4_MIN_P:
          Vector4MinP();
          break;
        case VECTOR4_MAX_P:
          Vector4MaxP();
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

void Vector4ConstructorP()
{
  float fVecX = 0.0f, fVecY = 2.0f, fVecZ = 4.5f, fVecW = 6.0f;

  //  Create a vector with 4 float values.
  Vector4 vec4( fVecX, fVecY, fVecZ, fVecW );

  DALI_CHECK_FAIL( ( vec4.x != fVecX ) || ( vec4.y != fVecY ) || ( vec4.z != fVecZ ) || ( vec4.w != fVecW ) , "Vector4 api is failed to create constructor with given value.");

  DaliLog::PrintPass();
}


void Vector4ConstructAndGetAsFloatP()
{
  float fVecX = 0.0f, fVecY = 2.0f, fVecZ = 4.5f, fVecW = 6.0f;
  float *rgfValue = NULL;

  //  Create a vector with 4 float values.
  Vector4 vec4( fVecX, fVecY, fVecZ, fVecW );

  DALI_CHECK_FAIL( ( vec4.x != fVecX ) || ( vec4.y != fVecY ) || ( vec4.z != fVecZ ) || ( vec4.w != fVecW ) , "Vector4 api is failed to create constructor with given value.");

  // Retrieve the vector value as an array of four float value
  rgfValue = vec4.AsFloat();

  DALI_CHECK_FAIL( ( vec4.x != rgfValue[0] ) || ( vec4.y != rgfValue[1] ) || ( vec4.z != rgfValue[2] ) || ( vec4.w != rgfValue[3] ) , "AsFloat is failed to retrieve value of Vector4 as an array.");

  DaliLog::PrintPass();
}

void Vector4ArrayAndGetAsConstFloatP()
{
  float rgfValues[] = { 0.0f, 1.0f, 2.0f, 3.0f };

  const Vector4 vec4( rgfValues );

  DALI_CHECK_FAIL( ( vec4.x != rgfValues[0] ) || ( vec4.y != rgfValues[1] ) || ( vec4.z != rgfValues[2] ) || ( vec4.w != rgfValues[3] ) , "Vector4 api is failed to create constructor with given array values.");

  const float *rgfpValue = vec4.AsFloat();

  DALI_CHECK_FAIL( ( vec4.x != rgfpValue[0] ) || ( vec4.y != rgfpValue[1] ) || ( vec4.z != rgfpValue[2] ) || ( vec4.w != rgfpValue[3] ) , "Const float* AsFloat() is failed create constructor with given value.");

  DaliLog::PrintPass();
}

void Vector4WithVec2P()
{
  float fValX = 1.0f, fValY = 2.0f;

  Vector2 vec2( fValX, fValY );
  Vector4 vec4( vec2);
  DALI_CHECK_FAIL( ( vec4.x != vec2.x ) || ( vec4.y != vec2.y ) || ( vec4.z != VECTOR4_FZERO) || ( vec4.w != VECTOR4_FZERO) , "Vector4 api is failed to create constructor with given Vector2 value.");

  DaliLog::PrintPass();
}

void Vector4WithVec3P()
{
  float fValX = 1.0f, fValY = 2.0f, fValZ = 3.0f, fValW = 0.0f;

  Vector3 vec3( fValX, fValY, fValZ );  //  Vector3 to assign as Vector4 value.
  Vector4 vec4( vec3 );
  DALI_CHECK_FAIL( (vec4.x != vec3.x ) || ( vec4.y != vec3.y ) || ( vec4.z != vec3.z ) || ( vec4.w != fValW ) , "Vector4 api is failed to create constructor with given Vector3 value.");

  DaliLog::PrintPass();
}

void Vector4CrossP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;

  Vector4 vec4Value1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Value2( fValue2X, fValue2Y, fValue2Z, fValue2W );

  Vector4 vec4CrossResult( ( vec4Value1.y*vec4Value2.z - vec4Value1.z*vec4Value2.y ),
      ( vec4Value1.z*vec4Value2.x - vec4Value1.x*vec4Value2.z ),
      ( vec4Value1.x*vec4Value2.y - vec4Value1.y*vec4Value2.x ), VECTOR4_FZERO );  //  Expected Result

  Vector4 vec4Result = vec4Value1.Cross( vec4Value2 );
  DALI_CHECK_FAIL( vec4CrossResult != vec4Result , "Cross is failed to produce expected cross product of two vectors.");

  DaliLog::PrintPass();
}

void Vector4DotP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 3.3f, fValue1W = 7.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;
  float fDotResult = 0;
  float fResult = 0;

  Vector4 vec4Value1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Value2( fValue2X, fValue2Y, fValue2Z, fValue2W );

  fDotResult = vec4Value1.x*vec4Value2.x + vec4Value1.y*vec4Value2.y + vec4Value1.z*vec4Value2.z + 0.0f;  //  Expected Dot Result
  fResult = 0.0f;

  fResult = vec4Value1.Dot( vec4Value2 );

  DALI_CHECK_FAIL( fResult != fDotResult , "Dot API failed to produce dot product of two vectors.");

  DaliLog::PrintPass();
}

void Vector4DotVec3P()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 3.3f, fValue1W = 7.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;

  float fDotResult;
  float fResult;

  Vector4 vec4Value1( fValue1X, fValue1Y, fValue1Z, fValue1W );

  Vector3 vec3Value2( fValue2X, fValue2Y, fValue2Z );
  fDotResult = vec4Value1.x*vec3Value2.x + vec4Value1.y*vec3Value2.y + vec4Value1.z*vec3Value2.z;
  fResult = 0.0f;

  fResult = vec4Value1.Dot( vec3Value2);

  DALI_CHECK_FAIL( fResult != fDotResult , "Dot is failed to produce dot product of Vector4 and Vector3.");

  DaliLog::PrintPass();
}

void Vector4Dot4P()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 3.3f, fValue1W = 7.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;

  float fDotResult;
  float fResult;

  Vector4 vec4Value1( fValue1X, fValue1Y, fValue1Z, fValue1W );

  Vector4 vec4Value2( fValue2X, fValue2Y, fValue2Z, fValue2W );

  fDotResult = vec4Value1.x*vec4Value2.x + vec4Value1.y*vec4Value2.y + vec4Value1.z*vec4Value2.z + vec4Value1.w*vec4Value2.w;
  fResult = 0.0f;

  fResult = vec4Value1.Dot4( vec4Value2);
  DALI_CHECK_FAIL( fResult != fDotResult , "Dot4 is failed to produce dot product of two vectors");

  DaliLog::PrintPass();
}
void Vector4ClampP()
{
  float fValueX = 11.0f, fValueY = 2.0f, fValueZ = 4.0f, fValueW = 4.0f;
  float fMinX = 1.0f, fMinY = 3.0f, fMinZ = 2.0f, fMinW = 2.0f;
  float fMaxX = 10.0f, fMaxY = 13.0f, fMaxZ = 5.0f, fMaxW = 5.0f;

  Vector4 vec4ClampResult(10.0f, 3.0f, 4.0f, 4.0f);  //  Expected Clamping Result
  Vector4 vec4Values( fValueX, fValueY, fValueZ, fValueW );
  Vector4 vec4Min( fMinX, fMinY, fMinZ, fMinW );
  Vector4 vec4Max( fMaxX, fMaxY, fMaxZ, fMaxW );

  //  Calculated Clamping Result
  vec4ClampResult.x = ( vec4Values.x >= vec4Min.x && vec4Values.x <= vec4Max.x ) ? ( vec4Values.x ) : (( fabsf( vec4Values.x - vec4Min.x ) < fabsf( vec4Values.x - vec4Max.x ) ) ? vec4Min.x:vec4Max.x );
  vec4ClampResult.y = ( vec4Values.y >= vec4Min.y && vec4Values.y <= vec4Max.y ) ? ( vec4Values.y ) : (( fabsf( vec4Values.y - vec4Min.y ) < fabsf( vec4Values.y - vec4Max.y ) ) ? vec4Min.y:vec4Max.y );
  vec4ClampResult.z = ( vec4Values.z >= vec4Min.z && vec4Values.z <= vec4Max.z ) ? ( vec4Values.z ) : (( fabsf( vec4Values.z - vec4Min.z ) < fabsf( vec4Values.z - vec4Max.z ) ) ? vec4Min.z:vec4Max.z );
  vec4ClampResult.w = ( vec4Values.w >= vec4Min.w && vec4Values.w <= vec4Max.w ) ? ( vec4Values.w ) : (( fabsf( vec4Values.w - vec4Min.w ) < fabsf( vec4Values.w - vec4Max.w ) ) ? vec4Min.w:vec4Max.w );

  vec4Values.Clamp( vec4Min, vec4Max);
  DALI_CHECK_FAIL( vec4ClampResult != vec4Values , "Clamp is failed to clamp the vector between minimum and maximum vectors.");

  DaliLog::PrintPass();
}

void Vector4NormalizeWithLengthAndLengthSquaredP()
{
  float fValue1X = 4.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fUnitLength = 1.0f, fRetVal = 0.0f, fLengthVal = -1.0f, fVecLength = -1.0f, fVecLengthSquared = -1.0f;
  Vector4 vec4NormalizedVal( -1.0f, -1.0f, -1.0f, -1.0f );

  Vector4 vec4Values( fValue1X, fValue1Y, fValue1Z, fValue1Z );

  //  Calculation for length according to definition
  fVecLength = sqrtf( vec4Values.x*vec4Values.x + vec4Values.y*vec4Values.y + vec4Values.z*vec4Values.z );

  //  Find length of the vector
  fLengthVal = vec4Values.Length();

  DALI_CHECK_FAIL( fLengthVal  !=  fVecLength , "Length Api failed to return the length of the vector.");

  //  Calculated Normalized Value.
  vec4NormalizedVal.x  =  vec4Values.x/fLengthVal;
  vec4NormalizedVal.y  =  vec4Values.y/fLengthVal;
  vec4NormalizedVal.z  =  vec4Values.z/fLengthVal;
  vec4NormalizedVal.w  =  vec4Values.z;

  vec4Values.Normalize();

  //  Calculation for length according to definition
  fVecLengthSquared = vec4Values.x*vec4Values.x + vec4Values.y*vec4Values.y + vec4Values.z*vec4Values.z;

  fRetVal = vec4Values.LengthSquared();

  DALI_CHECK_FAIL( !Equals(fVecLengthSquared, fRetVal, VECTOR4_MATH_EPSILON) , "LengthSquared Api failed to return expected result.");

  DALI_CHECK_FAIL( vec4Values  !=  vec4NormalizedVal , "Failed to normalize vector4.");

  DALI_CHECK_FAIL( !Equals( fRetVal, fUnitLength, VECTOR4_MATH_EPSILON ) , "Failed to meet unit length criteria for normalized vector.");

  DaliLog::PrintPass();
}

void Vector4OperatorInequalityP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  bool bInequal = false;
  Vector4 vec4Values1( 0.0f, 0.0f, 0.0f, 0.0f ), vec4Values2( 0.0f, 0.0f, 0.0f, 0.0f );

  vec4Values1 = Vector3( fValue1X, fValue1Y, fValue1Z );
  vec4Values2 = Vector3( fValue2X, fValue2Y, fValue2Z );

  bInequal = ( vec4Values1 != vec4Values2 );
  DALI_CHECK_FAIL( !bInequal , "OperatorInequality Api failed to check inequality between two Vector4.");

  DaliLog::PrintPass();
}

void Vector4OperatorMultiplicationAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Values2( fValue2X, fValue2Y, fValue2Z, fValue2W );

  Vector4 vec4Result( ( fValue1X*fValue2X ), ( fValue1Y*fValue2Y ), ( fValue1Z*fValue2Z ), ( fValue1W*fValue2W ) );  //  Expected Result After Multiplication.

  vec4GetResult = vec4Values1 * vec4Values2;
  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "OperatorMultiplication Api failed multiply two vector.");
  vec4Values1 *= vec4Values2;

  DALI_CHECK_FAIL( vec4Values1 != vec4Result , "OperatorMultiplicationAssignment Api failed multiply two vector and assign the value to left hand side.");

  DaliLog::PrintPass();
}

void Vector4OperatorMultiplicationAssignmentFloatP()
{
  float fScaleVal = 3.0f;
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Result(( fValue1X*fScaleVal ), ( fValue1Y*fScaleVal ), ( fValue1Z*fScaleVal ), ( fValue1W*fScaleVal ) );
  vec4GetResult = vec4Values * fScaleVal;
  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "Operator* Api failed to multiply a vector with a float value.");

  vec4Values *= fScaleVal;
  DALI_CHECK_FAIL( vec4Values != vec4Result , "operator*= failed to assing multiplication result.");

  DaliLog::PrintPass();
}

void Vector4OperatorAdditionAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Values2( fValue2X, fValue2Y, fValue2Z, fValue2W );
  Vector4 vec4Result(( fValue1X+fValue2X ), ( fValue1Y+fValue2Y ), ( fValue1Z+fValue2Z ), ( fValue1W+fValue2W ) );  //  Expected Result.
  vec4GetResult = vec4Values1 + vec4Values2;
  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "operator+ Api failed to add two vector.");
  vec4Values1 += vec4Values2;
  DALI_CHECK_FAIL( vec4Values1 != vec4Result , "operator+= Api failed to add two vector and assign the value to left hand side.");

  DaliLog::PrintPass();
}

void Vector4OperatorSubtractionAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 3.0f, fValue1Z = 5.0f, fValue1W = 5.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Values2( fValue2X, fValue2Y, fValue2Z, fValue2W );
  Vector4 vec4Result(( fValue1X-fValue2X ), ( fValue1Y-fValue2Y ), ( fValue1Z-fValue2Z ), ( fValue1W-fValue2W ) );  //  Expected Result.
  vec4GetResult = vec4Values1 - vec4Values2;

  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "operator- Api failed to Subtract two vector.");
  vec4Values1 -= vec4Values2;
  DALI_CHECK_FAIL( vec4Values1 != vec4Result , "operator-= Api failed to Subtract two vector and assign the value to left hand side.");

  DaliLog::PrintPass();
}

void Vector4OperatorUnaryNegationP()
{
  float fValue1X = 3.0f, fValue1Y = 3.0f, fValue1Z = 5.0f, fValue1W = 5.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Result( -fValue1X, -fValue1Y, -fValue1Z, -fValue1W );
  vec4GetResult = ( -vec4Values );
  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "operator-() Api failed to negate vector.");

  DaliLog::PrintPass();
}

void Vector4OperatorDivisionAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f, fValue2W = 4.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Values2( fValue2X, fValue2Y, fValue2Z, fValue2W );

  Vector4 vec4Result(( fValue1X/fValue2X ), ( fValue1Y/fValue2Y ),( fValue1Z/fValue2Z ),( fValue1W/fValue2W ) );
  vec4GetResult = vec4Values1 / vec4Values2;

  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "OperatorDivision Api failed Divide two vector.");
  vec4Values1 /= vec4Values2;

  DALI_CHECK_FAIL( vec4Values1 != vec4Result , "operator/= Api failed Divide two vector and assign the value to left hand side.");

  DaliLog::PrintPass();
}

void Vector4OperatorDivisionAssignmentFloatP()
{
  float fValue1X = 4.0f, fValue1Y = 4.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fScaleVal = 2.0f;
  Vector4 vec4GetResult;

  Vector4 vec4Values( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Result(( fValue1X/fScaleVal), ( fValue1Y/fScaleVal),( fValue1Z/fScaleVal),( fValue1W/fScaleVal) );
  vec4GetResult = vec4Values / fScaleVal;

  DALI_CHECK_FAIL( vec4GetResult != vec4Result , "operator/ Api failed to a divide vector by a float value.");
  vec4Values /= fScaleVal;
  DALI_CHECK_FAIL( vec4Values != vec4Result , "OperatorDivisionAssignmentFloat Api failed to a vector with a float value vec4Values.");

  DaliLog::PrintPass();
}

void Vector4OperatorFloatAssignmentP()
{
  float rgfpValues[4] = { 2.0f, 2.0f, 2.0f, 2.0f };

  Vector4 vec4Values;
  Vector4 vec4Result = Vector4( rgfpValues[0], rgfpValues[1], rgfpValues[2], rgfpValues[3] );

  vec4Values = rgfpValues;
  DALI_CHECK_FAIL( vec4Values != vec4Result , "Operator Float Assignment is failed to assign array of floats to vector4.");

  DaliLog::PrintPass();
}

void Vector4OperatorVector2AssignmentP()
{
  float fValue1 = 2.0f, fValue2 = 3.0f;
  Vector4 vec4Values;

  Vector2 vec2Values( fValue1, fValue2);
  Vector4 vec4Result ( fValue1, fValue2, VECTOR4_FZERO, VECTOR4_FZERO);
  vec4Values = vec2Values;
  DALI_CHECK_FAIL( vec4Values != vec4Result , "Operator Vector4 Assignment is failed to assign vector4 to vector4.");

  DaliLog::PrintPass();
}

void Vector4OperatorVector3AssignmentP()
{
  float fValue1 = 2.0f, fValue2 = 3.0f, fValue3 = 2.0f;
  Vector4 vec4Values;

  Vector3 vec3Values( fValue1, fValue2, fValue3);
  Vector4 vec4Result( vec3Values.x, vec3Values.y, vec3Values.z, VECTOR4_FZERO);
  vec4Values = vec3Values;

  DALI_CHECK_FAIL( vec4Values != vec4Result , "Operator Vector4 Assignment is failed to assign Vector3 to vector4.");
  DaliLog::PrintPass();
}

void Vector4OperatorEqualityP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  bool bEqual = false;

  Vector4 vec4Values1( fValue1X, fValue1Y, fValue1Z, fValue1W );
  Vector4 vec4Values2( fValue1X, fValue1Y, fValue1Z, fValue1W );

  bEqual = ( vec4Values1 == vec4Values2 );
  DALI_CHECK_FAIL( !bEqual , "OperatorEquality Api failed to return correct result.");

  DaliLog::PrintPass();
}

void Vector4OperatorSubscriptP()
{
  int nIndex = 0;
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f, fValue1W = 4.0f;
  float fValueGvnIndx = 2.0f, fRetValue = 0.0f;

  Vector4 vec4Values( fValue1X, fValue1Y, fValue1Z, fValue1W );

  fValueGvnIndx = vec4Values.x;
  fRetValue = 0.0f;
  fRetValue = vec4Values[nIndex];
  DALI_CHECK_FAIL( fRetValue != fValueGvnIndx, "Failed to return correct value.");

  DaliLog::PrintPass();
}

void Vector4ClampWithMinMaxP()
{
  float fValueX = 11.0f, fValueY = 2.0f, fValueZ = 4.0f, fValueW = 3.0f;;
  float fMin = 1.0f, fMax = 10.0f;

  Vector4 vec4ClampResult(12.0f, 10.0f, 3.0f, 4.0f);

  Vector4 vec4Values( fValueX, fValueY, fValueZ, fValueW );
  Vector4 vec4GetResult(-1.0f, -1.0f, -1.0f, -1.0f);
  Vector4 vec4Min( fMin, fMin, fMin, fMin );
  Vector4 vec4Max( fMax, fMax, fMax, fMax);

  vec4ClampResult.x = ( vec4Values.x >= vec4Min.x && vec4Values.x <= vec4Max.x ) ? ( vec4Values.x ) : (( fabsf( vec4Values.x - vec4Min.x ) < fabsf( vec4Values.x - vec4Max.x ) ) ? vec4Min.x:vec4Max.x );
  vec4ClampResult.y = ( vec4Values.y >= vec4Min.y && vec4Values.y <= vec4Max.y ) ? ( vec4Values.y ) : (( fabsf( vec4Values.y - vec4Min.y ) < fabsf( vec4Values.y - vec4Max.y ) ) ? vec4Min.y:vec4Max.y );
  vec4ClampResult.z = ( vec4Values.z >= vec4Min.z && vec4Values.z <= vec4Max.z ) ? ( vec4Values.z ) : (( fabsf( vec4Values.z - vec4Min.z ) < fabsf( vec4Values.z - vec4Max.z ) ) ? vec4Min.z:vec4Max.z );
  vec4ClampResult.w = ( vec4Values.w >= vec4Min.w && vec4Values.w <= vec4Max.w ) ? ( vec4Values.w ) : (( fabsf( vec4Values.w - vec4Min.w ) < fabsf( vec4Values.w - vec4Max.w ) ) ? vec4Min.w:vec4Max.w );

  vec4GetResult = Clamp( vec4Values, fMin, fMax );
  DALI_CHECK_FAIL( vec4ClampResult != vec4GetResult , "Clamp is failed to Clamp the vector between minimum and maximum vectors.");
  vec4Values.Clamp(vec4Min, vec4Max);
  DALI_CHECK_FAIL( vec4ClampResult != vec4Values , "Clamp api is failed to Clamp the vector between minimum and maximum values.");

  DaliLog::PrintPass();
}

void Vector4MinP()
{
  Vector4 vec4Values1(3.0f, 10.0f, 11.0f, 2.0f);
  Vector4 vec4Values2(2.0f, 5.0f, 10.0f, 1.0f);
  Vector4 vec4CalResult(min( vec4Values1.x, vec4Values2.x ), min( vec4Values1.y, vec4Values2.y ), min( vec4Values1.z, vec4Values2.z ), min( vec4Values1.w, vec4Values2.w ) );

  Vector4 vec4GetResult = Min( vec4Values1, vec4Values2 );

  DALI_CHECK_FAIL( vec4GetResult != vec4CalResult , "Min Api failed to return correct value.");
  DALI_CHECK_FAIL( vec4GetResult.x > vec4Values1.x || vec4GetResult.x > vec4Values2.x || 	vec4GetResult.y > vec4Values1.y || vec4GetResult.y > vec4Values2.y || vec4GetResult.z > vec4Values1.z || vec4GetResult.z > vec4Values2.z || vec4GetResult.w > vec4Values1.w || vec4GetResult.w > vec4Values2.w , "Returning Vector4 is not minimum for all components.");

  DaliLog::PrintPass();
}

void Vector4MaxP()
{
  Vector4 vec4Values1( 2.0f, 10.0f, 11.0f, 2.0f );
  Vector4 vec4Values2( 4.0f, 5.0f, 10.0f, 1.0f );
  Vector4 vec4CalResult( max( vec4Values1.x, vec4Values2.x ), max( vec4Values1.y, vec4Values2.y ), max( vec4Values1.z, vec4Values2.z ), max( vec4Values1.w, vec4Values2.w ) );

  Vector4 vec4GetResult = Max( vec4Values1, vec4Values2 );

  DALI_CHECK_FAIL( vec4GetResult != vec4CalResult , "Max Api failed to return correct value.");
  DALI_CHECK_FAIL( vec4GetResult.x < vec4Values1.x || vec4GetResult.x < vec4Values2.x || vec4GetResult.y < vec4Values1.y || vec4GetResult.y < vec4Values2.y || vec4GetResult.z < vec4Values1.z || vec4GetResult.z < vec4Values2.z || vec4GetResult.w < vec4Values1.w || vec4GetResult.w < vec4Values2.w , "Returning Vector4 is not maximum for all components.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase        UtcDaliVector4ConstructorP
 * @since_tizen     2.4
 * @description     Construct a vector with default constructor.
 */
int UtcDaliVector4ConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CONSTRUCTOR_P );
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4ConstructAndGetAsFloatP
 * @since_tizen     2.4
 * @description     Construct a vector with 4 float value and retrieve the values of the vector as an array of four float values.
 */
int UtcDaliVector4ConstructAndGetAsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CONSTRUCT_GET_AS_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4ArrayAndGetAsConstFloatP
 * @since_tizen     2.4
 * @description     Construct a Vector4 with array value and retrieve the value as an array of four float value.
 */
int UtcDaliVector4ArrayAndGetAsConstFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4WithVec2P
 * @since_tizen     2.4
 * @description     Construct a vector4 with Vector2 value.
 */
int UtcDaliVector4WithVec2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_WITH_VEC2_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4WithVec3P
 * @since_tizen     2.4
 * @description     Construct a vector with Vector3 value.
 */
int UtcDaliVector4WithVec3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_WITH_VEC3_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4CrossP
 * @since_tizen     2.4
 * @description     Produce the cross product of two vectors.
 */
int UtcDaliVector4CrossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CROSS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4DotP
 * @since_tizen     2.4
 * @description     Produce the dot product of two vectors.
 */
int UtcDaliVector4DotP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_DOT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4DotVec3P
 * @since_tizen     2.4
 * @description     Produce the dot product of Vector4 and Vector3.
 */
int UtcDaliVector4DotVec3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_DOT_VEC3_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4Dot4P
 * @since_tizen     2.4
 * @description     Returns the 4d dot product of two Vector4.
 */
int UtcDaliVector4Dot4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_DOT_VEC4_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4ClampP
 * @since_tizen     2.4
 * @description     Clamps the vector between minimum and maximum vectors.
 */
int UtcDaliVector4ClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CLAMP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4NormalizeWithLengthAndLengthSquaredP
 * @since_tizen     2.4
 * @description     Sets the vector to be unit length, whilst maintaining its direction.
 */
int UtcDaliVector4NormalizeWithLengthAndLengthSquaredP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_NORMALIZE_WITH_LENGTH_AND_LENGTH_SQUARED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorInequalityP
 * @since_tizen     2.4
 * @description     Check inequality between two Vector4.
 */
int UtcDaliVector4OperatorInequalityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_INEQUALITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorMultiplicationAndAssignmentP
 * @since_tizen     2.4
 * @description     Multiply two vector.
 */
int UtcDaliVector4OperatorMultiplicationAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorMultiplicationAssignmentFloatP
 * @since_tizen     2.4
 * @description     Multiply vector with a float value and assign the value to left hand side.
 */
int UtcDaliVector4OperatorMultiplicationAssignmentFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorAdditionAndAssignmentP
 * @since_tizen     2.4
 * @description     Add two vector.
 */
int UtcDaliVector4OperatorAdditionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_ADDITION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorSubtractionAssignmentP
 * @since_tizen     2.4
 * @description     Subtract two vectors and assign the result to left hand side.
 */
int UtcDaliVector4OperatorSubtractionAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorUnaryNegationP
 * @since_tizen     2.4
 * @description     Provide negation of a vector.
 */
int UtcDaliVector4OperatorUnaryNegationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_UNARY_NEGATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorDivisionAndAssignmentP
 * @since_tizen     2.4
 * @description     Divide two vector and assign the result to left hand side.
 */
int UtcDaliVector4OperatorDivisionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorDivisionAssignmentFloatP
 * @since_tizen     2.4
 * @description     Divide vector with a float value and assign the value to left hand side.
 */
int UtcDaliVector4OperatorDivisionAssignmentFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorFloatAssignmentP
 * @since_tizen     2.4
 * @description     Assign array of floats to a vector4.
 */
int UtcDaliVector4OperatorFloatAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_FLOAT_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorVector2AssignmentP
 * @since_tizen     2.4
 * @description     Assign vector4 to a vector4.
 */
int UtcDaliVector4OperatorVector2AssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_VECTOR2_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorVector3AssignmentP
 * @since_tizen     2.4
 * @description     Assign Vector4 to a vector3.
 */
int UtcDaliVector4OperatorVector3AssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_VECTOR3_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorEqualityP
 * @since_tizen     2.4
 * @description     Check equality between two operator.
 */
int UtcDaliVector4OperatorEqualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_EQUALITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4OperatorSubscriptP
 * @since_tizen     2.4
 * @description     Array subscript operator overload.
 */
int UtcDaliVector4OperatorSubscriptP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_OPERATOR_SUBSCRIPT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4ClampWithMinMaxP
 * @since_tizen     2.4
 * @description     Clamps the vector between minimum and maximum vectors.
 */
int UtcDaliVector4ClampWithMinMaxP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_CLAM_WITH_MIN_MAX_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4MinP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the minimum of the corresponding component in a and b.
 */
int UtcDaliVector4MinP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_MIN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector4MaxP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the maximum of the corresponding component in a and b.
 */
int UtcDaliVector4MaxP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector4_TestApp testApp( application, VECTOR4_MAX_P);
  application.MainLoop();
  return test_return_value;
}
