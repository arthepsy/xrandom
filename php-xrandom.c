#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include "xrandom.h"
#include "php-random.h"

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

#define PHP_XRANDOM_PRINT(bits) \
	({ \
		printf("php.zts.php.%d.php_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_PHP, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.freebsd.%d.sys_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_FREEBSD, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.freebsd.%d.php_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_FREEBSD_WO_RAND_R, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.freebsd.%d.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_FREEBSD_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.solaris.%d.sys_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_SOLARIS, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.solaris.%d.php_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_SOLARIS_WO_RAND_R, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.solaris.%d.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_SOLARIS_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.linux.%d.sys_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_LINUX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.linux.%d.php_rand_r: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_LINUX_WO_RAND_R, seed##bits, nth, min##bits, max##bits))); \
		printf("php.zts.linux.%d.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_ZTS_LINUX_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.freebsd.%d.random: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_FREEBSD_RANDOM, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.solaris.%d.random: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_SOLARIS_RANDOM, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.linux.%d.random: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_LINUX_RANDOM, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.shared.%d.rand48: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_SHARED_RAND48, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.freebsd.%d.rand.sys_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_FREEBSD_RAND, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.freebsd.%d.rand.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_FREEBSD_RAND_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.freebsd.%d.rand.php_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_FREEBSD_RAND_PHP_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.solaris.%d.rand.sys_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_SOLARIS_RAND, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.solaris.%d.rand.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_SOLARIS_RAND_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.solaris.%d.rand.php_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_SOLARIS_RAND_PHP_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.linux.%d.rand.sys_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_LINUX_RAND, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.linux.%d.rand.int_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_LINUX_RAND_WO_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
		printf("php.nts.linux.%d.rand.php_rand_max: %s\n", bits, _gvs(php_rand_##bits(PHP_RAND_NTS_LINUX_RAND_PHP_RAND_MAX, seed##bits, nth, min##bits, max##bits))); \
	});

int main(int argc, char *argv[])
{
	int c, nth;
	iz64 seed64, min64, max64;
	iz32 seed32, min32, max32;
	
	if (argc < 2)
		usage(argv, 0);
	seed64 = get_arg(argv, 1);
	nth = (argc > 2 ? get_arg(argv, 2) : 0);
	min64 = php_long_64(argc > 3 ? get_arg(argv, 3) : 0);
	max64 = php_long_64(argc > 4 ? get_arg(argv, 4) : 0);
	
	if (nth < 0)
		nth = 0;
	if (min64 > max64) {
		iz64 temp = min64;
		min64 = max64;
		max64 = temp;
	}
	
	seed32 = php_long_32(seed64);
	min32 = php_long_32(min64);
	max32 = php_long_32(max64);
	
	PHP_XRANDOM_PRINT(32);
	PHP_XRANDOM_PRINT(64);
}
