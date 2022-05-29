#include "utc-dali-frame-buffer-image-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: Framebufferimage
/**
 * @function            utc_Dali_FrameBufferImage_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_FrameBufferImage_startup(void)
{
  test_return_value = 0;
}

/**
 * @function            utc_Dali_FrameBufferImage_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */
void utc_Dali_FrameBufferImage_cleanup(void)
{

}


void FrameBufferImageDownCastP();
void FrameBufferImageDownCastN();
void FrameBufferImageDownCastN2();
void FrameBufferImageNewWithWidthHeightPixelFormatP();
void FrameBufferImageNativeP();
void FrameBufferImageCopyConstructorP();
void FrameBufferImageOperatorAssignmentP();

namespace
{
  enum TEST_CASES_LIST_FRAME_BUFFER_IMAGE
  {
    FRAME_BUFFER_IMAGE_DOWNCAST_P,
    FRAME_BUFFER_IMAGE_DOWNCAST_N,
    FRAME_BUFFER_IMAGE_DOWNCAST_N2,
    FRAME_BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P,
    FRAME_BUFFER_IMAGE_NATIVE_P,
    FRAME_BUFFER_IMAGE_COPY_CONSTRUCTOR_P,
    FRAME_BUFFER_IMAGE_OPERATOR_ASSIGNMENT_P
  };

  struct Frame_Buffer_Image_TestApp : public ConnectionTracker
  {
    Frame_Buffer_Image_TestApp( Application& app, int test_case ): mApplication( app ), mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Frame_Buffer_Image_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Frame_Buffer_Image_TestApp::Tick );
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
        case FRAME_BUFFER_IMAGE_DOWNCAST_P:
          FrameBufferImageDownCastP();
          break;

        case FRAME_BUFFER_IMAGE_DOWNCAST_N:
          FrameBufferImageDownCastN();
          break;

        case FRAME_BUFFER_IMAGE_DOWNCAST_N2:
          FrameBufferImageDownCastN2();
          break;


        case FRAME_BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P:
          FrameBufferImageNewWithWidthHeightPixelFormatP();
          break;

        case FRAME_BUFFER_IMAGE_NATIVE_P:
          FrameBufferImageNativeP();
          break;

        case FRAME_BUFFER_IMAGE_COPY_CONSTRUCTOR_P:
          FrameBufferImageCopyConstructorP();
          break;

