<div align="center">
 <h1><b>🤘🏻 ⛧ Compiladores ⛧ 🤘🏻</b></h1><br><br>

 <a href="" target="_blank">![License](https://img.shields.io/badge/license-MIT-blue.svg)</a><br>
 ![C++](https://img.shields.io/badge/C%2B%2B-pink)
 ![C](https://img.shields.io/badge/C-grey)
 ![Flex](https://img.shields.io/badge/Flex-green)
 ![Bison](https://img.shields.io/badge/Bison-grey)
</div>

Este repositório contém os projetos realizados durante a disciplina de **Compiladores** no curso de Ciência da Computação da Universidade Estadual de Londrina. A disciplina está sendo cursada no **5º e 6º semestre** do curso, e os projetos são divididos em diferentes etapas, cada uma focada em aprender e aplicar técnicas de compilação e análise lexical, sintática e semântica.

## Estrutura do Repositório

A estrutura do repositório é organizada da seguinte maneira:
```bash
UEL-Compiladores/
│
├── README.md
│
├── 1 Semestre/
│   │
│   ├── Lexico/
│   │   ├── AnalisadorLexico.pdf
│   │   └── < T1 - léxico >
│   │
│   ├── Sintatico/
│   │   ├── AnalisadorSintatico.pdf
│   │   └── < T2 - sintático >
│   │
│   ├── Portugol/
│   │   ├── Portugol.pdf
│   │   └── < Portugol >
│   │
│   ├── Teoricos/
│   │   └── < Listas teóricas >
│   │
│   └── Praticos/
│       └── < Exercícios práticos >
│
└── 2 Semestre/
    │
    ├── DCMAT/
    │   ├── DCMAT.pdf
    │   └── < T1 - DCMAT >
    │
    ├── Regalloc/
    │   ├── Regalloc.pdf
    │   └── < T2 - Regalloc >
    │
    ├── LinearScan/
    │   ├── LinearScn.pdf
    │   └── < T3 - LinearScan >
    │
    ├── Gerador/
    │   ├── GeradorCodigo.pdf
    │   └── < Gerador de código >
    │
    ├── Teoricos/
    │   └── < Listas teóricas >
    │
    └── Praticos/
        └── < Exercícios práticos >
```


- **[1 Semestre](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre)**
  
  - [Lexico](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre/Lexico)
    <br>Utilizando Flex na linguagem C, foi implementado um analisador **léxico** para um subconjunto de tokens da linguagem C.
    [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/1%20Semestre/Lexico/AnalisadorLexico.pdf)]
   
  - [Sintatico](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre/Sintatico)
    <br>Utilizando a ferramenta Bison, foi implementado um analisador **sintatico** para um subconjunto da linguagem C.
    [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/1%20Semestre/Sintatico/AnalisadorSintatico.pdf)]
    
  - [Portugol](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre/Portugol)
    <br>Mini compilador para a pseudolinguagem **Portugol**.
    [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/1%20Semestre/Portugol/T1%20-%20Portugol.pdf)]

  - [Teoricos](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre/Teoricos)
    <br>Listas teóricas feitas durante o 1º semestre do curso.

  - [Praticos](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/1%20Semestre/Praticos)
    <br>Exercícios práticos feitos durante o 1º semestre do curso.

<br>

- **[2 Semestre](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre)**
  
   - [DCMAT](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/DCMAT)
     <br>Através do emprego de técnicas de construção de compiladores, o objetivo deste trabalho é desenvolver um simples software matemático, que seja capaz de gerar gráficos,
     resolver expressões, calcular integrais e somatórios além de realizar operações básicas com matrizes.
     [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/2%20Semestre/DCMAT/DCMAT.pdf)]
    
   - [Regalloc](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/Regalloc)
     <br>Programa que realiza a leitura de arquivos que contêm grafos de interferência e tenta alocar registradores através da técnica de coloração de grafos.
     [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/2%20Semestre/Regalloc/T2%20-%20RegAlloc.pdf)]

   - [Linear Scan](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/LinearScan)
     <br>Programa que realiza a leitura de arquivos que contêm uma lista de tempos de vida e tenta alocar registradores através da técnica de Linear Scan.
     [[documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/2%20Semestre/LinearScan/T3%20-%20LinearScan.pdf)]
 
   - [Gerador de Códigos](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/Gerador)
     <br>Implementação de um programa que recebe como entrada arquivos que contêm representações lineares de árvores sintáticas abstratas e gera o código *assembly* equivalente.
     [[Documentação](https://github.com/LuccaGiovane/UEL-Compiladores/blob/main/2%20Semestre/Gerador/GeradorCodigo.pdf)]
 
   - [Teoricos](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/Teoricos)
     <br>Listas teóricas feitas durante o 2º semestre do curso.
 
   - [Praticos](https://github.com/LuccaGiovane/UEL-Compiladores/tree/main/2%20Semestre/Praticos/Lista%2018)
     <br>Exercícios práticos feitos durante o 2º semestre do curso.


<br>
