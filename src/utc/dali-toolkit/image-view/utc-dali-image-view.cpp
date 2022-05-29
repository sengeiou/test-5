#include "utc-dali-image-view-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ImageView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ImageView_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ImageView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ImageView_cleanup(void)
{
}

/**Check for resource ready status**/
bool gResourceReadySignalFired = false;

/**
 * @function            CbResourceReadySignalCallback
 * @description         Callback for resource ready
 * @since_tizen         4.0
 */
void CbResourceReadySignalCallback( Control control )
{
  gResourceReadySignalFired = true;
}

void ImageViewConstructorP();
void ImageViewNewP();
void ImageViewNewWithImageP();
void ImageViewNewWithUrlP();
void ImageViewNewWithUrlAndSizeP();
void ImageViewCopyConstructorP();
void ImageViewOperatorAssignmentP();
void ImageViewDownCastP();
void ImageViewDownCastN();
void ImageViewSetAndGetImageP();
void ImageViewSetAndGetImageP2();
void ImageViewSetAndGetImageP3();
void ImageViewSetAndGetPropertyImage();
void ImageViewResourceReadySignalP();
void ImageViewIsResourceReady( ImageView& imageView );
void VTImageViewResourceReadySignalP();
void VTImageViewIsResourceReady( ImageView& imageView );

const char* TEST_IMAGE_FILE_NAME =  "gallery_image_01.jpg";

namespace
{
  enum TEST_CASES_LIST_IMAGE_VIEW
  {
    IMAGE_VIEW_CONSTRUCTOR_P,
    IMAGE_VIEW_NEW_P,
    IMAGE_VIEW_NEW_WITH_IMAGE_P,
    IMAGE_VIEW_NEW_WITH_URL_P,
    IMAGE_VIEW_NEW_WITH_URL_SIZE_P,
    IMAGE_VIEW_COPY_CONSTRUCTOR_P,
    IMAGE_VIEW_OPERATOR_ASSIGNMENT_P,
    IMAGE_VIEW_DOWNCAST_P,
    IMAGE_VIEW_DOWNCAST_N,
    IMAGE_VIEW_SET_GET_IMAGE_P,
    IMAGE_VIEW_SET_GET_IMAGE_P2,
    IMAGE_VIEW_SET_GET_IMAGE_P3,
    IMAGE_VIEW_SET_GET_PROPERTY_IMAGE,
    IMAGE_VIEW_RESOURCE_READY_SIGNAL_P,
    IMAGE_VIEW_IS_RESOURCE_READY
  };
  struct ImageView_TestApp : public ConnectionTracker
  {
    ImageView_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ImageView_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ImageView_TestApp::Tick );
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
        case IMAGE_VIEW_CONSTRUCTOR_P:
          ImageViewConstructorP();
          break;
        case IMAGE_VIEW_NEW_P:
          ImageViewNewP();
          break;
        case IMAGE_VIEW_NEW_WITH_IMAGE_P:
          ImageViewNewWithImageP();
          break;
        case IMAGE_VIEW_NEW_WITH_URL_P:
          ImageViewNewWithUrlP();
          break;
        case IMAGE_VIEW_NEW_WITH_URL_SIZE_P:
          ImageViewNewWithUrlAndSizeP();
          break;
        case IMAGE_VIEW_COPY_CONSTRUCTOR_P:
          ImageViewCopyConstructorP();
          break;
        case IMAGE_VIEW_OPERATOR_ASSIGNMENT_P:
          ImageViewOperatorAssignmentP();
          break;
        case IMAGE_VIEW_DOWNCAST_P:
          ImageViewDownCastP();
          break;
        case IMAGE_VIEW_DOWNCAST_N:
          ImageViewDownCastN();
          break;
        case IMAGE_VIEW_SET_GET_IMAGE_P:
          ImageViewSetAndGetImageP();
          break;
        case IMAGE_VIEW_SET_GET_IMAGE_P2:
          ImageViewSetAndGetImageP2();
          break;
        case IMAGE_VIEW_SET_GET_IMAGE_P3:
          ImageViewSetAndGetImageP3();
          break;
        case IMAGE_VIEW_SET_GET_PROPERTY_IMAGE:
          ImageViewSetAndGetPropertyImage();
          break;
        case IMAGE_VIEW_RESOURCE_READY_SIGNAL_P:
          ImageViewResourceReadySignalP();
          break;
        case IMAGE_VIEW_IS_RESOURCE_READY:
          ImageViewIsResourceReady( mResourceReadyTestImageView );
          break;
      }
    }
    void VerdictTest()
    {
      switch (mTestCase)
      {
        case IMAGE_VIEW_RESOURCE_READY_SIGNAL_P:
          VTImageViewResourceReadySignalP();
          break;
        case IMAGE_VIEW_IS_RESOURCE_READY:
          VTImageViewIsResourceReady( mResourceReadyTestImageView );
          break;
      }
    }
    Application& mApplication;
    int mTestCase;
    ImageView mResourceReadyTestImageView;
    Timer mTimer;
  };
}

