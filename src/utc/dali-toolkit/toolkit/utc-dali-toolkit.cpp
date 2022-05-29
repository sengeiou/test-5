#include "utc-dali-toolkit-common.h"

//& set: Toolkit
ScrollView gScrollViewToolkit;            /**ScrollView instance**/
int gRenderCountToolkit;                  /**Render count **/
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Toolkit_startup
 * @description         Called before each test
 * @return              NA
 */

void utc_Dali_Toolkit_startup(void)
{
  test_return_value=0;
  gRenderCountToolkit=0;
}

/**
 * @function            utc_Dali_Toolkit_cleanup
 * @description         Called after each test
 * @return              NA
 */

void utc_Dali_Toolkit_cleanup(void)
{
}

void ToolkitIsVerticalP();
void ToolkitIsHorizontalP();
void ToolkitWrapActorConstraintP();
void ToolkitMoveActorConstraintP();
void VTToolkitWrapConstraint001();
void VTToolkitWrapConstraint002();
void VTToolkitWrapConstraint003();
void VTToolkitMoveActorConstraint001();
void VTToolkitMoveActorConstraint002();

namespace
{
  enum TEST_CASES_LIST_TOOLKIT
  {
    TOOLKIT_IS_VERTICAL_P,
    TOOLKIT_IS_HORIZONTAL_P,
    TOOLKIT_WRAP_ACTOR_CONSTRAINT_P,
    TOOLKIT_MOVE_ACTOR_CONSTRAINT_P
  };

  struct Toolkit_TestApp : public ConnectionTracker
  {
    Toolkit_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Toolkit_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Toolkit_TestApp::Tick );
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
        case TOOLKIT_IS_VERTICAL_P:
          ToolkitIsVerticalP();
          break;
        case TOOLKIT_IS_HORIZONTAL_P:
          ToolkitIsHorizontalP();
          break;
        case TOOLKIT_WRAP_ACTOR_CONSTRAINT_P:
          ToolkitWrapActorConstraintP();
          break;
        case TOOLKIT_MOVE_ACTOR_CONSTRAINT_P:
          ToolkitMoveActorConstraintP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case TOOLKIT_WRAP_ACTOR_CONSTRAINT_P:
          switch(gRenderCountToolkit)
          {
            case 0:
              VTToolkitWrapConstraint001();
              gRenderCountToolkit++;
              break;

            case 1:
              VTToolkitWrapConstraint002();
              gRenderCountToolkit++;
              break;

            case 2:
              VTToolkitWrapConstraint003();
              mTimer.Stop();
              mApplication.Quit();
              break;

          }
          break;

        case TOOLKIT_MOVE_ACTOR_CONSTRAINT_P:
          switch(gRenderCountToolkit)
          {
            case 0:
              VTToolkitMoveActorConstraint001();
              gRenderCountToolkit++;
              break;

            case 1:
              VTToolkitMoveActorConstraint002();
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

void ToolkitIsVerticalP()
{
  bool bRet = false;

  bRet = IsVertical(ControlOrientation::Up);
  DALI_CHECK_FAIL(!bRet, "IsVertical APi is getting failed for ControlOrientation::Up." );

  bRet = IsVertical(ControlOrientation::Down);
  DALI_CHECK_FAIL(!bRet, "IsVertical APi is getting failed for ControlOrientation::Down." );

  DaliLog::PrintPass();
}

void ToolkitIsHorizontalP()
{
  bool bRet = false;

  bRet = IsHorizontal(ControlOrientation::Left);
  DALI_CHECK_FAIL(!bRet, "IsVertical APi is getting failed for ControlOrientation::Left." );

  bRet = IsHorizontal(ControlOrientation::Right);
  DALI_CHECK_FAIL(!bRet, "IsVertical APi is getting failed for ControlOrientation::Right." );

  DaliLog::PrintPass();
}

void ToolkitWrapActorConstraintP()
{
  const Vector2 VEC2_SIZE(200.0f, 200.0f);
  const Vector2 VEC2_SCROLL_POS_MIN(0.0f, 0.0f);
  const Vector2 VEC2_POSITION(50.0f, 50.0f);
  const Vector3 VEC3_SCALE( 0.2f, 0.3f, 0.5f );
  bool bWrapMode = true;

  gScrollViewToolkit = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollViewToolkit, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollViewToolkit );
  gScrollViewToolkit.SetSize(VEC2_SIZE);
  gScrollViewToolkit.SetParentOrigin(ParentOrigin::TOP_LEFT);
  gScrollViewToolkit.SetAnchorPoint(AnchorPoint::TOP_LEFT);
  gScrollViewToolkit.SetScale(VEC3_SCALE);
  gScrollViewToolkit.SetPosition(Vector3(VEC2_POSITION));
  gScrollViewToolkit.SetProperty(Scrollable::Property::SCROLL_POSITION_MIN, VEC2_SCROLL_POS_MIN);
  gScrollViewToolkit.SetProperty(Scrollable::Property::SCROLL_POSITION_MAX, TOOLKIT_VEC2_SCROLL_POS_MAX);
  gScrollViewToolkit.SetWrapMode(bWrapMode);

  Constraint constraint = Constraint::New<Vector3>( gScrollViewToolkit, Actor::Property::POSITION, WrapActorConstraint );
  constraint.AddSource( LocalSource( Actor::Property::SCALE ) );
  constraint.AddSource( LocalSource( Actor::Property::ANCHOR_POINT ) );
  constraint.AddSource( LocalSource( Actor::Property::SIZE ) );
  constraint.AddSource( Source( gScrollViewToolkit, Scrollable::Property::SCROLL_POSITION_MIN ) );
  constraint.AddSource( Source( gScrollViewToolkit, Scrollable::Property::SCROLL_POSITION_MAX ) );
  constraint.AddSource( Source( gScrollViewToolkit, ScrollView::Property::WRAP ) );
  constraint.SetRemoveAction(Constraint::Discard);
  constraint.Apply();
}

// * ############################## Verdict test for ToolkitWrapActorConstraint

void VTToolkitWrapConstraint001()
{
  // After constraint application, setting a position inside the boundary
  gScrollViewToolkit.SetPosition(TOOLKIT_VEC3_INSIDE_BOUNDARY);
}
void VTToolkitWrapConstraint002()
{
  DALI_CHECK_FAIL(!ToolkitVector3Compare( gScrollViewToolkit.GetCurrentPosition(), TOOLKIT_VEC3_INSIDE_BOUNDARY ), "Toolkit::WrapActorConstraint is failed, position is not set inside the boundary");

  // Setting a position outside the boundary
  // to check whether the position is wrapped inside the boundary due to applied constraint
  gScrollViewToolkit.SetPosition(TOOLKIT_VEC3_OUTSIDE_BOUNDARY);
}
void VTToolkitWrapConstraint003()
{
  Vector3 vec3ExpectedWrappedPosition = TOOLKIT_VEC3_OUTSIDE_BOUNDARY - Vector3(TOOLKIT_VEC2_SCROLL_POS_MAX );

  DALI_CHECK_FAIL(!ToolkitVector3Compare( gScrollViewToolkit.GetCurrentPosition(), vec3ExpectedWrappedPosition ), "Toolkit::WrapActorConstraint is failed to wrap position inside the boundary" );

  gScrollViewToolkit.RemoveConstraints();
  Stage::GetCurrent().Remove( gScrollViewToolkit );
  DaliLog::PrintPass();
}

void ToolkitMoveActorConstraintP()
{
  const Vector2 VEC2_SCROLL_POSITION(200.0f, 200.0f);

  gScrollViewToolkit = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollViewToolkit, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollViewToolkit );
  gScrollViewToolkit.SetPosition(Vector3(TOOLKIT_VEC2_CURRENT_POSITION));
  gScrollViewToolkit.ScrollTo( VEC2_SCROLL_POSITION, 0.25f );

