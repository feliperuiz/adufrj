#include "cache.h"

extern double tempoSimulacao;

cache::cache() {
    taxasChegada = std::deque<double>();
    arquivos = std::deque<int>();
}

cache::cache(std::deque<double> taxas, std::deque<int> arquivosIniciais) {
    taxasChegada = taxas;
    arquivos = arquivosIniciais;
}

cache& cache::insereArquivo(int idArquivo) {
    if ( arquivos.size() >= SIM_MAX_FILES_PER_CACHE ) {
        int arquivo = arquivos.front();
        arquivos.pop_front();
        if ( DEBUG || LOGGING ) {
//            std::cout << "[ " << tempoSimulacao << " ] {RT_" << arquivo << "} Retirei da cache acima o arquivo " << arquivo << std::endl;
            std::cout << "{RT_" << arquivo << "}" << std::endl;
        }
    }
    arquivos.push_back(idArquivo);

    return *this;
}

bool cache::buscaArquivo(int idArquivo) {
    if ( std::find(arquivos.begin(), arquivos.end(), idArquivo) != arquivos.end() ) {
        return true;
    }
    return false;
}


void cache::imprimeConteudo() {
    if ( DEBUG ) {
        for (unsigned int i = 0; i < arquivos.size(); ++i) {
            std::cout << "arquivo(" << i << ") = " << arquivos[i] << " ";
        }
        std::cout << std::endl;
    }
}
