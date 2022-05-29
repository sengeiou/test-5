#include "utc-pixeldata-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: PixelData

void utc_pixeldata_startup(void)
{
  test_return_value = 0;
}

void utc_pixeldata_cleanup(void)
{

}

void PixelDataAssignmentOperator();
void PixelDataAllMethods();


namespace
{
  enum TEST_CASES_LIST_PIXELDATA
  {
    PIXELDATA_ASSIGNMENT_OPERATOR,
    PIXELDATA_ALL_METHODS,
  };

  struct PixelData_TestApp : public ConnectionTracker
  {
    PixelData_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &PixelData_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &PixelData_TestApp::Tick );
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
      case PIXELDATA_ASSIGNMENT_OPERATOR:
      PixelDataAssignmentOperator();
      break;
      case PIXELDATA_ALL_METHODS:
      PixelDataAllMethods();
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

static PixelData CreatePixelData()
{
  unsigned int width = 10u;
  unsigned int height = 10u;
  unsigned int bufferSize = width*height*Pixel::GetBytesPerPixel( Pixel::RGB888 );

  unsigned char* buffer= reinterpret_cast<unsigned char*>( malloc( bufferSize ) );
  PixelData pixelData = PixelData::New( buffer, bufferSize, width, height, Pixel::RGB888, PixelData::FREE );

  return pixelData;
}

void PixelDataAssignmentOperator()
{
  PixelData pixelData1 = CreatePixelData();
  PixelData pixelData2 = CreatePixelData();
  DALI_CHECK_FAIL( ! ( pixelData1 != pixelData2 ), "PixelData::operator= test failed" );

  pixelData2 = pixelData1;
  DALI_CHECK_FAIL( ! ( pixelData1 == pixelData2 ), "PixelData::operator= test failed" );

  DaliLog::PrintPass();
}

void PixelDataAllMethods()
{
  PixelData pixeldata;
  DALI_CHECK_FAIL( pixeldata, "PixelData constructor failed" );

  unsigned int width = 10u;
  unsigned int height = 10u;
  unsigned int bufferSize = width*height*Pixel::GetBytesPerPixel( Pixel::RGB888 );

  unsigned char* buffer= reinterpret_cast<unsigned char*>( malloc( bufferSize ) );
  PixelData pixelData = PixelData::New( buffer, bufferSize, width, height, Pixel::RGB888, PixelData::FREE );

  DALI_CHECK_FAIL( ! pixelData, "PixelData::New failed" );
  DALI_CHECK_FAIL( ! ( pixelData.GetWidth() == width ), "PixelData::GetWidth failed" );
  DALI_CHECK_FAIL( ! ( pixelData.GetHeight() == height ),"PixelData::GetHeight failed"  );
  DALI_CHECK_FAIL( ! ( pixelData.GetPixelFormat() == Pixel::RGB888 ), "PixelData::GetPixelFormat failed" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase          UtcPixelDataAssignmentOperator
 * @since_tizen       3.0
 * @description       Check assignment operator
 */
int UtcPixelDataAssignmentOperator(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PixelData_TestApp testApp( application, PIXELDATA_ASSIGNMENT_OPERATOR);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase          UtcPixelDataAllMethods
 * @since_tizen       3.0
 * @description       Check whether the default constructor and New method works and all the getters
 */
int UtcPixelDataAllMethods(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  PixelData_TestApp testApp( application, PIXELDATA_ALL_METHODS);
  application.MainLoop();
  return test_return_value;
}

