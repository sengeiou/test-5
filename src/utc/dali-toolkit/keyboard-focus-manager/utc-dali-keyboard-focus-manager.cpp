#include "utc-dali-keyboard-focus-manager-common.h"

//& set: KeyboardFocusManager

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_KeyboardFocusManager_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_KeyboardFocusManager_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_KeyboardFocusManager_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_KeyboardFocusManager_cleanup(void)
{

}

/** @addtogroup itc-keyboard-focus-manager-testcases
 *  @brief Integrated testcases for keyboard-focus-manager
 *  @ingroup itc-keyboard-focus-manager
 *  @{
 */


void KeyboardFocusManagerConstructorP();
void KeyboardFocusManagerGetP();
void KeyboardFocusManagerSetAndGetCurrentFocusActorP();
void KeyboardFocusManagerMoveFocusRightP();
void KeyboardFocusManagerMoveFocusLeftP();
void KeyboardFocusManagerMoveFocusUpP();
void KeyboardFocusManagerMoveFocusDownP();
void KeyboardFocusManagerClearFocusP();
void KeyboardFocusManagerSetAndGetFocusGroupLoopP();
void KeyboardFocusManagerSetAsAndGetFocusGroupP();
void KeyboardFocusManagerIsFocusGroupP();
void KeyboardFocusManagerSetAndGetFocusIndicatorActorP();
void KeyboardFocusManagerMoveFocusBackwardP();

namespace
{
  enum TEST_CASES_LIST_KEYBOARD_FOCUS_MANAGER
  {
    KEYBOARD_FOCUS_MANAGER_CONSTRUCTOR_P,
    KEYBOARD_FOCUS_MANAGER_GET_P,
    KEYBOARD_FOCUS_MANAGER_SET_AND_GET_CURRENT_FOCUS_ACTOR_P,
    KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_RIGHT_P,
    KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_LEFT_P,
    KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_UP_P,
    KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_DOWN_P,
    KEYBOARD_FOCUS_MANAGER_CLEAR_FOCUS_P,
    KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_LOOP_P,
    KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_P,
    KEYBOARD_FOCUS_MANAGER_IS_FOCUS_GROUP_P,
    KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_INDICATOR_ACTOR_P,
    KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_BACKWARD_P
  };

  struct KeyboardFocusManager_TestApp : public ConnectionTracker
  {
    KeyboardFocusManager_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &KeyboardFocusManager_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &KeyboardFocusManager_TestApp::Tick );
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
        case KEYBOARD_FOCUS_MANAGER_CONSTRUCTOR_P:
          KeyboardFocusManagerConstructorP();
          break;

        case KEYBOARD_FOCUS_MANAGER_GET_P:
          KeyboardFocusManagerGetP();
          break;

        case KEYBOARD_FOCUS_MANAGER_SET_AND_GET_CURRENT_FOCUS_ACTOR_P:
          KeyboardFocusManagerSetAndGetCurrentFocusActorP();
          break;

        case KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_RIGHT_P:
          KeyboardFocusManagerMoveFocusRightP();
          break;

        case KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_LEFT_P:
          KeyboardFocusManagerMoveFocusLeftP();
          break;

        case KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_UP_P:
          KeyboardFocusManagerMoveFocusUpP();
          break;

        case KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_DOWN_P:
          KeyboardFocusManagerMoveFocusDownP();
          break;

        case KEYBOARD_FOCUS_MANAGER_CLEAR_FOCUS_P:
          KeyboardFocusManagerClearFocusP();
          break;

        case KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_LOOP_P:
          KeyboardFocusManagerSetAndGetFocusGroupLoopP();
          break;

        case KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_P:
          KeyboardFocusManagerSetAsAndGetFocusGroupP();
          break;

        case KEYBOARD_FOCUS_MANAGER_IS_FOCUS_GROUP_P:
          KeyboardFocusManagerIsFocusGroupP();
          break;

        case KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_INDICATOR_ACTOR_P:
          KeyboardFocusManagerSetAndGetFocusIndicatorActorP();
          break;

