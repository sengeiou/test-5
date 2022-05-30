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

//Add helper function definitions here

/**
* @function 		NativeCommonGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* NativeCommonGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch (nRet)
	{
	case TIZEN_ERROR_NONE:								szErrorVal = "TIZEN_ERROR_NONE";							break;		/* Successful */
	case TIZEN_ERROR_NOT_PERMITTED:						szErrorVal = "TIZEN_ERROR_NOT_PERMITTED";					break;		/* Operation not permitted */
	case TIZEN_ERROR_NO_SUCH_FILE:						szErrorVal = "TIZEN_ERROR_NO_SUCH_FILE";					break;		/* No such file or directory */
	case TIZEN_ERROR_NO_SUCH_PROCESS:					szErrorVal = "TIZEN_ERROR_NO_SUCH_PROCESS";					break;		/* No such process */
	case TIZEN_ERROR_INTERRUPTED_SYS_CALL:				szErrorVal = "TIZEN_ERROR_INTERRUPTED_SYS_CALL";			break;		/* Interrupted system call */
	case TIZEN_ERROR_IO_ERROR:							szErrorVal = "TIZEN_ERROR_IO_ERROR";						break;		/* I/O error */
	case TIZEN_ERROR_NO_SUCH_DEVICE:					szErrorVal = "TIZEN_ERROR_NO_SUCH_DEVICE";					break;		/* No such device or address */
	case TIZEN_ERROR_ARGUMENT_LIST_TOO_LONG:			szErrorVal = "TIZEN_ERROR_ARGUMENT_LIST_TOO_LONG";			break;		/* Argument list too long */
	case TIZEN_ERROR_EXEC_FORMAT_ERROR:					szErrorVal = "TIZEN_ERROR_EXEC_FORMAT_ERROR";				break;		/* Exec format error */
	case TIZEN_ERROR_BAD_FILE_NUMBER:					szErrorVal = "TIZEN_ERROR_BAD_FILE_NUMBER";					break;		/* Bad file number */
	//case TIZEN_ERROR_TRY_AGAIN:							szErrorVal = "TIZEN_ERROR_TRY_AGAIN";					break;		/* Try again */
	case TIZEN_ERROR_OUT_OF_MEMORY:						szErrorVal = "TIZEN_ERROR_OUT_OF_MEMORY";					break;		/* Out of memory */
	case TIZEN_ERROR_PERMISSION_DENIED:					szErrorVal = "TIZEN_ERROR_PERMISSION_DENIED";				break;		/* Permission denied */
	case TIZEN_ERROR_BAD_ADDRESS:						szErrorVal = "TIZEN_ERROR_BAD_ADDRESS";						break;		/* Bad address */
	case TIZEN_ERROR_BLOCK_DEVICE_REQUIRED:				szErrorVal = "TIZEN_ERROR_BLOCK_DEVICE_REQUIRED";			break;		/* Block device required */
	case TIZEN_ERROR_RESOURCE_BUSY:						szErrorVal = "TIZEN_ERROR_RESOURCE_BUSY";					break;		/* Device or resource busy */
	case TIZEN_ERROR_FILE_EXISTS:						szErrorVal = "TIZEN_ERROR_FILE_EXISTS";						break;		/* File exists */
	case TIZEN_ERROR_CROSS_DEVICE_LINK:					szErrorVal = "TIZEN_ERROR_CROSS_DEVICE_LINK";				break;		/* Cross-device link */
	case TIZEN_ERROR_NOT_A_DIRECTORY:					szErrorVal = "TIZEN_ERROR_NOT_A_DIRECTORY";					break;		/* Not a directory */
	case TIZEN_ERROR_IS_A_DIRECTORY:					szErrorVal = "TIZEN_ERROR_IS_A_DIRECTORY";					break;		/* Is a directory */
	case TIZEN_ERROR_INVALID_PARAMETER:					szErrorVal = "TIZEN_ERROR_INVALID_PARAMETER";				break;		/* Invalid function parameter */
	case TIZEN_ERROR_FILE_TABLE_OVERFLOW:				szErrorVal = "TIZEN_ERROR_FILE_TABLE_OVERFLOW";				break;		/* File table overflow */
	case TIZEN_ERROR_TOO_MANY_OPEN_FILES:				szErrorVal = "TIZEN_ERROR_TOO_MANY_OPEN_FILES";				break;		/* Too many open files */
	case TIZEN_ERROR_TOO_NOT_A_TERMINAL:				szErrorVal = "TIZEN_ERROR_TOO_NOT_A_TERMINAL";				break;		/* Not a terminal */
	case TIZEN_ERROR_TOO_TEXT_FILE_BUSY:				szErrorVal = "TIZEN_ERROR_TOO_TEXT_FILE_BUSY";				break;		/* Not a terminal */
	case TIZEN_ERROR_FILE_TOO_LARGE:					szErrorVal = "TIZEN_ERROR_FILE_TOO_LARGE";					break;		/* File too large */
	case TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE:			szErrorVal = "TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE";			break;		/* No space left on device */
	case TIZEN_ERROR_ILLEGAL_SEEK:						szErrorVal = "TIZEN_ERROR_ILLEGAL_SEEK";					break;		/* Illegal seek */
	case TIZEN_ERROR_READ_ONLY_FILESYSTEM:				szErrorVal = "TIZEN_ERROR_READ_ONLY_FILESYSTEM";			break;		/* Read-only file system */
	case TIZEN_ERROR_NO_DATA:							szErrorVal = "TIZEN_ERROR_NO_DATA";							break;		/* No data available */
	case TIZEN_ERROR_TOO_MANY_LINKS:					szErrorVal = "TIZEN_ERROR_TOO_MANY_LINKS";					break;		/* Too many links */
	case TIZEN_ERROR_BROKEN_PIPE:						szErrorVal = "TIZEN_ERROR_BROKEN_PIPE";						break;		/* Broken pipe */
	case TIZEN_ERROR_ARGUMENT_OUT_OF_DOMAIN:			szErrorVal = "TIZEN_ERROR_ARGUMENT_OUT_OF_DOMAIN";			break;		/* Math argument out of domain of func */
	case TIZEN_ERROR_RESULT_OUT_OF_RANGE:				szErrorVal = "TIZEN_ERROR_RESULT_OUT_OF_RANGE";				break;		/* Math result not representable */
	case TIZEN_ERROR_WOULD_CAUSE_DEADLOCK:				szErrorVal = "TIZEN_ERROR_WOULD_CAUSE_DEADLOCK";			break;		/* Resource deadlock would occur */
	case TIZEN_ERROR_FILE_NAME_TOO_LONG:				szErrorVal = "TIZEN_ERROR_FILE_NAME_TOO_LONG";				break;		/* File name too long */
	case TIZEN_ERROR_FILE_NO_LOCKS_AVAILABLE:			szErrorVal = "TIZEN_ERROR_FILE_NO_LOCKS_AVAILABLE";			break;		/* No record locks available */
	case TIZEN_ERROR_INVALID_OPERATION:					szErrorVal = "TIZEN_ERROR_INVALID_OPERATION";				break;		/* Function not implemented */
	case TIZEN_ERROR_DIR_NOT_EMPTY:						szErrorVal = "TIZEN_ERROR_DIR_NOT_EMPTY";					break;		/* Directory not empty */
	case TIZEN_ERROR_TOO_MANY_SYMBOLIC_LINKS:			szErrorVal = "TIZEN_ERROR_TOO_MANY_SYMBOLIC_LINKS";			break;		/* Too many symbolic links encountered */
	case TIZEN_ERROR_WOULD_BLOCK:						szErrorVal = "TIZEN_ERROR_WOULD_BLOCK or TIZEN_ERROR_TRY_AGAIN";		break;		/* Operation would block */
	case TIZEN_ERROR_CORRUPTED_SHARED_LIB:				szErrorVal = "TIZEN_ERROR_CORRUPTED_SHARED_LIB";			break;		/* Accessing a corrupted shared library */
	case TIZEN_ERROR_LIB_SECTION_CORRUPTED:				szErrorVal = "TIZEN_ERROR_LIB_SECTION_CORRUPTED";			break;		/* .lib section in a.out corrupted */
	case TIZEN_ERROR_LINK_TOO_MANY_SHARED_LIB:			szErrorVal = "TIZEN_ERROR_LINK_TOO_MANY_SHARED_LIB";		break;		/* Attempting to link in too many shared libraries */
	case TIZEN_ERROR_SHARED_LIB_EXEC:					szErrorVal = "TIZEN_ERROR_SHARED_LIB_EXEC";					break;		/* Cannot exec a shared library directly */
	case TIZEN_ERROR_ILLEGAL_BYTE_SEQ:					szErrorVal = "TIZEN_ERROR_ILLEGAL_BYTE_SEQ";				break;		/* Illegal byte sequence */
	case TIZEN_ERROR_SYSTEM_CALL_RESTART:				szErrorVal = "TIZEN_ERROR_SYSTEM_CALL_RESTART";				break;		/* Interrupted system call should be restarted */
	case TIZEN_ERROR_STREAMS_PIPE:						szErrorVal = "TIZEN_ERROR_STREAMS_PIPE";					break;		/* Streams pipe error */
	case TIZEN_ERROR_TOO_MANY_USERS:					szErrorVal = "TIZEN_ERROR_TOO_MANY_USERS";					break;		/* Too many users */
	case TIZEN_ERROR_NON_SOCKET:						szErrorVal = "TIZEN_ERROR_NON_SOCKET";						break;		/* Socket operation on non-socket */
	case TIZEN_ERROR_NO_DEST_ADDRESS:					szErrorVal = "TIZEN_ERROR_NO_DEST_ADDRESS";					break;		/* Destination address required */
	case TIZEN_ERROR_MSG_TOO_LONG:						szErrorVal = "TIZEN_ERROR_MSG_TOO_LONG";					break;		/* Message too long */
	case TIZEN_ERROR_PROTOCOL_WRONG_TYPE:				szErrorVal = "TIZEN_ERROR_PROTOCOL_WRONG_TYPE";				break;		/* Protocol wrong type for socket */
	case TIZEN_ERROR_PROTOCOL_NOT_AVALIABLE:			szErrorVal = "TIZEN_ERROR_PROTOCOL_NOT_AVALIABLE";			break;		/* Protocol not available */
	case TIZEN_ERROR_PROTOCOL_NOT_SUPPORTED:			szErrorVal = "TIZEN_ERROR_PROTOCOL_NOT_SUPPORTED";			break;		/* Protocol not supported */
	case TIZEN_ERROR_SOCKET_TYPE_NOT_SUPPORTED:			szErrorVal = "TIZEN_ERROR_SOCKET_TYPE_NOT_SUPPORTED";		break;		/* Socket type not supported */
	case TIZEN_ERROR_ENDPOINT_OPERATIN_NOT_SUPPORTED:	szErrorVal = "TIZEN_ERROR_ENDPOINT_OPERATIN_NOT_SUPPORTED";	break;		/* Operation not supported on transport endpoint */
	case TIZEN_ERROR_PROTOCOL_FAMILY_NOT_SUPPORTED:		szErrorVal = "TIZEN_ERROR_PROTOCOL_FAMILY_NOT_SUPPORTED";	break;		/* Protocol family not supported */
	case TIZEN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED:		szErrorVal = "TIZEN_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED";	break;		/* Address family not supported by protocol */
	case TIZEN_ERROR_ADDRES_IN_USE:						szErrorVal = "TIZEN_ERROR_ADDRES_IN_USE";					break;		/* Address already in use */
	case TIZEN_ERROR_CANNOT_ASSIGN_ADDRESS:				szErrorVal = "TIZEN_ERROR_CANNOT_ASSIGN_ADDRESS";			break;		/* Cannot assign requested address */
	case TIZEN_ERROR_NETWORK_DOWN:						szErrorVal = "TIZEN_ERROR_NETWORK_DOWN";					break;		/* Network is down */
	case TIZEN_ERROR_NETWORK_UNREACHABLE:				szErrorVal = "TIZEN_ERROR_NETWORK_UNREACHABLE";				break;		/* Network is unreachable */
	case TIZEN_ERROR_NETWORK_RESET:						szErrorVal = "TIZEN_ERROR_NETWORK_RESET";					break;		/* Network dropped connection because of reset */
	case TIZEN_ERROR_CONNECTION_ABORTED:				szErrorVal = "TIZEN_ERROR_CONNECTION_ABORTED";				break;		/* Software caused connection abort */
	case TIZEN_ERROR_CONNECTION_RESET_BY_PEER:			szErrorVal = "TIZEN_ERROR_CONNECTION_RESET_BY_PEER";		break;		/* Connection reset by peer */
	case TIZEN_ERROR_BUFFER_SPACE:						szErrorVal = "TIZEN_ERROR_BUFFER_SPACE";					break;		/* No buffer space available */
	case TIZEN_ERROR_ENDPOINT_CONNECTED:				szErrorVal = "TIZEN_ERROR_ENDPOINT_CONNECTED";				break;		/* Transport endpoint is already connected */
	case TIZEN_ERROR_ENDPOINT_NOT_CONNECTED:			szErrorVal = "TIZEN_ERROR_ENDPOINT_NOT_CONNECTED";			break;		/* Transport endpoint is not connected */
	case TIZEN_ERROR_ENDPOINT_SHUTDOWN:					szErrorVal = "TIZEN_ERROR_ENDPOINT_SHUTDOWN";				break;		/* Cannot send after transport endpoint shutdown */
	case TIZEN_ERROR_TOO_MANY_REFERENCES:				szErrorVal = "TIZEN_ERROR_TOO_MANY_REFERENCES";				break;		/* Too many references: cannot splice */
	case TIZEN_ERROR_CONNECTION_TIME_OUT:				szErrorVal = "TIZEN_ERROR_CONNECTION_TIME_OUT";				break;		/* Connection timed out */
	case TIZEN_ERROR_CONNECTION_REFUSED:				szErrorVal = "TIZEN_ERROR_CONNECTION_REFUSED";				break;		/* Connection refused */
	case TIZEN_ERROR_HOST_DOWN:							szErrorVal = "TIZEN_ERROR_HOST_DOWN";						break;		/* Host is down */
	case TIZEN_ERROR_NO_ROUTE_TO_HOST:					szErrorVal = "TIZEN_ERROR_NO_ROUTE_TO_HOST";				break;		/* No route to host */
	case TIZEN_ERROR_ALREADY_IN_PROGRESS:				szErrorVal = "TIZEN_ERROR_ALREADY_IN_PROGRESS";				break;		/* Operation already in progress */
	case TIZEN_ERROR_NOW_IN_PROGRESS:					szErrorVal = "TIZEN_ERROR_NOW_IN_PROGRESS";					break;		/* Operation now in progress */
	case TIZEN_ERROR_STALE_NFS_FILE_HANDLE:				szErrorVal = "TIZEN_ERROR_STALE_NFS_FILE_HANDLE";			break;		/* Stale NFS file handle */
	case TIZEN_ERROR_STRUCTURE_UNCLEAN:					szErrorVal = "TIZEN_ERROR_STRUCTURE_UNCLEAN";				break;		/* Structure needs cleaning */
	case TIZEN_ERROR_NOT_XENIX_NAMED_TYPE_FILE:			szErrorVal = "TIZEN_ERROR_NOT_XENIX_NAMED_TYPE_FILE";		break;		/* Not a XENIX named type file */
	case TIZEN_ERROR_NO_XENIX_SEMAPHORES_AVAILABLE:		szErrorVal = "TIZEN_ERROR_NO_XENIX_SEMAPHORES_AVAILABLE";	break;		/* No XENIX semaphores available */
	case TIZEN_ERROR_IS_NAMED_TYPE_FILE:				szErrorVal = "TIZEN_ERROR_IS_NAMED_TYPE_FILE";				break;		/* Is a named type file */
	case TIZEN_ERROR_REMOTE_IO:							szErrorVal = "TIZEN_ERROR_REMOTE_IO";						break;		/* Remote I/O error */
	case TIZEN_ERROR_QUOTA_EXCEEDED:					szErrorVal = "TIZEN_ERROR_QUOTA_EXCEEDED";					break;		/* Quota exceeded */
	case TIZEN_ERROR_NO_MEDIUM:							szErrorVal = "TIZEN_ERROR_NO_MEDIUM";						break;		/* No medium found */
	case TIZEN_ERROR_WRONG_MEDIUM_TYPE:					szErrorVal = "TIZEN_ERROR_WRONG_MEDIUM_TYPE";				break;		/* Wrong medium type */
	case TIZEN_ERROR_CANCELED:							szErrorVal = "TIZEN_ERROR_CANCELED";						break;		/* Operation Canceled */
	case TIZEN_ERROR_KEY_NOT_AVAILABLE:					szErrorVal = "TIZEN_ERROR_KEY_NOT_AVAILABLE";				break;		/* Required key not available */
	case TIZEN_ERROR_KEY_EXPIRED:						szErrorVal = "TIZEN_ERROR_KEY_EXPIRED";						break;		/* Key has expired */
	case TIZEN_ERROR_KEY_REVOKED:						szErrorVal = "TIZEN_ERROR_KEY_REVOKED";						break;		/* Key has been revoked */
	case TIZEN_ERROR_KEY_REJECTED:						szErrorVal = "TIZEN_ERROR_KEY_REJECTED";					break;		/* Key was rejected by service */
	case TIZEN_ERROR_OWNER_DEAD:						szErrorVal = "TIZEN_ERROR_OWNER_DEAD";						break;		/* Owner died (for robust mutexes) */
	case TIZEN_ERROR_UNKNOWN:							szErrorVal = "TIZEN_ERROR_UNKNOWN";							break;		/* Unknown error */
	case TIZEN_ERROR_TIMED_OUT:							szErrorVal = "TIZEN_ERROR_TIMED_OUT";						break;		/* Time out */
	case TIZEN_ERROR_NOT_SUPPORTED:						szErrorVal = "TIZEN_ERROR_NOT_SUPPORTED";					break;		/* Not supported */
	case TIZEN_ERROR_USER_NOT_CONSENTED:				szErrorVal = "TIZEN_ERROR_USER_NOT_CONSENTED";				break;		/* Not Consented */
	default:											szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}

/** @} */ //end of itc-native-common