#include "utc-dali-table-view-common.h"

//& set: TableView
extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

TableView gTableView;                                                   /**TableView instance*/
int gRenderCountTableView;                                              /**Render count*/
Actor gTableActorFirst, gTableActorSecond, gTableActorThird;            /**Table view actors*/

/**Initial and final position of actors attached with TableView **/
Vector3 gVec3ActorOnePositionInit;
Vector3 gVec3ActorTwoPositionInit;
Vector3 gVec3ActorThreePositionInit;
Vector3 gVec3ActorOnePositionFinal;
Vector3 gVec3ActorTwoPositionFinal;
Vector3 gVec3ActorThreePositionFinal;

/**Initial and final padding value*/
Size gSizeInitPadding(0.0f, 0.0f);
Size gSizeIFinalPadding(20.0f, 30.0f);

/**
 * @function            utc_Dali_TableView_startup
 * @description         Called before each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TableView_startup(void)
{
  test_return_value=0;
  gRenderCountTableView = 0;
}

/**
 * @function            utc_Dali_TableView_cleanup
 * @description         Called after each test
 * @parameter           NA
 * @return              NA
 */

void utc_Dali_TableView_cleanup(void)
{

}

void TableViewConstructorP();
void TableViewNewP();
void TableViewCopyConstructorP();
void TableViewOperatorAssignmentP();
void TableViewDownCastP();
void TableViewDownCastN();
void TableViewAddGetChildAtP();
void TableViewRemoveChildP();
void TableViewFindChildPositionP();
void TableViewInsertRowColumnP();
void TableViewDeleteColumnP();
void TableViewDeleteRowP();
void TableViewResizeP();
void TableViewSetGetCellPaddingP();
void TableViewSetGetIsFitFixedWidthHeightP();
void TableViewSetGetRelativeWidthHeightP();
void TableViewGetRowsColumnsP();
void TableViewSetCellAlignmentP();
void VTTableViewSetGetRelativeWidthHeight001();
void VTTableViewSetGetRelativeWidthHeight002();
void VTTableViewSetGetFitFixedWidthHeight001();
void VTTableViewSetGetFitFixedWidthHeight002();
void VTTableViewSetGetFitFixedWidthHeight003();
void VTTableViewSetGetCellPadding001();
void VTTableViewSetGetCellPadding002();

namespace
{
  enum TEST_CASES_LIST_TABLE_VIEW
  {
    TABLE_VIEW_CONSTRUCTOR_P,
    TABLE_VIEW_NEW_P,
    TABLE_VIEW_COPY_CONSTRUCTOR_P,
    TABLE_VIEW_OPERATOR_ASSIGNMENT_P,
    TABLE_VIEW_DOWNCAST_P,
    TABLE_VIEW_DOWNCAST_N,
    TABLE_VIEW_ADD_GET_CHILD_AT_P,
    TABLE_VIEW_REMOVE_CHILD_P,
    TABLE_VIEW_FIND_CHILD_POSITION_P,
    TABLE_VIEW_INSERT_ROW_COLUMN_P,
    TABLE_VIEW_DELETE_COLUMN_P,
    TABLE_VIEW_DELETE_ROW_P,
    TABLE_VIEW_RESIZE_P,
    TABLE_VIEW_SET_GET_CELL_PADDING_P,
    TABLE_VIEW_SET_GET_IS_FIT_FIXED_WIDTH_HEIGHT_P,
    TABLE_VIEW_SET_GET_RELATIVE_WIDTH_HEIGHT_P,
    TABLE_VIEW_GET_ROWS_COLUMNS_P,
    TABLE_VIEW_SET_CELL_ALIGNMENT_P
  };