        case KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_BACKWARD_P:
          KeyboardFocusManagerMoveFocusBackwardP();
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

void KeyboardFocusManagerConstructorP()
{
  KeyboardFocusManager keyboardFocusManager;
  DALI_CHECK_FAIL(keyboardFocusManager,  "KeyboardFocusManager Default Contructor is failed.");

  DaliLog::PrintPass();
}

void KeyboardFocusManagerGetP()
{
  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();
  DALI_CHECK_FAIL(!keyboardFocusManager, " GetCurrentFocusActor api failed to get focus actor.");

  DaliLog::PrintPass();
}

void KeyboardFocusManagerSetAndGetCurrentFocusActorP()
{
  bool bRet = false;
  // Create the first actor and add it to the stage
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " Actor::New() api failed to get valid actor.");
  actor.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(actor);

  Actor getActor;

  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, " GetCurrentFocusActor api failed to get focus actor.");

  bRet = keyboardFocusManager.SetCurrentFocusActor( actor );

  DALI_CHECK_FAIL(!bRet, " SetCurrentFocusActor api failed to set focus actor.");

  getActor = keyboardFocusManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actor != getActor , "  Set and Get Value mismatched. Return focus actor is not match with set focus actor.");
  keyboardFocusManager.ClearFocus();

  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != Actor(), " Failed to Clear all focus actor.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void KeyboardFocusManagerMoveFocusRightP()
{
  if(!KeyboardFocusManagerMoveFocus(Control::KeyboardFocus::RIGHT))
  {
    test_return_value=TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void KeyboardFocusManagerMoveFocusLeftP()
{
  if(!KeyboardFocusManagerMoveFocus(Control::KeyboardFocus::LEFT))
  {
    test_return_value=TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void KeyboardFocusManagerMoveFocusUpP()
{
  if(!KeyboardFocusManagerMoveFocus(Control::KeyboardFocus::UP))
  {
    test_return_value=TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}


void KeyboardFocusManagerMoveFocusDownP()
{
  if(!KeyboardFocusManagerMoveFocus(Control::KeyboardFocus::DOWN))
  {
    test_return_value=TC_FAIL;
    return;
  }
  DaliLog::PrintPass();
}

void KeyboardFocusManagerClearFocusP()
{
  bool bRet = false;
  // Create the first actor and add it to the stage
  Actor actor = Actor::New();
  DALI_CHECK_FAIL(!actor, " Actor::New() api failed to get valid actor.");
  actor.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(actor);

  Actor getActor;

  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, " GetCurrentFocusActor api failed to get focus actor.");

  bRet = keyboardFocusManager.SetCurrentFocusActor( actor );

  DALI_CHECK_FAIL(!bRet, " SetCurrentFocusActor api failed to set focus actor.");

  getActor = keyboardFocusManager.GetCurrentFocusActor();

  DALI_CHECK_FAIL( actor != getActor , "  Set and Get Value mismatched. Return focus actor is not match with set focus actor.");
  keyboardFocusManager.ClearFocus();

  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != Actor(), " Failed to Clear all focus actor.");
  Stage::GetCurrent().Remove(actor);

  DaliLog::PrintPass();
}

void KeyboardFocusManagerSetAndGetFocusGroupLoopP()
{
  bool bEnableLoop = true;
  bool bGetLoopStatus = false;

  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, "Keyboard Focus Manager Initialization Failed");

  keyboardFocusManager.SetFocusGroupLoop(bEnableLoop);

  bGetLoopStatus = keyboardFocusManager.GetFocusGroupLoop();

  DALI_CHECK_FAIL(bEnableLoop != bGetLoopStatus, " GetFocusGroupLoop AND SetFocusGroupLoop  IS FAILED to match the value");

  DaliLog::PrintPass();
}

void KeyboardFocusManagerSetAsAndGetFocusGroupP()
{
  bool bRet = false;

  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, "Keyboard Focus Manager Initialization Failed");

  Actor parentActor = Actor::New();
  parentActor.SetName("Parent Actor");

  Actor childActor = Actor::New();
  parentActor.Add(childActor);
  Stage::GetCurrent().Add(parentActor);
  Actor testActor;

  keyboardFocusManager.SetAsFocusGroup(parentActor, true);
  bRet = keyboardFocusManager.IsFocusGroup(parentActor);

  DALI_CHECK_FAIL(!bRet, " Failed to set a focus group and check that group.");
  testActor = keyboardFocusManager.GetFocusGroup(childActor);

  DALI_CHECK_FAIL( testActor.GetName() !=  parentActor.GetName(), " SetAsFocusGroup AND GetFocusGroup  IS FAILED to match the value");
  Stage::GetCurrent().Remove(parentActor);
  DaliLog::PrintPass();
}

void KeyboardFocusManagerIsFocusGroupP()
{
  bool bRet = false;

  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, "Keyboard Focus Manager Initialization Failed");

  Actor parentActor = Actor::New();
  parentActor.SetName("Parent Actor");

  Actor childActor = Actor::New();
  parentActor.Add(childActor);
  Stage::GetCurrent().Add(parentActor);
  Actor testActor;

  keyboardFocusManager.SetAsFocusGroup(parentActor, true);
  bRet = keyboardFocusManager.IsFocusGroup(parentActor);

  DALI_CHECK_FAIL(!bRet, " Failed to set a focus group and check that group.");
  Stage::GetCurrent().Remove(parentActor);

  DaliLog::PrintPass();
}

