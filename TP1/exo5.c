#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("\n===============================A DICE WITH 6 FACES==============================");
    printf("\n================================100 EXPERIMENTS=================================");
    int n=6;
    int tab[6]={0,0,0,0,0,0};
    for(int i=0;i<100;i++){
        switch(rand()%6){
        case 0: tab[0]++; 
        break;
        case 1: tab[1]++; 
        break;
        case 2: tab[2]++; 
        break;
        case 3: tab[3]++; 
        break;
        case 4: tab[4]++; 
        break;
        case 5: tab[5]++; 
        break;
        }
    }
    for(int i=0;i<6;i++){
        printf("\nFace %d, %d times!", i+1, tab[i] );
    }
    printf("\n===============================1000 EXPERIMENTS=================================");
    for(int i=0;i<1000;i++){
        switch(rand()%6){
        case 0: tab[0]++; 
        break;
        case 1: tab[1]++; 
        break;
        case 2: tab[2]++; 
        break;
        case 3: tab[3]++; 
        break;
        case 4: tab[4]++; 
        break;
        case 5: tab[5]++; 
        break;
        }
    }
    for(int i=0;i<6;i++){
        printf("\nFace %d, %d times!", i+1, tab[i] );
    }
    printf("\n=======================NOW WE HAVE A DICE WITH 10 FACES=======================");
    printf("\n================================10 EXPERIMENTS================================");
    int m=10;
    int tab1[10]={0,0,0,0,0,0,0,0,0,0};
    for(int i=0;i<10;i++){
        switch(rand()%10){
        case 0: tab1[0]++; 
        break;
        case 1: tab1[1]++; 
        break;
        case 2: tab1[2]++; 
        break;
        case 3: tab1[3]++; 
        break;
        case 4: tab1[4]++; 
        break;
        case 5: tab1[5]++; 
        break;
        case 6: tab1[6]++; 
        break;
        case 7: tab1[7]++; 
        break;
        case 8: tab1[8]++; 
        break;
        case 9: tab1[9]++; 
        break;
        }
    }
    for(int i=0;i<10;i++){
        printf("\nFace %d, %d times!", i+1, tab1[i] );
    }
    printf("\n================================100 EXPERIMENTS================================");
    for(int i=0;i<100;i++){
        switch(rand()%10){
        case 0: tab1[0]++; 
        break;
        case 1: tab1[1]++; 
        break;
        case 2: tab1[2]++; 
        break;
        case 3: tab1[3]++; 
        break;
        case 4: tab1[4]++; 
        break;
        case 5: tab1[5]++; 
        break;
        case 6: tab1[6]++; 
        break;
        case 7: tab1[7]++; 
        break;
        case 8: tab1[8]++; 
        break;
        case 9: tab1[9]++; 
        break;
        }
    }
    for(int i=0;i<10;i++){
        printf("\nFace %d, %d times!", i+1, tab1[i] );
    }
    printf("\n===============================1000 EXPERIMENTS================================");
    for(int i=0;i<1000;i++){
        switch(rand()%10){
        case 0: tab1[0]++; 
        break;
        case 1: tab1[1]++; 
        break;
        case 2: tab1[2]++; 
        break;
        case 3: tab1[3]++; 
        break;
        case 4: tab1[4]++; 
        break;
        case 5: tab1[5]++; 
        break;
        case 6: tab1[6]++; 
        break;
        case 7: tab1[7]++; 
        break;
        case 8: tab1[8]++; 
        break;
        case 9: tab1[9]++; 
        break;
        }
    }
    for(int i=0;i<10;i++){
        printf("\nFace %d, %d times!", i+1, tab1[i] );
    }
    printf("\n==============================1000000 EXPERIMENTS===============================");
    for(int i=0;i<1000000;i++){
        switch(rand()%10){
        case 0: tab1[0]++; 
        break;
        case 1: tab1[1]++; 
        break;
        case 2: tab1[2]++; 
        break;
        case 3: tab1[3]++; 
        break;
        case 4: tab1[4]++; 
        break;
        case 5: tab1[5]++; 
        break;
        case 6: tab1[6]++; 
        break;
        case 7: tab1[7]++; 
        break;
        case 8: tab1[8]++; 
        break;
        case 9: tab1[9]++; 
        break;
        }
    }
    for(int i=0;i<10;i++){
        printf("\nFace %d, %d times!", i+1, tab1[i] );
    }

}



