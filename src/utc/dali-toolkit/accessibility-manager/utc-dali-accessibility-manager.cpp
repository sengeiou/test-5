#include "utc-dali-accessibility-manager-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_AccessibilityManager_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AccessibilityManager_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_AccessibilityManager_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_AccessibilityManager_cleanup(void)
{

}

class FocusChangedCallback : public Dali::ConnectionTracker
{
  public:
    FocusChangedCallback(bool& signalReceived)
      : m_bSignalVerified(signalReceived),
      m_OriginalFocusedActor(),
      m_CurrentFocusedActor()
  {
  }

    void Callback(Actor originalFocusedActor, Actor currentFocusedActor)
    {
      if(originalFocusedActor == m_CurrentFocusedActor)
      {
        m_bSignalVerified = true;
      }

      m_OriginalFocusedActor = originalFocusedActor;
      m_CurrentFocusedActor = currentFocusedActor;
    }

    void Reset()
    {
      m_bSignalVerified = false;
    }

    bool& m_bSignalVerified;
    Actor m_OriginalFocusedActor;
    Actor m_CurrentFocusedActor;
};

/**To test whether focus overshot signal is emitted when there is no way to move focus further**/
class FocusOvershotCallback : public Dali::ConnectionTracker
{
  public:
    FocusOvershotCallback(bool& signalReceived)
      : m_bSignalVerified(signalReceived),
      m_CurrentFocusedActor(),
      m_FocusOvershotDirection(Toolkit::AccessibilityManager::OVERSHOT_NEXT)
  {
  }

    void Callback(Actor currentFocusedActor, Toolkit::AccessibilityManager::FocusOvershotDirection direction)
    {
      if(currentFocusedActor == m_CurrentFocusedActor && direction == m_FocusOvershotDirection)
      {
        m_bSignalVerified = true;
      }
    }

    void Reset()
    {
      m_bSignalVerified = false;
    }

    bool& m_bSignalVerified;
    Actor m_CurrentFocusedActor;
    Toolkit::AccessibilityManager::FocusOvershotDirection m_FocusOvershotDirection;
};

// Functor to test whether focused actor activated signal is emitted.
class FocusedActorActivatedCallback : public Dali::ConnectionTracker
{
  public:
    FocusedActorActivatedCallback()
    {
    }

    void Callback(Actor activatedActor)
    {

    }
};


class AccessibilityManagerSignalHandler : public Dali::ConnectionTracker
{
  public:
    AccessibilityManagerSignalHandler() :
      mCalls( 0 )
    {
    }

    bool Callback( AccessibilityManager& accessibilityManager )
    {
      mCalls++;

      return true;
    }

    unsigned int GetCalls() const
    {
      return mCalls;
    }

  private:
    unsigned int mCalls;
};

class AccessibilityManagerScrollSignalHandler : public Dali::ConnectionTracker
{
  public:
    AccessibilityManagerScrollSignalHandler() :
      mCalls( 0 )
  {
  }

    bool Callback( AccessibilityManager& accessibilityManager, const Dali::TouchEvent& touchEvent )
    {
      mCalls++;
      mTouchEvent = touchEvent;
      return true;
    }

    unsigned int GetCalls() const
    {
      return mCalls;
    }

    const Dali::TouchEvent& GetTouchEvent() const
    {
      return mTouchEvent;
    }

  private:
    unsigned int mCalls;         ///< Keeps track of how many times the signal has been called.
    Dali::TouchEvent mTouchEvent; ///< Stores the last touch event received.
};

void AccessibilityManagerConstructorP();
void AccessibilityManagerGetP();
void AccessibilityManagerSetGetAccessibilityAttributeP();
void AccessibilityManagerSetGetFocusOrderP();
void AccessibilityManagerGenerateNewFocusOrderP();
void AccessibilityManagerGetActorByFocusOrderP();
void AccessibilityManagerSetGetCurrentFocusActorP();
void AccessibilityManagerGetCurrentFocusGroupP();
void AccessibilityManagerGetCurrentFocusOrderP();
void AccessibilityManagerMoveFocusForwardP();
void AccessibilityManagerMoveFocusBackwardP();
void AccessibilityManagerClearFocusP();
void AccessibilityManagerResetP();
void AccessibilityManagerSetIsFocusGroupP();
void AccessibilityManagerSetGetGroupModeP();
void AccessibilityManagerSetGetWrapModeP();
void AccessibilityManagerSetGetFocusIndicatorActorP();
void AccessibilityManagerSetGetFocusGroupP();
void AccessibilityManagerGetReadPositionP();
void AccessibilityManagerFocusChangedSignalP();
void AccessibilityManagerFocusOvershotSignalP();
void AccessibilityManagerStatusChangedSignalN();
void AccessibilityManagerActionNextSignalN();
void AccessibilityManagerActionPreviousSignalN();
void AccessibilityManagerActionActivateSignalN();
void AccessibilityManagerActionReadSignalN();
void AccessibilityManagerActionOverSignalN();
void AccessibilityManagerActionReadNextSignalN();
void AccessibilityManagerActionReadPreviousSignalN();
void AccessibilityManagerActionUpSignalN();
void AccessibilityManagerActionDownSignalN();
void AccessibilityManagerActionClearFocusSignalN();
void AccessibilityManagerActionBackSignalN();
void AccessibilityManagerActionScrollUpSignalN();
void AccessibilityManagerActionScrollDownSignalN();
void AccessibilityManagerActionPageLeftSignalN();
void AccessibilityManagerActionPageRightSignalN();
void AccessibilityManagerActionPageUpSignalN();
void AccessibilityManagerActionPageDownSignalN();
void AccessibilityManagerActionMoveToFirstSignalN();
void AccessibilityManagerActionMoveToLastSignalN();
void AccessibilityManagerActionReadFromTopSignalN();
void AccessibilityManagerActionReadFromNextSignalN();
void AccessibilityManagerActionZoomSignalN();
void AccessibilityManagerActionReadIndicatorInformationSignalN();
void AccessibilityManagerActionReadPauseResumeSignalN();
void AccessibilityManagerActionStartStopSignalN();
void AccessibilityManagerActionScrollSignalN();
void AccessibilityManagerFocusedActorActivatedSignalN();

