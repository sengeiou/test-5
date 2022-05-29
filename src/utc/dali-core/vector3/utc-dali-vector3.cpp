#include "utc-dali-vector3-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Vector3
/**
 * @function           utc_Dali_Vector3_startup
 * @description        Called before each test
 * @parameter          NA
 * @return             NA
 */
void utc_Dali_Vector3_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Vector3_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Vector3_cleanup(void)
{

}

void Vector3ConstructorP();
void Vector3ConstrucAndGetAsFloatP();
void Vector3ConstructArrayAndGetAsConstFloatP();
void Vector3Vec2ConstructAndAssignP();
void Vector3Vec4ConstructAndAssignP();
void Vector3CrossP();
void Vector3DotP();
void Vector3ClampP();
void Vector3GetVectorXYP();
void Vector3GetVectorYZP();
void Vector3OperatorInequalityP();
void Vector3OperatorMultiplicationAndAssignmentP();
void Vector3OperatorMultiplicationAssignmentFloatP();
void Vector3OperatorAdditionAndAssignmentP();
void Vector3OperatorSubtractionAndAssignmentP();
void Vector3OperatorUnaryNegationP();
void Vector3OperatorDivisionAndAssignmentP();
void Vector3OperatorDivisionAssignmentFloatP();
void Vector3OperatorFloatAssignmentP();
void Vector3OperatorEqualityP();
void Vector3OperatorSubscriptP();
void Vector3NormalizeWithLengthAndLengthSquaredP();
void Vector3GetVectorXYConstP();
void Vector3GetVectorYZConstP();
void Vector3OperatorMultiplicationAssignmentQuaternionP();
void Vector3OperatorArraySubscriptP();
void Vector3ClampWithMinMaxP();
void Vector3MinP();
void Vector3MaxP();


namespace
{
  enum TEST_CASES_LIST_VECTOR3
  {
    VECTOR3_CONSTRUCTOR_P,
    VECTOR3_CONSTRUCT_GET_AS_FLOAT_P,
    VECTOR3_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P,
    VECTOR3_VEC2_CONSTRUCT_AND_ASSIGN_P,
    VECTOR3_VEC4_CONSTRUCT_AND_ASSIGN_P,
    VECTOR3_CROSS_P,
    VECTOR3_DOT_P,
    VECTOR3_CLAMP_P,
    VECTOR3_GET_VECOR_XY_P,
    VECTOR3_GET_VECTOR_YZ_P,
    VECTOR3_OPERATOR_INEQUALITY_P,
    VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P,
    VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P,
    VECTOR3_OPERATOR_ADDITION_AND_ASSIGNMENT_P,
    VECTOR3_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P,
    VECTOR3_OPERATOR_UNARY_NEGATION_P,
    VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_P,
    VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P,
    VECTOR3_OPERATOR_FLOAT_ASSIGNMENT_P,
    VECTOR3_OPERATOR_EQUALITY_P,
    VECTOR3_OPERATOR_SUBSCRIPT_P,
    VECTOR3_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P,
    VECTOR3_GET_VECTOR_XY_CONST_P,
    VECTOR3_GET_VECTOR_YZ_CONST_P,
    VECTOR3_OPERATOR_MULTIPLICATION_ASSIGNMENT_QUATERNION_P,
    VECTOR3_OPERATOR_ARRAY_SUBSCRIPT_P,
    VECTOR3_CLAM_WITH_MIN_MAX_P,
    VECTOR3_MIN_P,
    VECTOR3_MAX_P
  };