void ImageViewConstructorP()
{
  ImageView imageview;
  DALI_CHECK_FAIL(imageview, "ImageView default handle is not empty.");

  DaliLog::PrintPass();
}

void ImageViewNewP()
{
  ImageView imageView = ImageView::New();
  DALI_CHECK_FAIL(!imageView, "ImageView::New() is failed.");

  DaliLog::PrintPass();
}

void ImageViewNewWithImageP()
{
  Image image;
  ImageView imageview = ImageView::New(image);
  DALI_CHECK_FAIL(!imageview, "ImageView::New(Image&) is failed.");

  DaliLog::PrintPass();
}

void ImageViewNewWithUrlP()
{
  ImageView imageview = ImageView::New(TEST_IMAGE_FILE_NAME);
  DALI_CHECK_FAIL(!imageview, "ImageView::New(const std::string&) is failed.");

  DaliLog::PrintPass();
}

void ImageViewNewWithUrlAndSizeP()
{
  ImageView imageview = ImageView::New(TEST_IMAGE_FILE_NAME, ImageDimensions( 34, 34 ));
  DALI_CHECK_FAIL(!imageview, "ImageView::New(const std::string&, int) is failed.");

  DaliLog::PrintPass();
}

void ImageViewCopyConstructorP()
{
  ImageView imageView = ImageView::New();
  ImageView copy( imageView );
  DALI_CHECK_FAIL(!copy, "ImageView::ImageView(const ImageView&) is failed.");

  DaliLog::PrintPass();
}

void ImageViewOperatorAssignmentP()
{
  ImageView imageView = ImageView::New();
  ImageView copy = imageView;
  DALI_CHECK_FAIL(!copy, "ImageView::ImageView(const ImageView&) is failed.");

  DaliLog::PrintPass();

}

void ImageViewDownCastP()
{
  ImageView imageView = ImageView::New();

  BaseHandle object(imageView);

  ImageView imageView2 = ImageView::DownCast( object );
  DALI_CHECK_FAIL(!imageView2, "ImageView::DownCast is failed.");

  ImageView imageView3 = DownCast< ImageView >( object );
  DALI_CHECK_FAIL(!imageView3, "DownCast<ImageView> is failed.");

  DaliLog::PrintPass();
}

void ImageViewDownCastN()
{
  BaseHandle unInitializedObject;

  ImageView imageView1 = ImageView::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(imageView1, "Model3dview handle is not empty." );

  ImageView imageView2 = DownCast< ImageView >( unInitializedObject );
  DALI_CHECK_FAIL(imageView2, "Model3dview handle is not empty." );

  DaliLog::PrintPass();
}

void ImageViewSetAndGetImageP()
{
  ResourceImage image1 = ResourceImage::New( TEST_IMAGE_FILE_NAME );
  ImageView imageView = ImageView::New();
  imageView.SetImage( image1 );
  Image image2 = imageView.GetImage();
  DALI_CHECK_FAIL( image1.GetWidth() != image2.GetWidth(), "ImageView Set Get Image is failed." );

  DaliLog::PrintPass();
}

void TestUrl( ImageView imageView, const std::string url )
{
  Property::Value value = imageView.GetProperty( imageView.GetPropertyIndex( "image" ) );

  std::string urlActual;
  value.Get( urlActual );
  DALI_CHECK_FAIL( urlActual != url, "ImageView ResourceUrl is failed." );

  DaliLog::PrintPass();
}

