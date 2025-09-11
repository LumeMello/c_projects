#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_in_file(FILE *fp, const char *term) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strlen(term) == 0 || strstr(line, term) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    const char *searchterm = argv[1];
    if (argc == 2) {
        search_in_file(stdin, searchterm);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            search_in_file(fp, searchterm);
            fclose(fp);
        }
    }

    return 0;
}
