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
#include "assert.h"
#include <push-service.h>
#include <app_control.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <stdio.h>
#include <system_info.h>

#include "sppc-common.h"
//& set: Push Service

#define OP_NONE 0
#define OP_REG 1
/**
 * UTC's push id
 * utc's daily quota is very small
 */

static bool push_supported= true;

typedef enum {
    CMD_GETID, CMD_DRG, CMD_END, CMD_UNREAD, CMD_UNREAD_ASYNC, CMD_SENDPUSH
} Commands;

typedef enum {
    NOTIFY_GETUNREAD, NOTIFY_GETDATA, NOTIFY_GETMSG, NOTIFY_GETTIME,
    NOTIFY_GETREQID, NOTIFY_GETSENDER, NOTIFY_GETSESSIONINFO, NOTIFY_GETTYPE, NOTIFY_NONE
} NotificationOP;

static bool get_service_error = false;
static bool state_cb_error = false;
static bool noti_cb_error = false;
static bool start_error = false;
static bool timeout_error = false;
static int ret_error = 0;

/**
* @function 		timeout_func
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
static gboolean timeout_func(gpointer data)
{
    _LOG("Timeout! Test case BLOCK!\n");
    timeout_error = true;
    g_main_loop_quit((GMainLoop *)data);
    return FALSE;
}

/**
* @function 		_get_service
* @description	 	Called to get app_control handle to start test
* @parameter		const char *tizen_app_id, const char *bd
* @return 			app_control_h
*/
static app_control_h _get_service(const char *tizen_app_id, const char *bd)
{
    char *key;
    char *val;
    char *s;
    char *t;
    app_control_h svc;

    const char *d = ",";

    int ret = app_control_create(&svc);
    if(APP_CONTROL_ERROR_NONE != ret) {
        _LOG("service_create() function failed!");
        get_service_error = true;
        return NULL;
    }

    if(!svc) {
        _LOG("svc is NULL.");
        return NULL;
    }

    if(tizen_app_id) {
        ret = app_control_set_app_id(svc, tizen_app_id);
        if(APP_CONTROL_ERROR_NONE != ret) {
            _LOG("service_set_app_id() function failed!");
            get_service_error = true;
            return svc;
        }
    }

    if(!bd) {
        _LOG("bd is NULL.");
        return svc;
    }

    val = NULL;
    key = strdup(bd);

    if(!key) {
        _LOG("key is NULL.");
        return svc;
    }

    t = strtok(key, d);

    while (t) {
        s = t;
        while (*s) {
            if(*s == ':') {
                *s = '\0';
                val = s + 1;
                break;
            }
            s++;
        }
        if(*t && (val && *val)) {
            ret = app_control_add_extra_data(svc, t, val);
            if(APP_CONTROL_ERROR_NONE != ret) {
                _LOG("service_add_extra_data(svc, t, val) function failed!");
                get_service_error = true;
    			free(key);
                return svc;
            }
        }
        t = strtok(NULL, d);
    }

    free(key);
    return svc;
}

typedef struct {
    Commands cmd;
    char *app_id;
    char *app_secret;
    const char *tizen_app_id;
    const char *bd;
    const char *userdata;
} PushT;

typedef struct {
    push_service_connection_h conn;
    PushT *pt;
    GMainLoop *ml;
    int op;
    NotificationOP notify_op;
    char *regid;
} PushData;

/**
* @function 		_reg_cb
* @description	 	Called with the result of a registration
* @parameter		push_service_result_e res, const char *msg, void *data
* @return 			NA
*/
static void _reg_cb(push_service_result_e res, const char *msg, void *data)
{
    _LOG("register callback result was called.");
    PushData *pv = data;
    if(CMD_END == pv->pt->cmd && NOTIFY_NONE == pv->notify_op) {
        g_main_loop_quit(pv->ml);
    }
}

/**
* @function 		_drg_cb
* @description	 	Called with the result of a deregistration.
* @parameter		push_service_result_e res, const char *msg, void *data
* @return 			NA
*/
static void _drg_cb(push_service_result_e res, const char *msg, void *data)
{
    _LOG("deregister callback result was called.");
    PushData *pv = data;
    if(NOTIFY_NONE == pv->notify_op) {
        g_main_loop_quit(pv->ml);
    }
}

