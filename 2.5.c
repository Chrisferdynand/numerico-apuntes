# include <stdio.h>

# define nelem(x) (sizeof(x)/sizeof(x[0]))

int
main(int argc, char *argv[])
{
	int i;

	for(i = 0; i < argc; i++)
		printf("argv[%d]: '%s'\n", i, argv[i]);
	printf("\n");

	char *strs[] = { "hola", "a", "todos", "los", "presentes" };

	for(i = 0; i < nelem(strs); i++)
		printf("%s\n", strs[i]);

	return 0;
}
