// gerador.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <cctype>

using namespace std;

enum NodeType {
    CONSTANT,
    GLOBAL_VARIABLE,
    FUNCTION,
    RETURN_TYPE,
    PARAMETER,
    VARIABLE,
    IF,
    WHILE,
    DO_WHILE,
    FOR,
    PRINTF,
    SCANF,
    EXIT,
    RETURN,
    EXPRESSION,
    END_FUNCTION,
    UNKNOWN
};

struct ASTNode {
    NodeType type;
    string content;
    vector<ASTNode> children;
};

map<string, int> globalVariables;
map<string, int> constants;
map<string, string> stringLiterals;
int stringLiteralCount = 0;

stack<map<string, int>> localVariablesStack;
int localVariableCount = 0; // Para atribuir registradores a variáveis locais
int labelCount = 0;

// Variável global para armazenar o nome da função atual
string currentFunctionName;

string trim(const string& s) {
    size_t start = 0;
    while (start < s.length() && isspace(s[start])) {
        start++;
    }
    if (start == s.length()) {
        return "";
    }
    size_t end = s.length() - 1;
    while (end > start && isspace(s[end])) {
        end--;
    }
    return s.substr(start, end - start + 1);
}

NodeType getNodeType(const string& line) {
    string trimmedLine = trim(line);
    if (trimmedLine.find("CONSTANT:") == 0) return CONSTANT;
    if (trimmedLine.find("GLOBAL VARIABLE:") == 0) return GLOBAL_VARIABLE;
    if (trimmedLine.find("FUNCTION:") == 0) return FUNCTION;
    if (trimmedLine.find("RETURN_TYPE:") == 0) return RETURN_TYPE;
    if (trimmedLine.find("PARAMETER:") == 0) return PARAMETER;
    if (trimmedLine.find("VARIABLE:") == 0) return VARIABLE;
    if (trimmedLine.find("IF(") == 0) return IF;
    if (trimmedLine.find("WHILE(") == 0) return WHILE;
    if (trimmedLine.find("DO WHILE(") == 0) return DO_WHILE;
    if (trimmedLine.find("FOR(") == 0) return FOR;
    if (trimmedLine.find("PRINTF(") == 0) return PRINTF;
    if (trimmedLine.find("SCANF(") == 0) return SCANF;
    if (trimmedLine.find("EXIT(") == 0) return EXIT;
    if (trimmedLine.find("RETURN(") == 0 || trimmedLine == "RETURN") return RETURN;
    if (trimmedLine == "END_FUNCTION") return END_FUNCTION;
    return EXPRESSION;
}

void parseAST(vector<ASTNode>& ast) {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        string trimmedLine = trim(line);
        NodeType nodeType = getNodeType(trimmedLine);
        ASTNode node;
        node.type = nodeType;
        node.content = trimmedLine;
        ast.push_back(node);
    }
}

void generateDataSection() {
    cout << ".data" << endl;

    // Declarar variáveis globais
    for (const auto& var : globalVariables) {
        // Detectar se a variável é um array
        size_t bracketPos = var.first.find('[');
        if (bracketPos != string::npos) {
            string varName = var.first.substr(0, bracketPos);
            string sizeStr = var.first.substr(bracketPos + 1, var.first.find(']') - bracketPos - 1);
            int size = stoi(sizeStr);
            cout << varName << ": .space " << (size * 4) << endl; // Supondo que cada elemento é um int (4 bytes)
        } else {
            cout << var.first << ": .word 0" << endl;
        }
    }

    // Declarar constantes
    for (const auto& cnst : constants) {
        cout << cnst.first << ": .word " << cnst.second << endl;
    }

    // Declarar literais de string
    for (const auto& str : stringLiterals) {
        cout << str.first << ": .asciiz " << str.second << endl;
    }
    cout << endl;
}

string getNewStringLabel() {
    return "str" + to_string(stringLiteralCount++);
}

string getNewLabel(const string& base) {
    return base + "_" + to_string(labelCount++);
}

// Função auxiliar para obter o registrador ou posição de uma variável local
string getLocalVarLocation(const string& varName, stringstream& assemblyCode) {
    if (localVariablesStack.empty() || localVariablesStack.top().count(varName) == 0) {
        cerr << "Error: Undefined local variable '" << varName << "'" << endl;
        exit(1);
    }
    int regNum = localVariablesStack.top()[varName];
    if (regNum >= 0) {
        return "$s" + to_string(regNum);
    } else {
        int offset = regNum;
        string tempReg = "$t9"; // Registrador temporário para carregar do stack
        assemblyCode << "    lw " << tempReg << ", " << offset << "($fp)" << endl;
        return tempReg;
    }
}

// Função auxiliar para obter o registrador de uma variável global
string getGlobalVarRegister(const string& varName, stringstream& assemblyCode) {
    string tempReg = "$t9"; // Usando $t9 para carregar endereços de variáveis globais
    assemblyCode << "    la " << tempReg << ", " << varName << endl;
    return tempReg;
}

// Função para processar nós recursivamente
void processNode(const ASTNode& node, stringstream& assemblyCode);

// Classe Parser para analisar expressões em notação prefixa
class Parser {
public:
    Parser(const string& expr) : expr(expr), pos(0), tempRegCount(0) {}

