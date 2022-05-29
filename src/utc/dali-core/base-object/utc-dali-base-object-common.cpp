#include "utc-dali-base-object-common.h"

/**
 * @function          BaseObjectGetTypeNameInfo
 * @description       Retrieves type name and type info
 * @param[in]         baseHandle[ BaseHandle instance ]
 *
 * @return            bool checked
 */

bool BaseObjectGetTypeNameInfo( BaseHandle &baseHandle)
{
  string strGetName = "";
  TypeInfo typeInfo;
  bool bTypeCheck = false;

  strGetName = baseHandle.GetBaseObject().GetTypeName();
  DALI_CHECK_FALSE( strGetName.empty() , " BaseObject::GetTypeName() is failed" );

  typeInfo = TypeRegistry::Get().GetTypeInfo( strGetName );
  if( !typeInfo )
  {
    LOG_E(" TypeInfo instance is not created with the typeName returned by the BaseObject::GetTypeName()" );
    strGetName.clear();
    return false;
  }
  strGetName.clear();

  bTypeCheck = baseHandle.GetBaseObject().GetTypeInfo( typeInfo );
  if(!bTypeCheck)
  {
    LOG_E("BaseObject::GetTypeInfo() is failed to return type info with the type name returned by BaseObject::GetTypeName()" );
    typeInfo.Reset();
    return false;
  }

  typeInfo.Reset();

  return true;
}

