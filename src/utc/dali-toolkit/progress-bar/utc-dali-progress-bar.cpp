#include "utc-dali-progress-bar-common.h"


//& set: PushButton
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ProgressBar_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ProgressBar_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ProgressBar_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ProgressBar_cleanup(void)
{
}

void ProgressBarNew(void);
void ProgressBarConstructorP(void);
void ProgressBarCopyConstructorP(void);
void ProgressBarOperatorAssignmentP(void);
void ProgressBarDownCastP(void);
void ProgressBarDownCastN(void);
void ProgressBarValueChangedSignal(void);
void ProgressBarPropertyTrackVisualImage(void);
void ProgressBarPropertyTrackVisualColor(void);
void ProgressBarPropertyProgressVisual(void);
void ProgressBarPropertySecondaryProgressVisual(void);
void ProgressBarPropertyIndeterminateVisual(void);
void ProgressBarPropertyLabelVisual1(void);
void ProgressBarPropertyLabelVisual2(void);


class ValueChangedSignalHandler : public Dali::ConnectionTracker
{
  public:
    ValueChangedSignalHandler() :
      mCalls( 0 )
  {
  }

    void Callback( ProgressBar progressBar, float value, float secondaryValue )
    {
      mCalls++;
    }

    unsigned int GetCalls() const
    {
      return mCalls;
    }

  private:
    unsigned int mCalls;
};

namespace
{
  enum TEST_CASES_LIST_PROGRESS_BAR
  {
    PROGRESS_BAR_NEW,
    PROGRESS_BAR_CONSTRUCTOR_P,
    PROGRESS_BAR_COPY_CONSTRUCTOR_P,
    PROGRESS_BAR_OPERATOR_ASSIGNMENT_P,
    PROGRESS_BAR_DOWNCAST_P,
    PROGRESS_BAR_DOWNCAST_N,
    PROGRESS_BAR_VALUE_CHANGED_SIGNAL,
    PROGRESS_BAR_PROPERTY_TRACK_VISUAL_IMAGE,
    PROGRESS_BAR_PROPERTY_TRACK_VISUAL_COLOR,
    PROGRESS_BAR_PROPERTY_PROGRESS_VISUAL,
    PROGRESS_BAR_PROPERTY_SECONDARY_PROGRESS_VISUAL,
    PROGRESS_BAR_PROPERTY_INDETERMINATE_VISUAL,
    PROGRESS_BAR_PROPERTY_LABEL_VISUAL_1,
    PROGRESS_BAR_PROPERTY_LABEL_VISUAL_2
  };

