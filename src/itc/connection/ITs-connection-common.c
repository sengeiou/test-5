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
#include "ITs-connection-common.h"

/** @addtogroup itc-connection
*  @ingroup itc
*  @{
*/

/**
* @function 		ConnectionGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ConnectionGetError(connection_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CONNECTION_ERROR_NONE : 							szErrorVal = "CONNECTION_ERROR_NONE"; 							break;/**< Successful */
	case CONNECTION_ERROR_INVALID_PARAMETER : 				szErrorVal = "CONNECTION_ERROR_INVALID_PARAMETER"; 				break;/**< Invalid parameter */
	case CONNECTION_ERROR_OUT_OF_MEMORY: 					szErrorVal = "CONNECTION_ERROR_OUT_OF_MEMORY"; 					break;/**< Out of memory error */
	case CONNECTION_ERROR_INVALID_OPERATION : 				szErrorVal = "CONNECTION_ERROR_INVALID_OPERATION"; 				break;/**< Invalid Operation */
	case CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED : 	szErrorVal = "CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED"; 	break;/**< Address family not supported */
	case CONNECTION_ERROR_OPERATION_FAILED : 				szErrorVal = "CONNECTION_ERROR_OPERATION_FAILED"; 				break;/**< Operation failed */
	case CONNECTION_ERROR_ITERATOR_END : 					szErrorVal = "CONNECTION_ERROR_ITERATOR_END"; 					break;/**< End of iteration */
	case CONNECTION_ERROR_NO_CONNECTION : 					szErrorVal = "CONNECTION_ERROR_NO_CONNECTION"; 					break;/**< There is no connection */
	case CONNECTION_ERROR_NOW_IN_PROGRESS : 				szErrorVal = "CONNECTION_ERROR_NOW_IN_PROGRESS"; 				break;/** Now in progress */
	case CONNECTION_ERROR_ALREADY_EXISTS : 					szErrorVal = "CONNECTION_ERROR_ALREADY_EXISTS"; 				break;/**< Already exists */
	case CONNECTION_ERROR_OPERATION_ABORTED : 				szErrorVal = "CONNECTION_ERROR_OPERATION_ABORTED"; 				break;/**< Operation is aborted */
	case CONNECTION_ERROR_DHCP_FAILED : 					szErrorVal = "CONNECTION_ERROR_DHCP_FAILED"; 					break;/**< DHCP failed  */
	case CONNECTION_ERROR_INVALID_KEY : 					szErrorVal = "CONNECTION_ERROR_INVALID_KEY"; 					break;/**< Invalid key  */
	case CONNECTION_ERROR_NO_REPLY : 						szErrorVal = "CONNECTION_ERROR_NO_REPLY"; 						break;/**< No reply */
	case CONNECTION_ERROR_PERMISSION_DENIED : 				szErrorVal = "CONNECTION_ERROR_PERMISSION_DENIED"; 				break;/**< Permission denied */
	case CONNECTION_ERROR_NOT_SUPPORTED : 					szErrorVal = "CONNECTION_ERROR_NOT_SUPPORTED"; 					break;/**< Not supported */
	case CONNECTION_ERROR_ALREADY_INITIALIZED : 			szErrorVal = "CONNECTION_ERROR_ALREADY_INITIALIZED"; 			break;/**< Already initialized */
	case CONNECTION_ERROR_NOT_INITIALIZED : 				szErrorVal = "CONNECTION_ERROR_NOT_INITIALIZED"; 				break;/**< Not initialized */
	default : 												szErrorVal = "Unknown Error"; 									break;
	}
	return szErrorVal;
}


