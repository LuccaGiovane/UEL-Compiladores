#include <iostream>
#include <vector>
#include "matriz.cpp"

using namespace std;

class Automaton{
    private: 
        int initialState;
        int currentIndex;
        int token;
        int lineNo;
        int colNo;
        string input;
        string tokenContent;
    
    void simMistake(){
        this->colNo = this->colNo - this->tokenContent.length(); 
        cout << "ERRO DE SINTAXE. Linha: " << this->lineNo << " Coluna: " << this->colNo << " -> \'" << this->tokenContent << "\'"; 
        exit(0);
    }
    void lexMistake(){
        this->colNo = this->colNo - this->tokenContent.length(); 
        cout << "ERRO LEXICO. Linha: " << this->lineNo << " Coluna: " << this->colNo << " -> \'" << this->tokenContent << "\'"; 
        exit(0);
    }

    int nextToken(){
        int lastFinalState = 0;
        int lastFinalIndex = this->currentIndex;
        int curentState = this->initialState;
        int i;

        for(i = this->currentIndex; i < this->input.length(); i++){
            int nextState = automaton[curentState][input[i]];
                if(finalStates[nextState] == true){
                    lastFinalState = nextState;
                    lastFinalIndex = i;
                }
                if(tokens[nextState] == ERRO){
                    this->tokenContent = this->input.substr(this->currentIndex, i - this->currentIndex);
                    this->currentIndex = lastFinalIndex + 1;
                    return tokens[lastFinalState];
                }
            curentState = nextState;
        }
        this->tokenContent = this->input.substr(this->currentIndex, this->input.length() - this->currentIndex);
        this->currentIndex = lastFinalIndex + 1;
        return tokens[lastFinalState];
    }

    void countCommentLength(){
        int i;
        for(i = 0; i < this->tokenContent.length(); i++){
            if(this->tokenContent[i] == '\n'){
                this->lineNo++;
                this->colNo = 1;
            } else{
                this->colNo++;
            }
        }
    }

    void advance(){
        this->token = nextToken();
        if(this->token == EOL){
            this->lineNo++;
            this->colNo = 1;
        } else if(this->token == COMMENT){
            countCommentLength();
        } else{
            this->colNo += this->tokenContent.length();
        }
        while(this->token == COMMENT || this->token == WHITESPACE || this->token == EOL || this->token == OTHER){
            if(this->token == OTHER){
                lexMistake();
            }
            this->token = nextToken();
            if(this->token == EOL){
                this->lineNo++;
                this->colNo = 1;
            } else if(this->token == COMMENT){
                countCommentLength();
            } else{
               this->colNo += this->tokenContent.length();
            }
        }
    }

    void eat(int token){
        if(this->token == token){
            advance();
        } else{
            simMistake();      
        }
    }

    void program(){
        eat(ALGORITMO);
        eat(ID);
        eat(SEMICOLON);
        variableBlock();
        procedureFunction();
        commandBlock();
        eat(DOT);
        cout << "PROGRAMA CORRETO.";
    }

    void procedureFunction(){
        switch(this->token){
        case(PROCEDIMENTO): procedureDeclare(); 
                            procedureFunction(); 
                            break;
        case(FUNCAO): funcionDeclare();     
                      procedureFunction();
                      break;
        case(INICIO): break;
        default: simMistake();
        
        }
    }

    void procedureDeclare(){
        switch(this->token){
            case(PROCEDIMENTO): eat(PROCEDIMENTO);
                                eat(ID);
                                parameters();
                                eat(SEMICOLON);
                                parametersDeclare();
                                variableBlock();
                                commandBlock();
                                eat(SEMICOLON);
                                break;
            default: simMistake();
            
        }
    }

    void funcionDeclare(){
        switch(this->token){
            case(FUNCAO): eat(FUNCAO);
                          eat(ID);
                          parameters();
                          eat(COLON);
                          basicType();
                          eat(SEMICOLON);
                          parametersDeclare();
                          variableBlock();
                          commandBlock();
                          eat(SEMICOLON);
                          break;
            default: simMistake();
            
        }
    }

    void parameters(){
        switch(this->token){
            case(L_C_BRACKET): eat(L_C_BRACKET);
                               identifierDeclare();
                               eat(R_C_BRACKET);
                               break;
            case(SEMICOLON): break;
            case(COLON): break;
            default: simMistake();
            
        }
    }

