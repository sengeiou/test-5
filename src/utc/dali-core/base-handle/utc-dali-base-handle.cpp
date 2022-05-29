#include "utc-dali-base-handle-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


/**
 * @function            utc_Dali_BaseHandle_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_BaseHandle_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_BaseHandle_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_BaseHandle_cleanup(void)
{

}


static bool gTouchCallBackCalled = false;

//Funtion for callback
struct TestCallback
{
  void operator()()
  {
    gTouchCallBackCalled = true;
  }
};

// Functor to test whether an animation finish signal is emitted
struct AnimationFinishCheck
{
  AnimationFinishCheck(bool& signalReceived) : mSignalReceived(signalReceived)
  {
  }

  void operator()(Animation& animation)
  {
    mSignalReceived = true;
  }

  void Reset()
  {
    mSignalReceived = false;
  }

  void CheckSignalReceived()
  {
    if (!mSignalReceived)
    {
      LOG_E(" Expected Finish signal was not received  ");
    }
    else
    {
      LOG_E(" Expected Finish signal was  received  ");
    }
  }

  bool& mSignalReceived; // owned by individual tests
};


void BaseHandleConstructor();
void BaseHandleCopyConstructorBaseObject();
void BaseHandleCopyConstructor();
void BaseHandleOperatorAssignment();
void BaseHandleDoAction();
void BaseHandleGetTypeNameP();
void BaseHandleGetTypeNameN();
void BaseHandleGetTypeInfoP();
void BaseHandleGetTypeInfoN();
void BaseHandleGetBaseObject();
void BaseHandleReset();
void BaseHandleBooleanType();
void BaseHandleEqualOperator();
void BaseHandleInequalOperator();
void BaseHandleGetObjectPtr();



namespace
{
  enum TEST_CASES_LIST
  {
    BASE_HANDLE_CONSTRUCTOR,
    BASE_HANDLE_COPY_CONSTRUCTOR,
    BASE_HANDLE_COPY_CONSTRUCTOR_P2,
    BASE_HANDLE_OPERATOR_ASSIGNMENT,
    BASE_HANDLE_DO_ACTION,
    BASE_HANDLE_GET_TYPE_NAME_P,
    BASE_HANDLE_GET_TYPE_NAME_N,
    BASE_HANDLE_GET_TYPE_INFO_P,
    BASE_HANDLE_GET_TYPE_INFO_N,
    BASE_HANDLE_GET_BASE_OBJECT,
    BASE_HANDLE_RESET,
    BASE_HANDLE_BOOLEAN_TYPE,
    BASE_HANDLE_EQUAL_OPERATOR,
    BASE_HANDLE_INEQUAL_OPERATOR,
    BASE_HANDLE_GET_BASE_OBJECT_PTR

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
        case BASE_HANDLE_CONSTRUCTOR:
          BaseHandleConstructor();
          break;

        case BASE_HANDLE_COPY_CONSTRUCTOR:
          BaseHandleCopyConstructorBaseObject();
          break;

        case BASE_HANDLE_COPY_CONSTRUCTOR_P2:
          BaseHandleCopyConstructor();
          break;

        case BASE_HANDLE_OPERATOR_ASSIGNMENT:
          BaseHandleOperatorAssignment();
          break;

        case BASE_HANDLE_DO_ACTION:
          BaseHandleDoAction();
          break;

        case BASE_HANDLE_GET_TYPE_NAME_P:
          BaseHandleGetTypeNameP();
          break;

        case BASE_HANDLE_GET_TYPE_NAME_N:
          BaseHandleGetTypeNameN();
          break;

        case BASE_HANDLE_GET_TYPE_INFO_P:
          BaseHandleGetTypeInfoP();
          break;

        case BASE_HANDLE_GET_TYPE_INFO_N:
          BaseHandleGetTypeInfoN();
          break;

        case BASE_HANDLE_GET_BASE_OBJECT:
          BaseHandleGetBaseObject();
          break;

        case BASE_HANDLE_RESET:
          BaseHandleReset();
          break;

        case BASE_HANDLE_BOOLEAN_TYPE:
          BaseHandleBooleanType();
          break;

        case BASE_HANDLE_EQUAL_OPERATOR:
          BaseHandleEqualOperator();
          break;

        case BASE_HANDLE_INEQUAL_OPERATOR:
          BaseHandleInequalOperator();
          break;

        case BASE_HANDLE_GET_BASE_OBJECT_PTR:
          BaseHandleGetObjectPtr();
          break;

      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace

void BaseHandleConstructor()
{
  BaseHandle*  Basehandleobject = new BaseHandle();

  DALI_CHECK_FAIL(Basehandleobject == NULL, "Basehandle() is failed to create Basehandle object." );
  delete Basehandleobject;

  DaliLog::PrintPass();
}
void BaseHandleCopyConstructorBaseObject()
{
  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;

  int nCount = 0, nFlag = 0;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created " );

  ++nFlag;
  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  ++nFlag;
  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  ++nFlag;
  BaseHandle BasehandleCopyobject(Basehandleobject);
  DALI_CHECK_FAIL(!BasehandleCopyobject, " BasehandleCopyobject is not created " );

  nCount = BasehandleCopyobject.GetBaseObject().ReferenceCount();
  strGetname = BasehandleCopyobject.GetBaseObject().GetTypeName();
  DALI_CHECK_FAIL(nCount != ++nFlag && strGetname != strname, " Getting Count failed");

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void BaseHandleCopyConstructor()
{
  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;

  int nCount = 0, nFlag = 0;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created " );

  ++nFlag;
  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  ++nFlag;
  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  ++nFlag;
  BaseHandle BasehandleCopyobject(Basehandleobject);
  DALI_CHECK_FAIL(!BasehandleCopyobject, " BasehandleCopyobject is not created " );

  nCount = BasehandleCopyobject.GetBaseObject().ReferenceCount();
  strGetname = BasehandleCopyobject.GetBaseObject().GetTypeName();
  DALI_CHECK_FAIL(nCount != ++nFlag && strGetname != strname, " Getting Count failed");

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void BaseHandleOperatorAssignment()
{
  Actor actor;
  Stage stage;
  string strGetname;
  float      fSetValuex = 3.13f, fSetValuey = 2.12f, fSetValuez = 1.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  DALI_CHECK_FAIL(!basehandleInit(stage,actor,&vec3SetPosition), " Initialization failed " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  BaseHandle BasehandleCopyobject(Basehandleobject);
  BaseHandle BasehandleDifferentObject;

  BasehandleDifferentObject = BasehandleCopyobject;

  Actor actor2 = Actor::DownCast(BasehandleDifferentObject);
  Actor actor3 = Actor::DownCast(BasehandleCopyobject);

  DALI_CHECK_FAIL(BasehandleCopyobject.GetTypeName() != BasehandleDifferentObject.GetTypeName() || !(BasehandleDifferentObject == BasehandleCopyobject) || actor2.GetCurrentPosition()!=actor3.GetCurrentPosition() , " BasehandleCopyobject and Basehandleobject not  are equal " );

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void BaseHandleDoAction()
{

  Actor actor;
  Stage stage;

  string strname = "Actor", strGetname;
  bool bTypeInfoStatus = false;

  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  stage = Stage::GetCurrent();

  DALI_CHECK_FAIL(!stage , " stage is not created " );

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);
  DALI_CHECK_FAIL(!actor.OnStage(), " actor is not in OnStage " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );


  // Check that an invalid command is not performed
  Property::Map attributes;
  bTypeInfoStatus = Basehandleobject.DoAction("invalidCommand", attributes);

  DALI_CHECK_FAIL(bTypeInfoStatus, "Action should not fail");

  // Check that the actor is visible
  actor.SetVisible(true);
  DALI_CHECK_FAIL(!actor.IsVisible(), "Actor should not be invisible" );

  bTypeInfoStatus = Basehandleobject.DoAction("hide", attributes);

  // Check the actor performed an action to hide itself
  DALI_CHECK_FAIL(!bTypeInfoStatus, "The action hide did not perform");

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void BaseHandleGetTypeNameP()
{
  Actor actor;
  string strname = "Actor", strGetname;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  BaseHandle basehandle = actor;
  DALI_CHECK_FAIL( basehandle != actor, "BaseHandle is not created with actor.");

  strGetname = basehandle.GetBaseObject().GetTypeName();

  DALI_CHECK_FAIL(strGetname != strname, " Getting Base Object is not Actor");
  DaliLog::PrintPass();
}
void BaseHandleGetTypeNameN()
{
  BaseHandle basehandle;

  try
  {
    string strname = basehandle.GetTypeName();
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "basehandle is empty" );
  }

  DaliLog::PrintPass();
}
void BaseHandleGetTypeInfoP()
{
  BaseHandle basehandle;
  bool bTypeInfoStatus = false;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor is not created.");

  basehandle = actor;
  DALI_CHECK_FAIL( basehandle != actor, "BaseHandle is not created with actor.");

  TypeRegistry typeRegistry = TypeRegistry::Get();
  DALI_CHECK_INSTANCE(typeRegistry, "TypeRegistry instance is not created.");

  TypeInfo typeInfo = typeRegistry.GetTypeInfo( basehandle.GetTypeName() );
  bTypeInfoStatus = basehandle.GetTypeInfo( typeInfo );

  DALI_CHECK_FAIL(!bTypeInfoStatus, "BaseHandle::GetTypeInfo(TypeInfo) is failed to return type info for the Handle.");

  DaliLog::PrintPass();
}
void BaseHandleGetTypeInfoN()
{
  BaseHandle basehandle;

  try
  {    TypeRegistry typeRegistry = TypeRegistry::Get();
    TypeInfo typeInfo = typeRegistry.GetTypeInfo( basehandle.GetTypeName() );
  }
  catch (Dali::DaliException(e))
  {
    DALI_CHECK_FAIL( false, "basehandle is empty" );
  }

  DaliLog::PrintPass();
}
void BaseHandleGetBaseObject()
{
  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;

  int nCount = 0, nFlag = 0;
  const float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;

  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage , " stage is not created " );

  ++nFlag;
  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  ++nFlag;
  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);
  DALI_CHECK_FAIL(!actor.OnStage(), " actor is not in OnStage " );

  BaseHandle basehandle = actor;
  DALI_CHECK_FAIL(!basehandle, " basehandle is not created " );

  nCount =  basehandle.GetBaseObject().ReferenceCount();
  strGetname = basehandle.GetBaseObject().GetTypeName();

  DALI_CHECK_FAIL(nCount != ++nFlag && strGetname != strname, " Getting Count failed or Base Object is not Actor");

  Actor actorHandle = Dali::DownCast<Actor>(basehandle);
  DALI_CHECK_FAIL(!actorHandle, " Dali::DownCast(BaseHandle) is failed.");

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void BaseHandleReset()
{

  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;

  int nCount = 0, nFlag = 0;
  const float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;

  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage , " stage is not created " );

  ++nFlag;
  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  ++nFlag;
  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);
  DALI_CHECK_FAIL(!actor.OnStage(), " actor is not in OnStage " );

  BaseHandle basehandle = actor;
  DALI_CHECK_FAIL(!basehandle, " basehandle is not created " );

  nCount =  basehandle.GetBaseObject().ReferenceCount();
  DALI_CHECK_FAIL(nCount != 3, "ReferenceCount should be 3");

  basehandle.Reset();

  DALI_CHECK_FAIL(basehandle, " base handle is not reset which is not expected " );

  DaliLog::PrintPass();
}
void BaseHandleBooleanType()
{
  Actor actor;
  Stage stage;
  string strGetname;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  bool bFlag = false;

  DALI_CHECK_FAIL(!basehandleInit(stage,actor,&vec3SetPosition), " Initialization failed " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  BaseHandle BasehandleCopyobject(Basehandleobject);

  bFlag = static_cast<BaseHandle::BooleanType>(BasehandleCopyobject);
  DALI_CHECK_FAIL(!bFlag, " BasehandleCopyobject is empty " );

  stage.Remove(actor);

  DaliLog::PrintPass();
}
void BaseHandleEqualOperator()
{
  Actor actor;
  Stage stage;
  string strGetname;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  bool bFlag = false;

  DALI_CHECK_FAIL(!basehandleInit(stage,actor,&vec3SetPosition), " Initialization failed " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  BaseHandle BasehandleCopyobject(Basehandleobject);
  bFlag = (Basehandleobject ==  BasehandleCopyobject);
  DALI_CHECK_FAIL(!bFlag, " BasehandleCopyobject and BasehandleDifferentObject are NOT equal " );

  stage.Remove(actor);

  DaliLog::PrintPass();

}
void BaseHandleInequalOperator()
{
  Actor actor;
  Stage stage;
  string strGetname;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  bool bFlag = false;

  DALI_CHECK_FAIL(!basehandleInit(stage,actor,&vec3SetPosition), " Initialization failed " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  BaseHandle BasehandleCopyobject(Basehandleobject);

  BaseHandle BasehandleDifferentObject = Actor::New();

  bFlag = (BasehandleCopyobject != BasehandleDifferentObject);
  DALI_CHECK_FAIL(!bFlag, " BasehandleCopyobject and BasehandleDifferentObject are equal " );

  stage.Remove(actor);

  DaliLog::PrintPass();

}
void BaseHandleGetObjectPtr()
{
  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;

  int nCount = 0, nFlag = 0;
  float      fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  stage = Stage::GetCurrent();

  DALI_CHECK_FAIL(!stage , " stage is not created " );

  ++nFlag;

  actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " actor is not created " );

  ++nFlag;

  stage.Add(actor);
  actor.SetPosition (vec3SetPosition);
  DALI_CHECK_FAIL(!actor.OnStage(), " actor is not in OnStage " );

  BaseHandle Basehandleobject = actor;
  DALI_CHECK_FAIL(!Basehandleobject, " Basehandleobject is not created " );

  Dali::RefObject* p = Basehandleobject.GetObjectPtr();

  nCount = p->ReferenceCount();
  nFlag++;

  DALI_CHECK_FAIL(!p  && nCount != nFlag, " Getting Count failed ");

  p->Unreference();
  nCount = p->ReferenceCount();
  nFlag--;

  DALI_CHECK_FAIL(nCount != nFlag, " Decrement the object's reference count not successful");

  p->Reference();
  stage.Remove(actor);

  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/



/**
 * @testcase        UtcDaliBaseHandleConstructorP
 * @since_tizen     2.4
 * @description     Constructor for BaseHandle.
 */
int UtcDaliBaseHandleConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleCopyConstructorBaseObjectP
 * @since_tizen     2.4
 * @description     This copy constructor is required for (smart) pointer semantics.
 */
int UtcDaliBaseHandleCopyConstructorBaseObjectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_COPY_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleCopyConstructorP2
 * @since_tizen     2.4
 * @description     This copy constructor is required for (smart) pointer semantics.
 */
int UtcDaliBaseHandleCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_COPY_CONSTRUCTOR_P2);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleOperatorAssignmentP
 * @since_tizen     2.4
 * @description     This assignment operator is required for (smart) pointer semantics.
 */
int UtcDaliBaseHandleOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_OPERATOR_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleDoActionP
 * @since_tizen     2.4
 * @description     This tests the DoAction api.
 */
int UtcDaliBaseHandleDoActionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_DO_ACTION);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetTypeNameP
 * @since_tizen     2.4
 * @description     This tests the GetTypeName api.
 */
int UtcDaliBaseHandleGetTypeNameP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_TYPE_NAME_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetTypeNameN
 * @since_tizen     2.4
 * @description     This tests the GetTypeName api.
 */
int UtcDaliBaseHandleGetTypeNameN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_TYPE_NAME_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetTypeInfoP
 * @since_tizen     2.4
 * @description     This tests the GetTypeInfo api.
 */
