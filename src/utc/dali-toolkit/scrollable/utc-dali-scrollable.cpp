#include "utc-dali-scrollable-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Scrollable_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Scrollable_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_scrollable_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Scrollable_cleanup(void)
{

}

void ScrollableConstructorP();
void ScrollableCopyConstructorP();
void ScrollableOperatorAssignmentP();
void ScrollableDownCastP();
void ScrollableDownCastN();
void ScrollableSetIsOvershootEnabledP();
void ScrollableSetGetOvershootEffectColorP();
void ScrollableSetGetOvershootAnimationSpeedP();
void ScrollableScrollStartedSignalP();
void ScrollableScrollUpdatedSignalP();
void ScrollableScrollCompletedSignalP();

class ScrollableSignalHandler : public Dali::ConnectionTracker
{
  public:
    ScrollableSignalHandler() :
      mCalls( 0 )
  {
  }

    void Callback( const Vector2& currentScrollPosition )
    {
      mCalls++;
    }

    unsigned int GetCalls() const
    {
      return mCalls;
    }

  private:
    unsigned int mCalls;
};

namespace
{
  enum TEST_CASES_LIST_SROLLABLE
  {
    SCROLLABLE_CONSTRUCTOR_P,
    SCROLLABLE_COPY_CONSTRUCTOR_P,
    SCROLLABLE_OPERATOR_ASSIGNMENT_P,
    SCROLLABLE_DOWNCAST_P,
    SCROLLABLE_DOWNCAST_N,
    SCROLLABLE_SET_IS_OVERSHOOT_ENABLED_P,
    SCROLLABLE_SET_GET_OVERSHOOT_EFFECT_COLOR_P,
    SCROLLABLE_SET_GET_OVER_SHOOT_ANIMATION_SPEED_P,
    SCROLLABLE_SCROLL_STARTED_SIGNAL_P,
    SCROLLABLE_SCROLL_UPDATED_SIGNAL_P,
    SCROLLABLE_SCROLL_COMPLETED_SIGNAL_P
  };

  struct Scrollable_TestApp : public ConnectionTracker
  {
    Scrollable_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Scrollable_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Scrollable_TestApp::Tick );
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
        case SCROLLABLE_CONSTRUCTOR_P:
          ScrollableConstructorP();
          break;

        case SCROLLABLE_COPY_CONSTRUCTOR_P:
          ScrollableCopyConstructorP();
          break;

        case SCROLLABLE_OPERATOR_ASSIGNMENT_P:
          ScrollableOperatorAssignmentP();
          break;

        case SCROLLABLE_DOWNCAST_P:
          ScrollableDownCastP();
          break;

        case SCROLLABLE_DOWNCAST_N:
          ScrollableDownCastN();
          break;

        case SCROLLABLE_SET_IS_OVERSHOOT_ENABLED_P:
          ScrollableSetIsOvershootEnabledP();
          break;

        case SCROLLABLE_SET_GET_OVERSHOOT_EFFECT_COLOR_P:
          ScrollableSetGetOvershootEffectColorP();
          break;

        case SCROLLABLE_SET_GET_OVER_SHOOT_ANIMATION_SPEED_P:
          ScrollableSetGetOvershootAnimationSpeedP();
          break;

        case SCROLLABLE_SCROLL_STARTED_SIGNAL_P:
          ScrollableScrollStartedSignalP();
          break;

        case SCROLLABLE_SCROLL_UPDATED_SIGNAL_P:
          ScrollableScrollUpdatedSignalP();
          break;

        case SCROLLABLE_SCROLL_COMPLETED_SIGNAL_P:
          ScrollableScrollCompletedSignalP();
          break;
      }
    }
    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace

void ScrollableConstructorP()
{
  Scrollable scrollable;
  DALI_CHECK_FAIL( scrollable, "Default Scrollable  handle is not null.");

  DaliLog::PrintPass();
}

void ScrollableCopyConstructorP()
{
  const Vector2 VEC2_SET_SIZE(2.0f,5.0f);
  ScrollView scrollview = ScrollView::New();
  DALI_CHECK_FAIL(!scrollview, "Scrollview::New is failed");

  Scrollable scrollable = scrollview;
  Scrollable scrollablenew (scrollable);
  DALI_CHECK_FAIL(!scrollablenew, "CopyConstructor failed");
  DALI_CHECK_FAIL(scrollablenew != scrollable, "Scrollable::CopyConstructor is failed");

  DaliLog::PrintPass();
}

