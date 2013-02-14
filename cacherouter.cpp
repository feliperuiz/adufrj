#include "cacherouter.h"

cacheRouter::cacheRouter() {}

bool cacheRouter::achouArquivo() {
    double p = (double)(rand()%101)/100; //Gerando número entre 0 e 100, dividindo por 100 para pegar um número entre 0 e 1
    if ( p <= SIM_PARTE_2_P ) {
        std::cout << "Achei o arquivo com p = " << p << std::endl;
        return true;
    }
    std::cout << "Não achei o arquivo com p = " << p << std::endl;
    return false;
}
