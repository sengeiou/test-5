#include "utc-dali-scroll-bar-common.h"

//& set: ScrollBar


extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

ScrollBar gScrollBar;              /** ScrollBar instance*/
Actor gScrollBarIndicatorActor;    /** Actor instance for scrollbar indication **/
int gRenderCountScrollBar;         /**Render count*/
float gposition = 0.0f;            /**To get position inside the callback **/

/**Whether the ScrollPositionIntervalReached signal was invoked**/
bool gScrollBarPositionIntervalReachedSignalCalled = false;

/**
 * @function       CbScrollPositionIntervalReached
 * @description    Invoked when the current scroll position of the scrollable content goes above or below the values specified by SCROLL_POSITION_INTERVALS property.
 * @param [in]     position The current scroll position.
 */

void CbScrollPositionIntervalReached( float fposition )
{
  LOG_I("Callabck for scroll position interval reached is called.");
  gScrollBarPositionIntervalReachedSignalCalled = true;
  gposition = fposition;
}

/**
 * @function            utc_Dali_Scrollbar_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Scrollbar_startup( void )
{
  test_return_value=0;
  gRenderCountScrollBar = 0;
}

/**
 * @function            utc_Dali_Scrollbar_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Scrollbar_cleanup( void )
{

}

void ScrollBarNewP();
void ScrollBarConstructorP();
void ScrollBarCopyConstructorP();
void ScrollBarOperatorAssignmentP();
void ScrollBarDowncastP();
void ScrollBarDowncastN();
void ScrollBarSetScrollPropertySourceP();
void ScrollBarSetGetScrollIndicatorP();
void ScrollBarSetGetScrollPositionIntervalsReachedSignalP();
void ScrollBarSetGetScrollDirectionP();
void ScrollBarSetGetIndicatorHeightPolicyP();
void ScrollBarSetGetIndicatorFixedHeightP();
void ScrollBarSetGetIndicatorShowDurationP();
void ScrollBarSetGetIndicatorHideDurationP();
void ScrollBarShowHideIndicatorP();
void ScrollBarPanFinishedSignalP();
void VTScrollBarCheckIndicatorHeight001();
void VTScrollBarCheckIndicatorShowDuration001();
void VTScrollBarCheckIndicatorShowDuration002();
void VTScrollBarCheckIndicatorShowDuration003();
void VTScrollBarCheckIndicatorShowDuration004();
void VTScrollBarCheckIndicatorShowDuration005();
void VTScrollBarCheckIndicatorHideDuration001();
void VTScrollBarCheckIndicatorHideDuration002();
void VTScrollBarIndicatorHeightPolicy001();
void VTScrollBarIndicatorHeightPolicy002();
void VTScrollBarIndicatorHeightPolicy003();
void VTScrollBarScrollPositionIntervalsReachedSignal001();

namespace
{
  enum TEST_CASES_LIST_SCROLL_BAR
  {
    SCROLL_BAR_NEW_P,
    SCROLL_BAR_CONSTRUCTOR_P,
    SCROLL_BAR_COPY_CONSTRUCTOR_P,
    SCROLL_BAR_OPERATOR_ASSIGNMENT_P,
    SCROLL_BAR_DOWNCAST_N,
    SCROLL_BAR_DOWNCAST_P,
    SCROLL_BAR_SET_SCROLL_PROPERTY_SOURCE_P,
    SCROLL_BAR_SET_GET_SCROLL_INDICATOR_P,
    SCROLL_BAR_SET_GET_SCROLL_POSITION_INTERVALS_REACHED_SIGNAL_P,
    SCROLL_BAR_SET_GET_SCROLL_DIRECTION_P,
    SCROLL_BAR_SET_GET_INDICATOR_FIXED_HEIGHT_P,
    SCROLL_BAR_SET_GET_INDICATOR_HEIGHT_POLICY_P,
    SCROLL_BAR_SET_GET_INDICATOR_SHOW_DURATION_P,
    SCROLL_BAR_SET_GET_INDICATOR_HIDE_DURATION_P,
    SCROLL_BAR_SHOW_HIDE_INDICATOR_P,
    SCROLL_BAR_PAN_FINISHED_SIGNAL_P
  };

  struct ScrollBar_TestApp : public ConnectionTracker
  {
    ScrollBar_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ScrollBar_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ScrollBar_TestApp::Tick );
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
        case SCROLL_BAR_NEW_P:
          ScrollBarNewP();
          break;

        case SCROLL_BAR_CONSTRUCTOR_P:
          ScrollBarConstructorP();
          break;

        case SCROLL_BAR_COPY_CONSTRUCTOR_P:
          ScrollBarCopyConstructorP();
          break;

        case SCROLL_BAR_OPERATOR_ASSIGNMENT_P:
          ScrollBarOperatorAssignmentP();
          break;

        case SCROLL_BAR_DOWNCAST_N:
          ScrollBarDowncastN();
          break;

        case SCROLL_BAR_DOWNCAST_P:
          ScrollBarDowncastP();
          break;

        case SCROLL_BAR_SET_SCROLL_PROPERTY_SOURCE_P:
          ScrollBarSetScrollPropertySourceP();
          break;

        case SCROLL_BAR_SET_GET_SCROLL_INDICATOR_P:
          ScrollBarSetGetScrollIndicatorP();
          break;

        case SCROLL_BAR_SET_GET_SCROLL_POSITION_INTERVALS_REACHED_SIGNAL_P:
          ScrollBarSetGetScrollPositionIntervalsReachedSignalP();
          break;

        case SCROLL_BAR_SET_GET_SCROLL_DIRECTION_P:
          ScrollBarSetGetScrollDirectionP();
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_HEIGHT_POLICY_P:
          ScrollBarSetGetIndicatorHeightPolicyP();
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_FIXED_HEIGHT_P:
          ScrollBarSetGetIndicatorFixedHeightP();
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_SHOW_DURATION_P:
          ScrollBarSetGetIndicatorShowDurationP();
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_HIDE_DURATION_P:
          ScrollBarSetGetIndicatorHideDurationP();
          break;

        case SCROLL_BAR_SHOW_HIDE_INDICATOR_P:
          ScrollBarShowHideIndicatorP();
          break;

        case SCROLL_BAR_PAN_FINISHED_SIGNAL_P:
          ScrollBarPanFinishedSignalP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {

        case SCROLL_BAR_SET_GET_INDICATOR_FIXED_HEIGHT_P:
          VTScrollBarCheckIndicatorHeight001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_SHOW_DURATION_P:
          switch (gRenderCountScrollBar)
          {
            case 0:
              VTScrollBarCheckIndicatorShowDuration001();
              gRenderCountScrollBar++;
              break;

            case 1:
              VTScrollBarCheckIndicatorShowDuration002();
              gRenderCountScrollBar++;
              break;

            case 2:
              VTScrollBarCheckIndicatorShowDuration003();
              gRenderCountScrollBar++;
              break;

            case 3:
              VTScrollBarCheckIndicatorShowDuration004();
              gRenderCountScrollBar++;
              break;

            case 4:
              VTScrollBarCheckIndicatorShowDuration005();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_HIDE_DURATION_P:
          switch (gRenderCountScrollBar)
          {
            case 0:
              VTScrollBarCheckIndicatorHideDuration001();
              gRenderCountScrollBar++;
              break;

            case 1:
              VTScrollBarCheckIndicatorHideDuration002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_BAR_SHOW_HIDE_INDICATOR_P:
          switch (gRenderCountScrollBar)
          {
            case 0:
              VTScrollBarCheckIndicatorHideDuration001();
              gRenderCountScrollBar++;
              break;

            case 1:
              VTScrollBarCheckIndicatorHideDuration002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_BAR_SET_GET_INDICATOR_HEIGHT_POLICY_P:
          switch (gRenderCountScrollBar)
          {
            case 0:
              VTScrollBarIndicatorHeightPolicy001();
              gRenderCountScrollBar++;
              break;

            case 1:
              VTScrollBarIndicatorHeightPolicy002();
              gRenderCountScrollBar++;
              break;

            case 2:
              VTScrollBarIndicatorHeightPolicy003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_BAR_SET_GET_SCROLL_POSITION_INTERVALS_REACHED_SIGNAL_P:
          VTScrollBarScrollPositionIntervalsReachedSignal001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        default:
          mTimer.Stop();
          mApplication.Quit();
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


void ScrollBarNewP()
{
  ScrollBar scrollbar = ScrollBar::New();
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New() is failed.");
  scrollbar.SetProperty( ScrollBar::Property::INDICATOR_FIXED_HEIGHT, 50.4f );

  DaliLog::PrintPass();
}


void ScrollBarConstructorP()
{
  ScrollBar scrollbar;
  DALI_CHECK_FAIL(scrollbar, "ScrollBar Default constructor is failed.");

  DaliLog::PrintPass();
}


void ScrollBarCopyConstructorP()
{
  ScrollBar scrollbar = ScrollBar::New();
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New() is failed.");
  scrollbar.SetProperty( ScrollBar::Property::INDICATOR_FIXED_HEIGHT, 50.4f );

  ScrollBar scrollbarcopy( scrollbar );
  DALI_CHECK_FAIL(!scrollbarcopy, "ScrollBar copy constructor is failed.");
  DALI_CHECK_FAIL( scrollbarcopy.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ) != scrollbar.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ), "Copy constructor is failed as property mismatched" );

  DaliLog::PrintPass();
}

void ScrollBarOperatorAssignmentP()
{
  ScrollBar scrollbar = ScrollBar::New();
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New() is failed.");
  scrollbar.SetProperty( ScrollBar::Property::INDICATOR_FIXED_HEIGHT, 50.4f );

  ScrollBar scrollbarAssignment =  scrollbar;
  DALI_CHECK_FAIL(!scrollbarAssignment, "ScrollBar Assignment Operator is failed.");
  DALI_CHECK_FAIL( scrollbarAssignment.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ) != scrollbar.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ), "Assignment operator is failed as property mismatched" );

  DaliLog::PrintPass();
}

void ScrollBarDowncastP()
{
  ScrollBar scrollbar = ScrollBar::New();
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New() is failed.");
  scrollbar.SetProperty( ScrollBar::Property::INDICATOR_FIXED_HEIGHT, 50.4f );

  BaseHandle Baseobject( scrollbar );
  ScrollBar scrollbarDowncast = ScrollBar::DownCast( Baseobject );
  DALI_CHECK_FAIL( !scrollbarDowncast, "ScrollBar::Downcast is failed" );
  DALI_CHECK_FAIL( scrollbarDowncast.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ) != scrollbar.GetProperty<float>( ScrollBar::Property::INDICATOR_FIXED_HEIGHT ), "Downcast is failed as property mismatched" );

  DaliLog::PrintPass();
}

void ScrollBarDowncastN()
{
  BaseHandle unInitializedObject;

  ScrollBar scrollBar = ScrollBar::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(scrollBar, "Control handle is not empty." );

  ScrollBar scrollBar2 = DownCast< ScrollBar >( unInitializedObject );
  DALI_CHECK_FAIL(scrollBar2, "Control handle is not empty." );

  DaliLog::PrintPass();
}

void ScrollBarSetScrollPropertySourceP()
{
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");

  const float F_WIDTH = 20.0f, F_DEPTH = 0.0f;

  gScrollBar.SetSize(F_WIDTH, SCROLL_BAR_F_HEIGHT, F_DEPTH);
  Stage::GetCurrent().Add( gScrollBar );
  Actor sourceActor = Actor::New();
  DALI_CHECK_FAIL(!sourceActor, "Actor ::New() is failed to create new actor");
  Stage::GetCurrent().Add( sourceActor );

  // Register the scroll properties
  Property::Index propertyScrollPosition = sourceActor.RegisterProperty( "source-position", 0.0f );
  Property::Index propertyMinScrollPosition = sourceActor.RegisterProperty( "source-position-min", 0.0f );
  Property::Index propertyMaxScrollPosition = sourceActor.RegisterProperty( "source-position-max", 100.0f );
  Property::Index propertyScrollContentSize = sourceActor.RegisterProperty( "source-content-size", 500.0f );

  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position" ) !=propertyScrollPosition, "Source position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-min" ) != propertyMinScrollPosition, "Source min position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-max" ) != propertyMaxScrollPosition, "Source max position is mismathced" );
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-content-size" ) != propertyScrollContentSize, "Source content size is mismathced ");

  // Set the source of the scroll position properties.
  try
  {
    gScrollBar.SetScrollPropertySource(sourceActor, propertyScrollPosition, propertyMinScrollPosition, propertyMaxScrollPosition, propertyScrollContentSize);
  }
  catch(DaliException& de)
  {
    LOG_E("SetScrollPropertySource is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;

  }
  DaliLog::PrintPass();
}

void ScrollBarSetGetScrollIndicatorP()
{
  ScrollBar scrollbar = ScrollBar::New();
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New() is failed.");
  Actor indicator = scrollbar.GetScrollIndicator();
  DALI_CHECK_FAIL( !indicator, "GetScrollIndicator has failed to create Actor indicator instance" );

  Actor indicatorNew = Actor::New();
  DALI_CHECK_FAIL(!indicatorNew, "Actor::New() is failed");
  scrollbar.SetScrollIndicator( indicatorNew );

  DALI_CHECK_FAIL( scrollbar.GetScrollIndicator() != indicatorNew,"SetScrollIndicator is failed to set correct indicator instance" );
  DALI_CHECK_FAIL( scrollbar.GetScrollIndicator() == indicator,"SetScrollIndicator is failed to set correct indicator instance" );

  DaliLog::PrintPass();
}

void ScrollBarSetGetScrollPositionIntervalsReachedSignalP()
{
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");

  const float F_WIDTH = 20.0f, F_HEIGHT = 800.0f, F_DEPTH = 0.0f, F_PIXEL = -80.0f, F_ANIM_TIME = 0.1f;
  gScrollBar.SetParentOrigin(ParentOrigin::TOP_LEFT);
  gScrollBar.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  gScrollBar.SetSize(F_WIDTH, F_HEIGHT, F_DEPTH);

  Stage::GetCurrent().Add( gScrollBar );

  // Connect to the ScrollPositionIntervalReached signal
  gScrollBar.ScrollPositionIntervalReachedSignal().Connect( &CbScrollPositionIntervalReached );

  // Create a source actor that owns the scroll properties required by the scroll bar
  Actor sourceActor = Actor::New();
  Stage::GetCurrent().Add( sourceActor );

  // Register the scroll properties
  Property::Index propertyScrollPosition = sourceActor.RegisterProperty( "source-position", 0.0f );
  Property::Index propertyMinScrollPosition = sourceActor.RegisterProperty( "source-position-min", 0.0f );
  Property::Index propertyMaxScrollPosition = sourceActor.RegisterProperty( "source-position-max", 800.0f );
  Property::Index propertyScrollContentSize = sourceActor.RegisterProperty( "source-content-size", 2000.0f );

  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position" ) !=propertyScrollPosition, "Source position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-min" ) != propertyMinScrollPosition, "Source min position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-max" ) != propertyMaxScrollPosition, "Source max position is mismathced" );
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-content-size" ) != propertyScrollContentSize, "Source content size is mismathced ");

  // Set the source of the scroll position properties.
  gScrollBar.SetScrollPropertySource(sourceActor, propertyScrollPosition, propertyMinScrollPosition, propertyMaxScrollPosition, propertyScrollContentSize);

  // Set the values to get notified when the scroll positions of the source actor goes above or below these values
  Vector<float> fpositionIntervals;
  for( size_t i = 0; i != 10; ++i )
  {
    fpositionIntervals.PushBack( F_PIXEL * i ); // should get notified for each 80 pixels
  }

  gScrollBar.SetScrollPositionIntervals( fpositionIntervals );

  // Get the list of scroll position intervals for notification
  Vector<float> fresults = gScrollBar.GetScrollPositionIntervals();

  // Check that the result is the same as the list previously set.
  DALI_CHECK_FAIL( fpositionIntervals.Count() != fresults.Count(), "Set and Get total scrollposition count mismatched");
  DALI_CHECK_FAIL( fpositionIntervals[0] != fresults[0], "Set and Get scrollposition value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[1] != fresults[1], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[2] != fresults[2], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[3] != fresults[3], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[4] != fresults[4], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[5] != fresults[5], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[6] != fresults[6], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[7] != fresults[7], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[8] != fresults[8], "Set and Get value mismatched" );
  DALI_CHECK_FAIL( fpositionIntervals[9] != fresults[9], "Set and Get value mismatched" );

  // Reset the flag
  gScrollBarPositionIntervalReachedSignalCalled = false;

  // Animate the scroll position to cross the specified value
  Animation animation = Animation::New( F_ANIM_TIME );
  animation.AnimateTo( Property( sourceActor, propertyScrollPosition ), SCROLL_BAR_F_TARGET_POSITION );
  animation.Play();
}

// * ############################## Verdict test for ScrollBarSetGetScrollPositionIntervalsReachedSignal

void VTScrollBarScrollPositionIntervalsReachedSignal001()
{
  // Check that the signal callback is called
  DALI_CHECK_FAIL( !gScrollBarPositionIntervalReachedSignalCalled, "Signal callback is not called" );
  DALI_CHECK_FAIL( !Equals(gposition, SCROLL_BAR_F_TARGET_POSITION, SCROLL_BAR_EPSILON),
      "Though signal callback is called, the position retrieved inside the callback mismatches with expected position.");

  Stage::GetCurrent().Remove( gScrollBar );
  DaliLog::PrintPass();
}

void ScrollBarSetGetScrollDirectionP()
{
  ScrollBar scrollbar = ScrollBar::New(ScrollBar::Vertical);
  DALI_CHECK_FAIL(!scrollbar, "ScrollBar::New( Vertical ) is failed.");
  DALI_CHECK_FAIL( scrollbar.GetScrollDirection() != ScrollBar::Vertical, "Get ScrollBarDirection is failed" );

  scrollbar.SetScrollDirection(ScrollBar::Horizontal);
  DALI_CHECK_FAIL( scrollbar.GetScrollDirection() != ScrollBar::Horizontal ,"SetScrollBarDirection is failed");

  DaliLog::PrintPass();
}

void ScrollBarSetGetIndicatorHeightPolicyP()
{
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");

  const float F_WIDTH = 20.0f, F_DEPTH = 0.0f;

  gScrollBar.SetSize(F_WIDTH, SCROLL_BAR_F_HEIGHT, F_DEPTH);
  Stage::GetCurrent().Add( gScrollBar );
  Actor sourceActor = Actor::New();
  DALI_CHECK_FAIL(!sourceActor, "Actor ::New() is failed to create new actor");
  Stage::GetCurrent().Add( sourceActor );

  // Register the scroll properties
  Property::Index propertyScrollPosition = sourceActor.RegisterProperty( "source-position", 0.0f );
  Property::Index propertyMinScrollPosition = sourceActor.RegisterProperty( "source-position-min", 0.0f );
  Property::Index propertyMaxScrollPosition = sourceActor.RegisterProperty( "source-position-max", 100.0f );
  Property::Index propertyScrollContentSize = sourceActor.RegisterProperty( "source-content-size", 500.0f );

  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position" ) !=propertyScrollPosition, "Source position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-min" ) != propertyMinScrollPosition, "Source min position is mismathced");
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-position-max" ) != propertyMaxScrollPosition, "Source max position is mismathced" );
  DALI_CHECK_FAIL( sourceActor.GetPropertyIndex( "source-content-size" ) != propertyScrollContentSize, "Source content size is mismathced ");

  // Set the source of the scroll position properties.
  gScrollBar.SetScrollPropertySource(sourceActor, propertyScrollPosition, propertyMinScrollPosition, propertyMaxScrollPosition, propertyScrollContentSize);
}

// * ############################## Verdict test for ScrollBarSetGetIndicatorHeightPolicy

void VTScrollBarIndicatorHeightPolicy001()
{
  gScrollBarIndicatorActor = gScrollBar.GetScrollIndicator();
  DALI_CHECK_FAIL( !gScrollBarIndicatorActor, "GetScrollIndicator failed to get Actor from scrollbar instance" );

  // Check that the indicator size should be: scroll bar size * (scroll bar size / content size).
  // i.e. The bigger the content size, the smaller the indicator size
  float fIndicatorHeight = gScrollBarIndicatorActor.GetCurrentSize().y;
  DALI_CHECK_FAIL( fIndicatorHeight != SCROLL_BAR_F_HEIGHT * SCROLL_BAR_F_HEIGHT / SCROLL_BAR_F_CONTENT_SIZE, "indicator height mismatch with the calculated value");

  // Set the indicator height to be fixed to 50.0f
  gScrollBar.SetIndicatorHeightPolicy(Toolkit::ScrollBar::Fixed);
  DALI_CHECK_FAIL(gScrollBar.GetIndicatorHeightPolicy() != Toolkit::ScrollBar::Fixed, "Set and Get indicator height policy mismatched");

  gScrollBar.SetIndicatorFixedHeight( SCROLL_BAR_F_FIXED_HEIGHT );

}
void VTScrollBarIndicatorHeightPolicy002()
{
  // Check that the indicator size should be 50.0f
  float fIndicatorHeight = gScrollBarIndicatorActor.GetCurrentSize().y;
  DALI_CHECK_FAIL( fIndicatorHeight != SCROLL_BAR_F_FIXED_HEIGHT, "set and get height mismatched after setting indicator height policy to fixed");

  // Set the indicator height to be variable
  gScrollBar.SetIndicatorHeightPolicy(Toolkit::ScrollBar::Variable);
  DALI_CHECK_FAIL(gScrollBar.GetIndicatorHeightPolicy() != Toolkit::ScrollBar::Variable, "Set and Get indicator height policy mismatched");
}
void VTScrollBarIndicatorHeightPolicy003()
{
  // Check that the indicator size should be: scroll bar size * (scroll bar size / content size).
  float fIndicatorHeight = gScrollBarIndicatorActor.GetCurrentSize().y;
  DALI_CHECK_FAIL( fIndicatorHeight != SCROLL_BAR_F_HEIGHT * SCROLL_BAR_F_HEIGHT / SCROLL_BAR_F_CONTENT_SIZE, "Set and get value mismatched after setting height policy to variable");

  Stage::GetCurrent().Remove( gScrollBar );
  DaliLog::PrintPass();
}

void ScrollBarSetGetIndicatorFixedHeightP()
{
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");

  Stage::GetCurrent().Add( gScrollBar );

  gScrollBar.SetIndicatorHeightPolicy(Toolkit::ScrollBar::Fixed);
  gScrollBar.SetIndicatorFixedHeight( SCROLL_BAR_F_HEIGHT );
}

// * ############################## Verdict test for ScrollBarSetGetIndicatorFixedHeight

void VTScrollBarCheckIndicatorHeight001()
{
  Actor indicator = gScrollBar.GetScrollIndicator();
  DALI_CHECK_FAIL( !indicator, "GetScrollIndicator failed to get Actor from scrollbar instance" );

  // Check that the indicator size should be 100.0f
  DALI_CHECK_FAIL( indicator.GetCurrentSize().y != SCROLL_BAR_F_HEIGHT, "SetIndicatorFixedHeight is failed to set value");

  gScrollBar.SetIndicatorFixedHeight( SCROLL_BAR_F_NEW_HEIGHT );
  DALI_CHECK_FAIL(gScrollBar.GetIndicatorFixedHeight() != SCROLL_BAR_F_NEW_HEIGHT, "Set and Get SetIndicatorFixedHeight mismatches");

  Stage::GetCurrent().Remove( gScrollBar );
  DaliLog::PrintPass();
}

void ScrollBarSetGetIndicatorShowDurationP()
{
  const float F_TIME = 0.35f;
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");
  Stage::GetCurrent().Add( gScrollBar );

  gScrollBarIndicatorActor = gScrollBar.GetScrollIndicator();
  DALI_CHECK_FAIL( !gScrollBarIndicatorActor, "GetScrollIndicator failed to get Actor from scrollbar instance" );

  // Set the duration to show the indicator to be 0.35 second
  gScrollBar.SetIndicatorShowDuration( F_TIME );
  DALI_CHECK_FAIL( gScrollBar.GetIndicatorShowDuration() != F_TIME, "Set and Get Show indicator value mismatched");

  gScrollBar.SetIndicatorHideDuration( F_TIME );

  gScrollBar.SetOpacity( SCROLL_BAR_F_VISIBLE_OPACITY );

  // Make the indicator invisible
  gScrollBar.HideIndicator();
}

// * ############################## Verdict test for ScrollBarSetGetIndicatorShowDuration

void VTScrollBarCheckIndicatorShowDuration001()
{
  // Check that the indicator is invisible
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_INVISIBLE_OPACITY,
      "Indicator is not hidden");
  // Show the indicator
  gScrollBar.ShowIndicator();
}
void VTScrollBarCheckIndicatorShowDuration002()
{
  // Check that the indicator is now visible beyond 0.35 second after render(tick interval is set to 0.5 s)
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_VISIBLE_OPACITY,
      "Indicator is not shown");

  //Make the indicator invisible again
  gScrollBar.HideIndicator();
}
void VTScrollBarCheckIndicatorShowDuration003()
{
  // Check that the indicator is invisible again
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_INVISIBLE_OPACITY,
      "Indicator is not hidden");

  // Set the duration to show the indicator to be 0.6 second
  gScrollBar.SetIndicatorShowDuration( SCROLL_BAR_F_NEW_TIME );
  DALI_CHECK_FAIL( gScrollBar.GetIndicatorShowDuration() != SCROLL_BAR_F_NEW_TIME, "Set and Get Show indicator value mismatched");

  // Show the indicator again
  gScrollBar.ShowIndicator();
}
void VTScrollBarCheckIndicatorShowDuration004()
{
  // Check that the indicator is invisible before new time is over (0.5s elapsed )
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() == SCROLL_BAR_F_VISIBLE_OPACITY,
      "Indicator should not be shown before new time is over");
}
void VTScrollBarCheckIndicatorShowDuration005()
{
  // Check that the indicator is visible after new time is over (another 0.5s elapsed, beyond 0.6s )
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_VISIBLE_OPACITY,
      "Set and get opacity is mismatched after new time is over.");
  Stage::GetCurrent().Remove( gScrollBar );
  DaliLog::PrintPass();
}
void ScrollBarSetGetIndicatorHideDurationP()
{
  const float F_TIME = 0.35f;
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");
  Stage::GetCurrent().Add( gScrollBar );

  gScrollBarIndicatorActor = gScrollBar.GetScrollIndicator();
  DALI_CHECK_FAIL( !gScrollBarIndicatorActor, "GetScrollIndicator failed to get Actor from scrollbar instance" );

  // Set the duration to show the indicator to be 0.35 second
  gScrollBar.SetIndicatorHideDuration( F_TIME );
  DALI_CHECK_FAIL( gScrollBar.GetIndicatorHideDuration() != F_TIME, "Set and Get Hide indicator value mismatched");

  // Make the indicator invisible
  gScrollBarIndicatorActor.SetOpacity( SCROLL_BAR_F_VISIBLE_OPACITY );
}

void VTScrollBarCheckIndicatorHideDuration001()
{
  // Check that the indicator is visible
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_VISIBLE_OPACITY,
      "Set and get opacity is mismatched");

  // hide the indicator
  gScrollBar.HideIndicator();
}
void VTScrollBarCheckIndicatorHideDuration002()
{
  // Check that the indicator is now invisible
  DALI_CHECK_FAIL( gScrollBarIndicatorActor.GetCurrentOpacity() != SCROLL_BAR_F_INVISIBLE_OPACITY,
      "Set and get opacity is mismatched");

  gScrollBar.SetIndicatorHideDuration( SCROLL_BAR_F_NEW_TIME );
  DALI_CHECK_FAIL( gScrollBar.GetIndicatorHideDuration() != SCROLL_BAR_F_NEW_TIME, "Set and Get Hide indicator value mismatched");

  Stage::GetCurrent().Remove( gScrollBar );
  DaliLog::PrintPass();
}

void ScrollBarShowHideIndicatorP()
{
  const float F_TIME = 0.35f;
  gScrollBar = ScrollBar::New();
  DALI_CHECK_FAIL(!gScrollBar, "ScrollBar::New() is failed.");
  Stage::GetCurrent().Add( gScrollBar );

  gScrollBarIndicatorActor = gScrollBar.GetScrollIndicator();
  DALI_CHECK_FAIL( !gScrollBarIndicatorActor, "GetScrollIndicator failed to get Actor from scrollbar instance" );

  // Set the duration to show the indicator to be 0.35 second
  gScrollBar.SetIndicatorHideDuration( F_TIME );
  DALI_CHECK_FAIL( gScrollBar.GetIndicatorHideDuration() != F_TIME, "Set and Get Hide indicator value mismatched");

  // Make the indicator invisible
  gScrollBarIndicatorActor.SetOpacity( SCROLL_BAR_F_VISIBLE_OPACITY );

  DaliLog::PrintPass();

}

void ScrollBarPanFinishedSignalP()
{
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliScrollBarConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliScrollBarConstructorP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliScrollBarNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliScrollBarNewP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarCopyConstructorP
 * @since_tizen         2.4
 * @description         Creates another handle that points to the same real object.
 */

