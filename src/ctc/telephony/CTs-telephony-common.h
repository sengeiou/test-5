#ifndef _CTS_TELEPHONY_COMMON_H_
#define _CTS_TELEPHONY_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <messages.h>

/** @addtogroup ctc-telephony
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE			"TELEPHONY_CTC"
#define TELEPHONY_FEATURE		"http://tizen.org/feature/network.telephony"
#define SMS_FEATURE				"http://tizen.org/feature/network.telephony.sms"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

char* MessagesGetError(int nRet);

/** @} */ //end of ctc-telephony

#endif  //_CTS_TELEPHONY_COMMON_H_
