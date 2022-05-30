//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-push-common.h"

/** @addtogroup itc-push
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		PushServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* PushServiceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case PUSH_SERVICE_ERROR_NONE:				szErrorVal = "PUSH_SERVICE_ERROR_NONE";					break; 
	case PUSH_SERVICE_ERROR_OUT_OF_MEMORY:		szErrorVal = "PUSH_SERVICE_ERROR_OUT_OF_MEMORY";		break; 
	case PUSH_SERVICE_ERROR_INVALID_PARAMETER:	szErrorVal = "PUSH_SERVICE_ERROR_INVALID_PARAMETER";	break; 
	case PUSH_SERVICE_ERROR_NOT_CONNECTED:		szErrorVal = "PUSH_SERVICE_ERROR_NOT_CONNECTED";		break;
	case PUSH_SERVICE_ERROR_NO_DATA:			szErrorVal = "PUSH_SERVICE_ERROR_NO_DATA";				break;
	case PUSH_SERVICE_ERROR_OPERATION_FAILED:	szErrorVal = "PUSH_SERVICE_ERROR_OPERATION_FAILED";		break;
	case PUSH_SERVICE_ERROR_PERMISSION_DENIED:	szErrorVal = "PUSH_SERVICE_ERROR_PERMISSION_DENIED";	break;
	default:									szErrorVal = "UNKNOWN_ERROR";							break;
	}
	return szErrorVal;
}

/**
 * @function 		CurlResponseCallback
 * @description	 	get result from json
 * @parameter		char *ptr, size_t size, size_t nmemb, void *userdata
 * @return 			size of response
 */
size_t CurlResponseCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	int nRet = 0;
	int *curl_response = (int *) userdata;
	char response_string[500];
	strncpy(response_string, ptr, 499);
	nRet = GetResultFromJson(response_string);
	if (!nRet) 
	{
		FPRINTF( "[Line : %d] [Push_ITc] Request successfully sent \\n", __LINE__);
		*curl_response = 0;
	}
#if DEBUG
	FPRINTF( "[Line : %d] [Push_ITc] CurlResponseCallback Response string is = %s \\n", __LINE__, response_string);
#endif
	return size*nmemb;
}

/**
 * @function 		GetResultFromJson
 * @description	 	get result from json
 * @parameter		char* json_string
 * @return 			0 for success, -1 for failure
 */
int GetResultFromJson(char* json_string)
{
	gint i = 0;
	int retval = 0;
	JsonParser *parser;
	gboolean ret = FALSE;

	if (NULL == json_string)
	{
		FPRINTF( "[Line : %d] [Push_ITc] json_string is NULL \\n", __LINE__);
		return -1;
	}
	parser = json_parser_new();
	
	if(parser == NULL)
	{
#if DEBUG
		FPRINTF( "[Line : %d] [Push_ITc] json parsor is NULL\\n", __LINE__);
#endif
		goto FINALLY;
	}
	
	if (!JSON_IS_PARSER(parser))
	{
		FPRINTF( "[Line : %d] [Push_ITc] Parser creation failed. \\n", __LINE__);
		goto FINALLY;
	}
	
	ret = json_parser_load_from_data(parser, json_string, strlen(json_string), NULL);
	if (FALSE == ret)
	{
		FPRINTF( "[Line : %d] [Push_ITc] Parser load failed \\n", __LINE__);
		goto FINALLY;
	}
	
	JsonObject *objnode = json_node_get_object(json_parser_get_root(parser));
	if (objnode == NULL)
	{
		FPRINTF( "[Line : %d] [Push_ITc] object node is NULL \\n", __LINE__);
		goto FINALLY;
	}
	
	JsonNode* node = json_object_get_member(objnode, "results");
	if (node == NULL)
	{
		FPRINTF( "[Line : %d] [Push_ITc] Node is null \\n", __LINE__);
		goto FINALLY;
	}
	
	JsonArray* jsonArray = json_node_get_array(node);
	if (jsonArray == NULL)
	{
		FPRINTF( "[Line : %d] [Push_ITc] Json Array is NULL \\n", __LINE__);
		goto FINALLY;
	}

	int length = json_array_get_length(jsonArray);
	for (i = 0; i < length; i++)
	{
		JsonNode *jsonNode = json_array_get_element(jsonArray, i);
		JsonObject* obj = json_node_get_object(jsonNode);
		char *status_msg = NULL;

		retval = json_object_get_int_member(obj, "statusCode");
		status_msg = g_strndup(json_object_get_string_member(obj, "statusMsg"), 100);
		
		if (status_msg)
		{
			g_free(status_msg);
		}
	}
	
	FINALLY:
	{
		g_object_unref (parser);
	}
	return retval == 1000 ? 0 : -1;
}

