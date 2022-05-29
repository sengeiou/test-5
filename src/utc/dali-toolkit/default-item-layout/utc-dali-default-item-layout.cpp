#include "utc-dali-default-item-layout-common.h"

//& set: DefaultItemlayout

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_DefaultItemLayout_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_DefaultItemLayout_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ItemLayout_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_DefaultItemLayout_cleanup(void)
{

}

void DefaultItemLayoutNewP();

namespace
{
  enum TEST_CASES_LIST_ITEM_LAYOUT
  {
    DEFAULT_ITEM_LAYOUT_NEW_P
  };

  struct DefaultItemLayout_TestApp : public ConnectionTracker
  {
    DefaultItemLayout_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &DefaultItemLayout_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &DefaultItemLayout_TestApp::Tick );
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
        case DEFAULT_ITEM_LAYOUT_NEW_P:
          DefaultItemLayoutNewP();
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

void DefaultItemLayoutNewP()
{
  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliDefaultItemLayoutNewP
 * @since_tizen         2.4
 * @description         Gets the Extension of Item Layout
 */

int UtcDaliDefaultItemLayoutNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultItemLayout_TestApp testApp( application, DEFAULT_ITEM_LAYOUT_NEW_P);
  application.MainLoop();

  return test_return_value;
}
