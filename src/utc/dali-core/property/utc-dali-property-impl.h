#include "utc-dali-property-common.h"

/**Property intance creation check */
bool gPropertyIntanceCheck = false;

/**Property animation check */
bool gPropertyCheckAnimation = false;
int gRenderCountProperty;
Animation gAnimationProperty;
Actor gActorProperty;


void PropertyWithPropertyName()
{
  gPropertyIntanceCheck = false;
  float fProgressInit = 0.0f, fProgressTarget = 1.0f;
  Vector3 vec3Init( Vector3::ONE ), vec3Target( 100.0f, 100.0f, 100.0f );

  gActorProperty = Actor::New();
  DALI_CHECK_FAIL(!gActorProperty, "Actor::New is failed .");

  Property property( gActorProperty, PROPERTY_NAME );
  gPropertyIntanceCheck = (property.object == gActorProperty) && ( property.propertyIndex == Actor::Property::POSITION );

  DALI_CHECK_FAIL( !gPropertyIntanceCheck, "Property(Handle&, const string&) is failed." );

  //Check whether the property is animated using created object+property pair
  gActorProperty.SetPosition( Vector3::ONE );
  Stage::GetCurrent().Add( gActorProperty );

  gAnimationProperty = Animation::New( PROPERTY_ANIMATION_TIME );
  DALI_CHECK_FAIL(!gAnimationProperty, "Animation::New is failed .");

  KeyFrames keyframes = KeyFrames::New();
  DALI_CHECK_FAIL(!keyframes, "KeyFrames::New is failed .");
  keyframes.Add( fProgressInit, vec3Init);
  keyframes.Add( fProgressTarget, vec3Target );

  gAnimationProperty.AnimateBetween( property, keyframes, AlphaFunction::LINEAR);
  gAnimationProperty.Play();

  DaliLog::PrintPass();
}
void VTPropertyWithPropertyName001()
{
  Vector3 vec3Target( 100.0f, 100.0f, 100.0f );
  DALI_CHECK_FAIL( gActorProperty.GetCurrentPosition() != vec3Target, "Property is not animated properly using created property instance.");

  gAnimationProperty.Clear();
  Stage::GetCurrent().Remove(gActorProperty);

  DaliLog::PrintPass();
}
void PropertyWithPropertyIndex()
{
  gPropertyIntanceCheck = false;
  gPropertyCheckAnimation = false;

  gActorProperty = Actor::New();
  DALI_CHECK_FAIL(!gActorProperty, "Actor::New is failed .");

  Property property( gActorProperty, Actor::Property::POSITION, PROPERTY_COMPONENT_INDEX );
  gPropertyIntanceCheck = (property.object == gActorProperty) && ( property.propertyIndex == Actor::Property::POSITION ) && (property.componentIndex == PROPERTY_COMPONENT_INDEX);

  DALI_CHECK_FAIL( !gPropertyIntanceCheck, "Property::Property(Handle& obj, Property::Index propIndex, int compIndex) is failed." );

  //Check whether the property is animated using created object+property pair

  gPropertyCheckAnimation = PropertyAnimationForPositionComponentX( gActorProperty, property );
  DALI_CHECK_FAIL( !gPropertyCheckAnimation, "Animation is not worked properly" );

  DaliLog::PrintPass();
}
void VTPropertyWithComponentIndex001()
{
  DALI_CHECK_FAIL( gActorProperty.GetCurrentPosition().x != gTarget, "Expected value is not found after animation.");
  Stage::GetCurrent().Remove(gActorProperty);
  DaliLog::PrintPass();
}
void PropertyWithNameComponentIndex()
{
  gPropertyIntanceCheck = false;
  gPropertyCheckAnimation = false;

  gActorProperty = Actor::New();
  DALI_CHECK_FAIL(!gActorProperty, "Actor::New is failed .");

  Property property( gActorProperty, PROPERTY_NAME, PROPERTY_COMPONENT_INDEX );
  gPropertyIntanceCheck = (property.object == gActorProperty) && ( property.propertyIndex == Actor::Property::POSITION ) && (property.componentIndex == PROPERTY_COMPONENT_INDEX);

  DALI_CHECK_FAIL( !gPropertyIntanceCheck, "Property::Property(Handle& obj, const std::string& propertyName, int compIndex) is failed." );

  //Check whether the property is animated using created object+property pair

  gPropertyCheckAnimation = PropertyAnimationForPositionComponentX(gActorProperty, property );
  DALI_CHECK_FAIL( !gPropertyCheckAnimation, "Animation is not worked properly" );

  DaliLog::PrintPass();
}
void PropertyWithPropertyIndexComponentIndex()
{
  gPropertyIntanceCheck = false;
  gPropertyCheckAnimation = false;

  gActorProperty = Actor::New();
  DALI_CHECK_FAIL(!gActorProperty, "Actor::New is failed .");

  Property property( gActorProperty, Actor::Property::POSITION, PROPERTY_COMPONENT_INDEX );
  gPropertyIntanceCheck = (property.object == gActorProperty) && ( property.propertyIndex == Actor::Property::POSITION ) && (property.componentIndex == PROPERTY_COMPONENT_INDEX);

  DALI_CHECK_FAIL( !gPropertyIntanceCheck, "Property::Property(Handle& obj, Property::Index propIndex, int compIndex) is failed." );

  //Check whether the property is animated using created object+property pair

  gPropertyCheckAnimation = PropertyAnimationForPositionComponentX( gActorProperty, property );
  DALI_CHECK_FAIL( !gPropertyCheckAnimation, "Animation is not worked properly" );

  DaliLog::PrintPass();
}
void VTPropertyWithNameComponentIndex001()
{
  DALI_CHECK_FAIL( gActorProperty.GetCurrentPosition().x != gTarget, "Expected value is not found after animation.");
  Stage::GetCurrent().Remove(gActorProperty);
  DaliLog::PrintPass();
}
