#include "utc-dali-scroll-view-effect-common.h"

//& set: ScrollView
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ScrollViewEffect_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ScrollViewEffect_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ScrollViewEffect_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */


void utc_Dali_ScrollViewEffect_cleanup(void)
{

}

void ScrollViewEffectConstructorP();

namespace
{
  enum TEST_CASES_LIST_ITEM_LAYOUT
  {
    SCROLL_VIEW_EFFECT_CONSTRUCTOR_P
  };

  struct ScrollViewEffect_TestApp : public ConnectionTracker
  {
    ScrollViewEffect_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ScrollViewEffect_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ScrollViewEffect_TestApp::Tick );
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
        case SCROLL_VIEW_EFFECT_CONSTRUCTOR_P:
          ScrollViewEffectConstructorP();
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

void ScrollViewEffectConstructorP()
{
  ScrollView scrollView;
  DALI_CHECK_FAIL( scrollView, "ScrollView constructor is failed." );

  DaliLog::PrintPass();

}


/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliScrollViewEffectConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliScrollViewEffectConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollViewEffect_TestApp testApp( application, SCROLL_VIEW_EFFECT_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}



