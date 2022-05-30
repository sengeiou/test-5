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
#include <push-service.h>
#include <app_control.h>
#include <string.h>
#include "sppc-common.h"

// For the sending feature
#include <json-glib/json-glib.h>
#include <curl/curl.h>
#define APP_SECRET_LENGTH 50
#define APP_DATA_MAX_SIZE 4096
#define ALERT_MESSAGE_MAX_LENGTH 127
#define MAX_BODY_LENGTH	APP_DATA_MAX_SIZE + 500
#define MAX_HEADER_LENGTH 100
#define SPP_ID_MAX_LENGTH 128
#define SPP_ID_MIN_LENGTH 10

/**
* @function 		CurlDebugCallback
* @description	 	Called with the result of a SendNotificationUsingCurl debug message
* @parameter		CURL *handle, curl_infotype type, char *data, size_t size, void *userptr
* @return 			0
*/
int CurlDebugCallback(CURL *handle, curl_infotype type, char *data, size_t size, void *userptr)
{
	  const char *text;
	  (void)handle; /* prevent compiler warning */

	  switch (type) {
	  case CURLINFO_TEXT:
#if DEBUG
		  _LOG("Info = %s", data);
#endif
		  return 0;
	  default: /* in case a new one is introduced to shock us */
	    return 0;

	  case CURLINFO_HEADER_OUT:
	    text = "=> Send header";
	    break;
	  case CURLINFO_DATA_OUT:
	    text = "=> Send data";
	    break;
	  case CURLINFO_SSL_DATA_OUT:
	    text = "=> Send SSL data";
	    break;
	  case CURLINFO_HEADER_IN:
	    text = "<= Recv header";
	    break;
	  case CURLINFO_DATA_IN:
	    text = "<= Recv data";
	    break;
	  case CURLINFO_SSL_DATA_IN:
	    text = "<= Recv SSL data";
	    break;
	  }
#if DEBUG
	  _LOG("Info = %s", text);
#endif
	  return 0;
}

