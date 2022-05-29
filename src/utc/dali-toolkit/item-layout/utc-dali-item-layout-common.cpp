#include "utc-dali-item-layout-common.h"

/**Gloabl variable definition**/
BufferImage gItemlayoutBufferImage;
ImageView gItemlayoutImageView;


/**
 * @function             ItemLayout Initialize
 * @description          Item Layout (ItemView and GridLayout )initialization
 */

bool ItemLayoutInitialize(ItemLayoutFactory& itemFactory, ItemView& itemView, ItemLayoutPtr& gridLayout, ItemLayoutPtr& itemLayout)
{
  const unsigned int FIRST_LAYOUT_INDEX = 0u;
  itemView = ItemView::New(itemFactory);
  DALI_CHECK_FALSE(!itemView, "ItemView::New() is failed." );

  gridLayout = DefaultItemLayout::New( DefaultItemLayout::GRID );
  DALI_CHECK_FALSE(!gridLayout, "GridLayout::New() is failed." );

  itemView.AddLayout(*gridLayout);
  itemLayout = itemView.GetLayout(FIRST_LAYOUT_INDEX);

  DALI_CHECK_FALSE(itemLayout != gridLayout, "Layout retrieve is incorrect." );
  return true;
}


/**
 * Function          Constructor
 * @param            application class, stored as reference
 */

ItemLayoutFactory::ItemLayoutFactory()
{
}

/**
 * @Function          Query the number of items available from the factory.
 * @return            NA
 * @remarks           The maximum available item has an ID of GetNumberOfItems() - 1.
 */

unsigned int ItemLayoutFactory::GetNumberOfItems()
{
  return ITEM_LAYOUT_TOTAL_ITEM_NUMBER;
}


/**
 * @Function             Create an Actor to represent a visible item.
 * @description          Create an Actor and Set Name and Size
 * @return               the created actor.
 */

Actor ItemLayoutFactory::NewItem(unsigned int uItemId)
{
  const string IMG_ACTOR_NAME = "TestImageFilenameActor";
  const float fWIDTH =100.0f, fHEIGHT = 100.0f;

  gItemlayoutImageView = ImageView::New( gItemlayoutBufferImage );
  gItemlayoutImageView.SetSize( fWIDTH, fHEIGHT );
  gItemlayoutImageView.SetName(IMG_ACTOR_NAME);

  return gItemlayoutImageView;
}


/**
 * @function          ItemLayout Set and Get Oriantation
 * @description       Set and Get the  internal orientation of a control.
 */

void ItemLayoutSetGetOriantation(ControlOrientation::Type nOrientationType, ItemLayoutPtr& itemLayout, int *pnTestResult)
{
  itemLayout->SetOrientation(nOrientationType);
  ControlOrientation::Type nOrientationGetType = itemLayout->GetOrientation();

  if (nOrientationType != nOrientationGetType)
  {
    (*pnTestResult)++;
    LOG_E( "OrientationType is mismatched." );
  }
}


/**
 * @function             ItemLayout Customization
 * @description          Customize Item Layout setting oriantation and layout
 * @@param               ControlOrientation::Type nOrientationType [Orientation of a Control]
 */

void ItemLayoutCustomization ( ItemView& itemView, ItemLayoutPtr& itemLayout, ControlOrientation::Type nOrientationType )
{
  const unsigned int ITEM_ID = 0u, LAYOUT_INDEX = 0u;
  const float fPOSITION = 0.0f , fDURATION = 0.0f;
  Vector3 vec3TargetSize(480.0f, 800.0f, 0.0f);

  itemLayout->SetOrientation(nOrientationType);
  itemView.ActivateLayout(LAYOUT_INDEX, vec3TargetSize, fDURATION);
  itemLayout->GetClosestOnScreenLayoutPosition(ITEM_ID, fPOSITION, vec3TargetSize);
}
