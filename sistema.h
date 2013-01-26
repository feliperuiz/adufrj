#ifndef SISTEMA_H
#define SISTEMA_H

#include "cache.h"

class sistema
{
public:
    sistema();
    sistema(int numCaches, std::deque< std::deque<double> > taxas, std::deque< std::deque<int> > arquivosIniciais);


    inline cache& getCache(int idCache) { return caches.at(idCache); }

    bool buscaArquivo(int idArquivo, int idCache);
private:
    std::deque<cache> caches;
};

#endif // SISTEMA_H
