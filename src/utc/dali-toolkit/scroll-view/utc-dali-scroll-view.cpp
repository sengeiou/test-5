#include "utc-dali-scroll-view-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

//& set: ScrollView

int GRenderCountScrollView;                    /** Render Count **/

/**
 * @function            utc_Dali_ScrollView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ScrollView_startup(void)
{
  test_return_value=0;
  GRenderCountScrollView=0;
}

/**
 * @function            utc_Dali_ScrollView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ScrollView_cleanup(void)
{

}

unsigned int GInterval = INTERVAL;

ScrollView gScrollView;                                    /** ScrollView instance **/
Actor gActorBinded, gActorA;                               /** Actor binded/ added to scrollview */


bool gScrollViewOnScrollStartCalled = false;               /** Scroll start callback status **/
bool gScrollViewOnScrollUpdateCalled = false;              /** Scroll update callback status **/
bool gScrollViewOnScrollCompleteCalled = false;            /** Scroll complete callback status **/
static std::vector< Actor > gVecPagesActor;                /** Vector of actor pages **/
typedef std::vector< Actor >::iterator ActorIter;          /** Iterator for actor pages **/
static Vector3 gVec3ScrollviewConstraintResult;            /** Vector3 value applied by constraint **/

const Vector3 SCROLL_VIEW_TEST_ACTOR_POSITION(400.0f, 400.0f, 0.0f);              /**A Test actor position offset (arbitrary value) **/
const Vector3 SCROLL_VIEW_TEST_CONSTRAINT_OFFSET(1.0f, 2.0f, 0.0f);               /** A Test constraint offset (arbitrary value to test effects) **/
const unsigned int SCROLL_VIEW_RENDER_DELAY_SCROLL = 1000u;                       /**duration to wait for any scroll to complete */
const Vector2 SCROLL_TARGET_2 = Vector2(150.0f,150.0f);                           /** Target position 2**/
const Vector2 SCROLL_TARGET_1 = Vector2(50.0f,50.0f);                             /** Target position 1**/
const float SCROLL_VIEW_RULER_SIZE_NEW = 200.0f;                                  /** New Ruler Size **/
const float SCROLL_TARGET_X = 90.0f;                                              /** Target scroll x position **/
const float SCROLL_TARGET_Y = 400.0f;                                             /** Target scroll y position **/
const float SCROLL_TARGET_Z = 0.0f;                                               /** Target scroll z position **/
const int SCROLL_DESTINATION = 2;                                                 /** Destination page number **/
float gScrollDurSet = 0.7f;                                                       /** Scroll duration **/

/**
 * @function                    ScrollViewOnScrollStart
 * @description                 Invoked when scrolling starts.
 * @return                      NA
 */
void ScrollViewOnScrollStart( const Vector2& vec2Position )
{
  if( vec2Position == Vector2::ZERO )
  {
    gScrollViewOnScrollStartCalled = true;
  }
}


/**
 * @function                    ScrollViewOnScrollUpdate
 * @description                 Invoked when scrolling updates (via dragging)
 * @return                      NA
 */
void ScrollViewOnScrollUpdate( const Vector2& vec2Position )
{
  Vector2 vec2Init = Vector2::ZERO;
  Vector2 vec2Target = Vector2( SCROLL_TARGET_X, SCROLL_TARGET_Y );

  if( (vec2Position.x > vec2Init.x && vec2Init.x <= vec2Target.x) &&
      (vec2Position.y > vec2Init.y && vec2Init.y <= vec2Target.y) )
  {
    gScrollViewOnScrollUpdateCalled = true;
  }
}


/**
 * @function                    ScrollViewOnScrollComplete
 * @description                 Invoked when scrolling finishes
 * @return                      NA
 */
void ScrollViewOnScrollComplete( const Vector2& vec2Position )
{
  if(vec2Position == Vector2( SCROLL_TARGET_X, SCROLL_TARGET_Y ))
  {
    gScrollViewOnScrollCompleteCalled = true;
  }
}

/**
 * ScrollviewSumConstraint
 *
 * Summation of current value, property, and offset.
 *
 * current' = current + m_Offset + property;
 */
struct ScrollviewSumConstraint
{
  /**
   * @param[in] offset The offset to be added to current.
   */
  ScrollviewSumConstraint(const Vector3& offset):m_Offset(offset)
  {
  }

  /**
   * @param [in] vec3Current The current base value
   * @param [in] property The property to be added to current.
   * @return The new vec3Current Vector.
   */
  void operator()( Vector3& current, const PropertyInputContainer& inputs )
  {
    gVec3ScrollviewConstraintResult = current + Vector3(inputs[0]->GetVector2()) + m_Offset;
    current = gVec3ScrollviewConstraintResult;
  }

  Vector3 m_Offset;

};


/**
 * @function                    ScrollViewTestAlphaFunction
 * @description                 y = 2x alpha function, which is clamped between 0.0f - 1.0f
 * @return                      interpolation value (ranges from 0.0f - 1.0f)
 */
float ScrollViewTestAlphaFunction(float fProgress)
{
  return std::min( fProgress * 2.0f, 1.0f );
}

/**
 * @function                    ScrollViewCreateRuler
 * @description                 Creates a Ruler that snaps to a specified grid size.
 * @return                      The ruler is returned.
 */
RulerPtr ScrollViewCreateRuler(float fGridSize = 0.0f)
{
  if(fGridSize <= Math::MACHINE_EPSILON_0)
  {
    return new DefaultRuler();
  }
  return new FixedRuler(fGridSize);
}

/**
 * @function                    ScrollViewSetupTest
 * @description                 Sets up a scrollview
 * @return                      ScrollView
 */
ScrollView ScrollViewSetupTest(int nRows, int nColumns, Vector2 vec2Size)
{
  Constraint constraint;

  ScrollView scrollView = ScrollView::New();
  scrollView.SetSize(vec2Size);
  scrollView.SetAnchorPoint(AnchorPoint::CENTER);
  scrollView.SetParentOrigin(ParentOrigin::CENTER);

  constraint = Constraint::New<Dali::Vector3>( scrollView, Dali::Actor::Property::SIZE, Dali::EqualToConstraint() );
  constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
  constraint.Apply();

  scrollView.SetWrapMode(false);
  Stage::GetCurrent().Add( scrollView );
  RulerPtr rulerX = ScrollViewCreateRuler(vec2Size.width);
  RulerPtr rulerY = ScrollViewCreateRuler(vec2Size.height);
  if(nColumns > 1)
  {
    rulerX->SetDomain(RulerDomain(0.0f, vec2Size.width * nColumns));
  }
  else
  {
    rulerX->Disable();
  }
  if(nRows > 1)
  {
    rulerY->SetDomain(RulerDomain(0.0f, vec2Size.width * nRows));
  }
  else
  {
    rulerY->Disable();
  }

  scrollView.SetRulerX( rulerX );
  scrollView.SetRulerY( rulerY );
  Stage::GetCurrent().Add( scrollView );

  Actor container = Actor::New();
  container.SetParentOrigin(ParentOrigin::CENTER);
  container.SetAnchorPoint(AnchorPoint::CENTER);
  container.SetSize( vec2Size );
  scrollView.Add( container );

  constraint = Constraint::New<Vector3>( container, Actor::Property::SIZE, EqualToConstraint() );
  constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
  constraint.Apply();

  gVecPagesActor.clear();
  for(int row = 0;row<nRows;row++)
  {
    for(int column = 0;column<nColumns;column++)
    {
      Actor page = Actor::New();

      constraint = Constraint::New<Vector3>( page, Actor::Property::SIZE, EqualToConstraint() );
      constraint.AddSource( Dali::ParentSource( Dali::Actor::Property::SIZE ) );
      constraint.Apply();
      page.SetParentOrigin( ParentOrigin::CENTER );
      page.SetAnchorPoint( AnchorPoint::CENTER );
      page.SetPosition( column * vec2Size.x, row * vec2Size.y );
      container.Add(page);

      gVecPagesActor.push_back(page);
    }
  }

  return scrollView;
}

