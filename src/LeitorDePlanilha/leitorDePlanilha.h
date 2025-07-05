#ifndef LEITORDEPLANILHA_H
#define LEITORDEPLANILHA_H

#include <vector>
#include <string>
#include <functional>

using namespace std;

class LeitorDePlanilha {
    public:
        vector<vector<string>> lerCSV(const string& caminhoArquivo);
        string limparCampoCSV(const string &campo);
        int contadorCSV(const string &caminho);
        void processarCSV(const string& caminhoArquivo, const function<void(const vector<string>&)>& processaLinha);
};

#endif