namespace
{
  enum TEST_CASES_LIST_ACCESSIBILITY_MANAGER
  {
    ACCESSIBILITY_MANAGER_CONSTRUCTOR_P,
    ACCESSIBILITY_MANAGER_GET_P,
    ACCESSIBILITY_MANAGER_SET_GET_ACCESSIBILITY_ATTRIBUTE_P,
    ACCESSIBILITY_MANAGER_SET_GET_FOCUS_ORDER_P,
    ACCESSIBILITY_MANAGER_GENERATE_NEW_FOCUS_ORDER_P,
    ACCESSIBILITY_MANAGER_GET_ACTOR_BY_FOCUS_ORDER_P,
    ACCESSIBILITY_MANAGER_SET_GET_CURRENT_FOCUS_ACTOR_P,
    ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_GROUP_P,
    ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_ORDER_P,
    ACCESSIBILITY_MANAGER_MOVE_FOCUS_FORWARD_P,
    ACCESSIBILITY_MANAGER_MOVE_FOCUS_BACKWARD_P,
    ACCESSIBILITY_MANAGER_CLEAR_FOCUS_P,
    ACCESSIBILITY_MANAGER_RESET_P,
    ACCESSIBILITY_MANAGER_SET_GET_GROUP_MODE_P,
    ACCESSIBILITY_MANAGER_SET_GET_WRAP_MODE_P,
    ACCESSIBILITY_MANAGER_SET_GET_FOCUS_INDICATOR_ACTOR_P,
    ACCESSIBILITY_MANAGER_SET_GET_FOCUS_GROUP_P,
    ACCESSIBILITY_MANAGER_SET_IS_FOCUS_GROUP_P,
    ACCESSIBILITY_MANAGER_GET_READ_POSITION_P,
    ACCESSIBILITY_MANAGER_FOCUS_CHANGED_SIGNAL_P,
    ACCESSIBILITY_MANAGER_FOCUS_OVERSHOT_SIGNAL_P,
    ACCESSIBILITY_MANAGER_STATUS_CHANGED_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_NEXT_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_PREVIOUS_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_ACTIVATE_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_OVER_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_NEXT_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_PREVIOUS_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_UP_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_DOWN_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_CLEAR_FOCUS_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_BACK_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_SCROLL_UP_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_SCROLL_DOWN_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_PAGE_LEFT_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_PAGE_RIGHT_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_PAGE_UP_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_PAGE_DOWN_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_FIRST_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_LAST_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_FROM_TOP_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_FROM_NEXT_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_ZOOM_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_INDICATOR_INFORMATION_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_READ_PAUSE_RESUME_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_START_STOP_SIGNAL_N,
    ACCESSIBILITY_MANAGER_ACTION_SCROLL_SIGNAL_N,
    ACCESSIBILITY_MANAGER_FOCUSED_ACTOR_ACTIVATED_SIGNAL_N
  };