void ScrollViewConstructorP();
void ScrollViewNewP();
void ScrollViewCopyConstructorP();
void ScrollViewOperatorAssignmentP();
void ScrollViewDownCastP();
void ScrollViewDownCastN();
void ScrollViewSetGetScrollSnapAlphaFunctionP();
void ScrollViewSetGetScrollFlickAlphaFunctionP();
void ScrollViewSetGetScrollFlickDurationP();
void ScrollViewSetGetScrollSnapDurationP();
void ScrollViewSetRulerP();
void ScrollViewSetScrollSensitiveP();
void ScrollViewSetActorAutoSnapP();
void ScrollViewSetWrapModeP();
void ScrollViewGetSetScrollUpdateDistanceP();
void ScrollViewSetGetAxisAutoLockP();
void ScrollViewSetGetAxisAutoLockGradientP();
void ScrollViewSetGetFrictionCoefficientP();
void ScrollViewSetGetFlickSpeedCoefficientP();
void ScrollViewGetSetMinimumDistanceForFlickP();
void ScrollViewGetSetMinimumSpeedForFlickP();
void ScrollViewSetGetMaxFlickSpeedP();
void ScrollViewSetGetWheelScrollDistanceStepP();
void ScrollViewGetCurrentPageP();
void ScrollViewGetCurrentScrollPositionP();
void ScrollViewScrollToPositionDurationP();
void ScrollViewScrollToPositionP();
void ScrollViewScrollToPositionToPageDurationP();
void ScrollViewScrollToPageP();
void ScrollViewScrollToActorDurationP();
void ScrollViewScrollToSpecifiedActorP();
void ScrollViewScrollToSnapPointP();
void ScrollViewScrollToPositionWithAlphaFunctionP();
void ScrollViewScrollToPositionWithAlphaFunctionAndDirectionBiasP();
void ScrollViewScrollToPositionWithDirectionBiasP();
void ScrollViewScrollToPageWithDirectionBiasP();
void ScrollViewConstraintsP();
void ScrollViewApplyAndRemoveAllEffectP();
void ScrollViewBindUnbindActorP();
void ScrollViewGetOvershootAnimationSpeedP();
void ScrollViewGetOvershootEffectColorP();
void VTScrollViewSetScrollSensitive001();
void VTScrollViewSetScrollSensitive002();
void VTScrollViewActorAutoSnap001();
void VTScrollViewActorAutoSnap003();
void VTScrollViewActorAutoSnap002();
void VTScrollViewSetWrapMode001();
void VTScrollViewSetWrapMode002();
void VTScrollViewGetCurrentPage001();
void VTScrollViewGetCurrentScrollPosition001();
void VTScrollViewScrollToPositionDuration001();
void VTScrollViewScrollToPosition001();
void ScrollViewScrollToPositionToPageDuration001();
void VTScrollViewScrollToPage001();
void VTScrollViewScrollToActorDuration001();
void VTScrollViewScrollToActorDuration002();
void VTScrollViewScrollToSpecifiedActor001();
void VTScrollViewScrollToSpecifiedActor002();
void VTScrollViewScrollToSnapPoint001();
void VTScrollViewScrollToSnapPoint002();
void VTScrollViewScrollToPositionWithAlphaFunction001();
void VTScrollViewScrollToPositionWithAlphaFunction002();
void VTScrollViewScrollToPositionWithAlphaFunction003();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias001();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias002();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias003();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias004();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias005();
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias006();
void VTScrollViewScrollToPositionWithDirectionBias001();
void VTScrollViewScrollToPositionWithDirectionBias002();
void VTScrollViewScrollToPositionWithDirectionBias003();
void VTScrollViewScrollToPositionWithDirectionBias004();
void VTScrollViewScrollToPageWithDirectionBias001();
void VTScrollViewScrollToPageWithDirectionBias002();
void VTScrollViewConstraints001();
void VTScrollViewConstraints002();
void VTScrollViewBindUnbindActor001();
void VTScrollViewBindUnbindActor002();
void VTScrollViewBindUnbindActor003();


namespace
{
  enum TEST_CASES_LIST_SCROLL_VIEW
  {
    SCROLL_VIEW_CONSTRUCTOR_P,
    SCROLL_VIEW_COPY_CONSTRUCTOR_P,
    SCROLL_VIEW_NEW_P,
    SCROLL_VIEW_OPERATOR_ASSIGNMENT_P,
    SCROLL_VIEW_DOWNCAST_P,
    SCROLL_VIEW_DOWNCAST_N,
    SCROLL_VIEW_SET_GET_SCROLL_SNAP_ALPHA_FUNCTION_P,
    SCROLL_VIEW_SET_GET_SCROLL_FLICK_ALPHA_FUNCTION_P,
    SCROLL_VIEW_SET_GET_SCROLL_SNAP_DURATION_P,
    SCROLL_VIEW_SET_GET_SCROLL_FLICK_DURATION_P,
    SCROLL_VIEW_SET_RULER_P,
    SCROLL_VIEW_SET_SCROLL_SENSITIVE_P,
    SCROLL_VIEW_SET_ACTOR_AUTO_SNAP_P,
    SCROLL_VIEW_SET_WRAP_MODE_P,
    SCROLL_VIEW_GET_SET_SCROLL_UPDATE_DISTANCE_P,
    SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_P,
    SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_GRADIENT_P,
    SCROLL_VIEW_SET_GET_FRICTION_COEFFICIENT_P,
    SCROLL_VIEW_SET_GET_FLICK_SPEED_COEFFICIENT_P,
    SCROLL_VIEW_GET_SET_MINIMUM_DISTANCE_FOR_FLICK_P,
    SCROLL_VIEW_GET_SET_MINIMUM_SPEED_FOR_FLICK_P,
    SCROLL_VIEW_SET_GET_MAX_FLICK_SPEED_P,
    SCROLL_VIEW_SET_GET_WHEEL_SCROLL_DISTANCE_STEP_P,
    SCROLL_VIEW_GET_CURRENT_PAGE_P,
    SCROLL_VIEW_GET_CURRENT_SCROLL_POSITION_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_DURATION_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_TO_PAGE_DURATION_P,
    SCROLL_VIEW_SCROLL_TO_PAGE_P,
    SCROLL_VIEW_SCROLL_TO_ACTOR_DURATION_P,
    SCROLL_VIEW_SCROLL_TO_SPECIFIED_ACTOR_P,
    SCROLL_VIEW_SCROLL_TO_SNAP_POINT_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_AND_DIRECTION_BIAS_P,
    SCROLL_VIEW_SCROLL_TO_POSITION_WITH_DIRECTION_BIAS_P,
    SCROLL_VIEW_SCROLL_TO_PAGE_WITH_DIRECTION_BIAS_P,
    SCROLL_VIEW_CONSTRAINTS_P,
    SCROLL_VIEW_APPLY_AND_REMOVE_ALL_EFFECT_P,
    SCROLL_VIEW_BIND_UNBIND_ACTOR_P,
    SCROLL_VIEW_GET_OVER_SHOOT_ANIMATION_SPEED_P,
    SCROLL_VIEW_GET_OVERSHOOT_EFFECT_COLOR_P
  };

  struct ScrollView_TestApp : public ConnectionTracker
  {
    ScrollView_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ScrollView_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( GInterval );
      mTimer.TickSignal().Connect( this, &ScrollView_TestApp::Tick );
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
        case SCROLL_VIEW_CONSTRUCTOR_P:
          ScrollViewConstructorP();
          break;

        case SCROLL_VIEW_NEW_P:
          ScrollViewNewP();
          break;

        case SCROLL_VIEW_COPY_CONSTRUCTOR_P:
          ScrollViewCopyConstructorP();
          break;

        case SCROLL_VIEW_OPERATOR_ASSIGNMENT_P:
          ScrollViewOperatorAssignmentP();
          break;

        case SCROLL_VIEW_DOWNCAST_P:
          ScrollViewDownCastP();
          break;

        case SCROLL_VIEW_DOWNCAST_N:
          ScrollViewDownCastN();
          break;

        case SCROLL_VIEW_SET_GET_SCROLL_SNAP_ALPHA_FUNCTION_P:
          ScrollViewSetGetScrollSnapAlphaFunctionP();
          break;

        case SCROLL_VIEW_SET_GET_SCROLL_FLICK_ALPHA_FUNCTION_P:
          ScrollViewSetGetScrollFlickAlphaFunctionP();
          break;

        case SCROLL_VIEW_SET_GET_SCROLL_FLICK_DURATION_P:
          ScrollViewSetGetScrollFlickDurationP();
          break;

        case SCROLL_VIEW_SET_GET_SCROLL_SNAP_DURATION_P:
          ScrollViewSetGetScrollSnapDurationP();
          break;

        case SCROLL_VIEW_SET_RULER_P:
          ScrollViewSetRulerP();
          break;

        case SCROLL_VIEW_SET_SCROLL_SENSITIVE_P:
          ScrollViewSetScrollSensitiveP();
          break;

