#ifndef __ASSERT_COMMON_H__
#define __ASSERT_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <service_app.h>

int g_argc;
char **g_argv;
int utc_result;

#define assert_with_exit(exp) do { \
		if (!(exp)) { \
			fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			fprintf(stderr, \
				"Following expression is not true:\n" \
				"%s\n", #exp); \
			utc_result = 1; \
			service_app_exit(); \
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
			utc_result = 1; \
			service_app_exit(); \
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
			utc_result = 1; \
			service_app_exit(); \
			return 1; \
		} \
	} while (0)

#define assert_eq_without_exit(var, ref) do { \
		if (var != ref) { \
			fprintf(stderr, \
				"Assert fail in %s:%d\n", __FILE__, __LINE__); \
			fprintf(stderr, \
				"Values \"%s\" and \"%s\" are not equal:\n" \
				"%s == %d, %s == %d\n", \
				#var, #ref, #var, (int)var, #ref, (int)ref); \
			utc_result = 1; \
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
			utc_result = 1; \
			return 1; \
		} \
	} while (0)

#define normal_exit(result) do { \
		utc_result = result; \
		service_app_exit(); \
	} while (0)


#endif /* __ASSERT_COMMON_H__ */
