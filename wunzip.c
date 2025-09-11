#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    FILE *fp;
    int count;
    char c;

    for (int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            return 1;
        }

        while (fread(&count, sizeof(int), 1, fp) == 1) {
            fread(&c, sizeof(char), 1, fp);
            for (int j = 0; j < count; j++) {
                printf("%c", c);
            }
        }

        fclose(fp);
    }

    return 0;
}
