#include "utc-texture-common.h"

NativeImageInterfaceImplPointer NativeImageInterfaceImpl::New(int nWidth, int nHeight)
{
  return new NativeImageInterfaceImpl(nWidth, nHeight);
}

