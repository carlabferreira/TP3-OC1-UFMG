//---------------------------------------------------------------------
// Arquivo	: simulador.c
// Conteúdo	: Implementação do TP3 de OC1 2024
// Autor	: Carla Beatriz Ferreira, Gabriele Pinheiro Sá e
//			  Manuela Monteiro Fernandes de Oliveira
// Histórico: 2024-08-08 - arquivo criado
//            2024-08-10 - Implementada a leitura dos argumentos corretamente
//            2024-08-11 - Inclusão de funções auxiliares e leitura do arquivo
//            2024-08-12 - Inclusão da biblioteca stdlib.h para a função strtoul
//            2024-08-14 - Esqueleto da função que simula a cache
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // para usar strtoul
#include <sys/types.h> // ou #include <stdint.h> para uint32_t
#include <stdint.h>

typedef struct EspacoNaCache{
    uint32_t EspacoEnderecamento[10]; //32 bits
    //todo
    int Valido; // 1 se a linha estiver ocupada, 0 caso contrário
    unsigned int Tag; // Identificador do bloco
} EspacoNaCache;

// Calcula o número total de linhas na cache
int NumLinhas(int TamanhoTotalCache, int TamanhoCadaLinha) {
    return TamanhoTotalCache / TamanhoCadaLinha;
}

// Calcula o número de conjuntos na cache
int NumConjuntos(int NumLinhas, int TamanhoCadaGrupo) {
    return NumLinhas / TamanhoCadaGrupo;
}

// Obtém o endereço base removendo os bits de offset
unsigned int EnderecoBase(unsigned int Endereco, int BitsOffset) {
    return Endereco >> BitsOffset;
}

// Obtém o índice do conjunto da cache
unsigned int IndiceConjunto(unsigned int Endereco, int BitsOffset, int BitsIndice) {
    return (Endereco >> BitsOffset) & ((1 << BitsIndice) - 1);
}

// Ler endereço de memória do arquivo de entrada
int LerArquivo(FILE *file_input, unsigned int *Endereco) {
    char linha[18];
    if(fgets(linha, sizeof(linha), file_input)) {
        sscanf(linha, "0x%x", Endereco); // Converte endereço de memória hexadecimal para inteiro
        return 1; // Se ler um endereço com sucesso, retorna 1
    }
    return 0; // Se não tiver mais endereços pra ler, retorna 0
}

// Simula o acesso à cache
void SimularCache(FILE *file_input, FILE *file_output, int TamanhoTotalCache, int TamanhoCadaLinha, int TamanhoCadaGrupo) {
    int linhas = NumLinhas(TamanhoTotalCache, TamanhoCadaLinha);
    int conjuntos = NumConjuntos(linhas, TamanhoCadaGrupo);
    
    //todo
}

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