void ScrollableOperatorAssignmentP()
{
  const Vector2 VEC2_SET_SIZE(2.0f,5.0f);
  ScrollView scrollview = ScrollView::New();
  DALI_CHECK_FAIL(!scrollview, "Scrollview::New is failed");
  scrollview.SetDrawMode(Dali::DrawMode::OVERLAY_2D);

  //Assignment
  Scrollable scrollable = scrollview;
  DALI_CHECK_FAIL(scrollable != scrollview, "Scrollable::Assignment is failed ");
  DALI_CHECK_FAIL(scrollable.GetDrawMode() != Dali::DrawMode::OVERLAY_2D, "Scrolable::Assignment property mismatched");

  DaliLog::PrintPass();
}

void ScrollableDownCastP()
{
  ScrollView scrollview = ScrollView::New();
  BaseHandle handle(scrollview);
  DALI_CHECK_FAIL(!handle, "Base handle creation failed");
  Scrollable scrollable = Scrollable::DownCast(handle) ;
  DALI_CHECK_FAIL(scrollable != scrollview, "Scrollable::Downcast is failed ");
  DALI_CHECK_FAIL(!scrollable, "Scrolable::downcast is failed");

  DaliLog::PrintPass();
}

void ScrollableDownCastN()
{
  BaseHandle uninitialized_handle;
  DALI_CHECK_FAIL(uninitialized_handle, "Base handle is not empty.");
  Scrollable scrollable = Scrollable::DownCast(uninitialized_handle) ;
  DALI_CHECK_FAIL(scrollable, "Scrollable handle is not empty.");

  DaliLog::PrintPass();
}

void ScrollableSetIsOvershootEnabledP()
{
  bool bIsEnabled = false;

  ScrollView scrollview = ScrollView::New();
  DALI_CHECK_FAIL(!scrollview, "Scrollview::New is failed");
  BaseHandle handle(scrollview);
  DALI_CHECK_FAIL(!handle, "Base handle creation failed");
  Scrollable scrollable = Scrollable::DownCast(handle) ;
  DALI_CHECK_FAIL(!scrollable, "Scrollable::DownCast is failed");

  scrollable.SetOvershootEnabled(true);
  bIsEnabled = scrollable.IsOvershootEnabled();
  DALI_CHECK_FAIL(!bIsEnabled,"IsOvershootEnabled is failed to return true after setting overshoot enabled true.");

  scrollable.SetOvershootEnabled(false);
  bIsEnabled = scrollable.IsOvershootEnabled();
  DALI_CHECK_FAIL(bIsEnabled,"IsOvershootEnabled is failed to return false after setting overshoot enabled false.");

  DaliLog::PrintPass();
}


void ScrollableSetGetOvershootEffectColorP()
{
  const Vector4 VEC4_SET_COLOR(2.0f, 1.0f, 0.0f,3.0f);
  ScrollView scrollview = ScrollView::New();
  DALI_CHECK_FAIL(!scrollview, "Scrollview::New is failed");
  BaseHandle handle(scrollview);
  DALI_CHECK_FAIL(!handle, "Base handle creation failed");
  Scrollable scrollable = Scrollable::DownCast(handle) ;
  DALI_CHECK_FAIL(!scrollable, "Scrollable::DownCast is failed");

  DALI_CHECK_FAIL(scrollable.GetOvershootEffectColor() == VEC4_SET_COLOR,"Set and Get color mismatched");
  scrollable.SetOvershootEffectColor(VEC4_SET_COLOR);
  DALI_CHECK_FAIL(scrollable.GetOvershootEffectColor() != VEC4_SET_COLOR,"Set and Get color mismatched");

  DaliLog::PrintPass();
}

void ScrollableSetGetOvershootAnimationSpeedP()
{
  const float F_SPEED = 5.0f;
  ScrollView scrollview = ScrollView::New();
  DALI_CHECK_FAIL(!scrollview, "Scrollview::New is failed");
  BaseHandle handle(scrollview);
  DALI_CHECK_FAIL(!handle, "Base handle creation failed");
  Scrollable scrollable = Scrollable::DownCast(handle) ;
  DALI_CHECK_FAIL(!scrollable, "Scrollable::DownCast is failed");

  DALI_CHECK_FAIL(scrollable.GetOvershootAnimationSpeed() == F_SPEED,"Set and Get animation speed mismatched");
  scrollable.SetOvershootAnimationSpeed(F_SPEED);
  DALI_CHECK_FAIL(scrollable.GetOvershootAnimationSpeed() != F_SPEED,"Set and Get animation speed mismatched");

  DaliLog::PrintPass();
}

