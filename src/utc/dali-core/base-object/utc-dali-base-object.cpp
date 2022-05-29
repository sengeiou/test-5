#include "utc-dali-base-object-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function        utc_Dali_BaseObject_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_BaseObject_startup(void)
{
  test_return_value=0;
}


/**
 * @function        utc_dali_BaseObject_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_BaseObject_cleanup(void)
{
}


bool gBaseObjectCallBack = false;         /**Status for animation finish callback*/
Actor gBaseObjectActor;                 /**Actor instance */
Animation gBaseObjectAnimation;         /**Animation instance */


void BaseObjectAnimationCheck(Animation& animation)
{
  LOG_I("Callback for animation finished is called");
  gBaseObjectCallBack = true;
};

void BaseObjectGetTypeNameInfoForActorP();
void BaseObjectGetTypeNameInfoForAnimationP();
void BaseObjectGetTypeNameInfoForLongPressGestureDetectorP();
void BaseObjectGetTypeNameInfoForBufferImageP();
void BaseObjectDoActionP();
void VTBaseObjectDoAction001P();

namespace
{
  enum TEST_CASES_LIST
  {
    BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ACTOR_P,
    BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ANIMATION_P,
    BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_LONGPRESSGESTUREDETECTOR_P,
    BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_BUFFERIMAGE_P,
    BASE_OBJECT_DO_ACTION_P
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
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }

      VerdictTest();

      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
      }
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ACTOR_P:
          BaseObjectGetTypeNameInfoForActorP();
          break;

        case BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ANIMATION_P:
          BaseObjectGetTypeNameInfoForAnimationP();
          break;

        case BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_LONGPRESSGESTUREDETECTOR_P:
          BaseObjectGetTypeNameInfoForLongPressGestureDetectorP();
          break;

        case BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_BUFFERIMAGE_P:
          BaseObjectGetTypeNameInfoForBufferImageP();
          break;

        case BASE_OBJECT_DO_ACTION_P:
          BaseObjectDoActionP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case BASE_OBJECT_DO_ACTION_P:
          VTBaseObjectDoAction001P();
          mTimer.Stop();
          mApplication.Quit();
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace




void BaseObjectGetTypeNameInfoForActorP()
{
  Actor actor = Actor::New();
  DALI_CHECK_FAIL( !actor , " Actor::New() is failed " );

  if(!BaseObjectGetTypeNameInfo( actor))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void BaseObjectGetTypeNameInfoForAnimationP()
{
  float fTime = 1.0f;

  Animation animation = Animation::New( fTime );
  DALI_CHECK_FAIL( !animation , " Animation::New() is failed " );

  if(!BaseObjectGetTypeNameInfo( animation))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}


void BaseObjectDoActionP()
{
  Property::Map mapAttributes;
  bool bActionCheck = false;
  gBaseObjectCallBack = false;
  const char* ACTION_PLAY = "play";

  Vector4 vec4TargetColor = Color::CYAN;
  Property::Value propertyValueTime;
  const float fDuration = 0.3f;

  gBaseObjectActor = Actor::New();
  DALI_CHECK_FAIL( !gBaseObjectActor , " Actor::New() is failed " );

  gBaseObjectAnimation = Animation::New( fDuration );
  DALI_CHECK_FAIL( !gBaseObjectAnimation , " Animation::New() is failed " );

  Stage::GetCurrent().Add( gBaseObjectActor );

  gBaseObjectAnimation.AnimateTo(Property(gBaseObjectActor, Actor::Property::COLOR), vec4TargetColor );
  propertyValueTime = Property::Value( fDuration );
  mapAttributes[ACTION_PLAY] = propertyValueTime;

  gBaseObjectAnimation.FinishedSignal().Connect( &BaseObjectAnimationCheck );
  bActionCheck = gBaseObjectAnimation.GetBaseObject().DoAction( ACTION_PLAY, mapAttributes);
  DALI_CHECK_FAIL( !bActionCheck , " BaseObject::DoAction() is failed" );
}

void VTBaseObjectDoAction001P()
{
  Vector4 vec4TargetColor = Color::CYAN;
  DALI_CHECK_FAIL( !gBaseObjectCallBack , " BaseObjectAnimationCheck is not called successfully" );
  DALI_CHECK_FAIL( gBaseObjectActor.GetCurrentColor() != vec4TargetColor , " Animation is failed to change actor's color" );

  gBaseObjectAnimation.Clear();
  Stage::GetCurrent().Remove( gBaseObjectActor );
  DaliLog::PrintPass();
}

void BaseObjectGetTypeNameInfoForLongPressGestureDetectorP()
{
  LongPressGestureDetector longPressGestureDetector = LongPressGestureDetector::New();
  DALI_CHECK_FAIL( !longPressGestureDetector , " LongPressGestureDetector::New() is failed " );

  if(!BaseObjectGetTypeNameInfo( longPressGestureDetector))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

void BaseObjectGetTypeNameInfoForBufferImageP()
{
  unsigned int uW = 10u, uH = 15u;

  BufferImage bufferImage = BufferImage::New( uW, uH );
  DALI_CHECK_FAIL( !bufferImage , " BufferImage::New() is failed " );

  if(!BaseObjectGetTypeNameInfo( bufferImage))
  {
    test_return_value=TC_FAIL;
    return;
  }

  DaliLog::PrintPass();
}

/**
 * @testcase        UtcDaliBaseObjectGetTypeNameInfoForActorP
 * @since_tizen     2.4
 * @description     checks for BaseObject::GetTypeNameInfoForActorP() functionality
 */

int UtcDaliBaseObjectGetTypeNameInfoForActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ACTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseObjectGetTypeNameInfoForAnimationP
 * @since_tizen     2.4
 * @description     checks for BaseObject::GetTypeNameInfoForAnimationP() functionality
 */

int UtcDaliBaseObjectGetTypeNameInfoForAnimationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_ANIMATION_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseObjectGetTypeNameInfoForLongPressGestureDetectorP
 * @since_tizen     2.4
 * @description     checks for BaseObject::GetTypeNameInfoForLongPressGestureDetectorP() functionality
 */

int UtcDaliBaseObjectGetTypeNameInfoForLongPressGestureDetectorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_LONGPRESSGESTUREDETECTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseObjectGetTypeNameInfoForBufferImageP
 * @since_tizen     2.4
 * @description     checks for BaseObject::GetTypeNameInfoForBufferImageP() functionality
 */

int UtcDaliBaseObjectGetTypeNameInfoForBufferImageP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_OBJECT_GET_TYPE_NAME_INFO_FOR_BUFFERIMAGE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliBaseObjectDoActionP
 * @since_tizen     2.4
 * @description     checks for BaseObject::DoActionP() functionality
 */

int UtcDaliBaseObjectDoActionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BASE_OBJECT_DO_ACTION_P);
  application.MainLoop();
  return test_return_value;
}

