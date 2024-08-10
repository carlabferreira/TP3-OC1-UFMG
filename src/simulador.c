#include <stdio.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
    if(argc == 4){ // Verifica se a quantidade de argumentos está correta
        unsigned int TamanhoTotalCache;
        unsigned int TamanhoCadaLinha;
        unsigned int TamanhoCadaGrupo;
        int EspacoEnderecamento = 32; //32 bits
        //todo

    } else printf("Erro, parametros incorretos!\n"
                  "Uso: TamanhoTotalCache TamanhoCadaLinha TamanhoCadaGrupo NomeArquivoComAcessosAMemoria\n");
    return 0;
}

/*
    POSSIVEIS FUNÇÕES A SEREM IMPLEMENTADAS
    1) Exibir a saisa corretamente no arquivo output.txt com fprintf
        prinft("================\n"
                "IDX V ** ADDR **\n");

    2) 
*/
