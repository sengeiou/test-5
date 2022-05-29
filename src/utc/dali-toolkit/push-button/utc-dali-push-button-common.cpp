#include "utc-dali-push-button-common.h"

//Add helper function definitions here

/**
 * @function                  PushButtonCreateImage
 * @description               Creates an Image handle with the specified image
 * @return                    true if image handle returns a valid handle or false otherwise
 */
bool PushButtonCreateImage(Image& imgSetImage)
{
  string strActualPathOne=getResourceFullPath(PUSH_BUTTON_IMAGE_ONE);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    return false;
  }

  imgSetImage = ResourceImage::New( strActualPathOne);
  if(!imgSetImage)
  {
    LOG_E( "PushButtonCreateImage is failed.");
    strActualPathOne.clear();
    return false;
  }
  strActualPathOne.clear();
  return true;
}

