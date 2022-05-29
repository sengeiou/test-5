#ifndef __ASSERT_COMMON_H__
#define __ASSERT_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <app.h>
#include <dlog.h>
#define MAX_TIMER_CNT 10

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "component-based-application-tests"
#endif

int utc_result;

#define assert_with_exit(exp) do { \
		if (!(exp)) { \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
			utc_result = 1; \
			ui_app_exit(); \
			return 1; \
		} \
	} while (0)

#define assert_eq_with_exit(var, ref) do { \
		if (var != ref) { \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, (int)var, #ref, (int)ref); \
			utc_result = 1; \
			ui_app_exit(); \
			return 1; \
		} \
	} while (0)

#define assert_neq_with_exit(var, ref) do { \
		if (var == ref) { \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, (int)ref); \
			utc_result = 1; \
			ui_app_exit(); \
			return 1; \
		} \
	} while (0)

#define assert_eq_without_exit(var, ref) do { \
		if (var != ref) { \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, var, #ref, ref); \
			utc_result = 1; \
			return 1; \
		} \
	} while (0)

#define assert_neq_without_exit(var, ref) do { \
		if (var == ref) { \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			dlog_print(DLOG_ERROR, LOG_TAG, \
				"Values \"%s\" and \"%s\" are equal:\n" \
				"%s == %s == %d\n", \
				#var, #ref, #var, #ref, ref); \
			utc_result = 1; \
			return 1; \
		} \
	} while (0)

#define normal_exit(result) do { \
		utc_result = result; \
		ui_app_exit(); \
	} while (0)

#define set_result(result) do { \
		dlog_print(DLOG_INFO, LOG_TAG, "result: %d", result); \
		utc_result = result; \
	} while (0)

#endif /* __ASSERT_COMMON_H__ */
