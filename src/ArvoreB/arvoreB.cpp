#include <vector>
#include <string>
#include "arvoreB.h"
#include "noB.h"

using namespace std;

void ArvoreB::indexarJogos(){

}

void ArvoreB::indexarConquistas(){
    
}

void ArvoreB::insere(){
    
}

// Mudar depois de bool para o tipo de informação que será retornada
bool ArvoreB::busca(int chave){

    if(raiz->getChavesPreenchidas() == 0){
        return false;
    }

    return buscaAuxiliar(raiz, chave);
}

bool ArvoreB::buscaAuxiliar(NoB* no, int chave){

    int i = 0;
    vector<int> chaves = no->getChaves();
    int chavesPreenchidas = no->getChavesPreenchidas();
    
    while(i < chavesPreenchidas && chave > chaves[i]){
        
        if(chave == chaves[i]) return true;
        i++;

    }

    if(no->getEFolha()) return false;
    return buscaAuxiliar(no->getFilhos()[i], chave);
}

void ArvoreB::remove(){
    
}

int ArvoreB::getOrdem(){
    return ordem;
}

NoB* ArvoreB::getRaiz(){
    return raiz;
}