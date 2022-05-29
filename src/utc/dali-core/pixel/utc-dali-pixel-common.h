#ifndef _UTC_DALI_PIXEL_COMMON_H_
#define _UTC_DALI_PIXEL_COMMON_H_

#include "dali-common.h"
#include <exception>
#include <dali/dali.h>
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "PIXEL-UTC"
#define IMAGE_NAME  "dali_imagemodule_image.png"


/****************Global variable declaration starts**************************/
extern string gPixelEnumList[];
extern Pixel::Format gPixelFormatA[];
extern int gPixelEnumSize;
extern unsigned int gPixelBytePerPxl[];
extern int gPixelByteOffset[];
extern int gPixelBitMask[];
/****************Global variable declaration ends**************************/

//Set and Get Pixel format for ImageAttributes
bool PixelSetGetforImageAttributes(Pixel::Format formatSet, Pixel::Format &formatGet);

#endif  //_UTC_DALI_PIXEL_COMMON_H_
