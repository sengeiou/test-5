#ifndef _UTC_DALI_RESOURCE_IMAGE_COMMON_H_
#define _UTC_DALI_RESOURCE_IMAGE_COMMON_H_

#include "dali-common.h"

#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "RESOURCE_IMAGE_UTC"

#define IMAGE_FILENAME  "dali_imagemodule_image.png"

namespace
{
  const unsigned int RESOURCE_IMAGE_INVALID_SIZE = 0u;
  const unsigned int RESOURCE_IMAGE_WIDTH = 80u;
  const unsigned int RESOURCE_IMAGE_HEIGHT = 80u;
};

/** Add actor to Stage */
void ResourceImageAddActorToStage(Dali::Image image);

#endif  //_UTC_DALI_RESOURCE_IMAGE_COMMON_H_
