#include "utc-dali-capture-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function    utc_Dali_Capture_startup
 * @description Called before each test
 * @parameter   NA
 * @return      NA
 */


void utc_Dali_Capture_startup(void)
{
  test_return_value=0;
}

/**
 * @function    utc_Dali_Capture_cleanup
 * @description Called after each test
 * @parameter   NA
 * @return      NA
 */

void utc_Dali_Capture_cleanup(void)
{
}

namespace
{
enum CaptureTestCase
{
  CONSTRUCTOR_P,
  NEW_P,
  NEW_CAMERA_P,
  COPY_CONSTRUCTOR_P,
  OPERATOR_ASSIGNMENT_P,
  DOWNCAST_P,
  START_P,
  START_COLOR_P,
  START_COLOR_AND_QUALITY_P,
  RETURN_NATIVE_IMAGE_SOURCE_P,
  START_COLOR_AND_QUALITY_N,
  RETURN_NATIVE_IMAGE_SOURCE_N,
  FINISHED_SIGNAL_N
};

struct CaptureTestApp : public ConnectionTracker
{
  CaptureTestApp( Application& app, int testCase )
  : mApplication( app ),
    mTestCase( testCase ),
    mFinished( false )
  {
    mApplication.InitSignal().Connect( this, &CaptureTestApp::OnInit );
  }

  Actor CreateSolidColor(const Vector4& color)
  {
    Toolkit::Control control = Toolkit::Control::New();

    Property::Map map;
    map[ Toolkit::Visual::Property::TYPE ] = Toolkit::Visual::COLOR;
    map[ Toolkit::ColorVisual::Property::MIX_COLOR ] = color;
    control.SetProperty( Toolkit::Control::Property::BACKGROUND, map );

    return control;
  }

  void OnInit( Application& app )
  {
    mStage = Stage::GetCurrent();
    mStageSize = mStage.GetSize();

    mRoot = CreateSolidColor(Color::WHITE);
    mRoot.SetColor(Color::BLACK);
    mRoot.SetParentOrigin(ParentOrigin::CENTER);
    mRoot.SetAnchorPoint(AnchorPoint::CENTER);
    mRoot.SetSize(mStageSize);
    mStage.Add(mRoot);

    ExcuteTest();

    mTimer = Timer::New( 1000 );
    mTimer.TickSignal().Connect( this, &CaptureTestApp::Tick );
    mTimer.Start();

    if( mTestCase == FINISHED_SIGNAL_N || mTestCase == START_COLOR_AND_QUALITY_N )
    {
      mCapture = Capture::New();
      mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );
    }

  }

  bool Tick()
  {
    Validate();

    mTimer.Stop();
    mApplication.Quit();
    return true;
  }

  void OnFinished( Capture capture, Capture::FinishState state )
  {
    mFinished = true;
  }

  void ExcuteTest()
  {
    switch( mTestCase )
    {
      case CONSTRUCTOR_P:
        TestConstructor();
        break;
      case NEW_P:
        TestNew();
        break;
      case NEW_CAMERA_P:
        TestNewCamera();
        break;
      case COPY_CONSTRUCTOR_P:
        TestCopyCOnstructor();
        break;
      case OPERATOR_ASSIGNMENT_P:
        TestOperatorAssignment();
        break;
      case DOWNCAST_P:
        TestDownCast();
        break;
      case START_P:
        TestStart();
        break;
      case START_COLOR_P:
        TestStartWithColor();
        break;
      case START_COLOR_AND_QUALITY_P:
        TestStartWithColorAndQuality();
        break;
      case RETURN_NATIVE_IMAGE_SOURCE_P:
        TestStart();
        break;
      case START_COLOR_AND_QUALITY_N:
        TestStartWithColorAndQualityForNegative();
        break;
      case RETURN_NATIVE_IMAGE_SOURCE_N:
        TestNew();
        break;
      case FINISHED_SIGNAL_N:
        TestFinishedSignal();
        break;
    }
  }

  void Validate()
  {
    switch( mTestCase )
    {
      case START_P:
        CheckFinishedSignal();
        break;
      case START_COLOR_P:
        CheckFinishedSignal();
        break;
      case START_COLOR_AND_QUALITY_P:
        CheckFinishedSignal();
        break;
      case RETURN_NATIVE_IMAGE_SOURCE_P:
        CheckFinishedSignalAndNativeImageSource();
        break;
      case START_COLOR_AND_QUALITY_N:
        ValidateFinished();
        break;
      case RETURN_NATIVE_IMAGE_SOURCE_N:
        ValidateFinished();
        break;
      case FINISHED_SIGNAL_N:
        ValidateFinished();
        break;
    }
  }

  void TestConstructor()
  {
    Capture capture;
    DALI_CHECK_FAIL( capture, "Constructor test is failed." );

    DaliLog::PrintPass();
  }

