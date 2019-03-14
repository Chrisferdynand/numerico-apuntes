# include <stdio.h>

int
main(void)
{
	unsigned int a = 60;	/* 60 = 0011 1100 */  
	unsigned int b = 13;	/* 13 = 0000 1101 */
	unsigned int c;           

	c = a & b;
	printf("%x\n", c);

	c = a | b;
	printf("%x\n", c);

	c = a ^ b;
	printf("%x\n", c);

	c = ~a;
	printf("%x\n", c);

	c = a << 2;
	printf("%x\n", c);

	c = a >> 2;
	printf("%x\n", c);

	return 0;
}
