#include <assert.h>
#include <dlfcn.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cuda.h>

#define xstr(s) str(s)
#define str(s) #s

#define unwrap(expr)                                                           \
	do {                                                                   \
		int _unwrap;                                                   \
                                                                               \
		if (_unwrap = expr) {                                          \
			(void)fprintf(stderr,                                  \
				      "lithos: " __FILE__ ":%d: %s: `" #expr   \
				      "` failed: %s\n",                        \
				      __LINE__, __func__, strerror(_unwrap));  \
			abort();                                               \
		}                                                              \
	} while (0)

static void *handle;

static void init(void) {
	handle = dlopen("/lib/libcuda.so.1", RTLD_LAZY);
	assert(handle);
}

void *interpose(char *symbol) {
	static pthread_once_t once = PTHREAD_ONCE_INIT;

	unwrap(pthread_once(&once, init));
	return dlsym(handle, symbol);
}

CUresult cuInit(unsigned flags) {
	(void)fprintf(stderr, "lithos: cuInit(%u)\n", flags);
	return ((CUresult (*)(unsigned))interpose(xstr(cuInit)))(flags);
}
