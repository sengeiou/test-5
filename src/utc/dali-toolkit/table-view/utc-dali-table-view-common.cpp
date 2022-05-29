#include "utc-dali-table-view-common.h"

/**
 * @function                     TableViewAddChildActor
 * @description                  Adds actors to tableview cells
 * @return                       If success return true, otherwise false
 */
bool TableViewAddChildActor(unsigned int unActorCount, TableView &tableView)
{
  for(unsigned int i = 0; i < unActorCount; ++i)
  {
    Actor currentActor = Actor::New(), childActor;
    TableView::CellPosition position = TableView::CellPosition();
    tableView.Add( currentActor );
    bool bIsFound = tableView.FindChildPosition(currentActor, position);
    DALI_CHECK_FALSE(!bIsFound, "TableView::FindChildPosition() is failed. Child actor not found to an expected cellposition.");
    childActor = tableView.GetChildAt(position);
    DALI_CHECK_FALSE(childActor != currentActor, "TableView::GetChildAt() is failed. Child actor is not found which was added.");
    bool bIsOccupied = tableView.AddChild( Actor::New(), position );
    DALI_CHECK_FALSE(bIsFound == bIsOccupied, "TableView::AddChild() is failed. The cellposition is should be occupied but its available.");
    unsigned int unCurrentCols = tableView.GetColumns();
    DALI_CHECK_FALSE((i / unCurrentCols) != position.rowIndex, "TableView::GetRows() is failed. Wrong row indexing.");
    DALI_CHECK_FALSE(position.columnIndex != (i % unCurrentCols), "TableView::GetColumns() is failed. Wrong column indexing.");
    DALI_CHECK_FALSE((position.rowIndex * unCurrentCols + position.columnIndex) != i, "TableView::CellPosition() is failed. Wrong cellposition indexing.");
  }
  return true;
}

/**
 * @function                     TableViewRemoveChildActor
 * @description                  Removes added actors from tableview cells
 * @return                       If success return true, otherwise false
 */
bool TableViewRemoveChildActor(TableView &tableView)
{
  TableView copiedTableView(tableView);
  DALI_CHECK_FALSE(copiedTableView != tableView, "TableView::TableView(const TableView&) is failed. Copy constructor gets an uninitialized object");
  TableView assignedTableView = copiedTableView;
  DALI_CHECK_FALSE(assignedTableView != copiedTableView, "TableView::operator=() is failed. Assignment operator gets an uninitialized object");
  TableView downcastedTableView = TableView::DownCast(tableView);
  DALI_CHECK_FALSE(downcastedTableView != copiedTableView, "TableView::DownCast() is failed. Downcasting gets an uninitialized object");
  for(unsigned int i = 0; i < assignedTableView.GetRows(); ++i)
  {
    for(unsigned int j = 0; j < assignedTableView.GetColumns(); ++j)
    {
      TableView::CellPosition position = TableView::CellPosition(i, j);
      Actor removedChild = downcastedTableView.RemoveChildAt(position), childActor;
      DALI_CHECK_FALSE(!removedChild, "TableView::RemoveChildAt() is failed. No child found to this position");
      childActor = tableView.GetChildAt(position);
      DALI_CHECK_FALSE(childActor, "TableView::RemoveChildAt() is failed. Child found to this position");
    }
  }
  return true;
}
/**
 * @function                     TableViewInsertWithChild
 * @description                  Inserts new column/ row and cell actors to new tableview cells
 * @return                       If success return true, otherwise false
 */
