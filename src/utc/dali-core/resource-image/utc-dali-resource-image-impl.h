#include "utc-dali-resource-image-common.h"

int gRenderCountResourceImage;   /**Render Count*/
ResourceImage gResourceImage;    /**ResourceImage instance **/
ResourceImage gResourceImage1;    /**ResourceImage instance **/
int gSignalLoadFlag;
int gSignalInvalidLoadFlag;
Actor gActorView1;                                    /** ImageView instance **/

void CbLoadingFinishedSignal(ResourceImage image)
{
  gSignalLoadFlag = 1;
  LOG_I(" CbLoadingFinishedSignal is called.");
  if(image.GetLoadingState() == ResourceLoadingSucceeded)
  {
    LOG_I("Loading state is LoadingState::ResourceLoadingSucceeded.");
  }
  else if(image.GetLoadingState() == ResourceLoadingFailed)
  {
    LOG_E("Loading state is LoadingState::ResourceLoadingFailed.");
  }
  else
  {
    LOG_E("Image::GetLoadingState is failed: invalid loading state.");
    gSignalInvalidLoadFlag = 1;
  }
}

void ResourceImageGetImageSizeP()
{
  unsigned int uWidth = 128u , uHeight = 256u;

  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  const ImageDimensions ImageSize = ResourceImage::GetImageSize(strActualPathOne);
  DALI_CHECK_FAIL( ImageSize.GetX() < RESOURCE_IMAGE_INVALID_SIZE, "ResourceImage::GetImageSize is failed; invalid ImageDimension is found.");
  DALI_CHECK_FAIL( ImageSize.GetY() < RESOURCE_IMAGE_INVALID_SIZE, "ResourceImage::GetImageSize is failed; invalid ImageDimension is found.");

  DaliLog::PrintPass();
}


void ResourceImageReloadP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  gResourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !gResourceImage ,  "ResourceImage::New creation is failed." );

  gResourceImage.LoadingFinishedSignal().Connect( CbLoadingFinishedSignal );
}

void VTResourceImageReload001()
{
  gActorView1 = ImageView::New(gResourceImage);
  DALI_CHECK_FAIL(!gActorView1, " imgActorView1 is empty.");

  gActorView1.SetVisible(true);
  Stage::GetCurrent().Add(gActorView1);
}
void VTResourceImageReload002()
{
  DALI_CHECK_FAIL( !gSignalLoadFlag, "Failed to connect to Image::LoadingFinishedSignal");
  gSignalLoadFlag = 0;
  gResourceImage.Reload();
}
void VTResourceImageReload003()
{
  DALI_CHECK_FAIL( !gSignalLoadFlag, "Failed to connect to Image::LoadingFinishedSignal");
  gSignalLoadFlag = 0;

  Stage::GetCurrent().Remove(gActorView1);
  DaliLog::PrintPass();
}

void ResourceImageGetLoadingStateP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  gResourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !gResourceImage ,  "ResourceImage::New creation is failed." );

  gResourceImage.LoadingFinishedSignal().Connect( CbLoadingFinishedSignal );

  LoadingState loadingState = gResourceImage.GetLoadingState();
  DALI_CHECK_FAIL(loadingState != ResourceLoadingSucceeded , "Image::GetLoadingState is failed: If resource image loads successfully (sync loading), loading state should be LoadingState::ResourceLoadingSucceeded." );

  DaliLog::PrintPass();
}

void ResourceImageDownCastP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  ResourceImage image = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !image ,  "ResourceImage::New creation is failed." );

  BaseHandle object(image);

  ResourceImage image2 = ResourceImage::DownCast(object);
  DALI_CHECK_FAIL( !image2 ,  "Image::DownCast is failed." );

  DaliLog::PrintPass();
}

void ResourceImageDownCastN()
{
  Image imgFromActor;

  ResourceImage imageDowncast = ResourceImage::DownCast(imgFromActor);
  DALI_CHECK_FAIL( imageDowncast ,  "Image::DownCast is failed." );

  DaliLog::PrintPass();
}

void ResourceImageGetUrlP()
{
  string strGetUrl = "";
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  ResourceImage resourceImageAssign;
  DALI_CHECK_FAIL( resourceImageAssign ,  "Default ResourceImage image is not null." );

  ResourceImage resourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !resourceImage ,  "ResourceImage::New creation is failed." );

  strGetUrl = resourceImage.GetUrl();
  DALI_CHECK_FAIL(strGetUrl != strActualPathOne, "ResourceImage::GetUrl() is failed to match with its original");

  resourceImageAssign = resourceImage;
  DALI_CHECK_FAIL( !resourceImageAssign ,  "ResourceImage instance is failed after assignment." );
  DALI_CHECK_FAIL( resourceImageAssign.GetUrl() != strActualPathOne,
      "ResourceImage::operator= is failed; could not get image url after assignment.");

  ResourceImage resourceImageCopy( resourceImage );
  DALI_CHECK_FAIL( !resourceImageCopy ,  "ResourceImage instance is failed after copying." );
  DALI_CHECK_FAIL( resourceImageCopy.GetUrl() != strActualPathOne, "ResourceImage(const ResourceImage& ) is failed; could not get image url after copying.");

  strGetUrl.clear();
  strActualPathOne.clear();
  DaliLog::PrintPass();

}

