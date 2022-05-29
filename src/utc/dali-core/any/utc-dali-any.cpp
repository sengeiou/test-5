#include "utc-dali-any-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Any
/**
 * @function            utc_Dali_Any_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Any_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Any_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Any_cleanup(void)
{

}

void AnyConstructorP();
void AnyConstructorP2();
void AnyConstructorP3();
void AnyGetTypeP();
void AnyGetP();
void AnyGetPointerP();
void AnyGetPointerP2();
void AnyEmptyP();
void AnyOperatorAssignmentP();
void AnyOperatorAssignmentP2();
void AnyCopyConstructorP();
void AnyAssertAlwaysP();
void AnyAnyCastP();
void AnyCastP();

namespace
{
  enum TEST_CASES_LIST_ANY
  {
    ANY_CONSTRUCTOR_P,
    ANY_CONSTRUCTOR_P2,
    ANY_CONSTRUCTOR_P3,
    ANY_GET_TYPE_P,
    ANY_GET_P,
    ANY_GET_POINTER_P,
    ANY_GET_POINTER_CONST_P,
    ANY_EMPTY_P,
    ANY_OPERATOR_ASSIGNMENT_P,
    ANY_OPERATOR_ASSIGNMENT_P2,
    ANY_COPY_CONSTRUCTOR_P,
    ANY_ASSERT_ALWAYS_P,
    ANY_ANY_CAST_P,
    ANY_CAST_P
  };

  struct Any_TestApp : public ConnectionTracker
  {
    Any_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Any_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Any_TestApp::Tick );
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
        case ANY_CONSTRUCTOR_P:
          AnyConstructorP();
          break;

        case ANY_CONSTRUCTOR_P2:
          AnyConstructorP2();
          break;

        case ANY_CONSTRUCTOR_P3:
          AnyConstructorP3();
          break;

        case ANY_GET_TYPE_P:
          AnyGetTypeP();
          break;

        case ANY_GET_P:
          AnyGetP();
          break;

        case ANY_GET_POINTER_P:
          AnyGetPointerP();
          break;

        case ANY_GET_POINTER_CONST_P:
          AnyGetPointerP2();
          break;

        case ANY_EMPTY_P:
          AnyEmptyP();
          break;

        case ANY_OPERATOR_ASSIGNMENT_P:
          AnyOperatorAssignmentP();
          break;

        case ANY_OPERATOR_ASSIGNMENT_P2:
          AnyOperatorAssignmentP2();
          break;

        case ANY_COPY_CONSTRUCTOR_P:
          AnyCopyConstructorP();
          break;

        case ANY_ASSERT_ALWAYS_P:
          AnyAssertAlwaysP();
          break;

        case ANY_ANY_CAST_P:
          AnyAnyCastP();
          break;

        case ANY_CAST_P:
          AnyCastP();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

void AnyCastP()
{
  Any anyInt;
  anyInt = Any(2);

  int nAny = AnyCast<int>(anyInt);
  DALI_CHECK_FAIL(nAny != 2 , "AnyCast(Any &any) failed.");

  const int nValue = 2;
  const int nConstAny = AnyCast<const int>(anyInt);
  DALI_CHECK_FAIL(nValue != nConstAny , "AnyCast(const Any &any) failed.");

  float fVale = 5.09f;
  Any anyFloat(fVale);
  float *fFloat = AnyCast<float>(&anyFloat);
  DALI_CHECK_FAIL(fVale != *fFloat, "AnyCast(Any *any) failed.");

  const float fConstVale = 1001.8f;
  const Any anyConst(fConstVale);
  const float *fConstFloat = AnyCast<const float>(&anyConst);
  DALI_CHECK_FAIL(fConstVale != *fConstFloat, "AnyCast(const Any *any) failed.");

  class MyClass
  {
    public:
      MyClass( float fValue, int iValue )
        : mAny( MyStruct( fValue, iValue ) )
      {
      }

      const MyStruct& Get() const
      {
        return AnyCastReference<MyStruct>( mAny );
      }

      MyStruct* GetPointer()
      {
        return AnyCast<MyStruct>( &mAny );
      }

      const MyStruct* GetPointer() const
      {
        return AnyCast<MyStruct>( &mAny );
      }

    private:
      Dali::Any mAny;
  };

  MyClass myClass(5.34f, 19);

  MyStruct myStruct1 = myClass.Get();
  const MyStruct& myStruct2 = myClass.Get();

  const float fEpsilon = 0.1f;
  DALI_CHECK_FAIL(!Equals(myStruct1.mFloatValue, 5.34f, fEpsilon), "AnyCastReference(Any &any) failed.");
  DALI_CHECK_FAIL(!Equals(myStruct2.mFloatValue, 5.34f, fEpsilon), "AnyCastReference(const Any &any) failed. ");

  DaliLog::PrintPass();
}

void AnyConstructorP()
{
  Any anyv;

  DALI_CHECK_FAIL( anyv.GetType().name() != typeid( void ).name() , " Any::Any() is failed to get expected float type");

  DaliLog::PrintPass();
}

void AnyConstructorP2()
{
  int nGetAny = 0, nSetVal = 63;
  float fGetAny = 0.0f, fSetVal = 55.5f;
  unsigned int uGetAny = 0u, uSetVal = 45u;

  Any anyFloat( fSetVal );

  const char* pchTypeFloat = anyFloat.GetType().name();
  DALI_CHECK_FAIL( pchTypeFloat != typeid( float ).name() , " Any::GetType is failed to get expected float type");

  anyFloat.Get( fGetAny );
  DALI_CHECK_FAIL( fGetAny != fSetVal , " Any::Get failed to get the float value which was given in Any Constructor");

  Any anyInt( nSetVal );
  const char* pchTypeInt = anyInt.GetType().name();
  DALI_CHECK_FAIL( pchTypeInt != typeid( int ).name() , " Any::GetType is failed to get expected integer type");

  anyInt.Get( nGetAny );
  DALI_CHECK_FAIL( nGetAny != nSetVal , " Any::Get failed to get the integer value which was given in Any Constructor");

  Any anyUnsigned( uSetVal );
  const char* pchTypeUnsigned = anyUnsigned.GetType().name();
  DALI_CHECK_FAIL( pchTypeUnsigned != typeid( unsigned int ).name() , " Any::GetType is failed to get expected unsigned integer type");

  anyUnsigned.Get( uGetAny );
  DALI_CHECK_FAIL( uGetAny != uSetVal , " Any::Get(&value) is failed to get the unsigned integer value which was given in Any Constructor");

  DaliLog::PrintPass();
}

void AnyConstructorP3()
{
  string strSet = string( "I am working" );

  Any anyString( strSet );
  const char* pchTypeString = anyString.GetType().name();
  DALI_CHECK_FAIL( pchTypeString != typeid( string ).name() , " Any::Any(const char*) is failed ");

  DaliLog::PrintPass();
}


void AnyGetTypeP()
{
  int nGetAny = 0, nSetVal = 63;
  float fGetAny = 0.0f, fSetVal = 55.5f;
  unsigned int uGetAny = 0u, uSetVal = 45u;
  string strGetAny, strSet = string( "I am working" );

  Any anyFloat( fSetVal );

  const char* pchTypeFloat = anyFloat.GetType().name();
  DALI_CHECK_FAIL( pchTypeFloat != typeid( float ).name() , " Any::GetType is failed to get expected float type");

  anyFloat.Get( fGetAny );
  DALI_CHECK_FAIL( fGetAny != fSetVal , " Any::Get failed to get the float value which was given in Any Constructor");

  Any anyInt( nSetVal );
  const char* pchTypeInt = anyInt.GetType().name();
  DALI_CHECK_FAIL( pchTypeInt != typeid( int ).name() , " Any::GetType is failed to get expected integer type");

  anyInt.Get( nGetAny );
  DALI_CHECK_FAIL( nGetAny != nSetVal , " Any::Get failed to get the integer value which was given in Any Constructor");

  Any anyUnsigned( uSetVal );
  const char* pchTypeUnsigned = anyUnsigned.GetType().name();
  DALI_CHECK_FAIL( pchTypeUnsigned != typeid( unsigned int ).name() , " Any::GetType is failed to get expected unsigned integer type");

  anyUnsigned.Get( uGetAny );
  DALI_CHECK_FAIL( uGetAny != uSetVal , " Any::Get(&value) is failed to get the unsigned integer value which was given in Any Constructor");

  Any anyString( strSet );
  const char* pchTypeString = anyString.GetType().name();
  if( pchTypeString != typeid( string ).name() )
  {
    LOG_E(" Any::GetType is failed to get expected string type");
    strGetAny.clear();
    test_return_value=TC_FAIL;
    return;
  }

  anyString.Get( strGetAny );
  DALI_CHECK_FAIL( strGetAny != strSet , " Any::Get failed to get the string value which was given in Any Constructor");

  strGetAny.clear();

  DaliLog::PrintPass();
}

void AnyGetP()
{
  int nGetAny = 0, nSetVal = 63;
  float fGetAny = 0.0f, fSetVal = 55.5f;
  unsigned int uGetAny = 0u, uSetVal = 45u;
  string strGetAny, strSet = string( "I am working" );

  Any anyFloat( fSetVal );

  const char* pchTypeFloat = anyFloat.GetType().name();
  DALI_CHECK_FAIL( pchTypeFloat != typeid( float ).name() , " Any::GetType is failed to get expected float type");

  anyFloat.Get( fGetAny );
  DALI_CHECK_FAIL( fGetAny != fSetVal , " Any::Get failed to get the float value which was given in Any Constructor");

  Any anyInt( nSetVal );
  const char* pchTypeInt = anyInt.GetType().name();
  DALI_CHECK_FAIL( pchTypeInt != typeid( int ).name() , " Any::GetType is failed to get expected integer type");

  anyInt.Get( nGetAny );
  DALI_CHECK_FAIL( nGetAny != nSetVal , " Any::Get failed to get the integer value which was given in Any Constructor");

  Any anyUnsigned( uSetVal );
  const char* pchTypeUnsigned = anyUnsigned.GetType().name();
  DALI_CHECK_FAIL( pchTypeUnsigned != typeid( unsigned int ).name() , " Any::GetType is failed to get expected unsigned integer type");

  anyUnsigned.Get( uGetAny );
  DALI_CHECK_FAIL( uGetAny != uSetVal , " Any::Get(&value) is failed to get the unsigned integer value which was given in Any Constructor");

  Any anyString( strSet );
  const char* pchTypeString = anyString.GetType().name();
  if( pchTypeString != typeid( string ).name() )
  {
    LOG_E(" Any::GetType is failed to get expected string type");
    strGetAny.clear();
    test_return_value=TC_FAIL;
    return;
  }

  anyString.Get( strGetAny );
  DALI_CHECK_FAIL( strGetAny != strSet , " Any::Get failed to get the string value which was given in Any Constructor");

  strGetAny.clear();

  DaliLog::PrintPass();
}

void AnyGetPointerP()
{
  class MyClass
  {
    public:
      MyClass( float fValue, int iValue )
        : mAny( MyStruct( fValue, iValue ) )
      {
      }

      const MyStruct& Get() const
      {
        return AnyCastReference<MyStruct>( mAny );
      }

      MyStruct* GetPointer()
      {
        return AnyCast<MyStruct>( &mAny );
      }

      const MyStruct* GetPointer() const
      {
        return AnyCast<MyStruct>( &mAny );
      }

    private:
      Dali::Any mAny;
  };

  MyClass myClass( 3.25f, 3 );

  MyStruct* myStruct = myClass.GetPointer();

  DALI_CHECK_FAIL( !myStruct, " GetPointer() is failed");
  DaliLog::PrintPass();
}

void AnyGetPointerP2()
{

  class MyClass
  {
    public:
      MyClass( float fValue, int iValue )
        : mAny( MyStruct( fValue, iValue ) )
      {
      }

      const MyStruct& Get() const
      {
        return AnyCastReference<MyStruct>( mAny );
      }

      MyStruct* GetPointer()
      {
        return AnyCast<MyStruct>( &mAny );
      }

      const MyStruct* GetPointer() const
      {
        return AnyCast<MyStruct>( &mAny );
      }

    private:
      Dali::Any mAny;
  };

  MyClass myClass( 3.25f, 3 );

  const MyStruct* myStruct = myClass.GetPointer();

  DALI_CHECK_FAIL( !myStruct, " GetPointer() const is failed");
  DaliLog::PrintPass();

}

void AnyEmptyP()
{
  int nIter = 0, nSet = 64, nGet;
  char chSet = 'a', chGet;
  bool bIsEmpty = false;

  Any anyValue;
  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return true for uninitialized Any");

  chSet = (char)(chSet + nIter);
  Any anyValuetoAssign( chSet );

  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != typeid( char ) , " The type of value to be assigned is matched to the type of the given char value");

  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return false after assigning a value");

  anyValue = anyValuetoAssign;
  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != anyValue.GetType() , " The type of anyValue is not matched to the expected type after assignment ");

  anyValue.Get( chGet );
  DALI_CHECK_FAIL( chGet != chSet , " The Any::operator=(&Any) is failed to assign expected value ");

  Any anyGet = nSet;

  anyGet.Get( nGet );
  DALI_CHECK_FAIL( anyGet.GetType() != typeid( int ) , " The type of anyGet is not matched to the expected type of set value after assignment");
  DALI_CHECK_FAIL( nGet != nSet , " The Any::operator=(&value) is failed to assign expected value ");

  DaliLog::PrintPass();
}

void AnyOperatorAssignmentP()
{
  int nIter = 0, nSet = 64, nGet;
  char chGet, chSet = 'a';
  bool bIsEmpty = false;

  Any anyValue;
  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return true for uninitialized Any");

  chSet = (char)(chSet + nIter);
  Any anyValuetoAssign( chSet );

  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != typeid( char ) , " The type of value to be assigned is matched to the type of the given char value");

  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return false after assigning a value");

  anyValue = anyValuetoAssign;
  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != anyValue.GetType() , " The type of anyValue is not matched to the expected type after assignment ");

  Any anyGet = nSet;

  anyGet.Get( nGet );
  DALI_CHECK_FAIL( anyGet.GetType() != typeid( int ) , " The type of anyGet is not matched to the expected type of set value after assignment");
  DALI_CHECK_FAIL( nGet != nSet , " The Any::operator=(&value) is failed to assign expected value ");

  DaliLog::PrintPass();
}

void AnyOperatorAssignmentP2()
{
  int nIter = 0;
  char chSet = 'a', chGet;
  bool bIsEmpty = false;

  Any anyValue;
  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return true for uninitialized Any");

  chSet = (char)(chSet + nIter);
  Any anyValuetoAssign( chSet );

  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != typeid( char ) , " The type of value to be assigned is matched to the type of the given char value");

  bIsEmpty = anyValue.Empty();
  DALI_CHECK_FAIL( !bIsEmpty , " Any::Empty is failed to return false after assigning a value");

  anyValue = anyValuetoAssign;
  DALI_CHECK_FAIL( anyValuetoAssign.GetType() != anyValue.GetType() , " The type of anyValue is not matched to the expected type after assignment ");

  anyValue.Get( chGet );
  DALI_CHECK_FAIL( chGet != chSet , " The Any::operator=(&Any) is failed to assign expected value ");

  DaliLog::PrintPass();
}

void AnyCopyConstructorP()
{
  int nSetVal = 77, nGetAny = 0, nGetAnyCopy = 0;
  bool bIsEmpty = false;
  Any any;

  bIsEmpty = any.Empty();

  DALI_CHECK_FAIL( !bIsEmpty , " No value should be assigned to an uninitialized any");

  any = nSetVal;
  bIsEmpty = any.Empty();

  DALI_CHECK_FAIL( bIsEmpty , " Any type is empty");

  Any anyCopy( any );

  bIsEmpty = true;
  bIsEmpty = anyCopy.Empty();

  DALI_CHECK_FAIL( bIsEmpty , " Any copy constructor is failed to copy any type");
  DALI_CHECK_FAIL( anyCopy.GetType() != any.GetType() , " The type of anyValue is not matched to the type of the assigned value");

  any.Get( nGetAny );
  anyCopy.Get( nGetAnyCopy );

  DALI_CHECK_FAIL( nGetAnyCopy !=  nGetAny , " The value of the anyCopy does not match to the value of any type");

  DaliLog::PrintPass();
}

void AnyAnyCastP()
{
  Any any;
  DALI_CHECK_FAIL( typeid( void ) != any.GetType() , " Any::GetType is failed to get correct type.");
  any = 50.0f;
  DALI_CHECK_FAIL( typeid( float ) != any.GetType() , " Any::GetType is failed to get correct type.");
  any = 5;
  DALI_CHECK_FAIL( typeid( int ) != any.GetType() , " Any::GetType is failed to get correct type.");

  Any intvariable= 1;
  AnyCast< int >( intvariable );
  DALI_CHECK_FAIL( typeid( int ) != intvariable.GetType()  , " Any::Anycast is failed");

  DaliLog::PrintPass();
}

void AnyAssertAlwaysP()
{
  bool bAssert = false;
  unsigned int uAny = 22u; //required to create an any object only
  Any any( uAny );

  try
  {
    any.AssertAlways("New Message for any error");
  }
  catch( Dali::DaliException& e )
  {
    bAssert = true;
  }

  DALI_CHECK_FAIL( !bAssert , " Any::Assert is failed to give message");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliAnyConstructorP
 * @since_tizen         2.4
 * @description         checks if default constructor works or not.
 */

int UtcDaliAnyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyConstructorP2
 * @since_tizen         2.4
 * @description         checks if constructor works or not.
 */

int UtcDaliAnyConstructorP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyConstructorP3
 * @since_tizen         2.4
 * @description         checks if constructor works or not.
 */

int UtcDaliAnyConstructorP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_CONSTRUCTOR_P3);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyGetTypeP
 * @since_tizen         2.4
 * @description         checks if GetType api works or not.
 */

int UtcDaliAnyGetTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_GET_TYPE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyGetP
 * @since_tizen         2.4
 * @description         checks if Get api works or not.
 */

int UtcDaliAnyGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_GET_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyGetPointerP
 * @since_tizen         2.4
 * @description         checks if GetPointer api works or not.
 */

int UtcDaliAnyGetPointerP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_GET_POINTER_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyGetPointerP2
 * @since_tizen         2.4
 * @description         checks if GetPointer api works or not.
 */

int UtcDaliAnyGetPointerP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_GET_POINTER_CONST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyEmptyP
 * @since_tizen         2.4
 * @description         checks if Empty api works or not.
 */

int UtcDaliAnyEmptyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_EMPTY_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyOperatorAssignmentP
 * @since_tizen         2.4
 * @description         checks if operator=() works or not.
 */

int UtcDaliAnyOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyOperatorAssignmentP2
 * @since_tizen         2.4
 * @description         checks if operator=() works or not.
 */

int UtcDaliAnyOperatorAssignmentP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_OPERATOR_ASSIGNMENT_P2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyCopyConstructorP
 * @since_tizen         2.4
 * @description         checks if copy constructor works or not.
 */

int UtcDaliAnyCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyAssertAlwaysP
 * @since_tizen         2.4
 * @description         checks if AssertAlways api works or not.
 */

int UtcDaliAnyAssertAlwaysP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_ASSERT_ALWAYS_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyAnyCastP
 * @since_tizen         2.4
 * @description         checks if AnyCast api works or not.
 */

int UtcDaliAnyAnyCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_ANY_CAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliAnyCastP
 * @since_tizen         2.4
 * @description         checks if AnyCast api works or not.
 */

int UtcDaliAnyCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Any_TestApp testApp(application, ANY_CAST_P);
  application.MainLoop();
  return test_return_value;
}
