#include <iostream>
//#include "cache.h"
#include "sistema.h"
#include "simulador.h"

#include "cacherouter.h"

/**
 * RT_i = Retirada do arquivo i
 * RQ_i_j = Requisição do arquivo i na cache j
 * IN_i_j = Inserção do arquivo i na cache j
 **/

using std::cout;
using std::endl;
double tempoSimulacao = 0;

int parte2() {

    srand( time(NULL) );

    router r1, r2;
    cacheRouter r3, r4, r5;

    r1.setTexto("router 1");
    r2.setTexto("router 2");
    r3.setTexto("router 3");
    r4.setTexto("router 4");
    r5.setTexto("router 5");


    r1.adicionaVizinho(&r2);

    r2.adicionaVizinho(&r1);
    r2.adicionaVizinho(&r3);
    r2.adicionaVizinho(&r4);

    r3.adicionaVizinho(&r2);
    r3.adicionaVizinho(&r4);
    r3.adicionaVizinho(&r5);

    r4.adicionaVizinho(&r2);
    r4.adicionaVizinho(&r3);
    r4.adicionaVizinho(&r5);

    r5.adicionaVizinho(&r3);
    r5.adicionaVizinho(&r4);

    r1.printVizinhos();
    r2.printVizinhos();
    r3.printVizinhos();
    r4.printVizinhos();
    r5.printVizinhos();

    std::cout << "      " << std::endl;
    int custo = 0;

    int ttl = SIM_PARTE_2_TTL;
    std::cout << "ttl inicial é de " << ttl << std::endl;
    router* routerAtual = &r1;

    while ( ttl > 0 && !routerAtual->achouArquivo() ) {
        --ttl;
        routerAtual = &routerAtual->getVizinhoAleatorio();
    }

    if ( ttl == 0 ) {
        custo = 100;
    }

    custo += SIM_PARTE_2_TTL - ttl;

    std::cout << "ttl final é de " << ttl << std::endl;
    std::cout << "Custo total para acessar o arquivo é de " << custo << std::endl;

    return 0;
}


int parte1() {

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
    /*int a2[SIM_MAX_FILES_PER_CACHE] = {0,1};

    double tempoChegada = simulador::geraChegadaPoisson(t[0][0]);
    sim.insereChegadaEmEventos(0, 0, tempoChegada);

    tempoChegada = simulador::geraChegadaPoisson(t[0][1]);
    sim.insereChegadaEmEventos(1, 0, tempoChegada);

    tempoChegada = simulador::geraChegadaPoisson(t[2]);
    sim.insereChegadaEmEventos(2, 0, tempoChegada);

    tempoChegada = simulador::geraChegadaPoisson(t2[0]);
    sim.insereChegadaEmEventos(0, 1, tempoChegada);

    tempoChegada = simulador::geraChegadaPoisson(t2[1]);
    sim.insereChegadaEmEventos(1, 1, tempoChegada);

    tempoChegada = simulador::geraChegadaPoisson(t2[2]);
    sim.insereChegadaEmEventos(2, 1, tempoChegada);

    taxasCache.push_back(std::deque<double>(t1, t1 + SIM_TOTAL_FILES));
    taxasCache.push_back(std::deque<double>(t2, t2 + SIM_TOTAL_FILES));

    arquivosIniciais.push_back(std::deque<int>(a1, a1 + SIM_MAX_FILES_PER_CACHE));
    arquivosIniciais.push_back(std::deque<int>(a2, a2 + SIM_MAX_FILES_PER_CACHE));*/

    for (int i = 0; i < 2; ++i) {
        taxasCache.push_back(std::deque<double>(t[i], t[i] + SIM_TOTAL_FILES));
        arquivosIniciais.push_back(std::deque<int>(a[i], a[i] + SIM_MAX_FILES_PER_CACHE));

        for (int j = 0; j < SIM_TOTAL_FILES; ++j) {
            tempoChegada = simulador::geraChegadaPoisson(t[i][j]);
            sim.insereChegadaEmEventos(j, i, tempoChegada);
        }
    }

    if ( DEBUG || LOGGING ) {
        std::cout << "Início do sistema:" << std::endl;
    }
    sim.imprimeListaDeEventos();

    sistema s(2, taxasCache, arquivosIniciais);

//    cache& c = s.getCache(0);

    while ( !sim.vazio() ) {
        evento e = sim.getPrimeiroEvento();
        ++totalEventos;

        tempoSimulacao = e.getTempoChegada();

        s.buscaArquivo(e.getArquivo(), e.getCache());
        if ( totalEventos < SIM_STOP_CONDITION ) {
            tempoChegada = simulador::geraChegadaPoisson(t[e.getCache()][e.getArquivo()]);
            sim.insereChegadaEmEventos(e.getArquivo(), e.getCache(), e.getTempoChegada() + tempoChegada);
        }

        sim.imprimeListaDeEventos();

        if ( sim.vazio() ) {
            std::cout << "[" << e.getTempoChegada() << "]{FIM}";
        }
    }


    return 0;
}


int main(void) {
    parte1();

    return 0;
}
