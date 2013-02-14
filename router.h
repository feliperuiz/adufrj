#ifndef ROUTER_H
#define ROUTER_H

#include "globais.h"
#include <deque>

class router {
public:
    router();

    inline void setTexto(std::string a) { str = a; }
    inline std::string getTexto() { return str; }

    inline router adicionaVizinho(router* r) { vizinhos.push_back(r); return *this; }
    inline router setVizinhos(std::deque<router* > v) { vizinhos = v; return *this; }

    router& getVizinhoAleatorio();
    void printVizinhos();

    virtual bool achouArquivo();
protected:
    std::deque<router* > vizinhos;

    std::string str;
};

#endif // ROUTER_H
