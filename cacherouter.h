#ifndef CACHEROUTER_H
#define CACHEROUTER_H

#include "router.h"

class cacheRouter : public router {
public:
    cacheRouter();

    bool achouArquivo();
};

#endif // CACHEROUTER_H
