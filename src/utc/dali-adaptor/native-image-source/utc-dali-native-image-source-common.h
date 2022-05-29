#ifndef _UTC_DALI_NATIVE_IMAGE_SOURCE_COMMON_H_
#define _UTC_DALI_NATIVE_IMAGE_SOURCE_COMMON_H_

#include "dali-common.h"

using namespace Dali;


#define SUITE_NAME              "NATIVE_IMAGE_SOURCE_UTC"
#define NATIVE_IMAGE_SOURCE_FILENAME        "native_image_source_testImage.png"

/**Helper for native image source construction with proper pixels, internal source and encoding to required file format for different color depths*/
bool NativeImageSourceNewGetPixelSourceEncodeToFile(NativeImageSource::ColorDepth colorDepth);

#endif  //_UTC_DALI_NATIVE_IMAGE_SOURCE_COMMON_H_
