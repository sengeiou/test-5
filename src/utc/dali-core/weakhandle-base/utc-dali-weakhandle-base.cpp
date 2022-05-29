
#include <exception>
#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "WEAK_HANDLE_BASE_UTC"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_WeakHandleBase_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_WeakHandleBase_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_WeakHandleBase_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_WeakHandleBase_cleanup(void)
{

}

void WeakHandleBaseGetBaseHandle();
void WeakHandleBaseReset();
void WeakHandleBaseConstructor();
void WeakHandleBaseConstructorHandle();
void WeakHandleBaseCopyConstructor();
void WeakHandleBaseInequalOperatorPositive();
void WeakHandleBaseInequalOperatorNegative();
void WeakHandleBaseEqualOperatorPositive();
void WeakHandleBaseEqualOperatorNegative();
void WeakHandleBaseAssignOperator();

namespace
{
  enum TEST_CASES_LIST
  {
    WEAK_HANDLE_BASE_GET_BASE_HANDLE,
    WEAK_HANDLE_BASE_RESET,
    WEAK_HANDLE_BASE_CONSTRUCTOR,
    WEAK_HANDLE_BASE_CONSTRUCTOR_HANDLE,
    WEAK_HANDLE_BASE_COPY_CONSTRUCTOR,
    WEAK_HANDLE_BASE_INEQUAL_OPERATOR_P,
    WEAK_HANDLE_BASE_INEQUAL_OPERATOR_N,
    WEAK_HANDLE_BASE_EQUAL_OPERATOR_P,
    WEAK_HANDLE_BASE_EQUAL_OPERATOR_N,
    WEAK_HANDLE_BASE_ASSIGN_OPERATOR
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
        case WEAK_HANDLE_BASE_GET_BASE_HANDLE:
          WeakHandleBaseGetBaseHandle();
          break;

        case WEAK_HANDLE_BASE_RESET:
          WeakHandleBaseReset();
          break;

        case WEAK_HANDLE_BASE_CONSTRUCTOR:
          WeakHandleBaseConstructor();
          break;

        case WEAK_HANDLE_BASE_CONSTRUCTOR_HANDLE:
          WeakHandleBaseConstructorHandle();
          break;

        case WEAK_HANDLE_BASE_COPY_CONSTRUCTOR:
          WeakHandleBaseCopyConstructor();
          break;

        case WEAK_HANDLE_BASE_INEQUAL_OPERATOR_P:
          WeakHandleBaseInequalOperatorPositive();
          break;

        case WEAK_HANDLE_BASE_INEQUAL_OPERATOR_N:
          WeakHandleBaseInequalOperatorNegative();
          break;

        case WEAK_HANDLE_BASE_EQUAL_OPERATOR_P:
          WeakHandleBaseEqualOperatorPositive();
          break;

        case WEAK_HANDLE_BASE_EQUAL_OPERATOR_N:
          WeakHandleBaseEqualOperatorNegative();
          break;

        case WEAK_HANDLE_BASE_ASSIGN_OPERATOR:
          WeakHandleBaseAssignOperator();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

void WeakHandleBaseGetBaseHandle()
{
  Actor actor = Actor::New();
  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#1");

  WeakHandleBase theSameObject = WeakHandleBase(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != theSameObject.GetBaseHandle(), "Failed! Step#2");

  Actor differentActor = Actor::New();
  WeakHandleBase aDifferentWeakHandleBase(differentActor);
  DALI_CHECK_FAIL(object.GetBaseHandle() == aDifferentWeakHandleBase.GetBaseHandle(), "Failed! Step#3");

  DaliLog::PrintPass();
}
void WeakHandleBaseReset()
{
  Actor actor = Actor::New();
  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#1");

  object.Reset();

  DALI_CHECK_FAIL(object != WeakHandleBase(), "Failed! Step#2");
  DALI_CHECK_FAIL(object.GetBaseHandle() != Handle(), "Failed! Step#3");

  DaliLog::PrintPass();
}
void WeakHandleBaseConstructor()
{
  WeakHandleBase object;

  DALI_CHECK_FAIL(object.GetBaseHandle(), "Failed! Step#1");

  DaliLog::PrintPass();
}
void WeakHandleBaseConstructorHandle()
{
  Handle emptyHandle;
  WeakHandleBase emptyObject(emptyHandle);
  DALI_CHECK_FAIL(emptyObject.GetBaseHandle(), "Failed! Step#1");

  Actor actor = Actor::New();
  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#2");

  DaliLog::PrintPass();
}

void WeakHandleBaseCopyConstructor()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#1");

  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#2");
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#3");

