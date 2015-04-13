// common
#define GLIBC_RAND_MAX	2147483647
#define __set_errno(ev) ((errno) = (ev))
typedef __int32_t int32_t;

struct random_data
  {
    int32_t *fptr;              /* Front pointer.  */
    int32_t *rptr;              /* Rear pointer.  */
    int32_t *state;             /* Array of state values.  */
    int rand_type;              /* Type of random number generator.  */
    int rand_deg;               /* Degree of random number generator.  */
    int rand_sep;               /* Distance between front and rear.  */
    int32_t *end_ptr;           /* Pointer behind state table.  */
  };
// random_r.h
int glibc_srandom_r (unsigned int seed, struct random_data *buf);
int glibc_random_r (struct random_data *buf, int32_t *result);
int glibc_initstate_r (unsigned int seed, char *arg_state, size_t n, struct random_data *buf);
int glibc_setstate_r (char *arg_state, struct random_data *buf);
// random_r.h
void glibc_srandom (unsigned int x);
long int glibc_random (void);
char * glibc_initstate (unsigned int seed, char *arg_state, size_t n);
char * glibc_setstate (char *arg_state);
// rand.h
int glibc_rand (void);
