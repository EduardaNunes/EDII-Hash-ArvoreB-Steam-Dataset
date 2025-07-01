#include <fstream>
#include <sstream>
#include "leitorDePlanilha.h"
#include <algorithm>

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

vector<vector<string>> LeitorDePlanilha::lerCSV(const string& caminhoArquivo) {
    ifstream arquivo(caminhoArquivo);
    vector<vector<string>> dados;
    string linha;

    if (!arquivo.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo: " + caminhoArquivo);
    }

    // Pula o cabeçalho
    getline(arquivo, linha);

    while (getline(arquivo, linha)) {
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

        if (!campo.empty() || linha.back() == ',') {
            colunas.push_back(limparCampoCSV(campo));
        }

        dados.push_back(colunas);
    }

    return dados;
}

int LeitorDePlanilha::contadorCSV(const string &caminho) {
    ifstream file(caminho);
    string line;
    int count = 0;

    getline(file, line);

    while (getline(file, line))
    {
        if (!line.empty())
            count++;
    }

    return count;
}