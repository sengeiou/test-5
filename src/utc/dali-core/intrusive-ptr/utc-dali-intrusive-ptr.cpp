#include "utc-dali-intrusive-ptr-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Intrusiveptr

/**
 * @function      utc_Dali_IntrusivePtr_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_IntrusivePtr_startup(void)
{
  test_return_value = 0;
}

/**
 * @function      utc_Dali_IntrusivePtr_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_IntrusivePtr_cleanup(void)
{
}

void IntrusivePtrConstructorReset();
void IntrusivePtrGet();
void IntrusivePtrCopyConstructors();
void IntrusivePtrAssignmentEquals();
void IntrusivePtrResetWithReference();
void IntrusivePtrBooleanType();
void IntrusivePtrPointerDereference();
void IntrusivePtrDetach();

namespace
{
  enum TEST_CASES_LIST_INTRUSIVE_PTR
  {
    INTRUSIVE_PTR_CONSTRUCTOR_RESET,
    INTRUSIVE_PTR_GET,
    INTRUSIVE_PTR_COPY_CONSTRUCTORS,
    INTRUSIVE_PTR_ASSIGNMENTE_QUALS,
    INTRUSIVE_PTR_RESET_WITH_REFERENCE,
    INTRUSIVE_PTR_BOOLEAN_TYPE,
    INTRUSIVE_PTR_POINTER_DEREFERENCE,
    INTRUSIVE_PTR_DETACH
  };

  struct IntrusivePtr_TestApp : public ConnectionTracker
  {
    IntrusivePtr_TestApp( Application& app, int test_case ) : mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &IntrusivePtr_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &IntrusivePtr_TestApp::Tick );
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
        case INTRUSIVE_PTR_CONSTRUCTOR_RESET:
          IntrusivePtrConstructorReset();
          break;

        case INTRUSIVE_PTR_GET:
          IntrusivePtrGet();
          break;

        case INTRUSIVE_PTR_COPY_CONSTRUCTORS:
          IntrusivePtrCopyConstructors();
          break;

        case INTRUSIVE_PTR_ASSIGNMENTE_QUALS:
          IntrusivePtrAssignmentEquals();
          break;

        case INTRUSIVE_PTR_RESET_WITH_REFERENCE:
          IntrusivePtrResetWithReference();
          break;

        case INTRUSIVE_PTR_BOOLEAN_TYPE:
          IntrusivePtrBooleanType();
          break;

        case INTRUSIVE_PTR_POINTER_DEREFERENCE:
          IntrusivePtrPointerDereference();
          break;

        case INTRUSIVE_PTR_DETACH:
          IntrusivePtrDetach();
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

void IntrusivePtrConstructorReset()
{
  float fTime = 1.0f;

  Animation animation = Animation::New( fTime );
  DALI_CHECK_FAIL(!animation, "Animation::New() is failed.");

  IntrusivePtr< RefObject > intrusivePtr( animation.GetObjectPtr() );

  DALI_CHECK_FAIL(!intrusivePtr, "IntrusivePtr::IntrusivePtr() is failed.");

  intrusivePtr.Reset();
  DALI_CHECK_FAIL(intrusivePtr, "IntrusivePtr::Reset() is failed");

  DaliLog::PrintPass();
}

void IntrusivePtrGet()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed");

  RefObject *refObjectActor = actor.GetObjectPtr();
  IntrusivePtr< RefObject > intrusivePtr( refObjectActor );
  DALI_CHECK_FAIL(!intrusivePtr, "IntrusivePtr::IntrusivePtr() is failed.");

  RefObject *refObject = intrusivePtr.Get();
  DALI_CHECK_FAIL(refObject != refObjectActor, "IntrusivePtr::Get() is failed");

  intrusivePtr.Reset();
  DaliLog::PrintPass();
}

void IntrusivePtrCopyConstructors()
{
  unsigned int uX = 20u, uY = 15u;

  BufferImage bufferImage = BufferImage::New( uX, uY );
  DALI_CHECK_FAIL(!bufferImage, "BufferImage::New() is failed.");

  IntrusivePtr< BaseObject > intrusivePtrBase( &bufferImage.GetBaseObject() );
  DALI_CHECK_FAIL(!intrusivePtrBase, "IntrusivePtr::IntrusivePtr() is failed for bufferImage's baseObject.");

  ImageView imageView = ImageView::New( bufferImage );
  DALI_CHECK_FAIL(!imageView, "ImageView::New() is failed.");

  RefObject *refObject = imageView.GetObjectPtr();
  IntrusivePtr< RefObject > intrusivePtrRef( refObject );
  DALI_CHECK_FAIL(!intrusivePtrRef, "IntrusivePtr::IntrusivePtr() is failed for imageView's refObject");

  IntrusivePtr< RefObject > intrusivePtrCopyBase( intrusivePtrBase );
  DALI_CHECK_FAIL(!intrusivePtrCopyBase, "IntrusivePtr instance is NULL after copying for BaseObject type");
  DALI_CHECK_FAIL(intrusivePtrCopyBase != intrusivePtrBase, "IntrusivePtr Copy Constructor is failed to copy intrusivePtr of BaseObject type");

  IntrusivePtr< RefObject > intrusivePtrCopyRef( intrusivePtrRef );
  DALI_CHECK_FAIL(!intrusivePtrCopyRef, "IntrusivePtr instance is NULL after copying for RefObject type");
  DALI_CHECK_FAIL(intrusivePtrCopyRef != intrusivePtrRef, "IntrusivePtr::Copy Constructor is failed to copy intrusivePtr of RefObject type");

  intrusivePtrBase.Reset();
  intrusivePtrRef.Reset();

  DaliLog::PrintPass();
}

void IntrusivePtrAssignmentEquals()
{
  PinchGestureDetector pinchGestureDetector = PinchGestureDetector::New();
  DALI_CHECK_FAIL(!pinchGestureDetector, "PinchGestureDetector::New() is failed.");

  RefObject *refObject = pinchGestureDetector.GetObjectPtr();

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed.");

  IntrusivePtr< RefObject > intrusivePtr( actor.GetObjectPtr() );
  DALI_CHECK_FAIL(!intrusivePtr, " IntrusivePtr::IntrusivePtr() is failed.");

  IntrusivePtr< RefObject > intrusivePtrAssignmentType = refObject;

  DALI_CHECK_FAIL(!intrusivePtrAssignmentType, "InstrusivePtr instance is NULL after assigning object pointer which is unexpected" );
  DALI_CHECK_FAIL(intrusivePtrAssignmentType != pinchGestureDetector.GetObjectPtr(), "IntrusivePtr::operator= is failed to assign the pointer to pinchGestureDetector object");
  DALI_CHECK_FAIL(!(intrusivePtrAssignmentType == pinchGestureDetector.GetObjectPtr() ), "IntrusivePtr::operator== is failed for the assigned pointer to pinchGestureDetector object");

  IntrusivePtr< RefObject > intrusivePtrAssignmentIntrusive = intrusivePtr;

  DALI_CHECK_FAIL(!intrusivePtrAssignmentIntrusive, "InstrusivePtr instance is NULL after assigning const reference to intrusive pointer which is unexpected" );
  DALI_CHECK_FAIL(intrusivePtrAssignmentIntrusive != intrusivePtr, "IntrusivePtr::operator= is failed to assign const reference to intrusive pointer");
  DALI_CHECK_FAIL(!(intrusivePtrAssignmentIntrusive == intrusivePtr ), "IntrusivePtr::operator== is failed for the assigned const reference to intrusive pointer.");

  intrusivePtr.Reset();
  DaliLog::PrintPass();
}

void IntrusivePtrResetWithReference()
{
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "The stage is not created");

  Handle handle = Layer::New();
  DALI_CHECK_FAIL(!handle, "The handle is not created for Layer");

  IntrusivePtr< RefObject > intrusivePtr( stage.GetObjectPtr() );
  DALI_CHECK_FAIL(!intrusivePtr, "IntrusivePtr::IntrusivePtr() is failed.");

  if( intrusivePtr != stage.GetObjectPtr() )
  {
    LOG_E("The intrusivePtr is not matched to Stage's object pointer");
    intrusivePtr.Reset();
    test_return_value=1;
    return;
  }

  intrusivePtr.Reset( handle.GetObjectPtr() );
  DALI_CHECK_FAIL(intrusivePtr != handle.GetObjectPtr(), "IntrusivePtr::Reset is failed to reset intrusive pointer with reference counted handle object");
  DaliLog::PrintPass();
}

void IntrusivePtrBooleanType()
{
  bool bCheckBoolean = false;

  CameraActor cameraActor = CameraActor::New();
  DALI_CHECK_FAIL(!cameraActor, "CameraActor::New() is failed");

  IntrusivePtr< RefObject > intrusivePtr( cameraActor.GetObjectPtr() );

  bCheckBoolean = static_cast< IntrusivePtr< RefObject >::BooleanType >( intrusivePtr );
  DALI_CHECK_FAIL(!bCheckBoolean, "IntrusivePtr instance is NULL");

  bCheckBoolean = false;
  intrusivePtr.Reset();
  bCheckBoolean = static_cast<IntrusivePtr< RefObject >::BooleanType>(intrusivePtr);
  DALI_CHECK_FAIL(bCheckBoolean, "IntrusivePtr instance is not NULL");

  DaliLog::PrintPass();
}

void IntrusivePtrPointerDereference()
{
  int nRefCount = 0, nCount = 0, nDerefCount = 0;
  g_bIntrusivePtrDummyCheck = false;

  IntrusivePtrDummyClass *pintrusivePtrDummyClass = new IntrusivePtrDummyClass();
  DALI_CHECK_FAIL(!pintrusivePtrDummyClass, "IntrusivePtrDummyClass instance creation is failed");

  IntrusivePtr< IntrusivePtrDummyClass > intrusivePtr = pintrusivePtrDummyClass;
  DALI_CHECK_FAIL(!intrusivePtr, "IntrusivePtr instance creation is failed with IntrusivePtrDummyClass");
  DALI_CHECK_FAIL(intrusivePtr.Get() != pintrusivePtrDummyClass, "Failed to get pointer to pintrusivePtrDummyClass");

  intrusivePtr->CheckIntrusivePtrDummyCreation();
  DALI_CHECK_FAIL(!g_bIntrusivePtrDummyCheck, "IntrusivePtr pointer operator is failed");

  nRefCount = intrusivePtr->ReferenceCount();

  DALI_CHECK_FAIL(nRefCount == nCount, "Failed to get reference count using pointer operator" );

  g_bIntrusivePtrDummyCheck = false;

  (*intrusivePtr).CheckIntrusivePtrDummyCreation();
  DALI_CHECK_FAIL(!g_bIntrusivePtrDummyCheck, "IntrusivePtr dereference operator is failed");

  nDerefCount = (*intrusivePtr).ReferenceCount();
  DALI_CHECK_FAIL(nDerefCount != nRefCount, "Failed to get reference count using dereference operator");

  intrusivePtr.Reset();
  DaliLog::PrintPass();
}

void IntrusivePtrDetach()
{
  int nRefCount = 0, nRefCountInPtr = 0;

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed");

  RefObject *refObjectActor = actor.GetObjectPtr();
  IntrusivePtr< RefObject > intrusivePtr( refObjectActor );
  DALI_CHECK_FAIL(!intrusivePtr, "IntrusivePtr::IntrusivePtr() is failed.");

  nRefCount = refObjectActor->ReferenceCount();
  RefObject *refObject = intrusivePtr.Get();

  DALI_CHECK_FAIL(refObject != refObjectActor, "IntrusivePtr::Get() is failed");

  nRefCountInPtr = refObject->ReferenceCount();
  DALI_CHECK_FAIL(nRefCountInPtr != nRefCount, "Reference count of actor object is not matched to reference count of intrusivePtr object");

  intrusivePtr.Reset();

  refObject = intrusivePtr.Detach();
  DALI_CHECK_FAIL(refObject == refObjectActor, "IntrusivePtr::Detach() is failed. Detached pointer is same as actor's object pointer.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase         UtcDaliIntrusivePtrConstructorResetP
 * @since_tizen     2.4
 * @description      Check whether IntrusivePtr instance is created and reset properly
 */
int UtcDaliIntrusivePtrConstructorResetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_CONSTRUCTOR_RESET);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliIntrusivePtrGetP
 * @since_tizen     2.4
 * @description      Check whether IntrusivePtr::Get() can get pointer to reference counted object
 */
int UtcDaliIntrusivePtrGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_GET);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliIntrusivePtrCopyConstructorsP
 * @since_tizen     2.4
 * @description      Check whether IntrusivePtr Copy constructors work properly or not
 */
int UtcDaliIntrusivePtrCopyConstructorsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_COPY_CONSTRUCTORS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliIntrusivePtrAssignmentEqualsP
 * @since_tizen     2.4
 * @description      Check whether IntrusivePtr Assignment operators work properly or not
 */
int UtcDaliIntrusivePtrAssignmentEqualsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_ASSIGNMENTE_QUALS);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliIntrusivePtrResetWithReferenceP
 * @since_tizen     2.4
 * @description      Reset intrusive pointer with reference counted object
 */
int UtcDaliIntrusivePtrResetWithReferenceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_RESET_WITH_REFERENCE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcDaliIntrusivePtrBooleanTypeP
 * @since_tizen       2.4
 * @description        Check if IntrusivePtr::operator BooleanType() can convert an handle to a BooleanType.
 */
int UtcDaliIntrusivePtrBooleanTypeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_BOOLEAN_TYPE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcDaliIntrusivePtrPointerDereferenceP
 * @since_tizen       2.4
 * @description        Check if IntrusivePtr Pointer operator and Dereference operator work properly or not.
 */
int UtcDaliIntrusivePtrPointerDereferenceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_POINTER_DEREFERENCE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase         UtcDaliIntrusivePtrDetachP
 * @since_tizen     2.4
 * @description      Whether detach pointer from intrusive ptr counting.
 */
int UtcDaliIntrusivePtrDetachP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  IntrusivePtr_TestApp testApp( application, INTRUSIVE_PTR_DETACH);
  application.MainLoop();
  return test_return_value;
}
