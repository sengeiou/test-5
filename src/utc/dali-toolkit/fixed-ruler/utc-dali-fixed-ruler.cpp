#include "utc-dali-fixed-ruler-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: FixedRuler

/**
 * @function            utc_Dali_FixedRuler_startup
 * @description         Called before each test
 * @return              NA
 */

void utc_Dali_FixedRuler_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_FixedRuler_cleanup
 * @description         Called after each test
 * @return              NA
 */

void utc_Dali_FixedRuler_cleanup(void)
{

}

void FixedRulerConstructorP();
void FixedRulerGetTotalPagesP();
void FixedRulerGetPositionFromPageP();
void FixedRulerGetPageFromPositionP();
void FixedRulerSnapP();

namespace
{
  enum TEST_CASES_LIST_FIXED_RULER
  {
    FIXED_RULER_CONSTRUCTOR_P,
    FIXED_RULER_GET_TOTAL_PAGES_P,
    FIXED_RULER_GET_POSITION_FROM_PAGE_P,
    FIXED_RULER_GET_PAGE_FROM_POSITION_P,
    FIXED_RULER_SNAP_P
  };

  struct FixedRuler_TestApp : public ConnectionTracker
  {
    FixedRuler_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &FixedRuler_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &FixedRuler_TestApp::Tick );
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
        case FIXED_RULER_CONSTRUCTOR_P:
          FixedRulerConstructorP();
          break;
        case FIXED_RULER_GET_TOTAL_PAGES_P:
          FixedRulerGetTotalPagesP();
          break;
        case FIXED_RULER_GET_POSITION_FROM_PAGE_P:
          FixedRulerGetPositionFromPageP();
          break;
        case FIXED_RULER_GET_PAGE_FROM_POSITION_P:
          FixedRulerGetPageFromPositionP();
          break;
        case FIXED_RULER_SNAP_P:
          FixedRulerSnapP();
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

void FixedRulerConstructorP()
{
  unsigned int uGetTotalpage = PAGE_SIZE, uSetTotalpages = 0u;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fGetDomainSize = 0.0f;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  DaliLog::PrintPass();
}

void FixedRulerGetTotalPagesP()
{
  unsigned int uGetTotalpage = PAGE_SIZE, uSetTotalpages = 0u;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fGetDomainSize = 0.0f;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fGetDomainSize = ruler->GetDomain().GetSize();
  uSetTotalpages = fGetDomainSize / fSETRULER;  //Total Pages will be the Ruler size and divided by Ruler Spacing(fSetRuler)

  uGetTotalpage = ruler->GetTotalPages();
  DALI_CHECK_FAIL( uGetTotalpage != uSetTotalpages, "GetTotalPages is failed." );

  DaliLog::PrintPass();
}


void FixedRulerGetPositionFromPageP()
{
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fPosition = -1.0f;
  unsigned int uVolume = PAGE_VOLUME, uSetVol = 1u;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fPosition = ruler->GetPositionFromPage(uSetVol, uVolume, true);

  DALI_CHECK_FAIL( fPosition != fMINVALUE, "GetPositionFromPage is failed." );
  DALI_CHECK_FAIL( uVolume != uSetVol, "GetPositionFromPage is failed when volume is not get properly." );

  DaliLog::PrintPass();
}

void FixedRulerGetPageFromPositionP()
{
  unsigned int uVolume = 0u;
  unsigned int uGetPage = PAGE_SIZE;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fPosition = 0.0f;

  RulerPtr rulerX;
  DALI_CHECK_FAIL( !FixedRulerInit(rulerX, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fPosition = rulerX->GetPositionFromPage(1, uVolume, true);
  uGetPage = rulerX->GetPageFromPosition(fPosition, true);

  DALI_CHECK_FAIL( uGetPage == PAGE_SIZE, "GetPageFromPosition is failed." );

  DaliLog::PrintPass();
}

void FixedRulerSnapP()
{
  const float fBIASSET = 0.0f, fMINVALUE = 0.0f, fMAXVALUE = 400.0f, fSETRULER = 50.0f;
  float fSnapRet = -1.0f;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fSnapRet = ruler->Snap(fSETRULER, fBIASSET);

  DALI_CHECK_FAIL( fSnapRet != fSETRULER, "GetPositionFromPage is failed." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliFixedRulerConstructorP
 * @since_tizen         2.4
 * @description         Creates an object for default ruler
 */

int UtcDaliFixedRulerConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FixedRuler_TestApp testApp( application, FIXED_RULER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliFixedRulerGetTotalPagesP
 * @since_tizen         2.4
 * @description         Returns the total number of pages within this Ruler
 */

int UtcDaliFixedRulerGetTotalPagesP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FixedRuler_TestApp testApp( application, FIXED_RULER_GET_TOTAL_PAGES_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliFixedRulerGetPositionFromPageP
 * @since_tizen         2.4
 * @description         Returns position from page, based on whatever the ruler defines as a page
 */

int UtcDaliFixedRulerGetPositionFromPageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FixedRuler_TestApp testApp( application, FIXED_RULER_GET_POSITION_FROM_PAGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliFixedRulerGetPageFromPositionP
 * @since_tizen         2.4
 * @description         Returns page from position, based on whatever the ruler defines as a position
 */

int UtcDaliFixedRulerGetPageFromPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FixedRuler_TestApp testApp( application, FIXED_RULER_GET_PAGE_FROM_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliFixedRulerSnapP
 * @since_tizen         2.4
 * @description         Snaps (x) in accordance to the ruler settings.
 */

int UtcDaliFixedRulerSnapP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  FixedRuler_TestApp testApp( application, FIXED_RULER_SNAP_P );
  application.MainLoop();

  return test_return_value;
}
