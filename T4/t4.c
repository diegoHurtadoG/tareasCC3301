//
// Created by diego on 05-10-19.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "integral.h"

typedef struct {
    Funcion f;
    void *pt;
    double inic;
    double fin;
    double num;
    double val;
} Integral;


void *calcfun(void *ptr){
    Integral *inte = (Integral *)ptr;
    inte->val = integral(inte->f, inte->pt, inte->inic, inte->fin, inte->num);
    return NULL;
}

double integral_par(Funcion f, void *ptr, double xi, double xf, int n, int p) {
    double resultadoFinal = 0;

    Integral arreglo_integrales[p];
    pthread_t comps[p];

    double intervalo = (xf - xi) / p;

    for(int k=0; k<p; k++){
        Integral *integralActual = &arreglo_integrales[k];
        integralActual->f = f;
        integralActual->pt = ptr;
        integralActual->inic = (k * intervalo ) + xi;
        integralActual->fin = ( (k + 1) * intervalo ) + xi;
        integralActual->num = n / p;
        pthread_create(&(comps[k]), NULL, calcfun, &(arreglo_integrales[k]));
    }

    for(int j=0; j<p; j++) {
        pthread_join(comps[j], NULL);
    }

    for(int i=0; i<p; i++){
        resultadoFinal += arreglo_integrales[i].val;
    }

    return resultadoFinal;
}


