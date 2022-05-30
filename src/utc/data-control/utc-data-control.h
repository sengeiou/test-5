#ifndef __UTC_DATA_CONTROL_H__
#define __UTC_DATA_CONTROL_H__
#include <stdbool.h>
#include <glib.h>

#include <app.h>

int __result;
static char *__next_operation = "";
int __correct_row_cnt;
static const char *__correct_value = "";
bool __is_foreach_check;


#define assert_with_exit(exp) do { \
	if (!(exp)) { \
		fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
		fprintf(stderr, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
		__result = 1; \
		ui_app_exit(); \
		return 1; \
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
		__result = 1; \
		ui_app_exit(); \
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
		__result = 1; \
		ui_app_exit(); \
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
		__result = 1; \
		ui_app_exit(); \
		return 1; \
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
                __result = 1; \
                ui_app_exit(); \
		return; \
        } \
} while (0)

#define normal_exit(result) do { \
	__result = result; \
	ui_app_exit(); \
} while (0)

#endif // __UTC_DATA_CONTROL_H__
