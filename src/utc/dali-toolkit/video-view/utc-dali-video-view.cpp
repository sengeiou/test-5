#include "utc-dali-video-view-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

std::string TEST_VIDEO;
static const char* TEST_VIDEO_FILE =  "daliTestVideo.mp4";

/**
 * @function            utc_Dali_VideoView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_VideoView_startup(void)
{
  test_return_value=0;

  char* pathPtr = getAppDataPath();
  if( pathPtr == NULL )
  {
    TEST_VIDEO = "/usr/apps/core-dali-toolkit-tests/data";
  }
  else
  {
    TEST_VIDEO = pathPtr;
  }
  TEST_VIDEO += "/";
  TEST_VIDEO += TEST_VIDEO_FILE;
}

/**
 * @function            utc_Dali_VideoView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_VideoView_cleanup(void)
{
}

namespace
{
const char* const VOLUME_LEFT( "volumeLeft" );
const char* const VOLUME_RIGHT( "volumeRight" );

enum VideoViewTestCase
{
  CONSTRUCTOR_P,
  NEW_P,
  NEW_URL_P,
  NEW_CODEC_P,
  NEW_URL_CODEC_P,
  COPY_CONSTRUCTOR_P,
  OPERATOR_ASSIGNMENT_P,
  DOWNCAST_P,
  PROPERTY_VIDEO_P,
  PROPERTY_LOOPING_P,
  PROPERTY_MUTED_P,
  PROPERTY_VOLUME_P,
  PLAY_N,
  STOP_N,
  PAUSE_N,
  FORWARD_N,
  BACKWARD_N,
  FINISHED_SIGNAL_N,
  UNDERLAY_P,
  PROPERTY_PLAY_POSITION_P,
  DISPLAY_MODE_P
};

struct VideoViewTestApp : public ConnectionTracker
{
  VideoViewTestApp( Application& app, int testCase )
    : mApplication( app ),
    mTestCase( testCase ),
    mFinished( false )
  {
    mApplication.InitSignal().Connect( this, &VideoViewTestApp::OnInit );
  }

  void OnInit(Application& app)
  {
    if( CONSTRUCTOR_P == mTestCase )
    {
      DALI_CHECK_FAIL( mView, "VideoView default handle is not empty." );
      DaliLog::PrintPass();

      mTimer = Timer::New( 100 );
      mTimer.TickSignal().Connect( this, &VideoViewTestApp::Tick );
      mTimer.Start();

      return;
    }

    switch( mTestCase )
    {
      case NEW_URL_P :
        mView = VideoView::New( TEST_VIDEO );
        break;
      case NEW_CODEC_P :
        mView = VideoView::New( true );
        break;
      case NEW_URL_CODEC_P :
        mView = VideoView::New( TEST_VIDEO, true );
        break;
      default :
        mView = VideoView::New();
        break;
    }
    DALI_CHECK_FAIL( !mView, "VideoView::New is failed" );
    mFinished = false;

    mView.SetParentOrigin( ParentOrigin::CENTER );
    mView.SetAnchorPoint( AnchorPoint::CENTER );
    mView.SetResizePolicy( ResizePolicy::USE_NATURAL_SIZE, Dimension::ALL_DIMENSIONS );
    mView.SetSize( 100, 100 );
    Stage::GetCurrent().Add( mView );
    mView.SetProperty( VideoView::Property::VIDEO, TEST_VIDEO );

    mTimer = Timer::New( 1000 );
    mTimer.TickSignal().Connect( this, &VideoViewTestApp::Tick );
    mTimer.Start();

    if( mTestCase == FINISHED_SIGNAL_N )
    {
      mView.FinishedSignal().Connect( this, &VideoViewTestApp::OnFinished );
      DALI_TEST_CHECK( !mFinished );
    }

    ExcuteTest();
  }

  bool Tick()
  {
    Validate();

    mTimer.Stop();
    mApplication.Quit();
    return true;
  }

  void OnFinished( VideoView& view )
  {
    mFinished = true;
  }

  void NewP();
  void CopyConstructorP();
  void OperatorAssignmentP();
  void DownCastP();
  void PropertyVideoP();
  void PropertyLoopingP();
  void ValidatePropertyLoopingP();
  void PropertyMutedP();
  void ValidatePropertyMutedP();
  void PropertyVolumeP();
  void PlayN();
  void StopN();
  void PauseN();
  void ForwardN();
  void BackwardN();
  void ValidateFinishedSignalN();
  void CheckPropertyUnderlay();
  void PropertyPlayPositionP();
  void DisplayModeP();

  void ExcuteTest()
  {
    switch (mTestCase)
    {
      case NEW_P:
        NewP();
        break;
      case NEW_URL_P:
        NewP();
        break;
      case NEW_CODEC_P:
        NewP();
        break;
      case NEW_URL_CODEC_P:
        NewP();
        break;
      case COPY_CONSTRUCTOR_P:
        CopyConstructorP();
        break;
      case OPERATOR_ASSIGNMENT_P:
        OperatorAssignmentP();
        break;
      case DOWNCAST_P:
        DownCastP();
        break;
      case PROPERTY_LOOPING_P:
        PropertyLoopingP();
        break;
      case PROPERTY_MUTED_P:
        PropertyMutedP();
        break;
      case FINISHED_SIGNAL_N:
        PlayN();
        break;
      case UNDERLAY_P:
        CheckPropertyUnderlay();
        break;
    }
  }

  void Validate()
  {
    switch (mTestCase)
    {
      case PROPERTY_VIDEO_P:
        PropertyVideoP();
        break;
      case PROPERTY_LOOPING_P:
        ValidatePropertyLoopingP();
        break;
      case PROPERTY_MUTED_P:
        ValidatePropertyMutedP();
        break;
      case PROPERTY_VOLUME_P:
        PropertyVolumeP();
        break;
      case PLAY_N:
        PlayN();
        break;
      case PAUSE_N:
        PauseN();
        break;
      case STOP_N:
        StopN();
        break;
      case FORWARD_N:
        ForwardN();
        break;
      case BACKWARD_N:
        BackwardN();
        break;
      case FINISHED_SIGNAL_N:
        ValidateFinishedSignalN();
        break;
      case PROPERTY_PLAY_POSITION_P:
        PropertyPlayPositionP();
        break;
      case DISPLAY_MODE_P:
        DisplayModeP();
        break;

    }
  }

  Application& mApplication;
  int mTestCase;
  Timer mTimer;
  VideoView mView;
  bool mFinished;
};

} // namespace

void VideoViewTestApp::NewP()
{
  DALI_CHECK_FAIL( !mView, "VideoView::New() is failed." );

  DaliLog::PrintPass();
}

void VideoViewTestApp::CopyConstructorP()
{
  VideoView copy( mView );
  DALI_CHECK_FAIL( !copy, "VideoView::VideoView(const VideoView&) is failed." );

  DaliLog::PrintPass();
}

void VideoViewTestApp::OperatorAssignmentP()
{
  VideoView copy = mView;
  DALI_CHECK_FAIL( !copy, "VideoView::VideoView(const VideoView&) is failed." );

  DaliLog::PrintPass();
}

void VideoViewTestApp::DownCastP()
{
  BaseHandle object( mView );

  VideoView view2 = VideoView::DownCast( object );
  DALI_CHECK_FAIL( !view2, "VideoView::DownCast is failed." );

  DaliLog::PrintPass();
}

void VideoViewTestApp::PropertyVideoP()
{
  std::string file;
  Property::Value val = mView.GetProperty( VideoView::Property::VIDEO );
  DALI_TEST_CHECK( val.Get( file ) );
  DALI_TEST_CHECK( file == TEST_VIDEO );
  DaliLog::PrintPass();
}

void VideoViewTestApp::PropertyLoopingP()
{
  bool looping;
  Property::Value val = mView.GetProperty( VideoView::Property::LOOPING );
  DALI_TEST_CHECK( val.Get( looping ) );
  DALI_TEST_CHECK( !looping );

  mView.SetProperty( VideoView::Property::LOOPING, true );
}

void VideoViewTestApp::ValidatePropertyLoopingP()
{
  bool looping;
  Property::Value val = mView.GetProperty( VideoView::Property::LOOPING );
  DALI_TEST_CHECK( val.Get( looping ) );
  DALI_TEST_CHECK( looping );
  DaliLog::PrintPass();
}

void VideoViewTestApp::PropertyMutedP()
{
  bool muted;
  Property::Value val = mView.GetProperty( VideoView::Property::MUTED );
  DALI_TEST_CHECK( val.Get( muted ) );
  DALI_TEST_CHECK( !muted );

  mView.SetProperty( VideoView::Property::MUTED, true );
}

void VideoViewTestApp::ValidatePropertyMutedP()
{
  bool muted;
  Property::Value val = mView.GetProperty( VideoView::Property::MUTED );
  DALI_TEST_CHECK( val.Get( muted ) );
  DALI_TEST_CHECK( muted );
  DaliLog::PrintPass();
}

void VideoViewTestApp::PropertyVolumeP()
{
  float left, right;
  left = right = 0.f;

  Property::Map map;
  map.Insert( VOLUME_LEFT, 0.5f );
  map.Insert( VOLUME_RIGHT, 0.5f );

  mView.SetProperty( VideoView::Property::VOLUME, map );
  Property::Value val = mView.GetProperty( VideoView::Property::VOLUME );

  Property::Map map2;
  DALI_TEST_CHECK( val.Get( map2 ) );

  Property::Value* volumeLeft = map2.Find( VOLUME_LEFT );
  Property::Value* volumeRight = map2.Find( VOLUME_RIGHT );

  DALI_TEST_CHECK( volumeLeft && volumeLeft->Get( left ) );
  DALI_TEST_CHECK( volumeRight && volumeRight->Get( right ) );
  DALI_TEST_CHECK( left == 0.5f );
  DALI_TEST_CHECK( right == 0.5f );
  DaliLog::PrintPass();
}

void VideoViewTestApp::PlayN()
{
  try
  {
    mView.SetProperty( VideoView::Property::VIDEO, "" );
    mView.Play();
  }
  catch( ... )
  {
    DALI_TEST_CHECK( false );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::PauseN()
{
  try
  {
    mView.Pause();
  }
  catch( ... )
  {
    DALI_TEST_CHECK( false );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::StopN()
{
  try
  {
    mView.Stop();
  }
  catch( ... )
  {
    DALI_TEST_CHECK( false );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::ForwardN()
{
  try
  {
    mView.Forward( 1000 );
    sleep( 1 );
  }
  catch( ... )
  {
    DALI_TEST_CHECK( false );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::BackwardN()
{
  try
  {
    mView.Backward( 1000 );
    sleep( 1 );
  }
  catch( ... )
  {
    DALI_TEST_CHECK( false );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::ValidateFinishedSignalN()
{
  DALI_TEST_CHECK( !mFinished );
  DaliLog::PrintPass();
}

void VideoViewTestApp::CheckPropertyUnderlay()
{
  bool featureFlag = true;
  int error = SYSTEM_INFO_ERROR_NONE;
  bool check = false;

  error = system_info_get_platform_bool( "tizen.org/feature/multimedia.raw_video", &featureFlag );

  if( error != SYSTEM_INFO_ERROR_NONE )
  {
    DALI_TEST_CHECK( false );
  }

  mView.SetProperty( Toolkit::VideoView::Property::UNDERLAY, false );
  check = mView.GetProperty( Toolkit::VideoView::Property::UNDERLAY ).Get< bool >();

  if( featureFlag )
  {
    DALI_TEST_CHECK( !check );
  }
  else
  {
    DALI_TEST_CHECK( check );
  }
  DaliLog::PrintPass();
}

void VideoViewTestApp::PropertyPlayPositionP()
{
  int playPos;

  mView.SetProperty( VideoView::Property::PLAY_POSITION, 10 );

  playPos = mView.GetProperty( VideoView::Property::PLAY_POSITION ).Get< int >();

  DALI_TEST_CHECK( playPos == 10  );
  DaliLog::PrintPass();
}

void VideoViewTestApp::DisplayModeP()
{
  int displayMode;

  mView.SetProperty( VideoView::Property::DISPLAY_MODE, VideoView::DisplayMode::FULL_SCREEN );

  displayMode = mView.GetProperty( VideoView::Property::DISPLAY_MODE ).Get< int >();

  DALI_TEST_CHECK( displayMode == VideoView::DisplayMode::FULL_SCREEN  );
  DaliLog::PrintPass();
}


/**
 * @testcase            UtcDaliVideoViewConstructorP
 * @since_tizen         3.0
 * @description         Checks correct creation of an object
 */

int UtcDaliVideoViewConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewNewP
 * @since_tizen         3.0
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliVideoViewNewP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, NEW_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewNewUrlP
 * @since_tizen         3.0
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliVideoViewNewUrlP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, NEW_URL_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewCopyConstructorP
 * @since_tizen         3.0
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliVideoViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, COPY_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewOperatorAssignmentP
 * @since_tizen         3.0
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliVideoViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewDownCastP
 * @since_tizen         3.0
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliVideoViewDownCastP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, DOWNCAST_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyVideoP
 * @since_tizen         3.0
 * @description         Checks set and get property VIDEO
 */
int UtcDaliVideoViewPropertyVideoP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PROPERTY_VIDEO_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyLoopingP
 * @since_tizen         3.0
 * @description         Checks set and get property LOOPING
 */
int UtcDaliVideoViewPropertyLoopingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PROPERTY_LOOPING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyMutedP
 * @since_tizen         3.0
 * @description         Checks set and get property MUTED
 */
int UtcDaliVideoViewPropertyMutedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PROPERTY_MUTED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyVolumeP
 * @since_tizen         3.0
 * @description         Checks set and get property VOLUME
 */
int UtcDaliVideoViewPropertyVolumeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PROPERTY_VOLUME_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPlayN
 * @since_tizen         3.0
 * @description         Checks Play()
 */
