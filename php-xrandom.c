#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include "xrandom.h"
#include "php-random.h"

#define _gvs(v) \
	({ \
		char buf[22]; \
		char *f = (sizeof(v) == 4) ? "%" PRId32 : "%" PRId64; \
		snprintf(buf, sizeof(buf), f, v); \
		buf; \
	})

void usage(char *argv[], int pos)
{
	fprintf(stderr, "usage: %s seed [nth] [min max]\n", argv[0]);
	if (pos > 0) {
		fprintf(stderr, "\nerror: invalid argument: \"%s\"\n", argv[pos]);
	}
	exit(1);
}

double get_arg(char *argv[], int pos)
{
	intmax_t val = strtod(argv[pos], NULL);
	if (errno == EINVAL || errno == ERANGE)  {
		usage(argv, pos);
	}
	return val;
}

int main(int argc, char *argv[])
{
	int c, nth;
	zend_i64 seed64, min64, max64;
	zend_i32 seed32, min32, max32;
	
	if (argc < 2)
		usage(argv, 0);
	seed64 = get_arg(argv, 1);
	nth = (argc > 2 ? get_arg(argv, 2) : 0);
	min64 = php_long_64(argc > 3 ? get_arg(argv, 3) : 0);
	max64 = php_long_64(argc > 4 ? get_arg(argv, 4) : 0);
	
	if (nth < 0)
		nth = 0;
	if (min64 > max64) {
		zend_i64 temp = min64;
		min64 = max64;
		max64 = temp;
	}
	
	seed32 = php_long_32(seed64);
	min32 = php_long_32(min64);
	max32 = php_long_32(max64);
	
	printf("freebsd.rand.32: %s\n",   _gvs(php_rand_32(PHP_RAND_FREEBSD_RAND,   seed32, nth, min32, max32)));
	printf("freebsd.random.32: %s\n", _gvs(php_rand_32(PHP_RAND_FREEBSD_RANDOM, seed32, nth, min32, max32)));
	printf("freebsd.zend.32: %s\n",   _gvs(php_rand_32(PHP_RAND_FREEBSD_ZEND,   seed32, nth, min32, max32)));
	printf("linux.rand.32: %s\n",     _gvs(php_rand_32(PHP_RAND_LINUX_RAND,     seed32, nth, min32, max32)));
	printf("linux.rand_r.32: %s\n",   _gvs(php_rand_32(PHP_RAND_LINUX_RAND_R,   seed32, nth, min32, max32)));
	printf("linux.zend.32: %s\n",     _gvs(php_rand_32(PHP_RAND_LINUX_ZEND,     seed32, nth, min32, max32)));
	printf("shared.rand48.32: %s\n",  _gvs(php_rand_32(PHP_RAND_SHARED_RAND48,  seed32, nth, min32, max32)));
	
	printf("freebsd.rand.64: %s\n",   _gvs(php_rand_64(PHP_RAND_FREEBSD_RAND,   seed64, nth, min64, max64)));
	printf("freebsd.random.64: %s\n", _gvs(php_rand_64(PHP_RAND_FREEBSD_RANDOM, seed64, nth, min64, max64)));
	printf("freebsd.zend.64: %s\n",   _gvs(php_rand_64(PHP_RAND_FREEBSD_ZEND,   seed64, nth, min64, max64)));
	printf("linux.rand.64: %s\n",     _gvs(php_rand_64(PHP_RAND_LINUX_RAND,     seed64, nth, min64, max64)));
	printf("linux.rand_r.64: %s\n",   _gvs(php_rand_64(PHP_RAND_LINUX_RAND_R,   seed64, nth, min64, max64)));
	printf("linux.zend.64: %s\n",     _gvs(php_rand_64(PHP_RAND_LINUX_ZEND,     seed64, nth, min64, max64)));
	printf("shared.rand48.64: %s\n",  _gvs(php_rand_64(PHP_RAND_SHARED_RAND48,  seed64, nth, min64, max64)));
}
