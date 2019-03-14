# include <stdio.h>

int
main(void)
{
	long l = 1024L * 1024L * 1024L * 1024L;
	int i = l;
	printf("%d %ld\n", i, l);

	double x = l*3.3;
	printf("%f\n", x);

	char c = '\0';
	int j = c*10;
	printf("%d\n", j);

	return 0;
}
