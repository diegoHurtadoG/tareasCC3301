//
// Created by diego on 23-09-19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_line(FILE *io, char *lin, int i, int largo){
    if(fread(lin, 1, largo, io) != largo){
        perror("cola.txt");
        exit(2);
    }
}

void write_line(FILE *io, char *lin, int i, int largo){
    if(fwrite(lin, 1, largo, io) != largo){
        perror("cola.txt");
        exit(2);
    }
}

int priority_value(char *linea){
    char *linea_aux=linea + 10;
    return atoi(linea_aux);
}


int main(int argc, char **argv){
    FILE *in = fopen(argv[1], "r+");
    //If the condition is valid, then the file doesnt exists.
    if (in == NULL){
        perror("cola.txt");
        exit(1);
    }

    //linnum va a ser la linea del numero
    char linnum[5];
    //Asigno a linnum el arreglo de caracteres
    read_line(in, linnum, 0, 5);
    //n es el numero de la primera linea
    int n = atoi(linnum);

    if(n==0){
        perror("cola.txt");
        exit(1);
    }

    //En buf voy a ir guardando las lineas que lea
    char buf[17];
    char minbuf[10];
    char minbuffinal[12];
    int indicemin;

    int minimo = 1000000; //cualquier numero de 6 digitos va a ser menor
    for(int i=1; i<=n; i++){
        fseek(in, 5+(i-1)*17, SEEK_SET);
        read_line(in, buf, i, 17);
        if(priority_value(buf) < minimo){
            indicemin = i;
            minimo = priority_value(buf);
            memcpy(minbuf, buf, sizeof(minbuf));
        }
    }
    //Luego de esto tengo la linea que quiero sacar en el valor minbuf.
    //Se supone que esto imprime la linea minbuf
    memcpy(minbuffinal, minbuf, sizeof(minbuffinal));
    minbuffinal[10] = '\n';
    minbuffinal[11] = 0;
    printf("%s", minbuffinal);
    //Esto va a mover el puntero a la linea numero n
    fseek(in,5+(n-1)*17,SEEK_SET);
    //Lee la linea n y la guarda en buf
    fread(buf, 1, 17, in);
    //Mueve el puntero a la linea que acaba de imprimir
    fseek(in, 5+(indicemin-1)*17, SEEK_SET);
    //Sobreescribe la linea que imprimio con la numero n
    fwrite(buf, 1, 17, in);
    //Lo que me falta ahora es actualizar el valor de n
    fseek(in,0,SEEK_SET);
    sprintf(linnum, "%-4d\n", (n-1));
    fwrite(linnum,1,5,in);

    fclose(in);
}