  struct TableView_TestApp : public ConnectionTracker
  {
    TableView_TestApp( Application& app, int test_case )
      : mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &TableView_TestApp::OnInit );
    }

    void OnInit(Application& app)
    {
      ExcuteTest();
      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &TableView_TestApp::Tick );
      mTimer.Start();
    }

    bool Tick()
    {
      if(test_return_value == TC_FAIL)
      {
        mTimer.Stop();
        mApplication.Quit();
        return true;
      }
      VerdictTest();
      if(test_return_value == TC_FAIL)
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
        case TABLE_VIEW_CONSTRUCTOR_P:
          TableViewConstructorP();
          break;

        case TABLE_VIEW_NEW_P:
          TableViewNewP();
          break;

        case TABLE_VIEW_COPY_CONSTRUCTOR_P:
          TableViewCopyConstructorP();
          break;

        case TABLE_VIEW_OPERATOR_ASSIGNMENT_P:
          TableViewOperatorAssignmentP();
          break;

        case TABLE_VIEW_DOWNCAST_P:
          TableViewDownCastP();
          break;

        case TABLE_VIEW_DOWNCAST_N:
          TableViewDownCastN();
          break;

        case TABLE_VIEW_ADD_GET_CHILD_AT_P:
          TableViewAddGetChildAtP();
          break;

        case TABLE_VIEW_REMOVE_CHILD_P:
          TableViewRemoveChildP();
          break;

        case TABLE_VIEW_FIND_CHILD_POSITION_P:
          TableViewFindChildPositionP();
          break;

        case TABLE_VIEW_INSERT_ROW_COLUMN_P:
          TableViewInsertRowColumnP();
          break;

        case TABLE_VIEW_DELETE_COLUMN_P:
          TableViewDeleteColumnP();
          break;

        case TABLE_VIEW_DELETE_ROW_P:
          TableViewDeleteRowP();
          break;

        case TABLE_VIEW_RESIZE_P:
          TableViewResizeP();
          break;

        case TABLE_VIEW_SET_GET_CELL_PADDING_P:
          TableViewSetGetCellPaddingP();
          break;

        case TABLE_VIEW_SET_GET_IS_FIT_FIXED_WIDTH_HEIGHT_P:
          TableViewSetGetIsFitFixedWidthHeightP();
          break;

        case TABLE_VIEW_SET_GET_RELATIVE_WIDTH_HEIGHT_P:
          TableViewSetGetRelativeWidthHeightP();
          break;

        case TABLE_VIEW_GET_ROWS_COLUMNS_P:
          TableViewGetRowsColumnsP();
          break;

        case TABLE_VIEW_SET_CELL_ALIGNMENT_P:
          TableViewSetCellAlignmentP();
          break;


      }
    }

    void VerdictTest()
    {
      switch (mTestCase)
      {
        case TABLE_VIEW_SET_GET_RELATIVE_WIDTH_HEIGHT_P:
          switch(gRenderCountTableView)
          {
            case 0:
              VTTableViewSetGetRelativeWidthHeight001();
              gRenderCountTableView++;
              break;

            case 1:
              VTTableViewSetGetRelativeWidthHeight002();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case TABLE_VIEW_SET_GET_IS_FIT_FIXED_WIDTH_HEIGHT_P:
          switch(gRenderCountTableView)
          {
            case 0:
              VTTableViewSetGetFitFixedWidthHeight001();
              gRenderCountTableView++;
              break;

            case 1:
              VTTableViewSetGetFitFixedWidthHeight002();
              gRenderCountTableView++;
              break;

            case 2:
              VTTableViewSetGetFitFixedWidthHeight003();
              mTimer.Stop();
              mApplication.Quit();
              break;
          }
          break;

        case TABLE_VIEW_SET_GET_CELL_PADDING_P:
          switch(gRenderCountTableView)
          {
            case 0:
              VTTableViewSetGetCellPadding001();
              gRenderCountTableView++;
              break;

            case 1:
              VTTableViewSetGetCellPadding002();
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

void TableViewConstructorP(void)
{
  TableView tableView;
  DALI_CHECK_FAIL(tableView,  "TableView Default Contructor is failed");

  DaliLog::PrintPass();
}


void TableViewNewP()
{
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  DaliLog::PrintPass();
}

void TableViewCopyConstructorP()
{
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  TableView tableView1(tableView);
  DALI_CHECK_FAIL(!tableView1,  "TableView copy constructor is failed.");

  DaliLog::PrintPass();
}

void TableViewOperatorAssignmentP()
{
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  TableView tableView1;
  tableView1 = tableView;
  DALI_CHECK_FAIL(tableView1 != tableView,  "TableView Assignment Operator is failed");

  DaliLog::PrintPass();
}

void TableViewDownCastP()
{
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  Handle handleView;
  handleView = tableView;
  TableView downCastTableView = TableView::DownCast( handleView );
  DALI_CHECK_FAIL(!downCastTableView,  "TableView::DownCast() is failed.");

  DaliLog::PrintPass();
}

void TableViewDownCastN()
{
  BaseHandle unInitializedObject;

  TableView tableView1 = TableView::DownCast( unInitializedObject );
  DALI_CHECK_FAIL(tableView1, "TableView handle is not empty." );

  TableView tableView2 = DownCast< TableView >( unInitializedObject );
  DALI_CHECK_FAIL(tableView2, "TableView handle is not empty." );

  DaliLog::PrintPass();

}

void TableViewAddGetChildAtP()
{
  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void TableViewRemoveChildP()
{
  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }

  if(!TableViewRemoveChildActor(tableView))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}


void TableViewFindChildPositionP()
{
  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }

  if(!TableViewRemoveChildActor(tableView))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}

void TableViewInsertRowColumnP()
{
  std::vector< Actor > vecRemoved;

  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }
  DALI_CHECK_FAIL(tableView.GetRows() < TABLE_VIEW_AVAILABLE_CELL_COUNT + 1, "TableView::Rows() is failed. Rows did not resize.");
  const unsigned int unPreviousIndex = tableView.GetColumns(), unNewActorsCount = tableView.GetRows() - TABLE_VIEW_AVAILABLE_CELL_COUNT;

  if(!TableViewInsertWithChild(ACTION_COLUMN, unPreviousIndex, unNewActorsCount, tableView))
  {
    test_return_value=1;
    return;
  }

  DaliLog::PrintPass();
}


void TableViewDeleteColumnP()
{
  std::vector< Actor > vecRemoved;
  const unsigned int FIRST_COL_INDEX = 0;

  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }
  DALI_CHECK_FAIL(tableView.GetRows() < TABLE_VIEW_AVAILABLE_CELL_COUNT + 1, "TableView::Rows() is failed. Rows did not resize.");
  const unsigned int unPreviousIndex = tableView.GetColumns(), unNewActorsCount = tableView.GetRows() - TABLE_VIEW_AVAILABLE_CELL_COUNT;

  if(!TableViewInsertWithChild(ACTION_COLUMN, unPreviousIndex, unNewActorsCount, tableView))
  {
    test_return_value=1;
    return;
  }
  tableView.DeleteColumn(tableView.GetColumns() - 1);
  DALI_CHECK_FAIL(tableView.GetColumns() != unPreviousIndex, "TableView::DeleteColumn() is failed. Column count mismatches after deletion.");

  if(!TableViewInsertWithChild(ACTION_COLUMN, unPreviousIndex, unNewActorsCount, tableView))
  {
    test_return_value=1;
    return;
  }
  tableView.DeleteColumn(tableView.GetColumns() - 1, vecRemoved);
  DALI_CHECK_FAIL(tableView.GetColumns() != unPreviousIndex, "TableView::DeleteColumn() is failed. Column count mismatches.");
  DALI_CHECK_FAIL(vecRemoved.size() != unNewActorsCount, "TableView::DeleteColumn() is failed. Removed actors count mismatches.");

  vecRemoved.clear();

  tableView.DeleteColumn(FIRST_COL_INDEX, vecRemoved);
  DALI_CHECK_FAIL(tableView.GetColumns() != unPreviousIndex - 1, "TableView::DeleteColumn() is failed. Column count mismatches.");
  DALI_CHECK_FAIL(vecRemoved.size() != tableView.GetRows(), "TableView::DeleteColumn() is failed. Removed actors count mismatches.");

  if(!TableViewRemoveChildActor(tableView))
  {
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();

}

void TableViewDeleteRowP()
{
  std::vector< Actor > vecRemoved;
  const unsigned int FIRST_ROW_INDEX = 0;

  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }
  DALI_CHECK_FAIL(tableView.GetColumns() < TABLE_VIEW_AVAILABLE_CELL_COUNT + 1, "TableView::GetColumns() is failed. Columns did not resize.");
  const unsigned int unPreviousIndex = tableView.GetColumns(), unNewActorsCount = tableView.GetColumns() - TABLE_VIEW_AVAILABLE_CELL_COUNT;

  if(!TableViewInsertWithChild(ACTION_ROW, unPreviousIndex, unNewActorsCount, tableView))
  {
    test_return_value=1;
    return;
  }
  tableView.DeleteRow(tableView.GetRows() - 1);
  DALI_CHECK_FAIL(tableView.GetRows() != unPreviousIndex, "TableView::DeleteRow() is failed. Row count mismatches.");

  if(!TableViewInsertWithChild(ACTION_ROW, unPreviousIndex, unNewActorsCount, tableView))
  {
    test_return_value=1;
    return;
  }
  tableView.DeleteRow(tableView.GetRows() - 1, vecRemoved);
  DALI_CHECK_FAIL(tableView.GetRows() != unPreviousIndex, "TableView::DeleteRow() is failed. Row count mismatches.");
  DALI_CHECK_FAIL(vecRemoved.size() != unNewActorsCount, "TableView::DeleteRow() is failed. Removed actors count mismatches.");

  vecRemoved.clear();

  tableView.DeleteRow(FIRST_ROW_INDEX, vecRemoved);
  DALI_CHECK_FAIL(tableView.GetRows() != unPreviousIndex - 1, "TableView::DeleteRow() is failed. Row count mismatches.");
  DALI_CHECK_FAIL(vecRemoved.size() != tableView.GetColumns(), "TableView::DeleteRow() is failed. Removed actors count mismatches.");

  if(!TableViewRemoveChildActor(tableView))
  {
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();

}

void TableViewResizeP()
{
  std::vector< Actor > vecRemoved;
  const unsigned int REMOVED_COL_COUNT = 2u, REMOVED_ROW_COUNT = 1u;

  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }
  unsigned int unPrevCols = tableView.GetColumns(), unPrevRows = tableView.GetRows();

  tableView.Resize(unPrevRows - REMOVED_ROW_COUNT, unPrevCols - REMOVED_COL_COUNT);
  DALI_CHECK_FAIL(tableView.GetRows() != unPrevRows - REMOVED_ROW_COUNT, "TableView::Resize() is failed. Row count mismatches.");
  DALI_CHECK_FAIL(tableView.GetColumns() != unPrevCols - REMOVED_COL_COUNT, "TableView::Resize() is failed. Column count mismatches.");

  unsigned int unPreviousIndex = 0u, unNewActorsCount = 0u;
  for(unsigned int i = 0; i < REMOVED_COL_COUNT; ++i)
  {
    unPreviousIndex = tableView.GetColumns();
    unNewActorsCount = tableView.GetRows() == 0 ? 1 : tableView.GetRows();
    if(!TableViewInsertWithChild(ACTION_COLUMN, unPreviousIndex, unNewActorsCount, tableView))
    {
      test_return_value=1;
      return;
    }
    unPreviousIndex = tableView.GetRows();
    unNewActorsCount = tableView.GetColumns() == 0 ? 1 : tableView.GetColumns();
    if(!TableViewInsertWithChild(ACTION_ROW, unPreviousIndex, unNewActorsCount, tableView))
    {
      test_return_value=1;
      return;
    }
  }
  unPrevCols = tableView.GetColumns();
  unPrevRows = tableView.GetRows();
  //@NOTE: ac = (rc * r) + (rr * c) - (rr * rc)
  const unsigned int REMOVED_ACTOR_COUNT = (REMOVED_COL_COUNT * unPrevRows) + (REMOVED_ROW_COUNT * unPrevCols) - (REMOVED_COL_COUNT * REMOVED_ROW_COUNT);
  tableView.Resize(unPrevRows - REMOVED_ROW_COUNT, unPrevCols - REMOVED_COL_COUNT, vecRemoved);
  DALI_CHECK_FAIL(tableView.GetRows() != unPrevRows - REMOVED_ROW_COUNT, "TableView::Resize() is failed. Row count mismatches.");
  DALI_CHECK_FAIL(tableView.GetColumns() != unPrevCols - REMOVED_COL_COUNT, "TableView::Resize() is failed. Column count mismatches.");
  DALI_CHECK_FAIL(vecRemoved.size() != REMOVED_ACTOR_COUNT, "TableView::Resize() is failed. Removed actors count mismatches after resizing.");

  vecRemoved.clear();

  if(!TableViewRemoveChildActor(tableView))
  {
    test_return_value=1;
    return;
  }
  DaliLog::PrintPass();

}

void TableViewSetGetCellPaddingP()
{
  TableView::CellPosition cellPosition( 0, 0 );
  gVec3ActorOnePositionInit = Vector3::ZERO;

  gTableView = TableView::New( ROW, COLUMN );
  DALI_CHECK_FAIL( !gTableView, "TableView::New() is failed." );

  Stage::GetCurrent().Add( gTableView );
  gTableView.SetSize( TABLE_VIEW_SIZE );

  gTableActorFirst = Actor::New();
  DALI_CHECK_FAIL( !gTableActorFirst, "Actor::New() is failed." );

  gTableActorFirst.SetSize( TABLE_VIEW_CELL_SIZE );
  gTableView.AddChild( gTableActorFirst, cellPosition );
  DALI_CHECK_FAIL( !gTableView.FindChildPosition(gTableActorFirst, cellPosition), "Actor is not added to table." );

  gTableView.SetCellPadding(gSizeInitPadding);
}

// * ############################## Verdict test for TableViewSetGetCellPadding

void VTTableViewSetGetCellPadding001()
{
  Size sizeGetInitPadding = gTableView.GetCellPadding();
  DALI_CHECK_FAIL( sizeGetInitPadding != gSizeInitPadding, "Set/Get cell padding mismatches for initally no padding." );
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Set/Get position mismatches for initially no padding." );

  gTableView.SetCellPadding(gSizeIFinalPadding);
}
void VTTableViewSetGetCellPadding002()
{
  Size sizeGetPadding = gTableView.GetCellPadding();
  DALI_CHECK_FAIL( sizeGetPadding != gSizeIFinalPadding, "Set/Get cell padding mismatches for a padding value." );

  gVec3ActorOnePositionFinal = Vector3( gSizeIFinalPadding.x, gSizeIFinalPadding.y, 0.0f );
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionFinal, "Set/Get position mismatches for a padding value." );

  Stage::GetCurrent().Remove( gTableView );
  DaliLog::PrintPass();
}

