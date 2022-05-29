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
#include "ITs-native-common-common.h"

/** @addtogroup itc-native-common
* @ingroup		itc
* @{
*/

//& set: NativeCommon

tizen_error_e error_type[] = {
	TIZEN_ERROR_NONE , /**< Successful */
	TIZEN_ERROR_NOT_PERMITTED, /**< Operation not permitted */
	TIZEN_ERROR_NO_SUCH_FILE, /**< No such file or directory */
	TIZEN_ERROR_NO_SUCH_PROCESS, /**< No such process */
	TIZEN_ERROR_INTERRUPTED_SYS_CALL, /**< Interrupted system call */
	TIZEN_ERROR_IO_ERROR, /**< I/O error */
	TIZEN_ERROR_NO_SUCH_DEVICE, /**< No such device or address */
	TIZEN_ERROR_ARGUMENT_LIST_TOO_LONG, /**< Argument list too long */
	TIZEN_ERROR_EXEC_FORMAT_ERROR, /**< Exec format error */
	TIZEN_ERROR_BAD_FILE_NUMBER, /**< Bad file number */
	TIZEN_ERROR_TRY_AGAIN, /**< Try again */
	TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
	TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
	TIZEN_ERROR_BAD_ADDRESS, /**< Bad address */
	TIZEN_ERROR_BLOCK_DEVICE_REQUIRED, /**< Block device required */
	TIZEN_ERROR_RESOURCE_BUSY, /**< Device or resource busy */
	TIZEN_ERROR_FILE_EXISTS, /**< File exists */
	TIZEN_ERROR_CROSS_DEVICE_LINK, /**< Cross-device link */
	TIZEN_ERROR_NOT_A_DIRECTORY, /**< Not a directory */
	TIZEN_ERROR_IS_A_DIRECTORY, /**< Is a directory */
	TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid function parameter */
	TIZEN_ERROR_FILE_TABLE_OVERFLOW, /**< File table overflow */
	TIZEN_ERROR_TOO_MANY_OPEN_FILES, /**< Too many open files */
	TIZEN_ERROR_TOO_NOT_A_TERMINAL, /**< Not a terminal */
	TIZEN_ERROR_TOO_TEXT_FILE_BUSY, /**< Not a terminal */
	TIZEN_ERROR_FILE_TOO_LARGE, /**< File too large */
	TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE, /**< No space left on device */
	TIZEN_ERROR_ILLEGAL_SEEK, /**< Illegal seek */
	TIZEN_ERROR_READ_ONLY_FILESYSTEM, /**< Read-only file system */
	TIZEN_ERROR_NO_DATA, /**< No data available */
	TIZEN_ERROR_TOO_MANY_LINKS, /**< Too many links */
	TIZEN_ERROR_BROKEN_PIPE, /**< Broken pipe */
	TIZEN_ERROR_ARGUMENT_OUT_OF_DOMAIN, /**< Math argument out of domain of func */
	TIZEN_ERROR_RESULT_OUT_OF_RANGE, /**< Math result not representable */
	TIZEN_ERROR_WOULD_CAUSE_DEADLOCK, /**< Resource deadlock would occur */
	TIZEN_ERROR_FILE_NAME_TOO_LONG,/**< File name too long */
	TIZEN_ERROR_FILE_NO_LOCKS_AVAILABLE, /**< No record locks available */
	TIZEN_ERROR_INVALID_OPERATION, /**< Function not implemented */
	TIZEN_ERROR_DIR_NOT_EMPTY, /**< Directory not empty */
	TIZEN_ERROR_TOO_MANY_SYMBOLIC_LINKS, /**< Too many symbolic links encountered */
	TIZEN_ERROR_WOULD_BLOCK, /**< Operation would block */
	TIZEN_ERROR_CORRUPTED_SHARED_LIB, /**< Accessing a corrupted shared library */
	TIZEN_ERROR_LIB_SECTION_CORRUPTED, /**< .lib section in a.out corrupted */
	TIZEN_ERROR_LINK_TOO_MANY_SHARED_LIB, /**< Attempting to link in too many shared libraries */
	TIZEN_ERROR_SHARED_LIB_EXEC, /**< Cannot exec a shared library directly */
	TIZEN_ERROR_ILLEGAL_BYTE_SEQ, /**< Illegal byte sequence */
	TIZEN_ERROR_SYSTEM_CALL_RESTART, /**< Interrupted system call should be restarted */
	TIZEN_ERROR_STREAMS_PIPE, /**< Streams pipe error */
	TIZEN_ERROR_TOO_MANY_USERS, /**< Too many users */
	TIZEN_ERROR_NON_SOCKET, /**< Socket operation on non-socket */
	TIZEN_ERROR_NO_DEST_ADDRESS, /**< Destination address required */
	TIZEN_ERROR_MSG_TOO_LONG, /**< Message too long */
	TIZEN_ERROR_PROTOCOL_WRONG_TYPE, /**< Protocol wrong type for socket */
	TIZEN_ERROR_PROTOCOL_NOT_AVALIABLE, /**< Protocol not available */
	TIZEN_ERROR_PROTOCOL_NOT_SUPPORTED, /**< Protocol not supported */
	TIZEN_ERROR_SOCKET_TYPE_NOT_SUPPORTED, /**< Socket type not supported */
	TIZEN_ERROR_ENDPOINT_OPERATIN_NOT_SUPPORTED, /**< Operation not supported on transport endpoint */
	TIZEN_ERROR_PROTOCOL_FAMILY_NOT_SUPPORTED, /**< Protocol family not supported */
	TIZEN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED, /**< Address family not supported by protocol */
	TIZEN_ERROR_ADDRES_IN_USE, /**< Address already in use */
	TIZEN_ERROR_CANNOT_ASSIGN_ADDRESS, /**< Cannot assign requested address */
	TIZEN_ERROR_NETWORK_DOWN, /**< Network is down */
	TIZEN_ERROR_NETWORK_UNREACHABLE, /**< Network is unreachable */
	TIZEN_ERROR_NETWORK_RESET, /**< Network dropped connection because of reset */
	TIZEN_ERROR_CONNECTION_ABORTED, /**< Software caused connection abort */
	TIZEN_ERROR_CONNECTION_RESET_BY_PEER, /**< Connection reset by peer */
	TIZEN_ERROR_BUFFER_SPACE, /**< No buffer space available */
	TIZEN_ERROR_ENDPOINT_CONNECTED, /**< Transport endpoint is already connected */
	TIZEN_ERROR_ENDPOINT_NOT_CONNECTED, /**< Transport endpoint is not connected */
	TIZEN_ERROR_ENDPOINT_SHUTDOWN, /**< Cannot send after transport endpoint shutdown */
	TIZEN_ERROR_TOO_MANY_REFERENCES, /**< Too many references: cannot splice */
	TIZEN_ERROR_CONNECTION_TIME_OUT, /**< Connection timed out */
	TIZEN_ERROR_CONNECTION_REFUSED, /**< Connection refused */
	TIZEN_ERROR_HOST_DOWN, /**< Host is down */
	TIZEN_ERROR_NO_ROUTE_TO_HOST, /**< No route to host */
	TIZEN_ERROR_ALREADY_IN_PROGRESS, /**< Operation already in progress */
	TIZEN_ERROR_NOW_IN_PROGRESS, /**< Operation now in progress */
	TIZEN_ERROR_STALE_NFS_FILE_HANDLE, /**< Stale NFS file handle */
	TIZEN_ERROR_STRUCTURE_UNCLEAN, /**< Structure needs cleaning */
	TIZEN_ERROR_NOT_XENIX_NAMED_TYPE_FILE, /**< Not a XENIX named type file */
	TIZEN_ERROR_NO_XENIX_SEMAPHORES_AVAILABLE, /**< No XENIX semaphores available */
	TIZEN_ERROR_IS_NAMED_TYPE_FILE, /**< Is a named type file */
	TIZEN_ERROR_REMOTE_IO, /**< Remote I/O error */
	TIZEN_ERROR_QUOTA_EXCEEDED, /**< Quota exceeded */
	TIZEN_ERROR_NO_MEDIUM, /**< No medium found */
	TIZEN_ERROR_WRONG_MEDIUM_TYPE, /**< Wrong medium type */
	TIZEN_ERROR_CANCELED, /**< Operation Canceled */
	TIZEN_ERROR_KEY_NOT_AVAILABLE, /**< Required key not available */
	TIZEN_ERROR_KEY_EXPIRED, /**< Key has expired */
	TIZEN_ERROR_KEY_REVOKED, /**< Key has been revoked */
	TIZEN_ERROR_KEY_REJECTED, /**< Key was rejected by service */
	TIZEN_ERROR_OWNER_DEAD, /**< Owner died (for robust mutexes) */
	TIZEN_ERROR_UNKNOWN, /**< Unknown error */
	TIZEN_ERROR_TIMED_OUT, /**< Time out */
	TIZEN_ERROR_NOT_SUPPORTED, /**< Not supported */
	TIZEN_ERROR_DEVICE_POLICY_RESTRICTION, /**< Restriction by Device Policy */ 
	TIZEN_ERROR_USER_NOT_CONSENTED, /**< Not Consented */
	TIZEN_ERROR_END_OF_COLLECTION
};

