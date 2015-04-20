#define zend_random_ex32(seed, rnd_max, nth) \
	({ \
		__int32_t lseed = seed; \
		int c=-1; while (c++ < nth) lseed = ((lseed * 1103515245 + 12345) % ((__uint32_t)rnd_max + 1)); \
		lseed; \
	})
#define zend_random_ex64(seed, rnd_max, nth) \
	({ \
		__int64_t lseed = seed; \
		int c=-1; while (c++ < nth) lseed = ((lseed * 1103515245 + 12345) % ((__uint64_t)rnd_max + 1)); \
		lseed; \
	})
#define zend_random32(seed, rnd_max) zend_random_ex32(seed, rnd_max, 0)
#define zend_random64(seed, rnd_max) zend_random_ex64(seed, rnd_max, 0)
