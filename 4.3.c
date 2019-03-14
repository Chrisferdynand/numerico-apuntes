# include <stdio.h>

enum {
	BSIZE = 1 << 12
};

int
readline(char *buf, int n)
{
	char c;
	int i;

	i = 0;
	while((c = getchar()) != EOF && c != '\n' && i < n-1)
		buf[i++] = c;
	buf[i] = '\0';

	return i;
}

int
main(void)
{
	int i, x;
	char buf[BSIZE];

	do{
		printf("enter a natural number: ");
		if(readline(buf, BSIZE) == 0)
			break;
	}while(sscanf(buf, "%d", &x) != 1 || x <= 0);

	for(i = 0; i < 8; i++){
		if(i > 3 && i < 6)
			continue;
		printf("%d\n", i);
	}

	printf("hola\n");
	goto end;
	printf("chau\n");

end:
	return 0;
}
