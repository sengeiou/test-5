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
#include "ITs-stc-common.h"
//& set: Stc

int g_bIsAPISuccess = 1;
/** @addtogroup itc-stc
*  @ingroup itc
*  @{
*/

/**
* @function			StcForeachStatsCallback
* @description		callback for stc_foreach_all_stats
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcForeachStatsCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	stc_stats_info_h hCloned = NULL;

	g_bIsAPISuccess = STC_ERROR_NONE;

	switch (g_eStatsInfo) {
	case STATS_INFO_FOREACH_ALL:
		{
			FPRINTF("[Line : %d][%s] Callback invoked stc_foreach_all_stats \\n", __LINE__, API_NAMESPACE);
			int nRet = stc_stats_info_clone(info, &hCloned);
			if(nRet != STC_ERROR_NONE || hCloned == NULL)
			{
				g_bIsAPISuccess = nRet;
				FPRINTF("[Line : %d][%s] stc_stats_info_clone API failed \\n", __LINE__, API_NAMESPACE);
				return STC_CALLBACK_CANCEL;
			}

			nRet = stc_stats_info_destroy(hCloned);
			if(nRet != STC_ERROR_NONE)
			{
				g_bIsAPISuccess = nRet;
				FPRINTF("[Line : %d][%s] stc_stats_info_destroy API failed \\n", __LINE__, API_NAMESPACE);
				return STC_CALLBACK_CANCEL;
			}
		}
		break;
	default:
		FPRINTF("[Line : %d][%s] Callback invoked StcForeachStatsCallback :default case \\n", __LINE__, API_NAMESPACE);
		break;
	}

	return STC_CALLBACK_CONTINUE;
}

/**
* @function			StcGetStatsFinishedCallback
* @description		callback for stc_get_all_stats
* @parameter		stc_error_e
* @parameter		stc_all_stats_info_h
* @parameter		void*
* @return			void
*/
void StcGetStatsFinishedCallback(stc_error_e result, stc_all_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	switch (g_eStatsInfo) {
	case STATS_INFO_GET_ALL:
		{
			g_iTargetApiCallback = result;
			FPRINTF("[Line : %d][%s] Callback invoked for STATS_INFO_GET_ALL\\n", __LINE__, API_NAMESPACE);
		}
		break;
	case STATS_INFO_FOREACH_ALL:
		{
			int nRet = stc_foreach_all_stats(info, StcForeachStatsCallback, user_data);
			g_iTargetApiCallback = nRet;
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_foreach_all_stats", StcGetError(nRet));
		}
		break;
	default:
		FPRINTF("[Line : %d][%s] StcGetStatsFinishedCallback Callback invoked:default case\\n", __LINE__, API_NAMESPACE);
		break;
	}

	QUIT_GMAIN_LOOP;
	return;
}