/**
* @function 		ConnectionGetCellularStateType
* @description	 	Maps Cellular status  enums to string values
* @parameter		nState : state code returned
* @return 			state string
*/
char* ConnectionGetCellularStateType(connection_cellular_state_e nState)
{
	char *szType = "Unknown State";
	switch ( nState )
	{
	case CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE: 				szType = "CONNECTION_CELLULAR_STATE_OUT_OF_SERVICE"; 		break; /**< Out of service */
	case CONNECTION_CELLULAR_STATE_FLIGHT_MODE: 				szType = "CONNECTION_CELLULAR_STATE_FLIGHT_MODE"; 			break; /**< Flight mode */
	case CONNECTION_CELLULAR_STATE_ROAMING_OFF: 				szType = "CONNECTION_CELLULAR_STATE_ROAMING_OFF"; 			break; /**< Roaming is turned off */
	case CONNECTION_CELLULAR_STATE_CALL_ONLY_AVAILABLE: 		szType = "CONNECTION_CELLULAR_STATE_CALL_ONLY_AVAILABLE"; 	break;/**< Call is only available */
	case CONNECTION_CELLULAR_STATE_AVAILABLE: 					szType = "CONNECTION_CELLULAR_STATE_AVAILABLE"; 			break; /**< Available but not connected yet */
	case CONNECTION_CELLULAR_STATE_CONNECTED: 					szType = "CONNECTION_CELLULAR_STATE_CONNECTED"; 			break; /**< Connected */
	}
	return szType;
}

/**
* @function 		ConnectionGetType
* @description	 	Maps type enums to string values
* @parameter		nType : code returned
* @return 			error string
*/
char* ConnectionGetType(connection_type_e nType)
{
	char *szType = "Unknown State";
	switch ( nType )
	{
	case CONNECTION_TYPE_DISCONNECTED: 				szType = "CONNECTION_TYPE_DISCONNECTED"; 		break; /**< Disconnected */
	case CONNECTION_TYPE_WIFI: 						szType = "CONNECTION_TYPE_WIFI"; 				break; /**< Wi-Fi type */
	case CONNECTION_TYPE_CELLULAR: 					szType = "CONNECTION_TYPE_CELLULAR"; 			break; /**< Cellular type */
	case CONNECTION_TYPE_ETHERNET: 					szType = "CONNECTION_TYPE_ETHERNET"; 			break; /**< Ethernet type */
	case CONNECTION_TYPE_BT: 						szType = "CONNECTION_TYPE_BT"; 					break;	/**< Bluetooth type */
	case CONNECTION_TYPE_NET_PROXY:					szType = "CONNECTION_TYPE_NET_PROXY";			break;  /**Proxy type for internet connection(since 3.0)**/
	}
	return szType;
}

/**
* @function 		ConnectionGetAddressFamily
* @description	 	Maps type enums to string values
* @parameter		nFamily : code returned
* @return 			error string
*/
char* ConnectionGetAddressFamily(connection_address_family_e nFamily)
{
	char *szFamily = "Unknown Address Family";
	switch ( nFamily )
	{
	case CONNECTION_ADDRESS_FAMILY_IPV4: 		szFamily = "CONNECTION_ADDRESS_FAMILY_IPV4"; 		break; /**< Disconnected */
	case CONNECTION_ADDRESS_FAMILY_IPV6: 		szFamily = "CONNECTION_ADDRESS_FAMILY_IPV6"; 		break; /**< Wi-Fi type */
	}
	return szFamily;
}

/**
* @function 		ConnectionGetCellularServiceType
* @description	 	Maps type enums to string values
* @parameter		nRet : code returned
* @return 			error string
*/
char* ConnectionGetCellularServiceType(connection_cellular_service_type_e nRet)
{
	char *szType = "Unknown State";
	switch ( nRet )
	{
	case CONNECTION_CELLULAR_SERVICE_TYPE_UNKNOWN: 					szType = "CONNECTION_CELLULAR_SERVICE_TYPE_UNKNOWN"; 				break;	/**< Unknown */
	case CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET: 				szType = "CONNECTION_CELLULAR_SERVICE_TYPE_INTERNET"; 				break;	/**< Internet */
	case CONNECTION_CELLULAR_SERVICE_TYPE_MMS: 						szType = "CONNECTION_CELLULAR_SERVICE_TYPE_MMS"; 					break;	/**< MMS */
	case CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_INTERNET: 		szType = "CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_INTERNET"; 		break;	/**< Prepaid internet */
	case CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_MMS: 				szType = "CONNECTION_CELLULAR_SERVICE_TYPE_PREPAID_MMS"; 			break;	/**< Prepaid MMS */
	case CONNECTION_CELLULAR_SERVICE_TYPE_TETHERING: 				szType = "CONNECTION_CELLULAR_SERVICE_TYPE_TETHERING"; 				break;	/**< Tethering */
	case CONNECTION_CELLULAR_SERVICE_TYPE_APPLICATION: 				szType = "CONNECTION_CELLULAR_SERVICE_TYPE_APPLICATION"; 			break; /**< Specific application */
	}
	return szType;
}

