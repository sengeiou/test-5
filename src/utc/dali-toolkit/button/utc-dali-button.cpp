#include "utc-dali-button-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_Button_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Button_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_Button_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_Button_cleanup(void)
{

}

// Status for button selected state
static bool g_bButtonSelectedState = false;

/**
 * @function            CbButtonSelected
 * @description         Callback for button is selected
 * @param [in]          button [Button instance]
 * @return              bool
 */
bool CbButtonSelected( Button button )
{
  LOG_I("Callback for button selection is called.");
  g_bButtonSelectedState = button.GetProperty<bool>( Button::Property::SELECTED );
  return true;
}

void ButtonConstructorP();
void ButtonCopyConstructorP();
void ButtonOperatorAssignmentP();
void ButtonDowncastP();
void ButtonDowncastN();
void ButtonSetIsDisabledP();
void ButtonSetIsAutoRepeatingP();
void ButtonSetGetInitialAutoRepeatingDelayP();
void ButtonSetGetNextAutoRepeatingDelayP();
void ButtonSetIsTogglableButtonP();
void ButtonSetIsSelectedP();
void ButtonSetGetLabelP();
void ButtonDisabledPropertyP();
void ButtonSetDisabledWithDifferentStates01P();
void ButtonSetDisabledWithDifferentStates02P();
void ButtonAutoRepeatingPropertyP();
void ButtonInitialAutoRepeatingDelayPropertyP();
void ButtonNextAutoRepeatingDelayPropertyP();
void ButtonTogglablePropertyP();
void ButtonSetUnselectedVisualP();
void ButtonSetSelectedVisualP();
void ButtonSetDisabledSelectedVisualP();
void ButtonSetDisabledUnselectedVisualP();
void ButtonSetUnselectedBackgroundVisualP();
void ButtonSetSelectedBackgroundVisualP();
void ButtonSetDisabledUnselectedBackgroundVisualP();
void ButtonSetDisabledSelectedBackgroundVisualP();

namespace
{
  enum TEST_CASES_LIST_BUTTON
  {
    BUTTON_COPY_CONSTRUCTOR_P,
    BUTTON_CONSTRUCTOR_P,
    BUTTON_OPERATOR_ASSIGNMENT_P,
    BUTTON_DOWNCAST_P,
    BUTTON_DOWNCAST_N,
    BUTTON_SET_IS_DISABLED_P,
    BUTTON_SET_IS_AUTO_REPEATING_P,
    BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P,
    BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P,
    BUTTON_SET_IS_TOGGLABLE_BUTTON_P,
    BUTTON_SET_IS_SELECTED_P,
    BUTTON_SET_GET_LABEL_P,
    BUTTON_DISABLED_PROPERTY_P,
    BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_01_P,
    BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_02_P,
    BUTTON_AUTO_REPEATING_PROPERTY_P,
    BUTTON_INITIAL_AUTO_REPEATING_DELAY_PROPERTY_P,
    BUTTON_NEXT_AUTO_REPEATING_DELAY_PROPERTY_P,
    BUTTON_TOGGLABLE_PROPERTY_P,
    BUTTON_SET_UNSELECTED_VISUAL_P,
    BUTTON_SET_SELECTED_VISUAL_P,
    BUTTON_SET_DISABLED_SELECTED_VISUAL_P,
    BUTTON_SET_DISABLED_UNSELECTED_VISUAL_P,
    BUTTON_SET_UNSELECTED_BACKGROUND_VISUAL_P,
    BUTTON_SET_SELECTED_BACKGROUND_VISUAL_P,
    BUTTON_SET_DISABLED_UNSELECTED_BACKGROUND_VISUAL_P,
    BUTTON_SET_DISABLED_SELECTED_BACKGROUND_VISUAL_P
  };

  struct Button_TestApp : public ConnectionTracker
  {
    Button_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &Button_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &Button_TestApp::Tick );
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
        case BUTTON_CONSTRUCTOR_P:
          ButtonConstructorP();
          break;

        case BUTTON_COPY_CONSTRUCTOR_P:
          ButtonCopyConstructorP();
          break;

        case BUTTON_OPERATOR_ASSIGNMENT_P:
          ButtonOperatorAssignmentP();
          break;

        case BUTTON_DOWNCAST_N:
          ButtonDowncastN();
          break;

