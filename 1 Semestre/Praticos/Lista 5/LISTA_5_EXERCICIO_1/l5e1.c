#include <stdio.h>
#include <stdlib.h>

/*========== CONSTANTES E PROTOTIPOS ==========*/
#define ESTADO_INICIAL 1
#define RESET 0
#define TAMANHO_DE_ENTRADA 1026 // 1024 caracteres em uma linha + um \n e \0

int pegaProximoEstado(int estadoAtual, int input);
int estadoUm(int input);
int estadoDois(int input);
int estadoCinco(int input);
int estadoSeis(int input);
int estadoSeteOuOito(int input);
int resetaInicio();
int resetaReceptorLeitor();
void processamento(int tamanho, char* endereco);
int verificaEstadoFinal(int estado);

/*============================================*/

int main()
{
    char entrada[TAMANHO_DE_ENTRADA];

    while(fgets(entrada, TAMANHO_DE_ENTRADA, stdin) != NULL)
    {
        int flag = 1;

        int ultimoEstadoFinal = 0;
        int estadoAtual = ESTADO_INICIAL;
        
        int receptor = 0;
        int leitor = 0;

        char* enderecoBase = entrada;

        while (flag)
        {
            // lê o próximo caractere
            char caractereAtual = enderecoBase[leitor];
            leitor++;

            // pega o próximo estado
            estadoAtual = pegaProximoEstado(estadoAtual, caractereAtual);

            if(estadoAtual == -1)
            {
                /* Estado inválido do autômato */
                printf("ERROR\n");

                enderecoBase += 1;

                receptor = resetaReceptorLeitor();
                leitor = resetaReceptorLeitor();
                estadoAtual = resetaInicio();

                continue;
            }
            else if(estadoAtual == 0)
            {
                if(*enderecoBase == '\n' || *enderecoBase == '\0')
                {
                    break;
                }

                processamento(receptor, enderecoBase);

                enderecoBase += receptor;

                receptor = resetaReceptorLeitor();
                leitor = resetaReceptorLeitor();
                estadoAtual = resetaInicio();
            }
            else if(verificaEstadoFinal(estadoAtual))
            {
                receptor = leitor;
            }
        }
    }

    return 0;
}

int pegaProximoEstado(int estadoAtual, int input)
{
    int retorno = 0;

    if(estadoAtual == 0 ||
       estadoAtual == 3 ||
       estadoAtual == 4 ||
       input == '\n' ||
       input == '\0')
    {
        return 0;
    }
    else if(estadoAtual == 1)
    {
        retorno = estadoUm(input);
        return retorno;
    }
    else if(estadoAtual == 2)
    {
        retorno = estadoDois(input);
        return retorno;
    }
    else if(estadoAtual == 5)
    {
        retorno = estadoCinco(input);
        return retorno;
    }
    else if(estadoAtual == 6)
    {
        retorno = estadoSeis(input);
        return retorno;
    }
    else if(estadoAtual == 7 || estadoAtual == 8)
    {
        retorno = estadoSeteOuOito(input);
        return retorno;
    }
    
    return -1; // Estado inválido
}

int estadoUm(int input)
{
    /* retorna os valores possíveis para o estado inicial */

    // verifica se é letra ou número
    if(input >= 'a' && input <= 'z')
    {
        return 2;
    }

    if(input >= '0' && input <= '9')
    {
        return 5;
    }

    // se não for números ou letras entra aqui para verificar se é '+' ou '-' caso não retorna -1
    switch (input)
    {
    case '+':
        return 3;
    
    case '-':
        return 4;
    
    default:
        return -1;
    }
}

int estadoDois(int input)
{
    // retorna 2 se for letras ou números
    if((input >= '0' && input <= '9') || 
       (input >= 'a' && input <= 'z'))
    {
        return 2;
    }

    // qualquer outra coisa vai para 0
    return 0;
}

int estadoCinco(int input)
{
    // se for '+' ou '-' vai pra 0
    if(input == '+' || input == '-')
    {
        return 0;
    }

    // se for um número vai pra 5
    if (input >= '0' && input <= '9')
    {
        return 5;
    }

    // se for 'e' vai pra 6 se for qualquer outra letra ou coisa obscura vai pra 0
    if(input == 'e')
    {
        return 6;
    }

    return 0;
}

int estadoSeis(int input)
{
    // se for letra vai pro erro -> 0
    if(input >= 'a' && input <= 'z')
    {
        return 0;
    }

    // se for '+' ou '-' vai pra 7
    if(input == '+' || input == '-')
    {
        return 7;
    }

    // se for um número vai pro 8
    if(input >= '0' && input <= '9')
    {
        return 8;
    }

    // qualquer coisa além disso vai pra 0
    return 0;
}

int estadoSeteOuOito(int input)
{
    // se input for '+' ou '-' vai pra erro
    if(input == '+' || input ==  '-')
    {
        return 0;
    }

    // se o input for um número vai pra 8
    if(input >= '0' && input <= '9') 
    {
        return 8;
    } 
    
    // se o input for uma letra vai pra 0 (Erro)
    if(input >= 'a' && input <= 'z')
    {
        return 0;
    }

    // qualquer outra coisa vai pra 0
    return 0;
}

int verificaEstadoFinal(int estado)
{
    if((estado  >= 2 && estado <= 5) || estado == 8)
    {
        return 1;
    }

    return 0;
}

int resetaInicio()
{
    return ESTADO_INICIAL;
}

int resetaReceptorLeitor()
{
    return RESET;
}

void processamento(int tamanho, char* endereco)
{
    // se está vazio, só vai embora
    if(tamanho == 0)
    {
        return;
    }

    char temporario = endereco[tamanho];

    endereco[tamanho] = '\0';
    printf("%s\n", endereco);

    endereco[tamanho] = temporario;
}
