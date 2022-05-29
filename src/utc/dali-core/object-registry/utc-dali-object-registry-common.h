#ifndef _UTC_DALI_OBJECT_REGISTRY_COMMON_H_
#define _UTC_DALI_OBJECT_REGISTRY_COMMON_H_

#include "dali-common.h"

#include <dali-toolkit/dali-toolkit.h>

using namespace Dali;
using namespace Toolkit;
#define SUITE_NAME  "OBJECT_REGISTRY_UTC"

// Global variable declaration
extern bool gDestroyedSignalVerified;  /** Check for Object destruction **/
extern bool gCreatedSignalVerified;    /** Check for Object Creation **/


//Helper function declaraton

/**Helper for Object destruction callback**/
void CbObjectRegistryDestroyed(const Dali::RefObject* objectPointer);

template<class T> void CbObjectRegistryCreated( BaseHandle object )
{
  T type = T::DownCast( object );
  if( type )
  {
    gCreatedSignalVerified = true;
    LOG_I( "Object is created.");
  }
}

template <class T> bool ObjectRegistryNewHelper()
{
  gDestroyedSignalVerified = false;
  gCreatedSignalVerified = false;

  ObjectRegistry objectRegistry = Stage::GetCurrent().GetObjectRegistry();
  DALI_CHECK_FALSE( !objectRegistry ,  "ObjectRegistry instance is not created successfully." );

  objectRegistry.ObjectCreatedSignal().Connect( &CbObjectRegistryCreated<T> );
  objectRegistry.ObjectDestroyedSignal().Connect( &CbObjectRegistryDestroyed );

  //Object will be created inside the scope
  {
    T typeT = T::New();
    DALI_CHECK_FALSE( !typeT ,  "Object Creation with New is failed" );

    DALI_CHECK_FALSE( !gCreatedSignalVerified, "ObjectRegistry::ObjectCreatedSignal() is failed." );
  }
  //Object will be destroyed outside the scope
  DALI_CHECK_FALSE( !gDestroyedSignalVerified ,  "ObjectRegistry::ObjectDestroyedSignal() is failed" );

  return true;
}
#endif  //_UTC_DALI_OBJECT_REGISTRY_COMMON_H_
