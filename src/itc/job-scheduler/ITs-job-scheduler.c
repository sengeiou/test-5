//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-job-scheduler-common.h"

//& set: JobScheduler

/**************************CallBack Functions**************************

/** @addtogroup itc-job-scheduler
*  @brief 		Callbacks for job-scheduler
*  @ingroup itc-job-scheduler
*  @{
*/
static bool __foreach_job_cb(job_info_h job_info, void *user_data)
{
	int nRet;
	char *job_id = NULL;
	bool *exist = (bool *)user_data;

	nRet = job_info_get_job_id(job_info, &job_id);
	if (!job_id || nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Failed to get job id\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	if (strcmp(job_id, JOB_ID) == 0)
	{
		FPRINTF("[Line : %d][%s] %s exists\\n", __LINE__, API_NAMESPACE,job_id);
		exist = true;
	}

	free(job_id);

	return true;
}

/**************************End CallBack Functions**************************/

/**
 * @function 		ITs_job_scheduler_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_startup(void)
{
	int nRet;
	g_bJobSchedulerInit = true;

	nRet = job_scheduler_init();
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to initialize job scheduler \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
		return;
	}

	nRet = job_info_create(&job_info);
	if (!job_info || nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to create job info \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
		return;
	}

	nRet = job_info_set_periodic(job_info, 30);
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to set periodic internal \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
		return;
	}

	nRet = job_info_set_requires_battery_not_low(job_info, true);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_info_set_requires_battery_not_low", JobGetError(nRet));

	nRet = job_scheduler_schedule(job_info, JOB_ID);
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to schedule job \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
	}
}

/**
 * @function 		ITs_job_scheduler_cleanup
 * @description	 	Called before after test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_cleanup(void)
{
	int nRet = JOB_ERROR_NONE;

	nRet = job_scheduler_cancel(JOB_ID);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_cancel", JobGetError(nRet));

	if (job_info)
	{
		nRet  = job_info_destroy(job_info);
		PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));
		job_info = NULL;
	}

	nRet = job_scheduler_finish();
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_finish", JobGetError(nRet));
}

/** @addtogroup itc-job-scheduler
*  @brief 		Integration testcases for module job-scheduler
*  @ingroup 	itc-job-scheduler
*  @{
*/

//& type: auto
//& purpose: To get the ID of the job.
/**
* @testcase 			ITc_job_info_get_job_id
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Gets the ID of the job.
* @scenario				Calls the job_info_get_job_id().
*						Checks whether the return values are the expected results or NOT.
*						The ret should be JOB_ERROR_NONE and the job_is should be JOB_ID("TestJob").
* @apicovered			job_info_get_job_id
* @passcase				Successfully gets the ID of the job.
* @failcase				Not able to get the ID of the job.
* @precondition			Job Scheduler must be initialised, created and set periodic
* @postcondition		NA
*/
int ITc_job_info_get_job_id(void)
{
	START_TEST;

	int nRet;
	char *job_id = NULL;

	nRet = job_info_get_job_id(job_info, &job_id);

	if(!strcmp(job_id, JOB_ID))
		FPRINTF("[Line : %d][%s] Value Match job_id = %s	JOB_ID = %s\\n", __LINE__, API_NAMESPACE,job_id,JOB_ID);

	PRINT_RESULT_CLEANUP(JOB_ERROR_NONE, nRet, "job_info_get_job_id", JobGetError(nRet), job_id);

	return 0;
}

//& type: auto
//& purpose: To cancel the scheduled job.
/**
* @testcase 			ITc_job_scheduler_cancel
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Cancels the scheduled job.
* @scenario				Calls the job_scheduler_cancel().
*						Checks whether the return value JOB_ERORR_NONE or NOT.
* @apicovered			job_scheduler_cancel
* @passcase				Successfully cancels the scheduled job.
* @failcase				Not able to cancel the scheduled job.
* @precondition			Job Scheduler must be initialised, created and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_cancel(void)
{
	START_TEST;

	int nRet = job_scheduler_cancel(NULL);
	PRINT_RESULT(JOB_ERROR_INVALID_PARAMETER, nRet, "job_scheduler_cancel", JobGetError(nRet));

	nRet = job_scheduler_cancel(JOB_ID);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_cancel", JobGetError(nRet));

	nRet = job_scheduler_schedule(job_info, JOB_ID);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_schedule", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To cancel all scheduled jobs.
/**
* @testcase 			ITc_job_scheduler_cancel_all
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Cancels all scheduled jobs.
* @scenario				Calls the job_scheduler_cancel_all().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_scheduler_cancel_all
* @passcase				Successfully cancels all scheduled jobs.
* @failcase				Not able to cancel all scheduled job.
* @precondition			Job Scheduler must be initialised, created and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_cancel_all(void)
{
	START_TEST;

	int nRet = job_scheduler_cancel_all();
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_cancel_all", JobGetError(nRet));

	nRet = job_scheduler_schedule(job_info, JOB_ID);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_schedule", JobGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: To notify that the job is finished.
/**
* @testcase 			ITc_job_scheduler_notify_job_finished
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Notifies that the job is finished.
* @scenario				Calls the job_scheduler_notify_job_finished().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_scheduler_notify_job_finished
* @passcase				Successfully notifies that the job is finished.
* @failcase				Not able to notify that the job is finished.
* @precondition			Job Scheduler must be initialised, created and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_notify_job_finished(void)
{
	START_TEST;

	int nRet = job_scheduler_notify_job_finished(JOB_ID);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_notify_job_finished", JobGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: To retrieve all scheduled jobs.
/**
* @testcase 			ITc_job_scheduler_foreach_job
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Retrieves all scheduled jobs.
* @scenario				Calls the job_scheduler_foreach_job().
*						Checks whether the return values are the expected results or NOT.
*						The return value should be JOB_ERROR_NONE and the exist should be true.
* @apicovered			ob_info_get_job_id
* @passcase				Successfully retrieves all scheduled jobs.
* @failcase				Not able to retrieve all scheduled jobs.
* @precondition			Job Scheduler must be initialised, created and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_foreach_job(void)
{
	START_TEST;

	int nRet;
	bool exist = false;

	nRet = job_scheduler_foreach_job(__foreach_job_cb, &exist);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_foreach_job", JobGetError(nRet));

	if(exist)
		FPRINTF("[Line : %d][%s] True value for exists\\n", __LINE__, API_NAMESPACE);

	return 0;
}

/** @} */
/** @} */