void TableViewSetGetIsFitFixedWidthHeightP()
{
  bool bTableSetupCheck = false;

  TableView::CellPosition cellPositionOne = TableView::CellPosition(0, 0);
  gVec3ActorOnePositionInit = Vector3(Vector3::ZERO);

  TableView::CellPosition cellPositionSecond = TableView::CellPosition(0, 1);
  gVec3ActorTwoPositionInit = Vector3(TABLE_VIEW_CELL_SIZE.x, 0.0f, 0.0f);

  TableView::CellPosition cellPositionThird = TableView::CellPosition(1, 0);
  gVec3ActorThreePositionInit = Vector3(0.0f, TABLE_VIEW_CELL_SIZE.y, 0.0f);

  bTableSetupCheck = TableViewSetUpSimpleTableWithActors( gTableView, gTableActorFirst, gTableActorSecond, gTableActorThird, cellPositionOne, cellPositionSecond, cellPositionThird );
  DALI_CHECK_FAIL( !bTableSetupCheck, "TableView setup with actors is failed." );
}

// * ############################## Verdict test for TableViewSetGetIsFitFixedWidthHeight

void VTTableViewSetGetFitFixedWidthHeight001()
{
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Initial position for first actor is failed." );
  DALI_CHECK_FAIL( gTableActorSecond.GetCurrentPosition() != gVec3ActorTwoPositionInit, "Initial position for second actor is failed." );
  DALI_CHECK_FAIL( gTableActorThird.GetCurrentPosition() != gVec3ActorThreePositionInit, "Initial position for third actor is failed." );

  bool bFitWidth = false, bFitHeight = false;

  gTableView.SetFitHeight(INDEX);
  bFitHeight = gTableView.IsFitHeight(INDEX);
  DALI_CHECK_FAIL( !bFitHeight, "Set/Get fit height mismatches" );

  gTableView.SetFitWidth(INDEX);
  bFitWidth = gTableView.IsFitWidth(INDEX);
  DALI_CHECK_FAIL( !bFitWidth, "Set/Get fit width mismatches" );
}
void VTTableViewSetGetFitFixedWidthHeight002()
{
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Position for first actor should not be changed." );
  DALI_CHECK_FAIL( gTableActorSecond.GetCurrentPosition() != gVec3ActorTwoPositionInit, "Position for second actor should be fit to its value." );
  DALI_CHECK_FAIL( gTableActorThird.GetCurrentPosition() != gVec3ActorThreePositionInit, "Position for third actor should be fit to its value." );

  const float FIXED_WIDTH = 60.0f, FIXED_HEIGHT = 80.0f;
  float fGetWidthFixed = 0.0f, fGetHeightFixed = 0.0f;

  gTableView.SetFixedWidth(INDEX, FIXED_WIDTH);
  fGetWidthFixed = gTableView.GetFixedWidth(INDEX);
  DALI_CHECK_FAIL( fGetWidthFixed != FIXED_WIDTH, "Set/Get fixed width mismatches." );

  gTableView.SetFixedHeight(INDEX, FIXED_HEIGHT);
  fGetHeightFixed = gTableView.GetFixedHeight(INDEX);
  DALI_CHECK_FAIL( fGetHeightFixed != FIXED_HEIGHT, "Set/Get fixed height mismatches." );

  gVec3ActorTwoPositionFinal = Vector3 (fGetWidthFixed, 0.0f, 0.0f);
  gVec3ActorThreePositionFinal = Vector3( 0.0f, fGetHeightFixed, 0.0f );
}
void VTTableViewSetGetFitFixedWidthHeight003()
{
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Position for first actor should not be changed due to setting fixed height and width." );
  DALI_CHECK_FAIL( gTableActorSecond.GetCurrentPosition()!= gVec3ActorTwoPositionFinal, "Position for second actor should be changed due to setting fixed width" );
  DALI_CHECK_FAIL( gTableActorThird.GetCurrentPosition() != gVec3ActorThreePositionFinal, "Position for third actor should be changed due to setting fixed height." );

  Stage::GetCurrent().Remove( gTableView );
  DaliLog::PrintPass();

}

