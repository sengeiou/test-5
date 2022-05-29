#include "utc-dali-ruler-domain-common.h"

//& set: Rulerdomain

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_RulerDomain_startup
 * @description         Called before each test
 * @return              NA
 */

void utc_Dali_RulerDomain_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_RulerDomain_cleanup
 * @description         Called after each test
 * @return              NA
 */

void utc_Dali_RulerDomain_cleanup(void)
{

}
void RulerDomainConstructorP();
void RulerDomainGetSizeP();
void RulerDomainClampWithMinClampP();
void RulerDomainClampWithMaxClampP();

namespace
{
  enum TEST_CASES_LIST_RULER_DOMAIN
  {
    RULER_DOMAIN_CONSTRUCTOR_P,
    RULER_DOMAIN_GET_SIZE_P,
    RULER_DOMAIN_CLAMP_WITH_MIN_CLAMP_P,
    RULER_DOMAIN_CLAMP_WITH_MAX_CLAMP_P
  };

  struct RulerDomain_TestApp : public ConnectionTracker
  {
    RulerDomain_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &RulerDomain_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &RulerDomain_TestApp::Tick );
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
        case RULER_DOMAIN_CONSTRUCTOR_P:
          RulerDomainConstructorP();
          break;

        case RULER_DOMAIN_GET_SIZE_P:
          RulerDomainGetSizeP();
          break;

        case RULER_DOMAIN_CLAMP_WITH_MIN_CLAMP_P:
          RulerDomainClampWithMinClampP();
          break;

        case RULER_DOMAIN_CLAMP_WITH_MAX_CLAMP_P:
          RulerDomainClampWithMaxClampP();
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

void RulerDomainConstructorP()
{
  bool bEnable = true ;
  float fGetDomainSize= 0.0f, fMinSize = 0.00f, fMaxSize = 100.00f ;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler() is failed  .");

  fGetDomainSize = -1.0f;
  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );
  fGetDomainSize = rulerX->GetDomain().GetSize();

  DALI_CHECK_FAIL(fGetDomainSize != (fMaxSize-fMinSize), "RulerDomain is failed");

  DaliLog::PrintPass();
}

void RulerDomainGetSizeP()
{
  bool bEnable = true ;
  float fGetDomainSize= 0.0f, fMinSize = 0.00f, fMaxSize = 100.00f ;

  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler() is failed  .");

  fGetDomainSize = -1.0f;

  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );

  fGetDomainSize = rulerX->GetDomain().GetSize();

  DALI_CHECK_FAIL(fGetDomainSize != (fMaxSize-fMinSize), "Getsize is failed to get the rulerdomain value.");

  DaliLog::PrintPass();
}

void RulerDomainClampWithMinClampP()
{
  bool bEnable = true ;
  float fClampRet = 0.0f , fMinSize = 0.00f, fMaxSize = 100.00f ;
  float fX = -40.0f , fLength = 0.0f , fScale = 1.0f ;
  float fClampVal = fMinSize * fScale ; //for min clamp
  ClampState clamped;
  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler() is failed  .");

  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );

  fClampRet = -1.0f;

  fClampRet = rulerX->Clamp(fX,fLength,fScale,clamped);

  DALI_CHECK_FAIL(fClampRet != fClampVal, "Clamp is failed  .");
  DALI_CHECK_FAIL(clamped != ClampedToMin, "Clamp is failed when clamped state do not get properly.");

  fClampRet = -1.0f;
  fClampRet = rulerX->Clamp(fX,fLength,fScale);
  DALI_CHECK_FAIL(fClampRet != fClampVal, "Clamp is failed  .");

  DaliLog::PrintPass();
}

void RulerDomainClampWithMaxClampP()
{
  bool bEnable = true ;
  float fClampRet = 0.0f, fMinSize = 0.00f, fMaxSize = 100.00f ;
  float fX = 120.0f , fLength = 0.0f , fScale = 1.0f ;
  float fClampVal = fMaxSize * fScale - fLength; //for max clamp
  ClampState clamped;
  RulerPtr rulerX = new DefaultRuler();
  DALI_CHECK_FAIL(!rulerX, "Ruler() is failed  .");

  rulerX->SetDomain( RulerDomain(fMinSize, fMaxSize, bEnable) );

  fClampRet = -1.0f;

  fClampRet = rulerX->Clamp(fX,fLength,fScale,clamped);

  DALI_CHECK_FAIL(fClampRet != fClampVal, "Clamp is failed  .");
  DALI_CHECK_FAIL(clamped != ClampedToMax, "Clamp is failed when clamped state do not get properly.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliRulerDomainConstructorP
 * @since_tizen         2.4
 * @description         Creates an object for default ruler
 */

int UtcDaliRulerDomainConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RulerDomain_TestApp testApp( application, RULER_DOMAIN_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerDomainGetSizeP
 * @since_tizen         2.4
 * @description         Sets Ruler domain and Gets Domain Size
 */

int UtcDaliRulerDomainGetSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RulerDomain_TestApp testApp( application, RULER_DOMAIN_GET_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerDomainClampWithMinClampP
 * @since_tizen         2.4
 * @description         clamps ruler.
 */

int UtcDaliRulerDomainClampWithMinClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RulerDomain_TestApp testApp( application, RULER_DOMAIN_CLAMP_WITH_MIN_CLAMP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliRulerDomainClampWithMaxClampP
 * @since_tizen         2.4
 * @description         clamps ruler.
 */

int UtcDaliRulerDomainClampWithMaxClampP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  RulerDomain_TestApp testApp( application, RULER_DOMAIN_CLAMP_WITH_MAX_CLAMP_P );
  application.MainLoop();

  return test_return_value;
}
