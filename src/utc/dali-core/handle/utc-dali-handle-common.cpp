#include "utc-dali-handle-common.h"

/**Global variable definition*/
bool gHandleException = false;

/**
 * @function    HandleAddActor
 * @description Add new Actor
 * @param[out]  actor [reference of Actor instance]
 * @param[out]  stage [reference of Stage instance]
 * @returnint   The actual time passed in milliseconds
 */
bool HandleAddActor(Actor& actor, Stage& stage)
{
  stage = Stage::GetCurrent();
  DALI_CHECK_FALSE(!stage, "stage is not created.");
  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, "actor is not created.");
  stage.Add(actor);
  return true;
}

/**
 * @function     HandleRegisterProperty
 * @description  Test for varrying the input parameter
 * @param[in]    stage [Handle to the Stage]
 * @param[in]    actor [Handle to the Actor]
 * @param[in]    handleobject [Handle to the HandleOBJECT]
 * @param[in]    index [Handle to the  Property::Index]
 * @param[in]    value [Handle to the Property::Value]
 * @param[in]    pstrName[string]
 * @param[in]    HandleRegisterPropertyOption [RegisterPropertyOption enum ]
 * @param[in]    accessMode [Handle to Property::AccessMode]
 * @return       True/False
 */
bool HandleRegisterProperty(Stage stage,Actor actor,Handle handleobject, Property::Index index, string *pstrName,Property::Value value, HandleRegisterPropertyOption RegisterPropertyOption, Property::AccessMode accessMode)
{

  int ncount = 0, ncount2 = 0;
  gHandleException = false;
  actor = Actor::New();
  DALI_CHECK_FALSE(!actor, "actor is not created.");
  stage.Add(actor);
  handleobject = actor;
  DALI_CHECK_FALSE(!handleobject, "handleobject is not created.");

  DALI_CHECK_FALSE(handleobject.GetPropertyIndex(*pstrName) != Property::INVALID_INDEX, "Before Register Property Property Index should be Invalid But  There is a Property");
  ncount2 = handleobject.GetPropertyCount();
  ncount= ncount2+1;

  (*pstrName).append("add");
  try
  {
    RegisterPropertyOption == REGISTERPROPERTY_WITHOUT_ACCESSMODE ? index = handleobject.RegisterProperty((*pstrName), value): index = handleobject.RegisterProperty((*pstrName), value,accessMode);
  }
  catch (Dali::DaliException& e)
  {
    gHandleException = true;
    stage.Remove(actor);
    return true;
  }

  DALI_CHECK_FALSE(handleobject.GetPropertyIndex((*pstrName)) != index , "ITcHandleRegisterProperty failed.");
  handleobject.SetProperty (index, value);

  ncount2 = handleobject.GetPropertyCount();

  DALI_CHECK_FALSE(ncount2 != ncount , "ITcHandleRegisterProperty failed.");

  stage.Remove(actor);
  return true;
}

