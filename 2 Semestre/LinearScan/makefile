# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Lista de arquivos objeto
OBJETOS = linearScan.o alocador_registradores.o utilitarios_string.o

# Alvo padrão: compilar o executável "linearscan"
linearscan: $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o linearscan $(OBJETOS)

# Regra genérica para compilar arquivos .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJETOS) linearscan

.PHONY: clean