/**
* @function 		_st_cb
* @description	 	Called when the push service state is refreshed.
* @parameter		push_service_state_e st, const char *err, void *data
* @return 			NA
*/
static void _st_cb(push_service_state_e st, const char *err, void *data)
{
    _LOG("_st_cb was called.");

    PushData *pv = data;
    PushT *pt = pv->pt;
    app_control_h svc = NULL;

    if(OP_NONE == pv->op) {
        if(NOTIFY_NONE == pv->notify_op) {
            g_main_loop_quit(pv->ml);
        }
        return;
    }

    switch (st) {
        case PUSH_SERVICE_STATE_UNREGISTERED: {
            _LOG("State was PUSH_SERVICE_STATE_UNREGISTERED.");
            get_service_error = false;
            svc = _get_service(pt->tizen_app_id, pt->bd);
            if(get_service_error) {
                _LOG("_get_service() function failed!");
                state_cb_error = true;
                g_main_loop_quit(pv->ml);
                break;
            }

            _LOG("push_service_register() function is being called.");
            int ret = push_service_register(pv->conn, _reg_cb, pv);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_register() function failed!");
                state_cb_error = true;
                g_main_loop_quit(pv->ml);
            }
        } break;

        case PUSH_SERVICE_STATE_REGISTERED: {
            _LOG("State was PUSH_SERVICE_STATE_REGISTERED.");
	    /* get id */
            if(CMD_GETID == pt->cmd) {
                char* regid = NULL;
                _LOG("push_service_get_registration_id() function is being called.");
                int ret = push_service_get_registration_id(pv->conn, &regid);
                if(PUSH_SERVICE_ERROR_NONE != ret) {
                    _LOG("push_service_get_registration_id() function failed!");
                    state_cb_error = true;
                    g_main_loop_quit(pv->ml);
                }
                free(regid);
            /* deregister */
            } else if(CMD_DRG == pt->cmd || CMD_END == pt->cmd) {
                _LOG("push_service_deregister() function is being called.");
                int ret = push_service_deregister(pv->conn, _drg_cb, pv);
                if(PUSH_SERVICE_ERROR_NONE != ret) {
                    _LOG("push_service_deregister() function failed!");
                    state_cb_error = true;
                    g_main_loop_quit(pv->ml);
                }
            /* get unread notification */
            } else if(CMD_UNREAD == pt->cmd) {
                _LOG("push_service_get_unread_notification() function is being called.");
                push_service_notification_h noti;
                int ret = push_service_get_unread_notification(pv->conn, &noti);
                if(PUSH_SERVICE_ERROR_NO_DATA != ret) {
                    _LOG("push_service_get_unread_notification() function failed!");
                    state_cb_error = true;
                    g_main_loop_quit(pv->ml);
                } else {
                    push_service_free_notification(noti);
                }
            /* get unread notification async */
            } else if(CMD_UNREAD_ASYNC == pt->cmd) {
                _LOG("push_service_request_unread_notification() function is being called after 1 second.");
		sleep(1);
                int ret = push_service_request_unread_notification(pv->conn);
                if(PUSH_SERVICE_ERROR_NONE != ret) {
                    _LOG("push_service_request_unread_notification() function failed!");
                    state_cb_error = true;
                    g_main_loop_quit(pv->ml);
                }
            } else if(CMD_SENDPUSH == pt->cmd) {
                _LOG("send push data to server");
		_LOG("push_service_deregister() function is being called.");
                int ret = push_service_get_registration_id(pv->conn, &pv->regid);
                if (PUSH_SERVICE_ERROR_NONE != ret) {
                    _LOG("push_service_get_registration_id() function failed!");
                    state_cb_error = true;
                    g_main_loop_quit(pv->ml);
		} else {
                    _LOG("regid : %s", pv->regid);
                }
            }

            if(NOTIFY_NONE == pv->notify_op && CMD_END != pt->cmd) {
		_LOG("NOTIFY_NONE && !CMD_END\n");
                g_main_loop_quit(pv->ml);
            }
        } break;

        default: {
            _LOG("unknown status!");
            state_cb_error = true;
            g_main_loop_quit(pv->ml);
        } break;
    }
}

