#include "utc-dali-item-view-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**Status for item view on layout activated callback**/
static bool gItemViewOnLayoutActivatedCalled;

//& set: ItemitemView

/**
 * @function            utc_Dali_ItemView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */


void utc_Dali_ItemView_startup(void)
{
  test_return_value=0;
}

/**
 * @function            utc_Dali_ItemView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */


void utc_Dali_ItemView_cleanup(void)
{
}


/**
 * @function            ItemViewOnLayoutActivated
 * @description         Callback for ItemView on layout activated
 * @return              NA
 */
static void ItemViewOnLayoutActivated()
{
  gItemViewOnLayoutActivatedCalled = true;
}

void ItemViewConstructorP();
void ItemViewNewP();
void ItemViewCopyConstructorP();
void ItemViewOperatorAssignmentP();
void ItemViewDownCastP();
void ItemViewDownCastN();
void ItemViewGetAddLayoutCountP();
void ItemViewGetLayoutP();
void ItemViewRemoveLayoutP();
void ItemViewGetActivateDeactivateLayoutP();
void ItemViewGetCurrentLayoutPositionP();
void ItemViewSetAndGetMinimumSwipeSpeedP();
void ItemViewSetAndGetMinimumSwipeDistanceP();
void ItemViewSetAndGetMouseWheelScrollDistanceStepP();
void ItemViewSetAndGetAnchoringP();
void ItemViewSetAndGetAnchoringDurationP();
void ItemViewScrollToItemP();
void ItemViewSetAndGetRefreshIntervalP();
void ItemViewGetItemIdP();
void ItemViewInsertItemP();
void ItemViewInsertItemsP();
void ItemViewRemoveItemP();
void ItemViewRemoveItemsP();
void ItemViewReplaceItemP();
void ItemViewReplaceItemsP();
void ItemViewSetAndGetItemsParentOriginP();
void ItemViewSetAndGetItemsAnchorPointP();
void ItemViewGetItemsRangeP();
void ItemViewLayoutActivatedSignalP();


namespace
{
  enum TEST_CASES_LIST_ITEM_VIEW
  {
    ITEM_VIEW_CONSTRUCTOR_P,
    ITEM_VIEW_NEW_P,
    ITEM_VIEW_COPY_CONSTRUCTOR_P,
    ITEM_VIEW_OPERATOR_ASSIGNMENT_P,
    ITEM_VIEW_DOWNCAST_P,
    ITEM_VIEW_DOWNCAST_N,
    ITEM_VIEW_GET_ADD_LAYOUT_COUNT_P,
    ITEM_VIEW_GET_LAYOUT_P,
    ITEM_VIEW_REMOVE_LAYOUT_P,
    ITEM_VIEW_GET_ACTIVATE_DEACTIVATE_LAYOUT_P,
    ITEM_VIEW_GET_ITEM_ID_P,
    ITEM_VIEW_INSERT_ITEM_P,
    ITEM_VIEW_REPLACE_ITEM_P,
    ITEM_VIEW_REMOVE_ITEM_P,
    ITEM_VIEW_INSERT_ITEMS_P,
    ITEM_VIEW_REPLACE_ITEMS_P,
    ITEM_VIEW_REMOVE_ITEMS_P,
    ITEM_VIEW_GET_CURRENT_LAYOUT_POSITION_P,
    ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_SPEED_P,
    ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_DISTANCE_P,
    ITEM_VIEW_SET_AND_GET_REFRESH_INTERVAL_P,
    ITEM_VIEW_SET_AND_GET_ANCHORING_P,
    ITEM_VIEW_SET_AND_GET_ANCHORING_DURATION_P,
    ITEM_VIEW_SET_AND_GET_MOUSE_WHEEL_SCROLL_DISTANCE_STEP_P,
    ITEM_VIEW_SET_AND_GET_ITEMS_ANCHOR_POINT_P,
    ITEM_VIEW_SET_AND_GET_ITEMS_PARENT_ORIGIN_P,
    ITEM_LAYOUT_ACTIVATED_SIGNAL_P,
    ITEM_VIEW_SCROLL_TO_ITEM_P,
    ITEM_VIEW_GET_ITEMS_RANGE_P,
  };

