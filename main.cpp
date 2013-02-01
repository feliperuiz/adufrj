#include <iostream>
#include "cache.h"
#include "sistema.h"
#include "simulador.h"

using std::cout;
using std::endl;


int main() {

    srand( time(NULL) );

    simulador sim;
    int totalEventos = 0;

    //taxasCache[i][j] = taxa do arquivo j no cache i
    std::deque< std::deque< double > > taxasCache;
    std::deque< std::deque< int > >  arquivosIniciais;

    double t[2][SIM_TOTAL_FILES] = {{0.35, 0.55, 0.1}, {0.05, 0.15, 0.8}};
//    double t2[SIM_TOTAL_FILES] = {0.05, 0.15, 0.8};

    int a[2][SIM_MAX_FILES_PER_CACHE] = {{0,1}, {0,1}};

    double tempoChegada;
//    int a2[SIM_MAX_FILES_PER_CACHE] = {0,1};

//    double tempoChegada = simulador::geraChegadaPoisson(t[0][0]);
//    sim.insereChegadaEmEventos(0, 0, tempoChegada);

//    tempoChegada = simulador::geraChegadaPoisson(t[0][1]);
//    sim.insereChegadaEmEventos(1, 0, tempoChegada);

//    tempoChegada = simulador::geraChegadaPoisson(t[2]);
//    sim.insereChegadaEmEventos(2, 0, tempoChegada);

//    tempoChegada = simulador::geraChegadaPoisson(t2[0]);
//    sim.insereChegadaEmEventos(0, 1, tempoChegada);

//    tempoChegada = simulador::geraChegadaPoisson(t2[1]);
//    sim.insereChegadaEmEventos(1, 1, tempoChegada);

//    tempoChegada = simulador::geraChegadaPoisson(t2[2]);
//    sim.insereChegadaEmEventos(2, 1, tempoChegada);

//    taxasCache.push_back(std::deque<double>(t1, t1 + SIM_TOTAL_FILES));
//    taxasCache.push_back(std::deque<double>(t2, t2 + SIM_TOTAL_FILES));

//    arquivosIniciais.push_back(std::deque<int>(a1, a1 + SIM_MAX_FILES_PER_CACHE));
//    arquivosIniciais.push_back(std::deque<int>(a2, a2 + SIM_MAX_FILES_PER_CACHE));

    for (int i = 0; i < 2; ++i) {
        taxasCache.push_back(std::deque<double>(t[i], t[i] + SIM_TOTAL_FILES));
        arquivosIniciais.push_back(std::deque<int>(a[i], a[i] + SIM_MAX_FILES_PER_CACHE));

        for (int j = 0; j < SIM_TOTAL_FILES; ++j) {
            tempoChegada = simulador::geraChegadaPoisson(t[i][j]);
            sim.insereChegadaEmEventos(j, i, tempoChegada);
        }
    }

    std::cout << "Início do sistema:" << std::endl;
    sim.imprimeListaDeEventos();

    std::cout << std::endl << std::endl;

    sistema s(2, taxasCache, arquivosIniciais);

//    cache& c = s.getCache(0);

    while (totalEventos < SIM_STOP_CONDITION) {
        evento e = sim.getPrimeiroEvento();
        totalEventos++;
        std::cout << "Requisição ao arquivo " << e.getArquivo() << " no cache " << e.getCache() << " no tempo " << e.getTempoChegada() << std::endl << std::endl;

        s.buscaArquivo(e.getArquivo(), e.getCache());
        std::cout << std::endl;
        tempoChegada = simulador::geraChegadaPoisson(t[e.getCache()][e.getArquivo()]);
        sim.insereChegadaEmEventos(e.getArquivo(), e.getCache(), e.getTempoChegada() + tempoChegada);

        sim.imprimeListaDeEventos();
    }


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