  WeakHandleBase copy(object);
  DALI_CHECK_FAIL(copy.GetBaseHandle() != actor, "Failed! Step#4");
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#5");

  DaliLog::PrintPass();
}
void WeakHandleBaseInequalOperatorPositive()
{
  Actor actor = Actor::New();

  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#1");

  Actor differentActor = Actor::New();
  WeakHandleBase aDifferentWeakHandleBase(differentActor);

  DALI_CHECK_FAIL(object == aDifferentWeakHandleBase, "Failed! Step#2");

  DaliLog::PrintPass();
}
void WeakHandleBaseInequalOperatorNegative()
{
  Actor actor = Actor::New();

  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#1");

  WeakHandleBase theSameWeakHandleBase = object;

  DALI_CHECK_FAIL((object != theSameWeakHandleBase), "Failed! Step#2");

  DaliLog::PrintPass();
}

void WeakHandleBaseEqualOperatorPositive()
{
  WeakHandleBase object;
  WeakHandleBase theSameObject;
  DALI_CHECK_FAIL(object != theSameObject, "Failed! Step#1");

  Actor actor = Actor::New();

  object = WeakHandleBase(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#2");

  theSameObject = object;
  DALI_CHECK_FAIL(theSameObject.GetBaseHandle() != actor, "Failed! Step#3");
  DALI_CHECK_FAIL(object != theSameObject, "Failed! Step#4");

  DaliLog::PrintPass();
}
void WeakHandleBaseEqualOperatorNegative()
{
  Actor actor = Actor::New();

  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#1");

  Actor differentActor = Actor::New();
  WeakHandleBase aDifferentWeakHandleBase(differentActor);

  DALI_CHECK_FAIL((object == aDifferentWeakHandleBase), "Failed! Step#2");

  DaliLog::PrintPass();
}
void WeakHandleBaseAssignOperator()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#1");

  WeakHandleBase object(actor);
  DALI_CHECK_FAIL(object.GetBaseHandle() != actor, "Failed! Step#2");
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#3");

  WeakHandleBase copy = object;
  DALI_CHECK_FAIL(copy.GetBaseHandle() != actor, "Failed! Step#4");
  DALI_CHECK_FAIL(1 != actor.GetBaseObject().ReferenceCount(), "Failed! Step#5");

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase        UtcDaliWeakHandleBaseGetBaseHandleP
 * @since_tizen     4.0
 * @description     GetBaseHandle from WeakHandleBase.
 */
int UtcDaliWeakHandleBaseGetBaseHandleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_GET_BASE_HANDLE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseResetP
 * @since_tizen     4.0
 * @description     Reset WeakHandleBase.
 */
int UtcDaliWeakHandleBaseResetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_RESET);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseConstructorP
 * @since_tizen     4.0
 * @description     The constructor of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseConstructorHandleP
 * @since_tizen     4.0
 * @description     The constructor of WeakHandleBase with Handle.
 */
int UtcDaliWeakHandleBaseConstructorHandleP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_CONSTRUCTOR_HANDLE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseCopyConstructorP
 * @since_tizen     4.0
 * @description     The copy constructor of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_COPY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseInequalOperatorP
 * @since_tizen     4.0
 * @description     The '!=' operator overriding of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseInequalOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_INEQUAL_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseInequalOperatorN
 * @since_tizen     4.0
 * @description     The '!=' operator overriding of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseInequalOperatorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_INEQUAL_OPERATOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseEqualOperatorP
 * @since_tizen     4.0
 * @description     The '==' operator overriding of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseEqualOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_EQUAL_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseEqualOperatorN
 * @since_tizen     4.0
 * @description     The '==' operator overriding of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseEqualOperatorN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_EQUAL_OPERATOR_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliWeakHandleBaseAssignOperatorP
 * @since_tizen     4.0
 * @description     The '=' operator overriding of WeakHandleBase.
 */
int UtcDaliWeakHandleBaseAssignOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, WEAK_HANDLE_BASE_ASSIGN_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

