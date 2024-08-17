#include<stdio.h>
#include<stdlib.h>


/*========== CONSTANTES E PROTOTIPOS ==========*/
#define ESTADO_INICIAL 1
#define TAMANHO_DA_ENTRADA 4098


int pegaProximoEstado(int estadoAtual, char caractere, int arestas[][21]);
int pegaCaractereDaColunaIndex(char caractere);
int verificaEstadoFinal(int estado);

void processamento(char* endereco, int tamanho, int estadoFinal, int* primeiroToken);
/*============================================*/

int main()
{
    int arestas[][21] = {/*input characters
                      +   -   0   1   2   3   4   5   6   7   8   9   a   c   e   h   i   r   s   t   O
        /*state 0*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 1*/  {17,18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0, 11,  0,  2,  0,  0,  4,  0,  0},
        /*state 2*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  0,  7,  0,  0,  0,  0},
        /*state 3*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,  0,  0,  0},
        /*state 4*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  0,  0,  0,  0,  0},
        /*state 5*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0},
        /*state 6*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 7*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0},
        /*state 8*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 9*/  {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,  0,  0},
        /*state 10*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 11*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 12*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 14,  0, 13,  0},
        /*state 13*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0,  0},
        /*state 14*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0},
        /*state 15*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 16*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 17*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 18*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 19*/ {0,  0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19,  0,  0, 20,  0,  0,  0,  0,  0,  0},
        /*state 20*/ {21,21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 21*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*state 22*/ {0,  0, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22,  0,  0,  0,  0,  0,  0,  0,  0,  0},

        /*obs: O stands for other*/
    };

    char linhaEntrada[TAMANHO_DA_ENTRADA];

    int primeiroToken = 1;

    while(fgets(linhaEntrada, TAMANHO_DA_ENTRADA, stdin) != NULL)
    {
        int ultimoEstadoFinal = 0;
        int estadoAtual = ESTADO_INICIAL;

        int receptor = 0;
        int leitor = 0;

        char* enderecoBase = linhaEntrada;

        for(;;)
        {
            char caractereAtual = enderecoBase[leitor];
            leitor++;

            estadoAtual = pegaProximoEstado(estadoAtual, caractereAtual, arestas);

            if(estadoAtual == 0)
            {
                if(*enderecoBase == '\n' || *enderecoBase == '\0')
                {
                    break;
                }

                if(receptor != 0)
                {
                    processamento(enderecoBase, receptor, ultimoEstadoFinal, &primeiroToken);
                    enderecoBase += receptor;
                    receptor = 0;
                }
                else
                {
                    if(*enderecoBase != ' ')
                    {
                        if(primeiroToken != 0)
                        {
                            primeiroToken = 0;
                        }
                        else
                        {
                            printf("\n");
                        }
                        printf("ERRO");
                    }
                    enderecoBase += 1;
                }

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

int pegaProximoEstado(int estadoAtual, char caractere, int arestas[][21])
{
    int index = pegaCaractereDaColunaIndex(caractere);

    return arestas[estadoAtual][index];
}

int pegaCaractereDaColunaIndex(char caractere)
{
    switch (caractere)
    {
    case '+':
        return 0;
        break;

    case '-':
        return 1;
        break;

    case 'a':
        return 12;
        break;

    case 'c':
        return 13;
        break;

    case 'e':
        return 14;
        break;

    case 'h':
        return 15;
        break;
    
    case 'i':
        return 16;
        break;

    case 'r':
        return 17;
        break;

    case 's':
        return 18;
        break;

    case 't':
        return 19;
        break;
    
    default:
        if( caractere >= '0' && caractere <= '9' )
        {
            return ( (caractere - 47) + 1);
        }
        break;
    }
}

int verificaEstadoFinal(int estado)
{
    if( estado == 3 || estado == 6 || estado == 8 || estado == 10 || (estado >=13 && estado <= 19) || estado == 22)
    {
        return 1;
    }

    return 0;
}

void processamento(char* endereco, int tamanho, int estadoFinal, int* primeiroToken)
{
    char temp = endereco[tamanho];
    endereco[tamanho] = '\0';

    if( (*primeiroToken) != 0)
    {
        *primeiroToken = 0;
    }
    else
    {
        printf("\n");
    }

    switch (estadoFinal)
    {
    case 3:
        printf("ELE");
        break;

    case 6:
        printf("ELA");
        break;

    case 8:
        printf("DELE");
        break;

    case 10:
        printf("DELA");
        break;

    case 13:
        printf("GATO");
        break;

    case 15:
        printf("GATOS");
        break;

    case 14:
        printf("CARRO");
        break;

    case 16:
        printf("CARROS");
        break;

    case 17:
        printf("MAIS");
        break;

    case 18:
        printf("MENOS");
        break;

    case 19:
        printf("INTEIRO %s", endereco);
        break;

    case 22:
        printf("REAL %s", endereco);
        break;
    
    default:
        break;
    }

    endereco[tamanho] = temp;

}