/**
* @function			StcStatsInfoGetAppIdCallback
* @description		callback for stc stats info to het App Id
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetAppIdCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(NULL != info)
		{
			char *app_id;

			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_app_id(info, &app_id);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_app_id", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				if(app_id != NULL)
				{
					g_bCallbackGetValue = true;
					FPRINTF("[Line : %d][%s] %s value returned = %s\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_app_id", app_id);
					FREE_MEMORY(app_id);
				}
				else
				{
					FPRINTF("[Line : %d][%s] %s failed, error returned = value returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_app_id");
				}
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_app_id");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetIfaceNameCallback
* @description		callback for stc stats info to get Iface Name
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetIfaceNameCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(NULL != info)
		{
			char *iface_name;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_iface_name(info, &iface_name);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_iface_name", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				if(iface_name != NULL)
				{
					g_bCallbackGetValue = true;
					FPRINTF("[Line : %d][%s] %s value returned = %s\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_iface_name", iface_name);
					FREE_MEMORY(iface_name);
				}
				else
				{
					g_bCallbackGetValue = false;
					FPRINTF("[Line : %d][%s] %s failed, error returned = value returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_iface_name");
				}
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_iface_name");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetTimeIntervalCallback
* @description		callback for stc stats info to get Time Interval
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetTimeIntervalCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(NULL != info)
		{
			time_t from;
			time_t to;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_time_interval(info, &from, &to);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_time_interval", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %ld\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_time_interval", (long)from);
				FPRINTF("[Line : %d][%s] %s value returned = %ld\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_time_interval", (long)to);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_time_interval");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetIfaceTypeCallback
* @description		callback for stc stats info to get Iface Type
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetIfaceTypeCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(NULL != info)
		{
			stc_iface_type_e iface_type;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_iface_type(info, &iface_type);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_iface_type", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %d\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_iface_type", iface_type);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_iface_type");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetCounterCallback
* @description		callback for stc stats info to get Counter
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetCounterCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(info != NULL)
		{
			int64_t incoming;
			int64_t outgoing;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_counter(info, &incoming, &outgoing);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_counter", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %lld\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_counter", incoming);
				FPRINTF("[Line : %d][%s] %s value returned = %lld\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_counter", outgoing);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_counter");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetRoamingTypeCallback
* @description		callback for stc stats info to get Roamimng Type
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetRoamingTypeCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(info != NULL)
		{
			stc_roaming_type_e roaming;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_roaming_type(info, &roaming);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_roaming_type", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %d\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_roaming_type", roaming);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_roaming_type");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetProtocolTypeCallback
* @description		callback for stc stats info to get protocol type
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetProtocolTypeCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(info != NULL)
		{
			stc_protocol_type_e prototype;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_protocol_type(info, &prototype);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_protocol_type", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %d\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_protocol_type", prototype);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_protocol_type");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcStatsInfoGetProcessStateCallback
* @description		callback for stc stats info to get process state
* @parameter		stc_error_e
* @parameter		stc_stats_info_h
* @parameter		void*
* @return			stc_callback_ret_e
*/
stc_callback_ret_e StcStatsInfoGetProcessStateCallback(stc_error_e result, stc_stats_info_h info, void *user_data)
{
	g_bCallbackCalled = true;
	FPRINTF("[Line : %d][%s] Callback invoked\\n", __LINE__, API_NAMESPACE);

	if (result == STC_ERROR_NONE) {
		if(info != NULL)
		{
			stc_process_state_e procstate;
			//Target API
			/**** Get App Id ****/
			int nRet = stc_stats_info_get_process_state(info, &procstate);
			PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_info_get_process_state", StcGetError(nRet));

			if(nRet == STC_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] %s value returned = %d\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_process_state", procstate);
				g_bCallbackGetValue = true;
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] %s can not be called as statistics information handle is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_info_get_process_state");
			g_bCallbackGetValue = true;
		}
	}

	QUIT_GMAIN_LOOP;
	return STC_CALLBACK_CANCEL;
}

/**
* @function			StcGetStatisticsInformation
* @description		Sets callback for statistics info APIl
* @parameter		void* user data
* @parameter		stc_stats_info_cb
* @return			int
*/
int StcGetStatisticsInformation(void *user_data, stc_stats_info_cb callback)
{
	time_t from, to;

	from = StcMakeTime(STC_YEAR, STC_MONTH, STC_DAY, STC_HOUR, STC_MIN);
	time(&to);

	int nRet = stc_stats_rule_set_time_interval(g_hRule, from, to);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_interval", StcGetError(nRet));

	nRet = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_app_id", StcGetError(nRet));

	g_bCallbackCalled = false;
	g_bCallbackGetValue = false;

	nRet = stc_foreach_stats(g_hSTC, g_hRule, callback, NULL);;
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_foreach_stats", StcGetError(nRet));

	RUN_GMAIN_LOOP;

	if(g_bCallbackCalled == false)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked for %s\\n", __LINE__, API_NAMESPACE, "stc_foreach_stats");
		return 1;
	}

	if(g_bCallbackGetValue == false)
	{
		return 1;
	}

	return 0;
}

