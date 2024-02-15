#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n=========================PARCTICAL WORK 1=========================");
    printf("\n===========================EXERCISE 1=============================");
    int N0=1234;
    for(int i=0; i<20;i++) {
    N0= N0*N0;
    N0= N0/100;
    N0= N0%10000;
    printf("\n%d", N0);
    }
      return 0;
}
