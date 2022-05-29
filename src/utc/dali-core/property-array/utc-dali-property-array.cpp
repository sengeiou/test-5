#include "utc-dali-property-array-common.h"
#include <dlog.h>

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_PropertyArray_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyArray_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_PropertyArray_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_PropertyArray_cleanup(void)
{

}

bool FloatCompare(float value1, float value2, float epsilon)
{
	return fabsf(value1 - value2)<epsilon;
}


void PropertyArrayConstructor();
void PropertyArrayConstructorInitializerList();
void PropertyArrayCopyConstructor();
void PropertyArraySize();
void PropertyArrayCount();
void PropertyArrayEmpty();
void PropertyArrayClear();
void PropertyArrayReserve();
void PropertyArrayResize();
void PropertyArrayAddP();
void PropertyArrayCapacity();
void PropertyArrayPushBack();
void PropertyArrayGetElementAt();
void PropertyArrayOperatorAssignment();
void PropertyArrayOperatorAssignmentP2();

namespace
{
  enum TEST_CASES_LIST_PROPERTY_ARRAY
  {
    PROPERTY_ARRAY_CONSTRUCTOR,
    PROPERTY_ARRAY_CONSTRUCTOR_INITIALIZER_LIST,
    PROPERTY_ARRAY_COPY_CONSTRUCTOR,
    PROPERTY_ARRAY_SIZE,
    PROPERTY_ARRAY_COUNT,
    PROPERTY_ARRAY_EMPTY,
    PROPERTY_ARRAY_CLEAR,
    PROPERTY_ARRAY_ADD,
    PROPERTY_ARRAY_RESERVE,
    PROPERTY_ARRAY_RESIZE,
    PROPERTY_ARRAY_CAPACITY,
    PROPERTY_ARRAY_PUSHBACK,
    PROPERTY_ARRAY_GET_ELEMENT_AT,
    PROPERTY_ARRAY_ASSIGNMENT_OPERATOR,
    PROPERTY_ARRAY_ASSIGNMENT_OPERATOR_P2
  };

  struct Property_Array_TestApp : public ConnectionTracker
  {
    Property_Array_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Property_Array_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Property_Array_TestApp::Tick );
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

        case PROPERTY_ARRAY_CONSTRUCTOR:
          PropertyArrayConstructor();
          break;

        case PROPERTY_ARRAY_CONSTRUCTOR_INITIALIZER_LIST:
          PropertyArrayConstructorInitializerList();
          break;

        case PROPERTY_ARRAY_COPY_CONSTRUCTOR:
          PropertyArrayCopyConstructor();
          break;

        case PROPERTY_ARRAY_SIZE:
          PropertyArraySize();
          break;

        case PROPERTY_ARRAY_COUNT:
          PropertyArrayCount();
          break;

        case PROPERTY_ARRAY_EMPTY:
          PropertyArrayEmpty();
          break;

        case PROPERTY_ARRAY_CLEAR:
          PropertyArrayClear();
          break;

        case PROPERTY_ARRAY_RESERVE:
          PropertyArrayReserve();
          break;

        case PROPERTY_ARRAY_ADD:
          PropertyArrayAddP();
          break;

        case PROPERTY_ARRAY_RESIZE:
          PropertyArrayResize();
          break;

        case PROPERTY_ARRAY_CAPACITY:
          PropertyArrayCapacity();
          break;

        case PROPERTY_ARRAY_PUSHBACK:
          PropertyArrayPushBack();
          break;

        case PROPERTY_ARRAY_GET_ELEMENT_AT:
          PropertyArrayGetElementAt();
          break;

        case PROPERTY_ARRAY_ASSIGNMENT_OPERATOR:
          PropertyArrayOperatorAssignment();
          break;

        case PROPERTY_ARRAY_ASSIGNMENT_OPERATOR_P2:
          PropertyArrayOperatorAssignmentP2();
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
void PropertyArrayConstructor()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property array should be empty by default ");