    void parametersDeclare(){
        switch(this->token){
            case(ID): declare(); 
                      break;
            case(TIPO): declare(); 
                        break;
            case(INTEIRO): declare(); 
                           break;
            case(REAL): declare(); 
                        break;
            case(CARACTERE): declare();
                             break;
            case(LOGICO): declare(); 
                          break;
            case(PROCEDIMENTO): break; 
            case(FUNCAO): break;
            case(VARIAVEIS): break;
            case(INICIO): break;
            default: simMistake();
            
        }
    }

    void variableBlock(){
         switch(this->token){
            case(VARIAVEIS): eat(VARIAVEIS); 
                             declare(); 
                             break;
            case(PROCEDIMENTO): break;
            case(FUNCAO): break;
            case(INICIO): break;
            case(_EOF): break;
            default: simMistake();
            
        }
    }

    void declare(){
         switch(this->token){
            case(ID): variableDeclare();
                      declareAux(); 
                      break;
            case(INTEIRO): variableDeclare();
                           declareAux(); 
                           break;
            case(REAL): variableDeclare();
                        declareAux(); 
                        break;
            case(CARACTERE): variableDeclare();
                             declareAux(); 
                             break;
            case(LOGICO): variableDeclare();
                          declareAux(); 
                          break;
            case(TIPO): typeDeclare(); 
                        declareAux(); 
                        break;
            default: simMistake();
            
        }
    }

    void declareAux(){
         switch(this->token){
            case(ID): variableDeclare();
                      declareAux(); 
                      break;
            case(INTEIRO): variableDeclare();
                           declareAux(); 
                           break;
            case(REAL): variableDeclare();
                        declareAux(); 
                        break;
            case(CARACTERE): variableDeclare();
                             declareAux(); 
                             break;
            case(LOGICO): variableDeclare();
                          declareAux(); 
                          break;
            case(TIPO): typeDeclare(); 
                        declareAux(); 
                        break;
            case(PROCEDIMENTO): break;
            case(FUNCAO): break;
            case(VARIAVEIS): break;
            case(INICIO): break;
            case(_EOF): break;
            default: simMistake();
            
         }
    }

    void typeDeclare(){
        switch(this->token){
            case(TIPO): eat(TIPO);
                        eat(ID);
                        eat(EQUAL);
                        matrixVector();
                        eat(L_S_BRACKET);
                        dimention();
                        eat(R_S_BRACKET);
                        basicType();
                        eat(SEMICOLON);
                        break;
            default: simMistake();
             
        }
    }

    void variableDeclare(){
        switch(this->token){
            case(ID): basicType();
                      eat(COLON);
                      identifierDeclare();
                      eat(SEMICOLON);
                      break;
            case(INTEIRO): basicType();
                           eat(COLON);
                           identifierDeclare();
                           eat(SEMICOLON);
                           break;
            case(REAL): basicType();
                        eat(COLON);
                        identifierDeclare();
                        eat(SEMICOLON);
                        break;
            case(CARACTERE): basicType();
                             eat(COLON);
                             identifierDeclare();
                             eat(SEMICOLON);
                             break;
            case(LOGICO): basicType();
                          eat(COLON);
                          identifierDeclare();
                          eat(SEMICOLON);
                          break;
            default: simMistake();
            
        }
    }

    void identifierDeclare(){
        switch(this->token){
            case(ID): eat(ID);
                      identifierDeclareAux();
                      break;
            default: simMistake();
            
        }
    }

    void identifierDeclareAux(){
        switch(this->token){
            case(COMMA): eat(COMMA);
                         identifierDeclare();
                         break;
            case(SEMICOLON): break;
            case(R_C_BRACKET): break;
            default: simMistake();
            
        }   
    }
    
    void matrixVector(){
        switch(this->token){
            case(VETOR): eat(VETOR);
                         break;
            case(MATRIZ): eat(MATRIZ);
                          break;
            default: simMistake();
            
        }
    }

    void dimention(){
        switch(this->token){
            case(NUM_INT): eat(NUM_INT);
                           eat(COLON);
                           eat(NUM_INT);
                           dimentionAux();
                           break;
            default: simMistake();
            
        }
    }