void ImageViewSetAndGetImageP2()
{
  ImageView imageView = ImageView::New();
  DALI_CHECK_FAIL(!imageView, "Image handle is empty." );

  imageView.SetImage(TEST_IMAGE_FILE_NAME);

  TestUrl( imageView, TEST_IMAGE_FILE_NAME );
}

void ImageViewSetAndGetImageP3()
{
  ImageView imageView = ImageView::New();
  DALI_CHECK_FAIL(!imageView, "Image handle is empty." );

  imageView.SetImage(TEST_IMAGE_FILE_NAME, ImageDimensions( 34, 34 ) );

  TestUrl( imageView, TEST_IMAGE_FILE_NAME );
}

void ImageViewSetAndGetPropertyImage()
{
  ImageView imageView = ImageView::New();

  Property::Index idx = imageView.GetPropertyIndex( "image" );

  DALI_CHECK_FAIL( idx != ImageView::Property::IMAGE, "ImageView Get is failed." );

  imageView.SetProperty( idx, TEST_IMAGE_FILE_NAME );
  TestUrl( imageView, TEST_IMAGE_FILE_NAME );
}

void ImageViewResourceReadySignalP()
{
  ImageView imageView = ImageView::New( TEST_IMAGE_FILE_NAME );
  imageView.ResourceReadySignal().Connect( &CbResourceReadySignalCallback);
  Stage::GetCurrent().Add( imageView );

  DaliLog::PrintPass();
}

void ImageViewIsResourceReady( ImageView& imageView )
{
  imageView = ImageView::New( TEST_IMAGE_FILE_NAME );

  DALI_CHECK_FAIL( imageView.IsResourceReady(), "IsResourceReady is returned which not expected" );

  Stage::GetCurrent().Add( imageView );

  DaliLog::PrintPass();
}

void VTImageViewResourceReadySignalP()
{
  DALI_CHECK_FAIL( !gResourceReadySignalFired, "ResourceReadySignal is failed to connect the callback." );
  DaliLog::PrintPass();
}

void VTImageViewIsResourceReady( ImageView& imageView )
{
  DALI_CHECK_FAIL( !imageView.IsResourceReady(), "IsResourceReady is returned which not expected" );
  DaliLog::PrintPass();
}

/**
 * @testcase            UtcDaliImageViewConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliImageViewConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliImageViewNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewNewWithImageP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliImageViewNewWithImageP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_NEW_WITH_IMAGE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewNewWithUrlP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliImageViewNewWithUrlP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_NEW_WITH_URL_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewNewWithUrlAndSizeP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliImageViewNewWithUrlAndSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_NEW_WITH_URL_SIZE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliImageViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_COPY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliImageViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewDownCastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliImageViewDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_DOWNCAST_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewDownCastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliImageViewDownCastN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_DOWNCAST_N);
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliImageViewSetAndGetImageP
 * @since_tizen         2.4
 * @description         Set and Get the Image with image
 */

int UtcDaliImageViewSetAndGetImageP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_SET_GET_IMAGE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewSetAndGetImageP2
 * @since_tizen         2.4
 * @description         Set and Get the Image with actor
 */

int UtcDaliImageViewSetAndGetImageP2(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_SET_GET_IMAGE_P2);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewSetAndGetImageP3
 * @since_tizen         3.0
 * @description         Set and Get the Image with actor
 */

int UtcDaliImageViewSetAndGetImageP3(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_SET_GET_IMAGE_P3);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewSetGetPropertyImage
 * @since_tizen         2.4
 * @description         Checks set and get property Image
 */
int UtcDaliImageViewSetGetPropertyImage(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_SET_GET_PROPERTY_IMAGE);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewResourceReadySignalP
 * @since_tizen         4.0
 * @description         Checks whether ResourceReadySignal can emmit and call to callback function.
 */
int UtcDaliImageViewResourceReadySignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_RESOURCE_READY_SIGNAL_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliImageViewIsResourceReady
 * @since_tizen         4.0
 * @description.........Query whether an resource is ready.
 */
int UtcDaliImageViewIsResourceReady(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ImageView_TestApp testApp( application, IMAGE_VIEW_IS_RESOURCE_READY);
  application.MainLoop();

  return test_return_value;
}