#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "leitorDePlanilha.h"

using namespace std;

string LeitorDePlanilha::limparCampoCSV(const string& campo) {
    
    string limpo;
    for (char c : campo) {
        if (c != '[' && c != ']' && c != '\'' && c != '"') {
            limpo += c;
        }
    }

    size_t inicio = limpo.find_first_not_of(" ");
    size_t fim = limpo.find_last_not_of(" ");

    return (inicio == string::npos) ? "" : limpo.substr(inicio, fim - inicio + 1);
}

int LeitorDePlanilha::contadorCSV(const string &caminho) {
    ifstream file(caminho);
    string line;
    int count = 0;

    getline(file, line);

    while (getline(file, line))
    {
        // Pular linhas totalmente vazias ou só com separadores
        if (line.find_first_not_of(", \t\r\n") == string::npos) {
            continue;
        }
        if (!line.empty())
            count++;
    }

    return count;
}

// Processa cada linha do CSV sem armazenar tudo em memória
void LeitorDePlanilha::processarCSV(const string& caminhoArquivo, const function<void(const vector<string>&)>& processaLinha) {

    ifstream arquivo(caminhoArquivo);
    string linha;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo!" << endl;
        throw runtime_error("Não foi possível abrir o arquivo: " + caminhoArquivo);
    }

    // Pula o cabeçalho
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {

        // Pular linhas totalmente vazias ou só com separadores
        if (linha.find_first_not_of(", \t\r\n") == string::npos) {
            continue;
        }

        vector<string> colunas;
        string campo;
        bool dentroDeAspas = false;

        for (size_t i = 0; i < linha.size(); ++i) {
            char c = linha[i];
            if (c == '"' || c == '\'') {
                dentroDeAspas = !dentroDeAspas;
                campo += c;
            }
            else if (c == ',' && !dentroDeAspas) {
                colunas.push_back(limparCampoCSV(campo));
                campo.clear();
            }
            else {
                campo += c;
            }
        }

        // Adiciona o último campo, se não estiver vazio
        if (!campo.empty() || (!linha.empty() && linha.back() == ',')) {
            colunas.push_back(limparCampoCSV(campo));
        }

        processaLinha(colunas);
    }
}