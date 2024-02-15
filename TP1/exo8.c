#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int intRand(int x0, int a, int c, int m){
    x0=(a*x0+c)%m;
    return x0;
}
float floatRand(int x0, int m){
    float x00=(float)x0/(float)m;
    return x00;
}
int main(){
    // Tests for differents seeds (a,c,m)
    printf("For a=8, c=2 and m=9\n");
    int x0=5;
    int a=8;
    int c=2;
    int m=9;
    /*
    printf("For a=10, c=40 and m=7\n");
    int x0=5;
    int a=10;
    int c=7;
    int m=40;
    */
    /*
    printf("For a=33, c=7 and m=40\n");
    int x0=5;
    int a=10;
    int c=7;
    int m=40;
    */
    float x00;
    printf("\The values which takes x0 are: \n");
    for(int i=0; i<32;i++){
        x0=intRand(x0,a,c,m);
        printf("%d, ", x0);
    }
    printf("\nThe values which takes x00 are: \n");
    for(int i=0; i<32;i++){
        x0=intRand(x0,a,c,m);
        x00=floatRand(x0,m);
        printf("%.4f, ", x00);
    }

    return 0;
}
