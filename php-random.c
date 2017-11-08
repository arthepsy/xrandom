/*
 * php_srand(seed) and php_rand() are used in several ways: 
 *
 * 1) [zts] internal php_rand_r + system's RAND_MAX
 * 2) [zts] internal php_rand_r + constant RAND_MAX=32768
 * 3) [zts] system's rand_r + system's RAND_MAX
 * 4) [zts] system's rand_r + constant RAND_MAX=32768
 * 5) [nts] system's srandom(seed) + random() + constant RAND_MAX=2147483647
 * 6) [nts] system's srand48(seed) + lrand48() + constant RAND_MAX=2147483647
 * 7) [nts] system's srand(seed) + rand() + constant RAND_MAX=2147483647
 * 8) [nts] system's srand(seed) + rand() + constant RAND_MAX=32768
 * 9) [nts] system's srand(seed) + rand() + system's RAND_MAX
 *
 * linux:   srand(seed) + rand() == srandom(seed) + random() 
 * freebsd: srand(seed) + rand() == rand_r(seed)
 * solaris: srand(seed) + rand() == rand_r(seed)
 * srand48(seed) + lrand48() - same on linux, freebsd and solaris
 * 
 */

#include <stdlib.h>
#include "php-random.h"

#define PHP_SEED(bits) \
	({ \
		switch(rand_type) { \
			case PHP_RAND_ZTS_PHP: \
				rmax = PHP_WO_RAND_MAX; \
				break; \
			case PHP_RAND_ZTS_FREEBSD: \
				rmax = FREEBSD_RAND_MAX; \
				useed = seed; \
				break; \
			case PHP_RAND_ZTS_FREEBSD_WO_RAND_R: \
				rmax = FREEBSD_RAND_MAX; \
				break; \
			case PHP_RAND_ZTS_FREEBSD_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				useed = seed; \
				break; \
			case PHP_RAND_ZTS_LINUX: \
				rmax = LINUX_RAND_MAX; \
				useed = seed; \
				break; \
			case PHP_RAND_ZTS_LINUX_WO_RAND_R: \
				rmax = LINUX_RAND_MAX; \
				break; \
			case PHP_RAND_ZTS_LINUX_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				useed = seed; \
				break; \
			case PHP_RAND_ZTS_SOLARIS: \
				rmax = SOLARIS_RAND_MAX; \
				break; \
			case PHP_RAND_ZTS_SOLARIS_WO_RAND_R: \
				rmax = SOLARIS_RAND_MAX; \
				break; \
			case PHP_RAND_ZTS_SOLARIS_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				break; \
			case PHP_RAND_NTS_FREEBSD_RANDOM: \
				rmax = PHP_RAND_MAX; \
				freebsd_srandom(seed); \
				break; \
			case PHP_RAND_NTS_SOLARIS_RANDOM: \
				rmax = PHP_RAND_MAX; \
				solaris_srandom(seed); \
				break; \
			case PHP_RAND_NTS_LINUX_RANDOM: \
				rmax = PHP_RAND_MAX; \
				linux_srandom(seed); \
				break; \
			case PHP_RAND_NTS_SHARED_RAND48: \
				rmax = PHP_RAND_MAX; \
				srand48(seed); \
				break; \
			case PHP_RAND_NTS_FREEBSD_RAND: \
				rmax = FREEBSD_RAND_MAX; \
				freebsd_srand(seed); \
				break; \
			case PHP_RAND_NTS_FREEBSD_RAND_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				freebsd_srand(seed); \
				break; \
			case PHP_RAND_NTS_FREEBSD_RAND_PHP_RAND_MAX: \
				rmax = PHP_RAND_MAX; \
				freebsd_srand(seed); \
				break; \
			case PHP_RAND_NTS_SOLARIS_RAND: \
				rmax = SOLARIS_RAND_MAX; \
				break; \
			case PHP_RAND_NTS_SOLARIS_RAND_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				break; \
			case PHP_RAND_NTS_SOLARIS_RAND_PHP_RAND_MAX: \
				rmax = PHP_RAND_MAX; \
				break; \
			case PHP_RAND_NTS_LINUX_RAND: \
				rmax = LINUX_RAND_MAX; \
				linux_srand(seed); \
				break; \
			case PHP_RAND_NTS_LINUX_RAND_WO_RAND_MAX: \
				rmax = PHP_WO_RAND_MAX; \
				linux_srand(seed); \
				break; \
			case PHP_RAND_NTS_LINUX_RAND_PHP_RAND_MAX: \
				rmax = PHP_RAND_MAX; \
				linux_srand(seed); \
				break; \
		} \
	})

