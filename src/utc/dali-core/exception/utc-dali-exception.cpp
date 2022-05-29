#include "utc-dali-exception-common.h"

//& set: dali-exception

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Exception_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Exception_startup(void)
{
    test_return_value=0;
}

/**
 * @function            utc_Dali_Exception_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_Exception_cleanup(void)
{

}

void DaliExceptionDaliAssertMessage();

namespace
{
  enum TEST_CASES_LIST_DALI_EXCEPTION
  {
    DALI_EXCEPTION_DALI_ASSERT_MESSAGE,
  };

  struct Dali_Exception_TestApp : public ConnectionTracker
  {
    Dali_Exception_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Dali_Exception_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Dali_Exception_TestApp::Tick );
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
        case DALI_EXCEPTION_DALI_ASSERT_MESSAGE:
          DaliExceptionDaliAssertMessage();
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
void DaliExceptionDaliAssertMessage()
{
  std::string strLocation, strCondition;
  try
  {
    Dali::Actor actor;
    if( !actor )
    {
      strLocation.append("[TC: " + std::string(__FUNCTION__) + "]");
      strCondition.append("Invalid handle object of an actor." );
      Dali::DaliAssertMessage(strLocation.c_str(), strCondition.c_str());
      throw Dali::DaliException( strLocation.c_str(), strCondition.c_str() );
    }

    //@NOTE: Must not reach at this line if assert message is thrown properly
    LOG_E("Dali::DaliAssertMessage() is failed. Did not throw to dali exception reference.");
    test_return_value = TC_FAIL;
    return;
  }
  catch(DaliException& de)
  {
    if( std::string(de.location).empty() || std::string(de.location).compare(strLocation) != 0 )
    {
      LOG_E("Dali::DaliException() is failed. The Dali::DaliException::location property mismatches with what it was thrown.");
      strLocation.clear();
      strCondition.clear();
      test_return_value = TC_FAIL;
      return;
    }

    if( std::string(de.condition).empty() || std::string(de.condition).compare(strCondition) != 0 )
    {
      LOG_E("Dali::DaliException() is failed. The Dali::DaliException::condition property mismatches with what it was thrown.");
      strLocation.clear();
      strCondition.clear();
      test_return_value = TC_FAIL;
      return;
    }
  }
  catch(exception& e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali::DaliException() is failed. Did not catch by DaliException reference. Standard Exception Thrown: %s, at [LINE: %d]", e.what(), __LINE__);
    strLocation.clear();
    strCondition.clear();
    test_return_value = TC_FAIL;
    return;
  }
  catch(...)
  {
    LOG_E("Dali::DaliException() is failed. Did not catch by DaliException reference. Unknown error.");
    strLocation.clear();
    strCondition.clear();
    test_return_value = TC_FAIL;
    return;
  }
  strLocation.clear();
  strCondition.clear();
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase         UtcDaliExceptionDaliAssertMessage
 * @since_tizen      2.4
 * @description      Checks dali exception when it logs an assertion message.
 */
int UtcDaliExceptionDaliAssertMessage(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Dali_Exception_TestApp testApp( application, DALI_EXCEPTION_DALI_ASSERT_MESSAGE);
  application.MainLoop();
  return test_return_value;
}