/**
* @function 		_noti_cb
* @description	 	Called to handle a notification.
* @parameter		const push_service_notification_h noti, void *data
* @return 			NA
*/
static void _noti_cb(const push_service_notification_h noti, void *data)
{
    _LOG("_noti_cb was called.");
    PushData *pv = data;
    int ret;

    switch(pv->notify_op){
        case NOTIFY_GETDATA: {
            char *appdata = NULL;
            _LOG("push_service_get_notification_data() function is being called.");
            ret = push_service_get_notification_data(noti, &appdata);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_data() function failed!");
                noti_cb_error = true;
            }
            free(appdata);
        } break;

        case NOTIFY_GETMSG: {
            char *msg = NULL;
            _LOG("push_service_get_notification_message() function is being called.");
            ret = push_service_get_notification_message(noti, &msg);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_message() function failed!");
                noti_cb_error = true;
            }
            free(msg);
        } break;

        case NOTIFY_GETTIME: {
            long long int time = 0;
            _LOG("push_service_get_notification_time() function is being called.");
            ret = push_service_get_notification_time(noti, &time);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_time() function failed!");
                noti_cb_error = true;
            }
        } break;

        case NOTIFY_GETREQID: {
            char *reqid = NULL;
            _LOG("push_service_get_notification_request_id() function is being called.");
            ret = push_service_get_notification_request_id(noti, &reqid);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_request_id() function failed!");
                noti_cb_error = true;
            }
            free(reqid);
        } break;
        case NOTIFY_GETSENDER: {
            char *sender = NULL;
            _LOG("push_service_get_notification_sender() function is being called.");
            ret = push_service_get_notification_sender(noti, &sender);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_sender() function failed!");
                noti_cb_error = true;
            }
            free(sender);
        } break;
        case NOTIFY_GETSESSIONINFO: {
            char *session = NULL;
            _LOG("push_service_get_notification_session_info() function is being called.");
            ret = push_service_get_notification_session_info(noti, &session);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_session_info() function failed!");
                noti_cb_error = true;
            }
            free(session);
        } break;

	case NOTIFY_GETTYPE: {
            int type = 0;
            _LOG("push_service_get_notification_type() function is being called.");
            ret = push_service_get_notification_type(noti, &type);
            if(PUSH_SERVICE_ERROR_NONE != ret) {
                _LOG("push_service_get_notification_type() function failed!");
                noti_cb_error = true;
            }
        } break;

        default: {

        } break;
    }

    g_main_loop_quit(pv->ml);
}

/**
* @function 		_rgdg_cb
* @description	 	Called when the push service state is refreshed. Only used in deregister_negative test case.
* @parameter		push_service_result_e result, const char *msg, void *user_data
* @return 			NA
*/
static void _rgdg_cb(push_service_result_e result, const char *msg, void *user_data)
{

}

/**
* @function 		initialize_service
* @description	 	Called before starting the each test case. It initialize data structure PushT and PushD.
* @parameter		PushT* _pPushT, PushData* _pPushD
* @return 			NA
*/
void initialize_service(PushT* _pPushT, PushData* _pPushD)
{
    _LOG("initialize_service start");
    int ret = 0;
    char *app_id_utc = NULL;
    char *app_secret_utc = NULL;

    /* app_id_utc allocated here, and will be freed end of startservice */
    ret = GetAppId(&app_id_utc);
    if (0 != ret) {
        _LOG("initialize_service : Appid info failed! [%d]", ret);
    }

    /* app_secret_utc allocated here, and will be freed end of startservice */
    ret = GetAppSecret(&app_secret_utc);
    if (0 != ret) {
        _LOG("initialize_service : AppSecret info failed! [%d]", ret);
    }

    /* _LOG("initialize_service : AppID[%s], AppSECRET[%s]", app_id_utc, app_secret_utc); */
    memset(_pPushT, 0, sizeof(PushT));
    _pPushT->app_id = app_id_utc;
    _pPushT->app_secret = app_secret_utc;
    _pPushT->cmd = CMD_END;

    memset(_pPushD, 0, sizeof(PushData));
    _pPushD->pt = _pPushT;
    _pPushD->op = OP_NONE;
    _pPushD->notify_op = NOTIFY_NONE;
    _pPushD->regid = NULL;
}