#define PHP_RAND(bits) \
	({ \
		int c = -1; \
		if (nth < 0) { \
			nth = 0; \
		} \
		while (c++ < nth) { \
			PHP_RAND_LOOP_BODY(bits); \
			if (min != 0 || max != 0) { \
					rnd = PHP_RANGED_RAND(rnd, min, max, rmax); \
			} \
		} \
	})

#define FOO2(bitz) solaris_rand_ex##bitz(1, 1);
#define PHP_RAND_LOOP_BREAK { c = nth; }

#define PHP_RAND_LOOP_BODY(bits) \
	({ \
		switch(rand_type) { \
			case PHP_RAND_ZTS_PHP: \
			case PHP_RAND_ZTS_FREEBSD_WO_RAND_R: \
			case PHP_RAND_ZTS_SOLARIS_WO_RAND_R: \
			case PHP_RAND_ZTS_LINUX_WO_RAND_R: \
				rnd = zend_random_ex##bits(seed, rmax, nth); \
				break; \
			case PHP_RAND_ZTS_FREEBSD: \
			case PHP_RAND_ZTS_FREEBSD_WO_RAND_MAX: \
				rnd = freebsd_rand_r(&useed); \
				break; \
			case PHP_RAND_ZTS_SOLARIS: \
			case PHP_RAND_ZTS_SOLARIS_WO_RAND_MAX: \
				rnd = zend_random_ex##bits(seed, rmax, nth); \
				break; \
			case PHP_RAND_ZTS_LINUX: \
			case PHP_RAND_ZTS_LINUX_WO_RAND_MAX: \
				rnd = linux_rand_r(&useed); \
				break; \
			case PHP_RAND_NTS_FREEBSD_RANDOM: \
				rnd = freebsd_random(); \
				break; \
			case PHP_RAND_NTS_SOLARIS_RANDOM: \
				rnd = solaris_random(); \
				break; \
			case PHP_RAND_NTS_LINUX_RANDOM: \
				rnd = linux_random(); \
				break; \
			case PHP_RAND_NTS_SHARED_RAND48: \
				rnd = lrand48(); \
				break; \
			case PHP_RAND_NTS_FREEBSD_RAND: \
			case PHP_RAND_NTS_FREEBSD_RAND_WO_RAND_MAX: \
			case PHP_RAND_NTS_FREEBSD_RAND_PHP_RAND_MAX: \
				rnd = freebsd_rand(); \
				break; \
			case PHP_RAND_NTS_SOLARIS_RAND: \
			case PHP_RAND_NTS_SOLARIS_RAND_WO_RAND_MAX: \
			case PHP_RAND_NTS_SOLARIS_RAND_PHP_RAND_MAX: \
				rnd = solaris_rand_ex##bits(seed, nth); \
				PHP_RAND_LOOP_BREAK; \
				break; \
			case PHP_RAND_NTS_LINUX_RAND: \
			case PHP_RAND_NTS_LINUX_RAND_WO_RAND_MAX: \
			case PHP_RAND_NTS_LINUX_RAND_PHP_RAND_MAX: \
				rnd = linux_rand(); \
				break; \
		} \
	})

#define PHP_RAND_ARCH_FUNCTION(bits) \
	PHP_RAND_ARCH_FUNCTION_HEAD(bits) { \
			iz##bits rnd = 0; \
			iz##bits rmax = 0; \
			uz32 useed = 0; \
			if (min != 0 && min == max) { \
				return min; \
			} \
			PHP_SEED(bits); \
			PHP_RAND(bits); \
			return rnd; \
		}

PHP_RAND_ARCH_FUNCTION(32);
PHP_RAND_ARCH_FUNCTION(64);
