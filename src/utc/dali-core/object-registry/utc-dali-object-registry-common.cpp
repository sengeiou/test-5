#include "utc-dali-object-registry-common.h"

// Global variable definitions
bool gDestroyedSignalVerified = false;  /** Check for Object destruction **/
bool gCreatedSignalVerified = false;    /** Check for Object Creation **/


void CbObjectRegistryDestroyed( const Dali::RefObject* objectPointer )
{
  if(objectPointer)
  {
    gDestroyedSignalVerified = true;
    LOG_I( "Object is destroyed.");
  }
}