  struct Vector3_TestApp : public ConnectionTracker
  {
    Vector3_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Vector3_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Vector3_TestApp::Tick );
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
        case VECTOR3_CONSTRUCTOR_P:
          Vector3ConstructorP();
          break;
        case VECTOR3_CONSTRUCT_GET_AS_FLOAT_P:
          Vector3ConstrucAndGetAsFloatP();
          break;
        case VECTOR3_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P:
          Vector3ConstructArrayAndGetAsConstFloatP();
          break;
        case VECTOR3_VEC2_CONSTRUCT_AND_ASSIGN_P:
          Vector3Vec2ConstructAndAssignP();
          break;
        case VECTOR3_VEC4_CONSTRUCT_AND_ASSIGN_P:
          Vector3Vec4ConstructAndAssignP();
          break;
        case VECTOR3_CROSS_P:
          Vector3CrossP();
          break;
        case VECTOR3_DOT_P:
          Vector3DotP();
          break;
        case VECTOR3_CLAMP_P:
          Vector3ClampP();
          break;
        case VECTOR3_GET_VECOR_XY_P:
          Vector3GetVectorXYP();
          break;
        case VECTOR3_GET_VECTOR_YZ_P:
          Vector3GetVectorYZP();
          break;
        case VECTOR3_OPERATOR_INEQUALITY_P:
          Vector3OperatorInequalityP();
          break;
        case VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P:
          Vector3OperatorMultiplicationAndAssignmentP();
          break;
        case VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P:
          Vector3OperatorMultiplicationAssignmentFloatP();
          break;
        case VECTOR3_OPERATOR_ADDITION_AND_ASSIGNMENT_P:
          Vector3OperatorAdditionAndAssignmentP();
          break;
        case VECTOR3_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P:
          Vector3OperatorSubtractionAndAssignmentP();
          break;
        case VECTOR3_OPERATOR_UNARY_NEGATION_P:
          Vector3OperatorUnaryNegationP();
          break;
        case VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_P:
          Vector3OperatorDivisionAndAssignmentP();
          break;
        case VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P:
          Vector3OperatorDivisionAssignmentFloatP();
          break;
        case VECTOR3_OPERATOR_FLOAT_ASSIGNMENT_P:
          Vector3OperatorFloatAssignmentP();
          break;
        case VECTOR3_OPERATOR_EQUALITY_P:
          Vector3OperatorEqualityP();
          break;
        case VECTOR3_OPERATOR_SUBSCRIPT_P:
          Vector3OperatorSubscriptP();
          break;
        case VECTOR3_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P:
          Vector3NormalizeWithLengthAndLengthSquaredP();
          break;
        case VECTOR3_GET_VECTOR_XY_CONST_P:
          Vector3GetVectorXYConstP();
          break;
        case VECTOR3_GET_VECTOR_YZ_CONST_P:
          Vector3GetVectorYZConstP();
          break;
        case VECTOR3_OPERATOR_MULTIPLICATION_ASSIGNMENT_QUATERNION_P:
          Vector3OperatorMultiplicationAssignmentQuaternionP();
          break;
        case VECTOR3_OPERATOR_ARRAY_SUBSCRIPT_P:
          Vector3OperatorArraySubscriptP();
          break;
        case VECTOR3_CLAM_WITH_MIN_MAX_P:
          Vector3ClampWithMinMaxP();
          break;
        case VECTOR3_MIN_P:
          Vector3MinP();
          break;
        case VECTOR3_MAX_P:
          Vector3MaxP();
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

void Vector3ConstructorP()
{
  float fVecX = 0.0f, fVecY = 0.0f, fVecZ = 0.0f;

  Vector3 vec3;

  DALI_CHECK_FAIL( ( vec3.x != fVecX ) || ( vec3.y != fVecY ) || ( vec3.z != fVecZ ) , "Vector3 api is failed to create constructor with default values.");

  DaliLog::PrintPass();
}

void Vector3ConstrucAndGetAsFloatP()
{
  float fVecX = 0.0f, fVecY = 2.0f, fVecZ = 3.0f;
  float *rgfpValue = NULL;

  Vector3 vec3( fVecX, fVecY, fVecZ );

  DALI_CHECK_FAIL( ( vec3.x != fVecX ) || ( vec3.y != fVecY ) || ( vec3.z != fVecZ ) , "Vector3 api is failed to create constructor with given float values.");

  rgfpValue = vec3.AsFloat();

  DALI_CHECK_FAIL( ( vec3.x != rgfpValue[0] ) || ( vec3.y != rgfpValue[1] ) || ( vec3.z != rgfpValue[2] ) , "AsFloat is failed to retrieve value of Vector3 as an array.");

  DaliLog::PrintPass();
}

void Vector3ConstructArrayAndGetAsConstFloatP()
{
  float rgfValues[] = { 0.0f, 1.0f, 2.0f };

  const Vector3 vec3( rgfValues );

  DALI_CHECK_FAIL( ( vec3.x != rgfValues[0] ) || ( vec3.y != rgfValues[1] ) || ( vec3.z != rgfValues[2] ) , "Vector3 api is failed create constructor with given value.");

  const float *rgfpValue = vec3.AsFloat();

  DALI_CHECK_FAIL( ( vec3.x != rgfpValue[0] ) || ( vec3.y != rgfpValue[1] ) , "AsFloat()const api is failed to retrieve values of Vector3 as an array of 3 float values.");

  DaliLog::PrintPass();
}

void Vector3Vec2ConstructAndAssignP()
{
  float fValX = 1.0f, fValY  = 3.0f;

  Vector2 vec2( fValX, fValY );
  Vector3 vec3Construct( vec2 );

  DALI_CHECK_FAIL( ( vec3Construct.x != vec2.x ) || ( vec3Construct.y != vec2.y ) || ( vec3Construct.z != 0.0f ) , "Vector3 api is failed to create constructor with given value.");

  Vector3 vec3Assign;
  vec3Assign = vec2;

  DALI_CHECK_FAIL( ( vec3Assign.x != vec2.x ) || ( vec3Assign.y != vec2.y ) || ( vec3Assign.z != 0.0f ) , "Assignment operator failed to assign Vector3 values to Vector3.");
  DALI_CHECK_FAIL( vec3Assign != vec3Construct , "Constructed and assigned Vector3 with same Vector2 values, so the vectors must be same.");

  DaliLog::PrintPass();
}

void Vector3Vec4ConstructAndAssignP()
{
  float fValX = 1.0f, fValY  = 3.0f, fValZ  = 3.0f, fValW = 4.0f;

  Vector4 vec4( fValX, fValY, fValZ, fValW );
  Vector3 vec3Construct( vec4 );

  DALI_CHECK_FAIL( ( vec3Construct.x != vec4.x ) || ( vec3Construct.y != vec4.y ) || ( vec3Construct.z != vec4.z ) , "Vector3 api is failed to create constructor with given value.");

  Vector3 vec3Assign( 0.0f, 0.0f, 0.0f );
  vec3Assign = vec4;

  DALI_CHECK_FAIL( ( vec3Assign.x != vec4.x ) || ( vec3Assign.y != vec4.y ) || ( vec3Assign.z != vec4.z ) , "Assignment operator failed to assign Vector4 values to Vector3.");
  DALI_CHECK_FAIL( vec3Assign != vec3Construct , "Constructed and assigned Vector3 with same Vector4 values must be same.");

  DaliLog::PrintPass();
}

void Vector3CrossP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;

