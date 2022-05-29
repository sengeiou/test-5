#ifndef _UTC_DALI_IMAGE_COMMON_H_
#define _UTC_DALI_IMAGE_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>
#include <dali-toolkit/public-api/image-loader/image.h>

using namespace Dali;
using namespace Toolkit;


#define SUITE_NAME            "IMAGE_UTC"

#define DALI_TEST_CHECK(condition)                                                          \
if ( (condition) )                                                                          \
{                                                                                           \
  test_return_value = 0;                                                                    \
}                                                                                           \
else                                                                                        \
{                                                                                           \
  fprintf(stderr, "%s Failed in %s at line %d\n", __PRETTY_FUNCTION__, __FILE__, __LINE__); \
  test_return_value = 1;                                                                    \
  TcResult();                                                                               \
}

#endif //_UTC_DALI_IMAGE_COMMON_H_
