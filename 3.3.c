# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXSIZE 128

struct personalA {
	char *name;
	unsigned age;
	unsigned height;
	unsigned weight;
};

struct personalB {
	char name[MAXSIZE];
	unsigned age;
	unsigned height;
	unsigned weight;
};

struct personalA *
createpersonal(char *name, unsigned age, unsigned height, unsigned weight)
{
	struct personalA *p;

	p = malloc(sizeof(struct personalA));
	if(p == NULL)
		return NULL;
	p->name = name;
	p->age = age;
	p->height = height;
	p->weight= weight;
	return p;
}

void
destroypersonal(struct personalA *p)
{
	free(p);
}

int
main(void)
{
	struct personalA *p;

	p = createpersonal("Hugo Marcelo", 36, 184, 70);
	if(p == NULL){
		fprintf(stderr, "3.3: out of memory\n");
		return 1;
	}
	printf("'%s' %u %u %u\n", p->name, p->age, p->height, p->weight);
	destroypersonal(p);
	printf("'%s' %u %u %u\n", p->name, p->age, p->height, p->weight);

	struct personalB pers;

	strcpy(pers.name, "Fulano");
	pers.age = 56;
	pers.height = 177;
	pers.weight = 78;
	printf("'%s' %u %u %u\n", pers.name, pers.age, pers.height, pers.weight);

	return 0;
}