/**
* @function 		ITs_native_common_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_native_common_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Native_Common_p\\n", __LINE__, APINAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_native_common_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_native_common_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Native_Common_p\\n", __LINE__, APINAMESPACE);
#endif
}

/** @addtogroup	itc-native-common-testcases
* @brief 		Integration testcases for module native-common
* @ingroup		itc-native-common
* @{
*/

//& purpose: To set and get the last error code in thread
//& type: auto
/**
* @testcase 		ITc_native_common_set_get_last_result_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To set and get the last error code in thread
* @scenario			Set the last error code to be returned in thread\n
*					Get the last error code in thread
* @apicovered		set_last_result, get_last_result
* @passcase			When set_last_result and get_last_result is successful.
* @failcase			If target API set_last_result or get_last_result API fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_native_common_set_get_last_result_p(void)
{
	START_TEST;

	int enum_size = sizeof(error_type) / sizeof(error_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		// Target API
		set_last_result(error_type[enum_counter]);

		// Target API
		tizen_error_e nGetResult = get_last_result();
		if ( nGetResult != error_type[enum_counter] )
		{
			FPRINTF("[Line : %d][%s] get_last_result return value %s mismatched set_last_result value %s\\n",
				__LINE__, APINAMESPACE, NativeCommonGetError(nGetResult), NativeCommonGetError(error_type[enum_counter]));
			return 1;
		}

#if DEBUG
		FPRINTF("[Line : %d][%s] get_last_result return value %s matched set_last_result value %s\\n",
			__LINE__, APINAMESPACE, NativeCommonGetError(nGetResult), NativeCommonGetError(error_type[enum_counter]));
#endif
	}

	return 0;
}

//& purpose: To get the last error message in thread
//& type: auto
/**
* @testcase 		ITc_native_common_get_error_message_p
* @since_tizen		2.3
* @author           SRID(gupta.sanjay)
* @reviewer         SRID(ravi.kumar2)
* @type 			auto
* @description		To get the last error message in thread
* @scenario			Set the last error code to be returned in thread\n
*					Get the last error message in thread
* @apicovered		get_error_message
* @passcase			When get_error_message is successful.
* @failcase			If target API get_error_message API fails.
* @precondition		NA
* @postcondition	NA
*/
int ITc_native_common_get_error_message_p(void)
{
	START_TEST;

	int enum_size = sizeof(error_type) / sizeof(error_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0; enum_counter<enum_size; enum_counter++ )
	{
		// Target API
		char* nGetMessage = get_error_message(error_type[enum_counter]);
		if ( nGetMessage == NULL )
		{
			FPRINTF("[Line : %d][%s] get_error_message returned invalid message %s for error code %s\\n",
				__LINE__, APINAMESPACE, nGetMessage, NativeCommonGetError(error_type[enum_counter]));
			return 1;
		}

#if DEBUG
		FPRINTF("[Line : %d][%s] get_error_message returned valid message %s for error code %s\\n",
			__LINE__, APINAMESPACE, nGetMessage, NativeCommonGetError(error_type[enum_counter]));
#endif
	}

	return 0;
}

/** @} */ //end of itc-native-common
/** @} */ //end of itc-native-common-testcases
