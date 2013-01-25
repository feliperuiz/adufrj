#include "simulador.h"

simulador::simulador() {
    totalArquivos = 0;
    cacheRouters = std::deque<cache>();
}

simulador::simulador(int numRouters, int numArquivos, int *maxArquivosRouter) {
    totalArquivos = numArquivos;
    cacheRouters = std::deque<cache>();
    for (int i = 0; i < numRouters; ++i) {
        cache router = cache(maxArquivosRouter[i]);
        cacheRouters.push_back(router);
    }
}

cache& simulador::getCache(int position) {
    return cacheRouters[position];
}

bool simulador::buscaArquivo(int idArquivo, int idCache) {

    if ( idCache >= cacheRouters.size() ) {
        std::cout << "Cheguei ao fim do routers" << std::endl;
        return false;
    }


    if ( getCache(idCache).buscaArquivo(idArquivo) ) {
        std::cout << "Achei o arquivo " << idArquivo << " no cache " << idCache << std::endl;
        return true;
    } else {
        std::cout << "Não achei o arquivo " << idArquivo << " no cache " << idCache << std::endl;
        std::cout << "Buscando no cache " << idCache + 1 << std::endl;
        return buscaArquivo(idArquivo, idCache + 1);
    }
}