void ScrollableScrollStartedSignalP()
{
  ScrollableSignalHandler callback;
  ScrollView scrollview = ScrollView::New();
  BaseHandle handle(scrollview);

  DALI_CHECK_FAIL(!handle, "Base handle creation failed");

  Scrollable scrollable = Scrollable::DownCast(handle) ;

  DALI_CHECK_FAIL(!scrollable, "Scrollable Downcast failed");

  scrollable.ScrollStartedSignal().Connect(&callback, &ScrollableSignalHandler::Callback);

  scrollview.ScrollTo( Vector2(10.0f, 10.0f) );

  DALI_CHECK_FAIL(callback.GetCalls() != 1, "Scrollable::ScrollStartedSignal() is failed.");

  DaliLog::PrintPass();
}

void ScrollableScrollUpdatedSignalP()
{
  ScrollableSignalHandler callback;
  ScrollView scrollview = ScrollView::New();
  BaseHandle handle(scrollview);

  DALI_CHECK_FAIL(!handle, "Base handle creation failed");

  Scrollable scrollable = Scrollable::DownCast(handle) ;

  DALI_CHECK_FAIL(!scrollable, "Scrollable Downcast failed");

  scrollable.ScrollStartedSignal().Connect(&callback, &ScrollableSignalHandler::Callback);
  scrollview.ScrollTo( Vector2(20.0f, 20.0f) );
  scrollable.ScrollUpdatedSignal().Connect(&callback, &ScrollableSignalHandler::Callback);

  DALI_CHECK_FAIL(!callback.GetCalls(), "Scrollable::ScrollUpdatedSignal() is failed." );

  DaliLog::PrintPass();
}

void ScrollableScrollCompletedSignalP()
{
  ScrollableSignalHandler callback;
  ScrollView scrollview = ScrollView::New();
  BaseHandle handle(scrollview);

  DALI_CHECK_FAIL(!handle, "Base handle creation failed");

  Scrollable scrollable = Scrollable::DownCast(handle) ;

  DALI_CHECK_FAIL(!scrollable, "Scrollable Downcast failed");

  scrollable.ScrollStartedSignal().Connect(&callback, &ScrollableSignalHandler::Callback);
  scrollview.ScrollTo( Vector2(30.0f, 30.0f) );
  scrollable.ScrollCompletedSignal().Connect(&callback, &ScrollableSignalHandler::Callback);

  DALI_CHECK_FAIL(!callback.GetCalls(), "Scrollable::ScrollCompletedSignal() is failed." );

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliScrollableConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliScrollableConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliScrollableCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliScrollableOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliScrollableOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliScrollableDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliScrollableDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableSetIsOvershootEnabledP
 * @since_tizen         2.4
 * @description 	check for correctness of api SetOvershootEnabled
 */

int UtcDaliScrollableSetIsOvershootEnabledP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SET_IS_OVERSHOOT_ENABLED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableSetGetOvershootEffectColorP
 * @since_tizen         2.4
 * @description         Check for correctness of api GetOvershootEnabled
 */

int UtcDaliScrollableSetGetOvershootEffectColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SET_GET_OVERSHOOT_EFFECT_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableSetGetOvershootAnimationSpeedP
 * @since_tizen         2.4
 * @description         Check for correctness of api GetOvershootAnimationSpeed
 */

int UtcDaliScrollableSetGetOvershootAnimationSpeedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SET_GET_OVER_SHOOT_ANIMATION_SPEED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableScrollStartedSignalP
 * @since_tizen         2.4
 * @description         Checks ScrollStartedSignal signal
 */

int UtcDaliScrollableScrollStartedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SCROLL_STARTED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableScrollUpdatedSignalP
 * @since_tizen         2.4
 * @description         Checks ScrollUpdatedSignal signal
 */

int UtcDaliScrollableScrollUpdatedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SCROLL_UPDATED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollableScrollCompletedSignalP
 * @since_tizen         2.4
 * @description         Checks ScrollCompletedSignal signal
 */

int UtcDaliScrollableScrollCompletedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Scrollable_TestApp testApp( application, SCROLLABLE_SCROLL_COMPLETED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}
