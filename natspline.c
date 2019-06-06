# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <errno.h>
# include <string.h>
# include <math.h>

enum{
	LINESZ = 256,
	INIT = 2,
	GROW = 2,
	NSAMP = 5000
};

typedef struct mat {
	int nrows;
	int ncols;
	int nelem;
	int max;
	double *elem;
} matrix;

char *argv0;
char *filename;
int lineno;

double *xvals;
double *yvals;
int nalloc;
int maxalloc;

void
fatal(int syserror, int line, char *fmt, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	fprintf(stderr, "%s: ", argv0);
	if(line)
		fprintf(stderr, "%s:%d: ", filename, lineno);
	fprintf(stderr, "%s", buf);
	if(syserror)
		fprintf(stderr, ": %s", strerror(errno));
	fprintf(stderr, "\n");

	exit(1);
}

char *
emalloc(unsigned int n)
{
	char *p;

	p = malloc(n);
	if(p == NULL)
		fatal(0, 0, "out of memory");
	return p;
}

char *
erealloc(void *p, unsigned int n)
{
	p = realloc(p, n);
	if(p == NULL)
		fatal(0, 0, "out of memory");
	return p;
}

matrix *
matalloc(int nrows, int ncols)
{
	matrix *m;

	m = (matrix *)emalloc(sizeof(matrix));
	m->nrows = nrows;
	m->ncols = ncols;
	m->max = m->nelem = nrows*ncols;
	m->elem = (double *)emalloc(m->max * sizeof(double));

	return m;
}

void
matfree(matrix *m)
{
	free(m->elem);
	free(m);
}

double *
matelem(matrix *m, int i, int j)
{
	return &m->elem[i*m->ncols + j];
}

