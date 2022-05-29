#include "utc-dali-native-image-common.h"

NativeImageImplementedPointer NativeImageImplemented::New(int nWidth, int nHeight)
{
  return new NativeImageImplemented(nWidth, nHeight);
}
