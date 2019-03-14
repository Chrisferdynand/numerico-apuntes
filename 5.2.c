# include <stdio.h>

enum{
	NSIZE = 232
};

int
main(int argc, char *argv[])
{
	int nums[NSIZE];
	int i;
	FILE *f;

	if(argc != 2){
		fprintf(stderr, "usage: 5.2 file\n");
		return 1;
	}
	f = fopen(*++argv, "w");
	if(f == NULL){
		fprintf(stderr, "5.2: %s: unable to open file\n", *argv);
		return 1;
	}
	for(i = 0; i < NSIZE; i++)
		nums[i] = 3*i + 4;
	if(fwrite(nums, sizeof(int), NSIZE, f) != NSIZE){
		fclose(f);
		fprintf(stderr, "5.2: %s: error while writing\n", *argv);
		return 1;
	}
	if(fseek(f, 55, SEEK_SET)){
		fclose(f);
		fprintf(stderr, "5.2: %s: error while seeking file\n", *argv);
		return 1;
	}
	if(fwrite(nums+NSIZE-1, sizeof(int), 1, f) != 1){
		fclose(f);
		fprintf(stderr, "5.2: %s: error while writing\n", *argv);
		return 1;
	}
	fclose(f);

	return 0;
}
