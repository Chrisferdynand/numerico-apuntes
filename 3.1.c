# include <stdio.h>

int
main(int argc, char *argv[])
{
	int i;

	if(argc != 2){
		fprintf(stderr, "usage: %s string\n", *argv);
		return 1;
	}
	for(i = 0; argv[1][i] != '\0'; i++)
		switch(argv[1][i]){
		case 'a':
		case 'A':
			printf("a\n");
			break;
		case 'e':
		case 'E':
			printf("e\n");
			break;
		case 'i':
		case 'I':
			printf("i\n");
			break;
		case 'o':
		case 'O':
			printf("o\n");
			break;
		case 'u':
		case 'U':
			printf("u\n");
			break;
		default:
			printf("not a vowel\n");
		}

	return 0;
}
