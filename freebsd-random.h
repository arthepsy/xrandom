void freebsd_srandom (unsigned long x);
long freebsd_random (void);
void freebsd_srand (unsigned int seed);
int freebsd_rand (void);
char * freebsd_initstate(unsigned long seed, char *arg_state, long n);
char * freebsd_setstate(char *arg_state);
