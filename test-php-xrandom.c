#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include "php-random.h"

#define TEST_PHP_NTS_RAND(os, bits, seed, min, max, ...) \
	({ \
		int len = sizeof((iz##bits[]){__VA_ARGS__})/sizeof(iz##bits); \
		iz##bits rv[] = { __VA_ARGS__ }; \
		for (int i=0; i<len; i++) { \
			iz##bits rnd = php_rand_##bits(PHP_RAND_NTS_##os##_RAND, seed, i, min, max); \
			printf("NTS.%s.x%s.RAND (%s:%d) = %s vs %s\n", #os, #bits, _gvs(seed), i, _gvs(rnd), _gvs(rv[i])); \
			assert(rnd == rv[i]); \
		} \
	})

#define TEST_PHP_NTS_RAND48(os, bits, seed, min, max, ...) \
	({ \
		int len = sizeof((iz##bits[]){__VA_ARGS__})/sizeof(iz##bits); \
		iz##bits rv[] = { __VA_ARGS__ }; \
		for (int i=0; i<len; i++) { \
			iz##bits rnd = php_rand_##bits(PHP_RAND_NTS_SHARED_RAND48, seed, i, min, max); \
			printf("NTS.%s.x%s.RAND48 (%s:%d) = %s vs %s\n", #os, #bits, _gvs(seed), i, _gvs(rnd), _gvs(rv[i])); \
			assert(rnd == rv[i]); \
		} \
	})

#define TEST_PHP_NTS_RANDOM(os, bits, seed, min, max, ...) \
	({ \
		int len = sizeof((iz##bits[]){__VA_ARGS__})/sizeof(iz##bits); \
		iz##bits rv[] = { __VA_ARGS__ }; \
		for (int i=0; i<len; i++) { \
			iz##bits rnd = php_rand_##bits(PHP_RAND_NTS_##os##_RANDOM, seed, i, min, max); \
			printf("NTS.%s.x%s.RANDOM (%s:%d) = %s vs %s\n", #os, #bits, _gvs(seed), i, _gvs(rnd), _gvs(rv[i])); \
			assert(rnd == rv[i]); \
		} \
	})

#define TEST_PHP_ZTS_RAND(os, bits, seed, min, max, ...) \
	({ \
		int len = sizeof((iz##bits[]){__VA_ARGS__})/sizeof(iz##bits); \
		iz##bits rv[] = { __VA_ARGS__ }; \
		for (int i=0; i<len; i++) { \
			iz##bits rnd = php_rand_##bits(PHP_RAND_ZTS_##os, seed, i, min, max); \
			printf("ZTS.%s.x%s.SYS_RND (%s:%d) = %s vs %s\n", #os, #bits, _gvs(seed), i, _gvs(rnd), _gvs(rv[i])); \
			assert(rnd == rv[i]); \
		} \
	})


int main() {
	iz64 seed = 1427476884;
	iz64 min = php_long_64(1000000000000000);
	iz64 max = php_long_64(9999999999999999);
	iz32 seed32 = php_long_32(seed);
	iz32 min32 = php_long_32(min);
	iz32 max32 = php_long_32(max);
	
	TEST_PHP_NTS_RAND(FREEBSD, 32, seed, min, max,             616988672, -1263521109,   568559530,   590820905,   142172314);
	TEST_PHP_NTS_RANDOM(FREEBSD, 32, seed, min, max,           616988672,   616988672,   616988672,  -145900244,   616988672);
	TEST_PHP_ZTS_RAND(FREEBSD_WO_RAND_R, 32, seed, min, max,   616988672,   616988672,   285551853,    47657339,  -128942756);
	TEST_PHP_NTS_RAND(SOLARIS, 32, seed, min, max,           -1530445853, -1530445071, -1530470847, -1530474875, -1530462977);
	TEST_PHP_NTS_RANDOM(SOLARIS, 32, seed, min, max,           436685182,   616988672,   616988672,  -214862618, -1311588470);
	TEST_PHP_NTS_RAND(LINUX, 32, seed, min, max,               616988672,   616988672,   616988672,  -145900244,   616988672);
	TEST_PHP_ZTS_RAND(LINUX, 32, seed, min, max,             -1100271686,  -884153021,   616988672,   613600609, -1505833740);
	TEST_PHP_ZTS_RAND(LINUX_WO_RAND_R, 32, seed, min, max,     616988672,   616988672,    50908005,  -213120972,   566701466);
	TEST_PHP_NTS_RAND48(SHARED, 32, seed, min, max,           -424455530, -1038198759,   616988672,  -363448493,  -465427349);
	
	TEST_PHP_NTS_RAND(FREEBSD, 64, seed, min, max,           9650901741488746, 1705571929649982, 6547486540905653, 6606320020376072, 5420609018691451);
	TEST_PHP_NTS_RANDOM(FREEBSD, 64, seed, min, max,         9329168658237905, 8392370757181198, 7553797039203347, 4659276411868632, 8050495193339885);
	TEST_PHP_ZTS_RAND(FREEBSD_WO_RAND_R, 64, seed, min, max, 6656807873544105, 7492002989623699, 6635379730849881, 1356891647313620, 9623795328777094);
	TEST_PHP_NTS_RAND(SOLARIS, 64, seed, min, max,           1000129827298223, 1000131893437355, 1000063769519329, 1000053124502301, 1000084569212049);
	TEST_PHP_NTS_RANDOM(SOLARIS, 64, seed, min, max,         6198962400201709, 6747761257458479, 9600490172393621, 4477019190322608, 1578537095338106);
	TEST_PHP_NTS_RAND(LINUX, 64, seed, min, max,             9329168658237905, 8392370757181198, 7553797039203347, 4659276411868632, 8050495193339885);
	TEST_PHP_ZTS_RAND(LINUX, 64, seed, min, max,             2137015692889690, 2708184940274805, 7683506437577308, 6666523365769536, 1065175952389836);
	TEST_PHP_ZTS_RAND(LINUX_WO_RAND_R, 64, seed, min, max,   9508435028139503, 9643995971418918, 5179411125835031, 4481622099876404, 6542575955856592);
	TEST_PHP_NTS_RAND48(SHARED, 64, seed, min, max,          3923096530139446, 2301065136678517, 7474387852475048, 4084328988101333, 3814814151264727);
}