  struct ItemView_TestApp : public ConnectionTracker
  {
    ItemView_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &ItemView_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &ItemView_TestApp::Tick );
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
        case ITEM_VIEW_CONSTRUCTOR_P:
          ItemViewConstructorP();
          break;

        case ITEM_VIEW_NEW_P:
          ItemViewNewP();
          break;

        case ITEM_VIEW_COPY_CONSTRUCTOR_P:
          ItemViewCopyConstructorP();
          break;

        case ITEM_VIEW_OPERATOR_ASSIGNMENT_P:
          ItemViewOperatorAssignmentP();
          break;

        case ITEM_VIEW_DOWNCAST_P:
          ItemViewDownCastP();
          break;

        case ITEM_VIEW_DOWNCAST_N:
          ItemViewDownCastN();
          break;

        case ITEM_VIEW_GET_ADD_LAYOUT_COUNT_P:
          ItemViewGetAddLayoutCountP();
          break;

        case ITEM_VIEW_GET_LAYOUT_P:
          ItemViewGetLayoutP();
          break;

        case ITEM_VIEW_REMOVE_LAYOUT_P:
          ItemViewRemoveLayoutP();
          break;

        case ITEM_VIEW_GET_ACTIVATE_DEACTIVATE_LAYOUT_P:
          ItemViewGetActivateDeactivateLayoutP();
          break;

        case ITEM_VIEW_GET_CURRENT_LAYOUT_POSITION_P:
          ItemViewGetCurrentLayoutPositionP();
          break;

        case ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_SPEED_P:
          ItemViewSetAndGetMinimumSwipeSpeedP();
          break;

        case ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_DISTANCE_P:
          ItemViewSetAndGetMinimumSwipeDistanceP();
          break;

        case ITEM_VIEW_SET_AND_GET_MOUSE_WHEEL_SCROLL_DISTANCE_STEP_P:
          ItemViewSetAndGetMouseWheelScrollDistanceStepP();
          break;

        case ITEM_VIEW_SET_AND_GET_ANCHORING_P:
          ItemViewSetAndGetAnchoringP();
          break;

        case ITEM_VIEW_SET_AND_GET_ANCHORING_DURATION_P:
          ItemViewSetAndGetAnchoringDurationP();
          break;

        case ITEM_VIEW_SCROLL_TO_ITEM_P:
          ItemViewScrollToItemP();
          break;

        case ITEM_VIEW_SET_AND_GET_REFRESH_INTERVAL_P:
          ItemViewSetAndGetRefreshIntervalP();
          break;

        case ITEM_VIEW_GET_ITEM_ID_P:
          ItemViewGetItemIdP();
          break;

        case ITEM_VIEW_INSERT_ITEM_P:
          ItemViewInsertItemP();
          break;

        case ITEM_VIEW_INSERT_ITEMS_P:
          ItemViewInsertItemsP();
          break;

        case ITEM_VIEW_REPLACE_ITEM_P:
          ItemViewReplaceItemP();
          break;

        case ITEM_VIEW_REPLACE_ITEMS_P:
          ItemViewReplaceItemsP();
          break;

        case ITEM_VIEW_REMOVE_ITEM_P:
          ItemViewRemoveItemP();
          break;

        case ITEM_VIEW_REMOVE_ITEMS_P:
          ItemViewRemoveItemsP();
          break;

        case ITEM_VIEW_SET_AND_GET_ITEMS_ANCHOR_POINT_P:
          ItemViewSetAndGetItemsAnchorPointP();
          break;

        case ITEM_VIEW_SET_AND_GET_ITEMS_PARENT_ORIGIN_P:
          ItemViewSetAndGetItemsParentOriginP();
          break;

        case ITEM_VIEW_GET_ITEMS_RANGE_P:
          ItemViewGetItemsRangeP();
          break;

