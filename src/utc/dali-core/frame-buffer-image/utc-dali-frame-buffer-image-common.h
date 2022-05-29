#ifndef _UTC_DALI_FRAME_BUFFER_IMAGE_COMMON_H_
#define _UTC_DALI_FRAME_BUFFER_IMAGE_COMMON_H_

#include "dali-common.h"
#include <dali-toolkit/dali-toolkit.h>

using namespace std;
using namespace Dali;
using namespace Toolkit;

#define SUITE_NAME  "FRAME_BUFFER_IMAGE_UTC"

const unsigned int INTERVAL_IN_MILLISECONDS = 16;

class TestNativeImageInterface : public NativeImageInterface
{
  public:
    int m_nWidth ;
    int m_nHeight;
    TestNativeImageInterface(int nWidth, int nHeight): m_nWidth(nWidth), m_nHeight(nHeight)
    {

    }

    virtual bool GlExtensionCreate()
    {
      return true;
    };

    /**
     * Destroy the GL resource for the NativeImageInterface.
     * e.g. For the EglImageKHR extension, this corresponds to calling eglDestroyImageKHR()
     * @pre There is a GL context for the current thread.
     */
    virtual void GlExtensionDestroy() {};

    /**
     * Use the NativeImageInterface as a texture for rendering
     * @pre There is a GL context for the current thread.
     * @return A GL error code
     */
    virtual unsigned int TargetTexture()
    {
      return 0;
    };

    /**
     * Called in each NativeTexture::Bind() call to allow implementation specific operations.
     * The correct texture sampler has already been bound before the function gets called.
     * @pre glAbstraction is being used by context in current thread
     */
    virtual void PrepareTexture() {}

    /**
     * Returns the width of the NativeImageInterface
     * @return width
     */
    virtual unsigned int GetWidth() const
    {
      return m_nWidth;
    }

    /**
     * Returns the height of the NativeImageInterface
     * @return height
     */
    virtual unsigned int GetHeight() const
    {
      return m_nHeight;
    }

    /**
     * Returns whether the Blending is required or not
     * @return bool
     */
    virtual bool RequiresBlending() const
    {
      return true;
    }

    /**
     * @brief Query whether an image is y-inverted.
     *
     * @return true if an image is y-inverted, otherwise false.
     */
    virtual bool IsYInverted() const
    {
      return true;
    }

    /**
     * Returns the internal pixel NativeImageInterface::PixelFormat of the NativeImageInterface
     * @return pixel format
     */
    virtual Pixel::Format GetPixelFormat() const
    {
      return Pixel::RGBA8888;
    }
  protected:
    ~TestNativeImageInterface() {}
};

#endif  //_UTC_DALI_FRAME_BUFFER_IMAGE_COMMON_H_