  struct AccessibilityManager_TestApp : public ConnectionTracker
  {
    AccessibilityManager_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &AccessibilityManager_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &AccessibilityManager_TestApp::Tick );
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
        case ACCESSIBILITY_MANAGER_CONSTRUCTOR_P:
          AccessibilityManagerConstructorP();
          break;
        case ACCESSIBILITY_MANAGER_GET_P:
          AccessibilityManagerGetP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_ACCESSIBILITY_ATTRIBUTE_P:
          AccessibilityManagerSetGetAccessibilityAttributeP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_FOCUS_ORDER_P:
          AccessibilityManagerSetGetFocusOrderP();
          break;
        case ACCESSIBILITY_MANAGER_GENERATE_NEW_FOCUS_ORDER_P:
          AccessibilityManagerGenerateNewFocusOrderP();
          break;
        case ACCESSIBILITY_MANAGER_GET_ACTOR_BY_FOCUS_ORDER_P:
          AccessibilityManagerGetActorByFocusOrderP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_CURRENT_FOCUS_ACTOR_P:
          AccessibilityManagerSetGetCurrentFocusActorP();
          break;
        case ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_GROUP_P:
          AccessibilityManagerGetCurrentFocusGroupP();
          break;
        case ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_ORDER_P:
          AccessibilityManagerGetCurrentFocusOrderP();
          break;
        case ACCESSIBILITY_MANAGER_MOVE_FOCUS_FORWARD_P:
          AccessibilityManagerMoveFocusForwardP();
          break;
        case ACCESSIBILITY_MANAGER_MOVE_FOCUS_BACKWARD_P:
          AccessibilityManagerMoveFocusBackwardP();
          break;
        case ACCESSIBILITY_MANAGER_CLEAR_FOCUS_P:
          AccessibilityManagerClearFocusP();
          break;
        case ACCESSIBILITY_MANAGER_RESET_P:
          AccessibilityManagerResetP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_GROUP_MODE_P:
          AccessibilityManagerSetGetGroupModeP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_WRAP_MODE_P:
          AccessibilityManagerSetGetWrapModeP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_FOCUS_INDICATOR_ACTOR_P:
          AccessibilityManagerSetGetFocusIndicatorActorP();
          break;
        case ACCESSIBILITY_MANAGER_SET_GET_FOCUS_GROUP_P:
          AccessibilityManagerSetGetFocusGroupP();
          break;
        case ACCESSIBILITY_MANAGER_GET_READ_POSITION_P:
          AccessibilityManagerGetReadPositionP();
          break;
        case ACCESSIBILITY_MANAGER_SET_IS_FOCUS_GROUP_P:
          AccessibilityManagerSetIsFocusGroupP();
          break;
        case ACCESSIBILITY_MANAGER_FOCUS_CHANGED_SIGNAL_P:
          AccessibilityManagerFocusChangedSignalP();
          break;
        case ACCESSIBILITY_MANAGER_FOCUS_OVERSHOT_SIGNAL_P:
          AccessibilityManagerFocusOvershotSignalP();
          break;
        case ACCESSIBILITY_MANAGER_STATUS_CHANGED_SIGNAL_N:
          AccessibilityManagerStatusChangedSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_NEXT_SIGNAL_N:
          AccessibilityManagerActionNextSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_PREVIOUS_SIGNAL_N:
          AccessibilityManagerActionPreviousSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_ACTIVATE_SIGNAL_N:
          AccessibilityManagerActionActivateSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_SIGNAL_N:
          AccessibilityManagerActionReadSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_OVER_SIGNAL_N:
          AccessibilityManagerActionOverSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_NEXT_SIGNAL_N:
          AccessibilityManagerActionReadNextSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_PREVIOUS_SIGNAL_N:
          AccessibilityManagerActionReadPreviousSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_UP_SIGNAL_N:
          AccessibilityManagerActionUpSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_DOWN_SIGNAL_N:
          AccessibilityManagerActionDownSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_CLEAR_FOCUS_SIGNAL_N:
          AccessibilityManagerActionClearFocusSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_BACK_SIGNAL_N:
          AccessibilityManagerActionBackSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_SCROLL_UP_SIGNAL_N:
          AccessibilityManagerActionScrollUpSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_SCROLL_DOWN_SIGNAL_N:
          AccessibilityManagerActionScrollDownSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_PAGE_LEFT_SIGNAL_N:
          AccessibilityManagerActionPageLeftSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_PAGE_RIGHT_SIGNAL_N:
          AccessibilityManagerActionPageRightSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_PAGE_UP_SIGNAL_N:
          AccessibilityManagerActionPageUpSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_PAGE_DOWN_SIGNAL_N:
          AccessibilityManagerActionPageDownSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_FIRST_SIGNAL_N:
          AccessibilityManagerActionMoveToFirstSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_LAST_SIGNAL_N:
          AccessibilityManagerActionMoveToLastSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_FROM_TOP_SIGNAL_N:
          AccessibilityManagerActionReadFromTopSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_FROM_NEXT_SIGNAL_N:
          AccessibilityManagerActionReadFromNextSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_ZOOM_SIGNAL_N:
          AccessibilityManagerActionZoomSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_INDICATOR_INFORMATION_SIGNAL_N:
          AccessibilityManagerActionReadIndicatorInformationSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_READ_PAUSE_RESUME_SIGNAL_N:
          AccessibilityManagerActionReadPauseResumeSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_START_STOP_SIGNAL_N:
          AccessibilityManagerActionStartStopSignalN();
          break;
        case ACCESSIBILITY_MANAGER_ACTION_SCROLL_SIGNAL_N:
          AccessibilityManagerActionScrollSignalN();
          break;
        case ACCESSIBILITY_MANAGER_FOCUSED_ACTOR_ACTIVATED_SIGNAL_N:
          AccessibilityManagerFocusedActorActivatedSignalN();
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


void AccessibilityManagerConstructorP()
{
  AccessibilityManager accessibilityManager;
  DALI_CHECK_FAIL(accessibilityManager, "AccessibilityManager default constructor is failed.");

  DaliLog::PrintPass();
}

void AccessibilityManagerGetP()
{
  AccessibilityManager accessibilityManager1 = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager1, "AccessibilityManager::Get() is failed." );

