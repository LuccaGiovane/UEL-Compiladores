##########################################
# Makefile para gerar o executável
# "regalloc" a partir dos arquivos .cpp
##########################################

# Nome do executável
EXEC = regalloc

# Compilador e flags (ajuste se desejar)
CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -std=c++11

# Fontes e cabeçalhos atualizados para português
SOURCES = Grafo.cpp NoGrafo.cpp regalloc.cpp Utilitarios_string.cpp
HEADERS = Grafo.h NoGrafo.h Utilitarios_string.h

# Alvo que gera o executável
all: $(EXEC)

# Converte lista de fontes .cpp em objetos .o
OBJECTS = $(SOURCES:.cpp=.o)

# Regras de link: gera o binário final
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regras genéricas de compilação: .cpp -> .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos artefatos de compilação
clean:
	rm -f *.o $(EXEC)

# Recompila tudo do zero
rebuild: clean all