    void parseExpression(string& resultReg, stringstream& assemblyCode) {
        parsePrefixExpr(resultReg, assemblyCode);
    }

private:
    string expr;
    size_t pos;
    int tempRegCount;

    void skipWhitespace() {
        while (pos < expr.size() && isspace(expr[pos])) {
            pos++;
        }
    }

    string getNextToken() {
        skipWhitespace();
        if (pos >= expr.size()) return "";

        if (expr[pos] == '(' || expr[pos] == ')' || expr[pos] == ',') {
            return string(1, expr[pos++]);
        }

        size_t start = pos;
        while (pos < expr.size() && (isalnum(expr[pos]) || expr[pos] == '_' || isOperatorChar(expr[pos]) || expr[pos] == '\'' || expr[pos] == '\"' || expr[pos] == '[' || expr[pos] == ']')) {
            pos++;
        }
        string token = expr.substr(start, pos - start);
        return token;
    }

    bool isOperatorChar(char c) {
        static const string opChars = "<>=!&|+-*/%~^";
        return opChars.find(c) != string::npos;
    }


    void expect(const string& expectedToken) {
        string token = getNextToken();
        if (token != expectedToken) {
            cerr << "Error: Expected '" << expectedToken << "', got '" << token << "'" << endl;
            exit(1);
        }
    }

