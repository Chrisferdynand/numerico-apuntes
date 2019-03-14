// functions
# include <stdio.h>

void printhello(void);

int
main(void)
{
	int i;

	i = 0;
	while(i < 4){
		printhello();
		printhello();
		printhello();
		printf("\n");
		i = i + 1;
	}

	return 0;
}

void
printhello(void)
{
	printf("hello\n");
}