int UtcDaliVideoViewPlayN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PLAY_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewStopN
 * @since_tizen         3.0
 * @description         Checks Stop()
 */
int UtcDaliVideoViewStopN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, STOP_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPauseN
 * @since_tizen         3.0
 * @description         Checks Pause()
 */
int UtcDaliVideoViewPauseN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PAUSE_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewForwardN
 * @since_tizen         3.0
 * @description         Checks Forward()
 */
int UtcDaliVideoViewForwardN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, FORWARD_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewBackwardN
 * @since_tizen         3.0
 * @description         Checks Backward()
 */
int UtcDaliVideoViewBackwardN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, BACKWARD_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewFinishedSignalN
 * @since_tizen         3.0
 * @description         Checks FinishedSignal
 */
int UtcDaliVideoViewFinishedSignalN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, FINISHED_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyUnderlayP
 * @since_tizen         4.0
 * @description         Checks Property::UNDERLAY
 */
int UtcDaliVideoViewPropertyUnderlayP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, UNDERLAY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewNewSWCodecP
 * @since_tizen         4.0
 * @description         Checks correct allocation of memory to object and setting sw codec
 */

int UtcDaliVideoViewNewSWCodecP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, NEW_CODEC_P);
  application.MainLoop();

  return test_return_value;
}
/**
 * @testcase            UtcDaliVideoViewNewUrlP
 * @since_tizen         4.0
 * @description         Checks correct allocation of memory to object and setting sw codec
 */

int UtcDaliVideoViewNewUrlSWCodecP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, NEW_URL_CODEC_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyPlayPositionP
 * @since_tizen         4.0
 * @description         Checks Property::PLAY_POSITION
 */
int UtcDaliVideoViewPropertyPlayPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, PROPERTY_PLAY_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliVideoViewPropertyDisplayModeP
 * @since_tizen         4.0
 * @description         Checks Property::DISPLAY_MODE
 */
int UtcDaliVideoViewPropertyDisplayModeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  VideoViewTestApp testApp( application, DISPLAY_MODE_P );
  application.MainLoop();

  return test_return_value;
}

