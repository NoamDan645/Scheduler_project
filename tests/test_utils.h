#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>

static int g_failures = 0;

#define CHECK(cond)                                                    \
	do                                                                 \
	{                                                                  \
		if (!(cond))                                                   \
		{                                                              \
			fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__,     \
					__LINE__, #cond);                                  \
			++g_failures;                                              \
		}                                                              \
	} while (0)

#define TEST_RESULT(name)                                              \
	(g_failures ? (printf("[FAIL] %s (%d)\n", name, g_failures), 1)    \
				: (printf("[ OK ] %s\n", name), 0))

#endif /* TEST_UTILS_H */
