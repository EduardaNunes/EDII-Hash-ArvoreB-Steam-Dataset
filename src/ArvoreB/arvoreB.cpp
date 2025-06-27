#include <vector>
#include <string>
#include "arvoreB.h"
#include "noB.h"

using namespace std;

ArvoreB::ArvoreB(int ordem){
    raiz = new NoB(ordem, true); 
}

void ArvoreB::indexarJogos(){

}

void ArvoreB::indexarConquistas(){
    
}

void ArvoreB::insere(int chave){

    if(raiz->eFolha){
        raiz->addChave(chave);
        return;
    }






}

// Mudar depois de bool para o tipo de informação que será retornada
bool ArvoreB::busca(int chave){

    if(raiz->chavesPreenchidas == 0){
        return false;
    }

    return buscaAuxiliar(raiz, chave);
}

bool ArvoreB::buscaAuxiliar(NoB* no, int chave){

    int i = 0;
    
    while(i < no->chavesPreenchidas && chave > no->chaves[i]){
        
        if(chave == no->chaves[i]) return true;
        i++;

    }

    if(no->eFolha) return false;
    return buscaAuxiliar(no->filhos[i], chave);
}

void ArvoreB::remove(){
    
}

int ArvoreB::getOrdem(){
    return ordem;
}

NoB* ArvoreB::getRaiz(){
    return raiz;
}