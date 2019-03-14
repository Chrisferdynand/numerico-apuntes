# include <stdio.h>

enum {
	BSIZE = 8192
};

int
main(int argc, char *argv[])
{
	int i;
	int cat(FILE *);
	FILE *f;

	if(argc == 1){
		if(cat(stdin) == 0){
			fprintf(stderr, "cat: <stdin>: I/O error\n");
			return 1;
		}
	}else
		for(i = 1; i < argc; i++){
			f = fopen(argv[i], "r");
			if(f == NULL){
				fprintf(stderr, "cat: %s: unable to open file\n", argv[i]);
				continue;
			}
			if(cat(f) == 0)
				fprintf(stderr, "cat: %s: I/O error\n", argv[i]);
			fclose(f);
		}

	return 0;
}

int
cat(FILE *f)
{
	char buf[BSIZE];
	int n;

	while((n = fread(buf, 1, BSIZE, f)) > 0)
		if(fwrite(buf, 1, n, stdout) != n)
			return 0;
	return 1;
}