void KeyboardFocusManagerSetAndGetFocusIndicatorActorP()
{
  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, "Keyboard Focus Manager Initialization Failed");

  Actor defaultFocusIndicatorActor;
  Actor newFocusIndicatorActor = Actor::New();
  Actor getFocusIndicatorActor;

  defaultFocusIndicatorActor = keyboardFocusManager.GetFocusIndicatorActor();

  DALI_CHECK_FAIL(!defaultFocusIndicatorActor, "GetFocusIndicatorActor  IS FAILED to match the value");

  keyboardFocusManager.SetFocusIndicatorActor(newFocusIndicatorActor);

  getFocusIndicatorActor = keyboardFocusManager.GetFocusIndicatorActor();

  DALI_CHECK_FAIL(getFocusIndicatorActor != newFocusIndicatorActor, " SetFocusIndicatorActor AND GetFocusIndicatorActor  IS FAILED to match the value");

  DaliLog::PrintPass();
}

void KeyboardFocusManagerMoveFocusBackwardP()
{
  KeyboardFocusManager keyboardFocusManager = KeyboardFocusManager::Get();

  DALI_CHECK_FAIL(!keyboardFocusManager, "Keyboard Focus Manager Initialization Failed");

  // Make history stack full
  for(int i = 0 ; i < 31 ; i ++)
  {
    Actor actor = Actor::New();
    actor.SetKeyboardFocusable(true);
    Stage::GetCurrent().Add(actor);
    keyboardFocusManager.SetCurrentFocusActor(actor);
  }

  // Create the first actor and add it to the stage
  Actor first = Actor::New();
  first.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(first);

  // Create the second actor and add it to the stage
  Actor second = Actor::New();
  second.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(second);

  // Create the second actor and add it to the stage
  Actor third = Actor::New();
  third.SetKeyboardFocusable(true);
  Stage::GetCurrent().Add(third);

  // Check that the focus is set on the second actor
  DALI_CHECK_FAIL(keyboardFocusManager.SetCurrentFocusActor(first) != true, "SetCurrentFocusActor() is failed");
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != first, "GetCurrentFocusActor() is failed");

  // Check that the focus is set on the second actor
  DALI_CHECK_FAIL(keyboardFocusManager.SetCurrentFocusActor(second) != true, "SetCurrentFocusActor() is failed");
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != second, "GetCurrentFocusActor() is failed");

  // Check that the focus is set on the third  actor
  DALI_CHECK_FAIL(keyboardFocusManager.SetCurrentFocusActor(third) != true, "SetCurrentFocusActor() is failed");
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != third, "GetCurrentFocusActor() is failed");

  // Move the focus backward
  keyboardFocusManager.MoveFocusBackward();

  // Check that it current focused actor is second actor
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != second, "MoveFocusBackward() is failed");

  // Check that the focus is set on the third actor
  DALI_CHECK_FAIL(keyboardFocusManager.SetCurrentFocusActor(third) != true, "SetCurrentFocusActor() is failed");
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != third, "GetCurrentFocusActor() is failed");

  // Remove the second actor on stage
  second.Unparent();

  // Move the focus backward
  keyboardFocusManager.MoveFocusBackward();

  // Check that it current focused actor is first actor
  DALI_CHECK_FAIL(keyboardFocusManager.GetCurrentFocusActor() != first, "GetCurrentFocusActor() is failed");

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliKeyboardFocusManagerConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliKeyboardFocusManagerConstructorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_CONSTRUCTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerGetP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliKeyboardFocusManagerGetP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_GET_P);
  application.MainLoop();

  return test_return_value;
}
/**
 * @testcase            UtcDaliKeyboardFocusManagerSetAndGetCurrentFocusActorP
 * @since_tizen         2.4
 * @description         Move the keyboard focus to the given actor and Get the current focused actor.
 */

