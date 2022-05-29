#include "utc-dali-constraints-common.h"

using namespace Dali;

namespace
{

  struct PropertyInputImpl : public PropertyInput
  {
    public:

      // Constants
      static const bool BOOLEAN_VALUE;
      static const float FLOAT_VALUE;
      static const int INTEGER_VALUE;
      static const unsigned int UNSIGNED_INTEGER_VALUE;
      static const Vector2 VECTOR2_VALUE;
      static const Vector3 VECTOR3_VALUE;
      static const Vector4 VECTOR4_VALUE;
      static const Matrix3 MATRIX3_VALUE;
      static const Matrix MATRIX_VALUE;
      static const Quaternion QUATERNION_VALUE;

      // Construction & Destruction
      PropertyInputImpl( Property::Type type ) : mType( type ) { }
      virtual ~PropertyInputImpl() { }

      // Methods
      Property::Type GetType() const { return mType; }

      // Virtual Methods
      virtual const bool& GetBoolean() const                 { return BOOLEAN_VALUE;          }
      virtual const float& GetFloat() const                  { return FLOAT_VALUE;            }
      virtual const int& GetInteger() const                  { return INTEGER_VALUE;          }
      virtual const unsigned int& GetUnsignedInteger() const { return UNSIGNED_INTEGER_VALUE; }
      virtual const Vector2& GetVector2() const              { return VECTOR2_VALUE;          }
      virtual const Vector3& GetVector3() const              { return VECTOR3_VALUE;          }
      virtual const Vector4& GetVector4() const              { return VECTOR4_VALUE;          }
      virtual const Matrix3& GetMatrix3() const              { return MATRIX3_VALUE;          }
      virtual const Matrix& GetMatrix() const                { return MATRIX_VALUE;           }
      virtual const Quaternion& GetQuaternion() const        { return QUATERNION_VALUE;       }

      // Data
      Property::Type mType;
  };

  const bool PropertyInputImpl::BOOLEAN_VALUE                  = true;
  const float PropertyInputImpl::FLOAT_VALUE                   = 123.0f;
  const int PropertyInputImpl::INTEGER_VALUE                   = 456;
  const unsigned int PropertyInputImpl::UNSIGNED_INTEGER_VALUE = 789u;
  const Vector2 PropertyInputImpl::VECTOR2_VALUE               = Vector2( 10.0f, 20.0f );
  const Vector3 PropertyInputImpl::VECTOR3_VALUE               = Vector3( 30.0f, 40.0f, 50.0f );
  const Vector4 PropertyInputImpl::VECTOR4_VALUE               = Vector4( 60.0f, 70.0f, 80.0f, 90.0f );
  const Matrix3 PropertyInputImpl::MATRIX3_VALUE               ( 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f );
  const Matrix PropertyInputImpl::MATRIX_VALUE                 = Matrix::IDENTITY;
  const Quaternion PropertyInputImpl::QUATERNION_VALUE         ( 1.0f, 2.0f, 3.0f, 4.0f );

  struct Vector3PropertyInput : public PropertyInputImpl
  {
    public:

      // Construction & Destruction
      Vector3PropertyInput( Vector3& value )
        : PropertyInputImpl( Property::VECTOR3 ),
        mValue( value )
    {
    }

      ~Vector3PropertyInput()
      {
      }

      const Vector3& GetVector3() const
      {
        return mValue;
      }

      // Data
      Vector3& mValue;
  };

  struct QuaternionPropertyInput : public PropertyInputImpl
  {
    public:

      // Construction & Destruction
      QuaternionPropertyInput( Quaternion& value )
        : PropertyInputImpl( Property::ROTATION ),
        mValue( value )
    {
    }

      ~QuaternionPropertyInput()
      {
      }

      const Quaternion& GetQuaternion() const
      {
        return mValue;
      }

      // Data
      Quaternion& mValue;
  };

} // unnamed namespace


extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Constraints
/**
 * @function            utc_Dali_Constraints_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Constraints_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Constraints_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Constraints_cleanup(void)
{
}

void ConstraintsEqualToConstraintConstructorP();
void ConstraintsEqualToConstraintForPropertyFloatP();
void ConstraintsEqualToConstraintForPropertyFloatP();
void ConstraintsEqualToConstraintForPropertyVector2P();
void ConstraintsEqualToConstraintForPropertyVector3P();
void ConstraintsEqualToConstraintForPropertyVector4P();
void ConstraintsEqualToConstraintForPropertyMatrix3P();
void ConstraintsEqualToConstraintForPropertyMatrixP();
void ConstraintsEqualToConstraintForPropertyQuaternionP();
void ConstraintsRelativeToConstraintForFloatScaleP();
void ConstraintsRelativeToConstraintForPropertyVector3P();
void ConstraintsRelativeToConstraintForPropertyFloatP();
void ConstraintsLookAtP();

namespace
{
  enum TEST_CASES_LIST_CONTRAINTS
  {
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_CONSTRUCTOR_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR2_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR4_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX3_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX_P,
    CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_QUATERNION_P,
    CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_FLOAT_SCALE_P,
    CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P,
    CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P,
    CONSTRAINTS_LOOK_AT_P
  };

  struct Constraints_TestApp : public ConnectionTracker
  {
    Constraints_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Constraints_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Constraints_TestApp::Tick );
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
        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_CONSTRUCTOR_P:
          ConstraintsEqualToConstraintConstructorP();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P:
          ConstraintsEqualToConstraintForPropertyFloatP();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR2_P:
          ConstraintsEqualToConstraintForPropertyVector2P();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P:
          ConstraintsEqualToConstraintForPropertyVector3P();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR4_P:
          ConstraintsEqualToConstraintForPropertyVector4P();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX3_P:
          ConstraintsEqualToConstraintForPropertyMatrix3P();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX_P:
          ConstraintsEqualToConstraintForPropertyMatrixP();
          break;

        case CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_QUATERNION_P:
          ConstraintsEqualToConstraintForPropertyQuaternionP();
          break;

        case CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_FLOAT_SCALE_P:
          ConstraintsRelativeToConstraintForFloatScaleP();
          break;

        case CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P:
          ConstraintsRelativeToConstraintForPropertyVector3P();
          break;

        case CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P:
          ConstraintsRelativeToConstraintForPropertyFloatP();
          break;

        case CONSTRAINTS_LOOK_AT_P:
          ConstraintsLookAtP();
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

void ConstraintsEqualToConstraintConstructorP()
{
  EqualToConstraint *equalConstraint = new EqualToConstraint();
  DALI_CHECK_FAIL((equalConstraint == NULL), "EqualToConstraint creation has failed" );

  DaliLog::PrintPass();
}


void ConstraintsEqualToConstraintForPropertyFloatP()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::FLOAT );
  propertyInput.PushBack( &propInput );

  float fValue = 0.0f;
  DALI_CHECK_FAIL( fValue == PropertyInputImpl::FLOAT_VALUE , "Initial value is not match with expected value for property container" );

  EqualToConstraint equalConstraint;
  equalConstraint( fValue, propertyInput );

  DALI_CHECK_FAIL( fValue != PropertyInputImpl::FLOAT_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyVector2P()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::VECTOR2 );
  propertyInput.PushBack( &propInput );

  Vector2 vec2Value (0.0f, 0.0f);
  DALI_CHECK_FAIL( vec2Value == PropertyInputImpl::VECTOR2_VALUE , "Initial value is not match with expected value for property container" );
  EqualToConstraint equalConstraint;
  equalConstraint( vec2Value, propertyInput );

  DALI_CHECK_FAIL( vec2Value != PropertyInputImpl::VECTOR2_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyVector3P()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::VECTOR3 );
  propertyInput.PushBack( &propInput );

  Vector3 vec3Value (0.0f, 0.0f, 0.0f);
  DALI_CHECK_FAIL( vec3Value == PropertyInputImpl::VECTOR3_VALUE , "Initial value is not match with expected value for property container" );

  EqualToConstraint equalConstraint;
  equalConstraint( vec3Value, propertyInput );

  DALI_CHECK_FAIL( vec3Value != PropertyInputImpl::VECTOR3_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyVector4P()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::VECTOR4 );
  propertyInput.PushBack( &propInput );

  Vector4 vec4Value (0.0f, 0.0f, 0.0f , 0.0f );
  DALI_CHECK_FAIL( vec4Value == PropertyInputImpl::VECTOR4_VALUE , "Initial value is not match with expected value for property container" );
  EqualToConstraint equalConstraint;
  equalConstraint( vec4Value, propertyInput );
  DALI_CHECK_FAIL( vec4Value != PropertyInputImpl::VECTOR4_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyMatrix3P()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::MATRIX3 );
  propertyInput.PushBack( &propInput );

  Matrix3 matValue;
  DALI_CHECK_FAIL( matValue == PropertyInputImpl::MATRIX3_VALUE , "Initial value is not match with expected value for property container" );
  EqualToConstraint equalConstraint;
  equalConstraint( matValue, propertyInput );
  DALI_CHECK_FAIL( matValue != PropertyInputImpl::MATRIX3_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyMatrixP()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::MATRIX );
  propertyInput.PushBack( &propInput );

  Matrix matValue;
  DALI_CHECK_FAIL( matValue == PropertyInputImpl::MATRIX_VALUE , "Initial value is not match with expected value for property container" );
  EqualToConstraint equalConstraint;
  equalConstraint( matValue, propertyInput );

  DALI_CHECK_FAIL( matValue != PropertyInputImpl::MATRIX_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsEqualToConstraintForPropertyQuaternionP()
{
  PropertyInputContainer propertyInput;
  PropertyInputImpl propInput( Property::ROTATION );
  propertyInput.PushBack( &propInput );

  Quaternion quatValue;
  DALI_CHECK_FAIL( quatValue == PropertyInputImpl::QUATERNION_VALUE , "Initial value is not match with expected value for property container" );
  EqualToConstraint equalConstraint;
  equalConstraint( quatValue, propertyInput );
  DALI_CHECK_FAIL( quatValue != PropertyInputImpl::QUATERNION_VALUE, "EqualToConstraint is not retrieved proper value" );

  DaliLog::PrintPass();
}

void ConstraintsLookAtP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL( !actor, "Actor::New is failed" );

  Vector3 vec3TargetPosition;
  Vector3 vec3CameraPosition;
  Quaternion quatTargetOrientation;

  Vector3PropertyInput targetPositionProperty( vec3TargetPosition );
  Vector3PropertyInput cameraPositionProperty( vec3CameraPosition );
  QuaternionPropertyInput targetOrientationProperty( quatTargetOrientation );

  PropertyInputContainer propertyInputs;
  propertyInputs.PushBack( &targetPositionProperty );
  propertyInputs.PushBack( &cameraPositionProperty );
  propertyInputs.PushBack( &targetOrientationProperty );

  Quaternion current;

  // 180 degrees round y
  vec3TargetPosition = Vector3::ZERO;
  vec3CameraPosition = Vector3( 0.0f, 0.0f, 1.0f );
  quatTargetOrientation = Quaternion::IDENTITY;
  Quaternion lookAtOrientation( Quaternion( Radian( Math::PI ), Vector3::YAXIS ) );
  LookAt( current, propertyInputs );
  DALI_CHECK_FAIL( current != lookAtOrientation, "LookAt api failed retrieve the value as expected" );

  DaliLog::PrintPass();
}

void ConstraintsRelativeToConstraintForFloatScaleP()
{
  float fScale( 0.2f );

  RelativeToConstraint relativeTo( fScale );
  DALI_CHECK_FAIL( relativeTo.mScale != Vector3( fScale, fScale, fScale ) , "Scale is not changed to required value.");
  DaliLog::PrintPass();
}

void ConstraintsRelativeToConstraintForPropertyVector3P()
{
  PropertyInputContainer propertyInputs;
  PropertyInputImpl input( Property::VECTOR3 );
  propertyInputs.PushBack( &input );

  Vector3 vec3Value;
  DALI_CHECK_FAIL( vec3Value != Vector3::ZERO, "Initial value is not get  as expected" );
  const Vector3 vec3Scale( 4.0f, 5.0f, 6.0f );
  RelativeToConstraint constraint( vec3Scale );
  constraint( vec3Value, propertyInputs );
  DALI_CHECK_FAIL( vec3Value != PropertyInputImpl::VECTOR3_VALUE * vec3Scale, "RelativeToConstraint is failed to get the proper relative value" );

  DaliLog::PrintPass();
}

void ConstraintsRelativeToConstraintForPropertyFloatP()
{
  PropertyInputContainer propertyInputs;
  PropertyInputImpl input( Property::FLOAT );

  DALI_CHECK_FAIL( input.GetExtension() != NULL , "GetExtension is failed to retrieve expected value" );

  propertyInputs.PushBack( &input );
  const float fScale( 4.0f );
  float fValue = 0.0f;
  DALI_CHECK_FAIL( fValue == PropertyInputImpl::FLOAT_VALUE * fScale ,"Initial value mismatch occur");
  RelativeToConstraintFloat constraint( fScale );
  constraint( fValue, propertyInputs );
  DALI_CHECK_FAIL( fValue != PropertyInputImpl::FLOAT_VALUE * fScale,"RelativeToConstraintFloat failed to get the proper relative value" );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliConstraintsEqualToConstraintConstructorP
 * @since_tizen     2.4
 * @description      Check for default constuctor
 */
int UtcDaliConstraintsEqualToConstraintConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyFloatP
 * @since_tizen     2.4
 * @description      Returns copy of the input property of type float.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyVector2P
 * @since_tizen     2.4
 * @description      Returns copy of the input property of type Vector2.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyVector3P
 * @since_tizen     2.4
 * @description      Returns copy of the input property of type Vector3.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyVector4P
 * @since_tizen     2.4
 * @description      Returns copy of the input property of type Vector4.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyMatrix3P
 * @since_tizen     2.4
 * @description     Returns copy of the input property of type Matrix3.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyMatrixP
 * @since_tizen     2.4
 * @description     Returns copy of the input property of type Matrix.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsEqualToConstraintForPropertyQuaternionP
 * @since_tizen     2.4
 * @description     Returns copy of the input property of type quaternion.
 */
int UtcDaliConstraintsEqualToConstraintForPropertyQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_EQUAL_TO_CONSTRAINT_FOR_PROPERTY_QUATERNION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintsLookAtP
 * @since_tizen     2.4
 * @description     To aim a camera at a target.
 */
int UtcDaliConstraintsLookAtP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_LOOK_AT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsRelativeToConstraintForFloatScaleP
 * @since_tizen     2.4
 * @description      Set the scale value of RelativeToConstraint.
 */
int UtcDaliConstraintsRelativeToConstraintForFloatScaleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_FLOAT_SCALE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliConstraintsRelativeToConstraintForPropertyVector3P
 * @since_tizen     2.4
 * @description     Returns copy of the input property of type vector3
 */
int UtcDaliConstraintsRelativeToConstraintForPropertyVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase        UtcDaliConstraintsRelativeToConstraintForPropertyFloatP
 * @since_tizen     2.4
 * @description     Returns copy of the input property of type float.
 */
int UtcDaliConstraintsRelativeToConstraintForPropertyFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Constraints_TestApp testApp( application, CONSTRAINTS_RELATIVE_TO_CONSTRAINT_FOR_PROPERTY_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


