# include <stdio.h>
# include <stdlib.h>

# define BSIZE 8

int
main(void)
{
	char buff[BSIZE];
	int i, c;

	for(i = 0; i < BSIZE-1; i++){
		c = getchar();
		if(c == EOF)
			break;
		buff[i] = c;
	}
	buff[i] = '\0';
	printf("%s\n", buff);

	return 0;
}