        case SCROLL_VIEW_SET_ACTOR_AUTO_SNAP_P:
          ScrollViewSetActorAutoSnapP();
          break;

        case SCROLL_VIEW_SET_WRAP_MODE_P:
          ScrollViewSetWrapModeP();
          break;

        case SCROLL_VIEW_GET_SET_SCROLL_UPDATE_DISTANCE_P:
          ScrollViewGetSetScrollUpdateDistanceP();
          break;

        case SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_P:
          ScrollViewSetGetAxisAutoLockP();
          break;

        case SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_GRADIENT_P:
          ScrollViewSetGetAxisAutoLockGradientP();
          break;

        case SCROLL_VIEW_SET_GET_FLICK_SPEED_COEFFICIENT_P:
          ScrollViewSetGetFlickSpeedCoefficientP();
          break;

        case SCROLL_VIEW_SET_GET_FRICTION_COEFFICIENT_P:
          ScrollViewSetGetFrictionCoefficientP();
          break;

        case SCROLL_VIEW_GET_SET_MINIMUM_DISTANCE_FOR_FLICK_P:
          ScrollViewGetSetMinimumDistanceForFlickP();
          break;

        case SCROLL_VIEW_GET_SET_MINIMUM_SPEED_FOR_FLICK_P:
          ScrollViewGetSetMinimumSpeedForFlickP();
          break;

        case SCROLL_VIEW_SET_GET_MAX_FLICK_SPEED_P:
          ScrollViewSetGetMaxFlickSpeedP();
          break;

        case SCROLL_VIEW_SET_GET_WHEEL_SCROLL_DISTANCE_STEP_P:
          ScrollViewSetGetWheelScrollDistanceStepP();
          break;

        case SCROLL_VIEW_GET_CURRENT_PAGE_P:
          ScrollViewGetCurrentPageP();
          break;

        case SCROLL_VIEW_GET_CURRENT_SCROLL_POSITION_P:
          ScrollViewGetCurrentScrollPositionP();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_DURATION_P:
          ScrollViewScrollToPositionDurationP();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_P:
          ScrollViewScrollToPositionP();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_TO_PAGE_DURATION_P:
          ScrollViewScrollToPositionToPageDurationP();
          break;

        case SCROLL_VIEW_SCROLL_TO_PAGE_P:
          ScrollViewScrollToPageP();
          break;

        case SCROLL_VIEW_SCROLL_TO_ACTOR_DURATION_P:
          ScrollViewScrollToActorDurationP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_SPECIFIED_ACTOR_P:
          ScrollViewScrollToSpecifiedActorP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_SNAP_POINT_P:
          ScrollViewScrollToSnapPointP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_P:
          ScrollViewScrollToPositionWithAlphaFunctionP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_AND_DIRECTION_BIAS_P:
          ScrollViewScrollToPositionWithAlphaFunctionAndDirectionBiasP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_DIRECTION_BIAS_P:
          ScrollViewScrollToPositionWithDirectionBiasP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_SCROLL_TO_PAGE_WITH_DIRECTION_BIAS_P:
          ScrollViewScrollToPageWithDirectionBiasP();
          GInterval = SCROLL_VIEW_RENDER_DELAY_SCROLL;
          break;

        case SCROLL_VIEW_CONSTRAINTS_P:
          ScrollViewConstraintsP();
          break;

        case SCROLL_VIEW_APPLY_AND_REMOVE_ALL_EFFECT_P:
          ScrollViewApplyAndRemoveAllEffectP();
          break;

        case SCROLL_VIEW_BIND_UNBIND_ACTOR_P:
          ScrollViewBindUnbindActorP();
          break;

        case SCROLL_VIEW_GET_OVER_SHOOT_ANIMATION_SPEED_P:
          ScrollViewGetOvershootAnimationSpeedP();
          break;

        case SCROLL_VIEW_GET_OVERSHOOT_EFFECT_COLOR_P:
          ScrollViewGetOvershootEffectColorP();
          break;
      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case SCROLL_VIEW_SET_ACTOR_AUTO_SNAP_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewActorAutoSnap001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewActorAutoSnap002();
              GRenderCountScrollView++;
              break;

            case 2:
              VTScrollViewActorAutoSnap003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_BIND_UNBIND_ACTOR_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewBindUnbindActor001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewBindUnbindActor002();
              GRenderCountScrollView++;
              break;

            case 2:
              VTScrollViewBindUnbindActor003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_CONSTRAINTS_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewConstraints001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewConstraints002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_ACTOR_DURATION_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToActorDuration001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToActorDuration002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_SPECIFIED_ACTOR_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToSpecifiedActor001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToSpecifiedActor002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_SNAP_POINT_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToSnapPoint001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToSnapPoint002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SET_WRAP_MODE_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewSetWrapMode001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewSetWrapMode002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_GET_CURRENT_PAGE_P:
          VTScrollViewGetCurrentPage001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_SCROLL_TO_PAGE_P:
          VTScrollViewScrollToPage001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_P:
          VTScrollViewScrollToPosition001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_GET_CURRENT_SCROLL_POSITION_P:
          VTScrollViewGetCurrentScrollPosition001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_DURATION_P:
          VTScrollViewScrollToPositionDuration001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToPositionWithAlphaFunction001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToPositionWithAlphaFunction002();
              GRenderCountScrollView++;
              break;

            case 2:
              VTScrollViewScrollToPositionWithAlphaFunction003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_PAGE_WITH_DIRECTION_BIAS_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToPageWithDirectionBias001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToPageWithDirectionBias002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_TO_PAGE_DURATION_P:
          ScrollViewScrollToPositionToPageDuration001();
          mTimer.Stop();
          mApplication.Quit();
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_AND_DIRECTION_BIAS_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias002();
              GRenderCountScrollView++;
              break;

            case 2:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias003();
              GRenderCountScrollView++;
              break;

            case 3:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias004();
              GRenderCountScrollView++;
              break;

            case 4:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias005();
              GRenderCountScrollView++;
              break;

            case 5:
              VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias006();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SCROLL_TO_POSITION_WITH_DIRECTION_BIAS_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewScrollToPositionWithDirectionBias001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewScrollToPositionWithDirectionBias002();
              GRenderCountScrollView++;
              break;

            case 2:
              VTScrollViewScrollToPositionWithDirectionBias003();
              GRenderCountScrollView++;
              break;

            case 3:
              VTScrollViewScrollToPositionWithDirectionBias004();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case SCROLL_VIEW_SET_SCROLL_SENSITIVE_P:
          switch(GRenderCountScrollView)
          {
            case 0:
              VTScrollViewSetScrollSensitive001();
              GRenderCountScrollView++;
              break;

            case 1:
              VTScrollViewSetScrollSensitive002();
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

void ScrollViewConstructorP(void)
{
  ScrollView ScrollView;
  DALI_CHECK_FAIL(ScrollView,  "ScrollView Default Contructor is failed");

  DaliLog::PrintPass();
}


void ScrollViewNewP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  DaliLog::PrintPass();
}

void ScrollViewCopyConstructorP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  ScrollView copyScrollView(scrollView);
  DALI_CHECK_FAIL(copyScrollView != scrollView, " Copy Constructor is mismatched for ScrollView.");

  DaliLog::PrintPass();
}

void ScrollViewOperatorAssignmentP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  ScrollView copyScrollView = scrollView;
  DALI_CHECK_FAIL(copyScrollView != scrollView, " Assignment operator is failed for ScrollView.");

  DaliLog::PrintPass();
}

void ScrollViewDownCastP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  BaseHandle handle(scrollView);
  DALI_CHECK_FAIL(!handle, " Base Handle Creation failed.");

  ScrollView newScrollView = ScrollView::DownCast( handle );
  DALI_CHECK_FAIL(!newScrollView, " ScrollView::DownCast API failed.");

  DaliLog::PrintPass();
}

void ScrollViewDownCastN()
{
  BaseHandle unInitializedObject;

  ScrollView ScrollView1 = ScrollView::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(ScrollView1, "ScrollView handle is not empty." );

  ScrollView ScrollView2 = DownCast< ScrollView >( unInitializedObject );
  DALI_CHECK_FAIL(ScrollView2, "ScrollView handle is not empty." );

  DaliLog::PrintPass();

}