bool TableViewInsertWithChild(int eActionType, const unsigned int unInsertIndex, const unsigned int unNewActorsCount, TableView &tableView)
{
  TableView::CellPosition position;
  if(eActionType == ACTION_COLUMN)
  {
    tableView.InsertColumn(unInsertIndex);
    DALI_CHECK_FALSE(tableView.GetColumns() != unInsertIndex + 1, "TableView::InsertColumn() is failed. Column count mismatches.");
  }
  else if(eActionType == ACTION_ROW)
  {
    tableView.InsertRow(unInsertIndex);
    DALI_CHECK_FALSE(tableView.GetRows() != unInsertIndex + 1, "TableView::InsertRow() is failed. Row count mismatches.");
  }
  for(unsigned int i = 0; i < unNewActorsCount; ++i)
  {
    if(eActionType == ACTION_COLUMN)
    {
      position = TableView::CellPosition( i, unInsertIndex);
    }
    else if(eActionType == ACTION_ROW)
    {
      position = TableView::CellPosition( unInsertIndex, i);
    }
    bool bIsAdded = tableView.AddChild( Actor::New(), position );
    DALI_CHECK_FALSE(!bIsAdded, "TableView::AddChild() is failed. The cellposition is not available.");
  }
  return true;
}

/**
 * @function                     TableViewSetUpSimpleTableWithActors
 * @description                  Helper for Setup a simple table with actors with their cell position
 * @return                       bool - true, if table is created successfully with actors; false, otherwise
 */

bool TableViewSetUpSimpleTableWithActors( TableView& tableView, Actor& actorFirst, Actor& actorSecond, Actor& actorThird, TableView::CellPosition cellActorFirst, TableView::CellPosition cellActorSecond, TableView::CellPosition cellActorThird)
{
  tableView = TableView::New( ROW, COLUMN );
  DALI_CHECK_FALSE( !tableView, "TableView::New() is failed." );

  Stage::GetCurrent().Add( tableView );
  tableView.SetSize( TABLE_VIEW_SIZE );

  actorFirst = Actor::New();
  DALI_CHECK_FALSE( !actorFirst, "Actor::New() is failed for first actor." );

  actorSecond = Actor::New();
  DALI_CHECK_FALSE( !actorSecond, "Actor::New() is failed for second actor." );

  actorThird = Actor::New();
  DALI_CHECK_FALSE( !actorSecond, "Actor::New() is failed for third actor." );

  actorFirst.SetSize( TABLE_VIEW_CELL_SIZE );
  actorSecond.SetSize( TABLE_VIEW_CELL_SIZE );
  actorThird.SetSize( TABLE_VIEW_CELL_SIZE );

  tableView.AddChild( actorFirst, cellActorFirst );
  DALI_CHECK_FALSE( !tableView.FindChildPosition(actorFirst, cellActorFirst), "First Actor is not added to table." );
  try
  {
    tableView.SetCellAlignment( cellActorFirst, HorizontalAlignment::LEFT, VerticalAlignment::TOP );
  }
  catch(DaliException& de)
  {
    LOG_E("TableView::SetCellAlignment is failed for first cell position");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    return false;
  }

  tableView.AddChild( actorSecond, cellActorSecond );
  DALI_CHECK_FALSE( !tableView.FindChildPosition(actorSecond, cellActorSecond), "Second Actor is not added to table." );
  try
  {
    tableView.SetCellAlignment( cellActorSecond, HorizontalAlignment::LEFT, VerticalAlignment::TOP );
  }
  catch(DaliException& de)
  {
    LOG_E("TableView::SetCellAlignment is failed for second cell position");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    return false;
  }

  tableView.AddChild( actorThird, cellActorThird );
  DALI_CHECK_FALSE( !tableView.FindChildPosition(actorThird, cellActorThird), "Third Actor is not added to table." );
  try
  {
    tableView.SetCellAlignment( cellActorThird, HorizontalAlignment::LEFT, VerticalAlignment::TOP );
  }
  catch(DaliException& de)
  {
    LOG_E("TableView::SetCellAlignment is failed for third cell position");
    DaliLog::PrintV(LOG_ERROR, SUITE_NAME, "Dali Exception Thrown, location: %s, condition: %s, at [LINE: %d]", de.location, de.condition, __LINE__);
    return false;
  }

  return true;
}

