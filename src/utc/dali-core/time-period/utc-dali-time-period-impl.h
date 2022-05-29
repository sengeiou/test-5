#include "utc-dali-time-period-common.h"

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

Actor gActorTimePeriod;            /**Actor instance*/
Property::Index gIndexTimePeriod;    /**Property index*/
int gRenderCountTimePeriod;        /**Render count*/


/**
 * ##############################
 * TC Logic Implementation Area.
 * ##############################
 **/
void TimePeriodWithDurationSeconds()
{
  float fDuration = 1.1f;
  Animation animation;
  Property::Index index;

  DALI_CHECK_FAIL( !TimePeriodActorAnimationNew( gActorTimePeriod, animation, F_START, fDuration, index ) , "Unable to create actor, animation, register property to actor and connect animation to functor");

  TimePeriodSetPropertyDuration( gActorTimePeriod, animation, F_START, fDuration, index );

  TimePeriod timePeriod( fDuration );

  DALI_CHECK_FAIL( timePeriod.durationSeconds != fDuration , "TimePeriod::TimePeriod is failed to create time period");

  TimePeriodAnimPlay( gActorTimePeriod, animation, F_START, F_TARGET, index, timePeriod );
}

void VTTimePeriodWithDurationSeconds001()
{
  // Checking signal finished before time period
  DALI_CHECK_FAIL( gSignalAfterTime , "Finish signal should not be received before time period is over");
}

void VTTimePeriodWithDurationSeconds002()
{
  // Checking signal finished at time period
  DALI_CHECK_FAIL( gSignalAfterTime , "Finish signal should not be received just at time period.");
}

void VTTimePeriodWithDurationSeconds003()
{
  //Checking signal beyond time period
  DALI_CHECK_FAIL( !gSignalAfterTime , "Finish signal should be received after time period");
  Stage::GetCurrent().Remove( gActorTimePeriod );
  DaliLog::PrintPass();
}

void TimePeriodWithDelayDurationSeconds()
{
  float fDuration = 1.2f, fDelay = 0.6f;
  Animation animation;

  DALI_CHECK_FAIL( !TimePeriodActorAnimationNew( gActorTimePeriod, animation, F_START, fDuration, gIndexTimePeriod ) , "Unable to create actor, animation, register property to actor and connect animation to functor");

  TimePeriodSetPropertyDuration( gActorTimePeriod, animation, F_START, fDuration, gIndexTimePeriod );

  TimePeriod timePeriod( fDelay, ( fDuration - fDelay ) );

  DALI_CHECK_FAIL( timePeriod.delaySeconds != fDelay , "TimePeriod::TimePeriod is failed to create time period as delaySeconds is not matched to set value");

  DALI_CHECK_FAIL( timePeriod.durationSeconds != ( fDuration - fDelay ) , "TimePeriod::TimePeriod is failed to create time period as durationSeconds is not matched to set value");

  TimePeriodAnimPlay( gActorTimePeriod, animation, F_START, F_TARGET, gIndexTimePeriod, timePeriod );
}

void VTTimePeriodWithDelayDurationSeconds001()
{
  DALI_CHECK_FAIL( gSignalAfterTime , "Finish signal should not be received at delay time");
  DALI_CHECK_FAIL( gActorTimePeriod.GetProperty< float >( gIndexTimePeriod ) != F_TARGET , "Property should be updated");
}

void VTTimePeriodWithDelayDurationSeconds002()
{
  DALI_CHECK_FAIL( gSignalAfterTime , "Finish signal not should be received before time period is over");
}

void VTTimePeriodWithDelayDurationSeconds003()
{
  DALI_CHECK_FAIL( gActorTimePeriod.GetProperty<float>( gIndexTimePeriod ) != F_TARGET , "Animator progress should be completed after time period");
  DALI_CHECK_FAIL( !gSignalAfterTime, "Finish signal should be received after time period" );
  DaliLog::PrintPass();
}

/**
 * End of TC Logic Implementation Area.
 **/
