#include "utc-dali-property-value-common.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sstream>

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

namespace
{
  template <typename T>
    struct CheckCopyCtorP
    {
      CheckCopyCtorP(Property::Value value)
      {
        Property::Value copy( value );
        DALI_CHECK_FAIL( !(value.Get<T>() == copy.Get<T>() ) , "Property::Value copy constructor has fialed.");
      }
    };

} // unnamed namespace

/**
 * @function            utc_Dali_PropertyValue_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyValue_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_PropertyValue_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyValue_cleanup(void)
{

}


void PropertyValueConstructorNoneP(void);
void PropertyValueConstructorNoneTypeP(void);
void PropertyValueConstructorBoolP(void);
void PropertyValueConstructorBoolTypeP(void);
void PropertyValueConstructorsFloatP(void);
void PropertyValueConstructorsFloatTypeP(void);
void PropertyValueConstructorsIntP(void);
void PropertyValueConstructorsIntTypeP(void);
void PropertyValueConstructorsVector2P(void);
void PropertyValueConstructorsVector2TypeP(void);
void PropertyValueConstructorsVector3P(void);
void PropertyValueConstructorsVector3TypeP(void);
void PropertyValueConstructorsVector4P(void);
void PropertyValueConstructorsVector4TypeP(void);
void PropertyValueConstructorsMatrix3P(void);
void PropertyValueConstructorsMatrix3TypeP(void);
void PropertyValueConstructorsMatrixP(void);
void PropertyValueConstructorsMatrixTypeP(void);
void PropertyValueConstructorsRectP(void);
void PropertyValueConstructorsRectTypeP(void);
void PropertyValueConstructorsAngleAxisP(void);
void PropertyValueConstructorsQuaternionP(void);
void PropertyValueConstructorsRotationTypeP(void);
void PropertyValueConstructorsStringP(void);
void PropertyValueConstructorsStringTypeP(void);
void PropertyValueConstructorsArrayP(void);
void PropertyValueConstructorsArray2P(void);
void PropertyValueConstructorsArrayTypeP(void);
void PropertyValueConstructorsMapP(void);
void PropertyValueConstructorsMap2P(void);
void PropertyValueConstructorsMapTypeP(void);
void PropertyValueConstructorsInitializerListP(void);
void PropertyValueConstructorsEnumP(void);
void PropertyValueCopyConstructorP(void);
void PropertyValueCopyConstructorBoolP(void);
void PropertyValueCopyConstructorFloatP(void);
void PropertyValueCopyConstructorIntP(void);
void PropertyValueCopyConstructoVector2P(void);
void PropertyValueCopyConstructorVector3P(void);
void PropertyValueCopyConstructorVector4P(void);
void PropertyValueCopyConstructorMatrix3P(void);
void PropertyValueCopyConstructorMatrixP(void);
void PropertyValueCopyConstructorRectP(void);
void PropertyValueCopyConstructorAngleAxisP(void);
void PropertyValueCopyConstructorQuaternionP(void);
void PropertyValueCopyConstructorStringP(void);
void PropertyValueCopyConstructorArrayP(void);
void PropertyValueCopyConstructorMapP(void);
void PropertyValueAssignmentSelfP(void);
void PropertyValueAssignmentOperatorNoneP(void);
void PropertyValueAssignmentOperatorBoolP(void);
void PropertyValueAssignmentOperatorIntP(void);
void PropertyValueAssignmentOperatorFloatP(void);
void PropertyValueAssignmentOperatorVector2P(void);
void PropertyValueAssignmentOperatorVector3P(void);
void PropertyValueAssignmentOperatorVector4P(void);
void PropertyValueAssignmentOperatorMatrix3P(void);
void PropertyValueAssignmentOperatorMatrixP(void);
void PropertyValueAssignmentOperatorRectP(void);
void PropertyValueAssignmentOperatorQuaternionP(void);
void PropertyValueAssignmentOperatorAngleAxisP(void);
void PropertyValueAssignmentOperatorStringP(void);
void PropertyValueAssignmentOperatorArrayP(void);
void PropertyValueAssignmentOperatorMapP(void);
void PropertyValueGetTypeP(void);
void PropertyValueGetBoolP(void);
void PropertyValueGetBoolN(void);
void PropertyValueGetFloatP(void);
void PropertyValueGetFloatN(void);
void PropertyValueGetIntP(void);
void PropertyValueGetIntN(void);
void PropertyValueGetRectP(void);
void PropertyValueGetRectN(void);
void PropertyValueGetVector2P(void);
void PropertyValueGetVector2N(void);
void PropertyValueGetVector3P(void);
void PropertyValueGetVector3N(void);
void PropertyValueGetVector4P(void);
void PropertyValueGetVector4N(void);
void PropertyValueGetMatrix3P(void);
void PropertyValueGetMatrix3N(void);
void PropertyValueGetMatrixP(void);
void PropertyValueGetMatrixN(void);
void PropertyValueGetAngleAxisP(void);
void PropertyValueGetAngleAxisN(void);
void PropertyValueGetQuaternionP(void);
void PropertyValueGetQuaternionN(void);
void PropertyValueGetStringP(void);
void PropertyValueGetStringN(void);
void PropertyValueGetArrayP(void);
void PropertyValueGetArrayN(void);
void PropertyValueGetMapP(void);
void PropertyValueGetMapN(void);
void PropertyValueGetEnumP(void);
void PropertyValueGetEnumN(void);
void PropertyValueOutputStreamP(void);
void PropertyValueConstructorsExtentsTypeP(void);
void PropertyValueConstructorsExtentsType2P(void);
void PropertyValueAssignmentOperatorExtentsP(void);
void PropertyValueGetExtentsP(void);


namespace
{
  enum TEST_CASES_LIST_PROPERTY_VALUE
  {
    PROPERTY_VALUE_CONSTRUCTOR_NONE_P,
    PROPERTY_VALUE_CONSTRUCTOR_NONETYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_BOOL_P,
    PROPERTY_VALUE_CONSTRUCTOR_BOOLTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_FLOAT_P,
    PROPERTY_VALUE_CONSTRUCTOR_FLOATTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_INT_P,
    PROPERTY_VALUE_CONSTRUCTOR_INTTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR2_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR2TYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR3_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR3TYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR4_P,
    PROPERTY_VALUE_CONSTRUCTOR_VECTOR4TYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_MATRIX3_P,
    PROPERTY_VALUE_CONSTRUCTOR_MATRIX3TYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_MATRIX_P,
    PROPERTY_VALUE_CONSTRUCTOR_MATRIXTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_RECT_P,
    PROPERTY_VALUE_CONSTRUCTOR_RECTTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_ANGLEAXIS_P,
    PROPERTY_VALUE_CONSTRUCTOR_QUATERNION_P,
    PROPERTY_VALUE_CONSTRUCTOR_QUATERNIONTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_STRING_P,
    PROPERTY_VALUE_CONSTRUCTOR_STRINGTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_ARRAY_P,
    PROPERTY_VALUE_CONSTRUCTOR_ARRAY2_P,
    PROPERTY_VALUE_CONSTRUCTOR_ARRAYTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_MAP_P,
    PROPERTY_VALUE_CONSTRUCTOR_MAP_P2,
    PROPERTY_VALUE_CONSTRUCTOR_MAPTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_INITIALIZER_LIST_P,
    PROPERTY_VALUE_CONSTRUCTOR_ENUM_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_BOOL_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_FLOAT_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_INT_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR2_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR3_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR4_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX3_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_RECT_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_ANGLEAXIS_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_QUARTERNION_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_STRING_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_ARRAY_P,
    PROPERTY_VALUE_COPYCONSTRUCTOR_MAP_P,
    PROPERTY_VALUE_ASSIGNMENT_SELF_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_NONE_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_BOOL_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_INT_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_FLOAT_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR2_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR3_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR4_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX3_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_RECT_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_QUARTERNION_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_ANGLEAXIS_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_STRING_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_ARRAY_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_MAP_P,
    PROPERTY_VALUE_GET_NONE_P,
    PROPERTY_VALUE_GET_BOOL_P,
    PROPERTY_VALUE_GET_BOOL_N,
    PROPERTY_VALUE_GET_FLOAT_P,
    PROPERTY_VALUE_GET_FLOAT_N,
    PROPERTY_VALUE_GET_INT_P,
    PROPERTY_VALUE_GET_INT_N,
    PROPERTY_VALUE_GET_RECT_P,
    PROPERTY_VALUE_GET_RECT_N,
    PROPERTY_VALUE_GET_VECTOR2_P,
    PROPERTY_VALUE_GET_VECTOR2_N,
    PROPERTY_VALUE_GET_VECTOR3_P,
    PROPERTY_VALUE_GET_VECTOR3_N,
    PROPERTY_VALUE_GET_VECTOR4_P,
    PROPERTY_VALUE_GET_VECTOR4_N,
    PROPERTY_VALUE_GET_MATRIX3_P,
    PROPERTY_VALUE_GET_MATRIX3_N,
    PROPERTY_VALUE_GET_MATRIX_P,
    PROPERTY_VALUE_GET_MATRIX_N,
    PROPERTY_VALUE_GET_ANGLEAXIS_P,
    PROPERTY_VALUE_GET_ANGLEAXIS_N,
    PROPERTY_VALUE_GET_QUARTERNION_P,
    PROPERTY_VALUE_GET_QUARTERNION_N,
    PROPERTY_VALUE_GET_STRING_P,
    PROPERTY_VALUE_GET_STRING_N,
    PROPERTY_VALUE_GET_ARRAY_P,
    PROPERTY_VALUE_GET_ARRAY_N,
    PROPERTY_VALUE_GET_MAP_P,
    PROPERTY_VALUE_GET_MAP_N,
    PROPERTY_VALUE_GET_ENUM_P,
    PROPERTY_VALUE_GET_ENUM_N,
    PROPERTY_VALUE_OUTPUTSTREAM_P,
    PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE_P,
    PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE2_P,
    PROPERTY_VALUE_OPERATORASSIGNMENT_EXTENTS_P,
    PROPERTY_VALUE_GET_EXTENTS_P
  };

  struct Property_Value_TestApp : public ConnectionTracker
  {
    Property_Value_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Value_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Value_TestApp::Tick );
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
        case PROPERTY_VALUE_CONSTRUCTOR_NONE_P:
          PropertyValueConstructorNoneP();
          break;
        case PROPERTY_VALUE_CONSTRUCTOR_NONETYPE_P:
          PropertyValueConstructorNoneTypeP();
          break;
        case PROPERTY_VALUE_CONSTRUCTOR_BOOL_P :
          PropertyValueConstructorBoolP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_BOOLTYPE_P :
          PropertyValueConstructorBoolTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_FLOAT_P :
          PropertyValueConstructorsFloatP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_FLOATTYPE_P :
          PropertyValueConstructorsFloatTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_INT_P :
          PropertyValueConstructorsIntP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_INTTYPE_P :
          PropertyValueConstructorsIntTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR2_P :
          PropertyValueConstructorsVector2P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR2TYPE_P :
          PropertyValueConstructorsVector2TypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR3_P :
          PropertyValueConstructorsVector3P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR3TYPE_P :
          PropertyValueConstructorsVector3TypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR4_P :
          PropertyValueConstructorsVector4P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_VECTOR4TYPE_P :
          PropertyValueConstructorsVector4TypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MATRIX3_P :
          PropertyValueConstructorsMatrix3P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MATRIX3TYPE_P :
          PropertyValueConstructorsMatrix3TypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MATRIX_P :
          PropertyValueConstructorsMatrixP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MATRIXTYPE_P :
          PropertyValueConstructorsMatrixTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_RECT_P :
          PropertyValueConstructorsRectP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_RECTTYPE_P :
          PropertyValueConstructorsRectTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_ANGLEAXIS_P :
          PropertyValueConstructorsAngleAxisP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_QUATERNION_P :
          PropertyValueConstructorsQuaternionP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_QUATERNIONTYPE_P :
          PropertyValueConstructorsRotationTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_STRING_P :
          PropertyValueConstructorsStringP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_STRINGTYPE_P :
          PropertyValueConstructorsStringTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_ARRAY_P :
          PropertyValueConstructorsArrayP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_ARRAY2_P :
          PropertyValueConstructorsArray2P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_ARRAYTYPE_P :
          PropertyValueConstructorsArrayTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MAP_P :
          PropertyValueConstructorsMapP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MAP_P2 :
          PropertyValueConstructorsMap2P();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_MAPTYPE_P :
          PropertyValueConstructorsMapTypeP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_INITIALIZER_LIST_P :
          PropertyValueConstructorsInitializerListP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_ENUM_P :
          PropertyValueConstructorsEnumP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_P :
          PropertyValueCopyConstructorP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_BOOL_P :
          PropertyValueCopyConstructorBoolP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_FLOAT_P :
          PropertyValueCopyConstructorFloatP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_INT_P :
          PropertyValueCopyConstructorIntP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR2_P :
          PropertyValueCopyConstructoVector2P();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR3_P :
          PropertyValueCopyConstructorVector3P();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR4_P :
          PropertyValueCopyConstructorVector4P();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX3_P :
          PropertyValueCopyConstructorMatrix3P();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX_P :
          PropertyValueCopyConstructorMatrixP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_RECT_P :
          PropertyValueCopyConstructorRectP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_ANGLEAXIS_P :
          PropertyValueCopyConstructorAngleAxisP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_QUARTERNION_P :
          PropertyValueCopyConstructorQuaternionP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_STRING_P :
          PropertyValueCopyConstructorStringP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_ARRAY_P :
          PropertyValueCopyConstructorArrayP();
          break;

        case PROPERTY_VALUE_COPYCONSTRUCTOR_MAP_P :
          PropertyValueCopyConstructorMapP();
          break;

        case PROPERTY_VALUE_ASSIGNMENT_SELF_P :
          PropertyValueAssignmentSelfP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_NONE_P :
          PropertyValueAssignmentOperatorNoneP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_BOOL_P :
          PropertyValueAssignmentOperatorBoolP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_INT_P :
          PropertyValueAssignmentOperatorIntP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_FLOAT_P :
          PropertyValueAssignmentOperatorFloatP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR2_P :
          PropertyValueAssignmentOperatorVector2P();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR3_P :
          PropertyValueAssignmentOperatorVector3P();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR4_P :
          PropertyValueAssignmentOperatorVector4P();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX3_P :
          PropertyValueAssignmentOperatorMatrix3P();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX_P :
          PropertyValueAssignmentOperatorMatrixP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_RECT_P :
          PropertyValueAssignmentOperatorRectP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_QUARTERNION_P :
          PropertyValueAssignmentOperatorQuaternionP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_ANGLEAXIS_P :
          PropertyValueAssignmentOperatorAngleAxisP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_STRING_P :
          PropertyValueAssignmentOperatorStringP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_ARRAY_P :
          PropertyValueAssignmentOperatorArrayP();
          break;

        case PROPERTY_VALUE_OPERATORASSIGNMENT_MAP_P :
          PropertyValueAssignmentOperatorMapP();
          break;

        case PROPERTY_VALUE_GET_NONE_P :
          PropertyValueGetTypeP();
          break;

        case PROPERTY_VALUE_GET_BOOL_P :
          PropertyValueGetBoolP();
          break;

        case PROPERTY_VALUE_GET_BOOL_N :
          PropertyValueGetBoolN();
          break;

        case PROPERTY_VALUE_GET_FLOAT_P :
          PropertyValueGetFloatP();
          break;

        case PROPERTY_VALUE_GET_FLOAT_N :
          PropertyValueGetFloatN();
          break;

        case PROPERTY_VALUE_GET_INT_P :
          PropertyValueGetIntP();
          break;

        case PROPERTY_VALUE_GET_INT_N :
          PropertyValueGetIntN();
          break;

        case PROPERTY_VALUE_GET_RECT_P :
          PropertyValueGetRectP();
          break;

        case PROPERTY_VALUE_GET_RECT_N :
          PropertyValueGetRectN();
          break;

        case PROPERTY_VALUE_GET_VECTOR2_P :
          PropertyValueGetVector2P();
          break;

        case PROPERTY_VALUE_GET_VECTOR2_N :
          PropertyValueGetVector2N();
          break;

        case PROPERTY_VALUE_GET_VECTOR3_P :
          PropertyValueGetVector3P();
          break;

        case PROPERTY_VALUE_GET_VECTOR3_N :
          PropertyValueGetVector3N();
          break;

        case PROPERTY_VALUE_GET_VECTOR4_P :
          PropertyValueGetVector4P();
          break;

        case PROPERTY_VALUE_GET_VECTOR4_N :
          PropertyValueGetVector4N();
          break;

        case PROPERTY_VALUE_GET_MATRIX3_P :
          PropertyValueGetMatrix3P();
          break;

        case PROPERTY_VALUE_GET_MATRIX3_N :
          PropertyValueGetMatrix3N();
          break;

        case PROPERTY_VALUE_GET_MATRIX_P :
          PropertyValueGetMatrixP();
          break;

        case PROPERTY_VALUE_GET_MATRIX_N :
          PropertyValueGetMatrixN();
          break;

        case PROPERTY_VALUE_GET_ANGLEAXIS_P :
          PropertyValueGetAngleAxisP();
          break;

        case PROPERTY_VALUE_GET_ANGLEAXIS_N :
          PropertyValueGetAngleAxisN();
          break;

        case PROPERTY_VALUE_GET_QUARTERNION_P :
          PropertyValueGetQuaternionP();
          break;

        case PROPERTY_VALUE_GET_QUARTERNION_N :
          PropertyValueGetQuaternionN();
          break;

        case PROPERTY_VALUE_GET_STRING_P :
          PropertyValueGetStringP();
          break;

        case PROPERTY_VALUE_GET_STRING_N :
          PropertyValueGetStringN();
          break;

        case PROPERTY_VALUE_GET_ARRAY_P :
          PropertyValueGetArrayP();
          break;

        case PROPERTY_VALUE_GET_ARRAY_N :
          PropertyValueGetArrayN();
          break;

        case PROPERTY_VALUE_GET_MAP_P :
          PropertyValueGetMapP();
          break;

        case PROPERTY_VALUE_GET_MAP_N :
          PropertyValueGetMapN();
          break;

        case PROPERTY_VALUE_GET_ENUM_P :
          PropertyValueGetEnumP();
          break;

        case PROPERTY_VALUE_GET_ENUM_N :
          PropertyValueGetEnumN();
          break;

        case PROPERTY_VALUE_OUTPUTSTREAM_P :
          PropertyValueOutputStreamP();
          break;

        case PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE_P :
          PropertyValueConstructorsExtentsTypeP();
          break;
        case PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE2_P :
          PropertyValueConstructorsExtentsType2P();
          break;
        case PROPERTY_VALUE_OPERATORASSIGNMENT_EXTENTS_P :
          PropertyValueAssignmentOperatorExtentsP();
          break;
        case PROPERTY_VALUE_GET_EXTENTS_P :
          PropertyValueGetExtentsP();
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

void PropertyValueConstructorNoneP(void)
{
  Property::Value value;

  DALI_CHECK_FAIL( (value.GetType() != Property::NONE), "PropertyValue Default Constuctor has Failed." );
  DaliLog::PrintPass();
}

/**
 * @testcase         UtcDaliPropertyValueConstructorNoneP
 * @since_tizen      2.4
 * @description      Check if default Constructor works fine or not
 */
int UtcDaliPropertyValueConstructorNoneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_NONE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorNoneTypeP(void)
{
  Property::Value value( Property::NONE );
  DALI_CHECK_FAIL( (value.GetType() != Property::NONE) , "PropertyValue Default Constuctor has Failed.");
  DaliLog::PrintPass();
}

/**
 * @testcase         UtcDaliPropertyValueConstructorNoneTypeP
 * @since_tizen      2.4
 * @description      Check if the Constructor works for None type or not.
 */
int UtcDaliPropertyValueConstructorNoneTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_NONETYPE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorBoolP(void)
{
  Property::Value value(true);

  DALI_CHECK_FAIL( (value.GetType() != Property::BOOLEAN) , "PropertyValue Constuctor for boolean type has Failed." );
  DALI_CHECK_FAIL( (value.Get<bool>() != true) , "PropertyValue::Get for boolean type has Failed." );

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorBoolP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Boolean type or not.
 */
int UtcDaliPropertyValueConstructorBoolP(void)
{

  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_BOOL_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorBoolTypeP(void)
{
  Property::Value value(Property::BOOLEAN);

  DALI_CHECK_FAIL( (value.GetType() != Property::BOOLEAN) , "PropertyValue Constuctor for boolean type has Failed.");
  DALI_CHECK_FAIL( (value.Get<bool>() != false) , "PropertyValue::Get for boolean type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorBoolTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Boolean type or not.
 */
int UtcDaliPropertyValueConstructorBoolTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_BOOLTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsFloatP(void)
{
  Property::Value value(2.f);

  DALI_CHECK_FAIL( (value.GetType() != Property::FLOAT) , "PropertyValue Constuctor for float type has Failed.");
  DALI_CHECK_FAIL( (value.Get<float>() != 2.f) , "PropertyValue::Get for float type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsFloatP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Float type or not.
 */
int UtcDaliPropertyValueConstructorsFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsFloatTypeP(void)
{
  Property::Value value(Property::FLOAT);

  DALI_CHECK_FAIL( (value.GetType() != Property::FLOAT) , "PropertyValue Constuctor for float type has Failed.");
  DALI_CHECK_FAIL( (value.Get<float>() != 0.f ), "PropertyValue::Get for float type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsFloatTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Float type or not.
 */
int UtcDaliPropertyValueConstructorsFloatTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_FLOATTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsIntP(void)
{
  Property::Value value(1);

  DALI_CHECK_FAIL( (value.GetType() != Property::INTEGER) , "PropertyValue Constuctor for Integer type has Failed.");
  DALI_CHECK_FAIL( (value.Get<int>() != 1 ), "PropertyValue::Get for Integer type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsIntP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Integer type or not.
 */
int UtcDaliPropertyValueConstructorsIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_INT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsIntTypeP(void)
{
  Property::Value value(Property::INTEGER);

  DALI_CHECK_FAIL( (value.GetType() != Property::INTEGER), "PropertyValue Constuctor for Integer type has Failed." );
  DALI_CHECK_FAIL( value.Get<int>() != 0 , "PropertyValue::Get for Integer type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsIntTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Integer type or not.
 */
int UtcDaliPropertyValueConstructorsIntTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_INTTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsVector2P(void)
{
  Vector2 v(1,1);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR2 , "PropertyValue Constuctor for Vector2 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector2>() != v , "PropertyValue::Get for Vector2 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsVector2P
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector2 type or not.
 */
int UtcDaliPropertyValueConstructorsVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsVector2TypeP(void)
{
  Property::Value value( Property::VECTOR2 );

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR2 , "PropertyValue Constuctor for Vector2 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector2>() != Vector2::ZERO , "PropertyValue::Get for Vector2 type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsVector2TypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector2 type or not.
 */
int UtcDaliPropertyValueConstructorsVector2TypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR2TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsVector3P(void)
{
  Vector3 v(1.f,2.f,3.f);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR3 , "PropertyValue Constuctor for Vector3 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector3>() != v , "PropertyValue::Get for VEctor3 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsVector3P
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector3 type or not.
 */
int UtcDaliPropertyValueConstructorsVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsVector3TypeP(void)
{
  Property::Value value( Property::VECTOR3 );

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR3 , "PropertyValue Constuctor for Vector3 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector3>() != Vector3(), "PropertyValue::Get for VEctor3 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsVector3TypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector3 type or not.
 */
int UtcDaliPropertyValueConstructorsVector3TypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR3TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsVector4P(void)
{
  Vector4 v(1.f,1.f,1.f,0.9f);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR4 , "PropertyValue Constuctor for Vector4 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector4>() != v , "PropertyValue::Get for Vector4 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsVector4P
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector4 type or not.
 */
int UtcDaliPropertyValueConstructorsVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsVector4TypeP(void)
{
  Property::Value value( Property::VECTOR4 );

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR4 , "PropertyValue Constuctor for Vector4 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Vector4>() != Vector4() , "PropertyValue::Get for Vector4 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsVector4TypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Vector4 type or not.
 */
int UtcDaliPropertyValueConstructorsVector4TypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_VECTOR4TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsMatrix3P(void)
{
  Matrix3 v(1.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,1.0);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::MATRIX3 , "PropertyValue Constuctor for Matrix3 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Matrix3>() != v , "PropertyValue::Get for Matrix3 type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsMatrix3P
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Matrix3 type or not.
 */
int UtcDaliPropertyValueConstructorsMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsMatrix3TypeP(void)
{
  Property::Value value( Property::MATRIX3 );

  DALI_CHECK_FAIL( value.GetType() != Property::MATRIX3 , "PropertyValue Constuctor for Matrix3 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Matrix3>() != Matrix3() , "PropertyValue::Get for Matrix3 type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsMatrix3TypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Matrix3 type or not.
 */
int UtcDaliPropertyValueConstructorsMatrix3TypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MATRIX3TYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsMatrixP(void)
{
  float a[] = {1.0,1.0,1.0,1.0, 1.0,1.0,1.0,1.0, 1.0,1.0,1.0,1.0, 1.0,1.0,1.0,1.0};
  Matrix v(a);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::MATRIX , "PropertyValue Constuctor for Matrix type has Failed.");
  DALI_CHECK_FAIL( value.Get<Matrix>() != v , "PropertyValue::Get for Matrix type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsMatrixP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Matrix type or not.
 */
int UtcDaliPropertyValueConstructorsMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsMatrixTypeP(void)
{
  Property::Value value( Property::MATRIX );

  DALI_CHECK_FAIL( value.GetType() != Property::MATRIX , "PropertyValue Constuctor for Matrix type has Failed.");
  DALI_CHECK_FAIL( value.Get<Matrix>() != Matrix() , "PropertyValue::Get for Matrix type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsMatrixTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Matrix type or not.
 */
int UtcDaliPropertyValueConstructorsMatrixTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MATRIXTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsRectP(void)
{
  Rect<int> v(1.0,1.0,1.0,1.0);
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() !=Property::RECTANGLE, "PropertyValue Constuctor for Rectangle type has Failed." );
  DALI_CHECK_FAIL( value.Get<Rect<int> >() != v , "PropertyValue::Get for Rectangle type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsRectP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Rect type or not.
 */
int UtcDaliPropertyValueConstructorsRectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_RECT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsRectTypeP(void)
{
  Property::Value value( Property::RECTANGLE );

  DALI_CHECK_FAIL( value.GetType() != Property::RECTANGLE,  "PropertyValue Constuctor for Rectangle type has Failed." );
  DALI_CHECK_FAIL( value.Get<Rect<int> >() != Rect<int>(0,0,0,0) , "PropertyValue::Get for Rectangle type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsRectTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Rect type or not.
 */
int UtcDaliPropertyValueConstructorsRectTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_RECTTYPE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsAngleAxisP(void)
{
  AngleAxis input( Dali::ANGLE_90, Vector3::XAXIS );
  Property::Value value( input );

  DALI_CHECK_FAIL( value.GetType() != Property::ROTATION , "PropertyValue Constuctor for Rotation type has Failed.");
  AngleAxis result = value.Get<AngleAxis>();
  DALI_CHECK_FAIL( result.angle != input.angle  , "PropertyValue::Get for AngleAxis type has Failed.");
  DALI_CHECK_FAIL( result.axis != input.axis, "PropertyValue::Get for AngleAxis type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsAngleAxisP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for AngleAxis type or not.
 */
int UtcDaliPropertyValueConstructorsAngleAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_ANGLEAXIS_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsQuaternionP(void)
{
  Quaternion v( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) );
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::ROTATION , "PropertyValue Constuctor for Quarternion type has Failed.");
  DALI_CHECK_FAIL( value.Get<Quaternion>() != v , "PropertyValue::Get for Quarternion type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsQuaternionP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Quaternion type or not.
 */
int UtcDaliPropertyValueConstructorsQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_QUATERNION_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsRotationTypeP(void)
{
  Property::Value value( Property::ROTATION );

  DALI_CHECK_FAIL( value.GetType() != Property::ROTATION , "PropertyValue Constuctor for Quarternion type has Failed.");
  AngleAxis result = value.Get<AngleAxis>();
  DALI_CHECK_FAIL( result.angle != Radian(0.f), "PropertyValue::Get for Quarternion type has Failed." );
  DALI_CHECK_FAIL( result.axis != Vector3::ZERO, "PropertyValue::Get for Quarternion type has Failed." ); // identity quaternion returns a zero angle-axis

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsRotationTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Quarternion type or not.
 */
int UtcDaliPropertyValueConstructorsRotationTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_QUATERNIONTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsStringP(void)
{
  std::string v("1");
  Property::Value value(v);

  DALI_CHECK_FAIL( value.GetType() != Property::STRING , "PropertyValue Constuctor for String type has Failed.");
  DALI_CHECK_FAIL( value.Get<std::string>() != v , "PropertyValue::Get for String type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsStringP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for String type or not.
 */
int UtcDaliPropertyValueConstructorsStringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_STRING_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsStringTypeP(void)
{
  Property::Value value( Property::STRING );

  DALI_CHECK_FAIL( value.GetType() != Property::STRING , "PropertyValue Constuctor for String type has Failed.");
  DALI_CHECK_FAIL( value.Get<std::string>() != std::string() , "PropertyValue::Get for String type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsStringTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for String type or not.
 */
int UtcDaliPropertyValueConstructorsStringTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_STRINGTYPE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsArrayP(void)
{
  Property::Array foo;
  Property::Value value( foo );

  DALI_CHECK_FAIL( value.GetType() != Property::ARRAY , "PropertyValue Constuctor for Array type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Array>().Count() != 0 , "PropertyValue::Get for Array type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsArrayP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Array type or not.
 */
int UtcDaliPropertyValueConstructorsArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsArray2P(void)
{
  Property::Array foo;
  foo.PushBack( Property::Value() );
  Property::Value value( foo );

  DALI_CHECK_FAIL( value.GetType() != Property::ARRAY , "PropertyValue Constuctor for Array type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Array>().Count() != 1 , "PropertyValue::Get for Array type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsArray2P
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Array type or not.
 */
int UtcDaliPropertyValueConstructorsArray2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_ARRAY2_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsArrayTypeP(void)
{
  Property::Value value(Property::ARRAY);

  DALI_CHECK_FAIL( value.GetType() != Property::ARRAY, "PropertyValue Constuctor for Array type has Failed." );
  DALI_CHECK_FAIL( value.Get<Property::Array>().Count() != 0 , "PropertyValue::Get for Array type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsArrayTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Array type or not.
 */
int UtcDaliPropertyValueConstructorsArrayTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_ARRAYTYPE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsMapP(void)
{
  Property::Map map;
  Property::Value value( map );

  DALI_CHECK_FAIL( value.GetType() != Property::MAP , "PropertyValue Constuctor for Map type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Map>().Count() != 0 , "PropertyValue::Get for Map type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsMapP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Map type or not.
 */
int UtcDaliPropertyValueConstructorsMapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MAP_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsMap2P(void)
{
  Property::Map map;
  map.Insert( "", "" );
  Property::Value value( map );

  DALI_CHECK_FAIL( value.GetType() != Property::MAP , "PropertyValue Constuctor for Map type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Map>().Count() != 1 , "PropertyValue::Get for Map type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsMapP2
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Map type or not.
 */
int UtcDaliPropertyValueConstructorsMapP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MAP_P2);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueConstructorsMapTypeP(void)
{
  Property::Value value(Property::MAP);

  DALI_CHECK_FAIL( value.GetType() != Property::MAP , "PropertyValue Constuctor for Map type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Map>().Count() != 0 , "PropertyValue::Get for Map type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsMapTypeP
 * @since_tizen     2.4
 * @description     Check if the Constructor works for Map type or not.
 */
int UtcDaliPropertyValueConstructorsMapTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_MAPTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsInitializerListP(void)
{
  Property::Value value{ { "one", 1 }, { "two", 2 }, { "three", 3 } };

  DALI_CHECK_FAIL( value.GetType() != Property::MAP , "PropertyValue Constuctor for Map type has Failed.");
  DALI_CHECK_FAIL( value.Get<Property::Map>().Count() != 3 , "PropertyValue::Get for Map type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsInitializerListP
 * @since_tizen     5.5
 * @description     Check if the Constructor works for initializer_list or not.
 */
int UtcDaliPropertyValueConstructorsInitializerListP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_INITIALIZER_LIST_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsEnumP(void)
{
  enum class T {
    None, V1 = 1, V2 = 2
  };
  Property::Value value = T::V1;

  DALI_CHECK_FAIL( value.GetType() != Property::INTEGER , "PropertyValue Constuctor for Enumeration type has Failed.");
  DALI_CHECK_FAIL( value.Get<T>() != T::V1 , "PropertyValue::Get for Enumeration type has Failed.");

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueConstructorsEnumP
 * @since_tizen     5.5
 * @description     Check if the Constructor works for Enumeration type or not.
 */
int UtcDaliPropertyValueConstructorsEnumP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_ENUM_P );
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorP(void)
{
  Property::Value value;
  Property::Value value2( value );
  DALI_CHECK_FAIL( value.GetType() != value2.GetType() , "PropertyValue::GetType has Failed.");
  DALI_CHECK_FAIL( value.GetMap() != value2.GetMap(), "PropertyValue::GetMap has Failed.");
  DALI_CHECK_FAIL( value.GetArray() != value2.GetArray(), "PropertyValue::GetArray has Failed.");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for None type or not.
 */
int UtcDaliPropertyValueCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorBoolP(void)
{
  CheckCopyCtorP<bool> check(true);
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorBoolP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Boolean type or not.
 */
int UtcDaliPropertyValueCopyConstructorBoolP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_BOOL_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorFloatP(void)
{
  CheckCopyCtorP<float> check(1.f);
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorFloatP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Boolean type or not.
 */
int UtcDaliPropertyValueCopyConstructorFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorIntP(void)
{
  CheckCopyCtorP<int> check(1);
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorIntP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Int type or not.
 */
int UtcDaliPropertyValueCopyConstructorIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_INT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueCopyConstructoVector2P(void)
{
  CheckCopyCtorP<Vector2> check( Vector2(2,1) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructoVector2P
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Vector2 type or not.
 */
int UtcDaliPropertyValueCopyConstructoVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorVector3P(void)
{
  CheckCopyCtorP<Vector3> check( Vector3(3.f,2.f,1.f) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorVector3P
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Vector3 type or not.
 */
int UtcDaliPropertyValueCopyConstructorVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorVector4P(void)
{
  CheckCopyCtorP<Vector3> check( Vector4(4.f,3.f,2.f,1.f) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorVector4P
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Vector4 type or not.
 */
int UtcDaliPropertyValueCopyConstructorVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueCopyConstructorMatrix3P(void)
{
  CheckCopyCtorP<Matrix3> check( Matrix3::IDENTITY );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorMatrix3P
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Matrix3 type or not.
 */
int UtcDaliPropertyValueCopyConstructorMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorMatrixP(void)
{
  CheckCopyCtorP<Matrix> check(Matrix::IDENTITY);
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorMatrixP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Matrix type or not.
 */
int UtcDaliPropertyValueCopyConstructorMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorRectP(void)
{
  CheckCopyCtorP<Rect<int> > check( Rect<int>(1.0,1.0,1.0,1.0) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorRectP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Rect type or not.
 */
int UtcDaliPropertyValueCopyConstructorRectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_RECT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorAngleAxisP(void)
{
  CheckCopyCtorP<AngleAxis> check( AngleAxis(Degree(1.0), Vector3(1.0,1.0,1.0)) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorAngleAxisP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for AngleAxis type or not.
 */
int UtcDaliPropertyValueCopyConstructorAngleAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_ANGLEAXIS_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueCopyConstructorQuaternionP(void)
{
  CheckCopyCtorP<Quaternion> check( Quaternion( Vector4(1.0, 1.0, 1.0, 1.0) ) );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorQuaternionP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Quarternion type or not.
 */
int UtcDaliPropertyValueCopyConstructorQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_QUARTERNION_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueCopyConstructorStringP(void)
{
  CheckCopyCtorP<std::string> check( std::string("1") );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueCopyConstructorStringP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for String type or not.
 */
int UtcDaliPropertyValueCopyConstructorStringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_STRING_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorArrayP(void)
{
  Property::Value value1(Property::ARRAY);
  Property::Array* array= value1.GetArray();
  array->PushBack(Property::Value(1));

  Property::Value value2( value1 );
  DALI_CHECK_FAIL( value1.GetType() !=value2.GetType(), "PropertyValue::GetType has Failed." );
  DALI_CHECK_FAIL( value1.GetArray()->Count() != value2.GetArray()->Count(), "PropertyValue::GetArray has Failed." );

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorArrayP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Array type or not.
 */
int UtcDaliPropertyValueCopyConstructorArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueCopyConstructorMapP(void)
{
  Property::Value value1(Property::MAP);
  Property::Map* map = value1.GetMap();
  (*map)["1"] = Property::Value(1);

  Property::Value value2( value1 );
  DALI_CHECK_FAIL( value1.GetType() != value2.GetType(), "PropertyValue::GetType has Failed." );
  DALI_CHECK_FAIL( value1.GetMap()->Count() != value2.GetMap()->Count(), "PropertyValue::GetMap has Failed." );
  DALI_CHECK_FAIL( value1.GetMap()->GetKey( 0 ) != value2.GetMap()->GetKey( 0 ), "PropertyValue::GetMap for key has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueCopyConstructorMapP
 * @since_tizen     2.4
 * @description     Check if the Copy Constructor works for Map type or not.
 */
int UtcDaliPropertyValueCopyConstructorMapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_COPYCONSTRUCTOR_MAP_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentSelfP(void)
{
  Property::Value value;
  Property::Value* self = &value;
  value = *self;
  DALI_CHECK_FAIL( value.GetType() != Property::NONE, "PropertyValue::GetType has Failed.");
  DALI_CHECK_FAIL( value.GetMap() != NULL , "PropertyValue::GetMap has Failed.");
  DALI_CHECK_FAIL( value.GetArray() != NULL , "PropertyValue::GetArray has Failed.");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentSelfP
 * @since_tizen     2.4
 * @description     Check if the assignment operator works for Self.
 */
int UtcDaliPropertyValueAssignmentSelfP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_ASSIGNMENT_SELF_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorNoneP(void)
{
  Property::Value value;
  value = Property::Value(); // type match
  DALI_CHECK_FAIL( value.GetType() !=Property::NONE, "PropertyValue::GetType has Failed." );
  Property::Value copy( false );
  copy = value; // type mismatch
  DALI_CHECK_FAIL( value.GetType() != Property::NONE, "PropertyValue::GetType has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorNoneP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for None type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorNoneP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_NONE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorBoolP(void)
{
  Property::Value value;
  value = Property::Value(true); // type mismatch
  DALI_CHECK_FAIL( true != value.Get<bool>() , "PropertyValue::Get for Boolean Type has Failed. ");
  Property::Value copy( false );
  copy = value; // type match
  DALI_CHECK_FAIL( true != copy.Get<bool>() , "PropertyValue::Get for boolean type has Failed for copy constructed object. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorBoolP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Boolean type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorBoolP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_BOOL_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorIntP(void)
{
  Property::Value value;
  value = Property::Value(10); // type mismatch
  DALI_CHECK_FAIL( 10 != value.Get<int>() , "PropertyValue::Get for Integer Type has Failed. ");
  Property::Value copy( 99 );
  copy = value; // type match
  DALI_CHECK_FAIL( 10 != copy.Get<int>(), "PropertyValue::Get for Integer Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorIntP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Integer type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_INT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorFloatP(void)
{
  Property::Value value;
  value = Property::Value(10.f); // mismatch
  DALI_CHECK_FAIL( 10.f != value.Get<float>() , "PropertyValue::Get for float Type has Failed. ");
  Property::Value copy(321.f);
  copy = value; // match
  DALI_CHECK_FAIL( 10.f != copy.Get<float>() , "PropertyValue::Get for float Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorFloatP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Float type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorVector2P(void)
{
  Property::Value value;
  value = Property::Value( Vector2(1,2) ); // mismatch
  DALI_CHECK_FAIL( Vector2(1,2) != value.Get<Vector2>() , "PropertyValue::Get for Vector2 Type has Failed. ");
  Property::Value copy( Property::VECTOR2 );
  copy = value; // match
  DALI_CHECK_FAIL( Vector2(1,2) != copy.Get<Vector2>(), "PropertyValue::Get for Vector2 Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorVector2P
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Vector2 type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorVector3P(void)
{
  Property::Value value;
  value = Property::Value( Vector3(1.f,2.f,3.f) ); // mismatch
  DALI_CHECK_FAIL( Vector3(1.f,2.f,3.f) != value.Get<Vector3>(), "PropertyValue::Get for Vector3 Type has Failed. " );
  Property::Value copy( Property::VECTOR3 );
  copy = value; // match
  DALI_CHECK_FAIL( Vector3(1.f,2.f,3.f) != copy.Get<Vector3>() , "PropertyValue::Get for Vecto3 Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorVector3P
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Vector3 type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorVector4P(void)
{
  Property::Value value;
  value = Property::Value( Vector4(1,2,3,4) ); // mismatch
  DALI_CHECK_FAIL( Vector4(1,2,3,4) != value.Get<Vector4>() , "PropertyValue::Get for Vector4 Type has Failed. ");
  Property::Value copy( Vector4(0,1,2,3) );
  copy = value; // match
  DALI_CHECK_FAIL( Vector4(1,2,3,4) != copy.Get<Vector4>() , "PropertyValue::Get for Vector4 Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorVector4P
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Vector4 type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorMatrix3P(void)
{
  Property::Value value;
  value = Property::Value( Matrix3::IDENTITY ); // mismatch
  DALI_CHECK_FAIL( Matrix3::IDENTITY != value.Get<Matrix3>() , "PropertyValue::Get for Matrix3 Type has Failed. ");
  Property::Value copy( Property::MATRIX3 );
  copy = value; // match
  DALI_CHECK_FAIL( Matrix3::IDENTITY != copy.Get<Matrix3>() , "PropertyValue::Get for Matrix3 Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorMatrix3P
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Matrix3 type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorMatrixP(void)
{
  Property::Value value;
  value = Property::Value( Matrix::IDENTITY ); // mismatch
  DALI_CHECK_FAIL( Matrix::IDENTITY != value.Get<Matrix>()  , "PropertyValue::Get for Matrix Type has Failed. ");
  Matrix foo;
  Property::Value copy( foo );
  copy = value; // match
  DALI_CHECK_FAIL( Matrix::IDENTITY != copy.Get<Matrix>()  , "PropertyValue::Get for Matrix Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorMatrixP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Matrix type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorRectP(void)
{
  Property::Value value;
  typedef Dali::Rect<int> Rectangle;
  value = Property::Value( Rectangle(4,3,2,1) ); // mismatch
  DALI_CHECK_FAIL( Rectangle(4,3,2,1) != value.Get<Rectangle>() , "PropertyValue::Get for Rectangle Type has Failed. ");
  Property::Value copy( Property::RECTANGLE );
  copy = value; // match
  Rectangle copyRect;
  copy.Get(copyRect);
  DALI_CHECK_FAIL( Rectangle(4,3,2,1) != copyRect , "PropertyValue::Get for Rectangle Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorRectP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Rect type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorRectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_RECT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorQuaternionP(void)
{
  Property::Value value;
  value = Property::Value( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) ); // mismatch
  DALI_CHECK_FAIL( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) != value.Get<Quaternion>() , "PropertyValue::Get for Quarternion Type has Failed. ");
  Property::Value copy( Property::ROTATION );
  copy = value; // match
  DALI_CHECK_FAIL( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) != copy.Get<Quaternion>() , "PropertyValue::Get for Quarternion Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorQuaternionP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Quarternion type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_QUARTERNION_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorAngleAxisP(void)
{
  Property::Value value;
  value = Property::Value( AngleAxis( Radian(Math::PI_2), Vector3::XAXIS ) ); // mismatch
  DALI_CHECK_FAIL( value.Get<AngleAxis>().axis != Vector3::XAXIS, "PropertyValue::Get for AngleAxis Type has Failed. " );
  DALI_CHECK_FAIL( value.Get<AngleAxis>().angle != Radian(Math::PI_2), "PropertyValue::Get for AngleAxis Type has Failed. " );
  Property::Value copy( Property::ROTATION );
  copy = value; // match
  DALI_CHECK_FAIL( value.Get<AngleAxis>().axis != copy.Get<AngleAxis>().axis, "PropertyValue::Get for AngleAxis Type has Failed. ");
  DALI_CHECK_FAIL( value.Get<AngleAxis>().angle != copy.Get<AngleAxis>().angle, "PropertyValue::Get for AngleAxis Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorAngleAxisP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for AngleAxis type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorAngleAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_ANGLEAXIS_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorStringP(void)
{
  Property::Value value;
  value = Property::Value("yes"); // mismatch
  DALI_CHECK_FAIL( "yes" != value.Get<std::string>() , "PropertyValue::Get for String Type has Failed. ");
  Property::Value copy("no");
  copy = value; // match
  DALI_CHECK_FAIL( "yes" != copy.Get<std::string>(), "PropertyValue::Get for String Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorStringP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for String type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorStringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_STRING_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorArrayP(void)
{
  Property::Value value;
  value = Property::Value(Property::ARRAY); // mismatch
  value.GetArray()->PushBack(10);
  DALI_CHECK_FAIL( !value.GetArray() , "PropertyValue::GetArray has Failed. ");
  Property::Value copy(Property::ARRAY);
  copy = value; // match
  Property::Array array;
  copy.Get( array );
  int getItem = 0;
  array[0].Get( getItem );
  DALI_CHECK_FAIL( getItem != 10 , "PropertyValue::Get for Array Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorArrayP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Array type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueAssignmentOperatorMapP(void)
{
  Property::Value value;
  value = Property::Value(Property::MAP); // mismatch
  value.GetMap()->Insert("key", "value");
  Property::Value copy( Property::MAP ); // match
  copy = value;
  Property::Map map;
  copy.Get( map );
  DALI_CHECK_FAIL( map.GetKey(0) != "key" , "PropertyValue::Get for Map Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorMapP
 * @since_tizen     2.4
 * @description     Check if assignment operator works for Map type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorMapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_MAP_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetTypeP(void)
{
  Property::Value value;
  DALI_CHECK_FAIL( value.GetType() != Property::NONE , "PropertyValue::GetType for NONE has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetTypeP
 * @since_tizen     2.4
 * @description     Check if Get api is working for None type or not.
 */
int UtcDaliPropertyValueGetTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_NONE_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetBoolP(void)
{
  Property::Value value(true);
  bool boolean( false );
  DALI_CHECK_FAIL( value.Get( boolean ) != true , "PropertyValue::Get for Boolean Type has Failed. ");
  DALI_CHECK_FAIL( value.Get<bool>() != true , "PropertyValue::Get for Boolean Type has Failed. ");
  std::string string;
  DALI_CHECK_FAIL( value.Get( string ) != false , "PropertyValue::Get for String Type has Failed. ");
  value = Property::Value(1.f);
  DALI_CHECK_FAIL( value.Get<float>() != 1.f , "PropertyValue::Get for Float Type has Failed. ");
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetBoolP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Boolean type or not.
 */
int UtcDaliPropertyValueGetBoolP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_BOOL_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetBoolN(void)
{
  Property::Value value;
  DALI_CHECK_FAIL( value.Get<bool>() != false , "PropertyValue::Get for Boolean Type has Failed. ");
  bool boolean( false );
  DALI_CHECK_FAIL( value.Get( boolean ) != false , "PropertyValue::Get for Boolean Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetBoolN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Boolean type or not.
 */
int UtcDaliPropertyValueGetBoolN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_BOOL_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetFloatP(void)
{
  Property::Value value(1.1f);
  float flow( 0.0f );
  DALI_CHECK_FAIL( 1.1f !=value.Get<float>(), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( flow ), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( 1.1f != flow, "PropertyValue::Get for float Type has Failed. " );

  Property::Value intValue(100);
  DALI_CHECK_FAIL( 100.f != intValue.Get<float>(), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( true != intValue.Get( flow ), "PropertyValue::Get for Integer Type has Failed. " );
  DALI_CHECK_FAIL( 100.f != flow, "PropertyValue::Get for float Type has Failed. " );

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetFloatP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Float type or not.
 */
int UtcDaliPropertyValueGetFloatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_FLOAT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetFloatN(void)
{
  Property::Value value;
  float result( 1.0f );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( 1.0f != result, "PropertyValue::Get for float Type has Failed. " ); // result is not modified
  Property::Value value2( "" );
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for boolean Type has Failed. " );
  DALI_CHECK_FAIL( 1.0f != result, "PropertyValue::Get for float Type has Failed. " ); // result is not modified
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetFloatN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Float type or not.
 */
int UtcDaliPropertyValueGetFloatN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_FLOAT_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetIntP(void)
{
  Property::Value value(123);
  int result( 10 );
  DALI_CHECK_FAIL( 123 != value.Get<int>(), "PropertyValue::Get for Integer Type has Failed. ");
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Integer Type has Failed. " );
  DALI_CHECK_FAIL( 123 != result, "PropertyValue::Get for Integer Type has Failed. " );

  Property::Value floatValue(21.f);
  DALI_CHECK_FAIL( 21 != floatValue.Get<int>(), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( true != floatValue.Get( result ), "PropertyValue::Get for float Type has Failed. " );
  DALI_CHECK_FAIL( 21 != result, "PropertyValue::Get for float Type has Failed. " );

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetIntP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Integer type or not.
 */
int UtcDaliPropertyValueGetIntP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_INT_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetIntN(void)
{
  Property::Value value;
  int result( 10 );
  DALI_CHECK_FAIL( 0 !=value.Get<int>(), "PropertyValue::Get for Integer Type has Failed. ");
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Integer Type has Failed. " );
  DALI_CHECK_FAIL( 10 != result, "PropertyValue::Get for Integer Type has Failed. " ); // result is not modified
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Boolean Type has Failed. " );
  DALI_CHECK_FAIL( 10 != result, "PropertyValue::Get for Integer Type has Failed. " ); // result is not modified
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetIntN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Integer type or not.
 */
int UtcDaliPropertyValueGetIntN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_INT_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetRectP(void)
{
  Property::Value value( Rect<int>(1,2,3,4) );
  Rect<int> result(4,3,2,1);
  DALI_CHECK_FAIL( Rect<int>(1,2,3,4) != value.Get< Rect<int> >(), "PropertyValue::Get for Rectangle Type has Failed. ");
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Rectangle Type has Failed. " );
  DALI_CHECK_FAIL( Rect<int>(1,2,3,4) != result, "PropertyValue::Get for Rectangle Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetRectP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Rect type or not.
 */
int UtcDaliPropertyValueGetRectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_RECT_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetRectN(void)
{
  Property::Value value;
  Rect<int> result(4,3,2,1);
  DALI_CHECK_FAIL( Rect<int>(0,0,0,0) != value.Get< Rect<int> >(), "PropertyValue::Get for Rectangle Type has Failed. "  );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Rectangle Type has Failed. "  );
  DALI_CHECK_FAIL( Rect<int>(4,3,2,1) != result, "PropertyValue::Get for Rectangle Type has Failed. "  );
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Rectangle Type has Failed. "  );
  DALI_CHECK_FAIL( Rect<int>(4,3,2,1) != result, "PropertyValue::Get for Rectangle Type has Failed. "  );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetRectN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Rect type or not.
 */
int UtcDaliPropertyValueGetRectN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_RECT_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetVector2P(void)
{
  Property::Value value( Vector2(1.0f,2.0f) );
  Vector2 result;
  DALI_CHECK_FAIL( Vector2(1.0f,2.0f) != value.Get< Vector2 >(), "PropertyValue::Get for Vector2 Type has Failed. "  );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Vector2 Type has Failed. " );
  DALI_CHECK_FAIL( Vector2(1.0f,2.0f) != result, "PropertyValue::Get for Vector2 Type has Failed. "  );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetVector2P
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector2 type or not.
 */
int UtcDaliPropertyValueGetVector2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR2_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetVector2N(void)
{
  Property::Value value;
  Vector2 result;
  DALI_CHECK_FAIL( Vector2(0.f,0.f) != value.Get< Vector2 >(), "PropertyValue::Get for Vector2 Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Vector2 Type has Failed. "  );
  DALI_CHECK_FAIL( Vector2() != result, "PropertyValue::Get for Vector2 Type has Failed. "  );
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Vector2 Type has Failed. "  );
  DALI_CHECK_FAIL( Vector2() != result, "PropertyValue::Get for Vector2 Type has Failed. "  );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetVector2N
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector2 type or not.
 */
int UtcDaliPropertyValueGetVector2N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR2_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetVector3P(void)
{
  Property::Value value( Vector3(1.0f,2.0f,-1.f) );
  Vector3 result;
  DALI_CHECK_FAIL( Vector3(1.0f,2.0f,-1.f) != value.Get< Vector3 >(), "PropertyValue::Get for Vector3 Type has Failed. "  );
  DALI_CHECK_FAIL( true != value.Get( result ) , "PropertyValue::Get for Vector3 Type has Failed. " );
  DALI_CHECK_FAIL( Vector3(1.0f,2.0f,-1.f) != result, "PropertyValue::Get for Vector3 Type has Failed. "  );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetVector3P
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector3 type or not.
 */
int UtcDaliPropertyValueGetVector3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetVector3N(void)
{
  Property::Value value;
  Vector3 result;
  DALI_CHECK_FAIL( Vector3(0.f,0.f,0.f) != value.Get< Vector3 >(), "PropertyValue::Get for Vector3 Type has Failed. "  );
  DALI_CHECK_FAIL( false != value.Get( result ) , "PropertyValue::Get for Vector3 Type has Failed. " );
  DALI_CHECK_FAIL( Vector3() != result, "PropertyValue::Get for Vector3 Type has Failed. " );
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Vector3 Type has Failed. " );
  DALI_CHECK_FAIL( Vector3() != result, "PropertyValue::Get for Vector3 Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetVector3N
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector3 type or not.
 */
int UtcDaliPropertyValueGetVector3N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR3_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetVector4P(void)
{
  Property::Value value( Vector4(1.f,2.f,-1.f,-3.f) );
  Vector4 result;
  DALI_CHECK_FAIL( Vector4(1.f,2.f,-1.f,-3.f) != value.Get< Vector4 >(), "PropertyValue::Get for Vector4 Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Vector4 Type has Failed. " );
  DALI_CHECK_FAIL( Vector4(1.f,2.f,-1.f,-3.f) != result, "PropertyValue::Get for Vector4 Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetVector4P
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector4 type or not.
 */
int UtcDaliPropertyValueGetVector4P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR4_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetVector4N(void)
{
  Property::Value value;
  Vector4 result;
  DALI_CHECK_FAIL( Vector4(0.f,0.f,0.f,0.f) != value.Get< Vector4 >(), "PropertyValue::Get for Vector4 Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Vector4 Type has Failed. " );
  DALI_CHECK_FAIL( Vector4() != result, "PropertyValue::Get for Vector4 Type has Failed. " );
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Vector4 Type has Failed. " );
  DALI_CHECK_FAIL( Vector4() != result, "PropertyValue::Get for Vector4 Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetVector4N
 * @since_tizen     2.4
 * @description     Check if Get api is working for Vector4 type or not.
 */
int UtcDaliPropertyValueGetVector4N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_VECTOR4_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetMatrix3P(void)
{
  Property::Value value( Matrix3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f) );
  Matrix3 result;
  DALI_CHECK_FAIL( Matrix3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f) != value.Get< Matrix3 >(), "PropertyValue::Get for Matrix3 Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Matrix3 Type has Failed. " );
  DALI_CHECK_FAIL( Matrix3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f) != result, "PropertyValue::Get for Matrix3 Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetMatrix3P
 * @since_tizen     2.4
 * @description     Check if Get api is working for Matrix3 type or not.
 */
int UtcDaliPropertyValueGetMatrix3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MATRIX3_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetMatrix3N(void)
{
  Property::Value value;
  Matrix3 result(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f);
  DALI_CHECK_FAIL( Matrix3() != value.Get< Matrix3 >(), "PropertyValue::Get for Matrix3 Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Matrix3 Type has Failed. " );
  DALI_CHECK_FAIL( Matrix3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f) != result, "PropertyValue::Get for Matrix3 Type has Failed. " );
  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Matrix3 Type has Failed. " );
  DALI_CHECK_FAIL( Matrix3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f) != result, "PropertyValue::Get for Matrix3 Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetMatrix3N
 * @since_tizen     2.4
 * @description     Check if Get api is working for Matrix3 type or not.
 */
int UtcDaliPropertyValueGetMatrix3N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MATRIX3_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetMatrixP(void)
{
  float matrixValues[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
  Matrix input( matrixValues );
  Property::Value value( input );
  Matrix result;
  DALI_CHECK_FAIL( input != value.Get< Matrix >(), "PropertyValue::Get for Matrix Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Matrix Type has Failed. " );
  DALI_CHECK_FAIL( input != result, "PropertyValue::Get for Matrix Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetMatrixP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Matrix type or not.
 */
int UtcDaliPropertyValueGetMatrixP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MATRIX_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetMatrixN(void)
{
  Property::Value value;
  Matrix result( Matrix::IDENTITY );
  DALI_CHECK_FAIL( Matrix() !=value.Get< Matrix >(), "PropertyValue::Get for Matrix Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Matrix Type has Failed. " );
  DALI_CHECK_FAIL( Matrix::IDENTITY != result, "PropertyValue::Get for Matrix Type has Failed. " );

  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Matrix Type has Failed. " );
  DALI_CHECK_FAIL( Matrix::IDENTITY != result, "PropertyValue::Get for Matrix Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetMatrixN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Matrix type or not.
 */
int UtcDaliPropertyValueGetMatrixN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MATRIX_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetAngleAxisP(void)
{
  AngleAxis input( Dali::ANGLE_90, Vector3::XAXIS );
  Property::Value value( input );
  AngleAxis result = value.Get<AngleAxis>();
  DALI_CHECK_FAIL( input.angle != result.angle, "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( input.axis != result.axis, "PropertyValue::Get for Angle Axis Type has Failed. " );

  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( !(input == result), "PropertyValue::Get for Angle Axis Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetAngleAxisP
 * @since_tizen     2.4
 * @description     Check if Get api is working for AngleAxis type or not.
 */
int UtcDaliPropertyValueGetAngleAxisP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ANGLEAXIS_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetAngleAxisN(void)
{
  Property::Value value;
  AngleAxis b = value.Get<AngleAxis>();
  AngleAxis result;
  DALI_CHECK_FAIL( 0.f != b.angle, "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( Vector3::ZERO != b.axis, "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( !(AngleAxis() == result), "PropertyValue::Get for Angle Axis Type has Failed. " );

  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Angle Axis Type has Failed. " );
  DALI_CHECK_FAIL( !(AngleAxis() == result), "PropertyValue::Get for Angle Axis Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetAngleAxisN
 * @since_tizen     2.4
 * @description     Check if Get api is working for AngleAxis type or not.
 */
int UtcDaliPropertyValueGetAngleAxisN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ANGLEAXIS_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetQuaternionP(void)
{
  Property::Value value( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) );
  Quaternion result( 0.f, 0.f, 0.f, 0.f );
  DALI_CHECK_FAIL( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) != value.Get< Quaternion >(), "PropertyValue::Get for Quarternion Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Quarternion Type has Failed. " );
  DALI_CHECK_FAIL( Quaternion( Radian( Math::PI_2 ), Vector3( 0.f, 1.f, 0.f ) ) != result, "PropertyValue::Get for Quarternion Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetQuaternionP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Quarternion type or not.
 */
int UtcDaliPropertyValueGetQuaternionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_QUARTERNION_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetQuaternionN(void)
{
  Property::Value value;
  Quaternion result(1.f,2.f,3.f,4.f);
  DALI_CHECK_FAIL( Quaternion() != value.Get< Quaternion >(), "PropertyValue::Get for Quarternion Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Quarternion Type has Failed. " );
  DALI_CHECK_FAIL( Quaternion(1.f,2.f,3.f,4.f) != result, "PropertyValue::Get for Quarternion Type has Failed. " );

  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Quarternion Type has Failed. " );
  DALI_CHECK_FAIL( Quaternion(1.f,2.f,3.f,4.f) != result, "PropertyValue::Get for Quarternion Type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueGetQuaternionN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Quarternion type or not.
 */
int UtcDaliPropertyValueGetQuaternionN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_QUARTERNION_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetStringP(void)
{
  Property::Value value( std::string("hello") );
  std::string result;
  DALI_CHECK_FAIL( std::string("hello") != value.Get< std::string >(), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( std::string("hello") != result, "PropertyValue::Get for String Type has Failed. " );

  Property::Value value2( "C hi!" );
  DALI_CHECK_FAIL( "C hi!" != value2.Get< std::string >(), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( true != value2.Get( result ), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( "C hi!" != result, "PropertyValue::Get for String Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetStringP
 * @since_tizen     2.4
 * @description     Check if Get api is working for String type or not.
 */
int UtcDaliPropertyValueGetStringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_STRING_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetStringN(void)
{
  Property::Value value;
  std::string result("doesn't change");
  DALI_CHECK_FAIL( std::string() != value.Get< std::string >(), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( "doesn't change" != result, "PropertyValue::Get for String Type has Failed. " );

  Property::Value value2(10);
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( "doesn't change" != result, "PropertyValue::Get for String Type has Failed. " );

  Property::Value value3((char*)NULL);
  DALI_CHECK_FAIL( true != value3.Get( result ), "PropertyValue::Get for String Type has Failed. " );
  DALI_CHECK_FAIL( std::string() != result, "PropertyValue::Get for String Type has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetStringN
 * @since_tizen     2.4
 * @description     Check if Get api is working for String type or not.
 */
int UtcDaliPropertyValueGetStringN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_STRING_N);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetArrayP(void)
{
  Property::Value value( Property::ARRAY );
  DALI_CHECK_FAIL( NULL == value.GetArray(), "PropertyValue::Get for Array Type has Failed. " );
  value.GetArray()->PushBack( Property::Value(1) );
  Property::Array got = value.Get<Property::Array>();
  DALI_CHECK_FAIL( got[0].Get<int>() != 1, "PropertyValue::Get for Array Type has Failed. ");
  Property::Array result;
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get for Array Type has Failed. ");
  DALI_CHECK_FAIL( result[0].Get<int>() != 1, "PropertyValue::Get for Array Type has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetArrayP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Array type or not.
 */
int UtcDaliPropertyValueGetArrayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ARRAY_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetArrayN(void)
{
  Property::Value value;
  DALI_CHECK_FAIL( NULL != value.GetArray() , "PropertyValue::Get for Array Type has Failed. ");
  Property::Array result;
  result.PushBack( Property::Value( 10 ) );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get for Array Type has Failed. " );
  DALI_CHECK_FAIL( 1 != result.Count(), "PropertyValue::Get for Array Type has Failed. "  ); // array is not modified

  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::Get for Array Type has Failed. " );
  DALI_CHECK_FAIL( 1 != result.Count(), "PropertyValue::Get for Array Type has Failed. "  ); // array is not modified
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetArrayN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Array type or not.
 */
int UtcDaliPropertyValueGetArrayN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ARRAY_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetMapP(void)
{
  Property::Value value(Property::MAP);
  DALI_CHECK_FAIL( NULL != value.GetArray() , "PropertyValue::GetArray has Failed. ");
  DALI_CHECK_FAIL( NULL == value.GetMap(), "PropertyValue::GetMap has Failed. " );
  value.GetMap()->Insert("key", Property::Value(1));
  Property::Map result = value.Get<Property::Map>();
  DALI_CHECK_FAIL(result.Find("key")->Get<int>() != 1, "PropertyValue::Get has Failed. ");
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get has Failed. " );
  DALI_CHECK_FAIL(result.Find("key")->Get<int>() != 1, "PropertyValue::Get has Failed. ");
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetMapP
 * @since_tizen     2.4
 * @description     Check if Get api is working for Map type or not.
 */
int UtcDaliPropertyValueGetMapP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MAP_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetMapN(void)
{
  Property::Value value;
  DALI_CHECK_FAIL( NULL != value.GetMap() , "PropertyValue::Get for Array Type has Failed. ");
  DALI_CHECK_FAIL( 0 != value.Get<Property::Map>().Count(), "PropertyValue::Get for Map type has Failed. " );
  Property::Map result;
  result.Insert("key", "value" );
  DALI_CHECK_FAIL( false != value.Get( result ), "PropertyValue::Get has Failed. " );
  DALI_CHECK_FAIL( 1 != result.Count(), "PropertyValue::GetMap has Failed. " );

  Property::Value value2("");
  DALI_CHECK_FAIL( false != value2.Get( result ), "PropertyValue::GetMap has Failed. " );
  DALI_CHECK_FAIL( 1 != result.Count(), "PropertyValue::GetMap has Failed. "  ); // array is not modified
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetMapN
 * @since_tizen     2.4
 * @description     Check if Get api is working for Map type or not.
 */
int UtcDaliPropertyValueGetMapN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_MAP_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetEnumP(void)
{
  enum class T {
    None, V1 = 1, V2 = 2
  };

  Property::Value value1 = T::V1;
  Property::Value value2 = T::V2;
  DALI_CHECK_FAIL( T::V1 != value1.Get<T>(), "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( T::V2 != value2.Get<T>(), "PropertyValue::Get for Enumeration Type has Failed." );

  T result = T::None;
  DALI_CHECK_FAIL( !value1.Get(result), "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( result != T::V1, "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( !value2.Get(result), "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( result != T::V2, "PropertyValue::Get for Enumeration Type has Failed." );

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetEnumP
 * @since_tizen     5.5
 * @description     Check if Get api is working for Enumeration type or not.
 */
int UtcDaliPropertyValueGetEnumP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ENUM_P);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueGetEnumN(void)
{
  enum class T {
    None, V1 = 1, V2 = 2
  };

  Property::Value value;
  T result = T::None;
  DALI_CHECK_FAIL( T::None != value.Get<T>(), "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( value.Get( result ), "PropertyValue::Get for Enumeration Type has Failed." );
  DALI_CHECK_FAIL( T::None != result, "PropertyValue::Get for Enumeration Type has Failed. " );

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetEnumN
 * @since_tizen     5.5
 * @description     Check if Get api is working for Enumeration type or not.
 */
int UtcDaliPropertyValueGetEnumN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_ENUM_N);
  application.MainLoop();
  return test_return_value;
}


void PropertyValueOutputStreamP(void)
{
  typedef Dali::Rect<int> Rectangle;

  Property::Value value(true);
  {
    std::ostringstream stream;
    stream << value;
    DALI_CHECK_FAIL( stream.str() != "1" , "PropertyValue::operator <<  for bool has Failed. ");
  }

  {
    Property::Value empty;
    std::ostringstream stream;
    stream << empty;
    DALI_CHECK_FAIL( stream.str() != "undefined type", "PropertyValue::operator <<  has Failed. " );
  }


  {
    Property::Value empty( Property::NONE );
    std::ostringstream stream;
    stream << empty;
    DALI_CHECK_FAIL( stream.str() != "undefined type" , "PropertyValue::operator <<  for None type has Failed. ");
  }

  {
    value = Property::Value(20.2f);
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "20.2", "PropertyValue::operator <<  for float type has Failed. " );
  }

  {
    value = Property::Value(-25);
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "-25" , "PropertyValue::operator <<  for Integer type has Failed. " );
  }

  {
    value = Property::Value( Vector2(1.f,1.f) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[1, 1]" , "PropertyValue::operator <<  for Vector2 type has Failed. ");
  }

  {
    value = Property::Value( Vector3(1.f,1.f,1.f) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[1, 1, 1]", "PropertyValue::operator <<  for Vector3 type has Failed. " );
  }

  {
    value = Property::Value( Vector4(-4.f,-3.f,-2.f,-1.f) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[-4, -3, -2, -1]", "PropertyValue::operator <<  for Vector4 type has Failed. " );
  }

  {
    value = Property::Value( Matrix3::IDENTITY );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[ 1, 0, 0, 0, 1, 0, 0, 0, 1 ]" , "PropertyValue::operator <<  for Matrix3 type has Failed. ");
  }

  {
    value = Property::Value( Matrix::IDENTITY );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 ]" , "PropertyValue::operator <<  for Matrix type has Failed. ");
  }

  {
    value = Property::Value( Rectangle(1,2,3,4) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[1, 2, 3, 4]" , "PropertyValue::operator <<  for Rectangle type has Failed. ");
  }

  {
    value = Property::Value( AngleAxis( Dali::ANGLE_120, Vector3::XAXIS ) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "[ Axis: [1, 0, 0], Angle: 120 degrees ]", "PropertyValue::operator <<  for AngleAxis type has Failed. " );
  }

  {
    value = Property::Value( std::string( "Foo" ) );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str() != "Foo" , "PropertyValue::operator <<  for String type has Failed. ");
  }

  // Maps and arrays currently not supported, we just check a message is output
  {
    Property::Map map;
    value = Property::Value( map );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str().empty() , "PropertyValue::operator <<  for Map type has Failed. ");
  }

  {
    Property::Array array;
    value = Property::Value( array );
    std::ostringstream stream;
    stream <<  value;
    DALI_CHECK_FAIL( stream.str().empty() , "PropertyValue::operator <<  for Array type has Failed. ");
  }

  {
     value = Property::Value( Extents( 1u, 2u, 3u, 4u ) );
     std::ostringstream stream;
     stream <<  value;
     DALI_CHECK_FAIL( stream.str() != "[1, 2, 3, 4]", "PropertyValue::operator << for Extents type has Failed. " );
   }

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueOutputStream
 * @since_tizen     2.4
 * @description     Check if operator<< api is working for all types or not.
 */
int UtcDaliPropertyValueOutputStreamP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OUTPUTSTREAM_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsExtentsTypeP(void)
{
  Property::Value value(Property::EXTENTS);

  DALI_CHECK_FAIL( value.GetType() != Property::EXTENTS , "PropertyValue Constuctor for Extents type has Failed.");
  DALI_CHECK_FAIL( value.Get<Extents>() != Extents( 0u, 0u, 0u, 0u ) , "PropertyValue::Get for Extents type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsExtentsTypeP
 * @since_tizen     4.0
 * @description     Check if the Constructor works for Extents type or not.
 */
int UtcDaliPropertyValueConstructorsExtentsTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueConstructorsExtentsType2P(void)
{
  Property::Value value(Property::VECTOR4);

  DALI_CHECK_FAIL( value.GetType() != Property::VECTOR4 , "PropertyValue Constuctor for Vector4 type has Failed.");
  DALI_CHECK_FAIL( value.Get<Extents>() != Extents( 0u, 0u, 0u, 0u ) , "PropertyValue::Get for Extents type has Failed.");

  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueConstructorsExtentsType2P
 * @since_tizen     4.0
 * @description     Check if the Constructor works for Extents type or not.
 */
int UtcDaliPropertyValueConstructorsExtentsType2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_CONSTRUCTOR_EXTENTSTYPE2_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueAssignmentOperatorExtentsP(void)
{
  Property::Value value;
  value = Property::Value( Extents( 4, 3, 2, 1 ) ); // mismatch
  Property::Value copy( Property::EXTENTS );
  copy = value; // match
  Extents copyExtents;
  copy.Get(copyExtents);
  DALI_CHECK_FAIL( Extents( 4, 3, 2, 1 ) != copyExtents, "PropertyValue::Get for Extents type has Failed. " );
  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliPropertyValueAssignmentOperatorExtentsP
 * @since_tizen     4.0
 * @description     Check if assignment operator works for Extents type or not.
 */
int UtcDaliPropertyValueAssignmentOperatorExtentsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_OPERATORASSIGNMENT_EXTENTS_P);
  application.MainLoop();
  return test_return_value;
}

void PropertyValueGetExtentsP(void)
{
  Property::Value value( Extents( 1u, 2u, 3u, 4u ) );
  Extents result( 4u, 3u, 2u, 1u );
  DALI_CHECK_FAIL( Extents( 1u, 2u, 3u, 4u ) != value.Get<Extents>(), "PropertyValue::Get has Failed. " );
  DALI_CHECK_FAIL( true != value.Get( result ), "PropertyValue::Get has Failed. " );
  DALI_CHECK_FAIL( Extents( 1u, 2u, 3u, 4u )!= result, "PropertyValue::Get has Failed. " );
  DaliLog::PrintPass();
}
/**
 * @testcase        UtcDaliPropertyValueGetExtentsP
 * @since_tizen     4.0
 * @description     Check if Get api is working for Extents type or not.
 */
int UtcDaliPropertyValueGetExtentsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Value_TestApp testApp( application, PROPERTY_VALUE_GET_EXTENTS_P);
  application.MainLoop();
  return test_return_value;
}
