#include "CTs-telephony-common.h"

//Add helper function definitions here

/**
 * @function 		MessagesGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* MessagesGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch( nRet )
	{
		case MESSAGES_ERROR_INVALID_PARAMETER:					szErrorVal = "MESSAGES_ERROR_INVALID_PARAMETER";		break;
		case MESSAGES_ERROR_OUT_OF_MEMORY:						szErrorVal = "MESSAGES_ERROR_OUT_OF_MEMORY";			break;		
		case MESSAGES_ERROR_SERVER_NOT_READY:					szErrorVal = "MESSAGES_ERROR_SERVER_NOT_READY";			break;
		case MESSAGES_ERROR_COMMUNICATION_WITH_SERVER_FAILED:	szErrorVal = "MESSAGES_ERROR_COMMUNICATION_WITH";		break;
		case MESSAGES_ERROR_OPERATION_FAILED:					szErrorVal = "MESSAGES_ERROR_OPERATION_FAILED";			break;
		case MESSAGES_ERROR_SENDING_FAILED:						szErrorVal = "MESSAGES_ERROR_SENDING_FAILED";			break;
		case MESSAGES_ERROR_OUT_OF_RANGE:						szErrorVal = "MESSAGES_ERROR_OUT_OF_RANGE";				break;
		case MESSAGES_ERROR_NO_SIM_CARD:						szErrorVal = "MESSAGES_ERROR_NO_SIM_CARD";				break;
		case MESSAGES_ERROR_NO_DATA:							szErrorVal = "MESSAGES_ERROR_NO_DATA";					break;
		case MESSAGES_ERROR_PERMISSION_DENIED:					szErrorVal = "MESSAGES_ERROR_PERMISSION_DENIED";		break;
		case MESSAGES_ERROR_NOT_SUPPORTED:						szErrorVal = "MESSAGES_ERROR_NOT_SUPPORTED";			break;
		case MESSAGES_ERROR_NONE:								szErrorVal = "MESSAGES_ERROR_NONE";						break;
		default:												szErrorVal = "MESSAGES_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}