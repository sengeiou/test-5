#ifndef __UTC_WATCHFACE_COMPLICATION_H__
#define __UTC_WATCHFACE_COMPLICATION_H__
#include <stdbool.h>
#include <glib.h>
#include <service_app.h>
#include <dlog.h>
#include <app_control.h>

#define SETUP_IS_EDITING_TEST_VAL "SETUP_IS_EDITING_TEST_VAL"
#define SETUP_REPLY_TO_EDITOR_TEST_VAL "SETUP_REPLY_TO_EDITOR_TEST_VAL"
#define SETUP_GET_CONTEXT_TEST_VAL "SETUP_GET_CONTEXT_VAL"

#define EVENT_GET_PROVIDER_ID_TEST_VAL "EVENT_GET_PROVIDER_ID_TEST_VAL"
#define EVENT_GET_COMP_TYPE_TEST_VAL "EVENT_GET_COMP_TYPE_TEST_VAL"
#define EVENT_GET_CONTEXT_TEST_VAL "EVENT_GET_CONTEXT_TEST_VAL"
#define EVENT_GET_EVENT_TYPE_TEST_VAL "EVENT_GET_EVENT_TYPE_TEST_VAL"


int __result;
app_control_h __test_control;
char *__event_cmd;

static gboolean __tc_exit(gpointer data) {
	service_app_exit();
	return G_SOURCE_REMOVE;
}

#define assert_with_exit(exp) do { \
	if (!(exp)) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return 1; \
	} \
} while (0)

#define assert_with_exit_no_returnval(exp) do { \
	if (!(exp)) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return; \
	} \
} while (0)


#define assert_eq_with_exit(var, ref) do { \
	if (var != ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, (int)var, #ref, (int)ref); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return 1; \
	} \
} while (0)

#define assert_eq_with_free(var, ref, var2) do { \
	if (var != ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, (int)var, #ref, (int)ref); \
		free(var2); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return 1; \
	} \
} while (0)


#define assert_neq_with_exit(var, ref) do { \
	if (var == ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return 1; \
	} \
} while (0)

#define assert_neq_with_exit_no_returnval(var, ref) do { \
	if (var == ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return; \
	} \
} while (0)

#define assert_neq_without_exit(var, ref) do { \
	if (var == ref) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d\n", __FILE__, __LINE__); \
		__result = 1; \
		return 1; \
	} \
} while (0)

#define assert_eq_with_exit_no_returnval(var, ref) do { \
	if (var != ref) { \
		fprintf(stderr, \
			"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
			"Values \"%s\" and \"%s\" are not equal:\n" \
			"%s == %d, %s == %d\n", \
			#var, #ref, #var, (int)var, #ref, (int)ref); \
		dlog_print(DLOG_INFO, "NativeTCT", "Assert fail in %s:%d ", __FILE__, __LINE__); \
		__result = 1; \
		g_idle_add(__tc_exit, NULL); \
		return; \
	} \
} while (0)

#define normal_exit(result) do { \
	__result = result; \
	g_idle_add(__tc_exit, NULL); \
	return 0; \
} while (0)

#define normal_exit_no_returnval(result) do { \
	__result = result; \
	g_idle_add(__tc_exit, NULL); \
	return; \
} while (0)

#endif // __UTC_WATCHFACE_COMPLICATION_H__
