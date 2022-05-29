#include "utc-dali-buffer-image-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

int gRenderCountBI;                                      /** Render Count **/
BufferImage gBufferImage;                                /** BufferImage instance **/
Actor gActorView;                                    /** ImageView instance **/
int gBufferImageUploadedSignalReceived;       /** Status for image uploaded signal connection **/
PixelBuffer* gPixelBuffer;                               /** Pixel Buffer For BufferImage **/

/**
 * @function            utc_Dali_BufferImage_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_BufferImage_startup(void)
{
  test_return_value = 0;
  gRenderCountBI = 0;
  gBufferImageUploadedSignalReceived = 0;
}

/**
 * @function            utc_Dali_BufferImage_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_BufferImage_cleanup(void)
{

}

void CbBufferImageUploaded(Image image)
{
  LOG_I("Received image uploaded signal.\n");
  ++gBufferImageUploadedSignalReceived;
}



void BufferImageNewWithExternalDataSourceAndStrideP();
void BufferImageNewWithWidthHeightPixelFormatP();
void BufferImageCopyConstructorWHITEP();
void BufferImageGetBufferStrideUpdateP();
void BufferImageWHITEP();
void BufferImageDowncastP();
void BufferImageDowncastN();
void BufferImageGetBufferP();
void BufferImageGetBufferSizeP();
void BufferImageGetBufferStrideP();
void BufferImageGetPixelFormatP();
void BufferImageIsDataExternalP();
void VTBufferImageGetBufferStrideUpdate001();
void VTBufferImageGetBufferStrideUpdate002();
void VTBufferImageGetBufferStrideUpdate003();
void VTBufferImageGetBufferStrideUpdate004();

namespace
{
  enum TEST_CASES_LIST
  {
    BUFFER_IMAGE_NEW_WITH_EXTERNAL_DATASOURCE_ANDSTRIDE_P,
    BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P,
    BUFFER_IMAGE_COPYCONSTRUCTOR_WHITE_P,
    BUFFER_IMAGE_GETBUFFER_STRIDE_UPDATE_P,
    BUFFER_IMAGE_WHITE_P,
    BUFFER_IMAGE_DOWNCAST_P,
    BUFFER_IMAGE_DOWNCAST_N,
    BUFFER_IMAGE_GET_BUFFER_P,
    BUFFER_IMAGE_GET_BUFFER_SIZE_P,
    BUFFER_IMAGE_GET_BUFFER_STRIDE_P,
    BUFFER_IMAGE_GET_PIXEL_FORMAT_P,
    BUFFER_IMAGE_IS_DATA_EXTERNAL_P
  };

  struct TestApp : public ConnectionTracker
  {
    TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value == TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }
      VerdictTest();
      if(test_return_value == TC_FAIL)
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
        case BUFFER_IMAGE_NEW_WITH_EXTERNAL_DATASOURCE_ANDSTRIDE_P:
          BufferImageNewWithExternalDataSourceAndStrideP();
          break;

        case BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P:
          BufferImageNewWithWidthHeightPixelFormatP();
          break;

        case BUFFER_IMAGE_COPYCONSTRUCTOR_WHITE_P:
          BufferImageCopyConstructorWHITEP();
          break;

        case BUFFER_IMAGE_GETBUFFER_STRIDE_UPDATE_P:
          BufferImageGetBufferStrideUpdateP();
          break;

        case BUFFER_IMAGE_WHITE_P:
          BufferImageWHITEP();
          break;

        case BUFFER_IMAGE_DOWNCAST_P:
          BufferImageDowncastP();
          break;

        case BUFFER_IMAGE_DOWNCAST_N:
          BufferImageDowncastN();
          break;

        case BUFFER_IMAGE_GET_BUFFER_P:
          BufferImageGetBufferP();
          break;

        case BUFFER_IMAGE_GET_BUFFER_SIZE_P:
          BufferImageGetBufferSizeP();
          break;

        case BUFFER_IMAGE_GET_BUFFER_STRIDE_P:
          BufferImageGetBufferStrideP();
          break;

        case BUFFER_IMAGE_GET_PIXEL_FORMAT_P:
          BufferImageGetPixelFormatP();
          break;

        case BUFFER_IMAGE_IS_DATA_EXTERNAL_P:
          BufferImageIsDataExternalP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case BUFFER_IMAGE_GETBUFFER_STRIDE_UPDATE_P:
          switch (gRenderCountBI)
          {
            case 0:
              VTBufferImageGetBufferStrideUpdate001();
              gRenderCountBI++;
              break;

            case 1:
              VTBufferImageGetBufferStrideUpdate002();
              gRenderCountBI++;
              break;

            case 2:
              VTBufferImageGetBufferStrideUpdate003();
              gRenderCountBI++;
              break;

            case 3:
              VTBufferImageGetBufferStrideUpdate004();
              mTimer.Stop();
              mApplication.Quit();
              break;

          }
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();
      }
    }
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };
} // unnamed namespace


/**
 * @testcase            UtcDaliBufferImageNewWithExternalDataSourceAndStrideP
 * @since_tizen         2.4
 * @description         check if New api works or not
 */

