# include <stdio.h>

int
main(void)
{
	int num[4] = { 2 };
	char name[4] = { 'h' };
	printf("%d %d %d %d\n", num[0], num[1], num[2], num[3]);
	printf("%c %c %c %c\n", name[0], name[1], name[2], name[3]);
	printf("%s\n", name);

	char *name1 = "hugo";
	printf("%s\n", name1);
	printf("%c %c %c %c\n", name1[0], name1[1], name1[2], name1[3]);

	return 0;
}