  struct ProgressBar_TestApp : public ConnectionTracker
  {
    ProgressBar_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ProgressBar_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ProgressBar_TestApp::Tick );
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
        case PROGRESS_BAR_NEW:
        {
          ProgressBarNew();
          break;
        }
        case PROGRESS_BAR_CONSTRUCTOR_P:
        {
          ProgressBarConstructorP();
          break;
        }
        case PROGRESS_BAR_COPY_CONSTRUCTOR_P:
        {
          ProgressBarCopyConstructorP();
          break;
        }
        case PROGRESS_BAR_OPERATOR_ASSIGNMENT_P:
        {
          ProgressBarOperatorAssignmentP();
          break;
        }
        case PROGRESS_BAR_DOWNCAST_P:
        {
          ProgressBarDownCastP();
          break;
        }
        case PROGRESS_BAR_DOWNCAST_N:
        {
          ProgressBarDownCastN();
          break;
        }
        case PROGRESS_BAR_VALUE_CHANGED_SIGNAL:
        {
          ProgressBarValueChangedSignal();
          break;
        }
        case PROGRESS_BAR_PROPERTY_TRACK_VISUAL_IMAGE:
        {
          ProgressBarPropertyTrackVisualImage();
          break;
        }
        case PROGRESS_BAR_PROPERTY_TRACK_VISUAL_COLOR:
        {
          ProgressBarPropertyTrackVisualColor();
          break;
        }
        case PROGRESS_BAR_PROPERTY_PROGRESS_VISUAL:
        {
          ProgressBarPropertyProgressVisual();
          break;
        }
        case PROGRESS_BAR_PROPERTY_SECONDARY_PROGRESS_VISUAL:
        {
          ProgressBarPropertySecondaryProgressVisual();
          break;
        }
        case PROGRESS_BAR_PROPERTY_INDETERMINATE_VISUAL:
        {
          ProgressBarPropertyIndeterminateVisual();
          break;
        }
        case PROGRESS_BAR_PROPERTY_LABEL_VISUAL_1:
        {
          ProgressBarPropertyLabelVisual1();
          break;
        }
        case PROGRESS_BAR_PROPERTY_LABEL_VISUAL_2:
        {
          ProgressBarPropertyLabelVisual2();
          break;
        }
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

void ProgressBarNew(void)
{
  ProgressBar progressBar;
  progressBar = ProgressBar::New();

  DALI_CHECK_FAIL( !progressBar,  "progressBar::New() is failed .");

  DaliLog::PrintPass();
}

void ProgressBarConstructorP(void)
{
  ProgressBar progressBar;

  DALI_CHECK_FAIL( progressBar, "ProgressBar::ProgressBar() is failed.");

  DaliLog::PrintPass();
}

void ProgressBarCopyConstructorP(void)
{
  ProgressBar progressBar;
  progressBar = ProgressBar::New();
  ProgressBar progressBar2( progressBar );

  DALI_CHECK_FAIL( progressBar2 != progressBar,  "ProgressBar::ProgressBar(const ProgressBar&) is failed");

  DaliLog::PrintPass();
}

void ProgressBarOperatorAssignmentP(void)
{
  ProgressBar progressBar;
  progressBar = ProgressBar::New();
  ProgressBar progressBar2 = progressBar;

  DALI_CHECK_FAIL( progressBar2 != progressBar,  "ProgressBar::operator= is failed.");

  DaliLog::PrintPass();
}

void ProgressBarDownCastP(void)
{

  Handle handle = ProgressBar::New();

  DALI_CHECK_FAIL(!handle,  "progressBar::New() is failed .");

  ProgressBar progressBar = ProgressBar::DownCast( handle );
  DALI_CHECK_FAIL( !progressBar,  "downCastProgressBar is not valid object.");
  DALI_CHECK_FAIL( progressBar != handle,  "downCastProgressBar is failed to match with handle.");

  DaliLog::PrintPass();
}

void ProgressBarDownCastN(void)
{
  BaseHandle uninitializedObject;
  ProgressBar progressBar1 = ProgressBar::DownCast( uninitializedObject );
  DALI_CHECK_FAIL( progressBar1, "ProgressBar handle is not empty.");

  ProgressBar progressBar2 = DownCast< ProgressBar >( uninitializedObject );
  DALI_CHECK_FAIL( progressBar2, "ProgressBar handle is not empty after downcast.");

  DaliLog::PrintPass();
}

void ProgressBarValueChangedSignal(void)
{

  ValueChangedSignalHandler callback;

  // Create the ProgressBar actor
  ProgressBar progressBar = ProgressBar::New();
  Stage::GetCurrent().Add( progressBar );

  progressBar.ValueChangedSignal().Connect( &callback, &ValueChangedSignalHandler::Callback );

  progressBar.SetProperty(ProgressBar::Property::PROGRESS_VALUE, 0.2f);

  DALI_CHECK_FAIL( callback.GetCalls() != 1 , "ProgressBar::ValueChangedSignal() is failed." );


  progressBar.SetProperty(ProgressBar::Property::SECONDARY_PROGRESS_VALUE, 0.2f);

  DALI_CHECK_FAIL( callback.GetCalls() != 2 , "ProgressBar::ValueChangedSignal() is failed." );

  DaliLog::PrintPass();
}

void ProgressBarPropertyTrackVisualImage(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string imageUrl = "testUrl";

  Property::Map map;
  map[ "visualType" ] = "IMAGE";
  map[ Toolkit::ImageVisual::Property::URL ] = imageUrl;
  progressBar.SetProperty(ProgressBar::Property::TRACK_VISUAL, map);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::TRACK_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of TRACK_VISUAL map." );


  Property::Value* urlValue = resultMap->Find( Toolkit::ImageVisual::Property::URL );
  std::string urlString;
  urlValue->Get( urlString );

  DALI_CHECK_FAIL( urlString.empty() , "URL is empty which is not expected." );
  DALI_CHECK_FAIL( urlString != imageUrl , "URL value is not matched with expected value." );

  DaliLog::PrintPass();
}

void ProgressBarPropertyTrackVisualColor(void)
{
  ProgressBar progressBar = ProgressBar::New();

  Property::Map colorMap;
  colorMap["visualType"] = "COLOR";
  colorMap[Toolkit::ColorVisual::Property::MIX_COLOR] = Color::RED;
  progressBar.SetProperty(ProgressBar::Property::TRACK_VISUAL, colorMap);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::TRACK_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of TRACK_VISUAL map." );

  Property::Value* colorValue = resultMap->Find( Toolkit::ColorVisual::Property::MIX_COLOR );
  Vector4 color = Color::TRANSPARENT;
  colorValue->Get( color );

  DALI_CHECK_FAIL( color == Color::TRANSPARENT, "Color is transparent which is not expected." );
  DALI_CHECK_FAIL( color != Color::RED, "Color value is not matched with expected value" );

  DaliLog::PrintPass();
}

void ProgressBarPropertyProgressVisual(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string imageUrl = "testUrl";

  Property::Map map;
  map[Toolkit::ImageVisual::Property::URL] = imageUrl;
  progressBar.SetProperty(ProgressBar::Property::PROGRESS_VISUAL, map);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::PROGRESS_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of PROGRESS_VISUAL map." );

  Property::Value* urlValue = resultMap->Find( Toolkit::ImageVisual::Property::URL );
  std::string urlString;
  urlValue->Get( urlString );

  DALI_CHECK_FAIL( urlString.empty() , "urlString is empty which is not expected." );
  DALI_CHECK_FAIL( urlString != imageUrl , "URL value is not matched with expected value." );

  DaliLog::PrintPass();
}

void ProgressBarPropertySecondaryProgressVisual(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string imageUrl = "testUrl";

  Property::Map map;
  map[Toolkit::ImageVisual::Property::URL] = imageUrl;
  progressBar.SetProperty(ProgressBar::Property::SECONDARY_PROGRESS_VISUAL, map);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::SECONDARY_PROGRESS_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of SECONDARY_PROGRESS_VISUAL map." );

  Property::Value* urlValue = resultMap->Find( Toolkit::ImageVisual::Property::URL );
  std::string urlString;
  urlValue->Get( urlString );

  DALI_CHECK_FAIL( urlString.empty() , "urlString is empty which is not expected." );
  DALI_CHECK_FAIL( urlString != imageUrl , "URL value is not matched with expected value." );

  DaliLog::PrintPass();
}

void ProgressBarPropertyIndeterminateVisual(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string imageUrl = "testUrl";

  Property::Map map;
  map[Toolkit::ImageVisual::Property::URL] = imageUrl;
  progressBar.SetProperty(ProgressBar::Property::INDETERMINATE_VISUAL, map);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::INDETERMINATE_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of INDETERMINATE_VISUAL map." );

  Property::Value* urlValue = resultMap->Find( Toolkit::ImageVisual::Property::URL );
  std::string urlString;
  urlValue->Get( urlString );

  DALI_CHECK_FAIL( urlString.empty() , "urlString is empty which is not expected." );
  DALI_CHECK_FAIL( urlString != imageUrl , "URL value is not matched with expected value." );

  DaliLog::PrintPass();
}

void ProgressBarPropertyLabelVisual1(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string testString = "Hello World";

  progressBar.SetProperty(ProgressBar::Property::LABEL_VISUAL, testString);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::LABEL_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of LABEL_VISUAL map." );

  Property::Value* textValue = resultMap->Find(Toolkit::TextVisual::Property::TEXT);

  std::string textString;
  textValue->Get( textString );

  DALI_CHECK_FAIL( textString.empty() , "textString is empty which is not expected." );
  DALI_CHECK_FAIL( textString != testString , "Text value is not matched with expected value." );


  DaliLog::PrintPass();
}

void ProgressBarPropertyLabelVisual2(void)
{
  ProgressBar progressBar = ProgressBar::New();
  std::string testString = "Hello World";

  Property::Map textVisualMap2;
  textVisualMap2.Insert( Toolkit::Visual::Property::TYPE, Toolkit::Visual::TEXT );
  textVisualMap2.Insert( Toolkit::TextVisual::Property::TEXT, testString );
  textVisualMap2.Insert( Toolkit::TextVisual::Property::POINT_SIZE, 12.0f );
  progressBar.SetProperty(ProgressBar::Property::LABEL_VISUAL, textVisualMap2);

  Property::Value value = progressBar.GetProperty(ProgressBar::Property::LABEL_VISUAL);
  Property::Map* resultMap = value.GetMap();

  DALI_CHECK_FAIL( !resultMap , "ProgressBar fails to get the value of LABEL_VISUAL map." );

  Property::Value* textValue = resultMap->Find(Toolkit::TextVisual::Property::TEXT);

  std::string textString;
  textValue->Get( textString );

  DALI_CHECK_FAIL( textString.empty() , "textString is empty which is not expected." );
  DALI_CHECK_FAIL( textString != testString , "Text value is not matched with expected value." );

  DaliLog::PrintPass();
}



/**
 * @testcase            UtcDaliProgressBarNew
 * @since_tizen         4.0
 * @description         to check for the TextLabel::New() functionality
 */
int UtcDaliProgressBarNew(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_NEW );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarConstructorP
 * @since_tizen         4.0
 * @description         Checks correct creation of an object
 */
int UtcDaliProgressBarConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarCopyConstructorP
 * @since_tizen         4.0
 * @description         Checks correct creation of a copy of object
 */
int UtcDaliProgressBarCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarOperatorAssignmentP
 * @since_tizen         4.0
 * @description         Checks correct assigntment of one object to other object
 */
int UtcDaliProgressBarOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarDownCastP
 * @since_tizen         4.0
 * @description         Checks for correct downcasting of Base Handle
 */
int UtcDaliProgressBarDownCastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarDownCastN
 * @since_tizen         4.0
 * @description         Negative test for checking downcasting of Base Handle
 */
int UtcDaliProgressBarDownCastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarValueChangedSignal
 * @since_tizen         4.0
 * @description         Checks whether ValueChangedSignal can emmit and call to callback function.
 */
int UtcDaliProgressBarValueChangedSignal(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_VALUE_CHANGED_SIGNAL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyTrackVisualImage
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the TRACK_VISUAL property
 */
int UtcDaliProgressBarPropertyTrackVisualImage(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_TRACK_VISUAL_IMAGE );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyTrackVisualColor
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the TRACK_VISUAL property
 */
int UtcDaliProgressBarPropertyTrackVisualColor(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_TRACK_VISUAL_COLOR );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyProgressVisual
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the PROGRESS_VISUAL property
 */
int UtcDaliProgressBarPropertyProgressVisual(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_PROGRESS_VISUAL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertySecondaryProgressVisual
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the SECONDARY_PROGRESS_VISUAL property
 */
int UtcDaliProgressBarPropertySecondaryProgressVisual(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_SECONDARY_PROGRESS_VISUAL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyIndeterminateVisual
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the INDETERMINATE_VISUAL property
 */
int UtcDaliProgressBarPropertyIndeterminateVisual(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_INDETERMINATE_VISUAL );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyLabelVisual1
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the LABEL_VISUAL property
 */
int UtcDaliProgressBarPropertyLabelVisual1(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_LABEL_VISUAL_1 );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliProgressBarPropertyLabelVisual2
 * @since_tizen         4.0
 * @description         Checks test for correct setting and getting of the LABEL_VISUAL property
 */
int UtcDaliProgressBarPropertyLabelVisual2(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ProgressBar_TestApp testApp( application, PROGRESS_BAR_PROPERTY_LABEL_VISUAL_2 );
  application.MainLoop();

  return test_return_value;
}