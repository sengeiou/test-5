#include "utc-dali-ruler-common.h"

//& set: Ruler

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Ruler_startup
 * @description         Called before each test
 * @return              NA
 */

void utc_Dali_Ruler_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Ruler_cleanup
 * @description         Called after each test
 * @return              NA
 */

void utc_Dali_Ruler_cleanup(void)
{

}

void RulerConstructorP();
void RulerSnapP();
void RulerGetPositionFromPageP();
void RulerGetPageFromPositionP();
void RulerGetTotalPagesP();
void RulerGetExtensionP();
void RulerGetTypeWithReturnEnumFreeP();
void RulerGetTypeWithReturnEnumFixedP();
void RulerEnableIsEnableP();
void RulerDisableDomainP();
void RulerSetGetDomainP();
void RulerClampP();
void RulerSnapAndClampWithClampStateP();
void RulerSnapAndClampP();

namespace
{
  enum TEST_CASES_LIST_RULER
  {
    RULER_CONSTRUCTOR_P,
    RULER_SNAP_P,
    RULER_GET_TOTAL_PAGES_P,
    RULER_GET_POSITION_FROM_PAGE_P,
    RULER_GET_PAGE_FROM_POSITION_P,
    RULER_GET_EXTENSION_P,
    RULER_GET_TYPE_WITH_RETURN_ENUM_FREE_P,
    RULER_GET_TYPE_WITH_RETURN_ENUM_FIXED_P,
    RULER_ENABLE_IS_ENABLE_P,
    RULER_SET_GET_DOMAIN_P,
    RULER_DISABLE_DOMAIN_P,
    RULER_CLAMP_P,
    RULER_SNAP_AND_CLAMP_WITH_CLAMP_STATE_P,
    RULER_SNAP_AND_CLAMP_P
  };