int UtcDaliBufferImageNewWithExternalDataSourceAndStrideP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_NEW_WITH_EXTERNAL_DATASOURCE_ANDSTRIDE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageNewWithExternalDataSourceAndStrideP()
{
  unsigned int uStride = 16u;

  PixelBuffer* pixelBuffer = new PixelBuffer[BUFFER_IMAGE_WIDTH * BUFFER_IMAGE_HEIGHT];
  DALI_CHECK_FAIL(!pixelBuffer, " pixelBuffer is empty.");

  BufferImage bufferImage = BufferImage::New(pixelBuffer, BUFFER_IMAGE_WIDTH, BUFFER_IMAGE_HEIGHT, Pixel::A8, uStride);
  DALI_CHECK_FAIL(!bufferImage, " bufferImage is empty.");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageNewWithWidthHeightPixelFormatP
 * @since_tizen         2.4
 * @description         check if New api works or not.
 */

int UtcDaliBufferImageNewWithWidthHeightPixelFormatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageNewWithWidthHeightPixelFormatP()
{
  BufferImage bufferImage = BufferImage::New(BUFFER_IMAGE_WIDTH, BUFFER_IMAGE_HEIGHT, Pixel::RGB565);
  DALI_CHECK_FAIL(!bufferImage, " bufferImage is empty.");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageCopyConstructorWhiteP
 * @since_tizen         2.4
 * @description         check if copy constructor works or not.
 */
int UtcDaliBufferImageCopyConstructorWhiteP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_COPYCONSTRUCTOR_WHITE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageCopyConstructorWHITEP()
{
  BufferImage bufferImage = BufferImage::New(BUFFER_IMAGE_WIDTH, BUFFER_IMAGE_HEIGHT, Pixel::RGB565);
  DALI_CHECK_FAIL(!bufferImage, " bufferImage is empty.");

  BufferImage bufferImgCopy = BufferImage(bufferImage);
  DALI_CHECK_FAIL(!bufferImgCopy, " BufferImage copy constructor failed.");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageGetbufferStrideUpdateP
 * @since_tizen         2.4
 * @description         check if GetBufferStride apis works or not.
 */
int UtcDaliBufferImageGetbufferStrideUpdateP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_GETBUFFER_STRIDE_UPDATE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageGetBufferStrideUpdateP()
{
  gBufferImage = BufferImage::WHITE();               // creates a 1x1 RGBA white pixel
  unsigned int ubufferStride = gBufferImage.GetBufferStride();

  gPixelBuffer = new PixelBuffer[20 * 16];
  DALI_CHECK_FAIL(!gPixelBuffer, " PixelBuffer new failed.");

  for(size_t i=0; i<16; i++)
  {
    gPixelBuffer[i*4+0] = 0xFF;
    gPixelBuffer[i*4+1] = 0xFF;
    gPixelBuffer[i*4+2] = 0xFF;
    gPixelBuffer[i*4+3] = 0xFF;
  }

  gBufferImage = BufferImage::New(gPixelBuffer, 16, 16, Pixel::A8, 20);
  DALI_CHECK_FAIL(!gBufferImage, " bufferImage is empty.");
  DALI_CHECK_FAIL(gBufferImage.GetWidth() != 16 || gBufferImage.GetHeight() != 16, "Image size is mismatched.");
  DALI_CHECK_FAIL(gBufferImage.GetPixelFormat() != Pixel::A8, "Pixel format is mismatched.");


  unsigned int uGetBufferStride = gBufferImage.GetBufferStride();
  unsigned int pixelSize = Pixel::GetBytesPerPixel(gBufferImage.GetPixelFormat());

  DALI_CHECK_FAIL( uGetBufferStride != 20 * pixelSize , "Stride mismatched");
  DALI_CHECK_FAIL(!gBufferImage.IsDataExternal() , "IsDataExternal is failed" );

  gBufferImage.UploadedSignal().Connect(CbBufferImageUploaded);

}

void VTBufferImageGetBufferStrideUpdate001()
{
  gActorView = ImageView::New(gBufferImage);
  DALI_CHECK_FAIL(!gActorView, " imgActorView is empty.");

  gActorView.SetVisible(true);
  Stage::GetCurrent().Add(gActorView);

}
void VTBufferImageGetBufferStrideUpdate002()
{
  DALI_CHECK_FAIL( !gBufferImageUploadedSignalReceived, " Image uploaded signal is not received.");
  gBufferImageUploadedSignalReceived = 0;
  gBufferImage.Update();
}
void VTBufferImageGetBufferStrideUpdate003()
{
  DALI_CHECK_FAIL( !gBufferImageUploadedSignalReceived, "Image uploaded signal is not received after calling Update.");

  unsigned int XCoord = 9u, YCoord = 9u;
  unsigned int WIDTH = 5u, HEIGHT = 5u;

  RectArea rect(XCoord, YCoord, WIDTH, HEIGHT);
  gBufferImage.Update(rect);
}
void VTBufferImageGetBufferStrideUpdate004()
{
  DALI_CHECK_FAIL( !gBufferImageUploadedSignalReceived, " Image uploaded signal is not received for RectArea.");
  gBufferImageUploadedSignalReceived = false;

  Stage::GetCurrent().Remove(gActorView);
  delete[] gPixelBuffer;
  gPixelBuffer = NULL;
  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliBufferImageWhiteP
 * @since_tizen         2.4
 * @description         check if White api works or not.
 */
int UtcDaliBufferImageWhiteP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_WHITE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageWHITEP()
{
  BufferImage bufferImage = BufferImage::WHITE();
  DALI_CHECK_FAIL(bufferImage.GetWidth() != 1u || bufferImage.GetHeight() != 1u, "Failed to get dimension(1x1)");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageDowncastP
 * @since_tizen         2.4
 * @description         check if DownCast works or not.
 */
int UtcDaliBufferImageDowncastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageDowncastP()
{
  unsigned int uStride = 16u;

  PixelBuffer* pixelBuffer = new PixelBuffer[BUFFER_IMAGE_WIDTH * BUFFER_IMAGE_HEIGHT];
  DALI_CHECK_FAIL(!pixelBuffer, " pixelBuffer is empty.");

  BufferImage bufferImage = BufferImage::New(pixelBuffer, BUFFER_IMAGE_WIDTH, BUFFER_IMAGE_HEIGHT, Pixel::A8, uStride);
  DALI_CHECK_FAIL(!bufferImage, " bufferImage is empty.");

  Image img = BufferImage::New(pixelBuffer, BUFFER_IMAGE_WIDTH, BUFFER_IMAGE_HEIGHT, Pixel::A8, uStride);
  DALI_CHECK_FAIL(!img, " img is empty.");

  //Stage::GetCurrent().Add(img);

  BufferImage  bufferImage1 =  BufferImage::DownCast(img);
  DALI_CHECK_FAIL(!bufferImage1, " BufferImage::DownCast is Failed to cast.");

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageDowncastN
 * @since_tizen         2.4
 * @description         check if DownCast works or not.
 */
int UtcDaliBufferImageDowncastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}

void BufferImageDowncastN()
{
  Actor unInitialzedActor;
  BufferImage bufferImage = BufferImage::DownCast( unInitialzedActor );

  DALI_CHECK_FAIL(bufferImage, " BufferImage::DownCast is Failed to cast.");

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliBufferImageGetPixelFormatP
 * @since_tizen         2.4
 * @description         check if GetPixelFormat works or not.
 */
int UtcDaliBufferImageGetPixelFormatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_GET_PIXEL_FORMAT_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageGetPixelFormatP()
{
  BufferImage image = BufferImage::New( 16, 16, Pixel::A8 );
  DALI_CHECK_FAIL( image.GetPixelFormat() != Pixel::A8 ,"Pixel FORMAT doesnt match");

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliBufferImageGetBufferP
 * @since_tizen         2.4
 * @description         check if GetBuffer api works or not.
 */
int UtcDaliBufferImageGetBufferP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_GET_BUFFER_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageGetBufferP()
{
  BufferImage image = BufferImage::WHITE();               // creates a 1x1 RGBA white pixel
  PixelBuffer* buffer = image.GetBuffer();

  DALI_CHECK_FAIL( image.GetWidth() != 1 ||               // 1 pixel wide
      buffer == NULL ||                      // valid buffer
      *((unsigned int*)buffer) != 0xffffffff , "Get Buffer is failed"); // all component are 255

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageGetBufferSizeP
 * @since_tizen         2.4
 * @description         check if GetBufferSize api works or not.
 */
int UtcDaliBufferImageGetBufferSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_GET_BUFFER_SIZE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageGetBufferSizeP()
{
  BufferImage image = BufferImage::WHITE();               // creates a 1x1 RGBA white pixel
  PixelBuffer* buffer = image.GetBuffer();
  unsigned int bufferSize = image.GetBufferSize();
  unsigned int pixelSize = Pixel::GetBytesPerPixel(image.GetPixelFormat());

  DALI_CHECK_FAIL( image.GetWidth() != 1 ||               // 1 pixel wide
      buffer == NULL ||                      // valid buffer
      bufferSize != pixelSize , "Size mismatch");              // r component is 255

  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliBufferImageGetBufferStrideP
 * @since_tizen         2.4
 * @description         check if GetBufferStride api works or not.
 */
int UtcDaliBufferImageGetBufferStrideP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_GET_BUFFER_STRIDE_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageGetBufferStrideP()
{
  BufferImage image = BufferImage::WHITE();               // creates a 1x1 RGBA white pixel
  unsigned int pixelSize = Pixel::GetBytesPerPixel(image.GetPixelFormat());
  unsigned int bufferStride = image.GetBufferStride();
  DALI_CHECK_FAIL( bufferStride != pixelSize , "Stride match");
  DALI_CHECK_FAIL( image.IsDataExternal() , "IsDataExternal is failed" );

  PixelBuffer* buffer = new PixelBuffer[20 * 16];
  image = BufferImage::New(buffer, 16, 16, Pixel::A8, 20);
  bufferStride = image.GetBufferStride();

  DALI_CHECK_FAIL( bufferStride != 20, "Bufferstride mismatch");
  delete [] buffer;

  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliBufferImageIsDataExternalP
 * @since_tizen         2.4
 * @description         check if IsDataExternal api works or not.
 */
int UtcDaliBufferImageIsDataExternalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TestApp testApp(application, BUFFER_IMAGE_IS_DATA_EXTERNAL_P);
  application.MainLoop();
  return test_return_value;
}

void BufferImageIsDataExternalP()
{
  PixelBuffer* buffer = new PixelBuffer[16 * 16];
  BufferImage image = BufferImage::New(buffer, 16, 16, Pixel::A8);
  DALI_CHECK_FAIL( !image.IsDataExternal() , "IsDataExternal is failed" );

  DaliLog::PrintPass();
}
