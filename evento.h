#ifndef EVENTO_H
#define EVENTO_H

class evento {
public:
    evento(int idArquivo, int idCache, double tempoChegada);

    inline int getArquivo() const { return this->idArquivo; }
    inline int getCache() const { return this->idCache; }
    double getTempoChegada() const { return this->tempoChegada; }

    inline bool operator>(const evento& e) const { return this->getTempoChegada() > e.getTempoChegada(); }
    inline bool operator<(const evento& e) const { return *this > e; }

private:
    int idArquivo, idCache;
    double tempoChegada;
};


#endif // EVENTO_H
