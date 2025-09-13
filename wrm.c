#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    
    if (argc != 2) {
        printf("Incorrect quantity of arguments");
        return 1;
    }
    else{
        remove(argv[1]);
    }
    
    return 0;
}
