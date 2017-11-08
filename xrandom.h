#include "freebsd-random.h"
#include "linux-random.h"
#include "solaris-random.h"
#include "zend-random.h"

#define _gvs(v) \
	({ \
		char buf[22]; \
		char *f = (sizeof(v) == 4) ? "%" PRId32 : "%" PRId64; \
		snprintf(buf, sizeof(buf), f, v); \
		buf; \
	})
