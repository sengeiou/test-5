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

/**
 * @function 		ITs_job_scheduler_schedule_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_schedule_startup(void)
{
	int nRet;
	g_bJobSchedulerInit = true;

	nRet = job_scheduler_init();
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to initialized job scheduler \\n", __LINE__, API_NAMESPACE);
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
}

/**
 * @function 		ITs_job_scheduler_schedule_cleanup
 * @description	 	Called before after test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_schedule_cleanup(void)
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

//& type: auto
//& purpose: To schedule the job.
/**
* @testcase 			ITc_job_scheduler_init_finish
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Schedules the job.
* @scenario				Calls the job_scheduler_schedule().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_scheduler_init, job_scheduler_finish
* @passcase				Successfully schedules the job.
* @failcase				Not able to schedule the job.
* @precondition			Job Scheduler must be initialised and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_init_finish(void)
{
	START_TEST;

	int nRet;

	nRet = job_scheduler_init();
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_init", JobGetError(nRet));

	nRet = job_scheduler_finish();
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_finish", JobGetError(nRet));

	nRet = job_scheduler_init();
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_init", JobGetError(nRet));

	nRet = job_scheduler_schedule(job_info, JOB_ID);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_schedule", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To schedule the job.
/**
* @testcase 			ITc_job_scheduler_schedule
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Schedules the job.
* @scenario				Calls the job_scheduler_schedule().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_scheduler_schedule
* @passcase				Successfully schedules the job.
* @failcase				Not able to schedule the job.
* @precondition			Job Scheduler must be initialised and set periodic
* @postcondition		NA
*/
int ITc_job_scheduler_schedule(void)
{
	START_TEST;

	int nRet = job_scheduler_schedule(job_info, JOB_ID);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_schedule", JobGetError(nRet));

	return 0;
}

/** @} */
/** @} */