/**
* @function 		SendNotificationUsingCurl
* @description	 	Send notification data to server using curl
* @parameter		OutgoingNotification *pstNotificationInfo, bool verbose
* @return 			response from curl API
*/
int SendNotificationUsingCurl(OutgoingNotification *pstNotificationInfo, bool verbose)
{

	char app_id_str[23];
	char app_secret_str[50];

	char *server_address = NULL;
	char body[MAX_BODY_LENGTH];
	int current_size = 0;

	char *temp_str= NULL;

	struct curl_slist *header_list = NULL;
	CURL *curl_handle;
	CURLcode curl_err;

	int curl_response = PUSH_SERVICE_ERROR_NOT_CONNECTED;
	int ret =0;

	connection_h connection;
	char *proxy_address = NULL;

	// Determine RQM server
	if (strncmp(pstNotificationInfo->reg_id, "00", 2) == 0) {
		server_address = "https://useast.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "02", 2) == 0) {
		server_address = "https://apsoutheast.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "03", 2) == 0) {
		server_address = "https://euwest.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "04", 2) == 0) {
		server_address = "https://apnortheast.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "05", 2) == 0) {
		server_address = "https://apkorea.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "06", 2) == 0) {
		server_address = "https://apchina.push.samsungosp.com.cn:8090/spp/pns/api/push";
	}
        else if (strncmp(pstNotificationInfo->reg_id, "50", 2) == 0) {
		server_address = "https://useast.gateway.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "52", 2) == 0) {
		server_address = "https://apsoutheast.gateway.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "53", 2) == 0) {
		server_address = "https://euwest.gateway.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "54", 2) == 0) {
		server_address = "https://apnortheast.gateway.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "55", 2) == 0) {
		server_address = "https://apkorea.gateway.push.samsungosp.com:8090/spp/pns/api/push";
	}
	else if (strncmp(pstNotificationInfo->reg_id, "56", 2) == 0) {
		server_address = "https://apchina.gateway.push.samsungosp.com.cn:8090/spp/pns/api/push";
	}
	else {
		FPRINTF("[Line : %d][%s] REG_ID has a wrong prefix\\n", __LINE__, API_NAMESPACE);
	}


	////////////////////////////////////
	// Create JSON query from here    //
	////////////////////////////////////

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, "{");
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add regID and requestID
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
		"\"regID\":\"%s\",\"requestID\":\"%s\"", pstNotificationInfo->reg_id, pstNotificationInfo->request_id);
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add time_stamp
	if ( pstNotificationInfo->time_stamp > 0 )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, ",\"timeStamp\":\"%ld\"", pstNotificationInfo->time_stamp);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add type
	if ( pstNotificationInfo->type > 0 )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"type\":\"%d\"", pstNotificationInfo->type);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add delayDate
	if ( pstNotificationInfo->delay >0 )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"delayDate\":\"%d\"", pstNotificationInfo->delay);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add sender
	if ( pstNotificationInfo->sender )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"sender\":\"%s\"", pstNotificationInfo->sender);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add session info field
	if ( pstNotificationInfo->session_info )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"sessionInfo\":\"%s\"", pstNotificationInfo->session_info);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add message
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
		",\"message\":\"");
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	switch ( pstNotificationInfo->action )
	{
	case PUSH_ACTION_ALERT:
		temp_str = "ALERT";
		break;

	case PUSH_ACTION_DISCARD:
		temp_str = "DISCARD";
		break;

	case PUSH_ACTION_LAUNCH:
		temp_str = "LAUNCH";
		break;

	case PUSH_ACTION_SILENT:
		temp_str = "SILENT";
		break;
	default :
		FPRINTF("[Line : %d][%s] Invalid action\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_INVALID_PARAMETER;
	}

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
		"action=%s", temp_str);

	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	if ( pstNotificationInfo->action == PUSH_ACTION_ALERT )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, "&alartMessage=%s", pstNotificationInfo->alert_message);

		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	if ( pstNotificationInfo->badge_option != PUSH_BADGE_OPTION_NONE )
	{
		switch (pstNotificationInfo->badge_option)
		{
		case PUSH_BADGE_OPTION_INCREASE:
			temp_str = "INCREASE";
			break;

		case PUSH_BADGE_OPTION_DECREASE:
			temp_str = "DECREASE";
			break;

		case PUSH_BADGE_OPTION_SET:
			temp_str = "SET";
			break;

		default:
			FPRINTF("[Line : %d][%s] Invalid badge option\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_INVALID_PARAMETER;
			break;
		}

		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, "&badgeOption=%s&badgeNumber=%d", temp_str, pstNotificationInfo->badge_number);
		current_size += ret;
		if ( current_size >= MAX_BODY_LENGTH )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, "\"");
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add appData
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, ",\"appData\":\"%s\"", pstNotificationInfo->app_data);
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Close the json query
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size, "}");
	current_size += ret;
	if ( current_size >= MAX_BODY_LENGTH )
	{
		FPRINTF("[Line : %d][%s] Buffer overflow\\n", __LINE__, API_NAMESPACE);
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	///////////////////////////////////////
	// End of creating the JSON query    //
	///////////////////////////////////////

	// Send noti to the RQM server using LIBCURL
	do
	{
		// Initiate the CURL handle
		curl_handle = curl_easy_init();

		ret = snprintf(app_id_str, sizeof(app_id_str), "appID:%s", pstNotificationInfo->app_id);
		if ( ret == sizeof(app_id_str) )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow-app_id\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}

		ret = snprintf(app_secret_str, sizeof(app_secret_str), "appSecret:%s", pstNotificationInfo->app_secret);
		if ( ret == sizeof(app_secret_str) )
		{
			FPRINTF("[Line : %d][%s] Buffer overflow-app_secret\\n", __LINE__, API_NAMESPACE);
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}

		// Print the headers

		// Add the headers to the CURL handle
		header_list = curl_slist_append(header_list, app_id_str);
		header_list = curl_slist_append(header_list, app_secret_str);
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, header_list);
		if ( curl_err != CURLE_OK )
		{
			FPRINTF("[Line : %d][%s] CURL_ERR:header_list [%d]\\n", __LINE__, API_NAMESPACE, curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		// Link the data to post
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, body);
		if ( curl_err != CURLE_OK )
		{
			FPRINTF("[Line : %d][%s] CURL_ERR:body [%d]\\n", __LINE__, API_NAMESPACE, curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		// Link the server address
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_URL, server_address);
		if ( curl_err != CURLE_OK )
		{
			FPRINTF("[Line : %d][%s] CURL_ERR:server_address [%d]\\n", __LINE__, API_NAMESPACE, curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &curl_response);
		curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT_MS, 30000);
		curl_easy_setopt(curl_handle, CURLOPT_PROXYPORT, 8090);

		ret = connection_create(&connection);
		if (CONNECTION_ERROR_NONE != ret) {
			FPRINTF( "[Line : %d] [Push_ITc] fail to create conn_handle[%d] \\n", __LINE__, ret);
			return -1;
		}

		ret = connection_get_proxy(connection, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy_address);
		if (ret != CONNECTION_ERROR_NONE) {
			FPRINTF( "[Line : %d][%s] Fail to get proxy[%d] \\n", __LINE__, API_NAMESPACE, ret);
			if (proxy_address) {
				free(proxy_address);
				proxy_address = NULL;
			}
		} else {
                        if (proxy_address != NULL && strlen(proxy_address)!=0) {
                                FPRINTF("[Line : %d][%s] Proxy Address : [%s]", __LINE__, API_NAMESPACE, proxy_address);
                                curl_easy_setopt(curl_handle, CURLOPT_PROXY, proxy_address);
                        }
		}

		if (connection) {
			 connection_destroy(connection);
			 connection = NULL;
		}

		// Display DEBUG info
		if (verbose)
		{
			curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
		}

		// Perform HTTP POST using CURL
		curl_err = curl_easy_perform(curl_handle);
		if ( curl_err != CURLE_OK )
		{
			FPRINTF("[Line : %d][%s] CURL_ERR: perform [%d]\\n", __LINE__, API_NAMESPACE, curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		long lCodeReturned = 0L;
		curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &lCodeReturned);
#if DEBUG
		FPRINTF("[Line : %d][%s] server status = %ld\\n", __LINE__, API_NAMESPACE, lCodeReturned);
#endif
		ret = curl_response;

	} while (0);

	curl_slist_free_all(header_list);
	curl_easy_cleanup(curl_handle);

	return ret;
}

/**
* @function 		SendPushDataToServer
* @description	 	Send notification data
* @parameter		const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
*					const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
*					push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
*					const char *sender, bool verbose
* @return 			response from curl API
*/
int SendPushDataToServer(const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
						 const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
						 push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
						 const char *sender, bool verbose)
{
	int ret;
	OutgoingNotification stOutgoingData;

	stOutgoingData.app_id = push_app_id;
	stOutgoingData.app_secret = app_secret;
	stOutgoingData.reg_id = reg_id;
	stOutgoingData.request_id = request_id;
	stOutgoingData.app_data = app_data;
	stOutgoingData.app_data_size = app_data_size;
	stOutgoingData.alert_message = alert_message;
	stOutgoingData.action = action;
	stOutgoingData.badge_option = badge_option;
	stOutgoingData.badge_number = badge_number;
	stOutgoingData.time_stamp = time_stamp;
	stOutgoingData.type = type;
	stOutgoingData.delay = delay;
	stOutgoingData.sender = sender;
	stOutgoingData.session_info = "001001";

	ret = SendNotificationUsingCurl(&stOutgoingData, verbose);

	return ret;
}

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/ 
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF( "[Line : %d] [Push_ITc]Callback Timeout \\n", __LINE__);
	return false;
}
/** @} */
