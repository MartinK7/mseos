
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
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

	for(uint32_t i = 0; i < strlen(argv[1]); ++i)
		if(argv[1][i] == '.')
			argv[1][i] = '_';
	char *name = argv[1] + strlen(argv[1]) - 1;
	while(name[-1] != '/' && name > argv[1])name--;

	printf("volatile uint32_t __attribute__((aligned(4))) bin2c__%s[] = {\n\t", name);

	int cnt = 0;
	uint8_t c0, c1, c2;
	uint32_t c3 = 0;
	while(c3 != EOF) {
		if(cnt > 0)
			printf(", ");
		if(!(cnt % 8) && cnt > 0)
			printf("\n\t");
		cnt++;
		c0 = fgetc(f);
		c1 = fgetc(f);
		c2 = fgetc(f);
		c3 = fgetc(f);
		printf("0x%02"PRIx8"%02"PRIx8"%02"PRIx8"%02"PRIx8, (uint8_t)c3, (uint8_t)c2, (uint8_t)c1, (uint8_t)c0);
	}

	printf("\n};\n");

	fclose(f);
	return 0;
}

