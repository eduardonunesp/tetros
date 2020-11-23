/* base code from - hexembed.c - copyright Lewis Van Winkle */
/* zlib license */
#include <stdio.h>
#include <stdlib.h>

int32_t main(int32_t argc, char* argv[]) {
	if (argc < 3) { printf("Usage:\n\thexembed <filename> <varname>\n"); return 1; }

	const char* fname = argv[1];
	const char* vname = argv[2];
	FILE* fp = fopen(fname, "rb");
	if (!fp) {
		fprintf(stderr, "Error opening file: %s.\n", fname);
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	const int32_t fsize = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	unsigned char* b = malloc(fsize);

	fread(b, fsize, 1, fp);
	fclose(fp);

	// printf("#ifndef __%s_c__\n", vname);
	// printf("#define __%s_c__\n", vname);
	printf("/* Embedded file: %s */\n", fname);
	printf("unsigned char %s[] = {\n", vname);

	int32_t i;
	for (i = 0; i < fsize; ++i) {
		printf("0x%02x%s",
			b[i],
			i == fsize - 1 ? " " : ((i + 1) % 12 == 0 ? ",\n" : ", "));
	}
	printf("\n};\n");
	// printf("#endif\n");

	free(b);
	return 0;
}
