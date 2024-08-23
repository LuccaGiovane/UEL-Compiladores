#include <iostream>
#include <vector>

#include "matriz.cpp"
#include "macrosErrosLexicoSintatico.cpp"

using namespace std;

/******************* PROTOTIPOS *******************/
int pegaProximoToken();

void count_comment_length();
void advance();
void eat(int token);
void programa();
void procedimento_funcao();
void declara_procedimento();
void declara_funcao();
void parametros();
void declara_parametros();
void bloco_variaveis();
void declaracoes();
void declaracoes_aux();
void declara_tipo();
void declara_variaveis();
void declara_identificador();
void declara_identificador_aux();
void vetor_matriz();
void dimensao();
void dimensao_aux();
void tipo_basico();
void bloco_comandos();
void lista_comandos();
void lista_comandos_aux();
void comandos();
void comandos_aux_id();
void comandos_aux_se();
void comandos_aux_para();
void expressao();
void expressao_simples();
void termo();
void fator();
void fator_id_aux();
void variavel();
void variavel_aux();
void expr_iter();
void expr_iter_comma_expr_loop();
void expr_iter_id_aux();
void expressao_();
void expressao_simples_();
void termo_();

class Automaton
{
    private:
        int initial_state, current_index, token;     
        int line_no, col_no;
        string input, token_content;


        /**
         * Obtém o próximo token da entrada com base no autômato finito determinístico.
         * 
         * A função percorre a entrada a partir do índice atual, atualizando o estado do autômato
         * e identificando o próximo token. Se encontrar um estado final, atualiza a posição do token
         * e retorna o token correspondente. Se encontrar um erro, define o conteúdo do token e retorna
         * o token de erro.
         * 
         * @return O token identificado ou um token de erro.
         */
        int pegaProximoToken() 
        {
            // Estado final mais recente encontrado e índice correspondente
            int last_final_state = 0, last_final_index = this->current_index;
            // Estado atual do autômato
            int current_state = this->initial_state;

            // Percorre a entrada a partir do índice atual
            for (int i = this->current_index; i < this->input.length(); i++) 
            {
                // Obtém o próximo estado com base no autômato e o caractere da entrada
                int next_state = automaton[current_state][input[i]];

                // Verifica se o próximo estado é um estado final
                if (final_states[next_state] == true) 
                {
                    // Atualiza o estado final mais recente e o índice correspondente
                    last_final_state = next_state;
                    last_final_index = i;
                }

                // Verifica se o próximo estado é um estado de erro
                if (tokens[next_state] == ERRO) 
                {
                    // Define o conteúdo do token como o trecho da entrada até o índice atual
                    this->token_content = this->input.substr(this->current_index, i - this->current_index);
                    // Atualiza o índice atual para o próximo caractere
                    this->current_index = last_final_index + 1;
                    // Retorna o token correspondente ao estado final mais recente
                    return tokens[last_final_state];
                }

                // Atualiza o estado atual para o próximo estado
                current_state = next_state;
            }

            // Define o conteúdo do token como o trecho restante da entrada
            this->token_content = this->input.substr(this->current_index, this->input.length() - this->current_index);
            // Atualiza o índice atual para o próximo caractere
            this->current_index = last_final_index + 1;
            // Retorna o token correspondente ao estado final mais recente
            return tokens[last_final_state];
        }


        /**
         * Conta o comprimento de um comentário e ajusta a posição da linha e coluna.
         * 
         * A função percorre o conteúdo do token de comentário e atualiza as informações de linha e coluna
         * conforme necessário. Se encontrar um caractere de nova linha, incrementa o número da linha e reseta
         * a coluna. Caso contrário, incrementa a coluna para refletir a largura do comentário.
        */
        void count_comment_length() 
        {
            // Percorre cada caractere do conteúdo do token de comentário
            for (int i = 0; i < this->token_content.length(); i++) 
            {
                // Verifica se o caractere atual é um caractere de nova linha
                if (this->token_content[i] == '\n') 
                {
                    // Incrementa o número da linha para refletir o novo número da linha
                    this->line_no++;
                    // Reseta a coluna para 1, pois estamos no início de uma nova linha
                    this->col_no = 1;
                } 
                else 
                {
                    // Incrementa a coluna para refletir o comprimento do comentário
                    this->col_no++;
                }
            }
        }


        /**
         * Avança para o próximo token na sequência de tokens.
         * 
         * A função atualiza o token atual para o próximo token obtido pela função `pegaProximoToken()`.
         * Além disso, ajusta as informações de linha e coluna com base no tipo de token encontrado.
         * 
         * - Atualiza a posição da linha e coluna para refletir a posição atual no texto.
         * - Processa comentários e espaços em branco, ajustando a posição da coluna conforme necessário.
         * - Se encontrar um token do tipo `OTHER`, gera um erro léxico.
         */
        void advance() 
        {
            // Atualiza o token atual para o próximo token
            this->token = pegaProximoToken();

            // Verifica o tipo de token e ajusta a posição da linha e coluna
            if (this->token == EOL) 
            { // Fim de linha
                // Incrementa o número da linha e reseta a coluna
                this->line_no++;
                this->col_no = 1;
            } 
            else if (this->token == COMMENT) 
            { // Comentário
                // Conta o comprimento do comentário para ajustar a posição da coluna
                count_comment_length();
            } 
            else 
            {
                // Atualiza a coluna com base no comprimento do conteúdo do token
                this->col_no += this->token_content.length();
            }

            // Continua processando até encontrar um token válido
            while (this->token == COMMENT    || 
                   this->token == WHITESPACE || 
                   this->token == EOL        || 
                   this->token == OTHER) 
                {
                if (this->token == OTHER)
                {
                    // Se encontrar um token do tipo `OTHER`, gera um erro léxico
                    ERRO_LEXICO;
                }

                // Obtém o próximo token
                this->token = pegaProximoToken();

                // Ajusta a posição da linha e coluna com base no novo token
                if (this->token == EOL) 
                {
                    // Incrementa o número da linha e reseta a coluna
                    this->line_no++;
                    this->col_no = 1;
                } 
                else if (this->token == COMMENT) 
                {
                    // Conta o comprimento do comentário
                    count_comment_length();
                } 
                else 
                {
                    // Atualiza a coluna com base no comprimento do conteúdo do token
                    this->col_no += this->token_content.length();
                }
            }
        }


