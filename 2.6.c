# include <stdio.h>

int
main(int argc, char *argv[])
{
	if(argc == 1)
		printf("argc is one\n");
	else if(argc < 5){
		int i;
		for(i = 0; i < argc; i++)
			printf("argv[%d]: '%s'\n", i, argv[i]);
	}else
		printf("argc is larger than four\n");

	return 0;
}