    void parsePrefixExpr(string& resultReg, stringstream& assemblyCode) {
        skipWhitespace();
        if (pos >= expr.size()) {
            cerr << "Error: Unexpected end of expression" << endl;
            exit(1);
        }

        string token = getNextToken();

        if (token == "(") {
            // Lidar com expressões entre parênteses
            parsePrefixExpr(resultReg, assemblyCode);
            expect(")");
        } else if (isOperator(token)) {
            // Operador binário ou unário
            if (token == "++" || token == "--") {
                // Operadores unários de pré-incremento/decremento
                expect("(");
                string varName = getNextToken();
                expect(")");
                string varReg = getLocalVarLocation(varName, assemblyCode);
                if (token == "++") {
                    assemblyCode << "    addi " << varReg << ", " << varReg << ", 1" << endl;
                } else { // "--"
                    assemblyCode << "    addi " << varReg << ", " << varReg << ", -1" << endl;
                }
                resultReg = varReg;
            } else {
                // Operadores binários
                expect("(");
                string leftReg;
                parsePrefixExpr(leftReg, assemblyCode);
                expect(",");
                string rightReg;
                parsePrefixExpr(rightReg, assemblyCode);
                expect(")");
                string tempReg = getTempReg();
                generateOperation(token, leftReg, rightReg, tempReg, assemblyCode);
                resultReg = tempReg;
            }
        } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Valor imediato
            resultReg = getTempReg();
            assemblyCode << "    li " << resultReg << ", " << token << endl;
        } else if (isCharLiteral(token)) {
            // Literal de caractere
            resultReg = getTempReg();
            char c = parseCharLiteral(token);
            assemblyCode << "    li " << resultReg << ", " << int(c) << endl;
        } else if (isFunctionCall(token)) {
            // Chamada de função
            expect("(");
            vector<string> argRegs;
            if (expr[pos] != ')') {
                while (true) {
                    string argReg;
                    parsePrefixExpr(argReg, assemblyCode);
                    argRegs.push_back(argReg);
                    skipWhitespace();
                    if (pos < expr.size() && expr[pos] == ',') {
                        pos++; // Consumir ','
                    } else {
                        break;
                    }
                }
            }
            expect(")");
            // Gerar código para chamada de função
            generateFunctionCall(token, argRegs, resultReg, assemblyCode);
        } else if (isVariable(token)) {
            // Variável
            resultReg = getVariableRegister(token, assemblyCode);
        } else if (token.size() >= 2 && token[0] == '"' && token.back() == '"') {
            // Literal de string
            string strLabel = getNewStringLabel();
            stringLiterals[strLabel] = token;
            resultReg = getTempReg();
            assemblyCode << "    la " << resultReg << ", " << strLabel << endl;
        } else {
            cerr << "Error: Unexpected token '" << token << "'" << endl;
            exit(1);
        }
    }

    bool isUnaryOperator(const string& token) {
        static const set<string> unaryOperators = {
            "+", "-", "!", "~"
        };
        return unaryOperators.count(token) > 0;
    }

    void generateUnaryOperation(const string& op, const string& operandReg, const string& resultReg, stringstream& assemblyCode) {
        if (op == "-") {
            assemblyCode << "    neg " << resultReg << ", " << operandReg << endl;
        } else if (op == "!") {
            assemblyCode << "    seq " << resultReg << ", " << operandReg << ", $zero" << endl;
        } else if (op == "~") {
            assemblyCode << "    nor " << resultReg << ", " << operandReg << ", $zero" << endl;
        } else if (op == "+") {
            // Unary plus, result is the same as operand
            assemblyCode << "    move " << resultReg << ", " << operandReg << endl;
        } else {
            cerr << "Error: Unsupported unary operator '" << op << "'" << endl;
            exit(1);
        }
    }

    bool isVariable(const string& token) {
        // Verificar se é uma variável conhecida
        return localVariablesStack.top().count(token) > 0 || globalVariables.count(token) > 0 || constants.count(token) > 0;
    }

    bool isOperator(const string& token) {
        static const set<string> operators = {
            "&&", "||", "==", "!=", "<", ">", "<=", ">=", "+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>", "++", "--", "!"
        };
        return operators.count(token) > 0;
    }

    bool isFunctionCall(const string& token) {
        // Assumindo que se não é um operador ou uma variável, é uma função
        return !isOperator(token) && !isVariable(token);
    }

    bool isCharLiteral(const string& token) {
        return token.size() >= 3 && token[0] == '\'' && token.back() == '\'';
    }

    char parseCharLiteral(const string& token) {
        if (token.size() == 3) {
            return token[1];
        } else if (token.size() == 4 && token[1] == '\\') {
            // Lidar com sequências de escape como '\n', '\t', etc.
            switch (token[2]) {
                case 'n': return '\n';
                case 't': return '\t';
                case '\\': return '\\';
                case '\'': return '\'';
                default:
                    cerr << "Error: Unknown escape sequence '\\" << token[2] << "'" << endl;
                    exit(1);
            }
        } else {
            cerr << "Error: Invalid character literal '" << token << "'" << endl;
            exit(1);
        }
    }

    string getVariableRegister(const string& varName, stringstream& assemblyCode) {
        if (localVariablesStack.top().count(varName) > 0) {
            return getLocalVarLocation(varName, assemblyCode);
        } else if (globalVariables.count(varName) > 0) {
            // Para variáveis globais, carregar o endereço
            string tempReg = getTempReg();
            assemblyCode << "    la " << tempReg << ", " << varName << endl;
            assemblyCode << "    lw " << tempReg << ", 0(" << tempReg << ")" << endl;
            return tempReg;
        } else if (constants.count(varName) > 0) {
            string tempReg = getTempReg();
            assemblyCode << "    li " << tempReg << ", " << constants[varName] << endl;
            return tempReg;
        } else {
            cerr << "Error: Undefined variable '" << varName << "'" << endl;
            exit(1);
        }
    }

    void generateOperation(const string& op, const string& leftReg, const string& rightReg, const string& resultReg, stringstream& assemblyCode) {
        if (op == "+") {
            assemblyCode << "    add " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "-") {
            assemblyCode << "    sub " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "*") {
            assemblyCode << "    mul " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "/") {
            assemblyCode << "    div " << leftReg << ", " << rightReg << endl;
            assemblyCode << "    mflo " << resultReg << endl;
        } else if (op == "%") {
            assemblyCode << "    div " << leftReg << ", " << rightReg << endl;
            assemblyCode << "    mfhi " << resultReg << endl;
        } else if (op == "<") {
            assemblyCode << "    slt " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == ">") {
            assemblyCode << "    slt " << resultReg << ", " << rightReg << ", " << leftReg << endl;
        } else if (op == "<=") {
            assemblyCode << "    slt " << resultReg << ", " << rightReg << ", " << leftReg << endl;
            assemblyCode << "    xori " << resultReg << ", " << resultReg << ", 1" << endl;
        } else if (op == ">=") {
            assemblyCode << "    slt " << resultReg << ", " << leftReg << ", " << rightReg << endl;
            assemblyCode << "    xori " << resultReg << ", " << resultReg << ", 1" << endl;
        } else if (op == "==") {
            assemblyCode << "    seq " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "!=") {
            assemblyCode << "    sne " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "&&") {
            assemblyCode << "    and " << resultReg << ", " << leftReg << ", " << rightReg << endl;
            assemblyCode << "    sne " << resultReg << ", " << resultReg << ", $zero" << endl;
        } else if (op == "||") {
            assemblyCode << "    or " << resultReg << ", " << leftReg << ", " << rightReg << endl;
            assemblyCode << "    sne " << resultReg << ", " << resultReg << ", $zero" << endl;
        } else if (op == "&") {
            assemblyCode << "    and " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "|") {
            assemblyCode << "    or " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "^") {
            assemblyCode << "    xor " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "<<") {
            assemblyCode << "    sllv " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == ">>") {
            assemblyCode << "    srlv " << resultReg << ", " << leftReg << ", " << rightReg << endl;
        } else if (op == "!") {
            assemblyCode << "    seq " << resultReg << ", " << leftReg << ", $zero" << endl;
        } else {
            cerr << "Error: Unsupported operator '" << op << "'" << endl;
            exit(1);
        }
    }

    void generateFunctionCall(const string& functionName, const vector<string>& argRegs, string& resultReg, stringstream& assemblyCode) {
        // Mover argumentos para $a0-$a3
        for (size_t i = 0; i < argRegs.size() && i < 4; ++i) {
            assemblyCode << "    move $a" << i << ", " << argRegs[i] << endl;
        }
        // Chamar a função
        assemblyCode << "    jal " << functionName << endl;
        // O valor de retorno está em $v0
        resultReg = getTempReg();
        assemblyCode << "    move " << resultReg << ", $v0" << endl;
    }

    string getTempReg() {
        if (tempRegCount >= 10) {
            tempRegCount = 0; // Resetar contagem se exceder
        }
        return "$t" + to_string(tempRegCount++);
    }
};