        /**
         * Função para consumir o token atual se ele corresponder ao token esperado.
         * 
         * A função verifica se o token atual corresponde ao token esperado passado como argumento.
         * Se corresponder, a função avança para o próximo token. Caso contrário, gera um erro sintático.
         * 
         * @param token O token esperado a ser verificado e consumido.
        */
        void eat(int token)
        {
            // Verifica se o token atual corresponde ao token esperado
            if (this->token == token) 
            {
                // Avança para o próximo token
                advance();
            } 
            else 
            {
                // Se o token não corresponder, gera um erro sintático
                ERRO_SINTATICO;
            }
        }


        /**
         * Função para processar a estrutura do programa.
         * 
         * Esta função valida e processa a estrutura principal do programa conforme a gramática definida.
         * Ela espera os seguintes componentes na ordem:
         * - Palavra-chave `ALGORITMO`.
         * - Um identificador (ID) que representa o nome do programa.
         * - Um ponto e vírgula (`SEMICOLON`).
         * - O bloco de variáveis (`bloco_variaveis`).
         * - Declarações de procedimentos e funções (`procedimento_funcao`).
         * - Bloco de comandos (`bloco_comandos`).
         * - Um ponto final (`DOT`).
         * 
         * Se todos os componentes estiverem corretos, a função imprime uma mensagem indicando que o programa está correto.
         */
        void programa() 
        {
            // Verifica e consome a palavra-chave ALGORITMO
            eat(ALGORITMO);

            // Verifica e consome o identificador (ID) do programa
            eat(ID);

            // Verifica e consome o ponto e vírgula ';' após o identificador
            eat(SEMICOLON);

            // Analisa o bloco de variáveis do programa
            bloco_variaveis();

            // Analisa os procedimentos e funções do programa
            procedimento_funcao();

            // Analisa o bloco de comandos do programa
            bloco_comandos();

            // Verifica e consome o ponto final '.' que encerra o programa
            eat(DOT);

            // Imprime uma mensagem indicando que o programa foi analisado corretamente
            cout << "PROGRAMA CORRETO.";
        }


