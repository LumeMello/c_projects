#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Wrong arguments quantity");
        return 1;
    }else{
        //muda a pasta do processo filho, é impossivel de mudar diretamente a do processo pai que é o que você está
        int status = chdir(argv[1]);
        
        //Para mudar o processo pai usamos um printf simples, utilize para rodar o comando após sua compilação o comando source <(./wcd ..) no terminal
        printf("cd %s\n", argv[1]);
        
        if(status != 0){
            printf("An error block the operation");
        }
    }
    
    return 0;
}
