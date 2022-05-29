#include "utc-dali-sync-image-loader-common.h"

//& set: SyncImageLoader
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

// resolution: 50*50, pixel format: RGBA8888
const std::string gImage_50_RGBA = getResourceFullPath(TEST_IMAGE_50);
// resolution: 128*128, pixel format: RGB888
const std::string gImage_128_RGB = getResourceFullPath(TEST_IMAGE_128);

namespace
{

void VerifyLoad( PixelData pixelData, uint32_t width, uint32_t height )
{
  DALI_CHECK_FAIL( !pixelData, "SyncImageLoad::Load() is failed." );
  DALI_CHECK_FAIL( pixelData.GetWidth() != width, "SyncImageLoad::GetWidth() is failed." );
  DALI_CHECK_FAIL( pixelData.GetHeight() != height, "SyncImageLoad::GetHeight() is failed." );
}

} // anonymous namespace


/**
 * @function            utc_Dali_SyncImageLoader_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_SyncImageLoader_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_SyncImageLoader_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_SyncImageLoader_cleanup(void)
{

}

void SyncImageLoaderLoad();
void SyncImageLoaderLoadWithDimensions();
void SyncImageLoaderLoadWithAllOptions();

namespace
{
  enum TEST_CASES_LIST_SYNC_IMAGE_LOADER
  {
    SYNC_IMAGE_LOADER_LOAD,
    SYNC_IMAGE_LOADER_LOAD_WITH_DIMENSIONS,
    SYNC_IMAGE_LOADER_LOAD_WITH_ALL_OPTIONS,
  };

  struct SyncImageLoader_TestApp : public ConnectionTracker
  {
    SyncImageLoader_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &SyncImageLoader_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &SyncImageLoader_TestApp::Tick );
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
        case SYNC_IMAGE_LOADER_LOAD:
          SyncImageLoaderLoad();
          break;

        case SYNC_IMAGE_LOADER_LOAD_WITH_DIMENSIONS:
          SyncImageLoaderLoadWithDimensions();
          break;

        case SYNC_IMAGE_LOADER_LOAD_WITH_ALL_OPTIONS:
          SyncImageLoaderLoadWithAllOptions();
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


void SyncImageLoaderLoad()
{
  PixelData pixelData = Toolkit::SyncImageLoader::Load( gImage_50_RGBA );

  DALI_CHECK_FAIL( !pixelData , "SyncImageLoader::Load() is failed" );

  DaliLog::PrintPass();
}

void SyncImageLoaderLoadWithDimensions()
{
  PixelData pixelData = Toolkit::SyncImageLoader::Load( gImage_50_RGBA, ImageDimensions( 25, 25 ) );

  VerifyLoad( pixelData, 25u, 25u );

  DaliLog::PrintPass();
}

void SyncImageLoaderLoadWithAllOptions()
{
  PixelData pixelData = Toolkit::SyncImageLoader::Load( gImage_128_RGB, ImageDimensions( 100, 100 ), FittingMode::SCALE_TO_FILL, SamplingMode::BOX_THEN_LINEAR, true );

  VerifyLoad( pixelData, 100u, 100u );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliSyncImageLoaderLoad
 * @since_tizen         3.0
 * @description         Checks correct Load of SyncImageLoader
 */

int UtcDaliSyncImageLoaderLoad(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  SyncImageLoader_TestApp testApp( application, SYNC_IMAGE_LOADER_LOAD );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSyncImageLoaderLoadWithDimensions
 * @since_tizen         3.0
 * @description         Check for Load with Dimensions of SyncImageLoader
 */

int UtcDaliSyncImageLoaderLoadWithDimensions(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  SyncImageLoader_TestApp testApp( application, SYNC_IMAGE_LOADER_LOAD_WITH_DIMENSIONS );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSyncImageLoaderLoadWithAllOptions
 * @since_tizen         3.0
 * @description         Checks for Load with all parameters of SyncImageLoader
 */

int UtcDaliSyncImageLoaderLoadWithAllOptions(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  SyncImageLoader_TestApp testApp( application, SYNC_IMAGE_LOADER_LOAD_WITH_ALL_OPTIONS );
  application.MainLoop();

  return test_return_value;
}
