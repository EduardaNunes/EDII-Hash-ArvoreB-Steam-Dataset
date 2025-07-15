[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/jnYLGS_4)
# DCC012 - Estrutura de Dados II
## Sistema de Análise de Perfis de Jogadores 2025

### Descrição
Neste trabalho prático, você deverá desenvolver um sistema de análise e consulta de perfis de jogadores utilizando o dataset "Gaming Profiles 2025: Steam, PlayStation, Xbox". O objetivo é implementar estruturas eficientes de armazenamento e busca utilizando tabelas hash e árvores B para gerenciar um grande volume de dados de perfis de jogadores.

### Dataset
O dataset contém informações sobre perfis de jogadores nas plataformas Steam, PlayStation e Xbox. Você deverá baixar somente o dataset da steam no seguinte link: https://www.kaggle.com/datasets/artyomkruglov/gaming-profiles-2025-steam-playstation-xbox/data. 

### Membros do Grupo
Diego Pereira Betti

Vanessa Palmeira Kelmer Trajano

Eduarda Pereira Mourão Nunes

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
