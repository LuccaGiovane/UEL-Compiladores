#include <iostream>
#include <string>
#include <vector>

#include "utilitarios_string.h"
#include "alocador_registradores.h"

int main() {
    int posicao;
    std::string linha;
    std::vector<RegistradorVirtual> registrosVirtuais;
    std::vector<std::string> comando_dividido;
    std::vector<std::string> intervalo_dividido;
    int controlador = 0, numero_de_registradores = 0;

    while(std::getline(std::cin, linha)) {
        if(controlador == 0) {
            comando_dividido = separar(linha, "=");
            numero_de_registradores = std::atoi(comando_dividido[1].c_str());
        } else {
            comando_dividido = separar(linha, " --> ");
            intervalo_dividido = separar(comando_dividido[1], " ");

            registrosVirtuais.push_back(RegistradorVirtual());

            posicao = controlador - 1;
            registrosVirtuais[posicao].id = posicao;
            registrosVirtuais[posicao].nome = comando_dividido[0];
            registrosVirtuais[posicao].inicio = std::atoi(intervalo_dividido[0].c_str());
            registrosVirtuais[posicao].fim = std::atoi(intervalo_dividido[1].c_str());
        }
        controlador++;
    }

    // Inicializar registradores
    std::vector<int> registradores;
    for(RegistradorVirtual rv: registrosVirtuais) {
        registradores.push_back(-1);
    }

    std::vector<std::vector<int>> spills;
    for(int i = numero_de_registradores; i > 1; i--) {
        spills.push_back({});
    }

    std::vector<int> alocacoes;
    std::vector<int> regs;
    int tempo, local_livre, posicao_spill;
    size_t iteracao;
    
    for(int i = numero_de_registradores; i > 1; i--) {
        std::cout << "K = " << i << std::endl << std::endl;

        regs = registradores;
        alocacoes.clear();
        for(int j = 0; j < i; j++) {
            alocacoes.push_back(-1);
        }

        tempo = 1;
        iteracao = 0;
        local_livre = 0;
        
        for(RegistradorVirtual rv : registrosVirtuais) {
            while(rv.inicio != tempo) {
                tempo++;
            }

            local_livre = i;
            for(int j = alocacoes.size() - 1; j >= 0; j--) {
                if(alocacoes[j] == -1) {
                    local_livre = j;
                    continue;
                }
                if(registrosVirtuais[alocacoes[j]].fim <= tempo) {
                    alocacoes[j] = -1;
                    local_livre = j;
                }
            }

            if(local_livre == i) {
                posicao_spill = posicao_para_spill(registrosVirtuais, alocacoes);
                if(deve_fazer_spill(rv, registrosVirtuais[alocacoes[posicao_spill]])) {
                    regs[rv.id] = -1;
                } else {
                    regs[alocacoes[posicao_spill]] = -1;
                    regs[rv.id] = posicao_spill;
                    alocacoes[posicao_spill] = rv.id;
                }
                spills[numero_de_registradores - i].push_back(static_cast<int>(iteracao));
            } else {
                alocacoes[local_livre] = rv.id;
                regs[rv.id] = local_livre;
            }
            iteracao++;
        }

        for(size_t j = 0; j < regs.size(); j++) {
            std::cout << registrosVirtuais[j].nome << ": ";
            if(regs[j] == -1) {
                std::cout << "SPILL" << std::endl;
            } else {
                std::cout << regs[j] << std::endl;
            }
        }

        std::cout << "----------------------------------------" << std::endl;
    }

    std::cout << "----------------------------------------";
    for(int i = numero_de_registradores; i > 1; i--) {
        std::cout << std::endl << "K = " << i << ": ";
        if(spills[numero_de_registradores - i].size()) {
            std::cout << "SPILL on interation(s): " << spills[numero_de_registradores - i][0];
            for(size_t j = 1; j < spills[numero_de_registradores - i].size(); j++) {
                std::cout << ", " << spills[numero_de_registradores - i][j];
            }
        } else {
            std::cout << "Successful Allocation";
        }
    }

    return 0;
}
