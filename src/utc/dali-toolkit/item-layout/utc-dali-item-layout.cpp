#include "utc-dali-item-layout-common.h"

//& set: Itemlayout

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**
 * @function            utc_Dali_ItemLayout_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemLayout_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ItemLayout_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_ItemLayout_cleanup(void)
{

}

void ItemLayoutSetGetOrientationLeftP();
void ItemLayoutSetGetOrientationRightP();
void ItemLayoutSetGetOrientationUpP();
void ItemLayoutSetGetOrientationDownP();
void ItemLayoutSetGetItemSizeP();
void ItemLayoutGetMinimumLayoutPositionP();
void ItemLayoutGetClosestAnchorPositionP();
void ItemLayoutGetItemScrollToPositionP();
void ItemLayoutGetItemsWithinAreaP();
void ItemLayoutGetClosestOnScreenLayoutPositionP();
void ItemLayoutGetReserveItemCountP();
void ItemLayoutGetDefaultItemSizeP();
void ItemLayoutGetScrollDirectionP();
void ItemLayoutGetNextFocusItemIDP();
void ItemLayoutGetFlickSpeedFactorP();
void ItemLayoutGetItemPositionP();
void ItemLayoutGetExtensionP();
void ItemLayoutSetAndGetLayoutPropertiesP();

namespace
{
  enum TEST_CASES_LIST_ITEM_LAYOUT
  {
    ITEM_LAYOUT_SET_GET_ORIENTATION_LEFT_P,
    ITEM_LAYOUT_SET_GET_ORIENTATION_RIGHT_P,
    ITEM_LAYOUT_SET_GET_ORIENTATION_UP_P,
    ITEM_LAYOUT_SET_GET_ORIENTATION_DOWN_P,
    ITEM_LAYOUT_SET_GET_ITEM_SIZE_P,
    ITEM_LAYOUT_GET_MINIMUM_LAYOUT_POSITION_P,
    ITEM_LAYOUT_GET_CLOSEST_ANCHOR_POSITION_P,
    ITEM_LAYOUT_GET_ITEM_SCROLL_TO_POSITION_P,
    ITEM_LAYOUT_GET_ITEM_WITHIN_AREA_P,
    ITEM_LAYOUT_GET_CLOSEST_ONSCREEN_LAYOUT_POSITION_P,
    ITEM_LAYOUT_GET_RESERVE_ITEM_COUNT_P,
    ITEM_LAYOUT_GET_DEFAULT_ITEM_SIZE_P,
    ITEM_LAYOUT_GET_SCROLL_DIRECTION_P,
    ITEM_LAYOUT_GET_NEXT_FOCUS_ITEM_ID_P,
    ITEM_LAYOUT_GET_FLICK_SPEED_FACTOR_P,
    ITEM_LAYOUT_GET_ITEM_POSITION_P,
    ITEM_LAYOUT_GET_EXTENSION_P,
    ITEM_LAYOUT_SET_GET_LAYOUT_PROPERTIES_P
  };

  struct ItemLayout_TestApp : public ConnectionTracker
  {
    ItemLayout_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ItemLayout_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ItemLayout_TestApp::Tick );
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
        case ITEM_LAYOUT_SET_GET_ORIENTATION_LEFT_P:
          ItemLayoutSetGetOrientationLeftP();
          break;

        case ITEM_LAYOUT_SET_GET_ORIENTATION_RIGHT_P:
          ItemLayoutSetGetOrientationRightP();
          break;

        case ITEM_LAYOUT_SET_GET_ORIENTATION_UP_P:
          ItemLayoutSetGetOrientationUpP();
          break;

        case ITEM_LAYOUT_SET_GET_ORIENTATION_DOWN_P:
          ItemLayoutSetGetOrientationDownP();
          break;

        case ITEM_LAYOUT_SET_GET_ITEM_SIZE_P:
          ItemLayoutSetGetItemSizeP();
          break;

        case ITEM_LAYOUT_GET_MINIMUM_LAYOUT_POSITION_P:
          ItemLayoutGetMinimumLayoutPositionP();
          break;

        case ITEM_LAYOUT_GET_CLOSEST_ANCHOR_POSITION_P:
          ItemLayoutGetClosestAnchorPositionP();
          break;

