#include "utc-dali-default-ruler-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: DefaultRuler

/**
 * @function            utc_Dali_DefaultRuler_startup
 * @description         Called before each test
 * @return              NA
 */

void utc_Dali_DefaultRuler_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_DefaultRuler_cleanup
 * @description         Called after each test
 * @return              NA
 */

void utc_Dali_DefaultRuler_cleanup(void)
{

}

void DefaultRulerConstructorP();
void DefaultRulerGetTotalPagesP();
void DefaultRulerSnapP();
void DefaultRulerGetPageFromPositionP();
void DefaultRulerGetPositionFromPageP();

namespace
{
  enum TEST_CASES_LIST_DEFAULT_RULER
  {
    DEFAULT_RULER_CONSTRUCTOR_P,
    DEFAULT_RULER_GET_TOTAL_PAGES_P,
    DEFAULT_RULER_SNAP_P,
    DEFAULT_RULER_GET_PAGE_FROM_POSITION_P,
    DEFAULT_RULER_GET_POSITION_FROM_PAGE_P
  };

  struct DefaultRuler_TestApp : public ConnectionTracker
  {
    DefaultRuler_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &DefaultRuler_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &DefaultRuler_TestApp::Tick );
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
        case DEFAULT_RULER_CONSTRUCTOR_P:
          DefaultRulerConstructorP();
          break;
        case DEFAULT_RULER_GET_TOTAL_PAGES_P:
          DefaultRulerGetTotalPagesP();
          break;
        case DEFAULT_RULER_SNAP_P:
          DefaultRulerSnapP();
          break;
        case DEFAULT_RULER_GET_PAGE_FROM_POSITION_P:
          DefaultRulerGetPageFromPositionP();
          break;
        case DEFAULT_RULER_GET_POSITION_FROM_PAGE_P:
          DefaultRulerGetPositionFromPageP();
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

void DefaultRulerConstructorP()
{
  RulerPtr ruler;
  DALI_CHECK_FAIL( ruler, "DefaultRuler constructor is failed." );

  DaliLog::PrintPass();
}

void DefaultRulerGetTotalPagesP()
{
  unsigned int uGetTotalpage = 0u;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL( !rulerX, "DefaultRuler new instance creation is failed." );

  uGetTotalpage = rulerX->GetTotalPages();
  //default ruler should have 1 total page;
  DALI_CHECK_FAIL( uGetTotalpage < 1, "GetTotalPages is failed." );

  DaliLog::PrintPass();
}

void DefaultRulerSnapP()
{
  const float fBIAS_SET = 0.0f, fSNAPX_SET = 50.0f, fMINVALUE = 0.0f, fMAXVALUE = 100.0f;
  float fSnapRet = -1.0f;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL( !rulerX, "DefaultRuler new instance creation is failed." );

  rulerX->SetDomain( RulerDomain(fMINVALUE, fMAXVALUE, true) );
  fSnapRet = rulerX->Snap(fSNAPX_SET, fBIAS_SET);

  DALI_CHECK_FAIL( fSnapRet != fSNAPX_SET, "Snap is failed." );

  DaliLog::PrintPass();
}

void DefaultRulerGetPageFromPositionP()
{
  unsigned int uGetPage = PAGE_SIZE;
  unsigned int uVolume = 0u, uSetPage = 1u;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f;
  float fPosition = 0.0f;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL( !rulerX, "DefaultRuler new instance creation is failed." );

  rulerX->SetDomain( RulerDomain(fMINVALUE, fMAXVALUE, true) );
  fPosition = rulerX->GetPositionFromPage(uSetPage, uVolume, true);
  uGetPage = rulerX->GetPageFromPosition(fPosition, true);

  //Compared with default value
  DALI_CHECK_FAIL( uGetPage == PAGE_SIZE, "GetPageFromPosition is failed." );

  DaliLog::PrintPass();
}

void DefaultRulerGetPositionFromPageP()
{
  unsigned int uVolume = PAGE_VOLUME, uSetpage =1u;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fMINPOS = 0.0f;
  float fPosition = -1.0f;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL( !rulerX, "DefaultRuler new instance creation is failed." );

  rulerX->SetDomain( RulerDomain(fMINVALUE, fMAXVALUE, true) );
  fPosition = rulerX->GetPositionFromPage(uSetpage, uVolume, true);

  DALI_CHECK_FAIL( fPosition < fMINPOS, "GetPositionFromPage is failed." );
  //IF Volume not changed and get default value
  DALI_CHECK_FAIL( uVolume == PAGE_VOLUME, "GetPositionFromPage is failed when volume do not get properly." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliDefaultRulerConstructorP
 * @since_tizen         2.4
 * @description         Creates an object for default ruler
 */

int UtcDaliDefaultRulerConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultRuler_TestApp testApp( application, DEFAULT_RULER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliDefaultRulerGetTotalPagesP
 * @since_tizen         2.4
 * @description         Returns the total number of pages within this Ruler.
 */

int UtcDaliDefaultRulerGetTotalPagesP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultRuler_TestApp testApp( application, DEFAULT_RULER_GET_TOTAL_PAGES_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliDefaultRulerSnapP
 * @since_tizen         2.4
 * @description         Snaps (x) in accordance to the ruler settings.
 */

int UtcDaliDefaultRulerSnapP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultRuler_TestApp testApp( application, DEFAULT_RULER_SNAP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliDefaultRulerGetPageFromPositionP
 * @since_tizen         2.4
 * @description         Gets page from Position
 */

int UtcDaliDefaultRulerGetPageFromPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultRuler_TestApp testApp( application, DEFAULT_RULER_GET_PAGE_FROM_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliDefaultRulerGetPositionFromPageP
 * @since_tizen         2.4
 * @description         Gets position from page
 */

int UtcDaliDefaultRulerGetPositionFromPageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  DefaultRuler_TestApp testApp( application, DEFAULT_RULER_GET_POSITION_FROM_PAGE_P );
  application.MainLoop();

  return test_return_value;
}
