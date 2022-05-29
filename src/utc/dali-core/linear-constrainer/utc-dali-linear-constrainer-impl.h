#include "utc-dali-linear-constrainer-common.h"

Actor gActorLc;
int gRenderCountLinearConstrainer;
Dali::LinearConstrainer gLinearConstrainer;
Property::Index gIndexLC;
float gStartLC  = 0.0f;
float gTargetLC = 1.0f;


void LinearConstrainerNewP()
{
  Dali::LinearConstrainer linearConstrainer;
  linearConstrainer = Dali::LinearConstrainer::New();
  DALI_CHECK_FAIL( !linearConstrainer,"Default LinearConstrainer instance is not null.");

  DaliLog::PrintPass();
}


void LinearConstrainerConstructorP()
{
  Dali::LinearConstrainer linearConstrainer;
  DALI_CHECK_FAIL(linearConstrainer,"Default LinearConstrainer instance is  null.");

  DaliLog::PrintPass();
}

void LinearConstrainerCopyConstructorP()
{
  Dali::LinearConstrainer linearConstrainer;
  DALI_CHECK_FAIL( linearConstrainer,"Default LinearConstrainer instance is not null.");

  linearConstrainer = Dali::LinearConstrainer::New();
  DALI_CHECK_FAIL( !linearConstrainer,"LinearConstrainer::New() is failed.");

  Dali::LinearConstrainer linearConstrainerCopy( linearConstrainer );
  DALI_CHECK_FAIL( linearConstrainerCopy != linearConstrainer,"LinearConstrainer copy constructor is failed.");

  Dali::LinearConstrainer linearConstrainerAssign = linearConstrainer;
  DALI_CHECK_FAIL( linearConstrainerAssign != linearConstrainer,"LinearConstrainer::operator= is failed.");

  DaliLog::PrintPass();
}


void LinearConstrainerOperatorAssignmentP()
{
  Dali::LinearConstrainer linearConstrainer;
  linearConstrainer = Dali::LinearConstrainer::New();
  DALI_CHECK_FAIL( !linearConstrainer,"Default LinearConstrainer instance is not null.");

  Dali::LinearConstrainer linearConstrainerAssign;
  linearConstrainerAssign = linearConstrainer;
  DALI_CHECK_FAIL( linearConstrainerAssign != linearConstrainer,"LinearConstrainer::operator= is failed.");

  DaliLog::PrintPass();
}

void LinearConstrainerDowncastP()
{
  Dali::LinearConstrainer linearConstrainer = Dali::LinearConstrainer::New();
  DALI_CHECK_FAIL( !linearConstrainer,"LinearConstrainer::New() is failed.");

  BaseHandle handle( linearConstrainer );
  DALI_CHECK_FAIL( !handle,"BaseHandle instance is not created with LinearConstrainer.");

  Dali::LinearConstrainer linearConstrainerDown = Dali::LinearConstrainer::DownCast( handle );
  DALI_CHECK_FAIL( !linearConstrainerDown,"LinearConstrainer::Downcast is failed.");

  DaliLog::PrintPass();
}

void LinearConstrainerDowncastN()
{
  Dali::LinearConstrainer linearConstrainer;
  DALI_CHECK_FAIL(linearConstrainer,"Default LinearConstrainer instance is  null.");

  BaseHandle handle ( linearConstrainer );
  DALI_CHECK_FAIL( handle,"BaseHandle instance is not created with LinearConstrainer.");

  Dali::LinearConstrainer linearConstrainerDown = Dali::LinearConstrainer::DownCast( handle );
  DALI_CHECK_FAIL( linearConstrainerDown,"LinearConstrainer::Downcast is failed.");

  DaliLog::PrintPass();
}


void LinearConstrainerApplyRemoveP()
{
  gActorLc = Dali::Actor::New();
  DALI_CHECK_FAIL(!gActorLc,"Actor creation is failed.");

  // Register a float property
  gIndexLC = gActorLc.RegisterProperty( "t", gStartLC );
  Dali::Stage::GetCurrent().Add(gActorLc);

  //Create a LinearConstrainer without specifying progress for values
  gLinearConstrainer = Dali::LinearConstrainer::New();
  DALI_CHECK_FAIL(!gLinearConstrainer,"linearConstrainer creation is failed.");

  LinearConstrainerSetupUniformProgress( gLinearConstrainer );

  //Apply the linear constraint to the actor's position. The source property for the constraint will be the custom property "t"
  Vector2 range( gStartLC, gTargetLC );
  gLinearConstrainer.Apply( Property(gActorLc,Dali::Actor::Property::POSITION_X), Property(gActorLc,gIndexLC), range );

  //Create an animation to animate the custom property
  float durationSeconds(gTargetLC);
  Dali::Animation animation = Dali::Animation::New(durationSeconds);
  animation.AnimateTo(Dali::Property(gActorLc,gIndexLC),gTargetLC);
  animation.Play();
}

void VTLinearConstrainerApplyRemove001()
{
  bool bValueCheck = (gActorLc.GetCurrentPosition().x > gStartLC) && (gActorLc.GetCurrentPosition().x <= gTargetLC/2.0f);
  DALI_CHECK_FAIL( !bValueCheck, "LinearConstrainer Apply is not work properly. Set Position is mismatched.");
}
void VTLinearConstrainerApplyRemove002()
{
  bool bValueCheck = (gActorLc.GetCurrentPosition().x > gTargetLC/2.0f) && (gActorLc.GetCurrentPosition().x <= gTargetLC);
  DALI_CHECK_FAIL( !bValueCheck, "LinearConstrainer Apply is not work properly. Set Position is mismatched.");
}
void VTLinearConstrainerApplyRemove003()
{
  bool bValueCheck = (gActorLc.GetCurrentPosition().x > gStartLC) && (gActorLc.GetCurrentPosition().x < gTargetLC);
  DALI_CHECK_FAIL( !bValueCheck, "LinearConstrainer Apply is not work properly. Set Position is mismatched.");
}
void VTLinearConstrainerApplyRemove004()
{
  bool bValueCheck = (gActorLc.GetCurrentPosition().x >= gStartLC) && (gActorLc.GetCurrentPosition().x < gTargetLC/2.0f);
  DALI_CHECK_FAIL( !bValueCheck, "LinearConstrainer Apply is not work properly. Set Position is mismatched.");
}
void VTLinearConstrainerApplyRemove005()
{
  DALI_CHECK_FAIL( gActorLc.GetCurrentPosition().x != gStartLC,"LinearConstrainer Apply is not work properly. Set Position is mismatched.");

  gLinearConstrainer.Remove(gActorLc);
  gActorLc.SetProperty(gIndexLC,0.75f);
}
void VTLinearConstrainerApplyRemove006()
{
  DALI_CHECK_FAIL( gActorLc.GetCurrentPosition().x != gStartLC,"LinearConstrainer::Remove operation is failed for non-specifying progress value.");

  Dali::Stage::GetCurrent().Remove(gActorLc);
  DaliLog::PrintPass();
}

