#ifndef _UTC_DALI_NATIVE_IMAGE_COMMON_H_
#define _UTC_DALI_NATIVE_IMAGE_COMMON_H_

#include "dali-common.h"

using namespace Dali;

#define SUITE_NAME  "NATIVE_IMAGE_UTC"

/** Helper class for NativeImage creation**/
class NativeImageImplemented;
typedef IntrusivePtr<NativeImageImplemented> NativeImageImplementedPointer;

class NativeImageImplemented : public Dali::NativeImageInterface
{
  public:
    static NativeImageImplementedPointer New(int nWidth, int nHeight);

    inline virtual bool GlExtensionCreate() { ++m_nExtensionCreateCalls; return true;};
    inline virtual void GlExtensionDestroy() { ++m_nExtensionDestroyCalls; };
    inline virtual unsigned int TargetTexture() { ++m_nTargetTextureCalls; return 1;};
    inline virtual void PrepareTexture() {};
    inline virtual unsigned int GetWidth() const {return m_nWidth;};
    inline virtual unsigned int GetHeight() const {return m_nHeight;};
    inline virtual bool RequiresBlending() const {return true;};
    inline virtual bool IsYInverted() const {return true;};

  private:
    NativeImageImplemented(int width, int height)
      : m_nWidth(width), m_nHeight(height), m_nExtensionCreateCalls(0), m_nExtensionDestroyCalls(0), m_nTargetTextureCalls(0)
    {
    }
    virtual ~NativeImageImplemented()
    {
    }

    int m_nWidth;
    int m_nHeight;
  public:
    int m_nExtensionCreateCalls;
    int m_nExtensionDestroyCalls;
    int m_nTargetTextureCalls;
};

#endif  //_UTC_DALI_NATIVE_IMAGE_COMMON_H_
