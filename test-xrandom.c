#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "xrandom.h"

#define _gvs(v) \
	({ \
		char buf[22]; \
		char *f = (sizeof(v) == 4) ? "%" PRId32 : "%" PRId64; \
		snprintf(buf, sizeof(buf), f, v); \
		buf; \
	})

void test_freebsd_random(int len, int seed, long * rv)
{
	freebsd_srandom(seed);
	for (int i=0; i < len; i++) {
		long rnd = freebsd_random();
		printf("freebsd_random (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_freebsd_rand(int len, int seed, int * rv)
{
	freebsd_srand(seed);
	for (int i=0; i < len; i++) {
		int rnd = freebsd_rand();
		printf("freebsd_rand (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_freebsd_rand_r(int len, int seed, int * rv)
{
	unsigned int useed = seed;
	for (int i=0; i < len; i++) {
		int rnd = freebsd_rand_r(&useed);
		printf("freebsd_rand_r (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_linux_random(int len, int seed, long * rv)
{
	linux_srandom(seed);
	for (int i=0; i < len; i++) {
		long rnd = linux_random();
		printf("linux_rand[om] (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_linux_rand_r(int len, int seed, int * rv)
{
	unsigned int useed = seed;
	for (int i=0; i < len; i++) {
		int rnd = linux_rand_r(&useed);
		printf("linux_rand_r (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_shared_rand48(int len, int seed, long * rv)
{
	srand48(seed);
	for (int i=0; i < len; i++) {
		long rnd = lrand48();
		printf("shared_rand48 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

int main() {
	int const imax = 2147483647;
	int const custom = 1427476884;
	
	test_freebsd_random(3, 0,       (long[]){ 577655601,  1248161417, 192959563  });
	test_freebsd_random(3, imax,    (long[]){ 1610004448, 1166754120, 128066074  });
	test_freebsd_random(3, imax + 1,(long[]){ 1336741213, 1210407648, 1447044896 });
	test_freebsd_random(3, custom,  (long[]){ 1987417055, 1763888369, 1563796886 });
	
	test_freebsd_rand(3, 0,          (int[]){ 16806,      282475248,  1622650072 });
	test_freebsd_rand(3, imax,       (int[]){ 33613,      564950497,  1097816498 });
	test_freebsd_rand(3, imax + 1,   (int[]){ 50420,      847425746,  572982924  });
	test_freebsd_rand(3, custom,     (int[]){ 2064185557, 168356020,  1323681847 });
	
	test_freebsd_rand_r(3, 0,        (int[]){ 16806,      282475248,  1622650072 });
	test_freebsd_rand_r(3, imax,     (int[]){ 33613,      564950497,  1097816498 });
	test_freebsd_rand_r(3, imax + 1, (int[]){ 50420,      847425746,  572982924  });
	test_freebsd_rand_r(3, custom,   (int[]){ 2064185557, 168356020,  1323681847 });
	
	test_linux_random(3, 0,         (long[]){ 1804289383,  846930886, 1681692777 });
	test_linux_random(3, imax,      (long[]){ 1065668062, 2142264300, 1066566375 });
	test_linux_random(3, imax + 1,  (long[]){ 1336741213, 1210407648, 1447044896 });
	test_linux_random(3, custom,    (long[]){ 1987417055, 1763888369, 1563796886 });
	
	test_linux_rand_r(3, 0,          (int[]){ 1012484,    1716955679, 1792309082 });
	test_linux_rand_r(3, imax,       (int[]){ 1670702726, 99100226,   931463008  });
	test_linux_rand_r(3, imax + 1,   (int[]){ 1012484,    1716955679, 1792309082 });
	test_linux_rand_r(3, custom,     (int[]){ 271302512,  407588803,  1594746754 });
	
	test_shared_rand48(3, 0,        (long[]){ 366850414,  1610402240, 206956554  });
	test_shared_rand48(3, imax,     (long[]){ 1718042167, 1171047564, 1842382256 });
	test_shared_rand48(3, imax + 1, (long[]){ 1440592238, 536660416,  1280698378 });
	test_shared_rand48(3, custom,   (long[]){ 697478000,  310446234,  1544849116 });
}