        case ITEM_LAYOUT_GET_ITEM_SCROLL_TO_POSITION_P:
          ItemLayoutGetItemScrollToPositionP();
          break;

        case ITEM_LAYOUT_GET_ITEM_WITHIN_AREA_P:
          ItemLayoutGetItemsWithinAreaP();
          break;

        case ITEM_LAYOUT_GET_CLOSEST_ONSCREEN_LAYOUT_POSITION_P:
          ItemLayoutGetClosestOnScreenLayoutPositionP();
          break;

        case ITEM_LAYOUT_GET_RESERVE_ITEM_COUNT_P:
          ItemLayoutGetReserveItemCountP();
          break;

        case ITEM_LAYOUT_GET_DEFAULT_ITEM_SIZE_P:
          ItemLayoutGetDefaultItemSizeP();
          break;

        case ITEM_LAYOUT_GET_SCROLL_DIRECTION_P:
          ItemLayoutGetScrollDirectionP();
          break;

        case ITEM_LAYOUT_GET_NEXT_FOCUS_ITEM_ID_P:
          ItemLayoutGetNextFocusItemIDP();
          break;

        case ITEM_LAYOUT_GET_FLICK_SPEED_FACTOR_P:
          ItemLayoutGetFlickSpeedFactorP();
          break;

        case ITEM_LAYOUT_GET_ITEM_POSITION_P:
          ItemLayoutGetItemPositionP();
          break;

        case ITEM_LAYOUT_GET_EXTENSION_P:
          ItemLayoutGetExtensionP();
          break;

        case ITEM_LAYOUT_SET_GET_LAYOUT_PROPERTIES_P:
          ItemLayoutSetAndGetLayoutPropertiesP();
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


void ItemLayoutSetGetOrientationLeftP()
{
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;
  int nTestResult = 0;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout),  "ItemLayout Initialization is failed." );

  ItemLayoutSetGetOriantation(ControlOrientation::Left, itemLayout, &nTestResult);
  DALI_CHECK_FAIL(nTestResult > PASS_CASE_CONDITION,  "UtcDaliItemLayoutSetGetOrientationLeft is failed." );

  DaliLog::PrintPass();
}

void ItemLayoutSetGetOrientationRightP()
{
  int nTestResult = 0;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutSetGetOriantation(ControlOrientation::Right, itemLayout, &nTestResult);
  DALI_CHECK_FAIL( nTestResult > PASS_CASE_CONDITION,  "UtcDaliItemLayoutSetGetOrientationRight is failed." );

  DaliLog::PrintPass();
}

void ItemLayoutSetGetOrientationUpP()
{
  int nTestResult = 0;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutSetGetOriantation(ControlOrientation::Up, itemLayout, &nTestResult);
  DALI_CHECK_FAIL(nTestResult > PASS_CASE_CONDITION, "UtcDaliItemLayoutSetGetOrientationUp is failed." );

  DaliLog::PrintPass();
}


void ItemLayoutSetGetOrientationDownP()
{
  int nTestResult = 0;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutSetGetOriantation(ControlOrientation::Down, itemLayout, &nTestResult);
  DALI_CHECK_FAIL(nTestResult > PASS_CASE_CONDITION, "UtcDaliItemLayoutSetGetOrientationDown is failed." );

  DaliLog::PrintPass();
}

void ItemLayoutSetGetItemSizeP()
{
  const int ITEM_ID = 0;
  Vector3 vec3Target(480.0f, 800.0f, 0.0f);
  Vector3 vec3ItemSizeTemp(0.0f, 0.0f, 0.0f);
  Vector3 vec3ItemSize(1.0f, 1.0f, 1.0f);

  ControlOrientation::Type nOrientationType = ControlOrientation::Up;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutCustomization ( itemView, itemLayout, nOrientationType );
  itemLayout->SetItemSize(vec3ItemSize);
  itemLayout->GetItemSize(ITEM_ID, vec3Target, vec3ItemSizeTemp);

  DALI_CHECK_FAIL( vec3ItemSize != vec3ItemSizeTemp, "UtcDaliItemLayoutGetItemSize is failed, GetItem size should be equal to SetItem size." );

  DaliLog::PrintPass();
}

