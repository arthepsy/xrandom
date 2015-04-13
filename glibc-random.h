void glibc_srandom (unsigned int x);
long int glibc_random (void);
void glibc_srand (unsigned int x);
int glibc_rand (void);
char * glibc_initstate (unsigned int seed, char *arg_state, size_t n);
char * glibc_setstate (char *arg_state);
