#include "utc-dali-async-image-loader-common.h"

//& set: AsyncImageLoader
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

// resolution: 34*34, pixel format: RGBA8888
const std::string gImage_34_RGBA = getResourceFullPath(TEST_IMAGE_34);
// resolution: 50*50, pixel format: RGBA8888
const std::string gImage_50_RGBA = getResourceFullPath(TEST_IMAGE_50);
// resolution: 128*128, pixel format: RGB888
const std::string gImage_128_RGB = getResourceFullPath(TEST_IMAGE_128);

namespace
{
// for testing the ImageLoadedSignal
class ImageLoadedSignalVerifier : public ConnectionTracker
{
public:

  ImageLoadedSignalVerifier()
  : mCount( 0 )
  {}

  virtual ~ImageLoadedSignalVerifier()
  {}

  void ImageLoaded( uint32_t id, PixelData pixelData )
  {
    mIDs.push_back( id );
    mPixelDataList.push_back( pixelData );
    mCount++;
  }

  int LoadedImageCount()
  {
    return mCount;
  }

  bool Verify( uint32_t id, uint32_t width, uint32_t height )
  {
    int size = mIDs.size();
    for( int i = 0; i<size; i++  )
    {
      if( mIDs[i] == id )
      {
        return mPixelDataList[i].GetWidth() == width
            && mPixelDataList[i].GetHeight() == height;
      }
    }

    return false;
  }

private:

  int mCount;

  std::vector<uint32_t> mIDs;
  std::vector<PixelData> mPixelDataList;
};


} // anonymous namespace



