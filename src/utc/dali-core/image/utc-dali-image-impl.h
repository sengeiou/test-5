#include "utc-dali-image-common.h"

void ImageDownCastP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !image ,  "ResourceImage::New creation is failed." );
  BaseHandle object(image);

  Image image2 = Image::DownCast(object);
  DALI_CHECK_FAIL( !image2 ,  "DownCast is failed." );

  DaliLog::PrintPass();

}

void ImageDownCastN()
{
  BaseHandle unInitializedObject;
  Image image = Image::DownCast(unInitializedObject);
  DALI_CHECK_FAIL( image ,  "DownCast is failed." );

  Image image2 = DownCast< Image >(unInitializedObject);
  DALI_CHECK_FAIL( image2 ,  "DownCast is failed." );

  DaliLog::PrintPass();

}

void ImageDefaultConstructorP()
{
  Image image;
  DALI_CHECK_FAIL( image ,  "Default Constructor is failed." );

  DaliLog::PrintPass();
}

void ImageCopyConstructorP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !image ,  "ResourceImage::New creation is failed." );

  Image image2(image);
  DALI_CHECK_FAIL(!image2, "Copy Constructor is failed" );

  DaliLog::PrintPass();
}

void ImageGetWidthP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New( strActualPathOne, ImageDimensions(256, 256), FittingMode::SCALE_TO_FILL, SamplingMode::DEFAULT );
  DALI_CHECK_FAIL( image.GetWidth() != 256u, "Width mismatch" );
  //DALI_CHECK_FAIL( image.GetHeight() != 256u, "Height mismatch" );

  DaliLog::PrintPass();
}

void ImageGetHeightP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New( strActualPathOne, ImageDimensions(256, 256), FittingMode::SCALE_TO_FILL, SamplingMode::DEFAULT );
  DALI_CHECK_FAIL( image.GetWidth() != 256u, "Width mismatch" );
  DALI_CHECK_FAIL( image.GetHeight() != 256u, "Height mismatch" );

  DaliLog::PrintPass();
}

void ImageAssignmentOperatorP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !image ,  "Image::New creation is failed" );

  Image imageAssignment;
  imageAssignment = image;
  DALI_CHECK_FAIL(!imageAssignment, "Image() Assignmentoperator  is failed" );

  DaliLog::PrintPass();
}
