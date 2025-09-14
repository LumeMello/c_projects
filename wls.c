#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    DIR *dir; 
    struct dirent *entry; 
    char *path;
    if(argc == 2){
        path = argv[1];
    }else{
        argv[1] = ".";
        path = argv[1];
    }
    dir = opendir(path);
    
    if (dir == NULL) {
        printf("Erro ao abrir o diretório");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    
    return 0;
}