void ScrollViewSetGetScrollSnapAlphaFunctionP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_OUT,ALPHAFUNCTION_EASE_OUT), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::DEFAULT,ALPHAFUNCTION_DEFAULT), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::LINEAR,ALPHAFUNCTION_LINEAR), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::REVERSE,ALPHAFUNCTION_REVERSE), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_IN_OUT,ALPHAFUNCTION_EASE_IN_OUT), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_IN_SINE,ALPHAFUNCTION_EASE_IN_SINE), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_OUT_SINE,ALPHAFUNCTION_EASE_OUT_SINE), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_IN_OUT_SINE,ALPHAFUNCTION_EASE_IN_OUT_SINE), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");
  ;
  DALI_CHECK_FAIL(!ScrollViewSetGetSnapAplhaFunction(scrollView,AlphaFunction::EASE_IN,ALPHAFUNCTION_EASE_IN), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();

}

void ScrollViewSetGetScrollFlickAlphaFunctionP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  DALI_CHECK_FAIL(!ScrollViewSetGetFilckAplhaFunction(scrollView,AlphaFunction::DEFAULT,ALPHAFUNCTION_DEFAULT), " SetScrollFlickAlphaFunction and GetScrollFlickAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetFilckAplhaFunction(scrollView,AlphaFunction::LINEAR,ALPHAFUNCTION_LINEAR), " SetScrollSnapAlphaFunction and GetScrollSnapAlphaFunction is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetFilckAplhaFunction(scrollView,AlphaFunction::SIN,ALPHAFUNCTION_SIN), " SetMaxFlickSpeed and GetMaxFlickSpeed is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetFilckAplhaFunction(scrollView,AlphaFunction::EASE_IN,ALPHAFUNCTION_EASE_IN), " SetMaxFlickSpeed and GetMaxFlickSpeed is mismatched for ScrollView.");

  DALI_CHECK_FAIL(!ScrollViewSetGetFilckAplhaFunction(scrollView,AlphaFunction::EASE_OUT,ALPHAFUNCTION_EASE_OUT), " SetFilckAplhaFunction and GetFilckAplhaFunction is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetScrollFlickDurationP()
{
  const float SET_FLICK_DURATION = 0.4f;
  float fFlickDuration = 0.0f;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetScrollFlickDuration (SET_FLICK_DURATION);
  fFlickDuration = scrollView.GetScrollFlickDuration();
  DALI_CHECK_FAIL(fFlickDuration != SET_FLICK_DURATION, " SetScrollFlickDuration and GetScrollFlickDuration is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetScrollSnapDurationP()
{
  const float TIME_OF_ANIMATION_SCROLL = 0.66f ;
  float fScrollSnapDuration = 0.0f;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  scrollView.SetScrollSnapDuration(TIME_OF_ANIMATION_SCROLL);
  fScrollSnapDuration = scrollView.GetScrollSnapDuration();
  DALI_CHECK_FAIL( fScrollSnapDuration != TIME_OF_ANIMATION_SCROLL, " SetScrollSnapDuration and GetScrollSnapDuration is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetRulerP()
{
  float fMax = 1000.0f , fMin = 0.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRularScale = false;
  gScrollViewOnScrollStartCalled = false;
  gScrollViewOnScrollUpdateCalled = false;
  gScrollViewOnScrollCompleteCalled = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRularScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,false,true);
  DALI_CHECK_FAIL(!bSetRularScale, " Set Ruler position is failed.");

  DaliLog::PrintPass();
}

void ScrollViewSetScrollSensitiveP()
{
  float fMax = 1000.0f , fMin = 0.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRularScale = false;
  gScrollViewOnScrollStartCalled = false;
  gScrollViewOnScrollUpdateCalled = false;
  gScrollViewOnScrollCompleteCalled = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRularScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,false,true);
  DALI_CHECK_FAIL(!bSetRularScale, " Set Ruler position is failed.");

  gScrollView.SetScrollSensitive(true);
  gScrollView.ScrollStartedSignal().Connect( &ScrollViewOnScrollStart );
  gScrollView.ScrollUpdatedSignal().Connect( &ScrollViewOnScrollUpdate );
  gScrollView.ScrollCompletedSignal().Connect( &ScrollViewOnScrollComplete );
  gScrollView.ScrollTo( Vector2( SCROLL_TARGET_X, SCROLL_TARGET_Y ) , gScrollDurSet );
}

// * ############################## Verdict test for ScrollViewSetScrollSensitive

void VTScrollViewSetScrollSensitive001()
{
  DALI_CHECK_FAIL( !gScrollViewOnScrollStartCalled || !gScrollViewOnScrollUpdateCalled, " ScrollViewSignal Scrolling Failed to start and update.");
}

void VTScrollViewSetScrollSensitive002()
{
  DALI_CHECK_FAIL( !gScrollViewOnScrollCompleteCalled, " ScrollViewSignal Scrolling Failed to complete.");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetActorAutoSnapP()
{
  float fMin = 0.0f,fMax = 800.0f,fRulerSize = 100.0f;
  Vector2 vec2ScrollToPos(0.0f, 0.0f);
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,false,true);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  Actor actor = Actor::New();
  gScrollView.Add(actor);
  actor.SetPosition(SCROLL_VIEW_TEST_ACTOR_POSITION);

  //ScrollTo [150.0f 150.0f]
  gScrollView.ScrollTo(SCROLL_TARGET_2, SCROLL_DURATION);
}

// * ############################## Verdict test for ScrollViewActorAutoSnap

void VTScrollViewActorAutoSnap001()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, " ScrollTo is failed");

  gScrollView.SetScrollSnapDuration(0.1f);

  //Try to snap without enabling true
  gScrollView.ScrollToSnapPoint();
}
void VTScrollViewActorAutoSnap002()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "Should not execute snap without enabling true.");

  //Try to snap with enabling true
  gScrollView.SetActorAutoSnap(true);
  gScrollView.ScrollToSnapPoint();
}
void VTScrollViewActorAutoSnap003()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != SCROLL_VIEW_TEST_ACTOR_POSITION.GetVectorXY() , " ScrollViewActorAutoSnap is Failed.");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetWrapModeP()
{
  float fRulerSize = 50.0f , fMin = 0.0f , fMax = 200.0f;
  const float TARGET_X = 225.0f , TARGET_Y = 125.0f;

  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,false,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.SetWrapMode(false);
  gScrollView.ScrollTo(Vector2(TARGET_X, TARGET_Y), SCROLL_DURATION); // 5th (1st) page across, and 3rd (3rd) page down. (wrapped)
}

// * ############################## Verdict test for ScrollViewSetWrapMode

