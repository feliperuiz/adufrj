#include "sistema.h"

extern double tempoSimulacao;

sistema::sistema() {
}

sistema::sistema(int numCaches, std::deque< std::deque<double> > taxas, std::deque< std::deque<int> > arquivosIniciais) {
    for (int i = 0; i < numCaches; ++i) {

        cache c(taxas[i], arquivosIniciais[i]);

        caches.push_back(c);
    }
}

bool sistema::buscaArquivo(int idArquivo, int idCache) {

    if ( DEBUG ) {
        std::cout << "buscando arquivo " << idArquivo << " no cache " << idCache << std::endl;
    }

    //Para calcular X2 - ids começam de zero, logo idCache == 1 signfica o segundo cache
    if ( idCache == 1 ) {
        if ( LOGGING || DEBUG) {
            std::cout << "[ " << tempoSimulacao << " ] {RQ_" << idArquivo <<"_2}Requisição ao arquivo " << idArquivo << " na cache 2" << std::endl;
            std::cout << "\tCache 2 tem o seguinte conteúdo: ";
            getCache(idCache).imprimeConteudo();
        }
    }

    if ( idCache >= caches.size() ) {
        if ( DEBUG ) {
            std::cout << "Procurei em todos os caches, não achei" << std::endl;
        }
        return true;
    }

    if ( getCache(idCache).buscaArquivo(idArquivo) ) {
        if ( DEBUG ) {
            std::cout << "achou arquivo " << idArquivo << " no cache " << idCache << std::endl;
        }
        return true;
    } else {
        if ( DEBUG ) {
            std::cout << "não achou arquivo " << idArquivo << " no cache " << idCache << std::endl;
        }
        //se achou arquivo no próximo cache, vamos copiar pra o cache atual;
        if ( buscaArquivo(idArquivo, idCache+1) ) {
            //gravando todas as vezes que algum arquivo for copiado para a cache 2
            //como fazer saída? fazer busca? talvez seja a solução
            if ( idCache == 1 ) {
                if ( LOGGING || DEBUG) {
//                    std::cout << "[ " << tempoSimulacao << " ] {IN_" << idArquivo << "_2}Copiando arquivo " << idArquivo << " para cache 2";
                    std::cout << "[ " << tempoSimulacao << " ] {IN_" << idArquivo << "_2}";
                }
            }
            getCache(idCache).insereArquivo(idArquivo);
            return true;
        }
    }

    return false;
}
