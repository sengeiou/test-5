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
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "tct_common.h"

#ifdef MOBILE
#include "tct-key-manager-core_mobile.h"
#endif

#ifdef WEARABLE
#include "tct-key-manager-core_wearable.h"
#endif

#ifdef TV
#include "tct-key-manager-core_tv.h"
#endif

#ifdef TIZENIOT
#include "tct-key-manager-core_tizeniot.h"
#endif //TIZENIOT

#include <malloc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <glib.h>
#include <stdbool.h>
#include <app.h>
#include <dlog.h>



#define MAX_TESTS 10000

pthread_t worker_thread;

struct fifo_t {
	pthread_mutex_t mutt;
	pthread_cond_t cond;
	char *name[MAX_TESTS];
	int wait;
	int first;
	int last;
	int exit;
} fifo;

void fifo_init() {
	pthread_mutex_init(&fifo.mutt, NULL);
	pthread_cond_init(&fifo.cond, NULL);
	fifo.wait = 0;
	fifo.first = 0;
	fifo.last = 0;
	fifo.exit = 0;
}

void fifo_push(char *ptr) {
	pthread_mutex_lock(&fifo.mutt);
	fifo.name[fifo.last++] = ptr;
	pthread_mutex_unlock(&fifo.mutt);
	pthread_cond_signal(&fifo.cond);
}

char *fifo_pop_block() {
	char *result = NULL;
	while (!fifo.exit) {
		pthread_mutex_lock(&fifo.mutt);
		if (fifo.first < fifo.last) {
			result = fifo.name[fifo.first++];
			pthread_mutex_unlock(&fifo.mutt);
			return result;
		}
	fifo.wait = 1;
	pthread_cond_wait(&fifo.cond, &fifo.mutt);
	fifo.wait = 0;
	pthread_mutex_unlock(&fifo.mutt);
	}
	return NULL;
}

void fifo_exit() {
	fifo.exit = 1;
	if (fifo.wait)
		pthread_cond_signal(&fifo.cond);
	else
		pthread_cancel(worker_thread);
}

void app_control_logic(char *pszGetTCName) {
	int i=0, result=0;

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Executing TC Name = %s", __FUNCTION__, __LINE__, pszGetTCName);
	for ( i = 0; tc_array[i].name; i++ )
	{
		if ( 0 == strncmp(pszGetTCName, tc_array[i].name, strlen(pszGetTCName)) )
		{
			DUMP_UTC_ERRLOG();
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup begin", pszGetTCName);
			if ( tc_array[i].startup )
			{
				tc_array[i].startup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Startup end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body begin", pszGetTCName);
			result = tc_array[i].function();
			dlog_print(DLOG_INFO, "NativeTCT", "%s returns value = %d", pszGetTCName, result);
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Body end", pszGetTCName);

			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup begin", pszGetTCName);
			if ( tc_array[i].cleanup )
			{
				tc_array[i].cleanup();
			}
			dlog_print(DLOG_INFO, "NativeTCT", "%s : Cleanup end", pszGetTCName);

			CLOSE_UTC_ERRLOG();
			PRINT_TC_RESULT("%d",result);
			FREE_MEMORY_TC(pszGetTCName);
			return;
		}
	}

	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Unable to execute %s : Unknown Test Case Name", __FUNCTION__, __LINE__, pszGetTCName);
	PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to execute %s : Unknown Test Case Name\\n", __FILE__, __LINE__, pszGetTCName);
	PRINT_TC_RESULT("%d",1);
	FREE_MEMORY_TC(pszGetTCName);
	return;
}

void *worker(void *param) {
	char *job;

	while((job = fifo_pop_block()))
		app_control_logic(job);

	return NULL;
}


	
	
	


static bool app_create(void *data)
{
	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	char* pszGetTCName = NULL;
	int nRet=0;
	nRet = app_control_get_extra_data(app_control, "testcase_name", &pszGetTCName);
	if(nRet != APP_CONTROL_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] app_control_get_extra_data returns error = %d", __FUNCTION__, __LINE__, nRet);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Unable to fetch test case name: app_control_get_extra_data API call fails\\n", __FILE__, __LINE__);
		PRINT_TC_RESULT("%d",1);
		FREE_MEMORY_TC(pszGetTCName);
		return;
	}

	fifo_push(pszGetTCName);
	return;
}

static void app_terminate(void *data)
{
    fifo_exit();
    pthread_join(worker_thread, NULL);
    dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is now Terminating", __FUNCTION__, __LINE__);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	

	ui_app_lifecycle_callback_s event_callback = {0,};
	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.app_control = app_control;

	fifo_init();
	ret = pthread_create(&worker_thread, NULL, worker, NULL);
	if(ret != 0)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "pthread_create call gets failed. err = %d", ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]pthread_create gets failed. err = %d\\n", __FILE__, __LINE__, ret);
		PRINT_TC_RESULT("%d",1);
		return ret;
	}

	//setting gcda file location for coverage
	setenv("GCOV_PREFIX","/tmp",1);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Coverage *.gcda File location set to /tmp/home/abuild/rpmbuild/BUILD/ ", __FUNCTION__, __LINE__);

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Main Function is Invoked", __FUNCTION__, __LINE__);
	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE)
	{
		dlog_print(DLOG_ERROR, "NativeTCT", "Application ui_app_main call gets failed. err = %d", ret);
		PRINT_UTC_LOG("\\n[%s][Line : %d]Application ui_app_main call gets failed. err = %d\\n", __FILE__, __LINE__, ret);
		PRINT_TC_RESULT("%d",1);
		return ret;
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Application Package is Terminated", __FUNCTION__, __LINE__);
	return ret;
}