  AccessibilityManager accessibilityManager2 = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager2, "AccessibilityManager::Get() is failed." );

  DALI_CHECK_FAIL( accessibilityManager1 != accessibilityManager2, "ingleton of AccessibilityManager object is not matched." );

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetAccessibilityAttributeP()
{
  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actor = Actor::New();

  DALI_CHECK_FAIL( !AccessibilityManagerAccessibilityAttribute( accessibilityManager, actor, AccessibilityManager::ACCESSIBILITY_LABEL), "Failed to set/get accessibility attribute with accessibility label." );

  DALI_CHECK_FAIL( !AccessibilityManagerAccessibilityAttribute( accessibilityManager, actor, AccessibilityManager::ACCESSIBILITY_TRAIT), "Failed to Set/Get accessibility attribute with accessibility trait." );

  DALI_CHECK_FAIL( !AccessibilityManagerAccessibilityAttribute( accessibilityManager, actor, AccessibilityManager::ACCESSIBILITY_VALUE), "Failed to Set/Get accessibility attribute with accessibility value." );

  DALI_CHECK_FAIL( !AccessibilityManagerAccessibilityAttribute( accessibilityManager, actor, AccessibilityManager::ACCESSIBILITY_HINT), "Failed to Set/Get accessibility attribute with accessibility hint." );

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetFocusOrderP()
{
  const int SET_FOCUS_ORDER = 1;
  int nGetFocusOrder = 0;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );
  Actor actor = Actor::New();

  accessibilityManager.SetFocusOrder(actor, SET_FOCUS_ORDER );
  nGetFocusOrder = accessibilityManager.GetFocusOrder(actor);

  DALI_CHECK_FAIL( SET_FOCUS_ORDER != nGetFocusOrder, "Set and Get focused order is mismatched." );

  DaliLog::PrintPass();
}

void AccessibilityManagerGenerateNewFocusOrderP()
{
  const int SET_FOCUS_ORDER = 1;
  int nGetFocusOrder = 0;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actor = Actor::New();

  accessibilityManager.SetFocusOrder(actor, SET_FOCUS_ORDER );
  nGetFocusOrder = accessibilityManager.GenerateNewFocusOrder();

  DALI_CHECK_FAIL( ( SET_FOCUS_ORDER + 1 ) != nGetFocusOrder, "Set and Generated new focused order is not correct." );

  DaliLog::PrintPass();
}

void AccessibilityManagerGetActorByFocusOrderP()
{
  const int SET_FOCUS_ORDER = 1;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );
  Actor actor = Actor::New();

  Actor orderedActor = Actor::New();
  DALI_CHECK_FAIL(!orderedActor, "Actor::New() is failed." );

  accessibilityManager.SetFocusOrder(actor, SET_FOCUS_ORDER);

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "Stage is not created." );
  stage.Add(actor);
  orderedActor = accessibilityManager.GetActorByFocusOrder(SET_FOCUS_ORDER) ;

  DALI_CHECK_FAIL( actor != orderedActor, "Set and Get current focus order is mismatched." );
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetCurrentFocusActorP()
{
  Actor actorLocation;
  const int SET_FOCUS_ORDER = 1 ;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorFirst = Actor::New();
  DALI_CHECK_FAIL( !actorFirst, "Actor::New() is failed." );

  accessibilityManager.SetFocusOrder(actorFirst, SET_FOCUS_ORDER);
  DALI_CHECK_FAIL(SET_FOCUS_ORDER != accessibilityManager.GetFocusOrder(actorFirst), "Set Focus Actor is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "stage is not created." );

  stage.Add(actorFirst);
  accessibilityManager.SetCurrentFocusActor(actorFirst);
  actorLocation = accessibilityManager.GetCurrentFocusActor() ;

  DALI_CHECK_FAIL( actorLocation != actorFirst, "Set Current Focus Actor and Get Current Focus Actor is mismatched." );
  stage.Remove(actorFirst);

  DaliLog::PrintPass();
}

void AccessibilityManagerGetCurrentFocusGroupP()
{
  const bool ENABLE_FOCUS_GROUP = true;
  bool bIsFocusGroup = false;
  const int SET_FOCUS_ORDER = 1;
  Actor actorGroup;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorParent = Actor::New();
  DALI_CHECK_FAIL( !actorParent, "Actor::New() is failed." );
  Actor actorChild = Actor::New();
  DALI_CHECK_FAIL( !actorChild, "Actor::New() is failed." );
  actorParent.Add(actorChild);

  DALI_CHECK_FAIL( !AccessibilityManagerHasAncestor(actorChild, actorParent), "Actor::Add() is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is not created." );
  stage.Add(actorParent);

  accessibilityManager.SetFocusOrder(actorParent, SET_FOCUS_ORDER);
  accessibilityManager.SetFocusOrder(actorChild, SET_FOCUS_ORDER+1 );
  accessibilityManager.SetFocusGroup(actorParent, ENABLE_FOCUS_GROUP);

  bIsFocusGroup = accessibilityManager.IsFocusGroup(actorParent);

  DALI_CHECK_FAIL( ENABLE_FOCUS_GROUP != bIsFocusGroup, "Failed to Set Focus Group." );

  accessibilityManager.SetCurrentFocusActor(actorChild);
  actorGroup = accessibilityManager.GetCurrentFocusGroup();

  DALI_CHECK_FAIL( actorGroup != actorParent, "Can not get the focus group of current focused actor." );

  stage.Remove(actorParent);
  actorParent.Remove(actorChild);

  DaliLog::PrintPass();
}

void AccessibilityManagerGetCurrentFocusOrderP()
{
  const int SET_FOCUS_ORDER = 1;
  int nCurrentOrder = 0;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, "Actor::New() is failed." );

  accessibilityManager.SetFocusOrder(actor, SET_FOCUS_ORDER );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "stage is not created." );
  stage.Add(actor);
  accessibilityManager.SetCurrentFocusActor(actor);    nCurrentOrder = accessibilityManager.GetCurrentFocusOrder();
  DALI_CHECK_FAIL( SET_FOCUS_ORDER != nCurrentOrder, "Set actor order and Get current Focus order is mismatched." );
  stage.Remove(actor);

  DaliLog::PrintPass();
}

