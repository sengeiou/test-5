#include "utc-dali-native-image-common.h"

int gRenderCountNativeImage;
NativeImageImplementedPointer gNativeImageImplemented;
const int EXPECTED_TEXTURE_CALL = 1;

void NativeImageConstructorP()
{
  NativeImage nativeImage;
  DALI_CHECK_FAIL( nativeImage, "NativeImage::Default Constructor is failed" );

  DaliLog::PrintPass();
}

void NativeImageNewP()
{
  const int WIDTH = 10, HEIGHT = 15;
  unsigned int uWidth = static_cast< unsigned int >( WIDTH );
  unsigned int uHeight = static_cast< unsigned int >( HEIGHT );

  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  DaliLog::PrintPass();
}

void NativeImageDownCastP()
{
  const int WIDTH = 10, HEIGHT = 15;
  unsigned int uWidth = static_cast< unsigned int >( WIDTH );
  unsigned int uHeight = static_cast< unsigned int >( HEIGHT );

  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  BaseHandle handle( nativeImage );
  NativeImage nativeImageDownCast = NativeImage::DownCast( handle );
  DALI_CHECK_FAIL( !nativeImageDownCast ,  "NativeImage::DownCast is failed" );
  DALI_CHECK_FAIL( ( nativeImageDownCast.GetWidth() != uWidth ) || ( nativeImageDownCast.GetHeight() != uHeight ),  "Failed to retrieve the width/ height after down cast." );

  DaliLog::PrintPass();
}

void NativeImageDownCastN()
{
  const int WIDTH = 10, HEIGHT = 15;
  //unsigned int uWidth = static_cast< unsigned int >( WIDTH );
  //unsigned int uHeight = static_cast< unsigned int >( HEIGHT );

  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  BaseHandle handle;
  NativeImage nativeImageDownCast = NativeImage::DownCast( handle );
  DALI_CHECK_FAIL( nativeImageDownCast ,  "NativeImage::DownCast is failed" );

  DaliLog::PrintPass();
}

void NativeImageCopyConstructorP()
{
  const int WIDTH = 10, HEIGHT = 15;
  unsigned int uWidth = static_cast< unsigned int >( WIDTH );
  unsigned int uHeight = static_cast< unsigned int >( HEIGHT );

  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  NativeImage nativeImageCopy( nativeImage );
  DALI_CHECK_INSTANCE( nativeImageCopy, "NativeImage Copy constructor is failed to create nativeImageCopy object." );
  DALI_CHECK_FAIL( nativeImageCopy != nativeImage,  "NativeImage copy constructor is failed to copy required native image object" );
  DALI_CHECK_FAIL( ( nativeImageCopy.GetWidth() != uWidth ) || ( nativeImageCopy.GetHeight() != uHeight ),  "Failed to retrieve the width/ height after copying." );

  DaliLog::PrintPass();
}

void NativeImageOperatorAssignmentP()
{
  const int WIDTH = 10, HEIGHT = 15;
  unsigned int uWidth = static_cast< unsigned int >( WIDTH );
  unsigned int uHeight = static_cast< unsigned int >( HEIGHT );

  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  NativeImage nativeImageAssigned =  nativeImage;
  DALI_CHECK_INSTANCE( nativeImageAssigned, "NativeImage::operator= is failed to create nativeImageAssigned object.");
  DALI_CHECK_FAIL( nativeImageAssigned != nativeImage , "NativeImage::operator= is failed to assign required native image object" );
  DALI_CHECK_FAIL( ( nativeImageAssigned.GetWidth() != uWidth ) || ( nativeImageAssigned.GetHeight() != uHeight ),  "Failed to retrieve the width/ height after assignment." );

  DaliLog::PrintPass();
}

void NativeImageCreateGlTextureP()
{
  const int WIDTH = 100, HEIGHT = 150;

  NativeImage nativeImage;
  DALI_CHECK_INSTANCE( !nativeImage, "Default NativeImage is not null." );

  gNativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  nativeImage = NativeImage::New(*(gNativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  nativeImage.CreateGlTexture();
}

void NativeImageCustomFragmentPrefixP()
{
  const int WIDTH = 10, HEIGHT = 15;
  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  DALI_CHECK_FAIL( nativeImage.GetCustomFragmentPreFix() != NULL, "NativeImageImplemented doesn't have Extension, so GetCustomFragmentPreFix() should be NULL" );
  DaliLog::PrintPass();
}

void NativeImageCustomSamplerTypenameP()
{
  const int WIDTH = 10, HEIGHT = 15;
  NativeImageImplementedPointer nativeImageImplemented = NativeImageImplemented::New( WIDTH, HEIGHT );
  DALI_CHECK_INSTANCE( nativeImageImplemented, "NativeImageImplemented instance is not created." );

  NativeImage nativeImage = NativeImage::New(*(nativeImageImplemented.Get()));
  DALI_CHECK_INSTANCE( nativeImage, "NativeImage::New is failed" );

  DALI_CHECK_FAIL( nativeImage.GetCustomSamplerTypename() != NULL, "NativeImageImplemented doesn't have Extension, so GetCustomSamplerTypename() should be NULL" );
  DaliLog::PrintPass();
}

void VTNativeImageCreateGlTexture001()
{
  bool bCreateGlTextureStatus = false;
  bCreateGlTextureStatus = gNativeImageImplemented->m_nExtensionCreateCalls == EXPECTED_TEXTURE_CALL;
  bCreateGlTextureStatus &= gNativeImageImplemented->m_nTargetTextureCalls == EXPECTED_TEXTURE_CALL;
  DALI_CHECK_FAIL( !bCreateGlTextureStatus, "NativeImage::CreateGlTexture is failed." );

  DaliLog::PrintPass();
}
