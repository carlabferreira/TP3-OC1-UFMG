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
//            2024-08-16 - Conclusão da simulaçao da cache
//            2024-08-16 - Verificação com testes extras
// ---------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <string.h> // Para memset

typedef struct {
    int valido;          // 1 se a linha estiver ocupada, 0 caso contrário
    uint32_t tag;        // Identificador do bloco (tag)
} LinhaCache;

// Função que lê um endereço de memória do arquivo de entrada
int LerArquivo(FILE *file_input, unsigned int *Endereco) {
    char linha[18]; // Buffer para armazenar a linha lida do arquivo
    if (fgets(linha, sizeof(linha), file_input)) {
        // Converte a string lida (em hexadecimal) para um inteiro
        sscanf(linha, "0x%x", Endereco); 
        return 1; // Se a leitura foi bem-sucedida, retorna 1
    }
    return 0; // Retorna 0 se não houver mais endereços para ler
}

// Calcula o número total de linhas na cache
int NumLinhas(int TamanhoTotalCache, int TamanhoCadaLinha) {
    return TamanhoTotalCache / TamanhoCadaLinha;
}

// Calcula o número de conjuntos na cache
int NumConjuntos(int NumLinhas, int TamanhoCadaGrupo) {
    return NumLinhas / TamanhoCadaGrupo;
}

// Calcula o número de bits de deslocamento (offset) baseado no tamanho da linha
int CalculaBitsOffset(int TamanhoCadaLinha) {
    int bits = 0;
    while (TamanhoCadaLinha > 1) {
        bits++;
        TamanhoCadaLinha /= 2;
    }
    return bits;
}

// Obtém o endereço base removendo os bits de offset
unsigned int EnderecoBase(unsigned int Endereco, int BitsOffset) {
    return Endereco >> BitsOffset;
}

// Função para imprimir a cache em cada etapa
void ImprimirCache(LinhaCache *cache, int linhas, FILE *file_output) {
    fprintf(file_output, "================\n"
                    "IDX V ** ADDR **\n");
    for (int i = 0; i < linhas; i++) {
        if (cache[i].valido) {
            fprintf(file_output, "%03d %d 0x%08X\n", i, cache[i].valido, cache[i].tag);
        } else {
            fprintf(file_output, "%03d %d\n", i, cache[i].valido);
        }
    }
}

// Simula o acesso à cache
void SimularCache(FILE *file_input, FILE *file_output, int TamanhoTotalCache, int TamanhoCadaLinha, int TamanhoCadaGrupo) {
    int linhas = NumLinhas(TamanhoTotalCache, TamanhoCadaLinha);
    int conjuntos = NumConjuntos(linhas, TamanhoCadaGrupo);
    int bitsOffset = CalculaBitsOffset(TamanhoCadaLinha);

    LinhaCache *cache = (LinhaCache *)malloc(linhas * sizeof(LinhaCache));
    memset(cache, 0, linhas * sizeof(LinhaCache)); // Inicializa cache

    int hits = 0, misses = 0;
    int *fifo_indices = (int *)malloc(conjuntos * sizeof(int)); // Para controle FIFO por conjunto
    memset(fifo_indices, 0, conjuntos * sizeof(int));

    unsigned int endereco;
    while (LerArquivo(file_input, &endereco)) {
        unsigned int endereco_base = EnderecoBase(endereco, bitsOffset);
        unsigned int conjunto_idx = endereco_base % conjuntos;

        int hit = 0;
        int linha_inicio = conjunto_idx * TamanhoCadaGrupo;

        // Verifica se há um HIT
        for (int i = 0; i < TamanhoCadaGrupo; i++) {
            int linha_atual = linha_inicio + i;
            if (cache[linha_atual].valido && cache[linha_atual].tag == endereco_base) {
                hit = 1;
                hits++;
                break;
            }
        }

        // Se for um MISS, insere na cache
        if (!hit) {
            misses++;
            int linha_fifo = linha_inicio + fifo_indices[conjunto_idx]; // Primeira linha disponível ou FIFO
            cache[linha_fifo].valido = 1;
            cache[linha_fifo].tag = endereco_base;
            
            // Atualiza o índice FIFO para o próximo acesso
            fifo_indices[conjunto_idx] = (fifo_indices[conjunto_idx] + 1) % TamanhoCadaGrupo;
        }

        // Imprime a cache a cada acesso
        ImprimirCache(cache, linhas, file_output);
    }

    // Imprime os resultados finais
    fprintf(file_output, "\n"
                        "#hits: %d\n", hits);
    fprintf(file_output, "#miss: %d", misses);

    free(cache);
    free(fifo_indices);
}

int main (int argc, char *argv[]){
    if(argc != 5){ // Verifica se a quantidade de argumentos está correta
        printf("Erro, parametros incorretos!\n"
                "Uso: TamanhoTotalCache TamanhoCadaLinha TamanhoCadaGrupo NomeArquivoComAcessosAMemoria\n");
        return 1;
    }

    FILE *file_input = fopen(argv[4], "r");
    FILE *file_output = fopen("output.txt", "w");

    if (file_input == NULL) { // Verifica se o arquivo foi aberto com sucesso
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    unsigned int TamanhoTotalCache;
    unsigned int TamanhoCadaLinha;
    unsigned int TamanhoCadaGrupo;
    char *endptr;

    // Converte os argumentos para unsigned int
    TamanhoTotalCache = (unsigned int)strtoul(argv[1], &endptr, 10);
    TamanhoCadaLinha = (unsigned int)strtoul(argv[2], &endptr, 10);
    TamanhoCadaGrupo = (unsigned int)strtoul(argv[3], &endptr, 10);

    // Chama a função que simula a cache
    SimularCache(file_input, file_output, TamanhoTotalCache, TamanhoCadaLinha, TamanhoCadaGrupo);

    // Fecha os arquivos após o uso
    fclose(file_input);
    fclose(file_output);

    return 0;
}