void ItemLayoutGetMinimumLayoutPositionP()
{
  Vector3 vec3ItemSize(480.0f, 800.0f, 0.0f);
  const float F_DEFAULT_POSITION = -0.35f;
  float fMinLayoutPosition = F_DEFAULT_POSITION;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  fMinLayoutPosition = itemLayout->GetMinimumLayoutPosition(itemFactory.GetNumberOfItems(), vec3ItemSize);
  DALI_CHECK_FAIL(fMinLayoutPosition == F_DEFAULT_POSITION, "Layout Position is not valid." );

  DaliLog::PrintPass();
}

void ItemLayoutGetClosestAnchorPositionP()
{
  const float F_DEFAULT_POSITION = -0.35f;
  float fAnchorPosition = F_DEFAULT_POSITION;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  fAnchorPosition = itemLayout->GetClosestAnchorPosition(LAYOUT_POSITION);
  DALI_CHECK_FAIL(fAnchorPosition == F_DEFAULT_POSITION, "Anchor Position is not valid." );

  DaliLog::PrintPass();
}

void ItemLayoutGetItemScrollToPositionP()
{
  const float F_DEFAULT_POSITION = -0.35f;
  const unsigned int  ITEM_ID = 0u;
  float fScrollToPosition = F_DEFAULT_POSITION;
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  fScrollToPosition = itemLayout->GetItemScrollToPosition(ITEM_ID);
  DALI_CHECK_FAIL(fScrollToPosition == F_DEFAULT_POSITION, "ScrollTo Position is not valid." );

  DaliLog::PrintPass();
}

void ItemLayoutGetItemsWithinAreaP()
{
  const float F_DEFAULT_POSITION = -0.35f;
  float fAnchorPosition = F_DEFAULT_POSITION;
  const unsigned int  ITEM_ID = 0u;
  Vector3 vec3LayoutSize(480.0f, 800.0f, 0.0f);
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  fAnchorPosition = itemLayout->GetClosestAnchorPosition(LAYOUT_POSITION);
  DALI_CHECK_FAIL(fAnchorPosition == F_DEFAULT_POSITION, "Anchor Position is not valid." );
  ItemRange viewableItems = itemLayout->GetItemsWithinArea(fAnchorPosition, vec3LayoutSize);

  DALI_CHECK_FAIL(!viewableItems.Within(ITEM_ID), "GetItemsWithinArea is not valid" );

  DaliLog::PrintPass();
}

void ItemLayoutGetClosestOnScreenLayoutPositionP()
{
  const unsigned int  ITEM_ID = 0u, LAYOUT_INDEX = 0;
  float fGetScreenLayoutPosition = 0.0f;
  const float F_DURATION =  0.0f, F_SET_CURRENT_POSITION = 1.0f;
  Vector3 vec3ItemSize(480.0f, 800.0f, 0.0f);
  ControlOrientation::Type nOrientationType = ControlOrientation::Up;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  itemLayout->SetOrientation(nOrientationType);
  itemView.ActivateLayout(LAYOUT_INDEX, vec3ItemSize, F_DURATION);
  fGetScreenLayoutPosition = itemLayout->GetClosestOnScreenLayoutPosition(ITEM_ID, F_SET_CURRENT_POSITION, vec3ItemSize);

  DALI_CHECK_FAIL( fGetScreenLayoutPosition != F_SET_CURRENT_POSITION, "GetScreenLayoutPosition should be equal to SetScreenLayoutPosition." );

  DaliLog::PrintPass();
}

void ItemLayoutGetReserveItemCountP()
{
  Vector3 vec3LayoutSize(480.0f, 800.0f, 0.0f);
  int nReserveItem = 0;
  ControlOrientation::Type nOrientationType = ControlOrientation::Up;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutCustomization ( itemView, itemLayout , nOrientationType );
  nReserveItem = itemLayout->GetReserveItemCount(vec3LayoutSize);

  DALI_CHECK_FAIL( nReserveItem == PASS_CASE_CONDITION, "UtcDaliItemLayoutGetReserveItemCount is failed. ReserveItemCount should not be 0." );

  DaliLog::PrintPass();
}

