CC = g++
CCFLAGS = -c++=11
LDFLAGS = 
TARGET = modificado original
EXE =

all: $(TARGET)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@

help:
	@echo
	@echo
	@echo "Exemplo de Execução"
	@echo "./knights-queens <nro_linhas_colunas_tabuleiro> <nro_cavalos>"

clean:
	rm -f *.o *~ $(TARGET)
