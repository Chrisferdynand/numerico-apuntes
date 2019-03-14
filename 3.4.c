# include <stdio.h>
# include <math.h>

# define MAX 50

double
calc(double *v, int n, double (*f)(double))
{
	int i;
	double s;

	s = 0.;
	i = 0;
	while(i < n)
		s += (*f)(v[i++]);
	return s;
}

double
f0(double x)
{
	return x*exp(-x);
}

double
f1(double x)
{
	double y = x*x - cos(x);
	return y*sin(3*x - 1);
}

int
main(void)
{
	int i, n;
	double data[MAX];

	for(n = 0; n < MAX; n++)
		if(scanf("%lf", data+n) != 1)
			break;

	printf("%g %g\n", calc(data, n, f0), calc(data, n, f1));

	return 0;
}
