#include <stdio.h>
#include <stdlib.h>

int intRand(int x0, int a, int c, int m){
    x0=(a*x0+c)%m;
    return x0;
}
int main(){
    int x0=5;
    int a=5;
    int c=1;
    int m=16;
    printf("THE 32 FIRST PSEUDO-RANDOM NUMBERS ARE:\n");
    for(int i=0; i<32;i++){
        x0=intRand(x0,a,c,m);
        printf("%d, ", x0);
    }
    return 0;
}