void
swap(double *a, double *b)
{
	double tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

matrix *
lupdecomp(matrix *m, matrix *p)
{
	int i, j, k, l, n;
	double r, a;

	n = m->nrows;
	for(i = 0; i < n; i++)
		*matelem(p, i, 0) = i;
	for(k = 0; k < n; k++){
		r = 0.;
		for(i = k; i < n; i++)
			if((a = fabs(*matelem(m, i, k))) > r){
				r = a;
				l = i;
			}
		if(r == 0.)
			return NULL;
		swap(matelem(p, k, 0), matelem(p, l, 0));
		for(i = 0; i < n; i++)
			swap(matelem(m, k, i), matelem(m, l, i));
		for(i = k+1; i < n; i++){
			*matelem(m, i, k) /= *matelem(m, k, k);
			for(j = k+1; j < n; j++)
				*matelem(m, i, j) -= *matelem(m, i, k) * *matelem(m, k, j);
		}
	}
	return m;
}

void
lupsolve(matrix *m, matrix *p, matrix *x, int k)
{
	# define getlow(m, i, j) ( ((i) == (j)) ? 1 : *matelem(m, i, j) )
	# define getupp(m, i, j) *matelem(m, i, j)
	int i, j, n;
	matrix *y;
	double sum;

	y = matalloc(x->nrows, 1);
	n = m->nrows;
	for(i = 0; i < n; i++){
		sum = 0.;
		for(j = 0; j < i; j++)
			sum += getlow(m, i, j) * *matelem(y, j, 0);
		*matelem(y, i, 0) = *matelem(m, *matelem(p, i, 0), n+k) - sum;
	}
	for(i = n-1; i >= 0; i--){
		sum = 0.;
		for(j = i+1; j < n; j++)
			sum += getupp(m, i, j) * *matelem(x, j, k);
		*matelem(x, i, k) = (*matelem(y, i, 0) - sum) / getupp(m, i, i);
	}
	matfree(y);
}

void
add(double x, double y)
{
	if(maxalloc == 0){
		nalloc = 0;
		maxalloc = INIT;
		xvals = (double *)emalloc(maxalloc*sizeof(double));
		yvals = (double *)emalloc(maxalloc*sizeof(double));
	}else if(nalloc >= maxalloc){
		maxalloc *= GROW;
		xvals = (double *)erealloc(xvals, maxalloc*sizeof(double));
		yvals = (double *)erealloc(yvals, maxalloc*sizeof(double));
	}
	if(nalloc > 0 && x <= xvals[nalloc-1])
		fatal(0, 1, "repeated or unsorted x values");
	xvals[nalloc] = x;
	yvals[nalloc++] = y;
}

int
readline(FILE *f, char *line, int n)
{
	int i;
	char c;

	for(i = 0; i < n-1 && (c = getc(f)) > 0 && c != '\n'; i++)
		line[i] = c;
	line[i] = '\0';

	return i;
}

int
iswhite(char c)
{
	return c == ' ' || c == '\t';
}

int
tokens(char *buf, char *elems[], int n)
{
	char *p;
	int i, sep, inword;

	inword = i = 0;
	for(p = buf; *p != '\0'; p++){
		sep = iswhite(*p);
		if(sep && inword){
			*p = '\0';
			inword = 0;
		}else if(!sep && !inword){
			if(i >= n)
				fatal(0, 1, "too many columns");
			elems[i++] = p;
			inword = 1;
		}
	}

	return i;
}

void
load(FILE *f)
{
	char line[LINESZ];
	char *elems[2];
	int n;
	double x, y;

	for(lineno = 1; (n = readline(f, line, LINESZ)) > 0; lineno++){
		n = tokens(line, elems, 2);
		if(n == 0)
			break;
		if(sscanf(elems[0], "%lg", &x) != 1)
			fatal(0, 1, "%s: invalid number", elems[0]);
		if(sscanf(elems[1], "%lg", &y) != 1)
			fatal(0, 1, "%s: invalid number", elems[1]);
		add(x, y);
	}
}

double
nspline(double x, double *b, double *c, double *d)
{
	int low, high, mid;
	double x1;

	low = 0;
	high = nalloc-1;
	while(low <= high){
		mid = (low+high)/2;
		if(x < xvals[mid])
			high = mid-1;
		else if(x > xvals[mid+1])
			low = mid+1;
		else
			break;
	}
	x1 = x - xvals[mid];
	return yvals[mid] + b[mid]*x1 + c[mid]*x1*x1 + d[mid]*x1*x1*x1;
}

int
main(int argc, char *argv[])
{
	FILE *f;
	int i, j;
	double x, dx, *b, *c, *d, *deltax, *deltay;
	matrix *m, *m0, *p, *mc;

	argv0 = *argv;
	maxalloc = 0;
	if(argc == 1){
		filename = "<stdin>";
		load(stdin);
	}else while(*++argv){
		filename = *argv;
		f = fopen(*argv, "r");
		if(f == NULL)
			fatal(1, 0, "%s: unable to read file", *argv);
		load(f);
		fclose(f);
	}

	b = (double *)emalloc((nalloc-1)*sizeof(double));
	c = (double *)emalloc(nalloc*sizeof(double));
	d = (double *)emalloc((nalloc-1)*sizeof(double));
	deltax = (double *)emalloc((nalloc-1)*sizeof(double));
	deltay = (double *)emalloc((nalloc-1)*sizeof(double));
	m = matalloc(nalloc, nalloc+1);
	mc = matalloc(nalloc, 1);;
	for(i = 0; i < nalloc-1; i++){
		deltax[i] = xvals[i+1] - xvals[i];
		deltay[i] = yvals[i+1] - yvals[i];
	}
	for(i = 0; i < nalloc; i++)
		for(j = 0; j < nalloc; j++)
			if(i == j)
				*matelem(m, i, j) = (i == 0 || i == nalloc-1) ? 1 :
					2*(deltax[i]+deltax[i-1]);
			else if(i-1 == j)
				*matelem(m, i, j) = (i == nalloc-1) ? 0 : deltax[j];
			else if(i+1 == j)
				*matelem(m, i, j) = (i == 0) ? 0 : deltax[j-1];
			else
				*matelem(m, i, j) = 0;
	for(i = 0; i < nalloc; i++)
		*matelem(m, i, nalloc) = (i == 0 || i == nalloc-1) ? 0 :
			3*(deltay[i]/deltax[i] - deltay[i-1]/deltax[i-1]);
	p = matalloc(nalloc, 1);
	m0 = lupdecomp(m, p);
	if(m0 == NULL)
		fatal(0, 0, "singular matrix");
	lupsolve(m, p, mc, 0);
	for(i = 0; i < nalloc; i++)
		c[i] = *matelem(mc, i, 0);
	for(i = 0; i < nalloc-1; i++){
		b[i] = deltay[i]/deltax[i] - deltax[i]*(2*c[i] + c[i+1])/3;
		d[i] = (c[i+1]-c[i])/(3*deltax[i]);
	}

	for(i = 0; i < nalloc-1; i++)
		fprintf(stderr, "%g %g %g\n", b[i], c[i], d[i]);

	dx = (xvals[nalloc-1] - xvals[0])/NSAMP;
	x = xvals[0];
	for(i = 0; i <= NSAMP; i++){
		printf("%g %g\n", x, nspline(x, b, c, d));
		x += dx;
	}

	matfree(m);
	matfree(mc);
	matfree(p);
	free(deltay);
	free(deltax);
	free(d);
	free(c);
	free(b);

	return 0;
}
