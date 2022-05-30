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
static void __job_service_start_cb(job_info_h job_info, void *user_data)
{
	/* Nothing */
}

static void __job_service_stop_cb(job_info_h job_info, void *user_data)
{
	/* Nothing */
}

/**************************End CallBack Functions**************************/

/**
 * @function 		ITs_job_scheduler_service_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_service_startup(void)
{
	int nRet;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	g_bJobSchedulerInit = true;

	nRet = job_scheduler_init();
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to initialize job scheduler \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
		return;
	}

	nRet = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to add job service \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
	}
}

/**
 * @function 		ITs_job_scheduler_service_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_scheduler_service_cleanup(void)
{
	int nRet  = JOB_ERROR_NONE;

	if (job_service)
	{
		nRet = job_scheduler_service_remove(job_service);
		PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_service_remove", JobGetError(nRet));
		job_service = NULL;
	}

	nRet = job_scheduler_finish();
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_finish", JobGetError(nRet));
}

//& type: auto
//& purpose: To add job service handler for receiving the information of the scheduled job.
/**
* @testcase 			ITc_job_scheduler_service_add
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds job service handler for receiving the information of the scheduled job.
* @scenario				Calls the job_scheduler_service_add().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_scheduler_service_add
* @passcase				Successfully adds job service handler.
* @failcase				Not able to add job service handler.
* @precondition			Job Scheduler must be initialised
* @postcondition		NA
*/
int ITc_job_scheduler_service_add(void)
{
	START_TEST;

	int nRet;
	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	nRet = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_service_add", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To remove registered job service handler.
/**
* @testcase 			ITc_job_scheduler_service_remove
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Removes registered job service handler.
* @scenario				Calls the job_scheduler_service_remove().
*						Checks whether the return value is JOB_ERROR_NONE or NOT
* @apicovered			job_scheduler_service_remove
* @passcase				Successfully removes registered job service handler.
* @failcase				Not able to remove registered job service handler.
* @precondition			Job Scheduler must be initialised
* @postcondition		NA
*/
int ITc_job_scheduler_service_remove(void)
{
	START_TEST;

	int nRet;

	nRet = job_scheduler_service_remove(job_service);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_scheduler_service_remove", JobGetError(nRet));

	job_service_callback_s callbacks = {
		.start = __job_service_start_cb,
		.stop = __job_service_stop_cb
	};

	nRet = job_scheduler_service_add(JOB_ID, &callbacks, NULL, &job_service);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_service_add", JobGetError(nRet));

	return 0;
}

/** @} */
/** @} */