/**
* @function 		GetResultFromJson
* @description	 	Called to find out the result string of CurlResponseCallback
* @parameter		char* json_string
* @return 			0 : OK, -1 FAIL
*/
int GetResultFromJson(char* json_string)
{
	gint i = 0;
	int retval = 0;
	JsonParser *parser;
	gboolean ret = FALSE;

	if (NULL == json_string)
	{
		_LOG("json_string is NULL");
		return -1;
	}
	parser = json_parser_new();

	if(parser == NULL)
	{
#if DEBUG
		_LOG("json parsor is NULL");
#endif
		goto FINALLY;
	}

	if (!JSON_IS_PARSER(parser))
	{
		_LOG("Parser creation failed.");
		goto FINALLY;
	}

	ret = json_parser_load_from_data(parser, json_string, strlen(json_string), NULL);
	if (FALSE == ret)
	{
		_LOG("Parser load failed");
		goto FINALLY;
	}

	JsonObject *objnode = json_node_get_object(json_parser_get_root(parser));
	if (objnode == NULL)
	{
		_LOG("object node is NULL");
		goto FINALLY;
	}

	JsonNode* node = json_object_get_member(objnode, "results");
	if (node == NULL)
	{
		_LOG("Node is null");
		goto FINALLY;
	}

	JsonArray* jsonArray = json_node_get_array(node);
	if (jsonArray == NULL)
	{
		_LOG("Json Array is NULL");
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
* @function 		GetResultFromJson
* @description	 	Called with the result of the SendNotificationUsingCurl
* @parameter		char *ptr, size_t size, size_t nmemb, void *userdata
* @return 			send data size (size * nmemb)
*/
size_t CurlResponseCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	int nRet = 0;
	int *curl_response = (int *) userdata;
	char response_string[500] = {0,};
	strncpy(response_string, ptr, 499);
	nRet = GetResultFromJson(response_string);
	if (!nRet)
	{
		_LOG("Request successfully sent");
		*curl_response = 0;
	}
#if DEBUG
	_LOG("CurlResponseCallback Response string is = %s", response_string);
#endif
	return size*nmemb;
}

/**
* @function 		CheckOutgoingNotification
* @description	 	Called to check Notification informaion before SendPushDataToServer
* @parameter		OutgoingNotification *pstNotificationInfo
* @return 			0 : OK, 1 FAIL
*/
int CheckOutgoingNotification(OutgoingNotification *pstNotificationInfo)
{
	_LOG("CheckOutgoingNotification start");
	int ret;

	// NULL check
	if (!pstNotificationInfo->app_id) {
		_LOG("app_id is NULL");
		return 1;
	}
	if (!pstNotificationInfo->app_secret)	{
		_LOG("app_secret is NULL");
		return 1;
	}

	if (!pstNotificationInfo->reg_id)	{
		_LOG("reg_id is NULL");
		return 1;
	}

	if (!pstNotificationInfo->request_id)	{
		_LOG("request_id is NULL");
		return 1;
	}

	// Size check
	ret = strnlen(pstNotificationInfo->app_id, SPP_ID_MAX_LENGTH+1);
	if ( ret > SPP_ID_MAX_LENGTH || ret < SPP_ID_MIN_LENGTH) {
		_LOG("app_id [%s] : wrong length", pstNotificationInfo->app_id);
		return 1;
	}


	ret = strnlen(pstNotificationInfo->app_secret, APP_SECRET_LENGTH+1);
	if ( ret > APP_SECRET_LENGTH) {
		_LOG("app_secret [%s]  : wrong length", pstNotificationInfo->app_secret);
		return 1;
	}

	ret = strnlen(pstNotificationInfo->alert_message, ALERT_MESSAGE_MAX_LENGTH+1);
	if ( ret > ALERT_MESSAGE_MAX_LENGTH) {
		_LOG("alert_message [%s] is too long or too short", pstNotificationInfo->alert_message);
		return 1;
	}

	ret = strnlen(pstNotificationInfo->app_data, APP_DATA_MAX_SIZE+1);
	if ( ret > APP_DATA_MAX_SIZE) {
		_LOG("app_data [%s] is too long or too short", pstNotificationInfo->app_data);
		return 1;
	}

	if (pstNotificationInfo->badge_number < 0 || pstNotificationInfo->badge_number > 1000) {
		_LOG("badge size is out of range!!");
		return 1;
	}

	return 0;
}

/**
* @function 		SendNotificationUsingCurl
* @description	 	Called to send notification to test device (itself) with curl_easy_perform
* @parameter		OutgoingNotification *pstNotificationInfo, bool verbose
* @return 			0 : OK, 1 FAIL
*/
int SendNotificationUsingCurl(OutgoingNotification *pstNotificationInfo, bool verbose)
{
	_LOG("SendNotificationUsingCurl start");

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
		_LOG("REG_ID has a wrong prefix");
	}


	////////////////////////////////////
	// Create JSON query from here    //
	////////////////////////////////////

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"{");
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add regID and requestID
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"\"regID\":\"%s\",\"requestID\":\"%s\"", pstNotificationInfo->reg_id, pstNotificationInfo->request_id);
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add time_stamp
	if (pstNotificationInfo->time_stamp>0)
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				",\"timeStamp\":\"%ld\"", pstNotificationInfo->time_stamp);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add type
	if (pstNotificationInfo->type > 0 )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				",\"type\":\"%d\"", pstNotificationInfo->type);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add delayDate
	if (pstNotificationInfo->delay >0 )
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				",\"delayDate\":\"%d\"", pstNotificationInfo->delay);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add sender
	if (pstNotificationInfo->sender)
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				",\"sender\":\"%s\"", pstNotificationInfo->sender);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add session info field
	if (pstNotificationInfo->session_info)
	{
		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				",\"sessionInfo\":\"%s\"", pstNotificationInfo->session_info);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	// Add message
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"message\":\"");
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	switch (pstNotificationInfo->action) {
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
			_LOG("Invalid action");
			return PUSH_SERVICE_ERROR_INVALID_PARAMETER;
	}

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"action=%s", temp_str);

	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	if (pstNotificationInfo->action == PUSH_ACTION_ALERT) {

		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"&alartMessage=%s", pstNotificationInfo->alert_message);

		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	if (pstNotificationInfo->badge_option != PUSH_BADGE_OPTION_NONE) {

		switch (pstNotificationInfo->badge_option) {
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
				_LOG("Invalid badge option");
				return PUSH_SERVICE_ERROR_INVALID_PARAMETER;
				break;
		}

		ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
				"&badgeOption=%s&badgeNumber=%d", temp_str, pstNotificationInfo->badge_number);
		current_size += ret;
		if (current_size >= MAX_BODY_LENGTH)
		{
			_LOG("Buffer overflow");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}
	}

	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"\"");
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Add appData
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			",\"appData\":\"%s\"", pstNotificationInfo->app_data);
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	// Close the json query
	ret = snprintf(body+current_size, MAX_BODY_LENGTH-current_size,
			"}");
	current_size += ret;
	if (current_size >= MAX_BODY_LENGTH)
	{
		_LOG("Buffer overflow");
		return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
	}

	///////////////////////////////////////
	// End of creating the JSON query    //
	///////////////////////////////////////

	// Send noti to the RQM server using LIBCURL
	do {

		// Initiate the CURL handle
		curl_handle = curl_easy_init();

		ret = snprintf(app_id_str, sizeof(app_id_str), "appID:%s", pstNotificationInfo->app_id);
		if (ret == sizeof(app_id_str)) {
			_LOG("Buffer overflow-app_id");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}

		ret = snprintf(app_secret_str, sizeof(app_secret_str), "appSecret:%s", pstNotificationInfo->app_secret);
		if (ret == sizeof(app_secret_str)) {
			_LOG("Buffer overflow-app_secret");
			return PUSH_SERVICE_ERROR_OUT_OF_MEMORY;
		}

		// Print the headers

		// Add the headers to the CURL handle
		header_list = curl_slist_append(header_list, app_id_str);
		header_list = curl_slist_append(header_list, app_secret_str);
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, header_list);
		if ( curl_err != CURLE_OK ) {
			_LOG("CURL_ERR:header_list [%d]", curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		// Link the data to post
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, body);
		if ( curl_err != CURLE_OK ) {
			_LOG("CURL_ERR:body [%d]", curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		// Link the server address
		curl_err = curl_easy_setopt(curl_handle, CURLOPT_URL, server_address);
		if ( curl_err != CURLE_OK ) {
			_LOG("CURL_ERR:server_address [%d]", curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlResponseCallback);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &curl_response);
		curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT_MS, 15000);
		curl_easy_setopt(curl_handle, CURLOPT_PROXYPORT, 8090);

		ret = connection_create(&connection);
		if (CONNECTION_ERROR_NONE != ret) {
			_LOG("fail to create conn_handle[%d]", ret);
			return -1;
		}

		ret = connection_get_proxy(connection, CONNECTION_ADDRESS_FAMILY_IPV4, &proxy_address);
		if (ret != CONNECTION_ERROR_NONE) {
			_LOG("Fail to get proxy[%d]", ret);
			if (proxy_address) {
				free(proxy_address);
				proxy_address = NULL;
			}
		} else {
			if (proxy_address != NULL && strlen(proxy_address)!=0) {
				_LOG("Proxy Address : [%s]", proxy_address);
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
			curl_easy_setopt(curl_handle, CURLOPT_DEBUGFUNCTION, CurlDebugCallback);
		}

		// Perform HTTP POST using CURL
		curl_err = curl_easy_perform(curl_handle);
		if ( curl_err != CURLE_OK ) {
			_LOG("CURL_ERR: perform [%d]", curl_err);
			ret = PUSH_SERVICE_ERROR_OPERATION_FAILED;
			break;
		}

		long lCodeReturned = 0L;
		curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &lCodeReturned);

		_LOG("server status = %ld", lCodeReturned);

		ret = curl_response;

	} while (0);

	curl_slist_free_all(header_list);
	curl_easy_cleanup(curl_handle);

	return ret;
}