/**
 * @function		ITs_stc_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void ITs_stc_startup(void)
{
	struct stat stBuff;
	int nRet;
	g_bStcMismatch = false;
	g_bStcNotSupported = false;
	g_bStcInit = false;
	g_bStcRuleCreation = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bFeatureSTC  = TCTCheckSystemInfoFeatureSupported(STC_FEATURE, API_NAMESPACE);
	g_hSTC = NULL;
	nRet = stc_initialize(&g_hSTC);

	if(!g_bFeatureSTC )
	{
		if(nRet == STC_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] stc_initialize() returned %s error for unsupported feature :success \\n", __LINE__,
				API_NAMESPACE, StcGetError(nRet));
			g_bStcNotSupported = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] stc_initialize() returned %s error for unsupported feature, error mismatch :Failure \\n",
			 __LINE__, API_NAMESPACE, StcGetError(nRet));
			g_bStcMismatch = true;
		}

		return;
	}

	if ( nRet == STC_ERROR_NONE)
	{
		if(g_hSTC == NULL)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_initialize");
			return;
		}

		g_bStcInit = true;
		FPRINTF("[Line : %d][%s] Stc handle created successfully\\n", __LINE__, API_NAMESPACE);

		g_hRule = NULL;
		nRet = stc_stats_rule_create(g_hSTC, &g_hRule);

		if(nRet == STC_ERROR_NONE)
		{
			if(g_hRule == NULL)
			{
				FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_create");
				return;
			}

			FPRINTF("[Line : %d][%s] Stc rule created successfully\\n", __LINE__, API_NAMESPACE);
			g_bStcRuleCreation = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] Unable to create Stc rule, error returned = %s\\n", __LINE__, API_NAMESPACE, StcGetError(nRet));
			g_bStcRuleCreation = false;
		}
	}
	else
	{
		FPRINTF("[Line : %d][%s] Unable to create Stc handle, error returned = %s\\n", __LINE__, API_NAMESPACE, StcGetError(nRet));
		g_bStcInit = false;
	}

	return;
}


/**
 * @function		ITs_stc_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return			NA
 */
void ITs_stc_cleanup(void)
{
	int nRet = STC_ERROR_NONE;

	if(g_bStcRuleCreation)
	{
		nRet = stc_stats_rule_destroy(g_hRule);
		PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_stats_rule_destroy", StcGetError(nRet));
	}

	if(g_bStcInit)
	{
		nRet = stc_deinitialize(g_hSTC);
		PRINT_RESULT_NORETURN(STC_ERROR_NONE, nRet, "stc_deinitialize", StcGetError(nRet));
	}

	return;
}

/** @addtogroup itc-stc-testcases
*  @brief		Integration testcases for module stc
*  @ingroup		itc-stc
*  @{
*/