  void TestNew()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );
    DaliLog::PrintPass();
  }

  void TestNewCamera()
  {
    CameraActor cameraActor;
    mCapture = Capture::New( cameraActor );
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );
    DaliLog::PrintPass();
  }

  void TestCopyCOnstructor()
  {
    mCapture = Capture::New();
    Capture copy( mCapture );
    DALI_CHECK_FAIL( !copy, "Copy constructor test is failed." );
    DaliLog::PrintPass();
  }

  void TestOperatorAssignment()
  {
    mCapture = Capture::New();
    Capture copy = mCapture;
    DALI_CHECK_FAIL( !copy, "Copy constructor test is failed." );
    DaliLog::PrintPass();
  }

  void TestDownCast()
  {
    mCapture = Capture::New();
    BaseHandle obj( mCapture );
    Capture capture = Capture::DownCast( obj );
    DALI_CHECK_FAIL( !capture, "Capture::DownCast is failed." );
    DaliLog::PrintPass();
  }

  void TestStart()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );

    mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );
    mCapture.Start( mRoot, mStageSize, "/tmp/capture.png" );
  }

  void TestStartWithColor()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );

    mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );
    mCapture.Start( mRoot, mStageSize, "/tmp/capture.png", Color::RED );
  }

  void TestStartWithColorAndQuality()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );

    mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );
    mCapture.Start( mRoot, mStageSize, "/tmp/capture.jpg", Color::RED, 50 );
  }

  void TestStartWithColorAndQualityForNegative()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );

    mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );

    Actor source;

    try{
      mCapture.Start( source, mStageSize, "/tmp/capture.png", Color::RED, 50 );
    }
    catch( ... )
    {
    }
  }

  void TestFinishedSignal()
  {
    mCapture = Capture::New();
    DALI_CHECK_FAIL( !mCapture, "Capture::New() is failed." );

    mCapture.FinishedSignal().Connect( this, &CaptureTestApp::OnFinished );

    Actor source;

    try{
      mCapture.Start( source, mStageSize, "/tmp/capture.png" );
    }
    catch( ... )
    {
    }
  }

  void CheckFinishedSignal()
  {
    DALI_CHECK_FAIL( !mFinished, "Finished is failed." );
    DaliLog::PrintPass();
  }

  void CheckFinishedSignalAndNativeImageSource()
  {
    DALI_CHECK_FAIL( !mFinished, "Finished is failed." );
    Dali::NativeImageSourcePtr nativeImageSource = mCapture.GetNativeImageSource();
    DALI_CHECK_FAIL( !nativeImageSource, "GetNativeImageSource is failed ");
    DaliLog::PrintPass();
  }

  void CheckNativeImageSourceForNegative()
  {
    Dali::NativeImageSourcePtr nativeImageSource = mCapture.GetNativeImageSource();
    DALI_CHECK_FAIL( nativeImageSource, "GetNativeImageSource is failed ");
    DaliLog::PrintPass();
  }

  void ValidateFinished()
  {
    DALI_CHECK_FAIL( mFinished, "Finished negative test is failed." );
    DaliLog::PrintPass();
  }

  Application& mApplication;
  int mTestCase;
  Stage mStage;
  Vector2 mStageSize;
  Actor mRoot;
  Timer mTimer;
  Capture mCapture;
  bool mFinished;
};

} // namespace

/**
 * @testcase            UtcDaliCaptureConstructorP
 * @since_tizen         4.0
 * @description         Checks constructor
 */
int UtcDaliCaptureConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureNewP
 * @since_tizen         4.0
 * @description         Checks New
 */
int UtcDaliCaptureNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureNewCameraP
 * @since_tizen         4.0
 * @description         Checks New with cameraActor as input
 */
int UtcDaliCaptureNewCameraP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, NEW_CAMERA_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureCopyConstructorP
 * @since_tizen         4.0
 * @description         Checks copy constructor
 */
int UtcDaliCaptureCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureAssignmentP
 * @since_tizen         4.0
 * @description         Checks operator=
 */
int UtcDaliCaptureAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureDownCastP
 * @since_tizen         4.0
 * @description         Checks DownCast
 */
int UtcDaliCaptureDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureStartP
 * @since_tizen         4.0
 * @description         Checks Start
 */
int UtcDaliCaptureStartP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, START_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureStartColorP
 * @since_tizen         4.0
 * @description         Checks Start with color value as input
 */
int UtcDaliCaptureStartColorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, START_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureStartColorAndQualityP
 * @since_tizen         6.0
 * @description         Checks Start with color and jpeg quality value as input
 */
int UtcDaliCaptureStartColorAndQualityP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, START_COLOR_AND_QUALITY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureReturnNativeImageSourceP
 * @since_tizen         6.0
 * @description         Checks Return nativeImageSource
 */
int UtcDaliCaptureReturnNativeImageSourceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, RETURN_NATIVE_IMAGE_SOURCE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureStartColorAndQualityN
 * @since_tizen         6.0
 * @description         Checks Start with color and jpeg quality value as input
 */
int UtcDaliCaptureStartColorAndQualityN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, START_COLOR_AND_QUALITY_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureReturnNativeImageSourceN
 * @since_tizen         6.0
 * @description         Checks Return nativeImageSource
 */
int UtcDaliCaptureReturnNativeImageSourceN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, RETURN_NATIVE_IMAGE_SOURCE_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliCaptureFinishedN
 * @since_tizen         4.0
 * @description         Checks FinishedSignal
 */
int UtcDaliCaptureFinishedN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  CaptureTestApp testApp( application, FINISHED_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}