void VTScrollViewSetWrapMode001()
{
  const int PAGEVALUE_ACCORDING_TO_VECTOR = 17; /**@note value needs to verify*/
  const Vector2 VEC2_NEW_TARGET = Vector2(230.0f, 130.0f);

  int nCurrentPage = static_cast<int>(gScrollView.GetCurrentPage());
  DALI_CHECK_FAIL(nCurrentPage != PAGEVALUE_ACCORDING_TO_VECTOR , " ScrollTo API failed with wrap mode false.");

  gScrollView.SetWrapMode(true);
  gScrollView.ScrollTo(VEC2_NEW_TARGET, SCROLL_DURATION); // 5th (1st) page across, and 3rd (3rd) page down. (wrapped)
}
void VTScrollViewSetWrapMode002()
{
  const int PAGEVALUE_ACCORDING_AFTER_WRAP = 13; /**@note value needs to verify*/

  int nCurrentPage = static_cast<int>(gScrollView.GetCurrentPage());
  DALI_CHECK_FAIL(nCurrentPage != PAGEVALUE_ACCORDING_AFTER_WRAP , " ScrollTo API failed with wrap mode true.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewGetSetScrollUpdateDistanceP()
{
  int nScrollUpdateDistance = 100;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  scrollView.SetScrollUpdateDistance(nScrollUpdateDistance);
  DALI_CHECK_FAIL( scrollView.GetScrollUpdateDistance() != nScrollUpdateDistance,"SetScrollUpdateDistance value is miss matched with GetScrollUpdateDistance");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetAxisAutoLockP()
{
  bool bAxisAutoLockOn = false , bReturnAutoLock = false;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetAxisAutoLock(bAxisAutoLockOn);
  bReturnAutoLock = scrollView.GetAxisAutoLock();
  DALI_CHECK_FAIL(bAxisAutoLockOn != bReturnAutoLock, " SetAxisAutoLock and GetAxisAutoLock is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetAxisAutoLockGradientP()
{
  const float SET_AXIS_AUTO_LOCK_GRADIENT = 1.0f;
  float fAxisAutoLockGradient = 0.0f ;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetAxisAutoLockGradient(SET_AXIS_AUTO_LOCK_GRADIENT);
  fAxisAutoLockGradient = scrollView.GetAxisAutoLockGradient();
  DALI_CHECK_FAIL(fAxisAutoLockGradient != SET_AXIS_AUTO_LOCK_GRADIENT, " SetAxisAutoLockGradient and GetAxisAutoLockGradient is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetFrictionCoefficientP()
{
  const float SET_FRICTION_COEFFICIENT = 0.06f;
  float fFrictionCoefficient = 0.0f ;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetFrictionCoefficient(SET_FRICTION_COEFFICIENT);
  fFrictionCoefficient = scrollView.GetFrictionCoefficient();
  DALI_CHECK_FAIL(fFrictionCoefficient != SET_FRICTION_COEFFICIENT, " SetAxisAutoLock and GetAxisAutoLock is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetFlickSpeedCoefficientP()
{
  const float SET_FLICK_SPEED_COEFFICIENT = 1.0f;
  float fFlickSpeedCoefficient = 0.0f ;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  scrollView.SetFlickSpeedCoefficient(SET_FLICK_SPEED_COEFFICIENT/2);
  fFlickSpeedCoefficient = scrollView.GetFlickSpeedCoefficient();
  DALI_CHECK_FAIL(fFlickSpeedCoefficient != SET_FLICK_SPEED_COEFFICIENT/2, " SetFlickSpeedCoefficient and GetFlickSpeedCoefficient is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewGetSetMinimumDistanceForFlickP()
{
  const Vector2 VEC2_TARGET = Vector2(100.0f,0.0f);

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetMinimumDistanceForFlick(VEC2_TARGET);
  DALI_CHECK_FAIL( scrollView.GetMinimumDistanceForFlick() != VEC2_TARGET, "SetMinimumDistanceForFlick value is miss matched with GetMinimumDistanceForFlick");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewGetSetMinimumSpeedForFlickP()
{
  float fMinSpeedForFlick = 10.0f;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetMinimumSpeedForFlick(fMinSpeedForFlick);
  DALI_CHECK_FAIL( scrollView.GetMinimumSpeedForFlick() != fMinSpeedForFlick,
      "SetMinimumSpeedForFlick value is miss matched with GetMinimumSpeedForFlick");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetMaxFlickSpeedP()
{
  const float SET_MAX_FLICK_SPEED = 0.6f ;
  float fMaxFlickSpeed = 0.0f;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  scrollView.SetMaxFlickSpeed(SET_MAX_FLICK_SPEED);
  fMaxFlickSpeed = scrollView.GetMaxFlickSpeed();
  DALI_CHECK_FAIL(fMaxFlickSpeed != SET_MAX_FLICK_SPEED, " SetMaxFlickSpeed and GetMaxFlickSpeed is mismatched for ScrollView.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewSetGetWheelScrollDistanceStepP()
{
  const float DISTANCE_X = 30.0f , DISTANCE_Y = 15.0f;
  Vector2 vec2ScrollDistanceGet;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, " ScrollView::New() is failed.");

  Vector2 vec2ScrollDistanceSet = Vector2(DISTANCE_X, DISTANCE_Y);
  scrollView.SetWheelScrollDistanceStep(vec2ScrollDistanceSet);
  vec2ScrollDistanceGet = scrollView.GetWheelScrollDistanceStep();
  DALI_CHECK_FAIL(vec2ScrollDistanceSet != vec2ScrollDistanceGet, " GetWheelScrollDistanceStep and SetWheelScrollDistanceStep is mismatched for ScrollView.");

  DaliLog::PrintPass();
}

void ScrollViewGetCurrentPageP()
{
  float fMin = 0.0f,fMax = 800.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.ScrollTo( SCROLL_DESTINATION );
}

// * ############################## Verdict test for ScrollViewGetCurrentPage

void VTScrollViewGetCurrentPage001()
{
  int nPageNum = static_cast<int>(gScrollView.GetCurrentPage());
  DALI_CHECK_FAIL(nPageNum != SCROLL_DESTINATION, " GetCurrentPage API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();

}

void ScrollViewGetCurrentScrollPositionP()
{
  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  const Vector2 vec2Target = Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y);
  gScrollView.ScrollTo( vec2Target, SCROLL_DURATION );
}

// * ############################## Verdict test for ScrollViewGetCurrentScrollPosition

void VTScrollViewGetCurrentScrollPosition001()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition()!= Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y), " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionDurationP()
{
  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  const Vector2 vec2Target = Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y);
  gScrollView.ScrollTo( vec2Target, SCROLL_DURATION );
}

// * ############################## Verdict test for ScrollViewScrollToPositionDuration

void VTScrollViewScrollToPositionDuration001()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition()!= Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y), " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionP()
{
  float fMin = 0.0f,fMax = 800.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.ScrollTo( SCROLL_DESTINATION );
}

// * ############################## Verdict test for ScrollViewScrollToPosition

void VTScrollViewScrollToPosition001()
{
  int nPageNum = static_cast<int>(gScrollView.GetCurrentPage());
  DALI_CHECK_FAIL(nPageNum != SCROLL_DESTINATION, " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionToPageDurationP()
{
  float fMin = 0.0f,fMax = 800.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,SCROLL_VIEW_RULER_SIZE_NEW,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.ScrollTo( SCROLL_DESTINATION, SCROLL_DURATION );
}

// * ############################## Verdict test for ScrollViewScrollToPositionToPageDuration

void ScrollViewScrollToPositionToPageDuration001()
{
  //Expected position is [400, 0], as rular size is 200;
  //page number 2, Max rular limit 800; 400(2*200) is within limit, so position will change in x direction

  Vector2 vec2ExpectedPosition = Vector2( SCROLL_DESTINATION*SCROLL_VIEW_RULER_SIZE_NEW, 0.0f );
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != vec2ExpectedPosition, " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPageP()
{
  float fMin = 0.0f,fMax = 800.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.ScrollTo( SCROLL_DESTINATION );
}

// * ############################## Verdict test for ScrollViewScrollToPage

void VTScrollViewScrollToPage001()
{
  int nPageNum = static_cast<int>(gScrollView.GetCurrentPage());
  DALI_CHECK_FAIL(nPageNum != SCROLL_DESTINATION, " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToActorDurationP()
{
  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  const Vector3 POSSITION_A = Vector3(SCROLL_TARGET_X,SCROLL_TARGET_Y,SCROLL_TARGET_Z);
  gActorA = Actor::New();
  gActorA.SetPosition(POSSITION_A);
  gScrollView.Add(gActorA);
}

// * ############################## Verdict test for ScrollViewScrollToActorDuration

void VTScrollViewScrollToActorDuration001()
{
  float fDuration = 0.25f;
  //Actor is rendered to stage with the position, now scroll to the actor
  gScrollView.ScrollTo(gActorA, fDuration);
}
void VTScrollViewScrollToActorDuration002()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != Vector2(SCROLL_TARGET_X,SCROLL_TARGET_Y), " ScrollTo API failed to  View the position specified.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToSpecifiedActorP()
{
  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  const Vector3 POSITION_A = Vector3(SCROLL_TARGET_X, SCROLL_TARGET_Y,SCROLL_TARGET_Z);
  gActorA = Actor::New();
  gActorA.SetPosition(POSITION_A);
  gScrollView.Add(gActorA);
}

// * ############################## Verdict test for ScrollViewScrollToSpecifiedActor

void VTScrollViewScrollToSpecifiedActor001()
{
  //Actor is rendered to stage with the position, now scroll to the actor
  gScrollView.ScrollTo(gActorA);
}
void VTScrollViewScrollToSpecifiedActor002()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y), " ScrollTo API failed.");

  Stage::GetCurrent().Remove( gScrollView );
  DaliLog::PrintPass();
}


void ScrollViewScrollToSnapPointP()
{
  float fMin = 0.0f,fMax = 800.0f,fRulerSize = 100.0f;
  RulerPtr rulerX;
  RulerPtr rulerY;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.ScrollTo( Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y), SCROLL_DURATION);

}

// * ############################## Verdict test for ScrollViewScrollToSnapPoint

void VTScrollViewScrollToSnapPoint001()
{
  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != Vector2(SCROLL_TARGET_X, SCROLL_TARGET_Y), " ScrollTo API failed.");

  bool bCheckSnapRequired = gScrollView.ScrollToSnapPoint();
  //ScrollToSnapPoint should return true as current position due to scroll is [90, 400]
  //which is set by SCROLL_TARGET_X, SCROLL_TARGET_Y

  DALI_CHECK_FAIL(!bCheckSnapRequired, "ScrollToSnapPoint is failed, it should return true." );
}
void VTScrollViewScrollToSnapPoint002()
{
  //Current position due to scroll is [90, 400], as snap is required for x position
  // Nearest snap for x position SCROLL_TARGET_X(90) is 100, so checking with  SCROLL_TARGET_X + 10.f
  const float NEAREST_SNAP_X = SCROLL_TARGET_X + 10.0f;

  DALI_CHECK_FAIL(gScrollView.GetCurrentScrollPosition() != Vector2(NEAREST_SNAP_X, SCROLL_TARGET_Y), " ScrollToSnapPoint API failed.");

  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionWithAlphaFunctionP()
{
  gScrollDurSet = 1.4f;

  gScrollView = ScrollView::New();

  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );

  gScrollView.ScrollTo( SCROLL_TARGET_1, gScrollDurSet, ScrollViewTestAlphaFunction);
}

// * ############################## Verdict test for ScrollViewScrollToPositionWithAlphaFunction

void VTScrollViewScrollToPositionWithAlphaFunction001()
{
  // As scroll duration is set 0.7s, scroll animation should finish after 0.35s with the above TestAlphaFunction;
  // Tick interval is 0.5s, so checking scroll animation is finished after 0.5s
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_1, " ScrollTo API is failed for Test Alpha function." );

  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, AlphaFunction::LINEAR );
}

void VTScrollViewScrollToPositionWithAlphaFunction002()
{
  // Check that the scroll animation has not finished before the specified duration with the linear alpha function
  // scroll duration is set 0.7s and tick interval is 0.5s; need to check the target value beyond the duration
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() == SCROLL_TARGET_2, " ScrollTo API is failed for AlphaFunction::LINEAR.");

  // Wait till the end of the specified duration
}
void VTScrollViewScrollToPositionWithAlphaFunction003()
{
  // Check that the scroll animation has finished beyond the duration
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "ScrollTo API is failed for AlphaFunction::LINEAR beyond duration");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionWithAlphaFunctionAndDirectionBiasP()
{
  RulerPtr rulerX;
  RulerPtr rulerY;
  float  fMin = 0.0f,fMax = 200.0f,fRulerSize = 100.0f;
  bool bSetRulerScale = false;
  gScrollDurSet = 0.25f;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.SetWrapMode(true);

  gScrollView.ScrollTo( SCROLL_TARGET_1, SCROLL_DURATION);
}

// * ############################## Verdict test for ScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias

void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias001()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_1, "ScrollTo API is failed to get expected position.");
  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, AlphaFunction::LINEAR, Dali::Toolkit::DirectionBiasLeft, Dali::Toolkit::DirectionBiasLeft );
}
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias002()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "ScrollTo API is failed to get expected position for Alpha LINEAR and DirectionBiasLeft.");
  gScrollView.ScrollTo( SCROLL_TARGET_1, SCROLL_DURATION);
}
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias003()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_1, "ScrollTo API is failed to get expected position.");
  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, AlphaFunction::LINEAR, Dali::Toolkit::DirectionBiasRight, Dali::Toolkit::DirectionBiasRight );
}
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias004()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "ScrollTo API is failed to get expected position for Alpha LINEAR and DirectionBiasRight.");
  gScrollView.ScrollTo( SCROLL_TARGET_1, SCROLL_DURATION );
}
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias005()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_1, "ScrollTo API is failed to get expected position." );
  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, ScrollViewTestAlphaFunction, Dali::Toolkit::DirectionBiasRight, Dali::Toolkit::DirectionBiasRight );
}
void VTScrollViewScrollToPositionWithAlphaFunctionAndDirectionBias006()
{
  // Check that the scroll animation with Test alpha function
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "ScrollTo API is failed to get expected position for Test Alpha function and DirectionBiasRight.");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPositionWithDirectionBiasP()
{
  RulerPtr rulerX;
  RulerPtr rulerY;
  float  fMin = 0.0f,fMax = 200.0f,fRulerSize = 100.0f;
  bool bSetRulerScale = false;
  gScrollDurSet = 0.25f;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,fRulerSize,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.SetWrapMode(true);
  gScrollView.ScrollTo( SCROLL_TARGET_1, SCROLL_DURATION );
}