/**
 * @function            utc_Dali_AsyncImageLoader_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AsyncImageLoader_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_AsyncImageLoader_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AsyncImageLoader_cleanup(void)
{

}

void AsyncImageLoaderConstructorP();
void AsyncImageLoaderCopyConstructorP();
void AsyncImageLoaderDestructorP();
void AsyncImageLoaderNewP();
void AsyncImageLoaderOperatorAssignmentP();
void AsyncImageLoaderDowncastP();
void AsyncImageLoaderDowncastN();
void AsyncImageLoaderLoadAndLoadedSignal( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id );
void AsyncImageLoaderCancel( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id );
void AsyncImageLoaderCancelAll();

void VTAsyncImageLoaderLoadAndLoadedSignal001( ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id );
void VTAsyncImageLoaderCancel001( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id );

namespace
{
  enum TEST_CASES_LIST_ASYNC_IMAGE_LOADER
  {
    ASYNC_IMAGE_LOADER_CONSTRUCTOR_P,
    ASYNC_IMAGE_LOADER_COPY_CONSTRUCTOR_P,
    ASYNC_IMAGE_LOADER_DESTRUCTOR_P,
    ASYNC_IMAGE_LOADER_NEW_P,
    ASYNC_IMAGE_LOADER_OPERATOR_ASSIGNMENT_P,
    ASYNC_IMAGE_LOADER_DOWNCAST_P,
    ASYNC_IMAGE_LOADER_DOWNCAST_N,
    ASYNC_IMAGE_LOADER_LOAD_AND_LOADED_SIGNAL,
    ASYNC_IMAGE_LOADER_CANCEL,
    ASYNC_IMAGE_LOADER_CANCEL_ALL,
  };

  struct AsyncImageLoader_TestApp : public ConnectionTracker
  {
    AsyncImageLoader_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &AsyncImageLoader_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( 1000 );
      mTimer.TickSignal().Connect( this, &AsyncImageLoader_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }
      VerdictTest();
      if(test_return_value==TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
      }
      return true;
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case ASYNC_IMAGE_LOADER_CONSTRUCTOR_P:
          AsyncImageLoaderConstructorP();
          break;

        case ASYNC_IMAGE_LOADER_COPY_CONSTRUCTOR_P:
          AsyncImageLoaderCopyConstructorP();
          break;

        case ASYNC_IMAGE_LOADER_DESTRUCTOR_P:
          AsyncImageLoaderDestructorP();
          break;

        case ASYNC_IMAGE_LOADER_NEW_P:
          AsyncImageLoaderNewP();
          break;

        case ASYNC_IMAGE_LOADER_OPERATOR_ASSIGNMENT_P:
          AsyncImageLoaderOperatorAssignmentP();
          break;

        case ASYNC_IMAGE_LOADER_DOWNCAST_P:
          AsyncImageLoaderDowncastP();
          break;

        case ASYNC_IMAGE_LOADER_DOWNCAST_N:
          AsyncImageLoaderDowncastN();
          break;

        case ASYNC_IMAGE_LOADER_LOAD_AND_LOADED_SIGNAL:
          AsyncImageLoaderLoadAndLoadedSignal( mAsyncImageLoader, mLoadedSignalVerifier, mIDs );
          break;

        case ASYNC_IMAGE_LOADER_CANCEL:
          AsyncImageLoaderCancel( mAsyncImageLoader, mLoadedSignalVerifier, mIDs );
          break;

        case ASYNC_IMAGE_LOADER_CANCEL_ALL:
          AsyncImageLoaderCancelAll();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case ASYNC_IMAGE_LOADER_LOAD_AND_LOADED_SIGNAL:
          VTAsyncImageLoaderLoadAndLoadedSignal001( mLoadedSignalVerifier, mIDs );
          mTimer.Stop();
          mApplication.Quit();
          break;

        case ASYNC_IMAGE_LOADER_CANCEL:
          VTAsyncImageLoaderCancel001( mAsyncImageLoader, mLoadedSignalVerifier, mIDs );
          mTimer.Stop();
          mApplication.Quit();
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
    AsyncImageLoader mAsyncImageLoader;
    ImageLoadedSignalVerifier mLoadedSignalVerifier;
    std::vector<uint32_t> mIDs;
  };

} // unnamed namespace


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/

void AsyncImageLoaderConstructorP()
{
  AsyncImageLoader loader;
  DALI_CHECK_FAIL( loader, "AsyncImageLoader Default Contructor is failed." );

  DaliLog::PrintPass();
}

void AsyncImageLoaderNewP()
{
  AsyncImageLoader loader = AsyncImageLoader::New();
  DALI_CHECK_FAIL( !loader, "AsyncImageLoader::New() is failed." );

  DaliLog::PrintPass();
}

void AsyncImageLoaderCopyConstructorP()
{
  AsyncImageLoader loader = AsyncImageLoader::New();
  DALI_CHECK_FAIL( !loader, "AsyncImageLoader::New() is failed." );

  AsyncImageLoader copyAsyncImageLoader( loader );
  DALI_CHECK_FAIL( loader != copyAsyncImageLoader, "Copy Constructor do not work properly." );

  DaliLog::PrintPass();
}

void AsyncImageLoaderDestructorP()
{
  AsyncImageLoader* loader = new AsyncImageLoader();
  delete loader;

  DALI_CHECK_FAIL( loader, "Destructor do not work properly." );
  DaliLog::PrintPass();
}

void AsyncImageLoaderOperatorAssignmentP()
{
  AsyncImageLoader loader = AsyncImageLoader::New();
  DALI_CHECK_FAIL( !loader, "AsyncImageLoader::New() is failed." );

  AsyncImageLoader* operatorAsyncImageLoader = &loader;
  DALI_CHECK_FAIL( operatorAsyncImageLoader == NULL, "AsyncImageLoader Assignment is Failed.");

  DaliLog::PrintPass();
}

void AsyncImageLoaderDowncastP()
{
  AsyncImageLoader loader = AsyncImageLoader::New();
  DALI_CHECK_FAIL(!loader, "AsyncImageLoader::New() is failed.");

  BaseHandle handleAsyncImageLoader;
  handleAsyncImageLoader = loader;

  AsyncImageLoader downCastAsyncImageLoader = AsyncImageLoader::DownCast( handleAsyncImageLoader );

  DALI_CHECK_FAIL( !downCastAsyncImageLoader, "downCastAsyncImageLoader is not valid object." );
  DALI_CHECK_FAIL( loader != downCastAsyncImageLoader, "downCastAsyncImageLoader is failed to match with loader." );

  DaliLog::PrintPass();
}

void AsyncImageLoaderDowncastN()
{
  BaseHandle unInitializedObject;

  AsyncImageLoader downCastAsyncImageLoader = AsyncImageLoader::DownCast( unInitializedObject );
  DALI_CHECK_FAIL( downCastAsyncImageLoader, "AsyncImageLoader handle is not empty." );

  DaliLog::PrintPass();
}

void AsyncImageLoaderLoadAndLoadedSignal( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id )
{
  loader = AsyncImageLoader::New();

  loader.ImageLoadedSignal().Connect( &verifier, &ImageLoadedSignalVerifier::ImageLoaded );

  loader.Load( gImage_34_RGBA );
  id.push_back( loader.Load( gImage_50_RGBA, ImageDimensions( 25, 25 ) ) );
  id.push_back( loader.Load( gImage_128_RGB, ImageDimensions( 100, 100 ), FittingMode::SCALE_TO_FILL, SamplingMode::BOX_THEN_LINEAR, true ) );
}

void VTAsyncImageLoaderLoadAndLoadedSignal001( ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id )
{
  DALI_CHECK_FAIL( verifier.LoadedImageCount() != 3, "AsyncImageLoader count is failed" );
  DALI_CHECK_FAIL( !verifier.Verify( id[0], 25, 25 ), "AsyncImageLoader Load is failed" );
  DALI_CHECK_FAIL( !verifier.Verify( id[1], 100, 100 ), "AsyncImageLoader Load is failed" );

  DaliLog::PrintPass();
}

void AsyncImageLoaderCancel( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id )
{
  loader = AsyncImageLoader::New();

  loader.ImageLoadedSignal().Connect( &verifier, &ImageLoadedSignalVerifier::ImageLoaded );

  id.push_back( loader.Load( gImage_34_RGBA, ImageDimensions( 34, 34 ) ) );
  id.push_back( loader.Load( gImage_50_RGBA, ImageDimensions( 25, 25 ) ) );
  id.push_back( loader.Load( gImage_128_RGB, ImageDimensions( 100, 100 ), FittingMode::SCALE_TO_FILL, SamplingMode::BOX_THEN_LINEAR, true ) );
}

void VTAsyncImageLoaderCancel001( AsyncImageLoader& loader, ImageLoadedSignalVerifier& verifier, std::vector<uint32_t>& id )
{
  DALI_CHECK_FAIL( verifier.LoadedImageCount() != 3, "AsyncImageLoader count is failed" );

  DALI_CHECK_FAIL( loader.Cancel( id[0] ), "AsyncImageLoader Cancel is failed" ); // Cannot cancel a task that is already implemeted

  DALI_CHECK_FAIL( !verifier.Verify( id[0], 34, 34 ), "AsyncImageLoader Load is failed" );   // first image is loaded
  DALI_CHECK_FAIL( !verifier.Verify( id[1], 25, 25 ), "AsyncImageLoader Load is failed" );   // second image is loaded
  DALI_CHECK_FAIL( !verifier.Verify( id[2], 100, 100 ), "AsyncImageLoader Load is failed" ); // third image is loaded

  DaliLog::PrintPass();
}

void AsyncImageLoaderCancelAll(void)
{
  AsyncImageLoader loader = AsyncImageLoader::New();

  // Test that it is safe to call CancelAll even there is no loading task requested.
  try
  {
    loader.CancelAll();
  }
  catch(Dali::DaliException& e)
  {
    LOG_E( "AsyncImageLoader TC is failed with dali exception." );
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliAsyncImageLoaderConstructorP
 * @since_tizen         3.0
 * @description         Checks correct creation of an object
 */

int UtcDaliAsyncImageLoaderConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderCopyConstructorP
 * @since_tizen         3.0
 * @description         Copy constructor to AsyncImageLoader.
 */

int UtcDaliAsyncImageLoaderCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderNewP
 * @since_tizen         3.0
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliAsyncImageLoaderNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderOperatorAssignmentP
 * @since_tizen         3.0
 * @description         Assignment operator.Changes this handle to point to another real object.
 */

int UtcDaliAsyncImageLoaderOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderDowncastP
 * @since_tizen         3.0
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliAsyncImageLoaderDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderDowncastN
 * @since_tizen         3.0
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliAsyncImageLoaderDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderLoadAndLoadedSignal
 * @since_tizen         3.0
 * @description         Check for Load and LoadedSignal of AsyncImageLoader
 */

int UtcDaliAsyncImageLoaderLoadAndLoadedSignal(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_LOAD_AND_LOADED_SIGNAL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderCancel
 * @since_tizen         3.0
 * @description         Check for AsyncImageLoader Cancel
 */

int UtcDaliAsyncImageLoaderCancel(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_CANCEL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAsyncImageLoaderCancelAll
 * @since_tizen         3.0
 * @description         Check for AsyncImageLoader CancelAll
 */

int UtcDaliAsyncImageLoaderCancelAll(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AsyncImageLoader_TestApp testApp( application, ASYNC_IMAGE_LOADER_CANCEL_ALL );
  application.MainLoop();

  return test_return_value;
}
