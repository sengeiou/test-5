#include "utc-dali-native-image-source-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function    utc_Dali_NativeImageSource_startup
 * @description Called before each test
 * @parameter   NA
 * @return      NA
 */


void utc_Dali_NativeImageSource_startup(void)
{
  test_return_value=0;
}

/**
 * @function    utc_Dali_NativeImageSource_cleanup
 * @description Called after each test
 * @parameter   NA
 * @return      NA
 */

void utc_Dali_NativeImageSource_cleanup(void)
{
}

void NativeImageSourceColorDepthDefaultP();
void NativeImageSourceColorDepth24P();
void NativeImageSourceColorDepth32P();
void NativeImageSourceGetNativeImageSourceP();
void NativeImageSourceGetNativeImageSourceN();
void NativeImageSourceCreateNativeImageSourceN();
void NativeImageSourceCreateNativeImageSourceP();
void NativeImageSourceNewAnyP();
void NativeImageSourceEncodeToFileP();
void NativeImageSourceGetPixelsN();
void NativeImageSourceGetPixelsP();
void NativeImageSourceSetSourceP();
void NativeImageSourceIsColorDepthSupportedP();

NativeImageSourcePtr CreateNativeImageSource(unsigned int, unsigned int);

namespace
{
  enum TEST_CASES_LIST_NATIVE_IMAGE_SOURCE
  {
    NATIVE_IMAGE_SOURCE_COLOR_DEPTH_DEFAULT_P,
    NATIVE_IMAGE_SOURCE_COLOR_DEPTH_24_P,
    NATIVE_IMAGE_SOURCE_COLOR_DEPTH_32_P,
    NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_P,
    NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_N,
    NATIVE_IMAGE_SOURCE_NEW_P,
    NATIVE_IMAGE_SOURCE_NEW_N,
    NATIVE_IMAGE_SOURCE_NEW_ANY_P,
    NATIVE_IMAGE_SOURCE_ENCODE_TO_FILE_P,
    NATIVE_IMAGE_SOURCE_GET_PIXELS_N,
    NATIVE_IMAGE_SOURCE_GET_PIXELS_P,
    NATIVE_IMAGE_SOURCE_SET_SOURCE_P,
    NATIVE_IMAGE_SOURCE_IS_COLOR_DEPTH_SUPPORTED_P,
  };

  struct NativeImageSource_TestApp : public ConnectionTracker
  {
    NativeImageSource_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &NativeImageSource_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &NativeImageSource_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      mTimer.Stop();
      ExcuteTest();
      mApplication.Quit();
      return true;
    }

    void ExcuteTest()
    {
      NativeImageSourcePtr nativeImageSource;
      switch (mTestCase)
      {
        case NATIVE_IMAGE_SOURCE_COLOR_DEPTH_DEFAULT_P:
          NativeImageSourceColorDepthDefaultP();
          break;

        case NATIVE_IMAGE_SOURCE_COLOR_DEPTH_24_P:
          NativeImageSourceColorDepth24P();
          break;

        case NATIVE_IMAGE_SOURCE_COLOR_DEPTH_32_P:
          NativeImageSourceColorDepth32P();
          break;

        case NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_P:
          NativeImageSourceGetNativeImageSourceP();
          break;

        case NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_N:
          NativeImageSourceGetNativeImageSourceN();
          break;

        case NATIVE_IMAGE_SOURCE_NEW_P:
          NativeImageSourceCreateNativeImageSourceP();
          break;

        case NATIVE_IMAGE_SOURCE_NEW_N:
          NativeImageSourceCreateNativeImageSourceN();
          break;

        case NATIVE_IMAGE_SOURCE_NEW_ANY_P:
          NativeImageSourceNewAnyP();
          break;

        case NATIVE_IMAGE_SOURCE_ENCODE_TO_FILE_P:
          NativeImageSourceEncodeToFileP();
          break;

        case NATIVE_IMAGE_SOURCE_GET_PIXELS_N:
          NativeImageSourceGetPixelsN();
          break;

        case NATIVE_IMAGE_SOURCE_GET_PIXELS_P:
          NativeImageSourceGetPixelsP();
          break;

        case NATIVE_IMAGE_SOURCE_SET_SOURCE_P:
          NativeImageSourceSetSourceP();
          break;

        case NATIVE_IMAGE_SOURCE_IS_COLOR_DEPTH_SUPPORTED_P:
          NativeImageSourceIsColorDepthSupportedP();
          break;

      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

} // unnamed namespace

void NativeImageSourceGetPixelsP()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(10u, 10u);

  if(nativeImageSource->IsColorDepthSupported(NativeImageSource::COLOR_DEPTH_DEFAULT) == false)
  {
    LOG_E( "Not supported ColorDepth format! HW target dependent value!" );
    DaliLog::PrintPass();
    return;
  }

  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  std::vector<unsigned char> pixbuf;
  unsigned int width = 10u;
  unsigned int height = 10u;
  Pixel::Format pixelFormat;

  nativeImageSource->GetPixels( pixbuf, width, height, pixelFormat );
  DALI_CHECK_FAIL( !width, "Native Image width is not 10" );
  DALI_CHECK_FAIL( !height, "Native Image height is not 10" );

  DaliLog::PrintPass();

}

void NativeImageSourceGetPixelsN()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(0u, 0u);
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  std::vector<unsigned char> pixbuf;
  unsigned int width = 0u;
  unsigned int height = 0u;
  Pixel::Format pixelFormat;