         /**
         * Função para processar declarações de procedimentos e funções.
         * Esta função lida com a declaração de procedimentos e funções em uma linguagem de programação.
         * Dependendo do token encontrado, a função pode processar diferentes partes das declarações.
         * Dependendo do token encontrado, a função pode:
         * - Processar uma declaração de procedimento e então chamar `procedimento_funcao` recursivamente para processar mais declarações.
         * - Processar uma declaração de função e então chamar `procedimento_funcao` recursivamente para processar mais declarações.
         * - Encerrar o processamento se o token for `INICIO`.
         * - Sinalizar um erro sintático se o token não corresponder a um dos casos esperados.
         */
        void procedimento_funcao() 
        {
            switch(this->token) 
            {
                // Se o token for `PROCEDIMENTO`, processa a declaração de um procedimento e chama recursivamente `procedimento_funcao` para mais declarações.
                case(PROCEDIMENTO):
                    declara_procedimento(); // Processa a declaração de um procedimento.
                    procedimento_funcao();  // Chama recursivamente para processar mais declarações.
                    break;

                // Se o token for `FUNCAO`, processa a declaração de uma função e chama recursivamente `procedimento_funcao` para mais declarações.
                case(FUNCAO):
                    declara_funcao();       // Processa a declaração de uma função.
                    procedimento_funcao();  // Chama recursivamente para processar mais declarações.
                    break;

                // Se o token for `INICIO`, encerra o processamento.
                case(INICIO):
                    break;

                default:
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função para processar a declaração de um procedimento.
         * Esta função lida com a declaração de um procedimento, incluindo o nome do procedimento, parâmetros,
           e blocos de variáveis e comandos. Dependendo do token encontrado, a função pode processar diferentes partes
           da declaração do procedimento.
         * Dependendo do token encontrado, a função pode:
         * - Processar a declaração de um procedimento se o token for `PROCEDIMENTO`, consumindo o token `PROCEDIMENTO`, o identificador do procedimento, os parâmetros, e então processar a declaração de parâmetros, bloco de variáveis e bloco de comandos.
         * - Encerrar o processamento de um procedimento se o token não corresponder a um dos casos esperados, sinalizando um erro sintático.
         */
        void declara_procedimento() 
        {
            switch(this->token) 
            {
                // Se o token for a palavra-chave de declaração de procedimento, processa a declaração completa.
                case(PROCEDIMENTO):
                    eat(PROCEDIMENTO);  // Consome o token `PROCEDIMENTO`.
                    eat(ID);            // Consome o identificador do procedimento.
                    parametros();       // Processa os parâmetros do procedimento.
                    eat(SEMICOLON);     // Consome o token `SEMICOLON` (ponto e vírgula).
                    declara_parametros(); // Processa a declaração de parâmetros (se houver).
                    bloco_variaveis();  // Processa o bloco de variáveis do procedimento.
                    bloco_comandos();   // Processa o bloco de comandos do procedimento.
                    eat(SEMICOLON);     // Consome o token `SEMICOLON` (ponto e vírgula) de fechamento do procedimento.
                    break;
                
                default:
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar a declaração de uma função.
         * Esta função lida com a declaração de uma função, incluindo o nome da função, parâmetros, tipo de retorno,
           e blocos de variáveis e comandos. Dependendo do token encontrado, a função pode processar diferentes partes
           da declaração da função.
         * Dependendo do token encontrado, a função pode:
         * - Processar a declaração de uma função se o token for `FUNCAO`, consumindo o token `FUNCAO`, o identificador da função, os parâmetros, o tipo de retorno, e então processar a declaração de parâmetros, bloco de variáveis e bloco de comandos.
         * - Encerrar o processamento de uma função se o token não corresponder a um dos casos esperados, sinalizando um erro sintático.
         */
        void declara_funcao() 
        {
            switch(this->token) 
            {
                // Se o token for a palavra-chave de declaração de função, processa a declaração completa.
                case(FUNCAO):
                    eat(FUNCAO);        // Consome o token `FUNCAO`.
                    eat(ID);            // Consome o identificador da função.
                    parametros();       // Processa os parâmetros da função.
                    eat(COLON);         // Consome o token `COLON` (dois pontos).
                    tipo_basico();      // Processa o tipo de retorno da função.
                    eat(SEMICOLON);     // Consome o token `SEMICOLON` (ponto e vírgula).
                    declara_parametros(); // Processa a declaração de parâmetros (se houver).
                    bloco_variaveis();  // Processa o bloco de variáveis da função.
                    bloco_comandos();   // Processa o bloco de comandos da função.
                    eat(SEMICOLON);     // Consome o token `SEMICOLON` (ponto e vírgula) de fechamento da função.
                    break;
                
                default:
                    ERRO_SINTATICO; 
            }
        }


        /**
        * Função para processar a declaração de parâmetros.
        * Esta função lida com a declaração de parâmetros em um bloco de código. Dependendo do token encontrado,
          a função pode processar identificadores de parâmetros ou finalizar a declaração de parâmetros.
        * Dependendo do token encontrado, a função pode:
        * - Processar a declaração de identificadores se o token for um delimitador de lista de parâmetros (`L_C_BRACKET`), seguido pela declaração de identificadores e o fechamento do delimitador (`R_C_BRACKET`).
        * - Encerrar o processamento de parâmetros se o token for um ponto e vírgula (`SEMICOLON`) ou dois pontos (`COLON`).
        * Caso o token não corresponda a um dos casos esperados, um erro sintático é sinalizado.
        */
        void parametros() 
        {
            switch(this->token) 
            {
                // Se o token for um delimitador de lista de parâmetros, processa a lista de identificadores.
                case(L_C_BRACKET):
                    eat(L_C_BRACKET); // Consome o delimitador de abertura.
                    declara_identificador(); // Processa a declaração de identificadores.
                    eat(R_C_BRACKET); // Consome o delimitador de fechamento.
                    break;
                
                // Se o token for um ponto e vírgula ou dois pontos, não realiza nenhuma ação adicional.
                case(SEMICOLON):
                case(COLON):
                    break;

                default:
                    ERRO_SINTATICO; 
            }
        }

        /**
         * Função para processar a declaração de parâmetros.
         * Esta função lida com a declaração de parâmetros em um bloco de código. Dependendo do token encontrado,
           a função pode processar declarações de variáveis ou encerrar o processamento de parâmetros.
         * Dependendo do token encontrado, a função pode:
         * - Processar declarações de variáveis se o token for um identificador (`ID`), um tipo (`TIPO`), ou um dos tipos primitivos (`INTEIRO`, `REAL`, `CARACTERE`, `LOGICO`).
         * - Encerrar o bloco de parâmetros se o token for um dos tokens de fim de bloco ou seção (PROCEDIMENTO, FUNCAO, VARIAVEIS, INICIO).
         * Caso o token não corresponda a um dos casos esperados, um erro sintático é sinalizado.
        */
        void declara_parametros() 
        {
            switch(this->token) 
            {
                // Se o token é um identificador ou tipo, processa a declaração de variáveis.
                case(ID): 
                case(TIPO): 
                case(INTEIRO): 
                case(REAL): 
                case(CARACTERE): 
                case(LOGICO): 
                    declaracoes(); 
                    break;

                // Tokens que sinalizam o fim da seção de parâmetros ou início de outras seções.
                case(PROCEDIMENTO): 
                case(FUNCAO): 
                case(VARIAVEIS): 
                case(INICIO): 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar o bloco de variáveis.
         * Esta função lida com a seção de variáveis de um bloco de código. Dependendo do token encontrado, a função
           pode processar a declaração de variáveis ou terminar o bloco de variáveis.
         * Dependendo do token encontrado, a função pode:
         * - Processar a declaração de variáveis se o token for `VARIAVEIS`.
         * - Tratar outros tokens que sinalizam o fim de declarações de variáveis ou outras seções (PROCEDIMENTO, FUNCAO, INICIO, _EOF).
         * Caso o token não corresponda a um dos casos esperados, um erro sintático é sinalizado.
         */
        void bloco_variaveis() 
        {
            switch(this->token) 
            {
                // Se o token é VARIAVEIS, processa a declaração de variáveis.
                case(VARIAVEIS): 
                    eat(VARIAVEIS); 
                    declaracoes(); 
                    break;

                // Tokens para fim de bloco de variáveis ou início de outras seções.
                case(PROCEDIMENTO): 
                case(FUNCAO): 
                case(INICIO): 
                case(_EOF): 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar declarações.
         * Esta função lida com diferentes tipos de declarações e processa a declaração de variáveis ou tipos
           dependendo do token encontrado. Após processar uma declaração, ela continua analisando declarações adicionais.
         * Dependendo do token encontrado, a função pode:
         * - Declarar variáveis de um tipo específico (ID, INTEIRO, REAL, CARACTERE, LOGICO).
         * - Declarar um tipo personalizado (TIPO).
         * A função chama `declaracoes_aux` para continuar a análise após uma declaração.
         */
        void declaracoes() 
        {
            switch(this->token) 
            {
                // Se o token é um identificador ou um tipo específico de variável, processa a declaração de variáveis
                // e continua com a análise de declarações adicionais.
                case(ID): 
                case(INTEIRO): 
                case(REAL): 
                case(CARACTERE): 
                case(LOGICO): 
                    declara_variaveis(); 
                    declaracoes_aux(); 
                    break;
                
                // Se o token é TIPO, processa a declaração de tipo e continua com a análise de declarações adicionais.
                case(TIPO): 
                    declara_tipo(); 
                    declaracoes_aux(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar declarações auxiliares.
         * Esta função lida com diferentes tipos de declarações e chamadas subsequentes. 
         * Dependendo do token encontrado, ela pode chamar funções para declarar variáveis, 
           ou lidar com tipos. A função continua processando até que um token que não exija 
           uma nova chamada para declaração seja encontrado.
         * O formato esperado é uma sequência de declarações de variáveis ou tipos,
           seguida por tokens que não exigem mais declarações, como procedimentos ou funções.
         */
        void declaracoes_aux() 
        {
            switch(this->token) 
            {
                // Se o token é um identificador ou um tipo específico de variável, processa a declaração de variáveis
                // e continua com a análise de declarações adicionais.
                case(ID): 
                case(INTEIRO): 
                case(REAL): 
                case(CARACTERE): 
                case(LOGICO): 
                    declara_variaveis(); 
                    declaracoes_aux(); 
                    break;
                    
                // Se o token é TIPO, processa a declaração de tipo e continua com a análise de declarações adicionais.
                case(TIPO): 
                    declara_tipo(); 
                    declaracoes_aux(); 
                    break;
                    
                // Se o token é PROCEDIMENTO, FUNCAO, VARIAVEIS, INICIO ou _EOF, a função apenas faz uma pausa,
                // pois esses tokens não requerem processamento adicional nesta função.
                case(PROCEDIMENTO): 
                case(FUNCAO): 
                case(VARIAVEIS): 
                case(INICIO): 
                case(_EOF): 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
        * Função para processar a declaração de tipo de variável. 
        * Esta função lida com a declaração de um tipo de variável, que inclui a definição do tipo, o nome do tipo,
        e suas características como vetor ou matriz, e suas dimensões. Após a definição do tipo, um ponto e vírgula
        (`SEMICOLON`) é consumido.
        * O formato esperado é:
        * - TIPO ID = VETOR|MATRIZ [ DIMENSAO ] tipo_basico;
        * Se o token não corresponder a uma declaração de tipo válida, um erro sintático é gerado.
        */
        void declara_tipo() 
        {
            switch(this->token) 
            {
                // Se o token é um tipo de declaração, o processamento inclui:
                // - Consumo do token TIPO
                // - Consumo do identificador ID
                // - Consumo do sinal de igual (=)
                // - Processamento de vetor ou matriz
                // - Processamento da dimensão (se houver)
                // - Consumo do tipo básico
                // - Consumo do ponto e vírgula (;)
                case(TIPO): 
                    eat(TIPO); 
                    eat(ID); 
                    eat(EQUAL); 
                    vetor_matriz(); 
                    eat(L_S_BRACKET); 
                    dimensao(); 
                    eat(R_S_BRACKET); 
                    tipo_basico(); 
                    eat(SEMICOLON); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
        * Função para processar a declaração de variáveis.
        * Esta função lida com a declaração de variáveis, verificando o tipo da variável e processando o identificador
        * conforme o tipo especificado. O tipo pode ser `INTEIRO`, `REAL`, `CARACTERE`, ou `LOGICO`.
        * Após o tipo e identificador, o token de finalização é consumido, que é um ponto e vírgula (`SEMICOLON`).
        * Se o token não corresponder a um tipo de variável esperado, um erro sintático é gerado.
        */
        void declara_variaveis() 
        {
            switch(this->token) 
            {
                // Se o token é um identificador, o tipo é processado, seguido pelo consumo do token `COLON`,
                // processamento do identificador e, finalmente, consumo do ponto e vírgula.
                case(ID): 
                case(INTEIRO): 
                case(REAL): 
                case(CARACTERE): 
                case(LOGICO): 
                    tipo_basico(); 
                    eat(COLON); 
                    declara_identificador(); 
                    eat(SEMICOLON); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar a declaração de identificadores.
         * 
         * Esta função trata a declaração de um identificador, verificando se o token atual é um identificador
         * e, se for o caso, consome o token e chama a função auxiliar para processar possíveis declarações adicionais.
         * Se o token não for um identificador, um erro sintático é gerado.
        */
        void declara_identificador() 
        {
            switch(this->token) 
            {
                // Se o token é um identificador, consome o token e chama a função auxiliar para continuar o processamento.
                case(ID): 
                    eat(ID); 
                    declara_identificador_aux(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar a declaração de identificadores.
         * Esta função trata os tokens que podem aparecer após a declaração inicial de um identificador.
         * Dependendo do token encontrado, a função pode consumir um token, continuar com a declaração
           de identificadores ou simplesmente terminar a execução. Se o token não corresponder a nenhum
           dos esperados, um erro sintático é gerado.
        */
        void declara_identificador_aux() 
        {
            switch(this->token) 
            {
                // Se o token é uma vírgula, consome o token e chama a função para continuar a declaração de identificadores.
                case(COMMA): 
                    eat(COMMA); 
                    declara_identificador(); 
                    break;

                // Se o token é um ponto e vírgula ou um colchete direito, não faz nada e simplesmente termina a execução.
                case(SEMICOLON): 
                case(R_C_BRACKET): 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função para processar a declaração de vetores e matrizes.
         * Esta função lida com a identificação de tokens que representam vetores e matrizes.
         * Dependendo do token encontrado, ela consome o token correspondente. Se o token
           não corresponder a nenhum dos esperados, um erro sintático é gerado.
         */
        void vetor_matriz() 
        {
            switch(this->token) 
            {
                // Se o token é VETOR, consome o token e prossegue.
                case(VETOR): 
                    eat(VETOR); 
                    break;
                
                // Se o token é MATRIZ, consome o token e prossegue.
                case(MATRIZ): 
                    eat(MATRIZ); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função para processar uma dimensão em uma declaração.
         * Esta função trata a declaração de uma dimensão que inclui um valor inteiro,
           seguido por dois pontos e outro valor inteiro. Após o processamento inicial,
           ela pode chamar a função auxiliar `dimensao_aux` para tratar dimensões adicionais.
        */
        void dimensao() 
        {
            switch(this->token) 
            {
                // Se o token é um número inteiro (NUM_INT), consome o token, seguido por dois pontos (COLON)
                // e outro número inteiro (NUM_INT), e então chama a função dimensao_aux para processar dimensões adicionais.
                case(NUM_INT): 
                    eat(NUM_INT); 
                    eat(COLON); 
                    eat(NUM_INT); 
                    dimensao_aux(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar dimensões adicionais em uma declaração.
         * Esta função trata o processamento de dimensões adicionais, que podem ser separadas por vírgulas,
         * dentro de uma declaração de vetor ou matriz. A função consome o token correspondente e processa
           a próxima dimensão, se necessário. Se o token não corresponder ao esperado, é indicado um erro sintático.
        */
        void dimensao_aux() 
        {
            switch(this->token) 
            {
                // Se o token é uma vírgula (COMMA), consome o token e chama a função dimensao para processar a próxima dimensão.
                case(COMMA): 
                    eat(COMMA); 
                    dimensao(); 
                    break;
                
                // Se o token é um colchete de fechamento (R_S_BRACKET), termina o processamento das dimensões adicionais.
                case(R_S_BRACKET): 
                    break;
                
                default: 
                    ERRO_SINTATICO; 
            }   
        }


        /**
         * Função para processar um tipo básico.
         * Esta função lida com diferentes tipos básicos que podem ser encontrados no código, como identificadores
           e tipos primitivos. Dependendo do token atual, a função consome o token correspondente.
         * Se o token não corresponder a nenhum dos tipos esperados, a função indica um erro sintático.
        */
        void tipo_basico()
        {
            switch(this->token) 
            {
                // Se o token é ID, consome o token ID.
                case(ID): 
                    eat(ID); 
                    break;
                
                // Se o token é INTEIRO, consome o token INTEIRO.
                case(INTEIRO): 
                    eat(INTEIRO); 
                    break;
                
                // Se o token é REAL, consome o token REAL.
                case(REAL): 
                    eat(REAL); 
                    break;
                
                // Se o token é CARACTERE, consome o token CARACTERE.
                case(CARACTERE): 
                    eat(CARACTERE); 
                    break;
                
                // Se o token é LOGICO, consome o token LOGICO.
                case(LOGICO): 
                    eat(LOGICO); 
                    break;
                
                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar um bloco de comandos.
         * Esta função lida com a estrutura de um bloco de comandos, que começa com o token `INICIO` e termina com o token `FIM`.
         * Entre `INICIO` e `FIM`, a função processa uma lista de comandos usando `lista_comandos`.
         * Se o token atual não for `INICIO`, a função indica um erro sintático.
        */
        void bloco_comandos() 
        {
            switch(this->token) 
            {
                // Se o token é INICIO, consome o token, processa a lista de comandos, e consome o token FIM.
                case(INICIO): 
                    eat(INICIO);      // Consome o token INICIO.
                    lista_comandos(); // Processa a lista de comandos dentro do bloco.
                    eat(FIM);         // Consome o token FIM que fecha o bloco de comandos.
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar uma lista de comandos.
         * Esta função lida com uma sequência de comandos onde cada comando é seguido por um ponto e vírgula.
         * Dependendo do token atual, a função consome o token correspondente, processa o comando associado, consome o ponto e vírgula,
           e então chama `lista_comandos_aux` para processar a lista de comandos subsequentes.
         * A função termina com um erro sintático se o token não corresponder a um comando válido.
         */
        void lista_comandos() 
        {

            switch(this->token) 
            {
                // Se o token é ID, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(ID): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é SE, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(SE): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é ENQUANTO, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(ENQUANTO): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é REPITA, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(REPITA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é PARA, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(PARA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é LEIA, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(LEIA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é IMPRIMA, consome o token, processa um comando, consome o ponto e vírgula, e chama `lista_comandos_aux` para processar comandos subsequentes.
                case(IMPRIMA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar a lista de comandos auxiliares.
         * Esta função é responsável por lidar com uma sequência de comandos, onde cada comando é seguido por um ponto e vírgula.
         * Dependendo do token atual, a função consome o token correspondente e chama a função `comandos` para processar o comando.
         * Em seguida, ela consome o ponto e vírgula e recursivamente chama `lista_comandos_aux` para processar a lista de comandos subsequentes.
         * A função termina quando encontra um token que não é um comando válido ou um terminador.
         */
        void lista_comandos_aux() 
        {

            switch(this->token) 
            {
                // Se o token é ID, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(ID): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é SE, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(SE): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é ENQUANTO, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(ENQUANTO): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é REPITA, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(REPITA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é PARA, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(PARA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é LEIA, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(LEIA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é IMPRIMA, consome o token, processa um comando, consome o ponto e vírgula, e chama recursivamente a função.
                case(IMPRIMA): 
                    comandos(); 
                    eat(SEMICOLON); 
                    lista_comandos_aux(); 
                    break;

                // Se o token é FIM, ATE ou SENAO, a função termina a execução.
                case(FIM):
                case(ATE):
                case(SENAO):
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função para processar comandos da linguagem.
         * Esta função trata diferentes tipos de comandos e suas respectivas sintaxes. Dependendo do tipo de token atual,
           a função realiza ações específicas como processamento de expressões, listas de comandos, iterações e impressões.
         * A função assegura que os comandos estejam formatados corretamente conforme a gramática da linguagem.
         */
        void comandos() 
        {

            switch(this->token)
            {
                // Se o token é ID, consome o token e chama a função auxiliar para comandos relacionados a identificadores.
                case(ID): 
                    eat(ID); 
                    comandos_aux_id(); 
                    break;

                // Se o token é SE, consome o token, processa uma expressão, consome ENTAO, processa uma lista de comandos,
                // e então chama a função auxiliar para comandos relacionados a SE.
                case(SE): 
                    eat(SE); 
                    expressao(); 
                    eat(ENTAO); 
                    lista_comandos(); 
                    comandos_aux_se(); 
                    break;

                // Se o token é ENQUANTO, consome o token, processa uma expressão, consome FACA, processa uma lista de comandos,
                // e então consome FIM e ENQUANTO.
                case(ENQUANTO): 
                    eat(ENQUANTO); 
                    expressao(); 
                    eat(FACA); 
                    lista_comandos(); 
                    eat(FIM); 
                    eat(ENQUANTO); 
                    break;

                // Se o token é PARA, consome o token, consome ID, consome DE, processa uma expressão, consome ATE,
                // processa outra expressão, e então chama a função auxiliar para comandos relacionados a PARA.
                case(PARA): 
                    eat(PARA); 
                    eat(ID); 
                    eat(DE); 
                    expressao(); 
                    eat(ATE); 
                    expressao(); 
                    comandos_aux_para(); 
                    break;

                // Se o token é REPITA, consome o token, processa uma lista de comandos e então consome ATE e uma expressão.
                case(REPITA): 
                    eat(REPITA); 
                    lista_comandos(); 
                    eat(ATE); 
                    expressao(); 
                    break;

                // Se o token é LEIA, consome o token, consome L_C_BRACKET, processa uma variável, e então consome R_C_BRACKET.
                case(LEIA): 
                    eat(LEIA); 
                    eat(L_C_BRACKET); 
                    variavel(); 
                    eat(R_C_BRACKET); 
                    break;

                // Se o token é IMPRIMA, consome o token, consome L_C_BRACKET, processa uma expressão iterativa,
                // e então consome R_C_BRACKET.
                case(IMPRIMA): 
                    eat(IMPRIMA); 
                    eat(L_C_BRACKET); 
                    expr_iter(); 
                    eat(R_C_BRACKET); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar comandos relacionados a identificadores.
         * Esta função trata de comandos que envolvem identificadores e operações associadas. A função verifica o tipo de token
           atual e executa as ações correspondentes, como atribuições e manipulações de expressões dentro de colchetes.
         * A função é responsável por garantir que a sintaxe dos comandos envolvendo identificadores esteja correta.
         */
        void comandos_aux_id() 
        {

            switch(this->token) 
            {
                // Se o token é SEMICOLON, não há ação adicional necessária.
                case(SEMICOLON): 
                    break;

                // Se o token é ASSIGN, consome o token e processa uma expressão.
                case(ASSIGN): 
                    eat(ASSIGN); 
                    expressao(); 
                    break;

                // Se o token é L_C_BRACKET, consome o token, processa a expressão iterativa e então consome o token R_C_BRACKET.
                case(L_C_BRACKET): 
                    eat(L_C_BRACKET); 
                    expr_iter(); 
                    eat(R_C_BRACKET); 
                    break;

                // Se o token é L_S_BRACKET, consome o token, processa a expressão iterativa, consome o token R_S_BRACKET,
                // e então consome o token ASSIGN seguido de uma expressão.
                case(L_S_BRACKET): 
                    eat(L_S_BRACKET); 
                    expr_iter(); 
                    eat(R_S_BRACKET); 
                    eat(ASSIGN); 
                    expressao(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
        * Função auxiliar para processar comandos relacionados a estruturas condicionais `se` (if statements).
        * Esta função lida com comandos que seguem uma estrutura condicional `se` (if statement). O comportamento da função
          depende do token atual, que pode ser uma cláusula `senão` (else) ou o fim da estrutura `se`. 
        * A função garante que a estrutura condicional esteja corretamente formada, processando os comandos internos e
          os tokens que encerram o bloco.
        */
        void comandos_aux_se() 
        {

            switch(this->token) 
            {
                // Se o token é SENAO, consome o token, processa a lista de comandos, e então consome os tokens FIM e SE
                case(SENAO): 
                    eat(SENAO); 
                    lista_comandos(); 
                    eat(FIM); 
                    eat(SE); 
                    break;

                // Se o token é FIM, consome o token e então consome o token SE, indicando o fim da estrutura condicional.
                case(FIM): 
                    eat(FIM); 
                    eat(SE); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar comandos relacionados a laços de repetição (loops) no código.
         * Esta função lida com comandos que envolvem a estrutura de controle `para` (for loop). O comportamento da função
           depende do token atual, que pode ser um comando de repetição ou uma declaração de passo.
         * A função chama funções adicionais para processar os comandos dentro do laço e os parâmetros relacionados,
           garantindo que a estrutura do loop esteja completa e correta.
         */
        void comandos_aux_para() 
        {

            switch(this->token) 
            {
                // Se o token é o início de um bloco de comandos (FACA), consome o token e processa a lista de comandos,
                // seguido pelos tokens FIM e PARA, que encerram o bloco.
                case(FACA): 
                    eat(FACA); 
                    lista_comandos(); 
                    eat(FIM); 
                    eat(PARA); 
                    break;

                // Se o token é um passo (PASSO), consome o token, processa uma expressão, e então continua com o bloco de comandos,
                // seguido pelos tokens FIM e PARA.
                case(PASSO): 
                    eat(PASSO); 
                    expressao(); 
                    eat(FACA); 
                    lista_comandos(); 
                    eat(FIM); 
                    eat(PARA); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função responsável por processar uma expressão, que pode incluir termos e operações adicionais.         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função chama `expressao_simples` para processar uma expressão simples e, em seguida,
           chama `expressao_` para continuar o processamento da expressão.
         * A função lida com tokens que representam diferentes tipos de valores, operadores e expressões entre colchetes.
        */
        void expressao() 
        {

            switch(this->token) 
            {
                // Para tokens de identificadores e valores (inteiros, reais, strings), processa uma expressão simples
                // e depois chama `expressao_` para continuar o processamento da expressão.
                case(ID): 
                case(NUM_INT): 
                case(NUM_REAL): 
                case(STRING): 
                case(PLUS): 
                case(MINUS): 
                case(NAO): 
                case(VERDADEIRO): 
                case(FALSO): 
                case(L_C_BRACKET): 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função responsável por processar expressões simples com base em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode chamar `termo` para processar um termo e depois chamar `expressao_simples_`
         * para continuar o processamento da expressão simples. Para tokens de operadores como PLUS e MINUS, a função consome
           o operador antes de processar o termo e a expressão simples.
         * A função lida com tokens que representam diferentes tipos de valores, operadores e expressões entre colchetes.
        */
        void expressao_simples() 
        {

            switch(this->token)
            {
                // Para tokens de identificadores e valores (inteiros, reais, strings), consome o token chamando a função `termo`,
                // e em seguida chama `expressao_simples_` para continuar o processamento da expressão simples.
                case(ID): 
                case(NUM_INT): 
                case(NUM_REAL): 
                case(STRING): 
                case(NAO): 
                case(VERDADEIRO): 
                case(FALSO): 
                case(L_C_BRACKET): 
                case(EQUAL): 
                    termo(); 
                    expressao_simples_(); 
                    break;

                // Para tokens de operadores PLUS e MINUS, consome o operador, processa um termo e chama `expressao_simples_`
                // para continuar o processamento da expressão simples.
                case(PLUS): 
                case(MINUS): 
                    eat(this->token); 
                    termo(); 
                    expressao_simples_(); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função responsável por processar termos com base em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função chama a função `fator` para processar o fator associado e, em seguida, chama a
         * função `termo_` para continuar o processamento.
         * A função lida com tokens que representam diferentes tipos de valores e operações, assim como termos que
           podem ser processados em diferentes contextos.
         */
        void termo() 
        {

            switch(this->token) 
            {
                // Para tokens de identificadores e valores (inteiros, reais, strings), consome o token chamando a função `fator`,
                // e em seguida chama `termo_` para continuar o processamento do termo.
                case(ID): 
                case(NUM_INT): 
                case(NUM_REAL): 
                case(STRING): 
                case(NAO): 
                case(VERDADEIRO): 
                case(FALSO): 
                case(L_C_BRACKET): 
                    fator(); 
                    termo_(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função responsável por processar fatores com base em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token e chamar funções auxiliares para processar identificadores
           ou outros tipos de valores. Também pode processar expressões entre colchetes.
         * A função lida com tokens que representam diferentes tipos de valores e operações, bem como expressões entre colchetes.
        */
        void fator()
        {

            switch(this->token) 
            {
                // Para o token ID, consome o token e chama a função auxiliar para processar fatores adicionais associados ao identificador.
                case(ID): 
                    eat(ID); 
                    fator_id_aux(); 
                    break;

                // Para tokens de números inteiros e reais, consome o token correspondente.
                case(NUM_INT): 
                case(NUM_REAL): 
                    eat(this->token); 
                    break;

                // Para o token STRING, consome o token correspondente.
                case(STRING): 
                    eat(STRING); 
                    break;

                // Para o token NAO, consome o token e processa o fator associado recursivamente.
                case(NAO): 
                    eat(NAO); 
                    fator(); 
                    break;

                // Para os tokens VERDADEIRO e FALSO, consome o token correspondente.
                case(VERDADEIRO): 
                case(FALSO): 
                    eat(this->token); 
                    break;

                // Para o token de colchete de abertura, consome o token, processa uma expressão entre colchetes, e consome o colchete de fechamento.
                case(L_C_BRACKET): 
                    eat(L_C_BRACKET); 
                    expressao(); 
                    eat(R_C_BRACKET); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar fatores associados a identificadores, com base em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token e processar expressões dentro de colchetes ou fazer nada
           se o token não exigir ação adicional.
         * O token atual é comparado com vários tipos de tokens esperados, e a função pode consumir tokens e processar
           expressões dependendo do tipo de token.
        */
        void fator_id_aux() 
        {

            switch(this->token) 
            {
                // Para tokens de ponto e vírgula e colchetes, não há ações associadas além de passar para o próximo token.
                case(SEMICOLON): 
                case(R_C_BRACKET): 
                case(R_S_BRACKET): 
                    break;

                // Para tokens de colchete de abertura, consome o token, processa expressões dentro dos colchetes, 
                // e então consome o token de fechamento correspondente.
                case(L_C_BRACKET): 
                    eat(L_C_BRACKET); 
                    expr_iter(); 
                    eat(R_C_BRACKET); 
                    break;

                case(L_S_BRACKET): 
                    eat(L_S_BRACKET); 
                    expr_iter(); 
                    eat(R_S_BRACKET); 
                    break;

                // Para outros tokens, não há ações associadas e a função não faz nada.
                case(EQUAL): 
                case(COMMA): 
                case(ENTAO): 
                case(FACA): 
                case(ATE): 
                case(PASSO): 
                case(PLUS): 
                case(MINUS): 
                case(DIFFERENT): 
                case(LESS): 
                case(LEQ): 
                case(GREATER): 
                case(GEQ): 
                case(OU): 
                case(MULT): 
                case(DIVISION): 
                case(DIV): 
                case(E): 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função responsável por processar variáveis baseadas em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token e chamar uma função auxiliar para processar expressões adicionais.
         * O token atual é comparado com vários tipos de tokens esperados, e em alguns casos, a função consome o token atual
           e chama `variavel_aux()` para processar componentes adicionais relacionados à variável.
        */
        void variavel() 
        {

            switch(this->token)
            {
                // Para o token ID, consome o token e chama a função auxiliar para processar componentes adicionais da variável.
                case(ID): 
                    eat(ID); 
                    variavel_aux(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar variáveis com base em tokens específicos.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token e processar expressões dentro de colchetes.
         * O token atual é comparado com vários tipos de tokens esperados, e em alguns casos, a função chama 
           `expr_iter()` para processar expressões dentro de colchetes.
        */
        void variavel_aux() 
        {

            switch(this->token) 
            {
                // Para o token de colchete de fechamento, não há ações associadas.
                case(R_C_BRACKET): 
                    break;

                // Para o token de colchete de abertura, consome o token, processa expressões entre colchetes,
                // e então consome o token de fechamento.
                case(L_S_BRACKET): 
                    eat(L_S_BRACKET); 
                    expr_iter(); 
                    eat(R_S_BRACKET); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função responsável por processar expressões iterativas com diferentes tipos de tokens.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token, chamar outras funções para processar termos, expressões, 
           e também chamar funções auxiliares para processar expressões separadas por vírgulas.
         * O token atual é comparado com vários tipos de tokens esperados, e em alguns casos, a função consome o token atual
           e chama `expr_iter_id_aux()` ou outras funções para processar partes adicionais da expressão.
        */
        void expr_iter() 
        {
 
            switch(this->token) 
            {
                // Para o token ID, consome o token e chama a função auxiliar para processar expressões iterativas com IDs.
                case(ID): 
                    eat(ID); 
                    expr_iter_id_aux(); 
                    break;

                // Para tokens de números inteiros, reais, strings, e valores booleanos, consome o token, processa termos e expressões, 
                // e então chama `expr_iter_comma_expr_loop()` para processar expressões adicionais separadas por vírgulas.
                case(NUM_INT): 
                case(NUM_REAL): 
                case(STRING): 
                case(VERDADEIRO): 
                case(FALSO): 
                    eat(this->token); 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                // Para operadores de adição e subtração, consome o token, processa termos e expressões, e chama `expr_iter_comma_expr_loop()`.
                case(PLUS): 
                case(MINUS): 
                    eat(this->token); 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                // Para o token NÃO, consome o token, processa fatores e outros componentes da expressão, e chama `expr_iter_comma_expr_loop()`.
                case(NAO): 
                    eat(NAO); 
                    fator(); 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                // Para tokens de colchetes, consome o token de abertura, processa a expressão entre os colchetes, 
                // e chama `expr_iter_comma_expr_loop()` após o fechamento dos colchetes.
                case(L_C_BRACKET): 
                    eat(L_C_BRACKET); 
                    expressao(); 
                    eat(R_C_BRACKET); 
                    termo_(); 
                    expressao_simples_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }   
        }


        /**
         * Função responsável por processar iterações e expressões separadas por vírgulas.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token, chamar outras funções para processar expressões iterativas, 
         * e lidar com casos de tokens de fechamento de colchetes.
         * O token atual é comparado com vários tipos de tokens esperados, e em alguns casos, a função pode chamar 
           `expr_iter()` para processar expressões adicionais.
         */
        void expr_iter_comma_expr_loop() 
        {

            switch(this->token) 
            {
                // Para o token de vírgula, consome o token e chama a função para processar expressões iterativas.
                case(COMMA): 
                    eat(COMMA); 
                    expr_iter(); 
                    break;

                // Para tokens de fechamento de colchetes, não há ações associadas.
                case(R_C_BRACKET): 
                case(R_S_BRACKET): 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função auxiliar para processar expressões iterativas identificadas.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode consumir o token, chamar outras funções para processar partes da expressão,
           e também pode executar uma função auxiliar para iterar sobre expressões separadas por vírgulas.
         * O token atual é comparado com vários tipos de tokens esperados e, para a maioria dos casos, a função chama
         * várias funções para processar termos e expressões, e então executa `expr_iter_comma_expr_loop()` para lidar com expressões adicionais.
        */
        void expr_iter_id_aux() 
        {

            switch(this->token) 
            {
                // Para tokens que envolvem colchetes, consumindo os colchetes e processando a expressão entre eles.
                case(L_C_BRACKET): 
                    eat(L_C_BRACKET); 
                    expr_iter(); 
                    eat(R_C_BRACKET); 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                case(R_C_BRACKET): 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                case(L_S_BRACKET): 
                    eat(L_S_BRACKET); 
                    expr_iter(); 
                    eat(R_S_BRACKET); 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                case(R_S_BRACKET): 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                // Para operadores e símbolos como "=" e ",", consome o token e processa os termos e expressões subsequentes.
                case(EQUAL): 
                case(COMMA): 
                case(PLUS): 
                case(MINUS): 
                case(DIFFERENT): 
                case(LESS): 
                case(LEQ): 
                case(GREATER): 
                case(GEQ): 
                case(OU): 
                case(MULT): 
                case(DIVISION): 
                case(DIV): 
                case(E): 
                    termo_(); 
                    expressao_simples_(); 
                    expressao_(); 
                    expr_iter_comma_expr_loop(); 
                    break;

                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função responsável por analisar e processar expressões na entrada.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode chamar outras funções ou realizar ações específicas.
         * O token atual é comparado com vários tipos de tokens esperados. Em alguns casos, a função consome o token atual
           e chama outras funções para processar expressões adicionais.
        */
        void expressao_()
        {

            switch(this->token)
            {
                // Para tokens de fechamento de colchetes, ponto e vírgula, ou vírgula, não há ações associadas.
                case(R_C_BRACKET): 
                case(R_S_BRACKET): 
                case(SEMICOLON): 
                case(COMMA): 
                case(ENTAO): 
                case(FACA): 
                case(ATE): 
                case(PASSO): 
                    break;

                // Para operadores de comparação, consome o token atual, processa uma expressão simples, e então processa expressões adicionais.
                case(EQUAL): 
                    eat(EQUAL); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                case(DIFFERENT): 
                    eat(DIFFERENT); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                case(LESS): 
                    eat(LESS); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                case(LEQ): 
                    eat(LEQ); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                case(GREATER): 
                    eat(GREATER); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                case(GEQ): 
                    eat(GEQ); 
                    expressao_simples(); 
                    expressao_(); 
                    break;

                
                default: 
                    ERRO_SINTATICO; 
            }
        }


        /**
         * Função responsável por analisar e processar expressões simples na entrada.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode chamar outras funções ou realizar ações específicas.
         * O token atual é comparado com vários tipos de tokens esperados, e em casos específicos, a função realiza
           chamadas a outras funções ou ações relacionadas.
        */
        void expressao_simples_() 
        {

            switch(this->token) 
            {
                // Para tokens de fechamento de colchetes, ponto e vírgula, ou operadores de comparação, não há ações associadas.
                case(R_C_BRACKET): 
                case(R_S_BRACKET): 
                case(SEMICOLON): 
                case(EQUAL): 
                case(COMMA): 
                case(ATE): 
                case(ENTAO): 
                case(FACA): 
                case(PASSO): 
                case(DIFFERENT): 
                case(LESS): 
                case(LEQ): 
                case(GREATER): 
                case(GEQ): 
                    break;

                // Para operadores de adição, subtração e OR, realiza a ação associada e processa o termo e as expressões simples subsequentes.
                case(PLUS): 
                    eat(PLUS); 
                    termo(); 
                    expressao_simples_(); 
                    break;

                case(MINUS): 
                    eat(MINUS); 
                    termo(); 
                    expressao_simples_(); 
                    break;

                case(OU): 
                    eat(OU); 
                    termo(); 
                    expressao_simples_(); 
                    break;

                default: 
                    ERRO_SINTATICO;
            }
        }


        /**
         * Função responsável por analisar e processar termos na entrada.
         * Esta função utiliza um `switch` para verificar o tipo de token atual e processa o token conforme o caso.
         * Dependendo do token, a função pode chamar outras funções ou realizar ações específicas.
         * O token atual é comparado com vários tipos de tokens esperados, e em casos específicos, a função realiza
           chamadas recursivas ou chamadas a outras funções.
         */
        void termo_()
        {
        
            switch(this->token) 
            {
                // Para tokens simples como ponto e vírgula, colchetes ou operadores, não há ações associadas.
                case(SEMICOLON): 
                case(R_C_BRACKET): 
                case(R_S_BRACKET): 
                case(EQUAL): 
                case(COMMA): 
                case(ENTAO): 
                case(FACA): 
                case(ATE): 
                case(PASSO): 
                case(PLUS): 
                case(MINUS): 
                case(DIFFERENT): 
                case(LESS): 
                case(LEQ): 
                case(GREATER): 
                case(GEQ): 
                case(OU): 
                    break;

                // Para operadores multiplicativos, realiza a ação associada e processa o fator e os termos subsequentes.
                case(MULT): 
                    eat(MULT); 
                    fator(); 
                    termo_(); 
                    break;
                    
                case(DIVISION): 
                    eat(DIVISION); 
                    fator(); 
                    termo_(); 
                    break;
                    
                case(DIV): 
                    eat(DIV); 
                    fator(); 
                    termo_(); 
                    break;
                    
                case(E): 
                    eat(E); 
                    fator(); 
                    termo_(); 
                    break;

                // Caso o token não corresponder a nenhum dos casos esperados.
                default: 
                    ERRO_SINTATICO; 
                    
            }
        }



    public:
        /**
        * Construtor da classe Automaton.
        * Este construtor inicializa o estado inicial do autômato e define o índice atual e a entrada.
        * @param initial_state O estado inicial do autômato.
        */
        Automaton(int initial_state)
        {
            this->initial_state = initial_state; // Define o estado inicial.
            this->current_index = 0;             // Define o índice atual como 0.
            this->input = input;                 // Define a entrada inicial.
        }

        /**
         * Analisa a entrada fornecida.
         * Esta função reinicia o índice atual e a entrada, e então inicia o processo de análise. 
         * Ela também inicializa a linha e a coluna atuais e chama a função de análise principal.
         * @param input A entrada que será analisada.
         */
        void Analyze(string input) 
        {
            this->current_index = 0; // Reinicia o índice atual para 0.
            this->input = input;     // Define a nova entrada para análise.
            this->line_no = 1;       // Inicializa o número da linha como 1.
            this->col_no = 1;        // Inicializa o número da coluna como 1.

            advance();  // Avança o índice para a próxima posição.
            programa(); // Chama a função principal de análise.
        }
};


/*
 * lê a entrada do usuário, cria um objeto da classe `Automaton`,
 * e utiliza esse objeto para analisar a entrada fornecida.
 */
int main() 
{
    int current_state = 1;   // Estado atual inicial do autômato.
    int last_final_index;    // Índice do último estado final.
    int current_final_index; // Índice do estado final atual.

    string input; // Armazena a entrada lida do usuário.
    char symbol;  // Armazena cada caractere lido da entrada.

    // Lê cada caractere da entrada padrão (stdin) e o adiciona à string 'input'.
    while (cin.get(symbol)) 
    {
        input += symbol; // Adiciona o caractere à string de entrada.
    }
    input += '\0'; // Adiciona um caractere nulo no final da entrada para marcar o fim da string.

    // Cria um objeto da classe Automaton com o estado inicial definido como 1.
    Automaton automato(1);
    // Analisa a entrada usando o objeto Automaton criado.
    automato.Analyze(input);

    return 0;

}