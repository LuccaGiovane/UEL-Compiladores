import sys
import json
import random

def parse_entries(alfabeto: str, estados: str, estados_finais: str) -> tuple[list[str], list[str], dict[str, str]]:
    """
    Converte as entradas de string para listas e dicionário. 
    - `alfabeto` é uma string separada por espaços.
    - `estados` pode ser uma lista separada por espaços ou um intervalo (e.g., '1-5').
    - `estados_finais` é uma lista de pares estado:token.
    """
    if not alfabeto:
        alfabeto = []
    else:
        alfabeto = alfabeto.split()
    
    if not estados:
        estados = []
    else:
        if "-" in estados:
            estados = estados.split("-")
            estados = [str(i) for i in range(int(estados[0]), int(estados[1]) + 1)]
        else:
            estados = estados.split()

    if not estados_finais:
        estados_finais = {}
    else:
        estados_finais = estados_finais.split()
        estados_tokens = {}

        for estado_token in estados_finais:
            estado, token = estado_token.split(":")
            estados_tokens.update({estado: token})

    return alfabeto, estados, estados_tokens

def cifra_de_cesar(estado: str, shift: int, estados: list[str]) -> str:
    """
    Aplica a cifra de César ao estado, deslocando o índice pelo valor de shift, e retornando o novo estado.
    """
    index = (estados.index(estado) + shift) % len(estados)
    return estados[index]

def generate_matrix(alfabeto: list[str], estados: list[str]) -> list[tuple[str, ...]]:
    """
    Gera a matriz de transição com base nas entradas do usuário. Cada célula da matriz representa uma transição de um estado a outro.
    """
    matrix = [['0'] * len(alfabeto) for _ in estados]

    print("="*25)
    print("\nGerar matriz de transição\n")
    print("Para cada estado representar as transições da seguinte maneira:\n")
    print("palavra=>estado\n")
    print("ou -1 para ir para o próximo estado\n")
    print("OBS: Apenas uma transição por linha\n")
    print("="*25)
    print("\n")

    for i, estado in enumerate(estados):
        print(f"{estado}\n")

        while (transicao := input("")) != "-1":
            palavra, estado_destino = transicao.strip().split("=>")

            palavra_index = alfabeto.index(palavra)
            estado_index = estados.index(estado)

            matrix[estado_index][palavra_index] = estado_destino

        print("="*25)
    
    return matrix

def randomize_matrix(matrix: list[tuple[str, ...]], estados: list[str]) -> list[tuple[str, ...]]:
    """
    Randomiza a matriz de transições aplicando um deslocamento de César aleatório para cada estado.
    """
    shift = random.randint(1, len(estados) - 1)
    randomized_matrix = [['0'] * len(matrix[0]) for _ in matrix]

    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if matrix[i][j] != '0':
                randomized_matrix[i][j] = cifra_de_cesar(matrix[i][j], shift, estados)
            else:
                randomized_matrix[i][j] = matrix[i][j]

    return randomized_matrix

def generate_txt(alfabeto: list[str], estados: list[str], estados_finais: dict[str, str], transitions: list[tuple[str, ...]]) -> None:
    """
    Gera arquivos de saída em formato de texto com as definições de autômato, incluindo alfabeto, estados, estados finais e transições.
    """
    with open("automato_cpp.txt", "w") as file:
        alfbt = '", "'.join(alfabeto)
        file.write(f'const std::string alfabeto [{len(alfabeto)}] {{"{alfbt}"}};\n')
        
        stds = '", "'.join(estados)
        file.write(f'\nconst std::string estados [{len(estados)}] {{"{stds}"}};\n')

        file.write("\nconst std::map<std::string, std::string> estados_finais {\n")
        for key, value in estados_finais.items():
            file.write(f'\t{{"{key}", "{value}"}},\n')
        file.write('};\n')

        file.write(f"\nconst std::string transicoes [{len(estados)}][{len(alfabeto)}] {{\n")
        file.write(f"//{' '*8}")
        for palavra in alfabeto:
            file.write(f"{palavra:^10}")
        file.write("\n")

        qtd = len(alfabeto)
        for estado, transicoes in zip(estados, transitions):
            file.write(f'/*{estado:^5}*/{{')
            
            for i, transicao in enumerate(transicoes):
                if i == qtd - 1:
                    break
                
                transicao = f'"{transicao}",'
                file.write(f'{transicao:^10}')
            
            transicao = f'"{transicoes[qtd-1]}"'
            file.write(f'{transicao:^10}}},\n')

        file.write("};\n")

    with open("lexico_cpp.txt", "w") as file:
        file.write("const int INVALID_STATE {-1};\n")
        file.write("const int START_STATE {0};\n")
        file.write("const std::map<std::string, int> tokens {\n")
        for i, token in enumerate(estados_finais.values(), start=1):
            token = f'"{token}"'
            file.write(f'\t{{{token}, {i}}},\n')
        file.write("};\n")

    with open("sintatico_cpp.txt", "w") as file:
        file.write("const int ")
        
        variaveis = []
        for i, token in enumerate(estados_finais.values(), start=1):
            variaveis.append(f"{token} = {i}")

        variaveis = ', '.join(variaveis)
        file.write(f"{variaveis};\n")

        file.write("const std::map<int, std::string> tokens {\n")
        for i, token in enumerate(estados_finais.values(), start=1):
            file.write("\t{")
            file.write(f'{i}, "{token.lower()}"')
            file.write("},\n")
        file.write("};\n")

if __name__ == "__main__":
    if len(sys.argv) == 1:
        print("Os valores devem ser fornecidos separados por um espaço em branco\n")
        alfabeto = input('Alfabeto:\n')
        estados = input('Estados (pode ser indicado por intervalo, ex: 1-15):\n')
        estados_finais = input('Estados Finais (Nome do estado:Token)\n')

        alfabeto, estados, estados_finais = parse_entries(alfabeto, estados, estados_finais)

        transitions = generate_matrix(alfabeto, estados)
        transitions = randomize_matrix(transitions, estados)

    else:
        file = sys.argv[1]
        
        with open(file, 'r') as f:
            data = json.load(f)

        alfabeto: list[str] = data["alfabeto"]
        estados: list[str] = data["estados"]
        estados_finais: dict[str, str] = data["estados_finais"]
        transicoes: dict[str, dict[str, str]] = data["transicoes"]

        if len(estados) == 1 and len(estados[0]) > 1 and '-' in estados[0]:
            start, end = estados[0].split("-")
            start = int(start)
            end = int(end)
            estados = [str(i) for i in range(start, end+1)]
        
        transitions = [['0'] * len(alfabeto) for _ in estados]

        for estado, conj_transicoes in transicoes.items():
            for palavra, estado_destino in conj_transicoes.items():
                transitions[estados.index(estado)][alfabeto.index(palavra)] = estado_destino

        transitions = randomize_matrix(transitions, estados)

    generate_txt(alfabeto, estados, estados_finais, transitions)