        case BUTTON_DOWNCAST_P:
          ButtonDowncastP();
          break;

        case BUTTON_SET_IS_DISABLED_P:
          ButtonSetIsDisabledP();
          break;

        case BUTTON_SET_IS_AUTO_REPEATING_P:
          ButtonSetIsAutoRepeatingP();
          break;

        case BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P:
          ButtonSetGetInitialAutoRepeatingDelayP();
          break;

        case BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P:
          ButtonSetGetNextAutoRepeatingDelayP();
          break;

        case BUTTON_SET_IS_TOGGLABLE_BUTTON_P:
          ButtonSetIsTogglableButtonP();
          break;

        case BUTTON_SET_IS_SELECTED_P:
          ButtonSetIsSelectedP();
          break;

        case BUTTON_SET_GET_LABEL_P:
          ButtonSetGetLabelP();
          break;

        case BUTTON_DISABLED_PROPERTY_P:
          ButtonDisabledPropertyP();
          break;

        case BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_01_P:
          ButtonSetDisabledWithDifferentStates01P();
          break;

        case BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_02_P:
          ButtonSetDisabledWithDifferentStates02P();
          break;

        case BUTTON_AUTO_REPEATING_PROPERTY_P:
          ButtonAutoRepeatingPropertyP();
          break;

        case BUTTON_INITIAL_AUTO_REPEATING_DELAY_PROPERTY_P:
          ButtonInitialAutoRepeatingDelayPropertyP();
          break;

        case BUTTON_NEXT_AUTO_REPEATING_DELAY_PROPERTY_P:
          ButtonNextAutoRepeatingDelayPropertyP();
          break;

        case BUTTON_TOGGLABLE_PROPERTY_P:
          ButtonTogglablePropertyP();
          break;

        case BUTTON_SET_UNSELECTED_VISUAL_P:
          ButtonSetUnselectedVisualP();
          break;

        case BUTTON_SET_SELECTED_VISUAL_P:
          ButtonSetSelectedVisualP();
          break;

        case BUTTON_SET_DISABLED_SELECTED_VISUAL_P:
          ButtonSetDisabledSelectedVisualP();
          break;

        case BUTTON_SET_DISABLED_UNSELECTED_VISUAL_P:
          ButtonSetDisabledUnselectedVisualP();
          break;

        case BUTTON_SET_UNSELECTED_BACKGROUND_VISUAL_P:
          ButtonSetUnselectedBackgroundVisualP();
          break;

        case BUTTON_SET_SELECTED_BACKGROUND_VISUAL_P:
          ButtonSetSelectedBackgroundVisualP();
          break;

        case BUTTON_SET_DISABLED_UNSELECTED_BACKGROUND_VISUAL_P:
          ButtonSetDisabledUnselectedBackgroundVisualP();
          break;

        case BUTTON_SET_DISABLED_SELECTED_BACKGROUND_VISUAL_P:
          ButtonSetDisabledSelectedBackgroundVisualP();
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

void ButtonConstructorP()
{
  Button button;
  DALI_CHECK_FAIL(button,  "Button Default Contructor is failed.");

  DaliLog::PrintPass();
}

void ButtonCopyConstructorP()
{
  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  Button* CopyConstButton(&button);
  DALI_CHECK_FAIL(CopyConstButton == NULL, "Button  Copy Constructor is Failed ");

  DaliLog::PrintPass();
}

void ButtonOperatorAssignmentP()
{
  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  Button* OperatorButton = &button;
  DALI_CHECK_FAIL(OperatorButton == NULL, "Button assignment operator  is Failed ");

  DaliLog::PrintPass();
}

void ButtonDowncastP()
{
  Button button;
  DALI_CHECK_FAIL(button,"Default button object is not null.");

  button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  BaseHandle handleButton (button);
  DALI_CHECK_FAIL(!handleButton, "BaseHandle object is not valid after assigning a valid button object.");

  Button downCastButton = Button::DownCast( handleButton );
  DALI_CHECK_FAIL(!downCastButton, "DownCast() is failed to return valid button object from basehandle.");

  DALI_CHECK_FAIL(button != downCastButton, "button object is not match with downcasted button object.");

  DaliLog::PrintPass();
}

void ButtonDowncastN()
{
  BaseHandle unInitializedObject;

  Button downCastButton = Button::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(downCastButton, "Button handle is not empty." );

  Button downCastButton2 = DownCast< Button >( unInitializedObject );
  DALI_CHECK_FAIL(downCastButton2, "Button handle is not empty." );

  DaliLog::PrintPass();
}

void ButtonSetIsDisabledP()
{
  bool bSetDisable = false ;
  bool bIsDisable  = true  ;

  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"PushButton::New() is failed to create valid button object ");