int UtcDaliScrollBarCopyConstructorP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks whether Assignmentoperator is executed successfully or not
 */

int UtcDaliScrollBarOperatorAssignmentP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_OPERATOR_ASSIGNMENT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarDowncastP
 * @since_tizen         2.4
 * @description         Downcast an Object handle to Control.
 */

int UtcDaliScrollBarDowncastP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_DOWNCAST_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliScrollBarDowncastN( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_DOWNCAST_N);
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliScrollBarSetScrollPropertySourceP
 * @since_tizen         2.4
 * @description         Checks if ScrollProperty Source is set correctly or not
 */

int UtcDaliScrollBarSetScrollPropertySourceP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_SCROLL_PROPERTY_SOURCE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetScrollIndicatorP
 * @since_tizen         2.4
 * @description         Check functionality of SetScrollDirection and GetScrollDirection
 */

int UtcDaliScrollBarSetGetScrollIndicatorP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_SCROLL_INDICATOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetScrollPositionIntervalsReachedSignalP
 * @since_tizen         2.4
 * @description         Check functionality of SetScrollPositionIntervals and GetScrollPositionIntervals and ScrollPositionIntervalReachedSignal
 */

int UtcDaliScrollBarSetGetScrollPositionIntervalsReachedSignalP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_SCROLL_POSITION_INTERVALS_REACHED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetScrollDirectionP
 * @since_tizen         2.4
 * @description         Check functionality of SetScrollDirection and GetScrollDirection
 */