// * ############################## Verdict test for ScrollViewScrollToPositionWithDirectionBias

void VTScrollViewScrollToPositionWithDirectionBias001()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_1, "ScrollTo API is failed to get expected position.");
  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, Dali::Toolkit::DirectionBiasLeft, Dali::Toolkit::DirectionBiasLeft );
}
void VTScrollViewScrollToPositionWithDirectionBias002()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2,"ScrollTo API is failed to get expected position for DirectionBiasLeft.");
  gScrollView.ScrollTo( SCROLL_TARGET_1, SCROLL_DURATION);
}
void VTScrollViewScrollToPositionWithDirectionBias003()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition()!= SCROLL_TARGET_1, "ScrollTo API is failed to get expected position.");
  gScrollView.ScrollTo( SCROLL_TARGET_2, gScrollDurSet, Dali::Toolkit::DirectionBiasRight, Dali::Toolkit::DirectionBiasRight );
}
void VTScrollViewScrollToPositionWithDirectionBias004()
{
  DALI_CHECK_FAIL( gScrollView.GetCurrentScrollPosition() != SCROLL_TARGET_2, "ScrollTo API is failed to get expected position for DirectionBiasRight.");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewScrollToPageWithDirectionBiasP()
{
  RulerPtr rulerX;
  RulerPtr rulerY;
  float  fMin = 0.0f,fMax = 800.0f;
  gScrollDurSet = 0.25f;
  bool bSetRulerScale = false;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage::GetCurrent().Add( gScrollView );
  bSetRulerScale = ScrollViewSetRulerScaleParameters(gScrollView ,rulerX , rulerY,fMin,fMax,SCROLL_VIEW_RULER_SIZE_NEW,true,false);
  DALI_CHECK_FAIL(!bSetRulerScale , " Set Ruler position is failed.");

  gScrollView.SetWrapMode(true);

  gScrollView.ScrollTo( SCROLL_DESTINATION, gScrollDurSet, Dali::Toolkit::DirectionBiasLeft );
}

// * ############################## Verdict test for ScrollViewScrollToPageWithDirectionBias

void VTScrollViewScrollToPageWithDirectionBias001()
{
  Vector2 vec2ExpectedPos = Vector2( SCROLL_DESTINATION*SCROLL_VIEW_RULER_SIZE_NEW, 0.0f );
  Vector2 pos = gScrollView.GetCurrentScrollPosition();

  // ScrollView should remain on zero position and zero page due to left bias
  DALI_CHECK_FAIL( pos  != vec2ExpectedPos,"ScrollTo API is failed for DirectionBiasLeft.");
  DALI_CHECK_FAIL( static_cast<int>(gScrollView.GetCurrentPage()) != SCROLL_DESTINATION, "ScrollTo API is failed to get expected page.");

  gScrollView.ScrollTo( SCROLL_DESTINATION, gScrollDurSet, Dali::Toolkit::DirectionBiasRight );
}

void VTScrollViewScrollToPageWithDirectionBias002()
{
  Vector2 vec2ExpectedPos = Vector2( SCROLL_DESTINATION*SCROLL_VIEW_RULER_SIZE_NEW, 0.0f );
  Vector2 pos = gScrollView.GetCurrentScrollPosition();

  // ScrollView should scroll to right position on expected page due to right bias
  DALI_CHECK_FAIL( pos != vec2ExpectedPos, "ScrollTo API is failed for DirectionBiasRigh as expected position is not retrieved.");
  DALI_CHECK_FAIL( static_cast<int>(gScrollView.GetCurrentPage()) != SCROLL_DESTINATION, "ScrollTo API is failed to get expected page.");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewConstraintsP()
{
  bool bSetBasicRule = false;
  RulerPtr rulerX;
  RulerPtr rulerY;

  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, " stage is not created.");
  stage.Add( gScrollView );

  bSetBasicRule = ScrollViewSetDefaultRuler(stage,gScrollView ,rulerX , rulerY,true);
  DALI_CHECK_FAIL(!bSetBasicRule , " Scrollview object basic setup is failed.");

  // Add an Actor to ScrollView,
  // Apply ScrollviewSumConstraint to ScrollView's children (includes this Actor)
  gVec3ScrollviewConstraintResult = Vector3::ZERO;
  gActorA = Actor::New();
  gScrollView.Add(gActorA);
  gActorA.SetPosition( SCROLL_VIEW_TEST_ACTOR_POSITION );

  Constraint constraint = Constraint::New<Vector3>( gScrollView, Actor::Property::POSITION, ScrollviewSumConstraint( SCROLL_VIEW_TEST_CONSTRAINT_OFFSET ) );
  constraint.AddSource( Source(gScrollView, ScrollView::Property::SCROLL_POSITION) );
  constraint.SetRemoveAction(Constraint::Discard);
  gScrollView.ApplyConstraintToChildren(constraint);
}

// * ############################## Verdict test for ScrollViewConstraints

void VTScrollViewConstraints001()
{
  DALI_CHECK_FAIL( gVec3ScrollviewConstraintResult != (SCROLL_VIEW_TEST_ACTOR_POSITION + SCROLL_VIEW_TEST_CONSTRAINT_OFFSET), "Scrollview ApplyConstraintToChildren is failed");
  DALI_CHECK_FAIL( gActorA.GetCurrentPosition() != gVec3ScrollviewConstraintResult, "Failed to get actor's position applied by constraint." );
  gScrollView.RemoveConstraintsFromChildren();
}

void VTScrollViewConstraints002()
{
  DALI_CHECK_FAIL( gActorA.GetCurrentPosition() != SCROLL_VIEW_TEST_ACTOR_POSITION, "Scrollview RemoveConstraintsFromChildren is failed ");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewApplyAndRemoveAllEffectP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, "ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );
  try
  {
    // Create two scroll view effects
    Dali::Path path = Dali::Path::New();
    ScrollViewEffect effect = ScrollViewPagePathEffect::New(path, Vector3(-1.0f, 0.0f, 0.0f), Toolkit::ScrollView::Property::SCROLL_FINAL_X, Vector3(100.0f, 100.0f, 0.0f), 2);
    ScrollViewEffect newEffect = ScrollViewPagePathEffect::New(path, Vector3(-1.0f, 1.0f, 1.0f), Toolkit::ScrollView::Property::SCROLL_FINAL_X, Vector3(200.0f, 150.0f, 0.0f), 5);

    // Apply both effects
    scrollView.ApplyEffect(effect);
    scrollView.ApplyEffect(newEffect);

    // Remove both effects. If ApplyEffect does not work then RemoveEffect will get exception
    scrollView.RemoveEffect(effect);
    scrollView.RemoveEffect(newEffect);

    // Apply both effects again. Same effect cannot be applied twice.So if it's not removed then it will get exception
    scrollView.ApplyEffect(effect);
    scrollView.ApplyEffect(newEffect);

    // Remove both effects
    scrollView.RemoveAllEffects();

    // Apply both effects again to check RemoveAllEffect's functionality.
    scrollView.ApplyEffect(effect);
    scrollView.ApplyEffect(newEffect);

    scrollView.RemoveEffect(effect);
    scrollView.RemoveAllEffects();
  }
  catch ( DaliException& de )
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception# location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    Stage::GetCurrent().Remove( scrollView );
    test_return_value = TC_FAIL;
    return;
  }
  catch(exception &e)
  {
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Exception: %s, at [LINE: %d]", e.what(), __LINE__);
    Stage::GetCurrent().Remove(scrollView);
    test_return_value = TC_FAIL;
    return;
  }

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewBindUnbindActorP()
{
  gScrollView = ScrollView::New();
  DALI_CHECK_FAIL(!gScrollView, " ScrollView::New() is failed.");

  //Set up a scrollView
  Stage::GetCurrent().Add( gScrollView );
  Vector2 stageSize = Stage::GetCurrent().GetSize();
  gScrollView.SetSize(stageSize);
  gScrollView.SetParentOrigin(ParentOrigin::TOP_LEFT);
  gScrollView.SetAnchorPoint(AnchorPoint::TOP_LEFT);

  // Position rulers.
  RulerPtr rulerX = new DefaultRuler();
  RulerPtr rulerY = new DefaultRuler();
  rulerX->SetDomain( RulerDomain(0.0f, stageSize.width + SCROLL_VIEW_CLAMP_EXCESS_WIDTH, true) );
  rulerY->SetDomain( RulerDomain(0.0f, stageSize.height + SCROLL_VIEW_CLAMP_EXCESS_HEIGHT, true) );
  gScrollView.SetRulerX(rulerX);
  gScrollView.SetRulerY(rulerY);

  gActorBinded = Actor::New();
  DALI_CHECK_FAIL(!gActorBinded, " Actor::New() is failed.");

  // Add an Actor to ScrollView,Apply ScrollviewSumConstraint to ScrollView's children (includes this Actor)
  gVec3ScrollviewConstraintResult = Vector3::ZERO;
  gScrollView.Add(gActorBinded);
  gActorBinded.SetPosition( SCROLL_VIEW_TEST_ACTOR_POSITION );

  // apply this constraint to scrollview
  Constraint constraint = Constraint::New<Vector3>( gScrollView, Actor::Property::POSITION, ScrollviewSumConstraint( SCROLL_VIEW_TEST_CONSTRAINT_OFFSET ) );
  constraint.AddSource( Source(gScrollView, ScrollView::Property::SCROLL_POSITION) );
  constraint.SetRemoveAction(Constraint::Discard);
  gScrollView.ApplyConstraintToChildren(constraint);
}

// * ############################## Verdict test for ScrollViewBindUnbindActor

void VTScrollViewBindUnbindActor001()
{
  // Check Default bind
  DALI_CHECK_FAIL(gVec3ScrollviewConstraintResult != (SCROLL_VIEW_TEST_ACTOR_POSITION + SCROLL_VIEW_TEST_CONSTRAINT_OFFSET), " Scrollview Default Bind is failed");
  // UnBind
  gVec3ScrollviewConstraintResult = Vector3::ZERO;
  gScrollView.UnbindActor(gActorBinded);
}
void VTScrollViewBindUnbindActor002()
{
  DALI_CHECK_FAIL(gVec3ScrollviewConstraintResult != Vector3::ZERO, " Scrollview Unbind is failed");
  // Bind
  gVec3ScrollviewConstraintResult = Vector3::ZERO;
  gScrollView.BindActor(gActorBinded);
}
void VTScrollViewBindUnbindActor003()
{
  DALI_CHECK_FAIL(gVec3ScrollviewConstraintResult != (SCROLL_VIEW_TEST_ACTOR_POSITION + SCROLL_VIEW_TEST_CONSTRAINT_OFFSET), " Scrollview Bind is failed");
  Stage::GetCurrent().Remove( gScrollView );

  DaliLog::PrintPass();
}

void ScrollViewGetOvershootAnimationSpeedP()
{
  const float SETANIMATIONSPEED1 = 55.0f,SETANIMATIONSPEED2 = 120.0f;

  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, "ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  scrollView.SetOvershootAnimationSpeed(SETANIMATIONSPEED1);
  DALI_CHECK_FAIL(scrollView.GetOvershootAnimationSpeed() != SETANIMATIONSPEED1,"GetOvershootAnimationSpeed value is mismatched with set value.");

  scrollView.SetOvershootAnimationSpeed(SETANIMATIONSPEED2);
  DALI_CHECK_FAIL(scrollView.GetOvershootAnimationSpeed() != SETANIMATIONSPEED2,"GetOvershootAnimationSpeed value is mismatched with set value.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}

void ScrollViewGetOvershootEffectColorP()
{
  ScrollView scrollView = ScrollView::New();
  DALI_CHECK_FAIL(!scrollView, "ScrollView::New() is failed.");

  Stage::GetCurrent().Add( scrollView );

  scrollView.SetOvershootEffectColor(Dali::Color::RED);
  DALI_CHECK_FAIL(scrollView.GetOvershootEffectColor() != Dali::Color::RED,"GetOvershootEffectColor is mismatched with set color.");

  scrollView.SetOvershootEffectColor(Dali::Color::YELLOW);
  DALI_CHECK_FAIL(scrollView.GetOvershootEffectColor() != Dali::Color::YELLOW,"GetOvershootEffectColor is mismatched with set color.");

  Stage::GetCurrent().Remove( scrollView );

  DaliLog::PrintPass();
}


/**
 * End of TC Logic Implementation Area.
 **/



/**
 * @testcase            UtcDaliScrollViewConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliScrollViewConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliScrollViewNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliScrollViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliScrollViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliScrollViewDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliScrollViewDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetScrollSnapAlphaFunctionP
 * @since_tizen         2.4
 * @description         Sets and gets the scroll snap alpha function with ease in
 */
int UtcDaliScrollViewSetGetScrollSnapAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_SCROLL_SNAP_ALPHA_FUNCTION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetScrollFlickAlphaFunctionP
 * @since_tizen         2.4
 * @description         Sets and gets the scroll snap alpha function with ease in
 */
int UtcDaliScrollViewSetGetScrollFlickAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_SCROLL_FLICK_ALPHA_FUNCTION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetScrollFlickDurationP
 * @since_tizen         2.4
 * @description         Creates a new Scroll View instance and sets and gets the ScrollFlickDuration
 */

int UtcDaliScrollViewSetGetScrollFlickDurationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_SCROLL_FLICK_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetScrollSnapDurationP
 * @since_tizen         2.4
 * @description         creates a new Scroll View instance and sets and gets the ScrollSnapDuration
 */

int UtcDaliScrollViewSetGetScrollSnapDurationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_SCROLL_SNAP_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetRulerP
 * @since_tizen         2.4
 * @description         Sets the ruler
 */

int UtcDaliScrollViewSetRulerP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_RULER_P );
  application.MainLoop();

  return test_return_value;
}

//& purpose:
/**
 * @testcase            UtcDaliScrollViewSetScrollSensitiveP
 * @since_tizen         2.4
 * @description         Checks if the scroll view APIs is getting the correct signal or not
 */

int UtcDaliScrollViewSetScrollSensitiveP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_SCROLL_SENSITIVE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetWrapModeP
 * @since_tizen         2.4
 * @description         Sets the scrol view wrap mode
 */
int UtcDaliScrollViewSetWrapModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_WRAP_MODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetActorAutoSnapP
 * @since_tizen         2.4
 * @description         Sets the actor auto snap mode and verifies the phenomenon
 */
int UtcDaliScrollViewSetActorAutoSnapP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_ACTOR_AUTO_SNAP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetAxisAutoLockP
 * @since_tizen         2.4
 * @description         Enables or Disables Axis Auto Lock mode for panning within the ScrollView and checks if the set value is true
 */

int UtcDaliScrollViewSetGetAxisAutoLockP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetAxisAutoLockGradientP
 * @since_tizen         2.4
 * @description         Creates a new Scroll View instance and sets X auto lock gradient
 */

int UtcDaliScrollViewSetGetAxisAutoLockGradientP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_AXIS_AUTO_LOCK_GRADIENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetSetScrollUpdateDistanceP
 * @since_tizen         2.4
 * @description         Sets the distance needed to scroll for ScrollUpdatedSignal to be emitted
 */
int UtcDaliScrollViewGetSetScrollUpdateDistanceP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_SET_SCROLL_UPDATE_DISTANCE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetFrictionCoefficientP
 * @since_tizen         2.4
 * @description         Sets the friction coefficient for ScrollView when flicking in free panning mode
 */

int UtcDaliScrollViewSetGetFrictionCoefficientP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_FRICTION_COEFFICIENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetFlickSpeedCoefficientP
 * @since_tizen         2.4
 * @description         creates a new Scroll View instance and sets and gets the FlickSpeedCoefficient
 */

int UtcDaliScrollViewSetGetFlickSpeedCoefficientP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_FLICK_SPEED_COEFFICIENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetSetMinimumDistanceForFlickP
 * @since_tizen         2.4
 * @description         Sets the minimum pan distance required for a flick in pixels.
 */

int UtcDaliScrollViewGetSetMinimumDistanceForFlickP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_SET_MINIMUM_DISTANCE_FOR_FLICK_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetSetMinimumSpeedForFlickP
 * @since_tizen         2.4
 * @description         Sets the minimum pan speed required for a flick in pixels per second.
 */

int UtcDaliScrollViewGetSetMinimumSpeedForFlickP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_SET_MINIMUM_SPEED_FOR_FLICK_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetMaxFlickSpeedP
 * @since_tizen         2.4
 * @description         Sets and gets the maximum flick speed setting for ScrollView when flicking in free panning mode
 */

int UtcDaliScrollViewSetGetMaxFlickSpeedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_MAX_FLICK_SPEED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewSetGetWheelScrollDistanceStepP
 * @since_tizen         2.4
 * @description         Sets and gets the scroll distance step
 */

int UtcDaliScrollViewSetGetWheelScrollDistanceStepP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SET_GET_WHEEL_SCROLL_DISTANCE_STEP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetCurrentPageP
 * @since_tizen         2.4
 * @description         Gets the current page.
 */

int UtcDaliScrollViewGetCurrentPageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_CURRENT_PAGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetCurrentScrollPositionP
 * @since_tizen         2.4
 * @description         Gets the current scroll position
 */

int UtcDaliScrollViewGetCurrentScrollPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_CURRENT_SCROLL_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionDurationP
 * @since_tizen         2.4
 * @description         Sets the scrol view postion and specified scale
 */

int UtcDaliScrollViewScrollToPositionDurationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionP
 * @since_tizen         2.4
 * @description         Sets and gets the scroll position
 */
int UtcDaliScrollViewScrollToPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionToPageDurationP
 * @since_tizen         2.4
 * @description         Sets the scrol view postion and specified duration and page
 */
int UtcDaliScrollViewScrollToPositionToPageDurationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_TO_PAGE_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPageP
 * @since_tizen         2.4
 * @description         Sets the scrol view postion and specified duration and page
 */
int UtcDaliScrollViewScrollToPageP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_PAGE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToActorDurationP
 * @since_tizen         2.4
 * @description         Sets the scroll view postion to a specified actor with duration
 */
int UtcDaliScrollViewScrollToActorDurationP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_ACTOR_DURATION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToSpecifiedActorP
 * @since_tizen         2.4
 * @description         Sets the scroll view postion to a specified actor
 */
int UtcDaliScrollViewScrollToSpecifiedActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_SPECIFIED_ACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToSnapPointP
 * @since_tizen         2.4
 * @description         Sets the scroll view postion to a definite snap point
 */
int UtcDaliScrollViewScrollToSnapPointP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_SNAP_POINT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionWithAlphaFunctionP
 * @since_tizen         2.4
 * @description         Scrolls View to position specified. Contents will scroll to this position.
 */

int UtcDaliScrollViewScrollToPositionWithAlphaFunctionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionWithAlphaFunctionAndDirectionBiasP
 * @since_tizen         2.4
 * @description         Scrolls View to position specified.
 */

int UtcDaliScrollViewScrollToPositionWithAlphaFunctionAndDirectionBiasP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_WITH_ALPHA_FUNCTION_AND_DIRECTION_BIAS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPositionWithDirectionBiasP
 * @since_tizen         2.4
 * @description         Scrolls View to position specified.
 */

int UtcDaliScrollViewScrollToPositionWithDirectionBiasP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_POSITION_WITH_DIRECTION_BIAS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewScrollToPageWithDirectionBiasP
 * @since_tizen         2.4
 * @description         Scrolls View to position specified.
 */

int UtcDaliScrollViewScrollToPageWithDirectionBiasP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_SCROLL_TO_PAGE_WITH_DIRECTION_BIAS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewConstraintsP
 * @since_tizen         2.4
 * @description         Applies and Remove a constrains that will affect the children.
 */
int UtcDaliScrollViewConstraintsP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_CONSTRAINTS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewApplyAndRemoveAllEffectP
 * @since_tizen         2.4
 * @description         Check ApplyEffect and RemoveEffect functionality.
 */
int UtcDaliScrollViewApplyAndRemoveAllEffectP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_APPLY_AND_REMOVE_ALL_EFFECT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewBindUnbindActorP
 * @since_tizen         2.4
 * @description         bind and unbinds the scroll view instances
 */
int UtcDaliScrollViewBindUnbindActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_BIND_UNBIND_ACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetOvershootAnimationSpeedP
 * @since_tizen         2.4
 * @description         Check the speed of overshoot animation in pixels per second.
 */
int UtcDaliScrollViewGetOvershootAnimationSpeedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_OVER_SHOOT_ANIMATION_SPEED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliScrollViewGetOvershootEffectColorP
 * @since_tizen         2.4
 * @description         Check the color of the overshoot effect.
 */
int UtcDaliScrollViewGetOvershootEffectColorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ScrollView_TestApp testApp( application, SCROLL_VIEW_GET_OVERSHOOT_EFFECT_COLOR_P );
  application.MainLoop();

  return test_return_value;
}