#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) || defined(TV)//Starts MOBILE or WEARABLE or TIZENIOT
/**
* @function 		ConnectionGetCellularPdnType
* @description	 	Maps type enums to string values
* @parameter		nRet : code returned
* @return 			error string
*/
char* ConnectionGetCellularPdnType(connection_cellular_pdn_type_e nRet)
{
	char *szType = NULL;
	switch ( nRet )
	{
	case CONNECTION_CELLULAR_PDN_TYPE_IPV4: 								szType = "CONNECTION_CELLULAR_PDN_TYPE_IPV4"; 					break;
	case CONNECTION_CELLULAR_PDN_TYPE_IPV6: 								szType = "CONNECTION_CELLULAR_PDN_TYPE_IPV6"; 					break;
	case CONNECTION_CELLULAR_PDN_TYPE_IPV4_IPv6: 						szType = "CONNECTION_CELLULAR_PDN_TYPE_IPV4_IPv6"; 		break;
	default : 																									szType = "Unknown Type"; 																break;
	}
	return szType;
}
#endif  // End MOBILE or WEARABLE or TIZENIOT

/**
* @function 		ConnectionGetCellularAuthType
* @description	 	Maps type enums to string values
* @parameter		nRet : enum value
* @return 			string of enum value
*/
char* ConnectionGetCellularAuthType(connection_cellular_auth_type_e nRet)
{
	char *szType = "Unknown State";
	switch ( nRet )
	{
	case CONNECTION_CELLULAR_AUTH_TYPE_NONE: 	szType = "CONNECTION_CELLULAR_AUTH_TYPE_NONE"; 	break;				  	/**< Unknown */
	case CONNECTION_CELLULAR_AUTH_TYPE_PAP: 	szType = "CONNECTION_CELLULAR_AUTH_TYPE_PAP"; 	break;			  		/**< Internet */
	case CONNECTION_CELLULAR_AUTH_TYPE_CHAP: 	szType = "CONNECTION_CELLULAR_AUTH_TYPE_CHAP"; 	break;					/**< MMS */
	}
	return szType;
}

/**
* @function 		ConnectionGetIpConfigType
* @description	 	Maps type enums to string values
* @parameter		nRet : enum value
* @return 			string of enum value
*/
char* ConnectionGetIpConfigType(connection_ip_config_type_e nRet)
{
	char *szType = "Unknown State";
	switch ( nRet )
	{
	case CONNECTION_IP_CONFIG_TYPE_NONE: 			szType = "CONNECTION_IP_CONFIG_TYPE_NONE"; 		break;				 /**< Unknown */
	case CONNECTION_IP_CONFIG_TYPE_STATIC: 			szType = "CONNECTION_IP_CONFIG_TYPE_STATIC"; 	break;			  	 /**< Internet */
	case CONNECTION_IP_CONFIG_TYPE_DYNAMIC: 		szType = "CONNECTION_IP_CONFIG_TYPE_DYNAMIC"; 	break;
	case CONNECTION_IP_CONFIG_TYPE_AUTO: 			szType = "CONNECTION_IP_CONFIG_TYPE_AUTO"; 		break;
	case CONNECTION_IP_CONFIG_TYPE_FIXED: 			szType = "CONNECTION_IP_CONFIG_TYPE_FIXED"; 	break;
	}
	return szType;
}

/**
* @function 		ConnectionGetProxyType
* @description	 	Maps type enums to string values
* @parameter		nType : enum value
* @return 			string of enum value
*/
char* ConnectionGetProxyType(connection_proxy_type_e nType)
{
	char *szType = "Unknown State";
	switch ( nType )
	{
	case CONNECTION_PROXY_TYPE_DIRECT: 			szType = "CONNECTION_PROXY_TYPE_DIRECT"; 		break;
	case CONNECTION_PROXY_TYPE_AUTO: 			szType = "CONNECTION_PROXY_TYPE_AUTO"; 			break;
	case CONNECTION_PROXY_TYPE_MANUAL: 			szType = "CONNECTION_PROXY_TYPE_MANUAL"; 		break;
	}
	return szType;
}

