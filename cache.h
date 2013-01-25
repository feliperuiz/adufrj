#ifndef CACHE_H
#define CACHE_H

#include <deque>
#include <algorithm>
#include "globais.h"

class cache {
public:
    cache();
    cache(int maxArquivos);

    int getMaxArquivos();
    int getTotalArquivos();
    std::deque<int> getArquivos();

    cache& insere(int idArquivo);
    bool buscaArquivo(int idArquivo);


    void imprimeArquivos();
private:
    std::deque<int> arquivos;
    int maxArquivos;
};

#endif // CACHE_H
