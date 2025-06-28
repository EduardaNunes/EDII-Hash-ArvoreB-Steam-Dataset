#include <fstream>
#include <sstream>
#include "leitorDePlanilha.h"

using namespace std;

vector<vector<string>> LeitorDePlanilha::lerCSV(const string& caminhoArquivo) {
    ifstream arquivo(caminhoArquivo);
    vector<vector<string>> dados;
    string linha;

    if (!arquivo.is_open()) {
        throw runtime_error("Não foi possível abrir o arquivo: " + caminhoArquivo);
    }

    while (getline(arquivo, linha)) {
        vector<string> colunas;
        stringstream ss(linha);
        string valor;

        while (getline(ss, valor, ',')) {
            colunas.push_back(valor);
        }

        dados.push_back(colunas);
    }

    return dados;
}

int LeitorDePlanilha::contarJogadoresCSV(const string &caminho) {
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