    void dimentionAux(){
        switch(this->token){
            case(COMMA): eat(COMMA);
                         dimention();
                         break;
            case(R_S_BRACKET): break;
            default: simMistake();
                   
        }
    }

    void basicType(){
        switch(this->token){
            case(ID): eat(ID);
                      break;
            case(INTEIRO): eat(INTEIRO);
                           break;
            case(REAL): eat(REAL);
                        break;
            case(CARACTERE): eat(CARACTERE);
                             break;
            case(LOGICO): eat(LOGICO);
                          break;
            default: simMistake();
            
        }
    }

    void commandBlock(){
        switch(this->token){
            case(INICIO): eat(INICIO);
                          commandList();
                          eat(FIM);
                          break;
            default: simMistake();
            
        }
    }

    void commandList(){
        switch(this->token){
            case(ID): command(); 
                      eat(SEMICOLON); 
                      commandListAux(); 
                      break;
            case(SE): command(); 
                      eat(SEMICOLON); 
                      commandListAux(); 
                      break;
            case(ENQUANTO): command(); 
                            eat(SEMICOLON); 
                            commandListAux(); 
                            break;
            case(REPITA): command(); 
                          eat(SEMICOLON); 
                          commandListAux(); 
                          break;
            case(PARA): command(); 
                        eat(SEMICOLON); 
                        commandListAux(); 
                        break;
            case(LEIA): command(); 
                        eat(SEMICOLON); 
                        commandListAux(); 
                        break;
            case(IMPRIMA): command(); 
                           eat(SEMICOLON); 
                           commandListAux(); 
                           break;
            default: simMistake();
            
        }
    }

    void commandListAux(){
        switch(this->token){
            case(ID): command(); 
                      eat(SEMICOLON); 
                      commandListAux(); 
                      break;
            case(SE): command(); 
                      eat(SEMICOLON); 
                      commandListAux(); 
                      break;
            case(ENQUANTO): command(); 
                            eat(SEMICOLON); 
                            commandListAux(); 
                            break;
            case(REPITA): command(); 
                          eat(SEMICOLON); 
                          commandListAux(); 
                          break;
            case(PARA): command(); 
                        eat(SEMICOLON); 
                        commandListAux(); 
                        break;
            case(LEIA): command(); 
                        eat(SEMICOLON); 
                        commandListAux(); 
                        break;
            case(IMPRIMA): command(); 
                           eat(SEMICOLON); 
                           commandListAux(); 
                           break;
            case(FIM): break;
            case(ATE): break;
            case(SENAO): break;
            default: simMistake();
            
        }
    }

    void command(){
        switch(this->token){
            case(ID): eat(ID);
                      commandIdAux();
                      break;
            case(SE): eat(SE);
                      expression();
                      eat(ENTAO);
                      commandList();
                      commandIfAux();
                      break;
            case(ENQUANTO): eat(ENQUANTO);
                            expression();
                            eat(FACA);
                            commandList();
                            eat(FIM);
                            eat(ENQUANTO);
                            break;
            case(PARA): eat(PARA);
                        eat(ID);
                        eat(DE);
                        expression();
                        eat(ATE);
                        expression();
                        commandForAux();
                        break;
            case(REPITA): eat(REPITA);
                          commandList();
                          eat(ATE);
                          expression();
                          break;
            case(LEIA): eat(LEIA);
                        eat(L_C_BRACKET);
                        variable();
                        eat(R_C_BRACKET);
                        break;
            case(IMPRIMA): eat(IMPRIMA);
                           eat(L_C_BRACKET);
                           exprIter();
                           eat(R_C_BRACKET);
                           break;
            default: simMistake();
            
        }
    }

    void commandIdAux(){
        switch(this->token){
            case(SEMICOLON): break;
            case(ASSIGN): eat(ASSIGN);
                          expression();
                          break;
            case(L_C_BRACKET): eat(L_C_BRACKET);
                               exprIter();
                               eat(R_C_BRACKET);
                               break;
            case(L_S_BRACKET): eat(L_S_BRACKET);
                               exprIter();
                               eat(R_S_BRACKET);
                               eat(ASSIGN);
                               expression();
                               break;
            default: simMistake();
            
        }
    }