  Stage::GetCurrent().Add( button );
  button.SetProperty( Button::Property::DISABLED, bSetDisable );

  bIsDisable = button.GetProperty<bool>( Button::Property::DISABLED );
  DALI_CHECK_FAIL( bSetDisable != bIsDisable, "Button::Property::DISABLED does not work properly");
  bSetDisable = true ;

  button.SetProperty( Button::Property::DISABLED, bSetDisable );

  bIsDisable = button.GetProperty<bool>( Button::Property::DISABLED );
  DALI_CHECK_FAIL( bSetDisable != bIsDisable, "Button::Property::DISABLED does not work properly");

  Stage::GetCurrent().Remove( button );
  DaliLog::PrintPass();

}

void ButtonSetIsAutoRepeatingP()
{
  bool bAutoRepeatCheck = false ;
  bool bIsAutoRepeat = true;

  Button pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsAutoRepeat );

  bAutoRepeatCheck = pushButton.GetProperty<bool>( Button::Property::AUTO_REPEATING );

  DALI_CHECK_FAIL( !bAutoRepeatCheck,  "Button::Property::AUTO_REPEATING is not working properly" );

  DaliLog::PrintPass();
}

void ButtonSetGetInitialAutoRepeatingDelayP()
{
  float fSetAutoRepeat = 1.15f;
  float fGetInitRepeatTime = 0.0f ;
  bool bIsRepeating = true   ;

  Button pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsRepeating );

  pushButton.SetProperty( Button::Property::INITIAL_AUTO_REPEATING_DELAY, fSetAutoRepeat );
	
	fGetInitRepeatTime = pushButton.GetProperty<float>( Button::Property::INITIAL_AUTO_REPEATING_DELAY );
	
  DALI_CHECK_FAIL( fGetInitRepeatTime != fSetAutoRepeat, "Button::Property::INITIAL_AUTO_REPEATING_DELAY is not match properly .");

  DaliLog::PrintPass();
}

void ButtonSetGetNextAutoRepeatingDelayP()
{
  float fSetNextAutoRepeat = 1.15f;
  float fGetNextRepeatTime = 0.0f;
  bool bIsRepeating = true   ;

  Button pushButton = PushButton::New();

  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  pushButton.SetProperty( Button::Property::AUTO_REPEATING, bIsRepeating );

  DALI_CHECK_FAIL( !pushButton.GetProperty<bool>( Button::Property::AUTO_REPEATING ), "Button::Property::AUTO_REPEATING is failed." );

	pushButton.SetProperty( Button::Property::NEXT_AUTO_REPEATING_DELAY, fSetNextAutoRepeat );

	fGetNextRepeatTime = pushButton.GetProperty<float>( Button::Property::NEXT_AUTO_REPEATING_DELAY );

  DALI_CHECK_FAIL( fGetNextRepeatTime != fSetNextAutoRepeat, "Button::Property::NEXT_AUTO_REPEATING_DELAY is not match properly.");

  DaliLog::PrintPass();
}

void ButtonSetIsSelectedP()
{
  bool bSetSelected = true;
  bool bIsSetSelected  = false;
  bool bSetTogglable   = true;
  bool bIsTogglable    = false;

  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  Stage::GetCurrent().Add( button );
  button.SetProperty( Button::Property::TOGGLABLE, bSetTogglable );
  button.StateChangedSignal().Connect( &CbButtonSelected );

  bIsTogglable = button.GetProperty<bool>( Button::Property::TOGGLABLE );
  DALI_CHECK_FAIL( bSetTogglable != bIsTogglable, "SetTogglableButton and IsTogglableButton value does not match properly");

  button.SetProperty( Button::Property::SELECTED, bSetSelected );
  bIsSetSelected = button.GetProperty<bool>( Button::Property::SELECTED );

  DALI_CHECK_FAIL(bSetSelected != bIsSetSelected, "Button::Property::SELECTED does not work properly");
  DALI_CHECK_FAIL(!g_bButtonSelectedState, "CbButtonSelected callback  is not called properly");

  Stage::GetCurrent().Remove( button );
  DaliLog::PrintPass();
}

