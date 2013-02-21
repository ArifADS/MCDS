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

int BusqFwd(int Org,int Dst,matrizAdy mAdy,vector Ondas,int n,int* NumOnd);
void BusqBck(int Org,int Dst,matrizAdy mAdy,vector Ondas,int n,int NumOnd,vector cam);
void onda_clean(vector Ondas);

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

    while (!feof(in)) {
        
        mostrarEnPantalla(in,k);
        k++;
    }
    
        
    fclose(in);
    return 0;
}

void mostrarEnPantalla(FILE *in,int k){
    matrizAdy mAdy;
    vector Ondas,cam;
    int NumOnd;

    float Cp;
    int n,i,j,v1,v2;
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
        if (BusqFwd(v1-1,v2-1,mAdy,Ondas,n,&NumOnd)){
            BusqBck(v1-1, v2-1, mAdy, Ondas, n, NumOnd, cam);
            printf("\nC%d,%d = %d\n",v1,v2,NumOnd-1);
            //printf("%d - ",v1);
            for (i=0; i<NumOnd; i++) {
                printf("%d - ",cam[i]+1);
            }

        }
        else{
            printf("\nNoConsegui Camino:(");
        }
        fscanf(in,"%d", &v1);
    }
    printf("\n\n");

}

void onda_clean(vector Ondas){
    int i;
    for (i=0; i<_MAX_; i++) {
        Ondas[i]=0;
    }
}

int BusqFwd(int Org,int Dst,matrizAdy mAdy,vector Ondas,int n,int* NumOnd){
	int i,w,j,k,d1,conseguida=0;
	vector Marcas;
	for (i=0;i<n;i++) {
		Marcas[i]=-1;
	}
    onda_clean(Ondas);
    k=0;
    *NumOnd=0;
    d1=k;
	Ondas[k++]=Org;
	Ondas[k++]=-1;
    *NumOnd = *NumOnd+1;
    d1=k;
	Marcas[Org] = 1;
	for (j = 0; j < n; j++) {
		if (mAdy[Org][j]){
			Ondas[k++]=j;
            Marcas[j]=1;
			if (j==Dst) conseguida=1;
		}
	}
	Ondas[k++]=-1;
    *NumOnd = *NumOnd+1;
	
	
	while ((!conseguida)&&(d1+1!=k)) {
		w=Ondas[d1++];
		while (w!=-1) {//Por cada vertice w en esa onda
			for (j = 0; j < n; j++) {
                //printf("\nw: %d mAdy[%d][%d]=%d Marcas[%d]=%d",w,w,j,mAdy[w][j],j,Marcas[j]);
				if (mAdy[w][j]&&Marcas[j]==-1){
					Ondas[k++]=j;
					Marcas[j]=1;
					if (j==Dst) conseguida=1;
				}
			}
			w=Ondas[d1++];
		}
        Ondas[k++]=-1;
        *NumOnd = *NumOnd+1;
	}
	Ondas[k++]=-2;
	return conseguida;
}

void BusqBck(int Org,int Dst,matrizAdy mAdy,vector Ondas,int n,int NumOnd,vector cam){
    int k;
    int i;
    for (i=0; i<_MAX_; i++) {
        cam[i]=0;
    }

    cam[NumOnd-1]=Dst;
    
        i=0;
    while (Ondas[i+1]!=-2) {
        i++;
    }
    i--;
    while (Ondas[i]!=-1) {
        i--;
    }
    
    for (k=NumOnd-1; k>=1; k--) {
        i--;
        //printf("\nk: %d",k);
        while ((Ondas[i]!=-1)||(i>0)) {
           // printf("\nmAdy[%d][%d]=%d",cam[k],Ondas[i],mAdy[cam[k]][Ondas[i]]);
            if (Ondas[i]==-1||i<0) {
                break;
            }
            
            if (mAdy[cam[k]][Ondas[i]]) {
                cam[k-1]= Ondas[i];
                //printf("conex %d con %d",Ondas[i],cam[k]);
            }
            i--;
        }
        
    }
    cam[0]=Org;
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
    int NumOndas;
    float Cp;
    vector Ondas;
    d = n*n-n;
    D= d*n;
    
    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            if (i!=j){
                if  (BusqFwd(i, j, mAdy, Ondas, n, &NumOndas))
                        s=s+NumOndas-1;
                else
                    s=s+n;
            }
    Cp = (D - s)/(float)(D-d);
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