        case FRAME_BUFFER_IMAGE_OPERATOR_ASSIGNMENT_P:
          FrameBufferImageOperatorAssignmentP();
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

void FrameBufferImageDownCastP()
{
  FrameBufferImage image = FrameBufferImage::New();
  DALI_CHECK_FAIL(!image, "FrameBufferImage::New is failed to create new FrameBufferImage instance");
  BaseHandle baseHandle(image);

  FrameBufferImage image2 = FrameBufferImage::DownCast(baseHandle);

  DALI_CHECK_FAIL(!image2, "FrameBufferImage::DownCast is failed to down cast and baseHandle to its base");

  FrameBufferImage image3 = DownCast< FrameBufferImage >(baseHandle);
  DALI_CHECK_FAIL(!image3, "DownCast< FrameBufferImage >() is failed to down cast and an baseHandle to its base");

  BaseHandle unInitializedObject;
  FrameBufferImage image4 = FrameBufferImage::DownCast(unInitializedObject);
  DALI_CHECK_FAIL(image4, "Invalid down cast operation");

  FrameBufferImage image5 = DownCast<FrameBufferImage>(unInitializedObject);
  DALI_CHECK_FAIL(image5, "Invalid down cast operation");

  DaliLog::PrintPass();
}

void FrameBufferImageDownCastN()
{
  BaseHandle unInitializedObject;
  FrameBufferImage image = FrameBufferImage::DownCast(unInitializedObject);
  DALI_CHECK_FAIL(image, "Invalid down cast operation");

  DaliLog::PrintPass();
}

void FrameBufferImageDownCastN2()
{
  BaseHandle unInitializedObject;
  FrameBufferImage image = DownCast<FrameBufferImage>(unInitializedObject);
  DALI_CHECK_FAIL(image, "Invalid down cast operation");

  DaliLog::PrintPass();
}

void FrameBufferImageNewWithWidthHeightPixelFormatP()
{
  unsigned int uWidth = 10, uHeight = 10;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage::GetCurrent is failed to create");

  FrameBufferImage frameBufferImage = FrameBufferImage::New(uWidth, uHeight, Pixel::RGBA8888);
  DALI_CHECK_FAIL( !frameBufferImage ,  "FrameBufferImage::New is failed ");

  FrameBufferImage frameBufferImage2 = FrameBufferImage::New(uWidth, uHeight, Pixel::RGBA8888, RenderBuffer::COLOR);
  DALI_CHECK_FAIL( !frameBufferImage2 ,  "FrameBufferImage::New is failed ");

  DaliLog::PrintPass();
}

void FrameBufferImageNativeP()
{
  unsigned int uWidth = 10, uHeight = 10;

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage::GetCurrent is failed to create");

  NativeImageInterfacePtr nativeImage = new TestNativeImageInterface(uWidth, uHeight);

  DALI_CHECK_FAIL( !nativeImage ,  "TestNativeImage::New is failed.");

  FrameBufferImage frameBufferImage = FrameBufferImage::New(*(nativeImage.Get()));

  DALI_CHECK_FAIL( !frameBufferImage ,  "FrameBufferImage::New is failed ");

  DaliLog::PrintPass();
}

void FrameBufferImageCopyConstructorP()
{
  FrameBufferImage image = FrameBufferImage::New();
  DALI_CHECK_FAIL(!image, "FrameBufferImage::New is failed to create new FrameBufferImage instance");
  BaseHandle baseHandle(image);

  FrameBufferImage image2(image);
  DALI_CHECK_FAIL( !image ,  "Dali::FrameBufferImage (const FrameBufferImage &handle) is failed. The object is not initialized.");

  DaliLog::PrintPass();
}

void FrameBufferImageOperatorAssignmentP()
{
  FrameBufferImage image = FrameBufferImage::New();
  DALI_CHECK_FAIL(!image, "FrameBufferImage::New is failed to create new FrameBufferImage instance");
  BaseHandle baseHandle(image);

  FrameBufferImage image2;
  image2 = image;
  DALI_CHECK_FAIL( !image ,  "operator =  is failed. The object is not initialized.");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliFrameBufferImageDownCastP
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliFrameBufferImageDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_DOWNCAST_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageDownCastN
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliFrameBufferImageDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_DOWNCAST_N);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageDownCastN2
 * @since_tizen         2.4
 * @description         check if DownCast api works or not.
 */
int UtcDaliFrameBufferImageDownCastN2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_DOWNCAST_N2);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageNewWithWidthHeightPixelFormatP
 * @since_tizen         2.4
 * @description         check if New api works or not.
 */
int UtcDaliFrameBufferImageNewWithWidthHeightPixelFormatP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_NEW_WITH_WIDTH_HEIGHT_PIXEL_FORMAT_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageNewWithNativeP
 * @since_tizen         2.4
 * @description         check if New Api works or not.
 */
int UtcDaliFrameBufferImageNewWithNativeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_NATIVE_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageCopyConstructorP
 * @since_tizen         2.4
 * @description         check if copy constructor works or not.
 */
int UtcDaliFrameBufferImageCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}


/**
 * @testcase            UtcDaliFrameBufferImageOperatorAssignmentP
 * @since_tizen         2.4
 * @description         check if operator=() works or not.
 */
int UtcDaliFrameBufferImageOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Frame_Buffer_Image_TestApp testApp( application, FRAME_BUFFER_IMAGE_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();
  return test_return_value;
}

