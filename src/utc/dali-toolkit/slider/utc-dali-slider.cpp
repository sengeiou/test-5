#include "utc-dali-slider-common.h"

//& set: Slider
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Slider_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Slider_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Slider_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Slider_cleanup(void)
{

}

void SliderConstructorP();
void SliderCopyConstructorP();
void SliderDestructorP();
void SliderNewP();
void SliderOperatorAssignmentP();
void SliderDowncastP();
void SliderDowncastN();

namespace
{
  enum TEST_CASES_LIST_SLIDER
  {
    SLIDER_CONSTRUCTOR_P,
    SLIDER_COPY_CONSTRUCTOR_P,
    SLIDER_DESTRUCTOR_P,
    SLIDER_NEW_P,
    SLIDER_OPERATOR_ASSIGNMENT_P,
    SLIDER_DOWNCAST_P,
    SLIDER_DOWNCAST_N,
  };

  struct Slider_TestApp : public ConnectionTracker
  {
    Slider_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Slider_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Slider_TestApp::Tick );
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
        case SLIDER_CONSTRUCTOR_P:
          SliderConstructorP();
          break;

        case SLIDER_COPY_CONSTRUCTOR_P:
          SliderCopyConstructorP();
          break;

        case SLIDER_DESTRUCTOR_P:
          SliderDestructorP();
          break;

        case SLIDER_NEW_P:
          SliderNewP();
          break;

        case SLIDER_OPERATOR_ASSIGNMENT_P:
          SliderOperatorAssignmentP();
          break;

        case SLIDER_DOWNCAST_P:
          SliderDowncastP();
          break;

        case SLIDER_DOWNCAST_N:
          SliderDowncastN();
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


void SliderConstructorP()
{
  Slider slider;
  DALI_CHECK_FAIL( slider, "slider Default Contructor is failed." );

  DaliLog::PrintPass();
}

void SliderNewP()
{
  Slider slider = Slider::New();
  DALI_CHECK_FAIL( !slider, "Slider::New() is failed." );

  DaliLog::PrintPass();
}

void SliderCopyConstructorP()
{
  Slider slider = Slider::New();
  DALI_CHECK_FAIL( !slider, "Slider::New() is failed." );

  Slider copySlider( slider );
  DALI_CHECK_FAIL( slider != copySlider, "Copy Constructor do not work properly." );

  DaliLog::PrintPass();
}

void SliderDestructorP()
{
  Slider* slider = new Slider();
  delete slider;

  DALI_CHECK_FAIL( slider, "Destructor do not work properly." );
  DaliLog::PrintPass();
}

void SliderOperatorAssignmentP()
{
  Slider slider = Slider::New();
  DALI_CHECK_FAIL( !slider, "Slider::New() is failed." );

  Slider* operatorSlider = &slider;
  DALI_CHECK_FAIL( operatorSlider == NULL, "Slider Assignment is Failed.");

  DaliLog::PrintPass();
}

void SliderDowncastP()
{
  Slider slider = Slider::New();
  DALI_CHECK_FAIL(!slider, "Slider::New() is failed.");

  BaseHandle handleSlider;
  handleSlider = slider;

  Slider downCastSlider = Slider::DownCast( handleSlider );

  DALI_CHECK_FAIL( !downCastSlider, "downCastSlider is not valid object." );
  DALI_CHECK_FAIL( slider != downCastSlider, "downCastSlider is failed to match with slider." );

  DaliLog::PrintPass();
}

void SliderDowncastN()
{
  BaseHandle unInitializedObject;

  Slider downCastSlider = Slider::DownCast( unInitializedObject );
  DALI_CHECK_FAIL( downCastSlider, "Slider handle is not empty." );

  Slider downCastSlider2 = DownCast< Slider >( unInitializedObject );
  DALI_CHECK_FAIL( downCastSlider2, "Slider handle is not empty." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliSliderConstructorP
 * @since_tizen         3.0
 * @description         Checks correct creation of an object
 */

int UtcDaliSliderConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSliderCopyConstructorP
 * @since_tizen         3.0
 * @description         Copy constructor to Slider.
 */

int UtcDaliSliderCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSliderNewP
 * @since_tizen         3.0
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliSliderNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSliderOperatorAssignmentP
 * @since_tizen         3.0
 * @description         Assignment operator.Changes this handle to point to another real object.
 */

int UtcDaliSliderOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSliderDowncastP
 * @since_tizen         3.0
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliSliderDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliSliderDowncastN
 * @since_tizen         3.0
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliSliderDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Slider_TestApp testApp( application, SLIDER_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}
