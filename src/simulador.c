//---------------------------------------------------------------------
// Arquivo	: simulador.c
// Conteúdo	: Implementação do TP3 de OC1 2024
// Autor	: Carla Beatriz Ferreira, Gabriele Pinheiro Sá e
//			  Manuela Monteiro Fernandes de Oliveira
// Histórico: 2024-08-08 - arquivo criado
//            2024-08-10 - Implementada a leitura dos argumentos corretamente      
// ---------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h> // ou #include <stdint.h> para uint32_t
#include <stdint.h>

typedef struct EspacoNaCache{
    uint32_t EspacoEnderecamento[10]; //32 bits
    //todo
} EspacoNaCache;


int main (int argc, char *argv[]){
    if(argc != 5){ // Verifica se a quantidade de argumentos está correta
        printf("Erro, parametros incorretos!\n"
                "Uso: TamanhoTotalCache TamanhoCadaLinha TamanhoCadaGrupo NomeArquivoComAcessosAMemoria\n");
        return 1;
    }

    FILE *file_input = fopen(argv[4], "r");

    if (file_input == NULL) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    unsigned int TamanhoTotalCache;
    unsigned int TamanhoCadaLinha;
    unsigned int TamanhoCadaGrupo;
    char *endptr;

    // Converte o argumento (argv[i]) para unsigned long, e então para unsigned int, 10 = base decimal
    TamanhoTotalCache = (unsigned int)strtoul(argv[1], &endptr, 10);
    TamanhoCadaLinha = (unsigned int)strtoul(argv[2], &endptr, 10);
    TamanhoCadaGrupo = (unsigned int)strtoul(argv[3], &endptr, 10);

    //todo

    // Fechar o arquivo após o uso
    fclose(file_input);
    return 0;
}
