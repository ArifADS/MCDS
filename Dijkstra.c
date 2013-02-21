//
//  Dijkstra.c
//  MCDS
//
//  Created by Arif De Sousa on 2/15/13.
//  Copyright (c) 2013 Arif De Sousa. All rights reserved.
//

#include <stdio.h>
#define _MAX_ 100
typedef int matrizAdy[_MAX_][_MAX_];
typedef int vector[_MAX_];

void dijkstra(matrizAdy mAdy,vector cam,vector costo,int n){
    vector T;
    int i,j;
    int Origen =0;
    for (i=0; i<n; i++) {
        cam[i]=0;
    }
    T[Origen]=1;
    costo[Origen]=0;
    cam[Origen]=Origen;
    
    for (i=1; i<n; i++) {
        if (mAdy[Origen][i]) {
            costo[i]=mAdy[Origen][i];
            cam[i]=Origen;
        }
        else
            costo[i]=n;
    }
    
    for (i=Origen; i<n&&T[i]!=1; i++) {
        T[i]=1;
        for (j=Origen; j<n&&T[j]!=1; j++) {
            if (costo[i]+mAdy[i][j]<costo[j]) {
                costo[j]=costo[i]+mAdy[i][j];
                cam[j]=i;
            }
        }
        
    }
}