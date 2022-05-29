#ifndef _UTC_DALI_ITEM_VIEW_COMMON_H_
#define _UTC_DALI_ITEM_VIEW_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME                     "ITEM_VIEW_UTC"

#define SWIPE_SPEED                     1.5f
#define ANCHOR_DURATION                 1.5f
#define SWIPE_DISTANCE                  2.5f
#define SCROLL_DISTANCE                 100.0f
#define REFRESH_INTERVAL                20
#define ITEM_VIEW_LAYOUT_COUNT          1
#define TEST_IMAGE_FILE_NAME            "dali_imagemodule_image.png"
#define ITEM_ID                         22

/**Gloabl constant variable definition**/
const unsigned int ITEM_VIEW_TOTAL_ITEM_NUMBER = 100;

/** Implementation of ItemFactory for providing actors to ItemView **/
class ItemViewFactory : public ItemFactory
{
  public:

    /**
     * function                 Constructor
     * @param                   NA
     */
    ItemViewFactory()
    {
    }

  public: // From ItemFactory

    /**
     * @function                 Query the number of items available from the factory.
     * @return                   total item number
     * @note                     The maximum available item has an ID of GetNumberOfItems() - 1.
     */
    virtual unsigned int GetNumberOfItems()
    {
      return ITEM_VIEW_TOTAL_ITEM_NUMBER;
    }

    /**
     * @function                 Create an Actor to represent a visible item.
     * @param                    int itemId
     * @return                   the created actor.
     */
    virtual Actor NewItem(unsigned int nItemId)
    {
      string strImagePath=getResourceFullPath(TEST_IMAGE_FILE_NAME);
      if(strImagePath=="")
      {
        LOG_E( "Unable to get resource path from app data directory." );
        return Actor();
      }

      Image image = ResourceImage::New( strImagePath );
      Actor actor = ImageView::New(image);
      return actor;
    }
};

/**Helper to get total decendant count **/
int  ItemViewDescendentCount(const Actor& actorRoot);

/** Helper tp ItemView Initialize **/
bool ItemViewInit(ItemView& itemView , ItemViewFactory& itemFactory);

#endif //_UTC_DALI_ITEM_VIEW_COMMON_H_