  Vector3 vec3Value1( fValue1X, fValue1Y, fValue1Z );

  if( !vector3IsApplicable( vec3Value1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Value2( fValue2X, fValue2Y, fValue2Z );
  if( !vector3IsApplicable( vec3Value2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3CrossResult( ( vec3Value1.y*vec3Value2.z - vec3Value1.z*vec3Value2.y ),
      ( vec3Value1.z*vec3Value2.x - vec3Value1.x*vec3Value2.z ),
      ( vec3Value1.x*vec3Value2.y - vec3Value1.y*vec3Value2.x ) );
  if( !vector3IsApplicable( vec3CrossResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( 0.00f, 0.00f, 0.00f );

  vec3Result = vec3Value1.Cross( vec3Value2 );

  DALI_CHECK_FAIL( vec3CrossResult != vec3Result , "Cross is failed to produce cross product of two vectors.");
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3DotP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;

  float fDotResult;
  float fResult;

  Vector3 vec3Value1( fValue1X, fValue1Y, fValue1Z );

  if( !vector3IsApplicable( vec3Value1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Value2( fValue2X, fValue2Y, fValue2Z );

  if( !vector3IsApplicable( vec3Value2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  fDotResult =  vec3Value1.x*vec3Value2.x + vec3Value1.y*vec3Value2.y + vec3Value1.z*vec3Value2.z;
  fResult = 0.0f;

  fResult = vec3Value1.Dot( vec3Value2 );

  DALI_CHECK_FAIL( fResult != fDotResult , "Dot is failed to produce dot product of two vectors.");

  DaliLog::PrintPass();
}

void Vector3ClampP()
{
  float fValueX = 11.0f, fValueY = 2.0f, fValueZ = 4.0f;
  float fMinX = 1.0f, fMinY = 3.0f, fMinZ =  2.0f;
  float fMaxX = 10.0f, fMaxY = 13.0f, fMaxZ =  5.0f;

  Vector3 vec3ClampResult( 10.0f, 3.0f, 4.0f );

  Vector3 vec3Values( fValueX, fValueY, fValueZ );

  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Min( fMinX, fMinY, fMinZ );
  if( !vector3IsApplicable( vec3Min ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Max( fMaxX, fMaxY, fMaxZ );
  if( !vector3IsApplicable( vec3Max ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3ClampResult.x = ( vec3Values.x>=vec3Min.x && vec3Values.x<=vec3Max.x )?( vec3Values.x ):( ( fabsf( vec3Values.x - vec3Min.x ) < fabsf( vec3Values.x - vec3Max.x ) )?vec3Min.x:vec3Max.x );
  vec3ClampResult.y = ( vec3Values.y>=vec3Min.y && vec3Values.y<=vec3Max.y )?( vec3Values.y ):( ( fabsf( vec3Values.y - vec3Min.y ) < fabsf( vec3Values.y - vec3Max.y ) )?vec3Min.y:vec3Max.y );
  vec3ClampResult.z = ( vec3Values.z>=vec3Min.z && vec3Values.z<=vec3Max.z )?( vec3Values.z ):( ( fabsf( vec3Values.z - vec3Min.z ) < fabsf( vec3Values.z - vec3Max.z ) )?vec3Min.z:vec3Max.z );

  vec3Values.Clamp( vec3Min, vec3Max );

  DALI_CHECK_FAIL( vec3ClampResult != vec3Values , "Clamp is failed to Clamp the vector between minimum and maximum vectors.");
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3GetVectorXYP()
{
  float fValueX = 3.0f, fValueY = 2.0f, fValueZ = 4.0f;

  Vector3 vec3Value( fValueX, fValueY, fValueZ );
  if( !vector3IsApplicable( vec3Value ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector2 vec2Result( fValueX, fValueY );
  Vector2 vec2GetResult( 0.00f, 0.00f );

  vec2GetResult = vec3Value.GetVectorXY();

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "GetVectorXY is failed to get x, y component of as a vector2.");

  DaliLog::PrintPass();
}

void Vector3GetVectorYZP()
{
  float fValueX = 3.0f, fValueY = 2.0f, fValueZ = 4.0f;

  Vector3 vec3Value( fValueX, fValueY, fValueZ );
  if( !vector3IsApplicable( vec3Value ) )
  {
    test_return_value=TC_FAIL;
    return;
  }
  Vector2 vec2Result( fValueY, fValueZ );
  Vector2 vec2GetResult( 0.00f, 0.00f );

  vec2GetResult = vec3Value.GetVectorYZ();

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "GetVectorYZ is failed to get Y, Z components of as a vector2.");

  DaliLog::PrintPass();
}

void Vector3OperatorInequalityP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  bool bInequal = false;
  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );

  if( !vector3IsApplicable( vec3Values1 ) || !vector3IsApplicable( vec3Values2 )  )
  {
    test_return_value=TC_FAIL;
    return;
  }

  bInequal = ( vec3Values1 != vec3Values2 );

  DALI_CHECK_FAIL( !bInequal , "Operator!= Api failed to return correct value.");

  DaliLog::PrintPass();
}

void Vector3OperatorMultiplicationAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );
  if( !vector3IsApplicable( vec3Values2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  //  Expected calculation of multiplication  of 2 vector
  Vector3 vec3Result( ( fValue1X*fValue2X ), ( fValue1Y*fValue2Y ),( fValue1Z*fValue2Z ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values1 * vec3Values2;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "operator* Api failed multiply two vector.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values1 *= vec3Values2;

  DALI_CHECK_FAIL( vec3Values1 != vec3Result , "Operator*= Api failed to multiply two vector and assign the value to left hand side.");
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorMultiplicationAssignmentFloatP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fScaleVal = 3.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( ( fValue1X*fScaleVal ), ( fValue1Y*fScaleVal ),( fValue1Z*fScaleVal ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values * fScaleVal;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "Operator* Api failed to multiply a vector with a float value.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values *= fScaleVal;

  DALI_CHECK_FAIL( vec3Values != vec3Result , "operator*= Api failed to multiply a vector with a float value.");
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorAdditionAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );
  if( !vector3IsApplicable( vec3Values2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( ( fValue1X+fValue2X ), ( fValue1Y+fValue2Y ),( fValue1Z+fValue2Z ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values1 + vec3Values2;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "perator+ Api failed to add two vector.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values1 += vec3Values2;

  DALI_CHECK_FAIL( vec3Values1 != vec3Result , "operator+= Api failed to add two vector and assign the value to left hand side.");
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorSubtractionAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 3.0f, fValue1Z = 5.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );
  if( !vector3IsApplicable( vec3Values2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( ( fValue1X-fValue2X ), ( fValue1Y-fValue2Y ),( fValue1Z-fValue2Z ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values1 - vec3Values2;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "operator- Api failed to Subtract two vector.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values1 -= vec3Values2;

  DALI_CHECK_FAIL( vec3Values1 != vec3Result , "operator-= Api failed to Subtract two vector and assign the value to left hand side.");
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorUnaryNegationP()
{
  float fValue1X = 3.0f, fValue1Y = 3.0f, fValue1Z = 5.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( -fValue1X, -fValue1Y, -fValue1Z );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = ( -vec3Values );

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "operator-() Api failed to negate vector.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorDivisionAndAssignmentP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 2.0f, fValue2Y = 3.0f, fValue2Z = 4.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );
  if( !vector3IsApplicable( vec3Values2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( ( fValue1X/fValue2X ), ( fValue1Y/fValue2Y ),( fValue1Z/fValue2Z ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values1 / vec3Values2;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "Operator/ Api failed to divide two vectors.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values1 /= vec3Values2;

  DALI_CHECK_FAIL( vec3Values1 != vec3Result , "Operator/= Api failed to divide two vector and assign the value to left hand side.");
  if( !vector3IsApplicable( vec3Values1 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorDivisionAssignmentFloatP()
{
  float fValue1X = 4.0f, fValue1Y = 4.0f, fValue1Z = 4.0f;
  float fScaleVal = 2.0f;
  Vector3 vec3GetResult;

  Vector3 vec3Values( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Result( ( fValue1X/fScaleVal ), ( fValue1Y/fScaleVal ),( fValue1Z/fScaleVal ) );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3GetResult = vec3Values / fScaleVal;

  DALI_CHECK_FAIL( vec3GetResult != vec3Result , "OperatorDivisionFloat Api failed to divide a vector with a float value.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values /= fScaleVal;

  DALI_CHECK_FAIL( vec3Values != vec3Result , "Operator/= Api failed to divide a vector with a float value.");
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorFloatAssignmentP()
{
  float rgfpValues[3] = {2.0f, 2.0f, 2.0f};

  Vector3 vec3Values;
  Vector3 vec3Result = Vector3( rgfpValues[0], rgfpValues[1], rgfpValues[2] );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values = rgfpValues;

  DALI_CHECK_FAIL( vec3Values != vec3Result , "Operator= is failed to assign array of floats to vector3.");
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorEqualityP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 4.0f;
  float fValue2X = 3.0f, fValue2Y = 2.0f, fValue2Z = 4.0f;
  bool bEqual = false;
  Vector3 vec3Values1( fValue1X, fValue1Y, fValue1Z );
  Vector3 vec3Values2( fValue2X, fValue2Y, fValue2Z );

  if( !vector3IsApplicable( vec3Values1 ) || !vector3IsApplicable( vec3Values2 ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  bEqual = ( vec3Values1 == vec3Values2 );

  DALI_CHECK_FAIL( !bEqual , "Operator== Api failed to return correct result.");

  DaliLog::PrintPass();
}

void Vector3OperatorSubscriptP()
{
  int nIndex = 0;
  float rgfValue[3] = { 1.0f, 2.0f, 3.0f };
  float fRetValue = 0.0f;

  Vector3 vec3Values( rgfValue );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  fRetValue = 0.0f;

  fRetValue = vec3Values[nIndex];

  DALI_CHECK_FAIL( fRetValue != rgfValue[nIndex] , "Failed to return correct value.");

  DaliLog::PrintPass();
}

void Vector3NormalizeWithLengthAndLengthSquaredP()
{
  float fValue1X = 3.0f, fValue1Y = 2.0f, fValue1Z = 3.0f;
  float fUnitLength = 1.0f, fRetVal = 0.0f, fLengthVal = -1.0f, fVecLength = -1.0f, fVecLengthSquared = -1.0f;
  Vector3 vec3NormalizedVal( -1.0f, -1.0f, -1.0f );

  Vector3 vec3Values( fValue1X, fValue1Y, fValue1Z );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  //  Calculation for length according to definition
  fVecLength = sqrtf( vec3Values.x*vec3Values.x + vec3Values.y*vec3Values.y + vec3Values.z*vec3Values.z );
  fLengthVal = -1.0f;

  //  Find length of the vector
  fLengthVal = vec3Values.Length();

  DALI_CHECK_FAIL(  !Equals( fLengthVal, fVecLength, VECTOR3_MATH_EPSILON ), "Length Api failed to return the length of the vector.");

  //  Calculated Normalized Value.
  vec3NormalizedVal.x  =  vec3Values.x/fLengthVal;
  vec3NormalizedVal.y  =  vec3Values.y/fLengthVal;
  vec3NormalizedVal.z  =  vec3Values.z/fLengthVal;

  vec3Values.Normalize();

  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  //  Calculation for length according to definition
  fVecLengthSquared = vec3Values.x*vec3Values.x + vec3Values.y*vec3Values.y + vec3Values.z*vec3Values.z;
  fRetVal = -1;

  fRetVal = vec3Values.LengthSquared();

  DALI_CHECK_FAIL(  fVecLengthSquared != fRetVal , "LengthSquared Api failed to return expected result.");
  DALI_CHECK_FAIL( vec3Values  !=  vec3NormalizedVal , "Failed to normalize vector3");
  DALI_CHECK_FAIL( !Equals( fRetVal, fUnitLength, VECTOR3_MATH_EPSILON ) , "Failed to meet unit length criteria for normalized vector.");

  DaliLog::PrintPass();
}

void Vector3GetVectorXYConstP()
{
  float fValueX = 3.0f, fValueY = 2.0f, fValueZ = 4.0f;

  const Vector3 vec3Value( fValueX, fValueY, fValueZ );
  const Vector2 vec2Result( fValueX, fValueY );

  const Vector2 vec2GetResult = vec3Value.GetVectorXY();

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "GetVectorXY is failed to get x, y component of vector3 as a vector2.");

  DaliLog::PrintPass();
}

void Vector3GetVectorYZConstP()
{
  float fValueX = 3.0f, fValueY = 2.0f, fValueZ = 4.0f;

  const Vector3 vec3Value( fValueX, fValueY, fValueZ );
  const Vector2 vec2Result( fValueY, fValueZ );

  const Vector2 vec2GetResult = vec3Value.GetVectorYZ();

  DALI_CHECK_FAIL( vec2GetResult != vec2Result , "GetVectorYZ is failed to get Y, Z components of as a vector2.");

  DaliLog::PrintPass();
}

void Vector3OperatorMultiplicationAssignmentQuaternionP()
{
  Vector3 vec3MathEps( 0.001f, 0.001f, 0.001f );

  Vector3 vec3Value( Vector3::YAXIS );
  if( !vector3IsApplicable( vec3Value ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Radian radian(Math::PI_2);
  Quaternion quatRotation( radian, Vector3::ZAXIS );

  Vector3 vec3Result( -Vector3::XAXIS );
  if( !vector3IsApplicable( vec3Result ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Value *= quatRotation;

  DALI_CHECK_FAIL( ( ( vec3Value.x - vec3Result.x ) > vec3MathEps.x ) || ( ( vec3Value.y - vec3Result.y ) > vec3MathEps.y ) || ( ( vec3Value.z - vec3Result.z ) > vec3MathEps.z ) , "Operator*= Api failed to multiply Vector3 with Quaternion and assign the value to left hand side.");
  if( !vector3IsApplicable( vec3Value ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3OperatorArraySubscriptP()
{
  float rgfValue[] = {3.0f, 2.0f, 4.0f};
  int nIndex = 0;

  Vector3 vec3Values( rgfValue[0], rgfValue[1], rgfValue[2] );
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  float fResult;
  fResult = vec3Values[nIndex];

  DALI_CHECK_FAIL( fabs( fResult - rgfValue[nIndex] ) > 0.00001f , "Operator[] Api failed to retrieve correct value for given index.");

  DaliLog::PrintPass();
}

void Vector3ClampWithMinMaxP()
{
  float fValueX = 11.0f, fValueY = 2.0f, fValueZ = 4.0f;
  float fMin = 1.0f, fMax = 10.0f;

  Vector3 vec3ClampResult( 10.0f, 3.0f, 4.0f );

  Vector3 vec3Values( fValueX, fValueY, fValueZ );
  Vector3 vec3GetResult( -1.0f, -1.0f, -1.0f );

  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Min( fMin, fMin, fMin );

  if( !vector3IsApplicable( vec3Min ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  Vector3 vec3Max( fMax, fMax, fMax );

  if( !vector3IsApplicable( vec3Max ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  // Calculate values according to clamping process
  vec3ClampResult.x = ( vec3Values.x>=vec3Min.x && vec3Values.x<=vec3Max.x )?( vec3Values.x ):( ( fabsf( vec3Values.x - vec3Min.x ) < fabsf( vec3Values.x - vec3Max.x ) )?vec3Min.x:vec3Max.x );
  vec3ClampResult.y = ( vec3Values.y>=vec3Min.y && vec3Values.y<=vec3Max.y )?( vec3Values.y ):( ( fabsf( vec3Values.y - vec3Min.y ) < fabsf( vec3Values.y - vec3Max.y ) )?vec3Min.y:vec3Max.y );
  vec3ClampResult.z = ( vec3Values.z>=vec3Min.z && vec3Values.z<=vec3Max.z )?( vec3Values.z ):( ( fabsf( vec3Values.z - vec3Min.z ) < fabsf( vec3Values.z - vec3Max.z ) )?vec3Min.z:vec3Max.z );

  vec3GetResult = Clamp( vec3Values, fMin, fMax );

  DALI_CHECK_FAIL( vec3ClampResult != vec3GetResult , "Clamp api is failed to Clamp the vector between minimum and maximum values.");
  if( !vector3IsApplicable( vec3GetResult ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  vec3Values.Clamp(vec3Min, vec3Max);

  DALI_CHECK_FAIL( vec3ClampResult != vec3Values , "Clamp api is failed to Clamp the vector between minimum and maximum values.");
  if( !vector3IsApplicable( vec3Values ) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void Vector3MinP()
{
  Vector3 vec3Values1( 10.0f, 11.0f, 2.0f );
  Vector3 vec3Values2( 5.0f, 10.0f, 1.0f );

  // Calculation of minimum value
  Vector3 vec3CalResult( min( vec3Values1.x, vec3Values2.x ), min( vec3Values1.y, vec3Values2.y ), min( vec3Values1.z, vec3Values2.z ) );

  Vector3 vec3GetResult = Min( vec3Values1, vec3Values2 );

  DALI_CHECK_FAIL( vec3GetResult != vec3CalResult , "Min Api failed to return correct value.");
  DALI_CHECK_FAIL( vec3GetResult.x > vec3Values1.x || vec3GetResult.x > vec3Values2.x || vec3GetResult.y > vec3Values1.y || vec3GetResult.y > vec3Values2.y || vec3GetResult.z > vec3Values1.z || vec3GetResult.z > vec3Values2.z , "Returning Vector3 is not minimum for all components.");

  DaliLog::PrintPass();
}

void Vector3MaxP()
{
  Vector3 vec3Values1( 10.0f, 11.0f, 2.0f );
  Vector3 vec3Values2( 5.0f, 10.0f, 1.0f );
  Vector3 vec3CalResult( max( vec3Values1.x, vec3Values2.x ), max( vec3Values1.y, vec3Values2.y ), max( vec3Values1.z, vec3Values2.z ) );

  Vector3 vec3GetResult = Max( vec3Values1, vec3Values2 );

  DALI_CHECK_FAIL( vec3GetResult != vec3CalResult , "Max Api failed to return correct value.");
  DALI_CHECK_FAIL( vec3GetResult.x < vec3Values1.x || vec3GetResult.x < vec3Values2.x || vec3GetResult.y < vec3Values1.y || vec3GetResult.y < vec3Values2.y || vec3GetResult.z < vec3Values1.z || vec3GetResult.z < vec3Values2.z , "Returning Vector3 id not maximum for all components.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase        UtcDaliVector3ConstructorP
 * @since_tizen     2.4
 * @description     Construct a vector with default constructor.
 */
int UtcDaliVector3ConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3ConstrucAndGetAsFloatP
 * @since_tizen     2.4
 * @description     Construct a vector with 3 float value and retrieve the values of Vector3 as an array of two float value.
 */
int UtcDaliVector3ConstrucAndGetAsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CONSTRUCT_GET_AS_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3ConstructArrayAndGetAsConstFloatP
 * @since_tizen     2.4
 * @description     Construct a vector with an array values and retrieve the values as an array of 3 float values.
 */
int UtcDaliVector3ConstructArrayAndGetAsConstFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CONSTRUCT_ARRAY_GET_AS_CONST_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3Vec2ConstructAndAssignP
 * @since_tizen     2.4
 * @description     Construct a vector with Vector2 and assigned a Vector3 with Vector2 values.
 */
int UtcDaliVector3Vec2ConstructAndAssignP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_VEC2_CONSTRUCT_AND_ASSIGN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3Vec4ConstructAndAssignP
 * @since_tizen     2.4
 * @description     Construct a vector with Vector4 and assigned a Vector3 with Vector4 values.
 */
int UtcDaliVector3Vec4ConstructAndAssignP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_VEC4_CONSTRUCT_AND_ASSIGN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3CrossP
 * @since_tizen     2.4
 * @description     Produce the cross product of two vectors.
 */
int UtcDaliVector3CrossP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CROSS_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3DotP
 * @since_tizen     2.4
 * @description     Produce the dot product of two vectors.
 */
int UtcDaliVector3DotP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_DOT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3ClampP
 * @since_tizen     2.4
 * @description     Clamps the vector between minimum and maximum vectors.
 */
int UtcDaliVector3ClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CLAMP_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3GetVectorXYP
 * @since_tizen     2.4
 * @description     Get the X, Y components of vector3 as a vector2.
 */
int UtcDaliVector3GetVectorXYP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_GET_VECOR_XY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3GetVectorYZP
 * @since_tizen   2.4.
 * @description     Get the Y, Z components of vector3 as a vector2.
 */
int UtcDaliVector3GetVectorYZP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_GET_VECTOR_YZ_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorInequalityP
 * @since_tizen     2.4
 * @description     Check inequality between two Vector3.
 */
int UtcDaliVector3OperatorInequalityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_INEQUALITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorMultiplicationAndAssignmentP
 * @since_tizen     2.4
 * @description     Multiply two vector.
 */
int UtcDaliVector3OperatorMultiplicationAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector3OperatorMultiplicationAssignmentFloatP
 * @since_tizen     2.4
 * @description     Multiply vector with a float value and assign the value to left hand side.
 */
int UtcDaliVector3OperatorMultiplicationAssignmentFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_MULTIPLICATION_AND_ASSIGNMENT_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorAdditionAndAssignmentP
 * @since_tizen     2.4
 * @description     Add two vector.
 */
int UtcDaliVector3OperatorAdditionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_ADDITION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector3OperatorSubtractionAndAssignmentP
 * @since_tizen     2.4
 * @description     Subtract two vector.
 */
int UtcDaliVector3OperatorSubtractionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_SUBTRUCTION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector3OperatorUnaryNegationP
 * @since_tizen     2.4
 * @description     Provide negation of a vector.
 */
int UtcDaliVector3OperatorUnaryNegationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_UNARY_NEGATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorDivisionAndAssignmentP
 * @since_tizen     2.4
 * @description     Divide two vector.
 */
int UtcDaliVector3OperatorDivisionAndAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector3OperatorDivisionAssignmentFloatP
 * @since_tizen     2.4
 * @description     Divide vector with a float value and assign the value to left hand side.
 */
int UtcDaliVector3OperatorDivisionAssignmentFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_DIVISION_AND_ASSIGNMENT_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorFloatAssignmentP
 * @since_tizen     2.4
 * @description     Assign array of floats to a vector3.
 */
int UtcDaliVector3OperatorFloatAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_FLOAT_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorEqualityP
 * @since_tizen     2.4
 * @description     Check equality between two vector.
 */
int UtcDaliVector3OperatorEqualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_EQUALITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorSubscriptP
 * @since_tizen     2.4
 * @description     Array subscript operator overload.
 */
int UtcDaliVector3OperatorSubscriptP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_SUBSCRIPT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliVector3NormalizeWithLengthAndLengthSquaredP
 * @since_tizen     2.4
 * @description     Sets the vector to be unit length, whilst maintaining its direction.
 */
int UtcDaliVector3NormalizeWithLengthAndLengthSquaredP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_NORMALIZAE_WITH_LENGTH_AND_LENGTH_SQUARED_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3GetVectorXYConstP
 * @since_tizen     2.4
 * @description     Get the X, Y components of vector3 as a const vector2.
 */
int UtcDaliVector3GetVectorXYConstP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_GET_VECTOR_XY_CONST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3GetVectorYZConstP
 * @since_tizen     2.4
 * @description     Get the Y, Z components of vector3 as a const vector2.
 */
int UtcDaliVector3GetVectorYZConstP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_GET_VECTOR_YZ_CONST_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorMultiplicationAssignmentQuaternionP
 * @since_tizen     2.4
 * @description     Multiply Vector3 with Quaternion
 */
int UtcDaliVector3OperatorMultiplicationAssignmentQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_MULTIPLICATION_ASSIGNMENT_QUATERNION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3OperatorArraySubscriptP
 * @since_tizen     2.4
 * @description     Mutable array subscript operator overload.
 */
int UtcDaliVector3OperatorArraySubscriptP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_OPERATOR_ARRAY_SUBSCRIPT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3ClampWithMinMaxP
 * @since_tizen     2.4
 * @description     Clamps the vector between minimum and maximum vectors.
 */
int UtcDaliVector3ClampWithMinMaxP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_CLAM_WITH_MIN_MAX_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3MinP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the minimum of the corresponding component in a and b.
 */
int UtcDaliVector3MinP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_MIN_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliVector3MaxP
 * @since_tizen     2.4
 * @description     Returns a vector with components set to the maximum of the corresponding component in a and b.
 */
int UtcDaliVector3MaxP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Vector3_TestApp testApp( application, VECTOR3_MAX_P);
  application.MainLoop();
  return test_return_value;
}
