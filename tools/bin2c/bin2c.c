
#include <stdio.h>
#include <stdlib.h>

#define assert(expr, msg, retcode)\
	if(!(expr)) {\
		fprintf(stderr, "%s:%d assert(%s); %s\n", __FILE__, __LINE__, #expr, msg);\
		exit(retcode);\
	}

int main(int argc, char *argv[])
{
	assert(argc > 1, "Missing argument!", 1);

	FILE *f = fopen(argv[1], "rb");
	assert(f != NULL, "File not exist!", 1);

	int cnt = 1;
	int c = fgetc(f);
	while(c != EOF) {
		printf("%02X ", (unsigned char)c);
		if(!(cnt++ % 10))putchar('\n');
		c = fgetc(f);
	}

	fclose(f);
	return 0;
}