/**
* @function 		ConnectionGetIteratorType
* @description	 	Maps type enums to string values
* @parameter		nType : enum value
* @return 			string of enum value
*/
char* ConnectionGetIteratorType(connection_iterator_type_e nType)
{
	char *szType = "Unknown State";
	switch ( nType )
	{
	case CONNECTION_ITERATOR_TYPE_REGISTERED: 		szType = "CONNECTION_ITERATOR_TYPE_REGISTERED"; 		break;
	case CONNECTION_ITERATOR_TYPE_CONNECTED: 		szType = "CONNECTION_ITERATOR_TYPE_CONNECTED"; 			break;
	case CONNECTION_ITERATOR_TYPE_DEFAULT: 			szType = "CONNECTION_ITERATOR_TYPE_DEFAULT"; 			break;
	}
	return szType;
}

/**
* @function 		ConnectionGetStatisticTypeData
* @description	 	Maps type enums to string values
* @parameter		nType : enum value
* @return 			string of enum value
*/
char* ConnectionGetStatisticTypeData(connection_statistics_type_e nType)
{
	char *szType = "Unknown State";
	switch ( nType )
	{
	case CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA: 		szType = "CONNECTION_STATISTICS_TYPE_LAST_RECEIVED_DATA"; 		break;
	case CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA: 			szType = "CONNECTION_STATISTICS_TYPE_LAST_SENT_DATA"; 			break;
	case CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA: 		szType = "CONNECTION_STATISTICS_TYPE_TOTAL_RECEIVED_DATA"; 		break;
	case CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA: 			szType = "CONNECTION_STATISTICS_TYPE_TOTAL_SENT_DATA"; 			break;
	}
	return szType;
}


/**
* @function 		ConnectionManager_get_celluar_profile
* @description	 	Get registered cellular profile
* @parameter		[in] connection_h [out] connection_profile_h
* @return 			int
*/
int ConnectionManager_get_celluar_profile(connection_h connection,connection_profile_h *profile)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;
	connection_profile_type_e eConnectionProfileType;

	int nRet = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Failed to get profile iterator, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 0;
	}

	while ( connection_profile_iterator_has_next(profile_iter) )
	{
		nRet = connection_profile_iterator_next(profile_iter, &profile_h);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		nRet = connection_profile_get_type(profile_h, &eConnectionProfileType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile type, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		if ( eConnectionProfileType == CONNECTION_PROFILE_TYPE_CELLULAR )
		{
			nRet = connection_profile_clone(profile, profile_h);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				connection_profile_destroy(&profile);
				FPRINTF("[Line : %d][%s] Failed to clone cellular profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 0;
			}
			return 1;
		}
	}
	FPRINTF("[Line : %d][%s] ConnectionManager_get_celluar_profile fail to get cellular profile handle\\n", __LINE__, API_NAMESPACE);
	return 0;
}

/**
* @function 		ConnectionManager_get_MMS_type
* @description	 	Get registered cellular profile - mms type
* @parameter		[in] connection_h [out] connection_profile_h
* @return 			int
*/
int ConnectionManager_get_MMS_type(connection_h connection,connection_profile_h *profile)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;
	connection_profile_type_e eConnectionProfileType;
	connection_cellular_service_type_e service_type;

	int nRet = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line: %d][%s] Failed to get profile iterator, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 0;
	}

	while ( connection_profile_iterator_has_next(profile_iter) )
	{
		nRet = connection_profile_iterator_next(profile_iter, &profile_h);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] Failed to get profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		nRet = connection_profile_get_type(profile_h, &eConnectionProfileType);

		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line: %d][%s] Failed to get profile type, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		if ( eConnectionProfileType == CONNECTION_PROFILE_TYPE_CELLULAR )
            	{
			nRet = connection_profile_get_cellular_service_type(profile_h, &service_type);
			if(service_type== CONNECTION_CELLULAR_SERVICE_TYPE_MMS)
			{
				nRet = connection_profile_clone(profile, profile_h);
				if ( nRet != CONNECTION_ERROR_NONE )
				{
					connection_profile_destroy(&profile);
					FPRINTF("[Line: %d][%s] Failed to clone cellular profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
					return 0;
				}
				return 1;
			}

		}
          }

	FPRINTF("[Line: %d][%s] ConnectionManager_get_celluar_profile fail to get cellular profile handle\\n", __LINE__, API_NAMESPACE);
	return 0;
}


