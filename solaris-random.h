#define SOLARIS_RAND_MAX 2147483647L
char * solaris_initstate(unsigned int seed, char *arg_state, size_t size);
char * solaris_setstate(const char *arg_state);
long solaris_random(void);
void solaris_srandom(unsigned int x);

#define solaris_rand_ex32(seed, nth) \
	({ \
		__int32_t lseed = seed; \
		int c=-1; while (c++ < nth) lseed = lseed * 1103515245 + 12345; \
		(lseed >> 16) & 0x7fff; \
	})
#define solaris_rand_ex64(seed, nth) \
	({ \
		__int64_t lseed = seed; \
		int c=-1; while (c++ < nth) lseed = lseed * 1103515245 + 12345; \
		(lseed >> 16) & 0x7fff; \
	})