int UtcDaliBaseHandleGetTypeInfoP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_TYPE_INFO_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetTypeInfoN
 * @since_tizen     2.4
 * @description     This tests the GetTypeInfo api.
 */
int UtcDaliBaseHandleGetTypeInfoN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_TYPE_INFO_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetBaseObjectP
 * @since_tizen     2.4
 * @description     Retrieve the internal Dali resource.
 */
int UtcDaliBaseHandleGetBaseObjectP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_BASE_OBJECT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleResetP
 * @since_tizen     2.4
 * @description     This tests the Reset api.
 */
int UtcDaliBaseHandleResetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_RESET);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleBooleanTypeP
 * @since_tizen     2.4
 * @description     Converts an handle to a BooleanType.
 */
int UtcDaliBaseHandleBooleanTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_BOOLEAN_TYPE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleEqualOperatorP
 * @since_tizen     2.4
 * @description     Inequality operator overload.
 */

int UtcDaliBaseHandleEqualOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_EQUAL_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleInequalOperatorP
 * @since_tizen     2.4
 * @description     Inequality operator overload.
 */

int UtcDaliBaseHandleInequalOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_INEQUAL_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseHandleGetObjectPtrP
 * @since_tizen     2.4
 * @description     Get the reference counted object pointer.
 */
int UtcDaliBaseHandleGetObjectPtrP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_HANDLE_GET_BASE_OBJECT_PTR);
  application.MainLoop();
  return test_return_value;
}
