# include <stdio.h>

# define nelem(x) sizeof(x)/sizeof(x[0])

void
swap(float **p, float **q)
{
	float *t;

	t = *p;
	*p = *q;
	*q = t;
}

void
wrongswap(float *p, float *q)
{
	float *t;

	t = p;
	p = q;
	q = t;
}

void
redefine(int x, int y)
{
	x = 2;
	y = 3;
}

void
redefine1(int *p, int *q)
{
	*p = 2;
	*q = 3;
}

int
main(int argc, char *argv[])
{
	char *p;
	int *q;
	int nums[] = {9, -8, 22, 53};

	if(argc < 2){
		fprintf(stderr, "usage: %s string\n", *argv);
		return 1;
	}

	for(p = *++argv; *p != '\0'; p++)
		printf("%u %c\n", p, *p);
	printf("\n");

	for(q = nums; q-nums < nelem(nums); q++)
		printf("%u %d\n", q, *q);

	float rands[] = { 4.85645, 52.8545, 11.4671, 24.2683, 0.00102949, 1.23398, 3.24011 };
	float *a = rands + 1;
	float *b = rands + 3;
	int n = 11;
	int m = 22;

	printf("%d %d\n", n, m);
	redefine(n, m);
	printf("%d %d\n", n, m);
	redefine1(&n, &m);
	printf("%d %d\n", n, m);

	printf("%f %f\n", *a, *b);
	wrongswap(a, b);
	printf("%f %f\n", *a, *b);
	swap(&a, &b);
	printf("%f %f\n", *a, *b);

	return 0;
}
