#ifndef LEITORDEPLANILHA_H
#define LEITORDEPLANILHA_H

#include <vector>
#include <string>

using namespace std;

class LeitorDePlanilha {
    public:
        vector<vector<string>> lerCSV(const string& caminhoArquivo);
        string limparCampoCSV(const string &campo);
        int contadorCSV(const string &caminho);
};

#endif 