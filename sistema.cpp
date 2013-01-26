#include "sistema.h"

sistema::sistema() {
}

sistema::sistema(int numCaches, std::deque< std::deque<double> > taxas, std::deque< std::deque<int> > arquivosIniciais) {
    for (int i = 0; i < numCaches; ++i) {

        cache c(taxas[i], arquivosIniciais[i]);

        caches.push_back(c);
    }
}

bool sistema::buscaArquivo(int idArquivo, int idCache) {

    std::cout << "buscando arquivo " << idArquivo << " no cache " << idCache << std::endl;

    if ( getCache(idCache).buscaArquivo(idArquivo) ) {
        std::cout << "achou arquivo " << idArquivo << " no cache " << idCache << std::endl;
        return true;
    } else {
        std::cout << "não achou arquivo " << idArquivo << " no cache " << idCache << std::endl;
        //se achou arquivo no próximo cache, vamos copiar pra o cache atual;
        if ( buscaArquivo(idArquivo, idCache+1) ) {
            getCache(idCache).insereArquivo(idArquivo);
        }
    }
}