void evaluateCondition(const string& condition, stringstream& assemblyCode) {
    Parser parser(condition);
    string resultReg;
    parser.parseExpression(resultReg, assemblyCode);
    // O resultado da condição está em resultReg
    assemblyCode << "    move $t0, " << resultReg << endl;
}

// Função para dividir múltiplas instruções separadas por ponto e vírgula
vector<string> splitStatements(const string& code) {
    vector<string> statements;
    int parenCount = 0;
    size_t lastPos = 0;
    for (size_t i = 0; i < code.length(); ++i) {
        if (code[i] == '(') {
            parenCount++;
        } else if (code[i] == ')') {
            parenCount--;
        } else if (code[i] == ';' && parenCount == 0) {
            statements.push_back(code.substr(lastPos, i - lastPos));
            lastPos = i + 1;
        }
    }
    if (lastPos < code.length()) {
        statements.push_back(code.substr(lastPos));
    }
    return statements;
}

void generateAssembly(const vector<ASTNode>& ast) {
    // Stringstreams para coletar o código assembly
    stringstream assemblyCode;
    stringstream mainFunctionCode;
    vector<stringstream> otherFunctionsCode;

    // Processar os nós da AST
    for (size_t i = 0; i < ast.size(); ++i) {
        const ASTNode& node = ast[i];
        if (node.type == FUNCTION) {
            // Começar a coletar o código da função
            string functionName = node.content.substr(node.content.find(":") + 1);
            functionName = trim(functionName);

            // Usar um novo stringstream para cada função
            stringstream functionCode;

            // Processar os nós da função
            currentFunctionName = functionName;
            localVariablesStack.push(map<string, int>());
            localVariableCount = 0; // Resetar para cada função

            // Prólogo da função
            functionCode << ".globl " << functionName << endl;
            functionCode << functionName << ":" << endl;
            functionCode << "    # Function prologue" << endl;
            functionCode << "    addi $sp, $sp, -40" << endl;
            functionCode << "    sw $fp, 40($sp)" << endl;
            functionCode << "    sw $ra, 36($sp)" << endl;
            for (int regNum = 0; regNum <= 7; ++regNum) {
                functionCode << "    sw $s" << regNum << ", " << (32 - regNum * 4) << "($sp)" << endl;
            }
            functionCode << "    addi $fp, $sp, 40" << endl;

            // Processar o resto da função
            size_t j = i + 1;
            for (; j < ast.size() && ast[j].type != END_FUNCTION; ++j) {
                const ASTNode& funcNode = ast[j];
                switch (funcNode.type) {
                    case RETURN_TYPE:
                        // Ignorar tipo de retorno ou armazenar se necessário
                        break;
                    case PARAMETER:
                    case VARIABLE:
                        // Processar parâmetros e variáveis
                        processNode(funcNode, functionCode);
                        break;
                    case EXPRESSION:
                    case IF:
                    case WHILE:
                    case DO_WHILE:
                    case FOR:
                    case PRINTF:
                    case SCANF:
                    case RETURN:
                    case EXIT:
                        // Processar demais tipos de nós
                        processNode(funcNode, functionCode);
                        break;
                    default:
                        cerr << "Error: Unsupported node type in function " << functionName << endl;
                        exit(1);
                        break;
                }
            }

            // Epílogo da função
            functionCode << "    # Function epilogue" << endl;
            for (int regNum = 0; regNum <= 7; ++regNum) {
                functionCode << "    lw $s" << regNum << ", " << (32 - regNum * 4) << "($sp)" << endl;
            }
            functionCode << "    lw $ra, 36($sp)" << endl;
            functionCode << "    lw $fp, 40($sp)" << endl;
            functionCode << "    addi $sp, $sp, 40" << endl;
            functionCode << "    jr $ra" << endl;

            // Desempilhar variáveis locais
            localVariablesStack.pop();

            // Decidir onde colocar o código da função
            if (functionName == "main") {
                mainFunctionCode << functionCode.str();
            } else {
                otherFunctionsCode.push_back(std::move(functionCode));
            }

            // Mover para o próximo nó após END_FUNCTION
            i = j;
        } else if (node.type == CONSTANT || node.type == GLOBAL_VARIABLE) {
            // Processar constantes e variáveis globais
            switch (node.type) {
                case CONSTANT: {
                    // Processar constantes
                    stringstream ss(node.content);
                    string temp, name, temp2, valueStr;
                    ss >> temp >> name >> temp2 >> valueStr;
                    int value = stoi(valueStr);
                    constants[name] = value;
                    break;
                }
                case GLOBAL_VARIABLE: {
                    // Processar variáveis globais
                    stringstream ss(node.content);
                    string temp, temp2, name, temp3, typeStr;
                    ss >> temp >> temp2 >> name >> temp3 >> typeStr;
                    globalVariables[name] = 0;
                    break;
                }
                default:
                    break;
            }
        }
    }

    // Primeiro, imprimir a seção .text
    cout << ".text" << endl;

    // Imprimir o código assembly da função main
    cout << mainFunctionCode.str();

    // Em seguida, imprimir o código assembly das outras funções
    for (const auto& funcCode : otherFunctionsCode) {
        cout << funcCode.str();
    }

    // Em seguida, imprimir a seção .data
    generateDataSection();
}

