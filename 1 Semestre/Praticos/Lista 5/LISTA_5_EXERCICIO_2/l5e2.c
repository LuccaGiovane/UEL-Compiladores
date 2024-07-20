#include <stdio.h>
#include <string.h>

/*========== CONSTANTES E PROTOTIPOS ==========*/
#define ESTADO_INICIAL 1
#define RESET 0
#define TAMANHO_DE_ENTRADA 1026 // 1024 caracteres em uma linha + um \n e \0

int pegaCaractereDaColunaIndex(char caractere);
int verificaEspaco(char caractere);
int verificaLetra(char caractere);
int verificaNumero(char caractere);
int verificaPonto(char caractere);
int verificaTraco(char caractere);
int verificaQuebraLinha(char caractere);
int pegaProximoEstado(int arestas[][41], int estadoAtual, char caractere);
int verificaEstadoFinal(int);

void processamento(char* endereco, int tamanho, int estadoFinal);
/*============================================*/

int main()
{
    int arestas[][41] = {/*caracteres de entrada
                      B   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   p   q   r   s   t   u   v   w   x   y   z   0   1   2   3   4   5   6   7   8   9   .   -  \n   O*/    
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {12, 4,  4,  4,  4,  4,  4,  4,  4,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  5,  9, 13, 13},
        /*state 2*/  {0,  4,  4,  4,  4,  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 3*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 4*/  {0,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  8,  0,  0,  0},
        /*state 8*/  {0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 11,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},

        /*B = Branco
          0 = outro*/
    };
    
    char entrada[TAMANHO_DE_ENTRADA];

    while(fgets(entrada, TAMANHO_DE_ENTRADA, stdin) != NULL)
    {
        int flag = 1;

        int ultimoEstadoFinal = 0;
        int estadoAtual = ESTADO_INICIAL;

        int receptor = 0;
        int leitor = 0;

        char* enderecoBase = entrada;

        while(flag)
        {
            char caractereAtual = enderecoBase[leitor];
            leitor ++;

            estadoAtual = pegaProximoEstado(arestas, estadoAtual, caractereAtual);

            if(estadoAtual == 0)
            {
                if(*enderecoBase == '\n' ||
                   *enderecoBase == '\0')
                {
                    break;
                }

                processamento(enderecoBase, receptor, ultimoEstadoFinal);
                enderecoBase += receptor;
                receptor = 0;
                leitor = 0;
                ultimoEstadoFinal = 0;
                estadoAtual = ESTADO_INICIAL;
                
            }
            else if(verificaEstadoFinal(estadoAtual))
            {
                ultimoEstadoFinal = estadoAtual;
                receptor = leitor;
            }
        }
    }

    return 0;
}

int pegaCaractereDaColunaIndex(char caractere)
{
    if(verificaEspaco(caractere) == 1)
    {
        return 0;
    }
    else if(verificaLetra(caractere) == 1)
    {
        return (caractere - 96);
    }
    else if(verificaNumero(caractere) == 1)
    {
        return ((caractere - 47) + 26);
    }
    else if(verificaPonto(caractere) == 1)
    {
        return 37;
    }
    else if(verificaTraco(caractere) == 1)
    {
        return 38;
    }
    else if(verificaQuebraLinha(caractere) == 1)
    {
        return 39;
    }

    return 40;
}

int verificaEspaco(char caractere)
{
    if(caractere == ' ')
    {
        return 1;
    }

    return 0;
}

int verificaLetra(char caractere)
{
    if(caractere >= 'a' && caractere <= 'z')
    {
        return 1;
    }
    
    return 0;
}

int verificaNumero(char caractere)
{
    if(caractere >= '0' && caractere <= '9')
    {
        return 1;
    }

    return 0;
}

int verificaPonto(char caractere)
{
    if(caractere == '.')
    {
        return 1;
    }

    return 0;
}

int verificaTraco(char caractere)
{
    if(caractere == '-')
    {
        return 1;
    }

    return 0;
}

int verificaQuebraLinha(char caractere)
{
    if(caractere == '\n')
    {
        return 1;
    }

    return 0;
}

int pegaProximoEstado(int arestas[][41], int estadoAtual, char caractere)
{
    int index = pegaCaractereDaColunaIndex(caractere);

    return arestas[estadoAtual][index];
}

int verificaEstadoFinal(int estado)
{
    if((estado  >= 2 && estado <= 9) || (estado >= 11 && estado <=13))
    {
        return 1;
    }

    return 0;
}

void processamento(char* endereco, int tamanho, int estadoFinal)
{
    if(tamanho == 0)
    {
        return;
    }

    char temporario = endereco[tamanho];
    endereco[tamanho] = '\0';

    switch (estadoFinal)
    {
    case 2:
        printf("%s ID\n", endereco);
        break;
    
    case 4:
        printf("%s ID\n", endereco);
        break;

    case 3:
        printf("IF\n");
        break;
        
    case 12:
        printf("white space\n");
        break;
    
    case 5:
        printf("%s error\n", endereco);
        break;

    case 9:
        printf("%s error\n", endereco);
        break;
        
    case 13:
        printf("%s error\n", endereco);
        break;

    case 6:
        printf("%s REAL\n", endereco);
        break;

    case 8:
        printf("%s REAL\n", endereco);
        break;

    case 7:
        printf("%s NUM\n", endereco);
        break;

    case 11:
        endereco[tamanho - 1] = '\0';
        printf("%s comment\n", endereco);
        endereco[tamanho - 1] = '\n';
        break;
    }

    endereco[tamanho] = temporario;
}