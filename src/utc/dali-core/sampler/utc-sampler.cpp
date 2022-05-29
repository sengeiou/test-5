#include "utc-sampler-common.h"


extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


void utc_sampler_startup(void)
{
  test_return_value = 0;
}

void utc_sampler_cleanup(void)
{

}


void SamplerConstructorAndNew();
void SamplerDownCastP();
void SamplerDownCastN();
void SamplerAssignmentOperator();

namespace
{
  enum TEST_CASES_LIST_SAMPLER
  {
    SAMPLER_CONSTRUCTOR_AND_NEW,
    SAMPLER_DOWN_CAST_POSITIVE,
    SAMPLER_DOWN_CAST_NEGATIVE,
    SAMPLER_ASSIGNMENT_OPERATOR,
  };

  struct Sampler_TestApp : public ConnectionTracker
  {
    Sampler_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Sampler_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Sampler_TestApp::Tick );
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
        case SAMPLER_CONSTRUCTOR_AND_NEW:
        SamplerConstructorAndNew();
        break;
        case SAMPLER_DOWN_CAST_POSITIVE:
        SamplerDownCastP();
        break;
        case SAMPLER_DOWN_CAST_NEGATIVE:
        SamplerDownCastN();
        break;
        case SAMPLER_ASSIGNMENT_OPERATOR:
        SamplerAssignmentOperator();
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

void SamplerConstructorAndNew()
{
  Sampler sampler;
  DALI_CHECK_FAIL( sampler, "Sampler constructor failed" );

  sampler = Sampler::New();
  DALI_CHECK_FAIL( !sampler, "Sampler::New failed" );

  DaliLog::PrintPass();
}

void SamplerDownCastP()
{
  Sampler sampler = Sampler::New();

  BaseHandle handle( sampler );
  Sampler sampler2 = Sampler::DownCast( handle );
  DALI_CHECK_FAIL( !sampler2, "Sampler::DownCast failed" );

  DaliLog::PrintPass();
}

void SamplerDownCastN()
{
  Handle handle = Handle::New();
  Sampler sampler = Sampler::DownCast( handle );

  DALI_CHECK_FAIL( sampler, "Sampler::DownCast Negative test failed" );

  DaliLog::PrintPass();
}

void SamplerAssignmentOperator()
{
  Sampler sampler1 = Sampler::New();
  Sampler sampler2 = Sampler::New();
  DALI_CHECK_FAIL( ! ( sampler1 != sampler2 ), "Sampler::operator= test failed" );

  sampler2 = sampler1;
  DALI_CHECK_FAIL( ! ( sampler1 == sampler2 ), "Sampler::operator= test failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcSamplerConstructorAndNew
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works
 */
int UtcSamplerConstructorAndNew(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Sampler_TestApp testApp( application, SAMPLER_CONSTRUCTOR_AND_NEW);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcSamplerDownCastP
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcSamplerDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Sampler_TestApp testApp( application, SAMPLER_DOWN_CAST_POSITIVE);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcSamplerAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcSamplerAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Sampler_TestApp testApp( application, SAMPLER_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcSamplerDownCastN
 * @since_tizen       3.0
 * @description       Check DownCast
 */
int UtcSamplerDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  Sampler_TestApp testApp( application, SAMPLER_DOWN_CAST_NEGATIVE);
  application.MainLoop();
  return test_return_value;
}

