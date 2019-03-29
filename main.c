#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inSVG.h"
#include "outSVG.h"
#include "structs.h"

int main(int argc, char *argv[]){
    int i = 1, j = 0;
    int nx = 1000;
    char *pathIn = NULL, *nameIn = NULL, *arqGeo = NULL;
    char *nameConsulta = NULL, *arqQry = NULL;
    char *pathOut = NULL, *nameOut = NULL, *arqSVG = NULL;
    char forma;
    FILE *arqIn, *arqOut, *arqConsul;

    Formas *figuras;

    /*Recebe os parametros da main (argv)*/
    receberParametros(argc, argv, &pathIn, &nameIn, &nameConsulta, &pathOut);
    
    /*Prepara o diretorio para abrir o arquivo de entrada*/

    if(pathIn != NULL){
        alocarMemoria(nameIn, pathIn, &arqGeo);
        arqIn = fopen(arqGeo, "r");
    }
    else{
        arqIn = fopen(nameIn, "r");
    }

    if(nameConsulta != NULL){
        if(pathIn != NULL){
            alocarMemoria(nameConsulta, pathIn, &arqQry);
            arqConsul = fopen(arqQry, "r");
        }
        else{
            arqConsul = fopen(nameConsulta, "r");
        }
    }

    /*Prepara o diretorio para criar o arquivo de saida*/
    criarArqSaida(&nameOut, nameIn);
    strcat(nameOut, ".svg");
    alocarMemoria(nameOut, pathOut, &arqSVG);
    arqOut = fopen(arqSVG, "w");
    fputs("<svg>\n", arqOut);

    /*Cria o vetor de structs para armazenar as dados das formas*/
    figuras = (Formas *)malloc(nx * sizeof(Formas));

    /*Le os dados das formas geometricas do arquivo de entrada*/
    while(1){
        if(feof(arqIn))
            break;

        lerFormaGeometrica(arqIn, &forma);

        if(forma == 'c'){
            lerCirculo(arqIn, figuras, arqOut);
        }
        else if(forma == 'r'){
            lerRetangulo(arqIn, figuras, arqOut);
        }
        else if(forma == 'n'){
            nx = lerNX(arqIn);
            figuras = realloc(figuras, nx * sizeof(Formas));
        }
        else if(forma == 't'){
            lerTexto(arqIn, arqOut);
        }
    }

    /*Finalizacao e fechamento dos arquivos*/
    fputs("\n</svg>\n", arqOut);
    if(nameConsulta != NULL)
        fclose(arqConsul);
    fclose(arqOut);
    fclose(arqIn);

    /*Libera a memoria reservada para strings e vetores*/
    free(pathIn);
    free(nameIn);
    free(arqGeo);
    free(arqQry);
    free(nameConsulta);
    free(pathOut);
    free(nameOut);
    free(arqSVG);
    free(figuras);

    return 0;
}