void ResourceImageCopyConstructorP()
{
  string strGetUrl = "";
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  ResourceImage resourceImageAssign;
  DALI_CHECK_FAIL( resourceImageAssign ,  "Default ResourceImage image is not null." );

  ResourceImage resourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !resourceImage ,  "ResourceImage::New creation is failed." );

  strGetUrl = resourceImage.GetUrl();
  DALI_CHECK_FAIL(strGetUrl != strActualPathOne, "ResourceImage::GetUrl() is failed to match with its original");

  resourceImageAssign = resourceImage;
  DALI_CHECK_FAIL( !resourceImageAssign ,  "ResourceImage instance is failed after assignment." );
  DALI_CHECK_FAIL( resourceImageAssign.GetUrl() != strActualPathOne,
      "ResourceImage::operator= is failed; could not get image url after assignment.");

  ResourceImage resourceImageCopy( resourceImage );
  DALI_CHECK_FAIL( !resourceImageCopy ,  "ResourceImage instance is failed after copying." );
  DALI_CHECK_FAIL( resourceImageCopy.GetUrl() != strActualPathOne, "ResourceImage(const ResourceImage& ) is failed; could not get image url after copying.");

  strGetUrl.clear();
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ResourceImageOperatorAssignmentP()
{
  string strGetUrl = "";
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  ResourceImage resourceImageAssign;
  DALI_CHECK_FAIL( resourceImageAssign ,  "Default ResourceImage image is not null." );

  ResourceImage resourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !resourceImage ,  "ResourceImage::New creation is failed." );

  strGetUrl = resourceImage.GetUrl();
  DALI_CHECK_FAIL(strGetUrl != strActualPathOne, "ResourceImage::GetUrl() is failed to match with its original");

  resourceImageAssign = resourceImage;
  DALI_CHECK_FAIL( !resourceImageAssign ,  "ResourceImage instance is failed after assignment." );
  DALI_CHECK_FAIL( resourceImageAssign.GetUrl() != strActualPathOne, "ResourceImage::operator= is failed; could not get image url after assignment.");

  ResourceImage resourceImageCopy;
  resourceImageCopy = resourceImage;
  DALI_CHECK_FAIL( !resourceImageCopy ,  "ResourceImage instance is failed after copying." );
  DALI_CHECK_FAIL( resourceImageCopy.GetUrl() != strActualPathOne, "Operator = is failed; could not get image url after copying.");

  strGetUrl.clear();
  strActualPathOne.clear();
  DaliLog::PrintPass();
}

void ResourceImageNewP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New( strActualPathOne);
  DALI_CHECK_FAIL(!image , "image creation is failed with dimension value");

  DaliLog::PrintPass();
}

void ResourceImageNewWithDimensionP()
{
  unsigned int uWidth = 128u , uHeight = 256u;

  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  Image image = ResourceImage::New( strActualPathOne, ImageDimensions(uWidth, uHeight), FittingMode::SCALE_TO_FILL, SamplingMode::DEFAULT );
  DALI_CHECK_FAIL(!image , "image creation is failed with dimension value");

  DALI_CHECK_FAIL(image.GetWidth() != uWidth, "ResourceImage::New is failed to set dimension value" );
  DALI_CHECK_FAIL(image.GetHeight() != uHeight, "ResourceImage::New is failed to set dimension value" );


  DaliLog::PrintPass();
}

void ResourceImageLoadingFinishedSignalP()
{
  string strActualPathOne=getResourceFullPath(IMAGE_FILENAME);
  if(strActualPathOne=="")
  {
    LOG_E( "Unable to get resource path from app data directory." );
    test_return_value=1;
    return;
  }

  gResourceImage = ResourceImage::New(strActualPathOne);
  DALI_CHECK_FAIL( !gResourceImage ,  "ResourceImage::New creation is failed." );

  gResourceImage.LoadingFinishedSignal().Connect( CbLoadingFinishedSignal );

  ImageView imageView = ImageView::New( gResourceImage );
  Stage::GetCurrent().Add( imageView );
}

void VTResourceImageLoadingFinishedSignal001()
{
  DALI_CHECK_FAIL( !gSignalLoadFlag,  "Failed to connect to Image::LoadingFinishedSignal" );
  gSignalLoadFlag = 0;
  DaliLog::PrintPass();
}
