#include <iostream>
#include "simulador.h"

using std::cout;
using std::endl;

int main(void)
{
    int maxArquivosRouter[] = {5, 2};
    simulador sim(2, 3, maxArquivosRouter);

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
}
