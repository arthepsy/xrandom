#include "glibc-random.h"
#define linux_srandom glibc_srandom
#define linux_random glibc_random
#define linux_srand glibc_srand
#define linux_rand glibc_rand
#define linux_initstate glibc_initstate
#define linux_setstate glibc_setstate