    void commandIfAux(){
        switch(this->token){
            case(SENAO): eat(SENAO);
                         commandList();
                         eat(FIM);
                         eat(SE);
                         break;
            case(FIM): eat(FIM);
                       eat(SE);
                       break;
            default: simMistake();
            
        }
    }

    void commandForAux(){
        switch(this->token){
            case(FACA): eat(FACA);
                        commandList();
                        eat(FIM);
                        eat(PARA);
                        break;
            case(PASSO): eat(PASSO);
                         expression();
                         eat(FACA);
                         commandList();
                         eat(FIM);
                         eat(PARA);
                         break;
            default: simMistake();
            
        }
    }

    void expression(){
        switch(this->token){
            case(ID): simpleExpression(); 
                      expression_(); 
                      break;
            case(NUM_INT): simpleExpression(); 
                           expression_(); 
                           break;
            case(NUM_REAL): simpleExpression(); 
                            expression_(); 
                            break;
            case(STRING): simpleExpression(); 
                          expression_(); 
                          break;
            case(PLUS): simpleExpression(); 
                        expression_();
                        break;
            case(MINUS): simpleExpression(); 
                         expression_(); 
                         break;
            case(NAO): simpleExpression(); 
                       expression_(); 
                       break;
            case(VERDADEIRO): simpleExpression(); 
                              expression_(); 
                              break;
            case(FALSO): simpleExpression(); 
                         expression_(); 
                         break;
            case(L_C_BRACKET): simpleExpression(); 
                               expression_(); 
                               break;
            default: simMistake();
            
        }
    }

    void simpleExpression(){
        switch(this->token){
            case(ID): term();
                      simpleExpression_();
                      break;
            case(NUM_INT): term();
                           simpleExpression_();
                           break;
            case(NUM_REAL):term();
                           simpleExpression_();
                           break;
            case(STRING): term();
                          simpleExpression_();
                          break;
            case(PLUS): eat(PLUS);
                        term();
                        simpleExpression_();
                        break;
            case(MINUS): eat(MINUS);
                         term();
                         simpleExpression_();
                         break;
            case(NAO): term();
                       simpleExpression_();
                       break;
            case(VERDADEIRO): term();
                              simpleExpression_();
                              break;
            case(FALSO): term();
                         simpleExpression_();
                         break;
            case(L_C_BRACKET): term();
                               simpleExpression_();
                               break;
            case(EQUAL): term();
                         simpleExpression_();
                         break;
            default: simMistake();
            
        }
    }

    void term(){
        switch(this->token){
            case(ID): factor();
                      term_(); 
                      break;
            case(NUM_INT): factor(); 
                           term_(); 
                           break;
            case(NUM_REAL): factor(); 
                            term_(); 
                            break;
            case(STRING): factor(); 
                          term_(); 
                          break;
            case(NAO): factor(); 
                       term_(); 
                       break;
            case(VERDADEIRO): factor(); 
                              term_(); 
                              break;
            case(FALSO): factor(); 
                         term_(); 
                         break;
            case(L_C_BRACKET): factor(); 
                               term_(); 
                               break;
            default: simMistake();
            
        }
    }

    void factor(){
        switch(this->token){
            case(ID): eat(ID); 
                      factorIdAux(); 
                      break;
            case(NUM_INT): eat(NUM_INT); 
                           break;
            case(NUM_REAL): eat(NUM_REAL); 
                            break;
            case(STRING): eat(STRING); 
                          break;
            case(NAO): eat(NAO); 
                       factor();
                       break;
            case(VERDADEIRO): eat(VERDADEIRO); 
                              break;
            case(FALSO): eat(FALSO); 
                         break;
            case(L_C_BRACKET): eat(L_C_BRACKET); 
                               expression();
                               eat(R_C_BRACKET);
                               break;
            default: simMistake();
              
        }
    }

