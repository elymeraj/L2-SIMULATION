#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\n======================10 EXPERIMENTS========================");
    int heads=0;
    int tails=0;
    for(int i=0;i<10;i++) {
       if(rand()%2==1){
           heads++;
       }else tails ++;
    /*
     printf("\n======================100 EXPERIMENTS=======================");
    for(int i=0;i<100;i++) {
       if(rand()%2==1){
           heads++;
       }else tails ++;
    */

    /*
     printf("\n======================1000 EXPERIMENTS======================");
    for(int i=0;i<1000;i++) {
       if(rand()%2==1){
           heads++;
       }else tails ++;
    */
    }
    printf("\n%d times head, %d times tails ", heads, tails);
    return 0;

}
