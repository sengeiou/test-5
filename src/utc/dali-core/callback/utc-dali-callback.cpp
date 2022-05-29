#include "utc-dali-callback-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_propertycondition_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Callback_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_Callback_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Callback_cleanup(void)
{

}

class TestCallbackBase : public CallbackBase
{
  public:
    TestCallbackBase()
      : CallbackBase()
    {
    }

    TestCallbackBase( void(*function)() )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
    { }
    template< typename R >
      TestCallbackBase( R(*function)() )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1 >
      TestCallbackBase( void(*function)(P1) )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1, typename R >
      TestCallbackBase( R(*function)(P1)  )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1, typename P2 >
      TestCallbackBase( void(*function)(P1,P2)  )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1, typename P2, typename R >
      TestCallbackBase( R(*function)(P1,P2) )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1, typename P2, typename P3 >
      TestCallbackBase( void(*function)(P1,P2,P3)  )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
    template< typename P1, typename P2, typename P3, typename R >
      TestCallbackBase( R(*function)(P1,P2,P3) )
      : CallbackBase( reinterpret_cast< CallbackBase::Function >( function ) )
      { }
};

class TestCallbackFunction : public ConnectionTracker
{
  public:
    TestCallbackFunction()
    {
    }

    static void VoidFuncVoid(void)
    {
      gTestCallback = CALLBACK_VOID_FUNC;
    }

    static int RetFuncVoid(void)
    {
      gTestCallback = CALLBACK_RETURN_FUNC;
      return gTestCallback;
    }

    static void VoidFuncParam1(int *pnNum)
    {
      *pnNum = CALLBACK_VOID_FUNC_PARAM_ONE;
    }

    static int RetFuncParam1(int nNum)
    {
      return nNum;
    }
    static void VoidFuncParam2(int *pnNum1, int *pnNum2)
    {
      *pnNum1 = CALLBACK_VOID_FUNC_PARAM_TWO;
      *pnNum2 = CALLBACK_VOID_FUNC_PARAM_TWO;
    }

    static int RetFuncParam2(int nNum1, int nNum2)
    {
      return nNum1;
    }
    static void VoidFuncParam3(int *pnNum1, int *pnNum2, int *pnNum3)
    {
      *pnNum1 = CALLBACK_VOID_FUNC_PARAM_THREE;
      *pnNum2 = CALLBACK_VOID_FUNC_PARAM_THREE;
      *pnNum3 = CALLBACK_VOID_FUNC_PARAM_THREE;
    }

    static int RetFuncParam3(int nNum1, int nNum2, int nNum3)
    {
      return nNum1;
    }
};

bool gCallbackFunctorDelegateCalled = false;

struct STCallbackFunctorDelegateCalled
{
  void operator()()
  {
    LOG_I("Callback for CallbackFunctorDelegate0 is called.");
    gCallbackFunctorDelegateCalled = true;
  }
};


void CallbackConstructor();
void CallbackReset();
void CallbackConstructExecute();
void CallbackConstructExecuteReturn();
void CallbackConstructExecuteParam1();
void CallbackConstructExecuteParam1Return();
void CallbackConstructExecuteParam2();
void CallbackConstructExecuteParam2Return();
void CallbackConstructExecuteParam3();
void CallbackConstructExecuteParam3Return();
void CallbackFunctorDelegateNew();
void CallbackFunctorDelegateExecute();

namespace
{
  enum TEST_CASES_LIST
  {
    CALLBACK_CONSTRUCTOR,
    CALLBACK_RESET,
    CALLBACK_CONSTRUCT_EXECUTE,
    CALLBACK_CONSTRUCT_EXECUTE_RETURN,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM1,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM1RETURN,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM2,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM2RETURN,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM3,
    CALLBACK_CONSTRUCT_EXECUTE_PARAM3RETURN,
    CALLBACK_FUNCTOR_DELEGATE_NEW,
    CALLBACK_FUNCTOR_DELEGATE_EXECUTE
  };

  struct TestApp : public ConnectionTracker
  {
    TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
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
        case CALLBACK_CONSTRUCTOR:
          CallbackConstructor();
          break;

        case CALLBACK_RESET:
          CallbackReset();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE:
          CallbackConstructExecute();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_RETURN:
          CallbackConstructExecuteReturn();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM1:
          CallbackConstructExecuteParam1();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM1RETURN:
          CallbackConstructExecuteParam1Return();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM2:
          CallbackConstructExecuteParam2();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM2RETURN:
          CallbackConstructExecuteParam2Return();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM3:
          CallbackConstructExecuteParam3();
          break;