  struct Ruler_TestApp : public ConnectionTracker
  {
    Ruler_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Ruler_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Ruler_TestApp::Tick );
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
        case RULER_CONSTRUCTOR_P:
          RulerConstructorP();
          break;
        case RULER_GET_TOTAL_PAGES_P:
          RulerGetTotalPagesP();
          break;
        case RULER_GET_POSITION_FROM_PAGE_P:
          RulerGetPositionFromPageP();
          break;
        case RULER_GET_PAGE_FROM_POSITION_P:
          RulerGetPageFromPositionP();
          break;
        case RULER_SNAP_P:
          RulerSnapP();
          break;
        case RULER_GET_EXTENSION_P:
          RulerGetExtensionP();
          break;
        case RULER_ENABLE_IS_ENABLE_P:
          RulerEnableIsEnableP();
          break;
        case RULER_SET_GET_DOMAIN_P:
          RulerSetGetDomainP();
          break;
        case RULER_DISABLE_DOMAIN_P:
          RulerDisableDomainP();
          break;
        case RULER_GET_TYPE_WITH_RETURN_ENUM_FREE_P:
          RulerGetTypeWithReturnEnumFreeP();
          break;
        case RULER_GET_TYPE_WITH_RETURN_ENUM_FIXED_P:
          RulerGetTypeWithReturnEnumFixedP();
          break;
        case RULER_CLAMP_P:
          RulerClampP();
          break;
        case RULER_SNAP_AND_CLAMP_WITH_CLAMP_STATE_P:
          RulerSnapAndClampWithClampStateP();
          break;
        case RULER_SNAP_AND_CLAMP_P:
          RulerSnapAndClampP();
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

void RulerConstructorP()
{
  RulerPtr ruler;
  DALI_CHECK_FAIL( ruler, "Ruler Initialization is failed." );

  DaliLog::PrintPass();
}

void RulerGetTotalPagesP()
{
  unsigned int uGetTotalpage = PAGE_SIZE1, uSetTotalpages = 0u;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fGetDomainSize = 0.0f;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit1(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fGetDomainSize = ruler->GetDomain().GetSize();
  uSetTotalpages = fGetDomainSize / fSETRULER;  //Total Pages will be the Ruler size and divided by Ruler Spacing(fSetRuler)

  uGetTotalpage = ruler->GetTotalPages();
  DALI_CHECK_FAIL( uGetTotalpage != uSetTotalpages, "GetTotalPages is failed." );

  DaliLog::PrintPass();
}

void RulerGetPositionFromPageP()
{
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fPosition = -1.0f;
  unsigned int uVolume = PAGE_VOLUME1, uSetVol = 1u;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit1(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fPosition = ruler->GetPositionFromPage(uSetVol, uVolume, true);

  DALI_CHECK_FAIL( fPosition != fMINVALUE, "GetPositionFromPage is failed." );
  DALI_CHECK_FAIL( uVolume != uSetVol, "GetPositionFromPage is failed when volume is not get properly." );

  DaliLog::PrintPass();
}

void RulerGetPageFromPositionP()
{
  unsigned int uVolume = 0u;
  unsigned int uGetPage = PAGE_SIZE1;
  const float fMINVALUE = 10.0f, fMAXVALUE = 90.0f, fSETRULER = 50.0f;
  float fPosition = 0.0f;

  RulerPtr rulerX;
  DALI_CHECK_FAIL( !FixedRulerInit1(rulerX, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fPosition = rulerX->GetPositionFromPage(1, uVolume, true);
  uGetPage = rulerX->GetPageFromPosition(fPosition, true);

  DALI_CHECK_FAIL( uGetPage == PAGE_SIZE1, "GetPageFromPosition is failed." );

  DaliLog::PrintPass();
}

void RulerSnapP()
{
  const float fBIASSET = 0.0f, fMINVALUE = 0.0f, fMAXVALUE = 400.0f, fSETRULER = 50.0f;
  float fSnapRet = -1.0f;

  RulerPtr ruler;
  DALI_CHECK_FAIL( !FixedRulerInit1(ruler, fSETRULER, fMINVALUE, fMAXVALUE), "FixedRuler Initialization is failed." );

  fSnapRet = ruler->Snap(fSETRULER, fBIASSET);

  DALI_CHECK_FAIL( fSnapRet != fSETRULER, "GetPositionFromPage is failed." );

  DaliLog::PrintPass();
}

void RulerEnableIsEnableP()
{
  bool bIsEnable = false;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rulerX->Enable();

  bIsEnable=rulerX->IsEnabled();
  DALI_CHECK_FAIL(!bIsEnable, "Ruler IsEnabled is failed to retrieve the expected value.");

  rulerX->Disable();

  bIsEnable=rulerX->IsEnabled();
  DALI_CHECK_FAIL(bIsEnable, "Ruler IsEnabled is failed to retrieve the expected value.");

  DaliLog::PrintPass();
}

void RulerSetGetDomainP()
{
  bool bEnable = true ;
  float fGetDomain = 0.0f, fMinSize = 0.0f , fMaxSize = 100.0f ;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  fGetDomain = -1.0f;
  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );

  fGetDomain=rulerX->GetDomain().GetSize();
  DALI_CHECK_FAIL(fGetDomain != (fMaxSize-fMinSize), "SetDomain and get domain value mismatch error occured.");

  DaliLog::PrintPass();
}

void RulerDisableDomainP()
{
  bool bEnable = true ;
  float fGetDomain =0.0f, fMinSize = 0.0f , fMaxSize = 100.0f ;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rulerX->SetDomain( RulerDomain(fMinSize,fMaxSize, bEnable) );
  rulerX->DisableDomain();

  fGetDomain = rulerX->GetDomain().GetSize();
  // disabledomain sets rulerdomain to 1.0f
  DALI_CHECK_FAIL(fGetDomain != 1.0f, "Disable Domain is failed.");

  DaliLog::PrintPass();
}

void RulerGetTypeWithReturnEnumFreeP()
{
  Ruler::RulerType  rType;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rType = rulerX->GetType();
  DALI_CHECK_FAIL(rType != Ruler::Free, "gettype is failed to get expected value.");

  DaliLog::PrintPass();
}

void RulerGetTypeWithReturnEnumFixedP()
{
  Ruler::RulerType  rType;

  RulerPtr rulerX = new FixedRuler( 50.0f );
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rType=rulerX->GetType();
  DALI_CHECK_FAIL(rType != Ruler::Fixed, "gettype is failed to get expected value.");

  DaliLog::PrintPass();
}

void RulerClampP()
{
  bool bEnable = true ;
  float fClampRet =0.0f , fMinSize = 0.0f , fMaxSize = 100.0f ,fX = 200.0f , fLength = 0.0f , fScale = 1.0f ;
  float fClampVal = fMaxSize * fScale - fLength ;
  ClampState clamped;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );
  fClampRet=rulerX->Clamp(fX,fLength,fScale,clamped);

  DALI_CHECK_FAIL(fClampRet != fClampVal, "Clamp is failed.");
  DALI_CHECK_FAIL(clamped != ClampedToMax, "Clamp is failed when clamped state do not get properly.");

  fClampRet =0.0f;
  fClampRet=rulerX->Clamp(fX,fLength,fScale);
  DALI_CHECK_FAIL(fClampRet != fClampVal, "Clamp is failed.");

  DaliLog::PrintPass();
}

void RulerSnapAndClampWithClampStateP()
{
  float fClampRet = 0.0f , fMinVal = 0.0f, fMaxVal = 400.0f, fX = 430.0f , fBias = 0.5f , fLength = 0.0f , fScale = 1.0f ;
  ClampState clamped;

  RulerPtr rulerX = new FixedRuler( 50.0f );
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rulerX->SetDomain( RulerDomain(fMinVal, fMaxVal, true) );
  fClampRet=rulerX->SnapAndClamp(fX, fBias, fLength, fScale, clamped);

  // snap value out of  the range so api should return the max value
  DALI_CHECK_FAIL(fClampRet != fMaxVal, "SnapAndClamp is failed .");
  DALI_CHECK_FAIL(clamped != ClampedToMax, "SnapAndClamp is failed when clamped State is not get properly.");

  DaliLog::PrintPass();
}

void RulerSnapAndClampP()
{
  bool bEnable = true ;
  float fClampRet = 0.0f , fMinVal = 0.0f, fMaxVal = 400.0f , fSetRuler = 50.0f ,fX = 50.0f , fBias = 0.5f , fLength = 0.0f , fScale = 2.0f ;

  RulerPtr rulerX = new FixedRuler( fSetRuler);
  DALI_CHECK_FAIL(!rulerX, "Ruler is failed.");

  rulerX->SetDomain( RulerDomain(fMinVal, fMaxVal, bEnable) );
  fClampRet = rulerX->SnapAndClamp(fX,fBias, fLength , fScale );

  // snap value within the range so api should return the same value
  DALI_CHECK_FAIL(fClampRet != fX, "SnapAndClamp api do not works properly.");

  DaliLog::PrintPass();
}

void RulerGetExtensionP()
{
  RulerPtr rulerX = new FixedRuler( 50.0f );
  DALI_CHECK_FAIL( rulerX->GetExtension(), "GetExtension is falied." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliRulerConstructorP
 * @since_tizen         2.4
 * @description         Creates an object for default ruler
 */

int UtcDaliRulerConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerGetTotalPagesP
 * @since_tizen         2.4
 * @description         Returns the total number of pages within this Ruler
 */

int UtcDaliRulerGetTotalPagesP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_TOTAL_PAGES_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerGetPositionFromPageP
 * @since_tizen         2.4
 * @description         Returns position from page, based on whatever the ruler defines as a page
 */

int UtcDaliRulerGetPositionFromPageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_POSITION_FROM_PAGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerGetPageFromPositionP
 * @since_tizen         2.4
 * @description         Returns page from position, based on whatever the ruler defines as a position
 */

int UtcDaliRulerGetPageFromPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_PAGE_FROM_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerSnapP
 * @since_tizen         2.4
 * @description         Snaps (x) in accordance to the ruler settings.
 */

int UtcDaliRulerSnapP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_SNAP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerRulerGetExtensionP
 * @since_tizen         2.4
 * @description         Snaps (x) in accordance to the ruler settings.
 */

int UtcDaliRulerRulerGetExtensionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_EXTENSION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerEnableIsEnableP
 * @since_tizen         2.4
 * @description         Checks the Ruler enable or not.
 */

int UtcDaliRulerEnableIsEnableP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_ENABLE_IS_ENABLE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerSetGetDomainP
 * @since_tizen         2.4
 * @description         Sets and Gets Domain.
 */

int UtcDaliRulerSetGetDomainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_SET_GET_DOMAIN_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerDisableDomainP
 * @since_tizen         2.4
 * @description         Disables Domain (minimum/maximum extents for this axis).
 */
int UtcDaliRulerDisableDomainP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_DISABLE_DOMAIN_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerGetTypeWithReturnEnumFreeP
 * @since_tizen         2.4
 * @description         Gets the ruler type.
 */
int UtcDaliRulerGetTypeWithReturnEnumFreeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_TYPE_WITH_RETURN_ENUM_FREE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerGetTypeWithReturnEnumFixedP
 * @since_tizen         2.4
 * @description         Gets the ruler type.
 */

int UtcDaliRulerGetTypeWithReturnEnumFixedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_GET_TYPE_WITH_RETURN_ENUM_FIXED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerClampP
 * @since_tizen         2.4
 * @description         Clamps value (x) from (min) to (max).
 */

int UtcDaliRulerClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_CLAMP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerSnapAndClampWithClampStateP
 * @since_tizen         2.4
 * @description         Snaps and Clamps (x) in accordance to ruler settings.
 */

int UtcDaliRulerSnapAndClampWithClampStateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_SNAP_AND_CLAMP_WITH_CLAMP_STATE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerSnapAndClampP
 * @since_tizen         2.4
 * @description         Snaps and Clamps (x) in accordance to ruler settings.
 */

int UtcDaliRulerSnapAndClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Ruler_TestApp testApp( application, RULER_SNAP_AND_CLAMP_P );
  application.MainLoop();

  return test_return_value;
}
