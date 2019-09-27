//
// Created by diego on 15-08-19.
//
#include "t1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Parte a

uint comprimir(uint* a, int nbits){
    uint *t=a;
    uint size=sizeof(uint) << 3;
    //size esta bien
    uint i = size;
    uint mask= ~( (-1) << nbits );
    //mask esta bien
    uint f=0;
    while(i > nbits){
        f=f << nbits;
        f=f | (*t & mask);
        i = i - nbits;
        t = t + 1;
    }
    return f;
}

//Parte b ya esta

char *insercion(char *d, char *s){
    char *r=malloc(strlen(d) + strlen(s) + 1);
    strcpy(r,s);
    strcat(r,d);
    return r;
}

//Parte c

void insertar(char *d, char *s){
    // d apunta a un char con mucha memoria, s es un "string"
    char *aux = d;
    aux = aux + strlen(d);
    char *aux_2 = aux;
    aux_2 = aux_2 + strlen(s);
    while(aux!=d){
        *aux_2 = *aux;
        aux--;
        aux_2--;
    }
    *aux_2=*aux;
    int c=0;
    while(c < strlen(s)+3){
        *aux=*s;
        aux++;
        s++;
        c++;
    }
}