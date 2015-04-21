/*
 * php_srand(seed) and php_rand() are used in several ways: 
 * 1) system's srand(seed) + rand() +  system's RAND_MAX
 * 2) system's srandom(seed) + random() + PHP_RAND_MAX
 * 3) system's srand48(seed) + lrand48() + PHP_RAND_MAX
 * 4) internal php_rand_r(seed) + system's RAND_MAX
 * 5) system's rand_r(seed) + system's RAND_MAX
 * 
 * PHP_RAND_MAX = 2147483647
 * linux: srand(seed) + rand() == srandom(seed) + random() 
 * freebsd: srand(seed) + rand() == rand_r(seed)
 * srand48(seed) + lrand48() - same on linux and freebsd
 * 
 */

#include <stdlib.h>
#include "xrandom.h"
#include "php-random.h"

zend_i32 php_rand_32(enum php_rand_type rand_type, zend_i32 seed, int nth, zend_i32 min, zend_i32 max)
{
	zend_i32 rnd = 0;
	zend_i32 rmax = 0;
	zend_ui32 useed = 0;
	int c = -1;
	
	if (nth < 0) {
		nth = 0;
	}
	if (min != 0 && min == max) {
		return min;
	}
	
	switch (rand_type) {
		case PHP_RAND_FREEBSD_RAND:
			rmax = FREEBSD_RAND_MAX;
			freebsd_srand(seed);
			break;
		case PHP_RAND_FREEBSD_RANDOM:
			rmax = PHP_RAND_MAX;
			freebsd_srandom(seed);
			break;
		case PHP_RAND_FREEBSD_ZEND:
			rmax = FREEBSD_RAND_MAX;
			break;
		case PHP_RAND_LINUX_RAND:
			rmax = LINUX_RAND_MAX;
			linux_srand(seed);
			break;
		case PHP_RAND_LINUX_RAND_R:
			rmax = LINUX_RAND_MAX;
			useed = seed;
			break;
		case PHP_RAND_LINUX_ZEND:
			rmax = LINUX_RAND_MAX;
			break;
		case PHP_RAND_SHARED_RAND48:
			srand48(seed);
			rmax = PHP_RAND_MAX;
			break;
		default:
			return rnd;
			break;
	}
	while (c++ < nth) {
		switch (rand_type) {
			case PHP_RAND_FREEBSD_RAND:
				rnd = freebsd_rand();
				break;
			case PHP_RAND_FREEBSD_RANDOM:
				rnd = freebsd_random();
				break;
			case PHP_RAND_FREEBSD_ZEND:
			case PHP_RAND_LINUX_ZEND:
				rnd = zend_random_ex32(seed, rmax, nth);
				c = nth;
				break;
			case PHP_RAND_LINUX_RAND:
				rnd = linux_rand();
				break;
			case PHP_RAND_LINUX_RAND_R:
				rnd = linux_rand_r(&useed);
				break;
			case PHP_RAND_SHARED_RAND48:
				rnd = lrand48();
				break;
			default:
				break;
		}
		if (min != 0 || max != 0) {
			rnd = PHP_RANGED_RAND(rnd, min, max, rmax);
		}
	}
	return rnd;
}

zend_i64 php_rand_64(enum php_rand_type rand_type, zend_i64 seed, int nth, zend_i64 min, zend_i64 max)
{
	zend_i64 rnd = 0;
	zend_i64 rmax = 0;
	zend_ui32 useed = 0;
	int c = -1;
	
	if (nth < 0) {
		nth = 0;
	}
	if (min != 0 && min == max) {
		return min;
	}
	
	switch (rand_type) {
		case PHP_RAND_FREEBSD_RAND:
			rmax = FREEBSD_RAND_MAX;
			freebsd_srand(seed);
			break;
		case PHP_RAND_FREEBSD_RANDOM:
			rmax = PHP_RAND_MAX;
			freebsd_srandom(seed);
			break;
		case PHP_RAND_FREEBSD_ZEND:
			rmax = FREEBSD_RAND_MAX;
			break;
		case PHP_RAND_LINUX_RAND:
			rmax = LINUX_RAND_MAX;
			linux_srand(seed);
			break;
		case PHP_RAND_LINUX_RAND_R:
			rmax = LINUX_RAND_MAX;
			useed = seed;
			break;
		case PHP_RAND_LINUX_ZEND:
			rmax = LINUX_RAND_MAX;
			break;
		case PHP_RAND_SHARED_RAND48:
			srand48(seed);
			rmax = PHP_RAND_MAX;
			break;
		default:
			return rnd;
			break;
	}
	while (c++ < nth) {
		switch (rand_type) {
			case PHP_RAND_FREEBSD_RAND:
				rnd = freebsd_rand();
				break;
			case PHP_RAND_FREEBSD_RANDOM:
				rnd = freebsd_random();
				break;
			case PHP_RAND_FREEBSD_ZEND:
			case PHP_RAND_LINUX_ZEND:
				rnd = zend_random_ex64(seed, rmax, nth);
				c = nth;
				break;
			case PHP_RAND_LINUX_RAND:
				rnd = linux_rand();
				break;
			case PHP_RAND_LINUX_RAND_R:
				rnd = linux_rand_r(&useed);
				break;
			case PHP_RAND_SHARED_RAND48:
				rnd = lrand48();
				break;
			default:
				break;
		}
		if (min != 0 || max != 0) {
			rnd = PHP_RANGED_RAND(rnd, min, max, rmax);
		}
	}
	return rnd;
}
