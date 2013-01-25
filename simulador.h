#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "cache.h"
#include "globais.h"

class simulador
{
public:
    simulador();
    simulador(int numRouters, int numArquivos, int* maxArquivosRouter);


    cache& getCache(int position);
    bool buscaArquivo(int idArquivo, int idCache);
private:
    int totalArquivos;
    std::deque<cache> cacheRouters;
};

#endif // SIMULADOR_H
