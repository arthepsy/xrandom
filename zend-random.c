int zend_random_ex(unsigned int seed, unsigned long rmax, unsigned int nth)
{
	unsigned long val = (unsigned long) seed;
	int c = -1;
	while (c++ < (int)nth) {
		val = (val * 1103515245 + 12345) % ((unsigned long)rmax + 1);
	}
	return (int) val;
}

int zendom_rand(unsigned int seed, unsigned long rmax)
{
	return zend_random_ex(seed, rmax, 0);
}