        case CALLBACK_CONSTRUCT_EXECUTE_PARAM3RETURN:
          CallbackConstructExecuteParam3Return();
          break;

        case CALLBACK_FUNCTOR_DELEGATE_NEW:
          CallbackFunctorDelegateNew();
          break;

        case CALLBACK_FUNCTOR_DELEGATE_EXECUTE:
          CallbackFunctorDelegateExecute();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


void CallbackConstructor()
{
  CallbackBase *pCallback = new CallbackBase();
  DALI_CHECK_FAIL( !pCallback, "CallbackBase() api is failed to create constructor." );

  delete pCallback;

  DaliLog::PrintPass();
}

void CallbackReset()
{
  TestCallbackBase callback(TestCallbackFunction::VoidFuncVoid);
  callback.Reset();
  //DALI_CHECK_FAIL(gTestCallback == CALLBACK_VOID_FUNC, " CallbackBase( Function function ) and Execute( CallbackBase& callback ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecute()
{
  TestCallbackBase callback(TestCallbackFunction::VoidFuncVoid);
  callback.Execute(callback);

  DALI_CHECK_FAIL(gTestCallback != CALLBACK_VOID_FUNC, " CallbackBase( Function function ) and Execute( CallbackBase& callback ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteReturn()
{
  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::RetFuncVoid);

  int nRet = CallbackBase::ExecuteReturn<int>( *pCallback );
  DALI_CHECK_FAIL( nRet != CALLBACK_RETURN_FUNC , " ExecuteReturn( CallbackBase& callback ) api is failed to execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteParam1()
{
  int nNum = 0;
  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::VoidFuncParam1);

  CallbackBase::Execute<int*>(*pCallback, &nNum);
  DALI_CHECK_FAIL(nNum != CALLBACK_VOID_FUNC_PARAM_ONE, " Execute( CallbackBase& callback, P1 param1 ) api is failed to execute the call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteParam1Return()
{
  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::RetFuncParam1);

  int nRet = CallbackBase::ExecuteReturn<int, int>( *pCallback, CALLBACK_VOID_FUNC_PARAM_ONE );
  DALI_CHECK_FAIL( nRet != CALLBACK_VOID_FUNC_PARAM_ONE , " ExecuteReturn( CallbackBase& callback ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteParam2()
{

  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::VoidFuncParam2);

  int nNum1, nNum2;

  CallbackBase::Execute<int*, int*>( *pCallback, &nNum1, &nNum2 );

  DALI_CHECK_FAIL( nNum1 != CALLBACK_VOID_FUNC_PARAM_TWO || nNum2 != CALLBACK_VOID_FUNC_PARAM_TWO, "Execute( CallbackBase& callback, P1 param1, P2 param2 ). api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteParam2Return()
{

  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::RetFuncParam2);

  int nRet = CallbackBase::ExecuteReturn<int, int, int>( *pCallback, CALLBACK_VOID_FUNC_PARAM_TWO, CALLBACK_VOID_FUNC_PARAM_TWO );

  DALI_CHECK_FAIL( nRet != CALLBACK_VOID_FUNC_PARAM_TWO, " ExecuteReturn( CallbackBase& callback ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackConstructExecuteParam3()
{
  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::VoidFuncParam3);

  int nNum1, nNum2, nNum3;

  CallbackBase::Execute<int*, int*, int*>( *pCallback, &nNum1, &nNum2, &nNum3 );

  DALI_CHECK_FAIL( nNum1 != CALLBACK_VOID_FUNC_PARAM_THREE || nNum2 != CALLBACK_VOID_FUNC_PARAM_THREE || nNum3 != CALLBACK_VOID_FUNC_PARAM_THREE, " Execute( CallbackBase& callback, P1 param1, P2 param2, P3 param3 ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}


void CallbackConstructExecuteParam3Return()
{

  CallbackBase *pCallback = MakeCallback(TestCallbackFunction::RetFuncParam3);

  int nRet = CallbackBase::ExecuteReturn<int, int, int, int>( *pCallback, CALLBACK_VOID_FUNC_PARAM_THREE, CALLBACK_VOID_FUNC_PARAM_THREE, CALLBACK_VOID_FUNC_PARAM_THREE);

  DALI_CHECK_FAIL( nRet != CALLBACK_VOID_FUNC_PARAM_THREE, "ExecuteReturn( CallbackBase& callback ) api is failed to create constructor and execute that call back function.");

  DaliLog::PrintPass();
}

void CallbackFunctorDelegateNew()
{
  STCallbackFunctorDelegateCalled callbackFunctor;
  CallbackBase *pCallback = new CallbackFunctorDelegate0( FunctorDelegate::New( callbackFunctor ) );

  DALI_CHECK_INSTANCE( pCallback, "CallbackBase creation is failed using CallbackFunctorDelegate0().");

  gCallbackFunctorDelegateCalled = false;
  CallbackBase::Execute( *pCallback );

  DALI_CHECK_FAIL( !gCallbackFunctorDelegateCalled, "Callback created from CallbackFunctorDelegate0 is failed to execute the callback function." );

  DALI_SAFE_FREE( pCallback );
  DaliLog::PrintPass();
}

void CallbackFunctorDelegateExecute()
{
  STCallbackFunctorDelegateCalled callbackFunctor;

  FunctorDelegate *pCallback = FunctorDelegate::New( callbackFunctor );
  DALI_CHECK_INSTANCE( pCallback, "CallbackBase creation is failed using CallbackFunctorDelegate0().");

  gCallbackFunctorDelegateCalled = false;
  (*pCallback).FunctorDelegate::Execute();

  DALI_CHECK_FAIL( !gCallbackFunctorDelegateCalled, "Callback created from CallbackFunctorDelegate0 is failed to execute the callback function." );

  DALI_SAFE_FREE( pCallback );
  DaliLog::PrintPass();

}


/**
 * End of TC Logic Implementation Area.
 **/



/**
 * @testcase                UtcDaliCallbackConstructorP
 * @since_tizen             2.4
 * @description             Create a handle of CallbackBase and execute the call bace function
 */
int UtcDaliCallbackConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackResetP
 * @since_tizen             2.4
 * @description             Create a handle of CallbackBase and execute the call bace function
 */
int UtcDaliCallbackResetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_RESET);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteP
 * @since_tizen             2.4
 * @description             Create a handle of CallbackBase and execute the call bace function
 */
int UtcDaliCallbackConstructExecuteP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteReturnP
 * @since_tizen             2.4
 * @description             Execute the call back function with return value.
 */
int UtcDaliCallbackConstructExecuteReturnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_RETURN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteParam1P
 * @since_tizen             2.4
 * @description             Execute the call back function with 1 parameter.
 */
int UtcDaliCallbackConstructExecuteParam1P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM1);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteParam1ReturnP
 * @since_tizen             2.4
 * @description             Execute call back function with return type and 1 parameter.
 */
int UtcDaliCallbackConstructExecuteParam1ReturnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM1RETURN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteParam2P
 * @since_tizen             2.4
 * @description             Execute the call back function with return and parameter type.
 */
int UtcDaliCallbackConstructExecuteParam2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteParam2ReturnP
 * @since_tizen             2.4
 * @description             Execute callback function with parameter and return type
 */

int UtcDaliCallbackConstructExecuteParam2ReturnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM2RETURN);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase                UtcDaliCallbackConstructExecuteParam3P
 * @since_tizen             2.4
 * @description             Create a handle of CallbackBase and execute the call bace function
 */
int UtcDaliCallbackConstructExecuteParam3P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM3);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackConstructExecuteParam3ReturnP
 * @since_tizen             2.4
 * @description             Create a handle of CallbackBase and execute the call bace function
 */
int UtcDaliCallbackConstructExecuteParam3ReturnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_CONSTRUCT_EXECUTE_PARAM3RETURN);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackFunctorDelegateNewP
 * @since_tizen             2.4
 * @description             Construct Function object callback for connecting void() methods with no parameter
 */
int UtcDaliCallbackFunctorDelegateNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_FUNCTOR_DELEGATE_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase                UtcDaliCallbackFunctorDelegateExecuteP
 * @since_tizen             2.4
 * @description             Construct Function object callback for connecting void() methods with no parameter
 */
int UtcDaliCallbackFunctorDelegateExecuteP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, CALLBACK_FUNCTOR_DELEGATE_EXECUTE);
  application.MainLoop();
  return test_return_value;
}