    void factorIdAux(){
        switch(this->token){
            case(SEMICOLON): break;
            case(L_C_BRACKET): eat(L_C_BRACKET);
                               exprIter();
                               eat(R_C_BRACKET);
                               break;
            case(R_C_BRACKET): break;
            case(L_S_BRACKET): eat(L_S_BRACKET);
                               exprIter();
                               eat(R_S_BRACKET);
                               break;
            case(R_S_BRACKET): break;
            case(EQUAL): break;
            case(COMMA): break;
            case(ENTAO): break;
            case(FACA): break;
            case(ATE): break;
            case(PASSO): break;
            case(PLUS): break;
            case(MINUS): break;
            case(DIFFERENT): break;
            case(LESS): break;
            case(LEQ): break;
            case(GREATER): break;
            case(GEQ): break;
            case(OU): break;
            case(MULT): break;
            case(DIVISION): break;
            case(DIV): break;
            case(E): break;
            default: simMistake();
            
        }
    }

    void variable(){
        switch(this->token){
            case(ID): eat(ID);
                      variableAux();
                      break;
            default: simMistake();
            
        }
    }

    void variableAux(){
        switch(this->token){
            case(R_C_BRACKET): break;
            case(L_S_BRACKET): eat(L_S_BRACKET);
                               exprIter();
                               eat(R_S_BRACKET);
                               break;
            default: simMistake();
            
        }
    }

    void exprIter(){
        switch(this->token){
            case(ID): eat(ID); exprIterIdAux(); 
                               break;
            case(NUM_INT): eat(NUM_INT); 
                           term_();
                           simpleExpression_();
                           expression_();
                           exprIterCommaExprLoop();
                           break;
            case(NUM_REAL): eat(NUM_REAL);
                            term_();
                            simpleExpression_();
                            expression_();
                            exprIterCommaExprLoop();
                            break;
            case(STRING): eat(STRING);
                          term_();
                          simpleExpression_();
                          expression_();
                          exprIterCommaExprLoop();
                          break;
            case(VERDADEIRO): eat(VERDADEIRO); 
                              term_();
                              simpleExpression_();
                              expression_();
                              exprIterCommaExprLoop();
                              break;
            case(FALSO): eat(FALSO);
                         term_();
                         simpleExpression_();
                         expression_();
                         exprIterCommaExprLoop();
                         break;
            case(PLUS): eat(PLUS);
                        term_();
                        simpleExpression_();
                        expression_();
                        exprIterCommaExprLoop();
                        break;
            case(MINUS): eat(MINUS);
                         term_();
                         simpleExpression_();
                         expression_();
                         exprIterCommaExprLoop();
                         break;
            case(NAO): eat(NAO);
                       factor();
                       term_();
                       simpleExpression_();
                       expression_();
                       exprIterCommaExprLoop();
                       break;
            case(L_C_BRACKET): eat(L_C_BRACKET);
                               expression();
                               eat(R_C_BRACKET);
                               term_();
                               simpleExpression_();
                               exprIterCommaExprLoop();
                               break;
            default: simMistake();
            
        }
    }

    void exprIterCommaExprLoop(){
        switch(this->token){
            case(COMMA): eat(COMMA);
                         exprIter();
                         break;
            case(R_C_BRACKET): break;
            case(R_S_BRACKET): break;
            default: simMistake();
            
        }
    }

    void exprIterIdAux(){
        switch(this->token){
            case(L_C_BRACKET): eat(L_C_BRACKET);
                               exprIter();
                               eat(R_C_BRACKET);
                               term_();
                               simpleExpression_();
                               expression_();
                               exprIterCommaExprLoop();
                               break;
            case(R_C_BRACKET): term_();
                               simpleExpression_();
                               expression_();
                               exprIterCommaExprLoop();
                               break;
            case(L_S_BRACKET): eat(L_S_BRACKET);
                               exprIter();
                               eat(R_S_BRACKET);
                               term_();
                               simpleExpression_();
                               expression_();
                               exprIterCommaExprLoop();
                               break;
            case(R_S_BRACKET): term_();
                               simpleExpression_();
                               expression_();
                               exprIterCommaExprLoop();
                               break;
            case(EQUAL): term_();
                         simpleExpression_();
                         expression_();
                         exprIterCommaExprLoop();
                         break;
            case(COMMA): term_();
                         simpleExpression_();
                         expression_();
                         exprIterCommaExprLoop();
                         break;
            case(PLUS): term_();
                        simpleExpression_();
                        expression_();
                        exprIterCommaExprLoop();
                        break;
            case(MINUS): term_();
                         simpleExpression_();
                         expression_();
                         exprIterCommaExprLoop();
                         break;
            case(DIFFERENT): term_();
                             simpleExpression_();
                             expression_();
                             exprIterCommaExprLoop();
                             break;
            case(LESS): term_();
                        simpleExpression_();
                        expression_();
                        exprIterCommaExprLoop();
                        break;
            case(LEQ): term_();
                       simpleExpression_();
                       expression_();
                       exprIterCommaExprLoop();
                       break;
            case(GREATER): term_();
                           simpleExpression_();
                           expression_();
                           exprIterCommaExprLoop();
                           break;
            case(GEQ): term_();
                       simpleExpression_();
                       expression_();
                       exprIterCommaExprLoop();
                       break;
            case(OU): term_();
                      simpleExpression_();
                      expression_();
                      exprIterCommaExprLoop();
                      break;
            case(MULT): term_();
                        simpleExpression_();
                        expression_();
                        exprIterCommaExprLoop();
                        break;
            case(DIVISION): term_();
                            simpleExpression_();
                            expression_();
                            exprIterCommaExprLoop();
                            break;
            case(DIV): term_();
                       simpleExpression_();
                       expression_();
                       exprIterCommaExprLoop();
                       break;
            case(E): term_();
                     simpleExpression_();
                     expression_();
                     exprIterCommaExprLoop();
                     break;
            default: simMistake();
            
        }
    }

