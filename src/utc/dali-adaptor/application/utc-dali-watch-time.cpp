#include "utc-dali-application-common.h"
#include "public-api/dali-wearable.h"
#include <appcore-watch/watch_app.h>
#include <stdlib.h>
#include <string.h>
#define TIMEZONE_BUFFER_MAX 1024

extern int gArgc;
extern char ** gArgv;
extern int test_return_value;

/**y
 * @function        utc_dali_watchtime_startup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_dali_watchtime_startup(void)
{
  test_return_value=0;
}

/**
 * @function        utc_dali_watchtime_cleanup
 * @description     Called after each test
 * @parameter       NA
 * @return          NA
 */
void utc_dali_watchtime_cleanup(void)
{
}

void WatchTimeNew();
void WatchTimeGetHour();
void WatchTimeGetHour24();
void WatchTimeGetMinute();
void WatchTimeGetSecond();
void WatchTimeGetMillisecond();
void WatchTimeGetYear();
void WatchTimeGetMonth();
void WatchTimeGetDay();
void WatchTimeGetDayOfWeek();
void WatchTimeGetUtcTime();
void WatchTimeGetUtcTimeStamp();
void WatchTimeGetTimeZone();
void WatchTimeGetDaylightSavingTimeStatus();

namespace
{
  enum TEST_CASES_LIST_WATCH
  {
    WATCH_TIME_NEW,
    WATCH_GET_HOUR,
    WATCH_GET_HOUR24,
    WATCH_GET_MINUTE,
    WATCH_GET_SECOND,
    WATCH_GET_MILLISECOND,
    WATCH_GET_YEAR,
    WATCH_GET_MONTH,
    WATCH_GET_DAY,
    WATCH_GET_DAY_OF_WEEK,
    WATCH_GET_UTC_TIME,
    WATCH_GET_UTC_TIME_STAMP,
    WATCH_GET_TIME_ZONE,
    WATCH_GET_DAYLIGHT_SAVING_TIME_STATUS
  };

  class WatchTime_TestApp : public ConnectionTracker
  {
  public:
    WatchTime_TestApp( WatchApplication& app, int test_case)
    : initCalled( false ),
      mApplication( app ),
      mTestCase( test_case )
    {
      mApplication.InitSignal().Connect( this, &WatchTime_TestApp::Create );
    }

  private:
    void Create(Application& app)
    {
      initCalled = true;

      mTimer = Timer::New( INTERVAL );
      mTimer.TickSignal().Connect( this, &WatchTime_TestApp::Tick );
      mTimer.Start();

      ExcuteTest();
      Quit();
    }

    void ExcuteTest()
    {
      switch (mTestCase)
      {
        case WATCH_TIME_NEW:
          WatchTimeNew();
          break;
        case WATCH_GET_HOUR:
          WatchTimeGetHour();
          break;
        case WATCH_GET_HOUR24:
          WatchTimeGetHour24();
          break;
        case WATCH_GET_MINUTE:
          WatchTimeGetMinute();
          break;
        case WATCH_GET_SECOND:
          WatchTimeGetSecond();
          break;
        case WATCH_GET_MILLISECOND:
          WatchTimeGetMillisecond();
          break;
        case WATCH_GET_YEAR:
          WatchTimeGetYear();
          break;
        case WATCH_GET_MONTH:
          WatchTimeGetMonth();
          break;
        case WATCH_GET_DAY:
          WatchTimeGetDay();
          break;
        case WATCH_GET_DAY_OF_WEEK:
          WatchTimeGetDayOfWeek();
          break;
        case WATCH_GET_UTC_TIME:
          WatchTimeGetUtcTime();
          break;
        case WATCH_GET_UTC_TIME_STAMP:
          WatchTimeGetUtcTimeStamp();
          break;
	case WATCH_GET_TIME_ZONE:
          WatchTimeGetTimeZone();
          break;
        case WATCH_GET_DAYLIGHT_SAVING_TIME_STATUS:
          WatchTimeGetDaylightSavingTimeStatus();
          break;
      }
    }

    void Quit()
    {
      mApplication.Quit();
    }

    bool Tick()
    {
      mTimer.Stop();
      mApplication.Quit();
      return true;
    }

    // Data
    bool initCalled;
    WatchApplication&  mApplication;
    int mTestCase;

    Timer mTimer;
  };

} // unnamed namespace

