#include "utc-dali-refobject-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_RefObject_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_RefObject_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_RefObject_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_RefObject_cleanup(void)
{
}

void RefObjReference();
void RefObjReferenceUnReference();
void RefObjAssignAndReferenceCount();
void RefObjReferenceConstructor();
void RefObjReferenceCopyConstructor();
void RefObjReferenceOperatorAssignment();

namespace
{
  enum TEST_CASES_LIST_REF_OBJECT
  {
    REF_OBJ_REFERENCE_REFERENCE,
    REF_OBJ_REFERENCE_UN_REFERENCE,
    REF_OBJ_REFERENCE_COUNT,
    REF_OBJ_REFERENCE_CONSTRUCTOR,
    REF_OBJ_REFERENCE_COPYCONSTRUCTOR,
    REF_OBJ_REFERENCE_OPERATOR_ASSIGNMENT
  };

  struct Ref_Object_TestApp : public ConnectionTracker
  {
    Ref_Object_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Ref_Object_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Ref_Object_TestApp::Tick );
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
        case REF_OBJ_REFERENCE_REFERENCE:
          RefObjReference();
          break;

        case REF_OBJ_REFERENCE_UN_REFERENCE:
          RefObjReferenceUnReference();
          break;

        case REF_OBJ_REFERENCE_COUNT:
          RefObjAssignAndReferenceCount();
          break;

        case REF_OBJ_REFERENCE_CONSTRUCTOR:
          RefObjReferenceConstructor();
          break;

        case REF_OBJ_REFERENCE_COPYCONSTRUCTOR:
          RefObjReferenceCopyConstructor();
          break;

        case REF_OBJ_REFERENCE_OPERATOR_ASSIGNMENT:
          RefObjReferenceOperatorAssignment();
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
void RefObjReference()
{
  int nCount1 = 0, nFlag = 0;

  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );
  BaseHandle BaseRefobject = actor;
  DALI_CHECK_FAIL(!BaseRefobject, "RefObjobject is not created" );
  nCount1 = BaseRefobject.GetBaseObject().ReferenceCount();

  RefObject *pRefobject = BaseRefobject.GetObjectPtr();
  DALI_CHECK_FAIL(pRefobject == NULL, "Reference is NULL after assigning basehandle to it" );

  pRefobject->Reference();
  nFlag = pRefobject->ReferenceCount();
  DALI_CHECK_FAIL(nCount1 >= nFlag, "Referencing was not successful");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void RefObjReferenceUnReference()
{
  int nCount = 0, nCount1 = 0, nFlag = 0;

  Actor actor;
  Stage stage;
  string strname = "Actor", strGetname;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );
  BaseHandle BaseRefobject = actor;
  DALI_CHECK_FAIL(!BaseRefobject, "RefObjobject is not created" );
  nCount1 = BaseRefobject.GetBaseObject().ReferenceCount();

  RefObject *pRefobject = BaseRefobject.GetObjectPtr();
  DALI_CHECK_FAIL(pRefobject == NULL, "Reference is NULL after assigning basehandle to it" );

  pRefobject->Reference();
  nFlag = pRefobject->ReferenceCount();
  DALI_CHECK_FAIL(nCount1 >= nFlag, "Referencing was not successful");
  pRefobject->Unreference();
  nCount = pRefobject->ReferenceCount();

  DALI_CHECK_FAIL(nCount != nCount1, "Decrement the object's reference count not successful");

  stage.Remove(actor);
  DaliLog::PrintPass();
}