    void expression_(){
        switch(this->token){
            case(R_C_BRACKET): break;
            case(R_S_BRACKET): break;
            case(SEMICOLON): break;
            case(COMMA): break;
            case(ENTAO): break;
            case(FACA): break;
            case(ATE): break;
            case(PASSO): break;
            case(EQUAL): eat(EQUAL);
                         simpleExpression();
                         expression_();
                         break;
            case(DIFFERENT): eat(DIFFERENT);
                             simpleExpression();
                             expression_();
                             break;
            case(LESS): eat(LESS);
                        simpleExpression();
                        expression_();
                        break;
            case(LEQ): eat(LEQ);
                       simpleExpression();
                       expression_(); 
                       break;
            case(GREATER): eat(GREATER);
                           simpleExpression();
                           expression_();
                           break;
            case(GEQ): eat(GEQ);
                       simpleExpression();
                       expression_();
                       break;
            default: simMistake();
            
        }
    }

    void simpleExpression_(){
        switch(this->token){
            case(R_C_BRACKET): break;
            case(R_S_BRACKET): break;
            case(SEMICOLON): break;
            case(EQUAL): break;
            case(COMMA): break;
            case(ATE): break;
            case(ENTAO): break;
            case(FACA): break;
            case(PASSO): break;
            case(DIFFERENT): break;
            case(LESS): break;
            case(LEQ): break;
            case(GREATER): break;
            case(GEQ): break;
            case(PLUS): eat(PLUS); 
                        term(); 
                        simpleExpression_(); 
                        break;
            case(MINUS): eat(MINUS);
                         term();
                         simpleExpression_();
                         break;
            case(OU): eat(OU); 
                      term(); 
                      simpleExpression_(); 
                      break;
            default: simMistake();
            
        }
    }

    void term_(){
        switch(this->token){
            case(SEMICOLON): break;
            case(R_C_BRACKET): break;
            case(R_S_BRACKET): break;
            case(EQUAL): break;
            case(COMMA): break;
            case(ENTAO): break;
            case(FACA): break;
            case(ATE): break;
            case(PASSO): break;
            case(PLUS): break;
            case(MINUS): break;
            case(DIFFERENT): break;
            case(LESS): break;
            case(LEQ): break;
            case(GREATER): break;
            case(GEQ): break;
            case(OU): break;
            case(MULT): eat(MULT);
                        factor();
                        term_();
                        break;
            case(DIVISION): eat(DIVISION);
                            factor();
                            term_();
                            break;
            case(DIV): eat(DIV);
                       factor();
                       term_();
                       break;
            case(E): eat(E);
                     factor();
                     term_();
                     break;
            default: simMistake();
            
        }
    }

    public:
    Automaton(int initialState){
        this->initialState = initialState;
        this->currentIndex = 0;
        this->input = input;
    }

    void Analyze(string input){
        this->currentIndex = 0;
        this->input = input;
        this->lineNo = 1;
        this->colNo = 1;

        advance();
        program();
    }
};