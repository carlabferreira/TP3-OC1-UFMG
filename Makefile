#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: Compilar o TP3
# Autor		: Carla Beatriz Ferreira (2022097470), Gabriele Pinheiro Sá (2022091544) e
#			  Manuela Monteiro Fernandes de Oliveira (2022035725)
# Histórico	: 2024-08-08 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/simulador.o
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/simulador

all: $(EXE)

clean:
	rm -f $(EXE) $(OBJS) simulador

$(EXE): $(OBJS) | $(BIN)
	$(CC) $(OBJS) -o $(EXE) $(LIBS) -g

$(BIN):
	mkdir -p $(BIN)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) $< -o $@

$(OBJ):
	mkdir -p $(OBJ)