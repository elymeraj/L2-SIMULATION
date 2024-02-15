#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Here we remplace the values which I found in google
int intRand(int x0, int a, int c, int m){
    x0=(a*x0+c)%m;
    return x0;
}
float floatRand(int x0, int m){
    float x00=(float)x0/(float)m;
    return x00;
}
int main(){
    int x0=5;
    int a=22695477;
    int c=1;
    int m=pow(2,32);
    float x00;
    printf("For m=2^32, a=22695477 and c=1: "\n);
    printf("The values of x00 are: \n");
    for(int i=0; i<32;i++){
        x0=intRand(x0,a,c,m);
        x00=floatRand(x0,m);
        printf("%.4f, ", x00);
    }
    
    return 0;
}
