#include "utc-dali-ttsplayer-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;


/**
 * @function        utc_Dali_TtsPlayer_startup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */

void utc_Dali_TtsPlayer_startup(void)
{
  test_return_value=0;
}

/**
 * @function        utc_Dali_TtsPlayer_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */


void utc_Dali_TtsPlayer_cleanup(void)
{
}


void TtsPlayerGetStateN();
void TtsPlayerPlayN(void);
void TtsPlayerPauseN(void);
void TtsPlayerStopN(void);
void TtsPlayerResumeN(void);
void TtsPlayerGetP(void);
void TtsPlayerConstructorP(void);
void TtsPlayerCopyConstructorP(void);
void TtsPlayerAssignmentOperatorP(void);

namespace
{
  enum TEST_CASES_LIST_TTS_PLAYER
  {
    TTS_PLAYER_GET_STATE_N,
    TTS_PLAYER_PLAY_N,
    TTS_PLAYER_PAUSE_N,
    TTS_PLAYER_STOP_N,
    TTS_PLAYER_RESUME_N,
    TTS_PLAYER_GET_P,
    TTS_PLAYER_CONSTRUCTOR_P,
    TTS_PLAYER_COPY_CONSTRUCTOR_P,
    TTS_PLAYER_ASSIGNMENT_OPERATOR_P
  };

  struct TtsPlayer_TestApp : public ConnectionTracker
  {
    TtsPlayer_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TtsPlayer_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TtsPlayer_TestApp::Tick );
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
        case TTS_PLAYER_GET_STATE_N:
          TtsPlayerGetStateN();
          break;

        case TTS_PLAYER_PLAY_N:
          TtsPlayerPlayN();
          break;

        case TTS_PLAYER_PAUSE_N:
          TtsPlayerPauseN();
          break;

        case TTS_PLAYER_STOP_N:
          TtsPlayerStopN();
          break;

        case TTS_PLAYER_RESUME_N:
          TtsPlayerResumeN();
          break;

        case TTS_PLAYER_GET_P:
          TtsPlayerGetP();
          break;

        case TTS_PLAYER_CONSTRUCTOR_P:
          TtsPlayerConstructorP();
          break;

        case TTS_PLAYER_COPY_CONSTRUCTOR_P:
          TtsPlayerCopyConstructorP();
          break;

        case TTS_PLAYER_ASSIGNMENT_OPERATOR_P:
          TtsPlayerAssignmentOperatorP();
          break;
      }
    }

    // Data
    Application& mApplication;
    int mTestCase;
    Timer mTimer;
  };

}

void TtsPlayerConstructorP(void)
{
  Dali::TtsPlayer player;
  DALI_CHECK_FAIL(player,"TtsPlayer::ConstructorP is failing");

  DaliLog::PrintPass();
}

void TtsPlayerCopyConstructorP(void)
{
  Dali::TtsPlayer player;
  DALI_CHECK_FAIL(player,"TtsPlayer::CopyConstructorP is failing");

  Dali::TtsPlayer copy( player );

  DALI_CHECK_FAIL(copy != player,"TtsPlayer::CopyConstructorP is failing")

    DaliLog::PrintPass();
}

void TtsPlayerAssignmentOperatorP(void)
{
  Dali::TtsPlayer player;
  DALI_CHECK_FAIL(player,"TtsPlayer::AssignmentOperatorP is failing");

  Dali::TtsPlayer copy;
  DALI_CHECK_FAIL(player,"TtsPlayer::AssignmentOperatorP is failing");

  copy = player;
  DALI_CHECK_FAIL(copy != player,"AssignmentOperatorP is failing")

    DaliLog::PrintPass();
}

void TtsPlayerGetP(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();
  DALI_CHECK_FAIL(!player,"TtsPlayer::GetP is failing");

  Dali::TtsPlayer::Mode  mode = Dali::TtsPlayer::DEFAULT;
  player = Dali::TtsPlayer::Get(mode);
  DALI_CHECK_FAIL(!player,"TtsPlayer::GetP is failing");

  DaliLog::PrintPass();
}

void TtsPlayerResumeN(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();

  try
  {
    player.Resume();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"TtsPlayer::ResumeN is failing");
  }

  DaliLog::PrintPass();
}

void TtsPlayerPlayN(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();

  try
  {
    player.Play("text");
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"TtsPlayer::PlayN is failing");
  }

  DaliLog::PrintPass();
}


void TtsPlayerStopN(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();

  try
  {
    player.Stop();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"TtsPlayer::StopN is failing");
  }

  DaliLog::PrintPass();
}


void TtsPlayerPauseN(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();

  try
  {
    player.Pause();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"TtsPlayer::PauseN is failing");
  }

  DaliLog::PrintPass();
}

void TtsPlayerGetStateN(void)
{
  Dali::TtsPlayer player = Dali::TtsPlayer::Get();

  try
  {
    Dali::TtsPlayer::State state = player.GetState();
  }
  catch( ... )
  {
    DALI_CHECK_FAIL(true,"TtsPlayer::GetStateN is failing");
  }

  DaliLog::PrintPass();
}


/**
 * @testcase        UtcDaliTtsPlayerConstructorP
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::ConstructorP() functionality
 */

int UtcDaliTtsPlayerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerCopyConstructorP
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::CopyConstructorP() functionality
 */

int UtcDaliTtsPlayerCopyConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_COPY_CONSTRUCTOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerAssignmentOperatorP
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::AssignmentOperatorP() functionality
 */

int UtcDaliTtsPlayerAssignmentOperatorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_ASSIGNMENT_OPERATOR_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerGetP
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::PlayerGetP() functionality
 */

int UtcDaliTtsPlayerGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_GET_P);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerResumeN
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::PlayerResumeN() functionality
 */

int UtcDaliTtsPlayerResumeN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_RESUME_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerPlayN
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::PlayerPlayN() functionality
 */

int UtcDaliTtsPlayerPlayN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_PLAY_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerPauseN
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::PlayerPauseN() functionality
 */

int UtcDaliTtsPlayerPauseN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_PAUSE_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerStopN
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::StopN() functionality
 */

int UtcDaliTtsPlayerStopN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_STOP_N);
  application.MainLoop();
  return test_return_value;
}

/**
 * @testcase        UtcDaliTtsPlayerGetStateN
 * @since_tizen     2.4
 * @description     checks for TtsPlayer::GetStateN() functionality
 */

int UtcDaliTtsPlayerGetStateN(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TtsPlayer_TestApp testApp( application, TTS_PLAYER_GET_STATE_N);
  application.MainLoop();
  return test_return_value;
}

