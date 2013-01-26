#ifndef CACHE_H
#define CACHE_H

#include <deque>
#include <algorithm>
#include "globais.h"

class cache {
public:
    cache();
    cache(std::deque<double> taxas, std::deque<int> arquivosIniciais);

    cache& insereArquivo(int idArquivo);
    bool buscaArquivo(int idArquivo);


    void imprimeConteudo();

private:
    std::deque<double> taxasChegada;
    std::deque<int> arquivos;
};

#endif // CACHE_H