  Constraint constraint = Constraint::New<Vector3>( gScrollViewToolkit, Actor::Property::POSITION, MoveActorConstraint );
  constraint.AddSource( Source( gScrollViewToolkit, ScrollView::Property::SCROLL_POSITION ) );
  constraint.SetRemoveAction(Constraint::Discard);
  constraint.Apply();
}

// * ############################## Verdict test for ToolkitMoveActorConstraint

void VTToolkitMoveActorConstraint001()
{
  Vector3 vec3ExpectedPositionAfterScroll, vec3GetPosition;

  vec3GetPosition = gScrollViewToolkit.GetCurrentPosition();
  vec3ExpectedPositionAfterScroll = Vector3( TOOLKIT_VEC2_CURRENT_POSITION + gScrollViewToolkit.GetCurrentProperty<Vector2>(ScrollView::Property::SCROLL_POSITION));
  DALI_CHECK_FAIL( !ToolkitVector3Compare(vec3GetPosition, vec3ExpectedPositionAfterScroll), "Toolkit::MoveActorConstraint is failed to apply constraint.");

  gScrollViewToolkit.SetPosition(Vector3(TOOLKIT_VEC2_NEW_POSITION));
}
void VTToolkitMoveActorConstraint002()
{
  Vector3 vec3ExpectedPositionAfterScroll, vec3GetPosition;
  vec3GetPosition = gScrollViewToolkit.GetCurrentPosition();
  vec3ExpectedPositionAfterScroll = Vector3( TOOLKIT_VEC2_NEW_POSITION + gScrollViewToolkit.GetCurrentProperty<Vector2>(ScrollView::Property::SCROLL_POSITION));

  DALI_CHECK_FAIL( ToolkitVector3Compare(vec3GetPosition, Vector3(TOOLKIT_VEC2_NEW_POSITION)), "New position should not be set due to constraint application");
  DALI_CHECK_FAIL( !ToolkitVector3Compare(vec3GetPosition, vec3ExpectedPositionAfterScroll), "Failed to get position applied by constraint.");

  gScrollViewToolkit.RemoveConstraints();
  Stage::GetCurrent().Remove( gScrollViewToolkit );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliToolkitIsVerticalP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliToolkitIsVerticalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Toolkit_TestApp testApp( application, TOOLKIT_IS_VERTICAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliToolkitIsHorizontalP
 * @since_tizen         2.4
 * @description         Query whether an orientation is horizontal.
 */

int UtcDaliToolkitIsHorizontalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Toolkit_TestApp testApp( application, TOOLKIT_IS_HORIZONTAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliToolkitWrapActorConstraintP
 * @since_tizen         2.4
 * @description         Wraps an Actor's position in accordance to min/max bounds of domain.
 */

int UtcDaliToolkitWrapActorConstraintP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Toolkit_TestApp testApp( application, TOOLKIT_WRAP_ACTOR_CONSTRAINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliToolkitMoveActorConstraintP
 * @since_tizen         2.4
 * @description         Moves an Actor in accordance to scroll position.
 */

int UtcDaliToolkitMoveActorConstraintP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Toolkit_TestApp testApp( application, TOOLKIT_MOVE_ACTOR_CONSTRAINT_P );
  application.MainLoop();

  return test_return_value;
}
