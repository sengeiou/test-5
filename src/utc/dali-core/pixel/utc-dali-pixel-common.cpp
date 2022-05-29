#include "utc-dali-pixel-common.h"

//Keeping all the enum names of Pixel in an array for Print Log
string gPixelEnumList[] = {  "A8",
  "L8",
  "LA88",
  "RGB565",
  "BGR565",
  "RGBA4444",
  "BGRA4444",
  "RGBA5551",
  "BGRA5551",
  "RGB888",
  "RGB8888",
  "BGR8888",
  "RGBA8888",
  "BGRA8888",
  "COMPRESSED_R11_EAC",
  "COMPRESSED_SIGNED_R11_EAC",
  "COMPRESSED_RG11_EAC",
  "COMPRESSED_SIGNED_RG11_EAC",
  "COMPRESSED_RGB8_ETC2",
  "COMPRESSED_SRGB8_ETC2",
  "COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2",
  "COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2",
  "COMPRESSED_RGBA8_ETC2_EAC",
  "COMPRESSED_SRGB8_ALPHA8_ETC2_EAC",
  "COMPRESSED_RGB8_ETC1",
  "COMPRESSED_RGB_PVRTC_4BPPV1"
};

//   Keeping all the enums of Pixel in an array in an order so that first 14 enums do not have alpha channel and rest of them
//   have alpha channel : According to help document
Pixel::Format gPixelFormatA[] = {  Pixel::L8,
  Pixel::RGB565,
  Pixel::RGB888,
  Pixel::RGB8888,
  Pixel::BGR8888,
  Pixel::BGR565,
  Pixel::COMPRESSED_R11_EAC,
  Pixel::COMPRESSED_SIGNED_R11_EAC,
  Pixel::COMPRESSED_RG11_EAC,
  Pixel::COMPRESSED_SIGNED_RG11_EAC,
  Pixel::COMPRESSED_RGB8_ETC2,
  Pixel::COMPRESSED_SRGB8_ETC2,
  Pixel::COMPRESSED_RGB8_ETC1,
  Pixel::COMPRESSED_RGB_PVRTC_4BPPV1,
  Pixel::A8,
  Pixel::LA88,
  Pixel::RGBA5551,
  Pixel::RGBA4444,
  Pixel::RGBA8888,
  Pixel::BGRA8888,
  Pixel::BGRA5551,
  Pixel::BGRA4444,
  Pixel::COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
  Pixel::COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
  Pixel::COMPRESSED_RGBA8_ETC2_EAC,
  Pixel::COMPRESSED_SRGB8_ALPHA8_ETC2_EAC
};

int gPixelEnumSize = sizeof( gPixelFormatA )/sizeof( gPixelFormatA[0] );

//Byte values are set according to help document
unsigned int gPixelBytePerPxl[] = { 1, 2, 3, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 4, 4, 2, 2, 0, 0, 0, 0 };

// For testing purpose, ByteOffSet and BitMask values are set according to source file as no information is given in help document
int gPixelByteOffset[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 3, 3, 1, 1, 0, 0, 0, 0 };
int gPixelBitMask[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0xff, 0x01, 0x0f, 0xff, 0xff, 0x01, 0x0f, 0, 0, 0, 0 };


/**
 * @function         PixelSetGetforImageAttributes
 * @description      Set and Get Pixel format for BitmapImage
 * @parameter
 *           [IN]    formatSet[Pixel::Format to set]
 *           [IN]    formatGet[Pixel::Format to get]
 *           [OUT]   NA
 * @return           bool : false, BitmapImage is not created with the piexel format or if retrieved pixel format is not matched to the set format
 *                        : true, if BitmapImage is created successfully with piexel format and retrieved pixel format is matched to the set format
 */
bool PixelSetGetforImageAttributes(Pixel::Format formatSet, Pixel::Format &formatGet)
{
  BufferImage bitmapImage = BufferImage::New(100,100, formatSet);

  if ( !bitmapImage )
  {
    LOG_E("Image::New() is failed");
    return false;
  }

  formatGet = bitmapImage.GetPixelFormat();
  bitmapImage.Reset();

  if ( formatGet != formatSet )
  {
    LOG_E("Failed to retrieve pixel format set to ImageAttributes");
    return false;
  }

  return true;
}