//& purpose Initialize and DeInitialize STC
//& type: auto
/**
* @testcase				ITs_stc_initialize_deinitialize_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Initialize and Deinitialize
* @scenario				Initialize and DeInitialize\n
* @apicovered			stc_initialize, stc_deinitialize
* @passcase				If Initialize and Deinitialize successfully
* @failcase				If fails to Initialize and/or Deinitialize
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_initialize_deinitialize_p(void)
{
	CHECK_INIT;

	int nRet = STC_ERROR_NONE;

	nRet = stc_deinitialize(g_hSTC);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_deinitialize", StcGetError(nRet));

	g_hSTC = NULL;
	nRet = stc_initialize(&g_hSTC);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_initialize", StcGetError(nRet));

	if(g_hSTC == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_initialize");
		return 1;
	}

	nRet = stc_deinitialize(g_hSTC);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_deinitialize", StcGetError(nRet));

	g_hSTC = NULL;
	nRet = stc_initialize(&g_hSTC);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_initialize", StcGetError(nRet));

	if(g_hSTC == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_initialize");
		return 1;
	}

	return 0;
}

//& purpose Creates and destroy the statistics rule handle
//& type: auto
/**
* @testcase				ITs_stc_stats_rule_create_destroy_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Creates and destroy the statistics rule handle
* @scenario				Creates and destroy the statistics rule handle\n
* @apicovered			stc_stats_rule_create, stc_stats_rule_destroy
* @passcase				If Creates and/or destroy successfully
* @failcase				If fails to Creates and/or destroy Deinitialize
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_rule_create_destroy_p(void)
{
	START_TEST;

	int nRet = STC_ERROR_NONE;

	nRet = stc_stats_rule_destroy(g_hRule);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_destroy", StcGetError(nRet));

	g_hRule = NULL;
	nRet = stc_stats_rule_create(g_hSTC, &g_hRule);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_create", StcGetError(nRet));

	if(g_hRule == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_create");
		return 1;
	}

	nRet = stc_stats_rule_destroy(g_hRule);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_destroy", StcGetError(nRet));

	g_hRule = NULL;
	nRet = stc_stats_rule_create(g_hSTC, &g_hRule);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_create", StcGetError(nRet));

	if(g_hRule == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_create");
		return 1;
	}

	return 0;
}

//& purpose Sets and Gets the application ID for statistics rule
//& type: auto
/**
* @testcase				ITs_stc_stats_rule_set_get_app_id_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets and Gets the application ID for statistics rule
* @scenario				Sets and Gets the application ID for statistics rule \n
* @apicovered			stc_stats_rule_set_app_id, stc_stats_rule_get_app_id
* @passcase				If Sets and Gets the application ID successfully
* @failcase				If fails to Sets and/or Gets the application ID
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_rule_set_get_app_id_p(void)
{
	START_TEST;

	int nRet = STC_ERROR_NONE;
	char *app_id = NULL;

	nRet = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_app_id", StcGetError(nRet));

	nRet = stc_stats_rule_get_app_id(g_hRule, &app_id);
	PRINT_RESULT_CLEANUP(STC_ERROR_NONE, nRet, "stc_stats_rule_get_app_id", StcGetError(nRet), FREE_MEMORY(app_id));

	if(app_id == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error = app_id returned is NULL\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_app_id");
		return 1;
	}

	if(strcmp(app_id, STC_ALL_APP) != 0)
	{
		FPRINTF("[Line : %d][%s] %s failed, error = app_id returned is different\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_app_id");
		FREE_MEMORY(app_id);
		return 1;
	}

	FREE_MEMORY(app_id);
	return 0;
}

//& purpose Sets and Gets the time interval for statistics rule
//& type: auto
/**
* @testcase				ITs_stc_stats_rule_set_get_time_interval_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets and Gets the time interval for statistics rule
* @scenario				Sets and Gets the time interval for statistics rule \n
* @apicovered			stc_stats_rule_set_time_interval, stc_stats_rule_get_time_interval
* @passcase				If Sets and Gets the time interval successfully
* @failcase				If fails to Sets and/or Gets the time interval
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_rule_set_get_time_interval_p(void)
{
	START_TEST;

	int nRet = STC_ERROR_NONE;
	time_t from, to;

	nRet = stc_stats_rule_set_time_interval(g_hRule, 0, 1);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_interval", StcGetError(nRet));

	nRet = stc_stats_rule_get_time_interval(g_hRule, &from, &to);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_get_time_interval", StcGetError(nRet));

	if(from != 0)
	{
		FPRINTF("[Line : %d][%s] %s failed, error = from value returned is different\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_time_interval");
		return 1;
	}

	if(to != 1)
	{
		FPRINTF("[Line : %d][%s] %s failed, error = to value returned is different\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_time_interval");
		return 1;
	}

	return 0;
}

//& purpose Sets and Gets the interface type for statistics rule
//& type: auto
/**
* @testcase				ITs_stc_stats_rule_set_get_iface_type_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets and Gets the interface type for statistics rule
* @scenario				Sets and Gets the interface type for statistics rule \n
* @apicovered			stc_stats_rule_set_iface_type, tc_stats_rule_get_iface_type
* @passcase				If Sets and Gets the interface type successfully
* @failcase				If fails to Sets and/or Gets the interface type
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_rule_set_get_iface_type_p(void)
{
	START_TEST;

	stc_iface_type_e iface_type[] = {STC_IFACE_UNKNOWN, STC_IFACE_DATACALL, STC_IFACE_WIFI, STC_IFACE_WIRED, STC_IFACE_BLUETOOTH,  STC_IFACE_ALL};
	int enum_size = sizeof(iface_type) / sizeof(iface_type[0]);
	int enum_counter = 0;
	int nRet = STC_ERROR_NONE;
	stc_iface_type_e iface_type_get;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		//Target API
		/**** Set Rule Iface Type ****/
		nRet = stc_stats_rule_set_iface_type(g_hRule, iface_type[enum_counter]);
		PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_iface_type", StcGetError(nRet));

		//Target API
		/**** Get Rule Iface Type ****/
		nRet = stc_stats_rule_get_iface_type(g_hRule, &iface_type_get);
		PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_get_iface_type", StcGetError(nRet));

		if(iface_type_get != iface_type[enum_counter])
		{
			FPRINTF("[Line : %d][%s] %s failed, error = iface_type returned is different\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_iface_type");
			return 1;
		}
	}

	return 0;
}

