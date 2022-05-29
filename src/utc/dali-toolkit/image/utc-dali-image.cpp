#include "utc-dali-image-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

using namespace Dali;
using namespace Dali::Toolkit;

/**
 * @function            utc_Dali_Image_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Image_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Image_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Image_cleanup(void)
{
}

void ImageConvertFrameBufferToUrl1P();
void ImageConvertFrameBufferToUrl2P();
void ImageConvertPixelDataToUrlP();
void ImageConvertNativeImageSourceToUrlP();
void ImageConvertFrameBufferToUrl1N();
void ImageConvertFrameBufferToUrl2N();
void ImageConvertPixelDataToUrlN();
void ImageConvertNativeImageSourceToUrlN();

namespace
{
  enum TEST_CASES_LIST_IMAGE
  {
    IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_P,
    IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_P,
    IMAGE_CONVERT_PIXEL_DATA_TO_URL_P,
    IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_P,
    IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_N,
    IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_N,
    IMAGE_CONVERT_PIXEL_DATA_TO_URL_N,
    IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_N
  };

  struct Image_TestApp : public ConnectionTracker
  {
    Image_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Image_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Image_TestApp::Tick );
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
      switch ( mTestCase )
      {
        case IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_P:
          ImageConvertFrameBufferToUrl1P();
          break;
        case IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_P:
          ImageConvertFrameBufferToUrl2P();
          break;
        case IMAGE_CONVERT_PIXEL_DATA_TO_URL_P:
          ImageConvertPixelDataToUrlP();
          break;
        case IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_P:
          ImageConvertNativeImageSourceToUrlP();
          break;
        case IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_N:
          ImageConvertFrameBufferToUrl1N();
          break;
        case IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_N:
          ImageConvertFrameBufferToUrl2N();
          break;
        case IMAGE_CONVERT_PIXEL_DATA_TO_URL_N:
          ImageConvertPixelDataToUrlN();
          break;
        case IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_N:
          ImageConvertNativeImageSourceToUrlN();
          break;
      }
    }

    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
}

void ImageConvertFrameBufferToUrl1P()
{
  unsigned int width(64);
  unsigned int height(64);
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::NONE );

  DALI_TEST_CHECK( frameBuffer );
  std::string url = Dali::Toolkit::Image::GenerateUrl( frameBuffer, Pixel::Format::RGBA8888, width, height );

  DALI_TEST_CHECK( url.size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertFrameBufferToUrl2P()
{
  unsigned int width(64);
  unsigned int height(64);
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::NONE );

  Texture texture = Texture::New( TextureType::TEXTURE_2D, Pixel::RGBA8888, width, height );
  frameBuffer.AttachColorTexture( texture );

  DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( frameBuffer, 0 ).size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertPixelDataToUrlP()
{
  unsigned int width(64);
  unsigned int height(64);
  unsigned int bufferSize = width*height*Pixel::GetBytesPerPixel( Pixel::RGB888 );

  unsigned char* buffer= reinterpret_cast<unsigned char*>( malloc( bufferSize ) );
  PixelData pixelData = PixelData::New( buffer, bufferSize, width, height, Pixel::RGB888, PixelData::FREE );

  DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( pixelData ).size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertNativeImageSourceToUrlP()
{
  unsigned int width(64);
  unsigned int height(64);
  try
  {
    NativeImageSourcePtr nativeImageSource = NativeImageSource::New(width, height, NativeImageSource::COLOR_DEPTH_DEFAULT );

    DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( nativeImageSource ).size() > 0u );
  }
  catch(Dali::DaliException& e)
  {
    LOG_E( "Adaptor::IsAvailable()" );
    test_return_value=1;
  }
  catch(...)
  {
  }

  DaliLog::PrintPass();
}

void ImageConvertFrameBufferToUrl1N()
{
  unsigned int width(64);
  unsigned int height(64);
  FrameBuffer frameBuffer = FrameBuffer::New( width, height );
  // Wrong size of width and height. But it is ok, though pointless from app point of view
  std::string url = Dali::Toolkit::Image::GenerateUrl( frameBuffer, Pixel::Format::RGBA8888, 0u, 0u );

  DALI_TEST_CHECK( url.size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertFrameBufferToUrl2N()
{
  unsigned int width(64);
  unsigned int height(64);
  FrameBuffer frameBuffer = FrameBuffer::New( width, height, FrameBuffer::Attachment::NONE );

  // No added texture. But it is ok, though pointless from app point of view
  DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( frameBuffer, 0 ).size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertPixelDataToUrlN()
{
  unsigned int width(64);
  unsigned int height(64);
  unsigned int bufferSize = width*height*Pixel::GetBytesPerPixel( Pixel::RGB888 );

  // empty buffer is ok, though pointless from app point of view
  PixelData pixelData = PixelData::New( NULL, bufferSize, width, height, Pixel::RGB888, PixelData::FREE );

  DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( pixelData ).size() > 0u );

  DaliLog::PrintPass();
}

void ImageConvertNativeImageSourceToUrlN()
{
  try
  {
    // Wrong size of width and height is ok, though pointless from app point of view
    NativeImageSourcePtr nativeImageSource = NativeImageSource::New( 0u, 0u, NativeImageSource::COLOR_DEPTH_DEFAULT );

    DALI_TEST_CHECK( Dali::Toolkit::Image::GenerateUrl( nativeImageSource ).size() > 0u );
  }
  catch(Dali::DaliException& e)
  {
    LOG_E( "Adaptor::IsAvailable()" );
    test_return_value=1;
  }
  catch(...)
  {
  }

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliImageConvertFrameBufferToUrl1P
 * @since_tizen         6.0
 * @description         Checks correct conversion from new texture in the frame buffer to url.
 */

int UtcDaliImageConvertFrameBufferToUrl1P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertFrameBufferToUrl2P
 * @since_tizen         6.0
 * @description         Checks correct conversion from already existed texture of the frame buffer to url.
 */

int UtcDaliImageConvertFrameBufferToUrl2P(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertPixelDataToUrlP
 * @since_tizen         6.0
 * @description         Checks correct conversion from pixel data to url.
 */

int UtcDaliImageConvertPixelDataToUrlP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_PIXEL_DATA_TO_URL_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertNativeImageSourceToUrlP
 * @since_tizen         6.0
 * @description         Checks correct conversion from native image source to url.
 */

int UtcDaliImageConvertNativeImageSourceToUrlP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertFrameBufferToUrl1N
 * @since_tizen         6.0
 * @description         Checks whether the API generate url even though the input value is wrong.
 */

int UtcDaliImageConvertFrameBufferToUrl1N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_FRAME_BUFFER_TO_URL1_N );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertFrameBufferToUrl2N
 * @since_tizen         6.0
 * @description         Checks whether the API generate url even though the input value is wrong.
 */

int UtcDaliImageConvertFrameBufferToUrl2N(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_FRAME_BUFFER_TO_URL2_N );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageConvertPixelDataToUrlN
 * @since_tizen         6.0
 * @description         Checks whether the API generate url even though the input value is wrong.
 */

int UtcDaliImageConvertPixelDataToUrlN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_PIXEL_DATA_TO_URL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageConvertNativeImageSourceToUrlN
 * @since_tizen         6.0
 * @description         Checks whether the API generate url even though the input value is wrong.
 */

int UtcDaliImageConvertNativeImageSourceToUrlN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Image_TestApp testApp( application, IMAGE_CONVERT_NATIVE_IMAGE_SOURCE_TO_URL_N );
  application.MainLoop();

  return test_return_value;
}