void ButtonSetIsTogglableButtonP()
{
  bool bSetTogglable   = true;
  bool bIsTogglable    = false;

  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  Stage::GetCurrent().Add( button );
  button.SetProperty( Button::Property::TOGGLABLE, bSetTogglable );
  button.StateChangedSignal().Connect( &CbButtonSelected );

  bIsTogglable = button.GetProperty<bool>( Button::Property::TOGGLABLE );
  DALI_CHECK_FAIL( bSetTogglable != bIsTogglable, "Button::Property::TOGGLABLE does not work properly");

  Stage::GetCurrent().Remove( button );
  DaliLog::PrintPass();
}

void ButtonSetGetLabelP()
{
  string strGetlabelText;
  string strSetLabelText( "Happy" );

  Button button = PushButton::New();
  DALI_CHECK_FAIL(!button,"Button::New() is failed to create valid button object ");

  Stage::GetCurrent().Add( button );
  button.SetProperty( Button::Property::LABEL, strSetLabelText );

  Property::Value value = button.GetProperty( Toolkit::Button::Property::LABEL );
	Property::Map *labelProperty = value.GetMap();
  if ( labelProperty )
  {
    Property::Value* value = labelProperty->Find( Toolkit::TextVisual::Property::TEXT );
    value->Get( strGetlabelText );
  }

  DALI_CHECK_FAIL( strSetLabelText != strGetlabelText, "Toolkit::Button::Property::LABEL does not work" );

  Stage::GetCurrent().Remove( button );
  DaliLog::PrintPass();
}

void ButtonDisabledPropertyP()
{
  Button button = PushButton::New();

  button.SetProperty( button.GetPropertyIndex("disabled"), true );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("disabled")) != true, "GetDisabledProperty is failed." );

  button.SetProperty( button.GetPropertyIndex("disabled"), false );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("disabled")) != false, "GetDisabledProperty is failed." );

  button.SetProperty( button.GetPropertyIndex("disabled"), true );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("disabled")) != true, "GetDisabledProperty is failed." );

  button.SetProperty( button.GetPropertyIndex("disabled"), false );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("disabled")) != false, "GetDisabledProperty is failed." );

  DaliLog::PrintPass();
}

void ButtonSetDisabledWithDifferentStates01P()
{
  Button button = PushButton::New();

  bool SELECTED = true;

  button.SetProperty( Button::Property::TOGGLABLE, true);
  button.SetProperty( Button::Property::SELECTED, SELECTED );

  button.SetProperty( Button::Property::DISABLED, true);

  button.SetProperty( Button::Property::SELECTED, !SELECTED );

  bool isSelected = button.GetProperty<bool>( Button::Property::SELECTED );

  DALI_CHECK_FAIL( isSelected != SELECTED, "Set DISABLED property and Get SELECTED Property is failed." );

  DaliLog::PrintPass();
}

void ButtonSetDisabledWithDifferentStates02P()
{
  Button button = PushButton::New();

  bool SELECTED = true;

  button.SetProperty( Button::Property::TOGGLABLE, true );
  button.SetProperty( Button::Property::SELECTED, SELECTED );
  button.SetProperty( Button::Property::DISABLED, true );

  bool isSelected =  button.GetProperty<bool>( Button::Property::SELECTED );
  DALI_CHECK_FAIL( isSelected != SELECTED , "Set DISABLED property and Get SELECTED Property is failed." );

  button.SetProperty( Button::Property::DISABLED, false );
  button.SetProperty( Button::Property::SELECTED, !SELECTED );

  isSelected = button.GetProperty<bool>( Button::Property::SELECTED );
  DALI_CHECK_FAIL( isSelected == SELECTED , "Set SELECTED property and Get SELECTED Property is failed." );

  DaliLog::PrintPass();
}