//& purpose Sets and Gets the time period for statistics rule
//& type: auto
/**
* @testcase				ITs_stc_stats_rule_set_get_time_period_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Sets and Gets the time period for statistics rule
* @scenario				Sets and Gets the time period for statistics rule \n
* @apicovered			stc_stats_rule_set_time_period, stc_stats_rule_get_time_period
* @passcase				If Sets and Gets the time period successfully
* @failcase				If fails to Sets and/or Gets the time period
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_rule_set_get_time_period_p(void)
{
	START_TEST;

	stc_time_period_e time_period_type[] =
	{STC_TIME_PERIOD_UNKNOWN, STC_TIME_PERIOD_HOUR, STC_TIME_PERIOD_DAY, STC_TIME_PERIOD_WEEK, STC_TIME_PERIOD_MONTH};

	int enum_size = sizeof(time_period_type) / sizeof(time_period_type[0]);
	int enum_counter = 0;
	int nRet = STC_ERROR_NONE;
	stc_time_period_e time_period;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++)
	{
		//Target API
		/**** Set Rule time period ****/
		nRet = stc_stats_rule_set_time_period(g_hRule, time_period_type[enum_counter]);
		PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_period", StcGetError(nRet));

		//Target API
		/**** Get Rule time period ****/
		nRet = stc_stats_rule_get_time_period(g_hRule, &time_period);
		PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_get_time_period", StcGetError(nRet));

		if(time_period != time_period_type[enum_counter])
		{
			FPRINTF("[Line : %d][%s] %s failed, error = time_period returned is different\\n", __LINE__, API_NAMESPACE, "stc_stats_rule_get_time_period");
			return 1;
		}
	}

	return 0;
}

/**
* @function			StcTimeout
* @description		Called if some callback is not invoked for a particular StcTimeout
* @parameter		gpointer data
* @return			gboolean
*/
gboolean StcTimeout(gpointer data)
{
	g_iTargetApiCallback = STC_ERROR_INVALID_OPERATION;
	FPRINTF("[Line : %d][%s] Callback Time-out\\n", __LINE__, API_NAMESPACE);
	QUIT_GMAIN_LOOP;
	return false;
}

