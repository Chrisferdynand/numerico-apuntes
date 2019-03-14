# include <stdio.h>

int
main(void)
{
	int ages[] = { 22, 27, 35, 23, 35 };
	char name[] = "hugo";
	char name1[] = { 'h', 'u', 'g', 'o', '\0' };

	printf("%ld %ld\n", sizeof(int), sizeof(long));
	printf("%ld %ld\n", sizeof(ages), sizeof(ages)/sizeof(ages[0]));
	printf("%d %d\n", ages[0], ages[3]);

	printf("%ld %ld %ld\n", sizeof(char), sizeof(name), sizeof(name1));
	printf("'%s' '%s'\n", name, name1);

	return 0;
}