int UtcDaliKeyboardFocusManagerSetAndGetCurrentFocusActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_SET_AND_GET_CURRENT_FOCUS_ACTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerMoveFocusRightP
 * @since_tizen         2.4
 * @description         Move the focus to the next focusable actor in the focus chain in the right direction (according to the focus traversal order).
 */

int UtcDaliKeyboardFocusManagerMoveFocusRightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_RIGHT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerMoveFocusLeftP
 * @since_tizen         2.4
 * @description         Move the focus to the next focusable actor in the focus chain in the left direction (according to the focus traversal order).
 */

int UtcDaliKeyboardFocusManagerMoveFocusLeftP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_LEFT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerMoveFocusUpP
 * @since_tizen         2.4
 * @description         Move the focus to the next focusable actor in the focus chain in the upper direction (according to the focus traversal order).
 */

int UtcDaliKeyboardFocusManagerMoveFocusUpP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_UP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerMoveFocusDownP
 * @since_tizen         2.4
 * @description         Move the focus to the next focusable actor in the focus chain in the downward direction (according to the focus traversal order).
 */

int UtcDaliKeyboardFocusManagerMoveFocusDownP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_DOWN_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerClearFocusP
 * @since_tizen         2.4
 * @description         Clears the Focus from the current object
 */

int UtcDaliKeyboardFocusManagerClearFocusP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_CLEAR_FOCUS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerSetAndGetFocusGroupLoopP
 * @since_tizen         2.4
 * @description         Set and Get the focus movement that can be looped within the same focus group.
 */

int UtcDaliKeyboardFocusManagerSetAndGetFocusGroupLoopP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_LOOP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerSetAsAndGetFocusGroupP
 * @since_tizen         2.4
 * @description         Set an actor is a focus group and Returns the closest ancestor of the given actor that is a focus group.
 */

int UtcDaliKeyboardFocusManagerSetAsAndGetFocusGroupP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_GROUP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerIsFocusGroupP
 * @since_tizen         2.4
 * @description         checks the focus of current object
 */

int UtcDaliKeyboardFocusManagerIsFocusGroupP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_IS_FOCUS_GROUP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerSetAndGetFocusIndicatorActorP
 * @since_tizen         2.4
 * @description         Set and Get the focus indicator actor.
 */

int UtcDaliKeyboardFocusManagerSetAndGetFocusIndicatorActorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_SET_AND_GET_FOCUS_INDICATOR_ACTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliKeyboardFocusManagerMoveFocusBackwardP
 * @since_tizen         4.0
 * @description         Move the focus to the prev focused actor.
 */

int UtcDaliKeyboardFocusManagerMoveFocusBackwardP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  KeyboardFocusManager_TestApp testApp( application, KEYBOARD_FOCUS_MANAGER_MOVE_FOCUS_BACKWARD_P);
  application.MainLoop();

  return test_return_value;
}
