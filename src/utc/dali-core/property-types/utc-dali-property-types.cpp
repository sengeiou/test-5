#include "utc-dali-property-types-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_PropertyTypes_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyTypes_startup(void)
{
  test_return_value =0;
}

/**
 * @function            utc_Dali_PropertyTypes_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyTypes_cleanup(void)
{

}

void PropertyTypesGetName();
void PropertyTypesBoolean();
void PropertyTypesFloat();
void PropertyTypesInt();
void PropertyTypesVector2();
void PropertyTypesVector3();
void PropertyTypesVector4();
void PropertyTypesMatrix3();
void PropertyTypesMatrix();
void PropertyTypesAngleAxis();
void PropertyTypesQuaternion();
void PropertyTypesstring();
void PropertyTypesRect();
void PropertyTypesMap();
void PropertyTypesArray();
void PropertyTypesGetBooleanTypeName();
void PropertyTypesGetFloatTypeName();
void PropertyTypesGetIntegerTypeName();
void PropertyTypesGetVector2TypeName();
void PropertyTypesGetVector3TypeName();
void PropertyTypesGetVector4TypeName();
void PropertyTypesGetMatrix3TypeName();
void PropertyTypesGetMatrixTypeName();
void PropertyTypesGetRectangleTypeName();
void PropertyTypesGetRotationTypeName();
void PropertyTypesGetStringTypeName();
void PropertyTypesGetArrayTypeName();
void PropertyTypesGetMapTypeName();

namespace
{
  enum TEST_CASES_LIST_PROPERTY_TYPES
  {
    PROPERTY_TYPES_GET_TYPE_NAME
  };

  struct Property_Types_TestApp : public ConnectionTracker
  {
    Property_Types_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Types_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Types_TestApp::Tick );
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
        case PROPERTY_TYPES_GET_TYPE_NAME:
          PropertyTypesGetName();
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

void PropertyTypesGetName()
{
  PropertyTypesGetBooleanTypeName();
  PropertyTypesGetFloatTypeName();
  PropertyTypesGetIntegerTypeName();
  PropertyTypesGetVector2TypeName();
  PropertyTypesGetVector3TypeName();
  PropertyTypesGetVector4TypeName();
  PropertyTypesGetMatrix3TypeName();
  PropertyTypesGetMatrixTypeName();
  PropertyTypesGetRectangleTypeName();
  PropertyTypesGetRotationTypeName();
  PropertyTypesGetStringTypeName();
  PropertyTypesGetArrayTypeName();
  PropertyTypesGetMapTypeName();

  DaliLog::PrintPass();
}


void PropertyTypesBoolean()
{
  bool bSetValue = true;

  Property::Value value( bSetValue );
  Property::Type type = PropertyTypes::Get<bool>();
  DALI_CHECK_FAIL( Property::BOOLEAN != type , " Failed to return enumerated property type for boolean." );

  DALI_CHECK_FAIL( value.GetType() != type , " Get Type not correct, expected type is boolean." );

  DaliLog::PrintPass();
}

void PropertyTypesFloat()
{
  float fSetValue = 1.0f;

  Property::Value value( fSetValue );
  Property::Type type = PropertyTypes::Get<float>();
  DALI_CHECK_FAIL( type != Property::FLOAT , " Failed to return enumerated property type for float." );

  DALI_CHECK_FAIL( value.GetType() != type , " Get Type not correct, expected type is float" );

  DaliLog::PrintPass();
}

void PropertyTypesInt()
{
  int nSetValue = 1;

  Property::Value value( nSetValue );
  Property::Type type = PropertyTypes::Get<int>();
  DALI_CHECK_FAIL( type != Property::INTEGER , "  Failed to return enumerated property type for int" );

  DALI_CHECK_FAIL( value.GetType() != type , " Get Type not correct, expected type is int." );

  DaliLog::PrintPass();
}

void PropertyTypesVector2()
{
  Vector2 vec2SetValue( 1.0f, 1.0f );

  Property::Value value( vec2SetValue );
  Property::Type type = PropertyTypes::Get<Vector2>();
  DALI_CHECK_FAIL( type != Property::VECTOR2 , "Get Type not correct, expected type is Vector2." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Vector2." );

  DaliLog::PrintPass();
}

void PropertyTypesVector3()
{
  Vector3 vec3SetValue( 1.0f, 1.0f, 1.0f );

  Property::Value value( vec3SetValue );
  Property::Type type = PropertyTypes::Get<Vector3>();
  DALI_CHECK_FAIL( type != Property::VECTOR3 , "Get Type not correct, expected type is Vector3." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Vector3" );

  DaliLog::PrintPass();
}

void PropertyTypesVector4()
{
  Vector4 vec4SetValue( 1.0f, 1.0f, 1.0f, 1.0f );

  Property::Value value( vec4SetValue );
  Property::Type type = PropertyTypes::Get<Vector4>();
  DALI_CHECK_FAIL( type != Property::VECTOR4 , "Get Type not correct, expected type is Vector4." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Vector4." );

  DaliLog::PrintPass();
}

void PropertyTypesMatrix3()
{
  Matrix3 mat3SetValue( 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );

  Property::Value value( mat3SetValue );
  Property::Type type = PropertyTypes::Get<Matrix3>();
  DALI_CHECK_FAIL( type != Property::MATRIX3 , "Get Type not correct, expected type is MATRIX3." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for MATRIX3.." );

  DaliLog::PrintPass();
}

void PropertyTypesMatrix()
{
  float frgValues[16] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
  Matrix matSetValue( frgValues );

  Property::Value value( matSetValue );
  Property::Type type = PropertyTypes::Get<Matrix>();
  DALI_CHECK_FAIL( type != Property::MATRIX , "Get Type not correct, expected type is MATRIX." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for MATRIX" );

  DaliLog::PrintPass();
}

void PropertyTypesAngleAxis()
{
  Degree deg( 75.0f );
  Vector3 vec3Value( 5.0f, 5.0f, 5.0f );
  AngleAxis angleSetValue( deg, vec3Value );

  Property::Value value( angleSetValue );
  Property::Type type = PropertyTypes::Get<AngleAxis>();
  DALI_CHECK_FAIL( type != Property::ROTATION , "Get Type not correct, expected type is ROTATION." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for ROTATION" );

  DaliLog::PrintPass();
}

void PropertyTypesQuaternion()
{
  float fAngle = 4.5f;
  Vector3 vec3Value( 2.0f, 2.0f, 2.0f );
  Quaternion quatSetValue( Radian(fAngle), vec3Value );

  Property::Value value( quatSetValue );
  Property::Type type = PropertyTypes::Get<Quaternion>();
  DALI_CHECK_FAIL( type != Property::ROTATION , "Get Type not correct, expected type is ROTATION." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for ROTATION." );

  DaliLog::PrintPass();
}

void PropertyTypesstring()
{
  string strSetValue = "Test For Property Type";

  Property::Value value( strSetValue );
  Property::Type type = PropertyTypes::Get<string>();
  DALI_CHECK_FAIL( type != Property::STRING , "Get Type not correct, expected type is STRING." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for STRING." );

  DaliLog::PrintPass();
}

void PropertyTypesRect()
{
  Dali::Rect<int> rectSetValue( 1.0f, 1.0f, 1.0f, 1.0f );

  Property::Value value( rectSetValue );
  Property::Type type = PropertyTypes::Get< Dali::Rect<int> >();
  DALI_CHECK_FAIL( type != Property::RECTANGLE , "Get Type not correct, expected type is Dali::Rect<int>." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Dali::Rect<int>." );

  DaliLog::PrintPass();
}

void PropertyTypesMap()
{
  Property::Map mapSetValue;

  Property::Value value( mapSetValue );
  Property::Type type = PropertyTypes::Get<Property::Map>();
  DALI_CHECK_FAIL( type != Property::MAP , "Failed to return enumerated property type for Property::Map." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Property::Map." );

  DaliLog::PrintPass();
}

void PropertyTypesArray()
{
  Property::Array arraySetValue;

  Property::Value value( arraySetValue );
  Property::Type type = PropertyTypes::Get<Property::Array>();
  DALI_CHECK_FAIL( type != Property::ARRAY , "Failed to return enumerated property type for Property::Array." );

  DALI_CHECK_FAIL( value.GetType() != type , "Failed to return enumerated property type for Property::Array." );

  DaliLog::PrintPass();
}

void PropertyTypesGetBooleanTypeName()
{
  bool bValue = true;
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( bValue, ( char* )"BOOLEAN" );
  DALI_CHECK_FAIL( bRet == false , "UtcDaliPropertyTypesGetBooleanTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetFloatTypeName()
{
  float fValue = 2.0f;
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( fValue, ( char* )"FLOAT" );
  DALI_CHECK_FAIL(!bRet, "UtcDaliPropertyTypesGetFloatTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetIntegerTypeName()
{
  int nValue = 2;
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( nValue, ( char* )"INTEGER" );
  DALI_CHECK_FAIL( !bRet, "UtcDaliPropertyTypesGetIntegerTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetVector2TypeName()
{
  Vector2 vec2Value( 2.0f, 2.0f );
  bool bRet = false;

  bRet = PropertyTypesGetTypeName(  vec2Value, ( char* )"VECTOR2" );
  DALI_CHECK_FAIL(!bRet, "UtcDaliPropertyTypesGetVector2TypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetVector3TypeName()
{
  Vector3 vec3Value( 2.0f, 2.0f, 2.0f );
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( vec3Value, ( char* )"VECTOR3" );
  DALI_CHECK_FAIL( !bRet, "UtcDaliPropertyTypesGetVector3TypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetVector4TypeName()
{
  Vector4 vec4Value( 2.0f, 2.0f, 2.0f, 2.0f );
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( vec4Value, ( char* )"VECTOR4" );
  DALI_CHECK_FAIL( !bRet , "UtcDaliPropertyTypesGetVector4TypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetMatrix3TypeName()
{
  Matrix3 mat3Value( 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f );

  bool bRet = false;

  bRet = PropertyTypesGetTypeName(  mat3Value, ( char* )"MATRIX3" );
  DALI_CHECK_FAIL(!bRet, "UtcDaliPropertyTypesGetMatrix3TypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetMatrixTypeName()
{
  float frgValue[16] = { 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f };
  Matrix matValue( frgValue );

  bool bRet = false;

  bRet = PropertyTypesGetTypeName( matValue, ( char* )"MATRIX" );
  DALI_CHECK_FAIL(!bRet , "UtcDaliPropertyTypesGetMatrixTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetRectangleTypeName()
{
  Dali::Rect<int> rectValue( 1.0f, 1.0f, 1.0f, 1.0f );

  bool bRet = false;

  bRet = PropertyTypesGetTypeName( rectValue, ( char* )"RECTANGLE" );
  DALI_CHECK_FAIL(!bRet, "UtcDaliPropertyTypesGetRectangleTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetRotationTypeName()
{
  float fAngle = 4.5f;
  Vector3 vec3Value( 2.0f, 2.0f, 2.0f );
  Quaternion quatValue( Radian(fAngle), vec3Value );
  //Quaternion quatValue( fAngle, vec3Value );

  bool bRet = false;

  bRet = PropertyTypesGetTypeName( quatValue, ( char* )"ROTATION" );
  DALI_CHECK_FAIL(!bRet , "UtcDaliPropertyTypesGetRotationTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetStringTypeName()
{
  string strValue = "Test Type String";

  bool bRet = false;

  bRet = PropertyTypesGetTypeName( strValue, ( char* )"STRING" );
  DALI_CHECK_FAIL( !bRet , "UtcDaliPropertyTypesGetStringTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetArrayTypeName()
{
  Property::Array arrayValue;

  bool bRet = false;

  bRet = PropertyTypesGetTypeName( arrayValue, ( char* )"ARRAY" );
  DALI_CHECK_FAIL(!bRet , "UtcDaliPropertyTypesGetArrayTypeName is failed" );

  DaliLog::PrintPass();
}

void PropertyTypesGetMapTypeName()
{
  Property::Type type = Property::MAP ;
  Property::Value value(type);
  bool bRet = false;

  bRet = PropertyTypesGetTypeName( value, ( char* )"MAP" );
  DALI_CHECK_FAIL(!bRet, "UtcDaliPropertyTypesGetMapTypeName is failed" );

  DaliLog::PrintPass();
}


/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase           UtcDaliPropertyTypesGetTypeNameP
 * @since_tizen        2.4
 * @description        Retrieve the name of a property type.
 */
int UtcDaliPropertyTypesGetNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Types_TestApp testApp( application, PROPERTY_TYPES_GET_TYPE_NAME);
  application.MainLoop();
  return test_return_value;
}