/**
* @function 		ConnectionManager_get_celluar_profile_by_name
* @description	 	Get registered cellular profile by name
* @parameter		[in] connection_h [in] profile name [out] connection_profile_h
* @return 			int
*/
int ConnectionManager_get_celluar_profile_by_name(connection_h connection, char* profileName, connection_profile_h *profile)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;
	connection_profile_type_e eConnectionProfileType;

	int nRet = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Failed to get profile iterator, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
		return 0;
	}

	while ( connection_profile_iterator_has_next(profile_iter) )
	{
		nRet = connection_profile_iterator_next(profile_iter, &profile_h);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		nRet = connection_profile_get_type(profile_h, &eConnectionProfileType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile type, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		if ( eConnectionProfileType == CONNECTION_PROFILE_TYPE_CELLULAR )
		{
			char* pszProfileName;
			nRet = connection_profile_get_name(profile_h, &pszProfileName);
			if ( nRet != CONNECTION_ERROR_NONE )
			{
				FPRINTF("[Line : %d][%s] connection_profile_get_name return error[%s]\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 0;
			}

			if ( !pszProfileName )
			{
				FPRINTF("[Line : %d][%s] connection_profile_get_name return profile name :: null, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
				return 0;
			}

			if ( strcmp(pszProfileName, profileName) == 0 )
			{
				nRet = connection_profile_clone(profile, profile_h);
				if ( nRet != CONNECTION_ERROR_NONE )
				{
					connection_profile_destroy(&profile);
					FPRINTF("[Line : %d][%s] Failed to clone cellular profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
					FREE_MEMORY(pszProfileName);
					return 0;
				}
				FREE_MEMORY(pszProfileName);
				return 1;
			}
		}
	}
	FPRINTF("[Line : %d][%s] ConnectionManager_get_celluar_profile fail to get cellular profile handle\\n", __LINE__, API_NAMESPACE);
	return 0;
}

/**
* @function 		ConnectionManager_get_wifi_profile
* @description	 	Get registered wifi profile
* @parameter		[in] connection_h [out] connection_profile_h
* @return 			int
*/
int ConnectionManager_get_wifi_profile(connection_h connection,connection_profile_h *profile)
{
	connection_profile_h profile_h;
	connection_profile_iterator_h profile_iter;
	connection_profile_type_e eConnectionProfileType;

	int nRet = connection_get_profile_iterator(connection, CONNECTION_ITERATOR_TYPE_REGISTERED, &profile_iter);
	if ( nRet != CONNECTION_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Failed to get profile iterator [%d]\\n", __LINE__, API_NAMESPACE, nRet);
		return 0;
	}

	while ( connection_profile_iterator_has_next(profile_iter) )
	{
		nRet = connection_profile_iterator_next(profile_iter, &profile_h);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		nRet = connection_profile_get_type(profile_h, &eConnectionProfileType);
		if ( nRet != CONNECTION_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Failed to get profile type, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			return 0;
		}

		if ( eConnectionProfileType == CONNECTION_PROFILE_TYPE_WIFI)
		{
			nRet = connection_profile_clone(profile, profile_h);
			if ( nRet != CONNECTION_ERROR_NONE )
		 {
			 connection_profile_destroy(&profile);
			 FPRINTF("[Line : %d][%s] Failed to clone wifi profile handle, error returned = %s\\n", __LINE__, API_NAMESPACE, ConnectionGetError(nRet));
			 return 0;
		 }
			return 1;
		}
	}

	FPRINTF("[Line : %d][%s] ConnectionManager_get_wifi_profile fail to get wifi profile handle\\n", __LINE__, API_NAMESPACE);
	return 0;
}
/** @} */
