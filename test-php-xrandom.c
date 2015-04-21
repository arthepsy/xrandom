#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "php-random.h"

typedef __int64_t z64;
typedef __int32_t z32;
typedef __uint64_t uz64;
typedef __uint32_t uz32;

#define _gvs(v) \
	({ \
		char buf[22]; \
		char *f = (sizeof(v) == 4) ? "%" PRId32 : "%" PRId64; \
		snprintf(buf, sizeof(buf), f, v); \
		buf; \
	})

void test_php_rand_with_freebsd_rand_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_FREEBSD_RAND, seed, i, min, max);
		printf("freebsd_rand_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_freebsd_rand_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_FREEBSD_RAND, seed, i, min, max);
		printf("freebsd_rand_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_freebsd_random_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_FREEBSD_RANDOM, seed, i, min, max);
		printf("freebsd_random_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_freebsd_random_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_FREEBSD_RANDOM, seed, i, min, max);
		printf("freebsd_random_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_freebsd_zts_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_FREEBSD_ZEND, seed, i, min, max);
		printf("freebsd_zts_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_freebsd_zts_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_FREEBSD_ZEND, seed, i, min, max);
		printf("freebsd_zts_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_linux_rand_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_LINUX_RAND, seed, i, min, max);
		printf("linux_rand_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_linux_rand_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_LINUX_RAND, seed, i, min, max);
		printf("linux_rand_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_linux_rand_r_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_LINUX_RAND_R, seed, i, min, max);
		printf("linux_rand_r_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_linux_rand_r_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_LINUX_RAND_R, seed, i, min, max);
		printf("linux_rand_r_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_linux_zts_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_LINUX_ZEND, seed, i, min, max);
		printf("linux_zts_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_linux_zts_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_LINUX_ZEND, seed, i, min, max);
		printf("linux_zts_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

void test_php_rand_with_shared_rand48_x64(int len, z64 seed, z64 min, z64 max, z64 * rv)
{
	for (int i=0; i < len; i++) {
		z64 rnd = php_rand_64(PHP_RAND_SHARED_RAND48, seed, i, min, max);
		printf("shared_rand48_x64 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}
void test_php_rand_with_shared_rand48_x32(int len, z32 seed, z32 min, z32 max, z32 * rv)
{
	for (int i=0; i < len; i++) {
		z32 rnd = php_rand_32(PHP_RAND_SHARED_RAND48, seed, i, min, max);
		printf("shared_rand48_x32 (%s:%d) = %s vs %s\n", _gvs(seed), i, _gvs(rnd), _gvs(rv[i]));
		assert(rnd == rv[i]);
	}
}

int main() {
	z64 seed = 1427476884;
	z64 min = php_long_64(1000000000000000);
	z64 max = php_long_64(9999999999999999);
	z32 seed32 = php_long_32(seed);
	z32 min32 = php_long_32(min);
	z32 max32 = php_long_32(max);
	
	test_php_rand_with_freebsd_rand_x32(5, seed32, min32, max32,   (z32[]){  616988672, -1263521109, 568559530,  590820905,   142172314 });
	test_php_rand_with_freebsd_random_x32(5, seed32, min32, max32, (z32[]){  616988672,  616988672,  616988672, -145900244,   616988672 });
	test_php_rand_with_freebsd_zts_x32(5, seed32, min32, max32,    (z32[]){  616988672,  616988672,  285551853,   47657339,  -128942756 });
	test_php_rand_with_linux_rand_x32(5, seed32, min32, max32,     (z32[]){  616988672,  616988672,  616988672, -145900244,   616988672 });
	test_php_rand_with_linux_rand_r_x32(5, seed32, min32, max32,   (z32[]){ -1100271686, -884153021, 616988672,  613600609, -1505833740 });
	test_php_rand_with_linux_zts_x32(5, seed32, min32, max32,      (z32[]){  616988672,  616988672,  50908005,  -213120972,   566701466 });
	test_php_rand_with_shared_rand48_x32(5, seed32, min32, max32,  (z32[]){ -424455530, -1038198759, 616988672, -363448493,  -465427349 });
	
	test_php_rand_with_freebsd_rand_x64(5, seed, min, max,   (z64[]){ 9650901741488746, 1705571929649982, 6547486540905653, 6606320020376072, 5420609018691451 });
	test_php_rand_with_freebsd_random_x64(5, seed, min, max, (z64[]){ 9329168658237905, 8392370757181198, 7553797039203347, 4659276411868632, 8050495193339885 });
	test_php_rand_with_freebsd_zts_x64(5, seed, min, max,    (z64[]){ 6656807873544105, 7492002989623699, 6635379730849881, 1356891647313620, 9623795328777094 });
	test_php_rand_with_linux_rand_x64(5, seed, min, max,     (z64[]){ 9329168658237905, 8392370757181198, 7553797039203347, 4659276411868632, 8050495193339885 });
	test_php_rand_with_linux_rand_r_x64(5, seed, min, max,   (z64[]){ 2137015692889690, 2708184940274805, 7683506437577308, 6666523365769536, 1065175952389836 });
	test_php_rand_with_linux_zts_x64(5, seed, min, max,      (z64[]){ 9508435028139503, 9643995971418918, 5179411125835031, 4481622099876404, 6542575955856592 });
	test_php_rand_with_shared_rand48_x64(5, seed, min, max,  (z64[]){ 3923096530139446, 2301065136678517, 7474387852475048, 4084328988101333, 3814814151264727 });
}
