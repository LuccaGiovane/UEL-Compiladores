#include "alocador_registradores.h"

bool deve_fazer_spill(RegistradorVirtual rv1, RegistradorVirtual rv2) {
    int intervalo1, intervalo2;
    
    if(rv1.fim > rv2.fim) return true;
    
    if(rv1.fim == rv2.fim) {
        intervalo1 = rv1.fim - rv1.inicio;
        intervalo2 = rv2.fim - rv2.inicio;

        if(intervalo1 < intervalo2) return true;
        
        if(intervalo1 == intervalo2) {
            if(rv1.id > rv2.id) return true;
        }
    }

    return false;
}

int posicao_para_spill(const std::vector<RegistradorVirtual>& registrosVirtuais, const std::vector<int>& alocacoes) {
    size_t pos = 0;
    for(size_t i = 1; i < alocacoes.size(); i++) {
        if(deve_fazer_spill(registrosVirtuais[alocacoes[i]], registrosVirtuais[alocacoes[pos]])) {
            pos = i;
        }
    }

    return static_cast<int>(pos);
}
