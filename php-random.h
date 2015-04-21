#define PHP_RAND_MAX 2147483647

typedef __int64_t zend_i64;
typedef __int32_t zend_i32;
typedef __uint64_t zend_ui64;
typedef __uint32_t zend_ui32;

#define php_long_64(n) (zend_i64)((double)n)
#define php_long_32(n) (zend_i32)(php_long_64(n))

#define PHP_RANGED_RAND(r, min, max, rmax) ((min) + (__typeof__(r)) ((double) ( (double) (max) - (min) + 1.0) * ((r) / ((rmax) + 1.0))))

enum php_rand_type {
	PHP_RAND_FREEBSD_RAND,   // rand() and rand_r()
	PHP_RAND_FREEBSD_RANDOM, // random()
	PHP_RAND_FREEBSD_ZEND,   // php_rand_r()
	PHP_RAND_LINUX_RAND,     // rand() and random()
	PHP_RAND_LINUX_RAND_R,   // rand_r()
	PHP_RAND_LINUX_ZEND,     // php_rand_r()
	PHP_RAND_SHARED_RAND48   // lrand48()
};

zend_i32 php_rand_32(enum php_rand_type rand_type, zend_i32 seed, int nth, zend_i32 min, zend_i32 max);
zend_i64 php_rand_64(enum php_rand_type rand_type, zend_i64 seed, int nth, zend_i64 min, zend_i64 max);
