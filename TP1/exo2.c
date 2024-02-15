 
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n=======================TEST FOR SEED 4100=========================");
    int N0=4100;
    for(int i=0; i<10;i++) {
    N0= N0*N0;
    N0= N0/100;
    N0= N0%10000;
    printf("\n%d", N0);
    }
      return 0;
}

/*
 int main() {
    printf("\n=======================TEST FOR SEED 1234=========================");
    int N0=1324;
    for(int i=0; i<10;i++) {
    N0= N0*N0;
    N0= N0/100;
    N0= N0%10000;
    printf("\n%d", N0);
    }
      return 0;
 */

/*
 int main() {
    printf("\n=======================TEST FOR SEED 1301=========================");
    int N0=1301;
    for(int i=0; i<10;i++) {
    N0= N0*N0;
    N0= N0/100;
    N0= N0%10000;
    printf("\n%d", N0);
    }
      return 0;
 */