void TableViewSetGetRelativeWidthHeightP()
{
  bool bTableSetupCheck = false;

  TableView::CellPosition cellPositionOne = TableView::CellPosition(0, 0);
  gVec3ActorOnePositionInit = Vector3::ZERO;

  TableView::CellPosition cellPositionSecond = TableView::CellPosition(0, 1);
  gVec3ActorTwoPositionInit = Vector3(TABLE_VIEW_CELL_SIZE.x, 0.0f, 0.0f);

  TableView::CellPosition cellPositionThird = TableView::CellPosition(1, 0);
  gVec3ActorThreePositionInit = Vector3(0.0f, TABLE_VIEW_CELL_SIZE.y, 0.0f);

  bTableSetupCheck = TableViewSetUpSimpleTableWithActors( gTableView, gTableActorFirst, gTableActorSecond, gTableActorThird, cellPositionOne, cellPositionSecond, cellPositionThird );
  DALI_CHECK_FAIL( !bTableSetupCheck, "TableView setup with actors is failed." );
}

// * ############################## Verdict test for TableViewSetGetRelativeWidthHeight

void VTTableViewSetGetRelativeWidthHeight001()
{
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Initial position for first actor is failed." );
  DALI_CHECK_FAIL( gTableActorSecond.GetCurrentPosition() != gVec3ActorTwoPositionInit, "Initial position for second actor is failed." );
  DALI_CHECK_FAIL( gTableActorThird.GetCurrentPosition() != gVec3ActorThreePositionInit, "Initial position for third actor is failed." );

  float fWidthPecentange = 0.4f, fHeightPecentange = 0.5f;
  float fGetWidthPercentage = 0.0f, fGetHeightPecentange = 0.0f;

  gTableView.SetRelativeWidth(INDEX, fWidthPecentange);
  fGetWidthPercentage = gTableView.GetRelativeWidth(INDEX);
  DALI_CHECK_FAIL( fGetWidthPercentage != fWidthPecentange, "Set/Get retative width mismatches." );

  gTableView.SetRelativeHeight(INDEX, fHeightPecentange);
  fGetHeightPecentange = gTableView.GetRelativeHeight(INDEX);
  DALI_CHECK_FAIL( fGetHeightPecentange != fHeightPecentange, "Set/Get retative height mismatches." );

  gVec3ActorTwoPositionFinal = Vector3(TABLE_VIEW_SIZE.x * fGetWidthPercentage, 0.0f, 0.0f);
  gVec3ActorThreePositionFinal = Vector3( 0.0f, TABLE_VIEW_SIZE.y * fGetHeightPecentange, 0.0f );
}
void VTTableViewSetGetRelativeWidthHeight002()
{
  DALI_CHECK_FAIL( gTableActorFirst.GetCurrentPosition() != gVec3ActorOnePositionInit, "Position for first actor should not be changed." );
  DALI_CHECK_FAIL( gTableActorSecond.GetCurrentPosition()!= gVec3ActorTwoPositionFinal, "Position for second actor should be changed due to setting relative width" );
  DALI_CHECK_FAIL( gTableActorThird.GetCurrentPosition() != gVec3ActorThreePositionFinal, "Position for third actor should be changed due to setting relative height." );

  Stage::GetCurrent().Remove( gTableView );

  DaliLog::PrintPass();
}

