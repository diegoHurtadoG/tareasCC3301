//
// Created by diego on 28-08-19.
//
#include "t2.h"
#include <stdio.h>

int calzar(Nodo *a, Nodo **ppat){
    Nodo *pa = *ppat;
    if( pa == NULL ){
        *ppat = a;
        return 1;
    }
    else if( a == NULL ){
        return 0;
    }
    else if( pa->x != a->x ){
        return 0;
    }
    else {
        int b_izq = calzar(a->izq, &pa->izq);
        int b_der = calzar(a->der, &pa->der);
        if ((b_izq == 1) && (b_der == 1)) {
            return 1;
        }

    }
    return 0;
}