void ItemLayoutGetDefaultItemSizeP()
{
  const unsigned int  ITEM_ID = 0u;
  Vector3 vec3ItemSize(0.0f, 0.0f, 0.0f);
  Vector3 vec3ItemSizeTemp(0.0f, 0.0f, 0.0f);
  Vector3 vec3Target(480.0f, 800.0f, 0.0f);

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  itemLayout->GetDefaultItemSize(ITEM_ID, vec3Target, vec3ItemSize);
  itemLayout->GetItemSize(ITEM_ID, vec3Target, vec3ItemSizeTemp);

  DALI_CHECK_FAIL( vec3ItemSize != vec3ItemSizeTemp, "GetDefaultItemSize failed" );

  DaliLog::PrintPass();
}

void ItemLayoutGetScrollDirectionP()
{
  Degree scrollDegree(180.0f);
  Degree scrollDegreeTemp = scrollDegree;
  ControlOrientation::Type orientationType = ControlOrientation::Up;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  itemLayout->SetOrientation(orientationType);
  scrollDegree = itemLayout->GetScrollDirection();

  DALI_CHECK_FAIL(scrollDegree == scrollDegreeTemp, "scroolDegree should not be equal scroolDegreeTemp." );

  DaliLog::PrintPass();
}

void ItemLayoutGetNextFocusItemIDP()
{
  const int ITEM_ID = 0 , MAX_ITEM = 10, NEXT_FOCUS_ITEM = 1;
  int nNextItem = 0;
  bool bLoopEnabled = false ;
  ControlOrientation::Type nOrientationType = ControlOrientation::Up;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  ItemLayoutCustomization ( itemView, itemLayout , nOrientationType );
  nNextItem = itemLayout->GetNextFocusItemID(ITEM_ID, MAX_ITEM, Control::KeyboardFocus::RIGHT, bLoopEnabled);

  DALI_CHECK_FAIL( nNextItem != NEXT_FOCUS_ITEM, "UtcDaliItemLayoutGetNextFocusItemID is failed." );  // Next Focus Item should be 1 by default.

  DaliLog::PrintPass();
}

void ItemLayoutGetFlickSpeedFactorP()
{
  float fFlickSpeedFactor = 0.0f;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  fFlickSpeedFactor = itemLayout->GetFlickSpeedFactor();
  DALI_CHECK_FAIL( fFlickSpeedFactor == 0.0f, "UtcDaliItemLayoutGetFlickSpeedFactor is failed." );

  DaliLog::PrintPass();
}

void ItemLayoutGetItemPositionP()
{
  Vector3 vec3ItemPosition(0.0f, 0.0f, 0.0f);
  Vector3 vec3LayoutSize(480.0f, 800.0f, 0.0f);
  Vector3 vec3ItemSizeTemp(0.0f, 0.0f, 0.0f);
  const unsigned int  ITEM_ID = 0u;

  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );
  vec3ItemPosition = itemLayout->GetItemPosition(ITEM_ID, 0, vec3LayoutSize);

  DALI_CHECK_FAIL(vec3ItemPosition == vec3ItemSizeTemp, "GetItemPosition is failed." );
  DaliLog::PrintPass();
}

void ItemLayoutGetExtensionP()
{
  ItemLayoutFactory itemFactory;
  ItemView itemView;
  ItemLayoutPtr gridLayout;
  ItemLayoutPtr itemLayout;

  DALI_CHECK_FAIL(!ItemLayoutInitialize(itemFactory, itemView, gridLayout, itemLayout), "ItemLayout Initialization is failed." );

  DALI_CHECK_FAIL( itemLayout->GetExtension(), "UtcDaliItemLayoutGetExtension is falied." );

  DaliLog::PrintPass();
}