/**
* @function 		SendPushDataToServer
* @description	 	Called to send notification with SendNotificationUsingCurl to test device
* @parameter		const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
*					const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
*					push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
*					const char *sender, bool verbose
* @return 			result message
*/
int SendPushDataToServer(const char *push_app_id, const char *app_secret, const char *reg_id, const char *request_id,
					const char *app_data, int app_data_size, const char *alert_message, push_action_e action,
					push_badge_option_e badge_option, int badge_number, long time_stamp, int type, int delay,
					const char *sender, bool verbose)
{
	_LOG("SendPushDataToServer start");
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

	if (CheckOutgoingNotification(&stOutgoingData))
	{
		_LOG("CheckOutgoingNotification failed");
		return PUSH_SERVICE_ERROR_INVALID_PARAMETER;
	}

	ret = SendNotificationUsingCurl(&stOutgoingData, verbose);

	return ret;
}

/**
* @function 		GetAppId
* @description	 	Called to get application id to send notification via SendNotificationUsingCurl to test device
* @parameter		char **app_id
* @return 			0 : OK, 1 FAIL
*/
int GetAppId(char **app_id)
{
	char appId[CONFIG_VALUE_LEN_MAX] = {0,};

	if (true == GetValueFromConfigFile("PUSH_APPID", appId, API_NAMESPACE)) {
		*app_id = strdup(appId);
		/* _LOG("GetAppId : AppID [%s]", *app_id); */
	}
	else {
		_LOG("GetAppId : Getting AppID failed");
		return 1;
	}

	return 0;
}

/**
* @function 		GetAppSecret
* @description	 	Called to get application secret to send notification via SendNotificationUsingCurl to test device
* @parameter		char **app_secret
* @return 			0 : OK, 1 FAIL
*/
int GetAppSecret(char **app_secret)
{
	char appSecret[CONFIG_VALUE_LEN_MAX] = {0,};

	if (true == GetValueFromConfigFile("PUSH_APPSECRET", appSecret, API_NAMESPACE)) {
		*app_secret = strdup(appSecret);
		/* _LOG("GetAppSecret : AppSecret [%s]", *app_secret); */
	}
	else {
		_LOG("GetAppSecret : Getting AppID failed");
		return 1;
	}

	return 0;
}
