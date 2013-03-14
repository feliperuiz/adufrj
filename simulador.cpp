#include "simulador.h"

simulador::simulador() {
    listaDeEventos = std::priority_queue<evento, std::vector<evento>, std::greater<evento> >();
}

simulador& simulador::insereChegadaEmEventos(int idArquivo, int idCache, double tempoChegada) {
    listaDeEventos.push( evento(idArquivo, idCache, tempoChegada) );
    return *this;
}

void simulador::imprimeListaDeEventos() {
    if ( !DEBUG ) {
        return;
    }
    std::priority_queue<evento, std::vector<evento>, std::greater<evento> > copia = listaDeEventos;

    while ( !copia.empty() ) {
        evento e = copia.top();
        std::cout << "tempo de chegada " << e.getTempoChegada() << " idArquivo " << e.getArquivo() << " idCache " << e.getCache() << std::endl;
        copia.pop();
    }
    std::cout << std::endl;
}

double simulador::geraChegadaPoisson(double taxa) {
    double u = (double)(rand()%101)/100;
    double tempo = -log(u)/taxa;

    return tempo;
}