void ButtonAutoRepeatingPropertyP()
{
  Button button = PushButton::New();

  button.SetProperty( button.GetPropertyIndex("autoRepeating"), true );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("autoRepeating")) != true, "Get AutoRepeating Property is failed." );

  button.SetProperty( button.GetPropertyIndex("autoRepeating"), false );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("autoRepeating")) != false, "Get AutoRepeating Property is failed." );

  button.SetProperty( button.GetPropertyIndex("autoRepeating"), true );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("autoRepeating")) != true, "Get AutoRepeating Property is failed." );

  button.SetProperty( Button::Property::AUTO_REPEATING, false );
  DALI_CHECK_FAIL( button.GetProperty<bool>( Button::Property::AUTO_REPEATING ), "Button::Property::AUTO_REPEATING is failed." );

  DaliLog::PrintPass();
}

void ButtonInitialAutoRepeatingDelayPropertyP()
{
  Button button = PushButton::New();

  button.SetProperty( button.GetPropertyIndex("initialAutoRepeatingDelay"), 0.5f );
  DALI_CHECK_FAIL( button.GetProperty<float>( button.GetPropertyIndex("initialAutoRepeatingDelay")) != 0.5f, "Get InitialAutoRepeatingDelay Property is failed." );

  DaliLog::PrintPass();
}

void ButtonNextAutoRepeatingDelayPropertyP()
{
  Button button = PushButton::New();

  button.SetProperty( button.GetPropertyIndex("nextAutoRepeatingDelay"), 0.5f );
  DALI_CHECK_FAIL( button.GetProperty<float>( button.GetPropertyIndex("nextAutoRepeatingDelay")) != 0.5f, "Get NextAutoRepeatingDelay Property is failed." );

  DaliLog::PrintPass();
}

void ButtonTogglablePropertyP()
{
  Button button = PushButton::New();

  button.SetProperty( button.GetPropertyIndex("togglable"), true );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("togglable")) != true, "Get Togglable Property is failed." );

  button.SetProperty( button.GetPropertyIndex("togglable"), false );
  DALI_CHECK_FAIL( button.GetProperty<bool>( button.GetPropertyIndex("togglable")) != false, "Get Togglable Property is failed." );

  DaliLog::PrintPass();
}

void ButtonSetUnselectedVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::UNSELECTED_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetSelectedVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::SELECTED_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetDisabledSelectedVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::DISABLED_SELECTED_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetDisabledUnselectedVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::DISABLED_UNSELECTED_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetUnselectedBackgroundVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::UNSELECTED_BACKGROUND_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetSelectedBackgroundVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::SELECTED_BACKGROUND_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetDisabledUnselectedBackgroundVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::DISABLED_UNSELECTED_BACKGROUND_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ButtonSetDisabledSelectedBackgroundVisualP()
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Button pushButton = PushButton::New();
  DALI_CHECK_FAIL(!pushButton,  "Button::New() is failed .");

  try
  {
    pushButton.SetProperty( Toolkit::Button::Property::DISABLED_SELECTED_BACKGROUND_VISUAL, strActualPathOne );
  }
  catch(DaliException& de)
  {
    LOG_E("SetUnselectedImage with image is failed.");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    test_return_value=1;
    return;
  }
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/


/**
 * @testcase            UtcDaliButtonConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliButtonConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonCopyConstructorP
 * @since_tizen         2.4
 * @description         Creates another handle that points to the same real object.
 */

int UtcDaliButtonCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Button Assignment Operator is checked.
 */

int UtcDaliButtonOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

//& purpose: Downcast an Object handle to Button.
/**
 * @testcase            UtcDaliButtonDowncastP
 * @since_tizen         2.4
 * @description         Downcast an Object handle to Button.
 */

int UtcDaliButtonDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliButtonDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetIsDisabledP
 * @since_tizen         2.4
 * @description         Sets and Checks the button as disabled or not.
 */

int UtcDaliButtonSetIsDisabledP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_IS_DISABLED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetIsAutoRepeatingP
 * @since_tizen         2.4
 * @description         Sets the autorepeating property. .
 */

int UtcDaliButtonSetIsAutoRepeatingP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_IS_AUTO_REPEATING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetGetInitialAutoRepeatingDelayP
 * @since_tizen         2.4
 * @description         Sets the autorepeating property. .
 */

int UtcDaliButtonSetGetInitialAutoRepeatingDelayP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_GET_INITIAL_AUTO_REPEATING_DELAY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetGetNextAutoRepeatingDelayP
 * @since_tizen         2.4
 * @description         Sets the autorepeating property. .
 */