void processNode(const ASTNode& node, stringstream& assemblyCode) {
    switch (node.type) {
        case PARAMETER: {
            // PARAMETER: m TYPE: int
            stringstream ss(node.content);
            string temp, name, temp2, typeStr;
            ss >> temp >> name >> temp2 >> typeStr;
            // Alocar variável local nos registradores $s
            int regNum = localVariableCount++;
            if (regNum <= 7) {
                localVariablesStack.top()[name] = regNum;
                // Mover parâmetro de $a0-$a3 para $s registradores
                assemblyCode << "    move $s" << regNum << ", $a" << regNum << "   # Move parameter " << name << endl;
            } else {
                // Alocar na stack
                int stackOffset = -(regNum - 7) * 4 - 40; // Ajuste do offset
                localVariablesStack.top()[name] = stackOffset;
                // Mover parâmetro de $a0-$a3 para stack
                assemblyCode << "    sw $a" << regNum << ", " << stackOffset << "($fp)" << "   # Move parameter " << name << endl;
            }
            break;
        }
        case VARIABLE: {
            // VARIABLE: x TYPE: int
            stringstream ss(node.content);
            string temp, name, temp2, typeStr;
            ss >> temp >> name >> temp2 >> typeStr;
            // Alocar variável local nos registradores $s
            int regNum = localVariableCount++;
            if (regNum <= 7) {
                localVariablesStack.top()[name] = regNum;
                // Inicializar variável com zero
                assemblyCode << "    li $s" << regNum << ", 0" << "   # Initialize " << name << endl;
            } else {
                // Alocar na stack
                int stackOffset = -(regNum - 7) * 4 - 40; // Ajuste do offset
                localVariablesStack.top()[name] = stackOffset;
                // Inicializar variável com zero
                assemblyCode << "    li $t9, 0" << endl;
                assemblyCode << "    sw $t9, " << stackOffset << "($fp)" << "   # Initialize " << name << endl;
            }
            break;
        }
        case PRINTF: {
            // Implementação do PRINTF
            string content = node.content;
            size_t start = content.find_first_of('(');
            size_t end = content.find_last_of(')');
            string argsFull = content.substr(start + 1, end - start - 1);

            // Extrair string de formato e argumentos
            stringstream ss(argsFull);
            string formatStr;
            getline(ss, formatStr, ',');

            // Remover espaços e aspas da string de formato
            formatStr = trim(formatStr);
            size_t firstQuote = formatStr.find_first_of('"');
            size_t lastQuote = formatStr.find_last_of('"');
            if (firstQuote == string::npos || lastQuote == string::npos || lastQuote <= firstQuote) {
                cerr << "Error: Invalid format string in PRINTF." << endl;
                exit(1);
            }
            string formatLiteral = formatStr.substr(firstQuote + 1, lastQuote - firstQuote - 1); // Remover aspas

            // Extrair argumentos adicionais
            vector<string> argsList;
            string arg;
            while (getline(ss, arg, ',')) {
                argsList.push_back(trim(arg));
            }

            // Dividir a string de formato em partes separadas por '%d'
            vector<string> formatParts;
            size_t pos = 0;
            size_t specPos;
            while ((specPos = formatLiteral.find("%d", pos)) != string::npos) {
                formatParts.push_back(formatLiteral.substr(pos, specPos - pos));
                formatParts.push_back("%d");
                pos = specPos + 2;
            }
            formatParts.push_back(formatLiteral.substr(pos));

            // Verificar se o número de especificadores '%d' corresponde ao número de argumentos
            size_t numSpecifiers = count(formatParts.begin(), formatParts.end(), "%d");
            if (numSpecifiers != argsList.size()) {
                cerr << "Error: Mismatch between number of format specifiers and arguments in PRINTF." << endl;
                exit(1);
            }

            // Gerar código para imprimir cada parte
            int argIndex = 0;
            for (const string& part : formatParts) {
                if (part == "%d") {
                    // Imprimir inteiro
                    string argName = argsList[argIndex++];
                    Parser parser(argName);
                    string exprReg;
                    parser.parseExpression(exprReg, assemblyCode);
                    assemblyCode << "    move $a0, " << exprReg << endl;
                    assemblyCode << "    li $v0, 1" << endl;
                    assemblyCode << "    syscall" << endl;
                } else if (!part.empty()) {
                    // Imprimir string
                    string strLabel = getNewStringLabel();
                    stringLiterals[strLabel] = "\"" + part + "\"";
                    assemblyCode << "    la $a0, " << strLabel << endl;
                    assemblyCode << "    li $v0, 4" << endl;
                    assemblyCode << "    syscall" << endl;
                }
            }

            break;
        }
        case SCANF: {
            // Implementação do SCANF
            string content = node.content;
            size_t start = content.find_first_of('(');
            size_t end = content.find_last_of(')');
            string args = content.substr(start + 1, end - start - 1);

            // Extrair string de formato (ignoramos para entrada de inteiro)
            size_t commaPos = args.find(',');
            if (commaPos == string::npos) {
                cerr << "Error: Invalid SCANF format." << endl;
                exit(1);
            }

            // Extrair a parte da variável
            string varPart = args.substr(commaPos + 1);
            // Remover espaços em branco
            varPart.erase(remove(varPart.begin(), varPart.end(), ' '), varPart.end());

            // Remover caracteres especiais
            size_t varNameStart = 0;
            while (varNameStart < varPart.size() && (varPart[varNameStart] == '&' || varPart[varNameStart] == '(')) {
                varNameStart++;
            }

            size_t varNameEnd = varPart.size() - 1;
            while (varNameEnd >= varNameStart && varPart[varNameEnd] == ')') {
                varNameEnd--;
            }

            if (varNameStart > varNameEnd) {
                cerr << "Error: Invalid variable name in SCANF." << endl;
                exit(1);
            }

            string varName = varPart.substr(varNameStart, varNameEnd - varNameStart + 1);

            assemblyCode << "    # SCANF statement" << endl;
            assemblyCode << "    li $v0, 5" << endl; // Ler inteiro
            assemblyCode << "    syscall" << endl;
            // Armazenar entrada na variável
            string reg = getLocalVarLocation(varName, assemblyCode);
            assemblyCode << "    move " << reg << ", $v0" << endl;
            break;
        }
        case IF: {
            // IF(condition, then_part, else_part)
            string content = node.content;

            assemblyCode << "    # IF statement" << endl;

            // Extrair condition, then_part, e else_part
            size_t start = content.find('(') + 1;
            size_t end = content.rfind(')');
            string args = content.substr(start, end - start);

            // Encontrar a vírgula que separa condition de then_part
            int parenCount = 0;
            size_t commaPos = 0;
            for (size_t i = 0; i < args.length(); ++i) {
                if (args[i] == '(') parenCount++;
                else if (args[i] == ')') parenCount--;
                else if (args[i] == ',' && parenCount == 0) {
                    commaPos = i;
                    break;
                }
            }

            if (commaPos == 0) {
                cerr << "Error parsing IF statement." << endl;
                exit(1);
            }

            string condition = args.substr(0, commaPos);
            string rest = args.substr(commaPos + 1);

            // Encontrar a vírgula que separa then_part de else_part
            parenCount = 0;
            size_t commaPos2 = string::npos;
            for (size_t i = 0; i < rest.length(); ++i) {
                if (rest[i] == '(') parenCount++;
                else if (rest[i] == ')') parenCount--;
                else if (rest[i] == ',' && parenCount == 0) {
                    commaPos2 = i;
                    break;
                }
            }

            string thenPart, elsePart;
            if (commaPos2 != string::npos) {
                thenPart = rest.substr(0, commaPos2);
                elsePart = rest.substr(commaPos2 + 1);
            } else {
                thenPart = rest;
                elsePart = "";
            }

            // Avaliar condição
            evaluateCondition(condition, assemblyCode);

            string elseLabel = getNewLabel("else");
            string endifLabel = getNewLabel("endif");

            assemblyCode << "    beqz $t0, " << elseLabel << endl;

            // Parte 'Then'
            assemblyCode << "    # Then part" << endl;
            vector<string> thenStatements = splitStatements(thenPart);
            for (const string& stmt : thenStatements) {
                ASTNode stmtNode;
                stmtNode.type = getNodeType(trim(stmt));
                stmtNode.content = trim(stmt);
                processNode(stmtNode, assemblyCode);
            }

            // Adicionar 'j' para 'endifLabel' apenas se houver um bloco 'else'
            if (!elsePart.empty()) {
                assemblyCode << "    j " << endifLabel << endl;
            }

            // Parte 'Else'
            assemblyCode << elseLabel << ":" << endl;
            if (!elsePart.empty()) {
                assemblyCode << "    # Else part" << endl;
                vector<string> elseStatements = splitStatements(elsePart);
                for (const string& stmt : elseStatements) {
                    ASTNode stmtNode;
                    stmtNode.type = getNodeType(trim(stmt));
                    stmtNode.content = trim(stmt);
                    processNode(stmtNode, assemblyCode);
                }

                assemblyCode << endifLabel << ":" << endl;
            }

            break;
        }
        case WHILE: {
            // WHILE(condition, body)
            string content = node.content;

            assemblyCode << "    # WHILE loop" << endl;

            // Extrair condition e body
            size_t start = content.find('(') + 1;
            size_t end = content.rfind(')');
            string args = content.substr(start, end - start);

            // Encontrar a vírgula que separa condition de body
            int parenCount = 0;
            size_t commaPos = 0;
            for (size_t i = 0; i < args.length(); ++i) {
                if (args[i] == '(') parenCount++;
                else if (args[i] == ')') parenCount--;
                else if (args[i] == ',' && parenCount == 0) {
                    commaPos = i;
                    break;
                }
            }

            if (commaPos == 0) {
                cerr << "Error parsing WHILE statement." << endl;
                exit(1);
            }

            string condition = args.substr(0, commaPos);
            string body = args.substr(commaPos + 1);

            string loopStartLabel = getNewLabel("while_start");
            string loopEndLabel = getNewLabel("while_end");

            assemblyCode << loopStartLabel << ":" << endl;

            // Avaliar condição
            evaluateCondition(condition, assemblyCode);

            // Se a condição for falsa, pula para o fim do loop
            assemblyCode << "    beqz $t0, " << loopEndLabel << endl;

            // Dividir o corpo em múltiplas instruções
            vector<string> statements = splitStatements(body);
            for (const string& stmt : statements) {
                ASTNode stmtNode;
                stmtNode.type = getNodeType(trim(stmt));
                stmtNode.content = trim(stmt);
                processNode(stmtNode, assemblyCode);
            }

            // Pular de volta para o início do loop
            assemblyCode << "    j " << loopStartLabel << endl;

            // Fim do loop
            assemblyCode << loopEndLabel << ":" << endl;

            break;
        }
        case DO_WHILE: {
            // DO_WHILE(body, condition)
            string content = node.content;

            assemblyCode << "    # DO_WHILE loop" << endl;

            // Extrair body e condition
            size_t start = content.find('(') + 1;
            size_t end = content.rfind(')');
            string args = content.substr(start, end - start);

            // Encontrar a vírgula que separa body de condition
            int parenCount = 0;
            size_t commaPos = 0;
            for (size_t i = 0; i < args.length(); ++i) {
                if (args[i] == '(') parenCount++;
                else if (args[i] == ')') parenCount--;
                else if (args[i] == ',' && parenCount == 0) {
                    commaPos = i;
                    break;
                }
            }

            if (commaPos == 0) {
                cerr << "Error parsing DO_WHILE statement." << endl;
                exit(1);
            }

            string body = args.substr(0, commaPos);
            string condition = args.substr(commaPos + 1);

            string loopStartLabel = getNewLabel("do_while_start");
            string loopEndLabel = getNewLabel("do_while_end");

            assemblyCode << loopStartLabel << ":" << endl;

            // Dividir o corpo em múltiplas instruções
            vector<string> statements = splitStatements(body);
            for (const string& stmt : statements) {
                ASTNode stmtNode;
                stmtNode.type = getNodeType(trim(stmt));
                stmtNode.content = trim(stmt);
                processNode(stmtNode, assemblyCode);
            }

            // Avaliar condição
            evaluateCondition(condition, assemblyCode);

            // Se a condição for verdadeira, pula para o início do loop
            assemblyCode << "    bnez $t0, " << loopStartLabel << endl;

            // Fim do loop
            assemblyCode << loopEndLabel << ":" << endl;

            break;
        }
        case FOR: {
            // FOR(init, condition, increment, body)
            string content = node.content;

            assemblyCode << "    # FOR loop" << endl;

            // Extrair init, condition, increment e body
            size_t start = content.find('(') + 1;
            size_t end = content.rfind(')');
            string args = content.substr(start, end - start);

            // Encontrar as vírgulas que separam os parâmetros
            vector<string> parts;
            int parenCount = 0;
            size_t lastPos = 0;
            for (size_t i = 0; i < args.length(); ++i) {
                if (args[i] == '(') parenCount++;
                else if (args[i] == ')') parenCount--;
                else if (args[i] == ',' && parenCount == 0) {
                    parts.push_back(args.substr(lastPos, i - lastPos));
                    lastPos = i + 1;
                }
            }
            parts.push_back(args.substr(lastPos));

            if (parts.size() != 4) {
                cerr << "Error parsing FOR statement." << endl;
                exit(1);
            }

            string init = trim(parts[0]);
            string condition = trim(parts[1]);
            string increment = trim(parts[2]);
            string body = trim(parts[3]);

            string loopStartLabel = getNewLabel("for_start");
            string loopEndLabel = getNewLabel("for_end");

            // Inicialização
            ASTNode initNode;
            initNode.type = getNodeType(trim(init));
            initNode.content = trim(init);
            processNode(initNode, assemblyCode);

            assemblyCode << loopStartLabel << ":" << endl;

            // Avaliar condição
            evaluateCondition(condition, assemblyCode);

            // Se a condição for falsa, pula para o fim do loop
            assemblyCode << "    beqz $t0, " << loopEndLabel << endl;

            // Dividir o corpo em múltiplas instruções
            vector<string> bodyStatements = splitStatements(body);
            for (const string& stmt : bodyStatements) {
                ASTNode bodyNode;
                bodyNode.type = getNodeType(trim(stmt));
                bodyNode.content = trim(stmt);
                processNode(bodyNode, assemblyCode);
            }

            // Incremento
            ASTNode incrNode;
            incrNode.type = getNodeType(trim(increment));
            incrNode.content = trim(increment);
            processNode(incrNode, assemblyCode);

            // Pular de volta para o início do loop
            assemblyCode << "    j " << loopStartLabel << endl;

            // Fim do loop
            assemblyCode << loopEndLabel << ":" << endl;

            break;
        }
        case EXPRESSION: {
            // Expressão de atribuição, ex: =(i,0);
            string content = node.content;
            // Remover o ponto e vírgula no final, se existir
            if (!content.empty() && content.back() == ';') {
                content.pop_back();
            }
            // Atribuição é representada por = (var, expr)
            size_t eqPos = content.find('=');
            if (eqPos == string::npos || content[eqPos + 1] != '(') {
                // Pode ser uma chamada de função sem atribuição, ex: quicksort(m,j)
                size_t funcNameEnd = content.find('(');
                if (funcNameEnd == string::npos) {
                    cerr << "Error: Invalid expression '" << content << "'" << endl;
                    exit(1);
                }
                string funcName = trim(content.substr(0, funcNameEnd));
                string args = content.substr(funcNameEnd + 1, content.find(')', funcNameEnd) - funcNameEnd - 1);
                // Parsear os argumentos
                vector<string> argRegs;
                stringstream ss(args);
                string arg;
                while (getline(ss, arg, ',')) {
                    arg = trim(arg);
                    Parser parser(arg);
                    string exprReg;
                    parser.parseExpression(exprReg, assemblyCode);
                    argRegs.push_back(exprReg);
                }
                // Gerar chamada de função
                string resultReg; // Nenhum resultado necessário
                // Mover argumentos para $a0-$a3
                for (size_t i = 0; i < argRegs.size() && i < 4; ++i) {
                    assemblyCode << "    move $a" << i << ", " << argRegs[i] << endl;
                }
                // Chamar a função
                assemblyCode << "    jal " << funcName << endl;
                // Ignorar o valor de retorno se não for usado
                break;
            }
            size_t start = eqPos + 2; // Após "=("
            size_t commaPos = content.find(',', start);
            if (commaPos == string::npos) {
                cerr << "Error: Invalid assignment expression '" << content << "'" << endl;
                exit(1);
            }
            string varName = trim(content.substr(start, commaPos - start));
            string expr = trim(content.substr(commaPos + 1, content.find(')', commaPos) - commaPos - 1));

            // Parsear a expressão da direita
            Parser parser(expr);
            string exprReg;
            parser.parseExpression(exprReg, assemblyCode);

            // Obter o registrador da variável de destino
            // Verificar se é uma variável global ou local
            if (localVariablesStack.top().count(varName) > 0) {
                int regNum = localVariablesStack.top()[varName];
                if (regNum >= 0) {
                    string varReg = "$s" + to_string(regNum);
                    assemblyCode << "    move " << varReg << ", " << exprReg << "   # Assign " << varName << endl;
                } else {
                    int offset = regNum;
                    assemblyCode << "    sw " << exprReg << ", " << offset << "($fp)" << "   # Assign " << varName << endl;
                }
            } else if (globalVariables.count(varName) > 0) {
                // Para variáveis globais, armazenar na memória
                string addrReg = getGlobalVarRegister(varName, assemblyCode);
                assemblyCode << "    sw " << exprReg << ", 0(" << addrReg << ")   # Assign " << varName << endl;
            } else {
                cerr << "Error: Undefined variable '" << varName << "'" << endl;
                exit(1);
            }

            break;
        }
        case RETURN: {
            // Implementação do RETURN
            assemblyCode << "    # Return statement" << endl;

            // Extrair a expressão de retorno, se houver
            string content = node.content;
            size_t start = content.find_first_of('(');
            size_t end = content.find_last_of(')');
            if (start != string::npos && end != string::npos && end > start) {
                string returnExpr = content.substr(start + 1, end - start - 1);
                Parser parser(returnExpr);
                string exprReg;
                parser.parseExpression(exprReg, assemblyCode);
                assemblyCode << "    move $v0, " << exprReg << endl;
            }

            // Epílogo da função
            if (currentFunctionName != "main") {
                assemblyCode << "    # Function epilogue" << endl;
                for (int regNum = 0; regNum <= 7; ++regNum) {
                    assemblyCode << "    lw $s" << regNum << ", " << (32 - regNum * 4) << "($sp)" << endl;
                }
                assemblyCode << "    lw $ra, 36($sp)" << endl;
                assemblyCode << "    lw $fp, 40($sp)" << endl;
                assemblyCode << "    addi $sp, $sp, 40" << endl;
                assemblyCode << "    jr $ra" << endl;
            } else {
                assemblyCode << "    # Main function epilogue" << endl;
                assemblyCode << "    lw $fp, 40($sp)" << endl;
                assemblyCode << "    addi $sp, $sp, 40" << endl;
                assemblyCode << "    li $v0, 10" << endl;
                assemblyCode << "    syscall" << endl;
            }
            break;
        }
        case EXIT: {
            // Implementação do EXIT
            // Extrair o argumento, mas como MIPS syscall 10 não usa argumentos, vamos ignorá-lo
            string content = node.content;
            size_t start = content.find('(') + 1;
            size_t end = content.find_last_of(')');
            if (start == string::npos || end == string::npos || end <= start) {
                cerr << "Error: Invalid EXIT syntax '" << content << "'" << endl;
                exit(1);
            }
            string expr = trim(content.substr(start, end - start -1));
            // Opcional: Avaliar a expressão e imprimir antes de sair
            // Mas como MIPS não suporta exit com código, apenas sair
            assemblyCode << "    li $v0, 10" << endl;
            assemblyCode << "    syscall" << endl;
            break;
        }
        case CONSTANT:
        case GLOBAL_VARIABLE:
        case RETURN_TYPE:
        case END_FUNCTION:
            // Já foram tratados em parseAST ou generateAssembly
            break;
        default:
            cerr << "Error: Unsupported node type during processing." << endl;
            exit(1);
            break;
    }
}


int main() {
    vector<ASTNode> ast;
    parseAST(ast);
    generateAssembly(ast);
    return 0;
}