//& purpose Gets the statistics information of each application asynchronously
//& type: auto
/**
* @testcase				ITs_stc_foreach_all_stats_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the statistics information of each application asynchronously
* @scenario				Sets callback for statistics info API \n
* @scenario				Check for callback invocation \n
* @apicovered			stc_foreach_all_stats,stc_get_all_stats
* @passcase				If stc_get_all_stats and stc_foreach_all_stats API passes and the callback is invoked.
* @failcase				If stc_get_all_stats or stc_foreach_all_stats API fails,or callback is not invoked.
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_foreach_all_stats_p(void)
{
	START_TEST;
	time_t from, to;
	stc_stats_info_e eInfo = STATS_INFO_FOREACH_ALL;

	int nRet = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_app_id", StcGetError(nRet));

	from = StcMakeTime(STC_YEAR, STC_MONTH, STC_DAY, STC_HOUR, STC_MIN);
	time(&to);

	nRet = stc_stats_rule_set_time_interval(g_hRule, from, to);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_interval", StcGetError(nRet));

	g_bCallbackCalled = false;
	g_iTargetApiCallback = -1;
	g_eStatsInfo = eInfo;

	nRet = stc_get_all_stats(g_hSTC, g_hRule, StcGetStatsFinishedCallback, NULL);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_get_all_stats", StcGetError(nRet));

	RUN_GMAIN_LOOP;
	if(g_iTargetApiCallback != STC_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Target Api failed in the callback= %s\\n", __LINE__, API_NAMESPACE, "StcGetStatsFinishedCallback");	
		return 1;
	}
	if(g_bCallbackCalled == false)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked for %s\\n", __LINE__, API_NAMESPACE, "stc_get_all_stats");
		return 1;
	}
	return 0;
}
//& purpose Gets the All statistics information by interface type asynchronously
//& type: auto
/**
* @testcase				ITs_stc_get_all_stats_p
* @since_tizen			5.5
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets All statistics information by interface type asynchronously
* @scenario				Sets callback for statistics info API \n
* @scenario				Check for callback invocation \n
* @apicovered			stc_get_all_stats
* @passcase				If stc_for_all_stats API passes and callback is invoked.
* @failcase				If stc_for_all_stats API fails or  callback is not invoked.
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_get_all_stats_p(void)
{
	START_TEST;
	time_t from, to;
	stc_stats_info_e eInfo = STATS_INFO_GET_ALL;

	int nRet = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_app_id", StcGetError(nRet));

	from = StcMakeTime(STC_YEAR, STC_MONTH, STC_DAY, STC_HOUR, STC_MIN);
	time(&to);

	nRet = stc_stats_rule_set_time_interval(g_hRule, from, to);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_interval", StcGetError(nRet));

	g_bCallbackCalled = false;
	g_iTargetApiCallback = -1;
	g_eStatsInfo = eInfo;

	nRet = stc_get_all_stats(g_hSTC, g_hRule, StcGetStatsFinishedCallback, NULL);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_get_all_stats", StcGetError(nRet));

	RUN_GMAIN_LOOP;
	if(g_iTargetApiCallback != STC_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Target Api failed in the callback= %s\\n", __LINE__, API_NAMESPACE, "StcGetStatsFinishedCallback");
		return 1;
	}
	if(g_bCallbackCalled == false)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked for %s\\n", __LINE__, API_NAMESPACE, "stc_get_all_stats");
		return 1;
	}

	return 0;
}

//& purpose Gets the application ID from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_app_id_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the application ID from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the application Id \n
* @apicovered			stc_stats_info_get_app_id
* @passcase				If callback gets called and get the application Id successfully
* @failcase				If fails to called callback and/or get the application Id
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_app_id_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void *)STATS_INFO_APPID, StcStatsInfoGetAppIdCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Iface Name from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_iface_name_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Iface Name from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Iface Name \n
* @apicovered			stc_stats_info_get_iface_name
* @passcase				If callback gets called and get the Iface Name successfully
* @failcase				If fails to called callback and/or get the Iface Name
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_iface_name_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void *)STATS_INFO_IFACE_NAME, StcStatsInfoGetIfaceNameCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Time Interval from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_time_interval_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Time Interval from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Time Interval \n
* @apicovered			stc_stats_info_get_time_interval
* @passcase				If callback gets called and get the Time Interval successfully
* @failcase				If fails to called callback and/or get the Time Interval
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_time_interval_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)STATS_INFO_TIME_INTERVAL, StcStatsInfoGetTimeIntervalCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Iface Type from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_iface_type_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Iface Type from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Iface Type \n
* @apicovered			stc_stats_info_get_iface_type
* @passcase				If callback gets called and get the Iface Type successfully
* @failcase				If fails to called callback and/or get the Iface Type
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_iface_type_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)STATS_INFO_IFACE_TYPE, StcStatsInfoGetIfaceTypeCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Counter from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_counter_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Counter from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Counter \n
* @apicovered			stc_stats_info_get_counter
* @passcase				If callback gets called and get the Counter successfully
* @failcase				If fails to called callback and/or get the Counter
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_counter_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)STATS_INFO_COUNTER, StcStatsInfoGetCounterCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Roaming Type from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_roaming_type_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Roaming Type from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Counter \n
* @apicovered			stc_stats_info_get_roaming_type
* @passcase				If callback gets called and get the Roaming Type successfully
* @failcase				If fails to called callback and/or get the Roaming Type
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_roaming_type_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)STATS_INFO_ROAMING_TYPE, StcStatsInfoGetRoamingTypeCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Protocol from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_protocol_type_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Protocol from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Counter \n
* @apicovered			stc_stats_info_get_counter
* @passcase				If callback gets called and get the Protocol successfully
* @failcase				If fails to called callback and/or get the Protocol
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_protocol_type_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)STATS_INFO_PROTOCOL_TYPE, StcStatsInfoGetProtocolTypeCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Gets the Process State from statistics information
//& type: auto
/**
* @testcase				ITs_stc_stats_info_get_process_state_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the Process State from statistics information
* @scenario				Sets callback for statistics info API \n
* @scenario				Gets the Counter \n
* @apicovered			stc_stats_info_get_counter
* @passcase				If callback gets called and get the Process State successfully
* @failcase				If fails to called callback and/or get the Process State
* @precondition			NA
* @postcondition		NA
*/
int ITs_stc_stats_info_get_process_state_p(void)
{
	START_TEST;

	if(0 != StcGetStatisticsInformation((void*)("STATS_INFO_PROTOCOL_TYPE"), StcStatsInfoGetProcessStateCallback))
	{
		return 1;
	}
	return 0;
}