/**
* @function         finialize_service
* @description      Free memory allocation for PushT and PushD.
* @parameter        PushT* _pPushT, PushData* _pPushD
* @return           NA
*/
void finialize_service(PushT* _pPushT, PushData* _pPushD)
{
    _PUSH_SAFE_FREE(_pPushT->app_id);
    _PUSH_SAFE_FREE(_pPushT->app_secret);
    _PUSH_SAFE_FREE(_pPushD->regid);
}

/**
* @function 		start_service
* @description	 	Called to start the each test case. It initialize the basic test sequence and makes disconnect state for test.
* @parameter		char *appid, PushT* _pPushT, PushData* _pPushD, int _op
* @return 			NA
*/
void start_service(char *appid, PushT* _pPushT, PushData* _pPushD, int _op)
{
    _LOG("start_service start");
    int timeout_id = 0;

    _pPushD->op = _op;

    int r = push_service_connect(appid, _st_cb, _noti_cb, _pPushD, &_pPushD->conn);
    if(PUSH_SERVICE_ERROR_NONE != r) {
        _LOG("push_service_connect() function failed!");
        ret_error = r;
        start_error = true;
        return;
    }

    _pPushD->ml = g_main_loop_new(NULL, FALSE);
    timeout_id = g_timeout_add(50000, timeout_func, _pPushD->ml);
    g_main_loop_run(_pPushD->ml);
    g_source_remove(timeout_id);
    g_main_loop_unref(_pPushD->ml);

    if(timeout_error) {
        _LOG("timeout error");
        start_error = true;
    }

    push_service_disconnect(_pPushD->conn);
    _pPushD->conn = NULL;
}

/**
 * @function		utc_push_service_startup
 * @description		Called before each test to check this model can support push service or not.
 * @parameter		NA
 * @return			NA
 */
void utc_push_service_startup(void)
{

    system_info_get_platform_bool("http://tizen.org/feature/network.push", &push_supported);

}


/**
 * @testcase		utc_sppc_push_service_connect_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_connect()
 * @scenario		Connect push service with invalid parameter and check return value
 */
