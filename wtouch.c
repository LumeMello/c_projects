#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    
    if (argc != 2) {
        printf("Incorrect quantity of arguments");
        return 1;
    }
    else{
        file = fopen(argv[1],"w");
        
        fclose(file);
    }
    
    return 0;
}
