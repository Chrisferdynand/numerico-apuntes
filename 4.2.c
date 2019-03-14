# include <stdio.h>

enum week {
	Mon = 10,
	Tue,
	Wed,
	Thur,
	Fri = 19,
	Sat = 16,
	Sun
};

enum {
	Mond = 1 << 14,
	Tues,
	Wedn,
	Thurs,
	Frid = 0x18,
	Satu = 0x11,
	Sund
};

int
main(void)
{
	enum week d;
	int d1;

	d = Wed;
	switch(d){
	case Mon:	printf("Mon\n");	break;
	case Tue:	printf("Tue\n");	break;
	case Wed:	printf("Wed\n");	break;
	case Thur:	printf("Thur\n");	break;
	case Fri:	printf("Fri\n");	break;
	case Sat:	printf("Sat\n");	break;
	case Sun:	printf("Sun\n");	break;
	}

	printf("%d %d %d %d %d %d %d\n", Mond, Tues, Wedn, Thurs, Frid, Satu, Sund);

	return 0;
}
