#ifndef _UTC_DALI_ITEM_LAYOUT_COMMON_H_
#define _UTC_DALI_ITEM_LAYOUT_COMMON_H_


#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME                    "ITEM_LAYOUT_UTC"
#define LAYOUT_POSITION               1.5f
#define PASS_CASE_CONDITION           0

const unsigned int ITEM_LAYOUT_TOTAL_ITEM_NUMBER = 100u; /** Total item number constant **/

/**Gloabl variable declaration**/
extern BufferImage gItemlayoutBufferImage;
extern ImageView gItemlayoutImageView;

/**Helper Class ItemLayoutFactory**/
class ItemLayoutFactory : public ItemFactory
{
  public:

    ItemLayoutFactory();

  public: // From ItemFactory
    virtual unsigned int GetNumberOfItems();
    virtual Actor NewItem(unsigned int uItemId);
};


/**itemlayout initialization**/
bool ItemLayoutInitialize(ItemLayoutFactory& itemFactory,ItemView& itemView, ItemLayoutPtr& gridLayout, ItemLayoutPtr& itemLayout);

/**Set and Get the  internal orientation of a control.**/
void ItemLayoutSetGetOriantation(ControlOrientation::Type nOrientationType, ItemLayoutPtr& itemLayout, int *pnTestResult);

/**Customize Item Layout setting oriantation and layout **/
void ItemLayoutCustomization ( ItemView& itemView, ItemLayoutPtr& itemLayout, ControlOrientation::Type nOrientationType );

#endif //_UTC_DALI_ITEM_LAYOUT_COMMON_H_
