#include "cacherouter.h"

cacheRouter::cacheRouter() {}

bool cacheRouter::achouArquivo() {
    double p = (double)(rand()%101)/100; //Gerando número entre 0 e 100, dividindo por 100 para pegar um número entre 0 e 1
    if ( p < SIM_PARTE_2_P ) {
        if ( DEBUG ) {
            std::cout << "Achei o arquivo com p = " << p << std::endl;
        }
        return true;
    }
    if ( DEBUG ) {
        std::cout << "Não achei o arquivo com p = " << p << std::endl;
    }
    return false;
}
