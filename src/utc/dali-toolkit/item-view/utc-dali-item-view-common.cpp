#include "utc-dali-item-view-common.h"

/**
 * @function            ItemViewDescendentCount
 * @description         Get total decendant count
 * @param [in]          actorRoot[root actor]
 * @return              itemviewdescent count
 */
int  ItemViewDescendentCount(const Actor& actorRoot)
{
  unsigned int uNumChildren = actorRoot.GetChildCount();

  int nCount = 1;

  for(unsigned int uIndex = 0; uIndex < uNumChildren; ++uIndex)
  {
    nCount += ItemViewDescendentCount(actorRoot.GetChildAt(uIndex));
  }

  return nCount;
}

/**
 * @function            ItemViewInit
 * @description         Initialize the itemview instance
 * @return              true if itemview initialize properly or false otherwise
 */
bool  ItemViewInit( ItemView& itemView , ItemViewFactory& itemFactory)
{
  itemView = ItemView::New(itemFactory);
  DALI_CHECK_FALSE(!itemView,  "Itemview::New() is failed.");

  return true;
}