void AccessibilityManagerMoveFocusForwardP()
{
  const int SET_FOCUS_ORDER = 1;
  Actor actorFocus;
  Stage stage;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorSecond = Actor::New();
  DALI_CHECK_FAIL( !actorSecond, "Actor::New() is failed." );
  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "Stage is not created." );
  stage.Add(actorSecond);

  Actor actorFirst = Actor::New();
  DALI_CHECK_FAIL( !actorFirst, "Actor::New() is failed." );

  stage = Stage::GetCurrent();
  stage.Add(actorFirst);
  accessibilityManager.SetFocusOrder(actorFirst, SET_FOCUS_ORDER);
  accessibilityManager.SetFocusOrder(actorSecond, SET_FOCUS_ORDER+1);
  accessibilityManager.SetCurrentFocusActor(actorFirst);
  actorFocus = accessibilityManager.GetCurrentFocusActor();
  DALI_CHECK_FAIL( actorFocus != actorFirst, "set/get current focus actor failed." );

  accessibilityManager.MoveFocusForward();  // target APi
  actorFocus = accessibilityManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actorFocus != actorSecond, "Move the focus to the next focusable actor is failed." );

  stage.Remove(actorFirst);
  stage.Remove(actorSecond);

  DaliLog::PrintPass();
}

void AccessibilityManagerMoveFocusBackwardP()
{
  const int SET_FOCUS_ORDER = 1;
  Actor actorFocus;
  Stage stage;
  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorSecond = Actor::New();
  DALI_CHECK_FAIL( !actorSecond, "Actor::New() is failed." );

  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is not created." );
  stage.Add(actorSecond);
  Actor actorFirst = Actor::New();
  DALI_CHECK_FAIL( !actorFirst, "Actor::New() is failed." );
  stage = Stage::GetCurrent();
  stage.Add(actorFirst);

  accessibilityManager.SetFocusOrder(actorFirst, SET_FOCUS_ORDER );
  accessibilityManager.SetFocusOrder(actorSecond, SET_FOCUS_ORDER + 1 );
  accessibilityManager.SetCurrentFocusActor(actorSecond);

  actorFocus = accessibilityManager.GetCurrentFocusActor();
  DALI_CHECK_FAIL( actorFocus != actorSecond, "seta and get current focus actor failed." );

  accessibilityManager.MoveFocusBackward();//target Api
  actorFocus = accessibilityManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actorFocus != actorFirst, "Move the focus to the previous focusable actor is failed." );
  stage.Remove(actorSecond);
  stage.Remove(actorFirst);

  DaliLog::PrintPass();
}

void AccessibilityManagerClearFocusP()
{
  const int SET_FOCUS_ORDER = 1;
  Actor actorFocus;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorParent = Actor::New();
  Actor firstChild = Actor::New();
  actorParent.Add(firstChild);
  DALI_CHECK_FAIL( !AccessibilityManagerHasAncestor(firstChild , actorParent), "Actor::Add() is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "Stage is not created." );
  stage.Add(actorParent);
  accessibilityManager.SetFocusOrder(firstChild, SET_FOCUS_ORDER);
  accessibilityManager.SetCurrentFocusActor(firstChild);
  actorFocus = accessibilityManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actorFocus != firstChild, "set/get current focus actor failed." );

  accessibilityManager.ClearFocus();
  actorFocus = accessibilityManager.GetCurrentFocusActor();
  DALI_CHECK_FAIL( actorFocus, "Clearing the focus from the current focused actor is failed." );
  stage.Remove(actorParent);
  actorParent.Remove(firstChild);

  DaliLog::PrintPass();
}

