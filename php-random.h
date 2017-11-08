#include "xrandom.h"

#define PHP_WO_RAND_MAX 1<<15
#define PHP_RAND_MAX 2147483647

typedef __int64_t iz64;
typedef __int32_t iz32;
typedef __uint64_t uz64;
typedef __uint32_t uz32;

#define php_long_64(n) (iz64)((double)n)
#define php_long_32(n) (iz32)(php_long_64(n))

#define PHP_RANGED_RAND(r, min, max, rmax) ((min) + (__typeof__(r)) ((double) ( (double) (max) - (min) + 1.0) * ((r) / ((rmax) + 1.0))))

enum php_rand_type {
	PHP_RAND_ZTS_PHP,                        // internal php_rand_r + constant RAND_MAX=32768
	PHP_RAND_ZTS_FREEBSD,                    // system's rand_r + system's RAND_MAX
	PHP_RAND_ZTS_FREEBSD_WO_RAND_R,          // internal php_rand_r + system's RAND_MAX
	PHP_RAND_ZTS_FREEBSD_WO_RAND_MAX,        // system's rand_r + constant RAND_MAX=32768
	PHP_RAND_ZTS_SOLARIS,                    // system's rand_r + system's RAND_MAX
	PHP_RAND_ZTS_SOLARIS_WO_RAND_R,          // internal php_rand_r + system's RAND_MAX
	PHP_RAND_ZTS_SOLARIS_WO_RAND_MAX,        // system's rand_r + constant RAND_MAX=32768
	PHP_RAND_ZTS_LINUX,                      // system's rand_r + system's RAND_MAX
	PHP_RAND_ZTS_LINUX_WO_RAND_R,            // internal php_rand_r + system's RAND_MAX
	PHP_RAND_ZTS_LINUX_WO_RAND_MAX,          // system's rand_r + constant RAND_MAX=32768
	PHP_RAND_NTS_FREEBSD_RANDOM,             // system's srandom(seed) + random() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_SOLARIS_RANDOM,             // system's srandom(seed) + random() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_LINUX_RANDOM,               // system's srandom(seed) + random() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_SHARED_RAND48,              // system's srand48(seed) + lrand48() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_FREEBSD_RAND,               // system's srand(seed) + rand() + system's RAND_MAX
	PHP_RAND_NTS_FREEBSD_RAND_WO_RAND_MAX,   // system's srand(seed) + rand() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_FREEBSD_RAND_PHP_RAND_MAX,  // system's srand(seed) + rand() + constant RAND_MAX=32768
	PHP_RAND_NTS_SOLARIS_RAND,               // system's srand(seed) + rand() + system's RAND_MAX
	PHP_RAND_NTS_SOLARIS_RAND_WO_RAND_MAX,   // system's srand(seed) + rand() + constant RAND_MAX=32768
	PHP_RAND_NTS_SOLARIS_RAND_PHP_RAND_MAX,  // system's srand(seed) + rand() + constant RAND_MAX=2147483647
	PHP_RAND_NTS_LINUX_RAND,                 // system's srand(seed) + rand() + system's RAND_MAX
	PHP_RAND_NTS_LINUX_RAND_WO_RAND_MAX,     // system's srand(seed) + rand() + constant RAND_MAX=32768
	PHP_RAND_NTS_LINUX_RAND_PHP_RAND_MAX,    // system's srand(seed) + rand() + constant RAND_MAX=2147483647
};

#define PHP_RAND_ARCH_FUNCTION_HEAD(bits) \
	iz##bits php_rand_##bits(enum php_rand_type rand_type, iz##bits seed, int nth, iz##bits min, iz##bits max)

PHP_RAND_ARCH_FUNCTION_HEAD(64);
PHP_RAND_ARCH_FUNCTION_HEAD(32);
