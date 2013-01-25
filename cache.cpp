#include "cache.h"

cache::cache() {
    maxArquivos = 0;
    arquivos = std::deque<int>();
}

cache::cache(int n) {
    maxArquivos = n;
    arquivos = std::deque<int>();
}

int cache::getMaxArquivos() {
    return maxArquivos;
}

int cache::getTotalArquivos() {
    return arquivos.size();
}

std::deque<int> cache::getArquivos() {
    return arquivos;
}

cache& cache::insere(int idArquivo) {
    if ( arquivos.size() >= maxArquivos ) {
        arquivos.pop_front();
    }
    arquivos.push_back(idArquivo);

    return *this;
}

bool cache::buscaArquivo(int idArquivo) {
    std::deque<int>::iterator posicao =  std::find(arquivos.begin(), arquivos.end(), idArquivo);
    if ( posicao == arquivos.end() ) {
        return false;
    }
    return true;
}

void cache::imprimeArquivos() {
    for (std::deque<int>::iterator it = arquivos.begin(); it != arquivos.end(); ++it) {
        std::cout << *it << std::endl;
    }
}
