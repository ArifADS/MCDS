//
//  main.c
//  MCDS
//
//  Created by Arif De Sousa on 2/13/13.
//  Copyright (c) 2013 Arif De Sousa. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define _MAX_ 100
typedef int matrizAdy[_MAX_][_MAX_];
typedef int vector[_MAX_];
typedef char string[64];
void ady_load(FILE* in,matrizAdy mAdy);
void ady_print(matrizAdy mAdy, int n);
int camino(matrizAdy CopiamAdy,vector v,int v1,int v2,int n,int o);
void ady_clone(matrizAdy mAdy,matrizAdy mAdyc,int n);
void ady_init(matrizAdy mAdy);
void mostrarEnPantalla(FILE *in,int k);
float compMetric(int n,matrizAdy mAdy);

int main(){
    FILE* in,*out;
    int k=1;
    out=NULL;

    in = fopen("mapaweb.in", "r");
    if (in==NULL)
        in = fopen("/Users/ADS/Dropbox/Programming/MCDS/MCDS/mapaweb.in", "r");
    if (in==NULL) {
        printf("no consegui el archivo ;(");
        return -1;
    }
    getchar();
    while (!feof(in)) {
        
        mostrarEnPantalla(in,k);
        k++;
    }
    
        
    fclose(in);
    return 0;
}

void mostrarEnPantalla(FILE *in,int k){
    matrizAdy mAdy,mAdyc;
    vector v;
    float Cp;
    int n,i,v1,v2;
    fscanf(in, "%d",&n);
    if (!n) return;
    printf("Diseño de hipertexto del producto #%d",k);
    //printf("\n%d\n",n);
    ady_init(mAdy);
    ady_load(in,mAdy);
    //ady_print(mAdy, n);
    //printf("\n");
    Cp = compMetric(n,mAdy);
    printf("\nCp = %.2f",Cp);
    fscanf(in,"%d", &v1);
    while (v1!=0) {
        fscanf(in, "%d",&v2);
        v[0]=-1;
        ady_clone(mAdy, mAdyc, n);
        camino(mAdyc, v, v1-1, v2-1, n,0);
        printf("\nPara ir de %d a %d necesitas pasar por:\n",v1,v2);
        printf("%d - ",v1);
        for (i=v[0]-1; i>0; i--) {
            printf("%d - ",v[i]+1);
        }
        printf("%d\n\n",v2);
        fscanf(in,"%d", &v1);
    }

}

int camino(matrizAdy mAdyc,vector v,int v1,int v2,int n,int o){
    int i,a=0;
    
    if (mAdyc[v1][v2]) {
        if (v[0]==-1||v[0]>o) {
            v[0]=1;
            v[1]=v2;
            //v[2]=-1;
        }
        return 1;
    }
    else{
        for (i=0; i<n; i++) {
            //printf("-%d %d\n",v1,i);
            if (mAdyc[v1][i]) {
                mAdyc[v1][i]=mAdyc[i][v1]=0;
                a= camino(mAdyc,v,i, v2, n,o+1);
                if (a) {
                    v[v[0]] = i;
                    v[0]=v[0]+1;
                }
            }
            
        }
    }
    return a;
}

void ady_init(matrizAdy mAdy){
    int i,j;
    for (i=0; i<_MAX_; i++) {
        for (j=0; j<_MAX_; j++) {
            mAdy[i][j]=0;
        }
    }
}

void ady_clone(matrizAdy mAdy,matrizAdy mAdyc,int n){
    int i,j;
    
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            mAdyc[i][j]=mAdy[i][j];
        }
    }
    
}

void ady_print(matrizAdy mAdy, int n){
    int i,j;
    printf("    ");
    for (i=0; i<n; i++) {
        printf("%.2d ",i);
    }
    printf("\n");
    for (i=0; i<n; i++) {
        printf("%.2d ",i);
        for (j=0; j<n; j++) {
            if (mAdy[i][j]) {
                printf(" 1 ");
            }
            else printf(" - ");
        }
        printf("\n");
    }

}

void ady_load(FILE* in,matrizAdy mAdy){
    int v1,v2;
    fscanf(in, "%d",&v1);
    while (v1!=0) {
        fscanf(in, "%d",&v2);
        //sscanf(fs,"%d %d",&v1,&v2);
        mAdy[v1-1][v2-1] = mAdy[v2-1][v1-1]= 1;
        //fgets(fs,5,in);
        fscanf(in, "%d",&v1);
    }    
}



float compMetric(int n,matrizAdy mAdy){
    int d,D,s=0,i,j;
    float Cp;
    vector v;
    matrizAdy mAdyc;
    d = n*n-n;
    D= d*n;
    
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            v[0]=-1;
            ady_clone(mAdy, mAdyc, n);
            camino(mAdyc, v, i, j, n, 0);
            s=s+v[0];//placeholder
            //aqui va ir la distancia desde el vertice i hasta el j
            //si j no es alcanzable a i entonces devuelve n o se asigna n, werever.
            // i a i es igual a 0
        }
    }
    //printf("\n%d - %d / %d - %d",D,s,D,d);
    
    Cp = (D - s)/(float)(D-d);
    //printf("\n%.2f",Cp);
    return Cp;
}

int DistanciaItoJ(int i,int j){
    return 1;
}
/*
(a) Calcular el valor de métrica de compactación de la documentación (desarrollada al estilo de hipertexto)
    de un sistema de software, utilizando la menor cantidad de cálculos posibles.
(b) Dadas dos páginas de la documentación: Pi y Pj, se desea conocer la distancia de acceso Cij ,
    y las páginas que corresponden a la secuencia de accesos involucradas en esa distancia.
*/