void AccessibilityManagerResetP()
{
  Actor actorFocus;
  int nOrder = -1;
  const int SET_FOCUS_ORDER = 1, FOCUS_CLEARED_INDEX = 0;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorParent = Actor::New();
  Actor firstChild = Actor::New();
  actorParent.Add(firstChild);

  DALI_CHECK_FAIL(!AccessibilityManagerHasAncestor(firstChild, actorParent), "Actor::New() is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage,  "stage is not created." );

  stage.Add(actorParent);
  accessibilityManager.SetFocusOrder(firstChild , SET_FOCUS_ORDER);
  accessibilityManager.SetCurrentFocusActor(firstChild);
  actorFocus = accessibilityManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actorFocus != firstChild, "set/get current focus actor is failed." );

  accessibilityManager.Reset(); // target APi
  actorFocus = accessibilityManager.GetCurrentFocusActor();
  nOrder = accessibilityManager.GetFocusOrder(firstChild) ;
  DALI_CHECK_FAIL( actorFocus, "Reset the focus from the current focused actor is failed." );
  DALI_CHECK_FAIL( nOrder != FOCUS_CLEARED_INDEX, "Focus order of actors have not been cleared." );
  stage.Remove(actorParent);
  actorParent.Remove(firstChild);

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetGroupModeP()
{
  const bool ENABLE_FOCUS_GROUP_MODE = true ;
  bool bGetGroupMode = false ;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  accessibilityManager.SetGroupMode(ENABLE_FOCUS_GROUP_MODE);
  bGetGroupMode = accessibilityManager.GetGroupMode();

  DALI_CHECK_FAIL( ENABLE_FOCUS_GROUP_MODE != bGetGroupMode, "Set and Get group mode is mismatched." );
  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetWrapModeP()
{
  const bool ENABLE_WRAP_MODE = true ;
  bool bGetWrapMode = false ;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  accessibilityManager.SetWrapMode(ENABLE_WRAP_MODE);
  bGetWrapMode = accessibilityManager.GetWrapMode();

  DALI_CHECK_FAIL(ENABLE_WRAP_MODE != bGetWrapMode, "Set and Get Wrap mode is mismatched." );

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetFocusIndicatorActorP()
{
  Actor getFocusIndicatorActor;
  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor setFocusIndicatorActor = Actor::New();
  DALI_CHECK_FAIL( !setFocusIndicatorActor, "Actor::New() is failed." );

  accessibilityManager.SetFocusIndicatorActor(setFocusIndicatorActor);
  getFocusIndicatorActor = accessibilityManager.GetFocusIndicatorActor();

  DALI_CHECK_FAIL( setFocusIndicatorActor != getFocusIndicatorActor, "Set and Get Focus indicator actor is mismatched." );

  DaliLog::PrintPass();
}

void AccessibilityManagerSetGetFocusGroupP()
{
  const bool ENABLE_FOCUS_GROUP = true;
  Actor checkChild;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL(!accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorParent = Actor::New();
  Actor actorChild = Actor::New();

  actorParent.Add(actorChild);
  DALI_CHECK_FAIL(!AccessibilityManagerHasAncestor(actorChild, actorParent), "Actor::Add() is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is not created." );

  stage.Add(actorParent);
  accessibilityManager.SetFocusGroup(actorParent, ENABLE_FOCUS_GROUP);
  checkChild = accessibilityManager.GetFocusGroup(actorChild);

  DALI_CHECK_FAIL(checkChild != actorParent, "Set and Get focused group is mismatched." );

  stage.Remove(actorParent);
  actorParent.Remove(actorChild);

  DaliLog::PrintPass();
}

void AccessibilityManagerGetReadPositionP()
{
  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Vector2 readPosition( accessibilityManager.GetReadPosition() );
  DALI_CHECK_FAIL( readPosition.x !=0.0f, "Read Position failed" );
  DALI_CHECK_FAIL( readPosition.y !=0.0f, "Read Position failed" );

  DaliLog::PrintPass();
}

void AccessibilityManagerSetIsFocusGroupP()
{
  const bool ENABLE_FOCUS_GROUP = true ;
  bool bIsFocusGroup = false ;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorParent = Actor::New();
  DALI_CHECK_FAIL( !actorParent, "Actor::New() is failed." );
  Actor actorChild = Actor::New();
  DALI_CHECK_FAIL( !actorChild, "Actor::New() is failed." );

  actorParent.Add(actorChild);
  DALI_CHECK_FAIL( !AccessibilityManagerHasAncestor(actorChild, actorParent), "Actor::Add is failed." );

  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "stage is not created." );
  stage.Add(actorParent);

  accessibilityManager.SetFocusGroup(actorParent, ENABLE_FOCUS_GROUP);
  bIsFocusGroup = accessibilityManager.IsFocusGroup(actorParent);

  DALI_CHECK_FAIL( ENABLE_FOCUS_GROUP != bIsFocusGroup, "Set and Get FocusGroup value is mismatched." );
  stage.Remove(actorParent);
  actorParent.Remove(actorChild);

  DaliLog::PrintPass();
}

void AccessibilityManagerFocusChangedSignalP()
{
  const int SET_FOCUS_ORDER = 1;
  bool bSignalVerified = false;
  Actor actorFocus ;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  Actor actorFirst = Actor::New();
  accessibilityManager.SetFocusOrder(actorFirst, SET_FOCUS_ORDER);
  Stage stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "Stage is not created." );
  stage.Add(actorFirst);
  Actor actorSecond = Actor::New();
  accessibilityManager.SetFocusOrder(actorSecond, SET_FOCUS_ORDER+1 );
  stage.Add(actorSecond);

  FocusChangedCallback callback(bSignalVerified);
  accessibilityManager.FocusChangedSignal().Connect( &callback, &FocusChangedCallback::Callback ); // target APi
  accessibilityManager.SetCurrentFocusActor(actorFirst);
  actorFocus = accessibilityManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actorFocus != actorFirst, "Changing current focus actor is failed." );
  DALI_CHECK_FAIL( !callback.m_bSignalVerified, "Did not invoke call back." );
  callback.Reset();

  accessibilityManager.SetCurrentFocusActor(actorSecond);
  stage.Remove(actorFirst);
  stage.Remove(actorSecond);

  DaliLog::PrintPass();
}


void AccessibilityManagerFocusOvershotSignalP()
{
  const int SET_FOCUS_ORDER = 1;
  bool bSignalVerified = false;
  Actor actorFocus;
  Stage stage;
  bool bOrder;

  AccessibilityManager accessibilityManager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !accessibilityManager, "AccessibilityManager::Get() is failed." );

  FocusOvershotCallback callback(bSignalVerified);
  accessibilityManager.FocusOvershotSignal().Connect(&callback, &FocusOvershotCallback::Callback); // target APi

  Actor actorFirst = Actor::New();
  DALI_CHECK_FAIL(!actorFirst, "Actor::New() is failed." );

  accessibilityManager.SetFocusOrder(actorFirst, SET_FOCUS_ORDER);
  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL(!stage, "Stage is not created" );
  stage.Add(actorFirst);

  Actor actorSecond = Actor::New();
  DALI_CHECK_FAIL(!actorSecond, "Actor::New() is failed." );

  accessibilityManager.SetFocusOrder(actorSecond, SET_FOCUS_ORDER+1);
  stage = Stage::GetCurrent();
  DALI_CHECK_FAIL( !stage, "Stage is not created." );

  stage.Add(actorSecond);
  accessibilityManager.SetWrapMode(false);
  accessibilityManager.SetCurrentFocusActor(actorFirst);
  DALI_CHECK_FAIL( accessibilityManager.GetCurrentFocusActor() != actorFirst, "SetCurrentFocusActor() is failed." );

  accessibilityManager.MoveFocusForward();
  DALI_CHECK_FAIL( accessibilityManager.GetCurrentFocusActor() != actorSecond, "changing current focus actor actor is failed." );

  callback.m_CurrentFocusedActor = actorSecond;
  callback.m_FocusOvershotDirection = Toolkit::AccessibilityManager::OVERSHOT_NEXT;
  bOrder = accessibilityManager.MoveFocusForward();  // take overshoot

  DALI_CHECK_FAIL( bOrder != false, "forward focus movement is not overshoted." );
  DALI_CHECK_FAIL(!callback.m_bSignalVerified, "Did not invoke call back." );

  callback.Reset();
  stage.Remove(actorFirst);
  stage.Remove(actorSecond);

  DaliLog::PrintPass();
}

void AccessibilityManagerStatusChangedSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.StatusChangedSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::StatusChangedSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionNextSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionNextSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionNextSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionPreviousSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionPreviousSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionPreviousSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionActivateSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionActivateSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionActivateSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionOverSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionOverSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionOverSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadNextSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadNextSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadNextSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadPreviousSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadPreviousSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadPreviousSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionUpSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionUpSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionUpSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionDownSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionDownSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionDownSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionClearFocusSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionClearFocusSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionClearFocusSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionBackSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionBackSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionBackSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionScrollUpSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionScrollUpSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionScrollUpSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionScrollDownSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionScrollDownSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionScrollDownSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionPageLeftSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionPageLeftSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionPageLeftSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionPageRightSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionPageRightSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionPageRightSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionPageUpSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionPageUpSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionPageUpSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionPageDownSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionPageDownSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionPageDownSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionMoveToFirstSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionMoveToFirstSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionMoveToFirstSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionMoveToLastSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionMoveToLastSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionMoveToLastSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadFromTopSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadFromTopSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadFromTopSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadFromNextSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadFromNextSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadFromNextSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionZoomSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionZoomSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionZoomSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadIndicatorInformationSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadIndicatorInformationSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadIndicatorInformationSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionReadPauseResumeSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionReadPauseResumeSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionReadPauseResumeSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionStartStopSignalN(void)
{
  AccessibilityManagerSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get() is failed." );

  manager.ActionStartStopSignal().Connect( &callback, &AccessibilityManagerSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionStartStopSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerActionScrollSignalN(void)
{
  AccessibilityManagerScrollSignalHandler callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get is failed." );

  manager.ActionScrollSignal().Connect( &callback, &AccessibilityManagerScrollSignalHandler::Callback );
  DALI_CHECK_FAIL( callback.GetCalls() != 0u, "AccessibilityManager::ActionScrollSignal is failed." );

  DaliLog::PrintPass();
}

void AccessibilityManagerFocusedActorActivatedSignalN(void)
{
  FocusedActorActivatedCallback callback;

  AccessibilityManager manager = AccessibilityManager::Get();
  DALI_CHECK_FAIL( !manager, "AccessibilityManager::Get is failed." );

  try
  {
    manager.FocusedActorActivatedSignal().Connect(&callback, &FocusedActorActivatedCallback::Callback);
  }
  catch(DaliException& de)
  {
    LOG_E("FocusedActorActivatedSignal is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;

  }
  DaliLog::PrintPass();
}
/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliAccessibilityManagerConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object for
 */

int UtcDaliAccessibilityManagerConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGetP
 * @since_tizen         2.4
 * @description         To Get the singleton of AccessibilityManager object.
 */

int UtcDaliAccessibilityManagerGetP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GET_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetAccessibilityAttributeP
 * @since_tizen         2.4
 * @description         To Set and get  the information of the specified actor's accessibility attribute.
 */

int UtcDaliAccessibilityManagerSetGetAccessibilityAttributeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_ACCESSIBILITY_ATTRIBUTE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetFocusOrderP
 * @since_tizen         2.4
 * @description         To Set and Get the focus order of the actor.
 */

int UtcDaliAccessibilityManagerSetGetFocusOrderP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_FOCUS_ORDER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGenerateNewFocusOrderP
 * @since_tizen         2.4
 * @description         To Generate a new focus order number
 */

int UtcDaliAccessibilityManagerGenerateNewFocusOrderP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GENERATE_NEW_FOCUS_ORDER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGetActorByFocusOrderP
 * @since_tizen         2.4
 * @description         To Get the actor that has the specified focus order.
 */

int UtcDaliAccessibilityManagerGetActorByFocusOrderP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GET_ACTOR_BY_FOCUS_ORDER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetCurrentFocusActorP
 * @since_tizen         2.4
 * @description         To Set and Get the current focused actor
 */

int UtcDaliAccessibilityManagerSetGetCurrentFocusActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_CURRENT_FOCUS_ACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGetCurrentFocusGroupP
 * @since_tizen         2.4
 * @description         To Get the focus group of current focused actor.
 */

int UtcDaliAccessibilityManagerGetCurrentFocusGroupP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_GROUP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGetCurrentFocusOrderP
 * @since_tizen         2.4
 * @description         To Get the focus order of currently focused actor.
 */

int UtcDaliAccessibilityManagerGetCurrentFocusOrderP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GET_CURRENT_FOCUS_ORDER_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerMoveFocusForwardP
 * @since_tizen         2.4
 * @description         To Move the focus to the next focusable actor in the focus chain .
 */

int UtcDaliAccessibilityManagerMoveFocusForwardP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_MOVE_FOCUS_FORWARD_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerMoveFocusBackwardP
 * @since_tizen         2.4
 * @description         To Move the focus to the previous focusable actor in the focus chain .
 */

int UtcDaliAccessibilityManagerMoveFocusBackwardP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_MOVE_FOCUS_BACKWARD_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerClearFocusP
 * @since_tizen         2.4
 * @description         To Clear the focus from the current focused actor .
 */

int UtcDaliAccessibilityManagerClearFocusP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_CLEAR_FOCUS_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerResetP
 * @since_tizen         2.4
 * @description         To Clear the every registered focusable actor from focus manager.
 */

int UtcDaliAccessibilityManagerResetP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_RESET_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetGroupModeP
 * @since_tizen         2.4
 * @description         To Set and Get whether the group mode is enabled or not.
 */

int UtcDaliAccessibilityManagerSetGetGroupModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_GROUP_MODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetWrapModeP
 * @since_tizen         2.4
 * @description         To set and Get whether the wrap mode is enabled or not.
 */

int UtcDaliAccessibilityManagerSetGetWrapModeP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_WRAP_MODE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetFocusIndicatorActorP
 * @since_tizen         2.4
 * @description         To Set and Get the focus indicator actor.
 */

int UtcDaliAccessibilityManagerSetGetFocusIndicatorActorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_FOCUS_INDICATOR_ACTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetGetFocusGroupP
 * @since_tizen         2.4
 * @description         Checks whether SetBlurStrength and GetCurrentBlurStrength apis are executed successfully or not
 */

int UtcDaliAccessibilityManagerSetGetFocusGroupP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_GET_FOCUS_GROUP_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerGetReadPositionP
 * @since_tizen         2.4
 * @description         Checks whether SetBlurStrength and GetCurrentBlurStrength apis are executed successfully or not
 */

int UtcDaliAccessibilityManagerGetReadPositionP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_GET_READ_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerSetIsFocusGroupP
 * @since_tizen         2.4
 * @description         To set and check the focus group of current focused actor group.
 */

int UtcDaliAccessibilityManagerSetIsFocusGroupP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_SET_IS_FOCUS_GROUP_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliAccessibilityManagerFocusChangedSignalP
 * @since_tizen         2.4
 * @description         To emit the signal when the current focused actor is changed.
 */

int UtcDaliAccessibilityManagerFocusChangedSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_FOCUS_CHANGED_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerFocusOvershotSignalP
 * @since_tizen         2.4
 * @description         To emit the signal  when there is no way to move focus further.
 */

int UtcDaliAccessibilityManagerFocusOvershotSignalP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_FOCUS_OVERSHOT_SIGNAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerStatusChangedSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerStatusChangedSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_STATUS_CHANGED_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionNextSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionNextSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_NEXT_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionPreviousSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionPreviousSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_PREVIOUS_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionActivateSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionActivateSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_ACTIVATE_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionOverSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionOverSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_OVER_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadNextSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadNextSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_NEXT_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadPreviousSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadPreviousSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_PREVIOUS_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionUpSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionUpSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_UP_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionDownSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionDownSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_DOWN_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionClearFocusSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionClearFocusSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_CLEAR_FOCUS_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionBackSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionBackSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_BACK_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionScrollUpSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionScrollUpSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_SCROLL_UP_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionScrollDownSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionScrollDownSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_SCROLL_DOWN_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionPageLeftSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionPageLeftSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_PAGE_LEFT_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionPageRightSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionPageRightSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_PAGE_RIGHT_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionPageUpSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionPageUpSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_PAGE_UP_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionPageDownSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionPageDownSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_PAGE_DOWN_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionMoveToFirstSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionMoveToFirstSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_FIRST_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionMoveToLastSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionMoveToLastSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_MOVE_TO_LAST_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadFromTopSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadFromTopSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_FROM_TOP_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadFromNextSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadFromNextSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_FROM_NEXT_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionZoomSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionZoomSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_ZOOM_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadIndicatorInformationSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadIndicatorInformationSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_INDICATOR_INFORMATION_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionReadPauseResumeSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionReadPauseResumeSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_READ_PAUSE_RESUME_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionStartStopSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionStartStopSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_START_STOP_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerActionScrollSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerActionScrollSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_ACTION_SCROLL_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliAccessibilityManagerFocusedActorActivatedSignalN
 * @since_tizen         2.4
 * @description         Negative test to check Signal
 */

int UtcDaliAccessibilityManagerFocusedActorActivatedSignalN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  AccessibilityManager_TestApp testApp( application, ACCESSIBILITY_MANAGER_FOCUSED_ACTOR_ACTIVATED_SIGNAL_N );
  application.MainLoop();

  return test_return_value;
}
