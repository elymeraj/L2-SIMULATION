#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32()>>1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32()*(1.0/4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32()*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5)*(1.0/4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6;
    return(a*67108864.0+b)*(1.0/9007199254740992.0);
}
/* These real versions are due to Isaku Wada, 2002/01/09 added */

// EXERCICE 1
double simPi(int nbPts){
    int compt=0;
    double xr,yr;
    for(int i=0;i<nbPts;i++){
        xr=genrand_real1();
        yr=genrand_real1();
        if((xr*xr+yr*yr)<1){
            compt++;
        }
    }
    return (double)compt/nbPts*4;

}

// EXERCICE 2
double * mean(int nbSim,int nbPts ){ // nbSim--> number of simulations, nbPts--> number of points which we will test the fonction
    double* arrPi=malloc(nbSim*sizeof(double)); // arrPi is an array which will stock all the values of Pi
    double absErr, relErr; // two variables which takes the values of absolut error and relative error
    double meanArr; // It's a variable which will takes the avarage of array arrPi
    double sum=0; // A variable sum which will help us to calculate the mean
    for(int i=0;i<nbSim;i++){ // Here I have initialized our array to 0
        arrPi[i]=0;
    }
    for(int i=0;i<nbSim;i++){ // Here I've placed all the values of Pi in exercice 1 to our array
        arrPi[i]=simPi(nbPts);
    }
    for(int i=0;i<nbSim;i++){ // The variable sum takes the sum of all elements in array aarPi
        sum+=arrPi[i];
    }
    meanArr=sum/nbSim; //Here the variable meanArr calcualtes the avarage of our values of Pi
    absErr=meanArr-M_PI; // Calcul of absolut error
    relErr=absErr/M_PI; // Calcul of relativ error
    printf("All the values of Pi for %d simulations and %d points: \n", nbSim, nbPts);
    for(int i=0;i<nbSim;i++){ // Display of our array with all the values of Pi
        printf("%f ,", arrPi[i]);
    }
    printf("\nThe value of absolute error is: %f \n",absErr);
    printf("The value of relative error is: %f \n",relErr);
    return arrPi; // Return of array with the values of Pi
}

// EXERCICE 3
void confIntervals(){
    int n=30; //I have initialized a variable n which contains the number of iterations
    double sum=0;
    double Xbarre; // The value of mean
    double simVar=0; // I have declared and initialized to 0 the value of variance
    double R=0;// Declaration of error margin
    double t=2.042; // the value of t for 30 experiments
    double *arr=malloc(n*sizeof(double)); // I have allocated a space in the memory four our array
    arr=mean(30,1000000); // This array calculates the mean for 30 experiments with 1'000'000 points
    for(int i=0;i<n;i++){ // sum of elements of array
        sum+=arr[i];
    }
    Xbarre=sum/n; // Calcul of the value of Xbarre
    for(int i=0;i<n;i++){
    simVar+=pow(arr[i]-Xbarre,2);
    }
    simVar/=n-1; // final value of simVar, calculated by the formula in the cours
    R=t*sqrt(simVar/n); // Calculating error margin by the formula in the cours
    printf("The value of error margin is :%f \n",R);
    printf("The mean Xbarre = %f\n", Xbarre);
    printf("Value of variance = %f\n", simVar);
    printf("The interval which which takes 95b percent of values is: [%f,%f]\n", Xbarre-R,Xbarre+R);
}


int main(void)
{
    int i;
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    printf("=======================EXERCICE 1======================");
    printf("\nFor 1'000 points the value of Pi is: %f \n", simPi(1000));
    printf("For 1'000'000 points the value of Pi is: %f \n", simPi(1000000));
    //printf("For 1'000'000'000 points the value of Pi is:%f \n", simPi(1000000000));
    printf("=======================EXERCICE 2======================\n");
    mean(10,1000);
    mean(10,1000000);
    //mean(10,1000000000);
    mean(20,1000);
    mean(20,1000000);
    //mean(20,1000000000);
    mean(30,1000);
    mean(30,1000000);
    //mean(30,1000000000);
    printf("=======================EXERCICE 3======================\n");
    confIntervals();
    return 0;
}