void RefObjAssignAndReferenceCount()
{
  int nCount = 0, nCount1 = 0;

  Actor actor;
  Stage stage;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  RefObject  *pRefobject  = NULL, *pRefobject2 = NULL;

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );

  BaseHandle BaseRefobject = actor;

  DALI_CHECK_FAIL(!BaseRefobject, "BaseHandle is not created" );
  pRefobject = BaseRefobject.GetObjectPtr();
  DALI_CHECK_FAIL(pRefobject == NULL, "Reference is NULL after assigning basehandle to it" );

  pRefobject2 = pRefobject;

  DALI_CHECK_FAIL(pRefobject2 == NULL, "Reference is NULL after assigning a constant reference object to it" );

  nCount = pRefobject->ReferenceCount();

  nCount1 = BaseRefobject.GetBaseObject().ReferenceCount();

  DALI_CHECK_FAIL(nCount != nCount1, "Getting Reference Count mismatched");

  stage.Remove(actor);

  DaliLog::PrintPass();
}

void RefObjReferenceConstructor()
{
  int nCount1 = 0;

  Actor actor;
  Stage stage;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  RefObject  *pRefobject  = NULL, *pRefobject2 = NULL;

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );

  BaseHandle BaseRefobject = actor;
  DALI_CHECK_FAIL(!BaseRefobject, "BaseHandle is not created" );

  DaliLog::PrintPass();
}

void RefObjReferenceCopyConstructor()
{
  Actor actor;
  Stage stage;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  RefObject  *pRefobject  = NULL;

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );

  BaseHandle BaseRefobject = actor;
  DALI_CHECK_FAIL(!BaseRefobject, "BaseHandle is not created" );

  BaseHandle BasehandleCopyobject(BaseRefobject);
  DALI_CHECK_FAIL(!BasehandleCopyobject, " BasehandleCopyobject is not created " );

  DaliLog::PrintPass();
}

void RefObjReferenceOperatorAssignment()
{
  Actor actor;
  Stage stage;
  float fSetValuex = 0.13f, fSetValuey = 0.12f, fSetValuez = 0.11f;
  Vector3 vec3SetPosition(fSetValuex, fSetValuey, fSetValuez);
  RefObject  *pRefobject  = NULL, *pRefobject2 = NULL;

  DALI_CHECK_FAIL(!RefObjInit(stage,actor,&vec3SetPosition), "Initialization failed" );

  BaseHandle BaseRefobject = actor;

  DALI_CHECK_FAIL(!BaseRefobject, "BaseHandle is not created" );
  pRefobject = BaseRefobject.GetObjectPtr();
  DALI_CHECK_FAIL(pRefobject == NULL, "Reference is NULL after assigning basehandle to it" );

  pRefobject2 = pRefobject;

  DALI_CHECK_FAIL(pRefobject2 == NULL, "Reference is NULL after assigning a constant reference object to it" );

  stage.Remove(actor);

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase        UtcDaliRefObjReferenceReferenceP
 * @since_tizen     2.4
 * @description     Tests the refObject UnReference Api.
 */
int UtcDaliRefObjReferenceReferenceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_REFERENCE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRefObjReferenceUnReferenceP
 * @since_tizen     2.4
 * @description     Tests the refObject UnReference Api.
 */
int UtcDaliRefObjReferenceUnReferenceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_UN_REFERENCE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRefObjAssignAndReferenceCountP
 * @since_tizen     2.4
 * @description     Retrieve the object's reference count.
 */
int UtcDaliRefObjReferenceCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_COUNT);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRefObjRefObjectConstructorP
 * @since_tizen     2.4
 * @description     Tests the refObject Constructor.
 */
int UtcDaliRefObjRefObjectConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_CONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRefObjRefObjectCopyConstructorP
 * @since_tizen     2.4
 * @description     Tests the refObject Copy Constructor.
 */
int UtcDaliRefObjRefObjectCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_COPYCONSTRUCTOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliRefObjReferenceOperatorAssignmentP
 * @since_tizen     2.4
 * @description     Tests the object's operator assignment API.
 */
int UtcDaliRefObjReferenceOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ref_Object_TestApp testApp( application, REF_OBJ_REFERENCE_OPERATOR_ASSIGNMENT);
  application.MainLoop();
  return test_return_value;
}