void TableViewGetRowsColumnsP()
{
  std::vector< Actor > vecRemoved;

  // Creates a 4x1 table-view, and just keep adding.
  TableView tableView = TableView();
  tableView = TableView::New(TABLE_VIEW_INITIAL_ROW_COUNT, TABLE_VIEW_INITIAL_COL_COUNT);
  DALI_CHECK_FAIL(!tableView, "TableView::New() is failed. Uninitialized object.");

  if(!TableViewAddChildActor(TABLE_VIEW_ACTOR_COUNT, tableView))
  {
    test_return_value=1;
    return;
  }

  DALI_CHECK_FAIL(tableView.GetRows() < TABLE_VIEW_AVAILABLE_CELL_COUNT + 1, "TableView::Rows() is failed. Rows did not resize.");
  int unPreviousIndex=0,unPreviousIndex1=0;
  unPreviousIndex = tableView.GetColumns();
  DALI_CHECK_FAIL(!unPreviousIndex, "TableView::GetRows() is failed. Row count mismatches.");


  unPreviousIndex1 = tableView.GetRows();
  DALI_CHECK_FAIL(!unPreviousIndex1, "TableView::GetRows() is failed. Row count mismatches.");

  DaliLog::PrintPass();
}

void TableViewSetCellAlignmentP()
{
  bool bTableSetupCheck = false;

  TableView::CellPosition cellPositionOne = TableView::CellPosition(0, 0);
  gVec3ActorOnePositionInit = Vector3(Vector3::ZERO);

  TableView::CellPosition cellPositionSecond = TableView::CellPosition(0, 1);
  gVec3ActorTwoPositionInit = Vector3(TABLE_VIEW_CELL_SIZE.x, 0.0f, 0.0f);

  TableView::CellPosition cellPositionThird = TableView::CellPosition(1, 0);
  gVec3ActorThreePositionInit = Vector3(0.0f, TABLE_VIEW_CELL_SIZE.y, 0.0f);

  bTableSetupCheck = TableViewSetUpSimpleTableWithActors( gTableView, gTableActorFirst, gTableActorSecond, gTableActorThird, cellPositionOne, cellPositionSecond, cellPositionThird );
  DALI_CHECK_FAIL( !bTableSetupCheck, "TableView setup with actors is failed." );

  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/



/**
 * @testcase            UtcDaliTableViewConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of an object
 */

int UtcDaliTableViewConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewNewP
 * @since_tizen         2.4
 * @description         Checks correct allocation of memory to object
 */

int UtcDaliTableViewNewP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_NEW_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewCopyConstructorP
 * @since_tizen         2.4
 * @description         Checks correct creation of a copy of object
 */

int UtcDaliTableViewCopyConstructorP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_COPY_CONSTRUCTOR_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewOperatorAssignmentP
 * @since_tizen         2.4
 * @description         Checks correct assigntment of one object to other object
 */

int UtcDaliTableViewOperatorAssignmentP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_OPERATOR_ASSIGNMENT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewDowncastP
 * @since_tizen         2.4
 * @description         Checks for correct downcasting of Base Handle
 */

int UtcDaliTableViewDowncastP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_DOWNCAST_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewDowncastN
 * @since_tizen         2.4
 * @description         Negative test for checking downcasting of Base Handle
 */

int UtcDaliTableViewDowncastN(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_DOWNCAST_N );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewAddGetChildAtP
 * @since_tizen         2.4
 * @description         Check correct functionility of AddChild and Getchild APIs
 */

int UtcDaliTableViewAddGetChildAtP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_ADD_GET_CHILD_AT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewRemoveChildP
 * @since_tizen         2.4
 * @description         Check correct functionility of RemoveChild API
 */

int UtcDaliTableViewRemoveChildP(void)
{
  DaliLog::PrintExecStarted( SUITE_NAME, __FUNCTION__ );
  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_REMOVE_CHILD_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewFindChildPositionP
 * @since_tizen         2.4
 * @description         Check that finds the child's layout position where to a cellposition is added before
 */

int UtcDaliTableViewFindChildPositionP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_FIND_CHILD_POSITION_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewInsertRowColumnP
 * @since_tizen         2.4
 * @description         check for correct addition of rows and columns
 */

int UtcDaliTableViewInsertRowColumnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_INSERT_ROW_COLUMN_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewDeleteColumnP
 * @since_tizen         2.4
 * @description         Check that tableView deletes columns and gives back the removed child actors.
 */

int UtcDaliTableViewDeleteColumnP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_DELETE_COLUMN_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewDeleteRowP
 * @since_tizen         2.4
 * @description         Check that tableView deletes rows and gives back the removed child actors.
 */

int UtcDaliTableViewDeleteRowP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_DELETE_ROW_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewResizeP
 * @since_tizen         2.4
 * @description         Check that tableView resizes and gives back the removed child actors.
 */

int UtcDaliTableViewResizeP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_RESIZE_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewSetGetCellPaddingP
 * @since_tizen         2.4
 * @description         Sets and gets cell padding
 */

int UtcDaliTableViewSetGetCellPaddingP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_SET_GET_CELL_PADDING_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewSetGetIsFitFixedWidthHeightP
 * @since_tizen         2.4
 * @description         Sets and gets and fit and fixed width and height
 */

int UtcDaliTableViewSetGetIsFitFixedWidthHeightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_SET_GET_IS_FIT_FIXED_WIDTH_HEIGHT_P );
  application.MainLoop();

  return test_return_value;
}

/**
 * @testcase            UtcDaliTableViewSetGetRelativeWidthHeightP
 * @since_tizen         2.4
 * @description         Sets and gets relative width and height
 */

int UtcDaliTableViewSetGetRelativeWidthHeightP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_SET_GET_RELATIVE_WIDTH_HEIGHT_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewGetRowsColumnsP
 * @since_tizen         2.4
 * @description         Gets rows and columns
 */

int UtcDaliTableViewGetRowsColumnsP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_GET_ROWS_COLUMNS_P );
  application.MainLoop();

  return test_return_value;

}

/**
 * @testcase            UtcDaliTableViewSetCellAlignmentP
 * @since_tizen         2.4
 * @description         Sets cell Alignment
 */

int UtcDaliTableViewSetCellAlignmentP(void)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  Application application = Application::New( &gArgc, &gArgv );
  CHECK_GL;
  TableView_TestApp testApp( application, TABLE_VIEW_SET_CELL_ALIGNMENT_P );
  application.MainLoop();

  return test_return_value;

}
