#include "utc-dali-native-image-source-common.h"

bool NativeImageSourceNewGetPixelSourceEncodeToFile(NativeImageSource::ColorDepth colorDepth)
{
  string strActualPathOne = "";
  bool bGetPixel = false, bEncodeToFIle = false;
  vector< unsigned char > pixbuf;
  unsigned int uSetWidth = 256u , uSetHeight = 256u , uGetWidth = 0u , uGetHeight = 0u;
  Pixel::Format pixelFormat;

  NativeImageSourcePtr ptrNativeImageSource = NativeImageSource::New(uSetWidth,uSetHeight, colorDepth);
  DALI_CHECK_FALSE(!ptrNativeImageSource, "NativeImageSource::New(unsigned int, unsigned int, ColorDepth) is failed.");

  if(ptrNativeImageSource->IsColorDepthSupported(colorDepth) == false)
  {
    LOG_E( "Not supported ColorDepth format! HW target dependent value!" );
    return true;
  }

  Any ptrNativeImageSourceAny = ptrNativeImageSource->GetNativeImageSource();
  DALI_CHECK_FALSE( ptrNativeImageSourceAny.Empty() , "NativeImageSource::GetNativeImageSource() is failed.");

  NativeImageSourcePtr ptrAnyNativeImageSource = NativeImageSource::New(ptrNativeImageSourceAny);
  DALI_CHECK_FALSE(!ptrAnyNativeImageSource, "NativeImageSource::New() is failed with Any source.");

  bGetPixel= ptrNativeImageSource->GetPixels(pixbuf,uGetWidth,uGetHeight,pixelFormat);
  DALI_CHECK_FALSE(!bGetPixel, "GetPixels is failed to retrieve the pixel values and formats.");

  strActualPathOne=getResourceFullPath(NATIVE_IMAGE_SOURCE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    return false;
  }

  bEncodeToFIle = ptrNativeImageSource->EncodeToFile(strActualPathOne);
  DALI_CHECK_FALSE(!bEncodeToFIle, "NativeImageSource::EncodeToFile() is failed.");
  return true;
}


