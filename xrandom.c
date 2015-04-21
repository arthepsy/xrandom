#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include "xrandom.h"

#define _gvs(v) \
	({ \
		char buf[22]; \
		char *f = (sizeof(v) == 4) ? "%" PRId32 : "%" PRId64; \
		snprintf(buf, sizeof(buf), f, v); \
		buf; \
	})

void usage(char *argv[], int pos)
{
	fprintf(stderr, "usage: %s seed [nth]\n", argv[0]);
	if (pos > 0) {
		fprintf(stderr, "\nerror: invalid argument: \"%s\"\n", argv[pos]);
	}
	exit(1);
}

intmax_t get_arg(char *argv[], int pos)
{
	intmax_t val = strtoimax(argv[pos], NULL, 10);
	if (errno == EINVAL || errno == ERANGE)  {
		usage(argv, pos);
	}
	return val;
}

int main(int argc, char *argv[])
{
	int c, nth, irnd;
	long lrnd;
	unsigned int useed;
	intmax_t seed;
	
	if (argc < 2) {
		usage(argv, 0);
	}
	
	seed = get_arg(argv, 1);
	nth = (argc > 2 ? get_arg(argv, 2) : 0);
	if (nth < 0)
		nth = 0;
	
	freebsd_srand(seed);
	for (c = -1; c < nth; c++)
		irnd = freebsd_rand();
	printf("freebsd.rand: %s\n", _gvs(irnd));
	
	freebsd_srandom(seed);
	for (c = -1; c < nth; c++)
		lrnd = freebsd_random();
	printf("freebsd.random: %s\n", _gvs(lrnd));
	
	linux_srandom(seed);
	for (c = -1; c < nth; c++)
		lrnd = linux_random();
	printf("linux.rand: %s\n", _gvs(lrnd));
	
	useed = seed;
	for (c = -1; c < nth; c++)
		irnd = linux_rand_r(&useed);
	printf("linux.rand_r: %s\n", _gvs(irnd));
	
	srand48(seed);
	for (c = -1; c < nth; c++)
		lrnd = lrand48();
	printf("shared.rand48: %s\n", _gvs(lrnd));
}