void WatchTimeNew()
{
  WatchTime watchTime;
  WatchTime *watchTimeRef = &watchTime;

  DALI_CHECK_FAIL( !watchTimeRef, "WatchTime() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetHour()
{
  int ret, hour;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);

  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetHour() has failed." );

  ret = watch_time_get_hour(watch_time, &hour);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetHour() has failed." );

  DALI_CHECK_FAIL(watchTime.GetHour() != hour, "WatchTime() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetHour24()
{
  int ret, hour24;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetHour24() has failed." );

  ret = watch_time_get_hour24(watch_time, &hour24);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetHour24() has failed." );

  DALI_CHECK_FAIL(watchTime.GetHour24() != hour24, "WatchTimeGetHour24() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetMinute()
{
  int ret, minute;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetMinute() has failed." );

  ret = watch_time_get_minute(watch_time, &minute);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetMinute() has failed." );

  DALI_CHECK_FAIL(watchTime.GetMinute() != minute, "WatchTimeGetMinute() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetSecond()
{
  int ret, second;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetSecond() has failed." );

  ret = watch_time_get_second(watch_time, &second);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetSecond() has failed." );

  DALI_CHECK_FAIL(watchTime.GetSecond() != second, "WatchTimeGetSecond() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetMillisecond()
{
  WatchTime watchTime;

  // Comparison of Millisecond is very difficult to catch the moment.
  DALI_CHECK_FAIL( watchTime.GetMillisecond() < 0, "WatchTimeGetMillisecond() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetYear()
{
  int ret, year;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetYear() has failed." );

  ret = watch_time_get_year(watch_time, &year);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetYear() has failed." );

  DALI_CHECK_FAIL(watchTime.GetYear() != year, "WatchTimeGetYear() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetMonth()
{
  int ret, month;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetMonth() has failed." );

  ret = watch_time_get_month(watch_time, &month);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetMonth() has failed." );
  DALI_CHECK_FAIL(watchTime.GetMonth() != month, "WatchTimeGetMonth() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetDay()
{
  int ret, day;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDay() has failed." );

  ret = watch_time_get_day(watch_time, &day);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDay() has failed." );
  DALI_CHECK_FAIL(watchTime.GetDay() != day, "WatchTimeGetDay() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetDayOfWeek()
{
  int ret, dayOfWeek;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDayOfWeek() has failed." );

  ret = watch_time_get_day_of_week(watch_time, &dayOfWeek);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDayOfWeek() has failed." );
  DALI_CHECK_FAIL(watchTime.GetDayOfWeek() != dayOfWeek, "WatchTimeGetDayOfWeek() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetUtcTime()
{
  int ret;
  struct tm *utcTime = (struct tm *)calloc( 1, sizeof( struct tm ) );
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetUtcTime() has failed." );

  ret = watch_time_get_utc_time(watch_time, utcTime);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetUtcTime() has failed." );
  DALI_CHECK_FAIL(watchTime.GetUtcTime().tm_sec != (*utcTime).tm_sec, "WatchTimeGetUtcTime() has failed." );

  free( utcTime );
  DaliLog::PrintPass();
}

void WatchTimeGetUtcTimeStamp()
{
  int ret;
  time_t *timeStamp = (time_t *)calloc( 1, sizeof( time_t ) );
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetUtcTimeStamp() has failed." );

  ret = watch_time_get_utc_timestamp(watch_time, timeStamp);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetUtcTimeStamp() has failed." );
  DALI_CHECK_FAIL(watchTime.GetUtcTimeStamp() != *timeStamp, "WatchTimeGetUtcTimeStamp() has failed.");

  free( timeStamp );
  DaliLog::PrintPass();
}

void WatchTimeGetTimeZone()
{
  int ret;
  char *timeZone[TIMEZONE_BUFFER_MAX] = {0,};
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetTimeZone() has failed." );

  ret = watch_time_get_time_zone(watch_time, timeZone);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetTimeZone() has failed." );

  DALI_CHECK_FAIL( strcmp( watchTime.GetTimeZone(), *timeZone ) != 0, "WatchTimeGetTimeZone() has failed." );

  DaliLog::PrintPass();
}

void WatchTimeGetDaylightSavingTimeStatus()
{
  int ret;
  bool daylight;
  WatchTime watchTime;
  watch_time_h watch_time = {0,};

  ret = watch_time_get_current_time(&watch_time);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDaylightSavingTimeStatus() has failed." );

  ret = watch_time_get_dst_status(watch_time, &daylight);
  DALI_CHECK_FAIL(ret != APP_ERROR_NONE, "WatchTimeGetDaylightSavingTimeStatus() has failed." );
  DALI_CHECK_FAIL(watchTime.GetDaylightSavingTimeStatus() != daylight, "WatchTimeGetDaylightSavingTimeStatus() has failed." );

  DaliLog::PrintPass();
}

int UtcDaliWatchTimeTest(int testMode)
{
  DaliLog::PrintExecStarted(SUITE_NAME, __FUNCTION__);

  WatchApplication application = WatchApplication::New( &gArgc, &gArgv );
  CHECK_GL;
  WatchTime_TestApp testApp( application, testMode);
  application.MainLoop();
  return test_return_value;
}

int UtcDaliWatchTimeNew(void)
{
  return UtcDaliWatchTimeTest(WATCH_TIME_NEW);
}

int UtcDaliWatchTimeGetHour(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_HOUR);
}

int UtcDaliWatchTimeGetHour24(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_HOUR24);
}

int UtcDaliWatchTimeGetMinute(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_MINUTE);
}

int UtcDaliWatchTimeGetSecond(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_SECOND);
}

int UtcDaliWatchTimeGetMillisecond(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_MILLISECOND);
}

int UtcDaliWatchTimeGetYear(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_YEAR);
}

int UtcDaliWatchTimeGetMonth(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_MONTH);
}

int UtcDaliWatchTimeGetDay(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_DAY);
}

int UtcDaliWatchTimeGetDayOfWeek(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_DAY_OF_WEEK);
}

int UtcDaliWatchTimeGetUtcTime(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_UTC_TIME);
}

int UtcDaliWatchTimeGetUtcTimeStamp(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_UTC_TIME_STAMP);
}

int UtcDaliWatchTimeGetTimeZone(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_TIME_ZONE);
}

int UtcDaliWatchTimeGetDaylightSavingTimeStatus(void)
{
  return UtcDaliWatchTimeTest(WATCH_GET_DAYLIGHT_SAVING_TIME_STATUS);
}