int UtcDaliScrollBarSetGetScrollDirectionP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_SCROLL_DIRECTION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetIndicatorHeightPolicyP
 * @since_tizen         2.4
 * @description         Check functionality of SetIndicatorHeightPolicy and GetIndicatorHeightPolicy
 */

int UtcDaliScrollBarSetGetIndicatorHeightPolicyP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_INDICATOR_HEIGHT_POLICY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetIndicatorFixedHeightP
 * @since_tizen         2.4
 * @description         Check functionality SetIndicatorFixedHeight and GetIndicatorFixedHeight
 */

int UtcDaliScrollBarSetGetIndicatorFixedHeightP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_INDICATOR_FIXED_HEIGHT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetIndicatorShowDurationP
 * @since_tizen         2.4
 * @description         Check functionality of SetIndicatorShowDuration and GetIndicatorShowDuration and Show Duration work properly or not
 */

int UtcDaliScrollBarSetGetIndicatorShowDurationP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_INDICATOR_SHOW_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarSetGetIndicatorHideDurationP
 * @since_tizen         2.4
 * @description         Check functionality of SetIndicatorHideDuration and GetIndicatorHideDuration and HideDuration work properly or not
 */

int UtcDaliScrollBarSetGetIndicatorHideDurationP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SET_GET_INDICATOR_HIDE_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarShowHideIndicatorP
 * @since_tizen         2.4
 * @description         Check functionality of ShowIndicator and HideIndicator work properly or not
 */

int UtcDaliScrollBarShowHideIndicatorP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_SHOW_HIDE_INDICATOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollBarPanFinishedSignalP
 * @since_tizen         2.4
 * @description         Check functionality of ShowIndicator and HideIndicator work properly or not
 */

int UtcDaliScrollBarPanFinishedSignalP( void )
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollBar_TestApp testApp( application, SCROLL_BAR_PAN_FINISHED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}
