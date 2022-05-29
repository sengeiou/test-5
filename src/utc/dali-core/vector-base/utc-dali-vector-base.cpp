#include "utc-dali-vector-base-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;
#define ZERO 0

//& set: Vector-Base

/**
 * @function      utc_Dali_VectorBase_startup
 * @description   Called before each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_VectorBase_startup(void)
{
  test_return_value = 0;
}

/**
 * @function      utc_Dali_VectorBase_cleanup
 * @description   Called after each test
 * @parameter     NA
 * @return        NA
 */
void utc_Dali_VectorBase_cleanup(void)
{
}

void VectorBaseCountP();
void VectorBaseSizeP();
void VectorBaseEmptyP();
void VectorBaseCapacityP();
void VectorBaseReleaseP();

namespace
{
  enum TEST_CASES_LIST_VECTOR_BASE
  {
    VECTOR_BASE_COUNT_P,
    VECTOR_BASE_SIZE_P,
    VECTOR_BASE_EMPTY_P,
    VECTOR_BASE_CAPACITY_P,
    VECTOR_BASE_RELEASE_P
  };

  struct VectorBase_TestApp : public ConnectionTracker
  {
    VectorBase_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &VectorBase_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &VectorBase_TestApp::Tick );
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
        case VECTOR_BASE_COUNT_P:
          VectorBaseCountP();
          break;

        case VECTOR_BASE_SIZE_P:
          VectorBaseSizeP();
          break;

        case VECTOR_BASE_EMPTY_P:
          VectorBaseEmptyP();
          break;

        case VECTOR_BASE_CAPACITY_P:
          VectorBaseCapacityP();
          break;

        case VECTOR_BASE_RELEASE_P:
          VectorBaseReleaseP();
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

void VectorBaseCountP()
{
  Vector< int > intvector;
  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );

  DALI_CHECK_FAIL( intvector.Count() != 3, "Count is failed.");

  DaliLog::PrintPass();
}

void VectorBaseSizeP()
{
  Vector< int > intvector;
  intvector.PushBack( 99 );
  intvector.PushBack( 11 );
  intvector.PushBack( 34 );

  DALI_CHECK_FAIL( intvector.Size() != 3, "Size is failed.");

  DaliLog::PrintPass();
}

void VectorBaseEmptyP()
{
  Vector< int > intvector;
  DALI_CHECK_FAIL( !intvector.Empty() , "Empty is failed. ");
  DaliLog::PrintPass();
}

void VectorBaseCapacityP()
{
  Vector< int > intvector;
  DALI_CHECK_FAIL( intvector.Capacity() != 0, "Capacity is failed.");

  intvector.Resize( 10u );
  DALI_CHECK_FAIL( intvector.Capacity() != static_cast<Dali::VectorBase::SizeType>(10) , "Capacity is failed.");
  DaliLog::PrintPass();
}

void VectorBaseReleaseP()
{
  Vector<unsigned int> vector;
  DALI_CHECK_FAIL( ZERO != vector.Count(), "Default constuctor is failed." );
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "Default Constructor is failed.");

  vector.PushBack( 1 );
  vector.PushBack( 2 );
  vector.PushBack( 3 );
  vector.PushBack( 4 );
  vector.PushBack( 5 );

  vector.Release();
  DALI_CHECK_FAIL( ZERO != vector.Capacity(), "Release is failed.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase      UtcDaliVectorBaseCountP
 * @since_tizen   2.4
 * @description   check if Count api works or not.
 */
int UtcDaliVectorBaseCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VectorBase_TestApp testApp( application, VECTOR_BASE_COUNT_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorBaseSizeP
 * @since_tizen   2.4
 * @description   check if Size api works or not.
 */
int UtcDaliVectorBaseSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VectorBase_TestApp testApp( application, VECTOR_BASE_SIZE_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorBaseEmptyP
 * @since_tizen   2.4
 * @description   check if Empty api works or not.
 */
int UtcDaliVectorBaseEmptyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VectorBase_TestApp testApp( application, VECTOR_BASE_EMPTY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorBaseCapacityP
 * @since_tizen   2.4
 * @description   check if Capacity api works or not.
 */
int UtcDaliVectorBaseCapacityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VectorBase_TestApp testApp( application, VECTOR_BASE_CAPACITY_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase      UtcDaliVectorBaseReleaseP
 * @since_tizen   2.4
 * @description   check if Release api works or not.
 */
int UtcDaliVectorBaseReleaseP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VectorBase_TestApp testApp( application, VECTOR_BASE_RELEASE_P);
  application.MainLoop();
  return test_return_value;
}
