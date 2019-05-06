# include <stdio.h>
# include <stdlib.h>

enum{
	NNUM = 10
};

int
gcd(int a, int b)
{
	int t;

	while(b != 0){
		t = b;
		b = a%b;
		a = t;
	}
	return a;
}

int
main(int argc, char *argv[])
{
	FILE *f;
	unsigned char buf[NNUM];
	int i, j;

	if(argc != 2){
		fprintf(stderr, "usage: gcdmat file\n");
		return 1;
	}
	f = fopen(*++argv, "r");
	if(f == NULL){
		fprintf(stderr, "gdcmat: %s: unable to open file\n", *argv);
		return 1;
	}
	i = fread(buf, 1, NNUM, f);
	fclose(f);
	if(i != NNUM){
		fprintf(stderr, "gdcmat: %s: unable to fill buffer\n", *argv);
		return 1;
	}
	for(i = 0; i < NNUM; i++)
		printf("%03d\n", buf[i]);
	printf("\n");
	for(i = 0; i < NNUM; i++){
		for(j = 0; j < NNUM; j++)
			printf(j == 0 ? "%03d" : " %03d", gcd(buf[i], buf[j]));
		printf("\n");
	}

	return 0;
}
