# include <stdio.h>

int
main(void)
{
	int i = 100;
	float x = 2.89;
	double y = 627.5327;
	char c = 'P';
	char name[] = "hugo";
	char surname[] = "rivera";

	printf("%d %f %lf %c '%s' \"%s\"\n", i, x, y, c, name, surname);

	return 0;
}