int UtcDaliButtonSetGetNextAutoRepeatingDelayP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_GET_NEXT_AUTO_REPEATING_DELAY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetIsSelectedP
 * @since_tizen         2.4
 * @description         Sets and Checks the button  selected or unselected.
 */

int UtcDaliButtonSetIsSelectedP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_IS_SELECTED_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetIsTogglableButtonP
 * @since_tizen         2.4
 * @description         Sets and Checks the button is Togglable or not
 */

int UtcDaliButtonSetIsTogglableButtonP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_IS_TOGGLABLE_BUTTON_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetGetLabelP
 * @since_tizen         2.4
 * @description         Sets and Checks the button label
 */

int UtcDaliButtonSetGetLabelP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_GET_LABEL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonDisabledPropertyP
 * @description         Sets and Gets the button as disabled.
 */

int UtcDaliButtonDisabledPropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_DISABLED_PROPERTY_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonSetDisabledWithDifferentStates01P
 * @description         Sets and Gets the button as disabled with different state.
 */

int UtcDaliButtonSetDisabledWithDifferentStates01P(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_01_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonSetDisabledWithDifferentStates02P
 * @description         Sets and Gets the button as disabled with different state.
 */

int UtcDaliButtonSetDisabledWithDifferentStates02P(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_WITH_DIFFERENT_STATES_02_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonAutoRepeatingPropertyP
 * @description         Sets and Gets the button set as auto repeating property.
 */

int UtcDaliButtonAutoRepeatingPropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_AUTO_REPEATING_PROPERTY_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonInitialAutoRepeatingDelayPropertyP
 * @description         Sets and Gets the button set as initial auto repeating delay property.
 */

int UtcDaliButtonInitialAutoRepeatingDelayPropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_INITIAL_AUTO_REPEATING_DELAY_PROPERTY_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonNextAutoRepeatingDelayPropertyP
 * @description         Sets and Gets the button set as next auto repeating delay property.
 */

int UtcDaliButtonNextAutoRepeatingDelayPropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_NEXT_AUTO_REPEATING_DELAY_PROPERTY_P );
  application.MainLoop();

  return test_return_value;
}


/**
 * @testcase            UtcDaliButtonTogglablePropertyP
 * @description         Sets and Gets the button set as togglable property.
 */

int UtcDaliButtonTogglablePropertyP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_TOGGLABLE_PROPERTY_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetUnselectedVisualP
 * @since_tizen         5.5
 * @description         Sets the unselected button foreground/icon visual
 */

int UtcDaliButtonSetUnselectedVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_UNSELECTED_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetSelectedVisualP
 * @since_tizen         5.5
 * @description         Sets the selected button foreground/icon visual
 */

int UtcDaliButtonSetSelectedVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_SELECTED_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetDisabledSelectedVisualP
 * @since_tizen         5.5
 * @description         Sets the disabled selected state foreground/icon button visual
 */

int UtcDaliButtonSetDisabledSelectedVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_SELECTED_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetDisabledUnselectedVisualP
 * @since_tizen         5.5
 * @description         Sets the disabled unselected state foreground/icon visual
 */

int UtcDaliButtonSetDisabledUnselectedVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_UNSELECTED_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetUnselectedBackgroundVisualP
 * @since_tizen         5.5
 * @description         Sets the disabled in the unselected state background, button visual
 */

int UtcDaliButtonSetUnselectedBackgroundVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_UNSELECTED_BACKGROUND_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetSelectedBackgroundVisualP
 * @since_tizen         5.5
 * @description         Sets the selected background button visual
 */

int UtcDaliButtonSetSelectedBackgroundVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_SELECTED_BACKGROUND_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetDisabledUnselectedBackgroundVisualP
 * @since_tizen         5.5
 * @description         Sets the disabled while unselected background button visual
 */

int UtcDaliButtonSetDisabledUnselectedBackgroundVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_UNSELECTED_BACKGROUND_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliButtonSetDisabledSelectedBackgroundVisualP
 * @since_tizen         5.5
 * @description         Sets the disabled while selected background button visual
 */

int UtcDaliButtonSetDisabledSelectedBackgroundVisualP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  Button_TestApp testApp( application, BUTTON_SET_DISABLED_SELECTED_BACKGROUND_VISUAL_P );
  application.MainLoop();

  return test_return_value;
}
