#include <iostream>
#include "cache.h"
#include "sistema.h"
//#include "simulador.h"

using std::cout;
using std::endl;


int main() {
    //taxasCache[i][j] = taxa do arquivo j no cache i
    std::deque< std::deque< double > > taxasCache;
    std::deque< std::deque< int > >  arquivosIniciais;

    double t1[SIM_TOTAL_FILES] = {0.35, 0.55, 0.1};
    double t2[SIM_TOTAL_FILES] = {0.05, 0.15, 0.8};

    int a1[SIM_MAX_FILES_PER_CACHE] = {0,1};
    int a2[SIM_MAX_FILES_PER_CACHE] = {0,1};

    taxasCache.push_back(std::deque<double>(t1, t1 + SIM_TOTAL_FILES));
    taxasCache.push_back(std::deque<double>(t2, t2 + SIM_TOTAL_FILES));

    arquivosIniciais.push_back(std::deque<int>(a1, a1 + SIM_MAX_FILES_PER_CACHE));
    arquivosIniciais.push_back(std::deque<int>(a2, a2 + SIM_MAX_FILES_PER_CACHE));

    sistema s(2, taxasCache, arquivosIniciais);

    cache& c = s.getCache(0);
    c.imprimeConteudo();
    c.insereArquivo(2);
    c.imprimeConteudo();

    s.buscaArquivo(0, 0);

    c.imprimeConteudo();

    return 0;
}

/*
int main2(void)
{
    int numRouters = 2;
    int numArquivos = 3;
//    double taxas[][] = {}

    int maxArquivosRouter[] = {2, 2};
    simulador sim(numRouters, numArquivos, maxArquivosRouter);

    std::cout << "Chegou alguém no tempo t = " << simulador::geraChegada(0.55) << std::endl;

    cache& cache1 = sim.getCache(0);
    cache& cache2 = sim.getCache(1);

    cache1.insere(3).insere(2).insere(4);
    cache2.insere(2).insere(3);

    if ( sim.buscaArquivo(1, 0) ) {
        cout << "Achei o arquivo 1" << endl;
    } else {
        cout << "Não achei o arquivo 1" << endl;
    }

    return 0;
}*/
