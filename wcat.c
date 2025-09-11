#include <stdio.h>
#include <stdlib.h>

int print_file (const char *name) {
	FILE *file = fopen(name, "r");

	if(file == NULL) {
		fprintf(stdout, "wcat: cannot open file\n");
		return 1;
	}

	else {

		char ch;
		while ((ch = fgetc(file)) != EOF) {	
			fprintf(stdout, "%c", ch);
		}
		fclose(file);
		return 0;
	}
}

int main (int argc, char *argv[]) {

    int status_ = EXIT_SUCCESS; 

    for (int i = 1; i < argc; i++) {
        if (print_file(argv[i]) != 0) {
			status_ = EXIT_FAILURE;
			return status_;
        }
    }
	
	return status_;
}
