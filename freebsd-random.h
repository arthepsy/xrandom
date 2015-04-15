#define	FREEBSD_RAND_MAX	0x7ffffffd
void freebsd_srandom (unsigned long x);
long freebsd_random (void);
void freebsd_srand (unsigned int seed);
int freebsd_rand (void);
int freebsd_rand_r(unsigned int *ctx);
char * freebsd_initstate(unsigned long seed, char *arg_state, long n);
char * freebsd_setstate(char *arg_state);
