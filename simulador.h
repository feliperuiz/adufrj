#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "globais.h"
#include "evento.h"
#include <queue>

class simulador {
public:
    simulador();

    simulador& insereChegadaEmEventos(int idArquivo, int idCache, double tempoChegada);
    void imprimeListaDeEventos();

    inline evento getPrimeiroEvento() {evento e = listaDeEventos.top(); listaDeEventos.pop(); return e;}
    inline bool vazio() { return listaDeEventos.empty(); }

    static double geraChegadaPoisson(double taxa);
private:
    std::priority_queue<evento, std::vector<evento>, std::greater<evento> > listaDeEventos;
};

#endif // SIMULADOR_H
