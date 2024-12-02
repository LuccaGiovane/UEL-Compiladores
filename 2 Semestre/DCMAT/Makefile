FLEX=flex
BISON=bison
BISON-FLAGS= -d -t
CC=g++
CFLAGS=

SINTATICO = sintatico.tab.c
LEXICO = lex.yy.c

CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(CPP_FILES:.cpp=.o)

PROGRAMA = dcmat

all: projeto

projeto: $(SINTATICO) $(OBJ_FILES)
	$(CC) $(LEXICO) $(SINTATICO) $(OBJ_FILES) $(CFLAGS) -o $(PROGRAMA)

$(SINTATICO): sintatico.y $(LEXICO)
	$(BISON) $(BISON-FLAGS) sintatico.y

$(LEXICO): lexico.l
	$(FLEX) lexico.l

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f lex.yy.c sintatico.tab.c sintatico.tab.h
	rm -f *.o
	rm -f $(PROGRAMA)