  nativeImageSource->GetPixels( pixbuf, width, height, pixelFormat );
  DALI_CHECK_FAIL( width, "Native Image width is 0" );
  DALI_CHECK_FAIL( height, "Native Image height is 0" );

  DaliLog::PrintPass();

}

void NativeImageSourceEncodeToFileP()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(10u, 10u);
  if(nativeImageSource->IsColorDepthSupported(NativeImageSource::COLOR_DEPTH_DEFAULT) == false)
  {
    LOG_E( "Not supported ColorDepth format! HW target dependent value!" );
    DaliLog::PrintPass();
    return;
  }

  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  string imageFileName = getResourceFullPath( "NativeImageSource.png" );
  bool ret = nativeImageSource->EncodeToFile( imageFileName.c_str() );
  DALI_CHECK_FAIL( !ret, "Native Image source not encoded to file" );

  DaliLog::PrintPass();
}

NativeImageSourcePtr CreateNativeImageSource(unsigned int width, unsigned int height)
{
  NativeImageSourcePtr nativeImageSource = NativeImageSource::New( width, height, NativeImageSource::COLOR_DEPTH_DEFAULT );

  return nativeImageSource;
}

void NativeImageSourceCreateNativeImageSourceP()
{
  unsigned int width = 10u;
  unsigned int height = 10u;

  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource( width, height );
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  DaliLog::PrintPass();
}

void NativeImageSourceCreateNativeImageSourceN()
{
  unsigned int width = 0u;
  unsigned int height = 0u;

  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource( width, height );
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  DaliLog::PrintPass();
}

void NativeImageSourceNewAnyP()
{
  Any pixmap;

  NativeImageSourcePtr nativeImageSource = NativeImageSource::New( pixmap );
  DALI_CHECK_FAIL( !nativeImageSource, "Native image Source craeton fail" );

  DaliLog::PrintPass();
}

void NativeImageSourceGetNativeImageSourceP()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(10u, 10u);
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );


  try
  {
    Any nativeImage = nativeImageSource->GetNativeImageSource();
    DALI_CHECK_FAIL( nativeImage.Empty(), "NativeImageSourceisEmpty" );
  }
  catch( DaliException& e )
  {
    DALI_CHECK_FAIL( true ," Window::GetNativeImageSource is failing" );
  }

  DaliLog::PrintPass();
}

void NativeImageSourceGetNativeImageSourceN()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(0u, 0u);
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  try
  {
    Any nativeImage = nativeImageSource->GetNativeImageSource();
    DALI_CHECK_FAIL( nativeImage.Empty(), "NativeImageSourceisEmpty" );
  }
  catch( DaliException& e )
  {
    DALI_CHECK_FAIL( true,"nativeImageSource::GetNativeImageSourceN is failing" );
  }

  DaliLog::PrintPass();
}

void NativeImageSourceColorDepthDefaultP()
{
  bool bCheck = false;

  bCheck = NativeImageSourceNewGetPixelSourceEncodeToFile( NativeImageSource::COLOR_DEPTH_DEFAULT );
  DALI_CHECK_FAIL( !bCheck,
      "NativeImageSource construction with proper pixels, internal source and encoding is failed for COLOR_DEPTH_DEFAULT." );

  DaliLog::PrintPass();
}

void NativeImageSourceColorDepth24P()
{
  bool bCheck = false;

  bCheck = NativeImageSourceNewGetPixelSourceEncodeToFile( NativeImageSource::COLOR_DEPTH_24 );
  DALI_CHECK_FAIL( !bCheck,
      "NativeImageSource construction with proper pixels, internal source and encoding is failed for COLOR_DEPTH_24." );

  DaliLog::PrintPass();
}

