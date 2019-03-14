# include <stdio.h>
# include <stdlib.h> // comment to see the compiler error

int
main(int argc, char *argv[])
{
	int i, j, n;

	if(argc < 2){
		fprintf(stderr, "usage: 1.2 n\n");
		return 1;
	}

	n = atoi(argv[1]);
	if(n <= 1){
		fprintf(stderr, "1.2: %s: invalid number\n", argv[1]);
		return 1;
	}

	for(i = 2; i <= n; i++){
		for(j = 2; j < i; j++)
			if(i%j == 0)
				break;
		if(j == i)
			printf("%d\n", i);
	}
	return 0;
}
