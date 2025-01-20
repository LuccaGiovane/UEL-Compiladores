#ifndef ALOCADOR_REGISTRADORES_H
#define ALOCADOR_REGISTRADORES_H

#include <vector>
#include <string>

struct RegistradorVirtual {
    int id;
    std::string nome;
    int inicio, fim;
};

/**
 * Determina se 'rv1' deve ser usado para spill em vez de 'rv2'.
 */
bool deve_fazer_spill(RegistradorVirtual rv1, RegistradorVirtual rv2);

/**
 * Retorna a posição para spill dentre as alocações ativas.
 */
int posicao_para_spill(const std::vector<RegistradorVirtual>& registrosVirtuais, const std::vector<int>& alocacoes);

#endif