//& purpose Clones and destroys the statistics info handle.
//& type: auto
/**
* @testcase				ITs_stc_stats_info_clone_destroy_p
* @since_tizen			5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @description			Clones and destroys the statistics info handle.
* @scenario				Clones and destroys the statistics info handle \n
* @apicovered			stc_stats_info_clone, stc_stats_info_destroy
* @passcase				If stc_stats_info_clone and stc_stats_info_destroy returns zero
* @failcase				If stc_stats_info_clone or stc_stats_info_destroy do not return zero
* @precondition			STC should be initialized and stats data must be exist in the testing device
* @postcondition		NA
*/
int ITs_stc_stats_info_clone_destroy_p(void)
{
	START_TEST;
	time_t from, to;
	stc_stats_info_e eInfo = STATS_INFO_FOREACH_ALL;

	int nRet = stc_stats_rule_set_app_id(g_hRule, STC_ALL_APP);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_app_id", StcGetError(nRet));

	from = StcMakeTime(STC_YEAR, STC_MONTH, STC_DAY, STC_HOUR, STC_MIN);
	time(&to);

	nRet = stc_stats_rule_set_time_interval(g_hRule, from, to);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_stats_rule_set_time_interval", StcGetError(nRet));

	g_bCallbackCalled = false;
	g_iTargetApiCallback = -1;
	g_bIsAPISuccess = 1;
	g_eStatsInfo = eInfo;

	nRet = stc_get_all_stats(g_hSTC, g_hRule, StcGetStatsFinishedCallback, NULL);
	PRINT_RESULT(STC_ERROR_NONE, nRet, "stc_get_all_stats", StcGetError(nRet));

	RUN_GMAIN_LOOP;
	if(g_iTargetApiCallback != STC_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] Target Api failed in the callback= %s\\n", __LINE__, API_NAMESPACE, "StcGetStatsFinishedCallback");
		return 1;
	}
	if(g_bCallbackCalled == false)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked for %s\\n", __LINE__, API_NAMESPACE, "stc_get_all_stats");
		return 1;
	}
	if(g_bIsAPISuccess != 1 && g_bIsAPISuccess != STC_ERROR_NONE)
	{
		return 1;
	}

	return 0;
}
/** @} */
/** @} */
