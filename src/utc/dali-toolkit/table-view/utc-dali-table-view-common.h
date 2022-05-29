#ifndef _UTC_DALI_TABLE_VIEW_COMMON_H_
#define _UTC_DALI_TABLE_VIEW_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME        "TABLE_VIEW_UTC"
#define INDEX             0u

const Vector2 TABLE_VIEW_CELL_SIZE(20.0f, 20.0f);                     /** Cell size of table**/
const Vector2 TABLE_VIEW_SIZE(200.0f, 200.0f);                        /** Table size **/
const unsigned int ROW = 10u, COLUMN = 10u;                           /** Rows and columns of table**/
const unsigned int TABLE_VIEW_ACTOR_COUNT = 16u;                      /** Number of actors to be added for table**/
const unsigned int TABLE_VIEW_INITIAL_ROW_COUNT = 1u;                 /** Initial row count**/
const unsigned int TABLE_VIEW_INITIAL_COL_COUNT = 4u;                 /** Initial column count**/
const unsigned int TABLE_VIEW_AVAILABLE_CELL_COUNT = 2u;              /**@NOTE: available cells are empty cells with no actors occupied**/

enum action_e
{
  ACTION_ROW,
  ACTION_COLUMN
};

/** Adds actors to tableview cells **/
bool TableViewAddChildActor(unsigned int unActorCount, TableView &refTableView);

/** Removes added actors from tableview cells **/
bool TableViewRemoveChildActor(TableView &tableView);

/** Inserts new column and cell actors to new tableview cells **/
bool TableViewInsertWithChild(int eActionType, const unsigned int unInsertIndex, const unsigned int unNewActorsCount, TableView &tableView);

/** Helper for Setup a simple table with actors with their cell position **/
bool TableViewSetUpSimpleTableWithActors( TableView& tableView, Actor& actorFirst, Actor& actorSecond, Actor& actorThird, TableView::CellPosition cellActorFirst, TableView::CellPosition cellActorSecond, TableView::CellPosition cellActorThird);

#endif //_UTC_DALI_TABLE_VIEW_COMMON_H_
