#include "router.h"
#include <typeinfo>

router::router() {
}

void router::printVizinhos() {
    for ( std::deque<router* >::iterator it = vizinhos.begin(); it != vizinhos.end(); ++it ) {
        std::cout << (*it)->str << " ";
    }
    std::cout << std::endl;
}

router& router::getVizinhoAleatorio() {
    std::cout << vizinhos.size() << std::endl;
    int vizinho = rand()%vizinhos.size();

    std::cout << "Meus vizinhos são: ";
    printVizinhos();

    std::cout << "Estou indo para o vizinho " << vizinhos.at(vizinho)->getTexto() << std::endl;
    return *(vizinhos.at(vizinho));
}

bool router::achouArquivo() {
    std::cout << "Não achei o arquivo no " << str << std::endl;
    return false;
}