void ItemLayoutSetAndGetLayoutPropertiesP()
{
  ItemLayoutFactory itemFactory;

  ItemView itemView = ItemView::New(itemFactory);

  // Create a grid layout and add it to ItemView
  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );

  // Set the property of the grid layout
  Property::Map gridLayoutProperty;
  gridLayoutProperty[ "itemSize" ] = Vector3( 200, 200, 50 );
  DALI_CHECK_FAIL( gridLayoutProperty.Empty(), "Property is empty which is not expected." );

  gridLayout->SetLayoutProperties( gridLayoutProperty );

  itemView.AddLayout( *gridLayout );
  ItemLayoutPtr layout = itemView.GetLayout( 0 );
  DALI_CHECK_FAIL( gridLayout != layout, "SetLayoutProperties() is failed." );

  Property::Map firstLayout = gridLayout->GetLayoutProperties();

  //Check all the properties of grid layout
  DALI_CHECK_FAIL( gridLayoutProperty.Count() != firstLayout.Count(), "GetLayoutProperties() is failed." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliItemLayoutSetGetOrientationLeftP
 * @since_tizen         2.4
 * @description         Set and get the left orientation of the layout
 */

int UtcDaliItemLayoutSetGetOrientationLeftP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_ORIENTATION_LEFT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutSetGetOrientationRightP
 * @since_tizen         2.4
 * @description         Set and get the right orientation of the layout
 */

int UtcDaliItemLayoutSetGetOrientationRightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_ORIENTATION_RIGHT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutSetGetOrientationUpP
 * @since_tizen         2.4
 * @description         Set and get the up orientation of the layout
 */
int UtcDaliItemLayoutSetGetOrientationUpP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_ORIENTATION_UP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutSetGetOrientationDownP
 * @since_tizen         2.4
 * @description         Set and get the down orientation of the layout
 */
int UtcDaliItemLayoutSetGetOrientationDownP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_ORIENTATION_DOWN_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutSetGetItemSizeP
 * @since_tizen         2.4
 * @description         Get the target size of an item in the layout
 */
int UtcDaliItemLayoutSetGetItemSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_ITEM_SIZE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetMinimumLayoutPositionP
 * @since_tizen         2.4
 * @description         get minimum layout position
 */

int UtcDaliItemLayoutGetMinimumLayoutPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_MINIMUM_LAYOUT_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetClosestAnchorPositionP
 * @since_tizen         2.4
 * @description         Get the closest anchor position for the given layout position
 */

int UtcDaliItemLayoutGetClosestAnchorPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_CLOSEST_ANCHOR_POSITION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetItemScrollToPositionP
 * @since_tizen         2.4
 * @description         get scroll position
 */

int UtcDaliItemLayoutGetItemScrollToPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application,ITEM_LAYOUT_GET_ITEM_SCROLL_TO_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetItemsWithinAreaP
 * @since_tizen         2.4
 * @description         get items within range
 */

int UtcDaliItemLayoutGetItemsWithinAreaP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_ITEM_WITHIN_AREA_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetClosestOnScreenLayoutPositionP
 * @since_tizen         2.4
 * @description         Get the closest layout position to bring an item onto the screen
 */

int UtcDaliItemLayoutGetClosestOnScreenLayoutPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_CLOSEST_ONSCREEN_LAYOUT_POSITION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetReserveItemCountP
 * @since_tizen         2.4
 * @description         Gets the number of items that should be reserved for scrolling
 */

int UtcDaliItemLayoutGetReserveItemCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_RESERVE_ITEM_COUNT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetDefaultItemSizeP
 * @since_tizen         2.4
 * @description         get item default size
 */

int UtcDaliItemLayoutGetDefaultItemSizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_DEFAULT_ITEM_SIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetScrollDirectionP
 * @since_tizen         2.4
 * @description         Get the scroll direction of the layout
 */
int UtcDaliItemLayoutGetScrollDirectionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_SCROLL_DIRECTION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliControlConstructorP
 * @since_tizen         2.4
 * @description         Gets the id of the next item for KeyboardFocusManager
 */

int UtcDaliItemLayoutGetNextFocusItemIDP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_NEXT_FOCUS_ITEM_ID_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetFlickSpeedFactorP
 * @since_tizen         2.4
 * @description         Gets the Flick Speed Factor for Item
 */

int UtcDaliItemLayoutGetFlickSpeedFactorP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_FLICK_SPEED_FACTOR_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetItemPositionP
 * @since_tizen         2.4
 @description           get item position
 */

int UtcDaliItemLayoutGetItemPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_ITEM_POSITION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutGetExtensionP
 * @since_tizen         2.4
 * @description         Gets the Extension of Item Layout
 */

int UtcDaliItemLayoutGetExtensionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_GET_EXTENSION_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemLayoutSetAndGetLayoutPropertiesP
 * @since_tizen         4.0
 * @description         Sets and Gets the layout Properties
 */

int UtcDaliItemLayoutSetAndGetLayoutPropertiesP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemLayout_TestApp testApp( application, ITEM_LAYOUT_SET_GET_LAYOUT_PROPERTIES_P );
  application.MainLoop();

  return test_return_value;
}