  propArray.Reserve(5);

  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);
  propArray.PushBack("world");
  propArray.PushBack("beautiful");

  DALI_CHECK_FAIL(propArray[2].Get<int>() != 3, "property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(propArray[4].Get<std::string>() != "beautiful", "property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArrayConstructorInitializerList()
{
  Property::Array propArray{ 1, 2, 3, "world", "beautiful" };

  DALI_CHECK_FAIL(propArray[2].Get<int>() != 3, "property array failed to retrieved correct value ");
  DALI_CHECK_FAIL(propArray[4].Get<std::string>() != "beautiful", "property array failed to retrieve correct value ");

  DaliLog::PrintPass();
}
void PropertyArrayCopyConstructor()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property array should be empty by default ");

  propArray.Reserve(5);

  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);
  propArray.PushBack("world");
  propArray.PushBack("beautiful");
  const Property::Array copyArray(propArray);

  DALI_CHECK_FAIL(copyArray[2].Get<int>() != 3, "Copied property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(copyArray[4].Get<std::string>() != "beautiful", "Copied property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArraySize()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(propArray.Size() != 0, "property array is failed to get it's initial size zero ");

  propArray.PushBack(1);
  DALI_CHECK_FAIL(propArray.Size() != 1, "property array is failed to get it's assigned size ");

  DALI_CHECK_FAIL(propArray[0].Get<int>() != 1, "property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArrayCount(void)
{
  Property::Array propArray;
  int nCount = 0;

  DALI_CHECK_FAIL(propArray.Size() != 0, "property array is failed to get it's initial size zero ");

  nCount = propArray.Count();
  DALI_CHECK_FAIL( 0 != nCount,"property array count should be 0 " );

  propArray.PushBack( 1 );
  propArray.PushBack( "world" );
  propArray.PushBack( 3 );

  nCount = propArray.Count();
  DALI_CHECK_FAIL( 3 != nCount , "property array count should be 3 ");

  DaliLog::PrintPass();

}
void PropertyArrayEmpty()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.PushBack(1);
  propArray.PushBack( "world" );
  propArray.PushBack( 3 );

  DALI_CHECK_FAIL(propArray.Empty(), "property is not empty which is not expected ");

  DaliLog::PrintPass();
}
void PropertyArrayClear()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.PushBack(1);
  propArray.PushBack( "world" );
  propArray.PushBack( 3 );

  DALI_CHECK_FAIL(propArray.Empty(), "property is not empty which is not expected ");

  propArray.Clear();
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  DaliLog::PrintPass();
}
void PropertyArrayReserve()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property array should be empty by default ");

  propArray.Reserve(5);
  DALI_CHECK_FAIL(propArray.Capacity() != 5, "property array is failed to get it's array capacity ");
  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);
  DALI_CHECK_FAIL(propArray[2].Get<int>() != 3, "property array is failed to retrieved it's array value ");
  propArray.Clear();
  DALI_CHECK_FAIL(!propArray.Empty(), "property array is failed to empty its size ");

  DaliLog::PrintPass();
}
void PropertyArrayResize()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.Resize(3);
  DALI_CHECK_FAIL(!propArray.Count() == 3 , "property is not empty which is not expected ");

  propArray.Resize(5);
  DALI_CHECK_FAIL(!propArray.Count() == 5 , "property is not empty which is not expected ");

  DaliLog::PrintPass();
}
void PropertyArrayAddP()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.Add( 1 );

  DALI_CHECK_FAIL( 1 != propArray.Size(), " property array count value is not which is not expected");
  DALI_CHECK_FAIL( propArray[0].Get<int>() != 1, " property array element value is not matched ");

  propArray.Add( 2 )
       .Add( 3 )
       .Add( 4.f );

  DALI_CHECK_FAIL( 4 != propArray.Size(), " property array count value is not which is not expected");

  DALI_CHECK_FAIL( propArray[1].Get<int>()   != 2,   " property array element value is not matched ");
  DALI_CHECK_FAIL( propArray[2].Get<int>()   != 3,   " property array element value is not matched ");
  DALI_CHECK_FAIL( !FloatCompare(propArray[3].Get<float>(),4.f, Math::MACHINE_EPSILON_1), " property array element value is not matched ");
  DaliLog::PrintPass();;
}
void PropertyArrayCapacity()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.Reserve(3);
  DALI_CHECK_FAIL(!propArray.Capacity() == 3 , "property capacity is not which is not expected ");

  DaliLog::PrintPass();
}
void PropertyArrayPushBack()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.PushBack(1);
  DALI_CHECK_FAIL(propArray.Size() != 1, "property array count value is not which is not expected ");

  propArray.PushBack(2);
  DALI_CHECK_FAIL(propArray[1].Get<int>() != 2, "property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArrayGetElementAt()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property is not empty which is not expected ");

  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);

  DALI_CHECK_FAIL(propArray[0].Get<int>() != 1, "property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(propArray[1].Get<int>() != 2, "property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(propArray[2].Get<int>() != 3, "property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArrayOperatorAssignment()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property array should be empty by default ");

  propArray.Reserve(5);

  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);
  propArray.PushBack("world");
  propArray.PushBack("beautiful");

  Property::Array propArray2 = propArray;
  DALI_CHECK_FAIL(propArray2[1].Get<int>() != 2, "Assigned property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(propArray2[3].Get<std::string>() != "world", "Assigned property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
void PropertyArrayOperatorAssignmentP2()
{
  Property::Array propArray;
  DALI_CHECK_FAIL(!propArray.Empty(), "property array should be empty by default ");

  propArray.Reserve(5);

  propArray.PushBack(1);
  propArray.PushBack(2);
  propArray.PushBack(3);
  propArray.PushBack("world");
  propArray.PushBack("beautiful");

  Property::Array propArray2 = propArray;
  DALI_CHECK_FAIL(propArray2[1].Get<int>() != 2, "Assigned property array is failed to retrieved it's array value ");
  DALI_CHECK_FAIL(propArray2[3].Get<std::string>() != "world", "Assigned property array is failed to retrieved it's array value ");

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase             UtcDaliPropertyArrayConstructorP
 * @since_tizen          2.4
 * @description          To Check propertyarray Constructor is working properly or not.
 */
int UtcDaliPropertyArrayConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayConstructorInitializerListP
 * @since_tizen          5.5
 * @description          To Check propertyarray initializer_list Constructor is working properly or not.
 */
int UtcDaliPropertyArrayConstructorInitializerListP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_CONSTRUCTOR_INITIALIZER_LIST);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayCopyConstructorP
 * @since_tizen          2.4
 * @description          To Check propertyarray CopyConstructor is working properly or not.
 */
int UtcDaliPropertyArrayCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_COPY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArraySizeP
 * @since_tizen          2.4
 * @description          To Check propertyarray size is working properly or not
 */
int UtcDaliPropertyArraySizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_SIZE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayCountP
 * @since_tizen          2.4
 * @description          To Check propertyarray count is working properly or not
 */
int UtcDaliPropertyArrayCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_COUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayEmptyP
 * @since_tizen          2.4
 * @description          To Check propertyarray empty is working properly or not
 */
int UtcDaliPropertyArrayEmptyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_EMPTY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayClearP
 * @since_tizen          2.4
 * @description          To Check propertyarray clear is working properly or not
 */
int UtcDaliPropertyArrayClearP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_CLEAR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayReserveP
 * @since_tizen          2.4
 * @description          To Check propertyarray reserve api is working properly or not.
 */

int UtcDaliPropertyArrayReserveP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_RESERVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayResizeP
 * @since_tizen          2.4
 * @description          To Check propertyarray resize is working properly or not
 */
int UtcDaliPropertyArrayResizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_RESIZE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayAddP
 * @since_tizen          4.0
 * @description          To Check propertyarray add is working properly or not
 */
int UtcDaliPropertyArrayAddP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_ADD);
  application.MainLoop();
  return test_return_value;
} 

/**
 * @testcase             UtcDaliPropertyArrayCapacityP
 * @since_tizen          2.4
 * @description          To Check propertyarray capacity is working properly or not
 */
int UtcDaliPropertyArrayCapacityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_CAPACITY);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayPushBackP
 * @since_tizen          2.4
 * @description          To Check propertyarray pushback is working properly or not
 */
int UtcDaliPropertyArrayPushBackP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_PUSHBACK);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayGetElementAtP
 * @since_tizen          2.4
 * @description          To Check propertyarray element at a particular index is retrieved properly or not
 */
int UtcDaliPropertyArrayGetElementAtP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_GET_ELEMENT_AT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayOperatorAssignmentP
 * @since_tizen          2.4
 * @description          To Check propertyarray assignment operator is working properly or not.
 */
int UtcDaliPropertyArrayOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase             UtcDaliPropertyArrayOperatorAssignmentP2
 * @since_tizen          2.4
 * @description          To Check propertyarray assignment operator is working properly or not.
 */
int UtcDaliPropertyArrayOperatorAssignmentP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Property_Array_TestApp testApp( application, PROPERTY_ARRAY_ASSIGNMENT_OPERATOR_P2);
  application.MainLoop();
  return test_return_value;
}