        case ITEM_LAYOUT_ACTIVATED_SIGNAL_P:
          ItemViewLayoutActivatedSignalP();
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

void ItemViewConstructorP(void)
{
  ItemView ItemView;
  DALI_CHECK_FAIL(ItemView,  "ItemView Default Contructor is failed");

  DaliLog::PrintPass();
}


void ItemViewNewP()
{
  ItemViewFactory itemFactory ;
  ItemView itemViewConst ;

  itemViewConst = ItemView::New(itemFactory);
  DALI_CHECK_FAIL(!itemViewConst,  "Itemview::New() is failed.");

  DaliLog::PrintPass();
}

void ItemViewCopyConstructorP()
{
  ItemViewFactory itemFactory ;
  ItemView itemViewConst ;

  itemViewConst = ItemView::New(itemFactory);
  DALI_CHECK_FAIL(!itemViewConst,  "Itemview::New() is failed.");

  ItemView itemviewConstructor (itemViewConst) ;
  DALI_CHECK_FAIL( itemviewConstructor != itemViewConst,  "Itemview copy constructor is failed.");

  DaliLog::PrintPass();
}

void ItemViewOperatorAssignmentP()
{
  ItemViewFactory itemFactory ;
  ItemView itemViewConst ;

  itemViewConst = ItemView::New(itemFactory);
  DALI_CHECK_FAIL(!itemViewConst,  "Itemview::New() is failed.");

  ItemView itemviewConstructor (itemViewConst) ;
  DALI_CHECK_FAIL( itemviewConstructor != itemViewConst,  "Itemview copy constructor is failed.");

  ItemView  OperatorItemView  = itemViewConst ;

  DALI_CHECK_FAIL(OperatorItemView != itemViewConst,  "Itemview assignment is failed.");

  DaliLog::PrintPass();
}

void ItemViewDownCastP()
{
  ItemViewFactory itemFactory;
  const ItemView itemViewConst = ItemView::New(itemFactory);
  DALI_CHECK_FAIL(!itemViewConst,  "Itemview::New() is failed.");
  ItemView itemView(itemViewConst);

  BaseHandle handle(itemView);

  ItemView newItemView = ItemView::DownCast( handle );

  DALI_CHECK_FAIL(!itemView,  "The itemitemView does not exist.");
  DALI_CHECK_FAIL(newItemView != itemView,  "DownCast failed, the newitem should be equal to itemitemView.");

  DaliLog::PrintPass();
}

void ItemViewDownCastN()
{
  BaseHandle unInitializedObject;

  ItemView ItemView1 = ItemView::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(ItemView1, "ItemView handle is not empty." );

  ItemView ItemView2 = DownCast< ItemView >( unInitializedObject );
  DALI_CHECK_FAIL(ItemView2, "ItemView handle is not empty." );

  DaliLog::PrintPass();

}

void ItemViewGetAddLayoutCountP()
{
  unsigned int  uLayoutCount = 0u ;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory) )
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);

  uLayoutCount = itemView.GetLayoutCount();

  DALI_CHECK_FAIL(uLayoutCount != ITEM_VIEW_LAYOUT_COUNT,  "Number of Layout is mismatched ");
  itemView.RemoveLayout(uLayoutCount-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewGetLayoutP()
{
  unsigned int uSet=0u ;
  ItemLayoutPtr itemLayout;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  itemLayout = itemView.GetLayout(uSet);

  DALI_CHECK_FAIL(itemLayout!= gridLayout,  "Number of Layout is mismatched ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}


void ItemViewRemoveLayoutP()
{
  unsigned int uInitLayout = 0u, uPreLayoutCount = 0u, uNextLayoutCount = 0u;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  uInitLayout= itemView.GetLayoutCount();
  itemView.AddLayout(*gridLayout);
  uPreLayoutCount= itemView.GetLayoutCount();

  itemView.RemoveLayout(uPreLayoutCount-ITEM_VIEW_LAYOUT_COUNT);

  uNextLayoutCount = itemView.GetLayoutCount();
  DALI_CHECK_FAIL(uInitLayout != uNextLayoutCount,  "Layout is not removed ");

  DaliLog::PrintPass();
}


void ItemViewGetActivateDeactivateLayoutP()
{
  unsigned int  uLayOutIndex = 0u ;
  float fDurationSeconds = 0.5f ;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);

  DALI_CHECK_FAIL(itemView.GetActiveLayout() != NULL,  "There should be no active layout at the moment ");

  Stage::GetCurrent().Add( itemView );

  // Connect the layout activated signal
  itemView.LayoutActivatedSignal().Connect( &ItemViewOnLayoutActivated );

  gItemViewOnLayoutActivatedCalled = false;

  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());

  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  DALI_CHECK_FAIL(itemView.GetActiveLayout() != gridLayout,  "There  layout at the moment is not active ");
  DALI_CHECK_FAIL( gItemViewOnLayoutActivatedCalled != true, "LayoutActivatedSignal is failed to call the ItemViewOnLayoutActivated" );

  itemView.DeactivateCurrentLayout();

  DALI_CHECK_FAIL(itemView.GetActiveLayout() != NULL,  "There should be no active layout at the moment ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewGetCurrentLayoutPositionP()
{
  float layoutPosition = 0.0f;
  const unsigned int  LAYOUTINDEX = 0u , ITEMID = 9u  ;
  float fDurationSeconds  = 0.0f ;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");
  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(LAYOUTINDEX, vecStageSize, fDurationSeconds);

  layoutPosition = itemView.GetCurrentLayoutPosition(ITEMID);
  // Check the current layout position for the 10th items is 9.0f
  DALI_CHECK_FAIL(layoutPosition != (float) ITEMID ,  "The current layout position for the 10th items should be 9.0f");
  unsigned int uInitLayout = itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewSetAndGetMinimumSwipeSpeedP()
{
  float fSwipeSpeed = 0.0f;

  ItemView itemView ;
  ItemViewFactory itemFactory;
  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetMinimumSwipeSpeed(SWIPE_SPEED);

  fSwipeSpeed = itemView.GetMinimumSwipeSpeed();

  DALI_CHECK_FAIL(fSwipeSpeed != SWIPE_SPEED,  "The minimum swipe speed not get the value as expected:");

  DaliLog::PrintPass();
}

void ItemViewSetAndGetMinimumSwipeDistanceP()
{
  float fSwipeDistance = 0.0f;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetMinimumSwipeDistance(SWIPE_DISTANCE);

  fSwipeDistance = itemView.GetMinimumSwipeDistance();

  DALI_CHECK_FAIL(fSwipeDistance != SWIPE_DISTANCE,  "The minimum swipe distance not get the value as expected.");

  DaliLog::PrintPass();
}

void ItemViewSetAndGetMouseWheelScrollDistanceStepP()
{
  float fScrollDistance = 0.0f;

  ItemView itemView ;
  ItemViewFactory itemFactory;
  if(!ItemViewInit( itemView , itemFactory ))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetWheelScrollDistanceStep(SCROLL_DISTANCE);

  fScrollDistance = itemView.GetWheelScrollDistanceStep();

  DALI_CHECK_FAIL(fScrollDistance != SCROLL_DISTANCE,  "The step of scroll distance should be 100.");

  DaliLog::PrintPass();
}

void ItemViewSetAndGetAnchoringP()
{
  bool bEnable = true;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory ))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetAnchoring(false);

  bEnable = itemView.GetAnchoring();

  DALI_CHECK_FAIL(bEnable != false,  "anchor animation should be disabled.");

  DaliLog::PrintPass();
}

void ItemViewSetAndGetAnchoringDurationP()
{
  float fDuration = 0.0f;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetAnchoringDuration(ANCHOR_DURATION);

  fDuration = itemView.GetAnchoringDuration();

  DALI_CHECK_FAIL(fDuration != ANCHOR_DURATION,  "anchor animation duration should be 1.5f.");

  DaliLog::PrintPass();
}

void ItemViewScrollToItemP()
{
  unsigned int  uLayOutIndex = 0u ;
  Vector3 vec3SetLayout(480.0f, 800.0f, 0.0f);
  float fDurationSeconds = 0.0f ;
  ItemView itemView ;
  ItemViewFactory itemFactory;
  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  itemView.SetName("view actor");
  itemView.SetSize(vec3SetLayout);
  DALI_CHECK_FAIL(itemView.GetActiveLayout() != NULL,  "There should be no active layout at the moment ");

  Stage::GetCurrent().Add( itemView );
  gridLayout->SetOrientation(ControlOrientation::Up);
  // Connect the layout activated signal
  itemView.LayoutActivatedSignal().Connect( &ItemViewOnLayoutActivated );

  gItemViewOnLayoutActivatedCalled = false;

  itemView.ActivateLayout(uLayOutIndex, vec3SetLayout, fDurationSeconds);

  // Confirm: we have actors in the view.
  std::vector<unsigned int> indices;
  for(unsigned int i = 0; i < 10; i++)
  {
    Actor testActor = itemView.GetItem(i);
    if (testActor)
    {
      indices.push_back(i);
    }
  }

  try
  {
    if (!indices.empty())
    {
      const unsigned int firstTargetIndex = indices[indices.size()-1];
      // scroll to last item
      itemView.ScrollToItem(firstTargetIndex, 0.00f);

      std::size_t moveCount = 0;
      for(std::size_t i = 0; i < indices.size(); i++)
      {
        float layoutPosBefore = itemView.GetCurrentLayoutPosition(i);
        itemView.ScrollToItem(indices[i], 0.0f);
        float layoutPosAfter = itemView.GetCurrentLayoutPosition(i);

        if (fabs(layoutPosBefore-layoutPosAfter) <= FLT_EPSILON)
        {
          ++moveCount;
        }
      }

      DALI_CHECK_FAIL((moveCount != indices.size()),"ScrollTo Item failed to return expected value");
    }
  }
  catch(...)
  {
    LOG_E(" unanonymous exception occurred");
    test_return_value=TC_FAIL;
    return;
  }

  Stage::GetCurrent().Remove( itemView );
  DaliLog::PrintPass();
}

void ItemViewSetAndGetRefreshIntervalP()
{
  float fInterval = 0.0f;

  ItemView itemView ;
  ItemViewFactory itemFactory;
  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetRefreshInterval(REFRESH_INTERVAL);

  itemView.Refresh();

  fInterval = itemView.GetRefreshInterval();

  DALI_CHECK_FAIL(fInterval != REFRESH_INTERVAL,  "The interval between refreshes not get the value as expected");

  DaliLog::PrintPass();
}

void ItemViewGetItemIdP()
{
  unsigned int  uLayOutIndex = 0u , uItemNumber = 2u ;
  float fDurationSeconds = 0.5f ;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor itemActor = itemView.GetItem(uItemNumber);

  ItemId itemId = itemView.GetItemId(itemActor);

  DALI_CHECK_FAIL(itemId != uItemNumber,  "Item id is not correct ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewInsertItemP()
{
  unsigned int uLayOutIndex = 0u , uItemId = 2u  ;
  float fDurationSeconds  = 0.5f ;
  int nWithItem, nWithoutItem = 0;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor itemActorTwo = itemView.GetItem(uItemId);
  ItemId id = itemView.GetItemId( itemActorTwo );
  Actor newActor = itemFactory.NewItem( ITEM_ID );

  nWithoutItem = ItemViewDescendentCount(itemView);

  itemView.InsertItem( Item(id,newActor), fDurationSeconds );

  nWithItem = ItemViewDescendentCount(itemView);

  DALI_CHECK_FAIL(nWithItem < nWithoutItem,  "Item is not inserted properly ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}


void ItemViewReplaceItemP()
{
  unsigned int  uLayOutIndex = 0 , uItemId = 2 ;
  int nSet=1 ;
  float fDurationSeconds  = 0.5f ;
  int nWithItem, nWithoutItem = -1;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor itemActorTwo = itemView.GetItem(uItemId);
  ItemId id = itemView.GetItemId( itemActorTwo );
  Actor newActor = itemFactory.NewItem( ITEM_ID );

  nWithoutItem = ItemViewDescendentCount(itemView);

  itemView.InsertItem( Item(id,newActor), fDurationSeconds );

  itemView.ReplaceItem( Item(id,newActor), fDurationSeconds );

  nWithItem = ItemViewDescendentCount(itemView);

  DALI_CHECK_FAIL(nWithItem < (nWithoutItem-nSet),  "Item is not replaced properly ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}


void ItemViewRemoveItemP()
{
  unsigned int uLayOutIndex = 0 , uItemId = 2;
  float fDurationSeconds  = 0.5f , fDuration = 0.5f ;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor itemActorTwo = itemView.GetItem(uItemId);
  Actor itemActorThree = itemView.GetItem(uItemId+1);

  itemView.RemoveItem(uItemId, fDurationSeconds - fDuration );

  Actor newitemActorTwo = itemView.GetItem( uItemId );
  ItemId itemId = itemView.GetItemId(newitemActorTwo);

  DALI_CHECK_FAIL(itemId != uItemId,  "Item is id should be 2  ");
  DALI_CHECK_FAIL(itemActorTwo == newitemActorTwo,  "original item with item ID 2 was not deleted  ");
  DALI_CHECK_FAIL(itemActorThree != newitemActorTwo,  "Item ID 2 should represent the original item with ID 3. It is not correct ");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewInsertItemsP()
{
  unsigned int uLayOutIndex = 0 ;
  float fDurationSeconds  = 0.5f ;
  int nWithItem = 0 , nWithoutItem = 0;
  ItemContainer itemContainerInsertList;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  nWithoutItem = ItemViewDescendentCount(itemView);

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor newActor = itemFactory.NewItem( ITEM_ID );

  for( unsigned int i = 0u; i < itemView.GetChildCount(); ++i )
  {
    Actor child = itemView.GetChildAt( i );
    itemContainerInsertList.push_back(Item(itemView.GetItemId(child), newActor));
  }

  itemView.InsertItems( itemContainerInsertList, fDurationSeconds );

  nWithItem = ItemViewDescendentCount(itemView);

  DALI_CHECK_FAIL(nWithItem < nWithoutItem,  "Item count is not properly get.");
  unsigned int uInitLayout = itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}


void ItemViewReplaceItemsP()
{
  unsigned int   uLayOutIndex = 0 ;
  int  nSet = 0;
  float fDurationSeconds  = 0.5f ;
  int nWithItem = 0 , nWithoutItem = 0;
  ItemContainer itemContainerReplaceList;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  nWithoutItem = ItemViewDescendentCount(itemView);

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  Actor newActor = itemFactory.NewItem( ITEM_ID );

  for( unsigned int i = 0u; i < itemView.GetChildCount(); ++i )
  {
    Actor child = itemView.GetChildAt( i );
    itemContainerReplaceList.push_back( Item(itemView.GetItemId(child), newActor));
  }

  itemView.ReplaceItems( itemContainerReplaceList,fDurationSeconds);

  nWithItem = ItemViewDescendentCount(itemView);

  DALI_CHECK_FAIL(nWithItem < (nWithoutItem-nSet),  "Item count is not properly get.");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewRemoveItemsP()
{
  float fDurationSeconds  = 0.5f ;
  unsigned int uLayOutIndex = 0 ;
  int nInitItem = 0 , nLaterItem = 0;
  ItemIdContainer itemContainerRemoveList;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  nInitItem = ItemViewDescendentCount(itemView);

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  ItemRange itemRange(0, 0);

  itemView.GetItemsRange(itemRange);

  DALI_CHECK_FAIL(! itemRange.Within(0) , "GetItemsRange failed to return expected value" ) ;

  Actor newActor = itemFactory.NewItem( ITEM_ID );

  for( unsigned int i = 0u; i < itemView.GetChildCount(); ++i )
  {
    Actor child = itemView.GetChildAt( i );
    itemContainerRemoveList.push_back( itemView.GetItemId(child) );
  }
  DALI_CHECK_FAIL( itemContainerRemoveList.empty(), "Container remove list is empty" );

  itemView.RemoveItems( itemContainerRemoveList, fDurationSeconds );

  nLaterItem = ItemViewDescendentCount(itemView);

  DALI_CHECK_FAIL(nInitItem != nLaterItem,  "Item count is not properly get.");
  unsigned int uInitLayout= itemView.GetLayoutCount();
  itemView.RemoveLayout(uInitLayout-ITEM_VIEW_LAYOUT_COUNT);

  DaliLog::PrintPass();
}

void ItemViewSetAndGetItemsAnchorPointP()
{
  Vector3 vecAnchorPoint = AnchorPoint::TOP_LEFT;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetItemsAnchorPoint( AnchorPoint::CENTER );

  vecAnchorPoint = itemView.GetItemsAnchorPoint();

  DALI_CHECK_FAIL(vecAnchorPoint != AnchorPoint::CENTER,  "The anchor point of the items should be in center but it is failed.");

  DaliLog::PrintPass();
}

void ItemViewSetAndGetItemsParentOriginP()
{
  Vector3 vecParentOrigin = ParentOrigin::TOP_LEFT;

  ItemView itemView ;
  ItemViewFactory itemFactory;
  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  itemView.SetItemsParentOrigin(ParentOrigin::CENTER);

  vecParentOrigin = itemView.GetItemsParentOrigin();

  DALI_CHECK_FAIL(vecParentOrigin != ParentOrigin::CENTER,  "The anchor point of the items should be in center.");

  DaliLog::PrintPass();
}

void ItemViewGetItemsRangeP()
{
  float fDurationSeconds  = 0.5f ;
  unsigned int uLayOutIndex = 0 ;
  ItemIdContainer itemContainerRemoveList;
  ItemViewFactory itemFactory;
  ItemView itemView ;

  if(!ItemViewInit(itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);
  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());
  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  ItemRange itemRange(0, 0);
  itemView.GetItemsRange(itemRange);
  DALI_CHECK_FAIL(! itemRange.Within(0) , "GetItemsRange failed to return expected value" ) ;

  DaliLog::PrintPass();
}

void ItemViewLayoutActivatedSignalP()
{
  unsigned int  uLayOutIndex = 0u ;
  float fDurationSeconds = 0.5f ;
  ItemView itemView ;
  ItemViewFactory itemFactory;

  if(!ItemViewInit( itemView , itemFactory))
  {
    test_return_value=TC_FAIL;
    return;
  }

  ItemLayoutPtr gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FAIL(!gridLayout,  "GridLayout::New() is failed.");

  itemView.AddLayout(*gridLayout);

  DALI_CHECK_FAIL(itemView.GetActiveLayout() != NULL,  "There should be no active layout at the moment ");

  Stage::GetCurrent().Add( itemView );

  // Connect the layout activated signal
  itemView.LayoutActivatedSignal().Connect( &ItemViewOnLayoutActivated );

  gItemViewOnLayoutActivatedCalled = false;

  Vector3 vecStageSize(Dali::Stage::GetCurrent().GetSize());

  itemView.ActivateLayout(uLayOutIndex, vecStageSize, fDurationSeconds);

  DALI_CHECK_FAIL(itemView.GetActiveLayout() != gridLayout,  "There  layout at the moment is not active ");
  DALI_CHECK_FAIL( gItemViewOnLayoutActivatedCalled != true, "LayoutActivatedSignal is failed to call the ItemViewOnLayoutActivated" );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/

/**
 * @testcase            UtcDaliItemViewConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object for PageTurnPortraitView
 */

int UtcDaliItemViewConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliItemViewNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliItemViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliItemViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliItemViewDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliItemViewDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewGetAddLayoutCountP
 * @since_tizen         2.4
 * @description         Query the number of layouts.
 */

int UtcDaliItemViewGetAddLayoutCountP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_ADD_LAYOUT_COUNT_P);
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliItemViewGetLayoutP
 * @since_tizen         2.4
 * @description         Retrieves the added layout
 */

int UtcDaliItemViewGetLayoutP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_LAYOUT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewRemoveLayoutP
 * @since_tizen         2.4
 * @description         Remove a layout.
 */

int UtcDaliItemViewRemoveLayoutP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_REMOVE_LAYOUT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewGetActivateDeactivateLayoutP
 * @since_tizen         2.4
 * @description         Activate the grid layout so that the items will be created and added to ItemView.
 */

int UtcDaliItemViewGetActivateDeactivateLayoutP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_ACTIVATE_DEACTIVATE_LAYOUT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewGetCurrentLayoutPositionP
 * @since_tizen         2.4
 * @description         Retrieve the current layout-position of an item in the ItemView.
 */

int UtcDaliItemViewGetCurrentLayoutPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_CURRENT_LAYOUT_POSITION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetMinimumSwipeSpeedP
 * @since_tizen         2.4
 * @description         Set and get the minimum swipe speed in pixels per second.
 */

int UtcDaliItemViewSetAndGetMinimumSwipeSpeedP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_SPEED_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetMinimumSwipeDistanceP
 * @since_tizen         2.4
 * @description         Set and get the minimum swipe distance in pixels per second.
 */

int UtcDaliItemViewSetAndGetMinimumSwipeDistanceP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_MINIMUM_SWIPE_DISTANCE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetMouseWheelScrollDistanceStepP
 * @since_tizen         2.4
 * @description         Set and get the step of scroll distance.
 */

int UtcDaliItemViewSetAndGetMouseWheelScrollDistanceStepP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_MOUSE_WHEEL_SCROLL_DISTANCE_STEP_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetAnchoringP
 * @since_tizen         2.4
 * @description         Set and get the anchor animation status.
 */

int UtcDaliItemViewSetAndGetAnchoringP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_ANCHORING_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetAnchoringDurationP
 * @since_tizen         2.4
 * @description         Set and get the duration of the anchor animation .
 */

int UtcDaliItemViewSetAndGetAnchoringDurationP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_ANCHORING_DURATION_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewScrollToItemP
 * @since_tizen         2.4
 * @description         To Check ScrolToItem api works properly.
 */

int UtcDaliItemViewScrollToItemP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SCROLL_TO_ITEM_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetRefreshIntervalP
 * @since_tizen         2.4
 * @description         Set and get the interval between refreshes.
 */

int UtcDaliItemViewSetAndGetRefreshIntervalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_REFRESH_INTERVAL_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewGetItemIdP
 * @since_tizen         2.4
 * @description         Given the Item ID,returns the accompanying actor.
 */

int UtcDaliItemViewGetItemIdP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_ITEM_ID_P);
  application.MainLoop();

  return test_return_value;
}

//& purpose: Remove a layout.
/**
 * @testcase            UtcDaliItemViewInsertItemP
 * @since_tizen         2.4
 * @description         Insert an item.
 */

int UtcDaliItemViewInsertItemP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_INSERT_ITEM_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewReplaceItemP
 * @since_tizen         2.4
 * @description         Replace an item.
 */

int UtcDaliItemViewReplaceItemP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_REPLACE_ITEM_P);
  application.MainLoop();

  return test_return_value;
}

//& purpose: Remove the item with ID.
//& purpose: Remove a layout.
/**
 * @testcase            UtcDaliItemViewRemoveItemP
 * @since_tizen         2.4
 * @description
 */

int UtcDaliItemViewRemoveItemP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_REMOVE_ITEM_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewInsertItemsP
 * @since_tizen         2.4
 * @description         Insert a set of items.
 */

int UtcDaliItemViewInsertItemsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_INSERT_ITEMS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewReplaceItemsP
 * @since_tizen         2.4
 * @description         Replace a set of items.
 */

int UtcDaliItemViewReplaceItemsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_REPLACE_ITEMS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewRemoveItemsP
 * @since_tizen         2.4
 * @description         remove a set of items.
 */

int UtcDaliItemViewRemoveItemsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_REMOVE_ITEMS_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetItemsAnchorPointP
 * @since_tizen         2.4
 * @description         Set and get the anchor point of the items.
 */

int UtcDaliItemViewSetAndGetItemsAnchorPointP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_ITEMS_ANCHOR_POINT_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewSetAndGetItemsParentOriginP
 * @since_tizen         2.4
 * @description         Set and get the parent origin of the items.
 */

int UtcDaliItemViewSetAndGetItemsParentOriginP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_SET_AND_GET_ITEMS_PARENT_ORIGIN_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewGetItemsRangeP
 * @since_tizen         2.4
 * @description         Get Range of Item
 */

int UtcDaliItemViewGetItemsRangeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_VIEW_GET_ITEMS_RANGE_P);
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliItemViewLayoutActivatedSignalP
 * @since_tizen         2.4
 * @description         Emitts signal when layout is activated
 */

int UtcDaliItemViewLayoutActivatedSignalP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  ItemView_TestApp testApp( application, ITEM_LAYOUT_ACTIVATED_SIGNAL_P);
  application.MainLoop();

  return test_return_value;
}