void NativeImageSourceColorDepth32P()
{
  bool bCheck = false;

  bCheck = NativeImageSourceNewGetPixelSourceEncodeToFile( NativeImageSource::COLOR_DEPTH_32 );
  DALI_CHECK_FAIL( !bCheck,
      "NativeImageSource construction with proper pixels, internal source and encoding is failed for COLOR_DEPTH_32." );

  DaliLog::PrintPass();
}

void NativeImageSourceSetSourceP()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(0u, 0u);
  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  try
  {
    Any nativeImage = nativeImageSource->GetNativeImageSource();
    DALI_CHECK_FAIL( nativeImage.Empty(), "NativeImageSourceisEmpty" );

    nativeImageSource->SetSource(nativeImage);

    Any nativeImage1 = nativeImageSource->GetNativeImageSource();
    DALI_CHECK_FAIL( nativeImage1.Empty(), "NativeImageSourceisEmpty" );
  }
  catch( DaliException& e )
  {
    DALI_CHECK_FAIL( true,"nativeImageSource::SetSource is failing" );
  }

  DaliLog::PrintPass();
}

void NativeImageSourceIsColorDepthSupportedP()
{
  NativeImageSourcePtr nativeImageSource = CreateNativeImageSource(10u, 10u);

  if(nativeImageSource->IsColorDepthSupported(NativeImageSource::COLOR_DEPTH_DEFAULT) == false)
  {
    LOG_E( "Not supported ColorDepth format! HW target dependent value!" );
    DaliLog::PrintPass();
    return;
  }

  DALI_CHECK_FAIL( !nativeImageSource, "Native Image source not created" );

  DaliLog::PrintPass();
}

/**
 * @testcase    UtcDaliNativeImageSourceColorDepthDefaultP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::ColorDepthDefaultP() functionality
 */

int UtcDaliNativeImageSourceColorDepthDefaultP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_COLOR_DEPTH_DEFAULT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceColorDepth24P
 * @since_tizen 2.4
 * @description checks for NativeImageSource::ColorDepth24P() functionality
 */

int UtcDaliNativeImageSourceColorDepth24P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_COLOR_DEPTH_24_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceColorDepth32P
 * @since_tizen 2.4
 * @description checks for NativeImageSource::ColorDepth32P() functionality
 */

int UtcDaliNativeImageSourceColorDepth32P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_COLOR_DEPTH_32_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceGetNativeImageSourceP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::GetNativeImageSourceP() functionality
 */

int UtcDaliNativeImageSourceGetNativeImageSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceGetNativeImageSourceN
 * @since_tizen 2.4
 * @description checks for NativeImageSource::GetNativeImageSourceN() functionality
 */

int UtcDaliNativeImageSourceGetNativeImageSourceN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_GET_NATIVE_IMAGE_SOURCE_N);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceNewN
 * @since_tizen 2.4
 * @description checks for NativeImageSource::SourceNewN() functionality
 */

int UtcDaliNativeImageSourceNewN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_NEW_N);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceNewP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::SourceNewP() functionality
 */

int UtcDaliNativeImageSourceNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceNewAnyP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::NewAnyP() functionality
 */

int UtcDaliNativeImageSourceNewAnyP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_NEW_ANY_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceEncodeToFileP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::EncodeToFileP() functionality
 */

int UtcDaliNativeImageSourceEncodeToFileP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_ENCODE_TO_FILE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceGetPixelsN
 * @since_tizen 2.4
 * @description checks for NativeImageSource::GetPixelsN() functionality
 */

int UtcDaliNativeImageSourceGetPixelsN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_GET_PIXELS_N);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceGetPixelsP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::GetPixelsP() functionality
 */

int UtcDaliNativeImageSourceGetPixelsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_GET_PIXELS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceSetSourceP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::SetSource() functionality
 */

int UtcDaliNativeImageSourceSetSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_SET_SOURCE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase    UtcDaliNativeImageSourceIsColorDepthSupportedP
 * @since_tizen 2.4
 * @description checks for NativeImageSource::IsColorDepthSupported() functionality
 */

int UtcDaliNativeImageSourceIsColorDepthSupportedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  NativeImageSource_TestApp testApp( application, NATIVE_IMAGE_SOURCE_IS_COLOR_DEPTH_SUPPORTED_P);
  application.MainLoop();

  return test_return_value;
}
