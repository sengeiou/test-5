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
 * @function 		ITs_job_info_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_info_startup(void)
{
	int nRet = job_info_create(&job_info);
	g_bJobSchedulerInit = true;

	if (!job_info || nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to create job info \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
	}
}

/**
 * @function 		ITs_job_info_cleanup
 * @description	 	Called before after test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_info_cleanup(void)
{
	int nRet = JOB_ERROR_NONE;

	if (job_info)
	{
		nRet = job_info_destroy(job_info);
		PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));
		job_info = NULL;
	}
}

/** @addtogroup itc-job-scheduler
*  @brief 		Integration testcases for module job-scheduler
*  @ingroup 	itc-job-scheduler
*  @{
*/

//& type: auto
//& purpose: To create the job info handle
/**
* @testcase 			ITc_job_info_create_destroy
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Creates the job info handle.
* @scenario				Check whether the result is JOB_ERROR_NONE or NOT.
* @apicovered			job_info_create, job_info_destroy
* @passcase				Job info handle is created and destroyed successfully.
* @failcase				Job info handle is not created/destroyed successfully.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_create_destroy(void)
{
	START_TEST;

	int nRet = job_info_destroy(job_info);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));

	nRet = job_info_create(&job_info);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_create", JobGetError(nRet));
	if (!job_info)
	{
		FPRINTF("[Line: %d][%s] Job info is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = job_info_destroy(job_info);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));

	nRet = job_info_create(&job_info);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_create", JobGetError(nRet));
	if (!job_info)
	{
		FPRINTF("[Line: %d][%s] Job info is NULL \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose: To set the periodic interval to the job handle.
/**
* @testcase 			ITc_job_info_set_periodic
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets the periodic interval to the job handle.
* @scenario				Sets the periodic interval(30 minutes) to the job handle.
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_info_set_periodic
* @passcase				Periodic interval is successfully set to given value.
* @failcase				Periodic interval is not successfully set to given value.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_set_periodic(void)
{
	START_TEST;

	int nRet = job_info_set_periodic(job_info, 30);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_periodic", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the job to be automatically scheduled after the device reboots.
/**
* @testcase 			ITc_job_info_set_persistent
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets the job to be automatically scheduled after the device reboots.
* @scenario				Calls the job_info_set_persistent() with "true" flag.
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the persistent parameter is true, the job will be scheduled
*						automatically after the device reboots.
* @apicovered			job_info_set_persistent
* @passcase				Job is automatically scheduled after the device reboots.
* @failcase				Job is not automatically scheduled after the device reboots.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_set_persistent(void)
{
	START_TEST;

	int nRet = job_info_set_persistent(job_info, true);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_persistent", JobGetError(nRet));

	nRet = job_info_set_persistent(job_info, false);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_persisten", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the job not to be repeated.
/**
* @testcase 			ITc_job_info_set_once
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets the job not to be repeated.
* @scenario				Calls the job_info_set_once().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the once parameter is "true", the job will not be repeated.
* @apicovered			job_info_set_once
* @passcase				If the once parameter is "true", the job is not be repeated.
* @failcase				If the once parameter is "true", the job is repeated.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_set_once(void)
{
	START_TEST;

	int nRet = job_info_set_once(job_info, true);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_once", JobGetError(nRet));

	nRet = job_info_set_once(job_info, false);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_once", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To set the timeout interval of the requirements.
/**
* @testcase 			ITc_job_info_set_requirement_timeout
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets the timeout interval of the requirements.
* @scenario				Sets the timeout interval(500ms) of the requirements to
*						the job info handle.
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the requirements are not ready within the interval when
*						triggering the events, the job will not be launched.
* @apicovered			job_info_set_requirement_timeout
* @passcase				If the requirements are not ready within the interval when
*						triggering the events, the job is not launched.
* @failcase				Even if the requirements are not ready within the interval
*						when triggering the events, the job is launched.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_set_requirement_timeout(void)
{
	START_TEST;

	int nRet = job_info_set_requirement_timeout(job_info, 500);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_requirement_timeout", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: To clone the given job_info handle.
/**
* @testcase 			ITc_job_info_clone
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Clones the given job_info handle.
* @scenario				Calls the job_info_clone().
*						Checks whether the return values are the expected results or NOT.
* @apicovered			job_info_clone, job_info_destroy
* @passcase				Successfully clones the given job_info handle.
* @failcase				Not able to clone the given job_info handle.
* @precondition			Job must be created.
* @postcondition		NA
*/
int ITc_job_info_clone(void)
{
	START_TEST;

	int nRet;
	job_info_h clone = NULL;

	nRet = job_info_clone(job_info, &clone);
	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_clone", JobGetError(nRet));

	if(!clone)
	{
		FPRINTF("[Line : %d][%s] Clone is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = job_info_destroy(clone);
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));

	return 0;
}

/** @} */
/** @} */
