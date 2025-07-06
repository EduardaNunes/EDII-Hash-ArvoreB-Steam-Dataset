[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jnYLGS_4)
# DCC012 - Estrutura de Dados II
## Trabalho Prático 

### Membros do Grupo
Diego Pereira Betti / 202376037 / diego.pereira@estudante.ufjf.br

Vanessa Palmeira Kelmer Trajano / 202376035 / vanessa.trajano@estudante.ufjf.br

Eduarda Pereira Mourão Nunes / 202376015 / eduarda.nunes@estudante.ufjf.br

### - Manual de Uso do Sistema
Este manual detalha os passos necessários para compilar e executar o projeto

### - Requisitos para Compilação
Para compilar e executar este sistema em C++ no Windows, necessita-se de CMAKE, MinGW

### - Configuração do Ambiente
Certifique-se de adicionar o caminho do diretório bin do MinGW à variável de ambiente PATH do Windows. Isso permitirá que o sistema encontre o compilador g++ e outras ferramentas necessárias.

### - Estrutura Esperada do Projeto
O projeto está organizado em pastas padrão (src, build, etc.). Não é necessário alterar essa estrutura.

Arquivos de Dados
É crucial que os arquivos de dados (CSV) estejam localizados em uma pasta chamada steam na raiz do projeto. Por exemplo, se o seu projeto está em C:\MeuProjeto, os arquivos CSV devem estar em C:\MeuProjeto\steam.

# Comandos para compilação do código
mkdir build (caso ela nao exista)

cd build

cmake .. -G "MinGW Makefiles"

cmake --build .

meu_programa.exe

# 