int utc_sppc_push_service_connect_n(void)
{

    int ret = PUSH_SERVICE_ERROR_NONE;
    void *cb_data = NULL;
    push_service_connection_h conn=NULL;

    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    ret = push_service_connect(NULL, _st_cb, _noti_cb, cb_data, &conn);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_connect(pt.app_id, NULL, _noti_cb, cb_data, &conn);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_connect(pt.app_id, _st_cb, NULL, cb_data, &conn);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_connect(pt.app_id, _st_cb, _noti_cb, cb_data, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_connect_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_connect()
 * @scenario		Connect push service and check state value
 */
int utc_sppc_push_service_connect_p(void)
{
    PushT pt;
    PushData pv;


    initialize_service(&pt, &pv);

    start_error = false;
    ret_error = 0;
    start_service(pt.app_id, &pt, &pv, OP_NONE);
    if(!push_supported){ assert_eq(ret_error, PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert(!start_error);}

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_register_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_register()
 * @scenario		Resister application to push server with invalid parameter and check return value
 */
int utc_sppc_push_service_register_n(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    int ret = push_service_register(NULL, _reg_cb, &pv);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_register((push_service_connection_h) pt.app_id, NULL, &pv);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_register_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_register()
 * @scenario		Register application to push server and check callback action
 */
int utc_sppc_push_service_register_p(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    state_cb_error = false;
    start_error = false;
    ret_error = 0;
    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
       assert(!start_error);
       assert(!state_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_registration_id_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_registration_id()
 * @scenario		Get push registration id in callback action
 */
int utc_sppc_push_service_get_registration_id_p(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    pt.cmd = CMD_GETID;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;
    start_service(pt.app_id, &pt, &pv, OP_REG);

    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_registration_id_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_registration_id()
 * @scenario		Try to get registration id with invalid parameter and check return value
 */
int utc_sppc_push_service_get_registration_id_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_connection_h conn = NULL;
    char *regid = NULL;

    ret = push_service_get_registration_id(conn, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_registration_id(NULL, &regid);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_deregister_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_deregister_p()
 * @scenario		deregister push service and check with callback action
 */
int utc_sppc_push_service_deregister_p(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    pt.cmd = CMD_DRG;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;
    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_deregister_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_deregister()
 * @scenario		Try to deregister with invalid parameter and check return value
 */
int utc_sppc_push_service_deregister_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_connection_h conn = NULL;
    void *data = NULL;

    ret = push_service_deregister(NULL, _rgdg_cb, data);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_deregister(conn, NULL, data);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_deregister(conn, _rgdg_cb, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_unread_notification_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_unread_notification()
 * @scenario		Try to get unread notification with invalid parameter and check return value
 */
int utc_sppc_push_service_get_unread_notification_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti;

    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    ret = push_service_get_unread_notification(NULL, &noti);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_unread_notification(pv.conn, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_unread_notification_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_unread_notification()
 * @scenario		Get unread notification with callback action
 */
int utc_sppc_push_service_get_unread_notification_p(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_UNREAD;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_request_unread_notification_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_request_unread_notification()
 * @scenario		Try to request unread notification with invalid parameter and check return value
 */
int utc_sppc_push_service_request_unread_notification_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;

    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    ret = push_service_request_unread_notification(NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_request_unread_notification_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_request_unread_notification()
 * @scenario		Request unread notification with callback action
 */
int utc_sppc_push_service_request_unread_notification_p(void)
{
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_UNREAD_ASYNC;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_data_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_data()
 * @scenario		Try to get notification data with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_data_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    char *data = NULL;

    ret = push_service_get_notification_data(NULL, &data);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_data(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_data_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_data()
 * @scenario		Send sample push notification message, and get notification data with notification callback
 */
int utc_sppc_push_service_get_notification_data_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer(pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETMSG;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_message_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_message()
 * @scenario		Try to get notification message with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_message_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    char *msg = NULL;

    ret = push_service_get_notification_message(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_message(NULL, &msg);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_message_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_message()
 * @scenario		Send sample push notification message, and get notification message with notification callback
 */
int utc_sppc_push_service_get_notification_message_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer(pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETMSG;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_time_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_time()
 * @scenario		Try to get notification arrival time with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_time_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    long long int rtime;

    ret = push_service_get_notification_time(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_time(NULL, &rtime);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_time_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_time()
 * @scenario		Send sample push notification message, and get notification time with notification callback
 */
int utc_sppc_push_service_get_notification_time_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer(pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETTIME;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_app_control_to_noti_data_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_app_control_to_noti_data()
 * @scenario		Try to app control operation to pass noti data with invalid parameter and check return value
 */
int utc_sppc_push_service_app_control_to_noti_data_n(void)
{
    int ret;
    char *notidata;
    char *operation = "INVALID_OPERATION";
    app_control_h app_control;

    ret = app_control_create(&app_control);
    assert_eq(ret, APP_CONTROL_ERROR_NONE);

    notidata = push_service_app_control_to_noti_data(NULL, operation);

    ret=get_last_result();
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert_eq(notidata, NULL);

        notidata = push_service_app_control_to_noti_data(app_control, NULL);
        assert_eq(notidata, NULL);

        ret = app_control_destroy(app_control);
        assert_eq(ret, APP_CONTROL_ERROR_NONE);
    }
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_app_control_to_notification_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_app_control_to_notification()
 * @scenario		Try to call app control through notification with invalid parameter and check return value
 */
int utc_sppc_push_service_app_control_to_notification_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    char *operation = "INVALID_OPERATION";
    push_service_notification_h noti = NULL;
    app_control_h app_control;

    ret = app_control_create(&app_control);
    assert_eq(ret, APP_CONTROL_ERROR_NONE);

    ret = push_service_app_control_to_notification(NULL, operation, &noti);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_app_control_to_notification(app_control, NULL, &noti);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_app_control_to_notification(app_control, operation, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_request_id_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_request_id()
 * @scenario		Try to get notification request id value with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_request_id_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    char *id;

    ret = push_service_get_notification_request_id(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_request_id(NULL, &id);

    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_request_id_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_request_id()
 * @scenario		Send sample push notification message, and get notification request id with notification callback
 */
int utc_sppc_push_service_get_notification_request_id_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer(pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETREQID;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_sender_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_sender()
 * @scenario		Try to get notification sender value with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_sender_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    char *sender;

    ret = push_service_get_notification_sender(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_sender(NULL, &sender);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_sender_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_sender()
 * @scenario		Send sample push notification message, and get notification sender with notification callback
 */
int utc_sppc_push_service_get_notification_sender_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer((const char*)pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETSENDER;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_session_info_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_session_info()
 * @scenario		Try to get notification session infomation with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_session_info_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    char *session;

    ret = push_service_get_notification_session_info(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}


    ret = push_service_get_notification_session_info(NULL, &session);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_session_info_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_session_info()
 * @scenario		Send sample push notification message, and get notification session infomation with notification callback
 */
int utc_sppc_push_service_get_notification_session_info_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);
    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer(pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETSESSIONINFO;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_type_n
 * @since_tizen		2.3
 * @description		Negative test case of push_service_get_notification_type()
 * @scenario		Try to get notification type with invalid parameter and check return value
 */
int utc_sppc_push_service_get_notification_type_n(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    push_service_notification_h noti = NULL;
    int type;

    ret = push_service_get_notification_type(noti, NULL);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    ret = push_service_get_notification_type(NULL, &type);
    if(!push_supported){assert_eq(ret,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{ assert_eq(ret, PUSH_SERVICE_ERROR_INVALID_PARAMETER);}

    return 0;
}

/**
 * @testcase		utc_sppc_push_service_get_notification_type_p
 * @since_tizen		2.3
 * @description		Positive test case of push_service_get_notification_type()
 * @scenario		Send sample push notification message, and get notification type with notification callback
 */
int utc_sppc_push_service_get_notification_type_p(void)
{
    int ret = PUSH_SERVICE_ERROR_NONE;
    PushT pt;
    PushData pv;

    initialize_service(&pt, &pv);

    pt.cmd = CMD_SENDPUSH;

    state_cb_error = false;
    start_error = false;
    ret_error = 0;

    start_service(pt.app_id, &pt, &pv, OP_REG);
    if(!push_supported){assert_eq(ret_error,PUSH_SERVICE_ERROR_NOT_SUPPORTED);}
    else{
        assert(!start_error);
        assert(!state_cb_error);

        ret = SendPushDataToServer((const char*)pt.app_id , pt.app_secret, pv.regid,
                                  "000101", "App_Data_to_send", 16,
                                  "Alert-Message-to-Quick-Panel", PUSH_ACTION_ALERT,
                                   PUSH_BADGE_OPTION_INCREASE, 1, 1L, 0, 0, pt.app_id, true);
        free(pv.regid);
        pv.regid = NULL;
        assert_neq(ret, PUSH_SERVICE_ERROR_OPERATION_FAILED);
        assert_neq(ret, PUSH_SERVICE_ERROR_OUT_OF_MEMORY);

        pt.cmd = CMD_UNREAD_ASYNC;
        pv.notify_op = NOTIFY_GETTYPE;

        state_cb_error = false;
        start_error = false;
        noti_cb_error = false;

        start_service(pt.app_id, &pt, &pv, OP_REG);

        assert(!start_error);
        assert(!state_cb_error);
        assert(!noti_cb_error);
    }

    finialize_service(&pt, &pv);
    return 0;
}
